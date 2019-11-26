#include"genAna.h"
using namespace std;

int main(){
    TFile * f = TFile::Open("test_out.root");
    TTree* t = (TTree*)f->Get("SM4L_Nominal");
    std::vector<int> *z1_ind;
    std::vector<int> *z2_ind;
    t->SetBranchAddress("z1_index", &z1_ind);
    t->SetBranchAddress("z2_index", &z2_ind);
    auto ne = t->GetEntries();
    for(uint i = 0; i < ne; i++){
        t->GetEntry(i);
        cout<<i<<":\t";
        if(z1_ind->size() > 0)
            cout<<(*z1_ind)[0]<<"\t"<<(*z1_ind)[1]<<"\t\t"<<(*z2_ind)[0]<<"\t"<<(*z2_ind)[1]<<endl;
    }
}