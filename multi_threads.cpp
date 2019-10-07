#include "anaMain.h"
#include <pthread.h>
#define NUM_THREADS 24

int main()
{
        char tree_name[] = "out_tree_";
        pthread_t threads[NUM_THREADS];
    //open input file
        TFile* in_tree_file = TFile::Open("/mnt/MainShare/Projects/Qichen/VBS/data/mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs.deriv.DAOD_HIGG2D1.e6611_e5984_a875_r10201_r10210_p3654.root");
        TTree* in_tree  = (TTree*)in_tree_file->Get("SM4L_Nominal");
        Long64_t entries_per_thread = (Long64_t)(in_tree->GetEntries()/ NUM_THREADS);

    //open output file
        TFile* out_tree_file = TFile::Open("/mnt/MainShare/Projects/Qichen/VBS/output/85M_mul.root", "recreate");

        for(int i = 0; i < NUM_THREADS; i++ ) {
            char * ind = intToChar(i);
            char* out_name_i = strcat(tree_name,ind);
            TTree* out_tree = new TTree(out_name_i, "processed tree");
            struct single_arg threadarg{
                in_tree,
                out_tree,
                i*entries_per_thread,
                (i+1)*entries_per_thread,
            };
            auto rc = pthread_create(&threads[i], NULL, analysis, (void *)&threadarg);
            if (rc){
                std::cout<<"error: thread "<<i<<" creation faild!"<<std::endl;
            }
            
        }
        out_tree_file->Write();
        in_tree_file->Close();
    return 0;
}
