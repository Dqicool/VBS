#include "genAna.h"
#include <RooUnfoldResponse.h>
#include <RooUnfoldBayes.h>
#include <RooUnfoldErrors.h>
#include <cstdlib>
#include <TLegend.h>
#include<THashList.h>
#include"ErrorProp.h"

//#define UNFOLDSELF
#define UNFLOLDDATA
using namespace std;
void distUnfold(const char* dist, const char* labeltex, TH1D* h_data)
{   

    TH1::SetDefaultSumw2();
    gStyle->SetPaintTextFormat("1.2f");
    //load file name into a vector
        std::vector<string> filevec{};
        filevec.push_back("output/resp_out/999_all/364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.root");
        filevec.push_back("output/resp_out/999_all/344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root");

        //filevec.push_back("output/resp_out/999_all/344295.Sherpa_Zee_4lMassFilter40GeV8GeV.root");
        //filevec.push_back("output/resp_out/999_all/344296.Sherpa_Zmumu_4lMassFilter40GeV8GeV.root");
        //filevec.push_back("output/resp_out/999_all/344297.Sherpa_Zee_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root");
        //filevec.push_back("output/resp_out/999_all/344298.Sherpa_Zmumu_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root");

        // filevec.push_back("output/resp_out/999_all/345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root");
        // filevec.push_back("output/resp_out/999_all/345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root");
        // filevec.push_back("output/resp_out/999_all/345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root");

        filevec.push_back("output/resp_out/999_all/345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root");
        filevec.push_back("output/resp_out/999_all/345706.Sherpa_222_NNPDF30NNLO_ggllll_130M4l.root");
        filevec.push_back("output/resp_out/999_all/345708.Sherpa_222_NNPDF30NNLO_ggllllNoHiggs_0M4l130.root");

        filevec.push_back("output/resp_out/999_all/346340.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_allhad.root");
        filevec.push_back("output/resp_out/999_all/346341.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_semilep.root");
        filevec.push_back("output/resp_out/999_all/346342.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_dilep.root");
        //filevec.push_back("output/resp_out/999_all/361601.PowhegPy8EG_WZlvll_mll4.root");
        // filevec.push_back("output/resp_out/999_all/364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6.root");
        // filevec.push_back("output/resp_out/999_all/364245.Sherpa_222_NNPDF30NNLO_WZZ_5l1v_EW6.root");
        // filevec.push_back("output/resp_out/999_all/364247.Sherpa_222_NNPDF30NNLO_ZZZ_6l0v_EW6.root");
        // filevec.push_back("output/resp_out/999_all/364248.Sherpa_222_NNPDF30NNLO_ZZZ_4l2v_EW6.root");
        filevec.push_back("output/resp_out/999_all/364250.Sherpa_222_NNPDF30NNLO_llll.root");
        //filevec.push_back("output/resp_out/999_all/410142.Sherpa_NNPDF30NNLO_ttll_mll5.root");
        //filevec.push_back("output/resp_out/999_all/410472.PhPy8EG_A14_ttbar_hdamp258p75_dil.root");
    //getting calculated response and stack
        std::vector<RooUnfoldResponse> resp_use_vec{};
        std::vector<RooUnfoldResponse> resp_disp_vec{};
        for (uint i = 0; i< filevec.size(); i++)
        {   
            string disp_save_name = "disp_resp_" + (string)(dist);
            string use_save_name = "use_resp_" + (string)(dist);
            TFile* f = TFile::Open(&(filevec[i])[0]);
            resp_use_vec.push_back(*((RooUnfoldResponse *)f->Get(&use_save_name[0])));
            resp_disp_vec.push_back(*((RooUnfoldResponse *)f->Get(&disp_save_name[0])));
        }
        RooUnfoldResponse resp_disp = resp_disp_vec[0];
        RooUnfoldResponse resp_use = resp_use_vec[0];
        for(uint i = 1; i < resp_disp_vec.size(); i++)
        {
            resp_disp.Add(resp_disp_vec[i]);
            resp_use.Add(resp_use_vec[i]);
        }

    //unfold
        auto h_meas = resp_use.Hmeasured();
        auto h_true = resp_use.Htruth();
        auto h_fake = resp_use.Hfakes();
        RooUnfoldBayes unfoldself(&resp_use, h_meas, 2);
        RooUnfoldBayes unfolddata(&resp_use, h_data, 1);
        auto cov = unfolddata.GetMeasuredCov();
        TH1D* h_unfold= (TH1D*) unfolddata.Hreco();
        unfolddata.PrintTable (std::cout);
        
    //save
        string pic_name = "plots/unfold/" + (string)(const char*)dist;
        auto unfold_name = pic_name + "_unfold.png";
        auto resp_name = pic_name + "_resp.png";
        auto resph_name = pic_name + "_resph.png";
        
        TCanvas *c1 = new TCanvas("c1","",1200,1200);
        auto pad1 = new TPad("pad1","", 0, 0.3, 1,    1,   0);
        auto pad2 = new TPad("pad2","", 0, 0,   1,    0.3, 0);
            pad1->Draw();
            pad2->Draw();
            pad1->cd();
            //h_unfold->SetAxisRange(0,25,"Y");
            h_unfold->SetTitle("");
            h_unfold->SetLineColorAlpha(kBlack,0);
            h_unfold->SetMarkerColor(kBlack);
            h_unfold->SetFillColorAlpha(kBlack, 0.2);
            h_unfold->SetMarkerStyle(kFullCircle);
            h_unfold->SetMarkerSize(2.0);
            h_unfold->SetLineWidth(2.0);
            h_unfold->GetXaxis()->SetTitle(labeltex);
            h_unfold->GetYaxis()->SetTitle("Events");
            h_unfold->SetAxisRange(0,30,"Y");
            h_unfold->Draw("E1");
            h_unfold->Draw("E2 same");

            h_data->SetLineColorAlpha(kBlack,0);
            h_data->SetMarkerColor(kBlue);
            h_data->SetFillColorAlpha(kBlue, 0.1);
            h_data->SetMarkerStyle(kFullSquare);
            h_data->SetMarkerSize(2.0);
            h_data->SetLineWidth(2.0);
            h_data->Draw("same E1");
            h_data->Draw("E2 same");

            h_meas->SetLineColor(kBlue);
            h_meas->SetLineWidth(2);
            h_meas->Draw("SAME HIST");
            auto h_tmp1 = (TH1D* )h_meas->Clone("h_tmp");
            h_tmp1->SetFillStyle(3004);
            h_tmp1->SetFillColorAlpha(kBlue,1);
            
            h_tmp1->Draw("SAME E2");

            h_true->SetLineColor(kBlack);
            h_true->SetLineWidth(2);
            h_true->Draw("SAME HIST");
            auto h_tmp2 = (TH1D* )h_true->Clone("h_tmpp");
            h_tmp2->SetFillStyle(3004);
            h_tmp2->SetFillColorAlpha(kBlack,1);
            h_tmp2->Draw("SAME E2");

            
            h_fake->SetLineColor(kGreen);
            h_fake->SetLineWidth(2);
            h_fake->Draw("HIST SAME");
            

            TLegend *legend = new TLegend(0.7, 0.55, 0.9, 0.9);
            legend->AddEntry(h_unfold,"Unfold Data","lepf");
            legend->AddEntry(h_tmp2,"Tru-level Pred","lepf");
            legend->AddEntry(h_data, "Data","lepf");
            legend->AddEntry(h_tmp1, "Det-level Pred","lepf");
            legend->AddEntry(h_fake, "Pred Fake","l");
            legend->Draw();

            pad2->cd();
            TH1D* h_sub = new TH1D(*h_unfold);
            TH1D* h_zero = new TH1D((*(TH1D*)h_tmp2));
            //h_sub->SetAxisRange(-5,5,"Y");
            for(uint i=1; i<=h_unfold->GetNbinsX(); i++){
                h_sub->SetBinContent(i, h_unfold->GetBinContent(i) / h_true->GetBinContent(i));
                h_sub->SetBinError(i, ErrADiviB(h_unfold->GetBinContent(i) / h_true->GetBinContent(i), h_unfold->GetBinContent(i),h_true->GetBinContent(i), h_unfold->GetBinError(i), h_true->GetBinError(i),0));
                h_zero->SetBinContent(i, 1);
                h_zero->SetBinError(i, ErrADiviB(1,h_true->GetBinContent(i), h_true->GetBinContent(i) , h_true->GetBinError(i), h_true->GetBinError(i),0));
            }
            h_sub->GetYaxis()->SetTitle("Unfolded / Prediction");
            h_sub->SetAxisRange(0,2,"Y");
            h_sub->Draw("");
            h_sub->Draw("E2 same");
            h_zero->Draw("SAME");
            h_zero->Draw("SAME E2");
        c1->Update();
        c1->SaveAs((&unfold_name[0]));

        auto* c2 = new TCanvas("c2","",2000,2000);
            c2->SetBottomMargin(0.2);
            c2->SetLeftMargin(0.2);
            auto m_resp = resp_disp.Mresponse();
            auto tmp = new TH2D(m_resp);
            for(int i=0; i < h_meas->GetNbinsX(); i++){
                std::stringstream buffer;
                buffer <<std::setprecision(3)<< h_meas->GetBinLowEdge(i+1);
                tmp->GetXaxis()->ChangeLabel(i+1,-1,-1,-1,-1,-1, &(buffer.str())[0]);
                tmp->GetYaxis()->ChangeLabel(i+1,-1,-1,-1,-1,-1, &(buffer.str())[0]);
            }
            tmp->SetTitle("Colums sum to unity, indecates how truth smeared");
            tmp->GetXaxis()->SetTitle("True");
            tmp->GetYaxis()->SetTitle("Meas");
            tmp->SetStats(0);
            tmp->SetMaximum(1);
            tmp->SetMinimum(0);
            tmp->Draw("COLZ");
            tmp->Draw("TEXT SAME");
            c2->SaveAs(&resp_name[0]);

        auto* c3 = new TCanvas("c3","",2000,2000);
            auto h_resp = resp_disp.Hresponse();
            h_resp->SetTitle("Colums sum to unity, indecates how measurments distributed in truth");
            h_resp->GetXaxis()->SetTitle("Meas");
            h_resp->GetYaxis()->SetTitle("True");
            h_resp->SetStats(0);
            h_resp->Draw("COLZ");
            h_resp->Draw("TEXT SAME");
            auto nx = h_resp->GetNbinsX();
            auto ny = h_resp->GetNbinsY();
            for(int i = 1; i <= nx; i++){
                auto linetotal = h_resp->Integral(i, i, 1, ny);
                for(int j = 1; j <= ny; j++){
                    h_resp->SetBinContent(i,j, h_resp->GetBinContent(i,j)/linetotal);
                }
            }
            h_resp->SetMaximum(1);
            h_resp->SetMinimum(0);
            //h_resp->Draw("COLZ");
            //h_resp->Draw("TEXT SAME");
            c3->SaveAs(&resph_name[0]);
            
        double errall, err;
        double all = h_true->IntegralAndError(1,4, errall,"");
        cout<<all<<"\t"<<errall<<endl;
}


int main(){
    TFile* inm4l = TFile::Open("output/histo_out/dem_unfold_m4l.root","read");
    TFile* inmjj = TFile::Open("output/histo_out/dem_unfold_mjj.root","read");
    TFile* indelphijj = TFile::Open("output/histo_out/dem_unfold_delphijj.root","read");

    auto datam4l = (TH1D*)inm4l->Get("h_rebin_m4l_data_cut");
    auto datamjj = (TH1D*)inmjj->Get("h_rebin_mjj_data_cut");
    auto datadelphijj = (TH1D*)indelphijj->Get("h_rebin_delphijj_data_cut");
    distUnfold("jj_delta_phi", "#Delta#phi_{jj} [rad]", datadelphijj);
    distUnfold("jj_m", "m_{jj} [GeV]", datamjj);
    distUnfold("llll_m", "m_{4l} [GeV]", datam4l);
}

