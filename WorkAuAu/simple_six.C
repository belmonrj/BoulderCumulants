void do_simple_six(TProfile*, TProfile*, TProfile*, int, const char*);


void simple_six()
{

  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");

  int rebin = 1;

  const char* handle = "cent";

  TProfile* tp1f_six = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c26");
  TProfile* tp1f_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c22");

  do_simple_six(tp1f_six,tp1f_for,tp1f_two,rebin,handle);

  // ------------------------------------------------------------------------

  rebin = 10;

  const char* handle2 = "strk";

  tp1f_six = (TProfile*)fin->Get("nfvtxt_os_fvtxc_tracks_c26");
  tp1f_for = (TProfile*)fin->Get("nfvtxt_os_fvtxc_tracks_c24");
  tp1f_two = (TProfile*)fin->Get("nfvtxt_os_fvtxc_tracks_c22");

  do_simple_six(tp1f_six,tp1f_for,tp1f_two,rebin,handle2);

}


void do_simple_six(TProfile* tp1f_six, TProfile* tp1f_for, TProfile* tp1f_two, int rebin, const char* handle)
{

  //  TCanvas* c1 = new TCanvas("c1","");

  bool iscent = false;
  bool isntrk = false;
  if ( strcmp(handle,"cent") == 0 ) iscent = true;
  if ( strcmp(handle,"strk") == 0 ) isntrk = true;

  tp1f_six->Rebin(rebin);
  tp1f_for->Rebin(rebin);
  tp1f_two->Rebin(rebin);

  TH1D* th1d_six = tp1f_six->ProjectionX(Form("th1d_six_%s")); // <6>
  TH1D* th1d_for = tp1f_for->ProjectionX(Form("th1d_for_%s")); // <4>
  TH1D* th1d_two = tp1f_two->ProjectionX(Form("th1d_two_%s")); // <2>

  TH1D* th1d_942 = (TH1D*)th1d_for->Clone(Form("th1d_942_%s")); // 9<4><2>
  TH1D* th1d_123 = (TH1D*)th1d_two->Clone(Form("th1d_123_%s")); // 12<2>^3
  TH1D* th1d_222 = (TH1D*)th1d_two->Clone(Form("th1d_222_%s")); // 2<2>^2

  th1d_942->Multiply(th1d_two);
  th1d_942->Scale(9);
  th1d_123->Multiply(th1d_two);
  th1d_123->Multiply(th1d_two);
  th1d_123->Scale(12);
  th1d_222->Multiply(th1d_two);
  th1d_222->Scale(2);

  TH1D* th1d_c26 = (TH1D*)th1d_six->Clone("th1d_c26"); // c2{6} = <6> - 9<4><2> + 12<2>^3
  th1d_c26->Add(th1d_942,-1);
  th1d_c26->Add(th1d_123,1);

  TH1D* th1d_c24 = (TH1D*)th1d_for->Clone("th1d_c24"); // c2{4} = <4> - 2<2>^2
  th1d_c24->Add(th1d_222,-1);

  TH1D* th1d_c22 = (TH1D*)th1d_two->Clone("th1d_c22"); // c2{2} = <2>

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
                 (1.0/18.0)*esix*esix // fixed a typo here
                 ); // correct formula excluding covariance terms, looks like over-estimate
          //ev26 = v26*(esix/six); // brutally simplistic, but *looks* right
        }
      th1d_v26->SetBinContent(i+1,v26);
      th1d_v26->SetBinError(i+1,ev26);
    }

  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = -1e-4;
  double ymax = 1e-4;
  if ( iscent ) xmax = 100.0;
  if ( isntrk ) xmax = 600.0;

  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("components");
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
  TLegend* leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_six,"#LT#LT6#GT#GT","p");
  leg->AddEntry(th1d_942,"9#LT#LT4#GT#GT#LT#LT2#GT#GT","p");
  leg->AddEntry(th1d_123,"12#LT#LT2#GT#GT^{3}","p");
  leg->Draw();
  c1->Print(Form("FigsSix/sixparticle_%s_components_blah.png",handle));
  c1->Print(Form("FigsSix/sixparticle_%s_components_blah.pdf",handle));



  ymin = -1e-6;
  ymax = 3e-6;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("components");
  th1d_six->Draw("same ex0p");
  th1d_942->Draw("same ex0p");
  th1d_123->Draw("same ex0p");
  leg->Draw();
  c1->Print(Form("FigsSix/sixparticle_%s_components_zoom_blah.png",handle));
  c1->Print(Form("FigsSix/sixparticle_%s_components_zoom_blah.pdf",handle));



  ymin = -1e-6;
  ymax = 3e-6;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("cumulant");
  th1d_c26->SetMarkerStyle(kOpenCircle);
  th1d_c26->SetLineColor(kBlack);
  th1d_c26->Draw("same ex0p");
  if ( leg ) delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_c26,"c_{2}{6} = 4v_{2}^{6}","p");
  leg->Draw();
  TLine *cline = new TLine(xmin,0,xmax,0);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  c1->Print(Form("FigsSix/sixparticle_%s_cumulant_blah.png",handle));
  c1->Print(Form("FigsSix/sixparticle_%s_cumulant_blah.pdf",handle));



  ymin = -2e-5;
  ymax = 2e-5;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("cumulant");
  th1d_c24->SetMarkerStyle(kOpenCircle);
  th1d_c24->SetLineColor(kBlack);
  th1d_c24->Draw("same ex0p");
  if ( leg ) delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_c24,"c_{2}{4} = -v_{2}^{4}","p");
  leg->Draw();
  cline->Draw();
  c1->Print(Form("FigsSix/sixparticle_%s_cumulant4_blah.png",handle));
  c1->Print(Form("FigsSix/sixparticle_%s_cumulant4_blah.pdf",handle));



  ymin = 0.0;
  ymax = 0.12;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
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
  if ( leg ) delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_v26,"v_{2}{6}","p");
  leg->Draw();
  c1->Print(Form("FigsSix/sixparticle_%s_v2_blah.png",handle));
  c1->Print(Form("FigsSix/sixparticle_%s_v2_blah.pdf",handle));
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
  c1->Print(Form("FigsSix/sixparticle_%s_v2642_blah.png",handle));
  c1->Print(Form("FigsSix/sixparticle_%s_v2642_blah.pdf",handle));

  if ( empty ) delete empty;
  //  if ( c1 ) delete c1;

}
