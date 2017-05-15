#include "BoulderCumulants.h"

bool BoulderCumulants::PassesTracksChargeRatio(int ntracks, double chargesum)
{

  double cutlow = 0;
  double cuthigh = 0;

  if ( ntracks < 0 ) return false;
  else if ( ntracks > 0 && ntracks <= 28) { cutlow = 0.65; cuthigh = 4.45; }
  else if ( ntracks > 28 && ntracks <= 56) { cutlow = 1.35; cuthigh = 3.65; }
  else if ( ntracks > 56 && ntracks <= 84) { cutlow = 1.55; cuthigh = 3.25; }
  else if ( ntracks > 84 && ntracks <= 112) { cutlow = 1.65; cuthigh = 3.05; }
  else if ( ntracks > 112 && ntracks <= 140) { cutlow = 1.65; cuthigh = 2.85; }
  else if ( ntracks > 140 && ntracks <= 168) { cutlow = 1.65; cuthigh = 2.75; }
  else if ( ntracks > 168 && ntracks <= 196) { cutlow = 1.65; cuthigh = 2.75; }
  else if ( ntracks > 196 && ntracks <= 224) { cutlow = 1.65; cuthigh = 2.65; }
  else if ( ntracks > 224 && ntracks <= 252) { cutlow = 1.65; cuthigh = 2.55; }
  else if ( ntracks > 252 && ntracks <= 280) { cutlow = 1.65; cuthigh = 2.55; }
  else if ( ntracks > 280 && ntracks <= 308) { cutlow = 1.65; cuthigh = 2.55; }
  else if ( ntracks > 308 && ntracks <= 336) { cutlow = 1.65; cuthigh = 2.45; }
  else if ( ntracks > 336 && ntracks <= 364) { cutlow = 1.65; cuthigh = 2.45; }
  else if ( ntracks > 364 && ntracks <= 392) { cutlow = 1.65; cuthigh = 2.45; }
  else if ( ntracks > 392 && ntracks <= 420) { cutlow = 1.65; cuthigh = 2.45; }
  else if ( ntracks > 420 && ntracks <= 448) { cutlow = 1.65; cuthigh = 2.35; }
  else if ( ntracks > 448 && ntracks <= 476) { cutlow = 1.65; cuthigh = 2.35; }
  else if ( ntracks > 476 && ntracks <= 504) { cutlow = 1.65; cuthigh = 2.35; }
  else if ( ntracks > 504 && ntracks <= 532) { cutlow = 1.65; cuthigh = 2.35; }
  else if ( ntracks > 532 && ntracks <= 560) { cutlow = 1.65; cuthigh = 2.25; }
  else if ( ntracks > 560 && ntracks <= 588) { cutlow = 1.65; cuthigh = 2.25; }
  else if ( ntracks > 588 && ntracks <= 616) { cutlow = 1.55; cuthigh = 2.25; }
  else if ( ntracks > 616 && ntracks <= 644) { cutlow = 1.55; cuthigh = 2.15; }
  else if ( ntracks > 644 && ntracks <= 672) { cutlow = 1.55; cuthigh = 2.15; }
  else if ( ntracks > 672 && ntracks <= 700) { cutlow = 1.55; cuthigh = 2.05; }
  else if ( ntracks > 700 && ntracks <= 728) { cutlow = 1.55; cuthigh = 2.05; }
  else if ( ntracks > 728 && ntracks <= 756) { cutlow = 1.55; cuthigh = 2.05; }
  else if ( ntracks > 756 && ntracks <= 784) { cutlow = 1.55; cuthigh = 2.05; }
  else if ( ntracks > 784 && ntracks <= 812) { cutlow = 1.55; cuthigh = 1.95; }
  else if ( ntracks > 812 && ntracks <= 840) { cutlow = 1.55; cuthigh = 1.95; }
  else if ( ntracks > 840 && ntracks <= 868) { cutlow = 1.55; cuthigh = 1.95; }
  else if ( ntracks > 868 && ntracks <= 896) { cutlow = 1.45; cuthigh = 1.95; }
  else if ( ntracks > 896 && ntracks <= 924) { cutlow = 1.45; cuthigh = 1.85; }
  else if ( ntracks > 924 && ntracks <= 952) { cutlow = 1.45; cuthigh = 1.85; }
  else if ( ntracks > 952 && ntracks <= 980) { cutlow = 1.45; cuthigh = 1.85; }
  else if ( ntracks > 980 && ntracks <= 1008) { cutlow = 1.45; cuthigh = 1.75; }
  else if ( ntracks > 1008 && ntracks <= 1036) { cutlow = 1.45; cuthigh = 1.75; }
  else if ( ntracks > 1036 && ntracks <= 1064) { cutlow = 1.45; cuthigh = 1.65; }
  else if ( ntracks > 1064 && ntracks <= 1092) { cutlow = 1.45; cuthigh = 1.65; }
  else if ( ntracks > 1092 && ntracks <= 1120) { cutlow = 1.35; cuthigh = 1.65; }
  else if ( ntracks > 1120 && ntracks <= 1148) { cutlow = 1.35; cuthigh = 1.55; }
  else if ( ntracks > 1148 && ntracks <= 1176) { cutlow = 1.35; cuthigh = 1.55; }
  else if ( ntracks > 1176 && ntracks <= 1204) { cutlow = 1.35; cuthigh = 1.55; }
  else if ( ntracks > 1204 && ntracks <= 1232) { cutlow = 1.35; cuthigh = 1.45; }
  else if ( ntracks > 1232 && ntracks <= 1260) { cutlow = 1.25; cuthigh = 1.45; }
  else if ( ntracks > 1260 && ntracks <= 1288) { cutlow = 1.25; cuthigh = 1.45; }
  else if ( ntracks > 1288 && ntracks <= 1316) { cutlow = 1.25; cuthigh = 1.45; }
  else if ( ntracks > 1316 && ntracks <= 1344) { cutlow = 1.25; cuthigh = 1.45; }
  else if ( ntracks > 1344 && ntracks <= 1372) { cutlow = 1.15; cuthigh = 1.45; }
  else if ( ntracks > 1372 && ntracks <= 1400) { cutlow = 0.95; cuthigh = 1.35; }
  else return false;

  double quantity = chargesum/double(ntracks);
  if ( quantity >= cutlow && quantity <= cuthigh ) return true;
  else return false;

}

