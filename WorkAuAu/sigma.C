void do_sigma(TProfile*, TProfile*, TProfile*, int, const char*);


void sigma()
{

  // ------------------------------------------------------------------------

  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");

  int rebin = 1;

  const char* handle = "cent";

  TProfile* tp1f_gap = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c22");
  TProfile* tp1f_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c22");

  do_simple_gap(tp1f_gap,tp1f_for,tp1f_two,rebin,handle);

  return;

  // ------------------------------------------------------------------------

  rebin = 2;

  const char* handle2s = "lowstrkzoom";

  tp1f_gap = (TProfile*)fin->Get("nfvtxt_os_fvtxsfvtxn_tracks_c22");
  tp1f_for = (TProfile*)fin->Get("nfvtxt_os_fvtxc_tracks_c24");
  tp1f_two = (TProfile*)fin->Get("nfvtxt_os_fvtxc_tracks_c22");

  do_simple_gap(tp1f_gap,tp1f_for,tp1f_two,rebin,handle2s);

  // ------------------------------------------------------------------------

  rebin = 5;

  const char* handle2 = "strk";

  tp1f_gap = (TProfile*)fin->Get("nfvtxt_os_fvtxsfvtxn_tracks_c22");
  tp1f_for = (TProfile*)fin->Get("nfvtxt_os_fvtxc_tracks_c24");
  tp1f_two = (TProfile*)fin->Get("nfvtxt_os_fvtxc_tracks_c22");

  do_simple_gap(tp1f_gap,tp1f_for,tp1f_two,rebin,handle2);

  // ------------------------------------------------------------------------

  gROOT->ProcessLine("gErrorIgnoreLevel = 2002;");
  TFile* fin = TFile::Open("input/cumulants_ampt_auau200_1.root");
  gROOT->ProcessLine("gErrorIgnoreLevel = 0;");
  //cout << fin << endl;

  rebin = 10;

  const char* handle3 = "amptstrk";

  tp1f_gap = (TProfile*)fin->Get("raa6_Ncharge");
  tp1f_for = (TProfile*)fin->Get("raa4_Ncharge");
  tp1f_two = (TProfile*)fin->Get("raa2_Ncharge");

  do_simple_gap(tp1f_gap,tp1f_for,tp1f_two,rebin,handle3);

  // ------------------------------------------------------------------------

  cout << "All done. Have a nice day!" << endl;

}


void do_simple_gap(TProfile* tp1f_gap, TProfile* tp1f_for, TProfile* tp1f_two, int rebin, const char* handle)
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



  tp1f_gap->Rebin(rebin);
  tp1f_for->Rebin(rebin);
  tp1f_two->Rebin(rebin);

  TH1D* th1d_gap = tp1f_gap->ProjectionX(Form("th1d_gap_%s",handle)); // <6>
  TH1D* th1d_for = tp1f_for->ProjectionX(Form("th1d_for_%s",handle)); // <4>
  TH1D* th1d_two = tp1f_two->ProjectionX(Form("th1d_two_%s",handle)); // <2>
  TH1D* th1d_222 = (TH1D*)th1d_two->Clone(Form("th1d_222_%s",handle)); // 2<2>^2
  th1d_222->Multiply(th1d_two);
  th1d_222->Scale(2);
  TH1D* th1d_c24 = (TH1D*)th1d_for->Clone("th1d_c24"); // c2{4} = <4> - 2<2>^2
  th1d_c24->Add(th1d_222,-1);
  TH1D* th1d_c22 = (TH1D*)th1d_two->Clone("th1d_c22"); // c2{2} = <2>
  TH1D* th1d_c2G = (TH1D*)th1d_gap->Clone("th1d_gap"); // c2{2} = <2>
  TH1D* th1d_v24 = (TH1D*)th1d_c24->Clone("th1d_v24");
  TH1D* th1d_v22 = (TH1D*)th1d_c22->Clone("th1d_v22");
  TH1D* th1d_v2G = (TH1D*)th1d_c2G->Clone("th1d_v2G");
  TH1D* th1d_SVV = (TH1D*)th1d_c24->Clone("th1d_SVV");
  TH1D* th1d_SVG = (TH1D*)th1d_c24->Clone("th1d_SVG");

  int nbins = th1d_gap->GetNbinsX();
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
      // --- 2-particle
      double c2G = th1d_c2G->GetBinContent(i+1);
      double v2G = -9999;
      double ev2G = 0;
      double twog = th1d_two->GetBinContent(i+1);
      double etwog = th1d_two->GetBinError(i+1);
      if ( c2G > 0 )
        {
          v2G = sqrt(c2G); // v2{2} = c2{2}^{(1/2)}
          ev2G = (1.0/v2G)*etwog; // correct formula
        }
      th1d_v2G->SetBinContent(i+1,v2G);
      th1d_v2G->SetBinError(i+1,ev2G);
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
      // --- sigma_v/v
      double numerator1 = -9999;
      double denominat1 = -9999;
      double sigmavv1 = -9999;
      double esigmavv1 = 0;
      if ( v22 > 0 && v24 > 0 )
        {
          numerator1 = v22*v22 - v24*v24;
          denominat1 = v22*v22 + v24*v24;
          sigmavv1 = numerator1/denominat1;
          // -----------------------
          cout << sigmavv1 << endl;
          sigmavv1 = sqrt(sigmavv1);
          cout << sigmavv1 << endl;
          // -----------------------
          esigmavv1 = sigmavv1*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) ); // quick and dirty guess, need to check
        }
      th1d_SVV->SetBinContent(i+1,sigmavv1);
      th1d_SVV->SetBinError(i+1,esigmavv1);
      // --- sigma_v/v
      double numerator2 = -9999;
      double denominat2 = -9999;
      double sigmavv2 = -9999;
      double esigmavv2 = 0;
      if ( v22 > 0 && v24 > 0 )
        {
          numerator2 = v2G*v2G - v24*v24;
          denominat2 = v2G*v2G + v24*v24;
          sigmavv2 = numerator2/denominat2;
          // -----------------------
          cout << sigmavv2 << endl;
          sigmavv2 = sqrt(sigmavv2);
          cout << sigmavv2 << endl;
          // -----------------------
          esigmavv2 = sigmavv2*sqrt( pow(ev22/v22,2.0) + pow(ev24/v24,2.0) ); // quick and dirty guess, need to check
        }
      th1d_SVG->SetBinContent(i+1,sigmavv2);
      th1d_SVG->SetBinError(i+1,esigmavv2);
    }

  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = 0.0;
  double ymax = 1.2;
  if ( iscent ) xmax = 100.0;
  if ( isntrk && !islowzoom ) xmax = 650.0;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("#sigma_{v_{2}}/v_{2}");
  th1d_SVV->SetMarkerStyle(kOpenCircle);
  th1d_SVV->SetMarkerColor(kBlack);
  th1d_SVV->SetLineColor(kBlack);
  th1d_SVG->SetMarkerStyle(kOpenSquare);
  th1d_SVG->SetMarkerColor(kBlack);
  th1d_SVG->SetLineColor(kBlack);
  th1d_SVV->Draw("same ex0p");
  th1d_SVG->Draw("same ex0p");
  c1->Print(Form("FigsSigma/sigma_%s_x01.png",handle));
  c1->Print(Form("FigsSigma/sigma_%s_x01.pdf",handle));


}

