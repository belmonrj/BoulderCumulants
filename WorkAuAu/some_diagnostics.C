void track_parameters();
void track_coordinates();
void track_coordinates_rebinned();

void some_diagnostics()
{
  track_parameters();
  //track_coordinates();
  //track_coordinates_rebinned();
}

void track_parameters()
{

  gStyle->SetOptTitle(1);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.08);

  TCanvas* c1 = new TCanvas("c1","");

  TFile* file = TFile::Open("input/histos_12587.root");

  // --- chi2
  TH2D* th2d_chi2 = (TH2D*)file->Get("th2d_cent_chisq");
  TH1D* th1d_chi2 = th2d_chi2->ProjectionY("th1d_chi2",1,100);
  th1d_chi2->Draw();
  c1->Print("FigsDiagnostics/th1d_chi2.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_chi2 = th2d_chi2->ProjectionY(Form("th1d_cent%02d_chi2",i),i+1,i+1);
      th1d_cent_chi2->SetTitle(Form("centrality = %d",i));
      th1d_cent_chi2->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_chi2.png",i));
    }

  // --- dcax
  TH2D* th2d_dcax = (TH2D*)file->Get("th2d_cent_dcax");
  TH1D* th1d_dcax = th2d_dcax->ProjectionY("th1d_dcax",1,100);
  th1d_dcax->Draw();
  c1->Print("FigsDiagnostics/th1d_dcax.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_dcax = th2d_dcax->ProjectionY(Form("th1d_cent%02d_dcax",i),i+1,i+1);
      th1d_cent_dcax->SetTitle(Form("centrality = %d",i));
      th1d_cent_dcax->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_dcax.png",i));
    }

  // --- dcay
  TH2D* th2d_dcay = (TH2D*)file->Get("th2d_cent_dcay");
  TH1D* th1d_dcay = th2d_dcay->ProjectionY("th1d_dcay",1,100);
  th1d_dcay->Draw();
  c1->Print("FigsDiagnostics/th1d_dcay.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_dcay = th2d_dcay->ProjectionY(Form("th1d_cent%02d_dcay",i),i+1,i+1);
      th1d_cent_dcay->SetTitle(Form("centrality = %d",i));
      th1d_cent_dcay->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_dcay.png",i));
    }

  // --- nhitr (normal number of hits, FVTX+VTX)
  TH2D* th2d_nhitr = (TH2D*)file->Get("th2d_cent_nhitr");
  TH1D* th1d_nhitr = th2d_nhitr->ProjectionY("th1d_nhitr",1,100);
  th1d_nhitr->Draw();
  c1->Print("FigsDiagnostics/th1d_nhitr.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_nhitr = th2d_nhitr->ProjectionY(Form("th1d_cent%02d_nhitr",i),i+1,i+1);
      th1d_cent_nhitr->SetTitle(Form("centrality = %d",i));
      th1d_cent_nhitr->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_nhitr.png",i));
    }

  // --- nhits (special number of hits, FVTX only)
  TH2D* th2d_nhits = (TH2D*)file->Get("th2d_cent_nhits");
  TH1D* th1d_nhits = th2d_nhits->ProjectionY("th1d_nhits",1,100);
  th1d_nhits->Draw();
  c1->Print("FigsDiagnostics/th1d_nhits.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_nhits = th2d_nhits->ProjectionY(Form("th1d_cent%02d_nhits",i),i+1,i+1);
      th1d_cent_nhits->SetTitle(Form("centrality = %d",i));
      th1d_cent_nhits->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_nhits.png",i));
    }

} // track_parameters

void track_coordinates()
{

  gStyle->SetOptTitle(1);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.08);

  TCanvas* c1 = new TCanvas("c1","");

  TFile* file = TFile::Open("input/histos_12587.root");

  // --- before_phi (phi distribution before track selection cuts)
  TH2D* th2d_before_phi = (TH2D*)file->Get("th2d_track_before_phi");
  TH1D* th1d_before_phi = th2d_before_phi->ProjectionY("th1d_before_phi",1,100);
  th1d_before_phi->Draw();
  c1->Print("FigsDiagnostics/th1d_before_phi.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_before_phi = th2d_before_phi->ProjectionY(Form("th1d_cent%02d_before_phi",i),i+1,i+1);
      th1d_cent_before_phi->SetTitle(Form("centrality = %d",i));
      th1d_cent_before_phi->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_before_phi.png",i));
    }

  // --- after_phi (phi distribution after track selection cuts)
  TH2D* th2d_after_phi = (TH2D*)file->Get("th2d_track_after_phi");
  TH1D* th1d_after_phi = th2d_after_phi->ProjectionY("th1d_after_phi",1,100);
  th1d_after_phi->Draw();
  c1->Print("FigsDiagnostics/th1d_after_phi.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_after_phi = th2d_after_phi->ProjectionY(Form("th1d_cent%02d_after_phi",i),i+1,i+1);
      th1d_cent_after_phi->SetTitle(Form("centrality = %d",i));
      th1d_cent_after_phi->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_after_phi.png",i));
    }

  // --- aafter_phi (phi distribution after track selection cuts AND double track cut)
  TH2D* th2d_aafter_phi = (TH2D*)file->Get("th2d_track_aafter_phi");
  TH1D* th1d_aafter_phi = th2d_aafter_phi->ProjectionY("th1d_aafter_phi",1,100);
  th1d_aafter_phi->Draw();
  c1->Print("FigsDiagnostics/th1d_aafter_phi.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_aafter_phi = th2d_aafter_phi->ProjectionY(Form("th1d_cent%02d_aafter_phi",i),i+1,i+1);
      th1d_cent_aafter_phi->SetTitle(Form("centrality = %d",i));
      th1d_cent_aafter_phi->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_aafter_phi.png",i));
    }

  // --- before_eta (eta distribution before track selection cuts)
  TH2D* th2d_before_eta = (TH2D*)file->Get("th2d_track_before_eta");
  TH1D* th1d_before_eta = th2d_before_eta->ProjectionY("th1d_before_eta",1,100);
  th1d_before_eta->Draw();
  c1->Print("FigsDiagnostics/th1d_before_eta.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_before_eta = th2d_before_eta->ProjectionY(Form("th1d_cent%02d_before_eta",i),i+1,i+1);
      th1d_cent_before_eta->SetTitle(Form("centrality = %d",i));
      th1d_cent_before_eta->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_before_eta.png",i));
    }

  // --- after_eta (eta distribution after track selection cuts)
  TH2D* th2d_after_eta = (TH2D*)file->Get("th2d_track_after_eta");
  TH1D* th1d_after_eta = th2d_after_eta->ProjectionY("th1d_after_eta",1,100);
  th1d_after_eta->Draw();
  c1->Print("FigsDiagnostics/th1d_after_eta.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_after_eta = th2d_after_eta->ProjectionY(Form("th1d_cent%02d_after_eta",i),i+1,i+1);
      th1d_cent_after_eta->SetTitle(Form("centrality = %d",i));
      th1d_cent_after_eta->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_after_eta.png",i));
    }

  // --- aafter_eta (eta distribution after track selection cuts AND double track cut)
  TH2D* th2d_aafter_eta = (TH2D*)file->Get("th2d_track_aafter_eta");
  TH1D* th1d_aafter_eta = th2d_aafter_eta->ProjectionY("th1d_aafter_eta",1,100);
  th1d_aafter_eta->Draw();
  c1->Print("FigsDiagnostics/th1d_aafter_eta.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_aafter_eta = th2d_aafter_eta->ProjectionY(Form("th1d_cent%02d_aafter_eta",i),i+1,i+1);
      th1d_cent_aafter_eta->SetTitle(Form("centrality = %d",i));
      th1d_cent_aafter_eta->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_aafter_eta.png",i));
    }

} // track_coordinates

void track_coordinates_rebinned()
{

  gStyle->SetOptTitle(1);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.08);

  int rebin = 5;

  TCanvas* c1 = new TCanvas("c1","");

  TFile* file = TFile::Open("input/histos_12587.root");

  // --- before_phi (phi distribution before track selection cuts)
  TH2D* th2d_before_phi = (TH2D*)file->Get("th2d_track_before_phi");
  TH1D* th1d_before_phi = th2d_before_phi->ProjectionY("th1d_before_phi",1,100);
  th1d_before_phi->Rebin(rebin);
  th1d_before_phi->Draw();
  c1->Print("FigsDiagnostics/th1d_before_phi_R.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_before_phi = th2d_before_phi->ProjectionY(Form("th1d_cent%02d_before_phi",i),i+1,i+1);
      th1d_cent_before_phi->Rebin(rebin);
      th1d_cent_before_phi->SetTitle(Form("centrality = %d",i));
      th1d_cent_before_phi->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_before_phi_R.png",i));
    }

  // --- after_phi (phi distribution after track selection cuts)
  TH2D* th2d_after_phi = (TH2D*)file->Get("th2d_track_after_phi");
  TH1D* th1d_after_phi = th2d_after_phi->ProjectionY("th1d_after_phi",1,100);
  th1d_after_phi->Rebin(rebin);
  th1d_after_phi->Draw();
  c1->Print("FigsDiagnostics/th1d_after_phi_R.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_after_phi = th2d_after_phi->ProjectionY(Form("th1d_cent%02d_after_phi",i),i+1,i+1);
      th1d_cent_after_phi->Rebin(rebin);
      th1d_cent_after_phi->SetTitle(Form("centrality = %d",i));
      th1d_cent_after_phi->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_after_phi_R.png",i));
    }

  // --- aafter_phi (phi distribution after track selection cuts AND double track cut)
  TH2D* th2d_aafter_phi = (TH2D*)file->Get("th2d_track_aafter_phi");
  TH1D* th1d_aafter_phi = th2d_aafter_phi->ProjectionY("th1d_aafter_phi",1,100);
  th1d_aafter_phi->Rebin(rebin);
  th1d_aafter_phi->Draw();
  c1->Print("FigsDiagnostics/th1d_aafter_phi_R.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_aafter_phi = th2d_aafter_phi->ProjectionY(Form("th1d_cent%02d_aafter_phi",i),i+1,i+1);
      th1d_cent_aafter_phi->Rebin(rebin);
      th1d_cent_aafter_phi->SetTitle(Form("centrality = %d",i));
      th1d_cent_aafter_phi->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_aafter_phi_R.png",i));
    }

  // --- before_eta (eta distribution before track selection cuts)
  TH2D* th2d_before_eta = (TH2D*)file->Get("th2d_track_before_eta");
  TH1D* th1d_before_eta = th2d_before_eta->ProjectionY("th1d_before_eta",1,100);
  th1d_before_eta->Rebin(rebin);
  th1d_before_eta->Draw();
  c1->Print("FigsDiagnostics/th1d_before_eta_R.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_before_eta = th2d_before_eta->ProjectionY(Form("th1d_cent%02d_before_eta",i),i+1,i+1);
      th1d_cent_before_eta->Rebin(rebin);
      th1d_cent_before_eta->SetTitle(Form("centrality = %d",i));
      th1d_cent_before_eta->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_before_eta_R.png",i));
    }

  // --- after_eta (eta distribution after track selection cuts)
  TH2D* th2d_after_eta = (TH2D*)file->Get("th2d_track_after_eta");
  TH1D* th1d_after_eta = th2d_after_eta->ProjectionY("th1d_after_eta",1,100);
  th1d_after_eta->Rebin(rebin);
  th1d_after_eta->Draw();
  c1->Print("FigsDiagnostics/th1d_after_eta_R.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_after_eta = th2d_after_eta->ProjectionY(Form("th1d_cent%02d_after_eta",i),i+1,i+1);
      th1d_cent_after_eta->Rebin(rebin);
      th1d_cent_after_eta->SetTitle(Form("centrality = %d",i));
      th1d_cent_after_eta->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_after_eta_R.png",i));
    }

  // --- aafter_eta (eta distribution after track selection cuts AND double track cut)
  TH2D* th2d_aafter_eta = (TH2D*)file->Get("th2d_track_aafter_eta");
  TH1D* th1d_aafter_eta = th2d_aafter_eta->ProjectionY("th1d_aafter_eta",1,100);
  th1d_aafter_eta->Rebin(rebin);
  th1d_aafter_eta->Draw();
  c1->Print("FigsDiagnostics/th1d_aafter_eta_R.png");
  for ( int i = 0; i < 100; ++i )
    {
      TH1D* th1d_cent_aafter_eta = th2d_aafter_eta->ProjectionY(Form("th1d_cent%02d_aafter_eta",i),i+1,i+1);
      th1d_cent_aafter_eta->Rebin(rebin);
      th1d_cent_aafter_eta->SetTitle(Form("centrality = %d",i));
      th1d_cent_aafter_eta->Draw();
      c1->Print(Form("FigsDiagnostics/Centrality/th1d_cent%02d_aafter_eta_R.png",i));
    }

} // track_coordinates_rebinned

