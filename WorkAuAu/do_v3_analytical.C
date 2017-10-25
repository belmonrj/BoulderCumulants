TFile* fout;

double calc_corr_four(double,double,double,double,double,double,double,double);

void do_process(const char*,int); // get it? :)

void do_v3_analytical()
{
  //do_process("Run14AuAu200",1);
  do_process("Run14AuAu200",2);
}

void do_process(const char* type, int rebin)
{

  TCanvas* c1 = new TCanvas("c1","");

  // --- get the file with the cumulants (considering making a function with a flag to take the collision system)
  TFile* fin = TFile::Open(Form("input/cumulants_%s.root",type));

  // --- get the histograms from the file
  TProfile* tp1f_four = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_c34");
  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_c32");
  TProfile* tp1f_cos1 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_cos31");
  TProfile* tp1f_sin1 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_sin31");
  TProfile* tp1f_cossum2 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_cossum32");
  TProfile* tp1f_sinsum2 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_sinsum32");
  TProfile* tp1f_cos3 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_cos33");
  TProfile* tp1f_sin3 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_sin33");
  TProfile* tp1f_G_two = (TProfile*)fin->Get("centrality_ac_fvtxsfvtxn_tracks_c32"); // scalar product north*south
  TProfile* tp1f_cos1_north = (TProfile*)fin->Get("centrality_ac_fvtxn_tracks_cos31");
  TProfile* tp1f_sin1_north = (TProfile*)fin->Get("centrality_ac_fvtxn_tracks_sin31");
  TProfile* tp1f_cos1_south = (TProfile*)fin->Get("centrality_ac_fvtxs_tracks_cos31");
  TProfile* tp1f_sin1_south = (TProfile*)fin->Get("centrality_ac_fvtxs_tracks_sin31");

  // --- check existence
  if ( !tp1f_four) cout << "tp1f_four" << endl; // missing
  if ( !tp1f_two) cout << "tp1f_two" << endl;
  if ( !tp1f_cos1) cout << "tp1f_cos1" << endl;
  if ( !tp1f_sin1) cout << "tp1f_sin1" << endl;
  if ( !tp1f_cossum2) cout << "tp1f_cossum2" << endl; // missing
  if ( !tp1f_sinsum2) cout << "tp1f_sinsum2" << endl; // missing
  if ( !tp1f_cos3) cout << "tp1f_cos3" << endl; // missing
  if ( !tp1f_sin3) cout << "tp1f_sin3" << endl; // missing
  if ( !tp1f_G_two) cout << "tp1f_G_two" << endl;
  if ( !tp1f_cos1_north) cout << "tp1f_cos1_north" << endl;
  if ( !tp1f_sin1_north) cout << "tp1f_sin1_north" << endl;
  if ( !tp1f_cos1_south) cout << "tp1f_cos1_south" << endl;
  if ( !tp1f_sin1_south) cout << "tp1f_sin1_south" << endl;

  // --- rebin as desired, rebinning on TProfile ensure weighted averages and uncertainties are done correctly
  tp1f_four->Rebin(rebin);
  tp1f_two->Rebin(rebin);
  tp1f_cos1->Rebin(rebin);
  tp1f_sin1->Rebin(rebin);
  tp1f_cossum2->Rebin(rebin);
  tp1f_sinsum2->Rebin(rebin);
  tp1f_cos3->Rebin(rebin);
  tp1f_sin3->Rebin(rebin);
  tp1f_G_two->Rebin(rebin);
  tp1f_cos1_north->Rebin(rebin);
  tp1f_sin1_north->Rebin(rebin);
  tp1f_cos1_south->Rebin(rebin);
  tp1f_sin1_south->Rebin(rebin);

  // --- make some clones to ensure the same binning (number and range)
  TH1D* th1d_four = tp1f_four->ProjectionX();
  TH1D* th1d_corr_four = (TH1D*)th1d_four->Clone("th1d_corr_four");
  TH1D* th1d_corr_222  = (TH1D*)th1d_four->Clone("th1d_corr_222");
  TH1D* th1d_corr_c34  = (TH1D*)th1d_four->Clone("th1d_corr_c34");
  TH1D* th1d_corr_c32  = (TH1D*)th1d_four->Clone("th1d_corr_c32");
  TH1D* th1d_corr_c3G  = (TH1D*)th1d_four->Clone("th1d_corr_c3G");
  TH1D* th1d_corr_v34  = (TH1D*)th1d_four->Clone("th1d_corr_v34");
  TH1D* th1d_corr_v32  = (TH1D*)th1d_four->Clone("th1d_corr_v32");
  TH1D* th1d_corr_v3G  = (TH1D*)th1d_four->Clone("th1d_corr_v3G");
  TH1D* th1d_uncorr_four = (TH1D*)th1d_four->Clone("th1d_uncorr_four");
  TH1D* th1d_uncorr_222  = (TH1D*)th1d_four->Clone("th1d_uncorr_222");
  TH1D* th1d_uncorr_c34  = (TH1D*)th1d_four->Clone("th1d_uncorr_c34");
  TH1D* th1d_uncorr_c32  = (TH1D*)th1d_four->Clone("th1d_uncorr_c32");
  TH1D* th1d_uncorr_c3G  = (TH1D*)th1d_four->Clone("th1d_uncorr_c3G");
  TH1D* th1d_uncorr_v34  = (TH1D*)th1d_four->Clone("th1d_uncorr_v34");
  TH1D* th1d_uncorr_v32  = (TH1D*)th1d_four->Clone("th1d_uncorr_v32");
  TH1D* th1d_uncorr_v3G  = (TH1D*)th1d_four->Clone("th1d_uncorr_v3G");

  // --- get the number of bins and do a loop
  int nbinsx = tp1f_four->GetNbinsX();
  const int nbins = nbinsx;
  for ( int i = 0; i < nbins; ++i )
    {
      // --- get the components
      double four    = tp1f_four->GetBinContent(i+1);
      double two     = tp1f_two->GetBinContent(i+1);
      double efour   = tp1f_four->GetBinError(i+1);
      double etwo    = tp1f_two->GetBinError(i+1);
      double cos1    = tp1f_cos1->GetBinContent(i+1);
      double sin1    = tp1f_sin1->GetBinContent(i+1);
      double cossum2 = tp1f_cossum2->GetBinContent(i+1);
      double sinsum2 = tp1f_sinsum2->GetBinContent(i+1);
      double cos3    = tp1f_cos3->GetBinContent(i+1);
      double sin3    = tp1f_sin3->GetBinContent(i+1);
      // --- calculate corrected terms
      double corr_c32 = two - cos1*cos1 - sin1*sin1;
      double corr_c34 = calc_corr_four(four,two,cos1,sin1,cossum2,sinsum2,cos3,sin3);
      double corr_222 = 2*corr_c32*corr_c32;
      double corr_four = corr_c34 + corr_222;
      // --- also useful to look at some things without the corrections
      double uncorr_four = four;
      double uncorr_222 = 2*two*two;
      double uncorr_c34 = four - 2*two*two;
      double uncorr_c32 = two;
      // --- now look at G
      double cos1_north = tp1f_cos1_north->GetBinContent(i+1);
      double sin1_north = tp1f_sin1_north->GetBinContent(i+1);
      double cos1_south = tp1f_cos1_south->GetBinContent(i+1);
      double sin1_south = tp1f_sin1_south->GetBinContent(i+1);
      double two_G      = tp1f_G_two->GetBinContent(i+1);
      double etwo_G     = tp1f_G_two->GetBinError(i+1);
      double corr_c3G   = two_G - cos1_north*cos1_south - sin1_north*sin1_south;
      double uncorr_c3G = two_G;
      // --- calculate the harmonics
      double corr_v34 = -9;
      double corr_v32 = -9;
      double corr_v3G = -9;
      if ( corr_c32 > 0 ) corr_v32 = sqrt(corr_c32);
      if ( corr_c3G > 0 ) corr_v3G = sqrt(corr_c3G);
      if ( corr_c34 < 0 ) corr_v34 = sqrt(sqrt(-corr_c34));
      double uncorr_v34 = -9;
      double uncorr_v32 = -9;
      double uncorr_v3G = -9;
      if ( uncorr_c32 > 0 ) uncorr_v32 = sqrt(uncorr_c32);
      if ( uncorr_c3G > 0 ) uncorr_v3G = sqrt(uncorr_c3G);
      if ( uncorr_c34 < 0 ) uncorr_v34 = sqrt(sqrt(-uncorr_c34));
      // --- calculate statistical uncertainties
      double ecorr_four = efour;
      double ecorr_222 = 4*two*etwo;
      double ecorr_c3G = etwo_G;
      double ecorr_c32 = etwo;
      double ecorr_c34 = (efour/four)*corr_c34;
      double ecorr_v3G = 0;
      double ecorr_v32 = 0;
      double ecorr_v34 = 0;
      if ( corr_c3G > 0 ) ecorr_v3G = sqrt(1.0/corr_v3G)*ecorr_c3G;
      if ( corr_c32 > 0 ) ecorr_v32 = sqrt(1.0/corr_v32)*ecorr_c32;
      if ( corr_c34 < 0 ) ecorr_v34 = (1.0/pow(-corr_c34,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
      double euncorr_four = efour;
      double euncorr_222 = 4*two*etwo;
      double euncorr_c3G = etwo_G;
      double euncorr_c32 = etwo;
      double euncorr_c34 = (efour/four)*uncorr_c34;
      double euncorr_v3G = 0;
      double euncorr_v32 = 0;
      double euncorr_v34 = 0;
      if ( uncorr_c3G > 0 ) euncorr_v3G = sqrt(1.0/uncorr_v3G)*euncorr_c3G;
      if ( uncorr_c32 > 0 ) euncorr_v32 = sqrt(1.0/uncorr_v32)*euncorr_c32;
      if ( uncorr_c34 < 0 ) euncorr_v34 = (1.0/pow(-uncorr_c34,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
      // --- now set the histogram values
      th1d_corr_four->SetBinContent(i+1,corr_four);
      th1d_corr_222->SetBinContent(i+1,corr_222);
      th1d_corr_c34->SetBinContent(i+1,corr_c34);
      th1d_corr_c32->SetBinContent(i+1,corr_c32);
      th1d_corr_c3G->SetBinContent(i+1,corr_c3G);
      th1d_corr_v34->SetBinContent(i+1,corr_v34);
      th1d_corr_v32->SetBinContent(i+1,corr_v32);
      th1d_corr_v3G->SetBinContent(i+1,corr_v3G);
      th1d_uncorr_four->SetBinContent(i+1,uncorr_four);
      th1d_uncorr_222->SetBinContent(i+1,uncorr_222);
      th1d_uncorr_c34->SetBinContent(i+1,uncorr_c34);
      th1d_uncorr_c32->SetBinContent(i+1,uncorr_c32);
      th1d_uncorr_c3G->SetBinContent(i+1,uncorr_c3G);
      th1d_uncorr_v34->SetBinContent(i+1,uncorr_v34);
      th1d_uncorr_v32->SetBinContent(i+1,uncorr_v32);
      th1d_uncorr_v3G->SetBinContent(i+1,uncorr_v3G);
      // --- now set the histogram uncertainties
      th1d_corr_four->SetBinError(i+1,ecorr_four);
      th1d_corr_222->SetBinError(i+1,ecorr_222);
      th1d_corr_c34->SetBinError(i+1,ecorr_c34);
      th1d_corr_c32->SetBinError(i+1,ecorr_c32);
      th1d_corr_c3G->SetBinError(i+1,ecorr_c3G);
      th1d_corr_v34->SetBinError(i+1,ecorr_v34);
      th1d_corr_v32->SetBinError(i+1,ecorr_v32);
      th1d_corr_v3G->SetBinError(i+1,ecorr_v3G);
      th1d_uncorr_four->SetBinError(i+1,euncorr_four);
      th1d_uncorr_222->SetBinError(i+1,euncorr_222);
      th1d_uncorr_c34->SetBinError(i+1,euncorr_c34);
      th1d_uncorr_c32->SetBinError(i+1,euncorr_c32);
      th1d_uncorr_c3G->SetBinError(i+1,euncorr_c3G);
      th1d_uncorr_v34->SetBinError(i+1,euncorr_v34);
      th1d_uncorr_v32->SetBinError(i+1,euncorr_v32);
      th1d_uncorr_v3G->SetBinError(i+1,euncorr_v3G);
    }

  // --- now we have all the histograms with proper uncertainties, so let's make some plots
  th1d_corr_v32->SetLineColor(kBlack);
  th1d_corr_v32->SetMarkerColor(kRed);
  th1d_corr_v32->SetMarkerStyle(kFullDiamond);
  th1d_corr_v3G->SetLineColor(kBlack);
  th1d_corr_v3G->SetMarkerColor(kMagenta+2);
  th1d_corr_v3G->SetMarkerStyle(kFullDiamond);
  th1d_corr_v34->SetLineColor(kBlack);
  th1d_corr_v34->SetMarkerColor(kBlue);
  th1d_corr_v34->SetMarkerStyle(kFullSquare);

  th1d_uncorr_v32->SetLineColor(kBlack);
  th1d_uncorr_v32->SetMarkerColor(kRed);
  th1d_uncorr_v32->SetMarkerStyle(kOpenDiamond);
  th1d_uncorr_v3G->SetLineColor(kBlack);
  th1d_uncorr_v3G->SetMarkerColor(kMagenta+2);
  th1d_uncorr_v3G->SetMarkerStyle(kOpenDiamond);
  th1d_uncorr_v34->SetLineColor(kBlack);
  th1d_uncorr_v34->SetMarkerColor(kBlue);
  th1d_uncorr_v34->SetMarkerStyle(kOpenSquare);

  th1d_corr_c32->SetLineColor(kBlack);
  th1d_corr_c32->SetMarkerColor(kRed);
  th1d_corr_c32->SetMarkerStyle(kFullDiamond);
  th1d_corr_c3G->SetLineColor(kBlack);
  th1d_corr_c3G->SetMarkerColor(kMagenta+2);
  th1d_corr_c3G->SetMarkerStyle(kFullDiamond);
  th1d_corr_c34->SetLineColor(kBlack);
  th1d_corr_c34->SetMarkerColor(kBlue);
  th1d_corr_c34->SetMarkerStyle(kFullSquare);

  th1d_uncorr_c32->SetLineColor(kBlack);
  th1d_uncorr_c32->SetMarkerColor(kRed);
  th1d_uncorr_c32->SetMarkerStyle(kOpenDiamond);
  th1d_uncorr_c3G->SetLineColor(kBlack);
  th1d_uncorr_c3G->SetMarkerColor(kMagenta+2);
  th1d_uncorr_c3G->SetMarkerStyle(kOpenDiamond);
  th1d_uncorr_c34->SetLineColor(kBlack);
  th1d_uncorr_c34->SetMarkerColor(kBlue);
  th1d_uncorr_c34->SetMarkerStyle(kOpenSquare);

  // --- get the systmatics histos
  TH1D* gv32_sys = (TH1D*) th1d_corr_v32->Clone("gv32_sys");
  gv32_sys->SetMarkerStyle(0);
  gv32_sys->SetMarkerSize(0);
  gv32_sys->SetFillColorAlpha(kRed, 0.35);
  for ( int i = 0; i < gv32_sys->GetNbinsX(); ++i )
  {
    double y = gv32_sys->GetBinContent(i);
    double err = y * 0.09;
    if ( err < 0.005*1.25 ) err = 0.005*1.25;
    if ( y > 0 ) gv32_sys->SetBinError(i, err);
  } // i
  TH1D* gv32ab_sys = (TH1D*) th1d_corr_v3G->Clone("gv32ab_sys");
  gv32ab_sys->SetMarkerStyle(0);
  gv32ab_sys->SetMarkerSize(0);
  gv32ab_sys->SetFillColorAlpha(kMagenta+2, 0.35);
  for ( int i = 0; i < gv32ab_sys->GetNbinsX(); ++i )
  {
    double y = gv32ab_sys->GetBinContent(i);
    double err = y * 0.1;
    if ( err < 0.005*1.25 ) err = 0.005*1.25;
    if ( y > 0 ) gv32ab_sys->SetBinError(i, err);
  } // i
  TH1D* gv34_sys = (TH1D*) th1d_corr_v34->Clone("gv34_sys");
  gv34_sys->SetMarkerStyle(0);
  gv34_sys->SetMarkerSize(0);
  gv34_sys->SetFillColorAlpha(kBlue, 0.35);
  for ( int i = 0; i < gv34_sys->GetNbinsX(); ++i )
  {
    double y = gv34_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.005*1.25 ) err = 0.005*1.25;
    if ( y > 0 ) gv34_sys->SetBinError(i, err);
  } // i

  // -----------------------
  // --- now do the plotting
  // -----------------------

  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = 0.0;
  double ymax = 0.1;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("v_{3}");
  th1d_corr_v32->Draw("ex0p same");
  th1d_corr_v34->Draw("ex0p same");
  TLegend* leg = new TLegend(0.20,0.68,0.40,0.88);
  leg->SetHeader(type);
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_corr_v32,"v_{3}{2}","p");
  leg->AddEntry(th1d_corr_v34,"v_{3}{4}","p");
  leg->Draw();
  c1->Print(Form("FigsFour/simpleR%d_v32andv34_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_v32andv34_%s.pdf",rebin,type));
  th1d_corr_v3G->Draw("ex0p same");
  leg->AddEntry(th1d_corr_v3G,"v_{3}{2,|#Delta#eta|>2}","p");
  leg->Draw();
  c1->Print(Form("FigsFour/simpleR%d_v32andv34andgap_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_v32andv34andgap_%s.pdf",rebin,type));
  th1d_uncorr_v32->Draw("ex0p same");
  th1d_uncorr_v34->Draw("ex0p same");
  th1d_uncorr_v3G->Draw("ex0p same");
  c1->Print(Form("FigsFour/simpleR%d_v32andv34andgapanduncorr_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_v32andv34andgapanduncorr_%s.pdf",rebin,type));

  ymin = -1e-3;
  ymax = 1e-3;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("c_{3}");
  th1d_corr_c32->Draw("ex0p same");
  th1d_corr_c3G->Draw("ex0p same");
  if ( leg ) delete leg;
  leg = new TLegend(0.20,0.68,0.40,0.88);
  leg->SetHeader(type);
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_corr_c3G,"c_{3}{2,|#Delta#eta|>2}","p");
  leg->AddEntry(th1d_corr_c32,"c_{3}{2}","p");
  leg->Draw();
  c1->Print(Form("FigsFour/simpleR%d_c32andgap_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_c32andgap_%s.pdf",rebin,type));
  th1d_uncorr_c32->Draw("ex0p same");
  th1d_uncorr_c3G->Draw("ex0p same");
  c1->Print(Form("FigsFour/simpleR%d_c32andgapanduncorr_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_c32andgapanduncorr_%s.pdf",rebin,type));



  ymin = -1e-6;
  ymax = 1e-6;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("c_{3}");
  th1d_corr_c34->Draw("ex0p same");
  if ( leg ) delete leg;
  leg = new TLegend(0.20,0.68,0.40,0.88);
  leg->SetHeader(type);
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_corr_c34,"c_{3}{4}","p");
  leg->Draw();
  c1->Print(Form("FigsFour/simpleR%d_c34_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_c34_%s.pdf",rebin,type));
  th1d_uncorr_c34->Draw("ex0p same");
  c1->Print(Form("FigsFour/simpleR%d_c34anduncorr_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_c34anduncorr_%s.pdf",rebin,type));



  th1d_corr_222->SetLineColor(kBlack);
  th1d_corr_222->SetMarkerColor(kGreen+2);
  th1d_corr_222->SetMarkerStyle(kFullCircle);
  th1d_corr_four->SetLineColor(kBlack);
  th1d_corr_four->SetMarkerColor(kOrange-5);
  th1d_corr_four->SetMarkerStyle(kFullSquare);
  ymax = 1.0e-5;
  delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("components");
  th1d_corr_222->Draw("ex0p same");
  th1d_corr_four->Draw("ex0p same");
  delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  leg->SetHeader(type);
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_corr_222,"2#LT#LT2#GT#GT^{2}","p");
  leg->AddEntry(th1d_corr_four,"#LT#LT4#GT#GT","p");
  leg->Draw();
  c1->Print(Form("FigsFour/simpleR%d_3h_222and4_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_3h_222and4_%s.pdf",rebin,type));

  th1d_uncorr_222->SetLineColor(kBlack);
  th1d_uncorr_222->SetMarkerColor(kGreen+2);
  th1d_uncorr_222->SetMarkerStyle(kFullCircle);
  th1d_uncorr_four->SetLineColor(kBlack);
  th1d_uncorr_four->SetMarkerColor(kOrange-5);
  th1d_uncorr_four->SetMarkerStyle(kFullSquare);
  ymax = 1.0e-5;
  delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("components");
  th1d_uncorr_222->Draw("ex0p same");
  th1d_uncorr_four->Draw("ex0p same");
  delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  leg->SetHeader(type);
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_uncorr_222,"2#LT#LT2#GT#GT^{2}","p");
  leg->AddEntry(th1d_uncorr_four,"#LT#LT4#GT#GT","p");
  leg->Draw();
  c1->Print(Form("FigsFour/simpleR%d_3h_uncorr_222and4_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_3h_uncorr_222and4_%s.pdf",rebin,type));

  // ---

  // --- these might be useful at some point...?
  TH1D* th1d_cos1 = tp1f_cos1->ProjectionX("th1d_cos1");
  TH1D* th1d_sin1 = tp1f_sin1->ProjectionX("th1d_sin1");
  TH1D* th1d_cossum2 = tp1f_cossum2->ProjectionX("th1d_cossum2");
  TH1D* th1d_sinsum2 = tp1f_sinsum2->ProjectionX("th1d_sinsum2");
  TH1D* th1d_cos3 = tp1f_cos3->ProjectionX("th1d_cos3");
  TH1D* th1d_sin3 = tp1f_sin3->ProjectionX("th1d_sin3");
  TH1D* th1d_cos1_north = tp1f_cos1_north->ProjectionX("th1d_cos1_north");
  TH1D* th1d_sin1_north = tp1f_sin1_north->ProjectionX("th1d_sin1_north");
  TH1D* th1d_cos1_south = tp1f_cos1_south->ProjectionX("th1d_cos1_south");
  TH1D* th1d_sin1_south = tp1f_sin1_south->ProjectionX("th1d_sin1_south");

  delete c1;

}



double calc_corr_four(double four, double two, double cos1, double sin1, double cossum2, double sinsum2, double cos3, double sin3)
{
  double uncorr = four - 2*two*two;
  double corr_term1 = 4*cos1*cos3;
  double corr_term2 = 4*sin1*sin3;
  double corr_term3 = cossum2*cossum2;
  double corr_term4 = sinsum2*sinsum2;
  double corr_term5 = 4*cossum2*(cos1*cos1 - sin1*sin1);
  double corr_term6 = 8*sinsum2*sin1*cos1;
  double corr_term7 = 8*two*(cos1*cos1 + sin1*sin1);
  double corr_term8 = 6*(cos1*cos1 + sin1*sin1)*(cos1*cos1 + sin1*sin1);
  double result = uncorr - corr_term1 + corr_term2 - corr_term3 - corr_term4 + corr_term5 + corr_term6 + corr_term7 - corr_term8;
  return result;
}


