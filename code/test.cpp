//claculation of interesting observables

#include "analambda.h"

void analysis(char* in_file1,char* in_file2, char* in_file3, char* out_anaed_tree)
{
    ROOT::RDataFrame dframe("SM4L_Nominal", {in_file1, in_file2, in_file3});
        auto ana=dframe.Define("jet_pass_energy",jet_energy,{"jet_pass_m","jet_pass_eta","jet_pass_pt"}).
                        Define("jet_pass_px_py_pz",jet_px_py_pz, {"jet_pass_eta","jet_pass_pt","jet_pass_phi"}).
                        Define("j1_j2_index", j1_j2_index, {"jet_pass_pt"}).
                        Define("j1_y", j1_y, {"jet_pass_px_py_pz","jet_pass_energy","j1_j2_index"}).
                        Define("j2_y", j2_y, {"jet_pass_px_py_pz","jet_pass_energy","j1_j2_index"}).
                        Define("jj_m", jj_m, {"jet_pass_energy", "jet_pass_px_py_pz", "j1_j2_index"}).
                        Define("njet_inbetween",nJetInBetween,{"jet_pass_px_py_pz", "jet_pass_energy", "j1_j2_index"}).
                        Define("jj_delta_y",jj_delta_y, {"j1_y","j2_y"}).
                        Define("jj_product_y",jj_product_y,{"j1_y","j2_y"}).
                        Define("j1_pt", j1_pt, {"jet_pass_pt","j1_j2_index"}).
                        Define("j2_pt", j2_pt, {"jet_pass_pt","j1_j2_index"}).
                        Define("lepton_pass_energy",lepton_energy,{"lepton_pass_m","lepton_pass_eta","lepton_pass_pt"}).
                        Define("lepton_pass_px_py_pz",lepton_px_py_pz, {"lepton_pass_eta","lepton_pass_pt","lepton_pass_phi"}).
                        Define("z1_z2_index",z1_z2_ind, {"lepton_pass_particleID", "lepton_pass_charge", "lepton_pass_eta", "lepton_pass_phi", "lepton_pass_energy", "lepton_pass_px_py_pz"}).
                        Define("z1_index",z1_index, {"z1_z2_index"}).
                        Define("z2_index",z2_index,  {"z1_z2_index"}).
                        Define("z1_px_py_pz",z_px_py_pz,{"lepton_pass_px_py_pz", "z1_index"}).
                        Define("z2_px_py_pz",z_px_py_pz,{"lepton_pass_px_py_pz", "z2_index"}).
                        Define("z1_energy", z_energy, {"lepton_pass_energy", "z1_index"}).
                        Define("z2_energy", z_energy, {"lepton_pass_energy", "z2_index"}).
                        Define("z1_pt",z_pt,{"lepton_pass_px_py_pz", "z1_index"}).
                        Define("z2_pt",z_pt,{"lepton_pass_px_py_pz", "z2_index"}).
                        Define("z1_m", z_m, {"z1_index","lepton_pass_px_py_pz", "lepton_pass_energy"}).
                        Define("z2_m", z_m, {"z2_index","lepton_pass_px_py_pz", "lepton_pass_energy"}).
                        Define("z1_y", z_y, {"z1_px_py_pz", "z1_energy"}).
                        Define("z2_y", z_y, {"z2_px_py_pz", "z2_energy"}).
                        Define("llll_index",llll_index,{"z1_index","z2_index"}).
                        Define("llll_px_py_pz",llll_px_py_pz, {"lepton_pass_px_py_pz","llll_index"}).
                        Define("llll_m", llll_m, {"lepton_pass_energy", "lepton_pass_px_py_pz", "llll_index"}).
                        Define("llll_pt",llll_pt,{"llll_px_py_pz"}).
                        Define("zzjj_rel_pt",zzjj_rel_pt, {"z1_pt","z2_pt","j1_pt","j2_pt","z1_px_py_pz","z2_px_py_pz","jet_pass_px_py_pz","j1_j2_index"}).
                        Define("centrarity", centrarity, {"jet_pass_px_py_pz", "jet_pass_energy","j1_j2_index", "z1_px_py_pz", "z2_px_py_pz", "z1_energy", "z2_energy", "jj_delta_y"}).
                        Define("pass_cut", pass_cut, {"j1_pt", "j2_pt", "llll_m", "jj_m",  "jj_product_y",  "jj_delta_y",  "zzjj_rel_pt",  "z1_m",  "z2_m"}).
                        Define("pass_SR", pass_SR,{"pass_cut", "njet_inbetween", "centrarity"}).
                        Define("pass_CT_NJN", pass_CT_no_JN,{"pass_cut", "njet_inbetween", "centrarity"}).
                        Define("pass_NCT_JN", pass_no_CT_JN, {"pass_cut", "njet_inbetween", "centrarity"}).
                        Define("pass_NCT_NJN", pass_no_CT_no_JN, {"pass_cut", "njet_inbetween", "centrarity"});

        if(dframe.HasColumn("NormWeight_true")){
            ana =   ana.Define("jet_truthBorn_pass_energy",jet_energy,{"jet_truthBorn_pass_m","jet_truthBorn_pass_eta","jet_truthBorn_pass_pt"}).
                        Define("jet_truthBorn_pass_px_py_pz",jet_px_py_pz, {"jet_truthBorn_pass_eta","jet_truthBorn_pass_pt","jet_truthBorn_pass_phi"}).
                        Define("j1_j2_truthBorn_index", j1_j2_index, {"jet_truthBorn_pass_pt"}).
                        Define("j1_truthBorn_y", j1_y, {"jet_truthBorn_pass_px_py_pz","jet_truthBorn_pass_energy","j1_j2_truthBorn_index"}).
                        Define("j2_truthBorn_y", j2_y, {"jet_truthBorn_pass_px_py_pz","jet_truthBorn_pass_energy","j1_j2_truthBorn_index"}).
                        Define("jj_truthBorn_m", jj_m, {"jet_truthBorn_pass_energy", "jet_truthBorn_pass_px_py_pz", "j1_j2_truthBorn_index"}).
                        Define("njet_truthBorn_inbetween",nJetInBetween,{"jet_truthBorn_pass_px_py_pz", "jet_truthBorn_pass_energy", "j1_j2_truthBorn_index"}).
                        Define("jj_truthBorn_delta_y",jj_delta_y, {"j1_truthBorn_y","j2_truthBorn_y"}).
                        Define("jj_truthBorn_product_y",jj_product_y,{"j1_truthBorn_y","j2_truthBorn_y"}).
                        Define("j1_truthBorn_pt", j1_pt, {"jet_truthBorn_pass_pt","j1_j2_truthBorn_index"}).
                        Define("j2_truthBorn_pt", j2_pt, {"jet_truthBorn_pass_pt","j1_j2_truthBorn_index"}).
                        Define("lepton_truthBorn_pass_energy",lepton_energy,{"lepton_truthBorn_pass_m","lepton_truthBorn_pass_eta","lepton_truthBorn_pass_pt"}).
                        Define("lepton_truthBorn_pass_px_py_pz",lepton_px_py_pz, {"lepton_truthBorn_pass_eta","lepton_truthBorn_pass_pt","lepton_truthBorn_pass_phi"}).
                        Define("z1_z2_truthBorn_index",z1_z2_ind, {"lepton_truthBorn_pass_particleID", "lepton_truthBorn_pass_charge", "lepton_truthBorn_pass_eta", "lepton_truthBorn_pass_phi", "lepton_truthBorn_pass_energy", "lepton_truthBorn_pass_px_py_pz"}).
                        Define("z1_truthBorn_index",z1_index, {"z1_z2_truthBorn_index"}).
                        Define("z2_truthBorn_index",z2_index,  {"z1_z2_truthBorn_index"}).
                        Define("z1_truthBorn_px_py_pz",z_px_py_pz,{"lepton_truthBorn_pass_px_py_pz", "z1_truthBorn_index"}).
                        Define("z2_truthBorn_px_py_pz",z_px_py_pz,{"lepton_truthBorn_pass_px_py_pz", "z2_truthBorn_index"}).
                        Define("z1_truthBorn_energy", z_energy, {"lepton_truthBorn_pass_energy", "z1_truthBorn_index"}).
                        Define("z2_truthBorn_energy", z_energy, {"lepton_truthBorn_pass_energy", "z2_truthBorn_index"}).
                        Define("z1_truthBorn_pt",z_pt,{"lepton_truthBorn_pass_px_py_pz", "z1_truthBorn_index"}).
                        Define("z2_truthBorn_pt",z_pt,{"lepton_truthBorn_pass_px_py_pz", "z2_truthBorn_index"}).
                        Define("z1_truthBorn_m", z_m, {"z1_truthBorn_index","lepton_truthBorn_pass_px_py_pz", "lepton_truthBorn_pass_energy"}).
                        Define("z2_truthBorn_m", z_m, {"z2_truthBorn_index","lepton_truthBorn_pass_px_py_pz", "lepton_truthBorn_pass_energy"}).
                        Define("z1_truthBorn_y", z_y, {"z1_truthBorn_px_py_pz", "z1_truthBorn_energy"}).
                        Define("z2_truthBorn_y", z_y, {"z2_truthBorn_px_py_pz", "z2_truthBorn_energy"}).
                        Define("llll_truthBorn_index",llll_index,{"z1_truthBorn_index","z2_truthBorn_index"}).
                        Define("llll_truthBorn_px_py_pz",llll_px_py_pz, {"lepton_truthBorn_pass_px_py_pz","llll_truthBorn_index"}).
                        Define("llll_truthBorn_m", llll_m, {"lepton_truthBorn_pass_energy", "lepton_truthBorn_pass_px_py_pz", "llll_truthBorn_index"}).
                        Define("llll_truthBorn_pt",llll_pt,{"llll_truthBorn_px_py_pz"}).
                        Define("zzjj_rel_pt_truthBorn",zzjj_rel_pt, {"z1_truthBorn_pt","z2_truthBorn_pt","j1_truthBorn_pt","j2_truthBorn_pt","z1_truthBorn_px_py_pz","z2_truthBorn_px_py_pz","jet_truthBorn_pass_px_py_pz","j1_j2_truthBorn_index"}).
                        Define("centrarity_truthBorn", centrarity, {"jet_truthBorn_pass_px_py_pz", "jet_truthBorn_pass_energy","j1_j2_truthBorn_index", "z1_truthBorn_px_py_pz", "z2_truthBorn_px_py_pz", "z1_truthBorn_energy", "z2_truthBorn_energy", "jj_truthBorn_delta_y"}).
                        Define("pass_truthBorn_cut", pass_cut, {"j1_truthBorn_pt", "j2_truthBorn_pt", "llll_truthBorn_m", "jj_truthBorn_m",  "jj_truthBorn_product_y",  "jj_truthBorn_delta_y",  "zzjj_rel_pt_truthBorn",  "z1_truthBorn_m",  "z2_truthBorn_m"}).
                        Define("pass_truthBorn_SR", pass_SR,{"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"}).
                        Define("pass_truthBorn_CT_NJN", pass_CT_no_JN,{"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"}).
                        Define("pass_truthBorn_NCT_JN", pass_no_CT_JN, {"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"}).
                        Define("pass_truthBorn_NCT_NJN", pass_no_CT_no_JN, {"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"});
    }
    if(dframe.HasColumn("NormWeight_true")){
            auto hehe = ana.GetColumnNames();
            hehe.erase(hehe.begin(),hehe.begin()+74);
            hehe.push_back("jet_pass_energy");
            hehe.push_back("j1_y");
            hehe.push_back("j2_y");
            hehe.push_back("jj_m");
            hehe.push_back("njet_inbetween");
            hehe.push_back("jj_delta_y");
            hehe.push_back("jj_product_y");
            hehe.push_back("j1_pt");
            hehe.push_back("j2_pt");
            hehe.push_back("lepton_pass_energy");
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
            hehe.push_back("pass_cut");
            hehe.push_back("pass_SR");
            hehe.push_back("pass_NCT_JN");
            hehe.push_back("pass_CT_NJN");
            hehe.push_back("pass_NCT_NJN");

            hehe.push_back("jet_truthBorn_pass_energy");
            hehe.push_back("j1_truthBorn_y");
            hehe.push_back("j2_truthBorn_y");
            hehe.push_back("jj_truthBorn_m");
            hehe.push_back("njet_truthBorn_inbetween");
            hehe.push_back("jj_truthBorn_delta_y");
            hehe.push_back("jj_truthBorn_product_y");
            hehe.push_back("j1_truthBorn_pt");
            hehe.push_back("j2_truthBorn_pt");
            hehe.push_back("lepton_truthBorn_pass_energy");
            hehe.push_back("z1_truthBorn_energy");
            hehe.push_back("z2_truthBorn_energy");
            hehe.push_back("z1_truthBorn_pt");
            hehe.push_back("z2_truthBorn_pt");
            hehe.push_back("z1_truthBorn_m");
            hehe.push_back("z2_truthBorn_m");
            hehe.push_back("z1_truthBorn_y");
            hehe.push_back("z2_truthBorn_y");
            hehe.push_back("llll_truthBorn_m");
            hehe.push_back("zzjj_rel_pt_truthBorn");
            hehe.push_back("centrarity_truthBorn");
            hehe.push_back("pass_truthBorn_cut");
            hehe.push_back("pass_truthBorn_SR");
            hehe.push_back("pass_truthBorn_NCT_JN");
            hehe.push_back("pass_truthBorn_CT_NJN");
            hehe.push_back("pass_truthBorn_NCT_NJN");

            ana.Snapshot("SM4L_Nominal", out_anaed_tree, hehe);
        }
}

int main()
{
    char* in_file1 = "output/preAna_out/005_rest/mc16_13TeV.344295.Sherpa_Zee_4lMassFilter40GeV8GeV.NTUP_SM4l.r10201_p3652.root";
    char* in_file2 = "output/preAna_out/005_rest/mc16_13TeV.344295.Sherpa_Zee_4lMassFilter40GeV8GeV.NTUP_SM4l.r10724_p3652.root";
    char* in_file3 = "output/preAna_out/005_rest/mc16_13TeV.344295.Sherpa_Zee_4lMassFilter40GeV8GeV.NTUP_SM4l.r9364_p3652.root";
    char* out_tree1  = "output/dbg/aaa.root";
    analysis(in_file1, in_file2, in_file3, out_tree1);
}
