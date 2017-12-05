#include "filenames.C"

const int nhistos = 60;




void get_offsets_RBR()
{

  TCanvas* c1 = new TCanvas("c1","");

  ofstream fout("BoulderCumulantsOffsetsExtraExtra.C");
  fout << "#include \"BoulderCumulants.h\"" << endl;
  fout << endl;
  fout << "void BoulderCumulants::SetQvectorOffsetsRBR(int run)" << endl;
  fout << "{" << endl;


  for ( int i = 0; i < nhistos; ++i )
  {
  // --- open the file
  TFile* fin = TFile::Open(filenames[i]);
  //TFile* fin = TFile::Open(Form("SpecialFiles/%s",filenames[i].Data()));
  filenames[i].Remove(6,5);
  cout << "run number " << filenames[i] << endl;

  TProfile* nfvtxt_recoffsets[2][10] = {{NULL}};
  TProfile* centre_recoffsets[2][10] = {{NULL}};
  TProfile* centre_recoffsets_north[2][10] = {{NULL}};
  TProfile* centre_recoffsets_south[2][10] = {{NULL}};
  for ( int cs = 0; cs < 2; ++cs )
    {
      for ( int c = 0; c < 10; ++c )
        {
          nfvtxt_recoffsets[cs][c] = (TProfile*)fin->Get(Form("nfvtxt_recoffsets_%d_%d",cs,c));
          centre_recoffsets[cs][c] = (TProfile*)fin->Get(Form("centrality_recoffsets_%d_%d",cs,c));
          centre_recoffsets_north[cs][c] = (TProfile*)fin->Get(Form("centrality_recoffsets_north_%d_%d",cs,c));
          centre_recoffsets_south[cs][c] = (TProfile*)fin->Get(Form("centrality_recoffsets_south_%d_%d",cs,c));
          // cout << nfvtxt_recoffsets[cs][c]->GetName() << " " << nfvtxt_recoffsets[cs][c] << endl;
          // cout << centre_recoffsets[cs][c]->GetName() << " " << centre_recoffsets[cs][c] << endl;
          // --- draw north
          centre_recoffsets_north[cs][c]->Draw();
          centre_recoffsets_north[cs][c]->SetMinimum(-0.05);
          centre_recoffsets_north[cs][c]->SetMaximum(0.05);
          centre_recoffsets_north[cs][c]->GetXaxis()->SetTitle("centrality");
          if ( cs == 0 ) centre_recoffsets_north[cs][c]->GetYaxis()->SetTitle(Form("north #LTcos %d#phi#GT",c));
          else           centre_recoffsets_north[cs][c]->GetYaxis()->SetTitle(Form("north #LTsin %d#phi#GT",c));
          c1->Print(Form("RBR_figs/qvoff/qvoff_north_%d_%d_%s.png",cs,c,filenames[i].Data()));
          // --- draw south
          centre_recoffsets_south[cs][c]->Draw();
          centre_recoffsets_south[cs][c]->SetMinimum(-0.05);
          centre_recoffsets_south[cs][c]->SetMaximum(0.05);
          centre_recoffsets_south[cs][c]->GetXaxis()->SetTitle("centrality");
          if ( cs == 0 ) centre_recoffsets_south[cs][c]->GetYaxis()->SetTitle(Form("south #LTcos %d#phi#GT",c));
          else           centre_recoffsets_south[cs][c]->GetYaxis()->SetTitle(Form("south #LTsin %d#phi#GT",c));
          c1->Print(Form("RBR_figs/qvoff/qvoff_south_%d_%d_%s.png",cs,c,filenames[i].Data()));
        }
    }

  // return;

  //fout << "  cout << \"run numnber is \" << run << \" but run number not currently used in this function... \" << endl;" << endl;
  fout << "  if ( run == " << filenames[i] << " )\n  {" << endl;
  double qvoff[2][100];
  char name[100];
  // --- centraliy
  for ( int i = 0; i < 100; ++i ) // adjust as needed...
    {
      fout << "  ";
      for ( int cs = 0; cs < 2; ++cs )
        {
          for ( int c = 0; c < 10; ++c )
            {
              qvoff[cs][c] = centre_recoffsets_north[cs][c]->GetBinContent(i+1);
              sprintf(name,"qvoff_cent_north[%d][%d][%d]",i,cs,c);
              char offset[10];
              sprintf(offset,"%.6f",qvoff[cs][c]);
              fout << name << " += " << offset << ";";
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
              char offset[10];
              sprintf(offset,"%.6f",qvoff[cs][c]);
              fout << name << " += " << offset << ";";
              fout << "\t";
            }
        } // end
      fout << endl;
    } // loop over centralities

  fout << "  }" << endl;

  } // loop over histos

  // --- end of function
  fout << "}" << endl;

} // this macro

