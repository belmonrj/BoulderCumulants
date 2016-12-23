void Run_BoulderCumulants(const char *outFile = "test_train_output.root")
{

  //-----------------//
  //--- Libraries ---//
  //-----------------//

  //gSystem->Load("libfvtx_subsysreco.so"); // must have for Run15 and must remove for Run16 and Run14
  gSystem->Load("libdAuBES_utils.so");
  gSystem->Load("libBoulderCumulants.so");
  gSystem->ListLibraries();

  //----------------------//
  //--- Fun4All Server ---//
  //----------------------//

  Fun4AllServer *se = Fun4AllServer::instance();

  // To get the FVTX tracks
  se->registerSubsystem(new FvtxReadbackDST());

  //--------------------//
  //--- User Module ----//
  //--------------------//

  BoulderCumulants *sflow = new BoulderCumulants();
  sflow->set_use_runlist(false);
  sflow->set_output_filename(outFile);
  sflow->Verbosity(0);
  se->registerSubsystem(sflow);

}

void InputData(vector<string> &indata)
{
  indata.push_back("CNT");
  indata.push_back("DST_EVE"); // must have for Run15 and Run16
  // indata.push_back("DST_FVTX"); // must have for Run15 and must remove for Run16
  // indata.push_back("MWG"); // must have for Run14 (only)
  // indata.push_back("MuonDST"); // must have for Run14 (only)
  return;
}
