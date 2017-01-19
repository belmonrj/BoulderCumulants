void doit(int, const char*);

void plot_sides()
{

  doit(1,"Run16dAu200");
  doit(2,"Run16dAu200");
  doit(5,"Run16dAu200");
  doit(1,"Run16dAu62");
  doit(2,"Run16dAu62");
  doit(5,"Run16dAu62");
  doit(1,"Run16dAu39");
  doit(2,"Run16dAu39");
  doit(5,"Run16dAu39");
  doit(1,"Run16dAu20");
  doit(2,"Run16dAu20");
  doit(5,"Run16dAu20");

}

void doit(int rebin, const char* system)
{

  TFile* file = TFile::Open("all_cumulants_northsouth.root");

  TH1D* th1d_v22_north = (TH1D*)file->Get(Form("th1dR%d_v22_north_%s",rebin,system));
  TH1D* th1d_v22_south = (TH1D*)file->Get(Form("th1dR%d_v22_south_%s",rebin,system));
  TH1D* th1d_v22_combi = (TH1D*)file->Get(Form("th1dR%d_v22_combined_%s",rebin,system));

  th1d_v22_combi->SetLineColor(kBlack);
  th1d_v22_north->SetLineColor(kBlack);
  th1d_v22_south->SetLineColor(kBlack);

  th1d_v22_combi->SetMarkerColor(kBlue);
  th1d_v22_north->SetMarkerColor(kRed);
  th1d_v22_south->SetMarkerColor(kBlack);

  th1d_v22_combi->SetMarkerStyle(kFullSquare);
  th1d_v22_north->SetMarkerStyle(kFullCircle);
  th1d_v22_south->SetMarkerStyle(kFullDiamond);

  th1d_v22_combi->Draw("ex0p");
  th1d_v22_combi->SetMinimum(0.0);
  th1d_v22_combi->SetMaximum(0.199);
  th1d_v22_combi->GetXaxis()->SetTitle("ntrk");
  th1d_v22_combi->GetYaxis()->SetTitle("v_{2}");
  th1d_v22_north->Draw("ex0p same");
  th1d_v22_south->Draw("ex0p same");
  TLegend* leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetHeader(system);
  leg->AddEntry(th1d_v22_combi,"combined","p");
  leg->AddEntry(th1d_v22_north,"north","p");
  leg->AddEntry(th1d_v22_south,"south","p");
  leg->Draw();
  c1->Print(Form("FigsFour/northsouth_v22_r%d_%s.png",rebin,system));
  c1->Print(Form("FigsFour/northsouth_v22_r%d_%s.pdf",rebin,system));

  TH1D* th1d_v24_north = (TH1D*)file->Get(Form("th1dR%d_v24_north_%s",rebin,system));
  TH1D* th1d_v24_south = (TH1D*)file->Get(Form("th1dR%d_v24_south_%s",rebin,system));
  TH1D* th1d_v24_combi = (TH1D*)file->Get(Form("th1dR%d_v24_combined_%s",rebin,system));

  th1d_v24_combi->SetLineColor(kBlack);
  th1d_v24_north->SetLineColor(kBlack);
  th1d_v24_south->SetLineColor(kBlack);

  th1d_v24_combi->SetMarkerColor(kBlue);
  th1d_v24_north->SetMarkerColor(kRed);
  th1d_v24_south->SetMarkerColor(kBlack);

  th1d_v24_combi->SetMarkerStyle(kFullSquare);
  th1d_v24_north->SetMarkerStyle(kFullCircle);
  th1d_v24_south->SetMarkerStyle(kFullDiamond);

  th1d_v24_combi->Draw("ex0p");
  th1d_v24_combi->SetMinimum(0.0);
  th1d_v24_combi->SetMaximum(0.199);
  th1d_v24_combi->GetXaxis()->SetTitle("ntrk");
  th1d_v24_combi->GetYaxis()->SetTitle("v_{2}");
  th1d_v24_north->Draw("ex0p same");
  th1d_v24_south->Draw("ex0p same");
  leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetHeader(system);
  leg->AddEntry(th1d_v24_combi,"combined","p");
  leg->AddEntry(th1d_v24_north,"north","p");
  leg->AddEntry(th1d_v24_south,"south","p");
  leg->Draw();
  c1->Print(Form("FigsFour/northsouth_v24_r%d_%s.png",rebin,system));
  c1->Print(Form("FigsFour/northsouth_v24_r%d_%s.pdf",rebin,system));

}
