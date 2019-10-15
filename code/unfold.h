#include <iostream>

#include <TRandom.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>

#include <RooUnfoldResponse.h>
#include <RooUnfoldBayes.h>

void ireUnfold(char* in_tree_file, char* out_histo)
{   
    TFile* treeFile = TFile::Open(in_tree_file);
    TTree* tree  = (TTree*)treeFile->Get("out_anaed_tree");
    //declare histos demands unfold
    TH1D* h_mjj = new TH1D("h_mjj","h_mjj",100,0.,1000.);
    TH1D* h_mjj_true = new TH1D("h_mjj_true","h_mjj",100,0.,1000.);
    TH1D* h_mjj_unfold = new TH1D("h_mjj_unfold","h_mjj",100,0.,1000.);
    
}