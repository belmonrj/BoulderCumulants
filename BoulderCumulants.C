#include "BoulderCumulants.h"

#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <fstream>


#include "TOAD.h"

#include <TMath.h>
#include <TString.h>

#include <TLorentzVector.h>
#include <TVector3.h>

// Fun4All includes...
#include <Fun4AllReturnCodes.h>
#include <Fun4AllServer.h>
#include <Fun4AllHistoManager.h>
#include <PHCompositeNode.h>
#include <PHIODataNode.h>
#include <phool.h>
#include <getClass.h>
#include <PHGlobalv9.h>
#include <EventHeader.h>
#include <TrigLvl1.h>
#include <SvxSegmentList.h>
#include <SvxSegment.h>
#include <VtxOut.h>
#include <PHPoint.h>
#include <PHAngle.h>
#include <RunHeader.h>
//#include <BbcLL1Out.h>
#include <TFvtxCompactTrkMap.h>
#include <BbcRaw.h>
#include <BbcOut.h>
#include <BbcCalib.hh>
#include <BbcGeo.hh>

#include "SvxClusterList.h"
#include "SvxCluster.h"

#include "RpSnglSumXY.h"
#include "RpSumXYObject.h"
#include "ReactionPlaneObject.h"
#include "RpConst.h"
#include "recoConsts.h"
#include <TFvtxCompactCoordMap.h>

#include <PreviousEvent.h>

#include "dAuBES_utils.h"


// ------------------------
#include "PHCentralTrack.h"
#include "PHSnglCentralTrack.h"



using namespace std;


// --- class constructor
BoulderCumulants::BoulderCumulants():
  SubsysReco("BOULDERCUMULANTS"),
  _ievent(0),
  _verbosity(0),
  _output_filename("NULL"),
  _output_file(NULL),
  _use_runlist(false),
  _runlist_filename(""),
  _utils(NULL),
  tmp_evt(0)
{
  ResetEvent(NULL);

  m_bbccalib = new BbcCalib();
  m_bbcgeo   = new BbcGeo();
  return;
}


// --- class destructor
BoulderCumulants::~BoulderCumulants()
{
  delete m_bbccalib;
  delete m_bbcgeo;
  if ( _utils ) delete _utils;
}


// --- Init method, part of Fun4All inheriance
int BoulderCumulants::Init(PHCompositeNode *topNode)
{

  ResetEvent(topNode); // is this needed?

  if (_verbosity > 1) cout << PHWHERE << "::Init() - entered." << endl;

  _output_file = new TFile(_output_filename.c_str(), "RECREATE");

  return EVENT_OK;
}


// --- InitRun, part of Fun4All inheritance
int BoulderCumulants::InitRun(PHCompositeNode *topNode)
{

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



  // Setup the utility class
  // This is done in init run so that the collision system can be
  // determined from the run number
  TString _collsys = "Run16dAu200"; // default to 200 GeV
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
  _utils = new dAuBES_utils(_collsys, true);
  // _utils->is_sim(_is_sim);


  return EVENT_OK;
}


// --- ResetEvent, part of Fun4All inheritance, called after every event by Fun4All
int BoulderCumulants::ResetEvent(PHCompositeNode *topNode)
{
  if (_verbosity > 1) cout << PHWHERE << "::ResetEvent() - entered." << endl;

  event         = -9999;
  centrality    = -9999;
  npc1          = -9999;
  trigger_scaled = -9999;
  trigger_live   = -9999;
  // bbc_qn        = -9999;
  // bbc_qs        = -9999;
  bbc_z         = -9999;
  vtx_z         = -9999;
  bc_x          = -9999;
  bc_y          = -9999;
  //  ntracklets    = -9999;


  return EVENT_OK;

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

  TrigLvl1 *triggers = findNode::getClass<TrigLvl1>(topNode, "TrigLvl1");
  if (!triggers)
  {
    cout << PHWHERE << " ERROR::TrigLvl1 not found" << endl;
    return ABORTEVENT;
  }
  PHGlobal *global = findNode::getClass<PHGlobal>(topNode, "PHGlobal");
  if (!global)
  {
    cout << PHWHERE << " ERROR::PHGlobal not found" << endl;
    return ABORTEVENT;
  }
  EventHeader *evthead = findNode::getClass<EventHeader>(topNode, "EventHeader");
  if (!evthead)
  {
    cout << PHWHERE << " ERROR::EventHeader not found" << endl;
    return ABORTEVENT;
  }
  VtxOut *vertexes = findNode::getClass<VtxOut>(topNode, "VtxOut");
  if (!vertexes)
  {
    cout << PHWHERE << " ERROR::VtxOut not found" << endl;
    return ABORTEVENT;
  }

  TFvtxCompactTrkMap* trkfvtx_map = NULL;
  if (_write_fvtx)
  {
    trkfvtx_map = findNode::getClass<TFvtxCompactTrkMap>(topNode, "TFvtxCompactTrkMap");
    if (!trkfvtx_map) {
      cerr << PHWHERE << " No TFvtxCompactTrkMap object !" << endl;
      return ABORTEVENT;
    }
  }

  TFvtxCompactCoordMap* fvtx_coord_map = findNode::getClass<TFvtxCompactCoordMap>(topNode, "TFvtxCompactCoordMap");
  if (!fvtx_coord_map && _write_fvtx_clusters)
  {
    cout << PHWHERE << " ERROR::TFvtxCompactCoordMap not found" << endl;
    return ABORTEVENT;
  }

  RpSumXYObject* d_rp = findNode::getClass<RpSumXYObject>(topNode, "RpSumXYObject");
  if (!d_rp)
  {
    if ( _verbosity > 4 ) cout << PHWHERE << "Could not find the RPSumXYObject" << endl;
    //return ABORTEVENT;
  }

  BbcRaw *bbcraw = findNode::getClass<BbcRaw>(topNode, "BbcRaw");
  if (!bbcraw)
  {
    cout << PHWHERE << "Could not find Bbcraw!" << endl;
    if (_write_bbc)
      return ABORTEVENT;
  }


  //---------------------------------------------------------//
  //
  //         Make Event Selection
  //
  //---------------------------------------------------------//

  if (!_utils->is_event_ok(topNode))
    return EVENT_OK;



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
  // bbc_qn      = global->getBbcChargeN();
  // bbc_qs      = global->getBbcChargeS();
  npc1        = global->getNumberPC1Hits();
  event = evthead->get_EvtSequence();
  trigger_scaled = triggers->get_lvl1_trigscaled();
  trigger_live = triggers->get_lvl1_triglive();




  // --- bbc_z...
  PHPoint vertex1 = vertexes->get_Vertex("BBC");
  bbc_z = vertex1.getZ();
  if ( bbc_z != bbc_z ) bbc_z = -9999; // reassign nan

  PHPoint fvtx_vertex = vertexes->get_Vertex("FVTX");
  FVTX_X = fvtx_vertex.getX();
  FVTX_Y = fvtx_vertex.getY();
  FVTX_Z = fvtx_vertex.getZ();
  if ( FVTX_Z != FVTX_Z ) FVTX_Z = -9999; // reassign nan

  // cout << endl;
  // cout << "--- starting vertex checking ---" << endl;
  float zvtx = _utils->get_vrtx(topNode);


  if ( _verbosity > 1 ) cout << "FVTX vertex points: " << FVTX_X << " " << FVTX_Y << " " << FVTX_Z << endl;


  //int ntr = -1;
  int ntr = 0;

  if ( trkfvtx_map && _write_fvtx )
  {
    TFvtxCompactTrkMap::const_iterator trk_iter = trkfvtx_map->range();
    while ( TFvtxCompactTrkMap::const_pointer trk_ptr = trk_iter.next() )
    {

      TFvtxCompactTrk* fvtx_trk = trk_ptr->get();

      //-- Only write out good fvtx tracks
      if ( !_utils->is_fvtx_track_ok(fvtx_trk, zvtx) )
        continue;

      float the = fvtx_trk->get_fvtx_theta();
      //float eta = fvtx_trk->get_fvtx_eta();
      float phi = fvtx_trk->get_fvtx_phi();
      //int   arm = (int)fvtx_trk->get_arm();
      float fvtx_x      = fvtx_trk->get_fvtx_vtx().getX();
      float fvtx_y      = fvtx_trk->get_fvtx_vtx().getY();
      float fvtx_z      = fvtx_trk->get_fvtx_vtx().getZ();
      //int   nfhits      = (int)fvtx_trk->get_nhits();

      // fix total momentum to 1.0 (for rotating due to beamtilt)
      double px = 1.0 * TMath::Sin(the) * TMath::Cos(phi);
      double py = 1.0 * TMath::Sin(the) * TMath::Sin(phi);
      double pz = 1.0 * TMath::Cos(the);

      // rotate based on beamtilt
      px = _utils->rotate_x(px, pz);
      pz = _utils->rotate_z(px, pz);
      phi = TMath::ATan2(py, px);
      the = TMath::ACos(pz / TMath::Sqrt(px * px + py * py + pz * pz));


      float vertex_z = bbc_z;
      if ( FVTX_Z > -999 ) vertex_z = FVTX_Z;
      float DCA_x      = fvtx_x + tan(the) * cos(phi) * (vertex_z - fvtx_z);
      float DCA_y      = fvtx_y + tan(the) * sin(phi) * (vertex_z - fvtx_z);
      //if(the==0 || phi==0 || fvtx_x==0 || fvtx_y==0 || fvtx_z==0) continue;
      //if(the==0) continue;

      //if ( nfhits < 3 ) continue;
      //if ( !pass_eta_cut(eta,ibbcz_bin) ) continue;
      if ( fvtx_trk->get_chi2_ndf() > 5 ) continue;
      if ( fabs(DCA_x - 0.3) > 2.0 || fabs(DCA_y - 0.02) > 2.0 ) continue;


      //float DCA_R      = sqrt((DCA_x*DCA_x) + (DCA_y*DCA_y));

      ++ntr;

    } // end while loop over tracks
  } // check on fvtx track map


  //---------------------------------------------------------//
  //                 finished Get FVTX Tracks
  //---------------------------------------------------------//


  //---------------------------------------------------------//
  //
  //                 Get CNT Tracks
  //
  //---------------------------------------------------------//


  PHCentralTrack *ctrk = findNode::getClass<PHCentralTrack>(topNode, "PHCentralTrack");
  if ( ctrk )
  {
    int ntrk = ctrk->get_npart();
    if ( ntrk > N_CTRK_MAX )
    {
      cout << PHWHERE << " WARNING: too many tracks, skipping event" << endl;
      return ABORTEVENT;
    }
    int counter = 0;
    for ( int itrk = 0; itrk < ntrk; ++itrk)
    {

      PHSnglCentralTrack *strk = ctrk->get_track(itrk);

      //-- Only write out good PHCentralTracks
      if ( !_utils->is_cnt_track_ok(strk) )
        continue;


      float mom         = strk->get_mom();
      float zed         = strk->get_zed();
      int quality       = strk->get_quality();
      if ( mom < 0.0 || mom > 50.0 ) continue;
      if ( fabs(zed) < 3.0 || fabs(zed) > 70.0 ) continue;
      if ( quality != 63 && quality != 31 ) continue;

      float px = strk->get_px();
      //float py = strk->get_py();
      float pz = strk->get_pz();

      // int arm = 0;
      // if ( px > 0 ) arm = 1;

      // rotate based on beamtilt
      px = _utils->rotate_x(px, pz);
      pz = _utils->rotate_z(px, pz);


      //int charge = strk->get_charge();

      float pc3dphi = strk->get_pc3dphi();
      float pc3dz = strk->get_pc3dz();

      if ( pc3dphi < -9990 || pc3dz < -9990 ) continue;

      // float pc3sdphi = calcsdphi(pc3dphi, arm, charge, mom);
      // float pc3sdz = calcsdz(pc3dz, arm, charge, mom);
      float pc3sdphi = strk->get_pc3sdphi();
      float pc3sdz = strk->get_pc3sdz();

      if ( fabs(pc3sdphi) > 3.0 || fabs(pc3sdz) > 3.0 ) continue;

      ++counter;

    } // loop over tracks

  } // check on track pointer

  //---------------------------------------------------------//
  //                 finished Get CNT Tracks
  //---------------------------------------------------------//


  if ( _create_ttree ) _ntp_event->Fill();

  if ( _verbosity > 0 ) cout << "sucessfully processed this event" << endl;

  tmp_evt++;//to keep track of how many events pass event cuts
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

  _output_file->cd();


  _output_file->Close();
  delete _output_file;

  return EVENT_OK;
}




bool BoulderCumulants::is_run_in_list(int runnumber)
{
  ifstream runlist;
  runlist.open(_runlist_filename.c_str());
  int run_num;
  while (1) {
    if (!runlist.good()) break;
    runlist >> run_num;
    if (run_num == runnumber)
      return true;
  }
  return false;
}

//these vaules were obtained from ana note 1162
bool BoulderCumulants::pass_eta_cut(float eta, int bbcz_bin)
{
  if (bbcz_bin == 0)
  {
    if (eta > 1.9 && eta < 3.2)
      return true;
  }
  if (bbcz_bin == 1)
  {
    if (eta > -1.7 && eta < -0.8)
      return true;
    if (eta > 1.7 && eta < 3.2)
      return true;
  }
  if (bbcz_bin == 2)
  {
    if (eta > -2.1 && eta < -0.7)
      return true;
    if (eta > 1.5 && eta < 3.1)
      return true;
  }
  if (bbcz_bin == 3)
  {
    if (eta > -2.4 && eta < -0.9)
      return true;
    if (eta > 1.3 && eta < 3.0)
      return true;
  }
  if (bbcz_bin == 4)
  {
    if (eta > -2.6 && eta < -1.0)
      return true;
    if (eta > 1.2 && eta < 2.8)
      return true;
  }
  if (bbcz_bin == 5)
  {
    if (eta > -2.8 && eta < -1.2)
      return true;
    if (eta > 1.0 && eta < 2.6)
      return true;
  }
  if (bbcz_bin == 6)
  {
    if (eta > -3.0 && eta < -1.3)
      return true;
    if (eta > 0.9 && eta < 2.4)
      return true;
  }
  if (bbcz_bin == 7)
  {
    if (eta > -3.1 && eta < -1.4)
      return true;
    if (eta > 0.7 && eta < 2.1)
      return true;
  }
  if (bbcz_bin == 8)
  {
    if (eta > -3.2 && eta < -1.5)
      return true;
    if (eta > 0.7 && eta < 1.6)
      return true;
  }
  if (bbcz_bin == 9)
  {
    if (eta > -3.3 && eta < -1.8)
      return true;
  }

  return false;
}

