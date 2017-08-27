void plot_subevents(TH1D* th1d_v24, TH1D* th1d_v24aabb, TH1D* th1d_v24abab, TH1D* th1d_v22, TH1D* th1d_v22ab)
{

  TCanvas* c1 = new TCanvas("c1","");

  bool iscent = true;
  bool isntrk = false;

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
  th1d_v24->GetXaxis()->SetRangeUser(5,70);
  th1d_v24aabb->GetXaxis()->SetRangeUser(5,70);
  th1d_v24abab->GetXaxis()->SetRangeUser(5,70);
  }
  th1d_v24->SetMarkerStyle(kOpenCircle);
  th1d_v24->SetMarkerColor(kBlack);
  th1d_v24->SetLineColor(kBlack);
  th1d_v24->Draw("same ex0p");
  th1d_v24aabb->SetMarkerStyle(kOpenSquare);
  th1d_v24aabb->SetMarkerColor(kRed);
  th1d_v24aabb->SetLineColor(kRed);
  th1d_v24aabb->Draw("same ex0p");
  th1d_v24abab->SetMarkerStyle(kOpenDiamond);
  th1d_v24abab->SetMarkerColor(kBlue);
  th1d_v24abab->SetLineColor(kBlue);
  th1d_v24abab->Draw("same ex0p");
  //if ( leg ) delete leg;
  TLegend* leg = new TLegend(0.62,0.72,0.88,0.92);
  //leg->SetHeader(type);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_v24,"v_{2}{4}","p");
  leg->AddEntry(th1d_v24aabb,"v_{2}{4}_{aa|bb}","p");
  leg->AddEntry(th1d_v24abab,"v_{2}{4}_{ab|ab}","p");
  leg->Draw();
  c1->Print("FigsSubevents/cent_subevents4.png");
  c1->Print("FigsSubevents/cent_subevents4.pdf");
  th1d_v22->SetMarkerStyle(kOpenCross);
  th1d_v22->SetMarkerColor(kRed);
  th1d_v22->SetLineColor(kRed);
  th1d_v22->Draw("same ex0p");
  th1d_v22ab->SetMarkerStyle(kOpenDiamond);
  th1d_v22ab->SetMarkerColor(kMagenta+2);
  th1d_v22ab->SetLineColor(kMagenta+2);
  th1d_v22ab->Draw("same ex0p");
  TLegend* leg2 = new TLegend(0.48,0.72,0.62,0.88);
  //leg2->SetHeader("Run14AuAu200");
  leg2->SetTextSize(0.045);
  leg2->SetFillStyle(0);
  leg2->AddEntry(th1d_v22,"v_{2}{2}","p");
  leg2->AddEntry(th1d_v22ab,"v_{2}{2}_{a|b}","p");
  leg2->Draw();
  c1->Print("FigsSubevents/cent_subevents24.png");
  c1->Print("FigsSubevents/cent_subevents24.pdf");


}
