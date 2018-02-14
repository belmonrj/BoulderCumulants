# This is BoulderCumulants, a PHENIX analysis code for doing multi-particle cumulant using the FVTX

## These are the main analysis files

File name | description
--------- | -----------
BoulderCumulants.C | class implementation file, has only the constructor and destructor
BoulderCumulants.h | class header file, has all the global level variables, function declarations, etc
BoulderCumulantsFunctions.C | class file for various functions to compute the various multi-particle correlations
BoulderCumulantsInitializations.C | class file for the initialization functions, particularly the TTree and histograms
BoulderCumulantsLinkDef.h | standard ROOT link def file
BoulderCumulantsOffsets.C | class file for storing the Q-vector offsets
BoulderCumulantsOffsetsRBR.C | class file for storing the run-by-run offsets, not currently used
BoulderCumulantsProcessEvent.C | class file for process_event, this is the main part of the analysis code
BoulderCumulantsSpecialEventCuts.C | class file for the special event cut that matches the BBC charge and NFVTXtracks

## Additional basic PHENIX universe files

File name | description
--------- | -----------
Makefile.am | standard makefile
autogen.sh | standard autogen file
configure.in | standard configure file

## Macros to test the code

File name | description
--------- | -----------
RunMyMacro.C | from offline/AnalysisTrain/pat/macro
Run_BoulderCumulants.C | user defined macro to run the code
Run_BoulderCumulantsRun14.C | specific settings for Run14 AuAu/HeAu
Run_BoulderCumulantsRun15.C | specific settings for Run15 pAu
Run_BoulderCumulantsRun16.C | specific settings for Run14 dAu

## Additional files

File name | description
--------- | -----------
.gitattributes | get the linguistics right
BCpseudocode.C | pseudocode showing the basic calculations

## Directories

**WorkAuAu** - Working area for the AuAu analysis

**work** - Working area for small systems


