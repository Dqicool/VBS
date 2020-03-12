#include "genAna.h"
#define LUMI 139e3
#include<THStack.h>
#define IMAGEX 3000
#define IMAGEY 2000

//#define debug

TH1D getDraw(const char* file, const char* filterr, const char* dist,  Color_t col)
{
    auto histoname = "h_" + (string)dist + "_" + (string)filterr;
    TFile *f = TFile::Open(file, "read");
    TH1D *h = (TH1D*)f->Get(&histoname[0]);
    h->SetFillColor(col);
    h->SetLineColor(col);
    h->SetMarkerColor(col);
    return (*h);
}

void plotProp(const char* outfile, const char* dist, bool truth){
    ROOT::EnableImplicitMT(24);
    TH1::SetDefaultSumw2();
    //loading data from files
        std::vector<std::vector<std::string>> files;
        std::vector<Color_t> color_vec;
        std::vector<std::string> cata;
        std::vector<std::string> color_name;
        color_vec =     {kOrange,   kOrange,    kOrange,    kOrange,        kRed,       kBlue,   kMagenta};
        color_name =    {"kOrange", "kOrange",  "kOrange",  "kOrange",      "kRed",     "kMagenta", "kBlue"};
        //SIGNAL
            std::vector<std::string> signals;

            signals.push_back("output/draw_out/999_all/364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.root");
            signals.push_back("output/draw_out/999_all/344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root");

        //Higgs
            std::vector<std::string> higgses;
            #ifndef debug
             higgses.push_back("output/draw_out/999_all/345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root");
             higgses.push_back("output/draw_out/999_all/345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root");
             higgses.push_back("output/draw_out/999_all/345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root");
            #endif
        //gg4l
            std::vector<std::string> gg4ls;
            #ifndef debug
            gg4ls.push_back("output/draw_out/999_all/345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root");
            gg4ls.push_back("output/draw_out/999_all/345706.Sherpa_222_NNPDF30NNLO_ggllll_130M4l.root");
            gg4ls.push_back("output/draw_out/999_all/345708.Sherpa_222_NNPDF30NNLO_ggllllNoHiggs_0M4l130.root");
            #endif
        //TRIBOSON
            std::vector<std::string> tribosons;
            #ifndef debug
            tribosons.push_back("output/draw_out/999_all/364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6.root");
            tribosons.push_back("output/draw_out/999_all/364245.Sherpa_222_NNPDF30NNLO_WZZ_5l1v_EW6.root");
            tribosons.push_back("output/draw_out/999_all/364247.Sherpa_222_NNPDF30NNLO_ZZZ_6l0v_EW6.root");
            tribosons.push_back("output/draw_out/999_all/364248.Sherpa_222_NNPDF30NNLO_ZZZ_4l2v_EW6.root");
            #endif
        //qq4l
            std::vector<std::string> qq4ls;
            #ifndef debug
            qq4ls.push_back("output/draw_out/999_all/364250.Sherpa_222_NNPDF30NNLO_llll.root");
            qq4ls.push_back("output/draw_out/999_all/346340.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_allhad.root");
            qq4ls.push_back("output/draw_out/999_all/346341.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_semilep.root");
            qq4ls.push_back("output/draw_out/999_all/346342.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_dilep.root");

            #endif
        //WZllvl
            std::vector<std::string> WZs;
            #ifndef debug
            WZs.push_back("output/draw_out/999_all/361601.PowhegPy8EG_WZlvll_mll4.root");
            #endif
        //rest
            std::vector<std::string> rests;
            #ifndef debug
            rests.push_back("output/draw_out/999_all/410142.Sherpa_NNPDF30NNLO_ttll_mll5.root");
            rests.push_back("output/draw_out/999_all/410472.PhPy8EG_A14_ttbar_hdamp258p75_dil.root");

            // rests.push_back("output/draw_out/999_all/344295.Sherpa_Zee_4lMassFilter40GeV8GeV.root");
            // rests.push_back("output/draw_out/999_all/344296.Sherpa_Zmumu_4lMassFilter40GeV8GeV.root");
            // // rests.push_back("output/draw_out/999_all/344297.Sherpa_Zee_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root");
            // rests.push_back("output/draw_out/999_all/344298.Sherpa_Zmumu_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root");
            #endif
        files =         {WZs,       rests,      higgses,    tribosons,      signals,   gg4ls,       qq4ls};
        
    //stack
        string cut_st_n = (string)dist + "_cut_stack";
        string nct_st_n  = (string)dist + "_nct_stack";
        string njn_st_n  = (string)dist + "_njn_stack";
        string nn_st_n  = (string)dist + "_nn_stack";
        string sr_st_n  = (string)dist + "_sr_stack";
        string det_st_n  = (string)dist + "_det_stack";

        string cut_h_n = (string)dist + "_cut_h";
        string nct_h_n  = (string)dist + "_nct_h";
        string njn_h_n  = (string)dist + "_njn_h";
        string nn_h_n  = (string)dist + "_nn_h";
        string sr_h_n  = (string)dist + "_sr_h";
        string det_h_n  = (string)dist + "_det_h";

        THStack* cut_stack = new THStack(&cut_st_n[0], "");
        THStack* nct_stack = new THStack(&nct_st_n[0], "");
        THStack* njn_stack = new THStack(&njn_st_n[0], "");
        THStack* nn_stack = new THStack(&nn_st_n[0], "");
        THStack* sr_stack = new THStack(&sr_st_n[0], "");
        THStack* det_stack = new THStack(&det_st_n[0], "");

        std::vector<TH1D> cut_histo, nct_histo, njn_histo, nn_histo, sr_histo, det_histo;
        

        for(uint i = 0; i < files.size(); i++){
            for (uint j = 0; j < (files[i]).size(); j++){
                if(truth){
                    cut_histo.push_back(getDraw(&(files[i][j])[0], "pass_truthBorn_cut", dist, color_vec[i]));
                    nct_histo.push_back(getDraw(&(files[i][j])[0], "pass_truthBorn_NCT_JN", dist, color_vec[i]));
                    njn_histo.push_back(getDraw(&(files[i][j])[0], "pass_truthBorn_CT_NJN", dist, color_vec[i]));
                    nn_histo.push_back(getDraw(&(files[i][j])[0], "pass_truthBorn_NCT_NJN", dist, color_vec[i]));
                    sr_histo.push_back(getDraw(&(files[i][j])[0], "pass_truthBorn_SR", dist, color_vec[i]));
                    det_histo.push_back(getDraw(&(files[i][j])[0], "pass_truthBorn_det", dist, color_vec[i]));
                }
                else{
                    cut_histo.push_back(getDraw(&(files[i][j])[0], "pass_cut", dist, color_vec[i]));
                    nct_histo.push_back(getDraw(&(files[i][j])[0], "pass_NCT_JN", dist, color_vec[i]));
                    njn_histo.push_back(getDraw(&(files[i][j])[0], "pass_CT_NJN", dist, color_vec[i]));
                    nn_histo.push_back(getDraw(&(files[i][j])[0], "pass_NCT_NJN", dist, color_vec[i]));
                    sr_histo.push_back(getDraw(&(files[i][j])[0], "pass_SR", dist, color_vec[i]));
                    det_histo.push_back(getDraw(&(files[i][j])[0], "pass_det", dist, color_vec[i]));
                }
            }
            // cout<<cata[i] + " is in color " + color_name[i]<<endl;
        }
        
        auto nbins = (cut_histo[0]).GetNbinsX();
        auto xmin  = (cut_histo[0]).GetBinLowEdge(1);
        auto xmax =  (cut_histo[0]).GetBinLowEdge(nbins) + (cut_histo[0]).GetBinWidth(nbins);

        TH1D * h_inc_sr = new TH1D(&sr_h_n[0],"",nbins,xmin,xmax);
        TH1D * h_inc_nct = new TH1D(&nct_h_n[0],"",nbins,xmin,xmax);
        TH1D * h_inc_njn = new TH1D(&njn_h_n[0],"",nbins,xmin,xmax);
        TH1D * h_inc_nn = new TH1D(&nn_h_n[0],"",nbins,xmin,xmax);
        TH1D * h_inc_cut = new TH1D(&cut_h_n[0],"",nbins,xmin,xmax);
        TH1D * h_inc_det = new TH1D(&det_h_n[0],"",nbins,xmin,xmax);
        
        for(uint i=0; i<cut_histo.size(); i++)
        {
            h_inc_cut->Add(&(cut_histo[i]));
            h_inc_nct->Add(&(nct_histo[i]));
            h_inc_njn->Add(&(njn_histo[i]));
            h_inc_nn->Add(&(nn_histo[i]));
            h_inc_sr->Add(&(sr_histo[i]));
            h_inc_det->Add(&(det_histo[i]));
        }
    //print results
        {
            double err;
            cout<<"$"<<h_inc_cut->IntegralAndError(1,nbins, err)<<"\\pm "<< err<<"$ & "<<"$"<<h_inc_sr->IntegralAndError(1,nbins, err)<<"\\pm "<< err<<"$ & $"<<h_inc_njn->IntegralAndError(1,nbins, err)<<"\\pm "<< err<<"$ & $"<<h_inc_nct->IntegralAndError(1,nbins, err)<<"\\pm "<< err<<"$ & $"<<h_inc_nn->IntegralAndError(1,nbins, err)<<"\\pm "<< err<<"$"<<endl;
                        cout<<10.2222<<endl;
        }
}

int main()
{
    cout<<"jj_delta_phi"<<endl;
    plotProp("output/stack_out/jjDelPhi.root", "jj_delta_phi", 0);
}
