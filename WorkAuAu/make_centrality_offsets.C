void make_centrality_offsets()
{

  // --- read in the file
  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");
  // --- get the histograms (only looking at north and south for now, no higher detail)
  TProfile* tp1f_offset_centrality_qx2_south = (TProfile*)fin->Get("centrality_tracks_south_qx2");
  TProfile* tp1f_offset_centrality_qx4_south = (TProfile*)fin->Get("centrality_tracks_south_qx4");
  TProfile* tp1f_offset_centrality_qx6_south = (TProfile*)fin->Get("centrality_tracks_south_qx6");
  TProfile* tp1f_offset_centrality_qy2_south = (TProfile*)fin->Get("centrality_tracks_south_qy2");
  TProfile* tp1f_offset_centrality_qy4_south = (TProfile*)fin->Get("centrality_tracks_south_qy4");
  TProfile* tp1f_offset_centrality_qy6_south = (TProfile*)fin->Get("centrality_tracks_south_qy6");
  TProfile* tp1f_offset_centrality_qx2_north = (TProfile*)fin->Get("centrality_tracks_north_qx2");
  TProfile* tp1f_offset_centrality_qx4_north = (TProfile*)fin->Get("centrality_tracks_north_qx4");
  TProfile* tp1f_offset_centrality_qx6_north = (TProfile*)fin->Get("centrality_tracks_north_qx6");
  TProfile* tp1f_offset_centrality_qy2_north = (TProfile*)fin->Get("centrality_tracks_north_qy2");
  TProfile* tp1f_offset_centrality_qy4_north = (TProfile*)fin->Get("centrality_tracks_north_qy4");
  TProfile* tp1f_offset_centrality_qy6_north = (TProfile*)fin->Get("centrality_tracks_north_qy6");

  ofstream fout("BoulderCumulantsOffsets.C");
  fout << "#include \"BoulderCumulants.h\"" << endl;
  fout << endl;
  fout << "void BoulderCumulants::SetQvectorOffsets(int run)" << endl;
  fout << "{" << endl;
  //fout << "  cout << \"run numnber is \" << run << \" but run number not currently used in this function... \" << endl;" << endl;
  fout << "  if ( run < 0 ) return;" << endl;
  for ( int i = 0; i < 100; ++i )
    {
      // --- get the offsets for the ith bin
      double offset_centrality_qx2_south = tp1f_offset_centrality_qx2_south->GetBinContent(i+1);
      double offset_centrality_qx4_south = tp1f_offset_centrality_qx4_south->GetBinContent(i+1);
      double offset_centrality_qx6_south = tp1f_offset_centrality_qx6_south->GetBinContent(i+1);
      double offset_centrality_qy2_south = tp1f_offset_centrality_qy2_south->GetBinContent(i+1);
      double offset_centrality_qy4_south = tp1f_offset_centrality_qy4_south->GetBinContent(i+1);
      double offset_centrality_qy6_south = tp1f_offset_centrality_qy6_south->GetBinContent(i+1);
      double offset_centrality_qx2_north = tp1f_offset_centrality_qx2_north->GetBinContent(i+1);
      double offset_centrality_qx4_north = tp1f_offset_centrality_qx4_north->GetBinContent(i+1);
      double offset_centrality_qx6_north = tp1f_offset_centrality_qx6_north->GetBinContent(i+1);
      double offset_centrality_qy2_north = tp1f_offset_centrality_qy2_north->GetBinContent(i+1);
      double offset_centrality_qy4_north = tp1f_offset_centrality_qy4_north->GetBinContent(i+1);
      double offset_centrality_qy6_north = tp1f_offset_centrality_qy6_north->GetBinContent(i+1);
      // --- print to the file
      fout << "  offset_centrality_qx2_south[" << i << "] = " << offset_centrality_qx2_south << ";\t";
      fout << "  offset_centrality_qx4_south[" << i << "] = " << offset_centrality_qx4_south << ";\t";
      fout << "  offset_centrality_qx6_south[" << i << "] = " << offset_centrality_qx6_south << ";\t";
      fout << endl;
      fout << "  offset_centrality_qy2_south[" << i << "] = " << offset_centrality_qy2_south << ";\t";
      fout << "  offset_centrality_qy4_south[" << i << "] = " << offset_centrality_qy4_south << ";\t";
      fout << "  offset_centrality_qy6_south[" << i << "] = " << offset_centrality_qy6_south << ";\t";
      fout << endl;
      fout << "  offset_centrality_qx2_north[" << i << "] = " << offset_centrality_qx2_north << ";\t";
      fout << "  offset_centrality_qx4_north[" << i << "] = " << offset_centrality_qx4_north << ";\t";
      fout << "  offset_centrality_qx6_north[" << i << "] = " << offset_centrality_qx6_north << ";\t";
      fout << endl;
      fout << "  offset_centrality_qy2_north[" << i << "] = " << offset_centrality_qy2_north << ";\t";
      fout << "  offset_centrality_qy4_north[" << i << "] = " << offset_centrality_qy4_north << ";\t";
      fout << "  offset_centrality_qy6_north[" << i << "] = " << offset_centrality_qy6_north << ";\t";
      fout << endl;
    }
  fout << "}" << endl;
}
