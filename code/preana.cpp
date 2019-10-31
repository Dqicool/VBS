//event selection and weight normalisation

#include"genAna.h"
#include"cutDet.h"
//#define debug
double getLumi(const char* infile)
{
    ROOT::RDataFrame m("MetaDataTree", infile);
    auto prwlumi = (m.Take<double>("prwLuminosity").GetValue())[0];
    return prwlumi;
}

void preAna(const char* infile ,const char* outfile, double lumi)
{
    ROOT::EnableImplicitMT(24);
    ROOT::RDataFrame d("SM4L_Nominal", infile);

    auto proWeight = [&](double weight){
        return weight/lumi;
    };

    auto baseline = [](std::vector<int> lepton_pass_ind, std::vector<int> jet_pass_ind){

        bool ret = lepton_pass_ind.size() >= 4 && jet_pass_ind.size() >= 2;
        return ret;
    };

    auto d1 = d.Define("jet_pass_ind", jetSel, {"jet_pt", "jet_eta"}).
                Define("jet_true_pass_ind", jetSel, {"jet_truthBorn_pt", "jet_truthBorn_eta"}).
                Define("lepton_pass_ind", lepSel, {"lepton_pt", "lepton_eta", "lepton_d0sig", "lepton_z0sinTheta", "lepton_particleID", "lepton_isLoose"}).
                Filter(baseline, {"lepton_pass_ind", "jet_pass_ind"}).
                Filter(leptonPtSel, {"lepton_pt","lepton_pass_ind"}).
                Define("NormWeight", proWeight, {"weight"}).
                Define("jet_pass_pt", fpass_property, {"jet_pass_ind", "jet_pt"}).
                Define("jet_pass_eta", fpass_property, {"jet_pass_ind", "jet_eta"}).
                Define("jet_pass_m", fpass_property, {"jet_pass_ind", "jet_m"}).
                Define("jet_pass_phi", fpass_property, {"jet_pass_ind", "jet_phi"}).
                Define("jet_pass_Jvt", fpass_property, {"jet_pass_ind", "jet_Jvt"}).
                Define("jet_pass_n", passN, {"jet_pass_ind"}).
                Define("lepton_pass_pt", fpass_property, {"lepton_pass_ind", "lepton_pt"}).
                Define("lepton_pass_eta", fpass_property, {"lepton_pass_ind", "lepton_eta"}).
                Define("lepton_pass_d0sig", fpass_property, {"lepton_pass_ind", "lepton_d0sig"}).
                Define("lepton_pass_z0sinTHeta", fpass_property, {"lepton_pass_ind", "lepton_z0sinTheta"}).
                Define("lepton_pass_particleID", ipass_property, {"lepton_pass_ind", "lepton_particleID"}).
                Define("lepton_pass_isLoose", cpass_property, {"lepton_pass_ind", "lepton_isLoose"}).
                Define("lepton_pass_isTight", cpass_property, {"lepton_pass_ind", "lepton_isTight"}).
                Define("lepton_pass_d0raw", fpass_property, {"lepton_pass_ind", "lepton_d0raw"}).
                Define("lepton_pass_charge", fpass_property, {"lepton_pass_ind", "lepton_charge"}).
                Define("lepton_pass_m", fpass_property, {"lepton_pass_ind", "lepton_m"}).
                Define("lepton_pass_phi", fpass_property, {"lepton_pass_ind", "lepton_phi"}).
                Define("lepton_pass_n", passN, {"lepton_pass_ind"});

    if(d.HasColumn("fid_weights")){
        d1 = d1.Define("NormWeight_true", proWeight, {"fid_weights"});
    }

    auto hehe = d1.GetColumnNames();
    hehe.erase(hehe.begin()+22, hehe.end());
    hehe.push_back("dijet_mjj");
    if(d.HasColumn("dijet_mjj_truthBorn")){
        hehe.push_back("dijet_mjj_truthBorn");
    }
    d1.Snapshot("SM4L_Nominal", outfile, hehe);
}
#ifndef debug
int main(int argc, char** argv){
    const char* infile = argv[1];
    const char* outfile = argv[2];
    preAna(infile, outfile, getLumi(infile));
}
#else 
int main(){
    const char* infile ="/data/999_all/mc16_13TeV.364250.Sherpa_222_NNPDF30NNLO_llll.deriv.DAOD_HIGG2D1.e5894_s3126_r9364_p3654.root";
    const char* outfile = "/output/dbg/bbb.root";
    preAna(infile, outfile, getLumi(infile));
}
#endif
