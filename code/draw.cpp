//#define debug
#include <TCanvas.h>
#include <ROOT/RDataFrame.hxx>

void draw(const char* in_file, const char* out_histo)
{
    ROOT::EnableImplicitMT();
    //Read files
        ROOT::RDataFrame df("SM4L_Nominal", in_file);
    //filt to working point
        auto srjnf = df.Filter("SRJN_flag == 1");
        auto crjnf = df.Filter("CRJN_flag == 1");
        auto srctf = df.Filter("SRCT_flag == 1");
        auto crctf = df.Filter("CRCT_flag == 1");

    //book histos
        auto h_mjj_srjn = srjnf.Histo1D({"h_mjj_srjn","",20,2e5,2e6},"jj_m","NormWeight");
        auto h_mjj_crjn = crjnf.Histo1D({"h_mjj_crjn","",20,2e5,2e6},"jj_m","NormWeight");
        auto h_mjj_srct = srctf.Histo1D({"h_mjj_srct","",20,2e5,2e6},"jj_m","NormWeight");
        auto h_mjj_crct = crctf.Histo1D({"h_mjj_crct","",20,2e5,2e6},"jj_m","NormWeight");

    //save
        TFile* out = TFile::Open(out_histo,"recreate");
        h_mjj_srjn->Write();
        h_mjj_srct->Write();
        h_mjj_crjn->Write();
        h_mjj_crct->Write();
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
    const char* in_file = "output/analyse_out/inc/364250.Sherpa_222_NNPDF30NNLO_llll.root";
    const char* out_histo = "output/histo_out/364250.Sherpa_222_NNPDF30NNLO_llll.root";
    draw(in_file,out_histo);
}
#endif