#include"genAna.h"
#include<THStack.h>
int main()
{
    TFile * in = TFile::Open("output/stack_out/mjj_stack.root","read");
    THStack* mjj_crct_stack = (THStack*)in->Get("mjj_crct_stack");
    THStack* mjj_crjn_stack = (THStack*)in->Get("mjj_crjn_stack");
    THStack* mjj_srct_stack = (THStack*)in->Get("mjj_srct_stack");
    THStack* mjj_srjn_stack = (THStack*)in->Get("mjj_srjn_stack");

    TCanvas c1("c1","",1200,800);

        mjj_crct_stack->Draw("");
        mjj_crct_stack->GetHistogram()->Draw("E, same");

    c1.SaveAs("plots/mjj_crct_bkg_stack.png");

    TCanvas c2("c2","",1200,800);

        mjj_crjn_stack->Draw("");
        mjj_crct_stack->GetHistogram()->Draw("E, same");

    c2.SaveAs("plots/mjj_crnj_bkg_stack.png");

    TCanvas c3("c3","",1200,800);

        mjj_srct_stack->Draw("");
        mjj_crct_stack->GetHistogram()->Draw("E, same");

    c3.SaveAs("plots/mjj_srct_bkg_stack.png");

    TCanvas c4("c4","",1200,800);

        mjj_srjn_stack->Draw("");
        mjj_crct_stack->GetHistogram()->Draw("E, same");
        
    c4.SaveAs("plots/mjj_srjn_bkg_stack.png");
}