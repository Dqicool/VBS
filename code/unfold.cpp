#include "genAna.h"
#include "histoProp.h"
#include <RooUnfoldResponse.h>
#include <RooUnfoldBayes.h>
#include <RooUnfoldErrors.h>
#include <cstdlib>



//#define debug

void distUnfold(char* dist, char* dist_true, int nbins, double xmin, double xmax)
{   
    //load files in chain
        TH1::SetDefaultSumw2();
        gStyle->SetPaintTextFormat("1.3f");
        TChain chain("SM4L_Nominal");
        chain.Add("output/analyse_out/999_all/364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.root");
#ifndef debug
        chain.Add("output/analyse_out/999_all/344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root");
        //chain.Add("output/analyse_out/999_all/344295.Sherpa_Zee_4lMassFilter40GeV8GeV.root");
        //chain.Add("output/analyse_out/999_all/344296.Sherpa_Zmumu_4lMassFilter40GeV8GeV.root");
        //chain.Add("output/analyse_out/999_all/344297.Sherpa_Zee_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root");
        //chain.Add("output/analyse_out/999_all/344298.Sherpa_Zmumu_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root");
        chain.Add("output/analyse_out/999_all/345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root");
        chain.Add("output/analyse_out/999_all/345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root");
        chain.Add("output/analyse_out/999_all/345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root");
        chain.Add("output/analyse_out/999_all/345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root");
        chain.Add("output/analyse_out/999_all/345706.Sherpa_222_NNPDF30NNLO_ggllll_130M4l.root");
        chain.Add("output/analyse_out/999_all/345708.Sherpa_222_NNPDF30NNLO_ggllllNoHiggs_0M4l130.root");
        chain.Add("output/analyse_out/999_all/346340.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_allhad.root");
        chain.Add("output/analyse_out/999_all/346341.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_semilep.root");
        chain.Add("output/analyse_out/999_all/346342.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_dilep.root");
        //chain.Add("output/analyse_out/999_all/361601.PowhegPy8EG_WZlvll_mll4.root");
        chain.Add("output/analyse_out/999_all/364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6.root");
        chain.Add("output/analyse_out/999_all/364245.Sherpa_222_NNPDF30NNLO_WZZ_5l1v_EW6.root");
        chain.Add("output/analyse_out/999_all/364247.Sherpa_222_NNPDF30NNLO_ZZZ_6l0v_EW6.root");
        chain.Add("output/analyse_out/999_all/364248.Sherpa_222_NNPDF30NNLO_ZZZ_4l2v_EW6.root");
        chain.Add("output/analyse_out/999_all/364250.Sherpa_222_NNPDF30NNLO_llll.root");
        chain.Add("output/analyse_out/999_all/410142.Sherpa_NNPDF30NNLO_ttll_mll5.root");
        //chain.Add("output/analyse_out/999_all/410472.PhPy8EG_A14_ttbar_hdamp258p75_dil.root");
#endif
    //declare histos demands unfold
        RooUnfoldResponse resp(nbins, xmin, xmax);
    //declare variable pointer in tree
        float x_measured=0;
        float x_true = 0;
        double weight = 0;
        double weight_true = 0;
        bool pass_cut = 0;
        bool pass_true_cut = 0;

    //set branch
        chain.SetBranchAddress("pass_cut", &pass_cut);
        chain.SetBranchAddress("pass_truthBorn_cut", &pass_true_cut);
        chain.SetBranchAddress(dist,&x_measured);
        chain.SetBranchAddress(dist_true,&x_true);
        chain.SetBranchAddress("NormWeight", &weight);
        chain.SetBranchAddress("NormWeight_true", &weight_true);
    //loop over entries
        auto n_entry = chain.GetEntries();
        long nfill=0;
        long nfake=0;
        long nmiss=0;
        for( Long64_t i = 0; i<(int)(n_entry); i++)
        {
            chain.GetEntry(i);
            
            if(pass_cut && pass_true_cut){
                resp.Fill(x_measured, x_true, weight*LUMI/3.0);
                nfill++;
            }
            else if(pass_cut && (pass_true_cut==0)){
                resp.Fake(x_measured, weight*LUMI/3.0);
                nfake++;
            }
            else if((pass_cut==0) && pass_true_cut){
                resp.Miss(x_true, weight_true*LUMI/3.0);
                nmiss++;
            }

            if (i % (Long64_t)(n_entry/10) == 0){
                cout<<i/(Long64_t)(n_entry/10)<<"0%"<<endl;
                cout<<"Fill: "<<nfill<<"\t\t"<<"Fake: "<<nfake<<"\t\t"<< "Miss: "<<nmiss<<endl; 
            }
        }
        TH2D* h_resp = (TH2D*)resp.Hresponse();
        auto m_resp = resp.Mresponse();
        auto h_meas = resp.Hmeasured();
        auto h_true = resp.Htruth();
        auto h_fake = resp.Hfakes();


        cout<<"Purity: \t"<<endl;
        for(int i=1; i<=nbins; i++){
            cout<<i<<":\t"<<h_resp->GetBinContent(i,i)<<"\t\t"<<h_resp->Integral(i,i,0,nbins)<<"\t\t"<<
            h_resp->GetBinContent(i,i)/h_resp->Integral(1, nbins,i,i)<<endl;
        }

    //unfold
        RooUnfoldBayes unfold(&resp, h_meas, 2);
        auto cov = unfold.GetMeasuredCov();
        TH1D* h_unfold= (TH1D*) unfold.Hreco();
        unfold.PrintTable (std::cout, h_true);
        
    //save
        string pic_name = "plots/unfold/" + (string)(const char*)dist;
        auto unfold_name = pic_name + "_unfold.png";
        auto resp_name = pic_name + "_resp.png";
        auto resph_name = pic_name + "_resph.png";
        TCanvas *c1 = new TCanvas("c1","",1200,800);

            h_unfold->SetLineColor(kBlue);
            h_unfold->GetXaxis()->SetTitle(dist);
            h_unfold->Draw("E");
            h_meas->SetLineColor(kRed);
            h_meas->Draw("same HISTO ");
            h_true->SetLineColor(kGreen);
            h_true->Draw("same HISTO");
            h_fake->SetLineColor(kBlack);
            h_fake->Draw("same HISTO");
            c1->SaveAs((&unfold_name[0]));
        
        auto* c2 = new TCanvas("c2","",2000,2000);
            auto tmp = new TH2D(m_resp);
            //tmp->Scale(1+ nmiss/nfill);
            tmp->SetStats(0);
            tmp->Draw("COLZ");
            tmp->Draw("TEXT SAME");
            c2->SaveAs(&resp_name[0]);

        auto* c3 = new TCanvas("c3","",2000,2000);
            h_resp->SetStats(0);
            h_resp->Draw("COLZ");
            h_resp->Draw("TEXT SAME");
            c3->SaveAs(&resph_name[0]);

}

#ifndef debug

int main(int argc, char** argv){
    auto dist = argv[1];
    auto dist_true = argv[2];
    int nbin = atoi(argv[3]);
    float xmin = atof(argv[4]);
    float xmax = atof(argv[5]);
    distUnfold(dist, dist_true, nbin, xmin, xmax);
}
#else

int main(){
    distUnfold("llll_m", "llll_truthBorn_m", 9, 100000, 1000000);
}
#endif
