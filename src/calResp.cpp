#include "genAna.h"
#include <RooUnfoldResponse.h>
#include <RooUnfoldBayes.h>
#include <RooUnfoldErrors.h>
#include <cstdlib>
#include <TLegend.h>
using namespace std;
void calResp(const char* infile, const char* out_resp,  const char* dist, const char* dist_true, TH1D* templ, bool recre)
{
    //load data file
        TH1::SetDefaultSumw2();
        TFile* f = TFile::Open(infile,"read");
        TTree* t = (TTree*)f->Get("SM4L_Nominal");
        RooUnfoldResponse resp(templ, templ, dist, infile);
        ROOT::RDataFrame df("SM4L_Nominal" ,infile);

    
    //declare variable pointer in tree
        double x_measured=0;
        double x_true = 0;
        double weight = 0;
        double weight_true = 0;
        bool pass_cut = 0;
        bool pass_true_cut = 0;
    
    if (df.HasColumn("NormWeight_true")){
        //setting pointers
            t->SetBranchAddress("pass_cut", &pass_cut);
            t->SetBranchAddress("pass_truthBorn_cut", &pass_true_cut);
            t->SetBranchAddress(dist,&x_measured);
            t->SetBranchAddress(dist_true,&x_true);
            t->SetBranchAddress("NormWeight", &weight);
            t->SetBranchAddress("NormWeight_true", &weight_true);
            auto n_entry = t->GetEntries();
        
        // loop fills
            for( Long64_t i = 0; i<(n_entry); i++)
            {
                t->GetEntry(i);
                if(pass_cut && pass_true_cut){
                    resp.Fill(x_measured, x_true, weight);
                }
            }
        //save representation response
            const char* file_opt;
            if (recre)  file_opt = "recreate";
            else        file_opt = "update";
            TFile* out = TFile::Open(out_resp, file_opt);
            string disp_save_name = "disp_resp_" + (string)(dist);
            resp.SetName(&disp_save_name[0]);
            resp.Write();
        
        //loop over fake and miss
            for( Long64_t i = 0; i<(n_entry); i++)
            {
                t->GetEntry(i);
                if((pass_cut==0) && pass_true_cut){
                    resp.Miss(x_true, weight_true);
                }
                else if(pass_cut && (pass_true_cut==0)){
                    resp.Fake(x_measured, weight);
                }
            }
        //save respond
            string use_save_name = "use_resp_" + (string)(dist);
            resp.SetName(&use_save_name[0]);
            resp.Write();
            out->Close();
            f->Close();
    }
}

int main(int argc, char** argv){
    TFile* inm4l = TFile::Open("output/histo_out/dem_unfold_m4l.root","read");
    TFile* inmjj = TFile::Open("output/histo_out/dem_unfold_mjj.root","read");
    TFile* indelphijj = TFile::Open("output/histo_out/dem_unfold_delphijj.root","read");

    auto Templm4l = (TH1D*)inm4l->Get("h_rebin_m4l_cut");
    auto Templmjj = (TH1D*)inmjj->Get("h_rebin_mjj_cut");
    auto Templdelphijj = (TH1D*)indelphijj->Get("h_rebin_delphijj_cut");

    const char* infile=argv[1];
    const char* out_resp = argv[2];
    
    calResp(infile, out_resp, "jj_delta_phi", "jj_truthBorn_delta_phi", Templdelphijj, 1);
    calResp(infile, out_resp, "jj_m", "jj_truthBorn_m", Templmjj, 0);
    calResp(infile, out_resp,  "llll_m", "llll_truthBorn_m", Templm4l, 0);
}