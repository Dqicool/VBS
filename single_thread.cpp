#include "anaMain.h"

int main()
{
    TFile* in_tree_file = TFile::Open("/mnt/MainShare/Projects/Qichen/VBS/data/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r10201_r10210_p3654.root");
    TTree* in_tree  = (TTree*)in_tree_file->Get("SM4L_Nominal");
    TFile* out_tree_file = TFile::Open("/mnt/MainShare/Projects/Qichen/VBS/output/85M.root", "recreate");
    TTree* out_tree = new TTree("out_tree", "processed tree");

    struct single_arg args{
        in_tree,
        out_tree,
        0,
        in_tree->GetEntries(),
    };

    analysis((void*)&args);
    in_tree_file->Close();
    out_tree_file->Write();
    return 0;
}
