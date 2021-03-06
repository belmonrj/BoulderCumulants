void calc_cumulants(TProfile* tp1f_eit, TProfile* tp1f_six, TProfile* tp1f_for, TProfile* tp1f_two,
                   TH1D** out_v28, TH1D** out_v26, TH1D** out_v24, TH1D** out_v22,
                   TH1D** out_c28, TH1D** out_c26, TH1D** out_c24, TH1D** out_c22,
                   TH1D** out_eit, TH1D** out_six, TH1D** out_for, TH1D** out_two,
                   TH1D** out_862, TH1D** out_842, TH1D** out_822, TH1D** out_824,
                   TH1D** out_942, TH1D** out_123, TH1D** out_222,
                   int rebin)
{

  double rand = gRandom->Rndm();
  int helper = rand*10000;
  // cout << "using random number helper " << helper << " to prevent memory leaks" << endl;

  // ---------------------------------------------------------------------------
  // --- build in fault tolerance for null histos
  // --- 8-particle fault tolerance
  if ( tp1f_eit == NULL )
    {
      // --- make a helper histo
      TProfile *h = NULL;
      // --- find a non-null histo
      if ( h == NULL ) h = tp1f_six;
      if ( h == NULL ) h = tp1f_for;
      if ( h == NULL ) h = tp1f_two;
      // --- if even two particle histo is NULL, exit
      if ( h == NULL )
        {
          cout << "ERROR: Need at least one non-null histogram " << endl;
          return;
        }
      cout << "WARNING: 8-particle histogram found to be null" << endl;
      // --- make a clone and set all values to zero
      tp1f_eit = (TProfile*)h->Clone("tp1f_eit");
      for ( int i = 0; i < h->GetNbinsX(); ++i )
        {
          tp1f_eit->SetBinContent(i+1,0.0);
          tp1f_eit->SetBinError(i+1,0.0);
        }
    }
  // --- 6-particle fault tolerance
  if ( tp1f_six == NULL )
    {
      // --- make a helper histo
      TProfile *h = NULL;
      // --- find a non-null histo
      if ( h == NULL ) h = tp1f_for;
      if ( h == NULL ) h = tp1f_two;
      // --- if even two particle histo is NULL, exit
      if ( h == NULL )
        {
          cout << "ERROR: Need at least one non-null histogram " << endl;
          return;
        }
      cout << "WARNING: 6-particle histogram found to be null" << endl;
      // --- make a clone and set all values to zero
      tp1f_six = (TProfile*)h->Clone("tp1f_six");
      for ( int i = 0; i < h->GetNbinsX(); ++i )
        {
          tp1f_six->SetBinContent(i+1,0.0);
          tp1f_six->SetBinError(i+1,0.0);
        }
    }
  // --- 4-particle fault tolerance
  if ( tp1f_for == NULL )
    {
      // --- make a helper histo
      TProfile *h = NULL;
      // --- find a non-null histo
      if ( h == NULL ) h = tp1f_two;
      // --- if even two particle histo is NULL, exit
      if ( h == NULL )
        {
          cout << "ERROR: Need at least one non-null histogram " << endl;
          return;
        }
      cout << "WARNING: 6-particle histogram found to be null" << endl;
      // --- make a clone and set all values to zero
      tp1f_for = (TProfile*)h->Clone("tp1f_for");
      for ( int i = 0; i < h->GetNbinsX(); ++i )
        {
          tp1f_for->SetBinContent(i+1,0.0);
          tp1f_for->SetBinError(i+1,0.0);
        }
    }
  // ---------------------------------------------------------------------------

  TProfile* ctp1f_eit = (TProfile*)tp1f_eit->Clone(Form("ctp1f_eit_%d",helper));
  TProfile* ctp1f_six = (TProfile*)tp1f_six->Clone(Form("ctp1f_eit_%d",helper));
  TProfile* ctp1f_for = (TProfile*)tp1f_for->Clone(Form("ctp1f_eit_%d",helper));
  TProfile* ctp1f_two = (TProfile*)tp1f_two->Clone(Form("ctp1f_eit_%d",helper));

  ctp1f_eit->Rebin(rebin);
  ctp1f_six->Rebin(rebin);
  ctp1f_for->Rebin(rebin);
  ctp1f_two->Rebin(rebin);

  TH1D* th1d_eit = ctp1f_eit->ProjectionX(Form("th1d_eit_%d",helper)); // <8>
  TH1D* th1d_six = ctp1f_six->ProjectionX(Form("th1d_six_%d",helper)); // <6>
  TH1D* th1d_for = ctp1f_for->ProjectionX(Form("th1d_for_%d",helper)); // <4>
  TH1D* th1d_two = ctp1f_two->ProjectionX(Form("th1d_two_%d",helper)); // <2>

  TH1D* th1d_862 = (TH1D*)th1d_six->Clone(Form("th1d_862_%d",helper)); // 16<6><2>     (for the 8p)
  TH1D* th1d_842 = (TH1D*)th1d_for->Clone(Form("th1d_842_%d",helper)); // 18<4>^2      (for the 8p)
  TH1D* th1d_822 = (TH1D*)th1d_for->Clone(Form("th1d_822_%d",helper)); // 144<4><2>^2  (for the 8p)
  TH1D* th1d_824 = (TH1D*)th1d_two->Clone(Form("th1d_824_%d",helper)); // 144<2>^4     (for the 8p)
  TH1D* th1d_942 = (TH1D*)th1d_for->Clone(Form("th1d_942_%d",helper)); // 9<4><2>      (for the 6p)
  TH1D* th1d_123 = (TH1D*)th1d_two->Clone(Form("th1d_123_%d",helper)); // 12<2>^3      (for the 6p)
  TH1D* th1d_222 = (TH1D*)th1d_two->Clone(Form("th1d_222_%d",helper)); // 2<2>^2       (for the 4p)

  // --- 8p pieces
  th1d_862->Multiply(th1d_two);
  th1d_862->Scale(16);
  th1d_842->Multiply(th1d_for);
  th1d_842->Scale(18);
  th1d_822->Multiply(th1d_two);
  th1d_822->Multiply(th1d_two);
  th1d_822->Scale(144);
  th1d_824->Multiply(th1d_two);
  th1d_824->Multiply(th1d_two);
  th1d_824->Multiply(th1d_two);
  th1d_824->Scale(144);
  // --- 6p pieces
  th1d_942->Multiply(th1d_two);
  th1d_942->Scale(9);
  th1d_123->Multiply(th1d_two);
  th1d_123->Multiply(th1d_two);
  th1d_123->Scale(12);
  // --- 4p pieces
  th1d_222->Multiply(th1d_two);
  th1d_222->Scale(2);

  TH1D* th1d_c28 = (TH1D*)th1d_eit->Clone("th1d_c28"); // c2{8} = <8> - 16<6><2> -18<4>^2 + 144<4><2>^2 -144<2>^4
  th1d_c28->Add(th1d_862,-1);
  th1d_c28->Add(th1d_842,-1);
  th1d_c28->Add(th1d_822,1);
  th1d_c28->Add(th1d_824,-1);

  TH1D* th1d_c26 = (TH1D*)th1d_six->Clone("th1d_c26"); // c2{6} = <6> - 9<4><2> + 12<2>^3
  th1d_c26->Add(th1d_942,-1);
  th1d_c26->Add(th1d_123,1);

  TH1D* th1d_c24 = (TH1D*)th1d_for->Clone("th1d_c24"); // c2{4} = <4> - 2<2>^2
  th1d_c24->Add(th1d_222,-1);

  TH1D* th1d_c22 = (TH1D*)th1d_two->Clone("th1d_c22"); // c2{2} = <2>

  TH1D* th1d_v28 = (TH1D*)th1d_c28->Clone("th1d_v28");
  TH1D* th1d_v26 = (TH1D*)th1d_c26->Clone("th1d_v26");
  TH1D* th1d_v24 = (TH1D*)th1d_c24->Clone("th1d_v24");
  TH1D* th1d_v22 = (TH1D*)th1d_c24->Clone("th1d_v22");

  int nbins = th1d_c26->GetNbinsX();
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
      // --- 6-particle
      double c26 = th1d_c26->GetBinContent(i+1);
      double v26 = -9999;
      double ev26 = 0;
      double six = th1d_six->GetBinContent(i+1);
      double esix = th1d_six->GetBinError(i+1);
      if ( c26 > 0 && six != 0 )
        {
          v26 = pow((0.25*c26),(1.0/6.0)); // v2{6} = (c2{6}/4)^{(1/6)}
          ev26 = (1.0/pow(2*c26,(5.0/6.0))) *
            sqrt(
                 (4.5*(4*two*two-four)*(4*two*two-four)*etwo*etwo) +
                 (4.5*two*two*efour*efour) +
                 (1.0/18.0)*esix*esix
                 );
        }
      th1d_v26->SetBinContent(i+1,v26);
      th1d_v26->SetBinError(i+1,ev26);
      // --- 8-particle
      double c28 = th1d_c28->GetBinContent(i+1);
      double v28 = -9999;
      double ev28 = 0;
      double eit = th1d_eit->GetBinContent(i+1);
      double eeit = th1d_eit->GetBinError(i+1);
      eeit = 0.0; // error on this one seems really wrong...
      if ( c28 < 0 && eit != 0 )
        {
          v28 = pow((-c28/33.0),(1.0/8.0)); // v2{8} = (-c2{8}/33)^{(1/8)}
          // ev28 = ( 2*pow(33,(1.0/8.0)) / pow(-c28,(7.0/8.0)) ) *
          //   sqrt(
          //        ( (36*two*two*two - 18*four*two + six)*(36*two*two*two - 18*four*two + six) * etwo*etwo ) +
          //        ( (81.0/16.0)*(4*two*two-four)*(4*two*two-four) * efour*efour ) +
          //        ( two*two*esix*esix ) +
          //        ( (1.0/256.0)*eeit*eeit )
          //        ); // issues fixed but looks wrong
          double prefix = ( 2*pow(33,(1.0/8.0)) / pow(-c28,(7.0/8.0)) );
          double term1  = ( (36*two*two*two - 18*four*two + six)*(36*two*two*two - 18*four*two + six) * etwo*etwo );
          double term2  = ( (81.0/16.0)*(4*two*two-four)*(4*two*two-four) * efour*efour );
          double term3  = ( two*two*esix*esix );
          double term4  = ( (1.0/256.0)*eeit*eeit );
          term3 = 0; // term3 seems problematic...
          ev28 = prefix * sqrt(term1 + term2 + term3 + term4);
          // cout << prefix * sqrt(term1) << " " << prefix * sqrt(term2) << " " << prefix * sqrt(term3) << " " << prefix * sqrt(term4) << " "
          //      << ev28 << endl;
        }
      //ev28 = 0;
      //cout << i << " v28 " << v28 << " ev28 " << ev28 << endl;
      //cout << etwo/two << " " << efour/four << " " << esix/six << " " << eeit/eit << endl;
      th1d_v28->SetBinContent(i+1,v28);
      th1d_v28->SetBinError(i+1,ev28);
    }

  *out_v28 = th1d_v28;
  *out_v26 = th1d_v26;
  *out_v24 = th1d_v24;
  *out_v22 = th1d_v22;

  *out_c28 = th1d_c28;
  *out_c26 = th1d_c26;
  *out_c24 = th1d_c24;
  *out_c22 = th1d_c22;

  *out_eit = th1d_eit;
  *out_six = th1d_six;
  *out_for = th1d_for;
  *out_two = th1d_two;

  *out_862 = th1d_862;
  *out_842 = th1d_842;
  *out_822 = th1d_822;
  *out_824 = th1d_824;
  *out_942 = th1d_942;
  *out_123 = th1d_123;
  *out_222 = th1d_222;

}


void calc_cumulants(TProfile* tp1f_eit, TProfile* tp1f_six, TProfile* tp1f_for, TProfile* tp1f_two,
                   TH1D** out_v28, TH1D** out_v26, TH1D** out_v24, TH1D** out_v22,
                   TH1D** out_c28, TH1D** out_c26, TH1D** out_c24, TH1D** out_c22,
                   int rebin)
{
  TH1D* h = NULL;
  calc_cumulants(tp1f_eit,tp1f_six,tp1f_for,tp1f_two,out_v28,out_v26,out_v24,out_v22,out_c28,out_c26,out_c24,out_c22,
                &h,&h,&h,&h,&h,&h,&h,&h,&h,&h,&h,rebin);
}


void calc_cumulants(TProfile* tp1f_eit, TProfile* tp1f_six, TProfile* tp1f_for, TProfile* tp1f_two,
                   TH1D** out_v28, TH1D** out_v26, TH1D** out_v24, TH1D** out_v22, int rebin)
{
  TH1D* h = NULL;
  calc_cumulants(tp1f_eit,tp1f_six,tp1f_for,tp1f_two,out_v28,out_v26,out_v24,out_v22,&h,&h,&h,&h,rebin);
}


void calc_cumulants(TProfile* tp1f_eit, TProfile* tp1f_six, TProfile* tp1f_for, TProfile* tp1f_two,
                   TH1D** out_v28, TH1D** out_v26, TH1D** out_v24, TH1D** out_v22)
{
  TH1D* h = NULL;
  calc_cumulants(tp1f_eit,tp1f_six,tp1f_for,tp1f_two,out_v28,out_v26,out_v24,out_v22,&h,&h,&h,&h,1);
}

