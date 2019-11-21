#include "analambda.h"
#define LUMI 1
#define ORIII
void cutflow(const char* infile, const char* outfile)
{
    std::vector<double> n_evt_survive{};
    ROOT::RDataFrame df("SM4L_Nominal", infile);

    df0

    auto h_cutflow = new TH1D("cutflow", "", n_evt_survive.size(), 0, n_evt_survive.size());
    std::vector<const char*> binlabels{"original", "j1_pt > 40 && j2_pt > 30", "jj_m > 200e3", "jj_product_y < 0", "|jj_delta_y| > 2", "pt_balance < 0.2", "Z-20 < z1_m < Z+20", "15 < z2_m < Z+20"};

    for(uint i=0; i < n_evt_survive.size(); i++){
        h_cutflow->SetBinContent(i+1, n_evt_survive[i]);
        h_cutflow->GetXaxis()->SetBinLabel(i+1, binlabels[i]);
    }
    
    auto out = TFile::Open(outfile, "recreate");
    //h_cutflow->SetAxisRange(0,1,"Y");
    
    h_cutflow->Write();
    out->Close();
}

int main(int argc, char** argv)
{
    char* infile = argv[1];
    char* outfile = argv[2];

    cutflow(infile, outfile);
}