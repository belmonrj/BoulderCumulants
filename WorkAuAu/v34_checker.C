#include "systematics_helper.C"

int rebin = 5;

TH1D* get_cumuhist(TFile*);
TH1D* get_histv324(TFile*);

void do_check(int);

void try_sys();
void try_sys_files(TFile*, TFile*, const char*);

void v34_checker()
{

  do_check(12097); // old baseline
  do_check(12194); // chi2
  do_check(12195); // zvtx
  do_check(12289); // nhit
  do_check(12290); // dcar
  do_check(12420); // another baseline
  do_check(12432); // qrbr
  do_check(12555); // code
  do_check(12579); // another baseline
  do_check(12581); // noqr
  do_check(12587); // nfqr
  do_check(12634); // version used for paper
  do_check(12650); // newc

  try_sys();

}

void do_check(int flag)
{

  //TFile* fileR = TFile::Open("RunByRun/combin.root"); // reference
  TFile* fileR = TFile::Open(Form("input/histos_%d.root",flag)); // reference

  TH1D* histR = get_cumuhist(fileR); // reference
  TH1D* histS = get_histv324(fileR); // reference
  if ( histR == NULL ) { cout << "RECURSION HISTOGRAM MISSING!!! " << flag << endl; return; }
  if ( histS == NULL ) cout << "SCALAR PRODUCT HISTOGRAM MISSING!!! " << flag << endl;

  const int nbins = histR->GetNbinsX();

  double norm_c3[nbins];
  double swap_c3[nbins];
  double norm_ec3[nbins];
  double swap_ec3[nbins];
  double norm_v3[nbins];
  double swap_v3[nbins];
  double norm_ev3[nbins];
  double swap_ev3[nbins];
  double cent[nbins];
  double norm_c2[nbins];
  double swap_c2[nbins];
  double norm_ec2[nbins];
  double swap_ec2[nbins];
  double ratio[nbins];
  double eratio[nbins];
  for ( int i = 0; i < nbins; ++i )
    {
      cent[i] = histR->GetBinCenter(i+1);
      // --- normal v3
      norm_c3[i] = histR->GetBinContent(i+1);
      norm_ec3[i] = histR->GetBinError(i+1);
      norm_v3[i] = pow(-norm_c3[i],0.25);
      norm_ev3[i] = (1/(4*pow(-norm_c3[i],0.75)))*norm_ec3[i];
      if ( norm_v3[i] != norm_v3[i] ) norm_v3[i] = -999;
      if ( norm_ev3[i] != norm_ev3[i] ) norm_v3[i] = 998;
      // --- swapped v3
      swap_c3[i] = -1*histR->GetBinContent(i+1);
      swap_ec3[i] = histR->GetBinError(i+1);
      swap_v3[i] = pow(-swap_c3[i],0.25);
      swap_ev3[i] = (1/(4*pow(-swap_c3[i],0.75)))*swap_ec3[i];
      if ( swap_v3[i] != swap_v3[i] ) swap_v3[i] = -999;
      if ( swap_ev3[i] != swap_ev3[i] ) swap_v3[i] = 998;
      // --- v3{2}^4
      if ( histS )
        {
          swap_c2[i] = histS->GetBinContent(i+1);
          swap_ec2[i] = histS->GetBinError(i+1);
        }
      ratio[i] = 2 - swap_c3[i]/swap_c2[i];
      // --- way too big
      eratio[i] = ratio[i]*sqrt( pow( (swap_ec3[i]/swap_c3[i]), 2.0 ) + pow( (swap_ec2[i]/swap_c2[i]), 2.0 ) );
      eratio[i] = (swap_ec2[i]/swap_c2[i]) * 50;
      swap_c3[i] *= 1e6;
      swap_ec3[i] *= 1e6;
      swap_c2[i] *= 1e6;
      swap_ec2[i] *= 1e6;
      // --- ratio
      // cout << cent[i] << " "
      //      << swap_c3[i] << " "
      //      << swap_c2[i] << " "
      //      << ratio[i] << " +- "
      //      << eratio[i]
      //      << endl;
      // cout << cent[i] << " "
      //      << swap_ec3[i]/swap_c3[i] << " "
      //      << swap_ec2[i]/swap_c2[i] << " "
      //      << eratio[i]/ratio[i] << " +- "
      //      << endl;
    }


  // Phys. Rev. C 88, 014904 (2013)
  // https://drupal.star.bnl.gov/STAR/files/starpublications/199/data.html
  // 106*v34{4}	2 - (v34{4}/v34{2})
  // cent (%)	STAR	        error	ALICE	error	STAR	error	ALICE	error
  // 2.5	-0.00156	0.004	0.0123	0.0047	2.04	0.096	1.95	0.021
  // 7.5	0.00549	        0.0058	0.025	0.0092	1.92	0.082	1.94	0.022
  // 15	        0.000938	0.0069	0.0581	0.01	1.99	0.063	1.91	0.015
  // 25	        0.00728	        0.012	0.0514	0.02	1.95	0.087	1.95	0.018
  // 35	        -0.0346	        0.026	0.114	0.037	2.21	0.15	1.92	0.024
  // 45	        -0.0362	        0.057	0.0983	0.078	2.21	0.34 	1.95	0.04

  float star_cent[6] = {2.5,7.5,15,25,35,45};
  float star_v34[6] = {-0.00156,
                       0.00549,
                       0.000938,
                       0.00728,
                       -0.0346,
                       -0.0362};
  float star_ev34[6] = {0.004,
                        0.0058,
                        0.0069,
                        0.012,
                        0.026,
                        0.057};
  float star_ratio[6] = {2.04,
                         1.92,
                         1.99,
                         1.95,
                         2.21,
                         2.21};
  float star_eratio[6] = {0.096,
                          0.082,
                          0.063,
                          0.087,
                          0.15,
                          0.34};

  //TGraphErrors* tge_norm = new TGraphErrors(nbins,cent,norm_v3,0,norm_ev3);
  TGraphErrors* tge_norm = new TGraphErrors(6,star_cent,star_v34,0,star_ev34);
  TGraphErrors* tge_swap = new TGraphErrors(nbins,cent,swap_c3,0,swap_ec3);
  TGraphErrors* tge_swap2 = new TGraphErrors(nbins,cent,swap_c2,0,swap_ec2);
  TGraphErrors* tge_ratio = new TGraphErrors(nbins,cent,ratio,0,eratio);
  TGraphErrors* tge_sratio = new TGraphErrors(6,star_cent,star_ratio,0,star_eratio);

  // --- do some drawing

  tge_norm->SetLineColor(kBlack);
  tge_norm->SetMarkerColor(kBlack);
  tge_norm->SetMarkerStyle(kFullCircle);
  tge_swap->SetLineColor(kBlack);
  tge_swap->SetMarkerColor(kBlack);
  tge_swap->SetMarkerStyle(kOpenCircle);
  tge_swap2->SetLineColor(kBlack);
  tge_swap2->SetMarkerColor(kBlack);
  tge_swap2->SetMarkerStyle(kFullCircle);
  tge_ratio->SetLineColor(kBlack);
  tge_ratio->SetMarkerColor(kBlack);
  tge_ratio->SetMarkerStyle(kOpenCircle);
  tge_sratio->SetLineColor(kBlack);
  tge_sratio->SetMarkerColor(kBlack);
  tge_sratio->SetMarkerStyle(kFullCircle);

  TCanvas* c1 = new TCanvas("c1","");

  double xmin = 0;
  double xmax = 60;
  double ymin = -0.2;
  double ymax = 0.1;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("10^{6} v_{3}^{4}{4}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_norm->Draw("pz");
  tge_swap->Draw("pz");
  TLatex latt;
  latt.SetNDC();
  latt.SetTextSize(0.05);
  latt.SetTextAlign(11);
  latt.DrawLatex(0.50, 0.87, "Au+Au #sqrt{s_{_{NN}}} = 200 GeV");
  TLegend *leg = new TLegend(0.18,0.18,0.38,0.38);
  leg->SetFillStyle(0);
  leg->AddEntry(tge_swap,"PHENIX 1<|#eta|<3","p");
  leg->AddEntry(tge_norm,"STAR |#eta|<1","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  TLine* line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  // c1->Print("STAR/v34_star.png");
  // c1->Print("STAR/v34_star.pdf");


  float star_c34[6];
  float star_ec34[6];
  for ( int i = 0; i < 6; ++i )
    {
      star_c34[i] = -star_v34[i]*1e-6;
      star_ec34[i] = star_ev34[i]*1e-6;
      //cout << star_c34[i] << " " << star_ec34[i] << endl;
    }
  TGraphErrors* tge_star = new TGraphErrors(6,star_cent,star_c34,0,star_ec34);
  TGraphErrors* tge_phen = new TGraphErrors(nbins,cent,norm_c3,0,norm_ec3);

  tge_star->SetLineColor(kBlack);
  tge_star->SetMarkerColor(kBlack);
  tge_star->SetMarkerStyle(kFullStar);
  tge_star->SetMarkerSize(2.5);
  tge_phen->SetLineColor(kRed);
  tge_phen->SetMarkerColor(kRed);
  tge_phen->SetMarkerStyle(kFullCircle);


  xmin = 0;
  xmax = 60;
  ymin = -1e-7;
  ymax = 2e-7;
  if ( hdummy) delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("c_{3}{4}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_star->Draw("pz");
  tge_phen->Draw("pz");
  latt.SetNDC();
  latt.SetTextSize(0.05);
  latt.SetTextAlign(11);
  latt.DrawLatex(0.50, 0.25, "Au+Au #sqrt{s_{_{NN}}} = 200 GeV");
  leg = new TLegend(0.18,0.73,0.38,0.93);
  leg->SetFillStyle(0);
  leg->AddEntry(tge_phen,"PHENIX 1<|#eta|<3","p");
  leg->AddEntry(tge_star,"STAR |#eta|<1","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  // c1->Print("STAR/c34_star.png");
  // c1->Print("STAR/c34_star.pdf");
  c1->Print(Form("STAR/help_%d_c34.png",flag));
  c1->Print(Form("STAR/help_%d_c34.pdf",flag));


  return;


  ymin = -0.2;
  ymax = 0.5;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("10^{6} v_{3}^{4}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_swap->Draw("pz");
  tge_swap2->Draw("pz");
  delete leg;
  leg = new TLegend(0.18,0.68,0.38,0.88);
  leg->SetFillStyle(0);
  //leg->SetHeader("10^{6} v_{3}^{4}");
  leg->AddEntry(tge_swap,"PHENIX v_{3}^{4}{4}","p");
  leg->AddEntry(tge_swap2,"PHENIX v_{3}^{4}{2}","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  delete line;
  line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print("STAR/v342_star.png");
  c1->Print("STAR/v342_star.pdf");


  ymin = 0.0;
  ymax = 9.0;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("2 - v_{3}^{4}{4}/v_{3}^{4}{2}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_ratio->Draw("pz");
  tge_sratio->Draw("pz");
  delete leg;
  leg = new TLegend(0.18,0.18,0.38,0.38);
  leg->SetFillStyle(0);
  //leg->SetHeader("10^{6} v_{3}^{4}");
  leg->AddEntry(tge_ratio,"PHENIX 1<|#eta|<3","p");
  leg->AddEntry(tge_sratio,"STAR |#eta|<1","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  delete line;
  line = new TLine(xmin,2,xmax,2);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print("STAR/v342_ratio_star.png");
  c1->Print("STAR/v342_ratio_star.pdf");


}

TH1D* get_cumuhist(TFile* fin)
{
  // --- random number helper to prevent memory collisions with ROOT named objects...
  double rand = gRandom->Rndm();
  int helper = rand*10000;
  // --- get the tprofiles
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_recursion_0_3");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_recursion_0_1");
  if ( ctp1f_for == NULL ) return NULL;
  if ( ctp1f_two == NULL ) return NULL;
  ctp1f_for->Rebin(rebin);
  ctp1f_two->Rebin(rebin);
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

TH1D* get_histv324(TFile* fin)
{
  // --- random number helper to prevent memory collisions with ROOT named objects...
  double rand = gRandom->Rndm();
  int helper = rand*10000;
  // --- get the tprofiles
  //TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_recursion_0_1");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c32");
  if ( ctp1f_two == NULL ) return NULL;
  //ctp1f_two->Rebin(rebin); // maybe already rebinned above? need to add clones to prevent this
  // --- convert to th1ds (to do math operations)
  TH1D* th1d_two = ctp1f_two->ProjectionX(Form("th1d_two_%d",helper)); // <2>
  // --- calc 22
  TH1D* th1d_22 = (TH1D*)th1d_two->Clone(Form("th1d_222_%d",helper)); // <2>^2
  th1d_22->Multiply(th1d_two);
  // --- return
  return th1d_22;
}



void try_sys()
{

  TFile* fbase = NULL;
  TFile* feval = NULL;

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12290.root");
  try_sys_files(fbase,feval,"dcar");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12195.root");
  try_sys_files(fbase,feval,"zvtx");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12194.root");
  try_sys_files(fbase,feval,"chi2");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12289.root");
  try_sys_files(fbase,feval,"nhit");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12420.root");
  feval = TFile::Open("input/histos_12432.root");
  try_sys_files(fbase,feval,"qrbr");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12420.root");
  feval = TFile::Open("input/histos_12555.root");
  try_sys_files(fbase,feval,"code");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12579.root"); // cent-based q-vector recentering
  feval = TFile::Open("input/histos_12581.root"); // no q-vector recentering
  try_sys_files(fbase,feval,"noqr");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12579.root"); // cent-based q-vector recentering
  feval = TFile::Open("input/histos_12587.root"); // fvtxt-based q-vector recentering
  try_sys_files(fbase,feval,"nfqr");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12587.root"); // fvtxt-based q-vector recentering, regular cuts
  feval = TFile::Open("input/histos_12650.root"); // fvtxt-based q-vector recentering, new cuts
  try_sys_files(fbase,feval,"newc");
  fbase->Close();
  feval->Close();

}



void try_sys_files(TFile* fbase, TFile* feval, const char* systype)
{

  // --------------------------------------------------------------------
  // --- v3 with recurision
  // --------------------------------------------------------------------

  TProfile* for_base = (TProfile*)fbase->Get("centrality_recursion_0_3");
  TProfile* two_base = (TProfile*)fbase->Get("centrality_recursion_0_1");
  TProfile* for_eval = (TProfile*)feval->Get("centrality_recursion_0_3");
  TProfile* two_eval = (TProfile*)feval->Get("centrality_recursion_0_1");

  //int rebin = 5;

  for_base->Rebin(rebin);
  two_base->Rebin(rebin);
  for_eval->Rebin(rebin);
  two_eval->Rebin(rebin);

  crunch_cumu4(for_base,two_base,for_eval,two_eval,systype,3);

}

