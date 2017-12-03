int rebin = 2;

TH1D* get_cumuhist(TFile*);

void swap_v36()
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

  double sub1_c3[nbins];
  double sub2_c3[nbins];
  double sub3_c3[nbins];
  double sub4_c3[nbins];
  double sub5_c3[nbins];
  double norm_c3[nbins];
  double swap_c3[nbins];
  double sub1_ec3[nbins];
  double sub2_ec3[nbins];
  double sub3_ec3[nbins];
  double sub4_ec3[nbins];
  double sub5_ec3[nbins];
  double norm_ec3[nbins];
  double swap_ec3[nbins];
  double sub1_v3[nbins];
  double sub2_v3[nbins];
  double sub3_v3[nbins];
  double sub4_v3[nbins];
  double sub5_v3[nbins];
  double norm_v3[nbins];
  double swap_v3[nbins];
  double sub1_ev3[nbins];
  double sub2_ev3[nbins];
  double sub3_ev3[nbins];
  double sub4_ev3[nbins];
  double sub5_ev3[nbins];
  double norm_ev3[nbins];
  double swap_ev3[nbins];
  double cent[nbins];
  for ( int i = 0; i < nbins; ++i )
    {
      cent[i] = histR->GetBinCenter(i+1);
      // --- normal v3
      norm_c3[i] = histR->GetBinContent(i+1);
      norm_ec3[i] = histR->GetBinError(i+1);
      norm_v3[i] = pow(0.25*norm_c3[i],(1.0/6.0));
      norm_ev3[i] = (1/(6*pow(norm_c3[i],(5.0/6.0))))*norm_ec3[i];
      if ( norm_v3[i] != norm_v3[i] ) norm_v3[i] = -999;
      if ( norm_ev3[i] != norm_ev3[i] ) norm_v3[i] = 998;
      // --- swapped v3
      swap_c3[i] = -1*histR->GetBinContent(i+1);
      swap_ec3[i] = histR->GetBinError(i+1);
      swap_v3[i] = pow(0.25*swap_c3[i],(1.0/6.0));
      swap_ev3[i] = (1/(6*pow(swap_c3[i],(5.0/6.0))))*swap_ec3[i];
      if ( swap_v3[i] != swap_v3[i] ) swap_v3[i] = -999;
      if ( swap_ev3[i] != swap_ev3[i] ) swap_v3[i] = 998;
      // --- v3 in sub1
      sub1_c3[i] = hist1->GetBinContent(i+1);
      sub1_ec3[i] = hist1->GetBinError(i+1);
      sub1_v3[i] = pow(0.25*sub1_c3[i],(1.0/6.0));
      sub1_ev3[i] = (1/(6*pow(sub1_c3[i],(5.0/6.0))))*sub1_ec3[i];
      if ( sub1_v3[i] != sub1_v3[i] ) sub1_v3[i] = -999;
      if ( sub1_ev3[i] != sub1_ev3[i] ) sub1_v3[i] = 998;
      // --- v3 in sub2
      sub2_c3[i] = hist2->GetBinContent(i+1);
      sub2_ec3[i] = hist2->GetBinError(i+1);
      sub2_v3[i] = pow(0.25*sub2_c3[i],(1.0/6.0));
      sub2_ev3[i] = (1/(6*pow(sub2_c3[i],(5.0/6.0))))*sub2_ec3[i];
      if ( sub2_v3[i] != sub2_v3[i] ) sub2_v3[i] = -999;
      if ( sub2_ev3[i] != sub2_ev3[i] ) sub2_v3[i] = 998;
      // --- v3 in sub3
      sub3_c3[i] = hist3->GetBinContent(i+1);
      sub3_ec3[i] = hist3->GetBinError(i+1);
      sub3_v3[i] = pow(0.25*sub3_c3[i],(1.0/6.0));
      sub3_ev3[i] = (1/(6*pow(sub3_c3[i],(5.0/6.0))))*sub3_ec3[i];
      if ( sub3_v3[i] != sub3_v3[i] ) sub3_v3[i] = -999;
      if ( sub3_ev3[i] != sub3_ev3[i] ) sub3_v3[i] = 998;
      // --- v3 in sub4
      sub4_c3[i] = hist4->GetBinContent(i+1);
      sub4_ec3[i] = hist4->GetBinError(i+1);
      sub4_v3[i] = pow(0.25*sub4_c3[i],(1.0/6.0));
      sub4_ev3[i] = (1/(6*pow(sub4_c3[i],(5.0/6.0))))*sub4_ec3[i];
      if ( sub4_v3[i] != sub4_v3[i] ) sub4_v3[i] = -999;
      if ( sub4_ev3[i] != sub4_ev3[i] ) sub4_v3[i] = 998;
      // --- v3 in sub5
      sub5_c3[i] = hist5->GetBinContent(i+1);
      sub5_ec3[i] = hist5->GetBinError(i+1);
      sub5_v3[i] = pow(0.25*sub5_c3[i],(1.0/6.0));
      sub5_ev3[i] = (1/(6*pow(sub5_c3[i],(5.0/6.0))))*sub5_ec3[i];
      if ( sub5_v3[i] != sub5_v3[i] ) sub5_v3[i] = -999;
      if ( sub5_ev3[i] != sub5_ev3[i] ) sub5_v3[i] = 998;
    }

  TGraphErrors* tge_norm = new TGraphErrors(nbins,cent,norm_v3,0,norm_ev3);
  TGraphErrors* tge_swap = new TGraphErrors(nbins,cent,swap_v3,0,swap_ev3);
  TGraphErrors* tge_sub1 = new TGraphErrors(nbins,cent,sub1_v3,0,sub1_ev3);
  TGraphErrors* tge_sub2 = new TGraphErrors(nbins,cent,sub2_v3,0,sub2_ev3);
  TGraphErrors* tge_sub3 = new TGraphErrors(nbins,cent,sub3_v3,0,sub3_ev3);
  TGraphErrors* tge_sub4 = new TGraphErrors(nbins,cent,sub4_v3,0,sub4_ev3);
  TGraphErrors* tge_sub5 = new TGraphErrors(nbins,cent,sub5_v3,0,sub5_ev3);



  // --- do some drawing

  tge_norm->SetLineColor(kBlack);
  tge_norm->SetMarkerColor(kBlack);
  tge_norm->SetMarkerStyle(kFullCircle);
  tge_swap->SetLineColor(kBlack);
  tge_swap->SetMarkerColor(kBlack);
  tge_swap->SetMarkerStyle(kOpenCircle);
  tge_sub1->SetLineColor(kRed);
  tge_sub1->SetMarkerColor(kRed);
  tge_sub1->SetMarkerStyle(kOpenCircle);
  tge_sub2->SetLineColor(kBlue);
  tge_sub2->SetMarkerColor(kBlue);
  tge_sub2->SetMarkerStyle(kOpenSquare);
  tge_sub3->SetLineColor(kGreen+2);
  tge_sub3->SetMarkerColor(kGreen+2);
  tge_sub3->SetMarkerStyle(kOpenDiamond);
  tge_sub4->SetLineColor(kMagenta+2);
  tge_sub4->SetMarkerColor(kMagenta+2);
  tge_sub4->SetMarkerStyle(kOpenTriangleUp);
  tge_sub5->SetLineColor(kOrange+2);
  tge_sub5->SetMarkerColor(kOrange+2);
  tge_sub5->SetMarkerStyle(kOpenTriangleDown);

  TCanvas* c1 = new TCanvas("c1","");

  double xmin = 0;
  double xmax = 100;
  double ymin = -0.01;
  double ymax = 0.1;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle(Form("v_{3}{4}"));
  hdummy->GetYaxis()->SetTitleOffset(1.25);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  tge_norm->Draw("pz");
  tge_swap->Draw("pz");
  TLegend *leg = new TLegend(0.18,0.65,0.38,0.85);
  leg->SetFillStyle(0);
  leg->AddEntry(tge_norm,"Regular","p");
  leg->AddEntry(tge_swap,"Swapped sign","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  c1->Print("v36_phase2.png");
  c1->Print("v36_phase2.pdf");

  hdummy->Draw();
  tge_norm->Draw("p");
  tge_sub1->Draw("p");
  tge_sub2->Draw("p");
  tge_sub3->Draw("p");
  tge_sub4->Draw("p");
  tge_sub5->Draw("p");
  delete leg;
  leg = new TLegend(0.18,0.55,0.38,0.90);
  leg->SetFillStyle(0);
  leg->AddEntry(tge_norm,"Full data set","p");
  leg->AddEntry(tge_sub1,"Subgroup 1","p");
  leg->AddEntry(tge_sub2,"Subgroup 2","p");
  leg->AddEntry(tge_sub3,"Subgroup 3","p");
  leg->AddEntry(tge_sub4,"Subgroup 4","p");
  leg->AddEntry(tge_sub5,"Subgroup 5","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  c1->Print("v36_phase1.png");
  c1->Print("v36_phase1.pdf");

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
