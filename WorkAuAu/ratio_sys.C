#include "systematics_helper.C"
#include "do_ratios.C"


void takefiles(TFile*, TFile*, const char*);


void ratio_sys()
{

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

  fbase = TFile::Open("input/histos_12420.root");
  feval = TFile::Open("input/histos_12432.root");
  takefiles(fbase,feval,"qrbr");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12420.root");
  feval = TFile::Open("input/histos_12555.root");
  takefiles(fbase,feval,"code");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12579.root"); // cent-based q-vector recentering
  feval = TFile::Open("input/histos_12581.root"); // no q-vector recentering
  takefiles(fbase,feval,"noqr");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12579.root"); // cent-based q-vector recentering
  feval = TFile::Open("input/histos_12587.root"); // fvtxt-based q-vector recentering
  takefiles(fbase,feval,"nfqr");
  fbase->Close();
  feval->Close();

  fbase = TFile::Open("input/histos_12587.root"); // fvtxt-based q-vector recentering, regular cuts
  feval = TFile::Open("input/histos_12650.root"); // fvtxt-based q-vector recentering, new cuts
  takefiles(fbase,feval,"newc");
  fbase->Close();
  feval->Close();

}

void takefiles(TFile* fbase, TFile* feval, const char* systype)
{

  if ( !fbase || !feval )
    {
      cout << "One or more files missing " << fbase << " " << feval << endl;
      return;
    }

  TH1D* ratio42_base = NULL;
  TH1D* ratio64_base = NULL;
  TH1D* ratio84_base = NULL;
  get_ratios_histos(fbase,&ratio42_base,&ratio64_base,&ratio84_base,false);

  TH1D* ratio42_eval = NULL;
  TH1D* ratio64_eval = NULL;
  TH1D* ratio84_eval = NULL;
  get_ratios_histos(feval,&ratio42_eval,&ratio64_eval,&ratio84_eval,false);

  crunch(ratio42_base,ratio42_eval,systype,"cent_ratio42",0,100,10,67);
  crunch(ratio64_base,ratio64_eval,systype,"cent_ratio64",0,100,10,67);
  crunch(ratio84_base,ratio84_eval,systype,"cent_ratio84",0,100,10,67);

}

