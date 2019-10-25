#include "genAna.h"

#include <RooUnfoldResponse.h>
#include <RooUnfoldBayes.h>
#include <RooUnfoldErrors.h>

void bayesUnfold(const char* in_tree_file, const char* out_histo)
{   
    TFile* treeFile = TFile::Open(in_tree_file);
    TTree* tree  = (TTree*)treeFile->Get("SM4L_Nominal");
    //declare histos demands unfold
    RooUnfoldResponse mjj_resp (10, 0., 2000.0);
    TH1D* h_mjj = new TH1D("h_mjj","h_mjj",10,0.,2000.);
    TH1D* h_mjj_true = new TH1D("h_mjj_true","h_mjj",10,0.,2000.);
    //declare variable pointer in tree
    double mjj=0;
    double mjj_true=0;
    double weights = 0;
    double fid_weights = 0;
    bool sr_flag = 0;
    bool cr_flag = 0;
    //set branch
    tree->SetBranchAddress("SR_flag", &sr_flag);
    tree->SetBranchAddress("CR_flag", &cr_flag);
    tree->SetBranchAddress("dijet_mjj",&mjj);
    tree->SetBranchAddress("dijet_mjj_truthBorn",&mjj_true);
    tree->SetBranchAddress("whights", &weights);
    tree->SetBranchAddress("fid_weights", &fid_weights);
    //loop over entries
    auto n_entry = tree->GetEntries();
    for( Long64_t i = 0; i<(int)(0.75*n_entry); i++)
    {
        tree->GetEntry(i);
        //if (sr_flag)
        {
            if(mjj>0 && mjj_true>0)
            {
                mjj_resp.Fill(mjj,mjj_true,weights);
            }
            else if(mjj_true>0 && mjj < 0)
            {
                mjj_resp.Miss(mjj_true);
            }
            else if (mjj_true>0 && mjj<0)
            {

            }
        }
    }
    for( Long64_t i = (Long64_t)(0.75*n_entry); i<n_entry; i++)
    {
        tree->GetEntry(i);
        //if (sr_flag)
        {
            if(mjj>0 && mjj_true>0)
            {
                h_mjj->Fill(mjj);
                h_mjj_true->Fill(mjj_true);
            }
            else if(mjj_true>0)
            {
                h_mjj_true->Fill(mjj_true);
            }
        }
    }

    RooUnfoldBayes mjj_unfold(&mjj_resp, h_mjj, 4);
    auto cov = mjj_unfold.GetMeasuredCov();
    TH1D* h_mjj_unfold= (TH1D*) mjj_unfold.Hreco();
    mjj_unfold.PrintTable (std::cout, h_mjj_true);
    TFile * out = TFile::Open(out_histo, "recreate");
    h_mjj->Write();
    h_mjj_true->Write();
    h_mjj_unfold->Write();
    cov.Write();
    

    //    RooUnfoldErrors errors(1, &mjj_unfold,h_mjj_true);
    //    auto chi2 = (TTree *)errors.Chi2();
    //    chi2->Write();
    out->Close();

    TCanvas *c1 = new TCanvas("c1","",1200,800);
        h_mjj_unfold->SetLineColor(kBlue);
        h_mjj_unfold->GetXaxis()->SetTitle("mjj");
        h_mjj_unfold->Draw();
        h_mjj->SetLineColor(kRed);
        h_mjj->Draw("same");
        h_mjj_true->SetLineColor(kGreen);
        h_mjj_true->Draw("same");
	c1->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/3G_test_mjj_unfold.png");
    TH2D* h_mjj_resp = mjj_resp.HresponseNoOverflow();
    auto* c2 = new TCanvas("c2","",1200,1200);
        h_mjj_resp->SetStats(0);
        h_mjj_resp->Draw("colz");
        c1->Draw();
    c2->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/3G_test_response.png");
    auto c3 = new TCanvas("c3","",1200,800);
        (cov).Print();
    c3->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/3G_test_cov.png");
}

int main(){
    bayesUnfold("/mnt/MainShare/Projects/Qichen/VBS/output/3G_baseline_w_SR_CR.root",
                "/mnt/MainShare/Projects/Qichen/VBS/output/3G_unfold_hh.root");
}