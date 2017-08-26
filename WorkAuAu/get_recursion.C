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
  // --- initialize the pointers
  TH1D* v28cent = NULL;
  TH1D* v26cent = NULL;
  TH1D* v24cent = NULL;
  TH1D* v22cent = NULL;
  TH1D* c28cent = NULL;
  TH1D* c26cent = NULL;
  TH1D* c24cent = NULL;
  TH1D* c22cent = NULL;
  TH1D* heitcent = NULL;
  TH1D* hsixcent = NULL;
  TH1D* hforcent = NULL;
  TH1D* htwocent = NULL;
  TH1D* h862cent = NULL;
  TH1D* h842cent = NULL;
  TH1D* h822cent = NULL;
  TH1D* h824cent = NULL;
  TH1D* h942cent = NULL;
  TH1D* h123cent = NULL;
  TH1D* h222cent = NULL;
  // --- get all the v2{k}, c2{k}, and component histograms
  get_cumulants(eit_cent,  six_cent,  for_cent,  two_cent,
                &v28cent,  &v26cent,  &v24cent,  &v22cent,
                &c28cent,  &c26cent,  &c24cent,  &c22cent,
                &heitcent, &hsixcent, &hforcent, &htwocent,
                &h862cent, &h842cent, &h822cent, &h824cent,
                &h942cent, &h123cent, &h222cent,
                1);
  // --- plot the v2{k}
  plot_recv2(v28cent,v26cent,v24cent,v22cent,"cent");
  // --- plot the components and cumulants
  plot_recomp(c28cent,  c26cent,  c24cent,  c22cent,
              heitcent, hsixcent, hforcent, htwocent,
              h862cent, h842cent, h822cent, h824cent,
              h942cent, h123cent, h222cent,
              "cent");

  // ------------------------------------------------------------------------





  // ------------------------------------------------------------------------

  cout << "All done. Have a nice day!" << endl;

}

