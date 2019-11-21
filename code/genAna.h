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
#include <TLorentzVector.h>
#include <TChain.h>
#include<TROOT.h>
#include<TStyle.h>
#define Z_MASS 91.1876
using namespace std;

float getDeltaR(float eta1, float eta2, float phi1, float phi2){
    return TMath::Sqrt((eta1-eta2)*(eta1-eta2) + (eta1-eta2)*(eta1-eta2));
}

float getTheta(float particle_eta){
        return (2 * TMath::ATan(TMath::Exp(-particle_eta)));
}

float getTotalP(float particle_pt,
                 float particle_eta){
    return (particle_pt)*TMath::CosH(particle_eta);
}

vector<float> getPxPyPz(float particle_pt,
                             float particle_eta,
                             float particle_phi){
    std::vector<float> particle_px_py_pz;
    //float particle_total_p = getTotalP(particle_pt,particle_eta);
    particle_px_py_pz.push_back(particle_pt * TMath::Sin(particle_phi));
    particle_px_py_pz.push_back(particle_pt * TMath::Cos(particle_phi));
    particle_px_py_pz.push_back(particle_pt * TMath::SinH(particle_eta));
    return particle_px_py_pz;
}

float getEnergy(float particle_m,  
                float particle_eta, 
                float particle_pt){
    return TMath::Sqrt(TMath::Power(particle_m, 2) + TMath::Power(getTotalP(particle_pt, particle_eta), 2));
}

float getMass(vector<float> particle_energy, 
                std::vector<std::vector<float>> particle_px_py_pz){
    float energy = 0;
    float px = 0;
    float py = 0;
    float pz = 0;
    for (uint i = 0; i<particle_energy.size(); i++){
        energy += particle_energy[i];
        px += particle_px_py_pz[i][0];
        py += particle_px_py_pz[i][1];
        pz += particle_px_py_pz[i][2];
    }
    return TMath::Sqrt(TMath::Power(energy,2) - TMath::Power(px,2) - TMath::Power(py,2) - TMath::Power(pz,2));
}

float getMassWithInd(vector<float> particle_energy, 
                    std::vector<std::vector<float>> particle_px_py_pz, 
                    vector<int> ind){
    float ret = 0;
    float energy = 0;
    float px = 0;
    float py = 0;
    float pz = 0;
    if (ind.size() > 0){
        for (uint i = 0; i<ind.size(); i++){
            energy += particle_energy[ind[i]];
            px += particle_px_py_pz[ind[i]][0];
            py += particle_px_py_pz[ind[i]][1];
            pz += particle_px_py_pz[ind[i]][2];
        }
        ret = TMath::Sqrt(TMath::Power(energy,2) - TMath::Power(px,2) - TMath::Power(py,2) - TMath::Power(pz,2));
    }
    else{
        ret = -999;
    }
    return ret;
}

vector<int> getMaxSec(vector<float> vec){
    int size = vec.size();
    vector<int> ret;
    if (size < 2){}
    else if (size == 2){
        ret.push_back(0);
        ret.push_back(1);
    }
    else{
        float maxind = 0;
        float secind = 1;
        if (vec[maxind] < vec[secind]){
            maxind = 1;
            secind = 0;
        }
        for (int i=2;i<size;i++){
            
            if (vec[i]>vec[maxind]){
                secind = maxind;
                maxind = i;
            }
            else if (vec[i]>vec[secind]){
                secind =i;
            }
            else{
                continue;
            }
        }
        ret.push_back(maxind);
        ret.push_back(secind);
    }
    return ret;
}

int findLowestNum(vector<float> vec){
    int size = vec.size();
    int ret = 0;
    for (int i = 1; i<size; i++){
        if (vec[ret] > vec[i]) ret = i;
    }
    return ret;
}

vector<int> getLeptonPeerInd(vector<int> lepton_particleID, 
                             vector<int> lepton_charge){
    vector<int> ret;
    for (uint i = 0; i<lepton_charge.size(); i++ )
    {
        for (uint j = i+1; j<lepton_charge.size(); j++)
        {
            if(lepton_particleID[i] == lepton_particleID[j] && lepton_charge[i] != lepton_charge[j])
            {
                {
                    ret.push_back(i);
                    ret.push_back(j);
                }
            }
        }
    }
    if (ret.size()>4)
    {
        int arr1 = ret[6]; int arr2 = ret[7];
        int arr[] = {arr1, arr2};
        ret.insert(ret.begin(),arr, arr+2);

        ret.erase(ret.end() - 2, ret.end());
    }
    return ret;
}

vector<int> closestMassSelect(vector<vector<float>> particle_mass, float target_mass){
    int minind1 = 0;
    int minind2 = 0;
    for (uint i = 0; i < particle_mass.size(); i++){
        for (int j = 0; j < 2; j++){
            auto m11 = TMath::Power(particle_mass[minind1][minind2]-target_mass, 2);
            auto m21 = TMath::Power(particle_mass[i][j]-target_mass, 2);
            if (m11 > m21){
                minind1 = i;
                minind2 = j;
            }
            else if (m11 == m21 && (int)i != minind1){
                auto m12 = TMath::Power(particle_mass[minind1][!(bool)minind2]-target_mass, 2);
                auto m22 = TMath::Power(particle_mass[i][!(bool)j]-target_mass, 2);
                if (m12 > m22){
                    minind1 = i;
                    minind2 = j;
                }
            }
        }
    }
    vector<int> minind{minind1,minind2};
    return minind;
}

float getTotalPt(vector<float> particle1_px_py_pz, 
                 vector<float> particle2_px_py_pz){
    return TMath::Sqrt(TMath::Power((particle1_px_py_pz[0]+particle2_px_py_pz[0]),2) +
                TMath::Power((particle1_px_py_pz[1]+particle2_px_py_pz[1]),2));
}

float getY(vector <float> particle_px_py_pz, float particle_energy){
    float ret = 0;
    if (particle_px_py_pz.size() > 0 && particle_energy > 0){
        float tmp1 = (particle_energy + particle_px_py_pz[2]);
        float tmp2 = (particle_energy - particle_px_py_pz[2]);
        float tmp3 = TMath::Log(tmp1/tmp2);
        ret = tmp3 / 2;
    }
    else{
        ret = -999;
    }
    return ret;
}

vector<float> getCombinedPxPyPzWithInd(std::vector<std::vector<float>> px_py_pz, vector<int> ind ){
    vector <float> ret{};
    float px = 0;
    float py = 0;
    float pz = 0;
    for (uint i = 0; i<ind.size(); i++){
        px += px_py_pz[ind[i]][0];
        py += px_py_pz[ind[i]][1];
        pz += px_py_pz[ind[i]][2];
    }
    ret.push_back(px);
    ret.push_back(py);
    ret.push_back(pz);
    return ret;
}

float getCombinedEnergyWithInd(vector<float> energy, vector<int> ind ){
    float ret = 0;
    if (ind.size() > 0){
        for (uint i = 0; i<ind.size(); i++){
            ret += energy[ind[i]];
        }
    }
    else{
        ret = -999;
    }
    return ret;
}

vector<vector<vector<int>>> getLeptonPairInd(vector<int> lepton_particleID, 
                                                  vector<float> lepton_charge,
                                                  vector<float> lepton_eta,
                                                  vector<float> lepton_phi){
    vector<vector<vector<int>>> ret;
    int size = lepton_charge.size();
    for (int i = 0; i < size-1; i++){
        for(int j = i+1; j < size; j++){
            if (lepton_particleID[i] == lepton_particleID[j] && ((lepton_charge[i] - lepton_charge[j])*(lepton_charge[i] - lepton_charge[j]))>2){
                for (int k = i+1; k < size-1; k++){
                    for (int l = k+1; l<size; l++){
                        if (l != j && k != j){
                            if (lepton_particleID[k] == lepton_particleID[l] && ((lepton_charge[k] - lepton_charge[l])*(lepton_charge[k] - lepton_charge[l]))>2){
                                auto delR_ij = getDeltaR(lepton_eta[i], lepton_eta[j], lepton_phi[i], lepton_eta[j]);
                                auto delR_kl = getDeltaR(lepton_eta[k], lepton_eta[l], lepton_phi[k], lepton_eta[l]);
                                if (delR_ij > 0.1 && delR_kl > 0.1){
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
    //std::cout<<ret.size()<<std::endl;
    return ret;
}

char * intToChar(int a){
        char ret1 = (char)(a/10 + 48);
        char ret2 = (char)((a - 10*(a/10)) +48);
        char tmp1[2] = {ret1,'\0'};
        char tmp2[2] = {ret2,'\0'};
        char* ret = strcat(tmp1, tmp2); 
        return ret;
}

Color_t str2Color(std::string s){
    Color_t ret=0;
    if (s == "kWhite") {ret=kWhite;}
    else if (s == "kBlack") {ret=kBlack;}
    else if (s == "kGray") {ret=kGray;}
    else if (s == "kRed") {ret=kRed;}
    else if (s == "kGreen") {ret=kGreen;}
    else if (s == "kBlue") {ret=kBlue;}
    else if (s == "kYellow") {ret=kYellow;}
    else if (s == "kMagenta") {ret=kMagenta;}
    else if (s == "kCyan") {ret=kCyan;}
    else if (s == "kOrange") {ret=kOrange;}
    else if (s == "kSpring") {ret=kSpring;}
    else if (s == "kTeal") {ret=kTeal;}
    else if (s == "kAzure") {ret=kAzure;}
    else if (s == "kViolet") {ret=kViolet;}
    else if (s == "kPink") {ret=kPink;}
    else {return -1;}
    return ret;
}

float dotProd(float theta1, float phi1, float r1, float theta2, float phi2, float r2){
    auto z1 = TMath::Cos(theta1);
    auto y1 = TMath::Sin(theta1) * TMath::Sin(phi1);
    auto x1 = TMath::Sin(theta1) * TMath::Cos(phi1);

    auto z2 = TMath::Cos(theta2);
    auto y2 = TMath::Sin(theta2) * TMath::Sin(phi2);
    auto x2 = TMath::Sin(theta2) * TMath::Cos(phi2);

    return x1*x2 + y1*y2 + z1*z2;
}

int nJetInBetween(vector<float> jet_eta, vector<float> jet_phi, vector<int> j1_j2_index)
{
    
    int ret = 0;
    std::vector<float> jet_theta;
    if (jet_eta.size()<=2){}
    else
    {
        for (uint i = 0; i<jet_eta.size(); i++){
            jet_theta.push_back(getTheta(jet_eta[i]));
        }
        auto cent_theta = (jet_theta[j1_j2_index[0]] + jet_theta[j1_j2_index[1]]) / 2;
        auto cent_phi   = (jet_phi[j1_j2_index[0]] + jet_phi[j1_j2_index[1]]) / 2;
        auto lead_jet_dot_cent = dotProd(jet_theta[j1_j2_index[0]], jet_phi[j1_j2_index[0]], 1, cent_theta, cent_phi, 1);
        //cout<< lead_jet_dot_cent<<endl;
        for (uint i = 0; i<jet_eta.size(); i++){
            if(i != (uint)j1_j2_index[0] && i != (uint)j1_j2_index[1]){
                auto tmp = dotProd(jet_theta[i], jet_phi[i], 1, cent_theta, cent_phi, 1);
                //cout<<tmp<<endl;
                if(tmp > lead_jet_dot_cent){
                    ret++;
                }
            }
        }
    }
    return ret;
}

std::vector<std::vector<float>> ZPairMSel(vector<vector<float>> lepton_pair_m, float target){
    vector<vector<float>> ret{};
    auto siz = lepton_pair_m.size();
    for (uint i = 0; i < siz; i++){
        if(lepton_pair_m[i][0] > 10e3 && lepton_pair_m[i][1] > 10e3)
        {
            std::vector<float> tmp{1, TMath::Abs(lepton_pair_m[i][0] - target) + TMath::Abs(lepton_pair_m[i][1] - target)};
            ret.push_back(tmp);
        }
        else
        {
            vector<float> tmp{-1, 0};
            ret.push_back(tmp);
        }
    }
    return ret;
} 

std::vector<std::vector<int>> Z1Z2Ind(std::vector<std::vector<float>> zpair_m_ind, std::vector<std::vector<std::vector<int>>>lepton_pair_ind){
    auto siz = zpair_m_ind.size();
    uint min_m_ind = 0;
    bool flag = 1;
    std::vector<std::vector<int>> ret{};
    for(uint i = 0; i < siz; i++){
        if(zpair_m_ind[i][0] > 0){min_m_ind = i; break;}
        if(i == siz-1){flag = 0;}
    }
    if (flag)
    {
        for(uint j = min_m_ind; j < siz; j++)
        {
            if(zpair_m_ind[j][0] > 0)
            {
                if (zpair_m_ind[j][1] < zpair_m_ind[min_m_ind][1]){
                    min_m_ind = j;
                }
            }
        }
        ret = lepton_pair_ind[min_m_ind];
    }
    return ret;
}





std::vector<std::vector<int>> getZ1Z2Index(std::vector<int> lepton_particleID, 
                                std::vector<float> lepton_charge, 
                                std::vector<float> lepton_eta, 
                                std::vector<float> lepton_phi,
                                std::vector<float> lepton_energy,
                                std::vector<std::vector<float>> lepton_px_py_pz){
    
    auto lepton_pair_index =  getLeptonPairInd(lepton_particleID, lepton_charge, lepton_eta, lepton_phi);
    std::vector<std::vector<int>> ret{};
    if(lepton_pair_index.size() >= 1)
    {
        std::vector<std::vector<float>>  lepton_pair_m;
        for (uint k = 0; k < lepton_pair_index.size(); k++)
        {
            std::vector<float> tmp;
            tmp.push_back(getMassWithInd(lepton_energy, lepton_px_py_pz, lepton_pair_index[k][0]));
            tmp.push_back(getMassWithInd(lepton_energy, lepton_px_py_pz, lepton_pair_index[k][1]));
            lepton_pair_m.push_back(tmp);
        }

        auto zpair_abs_m_z = ZPairMSel(lepton_pair_m, Z_MASS*1000);
        
        ret = Z1Z2Ind(zpair_abs_m_z, lepton_pair_index);
    }
    return ret;
}

#endif