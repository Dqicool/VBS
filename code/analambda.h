#ifndef __ANALAMBDA__
#define __ANALAMBDA__
#include "genAna.h"

//jet
    std::vector<float> jet_energy(std::vector<float> jet_m, std::vector<float> jet_eta, std::vector<float> jet_pt){
        std::vector<float> ret{}; 
        for(uint j=0;j<jet_pt.size();j++)
        {
            ret.push_back(getEnergy((jet_m)[j], (jet_eta)[j], (jet_pt)[j]));
        }
        return ret;
    };
    std::vector<std::vector<float>> jet_px_py_pz(std::vector<float> jet_eta, std::vector<float> jet_pt, std::vector<float> jet_phi){
        std::vector<std::vector<float>>  jet_px_py_pz;
        for(uint j=0;j<jet_pt.size();j++)
        {
            jet_px_py_pz.push_back(getPxPyPz((jet_pt)[j], (jet_eta)[j], (jet_phi)[j]));
        }
        return jet_px_py_pz;
    };

    float jj_delta_phi(std::vector<float> jet_phi, std::vector<int> j1_j2_index, float j1_y, float j2_y){
        float ret = -999;
        if(j1_j2_index.size() < 1){}
        else
        {
            if (j1_y > j2_y)    ret = jet_phi[j1_j2_index[0]] - jet_phi[j1_j2_index[1]];
            else                ret = jet_phi[j1_j2_index[1]] - jet_phi[j1_j2_index[0]];
        }
        return ret;
    }

    std::vector<int> j1_j2_index(std::vector<float> jet_pt, std::vector<std::vector<float>> jet_px_py_pz, std::vector<float> jet_energy){
        std::vector<int> ret{};
        uint size = jet_pt.size();
        if (size < 2) {}
        else{
            std::vector<std::vector<int>> jets_pairs_ind{};
            std::vector<float> jets_pair_energy{};
            for (uint i=0; i < size; i++)
            {
                for (uint j=i+1;j<size;j++)
                {
                    if(getY(jet_px_py_pz[i], jet_energy[i]) * getY(jet_px_py_pz[j], jet_energy[j]) < 0)
                    {
                        std::vector<int> tmp_pairs_ind{(int)i,(int)j};
                        jets_pairs_ind.push_back(tmp_pairs_ind);
                        jets_pair_energy.push_back(jet_energy[i] + jet_energy[j]);
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
                if(jet_pt[jets_pairs_ind[maxind][1]] > jet_pt[jets_pairs_ind[maxind][0]])
                {
                    auto tmp = jets_pairs_ind[maxind][0];
                    jets_pairs_ind[maxind][0] = jets_pairs_ind[maxind][1];
                    jets_pairs_ind[maxind][1] = tmp;
                }
                ret = jets_pairs_ind[maxind];
            }
        }
        return ret;
    };
    float j1_y(std::vector<std::vector<float>> jet_px_py_pz,std::vector<float> jet_energy, std::vector<int> j1_j2_index){
        float ret = -999;
        if(j1_j2_index.size() >= 2){
            ret = getY(jet_px_py_pz[j1_j2_index[0]], jet_energy[j1_j2_index[0]]);
        }
        return ret;
    };
    float j2_y(std::vector<std::vector<float>> jet_px_py_pz,std::vector<float> jet_energy, std::vector<int> j1_j2_index){
        float ret = -999;
        if(j1_j2_index.size() >= 2){
            ret = getY(jet_px_py_pz[j1_j2_index[1]], jet_energy[j1_j2_index[1]]);
        }
        return ret;
    };
    float jj_m(std::vector<float> jet_energy, std::vector<std::vector<float>> jet_px_py_pz, std::vector<int> j1_j2_index){
                return getMassWithInd(jet_energy, jet_px_py_pz, j1_j2_index);
    };
    float jj_delta_y(float j1_y, float j2_y){
        float ret = -999;
        if(j1_y > -999 && j2_y >-999){
            ret =  j1_y-j2_y;
        }
        return ret;
    };
    float jj_product_y(float j1_y, float j2_y){
        float ret = -999;
        if(j1_y > -999 && j2_y >-999){
            ret =  j1_y*j2_y;
        }
        return ret;
    };
    float j1_pt(std::vector<float> jet_pt, std::vector<int> j1_j2_index){
        float ret=0;
        if(j1_j2_index.size() > 0){
            ret = jet_pt[j1_j2_index[0]];
        }
        else{
            ret = -999;
        }
        return ret;
        
    };
    float j2_pt(std::vector<float> jet_pt, std::vector<int> j1_j2_index){
        float ret=0;
        if(j1_j2_index.size() > 0){
            ret = jet_pt[j1_j2_index[1]];
        }
        else{
            ret = -999;
        }
        return ret;
    };
    //z
    std::vector<float> lepton_energy(std::vector<float> lepton_m, std::vector<float> lepton_eta, std::vector<float> lepton_pt){
        std::vector<float> ret; 
        for(uint j=0;j<lepton_pt.size();j++)
        {
            ret.push_back(getEnergy((lepton_m)[j], (lepton_eta)[j], (lepton_pt)[j]));
        }
        return ret;
    };
    std::vector<std::vector<float>> lepton_px_py_pz (std::vector<float> lepton_eta, std::vector<float> lepton_pt, std::vector<float> lepton_phi){
        std::vector<std::vector<float>>  lepton_px_py_pz;
        for(uint j=0;j<lepton_pt.size();j++)
        {
            lepton_px_py_pz.push_back(getPxPyPz((lepton_pt)[j], (lepton_eta)[j], (lepton_phi)[j]));
        }
        return lepton_px_py_pz;
    };
    std::vector<std::vector<int>> z1_z2_ind (std::vector<int> lepton_particleID, 
                        std::vector<float> lepton_charge, 
                        std::vector<float> lepton_eta, 
                        std::vector<float> lepton_phi,
                        std::vector<float> lepton_energy,
                        std::vector<std::vector<float>> lepton_px_py_pz)
    {
        return getZ1Z2Index(lepton_particleID, lepton_charge, lepton_eta,lepton_phi, lepton_energy, lepton_px_py_pz);
    };
//z
    std::vector<int> z1_index (std::vector<std::vector<int>> z1_z2_ind){
        std::vector<int> ret{};
        if(z1_z2_ind.size() >= 1){
            ret = z1_z2_ind[0];
        }
        return ret;
    };

    std::vector<int> z2_index (std::vector<std::vector<int>> z1_z2_ind){
        std::vector<int> ret{};
        if(z1_z2_ind.size() >= 1){
            ret = z1_z2_ind[1];
        }
        return ret;
    };
    std::vector<float> z_px_py_pz(std::vector<std::vector<float>> lepton_px_py_pz, std::vector<int> z_index){
        return getCombinedPxPyPzWithInd(lepton_px_py_pz, z_index);
    };
    float z_energy (std::vector<float> lepton_energy, std::vector<int>z_index){
        return getCombinedEnergyWithInd(lepton_energy, z_index);
    };
    float z_pt (std::vector<std::vector<float>> lepton_px_py_pz, std::vector<int> z_index){
        float ret = 0;
        if(z_index.size() > 0){
            ret = getTotalPt(lepton_px_py_pz[z_index[0]], lepton_px_py_pz[z_index[1]]);
        }
        else{
            ret = -999;
        }
        return ret;
    };
    float z_m (std::vector<int> z_index, std::vector<std::vector<float>> lepton_px_py_pz, std::vector<float> lepton_energy){
        return getMassWithInd(lepton_energy, lepton_px_py_pz, z_index);
    };
    float z_y (std::vector<float> z_px_py_pz, float z_energy){
        return getY(z_px_py_pz,z_energy);
    };
    //llll
    std::vector<int> llll_index (std::vector<int> z1_index, std::vector<int> z2_index){
        std::vector<int> llll_index{};
        if((z1_index.size()) > 0 && (z2_index.size()) > 0){
            llll_index = {z1_index[0], z1_index[1], z2_index[0], z2_index[1]};
        }
        return llll_index;
    };
    std::vector<float> llll_px_py_pz (std::vector<std::vector<float>> lepton_px_py_pz, std::vector<int> llll_index){
        return getCombinedPxPyPzWithInd(lepton_px_py_pz, llll_index);
    };
    float llll_m (std::vector<float> lepton_energy,std::vector<std::vector<float>> lepton_px_py_pz, std::vector<int> llll_index){
        return getMassWithInd(lepton_energy, lepton_px_py_pz, llll_index);
    };
    float llll_pt (std::vector<float> llll_px_py_pz){
        float ret = 0;
        if( llll_px_py_pz.size() > 0){
            ret = TMath::Sqrt(llll_px_py_pz[0]*llll_px_py_pz[0] + llll_px_py_pz[1]*llll_px_py_pz[1]);
        }
        else 
        {
            ret = -999;
        }
        return ret;
    };
//system
    float zzjj_rel_pt (float z1_pt, float z2_pt, float j1_pt, float j2_pt, 
                        std::vector<float> z1_px_py_pz, std::vector<float> z2_px_py_pz, 
                        std::vector<std::vector<float>> jet_px_py_pz, std::vector<int> j1_j2_index){
        float ret=0;
        if(z1_pt>0 && z2_pt>0 && j1_pt>0 && j2_pt>0){
            float zzjj_scaler_sum_pt = z1_pt + z2_pt + j1_pt + j2_pt;
            std::vector<std::vector<float>> zzjj_px_py_pz{z1_px_py_pz, z2_px_py_pz, jet_px_py_pz[j1_j2_index[0]], jet_px_py_pz[j1_j2_index[1]]};
            std::vector<int> ind{0,1,2,3};
            std::vector<float> zzjj_sys_px_py_pz = getCombinedPxPyPzWithInd(zzjj_px_py_pz, ind);
            float zzjj_sys_pt = TMath::Sqrt(TMath::Power(zzjj_sys_px_py_pz[0],2) + TMath::Power(zzjj_sys_px_py_pz[1],2));
            ret = zzjj_sys_pt / zzjj_scaler_sum_pt;
        }
        else{
            ret = -999;
        }
        return ret;
    };
    float centrarity (vector<vector<float>> jet_px_py_pz, vector<float> jet_energy, vector<int> j1_j2_index,
                        vector<float> z1_px_py_pz, vector<float> z2_px_py_pz, float z1_energy, float z2_energy,
                        float jj_delta_y){
        float ret = 0;
        if(j1_j2_index.size()>0 && z1_energy>0 &&z2_energy>0){
            auto jj_energy = jet_energy[j1_j2_index[0]]+jet_energy[j1_j2_index[1]];
            std::vector<float> jj_px_py_pz;
            for (int i=0;i<3;i++){
                jj_px_py_pz.push_back(jet_px_py_pz[j1_j2_index[0]][i]+jet_px_py_pz[j1_j2_index[1]][i]);
            }
            auto zz_energy = z1_energy+z2_energy;
            std::vector<float> zz_px_py_pz = {z1_px_py_pz[0]+z2_px_py_pz[0], z1_px_py_pz[1]+z2_px_py_pz[1], z1_px_py_pz[2]+z2_px_py_pz[2]};
            auto jj_y = getY(jj_px_py_pz, jj_energy);
            auto zz_y = getY(zz_px_py_pz, zz_energy);
            ret =  TMath::Abs((jj_y - zz_y) / jj_delta_y);
        }
        else{
            ret = -999;
        }
        return ret;
    };
//working point

    bool cut_jpt(float j1_pt, float j2_pt){
        return j1_pt > 40e3 && j2_pt > 30e3;
    }

    bool cut_jjm(float jj_m){
        return jj_m > 200e3;
    }

    bool cut_jjyMINUy(float jj_delta_y){
        return ((jj_delta_y > 2 || jj_delta_y < -2) && jj_delta_y > -999);
    }

    bool cut_ptBala(float zzjj_rel_pt){
        return (zzjj_rel_pt < 0.5 && zzjj_rel_pt >= 0);
    }
    bool cut_z1m(float z1_m){
        return (z1_m > Z_MASS*1e3-20e3 && z1_m < Z_MASS*1e3+20e3);
    }

    bool cut_z2m(float z2_m){
        return (z2_m > 15e3 && z2_m < Z_MASS*1e3+20e3);
    }


    bool pass_cut (float j1_pt, float j2_pt, float llll_m, float jj_m, float jj_product_y, float jj_delta_y, float zzjj_rel_pt, float z1_m, float z2_m){
        auto ret =  cut_jpt(j1_pt, j2_pt) &&
                    cut_jjm(jj_m) &&
                    cut_jjyMINUy(jj_delta_y) &&
                    cut_ptBala(zzjj_rel_pt) &&
                    cut_z1m(z1_m) &&
                    cut_z2m(z2_m);
        return ret;
    };
    bool pass_SR(bool pass_cut, int njet_inbetween, float centrarity){
        return pass_cut && (njet_inbetween == 0) && (centrarity<0.4);
    };
    bool pass_CT_no_JN (bool pass_cut, int njet_inbetween, float centrarity){
        return pass_cut && (njet_inbetween > 0) && (centrarity<0.4);
    };
    bool pass_no_CT_JN (bool pass_cut, int njet_inbetween, float centrarity){
        return pass_cut && (njet_inbetween == 0) && (centrarity >= 0.4);
    };
    bool pass_no_CT_no_JN (bool pass_cut, int njet_inbetween, float centrarity){
        return pass_cut && (njet_inbetween > 0) && (centrarity >= 0.4);
    };

#endif

