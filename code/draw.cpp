//saving histogram as 

//#define debug
#include <TCanvas.h>
#include <ROOT/RDataFrame.hxx>

void draw(const char* in_file, const char* out_histo)
{
    ROOT::EnableImplicitMT();
    //Read files
        ROOT::RDataFrame df("SM4L_Nominal", in_file);
    //filt to working point
        auto f_sr = df.Filter("pass_SR == 1");
        auto f_ct_njn = df.Filter("pass_CT_NJN == 1");
        auto f_nct_jn = df.Filter("pass_NCT_JN == 1");
        auto f_nct_njn = df.Filter("pass_NCT_NJN == 1");

    //book histos
        TH1::SetDefaultSumw2();
        auto h_mjj_sr = f_sr.Histo1D({"h_mjj_sr","",20,2e5,2e6},"jj_m","NormWeight");
        auto h_mjj_ct_njn = f_ct_njn.Histo1D({"h_mjj_ct_njn","",20,2e5,2e6},"jj_m","NormWeight");
        auto h_mjj_nct_jn = f_nct_jn.Histo1D({"h_mjj_nct_jn","",20,2e5,2e6},"jj_m","NormWeight");
        auto h_mjj_nct_njn = f_nct_njn.Histo1D({"h_mjj_nct_njn","",20,2e5,2e6},"jj_m","NormWeight");
        h_mjj_sr->Scale(1.0 / 3.0);
        h_mjj_ct_njn->Scale(1.0/3.0);
        h_mjj_nct_jn->Scale(1.0/3.0);
        h_mjj_nct_njn->Scale(1.0/3.0);
    //save
        TFile* out = TFile::Open(out_histo,"recreate");
        h_mjj_sr->Write();
        h_mjj_nct_jn->Write();
        h_mjj_ct_njn->Write();
        h_mjj_nct_njn->Write();
        out->Close();
}
#ifndef debug
int main(int argc, char** argv){
    const char* in_file = argv[1];
    const char* out_histo = argv[2];

    draw(in_file,out_histo);
}
#else
int main(){
    const char* in_file = "output/analyse_out/999_all/364250.Sherpa_222_NNPDF30NNLO_llll.root";
    const char* out_histo = "output/histo_out/999_all/364250.Sherpa_222_NNPDF30NNLO_llll.root";
    draw(in_file,out_histo);
}
#endif