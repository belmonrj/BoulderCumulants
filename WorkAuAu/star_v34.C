int rebin = 5;

TH1D* get_cumuhist(TFile*);
TH1D* get_histv324(TFile*);

void star_v34()
{

  //TFile* fileR = TFile::Open("RunByRun/combin.root"); // reference
  TFile* fileR = TFile::Open("input/histos_12634.root"); // reference

  TH1D* histR = get_cumuhist(fileR); // reference
  TH1D* histS = get_histv324(fileR); // reference

  const int nbins = histR->GetNbinsX();

  double norm_c3[nbins];
  double swap_c3[nbins];
  double norm_ec3[nbins];
  double swap_ec3[nbins];
  double norm_v3[nbins];
  double swap_v3[nbins];
  double norm_ev3[nbins];
  double swap_ev3[nbins];
  double cent[nbins];
  double norm_c2[nbins];
  double swap_c2[nbins];
  double norm_ec2[nbins];
  double swap_ec2[nbins];
  double ratio[nbins];
  double eratio[nbins];
  for ( int i = 0; i < nbins; ++i )
    {
      cent[i] = histR->GetBinCenter(i+1);
      // --- normal v3
      norm_c3[i] = histR->GetBinContent(i+1);
      norm_ec3[i] = histR->GetBinError(i+1);
      norm_v3[i] = pow(-norm_c3[i],0.25);
      norm_ev3[i] = (1/(4*pow(-norm_c3[i],0.75)))*norm_ec3[i];
      if ( norm_v3[i] != norm_v3[i] ) norm_v3[i] = -999;
      if ( norm_ev3[i] != norm_ev3[i] ) norm_v3[i] = 998;
      // --- swapped v3
      swap_c3[i] = -1*histR->GetBinContent(i+1);
      swap_ec3[i] = histR->GetBinError(i+1);
      swap_v3[i] = pow(-swap_c3[i],0.25);
      swap_ev3[i] = (1/(4*pow(-swap_c3[i],0.75)))*swap_ec3[i];
      if ( swap_v3[i] != swap_v3[i] ) swap_v3[i] = -999;
      if ( swap_ev3[i] != swap_ev3[i] ) swap_v3[i] = 998;
      // --- v3{2}^4
      swap_c2[i] = histS->GetBinContent(i+1);
      swap_ec2[i] = histS->GetBinError(i+1);
      ratio[i] = 2 - swap_c3[i]/swap_c2[i];
      // --- way too big
      eratio[i] = ratio[i]*sqrt( pow( (swap_ec3[i]/swap_c3[i]), 2.0 ) + pow( (swap_ec2[i]/swap_c2[i]), 2.0 ) );
      eratio[i] = (swap_ec2[i]/swap_c2[i]) * 50;
      swap_c3[i] *= 1e6;
      swap_ec3[i] *= 1e6;
      swap_c2[i] *= 1e6;
      swap_ec2[i] *= 1e6;
      // --- ratio
      // cout << cent[i] << " "
      //      << swap_c3[i] << " "
      //      << swap_c2[i] << " "
      //      << ratio[i] << " +- "
      //      << eratio[i]
      //      << endl;
      cout << cent[i] << " "
           << swap_ec3[i]/swap_c3[i] << " "
           << swap_ec2[i]/swap_c2[i] << " "
           << eratio[i]/ratio[i] << " +- "
           << endl;
    }



  // 106*v34{4}	2 - (v34{4}/v34{2})
  // cent (%)	STAR	        error	ALICE	error	STAR	error	ALICE	error
  // 2.5	-0.00156	0.004	0.0123	0.0047	2.04	0.096	1.95	0.021
  // 7.5	0.00549	        0.0058	0.025	0.0092	1.92	0.082	1.94	0.022
  // 15	        0.000938	0.0069	0.0581	0.01	1.99	0.063	1.91	0.015
  // 25	        0.00728	        0.012	0.0514	0.02	1.95	0.087	1.95	0.018
  // 35	        -0.0346	        0.026	0.114	0.037	2.21	0.15	1.92	0.024
  // 45	        -0.0362	        0.057	0.0983	0.078	2.21	0.34 	1.95	0.04

  float star_cent[6] = {2.5,7.5,15,25,35,45};
  float star_v34[6] = {-0.00156,
                       0.00549,
                       0.000938,
                       0.00728,
                       -0.0346,
                       -0.0362};
  float star_ev34[6] = {0.004,
                        0.0058,
                        0.0069,
                        0.012,
                        0.026,
                        0.057};
  float star_ratio[6] = {2.04,
                         1.92,
                         1.99,
                         1.95,
                         2.21,
                         2.21};
  float star_eratio[6] = {0.096,
                          0.082,
                          0.063,
                          0.087,
                          0.15,
                          0.34};

  //TGraphErrors* tge_norm = new TGraphErrors(nbins,cent,norm_v3,0,norm_ev3);
  TGraphErrors* tge_norm = new TGraphErrors(6,star_cent,star_v34,0,star_ev34);
  TGraphErrors* tge_swap = new TGraphErrors(nbins,cent,swap_c3,0,swap_ec3);
  TGraphErrors* tge_swap2 = new TGraphErrors(nbins,cent,swap_c2,0,swap_ec2);
  TGraphErrors* tge_ratio = new TGraphErrors(nbins,cent,ratio,0,eratio);
  TGraphErrors* tge_sratio = new TGraphErrors(6,star_cent,star_ratio,0,star_eratio);



  // --- do some drawing

  tge_norm->SetLineColor(kBlack);
  tge_norm->SetMarkerColor(kBlack);
  tge_norm->SetMarkerStyle(kFullCircle);
  tge_swap->SetLineColor(kBlack);
  tge_swap->SetMarkerColor(kBlack);
  tge_swap->SetMarkerStyle(kOpenCircle);
  tge_swap2->SetLineColor(kBlack);
  tge_swap2->SetMarkerColor(kBlack);
  tge_swap2->SetMarkerStyle(kFullCircle);
  tge_ratio->SetLineColor(kBlack);
  tge_ratio->SetMarkerColor(kBlack);
  tge_ratio->SetMarkerStyle(kOpenCircle);
  tge_sratio->SetLineColor(kBlack);
  tge_sratio->SetMarkerColor(kBlack);
  tge_sratio->SetMarkerStyle(kFullCircle);

  TCanvas* c1 = new TCanvas("c1","");

  double xmin = 0;
  double xmax = 60;
  double ymin = -0.2;
  double ymax = 0.1;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("10^{6} v_{3}^{4}{4}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_norm->Draw("pz");
  tge_swap->Draw("pz");
  TLegend *leg = new TLegend(0.18,0.18,0.38,0.38);
  leg->SetFillStyle(0);
  //leg->SetHeader("10^{6} v_{3}^{4}{4}");
  leg->AddEntry(tge_swap,"PHENIX","p");
  leg->AddEntry(tge_norm,"STAR, Phys. Rev. C 88 (2013) 14904","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  TLine* line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print("STAR/v34_star.png");
  c1->Print("STAR/v34_star.pdf");


  ymin = -0.2;
  ymax = 0.5;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("10^{6} v_{3}^{4}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_swap->Draw("pz");
  tge_swap2->Draw("pz");
  delete leg;
  leg = new TLegend(0.18,0.68,0.38,0.88);
  leg->SetFillStyle(0);
  //leg->SetHeader("10^{6} v_{3}^{4}");
  leg->AddEntry(tge_swap,"PHENIX v_{3}^{4}{4}","p");
  leg->AddEntry(tge_swap2,"PHENIX v_{3}^{4}{2}","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  delete line;
  line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print("STAR/v342_star.png");
  c1->Print("STAR/v342_star.pdf");


  ymin = 0.0;
  ymax = 9.0;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("2 - v_{3}^{4}{4}/v_{3}^{4}{2}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_ratio->Draw("pz");
  tge_sratio->Draw("pz");
  delete leg;
  leg = new TLegend(0.18,0.18,0.38,0.38);
  leg->SetFillStyle(0);
  //leg->SetHeader("10^{6} v_{3}^{4}");
  leg->AddEntry(tge_ratio,"PHENIX","p");
  leg->AddEntry(tge_sratio,"STAR, Phys. Rev. C 88 (2013) 14904","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  delete line;
  line = new TLine(xmin,2,xmax,2);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print("STAR/v342_ratio_star.png");
  c1->Print("STAR/v342_ratio_star.pdf");


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

TH1D* get_histv324(TFile* fin)
{
  // --- random number helper to prevent memory collisions with ROOT named objects...
  double rand = gRandom->Rndm();
  int helper = rand*10000;
  // --- get the tprofiles
  //TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_recursion_0_1");
  TProfile* ctp1f_two = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c32");
  //ctp1f_two->Rebin(rebin); // maybe already rebinned above? need to add clones to prevent this
  // --- convert to th1ds (to do math operations)
  TH1D* th1d_two = ctp1f_two->ProjectionX(Form("th1d_two_%d",helper)); // <2>
  // --- calc 22
  TH1D* th1d_22 = (TH1D*)th1d_two->Clone(Form("th1d_222_%d",helper)); // <2>^2
  th1d_22->Multiply(th1d_two);
  // --- return
  return th1d_22;
}

