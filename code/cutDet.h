#ifndef __CUTDET__
#define __CUTDET__
#include"genAna.h"

    auto proWeight = [&](double weight){
        return weight;///lumi
    };

std::vector<int> lepSel(std::vector<float> lepton_pt, 
                        std::vector<float> lepton_eta, 
                        std::vector<float> lepton_d0sig, 
                        std::vector<float> lepton_z0sinTheta, 
                        std::vector<int> lepton_particleID,
                        std::vector<char> lepton_passesIsolation)
{
    std::vector<int> letpon_pass_ind;
    auto siz = lepton_pt.size();

    for (uint i = 0;i < siz; i++)
    {
        //if (lepton_passesIsolation[i] == 1)
        {
            if(lepton_particleID[i] == 11){
                if(lepton_pt[i] > 7e3 && TMath::Abs(lepton_eta[i]) < 2.47 && (TMath::Abs(lepton_d0sig[i]) < 5) && TMath::Abs(lepton_z0sinTheta[i]) < 0.5){
                    letpon_pass_ind.push_back(i);
                }
            }
            else if(lepton_particleID[i] == 13)
            {
                if(lepton_pt[i] > 7e3 && TMath::Abs(lepton_eta[i]) < 2.7 && (TMath::Abs(lepton_d0sig[i]) < 3) && TMath::Abs(lepton_z0sinTheta[i]) < 0.5){
                    letpon_pass_ind.push_back(i);
                }
            }
        }
    }
    
    return letpon_pass_ind;
}

std::vector<int> lepTrueSel(std::vector<float> lepton_pt, 
                            std::vector<float> lepton_eta, 
                            std::vector<int> lepton_particleID)
{
    std::vector<int> letpon_pass_ind;
    auto siz = lepton_pt.size();

    for (uint i = 0;i < siz; i++)
    {
        //if (lepton_isTight[i] == 0)
        {
            if(lepton_particleID[i] == 11){
                if(lepton_pt[i] > 7e3 && TMath::Abs(lepton_eta[i]) < 2.47){
                    letpon_pass_ind.push_back(i);
                }
            }
            else if(lepton_particleID[i] == 13)
            {
                if(lepton_pt[i] > 7e3 && TMath::Abs(lepton_eta[i]) < 2.7){
                    letpon_pass_ind.push_back(i);
                }
            }
        }
    }
    
    return letpon_pass_ind;
}

std::vector<int> jetSel(std::vector<float> jet_pt, std::vector<float> jet_eta)
{
    std::vector<int> jet_pass_ind;          //the index of passed jets
    auto siz = jet_pt.size(); 
    for (uint i = 0; i < siz; i++){
        if (TMath::Abs(jet_eta[i]) < 2.4 && jet_pt[i] > 30e3){
            jet_pass_ind.push_back(i);
        }
        else if(TMath::Abs(jet_eta[i]) < 4.5 && jet_pt[i] > 40e3){
            jet_pass_ind.push_back(i);
        }
    } 
    return jet_pass_ind;
}


std::vector<double> fpass_property(std::vector<int> index, std::vector<float> fproperty){
    std::vector<double> ret;
    auto siz = index.size();
    for(uint i = 0; i< siz; i++){
        ret.push_back((double)fproperty[i]);
    }
    return ret;
}


std::vector<char> cpass_property(std::vector<int> index, std::vector<char> cproperty){
    std::vector<char> ret;
    auto siz = index.size();
    for(uint i = 0; i< siz; i++){
        ret.push_back(cproperty[i]);
    }
    return ret;
}

std::vector<int> ipass_property(std::vector<int> index, std::vector<int> iproperty){
    std::vector<int> ret;
    auto siz = index.size();
    for(uint i = 0; i< siz; i++){
        ret.push_back(iproperty[i]);
    }
    return ret;
}

int passN(std::vector<int> index){
    return (int)index.size();
}

bool baseline(std::vector<int> lepton_pass_ind, std::vector<int> jet_pass_ind)
{
    bool ret = lepton_pass_ind.size() >= 4 && jet_pass_ind.size() >= 2;
    return ret;
}
#endif
