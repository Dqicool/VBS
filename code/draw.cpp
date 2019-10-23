//#define debug
#include <TCanvas.h>
#include <ROOT/RDataFrame.hxx>

void draw(const char* in_file, const char* out_histo)
{
    //Read files
        ROOT::RDataFrame df("SM4L_Nominal", in_file);
        ROOT::RDataFrame mf("totallumi", in_file);
    //filt to working point
        auto srjnf = df.Filter("SRJN_flag == 1");
        auto crjnf = df.Filter("CRJN_flag == 1");
        auto srctf = df.Filter("SRCT_flag == 1");
        auto crctf = df.Filter("CRCT_flag == 1");
    //get total lumi
    auto sumlumi = mf.Take<double>({"sumlumi"}).GetValue();
    auto lumiscale = 1/sumlumi[0];
    //book histos
        auto h_mjj_srjn = srjnf.Histo1D({"mjj_srjn","",100,2e5,1e6},"jj_m","weight");
        auto h_mjj_crjn = crjnf.Histo1D({"mjj_crjn","",100,2e5,1e6},"jj_m","weight");
        auto h_mjj_srct = srctf.Histo1D({"mjj_srct","",100,2e5,1e6},"jj_m","weight");
        auto h_mjj_crct = srctf.Histo1D({"mjj_crct","",100,2e5,1e6},"jj_m","weight");
            
        h_mjj_crct->Scale(lumiscale);
        h_mjj_crjn->Scale(lumiscale);
        h_mjj_srct->Scale(lumiscale);
        h_mjj_srjn->Scale(lumiscale);
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