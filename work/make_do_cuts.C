void make_do_cuts()
{

  int number_of_problems = 0;

  TFile* file = TFile::Open("fout.root");

  TGraph* tglower = (TGraph*)file->Get("tglower");
  TGraph* tgupper = (TGraph*)file->Get("tgupper");

  const int nlower = tglower->GetN();
  const int nupper = tgupper->GetN();

  double xlower[nlower];
  double ylower[nlower];
  double xupper[nupper];
  double yupper[nupper];

  if ( nlower != nupper )
    {
      cout << "what the fuck" << endl;
      ++number_of_problems;
    }

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
  fout << "  double quantity = double(ntracks)/chargesum;" << endl;
  fout << "  if ( quantity >= cutlow && quanity <= cuthigh ) return true;" << endl;
  fout << "  else return false;" << endl;
  fout << endl;
  fout << "}" << endl;
  fout << endl;

  cout << "number of problems is " << number_of_problems << endl;

}
