#include "genAna.h"
#define LUMI 139e3
#include<THStack.h>

//#define debug

TH1D getHisto(ROOT::RDataFrame df, const char* filterr, const char* dist, int nbins, double xmin, double xmax, Color_t col)
{
    auto histoname = "h_" + (string)dist + "_" + (string)filterr;
    auto filteddf = df.Filter(filterr); 
    auto h = filteddf.Histo1D({&histoname[0],"",nbins,xmin,xmax},dist,"NormWeight");
    h->Scale(LUMI/3.0);
    h->SetFillColor(col);
    h->SetLineColor(col);
    h->SetMarkerColor(col);
    return (*h);
}


void plotProp(const char* outfile, const char* dist, int nbins, double xmin, double xmax){
    ROOT::EnableImplicitMT(24);
    TH1::SetDefaultSumw2();
    //loading data from files
        std::vector<std::vector<std::string>> files;
        std::vector<Color_t> color_vec;
        std::vector<std::string> cata;
        std::vector<std::string> color_name;
        //SIGNAL
            std::vector<std::string> signals;

            signals.push_back("output/analyse_out/999_all/364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.root");
            signals.push_back("output/analyse_out/999_all/344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root");

        //Higgs
            std::vector<std::string> higgses;
            #ifndef debug
            higgses.push_back("output/analyse_out/999_all/345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root");
            higgses.push_back("output/analyse_out/999_all/345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root");
            higgses.push_back("output/analyse_out/999_all/345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root");
            #endif
        //gg4l
            std::vector<std::string> gg4ls;
            #ifndef debug
            gg4ls.push_back("output/analyse_out/999_all/345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root");
            gg4ls.push_back("output/analyse_out/999_all/345706.Sherpa_222_NNPDF30NNLO_ggllll_130M4l.root");
            gg4ls.push_back("output/analyse_out/999_all/345708.Sherpa_222_NNPDF30NNLO_ggllllNoHiggs_0M4l130.root");
            #endif
        //TRIBOSON
            std::vector<std::string> tribosons;
            #ifndef debug
            tribosons.push_back("output/analyse_out/999_all/364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6.root");
            tribosons.push_back("output/analyse_out/999_all/364245.Sherpa_222_NNPDF30NNLO_WZZ_5l1v_EW6.root");
            tribosons.push_back("output/analyse_out/999_all/364247.Sherpa_222_NNPDF30NNLO_ZZZ_6l0v_EW6.root");
            tribosons.push_back("output/analyse_out/999_all/364248.Sherpa_222_NNPDF30NNLO_ZZZ_4l2v_EW6.root");
            #endif
        //qq4l
            std::vector<std::string> qq4ls;
            #ifndef debug
            qq4ls.push_back("output/analyse_out/999_all/364250.Sherpa_222_NNPDF30NNLO_llll.root");
            qq4ls.push_back("output/analyse_out/999_all/346340.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_allhad.root");
            qq4ls.push_back("output/analyse_out/999_all/346341.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_semilep.root");
            qq4ls.push_back("output/analyse_out/999_all/346342.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_dilep.root");
            #endif
        //WZllvl
            std::vector<std::string> WZs;
            #ifndef debug
            WZs.push_back("output/analyse_out/999_all/361601.PowhegPy8EG_WZlvll_mll4.root");
            #endif
        //rest
            std::vector<std::string> rests;
            #ifndef debug
            rests.push_back("output/analyse_out/999_all/410142.Sherpa_NNPDF30NNLO_ttll_mll5.root");
            rests.push_back("output/analyse_out/999_all/410472.PhPy8EG_A14_ttbar_hdamp258p75_dil.root");

            //rests.push_back("output/analyse_out/999_all/344295.Sherpa_Zee_4lMassFilter40GeV8GeV.root");
            //rests.push_back("output/analyse_out/999_all/344296.Sherpa_Zmumu_4lMassFilter40GeV8GeV.root");
            //rests.push_back("output/analyse_out/999_all/344297.Sherpa_Zee_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root");
            //rests.push_back("output/analyse_out/999_all/344298.Sherpa_Zmumu_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root");
            #endif
        files =     {signals, higgses, gg4ls, tribosons, qq4ls, WZs, rests};
        cata = {"signals", "higgses", "gg4ls", "tribosons", "qq4ls", "WZs", "rests"};
        color_vec = {kRed, kGreen, kBlue, kYellow, kMagenta,kCyan,kOrange,kSpring,kTeal,kAzure,kViolet,kPink};
        color_name = {"kRed", "kGreen", "kBlue", "kYellow", "kMagenta","kCyan","kOrange","kSpring","kTeal", "kAzure","kViolet","kPink"};
        
    //stack
        string det_st_n = (string)dist + "_det_stack";
        string cut_st_n = (string)dist + "_cut_stack";
        string nct_st_n  = (string)dist + "_nct_stack";
        string njn_st_n  = (string)dist + "_njn_stack";
        string nn_st_n  = (string)dist + "_nn_stack";
        string sr_st_n  = (string)dist + "_sr_stack";

        string det_h_n = (string)dist + "_det_h";
        string cut_h_n = (string)dist + "_cut_h";
        string nct_h_n  = (string)dist + "_nct_h";
        string njn_h_n  = (string)dist + "_njn_h";
        string nn_h_n  = (string)dist + "_nn_h";
        string sr_h_n  = (string)dist + "_sr_h";

        THStack* det_stack = new THStack(&det_st_n[0], "");
        THStack* cut_stack = new THStack(&cut_st_n[0], "");
        THStack* nct_stack = new THStack(&nct_st_n[0], "");
        THStack* njn_stack = new THStack(&njn_st_n[0], "");
        THStack* nn_stack = new THStack(&nn_st_n[0], "");
        THStack* sr_stack = new THStack(&sr_st_n[0], "");

        std::vector<TH1D> cut_histo, nct_histo, njn_histo, nn_histo, sr_histo, det_histo;
        TH1D * h_inc_det = new TH1D(&det_h_n[0],"", nbins, xmin, xmax);
        TH1D * h_inc_sr = new TH1D(&sr_h_n[0],"",nbins,xmin,xmax);
        TH1D * h_inc_nct = new TH1D(&nct_h_n[0],"",nbins,xmin,xmax);
        TH1D * h_inc_njn = new TH1D(&njn_h_n[0],"",nbins,xmin,xmax);
        TH1D * h_inc_nn = new TH1D(&nn_h_n[0],"",nbins,xmin,xmax);
        TH1D * h_inc_cut = new TH1D(&cut_h_n[0],"",nbins,xmin,xmax);
        

        for(uint i = 0; i < files.size(); i++){
            for (uint j = 0; j < (files[i]).size(); j++){
                ROOT::RDataFrame df("SM4L_Nominal", &(files[i][j])[0]);
                det_histo.push_back(getHisto(df, "pass_det", dist, nbins, xmin, xmax, color_vec[i]));
                cut_histo.push_back(getHisto(df, "pass_cut", dist, nbins, xmin, xmax, color_vec[i]));
                nct_histo.push_back(getHisto(df, "pass_NCT_JN", dist, nbins, xmin, xmax,color_vec[i]));
                njn_histo.push_back(getHisto(df, "pass_CT_NJN", dist, nbins, xmin, xmax,color_vec[i]));
                nn_histo.push_back(getHisto(df, "pass_NCT_NJN", dist, nbins, xmin, xmax,color_vec[i]));
                sr_histo.push_back(getHisto(df, "pass_SR", dist, nbins, xmin, xmax,color_vec[i]));
            }
            cout<<cata[i] + " is in color " + color_name[i]<<endl;
        }
        for(uint i=0; i<cut_histo.size(); i++)
        {
            det_stack->Add(&(det_histo[i]));
            cut_stack->Add(&(cut_histo[i]));
            nct_stack->Add(&(nct_histo[i]));
            njn_stack->Add(&(njn_histo[i]));
            nn_stack->Add(&(nn_histo[i]));
            sr_stack->Add(&(sr_histo[i]));

            h_inc_det->Add(&(det_histo[i]));
            h_inc_cut->Add(&(cut_histo[i]));
            h_inc_nct->Add(&(nct_histo[i]));
            h_inc_njn->Add(&(njn_histo[i]));
            h_inc_nn->Add(&(nn_histo[i]));
            h_inc_sr->Add(&(sr_histo[i]));
        }
    //Store
        TFile * out = TFile::Open(outfile,"recreate");
        det_stack->Write();
        nct_stack->Write();
        njn_stack->Write();
        nn_stack->Write();
        sr_stack->Write();
        cut_stack->Write();

        h_inc_det->Write();
        h_inc_cut->Write();
        h_inc_nct->Write();
        h_inc_njn->Write();
        h_inc_nn->Write();
        h_inc_sr->Write();
        out->Close();

    //print stat
        cout<<h_inc_det->Integral()<<endl;
        cout<<h_inc_cut->Integral()<<endl;
        cout<<h_inc_sr->Integral()<<endl;
        cout<<h_inc_nct->Integral()<<endl;
        cout<<h_inc_njn->Integral()<<endl;
        cout<<h_inc_nn->Integral()<<endl;


    //drawstack
        //sr plot
            TCanvas c1("c1","",1200,800);
            h_inc_sr->SetMarkerColor(kBlack);
            h_inc_sr->SetLineColor(kBlack);
            h_inc_sr->SetFillColor(kBlack);
            h_inc_sr->SetFillStyle(3017);
            //h_inc_sr->SetAxisRange(0,YMAX,"Y");
            sr_stack->Draw("hist");
            h_inc_sr->Draw("E2, same");
            auto sr_save_name = "plots/stack/sr_" + (string)dist + "_stack.png";
            c1.SaveAs(&sr_save_name[0]);
        //nn plot
            TCanvas c2("c1","",1200,800);
            h_inc_nn->SetMarkerColor(kBlack);
            h_inc_nn->SetLineColor(kBlack);
            h_inc_nn->SetFillColor(kBlack);
            h_inc_nn->SetFillStyle(3017);
            //h_inc_nn->SetAxinnange(0,YMAX,"Y");
            nn_stack->Draw("hist");
            h_inc_nn->Draw("E2,same");
            auto nn_save_name = "plots/stack/nn_" + (string)dist + "_stack.png";
            c2.SaveAs(&nn_save_name[0]);
        //nct plot
            TCanvas c3("c1","",1200,800);
            h_inc_nct->SetMarkerColor(kBlack);
            h_inc_nct->SetLineColor(kBlack);
            h_inc_nct->SetFillColor(kBlack);
            h_inc_nct->SetFillStyle(3017);
            //h_inc_nct->SetAxinctange(0,YMAX,"Y");
            nct_stack->Draw("hist");
            h_inc_nct->Draw("E2,same");
            auto nct_save_name = "plots/stack/nct_" + (string)dist + "_stack.png";
            c3.SaveAs(&nct_save_name[0]);
        //njn plot
            TCanvas c4("c1","",1200,800);
            h_inc_njn->SetMarkerColor(kBlack);
            h_inc_njn->SetLineColor(kBlack);
            h_inc_njn->SetFillColor(kBlack);
            h_inc_njn->SetFillStyle(3017);
            //h_inc_njn->SetAxinjnange(0,YMAX,"Y");
            njn_stack->Draw("hist");
            h_inc_njn->Draw("E2,same");
            auto njn_save_name = "plots/stack/njn_" + (string)dist + "_stack.png";
            c4.SaveAs(&njn_save_name[0]);
        //cut plot
            TCanvas c5("c1","",1200,800);
            h_inc_cut->SetMarkerColor(kBlack);
            h_inc_cut->SetLineColor(kBlack);
            h_inc_cut->SetFillColor(kBlack);
            h_inc_cut->SetFillStyle(3017);
            //h_inc_cut->SetAxicutange(0,YMAX,"Y");
            cut_stack->Draw("hist");
            h_inc_cut->Draw("E2,same");
            auto cut_save_name = "plots/stack/cut_" + (string)dist + "_stack.png";
            c5.SaveAs(&cut_save_name[0]);
        //det plot
            TCanvas c6("c1","",1200,800);
            h_inc_det->SetMarkerColor(kBlack);
            h_inc_det->SetLineColor(kBlack);
            h_inc_det->SetFillColor(kBlack);
            h_inc_det->SetFillStyle(3017);
            //h_inc_det->SetAxidetange(0,YMAX,"Y");
            det_stack->Draw("hist");
            h_inc_det->Draw("E2,same");
            auto det_save_name = "plots/stack/det_" + (string)dist + "_stack.png";
            c6.SaveAs(&det_save_name[0]);
}

int main()
{
    cout<<"m4l:"<<endl;
    plotProp("output/stack_out/m4l.root", "llll_m", 1000, 0, 1000e3);
    cout<<"mjj:"<<endl;
    plotProp("output/stack_out/mjj.root", "jj_m", 450, 200e3, 2000e3);
    cout<<"jj_delta_phi"<<endl;
    plotProp("output/stack_out/jjDelPhi.root", "jj_delta_phi", 200, -2*TMath::Pi(), 2*TMath::Pi());
}
        

