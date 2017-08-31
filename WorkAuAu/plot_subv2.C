void plot_subv2(TH1D* th1d_v24, TH1D* th1d_v24aabb, TH1D* th1d_v24abab, TH1D* th1d_v22, TH1D* th1d_v22ab)
{

  TCanvas* c1 = new TCanvas("c1","");

  bool iscent = true;
  bool isntrk = false;

  // --- get the systmatics histos
  TH1D* gv22_sys = (TH1D*) th1d_v22->Clone("gv22_sys");
  gv22_sys->SetMarkerStyle(0);
  gv22_sys->SetMarkerSize(0);
  gv22_sys->SetFillColorAlpha(kRed, 0.35);
  for ( int i = 0; i < gv22_sys->GetNbinsX(); ++i )
  {
    double y = gv22_sys->GetBinContent(i);
    double err = y * 0.09;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv22_sys->SetBinError(i, err);
  } // i
  TH1D* gv22ab_sys = (TH1D*) th1d_v22ab->Clone("gv22ab_sys");
  gv22ab_sys->SetMarkerStyle(0);
  gv22ab_sys->SetMarkerSize(0);
  gv22ab_sys->SetFillColorAlpha(kRed, 0.35);
  for ( int i = 0; i < gv22ab_sys->GetNbinsX(); ++i )
  {
    double y = gv22ab_sys->GetBinContent(i);
    double err = y * 0.1;
    if ( err < 0.005 ) err = 0.005;
    //if ( i < 10 ) err = 0.005;
    if ( y > 0 ) gv22ab_sys->SetBinError(i, err);
  } // i
  TH1D* gv24_sys = (TH1D*) th1d_v24->Clone("gv24_sys");
  gv24_sys->SetMarkerStyle(0);
  gv24_sys->SetMarkerSize(0);
  gv24_sys->SetFillColorAlpha(kBlack, 0.35);
  for ( int i = 0; i < gv24_sys->GetNbinsX(); ++i )
  {
    double y = gv24_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv24_sys->SetBinError(i, err);
  } // i
  TH1D* gv24aabb_sys = (TH1D*) th1d_v24aabb->Clone("gv24aabb_sys");
  gv24aabb_sys->SetMarkerStyle(0);
  gv24aabb_sys->SetMarkerSize(0);
  gv24aabb_sys->SetFillColorAlpha(kRed, 0.35);
  for ( int i = 0; i < gv24aabb_sys->GetNbinsX(); ++i )
  {
    double y = gv24aabb_sys->GetBinContent(i);
    double err = y * 0.07;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv24aabb_sys->SetBinError(i, err);
  } // i
  TH1D* gv24abab_sys = (TH1D*) th1d_v24abab->Clone("gv24abab_sys");
  gv24abab_sys->SetMarkerStyle(0);
  gv24abab_sys->SetMarkerSize(0);
  gv24abab_sys->SetFillColorAlpha(kBlue, 0.35);
  for ( int i = 0; i < gv24abab_sys->GetNbinsX(); ++i )
  {
    double y = gv24abab_sys->GetBinContent(i);
    double err = y * 0.06;
    if ( err < 0.005 ) err = 0.005;
    if ( y > 0 ) gv24abab_sys->SetBinError(i, err);
  } // i


  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = 0.0;
  double ymax = 0.12;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("v_{2}");
  if ( iscent )
  {
  gv24_sys->GetXaxis()->SetRangeUser(7,65);
  gv24aabb_sys->GetXaxis()->SetRangeUser(7,63);
  gv24abab_sys->GetXaxis()->SetRangeUser(7,63);
  th1d_v24->GetXaxis()->SetRangeUser(7,65);
  th1d_v24aabb->GetXaxis()->SetRangeUser(7,63);
  th1d_v24abab->GetXaxis()->SetRangeUser(7,63);
  }
  gv24_sys->Draw("E5 same");
  gv24aabb_sys->Draw("E5 same");
  gv24abab_sys->Draw("E5 same");
  th1d_v24aabb->SetMarkerStyle(kOpenSquare);
  th1d_v24aabb->SetMarkerColor(kRed);
  th1d_v24aabb->SetLineColor(kRed);
  th1d_v24aabb->Draw("same ex0p");
  th1d_v24abab->SetMarkerStyle(kOpenDiamond);
  th1d_v24abab->SetMarkerColor(kBlue);
  th1d_v24abab->SetLineColor(kBlue);
  th1d_v24abab->Draw("same ex0p");
  th1d_v24->SetMarkerStyle(kOpenCircle);
  th1d_v24->SetMarkerColor(kBlack);
  th1d_v24->SetLineColor(kBlack);
  th1d_v24->Draw("same ex0p");
  //if ( leg ) delete leg;
  TLegend* leg = new TLegend(0.62,0.72,0.88,0.92);
  //leg->SetHeader(type);
  //leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_v24,"v_{2}{4}","p");
  leg->AddEntry(th1d_v24aabb,"v_{2}{4}_{aa|bb}","p");
  leg->AddEntry(th1d_v24abab,"v_{2}{4}_{ab|ab}","p");
  leg->Draw();
  TLatex* tex_phenix = new TLatex(0.2,0.87,"PHENIX");
  tex_phenix->SetTextSize(0.05);
  tex_phenix->SetNDC();
  tex_phenix->Draw();
  TLatex* tex_system = new TLatex(0.2,0.80,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  tex_system->SetTextSize(0.05);
  tex_system->SetNDC();
  tex_system->Draw();
  c1->Print("FigsSubevents/cent_subevents4.png");
  c1->Print("FigsSubevents/cent_subevents4.pdf");
  // if ( iscent )
  // {
  // gv22_sys->GetXaxis()->SetRangeUser(1,90);
  // gv22ab_sys->GetXaxis()->SetRangeUser(1,90);
  // th1d_v22->GetXaxis()->SetRangeUser(1,90);
  // th1d_v22ab->GetXaxis()->SetRangeUser(1,90);
  // }
  // th1d_v22->SetMarkerStyle(kOpenCross);
  // th1d_v22->SetMarkerColor(kRed);
  // th1d_v22->SetLineColor(kRed);
  // th1d_v22->Draw("same ex0p");
  // gv22_sys->Draw("same E5");
  // th1d_v22ab->SetMarkerStyle(kOpenDiamond);
  // th1d_v22ab->SetMarkerColor(kMagenta+2);
  // th1d_v22ab->SetLineColor(kMagenta+2);
  // th1d_v22ab->Draw("same ex0p");
  // gv22ab_sys->Draw("same E5");
  // TLegend* leg2 = new TLegend(0.48,0.72,0.62,0.88);
  // //leg2->SetHeader("Run14AuAu200");
  // leg2->SetTextSize(0.045);
  // leg2->SetFillStyle(0);
  // leg2->AddEntry(th1d_v22,"v_{2}{2}","p");
  // leg2->AddEntry(th1d_v22ab,"v_{2}{2}_{a|b}","p");
  // leg2->Draw();
  // c1->Print("FigsSubevents/cent_subevents24.png");
  // c1->Print("FigsSubevents/cent_subevents24.pdf");


}
