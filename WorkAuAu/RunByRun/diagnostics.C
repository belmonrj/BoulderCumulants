//#include "filenames.C"
#include "filenames_more.C"

//const int nhistos = 60;




void diagnostics()
{

  TCanvas* c1 = new TCanvas("c1","");

  //for ( int i = 0; i < nhistos; ++i )
  for ( int i = 0; i < NMOREFILES; ++i )
    {
      // --- open the file
      //TFile* fin = TFile::Open(filenames[i]);
      TFile* fin = TFile::Open(Form("NewFiles/%s",filenames[i].Data()));
      filenames[i].Remove(6,5);
      cout << "run number " << filenames[i] << endl;
      // --- get the qbbcns/nfvtxt correlation and make nice plot
      TH2D* h2_bsr = (TH2D*) fin->Get("th2d_nfvtxt_bbcsumratio");
      h2_bsr->Draw("col");
      h2_bsr->GetXaxis()->SetRangeUser(0,700);
      h2_bsr->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
      h2_bsr->GetYaxis()->SetTitle("Q^{BBC}_{N+S}/N^{FVTX}_{tracks}");
      TLatex tex;
      tex.SetNDC();
      tex.DrawLatex(0.7,0.2,Form("%s",filenames[i].Data()));
      c1->Print(Form("RBR_figs/h2_bsr_%s.png",filenames[i].Data()));
      // --- get the nfvtxt north-south correlation and make nice plot
      TH2D* h2_fns = (TH2D*) fin->Get("th2d_nfvtxt_northsouth");
      h2_fns->Draw("col");
      h2_fns->GetXaxis()->SetRangeUser(0,500);
      h2_fns->GetYaxis()->SetRangeUser(0,500);
      h2_fns->GetXaxis()->SetTitle("tracks north");
      h2_fns->GetYaxis()->SetTitle("tracks south");
      tex.DrawLatex(0.7,0.2,Form("%s",filenames[i].Data()));
      c1->SetLogz(1);
      c1->Print(Form("RBR_figs/h2_fns_%s.png",filenames[i].Data()));
      c1->SetLogz(0);
      //continue;
      // --- get the north qx2
      TProfile* h1_nqx2 = (TProfile*) fin->Get("centrality_recoffsets_north_0_2");
      h1_nqx2->Draw("col");
      double max = 0.2;
      double min = -max;
      h1_nqx2->SetMinimum(min);
      h1_nqx2->SetMaximum(max);
      h1_nqx2->GetXaxis()->SetTitle("centrality");
      h1_nqx2->GetYaxis()->SetTitle("north #LTcos 2#phi#GT");
      h1_nqx2->GetYaxis()->SetTitleOffset(1.2);
      tex.DrawLatex(0.7,0.2,Form("%s",filenames[i].Data()));
      c1->SetLogz(1);
      c1->Print(Form("RBR_figs/h1_nqx2_%s.png",filenames[i].Data()));
      c1->SetLogz(0);
      // --- get the south qx2
      TProfile* h1_sqx2 = (TProfile*) fin->Get("centrality_recoffsets_south_0_2");
      h1_sqx2->Draw("col");
      h1_sqx2->SetMinimum(min);
      h1_sqx2->SetMaximum(max);
      h1_sqx2->GetXaxis()->SetTitle("centrality");
      h1_sqx2->GetYaxis()->SetTitle("south #LTcos 2#phi#GT");
      h1_sqx2->GetYaxis()->SetTitleOffset(1.2);
      tex.DrawLatex(0.7,0.2,Form("%s",filenames[i].Data()));
      c1->SetLogz(1);
      c1->Print(Form("RBR_figs/h1_sqx2_%s.png",filenames[i].Data()));
      c1->SetLogz(0);
      // --- get the north qy2
      TProfile* h1_nqy2 = (TProfile*) fin->Get("centrality_recoffsets_north_1_2");
      h1_nqy2->Draw("col");
      h1_nqy2->SetMinimum(min);
      h1_nqy2->SetMaximum(max);
      h1_nqy2->GetXaxis()->SetTitle("centrality");
      h1_nqy2->GetYaxis()->SetTitle("north #LTsin 2#phi#GT");
      h1_nqy2->GetYaxis()->SetTitleOffset(1.2);
      tex.DrawLatex(0.7,0.2,Form("%s",filenames[i].Data()));
      c1->SetLogz(1);
      c1->Print(Form("RBR_figs/h1_nqy2_%s.png",filenames[i].Data()));
      c1->SetLogz(0);
      // --- get the south qy2
      TProfile* h1_sqy2 = (TProfile*) fin->Get("centrality_recoffsets_south_1_2");
      h1_sqy2->Draw("col");
      h1_sqy2->SetMinimum(min);
      h1_sqy2->SetMaximum(max);
      h1_sqy2->GetXaxis()->SetTitle("centrality");
      h1_sqy2->GetYaxis()->SetTitle("south #LTsin 2#phi#GT");
      h1_sqy2->GetYaxis()->SetTitleOffset(1.2);
      tex.DrawLatex(0.7,0.2,Form("%s",filenames[i].Data()));
      c1->SetLogz(1);
      c1->Print(Form("RBR_figs/h1_sqy2_%s.png",filenames[i].Data()));
      c1->SetLogz(0);
      // --- get the north qx3
      TProfile* h1_nqx3 = (TProfile*) fin->Get("centrality_recoffsets_north_0_3");
      h1_nqx3->Draw("col");
      h1_nqx3->SetMinimum(min);
      h1_nqx3->SetMaximum(max);
      h1_nqx3->GetXaxis()->SetTitle("centrality");
      h1_nqx3->GetYaxis()->SetTitle("north #LTcos 3#phi#GT");
      h1_nqx3->GetYaxis()->SetTitleOffset(1.2);
      tex.DrawLatex(0.7,0.2,Form("%s",filenames[i].Data()));
      c1->SetLogz(1);
      c1->Print(Form("RBR_figs/h1_nqx3_%s.png",filenames[i].Data()));
      c1->SetLogz(0);
      // --- get the south qx3
      TProfile* h1_sqx3 = (TProfile*) fin->Get("centrality_recoffsets_south_0_3");
      h1_sqx3->Draw("col");
      h1_sqx3->SetMinimum(min);
      h1_sqx3->SetMaximum(max);
      h1_sqx3->GetXaxis()->SetTitle("centrality");
      h1_sqx3->GetYaxis()->SetTitle("south #LTcos 3#phi#GT");
      h1_sqx3->GetYaxis()->SetTitleOffset(1.2);
      tex.DrawLatex(0.7,0.2,Form("%s",filenames[i].Data()));
      c1->SetLogz(1);
      c1->Print(Form("RBR_figs/h1_sqx3_%s.png",filenames[i].Data()));
      c1->SetLogz(0);
      // --- get the north qy3
      TProfile* h1_nqy3 = (TProfile*) fin->Get("centrality_recoffsets_north_1_3");
      h1_nqy3->Draw("col");
      h1_nqy3->SetMinimum(min);
      h1_nqy3->SetMaximum(max);
      h1_nqy3->GetXaxis()->SetTitle("centrality");
      h1_nqy3->GetYaxis()->SetTitle("north #LTsin 3#phi#GT");
      h1_nqy3->GetYaxis()->SetTitleOffset(1.2);
      tex.DrawLatex(0.7,0.2,Form("%s",filenames[i].Data()));
      c1->SetLogz(1);
      c1->Print(Form("RBR_figs/h1_nqy3_%s.png",filenames[i].Data()));
      c1->SetLogz(0);
      // --- get the south qy3
      TProfile* h1_sqy3 = (TProfile*) fin->Get("centrality_recoffsets_south_1_3");
      h1_sqy3->Draw("col");
      h1_sqy3->SetMinimum(min);
      h1_sqy3->SetMaximum(max);
      h1_sqy3->GetXaxis()->SetTitle("centrality");
      h1_sqy3->GetYaxis()->SetTitle("south #LTsin 3#phi#GT");
      h1_sqy3->GetYaxis()->SetTitleOffset(1.2);
      tex.DrawLatex(0.7,0.2,Form("%s",filenames[i].Data()));
      c1->SetLogz(1);
      c1->Print(Form("RBR_figs/h1_sqy3_%s.png",filenames[i].Data()));
      c1->SetLogz(0);
      // --- all done
      fin->Close();
      // --- this extra line doesn't harm anything but doesn't help
      // --- after a certain number of files i got a system error about too many files open
      // --- one need only check ulimit -n and then adjust as needed
      // --- i've added that line to my .bashrc file so that it's never a problem
      fin->Delete();
    }

}
