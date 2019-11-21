#include "genAna.h"


std::vector<int> lepSel(std::vector<float> lepton_pt, 
                        std::vector<float> lepton_eta, 
                        std::vector<float> lepton_d0sig, 
                        std::vector<float> lepton_z0sinTheta, 
                        std::vector<int> lepton_particleID,
                        std::vector<char> lepton_passesIsolation)
{
    std::vector<int> letpon_pass_ind;
    auto siz = lepton_pt.size();

    for (uint i = 0;i < siz; i++)
    {
        if (lepton_passesIsolation[i] == 1)
        {
            if(lepton_particleID[i] == 11){
                if( lepton_pt[i] > 7e3 
                    //&& TMath::Abs(lepton_eta[i]) < 2.47 
                    //&& TMath::Abs(lepton_d0sig[i] < 5) 
                    //&& TMath::Abs(lepton_z0sinTheta[i]) < 0.5
                    )
                {
                    letpon_pass_ind.push_back(i);
                }
            }
            else if(lepton_particleID[i] == 13){
                if( lepton_pt[i] > 7e3 
                    //&& TMath::Abs(lepton_eta[i]) < 2.7 
                    //&& TMath::Abs(lepton_d0sig[i] < 3) 
                    //&& TMath::Abs(lepton_z0sinTheta[i]) < 0.5
                    )
                {
                    letpon_pass_ind.push_back(i);
                }
            }
        }
    }
    
    return letpon_pass_ind;
}


std::vector<int> jetSel(std::vector<float> jet_pt, std::vector<float> jet_eta)
{
    std::vector<int> jet_pass_ind;
    auto siz = jet_pt.size();
    for (uint i = 0; i < siz; i++){
        if (TMath::Abs(jet_eta[i]) < 2.4 && jet_pt[i] > 30e3){
            jet_pass_ind.push_back(i);
        }
        else if(TMath::Abs(jet_eta[i]) < 4.5 && jet_pt[i] > 40e3){
            jet_pass_ind.push_back(i);
        }
    } 
    return jet_pass_ind;
}


bool baseline(std::vector<int> lepton_pass_ind, std::vector<int> jet_pass_ind, std::vector<float> lepton_pt)
{
    bool ret1 = lepton_pass_ind.size() >= 4 && jet_pass_ind.size() >= 2;
    bool ret2 = 0;
    std::vector<float> lep_pass_pt;
    auto siz = lepton_pass_ind.size();
    if (siz >= 4){
        for(uint i = 0; i< siz; i++){
            lep_pass_pt.push_back(lepton_pt[(lepton_pass_ind[i])]);
        }
        sort(lep_pass_pt.begin(), lep_pass_pt.end(), greater<float>());
        ret2 =  (lep_pass_pt[0] > 20e3 && lep_pass_pt[1] > 20e3 && lep_pass_pt[2] > 10e3);
    }
    return ret1 && ret2;
}


std::vector<double> test()
{
    //ROOT::EnableImplicitMT(24);
    vector<double> cutflow{};
    ROOT::RDataFrame d("SM4L_Nominal", "data/200_vbsf/mc16_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.deriv.DAOD_HIGG2D1.e5500_s3126_r9364_p3654.root");
    ROOT::RDataFrame m("MetaDataTree", "data/200_vbsf/mc16_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.deriv.DAOD_HIGG2D1.e5500_s3126_r9364_p3654.root");
    auto prwlumi = (m.Take<double>("prwLuminosity").GetValue())[0];
    cutflow.push_back(d.Filter("lepton_n >= 4 && jet_n>=2").Sum("weight").GetValue() * (double)139e3 / prwlumi);
    cutflow.push_back(d.Filter("lepton_n >= 4 && jet_n>=2").Define("pass_lep_ind", lepSel, {"lepton_pt", "lepton_eta", "lepton_d0sig", "lepton_z0sinTheta", "lepton_particleID", "lepton_passesIsolation"}).Filter("pass_lep_ind.size() >= 4").Sum("weight").GetValue() * (double)139e3 / prwlumi);
    cutflow.push_back(d.Filter("lepton_n >= 4 && jet_n>=2").Define("pass_lep_ind", lepSel, {"lepton_pt", "lepton_eta", "lepton_d0sig", "lepton_z0sinTheta", "lepton_particleID", "lepton_passesIsolation"}).Define("pass_jet_ind", jetSel,{"jet_pt", "jet_eta"}).Filter("pass_lep_ind.size() >= 4 && pass_jet_ind.size() >= 2").Sum("weight").GetValue() * (double)139e3 / prwlumi);
    cutflow.push_back(d.Filter("lepton_n >= 4 && jet_n>=2").Define("pass_lep_ind", lepSel, {"lepton_pt", "lepton_eta", "lepton_d0sig", "lepton_z0sinTheta", "lepton_particleID", "lepton_passesIsolation"}).Define("pass_jet_ind", jetSel,{"jet_pt", "jet_eta"}).Filter("pass_lep_ind.size() >= 4 && pass_jet_ind.size() >= 2").Filter(baseline, {"pass_lep_ind","pass_jet_ind","lepton_pt"}).Sum("weight").GetValue() * (double)139e3 / prwlumi);

    return cutflow;
}