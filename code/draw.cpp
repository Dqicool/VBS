//#define debug
#include <TCanvas.h>
#include <ROOT/RDataFrame.hxx>

#define MJJ_X_MIN 0
#define MJJ_X_MAX 2000e3
#define MJJ_N_BIN 1000

#define M4L_X_MIN 0
#define M4L_X_MAX 1000e3
#define M4L_N_BIN 1000

#define PHI_X_MIN -2*TMath::Pi()
#define PHI_X_MAX  2*TMath::Pi()
#define PHI_N_BIN   1000

TH1D getHisto(ROOT::RDataFrame df, const char* filterr, const char* dist, const char* weight, int nbins, double xmin, double xmax)
{
    auto histoname = "h_" + (std::string)dist + "_" + (std::string)filterr;
    auto filteddf = df.Filter(filterr); 
    auto h = filteddf.Histo1D({&histoname[0],"",nbins,xmin,xmax},dist,weight);
    return (*h);
}

void draw(const char* in_file, const char* out_histo)
{
    ROOT::EnableImplicitMT();
    //Read files
        ROOT::RDataFrame df("SM4L_Nominal", in_file);

    //book histos
        TH1::SetDefaultSumw2();

        TH1D h_mjj_cut = getHisto(df, "pass_cut",       "jj_m", "NormWeight", MJJ_N_BIN, MJJ_X_MIN, MJJ_X_MAX);
        TH1D h_mjj_sr  = getHisto(df, "pass_SR",        "jj_m", "NormWeight", MJJ_N_BIN, MJJ_X_MIN, MJJ_X_MAX);
        TH1D h_mjj_njn = getHisto(df, "pass_CT_NJN",    "jj_m", "NormWeight", MJJ_N_BIN, MJJ_X_MIN, MJJ_X_MAX);
        TH1D h_mjj_nct = getHisto(df, "pass_NCT_JN",    "jj_m", "NormWeight", MJJ_N_BIN, MJJ_X_MIN, MJJ_X_MAX);
        TH1D h_mjj_nn  = getHisto(df, "pass_NCT_NJN",   "jj_m", "NormWeight", MJJ_N_BIN, MJJ_X_MIN, MJJ_X_MAX);

        TH1D h_m4l_cut = getHisto(df, "pass_cut",       "llll_m", "NormWeight", M4L_N_BIN, M4L_X_MIN, M4L_X_MAX);
        TH1D h_m4l_sr  = getHisto(df, "pass_SR",        "llll_m", "NormWeight", M4L_N_BIN, M4L_X_MIN, M4L_X_MAX);
        TH1D h_m4l_njn = getHisto(df, "pass_CT_NJN",    "llll_m", "NormWeight", M4L_N_BIN, M4L_X_MIN, M4L_X_MAX);
        TH1D h_m4l_nct = getHisto(df, "pass_NCT_JN",    "llll_m", "NormWeight", M4L_N_BIN, M4L_X_MIN, M4L_X_MAX);
        TH1D h_m4l_nn  = getHisto(df, "pass_NCT_NJN",   "llll_m", "NormWeight", M4L_N_BIN, M4L_X_MIN, M4L_X_MAX);

        TH1D h_phi_cut = getHisto(df, "pass_cut",       "jj_delta_phi", "NormWeight", PHI_N_BIN, PHI_X_MIN, PHI_X_MAX);
        TH1D h_phi_sr  = getHisto(df, "pass_SR",        "jj_delta_phi", "NormWeight", PHI_N_BIN, PHI_X_MIN, PHI_X_MAX);
        TH1D h_phi_njn = getHisto(df, "pass_CT_NJN",    "jj_delta_phi", "NormWeight", PHI_N_BIN, PHI_X_MIN, PHI_X_MAX);
        TH1D h_phi_nct = getHisto(df, "pass_NCT_JN",    "jj_delta_phi", "NormWeight", PHI_N_BIN, PHI_X_MIN, PHI_X_MAX);
        TH1D h_phi_nn  = getHisto(df, "pass_NCT_NJN",   "jj_delta_phi", "NormWeight", PHI_N_BIN, PHI_X_MIN, PHI_X_MAX);

        
    //save
        TFile* out = TFile::Open(out_histo,"recreate");

        h_mjj_cut.Write();
        h_mjj_sr.Write();
        h_mjj_nct.Write();
        h_mjj_njn.Write();
        h_mjj_nn.Write();

        h_m4l_cut.Write();
        h_m4l_sr.Write();
        h_m4l_nct.Write();
        h_m4l_njn.Write();
        h_m4l_nn.Write();

        h_phi_cut.Write();
        h_phi_sr.Write();
        h_phi_nct.Write();
        h_phi_njn.Write();
        h_phi_nn.Write();

        if (df.HasColumn("NormWeight_true")){
            
            TH1D h_true_mjj_cut = getHisto(df, "pass_cut",       "jj_truthBorn_m", "NormWeight_true", MJJ_N_BIN, MJJ_X_MIN, MJJ_X_MAX);
            TH1D h_true_mjj_sr  = getHisto(df, "pass_SR",        "jj_truthBorn_m", "NormWeight_true", MJJ_N_BIN, MJJ_X_MIN, MJJ_X_MAX);
            TH1D h_true_mjj_njn = getHisto(df, "pass_CT_NJN",    "jj_truthBorn_m", "NormWeight_true", MJJ_N_BIN, MJJ_X_MIN, MJJ_X_MAX);
            TH1D h_true_mjj_nct = getHisto(df, "pass_NCT_JN",    "jj_truthBorn_m", "NormWeight_true", MJJ_N_BIN, MJJ_X_MIN, MJJ_X_MAX);
            TH1D h_true_mjj_nn  = getHisto(df, "pass_NCT_NJN",   "jj_truthBorn_m", "NormWeight_true", MJJ_N_BIN, MJJ_X_MIN, MJJ_X_MAX);

            TH1D h_true_m4l_cut = getHisto(df, "pass_cut",       "llll_truthBorn_m", "NormWeight_true", M4L_N_BIN, M4L_X_MIN, M4L_X_MAX);
            TH1D h_true_m4l_sr  = getHisto(df, "pass_SR",        "llll_truthBorn_m", "NormWeight_true", M4L_N_BIN, M4L_X_MIN, M4L_X_MAX);
            TH1D h_true_m4l_njn = getHisto(df, "pass_CT_NJN",    "llll_truthBorn_m", "NormWeight_true", M4L_N_BIN, M4L_X_MIN, M4L_X_MAX);
            TH1D h_true_m4l_nct = getHisto(df, "pass_NCT_JN",    "llll_truthBorn_m", "NormWeight_true", M4L_N_BIN, M4L_X_MIN, M4L_X_MAX);
            TH1D h_true_m4l_nn  = getHisto(df, "pass_NCT_NJN",   "llll_truthBorn_m", "NormWeight_true", M4L_N_BIN, M4L_X_MIN, M4L_X_MAX);

            TH1D h_true_phi_cut = getHisto(df, "pass_cut",       "jj_truthBorn_delta_phi", "NormWeight_true", PHI_N_BIN, PHI_X_MIN, PHI_X_MAX);
            TH1D h_true_phi_sr  = getHisto(df, "pass_SR",        "jj_truthBorn_delta_phi", "NormWeight_true", PHI_N_BIN, PHI_X_MIN, PHI_X_MAX);
            TH1D h_true_phi_njn = getHisto(df, "pass_CT_NJN",    "jj_truthBorn_delta_phi", "NormWeight_true", PHI_N_BIN, PHI_X_MIN, PHI_X_MAX);
            TH1D h_true_phi_nct = getHisto(df, "pass_NCT_JN",    "jj_truthBorn_delta_phi", "NormWeight_true", PHI_N_BIN, PHI_X_MIN, PHI_X_MAX);
            TH1D h_true_phi_nn  = getHisto(df, "pass_NCT_NJN",   "jj_truthBorn_delta_phi", "NormWeight_true", PHI_N_BIN, PHI_X_MIN, PHI_X_MAX);

            h_true_mjj_cut.Write();
            h_true_mjj_sr.Write();
            h_true_mjj_nct.Write();
            h_true_mjj_njn.Write();
            h_true_mjj_nn.Write();

            h_true_m4l_cut.Write();
            h_true_m4l_sr.Write();
            h_true_m4l_nct.Write();
            h_true_m4l_njn.Write();
            h_true_m4l_nn.Write();

            h_true_phi_cut.Write();
            h_true_phi_sr.Write();
            h_true_phi_nct.Write();
            h_true_phi_njn.Write();
            h_true_phi_nn.Write();
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