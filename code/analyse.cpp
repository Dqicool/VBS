#include "genAna.h"

//#define debug
#define MT
void analysis(char* in_file1,char* in_file2, char* in_file3, char* out_anaed_tree)
{
    #ifdef MT
    ROOT::EnableImplicitMT();
    #endif
    ROOT::RDataFrame dframe("SM4L_Nominal", {in_file1, in_file2, in_file3});

    //lambdas
        //Jets
            auto jet_energy = [](std::vector<float> jet_m, std::vector<float> jet_eta, std::vector<float> jet_pt){
                std::vector<float> ret; 
                for(uint j=0;j<jet_pt.size();j++)
                {
                    ret.push_back(getEnergy((jet_m)[j], (jet_eta)[j], (jet_pt)[j]));
                }
                return ret;
            };
            auto jet_px_py_pz = [](std::vector<float> jet_eta, std::vector<float> jet_pt, std::vector<float> jet_phi){
                std::vector<std::vector<float>>  jet_px_py_pz;
                for(uint j=0;j<jet_pt.size();j++)
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
                for(uint j=0;j<lepton_pt.size();j++)
                {
                    ret.push_back(getEnergy((lepton_m)[j], (lepton_eta)[j], (lepton_pt)[j]));
                }
                return ret;
            };
            auto lepton_px_py_pz = [](std::vector<float> lepton_eta, std::vector<float> lepton_pt, std::vector<float> lepton_phi){
                std::vector<std::vector<float>>  lepton_px_py_pz;
                for(uint j=0;j<lepton_pt.size();j++)
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
                for (uint k = 0; k < lepton_pair_index.size(); k++)
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
            auto centrarity = [](vector<vector<float>> jet_px_py_pz, vector<float> jet_energy, vector<int> j1_j2_index,
                                  vector<float> z1_px_py_pz, vector<float> z2_px_py_pz, float z1_energy, float z2_energy,
                                  float jj_delta_y){
                auto jj_energy = jet_energy[j1_j2_index[0]]+jet_energy[j1_j2_index[1]];
                std::vector<float> jj_px_py_pz;
                for (int i=0;i<3;i++){
                    jj_px_py_pz.push_back(jet_px_py_pz[j1_j2_index[0]][i]+jet_px_py_pz[j1_j2_index[1]][i]);
                }
                auto zz_energy = z1_energy+z2_energy;
                std::vector<float> zz_px_py_pz = {z1_px_py_pz[0]+z2_px_py_pz[0], z1_px_py_pz[1]+z2_px_py_pz[1], z1_px_py_pz[2]+z2_px_py_pz[2]};
                auto jj_y = getY(jj_px_py_pz, jj_energy);
                auto zz_y = getY(zz_px_py_pz, zz_energy);
                return TMath::Abs((jj_y - zz_y) / jj_delta_y);
            };
        //working point
            auto baseline = [](std::vector<float> lepton_pt, std::vector<float> jet_pt, char passReco_SR){
                auto ret = lepton_pt.size() >=4 && jet_pt.size() >= 2 && passReco_SR>0;
                return ret;
            };
            auto signalRegJN = [](float j1_pt, float j2_pt, float llll_m, float jj_m, float jj_product_y, float jj_delta_y, float zzjj_rel_pt, float z1_m, float z2_m, int jet_n){
                auto ret = j1_pt > 100e3 &&
                            j2_pt > 60e3 &&
                            llll_m > 150e3 &&
                            jj_m > 200e3 &&
                            jj_product_y < 0 &&
                            (jj_delta_y > 1.5 || jj_delta_y < 1.5) &&
                            zzjj_rel_pt < 0.2 &&
                            (z1_m > 62e3 || z1_m < 122e3) &&
                            (z2_m > 62e3 || z2_m < 122e3) &&
                            jet_n == 2;
                return ret;
            };
            auto controlRegJN = [](float j1_pt, float j2_pt, float llll_m, float jj_m, float jj_product_y, float jj_delta_y, float zzjj_rel_pt, float z1_m, float z2_m, int jet_n){
                auto ret = j1_pt > 100e3 &&
                            j2_pt > 60e3 &&
                            llll_m > 150e3 &&
                            jj_m > 200e3 &&
                            jj_product_y < 0 &&
                            (jj_delta_y > 1.5 || jj_delta_y < 1.5) &&
                            zzjj_rel_pt < 0.2 &&
                            (z1_m > 62e3 || z1_m < 122e3) &&
                            (z2_m > 62e3 || z2_m < 122e3) &&
                            jet_n > 2;
                return ret;
            };
            auto signalRegCT = [](float j1_pt, float j2_pt, float llll_m, float jj_m, float jj_product_y, float jj_delta_y, float zzjj_rel_pt, float z1_m, float z2_m, float centrarity){
                auto ret = j1_pt > 100e3 &&
                            j2_pt > 60e3 &&
                            llll_m > 150e3 &&
                            jj_m > 200e3 &&
                            jj_product_y < 0 &&
                            (jj_delta_y > 1.5 || jj_delta_y < 1.5) &&
                            zzjj_rel_pt < 0.2 &&
                            (z1_m > 62e3 || z1_m < 122e3) &&
                            (z2_m > 62e3 || z2_m < 122e3) &&
                            centrarity<0.4;
                return ret;
            };
            auto controlRegCT = [](float j1_pt, float j2_pt, float llll_m, float jj_m, float jj_product_y, float jj_delta_y, float zzjj_rel_pt, float z1_m, float z2_m, float centrarity){
                auto ret = j1_pt > 100e3 &&
                            j2_pt > 60e3 &&
                            llll_m > 150e3 &&
                            jj_m > 200e3 &&
                            jj_product_y < 0 &&
                            (jj_delta_y > 1.5 || jj_delta_y < 1.5) &&
                            zzjj_rel_pt < 0.2 &&
                            (z1_m > 62e3 || z1_m < 122e3) &&
                            (z2_m > 62e3 || z2_m < 122e3) &&
                            centrarity>0.4;
                return ret;
            };

    //analyse
        auto ana = dframe.Filter(baseline, {"lepton_pt","jet_pt", "passReco_SR"}).
                                Define("jet_energy",jet_energy,{"jet_m","jet_eta","jet_pt"}).
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
                                Define("zzjj_rel_pt",zzjj_rel_pt, {"z1_pt","z2_pt","j1_pt","j2_pt","z1_px_py_pz","z2_px_py_pz","jet_px_py_pz","j1_j2_index"}).
                                Define("centrarity", centrarity, {"jet_px_py_pz", "jet_energy","j1_j2_index", "z1_px_py_pz", "z2_px_py_pz", "z1_energy", "z2_energy", "jj_delta_y"}).
                                Define("SRJN_flag", signalRegJN,{"j1_pt", "j2_pt", "llll_m", "jj_m",  "jj_product_y",  "jj_delta_y",  "zzjj_rel_pt",  "z1_m",  "z2_m",  "jet_n"}).
                                Define("CRJN_flag", controlRegJN,{"j1_pt", "j2_pt", "llll_m", "jj_m",  "jj_product_y",  "jj_delta_y",  "zzjj_rel_pt",  "z1_m",  "z2_m",  "jet_n"}).
                                Define("SRCT_flag", signalRegCT, {"j1_pt", "j2_pt", "llll_m", "jj_m",  "jj_product_y",  "jj_delta_y",  "zzjj_rel_pt",  "z1_m",  "z2_m",  "centrarity"}).
                                Define("CRCT_flag", controlRegCT, {"j1_pt", "j2_pt", "llll_m", "jj_m",  "jj_product_y",  "jj_delta_y",  "zzjj_rel_pt",  "z1_m",  "z2_m",  "centrarity"});

    //save tree
        auto hehe = ana.GetColumnNames();
        hehe.erase(hehe.begin(),hehe.begin()+38);
        hehe.push_back("jet_energy");
        hehe.push_back("j1_y");
        hehe.push_back("j2_y");
        hehe.push_back("jj_m");
        hehe.push_back("j3_pt");
        hehe.push_back("jj_delta_y");
        hehe.push_back("jj_product_y");
        hehe.push_back("j1_pt");
        hehe.push_back("j2_pt");
        hehe.push_back("lepton_energy");
        hehe.push_back("z1_energy");
        hehe.push_back("z2_energy");
        hehe.push_back("z1_pt");
        hehe.push_back("z2_pt");
        hehe.push_back("z1_m");
        hehe.push_back("z2_m");
        hehe.push_back("z1_y");
        hehe.push_back("z2_y");
        hehe.push_back("llll_m");
        hehe.push_back("zzjj_rel_pt");
        hehe.push_back("centrarity");
        hehe.push_back("SRJN_flag");
        hehe.push_back("CRJN_flag");
        hehe.push_back("SRCT_flag");
        hehe.push_back("CRCT_flag");
        ana.Snapshot("SM4L_Nominal", out_anaed_tree, hehe);
}
void meta(char* in_file1,char* in_file2, char* in_file3, char* out_anaed_tree)
{
    TChain chain("MetaDataTree");
    chain.Add(in_file1);
    chain.Add(in_file2);
    chain.Add(in_file3);
    double lumi = 0;
    double totlumi = 0;
    chain.SetBranchAddress("prwLuminosity", &lumi);
    auto nent = chain.GetEntries();
    for (Long64_t i = 0; i < nent; i++)
    {
        chain.GetEntry(i);
        totlumi += lumi;
    }
    TTree outtree("totallumi", "");
    outtree.Branch("sumlumi", &totlumi);
    outtree.Fill();
    TFile* out = TFile::Open(out_anaed_tree,"update");
    outtree.Write();
    out->Close();
}
#ifndef debug
int main(int argc, char** argv)
{
    char* in_file1 = argv[1];
    char* in_file2 = argv[2];
    char* in_file3 = argv[3];
    char* out_tree = argv[4];

    analysis(in_file1, in_file2, in_file3, out_tree);
    meta(in_file1, in_file2, in_file3, out_tree);
    cout<<out_tree<<"\t ......done"<<endl;
}
#else
int main()
{
    char* in_file1 = "data/sig/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r10201_r10210_p3654.root";
    char* in_file2 = "data/sig/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r9364_r9315_p3654.root";
    char* in_file3 = "data/sig/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r10724_r10726_p3654.root";
    char* out_tree1  = "output/debug/364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.root";
    analysis(in_file1, in_file2, in_file3, out_tree1);
    meta(in_file1, in_file2, in_file3, out_tree1);
    cout<<out_tree1<<"\t\t\t done"<<endl;

    char* in_file4 = "data/bkg/QCDggZZ/mc16_13TeV.345706.Sherpa_222_NNPDF30NNLO_ggllll_130M4l.deriv.DAOD_HIGG2D1.e6213_s3126_r9364_p3654.root";
    char* in_file5 = "data/bkg/QCDggZZ/mc16_13TeV.345706.Sherpa_222_NNPDF30NNLO_ggllll_130M4l.deriv.DAOD_HIGG2D1.e6213_s3126_r10201_p3654.root";
    char* in_file6 = "data/bkg/QCDggZZ/mc16_13TeV.345706.Sherpa_222_NNPDF30NNLO_ggllll_130M4l.deriv.DAOD_HIGG2D1.e6213_s3126_r10724_p3654.root";
    char* out_tree2  = "output/debug/345706.Sherpa_222_NNPDF30NNLO_ggllll_130M4l.root";    
    analysis(in_file4, in_file5, in_file6, out_tree2);
    meta(in_file4, in_file5, in_file6, out_tree2);
    cout<<out_tree2<<"\t\t\t done"<<endl;
}
#endif