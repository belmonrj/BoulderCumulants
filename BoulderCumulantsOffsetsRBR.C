#include <iostream>
#include "TFile.h"
#include "TProfile.h"
#include "BoulderCumulants.h"

using std::cout;
using std::endl;

void BoulderCumulants::SetQvectorOffsetsRBR(int run)
{

  cout << "Setting Q-vector offsets..." << endl;

  //cout << "Since the previous version took 20 minutes to compile, let's do nothing until we come up with a better way..." << endl;
  if ( run < 0 )
    {
      cout << "Invalid run number, no offsets can be set" << endl;
      return;
    }

  cout << "Now geting offsets file" << endl;
  TFile* file = TFile::Open("rbr_offsets.root");
  if ( file == NULL )
    {
      cout << "Offset histogram file not found" << endl;
      return; // should modify routine to add return values to check...
    }

  cout << "Now looping to get offset histos and set offsets" << endl;
  for ( int cs = 0; cs < 2; ++cs )
    {
      for ( int c = 0; c < maxHarmonic; ++c )
        {
          TProfile* tp1f_cent_north = (TProfile*)file->Get(Form("run%d_centrality_recoffsets_north_%d_%d",run,cs,c));
          TProfile* tp1f_cent_south = (TProfile*)file->Get(Form("run%d_centrality_recoffsets_south_%d_%d",run,cs,c));
          if ( !tp1f_cent_north || !tp1f_cent_south )
            {
              cout << "Offset histogram(s) not found" << endl;
              cout << tp1f_cent_north << endl;
              cout << tp1f_cent_south << endl;
              return; // should modify routine to add return values to check...
            }
          for ( int i = 0; i < 100; ++i )
            {
              qvoff_cent_north[i][cs][c] = tp1f_cent_north->GetBinContent(i+1);
              qvoff_cent_south[i][cs][c] = tp1f_cent_south->GetBinContent(i+1);
            } // loop over centralities
        } // loop over harmonics
    } // loop over cos (0) or sin (1)

} // void BoulderCumulants::SetQvectorOffsetsRBR(int run)


