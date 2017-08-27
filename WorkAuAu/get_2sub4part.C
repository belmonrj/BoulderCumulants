void get_2sub4part()
{

  TCanvas* c1 = new TCanvas("c1","");

  bool iscent = true;
  bool isntrk = false;

  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");

  TProfile* tp1f_2aa = (TProfile*)fin->Get("centrality_os_fvtxs_tracks_c22");
  TProfile* tp1f_2bb = (TProfile*)fin->Get("centrality_os_fvtxn_tracks_c22");
  TProfile* tp1f_2ab = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c22");
  TProfile* tp1f_4aabb = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c24a");
  TProfile* tp1f_4abab = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c24b");

  TH1D* th1d_2aa = tp1f_2aa->ProjectionX("th1d_2aa");
  TH1D* th1d_2bb = tp1f_2bb->ProjectionX("th1d_2bb");
  TH1D* th1d_2ab = tp1f_2ab->ProjectionX("th1d_2ab");
  TH1D* th1d_4aabb = tp1f_4aabb->ProjectionX("th1d_4aabb");
  TH1D* th1d_4abab = tp1f_4abab->ProjectionX("th1d_4abab");

  TH1D* th1d_222aa = (TH1D*)th1d_2aa->Clone("th1d_222aa");
  TH1D* th1d_222bb = (TH1D*)th1d_2bb->Clone("th1d_222bb");
  TH1D* th1d_222ab = (TH1D*)th1d_2ab->Clone("th1d_222ab");
  TH1D* th1d_122ab = (TH1D*)th1d_2ab->Clone("th1d_122ab");
  TH1D* th1d_2aabb = (TH1D*)th1d_2aa->Clone("th1d_2aabb");
  th1d_222aa->Multiply(th1d_2aa); th1d_222aa->Scale(2.0);
  th1d_222bb->Multiply(th1d_2bb); th1d_222bb->Scale(2.0);
  th1d_222ab->Multiply(th1d_2ab); th1d_222ab->Scale(2.0);
  th1d_122ab->Multiply(th1d_2ab);
  th1d_2aabb->Multiply(th1d_2bb);

  TH1D* th1d_caabb = (TH1D*)th1d_4aabb->Clone("th1d_caabb");
  TH1D* th1d_cabab = (TH1D*)th1d_4abab->Clone("th1d_cabab");
  th1d_caabb->Add(th1d_222ab,-1.0);
  th1d_cabab->Add(th1d_2aabb,-1.0);
  th1d_cabab->Add(th1d_122ab,-1.0);

  TH1D* th1d_v24aabb = (TH1D*)th1d_4aabb->Clone("th1d_v24aabb");
  TH1D* th1d_v24abab = (TH1D*)th1d_4abab->Clone("th1d_v24abab");

  TH1D* th1d_v22ab = (TH1D*)th1d_2ab->Clone("th1d_v22ab");

  int nbins = th1d_2aa->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      // --- 4aabb
      double c24aabb = th1d_caabb->GetBinContent(i+1);
      double v24aabb = -9999;
      double twoab = th1d_2ab->GetBinContent(i+1);
      double etwoab = th1d_2ab->GetBinError(i+1);
      double fouraabb = th1d_4aabb->GetBinContent(i+1);
      double efouraabb = th1d_4aabb->GetBinError(i+1);
      double ev24aabb = 0;
      if ( c24aabb < 0 && fouraabb != 0 )
        {
          v24aabb = pow(-c24aabb,(1.0/4.0)); // v2{4} = -c2{4}^{(1/4)}
          // --- need to check this error calc, but i think it's close
          ev24aabb = (1.0/pow(-c24aabb,0.75))*sqrt((twoab*twoab*etwoab*etwoab)+(0.0625*efouraabb*efouraabb));
        }
      th1d_v24aabb->SetBinContent(i+1,v24aabb);
      th1d_v24aabb->SetBinError(i+1,ev24aabb);
      // --- 4abab
      double c24abab = th1d_cabab->GetBinContent(i+1);
      double v24abab = -9999;
      double twoaa = th1d_2aa->GetBinContent(i+1);
      double etwoaa = th1d_2aa->GetBinError(i+1);
      double twobb = th1d_2bb->GetBinContent(i+1);
      double etwobb = th1d_2bb->GetBinError(i+1);
      double fourabab = th1d_4abab->GetBinContent(i+1);
      double efourabab = th1d_4abab->GetBinError(i+1);
      double ev24abab = 0;
      if ( c24abab < 0 && fourabab != 0 )
        {
          v24abab = pow(-c24abab,(1.0/4.0)); // v2{4} = -c2{4}^{(1/4)}
          // --- this is definitely wrong
          ev24abab = (1.0/pow(-c24abab,0.75))*sqrt((twoab*twoab*etwoab*etwoab)+(0.0625*efourabab*efourabab));
        }
      th1d_v24abab->SetBinContent(i+1,v24abab);
      th1d_v24abab->SetBinError(i+1,ev24abab);
      // --- 2ab
      double c22ab = th1d_2ab->GetBinContent(i+1);
      double v22ab = -9999;
      double ev22ab = 0;
      if ( c22ab > 0 )
        {
          v22ab = sqrt(c22ab); // v2{2} = c2{2}^{(1/2)}
          ev22ab = (1.0/v22ab)*etwoab;
        }
      th1d_v22ab->SetBinContent(i+1,v22ab);
      th1d_v22ab->SetBinError(i+1,ev22ab);
    }

  // --------------------------------------------------------------------------------------------------------

  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c22");
  TProfile* tp1f_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c24");

  TH1D* th1d_for = tp1f_for->ProjectionX("th1d_for"); // <4>
  TH1D* th1d_two = tp1f_two->ProjectionX("th1d_two"); // <2>

  TH1D* th1d_222 = (TH1D*)th1d_two->Clone("th1d_222"); // 2<2>^2
  th1d_222->Multiply(th1d_two);
  th1d_222->Scale(2);

  TH1D* th1d_c24 = (TH1D*)th1d_for->Clone("th1d_c24"); // c2{4} = <4> - 2<2>^2
  th1d_c24->Add(th1d_222,-1);

  TH1D* th1d_c22 = (TH1D*)th1d_two->Clone("th1d_c22"); // c2{2} = <2>

  TH1D* th1d_v24 = (TH1D*)th1d_c24->Clone("th1d_v24");
  TH1D* th1d_v22 = (TH1D*)th1d_c24->Clone("th1d_v22");

  //nbins = th1d_c24->GetNbinsX();
  for ( int i = 0; i < nbins; ++i )
    {
      // --- 2-particle
      double c22 = th1d_c22->GetBinContent(i+1);
      double v22 = -9999;
      double ev22 = 0;
      double two = th1d_two->GetBinContent(i+1);
      double etwo = th1d_two->GetBinError(i+1);
      if ( c22 > 0 )
        {
          v22 = sqrt(c22); // v2{2} = c2{2}^{(1/2)}
          ev22 = (1.0/v22)*etwo; // correct formula
        }
      th1d_v22->SetBinContent(i+1,v22);
      th1d_v22->SetBinError(i+1,ev22);
      // --- 4-particle
      double c24 = th1d_c24->GetBinContent(i+1);
      double v24 = -9999;
      double four = th1d_for->GetBinContent(i+1);
      double efour = th1d_for->GetBinError(i+1);
      double ev24 = 0;
      if ( c24 < 0 && four != 0 )
        {
          v24 = pow(-c24,(1.0/4.0)); // v2{4} = -c2{4}^{(1/4)}
          ev24 = (1.0/pow(-c24,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
        }
      th1d_v24->SetBinContent(i+1,v24);
      th1d_v24->SetBinError(i+1,ev24);
    }

  // --------------------------------------------------------------------------------------------------------

  double xmin = 0.0;
  double xmax = 100.0;
  double ymin = 0.0;
  double ymax = 0.12;
  TH2D* empty = new TH2D("empty","",1,xmin,xmax,1,ymin,ymax);
  empty->Draw();
  if ( iscent ) empty->GetXaxis()->SetTitle("Centrality (%)");
  if ( isntrk ) empty->GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  empty->GetYaxis()->SetTitle("v_{2}");
  if ( iscent )
  {
  th1d_v24->GetXaxis()->SetRangeUser(5,70);
  th1d_v24aabb->GetXaxis()->SetRangeUser(5,70);
  th1d_v24abab->GetXaxis()->SetRangeUser(5,70);
  }
  th1d_v24->SetMarkerStyle(kOpenCircle);
  th1d_v24->SetMarkerColor(kBlack);
  th1d_v24->SetLineColor(kBlack);
  th1d_v24->Draw("same ex0p");
  th1d_v24aabb->SetMarkerStyle(kOpenSquare);
  th1d_v24aabb->SetMarkerColor(kRed);
  th1d_v24aabb->SetLineColor(kRed);
  th1d_v24aabb->Draw("same ex0p");
  th1d_v24abab->SetMarkerStyle(kOpenDiamond);
  th1d_v24abab->SetMarkerColor(kBlue);
  th1d_v24abab->SetLineColor(kBlue);
  th1d_v24abab->Draw("same ex0p");
  //if ( leg ) delete leg;
  TLegend* leg = new TLegend(0.62,0.72,0.88,0.92);
  //leg->SetHeader(type);
  leg->SetHeader("Run14AuAu200");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->AddEntry(th1d_v24,"v_{2}{4}","p");
  leg->AddEntry(th1d_v24aabb,"v_{2}{4}_{aa|bb}","p");
  leg->AddEntry(th1d_v24abab,"v_{2}{4}_{ab|ab}","p");
  leg->Draw();
  c1->Print("Figs2sub4part/cent_2sub4part.png");
  c1->Print("Figs2sub4part/cent_2sub4part.pdf");
  th1d_v22->SetMarkerStyle(kOpenCross);
  th1d_v22->SetMarkerColor(kRed);
  th1d_v22->SetLineColor(kRed);
  th1d_v22->Draw("same ex0p");
  th1d_v22ab->SetMarkerStyle(kOpenDiamond);
  th1d_v22ab->SetMarkerColor(kMagenta+2);
  th1d_v22ab->SetLineColor(kMagenta+2);
  th1d_v22ab->Draw("same ex0p");
  TLegend* leg2 = new TLegend(0.48,0.72,0.62,0.88);
  //leg2->SetHeader("Run14AuAu200");
  leg2->SetTextSize(0.045);
  leg2->SetFillStyle(0);
  leg2->AddEntry(th1d_v22,"v_{2}{2}","p");
  leg2->AddEntry(th1d_v22ab,"v_{2}{2}_{a|b}","p");
  leg2->Draw();
  c1->Print("Figs2sub4part/cent_2sub4part2part.png");
  c1->Print("Figs2sub4part/cent_2sub4part2part.pdf");


}
