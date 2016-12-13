#ifndef __BOULDERCUMULANTS_H__
#define __BOULDERCUMULANTS_H__

// standard includes
#include <string>
#include <SubsysReco.h>



class Fun4AllHistoManager;
class dAuBES_utils;
class TFile;
class TH1D;
class TProfile;
class TComplex;

class BoulderCumulants: public SubsysReco
{
 public:
  BoulderCumulants();
  virtual ~BoulderCumulants();

  /// Fun4All calls...
  int  Init         (PHCompositeNode *topNode);
  int  InitRun      (PHCompositeNode *topNode);
  int  process_event(PHCompositeNode *topNode);
  int  ResetEvent   (PHCompositeNode *topNode);
  int  End          (PHCompositeNode *topNode);
  int  EndRun       (PHCompositeNode *topNode);
  void Verbosity    (int verbosity) {_verbosity = verbosity;}

  /// Single particle ntuple output...
  void set_output_filename(std::string filename) { _output_filename = filename; } // select output file name externally
  void set_use_runlist(bool b){ _use_runlist = b;} // text file for runs to analyze
  void set_runlist_file(std::string filename) { _runlist_filename = filename; } // name of file for above
  void set_do_offsets(bool b) { dooffsets = b; }
  bool is_run_in_list(int runnumber);

 protected:

  // ---

  // --- cumulants functions
  float calc2_event(float, float, float);
  float calc4_event(float, float, float, float, float);
  // --- acceptance correction functions
  float calccossum2_event(TComplex&, TComplex&, float);
  float calcsinsum2_event(TComplex&, TComplex&, float);
  float calccos3_event(TComplex&, TComplex&, float);
  float calcsin3_event(TComplex&, TComplex&, float);


  /// current event
  unsigned long _ievent;

  /// verbosity level
  int _verbosity;

  // --- check on whether to do offsets
  bool dooffsets;

  /// module output filename
  std::string _output_filename;
  TFile* _output_file;
  TFile* offset_file;

  //run list stuff
  bool _use_runlist;
  std::string _runlist_filename;

  dAuBES_utils* _utils;            ///< Utilities class


  int tmp_evt;


  //-- ntp_event variables
  int event;
  float bbc_z;
  float centrality;
  int npc1;
  unsigned int trigger_scaled;
  unsigned int trigger_live;
  float bc_x;
  float bc_y;
  float vtx_z;
  float FVTX_X;
  float FVTX_Y;
  float FVTX_Z;



  //-- Other variables


  TH1D* th1d_nfvtxt_combined;
  TH1D* th1d_nfvtxt_north;
  TH1D* th1d_nfvtxt_south;


  // --- correlation histograms
  // --- <<cos(n(phi1-phi2))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_c22;
  TProfile* nfvtxt_ac_fvtxn_tracks_c22;
  TProfile* nfvtxt_ac_fvtxc_tracks_c22;
  // --- <<cos(n(phi1+phi2-phi3-phi4))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_c24;
  TProfile* nfvtxt_ac_fvtxn_tracks_c24;
  TProfile* nfvtxt_ac_fvtxc_tracks_c24;
  // --- 2-particle scalr product
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c22 ;
  // --- experimental 4-particle correlations
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c24 ;
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c24a;
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c24b;
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c24c;
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c24d;

  // --- acceptance correction histograms
  // --- <<cos(n(phi1))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_cos21;
  TProfile* nfvtxt_ac_fvtxn_tracks_cos21;
  TProfile* nfvtxt_ac_fvtxc_tracks_cos21;
  // --- <<sin(n(phi1))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_sin21;
  TProfile* nfvtxt_ac_fvtxn_tracks_sin21;
  TProfile* nfvtxt_ac_fvtxc_tracks_sin21;
  // --- <<cos(n(phi1+phi2))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_cossum22;
  TProfile* nfvtxt_ac_fvtxn_tracks_cossum22;
  TProfile* nfvtxt_ac_fvtxc_tracks_cossum22;
  // --- <<sin(n(phi1+phi2))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_sinsum22;
  TProfile* nfvtxt_ac_fvtxn_tracks_sinsum22;
  TProfile* nfvtxt_ac_fvtxc_tracks_sinsum22;
  // --- <<cos(n(phi1-phi2-phi3))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_cos23;
  TProfile* nfvtxt_ac_fvtxn_tracks_cos23;
  TProfile* nfvtxt_ac_fvtxc_tracks_cos23;
  // --- <<sin(n(phi1-phi2-phi3))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_sin23;
  TProfile* nfvtxt_ac_fvtxn_tracks_sin23;
  TProfile* nfvtxt_ac_fvtxc_tracks_sin23;

  // --- 3rd harmonic stuff
  TProfile* nfvtxt_ac_fvtxs_tracks_c32;
  TProfile* nfvtxt_ac_fvtxn_tracks_c32;
  TProfile* nfvtxt_ac_fvtxc_tracks_c32;
  TProfile* nfvtxt_ac_fvtxs_tracks_cos31;
  TProfile* nfvtxt_ac_fvtxn_tracks_cos31;
  TProfile* nfvtxt_ac_fvtxc_tracks_cos31;
  TProfile* nfvtxt_ac_fvtxs_tracks_sin31;
  TProfile* nfvtxt_ac_fvtxn_tracks_sin31;
  TProfile* nfvtxt_ac_fvtxc_tracks_sin31;
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c32;

  // --- event plane decorrelation stuff
  TProfile* tp1f_special_fvtx_tracks_ab[8];
  TProfile* tp1f_special_fvtx_tracks_aa;
  TProfile* tp1f_special_fvtx_tracks_aa_cos;
  TProfile* tp1f_special_fvtx_tracks_aa_sin;




  TProfile* nfvtxt_tracks_south_qx2;
  TProfile* nfvtxt_tracks_south_qx3;
  TProfile* nfvtxt_tracks_south_qx4;
  TProfile* nfvtxt_tracks_south_qy2;
  TProfile* nfvtxt_tracks_south_qy3;
  TProfile* nfvtxt_tracks_south_qy4;

  TProfile* nfvtxt_tracks_south_inner_qx2;
  TProfile* nfvtxt_tracks_south_inner_qx3;
  TProfile* nfvtxt_tracks_south_inner_qx4;
  TProfile* nfvtxt_tracks_south_inner_qy2;
  TProfile* nfvtxt_tracks_south_inner_qy3;
  TProfile* nfvtxt_tracks_south_inner_qy4;

  TProfile* nfvtxt_tracks_south_outer_qx2;
  TProfile* nfvtxt_tracks_south_outer_qx3;
  TProfile* nfvtxt_tracks_south_outer_qx4;
  TProfile* nfvtxt_tracks_south_outer_qy2;
  TProfile* nfvtxt_tracks_south_outer_qy3;
  TProfile* nfvtxt_tracks_south_outer_qy4;

  TProfile* nfvtxt_tracks_north_qx2;
  TProfile* nfvtxt_tracks_north_qx3;
  TProfile* nfvtxt_tracks_north_qx4;
  TProfile* nfvtxt_tracks_north_qy2;
  TProfile* nfvtxt_tracks_north_qy3;
  TProfile* nfvtxt_tracks_north_qy4;

  TProfile* nfvtxt_tracks_north_inner_qx2;
  TProfile* nfvtxt_tracks_north_inner_qx3;
  TProfile* nfvtxt_tracks_north_inner_qx4;
  TProfile* nfvtxt_tracks_north_inner_qy2;
  TProfile* nfvtxt_tracks_north_inner_qy3;
  TProfile* nfvtxt_tracks_north_inner_qy4;

  TProfile* nfvtxt_tracks_north_outer_qx2;
  TProfile* nfvtxt_tracks_north_outer_qx3;
  TProfile* nfvtxt_tracks_north_outer_qx4;
  TProfile* nfvtxt_tracks_north_outer_qy2;
  TProfile* nfvtxt_tracks_north_outer_qy3;
  TProfile* nfvtxt_tracks_north_outer_qy4;





};

#endif /* __BOULDERCUMULANTS_H__ */



