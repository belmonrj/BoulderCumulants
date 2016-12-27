double calc_corr_four(double,double,double,double,double,double,double,double);

void do_process(const char*,int); // get it? :)

void process_cumulants_special()
{
  //  do_process("Run16dAu200",1);
  // do_process("Run16dAu200",5);
  // do_process("Run16dAu200",10);
  // do_process("Run16dAu62",1);
  // do_process("Run16dAu62",5);
  // do_process("Run16dAu62",10);
  // do_process("Run16dAu39",1);
  // do_process("Run16dAu39",5);
  // do_process("Run16dAu39",10);
  // do_process("Run16dAu20",1);
  // do_process("Run16dAu20",5);
  // do_process("Run16dAu20",10);
  //  do_process("Run15pAu200",1);
  // do_process("Run15pAu200",5);
  // do_process("Run15pAu200",10);
  do_process("Run14AuAu200",1);
  // do_process("Run14AuAu200",10);
  // do_process("Run14AuAu200",20);
}

void do_process(const char* type, int rebin)
{

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
      // --- now look at G
      double cos1_north = tp1f_cos1_north->GetBinContent(i+1);
      double sin1_north = tp1f_sin1_north->GetBinContent(i+1);
      double cos1_south = tp1f_cos1_south->GetBinContent(i+1);
      double sin1_south = tp1f_sin1_south->GetBinContent(i+1);
      double two_G      = tp1f_G_two->GetBinContent(i+1);
      double etwo_G     = tp1f_G_two->GetBinError(i+1);
      double corr_c2G   = two_G - cos1_north*cos1_south - sin1_north*sin1_south;
      double uncorr_c2G = two_G;
      // --- calculate the harmonics
      double corr_v24 = -9;
      double corr_v22 = -9;
      double corr_v2G = -9;
      if ( corr_c22 > 0 ) corr_v22 = sqrt(corr_c22);
      if ( corr_c2G > 0 ) corr_v2G = sqrt(corr_c2G);
      if ( corr_c24 < 0 ) corr_v24 = sqrt(sqrt(-corr_c24));
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
      // --- now set the histogram values
      th1d_corr_four->SetBinContent(i+1,corr_four);
      th1d_corr_222->SetBinContent(i+1,corr_222);
      th1d_corr_c24->SetBinContent(i+1,corr_c24);
      th1d_corr_c22->SetBinContent(i+1,corr_c22);
      th1d_corr_c2G->SetBinContent(i+1,corr_c2G);
      th1d_corr_v24->SetBinContent(i+1,corr_v24);
      th1d_corr_v22->SetBinContent(i+1,corr_v22);
      th1d_corr_v2G->SetBinContent(i+1,corr_v2G);
      // --- now set the histogram uncertainties
      th1d_corr_four->SetBinError(i+1,ecorr_four);
      th1d_corr_222->SetBinError(i+1,ecorr_222);
      th1d_corr_c24->SetBinError(i+1,ecorr_c24);
      th1d_corr_c22->SetBinError(i+1,ecorr_c22);
      th1d_corr_c2G->SetBinError(i+1,ecorr_c2G);
      th1d_corr_v24->SetBinError(i+1,ecorr_v24);
      th1d_corr_v22->SetBinError(i+1,ecorr_v22);
      th1d_corr_v2G->SetBinError(i+1,ecorr_v2G);
    }

  // --- now we have all the histograms with proper uncertainties, so let's make some plots
  th1d_corr_v22->SetLineColor(kBlack);
  th1d_corr_v22->SetMarkerColor(kRed);
  th1d_corr_v22->SetMarkerStyle(kFullDiamond);
  th1d_corr_v2G->SetLineColor(kBlack);
  th1d_corr_v2G->SetMarkerColor(kMagenta+2);
  th1d_corr_v2G->SetMarkerStyle(kOpenDiamond);
  th1d_corr_v24->SetLineColor(kBlack);
  th1d_corr_v24->SetMarkerColor(kBlue);
  th1d_corr_v24->SetMarkerStyle(kFullSquare);

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
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_corr_v22,"v_{2}{2}","p");
  leg->AddEntry(th1d_corr_v24,"v_{2}{4}","p");
  leg->Draw();
  c1->Print(Form("FigsFourSpecial/simpleR%d_v22andv24_%s.png",rebin,type));
  c1->Print(Form("FigsFourSpecial/simpleR%d_v22andv24_%s.pdf",rebin,type));
  th1d_corr_v2G->Draw("ex0p same");
  leg->AddEntry(th1d_corr_v2G,"v_{2}{2,|#Delta#eta|>2}","p");
  leg->Draw();
  c1->Print(Form("FigsFourSpecial/simpleR%d_v22andv24andgap_%s.png",rebin,type));
  c1->Print(Form("FigsFourSpecial/simpleR%d_v22andv24andgap_%s.pdf",rebin,type));

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
  empty->GetYaxis()->SetTitle("v_{2}");
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
  c1->Print(Form("FigsFourSpecial/simpleR%d_222and4_%s.png",rebin,type));
  c1->Print(Form("FigsFourSpecial/simpleR%d_222and4_%s.pdf",rebin,type));


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

