void compare_ampt()
{

  // --------------------------------------------------------------------------------
  // --- get the histograms from the files

  gROOT->ProcessLine("gErrorIgnoreLevel = 2002;");
  TFile* fampt = TFile::Open("input/cumulants_ampt_auau200_comb.root");
  gROOT->ProcessLine("gErrorIgnoreLevel = 0;");

  TProfile* tp1f_for_ampt = (TProfile*)fampt->Get("raa4_Ncharge");
  TProfile* tp1f_two_ampt = (TProfile*)fampt->Get("daa2_Ncharge");
  TProfile* tp1f_gap_ampt = (TProfile*)fampt->Get("daa2_with_gap_Ncharge");

  TFile* fdata = TFile::Open("input/histos_11617.root");

  TProfile* tp1f_for_data = (TProfile*)fdata->Get("nfvtxt_os_fvtxc_tracks_c24");
  TProfile* tp1f_two_data = (TProfile*)fdata->Get("nfvtxt_os_fvtxc_tracks_c22");
  TProfile* tp1f_gap_data = (TProfile*)fdata->Get("nfvtxt_os_fvtxsfvtxn_tracks_c22");

  // --------------------------------------------------------------------------------
  // --- apply rebinning to TProfile histos

  int rebin = 2;

  tp1f_for_ampt->Rebin(rebin);
  tp1f_two_ampt->Rebin(rebin);
  tp1f_gap_ampt->Rebin(rebin);

  tp1f_for_data->Rebin(rebin);
  tp1f_two_data->Rebin(rebin);
  tp1f_gap_data->Rebin(rebin);

  // --------------------------------------------------------------------------------
  // --- make the cumulants

  TH1D* th1d_for_ampt = tp1f_for_ampt->ProjectionX("th1d_for_ampt");
  TH1D* th1d_two_ampt = tp1f_two_ampt->ProjectionX("th1d_two_ampt");
  TH1D* th1d_222_ampt = (TH1D*)th1d_two_ampt->Clone("th1d_222_ampt");
  th1d_222_ampt->Multiply(th1d_two_ampt);
  th1d_222_ampt->Scale(2);
  TH1D* th1d_c24_ampt = (TH1D*)th1d_for_ampt->Clone("th1d_c24");
  th1d_c24_ampt->Add(th1d_222_ampt,-1);

  TH1D* th1d_for_data = tp1f_for_data->ProjectionX("th1d_for_data");
  TH1D* th1d_two_data = tp1f_two_data->ProjectionX("th1d_two_data");
  TH1D* th1d_222_data = (TH1D*)th1d_two_data->Clone("th1d_222_data");
  th1d_222_data->Multiply(th1d_two_data);
  th1d_222_data->Scale(2);
  TH1D* th1d_c24_data = (TH1D*)th1d_for_data->Clone("th1d_c24");
  th1d_c24_data->Add(th1d_222_data,-1);

  // --------------------------------------------------------------------------------
  // --- turn the ampt c24 into a tgrapherrors
  int n = th1d_c24_ampt->GetNbinsX();
  double* x = new double[n];
  double* y = new double[n];
  double* ex = new double[n];
  double* ey = new double[n];
  for ( int i = 0; i < n; ++i )
    {
      x[i] = th1d_c24_ampt->GetBinCenter(i+1);
      y[i] = th1d_c24_ampt->GetBinContent(i+1);
      ex[i] = 0;
      ey[i] = th1d_c24_ampt->GetBinError(i+1);
    }
  TGraphErrors* tge_c24_ampt = new TGraphErrors(n,x,y,ex,ey);
  // --------------------------------------------------------------------------------
  // --- make some plots

  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = -1e-4;
  double ymax = 1e-4;

  //-- setup canvas
  //-- Margins
  float Lmarg = 0.14;
  float Rmarg = 0.02;
  // float Bmarg = 0.10;
  // float Bmarg = 0.14; // not quite enough
  //float Bmarg = 0.2; // a little too much
  float Bmarg = 0.16;
  float Tmarg = 0.02;

  double w = 800 / (1 + Lmarg + Rmarg);
  double h = 900 / (1 + Bmarg + Tmarg);

  TCanvas *ccomp4 = new TCanvas("ccomp4", "", w, h);
  ccomp4->SetMargin(0, 0, 0, 0);

  ccomp4->cd();
  TPad *pcomp4 = new TPad("pcomp4", "comp4", 0, 0.45, 1, 1);
  pcomp4->SetMargin(Lmarg, Rmarg, 0, 0.1);
  pcomp4->SetTicks(1, 1);
  pcomp4->Draw();

  ccomp4->cd();
  TPad *pcumu4 = new TPad("pcumu4", "cumu4", 0, 0, 1, 0.45);
  pcumu4->SetMargin(Lmarg, Rmarg, 0.22, 0);
  pcumu4->SetTicks(1, 1);
  pcumu4->Draw();

  //-- plot
  pcomp4->cd();
  ymin = -1e-5;
  ymax = 1e-4;
  TH2D* empty_comp4 = new TH2D("empty_comp4","",1,xmin,xmax,1,ymin,ymax);
  empty_comp4->Draw();
  empty_comp4->GetXaxis()->SetLabelSize(0.0);
  empty_comp4->GetXaxis()->SetTitleSize(0.0);
  empty_comp4->GetYaxis()->SetLabelFont(62);
  empty_comp4->GetYaxis()->SetTitleFont(62);
  empty_comp4->GetYaxis()->SetLabelSize(0.075);
  empty_comp4->GetYaxis()->SetTitleSize(0.075);
  empty_comp4->GetYaxis()->SetTitle("components");
  th1d_222_data->SetMarkerStyle(kOpenCircle);
  th1d_222_data->SetMarkerColor(kRed);
  th1d_222_data->SetLineColor(kBlack);
  th1d_222_data->Draw("same ex0p");
  th1d_for_data->SetMarkerStyle(kOpenSquare);
  th1d_for_data->SetMarkerColor(kBlue);
  th1d_for_data->SetLineColor(kBlack);
  th1d_for_data->Draw("same ex0p");
  TLine *cline = new TLine(xmin,0,xmax,0);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  TLegend* leg_comp4 = new TLegend(0.18,0.70,0.4,0.85);
  leg_comp4->SetTextFont(62);
  leg_comp4->SetTextSize(0.075);
  leg_comp4->SetFillStyle(0);
  leg_comp4->AddEntry(th1d_222_data,"2#LT#LT2#GT#GT^{2}","p");
  leg_comp4->AddEntry(th1d_for_data,"#LT#LT4#GT#GT","p");
  leg_comp4->Draw();

  //-- ratio
  pcumu4->cd();
  ymin = -1.999e-5;
  ymax = 1.999e-5;
  TH2D* empty_cumu4 = new TH2D("empty_cumu4","",1,xmin,xmax,1,ymin,ymax);
  empty_cumu4->Draw();
  //empty_cumu4->GetXaxis()->SetTitle("Centrality (%)");
  empty_cumu4->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty_cumu4->GetXaxis()->SetLabelFont(62);
  empty_cumu4->GetXaxis()->SetTitleFont(62);
  empty_cumu4->GetXaxis()->SetLabelSize(0.090);
  empty_cumu4->GetXaxis()->SetTitleSize(0.090);
  empty_cumu4->GetYaxis()->SetLabelFont(62);
  empty_cumu4->GetYaxis()->SetTitleFont(62);
  empty_cumu4->GetYaxis()->SetLabelSize(0.090);
  empty_cumu4->GetYaxis()->SetTitleSize(0.090);
  empty_cumu4->GetYaxis()->SetTitle("cumulant");
  empty_cumu4->GetYaxis()->SetTitleOffset(0.8);
  // --- this part is tricky
  //th1d_c24_ampt->SetLineColor(kBlack);
  //th1d_c24_ampt->Draw("same HIST L");
  // tge_c24_ampt->SetLineColor(kBlack);
  // tge_c24_ampt->SetFillColor(kGray);
  // tge_c24_ampt->Draw("LE3");
  th1d_c24_ampt->SetMarkerSize(0);
  th1d_c24_ampt->SetLineWidth(2);
  th1d_c24_ampt->SetLineColor(kGreen+2);
  th1d_c24_ampt->SetFillColorAlpha(kGreen+2, 0.4);
  TH1D* cloned = (TH1D*)th1d_c24_ampt->Clone("cloned");
  cloned->SetFillColorAlpha(kGreen+2,0.0);
  cloned->Draw("HIST L same");
  th1d_c24_ampt->Draw("LE3 same");
  // ---
  th1d_c24_data->SetMarkerStyle(kOpenCircle);
  th1d_c24_data->SetLineColor(kBlack);
  th1d_c24_data->Draw("same ex0p");
  TLegend* leg_cumu4 = new TLegend(0.18,0.80,0.4,0.95);
  leg_cumu4->SetTextFont(62);
  leg_cumu4->SetTextSize(0.090);
  leg_cumu4->SetFillStyle(0);
  leg_cumu4->AddEntry(th1d_c24_data,"c_{2}{4} = -v_{2}^{4}","p");
  leg_cumu4->Draw();
  cline->Draw();
  ccomp4->Print("FigsAmpt/comp_ampt_cumulant4.png");
  ccomp4->Print("FigsAmpt/comp_ampt_cumulant4.pdf");
  delete ccomp4;
  delete empty_cumu4;
  delete empty_comp4;
  delete leg_cumu4;
  delete leg_comp4;



}
