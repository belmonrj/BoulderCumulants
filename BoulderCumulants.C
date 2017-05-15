#include "BoulderCumulants.h"

#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <fstream>



#include "TOAD.h"

#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TComplex.h>

// Fun4All includes...
#include <Fun4AllReturnCodes.h>
#include <Fun4AllServer.h>
#include <PHCompositeNode.h>
#include <PHIODataNode.h>
#include <phool.h>
#include <getClass.h>
#include <PHGlobalv9.h>
#include <EventHeader.h>
#include <TrigLvl1.h>
#include <VtxOut.h>
#include <PHPoint.h>
#include <RunHeader.h>
#include <TFvtxCompactTrkMap.h>
#include <TFvtxCompactCoordMap.h>
#include <PreviousEvent.h>
#include "dAuBES_utils.h"


// ------------------------
#include "PHCentralTrack.h"
#include "PHSnglCentralTrack.h"



using namespace std;


// --- class constructor
BoulderCumulants::BoulderCumulants(): SubsysReco("BOULDERCUMULANTS")
{
  //ResetEvent(NULL);

  _ievent = 0;
  _verbosity = 0;
  _output_filename = "NULL";
  _output_file = NULL;
  _use_runlist = false;
  _runlist_filename = "NULL";
  _utils = NULL;
  _collsys = "NULL";

  use_utils = true;

  tmp_evt = 0;

  _create_ttree = true,

  FVTX_X = -9999.9;
  FVTX_Y = -9999.9;
  FVTX_Z = -9999.9;

  event = -9999;
  bbc_z = -9999.9;
  centrality = -9999;
  icent = 0;
  npc1 = -9999;
  trigger_scaled = -9999;
  trigger_live = -9999;
  bc_x = -9999.9;
  bc_y = -9999.9;
  vtx_z = -9999.9;

  shorttree = NULL;
  bbc_qn = -9999.9;
  bbc_qs = -9999.9;
  nfvtxt = 0;
  nfvtxt_south = 0;
  nfvtxt_north = 0;
  nfvtxt_raw = 0;
  for ( int i = 0; i < 9; ++i )
    {
      d_SouthQX[i] = 0;
      d_SouthQY[i] = 0;
      d_NorthQX[i] = 0;
      d_NorthQY[i] = 0;
    }
  d_SouthQW = 0;
  d_NorthQW = 0;


  th1d_nfvtxt_combinedER = NULL;
  th1d_nfvtxt_combined = NULL;
  th1d_nfvtxt_north = NULL;
  th1d_nfvtxt_south = NULL;
  th2d_nfvtxt_bbcsum = NULL;
  th2d_nfvtxt_bbcsumratio = NULL;
  nfvtxt_ac_fvtxs_tracks_c22 = NULL;
  nfvtxt_ac_fvtxn_tracks_c22 = NULL;
  nfvtxt_ac_fvtxc_tracks_c22 = NULL;
  nfvtxt_ac_fvtxs_tracks_c24 = NULL;
  nfvtxt_ac_fvtxn_tracks_c24 = NULL;
  nfvtxt_ac_fvtxc_tracks_c24 = NULL;
  nfvtxt_ac_fvtxs_tracks_c26 = NULL;
  nfvtxt_ac_fvtxn_tracks_c26 = NULL;
  nfvtxt_ac_fvtxc_tracks_c26 = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c22  = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c24  = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c24a = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c24b = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c24c = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c24d = NULL;
  nfvtxt_ac_fvtxs_tracks_cos21 = NULL;
  nfvtxt_ac_fvtxn_tracks_cos21 = NULL;
  nfvtxt_ac_fvtxc_tracks_cos21 = NULL;
  nfvtxt_ac_fvtxs_tracks_sin21 = NULL;
  nfvtxt_ac_fvtxn_tracks_sin21 = NULL;
  nfvtxt_ac_fvtxc_tracks_sin21 = NULL;
  nfvtxt_ac_fvtxs_tracks_cossum22 = NULL;
  nfvtxt_ac_fvtxn_tracks_cossum22 = NULL;
  nfvtxt_ac_fvtxc_tracks_cossum22 = NULL;
  nfvtxt_ac_fvtxs_tracks_sinsum22 = NULL;
  nfvtxt_ac_fvtxn_tracks_sinsum22 = NULL;
  nfvtxt_ac_fvtxc_tracks_sinsum22 = NULL;
  nfvtxt_ac_fvtxs_tracks_cos23 = NULL;
  nfvtxt_ac_fvtxn_tracks_cos23 = NULL;
  nfvtxt_ac_fvtxc_tracks_cos23 = NULL;
  nfvtxt_ac_fvtxs_tracks_sin23 = NULL;
  nfvtxt_ac_fvtxn_tracks_sin23 = NULL;
  nfvtxt_ac_fvtxc_tracks_sin23 = NULL;
  // --- now third harmonic
  nfvtxt_ac_fvtxs_tracks_c32 = NULL;
  nfvtxt_ac_fvtxn_tracks_c32 = NULL;
  nfvtxt_ac_fvtxc_tracks_c32 = NULL;
  nfvtxt_ac_fvtxs_tracks_c34 = NULL;
  nfvtxt_ac_fvtxn_tracks_c34 = NULL;
  nfvtxt_ac_fvtxc_tracks_c34 = NULL;
  nfvtxt_ac_fvtxs_tracks_c36 = NULL;
  nfvtxt_ac_fvtxn_tracks_c36 = NULL;
  nfvtxt_ac_fvtxc_tracks_c36 = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c32  = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c34  = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c34a = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c34b = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c34c = NULL;
  nfvtxt_ac_fvtxsfvtxn_tracks_c34d = NULL;
  nfvtxt_ac_fvtxs_tracks_cos31 = NULL;
  nfvtxt_ac_fvtxn_tracks_cos31 = NULL;
  nfvtxt_ac_fvtxc_tracks_cos31 = NULL;
  nfvtxt_ac_fvtxs_tracks_sin31 = NULL;
  nfvtxt_ac_fvtxn_tracks_sin31 = NULL;
  nfvtxt_ac_fvtxc_tracks_sin31 = NULL;
  nfvtxt_ac_fvtxs_tracks_cossum32 = NULL;
  nfvtxt_ac_fvtxn_tracks_cossum32 = NULL;
  nfvtxt_ac_fvtxc_tracks_cossum32 = NULL;
  nfvtxt_ac_fvtxs_tracks_sinsum32 = NULL;
  nfvtxt_ac_fvtxn_tracks_sinsum32 = NULL;
  nfvtxt_ac_fvtxc_tracks_sinsum32 = NULL;
  nfvtxt_ac_fvtxs_tracks_cos33 = NULL;
  nfvtxt_ac_fvtxn_tracks_cos33 = NULL;
  nfvtxt_ac_fvtxc_tracks_cos33 = NULL;
  nfvtxt_ac_fvtxs_tracks_sin33 = NULL;
  nfvtxt_ac_fvtxn_tracks_sin33 = NULL;
  nfvtxt_ac_fvtxc_tracks_sin33 = NULL;
  // --- end third harmonic
  centrality_ac_fvtxs_tracks_c22 = NULL;
  centrality_ac_fvtxn_tracks_c22 = NULL;
  centrality_ac_fvtxc_tracks_c22 = NULL;
  centrality_ac_fvtxs_tracks_c24 = NULL;
  centrality_ac_fvtxn_tracks_c24 = NULL;
  centrality_ac_fvtxc_tracks_c24 = NULL;
  centrality_ac_fvtxs_tracks_c26 = NULL;
  centrality_ac_fvtxn_tracks_c26 = NULL;
  centrality_ac_fvtxc_tracks_c26 = NULL;
  centrality_ac_fvtxsfvtxn_tracks_c22  = NULL;
  centrality_ac_fvtxsfvtxn_tracks_c24  = NULL;
  centrality_ac_fvtxsfvtxn_tracks_c24a = NULL;
  centrality_ac_fvtxsfvtxn_tracks_c24b = NULL;
  centrality_ac_fvtxsfvtxn_tracks_c24c = NULL;
  centrality_ac_fvtxsfvtxn_tracks_c24d = NULL;
  centrality_ac_fvtxs_tracks_cos21 = NULL;
  centrality_ac_fvtxn_tracks_cos21 = NULL;
  centrality_ac_fvtxc_tracks_cos21 = NULL;
  centrality_ac_fvtxs_tracks_sin21 = NULL;
  centrality_ac_fvtxn_tracks_sin21 = NULL;
  centrality_ac_fvtxc_tracks_sin21 = NULL;
  centrality_ac_fvtxs_tracks_cossum22 = NULL;
  centrality_ac_fvtxn_tracks_cossum22 = NULL;
  centrality_ac_fvtxc_tracks_cossum22 = NULL;
  centrality_ac_fvtxs_tracks_sinsum22 = NULL;
  centrality_ac_fvtxn_tracks_sinsum22 = NULL;
  centrality_ac_fvtxc_tracks_sinsum22 = NULL;
  centrality_ac_fvtxs_tracks_cos23 = NULL;
  centrality_ac_fvtxn_tracks_cos23 = NULL;
  centrality_ac_fvtxc_tracks_cos23 = NULL;
  centrality_ac_fvtxs_tracks_sin23 = NULL;
  centrality_ac_fvtxn_tracks_sin23 = NULL;
  centrality_ac_fvtxc_tracks_sin23 = NULL;
  centrality_ac_fvtxs_tracks_c32 = NULL;
  centrality_ac_fvtxn_tracks_c32 = NULL;
  centrality_ac_fvtxc_tracks_c32 = NULL;
  centrality_ac_fvtxsfvtxn_tracks_c32  = NULL;
  centrality_ac_fvtxs_tracks_cos31 = NULL;
  centrality_ac_fvtxn_tracks_cos31 = NULL;
  centrality_ac_fvtxc_tracks_cos31 = NULL;
  centrality_ac_fvtxs_tracks_sin31 = NULL;
  centrality_ac_fvtxn_tracks_sin31 = NULL;
  centrality_ac_fvtxc_tracks_sin31 = NULL;
  // ---
  nfvtxt_os_fvtxs_tracks_c22 = NULL;
  nfvtxt_os_fvtxn_tracks_c22 = NULL;
  nfvtxt_os_fvtxc_tracks_c22 = NULL;
  nfvtxt_os_fvtxs_tracks_c24 = NULL;
  nfvtxt_os_fvtxn_tracks_c24 = NULL;
  nfvtxt_os_fvtxc_tracks_c24 = NULL;
  nfvtxt_os_fvtxs_tracks_c26 = NULL;
  nfvtxt_os_fvtxn_tracks_c26 = NULL;
  nfvtxt_os_fvtxc_tracks_c26 = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c22  = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c24  = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c24a = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c24b = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c24c = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c24d = NULL;
  nfvtxt_os_fvtxs_tracks_cos21 = NULL;
  nfvtxt_os_fvtxn_tracks_cos21 = NULL;
  nfvtxt_os_fvtxc_tracks_cos21 = NULL;
  nfvtxt_os_fvtxs_tracks_sin21 = NULL;
  nfvtxt_os_fvtxn_tracks_sin21 = NULL;
  nfvtxt_os_fvtxc_tracks_sin21 = NULL;
  nfvtxt_os_fvtxs_tracks_cossum22 = NULL;
  nfvtxt_os_fvtxn_tracks_cossum22 = NULL;
  nfvtxt_os_fvtxc_tracks_cossum22 = NULL;
  nfvtxt_os_fvtxs_tracks_sinsum22 = NULL;
  nfvtxt_os_fvtxn_tracks_sinsum22 = NULL;
  nfvtxt_os_fvtxc_tracks_sinsum22 = NULL;
  nfvtxt_os_fvtxs_tracks_cos23 = NULL;
  nfvtxt_os_fvtxn_tracks_cos23 = NULL;
  nfvtxt_os_fvtxc_tracks_cos23 = NULL;
  nfvtxt_os_fvtxs_tracks_sin23 = NULL;
  nfvtxt_os_fvtxn_tracks_sin23 = NULL;
  nfvtxt_os_fvtxc_tracks_sin23 = NULL;
  // --- now third harmonic
  nfvtxt_os_fvtxs_tracks_c32 = NULL;
  nfvtxt_os_fvtxn_tracks_c32 = NULL;
  nfvtxt_os_fvtxc_tracks_c32 = NULL;
  nfvtxt_os_fvtxs_tracks_c34 = NULL;
  nfvtxt_os_fvtxn_tracks_c34 = NULL;
  nfvtxt_os_fvtxc_tracks_c34 = NULL;
  nfvtxt_os_fvtxs_tracks_c36 = NULL;
  nfvtxt_os_fvtxn_tracks_c36 = NULL;
  nfvtxt_os_fvtxc_tracks_c36 = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c32  = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c34  = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c34a = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c34b = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c34c = NULL;
  nfvtxt_os_fvtxsfvtxn_tracks_c34d = NULL;
  nfvtxt_os_fvtxs_tracks_cos31 = NULL;
  nfvtxt_os_fvtxn_tracks_cos31 = NULL;
  nfvtxt_os_fvtxc_tracks_cos31 = NULL;
  nfvtxt_os_fvtxs_tracks_sin31 = NULL;
  nfvtxt_os_fvtxn_tracks_sin31 = NULL;
  nfvtxt_os_fvtxc_tracks_sin31 = NULL;
  nfvtxt_os_fvtxs_tracks_cossum32 = NULL;
  nfvtxt_os_fvtxn_tracks_cossum32 = NULL;
  nfvtxt_os_fvtxc_tracks_cossum32 = NULL;
  nfvtxt_os_fvtxs_tracks_sinsum32 = NULL;
  nfvtxt_os_fvtxn_tracks_sinsum32 = NULL;
  nfvtxt_os_fvtxc_tracks_sinsum32 = NULL;
  nfvtxt_os_fvtxs_tracks_cos33 = NULL;
  nfvtxt_os_fvtxn_tracks_cos33 = NULL;
  nfvtxt_os_fvtxc_tracks_cos33 = NULL;
  nfvtxt_os_fvtxs_tracks_sin33 = NULL;
  nfvtxt_os_fvtxn_tracks_sin33 = NULL;
  nfvtxt_os_fvtxc_tracks_sin33 = NULL;
  // --- end third harmonic
  centrality_os_fvtxs_tracks_c22 = NULL;
  centrality_os_fvtxn_tracks_c22 = NULL;
  centrality_os_fvtxc_tracks_c22 = NULL;
  centrality_os_fvtxs_tracks_c24 = NULL;
  centrality_os_fvtxn_tracks_c24 = NULL;
  centrality_os_fvtxc_tracks_c24 = NULL;
  centrality_os_fvtxs_tracks_c26 = NULL;
  centrality_os_fvtxn_tracks_c26 = NULL;
  centrality_os_fvtxc_tracks_c26 = NULL;
  centrality_os_fvtxsfvtxn_tracks_c22  = NULL;
  centrality_os_fvtxsfvtxn_tracks_c24  = NULL;
  centrality_os_fvtxsfvtxn_tracks_c24a = NULL;
  centrality_os_fvtxsfvtxn_tracks_c24b = NULL;
  centrality_os_fvtxsfvtxn_tracks_c24c = NULL;
  centrality_os_fvtxsfvtxn_tracks_c24d = NULL;
  centrality_os_fvtxs_tracks_cos21 = NULL;
  centrality_os_fvtxn_tracks_cos21 = NULL;
  centrality_os_fvtxc_tracks_cos21 = NULL;
  centrality_os_fvtxs_tracks_sin21 = NULL;
  centrality_os_fvtxn_tracks_sin21 = NULL;
  centrality_os_fvtxc_tracks_sin21 = NULL;
  centrality_os_fvtxs_tracks_cossum22 = NULL;
  centrality_os_fvtxn_tracks_cossum22 = NULL;
  centrality_os_fvtxc_tracks_cossum22 = NULL;
  centrality_os_fvtxs_tracks_sinsum22 = NULL;
  centrality_os_fvtxn_tracks_sinsum22 = NULL;
  centrality_os_fvtxc_tracks_sinsum22 = NULL;
  centrality_os_fvtxs_tracks_cos23 = NULL;
  centrality_os_fvtxn_tracks_cos23 = NULL;
  centrality_os_fvtxc_tracks_cos23 = NULL;
  centrality_os_fvtxs_tracks_sin23 = NULL;
  centrality_os_fvtxn_tracks_sin23 = NULL;
  centrality_os_fvtxc_tracks_sin23 = NULL;
  centrality_os_fvtxs_tracks_c32 = NULL;
  centrality_os_fvtxn_tracks_c32 = NULL;
  centrality_os_fvtxc_tracks_c32 = NULL;
  centrality_os_fvtxsfvtxn_tracks_c32  = NULL;
  centrality_os_fvtxs_tracks_cos31 = NULL;
  centrality_os_fvtxn_tracks_cos31 = NULL;
  centrality_os_fvtxc_tracks_cos31 = NULL;
  centrality_os_fvtxs_tracks_sin31 = NULL;
  centrality_os_fvtxn_tracks_sin31 = NULL;
  centrality_os_fvtxc_tracks_sin31 = NULL;

  for ( int i = 0; i < 8; ++i ) tp1f_special_fvtx_tracks_ab[i] = NULL;
  tp1f_special_fvtx_tracks_aa = NULL;
  tp1f_special_fvtx_tracks_aa_cos = NULL;
  tp1f_special_fvtx_tracks_aa_sin = NULL;
  nfvtxt_tracks_south_qx2 = NULL;
  nfvtxt_tracks_south_qx3 = NULL;
  nfvtxt_tracks_south_qx4 = NULL;
  nfvtxt_tracks_south_qx6 = NULL;
  nfvtxt_tracks_south_qy2 = NULL;
  nfvtxt_tracks_south_qy3 = NULL;
  nfvtxt_tracks_south_qy4 = NULL;
  nfvtxt_tracks_south_qy6 = NULL;
  nfvtxt_tracks_south_inner_qx2 = NULL;
  nfvtxt_tracks_south_inner_qx3 = NULL;
  nfvtxt_tracks_south_inner_qx4 = NULL;
  nfvtxt_tracks_south_inner_qx6 = NULL;
  nfvtxt_tracks_south_inner_qy2 = NULL;
  nfvtxt_tracks_south_inner_qy3 = NULL;
  nfvtxt_tracks_south_inner_qy4 = NULL;
  nfvtxt_tracks_south_inner_qy6 = NULL;
  nfvtxt_tracks_south_outer_qx2 = NULL;
  nfvtxt_tracks_south_outer_qx3 = NULL;
  nfvtxt_tracks_south_outer_qx4 = NULL;
  nfvtxt_tracks_south_outer_qx6 = NULL;
  nfvtxt_tracks_south_outer_qy2 = NULL;
  nfvtxt_tracks_south_outer_qy3 = NULL;
  nfvtxt_tracks_south_outer_qy4 = NULL;
  nfvtxt_tracks_south_outer_qy6 = NULL;
  nfvtxt_tracks_north_qx2 = NULL;
  nfvtxt_tracks_north_qx3 = NULL;
  nfvtxt_tracks_north_qx4 = NULL;
  nfvtxt_tracks_north_qx6 = NULL;
  nfvtxt_tracks_north_qy2 = NULL;
  nfvtxt_tracks_north_qy3 = NULL;
  nfvtxt_tracks_north_qy4 = NULL;
  nfvtxt_tracks_north_qy6 = NULL;
  nfvtxt_tracks_north_inner_qx2 = NULL;
  nfvtxt_tracks_north_inner_qx3 = NULL;
  nfvtxt_tracks_north_inner_qx4 = NULL;
  nfvtxt_tracks_north_inner_qx6 = NULL;
  nfvtxt_tracks_north_inner_qy2 = NULL;
  nfvtxt_tracks_north_inner_qy3 = NULL;
  nfvtxt_tracks_north_inner_qy4 = NULL;
  nfvtxt_tracks_north_inner_qy6 = NULL;
  nfvtxt_tracks_north_outer_qx2 = NULL;
  nfvtxt_tracks_north_outer_qx3 = NULL;
  nfvtxt_tracks_north_outer_qx4 = NULL;
  nfvtxt_tracks_north_outer_qx6 = NULL;
  nfvtxt_tracks_north_outer_qy2 = NULL;
  nfvtxt_tracks_north_outer_qy3 = NULL;
  nfvtxt_tracks_north_outer_qy4 = NULL;
  nfvtxt_tracks_north_outer_qy6 = NULL;
  centrality_tracks_south_qx2 = NULL;
  centrality_tracks_south_qx3 = NULL;
  centrality_tracks_south_qx4 = NULL;
  centrality_tracks_south_qx6 = NULL;
  centrality_tracks_south_qy2 = NULL;
  centrality_tracks_south_qy3 = NULL;
  centrality_tracks_south_qy4 = NULL;
  centrality_tracks_south_qy6 = NULL;
  centrality_tracks_south_inner_qx2 = NULL;
  centrality_tracks_south_inner_qx3 = NULL;
  centrality_tracks_south_inner_qx4 = NULL;
  centrality_tracks_south_inner_qx6 = NULL;
  centrality_tracks_south_inner_qy2 = NULL;
  centrality_tracks_south_inner_qy3 = NULL;
  centrality_tracks_south_inner_qy4 = NULL;
  centrality_tracks_south_inner_qy6 = NULL;
  centrality_tracks_south_outer_qx2 = NULL;
  centrality_tracks_south_outer_qx3 = NULL;
  centrality_tracks_south_outer_qx4 = NULL;
  centrality_tracks_south_outer_qx6 = NULL;
  centrality_tracks_south_outer_qy2 = NULL;
  centrality_tracks_south_outer_qy3 = NULL;
  centrality_tracks_south_outer_qy4 = NULL;
  centrality_tracks_south_outer_qy6 = NULL;
  centrality_tracks_north_qx2 = NULL;
  centrality_tracks_north_qx3 = NULL;
  centrality_tracks_north_qx4 = NULL;
  centrality_tracks_north_qx6 = NULL;
  centrality_tracks_north_qy2 = NULL;
  centrality_tracks_north_qy3 = NULL;
  centrality_tracks_north_qy4 = NULL;
  centrality_tracks_north_qy6 = NULL;
  centrality_tracks_north_inner_qx2 = NULL;
  centrality_tracks_north_inner_qx3 = NULL;
  centrality_tracks_north_inner_qx4 = NULL;
  centrality_tracks_north_inner_qx6 = NULL;
  centrality_tracks_north_inner_qy2 = NULL;
  centrality_tracks_north_inner_qy3 = NULL;
  centrality_tracks_north_inner_qy4 = NULL;
  centrality_tracks_north_inner_qy6 = NULL;
  centrality_tracks_north_outer_qx2 = NULL;
  centrality_tracks_north_outer_qx3 = NULL;
  centrality_tracks_north_outer_qx4 = NULL;
  centrality_tracks_north_outer_qx6 = NULL;
  centrality_tracks_north_outer_qy2 = NULL;
  centrality_tracks_north_outer_qy3 = NULL;
  centrality_tracks_north_outer_qy4 = NULL;
  centrality_tracks_north_outer_qy6 = NULL;

  for ( int i = 0; i < 100; ++i )
    {
      offset_centrality_qx2_south[i] = 0;
      offset_centrality_qx4_south[i] = 0;
      offset_centrality_qx6_south[i] = 0;
      offset_centrality_qy2_south[i] = 0;
      offset_centrality_qy4_south[i] = 0;
      offset_centrality_qy6_south[i] = 0;
      offset_centrality_qx2_north[i] = 0;
      offset_centrality_qx4_north[i] = 0;
      offset_centrality_qx6_north[i] = 0;
      offset_centrality_qy2_north[i] = 0;
      offset_centrality_qy4_north[i] = 0;
      offset_centrality_qy6_north[i] = 0;
    }

}


// --- class destructor
BoulderCumulants::~BoulderCumulants()
{
  //if ( _utils ) delete _utils;
}


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
    shorttree -> Branch("event", &event, "event/F");
    shorttree -> Branch("bbc_z", &bbc_z, "bbc_z/F");
    shorttree -> Branch("centrality", &centrality, "centrality/F");
    shorttree -> Branch("npc1", &npc1, "npc1/I");
    shorttree -> Branch("nfvtxt", &nfvtxt, "nfvtxt/I");
    shorttree -> Branch("nfvtxt_south", &nfvtxt_south, "nfvtxt_south/I");
    shorttree -> Branch("nfvtxt_north", &nfvtxt_north, "nfvtxt_north/I");
    shorttree -> Branch("nfvtxt_raw", &nfvtxt_raw, "nfvtxt_raw/I");
    shorttree -> Branch("trigger_scaled", &trigger_scaled, "trigger_scaled/i");
    shorttree -> Branch("trigger_live", &trigger_live, "trigger_live/i");
    // shorttree -> Branch("d_Qx", &d_Qx, "d_Qx[9]/F");
    // shorttree -> Branch("d_Qy", &d_Qy, "d_Qy[9]/F");
    // shorttree -> Branch("d_Qw", &d_Qw, "d_Qw[9]/F");
    shorttree -> Branch("d_SouthQX", &d_SouthQX, "d_SouthQX[9]/F");
    shorttree -> Branch("d_SouthQY", &d_SouthQY, "d_SouthQY[9]/F");
    shorttree -> Branch("d_SouthQW", &d_SouthQW, "d_SouthQW/F");
    shorttree -> Branch("d_NorthQX", &d_NorthQX, "d_NorthQX[9]/F");
    shorttree -> Branch("d_NorthQY", &d_NorthQY, "d_NorthQY[9]/F");
    shorttree -> Branch("d_NorthQW", &d_NorthQW, "d_NorthQW/F");
    shorttree -> Branch("bc_x", &bc_x, "bc_x/F");
    shorttree -> Branch("bc_y", &bc_y, "bc_y/F");
    shorttree -> Branch("vtx_z", &vtx_z, "vtx_z/F");
    shorttree -> Branch("fvtx_x", &FVTX_X, "fvtx_x/F");
    shorttree -> Branch("fvtx_y", &FVTX_Y, "fvtx_y/F");
    shorttree -> Branch("fvtx_z", &FVTX_Z, "fvtx_z/F");
    // shorttree -> Branch("frac", &frac, "frac/F");
    shorttree -> Branch("bbc_qn", &bbc_qn, "bbc_qn/F");
    shorttree -> Branch("bbc_qs", &bbc_qs, "bbc_qs/F");
    // shorttree -> Branch("d_BBC_charge", &d_BBC_charge, "d_BBC_charge[128]/F");
  }

  // ---
  // --- initialize histograms
  // ---

  th1d_nfvtxt_combinedER = new TH1D("th1d_nfvtxt_combinedER","",5000, -0.5, 4999.5);
  th1d_nfvtxt_combined = new TH1D("th1d_nfvtxt_combined","",2000, -0.5, 1999.5);
  th2d_nfvtxt_bbcsum = new TH2D("th2d_nfvtxt_bbcsum","",2000, -0.5, 1999.5, 1000, 0, 4000);
  th2d_nfvtxt_bbcsumratio = new TH2D("th2d_nfvtxt_bbcsumratio","",2000, -0.5, 1999.5, 1000, 0, 5);
  th1d_nfvtxt_north = new TH1D("th1d_nfvtxt_north","",2000, -0.5, 1999.5);
  th1d_nfvtxt_south = new TH1D("th1d_nfvtxt_south","",2000, -0.5, 1999.5);

  nfvtxt_ac_fvtxs_tracks_c22 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_c22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_c22 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_c22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_c22 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_c22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxs_tracks_c24 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_c24"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_c24 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_c24"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_c24 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_c24"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxs_tracks_c26 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_c26"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_c26 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_c26"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_c26 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_c26"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c22  = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c24  = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c24"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c24a = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c24a"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c24b = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c24b"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c24c = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c24c"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c24d = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c24d"),"",2000, -0.5, 1999.5, -1.1, 1.1);

  // --- correction histograms

  // --- <<cos(n(phi1))>>
  nfvtxt_ac_fvtxs_tracks_cos21 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_cos21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_cos21 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_cos21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_cos21 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_cos21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1))>>
  nfvtxt_ac_fvtxs_tracks_sin21 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_sin21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_sin21 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_sin21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_sin21 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_sin21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<cos(n(phi1+phi2))>>
  nfvtxt_ac_fvtxs_tracks_cossum22 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_cossum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_cossum22 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_cossum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_cossum22 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_cossum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1+phi2))>>
  nfvtxt_ac_fvtxs_tracks_sinsum22 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_sinsum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_sinsum22 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_sinsum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_sinsum22 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_sinsum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<cos(n(phi1-phi2-phi3))>>
  nfvtxt_ac_fvtxs_tracks_cos23 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_cos23"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_cos23 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_cos23"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_cos23 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_cos23"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1-phi2-phi3))>>
  nfvtxt_ac_fvtxs_tracks_sin23 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_sin23"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_sin23 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_sin23"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_sin23 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_sin23"),"",2000, -0.5, 1999.5, -1.1, 1.1);

  // ---------------------------------------------------------------------------------------------------------

  nfvtxt_ac_fvtxs_tracks_c32 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_c32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_c32 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_c32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_c32 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_c32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxs_tracks_c34 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_c34"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_c34 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_c34"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_c34 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_c34"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxs_tracks_c36 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_c36"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_c36 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_c36"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_c36 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_c36"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c32  = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c34  = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c34"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c34a = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c34a"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c34b = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c34b"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c34c = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c34c"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxsfvtxn_tracks_c34d = new TProfile(Form("nfvtxt_ac_fvtxsfvtxn_tracks_c34d"),"",2000, -0.5, 1999.5, -1.1, 1.1);

  // --- correction histograms

  // --- <<cos(n(phi1))>>
  nfvtxt_ac_fvtxs_tracks_cos31 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_cos31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_cos31 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_cos31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_cos31 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_cos31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1))>>
  nfvtxt_ac_fvtxs_tracks_sin31 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_sin31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_sin31 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_sin31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_sin31 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_sin31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<cos(n(phi1+phi2))>>
  nfvtxt_ac_fvtxs_tracks_cossum32 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_cossum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_cossum32 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_cossum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_cossum32 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_cossum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1+phi2))>>
  nfvtxt_ac_fvtxs_tracks_sinsum32 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_sinsum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_sinsum32 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_sinsum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_sinsum32 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_sinsum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<cos(n(phi1-phi2-phi3))>>
  nfvtxt_ac_fvtxs_tracks_cos33 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_cos33"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_cos33 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_cos33"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_cos33 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_cos33"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1-phi2-phi3))>>
  nfvtxt_ac_fvtxs_tracks_sin33 = new TProfile(Form("nfvtxt_ac_fvtxs_tracks_sin33"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxn_tracks_sin33 = new TProfile(Form("nfvtxt_ac_fvtxn_tracks_sin33"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_ac_fvtxc_tracks_sin33 = new TProfile(Form("nfvtxt_ac_fvtxc_tracks_sin33"),"",2000, -0.5, 1999.5, -1.1, 1.1);


  // ---------------------------------------------------------------------------------------------------------
  // --- centrality
  // ---------------------------------------------------------------------------------------------------------

  centrality_ac_fvtxs_tracks_c22 = new TProfile(Form("centrality_ac_fvtxs_tracks_c22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_c22 = new TProfile(Form("centrality_ac_fvtxn_tracks_c22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_c22 = new TProfile(Form("centrality_ac_fvtxc_tracks_c22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxs_tracks_c24 = new TProfile(Form("centrality_ac_fvtxs_tracks_c24"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_c24 = new TProfile(Form("centrality_ac_fvtxn_tracks_c24"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_c24 = new TProfile(Form("centrality_ac_fvtxc_tracks_c24"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxs_tracks_c26 = new TProfile(Form("centrality_ac_fvtxs_tracks_c26"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_c26 = new TProfile(Form("centrality_ac_fvtxn_tracks_c26"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_c26 = new TProfile(Form("centrality_ac_fvtxc_tracks_c26"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxsfvtxn_tracks_c22  = new TProfile(Form("centrality_ac_fvtxsfvtxn_tracks_c22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxsfvtxn_tracks_c24  = new TProfile(Form("centrality_ac_fvtxsfvtxn_tracks_c24"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxsfvtxn_tracks_c24a = new TProfile(Form("centrality_ac_fvtxsfvtxn_tracks_c24a"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxsfvtxn_tracks_c24b = new TProfile(Form("centrality_ac_fvtxsfvtxn_tracks_c24b"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxsfvtxn_tracks_c24c = new TProfile(Form("centrality_ac_fvtxsfvtxn_tracks_c24c"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxsfvtxn_tracks_c24d = new TProfile(Form("centrality_ac_fvtxsfvtxn_tracks_c24d"),"",100, -0.5, 99.5, -1.1, 1.1);

  // --- correction histograms

  // --- <<cos(n(phi1))>>
  centrality_ac_fvtxs_tracks_cos21 = new TProfile(Form("centrality_ac_fvtxs_tracks_cos21"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_cos21 = new TProfile(Form("centrality_ac_fvtxn_tracks_cos21"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_cos21 = new TProfile(Form("centrality_ac_fvtxc_tracks_cos21"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<sin(n(phi1))>>
  centrality_ac_fvtxs_tracks_sin21 = new TProfile(Form("centrality_ac_fvtxs_tracks_sin21"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_sin21 = new TProfile(Form("centrality_ac_fvtxn_tracks_sin21"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_sin21 = new TProfile(Form("centrality_ac_fvtxc_tracks_sin21"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<cos(n(phi1+phi2))>>
  centrality_ac_fvtxs_tracks_cossum22 = new TProfile(Form("centrality_ac_fvtxs_tracks_cossum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_cossum22 = new TProfile(Form("centrality_ac_fvtxn_tracks_cossum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_cossum22 = new TProfile(Form("centrality_ac_fvtxc_tracks_cossum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<sin(n(phi1+phi2))>>
  centrality_ac_fvtxs_tracks_sinsum22 = new TProfile(Form("centrality_ac_fvtxs_tracks_sinsum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_sinsum22 = new TProfile(Form("centrality_ac_fvtxn_tracks_sinsum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_sinsum22 = new TProfile(Form("centrality_ac_fvtxc_tracks_sinsum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<cos(n(phi1-phi2-phi3))>>
  centrality_ac_fvtxs_tracks_cos23 = new TProfile(Form("centrality_ac_fvtxs_tracks_cos23"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_cos23 = new TProfile(Form("centrality_ac_fvtxn_tracks_cos23"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_cos23 = new TProfile(Form("centrality_ac_fvtxc_tracks_cos23"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<sin(n(phi1-phi2-phi3))>>
  centrality_ac_fvtxs_tracks_sin23 = new TProfile(Form("centrality_ac_fvtxs_tracks_sin23"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_sin23 = new TProfile(Form("centrality_ac_fvtxn_tracks_sin23"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_sin23 = new TProfile(Form("centrality_ac_fvtxc_tracks_sin23"),"",100, -0.5, 99.5, -1.1, 1.1);

  // ---------------------------------------------------------------------------------------------------------
  centrality_ac_fvtxs_tracks_c32 = new TProfile(Form("centrality_ac_fvtxs_tracks_c32"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_c32 = new TProfile(Form("centrality_ac_fvtxn_tracks_c32"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_c32 = new TProfile(Form("centrality_ac_fvtxc_tracks_c32"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxsfvtxn_tracks_c32  = new TProfile(Form("centrality_ac_fvtxsfvtxn_tracks_c32"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<cos(n(phi1))>>
  centrality_ac_fvtxs_tracks_cos31 = new TProfile(Form("centrality_ac_fvtxs_tracks_cos31"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_cos31 = new TProfile(Form("centrality_ac_fvtxn_tracks_cos31"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_cos31 = new TProfile(Form("centrality_ac_fvtxc_tracks_cos31"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<sin(n(phi1))>>
  centrality_ac_fvtxs_tracks_sin31 = new TProfile(Form("centrality_ac_fvtxs_tracks_sin31"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxn_tracks_sin31 = new TProfile(Form("centrality_ac_fvtxn_tracks_sin31"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_ac_fvtxc_tracks_sin31 = new TProfile(Form("centrality_ac_fvtxc_tracks_sin31"),"",100, -0.5, 99.5, -1.1, 1.1);

  // -----------------------------------------------------------------------------------------------------------
  // --- now offsets
  // -----------------------------------------------------------------------------------------------------------

  nfvtxt_os_fvtxs_tracks_c22 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_c22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_c22 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_c22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_c22 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_c22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxs_tracks_c24 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_c24"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_c24 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_c24"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_c24 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_c24"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxs_tracks_c26 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_c26"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_c26 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_c26"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_c26 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_c26"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c22  = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c24  = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c24"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c24a = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c24a"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c24b = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c24b"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c24c = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c24c"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c24d = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c24d"),"",2000, -0.5, 1999.5, -1.1, 1.1);

  // --- correction histograms

  // --- <<cos(n(phi1))>>
  nfvtxt_os_fvtxs_tracks_cos21 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_cos21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_cos21 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_cos21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_cos21 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_cos21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1))>>
  nfvtxt_os_fvtxs_tracks_sin21 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_sin21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_sin21 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_sin21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_sin21 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_sin21"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<cos(n(phi1+phi2))>>
  nfvtxt_os_fvtxs_tracks_cossum22 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_cossum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_cossum22 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_cossum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_cossum22 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_cossum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1+phi2))>>
  nfvtxt_os_fvtxs_tracks_sinsum22 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_sinsum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_sinsum22 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_sinsum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_sinsum22 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_sinsum22"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<cos(n(phi1-phi2-phi3))>>
  nfvtxt_os_fvtxs_tracks_cos23 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_cos23"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_cos23 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_cos23"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_cos23 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_cos23"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1-phi2-phi3))>>
  nfvtxt_os_fvtxs_tracks_sin23 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_sin23"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_sin23 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_sin23"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_sin23 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_sin23"),"",2000, -0.5, 1999.5, -1.1, 1.1);

  // ---------------------------------------------------------------------------------------------------------
  nfvtxt_os_fvtxs_tracks_c32 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_c32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_c32 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_c32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_c32 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_c32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxs_tracks_c34 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_c34"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_c34 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_c34"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_c34 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_c34"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxs_tracks_c36 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_c36"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_c36 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_c36"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_c36 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_c36"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c32  = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c34  = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c34"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c34a = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c34a"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c34b = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c34b"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c34c = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c34c"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxsfvtxn_tracks_c34d = new TProfile(Form("nfvtxt_os_fvtxsfvtxn_tracks_c34d"),"",2000, -0.5, 1999.5, -1.1, 1.1);

  // --- correction histograms

  // --- <<cos(n(phi1))>>
  nfvtxt_os_fvtxs_tracks_cos31 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_cos31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_cos31 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_cos31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_cos31 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_cos31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1))>>
  nfvtxt_os_fvtxs_tracks_sin31 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_sin31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_sin31 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_sin31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_sin31 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_sin31"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<cos(n(phi1+phi2))>>
  nfvtxt_os_fvtxs_tracks_cossum32 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_cossum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_cossum32 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_cossum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_cossum32 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_cossum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1+phi2))>>
  nfvtxt_os_fvtxs_tracks_sinsum32 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_sinsum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_sinsum32 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_sinsum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_sinsum32 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_sinsum32"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<cos(n(phi1-phi2-phi3))>>
  nfvtxt_os_fvtxs_tracks_cos33 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_cos33"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_cos33 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_cos33"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_cos33 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_cos33"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  // --- <<sin(n(phi1-phi2-phi3))>>
  nfvtxt_os_fvtxs_tracks_sin33 = new TProfile(Form("nfvtxt_os_fvtxs_tracks_sin33"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxn_tracks_sin33 = new TProfile(Form("nfvtxt_os_fvtxn_tracks_sin33"),"",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_os_fvtxc_tracks_sin33 = new TProfile(Form("nfvtxt_os_fvtxc_tracks_sin33"),"",2000, -0.5, 1999.5, -1.1, 1.1);



  // ---------------------------------------------------------------------------------------------------------
  // --- centrality
  // ---------------------------------------------------------------------------------------------------------

  centrality_os_fvtxs_tracks_c22 = new TProfile(Form("centrality_os_fvtxs_tracks_c22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_c22 = new TProfile(Form("centrality_os_fvtxn_tracks_c22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_c22 = new TProfile(Form("centrality_os_fvtxc_tracks_c22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxs_tracks_c24 = new TProfile(Form("centrality_os_fvtxs_tracks_c24"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_c24 = new TProfile(Form("centrality_os_fvtxn_tracks_c24"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_c24 = new TProfile(Form("centrality_os_fvtxc_tracks_c24"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxs_tracks_c26 = new TProfile(Form("centrality_os_fvtxs_tracks_c26"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_c26 = new TProfile(Form("centrality_os_fvtxn_tracks_c26"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_c26 = new TProfile(Form("centrality_os_fvtxc_tracks_c26"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxsfvtxn_tracks_c22  = new TProfile(Form("centrality_os_fvtxsfvtxn_tracks_c22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxsfvtxn_tracks_c24  = new TProfile(Form("centrality_os_fvtxsfvtxn_tracks_c24"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxsfvtxn_tracks_c24a = new TProfile(Form("centrality_os_fvtxsfvtxn_tracks_c24a"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxsfvtxn_tracks_c24b = new TProfile(Form("centrality_os_fvtxsfvtxn_tracks_c24b"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxsfvtxn_tracks_c24c = new TProfile(Form("centrality_os_fvtxsfvtxn_tracks_c24c"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxsfvtxn_tracks_c24d = new TProfile(Form("centrality_os_fvtxsfvtxn_tracks_c24d"),"",100, -0.5, 99.5, -1.1, 1.1);

  // --- correction histograms

  // --- <<cos(n(phi1))>>
  centrality_os_fvtxs_tracks_cos21 = new TProfile(Form("centrality_os_fvtxs_tracks_cos21"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_cos21 = new TProfile(Form("centrality_os_fvtxn_tracks_cos21"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_cos21 = new TProfile(Form("centrality_os_fvtxc_tracks_cos21"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<sin(n(phi1))>>
  centrality_os_fvtxs_tracks_sin21 = new TProfile(Form("centrality_os_fvtxs_tracks_sin21"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_sin21 = new TProfile(Form("centrality_os_fvtxn_tracks_sin21"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_sin21 = new TProfile(Form("centrality_os_fvtxc_tracks_sin21"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<cos(n(phi1+phi2))>>
  centrality_os_fvtxs_tracks_cossum22 = new TProfile(Form("centrality_os_fvtxs_tracks_cossum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_cossum22 = new TProfile(Form("centrality_os_fvtxn_tracks_cossum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_cossum22 = new TProfile(Form("centrality_os_fvtxc_tracks_cossum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<sin(n(phi1+phi2))>>
  centrality_os_fvtxs_tracks_sinsum22 = new TProfile(Form("centrality_os_fvtxs_tracks_sinsum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_sinsum22 = new TProfile(Form("centrality_os_fvtxn_tracks_sinsum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_sinsum22 = new TProfile(Form("centrality_os_fvtxc_tracks_sinsum22"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<cos(n(phi1-phi2-phi3))>>
  centrality_os_fvtxs_tracks_cos23 = new TProfile(Form("centrality_os_fvtxs_tracks_cos23"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_cos23 = new TProfile(Form("centrality_os_fvtxn_tracks_cos23"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_cos23 = new TProfile(Form("centrality_os_fvtxc_tracks_cos23"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<sin(n(phi1-phi2-phi3))>>
  centrality_os_fvtxs_tracks_sin23 = new TProfile(Form("centrality_os_fvtxs_tracks_sin23"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_sin23 = new TProfile(Form("centrality_os_fvtxn_tracks_sin23"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_sin23 = new TProfile(Form("centrality_os_fvtxc_tracks_sin23"),"",100, -0.5, 99.5, -1.1, 1.1);

  // ---------------------------------------------------------------------------------------------------------
  centrality_os_fvtxs_tracks_c32 = new TProfile(Form("centrality_os_fvtxs_tracks_c32"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_c32 = new TProfile(Form("centrality_os_fvtxn_tracks_c32"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_c32 = new TProfile(Form("centrality_os_fvtxc_tracks_c32"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxsfvtxn_tracks_c32  = new TProfile(Form("centrality_os_fvtxsfvtxn_tracks_c32"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<cos(n(phi1))>>
  centrality_os_fvtxs_tracks_cos31 = new TProfile(Form("centrality_os_fvtxs_tracks_cos31"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_cos31 = new TProfile(Form("centrality_os_fvtxn_tracks_cos31"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_cos31 = new TProfile(Form("centrality_os_fvtxc_tracks_cos31"),"",100, -0.5, 99.5, -1.1, 1.1);
  // --- <<sin(n(phi1))>>
  centrality_os_fvtxs_tracks_sin31 = new TProfile(Form("centrality_os_fvtxs_tracks_sin31"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxn_tracks_sin31 = new TProfile(Form("centrality_os_fvtxn_tracks_sin31"),"",100, -0.5, 99.5, -1.1, 1.1);
  centrality_os_fvtxc_tracks_sin31 = new TProfile(Form("centrality_os_fvtxc_tracks_sin31"),"",100, -0.5, 99.5, -1.1, 1.1);



  // ---------------------------------------------------------------------------------------------------------
  for ( int i = 0; i < 8; ++i ) tp1f_special_fvtx_tracks_ab[i] = new TProfile(Form("tp1f_special_fvtx_tracks_ab%d",i),"",12,-3,3,-1.1,1.1,"");
  tp1f_special_fvtx_tracks_aa = new TProfile("tp1f_special_fvtx_tracks_aa","",12,-3,3,-1.1,1.1,"");
  tp1f_special_fvtx_tracks_aa_cos = new TProfile("tp1f_special_fvtx_tracks_aa_cos","",12,-3,3,-1.1,1.1,"");
  tp1f_special_fvtx_tracks_aa_sin = new TProfile("tp1f_special_fvtx_tracks_aa_sin","",12,-3,3,-1.1,1.1,"");

  // ---
  // ---

  nfvtxt_tracks_south_qx2 = new TProfile("nfvtxt_tracks_south_qx2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_qx3 = new TProfile("nfvtxt_tracks_south_qx3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_qx4 = new TProfile("nfvtxt_tracks_south_qx4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_qx6 = new TProfile("nfvtxt_tracks_south_qx6","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_qy2 = new TProfile("nfvtxt_tracks_south_qy2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_qy3 = new TProfile("nfvtxt_tracks_south_qy3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_qy4 = new TProfile("nfvtxt_tracks_south_qy4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_qy6 = new TProfile("nfvtxt_tracks_south_qy6","",2000, -0.5, 1999.5, -1.1, 1.1);

  nfvtxt_tracks_south_inner_qx2 = new TProfile("nfvtxt_tracks_south_inner_qx2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_inner_qx3 = new TProfile("nfvtxt_tracks_south_inner_qx3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_inner_qx4 = new TProfile("nfvtxt_tracks_south_inner_qx4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_inner_qx6 = new TProfile("nfvtxt_tracks_south_inner_qx6","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_inner_qy2 = new TProfile("nfvtxt_tracks_south_inner_qy2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_inner_qy3 = new TProfile("nfvtxt_tracks_south_inner_qy3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_inner_qy4 = new TProfile("nfvtxt_tracks_south_inner_qy4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_inner_qy6 = new TProfile("nfvtxt_tracks_south_inner_qy6","",2000, -0.5, 1999.5, -1.1, 1.1);

  nfvtxt_tracks_south_outer_qx2 = new TProfile("nfvtxt_tracks_south_outer_qx2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_outer_qx3 = new TProfile("nfvtxt_tracks_south_outer_qx3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_outer_qx4 = new TProfile("nfvtxt_tracks_south_outer_qx4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_outer_qx6 = new TProfile("nfvtxt_tracks_south_outer_qx6","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_outer_qy2 = new TProfile("nfvtxt_tracks_south_outer_qy2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_outer_qy3 = new TProfile("nfvtxt_tracks_south_outer_qy3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_outer_qy4 = new TProfile("nfvtxt_tracks_south_outer_qy4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_south_outer_qy6 = new TProfile("nfvtxt_tracks_south_outer_qy6","",2000, -0.5, 1999.5, -1.1, 1.1);

  nfvtxt_tracks_north_qx2 = new TProfile("nfvtxt_tracks_north_qx2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_qx3 = new TProfile("nfvtxt_tracks_north_qx3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_qx4 = new TProfile("nfvtxt_tracks_north_qx4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_qx6 = new TProfile("nfvtxt_tracks_north_qx6","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_qy2 = new TProfile("nfvtxt_tracks_north_qy2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_qy3 = new TProfile("nfvtxt_tracks_north_qy3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_qy4 = new TProfile("nfvtxt_tracks_north_qy4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_qy6 = new TProfile("nfvtxt_tracks_north_qy6","",2000, -0.5, 1999.5, -1.1, 1.1);

  nfvtxt_tracks_north_inner_qx2 = new TProfile("nfvtxt_tracks_north_inner_qx2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_inner_qx3 = new TProfile("nfvtxt_tracks_north_inner_qx3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_inner_qx4 = new TProfile("nfvtxt_tracks_north_inner_qx4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_inner_qx6 = new TProfile("nfvtxt_tracks_north_inner_qx6","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_inner_qy2 = new TProfile("nfvtxt_tracks_north_inner_qy2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_inner_qy3 = new TProfile("nfvtxt_tracks_north_inner_qy3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_inner_qy4 = new TProfile("nfvtxt_tracks_north_inner_qy4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_inner_qy6 = new TProfile("nfvtxt_tracks_north_inner_qy6","",2000, -0.5, 1999.5, -1.1, 1.1);

  nfvtxt_tracks_north_outer_qx2 = new TProfile("nfvtxt_tracks_north_outer_qx2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_outer_qx3 = new TProfile("nfvtxt_tracks_north_outer_qx3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_outer_qx4 = new TProfile("nfvtxt_tracks_north_outer_qx4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_outer_qx6 = new TProfile("nfvtxt_tracks_north_outer_qx6","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_outer_qy2 = new TProfile("nfvtxt_tracks_north_outer_qy2","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_outer_qy3 = new TProfile("nfvtxt_tracks_north_outer_qy3","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_outer_qy4 = new TProfile("nfvtxt_tracks_north_outer_qy4","",2000, -0.5, 1999.5, -1.1, 1.1);
  nfvtxt_tracks_north_outer_qy6 = new TProfile("nfvtxt_tracks_north_outer_qy6","",2000, -0.5, 1999.5, -1.1, 1.1);




  centrality_tracks_south_qx2 = new TProfile("centrality_tracks_south_qx2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_qx3 = new TProfile("centrality_tracks_south_qx3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_qx4 = new TProfile("centrality_tracks_south_qx4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_qx6 = new TProfile("centrality_tracks_south_qx6","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_qy2 = new TProfile("centrality_tracks_south_qy2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_qy3 = new TProfile("centrality_tracks_south_qy3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_qy4 = new TProfile("centrality_tracks_south_qy4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_qy6 = new TProfile("centrality_tracks_south_qy6","",100, -0.5, 99.5, -1.1, 1.1);

  centrality_tracks_south_inner_qx2 = new TProfile("centrality_tracks_south_inner_qx2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_inner_qx3 = new TProfile("centrality_tracks_south_inner_qx3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_inner_qx4 = new TProfile("centrality_tracks_south_inner_qx4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_inner_qx6 = new TProfile("centrality_tracks_south_inner_qx6","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_inner_qy2 = new TProfile("centrality_tracks_south_inner_qy2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_inner_qy3 = new TProfile("centrality_tracks_south_inner_qy3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_inner_qy4 = new TProfile("centrality_tracks_south_inner_qy4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_inner_qy6 = new TProfile("centrality_tracks_south_inner_qy6","",100, -0.5, 99.5, -1.1, 1.1);

  centrality_tracks_south_outer_qx2 = new TProfile("centrality_tracks_south_outer_qx2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_outer_qx3 = new TProfile("centrality_tracks_south_outer_qx3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_outer_qx4 = new TProfile("centrality_tracks_south_outer_qx4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_outer_qx6 = new TProfile("centrality_tracks_south_outer_qx6","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_outer_qy2 = new TProfile("centrality_tracks_south_outer_qy2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_outer_qy3 = new TProfile("centrality_tracks_south_outer_qy3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_outer_qy4 = new TProfile("centrality_tracks_south_outer_qy4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_south_outer_qy6 = new TProfile("centrality_tracks_south_outer_qy6","",100, -0.5, 99.5, -1.1, 1.1);

  centrality_tracks_north_qx2 = new TProfile("centrality_tracks_north_qx2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_qx3 = new TProfile("centrality_tracks_north_qx3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_qx4 = new TProfile("centrality_tracks_north_qx4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_qx6 = new TProfile("centrality_tracks_north_qx6","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_qy2 = new TProfile("centrality_tracks_north_qy2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_qy3 = new TProfile("centrality_tracks_north_qy3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_qy4 = new TProfile("centrality_tracks_north_qy4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_qy6 = new TProfile("centrality_tracks_north_qy6","",100, -0.5, 99.5, -1.1, 1.1);

  centrality_tracks_north_inner_qx2 = new TProfile("centrality_tracks_north_inner_qx2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_inner_qx3 = new TProfile("centrality_tracks_north_inner_qx3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_inner_qx4 = new TProfile("centrality_tracks_north_inner_qx4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_inner_qx6 = new TProfile("centrality_tracks_north_inner_qx6","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_inner_qy2 = new TProfile("centrality_tracks_north_inner_qy2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_inner_qy3 = new TProfile("centrality_tracks_north_inner_qy3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_inner_qy4 = new TProfile("centrality_tracks_north_inner_qy4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_inner_qy6 = new TProfile("centrality_tracks_north_inner_qy6","",100, -0.5, 99.5, -1.1, 1.1);

  centrality_tracks_north_outer_qx2 = new TProfile("centrality_tracks_north_outer_qx2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_outer_qx3 = new TProfile("centrality_tracks_north_outer_qx3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_outer_qx4 = new TProfile("centrality_tracks_north_outer_qx4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_outer_qx6 = new TProfile("centrality_tracks_north_outer_qx6","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_outer_qy2 = new TProfile("centrality_tracks_north_outer_qy2","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_outer_qy3 = new TProfile("centrality_tracks_north_outer_qy3","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_outer_qy4 = new TProfile("centrality_tracks_north_outer_qy4","",100, -0.5, 99.5, -1.1, 1.1);
  centrality_tracks_north_outer_qy6 = new TProfile("centrality_tracks_north_outer_qy6","",100, -0.5, 99.5, -1.1, 1.1);




  return EVENT_OK;
}


// --- InitRun, part of Fun4All inheritance
int BoulderCumulants::InitRun(PHCompositeNode *topNode)
{

  int runnumber = 0;

  RunHeader *rh = findNode::getClass<RunHeader>(topNode, "RunHeader");
  if ( !rh )
  {
    cout << PHWHERE << " ERROR::RunHeader not found" << endl;
    return ABORTEVENT;
  }
  runnumber = rh->get_RunNumber();

  // --- reset all
  for ( int i = 0; i < 100; ++i )
    {
      offset_centrality_qx2_south[i] = 0;
      offset_centrality_qx4_south[i] = 0;
      offset_centrality_qx6_south[i] = 0;
      offset_centrality_qy2_south[i] = 0;
      offset_centrality_qy4_south[i] = 0;
      offset_centrality_qy6_south[i] = 0;
      offset_centrality_qx2_north[i] = 0;
      offset_centrality_qx4_north[i] = 0;
      offset_centrality_qx6_north[i] = 0;
      offset_centrality_qy2_north[i] = 0;
      offset_centrality_qy4_north[i] = 0;
      offset_centrality_qy6_north[i] = 0;
    }
  // --- then set again
  SetQvectorOffsets(runnumber);



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


// --- ResetEvent, part of Fun4All inheritance, called after every event by Fun4All
// int BoulderCumulants::ResetEvent(PHCompositeNode *topNode)
// {
//   if (_verbosity > 1) cout << PHWHERE << "::ResetEvent() - entered." << endl;

//   event         = -9999;
//   centrality    = -9999;
//   npc1          = -9999;
//   trigger_scaled = -9999;
//   trigger_live   = -9999;
//   // bbc_qn        = -9999;
//   // bbc_qs        = -9999;
//   bbc_z         = -9999;
//   vtx_z         = -9999;
//   bc_x          = -9999;
//   bc_y          = -9999;
//   //  ntracklets    = -9999;


//   return EVENT_OK;

// }



// --- process_event, inherited from Fun4All, does the main part of the analysis on an event by event basis
int BoulderCumulants::process_event(PHCompositeNode *topNode)
{

  if (_verbosity > 1) cout << PHWHERE << "::process_event() - entered on event #" << _ievent << endl;
  else if ((_ievent) % 10000 == 0) cout << PHWHERE << "::process_event() - event #" << _ievent << endl;

  // advance event counter
  _ievent++;

  event = _ievent;



  //---------------------------------
  // Run Number Selection Capability
  //---------------------------------

  if ( _verbosity > 1 ) cout << "getting the run information" << endl;

  int runnumber = 0;

  RunHeader *rh = findNode::getClass<RunHeader>(topNode, "RunHeader");
  if (!rh)
  {
    cout << PHWHERE << " ERROR::RunHeader not found" << endl;
    return ABORTEVENT;
  }
  else
  {
    runnumber = rh->get_RunNumber();
  }

  if (_use_runlist)
  {
    if (is_run_in_list(runnumber) == false)
    {
      if (_verbosity > 1) {
        cout << endl << "ABORTING RUN, Run number: " << runnumber << " is not in the run list" << endl << endl;
      }
      return ABORTEVENT;
    }
  }


  //-------------------------------
  // Grab info off of the node tree
  //-------------------------------

  if ( _verbosity > 1 ) cout << "getting the info from the node tree" << endl;

  // --- trigger object
  TrigLvl1 *triggers = findNode::getClass<TrigLvl1>(topNode, "TrigLvl1");
  if (!triggers)
  {
    cout << PHWHERE << " ERROR::TrigLvl1 not found" << endl;
    return ABORTEVENT;
  }

  // --- global object (centrality, bbc charge, etc)
  PHGlobal *global = findNode::getClass<PHGlobal>(topNode, "PHGlobal");
  if (!global)
  {
    cout << PHWHERE << " ERROR::PHGlobal not found" << endl;
    return ABORTEVENT;
  }

  // --- event header
  EventHeader *evthead = findNode::getClass<EventHeader>(topNode, "EventHeader");
  if (!evthead)
  {
    cout << PHWHERE << " ERROR::EventHeader not found" << endl;
    return ABORTEVENT;
  }

  // --- vertex object (bbc event vertex, fvtx event vertex, etc)
  VtxOut *vertexes = findNode::getClass<VtxOut>(topNode, "VtxOut");
  if (!vertexes)
  {
    cout << PHWHERE << " ERROR::VtxOut not found" << endl;
    return ABORTEVENT;
  }

  // --- fvtx track object
  TFvtxCompactTrkMap* trkfvtx_map = findNode::getClass<TFvtxCompactTrkMap>(topNode, "TFvtxCompactTrkMap");
  if (!trkfvtx_map)
  {
    cout << PHWHERE << " No TFvtxCompactTrkMap object !" << endl;
    return ABORTEVENT;
  }

  //---------------------------------------------------------//
  //
  //         Make Event Selection
  //
  //---------------------------------------------------------//

  if ( _verbosity > 1 ) cout << "applying event selection criteria" << endl;

  if ( use_utils )
    {
      if ( _verbosity > 1 ) cout << "using utils to check if event is ok " << endl;
      if (!_utils->is_event_ok(topNode)) return EVENT_OK;
      if ( _verbosity > 1 ) cout << "event passed utils check " << endl;
    }



  //---------------------------------------------------------//
  //
  //         Reading in Global Event Information into Tree
  //
  //---------------------------------------------------------//

  PHPoint precise_vertex1 = vertexes->get_Vertex("SVX_PRECISE");
  vtx_z = precise_vertex1.getZ();
  if (vtx_z != vtx_z) vtx_z = -9999; //NAN check

  PHPoint svx_fast = vertexes->get_Vertex("SVX");//seed vertex
  bc_x = svx_fast.getX();//these are actually the beam center
  bc_y = svx_fast.getY();

  // phglobal fields
  centrality  = global->getCentrality();
  icent = (int)centrality;
  if ( icent < 0 ) icent = 99; // last bin is always empty and this protects against invalid read
  bbc_qn      = global->getBbcChargeN();
  bbc_qs      = global->getBbcChargeS();
  float bbc_charge_sum = bbc_qn+bbc_qs;
  npc1        = global->getNumberPC1Hits();
  event = evthead->get_EvtSequence();
  trigger_scaled = triggers->get_lvl1_trigscaled();
  trigger_live = triggers->get_lvl1_triglive();

  if ( !use_utils && centrality < 0  ) return EVENT_OK;
  if ( !use_utils && centrality > 99 ) return EVENT_OK;



  // --- bbc_z...
  PHPoint vertex1 = vertexes->get_Vertex("BBC");
  bbc_z = vertex1.getZ();
  if ( bbc_z != bbc_z ) bbc_z = -9999; // reassign nan

  if ( !use_utils && fabs(bbc_z) > 10.0 ) return EVENT_OK;

  PHPoint fvtx_vertex = vertexes->get_Vertex("FVTX");
  FVTX_X = fvtx_vertex.getX();
  FVTX_Y = fvtx_vertex.getY();
  FVTX_Z = fvtx_vertex.getZ();
  if ( FVTX_Z != FVTX_Z ) FVTX_Z = -9999; // reassign nan

  // cout << endl;
  // cout << "--- starting vertex checking ---" << endl;
  float zvtx = bbc_z;
  if ( use_utils )
    {
      if ( _verbosity > 1 ) cout << "using utils to get vertex " << endl;
      zvtx = _utils->get_vrtx(topNode);
      if ( _verbosity > 1 ) cout << "got the vertex from utils" << endl;
    }

  if ( _verbosity > 1 ) cout << "FVTX vertex points: " << FVTX_X << " " << FVTX_Y << " " << FVTX_Z << endl;



  // ---

  // --- fvtx tracks
  float fvtxs_tracks_qx2[3]; // both, inner, outer
  float fvtxs_tracks_qy2[3];
  float fvtxs_tracks_qx3[3];
  float fvtxs_tracks_qy3[3];
  float fvtxs_tracks_qx4[3];
  float fvtxs_tracks_qy4[3];
  float fvtxs_tracks_qx6[3];
  float fvtxs_tracks_qy6[3];
  float fvtxs_tracks_qw[3];
  float fvtxn_tracks_qx2[3]; // both, inner, outer
  float fvtxn_tracks_qy2[3];
  float fvtxn_tracks_qx3[3];
  float fvtxn_tracks_qy3[3];
  float fvtxn_tracks_qx4[3];
  float fvtxn_tracks_qy4[3];
  float fvtxn_tracks_qx6[3];
  float fvtxn_tracks_qy6[3];
  float fvtxn_tracks_qw[3];

  for ( int i = 0; i < 3; ++i )
  {
    fvtxs_tracks_qx2[i] = 0.0;
    fvtxs_tracks_qy2[i] = 0.0;
    fvtxs_tracks_qx3[i] = 0.0;
    fvtxs_tracks_qy3[i] = 0.0;
    fvtxs_tracks_qx4[i] = 0.0;
    fvtxs_tracks_qy4[i] = 0.0;
    fvtxs_tracks_qx6[i] = 0.0;
    fvtxs_tracks_qy6[i] = 0.0;
    fvtxs_tracks_qw[i] = 0.0;
    fvtxn_tracks_qx2[i] = 0.0;
    fvtxn_tracks_qy2[i] = 0.0;
    fvtxn_tracks_qx3[i] = 0.0;
    fvtxn_tracks_qy3[i] = 0.0;
    fvtxn_tracks_qx4[i] = 0.0;
    fvtxn_tracks_qy4[i] = 0.0;
    fvtxn_tracks_qx6[i] = 0.0;
    fvtxn_tracks_qy6[i] = 0.0;
    fvtxn_tracks_qw[i] = 0.0;
  } // loop over layers

  int ntrack_south_inner = 0;
  int ntrack_north_inner = 0;
  int ntrack_south_outer = 0;
  int ntrack_north_outer = 0;

  float special_fvtx_tracks_qx2[8];
  float special_fvtx_tracks_qy2[8];
  float special_fvtx_tracks_qw[8];
  for ( int i = 0; i < 8; ++i )
  {
    special_fvtx_tracks_qx2[i] = 0;
    special_fvtx_tracks_qy2[i] = 0;
    special_fvtx_tracks_qw[i] = 0;
  }


  // --- initialize Q-vectors for tree
  for ( int i = 0; i < 9; ++i )
    {
      d_NorthQX[i] = 0;
      d_NorthQY[i] = 0;
      d_SouthQX[i] = 0;
      d_SouthQY[i] = 0;
    }
  d_NorthQW = 0;
  d_SouthQW = 0;

  //int ntr = -1;
  //int ntr = 0;
  nfvtxt = 0;
  nfvtxt_south = 0;
  nfvtxt_north = 0;
  nfvtxt_raw = 0;
  // --- first fvtx track loop
  if ( _verbosity > 1 ) cout << "entering fvtx track loop" << endl;
  TFvtxCompactTrkMap::const_iterator trk_iter = trkfvtx_map->range();
  while ( TFvtxCompactTrkMap::const_pointer trk_ptr = trk_iter.next() )
    {
      TFvtxCompactTrk* fvtx_trk = trk_ptr->get();

      ++nfvtxt_raw;
      // --- use the utility class to make the track selections
      if ( use_utils )
	{
	  if ( _verbosity > 2 ) cout << "using utils to check if the track is ok " << endl;
	  if ( !_utils->is_fvtx_track_ok(fvtx_trk, zvtx) ) continue;
	  if ( _verbosity > 2 ) cout << "track pass utils " << endl;
	}

      float the = fvtx_trk->get_fvtx_theta();
      float eta = fvtx_trk->get_fvtx_eta();
      float phi = fvtx_trk->get_fvtx_phi();
      // int   arm = (int)fvtx_trk->get_arm();
      float fvtx_x      = fvtx_trk->get_fvtx_vtx().getX();
      float fvtx_y      = fvtx_trk->get_fvtx_vtx().getY();
      float fvtx_z      = fvtx_trk->get_fvtx_vtx().getZ();
      float chisq       = fvtx_trk->get_chi2_ndf();
      int   nhits       = (int)fvtx_trk->get_nhits();

      // fix total momentum to 1.0 (for rotating due to beamtilt)
      double px = 1.0 * sin(the) * cos(phi);
      double py = 1.0 * sin(the) * sin(phi);
      double pz = 1.0 * cos(the);

      if ( use_utils )
	{
	  // rotate based on beamtilt, need to do both rotations with lab frame coordinates
	  double pxprime = _utils->rotate_x(px, pz);
	  double pzprime = _utils->rotate_z(px, pz);
	  // now reassign px and pz to the new rotated frame coordinates
	  px = pxprime;
	  pz = pzprime;
	  phi = TMath::ATan2(py, px);
	  the = TMath::ACos(pz / TMath::Sqrt(px * px + py * py + pz * pz));
	}

      float vertex_z = zvtx;
      if ( FVTX_Z > -999 ) vertex_z = FVTX_Z;
      float DCA_x      = fvtx_x + tan(the) * cos(phi) * (vertex_z - fvtx_z);
      float DCA_y      = fvtx_y + tan(the) * sin(phi) * (vertex_z - fvtx_z);

      if ( !use_utils )
        {
          if ( fabs(DCA_x) > 2.0 || fabs(DCA_y) > 2.0 ) continue;
          if ( nhits < 3 ) continue;
          if ( chisq > 5 ) continue;
        }

      // --- Q-vectors for tree
      if ( eta > 0 )
        {
          for ( int i = 0; i < 9; ++i )
            {
              d_NorthQX[i] += cos(i*phi);
              d_NorthQY[i] += sin(i*phi);
            }
          d_NorthQW += 1;
        }
      if ( eta < 0 )
        {
          for ( int i = 0; i < 9; ++i )
            {
              d_SouthQX[i] += cos(i*phi);
              d_SouthQY[i] += sin(i*phi);
            }
          d_SouthQW += 1;
        }

      // --- now fill the Q-vector arrays
      int special_index = -1;
      if ( eta > -3.0 && eta < -2.5 ) special_index = 0;
      if ( eta > -2.5 && eta < -2.0 ) special_index = 1;
      if ( eta > -2.0 && eta < -1.5 ) special_index = 2;
      if ( eta > -1.5 && eta < -1.0 ) special_index = 3;
      if ( eta > 1.0 && eta < 1.5 ) special_index = 4;
      if ( eta > 1.5 && eta < 2.0 ) special_index = 5;
      if ( eta > 2.0 && eta < 2.5 ) special_index = 6;
      if ( eta > 2.5 && eta < 3.0 ) special_index = 7;
      if ( special_index > -1 && special_index < 8 )
	{
	  special_fvtx_tracks_qx2[special_index] += cos(2*phi);
	  special_fvtx_tracks_qy2[special_index] += sin(2*phi);
	  special_fvtx_tracks_qw[special_index] += 1;
	}

      bool is_south = ( eta < 0 );
      bool is_south_inner = ( eta > -2 && eta < 0 );
      bool is_south_outer = ( eta < -2 );
      bool is_north = ( eta > 0 );
      bool is_north_inner = ( eta < 2 && eta > 0 );
      bool is_north_outer = ( eta > 2 );

      if ( is_south )
	{
	  fvtxs_tracks_qx2[0] += cos(2*phi);
	  fvtxs_tracks_qy2[0] += sin(2*phi);
	  fvtxs_tracks_qx3[0] += cos(3*phi);
	  fvtxs_tracks_qy3[0] += sin(3*phi);
	  fvtxs_tracks_qx4[0] += cos(4*phi);
	  fvtxs_tracks_qy4[0] += sin(4*phi);
	  fvtxs_tracks_qx6[0] += cos(6*phi);
	  fvtxs_tracks_qy6[0] += sin(6*phi);
	  fvtxs_tracks_qw[0] += 1;
	}
      if ( is_south_inner )
	{
	  fvtxs_tracks_qx2[1] += cos(2*phi);
	  fvtxs_tracks_qy2[1] += sin(2*phi);
	  fvtxs_tracks_qx3[1] += cos(3*phi);
	  fvtxs_tracks_qy3[1] += sin(3*phi);
	  fvtxs_tracks_qx4[1] += cos(4*phi);
	  fvtxs_tracks_qy4[1] += sin(4*phi);
	  fvtxs_tracks_qx6[1] += cos(6*phi);
	  fvtxs_tracks_qy6[1] += sin(6*phi);
	  fvtxs_tracks_qw[1] += 1;
	  ++ntrack_south_inner;
	}
      if ( is_south_outer )
	{
	  fvtxs_tracks_qx2[2] += cos(2*phi);
	  fvtxs_tracks_qy2[2] += sin(2*phi);
	  fvtxs_tracks_qx3[2] += cos(3*phi);
	  fvtxs_tracks_qy3[2] += sin(3*phi);
	  fvtxs_tracks_qx4[2] += cos(4*phi);
	  fvtxs_tracks_qy4[2] += sin(4*phi);
	  fvtxs_tracks_qx6[2] += cos(6*phi);
	  fvtxs_tracks_qy6[2] += sin(6*phi);
	  fvtxs_tracks_qw[2] += 1;
	  ++ntrack_south_outer;
	}
      if ( is_north )
	{
	  fvtxn_tracks_qx2[0] += cos(2*phi);
	  fvtxn_tracks_qy2[0] += sin(2*phi);
	  fvtxn_tracks_qx3[0] += cos(3*phi);
	  fvtxn_tracks_qy3[0] += sin(3*phi);
	  fvtxn_tracks_qx4[0] += cos(4*phi);
	  fvtxn_tracks_qy4[0] += sin(4*phi);
	  fvtxn_tracks_qx6[0] += cos(6*phi);
	  fvtxn_tracks_qy6[0] += sin(6*phi);
	  fvtxn_tracks_qw[0] += 1;
	}
      if ( is_north_inner )
	{
	  fvtxn_tracks_qx2[1] += cos(2*phi);
	  fvtxn_tracks_qy2[1] += sin(2*phi);
	  fvtxn_tracks_qx3[1] += cos(3*phi);
	  fvtxn_tracks_qy3[1] += sin(3*phi);
	  fvtxn_tracks_qx4[1] += cos(4*phi);
	  fvtxn_tracks_qy4[1] += sin(4*phi);
	  fvtxn_tracks_qx6[1] += cos(6*phi);
	  fvtxn_tracks_qy6[1] += sin(6*phi);
	  fvtxn_tracks_qw[1] += 1;
	  ++ntrack_north_inner;
	}
      if ( is_north_outer )
	{
	  fvtxn_tracks_qx2[2] += cos(2*phi);
	  fvtxn_tracks_qy2[2] += sin(2*phi);
	  fvtxn_tracks_qx3[2] += cos(3*phi);
	  fvtxn_tracks_qy3[2] += sin(3*phi);
	  fvtxn_tracks_qx4[2] += cos(4*phi);
	  fvtxn_tracks_qy4[2] += sin(4*phi);
	  fvtxn_tracks_qx6[2] += cos(6*phi);
	  fvtxn_tracks_qy6[2] += sin(6*phi);
	  fvtxn_tracks_qw[2] += 1;
	  ++ntrack_north_outer;
	}

      ++nfvtxt;
      if ( eta < 0 ) ++nfvtxt_south;
      if ( eta > 0 ) ++nfvtxt_north;

    } // end while loop over tracks

  th1d_nfvtxt_combinedER->Fill(nfvtxt);
  th1d_nfvtxt_combined->Fill(nfvtxt);
  th1d_nfvtxt_north->Fill(nfvtxt_north);
  th1d_nfvtxt_south->Fill(nfvtxt_south);

  th2d_nfvtxt_bbcsum->Fill(nfvtxt,bbc_charge_sum);
  th2d_nfvtxt_bbcsumratio->Fill(nfvtxt,bbc_charge_sum/(float)nfvtxt);

  bool passes = PassesTracksChargeRatio(nfvtxt,bbc_charge_sum);
  if ( _collsys == "Run14AuAu200" && !passes )
    {
      if ( _verbosity > 1 ) cout << "Making special event cut for " << _collsys << endl;
      return EVENT_OK;
    }

  //---------------------------------------------------------//
  //                 finished Get FVTX Tracks
  //---------------------------------------------------------//

  // --------------------------------------------------------------------------------------- //
  // --- calculations and histograms designed to be used with/for acceptance corrections --- //
  // --------------------------------------------------------------------------------------- //

  if ( _verbosity > 1 ) cout << "doing cumulant calculations and filling histograms" << endl;

  // --- FVTX south
  float ac_fvtxs_tracks_qw = fvtxs_tracks_qw[0];
  float ac_fvtxs_tracks_qx2 = fvtxs_tracks_qx2[0];
  float ac_fvtxs_tracks_qy2 = fvtxs_tracks_qy2[0];
  float ac_fvtxs_tracks_qx3 = fvtxs_tracks_qx3[0];
  float ac_fvtxs_tracks_qy3 = fvtxs_tracks_qy3[0];
  float ac_fvtxs_tracks_qx4 = fvtxs_tracks_qx4[0];
  float ac_fvtxs_tracks_qy4 = fvtxs_tracks_qy4[0];
  float ac_fvtxs_tracks_qx6 = fvtxs_tracks_qx6[0];
  float ac_fvtxs_tracks_qy6 = fvtxs_tracks_qy6[0];
  float ac_fvtxs_tracks_qq2 = calc2_event(ac_fvtxs_tracks_qx2,ac_fvtxs_tracks_qy2,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_qq3 = calc2_event(ac_fvtxs_tracks_qx3,ac_fvtxs_tracks_qy3,ac_fvtxs_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_c22->Fill(nfvtxt,ac_fvtxs_tracks_qq2);
  nfvtxt_ac_fvtxs_tracks_cos21->Fill(nfvtxt,ac_fvtxs_tracks_qx2/ac_fvtxs_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_sin21->Fill(nfvtxt,ac_fvtxs_tracks_qy2/ac_fvtxs_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_c32->Fill(nfvtxt,ac_fvtxs_tracks_qq3);
  nfvtxt_ac_fvtxs_tracks_cos31->Fill(nfvtxt,ac_fvtxs_tracks_qx3/ac_fvtxs_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_sin31->Fill(nfvtxt,ac_fvtxs_tracks_qy3/ac_fvtxs_tracks_qw);
  TComplex tc_ac_fvtxs_tracks_Q2(ac_fvtxs_tracks_qx2,ac_fvtxs_tracks_qy2);
  TComplex tc_ac_fvtxs_tracks_Q3(ac_fvtxs_tracks_qx3,ac_fvtxs_tracks_qy3);
  TComplex tc_ac_fvtxs_tracks_Q4(ac_fvtxs_tracks_qx4,ac_fvtxs_tracks_qy4);
  TComplex tc_ac_fvtxs_tracks_Q6(ac_fvtxs_tracks_qx6,ac_fvtxs_tracks_qy6);
  float ac_fvtxs_tracks_cossum22 = calccossum2_event(tc_ac_fvtxs_tracks_Q2,tc_ac_fvtxs_tracks_Q4,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_sinsum22 = calcsinsum2_event(tc_ac_fvtxs_tracks_Q2,tc_ac_fvtxs_tracks_Q4,ac_fvtxs_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_cossum22->Fill(nfvtxt,ac_fvtxs_tracks_cossum22);
  nfvtxt_ac_fvtxs_tracks_sinsum22->Fill(nfvtxt,ac_fvtxs_tracks_sinsum22);
  float ac_fvtxs_tracks_cossum32 = calccossum2_event(tc_ac_fvtxs_tracks_Q3,tc_ac_fvtxs_tracks_Q6,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_sinsum32 = calcsinsum2_event(tc_ac_fvtxs_tracks_Q3,tc_ac_fvtxs_tracks_Q6,ac_fvtxs_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_cossum32->Fill(nfvtxt,ac_fvtxs_tracks_cossum32);
  nfvtxt_ac_fvtxs_tracks_sinsum32->Fill(nfvtxt,ac_fvtxs_tracks_sinsum32);
  float ac_fvtxs_tracks_cos23 = calccos3_event(tc_ac_fvtxs_tracks_Q2,tc_ac_fvtxs_tracks_Q4,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_sin23 = calcsin3_event(tc_ac_fvtxs_tracks_Q2,tc_ac_fvtxs_tracks_Q4,ac_fvtxs_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_cos23->Fill(nfvtxt,ac_fvtxs_tracks_cos23);
  nfvtxt_ac_fvtxs_tracks_sin23->Fill(nfvtxt,ac_fvtxs_tracks_sin23);
  float ac_fvtxs_tracks_cos33 = calccos3_event(tc_ac_fvtxs_tracks_Q3,tc_ac_fvtxs_tracks_Q6,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_sin33 = calcsin3_event(tc_ac_fvtxs_tracks_Q3,tc_ac_fvtxs_tracks_Q6,ac_fvtxs_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_cos33->Fill(nfvtxt,ac_fvtxs_tracks_cos33);
  nfvtxt_ac_fvtxs_tracks_sin33->Fill(nfvtxt,ac_fvtxs_tracks_sin33);

  // --- FVTX north
  float ac_fvtxn_tracks_qw = fvtxn_tracks_qw[0];
  float ac_fvtxn_tracks_qx2 = fvtxn_tracks_qx2[0];
  float ac_fvtxn_tracks_qy2 = fvtxn_tracks_qy2[0];
  float ac_fvtxn_tracks_qx3 = fvtxn_tracks_qx3[0];
  float ac_fvtxn_tracks_qy3 = fvtxn_tracks_qy3[0];
  float ac_fvtxn_tracks_qx4 = fvtxn_tracks_qx4[0];
  float ac_fvtxn_tracks_qy4 = fvtxn_tracks_qy4[0];
  float ac_fvtxn_tracks_qx6 = fvtxn_tracks_qx6[0];
  float ac_fvtxn_tracks_qy6 = fvtxn_tracks_qy6[0];
  float ac_fvtxn_tracks_qq2 = calc2_event(ac_fvtxn_tracks_qx2,ac_fvtxn_tracks_qy2,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_qq3 = calc2_event(ac_fvtxn_tracks_qx3,ac_fvtxn_tracks_qy3,ac_fvtxn_tracks_qw);
  nfvtxt_ac_fvtxn_tracks_c22->Fill(nfvtxt,ac_fvtxn_tracks_qq2);
  nfvtxt_ac_fvtxn_tracks_cos21->Fill(nfvtxt,ac_fvtxn_tracks_qx2/ac_fvtxn_tracks_qw);
  nfvtxt_ac_fvtxn_tracks_sin21->Fill(nfvtxt,ac_fvtxn_tracks_qy2/ac_fvtxn_tracks_qw);
  nfvtxt_ac_fvtxn_tracks_c32->Fill(nfvtxt,ac_fvtxn_tracks_qq3);
  nfvtxt_ac_fvtxn_tracks_cos31->Fill(nfvtxt,ac_fvtxn_tracks_qx3/ac_fvtxn_tracks_qw);
  nfvtxt_ac_fvtxn_tracks_sin31->Fill(nfvtxt,ac_fvtxn_tracks_qy3/ac_fvtxn_tracks_qw);
  TComplex tc_ac_fvtxn_tracks_Q2(ac_fvtxn_tracks_qx2,ac_fvtxn_tracks_qy2);
  TComplex tc_ac_fvtxn_tracks_Q3(ac_fvtxn_tracks_qx3,ac_fvtxn_tracks_qy3);
  TComplex tc_ac_fvtxn_tracks_Q4(ac_fvtxn_tracks_qx4,ac_fvtxn_tracks_qy4);
  TComplex tc_ac_fvtxn_tracks_Q6(ac_fvtxn_tracks_qx6,ac_fvtxn_tracks_qy6);
  float ac_fvtxn_tracks_cossum22 = calccossum2_event(tc_ac_fvtxn_tracks_Q2,tc_ac_fvtxn_tracks_Q4,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_sinsum22 = calcsinsum2_event(tc_ac_fvtxn_tracks_Q2,tc_ac_fvtxn_tracks_Q4,ac_fvtxn_tracks_qw);
  nfvtxt_ac_fvtxn_tracks_cossum22->Fill(nfvtxt,ac_fvtxn_tracks_cossum22);
  nfvtxt_ac_fvtxn_tracks_sinsum22->Fill(nfvtxt,ac_fvtxn_tracks_sinsum22);
  float ac_fvtxn_tracks_cossum32 = calccossum2_event(tc_ac_fvtxn_tracks_Q3,tc_ac_fvtxn_tracks_Q6,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_sinsum32 = calcsinsum2_event(tc_ac_fvtxn_tracks_Q3,tc_ac_fvtxn_tracks_Q6,ac_fvtxn_tracks_qw);
  nfvtxt_ac_fvtxn_tracks_cossum32->Fill(nfvtxt,ac_fvtxn_tracks_cossum32);
  nfvtxt_ac_fvtxn_tracks_sinsum32->Fill(nfvtxt,ac_fvtxn_tracks_sinsum32);
  float ac_fvtxn_tracks_cos23 = calccos3_event(tc_ac_fvtxn_tracks_Q2,tc_ac_fvtxn_tracks_Q4,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_sin23 = calcsin3_event(tc_ac_fvtxn_tracks_Q2,tc_ac_fvtxn_tracks_Q4,ac_fvtxn_tracks_qw);
  nfvtxt_ac_fvtxn_tracks_cos23->Fill(nfvtxt,ac_fvtxn_tracks_cos23);
  nfvtxt_ac_fvtxn_tracks_sin23->Fill(nfvtxt,ac_fvtxn_tracks_sin23);
  float ac_fvtxn_tracks_cos33 = calccos3_event(tc_ac_fvtxn_tracks_Q3,tc_ac_fvtxn_tracks_Q6,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_sin33 = calcsin3_event(tc_ac_fvtxn_tracks_Q3,tc_ac_fvtxn_tracks_Q6,ac_fvtxn_tracks_qw);
  nfvtxt_ac_fvtxn_tracks_cos33->Fill(nfvtxt,ac_fvtxn_tracks_cos33);
  nfvtxt_ac_fvtxn_tracks_sin33->Fill(nfvtxt,ac_fvtxn_tracks_sin33);

  // --- FVTX north and south combined
  float ac_fvtxc_tracks_qx2 = ac_fvtxs_tracks_qx2 + ac_fvtxn_tracks_qx2;
  float ac_fvtxc_tracks_qy2 = ac_fvtxs_tracks_qy2 + ac_fvtxn_tracks_qy2;
  float ac_fvtxc_tracks_qx3 = ac_fvtxs_tracks_qx3 + ac_fvtxn_tracks_qx3;
  float ac_fvtxc_tracks_qy3 = ac_fvtxs_tracks_qy3 + ac_fvtxn_tracks_qy3;
  float ac_fvtxc_tracks_qx4 = ac_fvtxs_tracks_qx4 + ac_fvtxn_tracks_qx4;
  float ac_fvtxc_tracks_qy4 = ac_fvtxs_tracks_qy4 + ac_fvtxn_tracks_qy4;
  float ac_fvtxc_tracks_qx6 = ac_fvtxs_tracks_qx6 + ac_fvtxn_tracks_qx6;
  float ac_fvtxc_tracks_qy6 = ac_fvtxs_tracks_qy6 + ac_fvtxn_tracks_qy6;
  float ac_fvtxc_tracks_qw = ac_fvtxs_tracks_qw + ac_fvtxn_tracks_qw;
  float ac_fvtxc_tracks_qq2 = calc2_event(ac_fvtxc_tracks_qx2,ac_fvtxc_tracks_qy2,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_qq3 = calc2_event(ac_fvtxc_tracks_qx3,ac_fvtxc_tracks_qy3,ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxc_tracks_c22->Fill(nfvtxt,ac_fvtxc_tracks_qq2);
  nfvtxt_ac_fvtxc_tracks_cos21->Fill(nfvtxt,ac_fvtxc_tracks_qx2/ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxc_tracks_sin21->Fill(nfvtxt,ac_fvtxc_tracks_qy2/ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxc_tracks_c32->Fill(nfvtxt,ac_fvtxc_tracks_qq3);
  nfvtxt_ac_fvtxc_tracks_cos31->Fill(nfvtxt,ac_fvtxc_tracks_qx3/ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxc_tracks_sin31->Fill(nfvtxt,ac_fvtxc_tracks_qy3/ac_fvtxc_tracks_qw);
  TComplex tc_ac_fvtxc_tracks_Q2(ac_fvtxc_tracks_qx2,ac_fvtxc_tracks_qy2);
  TComplex tc_ac_fvtxc_tracks_Q3(ac_fvtxc_tracks_qx3,ac_fvtxc_tracks_qy3);
  TComplex tc_ac_fvtxc_tracks_Q4(ac_fvtxc_tracks_qx4,ac_fvtxc_tracks_qy4);
  TComplex tc_ac_fvtxc_tracks_Q6(ac_fvtxc_tracks_qx6,ac_fvtxc_tracks_qy6);
  float ac_fvtxc_tracks_cossum22 = calccossum2_event(tc_ac_fvtxc_tracks_Q2,tc_ac_fvtxc_tracks_Q4,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_sinsum22 = calcsinsum2_event(tc_ac_fvtxc_tracks_Q2,tc_ac_fvtxc_tracks_Q4,ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxc_tracks_cossum22->Fill(nfvtxt,ac_fvtxc_tracks_cossum22);
  nfvtxt_ac_fvtxc_tracks_sinsum22->Fill(nfvtxt,ac_fvtxc_tracks_sinsum22);
  float ac_fvtxc_tracks_cossum32 = calccossum2_event(tc_ac_fvtxc_tracks_Q3,tc_ac_fvtxc_tracks_Q6,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_sinsum32 = calcsinsum2_event(tc_ac_fvtxc_tracks_Q3,tc_ac_fvtxc_tracks_Q6,ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxc_tracks_cossum32->Fill(nfvtxt,ac_fvtxc_tracks_cossum32);
  nfvtxt_ac_fvtxc_tracks_sinsum32->Fill(nfvtxt,ac_fvtxc_tracks_sinsum32);
  float ac_fvtxc_tracks_cos23 = calccos3_event(tc_ac_fvtxc_tracks_Q2,tc_ac_fvtxc_tracks_Q4,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_sin23 = calcsin3_event(tc_ac_fvtxc_tracks_Q2,tc_ac_fvtxc_tracks_Q4,ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxc_tracks_cos23->Fill(nfvtxt,ac_fvtxc_tracks_cos23);
  nfvtxt_ac_fvtxc_tracks_sin23->Fill(nfvtxt,ac_fvtxc_tracks_sin23);
  float ac_fvtxc_tracks_cos33 = calccos3_event(tc_ac_fvtxc_tracks_Q3,tc_ac_fvtxc_tracks_Q6,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_sin33 = calcsin3_event(tc_ac_fvtxc_tracks_Q3,tc_ac_fvtxc_tracks_Q6,ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxc_tracks_cos33->Fill(nfvtxt,ac_fvtxc_tracks_cos33);
  nfvtxt_ac_fvtxc_tracks_sin33->Fill(nfvtxt,ac_fvtxc_tracks_sin33);

  // --- scalar product, fvtxs dot fvtxn
  float ac_fvtxsfvtxn_tracks_qq2 = ( (ac_fvtxs_tracks_qx2*ac_fvtxn_tracks_qx2) + (ac_fvtxs_tracks_qy2*ac_fvtxn_tracks_qy2) ) / ( ac_fvtxs_tracks_qw*ac_fvtxn_tracks_qw );
  float ac_fvtxsfvtxn_tracks_qq3 = ( (ac_fvtxs_tracks_qx3*ac_fvtxn_tracks_qx3) + (ac_fvtxs_tracks_qy3*ac_fvtxn_tracks_qy3) ) / ( ac_fvtxs_tracks_qw*ac_fvtxn_tracks_qw );
  nfvtxt_ac_fvtxsfvtxn_tracks_c22->Fill(nfvtxt,ac_fvtxsfvtxn_tracks_qq2);
  nfvtxt_ac_fvtxsfvtxn_tracks_c32->Fill(nfvtxt,ac_fvtxsfvtxn_tracks_qq3);

  // --- now have a look at some 4 particle cumulants
  // --- calc4_event has the protection/requirement on the minimum number of tracks
  float ac_fvtxs_tracks_qqqq24 = calc4_event(ac_fvtxs_tracks_qx2,ac_fvtxs_tracks_qy2,ac_fvtxs_tracks_qx4,ac_fvtxs_tracks_qy4,ac_fvtxs_tracks_qw);
  float ac_fvtxn_tracks_qqqq24 = calc4_event(ac_fvtxn_tracks_qx2,ac_fvtxn_tracks_qy2,ac_fvtxn_tracks_qx4,ac_fvtxn_tracks_qy4,ac_fvtxn_tracks_qw);
  float ac_fvtxc_tracks_qqqq24 = calc4_event(ac_fvtxc_tracks_qx2,ac_fvtxc_tracks_qy2,ac_fvtxc_tracks_qx4,ac_fvtxc_tracks_qy4,ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_c24->Fill(nfvtxt,ac_fvtxs_tracks_qqqq24);
  nfvtxt_ac_fvtxn_tracks_c24->Fill(nfvtxt,ac_fvtxn_tracks_qqqq24);
  nfvtxt_ac_fvtxc_tracks_c24->Fill(nfvtxt,ac_fvtxc_tracks_qqqq24);

  float ac_fvtxs_tracks_qqqq34 = calc4_event(ac_fvtxs_tracks_qx3,ac_fvtxs_tracks_qy3,ac_fvtxs_tracks_qx6,ac_fvtxs_tracks_qy6,ac_fvtxs_tracks_qw);
  float ac_fvtxn_tracks_qqqq34 = calc4_event(ac_fvtxn_tracks_qx3,ac_fvtxn_tracks_qy3,ac_fvtxn_tracks_qx6,ac_fvtxn_tracks_qy6,ac_fvtxn_tracks_qw);
  float ac_fvtxc_tracks_qqqq34 = calc4_event(ac_fvtxc_tracks_qx3,ac_fvtxc_tracks_qy3,ac_fvtxc_tracks_qx6,ac_fvtxc_tracks_qy6,ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_c34->Fill(nfvtxt,ac_fvtxs_tracks_qqqq34);
  nfvtxt_ac_fvtxn_tracks_c34->Fill(nfvtxt,ac_fvtxn_tracks_qqqq34);
  nfvtxt_ac_fvtxc_tracks_c34->Fill(nfvtxt,ac_fvtxc_tracks_qqqq34);

  float ac_fvtxs_tracks_six = calc6_event(tc_ac_fvtxs_tracks_Q2,tc_ac_fvtxs_tracks_Q4,tc_ac_fvtxs_tracks_Q6,ac_fvtxs_tracks_qw);
  float ac_fvtxn_tracks_six = calc6_event(tc_ac_fvtxn_tracks_Q2,tc_ac_fvtxn_tracks_Q4,tc_ac_fvtxn_tracks_Q6,ac_fvtxn_tracks_qw);
  float ac_fvtxc_tracks_six = calc6_event(tc_ac_fvtxc_tracks_Q2,tc_ac_fvtxc_tracks_Q4,tc_ac_fvtxc_tracks_Q6,ac_fvtxc_tracks_qw);
  nfvtxt_ac_fvtxs_tracks_c26->Fill(nfvtxt,ac_fvtxs_tracks_six);
  nfvtxt_ac_fvtxn_tracks_c26->Fill(nfvtxt,ac_fvtxn_tracks_six);
  nfvtxt_ac_fvtxc_tracks_c26->Fill(nfvtxt,ac_fvtxc_tracks_six);

  // --------------------------------------------------------- //
  // --- centrality
  // --------------

  // --- south only
  centrality_ac_fvtxs_tracks_c22->Fill(centrality,ac_fvtxs_tracks_qq2);
  centrality_ac_fvtxs_tracks_cos21->Fill(centrality,ac_fvtxs_tracks_qx2/ac_fvtxs_tracks_qw);
  centrality_ac_fvtxs_tracks_sin21->Fill(centrality,ac_fvtxs_tracks_qy2/ac_fvtxs_tracks_qw);
  centrality_ac_fvtxs_tracks_c32->Fill(centrality,ac_fvtxs_tracks_qq3);
  centrality_ac_fvtxs_tracks_cos31->Fill(centrality,ac_fvtxs_tracks_qx3/ac_fvtxs_tracks_qw);
  centrality_ac_fvtxs_tracks_sin31->Fill(centrality,ac_fvtxs_tracks_qy3/ac_fvtxs_tracks_qw);
  centrality_ac_fvtxs_tracks_cossum22->Fill(centrality,ac_fvtxs_tracks_cossum22);
  centrality_ac_fvtxs_tracks_sinsum22->Fill(centrality,ac_fvtxs_tracks_sinsum22);
  centrality_ac_fvtxs_tracks_cos23->Fill(centrality,ac_fvtxs_tracks_cos23);
  centrality_ac_fvtxs_tracks_sin23->Fill(centrality,ac_fvtxs_tracks_sin23);
  // --- north only
  centrality_ac_fvtxn_tracks_c22->Fill(centrality,ac_fvtxn_tracks_qq2);
  centrality_ac_fvtxn_tracks_cos21->Fill(centrality,ac_fvtxn_tracks_qx2/ac_fvtxn_tracks_qw);
  centrality_ac_fvtxn_tracks_sin21->Fill(centrality,ac_fvtxn_tracks_qy2/ac_fvtxn_tracks_qw);
  centrality_ac_fvtxn_tracks_c32->Fill(centrality,ac_fvtxn_tracks_qq3);
  centrality_ac_fvtxn_tracks_cos31->Fill(centrality,ac_fvtxn_tracks_qx3/ac_fvtxn_tracks_qw);
  centrality_ac_fvtxn_tracks_sin31->Fill(centrality,ac_fvtxn_tracks_qy3/ac_fvtxn_tracks_qw);
  centrality_ac_fvtxn_tracks_cossum22->Fill(centrality,ac_fvtxn_tracks_cossum22);
  centrality_ac_fvtxn_tracks_sinsum22->Fill(centrality,ac_fvtxn_tracks_sinsum22);
  centrality_ac_fvtxn_tracks_cos23->Fill(centrality,ac_fvtxn_tracks_cos23);
  centrality_ac_fvtxn_tracks_sin23->Fill(centrality,ac_fvtxn_tracks_sin23);
  // --- combined
  centrality_ac_fvtxc_tracks_c22->Fill(centrality,ac_fvtxc_tracks_qq2);
  centrality_ac_fvtxc_tracks_cos21->Fill(centrality,ac_fvtxc_tracks_qx2/ac_fvtxc_tracks_qw);
  centrality_ac_fvtxc_tracks_sin21->Fill(centrality,ac_fvtxc_tracks_qy2/ac_fvtxc_tracks_qw);
  centrality_ac_fvtxc_tracks_c32->Fill(centrality,ac_fvtxc_tracks_qq3);
  centrality_ac_fvtxc_tracks_cos31->Fill(centrality,ac_fvtxc_tracks_qx3/ac_fvtxc_tracks_qw);
  centrality_ac_fvtxc_tracks_sin31->Fill(centrality,ac_fvtxc_tracks_qy3/ac_fvtxc_tracks_qw);
  centrality_ac_fvtxc_tracks_cossum22->Fill(centrality,ac_fvtxc_tracks_cossum22);
  centrality_ac_fvtxc_tracks_sinsum22->Fill(centrality,ac_fvtxc_tracks_sinsum22);
  centrality_ac_fvtxc_tracks_cos23->Fill(centrality,ac_fvtxc_tracks_cos23);
  centrality_ac_fvtxc_tracks_sin23->Fill(centrality,ac_fvtxc_tracks_sin23);
  // --- scalar product
  centrality_ac_fvtxsfvtxn_tracks_c22->Fill(centrality,ac_fvtxsfvtxn_tracks_qq2);
  centrality_ac_fvtxsfvtxn_tracks_c32->Fill(centrality,ac_fvtxsfvtxn_tracks_qq3);
  // --- four particle
  centrality_ac_fvtxs_tracks_c24->Fill(centrality,ac_fvtxs_tracks_qqqq24);
  centrality_ac_fvtxn_tracks_c24->Fill(centrality,ac_fvtxn_tracks_qqqq24);
  centrality_ac_fvtxc_tracks_c24->Fill(centrality,ac_fvtxc_tracks_qqqq24);
  // --- six particle
  centrality_ac_fvtxs_tracks_c26->Fill(centrality,ac_fvtxs_tracks_six);
  centrality_ac_fvtxn_tracks_c26->Fill(centrality,ac_fvtxn_tracks_six);
  centrality_ac_fvtxc_tracks_c26->Fill(centrality,ac_fvtxc_tracks_six);

  // ------------------------------------------------------------------------------------- //
  // --- calculations and histograms designed to be used with/for q-vector recentering --- //
  // ------------------------------------------------------------------------------------- //


  nfvtxt_tracks_south_qx2->Fill(nfvtxt,fvtxs_tracks_qx2[0]/fvtxs_tracks_qw[0]);
  nfvtxt_tracks_south_qx3->Fill(nfvtxt,fvtxs_tracks_qx3[0]/fvtxs_tracks_qw[0]);
  nfvtxt_tracks_south_qx4->Fill(nfvtxt,fvtxs_tracks_qx4[0]/fvtxs_tracks_qw[0]);
  nfvtxt_tracks_south_qx6->Fill(nfvtxt,fvtxs_tracks_qx6[0]/fvtxs_tracks_qw[0]);
  nfvtxt_tracks_south_qy2->Fill(nfvtxt,fvtxs_tracks_qy2[0]/fvtxs_tracks_qw[0]);
  nfvtxt_tracks_south_qy3->Fill(nfvtxt,fvtxs_tracks_qy3[0]/fvtxs_tracks_qw[0]);
  nfvtxt_tracks_south_qy4->Fill(nfvtxt,fvtxs_tracks_qy4[0]/fvtxs_tracks_qw[0]);
  nfvtxt_tracks_south_qy6->Fill(nfvtxt,fvtxs_tracks_qy6[0]/fvtxs_tracks_qw[0]);

  nfvtxt_tracks_south_inner_qx2->Fill(nfvtxt,fvtxs_tracks_qx2[1]/fvtxs_tracks_qw[1]);
  nfvtxt_tracks_south_inner_qx3->Fill(nfvtxt,fvtxs_tracks_qx3[1]/fvtxs_tracks_qw[1]);
  nfvtxt_tracks_south_inner_qx4->Fill(nfvtxt,fvtxs_tracks_qx4[1]/fvtxs_tracks_qw[1]);
  nfvtxt_tracks_south_inner_qx6->Fill(nfvtxt,fvtxs_tracks_qx6[1]/fvtxs_tracks_qw[1]);
  nfvtxt_tracks_south_inner_qy2->Fill(nfvtxt,fvtxs_tracks_qy2[1]/fvtxs_tracks_qw[1]);
  nfvtxt_tracks_south_inner_qy3->Fill(nfvtxt,fvtxs_tracks_qy3[1]/fvtxs_tracks_qw[1]);
  nfvtxt_tracks_south_inner_qy4->Fill(nfvtxt,fvtxs_tracks_qy4[1]/fvtxs_tracks_qw[1]);
  nfvtxt_tracks_south_inner_qy6->Fill(nfvtxt,fvtxs_tracks_qy6[1]/fvtxs_tracks_qw[1]);

  nfvtxt_tracks_south_outer_qx2->Fill(nfvtxt,fvtxs_tracks_qx2[2]/fvtxs_tracks_qw[2]);
  nfvtxt_tracks_south_outer_qx3->Fill(nfvtxt,fvtxs_tracks_qx3[2]/fvtxs_tracks_qw[2]);
  nfvtxt_tracks_south_outer_qx4->Fill(nfvtxt,fvtxs_tracks_qx4[2]/fvtxs_tracks_qw[2]);
  nfvtxt_tracks_south_outer_qx6->Fill(nfvtxt,fvtxs_tracks_qx6[2]/fvtxs_tracks_qw[2]);
  nfvtxt_tracks_south_outer_qy2->Fill(nfvtxt,fvtxs_tracks_qy2[2]/fvtxs_tracks_qw[2]);
  nfvtxt_tracks_south_outer_qy3->Fill(nfvtxt,fvtxs_tracks_qy3[2]/fvtxs_tracks_qw[2]);
  nfvtxt_tracks_south_outer_qy4->Fill(nfvtxt,fvtxs_tracks_qy4[2]/fvtxs_tracks_qw[2]);
  nfvtxt_tracks_south_outer_qy6->Fill(nfvtxt,fvtxs_tracks_qy6[2]/fvtxs_tracks_qw[2]);

  nfvtxt_tracks_north_qx2->Fill(nfvtxt,fvtxn_tracks_qx2[0]/fvtxn_tracks_qw[0]);
  nfvtxt_tracks_north_qx3->Fill(nfvtxt,fvtxn_tracks_qx3[0]/fvtxn_tracks_qw[0]);
  nfvtxt_tracks_north_qx4->Fill(nfvtxt,fvtxn_tracks_qx4[0]/fvtxn_tracks_qw[0]);
  nfvtxt_tracks_north_qx6->Fill(nfvtxt,fvtxn_tracks_qx6[0]/fvtxn_tracks_qw[0]);
  nfvtxt_tracks_north_qy2->Fill(nfvtxt,fvtxn_tracks_qy2[0]/fvtxn_tracks_qw[0]);
  nfvtxt_tracks_north_qy3->Fill(nfvtxt,fvtxn_tracks_qy3[0]/fvtxn_tracks_qw[0]);
  nfvtxt_tracks_north_qy4->Fill(nfvtxt,fvtxn_tracks_qy4[0]/fvtxn_tracks_qw[0]);
  nfvtxt_tracks_north_qy6->Fill(nfvtxt,fvtxn_tracks_qy6[0]/fvtxn_tracks_qw[0]);

  nfvtxt_tracks_north_inner_qx2->Fill(nfvtxt,fvtxn_tracks_qx2[1]/fvtxn_tracks_qw[1]);
  nfvtxt_tracks_north_inner_qx3->Fill(nfvtxt,fvtxn_tracks_qx3[1]/fvtxn_tracks_qw[1]);
  nfvtxt_tracks_north_inner_qx4->Fill(nfvtxt,fvtxn_tracks_qx4[1]/fvtxn_tracks_qw[1]);
  nfvtxt_tracks_north_inner_qx6->Fill(nfvtxt,fvtxn_tracks_qx6[1]/fvtxn_tracks_qw[1]);
  nfvtxt_tracks_north_inner_qy2->Fill(nfvtxt,fvtxn_tracks_qy2[1]/fvtxn_tracks_qw[1]);
  nfvtxt_tracks_north_inner_qy3->Fill(nfvtxt,fvtxn_tracks_qy3[1]/fvtxn_tracks_qw[1]);
  nfvtxt_tracks_north_inner_qy4->Fill(nfvtxt,fvtxn_tracks_qy4[1]/fvtxn_tracks_qw[1]);
  nfvtxt_tracks_north_inner_qy6->Fill(nfvtxt,fvtxn_tracks_qy6[1]/fvtxn_tracks_qw[1]);

  nfvtxt_tracks_north_outer_qx2->Fill(nfvtxt,fvtxn_tracks_qx2[2]/fvtxn_tracks_qw[2]);
  nfvtxt_tracks_north_outer_qx3->Fill(nfvtxt,fvtxn_tracks_qx3[2]/fvtxn_tracks_qw[2]);
  nfvtxt_tracks_north_outer_qx4->Fill(nfvtxt,fvtxn_tracks_qx4[2]/fvtxn_tracks_qw[2]);
  nfvtxt_tracks_north_outer_qx6->Fill(nfvtxt,fvtxn_tracks_qx6[2]/fvtxn_tracks_qw[2]);
  nfvtxt_tracks_north_outer_qy2->Fill(nfvtxt,fvtxn_tracks_qy2[2]/fvtxn_tracks_qw[2]);
  nfvtxt_tracks_north_outer_qy3->Fill(nfvtxt,fvtxn_tracks_qy3[2]/fvtxn_tracks_qw[2]);
  nfvtxt_tracks_north_outer_qy4->Fill(nfvtxt,fvtxn_tracks_qy4[2]/fvtxn_tracks_qw[2]);
  nfvtxt_tracks_north_outer_qy6->Fill(nfvtxt,fvtxn_tracks_qy6[2]/fvtxn_tracks_qw[2]);

  // --- now centrality

  centrality_tracks_south_qx2->Fill(centrality,fvtxs_tracks_qx2[0]/fvtxs_tracks_qw[0]);
  centrality_tracks_south_qx3->Fill(centrality,fvtxs_tracks_qx3[0]/fvtxs_tracks_qw[0]);
  centrality_tracks_south_qx4->Fill(centrality,fvtxs_tracks_qx4[0]/fvtxs_tracks_qw[0]);
  centrality_tracks_south_qx6->Fill(centrality,fvtxs_tracks_qx6[0]/fvtxs_tracks_qw[0]);
  centrality_tracks_south_qy2->Fill(centrality,fvtxs_tracks_qy2[0]/fvtxs_tracks_qw[0]);
  centrality_tracks_south_qy3->Fill(centrality,fvtxs_tracks_qy3[0]/fvtxs_tracks_qw[0]);
  centrality_tracks_south_qy4->Fill(centrality,fvtxs_tracks_qy4[0]/fvtxs_tracks_qw[0]);
  centrality_tracks_south_qy6->Fill(centrality,fvtxs_tracks_qy6[0]/fvtxs_tracks_qw[0]);

  centrality_tracks_south_inner_qx2->Fill(centrality,fvtxs_tracks_qx2[1]/fvtxs_tracks_qw[1]);
  centrality_tracks_south_inner_qx3->Fill(centrality,fvtxs_tracks_qx3[1]/fvtxs_tracks_qw[1]);
  centrality_tracks_south_inner_qx4->Fill(centrality,fvtxs_tracks_qx4[1]/fvtxs_tracks_qw[1]);
  centrality_tracks_south_inner_qx6->Fill(centrality,fvtxs_tracks_qx6[1]/fvtxs_tracks_qw[1]);
  centrality_tracks_south_inner_qy2->Fill(centrality,fvtxs_tracks_qy2[1]/fvtxs_tracks_qw[1]);
  centrality_tracks_south_inner_qy3->Fill(centrality,fvtxs_tracks_qy3[1]/fvtxs_tracks_qw[1]);
  centrality_tracks_south_inner_qy4->Fill(centrality,fvtxs_tracks_qy4[1]/fvtxs_tracks_qw[1]);
  centrality_tracks_south_inner_qy6->Fill(centrality,fvtxs_tracks_qy6[1]/fvtxs_tracks_qw[1]);

  centrality_tracks_south_outer_qx2->Fill(centrality,fvtxs_tracks_qx2[2]/fvtxs_tracks_qw[2]);
  centrality_tracks_south_outer_qx3->Fill(centrality,fvtxs_tracks_qx3[2]/fvtxs_tracks_qw[2]);
  centrality_tracks_south_outer_qx4->Fill(centrality,fvtxs_tracks_qx4[2]/fvtxs_tracks_qw[2]);
  centrality_tracks_south_outer_qx6->Fill(centrality,fvtxs_tracks_qx6[2]/fvtxs_tracks_qw[2]);
  centrality_tracks_south_outer_qy2->Fill(centrality,fvtxs_tracks_qy2[2]/fvtxs_tracks_qw[2]);
  centrality_tracks_south_outer_qy3->Fill(centrality,fvtxs_tracks_qy3[2]/fvtxs_tracks_qw[2]);
  centrality_tracks_south_outer_qy4->Fill(centrality,fvtxs_tracks_qy4[2]/fvtxs_tracks_qw[2]);
  centrality_tracks_south_outer_qy6->Fill(centrality,fvtxs_tracks_qy6[2]/fvtxs_tracks_qw[2]);

  centrality_tracks_north_qx2->Fill(centrality,fvtxn_tracks_qx2[0]/fvtxn_tracks_qw[0]);
  centrality_tracks_north_qx3->Fill(centrality,fvtxn_tracks_qx3[0]/fvtxn_tracks_qw[0]);
  centrality_tracks_north_qx4->Fill(centrality,fvtxn_tracks_qx4[0]/fvtxn_tracks_qw[0]);
  centrality_tracks_north_qx6->Fill(centrality,fvtxn_tracks_qx6[0]/fvtxn_tracks_qw[0]);
  centrality_tracks_north_qy2->Fill(centrality,fvtxn_tracks_qy2[0]/fvtxn_tracks_qw[0]);
  centrality_tracks_north_qy3->Fill(centrality,fvtxn_tracks_qy3[0]/fvtxn_tracks_qw[0]);
  centrality_tracks_north_qy4->Fill(centrality,fvtxn_tracks_qy4[0]/fvtxn_tracks_qw[0]);
  centrality_tracks_north_qy6->Fill(centrality,fvtxn_tracks_qy6[0]/fvtxn_tracks_qw[0]);

  centrality_tracks_north_inner_qx2->Fill(centrality,fvtxn_tracks_qx2[1]/fvtxn_tracks_qw[1]);
  centrality_tracks_north_inner_qx3->Fill(centrality,fvtxn_tracks_qx3[1]/fvtxn_tracks_qw[1]);
  centrality_tracks_north_inner_qx4->Fill(centrality,fvtxn_tracks_qx4[1]/fvtxn_tracks_qw[1]);
  centrality_tracks_north_inner_qx6->Fill(centrality,fvtxn_tracks_qx6[1]/fvtxn_tracks_qw[1]);
  centrality_tracks_north_inner_qy2->Fill(centrality,fvtxn_tracks_qy2[1]/fvtxn_tracks_qw[1]);
  centrality_tracks_north_inner_qy3->Fill(centrality,fvtxn_tracks_qy3[1]/fvtxn_tracks_qw[1]);
  centrality_tracks_north_inner_qy4->Fill(centrality,fvtxn_tracks_qy4[1]/fvtxn_tracks_qw[1]);
  centrality_tracks_north_inner_qy6->Fill(centrality,fvtxn_tracks_qy6[1]/fvtxn_tracks_qw[1]);

  centrality_tracks_north_outer_qx2->Fill(centrality,fvtxn_tracks_qx2[2]/fvtxn_tracks_qw[2]);
  centrality_tracks_north_outer_qx3->Fill(centrality,fvtxn_tracks_qx3[2]/fvtxn_tracks_qw[2]);
  centrality_tracks_north_outer_qx4->Fill(centrality,fvtxn_tracks_qx4[2]/fvtxn_tracks_qw[2]);
  centrality_tracks_north_outer_qx6->Fill(centrality,fvtxn_tracks_qx6[2]/fvtxn_tracks_qw[2]);
  centrality_tracks_north_outer_qy2->Fill(centrality,fvtxn_tracks_qy2[2]/fvtxn_tracks_qw[2]);
  centrality_tracks_north_outer_qy3->Fill(centrality,fvtxn_tracks_qy3[2]/fvtxn_tracks_qw[2]);
  centrality_tracks_north_outer_qy4->Fill(centrality,fvtxn_tracks_qy4[2]/fvtxn_tracks_qw[2]);
  centrality_tracks_north_outer_qy6->Fill(centrality,fvtxn_tracks_qy6[2]/fvtxn_tracks_qw[2]);


  // ---
  // --- FVTX south
  float os_fvtxs_tracks_qw = fvtxs_tracks_qw[0];
  float os_fvtxs_tracks_qx2 = fvtxs_tracks_qx2[0] - offset_centrality_qx2_south[icent]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qy2 = fvtxs_tracks_qy2[0] - offset_centrality_qy2_south[icent]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qx3 = fvtxs_tracks_qx3[0];
  float os_fvtxs_tracks_qy3 = fvtxs_tracks_qy3[0];
  float os_fvtxs_tracks_qx4 = fvtxs_tracks_qx4[0] - offset_centrality_qx4_south[icent]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qy4 = fvtxs_tracks_qy4[0] - offset_centrality_qy4_south[icent]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qx6 = fvtxs_tracks_qx6[0] - offset_centrality_qx6_south[icent]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qy6 = fvtxs_tracks_qy6[0] - offset_centrality_qy6_south[icent]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qq2 = calc2_event(os_fvtxs_tracks_qx2,os_fvtxs_tracks_qy2,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_qq3 = calc2_event(os_fvtxs_tracks_qx3,os_fvtxs_tracks_qy3,os_fvtxs_tracks_qw);
  nfvtxt_os_fvtxs_tracks_c22->Fill(nfvtxt,os_fvtxs_tracks_qq2);
  nfvtxt_os_fvtxs_tracks_cos21->Fill(nfvtxt,os_fvtxs_tracks_qx2/os_fvtxs_tracks_qw);
  nfvtxt_os_fvtxs_tracks_sin21->Fill(nfvtxt,os_fvtxs_tracks_qy2/os_fvtxs_tracks_qw);
  nfvtxt_os_fvtxs_tracks_c32->Fill(nfvtxt,os_fvtxs_tracks_qq3);
  nfvtxt_os_fvtxs_tracks_cos31->Fill(nfvtxt,os_fvtxs_tracks_qx3/os_fvtxs_tracks_qw);
  nfvtxt_os_fvtxs_tracks_sin31->Fill(nfvtxt,os_fvtxs_tracks_qy3/os_fvtxs_tracks_qw);
  TComplex tc_os_fvtxs_tracks_Q2(os_fvtxs_tracks_qx2,os_fvtxs_tracks_qy2);
  TComplex tc_os_fvtxs_tracks_Q3(os_fvtxs_tracks_qx3,os_fvtxs_tracks_qy3);
  TComplex tc_os_fvtxs_tracks_Q4(os_fvtxs_tracks_qx4,os_fvtxs_tracks_qy4);
  TComplex tc_os_fvtxs_tracks_Q6(os_fvtxs_tracks_qx6,os_fvtxs_tracks_qy6);
  float os_fvtxs_tracks_cossum22 = calccossum2_event(tc_os_fvtxs_tracks_Q2,tc_os_fvtxs_tracks_Q4,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_sinsum22 = calcsinsum2_event(tc_os_fvtxs_tracks_Q2,tc_os_fvtxs_tracks_Q4,os_fvtxs_tracks_qw);
  nfvtxt_os_fvtxs_tracks_cossum22->Fill(nfvtxt,os_fvtxs_tracks_cossum22);
  nfvtxt_os_fvtxs_tracks_sinsum22->Fill(nfvtxt,os_fvtxs_tracks_sinsum22);
  float os_fvtxs_tracks_cossum32 = calccossum2_event(tc_os_fvtxs_tracks_Q3,tc_os_fvtxs_tracks_Q6,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_sinsum32 = calcsinsum2_event(tc_os_fvtxs_tracks_Q3,tc_os_fvtxs_tracks_Q6,os_fvtxs_tracks_qw);
  nfvtxt_os_fvtxs_tracks_cossum32->Fill(nfvtxt,os_fvtxs_tracks_cossum32);
  nfvtxt_os_fvtxs_tracks_sinsum32->Fill(nfvtxt,os_fvtxs_tracks_sinsum32);
  float os_fvtxs_tracks_cos23 = calccos3_event(tc_os_fvtxs_tracks_Q2,tc_os_fvtxs_tracks_Q4,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_sin23 = calcsin3_event(tc_os_fvtxs_tracks_Q2,tc_os_fvtxs_tracks_Q4,os_fvtxs_tracks_qw);
  nfvtxt_os_fvtxs_tracks_cos23->Fill(nfvtxt,os_fvtxs_tracks_cos23);
  nfvtxt_os_fvtxs_tracks_sin23->Fill(nfvtxt,os_fvtxs_tracks_sin23);
  float os_fvtxs_tracks_cos33 = calccos3_event(tc_os_fvtxs_tracks_Q3,tc_os_fvtxs_tracks_Q6,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_sin33 = calcsin3_event(tc_os_fvtxs_tracks_Q3,tc_os_fvtxs_tracks_Q6,os_fvtxs_tracks_qw);
  nfvtxt_os_fvtxs_tracks_cos33->Fill(nfvtxt,os_fvtxs_tracks_cos33);
  nfvtxt_os_fvtxs_tracks_sin33->Fill(nfvtxt,os_fvtxs_tracks_sin33);

  // --- FVTX north
  float os_fvtxn_tracks_qw = fvtxn_tracks_qw[0];
  float os_fvtxn_tracks_qx2 = fvtxn_tracks_qx2[0] - offset_centrality_qx2_north[icent]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qy2 = fvtxn_tracks_qy2[0] - offset_centrality_qy2_north[icent]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qx3 = fvtxn_tracks_qx3[0];
  float os_fvtxn_tracks_qy3 = fvtxn_tracks_qy3[0];
  float os_fvtxn_tracks_qx4 = fvtxn_tracks_qx4[0] - offset_centrality_qx4_north[icent]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qy4 = fvtxn_tracks_qy4[0] - offset_centrality_qy4_north[icent]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qx6 = fvtxn_tracks_qx6[0] - offset_centrality_qx6_north[icent]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qy6 = fvtxn_tracks_qy6[0] - offset_centrality_qy6_north[icent]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qq2 = calc2_event(os_fvtxn_tracks_qx2,os_fvtxn_tracks_qy2,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_qq3 = calc2_event(os_fvtxn_tracks_qx3,os_fvtxn_tracks_qy3,os_fvtxn_tracks_qw);
  nfvtxt_os_fvtxn_tracks_c22->Fill(nfvtxt,os_fvtxn_tracks_qq2);
  nfvtxt_os_fvtxn_tracks_cos21->Fill(nfvtxt,os_fvtxn_tracks_qx2/os_fvtxn_tracks_qw);
  nfvtxt_os_fvtxn_tracks_sin21->Fill(nfvtxt,os_fvtxn_tracks_qy2/os_fvtxn_tracks_qw);
  nfvtxt_os_fvtxn_tracks_c32->Fill(nfvtxt,os_fvtxn_tracks_qq3);
  nfvtxt_os_fvtxn_tracks_cos31->Fill(nfvtxt,os_fvtxn_tracks_qx3/os_fvtxn_tracks_qw);
  nfvtxt_os_fvtxn_tracks_sin31->Fill(nfvtxt,os_fvtxn_tracks_qy3/os_fvtxn_tracks_qw);
  TComplex tc_os_fvtxn_tracks_Q2(os_fvtxn_tracks_qx2,os_fvtxn_tracks_qy2);
  TComplex tc_os_fvtxn_tracks_Q3(os_fvtxn_tracks_qx3,os_fvtxn_tracks_qy3);
  TComplex tc_os_fvtxn_tracks_Q4(os_fvtxn_tracks_qx4,os_fvtxn_tracks_qy4);
  TComplex tc_os_fvtxn_tracks_Q6(os_fvtxn_tracks_qx6,os_fvtxn_tracks_qy6);
  float os_fvtxn_tracks_cossum22 = calccossum2_event(tc_os_fvtxn_tracks_Q2,tc_os_fvtxn_tracks_Q4,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_sinsum22 = calcsinsum2_event(tc_os_fvtxn_tracks_Q2,tc_os_fvtxn_tracks_Q4,os_fvtxn_tracks_qw);
  nfvtxt_os_fvtxn_tracks_cossum22->Fill(nfvtxt,os_fvtxn_tracks_cossum22);
  nfvtxt_os_fvtxn_tracks_sinsum22->Fill(nfvtxt,os_fvtxn_tracks_sinsum22);
  float os_fvtxn_tracks_cossum32 = calccossum2_event(tc_os_fvtxn_tracks_Q3,tc_os_fvtxn_tracks_Q6,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_sinsum32 = calcsinsum2_event(tc_os_fvtxn_tracks_Q3,tc_os_fvtxn_tracks_Q6,os_fvtxn_tracks_qw);
  nfvtxt_os_fvtxn_tracks_cossum32->Fill(nfvtxt,os_fvtxn_tracks_cossum32);
  nfvtxt_os_fvtxn_tracks_sinsum32->Fill(nfvtxt,os_fvtxn_tracks_sinsum32);
  float os_fvtxn_tracks_cos23 = calccos3_event(tc_os_fvtxn_tracks_Q2,tc_os_fvtxn_tracks_Q4,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_sin23 = calcsin3_event(tc_os_fvtxn_tracks_Q2,tc_os_fvtxn_tracks_Q4,os_fvtxn_tracks_qw);
  nfvtxt_os_fvtxn_tracks_cos23->Fill(nfvtxt,os_fvtxn_tracks_cos23);
  nfvtxt_os_fvtxn_tracks_sin23->Fill(nfvtxt,os_fvtxn_tracks_sin23);
  float os_fvtxn_tracks_cos33 = calccos3_event(tc_os_fvtxn_tracks_Q3,tc_os_fvtxn_tracks_Q6,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_sin33 = calcsin3_event(tc_os_fvtxn_tracks_Q3,tc_os_fvtxn_tracks_Q6,os_fvtxn_tracks_qw);
  nfvtxt_os_fvtxn_tracks_cos33->Fill(nfvtxt,os_fvtxn_tracks_cos33);
  nfvtxt_os_fvtxn_tracks_sin33->Fill(nfvtxt,os_fvtxn_tracks_sin33);

  // --- FVTX north and south combined
  float os_fvtxc_tracks_qx2 = os_fvtxs_tracks_qx2 + os_fvtxn_tracks_qx2;
  float os_fvtxc_tracks_qy2 = os_fvtxs_tracks_qy2 + os_fvtxn_tracks_qy2;
  float os_fvtxc_tracks_qx3 = os_fvtxs_tracks_qx3 + os_fvtxn_tracks_qx3;
  float os_fvtxc_tracks_qy3 = os_fvtxs_tracks_qy3 + os_fvtxn_tracks_qy3;
  float os_fvtxc_tracks_qx4 = os_fvtxs_tracks_qx4 + os_fvtxn_tracks_qx4;
  float os_fvtxc_tracks_qy4 = os_fvtxs_tracks_qy4 + os_fvtxn_tracks_qy4;
  float os_fvtxc_tracks_qx6 = os_fvtxs_tracks_qx6 + os_fvtxn_tracks_qx6;
  float os_fvtxc_tracks_qy6 = os_fvtxs_tracks_qy6 + os_fvtxn_tracks_qy6;
  float os_fvtxc_tracks_qw = os_fvtxs_tracks_qw + os_fvtxn_tracks_qw;
  float os_fvtxc_tracks_qq2 = calc2_event(os_fvtxc_tracks_qx2,os_fvtxc_tracks_qy2,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_qq3 = calc2_event(os_fvtxc_tracks_qx3,os_fvtxc_tracks_qy3,os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxc_tracks_c22->Fill(nfvtxt,os_fvtxc_tracks_qq2);
  nfvtxt_os_fvtxc_tracks_cos21->Fill(nfvtxt,os_fvtxc_tracks_qx2/os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxc_tracks_sin21->Fill(nfvtxt,os_fvtxc_tracks_qy2/os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxc_tracks_c32->Fill(nfvtxt,os_fvtxc_tracks_qq3);
  nfvtxt_os_fvtxc_tracks_cos31->Fill(nfvtxt,os_fvtxc_tracks_qx3/os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxc_tracks_sin31->Fill(nfvtxt,os_fvtxc_tracks_qy3/os_fvtxc_tracks_qw);
  TComplex tc_os_fvtxc_tracks_Q2(os_fvtxc_tracks_qx2,os_fvtxc_tracks_qy2);
  TComplex tc_os_fvtxc_tracks_Q3(os_fvtxc_tracks_qx4,os_fvtxc_tracks_qy3);
  TComplex tc_os_fvtxc_tracks_Q4(os_fvtxc_tracks_qx4,os_fvtxc_tracks_qy4);
  TComplex tc_os_fvtxc_tracks_Q6(os_fvtxc_tracks_qx6,os_fvtxc_tracks_qy6);
  float os_fvtxc_tracks_cossum22 = calccossum2_event(tc_os_fvtxc_tracks_Q2,tc_os_fvtxc_tracks_Q4,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_sinsum22 = calcsinsum2_event(tc_os_fvtxc_tracks_Q2,tc_os_fvtxc_tracks_Q4,os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxc_tracks_cossum22->Fill(nfvtxt,os_fvtxc_tracks_cossum22);
  nfvtxt_os_fvtxc_tracks_sinsum22->Fill(nfvtxt,os_fvtxc_tracks_sinsum22);
  float os_fvtxc_tracks_cossum32 = calccossum2_event(tc_os_fvtxc_tracks_Q3,tc_os_fvtxc_tracks_Q6,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_sinsum32 = calcsinsum2_event(tc_os_fvtxc_tracks_Q3,tc_os_fvtxc_tracks_Q6,os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxc_tracks_cossum32->Fill(nfvtxt,os_fvtxc_tracks_cossum32);
  nfvtxt_os_fvtxc_tracks_sinsum32->Fill(nfvtxt,os_fvtxc_tracks_sinsum32);
  float os_fvtxc_tracks_cos23 = calccos3_event(tc_os_fvtxc_tracks_Q2,tc_os_fvtxc_tracks_Q4,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_sin23 = calcsin3_event(tc_os_fvtxc_tracks_Q2,tc_os_fvtxc_tracks_Q4,os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxc_tracks_cos23->Fill(nfvtxt,os_fvtxc_tracks_cos23);
  nfvtxt_os_fvtxc_tracks_sin23->Fill(nfvtxt,os_fvtxc_tracks_sin23);
  float os_fvtxc_tracks_cos33 = calccos3_event(tc_os_fvtxc_tracks_Q3,tc_os_fvtxc_tracks_Q6,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_sin33 = calcsin3_event(tc_os_fvtxc_tracks_Q3,tc_os_fvtxc_tracks_Q6,os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxc_tracks_cos33->Fill(nfvtxt,os_fvtxc_tracks_cos33);
  nfvtxt_os_fvtxc_tracks_sin33->Fill(nfvtxt,os_fvtxc_tracks_sin33);

  // --- scalar product, fvtxs dot fvtxn
  float os_fvtxsfvtxn_tracks_qq2 = ( (os_fvtxs_tracks_qx2*os_fvtxn_tracks_qx2) + (os_fvtxs_tracks_qy2*os_fvtxn_tracks_qy2) ) / ( os_fvtxs_tracks_qw*os_fvtxn_tracks_qw );
  float os_fvtxsfvtxn_tracks_qq3 = ( (os_fvtxs_tracks_qx3*os_fvtxn_tracks_qx3) + (os_fvtxs_tracks_qy3*os_fvtxn_tracks_qy3) ) / ( os_fvtxs_tracks_qw*os_fvtxn_tracks_qw );
  nfvtxt_os_fvtxsfvtxn_tracks_c22->Fill(nfvtxt,os_fvtxsfvtxn_tracks_qq2);
  nfvtxt_os_fvtxsfvtxn_tracks_c32->Fill(nfvtxt,os_fvtxsfvtxn_tracks_qq3);

  // --- now have a look at some 4 particle cumulants
  // --- calc4_event has the protection/requirement on the minimum number of tracks
  float os_fvtxs_tracks_qqqq24 = calc4_event(os_fvtxs_tracks_qx2,os_fvtxs_tracks_qy2,os_fvtxs_tracks_qx4,os_fvtxs_tracks_qy4,os_fvtxs_tracks_qw);
  float os_fvtxn_tracks_qqqq24 = calc4_event(os_fvtxn_tracks_qx2,os_fvtxn_tracks_qy2,os_fvtxn_tracks_qx4,os_fvtxn_tracks_qy4,os_fvtxn_tracks_qw);
  float os_fvtxc_tracks_qqqq24 = calc4_event(os_fvtxc_tracks_qx2,os_fvtxc_tracks_qy2,os_fvtxc_tracks_qx4,os_fvtxc_tracks_qy4,os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxs_tracks_c24->Fill(nfvtxt,os_fvtxs_tracks_qqqq24);
  nfvtxt_os_fvtxn_tracks_c24->Fill(nfvtxt,os_fvtxn_tracks_qqqq24);
  nfvtxt_os_fvtxc_tracks_c24->Fill(nfvtxt,os_fvtxc_tracks_qqqq24);
  float os_fvtxs_tracks_qqqq34 = calc4_event(os_fvtxs_tracks_qx3,os_fvtxs_tracks_qy3,os_fvtxs_tracks_qx6,os_fvtxs_tracks_qy6,os_fvtxs_tracks_qw);
  float os_fvtxn_tracks_qqqq34 = calc4_event(os_fvtxn_tracks_qx3,os_fvtxn_tracks_qy3,os_fvtxn_tracks_qx6,os_fvtxn_tracks_qy6,os_fvtxn_tracks_qw);
  float os_fvtxc_tracks_qqqq34 = calc4_event(os_fvtxc_tracks_qx3,os_fvtxc_tracks_qy3,os_fvtxc_tracks_qx6,os_fvtxc_tracks_qy6,os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxs_tracks_c34->Fill(nfvtxt,os_fvtxs_tracks_qqqq34);
  nfvtxt_os_fvtxn_tracks_c34->Fill(nfvtxt,os_fvtxn_tracks_qqqq34);
  nfvtxt_os_fvtxc_tracks_c34->Fill(nfvtxt,os_fvtxc_tracks_qqqq34);

  float os_fvtxs_tracks_six = calc6_event(tc_os_fvtxs_tracks_Q2,tc_os_fvtxs_tracks_Q4,tc_os_fvtxs_tracks_Q6,os_fvtxs_tracks_qw);
  float os_fvtxn_tracks_six = calc6_event(tc_os_fvtxn_tracks_Q2,tc_os_fvtxn_tracks_Q4,tc_os_fvtxn_tracks_Q6,os_fvtxn_tracks_qw);
  float os_fvtxc_tracks_six = calc6_event(tc_os_fvtxc_tracks_Q2,tc_os_fvtxc_tracks_Q4,tc_os_fvtxc_tracks_Q6,os_fvtxc_tracks_qw);
  nfvtxt_os_fvtxs_tracks_c26->Fill(nfvtxt,os_fvtxs_tracks_six);
  nfvtxt_os_fvtxn_tracks_c26->Fill(nfvtxt,os_fvtxn_tracks_six);
  nfvtxt_os_fvtxc_tracks_c26->Fill(nfvtxt,os_fvtxc_tracks_six);

  // --------------------------------------------------------- //
  // --- centrality
  // --------------

  // --- south only
  centrality_os_fvtxs_tracks_c22->Fill(centrality,os_fvtxs_tracks_qq2);
  centrality_os_fvtxs_tracks_cos21->Fill(centrality,os_fvtxs_tracks_qx2/os_fvtxs_tracks_qw);
  centrality_os_fvtxs_tracks_sin21->Fill(centrality,os_fvtxs_tracks_qy2/os_fvtxs_tracks_qw);
  centrality_os_fvtxs_tracks_c32->Fill(centrality,os_fvtxs_tracks_qq3);
  centrality_os_fvtxs_tracks_cos31->Fill(centrality,os_fvtxs_tracks_qx3/os_fvtxs_tracks_qw);
  centrality_os_fvtxs_tracks_sin31->Fill(centrality,os_fvtxs_tracks_qy3/os_fvtxs_tracks_qw);
  centrality_os_fvtxs_tracks_cossum22->Fill(centrality,os_fvtxs_tracks_cossum22);
  centrality_os_fvtxs_tracks_sinsum22->Fill(centrality,os_fvtxs_tracks_sinsum22);
  centrality_os_fvtxs_tracks_cos23->Fill(centrality,os_fvtxs_tracks_cos23);
  centrality_os_fvtxs_tracks_sin23->Fill(centrality,os_fvtxs_tracks_sin23);
  // --- north only
  centrality_os_fvtxn_tracks_c22->Fill(centrality,os_fvtxn_tracks_qq2);
  centrality_os_fvtxn_tracks_cos21->Fill(centrality,os_fvtxn_tracks_qx2/os_fvtxn_tracks_qw);
  centrality_os_fvtxn_tracks_sin21->Fill(centrality,os_fvtxn_tracks_qy2/os_fvtxn_tracks_qw);
  centrality_os_fvtxn_tracks_c32->Fill(centrality,os_fvtxn_tracks_qq3);
  centrality_os_fvtxn_tracks_cos31->Fill(centrality,os_fvtxn_tracks_qx3/os_fvtxn_tracks_qw);
  centrality_os_fvtxn_tracks_sin31->Fill(centrality,os_fvtxn_tracks_qy3/os_fvtxn_tracks_qw);
  centrality_os_fvtxn_tracks_cossum22->Fill(centrality,os_fvtxn_tracks_cossum22);
  centrality_os_fvtxn_tracks_sinsum22->Fill(centrality,os_fvtxn_tracks_sinsum22);
  centrality_os_fvtxn_tracks_cos23->Fill(centrality,os_fvtxn_tracks_cos23);
  centrality_os_fvtxn_tracks_sin23->Fill(centrality,os_fvtxn_tracks_sin23);
  // --- combined
  centrality_os_fvtxc_tracks_c22->Fill(centrality,os_fvtxc_tracks_qq2);
  centrality_os_fvtxc_tracks_cos21->Fill(centrality,os_fvtxc_tracks_qx2/os_fvtxc_tracks_qw);
  centrality_os_fvtxc_tracks_sin21->Fill(centrality,os_fvtxc_tracks_qy2/os_fvtxc_tracks_qw);
  centrality_os_fvtxc_tracks_c32->Fill(centrality,os_fvtxc_tracks_qq3);
  centrality_os_fvtxc_tracks_cos31->Fill(centrality,os_fvtxc_tracks_qx3/os_fvtxc_tracks_qw);
  centrality_os_fvtxc_tracks_sin31->Fill(centrality,os_fvtxc_tracks_qy3/os_fvtxc_tracks_qw);
  centrality_os_fvtxc_tracks_cossum22->Fill(centrality,os_fvtxc_tracks_cossum22);
  centrality_os_fvtxc_tracks_sinsum22->Fill(centrality,os_fvtxc_tracks_sinsum22);
  centrality_os_fvtxc_tracks_cos23->Fill(centrality,os_fvtxc_tracks_cos23);
  centrality_os_fvtxc_tracks_sin23->Fill(centrality,os_fvtxc_tracks_sin23);
  // --- scalar product
  centrality_os_fvtxsfvtxn_tracks_c22->Fill(centrality,os_fvtxsfvtxn_tracks_qq2);
  centrality_os_fvtxsfvtxn_tracks_c32->Fill(centrality,os_fvtxsfvtxn_tracks_qq3);
  // --- four particle
  centrality_os_fvtxs_tracks_c24->Fill(centrality,os_fvtxs_tracks_qqqq24);
  centrality_os_fvtxn_tracks_c24->Fill(centrality,os_fvtxn_tracks_qqqq24);
  centrality_os_fvtxc_tracks_c24->Fill(centrality,os_fvtxc_tracks_qqqq24);
  // --- six particle
  centrality_os_fvtxs_tracks_c26->Fill(centrality,os_fvtxs_tracks_six);
  centrality_os_fvtxn_tracks_c26->Fill(centrality,os_fvtxn_tracks_six);
  centrality_os_fvtxc_tracks_c26->Fill(centrality,os_fvtxc_tracks_six);



  if ( _verbosity > 0 ) cout << "sucessfully processed this event, number of fvtx tracks is " << nfvtxt_raw << ", number of fvtx tracks passing cuts is " << nfvtxt << endl;

  if ( _create_ttree ) shorttree->Fill();

  ++tmp_evt;//to keep track of how many events pass event cuts
  return EVENT_OK;

} // end of process_event



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




bool BoulderCumulants::is_run_in_list(int runnumber)
{
  ifstream runlist;
  runlist.open(_runlist_filename.c_str());
  int run_num;
  while ( runlist >> run_num )
    if ( run_num == runnumber )
      return true;
  return false;
}

