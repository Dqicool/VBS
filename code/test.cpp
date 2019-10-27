//event selection and weight normalisation

#include"genAna.h"
using namespace std;
//#define debug

int main()
{
    std::vector<int> id{1,1,1,3};
    std::vector<float> ch{1,1,-1,-1};
    auto aa = getLeptonPairInd(id,ch);
    cout<<aa.size()<<endl;
}