void compare()
{

  const int nmax = 50;

  TCanvas* c1 = new TCanvas("c1","");

  // ---

  //TFile* fin1 = TFile::Open("tree_old.root"); // first of the recent tree passes
  //TFile* fin1 = TFile::Open("tree_new.root"); // second of the recent tree passes
  TFile* fin1 = TFile::Open("histos_14778.root"); // third of the recent taxi passes
  //TFile* fin1 = TFile::Open("histos_14720.root"); // second of the recent taxi passes
  //TFile* fin1 = TFile::Open("histos_14713.root"); // second of the recent taxi passes
  //TFile* fin2 = TFile::Open("histos_14650.root"); // first of the recent taxi passes
  //TFile* fin2 = TFile::Open("histos_14650.root"); // first of the recent taxi passes
  TFile* fin2 = TFile::Open("improved_20170517-2216.root"); // an old file with results for PPG206

  TProfile* tp1f_two1 = (TProfile*)fin1->Get("nfvtxt_ac_fvtxc_tracks_c22");
  TProfile* tp1f_two2 = (TProfile*)fin2->Get("nfvtxt_ac_fvtxc_tracks_c22");

  tp1f_two2->Draw();
  tp1f_two1->SetLineColor(kRed);
  tp1f_two1->Draw("same");

  TLegend* leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->AddEntry(tp1f_two2,"old, good file","l");
  leg->AddEntry(tp1f_two1,"new file","l");
  leg->Draw();

  c1->Print("figs/oldnew_file_compare_c22.png");

  // ---

  TProfile* tp1f_four1 = (TProfile*)fin1->Get("nfvtxt_ac_fvtxc_tracks_c24");
  TProfile* tp1f_four2 = (TProfile*)fin2->Get("nfvtxt_ac_fvtxc_tracks_c24");

  tp1f_four2->Draw();
  tp1f_four1->SetLineColor(kRed);
  tp1f_four1->Draw("same");

  delete leg;
  leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->AddEntry(tp1f_four2,"old, good file","l");
  leg->AddEntry(tp1f_four1,"new file","l");
  leg->Draw();

  c1->Print("figs/oldnew_file_compare_four.png");

  // ---

  double counts1[nmax];
  double counts2[nmax];
  double ratio[nmax];
  double num[nmax];
  for ( int i = 0; i < nmax; ++i )
    {
      counts1[i] = tp1f_four1->GetBinEntries(i+1);
      counts2[i] = tp1f_four2->GetBinEntries(i+1);
      ratio[i] = counts1[i]/counts2[i];
      num[i] = tp1f_four1->GetBinCenter(i+1);
    }

  TGraph* tg1 = new TGraph(nmax,num,counts1);
  TGraph* tg2 = new TGraph(nmax,num,counts2);
  TGraph* tgR = new TGraph(nmax,num,ratio);

  TH2D* hdummy = new TH2D("hummy","",1,0.0,num[nmax-1],1,0.1,3e7);
  hdummy->Draw();
  hdummy->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  hdummy->GetYaxis()->SetTitle("Number of events");
  tg1->SetLineColor(kRed);
  tg1->Draw("l");
  tg2->Draw("l");
  delete leg;
  leg = new TLegend(0.68,0.28,0.88,0.48);
  leg->AddEntry(tg2,"old, good file","l");
  leg->AddEntry(tg1,"new file","l");
  leg->Draw();
  c1->SetLogy();
  c1->Print("figs/oldnew_file_compare_mult.png");

  delete hdummy;
  hdummy = new TH2D("hummy","",1,0.0,num[nmax-1],1,1e-3,1e3);
  hdummy->Draw();
  hdummy->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  hdummy->GetYaxis()->SetTitle("Number of events, new/old");
  tgR->SetLineColor(kRed);
  tgR->Draw("l");
  c1->SetLogy();
  c1->Print("figs/oldnew_file_compare_multratio.png");
}

