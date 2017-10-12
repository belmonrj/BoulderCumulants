void doit(TProfile*, TProfile*, TProfile*, TProfile*, TProfile*, int, const char*);



void simple_SC()
{

  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");
  TProfile* tp1f_2323 = (TProfile*)fin->Get("centrality_recursion_0_10");
  TProfile* tp1f_2424 = (TProfile*)fin->Get("centrality_recursion_0_11");
  TProfile* tp1f_22 = (TProfile*)fin->Get("centrality_recursion_0_0");
  TProfile* tp1f_33 = (TProfile*)fin->Get("centrality_recursion_0_1");
  TProfile* tp1f_44 = (TProfile*)fin->Get("centrality_recursion_0_7");

  doit(tp1f_2323, tp1f_2424, tp1f_22, tp1f_33, tp1f_44, 1, "cent");

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
  double xmax = 100.0;
  double ymin = -1e-5;
  double ymax = 1e-5;
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
  TLegend* leg = new TLegend(0.6,0.2,0.8,0.4);
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

  // --- now do normalization

  th1d_SC23->Divide(th1d_2233);
  th1d_SC24->Divide(th1d_2244);

  ymin = -10;
  ymax = 20;
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
  leg = new TLegend(0.6,0.2,0.8,0.4);
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




  delete c1;
  delete empty;
  delete leg;
  delete line;

}
