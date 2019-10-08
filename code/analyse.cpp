#include "genAna.h"

void analysis(char* in_file, char* out_tree)
{
    ROOT::EnableImplicitMT();
    ROOT::RDataFrame frame("SM4L_Nominal",in_file);
    //lambdas
        //Jets
            auto jet_energy = [](std::vector<float> jet_m, std::vector<float> jet_eta, std::vector<float> jet_pt){
                std::vector<float> ret; 
                for(int j=0;j<jet_pt.size();j++)
                {
                    ret.push_back(getEnergy((jet_m)[j], (jet_eta)[j], (jet_pt)[j]));
                }
                return ret;
            };
            auto jet_px_py_pz = [](std::vector<float> jet_eta, std::vector<float> jet_pt, std::vector<float> jet_phi){
                std::vector<std::vector<float>>  jet_px_py_pz;
                for(int j=0;j<jet_pt.size();j++)
                {
                    jet_px_py_pz.push_back(getPxPyPz((jet_pt)[j], (jet_eta)[j], (jet_phi)[j]));
                }
                return jet_px_py_pz;
            };
            auto j1_j2_index = [](std::vector<float> jet_pt){
                    return getMaxSec(jet_pt);
            };
            auto j1_y = [](std::vector<std::vector<float>> jet_px_py_pz,std::vector<float> jet_energy, std::vector<int> j1_j2_index){
                return getY(jet_px_py_pz[j1_j2_index[0]], jet_energy[j1_j2_index[0]]);
            };
            auto j2_y = [](std::vector<std::vector<float>> jet_px_py_pz,std::vector<float> jet_energy, std::vector<int> j1_j2_index){
                return getY(jet_px_py_pz[j1_j2_index[1]], jet_energy[j1_j2_index[1]]);
            };
            auto jj_m = [](std::vector<float> jet_energy, std::vector<std::vector<float>> jet_px_py_pz, std::vector<int> j1_j2_index){
                        return getMassWithInd(jet_energy, jet_px_py_pz, j1_j2_index);
            };
            auto j3_pt = [](std::vector<float> jet_energy, std::vector<float> jet_pt){
                float j3_pt;
                if (jet_energy.size() > 2)
                {
                    int j3_index = findLowestNum(jet_energy);
                    j3_pt = jet_pt[j3_index];
                }
                else j3_pt = -1000;
                return j3_pt;
            };
            auto jj_delta_y = [](float j1_y, float j2_y){
                return j1_y-j2_y;
            };
            auto jj_product_y = [](float j1_y, float j2_y){
                return j1_y*j2_y;
            };
            auto j1_pt = [](std::vector<float> jet_pt, std::vector<int> j1_j2_index){
                return jet_pt[j1_j2_index[0]];
            };
            auto j2_pt = [](std::vector<float> jet_pt, std::vector<int> j1_j2_index){
                return jet_pt[j1_j2_index[1]];
            };
        //z
            auto lepton_energy = [](std::vector<float> lepton_m, std::vector<float> lepton_eta, std::vector<float> lepton_pt){
                std::vector<float> ret; 
                for(int j=0;j<lepton_pt.size();j++)
                {
                    ret.push_back(getEnergy((lepton_m)[j], (lepton_eta)[j], (lepton_pt)[j]));
                }
                return ret;
            };
            auto lepton_px_py_pz = [](std::vector<float> lepton_eta, std::vector<float> lepton_pt, std::vector<float> lepton_phi){
                std::vector<std::vector<float>>  lepton_px_py_pz;
                for(int j=0;j<lepton_pt.size();j++)
                {
                    lepton_px_py_pz.push_back(getPxPyPz((lepton_pt)[j], (lepton_eta)[j], (lepton_phi)[j]));
                }
                return lepton_px_py_pz;
            };
            auto lepton_pair_index = [](std::vector<int> lepton_particleID, std::vector<float> lepton_charge){
                return getLeptonPairInd(lepton_particleID, lepton_charge);
            };
            auto lepton_pair_m = [](std::vector<std::vector<std::vector<int>>> lepton_pair_index, std::vector<float> lepton_energy, std::vector<std::vector<float>> lepton_px_py_pz){
                std::vector<std::vector<float>>  lepton_pair_m;
                for (int k = 0; k < lepton_pair_index.size(); k++)
                {
                    std::vector<float> tmp;
                    tmp.push_back(getMassWithInd(lepton_energy, lepton_px_py_pz, lepton_pair_index[k][0]));
                    tmp.push_back(getMassWithInd(lepton_energy, lepton_px_py_pz, lepton_pair_index[k][1]));
                    lepton_pair_m.push_back(tmp);
                }
                return lepton_pair_m;
            };
            auto m_z1_ind = [](std::vector<std::vector<float>>  lepton_pair_m){
                return closestMassSelect(lepton_pair_m, Z_MASS*1000);
            };
            auto z1_index = [](std::vector<std::vector<std::vector<int>>> lepton_pair_index, std::vector<int> m_z1_ind){
                std::vector<int> z1_lepton_ind;
                z1_lepton_ind.push_back(lepton_pair_index[m_z1_ind[0]][m_z1_ind[1]][0]);
                z1_lepton_ind.push_back(lepton_pair_index[m_z1_ind[0]][m_z1_ind[1]][1]);
                return z1_lepton_ind;
            };
            auto z2_index = [](std::vector<std::vector<std::vector<int>>> lepton_pair_index, std::vector<int> m_z1_ind){
                std::vector<int> z2_lepton_ind;
                z2_lepton_ind.push_back(lepton_pair_index[m_z1_ind[0]][!(bool)m_z1_ind[1]][0]);
                z2_lepton_ind.push_back(lepton_pair_index[m_z1_ind[0]][!(bool)m_z1_ind[1]][1]);
                return z2_lepton_ind;
            };
            auto z_px_py_pz =[](std::vector<std::vector<float>> lepton_px_py_pz, std::vector<int> z_index){
                return getCombinedPxPyPzWithInd(lepton_px_py_pz, z_index);
            };
            auto z_energy = [](std::vector<float> lepton_energy, std::vector<int>z_index){
                return getCombinedEnergyWithInd(lepton_energy, z_index);
            };
            auto z_pt = [](std::vector<std::vector<float>> lepton_px_py_pz, std::vector<int> z_index){
                return getTotalPt(lepton_px_py_pz[z_index[0]], lepton_px_py_pz[z_index[1]]);
            };
            auto z1_m = [](std::vector<std::vector<float>>  lepton_pair_m, std::vector<int> m_z1_ind){
                return lepton_pair_m[m_z1_ind[0]][m_z1_ind[1]];
            };
            auto z2_m = [](std::vector<std::vector<float>>  lepton_pair_m, std::vector<int> m_z1_ind){
                return lepton_pair_m[m_z1_ind[0]][!(bool)m_z1_ind[1]];
            };
            auto z_y = [](std::vector<float> z_px_py_pz, float z_energy){
                return getY(z_px_py_pz,z_energy);
            };
        //llll
            auto llll_index = [](std::vector<int> z1_index, std::vector<int> z2_index){
                vector<int> llll_index = {z1_index[0], z1_index[1], z2_index[0], z2_index[1]};
                return llll_index;
            };
            auto llll_px_py_pz = [](std::vector<std::vector<float>> lepton_px_py_pz, std::vector<int> llll_index){
                return getCombinedPxPyPzWithInd(lepton_px_py_pz, llll_index);
            };
            auto llll_m = [](std::vector<float> lepton_energy,std::vector<std::vector<float>> lepton_px_py_pz, std::vector<int> llll_index){
                return getMassWithInd(lepton_energy, lepton_px_py_pz, llll_index);
            };
            auto llll_pt = [](std::vector<float> llll_px_py_pz){
                return TMath::Sqrt(llll_px_py_pz[0]*llll_px_py_pz[0] + llll_px_py_pz[1]*llll_px_py_pz[1]);
            };
        //system
            auto zzjj_rel_pt = [](float z1_pt, float z2_pt, float j1_pt, float j2_pt, 
                                std::vector<float> z1_px_py_pz, std::vector<float> z2_px_py_pz, 
                                std::vector<std::vector<float>> jet_px_py_pz, std::vector<int> j1_j2_index){
                float zzjj_scaler_sum_pt = z1_pt + z2_pt + j1_pt + j2_pt;
                std::vector<std::vector<float>> zzjj_px_py_pz{z1_px_py_pz, z2_px_py_pz, jet_px_py_pz[j1_j2_index[0]], jet_px_py_pz[j1_j2_index[1]]};
                std::vector<int> ind{0,1,2,3};
                std::vector<float> zzjj_sys_px_py_pz = getCombinedPxPyPzWithInd(zzjj_px_py_pz, ind);
                float zzjj_sys_pt = TMath::Sqrt(TMath::Power(zzjj_sys_px_py_pz[0],2) + TMath::Power(zzjj_sys_px_py_pz[1],2));
                return  zzjj_sys_pt / zzjj_scaler_sum_pt;
            };
    //cut
        auto cutted_frame = frame.Filter("lepton_pt.size() >=4 && jet_pt.size() >= 2");
    //analyse
        auto ana = cutted_frame.Define("jet_energy",jet_energy,{"jet_m","jet_eta","jet_pt"}).
                                Define("jet_px_py_pz",jet_px_py_pz, {"jet_eta","jet_pt","jet_phi"}).
                                Define("j1_j2_index", j1_j2_index, {"jet_pt"}).
                                Define("j1_y", j1_y, {"jet_px_py_pz","jet_energy","j1_j2_index"}).
                                Define("j2_y", j2_y, {"jet_px_py_pz","jet_energy","j1_j2_index"}).
                                Define("jj_m", jj_m, {"jet_energy", "jet_px_py_pz", "j1_j2_index"}).
                                Define("j3_pt", j3_pt, {"jet_energy","jet_pt"}).
                                Define("jj_delta_y",jj_delta_y, {"j1_y","j2_y"}).
                                Define("jj_product_y",jj_product_y,{"j1_y","j2_y"}).
                                Define("j1_pt", j1_pt, {"jet_pt","j1_j2_index"}).
                                Define("j2_pt", j2_pt, {"jet_pt","j1_j2_index"}).
                                Define("lepton_energy",lepton_energy,{"lepton_m","lepton_eta","lepton_pt"}).
                                Define("lepton_px_py_pz",lepton_px_py_pz, {"lepton_eta","lepton_pt","lepton_phi"}).
                                Define("lepton_pair_index",lepton_pair_index, {"lepton_particleID","lepton_charge"}).
                                Define("lepton_pair_m",lepton_pair_m,{"lepton_pair_index", "lepton_energy", "lepton_px_py_pz"}).
                                Define("m_z1_ind",m_z1_ind, {"lepton_pair_m"}).
                                Define("z1_index",z1_index, {"lepton_pair_index","m_z1_ind"}).
                                Define("z2_index",z2_index,  {"lepton_pair_index","m_z1_ind"}).
                                Define("z1_px_py_pz",z_px_py_pz,{"lepton_px_py_pz", "z1_index"}).
                                Define("z2_px_py_pz",z_px_py_pz,{"lepton_px_py_pz", "z2_index"}).
                                Define("z1_energy", z_energy, {"lepton_energy", "z1_index"}).
                                Define("z2_energy", z_energy, {"lepton_energy", "z2_index"}).
                                Define("z1_pt",z_pt,{"lepton_px_py_pz", "z1_index"}).
                                Define("z2_pt",z_pt,{"lepton_px_py_pz", "z2_index"}).
                                Define("z1_m", z1_m, {"lepton_pair_m", "m_z1_ind"}).
                                Define("z2_m", z2_m, {"lepton_pair_m", "m_z1_ind"}).
                                Define("z1_y", z_y, {"z1_px_py_pz", "z1_energy"}).
                                Define("z2_y", z_y, {"z2_px_py_pz", "z2_energy"}).
                                Define("llll_index",llll_index,{"z1_index","z2_index"}).
                                Define("llll_px_py_pz",llll_px_py_pz, {"lepton_px_py_pz","llll_index"}).
                                Define("llll_m", llll_m, {"lepton_energy", "lepton_px_py_pz", "llll_index"}).
                                Define("llll_pt",llll_pt,{"llll_px_py_pz"}).
                                Define("zzjj_rel_pt",zzjj_rel_pt, {"z1_pt","z2_pt","j1_pt","j2_pt","z1_px_py_pz","z2_px_py_pz","jet_px_py_pz","j1_j2_index"});
    //save tree
        ana.Snapshot("out_tree", out_tree, {"jj_m","j1_pt","j2_pt","j3_pt","j1_y","j2_y","jj_delta_y","jj_product_y","z1_m","z2_m","z1_pt","z2_pt","z1_y","z2_y","llll_m","llll_pt","zzjj_rel_pt"});
}

int main(int argc, char** argv)
{
    char* in_file = argv[1];
    char* out_tree = argv[2];
    analysis(in_file, out_tree);    
}