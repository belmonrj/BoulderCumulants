#include "get_cumulants.C"
#include "plot_recv2.C"
#include "plot_recomp.C"

void get_recursion()
{

  // ------------------------------------------------------------------------

  // --- get the file; soft link to latest stable analysis with default cuts
  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");

  // --- get the k-p correlator histograms from the file
  TProfile* eit_cent = (TProfile*)fin->Get("centrality_recursion_0_6");
  TProfile* six_cent = (TProfile*)fin->Get("centrality_recursion_0_4");
  TProfile* for_cent = (TProfile*)fin->Get("centrality_recursion_0_2");
  TProfile* two_cent = (TProfile*)fin->Get("centrality_recursion_0_0");

  // --- plot the v2{k}
  plot_recv2(eit_cent,six_cent,for_cent,two_cent,1,"cent");

  // --- plot the components and cumulants
  plot_recomp(eit_cent,six_cent,for_cent,two_cent,1,"cent");

  // ------------------------------------------------------------------------

  // --- get the k-p correlator histograms from the file
  TProfile* eit_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_6");
  TProfile* six_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_4");
  TProfile* for_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_2");
  TProfile* two_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_0");

  // --- plot the v2{k}
  plot_recv2(eit_ntrk,six_ntrk,for_ntrk,two_ntrk,1,"ntrk");

  // --- plot the components and cumulants
  plot_recomp(eit_ntrk,six_ntrk,for_ntrk,two_ntrk,1,"ntrk");

  // ------------------------------------------------------------------------

  cout << "All done. Have a nice day!" << endl;

}

