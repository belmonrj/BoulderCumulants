#ifndef __BOULDERCUMULANTS_H__
#define __BOULDERCUMULANTS_H__

// standard includes
#include <string>
#include <vector>
#include <TFile.h>
#include <SubsysReco.h>



class Fun4AllHistoManager;
class dAuBES_utils;


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
  void set_output_filename(std::string filename) {_output_filename = filename;} // select output file name externally
  void set_use_runlist(bool b){ _use_runlist = b;} // text file for runs to analyze
  void set_runlist_file(std::string filename) {_runlist_filename = filename;} // name of file for above
  bool is_run_in_list(int runnumber);

 protected:

  // ---

  bool pass_eta_cut(float eta, int bbcz_bin);

  /// current event
  unsigned long _ievent;

  /// verbosity level
  int _verbosity;

  //changes what is being written out
  //bool _create_ttree;
  Fun4AllHistoManager* HistoManager;

  bool _write_bbc;
  bool _write_cnt;
  bool _write_fvtx;
  bool _write_fvtx_clusters;
  /// module output filename
  std::string _output_filename;
  TFile *_output_file;

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



};

#endif /* __BOULDERCUMULANTS_H__ */



