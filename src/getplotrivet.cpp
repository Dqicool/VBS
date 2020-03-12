#include "genAna.h"

void getdphijj(){
    TH1::SetDefaultSumw2();
    TFile* infile = TFile::Open("rivet_routine/Plots/EFT_INT_1E6.hepmc.yoda.root", "read");
    TH1D * h_jj_Dphi = (TH1D*)infile->Get("qidong/jjDphi");
    cout<<(h_jj_Dphi->Integral())<<endl;
    auto nbin = h_jj_Dphi->GetNbinsX();
    auto wbin = h_jj_Dphi->GetBinWidth(1);
    auto xmin = h_jj_Dphi->GetBinLowEdge(1);

    
    auto h_rebin = h_jj_Dphi->Rebin(10);
    
    //cout<<h_rebin_delphijj_cut->Integral()<<endl;
    h_rebin->SetStats(0);
    h_rebin->Draw("");

}

void play(){
    TFile* in1 = TFile::Open("rivet_routine/Plots/SM_EW_1E5.hepmc.yoda.root", "read");
    TFile* in2 = TFile::Open("output/stack_out/jj_true_delphi.root", "read");
    TH1D * h_phi_1 = (TH1D*)in1->Get("qidong/jjDphi");
    TH1D * h_phi_2 = (TH1D*)in2->Get("jj_truthBorn_delta_phi_cut_h");

    TCanvas c1("c1","",2000,2000);
    h_phi_1->SetMarkerStyle(23);
    h_phi_1->Draw();
    h_phi_2->SetMarkerStyle(22);
    h_phi_2->SetLineColor(kRed);
    h_phi_2->Draw("same");
    c1.SaveAs("tmp.png");


}

void play2(){
    TFile* in1 = TFile::Open("rivet_routine/Plots/SM_EW_1E5.hepmc.yoda.root", "read");
    TFile* in2 = TFile::Open("output/stack_out/llll_true_m.root", "read");
    TH1D * h_phi_1 = (TH1D*)in1->Get("qidong/m4l");
    TH1D * h_phi_2 = (TH1D*)in2->Get("llll_truthBorn_m_cut_h");

    TCanvas c1("c1","",1000,1000);
    h_phi_1->SetMarkerStyle(23);
    h_phi_1->SetAxisRange(0,0.06, "Y");
    h_phi_1->SetMarkerColor(kBlue);
    h_phi_1->Draw();
    h_phi_2->SetMarkerStyle(22);
    // h_phi_2->SetLineColor(kRed);
    // h_phi_2->SetAxisRange(0,0.06, "Y");
    // h_phi_2->Draw("");
    c1.SaveAs("tmp2.png");
}
void play3(){
    TFile* in1 = TFile::Open("rivet_routine/Plots/SM_EW_1E5.hepmc.yoda.root", "read");
    TFile* in2 = TFile::Open("output/stack_out/llll_true_m.root", "read");
    TH1D * h_phi_1 = (TH1D*)in1->Get("qidong/m4l");
    TH1D * h_phi_2 = (TH1D*)in2->Get("llll_truthBorn_m_cut_h");

    TCanvas c1("c1","",1000,1000);
    h_phi_1->SetMarkerStyle(23);
    h_phi_1->SetAxisRange(0,0.06, "Y");
    h_phi_1->Draw();
    h_phi_2->SetMarkerStyle(22);
    h_phi_2->SetLineColor(kRed);
    h_phi_2->SetMarkerColor(kRed);
    h_phi_2->SetAxisRange(0,0.06, "Y");
    h_phi_2->Draw("");
    c1.SaveAs("tmp3.png");
}