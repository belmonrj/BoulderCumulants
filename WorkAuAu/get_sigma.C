TH1D* get_sigma_histo(TProfile*, TProfile*, TProfile*, int, const char*, bool);
TH1D* get_sigma_histo(TFile*, int, const char*, bool);
TH1D* get_sigma_histo(TFile*, int, const char*);


void get_sigma()
{

  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");

  int rebin = 1;

  const char* handle = "cent";

  TH1D* hreturn = get_sigma_histo(fin,rebin,handle,true);

  cout << "return histo is " << hreturn << endl;

  cout << "All done! Have a nice day!" << endl;

  ofstream fout("Figure8.dat");
  for ( int i = 0; i < hreturn->GetNbinsX(); ++i )
    {
      fout
        << hreturn->GetBinCenter(i+1)-0.5 << " "
        << hreturn->GetBinContent(i+1) << " "
        << hreturn->GetBinError(i+1) << " "
        << 0.02*hreturn->GetBinContent(i+1) << "\n";
    }

}


TH1D* get_sigma_histo(TFile* fin, int rebin, const char* handle)
{
  return get_sigma_histo(fin,rebin,handle,false);
}


TH1D* get_sigma_histo(TFile* fin, int rebin, const char* handle, bool doplot)
{

  TProfile* tp1f_gap = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c22");
  TProfile* tp1f_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c22");

  TH1D* hreturn = get_sigma_histo(tp1f_gap,tp1f_for,tp1f_two,rebin,handle,doplot);

  cout << "return histo is " << hreturn << endl;

  return hreturn;

}


TH1D* get_sigma_histo(TProfile* tp1f_gap, TProfile* tp1f_for, TProfile* tp1f_two, int rebin, const char* handle, bool doplot)
{

  if ( !tp1f_gap || !tp1f_two || !tp1f_for )
    {
      cout << "get_sigma_histo: one or more empty histograms" << endl;
      cout << "tp1f_gap: " << tp1f_gap << endl;
      cout << "tp1f_two: " << tp1f_two << endl;
      cout << "tp1f_for: " << tp1f_for << endl;
      return NULL;
    }

  TCanvas* c1 = new TCanvas("c1","");

  bool iscent = false;
  bool isntrk = false;
  if ( strcmp(handle,"cent") == 0 ) iscent = true;
  if ( strcmp(handle,"strk") == 0 ) isntrk = true;
  bool isamptntrk = false;
  if ( strcmp(handle,"amptstrk") == 0 ) { isamptntrk = true; isntrk = true; }
  bool islowzoom = false;
  if ( strcmp(handle,"lowstrkzoom") == 0 ) { islowzoom = true; isntrk = true; }



  tp1f_gap->Rebin(rebin);
  tp1f_for->Rebin(rebin);
  tp1f_two->Rebin(rebin);

  TH1D* th1d_gap = tp1f_gap->ProjectionX(Form("th1d_gap_%s",handle)); // <6>
  TH1D* th1d_for = tp1f_for->ProjectionX(Form("th1d_for_%s",handle)); // <4>
  TH1D* th1d_two = tp1f_two->ProjectionX(Form("th1d_two_%s",handle)); // <2>
  TH1D* th1d_222 = (TH1D*)th1d_two->Clone(Form("th1d_222_%s",handle)); // 2<2>^2
  th1d_222->Multiply(th1d_two);
  th1d_222->Scale(2);
  TH1D* th1d_c24 = (TH1D*)th1d_for->Clone("th1d_c24"); // c2{4} = <4> - 2<2>^2
  th1d_c24->Add(th1d_222,-1);
  TH1D* th1d_c22 = (TH1D*)th1d_two->Clone("th1d_c22"); // c2{2} = <2>
  TH1D* th1d_c2G = (TH1D*)th1d_gap->Clone("th1d_gap"); // c2{2} = <2>
  TH1D* th1d_v24 = (TH1D*)th1d_c24->Clone("th1d_v24");
  TH1D* th1d_v22 = (TH1D*)th1d_c22->Clone("th1d_v22");
  TH1D* th1d_v2G = (TH1D*)th1d_c2G->Clone("th1d_v2G");
  TH1D* th1d_SVV = (TH1D*)th1d_c24->Clone("th1d_SVV");
  TH1D* th1d_SVG = (TH1D*)th1d_c24->Clone("th1d_SVG");
  TH1D* th1d_SV4 = (TH1D*)th1d_c24->Clone("th1d_SV4");
  TH1D* th1d_mean = (TH1D*)th1d_c24->Clone("th1d_mean");
  TH1D* th1d_sigma = (TH1D*)th1d_c24->Clone("th1d_sigma");

  int nbins = th1d_gap->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      // --- 2-particle
      double c22 = th1d_c22->GetBinContent(i+1);
      double v22 = -9999;
      double ev22 = 0;
      double two = th1d_two->GetBinContent(i+1);
      double etwo = th1d_two->GetBinError(i+1);
      if ( c22 > 0 )
        {
          v22 = sqrt(c22); // v2{2} = c2{2}^{(1/2)}
          ev22 = (1.0/v22)*etwo; // correct formula
        }
      th1d_v22->SetBinContent(i+1,v22);
      th1d_v22->SetBinError(i+1,ev22);
      // --- 2-particle
      double c2G = th1d_c2G->GetBinContent(i+1);
      double v2G = -9999;
      double ev2G = 0;
      double twog = th1d_two->GetBinContent(i+1);
      double etwog = th1d_two->GetBinError(i+1);
      if ( c2G > 0 )
        {
          v2G = sqrt(c2G); // v2{2} = c2{2}^{(1/2)}
          ev2G = (1.0/v2G)*etwog; // correct formula
        }
      th1d_v2G->SetBinContent(i+1,v2G);
      th1d_v2G->SetBinError(i+1,ev2G);
      // --- 4-particle
      double c24 = th1d_c24->GetBinContent(i+1);
      double v24 = -9999;
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
          // -----------------------
          //cout << sigmavv1 << endl;
          if ( sigmavv1 > 0 ) sigmavv1 = sqrt(sigmavv1); else sigmavv1 = -9999;
          //cout << sigmavv1 << endl;
          // -----------------------
          esigmavv1 = sigmavv1*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) ); // quick and dirty guess, need to check
        }
      th1d_SVV->SetBinContent(i+1,sigmavv1);
      th1d_SVV->SetBinError(i+1,esigmavv1);
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
          // -----------------------
          //cout << sigmavv2 << endl;
          if ( sigmavv2 > 0 ) sigmavv2 = sqrt(sigmavv2); else sigmavv2 = -9999;
          //cout << sigmavv2 << endl;
          // -----------------------
          // need to check, some problem for very central
          esigmavv2 = sigmavv2*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) );
        }
      if ( numerator2 > 0 && denominat2 > 0 )
        {
          double mean = sqrt(denominat2/2);
          double sigma = sqrt(numerator2/2);
          // --- need to check these, some problem for very central
          double emean = mean*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) );
          double esigma = sigma*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) );
          // emean = 0;
          // esigma = 0;
          th1d_mean->SetBinContent(i+1,mean);
          th1d_sigma->SetBinContent(i+1,sigma);
          th1d_mean->SetBinError(i+1,emean);
          th1d_sigma->SetBinError(i+1,esigma);
        }
      else
        {
          th1d_mean->SetBinContent(i+1,-9999);
          th1d_sigma->SetBinContent(i+1,-9999);
          th1d_mean->SetBinError(i+1,0);
          th1d_sigma->SetBinError(i+1,0);
        }
      cout << i << " " << th1d_sigma->GetBinContent(i+1) << endl;
      th1d_SVG->SetBinContent(i+1,sigmavv2);
      th1d_SVG->SetBinError(i+1,esigmavv2);
      // --- sigma_v/v this turns out to be algrebraically identical to the above...
      double numerator4 = -9999;
      double denominat4 = -9999;
      double sigmavv4 = -9999;
      double esigmavv4 = 0;
      if ( c22 > 0 && c24 < 0 )
        {
          numerator4 = c22*c22 + c24;
          denominat4 = v22*v22 + v24*v24;
          denominat4 *= denominat4;
          sigmavv4 = numerator4/denominat4;
          // -----------------------
          //cout << sigmavv4 << endl;
          if ( sigmavv4 > 0 ) sigmavv4 = sqrt(sigmavv4); else sigmavv4 = -9999;
          //cout << sigmavv4 << endl;
          // -----------------------
          esigmavv4 = sigmavv4*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) ); // quick and dirty guess, need to check
        }
      th1d_SV4->SetBinContent(i+1,sigmavv4);
      th1d_SV4->SetBinError(i+1,esigmavv4);
    }

  // ---
  TFile* fglauber = TFile::Open("input/fout_auau200gev_mcglauber_e2fluc.root");
  TGraph* tg_sig1 = (TGraph*)fglauber->Get("sigmae2overe2"); // direct calculation (need to double check with Jamie)
  TGraph* tg_sig2 = (TGraph*)fglauber->Get("fulle2fluc"); // estimate with cumulants (need to double check with Jamie)
  tg_sig1->SetLineColor(kBlue);
  tg_sig2->SetLineColor(kBlue);
  // tg_sig1->SetLineWidth(2);
  // tg_sig2->SetLineWidth(2);
  tg_sig1->SetLineWidth(3);
  tg_sig2->SetLineWidth(3);
  tg_sig1->SetLineStyle(2);
  tg_sig2->SetLineStyle(1);
  // ---

  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = 0.0;
  double ymax = 1.2;
  if ( iscent ) xmax = 100.0;
  if ( isntrk && !islowzoom ) xmax = 650.0;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("#sigma_{v_{2}}/#LTv_{2}#GT");
  if ( iscent )
  {
  th1d_SVV->GetXaxis()->SetRangeUser(0,70);
  th1d_SVG->GetXaxis()->SetRangeUser(0,70);
  th1d_SV4->GetXaxis()->SetRangeUser(0,70);
  }
  th1d_SVV->SetMarkerStyle(kOpenCircle);
  th1d_SVV->SetMarkerColor(kBlack);
  th1d_SVV->SetLineColor(kBlack);
  th1d_SVG->SetMarkerStyle(kOpenSquare);
  th1d_SVG->SetMarkerColor(kBlack);
  th1d_SVG->SetLineColor(kBlack);
  th1d_SV4->SetMarkerStyle(kOpenCross);
  th1d_SV4->SetMarkerColor(kGreen+2);
  th1d_SV4->SetLineColor(kGreen+2);
  th1d_SVV->Draw("same ex0p");
  th1d_SVG->Draw("same ex0p");
  //th1d_SV4->Draw("same ex0p");
  TLegend* leg = new TLegend(0.22,0.72,0.48,0.92);
  leg->SetHeader("Run14AuAu200");
  leg->AddEntry(th1d_SVV,"Using v_{2}{2} no eta gap","p");
  leg->AddEntry(th1d_SVG,"Using v_{2}{2} with eta gap","p");
  leg->Draw();
  // c1->Print(Form("FigsSigma/sigma_%s_x01.png",handle));
  // c1->Print(Form("FigsSigma/sigma_%s_x01.pdf",handle));
  if ( iscent )
  {
  tg_sig1->Draw("l");
  tg_sig2->Draw("l");
  leg->AddEntry(tg_sig2,"MC Glauber, cumulant based calc","l");
  leg->AddEntry(tg_sig1,"MC Glauber, direct calc","l");
  leg->Draw();
  // c1->Print(Form("FigsSigma/sigma_%s_x02.png",handle));
  // c1->Print(Form("FigsSigma/sigma_%s_x02.pdf",handle));
  }

  // ---

  if ( iscent )
  {
  empty->Draw();
  th1d_SVG->GetXaxis()->SetRangeUser(7,65);
  th1d_SVG->Draw("same ex0p");
  double Rmarg = 0.08;
  TLatex latt;
  latt.SetNDC();
  //latt.SetTextFont(62);
  latt.SetTextSize(0.05);
  latt.SetTextAlign(11);
  latt.DrawLatex(0.30 - Rmarg, 0.87, "PHENIX");
  latt.DrawLatex(0.56 - Rmarg, 0.87, "Au+Au #sqrt{s_{_{NN}}} = 200 GeV");
  latt.DrawLatex(0.56 - Rmarg, 0.80, "h^{#pm} 1<|#eta|<3");
  latt.DrawLatex(0.30 - Rmarg, 0.22, "Sys. Uncert. 2%");
  delete leg;
  leg = new TLegend(0.22,0.71,0.48,0.78);
  leg->AddEntry(th1d_SVG,"Data","p");
  leg->Draw();
  if ( doplot) c1->Print(Form("FigsSigma/sigma_%s_x03.png",handle));
  if ( doplot) c1->Print(Form("FigsSigma/sigma_%s_x03.pdf",handle));
  tg_sig1->Draw("l");
  tg_sig2->Draw("l");
  delete leg;
  leg = new TLegend(0.22,0.58,0.48,0.78);
  leg->AddEntry(tg_sig2,"MC Glauber, cumulant based estimate","l");
  leg->AddEntry(tg_sig1,"MC Glauber, direct calculation","l");
  leg->AddEntry(th1d_SVG,"Data","p");
  leg->Draw();
  if ( doplot) c1->Print(Form("FigsSigma/sigma_%s_x04.png",handle));
  if ( doplot) c1->Print(Form("FigsSigma/sigma_%s_x04.pdf",handle));
  ifstream fampt("input/temp_ampt.dat");
  double cent[16], ntrk[16], y[16], ey[16];
  for ( int i = 0; i < 16; ++i )
    {
      fampt >> cent[i] >> ntrk[i] >> y[i] >> ey[i];
      //cout << cent[i] << " " << ntrk[i] << " " << y[i] << " " << ey[i] << endl;
    }
  TGraphErrors* tge_amptcent = new TGraphErrors(16,cent,y,0,ey);
  tge_amptcent->SetLineColor(kGreen+2);
  tge_amptcent->SetLineWidth(3);
  tge_amptcent->SetLineStyle(1);
  tge_amptcent->SetFillColorAlpha(kGreen+2,0.35);
  tge_amptcent->Draw("L3");
  delete leg;
  leg = new TLegend(0.22,0.515,0.48,0.78);
  leg->AddEntry(tg_sig2,"MC Glauber, cumulant based estimate","l");
  leg->AddEntry(tg_sig1,"MC Glauber, direct calculation","l");
  leg->AddEntry(tge_amptcent,"AMPT","l");
  leg->AddEntry(th1d_SVG,"Data","p");
  leg->Draw();
  if ( doplot) c1->Print(Form("FigsSigma/sigma_%s_x05.png",handle));
  if ( doplot) c1->Print(Form("FigsSigma/sigma_%s_x05.pdf",handle));
  } // --- matches if ( iscent )


  // TH1D* hmean5 = (TH1D*)th1d_mean->Clone("hmean5");
  // TH1D* hsigma5 = (TH1D*)th1d_sigma->Clone("hsigma5");
  // TH1D* hratio5 = (TH1D*)th1d_SVG->Clone("hratio5");
  // hmean5->Scale(0.2);
  // hsigma5->Scale(0.2);
  // hratio5->Scale(0.2);
  // TH1D* hmean10 = (TH1D*)th1d_mean->Clone("hmean10");
  // TH1D* hsigma10 = (TH1D*)th1d_sigma->Clone("hsigma10");
  // TH1D* hratio10 = (TH1D*)th1d_SVG->Clone("hratio10");
  // hmean10->Scale(0.1);
  // hsigma10->Scale(0.1);
  // hratio10->Scale(0.1);
  float cent[6] = {2.5,7.5,15,25,35,45};
  float sbin[6] = {  5,  5,10,10,10,10};
  float mean[6] = {0,0,0,0,0,0};
  float emean[6] = {0,0,0,0,0,0};
  float sigma[6] = {0,0,0,0,0,0};
  float esigma[6] = {0,0,0,0,0,0};
  float ratio[6] = {0,0,0,0,0,0};
  float eratio[6] = {0,0,0,0,0,0};
  for ( int i = 0; i < 5; ++i )
    {
      // --- mean
      mean[0] += th1d_mean->GetBinContent(i+2);
      emean[0] += pow(th1d_mean->GetBinError(i+2),2);
      mean[1] += th1d_mean->GetBinContent(i+7);
      emean[1] += pow(th1d_mean->GetBinError(i+7),2);
      // --- sigma
      sigma[0] += th1d_sigma->GetBinContent(i+2);
      esigma[0] += pow(th1d_sigma->GetBinError(i+2),2);
      sigma[1] += th1d_sigma->GetBinContent(i+7);
      esigma[1] += pow(th1d_sigma->GetBinError(i+7),2);
      // --- ratio
      ratio[0] += th1d_SVG->GetBinContent(i+2);
      eratio[0] += pow(th1d_SVG->GetBinError(i+2),2);
      ratio[1] += th1d_SVG->GetBinContent(i+7);
      eratio[1] += pow(th1d_SVG->GetBinError(i+7),2);
      // ---
      //cout << sigma[1] << endl;
    }
  for ( int i = 0; i < 10; ++i )
    {
      // --- mean
      mean[2] += th1d_mean->GetBinContent(i+12);
      emean[2] += pow(th1d_mean->GetBinError(i+12),2);
      mean[3] += th1d_mean->GetBinContent(i+22);
      emean[3] += pow(th1d_mean->GetBinError(i+22),2);
      mean[4] += th1d_mean->GetBinContent(i+32);
      emean[4] += pow(th1d_mean->GetBinError(i+32),2);
      mean[5] += th1d_mean->GetBinContent(i+42);
      emean[5] += pow(th1d_mean->GetBinError(i+42),2);
      // --- sigma
      sigma[2] += th1d_sigma->GetBinContent(i+12);
      esigma[2] += pow(th1d_sigma->GetBinError(i+12),2);
      sigma[3] += th1d_sigma->GetBinContent(i+22);
      esigma[3] += pow(th1d_sigma->GetBinError(i+22),2);
      sigma[4] += th1d_sigma->GetBinContent(i+32);
      esigma[4] += pow(th1d_sigma->GetBinError(i+32),2);
      sigma[5] += th1d_sigma->GetBinContent(i+42);
      esigma[5] += pow(th1d_sigma->GetBinError(i+42),2);
      // --- ratio
      ratio[2] += th1d_SVG->GetBinContent(i+12);
      eratio[2] += pow(th1d_SVG->GetBinError(i+12),2);
      ratio[3] += th1d_SVG->GetBinContent(i+22);
      eratio[3] += pow(th1d_SVG->GetBinError(i+22),2);
      ratio[4] += th1d_SVG->GetBinContent(i+32);
      eratio[4] += pow(th1d_SVG->GetBinError(i+32),2);
      ratio[5] += th1d_SVG->GetBinContent(i+42);
      eratio[5] += pow(th1d_SVG->GetBinError(i+42),2);
      cout << sigma[2] << endl;
    }
  for ( int i = 0; i < 6; ++i )
    {
      // --- mean
      mean[i] /= sbin[i];
      emean[i] = sqrt(emean[i]);
      emean[i] /= sbin[i];
      // --- sigma
      sigma[i] /= sbin[i];
      esigma[i] = sqrt(esigma[i]);
      esigma[i] /= sbin[i];
      // --- ratio
      ratio[i] /= sbin[i];
      eratio[i] = sqrt(eratio[i]);
      eratio[i] /= sbin[i];
      cout << cent[2] << " " << sigma[2] << endl;
    }
  emean[1] = 0;
  esigma[1] = 0;
  eratio[1] = 0;
  TGraphErrors* tge_mean = new TGraphErrors(6,cent,mean,0,emean);
  TGraphErrors* tge_sigma = new TGraphErrors(6,cent,sigma,0,esigma);
  TGraphErrors* tge_ratio = new TGraphErrors(6,cent,ratio,0,eratio);
  tge_mean->SetMarkerStyle(kFullCircle);
  tge_mean->Draw("ap");
  tge_mean->SetMinimum(0.0);
  tge_mean->SetMaximum(0.06);
  if ( doplot) c1->Print(Form("FigsSigma/xx_r_mean.png"));
  if ( doplot) c1->Print(Form("FigsSigma/xx_r_mean.pdf"));
  tge_sigma->SetMarkerStyle(kFullCircle);
  tge_sigma->Draw("ap");
  tge_sigma->SetMinimum(0.0);
  tge_sigma->SetMaximum(0.02);
  if ( doplot) c1->Print(Form("FigsSigma/xx_r_sigma.png"));
  if ( doplot) c1->Print(Form("FigsSigma/xx_r_sigma.pdf"));
  tge_ratio->SetMarkerStyle(kFullCircle);
  tge_ratio->Draw("ap");
  tge_ratio->SetMinimum(0.0);
  tge_ratio->SetMaximum(1.0);
  if ( doplot) c1->Print(Form("FigsSigma/xx_r_ratio.png"));
  if ( doplot) c1->Print(Form("FigsSigma/xx_r_ratio.pdf"));

  th1d_mean->SetMarkerStyle(kFullCircle);
  th1d_mean->Draw("ex0p");
  th1d_mean->SetMinimum(0.0);
  th1d_mean->SetMaximum(0.06);
  if ( doplot) c1->Print(Form("FigsSigma/yy_r_mean.png"));
  if ( doplot) c1->Print(Form("FigsSigma/yy_r_mean.pdf"));
  th1d_sigma->SetMarkerStyle(kFullCircle);
  th1d_sigma->Draw("ex0p");
  th1d_sigma->SetMinimum(0.0);
  th1d_sigma->SetMaximum(0.02);
  if ( doplot) c1->Print(Form("FigsSigma/yy_r_sigma.png"));
  if ( doplot) c1->Print(Form("FigsSigma/yy_r_sigma.pdf"));
  th1d_SVG->SetMarkerStyle(kFullCircle);
  th1d_SVG->Draw("ex0p");
  th1d_SVG->SetMinimum(0.0);
  th1d_SVG->SetMaximum(1.0);
  if ( doplot) c1->Print(Form("FigsSigma/yy_r_ratio.png"));
  if ( doplot) c1->Print(Form("FigsSigma/yy_r_ratio.pdf"));

  if ( doplot )
    {
      TFile* fout = TFile::Open("sigma_for_jamie.root","recreate");
      fout->cd();
      th1d_mean->Write();
      th1d_sigma->Write();
      th1d_SVG->SetName("th1d_sigmaovermean");
      th1d_SVG->Write();
      tge_mean->SetName("tge_mean");
      tge_mean->Write();
      tge_sigma->SetName("tge_sigma");
      tge_sigma->Write();
      tge_ratio->SetName("tge_sigmaovermean");
      tge_ratio->Write();
      fout->Write();
      fout->Close();
      delete fout;
    }

  delete c1;

  TH1D* hreturn = th1d_SVV;

  return hreturn;

}

