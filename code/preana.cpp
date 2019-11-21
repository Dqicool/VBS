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
        return weight;
    };



    auto d1 = d.Define("jet_pass_ind", jetSel, {"jet_pt", "jet_eta"}).
                Define("lepton_pass_ind", lepSel, {"lepton_pt", "lepton_eta", "lepton_d0sig", "lepton_z0sinTheta", "lepton_particleID", "lepton_passesIsolation"}).
                Define("pass_det",baseline, {"lepton_pass_ind", "jet_pass_ind", "lepton_pt"}).
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

    if(d.HasColumn("fid_weight")){
        d1 = d1.Define("NormWeight_true", proWeight, {"fid_weight"}).
                Define("jet_truthBorn_pass_ind", jetSel, {"jet_truthBorn_pt", "jet_truthBorn_eta"}).
                Define("lepton_truthBorn_pass_ind", lepTrueSel, {"lepton_truthBorn_pt", "lepton_truthBorn_eta", "lepton_truthBorn_particleID"}).
                Define("pass_det_truthBorn",baseline, {"lepton_truthBorn_pass_ind", "jet_truthBorn_pass_ind", "lepton_truthBorn_pt"}).
                Define("jet_truthBorn_pass_pt", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_pt"}).
                Define("jet_truthBorn_pass_eta", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_eta"}).
                Define("jet_truthBorn_pass_m", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_m"}).
                Define("jet_truthBorn_pass_phi", fpass_property, {"jet_truthBorn_pass_ind", "jet_truthBorn_phi"}).
                Define("jet_truthBorn_pass_n", passN, {"jet_truthBorn_pass_ind"}).
                Define("lepton_truthBorn_pass_pt", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_pt"}).
                Define("lepton_truthBorn_pass_eta", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_eta"}).
                Define("lepton_truthBorn_pass_particleID", ipass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_particleID"}).
                Define("lepton_truthBorn_pass_charge", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_charge"}).
                Define("lepton_truthBorn_pass_m", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_m"}).
                Define("lepton_truthBorn_pass_phi", fpass_property, {"lepton_truthBorn_pass_ind", "lepton_truthBorn_phi"}).
                Define("lepton_truthBorn_pass_n", passN, {"lepton_truthBorn_pass_ind"});
    }

    auto hehe = d1.GetColumnNames();
    if(d.HasColumn("fid_weight")){
        auto d2 = d1.Filter("pass_det || pass_det_truthBorn");
        hehe.erase(hehe.begin()+38, hehe.end());
        hehe.push_back("lepton_n");
        hehe.push_back("jet_n");
        d2.Snapshot("SM4L_Nominal", outfile, hehe);
    }
    else
    {
        auto d2 = d1.Filter("pass_det");
        hehe.erase(hehe.begin()+22, hehe.end());
        hehe.push_back("lepton_n");
        hehe.push_back("jet_n");
        d2.Snapshot("SM4L_Nominal", outfile, hehe);
    }


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
