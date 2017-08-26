#include "get_cumulants.C"

void takefiles(TFile*, TFile*, const char*);

void crunch(TProfile*, TProfile*, const char*);

void crunch(TH1D*, TH1D*, const char*, double, double, double, double);



void get_sys()
{

  TFile* fbase = TFile::Open("input/histos_11724.root");
  TFile* ftest = TFile::Open("input/histos_11660.root");
  takefiles(fbase,ftest,"test");

}

void takefiles(TFile* fbase, TFile* feval, const char* handle)
{

  if ( !fbase || !feval )
    {
      cout << "One or more files missing " << fbase << " " << feval << endl;
      return;
    }

  TProfile* eit_base = (TProfile*)fbase->Get("centrality_recursion_0_6");
  TProfile* six_base = (TProfile*)fbase->Get("centrality_recursion_0_4");
  TProfile* for_base = (TProfile*)fbase->Get("centrality_recursion_0_2");
  TProfile* two_base = (TProfile*)fbase->Get("centrality_recursion_0_0");
  TH1D* v28base = NULL;
  TH1D* v26base = NULL;
  TH1D* v24base = NULL;
  TH1D* v22base = NULL;
  TH1D* c28base = NULL;
  TH1D* c26base = NULL;
  TH1D* c24base = NULL;
  TH1D* c22base = NULL;
  get_cumulants(eit_base,six_base,for_base,two_base,&v28base,&v26base,&v24base,&v22base,&c28base,&c26base,&c24base,&c22base,1);
  TProfile* eit_eval = (TProfile*)feval->Get("centrality_recursion_0_6");
  TProfile* six_eval = (TProfile*)feval->Get("centrality_recursion_0_4");
  TProfile* for_eval = (TProfile*)feval->Get("centrality_recursion_0_2");
  TProfile* two_eval = (TProfile*)feval->Get("centrality_recursion_0_0");
  TH1D* v28eval = NULL;
  TH1D* v26eval = NULL;
  TH1D* v24eval = NULL;
  TH1D* v22eval = NULL;
  TH1D* c28eval = NULL;
  TH1D* c26eval = NULL;
  TH1D* c24eval = NULL;
  TH1D* c22eval = NULL;
  get_cumulants(eit_eval,six_eval,for_eval,two_eval,&v28eval,&v26eval,&v24eval,&v22eval,&c28eval,&c26eval,&c24eval,&c22eval,1);
  crunch(v22base,v22eval,Form("cent_%s_v22",handle),0,100,1,93);
  crunch(v24base,v24eval,Form("cent_%s_v24",handle),0,100,20,50);
  crunch(v26base,v26eval,Form("cent_%s_v26",handle),0,100,20,50);
  crunch(v28base,v28eval,Form("cent_%s_v28",handle),0,100,20,50);


}



void crunch(TProfile* tpbase, TProfile* tpeval, const char* handle)
{
  if ( !tpbase || !tpeval )
    {
      cout << "one or more null histograms " << tpbase << " " << tpeval << endl;
      return;
    }
  TH1D* hbase = tpbase->ProjectionX("hbase");
  TH1D* heval = tpeval->ProjectionX("heval");
  crunch(hbase,heval,handle,0,100,20,50);
}



void crunch(TH1D* hbase, TH1D* heval, const char* handle, double xmin, double xmax, double fmin, double fmax)
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
      if ( cont <= 0.0 )
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
  leg_comp->AddEntry(hbase,"base","p");
  leg_comp->AddEntry(heval,"eval","p");
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
  hratio->Draw("same ex0p");
  if ( cline) delete cline;
  cline = new TLine(xmin,1,xmax,1);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  TF1* fun = new TF1("fun","pol0",xmin,xmax);
  fun->SetParameter(0,1.0);
  hratio->Fit(fun,"","",fmax,fmin);
  TLegend* leg_ratio = new TLegend(0.18,0.80,0.4,0.95);
  leg_ratio->SetTextFont(62);
  leg_ratio->SetTextSize(0.090);
  leg_ratio->SetFillStyle(0);
  leg_ratio->AddEntry(hratio,Form("Sys = %.2f %%", fabs(1.0 - fun->GetParameter(0)) * 100.0),"p");
  leg_ratio->Draw();
  ccomp->Print(Form("Systematics/sys_%s.png",handle));
  ccomp->Print(Form("Systematics/sys_%s.pdf",handle));
  delete cline;
  delete ccomp;
  delete empty_ratio;
  delete empty_comp;
  delete leg_ratio;
  delete leg_comp;

}

