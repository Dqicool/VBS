
// MPhys Project 2019-20 Vector Boson Scattering at the ATLAS experiment
//
// Harriet Watson     Superivosr: Andrew Pilkington
// Lab partner: Dong Qichen
//
// 01/10/19
//
// Based on the basic version of the skeleton code provided by Matteo, PhD student

#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include "vector"
#include<iostream>
using namespace std;


int main(){
    vector<float> tester{4,2,3,23,5,254,7,8};
    cout<<findLowest(tester)<<endl;
}