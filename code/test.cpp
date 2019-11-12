#include "genAna.h"

void test()
{
    ROOT::RDataFrame df("SM4L_Nominal", "output/analyse_out/999_all/364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.root");
    auto dg = df.Filter("pass_cut == 0");
    auto h = dg.Histo1D({"test","", 400, 0,1000}, "m4l");
    h->Draw();
    
}