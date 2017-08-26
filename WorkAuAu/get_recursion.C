#include "get_cumulants.C"
#include "plot_recv2.C"

void get_recursion()
{

  // ------------------------------------------------------------------------

  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");

  TProfile* eit_cent = (TProfile*)fin->Get("centrality_recursion_0_6");
  TProfile* six_cent = (TProfile*)fin->Get("centrality_recursion_0_4");
  TProfile* for_cent = (TProfile*)fin->Get("centrality_recursion_0_2");
  TProfile* two_cent = (TProfile*)fin->Get("centrality_recursion_0_0");
  TH1D* v28cent = NULL;
  TH1D* v26cent = NULL;
  TH1D* v24cent = NULL;
  TH1D* v22cent = NULL;
  TH1D* c28cent = NULL;
  TH1D* c26cent = NULL;
  TH1D* c24cent = NULL;
  TH1D* c22cent = NULL;
  get_cumulants(eit_cent,six_cent,for_cent,two_cent,&v28cent,&v26cent,&v24cent,&v22cent,&c28cent,&c26cent,&c24cent,&c22cent,1);
  plot_recv2(v28cent,v26cent,v24cent,v22cent,"cent");

  // ------------------------------------------------------------------------





  // ------------------------------------------------------------------------

  cout << "All done. Have a nice day!" << endl;

}

