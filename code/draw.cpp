
#include <TCanvas.h>
#include <ROOT/RDataFrame.hxx>
#define DRAW_1
#define DRAW_2
#define DRAW_3

void draw()
{
    ROOT::EnableImplicitMT;
    //Read files
        #ifdef DRAW_1
        ROOT::RDataFrame f1("out_tree", "/mnt/MainShare/Projects/Qichen/VBS/output/3G_tree.root");
        #endif
        #ifdef DRAW_2
        ROOT::RDataFrame f2("out_tree", "/mnt/MainShare/Projects/Qichen/VBS/output/281M_tree.root");
        #endif
        #ifdef DRAW_3
        ROOT::RDataFrame f3("out_tree", "/mnt/MainShare/Projects/Qichen/VBS/output/85M_tree.root");
        #endif
    //book histos
        #ifdef DRAW_1
            auto h_f1_jj_m = f1.Histo1D({"jj_m","",400,0,1e6},"jj_m");
            auto h_f1_j3_pt = f1.Histo1D({"j3_pt","",400,0,1e6},"j3_pt");
            auto h_f1_j1_y = f1.Histo1D({"j1_y","",400,-5,5},"j1_y");
            auto h_f1_j2_y = f1.Histo1D({"j2_y","",400,-5,5},"j2_y");
            auto h_f1_jj_delta_y = f1.Histo1D({"jj_delta_y","",400,-10,10},"jj_delta_y");
            auto h_f1_jj_product_y = f1.Histo1D({"jj_product_y","",400,-20,20},"jj_product_y");
            auto h_f1_j1_pt = f1.Histo1D({"j1_pt","",400,0,1e6},"j1_pt");
            auto h_f1_j2_pt = f1.Histo1D({"j2_pt","",400,0,1e6},"j2_pt");
            auto h_f1_z1_pt = f1.Histo1D({"z1_pt","",400,0,1e6},"z1_pt");
            auto h_f1_z2_pt = f1.Histo1D({"z2_pt","",400,0,1e6},"z2_pt");
            auto h_f1_z1_m = f1.Histo1D({"z1_m","",400,0,3e5},"z1_m");
            auto h_f1_z2_m = f1.Histo1D({"z2_m","",400,0,3e5},"z2_m");
            auto h_f1_z1_y = f1.Histo1D({"z1_y","",400,-5,5},"z1_y");
            auto h_f1_z2_y = f1.Histo1D({"z2_y","",400,-5,5},"z2_y");
            auto h_f1_llll_m = f1.Histo1D({"llll_m","",400,0,1e6},"llll_m");
            auto h_f1_llll_pt = f1.Histo1D({"llll_pt","",400,0,1e6},"llll_pt");
            auto h_f1_zzjj_rel_pt = f1.Histo1D({"zzjj_rel_pt","",400,0,1},"zzjj_rel_pt");
        #endif
        #ifdef DRAW_2
            auto h_f2_jj_m = f2.Histo1D({"jj_m","",400,0,1e6},"jj_m");
            auto h_f2_j3_pt = f2.Histo1D({"j3_pt","",400,0,1e6},"j3_pt");
            auto h_f2_j1_y = f2.Histo1D({"j1_y","",400,-5,5},"j1_y");
            auto h_f2_j2_y = f2.Histo1D({"j2_y","",400,-5,5},"j2_y");
            auto h_f2_jj_delta_y = f2.Histo1D({"jj_delta_y","",400,-10,10},"jj_delta_y");
            auto h_f2_jj_product_y = f2.Histo1D({"jj_product_y","",400,-20,20},"jj_product_y");
            auto h_f2_j1_pt = f2.Histo1D({"j1_pt","",400,0,1e6},"j1_pt");
            auto h_f2_j2_pt = f2.Histo1D({"j2_pt","",400,0,1e6},"j2_pt");
            auto h_f2_z1_pt = f2.Histo1D({"z1_pt","",400,0,1e6},"z1_pt");
            auto h_f2_z2_pt = f2.Histo1D({"z2_pt","",400,0,1e6},"z2_pt");
            auto h_f2_z1_m = f2.Histo1D({"z1_m","",400,0,3e5},"z1_m");
            auto h_f2_z2_m = f2.Histo1D({"z2_m","",400,0,3e5},"z2_m");
            auto h_f2_z1_y = f2.Histo1D({"z1_y","",400,-5,5},"z1_y");
            auto h_f2_z2_y = f2.Histo1D({"z2_y","",400,-5,5},"z2_y");
            auto h_f2_llll_m = f2.Histo1D({"llll_m","",400,0,1e6},"llll_m");
            auto h_f2_llll_pt = f2.Histo1D({"llll_pt","",400,0,1e6},"llll_pt");
            auto h_f2_zzjj_rel_pt = f2.Histo1D({"zzjj_rel_pt","",400,0,1},"zzjj_rel_pt");
        #endif
        #ifdef DRAW_3
            auto h_f3_jj_m = f3.Histo1D({"jj_m","",400,0,1e6},"jj_m");
            auto h_f3_j3_pt = f3.Histo1D({"j3_pt","",400,0,1e6},"j3_pt");
            auto h_f3_j1_y = f3.Histo1D({"j1_y","",400,-5,5},"j1_y");
            auto h_f3_j2_y = f3.Histo1D({"j2_y","",400,-5,5},"j2_y");
            auto h_f3_jj_delta_y = f3.Histo1D({"jj_delta_y","",400,-10,10},"jj_delta_y");
            auto h_f3_jj_product_y = f3.Histo1D({"jj_product_y","",400,-20,20},"jj_product_y");
            auto h_f3_j1_pt = f3.Histo1D({"j1_pt","",400,0,1e6},"j1_pt");
            auto h_f3_j2_pt = f3.Histo1D({"j2_pt","",400,0,1e6},"j2_pt");
            auto h_f3_z1_pt = f3.Histo1D({"z1_pt","",400,0,1e6},"z1_pt");
            auto h_f3_z2_pt = f3.Histo1D({"z2_pt","",400,0,1e6},"z2_pt");
            auto h_f3_z1_m = f3.Histo1D({"z1_m","",400,0,3e5},"z1_m");
            auto h_f3_z2_m = f3.Histo1D({"z2_m","",400,0,3e5},"z2_m");
            auto h_f3_z1_y = f3.Histo1D({"z1_y","",400,-5,5},"z1_y");
            auto h_f3_z2_y = f3.Histo1D({"z2_y","",400,-5,5},"z2_y");
            auto h_f3_llll_m = f3.Histo1D({"llll_m","",400,0,1e6},"llll_m");
            auto h_f3_llll_pt = f3.Histo1D({"llll_pt","",400,0,1e6},"llll_pt");
            auto h_f3_zzjj_rel_pt = f3.Histo1D({"zzjj_rel_pt","",400,0,1},"zzjj_rel_pt");
        #endif
    //draw
        TCanvas *c1 = new TCanvas("c1","",600,400);
        #ifdef DRAW_1
            h_f1_j1_pt->SetLineColor(kBlue);
            h_f1_j1_pt->GetXaxis()->SetTitle("j1_pt");
            h_f1_j1_pt->Draw();
        #endif
        #ifdef DRAW_2
            h_f2_j1_pt->SetLineColor(kRed);
            h_f2_j1_pt->Draw("same");
        #endif
        #ifdef DRAW_3
            h_f3_j1_pt->SetLineColor(kGreen);
            h_f3_j1_pt->Draw("same");
        #endif
		c1->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/j1_pt.pdf");

        TCanvas *c2 = new TCanvas("c2","",600,400);
        #ifdef DRAW_1
            h_f1_z1_m->SetLineColor(kBlue);
            h_f1_z1_m->GetXaxis()->SetTitle("z1_m");
            h_f1_z1_m->Draw();
        #endif
        #ifdef DRAW_2
            h_f2_z1_m->SetLineColor(kRed);
            h_f2_z1_m->Draw("same");
        #endif
        #ifdef DRAW_3
            h_f3_z1_m->SetLineColor(kGreen);
            h_f3_z1_m->Draw("same");
        #endif
		c2->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/z1_m.pdf");

        TCanvas *c3 = new TCanvas("c3","",600,400);
        #ifdef DRAW_1
            h_f1_z2_m->SetLineColor(kBlue);
            h_f1_z2_m->GetXaxis()->SetTitle("z2_m");
            h_f1_z2_m->Draw();
        #endif
        #ifdef DRAW_2
            h_f2_z2_m->SetLineColor(kRed);
            h_f2_z2_m->Draw("same");
        #endif
        #ifdef DRAW_3
            h_f3_z2_m->SetLineColor(kGreen);
            h_f3_z2_m->Draw("same");
        #endif
		c3->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/z2_m.pdf");

        TCanvas *c4 = new TCanvas("c4","",600,400);
        #ifdef DRAW_1
            h_f1_llll_m->SetLineColor(kBlue);
            h_f1_llll_m->GetXaxis()->SetTitle("llll_m");
            h_f1_llll_m->Draw();
        #endif
        #ifdef DRAW_2
            h_f2_llll_m->SetLineColor(kRed);
            h_f2_llll_m->Draw("same");
        #endif
        #ifdef DRAW_3
            h_f3_llll_m->SetLineColor(kGreen);
            h_f3_llll_m->Draw("same");
        #endif
		c4->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/llll_m.pdf");

        TCanvas *c5 = new TCanvas("c5","",600,400);
        #ifdef DRAW_1
            h_f1_j3_pt->SetLineColor(kBlue);
            h_f1_j3_pt->GetXaxis()->SetTitle("j3_pt_m");
            h_f1_j3_pt->Draw();
        #endif
        #ifdef DRAW_2
            h_f2_j3_pt->SetLineColor(kRed);
            h_f2_j3_pt->Draw("same");
        #endif
        #ifdef DRAW_3
            h_f3_j3_pt->SetLineColor(kGreen);
            h_f3_j3_pt->Draw("same");
        #endif
		c5->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/j3_pt.pdf");

        TCanvas *c6 = new TCanvas("c6","",600,400);
        #ifdef DRAW_1
            h_f1_j2_pt->SetLineColor(kBlue);
            h_f1_j2_pt->GetXaxis()->SetTitle("j2_pt");
            h_f1_j2_pt->Draw();
        #endif
        #ifdef DRAW_2
            h_f2_j2_pt->SetLineColor(kRed);
            h_f2_j2_pt->Draw("same");
        #endif
        #ifdef DRAW_3
            h_f3_j2_pt->SetLineColor(kGreen);
            h_f3_j2_pt->Draw("same");
        #endif
		c6->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/j2_pt.pdf");

        TCanvas *c7 = new TCanvas("c7","",600,400);
        #ifdef DRAW_1
            h_f1_j1_y->SetLineColor(kBlue);
            h_f1_j1_y->GetXaxis()->SetTitle("j1_y");
            h_f1_j1_y->Draw();
        #endif
        #ifdef DRAW_2
            h_f2_j1_y->SetLineColor(kRed);
            h_f2_j1_y->Draw("same");
        #endif
        #ifdef DRAW_3
            h_f3_j1_y->SetLineColor(kGreen);
            h_f3_j1_y->Draw("same");
        #endif
		c7->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/j1_y.pdf");

        TCanvas *c8 = new TCanvas("c8","",600,400);
        #ifdef DRAW_1
            h_f1_j2_y->SetLineColor(kBlue);
            h_f1_j2_y->GetXaxis()->SetTitle("j2_y");
            h_f1_j2_y->Draw();
        #endif
        #ifdef DRAW_2
            h_f2_j2_y->SetLineColor(kRed);
            h_f2_j2_y->Draw("same");
        #endif
        #ifdef DRAW_3
            h_f3_j2_y->SetLineColor(kGreen);
            h_f3_j2_y->Draw("same");
        #endif
		c8->SaveAs("/mnt/MainShare/Projects/Qichen/VBS/plots/j2_y.pdf");
}
#ifndef __CINT__
int main(){draw();}
#endif