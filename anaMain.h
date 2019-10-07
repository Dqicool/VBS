#ifndef _anaMain_
#define _ana_Main_
#include "genAna.h"

struct single_arg
{
    TTree * in;
    TTree * out;
    Long64_t start;
    Long64_t end;
};

void * analysis(void * arg)
{
    //parse the arguments
        struct single_arg * args = (struct single_arg *)arg;
        TTree * in_tree = args->in;
        TTree * out_tree = args->out;
        Long64_t entry_start = args->start;
        Long64_t entry_end = args->end;

    //define output tree;
        float jj_m, 
              jj_delta_y, 
              leading_jet_pt, 
              sublead_jet_pt,
              third_jet_pt,
              product_jj_y, 
              z1_pt, 
              z2_pt, 
              z1_m,
              z2_m,
              z1_y,
              z2_y,
              zzjj_rel_pt,
              llll_m,
              llll_pt;
        out_tree->Branch("jj_m", &jj_m);
        out_tree->Branch("jj_delta_y", &jj_delta_y);
        out_tree->Branch("leading_jet_pt", &leading_jet_pt);
        out_tree->Branch("sublead_jet_pt", &sublead_jet_pt);
        out_tree->Branch("third_jet_pt", &third_jet_pt);
        out_tree->Branch("product_jj_eta", &product_jj_y);
        out_tree->Branch("z1_pt", &z1_pt);
        out_tree->Branch("z2_pt", &z2_pt);
        out_tree->Branch("z1_m", &z1_m);
        out_tree->Branch("z2_m", &z2_m);
        out_tree->Branch("z1_y", &z1_y);
        out_tree->Branch("z2_y", &z2_y);
        out_tree->Branch("zzjj_rel_pt", &zzjj_rel_pt);
        out_tree->Branch("llll_m", &llll_m);
        out_tree->Branch("llll_pt", &llll_pt);


    
    //declare variables to read from in_tree
        std::vector<float> *jet_pt = 0;
        std::vector<float> *jet_m = 0;
        std::vector<float> *jet_eta = 0;
        std::vector<float> *jet_phi = 0;

        std::vector<float> *lepton_pt = 0;
        std::vector<float> *lepton_m = 0;
        std::vector<float> *lepton_eta = 0;
        std::vector<float> *lepton_phi = 0;
        std::vector<int>   *lepton_charge = 0;
        std::vector<int>   *lepton_particleID = 0;

    //assign variables to branches
        in_tree->SetBranchAddress("jet_eta", &jet_eta);
        in_tree->SetBranchAddress("jet_pt", &jet_pt);
        in_tree->SetBranchAddress("jet_m", &jet_m);
        in_tree->SetBranchAddress("jet_phi", &jet_phi);

        in_tree->SetBranchAddress("lepton_eta", &lepton_eta);
        in_tree->SetBranchAddress("lepton_pt", &lepton_pt);
        in_tree->SetBranchAddress("lepton_m", &lepton_m);
        in_tree->SetBranchAddress("lepton_phi", &lepton_phi);
        in_tree->SetBranchAddress("lepton_particleID", &lepton_particleID);
        in_tree->SetBranchAddress("lepton_charge", &lepton_charge);

    //loop over tree events
        for (int i = entry_start; i<entry_end; i++) 
        {
            in_tree->GetEntry(i);
            //observables used 
                std::vector<int>    lead_sec_jets_ind;
                std::vector<float>  jet_energy;
                std::vector<float>  jet_px_py_pz[jet_pt->size()];
                std::vector<float>  lepton_energy;
                std::vector<float>  lepton_px_py_pz[lepton_pt->size()];
                std::vector<std::vector<std::vector<int>>>    
                                    lepton_pair_index;
                std::vector<int>    z1_lepton_ind;
                std::vector<int>    z2_lepton_ind;
                std::vector<std::vector<float>>  
                                    lepton_pair_mll;
                std::vector<float>  llll_px_py_pz;
                std::vector<int>    llll_ind;
                std::vector<float>  z1_px_py_pz;
                std::vector<float>  z2_px_py_pz;
                float               z1_energy;
                float               z2_energy;

            //cuts
                if (jet_pt->size() < 2 ){continue;}
                if (lepton_pt->size() < 4 ){continue;}
            //jets calculations
                for(int j=0;j<jet_pt->size();j++)
                {
                    jet_energy.push_back(getEnergy((*jet_m)[j], (*jet_eta)[j], (*jet_pt)[j]));
                    jet_px_py_pz[j] = getPxPyPz((*jet_pt)[j], (*jet_eta)[j], (*jet_phi)[j]);
                }
                lead_sec_jets_ind = getMaxSec(*jet_pt);
                std::vector <float> jet_lead_subl_y{getY(jet_px_py_pz[lead_sec_jets_ind[0]], jet_energy[lead_sec_jets_ind[0]]), 
                                                    getY(jet_px_py_pz[lead_sec_jets_ind[1]], jet_energy[lead_sec_jets_ind[1]])};
                
                if (jet_pt->size() > 2){
                    int least_jet_ind = findLowestNum(jet_energy);
                    third_jet_pt = (*jet_pt)[least_jet_ind];
                }
                jj_m = getMassWithInd(jet_energy, jet_px_py_pz, lead_sec_jets_ind);
                jj_delta_y = TMath::Abs(jet_lead_subl_y[0]-jet_lead_subl_y[1]);
                leading_jet_pt = (*jet_pt)[lead_sec_jets_ind[0]];
                sublead_jet_pt = (*jet_pt)[lead_sec_jets_ind[1]];
                product_jj_y = jet_lead_subl_y[0]*jet_lead_subl_y[1];
            //lepton peer mass, 
                for(int j=0;j<lepton_pt->size();j++)
                {
                    lepton_energy.push_back(getEnergy((*lepton_m)[j], (*lepton_eta)[j], (*lepton_pt)[j]));
                    lepton_px_py_pz[j] = getPxPyPz((*lepton_pt)[j], (*lepton_eta)[j], (*lepton_phi)[j]);
                }
                lepton_pair_index = getLeptonPairInd(*lepton_particleID, *lepton_charge);
                for (int k = 0; k < lepton_pair_index.size(); k++)
                {
                    std::vector<float> tmp;
                    tmp.push_back(getMassWithInd(lepton_energy, lepton_px_py_pz, lepton_pair_index[k][0]));
                    tmp.push_back(getMassWithInd(lepton_energy, lepton_px_py_pz, lepton_pair_index[k][1]));
                    lepton_pair_mll.push_back(tmp);
                }
                std::vector<int> m_closest_to_z_ind = closestMassSelect(lepton_pair_mll, Z_MASS*1000);
                z1_lepton_ind.push_back(lepton_pair_index[m_closest_to_z_ind[0]][m_closest_to_z_ind[1]][0]);
                z1_lepton_ind.push_back(lepton_pair_index[m_closest_to_z_ind[0]][m_closest_to_z_ind[1]][1]);
                z2_lepton_ind.push_back(lepton_pair_index[m_closest_to_z_ind[0]][!(bool)m_closest_to_z_ind[1]][0]);
                z2_lepton_ind.push_back(lepton_pair_index[m_closest_to_z_ind[0]][!(bool)m_closest_to_z_ind[1]][1]);
                z1_px_py_pz = getCombinedPxPyPzWithInd(lepton_px_py_pz, z1_lepton_ind);
                z1_energy = getCombinedEnergyWithInd(lepton_energy, z1_lepton_ind);
                z2_px_py_pz = getCombinedPxPyPzWithInd(lepton_px_py_pz, z2_lepton_ind);
                z2_energy = getCombinedEnergyWithInd(lepton_energy, z2_lepton_ind);
                llll_ind = {z1_lepton_ind[0], z1_lepton_ind[1], z2_lepton_ind[0], z2_lepton_ind[1]};
                llll_px_py_pz = getCombinedPxPyPzWithInd(lepton_px_py_pz, llll_ind);
                z1_pt = getTotalPt(lepton_px_py_pz[z1_lepton_ind[0]], lepton_px_py_pz[z1_lepton_ind[1]]);
                z2_pt = getTotalPt(lepton_px_py_pz[z2_lepton_ind[0]], lepton_px_py_pz[z2_lepton_ind[1]]);
                z1_m = lepton_pair_mll[m_closest_to_z_ind[0]][m_closest_to_z_ind[1]];
                z2_m = lepton_pair_mll[m_closest_to_z_ind[0]][!(bool)m_closest_to_z_ind[1]];
                z1_y = getY(z1_px_py_pz,z1_energy);
                z2_y = getY(z2_px_py_pz,z2_energy);
                llll_m = getMassWithInd(lepton_energy, lepton_px_py_pz, llll_ind);
                llll_pt = TMath::Sqrt(llll_px_py_pz[0]*llll_px_py_pz[0] + llll_px_py_pz[1]*llll_px_py_pz[1]);
            //jjzz system 
                float z1_pt = TMath::Sqrt(TMath::Power(z1_px_py_pz[0],2) + TMath::Power(z1_px_py_pz[1],2));
                float z2_pt = TMath::Sqrt(TMath::Power(z2_px_py_pz[0],2) + TMath::Power(z2_px_py_pz[1],2));
                float jet1_pt = (*jet_pt)[lead_sec_jets_ind[0]];
                float jet2_pt = (*jet_pt)[lead_sec_jets_ind[1]];
                float zzjj_scaler_sum_pt = z1_pt + z2_pt + jet1_pt + jet2_pt;
                vector<float> zzjj_px_py_pz[4] = {z1_px_py_pz, z2_px_py_pz, jet_px_py_pz[lead_sec_jets_ind[0]], jet_px_py_pz[lead_sec_jets_ind[1]]};
                vector<int> ind{0,1,2,3};
                vector<float> zzjj_sys_px_py_pz = getCombinedPxPyPzWithInd(zzjj_px_py_pz, ind);
                float zzjj_sys_pt = TMath::Sqrt(TMath::Power(zzjj_sys_px_py_pz[0],2) + TMath::Power(zzjj_sys_px_py_pz[1],2));
                zzjj_rel_pt = zzjj_sys_pt / zzjj_scaler_sum_pt;
            //Filling out_tree
                out_tree->Fill();
        }
}
#endif