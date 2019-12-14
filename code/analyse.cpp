//claculation of interesting observables
#include "genAna.h"
#include "cutDet.h"

#define MT
//#define debug
//#define PRESERVEALL


void analyse(char* in_file1,char* in_file2, char* in_file3, char* out_anaed_tree)
{
    #ifdef MT
    ROOT::EnableImplicitMT();
    #endif
    ROOT::RDataFrame dframe("SM4L_Nominal", {in_file1, in_file2, in_file3});

    //analyse
        auto ana=dframe.//0
                        Define("jet_pass_ind", jetSel, {"jet_pt", "jet_eta", "jet_Jvt"}).
                        //1
                        Define("lepton_pass_ind", lepSel, {"lepton_pt", "lepton_eta", "lepton_d0sig", "lepton_z0sinTheta", "lepton_particleID", "lepton_passesIsolation"}).
                        //2
                        Define("pass_det",baseline, {"lepton_pass_ind", "jet_pass_ind"}).
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
                        Define("jet_pass_lorentz", getLorentz, {"jet_pass_pt", "jet_pass_eta", "jet_pass_phi", "jet_pass_m"}).
                        //23
                        Define("lepton_pass_lorentz", getLorentz, {"lepton_pass_pt", "lepton_pass_eta", "lepton_pass_phi", "lepton_pass_m"}).
                        //24
                        Define("j1_j2_index", getJ1J2Ind, {"jet_pass_lorentz"}).
                        //25
                        Define("jj_m", getMjj, {"jet_pass_lorentz", "j1_j2_index"}).
                        //26
                        Define("njet_inbetween",GetNJBetween, {"jet_pass_lorentz", "j1_j2_index"}).
                        //27
                        Define("jj_delta_phi", getJJDelPhi, {"jet_pass_lorentz", "j1_j2_index"}).
                        //28
                        Define("jj_delta_y",getJJDelY,  {"jet_pass_lorentz", "j1_j2_index"}).
                        //29
                        Define("z1_z2_index",getZ1Z2Index, {"lepton_pass_particleID", "lepton_pass_charge", "lepton_pass_lorentz"}).

                        Define("z1_index", getZ1Ind, {"lepton_pass_lorentz", "z1_z2_index"}).

                        Define("z2_index", getZ2Ind, {"lepton_pass_lorentz", "z1_z2_index"}).
                        //30
                        Define("llll_m", getM4l, {"lepton_pass_lorentz", "z1_z2_index"}).
                        //31
                        Define("z1_m", getZ1M, {"lepton_pass_lorentz", "z1_z2_index"}).
                        //32
                        Define("z2_m", getZ2M, {"lepton_pass_lorentz", "z1_z2_index"}).
                        //33
                        Define("pt_balance",getPtBala, {"jet_pass_lorentz", "j1_j2_index", "lepton_pass_lorentz", "z1_z2_index"}).
                        //34
                        Define("centrarity", getCentra, {"jet_pass_lorentz", "j1_j2_index", "lepton_pass_lorentz", "z1_z2_index"}).
                        //35
                        Define("pass_cut", pass_cut, {"jj_m", "jj_delta_y", "pt_balance", "z1_m", "z2_m", "llll_m"}).
                        //36
                        Define("pass_SR", pass_SR,{"pass_cut", "njet_inbetween", "centrarity"}).
                        //37
                        Define("pass_CT_NJN", pass_CT_no_JN,{"pass_cut", "njet_inbetween", "centrarity"}).
                        //38
                        Define("pass_NCT_JN", pass_no_CT_JN, {"pass_cut", "njet_inbetween", "centrarity"}).
                        //39
                        Define("pass_NCT_NJN", pass_no_CT_no_JN, {"pass_cut", "njet_inbetween", "centrarity"});

        if(dframe.HasColumn("fid_weight")){
            ana =   ana.//40
                        Define("NormWeight_true", proWeight, {"fid_weight"}).
                        //41
                        Define("jet_truthBorn_pass_ind", jetTrueSel, {"jet_truthBorn_pt", "jet_truthBorn_eta"}).
                        //42
                        Define("lepton_truthBorn_pass_ind", lepTrueSel, {"lepton_truthBorn_pt", "lepton_truthBorn_eta", "lepton_truthBorn_particleID"}).
                        //43
                        Define("pass_truthBorn_det",baseline, {"lepton_truthBorn_pass_ind", "jet_truthBorn_pass_ind"}).
                        //44
                        Define("jet_truthBorn_pass_pt", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_pt"}).
                        //45
                        Define("jet_truthBorn_pass_eta", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_eta"}).
                        //46
                        Define("jet_truthBorn_pass_m", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_m"}).
                        //47
                        Define("jet_truthBorn_pass_phi", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_phi"}).
                        //48
                        Define("jet_truthBorn_pass_n", passN, {"jet_truthBorn_pass_ind"}).
                        //49
                        Define("lepton_truthBorn_pass_pt", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_pt"}).
                        //50
                        Define("lepton_truthBorn_pass_eta", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_eta"}).
                        //51
                        Define("lepton_truthBorn_pass_particleID", ipass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_particleID"}).
                        //52
                        Define("lepton_truthBorn_pass_charge", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_charge"}).
                        //53
                        Define("lepton_truthBorn_pass_m", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_m"}).
                        //54
                        Define("lepton_truthBorn_pass_phi", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_phi"}).
                        //55
                        Define("lepton_truthBorn_pass_n", passN, {"lepton_truthBorn_pass_ind"}).
                        //56
                        Define("jet_truthBorn_pass_lorentz", getLorentz, {"jet_truthBorn_pass_pt", "jet_truthBorn_pass_eta", "jet_truthBorn_pass_phi", "jet_truthBorn_pass_m"}).
                        //57
                        Define("lepton_truthBorn_pass_lorentz", getLorentz, {"lepton_truthBorn_pass_pt", "lepton_truthBorn_pass_eta", "lepton_truthBorn_pass_phi", "lepton_truthBorn_pass_m"}).
                        //58
                        Define("j1_j2_truthBorn_index", getJ1J2Ind, {"jet_truthBorn_pass_lorentz"}).
                        //59
                        Define("jj_truthBorn_m", getMjj, {"jet_truthBorn_pass_lorentz", "j1_j2_truthBorn_index"}).
                        //60
                        Define("njet_truthBorn_inbetween",GetNJBetween, {"jet_truthBorn_pass_lorentz", "j1_j2_truthBorn_index"}).
                        //61
                        Define("jj_truthBorn_delta_phi", getJJDelPhi, {"jet_truthBorn_pass_lorentz", "j1_j2_truthBorn_index"}).
                        //62
                        Define("jj_truthBorn_delta_y",getJJDelY,  {"jet_truthBorn_pass_lorentz", "j1_j2_truthBorn_index"}).
                        //63
                        Define("z1_z2_truthBorn_index",getZ1Z2Index, {"lepton_truthBorn_pass_particleID", "lepton_truthBorn_pass_charge", "lepton_truthBorn_pass_lorentz"}).

                        Define("z1_truthBorn_index", getZ1Ind, {"lepton_truthBorn_pass_lorentz", "z1_z2_truthBorn_index"}).

                        Define("z2_truthBorn_index", getZ2Ind, {"lepton_truthBorn_pass_lorentz", "z1_z2_truthBorn_index"}).
                        //64
                        Define("llll_truthBorn_m", getM4l, {"lepton_truthBorn_pass_lorentz", "z1_z2_truthBorn_index"}).
                        //65
                        Define("z1_truthBorn_m", getZ1M, {"lepton_truthBorn_pass_lorentz", "z1_z2_truthBorn_index"}).
                        //66
                        Define("z2_truthBorn_m", getZ2M, {"lepton_truthBorn_pass_lorentz", "z1_z2_truthBorn_index"}).
                        //67
                        Define("pt_truthBorn_balance",getPtBala, {"jet_truthBorn_pass_lorentz", "j1_j2_truthBorn_index", "lepton_truthBorn_pass_lorentz", "z1_z2_truthBorn_index"}).
                        //68
                        Define("centrarity_truthBorn", getCentra, {"jet_truthBorn_pass_lorentz", "j1_j2_truthBorn_index", "lepton_truthBorn_pass_lorentz", "z1_z2_truthBorn_index"}).
                        //69
                        Define("pass_truthBorn_cut", pass_cut, {"jj_truthBorn_m", "jj_truthBorn_delta_y", "pt_truthBorn_balance", "z1_truthBorn_m", "z2_truthBorn_m", "llll_truthBorn_m"}).
                        //70
                        Define("pass_truthBorn_SR", pass_SR,{"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"}).
                        //71
                        Define("pass_truthBorn_CT_NJN", pass_CT_no_JN,{"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"}).
                        //72
                        Define("pass_truthBorn_NCT_JN", pass_no_CT_JN, {"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"}).
                        //73
                        Define("pass_truthBorn_NCT_NJN", pass_no_CT_no_JN, {"pass_truthBorn_cut", "njet_truthBorn_inbetween", "centrarity_truthBorn"});
        }
    //save tree
        auto hehe = ana.GetColumnNames();
        if (ana.HasColumn("fid_weight")){
            hehe.erase(hehe.begin() + 78 , hehe.end());
            hehe.erase(hehe.begin()+ 65, hehe.begin()+66);
            hehe.erase(hehe.begin()+ 58, hehe.begin()+61);
            hehe.erase(hehe.begin()+ 29, hehe.begin()+30);
            hehe.erase(hehe.begin()+ 22, hehe.begin()+24);

            hehe.push_back("lepton_n");
            hehe.push_back("jet_n");
            #ifndef PRESERVEALL
            ana.Filter("pass_det == 1 || pass_truthBorn_det == 1").Snapshot("SM4L_Nominal", out_anaed_tree, hehe);
            #else
            ana.Snapshot("SM4L_Nominal", out_anaed_tree, hehe);
            #endif
        }
        else{
            hehe.erase(hehe.begin()+ 29, hehe.begin()+30);
            hehe.erase(hehe.begin()+ 22, hehe.begin()+24);

            hehe.push_back("lepton_n");
            hehe.push_back("jet_n");
            #ifndef PRESERVEALL
            ana.Filter("pass_det == 1").Snapshot("SM4L_Nominal", out_anaed_tree, hehe);
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
    char* in_file1 = "data/999_all/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r10201_r10210_p3654.root";
    char* in_file2 = "data/999_all/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r10724_r10726_p3654.root";
    char* in_file3 = "data/999_all/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r9364_r9315_p3654.root";
    char* out_tree = "debug.root";
    analyse(in_file1, in_file2, in_file3, out_tree);
}
#endif