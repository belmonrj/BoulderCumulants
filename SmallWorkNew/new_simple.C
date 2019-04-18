#include "../WorkAuAu/hsqrt.C"
#include "../WorkAuAu/calc_subevents.C"



double calc_corr_four(double,double,double,double,double,double,double,double);


TH1D* get_corr_four(TH1D*,TH1D*,TH1D*,TH1D*,TH1D*,TH1D*,TH1D*,TH1D*);

TH1D* get_v24(TH1D*,TH1D*,TH1D*);


void new_simple()
{

  // --- Step 1: open the root file with the histograms in it
  //TFile* fin = TFile::Open("temp.root");
  //TFile* fin = TFile::Open("improved_20170517-2216.root"); // checking against an old file
  //TFile* fin = TFile::Open("tree_temp.root");
  TFile* fin = TFile::Open("tree_new.root");

  // --- Step 2: get the TProfile histograms from the root file
  // --- 2-particle correlator
  TProfile* tp1f_two = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c22");
  // --- 2-particle correlator corrections
  TProfile* tp1f_cos1 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cos21");
  TProfile* tp1f_sin1 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_sin21");
  // --- 2-particle scalar product
  TProfile* tp1f_G_two = (TProfile*)fin->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c22"); // scalar product north*south
  // --- corrections for 2-particle SP
  TProfile* tp1f_cos1_north = (TProfile*)fin->Get("nfvtxt_ac_fvtxn_tracks_cos21");
  TProfile* tp1f_sin1_north = (TProfile*)fin->Get("nfvtxt_ac_fvtxn_tracks_sin21");
  TProfile* tp1f_cos1_south = (TProfile*)fin->Get("nfvtxt_ac_fvtxs_tracks_cos21");
  TProfile* tp1f_sin1_south = (TProfile*)fin->Get("nfvtxt_ac_fvtxs_tracks_sin21");
  // --- 4-particle correlator
  TProfile* tp1f_four = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c24");
  // --- corrections for 4-particle (also need 2-p corrections above)
  TProfile* tp1f_cossum2 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cossum22");
  TProfile* tp1f_sinsum2 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_sinsum22");
  TProfile* tp1f_cos3 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cos23");
  TProfile* tp1f_sin3 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_sin23");
  // --- covariance histogram for statistical studies... I should check if it's still there...
  //TProfile* tp1f_cov = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cov24");

  // --- Step 3: convert the TProfiles to TH1Ds
  // --- 2-particle correlator
  TH1D* th1d_two = tp1f_two->ProjectionX("th1d_two");
  // --- 2-particle correlator corrections
  TH1D* th1d_cos1 = tp1f_cos1->ProjectionX("th1d_cos1");
  TH1D* th1d_sin1 = tp1f_sin1->ProjectionX("th1d_sin1");
  // --- 2-particle scalar product
  TH1D* th1d_G_two = tp1f_G_two->ProjectionX("th1d_G_two");
  // --- corrections for 2-particle SP
  TH1D* th1d_cos1_north = tp1f_cos1_north->ProjectionX("th1d_cos1_north");
  TH1D* th1d_sin1_north = tp1f_sin1_north->ProjectionX("th1d_sin1_north");
  TH1D* th1d_cos1_south = tp1f_cos1_south->ProjectionX("th1d_cos1_south");
  TH1D* th1d_sin1_south = tp1f_sin1_south->ProjectionX("th1d_sin1_south");
  // --- 4-particle correlator
  TH1D* th1d_four = tp1f_four->ProjectionX("th1d_four");
  // --- corrections for 4-particle (also need 2-p corrections above)
  TH1D* th1d_cossum2 = tp1f_cossum2->ProjectionX("th1d_cossum2");
  TH1D* th1d_sinsum2 = tp1f_sinsum2->ProjectionX("th1d_sinsum2");
  TH1D* th1d_cos3 = tp1f_cos3->ProjectionX("th1d_cos3");
  TH1D* th1d_sin3 = tp1f_sin3->ProjectionX("th1d_sin3");
  // --- covariance histogram for statistical studies... I should check if it's still there...
  //TH1D* th1d_cov = tp1f_cov->ProjectionX("th1d_cov");

  // --- Step 4: make some clones
  TH1D* th1d_c22one = (TH1D*)th1d_two->Clone("th1d_c22one");
  TH1D* th1d_c22gap = (TH1D*)th1d_G_two->Clone("th1d_c22gap");
  TH1D* th1d_cos1_squared = (TH1D*)th1d_cos1->Clone("th1d_cos1_squared");
  TH1D* th1d_sin1_squared = (TH1D*)th1d_sin1->Clone("th1d_sin1_squared");
  TH1D* th1d_cos1_north_south = (TH1D*)th1d_cos1_north->Clone("th1d_cos1_north_south");
  TH1D* th1d_sin1_north_south = (TH1D*)th1d_sin1_north->Clone("th1d_sin1_north_south");
  // --- 4p clones ...
  TH1D* th1d_c24one = (TH1D*)th1d_four->Clone("th1d_c24one");
  TH1D* th1d_222one = (TH1D*)th1d_two->Clone("th1d_222one");

  // --- Step 5: calculate the cumulants
  // --- correction terms
  th1d_cos1_squared->Multiply(th1d_cos1_squared);
  th1d_sin1_squared->Multiply(th1d_sin1_squared);
  th1d_cos1_north_south->Multiply(th1d_cos1_south);
  th1d_sin1_north_south->Multiply(th1d_sin1_south);
  // --- apply correction to cumulant
  th1d_c22one->Add(th1d_cos1_squared,-1.0);
  th1d_c22one->Add(th1d_sin1_squared,-1.0);
  th1d_c22gap->Add(th1d_cos1_north_south,-1.0);
  th1d_c22gap->Add(th1d_sin1_north_south,-1.0);
  // --- 4-particle cumulant
  th1d_222one->Multiply(th1d_222one);
  th1d_222one->Scale(2.0);
  th1d_c24one->Add(th1d_222one,-1.0);
  // --- 4-particle corrections
  //TH1D* get_corr_four(TH1D* hfour, TH1D* htwo, TH1D* hcos1, TH1D* hsin1, TH1D* hcossum2, TH1D* hsinsum2, TH1D* hcos3, TH1D* hsin3)
  TH1D* th1d_c24cor = get_corr_four(th1d_four,th1d_two,th1d_cos1,th1d_sin1,th1d_cossum2,th1d_sinsum2,th1d_cos3,th1d_sin3);

  // --- Step 6: calculate v2 from cumulant
  TH1D* th1d_v22one = hsqrt(th1d_c22one);
  TH1D* th1d_v22gap = hsqrt(th1d_c22gap);
  TH1D* th1d_v24one = get_v24(th1d_c24one,th1d_four,th1d_two);
  TH1D* th1d_v24cor = get_v24(th1d_c24cor,th1d_four,th1d_two);

  // --- Step 7: make a plot or two
  TCanvas* c1 = new TCanvas("c1","");
  th1d_v22one->SetMarkerStyle(kFullCircle);
  th1d_v22one->SetMarkerColor(kRed);
  th1d_v22one->SetMinimum(0.0);
  th1d_v22one->SetMaximum(0.13999);
  th1d_v22one->GetXaxis()->SetRangeUser(0.00001,49.9999);
  th1d_v22one->Draw("ex0p");
  th1d_v22gap->SetMarkerStyle(kFullDiamond);
  th1d_v22gap->SetMarkerColor(kMagenta+2);
  th1d_v22gap->Draw("ex0p same");
  // th1d_v24one->SetMarkerStyle(kOpenSquare);
  // th1d_v24one->SetMarkerColor(kBlue);
  // th1d_v24one->Draw("ex0p same");
  th1d_v24cor->SetMarkerStyle(kFullSquare);
  th1d_v24cor->SetMarkerColor(kBlue);
  th1d_v24cor->Draw("ex0p same");
  c1->Print("check_v22.png");

  // --- from AuAu code
  TProfile* tp1f_for = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c24");
  TProfile* tp1f_4aabb = (TProfile*)fin->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c24a");
  TProfile* tp1f_4abab = (TProfile*)fin->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c24b");
  //TProfile* tp1f_two = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c22");
  tp1f_two = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c22");
  TProfile* tp1f_2aa = (TProfile*)fin->Get("nfvtxt_ac_fvtxs_tracks_c22");
  TProfile* tp1f_2bb = (TProfile*)fin->Get("nfvtxt_ac_fvtxn_tracks_c22");
  TProfile* tp1f_2ab = (TProfile*)fin->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c22");
  // ---
  TH1D* hv24 = NULL;
  TH1D* hv24aabb = NULL;
  TH1D* hv24abab = NULL;
  TH1D* hv22 = NULL;
  TH1D* hv22ab = NULL;
  TH1D* hc24 = NULL;
  TH1D* hc24aabb = NULL;
  TH1D* hc24abab = NULL;
  TH1D* hc22 = NULL;
  TH1D* hc22ab = NULL;
  calc_subevents(tp1f_for, tp1f_4aabb, tp1f_4abab,
                 tp1f_two, tp1f_2aa, tp1f_2bb, tp1f_2ab,
                 &hv24, &hv24aabb, &hv24abab, &hv22, &hv22ab,
                 &hc24, &hc24aabb, &hc24abab, &hc22, &hc22ab,
                 5);

  hv24aabb->SetMarkerStyle(kOpenSquare);
  hv24aabb->SetMarkerColor(kBlack);
  hv24aabb->Draw("ex0p same");
  hv24abab->SetMarkerStyle(kOpenCircle);
  hv24abab->SetMarkerColor(kBlack);
  hv24abab->Draw("ex0p same");
  c1->Print("check_v22_addsub.png");

  hc24->Rebin(2);
  hc24->Scale(0.5);

  TH2D* hdummy = new TH2D("hdummy","",1,0,49.999,1,-1e-3,1e-3);
  // hdummy->GetYaxis()->SetTitle("c_{2}{4}");
  // hdummy->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle("c_{2}{4}");
  hdummy->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  hc24->SetMarkerStyle(kFullCircle);
  hc24->SetMarkerColor(kBlack);
  hc24->Draw("ex0p same");
  hc24aabb->SetMarkerStyle(kOpenSquare);
  hc24aabb->SetMarkerColor(kBlack);
  hc24aabb->Draw("ex0p same");
  hc24abab->SetMarkerStyle(kOpenCircle);
  hc24abab->SetMarkerColor(kBlack);
  hc24abab->Draw("ex0p same");
  TLegend* leg2 = new TLegend(0.18,0.81,0.38,0.88);
  leg2->SetHeader("d+Au at #sqrt{s_{NN}} = 200 GeV");
  leg2->Draw();
  TLegend* leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->AddEntry(hc24,"c_{2}{4}","p");
  leg->AddEntry(hc24abab,"c_{2}{4}_{ab|ab}","p");
  leg->AddEntry(hc24aabb,"c_{2}{4}_{aa|bb}","p");
  leg->SetFillStyle(0);
  leg->Draw();
  c1->Print("check_c24_addsub.png");

  delete hdummy;
  hdummy = new TH2D("hdummy","",1,0,49.999,1,-2.5e-5,2.5e-5);
  // hdummy->GetYaxis()->SetTitle("c_{2}{4}");
  // hdummy->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle("c_{2}{4}");
  hdummy->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  hdummy->GetYaxis()->SetTitle("c_{2}{4}");
  hc24->SetMarkerStyle(kFullCircle);
  hc24->SetMarkerColor(kBlack);
  hc24->Draw("ex0p same");
  hc24aabb->SetMarkerStyle(kOpenSquare);
  hc24aabb->SetMarkerColor(kBlack);
  hc24aabb->Draw("ex0p same");
  hc24abab->SetMarkerStyle(kOpenCircle);
  hc24abab->SetMarkerColor(kBlack);
  hc24abab->Draw("ex0p same");
  hdummy->GetYaxis()->SetTitle("c_{2}{4}");
  leg2->Draw();
  leg->Draw();
  c1->Print("check_c24_addsub_zoom.png");

}



TH1D* get_corr_four(TH1D* hfour, TH1D* htwo, TH1D* hcos1, TH1D* hsin1, TH1D* hcossum2, TH1D* hsinsum2, TH1D* hcos3, TH1D* hsin3)
{
  TH1D* giveback = (TH1D*)hfour->Clone(hfour->GetName());
  for ( int i = 0; i < giveback->GetNbinsX(); ++i )
    {
      double four = hfour->GetBinContent(i+1);
      double two = htwo->GetBinContent(i+1);
      double cos1 = hcos1->GetBinContent(i+1);
      double sin1 = hsin1->GetBinContent(i+1);
      double cossum2 = hcossum2->GetBinContent(i+1);
      double sinsum2 = hsinsum2->GetBinContent(i+1);
      double cos3 = hcos3->GetBinContent(i+1);
      double sin3 = hsin3->GetBinContent(i+1);
      double corr_c24 = calc_corr_four(four,two,cos1,sin1,cossum2,sinsum2,cos3,sin3);
      giveback->SetBinContent(i+1,corr_c24);
      double efour = hfour->GetBinError(i+1);
      double error = (efour/four)*corr_c24;
      giveback->SetBinError(i+1,error);
    }
  return giveback;
}



double calc_corr_four(double four, double two, double cos1, double sin1, double cossum2, double sinsum2, double cos3, double sin3)
{
  double uncorr = four - 2*two*two;
  double corr_term1 = 4*cos1*cos3;
  double corr_term2 = 4*sin1*sin3;
  double corr_term3 = cossum2*cossum2;
  double corr_term4 = sinsum2*sinsum2;
  double corr_term5 = 4*cossum2*(cos1*cos1 - sin1*sin1);
  double corr_term6 = 8*sinsum2*sin1*cos1;
  double corr_term7 = 8*two*(cos1*cos1 + sin1*sin1);
  double corr_term8 = 6*(cos1*cos1 + sin1*sin1)*(cos1*cos1 + sin1*sin1);
  double result = uncorr - corr_term1 + corr_term2 - corr_term3 - corr_term4 + corr_term5 + corr_term6 + corr_term7 - corr_term8;
  return result;
}

TH1D* get_v24(TH1D* th1d_c24, TH1D* th1d_for, TH1D* th1d_two)
{
  TH1D* th1d_v24 = (TH1D*)th1d_c24->Clone(Form("%s",th1d_c24->GetName()));
  for ( int i = 0; i < th1d_c24->GetNbinsX(); ++i )
    {
      double c24 = th1d_c24->GetBinContent(i+1);
      double v24 = -9999;
      double two = th1d_two->GetBinContent(i+1);
      double etwo = th1d_two->GetBinError(i+1);
      double four = th1d_for->GetBinContent(i+1);
      double efour = th1d_for->GetBinError(i+1);
      double ev24 = 0;
      if ( c24 < 0 && four != 0 )
        {
          v24 = pow(-c24,(1.0/4.0)); // v2{4} = -c2{4}^{(1/4)}
          ev24 = (1.0/pow(-c24,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
        }
      th1d_v24->SetBinContent(i+1,v24);
      th1d_v24->SetBinError(i+1,ev24);
    }
  return th1d_v24;
}
