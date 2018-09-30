#include "hsqrt.C"

void doit(const char*);

void checker_v3()
{
  // --- need to build in fault tolerance for missing histograms
  doit("12097");
  //doit("12579");
  //doit("12587");
  doit("12634");
  //doit("12650");
  //doit("13792");
  doit("13799");
}

void doit(const char* handle)
{

  TCanvas* c1 = new TCanvas("c1","");

  int rebin = 2;

  TFile* fin = TFile::Open(Form("input/histos_%s.root",handle));

  // --- get the histograms from the file
  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_c32");
  TProfile* tp1f_cos1 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_cos31");
  TProfile* tp1f_sin1 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_sin31");
  TProfile* tp1f_G_two = (TProfile*)fin->Get("centrality_ac_fvtxsfvtxn_tracks_c32"); // scalar product north*south
  TProfile* tp1f_cos1_north = (TProfile*)fin->Get("centrality_ac_fvtxn_tracks_cos31");
  TProfile* tp1f_sin1_north = (TProfile*)fin->Get("centrality_ac_fvtxn_tracks_sin31");
  TProfile* tp1f_cos1_south = (TProfile*)fin->Get("centrality_ac_fvtxs_tracks_cos31");
  TProfile* tp1f_sin1_south = (TProfile*)fin->Get("centrality_ac_fvtxs_tracks_sin31");

  // --- check existence
  if ( !tp1f_two) cout << "tp1f_two" << endl;
  if ( !tp1f_cos1) cout << "tp1f_cos1" << endl;
  if ( !tp1f_sin1) cout << "tp1f_sin1" << endl;
  if ( !tp1f_G_two) cout << "tp1f_G_two" << endl;
  if ( !tp1f_cos1_north) cout << "tp1f_cos1_north" << endl;
  if ( !tp1f_sin1_north) cout << "tp1f_sin1_north" << endl;
  if ( !tp1f_cos1_south) cout << "tp1f_cos1_south" << endl;
  if ( !tp1f_sin1_south) cout << "tp1f_sin1_south" << endl;

  // --- rebin as desired, rebinning on TProfile ensure weighted averages and uncertainties are done correctly
  tp1f_two->Rebin(rebin);
  tp1f_cos1->Rebin(rebin);
  tp1f_sin1->Rebin(rebin);
  tp1f_G_two->Rebin(rebin);
  tp1f_cos1_north->Rebin(rebin);
  tp1f_sin1_north->Rebin(rebin);
  tp1f_cos1_south->Rebin(rebin);
  tp1f_sin1_south->Rebin(rebin);

  TH1D* th1d_two = tp1f_two->ProjectionX("th1d_two");
  TH1D* th1d_cos1 = tp1f_cos1->ProjectionX("th1d_cos1");
  TH1D* th1d_sin1 = tp1f_sin1->ProjectionX("th1d_sin1");
  TH1D* th1d_G_two = tp1f_G_two->ProjectionX("th1d_G_two");
  TH1D* th1d_cos1_north = tp1f_cos1_north->ProjectionX("th1d_cos1_north");
  TH1D* th1d_sin1_north = tp1f_sin1_north->ProjectionX("th1d_sin1_north");
  TH1D* th1d_cos1_south = tp1f_cos1_south->ProjectionX("th1d_cos1_south");
  TH1D* th1d_sin1_south = tp1f_sin1_south->ProjectionX("th1d_sin1_south");

  // --- make some clones to ensure the same binning (number and range)
  //TH1D* th1d_two = tp1f_two->ProjectionX("th1d_two");
  TH1D* th1d_corr_c32 = (TH1D*)th1d_two->Clone("th1d_corr_c32");
  TH1D* th1d_corr_c3G = (TH1D*)th1d_G_two->Clone("th1d_corr_c3G");
  TH1D* th1d_uncorr_c32 = (TH1D*)th1d_two->Clone("th1d_uncorr_c32");
  TH1D* th1d_uncorr_c3G = (TH1D*)th1d_G_two->Clone("th1d_uncorr_c3G");

  th1d_cos1->Multiply(th1d_cos1);
  th1d_sin1->Multiply(th1d_sin1);
  th1d_corr_c32->Add(th1d_cos1,-1.0);
  th1d_corr_c32->Add(th1d_sin1,-1.0);
  TH1D* th1d_corr_v32 = hsqrt(th1d_corr_c32);

  th1d_cos1_north->Multiply(th1d_cos1_south);
  th1d_sin1_north->Multiply(th1d_sin1_south);
  th1d_corr_c3G->Add(th1d_cos1_north,-1.0);
  th1d_corr_c3G->Add(th1d_sin1_north,-1.0);
  TH1D* th1d_corr_v3G = hsqrt(th1d_corr_c3G);



  th1d_corr_v32->SetMarkerColor(kRed);
  th1d_corr_v32->SetMarkerStyle(kFullSquare);
  th1d_corr_v3G->SetMarkerColor(kMagenta+2);
  th1d_corr_v3G->SetMarkerStyle(kFullDiamond);

  TH2D* hdummy = new TH2D("hdummy","", 1,0.0,100.0, 1,0.0,0.1);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle("v_{3}{2}");
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  th1d_corr_v32->Draw("ex0p same");
  th1d_corr_v3G->Draw("ex0p same");

  //c1->Print(Form("FigsWork/v32comp_%s.png",handle));

  TProfile* tp1f_two_os = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c32");
  TProfile* tp1f_G_two_os = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c32"); // scalar product north*south
  tp1f_two_os->Rebin(rebin);
  tp1f_G_two_os->Rebin(rebin);

  TH1D* th1d_os_v32 = hsqrt(tp1f_two_os);
  TH1D* th1d_os_v3G = hsqrt(tp1f_G_two_os);

  th1d_os_v32->SetMarkerColor(kRed);
  th1d_os_v32->SetMarkerStyle(kOpenSquare);
  th1d_os_v3G->SetMarkerColor(kMagenta+2);
  th1d_os_v3G->SetMarkerStyle(kOpenDiamond);
  th1d_os_v3G->SetMarkerSize(1.9);

  th1d_os_v32->Draw("ex0p same");
  th1d_os_v3G->Draw("ex0p same");

  TLegend* leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->AddEntry(th1d_corr_v32,"corr","p");
  leg->AddEntry(th1d_os_v32,"offs","p");
  leg->AddEntry(th1d_corr_v3G,"corr","p");
  leg->AddEntry(th1d_os_v3G,"offs","p");
  leg->SetTextSize(0.05);
  leg->Draw();

  c1->Print(Form("FigsWork/v32compmore_%s.png",handle));

  delete c1;

}

