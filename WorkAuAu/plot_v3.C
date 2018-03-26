#include "hsqrt.C"

void doit(const char*);

void plot_v3()
{
  doit("12634");
}

void doit(const char* handle)
{

  TCanvas* c1 = new TCanvas("c1","");

  int rebin = 2;

  TFile* fin = TFile::Open(Form("input/histos_%s.root",handle));



  TProfile* tp1f_two_os = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c32");
  TProfile* tp1f_G_two_os = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c32"); // scalar product north*south
  tp1f_two_os->Rebin(rebin);
  tp1f_G_two_os->Rebin(rebin);

  TH1D* th1d_os_v32 = hsqrt(tp1f_two_os);
  TH1D* th1d_os_v3G = hsqrt(tp1f_G_two_os);

  // --- get the systmatics histos
  TH1D* gv3_sys = (TH1D*) th1d_os_v3G->Clone("gv3_sys");
  gv3_sys->SetMarkerStyle(0);
  gv3_sys->SetMarkerSize(0);
  gv3_sys->SetFillColorAlpha(kMagenta+2, 0.35);
  for ( int i = 0; i < gv3_sys->GetNbinsX(); ++i )
  {
    double y = gv3_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.0012 ) err = 0.0012;
    if ( y > 0 ) gv3_sys->SetBinError(i, err);
  } // i
  gv3_sys->GetXaxis()->SetRangeUser(0,67);

  th1d_os_v32->SetMarkerColor(kRed);
  th1d_os_v32->SetMarkerStyle(kFullSquare);
  th1d_os_v3G->SetMarkerColor(kMagenta+2);
  th1d_os_v3G->SetMarkerStyle(kFullDiamond);
  th1d_os_v3G->SetMarkerSize(1.9);

  //TH2D* hdummy = new TH2D("hdummy","", 1,0.0,100.0, 1,0.0,0.1);
  //TH2D* hdummy = new TH2D("hdummy","", 1,0.0,70.0, 1,0.0,0.04);
  TH2D* hdummy = new TH2D("hdummy","", 1,0.0,70.0, 1,0.0,0.02);
  hdummy->Draw();
  hdummy->GetYaxis()->SetTitle("v_{3}");
  hdummy->GetYaxis()->SetTitleOffset(1.2);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  //gv3_sys->Draw("E5 same");
  th1d_os_v3G->Draw("ex0p same");

  TLatex* tex_phenix = new TLatex(0.2,0.778,"PHENIX");
  tex_phenix->SetTextSize(0.05);
  tex_phenix->SetNDC();
  tex_phenix->Draw();
  // TLatex* tex_system = new TLatex(0.2,0.83,"Au+Au #sqrt{s_{NN}} = 200 GeV");
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

  TLegend* leg = new TLegend(0.66,0.87,0.92,0.92);
  leg->AddEntry(th1d_os_v3G,"v_{3}{2,|#Delta#eta|>2}","p");
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  leg->Draw();

  c1->Print(Form("FigsWork/v32.pdf"));
  c1->Print(Form("FigsWork/v32.png"));

  // --- get stuff for comparison

  TFile* fjamie = TFile::Open("FilesJamie/fout_v3_ron.root");
  // KEY: TGraphAsymmErrors     v3mean;1
  // KEY: TGraphAsymmErrors     v3rms;1
  // KEY: TGraphAsymmErrors     v3quadmeanplusrms;1
  TGraphAsymmErrors* tgae_v3m = (TGraphAsymmErrors*)fjamie->Get("v3mean");
  TGraphAsymmErrors* tgae_v32 = (TGraphAsymmErrors*)fjamie->Get("v3quadmeanplusrms");

  tgae_v32->SetMarkerStyle(kFullSquare);
  tgae_v32->Draw("p");

  if ( leg ) delete leg;
  leg = new TLegend(0.66,0.82,0.92,0.92);
  leg->AddEntry(th1d_os_v3G,"v_{3}{2,|#Delta#eta|>2}","p");
  leg->AddEntry(tgae_v32,"v_{3}{RMS,folding}","p");
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  leg->Draw();

  c1->Print(Form("FigsWork/v32andfold.pdf"));
  c1->Print(Form("FigsWork/v32andfold.png"));

  tgae_v3m->SetMarkerStyle(kFullCircle);
  tgae_v3m->Draw("p");

  if ( leg ) delete leg;
  leg = new TLegend(0.66,0.77,0.92,0.92);
  leg->AddEntry(th1d_os_v3G,"v_{3}{2,|#Delta#eta|>2}","p");
  leg->AddEntry(tgae_v32,"v_{3}{RMS,folding}","p");
  leg->AddEntry(tgae_v3m,"v_{3}{MEAN,folding}","p");
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  leg->Draw();

  c1->Print(Form("FigsWork/v32andfoldandmean.pdf"));
  c1->Print(Form("FigsWork/v32andfoldandmean.png"));

  delete c1;

}
