# Quick script

Script | Description
------ | -----------
analysis.sh | runs the four macros below (important plotting macros)



# Important plotting macros:

Macro | Description
----- | -----------
do_special.C | makes the v2{2gap,4,6,8} plot and the v2{2,2gap} plot
get_subevents.C | makes the v2{4sub} plot
get_sigma.C | makes the sigma/v2 plot using v2{2gap} and v2{4}
plot_v3.C | makes the v3{2gap} plot
star_v34.C | makes the v34 plot with comparison to STAR



# Supporting macros:

Macro | Description
----- | -----------
calc_cumulants.C | takes histos for <k> and produces cn{k} and vn{k}
calc_subevents.C | takes the <4>_sub and <2>_sub and produces the cn and vn
hsqrt.C | defines a simple function that takes the square root of a histogram and returns it as a TH1D*, leaving the original histogram unaffected
plot_recv2.C | takes the vn{k} histograms and makes plots
plot_recomp.C | takes the <k> and cn{k} histograms and makes two-panel plots
plot_subcomp.C | same as plot_recomp but for the subevents



# Systematics macros:

Macro | Description
----- | -----------
get_sys.C | main macro, does systematics for all v2 and v3
sigma_sys.C | small macro to look at the sysetmatics for the sigma/v2 (uses get_sigma)
systematics_helper.C | support macro that does the actual calculations for the systematics

