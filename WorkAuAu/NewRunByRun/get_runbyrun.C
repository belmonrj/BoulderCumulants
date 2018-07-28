void crunch(int);

TFile* fout;

void get_runbyrun()
{

  gStyle->SetOptTitle(1);

  fout = new TFile("rbr_offsets.root","recreate");

  ifstream fin;
  fin.open("run14auau.list");
  int run;
  while ( fin >> run )
    {
      //if ( run > 406000) break;
      cout << "Processing run " << run << endl;
      crunch(run);
    }

  fout->Write();
  fout->Close();
  delete fout;

}


void crunch(int run)
{

  TFile* file = TFile::Open(Form("RunFiles/%d.root",run));
  if ( file == NULL ) { cout << "run number " << run << " not found" << endl; return; }

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
          nfvtxt_recoffsets[cs][c] = (TProfile*)file->Get(Form("nfvtxt_recoffsets_%d_%d",cs,c));
          nfvtxt_recoffsets_north[cs][c] = (TProfile*)file->Get(Form("nfvtxt_recoffsets_north_%d_%d",cs,c));
          nfvtxt_recoffsets_south[cs][c] = (TProfile*)file->Get(Form("nfvtxt_recoffsets_south_%d_%d",cs,c));
          centre_recoffsets[cs][c] = (TProfile*)file->Get(Form("centrality_recoffsets_%d_%d",cs,c));
          centre_recoffsets_north[cs][c] = (TProfile*)file->Get(Form("centrality_recoffsets_north_%d_%d",cs,c));
          centre_recoffsets_south[cs][c] = (TProfile*)file->Get(Form("centrality_recoffsets_south_%d_%d",cs,c));
          // cout << nfvtxt_recoffsets[cs][c]->GetName() << " " << nfvtxt_recoffsets[cs][c] << endl;
          // cout << centre_recoffsets[cs][c]->GetName() << " " << centre_recoffsets[cs][c] << endl;
          fout->cd();
          centre_recoffsets_north[cs][c]->SetName(Form("run%d_%s",run,centre_recoffsets_north[cs][c]->GetName() ) );
          centre_recoffsets_south[cs][c]->SetName(Form("run%d_%s",run,centre_recoffsets_south[cs][c]->GetName() ) );
          centre_recoffsets_north[cs][c]->Write();
          centre_recoffsets_south[cs][c]->Write();
        }
    }


}

