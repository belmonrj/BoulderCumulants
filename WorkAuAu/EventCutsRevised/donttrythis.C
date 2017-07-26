void donttrythis()
{

  TCanvas* c1 = new TCanvas("c1","");

  TFile* file = TFile::Open("input/cumulants_Run14AuAu200.root");
  TH2D* histo = (TH2D*)file->Get("th2d_nfvtxt_bbcsumratio");
  TFile* file2 =  TFile::Open("jout.root");
  TGraph* tg_upper = (TGraph*)file2->Get("tgupper");
  TGraph* tg_lower = (TGraph*)file2->Get("tglower");

  histo->RebinX(10);
  histo->GetXaxis()->SetRangeUser(0,1000);
  histo->Draw("colz");
  tg_upper->SetLineColor(1);
  tg_lower->SetLineColor(1);
  tg_upper->SetLineWidth(2);
  tg_lower->SetLineWidth(2);
  tg_upper->Draw("l");
  tg_lower->Draw("l");

  c1->Print("noreallydonttrythis.png");


}
