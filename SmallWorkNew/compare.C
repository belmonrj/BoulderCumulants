void compare()
{

  TCanvas* c1 = new TCanvas("c1","");

  // ---

  //TFile* fin1 = TFile::Open("temp.root");
  TFile* fin1 = TFile::Open("tree_temp.root");
  TFile* fin2 = TFile::Open("improved_20170517-2216.root"); // checking against an old file

  TProfile* tp1f_two1 = (TProfile*)fin1->Get("nfvtxt_ac_fvtxc_tracks_c22");
  TProfile* tp1f_two2 = (TProfile*)fin2->Get("nfvtxt_ac_fvtxc_tracks_c22");

  tp1f_two2->Draw();
  tp1f_two1->SetLineColor(kRed);
  tp1f_two1->Draw("same");

  TLegend* leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->AddEntry(tp1f_two2,"old, good file","l");
  leg->AddEntry(tp1f_two1,"new file","l");
  leg->Draw();

  c1->Print("oldnew_file_compare_c22.png");

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

  c1->Print("oldnew_file_compare_four.png");

}

