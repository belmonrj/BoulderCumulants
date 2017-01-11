void helpmecent()
{

  TCanvas* c1 = new TCanvas();

  TFile* fin = TFile::Open("all_cumulants_cent.root");
  TH1D* th1d_v22gap_base = (TH1D*)fin->Get("th1dR1_v22gap_Run14AuAu200");
  TH1D* th1d_v22_base = (TH1D*)fin->Get("th1dR1_v22_Run14AuAu200");
  TH1D* th1d_v24_base = (TH1D*)fin->Get("th1dR1_v24_Run14AuAu200");
  TH1D* th1d_v22gap_unco = (TH1D*)fin->Get("th1dR1U_v22gap_Run14AuAu200");
  TH1D* th1d_v22_unco = (TH1D*)fin->Get("th1dR1U_v22_Run14AuAu200");
  TH1D* th1d_v24_unco = (TH1D*)fin->Get("th1dR1U_v24_Run14AuAu200");

  th1d_v22gap_base->SetMarkerStyle(kFullDiamond);
  th1d_v22_base->SetMarkerStyle(kFullCircle);
  th1d_v24_base->SetMarkerStyle(kFullSquare);

  th1d_v22gap_base->SetMarkerColor(kMagenta+2);
  th1d_v22_base->SetMarkerColor(kRed);
  th1d_v24_base->SetMarkerColor(kBlue);

  th1d_v22gap_unco->SetMarkerStyle(kOpenDiamond);
  th1d_v22_unco->SetMarkerStyle(kOpenCircle);
  th1d_v24_unco->SetMarkerStyle(kOpenSquare);

  th1d_v22gap_unco->SetMarkerColor(kMagenta+2);
  th1d_v22_unco->SetMarkerColor(kRed);
  th1d_v24_unco->SetMarkerColor(kBlue);

  th1d_v22_base->Draw("ex0p");
  th1d_v22_base->SetMinimum(0.0);
  th1d_v22_base->SetMaximum(0.199);
  th1d_v22_base->GetXaxis()->SetTitle("centrality (%)");
  th1d_v22_base->GetYaxis()->SetTitle("v_{2}");
  th1d_v24_base->Draw("ex0p same");
  th1d_v22gap_base->Draw("ex0p same");
  th1d_v22_unco->Draw("ex0p same");
  th1d_v24_unco->Draw("ex0p same");
  th1d_v22gap_unco->Draw("ex0p same");

  c1->Print("acceptance_AuAu.png");


}
