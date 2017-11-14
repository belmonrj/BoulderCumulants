int rebin = 2;

TH1D* get_cumuhist(TFile*);

void simple_five()
{

  TFile* file1 = TFile::Open("4095XX.root");
  TFile* file2 = TFile::Open("4096XX.root");
  TFile* file3 = TFile::Open("4097XX.root");
  TFile* file4 = TFile::Open("4098XX.root");
  TFile* file5 = TFile::Open("4099XX.root");
  TFile* fileR = TFile::Open("combin.root"); // reference

  TH1D* hist1 = get_cumuhist(file1);
  TH1D* hist2 = get_cumuhist(file2);
  TH1D* hist3 = get_cumuhist(file3);
  TH1D* hist4 = get_cumuhist(file4);
  TH1D* hist5 = get_cumuhist(file5);
  TH1D* histR = get_cumuhist(fileR); // reference

  const int nbins = histR->GetNbinsX();

  double mean[nbins];
  double widt[nbins];
  double emean[nbins];
  double ewidt[nbins];
  double cent[nbins];
  for ( int i = 0; i < nbins; ++i )
    {
      cent[i] = histR->GetBinCenter(i+1);
      // --- get the weights (1/error^2~N)
      double weit1 = 1/(hist1->GetBinError(i+1)*hist1->GetBinError(i+1));
      double weit2 = 1/(hist2->GetBinError(i+1)*hist2->GetBinError(i+1));
      double weit3 = 1/(hist3->GetBinError(i+1)*hist3->GetBinError(i+1));
      double weit4 = 1/(hist4->GetBinError(i+1)*hist4->GetBinError(i+1));
      double weit5 = 1/(hist5->GetBinError(i+1)*hist5->GetBinError(i+1));
      // --- get the values
      double cumu1 = hist1->GetBinContent(i+1);
      double cumu2 = hist2->GetBinContent(i+1);
      double cumu3 = hist3->GetBinContent(i+1);
      double cumu4 = hist4->GetBinContent(i+1);
      double cumu5 = hist5->GetBinContent(i+1);
      // --- calculate the mean
      mean[i] = ( weit1*cumu1 + weit2*cumu2 + weit3*cumu3 + weit4*cumu4 + weit5*cumu5 )
              / ( weit1 + weit2 + weit3 + weit4 + weit5 );
      widt[i] = ( weit1*cumu1*weit1*cumu1 + weit2*cumu2*weit2*cumu2 + weit3*cumu3*weit3*cumu3 + weit4*cumu4*weit4*cumu4 + weit5*cumu5*weit5*cumu5 )
              / ( weit1*weit1 + weit2*weit2 + weit3*weit3 + weit4*weit4 + weit5*weit5 );
      if ( widt[i] > 0 ) widt[i] = sqrt(widt[i]/5);
      else widt[i] = 0;
      // --- calculate the uncertainties...
      //emean[i] = widt[i]*widt[i] - mean[i]*mean[i];
      // if ( emean[i] > 0 ) emean[i] = sqrt(emean[i]);
      // else emean[i] = 0;
      //emean[i] = sqrt(fabs(emean[i]/nhistos));
      // --- diagnostics...
      //cout << i << " " << width[i] << " " << mean[i]*mean[i] << " " << mean[i] << " " << rms[i] << " " << emean[i] << endl;
      mean[i] = histR->GetBinContent(i+1); // reassign
      if ( mean[i] == 0 ) mean[i] = -999;
    }

  // --- do some drawing

  hist1->SetLineColor(kRed);
  hist1->SetMarkerColor(kRed);
  hist1->SetMarkerStyle(kOpenCircle);
  hist2->SetLineColor(kBlue);
  hist2->SetMarkerColor(kBlue);
  hist2->SetMarkerStyle(kOpenSquare);
  hist3->SetLineColor(kGreen+2);
  hist3->SetMarkerColor(kGreen+2);
  hist3->SetMarkerStyle(kOpenDiamond);
  hist4->SetLineColor(kMagenta+2);
  hist4->SetMarkerColor(kMagenta+2);
  hist4->SetMarkerStyle(kOpenTriangleUp);
  hist5->SetLineColor(kOrange+2);
  hist5->SetMarkerColor(kOrange+2);
  hist5->SetMarkerStyle(kOpenTriangleDown);

  TCanvas* c1 = new TCanvas("c1","");

  double xmin = 0;
  double xmax = 100;
  double ymin = -1e-5;
  double ymax = 1e-5;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hist1->Draw("same ex0p");
  hist2->Draw("same ex0p");
  hist3->Draw("same ex0p");
  hist4->Draw("same ex0p");
  hist5->Draw("same ex0p");

  c1->Print("fig_part1.png");

  TGraphErrors* tge_mean = new TGraphErrors(nbins,cent,mean,0,widt);
  tge_mean->SetLineColor(kGray+1);
  tge_mean->SetLineWidth(10);
  tge_mean->SetMarkerColor(kBlack);
  tge_mean->SetMarkerStyle(kOpenCircle);
  histR->SetLineColor(kBlack);
  histR->SetMarkerColor(kBlack);
  histR->SetMarkerStyle(kFullCircle);

  hdummy->Draw();
  tge_mean->Draw("pz");
  histR->Draw("same ex0p");
  c1->Print("fig_part2.png");

  ymin = -1e-6;
  ymax = 1e-6;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  tge_mean->Draw("pz");
  histR->Draw("same ex0p");
  c1->Print("fig_part3.png");



}

TH1D* get_cumuhist(TFile* fin)
{
  // --- random number helper to prevent memory collisions with ROOT named objects...
  double rand = gRandom->Rndm();
  int helper = rand*10000;
  // --- get the tprofiles
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_recursion_0_3");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_recursion_0_1");
  ctp1f_for->Rebin(rebin);
  ctp1f_two->Rebin(rebin);
  // --- convert to th1ds (to do math operations)
  TH1D* th1d_for = ctp1f_for->ProjectionX(Form("th1d_for_%d",helper)); // <4>
  TH1D* th1d_two = ctp1f_two->ProjectionX(Form("th1d_two_%d",helper)); // <2>
  // --- calc 222
  TH1D* th1d_222 = (TH1D*)th1d_two->Clone(Form("th1d_222_%d",helper)); // 2<2>^2       (for the 4p)
  th1d_222->Multiply(th1d_two);
  th1d_222->Scale(2);
  // --- calc the cumulant
  TH1D* th1d_cu4 = (TH1D*)th1d_for->Clone(Form("th1d_cu4_%d",helper)); // c{4} = <4> - 2<2>^2
  th1d_cu4->Add(th1d_222,-1);
  // --- return the cumulant
  return th1d_cu4;
}
