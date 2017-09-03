void more_percentiles()
{

  gStyle->SetOptStat(0);

  TFile* file = TFile::Open("../input/cumulants_Run14AuAu200.root");
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



  const int max = 700;
  double total = histo->Integral(1,max);
  //vector<double> percentiles;
  double percentiles[max];
  for ( int i = max-1; i > 0; --i )
    {
      double integral = histo->Integral(i,max);
      double percentile = integral/total;
      percentile *= 100.0; // turn into percent
      percentiles[i] = percentile;
    } // end of loop



  double differences[100][max];
  for ( int icent = 0; icent < 100; ++icent )
    {
      for ( int ip = max-1; ip > 0; --ip )
        {
          // if ( percentiles[ip] > icent+1 ) continue;
          // if ( percentiles[ip] < icent-1 ) continue;
          differences[icent][ip] = fabs(percentiles[ip]-icent);
        }
    }



  for ( int icent = 0; icent < 100; ++icent )
    {
      //double minimum = *min_element(differences[i].begin(),differences[i].end());
      //double minimum = differences[icent][0];
      double minimum = 99999;
      int which = 0;
      //cout << "minimum is " << minimum << endl;
      for ( int ip = max-1; ip > 0; --ip )
        {
          if ( percentiles[ip] > icent+1 ) continue;
          if ( percentiles[ip] < icent-1 ) continue;
          if ( differences[icent][ip] == 0 ) continue; // exactly zero unrealistic and likely indicative of some problem
          // cout << "icent " << icent << " ip=" << ip << "/" << max << " "
          //      << "percentiles " << percentiles[ip] << " "
          //      << "differences " << differences[icent][ip] << " "
          //      << "x"
          //      << endl;
          if(differences[icent][ip]<minimum)
            {
              minimum = differences[icent][ip];
              which = ip;
            }
        }
      cout << "found minimum " << icent << " " << which << " " << minimum << " " << percentiles[which] << endl;
    }

} // end of function
