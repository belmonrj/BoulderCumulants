#include <BoulderCumulants.h>

#include <iostream>
#include <fstream>



#include <TOAD.h>
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
#include <getClass.h>
#include <PHGlobal.h>
#include <EventHeader.h>
#include <TrigLvl1.h>
#include <VtxOut.h>
#include <PHPoint.h>
#include <RunHeader.h>
#include <TFvtxCompactTrkMap.h>
#include <TFvtxCompactCoordMap.h>
#include <dAuBES_utils.h>




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
  do_double_track_cut = false;
  _cut_zvtx = 10.0;
  _cut_chi2 = 5.0;
  _cut_nhit = 3;
  _cut_dca = 2.0;
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
  for ( int i = 0; i < nharm; ++i )
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
  th2d_nfvtxt_northsouth = NULL;
  th1d_centrality = NULL;
  th1d_centralityA = NULL;
  th2d_nfvtxt_bbcsum = NULL;
  th2d_nfvtxt_centrality = NULL;
  th2d_nfvtxt_centralityA = NULL;
  th2d_nfvtxt_bbcsumratio = NULL;
  th1d_track_deta = NULL;
  th1d_track_dphi = NULL;
  tp1f_track_detacutpass = NULL;
  // --- now third harmonic
  // --- end third harmonic
  centrality_ac_fvtxc_tracks_c22 = NULL;
  centrality_ac_fvtxc_tracks_c24 = NULL;
  centrality_ac_fvtxc_tracks_c26 = NULL;
  centrality_ac_fvtxc_tracks_c28 = NULL;
  centrality_ac_fvtxc_tracks_cos21 = NULL;
  centrality_ac_fvtxc_tracks_sin21 = NULL;
  centrality_ac_fvtxc_tracks_cossum22 = NULL;
  centrality_ac_fvtxc_tracks_sinsum22 = NULL;
  centrality_ac_fvtxc_tracks_cos23 = NULL;
  centrality_ac_fvtxc_tracks_sin23 = NULL;
  centrality_ac_fvtxc_tracks_c32 = NULL;
  centrality_ac_fvtxc_tracks_c34 = NULL;
  centrality_ac_fvtxc_tracks_cos31 = NULL;
  centrality_ac_fvtxc_tracks_sin31 = NULL;
  centrality_ac_fvtxc_tracks_cossum32 = NULL;
  centrality_ac_fvtxc_tracks_sinsum32 = NULL;
  centrality_ac_fvtxc_tracks_cos33 = NULL;
  centrality_ac_fvtxc_tracks_sin33 = NULL;
  // ---
  // --- now third harmonic
  // --- end third harmonic
  centrality_os_fvtxc_tracks_c22 = NULL;
  centrality_os_fvtxc_tracks_c24 = NULL;
  centrality_os_fvtxc_tracks_c26 = NULL;
  centrality_os_fvtxc_tracks_c28 = NULL;
  centrality_os_fvtxc_tracks_cos21 = NULL;
  centrality_os_fvtxc_tracks_sin21 = NULL;
  centrality_os_fvtxc_tracks_cossum22 = NULL;
  centrality_os_fvtxc_tracks_sinsum22 = NULL;
  centrality_os_fvtxc_tracks_cos23 = NULL;
  centrality_os_fvtxc_tracks_sin23 = NULL;
  centrality_os_fvtxc_tracks_c32 = NULL;
  centrality_os_fvtxc_tracks_cos31 = NULL;
  centrality_os_fvtxc_tracks_sin31 = NULL;

  for ( int i = 0; i < 8; ++i ) tp1f_special_fvtx_tracks_ab[i] = NULL;
  tp1f_special_fvtx_tracks_aa = NULL;
  tp1f_special_fvtx_tracks_aa_cos = NULL;
  tp1f_special_fvtx_tracks_aa_sin = NULL;

  for ( int cs = 0; cs < 2; ++cs )
    {
      for ( int c = 0; c < maxCorrelator; ++c )
        {
          nfvtxt_recursion[cs][c] = NULL;
          centrality_recursion[cs][c] = NULL;
        }
    }
  for ( int cs = 0; cs < 2; ++cs )
    {
      for ( int c = 0; c < maxHarmonic; ++c )
        {
          nfvtxt_recoffsets[cs][c] = NULL;
          nfvtxt_recoffsets_north[cs][c] = NULL;
          nfvtxt_recoffsets_south[cs][c] = NULL;
          centrality_recoffsets[cs][c] = NULL;
          centrality_recoffsets_north[cs][c] = NULL;
          centrality_recoffsets_south[cs][c] = NULL;
        }
    }

  for ( int i = 0; i < maxTracks; ++i )
    {
      for ( int cs = 0; cs < 2; ++cs )
        {
          for ( int c = 0; c < maxHarmonic; ++c )
            {
              qvoff_nfvtxt[i][cs][c] = 0;
              qvoff_nfvtxt_north[i][cs][c] = 0;
              qvoff_nfvtxt_south[i][cs][c] = 0;
            }
        }
    }

  for ( int i = 0; i < 100; ++i )
    {
      for ( int cs = 0; cs < 2; ++cs )
        {
          for ( int c = 0; c < maxHarmonic; ++c )
            {
              qvoff_cent[i][cs][c] = 0;
              qvoff_cent_north[i][cs][c] = 0;
              qvoff_cent_south[i][cs][c] = 0;
            }
        }
    }

} // end of class constructor


// --- class destructor
BoulderCumulants::~BoulderCumulants()
{
  //if ( _utils ) delete _utils;
}



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

  if ( !use_utils && fabs(bbc_z) > _cut_zvtx ) return EVENT_OK;

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



  // --- for the generic formulas ---------
  for(int h=0;h<maxHarmonic;h++)
    {
      for(int p=0;p<maxPower;p++)
        {
          Qvector[h][p] = TComplex(0.,0.);
          Qvector_north[h][p] = TComplex(0.,0.);
          Qvector_south[h][p] = TComplex(0.,0.);
          Qoffset[h][p] = TComplex(0.,0.);
          Qoffset_north[h][p] = TComplex(0.,0.);
          Qoffset_south[h][p] = TComplex(0.,0.);
        } //  for(int p=0;p<maxPower;p++)
    } // for(int h=0;h<maxHarmonic;h++)
  // --------------------------------------



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
  for ( int i = 0; i < nharm; ++i )
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

  vector<double> fphi;
  vector<double> feta;
  vector<double> fdcax;
  vector<double> fdcay;
  vector<double> fchi2ndf;
  vector<int> fnhitspc;

  if ( _verbosity > 1 ) cout << "entering fvtx track loop" << endl;
  TFvtxCompactTrkMap::const_iterator trk_iter = trkfvtx_map->range();
  while ( TFvtxCompactTrkMap::const_pointer trk_ptr = trk_iter.next() )
    {
      TFvtxCompactTrk* fvtx_trk = trk_ptr->get();
      bool pattern0 = ((fvtx_trk->get_hit_pattern() & 0x3) > 0);
      bool pattern2 = ((fvtx_trk->get_hit_pattern() & (0x3 << 2)) > 0 );
      bool pattern4 = ((fvtx_trk->get_hit_pattern() & (0x3 << 4)) > 0 );
      bool pattern6 = ((fvtx_trk->get_hit_pattern() & (0x3 << 6)) > 0 );
      int nhits_special = pattern0 + pattern2 + pattern4 + pattern6;

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

      // cout << "----------------------------------------------------" << endl;
      // cout << "pattern " << (int)fvtx_trk->get_hit_pattern() << endl;
      // cout << "part0 " << (fvtx_trk->get_hit_pattern() & 0x3) << endl;
      // cout << "part2 " << (fvtx_trk->get_hit_pattern() & (0x3 << 2)) << endl;
      // cout << "part4 " << (fvtx_trk->get_hit_pattern() & (0x3 << 4)) << endl;
      // cout << "part6 " << (fvtx_trk->get_hit_pattern() & (0x3 << 6)) << endl;
      // cout << "nhits_special " << nhits_special << endl;
      // cout << "nhits " << nhits << endl;
      // cout << "----------------------------------------------------" << endl;

      if ( nhits_special < default_cut_nhit ) continue; // need at least 3 hits in FVTX, excluding VTX

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
          if ( fabs(DCA_x) > default_cut_dca || fabs(DCA_y) > default_cut_dca ) continue;
          if ( nhits < default_cut_nhit ) continue;
          if ( chisq > default_cut_chi2 ) continue;
        }
      // --- done with first loop, so push the eta and phi and count total number of good tracks
      fphi.push_back(phi);
      feta.push_back(eta);
      fdcax.push_back(DCA_x);
      fdcay.push_back(DCA_y);
      fchi2ndf.push_back(chisq);
      fnhitspc.push_back(nhits_special);
      ++nfvtxt;
      if ( eta < 0 ) ++nfvtxt_south;
      if ( eta > 0 ) ++nfvtxt_north;
    } // end first for loop over tracks

  if ( nfvtxt > maxTracks ) return EVENT_OK;

  // --- second fvtx track loop to get the double track cut
  bool fvtx_track_passes[nfvtxt];
  int number_of_tracks_that_pass = 0;
  if ( do_double_track_cut )
    {
      for ( int i = 0; i < nfvtxt; ++i )
        {
          fvtx_track_passes[i] = true;
        }
      for ( int i = 0; i < nfvtxt; ++i )
        {
          for ( int j = i+1; j < nfvtxt; ++j )
            {
              double eta1 = feta[i];
              double eta2 = feta[j];
              double phi1 = fphi[i];
              double phi2 = fphi[j];
              th1d_track_deta->Fill(eta1-eta2);
              if ( fabs(eta1-eta2) < 0.0002 )
                {
                  th1d_track_dphi->Fill(phi1-phi2);
                  fvtx_track_passes[i] = false;
                  fvtx_track_passes[j] = false;
                } // check on narrow eta
            } // inner loop
          if ( fvtx_track_passes[i] == true ) ++number_of_tracks_that_pass;
        } // outer loop
    } // check on do_double_track_cut
  double passratio = (double)number_of_tracks_that_pass/(double)nfvtxt;
  tp1f_track_detacutpass->Fill(centrality,passratio);
  if ( _verbosity > 1 )
    {
      cout << "number of tracks that pass " << number_of_tracks_that_pass
           << " total number of tracks " << nfvtxt
           << " ratio " << passratio << endl;
    }

  // --- third fvtxt track loop to calculate Q-vectors
  for ( int i = 0; i < nfvtxt; ++i )
    {
      // --- double track cut
      if ( do_double_track_cut && !fvtx_track_passes[i] ) continue;
      double eta = feta[i];
      double phi = fphi[i];
      double DCA_x = fdcax[i];
      double DCA_y = fdcay[i];
      double chisq = fchi2ndf[i];
      int nhits_special = fnhitspc[i];
      // --- need to do different cuts here
      if ( nhits_special < _cut_nhit ) continue; // need at least 3 hits in FVTX, excluding VTX
      if ( fabs(DCA_x) > _cut_dca || fabs(DCA_y) > _cut_dca ) continue;
      //if ( nhits < _cut_nhit ) continue;
      if ( chisq > _cut_chi2 ) continue;
      // --- from generic formulas ----------------------------------------------------------------------
      double dPhi = 0.0; // particle angle
      //double wPhi = 1.0; // particle weight
      double wPhiToPowerP = 1.0; // particle weight raised to power p
      dPhi = phi; // minimal change from me to match the generic forumlas code
      for(int h=0;h<maxHarmonic;h++)
        {
          for(int p=0;p<maxPower;p++)
            {
              //if(bUseWeights){wPhiToPowerP = pow(wPhi,p);} // no weights for us...
              Qvector[h][p] += TComplex(wPhiToPowerP*TMath::Cos(h*dPhi),wPhiToPowerP*TMath::Sin(h*dPhi));
              if ( eta > 0 ) Qvector_north[h][p] += TComplex(wPhiToPowerP*TMath::Cos(h*dPhi),wPhiToPowerP*TMath::Sin(h*dPhi));
              if ( eta < 0 ) Qvector_south[h][p] += TComplex(wPhiToPowerP*TMath::Cos(h*dPhi),wPhiToPowerP*TMath::Sin(h*dPhi));
            } //  for(int p=0;p<maxPower;p++)
        } // for(int h=0;h<maxHarmonic;h++)
      // ------------------------------------------------------------------------------------------------
      // --- Q-vectors for tree
      if ( eta > 0 )
        {
          for ( int i = 0; i < nharm; ++i )
            {
              d_NorthQX[i] += cos(i*phi);
              d_NorthQY[i] += sin(i*phi);
            }
          d_NorthQW += 1;
        }
      if ( eta < 0 )
        {
          for ( int i = 0; i < nharm; ++i )
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
    } // end third for loop over tracks



  // -------------------------------------------------------------------------------------------------------------------------------
  for(int h=1;h<maxHarmonic;h++) // ABSOLUTELY MUST START AT 1!!!  RECURSION ALGORITHM USES ZEROTH COMPONENT TO GET COMBINATORICS!!!
    {
      for(int p=0;p<maxPower;p++)
        {
          // --- combined subtraction does not work well...
          // Qoffset[h][p] = TComplex( Qvector[0][1].Re()*qvoff_nfvtxt[nfvtxt][0][h], Qvector[0][1].Re()*qvoff_nfvtxt[nfvtxt][1][h] );
          // Qvector[h][p] -= Qoffset[h][p];
          // --- north
          Qoffset_north[h][p] = TComplex( Qvector_north[0][1].Re()*qvoff_cent_north[icent][0][h], Qvector_north[0][1].Re()*qvoff_cent_north[icent][1][h] );
          Qvector_north[h][p] -= Qoffset_north[h][p];
          // --- south
          Qoffset_south[h][p] = TComplex( Qvector_south[0][1].Re()*qvoff_cent_south[icent][0][h], Qvector_south[0][1].Re()*qvoff_cent_south[icent][1][h] );
          Qvector_south[h][p] -= Qoffset_south[h][p];
          // --- add up north and south to get combined that's been recentered arm-by-arm
          Qvector[h][p] = Qvector_north[h][p] + Qvector_south[h][p];
        } // for(int p=0;p<maxPower;p++)
    } // for(int h=0;h<maxHarmonic;h++)
  // -------------------------------------------------------------------------------------------------------------------------------

  th1d_nfvtxt_combinedER->Fill(nfvtxt);
  th1d_nfvtxt_combined->Fill(nfvtxt);
  th1d_nfvtxt_north->Fill(nfvtxt_north);
  th1d_nfvtxt_south->Fill(nfvtxt_south);
  th2d_nfvtxt_northsouth->Fill(nfvtxt_north,nfvtxt_south);

  th1d_centrality->Fill(centrality);
  th2d_nfvtxt_bbcsum->Fill(nfvtxt,bbc_charge_sum);
  th2d_nfvtxt_centrality->Fill(nfvtxt,centrality);
  th2d_nfvtxt_bbcsumratio->Fill(nfvtxt,bbc_charge_sum/(float)nfvtxt);

  bool passes = PassesTracksChargeRatio(nfvtxt,bbc_charge_sum);
  if ( _collsys == "Run14AuAu200" && !passes )
    {
      if ( _verbosity > 1 ) cout << "Making special event cut for " << _collsys << endl;
      return EVENT_OK; // now testing revised cut...
    }
  th2d_nfvtxt_centralityA->Fill(nfvtxt,centrality);
  th1d_centralityA->Fill(centrality);

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
  TComplex tc_ac_fvtxs_tracks_Q2(ac_fvtxs_tracks_qx2,ac_fvtxs_tracks_qy2);
  TComplex tc_ac_fvtxs_tracks_Q3(ac_fvtxs_tracks_qx3,ac_fvtxs_tracks_qy3);
  TComplex tc_ac_fvtxs_tracks_Q4(ac_fvtxs_tracks_qx4,ac_fvtxs_tracks_qy4);
  TComplex tc_ac_fvtxs_tracks_Q6(ac_fvtxs_tracks_qx6,ac_fvtxs_tracks_qy6);
  float ac_fvtxs_tracks_cossum22 = calccossum2_event(tc_ac_fvtxs_tracks_Q2,tc_ac_fvtxs_tracks_Q4,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_sinsum22 = calcsinsum2_event(tc_ac_fvtxs_tracks_Q2,tc_ac_fvtxs_tracks_Q4,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_cossum32 = calccossum2_event(tc_ac_fvtxs_tracks_Q3,tc_ac_fvtxs_tracks_Q6,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_sinsum32 = calcsinsum2_event(tc_ac_fvtxs_tracks_Q3,tc_ac_fvtxs_tracks_Q6,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_cos23 = calccos3_event(tc_ac_fvtxs_tracks_Q2,tc_ac_fvtxs_tracks_Q4,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_sin23 = calcsin3_event(tc_ac_fvtxs_tracks_Q2,tc_ac_fvtxs_tracks_Q4,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_cos33 = calccos3_event(tc_ac_fvtxs_tracks_Q3,tc_ac_fvtxs_tracks_Q6,ac_fvtxs_tracks_qw);
  float ac_fvtxs_tracks_sin33 = calcsin3_event(tc_ac_fvtxs_tracks_Q3,tc_ac_fvtxs_tracks_Q6,ac_fvtxs_tracks_qw);

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
  TComplex tc_ac_fvtxn_tracks_Q2(ac_fvtxn_tracks_qx2,ac_fvtxn_tracks_qy2);
  TComplex tc_ac_fvtxn_tracks_Q3(ac_fvtxn_tracks_qx3,ac_fvtxn_tracks_qy3);
  TComplex tc_ac_fvtxn_tracks_Q4(ac_fvtxn_tracks_qx4,ac_fvtxn_tracks_qy4);
  TComplex tc_ac_fvtxn_tracks_Q6(ac_fvtxn_tracks_qx6,ac_fvtxn_tracks_qy6);
  float ac_fvtxn_tracks_cossum22 = calccossum2_event(tc_ac_fvtxn_tracks_Q2,tc_ac_fvtxn_tracks_Q4,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_sinsum22 = calcsinsum2_event(tc_ac_fvtxn_tracks_Q2,tc_ac_fvtxn_tracks_Q4,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_cossum32 = calccossum2_event(tc_ac_fvtxn_tracks_Q3,tc_ac_fvtxn_tracks_Q6,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_sinsum32 = calcsinsum2_event(tc_ac_fvtxn_tracks_Q3,tc_ac_fvtxn_tracks_Q6,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_cos23 = calccos3_event(tc_ac_fvtxn_tracks_Q2,tc_ac_fvtxn_tracks_Q4,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_sin23 = calcsin3_event(tc_ac_fvtxn_tracks_Q2,tc_ac_fvtxn_tracks_Q4,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_cos33 = calccos3_event(tc_ac_fvtxn_tracks_Q3,tc_ac_fvtxn_tracks_Q6,ac_fvtxn_tracks_qw);
  float ac_fvtxn_tracks_sin33 = calcsin3_event(tc_ac_fvtxn_tracks_Q3,tc_ac_fvtxn_tracks_Q6,ac_fvtxn_tracks_qw);

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
  TComplex tc_ac_fvtxc_tracks_Q2(ac_fvtxc_tracks_qx2,ac_fvtxc_tracks_qy2);
  TComplex tc_ac_fvtxc_tracks_Q3(ac_fvtxc_tracks_qx3,ac_fvtxc_tracks_qy3);
  TComplex tc_ac_fvtxc_tracks_Q4(ac_fvtxc_tracks_qx4,ac_fvtxc_tracks_qy4);
  TComplex tc_ac_fvtxc_tracks_Q6(ac_fvtxc_tracks_qx6,ac_fvtxc_tracks_qy6);
  float ac_fvtxc_tracks_cossum22 = calccossum2_event(tc_ac_fvtxc_tracks_Q2,tc_ac_fvtxc_tracks_Q4,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_sinsum22 = calcsinsum2_event(tc_ac_fvtxc_tracks_Q2,tc_ac_fvtxc_tracks_Q4,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_cossum32 = calccossum2_event(tc_ac_fvtxc_tracks_Q3,tc_ac_fvtxc_tracks_Q6,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_sinsum32 = calcsinsum2_event(tc_ac_fvtxc_tracks_Q3,tc_ac_fvtxc_tracks_Q6,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_cos23 = calccos3_event(tc_ac_fvtxc_tracks_Q2,tc_ac_fvtxc_tracks_Q4,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_sin23 = calcsin3_event(tc_ac_fvtxc_tracks_Q2,tc_ac_fvtxc_tracks_Q4,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_cos33 = calccos3_event(tc_ac_fvtxc_tracks_Q3,tc_ac_fvtxc_tracks_Q6,ac_fvtxc_tracks_qw);
  float ac_fvtxc_tracks_sin33 = calcsin3_event(tc_ac_fvtxc_tracks_Q3,tc_ac_fvtxc_tracks_Q6,ac_fvtxc_tracks_qw);

  // --- scalar product, fvtxs dot fvtxn
  float ac_fvtxsfvtxn_tracks_qq2 = ( (ac_fvtxs_tracks_qx2*ac_fvtxn_tracks_qx2) + (ac_fvtxs_tracks_qy2*ac_fvtxn_tracks_qy2) ) / ( ac_fvtxs_tracks_qw*ac_fvtxn_tracks_qw );
  float ac_fvtxsfvtxn_tracks_qq3 = ( (ac_fvtxs_tracks_qx3*ac_fvtxn_tracks_qx3) + (ac_fvtxs_tracks_qy3*ac_fvtxn_tracks_qy3) ) / ( ac_fvtxs_tracks_qw*ac_fvtxn_tracks_qw );

  // --- now have a look at some 4 particle cumulants
  // --- calc4_event has the protection/requirement on the minimum number of tracks
  float ac_fvtxs_tracks_qqqq24 = calc4_event(ac_fvtxs_tracks_qx2,ac_fvtxs_tracks_qy2,ac_fvtxs_tracks_qx4,ac_fvtxs_tracks_qy4,ac_fvtxs_tracks_qw);
  float ac_fvtxn_tracks_qqqq24 = calc4_event(ac_fvtxn_tracks_qx2,ac_fvtxn_tracks_qy2,ac_fvtxn_tracks_qx4,ac_fvtxn_tracks_qy4,ac_fvtxn_tracks_qw);
  float ac_fvtxc_tracks_qqqq24 = calc4_event(ac_fvtxc_tracks_qx2,ac_fvtxc_tracks_qy2,ac_fvtxc_tracks_qx4,ac_fvtxc_tracks_qy4,ac_fvtxc_tracks_qw);
  // --- four particle 2sub
  TComplex tca2 = TComplex(ac_fvtxs_tracks_qx2,ac_fvtxs_tracks_qy2);
  TComplex tcb2 = TComplex(ac_fvtxn_tracks_qx2,ac_fvtxn_tracks_qy2);
  TComplex tca4 = TComplex(ac_fvtxs_tracks_qx4,ac_fvtxs_tracks_qy4);
  TComplex tcb4 = TComplex(ac_fvtxn_tracks_qx4,ac_fvtxn_tracks_qy4);
  TComplex tc_numerator_a = tca2*tca2 - tca4;
  TComplex tc_numerator_b = TComplex::Conjugate(tcb2*tcb2 - tcb4);
  TComplex tc_numerator = tc_numerator_a*tc_numerator_b;
  double numerator = tc_numerator.Re();
  double tcaw = ac_fvtxs_tracks_qw*ac_fvtxs_tracks_qw - ac_fvtxs_tracks_qw;
  double tcbw = ac_fvtxn_tracks_qw*ac_fvtxn_tracks_qw - ac_fvtxn_tracks_qw;
  double denominator = tcaw*tcbw;
  double answer_c24a = numerator/denominator;

  float ac_fvtxs_tracks_qqqq34 = calc4_event(ac_fvtxs_tracks_qx3,ac_fvtxs_tracks_qy3,ac_fvtxs_tracks_qx6,ac_fvtxs_tracks_qy6,ac_fvtxs_tracks_qw);
  float ac_fvtxn_tracks_qqqq34 = calc4_event(ac_fvtxn_tracks_qx3,ac_fvtxn_tracks_qy3,ac_fvtxn_tracks_qx6,ac_fvtxn_tracks_qy6,ac_fvtxn_tracks_qw);
  float ac_fvtxc_tracks_qqqq34 = calc4_event(ac_fvtxc_tracks_qx3,ac_fvtxc_tracks_qy3,ac_fvtxc_tracks_qx6,ac_fvtxc_tracks_qy6,ac_fvtxc_tracks_qw);

  float ac_fvtxs_tracks_six = calc6_event(tc_ac_fvtxs_tracks_Q2,tc_ac_fvtxs_tracks_Q4,tc_ac_fvtxs_tracks_Q6,ac_fvtxs_tracks_qw);
  float ac_fvtxn_tracks_six = calc6_event(tc_ac_fvtxn_tracks_Q2,tc_ac_fvtxn_tracks_Q4,tc_ac_fvtxn_tracks_Q6,ac_fvtxn_tracks_qw);
  float ac_fvtxc_tracks_six = calc6_event(tc_ac_fvtxc_tracks_Q2,tc_ac_fvtxc_tracks_Q4,tc_ac_fvtxc_tracks_Q6,ac_fvtxc_tracks_qw);

  // --- from generic formulas ----------------------------------------------------------------------------
  // --- need to add these here, initialization in header file doesn't seem to work...
  //  2-p correlations:
  //cout<<" => Calculating 2-p correlations (using recursion)...       \r"<<flush;
  int harmonics_Two_Num[2] = {2,-2}; // 2, -2
  int harmonics_Two_Den[2] = {0,0}; // recursion gives right combinatorics
  TComplex twoRecursion = Recursion(2,harmonics_Two_Num)/Recursion(2,harmonics_Two_Den).Re();
  //double wTwoRecursion = Recursion(2,harmonics_Two_Den).Re();
  double wTwoRecursion = 1.0;
  nfvtxt_recursion[0][0]->Fill(nfvtxt,twoRecursion.Re(),wTwoRecursion); // <<cos(h1*phi1+h2*phi2)>>
  nfvtxt_recursion[1][0]->Fill(nfvtxt,twoRecursion.Im(),wTwoRecursion); // <<sin(h1*phi1+h2*phi2)>>
  //  4-p correlations:
  //cout<<" => Calculating 4-p correlations (using recursion)...       \r"<<flush;
  int harmonics_Four_Num[4] = {2,2,-2,-2};
  int harmonics_Four_Den[4] = {0,0,0,0}; // recursion gives right combinatorics
  TComplex fourRecursion = Recursion(4,harmonics_Four_Num)/Recursion(4,harmonics_Four_Den).Re();
  //double wFourRecursion = Recursion(4,harmonics_Four_Den).Re();
  double wFourRecursion = 1.0;
  nfvtxt_recursion[0][2]->Fill(nfvtxt,fourRecursion.Re(),wFourRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>
  nfvtxt_recursion[1][2]->Fill(nfvtxt,fourRecursion.Im(),wFourRecursion); // <<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>
  //  6-p correlations:
  //cout<<" => Calculating 6-p correlations (using recursion)...       \r"<<flush;
  int harmonics_Six_Num[6] = {2,2,2,-2,-2,-2};
  int harmonics_Six_Den[6] = {0,0,0,0,0,0};
  TComplex sixRecursion = Recursion(6,harmonics_Six_Num)/Recursion(6,harmonics_Six_Den).Re();
  //double wSixRecursion = Recursion(6,harmonics_Six_Den).Re();
  double wSixRecursion = 1.0;
  nfvtxt_recursion[0][4]->Fill(nfvtxt,sixRecursion.Re(),wSixRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>>
  nfvtxt_recursion[1][4]->Fill(nfvtxt,sixRecursion.Im(),wSixRecursion); // <<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>>
  //  8-p correlations:
  //cout<<" => Calculating 8-p correlations (using recursion)...       \r"<<flush;
  int harmonics_Eight_Num[8] = {2,2,2,2,-2,-2,-2,-2};
  int harmonics_Eight_Den[8] = {0,0,0,0,0,0,0,0};
  TComplex eightRecursion = Recursion(8,harmonics_Eight_Num)/Recursion(8,harmonics_Eight_Den).Re();
  //double wEightRecursion = Recursion(8,harmonics_Eight_Den).Re();
  double wEightRecursion = 1.0;
  nfvtxt_recursion[0][6]->Fill(nfvtxt,eightRecursion.Re(),wEightRecursion);
  nfvtxt_recursion[1][6]->Fill(nfvtxt,eightRecursion.Im(),wEightRecursion);
  // --- now some stuff for the third harmonic
  // --- v3{2}
  int harmonics_Twov3_Num[2] = {3,-3};
  int harmonics_Twov3_Den[2] = {0,0};
  TComplex twov3Recursion = Recursion(2,harmonics_Twov3_Num)/Recursion(2,harmonics_Twov3_Den).Re();
  double wTwov3Recursion = 1.0;
  nfvtxt_recursion[0][1]->Fill(nfvtxt,twov3Recursion.Re(),wTwov3Recursion);
  nfvtxt_recursion[1][1]->Fill(nfvtxt,twov3Recursion.Im(),wTwov3Recursion);
  // --- v3{4}
  int harmonics_Fourv3_Num[4] = {3,3,-3,-3};
  int harmonics_Fourv3_Den[4] = {0,0,0,0};
  TComplex fourv3Recursion = Recursion(4,harmonics_Fourv3_Num)/Recursion(4,harmonics_Fourv3_Den).Re();
  double wFourv3Recursion = 1.0;
  nfvtxt_recursion[0][3]->Fill(nfvtxt,fourv3Recursion.Re(),wFourv3Recursion);
  nfvtxt_recursion[1][3]->Fill(nfvtxt,fourv3Recursion.Im(),wFourv3Recursion);
  // --- v3{6}
  int harmonics_Sixv3_Num[6] = {3,3,3,-3,-3,-3};
  int harmonics_Sixv3_Den[6] = {0,0,0,0,0,0};
  TComplex sixv3Recursion = Recursion(6,harmonics_Sixv3_Num)/Recursion(6,harmonics_Sixv3_Den).Re();
  double wSixv3Recursion = 1.0;
  nfvtxt_recursion[0][5]->Fill(nfvtxt,sixv3Recursion.Re(),wSixv3Recursion);
  nfvtxt_recursion[1][5]->Fill(nfvtxt,sixv3Recursion.Im(),wSixv3Recursion);
  // --- now some stuff for the fourth harmonic
  // --- v4{2}
  int harmonics_Twov4_Num[2] = {4,-4};
  int harmonics_Twov4_Den[2] = {0,0};
  TComplex twov4Recursion = Recursion(2,harmonics_Twov4_Num)/Recursion(2,harmonics_Twov4_Den).Re();
  double wTwov4Recursion = 1.0;
  nfvtxt_recursion[0][7]->Fill(nfvtxt,twov4Recursion.Re(),wTwov4Recursion);
  nfvtxt_recursion[1][7]->Fill(nfvtxt,twov4Recursion.Im(),wTwov4Recursion);
  // --- v4{4}
  int harmonics_Fourv4_Num[4] = {4,4,-4,-4};
  int harmonics_Fourv4_Den[4] = {0,0,0,0};
  TComplex fourv4Recursion = Recursion(4,harmonics_Fourv4_Num)/Recursion(4,harmonics_Fourv4_Den).Re();
  double wFourv4Recursion = 1.0;
  nfvtxt_recursion[0][9]->Fill(nfvtxt,fourv4Recursion.Re(),wFourv4Recursion);
  nfvtxt_recursion[1][9]->Fill(nfvtxt,fourv4Recursion.Im(),wFourv4Recursion);
  // --- now some symmetric cumulants
  // --- SC(2,3)
  int harmonics_FourSC23_Num[4] = {2,3,-2,-3};
  int harmonics_FourSC23_Den[4] = {0,0,0,0};
  TComplex fourSC23Recursion = Recursion(4,harmonics_FourSC23_Num)/Recursion(4,harmonics_FourSC23_Den).Re();
  double wFourSC23Recursion = 1.0;
  nfvtxt_recursion[0][10]->Fill(nfvtxt,fourSC23Recursion.Re(),wFourSC23Recursion);
  nfvtxt_recursion[1][10]->Fill(nfvtxt,fourSC23Recursion.Im(),wFourSC23Recursion);
  // --- SC(2,4)
  int harmonics_FourSC24_Num[4] = {2,4,-2,-4};
  int harmonics_FourSC24_Den[4] = {0,0,0,0};
  TComplex fourSC24Recursion = Recursion(4,harmonics_FourSC24_Num)/Recursion(4,harmonics_FourSC24_Den).Re();
  double wFourSC24Recursion = 1.0;
  nfvtxt_recursion[0][11]->Fill(nfvtxt,fourSC24Recursion.Re(),wFourSC24Recursion);
  nfvtxt_recursion[1][11]->Fill(nfvtxt,fourSC24Recursion.Im(),wFourSC24Recursion);
  // ------------------------------------------------------------------------------------------------------
  for ( int cs = 0; cs < maxHarmonic; ++cs )
    {
      nfvtxt_recoffsets[0][cs]->Fill(nfvtxt,Qvector[cs][1].Re()/Qvector[0][1].Re());
      nfvtxt_recoffsets[1][cs]->Fill(nfvtxt,Qvector[cs][1].Im()/Qvector[0][1].Re());
      nfvtxt_recoffsets_north[0][cs]->Fill(nfvtxt,Qvector_north[cs][1].Re()/Qvector_north[0][1].Re());
      nfvtxt_recoffsets_north[1][cs]->Fill(nfvtxt,Qvector_north[cs][1].Im()/Qvector_north[0][1].Re());
      nfvtxt_recoffsets_south[0][cs]->Fill(nfvtxt,Qvector_south[cs][1].Re()/Qvector_south[0][1].Re());
      nfvtxt_recoffsets_south[1][cs]->Fill(nfvtxt,Qvector_south[cs][1].Im()/Qvector_south[0][1].Re());
    }
  // ------------------------------------------------------------------------------------------------------

  // --------------------------------------------------------- //
  // --- centrality
  // --------------

  // --- south only
  // --- north only
  // --- combined
  centrality_ac_fvtxc_tracks_c22->Fill(centrality,ac_fvtxc_tracks_qq2);
  centrality_ac_fvtxc_tracks_cos21->Fill(centrality,ac_fvtxc_tracks_qx2/ac_fvtxc_tracks_qw);
  centrality_ac_fvtxc_tracks_sin21->Fill(centrality,ac_fvtxc_tracks_qy2/ac_fvtxc_tracks_qw);
  centrality_ac_fvtxc_tracks_c32->Fill(centrality,ac_fvtxc_tracks_qq3); // come back here
  centrality_ac_fvtxc_tracks_cos31->Fill(centrality,ac_fvtxc_tracks_qx3/ac_fvtxc_tracks_qw);
  centrality_ac_fvtxc_tracks_sin31->Fill(centrality,ac_fvtxc_tracks_qy3/ac_fvtxc_tracks_qw);
  centrality_ac_fvtxc_tracks_cossum22->Fill(centrality,ac_fvtxc_tracks_cossum22);
  centrality_ac_fvtxc_tracks_sinsum22->Fill(centrality,ac_fvtxc_tracks_sinsum22);
  centrality_ac_fvtxc_tracks_cos23->Fill(centrality,ac_fvtxc_tracks_cos23);
  centrality_ac_fvtxc_tracks_sin23->Fill(centrality,ac_fvtxc_tracks_sin23);
  // --- additional acceptance correction histos
  centrality_ac_fvtxc_tracks_cossum32->Fill(centrality,ac_fvtxc_tracks_cossum32);
  centrality_ac_fvtxc_tracks_sinsum32->Fill(centrality,ac_fvtxc_tracks_sinsum32);
  centrality_ac_fvtxc_tracks_cos33->Fill(centrality,ac_fvtxc_tracks_cos33);
  centrality_ac_fvtxc_tracks_sin33->Fill(centrality,ac_fvtxc_tracks_sin33);
  // --- scalar product
  // --- four particle
  centrality_ac_fvtxc_tracks_c24->Fill(centrality,ac_fvtxc_tracks_qqqq24);
  centrality_ac_fvtxc_tracks_c34->Fill(centrality,ac_fvtxc_tracks_qqqq34);
  // --- four particle 2sub
  // --- six particle
  centrality_ac_fvtxc_tracks_c26->Fill(centrality,ac_fvtxc_tracks_six);
  centrality_ac_fvtxc_tracks_c28->Fill(centrality,eightRecursion.Re());

  if ( _verbosity > 2 )
    {
      cout << "Mcos2phi " << ac_fvtxc_tracks_qx2 << " " << Qvector[2][1].Re()  << endl;
      cout << "Msin2phi " << ac_fvtxc_tracks_qy2 << " " << Qvector[2][1].Im()  << endl;
      cout << "M        " << ac_fvtxc_tracks_qw  << " " << Qvector[0][1].Re() << endl;
      cout << "2 " << ac_fvtxc_tracks_qq2    << " " <<  twoRecursion.Re() << endl;
      cout << "4 " << ac_fvtxc_tracks_qqqq24 << " " << fourRecursion.Re() << endl;
      cout << "6 " << ac_fvtxc_tracks_six    << " " <<  sixRecursion.Re() << endl;
    }
  // --- v2
  centrality_recursion[0][0]->Fill(centrality,twoRecursion.Re(),wTwoRecursion);
  centrality_recursion[1][0]->Fill(centrality,twoRecursion.Im(),wTwoRecursion);
  centrality_recursion[0][2]->Fill(centrality,fourRecursion.Re(),wFourRecursion);
  centrality_recursion[1][2]->Fill(centrality,fourRecursion.Im(),wFourRecursion);
  centrality_recursion[0][4]->Fill(centrality,sixRecursion.Re(),wSixRecursion);
  centrality_recursion[1][4]->Fill(centrality,sixRecursion.Im(),wSixRecursion);
  centrality_recursion[0][6]->Fill(centrality,eightRecursion.Re(),wEightRecursion);
  centrality_recursion[1][6]->Fill(centrality,eightRecursion.Im(),wEightRecursion);
  // --- v3
  centrality_recursion[0][1]->Fill(centrality,twov3Recursion.Re(),wTwov3Recursion);
  centrality_recursion[1][1]->Fill(centrality,twov3Recursion.Im(),wTwov3Recursion);
  centrality_recursion[0][3]->Fill(centrality,fourv3Recursion.Re(),wFourv3Recursion);
  centrality_recursion[1][3]->Fill(centrality,fourv3Recursion.Im(),wFourv3Recursion);
  centrality_recursion[0][5]->Fill(centrality,sixv3Recursion.Re(),wSixv3Recursion);
  centrality_recursion[1][5]->Fill(centrality,sixv3Recursion.Im(),wSixv3Recursion);
  // --- v4
  centrality_recursion[0][7]->Fill(centrality,twov4Recursion.Re(),wTwov4Recursion);
  centrality_recursion[1][7]->Fill(centrality,twov4Recursion.Im(),wTwov4Recursion);
  centrality_recursion[0][9]->Fill(centrality,fourv4Recursion.Re(),wFourv4Recursion);
  centrality_recursion[1][9]->Fill(centrality,fourv4Recursion.Im(),wFourv4Recursion);
  // --- symmetric cumulants
  centrality_recursion[0][10]->Fill(centrality,fourSC23Recursion.Re(),wFourSC23Recursion);
  centrality_recursion[1][10]->Fill(centrality,fourSC23Recursion.Im(),wFourSC23Recursion);
  centrality_recursion[0][11]->Fill(centrality,fourSC24Recursion.Re(),wFourSC24Recursion);
  centrality_recursion[1][11]->Fill(centrality,fourSC24Recursion.Im(),wFourSC24Recursion);
  for ( int cs = 0; cs < maxHarmonic; ++cs )
    {
      centrality_recoffsets[0][cs]->Fill(centrality,Qvector[cs][1].Re()/Qvector[0][1].Re());
      centrality_recoffsets[1][cs]->Fill(centrality,Qvector[cs][1].Im()/Qvector[0][1].Re());
      centrality_recoffsets_north[0][cs]->Fill(centrality,Qvector_north[cs][1].Re()/Qvector_north[0][1].Re());
      centrality_recoffsets_north[1][cs]->Fill(centrality,Qvector_north[cs][1].Im()/Qvector_north[0][1].Re());
      centrality_recoffsets_south[0][cs]->Fill(centrality,Qvector_south[cs][1].Re()/Qvector_south[0][1].Re());
      centrality_recoffsets_south[1][cs]->Fill(centrality,Qvector_south[cs][1].Im()/Qvector_south[0][1].Re());
    }

  // ------------------------------------------------------------------------------------- //
  // --- calculations and histograms designed to be used with/for q-vector recentering --- //
  // ------------------------------------------------------------------------------------- //

  // ---
  // --- FVTX south
  float os_fvtxs_tracks_qw = fvtxs_tracks_qw[0];
  float os_fvtxs_tracks_qx2 = fvtxs_tracks_qx2[0] - qvoff_cent_south[icent][0][2]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qy2 = fvtxs_tracks_qy2[0] - qvoff_cent_south[icent][1][2]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qx3 = fvtxs_tracks_qx3[0] - qvoff_cent_south[icent][0][3]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qy3 = fvtxs_tracks_qy3[0] - qvoff_cent_south[icent][1][3]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qx4 = fvtxs_tracks_qx4[0] - qvoff_cent_south[icent][0][4]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qy4 = fvtxs_tracks_qy4[0] - qvoff_cent_south[icent][1][4]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qx6 = fvtxs_tracks_qx6[0] - qvoff_cent_south[icent][0][6]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qy6 = fvtxs_tracks_qy6[0] - qvoff_cent_south[icent][1][6]*os_fvtxs_tracks_qw;
  float os_fvtxs_tracks_qq2 = calc2_event(os_fvtxs_tracks_qx2,os_fvtxs_tracks_qy2,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_qq3 = calc2_event(os_fvtxs_tracks_qx3,os_fvtxs_tracks_qy3,os_fvtxs_tracks_qw);
  TComplex tc_os_fvtxs_tracks_Q2(os_fvtxs_tracks_qx2,os_fvtxs_tracks_qy2);
  TComplex tc_os_fvtxs_tracks_Q3(os_fvtxs_tracks_qx3,os_fvtxs_tracks_qy3);
  TComplex tc_os_fvtxs_tracks_Q4(os_fvtxs_tracks_qx4,os_fvtxs_tracks_qy4);
  TComplex tc_os_fvtxs_tracks_Q6(os_fvtxs_tracks_qx6,os_fvtxs_tracks_qy6);
  float os_fvtxs_tracks_cossum22 = calccossum2_event(tc_os_fvtxs_tracks_Q2,tc_os_fvtxs_tracks_Q4,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_sinsum22 = calcsinsum2_event(tc_os_fvtxs_tracks_Q2,tc_os_fvtxs_tracks_Q4,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_cossum32 = calccossum2_event(tc_os_fvtxs_tracks_Q3,tc_os_fvtxs_tracks_Q6,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_sinsum32 = calcsinsum2_event(tc_os_fvtxs_tracks_Q3,tc_os_fvtxs_tracks_Q6,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_cos23 = calccos3_event(tc_os_fvtxs_tracks_Q2,tc_os_fvtxs_tracks_Q4,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_sin23 = calcsin3_event(tc_os_fvtxs_tracks_Q2,tc_os_fvtxs_tracks_Q4,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_cos33 = calccos3_event(tc_os_fvtxs_tracks_Q3,tc_os_fvtxs_tracks_Q6,os_fvtxs_tracks_qw);
  float os_fvtxs_tracks_sin33 = calcsin3_event(tc_os_fvtxs_tracks_Q3,tc_os_fvtxs_tracks_Q6,os_fvtxs_tracks_qw);

  // --- FVTX north
  float os_fvtxn_tracks_qw = fvtxn_tracks_qw[0];
  float os_fvtxn_tracks_qx2 = fvtxn_tracks_qx2[0] - qvoff_cent_north[icent][0][2]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qy2 = fvtxn_tracks_qy2[0] - qvoff_cent_north[icent][1][2]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qx3 = fvtxn_tracks_qx3[0] - qvoff_cent_north[icent][0][3]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qy3 = fvtxn_tracks_qy3[0] - qvoff_cent_north[icent][1][3]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qx4 = fvtxn_tracks_qx4[0] - qvoff_cent_north[icent][0][4]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qy4 = fvtxn_tracks_qy4[0] - qvoff_cent_north[icent][1][4]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qx6 = fvtxn_tracks_qx6[0] - qvoff_cent_north[icent][0][6]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qy6 = fvtxn_tracks_qy6[0] - qvoff_cent_north[icent][1][6]*os_fvtxn_tracks_qw;
  float os_fvtxn_tracks_qq2 = calc2_event(os_fvtxn_tracks_qx2,os_fvtxn_tracks_qy2,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_qq3 = calc2_event(os_fvtxn_tracks_qx3,os_fvtxn_tracks_qy3,os_fvtxn_tracks_qw);
  TComplex tc_os_fvtxn_tracks_Q2(os_fvtxn_tracks_qx2,os_fvtxn_tracks_qy2);
  TComplex tc_os_fvtxn_tracks_Q3(os_fvtxn_tracks_qx3,os_fvtxn_tracks_qy3);
  TComplex tc_os_fvtxn_tracks_Q4(os_fvtxn_tracks_qx4,os_fvtxn_tracks_qy4);
  TComplex tc_os_fvtxn_tracks_Q6(os_fvtxn_tracks_qx6,os_fvtxn_tracks_qy6);
  float os_fvtxn_tracks_cossum22 = calccossum2_event(tc_os_fvtxn_tracks_Q2,tc_os_fvtxn_tracks_Q4,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_sinsum22 = calcsinsum2_event(tc_os_fvtxn_tracks_Q2,tc_os_fvtxn_tracks_Q4,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_cossum32 = calccossum2_event(tc_os_fvtxn_tracks_Q3,tc_os_fvtxn_tracks_Q6,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_sinsum32 = calcsinsum2_event(tc_os_fvtxn_tracks_Q3,tc_os_fvtxn_tracks_Q6,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_cos23 = calccos3_event(tc_os_fvtxn_tracks_Q2,tc_os_fvtxn_tracks_Q4,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_sin23 = calcsin3_event(tc_os_fvtxn_tracks_Q2,tc_os_fvtxn_tracks_Q4,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_cos33 = calccos3_event(tc_os_fvtxn_tracks_Q3,tc_os_fvtxn_tracks_Q6,os_fvtxn_tracks_qw);
  float os_fvtxn_tracks_sin33 = calcsin3_event(tc_os_fvtxn_tracks_Q3,tc_os_fvtxn_tracks_Q6,os_fvtxn_tracks_qw);

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
  TComplex tc_os_fvtxc_tracks_Q2(os_fvtxc_tracks_qx2,os_fvtxc_tracks_qy2);
  TComplex tc_os_fvtxc_tracks_Q3(os_fvtxc_tracks_qx4,os_fvtxc_tracks_qy3);
  TComplex tc_os_fvtxc_tracks_Q4(os_fvtxc_tracks_qx4,os_fvtxc_tracks_qy4);
  TComplex tc_os_fvtxc_tracks_Q6(os_fvtxc_tracks_qx6,os_fvtxc_tracks_qy6);
  float os_fvtxc_tracks_cossum22 = calccossum2_event(tc_os_fvtxc_tracks_Q2,tc_os_fvtxc_tracks_Q4,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_sinsum22 = calcsinsum2_event(tc_os_fvtxc_tracks_Q2,tc_os_fvtxc_tracks_Q4,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_cossum32 = calccossum2_event(tc_os_fvtxc_tracks_Q3,tc_os_fvtxc_tracks_Q6,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_sinsum32 = calcsinsum2_event(tc_os_fvtxc_tracks_Q3,tc_os_fvtxc_tracks_Q6,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_cos23 = calccos3_event(tc_os_fvtxc_tracks_Q2,tc_os_fvtxc_tracks_Q4,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_sin23 = calcsin3_event(tc_os_fvtxc_tracks_Q2,tc_os_fvtxc_tracks_Q4,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_cos33 = calccos3_event(tc_os_fvtxc_tracks_Q3,tc_os_fvtxc_tracks_Q6,os_fvtxc_tracks_qw);
  float os_fvtxc_tracks_sin33 = calcsin3_event(tc_os_fvtxc_tracks_Q3,tc_os_fvtxc_tracks_Q6,os_fvtxc_tracks_qw);

  // --- scalar product, fvtxs dot fvtxn
  float os_fvtxsfvtxn_tracks_qq2 = ( (os_fvtxs_tracks_qx2*os_fvtxn_tracks_qx2) + (os_fvtxs_tracks_qy2*os_fvtxn_tracks_qy2) ) / ( os_fvtxs_tracks_qw*os_fvtxn_tracks_qw );
  float os_fvtxsfvtxn_tracks_qq3 = ( (os_fvtxs_tracks_qx3*os_fvtxn_tracks_qx3) + (os_fvtxs_tracks_qy3*os_fvtxn_tracks_qy3) ) / ( os_fvtxs_tracks_qw*os_fvtxn_tracks_qw );
  float os_fvtxsfvtxn_tracks_qq4 = ( (os_fvtxs_tracks_qx4*os_fvtxn_tracks_qx4) + (os_fvtxs_tracks_qy4*os_fvtxn_tracks_qy4) ) / ( os_fvtxs_tracks_qw*os_fvtxn_tracks_qw );

  // --- now have a look at some 4 particle cumulants
  // --- calc4_event has the protection/requirement on the minimum number of tracks
  float os_fvtxs_tracks_qqqq24 = calc4_event(os_fvtxs_tracks_qx2,os_fvtxs_tracks_qy2,os_fvtxs_tracks_qx4,os_fvtxs_tracks_qy4,os_fvtxs_tracks_qw);
  float os_fvtxn_tracks_qqqq24 = calc4_event(os_fvtxn_tracks_qx2,os_fvtxn_tracks_qy2,os_fvtxn_tracks_qx4,os_fvtxn_tracks_qy4,os_fvtxn_tracks_qw);
  float os_fvtxc_tracks_qqqq24 = calc4_event(os_fvtxc_tracks_qx2,os_fvtxc_tracks_qy2,os_fvtxc_tracks_qx4,os_fvtxc_tracks_qy4,os_fvtxc_tracks_qw);
  float os_fvtxs_tracks_qqqq34 = calc4_event(os_fvtxs_tracks_qx3,os_fvtxs_tracks_qy3,os_fvtxs_tracks_qx6,os_fvtxs_tracks_qy6,os_fvtxs_tracks_qw);
  float os_fvtxn_tracks_qqqq34 = calc4_event(os_fvtxn_tracks_qx3,os_fvtxn_tracks_qy3,os_fvtxn_tracks_qx6,os_fvtxn_tracks_qy6,os_fvtxn_tracks_qw);
  float os_fvtxc_tracks_qqqq34 = calc4_event(os_fvtxc_tracks_qx3,os_fvtxc_tracks_qy3,os_fvtxc_tracks_qx6,os_fvtxc_tracks_qy6,os_fvtxc_tracks_qw);
  // --- four particle 2sub
  tca2 = TComplex(os_fvtxs_tracks_qx2,os_fvtxs_tracks_qy2);
  tcb2 = TComplex(os_fvtxn_tracks_qx2,os_fvtxn_tracks_qy2);
  tca4 = TComplex(os_fvtxs_tracks_qx4,os_fvtxs_tracks_qy4);
  tcb4 = TComplex(os_fvtxn_tracks_qx4,os_fvtxn_tracks_qy4);
  tc_numerator_a = tca2*tca2 - tca4;
  tc_numerator_b = TComplex::Conjugate(tcb2*tcb2 - tcb4);
  tc_numerator = tc_numerator_a*tc_numerator_b;
  numerator = tc_numerator.Re();
  tcaw = os_fvtxs_tracks_qw*os_fvtxs_tracks_qw - os_fvtxs_tracks_qw;
  tcbw = os_fvtxn_tracks_qw*os_fvtxn_tracks_qw - os_fvtxn_tracks_qw;
  denominator = tcaw*tcbw;
  answer_c24a = numerator/denominator;

  float os_fvtxs_tracks_six = calc6_event(tc_os_fvtxs_tracks_Q2,tc_os_fvtxs_tracks_Q4,tc_os_fvtxs_tracks_Q6,os_fvtxs_tracks_qw);
  float os_fvtxn_tracks_six = calc6_event(tc_os_fvtxn_tracks_Q2,tc_os_fvtxn_tracks_Q4,tc_os_fvtxn_tracks_Q6,os_fvtxn_tracks_qw);
  float os_fvtxc_tracks_six = calc6_event(tc_os_fvtxc_tracks_Q2,tc_os_fvtxc_tracks_Q4,tc_os_fvtxc_tracks_Q6,os_fvtxc_tracks_qw);

  if ( _verbosity > 2 )
    {
      cout << "Mcos2phi " << os_fvtxc_tracks_qx2 << " " << Qvector[2][1].Re()  << endl;
      cout << "Msin2phi " << os_fvtxc_tracks_qy2 << " " << Qvector[2][1].Im()  << endl;
      cout << "M        " << os_fvtxc_tracks_qw  << " " << Qvector[0][1].Re() << endl;
      cout << "2 " << os_fvtxc_tracks_qq2    << " " <<  twoRecursion.Re() << endl;
      cout << "4 " << os_fvtxc_tracks_qqqq24 << " " << fourRecursion.Re() << endl;
      cout << "6 " << os_fvtxc_tracks_six    << " " <<  sixRecursion.Re() << endl;
      cout << "offset south 2x " << " " << Qoffset_south[2][1].Re()/Qvector_south[0][1].Re() << " " << qvoff_cent_south[icent][0][2] << endl;
      cout << "offset north 2x " << " " << Qoffset_north[2][1].Re()/Qvector_north[0][1].Re() << " " << qvoff_cent_north[icent][0][2] << endl;
      cout << "offset south 2y " << " " << Qoffset_south[2][1].Im()/Qvector_south[0][1].Re() << " " << qvoff_cent_south[icent][1][2] << endl;
      cout << "offset north 2y " << " " << Qoffset_north[2][1].Im()/Qvector_north[0][1].Re() << " " << qvoff_cent_north[icent][1][2] << endl;
    }

  // --------------------------------------------------------- //
  // --- centrality
  // --------------

  // --- south only
  // --- north only
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
  // --- four particle
  centrality_os_fvtxc_tracks_c24->Fill(centrality,os_fvtxc_tracks_qqqq24);
  // --- four particle 2sub
  // --- six particle
  centrality_os_fvtxc_tracks_c26->Fill(centrality,os_fvtxc_tracks_six);
  centrality_os_fvtxc_tracks_c28->Fill(centrality,eightRecursion.Re());

  if ( _verbosity > 1000 )
    {
      cout << ac_fvtxs_tracks_qq2 << endl;
      cout << ac_fvtxs_tracks_qq3 << endl;
      cout << ac_fvtxs_tracks_cossum22 << endl;
      cout << ac_fvtxs_tracks_sinsum22 << endl;
      cout << ac_fvtxs_tracks_cossum32 << endl;
      cout << ac_fvtxs_tracks_sinsum32 << endl;
      cout << ac_fvtxs_tracks_cos23 << endl;
      cout << ac_fvtxs_tracks_sin23 << endl;
      cout << ac_fvtxs_tracks_cos33 << endl;
      cout << ac_fvtxs_tracks_sin33 << endl;
      cout << ac_fvtxn_tracks_qq2 << endl;
      cout << ac_fvtxn_tracks_qq3 << endl;
      cout << ac_fvtxn_tracks_cossum22 << endl;
      cout << ac_fvtxn_tracks_sinsum22 << endl;
      cout << ac_fvtxn_tracks_cossum32 << endl;
      cout << ac_fvtxn_tracks_sinsum32 << endl;
      cout << ac_fvtxn_tracks_cos23 << endl;
      cout << ac_fvtxn_tracks_sin23 << endl;
      cout << ac_fvtxn_tracks_cos33 << endl;
      cout << ac_fvtxn_tracks_sin33 << endl;
      cout << ac_fvtxsfvtxn_tracks_qq2 << endl;
      cout << ac_fvtxsfvtxn_tracks_qq3 << endl;
      cout << ac_fvtxs_tracks_qqqq24 << endl;
      cout << ac_fvtxn_tracks_qqqq24 << endl;
      cout << ac_fvtxs_tracks_qqqq34 << endl;
      cout << ac_fvtxn_tracks_qqqq34 << endl;
      cout << ac_fvtxs_tracks_six << endl;
      cout << ac_fvtxn_tracks_six << endl;
      cout << os_fvtxs_tracks_qq2 << endl;
      cout << os_fvtxs_tracks_qq3 << endl;
      cout << os_fvtxs_tracks_cossum22 << endl;
      cout << os_fvtxs_tracks_sinsum22 << endl;
      cout << os_fvtxs_tracks_cossum32 << endl;
      cout << os_fvtxs_tracks_sinsum32 << endl;
      cout << os_fvtxs_tracks_cos23 << endl;
      cout << os_fvtxs_tracks_sin23 << endl;
      cout << os_fvtxs_tracks_cos33 << endl;
      cout << os_fvtxs_tracks_sin33 << endl;
      cout << os_fvtxn_tracks_qq2 << endl;
      cout << os_fvtxn_tracks_qq3 << endl;
      cout << os_fvtxn_tracks_cossum22 << endl;
      cout << os_fvtxn_tracks_sinsum22 << endl;
      cout << os_fvtxn_tracks_cossum32 << endl;
      cout << os_fvtxn_tracks_sinsum32 << endl;
      cout << os_fvtxn_tracks_cos23 << endl;
      cout << os_fvtxn_tracks_sin23 << endl;
      cout << os_fvtxn_tracks_cos33 << endl;
      cout << os_fvtxn_tracks_sin33 << endl;
      cout << os_fvtxc_tracks_cossum32 << endl;
      cout << os_fvtxc_tracks_sinsum32 << endl;
      cout << os_fvtxc_tracks_cos33 << endl;
      cout << os_fvtxc_tracks_sin33 << endl;
      cout << os_fvtxsfvtxn_tracks_qq2 << endl;
      cout << os_fvtxsfvtxn_tracks_qq3 << endl;
      cout << os_fvtxsfvtxn_tracks_qq4 << endl;
      cout << os_fvtxs_tracks_qqqq24 << endl;
      cout << os_fvtxn_tracks_qqqq24 << endl;
      cout << os_fvtxs_tracks_qqqq34 << endl;
      cout << os_fvtxn_tracks_qqqq34 << endl;
      cout << os_fvtxc_tracks_qqqq34 << endl;
      cout << os_fvtxs_tracks_six << endl;
      cout << os_fvtxn_tracks_six << endl;
    }

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

