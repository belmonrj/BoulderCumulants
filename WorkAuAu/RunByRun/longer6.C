#include "filenames.C"

const int rebin = 2;
const int nhistos = 60;

TH1D* get_cumuhist(TFile*);



void longer6()
{

  // --- get the reference histo
  TFile* fileR = TFile::Open("combin.root");
  TH1D* histR = get_cumuhist(fileR);

  // -- get the histo for each of the 60 different runs
  TH1D* hist[nhistos];
  for ( int i = 0; i < nhistos; ++i )
    {
      //cout << "opening file " << filenames[i] << endl;
      TFile* fin = TFile::Open(filenames[i]);
      hist[i] = get_cumuhist(fin);
      //cout << "retrieved histo " << hist[i] << endl;
    }

  const int nbins = histR->GetNbinsX();
  double rms[nbins];
  double mean[nbins];
  double sumw[nbins];
  double sumw2[nbins];
  double width[nbins];
  double emean[nbins];
  double ewidth[nbins];
  double cent[nbins];
  for ( int i = 0; i < nbins; ++i )
    {
      // --- get the centrality
      cent[i] = histR->GetBinCenter(i+1);
      // --- loop over histograms to get the weighted average...
      for ( int j = 0; j < nhistos; ++j )
        {
          double weight = hist[j]->GetBinError(i+1); // w = s
          weight *= weight; // w = s^2
          weight = 1/weight; // w = 1/s^2
          double cont = hist[j]->GetBinContent(i+1);
          mean[i] += weight*cont;
          sumw[i] += weight;
          width[i] += weight*weight*cont*cont;
          sumw2[i] += weight*weight;
        }
      // --- now do the normalization
      if ( i == 10 || i == 11 || i == 14 )
        {
          cout << "PROBLEMATIC BIN " << i << endl;
          cout << "mean " << mean[i] << endl;
          cout << "width " << width[i] << endl;
          cout << "sumw " << sumw[i] << endl;
          cout << "sumw2 " << sumw2[i] << endl;
        }
      mean[i] /= sumw[i];
      width[i] /= sumw2[i];
      if ( i == 10 || i == 11 || i == 14 )
        {
          cout << "PROBLEMATIC BIN " << i << endl;
          cout << "normed mean " << mean[i] << endl;
          cout << "normed width " << width[i] << endl;
        }
      if ( i == 2 ) width[i] = width[1];
      rms[i] = sqrt(width[i]);
      // --- now calculate the subgroup method uncertainty
      emean[i] = width[i] - mean[i]*mean[i];
      emean[i] = sqrt(fabs(emean[i]/nhistos));
      // --- diagnostics...
      mean[i] = histR->GetBinContent(i+1); // reassign
      cout << i << " " << width[i] << " " << mean[i]*mean[i] << " " << mean[i] << " " << rms[i] << " " << emean[i] << " " << emean[i]/mean[i] << endl;
      if ( mean[i] == 0 ) mean[i] = -999;
      if ( fabs(emean[i]/mean[i]) > 1e5 ) emean[i] = 0;
    }

  TCanvas* c1 = new TCanvas("c1","");

  double xmin = 0;
  double xmax = 100;
  double ymin = -1e-6;
  double ymax = 1e-6;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();

  //TGraphErrors* tge_mean = new TGraphErrors(nbins,cent,mean,0,width);
  TGraphErrors* tge_mean = new TGraphErrors(nbins,cent,mean,0,emean);
  tge_mean->SetLineColor(kGray+1);
  tge_mean->SetLineWidth(10);
  tge_mean->SetMarkerColor(kBlack);
  tge_mean->SetMarkerStyle(kOpenCircle);
  histR->SetLineColor(kBlack);
  histR->SetMarkerColor(kBlack);
  histR->SetMarkerStyle(kFullCircle);

  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("cumulant"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_mean->Draw("pz");
  histR->Draw("same ex0p");
  TLegend *leg = new TLegend(0.18,0.15,0.38,0.35);
  leg->SetFillStyle(0);
  leg->SetHeader("Stat. Uncertainties");
  leg->AddEntry(histR,"Standard","l");
  leg->AddEntry(tge_mean,"Subgroup estimate","l");
  leg->SetTextSize(0.05);
  leg->Draw();
  c1->Print("sixsixsixfig_part2.png");

  ymin = -1e-7;
  ymax = 1e-7;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("cumulant"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_mean->Draw("pz");
  histR->Draw("same ex0p");
  leg->Draw();
  c1->Print("sixsixsixfig_part3.png");

  ymin = -1e-8;
  ymax = 1e-8;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("cumulant"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_mean->Draw("pz");
  histR->Draw("same ex0p");
  leg->Draw();
  c1->Print("sixsixsixfig_part4.png");

}



TH1D* get_cumuhist(TFile* fin)
{
  // --- random number helper to prevent memory collisions with ROOT named objects...
  double rand = gRandom->Rndm();
  int helper = rand*10000;
  // --- get the tprofiles
  TProfile* ctp1f_six = (TProfile*)fin->Get("centrality_recursion_0_5");
  TProfile* ctp1f_for = (TProfile*)fin->Get("centrality_recursion_0_3");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_recursion_0_1");
  ctp1f_six->Rebin(rebin);
  ctp1f_for->Rebin(rebin);
  ctp1f_two->Rebin(rebin);
  // --- convert to th1ds (to do math operations)
  TH1D* th1d_six = ctp1f_six->ProjectionX(Form("th1d_six_%d",helper)); // <4>
  TH1D* th1d_for = ctp1f_for->ProjectionX(Form("th1d_for_%d",helper)); // <4>
  TH1D* th1d_two = ctp1f_two->ProjectionX(Form("th1d_two_%d",helper)); // <2>
  // --- get the component pieces
  TH1D* th1d_942 = (TH1D*)th1d_for->Clone(Form("th1d_942_%d",helper)); // 9<4><2>      (for the 6p)
  TH1D* th1d_123 = (TH1D*)th1d_two->Clone(Form("th1d_123_%d",helper)); // 12<2>^3      (for the 6p)
  th1d_942->Multiply(th1d_two);
  th1d_942->Scale(9);
  th1d_123->Multiply(th1d_two);
  th1d_123->Multiply(th1d_two);
  th1d_123->Scale(12);
  // --- return the cumulant
  TH1D* th1d_cu6 = (TH1D*)th1d_six->Clone("th1d_cu6"); // c2{6} = <6> - 9<4><2> + 12<2>^3
  th1d_cu6->Add(th1d_942,-1);
  th1d_cu6->Add(th1d_123,1);
  return th1d_cu6;
}
