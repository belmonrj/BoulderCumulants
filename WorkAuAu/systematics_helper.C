void crunch(TProfile*, TProfile*, const char*, const char*);
void crunch(TH1D*, TH1D*, const char*, const char*, double, double, double, double);

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
      double err = hratio->GetBinError(i+1);
      if ( cont <= 0.0 || err >= 1.0 )
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

