#include"genAna.h"
#include<THStack.h>
#include<TList.h>
int main()
{
    TH1::SetDefaultSumw2();
    TH1D * h_inc_mjj_sr = new TH1D("h_inc_mjj_sr","",20,2e5,2e6);
    TH1D * h_inc_mjj_ct_njn = new TH1D("h_inc_mjj_ct_njn","",20,2e5,2e6);
    TH1D * h_inc_mjj_nct_jn = new TH1D("h_inc_mjj_nct_jn","",20,2e5,2e6);
    TH1D * h_inc_mjj_nct_njn = new TH1D("h_inc_mjj_nct_njn","",20,2e5,2e6);

    TFile * in = TFile::Open("output/stack_out/mjj_stack.root","read");
    THStack* mjj_sr_stack = (THStack*)in->Get("mjj_sr_stack");
    THStack* mjj_ct_njn_stack = (THStack*)in->Get("mjj_ct_njn_stack");
    THStack* mjj_nct_njn_stack = (THStack*)in->Get("mjj_nct_njn_stack");
    THStack* mjj_nct_jn_stack = (THStack*)in->Get("mjj_nct_jn_stack");

    TObjLink *lnksr = mjj_sr_stack->GetHists()->FirstLink();
    while (lnksr) {
        h_inc_mjj_sr->Add((TH1D*)(lnksr->GetObject()));
        lnksr = lnksr->Next();
    }

    TObjLink *lnkct_njn = mjj_ct_njn_stack->GetHists()->FirstLink();
    while (lnkct_njn) {
        h_inc_mjj_ct_njn->Add((TH1D*)(lnkct_njn->GetObject()));
        lnkct_njn = lnkct_njn->Next();
    }

    TObjLink *lnknct_jn = mjj_nct_jn_stack->GetHists()->FirstLink();
    while (lnknct_jn) {
        h_inc_mjj_nct_jn->Add((TH1D*)(lnknct_jn->GetObject()));
        lnknct_jn = lnknct_jn->Next();
    }

    TObjLink *lnknct_njn = mjj_nct_njn_stack->GetHists()->FirstLink();
    while (lnknct_njn) {
        h_inc_mjj_nct_njn->Add((TH1D*)(lnknct_njn->GetObject()));
        lnknct_njn = lnknct_njn->Next();
    }

    TCanvas c1("c1","",1200,800);
        h_inc_mjj_sr->SetMarkerColor(kBlack);
        h_inc_mjj_sr->SetLineColor(kBlack);
        h_inc_mjj_sr->SetFillColor(kBlack);
        h_inc_mjj_sr->SetFillStyle(3017);
        h_inc_mjj_sr->SetAxisRange(0,50e-6,"Y");
        h_inc_mjj_sr->Draw("E2");

        mjj_sr_stack->Draw("hist,same");
        h_inc_mjj_sr->Draw("E2,same");

    c1.SaveAs("plots/mjj_sr_stack.png");

    TCanvas c2("c2","",1200,800);
        h_inc_mjj_ct_njn->SetMarkerColor(kBlack);
        h_inc_mjj_ct_njn->SetLineColor(kBlack);
        h_inc_mjj_ct_njn->SetFillColor(kBlack);
        h_inc_mjj_ct_njn->SetFillStyle(3017);
        h_inc_mjj_ct_njn->SetAxisRange(0,50e-6,"Y");
        h_inc_mjj_ct_njn->Draw("E2");

        mjj_ct_njn_stack->Draw("hist,same");
        h_inc_mjj_ct_njn->Draw("E2,same");

    c2.SaveAs("plots/mjj_ct_njn_stack.png");

    TCanvas c3("c3","",1200,800);
        h_inc_mjj_nct_jn->SetAxisRange(0,50e-6,"Y");
        h_inc_mjj_nct_jn->SetMarkerColor(kBlack);
        h_inc_mjj_nct_jn->SetLineColor(kBlack);
        h_inc_mjj_nct_jn->SetFillColor(kBlack);
        h_inc_mjj_nct_jn->SetFillStyle(3017);
        h_inc_mjj_nct_jn->Draw("E2");

        mjj_nct_jn_stack->Draw("hist, same");
        h_inc_mjj_nct_jn->Draw("E2,same");


    c3.SaveAs("plots/mjj_nct_jn_bkg_stack.png");

    TCanvas c4("c4","",1200,800);

        h_inc_mjj_nct_njn->SetAxisRange(0,50e-6,"Y");
        h_inc_mjj_nct_njn->SetMarkerColor(kBlack);
        h_inc_mjj_nct_njn->SetLineColor(kBlack);
        h_inc_mjj_nct_njn->SetFillColor(kBlack);
        h_inc_mjj_nct_njn->SetFillStyle(3017);
        h_inc_mjj_nct_njn->Draw("E2");

        mjj_nct_njn_stack->Draw("hist, same");
        h_inc_mjj_nct_njn->Draw("E2,same");
        
    c4.SaveAs("plots/mjj_nct_njn_bkg_stack.png");
}