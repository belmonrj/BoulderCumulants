int rebin = 5;

TH1D* get_cumuhist(TFile*);
TH1D* get_cumuhistC(TFile*);
TH1D* get_cumuhistS(TFile*);
TH1D* get_cumuhistN(TFile*);
TH1D* get_cumuhist(TProfile*,TProfile*);

void do_jeck(int);


void jeck()
{

  // do_jeck(13617);
  // do_jeck(13712);
  // do_jeck(13720);
  // do_jeck(13726);
  // do_jeck(13737);
  // do_jeck(13798);
  // do_jeck(13841);
  do_jeck(13847); // nhit
  do_jeck(13872); // DCA
  do_jeck(13897); // zvtx
  do_jeck(13911); // chi2
  do_jeck(13926); // dubl
  do_jeck(13799); // base

}


void do_jeck(int flag)
{

  TFile* fileR = TFile::Open(Form("input/histos_%d.root",flag));
  //TFile* fileR = TFile::Open(Form("input/partial_%d.root",flag));
  //TFile* fileR = TFile::Open(Form("input/full_%d.root",flag));

  TH1D* histR = get_cumuhist(fileR); // recursion for reference
  if ( histR == NULL ) { cout << "RECURSION HISTOGRAM MISSING!!! " << flag << endl; return; }
  const int nbins = histR->GetNbinsX();
  cout << "histogram at address " << histR << " has " << nbins << " bins" << endl;

  TH1D* histC = get_cumuhistC(fileR); // combined
  if ( histC == NULL ) { cout << " HISTOGRAM MISSING!!! " << flag << endl; return; }
  TH1D* histS = get_cumuhistS(fileR); // combined
  if ( histS == NULL ) { cout << " HISTOGRAM MISSING!!! " << flag << endl; return; }
  TH1D* histN = get_cumuhistN(fileR); // combined
  if ( histN == NULL ) { cout << " HISTOGRAM MISSING!!! " << flag << endl; return; }





  //double standard[nbins];
  double norm_c3[nbins];
  double norm_ec3[nbins];
  double sysnorm_ec3[nbins];
  double hisysnorm_ec3[nbins];
  double losysnorm_ec3[nbins];
  //double scent[20]={2.5,7.5,12.5,17.5,22.5,27.5,32.5,37.5,42.5,47.5,52.5,57.5,62.5,67.5,72.5,77.5,82.5,87.5,92.5,97.5};
  double scent[20]={2.0,7.0,12.0,17.0,22.0,27.0,32.0,37.0,42.0,47.0,52.0,57.0,62.0,67.0,72.0,77.0,82.0,87.0,92.0,97.0};
  double cent[nbins];
  double sys = 0.5;
  double hisys = 0.4;
  double losys = 0.3;
  double standard[20]={
    3.64513e-08,
    6.44798e-08,
    8.97388e-08,
    1.22304e-07,
    1.76018e-07,
    1.93017e-07,
    2.46064e-07,
    1.93137e-07,
    2.00649e-07,
    5.17558e-07,
    2.90058e-07,
    1.28054e-06,
    3.39121e-06,
    2.16037e-06,
    -1.87409e-05,
    -6.14957e-05,
    -0.000221997,
    -0.000185939,
    -5.84767e-05,
    0};
  for ( int i = 0; i < nbins; ++i )
    {
      cent[i] = histN->GetBinCenter(i+1);
      norm_c3[i] = histN->GetBinContent(i+1);
      // if ( flag == 13799 )
      //   {
      //     cout << cent[i] << " " << norm_c3[i] << endl;
      //   }
      norm_ec3[i] = histN->GetBinError(i+1);
      sysnorm_ec3[i] = standard[i]*sys;
      // hisysnorm_ec3[i] = standard[i]+sysnorm_ec3[i];
      // losysnorm_ec3[i] = standard[i]-sysnorm_ec3[i];
      hisysnorm_ec3[i] = standard[i]*(1+hisys);
      losysnorm_ec3[i] = standard[i]*(1-losys);
    }

  TGraph* tge_std = new TGraph(11,scent,standard);
  tge_std->SetLineColor(kGray);
  tge_std->SetMarkerColor(kGray);
  tge_std->SetMarkerStyle(kOpenCircle);
  TGraph* tge_sys_hi = new TGraph(11,scent,hisysnorm_ec3);
  TGraph* tge_sys_lo = new TGraph(11,scent,losysnorm_ec3);
  tge_sys_hi->SetLineColor(kBlack);
  tge_sys_hi->SetLineWidth(2);
  tge_sys_hi->SetLineStyle(1);
  tge_sys_lo->SetLineColor(kBlack);
  tge_sys_lo->SetLineWidth(2);
  tge_sys_lo->SetLineStyle(1);



  TCanvas* c1 = new TCanvas("c1","");

  double xmin = 0;
  double xmax = 60;
  double ymin = -0.2;
  double ymax = 0.1;
  // --- normal
  ymin = -1e-7;
  ymax = 2e-7;
  // --- offset problem
  ymin = -2.5e-6;
  ymax = 5e-6;
  // --- "new" normal
  ymin = -1e-7;
  ymax = 5e-7;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("c_{3}{4}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  histR->SetLineColor(kBlack);
  histR->SetMarkerColor(kBlack);
  histR->SetMarkerStyle(kOpenCircle);
  histR->SetMarkerSize(1.8);
  //histR->Draw("ex0p same");
  histC->SetLineColor(kGray);
  histC->SetMarkerColor(kGray);
  histC->SetMarkerStyle(kFullCircle);
  histC->Draw("ex0p same");
  histS->SetLineColor(kBlue);
  histS->SetMarkerColor(kBlue);
  histS->SetMarkerStyle(kFullCircle);
  //histS->Draw("ex0p same");
  histN->SetLineColor(kRed);
  histN->SetMarkerColor(kRed);
  histN->SetMarkerStyle(kFullCircle);
  histN->Draw("ex0p same");
  TH1D* histNS = (TH1D*)histN->Clone("histNS");
  histNS->Add(histS);
  histNS->Scale(0.5);
  histNS->SetLineColor(kGreen+2);
  histNS->SetMarkerColor(kGreen+2);
  histNS->SetMarkerStyle(kFullCircle);
  //histNS->Draw("ex0p same");
  // TLatex latt;
  // latt.SetNDC();
  // latt.SetTextSize(0.05);
  // latt.SetTextAlign(11);
  // latt.DrawLatex(0.50, 0.25, "Au+Au #sqrt{s_{_{NN}}} = 200 GeV");
  TLegend* leg = new TLegend(0.18,0.73,0.38,0.93);
  leg->SetFillStyle(0);
  //leg->AddEntry(histR,"Recursion","p");
  leg->AddEntry(histC,"N+S combined","p");
  //leg->AddEntry(histNS,"N+S averaged","p");
  leg->AddEntry(histN,"North only","p");
  //leg->AddEntry(histS,"South only","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  // TLegend* leg = new TLegend(0.18,0.73,0.38,0.93);
  // leg->SetFillStyle(0);
  // leg->AddEntry(histR,"PHENIX 1<|#eta|<3","p");
  // leg->SetTextSize(0.05);
  // leg->Draw();
  TLine* line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print(Form("STAR/jeck_%d_c34.png",flag));
  c1->Print(Form("STAR/jeck_%d_c34.pdf",flag));
  tge_sys_hi->Draw("l");
  tge_sys_lo->Draw("l");
  tge_std->Draw("p");
  c1->Print(Form("STAR/heck_%d_c34.png",flag));
  c1->Print(Form("STAR/heck_%d_c34.pdf",flag));



  histC->GetXaxis()->SetRangeUser(0,53);
  histC->SetMarkerStyle(kOpenCircle);
  histC->SetMarkerColor(kBlack);
  histC->SetLineColor(kBlack);

  histN->GetXaxis()->SetRangeUser(0,45);
  histN->SetMarkerStyle(kFullCircle);
  histN->SetMarkerColor(kBlack);
  histN->SetLineColor(kBlack);


  const int nbins0 = histC->GetNbinsX();
  const int nbins1 = histN->GetNbinsX();
  float cent0[nbins0];
  float cent1[nbins1];
  float value0[nbins0];
  float value1[nbins1];
  float loerr0[nbins0];
  float loerr1[nbins1];
  float hierr0[nbins0];
  float hierr1[nbins1];
  // sys comb
  for ( int i = 0; i < nbins0; ++i )
    {
      cent0[i] = histC->GetBinCenter(i+1);
      value0[i] = histC->GetBinContent(i+1);
      loerr0[i] = value0[i]*0.6;
      hierr0[i] = value0[i]*0.3;
    }
  TGraphAsymmErrors* tgaesys_comb = new TGraphAsymmErrors(11,cent0,value0,0,0,loerr0,hierr0);
  tgaesys_comb->SetFillColorAlpha(kBlack,0.35);
  // sys nort
  for ( int i = 0; i < nbins1; ++i )
    {
      cent1[i] = histN->GetBinCenter(i+1);
      value1[i] = histN->GetBinContent(i+1);
      loerr1[i] = value1[i]*0.3;
      hierr1[i] = value1[i]*0.4;
    }
  TGraphAsymmErrors* tgaesys_nort = new TGraphAsymmErrors(9,cent1,value1,0,0,loerr1,hierr1);
  tgaesys_nort->SetFillColorAlpha(kBlack,0.35);


  // --- "new" normal
  ymin = -1e-7;
  ymax = 5e-7;
  if ( hdummy ) delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("c_{3}{4}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  TLatex* tex_phenix = new TLatex(0.2,0.778,"PHENIX");
  tex_phenix->SetTextSize(0.05);
  tex_phenix->SetNDC();
  tex_phenix->Draw();
  TLatex* tex_tracks = new TLatex(0.2,0.83,"h^{#pm} 1<|#eta|<3");
  tex_tracks->SetTextSize(0.05);
  tex_tracks->SetNDC();
  tex_tracks->Draw();
  TLatex* tex_system = new TLatex(0.2,0.882,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  tex_system->SetTextSize(0.05);
  tex_system->SetNDC();
  tex_system->Draw();
  histC->Draw("ex0p same");
  histN->Draw("ex0p same");
  TLegend* leg34 = new TLegend(0.60,0.76,0.92,0.92);
  leg34->SetTextSize(0.05);
  leg34->SetFillStyle(0);
  leg34->AddEntry(histC,"Combined arms","p");
  leg34->AddEntry(histN,"Single arm","p");
  leg34->Draw();
  line->Draw();
  tgaesys_comb->Draw("3");
  tgaesys_nort->Draw("3");
  c1->Print(Form("STAR/neck_%d_c34.png",flag));
  c1->Print(Form("STAR/neck_%d_c34.pdf",flag));
  TLatex latt;
  latt.SetNDC();
  latt.SetTextSize(0.05);
  latt.SetTextAlign(11);
  latt.DrawLatex(0.2, 0.2, "(b)");
  c1->Print(Form("STAR/nneck_%d_c34.png",flag));
  c1->Print(Form("STAR/nneck_%d_c34.pdf",flag));
  if ( flag == 13799 )
  {
  c1->Print(Form("STAR/cent_c34arm.png"));
  c1->Print(Form("STAR/cent_c34arm.pdf"));
  }


  // --- now do the ratio

  histN->Divide(histC);
  histN->SetMarkerColor(kBlack);
  histN->SetLineColor(kBlack);
  histN->Draw();
  histN->SetMaximum(10.0);
  histN->SetMinimum(0.0);
  histN->GetYaxis()->SetTitle(Form("Ratio"));
  histN->GetYaxis()->SetTitleOffset(1.25);
  histN->GetXaxis()->SetTitle("Centrality (%)");
  histN->GetXaxis()->SetRangeUser(xmin,xmax);
  line = new TLine(xmin,1,xmax,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print(Form("STAR/rajeck_%d_c34.png",flag));
  c1->Print(Form("STAR/rajeck_%d_c34.pdf",flag));



  delete c1;

}


TH1D* get_cumuhist(TFile* fin)
{
  // safety check for null pointer
  if ( fin == NULL ) return NULL;
  // --- get the tprofiles
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_recursion_0_3");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_recursion_0_1");
  return get_cumuhist(ctp1f_for,ctp1f_two);
}


TH1D* get_cumuhistC(TFile* fin)
{
  // safety check for null pointer
  if ( fin == NULL ) return NULL;
  // --- get the tprofiles
  // TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_c34");
  // TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_c32");
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c34");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c32");
  return get_cumuhist(ctp1f_for,ctp1f_two);
}


TH1D* get_cumuhistS(TFile* fin)
{
  // safety check for null pointer
  if ( fin == NULL ) return NULL;
  // --- get the tprofiles
  // TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_ac_fvtxs_tracks_c34");
  // TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_ac_fvtxs_tracks_c32");
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_os_fvtxs_tracks_c34");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_os_fvtxs_tracks_c32");
  return get_cumuhist(ctp1f_for,ctp1f_two);
}


TH1D* get_cumuhistN(TFile* fin)
{
  // safety check for null pointer
  if ( fin == NULL ) return NULL;
  // --- get the tprofiles
  // TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_ac_fvtxn_tracks_c34");
  // TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_ac_fvtxn_tracks_c32");
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_os_fvtxn_tracks_c34");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_os_fvtxn_tracks_c32");
  return get_cumuhist(ctp1f_for,ctp1f_two);
}


TH1D* get_cumuhist(TProfile* ctp1f_for, TProfile* ctp1f_two)
{
  // --- safety check for null pointers
  if ( ctp1f_for == NULL ) return NULL;
  if ( ctp1f_two == NULL ) return NULL;
  // --- rebin with the global variable
  ctp1f_for->Rebin(rebin);
  ctp1f_two->Rebin(rebin);
  // --- random number helper to prevent memory collisions with ROOT named objects...
  double rand = gRandom->Rndm();
  int helper = rand*10000;
  // --- convert to th1ds (to do math operations)
  TH1D* th1d_for = ctp1f_for->ProjectionX(Form("th1d_for_%d",helper)); // <4>
  TH1D* th1d_two = ctp1f_two->ProjectionX(Form("th1d_two_%d",helper)); // <2>
  // --- calc 222
  TH1D* th1d_222 = (TH1D*)th1d_two->Clone(Form("th1d_222_%d",helper)); // 2<2>^2       (for the 4p)
  th1d_222->Multiply(th1d_two);
  th1d_222->Scale(2);
  // --- calc the cumulant
  TH1D* th1d_cu4 = (TH1D*)th1d_for->Clone(Form("th1d_cu4_%d",helper)); // c{4} = <4> - 2<2>^2
  th1d_cu4->Add(th1d_222,-1);
  // --- return the cumulant
  return th1d_cu4;
}
