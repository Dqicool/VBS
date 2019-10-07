#include "genAna.h"
int main(){
    vector<float> mp1{1,3};
    vector<float> mp2{1,2};
    vector<float> mp6{1,1};
    vector<float> mp4{3,3};
    vector<float> mp5{3,2};
    vector<float> mp3{3,1};
    vector<vector<float>> mass{mp1,mp2,mp3, mp4, mp5,mp6};
    auto ind = closestMassSelect(mass,0);
    cout<<mass[ind[0]][ind[1]]<<"\t"<<mass[ind[0]][!(bool)(ind[1])]<<endl;
}