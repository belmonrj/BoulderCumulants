void plot_recomp(TProfile*, TProfile*, TProfile*, TProfile*, int, const char*);
void plot_recomp(TH1D*, TH1D*, TH1D*, TH1D*,
                 TH1D*, TH1D*, TH1D*, TH1D*,
                 TH1D*, TH1D*, TH1D*, TH1D*,
                 TH1D*, TH1D*, TH1D*,
                 const char*
                 );


void plot_recomp(TProfile* tp1f_eit, TProfile* tp1f_six, TProfile* tp1f_for, TProfile* tp1f_two, int rebin, const char* handle)
{
  cout << "Using hidden method!" << endl;
  // --- initialize the pointers
  TH1D* v28 = NULL;
  TH1D* v26 = NULL;
  TH1D* v24 = NULL;
  TH1D* v22 = NULL;
  TH1D* c28 = NULL;
  TH1D* c26 = NULL;
  TH1D* c24 = NULL;
  TH1D* c22 = NULL;
  TH1D* heit = NULL;
  TH1D* hsix = NULL;
  TH1D* hfor = NULL;
  TH1D* htwo = NULL;
  TH1D* h862 = NULL;
  TH1D* h842 = NULL;
  TH1D* h822 = NULL;
  TH1D* h824 = NULL;
  TH1D* h942 = NULL;
  TH1D* h123 = NULL;
  TH1D* h222 = NULL;
  // --- get all the v2{k}, c2{k}, and component histograms
  get_cumulants(tp1f_eit, tp1f_six, tp1f_for, tp1f_two,
                &v28,  &v26,  &v24,  &v22,
                &c28,  &c26,  &c24,  &c22,
                &heit, &hsix, &hfor, &htwo,
                &h862, &h842, &h822, &h824,
                &h942, &h123, &h222,
                rebin);
  // --- plot the components and cumulants
  plot_recomp(c28,  c26,  c24,  c22,
              heit, hsix, hfor, htwo,
              h862, h842, h822, h824,
              h942, h123, h222,
              handle);
}


void plot_recomp(TH1D* th1d_c28, TH1D* th1d_c26, TH1D* th1d_c24, TH1D* th1d_c22,
                 TH1D* th1d_eit, TH1D* th1d_six, TH1D* th1d_for, TH1D* th1d_two,
                 TH1D* th1d_862, TH1D* th1d_842, TH1D* th1d_822, TH1D* th1d_824,
                 TH1D* th1d_942, TH1D* th1d_123, TH1D* th1d_222,
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
  TLegend* leg_comp4 = new TLegend(0.165,0.70,0.4,0.85);
  leg_comp4->SetTextFont(62);
  leg_comp4->SetTextSize(0.08);
  leg_comp4->SetFillStyle(0);
  leg_comp4->AddEntry(th1d_222,"2#LT#LT2#GT#GT^{2}","p");
  leg_comp4->AddEntry(th1d_for,"#LT#LT4#GT#GT","p");
  leg_comp4->Draw();

  //-- ratio
  pcumu4->cd();
  ymin = -1.5e-5;
  ymax = 1.5e-5;
  TH2D* empty_cumu4 = new TH2D("empty_cumu4","",1,xmin,xmax,1,ymin,ymax);
  empty_cumu4->Draw();
  if ( iscent ) empty_cumu4->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty_cumu4->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
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
  th1d_c24->SetMarkerStyle(kOpenCircle);
  th1d_c24->SetLineColor(kBlack);
  th1d_c24->Draw("same ex0p");
  TLegend* leg_cumu4 = new TLegend(0.165,0.87,0.4,0.97);
  leg_cumu4->SetTextFont(62);
  leg_cumu4->SetTextSize(0.08);
  leg_cumu4->SetFillStyle(0);
  leg_cumu4->AddEntry(th1d_c24,"c_{2}{4} = -v_{2}^{4}","p");
  leg_cumu4->Draw();
  cline->Draw();
  ccomp4->Print(Form("FigsRecursion/recursion_%s_cumulant4.png",handle));
  ccomp4->Print(Form("FigsRecursion/recursion_%s_cumulant4.pdf",handle));
  delete ccomp4;
  delete empty_cumu4;
  delete empty_comp4;
  delete leg_cumu4;
  delete leg_comp4;

  // --- six particle components and cumulants

  TCanvas* ccomp6 = new TCanvas("ccomp6", "", w, h);
  ccomp6->SetMargin(0, 0, 0, 0);

  ccomp6->cd();
  TPad* pcomp6 = new TPad("pcomp6", "comp6", 0, 0.5, 1, 1);
  pcomp6->SetMargin(Lmarg, Rmarg, 0, 0.1);
  pcomp6->SetTicks(1, 1);
  pcomp6->Draw();

  ccomp6->cd();
  TPad* pcumu6 = new TPad("pcumu6", "cumu6", 0, 0, 1, 0.5);
  pcumu6->SetMargin(Lmarg, Rmarg, 0.22, 0);
  pcumu6->SetTicks(1, 1);
  pcumu6->Draw();

  //-- plot
  pcomp6->cd();
  ymin = -3e-7;
  ymax = 3e-6;
  TH2D* empty_comp6 = new TH2D("empty_comp6","",1,xmin,xmax,1,ymin,ymax);
  empty_comp6->Draw();
  empty_comp6->GetXaxis()->SetLabelSize(0.0);
  empty_comp6->GetXaxis()->SetTitleSize(0.0);
  empty_comp6->GetYaxis()->SetLabelFont(62);
  empty_comp6->GetYaxis()->SetTitleFont(62);
  empty_comp6->GetYaxis()->SetLabelSize(0.08);
  empty_comp6->GetYaxis()->SetTitleSize(0.08);
  empty_comp6->GetYaxis()->SetTitle("components");
  empty_comp6->GetYaxis()->SetTitleOffset(0.9);
  th1d_six->SetMarkerStyle(kOpenCircle);
  th1d_942->SetMarkerStyle(kOpenSquare);
  th1d_123->SetMarkerStyle(kOpenCross);
  th1d_six->SetMarkerColor(kBlack);
  th1d_942->SetMarkerColor(kBlue);
  th1d_123->SetMarkerColor(kRed);
  th1d_six->SetLineColor(kBlack);
  th1d_942->SetLineColor(kBlue);
  th1d_123->SetLineColor(kRed);
  th1d_six->Draw("same ex0p");
  th1d_942->Draw("same ex0p");
  th1d_123->Draw("same ex0p");
  cline->Draw();
  TLegend* leg_comp6 = new TLegend(0.165,0.62,0.4,0.85);
  leg_comp6->SetTextFont(62);
  leg_comp6->SetTextSize(0.08);
  leg_comp6->SetFillStyle(0);
  leg_comp6->AddEntry(th1d_123,"12#LT#LT2#GT#GT^{3}","p");
  leg_comp6->AddEntry(th1d_942,"9#LT#LT4#GT#GT#LT#LT2#GT#GT","p");
  leg_comp6->AddEntry(th1d_six,"#LT#LT6#GT#GT","p");
  leg_comp6->Draw();

  //-- ratio
  pcumu6->cd();
  ymin = -2e-7;
  ymax = 2e-7;
  TH2D* empty_cumu6 = new TH2D("empty_cumu6","",1,xmin,xmax,1,ymin,ymax);
  empty_cumu6->Draw();
  if ( iscent ) empty_cumu6->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty_cumu6->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty_cumu6->GetXaxis()->SetLabelFont(62);
  empty_cumu6->GetXaxis()->SetTitleFont(62);
  empty_cumu6->GetXaxis()->SetLabelSize(0.08);
  empty_cumu6->GetXaxis()->SetTitleSize(0.08);
  empty_cumu6->GetYaxis()->SetLabelFont(62);
  empty_cumu6->GetYaxis()->SetTitleFont(62);
  empty_cumu6->GetYaxis()->SetLabelSize(0.08);
  empty_cumu6->GetYaxis()->SetTitleSize(0.08);
  empty_cumu6->GetYaxis()->SetTitle("cumulant");
  empty_cumu6->GetYaxis()->SetTitleOffset(0.9);
  th1d_c26->SetMarkerStyle(kOpenCircle);
  th1d_c26->SetLineColor(kBlack);
  th1d_c26->Draw("same ex0p");
  TLegend* leg_cumu6 = new TLegend(0.165,0.87,0.4,0.97);
  leg_cumu6->SetTextFont(62);
  leg_cumu6->SetTextSize(0.08);
  leg_cumu6->SetFillStyle(0);
  leg_cumu6->AddEntry(th1d_c26,"c_{2}{6} = 4v_{2}^{6}","p");
  leg_cumu6->Draw();
  cline->Draw();
  ccomp6->Print(Form("FigsRecursion/recursion_%s_cumulant6.png",handle));
  ccomp6->Print(Form("FigsRecursion/recursion_%s_cumulant6.pdf",handle));
  delete ccomp6;
  delete empty_cumu6;
  delete empty_comp6;
  delete leg_cumu6;
  delete leg_comp6;


  // --- eight particle components and cumulants

  TCanvas* ccomp8 = new TCanvas("ccomp8", "", w, h);
  ccomp8->SetMargin(0, 0, 0, 0);

  ccomp8->cd();
  TPad* pcomp8 = new TPad("pcomp8", "comp8", 0, 0.5, 1, 1);
  pcomp8->SetMargin(Lmarg, Rmarg, 0, 0.1);
  pcomp8->SetTicks(1, 1);
  pcomp8->Draw();

  ccomp8->cd();
  TPad* pcumu8 = new TPad("pcumu8", "cumu8", 0, 0, 1, 0.5);
  pcumu8->SetMargin(Lmarg, Rmarg, 0.22, 0);
  pcumu8->SetTicks(1, 1);
  pcumu8->Draw();

  //-- plot
  pcomp8->cd();
  ymin = -1e-8;
  ymax = 1e-7;
  TH2D* empty_comp8 = new TH2D("empty_comp8","",1,xmin,xmax,1,ymin,ymax);
  empty_comp8->Draw();
  empty_comp8->GetXaxis()->SetLabelSize(0.0);
  empty_comp8->GetXaxis()->SetTitleSize(0.0);
  empty_comp8->GetYaxis()->SetLabelFont(62);
  empty_comp8->GetYaxis()->SetTitleFont(62);
  empty_comp8->GetYaxis()->SetLabelSize(0.08);
  empty_comp8->GetYaxis()->SetTitleSize(0.08);
  empty_comp8->GetYaxis()->SetTitle("components");
  empty_comp8->GetYaxis()->SetTitleOffset(0.9);
  // TH1D* th1d_862 = (TH1D*)th1d_six->Clone(Form("th1d_846_%s",handle)); // 16<6><2>     (for the 8p)
  // TH1D* th1d_842 = (TH1D*)th1d_for->Clone(Form("th1d_842_%s",handle)); // 18<4>^2      (for the 8p)
  // TH1D* th1d_822 = (TH1D*)th1d_for->Clone(Form("th1d_822_%s",handle)); // 144<4><2>^2  (for the 8p)
  // TH1D* th1d_824 = (TH1D*)th1d_two->Clone(Form("th1d_824_%s",handle)); // 144<2>^4     (for the 8p)
  th1d_824->SetMarkerStyle(kOpenCircle);
  th1d_822->SetMarkerStyle(kOpenCircle);
  th1d_842->SetMarkerStyle(kOpenSquare);
  th1d_862->SetMarkerStyle(kOpenCross);
  th1d_eit->SetMarkerStyle(kOpenDiamond);
  th1d_824->SetMarkerColor(kRed);
  th1d_822->SetMarkerColor(kBlue);
  th1d_842->SetMarkerColor(kBlue);
  th1d_862->SetMarkerColor(kBlack);
  th1d_eit->SetMarkerColor(kGreen+2);
  th1d_824->Draw("same ex0p");
  th1d_822->Draw("same ex0p");
  th1d_842->Draw("same ex0p");
  th1d_862->Draw("same ex0p");
  th1d_eit->Draw("same ex0p");
  cline->Draw();
  TLegend* leg_comp8 = new TLegend(0.165,0.47,0.4,0.85);
  leg_comp8->SetTextFont(62);
  leg_comp8->SetTextSize(0.08);
  leg_comp8->SetFillStyle(0);
  leg_comp8->AddEntry(th1d_824,"144#LT#LT2#GT#GT^{4}","p");
  leg_comp8->AddEntry(th1d_822,"144#LT#LT4#GT#GT#LT#LT2#GT#GT^{2}","p");
  leg_comp8->AddEntry(th1d_842,"18#LT#LT4#GT#GT^{2}","p");
  leg_comp8->AddEntry(th1d_862,"16#LT#LT6#GT#GT#LT#LT2#GT#GT","p");
  leg_comp8->AddEntry(th1d_eit,"#LT#LT8#GT#GT","p");
  leg_comp8->Draw();

  //-- ratio
  pcumu8->cd();
  ymin = -5e-9;
  ymax = 5e-9;
  TH2D* empty_cumu8 = new TH2D("empty_cumu8","",1,xmin,xmax,1,ymin,ymax);
  empty_cumu8->Draw();
  if ( iscent ) empty_cumu8->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty_cumu8->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty_cumu8->GetXaxis()->SetLabelFont(62);
  empty_cumu8->GetXaxis()->SetTitleFont(62);
  empty_cumu8->GetXaxis()->SetLabelSize(0.08);
  empty_cumu8->GetXaxis()->SetTitleSize(0.08);
  empty_cumu8->GetYaxis()->SetLabelFont(62);
  empty_cumu8->GetYaxis()->SetTitleFont(62);
  empty_cumu8->GetYaxis()->SetLabelSize(0.08);
  empty_cumu8->GetYaxis()->SetTitleSize(0.08);
  empty_cumu8->GetYaxis()->SetTitle("cumulant");
  empty_cumu8->GetYaxis()->SetTitleOffset(0.9);
  th1d_c28->SetMarkerStyle(kOpenCircle);
  th1d_c28->SetLineColor(kBlack);
  th1d_c28->Draw("same ex0p");
  TLegend* leg_cumu8 = new TLegend(0.165,0.87,0.4,0.97);
  leg_cumu8->SetTextFont(62);
  leg_cumu8->SetTextSize(0.08);
  leg_cumu8->SetFillStyle(0);
  leg_cumu8->AddEntry(th1d_c28,"c_{2}{8} = -33v_{2}^{8}","p");
  leg_cumu8->Draw();
  cline->Draw();
  ccomp8->Print(Form("FigsRecursion/recursion_%s_cumulant8.png",handle));
  ccomp8->Print(Form("FigsRecursion/recursion_%s_cumulant8.pdf",handle));
  delete ccomp8;
  delete empty_cumu8;
  delete empty_comp8;
  delete leg_cumu8;
  delete leg_comp8;

}

