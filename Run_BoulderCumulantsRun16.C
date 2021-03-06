void Run_BoulderCumulantsRun16(const char *outFile = "test_train_output.root")
{

  //-----------------//
  //--- Libraries ---//
  //-----------------//

  gSystem->Load("libdAuBES_utils.so");
  gSystem->Load("libDoubleInteractionUtil.so");
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
  sflow->set_output_filename(outFile);
  sflow->set_create_ttree(false);
  sflow->Verbosity(0);
  se->registerSubsystem(sflow);

}

void InputData(vector<string> &indata)
{
  indata.push_back("CNT");
  indata.push_back("DST_EVE");
  return;
}
