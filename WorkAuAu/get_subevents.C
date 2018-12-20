#include "calc_subevents.C"
#include "plot_subv2.C"
#include "plot_subc2.C"

void get_subevents()
{

  //TFile* fin = TFile::Open("input/cumulants_Run14AuAu200.root");
  TFile* fin = TFile::Open("input/histos_13799.root");

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
  plot_subv2(hv24, hv24aabb, hv24abab, hv22, hv22ab);
  plot_subc2(hc24, hc24aabb, hc24abab);

  // --- now third harmonic

  TProfile* tp1f_h3_for = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c34");
  TProfile* tp1f_h3_4aabb = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c34a");
  TProfile* tp1f_h3_4abab = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c34b");
  TProfile* tp1f_h3_two = (TProfile*)fin->Get("centrality_os_fvtxc_tracks_c32");
  TProfile* tp1f_h3_2aa = (TProfile*)fin->Get("centrality_os_fvtxs_tracks_c32");
  TProfile* tp1f_h3_2bb = (TProfile*)fin->Get("centrality_os_fvtxn_tracks_c32");
  TProfile* tp1f_h3_2ab = (TProfile*)fin->Get("centrality_os_fvtxsfvtxn_tracks_c32");
  TH1D* hv34 = NULL;
  TH1D* hv34aabb = NULL;
  TH1D* hv34abab = NULL;
  TH1D* hv32 = NULL;
  TH1D* hv32ab = NULL;
  TH1D* hc34 = NULL;
  TH1D* hc34aabb = NULL;
  TH1D* hc34abab = NULL;
  TH1D* hc32 = NULL;
  TH1D* hc32ab = NULL;
  calc_subevents(tp1f_h3_for, tp1f_h3_4aabb, tp1f_h3_4abab,
                 tp1f_h3_two, tp1f_h3_2aa, tp1f_h3_2bb, tp1f_h3_2ab,
                 &hv34, &hv34aabb, &hv34abab, &hv32, &hv32ab,
                 &hc34, &hc34aabb, &hc34abab, &hc32, &hc32ab,
                 1);
  //plot_subv2(hv34, hv34aabb, hv34abab, hv32, hv32ab);
  plot_subc2(hc34, hc34aabb, hc34abab, 3);

  ofstream fout("Figure6.dat");
  for ( int i = 0; i < hv22->GetNbinsX(); ++i )
    {
      fout
        << hv22->GetBinCenter(i+1)-0.5 << " "
        << hv22->GetBinContent(i+1) << " "
        << hv22->GetBinError(i+1) << " "
        << 0.06*hv22->GetBinContent(i+1) << "\n";
    }
  fout << endl;
  for ( int i = 0; i < hv22ab->GetNbinsX(); ++i )
    {
      fout
        << hv22ab->GetBinCenter(i+1)-0.5 << " "
        << hv22ab->GetBinContent(i+1) << " "
        << hv22ab->GetBinError(i+1) << " "
        << 0.06*hv22ab->GetBinContent(i+1) << "\n";
    }
  fout << endl;
  for ( int i = 0; i < hv24->GetNbinsX(); ++i )
    {
      fout
        << hv24->GetBinCenter(i+1)-0.5 << " "
        << hv24->GetBinContent(i+1) << " "
        << hv24->GetBinError(i+1) << " "
        << 0.06*hv24->GetBinContent(i+1) << "\n";
    }
  fout << endl;
  for ( int i = 0; i < hv24abab->GetNbinsX(); ++i )
    {
      fout
        << hv24abab->GetBinCenter(i+1)-0.5 << " "
        << hv24abab->GetBinContent(i+1) << " "
        << hv24abab->GetBinError(i+1) << " "
        << 0.06*hv24abab->GetBinContent(i+1) << "\n";
    }
  fout << endl;
  for ( int i = 0; i < hv24aabb->GetNbinsX(); ++i )
    {
      fout
        << hv24aabb->GetBinCenter(i+1)-0.5 << " "
        << hv24aabb->GetBinContent(i+1) << " "
        << hv24aabb->GetBinError(i+1) << " "
        << 0.06*hv24aabb->GetBinContent(i+1) << "\n";
    }
  fout << endl;

}
