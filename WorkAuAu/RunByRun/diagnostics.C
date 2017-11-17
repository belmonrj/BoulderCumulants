#include "filenames.C"

const int nhistos = 60;




void diagnostics()
{

  TCanvas* c1 = new TCanvas("c1","");

  for ( int i = 0; i < nhistos; ++i )
    {
      // --- open the file
      //TFile* fin = TFile::Open(filenames[i]);
      TFile* fin = TFile::Open(Form("SpecialFiles/%s",filenames[i].Data()));
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
      // --- all done
      fin->Close();
    }

}
