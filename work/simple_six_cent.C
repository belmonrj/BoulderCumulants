void simple_six_cent()
{

  //TFile* fin = TFile::Open("input/cumulants_200.root");
  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");

  int rebin = 1;

  TProfile* tp1f_six = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c26");
  TProfile* tp1f_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c22");

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
      // --- 6-particle
      double c26 = th1d_c26->GetBinContent(i+1);
      double v26 = -9999;
      double six = th1d_six->GetBinContent(i+1);
      double esix = th1d_six->GetBinError(i+1);
      double ev26 = v26*(esix/six); // relative error for now, will get proper formula later...
      ev26 = 0; // looks very bad for reasons I don't yet understand...
      if ( c26 > 0 && six != 0 ) v26 = 0.25*pow(c26,(1.0/6.0)); // v2{6} = (1/4)*c2{6}^{(1/6)}
      th1d_v26->SetBinContent(i+1,v26);
      th1d_v26->SetBinError(i+1,ev26);
      // --- 4-particle
      double c24 = th1d_c24->GetBinContent(i+1);
      double v24 = -9999;
      double four = th1d_for->GetBinContent(i+1);
      double efour = th1d_for->GetBinError(i+1);
      double ev24 = v24*(efour/four); // relative error for now, will get proper formula later...
      ev24 = 0; // looks very bad for reasons I don't yet understand...
      if ( c24 < 0 && four != 0 ) v24 = pow(-c24,(1.0/4.0)); // v2{4} = -c2{4}^{(1/4)}
      th1d_v24->SetBinContent(i+1,v24);
      th1d_v24->SetBinError(i+1,ev24);
      // --- 2-particle
      double c22 = th1d_c22->GetBinContent(i+1);
      double v22 = -9999;
      double two = th1d_two->GetBinContent(i+1);
      double etwo = th1d_two->GetBinError(i+1);
      double ev22 = (1.0/v22)*etwo; // correct formula
      if ( c22 > 0 ) v22 = sqrt(c22); // v2{2} = c2{2}^{(1/2)}
      th1d_v22->SetBinContent(i+1,v22);
      th1d_v22->SetBinError(i+1,ev22);
      // ---
      // cout << i << " 123 " << th1d_123->GetBinContent(i+1) << " " << 12*two*two*two << endl;
      // cout << i << " 942 " << th1d_942->GetBinContent(i+1) << " " << 9*four*two << endl;
      // cout << i << " six " << th1d_six->GetBinContent(i+1) << " " << six << endl;
    }

  double xmin = 0.0;
  double xmax = 70.0;
  double ymin = -1e-4;
  double ymax = 1e-4;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("Centrality (%)");
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
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_six,"#LT#LT6#GT#GT","p");
  leg->AddEntry(th1d_942,"9#LT#LT4#GT#GT#LT#LT2#GT#GT","p");
  leg->AddEntry(th1d_123,"12#LT#LT2#GT#GT^{3}","p");
  leg->Draw();
  c1->Print(Form("FigsSix/sixparticle_components_blah.png"));
  c1->Print(Form("FigsSix/sixparticle_components_blah.pdf"));

  // xmin = 0.0;
  // xmax = 100.0;
  ymin = -2e-5;
  ymax = 2e-5;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("components");
  th1d_six->Draw("same ex0p");
  th1d_942->Draw("same ex0p");
  th1d_123->Draw("same ex0p");
  leg->Draw();
  c1->Print(Form("FigsSix/sixparticle_components_zoom_blah.png"));
  c1->Print(Form("FigsSix/sixparticle_components_zoom_blah.pdf"));

  // xmin = 0.0;
  // xmax = 100.0;
  ymin = -4e-6;
  ymax = 4e-6;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("cumulant");
  th1d_c26->SetMarkerStyle(kOpenCircle);
  th1d_c26->SetLineColor(kBlack);
  th1d_c26->Draw("same ex0p");
  if ( leg ) delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_c26,"c_{2}{6} = 4v_{2}^{6}","p");
  leg->Draw();
  c1->Print(Form("FigsSix/sixparticle_cumulant_blah.png"));
  c1->Print(Form("FigsSix/sixparticle_cumulant_blah.pdf"));

  // xmin = 0.0;
  // xmax = 100.0;
  ymin = 0.0;
  ymax = 0.199;
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  //empty->GetXaxis()->SetTitle("N^{1<|#eta|<3}_{trk}");
  empty->GetXaxis()->SetTitle("Centrality (%)");
  empty->GetYaxis()->SetTitle("v_{2}");
  th1d_v26->SetMarkerStyle(kOpenCircle);
  th1d_v26->SetMarkerColor(kBlack);
  th1d_v26->SetLineColor(kBlack);
  th1d_v26->Draw("same ex0p");
  if ( leg ) delete leg;
  leg = new TLegend(0.62,0.68,0.88,0.88);
  //leg->SetHeader(type);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_v26,"v_{2}{6}","p");
  leg->Draw();
  c1->Print(Form("FigsSix/sixparticle_v2_blah.png"));
  c1->Print(Form("FigsSix/sixparticle_v2_blah.pdf"));
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
  c1->Print(Form("FigsSix/sixparticle_v2642_blah.png"));
  c1->Print(Form("FigsSix/sixparticle_v2642_blah.pdf"));

}
