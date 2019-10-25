#include"genAna.h"
#include <THStack.h>
//#define debug
void stack(const char* in_file, const char* out_file, Color_t col)
{
    TFile * out = TFile::Open(out_file, "read");

    THStack* mjj_crct_stack = (THStack*)out->Get("mjj_crct_stack");
    THStack* mjj_crjn_stack = (THStack*)out->Get("mjj_crjn_stack");
    THStack* mjj_srct_stack = (THStack*)out->Get("mjj_srct_stack");
    THStack* mjj_srjn_stack = (THStack*)out->Get("mjj_srjn_stack");
    
    TFile* in = TFile::Open(in_file, "read");
    TH1D * h_mjj_crct = (TH1D* )in->Get("h_mjj_crct");
    TH1D * h_mjj_crjn = (TH1D* )in->Get("h_mjj_crjn");
    TH1D * h_mjj_srct = (TH1D* )in->Get("h_mjj_srct");
    TH1D * h_mjj_srjn = (TH1D* )in->Get("h_mjj_srjn");
    //cout<<col<<endl;
    h_mjj_crct->SetLineColor(col);
    h_mjj_crjn->SetLineColor(col);
    h_mjj_srct->SetLineColor(col);
    h_mjj_srjn->SetLineColor(col);

    h_mjj_crct->SetMarkerColor(col);
    h_mjj_crjn->SetMarkerColor(col);
    h_mjj_srct->SetMarkerColor(col);
    h_mjj_srjn->SetMarkerColor(col);

    h_mjj_crct->SetFillColor(col);
    h_mjj_crjn->SetFillColor(col);
    h_mjj_srct->SetFillColor(col);
    h_mjj_crjn->SetFillColor(col);
    
    mjj_crct_stack->Add(h_mjj_crct);
    mjj_crjn_stack->Add(h_mjj_crjn);
    mjj_srct_stack->Add(h_mjj_srct);
    mjj_srjn_stack->Add(h_mjj_srjn);
    out->ReOpen("update");
    out->Delete("*;*");
    mjj_crct_stack->Write();
    mjj_crjn_stack->Write();
    mjj_srct_stack->Write();
    mjj_srjn_stack->Write();
    in->Close();
    out->Close();
    
}
#ifndef debug
int main(int argc, char** argv)
{
    const char* in_file = argv[1];
    const char* out_file = argv[2];
    auto col = str2Color(argv[3]);
    stack(in_file, out_file,col);
}
#else
int main()
{
    const char* in_file = "output/histo_out/inc/364250.Sherpa_222_NNPDF30NNLO_llll.root";
    const char* out_file = "debug.root";
    stack(in_file, out_file);
}
#endif
        