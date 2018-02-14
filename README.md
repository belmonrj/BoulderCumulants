# This is BoulderCumulants, a PHENIX analysis code for doing multi-particle cumulant using the FVTX

## These are the main analysis files

#### BoulderCumulants.C
class implementation file, has only the constructor and destructor

#### BoulderCumulants.h
class header file, has all the global level variables, function declarations, etc

#### BoulderCumulantsFunctions.C
class file for various functions to compute the various multi-particle correlations

#### BoulderCumulantsInitializations.C
class file for the initialization functions, particularly the TTree and histograms

#### BoulderCumulantsLinkDef.h
standard ROOT link def file

#### BoulderCumulantsOffsets.C
class file for storing the Q-vector offsets

#### BoulderCumulantsOffsetsRBR.C
class file for storing the run-by-run offsets, not currently used

#### BoulderCumulantsProcessEvent.C
class file for process_event, this is the main part of the analysis code

#### BoulderCumulantsSpecialEventCuts.C
class file for the special event cut that matches the BBC charge and NFVTXtracks

## Additional basic PHENIX universe files

Makefile.am
autogen.sh
configure.in

## Macros to test the code

RunMyMacro.C
Run_BoulderCumulants.C
Run_BoulderCumulantsRun14.C
Run_BoulderCumulantsRun15.C
Run_BoulderCumulantsRun16.C

## Additional files

.gitattributes
BCpseudocode.C

## Directories

#### WorkAuAu
Working area for the AuAu analysis

#### work
Working area for small systems


