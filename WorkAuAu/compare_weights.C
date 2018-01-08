#include "systematics_helper.C"
#include "hsqrt.C"

void takefile(TFile*, const char*, int);

void compare_weights()
{
  TFile* file = TFile::Open("input/histos_12579.root"); // centrality based qvrc
  takefile(file,"wght",2);
  takefile(file,"wght",3);
  takefile(file,"wght",4);
}

void takefile(TFile* file, const char* systype, int harmonic)
{

  int rebin = 2;

  bool isacce = false;
  if ( strcmp(systype,"acce") == 0 ) isacce = true;

  // --- make sure both files are not null
  if ( !file || !file )
    {
      cout << "One or more files missing for " << systype << ": " << file << " " << file << endl;
      return;
    }

  // --- get the <<2>> and <<4>> (3rd harmonic)
  TProfile* for_base = NULL;
  TProfile* two_base = NULL;
  TProfile* for_eval = NULL;
  TProfile* two_eval = NULL;
  if ( harmonic == 2 )
    {
      for_base = (TProfile*)file->Get("centrality_recursion_0_2");
      two_base = (TProfile*)file->Get("centrality_recursion_0_0");
      for_eval = (TProfile*)file->Get("centrality_spw_recursion_0_2");
      two_eval = (TProfile*)file->Get("centrality_spw_recursion_0_0");
    }
  if ( harmonic == 3 )
    {
      for_base = (TProfile*)file->Get("centrality_recursion_0_3");
      two_base = (TProfile*)file->Get("centrality_recursion_0_1");
      for_eval = (TProfile*)file->Get("centrality_spw_recursion_0_3");
      two_eval = (TProfile*)file->Get("centrality_spw_recursion_0_1");
    }
  if ( harmonic == 4 )
    {
      for_base = (TProfile*)file->Get("centrality_recursion_0_9");
      two_base = (TProfile*)file->Get("centrality_recursion_0_7");
      for_eval = (TProfile*)file->Get("centrality_spw_recursion_0_9");
      two_eval = (TProfile*)file->Get("centrality_spw_recursion_0_7");
    }

  // --- check for existence of histograms, exit if missing
  if ( for_base == NULL ||  two_base == NULL ||  for_eval == NULL ||  two_eval == NULL )
    {
      cout << "One or more histograms missing for " << systype << ": \n";
      cout << "for_base " << for_base << " \n";
      cout << "two_base " << two_base << " \n";
      cout << "for_eval " << for_eval << " \n";
      cout << "two_eval " << two_eval << " \n";
      cout << endl;
      return;
    }


  for_base->Rebin(rebin);
  two_base->Rebin(rebin);
  if ( !isacce )
    {
      for_eval->Rebin(rebin);
      two_eval->Rebin(rebin);
    }

  // --- use a random number generator to prevent over-writing histograms (a funny ROOT feature)
  double rand = gRandom->Rndm();
  int helper = rand*10000;

  // --- get the extra base histos
  TH1D* th1d_base_for = for_base->ProjectionX(Form("th1d_base_for_%d",helper)); // <4>
  TH1D* th1d_base_two = two_base->ProjectionX(Form("th1d_base_two_%d",helper)); // <2>
  TH1D* th1d_base_222 = (TH1D*)th1d_base_two->Clone(Form("th1d_base_222_%d",helper)); // 2<2>^2       (for the 4p)
  th1d_base_222->Multiply(th1d_base_two);
  th1d_base_222->Scale(2);
  TH1D* th1d_base_c24 = (TH1D*)th1d_base_for->Clone("th1d_base_c24"); // c2{4} = <4> - 2<2>^2
  th1d_base_c24->Add(th1d_base_222,-1);

  // --- get the extra eval histos
  TH1D* th1d_eval_for = for_eval->ProjectionX(Form("th1d_eval_for_%d",helper)); // <4>
  TH1D* th1d_eval_two = two_eval->ProjectionX(Form("th1d_eval_two_%d",helper)); // <2>
  TH1D* th1d_eval_222 = (TH1D*)th1d_eval_two->Clone(Form("th1d_eval_222_%d",helper)); // 2<2>^2       (for the 4p)
  th1d_eval_222->Multiply(th1d_eval_two);
  th1d_eval_222->Scale(2);
  TH1D* th1d_eval_c24 = (TH1D*)th1d_eval_for->Clone("th1d_eval_c24"); // c2{4} = <4> - 2<2>^2
  th1d_eval_c24->Add(th1d_eval_222,-1);


  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = -1e-4;
  double ymax = 1e-4;
  // if ( iscent ) xmax = 100.0;
  // if ( isntrk && !islowzoom ) xmax = 650.0;



  // --- four particle components and cumulants

  //-- setup canvas
  //-- Margins
  float Lmarg = 0.14;
  float Rmarg = 0.05;
  // float Bmarg = 0.10;
  // float Bmarg = 0.14; // not quite enough
  //float Bmarg = 0.2; // a little too much
  float Bmarg = 0.16;
  float Tmarg = 0.02;

  double w = 800 / (1 + Lmarg + Rmarg);
  double h = 900 / (1 + Bmarg + Tmarg);

  TCanvas *ccomp4 = new TCanvas("ccomp4", "", w, h);
  ccomp4->SetMargin(0, 0, 0, 0);

  ccomp4->cd();
  TPad *pcomp4 = new TPad("pcomp4", "comp4", 0, 0.5, 1, 1);
  pcomp4->SetMargin(Lmarg, Rmarg, 0, 0.1);
  pcomp4->SetTicks(1, 1);
  pcomp4->Draw();

  ccomp4->cd();
  TPad *pcumu4 = new TPad("pcumu4", "cumu4", 0, 0, 1, 0.5);
  pcumu4->SetMargin(Lmarg, Rmarg, 0.22, 0);
  pcumu4->SetTicks(1, 1);
  pcumu4->Draw();

  //-- plot
  pcomp4->cd();
  ymin = -1e-5;
  ymax = 1e-4;
  if ( harmonic == 3 )
    {
      ymin = -1e-6;
      ymax = 1e-5;
      ymin = -5e-7;
      ymax = 6e-6; // to get the hash mark
    }
  if ( harmonic == 4 )
    {
      ymin = -1e-6;
      ymax = 1e-5;
      ymin = -5e-7;
      ymax = 6e-6; // to get the hash mark
    }
  TH2D* empty_comp4 = new TH2D("empty_comp4","",1,xmin,xmax,1,ymin,ymax);
  empty_comp4->Draw();
  empty_comp4->GetXaxis()->SetLabelSize(0.0);
  empty_comp4->GetXaxis()->SetTitleSize(0.0);
  empty_comp4->GetYaxis()->SetLabelFont(62);
  empty_comp4->GetYaxis()->SetTitleFont(62);
  empty_comp4->GetYaxis()->SetLabelSize(0.08);
  empty_comp4->GetYaxis()->SetTitleSize(0.08);
  empty_comp4->GetYaxis()->SetTitle("components");
  empty_comp4->GetYaxis()->SetTitleOffset(0.9);
  th1d_base_222->SetMarkerStyle(kFullCircle);
  th1d_base_222->SetMarkerColor(kRed);
  th1d_base_222->SetLineColor(kBlack);
  th1d_base_222->Draw("same ex0p");
  th1d_base_for->SetMarkerStyle(kFullSquare);
  th1d_base_for->SetMarkerColor(kBlue);
  th1d_base_for->SetLineColor(kBlack);
  th1d_base_for->Draw("same ex0p");
  th1d_eval_222->SetMarkerStyle(kOpenCircle);
  th1d_eval_222->SetMarkerColor(kRed);
  th1d_eval_222->SetLineColor(kBlack);
  th1d_eval_222->Draw("same ex0p");
  th1d_eval_for->SetMarkerStyle(kOpenSquare);
  th1d_eval_for->SetMarkerColor(kBlue);
  th1d_eval_for->SetLineColor(kBlack);
  th1d_eval_for->Draw("same ex0p");
  TLine *cline = new TLine(xmin,0,xmax,0);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  TLegend* leg_comp4 = new TLegend(0.165,0.70,0.4,0.85);
  leg_comp4->SetTextFont(62);
  leg_comp4->SetTextSize(0.08);
  leg_comp4->SetFillStyle(0);
  leg_comp4->AddEntry(th1d_base_222,"2#LT#LT2#GT#GT^{2}","p");
  leg_comp4->AddEntry(th1d_base_for,"#LT#LT4#GT#GT","p");
  leg_comp4->Draw();

  //-- ratio
  pcumu4->cd();
  ymin = -1.4999e-5;
  ymax = 1.4999e-5;
  if ( harmonic == 3 )
    {
      ymin = -1.4999e-6;
      ymax = 1.4999e-6;
      ymin = -0.4999e-6;
      ymax = 0.4999e-6;
      ymin = -0.3999e-6;
      ymax = 0.3999e-6;
    }
  if ( harmonic == 4 )
    {
      ymin = -1.4999e-6;
      ymax = 1.4999e-6;
      ymin = -0.3999e-6;
      ymax = 0.3999e-6;
    }
  TH2D* empty_cumu4 = new TH2D("empty_cumu4","",1,xmin,xmax,1,ymin,ymax);
  empty_cumu4->Draw();
  // if ( iscent ) empty_cumu4->GetXaxis()->SetTitle("Centrality (%)");
  // if ( isntrk ) empty_cumu4->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty_cumu4->GetXaxis()->SetTitle("Centrality (%)");
  empty_cumu4->GetXaxis()->SetLabelFont(62);
  empty_cumu4->GetXaxis()->SetTitleFont(62);
  empty_cumu4->GetXaxis()->SetLabelSize(0.08);
  empty_cumu4->GetXaxis()->SetTitleSize(0.08);
  empty_cumu4->GetYaxis()->SetLabelFont(62);
  empty_cumu4->GetYaxis()->SetTitleFont(62);
  empty_cumu4->GetYaxis()->SetLabelSize(0.08);
  empty_cumu4->GetYaxis()->SetTitleSize(0.08);
  empty_cumu4->GetYaxis()->SetTitle("cumulant");
  empty_cumu4->GetYaxis()->SetTitleOffset(0.9);
  th1d_base_c24->SetMarkerStyle(kFullCircle);
  th1d_base_c24->SetLineColor(kBlack);
  th1d_base_c24->Draw("same ex0p");
  th1d_eval_c24->SetMarkerStyle(kOpenCircle);
  th1d_eval_c24->SetLineColor(kBlack);
  th1d_eval_c24->Draw("same ex0p");
  TLegend* leg_cumu4 = new TLegend(0.165,0.87,0.4,0.97);
  leg_cumu4->SetTextFont(62);
  leg_cumu4->SetTextSize(0.08);
  leg_cumu4->SetFillStyle(0);
  leg_cumu4->AddEntry(th1d_base_c24,Form("c_{%d}{4} = -v_{%d}^{4}",harmonic,harmonic),"p");
  leg_cumu4->Draw();
  cline->Draw();
  ccomp4->Print(Form("FigsWork/helpme_h%d_%s_cumulant4.png",harmonic,systype));
  ccomp4->Print(Form("FigsWork/helpme_h%d_%s_cumulant4.pdf",harmonic,systype));
  delete ccomp4;
  delete empty_cumu4;
  delete empty_comp4;
  delete leg_cumu4;
  delete leg_comp4;

  TH1D* vn2_base = NULL;
  TH1D* vn2_eval = NULL;
  vn2_base = hsqrt(two_base);
  vn2_eval = hsqrt(two_eval);
  char varname[5];
  sprintf(varname,"v%d2",harmonic);
  crunch(vn2_base,vn2_eval,systype,varname,0,100,1,70);

}

