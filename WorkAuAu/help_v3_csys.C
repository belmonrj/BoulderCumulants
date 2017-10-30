#include "calc_cumulants.C"
#include "calc_subevents.C"

void takefiles(TFile*, TFile*, const char*);

void crunch(TProfile*, TProfile*, const char*, const char*);

void crunch(TH1D*, TH1D*, const char*, const char*, double, double, double, double);



void help_v3_csys()
{

  TFile* fbase = NULL;
  TFile* feval = NULL;

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12185.root");
  takefiles(fbase,feval,"dcar");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12195.root");
  takefiles(fbase,feval,"zvtx");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12194.root");
  takefiles(fbase,feval,"chi2");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12203.root");
  takefiles(fbase,feval,"nhit");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_99999.root");
  takefiles(fbase,feval,"acce");
  fbase->Close();
  feval->Close();

}

void takefiles(TFile* fbase, TFile* feval, const char* systype)
{

  int harmonic = 3;
  int rebin = 2;

  bool isacce = false;
  if ( strcmp(systype,"acce") == 0 ) isacce = true;

  // --- make sure both files are not null
  if ( !fbase || !feval )
    {
      cout << "One or more files missing " << fbase << " " << feval << endl;
      return;
    }

  // --- get the <<2>> and <<4>> (3rd harmonic)
  TProfile* for_base = (TProfile*)fbase->Get("centrality_recursion_0_3");
  TProfile* two_base = (TProfile*)fbase->Get("centrality_recursion_0_1");
  TProfile* for_eval = (TProfile*)feval->Get("centrality_recursion_0_3");
  TProfile* two_eval = (TProfile*)feval->Get("centrality_recursion_0_1");

  for_base->Rebin(rebin);
  two_base->Rebin(rebin);
  if ( !isacce )
  {
  for_eval->Rebin(rebin);
  two_eval->Rebin(rebin);
  }

  // --- use a random number generator to prevent over-writing histograms (a funny ROOT feature)
  double rand = gRandom->Rndm();
  int helper = rand*10000;

  // --- get the extra base histos
  TH1D* th1d_base_for = for_base->ProjectionX(Form("th1d_base_for_%d",helper)); // <4>
  TH1D* th1d_base_two = two_base->ProjectionX(Form("th1d_base_two_%d",helper)); // <2>
  TH1D* th1d_base_222 = (TH1D*)th1d_base_two->Clone(Form("th1d_base_222_%d",helper)); // 2<2>^2       (for the 4p)
  th1d_base_222->Multiply(th1d_base_two);
  th1d_base_222->Scale(2);
  TH1D* th1d_base_c24 = (TH1D*)th1d_base_for->Clone("th1d_base_c24"); // c2{4} = <4> - 2<2>^2
  th1d_base_c24->Add(th1d_base_222,-1);

  // --- get the extra eval histos
  TH1D* th1d_eval_for = for_eval->ProjectionX(Form("th1d_eval_for_%d",helper)); // <4>
  TH1D* th1d_eval_two = two_eval->ProjectionX(Form("th1d_eval_two_%d",helper)); // <2>
  TH1D* th1d_eval_222 = (TH1D*)th1d_eval_two->Clone(Form("th1d_eval_222_%d",helper)); // 2<2>^2       (for the 4p)
  th1d_eval_222->Multiply(th1d_eval_two);
  th1d_eval_222->Scale(2);
  TH1D* th1d_eval_c24 = (TH1D*)th1d_eval_for->Clone("th1d_eval_c24"); // c2{4} = <4> - 2<2>^2
  th1d_eval_c24->Add(th1d_eval_222,-1);


  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = -1e-4;
  double ymax = 1e-4;
  // if ( iscent ) xmax = 100.0;
  // if ( isntrk && !islowzoom ) xmax = 650.0;



  // --- four particle components and cumulants

  //-- setup canvas
  //-- Margins
  float Lmarg = 0.14;
  float Rmarg = 0.05;
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
  TPad *pcomp4 = new TPad("pcomp4", "comp4", 0, 0.5, 1, 1);
  pcomp4->SetMargin(Lmarg, Rmarg, 0, 0.1);
  pcomp4->SetTicks(1, 1);
  pcomp4->Draw();

  ccomp4->cd();
  TPad *pcumu4 = new TPad("pcumu4", "cumu4", 0, 0, 1, 0.5);
  pcumu4->SetMargin(Lmarg, Rmarg, 0.22, 0);
  pcumu4->SetTicks(1, 1);
  pcumu4->Draw();

  //-- plot
  pcomp4->cd();
  ymin = -1e-5;
  ymax = 1e-4;
  if ( harmonic == 3 )
    {
      ymin = -1e-6;
      ymax = 1e-5;
      ymin = -5e-7;
      ymax = 6e-6; // to get the hash mark
    }
  if ( harmonic == 4 )
    {
      ymin = -1e-6;
      ymax = 1e-5;
    }
  TH2D* empty_comp4 = new TH2D("empty_comp4","",1,xmin,xmax,1,ymin,ymax);
  empty_comp4->Draw();
  empty_comp4->GetXaxis()->SetLabelSize(0.0);
  empty_comp4->GetXaxis()->SetTitleSize(0.0);
  empty_comp4->GetYaxis()->SetLabelFont(62);
  empty_comp4->GetYaxis()->SetTitleFont(62);
  empty_comp4->GetYaxis()->SetLabelSize(0.08);
  empty_comp4->GetYaxis()->SetTitleSize(0.08);
  empty_comp4->GetYaxis()->SetTitle("components");
  empty_comp4->GetYaxis()->SetTitleOffset(0.9);
  th1d_base_222->SetMarkerStyle(kFullCircle);
  th1d_base_222->SetMarkerColor(kRed);
  th1d_base_222->SetLineColor(kBlack);
  th1d_base_222->Draw("same ex0p");
  th1d_base_for->SetMarkerStyle(kFullSquare);
  th1d_base_for->SetMarkerColor(kBlue);
  th1d_base_for->SetLineColor(kBlack);
  th1d_base_for->Draw("same ex0p");
  th1d_eval_222->SetMarkerStyle(kOpenCircle);
  th1d_eval_222->SetMarkerColor(kRed);
  th1d_eval_222->SetLineColor(kBlack);
  th1d_eval_222->Draw("same ex0p");
  th1d_eval_for->SetMarkerStyle(kOpenSquare);
  th1d_eval_for->SetMarkerColor(kBlue);
  th1d_eval_for->SetLineColor(kBlack);
  th1d_eval_for->Draw("same ex0p");
  TLine *cline = new TLine(xmin,0,xmax,0);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  TLegend* leg_comp4 = new TLegend(0.165,0.70,0.4,0.85);
  leg_comp4->SetTextFont(62);
  leg_comp4->SetTextSize(0.08);
  leg_comp4->SetFillStyle(0);
  leg_comp4->AddEntry(th1d_base_222,"2#LT#LT2#GT#GT^{2}","p");
  leg_comp4->AddEntry(th1d_base_for,"#LT#LT4#GT#GT","p");
  leg_comp4->Draw();

  //-- ratio
  pcumu4->cd();
  ymin = -1.4999e-5;
  ymax = 1.4999e-5;
  if ( harmonic == 3 )
    {
      ymin = -1.4999e-6;
      ymax = 1.4999e-6;
      ymin = -0.4999e-6;
      ymax = 0.4999e-6;
      ymin = -0.3999e-6;
      ymax = 0.3999e-6;
    }
  if ( harmonic == 4 )
    {
      ymin = -1.4999e-6;
      ymax = 1.4999e-6;
    }
  TH2D* empty_cumu4 = new TH2D("empty_cumu4","",1,xmin,xmax,1,ymin,ymax);
  empty_cumu4->Draw();
  // if ( iscent ) empty_cumu4->GetXaxis()->SetTitle("Centrality (%)");
  // if ( isntrk ) empty_cumu4->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty_cumu4->GetXaxis()->SetTitle("Centrality (%)");
  empty_cumu4->GetXaxis()->SetLabelFont(62);
  empty_cumu4->GetXaxis()->SetTitleFont(62);
  empty_cumu4->GetXaxis()->SetLabelSize(0.08);
  empty_cumu4->GetXaxis()->SetTitleSize(0.08);
  empty_cumu4->GetYaxis()->SetLabelFont(62);
  empty_cumu4->GetYaxis()->SetTitleFont(62);
  empty_cumu4->GetYaxis()->SetLabelSize(0.08);
  empty_cumu4->GetYaxis()->SetTitleSize(0.08);
  empty_cumu4->GetYaxis()->SetTitle("cumulant");
  empty_cumu4->GetYaxis()->SetTitleOffset(0.9);
  th1d_base_c24->SetMarkerStyle(kFullCircle);
  th1d_base_c24->SetLineColor(kBlack);
  th1d_base_c24->Draw("same ex0p");
  th1d_eval_c24->SetMarkerStyle(kOpenCircle);
  th1d_eval_c24->SetLineColor(kBlack);
  th1d_eval_c24->Draw("same ex0p");
  TLegend* leg_cumu4 = new TLegend(0.165,0.87,0.4,0.97);
  leg_cumu4->SetTextFont(62);
  leg_cumu4->SetTextSize(0.08);
  leg_cumu4->SetFillStyle(0);
  leg_cumu4->AddEntry(th1d_base_c24,Form("c_{%d}{4} = -v_{%d}^{4}",harmonic,harmonic),"p");
  leg_cumu4->Draw();
  cline->Draw();
  ccomp4->Print(Form("FigsWork/helpme_h%d_%s_cumulant4.png",harmonic,systype));
  ccomp4->Print(Form("FigsWork/helpme_h%d_%s_cumulant4.pdf",harmonic,systype));
  delete ccomp4;
  delete empty_cumu4;
  delete empty_comp4;
  delete leg_cumu4;
  delete leg_comp4;



}



void crunch(TProfile* tpbase, TProfile* tpeval, const char* systype, const char* quantity)
{
  if ( !tpbase || !tpeval )
    {
      cout << "one or more null histograms " << tpbase << " " << tpeval << endl;
      return;
    }
  TH1D* hbase = tpbase->ProjectionX("hbase");
  TH1D* heval = tpeval->ProjectionX("heval");
  crunch(hbase,heval,systype,quantity,0,100,20,50);
}



void crunch(TH1D* hbase, TH1D* heval, const char* systype, const char* quantity, double xmin, double xmax, double fmin, double fmax)
{

  if ( !hbase || !heval )
    {
      cout << "one or more null histograms " << hbase << " " << heval << endl;
      return;
    }

  TH1D* hratio = (TH1D*)heval->Clone("hratio");
  hratio->Divide(hbase);
  for ( int i = 0; i < hratio->GetNbinsX(); ++i )
    {
      double cont = hratio->GetBinContent(i+1);
      if ( cont <= 0.0 || cont == 1.0 )
        {
          hratio->SetBinContent(i+1,0);
          hratio->SetBinError(i+1,9999); // effectively de-weight during fit
        }
    }


  bool iscent = true;
  bool isntrk = false;

  //-- setup canvas
  //-- Margins
  float Lmarg = 0.15;
  float Rmarg = 0.04;
  float Bmarg = 0.16;
  float Tmarg = 0.02;

  double w = 800 / (1 + Lmarg + Rmarg);
  double h = 900 / (1 + Bmarg + Tmarg);

  TCanvas *ccomp = new TCanvas("ccomp", "", w, h);
  ccomp->SetMargin(0, 0, 0, 0);

  ccomp->cd();
  TPad *pcomp = new TPad("pcomp", "comp", 0, 0.45, 1, 1);
  pcomp->SetMargin(Lmarg, Rmarg, 0, 0.1);
  pcomp->SetTicks(1, 1);
  pcomp->Draw();

  ccomp->cd();
  TPad *pratio = new TPad("pratio", "ratio", 0, 0, 1, 0.45);
  pratio->SetMargin(Lmarg, Rmarg, 0.22, 0);
  pratio->SetTicks(1, 1);
  pratio->Draw();

  //-- plot
  pcomp->cd();
  double ymin = -1e-2;
  double ymax = 1e-1;
  // double xmin = 0;
  // double xmax = 100;
  TH2D* empty_comp = new TH2D("empty_comp","",1,xmin,xmax,1,ymin,ymax);
  empty_comp->Draw();
  empty_comp->GetXaxis()->SetLabelSize(0.0);
  empty_comp->GetXaxis()->SetTitleSize(0.0);
  empty_comp->GetYaxis()->SetLabelFont(62);
  empty_comp->GetYaxis()->SetTitleFont(62);
  empty_comp->GetYaxis()->SetLabelSize(0.075);
  empty_comp->GetYaxis()->SetTitleSize(0.075);
  empty_comp->GetYaxis()->SetTitle("comparison");
  empty_comp->GetYaxis()->SetTitleOffset(1.05);
  hbase->SetMarkerStyle(kOpenCircle);
  hbase->SetMarkerColor(kRed);
  hbase->SetLineColor(kBlack);
  hbase->Draw("same ex0p");
  heval->SetMarkerStyle(kOpenSquare);
  heval->SetMarkerColor(kBlue);
  heval->SetLineColor(kBlack);
  heval->Draw("same ex0p");
  TLine *cline = new TLine(xmin,0,xmax,0);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  TLegend* leg_comp = new TLegend(0.18,0.70,0.4,0.85);
  leg_comp->SetTextFont(62);
  leg_comp->SetTextSize(0.075);
  leg_comp->SetFillStyle(0);
  leg_comp->AddEntry(hbase,Form("base for %s",quantity),"p");
  leg_comp->AddEntry(heval,systype,"p");
  leg_comp->Draw();

  //-- ratio
  pratio->cd();
  ymin = 0.25;
  ymax = 1.75;
  // ymin = -0.01;
  // ymax = 1.99;
  TH2D* empty_ratio = new TH2D("empty_ratio","",1,xmin,xmax,1,ymin,ymax);
  empty_ratio->Draw();
  if ( iscent ) empty_ratio->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty_ratio->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty_ratio->GetXaxis()->SetLabelFont(62);
  empty_ratio->GetXaxis()->SetTitleFont(62);
  empty_ratio->GetXaxis()->SetLabelSize(0.090);
  empty_ratio->GetXaxis()->SetTitleSize(0.090);
  empty_ratio->GetYaxis()->SetLabelFont(62);
  empty_ratio->GetYaxis()->SetTitleFont(62);
  empty_ratio->GetYaxis()->SetLabelSize(0.090);
  empty_ratio->GetYaxis()->SetTitleSize(0.090);
  empty_ratio->GetYaxis()->SetTitle("ratio");
  empty_ratio->GetYaxis()->SetTitleOffset(0.9);
  hratio->SetMarkerStyle(kOpenCircle);
  hratio->SetLineColor(kBlack);
  hratio->GetXaxis()->SetRangeUser(fmin,fmax);
  hratio->Draw("same ex0p");
  if ( cline) delete cline;
  cline = new TLine(xmin,1,xmax,1);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  TF1* fun = new TF1("fun","pol0",xmin,xmax);
  fun->SetParameter(0,1.0);
  hratio->Fit(fun,"","",fmin,fmax);
  TLegend* leg_ratio = new TLegend(0.18,0.80,0.4,0.95);
  leg_ratio->SetTextFont(62);
  leg_ratio->SetTextSize(0.090);
  leg_ratio->SetFillStyle(0);
  //leg_ratio->AddEntry(hratio,Form("Sys Uncert on %s = %.2f%%", quantity, fabs(1.0 - fun->GetParameter(0)) * 100.0),"p");
  leg_ratio->AddEntry(hratio,Form("Sys = %.2f%%", fabs(1.0 - fun->GetParameter(0)) * 100.0),"p");
  leg_ratio->Draw();
  ccomp->Print(Form("Systematics/sys_%s_%s.png",quantity,systype));
  ccomp->Print(Form("Systematics/sys_%s_%s.pdf",quantity,systype));
  delete cline;
  delete ccomp;
  delete empty_ratio;
  delete empty_comp;
  delete leg_ratio;
  delete leg_comp;

}

