#include "calc_cumulants.C"
#include "calc_subevents.C"

void takefiles(TFile*, TFile*, const char*);

void crunch(TProfile*, TProfile*, const char*, const char*);

void crunch(TH1D*, TH1D*, const char*, const char*, double, double, double, double);



void get_sys()
{

  TFile* fbase = NULL;
  TFile* feval = NULL;

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12290.root");
  takefiles(fbase,feval,"dcar");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12195.root");
  takefiles(fbase,feval,"zvtx");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12194.root");
  takefiles(fbase,feval,"chi2");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12289.root");
  takefiles(fbase,feval,"nhit");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12420.root");
  feval = TFile::Open("input/histos_12432.root");
  takefiles(fbase,feval,"qrbr");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12420.root");
  feval = TFile::Open("input/histos_12555.root");
  takefiles(fbase,feval,"code");
  fbase->Close();
  feval->Close();

  //fbase = TFile::Open("input/histos_12581.root"); no q-vector recentering
  fbase = TFile::Open("input/histos_12579.root"); // cent-based
  feval = TFile::Open("input/histos_12587.root");
  takefiles(fbase,feval,"nfqr");
  fbase->Close();
  feval->Close();

}

void takefiles(TFile* fbase, TFile* feval, const char* systype)
{

  if ( !fbase || !feval )
    {
      cout << "One or more files missing " << fbase << " " << feval << endl;
      return;
    }

  TProfile* eit_base = (TProfile*)fbase->Get("centrality_recursion_0_6");
  TProfile* six_base = (TProfile*)fbase->Get("centrality_recursion_0_4");
  TProfile* for_base = (TProfile*)fbase->Get("centrality_recursion_0_2");
  TProfile* two_base = (TProfile*)fbase->Get("centrality_recursion_0_0");
  TH1D* v28base = NULL;
  TH1D* v26base = NULL;
  TH1D* v24base = NULL;
  TH1D* v22base = NULL;
  TH1D* c28base = NULL;
  TH1D* c26base = NULL;
  TH1D* c24base = NULL;
  TH1D* c22base = NULL;
  calc_cumulants(eit_base,six_base,for_base,two_base,&v28base,&v26base,&v24base,&v22base,&c28base,&c26base,&c24base,&c22base,1);
  TProfile* eit_eval = (TProfile*)feval->Get("centrality_recursion_0_6");
  TProfile* six_eval = (TProfile*)feval->Get("centrality_recursion_0_4");
  TProfile* for_eval = (TProfile*)feval->Get("centrality_recursion_0_2");
  TProfile* two_eval = (TProfile*)feval->Get("centrality_recursion_0_0");
  TH1D* v28eval = NULL;
  TH1D* v26eval = NULL;
  TH1D* v24eval = NULL;
  TH1D* v22eval = NULL;
  TH1D* c28eval = NULL;
  TH1D* c26eval = NULL;
  TH1D* c24eval = NULL;
  TH1D* c22eval = NULL;
  calc_cumulants(eit_eval,six_eval,for_eval,two_eval,&v28eval,&v26eval,&v24eval,&v22eval,&c28eval,&c26eval,&c24eval,&c22eval,1);
  crunch(v22base,v22eval,systype,"cent_v22",0,100,1,93);
  crunch(v24base,v24eval,systype,"cent_v24",0,100,6,65);
  crunch(v26base,v26eval,systype,"cent_v26",0,100,6,60);
  crunch(v28base,v28eval,systype,"cent_v28",0,100,10,50);

  // ---

  TProfile* base_for = (TProfile*)fbase->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* base_4aabb = (TProfile*)fbase->Get("centrality_os_fvtxsfvtxn_tracks_c24a");
  TProfile* base_4abab = (TProfile*)fbase->Get("centrality_os_fvtxsfvtxn_tracks_c24b");
  TProfile* base_two = (TProfile*)fbase->Get("centrality_os_fvtxc_tracks_c22");
  TProfile* base_2aa = (TProfile*)fbase->Get("centrality_os_fvtxs_tracks_c22");
  TProfile* base_2bb = (TProfile*)fbase->Get("centrality_os_fvtxn_tracks_c22");
  TProfile* base_2ab = (TProfile*)fbase->Get("centrality_os_fvtxsfvtxn_tracks_c22");
  TH1D* hbase_v24 = NULL;
  TH1D* hbase_v24aabb = NULL;
  TH1D* hbase_v24abab = NULL;
  TH1D* hbase_v22 = NULL;
  TH1D* hbase_v22ab = NULL;
  TH1D* hbase_c24 = NULL;
  TH1D* hbase_c24aabb = NULL;
  TH1D* hbase_c24abab = NULL;
  TH1D* hbase_c22 = NULL;
  TH1D* hbase_c22ab = NULL;
  calc_subevents(base_for, base_4aabb, base_4abab,
                 base_two, base_2aa, base_2bb, base_2ab,
                 &hbase_v24, &hbase_v24aabb, &hbase_v24abab, &hbase_v22, &hbase_v22ab,
                 &hbase_c24, &hbase_c24aabb, &hbase_c24abab, &hbase_c22, &hbase_c22ab,
                 1);
  TProfile* eval_for = (TProfile*)feval->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* eval_4aabb = (TProfile*)feval->Get("centrality_os_fvtxsfvtxn_tracks_c24a");
  TProfile* eval_4abab = (TProfile*)feval->Get("centrality_os_fvtxsfvtxn_tracks_c24b");
  TProfile* eval_two = (TProfile*)feval->Get("centrality_os_fvtxc_tracks_c22");
  TProfile* eval_2aa = (TProfile*)feval->Get("centrality_os_fvtxs_tracks_c22");
  TProfile* eval_2bb = (TProfile*)feval->Get("centrality_os_fvtxn_tracks_c22");
  TProfile* eval_2ab = (TProfile*)feval->Get("centrality_os_fvtxsfvtxn_tracks_c22");
  if ( strcmp(systype,"acce") == 0 )
  {
  eval_for = (TProfile*)feval->Get("centrality_ac_fvtxc_tracks_c24");
  eval_4aabb = (TProfile*)feval->Get("centrality_ac_fvtxsfvtxn_tracks_c24a");
  eval_4abab = (TProfile*)feval->Get("centrality_ac_fvtxsfvtxn_tracks_c24b");
  eval_two = (TProfile*)feval->Get("centrality_ac_fvtxc_tracks_c22");
  eval_2aa = (TProfile*)feval->Get("centrality_ac_fvtxs_tracks_c22");
  eval_2bb = (TProfile*)feval->Get("centrality_ac_fvtxn_tracks_c22");
  eval_2ab = (TProfile*)feval->Get("centrality_ac_fvtxsfvtxn_tracks_c22");
  }
  TH1D* heval_v24 = NULL;
  TH1D* heval_v24aabb = NULL;
  TH1D* heval_v24abab = NULL;
  TH1D* heval_v22 = NULL;
  TH1D* heval_v22ab = NULL;
  TH1D* heval_c24 = NULL;
  TH1D* heval_c24aabb = NULL;
  TH1D* heval_c24abab = NULL;
  TH1D* heval_c22 = NULL;
  TH1D* heval_c22ab = NULL;
  calc_subevents(eval_for, eval_4aabb, eval_4abab,
                 eval_two, eval_2aa, eval_2bb, eval_2ab,
                 &heval_v24, &heval_v24aabb, &heval_v24abab, &heval_v22, &heval_v22ab,
                 &heval_c24, &heval_c24aabb, &heval_c24abab, &heval_c22, &heval_c22ab,
                 1);
  crunch(hbase_v22ab,heval_v22ab,systype,"cent_v22ab",0,100,1,93);
  crunch(hbase_v24aabb,heval_v24aabb,systype,"cent_v24aabb",0,100,6,65);
  crunch(hbase_v24abab,heval_v24abab,systype,"cent_v24abab",0,100,6,65);

}



void crunch(TProfile* tpbase, TProfile* tpeval, const char* systype, const char* quantity)
{
  if ( !tpbase || !tpeval )
    {
      cout << "one or more null histograms " << tpbase << " " << tpeval << endl;
      return;
    }
  TH1D* hbase = tpbase->ProjectionX("hbase");
  TH1D* heval = tpeval->ProjectionX("heval");
  crunch(hbase,heval,systype,quantity,0,100,20,50);
}



void crunch(TH1D* hbase, TH1D* heval, const char* systype, const char* quantity, double xmin, double xmax, double fmin, double fmax)
{

  if ( !hbase || !heval )
    {
      cout << "one or more null histograms " << hbase << " " << heval << endl;
      return;
    }

  TH1D* hratio = (TH1D*)heval->Clone("hratio");
  hratio->Divide(hbase);
  for ( int i = 0; i < hratio->GetNbinsX(); ++i )
    {
      double cont = hratio->GetBinContent(i+1);
      double err = hratio->GetBinError(i+1);
      if ( cont <= 0.0 || err >= 1.0 )
        {
          hratio->SetBinContent(i+1,0);
          hratio->SetBinError(i+1,9999); // effectively de-weight during fit
        }
    }


  bool iscent = true;
  bool isntrk = false;

  //-- setup canvas
  //-- Margins
  float Lmarg = 0.15;
  float Rmarg = 0.04;
  float Bmarg = 0.16;
  float Tmarg = 0.02;

  double w = 800 / (1 + Lmarg + Rmarg);
  double h = 900 / (1 + Bmarg + Tmarg);

  TCanvas *ccomp = new TCanvas("ccomp", "", w, h);
  ccomp->SetMargin(0, 0, 0, 0);

  ccomp->cd();
  TPad *pcomp = new TPad("pcomp", "comp", 0, 0.45, 1, 1);
  pcomp->SetMargin(Lmarg, Rmarg, 0, 0.1);
  pcomp->SetTicks(1, 1);
  pcomp->Draw();

  ccomp->cd();
  TPad *pratio = new TPad("pratio", "ratio", 0, 0, 1, 0.45);
  pratio->SetMargin(Lmarg, Rmarg, 0.22, 0);
  pratio->SetTicks(1, 1);
  pratio->Draw();

  //-- plot
  pcomp->cd();
  double ymin = -1e-2;
  double ymax = 1e-1;
  // double xmin = 0;
  // double xmax = 100;
  TH2D* empty_comp = new TH2D("empty_comp","",1,xmin,xmax,1,ymin,ymax);
  empty_comp->Draw();
  empty_comp->GetXaxis()->SetLabelSize(0.0);
  empty_comp->GetXaxis()->SetTitleSize(0.0);
  empty_comp->GetYaxis()->SetLabelFont(62);
  empty_comp->GetYaxis()->SetTitleFont(62);
  empty_comp->GetYaxis()->SetLabelSize(0.075);
  empty_comp->GetYaxis()->SetTitleSize(0.075);
  empty_comp->GetYaxis()->SetTitle("comparison");
  empty_comp->GetYaxis()->SetTitleOffset(1.05);
  hbase->SetMarkerStyle(kOpenCircle);
  hbase->SetMarkerColor(kRed);
  hbase->SetLineColor(kBlack);
  hbase->Draw("same ex0p");
  heval->SetMarkerStyle(kOpenSquare);
  heval->SetMarkerColor(kBlue);
  heval->SetLineColor(kBlack);
  heval->Draw("same ex0p");
  TLine *cline = new TLine(xmin,0,xmax,0);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  TLegend* leg_comp = new TLegend(0.18,0.70,0.4,0.85);
  leg_comp->SetTextFont(62);
  leg_comp->SetTextSize(0.075);
  leg_comp->SetFillStyle(0);
  leg_comp->AddEntry(hbase,Form("base for %s",quantity),"p");
  leg_comp->AddEntry(heval,systype,"p");
  leg_comp->Draw();

  //-- ratio
  pratio->cd();
  ymin = 0.25;
  ymax = 1.75;
  // ymin = -0.01;
  // ymax = 1.99;
  TH2D* empty_ratio = new TH2D("empty_ratio","",1,xmin,xmax,1,ymin,ymax);
  empty_ratio->Draw();
  if ( iscent ) empty_ratio->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty_ratio->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty_ratio->GetXaxis()->SetLabelFont(62);
  empty_ratio->GetXaxis()->SetTitleFont(62);
  empty_ratio->GetXaxis()->SetLabelSize(0.090);
  empty_ratio->GetXaxis()->SetTitleSize(0.090);
  empty_ratio->GetYaxis()->SetLabelFont(62);
  empty_ratio->GetYaxis()->SetTitleFont(62);
  empty_ratio->GetYaxis()->SetLabelSize(0.090);
  empty_ratio->GetYaxis()->SetTitleSize(0.090);
  empty_ratio->GetYaxis()->SetTitle("ratio");
  empty_ratio->GetYaxis()->SetTitleOffset(0.9);
  hratio->SetMarkerStyle(kOpenCircle);
  hratio->SetLineColor(kBlack);
  hratio->GetXaxis()->SetRangeUser(fmin,fmax);
  hratio->Draw("same ex0p");
  if ( cline) delete cline;
  cline = new TLine(xmin,1,xmax,1);
  cline->SetLineWidth(2);
  cline->SetLineStyle(2);
  cline->Draw();
  TF1* fun = new TF1("fun","pol0",xmin,xmax);
  fun->SetParameter(0,1.0);
  hratio->Fit(fun,"","",fmin,fmax);
  TLegend* leg_ratio = new TLegend(0.18,0.80,0.4,0.95);
  leg_ratio->SetTextFont(62);
  leg_ratio->SetTextSize(0.090);
  leg_ratio->SetFillStyle(0);
  //leg_ratio->AddEntry(hratio,Form("Sys Uncert on %s = %.2f%%", quantity, fabs(1.0 - fun->GetParameter(0)) * 100.0),"p");
  leg_ratio->AddEntry(hratio,Form("Sys = %.2f%%", fabs(1.0 - fun->GetParameter(0)) * 100.0),"p");
  leg_ratio->Draw();
  ccomp->Print(Form("Systematics/sys_%s_%s.png",quantity,systype));
  ccomp->Print(Form("Systematics/sys_%s_%s.pdf",quantity,systype));
  delete cline;
  delete ccomp;
  delete empty_ratio;
  delete empty_comp;
  delete leg_ratio;
  delete leg_comp;

}

