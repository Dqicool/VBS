#include "genAna.h"
#include "histoProp.h"
#include <RooUnfoldResponse.h>
#include <RooUnfoldBayes.h>
#include <RooUnfoldErrors.h>

void mjjUnfold()
{   
    //load files in chain
        TH1::SetDefaultSumw2();
        TChain chain("SM4L_Nominal");
        chain.Add("output/analyse_out/999_all/364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.root");
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
    //declare histos demands unfold
        RooUnfoldResponse mjj_resp (MJJNBIN, MJJXMIN, MJJXMAX);
        TH1D* h_mjj = new TH1D("h_mjj","h_mjj",MJJNBIN,MJJXMIN,MJJXMAX);
        TH1D* h_mjj_true = new TH1D("h_mjj_true","h_mjj",MJJNBIN,MJJXMIN,MJJXMAX);
    //declare variable pointer in tree
        float mjj=0;
        float mjj_true = 0;
        double weight = 0;
        double weight_true = 0;
        bool pass_cut = 0;
        bool pass_true_cut = 0;

    //set branch
        chain.SetBranchAddress("pass_cut", &pass_cut);
        chain.SetBranchAddress("pass_truthBorn_cut", &pass_true_cut);
        chain.SetBranchAddress("jj_m",&mjj);
        chain.SetBranchAddress("jj_truthBorn_m",&mjj_true);
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
                mjj_resp.Fill(mjj, mjj_true, weight*LUMI/3.0);
                nfill++;
            }
            else if(pass_cut && (pass_true_cut==0)){
                mjj_resp.Fake(mjj, weight*LUMI/3.0);
                nfake++;
            }
            else if((pass_cut==0) && pass_true_cut){
                mjj_resp.Miss(mjj_true, weight_true*LUMI/3.0);
                nmiss++;
            }

            if(pass_cut)  {h_mjj->Fill(mjj, weight*LUMI/3.0);}
            if(pass_true_cut){h_mjj_true->Fill(mjj_true, weight_true*LUMI/3.0);};

            if (i % (Long64_t)(n_entry/100) == 0){
                cout<<i/(Long64_t)(n_entry/100)<<'%'<<endl;
                cout<<"Fill: "<<nfill<<"\t\t"<<"Fake: "<<nfake<<"\t\t"<< "Miss: "<<nmiss<<endl; 
            }
        }
    //unfold
        RooUnfoldBayes mjj_unfold(&mjj_resp, h_mjj, 4);
        auto cov = mjj_unfold.GetMeasuredCov();
        TH1D* h_mjj_unfold= (TH1D*) mjj_unfold.Hreco();
        mjj_unfold.PrintTable (std::cout, h_mjj_true);
    //save
        TCanvas *c1 = new TCanvas("c1","",1200,800);
            h_mjj_unfold->SetLineColor(kBlue);
            h_mjj_unfold->GetXaxis()->SetTitle("mjj");
            h_mjj_unfold->Draw();
            h_mjj->SetLineColor(kRed);
            h_mjj->Draw("same");
            h_mjj_true->SetLineColor(kGreen);
            h_mjj_true->Draw("same");
        c1->SaveAs("plots/unfold/test_mjj_unfold.png");
        TH2D* h_mjj_resp = mjj_resp.HresponseNoOverflow();
        auto* c2 = new TCanvas("c2","",1200,1200);
            h_mjj_resp->SetStats(0);
            h_mjj_resp->Draw("colz");
            c2->Draw();
        c2->SaveAs("plots/unfold/test_response.png");
}

int main(){
    mjjUnfold();
}
