#include"genAna.h"
void getGraph(){
    std::vector<std::string> signals{};
    signals.push_back("output/analyse_out/999_all/364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.root");
    signals.push_back("output/analyse_out/999_all/344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root");
    ROOT::RDataFrame df("SM4L_Nominal", {signals[0], signals[1]});
    auto df0 = df.Filter("jet_n>=2 && lepton_n >= 4");
    auto df1 = df0.Filter("jet_pass_n >= 2");
    auto df2 = df1.Filter("jj_m > 300e3");

    TCanvas c1("c1","",1200,800);
    auto h = df2.Histo1D({"mjj", "", 400, 0, 2000e3}, "jj_m", "NormWeight");
    h->Draw();
    c1.SaveAs("mjj1.png");

    TCanvas c2("c2","",1200,800);
    auto h1 = df1.Histo1D({"mjj", "", 400, 0, 2000e3}, "jj_m", "NormWeight");
    c2.SetLeftMargin(0.5);
    c2.SetBottomMargin(0.5);
    h1->Draw();
    c2.SaveAs("mjj2.png");
}

void testlatex(){
    TFile* indelphijj = TFile::Open("output/histo_out/dem_unfold_delphijj.root","read");
    auto Templdelphijj = (TH1D*)indelphijj->Get("h_rebin_delphijj_cut");
    
    for(int i=0; i < Templdelphijj->GetNbinsX(); i++){
        std::stringstream buffer;
        buffer <<std::setprecision(3)<< Templdelphijj->GetBinLowEdge(i+1)/TMath::Pi() <<"#pi<"<<"#Delta#phi_{jj}"<<"<" << (Templdelphijj->GetBinLowEdge(i+1) + Templdelphijj->GetBinWidth(i+1))/TMath::Pi()<<"#pi";
        cout<<buffer.str()<<endl;
        Templdelphijj->GetXaxis()->SetBinLabel(i+1, &(buffer.str())[0]);
        //Templdelphijj->GetYaxis()->SetBinLabel(i+1, &(buffer.str())[0]);
    }
    std::stringstream buffer;
    buffer<<"-0.5#pi<#Delta#phi_{jj}<0.5#pi";
    Templdelphijj->GetXaxis()->SetBinLabel(1,&(buffer.str())[0]);
    TCanvas c1("c1","",2000,2000);
        Templdelphijj->Draw();
}
