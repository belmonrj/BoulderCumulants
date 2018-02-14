# Important plotting macros:

## do_special.C
makes the v2{2gap,4,6,8} plot and the v2{2,2gap} plot

## get_subevents.C
makes the v2{4sub} plot

## sigma.C
makes the sigma/v2 plot using v2{2gap} and v2{4}

## star_v34.C
makes the v34 plot with comparison to STAR



# Supporting macros:

## calc_cumulants.C
takes histos for <k> and produces cn{k} and vn{k}

## calc_subevents.C
takes the <4>_sub and <2>_sub and produces the cn and vn

## plot_recv2.C
takes the vn{k} histograms and makes plots

## plot_recomp.C
takes the <k> and cn{k} histograms and makes two-panel plots

## plot_subcomp.C
same as plot_recomp but for the subevents

