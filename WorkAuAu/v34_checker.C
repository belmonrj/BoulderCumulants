#include "systematics_helper.C"

int spec_rebin = 70;
int rebin = 5;

TH1D* get_cumuhist_ntrk(TFile*);
TH1D* get_cumuhist(TFile*);
TH1D* get_cumuhist_a(TFile*);
TH1D* get_cumuhist_b(TFile*);

void do_check(int);
void do_check(int,int);

void try_sys();
void try_sys_files(TFile*, TFile*, const char*);

void v34_checker()
{

  //do_check(12097); // old baseline
  //do_check(12194); // chi2
  //do_check(12195); // zvtx
  //do_check(12289); // nhit
  //do_check(12290); // dcar
  //do_check(12420); // another baseline
  //do_check(12432); // qrbr
  //do_check(12555); // code
  //do_check(12579); // another baseline
  //do_check(12581); // noqr
  //do_check(12587); // nfqr
  //do_check(12634); // version used for paper
  //do_check(12650); // newc

  do_check(13799); // base
  do_check(13847); // nhit
  do_check(13872); // dcar
  do_check(13897); // zvtx
  do_check(13911); // chi2
  do_check(13926); // dubl

  try_sys();

}

void do_check(int flag)
{
  do_check(flag,0);
  do_check(flag,1);
  do_check(flag,2);
}

void do_check(int flag, int type)
{

  //TFile* fileR = TFile::Open("RunByRun/combin.root"); // reference
  TFile* fileR = TFile::Open(Form("input/histos_%d.root",flag)); // reference

  TH1D* histR = NULL;
  if ( type == 0 ) histR = get_cumuhist(fileR); // reference
  if ( type == 1 ) histR = get_cumuhist_a(fileR); // reference
  if ( type == 2 ) histR = get_cumuhist_b(fileR); // reference
  if ( histR == NULL ) { cout << "RECURSION HISTOGRAM MISSING!!! " << flag << endl; return; }

  const int nbins = histR->GetNbinsX();

  cout << nbins << endl;

  //double standard[nbins];
  double norm_c3[nbins];
  double norm_ec3[nbins];
  double sysnorm_ec3[nbins];
  double hisysnorm_ec3[nbins];
  double losysnorm_ec3[nbins];
  double cent[nbins];
  double sys = 0.5;
  double hisys = 0.3;
  double losys = 0.6;
  double standard[20]={
    2.32027e-08,
    2.75107e-08,
    3.1886e-08,
    3.25301e-08,
    5.93043e-08,
    4.56757e-08,
    4.92848e-08,
    3.41955e-08,
    7.15555e-08,
    8.71393e-08,
    8.19061e-08,
    2.27846e-07,
    5.02444e-07,
    4.453e-07,
    1.65036e-06,
    6.22593e-07,
    -8.944e-06,
    -9.35808e-05,
    -0.000348249,
    0};
  for ( int i = 0; i < nbins; ++i )
    {
      cent[i] = histR->GetBinCenter(i+1);
      norm_c3[i] = histR->GetBinContent(i+1);
      // if ( flag == 12634 )
      //   {
      //     cout << cent[i] << " " << norm_c3[i] << endl;
      //   }
      norm_ec3[i] = histR->GetBinError(i+1);
      sysnorm_ec3[i] = standard[i]*sys;
      // hisysnorm_ec3[i] = standard[i]+sysnorm_ec3[i];
      // losysnorm_ec3[i] = standard[i]-sysnorm_ec3[i];
      hisysnorm_ec3[i] = standard[i]*(1+hisys);
      losysnorm_ec3[i] = standard[i]*(1-losys);
    }

  TGraph* tge_std = new TGraph(11,cent,standard);
  tge_std->SetLineColor(kGray);
  tge_std->SetMarkerColor(kGray);
  tge_std->SetMarkerStyle(kOpenCircle);
  TGraph* tge_sys_hi = new TGraph(11,cent,hisysnorm_ec3);
  TGraph* tge_sys_lo = new TGraph(11,cent,losysnorm_ec3);
  tge_sys_hi->SetLineColor(kBlack);
  tge_sys_hi->SetLineWidth(2);
  tge_sys_hi->SetLineStyle(1);
  tge_sys_lo->SetLineColor(kBlack);
  tge_sys_lo->SetLineWidth(2);
  tge_sys_lo->SetLineStyle(1);


  // --- do some drawing



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
  //tge_norm->Draw("pz");
  TLatex latt;
  latt.SetNDC();
  latt.SetTextSize(0.05);
  latt.SetTextAlign(11);
  latt.DrawLatex(0.50, 0.87, "Au+Au #sqrt{s_{_{NN}}} = 200 GeV");
  TLegend *leg = new TLegend(0.18,0.18,0.38,0.38);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->Draw();
  TLine* line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  // c1->Print("STAR/v34_star.png");
  // c1->Print("STAR/v34_star.pdf");


  TGraphErrors* tge_phen = new TGraphErrors(nbins,cent,norm_c3,0,norm_ec3);

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
  tge_phen->Draw("pz");
  latt.SetNDC();
  latt.SetTextSize(0.05);
  latt.SetTextAlign(11);
  latt.DrawLatex(0.50, 0.25, "Au+Au #sqrt{s_{_{NN}}} = 200 GeV");
  leg = new TLegend(0.18,0.73,0.38,0.93);
  leg->SetFillStyle(0);
  leg->AddEntry(tge_phen,"PHENIX 1<|#eta|<3","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print(Form("STAR/help_%d_c34_%d.png",flag,type));
  c1->Print(Form("STAR/help_%d_c34_%d.pdf",flag,type));
  tge_sys_hi->Draw("l");
  tge_sys_lo->Draw("l");
  tge_std->Draw("p");
  c1->Print(Form("STAR/syshelp_%d_c34_%d.png",flag,type));
  c1->Print(Form("STAR/syshelp_%d_c34_%d.pdf",flag,type));


  if ( type != 0 ) return; // we'll skip this part for now...

  TH1D* histRN = get_cumuhist_ntrk(fileR); // reference

  histRN->SetLineColor(kRed);
  histRN->SetMarkerColor(kRed);
  histRN->SetMarkerStyle(kFullCircle);

  xmin = 0;
  xmax = 650;
  ymin = -1e-7;
  ymax = 2e-7;
  if ( hdummy) delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("c_{3}{4}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("nfvtxt");
  histRN->Draw("ex0p same");
  latt.SetNDC();
  latt.SetTextSize(0.05);
  latt.SetTextAlign(11);
  latt.DrawLatex(0.50, 0.25, "Au+Au #sqrt{s_{_{NN}}} = 200 GeV");
  leg = new TLegend(0.18,0.73,0.38,0.93);
  leg->SetFillStyle(0);
  leg->AddEntry(tge_phen,"PHENIX 1<|#eta|<3","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print(Form("STAR/nthelp_%d_c34_%d.png",flag,type));
  c1->Print(Form("STAR/nthelp_%d_c34_%d.pdf",flag,type));


}

TH1D* get_cumuhist_ntrk(TFile* fin)
{
  // --- random number helper to prevent memory collisions with ROOT named objects...
  double rand = gRandom->Rndm();
  int helper = rand*10000;
  // --- get the tprofiles
  TProfile* ctp1f_for = (TProfile*)fin->Get("nfvtxt_recursion_0_3");
  TProfile* ctp1f_two = (TProfile*)fin->Get("nfvtxt_recursion_0_1");
  if ( ctp1f_for == NULL ) return NULL;
  if ( ctp1f_two == NULL ) return NULL;
  ctp1f_for->Rebin(spec_rebin);
  ctp1f_two->Rebin(spec_rebin);
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


TH1D* get_cumuhist_a(TFile* fin)
{
  // --- random number helper to prevent memory collisions with ROOT named objects...
  double rand = gRandom->Rndm();
  int helper = rand*10000;
  // --- get the tprofiles
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c34a");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c32");
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




TH1D* get_cumuhist_b(TFile* fin)
{
  // --- random number helper to prevent memory collisions with ROOT named objects...
  double rand = gRandom->Rndm();
  int helper = rand*10000;
  // --- get the tprofiles
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c34b");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c32");
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




void try_sys()
{

  TFile* fbase = NULL;
  TFile* feval = NULL;

  // fbase = TFile::Open("input/histos_12097.root");
  // feval = TFile::Open("input/histos_12290.root");
  // try_sys_files(fbase,feval,"dcar");
  // fbase->Close();
  // feval->Close();

  // fbase = TFile::Open("input/histos_12097.root");
  // feval = TFile::Open("input/histos_12195.root");
  // try_sys_files(fbase,feval,"zvtx");
  // fbase->Close();
  // feval->Close();

  // fbase = TFile::Open("input/histos_12097.root");
  // feval = TFile::Open("input/histos_12194.root");
  // try_sys_files(fbase,feval,"chi2");
  // fbase->Close();
  // feval->Close();

  // fbase = TFile::Open("input/histos_12097.root");
  // feval = TFile::Open("input/histos_12289.root");
  // try_sys_files(fbase,feval,"nhit");
  // fbase->Close();
  // feval->Close();

  // fbase = TFile::Open("input/histos_12420.root");
  // feval = TFile::Open("input/histos_12432.root");
  // try_sys_files(fbase,feval,"qrbr");
  // fbase->Close();
  // feval->Close();

  // fbase = TFile::Open("input/histos_12420.root");
  // feval = TFile::Open("input/histos_12555.root");
  // try_sys_files(fbase,feval,"code");
  // fbase->Close();
  // feval->Close();

  // fbase = TFile::Open("input/histos_12579.root"); // cent-based q-vector recentering
  // feval = TFile::Open("input/histos_12581.root"); // no q-vector recentering
  // try_sys_files(fbase,feval,"noqr");
  // fbase->Close();
  // feval->Close();

  // fbase = TFile::Open("input/histos_12579.root"); // cent-based q-vector recentering
  // feval = TFile::Open("input/histos_12587.root"); // fvtxt-based q-vector recentering
  // try_sys_files(fbase,feval,"nfqr");
  // fbase->Close();
  // feval->Close();

  // fbase = TFile::Open("input/histos_12587.root"); // fvtxt-based q-vector recentering, regular cuts
  // feval = TFile::Open("input/histos_12650.root"); // fvtxt-based q-vector recentering, new cuts
  // try_sys_files(fbase,feval,"newc");
  // fbase->Close();
  // feval->Close();

  fbase = TFile::Open("input/histos_13799.root");
  feval = TFile::Open("input/histos_13847.root");
  try_sys_files(fbase,feval,"nhit");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_13799.root");
  feval = TFile::Open("input/histos_13872.root");
  try_sys_files(fbase,feval,"dcar");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_13799.root");
  feval = TFile::Open("input/histos_13897.root");
  try_sys_files(fbase,feval,"zvtx");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_13799.root");
  feval = TFile::Open("input/histos_13911.root");
  try_sys_files(fbase,feval,"chi2");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_13799.root");
  feval = TFile::Open("input/histos_13926.root");
  try_sys_files(fbase,feval,"dubl");
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

