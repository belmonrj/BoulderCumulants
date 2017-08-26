

void plot_recv2(TH1D* th1d_v28, TH1D* th1d_v26, TH1D* th1d_v24, TH1D* th1d_v22, const char* handle)
{

  TCanvas* c1 = new TCanvas("c1","");

  bool iscent = false;
  bool isntrk = false;
  if ( strcmp(handle,"cent") == 0 ) iscent = true;
  if ( strcmp(handle,"strk") == 0 ) isntrk = true;
  bool isamptntrk = false;
  if ( strcmp(handle,"amptstrk") == 0 ) { isamptntrk = true; isntrk = true; }
  bool islowzoom = false;
  if ( strcmp(handle,"lowstrkzoom") == 0 ) { islowzoom = true; isntrk = true; }



  // --- considering passing these as arguments...
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
  th1d_v22->GetXaxis()->SetRangeUser(0,90);
  th1d_v24->GetXaxis()->SetRangeUser(5,70);
  th1d_v26->GetXaxis()->SetRangeUser(5,70);
  }
  th1d_v26->SetMarkerStyle(kOpenCircle);
  th1d_v26->SetMarkerColor(kBlack);
  th1d_v26->SetLineColor(kBlack);
  th1d_v26->Draw("same ex0p");
  TLegend* leg = new TLegend(0.62,0.68,0.88,0.88);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_v26,"v_{2}{6}","p");
  leg->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v26.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v26.pdf",handle));
  th1d_v24->SetMarkerStyle(kOpenSquare);
  th1d_v24->SetMarkerColor(kBlue);
  th1d_v24->SetLineColor(kBlue);
  th1d_v24->Draw("same ex0p");
  th1d_v22->SetMarkerStyle(kOpenCross);
  th1d_v22->SetMarkerColor(kRed);
  th1d_v22->SetLineColor(kRed);
  th1d_v22->Draw("same ex0p");
  leg->AddEntry(th1d_v24,"v_{2}{4}","p");
  leg->AddEntry(th1d_v22,"v_{2}{2}","p");
  leg->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v2642.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v2642.pdf",handle));

  ymin = 0.0;
  ymax = 0.12;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("v_{2}");
  if ( iscent ) th1d_v28->GetXaxis()->SetRangeUser(0,50);
  th1d_v28->SetMarkerStyle(kFullDiamond);
  th1d_v28->SetMarkerColor(kGreen+2);
  th1d_v28->SetLineColor(kGreen+2);
  th1d_v28->Draw("same ex0p");
  if ( leg ) delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_v28,"v_{2}{8}","p");
  leg->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v28.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v28.pdf",handle));
  th1d_v26->Draw("same ex0p");
  th1d_v24->Draw("same ex0p");
  th1d_v22->Draw("same ex0p");
  th1d_v28->Draw("same ex0p");
  leg->AddEntry(th1d_v26,"v_{2}{6}","p");
  leg->AddEntry(th1d_v24,"v_{2}{4}","p");
  leg->AddEntry(th1d_v22,"v_{2}{2}","p");
  leg->Draw();
  c1->Print(Form("FigsRecursion/recursion_%s_v28642.png",handle));
  c1->Print(Form("FigsRecursion/recursion_%s_v28642.pdf",handle));

  if ( empty ) delete empty;
  if ( c1 ) delete c1;

}

