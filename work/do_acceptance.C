void process(const char*, const char*);
double get_mean(const TH1D*);
void clean(TH1D*);

void do_acceptance()
{
  process("U","Run16dAu200");
  process("Z","Run16dAu200");
  process("U","Run16dAu62");
  process("Z","Run16dAu62");
  process("U","Run16dAu39");
  process("Z","Run16dAu39");
  process("U","Run16dAu20");
  process("Z","Run16dAu20");
}



void process(const char* systematic, const char* collision)
{

  TCanvas* c1 = new TCanvas();

  TFile* finbase = TFile::Open("all_cumulants_acc.root");
  TH1D* v22gap_base = (TH1D*)finbase->Get(Form("th1dR1_v22gap_%s",collision));
  TH1D* v22_base    = (TH1D*)finbase->Get(Form("th1dR1_v22_%s",collision));
  TH1D* v24_base    = (TH1D*)finbase->Get(Form("th1dR1_v24_%s",collision));

  TH1D* v22gap_syst = (TH1D*)finbase->Get(Form("th1dR1%s_v22gap_%s",systematic,collision));
  TH1D* v22_syst    = (TH1D*)finbase->Get(Form("th1dR1%s_v22_%s",systematic,collision));
  TH1D* v24_syst    = (TH1D*)finbase->Get(Form("th1dR1%s_v24_%s",systematic,collision));

  // ---

  v22gap_base->SetMarkerStyle(kFullDiamond);
  v22_base->SetMarkerStyle(kFullCircle);
  v24_base->SetMarkerStyle(kFullSquare);
  v22gap_base->SetMarkerColor(kMagenta+2);
  v22_base->SetMarkerColor(kRed);
  v24_base->SetMarkerColor(kBlue);
  v22gap_syst->SetMarkerStyle(kOpenDiamond);
  v22_syst->SetMarkerStyle(kOpenCircle);
  v24_syst->SetMarkerStyle(kOpenSquare);
  v22gap_syst->SetMarkerColor(kMagenta+2);
  v22_syst->SetMarkerColor(kRed);
  v24_syst->SetMarkerColor(kBlue);

  v22_base->Draw("ex0p");
  v22_base->SetMinimum(0.0);
  v22_base->SetMaximum(0.199);
  v22_base->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  v22_base->GetYaxis()->SetTitle("v_{2}");
  v24_base->Draw("ex0p same");
  v22gap_base->Draw("ex0p same");
  v22_syst->Draw("ex0p same");
  v24_syst->Draw("ex0p same");
  v22gap_syst->Draw("ex0p same");
  TLegend* leg1 = new TLegend(0.48,0.68,0.68,0.88);
  leg1->SetHeader("Alternate");
  leg1->AddEntry(v22_syst,"v_{2}{2}","p");
  leg1->AddEntry(v22gap_syst,"v_{2}{2,|#Delta#eta|>2}","p");
  leg1->AddEntry(v24_syst,"v_{2}{4}","p");
  leg1->SetTextSize(0.045);
  leg1->Draw();
  TLegend* leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetHeader("Corr. terms");
  leg2->AddEntry(v22_base,"v_{2}{2}","p");
  leg2->AddEntry(v22gap_base,"v_{2}{2,|#Delta#eta|>2}","p");
  leg2->AddEntry(v24_base,"v_{2}{4}","p");
  leg2->SetTextSize(0.045);
  leg2->Draw();
  c1->Print(Form("SysFigsFour/accsys_v2all_%s_%s.png",systematic,collision));
  c1->Print(Form("SysFigsFour/accsys_v2all_%s_%s.pdf",systematic,collision));

  // ---

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
  v22gap_syst->SetMaximum(1.5);
  v22gap_syst->SetMinimum(0.5);
  //fun->SetParameter(0,1);
  //fun->FixParameter(0,get_mean(v22gap_syst));
  v22gap_syst->Fit(fun,"","",10,50);
  //fun->Draw("same");
  num = fun->GetParameter(0);
  tex->DrawLatex(0.2,0.8,Form("%s systematic, %.2f%%", systematic, fabs((num-1)*100) ));
  c1->Print(Form("SysFigsFour/accsys_v22gap_%s_%s.png",systematic,collision));
  c1->Print(Form("SysFigsFour/accsys_v22gap_%s_%s.pdf",systematic,collision));

  v22_syst->Divide(v22_base);
  clean(v22_syst);
  v22_syst->SetMarkerStyle(kFullCircle);
  v22_syst->SetMarkerColor(kBlack);
  v22_syst->SetLineColor(kBlack);
  v22_syst->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  v22_syst->GetYaxis()->SetTitle("ratio (sytematic)");
  v22_syst->GetXaxis()->SetRangeUser(0,70);
  v22_syst->SetMaximum(1.5);
  v22_syst->SetMinimum(0.5);
  //fun->SetParameter(0,1);
  //fun->FixParameter(0,get_mean(v22_syst));
  v22_syst->Fit(fun,"","",10,50);
  num = fun->GetParameter(0);
  //fun->Draw("same");
  tex->DrawLatex(0.2,0.8,Form("%s systematic, %.2f%%", systematic, fabs((num-1)*100) ));
  c1->Print(Form("SysFigsFour/accsys_v22_%s_%s.png",systematic,collision));
  c1->Print(Form("SysFigsFour/accsys_v22_%s_%s.pdf",systematic,collision));

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
  c1->Print(Form("SysFigsFour/accsys_v24_%s_%s.png",systematic,collision));
  c1->Print(Form("SysFigsFour/accsys_v24_%s_%s.pdf",systematic,collision));

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
