
#ifndef __GEN_ANA__
#define __GEN_ANA__
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include "vector"
#include <TMath.h>
#include <iostream>
#include <string.h>
#include <ROOT/RDataFrame.hxx>
#include <Math/GenVector/LorentzVector.h>
#include <Math/GenVector/PtEtaPhiM4D.h>
#include <Math/GenVector/PtEtaPhiM4Dfwd.h>
#include <Math/Vector4Dfwd.h>
#include <TChain.h>
#include<TROOT.h>
#include<TStyle.h>
#include<TLatex.h>
#define Z_MASS 91.1876e3
using namespace std;
using namespace ROOT::Math;


vector<PtEtaPhiMVector> getLorentz(vector<double> pt, vector<double> eta, vector<double> phi, vector<double> m){
    std::vector<PtEtaPhiMVector> ret{};
    for(uint i = 0; i < pt.size(); i++){
        PtEtaPhiMVector tmpv(pt[i], eta[i], phi[i], m[i]);
        ret.push_back(tmpv);
    } 
    return ret;
}

double getDeltaR(double eta1, double eta2, double phi1, double phi2){
    return TMath::Sqrt((eta1-eta2)*(eta1-eta2) + (phi1-phi2)*(phi1-phi2));
}

std::vector<int> getJ1J2Ind(std::vector<PtEtaPhiMVector> jet_lorentz){
    std::vector<int> ret{};
    uint size = jet_lorentz.size();
    if (size < 2) {}
    else{
        std::vector<std::vector<int>> jets_pairs_ind{};
        std::vector<double> jets_pair_energy{};
        for (uint i=0; i < size; i++)
        {
            for (uint j=i+1;j<size;j++)
            {
                if(jet_lorentz[i].Rapidity() * jet_lorentz[j].Rapidity() < 0)
                {
                    std::vector<int> tmp_pairs_ind{(int)i,(int)j};
                    jets_pairs_ind.push_back(tmp_pairs_ind);
                    jets_pair_energy.push_back((jet_lorentz[i] + jet_lorentz[j]).Pt());
                }
            }
        }
        if(jets_pair_energy.size() > 0)
        {
            uint maxind = 0;
            for (uint k=1; k<jets_pair_energy.size(); k++)
            {
                if(jets_pair_energy[k] > jets_pair_energy[maxind])
                {
                    maxind = k;
                }
            }
            if(jet_lorentz[jets_pairs_ind[maxind][1]].Pt() > jet_lorentz[jets_pairs_ind[maxind][0]].Pt())
            {
                auto tmp = jets_pairs_ind[maxind][0];
                jets_pairs_ind[maxind][0] = jets_pairs_ind[maxind][1];
                jets_pairs_ind[maxind][1] = tmp;
            }
            ret = jets_pairs_ind[maxind];

            if(jet_lorentz[jets_pairs_ind[maxind][0]].Pt() < 40e3 || jet_lorentz[jets_pairs_ind[maxind][1]].Pt() < 30e3)
                ret = {};
        }
    }
    return ret;
};

double getMjj(std::vector<PtEtaPhiMVector> jet_lorentz, std::vector<int> j1_j2_ind)
{
    double ret = -999;
    if (j1_j2_ind.size() >= 2) ret = (jet_lorentz[j1_j2_ind[0]] + jet_lorentz[j1_j2_ind[1]]).M();
    return ret;
}

int GetNJBetween(std::vector<PtEtaPhiMVector> jet_lorentz, std::vector<int> j1_j2_ind)
{
    int ret = 0;
    if (j1_j2_ind.size() >= 2){
        for (uint i = 0; i<jet_lorentz.size(); i++){
            if((int)i != j1_j2_ind[0] && (int)i != j1_j2_ind[1]){
                if ((jet_lorentz[j1_j2_ind[0]].Rapidity() < jet_lorentz[i].Rapidity()) && (jet_lorentz[j1_j2_ind[1]].Rapidity() > jet_lorentz[i].Rapidity())) {ret++;}
                else if((jet_lorentz[j1_j2_ind[0]].Rapidity() > jet_lorentz[i].Rapidity()) && (jet_lorentz[j1_j2_ind[1]].Rapidity() < jet_lorentz[i].Rapidity())) {ret++;};
            }
        }
    }
    return ret;
}

double getJJDelPhi(std::vector<PtEtaPhiMVector> jet_lorentz, std::vector<int> j1_j2_ind){
    double ret = -999;
    if(j1_j2_ind.size() >= 2){
        if (jet_lorentz[j1_j2_ind[0]].Rapidity() > jet_lorentz[j1_j2_ind[1]].Rapidity())    
            ret = jet_lorentz[j1_j2_ind[0]].Phi() - jet_lorentz[j1_j2_ind[1]].Phi();
        else                
            ret = jet_lorentz[j1_j2_ind[1]].Phi() - jet_lorentz[j1_j2_ind[0]].Phi();
        
        if(ret > TMath::Pi()){
            ret -= 2*TMath::Pi();
        }
        else if(ret < -TMath::Pi()){
            ret += 2*TMath::Pi();
        }
    }
    return ret;
}

double getJJDelY(std::vector<PtEtaPhiMVector> jet_lorentz, std::vector<int> j1_j2_ind){
    double ret = -999;
    if(j1_j2_ind.size() >= 2){
        ret =  jet_lorentz[j1_j2_ind[0]].Rapidity() -  jet_lorentz[j1_j2_ind[1]].Rapidity();
    }
    return ret;
}

vector<vector<vector<int>>> getLeptonPairInd(   vector<int> lepton_particleID, 
                                                vector<double> lepton_charge,
                                                std::vector<PtEtaPhiMVector> lepton_lorentz)
{
    vector<vector<vector<int>>> ret;
    int size = lepton_charge.size();
    for (int i = 0; i < size-1; i++){
        for(int j = i+1; j < size; j++){
            if (lepton_particleID[i] == lepton_particleID[j] && ((lepton_charge[i] - lepton_charge[j])*(lepton_charge[i] - lepton_charge[j]))>2){
                for (int k = i+1; k < size-1; k++){
                    for (int l = k+1; l<size; l++){
                        if (l != j && k != j){
                            if (lepton_particleID[k] == lepton_particleID[l] && ((lepton_charge[k] - lepton_charge[l])*(lepton_charge[k] - lepton_charge[l]))>2){
                                auto delR_ij = getDeltaR(lepton_lorentz[i].Eta(), lepton_lorentz[j].Eta(), lepton_lorentz[i].Phi(), lepton_lorentz[j].Phi());
                                auto delR_kl = getDeltaR(lepton_lorentz[k].Eta(), lepton_lorentz[l].Eta(), lepton_lorentz[k].Phi(), lepton_lorentz[l].Phi());
                                if (delR_ij > 0.2 && delR_kl > 0.2){
                                    if( lepton_particleID[i] == lepton_particleID[k] 
                                        && (lepton_lorentz[i] + lepton_lorentz[j]).M() > 10e3 
                                        && (lepton_lorentz[i] + lepton_lorentz[j]).M() > 10e3)
                                    {
                                        vector<int> tmp1{i,j};
                                        vector<int> tmp2{k,l};
                                        vector<vector<int>> tmp{tmp1,tmp2};
                                        ret.push_back(tmp);
                                    }
                                    else if(lepton_particleID[i] != lepton_particleID[k]){
                                        vector<int> tmp1{i,j};
                                        vector<int> tmp2{k,l};
                                        vector<vector<int>> tmp{tmp1,tmp2};
                                        ret.push_back(tmp);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //std::cout<<ret.size()<<std::endl;
    return ret;
}


std::vector<std::vector<int>> getZ1Z2Index(std::vector<int> lepton_particleID, 
                                std::vector<double> lepton_charge, 
                                std::vector<PtEtaPhiMVector> lepton_lorentz){
    
    auto lepton_pair_index =  getLeptonPairInd(lepton_particleID, lepton_charge, lepton_lorentz);
    std::vector<std::vector<int>> ret{};
    if(lepton_pair_index.size() >= 1)
    {
        std::vector<std::vector<double>>  lepton_pair_m;
        for (uint k = 0; k < lepton_pair_index.size(); k++)
        {
            std::vector<double> tmp;
            tmp.push_back((lepton_lorentz[lepton_pair_index[k][0][0]] + lepton_lorentz[lepton_pair_index[k][0][1]]).M());
            tmp.push_back((lepton_lorentz[lepton_pair_index[k][1][0]] + lepton_lorentz[lepton_pair_index[k][1][1]]).M());
            lepton_pair_m.push_back(tmp);
        }

        vector<double> mass_diff{};
        for (uint i = 0; i < lepton_pair_m.size(); i++){
            auto tmp = TMath::Abs(lepton_pair_m[i][0] - Z_MASS) + TMath::Abs(lepton_pair_m[i][1] - Z_MASS);
            mass_diff.push_back(tmp);
        }

        int min_ind = 0;
        for (uint i = 1; i < mass_diff.size(); i++){
            if (mass_diff[min_ind] > mass_diff[i]) min_ind = (int)i;
        }
        if(TMath::Abs(lepton_pair_m[min_ind][1] - Z_MASS) < TMath::Abs(lepton_pair_m[min_ind][0] - Z_MASS)){
            auto tmp = lepton_pair_index[min_ind][1];
            lepton_pair_index[min_ind][1] = lepton_pair_index[min_ind][0];
            lepton_pair_index[min_ind][0] = tmp;
        }
        ret = lepton_pair_index[min_ind];
    }
    return ret;
}

std::vector<int> getZ1Ind(std::vector<PtEtaPhiMVector> lepton_lorentz, std::vector<std::vector<int>> z1_z2_ind){
    std::vector<int> ret{};
    if(z1_z2_ind.size() >=2)
        ret = z1_z2_ind[0];
    return ret;
}

std::vector<int> getZ2Ind(std::vector<PtEtaPhiMVector> lepton_lorentz, std::vector<std::vector<int>> z1_z2_ind){
    std::vector<int> ret{};
    if(z1_z2_ind.size() >=2)
        ret = z1_z2_ind[1];
    return ret;
}

double getPtBala (std::vector<PtEtaPhiMVector> jet_lorentz, std::vector<int> j1_j2_ind, std::vector<PtEtaPhiMVector> lepton_lorentz, vector<std::vector<int>> z1_z2_ind){
    double ret = -999;
    if(j1_j2_ind.size() >= 2 && z1_z2_ind.size() >= 2){
        auto z1_lorentz = lepton_lorentz[z1_z2_ind[0][0]] + lepton_lorentz[z1_z2_ind[0][1]];
        auto z2_lorentz = lepton_lorentz[z1_z2_ind[1][0]] + lepton_lorentz[z1_z2_ind[1][1]];
        auto j1_lorentz = jet_lorentz[j1_j2_ind[0]];
        auto j2_lorentz = jet_lorentz[j1_j2_ind[1]];
        auto tot_lorentz = z1_lorentz + z2_lorentz +j1_lorentz + j2_lorentz;

        double zzjj_scaler_sum_pt =z1_lorentz.Pt()  + z2_lorentz.Pt() + j1_lorentz.Pt() + j2_lorentz.Pt();
        double zzjj_sys_pt = tot_lorentz.Pt();
        ret = zzjj_sys_pt / zzjj_scaler_sum_pt;
    }
    return ret;
}

double getCentra (std::vector<PtEtaPhiMVector> jet_lorentz, std::vector<int> j1_j2_ind, std::vector<PtEtaPhiMVector> lepton_lorentz, vector<std::vector<int>> z1_z2_ind){
        double ret = -999;
        if(j1_j2_ind.size()>=2 && z1_z2_ind.size() >= 2){
            auto z1_lorentz = lepton_lorentz[z1_z2_ind[0][0]] + lepton_lorentz[z1_z2_ind[0][1]];
            auto z2_lorentz = lepton_lorentz[z1_z2_ind[1][0]] + lepton_lorentz[z1_z2_ind[1][1]];
            auto j1_lorentz = jet_lorentz[j1_j2_ind[0]];
            auto j2_lorentz = jet_lorentz[j1_j2_ind[1]];

            ret =  TMath::Abs(((j1_lorentz + j2_lorentz).Rapidity() - (z1_lorentz + z2_lorentz).Rapidity()) / (j1_lorentz.Rapidity() - j2_lorentz.Rapidity()));
        }
        return ret;
}

double getM4l(std::vector<PtEtaPhiMVector> lepton_lorentz, std::vector<std::vector<int>> z1_z2_ind){
    double ret = -999;
    if(z1_z2_ind.size() >= 2){
            auto zz_lorentz = lepton_lorentz[z1_z2_ind[0][0]] + lepton_lorentz[z1_z2_ind[0][1]] + lepton_lorentz[z1_z2_ind[1][0]] + lepton_lorentz[z1_z2_ind[1][1]];
            ret = zz_lorentz.M();
    }
    return ret;
}

double getZ1M(std::vector<PtEtaPhiMVector> lepton_lorentz, std::vector<std::vector<int>> z1_z2_ind){
    double ret = -999;
    if(z1_z2_ind.size()>=2){
        auto z1_lorentz = lepton_lorentz[z1_z2_ind[0][0]] + lepton_lorentz[z1_z2_ind[0][1]];
        ret =  (z1_lorentz.M());
    }
    return ret;
}

double getZ2M(std::vector<PtEtaPhiMVector> lepton_lorentz, std::vector<std::vector<int>> z1_z2_ind){
    double ret = -999;
    if(z1_z2_ind.size()>=2){
        auto z2_lorentz = lepton_lorentz[z1_z2_ind[1][0]] + lepton_lorentz[z1_z2_ind[1][1]];
        ret =  (z2_lorentz.M());
    }
    return ret;
}

bool pass_cut (double jj_m, double jj_delta_y, double pt_bala, double z1_m, double z2_m, double llll_m){
    auto ret =  jj_m > 200e3 &&
                ((jj_delta_y > 2 || jj_delta_y < -2) && jj_delta_y > -999)  &&
                (TMath::Abs(pt_bala < 0.5)) &&
                (z1_m > 70e3 && z1_m < 110e3) &&
                z2_m > 21.1876e3 && z2_m < 110e3 &&
                llll_m > 0;
    return ret;
};
bool pass_SR(bool pass_cut, int njet_inbetween, double centrarity){
    return pass_cut && (njet_inbetween == 0) && (centrarity<0.4);
};
bool pass_CT_no_JN (bool pass_cut, int njet_inbetween, double centrarity){
    return pass_cut && (njet_inbetween > 0) && (centrarity<0.4);
};
bool pass_no_CT_JN (bool pass_cut, int njet_inbetween, double centrarity){
    return pass_cut && (njet_inbetween == 0) && (centrarity >= 0.4);
};
bool pass_no_CT_no_JN (bool pass_cut, int njet_inbetween, double centrarity){
    return pass_cut && (njet_inbetween > 0) && (centrarity >= 0.4);
};
#endif