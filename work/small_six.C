void small_six()
{
  doit("Run16dAu200",2);
  doit("Run16dAu62",5);
  doit("Run16dAu39",5);
}

void doit(const char* handle, int rebin)
{

  //TFile* fin = TFile::Open("input/cumulants_200.root");
  //TFile* fin = TFile::Open("input/cumulants_Run16dAu200.root");
  //TFile* fin = TFile::Open("input/cumulants_Run16dAu62.root");
  TFile* fin = TFile::Open(Form("input/cumulants_%s.root",handle));

  // int rebin = 2;

  // TProfile* tp1f_six = (TProfile*)fin->Get("nfvtxt_os_fvtxc_tracks_c26");
  // TProfile* tp1f_for = (TProfile*)fin->Get("nfvtxt_os_fvtxc_tracks_c24");
  // TProfile* tp1f_two = (TProfile*)fin->Get("nfvtxt_os_fvtxc_tracks_c22");
  TProfile* tp1f_six = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c26");
  TProfile* tp1f_for = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c24");
  TProfile* tp1f_two = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c22");
  // TProfile* tp1f_six = (TProfile*)fin->Get("nfvtxt_zzyzx_fvtxc_tracks_c26");
  // TProfile* tp1f_for = (TProfile*)fin->Get("nfvtxt_zzyzx_fvtxc_tracks_c24");
  // TProfile* tp1f_two = (TProfile*)fin->Get("nfvtxt_zzyzx_fvtxc_tracks_c22");

  tp1f_six->Rebin(rebin);
  tp1f_for->Rebin(rebin);
  tp1f_two->Rebin(rebin);

  TH1D* th1d_six = tp1f_six->ProjectionX("th1d_six"); // <6>
  TH1D* th1d_for = tp1f_for->ProjectionX("th1d_for"); // <4>
  TH1D* th1d_two = tp1f_two->ProjectionX("th1d_two"); // <2>

  TH1D* th1d_942 = (TH1D*)th1d_for->Clone("th1d_942"); // 9<4><2>
  TH1D* th1d_123 = (TH1D*)th1d_two->Clone("th1d_123"); // 12<2>^3
  TH1D* th1d_222 = (TH1D*)th1d_two->Clone("th1d_222"); // 2<2>^2

  th1d_942->Multiply(th1d_two);
  th1d_942->Scale(9);
  th1d_123->Multiply(th1d_two);
  th1d_123->Multiply(th1d_two);
  th1d_123->Scale(12);
  th1d_222->Multiply(th1d_two);
  th1d_222->Scale(2);

  TH1D* th1d_c26 = (TH1D*)th1d_six->Clone("th1d_c26"); // c2{6} = <6> - 9<4><2> + 12<2>^3
  th1d_c26->Add(th1d_942,-1);
  th1d_c26->Add(th1d_123,1);

  TH1D* th1d_c24 = (TH1D*)th1d_for->Clone("th1d_c24"); // c2{4} = <4> - 2<2>^2
  th1d_c24->Add(th1d_222,-1);

  TH1D* th1d_c22 = (TH1D*)th1d_two->Clone("th1d_c22"); // c2{2} = <2>

  TH1D* th1d_v26 = (TH1D*)th1d_c26->Clone("th1d_v26");
  TH1D* th1d_v24 = (TH1D*)th1d_c24->Clone("th1d_v24");
  TH1D* th1d_v22 = (TH1D*)th1d_c24->Clone("th1d_v22");

  int nbins = th1d_c26->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      // --- base quantities
      double six = th1d_six->GetBinContent(i+1);
      double esix = th1d_six->GetBinError(i+1);
      double four = th1d_for->GetBinContent(i+1);
      double efour = th1d_for->GetBinError(i+1);
      double two = th1d_two->GetBinContent(i+1);
      double etwo = th1d_two->GetBinError(i+1);
      // --- 6-particle
      double center = th1d_c26->GetBinCenter(i+1);
      if ( center < 7 ) th1d_c26->SetBinContent(i+1,-9999);
      double c26 = th1d_c26->GetBinContent(i+1);
      double v26 = -9999;
      double ev26 = -9999;
      if ( c26 > 0 && six != 0 )
        {
          v26 = pow((0.25*c26),(1.0/6.0));
          ev26 = (1.0/pow(c26,1.25)) *
            sqrt(
                 (4.5*(4*two*two-four)*(4*two*two-four)*etwo*etwo) +
                 (4.5*two*two*efour*efour) +
                 (1.0/18.0)*esix*six
                 );
        }
      th1d_v26->SetBinContent(i+1,v26);
      double ev26 = v26*(esix/six);
      th1d_v26->SetBinError(i+1,ev26);
      // --- 4-particle
      center = th1d_c24->GetBinCenter(i+1);
      if ( center < 5 ) th1d_c24->SetBinContent(i+1,9999);
      double c24 = th1d_c24->GetBinContent(i+1);
      double v24 = -9999;
      double ev24 = -9999;
      if ( c24 < 0 && four != 0 )
        {
          v24 = pow(-c24,(1.0/4.0));
          ev24 = (1.0/pow(-c24,0.75)) *
            sqrt(
                 (two*two*etwo*etwo) +
                 (0.0625*efour*efour)
                 );
        }
      th1d_v24->SetBinContent(i+1,v24);
      th1d_v24->SetBinError(i+1,ev24);
      // --- 2-particle
      double c22 = th1d_c22->GetBinContent(i+1);
      double v22 = -9999;
      double ev22 = (1.0/v22)*etwo;
      if ( c22 > 0 ) v22 = sqrt(c22);
      th1d_v22->SetBinContent(i+1,v22);
      th1d_v22->SetBinError(i+1,ev22);
      // ---
      // cout << i << " 123 " << th1d_123->GetBinContent(i+1) << " " << 12*two*two*two << endl;
      // cout << i << " 942 " << th1d_942->GetBinContent(i+1) << " " << 9*four*two << endl;
      // cout << i << " six " << th1d_six->GetBinContent(i+1) << " " << six << endl;
    }


  float Lmarg = 0.14;
  float Rmarg = 0.02;
  float Bmarg = 0.16;
  float Tmarg = 0.02;

  TCanvas *ccomp = new TCanvas("ccomp", "", 600, 700);
  ccomp->SetMargin(0, 0, 0, 0);

  ccomp->cd();
  TPad *pcomp = new TPad("pcomp", "comp", 0, 0.45, 1, 1);
  pcomp->SetMargin(Lmarg, Rmarg, 0, 0.1);
  pcomp->SetTicks(1, 1);
  pcomp->Draw();

  ccomp->cd();
  TPad *pcompc26 = new TPad("pcompc24", "compc24", 0, 0, 1, 0.45);
  pcompc26->SetMargin(Lmarg, Rmarg, 0.22, 0);
  pcompc26->SetTicks(1, 1);
  pcompc26->Draw();

  double xmin = 0.0;
  double xmax = 50.0;
  // double ymin = -0.999e-5;
  // double ymax = 3e-5;
  double ymin = -0.999e-5;
  double ymax = 4e-5;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  pcomp->cd();
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
  empty->GetYaxis()->SetTitle("components");
  th1d_six->SetMarkerStyle(kOpenCircle);
  th1d_942->SetMarkerStyle(kOpenSquare);
  th1d_123->SetMarkerStyle(kOpenCross);
  th1d_six->SetMarkerColor(kBlack);
  th1d_942->SetMarkerColor(kRed);
  th1d_123->SetMarkerColor(kBlue);
  th1d_six->SetLineColor(kBlack);
  th1d_942->SetLineColor(kRed);
  th1d_123->SetLineColor(kBlue);
  th1d_six->Draw("same ex0p");
  th1d_942->Draw("same ex0p");
  th1d_123->Draw("same ex0p");
  TLegend* leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader(handle);
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_six,"#LT#LT6#GT#GT","p");
  leg->AddEntry(th1d_942,"9#LT#LT4#GT#GT#LT#LT2#GT#GT","p");
  leg->AddEntry(th1d_123,"12#LT#LT2#GT#GT^{3}","p");
  leg->Draw();
  pcompc26->cd();
  ymax = 2e-6;
  ymin = -5e-7;
  TH2D* empty2 = new TH2D("empty2","",1,xmin,xmax,1,ymin,ymax);
  empty2->Draw();
  empty2->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
  empty2->GetYaxis()->SetTitle("c_{2}{6}");
  empty2->GetXaxis()->SetTitleSize(0.06);
  empty2->GetYaxis()->SetTitleSize(0.06);
  empty2->GetXaxis()->SetLabelSize(0.06);
  empty2->GetYaxis()->SetLabelSize(0.06);
  th1d_c26->SetMarkerStyle(kFullCircle);
  th1d_c26->SetMarkerColor(kBlack);
  th1d_c26->SetLineColor(kBlack);
  th1d_c26->Draw("same ex0p");
  TLine line(xmin,0,xmax,0);
  line.SetLineWidth(2);
  line.SetLineStyle(2);
  line.Draw();
  ccomp->cd();
  ccomp->Print(Form("FigsSixSmall/strk_sixparticle_components_%s.png",handle));
  ccomp->Print(Form("FigsSixSmall/strk_sixparticle_components_%s.pdf",handle));

  //return;

  TCanvas* c1 = new TCanvas("c1","");
  c1->cd();
  // xmin = 0.0;
  // xmax = 100.0;
  ymin = -2e-5;
  ymax = 2e-5;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
  empty->GetYaxis()->SetTitle("components");
  th1d_six->Draw("same ex0p");
  th1d_942->Draw("same ex0p");
  th1d_123->Draw("same ex0p");
  leg->Draw();
  c1->Print(Form("FigsSixSmall/strk_sixparticle_components_zoom_%s.png",handle));
  c1->Print(Form("FigsSixSmall/strk_sixparticle_components_zoom_%s.pdf",handle));

  // xmin = 0.0;
  // xmax = 100.0;
  ymin = -4e-6;
  ymax = 4e-6;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
  empty->GetYaxis()->SetTitle("cumulant");
  th1d_c26->SetMarkerStyle(kOpenCircle);
  th1d_c26->SetLineColor(kBlack);
  th1d_c26->Draw("same ex0p");
  if ( leg ) delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader(handle);
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_c26,"c_{2}{6} = 4v_{2}^{6}","p");
  leg->Draw();
  c1->Print(Form("FigsSixSmall/strk_sixparticle_cumulant_%s.png",handle));
  c1->Print(Form("FigsSixSmall/strk_sixparticle_cumulant_%s.pdf",handle));

  // xmin = 0.0;
  // xmax = 100.0;
  ymin = 0.0;
  ymax = 0.199;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
  empty->GetYaxis()->SetTitle("v_{2}");
  th1d_v26->SetMarkerStyle(kOpenCircle);
  th1d_v26->SetMarkerColor(kBlack);
  th1d_v26->SetLineColor(kBlack);
  th1d_v26->Draw("same ex0p");
  if ( leg ) delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader(handle);
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_v26,"v_{2}{6}","p");
  leg->Draw();
  c1->Print(Form("FigsSixSmall/strk_sixparticle_v2_%s.png",handle));
  c1->Print(Form("FigsSixSmall/strk_sixparticle_v2_%s.pdf",handle));
  th1d_v24->SetMarkerStyle(kOpenSquare);
  th1d_v24->SetMarkerColor(kRed);
  th1d_v24->SetLineColor(kRed);
  th1d_v24->Draw("same ex0p");
  th1d_v22->SetMarkerStyle(kOpenCross);
  th1d_v22->SetMarkerColor(kBlue);
  th1d_v22->SetLineColor(kBlue);
  th1d_v22->Draw("same ex0p");
  leg->AddEntry(th1d_v24,"v_{2}{4}","p");
  leg->AddEntry(th1d_v22,"v_{2}{2}","p");
  leg->Draw();
  double sysB_v22_dAu200 = 0.1;
  TH1D* gv22_sys_dAu200 = (TH1D*) th1d_v22->Clone("gv22_sys_dAu200");
  gv22_sys_dAu200->SetMarkerSize(0);
  gv22_sys_dAu200->SetFillColorAlpha(kBlue, 0.35);
  for (int i = 1; i <= gv22_sys_dAu200->GetNbinsX(); i++)
  {
    double y = gv22_sys_dAu200->GetBinContent(i);
    if ( y > 0 )
    {
      gv22_sys_dAu200->SetBinError(i, y * sysB_v22_dAu200);
      //cout << y << " +- " << y * sysB_v22_dAu200 << endl;
    }
    else
    {
      gv22_sys_dAu200->SetBinContent(i, 0);
      gv22_sys_dAu200->SetBinError(i, 0);
    }
  } // i
  gv22_sys_dAu200->Draw("E5 same");
  double sysB_v24_dAu200 = TMath::Sqrt(0.10 * 0.10 + // acceptance
                                       0.10 * 0.10 + // zvrtx
                                       0.01 * 0.01 + // DCA
                                       0.01 * 0.01); // ghost tracks
  //cout << "sys is " << sysB_v24_dAu200 << endl;
  TH1D* gv24_sys_dAu200 = (TH1D*) th1d_v24->Clone("gv24_sys_dAu200");
  gv24_sys_dAu200->SetMarkerSize(0);
  gv24_sys_dAu200->SetFillColorAlpha(kRed, 0.35);
  for (int i = 1; i <= gv24_sys_dAu200->GetNbinsX(); i++)
  {
    double y = gv24_sys_dAu200->GetBinContent(i);
    if ( y > 0 )
    {
      gv24_sys_dAu200->SetBinError(i, y * sysB_v24_dAu200);
      //cout << y << " +- " << y * sysB_v24_dAu200 << endl;
    }
    else
    {
      gv24_sys_dAu200->SetBinContent(i, 0);
      gv24_sys_dAu200->SetBinError(i, 0);
    }
  } // i
  gv24_sys_dAu200->Draw("E5 same");
  double sysB_v26_dAu200 = sysB_v24_dAu200;
  TH1D* gv26_sys_dAu200 = (TH1D*) th1d_v26->Clone("gv26_sys_dAu200");
  gv26_sys_dAu200->SetMarkerSize(0);
  gv26_sys_dAu200->SetFillColorAlpha(kBlack, 0.35);
  for (int i = 1; i <= gv26_sys_dAu200->GetNbinsX(); i++)
  {
    double y = gv26_sys_dAu200->GetBinContent(i);
    if ( y > 0 )
    {
      gv26_sys_dAu200->SetBinError(i, y * sysB_v26_dAu200);
      //cout << y << " +- " << y * sysB_v26_dAu200 << endl;
    }
    else
    {
      gv26_sys_dAu200->SetBinContent(i, 0);
      gv26_sys_dAu200->SetBinError(i, 0);
    }
  } // i
  gv26_sys_dAu200->Draw("E5 same");
  c1->Print(Form("FigsSixSmall/strk_sixparticle_v2642_%s.png",handle));
  c1->Print(Form("FigsSixSmall/strk_sixparticle_v2642_%s.pdf",handle));

  delete c1;
  delete ccomp;

}
