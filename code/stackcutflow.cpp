#include "genAna.h"
#define LUMI 139e3
#include<THStack.h>
#include <iterator>
#include <TLegend.h>
#include<fstream>
#include<cstdio>

//#define debug

void cutflowstack(const char* outfile){
    //loading data from files
        std::vector<std::vector<std::string>> files;
        std::vector<Color_t> color_vec;
        std::vector<std::string> cata;
        std::vector<std::string> color_name;
        //SIGNAL
            std::vector<std::string> signals;

            signals.push_back("output/cutflow_out/999_all/364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.root");
            signals.push_back("output/cutflow_out/999_all/344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root");

        //Higgs
            std::vector<std::string> higgses;
            #ifndef debug
            // higgses.push_back("output/cutflow_out/999_all/345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root");
            // higgses.push_back("output/cutflow_out/999_all/345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root");
            // higgses.push_back("output/cutflow_out/999_all/345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root");
            #endif
        //gg4l
            std::vector<std::string> gg4ls;
            #ifndef debug
            gg4ls.push_back("output/cutflow_out/999_all/345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root");
            gg4ls.push_back("output/cutflow_out/999_all/345706.Sherpa_222_NNPDF30NNLO_ggllll_130M4l.root");
            gg4ls.push_back("output/cutflow_out/999_all/345708.Sherpa_222_NNPDF30NNLO_ggllllNoHiggs_0M4l130.root");
            #endif
        //TRIBOSON
            std::vector<std::string> tribosons;
            #ifndef debug
            // tribosons.push_back("output/cutflow_out/999_all/364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6.root");
            // tribosons.push_back("output/cutflow_out/999_all/364245.Sherpa_222_NNPDF30NNLO_WZZ_5l1v_EW6.root");
            // tribosons.push_back("output/cutflow_out/999_all/364247.Sherpa_222_NNPDF30NNLO_ZZZ_6l0v_EW6.root");
            // tribosons.push_back("output/cutflow_out/999_all/364248.Sherpa_222_NNPDF30NNLO_ZZZ_4l2v_EW6.root");
            #endif
        //qq4l
            std::vector<std::string> qq4ls;
            #ifndef debug
            qq4ls.push_back("output/cutflow_out/999_all/364250.Sherpa_222_NNPDF30NNLO_llll.root");
            qq4ls.push_back("output/cutflow_out/999_all/346340.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_allhad.root");
            qq4ls.push_back("output/cutflow_out/999_all/346341.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_semilep.root");
            qq4ls.push_back("output/cutflow_out/999_all/346342.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_dilep.root");
            #endif
        //WZllvl
            std::vector<std::string> WZs;
            #ifndef debug
            // WZs.push_back("output/cutflow_out/999_all/361601.PowhegPy8EG_WZlvll_mll4.root");
            #endif
        //rest
            std::vector<std::string> rests;
            #ifndef debug
            // rests.push_back("output/cutflow_out/999_all/410142.Sherpa_NNPDF30NNLO_ttll_mll5.root");
            // rests.push_back("output/cutflow_out/999_all/410472.PhPy8EG_A14_ttbar_hdamp258p75_dil.root");

            // rests.push_back("output/cutflow_out/999_all/344295.Sherpa_Zee_4lMassFilter40GeV8GeV.root");
            // rests.push_back("output/cutflow_out/999_all/344296.Sherpa_Zmumu_4lMassFilter40GeV8GeV.root");
            // rests.push_back("output/cutflow_out/999_all/344297.Sherpa_Zee_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root");
            // rests.push_back("output/cutflow_out/999_all/344298.Sherpa_Zmumu_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root");
            #endif
        files =     {signals, higgses, gg4ls, tribosons, qq4ls, WZs, rests};
        cata = {"signals", "higgses", "gg4ls", "tribosons", "qq4ls", "WZs", "rests"};
        color_vec = {kRed, kGreen, kBlue, kYellow, kMagenta,kCyan,kOrange,kSpring,kTeal,kAzure,kViolet,kPink};
        color_name = {"kRed", "kGreen", "kBlue", "kYellow", "kMagenta","kCyan","kOrange","kSpring","kTeal", "kAzure","kViolet","kPink"};
        
    //stack

        THStack* stack = new THStack("s_cutflow_n", "");

        std::vector<TH1D> histo; 
        std::remove("plots/cutflow/cutflow_text.csv");
        std::ofstream outcsv("plots/cutflow/cutflow_text.csv");


        for(uint i = 0; i < files.size(); i++){
            cout<<"\n"<<cata[i] + " is in color " + color_name[i]<<endl;
            for (uint j = 0; j < (files[i]).size(); j++){
                std::vector<std::vector<double>> cata_cutflow{};
                auto f = TFile::Open(&(files[i][j])[0], "read");
                auto tmp = (TH1D*)f->Get("cutflow");

                auto lst = tmp->GetArray();
                outcsv<<"\n"<<cata[i] + ": "<<files[i][j]<<", ";
                for(uint j=1;j<=sizeof(lst);j++)
                {
                    outcsv<<lst[j] << "("<< lst[j]/lst[1] <<")"<<", ";
                }
                outcsv<<endl;
                tmp->SetFillColor(color_vec[i]);
                tmp->SetLineColor(color_vec[i]);
                tmp->SetMarkerColor(color_vec[i]);
                histo.push_back(*tmp);
            }

        }
        auto h_inc = (TH1D* )(histo[0]).Clone("hehe");
        //h_inc->Clear();

        for(uint i=0; i<histo.size(); i++)
        {
            stack->Add(&(histo[i]));
            if(i>0) h_inc->Add(&(histo[i]));
        }
    //Store
        TFile * out = TFile::Open(outfile,"recreate");
        stack->Write();
        h_inc->Write();
        out->Close();

    //drawstack
        //sr plot
            TCanvas c1("c1","",1200,800);
            h_inc->SetAxisRange(0,100,"Y");
            h_inc->Draw("TEXT");
            stack->Draw("hist same");
#ifndef debug
            TLegend *legend = new TLegend(0.55,0.65,0.76,0.82);
            legend->AddEntry(&histo[0],"Signal","f");
            legend->AddEntry(&histo[3],"gg4l","f");
            legend->AddEntry(&histo[5],"qq4l","f");
            //legend->AddEntry(&histo[18],"other","f");
            legend->Draw();
#endif
            stack->GetYaxis()->SetTitle("Events");
            //stack->GetXaxis()->SetTitle("Cut applied");

            string sr_save_name = (string)"plots/cutflow/cutflow" + (string)"_stack.png";
            c1.SaveAs(&sr_save_name[0]);
            
}

int main()
{
    cutflowstack("output/histo_out/cutflow.root");
}




