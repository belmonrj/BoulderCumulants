#ifndef __BOULDERCUMULANTS_H__
#define __BOULDERCUMULANTS_H__

// standard includes
#include <string>
#include <SubsysReco.h>
#include "TComplex.h"


class Fun4AllHistoManager;
class dAuBES_utils;
class TFile;
class TTree;
class TH1D;
class TH2D;
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
  //  int  ResetEvent   (PHCompositeNode *topNode);
  int  End          (PHCompositeNode *topNode);
  int  EndRun       (PHCompositeNode *topNode);
  void Verbosity    (int verbosity) {_verbosity = verbosity;}

  /// Single particle ntuple output...
  void set_output_filename(std::string filename) { _output_filename = filename; } // select output file name externally
  void set_use_runlist(bool b){ _use_runlist = b;} // text file for runs to analyze
  void set_runlist_file(std::string filename) { _runlist_filename = filename; } // name of file for above
  bool is_run_in_list(int runnumber);
  void SetQvectorOffsets(int runnumber);
  void set_create_ttree(bool b){_create_ttree = b;} // ??
  void set_do_double_track_cut(bool b){do_double_track_cut = b;}
  void set_zvtxcut(double z){_cut_zvtx = z;}
  void set_chi2cut(double c){_cut_chi2 = c;}
  void set_nhitcut(int n){_cut_nhit = n;}

 protected:

  // --- special event cuts
  bool PassesTracksChargeRatio(int, double);

  // --- cumulants functions
  float calc2_event(float, float, float);
  float calc4_event(float, float, float, float, float);
  float calc6_event(TComplex&, TComplex&, TComplex&, float);
  // --- acceptance correction functions
  float calccossum2_event(TComplex&, TComplex&, float);
  float calcsinsum2_event(TComplex&, TComplex&, float);
  float calccos3_event(TComplex&, TComplex&, float);
  float calcsin3_event(TComplex&, TComplex&, float);

  //static const int h1=2;
  //static const int h2=-2;
  //static const int h3=2;
  //static const int h4=-2;
  //static const int h5=2;
  //static const int h6=-2;
  //static const int h7=2;
  //static const int h8=-2; // simplifed to v2
  //static const int sum = (h1<0?-1*h1:h1)+(h2<0?-1*h2:h2)+(h3<0?-1*h3:h3)+(h4<0?-1*h4:h4)
  //  + (h5<0?-1*h5:h5)+(h6<0?-1*h6:h6)+(h7<0?-1*h7:h7)+(h8<0?-1*h8:h8);
  //static const int maxCorrelator = 8; // We will not go beyond 8-p correlations
  //static const int maxHarmonic = sum+1;
  //static const int maxPower = maxCorrelator+1;
  static const int maxCorrelator = 12; // Somewhat abusing the setup as it is...
  static const int maxHarmonic = 10; // Need to assess on case-by-case basis, but this gets you v2{8} and v3{6}
  static const int maxPower = 9;
  TComplex Qvector[maxHarmonic][maxPower]; // All needed Q-vector components
  TComplex Qvector_north[maxHarmonic][maxPower];
  TComplex Qvector_south[maxHarmonic][maxPower];
  TComplex Qoffset[maxHarmonic][maxPower];
  TComplex Qoffset_north[maxHarmonic][maxPower];
  TComplex Qoffset_south[maxHarmonic][maxPower];
  TComplex Q(int, int);
  TComplex Recursion(int, int*);
  TComplex Recursion(int, int*, int, int);

  // ---------------------------------------------------------------------
  static const int maxTracks = 650; // accept no more FVTX tracks than this

  /// current event
  unsigned long _ievent;

  /// verbosity level
  int _verbosity;

  /// module output filename
  std::string _output_filename;
  TFile* _output_file;

  // whether to do the double track cut
  bool do_double_track_cut;

  double _cut_zvtx;
  double _cut_chi2;
  int _cut_nhit;

  //run list stuff
  bool _use_runlist;
  std::string _runlist_filename;

  dAuBES_utils* _utils;            ///< Utilities class
  bool use_utils;
  std::string _collsys;

  int tmp_evt;

  bool _create_ttree;
  // -- the tree itself
  TTree* shorttree;

  //-- ntp_event variables
  int event;
  float bbc_z;
  float centrality;
  float bbc_qn;
  float bbc_qs;
  int icent;
  int npc1;
  int nfvtxt;
  int nfvtxt_south;
  int nfvtxt_north;
  int nfvtxt_raw;
  unsigned int trigger_scaled;
  unsigned int trigger_live;
  float bc_x;
  float bc_y;
  float vtx_z;
  float FVTX_X;
  float FVTX_Y;
  float FVTX_Z;

  float d_SouthQX[9];
  float d_SouthQY[9];
  float d_SouthQW;
  float d_NorthQX[9];
  float d_NorthQY[9];
  float d_NorthQW;

  // --- Q-vector offset variables
  double qvoff_nfvtxt[maxTracks][2][maxHarmonic];
  double qvoff_nfvtxt_north[maxTracks][2][maxHarmonic];
  double qvoff_nfvtxt_south[maxTracks][2][maxHarmonic];
  double qvoff_cent[100][2][maxHarmonic];
  double qvoff_cent_north[100][2][maxHarmonic];
  double qvoff_cent_south[100][2][maxHarmonic];
  double offset_centrality_qx2_south[100];
  double offset_centrality_qx4_south[100];
  double offset_centrality_qx6_south[100];
  double offset_centrality_qy2_south[100];
  double offset_centrality_qy4_south[100];
  double offset_centrality_qy6_south[100];
  double offset_centrality_qx2_north[100];
  double offset_centrality_qx4_north[100];
  double offset_centrality_qx6_north[100];
  double offset_centrality_qy2_north[100];
  double offset_centrality_qy4_north[100];
  double offset_centrality_qy6_north[100];



  //-- Other variables
  TH1D* th1d_nfvtxt_combinedER;
  TH1D* th1d_nfvtxt_combined;
  TH1D* th1d_nfvtxt_north;
  TH1D* th1d_nfvtxt_south;
  TH2D* th2d_nfvtxt_bbcsum;
  TH2D* th2d_nfvtxt_centrality;
  TH2D* th2d_nfvtxt_centralityA;
  TH2D* th2d_nfvtxt_bbcsumratio;
  TH1D* th1d_track_deta;
  TH1D* th1d_track_dphi;
  TProfile* tp1f_track_detacutpass;


  // --- correlation histograms
  // --- <<cos(n(phi1-phi2))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_c22;
  TProfile* nfvtxt_ac_fvtxn_tracks_c22;
  TProfile* nfvtxt_ac_fvtxc_tracks_c22;
  // --- <<cos(n(phi1+phi2-phi3-phi4))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_c24;
  TProfile* nfvtxt_ac_fvtxn_tracks_c24;
  TProfile* nfvtxt_ac_fvtxc_tracks_c24;
  TProfile* nfvtxt_ac_fvtxs_tracks_c26;
  TProfile* nfvtxt_ac_fvtxn_tracks_c26;
  TProfile* nfvtxt_ac_fvtxc_tracks_c26;
  TProfile* nfvtxt_ac_fvtxc_tracks_c28;
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
  // --- correlation histograms
  // --- <<cos(n(phi1-phi2))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_c32;
  TProfile* nfvtxt_ac_fvtxn_tracks_c32;
  TProfile* nfvtxt_ac_fvtxc_tracks_c32;
  // --- <<cos(n(phi1+phi2-phi3-phi4))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_c34;
  TProfile* nfvtxt_ac_fvtxn_tracks_c34;
  TProfile* nfvtxt_ac_fvtxc_tracks_c34;
  TProfile* nfvtxt_ac_fvtxs_tracks_c36;
  TProfile* nfvtxt_ac_fvtxn_tracks_c36;
  TProfile* nfvtxt_ac_fvtxc_tracks_c36;
  // --- 2-particle scalr product
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c42 ;
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c32 ;
  // --- experimental 4-particle correlations
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c34 ;
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c34a;
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c34b;
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c34c;
  TProfile* nfvtxt_ac_fvtxsfvtxn_tracks_c34d;

  // --- acceptance correction histograms
  // --- <<cos(n(phi1))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_cos31;
  TProfile* nfvtxt_ac_fvtxn_tracks_cos31;
  TProfile* nfvtxt_ac_fvtxc_tracks_cos31;
  // --- <<sin(n(phi1))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_sin31;
  TProfile* nfvtxt_ac_fvtxn_tracks_sin31;
  TProfile* nfvtxt_ac_fvtxc_tracks_sin31;
  // --- <<cos(n(phi1+phi2))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_cossum32;
  TProfile* nfvtxt_ac_fvtxn_tracks_cossum32;
  TProfile* nfvtxt_ac_fvtxc_tracks_cossum32;
  // --- <<sin(n(phi1+phi2))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_sinsum32;
  TProfile* nfvtxt_ac_fvtxn_tracks_sinsum32;
  TProfile* nfvtxt_ac_fvtxc_tracks_sinsum32;
  // --- <<cos(n(phi1-phi2-phi3))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_cos33;
  TProfile* nfvtxt_ac_fvtxn_tracks_cos33;
  TProfile* nfvtxt_ac_fvtxc_tracks_cos33;
  // --- <<sin(n(phi1-phi2-phi3))>>
  TProfile* nfvtxt_ac_fvtxs_tracks_sin33;
  TProfile* nfvtxt_ac_fvtxn_tracks_sin33;
  TProfile* nfvtxt_ac_fvtxc_tracks_sin33;

  // --- centrality stuff

  // --- correlation histograms
  // --- <<cos(n(phi1-phi2))>>
  TProfile* centrality_ac_fvtxs_tracks_c22;
  TProfile* centrality_ac_fvtxn_tracks_c22;
  TProfile* centrality_ac_fvtxc_tracks_c22;
  // --- <<cos(n(phi1+phi2-phi3-phi4))>>
  TProfile* centrality_ac_fvtxs_tracks_c24;
  TProfile* centrality_ac_fvtxn_tracks_c24;
  TProfile* centrality_ac_fvtxc_tracks_c24;
  TProfile* centrality_ac_fvtxs_tracks_c26;
  TProfile* centrality_ac_fvtxn_tracks_c26;
  TProfile* centrality_ac_fvtxc_tracks_c26;
  TProfile* centrality_ac_fvtxc_tracks_c28;
  // --- 2-particle scalr product
  TProfile* centrality_ac_fvtxsfvtxn_tracks_c22 ;
  // --- experimental 4-particle correlations
  TProfile* centrality_ac_fvtxsfvtxn_tracks_c24 ;
  TProfile* centrality_ac_fvtxsfvtxn_tracks_c24a;
  TProfile* centrality_ac_fvtxsfvtxn_tracks_c24b;
  TProfile* centrality_ac_fvtxsfvtxn_tracks_c24c;
  TProfile* centrality_ac_fvtxsfvtxn_tracks_c24d;

  // --- acceptance correction histograms
  // --- <<cos(n(phi1))>>
  TProfile* centrality_ac_fvtxs_tracks_cos21;
  TProfile* centrality_ac_fvtxn_tracks_cos21;
  TProfile* centrality_ac_fvtxc_tracks_cos21;
  // --- <<sin(n(phi1))>>
  TProfile* centrality_ac_fvtxs_tracks_sin21;
  TProfile* centrality_ac_fvtxn_tracks_sin21;
  TProfile* centrality_ac_fvtxc_tracks_sin21;
  // --- <<cos(n(phi1+phi2))>>
  TProfile* centrality_ac_fvtxs_tracks_cossum22;
  TProfile* centrality_ac_fvtxn_tracks_cossum22;
  TProfile* centrality_ac_fvtxc_tracks_cossum22;
  // --- <<sin(n(phi1+phi2))>>
  TProfile* centrality_ac_fvtxs_tracks_sinsum22;
  TProfile* centrality_ac_fvtxn_tracks_sinsum22;
  TProfile* centrality_ac_fvtxc_tracks_sinsum22;
  // --- <<cos(n(phi1-phi2-phi3))>>
  TProfile* centrality_ac_fvtxs_tracks_cos23;
  TProfile* centrality_ac_fvtxn_tracks_cos23;
  TProfile* centrality_ac_fvtxc_tracks_cos23;
  // --- <<sin(n(phi1-phi2-phi3))>>
  TProfile* centrality_ac_fvtxs_tracks_sin23;
  TProfile* centrality_ac_fvtxn_tracks_sin23;
  TProfile* centrality_ac_fvtxc_tracks_sin23;
  // --- 3rd harmonic stuff
  TProfile* centrality_ac_fvtxs_tracks_c32;
  TProfile* centrality_ac_fvtxn_tracks_c32;
  TProfile* centrality_ac_fvtxc_tracks_c32;
  TProfile* centrality_ac_fvtxs_tracks_cos31;
  TProfile* centrality_ac_fvtxn_tracks_cos31;
  TProfile* centrality_ac_fvtxc_tracks_cos31;
  TProfile* centrality_ac_fvtxs_tracks_sin31;
  TProfile* centrality_ac_fvtxn_tracks_sin31;
  TProfile* centrality_ac_fvtxc_tracks_sin31;
  TProfile* centrality_ac_fvtxsfvtxn_tracks_c42;
  TProfile* centrality_ac_fvtxsfvtxn_tracks_c32;

  // --- come back here

  // --- correlation histograms
  // --- <<cos(n(phi1-phi2))>>
  TProfile* nfvtxt_os_fvtxs_tracks_c22;
  TProfile* nfvtxt_os_fvtxn_tracks_c22;
  TProfile* nfvtxt_os_fvtxc_tracks_c22;
  // --- <<cos(n(phi1+phi2-phi3-phi4))>>
  TProfile* nfvtxt_os_fvtxs_tracks_c24;
  TProfile* nfvtxt_os_fvtxn_tracks_c24;
  TProfile* nfvtxt_os_fvtxc_tracks_c24;
  TProfile* nfvtxt_os_fvtxs_tracks_c26;
  TProfile* nfvtxt_os_fvtxn_tracks_c26;
  TProfile* nfvtxt_os_fvtxc_tracks_c26;
  TProfile* nfvtxt_os_fvtxc_tracks_c28;
  // --- 2-particle scalr product
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c22 ;
  // --- experimental 4-particle correlations
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c24 ;
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c24a;
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c24b;
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c24c;
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c24d;

  // --- acceptance correction histograms
  // --- <<cos(n(phi1))>>
  TProfile* nfvtxt_os_fvtxs_tracks_cos21;
  TProfile* nfvtxt_os_fvtxn_tracks_cos21;
  TProfile* nfvtxt_os_fvtxc_tracks_cos21;
  // --- <<sin(n(phi1))>>
  TProfile* nfvtxt_os_fvtxs_tracks_sin21;
  TProfile* nfvtxt_os_fvtxn_tracks_sin21;
  TProfile* nfvtxt_os_fvtxc_tracks_sin21;
  // --- <<cos(n(phi1+phi2))>>
  TProfile* nfvtxt_os_fvtxs_tracks_cossum22;
  TProfile* nfvtxt_os_fvtxn_tracks_cossum22;
  TProfile* nfvtxt_os_fvtxc_tracks_cossum22;
  // --- <<sin(n(phi1+phi2))>>
  TProfile* nfvtxt_os_fvtxs_tracks_sinsum22;
  TProfile* nfvtxt_os_fvtxn_tracks_sinsum22;
  TProfile* nfvtxt_os_fvtxc_tracks_sinsum22;
  // --- <<cos(n(phi1-phi2-phi3))>>
  TProfile* nfvtxt_os_fvtxs_tracks_cos23;
  TProfile* nfvtxt_os_fvtxn_tracks_cos23;
  TProfile* nfvtxt_os_fvtxc_tracks_cos23;
  // --- <<sin(n(phi1-phi2-phi3))>>
  TProfile* nfvtxt_os_fvtxs_tracks_sin23;
  TProfile* nfvtxt_os_fvtxn_tracks_sin23;
  TProfile* nfvtxt_os_fvtxc_tracks_sin23;

  // --- 3rd harmonic stuff
  // --- 3rd harmonic stuff
  // --- correlation histograms
  // --- <<cos(n(phi1-phi2))>>
  TProfile* nfvtxt_os_fvtxs_tracks_c32;
  TProfile* nfvtxt_os_fvtxn_tracks_c32;
  TProfile* nfvtxt_os_fvtxc_tracks_c32;
  // --- <<cos(n(phi1+phi2-phi3-phi4))>>
  TProfile* nfvtxt_os_fvtxs_tracks_c34;
  TProfile* nfvtxt_os_fvtxn_tracks_c34;
  TProfile* nfvtxt_os_fvtxc_tracks_c34;
  TProfile* nfvtxt_os_fvtxs_tracks_c36;
  TProfile* nfvtxt_os_fvtxn_tracks_c36;
  TProfile* nfvtxt_os_fvtxc_tracks_c36;
  // --- 2-particle scalr product
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c42 ;
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c32 ;
  // --- experimental 4-particle correlations
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c34 ;
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c34a;
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c34b;
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c34c;
  TProfile* nfvtxt_os_fvtxsfvtxn_tracks_c34d;

  // --- acceptance correction histograms
  // --- <<cos(n(phi1))>>
  TProfile* nfvtxt_os_fvtxs_tracks_cos31;
  TProfile* nfvtxt_os_fvtxn_tracks_cos31;
  TProfile* nfvtxt_os_fvtxc_tracks_cos31;
  // --- <<sin(n(phi1))>>
  TProfile* nfvtxt_os_fvtxs_tracks_sin31;
  TProfile* nfvtxt_os_fvtxn_tracks_sin31;
  TProfile* nfvtxt_os_fvtxc_tracks_sin31;
  // --- <<cos(n(phi1+phi2))>>
  TProfile* nfvtxt_os_fvtxs_tracks_cossum32;
  TProfile* nfvtxt_os_fvtxn_tracks_cossum32;
  TProfile* nfvtxt_os_fvtxc_tracks_cossum32;
  // --- <<sin(n(phi1+phi2))>>
  TProfile* nfvtxt_os_fvtxs_tracks_sinsum32;
  TProfile* nfvtxt_os_fvtxn_tracks_sinsum32;
  TProfile* nfvtxt_os_fvtxc_tracks_sinsum32;
  // --- <<cos(n(phi1-phi2-phi3))>>
  TProfile* nfvtxt_os_fvtxs_tracks_cos33;
  TProfile* nfvtxt_os_fvtxn_tracks_cos33;
  TProfile* nfvtxt_os_fvtxc_tracks_cos33;
  // --- <<sin(n(phi1-phi2-phi3))>>
  TProfile* nfvtxt_os_fvtxs_tracks_sin33;
  TProfile* nfvtxt_os_fvtxn_tracks_sin33;
  TProfile* nfvtxt_os_fvtxc_tracks_sin33;

  // --- centrality stuff

  // --- correlation histograms
  // --- <<cos(n(phi1-phi2))>>
  TProfile* centrality_os_fvtxs_tracks_c22;
  TProfile* centrality_os_fvtxn_tracks_c22;
  TProfile* centrality_os_fvtxc_tracks_c22;
  // --- <<cos(n(phi1+phi2-phi3-phi4))>>
  TProfile* centrality_os_fvtxs_tracks_c24;
  TProfile* centrality_os_fvtxn_tracks_c24;
  TProfile* centrality_os_fvtxc_tracks_c24;
  TProfile* centrality_os_fvtxs_tracks_c26;
  TProfile* centrality_os_fvtxn_tracks_c26;
  TProfile* centrality_os_fvtxc_tracks_c26;
  TProfile* centrality_os_fvtxc_tracks_c28;
  // --- 2-particle scalr product
  TProfile* centrality_os_fvtxsfvtxn_tracks_c22 ;
  // --- experimental 4-particle correlations
  TProfile* centrality_os_fvtxsfvtxn_tracks_c24 ;
  TProfile* centrality_os_fvtxsfvtxn_tracks_c24a;
  TProfile* centrality_os_fvtxsfvtxn_tracks_c24b;
  TProfile* centrality_os_fvtxsfvtxn_tracks_c24c;
  TProfile* centrality_os_fvtxsfvtxn_tracks_c24d;

  // --- acceptance correction histograms
  // --- <<cos(n(phi1))>>
  TProfile* centrality_os_fvtxs_tracks_cos21;
  TProfile* centrality_os_fvtxn_tracks_cos21;
  TProfile* centrality_os_fvtxc_tracks_cos21;
  // --- <<sin(n(phi1))>>
  TProfile* centrality_os_fvtxs_tracks_sin21;
  TProfile* centrality_os_fvtxn_tracks_sin21;
  TProfile* centrality_os_fvtxc_tracks_sin21;
  // --- <<cos(n(phi1+phi2))>>
  TProfile* centrality_os_fvtxs_tracks_cossum22;
  TProfile* centrality_os_fvtxn_tracks_cossum22;
  TProfile* centrality_os_fvtxc_tracks_cossum22;
  // --- <<sin(n(phi1+phi2))>>
  TProfile* centrality_os_fvtxs_tracks_sinsum22;
  TProfile* centrality_os_fvtxn_tracks_sinsum22;
  TProfile* centrality_os_fvtxc_tracks_sinsum22;
  // --- <<cos(n(phi1-phi2-phi3))>>
  TProfile* centrality_os_fvtxs_tracks_cos23;
  TProfile* centrality_os_fvtxn_tracks_cos23;
  TProfile* centrality_os_fvtxc_tracks_cos23;
  // --- <<sin(n(phi1-phi2-phi3))>>
  TProfile* centrality_os_fvtxs_tracks_sin23;
  TProfile* centrality_os_fvtxn_tracks_sin23;
  TProfile* centrality_os_fvtxc_tracks_sin23;
  // --- 3rd harmonic stuff
  TProfile* centrality_os_fvtxs_tracks_c32;
  TProfile* centrality_os_fvtxn_tracks_c32;
  TProfile* centrality_os_fvtxc_tracks_c32;
  TProfile* centrality_os_fvtxs_tracks_cos31;
  TProfile* centrality_os_fvtxn_tracks_cos31;
  TProfile* centrality_os_fvtxc_tracks_cos31;
  TProfile* centrality_os_fvtxs_tracks_sin31;
  TProfile* centrality_os_fvtxn_tracks_sin31;
  TProfile* centrality_os_fvtxc_tracks_sin31;
  TProfile* centrality_os_fvtxsfvtxn_tracks_c42;
  TProfile* centrality_os_fvtxsfvtxn_tracks_c32;

  TProfile* centrality_ac_fvtxs_tracks_c34;
  TProfile* centrality_ac_fvtxn_tracks_c34;
  TProfile* centrality_ac_fvtxc_tracks_c34;
  TProfile* centrality_ac_fvtxs_tracks_cossum32;
  TProfile* centrality_ac_fvtxn_tracks_cossum32;
  TProfile* centrality_ac_fvtxc_tracks_cossum32;
  TProfile* centrality_ac_fvtxs_tracks_sinsum32;
  TProfile* centrality_ac_fvtxn_tracks_sinsum32;
  TProfile* centrality_ac_fvtxc_tracks_sinsum32;
  TProfile* centrality_ac_fvtxs_tracks_cos33;
  TProfile* centrality_ac_fvtxn_tracks_cos33;
  TProfile* centrality_ac_fvtxc_tracks_cos33;
  TProfile* centrality_ac_fvtxs_tracks_sin33;
  TProfile* centrality_ac_fvtxn_tracks_sin33;
  TProfile* centrality_ac_fvtxc_tracks_sin33;


  // --- event plane decorrelation stuff
  TProfile* tp1f_special_fvtx_tracks_ab[8];
  TProfile* tp1f_special_fvtx_tracks_aa;
  TProfile* tp1f_special_fvtx_tracks_aa_cos;
  TProfile* tp1f_special_fvtx_tracks_aa_sin;


  TProfile* nfvtxt_tracks_south_qx2;
  TProfile* nfvtxt_tracks_south_qx3;
  TProfile* nfvtxt_tracks_south_qx4;
  TProfile* nfvtxt_tracks_south_qx6;
  TProfile* nfvtxt_tracks_south_qy2;
  TProfile* nfvtxt_tracks_south_qy3;
  TProfile* nfvtxt_tracks_south_qy4;
  TProfile* nfvtxt_tracks_south_qy6;

  TProfile* nfvtxt_tracks_south_inner_qx2;
  TProfile* nfvtxt_tracks_south_inner_qx3;
  TProfile* nfvtxt_tracks_south_inner_qx4;
  TProfile* nfvtxt_tracks_south_inner_qx6;
  TProfile* nfvtxt_tracks_south_inner_qy2;
  TProfile* nfvtxt_tracks_south_inner_qy3;
  TProfile* nfvtxt_tracks_south_inner_qy4;
  TProfile* nfvtxt_tracks_south_inner_qy6;

  TProfile* nfvtxt_tracks_south_outer_qx2;
  TProfile* nfvtxt_tracks_south_outer_qx3;
  TProfile* nfvtxt_tracks_south_outer_qx4;
  TProfile* nfvtxt_tracks_south_outer_qx6;
  TProfile* nfvtxt_tracks_south_outer_qy2;
  TProfile* nfvtxt_tracks_south_outer_qy3;
  TProfile* nfvtxt_tracks_south_outer_qy4;
  TProfile* nfvtxt_tracks_south_outer_qy6;

  TProfile* nfvtxt_tracks_north_qx2;
  TProfile* nfvtxt_tracks_north_qx3;
  TProfile* nfvtxt_tracks_north_qx4;
  TProfile* nfvtxt_tracks_north_qx6;
  TProfile* nfvtxt_tracks_north_qy2;
  TProfile* nfvtxt_tracks_north_qy3;
  TProfile* nfvtxt_tracks_north_qy4;
  TProfile* nfvtxt_tracks_north_qy6;

  TProfile* nfvtxt_tracks_north_inner_qx2;
  TProfile* nfvtxt_tracks_north_inner_qx3;
  TProfile* nfvtxt_tracks_north_inner_qx4;
  TProfile* nfvtxt_tracks_north_inner_qx6;
  TProfile* nfvtxt_tracks_north_inner_qy2;
  TProfile* nfvtxt_tracks_north_inner_qy3;
  TProfile* nfvtxt_tracks_north_inner_qy4;
  TProfile* nfvtxt_tracks_north_inner_qy6;

  TProfile* nfvtxt_tracks_north_outer_qx2;
  TProfile* nfvtxt_tracks_north_outer_qx3;
  TProfile* nfvtxt_tracks_north_outer_qx4;
  TProfile* nfvtxt_tracks_north_outer_qx6;
  TProfile* nfvtxt_tracks_north_outer_qy2;
  TProfile* nfvtxt_tracks_north_outer_qy3;
  TProfile* nfvtxt_tracks_north_outer_qy4;
  TProfile* nfvtxt_tracks_north_outer_qy6;



  TProfile* centrality_tracks_south_qx2;
  TProfile* centrality_tracks_south_qx3;
  TProfile* centrality_tracks_south_qx4;
  TProfile* centrality_tracks_south_qx6;
  TProfile* centrality_tracks_south_qy2;
  TProfile* centrality_tracks_south_qy3;
  TProfile* centrality_tracks_south_qy4;
  TProfile* centrality_tracks_south_qy6;

  TProfile* centrality_tracks_south_inner_qx2;
  TProfile* centrality_tracks_south_inner_qx3;
  TProfile* centrality_tracks_south_inner_qx4;
  TProfile* centrality_tracks_south_inner_qx6;
  TProfile* centrality_tracks_south_inner_qy2;
  TProfile* centrality_tracks_south_inner_qy3;
  TProfile* centrality_tracks_south_inner_qy4;
  TProfile* centrality_tracks_south_inner_qy6;

  TProfile* centrality_tracks_south_outer_qx2;
  TProfile* centrality_tracks_south_outer_qx3;
  TProfile* centrality_tracks_south_outer_qx4;
  TProfile* centrality_tracks_south_outer_qx6;
  TProfile* centrality_tracks_south_outer_qy2;
  TProfile* centrality_tracks_south_outer_qy3;
  TProfile* centrality_tracks_south_outer_qy4;
  TProfile* centrality_tracks_south_outer_qy6;

  TProfile* centrality_tracks_north_qx2;
  TProfile* centrality_tracks_north_qx3;
  TProfile* centrality_tracks_north_qx4;
  TProfile* centrality_tracks_north_qx6;
  TProfile* centrality_tracks_north_qy2;
  TProfile* centrality_tracks_north_qy3;
  TProfile* centrality_tracks_north_qy4;
  TProfile* centrality_tracks_north_qy6;

  TProfile* centrality_tracks_north_inner_qx2;
  TProfile* centrality_tracks_north_inner_qx3;
  TProfile* centrality_tracks_north_inner_qx4;
  TProfile* centrality_tracks_north_inner_qx6;
  TProfile* centrality_tracks_north_inner_qy2;
  TProfile* centrality_tracks_north_inner_qy3;
  TProfile* centrality_tracks_north_inner_qy4;
  TProfile* centrality_tracks_north_inner_qy6;

  TProfile* centrality_tracks_north_outer_qx2;
  TProfile* centrality_tracks_north_outer_qx3;
  TProfile* centrality_tracks_north_outer_qx4;
  TProfile* centrality_tracks_north_outer_qx6;
  TProfile* centrality_tracks_north_outer_qy2;
  TProfile* centrality_tracks_north_outer_qy3;
  TProfile* centrality_tracks_north_outer_qy4;
  TProfile* centrality_tracks_north_outer_qy6;

  TProfile* nfvtxt_recursion[2][maxCorrelator];
  TProfile* centrality_recursion[2][maxCorrelator];
  TProfile* nfvtxt_recoffsets[2][maxHarmonic];
  TProfile* nfvtxt_recoffsets_north[2][maxHarmonic];
  TProfile* nfvtxt_recoffsets_south[2][maxHarmonic];
  TProfile* centrality_recoffsets[2][maxHarmonic];
  TProfile* centrality_recoffsets_north[2][maxHarmonic];
  TProfile* centrality_recoffsets_south[2][maxHarmonic];



};

#endif /* __BOULDERCUMULANTS_H__ */



