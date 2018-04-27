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
      //if ( err < 0.0012 ) err = 0.0012;
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
  TLatex* latt = new TLatex();
  latt->SetNDC();
  latt->SetTextSize(0.05);
  latt->DrawLatex(0.35, 0.21, "Sys. Uncert. 6%");

  TLegend* leg = new TLegend(0.66,0.87,0.92,0.92);
  leg->AddEntry(th1d_os_v3G,"v_{3}{2,|#Delta#eta|>2}","p");
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  leg->Draw();

  c1->Print(Form("FigsWork/v32.pdf"));
  c1->Print(Form("FigsWork/v32.png"));

  hdummy->Draw();
  th1d_os_v3G->Draw("ex0p same");
  tex_phenix->Draw();
  tex_tracks->Draw();
  tex_system->Draw();

  if ( leg ) delete leg;
  leg = new TLegend(0.61,0.87,0.81,0.92);
  //leg = new TLegend(0.57,0.89,0.77,0.95);
  leg->AddEntry(th1d_os_v3G,"v_{3}{2,|#Delta#eta|>2}","p");
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  //leg->Draw();

  gv3_sys->Draw("E5 same");

  c1->Print(Form("FigsWork/v32and.pdf"));
  c1->Print(Form("FigsWork/v32and.png"));

  // --- get stuff for comparison

  TFile* fjamie = TFile::Open("FilesJamie/fout_v3_ron.root");
  TGraphAsymmErrors* tgae_v3m = (TGraphAsymmErrors*)fjamie->Get("v3mean");
  TGraphAsymmErrors* tgae_v32 = (TGraphAsymmErrors*)fjamie->Get("v3quadmeanplusrms");
  TFile* fjamiesys = TFile::Open("FilesJamie/fout_v3_sys.root");
  TGraphAsymmErrors* tgae_sys_v3m = (TGraphAsymmErrors*)fjamiesys->Get("v3mean");
  TGraphAsymmErrors* tgae_sys_v32 = (TGraphAsymmErrors*)fjamiesys->Get("v3quadmeanplusrms");

  tgae_v32->SetMarkerStyle(kFullSquare);
  tgae_v32->Draw("p");
  tgae_sys_v32->SetFillColorAlpha(kBlack,0.35);
  tgae_sys_v32->Draw("3");

  //if ( leg ) delete leg;
  //leg = new TLegend(0.61,0.82,0.81,0.92);
  //leg = new TLegend(0.57,0.89,0.77,0.95);
  TLegend* leg2 = new TLegend(0.57,0.79,0.77,0.95);
  leg2->AddEntry(th1d_os_v3G,"v_{3}{2,|#Delta#eta|>2}","p");
  leg2->AddEntry(tgae_v32,"#sqrt{#LTv_{3}^{2}#GT} from folding","p");
  leg2->SetTextSize(0.05);
  leg2->SetFillStyle(0);
  leg2->Draw();

  c1->Print(Form("FigsWork/v32andfold.pdf"));
  c1->Print(Form("FigsWork/v32andfold.png"));

  // tgae_v3m->SetMarkerStyle(kFullCircle);
  // tgae_v3m->Draw("p");
  // tgae_sys_v3m->SetFillColorAlpha(kBlack,0.35);
  // tgae_sys_v3m->Draw("3");

  // if ( leg ) delete leg;
  // leg = new TLegend(0.61,0.77,0.81,0.92);
  // leg->AddEntry(th1d_os_v3G,"v_{3}{2,|#Delta#eta|>2}","p");
  // leg->AddEntry(tgae_v32,"v_{3}{RMS,folding}","p");
  // leg->AddEntry(tgae_v3m,"v_{3}{MEAN,folding}","p");
  // leg->SetTextSize(0.05);
  // leg->SetFillStyle(0);
  // leg->Draw();

  // c1->Print(Form("FigsWork/v32andfoldandmean.pdf"));
  // c1->Print(Form("FigsWork/v32andfoldandmean.png"));

  // Phys. Rev. C 88, 014904 (2013)
  // https://drupal.star.bnl.gov/STAR/files/starpublications/199/data.html
  // Fig. 08
  // v3*100 vs cenrality
  // cent (%)   TPC     error   wide gauss      error   delta eta>1     error   FTPC    error
  // 2.5        1.43    0.01    1.44            0.019   1.38            0.01    0.72    0.028
  // 7.5        1.63    0.01    1.67            0.028   1.57            0.01    1.1     0.033
  // 15         1.82    0.0085  1.78            0.036   1.75            0.01    1.22    0.023
  // 25         1.94    0.011   1.94            0.045   1.83            0.01    1.38    0.031
  // 35         2.02    0.015   2.02            0.053   1.87            0.02    1.33    0.039
  // 45         2.03    0.024   2.03            0.062   1.81            0.03    1.19    0.049
  // 55         1.96    0.044   1.96            0.072   1.63            0.06    0.808   0.095
  // 65         1.79    0.11    1.88            0.091   1.09            0.16    0.331   0.15
  // 75         2       0.31    1.64            0.14    0.9             0.4     0.151   0.26
  //double cent[9] = {75,65,55,45,35,25,15,7.5,2.5};
  double cent[9] = {2.5,7.5,15,25,35,45,55,65,75};
  double star_v3T[9]={0};
  double star_v3F[9]={0};
  double star_ev3T[9]={0};
  double star_ev3F[9]={0};
  star_v3T[0] = 1.38;  star_v3F[0] = 0.72 ;   star_ev3T[0] = 0.01;  star_ev3F[0] = 0.028;  // 2.5
  star_v3T[1] = 1.57;  star_v3F[1] = 1.1  ;   star_ev3T[1] = 0.01;  star_ev3F[1] = 0.033;  // 7.5
  star_v3T[2] = 1.75;  star_v3F[2] = 1.22 ;   star_ev3T[2] = 0.01;  star_ev3F[2] = 0.023;  // 15
  star_v3T[3] = 1.83;  star_v3F[3] = 1.38 ;   star_ev3T[3] = 0.01;  star_ev3F[3] = 0.031;  // 25
  star_v3T[4] = 1.87;  star_v3F[4] = 1.33 ;   star_ev3T[4] = 0.02;  star_ev3F[4] = 0.039;  // 35
  star_v3T[5] = 1.81;  star_v3F[5] = 1.19 ;   star_ev3T[5] = 0.03;  star_ev3F[5] = 0.049;  // 45
  star_v3T[6] = 1.63;  star_v3F[6] = 0.808;   star_ev3T[6] = 0.06;  star_ev3F[6] = 0.095;  // 55
  star_v3T[7] = 1.09;  star_v3F[7] = 0.331;   star_ev3T[7] = 0.16;  star_ev3F[7] = 0.15 ;  // 65
  star_v3T[8] = 0.9 ;  star_v3F[8] = 0.151;   star_ev3T[8] = 0.4 ;  star_ev3F[8] = 0.26 ;  // 75
  for ( int i = 0; i < 9; ++i )
    {
      star_v3T[i] /= 100.0;
      star_v3F[i] /= 100.0;
      star_ev3T[i] /= 100.0;
      star_ev3F[i] /= 100.0;
    }
  for ( int i = 0; i < 9; ++i )
    {
      star_v3T[i] *= 0.85;
      star_ev3T[i] *= 0.85;
      star_v3F[i] *= 1.2;
      star_ev3F[i] *= 1.2;
    }
  TGraphErrors* tge_star_v3T = new TGraphErrors(9,cent,star_v3T,0,star_ev3T);
  TGraphErrors* tge_star_v3F = new TGraphErrors(9,cent,star_v3F,0,star_ev3F);
  tge_star_v3T->SetMarkerStyle(kFullStar);
  tge_star_v3T->SetMarkerColor(kRed);
  tge_star_v3T->SetLineColor(kRed);
  tge_star_v3F->SetMarkerStyle(kFullStar);
  tge_star_v3F->SetMarkerColor(kBlue);
  tge_star_v3F->SetLineColor(kBlue);
  tge_star_v3T->SetMarkerSize(2.5);
  tge_star_v3F->SetMarkerSize(2.5);

  hdummy->Draw();
  th1d_os_v3G->Draw("ex0p same");
  gv3_sys->Draw("E5 same");
  tex_phenix->Draw();
  tex_tracks->Draw();
  tex_system->Draw();

  leg->Draw();

  tge_star_v3T->Draw("p");
  tge_star_v3F->Draw("p");

  TLegend* legs = new TLegend(0.20,0.19,0.40,0.35);
  legs->SetHeader("STAR, Phys. Rev. C 88, 014904 (2013)");
  //legs->AddEntry((TObject*)0x0,"STAR, Phys. Rev. C 88, 014904 (2013)","");
  legs->AddEntry(tge_star_v3T,"v_{3}{2,|#Delta#eta|>1}        |#eta|<1   (#times 0.85)","p");
  legs->AddEntry(tge_star_v3F,"v_{3}{FTPC}    2.5<|#eta|<4   (#times 1.2)","p");
  legs->SetTextSize(0.05);
  legs->SetFillStyle(0);
  legs->Draw();

  c1->Print(Form("FigsWork/v32andfoldandSTAR.pdf"));
  c1->Print(Form("FigsWork/v32andfoldandSTAR.png"));

  delete c1;

}

