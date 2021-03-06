#include "calc_cumulants.C"
#include "calc_subevents.C"

void clean_histo(TH1D*);
void clean_histo(TH1D*,double,double);

void get_ratios_histos(TFile*, TH1D**, TH1D**, TH1D**, bool);

void compare_to_STAR(TH1D*,TH1D*);

void get_ratios()
{
  // --- get the file; soft link to latest stable analysis with default cuts
  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");
  TH1D* hratio42 = NULL;
  TH1D* hratio64 = NULL;
  TH1D* hratio84 = NULL;
  get_ratios_histos(fin,&hratio42,&hratio64,&hratio84,true);
  cout << "Finished with memory address " << hratio42 << " " << hratio64 << " " << hratio84 << endl;
  compare_to_STAR(hratio42,hratio64);
}

void get_ratios_histos(TFile* fin, TH1D** return_ratio42, TH1D** return_ratio64, TH1D** return_ratio84, bool doplot)
{
  // --- get the k-p correlator histograms from the file
  TProfile* eit_cent = (TProfile*)fin->Get("centrality_recursion_0_6");
  TProfile* six_cent = (TProfile*)fin->Get("centrality_recursion_0_4");
  TProfile* for_cent = (TProfile*)fin->Get("centrality_recursion_0_2");
  TProfile* two_cent = (TProfile*)fin->Get("centrality_recursion_0_0");

  // --- initialize the pointers
  TH1D* v28 = NULL;
  TH1D* v26 = NULL;
  TH1D* v24 = NULL;
  TH1D* v22 = NULL;

  // --- get all the v2{k}, c2{k}, and component histograms
  calc_cumulants(eit_cent, six_cent, for_cent, two_cent,
                &v28,  &v26,  &v24,  &v22,
                1);

  // --- now get the subevent v2{2}

  TProfile* tp1f_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* tp1f_4aabb = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c24a");
  TProfile* tp1f_4abab = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c24b");
  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c22");
  TProfile* tp1f_2aa = (TProfile*)fin->Get("centrality_os_fvtxs_tracks_c22");
  TProfile* tp1f_2bb = (TProfile*)fin->Get("centrality_os_fvtxn_tracks_c22");
  TProfile* tp1f_2ab = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c22");
  TH1D* hv24 = NULL;
  TH1D* hv24aabb = NULL;
  TH1D* hv24abab = NULL;
  TH1D* hv22 = NULL;
  TH1D* hv22ab = NULL;
  TH1D* hc24 = NULL;
  TH1D* hc24aabb = NULL;
  TH1D* hc24abab = NULL;
  TH1D* hc22 = NULL;
  TH1D* hc22ab = NULL;
  calc_subevents(tp1f_for, tp1f_4aabb, tp1f_4abab,
                 tp1f_two, tp1f_2aa, tp1f_2bb, tp1f_2ab,
                 &hv24, &hv24aabb, &hv24abab, &hv22, &hv22ab,
                 &hc24, &hc24aabb, &hc24abab, &hc22, &hc22ab,
                 1);

  // --- now calculate the ratios

  TH1D* hratio42 = (TH1D*)v24->Clone("hratio42");
  hratio42->Divide(hv22ab);
  clean_histo(hratio42,6.5,65.5);

  TH1D* hratio64 = (TH1D*)v26->Clone("hratio64");
  hratio64->Divide(v24);
  clean_histo(hratio64,7.5,60.5);

  TH1D* hratio84 = (TH1D*)v28->Clone("hratio84");
  hratio84->Divide(v24);
  clean_histo(hratio84,9.5,50.5);

  // --- set the return addresses
  *return_ratio42 = hratio42;
  *return_ratio64 = hratio64;
  *return_ratio84 = hratio84;

  if ( !doplot ) return;

  TCanvas* c1 = new TCanvas("c1","");

  double xmin = 0;
  double xmax = 100;
  double ymin = 0.0;
  double ymax = 2.0;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  hdummy->GetYaxis()->SetTitle("Cumulant ratio");
  hdummy->Draw();
  hratio42->SetMarkerStyle(kOpenSquare);
  hratio42->SetMarkerColor(kBlue);
  hratio42->Draw("same ex0p");

  TLatex* tex_phenix = new TLatex(0.2,0.778,"PHENIX");
  tex_phenix->SetTextSize(0.05);
  tex_phenix->SetNDC();
  tex_phenix->Draw();
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
  latt.DrawLatex(0.35, 0.21, "Sys. Uncert. 3%");

  double legleft = 0.55;
  double legbott = 0.87;
  double legrght = 0.9;
  double legtopp = 0.92;
  double legspace = 0.05;
  TLegend* leg42 = new TLegend(legleft,legbott,legrght,legtopp);
  leg42->AddEntry(hratio42,"v_{2}{4}/v_{2}{2,|#Delta#eta|>2}","p");
  leg42->SetTextSize(0.05);
  leg42->Draw();

  c1->Print("FigsRatio/cumu_ratio_24.png");
  c1->Print("FigsRatio/cumu_ratio_24.pdf");

  hratio64->SetMarkerStyle(kOpenCircle);
  hratio64->SetMarkerColor(kBlack);
  hratio64->Draw("same ex0p");

  TLegend* leg64 = new TLegend(legleft,legbott-legspace,legrght,legtopp-legspace);
  leg64->AddEntry(hratio64,"v_{2}{6}/v_{2}{4}","p");
  leg64->SetTextSize(0.05);
  leg64->Draw();

  c1->Print("FigsRatio/cumu_ratio_246.png");
  c1->Print("FigsRatio/cumu_ratio_246.pdf");

  hratio84->SetMarkerStyle(kFullDiamond);
  hratio84->SetMarkerColor(kGreen+2);
  hratio84->Draw("same ex0p");

  TLegend* leg84 = new TLegend(legleft,legbott-2*legspace,legrght,legtopp-2*legspace);
  leg84->AddEntry(hratio84,"v_{2}{8}/v_{2}{4}","p");
  leg84->SetTextSize(0.05);
  leg84->Draw();

  c1->Print("FigsRatio/cumu_ratio_2468.png");
  c1->Print("FigsRatio/cumu_ratio_2468.pdf");

  delete hdummy;
  delete c1;

}

void clean_histo(TH1D* h)
{
  int nbins = h->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      double cen = h->GetBinCenter(i+1);
      double val = h->GetBinContent(i+1);
      double err = h->GetBinError(i+1);
      if ( err == 0 || err > 0.5 )
        {
          h->SetBinContent(i+1,-9);
          h->SetBinError(i+1,9999);
        }
    }
}

void clean_histo(TH1D* h, double low, double high)
{
  int nbins = h->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      double cent = h->GetBinCenter(i+1);
      if ( cent < low || cent > high )
        {
          h->SetBinContent(i+1,-9);
          h->SetBinError(i+1,9999);
        }
    }
}

void compare_to_STAR(TH1D* hratio42, TH1D* hratio64)
{

  // -----------------------------------------------------------------------------
  // --- STAR data ---------------------------------------------------------------
  // J. Adams et al, Phys. Rev. C72 (2005) 014904
  // arXiv:nucl-ex/0409033
  // https://drupal.star.bnl.gov/STAR/files/starpublications/48/data.html
  // https://drupal.star.bnl.gov/STAR/files/starpublications/48/Figure_29a.html
  // --- figure 32 shows the v2{4}/v2{2}, but no date file is given
  // --- so we calculate it ourselves
  double star_cent[9] = {75,65,55,45,35,25,15,7.5,2.5};
  double star_v22[9]={0};
  double star_v24[9]={0};
  double star_v26[9]={0};
  double star_v2LYZS[9]={0};
  double star_v2LYZP[9]={0};
  double star_ev22[9]={0};
  double star_ev24[9]={0};
  double star_ev26[9]={0};
  double star_ev2LYZS[9]={0};
  double star_ev2LYZP[9]={0};
  star_v22[0] = 6.88;  star_v24[0] = -9.0;   star_v26[0] = -9.0;   // 75
  star_v22[1] = 7.25;  star_v24[1] = 5.68;   star_v26[1] = 5.65;   // 65
  star_v22[2] = 7.59;  star_v24[2] = 6.18;   star_v26[2] = 6.01;   // 55
  star_v22[3] = 7.64;  star_v24[3] = 6.43;   star_v26[3] = 6.24;   // 45
  star_v22[4] = 7.29;  star_v24[4] = 6.33;   star_v26[4] = 6.14;   // 35
  star_v22[5] = 6.42;  star_v24[5] = 5.66;   star_v26[5] = 5.45;   // 25
  star_v22[6] = 4.97;  star_v24[6] = 4.27;   star_v26[6] = 4.01;   // 15
  star_v22[7] = 3.55;  star_v24[7] = 2.53;   star_v26[7] = 2.48;   // 7.5
  star_v22[8] = 2.41;  star_v24[8] = -9.0;   star_v26[8] = 2.08;   // 2.5
  star_ev22[0] = 0.052 ;  star_ev24[0] = 0    ;  star_ev26[0] = 0   ; // 75
  star_ev22[1] = 0.029 ;  star_ev24[1] = 0.35 ;  star_ev26[1] = 1.54; // 65
  star_ev22[2] = 0.018 ;  star_ev24[2] = 0.1  ;  star_ev26[2] = 0.27; // 55
  star_ev22[3] = 0.013 ;  star_ev24[3] = 0.045;  star_ev26[3] = 0.08; // 45
  star_ev22[4] = 0.0094;  star_ev24[4] = 0.026;  star_ev26[4] = 0.03; // 35
  star_ev22[5] = 0.0075;  star_ev24[5] = 0.02 ;  star_ev26[5] = 0.02; // 25
  star_ev22[6] = 0.0066;  star_ev24[6] = 0.022;  star_ev26[6] = 0.03; // 15
  star_ev22[7] = 0.0088;  star_ev24[7] = 0.066;  star_ev26[7] = 0.13; // 7.5
  star_ev22[8] = 0.0096;  star_ev24[8] = 0    ;  star_ev26[8] = 0.2 ; // 2.5

  TCanvas* c1 = new TCanvas("c1","");

  double xmin = 0;
  double xmax = 100;
  double ymin = 0.0;
  double ymax = 2.0;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->GetXaxis()->SetTitle("Centrality (%)");
  hdummy->GetYaxis()->SetTitle("Cumulant ratio");
  hdummy->Draw();
  hratio42->SetMarkerStyle(kOpenSquare);
  hratio42->SetMarkerColor(kBlue);
  hratio42->Draw("same ex0p");

  TLatex* tex_phenix = new TLatex(0.2,0.778,"PHENIX");
  tex_phenix->SetTextSize(0.05);
  tex_phenix->SetNDC();
  tex_phenix->Draw();
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
  latt.DrawLatex(0.35, 0.21, "Sys. Uncert. 3%");

  double legleft = 0.55;
  double legbott = 0.87;
  double legrght = 0.9;
  double legtopp = 0.92;
  double legspace = 0.05;
  TLegend* leg42 = new TLegend(legleft,legbott,legrght,legtopp);
  leg42->AddEntry(hratio42,"v_{2}{4}/v_{2}{2,|#Delta#eta|>2}","p");
  leg42->SetTextSize(0.05);
  leg42->Draw();

  double star_ratio42[9];
  double estar_ratio42[9];
  for ( int i = 0; i < 9; ++i )
    {
      star_ratio42[i] = star_v24[i]/star_v22[i];
      estar_ratio42[i] = star_ratio42[i]*sqrt( pow(star_ev22[i]/star_v22[i],2) + pow(star_ev24[i]/star_v24[i],2) );
    }

  TGraphErrors* tge_star_ratio42 = new TGraphErrors(9,star_cent,star_ratio42,0,estar_ratio42);
  tge_star_ratio42->SetMarkerStyle(kFullStar);
  tge_star_ratio42->SetMarkerColor(kBlue);
  tge_star_ratio42->SetMarkerSize(3.5);
  tge_star_ratio42->Draw("p");

  c1->Print("FigsRatio/star_cumu_ratio_24.png");
  c1->Print("FigsRatio/star_cumu_ratio_24.pdf");

  hratio64->SetMarkerStyle(kOpenCircle);
  hratio64->SetMarkerColor(kBlack);
  hratio64->Draw("same ex0p");

  TLegend* leg64 = new TLegend(legleft,legbott-legspace,legrght,legtopp-legspace);
  leg64->AddEntry(hratio64,"v_{2}{6}/v_{2}{4}","p");
  leg64->SetTextSize(0.05);
  leg64->Draw();

  double star_ratio64[9];
  double estar_ratio64[9];
  for ( int i = 0; i < 9; ++i )
    {
      star_ratio64[i] = star_v26[i]/star_v24[i];
      if ( star_v26[i] == -9 ) star_ratio64[i] = -9;
      estar_ratio64[i] = star_ratio64[i]*sqrt( pow(star_ev26[i]/star_v26[i],2) + pow(star_ev24[i]/star_v24[i],2) );
    }

  TGraphErrors* tge_star_ratio64 = new TGraphErrors(9,star_cent,star_ratio64,0,estar_ratio64);
  tge_star_ratio64->SetMarkerStyle(kFullStar);
  tge_star_ratio64->SetMarkerColor(kBlack);
  tge_star_ratio64->SetMarkerSize(3.5);
  tge_star_ratio64->Draw("p");

  c1->Print("FigsRatio/star_cumu_ratio_246.png");
  c1->Print("FigsRatio/star_cumu_ratio_246.pdf");

}

