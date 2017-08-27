void plot_subcomp(
                 const char* handle
                 )
{

  bool iscent = false;
  bool isntrk = false;
  if ( strcmp(handle,"cent") == 0 ) iscent = true;
  if ( strcmp(handle,"ntrk") == 0 ) isntrk = true;
  bool isamptntrk = false;
  if ( strcmp(handle,"amptntrk") == 0 ) { isamptntrk = true; isntrk = true; }
  bool islowzoom = false;
  if ( strcmp(handle,"lowntrkzoom") == 0 ) { islowzoom = true; isntrk = true; }




  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = -1e-4;
  double ymax = 1e-4;
  if ( iscent ) xmax = 100.0;
  if ( isntrk && !islowzoom ) xmax = 650.0;



  // --- four particle components and cumulants

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
  th1d_222->SetMarkerStyle(kOpenCircle);
  th1d_222->SetMarkerColor(kRed);
  th1d_222->SetLineColor(kBlack);
  th1d_222->Draw("same ex0p");
  th1d_for->SetMarkerStyle(kOpenSquare);
  th1d_for->SetMarkerColor(kBlue);
  th1d_for->SetLineColor(kBlack);
  th1d_for->Draw("same ex0p");
  TLine *cline = new TLine(xmin,0,xmax,0);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  TLegend* leg_comp4 = new TLegend(0.18,0.70,0.4,0.85);
  leg_comp4->SetTextFont(62);
  leg_comp4->SetTextSize(0.075);
  leg_comp4->SetFillStyle(0);
  leg_comp4->AddEntry(th1d_222,"2#LT#LT2#GT#GT^{2}","p");
  leg_comp4->AddEntry(th1d_for,"#LT#LT4#GT#GT","p");
  leg_comp4->Draw();

  //-- ratio
  pcumu4->cd();
  ymin = -1.999e-5;
  ymax = 1.999e-5;
  TH2D* empty_cumu4 = new TH2D("empty_cumu4","",1,xmin,xmax,1,ymin,ymax);
  empty_cumu4->Draw();
  if ( iscent ) empty_cumu4->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty_cumu4->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
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
  th1d_c24->SetMarkerStyle(kOpenCircle);
  th1d_c24->SetLineColor(kBlack);
  th1d_c24->Draw("same ex0p");
  TLegend* leg_cumu4 = new TLegend(0.18,0.80,0.4,0.95);
  leg_cumu4->SetTextFont(62);
  leg_cumu4->SetTextSize(0.090);
  leg_cumu4->SetFillStyle(0);
  leg_cumu4->AddEntry(th1d_c24,"c_{2}{4} = -v_{2}^{4}","p");
  leg_cumu4->Draw();
  cline->Draw();
  ccomp4->Print(Form("FigsSubevents/subevents_%s_cumulant4.png",handle));
  ccomp4->Print(Form("FigsSubevents/subevents_%s_cumulant4.pdf",handle));
  delete ccomp4;
  delete empty_cumu4;
  delete empty_comp4;
  delete leg_cumu4;
  delete leg_comp4;

}

