#include "calc_cumulants.C"
#include "plot_recv2.C"
#include "plot_recomp.C"
#include "calc_subevents.C"
#include "plot_subv2.C"
#include "plot_special.C"


void do_special()
{

  // --- get the file; soft link to latest stable analysis with default cuts
  //TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");
  TFile* fin = TFile::Open("input/histos_13799.root");
  //TFile* fin = TFile::Open("input/histos_14063.root");
  //TFile* fin = TFile::Open("input/histos_14076.root");

  // --- get the k-p correlator histograms from the file
  TProfile* eit_cent = (TProfile*)fin->Get("centrality_recursion_0_6");
  TProfile* six_cent = (TProfile*)fin->Get("centrality_recursion_0_4");
  TProfile* for_cent = (TProfile*)fin->Get("centrality_recursion_0_2");
  TProfile* two_cent = (TProfile*)fin->Get("centrality_recursion_0_0");

  // --- initialize the pointers
  TH1D* v28 = NULL;
  TH1D* v26 = NULL;
  TH1D* v24 = NULL;
  TH1D* v22 = NULL;

  // --- get all the v2{k}, c2{k}, and component histograms
  calc_cumulants(eit_cent, six_cent, for_cent, two_cent,
                &v28,  &v26,  &v24,  &v22,
                1);
  // --- plot the v2{k}
  //plot_recv2(v28,v26,v24,v22,"cent",2);

  // --- now get the subevent v2{2}

  TProfile* tp1f_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c24");
  TProfile* tp1f_4aabb = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c24a");
  TProfile* tp1f_4abab = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c24b");
  TProfile* tp1f_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c22");
  TProfile* tp1f_2aa = (TProfile*)fin->Get("centrality_os_fvtxs_tracks_c22");
  TProfile* tp1f_2bb = (TProfile*)fin->Get("centrality_os_fvtxn_tracks_c22");
  TProfile* tp1f_2ab = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c22");
  TH1D* hv24 = NULL;
  TH1D* hv24aabb = NULL;
  TH1D* hv24abab = NULL;
  TH1D* hv22 = NULL;
  TH1D* hv22ab = NULL;
  TH1D* hc24 = NULL;
  TH1D* hc24aabb = NULL;
  TH1D* hc24abab = NULL;
  TH1D* hc22 = NULL;
  TH1D* hc22ab = NULL;
  calc_subevents(tp1f_for, tp1f_4aabb, tp1f_4abab,
                 tp1f_two, tp1f_2aa, tp1f_2bb, tp1f_2ab,
                 &hv24, &hv24aabb, &hv24abab, &hv22, &hv22ab,
                 &hc24, &hc24aabb, &hc24abab, &hc22, &hc22ab,
                 1);

  // --- plot the v2{k} with subevent v2 instead...
  plot_recv2(v28,v26,v24,hv22ab,"scent",2);

  // --- now do a special plot with all 5...
  plot_special(v28,v26,v24,v22,hv22ab,"cent");

  ofstream fout("Figure7.dat");
  for ( int i = 0; i < hv22ab->GetNbinsX(); ++i )
    {
      fout
        << hv22ab->GetBinCenter(i+1)-0.5 << " "
        << hv22ab->GetBinContent(i+1) << " "
        << hv22ab->GetBinError(i+1) << " "
        << 0.06*hv22ab->GetBinContent(i+1) << "\n";
    }
  fout << endl;
  for ( int i = 0; i < v24->GetNbinsX(); ++i )
    {
      fout
        << v24->GetBinCenter(i+1)-0.5 << " "
        << v24->GetBinContent(i+1) << " "
        << v24->GetBinError(i+1) << " "
        << 0.06*v24->GetBinContent(i+1) << "\n";
    }
  fout << endl;
  for ( int i = 0; i < v26->GetNbinsX(); ++i )
    {
      fout
        << v26->GetBinCenter(i+1)-0.5 << " "
        << v26->GetBinContent(i+1) << " "
        << v26->GetBinError(i+1) << " "
        << 0.06*v26->GetBinContent(i+1) << "\n";
    }
  fout << endl;
  for ( int i = 0; i < v28->GetNbinsX(); ++i )
    {
      fout
        << v28->GetBinCenter(i+1)-0.5 << " "
        << v28->GetBinContent(i+1) << " "
        << v28->GetBinError(i+1) << " "
        << 0.06*v28->GetBinContent(i+1) << "\n";
    }
  fout << endl;

}
