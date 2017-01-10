void process(const char*, const char*);
double get_mean(const TH1D*);
void clean(TH1D*);

void do_systematics()
{

  process("dca","Run16dAu200");
  process("dtc","Run16dAu200");
  process("zvtx","Run16dAu200");
  process("dca","Run16dAu62");
  process("dtc","Run16dAu62");
  process("zvtx","Run16dAu62");
  process("dca","Run16dAu39");
  process("dtc","Run16dAu39");
  process("zvtx","Run16dAu39");
  process("dca","Run16dAu20");
  process("dtc","Run16dAu20");
  process("zvtx","Run16dAu20");

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
  clean(v22gap_syst);
  v22gap_syst->SetMarkerStyle(kFullCircle);
  v22gap_syst->SetMarkerColor(kBlack);
  v22gap_syst->SetLineColor(kBlack);
  v22gap_syst->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  v22gap_syst->GetYaxis()->SetTitle("ratio (sytematic)");
  v22gap_syst->GetXaxis()->SetRangeUser(0,70);
  v22gap_syst->SetMaximum(1.2);
  v22gap_syst->SetMinimum(0.8);
  //fun->SetParameter(0,1);
  //fun->FixParameter(0,get_mean(v22gap_syst));
  v22gap_syst->Fit(fun,"","",10,50);
  //fun->Draw("same");
  num = fun->GetParameter(0);
  tex->DrawLatex(0.2,0.8,Form("%s systematic, %.2f%%", systematic, fabs((num-1)*100) ));
  c1->Print(Form("SysFigsFour/sys_v22gap_%s_%s.png",systematic,collision));
  c1->Print(Form("SysFigsFour/sys_v22gap_%s_%s.pdf",systematic,collision));

  v22_syst->Divide(v22_base);
  clean(v22_syst);
  v22_syst->SetMarkerStyle(kFullCircle);
  v22_syst->SetMarkerColor(kBlack);
  v22_syst->SetLineColor(kBlack);
  v22_syst->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  v22_syst->GetYaxis()->SetTitle("ratio (sytematic)");
  v22_syst->GetXaxis()->SetRangeUser(0,70);
  v22_syst->SetMaximum(1.2);
  v22_syst->SetMinimum(0.8);
  //fun->SetParameter(0,1);
  //fun->FixParameter(0,get_mean(v22_syst));
  v22_syst->Fit(fun,"","",10,50);
  num = fun->GetParameter(0);
  //fun->Draw("same");
  tex->DrawLatex(0.2,0.8,Form("%s systematic, %.2f%%", systematic, fabs((num-1)*100) ));
  c1->Print(Form("SysFigsFour/sys_v22_%s_%s.png",systematic,collision));
  c1->Print(Form("SysFigsFour/sys_v22_%s_%s.pdf",systematic,collision));

  v24_syst->Divide(v24_base);
  clean(v24_syst);
  v24_syst->SetMarkerStyle(kFullCircle);
  v24_syst->SetMarkerColor(kBlack);
  v24_syst->SetLineColor(kBlack);
  v24_syst->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  v24_syst->GetYaxis()->SetTitle("ratio (sytematic)");
  v24_syst->GetXaxis()->SetRangeUser(0,70);
  v24_syst->SetMaximum(1.5);
  v24_syst->SetMinimum(0.5);
  //fun->SetParameter(0,1);
  //fun->FixParameter(0,get_mean(v24_syst));
  v24_syst->Fit(fun,"","",10,50);
  //fun->Draw("same");
  num = fun->GetParameter(0);
  tex->DrawLatex(0.2,0.8,Form("%s systematic, %.2f%%", systematic, fabs((num-1)*100) ));
  c1->Print(Form("SysFigsFour/sys_v24_%s_%s.png",systematic,collision));
  c1->Print(Form("SysFigsFour/sys_v24_%s_%s.pdf",systematic,collision));

}

double get_mean(const TH1D* h)
{
  int nbins = h->GetNbinsX();
  double total = 0;
  for ( int i = 0; i < nbins; ++i )
    {
      double content = h->GetBinContent(i+1);
      if ( content > 0 ) total += content;
    }
  double final = total/nbins;
  cout << final << endl;
  return final;
}

void clean(TH1D* h)
{
  int nbins = h->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      double content = h->GetBinContent(i+1);
      if ( content < 0 ) h->SetBinError(i+1,999);
    }
}
