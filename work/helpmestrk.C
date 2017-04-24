void helpmestrk()
{

  TCanvas* c1 = new TCanvas();

  TFile* fin = TFile::Open("all_cumulants_strk.root");
  TH1D* th1d_v22gap_base = (TH1D*)fin->Get("th1dR10_v22gap_Run14AuAu200");
  TH1D* th1d_v22_base = (TH1D*)fin->Get("th1dR10_v22_Run14AuAu200");
  TH1D* th1d_v24_base = (TH1D*)fin->Get("th1dR10_v24_Run14AuAu200");
  TH1D* th1d_v22gap_unco = (TH1D*)fin->Get("th1dR10U_v22gap_Run14AuAu200");
  TH1D* th1d_v22_unco = (TH1D*)fin->Get("th1dR10U_v22_Run14AuAu200");
  TH1D* th1d_v24_unco = (TH1D*)fin->Get("th1dR10U_v24_Run14AuAu200");

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
  th1d_v22_base->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
  th1d_v22_base->GetYaxis()->SetTitle("v_{2}");
  th1d_v24_base->Draw("ex0p same");
  th1d_v22gap_base->Draw("ex0p same");
  th1d_v22_unco->Draw("ex0p same");
  th1d_v24_unco->Draw("ex0p same");
  th1d_v22gap_unco->Draw("ex0p same");

  TLegend* leg = new TLegend(0.62,0.68,0.88,0.88);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  //leg->SetFillStyle(0);
  leg->AddEntry(th1d_v22_base,"v_{2}{2} 1<|#eta|<3","p");
  leg->AddEntry(th1d_v24_base,"v_{2}{4} 1<|#eta|<3","p");
  leg->AddEntry(th1d_v22gap_base,"v_{2}{2,|#Delta#eta|>2}","p");
  leg->Draw();

  c1->Print("FigsFourSpecial/strk_acceptance_AuAu.png");
  c1->Print("FigsFourSpecial/strk_acceptance_AuAu.pdf");

  TH1D* th1d_cos1 = (TH1D*)fin->Get("th1d_cos1");
  TH1D* th1d_sin1 = (TH1D*)fin->Get("th1d_sin1");
  TH1D* th1d_cossum2 = (TH1D*)fin->Get("th1d_cossum2");
  TH1D* th1d_sinsum2 = (TH1D*)fin->Get("th1d_sinsum2");
  TH1D* th1d_cos3 = (TH1D*)fin->Get("th1d_cos3");
  TH1D* th1d_sin3 = (TH1D*)fin->Get("th1d_sin3");
  TH1D* th1d_cos1_north = (TH1D*)fin->Get("th1d_cos1_north");
  TH1D* th1d_sin1_north = (TH1D*)fin->Get("th1d_sin1_north");
  TH1D* th1d_cos1_south = (TH1D*)fin->Get("th1d_cos1_south");
  TH1D* th1d_sin1_south = (TH1D*)fin->Get("th1d_sin1_south");

  th1d_v22_base->Draw("ex0p");
  th1d_v22_unco->Draw("ex0p same");
  th1d_cos1->SetLineColor(kBlack);
  th1d_cos1->SetMarkerColor(kBlack);
  th1d_cos1->SetMarkerStyle(kOpenCircle);
  th1d_sin1->SetLineColor(kBlack);
  th1d_sin1->SetMarkerColor(kBlack);
  th1d_sin1->SetMarkerStyle(kOpenCircle);
  th1d_cos1->Draw("ex0p same");
  th1d_sin1->Draw("ex0p same");

  c1->Print("FigsFourSpecial/strk_acceptance_AuAu_v22andterms.png");
  c1->Print("FigsFourSpecial/strk_acceptance_AuAu_v22andterms.pdf");

  th1d_cos1_north->SetLineColor(kBlack);
  th1d_cos1_north->SetMarkerColor(kBlack);
  th1d_cos1_north->SetMarkerStyle(kOpenCircle);
  th1d_sin1_north->SetLineColor(kBlack);
  th1d_sin1_north->SetMarkerColor(kBlack);
  th1d_sin1_north->SetMarkerStyle(kOpenTriangleUp);
  th1d_cos1_south->SetLineColor(kBlack);
  th1d_cos1_south->SetMarkerColor(kBlack);
  th1d_cos1_south->SetMarkerStyle(kOpenSquare);
  th1d_sin1_south->SetLineColor(kBlack);
  th1d_sin1_south->SetMarkerColor(kBlack);
  th1d_sin1_south->SetMarkerStyle(kOpenTriangleDown);

  th1d_v22gap_base->Draw("ex0p");
  th1d_v22gap_base->SetMinimum(0.0);
  th1d_v22gap_base->SetMaximum(0.199);
  th1d_v22gap_unco->Draw("ex0p same");
  th1d_cos1_north->Draw("ex0p same");
  th1d_cos1_south->Draw("ex0p same");
  th1d_sin1_north->Draw("ex0p same");
  th1d_sin1_south->Draw("ex0p same");

  c1->Print("FigsFourSpecial/strk_acceptance_AuAu_v22gapandterms.png");
  c1->Print("FigsFourSpecial/strk_acceptance_AuAu_v22gapandterms.pdf");

  // TLegend* leg = new TLegend(0.68,0.58,0.88,0.88);
  // leg->AddEntry(th1d_c22gap_base);

  TH1D* th1d_c22gap_base = th1d_v22gap_base->Clone();
  TH1D* th1d_c22gap_unco = th1d_v22gap_unco->Clone();
  th1d_c22gap_base->Multiply(th1d_v22gap_base);
  th1d_c22gap_unco->Multiply(th1d_v22gap_unco);

  c1->Print("FigsFourSpecial/strk_acceptance_AuAu_c22gapandterms.png");
  c1->Print("FigsFourSpecial/strk_acceptance_AuAu_c22gapandterms.pdf");



}
