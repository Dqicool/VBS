#include"genAna.h"
#include<THStack.h>
int main()
{
    TFile * in = TFile::Open("output/stack_out/mjj_stack.root","read");
    THStack* mjj_crct_stack = (THStack*)in->Get("mjj_crct_stack");
    THStack* mjj_crjn_stack = (THStack*)in->Get("mjj_crjn_stack");
    THStack* mjj_srct_stack = (THStack*)in->Get("mjj_srct_stack");
    THStack* mjj_srjn_stack = (THStack*)in->Get("mjj_srjn_stack");

    TFile *inn = TFile::Open("output/histo_out/inc/364250.Sherpa_222_NNPDF30NNLO_llll.root");
    TH1D * h_mjj_crct = (TH1D* )inn->Get("h_mjj_crct");
    TH1D * h_mjj_crjn = (TH1D* )inn->Get("h_mjj_crjn");
    TH1D * h_mjj_srct = (TH1D* )inn->Get("h_mjj_srct");
    TH1D * h_mjj_srjn = (TH1D* )inn->Get("h_mjj_srjn");

    TCanvas c1("c1","",1200,800);
        h_mjj_crct->SetMarkerColor(kBlack);
        h_mjj_crct->SetLineColor(kBlack);
        h_mjj_crct->Draw("same");
        mjj_crct_stack->Draw("same");

    c1.SaveAs("plots/mjj_crct_bkg_stack.png");

    TCanvas c2("c2","",1200,800);
        h_mjj_crjn->SetMarkerColor(kBlack);
        h_mjj_crjn->SetLineColor(kBlack);
        h_mjj_crjn->Draw();
        mjj_crjn_stack->Draw("same");

    c2.SaveAs("plots/mjj_crnj_bkg_stack.png");

    TCanvas c3("c3","",1200,800);
        h_mjj_srct->SetMarkerColor(kBlack);
        h_mjj_srct->SetLineColor(kBlack);
        h_mjj_srct->Draw();
        
        mjj_srct_stack->Draw("same");

    c3.SaveAs("plots/mjj_srct_bkg_stack.png");

    TCanvas c4("c4","",1200,800);
        h_mjj_srjn->SetMarkerColor(kBlack);
        h_mjj_srjn->SetLineColor(kBlack);
        h_mjj_srjn->Draw();
        mjj_srjn_stack->Draw("same");
        
    c4.SaveAs("plots/mjj_srjn_bkg_stack.png");
}