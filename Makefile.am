AUTOMAKE_OPTIONS = foreign

INCLUDES = \
	-I$(includedir) \
	-I$(OFFLINE_MAIN)/include \
	-I$(ROOTSYS)/include

lib_LTLIBRARIES = \
  libBoulderCumulants.la

noinst_HEADERS = \
  BoulderCumulants.h \
  BoulderCumulantsLinkDef.h

libBoulderCumulants_la_SOURCES = \
  BoulderCumulants.C \
  BoulderCumulantsFunctions.C \
  BoulderCumulantsOffsets.C \
  BoulderCumulantsOffsetsRBR.C \
  BoulderCumulantsSpecialEventCuts.C \
  BoulderCumulants_Dict.C

libBoulderCumulants_la_LIBADD = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib \
  -lSubsysReco \
  -lTOAD

# Rule for generating CINT dictionaries from class headers.
BoulderCumulants_Dict.C: \
  BoulderCumulants.h \
  BoulderCumulantsLinkDef.h
	rootcint -f $@ -c $(DEFAULT_INCLUDES) $(INCLUDES) $^

clean-local:
	rm -f *Dict*
