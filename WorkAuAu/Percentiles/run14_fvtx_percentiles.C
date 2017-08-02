void run14_fvtx_percentiles()
{

  gStyle->SetOptStat(0);

  TFile* file = TFile::Open("input/cumulants_Run14AuAu200.root");
  if ( !file )
    {
      cout << "uh oh" << endl;
      return;
    }

  TH1D* histo = (TH1D*)file->Get("th1d_nfvtxt_combinedER");
  if ( !histo )
    {
      cout << "uh oh" << endl;
    }

  int max = 1500;
  double total = histo->Integral(1,max);
  double five, ten, twenty, forty, sixty;
  for ( int i = max-1; i > 0; --i )
    {
      double integral = histo->Integral(i,max);
      double percentile = integral/total;
      percentile *= 100.0; // turn into percent
      //if ( percentile > 4.99 && percentile < 5.01 )
      if ( percentile > 4.9 && percentile < 5.1 )
        {
          cout << "5% most central events " << i << " " << percentile << endl;
          five = i;
        }
      //if ( percentile > 9.99 && percentile < 10.01 )
      if ( percentile > 9.9 && percentile < 10.1 )
        {
          cout << "10% most central events " << i << " " << percentile << endl;
          ten = i;
        }
      //if ( percentile > 19.99 && percentile < 20.01 )
      if ( percentile > 19.9 && percentile < 20.1 )
        {
          cout << "20% most central events " << i << " " << percentile << endl;
          twenty = i;
        }
      //if ( percentile > 39.99 && percentile < 40.01 )
      if ( percentile > 39.9 && percentile < 40.1 )
        {
          cout << "40% most central events " << i << " " << percentile << endl;
          forty = i;
        }
      //if ( percentile > 59.99 && percentile < 60.01 )
      if ( percentile > 59.9 && percentile < 60.1 )
        {
          cout << "60% most central events " << i << " " << percentile << endl;
          sixty = i;
        }
      if ( i == 700 || i == 650 || i == 600 )
        {
          cout << i << " " << percentile << endl;
        }
    } // end of loop

  TCanvas* c1 = new TCanvas();
  c1->SetTicks();

  // c1->SetMargin(0.15,0.02,0.15,0.02);
  // c1->SetMargin(0.10,0.02,0.10,0.02);
  // c1->SetMargin(0.10,0.10,0.10,0.02);
  c1->SetMargin(0.10,0.10,0.15,0.02);

  histo->GetXaxis()->SetRangeUser(-0.5,max+0.5);
  histo->GetXaxis()->SetTitle("N^{FVTX}_{tracks}");
  histo->GetXaxis()->SetTitleSize(0.05);
  histo->GetXaxis()->SetLabelSize(0.05);
  histo->GetYaxis()->SetTitle("Number of events");
  histo->GetYaxis()->SetTitleSize(0.05);
  histo->GetYaxis()->SetLabelSize(0.05);
  histo->SetLineColor(kBlack);
  int linewidth = 2;
  histo->SetLineWidth(linewidth);
  histo->Draw();
  c1->SetLogy();

  TH1D* histo_five = (TH1D*)histo->Clone("histo_five");
  TH1D* histo_ten = (TH1D*)histo->Clone("histo_ten");
  TH1D* histo_twenty = (TH1D*)histo->Clone("histo_twenty");
  TH1D* histo_forty = (TH1D*)histo->Clone("histo_forty");
  TH1D* histo_sixty = (TH1D*)histo->Clone("histo_sixty");

  histo_five->SetFillColor(kRed);
  histo_five->GetXaxis()->SetRangeUser(five,max);
  histo_five->Draw("same");
  histo_ten->SetFillColor(kYellow);
  histo_ten->GetXaxis()->SetRangeUser(ten,five);
  histo_ten->Draw("same");
  //histo_twenty->SetFillColor(kBlue); // hard to read black text on blue background
  histo_twenty->SetFillColor(kAzure-4);
  histo_twenty->GetXaxis()->SetRangeUser(twenty,ten);
  histo_twenty->Draw("same");
  histo_forty->SetFillColor(kGreen+2);
  histo_forty->GetXaxis()->SetRangeUser(forty,twenty);
  histo_forty->Draw("same");
  histo_sixty->SetFillColor(kMagenta+2);
  histo_sixty->GetXaxis()->SetRangeUser(sixty,forty);
  histo_sixty->Draw("same");

  histo->Draw("sameaxis"); // to get tick marks back, they get hidden by the fill colors

  double height = histo->GetMaximum();
  //  height *= 1.8;

  // TLine line_five(five,0,five,height);
  // TLine line_ten(ten,0,ten,height);
  // TLine line_twenty(twenty,0,twenty,height);
  // TLine line_forty(forty,0,forty,height);
  // TLine line_sixty(sixty,0,sixty,height);

  TLine line_five(five,0,five,histo->GetBinContent(histo->FindBin(five)));
  TLine line_ten(ten,0,ten,histo->GetBinContent(histo->FindBin(ten)));
  TLine line_twenty(twenty,0,twenty,histo->GetBinContent(histo->FindBin(twenty)));
  TLine line_forty(forty,0,forty,histo->GetBinContent(histo->FindBin(forty)));
  TLine line_sixty(sixty,0,sixty,histo->GetBinContent(histo->FindBin(sixty)));

  line_five.SetLineWidth(linewidth);
  line_ten.SetLineWidth(linewidth);
  line_twenty.SetLineWidth(linewidth);
  line_forty.SetLineWidth(linewidth);
  line_sixty.SetLineWidth(linewidth);

  line_five.Draw();
  line_ten.Draw();
  line_twenty.Draw();
  line_forty.Draw();
  line_sixty.Draw();

  TLatex* tex = new TLatex(0,0,"");
  //tex->SetNDC();
  tex->SetTextSize(0.05);
  // tex->DrawLatex(0.70,0.2,"0-5%");
  // tex->DrawLatex(0.50,0.2,"5-10%");
  // tex->DrawLatex(0.35,0.2,"10-20%");
  // tex->DrawLatex(0.20,0.2,"20-40%");
  tex->DrawLatex(five,height*0.00002,"0-5%");
  tex->DrawLatex(ten,height*0.0002,"5-10%");
  tex->DrawLatex(twenty,height*0.002,"10-20%");
  tex->DrawLatex(forty,height*0.02,"20-40%");

  c1->Print("Run14FVTXPercentiles.png");
  c1->Print("Run14FVTXPercentiles.pdf");

} // end of function
