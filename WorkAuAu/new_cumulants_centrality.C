TFile* fout;

double calc_corr_four(double,double,double,double,double,double,double,double);

void do_process(const char*,int); // get it? :)

void new_cumulants_centrality()
{
  fout = TFile::Open("all_cumulants_cent.root","recreate");
  do_process("Run14AuAu200",1);
  fout->Close();
}

void do_process(const char* type, int rebin)
{

  TCanvas* c1 = new TCanvas("c1","");

  // --- get the file with the cumulants (considering making a function with a flag to take the collision system)
  TFile* fin = TFile::Open(Form("input/cumulants_%s.root",type));

  // --- get the histograms from the file
  TProfile* tp1f_four = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_c24");
  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_c22");
  TProfile* tp1f_cos1 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_cos21");
  TProfile* tp1f_sin1 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_sin21");
  TProfile* tp1f_cossum2 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_cossum22");
  TProfile* tp1f_sinsum2 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_sinsum22");
  TProfile* tp1f_cos3 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_cos23");
  TProfile* tp1f_sin3 = (TProfile*)fin->Get("centrality_ac_fvtxc_tracks_sin23");
  TProfile* tp1f_G_two = (TProfile*)fin->Get("centrality_ac_fvtxsfvtxn_tracks_c22"); // scalar product north*south
  TProfile* tp1f_cos1_north = (TProfile*)fin->Get("centrality_ac_fvtxn_tracks_cos21");
  TProfile* tp1f_sin1_north = (TProfile*)fin->Get("centrality_ac_fvtxn_tracks_sin21");
  TProfile* tp1f_cos1_south = (TProfile*)fin->Get("centrality_ac_fvtxs_tracks_cos21");
  TProfile* tp1f_sin1_south = (TProfile*)fin->Get("centrality_ac_fvtxs_tracks_sin21");

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
  TH1D* th1d_corr_c24  = (TH1D*)th1d_four->Clone("th1d_corr_c24");
  TH1D* th1d_corr_c22  = (TH1D*)th1d_four->Clone("th1d_corr_c22");
  TH1D* th1d_corr_c2G  = (TH1D*)th1d_four->Clone("th1d_corr_c2G");
  TH1D* th1d_corr_v24  = (TH1D*)th1d_four->Clone("th1d_corr_v24");
  TH1D* th1d_corr_v22  = (TH1D*)th1d_four->Clone("th1d_corr_v22");
  TH1D* th1d_corr_v2G  = (TH1D*)th1d_four->Clone("th1d_corr_v2G");
  TH1D* th1d_uncorr_four = (TH1D*)th1d_four->Clone("th1d_uncorr_four");
  TH1D* th1d_uncorr_222  = (TH1D*)th1d_four->Clone("th1d_uncorr_222");
  TH1D* th1d_uncorr_c24  = (TH1D*)th1d_four->Clone("th1d_uncorr_c24");
  TH1D* th1d_uncorr_c22  = (TH1D*)th1d_four->Clone("th1d_uncorr_c22");
  TH1D* th1d_uncorr_c2G  = (TH1D*)th1d_four->Clone("th1d_uncorr_c2G");
  TH1D* th1d_uncorr_v24  = (TH1D*)th1d_four->Clone("th1d_uncorr_v24");
  TH1D* th1d_uncorr_v22  = (TH1D*)th1d_four->Clone("th1d_uncorr_v22");
  TH1D* th1d_uncorr_v2G  = (TH1D*)th1d_four->Clone("th1d_uncorr_v2G");

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
      double corr_c22 = two - cos1*cos1 - sin1*sin1;
      double corr_c24 = calc_corr_four(four,two,cos1,sin1,cossum2,sinsum2,cos3,sin3);
      double corr_222 = 2*corr_c22*corr_c22;
      double corr_four = corr_c24 + corr_222;
      // --- also useful to look at some things without the corrections
      double uncorr_four = four;
      double uncorr_222 = 2*two*two;
      double uncorr_c24 = four - 2*two*two;
      double uncorr_c22 = two;
      // --- now look at G
      double cos1_north = tp1f_cos1_north->GetBinContent(i+1);
      double sin1_north = tp1f_sin1_north->GetBinContent(i+1);
      double cos1_south = tp1f_cos1_south->GetBinContent(i+1);
      double sin1_south = tp1f_sin1_south->GetBinContent(i+1);
      double two_G      = tp1f_G_two->GetBinContent(i+1);
      double etwo_G     = tp1f_G_two->GetBinError(i+1);
      double corr_c2G   = two_G - cos1_north*cos1_south - sin1_north*sin1_south;
      //double corr_c2G   = two_G - cos1_north*cos1_south; // this is a dumb idea and it doesn't work anyway
      //double corr_c2G   = two_G - cos1*cos1 - sin1*sin1; // interesting to note this looks much much worse
      double uncorr_c2G = two_G;
      // --- calculate the harmonics
      double corr_v24 = -9;
      double corr_v22 = -9;
      double corr_v2G = -9;
      if ( corr_c22 > 0 ) corr_v22 = sqrt(corr_c22);
      if ( corr_c2G > 0 ) corr_v2G = sqrt(corr_c2G);
      if ( corr_c24 < 0 ) corr_v24 = sqrt(sqrt(-corr_c24));
      double uncorr_v24 = -9;
      double uncorr_v22 = -9;
      double uncorr_v2G = -9;
      if ( uncorr_c22 > 0 ) uncorr_v22 = sqrt(uncorr_c22);
      if ( uncorr_c2G > 0 ) uncorr_v2G = sqrt(uncorr_c2G);
      if ( uncorr_c24 < 0 ) uncorr_v24 = sqrt(sqrt(-uncorr_c24));
      // --- calculate statistical uncertainties
      double ecorr_four = efour;
      double ecorr_222 = 4*two*etwo;
      double ecorr_c2G = etwo_G;
      double ecorr_c22 = etwo;
      double ecorr_c24 = (efour/four)*corr_c24;
      double ecorr_v2G = 0;
      double ecorr_v22 = 0;
      double ecorr_v24 = 0;
      if ( corr_c2G > 0 ) ecorr_v2G = sqrt(1.0/corr_v2G)*ecorr_c2G;
      if ( corr_c22 > 0 ) ecorr_v22 = sqrt(1.0/corr_v22)*ecorr_c22;
      if ( corr_c24 < 0 ) ecorr_v24 = (1.0/pow(-corr_c24,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
      double euncorr_four = efour;
      double euncorr_222 = 4*two*etwo;
      double euncorr_c2G = etwo_G;
      double euncorr_c22 = etwo;
      double euncorr_c24 = (efour/four)*uncorr_c24;
      double euncorr_v2G = 0;
      double euncorr_v22 = 0;
      double euncorr_v24 = 0;
      if ( uncorr_c2G > 0 ) euncorr_v2G = sqrt(1.0/uncorr_v2G)*euncorr_c2G;
      if ( uncorr_c22 > 0 ) euncorr_v22 = sqrt(1.0/uncorr_v22)*euncorr_c22;
      if ( uncorr_c24 < 0 ) euncorr_v24 = (1.0/pow(-uncorr_c24,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
      // --- now set the histogram values
      th1d_corr_four->SetBinContent(i+1,corr_four);
      th1d_corr_222->SetBinContent(i+1,corr_222);
      th1d_corr_c24->SetBinContent(i+1,corr_c24);
      th1d_corr_c22->SetBinContent(i+1,corr_c22);
      th1d_corr_c2G->SetBinContent(i+1,corr_c2G);
      th1d_corr_v24->SetBinContent(i+1,corr_v24);
      th1d_corr_v22->SetBinContent(i+1,corr_v22);
      th1d_corr_v2G->SetBinContent(i+1,corr_v2G);
      th1d_uncorr_four->SetBinContent(i+1,uncorr_four);
      th1d_uncorr_222->SetBinContent(i+1,uncorr_222);
      th1d_uncorr_c24->SetBinContent(i+1,uncorr_c24);
      th1d_uncorr_c22->SetBinContent(i+1,uncorr_c22);
      th1d_uncorr_c2G->SetBinContent(i+1,uncorr_c2G);
      th1d_uncorr_v24->SetBinContent(i+1,uncorr_v24);
      th1d_uncorr_v22->SetBinContent(i+1,uncorr_v22);
      th1d_uncorr_v2G->SetBinContent(i+1,uncorr_v2G);
      // --- now set the histogram uncertainties
      th1d_corr_four->SetBinError(i+1,ecorr_four);
      th1d_corr_222->SetBinError(i+1,ecorr_222);
      th1d_corr_c24->SetBinError(i+1,ecorr_c24);
      th1d_corr_c22->SetBinError(i+1,ecorr_c22);
      th1d_corr_c2G->SetBinError(i+1,ecorr_c2G);
      th1d_corr_v24->SetBinError(i+1,ecorr_v24);
      th1d_corr_v22->SetBinError(i+1,ecorr_v22);
      th1d_corr_v2G->SetBinError(i+1,ecorr_v2G);
      th1d_uncorr_four->SetBinError(i+1,euncorr_four);
      th1d_uncorr_222->SetBinError(i+1,euncorr_222);
      th1d_uncorr_c24->SetBinError(i+1,euncorr_c24);
      th1d_uncorr_c22->SetBinError(i+1,euncorr_c22);
      th1d_uncorr_c2G->SetBinError(i+1,euncorr_c2G);
      th1d_uncorr_v24->SetBinError(i+1,euncorr_v24);
      th1d_uncorr_v22->SetBinError(i+1,euncorr_v22);
      th1d_uncorr_v2G->SetBinError(i+1,euncorr_v2G);
    }

  // --- now we have all the histograms with proper uncertainties, so let's make some plots
  th1d_corr_v22->SetLineColor(kBlack);
  th1d_corr_v22->SetMarkerColor(kRed);
  th1d_corr_v22->SetMarkerStyle(kFullDiamond);
  th1d_corr_v2G->SetLineColor(kBlack);
  th1d_corr_v2G->SetMarkerColor(kMagenta+2);
  th1d_corr_v2G->SetMarkerStyle(kFullDiamond);
  th1d_corr_v24->SetLineColor(kBlack);
  th1d_corr_v24->SetMarkerColor(kBlue);
  th1d_corr_v24->SetMarkerStyle(kFullSquare);

  th1d_uncorr_v22->SetLineColor(kBlack);
  th1d_uncorr_v22->SetMarkerColor(kRed);
  th1d_uncorr_v22->SetMarkerStyle(kFullDiamond);
  th1d_uncorr_v2G->SetLineColor(kBlack);
  th1d_uncorr_v2G->SetMarkerColor(kMagenta+2);
  th1d_uncorr_v2G->SetMarkerStyle(kFullDiamond);
  th1d_uncorr_v24->SetLineColor(kBlack);
  th1d_uncorr_v24->SetMarkerColor(kBlue);
  th1d_uncorr_v24->SetMarkerStyle(kFullSquare);

  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = 0.0;
  double ymax = 0.199;
  // if ( strcmp(type,"Run15pAu200") == 0 ) xmax = 70.0;
  // if ( strcmp(type,"Run16dAu200") == 0 ) xmax = 70.0;
  // if ( strcmp(type,"Run16dAu62") == 0 ) xmax = 70.0;
  // if ( strcmp(type,"Run16dAu39") == 0 ) xmax = 70.0;
  // if ( strcmp(type,"Run16dAu20") == 0 ) xmax = 70.0;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("v_{2}");
  th1d_corr_v22->Draw("ex0p same");
  th1d_corr_v24->Draw("ex0p same");
  TLegend* leg = new TLegend(0.62,0.68,0.88,0.88);
  leg->SetHeader(type);
  leg->SetTextSize(0.045);
  //leg->SetFillStyle(0);
  leg->AddEntry(th1d_corr_v22,"v_{2}{2}","p");
  leg->AddEntry(th1d_corr_v24,"v_{2}{4}","p");
  leg->Draw();
  th1d_corr_v2G->Draw("ex0p same");
  leg->AddEntry(th1d_corr_v2G,"v_{2}{2,|#Delta#eta|>2}","p");
  leg->Draw();
  // -----------------------------------------------------------------------------
  // -----------------------------------------------------------------------------
  double cent[9] = {75,65,55,45,35,25,15,7.5,2.5};
  double star_v22[9]={0};
  double star_v24[9]={0};
  double star_v26[9]={0};
  double star_v2LYZS[9]={0};
  double star_v2LYZP[9]={0};
  double star_ev22[9]={0};
  double star_ev24[9]={0};
  double star_ev26[9]={0};
  double star_ev2LYZS[9]={0};
  double star_ev2LYZP[9]={0};
  star_v22[0] = 6.88;  star_v24[0] = -9.0;   star_v26[0] = -9.0;   // 75
  star_v22[1] = 7.25;  star_v24[1] = 5.68;   star_v26[1] = 5.65;   // 65
  star_v22[2] = 7.59;  star_v24[2] = 6.18;   star_v26[2] = 6.01;   // 55
  star_v22[3] = 7.64;  star_v24[3] = 6.43;   star_v26[3] = 6.24;   // 45
  star_v22[4] = 7.29;  star_v24[4] = 6.33;   star_v26[4] = 6.14;   // 35
  star_v22[5] = 6.42;  star_v24[5] = 5.66;   star_v26[5] = 5.45;   // 25
  star_v22[6] = 4.97;  star_v24[6] = 4.27;   star_v26[6] = 4.01;   // 15
  star_v22[7] = 3.55;  star_v24[7] = 2.53;   star_v26[7] = 2.48;   // 7.5
  star_v22[8] = 2.41;  star_v24[8] = -9.0;   star_v26[8] = 2.08;   // 2.5
  star_ev22[0] = 0.052 ;  star_ev24[0] = 0    ;  star_ev26[0] = 0   ; // 75
  star_ev22[1] = 0.029 ;  star_ev24[1] = 0.35 ;  star_ev26[1] = 1.54; // 65
  star_ev22[2] = 0.018 ;  star_ev24[2] = 0.1  ;  star_ev26[2] = 0.27; // 55
  star_ev22[3] = 0.013 ;  star_ev24[3] = 0.045;  star_ev26[3] = 0.08; // 45
  star_ev22[4] = 0.0094;  star_ev24[4] = 0.026;  star_ev26[4] = 0.03; // 35
  star_ev22[5] = 0.0075;  star_ev24[5] = 0.02 ;  star_ev26[5] = 0.02; // 25
  star_ev22[6] = 0.0066;  star_ev24[6] = 0.022;  star_ev26[6] = 0.03; // 15
  star_ev22[7] = 0.0088;  star_ev24[7] = 0.066;  star_ev26[7] = 0.13; // 7.5
  star_ev22[8] = 0.0096;  star_ev24[8] = 0    ;  star_ev26[8] = 0.2 ; // 2.5
  star_v2LYZS[0] = -9.0  ;   star_v2LYZP[0] = -9.0  ;   star_ev2LYZS[0] = 0          ;   star_ev2LYZP[0] = 0      ;   // 75
  star_v2LYZS[1] = -9.0  ;   star_v2LYZP[1] = -9.0  ;   star_ev2LYZS[1] = 0          ;   star_ev2LYZP[1] = 0      ;   // 65
  star_v2LYZS[2] = -9.0  ;   star_v2LYZP[2] = 0.063 ;   star_ev2LYZS[2] = 0          ;   star_ev2LYZP[2] = 0.0037 ;   // 55
  star_v2LYZS[3] = 0.0581;   star_v2LYZP[3] = 0.0627;   star_ev2LYZS[3] = 0.00115924 ;   star_ev2LYZP[3] = 0.0017 ;   // 45
  star_v2LYZS[4] = 0.0599;   star_v2LYZP[4] = 0.0612;   star_ev2LYZS[4] = 0.000298429;   star_ev2LYZP[4] = 0.0003 ;   // 35
  star_v2LYZS[5] = 0.0541;   star_v2LYZP[5] = 0.0541;   star_ev2LYZS[5] = 0.000171784;   star_ev2LYZP[5] = 0.00024;   // 25
  star_v2LYZS[6] = 0.0411;   star_v2LYZP[6] = 0.0404;   star_ev2LYZS[6] = 0.0002367  ;   star_ev2LYZP[6] = 0.00032;   // 15
  star_v2LYZS[7] = -9.0  ;   star_v2LYZP[7] = 0.0292;   star_ev2LYZS[7] = 0          ;   star_ev2LYZP[7] = 0.0023 ;   // 7.5
  star_v2LYZS[8] = -9.0  ;   star_v2LYZP[8] = -9.0  ;   star_ev2LYZS[8] = 0          ;   star_ev2LYZP[8] = 0      ;   // 2.5
  for ( int i = 0; i < 9; ++i )
    {
      star_v22[i] /= 100.0;
      star_v24[i] /= 100.0;
      star_v26[i] /= 100.0;
      star_ev22[i] /= 100.0;
      star_ev24[i] /= 100.0;
      star_ev26[i] /= 100.0;
    }
  TGraphErrors* tge_star_v22 = new TGraphErrors(9,cent,star_v22,0,star_ev22);
  TGraphErrors* tge_star_v24 = new TGraphErrors(9,cent,star_v24,0,star_ev24);
  TGraphErrors* tge_star_v26 = new TGraphErrors(9,cent,star_v26,0,star_ev26);
  tge_star_v22->SetMarkerStyle(kFullStar);
  tge_star_v22->SetMarkerColor(kRed);
  tge_star_v22->SetLineColor(kRed);
  tge_star_v24->SetMarkerStyle(kFullStar);
  tge_star_v24->SetMarkerColor(kBlue);
  tge_star_v24->SetLineColor(kBlue);
  tge_star_v26->SetMarkerStyle(kFullStar);
  tge_star_v26->SetMarkerColor(kBlack);
  tge_star_v26->SetLineColor(kBlack);
  tge_star_v22->SetMarkerSize(2.9);
  tge_star_v24->SetMarkerSize(2.9);
  tge_star_v26->SetMarkerSize(2.9);
  // ---
  TGraphErrors* tge_star_v2LYZS = new TGraphErrors(9,cent,star_v2LYZS,0,star_ev2LYZS);
  TGraphErrors* tge_star_v2LYZP = new TGraphErrors(9,cent,star_v2LYZP,0,star_ev2LYZP);
  tge_star_v2LYZS->SetMarkerStyle(kOpenStar);
  tge_star_v2LYZS->SetMarkerColor(kRed);
  tge_star_v2LYZS->SetLineColor(kRed);
  tge_star_v2LYZP->SetMarkerStyle(kOpenStar);
  tge_star_v2LYZP->SetMarkerColor(kBlack);
  tge_star_v2LYZP->SetLineColor(kBlack);
  tge_star_v2LYZS->SetMarkerSize(2.9);
  tge_star_v2LYZP->SetMarkerSize(2.9);
  // ---
  ymax = 0.12;
  delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("v_{2}");
  th1d_corr_v22->Draw("ex0p same");
  th1d_corr_v24->Draw("ex0p same");
  th1d_corr_v2G->Draw("ex0p same");
  tge_star_v22->Draw("p");
  tge_star_v24->Draw("p");
  leg->Draw();
  //TLegend* leg2 = new TLegend(0.18,0.78,0.38,0.93);
  TLegend* leg2 = new TLegend(0.48,0.16,0.68,0.31);
  leg2->SetHeader("STAR, PRC 72 014904 (2005)");
  leg2->AddEntry(tge_star_v22,"v_{2}{2} |#eta|<1","p");
  leg2->AddEntry(tge_star_v24,"v_{2}{4} |#eta|<1","p");
  leg2->SetTextSize(0.045);
  leg2->Draw();
  // ---
  th1d_corr_v22->SetLineColor(kBlack);
  th1d_corr_v22->SetMarkerColor(kRed);
  th1d_corr_v22->SetMarkerStyle(kOpenCross);
  th1d_corr_v2G->SetLineColor(kBlack);
  th1d_corr_v2G->SetMarkerColor(kMagenta+2);
  th1d_corr_v2G->SetMarkerStyle(kOpenDiamond);
  th1d_corr_v24->SetLineColor(kBlack);
  th1d_corr_v24->SetMarkerColor(kBlue);
  th1d_corr_v24->SetMarkerStyle(kOpenSquare);
  empty->Draw();
  th1d_corr_v22->Scale(1.25);
  th1d_corr_v24->Scale(1.25);
  th1d_corr_v2G->Scale(1.25);
  // --- get the systmatics histos
  TH1D* gv22_sys = (TH1D*) th1d_corr_v22->Clone("gv22_sys");
  gv22_sys->SetMarkerStyle(0);
  gv22_sys->SetMarkerSize(0);
  gv22_sys->SetFillColorAlpha(kRed, 0.35);
  for ( int i = 0; i < gv22_sys->GetNbinsX(); ++i )
  {
    double y = gv22_sys->GetBinContent(i);
    double err = y * 0.09;
    if ( err < 0.005*1.25 ) err = 0.005*1.25;
    if ( y > 0 ) gv22_sys->SetBinError(i, err);
  } // i
  TH1D* gv22ab_sys = (TH1D*) th1d_corr_v2G->Clone("gv22ab_sys");
  gv22ab_sys->SetMarkerStyle(0);
  gv22ab_sys->SetMarkerSize(0);
  gv22ab_sys->SetFillColorAlpha(kMagenta+2, 0.35);
  for ( int i = 0; i < gv22ab_sys->GetNbinsX(); ++i )
  {
    double y = gv22ab_sys->GetBinContent(i);
    double err = y * 0.1;
    if ( err < 0.005*1.25 ) err = 0.005*1.25;
    if ( y > 0 ) gv22ab_sys->SetBinError(i, err);
  } // i
  TH1D* gv24_sys = (TH1D*) th1d_corr_v24->Clone("gv24_sys");
  gv24_sys->SetMarkerStyle(0);
  gv24_sys->SetMarkerSize(0);
  gv24_sys->SetFillColorAlpha(kBlue, 0.35);
  for ( int i = 0; i < gv24_sys->GetNbinsX(); ++i )
  {
    double y = gv24_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.005*1.25 ) err = 0.005*1.25;
    if ( y > 0 ) gv24_sys->SetBinError(i, err);
  } // i
  // ---
  gv22_sys->GetXaxis()->SetRangeUser(1,90);
  gv24_sys->GetXaxis()->SetRangeUser(7,65);
  gv22ab_sys->GetXaxis()->SetRangeUser(1,90);
  th1d_corr_v22->GetXaxis()->SetRangeUser(1,90);
  th1d_corr_v24->GetXaxis()->SetRangeUser(7,65);
  th1d_corr_v2G->GetXaxis()->SetRangeUser(1,90);
  gv22_sys->Draw("same E5");
  //gv22ab_sys->Draw("same E5");
  gv24_sys->Draw("same E5");
  th1d_corr_v22->Draw("ex0p same");
  th1d_corr_v24->Draw("ex0p same");
  //th1d_corr_v2G->Draw("ex0p same");
  tge_star_v22->Draw("p");
  tge_star_v24->Draw("p");
  delete leg;
  leg = new TLegend(0.195,0.655,0.455,0.805);
  leg->SetHeader("1<|#eta|<3 Scaled by 1.25");
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  //leg->AddEntry(th1d_corr_v2G,"v_{2}{2,|#Delta#eta|>2}","p");
  leg->AddEntry(th1d_corr_v22,"v_{2}{2}","p");
  leg->AddEntry(th1d_corr_v24,"v_{2}{4}","p");
  leg->Draw();
  leg->Draw();
  leg2->Draw();
  // ---
  TLatex* tex_phenix = new TLatex(0.2,0.882,"PHENIX");
  tex_phenix->SetTextSize(0.05);
  tex_phenix->SetNDC();
  tex_phenix->Draw();
  TLatex* tex_system = new TLatex(0.2,0.83,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  tex_system->SetTextSize(0.05);
  tex_system->SetNDC();
  tex_system->Draw();
  // ---
  c1->Print(Form("FigsStar/star%d_v224_%s.png",rebin,type));
  c1->Print(Form("FigsStar/star%d_v224_%s.pdf",rebin,type));
  th1d_corr_v2G->Draw("ex0p same");
  gv22ab_sys->Draw("same E5");
  delete leg;
  leg = new TLegend(0.195,0.605,0.455,0.805);
  leg->SetHeader("1<|#eta|<3 Scaled by 1.25");
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_corr_v2G,"v_{2}{2,|#Delta#eta|>2}","p");
  leg->AddEntry(th1d_corr_v22,"v_{2}{2}","p");
  leg->AddEntry(th1d_corr_v24,"v_{2}{4}","p");
  leg->Draw();
  c1->Print(Form("FigsStar/star%d_v22g4_%s.png",rebin,type));
  c1->Print(Form("FigsStar/star%d_v22g4_%s.pdf",rebin,type));


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


