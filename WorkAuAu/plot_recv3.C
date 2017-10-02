void plot_recv3(TProfile*, TProfile*, TProfile*, TProfile*, int, const char*);
void plot_recv3(TH1D*, TH1D*, TH1D*, TH1D*, const char*);


void plot_recv3(TProfile* tp1f_eit, TProfile* tp1f_six, TProfile* tp1f_for, TProfile* tp1f_two, int rebin, const char* handle)
{
  cout << "Using hidden method!" << endl;
  // --- initialize the pointers
  TH1D* v38 = NULL;
  TH1D* v36 = NULL;
  TH1D* v34 = NULL;
  TH1D* v32 = NULL;
  // --- get all the v3{k}, c2{k}, and component histograms
  calc_cumulants(tp1f_eit, tp1f_six, tp1f_for, tp1f_two,
                &v38,  &v36,  &v34,  &v32,
                rebin);
  // --- plot the v3{k}
  plot_recv3(v38,v36,v34,v32,handle);
}


void plot_recv3(TH1D* th1d_v38, TH1D* th1d_v36, TH1D* th1d_v34, TH1D* th1d_v32, const char* handle)
{

  TCanvas* c1 = new TCanvas("c1","");

  bool iscent = false;
  bool isscent = false;
  bool isntrk = false;
  if ( strcmp(handle,"cent") == 0 ) iscent = true;
  if ( strcmp(handle,"scent") == 0 ) {iscent = true; isscent = true;}
  if ( strcmp(handle,"ntrk") == 0 ) isntrk = true;
  bool isamptntrk = false;
  if ( strcmp(handle,"amptntrk") == 0 ) { isamptntrk = true; isntrk = true; }
  bool islowzoom = false;
  if ( strcmp(handle,"lowntrkzoom") == 0 ) { islowzoom = true; isntrk = true; }

  // --- get the systmatics histos
  TH1D* gv32_sys = (TH1D*) th1d_v32->Clone("gv32_sys");
  gv32_sys->SetMarkerStyle(0);
  gv32_sys->SetMarkerSize(0);
  gv32_sys->SetFillColorAlpha(kRed, 0.35);
  if ( isscent ) gv32_sys->SetFillColorAlpha(kMagenta+2, 0.35);
  for ( int i = 0; i < gv32_sys->GetNbinsX(); ++i )
  {
    double y = gv32_sys->GetBinContent(i);
    double err = y * 0.09;
    if ( isscent ) err = y * 0.1;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv32_sys->SetBinError(i, err);
  } // i
  TH1D* gv34_sys = (TH1D*) th1d_v34->Clone("gv34_sys");
  gv34_sys->SetMarkerStyle(0);
  gv34_sys->SetMarkerSize(0);
  gv34_sys->SetFillColorAlpha(kBlue, 0.35);
  for ( int i = 0; i < gv34_sys->GetNbinsX(); ++i )
  {
    double y = gv34_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv34_sys->SetBinError(i, err);
  } // i
  TH1D* gv36_sys = (TH1D*) th1d_v36->Clone("gv36_sys");
  gv36_sys->SetMarkerStyle(0);
  gv36_sys->SetMarkerSize(0);
  gv36_sys->SetFillColorAlpha(kBlack, 0.35);
  for ( int i = 0; i < gv34_sys->GetNbinsX(); ++i )
  {
    double y = gv36_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv36_sys->SetBinError(i, err);
  } // i
  TH1D* gv38_sys = (TH1D*) th1d_v38->Clone("gv38_sys");
  gv38_sys->SetMarkerStyle(0);
  gv38_sys->SetMarkerSize(0);
  gv38_sys->SetFillColorAlpha(kGreen+2, 0.35);
  for ( int i = 0; i < gv34_sys->GetNbinsX(); ++i )
  {
    double y = gv38_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv38_sys->SetBinError(i, err);
  } // i


  // --- set up the various drawing options
  if ( iscent )
  {
  th1d_v32->GetXaxis()->SetRangeUser(1,90);
  th1d_v34->GetXaxis()->SetRangeUser(7,65);
  th1d_v36->GetXaxis()->SetRangeUser(7,60);
  th1d_v38->GetXaxis()->SetRangeUser(10,50);
  gv32_sys->GetXaxis()->SetRangeUser(1,90);
  gv34_sys->GetXaxis()->SetRangeUser(7,65);
  gv36_sys->GetXaxis()->SetRangeUser(7,60);
  gv38_sys->GetXaxis()->SetRangeUser(10,50);
  }
  th1d_v36->SetMarkerStyle(kOpenCircle);
  th1d_v36->SetMarkerColor(kBlack);
  th1d_v36->SetLineColor(kBlack);
  th1d_v34->SetMarkerStyle(kOpenSquare);
  th1d_v34->SetMarkerColor(kBlue);
  th1d_v34->SetLineColor(kBlue);
  th1d_v32->SetMarkerStyle(kOpenCross);
  th1d_v32->SetMarkerColor(kRed);
  th1d_v32->SetLineColor(kRed);
  if ( isscent )
  {
  th1d_v32->SetMarkerStyle(kOpenDiamond);
  th1d_v32->SetMarkerColor(kMagenta+2);
  th1d_v32->SetLineColor(kMagenta+2);
  }
  th1d_v38->SetMarkerStyle(kFullDiamond);
  th1d_v38->SetMarkerColor(kGreen+2);
  th1d_v38->SetLineColor(kGreen+2);
  // ---

  // --- considering passing these as arguments...
  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = 0.0;
  double ymax = 0.12;
  if ( isntrk && !islowzoom ) xmax = 650.0;

  // --- do the plotting
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("v_{3}");
  empty->GetYaxis()->SetTitleOffset(1.2);
  // ---
  // TLatex* tex_phenix = new TLatex(0.2,0.882,"PHENIX");
  // tex_phenix->SetTextSize(0.05);
  // tex_phenix->SetNDC();
  // tex_phenix->Draw();
  // TLatex* tex_system = new TLatex(0.2,0.83,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  // tex_system->SetTextSize(0.05);
  // tex_system->SetNDC();
  // tex_system->Draw();
  TLatex* tex_tracks = new TLatex(0.2,0.83,"h^{#pm} 1<|#eta|<3");
  tex_tracks->SetTextSize(0.05);
  tex_tracks->SetNDC();
  tex_tracks->Draw();
  TLatex* tex_system = new TLatex(0.2,0.882,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  tex_system->SetTextSize(0.05);
  tex_system->SetNDC();
  tex_system->Draw();
  // --- first v32
  gv32_sys->Draw("E5 same");
  th1d_v32->Draw("same ex0p");
  TLegend* leg22 = new TLegend(0.66,0.87,0.92,0.92);
  leg22->SetTextSize(0.05);
  leg22->SetFillStyle(0);
  if ( !isscent ) leg22->AddEntry(th1d_v32,"v_{3}{2}","p");
  if ( isscent ) leg22->AddEntry(th1d_v32,"v_{3}{2,|#Delta#eta|>2}","p");
  leg22->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v32.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v32.pdf",handle));
  // --- then animate on v34
  gv34_sys->Draw("E5 same");
  th1d_v34->Draw("same ex0p");
  TLegend* leg24 = new TLegend(0.66,0.82,0.92,0.87);
  leg24->SetTextSize(0.05);
  leg24->SetFillStyle(0);
  leg24->AddEntry(th1d_v34,"v_{3}{4}","p");
  leg24->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v324.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v324.pdf",handle));
  // --- then animate on v36
  gv36_sys->Draw("E5 same");
  th1d_v36->Draw("same ex0p");
  TLegend* leg26 = new TLegend(0.66,0.77,0.92,0.82);
  leg26->SetTextSize(0.05);
  leg26->SetFillStyle(0);
  leg26->AddEntry(th1d_v36,"v_{3}{6}","p");
  leg26->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v3246.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v3246.pdf",handle));
  // --- then animate on v38
  // gv38_sys->Draw("E5 same");
  // th1d_v38->Draw("same ex0p");
  // TLegend* leg28 = new TLegend(0.66,0.72,0.92,0.77);
  // leg28->SetTextSize(0.05);
  // leg28->SetFillStyle(0);
  // leg28->AddEntry(th1d_v38,"v_{3}{8}","p");
  // leg28->Draw();
  // c1->Print(Form("FigsRecursion/recursion_%s_v32468.png",handle));
  // c1->Print(Form("FigsRecursion/recursion_%s_v32468.pdf",handle));

  if ( empty ) delete empty;
  if ( c1 ) delete c1;

}

