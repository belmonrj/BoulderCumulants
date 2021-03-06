double calc_corr_four(double,double,double,double,double,double,double,double);

void do_process(const char*,int); // get it? :)

TFile* fout;

void process_cumulants_v3()
{

  fout = TFile::Open("all_cumulants_out3.root","recreate");
  // do_process("Run16dAu200",1);
  // do_process("Run16dAu200",2);
  // do_process("Run16dAu200",5);
  // do_process("Run16dAu200",10);
  // do_process("Run16dAu62",1);
  // do_process("Run16dAu62",2);
  // do_process("Run16dAu62",5);
  // do_process("Run16dAu62",10);
  // do_process("Run16dAu39",1);
  // do_process("Run16dAu39",2);
  // do_process("Run16dAu39",5);
  // do_process("Run16dAu39",10);
  // do_process("Run16dAu20",1);
  // do_process("Run16dAu20",2);
  // do_process("Run16dAu20",5);
  // do_process("Run16dAu20",10);
  // do_process("Run15pAu200",1);
  // do_process("Run15pAu200",2);
  // do_process("Run15pAu200",5);
  // do_process("Run15pAu200",10);
  do_process("Run14HeAu200",1);
  do_process("Run14HeAu200",2);
  do_process("Run14HeAu200",5);
  do_process("Run14HeAu200",10);
  // // do_process("Run14AuAu200",1);
  // // do_process("Run14AuAu200",10);
  // // do_process("Run14AuAu200",20);
  fout->Close();
}

void do_process(const char* type, int rebin)
{

  // --- get the file with the cumulants (considering making a function with a flag to take the collision system)
  TFile* fin = TFile::Open(Form("input/cumulants_%s.root",type));

  // --- get the histograms from the file
  TProfile* tp1f_four = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c34");
  TProfile* tp1f_two = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c32");
  TProfile* tp1f_cov = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cov24");
  TProfile* tp1f_cos1 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cos31");
  TProfile* tp1f_sin1 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_sin31");
  TProfile* tp1f_cossum2 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cossum32");
  TProfile* tp1f_sinsum2 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_sinsum32");
  TProfile* tp1f_cos3 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cos33");
  TProfile* tp1f_sin3 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_sin33");
  TProfile* tp1f_G_two = (TProfile*)fin->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c32"); // scalar product north*south
  TProfile* tp1f_cos1_north = (TProfile*)fin->Get("nfvtxt_ac_fvtxn_tracks_cos31");
  TProfile* tp1f_sin1_north = (TProfile*)fin->Get("nfvtxt_ac_fvtxn_tracks_sin31");
  TProfile* tp1f_cos1_south = (TProfile*)fin->Get("nfvtxt_ac_fvtxs_tracks_cos31");
  TProfile* tp1f_sin1_south = (TProfile*)fin->Get("nfvtxt_ac_fvtxs_tracks_sin31");

  bool docov = false;
  if ( tp1f_cov ) docov = true;
  // --- rebin as desired, rebinning on TProfile ensure weighted averages and uncertainties are done correctly
  tp1f_four->Rebin(rebin);
  tp1f_two->Rebin(rebin);
  if ( docov) tp1f_cov->Rebin(rebin);
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

  // --- get the number of bins and do a loop
  int nbinsx = tp1f_four->GetNbinsX();
  const int nbins = nbinsx;
  for ( int i = 0; i < nbins; ++i )
    {
      // --- get the components
      double four    = tp1f_four->GetBinContent(i+1);
      double two     = tp1f_two->GetBinContent(i+1);
      double twofour = 0;
      double count24 = 1;
      if ( docov )
	{
	  twofour = tp1f_cov->GetBinContent(i+1);
	  count24 = tp1f_cov->GetBinEntries(i+1);
	}
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
      // --- calculate statistical uncertainties
      double cov24 = twofour - two*four;
      if ( count24 > 0 ) cov24 /= count24; // ...
      // cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
      // cout << "covariance term: " << cov24 << " <24> = " << twofour << " <2><4> = " << two*four << " <2> = " << two << " <4>  = " << four << endl;
      // cout << "counts: " << count24 << endl;
      // cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
      double ecorr_four = efour;
      double ecorr_222 = 4*two*etwo;
      double ecorr_c3G = etwo_G;
      double ecorr_c32 = etwo;
      double ecorr_c34 = 0;
      // cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
      ecorr_c34 = sqrt((16*two*two*etwo*etwo)+(efour*efour));
      // cout << ecorr_c34 << endl;
      ecorr_c34 = sqrt((16*two*two*etwo*etwo)+(efour*efour)-(8*two*cov24));
      // cout << ecorr_c34 << endl;
      // cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
      // cout << "cumulant is " << corr_c34 << " and error is " << (16*two*two*etwo*etwo) << " + " << (efour*efour) << " - " << (8*two*cov24) << endl;
      double ecorr_v3G = 0;
      double ecorr_v32 = 0;
      double ecorr_v34 = 0;
      if ( corr_c3G > 0 ) ecorr_v3G = sqrt(1.0/corr_v3G)*ecorr_c3G;
      if ( corr_c32 > 0 ) ecorr_v32 = sqrt(1.0/corr_v32)*ecorr_c32;
      if ( corr_c34 < 0 ) ecorr_v34 = (1.0/pow(-corr_c34,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour)-(0.5*two*cov24));
      // --- now set the histogram values
      th1d_corr_four->SetBinContent(i+1,corr_four);
      th1d_corr_222->SetBinContent(i+1,corr_222);
      th1d_corr_c34->SetBinContent(i+1,corr_c34);
      th1d_corr_c32->SetBinContent(i+1,corr_c32);
      th1d_corr_c3G->SetBinContent(i+1,corr_c3G);
      th1d_corr_v34->SetBinContent(i+1,corr_v34);
      th1d_corr_v32->SetBinContent(i+1,corr_v32);
      th1d_corr_v3G->SetBinContent(i+1,corr_v3G);
      // --- now set the histogram uncertainties
      th1d_corr_four->SetBinError(i+1,ecorr_four);
      th1d_corr_222->SetBinError(i+1,ecorr_222);
      th1d_corr_c34->SetBinError(i+1,ecorr_c34);
      th1d_corr_c32->SetBinError(i+1,ecorr_c32);
      th1d_corr_c3G->SetBinError(i+1,ecorr_c3G);
      th1d_corr_v34->SetBinError(i+1,ecorr_v34);
      th1d_corr_v32->SetBinError(i+1,ecorr_v32);
      th1d_corr_v3G->SetBinError(i+1,ecorr_v3G);
    }

  // --- now we have all the histograms with proper uncertainties, so let's make some plots
  th1d_corr_v32->SetLineColor(kBlack);
  th1d_corr_v32->SetMarkerColor(kRed);
  th1d_corr_v32->SetMarkerStyle(kFullDiamond);
  th1d_corr_v3G->SetLineColor(kBlack);
  th1d_corr_v3G->SetMarkerColor(kMagenta+2);
  th1d_corr_v3G->SetMarkerStyle(kOpenDiamond);
  th1d_corr_v34->SetLineColor(kBlack);
  th1d_corr_v34->SetMarkerColor(kBlue);
  th1d_corr_v34->SetMarkerStyle(kFullSquare);

  double xmin = 0.0;
  double xmax = 500.0;
  double ymin = 0.0;
  double ymax = 0.199;
  if ( strcmp(type,"Run14HeAu200") == 0 ) xmax = 200.0;
  if ( strcmp(type,"Run15pAu200") == 0 ) xmax = 70.0;
  if ( strcmp(type,"Run16dAu200") == 0 ) xmax = 70.0;
  if ( strcmp(type,"Run16dAu62") == 0 ) xmax = 70.0;
  if ( strcmp(type,"Run16dAu39") == 0 ) xmax = 70.0;
  if ( strcmp(type,"Run16dAu20") == 0 ) xmax = 70.0;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetYaxis()->SetTitle("v_{3}");
  th1d_corr_v32->Draw("ex0p same");
  th1d_corr_v34->Draw("ex0p same");
  TLegend* leg = new TLegend(0.62,0.68,0.88,0.88);
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

  th1d_corr_222->SetLineColor(kBlack);
  th1d_corr_222->SetMarkerColor(kGreen+2);
  th1d_corr_222->SetMarkerStyle(kFullCircle);
  th1d_corr_four->SetLineColor(kBlack);
  th1d_corr_four->SetMarkerColor(kOrange-5);
  th1d_corr_four->SetMarkerStyle(kFullSquare);
  ymax = 3.0e-4;
  if ( strcmp(type,"Run14HeAu200") == 0 ) ymax = 3.0e-3;
  delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
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
  c1->Print(Form("FigsFour/simpleR%d_222and4_3rd_%s.png",rebin,type));
  c1->Print(Form("FigsFour/simpleR%d_222and4_3rd_%s.pdf",rebin,type));

  fout->cd();
  th1d_corr_v32->SetName(Form("th1dR%d_v32_%s",rebin,type));
  th1d_corr_v3G->SetName(Form("th1dR%d_v32gap_%s",rebin,type));
  th1d_corr_v34->SetName(Form("th1dR%d_v34_%s",rebin,type));
  th1d_corr_222->SetName(Form("th1dR%d_222_%s",rebin,type));
  th1d_corr_four->SetName(Form("th1dR%d_four_%s",rebin,type));
  th1d_corr_c34->SetName(Form("th1dR%d_c34_%s",rebin,type));
  th1d_corr_v32->Write();
  th1d_corr_v3G->Write();
  th1d_corr_v34->Write();
  th1d_corr_222->Write();
  th1d_corr_four->Write();
  th1d_corr_c34->Write();

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

