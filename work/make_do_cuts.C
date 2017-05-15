void make_do_cuts()
{

  int number_of_problems = 0;

  // --- this was made with root6, so there may be problems when running on RCF...
  TFile* file = TFile::Open("fout.root");

  TGraph* tglower = (TGraph*)file->Get("tglower");
  TGraph* tgupper = (TGraph*)file->Get("tgupper");

  const int nlower = tglower->GetN();
  const int nupper = tgupper->GetN();

  if ( nlower != nupper || nlower > 50 || nupper > 50 )
    {
      cout << "this is very bad" << endl;
      ++number_of_problems;
    }

  // double xlower[nlower];
  // double ylower[nlower];
  // double xupper[nupper];
  // double yupper[nupper];

  double xlower[50];
  double ylower[50];
  double xupper[50];
  double yupper[50];

  for ( int i = 0; i < nlower; ++i ) tglower->GetPoint(i,xlower[i],ylower[i]);
  for ( int i = 0; i < nupper; ++i ) tgupper->GetPoint(i,xupper[i],yupper[i]);

  cout << nlower << " " << nupper << endl;

  double xall[50];
  //double delta_x = 28;

  ofstream fout("tracks_charge_function.C");
  fout << endl;
  fout << "bool tracks_charge_function(int ntracks, double chargesum)" << endl;
  fout << "{" << endl;
  fout << endl;
  fout << "  double cutlow = 0;" << endl;
  fout << "  double cuthigh = 0;" << endl;
  fout << endl;
  fout << "  if ( ntracks < 0 ) return false;" << endl;
  for ( int i = 0; i < 50; ++i )
    {
      //cout << xlower[i] << " " << xupper[i] << " "  << ylower[i] << " " << yupper[i] << " " << endl;
      if ( xlower[i] != xupper[i] ) ++number_of_problems;
      else xall[i] = xlower[i];
      //if ( i > 0 ) cout << "delta x = " << xall[i] - xall[i-1] << endl;
      int bin_low_edge = i*28;
      int bin_high_edge = (i+1)*28;
      int bin_center = bin_low_edge/2 + bin_high_edge/2;
      //cout << i*28 << " " << (i+1)*28 << " " << bin_center << " " << xall[i] << endl;
      fout << "  else if ( ntracks > " << bin_low_edge << " && ntracks <= " << bin_high_edge << ") { cutlow = " << ylower[i] << "; cuthigh = " << yupper[i] << "; }" << endl;
    }
  fout << "  else return false;" << endl;
  fout << endl;
  fout << "  double quantity = chargesum/double(ntracks);" << endl;
  fout << "  if ( quantity >= cutlow && quantity <= cuthigh ) return true;" << endl;
  fout << "  else return false;" << endl;
  fout << endl;
  fout << "}" << endl;
  fout << endl;

  cout << "number of problems is " << number_of_problems << endl;

}
