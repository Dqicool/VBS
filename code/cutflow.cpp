#include "analambda.h"

bool lptsel(std::vector<int> z1_index, std::vector<int> z2_index, std::vector<double> lepton_pt){
    std::vector<double> l1l2l3l4_pt{lepton_pt[z1_index[0]], lepton_pt[z1_index[1]], lepton_pt[z2_index[0]], lepton_pt[z2_index[1]]};
    std::sort(l1l2l3l4_pt.begin(), l1l2l3l4_pt.end());
    return l1l2l3l4_pt[3] > 20e3 && l1l2l3l4_pt[2] > 20e3 && l1l2l3l4_pt[1] > 10e3;
}
void cutflow(const char* infile, const char* outfile)
{
    ROOT::EnableImplicitMT(24);
    std::vector<double> n_evt_survive{};
    ROOT::RDataFrame df("SM4L_Nominal", infile);

    auto df0 = df.Filter("jet_n>=2 && lepton_n >= 4");
    auto df1 = df0.Filter("jet_pass_n >= 2");
    auto df2 = df1.Filter("jj_m > 300e3");
    auto df3 = df2.Filter("(jj_delta_y > 2 || jj_delta_y < -2) && jj_delta_y > -999");
    auto df4 = df3.Filter("lepton_pass_n >= 4");
    auto df5 = df4.Filter("z1_energy > 0 && z2_energy > 0");
    auto df6 = df5.Filter("z1_m > 66e3 && z1_m < 116e3 && z2_m > 66e3 && z2_m < 116e3");
    auto df7 = df6.Filter(lptsel, {"z1_index", "z2_index", "lepton_pass_pt"});

    n_evt_survive.push_back(df0.Sum("NormWeight").GetValue());
    n_evt_survive.push_back(df1.Sum("NormWeight").GetValue());
    n_evt_survive.push_back(df2.Sum("NormWeight").GetValue());
    n_evt_survive.push_back(df3.Sum("NormWeight").GetValue());
    n_evt_survive.push_back(df4.Sum("NormWeight").GetValue());
    n_evt_survive.push_back(df5.Sum("NormWeight").GetValue());
    n_evt_survive.push_back(df6.Sum("NormWeight").GetValue());
    n_evt_survive.push_back(df7.Sum("NormWeight").GetValue());

    auto h_cutflow = new TH1D("cutflow", "", n_evt_survive.size(), 0, n_evt_survive.size());
    std::vector<const char*> binlabels{"origin", "2_jets_pass_det", "jj_m > 300", "|jj_delta_y| > 2", "4_leps_pass_det", "2_lpairs", "z1_z2_m_around_Z", "lep_pt>20,20,10"};

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