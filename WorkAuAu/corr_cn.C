void corr_cn()
{

  TCanvas* c1 = new TCanvas("c1","");

  TFile* fin = TFile::Open("input/histos_11811.root");
  TH2D* histo = (TH2D*)fin->Get("th2d_nfvtxt_centrality");
  TH2D* hista = (TH2D*)fin->Get("th2d_nfvtxt_centralityA");
  TProfile* hista_px = hista->ProfileX("hista_px");
  TProfile* hista_py = hista->ProfileY("hista_py");

  histo->Draw("col");
  histo->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
  histo->GetXaxis()->SetRangeUser(0,650);
  histo->GetYaxis()->SetTitle("Centrality (%)");
  c1->SetLogz();
  c1->Print("FigsCorrelation/corr_2d.png");
  c1->Print("FigsCorrelation/corr_2d.pdf");

  hista->Draw("col");
  hista->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
  hista->GetXaxis()->SetRangeUser(0,650);
  hista->GetYaxis()->SetTitle("Centrality (%)");
  c1->Print("FigsCorrelation/corr_2dA.png");
  c1->Print("FigsCorrelation/corr_2dA.pdf");

  hista_px->Draw("same l");
  hista_px->SetLineColor(kBlack);
  hista_px->SetLineWidth(3);
  hista_px->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
  hista_px->GetXaxis()->SetRangeUser(0,650);
  hista_px->GetYaxis()->SetTitle("Centrality (%)");
  c1->Print("FigsCorrelation/corr_2dandprofilex.png");
  c1->Print("FigsCorrelation/corr_2dandprofilex.pdf");
  TLatex latt;
  latt.SetNDC();
  latt.SetTextSize(0.05);
  latt.DrawLatex(0.50 - 0.20, 0.95 - 0.1 - 0.0, "Au+Au #sqrt{s_{_{NN}}} = 200 GeV");
  latt.DrawLatex(0.50 - 0.20, 0.95 - 0.1 - 0.06, "Tracks in FVTX: h^{#pm}, 1<|#eta|<3");
  latt.DrawLatex(0.50 - 0.20, 0.95 - 0.1 - 0.12, "Centrality (BBC): h^{#pm}, 3.1<|#eta|<3.9");
  c1->Print("FigsCorrelation/correlation_centrality_nfvtxt.png");
  c1->Print("FigsCorrelation/correlation_centrality_nfvtxt.pdf");

  hista_px->Draw();
  c1->Print("FigsCorrelation/corr_profilex.png");
  c1->Print("FigsCorrelation/corr_profilex.pdf");

  hista_py->Draw();
  hista_py->GetYaxis()->SetTitle("N^{FVTX}_{tracks}");
  //hista_py->GetXaxis()->SetRangeUser(0,100); // looks very bad
  hista_py->GetXaxis()->SetTitle("Centrality (%)");
  c1->Print("FigsCorrelation/corr_profiley.png");
  c1->Print("FigsCorrelation/corr_profiley.pdf");

}
