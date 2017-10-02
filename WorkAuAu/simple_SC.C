void simple_SC()
{

  TCanvas* c1 = new TCanvas("c1","");

  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");
  TProfile* tp1f_cent_2323 = (TProfile*)fin->Get("centrality_recursion_0_10");
  TProfile* tp1f_cent_2424 = (TProfile*)fin->Get("centrality_recursion_0_11");
  TProfile* tp1f_cent_22 = (TProfile*)fin->Get("centrality_recursion_0_0");
  TProfile* tp1f_cent_33 = (TProfile*)fin->Get("centrality_recursion_0_1");
  TProfile* tp1f_cent_44 = (TProfile*)fin->Get("centrality_recursion_0_7");

  tp1f_cent_2323->Draw();
  c1->Print("FigsSymmetricCumulants/diagnostic_cent_2323.png");
  c1->Print("FigsSymmetricCumulants/diagnostic_cent_2323.pdf");

  tp1f_cent_2424->Draw();
  c1->Print("FigsSymmetricCumulants/diagnostic_cent_2424.png");
  c1->Print("FigsSymmetricCumulants/diagnostic_cent_2424.pdf");

  tp1f_cent_22->Draw();
  c1->Print("FigsSymmetricCumulants/diagnostic_cent_22.png");
  c1->Print("FigsSymmetricCumulants/diagnostic_cent_22.pdf");

  tp1f_cent_33->Draw();
  c1->Print("FigsSymmetricCumulants/diagnostic_cent_33.png");
  c1->Print("FigsSymmetricCumulants/diagnostic_cent_33.pdf");

  tp1f_cent_44->Draw();
  c1->Print("FigsSymmetricCumulants/diagnostic_cent_44.png");
  c1->Print("FigsSymmetricCumulants/diagnostic_cent_44.pdf");

  TH1D* th1d_cent_2323 = (TH1D*)tp1f_cent_2323->ProjectionX("th1d_cent_2323");
  TH1D* th1d_cent_2424 = (TH1D*)tp1f_cent_2424->ProjectionX("th1d_cent_2424");
  TH1D* th1d_cent_22 = (TH1D*)tp1f_cent_22->ProjectionX("th1d_cent_22");
  TH1D* th1d_cent_33 = (TH1D*)tp1f_cent_33->ProjectionX("th1d_cent_33");
  TH1D* th1d_cent_44 = (TH1D*)tp1f_cent_44->ProjectionX("th1d_cent_44");

  TH1D* th1d_cent_2233 = (TH1D*)th1d_cent_22->Clone();
  th1d_cent_2233->Multiply(th1d_cent_33);
  TH1D* th1d_cent_SC23 = (TH1D*)th1d_cent_2323->Clone();
  th1d_cent_SC23->Add(th1d_cent_2233,-1.0);

  TH1D* th1d_cent_2244 = (TH1D*)th1d_cent_22->Clone();
  th1d_cent_2244->Multiply(th1d_cent_44);
  TH1D* th1d_cent_SC24 = (TH1D*)th1d_cent_2424->Clone();
  th1d_cent_SC24->Add(th1d_cent_2244,-1.0);

  // --- considering passing these as arguments...
  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = -1e-5;
  double ymax = 1e-5;

  // --- do the plotting
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("Symmetric Cumulant");
  empty->GetYaxis()->SetTitleOffset(1.2);
  TLatex* tex_tracks = new TLatex(0.2,0.83,"h^{#pm} 1<|#eta|<3");
  tex_tracks->SetTextSize(0.05);
  tex_tracks->SetNDC();
  tex_tracks->Draw();
  TLatex* tex_system = new TLatex(0.2,0.882,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  tex_system->SetTextSize(0.05);
  tex_system->SetNDC();
  tex_system->Draw();
  // ---
  th1d_cent_SC23->SetMarkerStyle(kFullCircle);
  th1d_cent_SC23->SetMarkerColor(kBlue);
  th1d_cent_SC23->SetLineColor(kBlue);
  th1d_cent_SC23->Draw("ex0p same");
  th1d_cent_SC24->SetMarkerStyle(kFullSquare);
  th1d_cent_SC24->SetMarkerColor(kRed);
  th1d_cent_SC24->SetLineColor(kRed);
  th1d_cent_SC24->Draw("ex0p same");
  TLegend* leg = new TLegend(0.6,0.6,0.8,0.8);
  leg->AddEntry(th1d_cent_SC23,"SC(2,3)","p");
  leg->AddEntry(th1d_cent_SC24,"SC(2,4)","p");
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->Draw();
  c1->Print("FigsSymmetricCumulants/physics_cent.png");

}
