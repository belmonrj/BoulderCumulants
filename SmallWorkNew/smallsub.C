#include "../WorkAuAu/calc_subevents.C"

void make206(TH1D*,TH1D*,TH1D*);

void smallsub()
{

  TFile* fin = TFile::Open("tree_new.root");

  // --- from AuAu code
  TProfile* tp1f_for = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c24");
  TProfile* tp1f_4aabb = (TProfile*)fin->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c24a");
  TProfile* tp1f_4abab = (TProfile*)fin->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c24b");
  TProfile* tp1f_two = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c22");
  TProfile* tp1f_2aa = (TProfile*)fin->Get("nfvtxt_ac_fvtxs_tracks_c22");
  TProfile* tp1f_2bb = (TProfile*)fin->Get("nfvtxt_ac_fvtxn_tracks_c22");
  TProfile* tp1f_2ab = (TProfile*)fin->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c22");
  // --- rebin 1
  TH1D* h1v24 = NULL;
  TH1D* h1v24aabb = NULL;
  TH1D* h1v24abab = NULL;
  TH1D* h1v22 = NULL;
  TH1D* h1v22ab = NULL;
  TH1D* h1c24 = NULL;
  TH1D* h1c24aabb = NULL;
  TH1D* h1c24abab = NULL;
  TH1D* h1c22 = NULL;
  TH1D* h1c22ab = NULL;
  calc_subevents(tp1f_for, tp1f_4aabb, tp1f_4abab,
                 tp1f_two, tp1f_2aa, tp1f_2bb, tp1f_2ab,
                 &h1v24, &h1v24aabb, &h1v24abab, &h1v22, &h1v22ab,
                 &h1c24, &h1c24aabb, &h1c24abab, &h1c22, &h1c22ab,
                 1);
  // --- rebin 2
  TH1D* h2v24 = NULL;
  TH1D* h2v24aabb = NULL;
  TH1D* h2v24abab = NULL;
  TH1D* h2v22 = NULL;
  TH1D* h2v22ab = NULL;
  TH1D* h2c24 = NULL;
  TH1D* h2c24aabb = NULL;
  TH1D* h2c24abab = NULL;
  TH1D* h2c22 = NULL;
  TH1D* h2c22ab = NULL;
  calc_subevents(tp1f_for, tp1f_4aabb, tp1f_4abab,
                 tp1f_two, tp1f_2aa, tp1f_2bb, tp1f_2ab,
                 &h2v24, &h2v24aabb, &h2v24abab, &h2v22, &h2v22ab,
                 &h2c24, &h2c24aabb, &h2c24abab, &h2c22, &h2c22ab,
                 2);
  // --- rebin 5
  TH1D* h5v24 = NULL;
  TH1D* h5v24aabb = NULL;
  TH1D* h5v24abab = NULL;
  TH1D* h5v22 = NULL;
  TH1D* h5v22ab = NULL;
  TH1D* h5c24 = NULL;
  TH1D* h5c24aabb = NULL;
  TH1D* h5c24abab = NULL;
  TH1D* h5c22 = NULL;
  TH1D* h5c22ab = NULL;
  calc_subevents(tp1f_for, tp1f_4aabb, tp1f_4abab,
                 tp1f_two, tp1f_2aa, tp1f_2bb, tp1f_2ab,
                 &h5v24, &h5v24aabb, &h5v24abab, &h5v22, &h5v22ab,
                 &h5c24, &h5c24aabb, &h5c24abab, &h5c22, &h5c22ab,
                 5);

  // --- now make a plot or two...
  make206(h1v22,h1v22ab,h2v24);

}

void make206(TH1D* hv22, TH1D*hv22gap, TH1D* hv24)
{

  // --- Step 7: make a plot or two
  TCanvas* c1 = new TCanvas("c1","");
  hv22->SetMarkerStyle(kFullCircle);
  hv22->SetMarkerColor(kRed);
  hv22->SetMinimum(0.0);
  hv22->SetMaximum(0.13999);
  hv22->GetXaxis()->SetRangeUser(0.00001,49.9999);
  hv22->Draw("ex0p");
  hv22gap->SetMarkerStyle(kFullDiamond);
  hv22gap->SetMarkerColor(kMagenta+2);
  hv22gap->Draw("ex0p same");
  hv24->SetMarkerStyle(kFullSquare);
  hv24->SetMarkerColor(kBlue);
  hv24->Draw("ex0p same");
  c1->Print("figs/newcheck_206.png");
  delete c1;

}
