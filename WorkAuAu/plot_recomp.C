void plot_recomp(TProfile* tp1f_eit, TProfile* tp1f_six, TProfile* tp1f_for, TProfile* tp1f_two, int rebin, const char* handle)
{

  bool iscent = false;
  bool isntrk = false;
  if ( strcmp(handle,"cent") == 0 ) iscent = true;
  if ( strcmp(handle,"strk") == 0 ) isntrk = true;
  bool isamptntrk = false;
  if ( strcmp(handle,"amptstrk") == 0 ) { isamptntrk = true; isntrk = true; }
  bool islowzoom = false;
  if ( strcmp(handle,"lowstrkzoom") == 0 ) { islowzoom = true; isntrk = true; }


  // --- note to self, I should change get_cumulants to also pass the component histograms
  // --- that way, there's no duplication of the calculation part at all,
  // --- and it keeps the rest of the code short and clean

  tp1f_eit->Rebin(rebin);
  tp1f_six->Rebin(rebin);
  tp1f_for->Rebin(rebin);
  tp1f_two->Rebin(rebin);

  TH1D* th1d_eit = tp1f_eit->ProjectionX(Form("th1d_eit_%s",handle)); // <8>
  TH1D* th1d_six = tp1f_six->ProjectionX(Form("th1d_six_%s",handle)); // <6>
  TH1D* th1d_for = tp1f_for->ProjectionX(Form("th1d_for_%s",handle)); // <4>
  TH1D* th1d_two = tp1f_two->ProjectionX(Form("th1d_two_%s",handle)); // <2>

  TH1D* th1d_862 = (TH1D*)th1d_six->Clone(Form("th1d_846_%s",handle)); // 16<6><2>     (for the 8p)
  TH1D* th1d_842 = (TH1D*)th1d_for->Clone(Form("th1d_842_%s",handle)); // 18<4>^2      (for the 8p)
  TH1D* th1d_822 = (TH1D*)th1d_for->Clone(Form("th1d_822_%s",handle)); // 144<4><2>^2  (for the 8p)
  TH1D* th1d_824 = (TH1D*)th1d_two->Clone(Form("th1d_824_%s",handle)); // 144<2>^4     (for the 8p)
  TH1D* th1d_942 = (TH1D*)th1d_for->Clone(Form("th1d_942_%s",handle)); // 9<4><2>      (for the 6p)
  TH1D* th1d_123 = (TH1D*)th1d_two->Clone(Form("th1d_123_%s",handle)); // 12<2>^3      (for the 6p)
  TH1D* th1d_222 = (TH1D*)th1d_two->Clone(Form("th1d_222_%s",handle)); // 2<2>^2       (for the 4p)

  // --- 8p pieces
  th1d_862->Multiply(th1d_two);
  th1d_862->Scale(16);
  th1d_842->Multiply(th1d_for);
  th1d_842->Scale(18);
  th1d_822->Multiply(th1d_two);
  th1d_822->Multiply(th1d_two);
  th1d_822->Scale(144);
  th1d_824->Multiply(th1d_two);
  th1d_824->Multiply(th1d_two);
  th1d_824->Multiply(th1d_two);
  th1d_824->Scale(144);
  // --- 6p pieces
  th1d_942->Multiply(th1d_two);
  th1d_942->Scale(9);
  th1d_123->Multiply(th1d_two);
  th1d_123->Multiply(th1d_two);
  th1d_123->Scale(12);
  // --- 4p pieces
  th1d_222->Multiply(th1d_two);
  th1d_222->Scale(2);

  TH1D* th1d_c28 = (TH1D*)th1d_eit->Clone("th1d_c28"); // c2{8} = <8> - 16<6><2> -18<4>^2 + 144<4><2>^2 -144<2>^4
  th1d_c28->Add(th1d_862,-1);
  th1d_c28->Add(th1d_842,-1);
  th1d_c28->Add(th1d_822,1);
  th1d_c28->Add(th1d_824,-1);

  TH1D* th1d_c26 = (TH1D*)th1d_six->Clone("th1d_c26"); // c2{6} = <6> - 9<4><2> + 12<2>^3
  th1d_c26->Add(th1d_942,-1);
  th1d_c26->Add(th1d_123,1);

  TH1D* th1d_c24 = (TH1D*)th1d_for->Clone("th1d_c24"); // c2{4} = <4> - 2<2>^2
  th1d_c24->Add(th1d_222,-1);

  TH1D* th1d_c22 = (TH1D*)th1d_two->Clone("th1d_c22"); // c2{2} = <2>

  TH1D* th1d_v28 = (TH1D*)th1d_c28->Clone("th1d_v28");
  TH1D* th1d_v26 = (TH1D*)th1d_c26->Clone("th1d_v26");
  TH1D* th1d_v24 = (TH1D*)th1d_c24->Clone("th1d_v24");
  TH1D* th1d_v22 = (TH1D*)th1d_c24->Clone("th1d_v22");


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
  TPad* pcomp6 = new TPad("pcomp6", "comp6", 0, 0.45, 1, 1);
  pcomp6->SetMargin(Lmarg, Rmarg, 0, 0.1);
  pcomp6->SetTicks(1, 1);
  pcomp6->Draw();

  ccomp6->cd();
  TPad* pcumu6 = new TPad("pcumu6", "cumu6", 0, 0, 1, 0.45);
  pcumu6->SetMargin(Lmarg, Rmarg, 0.22, 0);
  pcumu6->SetTicks(1, 1);
  pcumu6->Draw();

  //-- plot
  pcomp6->cd();
  ymin = -1e-7;
  ymax = 1e-5;
  TH2D* empty_comp6 = new TH2D("empty_comp6","",1,xmin,xmax,1,ymin,ymax);
  empty_comp6->Draw();
  empty_comp6->GetXaxis()->SetLabelSize(0.0);
  empty_comp6->GetXaxis()->SetTitleSize(0.0);
  empty_comp6->GetYaxis()->SetLabelFont(62);
  empty_comp6->GetYaxis()->SetTitleFont(62);
  empty_comp6->GetYaxis()->SetLabelSize(0.065);
  empty_comp6->GetYaxis()->SetTitleSize(0.065);
  empty_comp6->GetYaxis()->SetTitle("components");
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
  TLegend* leg_comp6 = new TLegend(0.18,0.70,0.4,0.85);
  leg_comp6->SetTextSize(0.06);
  leg_comp6->SetFillStyle(0);
  leg_comp6->AddEntry(th1d_123,"12#LT#LT2#GT#GT^{3}","p");
  leg_comp6->AddEntry(th1d_942,"9#LT#LT4#GT#GT#LT#LT2#GT#GT","p");
  leg_comp6->AddEntry(th1d_six,"#LT#LT6#GT#GT","p");
  leg_comp6->Draw();

  //-- ratio
  pcumu6->cd();
  ymin = -2e-6;
  ymax = 2e-6;
  TH2D* empty_cumu6 = new TH2D("empty_cumu6","",1,xmin,xmax,1,ymin,ymax);
  empty_cumu6->Draw();
  if ( iscent ) empty_cumu6->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty_cumu6->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty_cumu6->GetXaxis()->SetLabelFont(62);
  empty_cumu6->GetXaxis()->SetTitleFont(62);
  empty_cumu6->GetXaxis()->SetLabelSize(0.077);
  empty_cumu6->GetXaxis()->SetTitleSize(0.077);
  empty_cumu6->GetYaxis()->SetLabelFont(62);
  empty_cumu6->GetYaxis()->SetTitleFont(62);
  empty_cumu6->GetYaxis()->SetLabelSize(0.077);
  empty_cumu6->GetYaxis()->SetTitleSize(0.077);
  empty_cumu6->GetYaxis()->SetTitle("cumulant");
  th1d_c26->SetMarkerStyle(kOpenCircle);
  th1d_c26->SetLineColor(kBlack);
  th1d_c26->Draw("same ex0p");
  TLegend* leg_cumu6 = new TLegend(0.18,0.80,0.4,0.95);
  leg_cumu6->SetTextSize(0.07);
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
  TPad* pcomp8 = new TPad("pcomp8", "comp8", 0, 0.45, 1, 1);
  pcomp8->SetMargin(Lmarg, Rmarg, 0, 0.1);
  pcomp8->SetTicks(1, 1);
  pcomp8->Draw();

  ccomp8->cd();
  TPad* pcumu8 = new TPad("pcumu8", "cumu8", 0, 0, 1, 0.45);
  pcumu8->SetMargin(Lmarg, Rmarg, 0.22, 0);
  pcumu8->SetTicks(1, 1);
  pcumu8->Draw();

  //-- plot
  pcomp8->cd();
  ymin = -1e-7;
  ymax = 1e-5;
  TH2D* empty_comp8 = new TH2D("empty_comp8","",1,xmin,xmax,1,ymin,ymax);
  empty_comp8->Draw();
  empty_comp8->GetXaxis()->SetLabelSize(0.0);
  empty_comp8->GetXaxis()->SetTitleSize(0.0);
  empty_comp8->GetYaxis()->SetLabelFont(62);
  empty_comp8->GetYaxis()->SetTitleFont(62);
  empty_comp8->GetYaxis()->SetLabelSize(0.065);
  empty_comp8->GetYaxis()->SetTitleSize(0.065);
  empty_comp8->GetYaxis()->SetTitle("components");
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
  TLegend* leg_comp8 = new TLegend(0.18,0.70,0.4,0.85);
  leg_comp8->SetTextSize(0.06);
  leg_comp8->SetFillStyle(0);
  leg_comp8->AddEntry(th1d_824,"144#LT#LT2#GT#GT^{4}","p");
  leg_comp8->AddEntry(th1d_822,"144#LT#LT4#GT#GT#LT#LT2#GT#GT^{4}","p");
  leg_comp8->AddEntry(th1d_842,"18#LT#LT4#GT#GT^{2}","p");
  leg_comp8->AddEntry(th1d_862,"16#LT#LT6#GT#GT#LT#LT2#GT#GT","p");
  leg_comp8->AddEntry(th1d_eit,"#LT#LT8#GT#GT","p");
  leg_comp8->Draw();

  //-- ratio
  pcumu8->cd();
  ymin = -2e-6;
  ymax = 2e-6;
  TH2D* empty_cumu8 = new TH2D("empty_cumu8","",1,xmin,xmax,1,ymin,ymax);
  empty_cumu8->Draw();
  if ( iscent ) empty_cumu8->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty_cumu8->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty_cumu8->GetXaxis()->SetLabelFont(62);
  empty_cumu8->GetXaxis()->SetTitleFont(62);
  empty_cumu8->GetXaxis()->SetLabelSize(0.077);
  empty_cumu8->GetXaxis()->SetTitleSize(0.077);
  empty_cumu8->GetYaxis()->SetLabelFont(62);
  empty_cumu8->GetYaxis()->SetTitleFont(62);
  empty_cumu8->GetYaxis()->SetLabelSize(0.077);
  empty_cumu8->GetYaxis()->SetTitleSize(0.077);
  empty_cumu8->GetYaxis()->SetTitle("cumulant");
  th1d_c28->SetMarkerStyle(kOpenCircle);
  th1d_c28->SetLineColor(kBlack);
  th1d_c28->Draw("same ex0p");
  TLegend* leg_cumu8 = new TLegend(0.18,0.80,0.4,0.95);
  leg_cumu8->SetTextSize(0.07);
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

