void find_cut()
{

  TCanvas* c1 = new TCanvas("c1","");
  c1->SetMargin(0.12,0.12,0.12,0.08); // LRBT

  //TFile* file = TFile::Open("../input/cumulants_Run14AuAu200.root");
  TFile* file = TFile::Open("../input/histos_14051.root");
  TH2D* histo = (TH2D*)file->Get("th2d_nfvtxt_bbcsumratio");

  histo->RebinX(10);
  histo->GetXaxis()->SetRangeUser(0,1000);
  histo->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  histo->GetYaxis()->SetTitle("Q^{BBC}_{N+S}/N_{tracks}^{FVTX}");
  histo->Draw("colz");

  TProfile* tp1f_histo = histo->ProfileX("tp1f_histo",1,-1,"s");
  //tp1f_histo->Draw("same");

  TH1D* th1d_histo = tp1f_histo->ProjectionX("th1d_histo");
  TH1D* th1d_upper = (TH1D*)th1d_histo->Clone("th1d_upper");
  TH1D* th1d_lower = (TH1D*)th1d_histo->Clone("th1d_lower");

  for ( int i = 0; i < th1d_histo->GetNbinsX(); ++i )
    {
      double mean = tp1f_histo->GetBinContent(i+1);
      double sigma = tp1f_histo->GetBinError(i+1);
      // note that 1.65 sigma ~ 90% CI
      th1d_upper->SetBinContent(i+1,mean+1.65*sigma);
      th1d_lower->SetBinContent(i+1,mean-1.65*sigma);
      th1d_upper->SetBinError(i+1,mean*0.00001);
      th1d_lower->SetBinError(i+1,mean*0.00001);
      th1d_histo->SetBinError(i+1,1.65*sigma);
    }
  th1d_histo->SetLineWidth(2);
  th1d_upper->SetLineWidth(2);
  th1d_lower->SetLineWidth(2);
  th1d_histo->SetLineColor(1);
  th1d_upper->SetLineColor(1);
  th1d_lower->SetLineColor(1);
  th1d_histo->Draw("same");
  th1d_upper->Draw("same");
  th1d_lower->Draw("same");

  c1->Print("make_the_cut.png");
  c1->Print("make_the_cut.pdf");

  ofstream fout("tracks_charge_function.C");
  fout << endl;
  fout << "bool tracks_charge_function(int ntracks, double chargesum)" << endl;
  fout << "{" << endl;
  fout << endl;
  fout << "  double cutlow = 0;" << endl;
  fout << "  double cuthigh = 0;" << endl;
  fout << endl;
  fout << "  if ( ntracks < 0 ) return false;" << endl;
  for ( int i = 0; i < 65; ++i )
    {
      int bin_low_edge = th1d_histo->GetBinLowEdge(i+1);
      int bin_high_edge = th1d_histo->GetBinLowEdge(i+2); // no get bin high edge
      int bin_center = th1d_histo->GetBinCenter(i+1);
      double ylower = th1d_lower->GetBinContent(i+1);
      double yupper = th1d_upper->GetBinContent(i+1);
      fout << "  else if ( ntracks > " << bin_low_edge << " && ntracks <= " << bin_high_edge << ") { cutlow = " << ylower << "; cuthigh = " << yupper << "; }" << endl;
    }
  fout << "  else return false;" << endl;
  fout << endl;
  fout << "  double quantity = chargesum/double(ntracks);" << endl;
  fout << "  if ( quantity >= cutlow && quantity <= cuthigh ) return true;" << endl;
  fout << "  else return false;" << endl;
  fout << endl;
  fout << "}" << endl;
  fout << endl;


}
