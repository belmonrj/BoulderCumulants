void new_simple()
{

  // --- Step 1: open the root file with the histograms in it
  TFile* fin = TFile::Open("temp.root");

  // --- Step 2: get the TProfile histograms from the root file
  // --- 2-particle correlator
  TProfile* tp1f_two = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c22");
  // --- 2-particle correlator corrections
  TProfile* tp1f_cos1 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cos21");
  TProfile* tp1f_sin1 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_sin21");
  // --- 2-particle scalar product
  TProfile* tp1f_G_two = (TProfile*)fin->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c22"); // scalar product north*south
  // --- corrections for 2-particle SP
  TProfile* tp1f_cos1_north = (TProfile*)fin->Get("nfvtxt_ac_fvtxn_tracks_cos21");
  TProfile* tp1f_sin1_north = (TProfile*)fin->Get("nfvtxt_ac_fvtxn_tracks_sin21");
  TProfile* tp1f_cos1_south = (TProfile*)fin->Get("nfvtxt_ac_fvtxs_tracks_cos21");
  TProfile* tp1f_sin1_south = (TProfile*)fin->Get("nfvtxt_ac_fvtxs_tracks_sin21");
  // --- 4-particle correlator
  TProfile* tp1f_four = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_c24");
  // --- corrections for 4-particle (also need 2-p corrections above)
  TProfile* tp1f_cossum2 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cossum22");
  TProfile* tp1f_sinsum2 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_sinsum22");
  TProfile* tp1f_cos3 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cos23");
  TProfile* tp1f_sin3 = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_sin23");
  // --- covariance histogram for statistical studies... I should check if it's still there...
  //TProfile* tp1f_cov = (TProfile*)fin->Get("nfvtxt_ac_fvtxc_tracks_cov24");

  // --- Step 3: convert the TProfiles to TH1Ds
  // --- 2-particle correlator
  TH1D* th1d_two = tp1f_two->ProjectionX("th1d_two");
  // --- 2-particle correlator corrections
  TH1D* th1d_cos1 = tp1f_cos1->ProjectionX("th1d_cos1");
  TH1D* th1d_sin1 = tp1f_sin1->ProjectionX("th1d_sin1");
  // --- 2-particle scalar product
  TH1D* th1d_G_two = tp1f_G_two->ProjectionX("th1d_G_two");
  // --- corrections for 2-particle SP
  TH1D* th1d_cos1_north = tp1f_cos1_north->ProjectionX("th1d_cos1_north");
  TH1D* th1d_sin1_north = tp1f_sin1_north->ProjectionX("th1d_sin1_north");
  TH1D* th1d_cos1_south = tp1f_cos1_south->ProjectionX("th1d_cos1_south");
  TH1D* th1d_sin1_south = tp1f_sin1_south->ProjectionX("th1d_sin1_south");
  // --- 4-particle correlator
  TH1D* th1d_four = tp1f_four->ProjectionX("th1d_four");
  // --- corrections for 4-particle (also need 2-p corrections above)
  TH1D* th1d_cossum2 = tp1f_cossum2->ProjectionX("th1d_cossum2");
  TH1D* th1d_sinsum2 = tp1f_sinsum2->ProjectionX("th1d_sinsum2");
  TH1D* th1d_cos3 = tp1f_cos3->ProjectionX("th1d_cos3");
  TH1D* th1d_sin3 = tp1f_sin3->ProjectionX("th1d_sin3");
  // --- covariance histogram for statistical studies... I should check if it's still there...
  //TH1D* th1d_cov = tp1f_cov->ProjectionX("th1d_cov");

  // --- Step 4: make some clones
  TH1D* th1d_c22one = th1d_two->Clone("th1d_c22one");
  TH1D* th1d_c22gap = th1d_G_two->Clone("th1d_c22gap");
  TH1D* th1d_cos1_squared = th1d_cos1->Clone("th1d_cos1_squared");
  TH1D* th1d_sin1_squared = th1d_sin1->Clone("th1d_sin1_squared");
  TH1D* th1d_cos1_north_south = th1d_cos1_north->Clone("th1d_cos1_north_south");
  TH1D* th1d_sin1_north_south = th1d_sin1_north->Clone("th1d_sin1_north_south");

  // --- Step 5: calculate the cumulants
  // --- correction terms
  th1d_cos1_squared->Multiply(th1d_cos1_squared);
  th1d_sin1_squared->Multiply(th1d_sin1_squared);
  // --- apply correction to cumulant
  th1d_c22one->Add(th1d_cos1_squared,-1.0);
  th1d_c22one->Add(th1d_sin1_squared,-1.0);

  // --- Step 6: calcualte v2 from cumulant


}
