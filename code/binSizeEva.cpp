#include "genAna.h"
#include <THStack.h>

std::vector<double> mulScalar(std::vector<double> mat, double x){
    std::vector<double> ret{};
    for(int i = 0; i < mat.size(); i++){
        ret.push_back(mat[i]*x);
    }
    return ret;
}

std::vector<double> pluScalar(std::vector<double> mat, double x){
    std::vector<double> ret{};
    for(int i = 0; i < mat.size(); i++){
        ret.push_back(mat[i] + x);
    }
    return ret;
}

void m4lBinSizeEva()
{
    TH1::SetDefaultSumw2();
    TFile* infile = TFile::Open("output/stack_out/m4l.root", "read");
    TH1D * h_llll_m_det = (TH1D*)infile->Get("llll_m_det_h");
    TH1D * h_llll_m_sr = (TH1D*)infile->Get("llll_m_sr_h");
    TH1D * h_llll_m_cut = (TH1D*)infile->Get("llll_m_cut_h");
    TH1D * h_llll_m_nct = (TH1D*)infile->Get("llll_m_nct_h");
    TH1D * h_llll_m_njn = (TH1D*)infile->Get("llll_m_njn_h");
    TH1D * h_llll_m_nn = (TH1D*)infile->Get("llll_m_nn_h");
    //cout<<(h_llll_m_cut->Integral())<<endl;
    auto nbin = h_llll_m_cut->GetNbinsX();
    auto wbin = h_llll_m_cut->GetBinWidth(1);
    std::vector<double> sepa{0, 115, 135};
    for(int i=135; i<nbin; ){
        double store = 0;
        while (store < 10 && i < nbin){
            store += h_llll_m_cut->GetBinContent(i);
            i++;
        }
        sepa.push_back(i);
    }
    sepa = mulScalar(sepa, wbin);
    auto h_rebin_m4l_cut = h_llll_m_cut->Rebin(sepa.size()-1, "h_rebin_m4l_cut",&sepa[0]);
    //cout<<h_rebin_m4l_cut->Integral()<<endl;
    h_rebin_m4l_cut->SetStats(0);
    h_rebin_m4l_cut->Draw("");
    h_llll_m_cut->Scale(10.0);
    h_llll_m_cut->SetFillColor(kRed);
    h_llll_m_cut->SetMarkerColor(kRed);
    h_llll_m_cut->SetLineColor(kRed);
    h_llll_m_cut->SetStats(0);
    h_llll_m_cut->Draw("Histo same");
    
    //save in files
    TFile* outfile = TFile::Open("output/histo_out/dem_unfold_m4l.root", "recreate");
    h_rebin_m4l_cut->Write();
    h_rebin_m4l_cut->GetNbinsX();
    
    outfile->Close();
}

void mjjBinSizeEva()
{
    TH1::SetDefaultSumw2();
    TFile* infile = TFile::Open("output/stack_out/mjj.root", "read");
    TH1D * h_llll_m_det = (TH1D*)infile->Get("jj_m_det_h");
    TH1D * h_jj_m_sr = (TH1D*)infile->Get("jj_m_sr_h");
    TH1D * h_jj_m_cut = (TH1D*)infile->Get("jj_m_cut_h");
    TH1D * h_jj_m_nct = (TH1D*)infile->Get("jj_m_nct_h");
    TH1D * h_jj_m_njn = (TH1D*)infile->Get("jj_m_njn_h");
    TH1D * h_jj_m_nn = (TH1D*)infile->Get("jj_m_nn_h");
    //cout<<(h_jj_m_cut->Integral())<<endl;
    auto nbin = h_jj_m_cut->GetNbinsX();
    auto wbin = h_jj_m_cut->GetBinWidth(1);
    auto xmin = h_jj_m_cut->GetBinLowEdge(1);
    std::vector<double> sepa{0};
    for(int i=0; i<nbin; ){
        double store = 0;
        while (store < 10 && i < nbin){
            store += h_jj_m_cut->GetBinContent(i);
            i++;
        }
        sepa.push_back(i);
    }
    sepa = mulScalar(sepa, wbin);
    sepa = pluScalar(sepa,xmin);
    auto h_rebin_mjj_cut = h_jj_m_cut->Rebin(sepa.size()-1, "h_rebin_mjj_cut",&sepa[0]);
    //cout<<h_rebin_mjj_cut->Integral()<<endl;
    h_rebin_mjj_cut->SetStats(0);
    h_rebin_mjj_cut->Draw("");
    h_jj_m_cut->Scale(10.0);
    h_jj_m_cut->SetFillColor(kRed);
    h_jj_m_cut->SetMarkerColor(kRed);
    h_jj_m_cut->SetLineColor(kRed);
    h_jj_m_cut->SetStats(0);
    h_jj_m_cut->Draw("Histo same");
    
    //save in files
    TFile* outfile = TFile::Open("output/histo_out/dem_unfold_mjj.root", "recreate");
    h_rebin_mjj_cut->Write();
    outfile->Close();
}

void delphijjBinSizeEva(){
    TH1::SetDefaultSumw2();
    TFile* infile = TFile::Open("output/stack_out/jjDelPhi.root", "read");
    TH1D * h_jj_delta_phi_det = (TH1D*)infile->Get("jj_delta_phi_det_h");
    TH1D * h_jj_delta_phi_sr = (TH1D*)infile->Get("jj_delta_phi_sr_h");
    TH1D * h_jj_delta_phi_cut = (TH1D*)infile->Get("jj_delta_phi_cut_h");
    TH1D * h_jj_delta_phi_nct = (TH1D*)infile->Get("jj_delta_phi_nct_h");
    TH1D * h_jj_delta_phi_njn = (TH1D*)infile->Get("jj_delta_phi_njn_h");
    TH1D * h_jj_delta_phi_nn = (TH1D*)infile->Get("jj_delta_phi_nn_h");
    //cout<<(h_jj_delta_phi_cut->Integral())<<endl;
    auto nbin = h_jj_delta_phi_cut->GetNbinsX();
    auto wbin = h_jj_delta_phi_cut->GetBinWidth(1);
    auto xmin = h_jj_delta_phi_cut->GetBinLowEdge(1);

    std::vector<double> sepaR{(double)nbin/2};
    std::vector<double> sepaL{};
    for(int i=nbin/2 +1; i<nbin; ){
        double store = 0;
        while (store < 10 && i < nbin){
            store += h_jj_delta_phi_cut->GetBinContent(i);
            i++;
        }
        sepaR.push_back(i);
    }
    sepaL = sepaR;
    std::reverse(sepaL.begin(), sepaL.end());
    sepaL = pluScalar(mulScalar(sepaL, -1), nbin);

    std::vector<double> sepa{};
    sepa.insert(sepa.end(), sepaL.begin(), sepaL.end()-1);
    sepa.insert(sepa.end(), sepaR.begin(), sepaR.end());
    sepa = mulScalar(sepa, wbin);
    sepa = pluScalar(sepa,xmin);
    auto h_rebin_delphijj_cut = h_jj_delta_phi_cut->Rebin(sepa.size()-1, "h_rebin_delphijj_cut",&sepa[0]);
    //cout<<h_rebin_delphijj_cut->Integral()<<endl;
    h_rebin_delphijj_cut->SetStats(0);
    h_rebin_delphijj_cut->Draw("");
    h_jj_delta_phi_cut->Scale(5.0);
    h_jj_delta_phi_cut->SetFillColor(kRed);
    h_jj_delta_phi_cut->SetMarkerColor(kRed);
    h_jj_delta_phi_cut->SetLineColor(kRed);
    h_jj_delta_phi_cut->SetStats(0);
    h_jj_delta_phi_cut->Draw("Histo same");
    
    //save in files
    TFile* outfile = TFile::Open("output/histo_out/dem_unfold_delphijj.root", "recreate");
    h_rebin_delphijj_cut->Write();
    outfile->Close();
}

int main(){
    m4lBinSizeEva();
    mjjBinSizeEva();
    delphijjBinSizeEva();
}