#ifndef __CINT__
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
 
#include <Fun4AllDstInputManager.h>
#include <Fun4AllServer.h>
#include <MasterRecalibratorManager.h>
#include <TBenchmark.h>
#include <TInterpreter.h>
#include <TROOT.h>
#include <TSystem.h>

// emulate using declaration implicit in CINT
using std::string;
using std::cout;
using std::endl;
using std::vector;

// This needs to be defined by the user and is loaded from `modulemacro`. Add a
// definition here so this is valid C++.
void InputData(vector<string> &indata);
#endif

void RunMyMacro(const char *modulemacro = "Run_BoulderCumulantsRun16.C",  // your anataxi macro name
                const char *outfile     = "output_test.root",   // <module_name>_<run>-<sequence>.root
                const int nevnt         = 2000,               // number of events for valgrind checking
                const char *system      = "Run16dAu200CAnVXMBP107") // system type
                //const char *system      = "Run15pAu200FvtxMBPro107") // system type
                //const char *system      = "Run14AuAu200MuonsMBPro104") // system type
                //const char *system      = "Run14AuAu200MuonsMBPro109") // system type
                //const char *system      = "Run14HeAu200MinBias") // system type
{
  int starttime = TDatime().GetTime();
  cout<<"    Start Time: "<<starttime<<endl<<endl;
  string cntfile = "NONE";
  string cwgfile = "NONE";
  string ewgfile = "NONE";
  string dst_allfile = "NONE";
  string dst_evefile = "NONE";
  string dst_fcalfile = "NONE";
  string dst_hbdfile = "NONE";
  string dst_mpcfile = "NONE";
  string dst_mpcexfile = "NONE";
  string dst_rxnpfile = "NONE";
  string dst_svxfile = "NONE";
  string dst_fvtxfile = "NONE";
  string dst_tecfile = "NONE";
  string mwgfile = "NONE";
  string muondstfile = "NONE";
  string pwgfile = "NONE";
  string lpolfile = "NONE";

  bool cnt_included = false;
  bool pwg_included = false;
  bool cwg_included = false;
  bool need_vtx_geo_patch = false;

  if (strcmp(system, "Test") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_ERT_run15pp_200GeV_MuonStandalone_pro106-0000430238-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_fvtxfile = "MWG_ERT_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
    }
  else if (strcmp(system, "Run3dAu200Electron") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libaggro.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libCNT.so");

      cntfile = "CNT_Electron_run3dAu_v03AG_pro48-0000069502-5100.root";
      pwgfile = "PWG_Electron_run3dAu_v03AG_pro48-0000069502-5100.root";
    }
  else if (strcmp(system, "Run3dAu200MinBias") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libaggro.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libCNT.so");

      cntfile = "CNT_MinBias_run3dAu_v03AG_pro48-0000069502-5100.root";
      pwgfile = "PWG_MinBias_run3dAu_v03AG_pro48-0000069502-5100.root";
    }
  else if (strcmp(system, "Run3dAu200Muon") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libaggro.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libCNT.so");

      cntfile = "CNT_Muon_run3dAu_v03AG_pro48-0000069502-5100.root";
      pwgfile = "PWG_Muon_run3dAu_v03AG_pro48-0000069502-5100.root";
    }
  else if (strcmp(system, "Run3dAu200Photon") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libaggro.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libCNT.so");

      cntfile = "CNT_Photon_run3dAu_v03AG_pro48-0000069502-5100.root";
      pwgfile = "PWG_Photon_run3dAu_v03AG_pro48-0000069502-5100.root";
    }
  else if (strcmp(system, "Run4AuAu200") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");

      cntfile = "CNT_MinBias_run4AuAu_Central_200GeV_v01_pro66-0000121548-0003.root";
      pwgfile = "PWG_MinBias_run4AuAu_Central_200GeV_v01_pro66-0000121548-0003.root";
      dst_evefile = "DST_EVE_MinBias_run4AuAu_Central_200GeV_v01_pro66-0000121548-0003.root";
      dst_tecfile = "DST_TEC_MinBias_run4AuAu_Central_200GeV_v01_pro66-0000121548-0003.root";
    }
  else if (strcmp(system, "Run4AuAu62") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");

      cntfile = "CNT_MinBias_run4AuAu_Central_62_4GeV_v02_pro58-0000123039-0000.root";
      pwgfile = "PWG_MinBias_run4AuAu_Central_62_4GeV_v02_pro58-0000123039-0000.root";
      dst_evefile = "DST_EVE_MinBias_run4AuAu_Central_62_4GeV_v02_pro58-0000123039-0000.root";
    }
  else if (strcmp(system, "Run4AuAu62Repass") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_MB_run4auau62_pass2_pro83-0000123039-9000.root";
      pwgfile = "PWG_MB_run4auau62_pass2_pro83-0000123039-9000.root";
      dst_hbdfile = "DST_HBD_run4auau62_pass2_pro83-0000123039-9000.root";
      dst_mpcfile = "DST_MPC_run4auau62_pass2_pro83-0000123039-9000.root";
      dst_rxnpfile = "DST_RXNP_run4auau62_pass2_pro83-0000123039-9000.root";
    }
  else if (strcmp(system, "Run5CuCu200ERT") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libmrpc.so");

      cntfile = "CNT_ERT_run5CuCu_200GeV_pro73-0000154343-9010.root";
      pwgfile = "PWG_ERT_run5CuCu_200GeV_pro73-0000154343-9010.root";
      dst_evefile = "DST_EVE_ERT_run5CuCu_200GeV_pro73-0000154343-9001.root";
      gSystem->Exec("echo CNT_MB_run5CuCu_200GeV_pro73-0000154343-9010.root > cnt_mb.list");
      gSystem->Exec("echo PWG_MB_run5CuCu_200GeV_pro73-0000154343-9010.root > pwg_mb.list");
      gSystem->Exec("echo DST_EVE_MB_run5CuCu_200GeV_pro73-0000154343-9010.root > dst_eve_mb.list");
    }
  else if (strcmp(system, "Run5CuCu200MB") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libmrpc.so");

      cntfile = "CNT_MB_run5CuCu_200GeV_pro73-0000154343-9010.root";
      pwgfile = "PWG_MB_run5CuCu_200GeV_pro73-0000154343-9010.root";
      dst_evefile = "DST_EVE_MB_run5CuCu_200GeV_pro73-0000154343-9001.root";
      gSystem->Exec("echo CNT_ERT_run5CuCu_200GeV_pro73-0000154343-9010.root > cnt_ert.list");
      gSystem->Exec("echo PWG_ERT_run5CuCu_200GeV_pro73-0000154343-9010.root > pwg_ert.list");
      gSystem->Exec("echo DST_EVE_ERT_run5CuCu_200GeV_pro73-0000154343-9010.root > dst_eve_ert.list");
    }
  else if (strcmp(system, "Run5CuCu62") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      cntfile = "CNT_MB_run5CuCu_62GeV_pro71-0000163431-9000.root";
      pwgfile = "PWG_MB_run5CuCu_62GeV_pro71-0000163431-9000.root";
    }
  else if (strcmp(system, "Run5pp200ERT") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("liblpc.so");

      cntfile = "CNT_ERT_run5pp_v02CCJ_pro73-0000175912-0000.root";
      pwgfile = "PWG_ERT_run5pp_v02CCJ_pro73-0000175912-0000.root";
      dst_evefile = "DST_EVE_ALL_run5pp_v02CCJ_pro73-0000175912-0000.root";
      gSystem->Exec("echo PWG_MinBias_run5pp_v02CCJ_pro73-0000175912-0000.root > pwg_minbias.list");
      gSystem->Exec("echo CNT_MinBias_run5pp_v02CCJ_pro73-0000175912-0000.root > cnt_minbias.list");
      dst_tecfile = "DST_TEC_ERT_run5pp_v02CCJ_pro73-0000175912-0000.root";
    }
  else if (strcmp(system, "Run5pp200MinBias") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("liblpc.so");

      cntfile = "CNT_MinBias_run5pp_v02CCJ_pro73-0000175912-0000.root";
      pwgfile = "PWG_MinBias_run5pp_v02CCJ_pro73-0000175912-0000.root";
      dst_evefile = "DST_EVE_ALL_run5pp_v02CCJ_pro73-0000175912-0000.root";
      dst_tecfile = "DST_TEC_MinBias_run5pp_v02CCJ_pro73-0000175912-0000.root";
    }
  else if (strcmp(system, "Run6pp200ERT") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("liblpc.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_ERT_run6pp_200GeV_pro74-0000191068-9000.root";
      pwgfile = "PWG_ERT_run6pp_200GeV_pro74-0000191068-9000.root";
      dst_evefile = "DST_EVE_ALL_run6pp_200GeV_pro74-0000191068-9000.root";
      gSystem->Exec("echo CNT_MB_run6pp_200GeV_pro74-0000191068-9000.root > cnt_mb.list");
      gSystem->Exec("echo PWG_MB_run6pp_200GeV_pro74-0000191068-9000.root > pwg_mb.list");
      dst_tecfile = "DST_TEC_ERT_run6pp_200GeV_pro74-0000191068-9000.root";
    }
  else if (strcmp(system, "Run6pp200MinBias") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("liblpc.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_MB_run6pp_200GeV_pro74-0000191068-9000.root";
      pwgfile = "PWG_MB_run6pp_200GeV_pro74-0000191068-9000.root";
      dst_evefile = "DST_EVE_ALL_run6pp_200GeV_pro74-0000191068-9000.root";
      gSystem->Exec("echo CNT_ERT_run6pp_200GeV_pro74-0000191068-9000.root > cnt_ert.list");
      gSystem->Exec("echo PWG_ERT_run6pp_200GeV_pro74-0000191068-9000.root > pwg_ert.list");
      dst_tecfile = "DST_TEC_MB_run6pp_200GeV_pro74-0000191068-9000.root";
    }
  else if (strcmp(system, "Run6pp200Muon") == 0)
    {
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libmuioo_interface.so");

      cntfile = "CNT_MU_run6pp_200GeV_pro74-0000191068-9000.root";
      pwgfile = "PWG_MU_run6pp_200GeV_pro74-0000191068-9000.root";
      mwgfile = "MWG_MU_run6pp_200GeV_pro74-0000191068-9000.root";
      gSystem->Exec("echo CNT_MB_run6pp_200GeV_pro74-0000191068-9000.root > cnt_mb.list");
      gSystem->Exec("echo PWG_MB_run6pp_200GeV_pro74-0000191068-9000.root > pwg_mb.list");
    }
  else if (strcmp(system, "Run6pp62") == 0)
    {
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("liblpc.so");

      cntfile = "CNT_run6pp_62GeV_pro73-0000206041-9000.root";
      pwgfile = "PWG_run6pp_62GeV_pro73-0000206041-9000.root";
      dst_mpcfile = "DST_MPC_run6pp_62GeV_pro73-0000206041-9000.root";
      dst_evefile = "DST_EVE_run6pp_62GeV_pro73-0000206041-9000.root";
    }
  else if (strcmp(system, "Run6pp62MWG") == 0)
    {
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("liblpc.so");

      mwgfile = "MWG_run6pp_62GeV_pro73-0000206041-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run7AuAu200") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libHardpDST.so");
      gSystem->Load("libert.so");

      cwgfile = "CWG_MB_run7AuAu_Central_200GeV_pro78-0000228411-9000.root";
      ewgfile = "EWG_MB_run7AuAu_Central_200GeV_pro78-0000228411-9000.root";
      dst_evefile = "DST_EVE_ALL_run7AuAu_Central_200GeV_pro78-0000228411-9000.root";
      dst_mpcfile = "DST_MPC_MB_run7AuAu_Central_200GeV_pro78-0000228411-9000.root";
      dst_rxnpfile = "DST_RXNP_MB_run7AuAu_Central_200GeV_pro78-0000228411-9000.root";
      mwgfile = "MWG_MB_run7AuAu_Muon_200GeV_pro80__anatrain_taxi172-0000228411-9000.root";
    }
  else if (strcmp(system, "Run7AuAu200EWG") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libHardpDST.so");
      gSystem->Load("libert.so");

      ewgfile = "EWG_MB_run7AuAu_Central_200GeV_pro78-0000228411-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run7AuAu200Muon") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libMWG_interface.so");

      mwgfile = "MWG_MB_run7AuAu_Muon_200GeV_pro80__anatrain_taxi172-0000228411-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run7AuAu200MuonSwap") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libMWG_interface.so");

      mwgfile = "MWG_MB_run7AuAu_Muon_200GeV_pro80swap-0000229595-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run7AuAu200UP") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libHardpDST.so");
      gSystem->Load("libert.so");
      cntfile = "CNT_UP_run7AuAu_Central_200GeV_pro78-0000228411-9000.root";
      pwgfile = "PWG_UP_run7AuAu_Central_200GeV_pro78-0000228411-9000.root";
    }
  else if (strcmp(system, "Run8dAu200ERT") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_ERT_run8dAu_Central_pro82-0000246548-9000.root";
      mwgfile = "MWG_ERT_run8dAu_muon_pro81__anatrain_taxi244-0000246548-9000.root";
      pwgfile = "PWG_ERT_run8dAu_Central_pro82-0000246548-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run8dAu_200GeV_RXNP_pro82-0000246548-9000.root";
      ewgfile = "EWG_ERT_run8dAu_Central_pro82-0000246548-9000.root";
      dst_evefile = "DST_EVE_ALL_run8dAu_200GeV_RXNP_pro82-0000246548-9000.root";
      dst_rxnpfile = "DST_RXNP_ERT_run8dAu_200GeV_RXNP_pro82-0000246548-9000.root";
      gSystem->Exec("echo CNT_MB_run8dAu_Central_pro82-0000246548-9000.root > cnt_mb.list");
      gSystem->Exec("echo PWG_MB_run8dAu_Central_pro82-0000246548-9000.root > pwg_mb.list");
      gSystem->Exec("echo DST_MPC_MB_run8dAu_muon_pro81-0000246548-9000.root > dst_mpc_mb.list");
    }
  else if (strcmp(system, "Run8dAu200MinBias") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
 
      cntfile = "CNT_MB_run8dAu_Central_pro82-0000246548-9000.root";
      mwgfile = "MWG_MB_run8dAu_muon_pro81__anatrain_taxi244-0000246548-9000.root";
      pwgfile = "PWG_MB_run8dAu_Central_pro82-0000246548-9000.root";
      dst_fcalfile = "DST_FCAL_ALL_run8dAu_MPC_200GeV_pro82-0000246548-9000.root";
      ewgfile = "EWG_MB_run8dAu_Central_pro82-0000246548-9000.root";
      dst_mpcfile = "DST_MPC_MB_run8dAu_200GeV_RXNP_pro82-0000246548-9000.root";
      dst_evefile = "DST_EVE_ALL_run8dAu_200GeV_RXNP_pro82-0000246548-9000.root";
      dst_rxnpfile = "DST_RXNP_MB_run8dAu_200GeV_RXNP_pro82-0000246548-9000.root";
    }
  else if (strcmp(system, "Run8dAu200MPC") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_MPC_run8dAu_Central_pro82-0000246548-9000.root";
      mwgfile = "MWG_MPC_run8dAu_muon_pro81__anatrain_taxi244-0000246548-9000.root";
      pwgfile = "PWG_MPC_run8dAu_Central_pro82-0000246548-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run8dAu_200GeV_RXNP_pro82-0000246548-9000.root";
      dst_rxnpfile = "DST_RXNP_MPC_run8dAu_200GeV_RXNP_pro82-0000246548-9000.root";
      gSystem->Exec("echo CNT_MB_run8dAu_Central_pro82-0000246548-9000.root > cnt_mb.list");
      gSystem->Exec("echo PWG_MB_run8dAu_Central_pro82-0000246548-9000.root > pwg_mb.list");
      gSystem->Exec("echo DST_MPC_MB_run8dAu_muon_pro81-0000246548-9000.root > dst_mpc_mb.list");
    }
  else if (strcmp(system, "Run8dAu200Muon") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
 
      cntfile = "CNT_MU_run8dAu_Central_pro82-0000246547-9000.root";
      dst_mpcfile = "DST_MPC_MU_run8dAu_MPC_200GeV_pro82-0000246547-9000.root";
      mwgfile = "MWG_MU_run8dAu_muon_pro81__anatrain_taxi244-0000246547-9000.root";
      pwgfile = "PWG_MU_run8dAu_Central_pro82-0000246547-9000.root";
      dst_evefile = "DST_ALL_run8dAu_Central_pro82-0000246547-9000.root";
      gSystem->Exec("echo CNT_MB_run8dAu_Central_pro82-0000246547-9000.root> cnt_mb.list");
      gSystem->Exec("echo PWG_MB_run8dAu_Central_pro82-0000246547-9000.root > pwg_mb.list");
      gSystem->Exec("echo DST_MPC_MB_run8dAu_muon_pro81-0000246547-9000.root > dst_mpc_mb.list");
    }
  else if (strcmp(system, "Run8pp200DstEve") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("liblpc.so");
 
      dst_evefile = "DST_EVE_ALL_run8pp_200GeV_pro82-0000257850-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run8pp200ERT") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("liblpc.so");
 
      cntfile = "CNT_ERT_run8pp_200GeV_pro82-0000257850-9000.root";
      mwgfile = "MWG_ERT_run8pp_200GeV_pro82__anatrain_taxi244-0000257850-9000.root";
      pwgfile = "PWG_ERT_run8pp_200GeV_pro82-0000257850-9000.root";
      ewgfile = "EWG_ERT_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_evefile = "DST_EVE_ALL_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_tecfile = "DST_TEC_ERT_run8pp_200GeV_pro82-0000257850-9000.root";
      gSystem->Exec("echo CNT_MB_run8pp_200GeV_pro82-0000257850-9000.root > cnt_mb.list");
      gSystem->Exec("echo PWG_MB_run8pp_200GeV_pro82-0000257850-9000.root > pwg_mb.list");
      gSystem->Exec("echo DST_MPC_MB_run8pp_200GeV_pro82-0000257850-9000.root > dst_mpc_mb.list");

    }
  else if (strcmp(system, "Run8pp200MinBias") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("liblpc.so");

      cntfile = "CNT_MB_run8pp_200GeV_pro82-0000257850-9000.root";
      mwgfile = "MWG_MB_run8pp_200GeV_pro82__anatrain_taxi244-0000257850-9000.root";
      pwgfile = "PWG_MB_run8pp_200GeV_pro82-0000257850-9000.root";
      ewgfile = "EWG_MB_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_mpcfile = "DST_MPC_MB_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_evefile = "DST_EVE_ALL_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_tecfile = "DST_TEC_MB_run8pp_200GeV_pro82-0000257850-9000.root";
    }
  else if (strcmp(system, "Run8pp200MPC") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("liblpc.so");

      cntfile = "CNT_MPC_run8pp_200GeV_pro82-0000257850-9000.root";
      pwgfile = "PWG_MPC_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_evefile = "DST_EVE_ALL_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run8pp_200GeV_pro82-0000257850-9000.root";
      gSystem->Exec("echo CNT_MB_run8pp_200GeV_pro82-0000257850-9000.root > cnt_mb.list");
      gSystem->Exec("echo PWG_MB_run8pp_200GeV_pro82-0000257850-9000.root > pwg_mb.list");
      gSystem->Exec("echo DST_MPC_MB_run8pp_200GeV_pro82-0000257850-9000.root > dst_mpc_mb.list");
    }
  else if (strcmp(system, "Run8pp200MT") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("liblpc.so");

      cntfile = "CNT_MT_run8pp_200GeV_pro82-0000257850-9000.root";
      mwgfile = "MWG_MT_run8pp_200GeV_pro82__anatrain_taxi244-0000257850-9000.root";
      pwgfile = "PWG_MT_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_mpcfile = "DST_MPC_MT_run8pp_200GeV_pro82-0000257850-9000.root";
    }
  else if (strcmp(system, "Run8pp200Muon") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("liblpc.so");

      cntfile = "CNT_MU_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_mpcfile = "DST_MPC_MU_run8pp_MPC_200GeV_pro82-0000257850-9000.root";
      mwgfile = "MWG_MU_run8pp_200GeV_pro82__anatrain_taxi244-0000257850-9000.root";
      pwgfile = "PWG_MU_run8pp_200GeV_pro82-0000257850-9000.root";
      dst_evefile = "DST_EVE_ALL_run8pp_200GeV_pro82-0000257850-9000.root";
      gSystem->Exec("echo CNT_MB_run8pp_200GeV_pro82-0000257850-9000.root > cnt_mb.list");
      gSystem->Exec("echo PWG_MB_run8pp_200GeV_pro82-0000257850-9000.root > pwg_mb.list");
      gSystem->Exec("echo DST_MPC_MB_run8pp_200GeV_pro82-0000257850-9000.root > dst_mpc_mb.list");
    }
  else if (strcmp(system, "Run9pp500ERT") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_ERT_run9pp_500GeV_pro83-0000276875-9000.root";
      dst_hbdfile = "DST_HBD_ERT_run9pp_500GeV_pro83-0000276875-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run9pp_500GeV_pro83-0000276875-9000.root";
      dst_tecfile = "DST_TEC_ERT_run9pp_500GeV_pro83-0000276875-9000.root";
      mwgfile = "MWG_ERT_run9pp_Muon_500GeV_pro85-0000276875-9000.root";
      pwgfile = "PWG_ERT_run9pp_500GeV_pro83-0000276875-9000.root";
    }
  else if (strcmp(system, "Run9pp500MinBias") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_MB_run9pp_500GeV_pro83-0000276875-9000.root";
      dst_hbdfile = "DST_HBD_MB_run9pp_500GeV_pro83-0000276875-9000.root";
      dst_mpcfile = "DST_MPC_MB_run9pp_500GeV_pro83-0000276875-9000.root";
      dst_tecfile = "DST_TEC_MB_run9pp_500GeV_pro83-0000276875-9000.root";
      mwgfile = "MWG_MB_run9pp_Muon_500GeV_pro85-0000276875-9000.root";
      pwgfile = "PWG_MB_run9pp_500GeV_pro83-0000276875-9000.root";
    }
  else if (strcmp(system, "Run9pp500MPC") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_MPC_run9pp_500GeV_pro83-0000276875-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run9pp_500GeV_pro83-0000276875-9000.root";
      mwgfile = "MWG_MPC_run9pp_Muon_500GeV_pro85-0000276875-9000.root";
      pwgfile = "PWG_MPC_run9pp_500GeV_pro83-0000276875-9000.root";
    }
  else if (strcmp(system, "Run9pp500Muon") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_MU_run9pp_500GeV_pro83-0000276875-9000.root";
      dst_mpcfile = "DST_MPC_MU_run9pp_500GeV_pro83-0000276875-9000.root";
      mwgfile = "MWG_MU_run9pp_Muon_500GeV_pro85-0000276875-9000.root";
      pwgfile = "PWG_MU_run9pp_500GeV_pro83-0000276875-9000.root";
    }
  else if (strcmp(system, "Run9pp500MWGMinBias") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      mwgfile = "MWG_MB_run9pp_Muon_500GeV_pro85-0000276875-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run9pp500MWGMuon") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      mwgfile = "MWG_MU_run9pp_Muon_500GeV_pro85-0000276875-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run9pp200ERT") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_ERT_run9pp_200GeV_pro83-0000283353-9000.root";
      dst_hbdfile = "DST_HBD_ERT_run9pp_200GeV_pro83-0000283353-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run9pp_200GeV_pro83-0000283353-9000.root";
      dst_tecfile = "DST_TEC_ERT_run9pp_200GeV_pro83-0000283353-9000.root";
      dst_evefile = "DST_EVE_ALL_run9pp_200GeV_pro83-0000283353-9000.root";
      mwgfile = "MWG_ERT_run9pp_Muon_200GeV_pro85-0000283353-9000.root";
      pwgfile = "PWG_ERT_run9pp_200GeV_pro83-0000283353-9000.root";
      gSystem->Exec("echo CNT_MB_run9pp_200GeV_pro83-0000283353-9000.root > cnt_mb.list");
      gSystem->Exec("echo PWG_MB_run9pp_200GeV_pro83-0000283353-9000.root > pwg_mb.list");
      gSystem->Exec("echo MWG_MB_run9pp_200GeV_pro83-0000283353-9000.root > mwg_mb.list");
      gSystem->Exec("echo DST_HBD_MB_run9pp_200GeV_pro83-0000283353-9000.root > dst_hbd_mb.list");
      gSystem->Exec("echo DST_MPC_MB_run9pp_200GeV_pro83-0000283353-9000.root > dst_mpc_mb.list");
      gSystem->Exec("echo DST_TEC_MB_run9pp_200GeV_pro83-0000283353-9000.root > dst_tec_mb.list");
    }
  else if (strcmp(system, "Run9pp200MinBias") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("librecal.so");
      gSystem->Load("liblpc.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_MB_run9pp_200GeV_pro83-0000283353-9000.root";
      dst_hbdfile = "DST_HBD_MB_run9pp_200GeV_pro83-0000283353-9000.root";
      dst_mpcfile = "DST_MPC_MB_run9pp_200GeV_pro83-0000283353-9000.root";
      dst_tecfile = "DST_TEC_MB_run9pp_200GeV_pro83-0000283353-9000.root";
      dst_evefile = "DST_EVE_ALL_run9pp_200GeV_pro83-0000283353-9000.root";
      mwgfile = "MWG_MB_run9pp_Muon_200GeV_pro85-0000283353-9000.root";
      pwgfile = "PWG_MB_run9pp_200GeV_pro83-0000283353-9000.root";
    }
  else if (strcmp(system, "Run9pp200MPC") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_MPC_run9pp_200GeV_pro83-0000283353-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run9pp_200GeV_pro83-0000283353-9000.root";
      mwgfile = "MWG_MPC_run9pp_Muon_200GeV_pro85-0000283353-9000.root";
      pwgfile = "PWG_MPC_run9pp_200GeV_pro83-0000283353-9000.root";
    }
  else if (strcmp(system, "Run9pp200Muon") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_MU_run9pp_200GeV_pro83-0000283353-9000.root";
      dst_mpcfile = "DST_MPC_MU_run9pp_200GeV_pro83-0000283353-9000.root";
      mwgfile = "MWG_MU_run9pp_Muon_200GeV_pro85-0000283353-9000.root";
      pwgfile = "PWG_MU_run9pp_200GeV_pro83-0000283353-9000.root";
    }
  else if (strcmp(system, "Run9pp200MWGMinBias") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      mwgfile = "MWG_MB_run9pp_Muon_200GeV_pro85-0000283353-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run9pp200MWGMuon") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      mwgfile = "MWG_MU_run9pp_Muon_200GeV_pro85-0000283353-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run9pp200ALL") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("librecal.so");
      gSystem->Load("liblpc.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      dst_evefile = "DST_EVE_ALL_run9pp_200GeV_pro83-0000283353-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run9pp500ALL") == 0)
    {
      gSystem->Load("libMWGOO.so");
      gSystem->Load("librecal.so");
      gSystem->Load("liblpc.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      dst_evefile = "DST_EVE_ALL_run9pp_500GeV_pro83-0000276875-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run10AuAu200MinBias") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_MB_run10auau200_pro84-0000301989-9000.root";
      dst_evefile = "DST_EVE_MB_run10auau200_pro84-0000301989-9000.root";
      dst_mpcfile = "DST_MPC_MB_run10auau200_pro84-0000301989-9000.root";
      dst_rxnpfile = "DST_RXNP_MB_run10auau200_pro84-0000301989-9000.root";
      mwgfile = "MWG_MB_run10AuAu_Muon_200GeV_pro85-0000301989-9000.root";
    }
  else if (strcmp(system, "Run10AuAu200OT") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_OT_run10auau200_pro84-0000301989-9000.root";
      dst_evefile = "DST_EVE_OT_run10auau200_pro84-0000301989-9000.root";
      dst_mpcfile = "DST_MPC_OT_run10auau200_pro84-0000301989-9000.root";
      dst_rxnpfile = "DST_RXNP_OT_run10auau200_pro84-0000301989-9000.root";
      mwgfile = "MWG_OT_run10AuAu_Muon_200GeV_pro85-0000301989-9000.root";
    }
  else if (strcmp(system, "Run10AuAu200Muon") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libMWG_interface.so");

      mwgfile = "MWG_MB_run10AuAu_Muon_200GeV_pro85-0000301989-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run10AuAu200MuonsUPPro85") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libMWG_interface.so");

      mwgfile = "MWG_UP_run10AuAu_Muon_200GeV_pro85-0000301989-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run10AuAu200Up") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_UP_run10auau200_pro84-0000301989-9000.root";
      dst_mpcfile = "DST_MPC_UP_run10auau200_pro84-0000301989-9000.root";
      dst_rxnpfile = "DST_RXNP_UP_run10auau200_pro84-0000301989-9000.root";
      mwgfile = "MWG_UP_run10AuAu_Muon_200GeV_pro85-0000301989-9000.root";
    }
  else if (strcmp(system, "Run10AuAu62MinBias") == 0)
    {
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_MB_run10auau062_pro84-0000311553-9000.root";
      dst_evefile = "DST_EVE_MB_run10auau062_pro84-0000311553-9000.root";
      dst_mpcfile = "DST_MPC_MB_run10auau062_pro84-0000311553-9000.root";
      dst_rxnpfile = "DST_RXNP_MB_run10auau062_pro84-0000311553-9000.root";
      mwgfile = "MWG_ALL_run10AuAu_Muon_062GeV_pro85-0000311553-9000.root";
    }
  else if (strcmp(system, "Run10AuAu39MinBias") == 0)
    {
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_MB_run10auau039_pro84-0000314470-9000.root";
      dst_evefile = "DST_EVE_MB_run10auau039_pro84-0000314470-9000.root";
      dst_mpcfile = "DST_MPC_MB_run10auau039_pro84-0000314470-9000.root";
      dst_rxnpfile = "DST_RXNP_MB_run10auau039_pro84-0000314470-9000.root";
      mwgfile = "MWG_ALL_run10AuAu_Muon_039GeV_pro85-0000314470-9000.root";
    }
  else if (strcmp(system, "Run10AuAu7MB") == 0)
    {
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
 
      cntfile = "CNT_MB_run10auau007_pro84-0000318778-9000.root";
      dst_evefile = "DST_EVE_MB_run10auau007_pro84-0000318778-9000.root";
      dst_mpcfile = "DST_MPC_MB_run10auau007_pro84-0000318778-9000.root";
      dst_rxnpfile = "DST_RXNP_MB_run10auau007_pro84-0000318778-9000.root";
    }
  else if (strcmp(system, "Run10AuAu7OT") == 0)
    {
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
 
      cntfile = "CNT_OT_run10auau007_pro84-0000318778-9000.root";
      dst_evefile = "DST_EVE_OT_run10auau007_pro84-0000318778-9000.root";
      dst_mpcfile = "DST_MPC_OT_run10auau007_pro84-0000318778-9000.root";
      dst_rxnpfile = "DST_RXNP_OT_run10auau007_pro84-0000318778-9000.root";
    }
  else if (strcmp(system, "Run10AuAuZFMinBias") == 0)
    {
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      cntfile = "CNT_MB_run10auau_zerof_pro85-0000307669-9000.root";
      dst_evefile = "DST_EVE_MB_run10auau_zerof_pro85-0000307669-9000.root";
      dst_mpcfile = "DST_MPC_MB_run10auau_zerof_pro85-0000307669-9000.root";
      dst_rxnpfile = "DST_RXNP_MB_run10auau_zerof_pro85-0000307669-9000.root";
    }
  else if (strcmp(system, "Run10AuAuZFOT") == 0)
    {
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      cntfile = "CNT_OT_run10auau_zerof_pro85-0000307669-9000.root";
      dst_evefile = "DST_EVE_OT_run10auau_zerof_pro85-0000307669-9000.root";
      dst_mpcfile = "DST_MPC_OT_run10auau_zerof_pro85-0000307669-9000.root";
      dst_rxnpfile = "DST_RXNP_OT_run10auau_zerof_pro85-0000307669-9000.root";
    }
  else if (strcmp(system, "Run10AuAuZFUP") == 0)
    {
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      cntfile = "CNT_UP_run10auau_zerof_pro85-0000307669-9000.root";
      dst_evefile = "DST_EVE_UP_run10auau_zerof_pro85-0000307669-9000.root";
      dst_mpcfile = "DST_MPC_UP_run10auau_zerof_pro85-0000307669-9000.root";
      dst_rxnpfile = "DST_RXNP_UP_run10auau_zerof_pro85-0000307669-9000.root";
    }
  else if (strcmp(system, "Run11AuAu19MinBias") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libsvx.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_MB_run11auau_019GeV_pro89-0000341933-9000.root";
      dst_evefile = "DST_EVE_MB_run11auau_019GeV_pro89-0000341933-9000.root";
      dst_mpcfile = "DST_MPC_MB_run11auau_019GeV_pro89-0000341933-9000.root";
      dst_svxfile = "DST_SVX_MB_run11auau_019GeV_pro89-0000341933-9000.root";
      mwgfile = "MWG_MB_run11auau_Muon_019GeV_pro88-0000341933-9000.root";
     }
  else if (strcmp(system, "Run11AuAu27MinBias") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libsvx.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_MB_run11auau_027GeV_pro89-0000350342-9000.root";
      dst_evefile = "DST_EVE_MB_run11auau_027GeV_pro89-0000350342-9000.root";
      dst_mpcfile = "DST_MPC_MB_run11auau_027GeV_pro89-0000350342-9000.root";
      dst_svxfile = "DST_SVX_MB_run11auau_027GeV_pro89-0000350342-9000.root";
      mwgfile = "MWG_MB_run11auau_Muon_027GeV_pro88-0000350342-9000.root";
     }
  else if (strcmp(system, "Run11AuAu27MBPro89") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libert.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libSvxDstQA.so");

      cntfile = "CNT_MB_run11auau_027GeV_pro89-0000350342-9000.root";
      dst_evefile = "DST_EVE_MB_run11auau_027GeV_pro89-0000350342-9000.root";
      dst_mpcfile = "DST_MPC_MB_run11auau_027GeV_pro89-0000350342-9000.root";
      dst_svxfile = "DST_SVX_MB_run11auau_027GeV_pro89-0000350342-9000.root";
      mwgfile = "MWG_MB_run11auau_Muon_027GeV_pro88-0000350342-9000.root";
     }
  else if (strcmp(system, "Run11AuAu27MuonsMBPro88") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("libspin.so");
      gSystem->Load("librecal.so");

      mwgfile = "MWG_MB_run11auau_Muon_027GeV_pro88-0000350342-9000.root";
      cnt_included = true;
     }
  else if (strcmp(system, "Run11AuAu200MinBiasOld") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libsvx.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_MB_run11auau_200GeV_pro90-0000349676-9000.root";
      dst_evefile = "DST_EVE_MB_run11auau_200GeV_pro90-0000349676-9000.root";
      dst_mpcfile = "DST_MPC_MB_run11auau_200GeV_pro90-0000349676-9000.root";
      dst_svxfile = "DST_SVX_MB_run11auau_200GeV_pro90-0000349676-9000.root";
     }
  else if (strcmp(system, "Run11AuAu200MinBias") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libsvx.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_MB_run11auau_200GeV_pro98-0000348165-9000.root";
      dst_evefile = "DST_EVE_MB_run11auau_200GeV_pro98-0000348165-9000.root";
      dst_mpcfile = "DST_MPC_MB_run11auau_200GeV_pro90-0000348165-9000.root";
      dst_svxfile = "DST_SVX_MB_run11auau_200GeV_pro98-0000348165-9000.root";

     }
  else if (strcmp(system, "Run11AuAu200MinBiasPro101") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libSvxDstQA.so");

      cntfile = "CNT_MB_run11auau_200GeV_pro101-0000343786-9000.root";
      dst_evefile = "DST_EVE_MB_run11auau_200GeV_pro101-0000343786-9000.root";
      dst_mpcfile = "DST_MPC_MB_run11auau_200GeV_pro90-0000343786-9000.root";
      dst_svxfile = "DST_SVX_MB_run11auau_200GeV_pro101-0000343786-9000.root";
     }
  else if (strcmp(system, "Run11AuAu200CAERTPro101") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libSvxDstQA.so");

      cntfile = "CNT_ERT_run11auau_200GeV_pro101-0000343786-9000.root";
      dst_evefile = "DST_EVE_ERT_run11auau_200GeV_pro101-0000343786-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run11auau_200GeV_pro90-0000343786-9000.root";
      dst_svxfile = "DST_SVX_ERT_run11auau_200GeV_pro101-0000343786-9000.root";
      gSystem->Exec("echo CNT_MB_run11auau_200GeV_pro101-0000343786-9000.root > cnt_mb.list");
      gSystem->Exec("echo DST_EVE_MB_run11auau_200GeV_pro101-0000343786-9000.root > dst_eve_mb.list");
      gSystem->Exec("echo DST_MPC_MB_run11auau_200GeV_pro90-0000343786-9000.root > dst_mpc_mb.list");
    }
  else if (strcmp(system, "Run11AuAu200CAOTPro101") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libSvxDstQA.so");

      cntfile = "CNT_OT_run11auau_200GeV_pro101-0000343786-9000.root";
      dst_evefile = "DST_EVE_OT_run11auau_200GeV_pro101-0000343786-9000.root";
      dst_mpcfile = "DST_MPC_OT_run11auau_200GeV_pro90-0000343786-9000.root";
      dst_svxfile = "DST_SVX_OT_run11auau_200GeV_pro101-0000343786-9000.root";
    }
  else if (strcmp(system, "Run11AuAu200ZFMinBias") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libsvx.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWG_interface.so");

      cntfile = "CNT_MB_run11auau_ZF_ana334-0000343349-9000.root";
      dst_evefile = "DST_EVE_MB_run11auau_ZF_ana334-0000343349-9000.root";
      dst_mpcfile = "DST_MPC_MB_run11auau_ZF_ana334-0000343349-9000.root";
      dst_svxfile = "DST_SVX_MB_run11auau_ZF_ana334-0000343349-9000.root";
    }
  else if (strcmp(system, "Run11AuAu200ZFERT") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libCNT.so");
      gSystem->Load("libsvx.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWG_interface.so");


      cntfile = "CNT_ERT_run11auau_ZF_ana334-0000343349-9000.root";
      dst_evefile = "DST_EVE_ERT_run11auau_ZF_ana334-0000343349-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run11auau_ZF_ana334-0000343349-9000.root";
      dst_svxfile = "DST_SVX_ERT_run11auau_ZF_ana334-0000343349-9000.root";
    }

  else if (strcmp(system, "Run11AuAu200MWGMinBias") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libmutrg.so");

      mwgfile = "MWG_MB_run11auau_Muon_200GeV_pro88-0000349676-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG                       
    }
  else if (strcmp(system, "Run11AuAu200MWGERT") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libmutrg.so");

      mwgfile = "MWG_ERT_run11auau_Muon_200GeV_pro88-0000349676-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG                       
    }
  else if (strcmp(system, "Run11pp500ERT") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_ERT_run11pp_500GeV_pro90-0000338145-9000.root";
      dst_evefile = "DST_EVE_ERT_run11pp_500GeV_pro90-0000338145-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run11pp_500GeV_pro90-0000338145-9000.root";
      mwgfile = "MWG_ERT_run11pp_500GeV_pro88-0000338145-9000.root";
    }
  else if (strcmp(system, "Run11pp500MinBias") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      cntfile = "CNT_MB_run11pp_500GeV_pro90-0000338145-9000.root";
      dst_evefile = "DST_EVE_MB_run11pp_500GeV_pro90-0000338145-9000.root";
      dst_mpcfile = "DST_MPC_MB_run11pp_500GeV_pro90-0000338145-9000.root";
      mwgfile = "MWG_MB_run11pp_500GeV_pro88-0000338145-9000.root";
    }
  else if (strcmp(system, "Run11pp500MuonsERTP86") == 0) // same pro.86 as other Run11pp500MWG datasets
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      dst_mpcfile = "DST_MPC_ERT_run11pp_Muon_500GeV_pro86-0000338145-9000.root";
      mwgfile = "MWG_ERT_run11pp_Muon_500GeV_pro86-0000338145-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run11pp500MWGMinBias") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      dst_mpcfile = "DST_MPC_MB_run11pp_Muon_500GeV_pro86-0000338145-9000.root";
      mwgfile = "MWG_MB_run11pp_Muon_500GeV_pro86-0000338145-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run11pp500MWGMPC") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      dst_mpcfile = "DST_MPC_MPC_run11pp_Muon_500GeV_pro86-0000338145-9000.root";
      mwgfile = "MWG_MPC_run11pp_Muon_500GeV_pro86-0000338145-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run11pp500MWGMuon") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");

      dst_mpcfile = "DST_MPC_MU_run11pp_Muon_500GeV_pro86-0000338145-9000.root";
      mwgfile = "MWG_MU_run11pp_Muon_500GeV_pro86-0000338145-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12pp200ERTPro101") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libert.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWGOO.so");

      cntfile = "CNT_ERT_run12pp_200GeV_pro101-0000360934-9000.root";
      dst_evefile = "DST_EVE_ERT_run12pp_200GeV_pro101-0000360934-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run12pp_200GeV_pro91-0000360934-9000.root";
      dst_svxfile = "DST_SVX_ERT_run12pp_200GeV_pro101-0000360934-9000.root";
      mwgfile = "MWG_ERT_run12pp_200GeV_pro91-0000360934-9000.root";
    }
  else if (strcmp(system, "Run12pp200MBPro101") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libert.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWGOO.so");

      cntfile = "CNT_MB_run12pp_200GeV_pro101-0000360934-9000.root";
      dst_evefile = "DST_EVE_MB_run12pp_200GeV_pro101-0000360934-9000.root";
      dst_mpcfile = "DST_MPC_MB_run12pp_200GeV_pro91-0000360934-9000.root";
      dst_svxfile = "DST_SVX_MB_run12pp_200GeV_pro101-0000360934-9000.root";
      mwgfile = "MWG_MB_run12pp_200GeV_pro91-0000360934-9000.root";
    }
  else if (strcmp(system, "Run12pp200MPCPro101") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libert.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWGOO.so");

      cntfile = "CNT_MPC_run12pp_200GeV_pro101-0000360934-9000.root";
      dst_evefile = "DST_EVE_MPC_run12pp_200GeV_pro101-0000360934-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run12pp_200GeV_pro91-0000360934-9000.root";
      dst_svxfile = "DST_SVX_MPC_run12pp_200GeV_pro101-0000360934-9000.root";
      mwgfile = "MWG_MPC_run12pp_200GeV_pro91-0000360934-9000.root";
    }
  else if (strcmp(system, "Run12pp200MUPro101") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libert.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWGOO.so");

      cntfile = "CNT_MU_run12pp_200GeV_pro101-0000360934-9000.root";
      dst_evefile = "DST_EVE_MU_run12pp_200GeV_pro101-0000360934-9000.root";
      dst_mpcfile = "DST_MPC_MU_run12pp_200GeV_pro91-0000360934-9000.root";
      dst_svxfile = "DST_SVX_MU_run12pp_200GeV_pro101-0000360934-9000.root";
      mwgfile = "MWG_MU_run12pp_200GeV_pro91-0000360934-9000.root";
    }
  else if (strcmp(system, "Run12pp200OTPro101") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libert.so");
      gSystem->Load("libSvxDstQA.so");
      gSystem->Load("libMWGOO.so");

      cntfile = "CNT_OT_run12pp_200GeV_pro101-0000360934-9000.root";
      dst_evefile = "DST_EVE_OT_run12pp_200GeV_pro101-0000360934-9000.root";
      dst_mpcfile = "DST_MPC_OT_run12pp_200GeV_pro91-0000360934-9000.root";
      dst_svxfile = "DST_SVX_OT_run12pp_200GeV_pro101-0000360934-9000.root";
      mwgfile = "MWG_OT_run12pp_200GeV_pro91-0000360934-9000.root";
    }
  else if (strcmp(system, "Run12pp500FastMWG") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("libBbcMultipleVtx.so");

      mwgfile = "MWG_MU_run12_online_muon-0000366052-0000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12UU200FastMWG") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libmutrg.so");

      mwgfile = "MWG_run12_online_muon-0000370997-0000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12UU200FastCentral") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libCNT.so");

      cntfile = "CNT_run12_online_central-0000371003-0000.root";
      dst_evefile = "DST_EVE_run12_online_central-0000371003-0000.root";
      dst_mpcfile = "DST_MPC_run12_online_central-0000371003-0000.root";
    }
  else if (strcmp(system, "Run12CuAu200MWGMuonPro91") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libmutrg.so");

      mwgfile = "MWG_MU_run12CuAu_Muons_200GeV_pro91-0000376084-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12CuAu200MWGMuonPro100") == 0)
    {
      gSystem->Load("libfun4all");
      gSystem->Load("libmutoo_subsysreco" );
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("liblvl2");
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load("libmutrg");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");
      gSystem->Load("libSvxDstQA.so");

      mwgfile = "MWG_MU_run12CuAu_200GeV_Muons_pro100-0000377309-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12CuAu200MWGMBPro100") == 0)
    {
      gSystem->Load("libfun4all");
      gSystem->Load("libmutoo_subsysreco" );
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("liblvl2");
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load("libmutrg");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");
      gSystem->Load("libSvxDstQA.so");

      mwgfile = "MWG_MB_run12CuAu_200GeV_Muons_pro100-0000377309-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12CuAu200MWGMinBias") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libspin.so");
      gSystem->Load("libmutrg.so");

      mwgfile = "MWG_MB_run12CuAu_Muons_200GeV_pro91-0000373672-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12CuAu200FastCentral") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libMWG_interface.so");
      gSystem->Load("libCNT.so");

      cntfile = "CNT_run12_online_central-0000373828-0000.root";
      dst_evefile = "DST_EVE_run12_online_central-0000373828-0000.root";
      dst_mpcfile = "DST_MPC_run12_online_central-0000373828-0000.root";
    }
  else if (strcmp(system, "Run12pp510Muon") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("liblpc.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("libSvxDstQA.so");

      cntfile = "CNT_MU_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_evefile = "DST_EVE_MU_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_mpcfile = "DST_MPC_MU_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_svxfile = "DST_SVX_MU_run12pp_510GeV_pro93-0000368357-9000.root";
      mwgfile = "MWG_MU_run12pp_510GeV_pro93-0000368357-9000.root";
    }
  else if (strcmp(system, "Run12pp510MuonPro100") == 0)
    {
      gSystem->Load("libfun4all");
      gSystem->Load("libmutoo_subsysreco" );
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("liblvl2");
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load("libmutrg");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");
      gSystem->Load("libSvxDstQA.so");

      mwgfile = "MWG_MU_run12pp_510GeV_Muons_pro100-0000368037-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12pp510MinBias") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("liblpc.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("libSvxDstQA.so");

      cntfile = "CNT_MB_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_evefile = "DST_EVE_MB_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_mpcfile = "DST_MPC_MB_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_svxfile = "DST_SVX_MB_run12pp_510GeV_pro93-0000368357-9000.root";
      mwgfile = "MWG_MB_run12pp_510GeV_pro93-0000368357-9000.root";
    }
  else if (strcmp(system, "Run12pp510MinBiasPro100") == 0)
    {
      gSystem->Load("libfun4all");
      gSystem->Load("libmutoo_subsysreco" );
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("liblvl2");
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("librecal.so");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("libmutrg");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");
      gSystem->Load("libSvxDstQA.so");

      mwgfile = "MWG_MB_run12pp_510GeV_Muons_pro100-0000367033-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12pp510MPC") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("liblpc.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("libSvxDstQA.so");

      cntfile = "CNT_MPC_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_evefile = "DST_EVE_MPC_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_svxfile = "DST_SVX_MPC_run12pp_510GeV_pro93-0000368357-9000.root";
      mwgfile = "MWG_MPC_run12pp_510GeV_pro93-0000368357-9000.root";
    }
  else if (strcmp(system, "Run12pp510ERT") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("liblpc.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("libSvxDstQA.so");

      cntfile = "CNT_ERT_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_evefile = "DST_EVE_ERT_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_svxfile = "DST_SVX_ERT_run12pp_510GeV_pro93-0000368357-9000.root";
      mwgfile = "MWG_ERT_run12pp_510GeV_pro93-0000368357-9000.root";
    }
  else if (strcmp(system, "Run12pp510OT") == 0)
    {
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("liblpc.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("libSvxDstQA.so");

      cntfile = "CNT_OT_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_evefile = "DST_EVE_OT_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_mpcfile = "DST_MPC_OT_run12pp_510GeV_pro93-0000368357-9000.root";
      dst_svxfile = "DST_SVX_OT_run12pp_510GeV_pro93-0000368357-9000.root";
      mwgfile = "MWG_OT_run12pp_510GeV_pro93-0000368357-9000.root";
    }
  else if (strcmp(system, "Run12UU192MWGMuon") == 0)
    {

      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal.so");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load( "librpc_muotrackreco" );

      mwgfile = "MWG_MU_run12UU_192GeV_Muons_pro94-0000371881-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12UU192MWGMinBias") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal.so");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load( "librpc_muotrackreco" );

      mwgfile = "MWG_MB_run12UU_192GeV_Muons_pro94-0000371881-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12UU192MWGERT") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal.so");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load( "librpc_muotrackreco" );

      mwgfile = "MWG_ERT_run12UU_192GeV_Muons_pro94-0000371881-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12UU192MWGUPC") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal.so");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load( "librpc_muotrackreco" );

      mwgfile = "MWG_UPC_run12UU_192GeV_Muons_pro94-0000371881-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12UU192MWGOT") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal.so");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load( "librpc_muotrackreco" );

      mwgfile = "MWG_OT_run12UU_192GeV_Muons_pro94-0000371881-9000.root";
      pwg_included = true; // disable warning about missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12CuAu200MinBiasPro95") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run12CuAu_200GeV_pro95-0000373139-9000.root";
      dst_evefile = "DST_EVE_MB_run12CuAu_200GeV_pro95-0000373139-9000.root";
//      dst_svxfile = "DST_SVX_MB_run12CuAu_200GeV_pro95-0000373139-9000.root";
      dst_mpcfile = "DST_MPC_MB_run12CuAu_200GeV_pro95-0000373139-9000.root";
      mwgfile = "MWG_MB_run12CuAu_200GeV_pro95-0000373139-9000.root";
    }
  else if (strcmp(system, "Run12CuAu200MinBias") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");

      cntfile = "CNT_MB_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
      dst_evefile = "DST_EVE_MB_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
//      dst_svxfile = "DST_SVX_MB_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
      dst_mpcfile = "DST_MPC_MB_run12CuAu_200GeV_pro95-0000374003-9000.root";
      mwgfile = "MWG_MB_run12CuAu_200GeV_Muons_pro100-0000374003-9000.root";

    }
  else if (strcmp(system, "Run12CuAu200CAERTPro99") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");

      cntfile = "CNT_ERT_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
      dst_evefile = "DST_EVE_ERT_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run12CuAu_200GeV_pro95-0000374003-9000.root";
//      dst_svxfile = "DST_SVX_ERT_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";

      gSystem->Exec("echo CNT_MB_run12CuAu_200GeV_CA_pro99-0000374003-9000.root > cnt_mb.list");
      gSystem->Exec("echo DST_EVE_MB_run12CuAu_200GeV_CA_pro99-0000374003-9000.root > dst_eve_mb.list");
      gSystem->Exec("echo DST_MPC_MB_run12CuAu_200GeV_pro95-0000374003-9000.root > dst_mpc_mb.list");
//      gSystem->Exec("echo DST_SVX_MB_run12CuAu_200GeV_CA_pro99-0000374003-9000.root > dst_svx_mb.list");

    }
  else if (strcmp(system, "Run12CuAu200CAOTPro99") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");

      cntfile = "CNT_OT_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
      dst_evefile = "DST_EVE_OT_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
      dst_mpcfile = "DST_MPC_OT_run12CuAu_200GeV_pro95-0000374003-9000.root";
//      dst_svxfile = "DST_SVX_OT_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
    }
  else if (strcmp(system, "Run12CuAu200ZFMinBias") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("librecal");

      cntfile     = "CNT_MB_run12CuAu_200GeV_ZF_ana337-0000372527-9000.root";
      dst_evefile = "DST_EVE_MB_run12CuAu_200GeV_ZF_ana337-0000372527-9000.root";
//      dst_svxfile = "DST_SVX_MB_run12CuAu_200GeV_ZF_ana337-0000372527-9000.root";
      dst_mpcfile = "DST_MPC_MB_run12CuAu_200GeV_ZF_ana337-0000372527-9000.root";
    }
  else if (strcmp(system, "Run12CuAu200ERT") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run12CuAu_200GeV_pro95-0000373139-9000.root";
      dst_evefile = "DST_EVE_ERT_run12CuAu_200GeV_pro95-0000373139-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run12CuAu_200GeV_pro95-0000373139-9000.root";
      mwgfile = "MWG_ERT_run12CuAu_200GeV_pro95-0000373139-9000.root";
        gSystem->Exec("echo CNT_MB_run12CuAu_200GeV_pro95-0000373139-9000.root > cnt_mb.list");
        gSystem->Exec("echo DST_EVE_MB_run12CuAu_200GeV_pro95-0000373139-9000.root > dst_eve_mb.list");

    }
  else if (strcmp(system, "Run12CuAu200Muon") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
      dst_evefile = "DST_EVE_MU_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
//      dst_svxfile = "DST_SVX_MU_run12CuAu_200GeV_CA_pro99-0000374003-9000.root";
      dst_mpcfile = "DST_MPC_MU_run12CuAu_200GeV_pro95-0000374003-9000.root";
      mwgfile = "MWG_MU_run12CuAu_200GeV_Muons_pro100-0000374003-9000.root";
    }
  else if (strcmp(system, "Run12CuAu200MuonPro95") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run12CuAu_200GeV_pro95-0000373139-9000.root";
      dst_evefile = "DST_EVE_MU_run12CuAu_200GeV_pro95-0000373139-9000.root";
      dst_mpcfile = "DST_MPC_MU_run12CuAu_200GeV_pro95-0000373139-9000.root";
      mwgfile = "MWG_MU_run12CuAu_200GeV_pro95-0000373139-9000.root";
    }
  else if (strcmp(system, "Run12CuAu200OT") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run12CuAu_200GeV_pro95-0000373139-9000.root";
      dst_evefile = "DST_EVE_OT_run12CuAu_200GeV_pro95-0000373139-9000.root";
      dst_mpcfile = "DST_MPC_OT_run12CuAu_200GeV_pro95-0000373139-9000.root";
      mwgfile = "MWG_OT_run12CuAu_200GeV_pro95-0000373139-9000.root";
    }
  else if (strcmp(system, "Run12UU192MinBias") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load( "librpc_muotrackreco" );
      cntfile = "CNT_MB_run12UU_192GeV_pro96-0000371881-9000.root";
      dst_evefile = "DST_EVE_MB_run12UU_192GeV_pro96-0000371881-9000.root";
      dst_mpcfile = "DST_MPC_MB_run12UU_192GeV_pro96-0000371881-9000.root";
      mwgfile = "MWG_MB_run12UU_192GeV_Muons_pro94-0000371881-9000.root";
    }
  else if (strcmp(system, "Run12UU192ERT") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load( "librpc_muotrackreco" );

      cntfile = "CNT_ERT_run12UU_192GeV_pro96-0000371881-9000.root";
      dst_evefile = "DST_EVE_ERT_run12UU_192GeV_pro96-0000371881-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run12UU_192GeV_pro96-0000371881-9000.root";
      mwgfile = "MWG_ERT_run12UU_192GeV_Muons_pro94-0000371881-9000.root";
    }
  else if (strcmp(system, "Run12UU192Muon") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load( "librpc_muotrackreco" );

      cntfile = "CNT_MU_run12UU_192GeV_pro96-0000371881-9000.root";
      dst_evefile = "DST_EVE_MU_run12UU_192GeV_pro96-0000371881-9000.root";
      dst_mpcfile = "DST_MPC_MU_run12UU_192GeV_pro96-0000371881-9000.root";
      mwgfile = "MWG_MU_run12UU_192GeV_Muons_pro94-0000371881-9000.root";
    }
  else if (strcmp(system, "Run12UU192OT") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load( "librpc_muotrackreco" );
      cntfile = "CNT_OT_run12UU_192GeV_pro96-0000371881-9000.root";
      dst_evefile = "DST_EVE_OT_run12UU_192GeV_pro96-0000371881-9000.root";
      dst_mpcfile = "DST_MPC_OT_run12UU_192GeV_pro96-0000371881-9000.root";
      mwgfile = "MWG_OT_run12UU_192GeV_Muons_pro94-0000371881-9000.root";
    }
  else if (strcmp(system, "Run12UU192UPC") == 0)
    {
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load( "librpc_subsysreco" );
      gSystem->Load( "librpc_muotrackreco" );

      cntfile = "CNT_UPC_run12UU_192GeV_pro96-0000371881-9000.root";
      dst_evefile = "DST_EVE_UPC_run12UU_192GeV_pro96-0000371881-9000.root";
      dst_mpcfile = "DST_MPC_UPC_run12UU_192GeV_pro96-0000371881-9000.root";
      mwgfile = "MWG_UPC_run12UU_192GeV_Muons_pro94-0000371881-9000.root";
    }
  else if (strcmp(system, "Run13pp510MinBias") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile = "CNT_MB_run13pp_510GeV_pro97-0000393483-9000.root";
      dst_evefile = "DST_EVE_MB_run13pp_510GeV_pro97-0000393483-9000.root";
      dst_mpcfile = "DST_MPC_MB_run13pp_510GeV_pro97-0000393483-9000.root";
//      dst_svxfile = "DST_SVX_MB_run13pp_510GeV_pro97-0000393483-9000.root";
      mwgfile = "MWG_MB_run13pp_510GeV_pro97-0000393483-9000.root";
    }
  else if (strcmp(system, "Run13pp510ERT") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
  
      cntfile = "CNT_ERT_run13pp_510GeV_pro97-0000393483-9000.root";
      dst_evefile = "DST_EVE_ERT_run13pp_510GeV_pro97-0000393483-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run13pp_510GeV_pro97-0000393483-9000.root";
//      dst_svxfile = "DST_SVX_ERT_run13pp_510GeV_pro97-0000393483-9000.root";
      mwgfile = "MWG_ERT_run13pp_510GeV_pro97-0000393483-9000.root";
        gSystem->Exec("echo CNT_MB_run13pp_510GeV_pro97-0000393483-9000.root > cnt_mb.list");
        gSystem->Exec("echo DST_EVE_MB_run13pp_510GeV_pro97-0000393483-9000.root > dst_eve_mb.list");

    }
  else if (strcmp(system, "Run13pp510MPC") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
  
      cntfile = "CNT_MPC_run13pp_510GeV_pro97-0000393483-9000.root";
      dst_evefile = "DST_EVE_MPC_run13pp_510GeV_pro97-0000393483-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run13pp_510GeV_pro97-0000393483-9000.root";
//      dst_svxfile = "DST_SVX_MPC_run13pp_510GeV_pro97-0000393483-9000.root";
      mwgfile = "MWG_MPC_run13pp_510GeV_pro97-0000393483-9000.root";
    }
  else if (strcmp(system, "Run13pp510Muon") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
  
      cntfile = "CNT_MU_run13pp_510GeV_pro97-0000393483-9000.root";
      dst_evefile = "DST_EVE_MU_run13pp_510GeV_pro97-0000393483-9000.root";
      dst_mpcfile = "DST_MPC_MU_run13pp_510GeV_pro97-0000393483-9000.root";
//      dst_svxfile = "DST_SVX_MU_run13pp_510GeV_pro97-0000393483-9000.root";
      mwgfile = "MWG_MU_run13pp_510GeV_pro97-0000393483-9000.root";
    }
  else if (strcmp(system, "Run13pp510OT") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
  
      cntfile = "CNT_OT_run13pp_510GeV_pro97-0000393483-9000.root";
      dst_evefile = "DST_EVE_OT_run13pp_510GeV_pro97-0000393483-9000.root";
      dst_mpcfile = "DST_MPC_OT_run13pp_510GeV_pro97-0000393483-9000.root";
//      dst_svxfile = "DST_SVX_OT_run13pp_510GeV_pro97-0000393483-9000.root";
      mwgfile = "MWG_OT_run13pp_510GeV_pro97-0000393483-9000.root";
    }
  else if (strcmp(system, "Run13pp510ZFMinBias") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile = "CNT_MB_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
      dst_evefile = "DST_EVE_MB_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
      dst_mpcfile = "DST_MPC_MB_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
//      dst_svxfile = "DST_SVX_MB_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
      mwgfile = "MWG_MB_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
    }
  else if (strcmp(system, "Run13pp510ZFMuon") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");      
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile = "CNT_MU_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
      dst_evefile = "DST_EVE_MU_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
      dst_mpcfile = "DST_MPC_MU_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
//      dst_svxfile = "DST_SVX_MU_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
      mwgfile = "MWG_MU_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
    }
  else if (strcmp(system, "Run13pp510ZFERT") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");      
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile = "CNT_ERT_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
      dst_evefile = "DST_EVE_ERT_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
//      dst_svxfile = "DST_SVX_ERT_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
      mwgfile = "MWG_ERT_run13pp_510GeV_ZF_pro97-0000386885-9000.root";
    }
  else if (strcmp(system, "Run13pp510LPOL") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      lpolfile = "LOCALPOL_MB_run13pp_510GeV_lpol_pro97-0000385985-9000.root";
      pwg_included = true;//disable wanring for missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run13Cosmic") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libBbcMultipleVtx.so" );

      mwgfile = "MWG_MU_run13_cosmics_pro98-0000382644-9000.root";
      pwg_included = true;//disable wanring for missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run13ZFCosmic") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libBbcMultipleVtx.so" );

      mwgfile = "MWG_MU_run13_cosmics_ZF_pro98-0000382453-9000.root";
      pwg_included = true;//disable wanring for missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12Cosmic") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libBbcMultipleVtx.so" );

      mwgfile = "MWG_MU_run12_cosmics_pro98-0000355725-9000.root";
      pwg_included = true;//disable wanring for missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run12ZFCosmic") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libBbcMultipleVtx.so" );

      mwgfile = "MWG_MU_run12_cosmics_ZF_pro98-0000373083-9000.root";
      pwg_included = true;//disable wanring for missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run11Cosmic") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libBbcMultipleVtx.so" );

      mwgfile = "MWG_MU_run11_cosmics_pro98-0000334367-9000.root";
      pwg_included = true;//disable wanring for missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run11ZFCosmic") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load("libBbcMultipleVtx.so" );

      mwgfile = "MWG_MU_run11_cosmics_ZF_pro98-0000334395-9000.root";
      pwg_included = true;//disable wanring for missing CNT/PWG/CWG
    }
  else if (strcmp(system, "Run14HeAu200ERT") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile     = "CNT_ERT_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_evefile = "DST_EVE_ERT_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_svxfile = "DST_SVX_ERT_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      mwgfile     = "MWG_ERT_run14HeAu_200GeV_Muons_pro109-0000415751-9000.root";
      gSystem->Exec("echo CNT_MB_run14HeAu_200GeV_CA_pro102-0000415751-9000.root > cnt_mb.list");
      gSystem->Exec("echo DST_EVE_MB_run14HeAu_200GeV_CA_pro102-0000415751-9000.root > dst_eve_mb.list");
      gSystem->Exec("echo DST_MPC_MB_run14HeAu_200GeV_CA_pro102-0000415751-9000.root > dst_mpc_mb.list");
      gSystem->Exec("echo DST_SVX_MB_run14HeAu_200GeV_CA_pro102-0000415751-9000.root > dst_svx_mb.list");
      gSystem->Exec("echo MWG_MB_run14HeAu_200GeV_CA_pro102-0000415751-9000.root > mwg_mb.list");

    }
  else if (strcmp(system, "Run14HeAu200MinBias") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile     = "CNT_MB_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_evefile = "DST_EVE_MB_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_mpcfile = "DST_MPC_MB_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_svxfile = "DST_SVX_MB_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      mwgfile     = "MWG_MB_run14HeAu_200GeV_Muons_pro109-0000415751-9000.root";

    }
  else if (strcmp(system, "Run14HeAu200MPC") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile     = "CNT_MPC_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_evefile = "DST_EVE_MPC_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_svxfile = "DST_SVX_MPC_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      mwgfile     = "MWG_MPC_run14HeAu_200GeV_Muons_pro109-0000415751-9000.root";

    }
  else if (strcmp(system, "Run14HeAu200MU") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile     = "CNT_MU_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_evefile = "DST_EVE_MU_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_mpcfile = "DST_MPC_MU_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_svxfile = "DST_SVX_MU_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      mwgfile     = "MWG_MU_run14HeAu_200GeV_Muons_pro109-0000415751-9000.root";

    }
  else if (strcmp(system, "Run14HeAu200OT") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile     = "CNT_OT_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_evefile = "DST_EVE_OT_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_mpcfile = "DST_MPC_OT_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      dst_svxfile = "DST_SVX_OT_run14HeAu_200GeV_CA_pro102-0000415751-9000.root";
      mwgfile     = "MWG_OT_run14HeAu_200GeV_Muons_pro109-0000415751-9000.root";

    }
  else if (strcmp(system, "Run14HeAu200MuonsERTPro103") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile     = "MWG_ERT_run14HeAu_200GeV_Muons_pro103-0000415751-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run14HeAu200MuonsMBPro103") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile     = "MWG_MB_run14HeAu_200GeV_Muons_pro103-0000415751-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run14HeAu200MuonsMPCPro103") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile     = "MWG_MPC_run14HeAu_200GeV_Muons_pro103-0000415751-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run14HeAu200MuonsMUPro103") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile     = "MWG_MU_run14HeAu_200GeV_Muons_pro103-0000415751-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run14HeAu200MuonsOTPro103") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile     = "MWG_OT_run14HeAu_200GeV_Muons_pro103-0000415751-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run14HeAu200MuonsERTPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile     = "MWG_ERT_run14HeAu_200GeV_Muons_pro109-0000415751-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run14HeAu200MuonsMBPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile     = "MWG_MB_run14HeAu_200GeV_Muons_pro109-0000415751-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run14HeAu200MuonsMPCPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile     = "MWG_MPC_run14HeAu_200GeV_Muons_pro109-0000415751-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run14HeAu200MuonsMUPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile     = "MWG_MU_run14HeAu_200GeV_Muons_pro109-0000415751-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run14HeAu200MuonsOTPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile     = "MWG_OT_run14HeAu_200GeV_Muons_pro109-0000415751-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run14AuAu200CAMBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile     = "CNT_MB_run14AuAu_200GeV_CA_pro104-0000405868-9000.root";
      dst_evefile = "DST_EVE_MB_run14AuAu_200GeV_CA_pro104-0000405868-9000.root";
      dst_mpcfile = "DST_MPC_MB_run14AuAu_200GeV_CA_pro104-0000405868-9000.root";
      dst_svxfile = "DST_SVX_MB_run14AuAu_200GeV_CA_pro104-0000405868-9000.root";
    }
  else if (strcmp(system, "Run14AuAu200CAERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile     = "CNT_ERT_run14AuAu_200GeV_CA_pro104-0000405868-9000.root";
      dst_evefile = "DST_EVE_ERT_run14AuAu_200GeV_CA_pro104-0000405868-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run14AuAu_200GeV_CA_pro104-0000405868-9000.root";
      dst_svxfile = "DST_SVX_ERT_run14AuAu_200GeV_CA_pro104-0000405868-9000.root";
        gSystem->Exec("echo CNT_MB_run14AuAu_200GeV_CA_pro104-0000405868-9000.root > cnt_mb.list");
        gSystem->Exec("echo DST_EVE_MB_run14AuAu_200GeV_CA_pro104-0000405868-9000.root > dst_eve_mb.list");

    }
  else if (strcmp(system, "Run14AuAu200CAERTPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      cntfile     = "CNT_ERT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_evefile = "DST_EVE_ERT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_svxfile = "DST_SVX_ERT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
        gSystem->Exec("echo CNT_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root > cnt_mb.list");
        gSystem->Exec("echo DST_EVE_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root > dst_eve_mb.list");
    }
  else if (strcmp(system, "Run14AuAu200CAMBPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      cntfile     = "CNT_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_evefile = "DST_EVE_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_MB_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_svxfile = "DST_SVX_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
    }
  else if (strcmp(system, "Run14AuAu200CAOTPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      cntfile     = "CNT_OT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_evefile = "DST_EVE_OT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_OT_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_svxfile = "DST_SVX_OT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
        gSystem->Exec("echo CNT_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root > cnt_mb.list");
        gSystem->Exec("echo DST_EVE_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root > dst_eve_mb.list");
    }
  else if (strcmp(system, "Run14AuAu200CAUPPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      cntfile     = "CNT_UP_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_evefile = "DST_EVE_UP_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_UP_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_svxfile = "DST_SVX_UP_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
        gSystem->Exec("echo CNT_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root > cnt_mb.list");
        gSystem->Exec("echo DST_EVE_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root > dst_eve_mb.list");
    }
  else if (strcmp(system, "Run14AuAu200ERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile     = "CNT_ERT_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      dst_evefile = "DST_EVE_ERT_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      dst_svxfile = "DST_SVX_ERT_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      mwgfile     = "MWG_ERT_run14AuAu_200GeV_Muons_pro104-0000405863-9000.root";
    }
  else if (strcmp(system, "Run14AuAu200OTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile     = "CNT_OT_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      dst_evefile = "DST_EVE_OT_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_OT_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      dst_svxfile = "DST_SVX_OT_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      mwgfile     = "MWG_OT_run14AuAu_200GeV_Muons_pro104-0000405863-9000.root";
    }
  else if (strcmp(system, "Run14AuAu200UPPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile     = "CNT_UP_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      dst_evefile = "DST_EVE_UP_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_UP_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      dst_svxfile = "DST_SVX_UP_run14AuAu_200GeV_CA_pro104-0000405863-9000.root";
      mwgfile     = "MWG_UP_run14AuAu_200GeV_Muons_pro104-0000405863-9000.root";
    }
  else if (strcmp(system, "Run14AuAu200CAnVXERTP106") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      cntfile     = "CNT_ERT_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_evefile = "DST_EVE_ERT_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
    }
  else if (strcmp(system, "Run14AuAu200CAnVXMBP106") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      cntfile     = "CNT_MB_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_evefile = "DST_EVE_MB_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_MB_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
    }
  else if (strcmp(system, "Run14AuAu200CAnVXOTP106") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      cntfile     = "CNT_OT_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_evefile = "DST_EVE_OT_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_OT_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
    }
  else if (strcmp(system, "Run14AuAu200CAnVXUPP106") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      cntfile     = "CNT_UP_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_evefile = "DST_EVE_UP_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
      dst_mpcfile = "DST_MPC_UP_run14AuAu_200GeV_CA_noVTX_pro106-0000405863-9000.root";
    }
  else if (strcmp(system, "Run14AuAu15CAERT") == 0)
    {
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile     = "CNT_ERT_run14AuAu_15GeV_CA_noSVX_pro100-0000405030-9000.root";
      dst_evefile = "DST_EVE_ERT_run14AuAu_15GeV_CA_noSVX_pro100-0000405030-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run14AuAu_15GeV_CA_noSVX_pro100-0000405030-9000.root";
    }
  else if (strcmp(system, "Run14AuAu15CAMinBias") == 0)
    {
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile     = "CNT_MB_run14AuAu_15GeV_CA_noSVX_pro100-0000405030-9000.root";
      dst_evefile = "DST_EVE_MB_run14AuAu_15GeV_CA_noSVX_pro100-0000405030-9000.root";
      dst_mpcfile = "DST_MPC_MB_run14AuAu_15GeV_CA_noSVX_pro100-0000405030-9000.root";
    }
  else if (strcmp(system, "Run14AuAu15CAOT") == 0)
    {
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile     = "CNT_OT_run14AuAu_15GeV_CA_noSVX_pro100-0000405030-9000.root";
      dst_evefile = "DST_EVE_OT_run14AuAu_15GeV_CA_noSVX_pro100-0000405030-9000.root";
      dst_mpcfile = "DST_MPC_OT_run14AuAu_15GeV_CA_noSVX_pro100-0000405030-9000.root";
    }
  else if (strcmp(system, "Run15pp200MBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile     = "CNT_MB_run15pp_200GeV_CA_pro104-0000421716-9000.root";
      dst_evefile = "DST_EVE_MB_run15pp_200GeV_CA_pro104-0000421716-9000.root";
      dst_mpcfile = "DST_MPC_MB_run15pp_200GeV_CA_pro104-0000421716-9000.root";
      dst_svxfile = "DST_SVX_MB_run15pp_200GeV_CA_pro104-0000421716-9000.root";
    }
  else if (strcmp(system, "Run15pp200FVTXPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile     = "CNT_FVTX_run15pp_200GeV_CA_pro104-0000422540-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pp_200GeV_CA_pro104-0000422540-9000.root";
      dst_mpcfile = "DST_MPC_FVTX_run15pp_200GeV_CA_pro104-0000422540-9000.root";
      dst_svxfile = "DST_SVX_FVTX_run15pp_200GeV_CA_pro104-0000422540-9000.root";
    }
  else if (strcmp(system, "Run15pp200ERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      cntfile     = "CNT_ERT_run15pp_200GeV_CA_pro104-0000421716-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pp_200GeV_CA_pro104-0000421716-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run15pp_200GeV_CA_pro104-0000421716-9000.root";
      dst_svxfile = "DST_SVX_ERT_run15pp_200GeV_CA_pro104-0000421716-9000.root";
    }
  else if (strcmp(system, "Run15pAl200ERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile     = "CNT_ERT_run15pAl_200GeV_CA_pro104-0000438420-9000.root";
      mwgfile = "MWG_ERT_run15pAl_200GeV_Muons_pro105-0000438420-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pAl_200GeV_CA_pro104-0000438420-9000.root";
      dst_fvtxfile = "FVTX_Clusters_run15pAl_200GeV_FVTXClusters_pro107-0000438420-9000.root";
    }
  else if (strcmp(system, "Run15pAl200FVTXPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile     = "CNT_FVTX_run15pAl_200GeV_CA_pro104-0000438420-9000.root";
      mwgfile = "MWG_FVTX_run15pAl_200GeV_Muons_pro105-0000438420-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pAl_200GeV_CA_pro104-0000438420-9000.root";
      dst_fvtxfile = "FVTX_Clusters_run15pAl_200GeV_FVTXClusters_pro107-0000438420-9000.root";
    }
  else if (strcmp(system, "Run15pAl200MBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile     = "CNT_MB_run15pAl_200GeV_CA_pro104-0000438420-9000.root";
      mwgfile = "MWG_MB_run15pAl_200GeV_Muons_pro105-0000438420-9000.root";
      dst_evefile = "DST_EVE_MB_run15pAl_200GeV_CA_pro104-0000438420-9000.root";
      dst_fvtxfile = "FVTX_Clusters_run15pAl_200GeV_FVTXClusters_pro107-0000438420-9000.root";
    }
  else if (strcmp(system, "Run15pAl200MUPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile     = "CNT_MU_run15pAl_200GeV_CA_pro104-0000438420-9000.root";
      mwgfile = "MWG_MU_run15pAl_200GeV_Muons_pro105-0000438420-9000.root";
      dst_evefile = "DST_EVE_MU_run15pAl_200GeV_CA_pro104-0000438420-9000.root";
      dst_fvtxfile = "FVTX_Clusters_run15pAl_200GeV_FVTXClusters_pro107-0000438420-9000.root";
    }
  else if (strcmp(system, "Run15pAl200OTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile     = "CNT_OT_run15pAl_200GeV_CA_pro104-0000438420-9000.root";
      mwgfile = "MWG_OT_run15pAl_200GeV_Muons_pro105-0000438420-9000.root";
      dst_evefile = "DST_EVE_OT_run15pAl_200GeV_CA_pro104-0000438420-9000.root";
      dst_fvtxfile = "FVTX_Clusters_run15pAl_200GeV_FVTXClusters_pro107-0000438420-9000.root";
    }
  else if (strcmp(system, "Run12pp510MuonsMBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      mwgfile = "MWG_MB_run12pp_510GeV_Muons_pro104-0000366035-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run12pp510MuonsMUPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      mwgfile = "MWG_MU_run12pp_510GeV_Muons_pro104-0000366035-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run12pp510MuonsMPCPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      mwgfile = "MWG_MPC_run12pp_510GeV_Muons_pro104-0000366035-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run12pp510MuonsERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );

      mwgfile = "MWG_ERT_run12pp_510GeV_Muons_pro104-0000366035-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run12pp510MuStaERTP104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("librpcoo_interface.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_ERT_run12pp_510GeV_MuonStandalone_pro104-0000368037-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run12pp510MuStaMBP104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("librpcoo_interface.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MB_run12pp_510GeV_MuonStandalone_pro104-0000368037-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run12pp510MuStaMPCP104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("librpcoo_interface.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MPC_run12pp_510GeV_MuonStandalone_pro104-0000368037-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run12pp510MuStaMUP104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("librpcoo_interface.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MU_run12pp_510GeV_MuonStandalone_pro104-0000368037-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run12pp510MuStaOTP104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("librpcoo_interface.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_OT_run12pp_510GeV_MuonStandalone_pro104-0000368037-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MPCPlusMBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      cntfile = "CNT_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_MB_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_mpcexfile = "DST_MPCEX_MB_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MPCPlusMUPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      cntfile = "CNT_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_MU_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_mpcexfile = "DST_MPCEX_MU_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MPCPlusMPCPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      cntfile = "CNT_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_mpcexfile = "DST_MPCEX_MPC_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MPCPlusFVTXPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      cntfile = "CNT_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_FVTX_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_mpcexfile = "DST_MPCEX_FVTX_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      pwg_included = true;
    }

  else if (strcmp(system, "Run15pAu200CAnoVTXERTPro104") == 0)
    {
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
        gSystem->Exec("echo CNT_MB_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root > cnt_mb.list");
        gSystem->Exec("echo DST_EVE_MB_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root > dst_eve_mb.list");

    }
  else if (strcmp(system, "Run15pAu200CAnoVTXFVTXPro104") == 0)
    {
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAnoVTXMBPro104") == 0)
    {
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
      dst_evefile = "DST_EVE_MB_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAnoVTXMPCPro104") == 0)
    {
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAnoVTXMUPro104") == 0)
    {
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
      dst_evefile = "DST_EVE_MU_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAnoVTXOTPro104") == 0)
    {
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
      dst_evefile = "DST_EVE_OT_run15pAu_200GeV_CA_noVTX_pro104-0000435246-9000.root";
    }

  else if (strcmp(system, "Run15pAu200FVTXClusAna503") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      gSystem->Load("libspin");

      cntfile = "CNT_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      mwgfile = "MWG_MB_run15pAu_200GeV_Muons_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "FVTX_Clusters_run15pAu_200GeV_CA_FVTXcluster_ana503-0000435527-9000.root";

      pwg_included = true;
    }

  else if (strcmp(system, "Run15pAu200CAERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      mwgfile = "MWG_ERT_run15pAu_200GeV_Muons_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_ERT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
        gSystem->Exec("echo CNT_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root > cnt_mb.list");
        gSystem->Exec("echo DST_EVE_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root > dst_eve_mb.list");

    }
  else if (strcmp(system, "Run15pAu200CAFVTXPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      mwgfile = "MWG_FVTX_run15pAu_200GeV_Muons_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_FVTX_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAMBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      mwgfile = "MWG_MB_run15pAu_200GeV_Muons_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAMPCPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_MPC_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      mwgfile = "MWG_MPC_run15pAu_200GeV_Muons_pro104-0000435527-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAMUPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      mwgfile = "MWG_MU_run15pAu_200GeV_Muons_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MU_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_MU_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAOTPro104") == 0)
    {
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_OT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_OT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
    }

  else if (strcmp(system, "Run15pAu200CAERTPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_ERT_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAFVTXPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_FVTX_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_FVTX_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAMBPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_MB_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_MB_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_MB_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAMPCPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_MPC_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAMUPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_MU_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_MU_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_MU_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
    }
  else if (strcmp(system, "Run15pAu200CAOTPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_OT_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_OT_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_OT_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
    }

  else if (strcmp(system, "Run15pp200CAERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_ERT_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAFVTXPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_FVTX_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAMBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_MB_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_MB_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAMPCPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_MPC_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAMUPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_MU_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      dst_evefile = "DST_EVE_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAOTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_OT_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      dst_evefile = "DST_EVE_OT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_OT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAERTP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_ERT_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      mwgfile = "MWG_ERT_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
        gSystem->Exec("echo CNT_MB_run15pp_200GeV_CA_pro108-0000430238-9000.root > cnt_mb.list");
        gSystem->Exec("echo DST_EVE_MB_run15pp_200GeV_CA_pro108-0000430238-9000.root > dst_eve_mb.list");
        gSystem->Exec("echo DST_SVX_MB_run15pp_200GeV_CA_pro108-0000430238-9000.root > dst_svx_mb.list");
    }
  else if (strcmp(system, "Run15pp200CAFVTXP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_FVTX_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_FVTX_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      mwgfile = "MWG_FVTX_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAMBP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_evefile = "DST_EVE_MB_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_MB_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_MB_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      mwgfile = "MWG_MB_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAMPCP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_MPC_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      mwgfile = "MWG_MPC_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAMUP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_evefile = "DST_EVE_MU_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_MU_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_MU_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      mwgfile = "MWG_MU_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAOTP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_evefile = "DST_EVE_OT_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      dst_mpcfile = "DST_MPC_OT_run15pp_200GeV_MPCPlus_pro104-0000430238-9000.root";
      dst_svxfile = "DST_SVX_OT_run15pp_200GeV_CA_pro108-0000430238-9000.root";
      mwgfile = "MWG_OT_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
    }

  else if (strcmp(system, "Run15pp200CAnoVTXERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_ERT_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAnoVTXFVTXPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_FVTX_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAnoVTXMBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_MB_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAnoVTXMPCPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_MPC_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAnoVTXMUPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_MU_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200CAnoVTXOTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_OT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      mwgfile = "MWG_OT_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200MuonsERTPro106") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_fvtxfile = "MWG_ERT_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      mwgfile = "MWG_ERT_run15pp_200GeV_MuonStandalone_pro106-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsFVTXPro106") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_fvtxfile = "MWG_FVTX_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      mwgfile = "MWG_FVTX_run15pp_200GeV_MuonStandalone_pro106-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMBPro106") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_fvtxfile = "MWG_MB_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      mwgfile = "MWG_MB_run15pp_200GeV_MuonStandalone_pro106-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMPCPro106") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_fvtxfile = "MWG_MPC_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      mwgfile = "MWG_MPC_run15pp_200GeV_MuonStandalone_pro106-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMUPro106") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_fvtxfile = "MWG_MU_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      mwgfile = "MWG_MU_run15pp_200GeV_MuonStandalone_pro106-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsOTPro106") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");    
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libert");
      gSystem->Load("libspin");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_OT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_fvtxfile = "MWG_OT_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      mwgfile = "MWG_OT_run15pp_200GeV_MuonStandalone_pro106-0000430238-9000.root";
      pwg_included = true;
    }

  else if (strcmp(system, "Run16AuAu200CAnVXERTP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("libmpc");
      gSystem->Load("librecal");
      cntfile = "CNT_ERT_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
      dst_evefile = "DST_EVE_ERT_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
    }
  else if (strcmp(system, "Run16AuAu200CAnVXMBP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("libmpc");
      gSystem->Load("librecal");
      cntfile = "CNT_MB_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
      dst_evefile = "DST_EVE_MB_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
      dst_mpcfile = "DST_MPC_MB_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
    }
  else if (strcmp(system, "Run16AuAu200CAnVXOTP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("libmpc");
      gSystem->Load("librecal");
      cntfile = "CNT_OT_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
      dst_evefile = "DST_EVE_OT_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
      dst_mpcfile = "DST_MPC_OT_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
    }
  else if (strcmp(system, "Run16AuAu200CAnVXUPP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("libmpc");
      gSystem->Load("librecal");
      cntfile = "CNT_UP_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
      dst_evefile = "DST_EVE_UP_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
      dst_mpcfile = "DST_MPC_UP_run16AuAu_200GeV_CA_noVTX_pro108-0000447993-9000.root";
    }
  else if (strcmp(system, "Run16dAu20CAnVXALLP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_ALL_run16dAu_20GeV_CA_noVTX_pro107-0000457111-9000.root";
      dst_evefile = "DST_EVE_ALL_run16dAu_20GeV_CA_noVTX_pro107-0000457111-9000.root";
    }

  else if (strcmp(system, "Run16dAu20CAnVXOTP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run16dAu_20GeV_CA_noVTX_pro107-0000457111-9000.root";
      dst_evefile = "DST_EVE_OT_run16dAu_20GeV_CA_noVTX_pro107-0000457111-9000.root";
    }
  else if (strcmp(system, "Run16dAu20MPCexALLP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      dst_evefile = "DST_EVE_ALL_run16dAu_20GeV_CA_noVTX_pro107-0000457111-9000.root";
      dst_mpcfile = "DST_MPC_ALL_run16dAu_20GeV_MPCPlus_pro108-0000457111-9000.root";
      dst_mpcexfile = "DST_MPCEX_ALL_run16dAu_20GeV_MPCPlus_pro108-0000457111-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu20MPCexOTP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      dst_evefile = "DST_EVE_OT_run16dAu_20GeV_CA_noVTX_pro107-0000457111-9000.root";
      dst_mpcfile = "DST_MPC_OT_run16dAu_20GeV_MPCPlus_pro108-0000457111-9000.root";
      dst_mpcexfile = "DST_MPCEX_OT_run16dAu_20GeV_MPCPlus_pro108-0000457111-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu20MPCexALLP109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      dst_evefile = "DST_EVE_ALL_run16dAu_20GeV_CA_noVTX_pro107-0000457111-9000.root";
      dst_mpcfile = "DST_MPC_ALL_run16dAu_20GeV_MPCPlus_pro109-0000457111-9000.root";
      dst_mpcexfile = "DST_MPCEX_ALL_run16dAu_20GeV_MPCPlus_pro109-0000457111-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu20MPCexOTP109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      dst_evefile = "DST_EVE_OT_run16dAu_20GeV_CA_noVTX_pro107-0000457111-9000.root";
      dst_mpcfile = "DST_MPC_OT_run16dAu_20GeV_MPCPlus_pro109-0000457111-9000.root";
      dst_mpcexfile = "DST_MPCEX_OT_run16dAu_20GeV_MPCPlus_pro109-0000457111-9000.root";
      pwg_included = true;
    }

  else if (strcmp(system, "Run16dAu39CAnVXALLP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_ALL_run16dAu_39GeV_CA_noVTX_pro107-0000458166-9000.root";
      dst_evefile = "DST_EVE_ALL_run16dAu_39GeV_CA_noVTX_pro107-0000458166-9000.root";
    }
  else if (strcmp(system, "Run16dAu39CAnVXOTP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run16dAu_39GeV_CA_noVTX_pro107-0000458166-9000.root";
      dst_evefile = "DST_EVE_OT_run16dAu_39GeV_CA_noVTX_pro107-0000458166-9000.root";
    }
  else if (strcmp(system, "Run16dAu39MPCexALLP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      gSystem->Load("librecal");

      dst_evefile = "DST_EVE_ALL_run16dAu_39GeV_CA_noVTX_pro107-0000458166-9000.root";
      dst_mpcfile = "DST_MPC_ALL_run16dAu_39GeV_MPCPlus_pro108-0000458166-9000.root";
      dst_mpcexfile = "DST_MPCEX_ALL_run16dAu_39GeV_MPCPlus_pro108-0000458166-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu39MPCexOTP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      gSystem->Load("librecal");

      dst_evefile = "DST_EVE_OT_run16dAu_39GeV_CA_noVTX_pro107-0000458166-9000.root";
      dst_mpcfile = "DST_MPC_OT_run16dAu_39GeV_MPCPlus_pro108-0000458166-9000.root";
      dst_mpcexfile = "DST_MPCEX_OT_run16dAu_39GeV_MPCPlus_pro108-0000458166-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu39MPCexALLP109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      gSystem->Load("librecal");

      dst_evefile = "DST_EVE_ALL_run16dAu_39GeV_CA_noVTX_pro107-0000458166-9000.root";
      dst_mpcfile = "DST_MPC_ALL_run16dAu_39GeV_MPCPlus_pro109-0000458166-9000.root";
      dst_mpcexfile = "DST_MPCEX_ALL_run16dAu_39GeV_MPCPlus_pro109-0000458166-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu39MPCexOTP109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      gSystem->Load("librecal");

      dst_evefile = "DST_EVE_OT_run16dAu_39GeV_CA_noVTX_pro107-0000458166-9000.root";
      dst_mpcfile = "DST_MPC_OT_run16dAu_39GeV_MPCPlus_pro109-0000458166-9000.root";
      dst_mpcexfile = "DST_MPCEX_OT_run16dAu_39GeV_MPCPlus_pro109-0000458166-9000.root";
      pwg_included = true;
    }


  else if (strcmp(system, "Run16dAu60CAnVXERTP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_ERT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
    }
  else if (strcmp(system, "Run16dAu60CAnVXFVTXP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_FVTX_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
    }
  else if (strcmp(system, "Run16dAu60CAnVXMBP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_MB_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
    }
  else if (strcmp(system, "Run16dAu60CAnVXMPCP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_MPC_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
    }
  else if (strcmp(system, "Run16dAu60CAnVXMUP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_MU_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
    }
  else if (strcmp(system, "Run16dAu60CAnVXOTP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_OT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
    }
  else if (strcmp(system, "Run16dAu62MPCexERTP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_ERT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_ERT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_ERT_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexFVTXP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_FVTX_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_FVTX_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_FVTX_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_FVTX_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexMBP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_MB_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_MB_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_MB_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_MB_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexMPCP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_MPC_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_MPC_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_MPC_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexMUP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_MU_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_MU_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_MU_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_MU_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexOTP108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_OT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_OT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_OT_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_OT_run16dAu_62GeV_MPCPlus_pro108-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexERTP109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_ERT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_ERT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_ERT_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexFVTXP109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_FVTX_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_FVTX_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_FVTX_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_FVTX_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexMBP109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_MB_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_MB_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_MB_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_MB_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexMPCP109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_MPC_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_MPC_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_MPC_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexMUP109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_MU_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_MU_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_MU_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_MU_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MPCexOTP109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert");
      gSystem->Load("librecal");
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );
      cntfile = "CNT_OT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_evefile = "DST_EVE_OT_run16dAu_62GeV_CA_noVTX_pro107-0000456107-9000.root";
      dst_mpcfile = "DST_MPC_OT_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      dst_mpcexfile = "DST_MPCEX_OT_run16dAu_62GeV_MPCPlus_pro109-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MuonsERTP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile = "MWG_ERT_run16dAu_62GeV_Muons_noVTX_pro107-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MuonsFVTXP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile = "MWG_FVTX_run16dAu_62GeV_Muons_noVTX_pro107-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MuonsMBP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile = "MWG_MB_run16dAu_62GeV_Muons_noVTX_pro107-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MuonsMPCP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile = "MWG_MPC_run16dAu_62GeV_Muons_noVTX_pro107-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MuonsMUP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile = "MWG_MU_run16dAu_62GeV_Muons_noVTX_pro107-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu62MuonsOTP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("librecal");

      mwgfile = "MWG_OT_run16dAu_62GeV_Muons_noVTX_pro107-0000456107-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200CAnVXERTP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert.so");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_ERT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";
        gSystem->Exec("echo CNT_MB_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root > cnt_mb.list");
        gSystem->Exec("echo DST_EVE_MB_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root > dst_eve_mb.list");
    }
  else if (strcmp(system, "Run16dAu200CAnVXFVTXP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert.so");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_FVTX_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_FVTX_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";

    }
  else if (strcmp(system, "Run16dAu200CAnVXMBP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert.so");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MB_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_MB_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";

    }
  else if (strcmp(system, "Run16dAu200CAnVXMPCP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert.so");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MPC_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";
    }
  else if (strcmp(system, "Run16dAu200CAnVXMUP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert.so");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MU_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_MU_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";
    }
  else if (strcmp(system, "Run16dAu200CAnVXOTP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libert.so");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_OT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_OT_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";
    }
  else if (strcmp(system, "Run16dAu200MuonsERTP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_ERT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      mwgfile = "MWG_ERT_run16dAu_200GeV_Muons_noVTX_pro107-0000455605-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MuonsFVTXP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_FVTX_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      mwgfile = "MWG_FVTX_run16dAu_200GeV_Muons_noVTX_pro107-0000455605-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MuonsMBP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MB_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      mwgfile = "MWG_MB_run16dAu_200GeV_Muons_noVTX_pro107-0000455605-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MuonsMPCP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MPC_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      mwgfile = "MWG_MPC_run16dAu_200GeV_Muons_noVTX_pro107-0000455605-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MuonsMUP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MU_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      mwgfile = "MWG_MU_run16dAu_200GeV_Muons_noVTX_pro107-0000455605-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MuonsOTP107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_OT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      mwgfile = "MWG_OT_run16dAu_200GeV_Muons_noVTX_pro107-0000455605-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexERTP106") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_ERT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_ERT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_ERT_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexFVTXP106") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_FVTX_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_FVTX_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_FVTX_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_FVTX_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexMBP106") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_MB_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MB_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_MB_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_MB_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexMPCP106") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_MPC_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MPC_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_MPC_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexMUP106") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_MU_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MU_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_MU_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_MU_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexOTP106") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_OT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_OT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_OT_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_OT_run16dAu_200GeV_MPCPlus_pro106-0000455605-9000.root";

      pwg_included = true;
    }

  else if (strcmp(system, "Run16dAu200MPCexERTP109") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_ERT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_ERT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_ERT_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexFVTXP109") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_FVTX_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_FVTX_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_FVTX_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_FVTX_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexMBP109") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_MB_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MB_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_MB_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_MB_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexMPCP109") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_MPC_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MPC_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_MPC_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexMUP109") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_MU_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_MU_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_MU_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_MU_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run16dAu200MPCexOTP109") == 0)
    {
      gSystem->Load("librecal");
      gSystem->Load("libert.so" );
      gSystem->Load("libmpc.so" );
      gSystem->Load("libMpcEx.so" );

      cntfile = "CNT_OT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_evefile = "DST_EVE_OT_run16dAu_200GeV_CA_noVTX_pro107-0000455605-9000.root";
      dst_mpcfile = "DST_MPC_OT_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";
      dst_mpcexfile = "DST_MPCEX_OT_run16dAu_200GeV_MPCPlus_pro109-0000455605-9000.root";

      pwg_included = true;
    }

  else if (strcmp(system, "Run15pp200MuonsMBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_MB_run15pp_200GeV_Muons_pro104-0000428453-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_ERT_run15pp_200GeV_Muons_pro104-0000428453-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMPCPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_MPC_run15pp_200GeV_Muons_pro104-0000428453-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsFVTXPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_FVTX_run15pp_200GeV_Muons_pro104-0000428453-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMUPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_MU_run15pp_200GeV_Muons_pro104-0000428453-9000.root";
      dst_svxfile = "DST_SVX_MU_run15pp_200GeV_CA_pro104-0000428453-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsERTPro105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_ERT_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsFVTXPro105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_FVTX_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMBPro105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MB_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMPCPro105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MPC_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMUPro105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MU_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsOTPro105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_OT_run15pp_200GeV_Muons_pro105-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsERTPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_ERT_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsFVTXPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_FVTX_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMBPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MB_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMPCPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MPC_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsMUPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MU_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200MuonsOTPro108") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_OT_run15pp_200GeV_Muons_pro108-0000430238-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pp200FvtxERTPro107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      gSystem->Load("libspin");

      mwgfile = "MWG_ERT_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      cntfile= "CNT_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200FvtxFVTXPro107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      gSystem->Load("libspin");

      mwgfile = "MWG_FVTX_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      cntfile= "CNT_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200FvtxMBPro107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      gSystem->Load("libspin");

      mwgfile = "MWG_MB_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      cntfile= "CNT_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MB_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200FvtxMPCPro107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      gSystem->Load("libspin");

      mwgfile = "MWG_MPC_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      cntfile= "CNT_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200FvtxMUPro107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      gSystem->Load("libspin");

      mwgfile = "MWG_MU_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      cntfile= "CNT_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_MU_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }
  else if (strcmp(system, "Run15pp200FvtxOTPro107") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");
      gSystem->Load("libspin");

      mwgfile = "MWG_OT_run15pp_200GeV_Muons_noVTX_pro107-0000430238-9000.root";
      cntfile= "CNT_OT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
      dst_evefile = "DST_EVE_OT_run15pp_200GeV_CA_pro104-0000430238-9000.root";
    }

  else if (strcmp(system, "Run15pAl200MuonsERTPro105") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_ERT_run15pAl_200GeV_Muons_pro105-0000438420-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAl200MuonsFVTXPro105") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_FVTX_run15pAl_200GeV_Muons_pro105-0000438420-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAl200MuonsMBPro105") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MB_run15pAl_200GeV_Muons_pro105-0000438420-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAl200MuonsMUPro105") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MU_run15pAl_200GeV_Muons_pro105-0000438420-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAl200MuonsOTPro105") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_OT_run15pAl_200GeV_Muons_pro105-0000438420-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run14AuAu200MuonsMBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_MB_run14AuAu_200GeV_Muons_pro104-0000409840-9000.root";
      muondstfile = "MuonDST_MB_run14AuAu_200GeV_Muons_pro104-0000409840-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run14AuAu200MuonsUPPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");

      mwgfile = "MWG_UP_run14AuAu_200GeV_Muons_pro104-0000405863-9000.root";
      muondstfile = "MuonDST_UP_run14AuAu_200GeV_Muons_pro104-0000405863-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run14AuAu200MuonsERTPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");

      cntfile     = "CNT_ERT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_evefile = "DST_EVE_ERT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_svxfile = "DST_SVX_ERT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      mwgfile = "MWG_ERT_run14AuAu_200GeV_Muons_pro109-0000405863-9000.root";
      muondstfile = "MuonDST_ERT_run14AuAu_200GeV_Muons_pro109-0000405863-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run14AuAu200MuonsMBPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");

      cntfile     = "CNT_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_evefile = "DST_EVE_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_svxfile = "DST_SVX_MB_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      mwgfile = "MWG_MB_run14AuAu_200GeV_Muons_pro109-0000405863-9000.root";
      muondstfile = "MuonDST_MB_run14AuAu_200GeV_Muons_pro109-0000405863-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run14AuAu200MuonsOTPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");

      cntfile     = "CNT_OT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_evefile = "DST_EVE_OT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_svxfile = "DST_SVX_OT_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      mwgfile = "MWG_OT_run14AuAu_200GeV_Muons_pro109-0000405863-9000.root";
      muondstfile = "MuonDST_OT_run14AuAu_200GeV_Muons_pro109-0000405863-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run14AuAu200MuonsUPPro109") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librecal");
      gSystem->Load("libert");

      cntfile     = "CNT_UP_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_evefile = "DST_EVE_UP_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      dst_svxfile = "DST_SVX_UP_run14AuAu_200GeV_CA_pro109-0000405863-9000.root";
      mwgfile = "MWG_UP_run14AuAu_200GeV_Muons_pro109-0000405863-9000.root";
      muondstfile = "MuonDST_UP_run14AuAu_200GeV_Muons_pro109-0000405863-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MAnVXMBP105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_MB_run15pAu_200GeV_Muons_noVTX_pro105-0000435838-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MAnVXMUP105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_MU_run15pAu_200GeV_Muons_noVTX_pro105-0000435838-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MAnVXMPCP105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_MPC_run15pAu_200GeV_Muons_noVTX_pro105-0000435717-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MAnVXFVTXP105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_FVTX_run15pAu_200GeV_Muons_noVTX_pro105-0000435838-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MAnVXERTP105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_ERT_run15pAu_200GeV_Muons_noVTX_pro105-0000435838-9000.root";
      pwg_included = true;
    }



  else if (strcmp(system, "Run15pAu200MuonsMBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_MB_run15pAu_200GeV_Muons_pro104-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsMUPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_MU_run15pAu_200GeV_Muons_pro104-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_ERT_run15pAu_200GeV_Muons_pro104-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsFVTXPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_FVTX_run15pAu_200GeV_Muons_pro104-0000435527-9000.root";
      pwg_included = true;
    }

  else if (strcmp(system, "Run15pAu200MuonsERTPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_ERT_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      mwgfile = "MWG_ERT_run15pAu_200GeV_Muons_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsFVTXPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_FVTX_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      mwgfile = "MWG_FVTX_run15pAu_200GeV_Muons_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsMBPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_MB_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      mwgfile = "MWG_MB_run15pAu_200GeV_Muons_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsMPCPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_MPC_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      mwgfile = "MWG_MPC_run15pAu_200GeV_Muons_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsMUPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MU_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_MU_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      mwgfile = "MWG_MU_run15pAu_200GeV_Muons_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsOTPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_OT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_OT_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      mwgfile = "MWG_OT_run15pAu_200GeV_Muons_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsERTPro108") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      mwgfile = "MWG_ERT_run15pAu_200GeV_Muons_pro108-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsFVTXPro108") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      mwgfile = "MWG_FVTX_run15pAu_200GeV_Muons_pro108-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsMBPro108") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_MB_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      mwgfile = "MWG_MB_run15pAu_200GeV_Muons_pro108-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsMPCPro108") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      mwgfile = "MWG_MPC_run15pAu_200GeV_Muons_pro108-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsMUPro108") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_MU_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      mwgfile = "MWG_MU_run15pAu_200GeV_Muons_pro108-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsOTPro108") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      dst_evefile = "DST_EVE_OT_run15pAu_200GeV_CA_pro108-0000435527-9000.root";
      mwgfile = "MWG_OT_run15pAu_200GeV_Muons_pro108-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200FvtxERTPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_ERT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_ERT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_ERT_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200FvtxFVTXPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_FVTX_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_FVTX_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_FVTX_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200FvtxMBPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_MB_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200FvtxMPCPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MPC_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MPC_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_MPC_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200FvtxMUPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_MU_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MU_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_MU_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200FvtxOTPro107") == 0)
    {
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("libspin");
      gSystem->Load("libert");
      gSystem->Load("librecal");

      cntfile = "CNT_OT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_OT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_fvtxfile = "MWG_OT_run15pAu_200GeV_Muons_noVTX_pro107-0000435527-9000.root";
      pwg_included = true;
    }

  else if (strcmp(system, "Run15pAu200MuonsMBPro105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco.so");
      gSystem->Load("libMWGOO.so");
      gSystem->Load("libmutrg.so");
      gSystem->Load("librecal.so");
      gSystem->Load("libert.so" );
      gSystem->Load("libspin.so" );

      mwgfile = "MWG_MB_run15pAu_200GeV_Muons_pro105-0000435527-9000.root";
      cntfile = "CNT_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_svxfile = "DST_SVX_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_evefile = "DST_EVE_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";

      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MuonsMUPro105") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      mwgfile = "MWG_MU_run15pAu_200GeV_Muons_pro105-0000435527-9000.root";
      dst_evefile = "DST_EVE_MU_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      pwg_included = true;
    }

  else if (strcmp(system, "Run15pAu200MPCPlusMBPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      dst_evefile = "DST_EVE_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_MB_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_mpcexfile = "DST_MPCEX_MB_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      cntfile = "CNT_MB_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MPCPlusMUPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      dst_evefile = "DST_EVE_MU_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_MU_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_mpcexfile = "DST_MPCEX_MU_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      cntfile = "CNT_MU_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MPCPlusMPCPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      dst_evefile = "DST_EVE_MPC_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_MPC_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_mpcexfile = "DST_MPCEX_MPC_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      cntfile = "CNT_MPC_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      pwg_included = true;
    }
  else if (strcmp(system, "Run15pAu200MPCPlusERTPro104") == 0)
    {
      gSystem->Load("libfvtx_subsysreco.so");
      gSystem->Load("libmutoo_subsysreco");
      gSystem->Load("libfun4all.so");
      gSystem->Load("libfun4allfuncs.so");
      gSystem->Load("libfun4allfuncs_muons");
      gSystem->Load("libMWGOO");
      gSystem->Load("libmutrg");
      gSystem->Load("librpc_subsysreco");
      gSystem->Load("librpc_muotrackreco");
      gSystem->Load("libcompactCNT.so");
      gSystem->Load("librecal");
      gSystem->Load( "libBbcMultipleVtx.so" );
      gSystem->Load("libMpcExReco");

      dst_evefile = "DST_EVE_ERT_run15pAu_200GeV_CA_pro104-0000435527-9000.root";
      dst_mpcfile = "DST_MPC_ERT_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      dst_mpcexfile = "DST_MPCEX_ERT_run15pAu_200GeV_MPCPlus_pro104-0000435527-9000.root";
      pwg_included = true;
    }

  else
    {
      cout << "Unknown system: " << system << endl;
      exit(1);
    }
  if (strcmp(system, "Run12pp510ERT") == 0 ||
      strcmp(system, "Run12pp510MinBias") == 0 ||
      strcmp(system, "Run12pp510MPC") == 0 ||
      strcmp(system, "Run12pp510Muon") == 0 ||
      strcmp(system, "Run12pp510OT") == 0 ||
      strcmp(system, "Run14HeAu200ERT") == 0 ||
      strcmp(system, "Run14HeAu200MinBias") == 0 ||
      strcmp(system, "Run14HeAu200MPC") == 0 ||
      strcmp(system, "Run14HeAu200MU") == 0 ||
      strcmp(system, "Run14HeAu200OT") == 0 ||
      strcmp(system, "Run15pAu200FVTXClusAna503") == 0 ||
      strcmp(system, "Run15pAu200CAERTPro104") == 0 ||
      strcmp(system, "Run15pAu200CAFVTXPro104") == 0 ||
      strcmp(system, "Run15pAu200CAMBPro104") == 0 ||
      strcmp(system, "Run15pAu200CAMPCPro104") == 0 ||
      strcmp(system, "Run15pAu200CAMUPro104") == 0 ||
      strcmp(system, "Run15pAu200CAOTPro104") == 0 ||
      strcmp(system, "Run15pp200CAERTPro104") == 0 ||
      strcmp(system, "Run15pp200CAFVTXPro104") == 0 ||
      strcmp(system, "Run15pp200CAMBPro104") == 0 ||
      strcmp(system, "Run15pp200CAMPCPro104") == 0 ||
      strcmp(system, "Run15pp200CAMUPro104") == 0 ||
      strcmp(system, "Run15pp200CAOTPro104") == 0 ||
      strcmp(system, "Run15pAu200MuonsMBPro105") == 0)
    {
      need_vtx_geo_patch = true;
    }

  int ierror;
  gROOT->LoadMacro(modulemacro, &ierror);
  if (ierror != TInterpreter::kNoError)
    {
      cout << "Error: could not load macro " << modulemacro << endl;
      cout << "Exiting with gSystem->Exit(10)" << endl;
      gSystem->Exit(10);
    }
  Fun4AllServer *se = Fun4AllServer::instance();
  MasterRecalibratorManager *mr = new MasterRecalibratorManager("MASTERRECALIBRATORMANAGER");
  mr->FillHistos(0);
  se->registerSubsystem(mr);
  if (need_vtx_geo_patch)
  {
    SvxParManager *svxpar = new SvxParManager();
    svxpar->set_UseProductionGeo(true);
    se->registerSubsystem(svxpar);
  }
  // remove the .C from the macro name
  // Using TStrings here because stl string handling in CINT
  // does not work properly (algorithms like toLower do not work)
  TString runmac(modulemacro);
  runmac.Remove(0, runmac.Last('/') + 1); // remove leading directories
  runmac.Remove(runmac.Index("."), runmac.Length()); // remove .C extension
  runmac += "(\"";
  runmac += outfile;
  runmac += "\")";
  cout << "running user macro like: " << runmac << endl;
  // execute the user macro
  gROOT->ProcessLine(runmac, &ierror);
  if (ierror != TInterpreter::kNoError)
    {
      cout << "Error: could not execute " << runmac << endl;
      cout << "Exiting with gSystem->Exit(10)" << endl;
      gSystem->Exit(10);
    }
  // get the data types
  vector<string> indata;
  InputData(indata);
  int i = indata.size();
  for (int j = 0; j < i;j++)
    {
      TString flist =  indata[j];
      flist.ToUpper();
      if (flist == "PWG" && pwg_included)
        {
          continue;
        }
      Fun4AllInputManager *in = new Fun4AllDstInputManager(flist.Data());
      in->Verbosity(1);
      se->registerInputManager(in);
      flist.ToLower();
      if (flist == "cnt")
        {
          cnt_included = true;
          in->fileopen(cntfile);
        }
      else if (flist == "cwg")
        {
          cwg_included = true;
          in->fileopen(cwgfile);
        }
      else if (flist == "ewg")
        {
          if (ewgfile != "NONE")
            {
              in->fileopen(ewgfile);
            }
          else
            {
              cout << "No ewg file implemented" << endl;
              exit(1);
            }
        }

      else if (flist == "dst_all")
        {
          if (dst_allfile != "NONE")
            {
              in->fileopen(dst_allfile);
            }
          else
            {
              cout << "No dst_all file implemented" << endl;
              exit(1);
            }
        }
      else if (flist == "dst_eve")
        {
          if (dst_evefile != "NONE")
            {
              in->fileopen(dst_evefile);
            }
          else
            {
              cout << "No dst_eve file implemented" << endl;
              exit(1);
            }
        }
      else if (flist == "dst_fcal")
        {
          if (dst_fcalfile != "NONE")
            {
              in->fileopen(dst_fcalfile);
            }
          else
            {
              cout << "No dst_fcal file implemented" << endl;
              exit(1);
            }
        }
      else if (flist == "dst_hbd")
        {
          if (dst_hbdfile != "NONE")
            {
              in->fileopen(dst_hbdfile);
            }
          else
            {
              cout << "No dst_hbd file implemented" << endl;
              exit(1);
            }
        }
      else if (flist == "dst_mpc")
        {
          if (dst_mpcfile != "NONE")
            {
              in->fileopen(dst_mpcfile);
            }
          else
            {
              cout << "No dst_mpc file implemented" << endl;
              exit(1);
            }
        }
      else if (flist == "dst_mpcex")
        {
          if (dst_mpcexfile != "NONE")
            {
              in->fileopen(dst_mpcexfile);
            }
          else
            {
              cout << "No dst_mpcex file implemented" << endl;
              exit(1);
            }
        }
      else if (flist == "dst_rxnp")
        {
          if (dst_rxnpfile != "NONE")
            {
              in->fileopen(dst_rxnpfile);
            }
        }
      else if (flist == "dst_svx")
        {
          if (dst_svxfile != "NONE")
            {
              in->fileopen(dst_svxfile);
            }
        }
      else if (flist == "dst_fvtx")
        {
          if (dst_fvtxfile != "NONE")
            {
              in->fileopen(dst_fvtxfile);
            }
        }
      else if (flist == "dst_tec")
        {
          if (dst_tecfile != "NONE")
            {
              in->fileopen(dst_tecfile);
            }
          else
            {
              cout << "No dst_tec file implemented" << endl;
              exit(1);
            }
        }
      else if (flist == "mwg")
        {
          if (mwgfile != "NONE")
            {
              in->fileopen(mwgfile);
            }
          else
            {
              cout << "No mwg file implemented" << endl;
              exit(1);
            }
        }
      else if (flist == "muondst")
        {
          if (muondstfile != "NONE")
            {
              in->fileopen(muondstfile);
            }
          else
            {
              cout << "No muondst file implemented" << endl;
              exit(1);
            }
        }
      else if (flist == "pwg")
        {
          pwg_included = true;
          in->fileopen(pwgfile);
        }
      else if (flist == "localpol")
        {
          if (lpolfile != "NONE")
            {
              in->fileopen(lpolfile);
            }
          else
            {
              cout << "No lpol file implemented" << endl;
              exit(1);
            }
        }
      else
        {
          cout << "Unknown data type: " << flist << endl;
        }
    }

  if(!cwg_included && !cnt_included && !pwg_included){
    cout<<"You must included at least one of the following types because of the way the train is set up: CWG(Run7) or CNT/PWG"<<std::endl;
    //if(strcmp(system, "Run7AuAu200") == 0){
    //  std::cout<<"\tCWG"<<std::endl;
    //} else {
    //  std::cout<<"\tCNT"<<std::endl;
    //  std::cout<<"\tPWG"<<std::endl;
   // }
    exit(10);
  }
  if (gSystem->Getenv("JPROF_FLAGS"))
    {
      cout << "JPROF_FLAGS Env var set, adding profiler" << endl;
      gSystem->Load("libjprof.so");
      prof *Pr = new prof;
    }
  gSystem->ListLibraries();
  TString seOutFile(outfile);
  seOutFile.Insert(seOutFile.Last('/') + 1, "se-");
  gBenchmark->Start("timeme");
 
  se->run(nevnt);
  ProcInfo_t procinfo;
  gSystem->GetProcInfo(&procinfo);
  cout << "MemoryUsage " << procinfo.fMemResident << endl;
  gBenchmark->Show("timeme");
  se->End();
  se->dumpHistos(seOutFile.Data());

  cout << "Successfully Completed Analysis." << endl;
  PHTimeServer::get()->print_stat();

  int endtime = TDatime().GetTime();

  cout<<" Timing:   Start: "<<starttime<<endl<<"\t\t  "<<endtime<<endl;

  delete se;
  cout << "All done" << endl;
  gSystem->Exit(0);
}
