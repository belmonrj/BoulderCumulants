#include "systematics_helper.C"
#include "hsqrt.C"
#include "calc_cumulants.C"
#include "calc_subevents.C"

void takefiles(TFile*, TFile*, const char*);
void takefiles(TFile*, TFile*, const char*, int);

void help_v3_csys()
{

  cout << "Starting..." << endl;

  TFile* fbase = NULL;
  TFile* feval = NULL;

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12290.root");
  takefiles(fbase,feval,"dcar");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12195.root");
  takefiles(fbase,feval,"zvtx");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12194.root");
  takefiles(fbase,feval,"chi2");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_12289.root");
  takefiles(fbase,feval,"nhit");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12097.root");
  feval = TFile::Open("input/histos_99999.root");
  takefiles(fbase,feval,"acce");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12420.root");
  feval = TFile::Open("input/histos_12432.root");
  takefiles(fbase,feval,"qrbr");
  fbase->Close();
  feval->Close();

  //fbase = TFile::Open("input/histos_12581.root"); no q-vector recentering
  fbase = TFile::Open("input/histos_12579.root"); // cent-based
  feval = TFile::Open("input/histos_12587.root");
  takefiles(fbase,feval,"nfqr");
  fbase->Close();
  feval->Close();

  cout << "All done.  Have a nice day!" << endl;

}

void takefiles(TFile* fbase, TFile* feval, const char* systype)
{

  takefiles(fbase,feval,systype,3);
  takefiles(fbase,feval,systype,4);

}

void takefiles(TFile* fbase, TFile* feval, const char* systype, int harmonic)
{

  //int harmonic = 3;
  int rebin = 2;

  bool isacce = false;
  if ( strcmp(systype,"acce") == 0 ) isacce = true;

  // --- make sure both files are not null
  if ( !fbase || !feval )
    {
      cout << "One or more files missing for " << systype << ": " << fbase << " " << feval << endl;
      return;
    }

  // --- get the <<2>> and <<4>> (3rd harmonic)
  TProfile* for_base = NULL;
  TProfile* two_base = NULL;
  TProfile* for_eval = NULL;
  TProfile* two_eval = NULL;
  if ( harmonic == 3 )
    {
      for_base = (TProfile*)fbase->Get("centrality_recursion_0_3");
      two_base = (TProfile*)fbase->Get("centrality_recursion_0_1");
      for_eval = (TProfile*)feval->Get("centrality_recursion_0_3");
      two_eval = (TProfile*)feval->Get("centrality_recursion_0_1");
    }
  if ( harmonic == 4 )
    {
      for_base = (TProfile*)fbase->Get("centrality_recursion_0_9");
      two_base = (TProfile*)fbase->Get("centrality_recursion_0_7");
      for_eval = (TProfile*)feval->Get("centrality_recursion_0_9");
      two_eval = (TProfile*)feval->Get("centrality_recursion_0_7");
    }

  // --- check for existence of histograms, exit if missing
  if ( for_base == NULL ||  two_base == NULL ||  for_eval == NULL ||  two_eval == NULL )
    {
      cout << "One or more histograms missing for " << systype << ": \n";
      cout << "for_base " << for_base << " \n";
      cout << "two_base " << two_base << " \n";
      cout << "for_eval " << for_eval << " \n";
      cout << "two_eval " << two_eval << " \n";
      cout << endl;
      return;
    }


  for_base->Rebin(rebin);
  two_base->Rebin(rebin);
  if ( !isacce )
    {
      for_eval->Rebin(rebin);
      two_eval->Rebin(rebin);
    }

  crunch_cumu4(for_base,two_base,for_eval,two_eval,systype,harmonic);

  TProfile* reg_base = NULL;
  TProfile* gap_base = NULL;
  TProfile* reg_eval = NULL;
  TProfile* gap_eval = NULL;
  TH1D* vn2_base = NULL;
  TH1D* vn2_eval = NULL;
  TH1D* vn2gap_base = NULL;
  TH1D* vn2gap_eval = NULL;
  if ( harmonic == 3 )
    {
      cout << "doing more for third harmonic..." << endl;
      reg_base = (TProfile*)fbase->Get("centrality_ac_fvtxc_tracks_c32");
      reg_eval = (TProfile*)feval->Get("centrality_ac_fvtxc_tracks_c32");
      gap_base = (TProfile*)fbase->Get("centrality_ac_fvtxsfvtxn_tracks_c32");
      gap_eval = (TProfile*)feval->Get("centrality_ac_fvtxsfvtxn_tracks_c32");
      vn2_base = hsqrt(reg_base);
      vn2_eval = hsqrt(reg_eval);
      vn2gap_base = hsqrt(gap_base);
      vn2gap_eval = hsqrt(gap_eval);
      crunch(vn2_base,vn2_eval,systype,"v32ac",0,100,1,70);
      crunch(vn2gap_base,vn2gap_eval,systype,"v32acgap",0,100,1,70);
      reg_base = (TProfile*)fbase->Get("centrality_os_fvtxc_tracks_c32");
      reg_eval = (TProfile*)feval->Get("centrality_os_fvtxc_tracks_c32");
      gap_base = (TProfile*)fbase->Get("centrality_os_fvtxsfvtxn_tracks_c32");
      gap_eval = (TProfile*)feval->Get("centrality_os_fvtxsfvtxn_tracks_c32");
      vn2_base = hsqrt(reg_base);
      vn2_eval = hsqrt(reg_eval);
      vn2gap_base = hsqrt(gap_base);
      vn2gap_eval = hsqrt(gap_eval);
      crunch(vn2_base,vn2_eval,systype,"v32os",0,100,1,70);
      crunch(vn2gap_base,vn2gap_eval,systype,"v32osgap",0,100,1,70);
    }
  if ( harmonic == 4 )
    {
      cout << "not doing more for fourth harmonic, no histograms available.." << endl;
      // reg_base = (TProfile*)fbase->Get("centrality_ac_fvtxc_tracks_c42");
      // reg_eval = (TProfile*)feval->Get("centrality_ac_fvtxc_tracks_c42");
      // gap_base = (TProfile*)fbase->Get("centrality_ac_fvtxsfvtxn_tracks_c42");
      // gap_eval = (TProfile*)feval->Get("centrality_ac_fvtxsfvtxn_tracks_c42");
      // vn2_base = hsqrt(reg_base);
      // vn2_eval = hsqrt(reg_eval);
      // vn2gap_base = hsqrt(gap_base);
      // vn2gap_eval = hsqrt(gap_eval);
      // crunch(vn2_base,vn2_eval,systype,"v42ac",0,100,1,70);
      // crunch(vn2gap_base,vn2gap_eval,systype,"v42acgap",0,100,1,70);
    }



}

