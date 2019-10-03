#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include "vector"
#include <TMath.h>
#include <iostream>

using namespace std;

float findLowestNum(vector<float> array){
    float lowest = array[0];
    for(int i = 0; i < array.size(); i++){
        if(array[i] < lowest){
            lowest = array[i];
        }
    }
    return lowest;
}

void my_analysis()
{
    // open file containing the sample data tree
    TFile* treeFile = TFile::Open("/mnt/MainShare/Projects/Qichen/VBS/samples/sample/ntuple.root");
    

    // get tree from file
    TTree* tree  = (TTree*)treeFile->Get("SM4L_Nominal");
    

    // declare histograms
    TH1F* h_m4l = new TH1F("m4l","m4l",50,0.,1000.);
    TH1F* h_ele_pt = new TH1F("ele_pt","pt1",50,0.,1000.);

    TH1F* h_jet_pt = new TH1F("jet_pt","jet_pt",50,-5.,1000.);
    TH1F* h_third_jet_pt = new TH1F("third_jet_pt","third_jet_pt",50,0.,200);
    TH1F* h_jet_E = new TH1F("jet_E","jet_E",50,0.,1000.);


    // declare variables to read from tree
    std::vector<int> *lepton_particleID=0;
    double m4l=0;
    std::vector<float> *lepton_pt = 0;
    std::vector<float> *jet_pt = 0;
    std::vector<float> *jet_E = 0;
    std::vector<float> jet_3pt;
    std::vector<float> third_jet_pt;


    // assign variables to branches
    tree->SetBranchAddress("m4l",&m4l);
    tree->SetBranchAddress("lepton_pt",&lepton_pt);
    tree->SetBranchAddress("lepton_particleID",&lepton_particleID);
    tree->SetBranchAddress("jet_pt",&jet_pt);


    // loop over tree events
    int nentries = (int)tree->GetEntries();
    for (int i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        
        // do some selection, for example only events with 4 or more leptons
        if (lepton_pt->size() < 4) continue;
        //Fill histogram
        h_m4l->Fill(m4l);
        
        // loop over objects and fill histograms under certain conditions e.g. electrons with pt>30GeV
        for(int j = 0; j < lepton_pt->size(); j++){
            if((abs((*lepton_particleID)[j])==11)&&((*lepton_pt)[j]>30000)){
	      h_ele_pt->Fill((*lepton_pt)[j]/1000.);
            }
        }

    }


    for (int i = 0; i < nentries; i++) {
        tree->GetEntry(i);

        // find 3rd jet - selected on lowest E/pT
        if (jet_pt->size() < 3) continue; //ignore events with less than 3 jets
        for(int k = 0; k < jet_pt->size(); k++){
            h_jet_pt->Fill((*jet_pt)[k]/1000.);
        }
        h_third_jet_pt->Fill(findLowestNum(*jet_pt)/1000); //find lowest pt jet for each event

}

    // open output file and write output
    TFile* out = TFile::Open("output.root","recreate");
    //write histograms to file
    h_m4l->Write();
    h_ele_pt->Write();
    h_jet_pt->Write();
    h_third_jet_pt->Write();

    //close output file
    out->Close();
    

    // plot histograms
    //TCanvas* c0 = new TCanvas("c0","c0");
    //h_m4l->SetTitle("m4l;m4l [GeV];Events");
    //h_m4l->Draw();
    //TCanvas* c1 = new TCanvas("c1","c1");
    //h_ele_pt->SetTitle("electron pt;pt [GeV];Events");
    //h_ele_pt->Draw();
    TCanvas* c2 = new TCanvas("c2","c2");
    h_jet_pt->SetTitle("Jet pt;pt [GeV];Events");
    h_jet_pt->Draw();
    TCanvas* c3 = new TCanvas("c3","c3");
    h_third_jet_pt->SetTitle("3rd Jet pt;pt [GeV];Events");
    h_third_jet_pt->Draw();

    
}

# ifndef __CINT__
int main()
{
    
    my_analysis();
    return 0;
}
# endif

