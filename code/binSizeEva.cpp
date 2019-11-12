#include "genAna.h"
#include <THStack.h>
#define START 80
std::vector<double> mulScalar(std::vector<double> mat, double x){
    std::vector<double> ret{};
    for(int i = 0; i < mat.size(); i++){
        ret.push_back(mat[i]*x);
    }
    return ret;
}

void binSizeEva()
{
    TH1::SetDefaultSumw2();
    TFile* infile = TFile::Open("output/stack_out/m4l.root", "read");
    TH1D * h_llll_m_det = (TH1D*)infile->Get("llll_m_det_h");
    TH1D * h_llll_m_sr = (TH1D*)infile->Get("llll_m_sr_h");
    TH1D * h_llll_m_cut = (TH1D*)infile->Get("llll_m_cut_h");
    TH1D * h_llll_m_nct = (TH1D*)infile->Get("llll_m_nct_h");
    TH1D * h_llll_m_njn = (TH1D*)infile->Get("llll_m_njn_h");
    TH1D * h_llll_m_nn = (TH1D*)infile->Get("llll_m_nn_h");
    cout<<(h_llll_m_cut->Integral())<<endl;
    auto nbin = h_llll_m_cut->GetNbinsX();
    auto wbin = h_llll_m_cut->GetBinWidth(1);
    std::vector<double> sepa{0, START};
    for(int i=START; i<nbin; ){
        double store = 0;
        while (store < 10 && i < nbin){
            store += h_llll_m_cut->GetBinContent(i);
            i++;
        }
        sepa.push_back(i);
    }
    sepa = mulScalar(sepa, wbin);
    auto h_rebin_m4l_cut = h_llll_m_cut->Rebin(sepa.size()-1, "h_rebin_m4l_cut",&sepa[0]);
    cout<<h_rebin_m4l_cut->Integral()<<endl;
    h_rebin_m4l_cut->SetStats(0);
    h_rebin_m4l_cut->Draw("");
    h_llll_m_cut->Scale(10.0);
    h_llll_m_cut->SetFillColor(kRed);
    h_llll_m_cut->SetMarkerColor(kRed);
    h_llll_m_cut->SetLineColor(kRed);
    h_llll_m_cut->SetStats(0);
    h_llll_m_cut->Draw("Histo same");
    
}

int main(){
    binSizeEva();
}