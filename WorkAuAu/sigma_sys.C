#include "systematics_helper.C"
#include "hsqrt.C"
#include "calc_cumulants.C"
#include "calc_subevents.C"
#include "get_sigma.C"


void takefiles(TFile*, TFile*, const char*);


void sigma_sys()
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

  TH1D* sigma_base = get_sigma_histo(fbase,1,"cent");
  TH1D* sigma_eval = get_sigma_histo(feval,1,"cent");

  crunch(sigma_base,sigma_eval,systype,"cent_sigma",0,100,10,67);

}

