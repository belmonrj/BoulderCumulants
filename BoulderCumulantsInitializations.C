#include <BoulderCumulants.h>

#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>

#include <Fun4AllReturnCodes.h>
#include <Fun4AllServer.h>
#include <PHCompositeNode.h>
#include <getClass.h>
#include <RunHeader.h>
#include <dAuBES_utils.h>




using namespace std;


// --- Init method, part of Fun4All inheriance
int BoulderCumulants::Init(PHCompositeNode *topNode)
{

  //  ResetEvent(topNode); // is this needed?

  if (_verbosity > 1) cout << PHWHERE << "::Init() - entered." << endl;

  _output_file = new TFile(_output_filename.c_str(), "RECREATE");

  if (_create_ttree)
  {
    shorttree = new TTree("shorttree", "Event-wise TTree");
    shorttree->SetAutoFlush(1000);
    shorttree->SetMaxTreeSize(100000000000LL);
    //shorttree -> Branch("event", &event, "event/F");
    shorttree -> Branch("bbc_z", &bbc_z, "bbc_z/F");
    shorttree -> Branch("centrality", &centrality, "centrality/F");
    //shorttree -> Branch("npc1", &npc1, "npc1/I");
    shorttree -> Branch("nfvtxt", &nfvtxt, "nfvtxt/I");
    shorttree -> Branch("nfvtxt_south", &nfvtxt_south, "nfvtxt_south/I");
    shorttree -> Branch("nfvtxt_north", &nfvtxt_north, "nfvtxt_north/I");
    shorttree -> Branch("nfvtxt_raw", &nfvtxt_raw, "nfvtxt_raw/I");
    shorttree -> Branch("trigger_scaled", &trigger_scaled, "trigger_scaled/i");
    //shorttree -> Branch("trigger_live", &trigger_live, "trigger_live/i");
    // shorttree -> Branch("d_Qx", &d_Qx, "d_Qx[9]/F");
    // shorttree -> Branch("d_Qy", &d_Qy, "d_Qy[9]/F");
    // shorttree -> Branch("d_Qw", &d_Qw, "d_Qw[9]/F");
    shorttree -> Branch("d_SouthQX", &d_SouthQX, "d_SouthQX[9]/F");
    shorttree -> Branch("d_SouthQY", &d_SouthQY, "d_SouthQY[9]/F");
    shorttree -> Branch("d_SouthQW", &d_SouthQW, "d_SouthQW/F");
    shorttree -> Branch("d_NorthQX", &d_NorthQX, "d_NorthQX[9]/F");
    shorttree -> Branch("d_NorthQY", &d_NorthQY, "d_NorthQY[9]/F");
    shorttree -> Branch("d_NorthQW", &d_NorthQW, "d_NorthQW/F");
    // shorttree -> Branch("bc_x", &bc_x, "bc_x/F");
    // shorttree -> Branch("bc_y", &bc_y, "bc_y/F");
    // shorttree -> Branch("vtx_z", &vtx_z, "vtx_z/F");
    // shorttree -> Branch("fvtx_x", &FVTX_X, "fvtx_x/F");
    // shorttree -> Branch("fvtx_y", &FVTX_Y, "fvtx_y/F");
    // shorttree -> Branch("fvtx_z", &FVTX_Z, "fvtx_z/F");
    // shorttree -> Branch("frac", &frac, "frac/F");
    shorttree -> Branch("bbc_qn", &bbc_qn, "bbc_qn/F");
    shorttree -> Branch("bbc_qs", &bbc_qs, "bbc_qs/F");
    // shorttree -> Branch("d_BBC_charge", &d_BBC_charge, "d_BBC_charge[128]/F");
  }

  // ---
  // --- initialize histograms
  // ---

  th1d_nfvtxt_combinedER = new TH1D("th1d_nfvtxt_combinedER","",5000, -0.5, 4999.5);
  th1d_nfvtxt_combined = new TH1D("th1d_nfvtxt_combined","",700, -0.5, 699.5);
  th1d_centrality = new TH1D("th1d_centrality","",100, -0.5, 99.5);
  th1d_centralityA = new TH1D("th1d_centralityA","",100, -0.5, 99.5);
  th2d_nfvtxt_bbcsum = new TH2D("th2d_nfvtxt_bbcsum","",700, -0.5, 699.5, 1000, 0, 4000);
  th2d_nfvtxt_centrality = new TH2D("th2d_nfvtxt_centrality","",700, -0.5, 699.5, 100, -0.5, 99.5);
  th2d_nfvtxt_centralityA = new TH2D("th2d_nfvtxt_centralityA","",700, -0.5, 699.5, 100, -0.5, 99.5);
  th2d_nfvtxt_bbcsumratio = new TH2D("th2d_nfvtxt_bbcsumratio","",700, -0.5, 699.5, 1000, 0, 5);
  th1d_nfvtxt_north = new TH1D("th1d_nfvtxt_north","",700, -0.5, 699.5);
  th1d_nfvtxt_south = new TH1D("th1d_nfvtxt_south","",700, -0.5, 699.5);
  th2d_nfvtxt_northsouth = new TH2D("th2d_nfvtxt_northsouth","",1000, -0.5, 999.5, 1000, -0.5, 999.5);
  th1d_track_deta = new TH1D("th1d_track_deta","",2000, -0.1, 0.1);
  th1d_track_dphi = new TH1D("th1d_track_dphi","",2000, -0.1, 0.1);
  th2d_track_before_eta = new TH2D("th2d_track_before_eta","",100,-0.5,99.5, 700, -3.5, 3.5);
  th2d_track_before_phi = new TH2D("th2d_track_before_phi","",100,-0.5,99.5, 640, -3.2, 3.2);
  th2d_track_after_eta  = new TH2D("th2d_track_after_eta", "",100,-0.5,99.5, 700, -3.5, 3.5);
  th2d_track_after_phi  = new TH2D("th2d_track_after_phi", "",100,-0.5,99.5, 640, -3.2, 3.2);
  th2d_track_aafter_eta = new TH2D("th2d_track_aafter_eta","",100,-0.5,99.5, 700, -3.5, 3.5);
  th2d_track_aafter_phi = new TH2D("th2d_track_aafter_phi","",100,-0.5,99.5, 640, -3.2, 3.2);
  th2d_cent_dcax = new TH2D("th2d_cent_dcax","",100,-0.5,99.5, 600,-3.0,3.0);
  th2d_cent_dcay = new TH2D("th2d_cent_dcay","",100,-0.5,99.5, 600,-3.0,3.0);
  th2d_cent_nhitr = new TH2D("th2d_cent_nhitr","",100,-0.5,99.5, 7,-0.5,6.5);
  th2d_cent_nhits = new TH2D("th2d_cent_nhits","",100,-0.5,99.5, 7,-0.5,6.5);
  th2d_cent_chisq = new TH2D("th2d_cent_chisq","",100,-0.5,99.5, 100,0.0,10.0);
  tp1f_track_detacutpass = new TProfile("tp1f_track_detacutpass","",100,-0.5,99.5,-0.1,1.1);




  // ---------------------------------------------------------------------------------------------------------
  // --- centrality
  // ---------------------------------------------------------------------------------------------------------

  for ( int iharm = 2; iharm < 5; ++iharm )
    {
      // --------------------------------------------------------------------------------------------------------------------------
      // --- without q-vector recentering
      // ---
      // --- cumulant histograms
      // --- combined
      centrality_ac_cumu2[0][iharm] = new TProfile(Form("centrality_ac_fvtxc_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      centrality_ac_cumu4[0][iharm] = new TProfile(Form("centrality_ac_fvtxc_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      if ( iharm < 4 ) centrality_ac_cumu6[0][iharm] = new TProfile(Form("centrality_ac_fvtxc_tracks_c%d%d",iharm,6),"",100, -0.5, 99.5, -1.1, 1.1);
      if ( iharm < 3 ) centrality_ac_cumu8[0][iharm] = new TProfile(Form("centrality_ac_fvtxc_tracks_c%d%d",iharm,8),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- south
      centrality_ac_cumu2[1][iharm] = new TProfile(Form("centrality_ac_fvtxs_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      centrality_ac_cumu4[1][iharm] = new TProfile(Form("centrality_ac_fvtxs_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- north
      centrality_ac_cumu2[2][iharm] = new TProfile(Form("centrality_ac_fvtxn_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      centrality_ac_cumu4[2][iharm] = new TProfile(Form("centrality_ac_fvtxn_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- subevent histograms
      centrality_ac_sub2[iharm] = new TProfile(Form("centrality_ac_fvtxsfvtxn_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      centrality_ac_sub4a[iharm] = new TProfile(Form("centrality_ac_fvtxsfvtxn_tracks_c%d%da",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      centrality_ac_sub4b[iharm] = new TProfile(Form("centrality_ac_fvtxsfvtxn_tracks_c%d%db",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- correction histograms
      // --- combined
      centrality_ac_corr_cos1[0][iharm] = new TProfile(Form("centrality_ac_fvtxc_tracks_cos%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1))>>
      centrality_ac_corr_sin1[0][iharm] = new TProfile(Form("centrality_ac_fvtxc_tracks_sin%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1))>>
      centrality_ac_corr_cos2[0][iharm] = new TProfile(Form("centrality_ac_fvtxc_tracks_cossum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<cos(n(phi1+phi2))>>
      centrality_ac_corr_sin2[0][iharm] = new TProfile(Form("centrality_ac_fvtxc_tracks_sinsum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<sin(n(phi1+phi2))>>
      centrality_ac_corr_cos3[0][iharm] = new TProfile(Form("centrality_ac_fvtxc_tracks_cos%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1-phi2-phi3))>>
      centrality_ac_corr_sin3[0][iharm] = new TProfile(Form("centrality_ac_fvtxc_tracks_sin%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1-phi2-phi3))>>
      // --- south
      centrality_ac_corr_cos1[1][iharm] = new TProfile(Form("centrality_ac_fvtxs_tracks_cos%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1))>>
      centrality_ac_corr_sin1[1][iharm] = new TProfile(Form("centrality_ac_fvtxs_tracks_sin%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1))>>
      centrality_ac_corr_cos2[1][iharm] = new TProfile(Form("centrality_ac_fvtxs_tracks_cossum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<cos(n(phi1+phi2))>>
      centrality_ac_corr_sin2[1][iharm] = new TProfile(Form("centrality_ac_fvtxs_tracks_sinsum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<sin(n(phi1+phi2))>>
      centrality_ac_corr_cos3[1][iharm] = new TProfile(Form("centrality_ac_fvtxs_tracks_cos%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1-phi2-phi3))>>
      centrality_ac_corr_sin3[1][iharm] = new TProfile(Form("centrality_ac_fvtxs_tracks_sin%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1-phi2-phi3))>>
      // --- south
      centrality_ac_corr_cos1[2][iharm] = new TProfile(Form("centrality_ac_fvtxn_tracks_cos%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1))>>
      centrality_ac_corr_sin1[2][iharm] = new TProfile(Form("centrality_ac_fvtxn_tracks_sin%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1))>>
      centrality_ac_corr_cos2[2][iharm] = new TProfile(Form("centrality_ac_fvtxn_tracks_cossum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<cos(n(phi1+phi2))>>
      centrality_ac_corr_sin2[2][iharm] = new TProfile(Form("centrality_ac_fvtxn_tracks_sinsum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<sin(n(phi1+phi2))>>
      centrality_ac_corr_cos3[2][iharm] = new TProfile(Form("centrality_ac_fvtxn_tracks_cos%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1-phi2-phi3))>>
      centrality_ac_corr_sin3[2][iharm] = new TProfile(Form("centrality_ac_fvtxn_tracks_sin%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1-phi2-phi3))>>
      // --------------------------------------------------------------------------------------------------------------------------
      // --- with q-vector recentering
      // ---
      // --- cumulant histograms
      // --- combined
      centrality_os_cumu2[0][iharm] = new TProfile(Form("centrality_os_fvtxc_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      centrality_os_cumu4[0][iharm] = new TProfile(Form("centrality_os_fvtxc_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      if ( iharm < 4 ) centrality_os_cumu6[0][iharm] = new TProfile(Form("centrality_os_fvtxc_tracks_c%d%d",iharm,6),"",100, -0.5, 99.5, -1.1, 1.1);
      if ( iharm < 3 ) centrality_os_cumu8[0][iharm] = new TProfile(Form("centrality_os_fvtxc_tracks_c%d%d",iharm,8),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- south
      centrality_os_cumu2[1][iharm] = new TProfile(Form("centrality_os_fvtxs_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      centrality_os_cumu4[1][iharm] = new TProfile(Form("centrality_os_fvtxs_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- north
      centrality_os_cumu2[2][iharm] = new TProfile(Form("centrality_os_fvtxn_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      centrality_os_cumu4[2][iharm] = new TProfile(Form("centrality_os_fvtxn_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- subevent histograms
      centrality_os_sub2[iharm] = new TProfile(Form("centrality_os_fvtxsfvtxn_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      centrality_os_sub4a[iharm] = new TProfile(Form("centrality_os_fvtxsfvtxn_tracks_c%d%da",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      centrality_os_sub4b[iharm] = new TProfile(Form("centrality_os_fvtxsfvtxn_tracks_c%d%db",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- correction histograms
      // --- combined
      centrality_os_corr_cos1[0][iharm] = new TProfile(Form("centrality_os_fvtxc_tracks_cos%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1))>>
      centrality_os_corr_sin1[0][iharm] = new TProfile(Form("centrality_os_fvtxc_tracks_sin%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1))>>
      centrality_os_corr_cos2[0][iharm] = new TProfile(Form("centrality_os_fvtxc_tracks_cossum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<cos(n(phi1+phi2))>>
      centrality_os_corr_sin2[0][iharm] = new TProfile(Form("centrality_os_fvtxc_tracks_sinsum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<sin(n(phi1+phi2))>>
      centrality_os_corr_cos3[0][iharm] = new TProfile(Form("centrality_os_fvtxc_tracks_cos%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1-phi2-phi3))>>
      centrality_os_corr_sin3[0][iharm] = new TProfile(Form("centrality_os_fvtxc_tracks_sin%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1-phi2-phi3))>>
    }

  // --- nfvtxt

  for ( int iharm = 2; iharm < 5; ++iharm )
    {
      // --------------------------------------------------------------------------------------------------------------------------
      // --- without q-vector recentering
      // ---
      // --- cumulant histograms
      // --- combined
      nfvtxt_ac_cumu2[0][iharm] = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      nfvtxt_ac_cumu4[0][iharm] = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      if ( iharm < 4 ) nfvtxt_ac_cumu6[0][iharm] = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_c%d%d",iharm,6),"",100, -0.5, 99.5, -1.1, 1.1);
      if ( iharm < 3 ) nfvtxt_ac_cumu8[0][iharm] = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_c%d%d",iharm,8),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- south
      nfvtxt_ac_cumu2[1][iharm] = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      nfvtxt_ac_cumu4[1][iharm] = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- north
      nfvtxt_ac_cumu2[2][iharm] = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      nfvtxt_ac_cumu4[2][iharm] = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- subevent histograms
      nfvtxt_ac_sub2[iharm] = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      nfvtxt_ac_sub4a[iharm] = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c%d%da",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      nfvtxt_ac_sub4b[iharm] = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c%d%db",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- correction histograms
      // --- combined
      nfvtxt_ac_corr_cos1[0][iharm] = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_cos%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1))>>
      nfvtxt_ac_corr_sin1[0][iharm] = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_sin%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1))>>
      nfvtxt_ac_corr_cos2[0][iharm] = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_cossum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<cos(n(phi1+phi2))>>
      nfvtxt_ac_corr_sin2[0][iharm] = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_sinsum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<sin(n(phi1+phi2))>>
      nfvtxt_ac_corr_cos3[0][iharm] = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_cos%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1-phi2-phi3))>>
      nfvtxt_ac_corr_sin3[0][iharm] = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_sin%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1-phi2-phi3))>>
      // --- south
      nfvtxt_ac_corr_cos1[1][iharm] = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_cos%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1))>>
      nfvtxt_ac_corr_sin1[1][iharm] = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_sin%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1))>>
      nfvtxt_ac_corr_cos2[1][iharm] = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_cossum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<cos(n(phi1+phi2))>>
      nfvtxt_ac_corr_sin2[1][iharm] = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_sinsum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<sin(n(phi1+phi2))>>
      nfvtxt_ac_corr_cos3[1][iharm] = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_cos%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1-phi2-phi3))>>
      nfvtxt_ac_corr_sin3[1][iharm] = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_sin%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1-phi2-phi3))>>
      // --- south
      nfvtxt_ac_corr_cos1[2][iharm] = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_cos%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1))>>
      nfvtxt_ac_corr_sin1[2][iharm] = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_sin%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1))>>
      nfvtxt_ac_corr_cos2[2][iharm] = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_cossum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<cos(n(phi1+phi2))>>
      nfvtxt_ac_corr_sin2[2][iharm] = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_sinsum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<sin(n(phi1+phi2))>>
      nfvtxt_ac_corr_cos3[2][iharm] = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_cos%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1-phi2-phi3))>>
      nfvtxt_ac_corr_sin3[2][iharm] = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_sin%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1-phi2-phi3))>>
      // --------------------------------------------------------------------------------------------------------------------------
      // --- with q-vector recentering
      // ---
      // --- cumulant histograms
      // --- combined
      nfvtxt_os_cumu2[0][iharm] = new TProfile(Form("nfvtxt_os_fvtxc_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      nfvtxt_os_cumu4[0][iharm] = new TProfile(Form("nfvtxt_os_fvtxc_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      if ( iharm < 4 ) nfvtxt_os_cumu6[0][iharm] = new TProfile(Form("nfvtxt_os_fvtxc_tracks_c%d%d",iharm,6),"",100, -0.5, 99.5, -1.1, 1.1);
      if ( iharm < 3 ) nfvtxt_os_cumu8[0][iharm] = new TProfile(Form("nfvtxt_os_fvtxc_tracks_c%d%d",iharm,8),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- south
      nfvtxt_os_cumu2[1][iharm] = new TProfile(Form("nfvtxt_os_fvtxs_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      nfvtxt_os_cumu4[1][iharm] = new TProfile(Form("nfvtxt_os_fvtxs_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- north
      nfvtxt_os_cumu2[2][iharm] = new TProfile(Form("nfvtxt_os_fvtxn_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      nfvtxt_os_cumu4[2][iharm] = new TProfile(Form("nfvtxt_os_fvtxn_tracks_c%d%d",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- subevent histograms
      nfvtxt_os_sub2[iharm] = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c%d%d",iharm,2),"",100, -0.5, 99.5, -1.1, 1.1);
      nfvtxt_os_sub4a[iharm] = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c%d%da",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      nfvtxt_os_sub4b[iharm] = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c%d%db",iharm,4),"",100, -0.5, 99.5, -1.1, 1.1);
      // --- correction histograms
      // --- combined
      nfvtxt_os_corr_cos1[0][iharm] = new TProfile(Form("nfvtxt_os_fvtxc_tracks_cos%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1))>>
      nfvtxt_os_corr_sin1[0][iharm] = new TProfile(Form("nfvtxt_os_fvtxc_tracks_sin%d1",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1))>>
      nfvtxt_os_corr_cos2[0][iharm] = new TProfile(Form("nfvtxt_os_fvtxc_tracks_cossum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<cos(n(phi1+phi2))>>
      nfvtxt_os_corr_sin2[0][iharm] = new TProfile(Form("nfvtxt_os_fvtxc_tracks_sinsum%d2",iharm),"",100, -0.5, 99.5, -1.1, 1.1);   // --- <<sin(n(phi1+phi2))>>
      nfvtxt_os_corr_cos3[0][iharm] = new TProfile(Form("nfvtxt_os_fvtxc_tracks_cos%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<cos(n(phi1-phi2-phi3))>>
      nfvtxt_os_corr_sin3[0][iharm] = new TProfile(Form("nfvtxt_os_fvtxc_tracks_sin%d3",iharm),"",100, -0.5, 99.5, -1.1, 1.1);      // --- <<sin(n(phi1-phi2-phi3))>>
    }







  // ---------------------------------------------------------------------------------------------------------
  for ( int i = 0; i < 8; ++i ) tp1f_special_fvtx_tracks_ab[i] = new TProfile(Form("tp1f_special_fvtx_tracks_ab%d",i),"",12,-3,3,-1.1,1.1,"");
  tp1f_special_fvtx_tracks_aa = new TProfile("tp1f_special_fvtx_tracks_aa","",12,-3,3,-1.1,1.1,"");
  tp1f_special_fvtx_tracks_aa_cos = new TProfile("tp1f_special_fvtx_tracks_aa_cos","",12,-3,3,-1.1,1.1,"");
  tp1f_special_fvtx_tracks_aa_sin = new TProfile("tp1f_special_fvtx_tracks_aa_sin","",12,-3,3,-1.1,1.1,"");

  // ---
  // ---

  for ( int cs = 0; cs < 2; ++cs )
    {
      for(int c = 0; c < maxCorrelator; ++c )
        {
          nfvtxt_recursion[cs][c] = new TProfile(Form("nfvtxt_recursion_%d_%d",cs,c),"",700,-0.5,699.5,-1.1,1.1);
          centrality_recursion[cs][c] = new TProfile(Form("centrality_recursion_%d_%d",cs,c),"",100,-0.5,99.5,-1.1,1.1);
          centrality_spw_recursion[cs][c] = new TProfile(Form("centrality_spw_recursion_%d_%d",cs,c),"",100,-0.5,99.5,-1.1,1.1);
        }
    }
  for ( int cs = 0; cs < 2; ++cs )
    {
      for ( int c = 0; c < maxHarmonic; ++c )
        {
          eta_recoffsets[cs][c] = new TProfile(Form("eta_recoffsets_%d_%d",cs,c),"",700,-3.5,3.5,-1.1,1.1);
          zvtx_recoffsets[cs][c] = new TProfile(Form("zvtx_recoffsets_%d_%d",cs,c),"",220,-11.0,11.0,-1.1,1.1);
          zvtx_recoffsets_north[cs][c] = new TProfile(Form("zvtx_recoffsets_north_%d_%d",cs,c),"",220,-11.0,11.0,-1.1,1.1);
          zvtx_recoffsets_south[cs][c] = new TProfile(Form("zvtx_recoffsets_south_%d_%d",cs,c),"",220,-11.0,11.0,-1.1,1.1);
          nfvtxt_recoffsets[cs][c] = new TProfile(Form("nfvtxt_recoffsets_%d_%d",cs,c),"",700,-0.5,699.5,-1.1,1.1);
          nfvtxt_recoffsets_north[cs][c] = new TProfile(Form("nfvtxt_recoffsets_north_%d_%d",cs,c),"",700,-0.5,699.5,-1.1,1.1);
          nfvtxt_recoffsets_south[cs][c] = new TProfile(Form("nfvtxt_recoffsets_south_%d_%d",cs,c),"",700,-0.5,699.5,-1.1,1.1);
          centrality_recoffsets[cs][c] = new TProfile(Form("centrality_recoffsets_%d_%d",cs,c),"",100,-0.5,99.5,-1.1,1.1);
          centrality_recoffsets_north[cs][c] = new TProfile(Form("centrality_recoffsets_north_%d_%d",cs,c),"",100,-0.5,99.5,-1.1,1.1);
          centrality_recoffsets_south[cs][c] = new TProfile(Form("centrality_recoffsets_south_%d_%d",cs,c),"",100,-0.5,99.5,-1.1,1.1);
        }
    }

  return EVENT_OK;

}


// --- InitRun, part of Fun4All inheritance
int BoulderCumulants::InitRun(PHCompositeNode *topNode)
{

  cout << "InitRun called " << endl;

  int runnumber = 0;

  RunHeader *rh = findNode::getClass<RunHeader>(topNode, "RunHeader");
  if ( !rh )
  {
    cout << PHWHERE << " ERROR::RunHeader not found" << endl;
    return ABORTEVENT;
  }
  runnumber = rh->get_RunNumber();

  // --- set Q-vector offsets
  cout << "setting Q-vector offsets..." << endl;
  SetQvectorOffsets(runnumber);
  SetQvectorOffsetsRBR(runnumber);



  // Setup the utility class
  // This is done in init run so that the collision system can be
  // determined from the run number
  _collsys = "Run16dAu200"; // default to 200 GeV
  use_utils = true;
  // --- Run14AuAu200
  if ( runnumber >= 405839 && runnumber <= 414988 )
    {
      _collsys = "Run14AuAu200";
      use_utils = false;
    }
  if ( runnumber >= 415370 && runnumber <= 416893 )
    {
      _collsys = "Run14HeAu200";
      use_utils = false;
    }
  // --- Run15pAu200
  if ( runnumber >= 432637 && runnumber <= 436647 )
    _collsys = "Run15pAu200";
  // --- Run15pAl200
  if ( runnumber >= 436759 && runnumber <= 438422 )
    _collsys = "Run15pAl200";
  // --- Run16dAu200
  if ( runnumber >= 454774 && runnumber <= 455639 )
    _collsys = "Run16dAu200";
  // --- Run16dAu62
  if ( runnumber >= 455792 && runnumber <= 456283 )
    _collsys = "Run16dAu62";
  // --- Run16dAu20
  if ( runnumber >= 456652 && runnumber <= 457298 )
    _collsys = "Run16dAu20";
  // --- Run16dAu39
  if ( runnumber >= 457634 && runnumber <= 458167 )
    _collsys = "Run16dAu39";

  // --- delete this pointer in EndRun
  if ( use_utils )
    {
      cout << "initializing uitls..." << _utils << endl;
      _utils = new dAuBES_utils(_collsys, true);
      cout << "done initializing utils? " << _utils << endl;
    }
  // _utils->is_sim(_is_sim);


  return EVENT_OK;
}



int BoulderCumulants::EndRun(PHCompositeNode *topNode)
{
  if ( _utils ) delete _utils;
  return EVENT_OK;
}



int BoulderCumulants::End(PHCompositeNode *topNode)
{
  if (_verbosity > 1) cout << PHWHERE << "::End() - entered." << endl;
  cout << "total events: " << _ievent << " fraction passing vtx cut: " << tmp_evt * 1.0 / _ievent << endl;
  _output_file->Write();
  _output_file->Close();
  delete _output_file;
  return EVENT_OK;
}
