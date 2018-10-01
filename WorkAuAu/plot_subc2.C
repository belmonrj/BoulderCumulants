void plot_subc2(TH1D*,TH1D*,TH1D*);

void plot_subc2(TH1D*,TH1D*,TH1D*,int);



void plot_subc2(TH1D* th1d_c24, TH1D* th1d_c24aabb, TH1D* th1d_c24abab)
{
  plot_subc2(th1d_c24,th1d_c24aabb,th1d_c24abab,2);
}

void plot_subc2(TH1D* th1d_c24, TH1D* th1d_c24aabb, TH1D* th1d_c24abab, int harm)
{

  TCanvas* c1 = new TCanvas("c1","");

  bool iscent = true;
  bool isntrk = false;

  TGraphAsymmErrors* tgaesys_c34 = NULL;
  TGraphAsymmErrors* tgaesys_c34aabb = NULL;
  TGraphAsymmErrors* tgaesys_c34abab = NULL;

  if ( harm == 3 )
    {
      // th1d_c24->Rebin(5);
      // th1d_c24aabb->Rebin(5);
      // th1d_c24abab->Rebin(5);
      // th1d_c24->Scale(0.2);
      // th1d_c24aabb->Scale(0.2);
      // th1d_c24abab->Scale(0.2);
      th1d_c24->Rebin(5);
      th1d_c24aabb->Rebin(10);
      th1d_c24abab->Rebin(10);
      th1d_c24->Scale(0.2);
      th1d_c24aabb->Scale(0.1);
      th1d_c24abab->Scale(0.1);
      // --- clean out higher bins
      for ( int i = 0; i < th1d_c24aabb->GetNbinsX(); ++i )
        {
          double cent = th1d_c24aabb->GetBinCenter(i+1);
          if ( cent > 50 )
            {
              th1d_c24aabb->SetBinContent(i+1,-999);
              th1d_c24abab->SetBinContent(i+1,-999);
            }
        }
      // now setup some TGraphAsymmErrors stuff for the systematics
      const int nbins0 = th1d_c24->GetNbinsX();
      const int nbins1 = th1d_c24aabb->GetNbinsX();
      const int nbins2 = th1d_c24abab->GetNbinsX();
      float cent0[nbins0];
      float cent1[nbins1];
      float cent2[nbins1];
      float value0[nbins0];
      float value1[nbins1];
      float value2[nbins1];
      float loerr0[nbins0];
      float loerr1[nbins1];
      float loerr2[nbins1];
      float hierr0[nbins0];
      float hierr1[nbins1];
      float hierr2[nbins1];
      // sys type0
      for ( int i = 0; i < nbins0; ++i )
        {
          cent0[i] = th1d_c24->GetBinCenter(i+1);
          value0[i] = th1d_c24->GetBinContent(i+1);
          loerr0[i] = value0[i]*0.6; // use of all bins is intentional
          hierr0[i] = value0[i]*0.3; // use of all bins is intentional
        }
      //tgaesys_c34 = new TGraphAsymmErrors(nbins0,cent0,value0,0,0,loerr0,hierr0);
      tgaesys_c34 = new TGraphAsymmErrors(11,cent0,value0,0,0,loerr0,hierr0);
      tgaesys_c34->SetFillColorAlpha(kBlack,0.35);
      // sys type1
      for ( int i = 0; i < nbins1; ++i )
        {
          cent1[i] = th1d_c24aabb->GetBinCenter(i+1);
          value1[i] = th1d_c24aabb->GetBinContent(i+1);
          loerr1[i] = value1[0]*0.6; // use of first bin is intentional
          hierr1[i] = value1[0]*1.0; // use of first bin is intentional
        }
      //tgaesys_c34aabb = new TGraphAsymmErrors(nbins1,cent1,value1,0,0,loerr1,hierr1);
      tgaesys_c34aabb = new TGraphAsymmErrors(4,cent1,value1,0,0,loerr1,hierr1);
      tgaesys_c34aabb->SetFillColorAlpha(kRed,0.35);
      // sys type2
      for ( int i = 0; i < nbins2; ++i )
        {
          cent2[i] = th1d_c24abab->GetBinCenter(i+1);
          value2[i] = th1d_c24abab->GetBinContent(i+1);
          loerr2[i] = value2[0]*2.0; // use of first bin is intentional
          hierr2[i] = value2[0]*6.0; // use of first bin is intentional
        }
      //tgaesys_c34aabb = new TGraphAsymmErrors(nbins2,cent2,value2,0,0,loerr2,hierr2);
      tgaesys_c34abab = new TGraphAsymmErrors(6,cent2,value2,0,0,loerr2,hierr2);
      tgaesys_c34abab->SetFillColorAlpha(kBlue,0.35);
    } // end of check on harm == 3
  if ( harm == 2 )
    {
      for ( int i = 0; i < th1d_c24->GetNbinsX(); ++i )
        {
          double cent = th1d_c24->GetBinCenter(i+1);
          if ( cent > 65 )
            {
              th1d_c24->SetBinContent(i+1,-999);
              th1d_c24aabb->SetBinContent(i+1,-999);
              th1d_c24abab->SetBinContent(i+1,-999);
            }
        }
    }

  th1d_c24aabb->SetMarkerStyle(kOpenSquare);
  th1d_c24aabb->SetMarkerColor(kRed);
  th1d_c24aabb->SetLineColor(kRed);
  th1d_c24abab->SetMarkerStyle(kOpenDiamond);
  th1d_c24abab->SetMarkerColor(kBlue);
  th1d_c24abab->SetLineColor(kBlue);
  th1d_c24->SetMarkerStyle(kOpenCircle);
  th1d_c24->SetMarkerColor(kBlack);
  th1d_c24->SetLineColor(kBlack);

  double xmin = 0.0;
  double xmax = 100.0;
  if ( harm == 3 ) xmax = 60.0;
  double ymin = -1e-5;
  double ymax = 4e-6;
  if ( harm == 3 )
  {
  // nice
  ymin = -2e-7;
  ymax = 1e-6;
  // matches c34 plot in paper
  ymin = -1e-7;
  ymax = 2e-7;
  }
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle(Form("c_{%d}{4}",harm));
  empty->GetYaxis()->SetTitleOffset(1.2);
  TLine* line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  TLatex* tex_phenix = new TLatex(0.2,0.778,"PHENIX");
  tex_phenix->SetTextSize(0.05);
  tex_phenix->SetNDC();
  tex_phenix->Draw();
  // TLatex* tex_system = new TLatex(0.2,0.80,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  // tex_system->SetTextSize(0.05);
  // tex_system->SetNDC();
  // tex_system->Draw();
  TLatex* tex_tracks = new TLatex(0.2,0.83,"h^{#pm} 1<|#eta|<3");
  tex_tracks->SetTextSize(0.05);
  tex_tracks->SetNDC();
  tex_tracks->Draw();
  TLatex* tex_system = new TLatex(0.2,0.882,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  tex_system->SetTextSize(0.05);
  tex_system->SetNDC();
  tex_system->Draw();
  //TLatex latt;
  //latt.SetNDC();
  //latt.SetTextSize(0.05);
  //latt.SetTextAlign(11);
  //latt.DrawLatex(0.2, 0.71, "Sys. Uncert. 6%");
  //latt.DrawLatex(0.35, 0.21, "Sys. Uncert. 6%");
  th1d_c24->Draw("same ex0p");
  if ( tgaesys_c34 != NULL )
    {
      tgaesys_c34->Draw("3");
    }
  else cout << "No systematics tgae available... " << tgaesys_c34 << endl;
  TLegend* leg24 = new TLegend(0.66,0.86,0.92,0.92);
  leg24->SetTextSize(0.05);
  leg24->SetFillStyle(0);
  leg24->AddEntry(th1d_c24,Form("c_{%d}{4}",harm),"p");
  leg24->Draw();
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x01.png",harm));
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x01.pdf",harm));
  th1d_c24abab->Draw("same ex0p");
  if ( tgaesys_c34abab != NULL )
    {
      tgaesys_c34abab->Draw("3");
    }
  TLegend* leg24abab = new TLegend(0.66,0.80,0.92,0.86);
  leg24abab->SetTextSize(0.05);
  leg24abab->SetFillStyle(0);
  leg24abab->AddEntry(th1d_c24abab,Form("c_{%d}{4}_{ab|ab}",harm),"p");
  leg24abab->Draw();
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x02.png",harm));
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x02.pdf",harm));
  th1d_c24aabb->Draw("same ex0p");
  if ( tgaesys_c34aabb != NULL )
    {
      tgaesys_c34aabb->Draw("3");
    }
  TLegend* leg24aabb = new TLegend(0.66,0.74,0.92,0.80);
  leg24aabb->SetTextSize(0.05);
  leg24aabb->SetFillStyle(0);
  leg24aabb->AddEntry(th1d_c24aabb,Form("c_{%d}{4}_{aa|bb}",harm),"p");
  leg24aabb->Draw();
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x03.png",harm));
  c1->Print(Form("FigsSubevents/cent_subevents_c%d4x03.pdf",harm));

  delete empty;
  delete c1;

}
