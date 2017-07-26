void dothething_diagnostics(int name, int which1, int which2, int which3, int which4)
{

  gStyle->SetOptTitle(0);

  TString ts_hash1 = hash_description[xhash][which1];
  TString ts_hash2 = hash_description[xhash][which2];
  TString ts_hash3 = hash_description[xhash][which3];
  TString ts_hash4 = hash_description[xhash][which4];

  TString ts_desc1 = hash_description[xdesc][which1];
  TString ts_desc2 = hash_description[xdesc][which2];
  TString ts_desc3 = hash_description[xdesc][which3];
  TString ts_desc4 = hash_description[xdesc][which4];

  TString fname1 = "input/histos_"; fname1 += ts_hash1; fname1 += ".root";
  TString fname2 = "input/histos_"; fname2 += ts_hash2; fname2 += ".root";
  TString fname3 = "input/histos_"; fname3 += ts_hash3; fname3 += ".root";
  TString fname4 = "input/histos_"; fname4 += ts_hash4; fname4 += ".root";

  TString leghead1 = ts_desc1; leghead1 += " "; leghead1 += ts_hash1;
  TString leghead2 = ts_desc2; leghead2 += " "; leghead2 += ts_hash2;
  TString leghead3 = ts_desc3; leghead3 += " "; leghead3 += ts_hash3;
  TString leghead4 = ts_desc4; leghead4 += " "; leghead4 += ts_hash4;

  cout << ts_hash1 << " " << ts_desc1 << " " << fname1 << " " << leghead1 << endl;
  cout << ts_hash2 << " " << ts_desc2 << " " << fname2 << " " << leghead2 << endl;
  cout << ts_hash3 << " " << ts_desc3 << " " << fname3 << " " << leghead3 << endl;
  cout << ts_hash4 << " " << ts_desc4 << " " << fname4 << " " << leghead4 << endl;



  TCanvas* c1 = new TCanvas();
  c1->SetMargin(0.15,0.05,0.13,0.08); // LRBT

  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = 0.0;
  double ymax = 50.0;

  TFile* file1 = TFile::Open(fname1);
  TFile* file2 = TFile::Open(fname2);
  TFile* file3 = TFile::Open(fname3);
  TFile* file4 = TFile::Open(fname4);

  th1d_nfvtxt_combinedER;
  th1d_nfvtxt_combined;
  th2d_nfvtxt_bbcsum;
  th2d_nfvtxt_bbcsumratio;
  th1d_nfvtxt_north;
  th1d_nfvtxt_south;


  // --- cos21

  TProfile* h1_os_cos21 = (TProfile*)file1->Get("centrality_ac_fvtxc_tracks_cos21");
  TProfile* h2_os_cos21 = (TProfile*)file2->Get("centrality_ac_fvtxc_tracks_cos21");
  TProfile* h3_os_cos21 = (TProfile*)file3->Get("centrality_ac_fvtxc_tracks_cos21");
  TProfile* h4_os_cos21 = (TProfile*)file4->Get("centrality_ac_fvtxc_tracks_cos21");

  xmin = 0.0;
  xmax = 100.0;
  ymin = -0.2;
  ymax = 0.2;
  TH2D* hd_os_cos21 = new TH2D("hd_os_cos21","",1,xmin,xmax,1,ymin,ymax);
  hd_os_cos21->GetXaxis()->SetTitle("centrality");
  hd_os_cos21->GetYaxis()->SetTitle("#LT#LTcos2#phi#GT#GT");
  hd_os_cos21->GetXaxis()->SetTitleOffset(1.1);
  hd_os_cos21->GetYaxis()->SetTitleOffset(1.4);
  hd_os_cos21->GetXaxis()->SetTitleSize(0.055);
  hd_os_cos21->GetYaxis()->SetTitleSize(0.055);
  hd_os_cos21->GetXaxis()->SetLabelSize(0.055);
  hd_os_cos21->GetYaxis()->SetLabelSize(0.055);
  hd_os_cos21->Draw();
  h1_os_cos21->SetLineColor(kBlack);
  h2_os_cos21->SetLineColor(kRed);
  h3_os_cos21->SetLineColor(kBlue);
  h4_os_cos21->SetLineColor(kGreen+2);
  h1_os_cos21->SetMarkerColor(kBlack);
  h2_os_cos21->SetMarkerColor(kRed);
  h3_os_cos21->SetMarkerColor(kBlue);
  h4_os_cos21->SetMarkerColor(kGreen+2);
  h1_os_cos21->SetMarkerStyle(kOpenSquare);
  h2_os_cos21->SetMarkerStyle(kOpenCircle);
  h3_os_cos21->SetMarkerStyle(kOpenDiamond);
  h4_os_cos21->SetMarkerStyle(kOpenCross);
  h1_os_cos21->Draw("same ex0p");
  h2_os_cos21->Draw("same ex0p");
  h3_os_cos21->Draw("same ex0p");
  h4_os_cos21->Draw("same ex0p");
  TLegend* leg_os_cos21 = new TLegend(0.58,0.68,0.88,0.88);
  leg_os_cos21->AddEntry(h1_os_cos21,leghead1,"p");
  leg_os_cos21->AddEntry(h2_os_cos21,leghead2,"p");
  leg_os_cos21->AddEntry(h3_os_cos21,leghead3,"p");
  leg_os_cos21->AddEntry(h4_os_cos21,leghead4,"p");
  leg_os_cos21->SetTextSize(0.055);
  leg_os_cos21->SetFillStyle(0);
  leg_os_cos21->Draw();
  c1->Print(Form("ComparisonFigs/FourWayComparison_os_cos21_%d_%d%d%d%d.png",name,which1,which2,which3,which4));
  c1->Print(Form("ComparisonFigs/FourWayComparison_os_cos21_%d_%d%d%d%d.pdf",name,which1,which2,which3,which4));

  // --- sin21

  TProfile* h1_os_sin21 = (TProfile*)file1->Get("centrality_ac_fvtxc_tracks_sin21");
  TProfile* h2_os_sin21 = (TProfile*)file2->Get("centrality_ac_fvtxc_tracks_sin21");
  TProfile* h3_os_sin21 = (TProfile*)file3->Get("centrality_ac_fvtxc_tracks_sin21");
  TProfile* h4_os_sin21 = (TProfile*)file4->Get("centrality_ac_fvtxc_tracks_sin21");

  xmin = 0.0;
  xmax = 100.0;
  ymin = -0.2;
  ymax = 0.2;
  TH2D* hd_os_sin21 = new TH2D("hd_os_sin21","",1,xmin,xmax,1,ymin,ymax);
  hd_os_sin21->GetXaxis()->SetTitle("centrality");
  hd_os_sin21->GetYaxis()->SetTitle("#LT#LTsin2#phi#GT#GT");
  hd_os_sin21->GetXaxis()->SetTitleOffset(1.1);
  hd_os_sin21->GetYaxis()->SetTitleOffset(1.4);
  hd_os_sin21->GetXaxis()->SetTitleSize(0.055);
  hd_os_sin21->GetYaxis()->SetTitleSize(0.055);
  hd_os_sin21->GetXaxis()->SetLabelSize(0.055);
  hd_os_sin21->GetYaxis()->SetLabelSize(0.055);
  hd_os_sin21->Draw();
  h1_os_sin21->SetLineColor(kBlack);
  h2_os_sin21->SetLineColor(kRed);
  h3_os_sin21->SetLineColor(kBlue);
  h4_os_sin21->SetLineColor(kGreen+2);
  h1_os_sin21->SetMarkerColor(kBlack);
  h2_os_sin21->SetMarkerColor(kRed);
  h3_os_sin21->SetMarkerColor(kBlue);
  h4_os_sin21->SetMarkerColor(kGreen+2);
  h1_os_sin21->SetMarkerStyle(kOpenSquare);
  h2_os_sin21->SetMarkerStyle(kOpenCircle);
  h3_os_sin21->SetMarkerStyle(kOpenDiamond);
  h4_os_sin21->SetMarkerStyle(kOpenCross);
  h1_os_sin21->Draw("same ex0p");
  h2_os_sin21->Draw("same ex0p");
  h3_os_sin21->Draw("same ex0p");
  h4_os_sin21->Draw("same ex0p");
  TLegend* leg_os_sin21 = new TLegend(0.58,0.68,0.88,0.88);
  leg_os_sin21->AddEntry(h1_os_sin21,leghead1,"p");
  leg_os_sin21->AddEntry(h2_os_sin21,leghead2,"p");
  leg_os_sin21->AddEntry(h3_os_sin21,leghead3,"p");
  leg_os_sin21->AddEntry(h4_os_sin21,leghead4,"p");
  leg_os_sin21->SetTextSize(0.055);
  leg_os_sin21->SetFillStyle(0);
  leg_os_sin21->Draw();
  c1->Print(Form("ComparisonFigs/FourWayComparison_os_sin21_%d_%d%d%d%d.png",name,which1,which2,which3,which4));
  c1->Print(Form("ComparisonFigs/FourWayComparison_os_sin21_%d_%d%d%d%d.pdf",name,which1,which2,which3,which4));

  // --- nfvtxt

  TH1D* h1_nfvtxt = (TH1D*)file1->Get("th1d_nfvtxt_combinedER");
  TH1D* h2_nfvtxt = (TH1D*)file2->Get("th1d_nfvtxt_combinedER");
  TH1D* h3_nfvtxt = (TH1D*)file3->Get("th1d_nfvtxt_combinedER");
  TH1D* h4_nfvtxt = (TH1D*)file4->Get("th1d_nfvtxt_combinedER");

  xmin = 0.0;
  xmax = 1500.0;
  ymin = 1;
  ymax = h1_nfvtxt->GetMaximum();
  TH2D* hd_nfvtxt = new TH2D("hd_nfvtxt","",1,xmin,xmax,1,ymin,ymax);
  hd_nfvtxt->GetXaxis()->SetTitle("number of FVTX tracks");
  hd_nfvtxt->GetYaxis()->SetTitle("number of events");
  hd_nfvtxt->GetXaxis()->SetTitleOffset(1.1);
  hd_nfvtxt->GetYaxis()->SetTitleOffset(1.4);
  hd_nfvtxt->GetXaxis()->SetTitleSize(0.055);
  hd_nfvtxt->GetYaxis()->SetTitleSize(0.055);
  hd_nfvtxt->GetXaxis()->SetLabelSize(0.055);
  hd_nfvtxt->GetYaxis()->SetLabelSize(0.055);
  hd_nfvtxt->Draw();
  h1_nfvtxt->SetLineColor(kBlack);
  h2_nfvtxt->SetLineColor(kRed);
  h3_nfvtxt->SetLineColor(kBlue);
  h4_nfvtxt->SetLineColor(kGreen+2);
  h1_nfvtxt->SetLineWidth(2);
  h2_nfvtxt->SetLineWidth(2);
  h3_nfvtxt->SetLineWidth(2);
  h4_nfvtxt->SetLineWidth(2);
  h1_nfvtxt->SetLineStyle(1);
  h2_nfvtxt->SetLineStyle(2);
  h3_nfvtxt->SetLineStyle(3);
  h4_nfvtxt->SetLineStyle(4);
  h1_nfvtxt->Draw("same");
  h2_nfvtxt->Draw("same");
  h3_nfvtxt->Draw("same");
  h4_nfvtxt->Draw("same");
  TLegend* leg_nfvtxt = new TLegend(0.58,0.68,0.88,0.88);
  leg_nfvtxt->AddEntry(h1_nfvtxt,leghead1,"l");
  leg_nfvtxt->AddEntry(h2_nfvtxt,leghead2,"l");
  leg_nfvtxt->AddEntry(h3_nfvtxt,leghead3,"l");
  leg_nfvtxt->AddEntry(h4_nfvtxt,leghead4,"l");
  leg_nfvtxt->SetTextSize(0.055);
  leg_nfvtxt->SetFillStyle(0);
  leg_nfvtxt->Draw();
  c1->SetLogy();
  c1->Print(Form("ComparisonFigs/FourWayComparison_nfvtxt_%d_%d%d%d%d.png",name,which1,which2,which3,which4));
  c1->Print(Form("ComparisonFigs/FourWayComparison_nfvtxt_%d_%d%d%d%d.pdf",name,which1,which2,which3,which4));

  // --- 2d shenanigans

  return; // runs very slowly so only run it when needed

  gStyle->SetOptTitle(1);

  TCanvas* c2 = new TCanvas("c2","",1000,1000);
  c2->Divide(2,2); // may need to make my own pads, but let's do it the easy way for now...

  TH2D* h1_fbsr = (TH2D*)file1->Get("th2d_nfvtxt_bbcsumratio");
  TH2D* h2_fbsr = (TH2D*)file2->Get("th2d_nfvtxt_bbcsumratio");
  TH2D* h3_fbsr = (TH2D*)file3->Get("th2d_nfvtxt_bbcsumratio");
  TH2D* h4_fbsr = (TH2D*)file4->Get("th2d_nfvtxt_bbcsumratio");

  if ( h1_fbsr )
    {
      c2->cd(1);
      c2->SetLogz(1);
      h1_fbsr->SetTitle(leghead1);
      h1_fbsr->Draw("colz");
    }

  if ( h2_fbsr )
    {
      c2->cd(2);
      c2->SetLogz(1);
      h2_fbsr->SetTitle(leghead2);
      h2_fbsr->Draw("colz");
    }

  if ( h3_fbsr )
    {
      c2->cd(3);
      c2->SetLogz(1);
      h3_fbsr->SetTitle(leghead3);
      h3_fbsr->Draw("colz");
    }

  if ( h4_fbsr )
    {
      c2->cd(4);
      c2->SetLogz(1);
      h4_fbsr->SetTitle(leghead4);
      h4_fbsr->Draw("colz");
    }

  c2->cd(0);

  c2->Print(Form("ComparisonFigs/FourWayComparison_fbsr_%d_%d%d%d%d.png",name,which1,which2,which3,which4));
  c2->Print(Form("ComparisonFigs/FourWayComparison_fbsr_%d_%d%d%d%d.pdf",name,which1,which2,which3,which4));

  delete c1;
  delete c2;

}
