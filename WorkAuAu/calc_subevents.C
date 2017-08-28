void calc_subevents(const TProfile* tp1f_for, const TProfile* tp1f_4aabb, const TProfile* tp1f_4abab,
                    const TProfile* tp1f_two, const TProfile* tp1f_2aa, const TProfile* tp1f_2bb, const TProfile* tp1f_2ab,
                    TH1D** out_v24, TH1D** out_v24aabb, TH1D** out_v24abab, TH1D** out_v22, TH1D** out_v22ab,
                    TH1D** out_c24, TH1D** out_c24aabb, TH1D** out_c24abab, TH1D** out_c22, TH1D** out_c22ab,
                    int rebin)
{

  double rand = gRandom->Rndm();
  int helper = rand*10000;

  TH1D* th1d_2aa = tp1f_2aa->ProjectionX(Form("th1d_2aa_%d",helper));
  TH1D* th1d_2bb = tp1f_2bb->ProjectionX(Form("th1d_2bb_%d",helper));
  TH1D* th1d_2ab = tp1f_2ab->ProjectionX(Form("th1d_2ab_%d",helper));
  TH1D* th1d_4aabb = tp1f_4aabb->ProjectionX(Form("th1d_4aabb_%d",helper));
  TH1D* th1d_4abab = tp1f_4abab->ProjectionX(Form("th1d_4abab_%d",helper));

  TH1D* th1d_222aa = (TH1D*)th1d_2aa->Clone(Form("th1d_222aa_%d",helper));
  TH1D* th1d_222bb = (TH1D*)th1d_2bb->Clone(Form("th1d_222bb_%d",helper));
  TH1D* th1d_222ab = (TH1D*)th1d_2ab->Clone(Form("th1d_222ab_%d",helper));
  TH1D* th1d_122ab = (TH1D*)th1d_2ab->Clone(Form("th1d_122ab_%d",helper));
  TH1D* th1d_2aabb = (TH1D*)th1d_2aa->Clone(Form("th1d_2aabb_%d",helper));
  th1d_222aa->Multiply(th1d_2aa); th1d_222aa->Scale(2.0);
  th1d_222bb->Multiply(th1d_2bb); th1d_222bb->Scale(2.0);
  th1d_222ab->Multiply(th1d_2ab); th1d_222ab->Scale(2.0);
  th1d_122ab->Multiply(th1d_2ab);
  th1d_2aabb->Multiply(th1d_2bb);

  TH1D* th1d_caabb = (TH1D*)th1d_4aabb->Clone(Form("th1d_caabb_%d",helper));
  TH1D* th1d_cabab = (TH1D*)th1d_4abab->Clone(Form("th1d_cabab_%d",helper));
  th1d_caabb->Add(th1d_222ab,-1.0);
  th1d_cabab->Add(th1d_2aabb,-1.0);
  th1d_cabab->Add(th1d_122ab,-1.0);

  TH1D* th1d_v24aabb = (TH1D*)th1d_4aabb->Clone(Form("th1d_v24aabb_%d",helper));
  TH1D* th1d_v24abab = (TH1D*)th1d_4abab->Clone(Form("th1d_v24abab_%d",helper));

  TH1D* th1d_v22ab = (TH1D*)th1d_2ab->Clone(Form("th1d_v22ab_%d",helper));

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

  // TProfile* tp1f_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c22");
  // TProfile* tp1f_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c24");

  TH1D* th1d_for = tp1f_for->ProjectionX(Form("th1d_for_%d",helper)); // <4>
  TH1D* th1d_two = tp1f_two->ProjectionX(Form("th1d_two_%d",helper)); // <2>

  TH1D* th1d_222 = (TH1D*)th1d_two->Clone(Form("th1d_222_%d",helper)); // 2<2>^2
  th1d_222->Multiply(th1d_two);
  th1d_222->Scale(2);

  TH1D* th1d_c24 = (TH1D*)th1d_for->Clone(Form("th1d_c24_%d",helper)); // c2{4} = <4> - 2<2>^2
  th1d_c24->Add(th1d_222,-1);

  TH1D* th1d_c22 = (TH1D*)th1d_two->Clone(Form("th1d_c22_%d",helper)); // c2{2} = <2>

  TH1D* th1d_v24 = (TH1D*)th1d_c24->Clone(Form("th1d_v24_%d",helper));
  TH1D* th1d_v22 = (TH1D*)th1d_c24->Clone(Form("th1d_v22_%d",helper));

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

  *out_v24 = th1d_v24;
  *out_v24aabb = th1d_v24aabb;
  *out_v24abab = th1d_v24abab;
  *out_v22 = th1d_v22;
  *out_v22ab = th1d_v22ab;

  *out_c24 = th1d_c24;
  *out_c24aabb = th1d_caabb;
  *out_c24abab = th1d_cabab;
  *out_c22 = th1d_c22;
  *out_c22ab = th1d_2ab;

}
