void get_2sub4part()
{

  TFile* fin = TFile::Open("input/histos_11609.root");

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
    }

}
