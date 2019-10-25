//event selection and weight normalisation

#include"genAna.h"
//#define debug
double getLumi(const char* infile)
{
    ROOT::RDataFrame m("MetaDataTree", infile);
    auto prwlumi = (m.Take<double>("prwLuminosity").GetValue())[0];
    return prwlumi;
}
void preAna(const char* infile ,const char* outfile, double lumi)
{
    ROOT::EnableImplicitMT();
    ROOT::RDataFrame d("SM4L_Nominal", infile);

    auto proWeight = [&](double weight){
        return weight/lumi;
    };
    auto baseline = [](std::vector<float> lepton_pt, std::vector<float> jet_pt, char passReco_any){
        auto ret = lepton_pt.size() >=4 && jet_pt.size() >= 2 && passReco_any>0;
        return ret;
    };
    auto d2 = d.Filter(baseline, {"lepton_pt","jet_pt", "passReco_any"});
    auto d3= d2.Define("NormWeight", proWeight, {"weight"});
                //Define("NormfidWeight", proWeight, {"fid_weight"});
    
    d3.Snapshot("SM4L_Nominal", outfile);
}
#ifndef debug
int main(int argc, char** argv){
    const char* infile = argv[1];
    const char* outfile = argv[2];
    preAna(infile, outfile, getLumi(infile));
}
#else 
int main(){
    const char* infile ="";
    const char* outfile = "";
    preAna(infile, outfile, getLumi(infile));
}
#endif
