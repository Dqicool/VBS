//claculation of interesting observables

#include "analambda.h"
#include "cutDet.h"

#define MT
//#define debug
//#define PRESERVEALL

#ifdef debug
#undef MT
#endif

void analyse(char* in_file1,char* in_file2, char* in_file3, char* out_anaed_tree)
{
    #ifdef MT
    ROOT::EnableImplicitMT(24);
    #endif
    ROOT::RDataFrame dframe("SM4L_Nominal", {in_file1, in_file2, in_file3});

    //analyse
        auto ana=dframe.//0
                        Define("jet_pass_ind", jetSel, {"jet_pt", "jet_eta"}).
                        //1
                        Define("lepton_pass_ind", lepSel, {"lepton_pt", "lepton_eta", "lepton_d0sig", "lepton_z0sinTheta", "lepton_particleID", "lepton_passesIsolation"}).
                        //2
                        Define("pass_det",baseline, {"lepton_pass_ind", "jet_pass_ind", "lepton_pt"}).
                        //3
                        Define("NormWeight", proWeight, {"weight"}).
                        //4
                        Define("jet_pass_pt", fpass_property, {"jet_pass_ind", "jet_pt"}).
                        //5
                        Define("jet_pass_eta", fpass_property, {"jet_pass_ind", "jet_eta"}).
                        //6
                        Define("jet_pass_m", fpass_property, {"jet_pass_ind", "jet_m"}).
                        //7
                        Define("jet_pass_phi", fpass_property, {"jet_pass_ind", "jet_phi"}).
                        //8
                        Define("jet_pass_Jvt", fpass_property, {"jet_pass_ind", "jet_Jvt"}).
                        //9
                        Define("jet_pass_n", passN, {"jet_pass_ind"}).
                        //10
                        Define("lepton_pass_pt", fpass_property, {"lepton_pass_ind", "lepton_pt"}).
                        //11
                        Define("lepton_pass_eta", fpass_property, {"lepton_pass_ind", "lepton_eta"}).
                        //12
                        Define("lepton_pass_d0sig", fpass_property, {"lepton_pass_ind", "lepton_d0sig"}).
                        //13
                        Define("lepton_pass_z0sinTHeta", fpass_property, {"lepton_pass_ind", "lepton_z0sinTheta"}).
                        //14
                        Define("lepton_pass_particleID", ipass_property, {"lepton_pass_ind", "lepton_particleID"}).
                        //15
                        Define("lepton_pass_isLoose", cpass_property, {"lepton_pass_ind", "lepton_isLoose"}).
                        //16
                        Define("lepton_pass_isTight", cpass_property, {"lepton_pass_ind", "lepton_isTight"}).
                        //17
                        Define("lepton_pass_d0raw", fpass_property, {"lepton_pass_ind", "lepton_d0raw"}).
                        //18
                        Define("lepton_pass_charge", fpass_property, {"lepton_pass_ind", "lepton_charge"}).
                        //19
                        Define("lepton_pass_m", fpass_property, {"lepton_pass_ind", "lepton_m"}).
                        //20
                        Define("lepton_pass_phi", fpass_property, {"lepton_pass_ind", "lepton_phi"}).
                        //21
                        Define("lepton_pass_n", passN, {"lepton_pass_ind"}).
                        //22
                        Define("jet_pass_energy",jet_energy,{"jet_pass_m","jet_pass_eta","jet_pass_pt"}).
                        //23
                        Define("jet_pass_px_py_pz",jet_px_py_pz, {"jet_pass_eta","jet_pass_pt","jet_pass_phi"}).
                        //24
                        Define("j1_j2_index", j1_j2_index, {"jet_pass_pt", "jet_pass_px_py_pz", "jet_pass_energy"}).
                        //25
                        Define("j1_y", j1_y, {"jet_pass_px_py_pz","jet_pass_energy","j1_j2_index"}).
                        //26
                        Define("j2_y", j2_y, {"jet_pass_px_py_pz","jet_pass_energy","j1_j2_index"}).
                        //27
                        Define("jj_m", jj_m, {"jet_pass_energy", "jet_pass_px_py_pz", "j1_j2_index"}).
                        //28
                        Define("njet_inbetween",nJetInBetween,{"jet_pass_eta", "jet_pass_phi", "j1_j2_index", "jet_pass_px_py_pz", "jet_pass_energy"}).
                        //29
                        Define("jj_delta_phi", jj_delta_phi, {"jet_pass_phi","j1_j2_index", "j1_y", "j2_y"}).
                        //30
                        Define("jj_delta_y",jj_delta_y, {"j1_y","j2_y"}).
                        //31
                        Define("jj_product_y",jj_product_y,{"j1_y","j2_y"}).
                        //32
                        Define("j1_pt", j1_pt, {"jet_pass_pt","j1_j2_index"}).
                        //33
                        Define("j2_pt", j2_pt, {"jet_pass_pt","j1_j2_index"}).
                        //34
                        Define("lepton_pass_energy",lepton_energy,{"lepton_pass_m","lepton_pass_eta","lepton_pass_pt"}).
                        //35
                        Define("lepton_pass_px_py_pz",lepton_px_py_pz, {"lepton_pass_eta","lepton_pass_pt","lepton_pass_phi"}).
                        //36
                        Define("z1_z2_index",z1_z2_ind, {"lepton_pass_particleID", "lepton_pass_charge", "lepton_pass_eta", "lepton_pass_phi", "lepton_pass_energy", "lepton_pass_px_py_pz"}).
                        //37
                        Define("z1_index",z1_index, {"z1_z2_index"}).
                        //38
                        Define("z2_index",z2_index,  {"z1_z2_index"}).
                        //39
                        Define("z1_px_py_pz",z_px_py_pz,{"lepton_pass_px_py_pz", "z1_index"}).
                        //40
                        Define("z2_px_py_pz",z_px_py_pz,{"lepton_pass_px_py_pz", "z2_index"}).
                        //41
                        Define("z1_energy", z_energy, {"lepton_pass_energy", "z1_index"}).
                        //42
                        Define("z2_energy", z_energy, {"lepton_pass_energy", "z2_index"}).
                        //43
                        Define("z1_pt",z_pt,{"lepton_pass_px_py_pz", "z1_index"}).
                        //44
                        Define("z2_pt",z_pt,{"lepton_pass_px_py_pz", "z2_index"}).
                        //45
                        Define("z1_m", z_m, {"z1_index","lepton_pass_px_py_pz", "lepton_pass_energy"}).
                        //46
                        Define("z2_m", z_m, {"z2_index","lepton_pass_px_py_pz", "lepton_pass_energy"}).
                        //47
                        Define("z1_y", z_y, {"z1_px_py_pz", "z1_energy"}).
                        //48
                        Define("z2_y", z_y, {"z2_px_py_pz", "z2_energy"}).
                        //49
                        Define("llll_index",llll_index,{"z1_index","z2_index"}).
                        //50
                        Define("llll_px_py_pz",llll_px_py_pz, {"lepton_pass_px_py_pz","llll_index"}).
                        //51
                        Define("llll_m", llll_m, {"lepton_pass_energy", "lepton_pass_px_py_pz", "llll_index"}).
                        //52
                        Define("llll_pt",llll_pt,{"llll_px_py_pz"}).
                        //53
                        Define("zzjj_rel_pt",zzjj_rel_pt, {"z1_pt","z2_pt","j1_pt","j2_pt","z1_px_py_pz","z2_px_py_pz","jet_pass_px_py_pz","j1_j2_index"}).
                        //54
                        Define("centrarity", centrarity, {"jet_pass_px_py_pz", "jet_pass_energy","j1_j2_index", "z1_px_py_pz", "z2_px_py_pz", "z1_energy", "z2_energy", "jj_delta_y"}).
                        //55
                        Define("pass_cut", pass_cut, {"j1_pt", "j2_pt", "llll_m", "jj_m",  "jj_product_y",  "jj_delta_y",  "zzjj_rel_pt",  "z1_m",  "z2_m"}).
                        //56
                        Define("pass_SR", pass_SR,{"pass_cut", "njet_inbetween", "centrarity"}).
                        //57
                        Define("pass_CT_NJN", pass_CT_no_JN,{"pass_cut", "njet_inbetween", "centrarity"}).
                        //58
                        Define("pass_NCT_JN", pass_no_CT_JN, {"pass_cut", "njet_inbetween", "centrarity"}).
                        //59
                        Define("pass_NCT_NJN", pass_no_CT_no_JN, {"pass_cut", "njet_inbetween", "centrarity"});

        if(dframe.HasColumn("fid_weight")){
            ana =   ana.//60
                        Define("NormWeight_true", proWeight, {"fid_weight"}).
                        //61
                        Define("jet_truthBorn_pass_ind", jetSel, {"jet_truthBorn_pt", "jet_truthBorn_eta"}).
                        //62
                        Define("lepton_truthBorn_pass_ind", lepTrueSel, {"lepton_truthBorn_pt", "lepton_truthBorn_eta", "lepton_truthBorn_particleID"}).
                        //63
                        Define("pass_det_truthBorn",baseline, {"lepton_truthBorn_pass_ind", "jet_truthBorn_pass_ind", "lepton_truthBorn_pt"}).
                        //64
                        Define("jet_truthBorn_pass_pt", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_pt"}).
                        //65
                        Define("jet_truthBorn_pass_eta", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_eta"}).
                        //66
                        Define("jet_truthBorn_pass_m", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_m"}).
                        //67
                        Define("jet_truthBorn_pass_phi", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_phi"}).
                        //68
                        Define("jet_truthBorn_pass_n", passN, {"jet_truthBorn_pass_ind"}).
                        //69
                        Define("lepton_truthBorn_pass_pt", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_pt"}).
                        //70
                        Define("lepton_truthBorn_pass_eta", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_eta"}).
                        //71
                        Define("lepton_truthBorn_pass_particleID", ipass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_particleID"}).
                        //72
                        Define("lepton_truthBorn_pass_charge", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_charge"}).
                        //73
                        Define("lepton_truthBorn_pass_m", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_m"}).
                        //74
                        Define("lepton_truthBorn_pass_phi", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_phi"}).
                        //75
                        Define("lepton_truthBorn_pass_n", passN, {"lepton_truthBorn_pass_ind"}).
                        //76
                        Define("jet_truthBorn_pass_energy",jet_energy,{"jet_truthBorn_pass_m","jet_truthBorn_pass_eta","jet_truthBorn_pass_pt"}).
                        //77
                        Define("jet_truthBorn_pass_px_py_pz",jet_px_py_pz, {"jet_truthBorn_pass_eta","jet_truthBorn_pass_pt","jet_truthBorn_pass_phi"}).
                        //78
                        Define("j1_j2_truthBorn_index", j1_j2_index, {"jet_truthBorn_pass_pt", "jet_truthBorn_pass_px_py_pz", "jet_truthBorn_pass_energy"}).
                        //79
                        Define("j1_truthBorn_y", j1_y, {"jet_truthBorn_pass_px_py_pz","jet_truthBorn_pass_energy","j1_j2_truthBorn_index"}).
                        //80
                        Define("j2_truthBorn_y", j2_y, {"jet_truthBorn_pass_px_py_pz","jet_truthBorn_pass_energy","j1_j2_truthBorn_index"}).
                        //81
                        Define("jj_truthBorn_m", jj_m, {"jet_truthBorn_pass_energy", "jet_truthBorn_pass_px_py_pz", "j1_j2_truthBorn_index"}).
                        //82
                        Define("njet_truthBorn_inbetween",nJetInBetween,{"jet_truthBorn_pass_eta", "jet_truthBorn_pass_phi", "j1_j2_truthBorn_index", "jet_truthBorn_pass_px_py_pz", "jet_truthBorn_pass_energy"}).
                        //83
                        Define("jj_truthBorn_delta_phi", jj_delta_phi, {"jet_truthBorn_pass_phi","j1_j2_truthBorn_index", "j1_truthBorn_y", "j2_truthBorn_y"}).
                        //84
                        Define("jj_truthBorn_delta_y",jj_delta_y, {"j1_truthBorn_y","j2_truthBorn_y"}).
                        //85
                        Define("jj_truthBorn_product_y",jj_product_y,{"j1_truthBorn_y","j2_truthBorn_y"}).
                        //86
                        Define("j1_truthBorn_pt", j1_pt, {"jet_truthBorn_pass_pt","j1_j2_truthBorn_index"}).
                        //87
                        Define("j2_truthBorn_pt", j2_pt, {"jet_truthBorn_pass_pt","j1_j2_truthBorn_index"}).
                        //88
                        Define("lepton_truthBorn_pass_energy",lepton_energy,{"lepton_truthBorn_pass_m","lepton_truthBorn_pass_eta","lepton_truthBorn_pass_pt"}).
                        //89
                        Define("lepton_truthBorn_pass_px_py_pz",lepton_px_py_pz, {"lepton_truthBorn_pass_eta","lepton_truthBorn_pass_pt","lepton_truthBorn_pass_phi"}).
                        //90
                        Define("z1_z2_truthBorn_index",z1_z2_ind, {"lepton_truthBorn_pass_particleID", "lepton_truthBorn_pass_charge", "lepton_truthBorn_pass_eta", "lepton_truthBorn_pass_phi", "lepton_truthBorn_pass_energy", "lepton_truthBorn_pass_px_py_pz"}).
                        //91
                        Define("z1_truthBorn_index",z1_index, {"z1_z2_truthBorn_index"}).
                        //92
                        Define("z2_truthBorn_index",z2_index,  {"z1_z2_truthBorn_index"}).
                        //93
                        Define("z1_truthBorn_px_py_pz",z_px_py_pz,{"lepton_truthBorn_pass_px_py_pz", "z1_truthBorn_index"}).
                        //94
                        Define("z2_truthBorn_px_py_pz",z_px_py_pz,{"lepton_truthBorn_pass_px_py_pz", "z2_truthBorn_index"}).
                        //95
                        Define("z1_truthBorn_energy", z_energy, {"lepton_truthBorn_pass_energy", "z1_truthBorn_index"}).
                        //96
                        Define("z2_truthBorn_energy", z_energy, {"lepton_truthBorn_pass_energy", "z2_truthBorn_index"}).
                        //97
                        Define("z1_truthBorn_pt",z_pt,{"lepton_truthBorn_pass_px_py_pz", "z1_truthBorn_index"}).
                        //98
                        Define("z2_truthBorn_pt",z_pt,{"lepton_truthBorn_pass_px_py_pz", "z2_truthBorn_index"}).
                        //99
                        Define("z1_truthBorn_m", z_m, {"z1_truthBorn_index","lepton_truthBorn_pass_px_py_pz", "lepton_truthBorn_pass_energy"}).
                        //100
                        Define("z2_truthBorn_m", z_m, {"z2_truthBorn_index","lepton_truthBorn_pass_px_py_pz", "lepton_truthBorn_pass_energy"}).
                        //101
                        Define("z1_truthBorn_y", z_y, {"z1_truthBorn_px_py_pz", "z1_truthBorn_energy"}).
                        //102
                        Define("z2_truthBorn_y", z_y, {"z2_truthBorn_px_py_pz", "z2_truthBorn_energy"}).
                        //103
                        Define("llll_truthBorn_index",llll_index,{"z1_truthBorn_index","z2_truthBorn_index"}).
                        //104
                        Define("llll_truthBorn_px_py_pz",llll_px_py_pz, {"lepton_truthBorn_pass_px_py_pz","llll_truthBorn_index"}).
                        //105
                        Define("llll_truthBorn_m", llll_m, {"lepton_truthBorn_pass_energy", "lepton_truthBorn_pass_px_py_pz", "llll_truthBorn_index"}).
                        //106
                        Define("llll_truthBorn_pt",llll_pt,{"llll_truthBorn_px_py_pz"}).
                        //107
                        Define("zzjj_rel_pt_truthBorn",zzjj_rel_pt, {"z1_truthBorn_pt","z2_truthBorn_pt","j1_truthBorn_pt","j2_truthBorn_pt","z1_truthBorn_px_py_pz","z2_truthBorn_px_py_pz","jet_truthBorn_pass_px_py_pz","j1_j2_truthBorn_index"}).
                        //108
                        Define("centrarity_truthBorn", centrarity, {"jet_truthBorn_pass_px_py_pz", "jet_truthBorn_pass_energy","j1_j2_truthBorn_index", "z1_truthBorn_px_py_pz", "z2_truthBorn_px_py_pz", "z1_truthBorn_energy", "z2_truthBorn_energy", "jj_truthBorn_delta_y"}).
                        //109
                        Define("pass_truthBorn_cut", pass_cut, {"j1_truthBorn_pt", "j2_truthBorn_pt", "llll_truthBorn_m", "jj_truthBorn_m",  "jj_truthBorn_product_y",  "jj_truthBorn_delta_y",  "zzjj_rel_pt_truthBorn",  "z1_truthBorn_m",  "z2_truthBorn_m"}).
                        //110
                        Define("pass_truthBorn_SR", pass_SR,{"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"}).
                        //111
                        Define("pass_truthBorn_CT_NJN", pass_CT_no_JN,{"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"}).
                        //112
                        Define("pass_truthBorn_NCT_JN", pass_no_CT_JN, {"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"}).
                        //113
                        Define("pass_truthBorn_NCT_NJN", pass_no_CT_no_JN, {"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"});
        }

    //save tree
        if(dframe.HasColumn("fid_weight")){
            auto hehe = ana.GetColumnNames();
            hehe.erase(hehe.begin()+115,hehe.end());
            hehe.erase(hehe.begin()+90, hehe.begin()+91);
            hehe.erase(hehe.begin()+89, hehe.begin()+90);
            hehe.erase(hehe.begin()+77, hehe.begin()+78);
            hehe.erase(hehe.begin()+36, hehe.begin()+37);
            hehe.erase(hehe.begin()+35, hehe.begin()+36);
            hehe.erase(hehe.begin()+23, hehe.begin()+24);

            hehe.push_back("lepton_n");
            hehe.push_back("jet_n");
            #ifndef PRESERVEALL
            ana.Filter("pass_cut || pass_truthBorn_cut").Snapshot("SM4L_Nominal", out_anaed_tree, hehe);
            #else
            ana.Snapshot("SM4L_Nominal", out_anaed_tree, hehe);
            #endif
        }
        else{
            auto hehe = ana.GetColumnNames();
            hehe.erase(hehe.begin()+61, hehe.end());
            hehe.erase(hehe.begin()+36, hehe.begin()+37);
            hehe.erase(hehe.begin()+35, hehe.begin()+36);
            hehe.erase(hehe.begin()+23, hehe.begin()+24);

            hehe.push_back("lepton_n");
            hehe.push_back("jet_n");
            #ifndef PRESERVEALL
            ana.Filter("pass_cut").Snapshot("SM4L_Nominal", out_anaed_tree, hehe);
            #else
            ana.Snapshot("SM4L_Nominal", out_anaed_tree, hehe);
            #endif  
        }
}

#ifndef debug
int main(int argc, char** argv)
{
    char* in_file1 = argv[1];
    char* in_file2 = argv[2];
    char* in_file3 = argv[3];
    char* out_tree = argv[4];

    analyse(in_file1, in_file2, in_file3, out_tree);
}
#else
int main(){
    char* in_file1 = "data/200_vbsf/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r10201_r10210_p3654.root";
    char* in_file2 = "data/200_vbsf/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r10724_r10726_p3654.root";
    char* in_file3 = "data/200_vbsf/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r9364_r9315_p3654.root";
    char* out_tree = "debug.root";
    analyse(in_file1, in_file2, in_file3, out_tree);
}
#endif