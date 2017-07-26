#include "BoulderCumulants.h"

bool BoulderCumulants::PassesTracksChargeRatio(int ntracks, double chargesum)
{

  double cutlow = 0;
  double cuthigh = 0;

  if ( ntracks < 0 ) return false;
  else if ( ntracks > 0 && ntracks <= 9) { cutlow = 1.26624; cuthigh = 4.83333; }
  else if ( ntracks > 9 && ntracks <= 19) { cutlow = 1.24411; cuthigh = 4.5397; }
  else if ( ntracks > 19 && ntracks <= 29) { cutlow = 1.48974; cuthigh = 4.36608; }
  else if ( ntracks > 29 && ntracks <= 39) { cutlow = 1.65513; cuthigh = 4.20903; }
  else if ( ntracks > 39 && ntracks <= 49) { cutlow = 1.75586; cuthigh = 4.07267; }
  else if ( ntracks > 49 && ntracks <= 59) { cutlow = 1.83064; cuthigh = 3.96117; }
  else if ( ntracks > 59 && ntracks <= 69) { cutlow = 1.88972; cuthigh = 3.87007; }
  else if ( ntracks > 69 && ntracks <= 79) { cutlow = 1.93752; cuthigh = 3.79651; }
  else if ( ntracks > 79 && ntracks <= 89) { cutlow = 1.97757; cuthigh = 3.73674; }
  else if ( ntracks > 89 && ntracks <= 99) { cutlow = 2.01128; cuthigh = 3.68721; }
  else if ( ntracks > 99 && ntracks <= 109) { cutlow = 2.04068; cuthigh = 3.64709; }
  else if ( ntracks > 109 && ntracks <= 119) { cutlow = 2.06705; cuthigh = 3.61356; }
  else if ( ntracks > 119 && ntracks <= 129) { cutlow = 2.09048; cuthigh = 3.58507; }
  else if ( ntracks > 129 && ntracks <= 139) { cutlow = 2.11196; cuthigh = 3.56178; }
  else if ( ntracks > 139 && ntracks <= 149) { cutlow = 2.13272; cuthigh = 3.54134; }
  else if ( ntracks > 149 && ntracks <= 159) { cutlow = 2.15168; cuthigh = 3.52402; }
  else if ( ntracks > 159 && ntracks <= 169) { cutlow = 2.17009; cuthigh = 3.50902; }
  else if ( ntracks > 169 && ntracks <= 179) { cutlow = 2.18793; cuthigh = 3.49644; }
  else if ( ntracks > 179 && ntracks <= 189) { cutlow = 2.20541; cuthigh = 3.48503; }
  else if ( ntracks > 189 && ntracks <= 199) { cutlow = 2.22178; cuthigh = 3.47557; }
  else if ( ntracks > 199 && ntracks <= 209) { cutlow = 2.23807; cuthigh = 3.46716; }
  else if ( ntracks > 209 && ntracks <= 219) { cutlow = 2.25455; cuthigh = 3.45903; }
  else if ( ntracks > 219 && ntracks <= 229) { cutlow = 2.27053; cuthigh = 3.45224; }
  else if ( ntracks > 229 && ntracks <= 239) { cutlow = 2.2858; cuthigh = 3.44668; }
  else if ( ntracks > 239 && ntracks <= 249) { cutlow = 2.30139; cuthigh = 3.44147; }
  else if ( ntracks > 249 && ntracks <= 259) { cutlow = 2.31679; cuthigh = 3.43647; }
  else if ( ntracks > 259 && ntracks <= 269) { cutlow = 2.33224; cuthigh = 3.43203; }
  else if ( ntracks > 269 && ntracks <= 279) { cutlow = 2.34649; cuthigh = 3.42846; }
  else if ( ntracks > 279 && ntracks <= 289) { cutlow = 2.36121; cuthigh = 3.42516; }
  else if ( ntracks > 289 && ntracks <= 299) { cutlow = 2.37594; cuthigh = 3.42181; }
  else if ( ntracks > 299 && ntracks <= 309) { cutlow = 2.38983; cuthigh = 3.41975; }
  else if ( ntracks > 309 && ntracks <= 319) { cutlow = 2.40345; cuthigh = 3.41707; }
  else if ( ntracks > 319 && ntracks <= 329) { cutlow = 2.41753; cuthigh = 3.41456; }
  else if ( ntracks > 329 && ntracks <= 339) { cutlow = 2.43067; cuthigh = 3.41276; }
  else if ( ntracks > 339 && ntracks <= 349) { cutlow = 2.44403; cuthigh = 3.41056; }
  else if ( ntracks > 349 && ntracks <= 359) { cutlow = 2.45727; cuthigh = 3.4082; }
  else if ( ntracks > 359 && ntracks <= 369) { cutlow = 2.47057; cuthigh = 3.40582; }
  else if ( ntracks > 369 && ntracks <= 379) { cutlow = 2.4831; cuthigh = 3.40341; }
  else if ( ntracks > 379 && ntracks <= 389) { cutlow = 2.4953; cuthigh = 3.40121; }
  else if ( ntracks > 389 && ntracks <= 399) { cutlow = 2.50737; cuthigh = 3.39855; }
  else if ( ntracks > 399 && ntracks <= 409) { cutlow = 2.51884; cuthigh = 3.39659; }
  else if ( ntracks > 409 && ntracks <= 419) { cutlow = 2.52947; cuthigh = 3.39442; }
  else if ( ntracks > 419 && ntracks <= 429) { cutlow = 2.54032; cuthigh = 3.39145; }
  else if ( ntracks > 429 && ntracks <= 439) { cutlow = 2.55046; cuthigh = 3.38881; }
  else if ( ntracks > 439 && ntracks <= 449) { cutlow = 2.5604; cuthigh = 3.38587; }
  else if ( ntracks > 449 && ntracks <= 459) { cutlow = 2.56931; cuthigh = 3.38274; }
  else if ( ntracks > 459 && ntracks <= 469) { cutlow = 2.57809; cuthigh = 3.37954; }
  else if ( ntracks > 469 && ntracks <= 479) { cutlow = 2.58634; cuthigh = 3.37518; }
  else if ( ntracks > 479 && ntracks <= 489) { cutlow = 2.59408; cuthigh = 3.37061; }
  else if ( ntracks > 489 && ntracks <= 499) { cutlow = 2.60156; cuthigh = 3.36415; }
  else if ( ntracks > 499 && ntracks <= 509) { cutlow = 2.60904; cuthigh = 3.35493; }
  else if ( ntracks > 509 && ntracks <= 519) { cutlow = 2.61484; cuthigh = 3.34285; }
  else if ( ntracks > 519 && ntracks <= 529) { cutlow = 2.6204; cuthigh = 3.32513; }
  else if ( ntracks > 529 && ntracks <= 539) { cutlow = 2.62338; cuthigh = 3.30204; }
  else if ( ntracks > 539 && ntracks <= 549) { cutlow = 2.62227; cuthigh = 3.27388; }
  else if ( ntracks > 549 && ntracks <= 559) { cutlow = 2.61717; cuthigh = 3.24057; }
  else if ( ntracks > 559 && ntracks <= 569) { cutlow = 2.60631; cuthigh = 3.20419; }
  else if ( ntracks > 569 && ntracks <= 579) { cutlow = 2.58998; cuthigh = 3.16582; }
  else if ( ntracks > 579 && ntracks <= 589) { cutlow = 2.56737; cuthigh = 3.12705; }
  else if ( ntracks > 589 && ntracks <= 599) { cutlow = 2.54; cuthigh = 3.08803; }
  else if ( ntracks > 599 && ntracks <= 609) { cutlow = 2.50623; cuthigh = 3.05171; }
  else if ( ntracks > 609 && ntracks <= 619) { cutlow = 2.46793; cuthigh = 3.01548; }
  else if ( ntracks > 619 && ntracks <= 629) { cutlow = 2.42126; cuthigh = 2.98444; }
  else if ( ntracks > 629 && ntracks <= 639) { cutlow = 2.36944; cuthigh = 2.95869; }
  else if ( ntracks > 639 && ntracks <= 649) { cutlow = 2.30715; cuthigh = 2.94763; }
  else return false;

  double quantity = chargesum/double(ntracks);
  if ( quantity >= cutlow && quantity <= cuthigh ) return true;
  else return false;

}

