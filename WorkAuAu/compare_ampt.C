TH1D* squareroot(TH1D*);
void compare_4part();
void compare_sigma();

void compare_ampt()
{

  compare_4part();
  compare_sigma();

}

void compare_4part()
{

  // --------------------------------------------------------------------------------
  // --- get the histograms from the files

  gROOT->ProcessLine("gErrorIgnoreLevel = 2002;");
  TFile* fampt = TFile::Open("input/messy_combination_auau200.root");
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

  int rebin = 5;

  tp1f_for_ampt->Rebin(rebin);
  tp1f_two_ampt->Rebin(rebin);
  tp1f_gap_ampt->Rebin(rebin);

  rebin = 2;

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
  // int n = th1d_c24_ampt->GetNbinsX();
  // double* x = new double[n];
  // double* y = new double[n];
  // double* ex = new double[n];
  // double* ey = new double[n];
  // for ( int i = 0; i < n; ++i )
  //   {
  //     x[i] = th1d_c24_ampt->GetBinCenter(i+1);
  //     y[i] = th1d_c24_ampt->GetBinContent(i+1);
  //     ex[i] = 0;
  //     ey[i] = th1d_c24_ampt->GetBinError(i+1);
  //   }
  // TGraphErrors* tge_c24_ampt = new TGraphErrors(n,x,y,ex,ey);
  // --------------------------------------------------------------------------------
  // --- make some plots

  double xmin = 0.0;
  double xmax = 99.9;
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
  empty_comp4->GetYaxis()->SetTitleOffset(0.92);
  th1d_222_data->SetMarkerStyle(kOpenCircle);
  th1d_222_data->SetMarkerColor(kRed);
  th1d_222_data->SetLineColor(kBlack);
  th1d_222_data->GetXaxis()->SetRangeUser(4,xmax);
  th1d_222_data->Draw("same ex0p");
  th1d_for_data->SetMarkerStyle(kOpenSquare);
  th1d_for_data->SetMarkerColor(kBlue);
  th1d_for_data->SetLineColor(kBlack);
  th1d_for_data->GetXaxis()->SetRangeUser(4,xmax);
  th1d_for_data->Draw("same ex0p");
  TLine *cline = new TLine(xmin,0,xmax,0);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  TLegend* leg_comp4 = new TLegend(0.68,0.70,0.9,0.85);
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
  //th1d_c24_ampt->GetXaxis()->SetRangeUser(4,xmax);
  th1d_c24_ampt->GetXaxis()->SetRangeUser(5,xmax);
  th1d_c24_ampt->SetMarkerSize(0);
  th1d_c24_ampt->SetLineWidth(2);
  th1d_c24_ampt->SetLineColor(kGreen+2);
  th1d_c24_ampt->SetFillColorAlpha(kGreen+2, 0.4);
  TH1D* cloned = (TH1D*)th1d_c24_ampt->Clone("cloned");
  cloned->SetFillColorAlpha(kGreen+2,0.0);
  cloned->Draw("HIST L same");
  th1d_c24_ampt->Draw("LE3 same");
  // ---
  th1d_c24_data->GetXaxis()->SetRangeUser(4,xmax);
  th1d_c24_data->SetMarkerStyle(kOpenCircle);
  th1d_c24_data->SetLineColor(kBlack);
  th1d_c24_data->Draw("same ex0p");
  TLegend* leg_cumu4 = new TLegend(0.68,0.80,0.9,0.95);
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

void compare_sigma()
{

  TCanvas* c1 = new TCanvas("c1","");

  // --------------------------------------------------------------------------------
  // --- get the histograms from the files

  gROOT->ProcessLine("gErrorIgnoreLevel = 2002;");
  TFile* fampt = TFile::Open("input/messy_combination_auau200.root");
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

  // --- something weird going on with rebinning...
  int rebin = 10;

  tp1f_for_ampt->Rebin(rebin);
  tp1f_two_ampt->Rebin(rebin);
  tp1f_gap_ampt->Rebin(rebin);

  rebin = 10;

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

  TH1D* th1d_gap_ampt = tp1f_gap_ampt->ProjectionX("th1d_gap_ampt");
  TH1D* th1d_gap_data = tp1f_gap_data->ProjectionX("th1d_gap_data");

  // th1d_c24_ampt->GetXaxis()->SetRangeUser(4,600);
  // th1d_two_ampt->GetXaxis()->SetRangeUser(4,600);
  // th1d_for_ampt->GetXaxis()->SetRangeUser(4,600);
  // th1d_gap_ampt->GetXaxis()->SetRangeUser(4,600);

  // th1d_c24_data->GetXaxis()->SetRangeUser(4,600);
  // th1d_two_data->GetXaxis()->SetRangeUser(4,600);
  // th1d_for_data->GetXaxis()->SetRangeUser(4,600);
  // th1d_gap_data->GetXaxis()->SetRangeUser(4,600);

  TH1D* th1d_SVV_data = (TH1D*)th1d_c24->Clone("th1d_SVV_data");
  TH1D* th1d_SVG_data = (TH1D*)th1d_c24->Clone("th1d_SVG_data");

  int nbins = th1d_gap_data->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      // --- 2-particle
      double c22 = th1d_two_data->GetBinContent(i+1);
      double v22 = -9999;
      double ev22 = 0;
      double two = th1d_two_data->GetBinContent(i+1);
      double etwo = th1d_two_data->GetBinError(i+1);
      if ( c22 > 0 )
        {
          v22 = sqrt(c22); // v2{2} = c2{2}^{(1/2)}
          ev22 = (1.0/v22)*etwo; // correct formula
        }
      // th1d_v22_data->SetBinContent(i+1,v22);
      // th1d_v22_data->SetBinError(i+1,ev22);
      // --- 2-particle
      double c2G = th1d_gap_data->GetBinContent(i+1);
      double v2G = -9999;
      double ev2G = 0;
      double twog = th1d_gap_data->GetBinContent(i+1);
      double etwog = th1d_gap_data->GetBinError(i+1);
      if ( c2G > 0 )
        {
          v2G = sqrt(c2G); // v2{2} = c2{2}^{(1/2)}
          ev2G = (1.0/v2G)*etwog; // correct formula
        }
      // th1d_v2G_data->SetBinContent(i+1,v2G);
      // th1d_v2G_data->SetBinError(i+1,ev2G);
      // --- 4-particle
      double c24 = th1d_c24_data->GetBinContent(i+1);
      double v24 = -9999;
      double four = th1d_for_data->GetBinContent(i+1);
      double efour = th1d_for_data->GetBinError(i+1);
      double ev24 = 0;
      if ( c24 < 0 && four != 0 )
        {
          v24 = pow(-c24,(1.0/4.0)); // v2{4} = -c2{4}^{(1/4)}
          ev24 = (1.0/pow(-c24,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
        }
      // th1d_v24_data->SetBinContent(i+1,v24);
      // th1d_v24_data->SetBinError(i+1,ev24);
      // --- sigma_v/v
      double numerator1 = -9999;
      double denominat1 = -9999;
      double sigmavv1 = -9999;
      double esigmavv1 = 0;
      if ( v22 > 0 && v24 > 0 )
        {
          numerator1 = v22*v22 - v24*v24;
          denominat1 = v22*v22 + v24*v24;
          sigmavv1 = numerator1/denominat1;
          if ( sigmavv1 > 0 ) sigmavv1 = sqrt(sigmavv1); else sigmavv1 = -9999;
          esigmavv1 = sigmavv1*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) ); // quick and dirty guess, need to check
        }
      th1d_SVV_data->SetBinContent(i+1,sigmavv1);
      th1d_SVV_data->SetBinError(i+1,esigmavv1);
      // --- sigma_v/v
      double numerator2 = -9999;
      double denominat2 = -9999;
      double sigmavv2 = -9999;
      double esigmavv2 = 0;
      if ( v22 > 0 && v24 > 0 )
        {
          numerator2 = v2G*v2G - v24*v24;
          denominat2 = v2G*v2G + v24*v24;
          sigmavv2 = numerator2/denominat2;
          if ( sigmavv2 > 0 ) sigmavv2 = sqrt(sigmavv2); else sigmavv2 = -9999;
          esigmavv2 = sigmavv2*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) ); // quick and dirty guess, need to check
        }
      th1d_SVG_data->SetBinContent(i+1,sigmavv2);
      th1d_SVG_data->SetBinError(i+1,esigmavv2);
      // ---------------------------------------
      //cout << i << " " << v22 << " " << v24 << " " << sigmavv1 << endl;
    }

  TH1D* th1d_SVV_ampt = (TH1D*)th1d_c24->Clone("th1d_SVV_ampt");
  TH1D* th1d_SVG_ampt = (TH1D*)th1d_c24->Clone("th1d_SVG_ampt");

  int nbins = th1d_gap_ampt->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      // --- 2-particle
      double c22 = th1d_two_ampt->GetBinContent(i+1);
      double v22 = -9999;
      double ev22 = 0;
      double two = th1d_two_ampt->GetBinContent(i+1);
      double etwo = th1d_two_ampt->GetBinError(i+1);
      if ( c22 > 0 )
        {
          v22 = sqrt(c22); // v2{2} = c2{2}^{(1/2)}
          ev22 = (1.0/v22)*etwo; // correct formula
        }
      // th1d_v22_ampt->SetBinContent(i+1,v22);
      // th1d_v22_ampt->SetBinError(i+1,ev22);
      // --- 2-particle
      double c2G = th1d_gap_ampt->GetBinContent(i+1);
      double v2G = -9999;
      double ev2G = 0;
      double twog = th1d_gap_ampt->GetBinContent(i+1);
      double etwog = th1d_gap_ampt->GetBinError(i+1);
      if ( c2G > 0 )
        {
          v2G = sqrt(c2G); // v2{2} = c2{2}^{(1/2)}
          ev2G = (1.0/v2G)*etwog; // correct formula
        }
      // th1d_v2G_ampt->SetBinContent(i+1,v2G);
      // th1d_v2G_ampt->SetBinError(i+1,ev2G);
      // --- 4-particle
      double c24 = th1d_c24_ampt->GetBinContent(i+1);
      double v24 = -9999;
      double four = th1d_for_ampt->GetBinContent(i+1);
      double efour = th1d_for_ampt->GetBinError(i+1);
      double ev24 = 0;
      if ( c24 < 0 && four != 0 )
        {
          v24 = pow(-c24,(1.0/4.0)); // v2{4} = -c2{4}^{(1/4)}
          ev24 = (1.0/pow(-c24,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
        }
      // th1d_v24_ampt->SetBinContent(i+1,v24);
      // th1d_v24_ampt->SetBinError(i+1,ev24);
      // --- sigma_v/v
      double numerator1 = -9999;
      double denominat1 = -9999;
      double sigmavv1 = -9999;
      double esigmavv1 = 0;
      if ( v22 > 0 && v24 > 0 )
        {
          numerator1 = v22*v22 - v24*v24;
          denominat1 = v22*v22 + v24*v24;
          sigmavv1 = numerator1/denominat1;
          if ( sigmavv1 > 0 ) sigmavv1 = sqrt(sigmavv1); else sigmavv1 = -9999;
          esigmavv1 = sigmavv1*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) ); // quick and dirty guess, need to check
        }
      th1d_SVV_ampt->SetBinContent(i+1,sigmavv1);
      th1d_SVV_ampt->SetBinError(i+1,esigmavv1);
      // --- sigma_v/v
      double numerator2 = -9999;
      double denominat2 = -9999;
      double sigmavv2 = -9999;
      double esigmavv2 = 0;
      if ( v22 > 0 && v24 > 0 )
        {
          numerator2 = v2G*v2G - v24*v24;
          denominat2 = v2G*v2G + v24*v24;
          sigmavv2 = numerator2/denominat2;
          if ( sigmavv2 > 0 ) sigmavv2 = sqrt(sigmavv2); else sigmavv2 = -9999;
          esigmavv2 = sigmavv2*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) ); // quick and dirty guess, need to check
        }
      th1d_SVG_ampt->SetBinContent(i+1,sigmavv2);
      th1d_SVG_ampt->SetBinError(i+1,esigmavv2);
      // ---------------------------------------
      //cout << i << " " << v22 << " " << v24 << " " << sigmavv1 << endl;
    }



  double xmin = 0.0;
  double xmax = 99.9;
  double ymin = -1e-4;
  double ymax = 1e-4;

  xmin = 0;
  xmax = 600;
  ymin = 0.0;
  ymax = 1.2;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("#sigma_{v_{2}}/v_{2}");
  th1d_SVV_data->SetMarkerStyle(kOpenCircle);
  th1d_SVV_data->SetMarkerColor(kBlack);
  th1d_SVV_data->SetLineColor(kBlack);
  th1d_SVG_data->SetMarkerStyle(kOpenSquare);
  th1d_SVG_data->SetMarkerColor(kBlack);
  th1d_SVG_data->SetLineColor(kBlack);
  th1d_SVV_data->Draw("same ex0p");
  th1d_SVG_data->Draw("same ex0p");
  // ---------------------------------------------
  th1d_SVV_ampt->GetXaxis()->SetRangeUser(5,xmax);
  th1d_SVV_ampt->SetMarkerSize(0);
  th1d_SVV_ampt->SetLineWidth(2);
  th1d_SVV_ampt->SetLineColor(kGreen+2);
  th1d_SVV_ampt->SetFillColorAlpha(kGreen+2, 0.4);
  TH1D* cloned = (TH1D*)th1d_SVV_ampt->Clone("cloned");
  cloned->SetFillColorAlpha(kGreen+2,0.0);
  cloned->Draw("HIST L same");
  th1d_SVV_ampt->Draw("LE3 same");
  // ---------------------------------------------
  th1d_SVG_ampt->GetXaxis()->SetRangeUser(5,xmax);
  th1d_SVG_ampt->SetMarkerSize(0);
  th1d_SVG_ampt->SetLineWidth(2);
  th1d_SVG_ampt->SetLineColor(kGreen+2);
  th1d_SVG_ampt->SetFillColorAlpha(kGreen+2, 0.4);
  TH1D* clonet = (TH1D*)th1d_SVG_ampt->Clone("clonet");
  clonet->SetFillColorAlpha(kGreen+2,0.0);
  clonet->Draw("HIST L same");
  th1d_SVG_ampt->Draw("LE3 same");
  // ---------------------------------------------
  TLegend* leg = new TLegend(0.22,0.72,0.48,0.92);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_SVV_data,"Using v_{2}{2} no eta gap","p");
  leg->AddEntry(th1d_SVG_data,"Using v_{2}{2} with eta gap","p");
  leg->Draw();
  c1->Print("FigsAmpt/sigma_ampt_x01.png");
  c1->Print("FigsAmpt/sigma_ampt_x01.pdf");

  delete c1;

}



TH1D* squareroot(TH1D* h)
{
  TH1D* hr = (TH1D*)h->Clone(Form("%s_sqrt",h->GetName()));
  int n = hr->GetNbinsX();
  for ( int i = 0; i < n; ++i )
    {
      double content = hr->GetBinContent(i+1);
      double error = hr->GetBinError(i+1);
      double newcontent = -9999;
      double newerror = 0;
      if ( content > 0 )
        {
          newcontent = sqrt(content);
          newerror = (1.0/newcontent)*error;
        }
      hr->SetBinContent(i+1,newcontent);
      hr->SetBinError(i+1,newerror);
    }
  return hr;
}
