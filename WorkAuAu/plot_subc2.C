void plot_subc2(TH1D*,TH1D*,TH1D*);

void plot_subc2(TH1D*,TH1D*,TH1D*,int);



void plot_subc2(TH1D* th1d_c24, TH1D* th1d_c24aabb, TH1D* th1d_c24abab)
{
  plot_subc2(th1d_c24,th1d_c24aabb,th1d_c24abab,2);
}

void plot_subc2(TH1D* th1d_c24, TH1D* th1d_c24aabb, TH1D* th1d_c24abab, int harm)
{

  TCanvas* c1 = new TCanvas("c1","");

  bool iscent = true;
  bool isntrk = false;

  th1d_c24aabb->SetMarkerStyle(kOpenSquare);
  th1d_c24aabb->SetMarkerColor(kRed);
  th1d_c24aabb->SetLineColor(kRed);
  th1d_c24abab->SetMarkerStyle(kOpenDiamond);
  th1d_c24abab->SetMarkerColor(kBlue);
  th1d_c24abab->SetLineColor(kBlue);
  th1d_c24->SetMarkerStyle(kOpenCircle);
  th1d_c24->SetMarkerColor(kBlack);
  th1d_c24->SetLineColor(kBlack);

  double xmin = 0.0;
  double xmax = 100.0;
  if ( harm == 3 ) xmax = 60.0;
  double ymin = -1e-5;
  double ymax = 1e-5;
  if ( harm == 3 )
  {
  ymin = -1e-5;
  ymax = 1e-5;
  }
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle(Form("v_{%d}",harm));
  empty->GetYaxis()->SetTitleOffset(1.2);
  TLatex* tex_phenix = new TLatex(0.2,0.778,"PHENIX");
  tex_phenix->SetTextSize(0.05);
  tex_phenix->SetNDC();
  tex_phenix->Draw();
  // TLatex* tex_system = new TLatex(0.2,0.80,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  // tex_system->SetTextSize(0.05);
  // tex_system->SetNDC();
  // tex_system->Draw();
  TLatex* tex_tracks = new TLatex(0.2,0.83,"h^{#pm} 1<|#eta|<3");
  tex_tracks->SetTextSize(0.05);
  tex_tracks->SetNDC();
  tex_tracks->Draw();
  TLatex* tex_system = new TLatex(0.2,0.882,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  tex_system->SetTextSize(0.05);
  tex_system->SetNDC();
  tex_system->Draw();
  TLatex latt;
  latt.SetNDC();
  latt.SetTextSize(0.05);
  //latt.SetTextAlign(11);
  //latt.DrawLatex(0.2, 0.71, "Sys. Uncert. 6%");
  latt.DrawLatex(0.35, 0.21, "Sys. Uncert. 6%");
  th1d_c24->Draw("same ex0p");
  TLegend* leg24 = new TLegend(0.66,0.86,0.92,0.92);
  leg24->SetTextSize(0.05);
  leg24->SetFillStyle(0);
  leg24->AddEntry(th1d_c24,Form("v_{%d}{4}",harm),"p");
  leg24->Draw();
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x01.png",harm));
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x01.pdf",harm));
  th1d_c24abab->Draw("same ex0p");
  TLegend* leg24abab = new TLegend(0.66,0.80,0.92,0.86);
  leg24abab->SetTextSize(0.05);
  leg24abab->SetFillStyle(0);
  leg24abab->AddEntry(th1d_c24abab,Form("v_{%d}{4}_{ab|ab}",harm),"p");
  leg24abab->Draw();
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x02.png",harm));
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x02.pdf",harm));
  th1d_c24aabb->Draw("same ex0p");
  TLegend* leg24aabb = new TLegend(0.66,0.74,0.92,0.80);
  leg24aabb->SetTextSize(0.05);
  leg24aabb->SetFillStyle(0);
  leg24aabb->AddEntry(th1d_c24aabb,Form("v_{%d}{4}_{aa|bb}",harm),"p");
  leg24aabb->Draw();
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x03.png",harm));
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x03.pdf",harm));

  delete empty;
  delete c1;

}
