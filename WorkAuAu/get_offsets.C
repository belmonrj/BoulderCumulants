//#include <iomanip>

void get_offsets()
{

  // --- read in the file
  TFile* fin = TFile::Open("input/histos_12581.root");
  // --- get the histograms (only looking at north and south for now, no higher detail)
  TProfile* nfvtxt_recoffsets[2][10] = {{NULL}};
  TProfile* nfvtxt_recoffsets_north[2][10] = {{NULL}};
  TProfile* nfvtxt_recoffsets_south[2][10] = {{NULL}};
  TProfile* centre_recoffsets[2][10] = {{NULL}};
  TProfile* centre_recoffsets_north[2][10] = {{NULL}};
  TProfile* centre_recoffsets_south[2][10] = {{NULL}};
  for ( int cs = 0; cs < 2; ++cs )
    {
      for ( int c = 0; c < 10; ++c )
        {
          nfvtxt_recoffsets[cs][c] = (TProfile*)fin->Get(Form("nfvtxt_recoffsets_%d_%d",cs,c));
          nfvtxt_recoffsets_north[cs][c] = (TProfile*)fin->Get(Form("nfvtxt_recoffsets_north_%d_%d",cs,c));
          nfvtxt_recoffsets_south[cs][c] = (TProfile*)fin->Get(Form("nfvtxt_recoffsets_south_%d_%d",cs,c));
          centre_recoffsets[cs][c] = (TProfile*)fin->Get(Form("centrality_recoffsets_%d_%d",cs,c));
          centre_recoffsets_north[cs][c] = (TProfile*)fin->Get(Form("centrality_recoffsets_north_%d_%d",cs,c));
          centre_recoffsets_south[cs][c] = (TProfile*)fin->Get(Form("centrality_recoffsets_south_%d_%d",cs,c));
          // cout << nfvtxt_recoffsets[cs][c]->GetName() << " " << nfvtxt_recoffsets[cs][c] << endl;
          // cout << centre_recoffsets[cs][c]->GetName() << " " << centre_recoffsets[cs][c] << endl;
        }
    }

  // return;

  ofstream fout("BoulderCumulantsOffsetsExtra.C");
  fout << "#include <iostream>" << endl;
  fout << "#include \"BoulderCumulants.h\"" << endl;
  fout << endl;
  fout << "using std::cout;" << endl;
  fout << "using std::endl;" << endl;
  fout << endl;
  fout << "void BoulderCumulants::SetQvectorOffsets(int run)" << endl;
  fout << "{" << endl;
  //fout << "  cout << \"run numnber is \" << run << \" but run number not currently used in this function... \" << endl;" << endl;
  fout << "  if ( run < 0 ) return;" << endl;
  fout << "  if ( _verbosity > 1 ) cout << \"setting Q-vector offsets...\" << endl;" << endl;

  double qvoff[2][100];
  char name[100];
  // --- loop over tracks
  // --- skipping tracks for the time being...
  /*
  for ( int i = 0; i < 650; ++i ) // adjust as needed...
    {
      fout << "  ";
      for ( int cs = 0; cs < 2; ++cs )
        {
          for ( int c = 0; c < 10; ++c )
            {
              qvoff[cs][c] = nfvtxt_recoffsets[cs][c]->GetBinContent(i+1);
              sprintf(name,"qvoff_nfvtxt[%d][%d][%d]",i,cs,c);
              //fout << setprecision(6);
              char offset[10];
              sprintf(offset,"%.6f",qvoff[cs][c]);
              fout << name << " = " << offset << ";";
              fout << "\t";
            }
        } // end
      fout << endl;
    } // end of loop over number of tracks
  */
  // --- now loop over centralities
  /*
  for ( int i = 0; i < 100; ++i ) // adjust as needed...
    {
      fout << "  ";
      for ( int cs = 0; cs < 2; ++cs )
        {
          for ( int c = 0; c < 10; ++c )
            {
              qvoff[cs][c] = centre_recoffsets[cs][c]->GetBinContent(i+1);
              sprintf(name,"qvoff_cent[%d][%d][%d]",i,cs,c);
              //fout << setprecision(6);
              char offset[10];
              sprintf(offset,"%.6f",qvoff[cs][c]);
              fout << name << " = " << offset << ";";
              fout << "\t";
            }
        } // end
      fout << endl;
    } // end of loop over number of tracks
  */
  for ( int i = 0; i < 650; ++i ) // adjust as needed...
    {
      fout << "  ";
      for ( int cs = 0; cs < 2; ++cs )
        {
          for ( int c = 0; c < 10; ++c )
            {
              qvoff[cs][c] = nfvtxt_recoffsets_north[cs][c]->GetBinContent(i+1);
              sprintf(name,"qvoff_nfvtxt_north[%d][%d][%d]",i,cs,c);
              //fout << setprecision(6);
              char offset[10];
              sprintf(offset,"%.10f",qvoff[cs][c]);
              fout << name << " = " << offset << ";";
              fout << "\t";
            }
        } // end
      fout << endl;
    } // end of loop over number of tracks
  for ( int i = 0; i < 650; ++i ) // adjust as needed...
    {
      fout << "  ";
      for ( int cs = 0; cs < 2; ++cs )
        {
          for ( int c = 0; c < 10; ++c )
            {
              qvoff[cs][c] = nfvtxt_recoffsets_south[cs][c]->GetBinContent(i+1);
              sprintf(name,"qvoff_nfvtxt_south[%d][%d][%d]",i,cs,c);
              //fout << setprecision(6);
              char offset[10];
              sprintf(offset,"%.10f",qvoff[cs][c]);
              fout << name << " = " << offset << ";";
              fout << "\t";
            }
        } // end
      fout << endl;
    } // end of loop over number of tracks
  /*
  for ( int i = 0; i < 100; ++i ) // adjust as needed...
    {
      fout << "  ";
      for ( int cs = 0; cs < 2; ++cs )
        {
          for ( int c = 0; c < 10; ++c )
            {
              qvoff[cs][c] = centre_recoffsets_north[cs][c]->GetBinContent(i+1);
              sprintf(name,"qvoff_cent_north[%d][%d][%d]",i,cs,c);
              //fout << setprecision(6);
              char offset[10];
              sprintf(offset,"%.6f",qvoff[cs][c]);
              fout << name << " = " << offset << ";";
              fout << "\t";
            }
        } // end
      fout << endl;
    } // end of loop over number of tracks
  for ( int i = 0; i < 100; ++i ) // adjust as needed...
    {
      fout << "  ";
      for ( int cs = 0; cs < 2; ++cs )
        {
          for ( int c = 0; c < 10; ++c )
            {
              qvoff[cs][c] = centre_recoffsets_south[cs][c]->GetBinContent(i+1);
              sprintf(name,"qvoff_cent_south[%d][%d][%d]",i,cs,c);
              //fout << setprecision(6);
              char offset[10];
              sprintf(offset,"%.6f",qvoff[cs][c]);
              fout << name << " = " << offset << ";";
              fout << "\t";
            }
        } // end
      fout << endl;
    } // end of loop over number of tracks
  */
  // --- end of function
  fout << "}" << endl;

}

