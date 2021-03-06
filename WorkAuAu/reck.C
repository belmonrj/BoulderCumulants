int rebin = 2;

TH1D* get_cumuhist(TFile*);
TH1D* get_cumuhistC(TFile*);
TH1D* get_cumuhistS(TFile*);
TH1D* get_cumuhistN(TFile*);
TH1D* get_cumuhist(TProfile*,TProfile*);

void do_reck(int);


void reck()
{

  // do_reck(13617);
  // do_reck(13712);
  // do_reck(13720);
  // do_reck(13726);
  // do_reck(13737);
  do_reck(13798);
  do_reck(13799);

}


void do_reck(int flag)
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
  // --- 2nd harmonic
  ymin = -2e-5;
  ymax = 2e-6;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("c_{2}{4}"));
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
  histS->Draw("ex0p same");
  histN->SetLineColor(kRed);
  histN->SetMarkerColor(kRed);
  histN->SetMarkerStyle(kFullCircle);
  //histN->Draw("ex0p same");
  TH1D* histNS = (TH1D*)histN->Clone("histNS");
  histNS->Add(histS);
  histNS->Scale(0.5);
  histNS->SetLineColor(kGreen+2);
  histNS->SetMarkerColor(kGreen+2);
  histNS->SetMarkerStyle(kFullCircle);
 //histNS->Draw("ex0p same");
  TLatex latt;
  latt.SetNDC();
  latt.SetTextSize(0.05);
  latt.SetTextAlign(11);
  latt.DrawLatex(0.50, 0.25, "Au+Au #sqrt{s_{_{NN}}} = 200 GeV");
  //TLegend* leg = new TLegend(0.18,0.73,0.38,0.93);
  TLegend* leg = new TLegend(0.18,0.18,0.38,0.48);
  leg->SetFillStyle(0);
  //leg->AddEntry(histR,"Recursion","p");
  leg->AddEntry(histC,"N+S combined","p");
  //leg->AddEntry(histNS,"N+S averaged","p");
  //leg->AddEntry(histN,"North only","p");
  leg->AddEntry(histS,"South only","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  TLine* line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print(Form("STAR/reck_%d_c24.png",flag));
  c1->Print(Form("STAR/reck_%d_c24.pdf",flag));

  histNS->Divide(histC);
  histNS->SetMarkerColor(kBlack);
  histNS->SetLineColor(kBlack);
  histNS->Draw();
  histNS->SetMaximum(2.0);
  histNS->SetMinimum(0.0);
  histNS->GetYaxis()->SetTitle(Form("Ratio"));
  histNS->GetYaxis()->SetTitleOffset(1.25);
  histNS->GetXaxis()->SetTitle("Centrality (%)");
  histNS->GetXaxis()->SetRangeUser(xmin,xmax);
  line = new TLine(xmin,1,xmax,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print(Form("STAR/rareck_%d_c24.png",flag));
  c1->Print(Form("STAR/rareck_%d_c24.pdf",flag));

  delete c1;

}


TH1D* get_cumuhist(TFile* fin)
{
  // safety check for null pointer
  if ( fin == NULL ) return NULL;
  // --- get the tprofiles
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_recursion_0_2");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_recursion_0_0");
  return get_cumuhist(ctp1f_for,ctp1f_two);
}


TH1D* get_cumuhistC(TFile* fin)
{
  // safety check for null pointer
  if ( fin == NULL ) return NULL;
  // --- get the tprofiles
  // TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_c24");
  // TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_c22");
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c22");
  return get_cumuhist(ctp1f_for,ctp1f_two);
}


TH1D* get_cumuhistS(TFile* fin)
{
  // safety check for null pointer
  if ( fin == NULL ) return NULL;
  // --- get the tprofiles
  // TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_ac_fvtxs_tracks_c24");
  // TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_ac_fvtxs_tracks_c22");
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_os_fvtxs_tracks_c24");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_os_fvtxs_tracks_c22");
  return get_cumuhist(ctp1f_for,ctp1f_two);
}


TH1D* get_cumuhistN(TFile* fin)
{
  // safety check for null pointer
  if ( fin == NULL ) return NULL;
  // --- get the tprofiles
  // TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_ac_fvtxn_tracks_c24");
  // TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_ac_fvtxn_tracks_c22");
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_os_fvtxn_tracks_c24");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_os_fvtxn_tracks_c22");
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

