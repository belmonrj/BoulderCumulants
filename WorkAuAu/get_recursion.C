#include "get_cumulants.C"
#include "plot_recv2.C"
#include "plot_recomp.C"

void get_recursion()
{

  // ------------------------------------------------------------------------

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





  // ------------------------------------------------------------------------

  cout << "All done. Have a nice day!" << endl;

}

