#include "analambda.h"
#include "genAna.h"
int main(){
    ROOT::RDataFrame dframe("SM4L_Nominal", {"data/200_vbsf/mc16_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.deriv.DAOD_HIGG2D1.e5500_s3126_r10201_p3654.root", "data/200_vbsf/mc16_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.deriv.DAOD_HIGG2D1.e5500_s3126_r10724_p3654.root", "data/200_vbsf/mc16_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.deriv.DAOD_HIGG2D1.e5500_s3126_r9364_p3654.root"});
    auto f = dframe.Filter("lepton_n > 6");
    f.Define("Z1Z2Index", {"lepton_"})
}
