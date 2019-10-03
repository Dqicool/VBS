#include "genAna.h"
#define Z_MASS 91.1876 //GeV

void firstplay()
{
    //open file containing ntuples
    TFile* treeFile = TFile::Open("/mnt/MainShare/Projects/Qichen/VBS/samples/sample/ntuple.root");
    
    //get tree from file
    TTree* tree  = (TTree*)treeFile->Get("SM4L_Nominal");
    
    //declare histograms
    TH1F* h_mjj = new TH1F("mjj", "mjj", 400, 0.0, 5000.);
    TH1F* h_jj_delta_eta = new TH1F("jj_delta_eta", "jj_delta_eta", 400, 0., 10.);
    TH1F* h_leading_jet_pt = new TH1F("leading_jet_pt", "leading_jet_pt", 400, 0., 2000.);
    TH1F* h_sublead_jet_pt = new TH1F("sublead_jet_pt", "sublead_jet_pt", 400, 0., 2000.);
    TH1F* h_product_jj_eta = new TH1F("product_jj_eta", "product_jj_eta", 400, 0., 50.);
    TH1F* h_z1_pt = new TH1F("z1_pt", "z1_pt", 400, 0., 1000.);
    TH1F* h_z2_pt = new TH1F("z2_pt", "z2_pt", 400, 0., 1000.);
    TH1F* h_z1_m = new TH1F("z1_m", "z1_m", 400, 0., 200.);
    TH1F* h_z2_m = new TH1F("z2_m", "z2_m", 400, 0., 200.);
    TH1F* h_z1_y = new TH1F("z1_y", "z1_y", 200, -5., 5.);
    TH1F* h_z2_y = new TH1F("z2_y", "z2_y", 200, -5., 5.);

    
    //declare variables to read from tree
    std::vector<float> *jet_pt = 0;
    std::vector<float> *jet_m = 0;
    std::vector<float> *jet_eta = 0;
    std::vector<float> *jet_phi = 0;

    std::vector<float> *lepton_pt = 0;
    std::vector<float> *lepton_m = 0;
    std::vector<float> *lepton_eta = 0;
    std::vector<float> *lepton_phi = 0;
    std::vector<int> *lepton_charge = 0;
    std::vector<int> *lepton_particleID = 0;

    //assign variables to branches
    tree->SetBranchAddress("jet_eta", &jet_eta);
    tree->SetBranchAddress("jet_pt", &jet_pt);
    tree->SetBranchAddress("jet_m", &jet_m);
    tree->SetBranchAddress("jet_phi", &jet_phi);

    tree->SetBranchAddress("lepton_eta", &lepton_eta);
    tree->SetBranchAddress("lepton_pt", &lepton_pt);
    tree->SetBranchAddress("lepton_m", &lepton_m);
    tree->SetBranchAddress("lepton_phi", &lepton_phi);
    tree->SetBranchAddress("lepton_particleID", &lepton_particleID);
    tree->SetBranchAddress("lepton_charge", &lepton_charge);


    //loop over tree events
    int nentries = (int)tree->GetEntries();
    for (int i = 0; i<nentries; i++) 
    {
        tree->GetEntry(i);
        std::vector<int>    lead_sec_jets_ind;
        std::vector<float>  jet_energy;
        std::vector<float>  jet_px_py_pz[jet_pt->size()];

        std::vector<float>  lepton_energy;
        std::vector<float>  lepton_px_py_pz[lepton_pt->size()];
        std::vector<int>    lepton_peer_index;
        std::vector<float>  lepton_peer_mll;
        std::vector<float>  z1_px_py_pz;
        std::vector<float>  z2_px_py_pz;
        float               z1_energy;
        float               z2_energy;

        //dijets mjj, delta eta, pt1, pt2, etaj1*etaj2
        if (jet_pt->size() < 2 ){continue;}
        else
        {
            for(int j=0;j<jet_pt->size();j++)
            {
                jet_energy.push_back(getEnergy((*jet_m)[j], (*jet_eta)[j], (*jet_pt)[j]));
                jet_px_py_pz[j] = getPxPyPz((*jet_pt)[j], (*jet_eta)[j], (*jet_phi)[j]);
            }
            lead_sec_jets_ind = getMaxSec(jet_energy);
            h_mjj->Fill(getMassWithInd(jet_energy, jet_px_py_pz, lead_sec_jets_ind)/1000);
            h_jj_delta_eta->Fill(TMath::Abs((*jet_eta)[lead_sec_jets_ind[0]] - (*jet_eta)[lead_sec_jets_ind[1]]));
            h_leading_jet_pt->Fill((*jet_pt)[lead_sec_jets_ind[0]] / 1000);
            h_sublead_jet_pt->Fill((*jet_pt)[lead_sec_jets_ind[1]] / 1000);
            h_product_jj_eta->Fill((*jet_eta)[lead_sec_jets_ind[0]] * (*jet_eta)[lead_sec_jets_ind[1]]);
        }
        //lepton peer mass,
        if (lepton_pt->size() < 4 ){continue;}
        else if (lepton_pt->size() == 4 )
        {
            for(int j=0;j<lepton_pt->size();j++)
            {
                lepton_energy.push_back(getEnergy((*lepton_m)[j], (*lepton_eta)[j], (*lepton_pt)[j]));
                lepton_px_py_pz[j] = getPxPyPz((*lepton_pt)[j], (*lepton_eta)[j], (*lepton_phi)[j]);
            }
            lepton_peer_index = getLeptonPeerInd(*lepton_particleID, *lepton_charge);
            for (int k = 0; k < lepton_peer_index.size(); k+=2)
            {
                std::vector<int> ind{lepton_peer_index[k],lepton_peer_index[k+1]};
                lepton_peer_mll.push_back(getMassWithInd(lepton_energy, lepton_px_py_pz, ind)/1000);
            }
            int m_closest_to_z_ind = closestMassSelect(lepton_peer_mll, Z_MASS);
            std::vector<int> z1_lepton_ind{lepton_peer_index[m_closest_to_z_ind*2], lepton_peer_index[m_closest_to_z_ind*2+1]};
            std::vector<int> z2_lepton_ind;
            h_z1_pt->Fill(getTotalPt(lepton_px_py_pz[lepton_peer_index[m_closest_to_z_ind*2]], 
                                     lepton_px_py_pz[lepton_peer_index[m_closest_to_z_ind*2+1]])/1000);
            h_z1_m->Fill(lepton_peer_mll[m_closest_to_z_ind]);
            z1_px_py_pz = getCombinedPxPyPzWithInd(lepton_px_py_pz, z1_lepton_ind);
            z1_energy = getCombinedEnergyWithInd(lepton_energy, z1_lepton_ind);
            auto tmp = getY(z1_px_py_pz,z1_energy);
            h_z1_y->Fill(tmp);
            
            if (m_closest_to_z_ind % 2 == 1)
            {
                z2_lepton_ind.push_back(lepton_peer_index[(m_closest_to_z_ind - 1)*2]);
                z2_lepton_ind.push_back(lepton_peer_index[(m_closest_to_z_ind - 1)*2 + 1]);
                h_z2_m->Fill(lepton_peer_mll[m_closest_to_z_ind - 1]);
                h_z2_pt->Fill(getTotalPt(lepton_px_py_pz[z2_lepton_ind[0]], 
                                         lepton_px_py_pz[z2_lepton_ind[1]])/1000);
                z2_px_py_pz = getCombinedPxPyPzWithInd(lepton_px_py_pz, z2_lepton_ind);
                z2_energy = getCombinedEnergyWithInd(lepton_energy, z2_lepton_ind);
                h_z2_y->Fill(getY(z2_px_py_pz,z2_energy));
            }
            else
            {
                z2_lepton_ind.push_back(lepton_peer_index[(m_closest_to_z_ind + 1)*2]);
                z2_lepton_ind.push_back(lepton_peer_index[(m_closest_to_z_ind + 1)*2 + 1]);
                h_z2_m->Fill(lepton_peer_mll[m_closest_to_z_ind + 1]);
                h_z2_pt->Fill(getTotalPt(lepton_px_py_pz[z2_lepton_ind[0]], 
                                         lepton_px_py_pz[z2_lepton_ind[1]])/1000);
                z2_px_py_pz = getCombinedPxPyPzWithInd(lepton_px_py_pz, z2_lepton_ind);
                z2_energy = getCombinedEnergyWithInd(lepton_energy, z2_lepton_ind);
                h_z2_y->Fill(getY(z2_px_py_pz,z2_energy));
            }
            
        }
    }
    
    
    //open file to write output
    TFile* out = TFile::Open("/mnt/MainShare/Projects/Qichen/VBS/output/mjj.root","recreate");

    //write histograms to file
    h_mjj->Write();
    h_jj_delta_eta->Write();
    h_leading_jet_pt->Write();
    h_sublead_jet_pt->Write();
    h_product_jj_eta->Write();
    h_z1_pt->Write();
    h_z1_m->Write();
    h_z2_m->Write();
    h_z2_pt->Write();

    //close output file
    out->Close();
}

# ifndef __CINT__
int main()
{
    firstplay();
    return 0;
}
# endif
