#include "systematics_helper.C"
#include "hsqrt.C"
#include "calc_cumulants.C"
#include "calc_subevents.C"


void takefiles(TFile*, TFile*, const char*);


void get_sys()
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

}

void takefiles(TFile* fbase, TFile* feval, const char* systype)
{

  if ( !fbase || !feval )
    {
      cout << "One or more files missing " << fbase << " " << feval << endl;
      return;
    }

  TProfile* eit_base = (TProfile*)fbase->Get("centrality_recursion_0_6");
  TProfile* six_base = (TProfile*)fbase->Get("centrality_recursion_0_4");
  TProfile* for_base = (TProfile*)fbase->Get("centrality_recursion_0_2");
  TProfile* two_base = (TProfile*)fbase->Get("centrality_recursion_0_0");
  TH1D* v28base = NULL;
  TH1D* v26base = NULL;
  TH1D* v24base = NULL;
  TH1D* v22base = NULL;
  TH1D* c28base = NULL;
  TH1D* c26base = NULL;
  TH1D* c24base = NULL;
  TH1D* c22base = NULL;
  calc_cumulants(eit_base,six_base,for_base,two_base,&v28base,&v26base,&v24base,&v22base,&c28base,&c26base,&c24base,&c22base,1);
  TProfile* eit_eval = (TProfile*)feval->Get("centrality_recursion_0_6");
  TProfile* six_eval = (TProfile*)feval->Get("centrality_recursion_0_4");
  TProfile* for_eval = (TProfile*)feval->Get("centrality_recursion_0_2");
  TProfile* two_eval = (TProfile*)feval->Get("centrality_recursion_0_0");
  TH1D* v28eval = NULL;
  TH1D* v26eval = NULL;
  TH1D* v24eval = NULL;
  TH1D* v22eval = NULL;
  TH1D* c28eval = NULL;
  TH1D* c26eval = NULL;
  TH1D* c24eval = NULL;
  TH1D* c22eval = NULL;
  calc_cumulants(eit_eval,six_eval,for_eval,two_eval,&v28eval,&v26eval,&v24eval,&v22eval,&c28eval,&c26eval,&c24eval,&c22eval,1);
  crunch(v22base,v22eval,systype,"cent_v22",0,100,1,93);
  crunch(v24base,v24eval,systype,"cent_v24",0,100,6,65);
  crunch(v26base,v26eval,systype,"cent_v26",0,100,6,60);
  crunch(v28base,v28eval,systype,"cent_v28",0,100,10,50);

  // ---

  TProfile* base_for = (TProfile*)fbase->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* base_4aabb = (TProfile*)fbase->Get("centrality_os_fvtxsfvtxn_tracks_c24a");
  TProfile* base_4abab = (TProfile*)fbase->Get("centrality_os_fvtxsfvtxn_tracks_c24b");
  TProfile* base_two = (TProfile*)fbase->Get("centrality_os_fvtxc_tracks_c22");
  TProfile* base_2aa = (TProfile*)fbase->Get("centrality_os_fvtxs_tracks_c22");
  TProfile* base_2bb = (TProfile*)fbase->Get("centrality_os_fvtxn_tracks_c22");
  TProfile* base_2ab = (TProfile*)fbase->Get("centrality_os_fvtxsfvtxn_tracks_c22");
  TH1D* hbase_v24 = NULL;
  TH1D* hbase_v24aabb = NULL;
  TH1D* hbase_v24abab = NULL;
  TH1D* hbase_v22 = NULL;
  TH1D* hbase_v22ab = NULL;
  TH1D* hbase_c24 = NULL;
  TH1D* hbase_c24aabb = NULL;
  TH1D* hbase_c24abab = NULL;
  TH1D* hbase_c22 = NULL;
  TH1D* hbase_c22ab = NULL;
  calc_subevents(base_for, base_4aabb, base_4abab,
                 base_two, base_2aa, base_2bb, base_2ab,
                 &hbase_v24, &hbase_v24aabb, &hbase_v24abab, &hbase_v22, &hbase_v22ab,
                 &hbase_c24, &hbase_c24aabb, &hbase_c24abab, &hbase_c22, &hbase_c22ab,
                 1);
  TProfile* eval_for = (TProfile*)feval->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* eval_4aabb = (TProfile*)feval->Get("centrality_os_fvtxsfvtxn_tracks_c24a");
  TProfile* eval_4abab = (TProfile*)feval->Get("centrality_os_fvtxsfvtxn_tracks_c24b");
  TProfile* eval_two = (TProfile*)feval->Get("centrality_os_fvtxc_tracks_c22");
  TProfile* eval_2aa = (TProfile*)feval->Get("centrality_os_fvtxs_tracks_c22");
  TProfile* eval_2bb = (TProfile*)feval->Get("centrality_os_fvtxn_tracks_c22");
  TProfile* eval_2ab = (TProfile*)feval->Get("centrality_os_fvtxsfvtxn_tracks_c22");
  if ( strcmp(systype,"acce") == 0 )
  {
  eval_for = (TProfile*)feval->Get("centrality_ac_fvtxc_tracks_c24");
  eval_4aabb = (TProfile*)feval->Get("centrality_ac_fvtxsfvtxn_tracks_c24a");
  eval_4abab = (TProfile*)feval->Get("centrality_ac_fvtxsfvtxn_tracks_c24b");
  eval_two = (TProfile*)feval->Get("centrality_ac_fvtxc_tracks_c22");
  eval_2aa = (TProfile*)feval->Get("centrality_ac_fvtxs_tracks_c22");
  eval_2bb = (TProfile*)feval->Get("centrality_ac_fvtxn_tracks_c22");
  eval_2ab = (TProfile*)feval->Get("centrality_ac_fvtxsfvtxn_tracks_c22");
  }
  TH1D* heval_v24 = NULL;
  TH1D* heval_v24aabb = NULL;
  TH1D* heval_v24abab = NULL;
  TH1D* heval_v22 = NULL;
  TH1D* heval_v22ab = NULL;
  TH1D* heval_c24 = NULL;
  TH1D* heval_c24aabb = NULL;
  TH1D* heval_c24abab = NULL;
  TH1D* heval_c22 = NULL;
  TH1D* heval_c22ab = NULL;
  calc_subevents(eval_for, eval_4aabb, eval_4abab,
                 eval_two, eval_2aa, eval_2bb, eval_2ab,
                 &heval_v24, &heval_v24aabb, &heval_v24abab, &heval_v22, &heval_v22ab,
                 &heval_c24, &heval_c24aabb, &heval_c24abab, &heval_c22, &heval_c22ab,
                 1);
  crunch(hbase_v22ab,heval_v22ab,systype,"cent_v22ab",0,100,1,93);
  crunch(hbase_v24aabb,heval_v24aabb,systype,"cent_v24aabb",0,100,6,65);
  crunch(hbase_v24abab,heval_v24abab,systype,"cent_v24abab",0,100,6,65);

}

