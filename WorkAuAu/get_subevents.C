#include "calc_subevents.C"
#include "plot_subevents.C"

void get_subevents()
{

  TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");

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
  plot_subevents(hv24, hv24aabb, hv24abab, hv22, hv22ab);

}
