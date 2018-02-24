#!/bin/sh

root -b -l -q do_special.C
root -b -l -q get_subevents.C
root -b -l -q sigma.C
root -b -l -q plot_v3.C
root -b -l -q star_v34.C

cp FigsSubevents/cent_subevents_v24x03.pdf CollectFigures/
cp FigsSubevents/cent_subevents_v24x03.png CollectFigures/
cp FigsRecursion/recursion_scent_v22468.pdf CollectFigures/
cp FigsRecursion/recursion_scent_v22468.png CollectFigures/
cp FigsSigma/sigma_cent_x05.pdf CollectFigures/
cp FigsSigma/sigma_cent_x05.png CollectFigures/
cp FigsSpecial/special_cent_v222.pdf CollectFigures/
cp FigsSpecial/special_cent_v222.png CollectFigures/
cp FigsWork/v32.pdf CollectFigures/
cp FigsWork/v32.png CollectFigures/
cp STAR/c34_star.pdf CollectFigures/
cp STAR/c34_star.png CollectFigures/
