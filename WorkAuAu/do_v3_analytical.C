TFile* fout;

double calc_corr_four(double,double,double,double,double,double,double,double);

void do_process(const char*,int); // get it? :)

void do_v3_analytical()
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
      //double corr_c3G   = two_G - cos1_north*cos1_south; // this is a dumb idea and it doesn't work anyway
      //double corr_c3G   = two_G - cos1*cos1 - sin1*sin1; // interesting to note this looks much much worse
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
  th1d_uncorr_v32->SetMarkerStyle(kFullDiamond);
  th1d_uncorr_v3G->SetLineColor(kBlack);
  th1d_uncorr_v3G->SetMarkerColor(kMagenta+2);
  th1d_uncorr_v3G->SetMarkerStyle(kFullDiamond);
  th1d_uncorr_v34->SetLineColor(kBlack);
  th1d_uncorr_v34->SetMarkerColor(kBlue);
  th1d_uncorr_v34->SetMarkerStyle(kFullSquare);

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
  th1d_corr_v32->Draw("ex0p same");
  th1d_corr_v34->Draw("ex0p same");
  TLegend* leg = new TLegend(0.62,0.68,0.88,0.88);
  leg->SetHeader(type);
  leg->SetTextSize(0.045);
  //leg->SetFillStyle(0);
  leg->AddEntry(th1d_corr_v32,"v_{2}{2}","p");
  leg->AddEntry(th1d_corr_v34,"v_{2}{4}","p");
  leg->Draw();
  c1->Print(Form("FigsFour/simpleR%d_v32andv34_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_v32andv34_%s.pdf",rebin,type));
  th1d_corr_v3G->Draw("ex0p same");
  leg->AddEntry(th1d_corr_v3G,"v_{2}{2,|#Delta#eta|>2}","p");
  leg->Draw();
  c1->Print(Form("FigsFour/simpleR%d_v32andv34andgap_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_v32andv34andgap_%s.pdf",rebin,type));
  // -----------------------------------------------------------------------------
  // --- STAR data ---------------------------------------------------------------
  // J. Adams et al, Phys. Rev. C72 (2005) 014904
  // arXiv:nucl-ex/0409033
  // https://drupal.star.bnl.gov/STAR/files/starpublications/48/Figure_29a.html
  // v_{2}{2}
  // 1(70-80%) 6.88 0.052
  // 2(60-70%) 7.25 0.029
  // 3(50-60%) 7.59 0.018
  // 4(40-50%) 7.64 0.013
  // 5(30-40%) 7.29 0.0094
  // 6(20-30%) 6.42 0.0075
  // 7(10-20%) 4.97 0.0066
  // 8(5-10%)  3.55 0.0088
  // 9(0-5%)   2.41 0.0096
  // v_{2}{4}
  // 2(60-70%) 5.68 0.35
  // 3(50-60%) 6.18 0.1
  // 4(40-50%) 6.43 0.045
  // 5(30-40%) 6.33 0.026
  // 6(20-30%) 5.66 0.02
  // 7(10-20%) 4.27 0.022
  // 8(5-10%)  2.53 0.066
  // Figure30
  // v3{6}
  // 2(60-70%) 5.65 1.54
  // 3(50-60%) 6.01 0.27
  // 4(40-50%) 6.24 0.08
  // 5(30-40%) 6.14 0.03
  // 6(20-30%) 5.45 0.02
  // 7(10-20%) 4.01 0.03
  // 8(5-10%)  2.48 0.13
  // 9(0-5%)   2.08 0.2
  // -----------------------------------------------------------------------------
  // B. Abelev et al, Phys.Rev. C77 (2008) 054901
  // arXiv:0801.3466
  // https://drupal.star.bnl.gov/STAR/files/starpublications/108/data.html (fig 5)
  //Collision Cross Sectionv3{LYZ_Sum}
  //45 0.0581909  0.00115924
  //35 0.059935   0.000298429
  //25 0.0541134  0.000171784
  //15 0.0411426  0.0002367
  //Collision Cross Sectionv3{LYZ_Prod}(%)
  //55  0.063  0.0037
  //45  0.0627 0.0017
  //35  0.0612 0.0003
  //25  0.0541 0.00024
  //15  0.0404 0.00032
  //7.5 0.0292 0.0023
  // -----------------------------------------------------------------------------
  double cent[9] = {75,65,55,45,35,25,15,7.5,2.5};
  double star_v32[9]={0};
  double star_v34[9]={0};
  double star_v36[9]={0};
  double star_v3LYZS[9]={0};
  double star_v3LYZP[9]={0};
  double star_ev32[9]={0};
  double star_ev34[9]={0};
  double star_ev36[9]={0};
  double star_ev3LYZS[9]={0};
  double star_ev3LYZP[9]={0};
  star_v32[0] = 6.88;  star_v34[0] = -9.0;   star_v36[0] = -9.0;   // 75
  star_v32[1] = 7.25;  star_v34[1] = 5.68;   star_v36[1] = 5.65;   // 65
  star_v32[2] = 7.59;  star_v34[2] = 6.18;   star_v36[2] = 6.01;   // 55
  star_v32[3] = 7.64;  star_v34[3] = 6.43;   star_v36[3] = 6.24;   // 45
  star_v32[4] = 7.29;  star_v34[4] = 6.33;   star_v36[4] = 6.14;   // 35
  star_v32[5] = 6.42;  star_v34[5] = 5.66;   star_v36[5] = 5.45;   // 25
  star_v32[6] = 4.97;  star_v34[6] = 4.27;   star_v36[6] = 4.01;   // 15
  star_v32[7] = 3.55;  star_v34[7] = 2.53;   star_v36[7] = 2.48;   // 7.5
  star_v32[8] = 2.41;  star_v34[8] = -9.0;   star_v36[8] = 2.08;   // 2.5
  star_ev32[0] = 0.052 ;  star_ev34[0] = 0    ;  star_ev36[0] = 0   ; // 75
  star_ev32[1] = 0.029 ;  star_ev34[1] = 0.35 ;  star_ev36[1] = 1.54; // 65
  star_ev32[2] = 0.018 ;  star_ev34[2] = 0.1  ;  star_ev36[2] = 0.27; // 55
  star_ev32[3] = 0.013 ;  star_ev34[3] = 0.045;  star_ev36[3] = 0.08; // 45
  star_ev32[4] = 0.0094;  star_ev34[4] = 0.026;  star_ev36[4] = 0.03; // 35
  star_ev32[5] = 0.0075;  star_ev34[5] = 0.02 ;  star_ev36[5] = 0.02; // 25
  star_ev32[6] = 0.0066;  star_ev34[6] = 0.022;  star_ev36[6] = 0.03; // 15
  star_ev32[7] = 0.0088;  star_ev34[7] = 0.066;  star_ev36[7] = 0.13; // 7.5
  star_ev32[8] = 0.0096;  star_ev34[8] = 0    ;  star_ev36[8] = 0.2 ; // 2.5
  star_v3LYZS[0] = -9.0  ;   star_v3LYZP[0] = -9.0  ;   star_ev3LYZS[0] = 0          ;   star_ev3LYZP[0] = 0      ;   // 75
  star_v3LYZS[1] = -9.0  ;   star_v3LYZP[1] = -9.0  ;   star_ev3LYZS[1] = 0          ;   star_ev3LYZP[1] = 0      ;   // 65
  star_v3LYZS[2] = -9.0  ;   star_v3LYZP[2] = 0.063 ;   star_ev3LYZS[2] = 0          ;   star_ev3LYZP[2] = 0.0037 ;   // 55
  star_v3LYZS[3] = 0.0581;   star_v3LYZP[3] = 0.0627;   star_ev3LYZS[3] = 0.00115924 ;   star_ev3LYZP[3] = 0.0017 ;   // 45
  star_v3LYZS[4] = 0.0599;   star_v3LYZP[4] = 0.0612;   star_ev3LYZS[4] = 0.000298429;   star_ev3LYZP[4] = 0.0003 ;   // 35
  star_v3LYZS[5] = 0.0541;   star_v3LYZP[5] = 0.0541;   star_ev3LYZS[5] = 0.000171784;   star_ev3LYZP[5] = 0.00024;   // 25
  star_v3LYZS[6] = 0.0411;   star_v3LYZP[6] = 0.0404;   star_ev3LYZS[6] = 0.0002367  ;   star_ev3LYZP[6] = 0.00032;   // 15
  star_v3LYZS[7] = -9.0  ;   star_v3LYZP[7] = 0.0292;   star_ev3LYZS[7] = 0          ;   star_ev3LYZP[7] = 0.0023 ;   // 7.5
  star_v3LYZS[8] = -9.0  ;   star_v3LYZP[8] = -9.0  ;   star_ev3LYZS[8] = 0          ;   star_ev3LYZP[8] = 0      ;   // 2.5
  for ( int i = 0; i < 9; ++i )
    {
      star_v32[i] /= 100.0;
      star_v34[i] /= 100.0;
      star_v36[i] /= 100.0;
      star_ev32[i] /= 100.0;
      star_ev34[i] /= 100.0;
      star_ev36[i] /= 100.0;
    }
  TGraphErrors* tge_star_v32 = new TGraphErrors(9,cent,star_v32,0,star_ev32);
  TGraphErrors* tge_star_v34 = new TGraphErrors(9,cent,star_v34,0,star_ev34);
  TGraphErrors* tge_star_v36 = new TGraphErrors(9,cent,star_v36,0,star_ev36);
  tge_star_v32->SetMarkerStyle(kFullStar);
  tge_star_v32->SetMarkerColor(kRed);
  tge_star_v32->SetLineColor(kRed);
  tge_star_v34->SetMarkerStyle(kFullStar);
  tge_star_v34->SetMarkerColor(kBlue);
  tge_star_v34->SetLineColor(kBlue);
  tge_star_v36->SetMarkerStyle(kFullStar);
  tge_star_v36->SetMarkerColor(kBlack);
  tge_star_v36->SetLineColor(kBlack);
  tge_star_v32->SetMarkerSize(2.9);
  tge_star_v34->SetMarkerSize(2.9);
  tge_star_v36->SetMarkerSize(2.9);
  // ---
  TGraphErrors* tge_star_v3LYZS = new TGraphErrors(9,cent,star_v3LYZS,0,star_ev3LYZS);
  TGraphErrors* tge_star_v3LYZP = new TGraphErrors(9,cent,star_v3LYZP,0,star_ev3LYZP);
  tge_star_v3LYZS->SetMarkerStyle(kOpenStar);
  tge_star_v3LYZS->SetMarkerColor(kRed);
  tge_star_v3LYZS->SetLineColor(kRed);
  tge_star_v3LYZP->SetMarkerStyle(kOpenStar);
  tge_star_v3LYZP->SetMarkerColor(kBlack);
  tge_star_v3LYZP->SetLineColor(kBlack);
  tge_star_v3LYZS->SetMarkerSize(2.9);
  tge_star_v3LYZP->SetMarkerSize(2.9);
  // ---
  ymax = 0.12;
  delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("v_{2}");
  // th1d_uncorr_v32->Draw("ex0p same");
  // th1d_uncorr_v34->Draw("ex0p same");
  // th1d_uncorr_v3G->Draw("ex0p same");
  th1d_corr_v32->Draw("ex0p same");
  th1d_corr_v34->Draw("ex0p same");
  th1d_corr_v3G->Draw("ex0p same");
  tge_star_v32->Draw("p");
  tge_star_v34->Draw("p");
  // tge_star_v36->Draw("p");
  // tge_star_v3LYZS->Draw("p");
  // tge_star_v3LYZP->Draw("p");
  leg->Draw();
  //TLegend* leg2 = new TLegend(0.18,0.78,0.38,0.93);
  TLegend* leg2 = new TLegend(0.48,0.16,0.68,0.31);
  leg2->SetHeader("STAR, PRC 72 014904 (2005)");
  leg2->AddEntry(tge_star_v32,"v_{2}{2} |#eta|<1","p");
  leg2->AddEntry(tge_star_v34,"v_{2}{4} |#eta|<1","p");
  // leg2->AddEntry(tge_star_v36,"v_{2}{6} |#eta|<1","p");
  // leg2->AddEntry(tge_star_v3LYZS,"v_{2}{LYZ} Sum |#eta|<1","p");
  // leg2->AddEntry(tge_star_v3LYZP,"v_{2}{LYZ} Product |#eta|<1","p");
  leg2->SetTextSize(0.045);
  leg2->Draw();
  c1->Print(Form("FigsFour/simpleR%d_v32andv34andgapandSTAR_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_v32andv34andgapandSTAR_%s.pdf",rebin,type));
  // ---
  th1d_corr_v32->SetLineColor(kBlack);
  th1d_corr_v32->SetMarkerColor(kRed);
  th1d_corr_v32->SetMarkerStyle(kOpenDiamond);
  th1d_corr_v3G->SetLineColor(kBlack);
  th1d_corr_v3G->SetMarkerColor(kMagenta+2);
  th1d_corr_v3G->SetMarkerStyle(kOpenDiamond);
  th1d_corr_v34->SetLineColor(kBlack);
  th1d_corr_v34->SetMarkerColor(kBlue);
  th1d_corr_v34->SetMarkerStyle(kOpenSquare);
  empty->Draw();
  // th1d_corr_v32->Scale(1.35);
  // th1d_corr_v34->Scale(1.35);
  // th1d_corr_v3G->Scale(1.35);
  // th1d_corr_v32->Scale(1.1);
  // th1d_corr_v34->Scale(1.1);
  // th1d_corr_v3G->Scale(1.1);
  // th1d_corr_v32->Scale(1.2);
  // th1d_corr_v34->Scale(1.2);
  // th1d_corr_v3G->Scale(1.2);
  th1d_corr_v32->Scale(1.25);
  th1d_corr_v34->Scale(1.25);
  th1d_corr_v3G->Scale(1.25);
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
  // ---
  gv32_sys->GetXaxis()->SetRangeUser(1,90);
  gv34_sys->GetXaxis()->SetRangeUser(7,65);
  gv32ab_sys->GetXaxis()->SetRangeUser(1,90);
  th1d_corr_v32->GetXaxis()->SetRangeUser(1,90);
  th1d_corr_v34->GetXaxis()->SetRangeUser(7,65);
  th1d_corr_v3G->GetXaxis()->SetRangeUser(1,90);
  gv32_sys->Draw("same E5");
  gv32ab_sys->Draw("same E5");
  gv34_sys->Draw("same E5");
  th1d_corr_v32->Draw("ex0p same");
  th1d_corr_v34->Draw("ex0p same");
  th1d_corr_v3G->Draw("ex0p same");
  tge_star_v32->Draw("p");
  tge_star_v34->Draw("p");
  // tge_star_v36->Draw("p");
  // tge_star_v3LYZS->Draw("p");
  // tge_star_v3LYZP->Draw("p");
  delete leg;
  leg = new TLegend(0.195,0.605,0.455,0.805);
  //leg->SetHeader("Scaled by 1.35");
  //leg->SetHeader("Scaled by 1.1");
  //leg->SetHeader("Scaled by 1.2");
  leg->SetHeader("1<|#eta|<3 Scaled by 1.25");
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_corr_v3G,"v_{2}{2,|#Delta#eta|>2}","p");
  leg->AddEntry(th1d_corr_v32,"v_{2}{2}","p");
  leg->AddEntry(th1d_corr_v34,"v_{2}{4}","p");
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
  c1->Print(Form("FigsFour/simpleR%d_v32andv34andgapandSTARSCALE_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_v32andv34andgapandSTARSCALE_%s.pdf",rebin,type));

  th1d_corr_222->SetLineColor(kBlack);
  th1d_corr_222->SetMarkerColor(kGreen+2);
  th1d_corr_222->SetMarkerStyle(kFullCircle);
  th1d_corr_four->SetLineColor(kBlack);
  th1d_corr_four->SetMarkerColor(kOrange-5);
  th1d_corr_four->SetMarkerStyle(kFullSquare);
  ymax = 3.0e-4;
  delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("components");
  th1d_corr_222->Draw("ex0p same");
  th1d_corr_four->Draw("ex0p same");
  delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  leg->SetHeader(type);
  leg->SetTextSize(0.045);
  //leg->SetFillStyle(0);
  leg->AddEntry(th1d_corr_222,"2#LT#LT2#GT#GT^{2}","p");
  leg->AddEntry(th1d_corr_four,"#LT#LT4#GT#GT","p");
  leg->Draw();
  c1->Print(Form("FigsFour/simpleR%d_222and4_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_222and4_%s.pdf",rebin,type));

  th1d_uncorr_222->SetLineColor(kBlack);
  th1d_uncorr_222->SetMarkerColor(kGreen+2);
  th1d_uncorr_222->SetMarkerStyle(kFullCircle);
  th1d_uncorr_four->SetLineColor(kBlack);
  th1d_uncorr_four->SetMarkerColor(kOrange-5);
  th1d_uncorr_four->SetMarkerStyle(kFullSquare);
  ymax = 6.0e-4;
  delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("components");
  th1d_uncorr_222->Draw("ex0p same");
  th1d_uncorr_four->Draw("ex0p same");
  delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  leg->SetHeader(type);
  leg->SetTextSize(0.045);
  //leg->SetFillStyle(0);
  leg->AddEntry(th1d_uncorr_222,"2#LT#LT2#GT#GT^{2}","p");
  leg->AddEntry(th1d_uncorr_four,"#LT#LT4#GT#GT","p");
  leg->Draw();
  c1->Print(Form("FigsFour/simpleR%d_uncorr_222and4_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_uncorr_222and4_%s.pdf",rebin,type));

  // ---

  // tp1f_cos1->Rebin(rebin);
  // tp1f_sin1->Rebin(rebin);
  // tp1f_cossum2->Rebin(rebin);
  // tp1f_sinsum2->Rebin(rebin);
  // tp1f_cos3->Rebin(rebin);
  // tp1f_sin3->Rebin(rebin);
  // tp1f_cos1_north->Rebin(rebin);
  // tp1f_sin1_north->Rebin(rebin);
  // tp1f_cos1_south->Rebin(rebin);
  // tp1f_sin1_south->Rebin(rebin);

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


  // --- back out the scaling when writing to file

  th1d_corr_v32->GetXaxis()->SetRangeUser(0,100);
  th1d_corr_v34->GetXaxis()->SetRangeUser(0,100);
  th1d_corr_v3G->GetXaxis()->SetRangeUser(0,100);

  th1d_corr_v32->Scale(1.0/1.35);
  th1d_corr_v34->Scale(1.0/1.35);
  th1d_corr_v3G->Scale(1.0/1.35);

  fout->cd();
  tge_star_v32->SetName("tgrapherrors_v32_STAR");
  tge_star_v34->SetName("tgrapherrors_v34_STAR");
  tge_star_v32->Write();
  tge_star_v34->Write();
  th1d_corr_v32->SetName(Form("th1dR%d_v32_%s",rebin,type));
  th1d_corr_v3G->SetName(Form("th1dR%d_v32gap_%s",rebin,type));
  th1d_corr_v34->SetName(Form("th1dR%d_v34_%s",rebin,type));
  th1d_corr_222->SetName(Form("th1dR%d_222_%s",rebin,type));
  th1d_corr_four->SetName(Form("th1dR%d_four_%s",rebin,type));
  th1d_corr_v32->Write();
  th1d_corr_v3G->Write();
  th1d_corr_v34->Write();
  th1d_corr_222->Write();
  th1d_corr_four->Write();
  th1d_uncorr_v32->SetName(Form("th1dR%dU_v32_%s",rebin,type));
  th1d_uncorr_v3G->SetName(Form("th1dR%dU_v32gap_%s",rebin,type));
  th1d_uncorr_v34->SetName(Form("th1dR%dU_v34_%s",rebin,type));
  th1d_uncorr_222->SetName(Form("th1dR%dU_222_%s",rebin,type));
  th1d_uncorr_four->SetName(Form("th1dR%dU_four_%s",rebin,type));
  th1d_uncorr_v32->Write();
  th1d_uncorr_v3G->Write();
  th1d_uncorr_v34->Write();
  th1d_uncorr_222->Write();
  th1d_uncorr_four->Write();
  th1d_cos1->Write();
  th1d_sin1->Write();
  th1d_cossum2->Write();
  th1d_sinsum2->Write();
  th1d_cos3->Write();
  th1d_sin3->Write();
  th1d_cos1_north->Write();
  th1d_sin1_north->Write();
  th1d_cos1_south->Write();
  th1d_sin1_south->Write();

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


