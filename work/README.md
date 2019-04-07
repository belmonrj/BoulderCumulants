# BoulderCumulants



## This is the subdirectory for work on small systems



File name | description
--------- | -----------
do_acceptance.C | compares acceptance corrected quantities to assess systematic uncertainty, uses all_cumulants_acc.root
do_systematics.C | compares systematic variations to the baseline, needs special root files to be made using process_cumulants.C using special output files
plot_sides.C | makes a comparison of FVTX north only, southonly, and combined (uses all_cumulants_northsouth.root)
process_cumulants.C | the main macro to create the histogram file with all of the results (all_cumulants_out.root)
process_cumulants_NS.C | special variant of process_cumulants to generate all_cumulants_northsouth.root
process_cumulants_acc.C | special variant of process_cumulants to generate all_cumulants_acc.root
process_cumulants_old.C | old verion of process_cumulants, not sure why I'm keeping it around
process_cumulants_v3.C | special variant of process_cumulants to do v3 instead of v2
small_six.C | macro to look at v2{6} in Run16dAu
tracks_charge_function.C | output of make_do_cuts.C

