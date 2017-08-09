void doit(TProfile*, TProfile*, TProfile*, TProfile*, int, const char*);


void get_recursion()
{

  // ------------------------------------------------------------------------

  //TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");
  TFile* fin = TFile::Open("input/histos_11609.root");

  int rebin = 1;

  const char* handle = "cent";

  TProfile* tp1f_eit = (TProfile*)fin->Get("centrality_recursion_0_6");
  TProfile* tp1f_six = (TProfile*)fin->Get("centrality_recursion_0_4");
  TProfile* tp1f_for = (TProfile*)fin->Get("centrality_recursion_0_2");
  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_recursion_0_0");

  doit(tp1f_eit,tp1f_six,tp1f_for,tp1f_two,rebin,handle);


  // ------------------------------------------------------------------------

  cout << "All done. Have a nice day!" << endl;

}


void doit(TProfile* tp1f_eit, TProfile* tp1f_six, TProfile* tp1f_for, TProfile* tp1f_two, int rebin, const char* handle)
{

  TCanvas* c1 = new TCanvas("c1","");

  bool iscent = false;
  bool isntrk = false;
  if ( strcmp(handle,"cent") == 0 ) iscent = true;
  if ( strcmp(handle,"strk") == 0 ) isntrk = true;
  bool isamptntrk = false;
  if ( strcmp(handle,"amptstrk") == 0 ) { isamptntrk = true; isntrk = true; }
  bool islowzoom = false;
  if ( strcmp(handle,"lowstrkzoom") == 0 ) { islowzoom = true; isntrk = true; }



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

  int nbins = th1d_c26->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      // --- 2-particle
      double c22 = th1d_c22->GetBinContent(i+1);
      double v22 = -9999;
      double ev22 = 0;
      double two = th1d_two->GetBinContent(i+1);
      double etwo = th1d_two->GetBinError(i+1);
      if ( c22 > 0 )
        {
          v22 = sqrt(c22); // v2{2} = c2{2}^{(1/2)}
          ev22 = (1.0/v22)*etwo; // correct formula
        }
      th1d_v22->SetBinContent(i+1,v22);
      th1d_v22->SetBinError(i+1,ev22);
      // --- 4-particle
      double c24 = th1d_c24->GetBinContent(i+1);
      double v24 = -9999;
      double four = th1d_for->GetBinContent(i+1);
      double efour = th1d_for->GetBinError(i+1);
      double ev24 = 0;
      if ( c24 < 0 && four != 0 )
        {
          v24 = pow(-c24,(1.0/4.0)); // v2{4} = -c2{4}^{(1/4)}
          ev24 = (1.0/pow(-c24,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
        }
      th1d_v24->SetBinContent(i+1,v24);
      th1d_v24->SetBinError(i+1,ev24);
      // --- 6-particle
      double c26 = th1d_c26->GetBinContent(i+1);
      double v26 = -9999;
      double ev26 = 0;
      double six = th1d_six->GetBinContent(i+1);
      double esix = th1d_six->GetBinError(i+1);
      if ( c26 > 0 && six != 0 )
        {
          v26 = pow((0.25*c26),(1.0/6.0)); // v2{6} = (c2{6}/4)^{(1/6)}
          ev26 = (1.0/pow(2*c26,(5.0/6.0))) *
            sqrt(
                 (4.5*(4*two*two-four)*(4*two*two-four)*etwo*etwo) +
                 (4.5*two*two*efour*efour) +
                 (1.0/18.0)*esix*esix
                 );
        }
      th1d_v26->SetBinContent(i+1,v26);
      th1d_v26->SetBinError(i+1,ev26);
      // --- 8-particle
      double c28 = th1d_c28->GetBinContent(i+1);
      double v28 = -9999;
      double ev28 = 0;
      double eit = th1d_eit->GetBinContent(i+1);
      double eeit = th1d_eit->GetBinError(i+1);
      if ( c28 < 0 && eit != 0 )
        {
          v28 = pow((-c28/33.0),(1.0/8.0)); // v2{8} = (-c2{8}/33)^{(1/8)}
          ev28 = ( 2*pow(33,(1.0/8.0)) / pow(c28,(7.0/8.0)) ) *
            sqrt(
                 ( (36*two*two*two - 18*four*two + six)*(36*two*two*two - 18*four*two + six) * etwo*etwo ) +
                 ( (81.0/16.0)*(4*two*two-four)*(4*two*two-four) * efour*efour ) +
                 ( two*two*esix*esix ) +
                 ( (1.0/256.0)*eeit*eeit )
                 ); // I think this is right but will need to double check when error bar issue on raw histos is resolved
        }
      //cout << "c28 " << c28 << " v28 " << v28 << endl;
      if ( iscent && i > 50 ) v28 = -9999; // don't know why set range user is causing problems below
      th1d_v28->SetBinContent(i+1,v28);
      th1d_v28->SetBinError(i+1,ev28);
    }

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

  // --- now v2 ------------------------------------------------------




  ymin = 0.0;
  ymax = 0.12;
  //if ( empty ) delete empty;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("v_{2}");
  if ( iscent )
  {
  th1d_v22->GetXaxis()->SetRangeUser(0,90);
  th1d_v24->GetXaxis()->SetRangeUser(0,70);
  th1d_v26->GetXaxis()->SetRangeUser(0,70);
  }
  th1d_v26->SetMarkerStyle(kOpenCircle);
  th1d_v26->SetMarkerColor(kBlack);
  th1d_v26->SetLineColor(kBlack);
  th1d_v26->Draw("same ex0p");
  //if ( leg ) delete leg;
  TLegend* leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_v26,"v_{2}{6}","p");
  leg->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v26.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v26.pdf",handle));
  th1d_v24->SetMarkerStyle(kOpenSquare);
  th1d_v24->SetMarkerColor(kBlue);
  th1d_v24->SetLineColor(kBlue);
  th1d_v24->Draw("same ex0p");
  th1d_v22->SetMarkerStyle(kOpenCross);
  th1d_v22->SetMarkerColor(kRed);
  th1d_v22->SetLineColor(kRed);
  th1d_v22->Draw("same ex0p");
  leg->AddEntry(th1d_v24,"v_{2}{4}","p");
  leg->AddEntry(th1d_v22,"v_{2}{2}","p");
  leg->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v2642.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v2642.pdf",handle));

  ymin = 0.0;
  ymax = 0.12;
  if ( empty ) delete empty;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("v_{2}");
  // if ( iscent ) th1d_v28->GetXaxis()->SetRangeUser(0,50); // very hard to understand why this line causes the points to disappear...
  th1d_v28->SetMarkerStyle(kFullDiamond);
  th1d_v28->SetMarkerColor(kGreen+2);
  th1d_v28->SetLineColor(kGreen+2);
  th1d_v28->Draw("same ex0p");
  //if ( leg ) delete leg;
  TLegend* leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_v28,"v_{2}{8}","p");
  leg->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v28.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v28.pdf",handle));
  th1d_v26->Draw("same ex0p");
  th1d_v24->Draw("same ex0p");
  th1d_v22->Draw("same ex0p");
  th1d_v28->Draw("same ex0p");
  leg->AddEntry(th1d_v26,"v_{2}{6}","p");
  leg->AddEntry(th1d_v24,"v_{2}{4}","p");
  leg->AddEntry(th1d_v22,"v_{2}{2}","p");
  leg->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v28642.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v28642.pdf",handle));

  if ( empty ) delete empty;
  if ( c1 ) delete c1;

}

