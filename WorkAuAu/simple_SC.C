void doit(TProfile*, TProfile*, TProfile*, TProfile*, TProfile*, int, const char*);



void simple_SC()
{

  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");
  TProfile* tp1f_2323 = (TProfile*)fin->Get("centrality_recursion_0_10");
  TProfile* tp1f_2424 = (TProfile*)fin->Get("centrality_recursion_0_11");
  TProfile* tp1f_22 = (TProfile*)fin->Get("centrality_recursion_0_0");
  TProfile* tp1f_33 = (TProfile*)fin->Get("centrality_recursion_0_1");
  TProfile* tp1f_44 = (TProfile*)fin->Get("centrality_recursion_0_7");

  doit(tp1f_2323, tp1f_2424, tp1f_22, tp1f_33, tp1f_44, 2, "cent");

  tp1f_2323 = (TProfile*)fin->Get("nfvtxt_recursion_0_10");
  tp1f_2424 = (TProfile*)fin->Get("nfvtxt_recursion_0_11");
  tp1f_22 = (TProfile*)fin->Get("nfvtxt_recursion_0_0");
  tp1f_33 = (TProfile*)fin->Get("nfvtxt_recursion_0_1");
  tp1f_44 = (TProfile*)fin->Get("nfvtxt_recursion_0_7");

  doit(tp1f_2323, tp1f_2424, tp1f_22, tp1f_33, tp1f_44, 10, "ntrk");

}



void doit(TProfile* tp1f_2323, TProfile* tp1f_2424, TProfile* tp1f_22, TProfile* tp1f_33, TProfile* tp1f_44, int rebin, const char* handle)
{

  bool iscent = false;
  bool isscent = false;
  bool isntrk = false;
  if ( strcmp(handle,"cent") == 0 ) iscent = true;
  if ( strcmp(handle,"scent") == 0 ) {iscent = true; isscent = true;}
  if ( strcmp(handle,"ntrk") == 0 ) isntrk = true;
  bool isamptntrk = false;
  if ( strcmp(handle,"amptntrk") == 0 ) { isamptntrk = true; isntrk = true; }
  bool islowzoom = false;
  if ( strcmp(handle,"lowntrkzoom") == 0 ) { islowzoom = true; isntrk = true; }

  tp1f_2323->Rebin(rebin);
  tp1f_2424->Rebin(rebin);
  tp1f_22->Rebin(rebin);
  tp1f_33->Rebin(rebin);
  tp1f_44->Rebin(rebin);



  TCanvas* c1 = new TCanvas("c1","");

  tp1f_2323->Draw();
  c1->Print(Form("FigsSymmetricCumulants/diagnostic_%s_2323.png",handle));
  c1->Print(Form("FigsSymmetricCumulants/diagnostic_%s_2323.pdf",handle));

  tp1f_2424->Draw();
  c1->Print(Form("FigsSymmetricCumulants/diagnostic_%s_2424.png",handle));
  c1->Print(Form("FigsSymmetricCumulants/diagnostic_%s_2424.pdf",handle));

  tp1f_22->Draw();
  c1->Print(Form("FigsSymmetricCumulants/diagnostic_%s_22.png",handle));
  c1->Print(Form("FigsSymmetricCumulants/diagnostic_%s_22.pdf",handle));

  tp1f_33->Draw();
  c1->Print(Form("FigsSymmetricCumulants/diagnostic_%s_33.png",handle));
  c1->Print(Form("FigsSymmetricCumulants/diagnostic_%s_33.pdf",handle));

  tp1f_44->Draw();
  c1->Print(Form("FigsSymmetricCumulants/diagnostic_%s_44.png",handle));
  c1->Print(Form("FigsSymmetricCumulants/diagnostic_%s_44.pdf",handle));

  TH1D* th1d_2323 = (TH1D*)tp1f_2323->ProjectionX(Form("th1d_2323_%s",handle));
  TH1D* th1d_2424 = (TH1D*)tp1f_2424->ProjectionX(Form("th1d_2424_%s",handle));
  TH1D* th1d_22 = (TH1D*)tp1f_22->ProjectionX(Form("th1d_22_%s",handle));
  TH1D* th1d_33 = (TH1D*)tp1f_33->ProjectionX(Form("th1d_33_%s",handle));
  TH1D* th1d_44 = (TH1D*)tp1f_44->ProjectionX(Form("th1d_44_%s",handle));

  TH1D* th1d_2233 = (TH1D*)th1d_22->Clone();
  th1d_2233->Multiply(th1d_33);
  TH1D* th1d_SC23 = (TH1D*)th1d_2323->Clone();
  th1d_SC23->Add(th1d_2233,-1.0);

  TH1D* th1d_2244 = (TH1D*)th1d_22->Clone();
  th1d_2244->Multiply(th1d_44);
  TH1D* th1d_SC24 = (TH1D*)th1d_2424->Clone();
  th1d_SC24->Add(th1d_2244,-1.0);

  // --- considering passing these as arguments...
  double xmin = 0.0;
  double xmax = 70.0;
  double ymin = -4e-6;
  double ymax = 4e-6;
  if ( isntrk && !islowzoom ) xmax = 650.0;

  // --- do the plotting
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("Symmetric Cumulant");
  empty->GetYaxis()->SetTitleOffset(1.2);
  TLatex* tex_tracks = new TLatex(0.2,0.83,"h^{#pm} 1<|#eta|<3");
  tex_tracks->SetTextSize(0.05);
  tex_tracks->SetNDC();
  tex_tracks->Draw();
  TLatex* tex_system = new TLatex(0.2,0.882,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  tex_system->SetTextSize(0.05);
  tex_system->SetNDC();
  tex_system->Draw();
  // ---
  th1d_SC23->SetMarkerStyle(kFullCircle);
  th1d_SC23->SetMarkerColor(kBlue);
  th1d_SC23->SetLineColor(kBlue);
  th1d_SC23->Draw("ex0p same");
  th1d_SC24->SetMarkerStyle(kFullSquare);
  th1d_SC24->SetMarkerColor(kRed);
  th1d_SC24->SetLineColor(kRed);
  th1d_SC24->Draw("ex0p same");
  TLegend* leg = new TLegend(0.68,0.18,0.88,0.38);
  leg->SetHeader("PHENIX");
  leg->AddEntry(th1d_SC23,"SC(2,3)","p");
  leg->AddEntry(th1d_SC24,"SC(2,4)","p");
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->Draw();
  TLine* line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print(Form("FigsSymmetricCumulants/physics_%s.png",handle));
  c1->Print(Form("FigsSymmetricCumulants/physics_%s.pdf",handle));


  // 0.0 –  5.0	        -0.00000001474034 ± 0.00000000185676 (stat) ∓ 0.00000000144455 (sys)	0.000000001382924 ± 0.000000001195944 (stat) ± 0.000000000233714 (sys)
  // 5.0 –  10.0	-0.00000006189796 ± 0.00000000413260 (stat) ∓ 0.00000000606600 (sys)	0.00000001739164  ± 0.00000000272449  (stat) ± 0.00000000293919  (sys)
  // 10.0 –  20.0	-0.0000003210893  ± 0.0000000073627  (stat) ∓ 0.0000000314668  (sys)	0.00000008423141  ± 0.00000000512466  (stat) ± 0.00000001423511  (sys)
  // 20.0 –  30.0	-0.0000006376161  ± 0.0000000153537  (stat) ∓ 0.0000000624864  (sys)	0.0000004483835   ± 0.0000000119450   (stat) ± 0.0000000757768   (sys)
  // 30.0 –  40.0	-0.000001026290   ± 0.000000028970   (stat) ∓ 0.000000100576   (sys)	0.000001126789    ± 0.000000025103    (stat) ± 0.000000190427    (sys)
  // 40.0 –  50.0	-0.000001254218   ± 0.000000055094   (stat) ∓ 0.000000122913   (sys)	0.000001861415    ± 0.000000051132    (stat) ± 0.000000314579    (sys)
  // 50.0 –  60.0	-0.000001077982   ± 0.000000115430   (stat) ∓ 0.000000105642   (sys)	0.000002147265    ± 0.000000110627    (stat) ± 0.000000362888    (sys)
  // 60.0 –  70.0	-0.000001093781   ± 0.000000305660   (stat) ∓ 0.000000107190   (sys)	0.000002207977    ± 0.000000300449    (stat) ± 0.000000373148    (sys)

  double alice_cent[8] = {2.5,7.5,15,25,35,45,55,65};
  double alice_sc23[8] = {-0.00000001474034, -0.00000006189796, -0.0000003210893, -0.0000006376161, -0.000001026290, -0.000001254218, -0.000001077982, -0.000001093781};
  double alice_sc24[8] = {0.000000001382924, 0.00000001739164, 0.00000008423141, 0.0000004483835, 0.000001126789, 0.000001861415, 0.000002147265, 0.000002207977};
  double alice_esc23[8] = {0.00000000185676, 0.00000000413260, 0.0000000073627, 0.0000000153537, 0.000000028970, 0.000000055094, 0.000000115430, 0.000000305660};
  double alice_esc24[8] = {0.000000001195944, 0.00000000272449, 0.00000000512466, 0.0000000119450, 0.000000025103, 0.000000051132, 0.000000110627, 0.000000300449};

  TGraphErrors* tge_alice_sc23 = new TGraphErrors(8,alice_cent,alice_sc23,0,alice_esc23);
  TGraphErrors* tge_alice_sc24 = new TGraphErrors(8,alice_cent,alice_sc24,0,alice_esc24);
  tge_alice_sc23->SetMarkerStyle(kOpenStar);
  tge_alice_sc23->SetMarkerColor(kBlue);
  tge_alice_sc23->SetMarkerSize(3.4);
  tge_alice_sc24->SetMarkerStyle(kOpenStar);
  tge_alice_sc24->SetMarkerColor(kRed);
  tge_alice_sc24->SetMarkerSize(3.4);
  tge_alice_sc23->Draw("p");
  tge_alice_sc24->Draw("p");
  TLegend* lega = new TLegend(0.2,0.18,0.4,0.38);
  lega->SetHeader("ALICE, PRL 117, 182301 (2016)");
  lega->SetHeader("ALICE");
  lega->SetHeader("ALICE (Pb+Pb at 2.76 TeV)");
  lega->AddEntry(tge_alice_sc23,"SC(2,3)","p");
  lega->AddEntry(tge_alice_sc24,"SC(2,4)","p");
  lega->SetFillStyle(0);
  lega->SetTextSize(0.05);
  lega->Draw();
  if ( iscent )
  {
  c1->Print(Form("FigsSymmetricCumulants/alice_physics_%s.png",handle));
  c1->Print(Form("FigsSymmetricCumulants/alice_physics_%s.pdf",handle));
  }

  // --- now do normalization

  th1d_SC23->Divide(th1d_2233);
  th1d_SC24->Divide(th1d_2244);

  ymin = -5;
  ymax = 5;
  // --- do the plotting
  if ( empty ) delete empty;
  empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("Symmetric Cumulant");
  empty->GetYaxis()->SetTitleOffset(1.2);
  if ( tex_tracks ) delete tex_tracks;
  tex_tracks = new TLatex(0.2,0.83,"h^{#pm} 1<|#eta|<3");
  tex_tracks->SetTextSize(0.05);
  tex_tracks->SetNDC();
  tex_tracks->Draw();
  if ( tex_system ) delete tex_system;
  tex_system = new TLatex(0.2,0.882,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  tex_system->SetTextSize(0.05);
  tex_system->SetNDC();
  tex_system->Draw();
  // ---
  th1d_SC23->SetMarkerStyle(kFullCircle);
  th1d_SC23->SetMarkerColor(kBlue);
  th1d_SC23->SetLineColor(kBlue);
  th1d_SC23->Draw("ex0p same");
  th1d_SC24->SetMarkerStyle(kFullSquare);
  th1d_SC24->SetMarkerColor(kRed);
  th1d_SC24->SetLineColor(kRed);
  th1d_SC24->Draw("ex0p same");
  if ( leg ) delete leg;
  leg = new TLegend(0.68,0.18,0.88,0.38);
  leg->SetHeader("PHENIX");
  leg->AddEntry(th1d_SC23,"SC(2,3)","p");
  leg->AddEntry(th1d_SC24,"SC(2,4)","p");
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->Draw();
  if ( line ) delete line;
  line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->Print(Form("FigsSymmetricCumulants/physics_norm_%s.png",handle));
  c1->Print(Form("FigsSymmetricCumulants/physics_norm_%s.pdf",handle));
  // 0.0 –   5.0	-0.0328962 ± 0.0176542 (stat) ∓ 0.0030264 (sys)	0.0281826 ± 0.0463860 (stat) ± 0.0023110 (sys)
  // 5.0 –  10.0	-0.0499901 ± 0.0064077 (stat) ∓ 0.0045991 (sys)	0.0581925 ± 0.0320476 (stat) ± 0.0047718 (sys)
  // 10.0 –  20.0	-0.103095  ± 0.003496  (stat) ∓ 0.009485 (sys)	0.124046  ± 0.019574  (stat) ± 0.010172 (sys)
  // 20.0 –  30.0	-0.104141  ± 0.008150  (stat) ∓ 0.009581 (sys)	0.306628  ± 0.034699  (stat) ± 0.025144 (sys)
  // 30.0 –  40.0	-0.121965  ± 0.009387  (stat) ∓ 0.011221 (sys)	0.480953  ± 0.031312  (stat) ± 0.039438 (sys)
  // 40.0 –  50.0	-0.134738  ± 0.019299  (stat) ∓ 0.012396 (sys)	0.793742  ± 0.087712  (stat) ± 0.065087 (sys)
  // 50.0 –  60.0	-0.153151  ± 0.044574  (stat) ∓ 0.014090 (sys)	0.940638  ± 0.165636  (stat) ± 0.077132 (sys)
  double alice_nsc23[8] = {-0.0328962, -0.0499901, -0.103095, -0.104141, -0.121965, -0.134738, -0.153151};
  double alice_ensc23[8] = {0.0176542, 0.0064077, 0.003496, 0.008150, 0.009387, 0.019299, 0.044574};
  double alice_nsc24[8] = {0.0281826, 0.0581925, 0.124046, 0.306628, 0.480953, 0.793742, 0.940638};
  double alice_encs24[8] = {0.0463860, 0.0320476, 0.019574, 0.034699, 0.031312, 0.087712, 0.165636};
  TGraphErrors* tge_alice_nsc23 = new TGraphErrors(8,alice_cent,alice_nsc23,0,alice_esc23);
  TGraphErrors* tge_alice_nsc24 = new TGraphErrors(8,alice_cent,alice_nsc24,0,alice_esc24);
  tge_alice_nsc23->SetMarkerStyle(kOpenStar);
  tge_alice_nsc23->SetMarkerColor(kBlue);
  tge_alice_nsc23->SetMarkerSize(3.4);
  tge_alice_nsc24->SetMarkerStyle(kOpenStar);
  tge_alice_nsc24->SetMarkerColor(kRed);
  tge_alice_nsc24->SetMarkerSize(3.4);
  tge_alice_nsc23->Draw("p");
  tge_alice_nsc24->Draw("p");
  if ( lega ) delete lega;
  lega = new TLegend(0.2,0.18,0.4,0.38);
  lega->SetHeader("ALICE, PRL 117, 182301 (2016)");
  lega->SetHeader("ALICE");
  lega->SetHeader("ALICE (Pb+Pb at 2.76 TeV)");
  lega->AddEntry(tge_alice_nsc23,"SC(2,3)","p");
  lega->AddEntry(tge_alice_nsc24,"SC(2,4)","p");
  lega->SetFillStyle(0);
  lega->SetTextSize(0.05);
  lega->Draw();
  if ( iscent )
  {
  c1->Print(Form("FigsSymmetricCumulants/alice_physics_norm_%s.png",handle));
  c1->Print(Form("FigsSymmetricCumulants/alice_physics_norm_%s.pdf",handle));
  }




  delete c1;
  delete empty;
  delete leg;
  delete lega;
  delete line;

}
