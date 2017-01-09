void do_systematics()
{

  process("dca","Run16dAu200");

}



void process(const char* systematic, const char* collision)
{

  TCanvas* c1 = new TCanvas();

  TFile* finbase = TFile::Open("all_cumulants_base.root");
  TH1D* v22gap_base = (TH1D*)finbase->Get(Form("th1dR1_v22gap_%s",collision));
  TH1D* v22_base    = (TH1D*)finbase->Get(Form("th1dR1_v22_%s",collision));
  TH1D* v24_base    = (TH1D*)finbase->Get(Form("th1dR1_v24_%s",collision));


  TFile* finsyst = TFile::Open(Form("all_cumulants_%s.root",systematic));
  TH1D* v22gap_syst = (TH1D*)finsyst->Get(Form("th1dR1_v22gap_%s",collision));
  TH1D* v22_syst    = (TH1D*)finsyst->Get(Form("th1dR1_v22_%s",collision));
  TH1D* v24_syst    = (TH1D*)finsyst->Get(Form("th1dR1_v24_%s",collision));

  TF1* fun = new TF1("fun","pol0",0,70);
  double num = -9;
  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.05);

  v22gap_syst->Divide(v22gap_base);
  v22gap_syst->SetMarkerStyle(kFullCircle);
  v22gap_syst->SetMarkerColor(kBlack);
  v22gap_syst->SetLineColor(kBlack);
  v22gap_syst->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  v22gap_syst->GetYaxis()->SetTitle("ratio (sytematic)");
  v22gap_syst->GetXaxis()->SetRangeUser(0,70);
  v22gap_syst->SetMaximum(2.0);
  v22gap_syst->SetMinimum(0.0);
  v22gap_syst->Fit(fun,"R");
  num = fun->GetParameter(0);
  tex->DrawLatex(0.2,0.8,Form("%s systematc, %.2f%%",systematic,(num-1)*100));
  c1->Print(Form("SysFigsFour/sys_%s_%s.png",systematic,collision));
  c1->Print(Form("SysFigsFour/sys_%s_%s.pdf",systematic,collision));

}

