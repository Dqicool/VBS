#include "genAna.h"
#include "cutDet.h"
#include "ErrorProp.h"

#include <RooUnfoldResponse.h>
#include <RooUnfoldBayes.h>
#include <RooUnfoldErrors.h>
#include<RooUnfoldInvert.h>
#include <cstdlib>
#include <TLegend.h>
#include<THashList.h>
#include<THStack.h>
#include<TRandom.h>
#include<TF1.h>

void getGraph(){
    std::vector<std::string> signals{};
    signals.push_back("output/analyse_out/999_all/364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.root");
    signals.push_back("output/analyse_out/999_all/344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root");
    std::vector<std::string> llll{};
    ROOT::RDataFrame df("SM4L_Nominal", {signals[0], signals[1]});
    auto df0 = df.Filter("jet_n>=2 && lepton_n >= 4");
    auto df1 = df0.Filter("jet_pass_n >= 2");
    auto df2 = df1.Filter("jj_m > 300e3");

    TCanvas c1("c1","",1200,800);
    auto h = df.Histo1D({"z1_m", "", 400, 0, 200e3}, "z1_m", "NormWeight");
    h->Draw();
    c1.SaveAs("mjj1.png");

    TCanvas c2("c2","",1200,800);
    auto h1 = df.Histo1D({"z2_m", "", 400, 0,200e3}, "z2_m", "NormWeight");
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
    TCanvas c1("c1","",1000,1000);
        Templdelphijj->Draw();
}

void testunfold(){
    std::vector<double> m{1,2,3,4,5,6,7,8,9,1};
    std::vector<double> t{1,2,3,4,5,6,7,8,9,9};
    RooUnfoldResponse resp(10,0,10);
    for( uint i = 0;i<m.size();i++){
        resp.Fill(m[i],t[i]);
    }
    TH2D* h_m = new TH2D(resp.Mresponse());
    auto h = resp.Hresponse();
    auto* c1 = new TCanvas("c1","",1000,1000);
    h->SetStats(0);
    auto nx = h->GetNbinsX();
    auto ny = h->GetNbinsY();
    for(int i = 1; i <= nx; i++){
        auto linetotal = h->Integral(i, i, 1, ny);
        for(int j = 1; j <= ny; j++){
            h->SetBinContent(i,j, h->GetBinContent(i,j)/linetotal);
        }
    }

    h->Draw("COLZ");
    h->Draw("TEXT SAME");
    auto* c3 = new TCanvas("c3","",1000,1000);
    h_m->Draw("COLZ");
    h_m->Draw("TEXT SAME");
    c1->SaveAs("hh.png");
    c3->SaveAs("hm.png");
}

void integraldelphijj(const char* dist){
    TFile* f= TFile::Open("output/histo_out/dem_unfold_delphijj.root", "read");
    TH1D* h = (TH1D*) f->Get(dist);
    double errplus, errminus, errall;
    double plus = h->IntegralAndError(3,4, errplus,"");
    double minus = h->IntegralAndError(1,2, errminus,"");
    double all = h->IntegralAndError(1,4, errall,"");
    double A = (plus - minus) / all;
    double errUp = ErrAPlusB(errplus, errminus, 0);
    double errA = ErrADiviB(A, plus-minus, all, errUp, errall,0);
    cout<<dist<<"\tA = " <<A<<" +- "<<errA<<"\tsignificance: "<< A/errA <<endl;
}

void columntype(){

    ROOT::RDataFrame dframe("SM4L_Nominal", "data/999_all/mc16_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.deriv.DAOD_HIGG2D1.e5500_s3126_r9364_p3654.root");
    auto col_name = dframe.GetColumnNames();
    for(uint i=0; col_name.size();i++){
        cout<<col_name[i]<<":\t" <<dframe.GetColumnType(col_name[i])<<endl;
    }
}

void ahhh(){
    auto f1 =TFile::Open("output/stack_out/mjj.root", "read");
    auto f2 = TFile::Open("output/draw_out/Data1516.root", "read");
    auto s_mjj = (THStack*)f1->Get("jj_m_cut_stack");
    auto h_mjj = (TH1D*)f1->Get("jj_m_cut_h");
    auto h_d_mjj = (TH1D*)f2->Get("h_jj_m_pass_cut");
    TCanvas c5("c5","",1000,1000);
            h_mjj->SetMarkerColor(kBlack);
            h_mjj->SetLineColor(kBlack);
            h_mjj->SetFillColor(kBlack);
            h_mjj->SetFillStyle(3017);
            //h_mjj->SetAxicutange(0,YMAX,"Y");
            h_mjj->SetStats(0);
            
            s_mjj->Draw("hist");
            h_mjj->Draw("E2,same");
            
            h_d_mjj->SetMarkerStyle(kFullSquare);
            h_d_mjj->SetMarkerColor(kBlack);
            h_d_mjj->SetLineColor(kBlack);
            h_d_mjj->SetLineWidth(2);

            h_d_mjj->Draw("same, E1");

            c5.SaveAs("debug_mjj.png");
}

void bhhh(){
    auto f1 =TFile::Open("output/stack_out/m4l.root", "read");
    auto f2 = TFile::Open("output/draw_out/Data1516.root", "read");
    auto s_mjj = (THStack*)f1->Get("llll_m_cut_stack");
    auto h_mjj = (TH1D*)f1->Get("llll_m_cut_h");
    auto h_d_mjj = (TH1D*)f2->Get("h_llll_m_pass_cut");
    TCanvas c5("c5","",1000, 1000);
            h_mjj->SetMarkerColor(kBlack);
            h_mjj->SetLineColor(kBlack);
            h_mjj->SetFillColor(kBlack);
            h_mjj->SetFillStyle(3017);
            h_mjj->SetAxisRange(0,25,"Y");
            h_mjj->SetStats(0);
            h_d_mjj->Draw("E1");
            s_mjj->Draw("hist, same");
            h_mjj->Draw("E2,same");
            
            h_d_mjj->SetMarkerStyle(kFullSquare);
            h_d_mjj->SetMarkerColor(kBlack);
            h_d_mjj->SetLineColor(kBlack);
            h_d_mjj->SetLineWidth(2);
            h_d_mjj->Draw("E1 same");
            

            c5.SaveAs("deb_m4l.png");
}

void chhh(){
    auto f1 =TFile::Open("output/stack_out/jjDelPhi.root", "read");
    auto f2 = TFile::Open("output/draw_out/Data1516.root", "read");
    auto s_mjj = (THStack*)f1->Get("jj_delta_phi_cut_stack");
    auto h_mjj = (TH1D*)f1->Get("jj_delta_phi_cut_h");
    auto h_d_mjj = (TH1D*)f2->Get("h_jj_delta_phi_pass_cut");
    TCanvas c5("c5","",1000,1000);
            h_mjj->SetMarkerColor(kBlack);
            h_mjj->SetLineColor(kBlack);
            h_mjj->SetFillColor(kBlack);
            h_mjj->SetFillStyle(3017);
            h_mjj->SetAxisRange(0,14,"Y");
            h_mjj->SetStats(0);
            h_mjj->Draw("E2");
            s_mjj->Draw("hist SAME");
            h_mjj->Draw("E2 SAME");
            
            
            h_d_mjj->SetMarkerStyle(kFullSquare);
            h_d_mjj->SetMarkerColor(kBlack);
            h_d_mjj->SetLineColor(kBlack);
            h_d_mjj->SetLineWidth(2);

            h_d_mjj->Draw("same, E1");

            c5.SaveAs("deb_jjdelphi.png");
}

void playrandom()
{
    TRandom* rtrue= new TRandom();
    TRandom* rsmear= new TRandom();
    RooUnfoldResponse resp(10,-3,3);
    TH1D* testh = new TH1D("hehe","",10,-3,3);
    for(int i = 0;i<50;i++){
        double truth = rtrue->Gaus(0,1);
        double meas = truth + rsmear->Gaus(0,0.2);
        testh->Fill(truth + rsmear->Gaus(0,0.2));
        resp.Fill(meas, truth);
    }
    RooUnfoldBayes unf(&resp, testh, 1);
    unf.PrintTable(std::cout,resp.Htruth());
    auto h_true = resp.Htruth();
    auto h_reco = unf.Hreco();

    auto* c1 = new TCanvas("c1","",2000,2000);
    TH2D* h_resp= new TH2D(resp.Mresponse());
    h_resp->SetStats(0);
    h_resp->Draw("colz");
    c1->SaveAs("debug_resp.png");

    auto* c2 = new TCanvas("c2","",1000,1000);
    h_reco->SetLineColor(kBlack);
    h_reco->SetMarkerColor(kBlack);
    h_reco->SetMarkerStyle(kFullCircle);
    h_reco->SetFillColorAlpha(kBlack, 0.3);
    h_reco->SetMarkerStyle(kFullCircle);
    h_reco->SetStats(0);
    h_reco->SetAxisRange(-12, 35, "Y");
    h_reco->Draw("E2");
    h_reco->Draw("SAME E1");
    testh->SetLineStyle(kDashed);
    testh->SetLineColor(kRed);
    testh->Draw("HIST same");
    h_true->SetLineColor(kRed);
    h_true->Draw("HIST SAME");
    TF1* fgaus = new TF1("gaushehe", "gaus", -3,3);
    fgaus->SetParameters(30/TMath::Sqrt(TMath::TwoPi()),0,1);
    fgaus->SetLineColor(kBlue);
    fgaus->Draw("same");
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
            legend->AddEntry(h_reco,"Unfolded","lepf");
            legend->AddEntry(h_true,"Truth","l");
            legend->AddEntry(testh,"Measurement","l");
            legend->AddEntry(fgaus,"Expectation","l");
            legend->Draw();
    c2->SaveAs("debug_dist.png");

    auto* c3 = new TCanvas("c3","",1000,1000);
    for(int i =1;i<=10;i++){
        h_reco->SetBinContent(i ,h_reco->GetBinContent(i) - h_true->GetBinContent(i));
        testh->SetBinContent(i, testh->GetBinContent(i) - h_true->GetBinContent(i));
        h_true->SetBinContent(i, 0);

    }
    h_reco->SetAxisRange(-15,15, "Y");
    h_reco->Draw("E2");
    h_reco->Draw("SAME E1");
    testh->Draw("HIST same");
    h_true->Draw("HIST SAME");
    c3->SaveAs("debug_diff.png");
}

int main(){
    //ahhh();
    //bhhh();
    chhh();
    //playrandom();
    //integraldelphijj("h_rebin_delphijj_data_cut");
    // integraldelphijj("jj_delta_phi_sr_h");
    // integraldelphijj("jj_delta_phi_njn_h");
    // integraldelphijj("jj_delta_phi_nct_h");
    // integraldelphijj("jj_delta_phi_nn_h");
    //getGraph();
    //columntype();
    //comPareevents();

}