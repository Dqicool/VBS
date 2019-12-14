#include "genAna.h"
#include "cutDet.h"


void prodout(){
    //chain signals 
    ROOT::EnableImplicitMT();
    ROOT::RDataFrame df("SM4L_Nominal", 
    {"data/999_all/mc16_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.deriv.DAOD_HIGG2D1.e5500_s3126_r10201_p3654.root",
    "data/999_all/mc16_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.deriv.DAOD_HIGG2D1.e5500_s3126_r10724_p3654.root",
    "data/999_all/mc16_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.deriv.DAOD_HIGG2D1.e5500_s3126_r9364_p3654.root",
    "data/999_all/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r10201_r10210_p3654.root",
    "data/999_all/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r10724_r10726_p3654.root",
    "data/999_all/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r9364_r9315_p3654.root"});

    //analysis
    auto ana=df.//0
        Define("jet_pass_ind", jetSel, {"jet_pt", "jet_eta"}).
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

    //cutflags
    auto cut = ana.Define("cut_base", [](int jet_n, int lepton_n){return jet_n>=2 && lepton_n >= 4;}, {"jet_n", "lepton_n"})
            .Define("cut_jet_det",[](int jet_pass_n){return jet_pass_n >= 2;}, {"jet_pass_n"})
            .Define("cut_mjj", [](double jj_m){return jj_m > 300e3;}, {"jj_m"})
            .Define("cut_jjdely", [](double jj_delta_y){return (jj_delta_y > 2 || jj_delta_y < -2) && jj_delta_y > -999;}, {"jj_delta_y"})
            .Define("cut_lep_det", [](int lepton_pass_n){return lepton_pass_n >= 4;}, {"lepton_pass_n"})
            .Define("cut_lep_2_pairs", [](double z1_energy, double z2_energy){return z1_energy > 0 && z2_energy > 0;}, {"z1_energy", "z2_energy"})
            .Define("cut_z_m" ,[](double z1_m, double z2_m){return z1_m > 66e3 && z1_m < 116e3 && z2_m > 66e3 && z2_m < 116e3;},{"z1_m","z2_m"});

    //save files
    auto col_name = cut.GetColumnNames();
            col_name.erase(col_name.begin()+67,col_name.end());
            col_name.erase(col_name.begin()+36, col_name.begin()+37);
            col_name.erase(col_name.begin()+35, col_name.begin()+36);
            col_name.erase(col_name.begin()+23, col_name.begin()+24);
            
            cut.Snapshot("SM4L_Nominal", "D_output.root", col_name);
}

#define BEN
//#define HAR
#define DON

void compares(){
    bool Dcut[7], Hcut[7], Bcut[7];
    double  H_mjj,  D_mjj;
    float B_mjj;
    double weight;

#ifdef HAR
    auto Hf = TFile::Open("output_H.root","read");
    TTree* Ht = (TTree*)Hf->Get("SM4L_Nominal");
    auto n_h = Ht->GetEntries();
#endif
#ifdef BEN
    auto Bf = TFile::Open("B_output.root", "read");
    TTree* Bt = (TTree*)Bf->Get("signal_tree");
    auto n_b = Bt->GetEntries();
    Bt->SetBranchAddress("cut_1", &Bcut[0]);
    Bt->SetBranchAddress("cut_2", &Bcut[1]);
    Bt->SetBranchAddress("cut_3",&Bcut[2]);
    Bt->SetBranchAddress("cut_4",&Bcut[3]);
    Bt->SetBranchAddress("cut_5", &Bcut[4]);
    Bt->SetBranchAddress("cut_6", &Bcut[5]);
    Bt->SetBranchAddress("cut_7", &Bcut[6]);

    Bt->SetBranchAddress("m_j1j2",&B_mjj);
    Bt->SetBranchAddress("weight", &weight);
#endif
#ifdef DON
    auto Df = TFile::Open("D_output.root","read");
    TTree* Dt = (TTree*)Df->Get("SM4L_Nominal");
    auto n_d = Dt->GetEntries();
    Dt->SetBranchAddress("cut_base", &Dcut[0]);
    Dt->SetBranchAddress("cut_jet_det", &Dcut[1]);
    Dt->SetBranchAddress("cut_mjj",&Dcut[2]);
    Dt->SetBranchAddress("cut_jjdely",&Dcut[3]);
    Dt->SetBranchAddress("cut_lep_det", &Dcut[4]);
    Dt->SetBranchAddress("cut_lep_2_pairs", &Dcut[5]);
    Dt->SetBranchAddress("cut_z_m", &Dcut[6]);

    Dt->SetBranchAddress("jj_m",&D_mjj);

#endif
    double div_evts=0;
    for (ulong i=0;i<n_d;i++){

        Bt->GetEntry(i);
        Dt->GetEntry(i);
        if((Dcut[0] && !Bcut[0]) || (!Dcut[0] && Bcut[0])){
            cout<<"DIVERGENCE in cut 0 "<< D_mjj<<"\t"<< B_mjj<<endl;
            div_evts += weight;
        }

    }
    cout<<"div numbers "<<div_evts<<endl;
}

int main(){
    //prodout();
    cout<<"start"<<endl;
    compares();
}
