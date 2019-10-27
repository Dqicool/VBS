#include"genAna.h"
#include <THStack.h>
//#define debug
void stack(const char* in_file, const char* out_file, Color_t col)
{
    TH1::SetDefaultSumw2();
    TFile * out = TFile::Open(out_file, "read");

    THStack* mjj_sr_stack = (THStack*)out->Get("mjj_sr_stack");
    THStack* mjj_ct_njn_stack = (THStack*)out->Get("mjj_ct_njn_stack");
    THStack* mjj_nct_jn_stack = (THStack*)out->Get("mjj_nct_jn_stack");
    THStack* mjj_nct_njn_stack = (THStack*)out->Get("mjj_nct_njn_stack");
    
    TFile* in = TFile::Open(in_file, "read");

    TH1D * h_mjj_sr = (TH1D* )in->Get("h_mjj_sr");
    TH1D * h_mjj_ct_njn = (TH1D* )in->Get("h_mjj_ct_njn");
    TH1D * h_mjj_nct_jn = (TH1D* )in->Get("h_mjj_nct_jn");
    TH1D * h_mjj_nct_njn = (TH1D* )in->Get("h_mjj_nct_njn");


    //cout<<col<<endl;

    h_mjj_sr->SetFillColor(col);
    h_mjj_nct_njn->SetFillColor(col);
    h_mjj_nct_jn->SetFillColor(col);
    h_mjj_ct_njn->SetFillColor(col);

    h_mjj_sr->SetLineColor(col);
    h_mjj_nct_njn->SetLineColor(col);
    h_mjj_nct_jn->SetLineColor(col);
    h_mjj_ct_njn->SetLineColor(col);

    h_mjj_sr->SetMarkerColor(col);
    h_mjj_nct_njn->SetMarkerColor(col);
    h_mjj_nct_jn->SetMarkerColor(col);
    h_mjj_ct_njn->SetMarkerColor(col);
    
    mjj_sr_stack->Add(h_mjj_sr);
    mjj_ct_njn_stack->Add(h_mjj_ct_njn);
    mjj_nct_jn_stack->Add(h_mjj_nct_jn);
    mjj_nct_njn_stack->Add(h_mjj_nct_njn);


    out->ReOpen("update");
    out->Delete("*;*");
    
    mjj_sr_stack->Write();
    mjj_ct_njn_stack->Write();
    mjj_nct_jn_stack->Write();
    mjj_nct_njn_stack->Write();


    in->Close();
    out->Close();
    
}
#ifndef debug
int main(int argc, char** argv)
{
    const char* in_file = argv[1];
    const char* out_file = argv[2];
    auto col = str2Color(argv[3]);
    stack(in_file, out_file, col);
}
#else
int main()
{
    const char* in_file = "output/histo_out/inc/364250.Sherpa_222_NNPDF30NNLO_llll.root";
    const char* out_file = "debug.root";
    stack(in_file, out_file);
}
#endif
        