void plot_recv2(TProfile*, TProfile*, TProfile*, TProfile*, int, const char*);
void plot_recv2(TH1D*, TH1D*, TH1D*, TH1D*, const char*);


void plot_recv2(TProfile* tp1f_eit, TProfile* tp1f_six, TProfile* tp1f_for, TProfile* tp1f_two, int rebin, const char* handle)
{
  cout << "Using hidden method!" << endl;
  // --- initialize the pointers
  TH1D* v28 = NULL;
  TH1D* v26 = NULL;
  TH1D* v24 = NULL;
  TH1D* v22 = NULL;
  // --- get all the v2{k}, c2{k}, and component histograms
  calc_cumulants(tp1f_eit, tp1f_six, tp1f_for, tp1f_two,
                &v28,  &v26,  &v24,  &v22,
                rebin);
  // --- plot the v2{k}
  plot_recv2(v28,v26,v24,v22,handle);
}


void plot_recv2(TH1D* th1d_v28, TH1D* th1d_v26, TH1D* th1d_v24, TH1D* th1d_v22, const char* handle)
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
  TH1D* gv22_sys = (TH1D*) th1d_v22->Clone("gv22_sys");
  gv22_sys->SetMarkerStyle(0);
  gv22_sys->SetMarkerSize(0);
  gv22_sys->SetFillColorAlpha(kRed, 0.35);
  if ( isscent ) gv22_sys->SetFillColorAlpha(kMagenta+2, 0.35);
  for ( int i = 0; i < gv22_sys->GetNbinsX(); ++i )
  {
    double y = gv22_sys->GetBinContent(i);
    double err = y * 0.09;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv22_sys->SetBinError(i, err);
  } // i
  TH1D* gv24_sys = (TH1D*) th1d_v24->Clone("gv24_sys");
  gv24_sys->SetMarkerStyle(0);
  gv24_sys->SetMarkerSize(0);
  gv24_sys->SetFillColorAlpha(kBlue, 0.35);
  for ( int i = 0; i < gv24_sys->GetNbinsX(); ++i )
  {
    double y = gv24_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv24_sys->SetBinError(i, err);
  } // i
  TH1D* gv26_sys = (TH1D*) th1d_v26->Clone("gv26_sys");
  gv26_sys->SetMarkerStyle(0);
  gv26_sys->SetMarkerSize(0);
  gv26_sys->SetFillColorAlpha(kBlack, 0.35);
  for ( int i = 0; i < gv24_sys->GetNbinsX(); ++i )
  {
    double y = gv26_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv26_sys->SetBinError(i, err);
  } // i
  TH1D* gv28_sys = (TH1D*) th1d_v28->Clone("gv28_sys");
  gv28_sys->SetMarkerStyle(0);
  gv28_sys->SetMarkerSize(0);
  gv28_sys->SetFillColorAlpha(kGreen+2, 0.35);
  for ( int i = 0; i < gv24_sys->GetNbinsX(); ++i )
  {
    double y = gv28_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv28_sys->SetBinError(i, err);
  } // i


  // --- set up the various drawing options
  if ( iscent )
  {
  th1d_v22->GetXaxis()->SetRangeUser(1,90);
  th1d_v24->GetXaxis()->SetRangeUser(7,65);
  th1d_v26->GetXaxis()->SetRangeUser(7,60);
  th1d_v28->GetXaxis()->SetRangeUser(10,50);
  gv22_sys->GetXaxis()->SetRangeUser(1,90);
  gv24_sys->GetXaxis()->SetRangeUser(7,65);
  gv26_sys->GetXaxis()->SetRangeUser(7,60);
  gv28_sys->GetXaxis()->SetRangeUser(10,50);
  }
  th1d_v26->SetMarkerStyle(kOpenCircle);
  th1d_v26->SetMarkerColor(kBlack);
  th1d_v26->SetLineColor(kBlack);
  th1d_v24->SetMarkerStyle(kOpenSquare);
  th1d_v24->SetMarkerColor(kBlue);
  th1d_v24->SetLineColor(kBlue);
  th1d_v22->SetMarkerStyle(kOpenCross);
  th1d_v22->SetMarkerColor(kRed);
  th1d_v22->SetLineColor(kRed);
  if ( isscent )
  {
  th1d_v22->SetMarkerStyle(kOpenDiamond);
  th1d_v22->SetMarkerColor(kMagenta+2);
  th1d_v22->SetLineColor(kMagenta+2);
  }
  th1d_v28->SetMarkerStyle(kFullDiamond);
  th1d_v28->SetMarkerColor(kGreen+2);
  th1d_v28->SetLineColor(kGreen+2);
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
  empty->GetYaxis()->SetTitle("v_{2}");
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
  // --- first v22
  gv22_sys->Draw("E5 same");
  th1d_v22->Draw("same ex0p");
  TLegend* leg22 = new TLegend(0.66,0.87,0.92,0.92);
  leg22->SetTextSize(0.05);
  leg22->SetFillStyle(0);
  if ( !isscent ) leg22->AddEntry(th1d_v22,"v_{2}{2}","p");
  if ( isscent ) leg22->AddEntry(th1d_v22,"v_{2}{2,|#Delta#eta|>2}","p");
  leg22->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v22.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v22.pdf",handle));
  // --- then animate on v24
  gv24_sys->Draw("E5 same");
  th1d_v24->Draw("same ex0p");
  TLegend* leg24 = new TLegend(0.66,0.82,0.92,0.87);
  leg24->SetTextSize(0.05);
  leg24->SetFillStyle(0);
  leg24->AddEntry(th1d_v24,"v_{2}{4}","p");
  leg24->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v224.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v224.pdf",handle));
  // --- then animate on v26
  gv26_sys->Draw("E5 same");
  th1d_v26->Draw("same ex0p");
  TLegend* leg26 = new TLegend(0.66,0.77,0.92,0.82);
  leg26->SetTextSize(0.05);
  leg26->SetFillStyle(0);
  leg26->AddEntry(th1d_v26,"v_{2}{6}","p");
  leg26->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v2246.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v2246.pdf",handle));
  // --- then animate on v28
  gv28_sys->Draw("E5 same");
  th1d_v28->Draw("same ex0p");
  TLegend* leg28 = new TLegend(0.66,0.72,0.92,0.77);
  leg28->SetTextSize(0.05);
  leg28->SetFillStyle(0);
  leg28->AddEntry(th1d_v28,"v_{2}{8}","p");
  leg28->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v22468.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v22468.pdf",handle));

  if ( empty ) delete empty;
  if ( c1 ) delete c1;

}

