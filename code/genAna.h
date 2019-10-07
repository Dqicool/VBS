#ifndef GEN_ANA
#define GEN_ANA
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include "vector"
#include <TMath.h>
#include <iostream>
#include <string.h>
#define Z_MASS 91.1876
using namespace std;

float getTheta(float particle_eta){
        return (2 * TMath::TanH(TMath::Exp(particle_eta)));
}

float getTotalP(float particle_pt,
                 float particle_eta){
    return (particle_pt)*TMath::CosH(particle_eta);
}

vector<float> getPxPyPz(float particle_pt,
                             float particle_eta,
                             float particle_phi){
    std::vector<float> particle_px_py_pz;
    float particle_total_p = getTotalP(particle_pt,particle_eta);
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
    for (int i = 0; i<particle_energy.size(); i++){
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
    float energy = 0;
    float px = 0;
    float py = 0;
    float pz = 0;
    for (int i = 0; i<ind.size(); i++){
        energy += particle_energy[ind[i]];
        px += particle_px_py_pz[ind[i]][0];
        py += particle_px_py_pz[ind[i]][1];
        pz += particle_px_py_pz[ind[i]][2];
    }
    return TMath::Sqrt(TMath::Power(energy,2) - TMath::Power(px,2) - TMath::Power(py,2) - TMath::Power(pz,2));
}

vector<int> getMaxSec(vector<float> vec){
    int size = vec.size();
    vector<int> ret;
    if (size < 2){
        cout<<"error: size less then 2"<<endl;
        ret.push_back(-1);
    }
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
    for (int i = 0; i<lepton_charge.size(); i++ )
    {
        for (int j = i+1; j<lepton_charge.size(); j++)
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
    for (int i = 0; i < particle_mass.size(); i++){
        for (int j = 0; j < 2; j++){
            auto m11 = TMath::Power(particle_mass[minind1][minind2]-target_mass, 2);
            auto m21 = TMath::Power(particle_mass[i][j]-target_mass, 2);
            if (m11 > m21){
                minind1 = i;
                minind2 = j;
            }
            else if (m11 == m21 && i != minind1){
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
    float tmp1 = (particle_energy + particle_px_py_pz[2]);
    float tmp2 = (particle_energy - particle_px_py_pz[2]);
    float tmp3 = TMath::Log(tmp1/tmp2);
    float ret = tmp3 / 2;
    return ret;
}

vector<float> getCombinedPxPyPzWithInd(std::vector<std::vector<float>> px_py_pz, vector<int> ind ){
    vector <float> ret;
    float px = 0;
    float py = 0;
    float pz = 0;
    for (int i = 0; i<ind.size(); i++){
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
    for (int i = 0; i<ind.size(); i++){
        ret += energy[ind[i]];
    }
    return ret;
}

vector<vector<vector<int>>> getLeptonPairInd(vector<int> lepton_particleID, 
                                                  vector<float> lepton_charge){
    vector<vector<vector<int>>> ret;
    int size = lepton_charge.size();
    for (int i = 0; i < size-1; i++){
        for(int j = i+1; j < size; j++){
            if (lepton_particleID[i] == lepton_particleID[j] && ((lepton_charge[i] - lepton_charge[j])*(lepton_charge[i] - lepton_charge[j]))>2){
                for (int k = i+1; k < size-1; k++){
                    for (int l = k+1; l<size; l++){
                        if (l != j && k != j){
                            if (lepton_particleID[k] == lepton_particleID[l] && ((lepton_charge[k] - lepton_charge[l])*(lepton_charge[k] - lepton_charge[l]))>2){
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

#endif