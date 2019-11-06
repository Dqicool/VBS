//saving histogram as 
#include"histoProp.h"
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
        auto h_mjj_sr = f_sr.Histo1D({"h_mjj_sr","",MJJNBIN,MJJXMIN,MJJXMAX},"jj_m","NormWeight");
        auto h_mjj_ct_njn = f_ct_njn.Histo1D({"h_mjj_ct_njn","",MJJNBIN,MJJXMIN,MJJXMAX},"jj_m","NormWeight");
        auto h_mjj_nct_jn = f_nct_jn.Histo1D({"h_mjj_nct_jn","",MJJNBIN,MJJXMIN,MJJXMAX},"jj_m","NormWeight");
        auto h_mjj_nct_njn = f_nct_njn.Histo1D({"h_mjj_nct_njn","",MJJNBIN,MJJXMIN,MJJXMAX},"jj_m","NormWeight");

        auto h_m4l_sr = f_sr.Histo1D({"h_m4l_sr","",M4LNBIN,M4LXMIN,M4LXMAX},"llll_m","NormWeight");
        auto h_m4l_ct_njn = f_ct_njn.Histo1D({"h_m4l_ct_njn","",M4LNBIN,M4LXMIN,M4LXMAX},"llll_m","NormWeight");
        auto h_m4l_nct_jn = f_nct_jn.Histo1D({"h_m4l_nct_jn","",M4LNBIN,M4LXMIN,M4LXMAX},"llll_m","NormWeight");
        auto h_m4l_nct_njn = f_nct_njn.Histo1D({"h_m4l_nct_njn","",M4LNBIN,M4LXMIN,M4LXMAX},"llll_m","NormWeight");

        h_mjj_sr->Scale(LUMI / 3.0);
        h_mjj_ct_njn->Scale(LUMI/3.0);
        h_mjj_nct_jn->Scale(LUMI/3.0);
        h_mjj_nct_njn->Scale(LUMI/3.0);
        
        h_m4l_sr->Scale(LUMI / 3.0);
        h_m4l_ct_njn->Scale(LUMI/3.0);
        h_m4l_nct_jn->Scale(LUMI/3.0);
        h_m4l_nct_njn->Scale(LUMI/3.0);

        
    //save
        TFile* out = TFile::Open(out_histo,"recreate");

        h_mjj_sr->Write();
        h_mjj_nct_jn->Write();
        h_mjj_ct_njn->Write();
        h_mjj_nct_njn->Write();

        h_m4l_sr->Write();
        h_m4l_nct_jn->Write();
        h_m4l_ct_njn->Write();
        h_m4l_nct_njn->Write();

        if (df.HasColumn("NormWeight_true")){

            auto f_true_sr = df.Filter("pass_truthBorn_SR == 1");
            auto f_true_ct_njn = df.Filter("pass_truthBorn_CT_NJN == 1");
            auto f_true_nct_jn = df.Filter("pass_truthBorn_NCT_JN == 1");
            auto f_true_nct_njn = df.Filter("pass_truthBorn_NCT_NJN == 1");

            auto h_true_mjj_sr = f_true_sr.Histo1D({"h_true_mjj_sr","",MJJNBIN,MJJXMIN,MJJXMAX},"jj_m","NormWeight_true");
            auto h_true_mjj_ct_njn = f_true_ct_njn.Histo1D({"h_true_mjj_ct_njn","",MJJNBIN,MJJXMIN,MJJXMAX},"jj_m","NormWeight_true");
            auto h_true_mjj_nct_jn = f_true_nct_jn.Histo1D({"h_true_mjj_nct_jn","",MJJNBIN,MJJXMIN,MJJXMAX},"jj_m","NormWeight_true");
            auto h_true_mjj_nct_njn = f_true_nct_njn.Histo1D({"h_true_mjj_nct_njn","",MJJNBIN,MJJXMIN,MJJXMAX},"jj_m","NormWeight_true");

            auto h_true_m4l_sr = f_sr.Histo1D({"h_true_m4l_sr","",M4LNBIN,M4LXMIN,M4LXMAX},"llll_m","NormWeight");
            auto h_true_m4l_ct_njn = f_ct_njn.Histo1D({"h_true_m4l_ct_njn","",M4LNBIN,M4LXMIN,M4LXMAX},"llll_m","NormWeight");
            auto h_true_m4l_nct_jn = f_nct_jn.Histo1D({"h_true_m4l_nct_jn","",M4LNBIN,M4LXMIN,M4LXMAX},"llll_m","NormWeight");
            auto h_true_m4l_nct_njn = f_nct_njn.Histo1D({"h_true_m4l_nct_njn","",M4LNBIN,M4LXMIN,M4LXMAX},"llll_m","NormWeight");

            h_true_mjj_sr->Scale(LUMI / 3.0);
            h_true_mjj_ct_njn->Scale(LUMI/3.0);
            h_true_mjj_nct_jn->Scale(LUMI/3.0);
            h_true_mjj_nct_njn->Scale(LUMI/3.0);

            h_true_m4l_sr->Scale(LUMI / 3.0);
            h_true_m4l_ct_njn->Scale(LUMI/3.0);
            h_true_m4l_nct_jn->Scale(LUMI/3.0);
            h_true_m4l_nct_njn->Scale(LUMI/3.0);

            h_true_mjj_sr->Write();
            h_true_mjj_nct_jn->Write();
            h_true_mjj_ct_njn->Write();
            h_true_mjj_nct_njn->Write();

            h_true_m4l_sr->Write();
            h_true_m4l_nct_jn->Write();
            h_true_m4l_ct_njn->Write();
            h_true_m4l_nct_njn->Write();
        }

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