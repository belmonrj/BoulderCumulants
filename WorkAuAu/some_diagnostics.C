void some_diagnostics()
{

  TCanvas* c1 = new TCanvas("c1","");

  TFile* file = TFile::Open("input/histos_12587.root");

  TH2D* th2d_chi2 = (TH2D*)file->Get("th2d_cent_chisq");
  TH1D* th1d_chi2 = th2d_chi2->ProjectionY("th1d_chi2",1,100);
  th1d_chi2->Draw();
  c1->Print("FigsDiagnostics/th1d_chi2.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_chi2 = th2d_chi2->ProjectionY(Form("th1d_cent%02d_chi2",i),i+1,i+1);
      th1d_cent_chi2->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_chi2.png",i));
    }

  TH2D* th2d_chi2 = (TH2D*)file->Get("th2d_cent_chisq");
  TH1D* th1d_chi2 = th2d_chi2->ProjectionY("th1d_chi2",1,100);
  th1d_chi2->Draw();
  c1->Print("FigsDiagnostics/th1d_chi2.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_chi2 = th2d_chi2->ProjectionY(Form("th1d_cent%02d_chi2",i),i+1,i+1);
      th1d_cent_chi2->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_chi2.png",i));
    }

}
