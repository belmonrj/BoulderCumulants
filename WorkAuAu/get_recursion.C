#include "calc_cumulants.C"
#include "plot_recv2.C"
//#include "plot_recv3.C"
#include "plot_recomp.C"



void get_recursion()
{

  // ------------------------------------------------------------------------
  // --- centrality histograms

  // --- get the file; soft link to latest stable analysis with default cuts
  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");

  // --- get the k-p correlator histograms from the file
  TProfile* eit_cent = (TProfile*)fin->Get("centrality_recursion_0_6");
  TProfile* six_cent = (TProfile*)fin->Get("centrality_recursion_0_4");
  TProfile* for_cent = (TProfile*)fin->Get("centrality_recursion_0_2");
  TProfile* two_cent = (TProfile*)fin->Get("centrality_recursion_0_0");

  // --- plot the v2{k}
  plot_recv2(eit_cent,six_cent,for_cent,two_cent,1,"cent",2);

  // --- plot the components and cumulants
  plot_recomp(eit_cent,six_cent,for_cent,two_cent,1,"cent",2);



  // --- get the k-p correlator histograms from the file
  eit_cent = NULL;
  six_cent = (TProfile*)fin->Get("centrality_recursion_0_5");
  for_cent = (TProfile*)fin->Get("centrality_recursion_0_3");
  two_cent = (TProfile*)fin->Get("centrality_recursion_0_1");

  // --- plot the v3{k}
  plot_recv2(eit_cent,six_cent,for_cent,two_cent,1,"cent",3);

  // --- plot the components and cumulants
  // --- need to come up with something for this...
  plot_recomp(eit_cent,six_cent,for_cent,two_cent,1,"cent",3);



  // ------------------------------------------------------------------------
  // --- N_{tracks}^{FVTX} histograms

  // --- get the k-p correlator histograms from the file
  TProfile* eit_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_6");
  TProfile* six_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_4");
  TProfile* for_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_2");
  TProfile* two_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_0");

  // --- plot the v2{k}
  plot_recv2(eit_ntrk,six_ntrk,for_ntrk,two_ntrk,10,"ntrk",2);

  // --- plot the components and cumulants
  plot_recomp(eit_ntrk,six_ntrk,for_ntrk,two_ntrk,10,"ntrk",2);

  // --- get the k-p correlator histograms from the file
  eit_ntrk = NULL;
  six_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_5");
  for_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_3");
  two_ntrk = (TProfile*)fin->Get("nfvtxt_recursion_0_1");

  // --- plot the v3{k}
  plot_recv2(eit_ntrk,six_ntrk,for_ntrk,two_ntrk,10,"ntrk",3);

  // --- plot the components and cumulants
  // --- need to come up with something for this...
  plot_recomp(eit_ntrk,six_ntrk,for_ntrk,two_ntrk,1,"ntrk",3);

  // ------------------------------------------------------------------------



  cout << "All done. Have a nice day!" << endl;

}

