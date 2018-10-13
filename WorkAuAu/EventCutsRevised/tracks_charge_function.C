
bool tracks_charge_function(int ntracks, double chargesum)
{

  double cutlow = 0;
  double cuthigh = 0;

  if ( ntracks < 0 ) return false;
  else if ( ntracks > 0 && ntracks <= 9) { cutlow = 1.33165; cuthigh = 4.86648; }
  else if ( ntracks > 9 && ntracks <= 19) { cutlow = 1.30461; cuthigh = 4.56379; }
  else if ( ntracks > 19 && ntracks <= 29) { cutlow = 1.51533; cuthigh = 4.37567; }
  else if ( ntracks > 29 && ntracks <= 39) { cutlow = 1.66398; cuthigh = 4.22569; }
  else if ( ntracks > 39 && ntracks <= 49) { cutlow = 1.76699; cuthigh = 4.10057; }
  else if ( ntracks > 49 && ntracks <= 59) { cutlow = 1.84294; cuthigh = 3.99654; }
  else if ( ntracks > 59 && ntracks <= 69) { cutlow = 1.9016; cuthigh = 3.91053; }
  else if ( ntracks > 69 && ntracks <= 79) { cutlow = 1.94837; cuthigh = 3.83915; }
  else if ( ntracks > 79 && ntracks <= 89) { cutlow = 1.98675; cuthigh = 3.77976; }
  else if ( ntracks > 89 && ntracks <= 99) { cutlow = 2.01875; cuthigh = 3.72971; }
  else if ( ntracks > 99 && ntracks <= 109) { cutlow = 2.04633; cuthigh = 3.68731; }
  else if ( ntracks > 109 && ntracks <= 119) { cutlow = 2.07023; cuthigh = 3.65073; }
  else if ( ntracks > 119 && ntracks <= 129) { cutlow = 2.09142; cuthigh = 3.61918; }
  else if ( ntracks > 129 && ntracks <= 139) { cutlow = 2.11038; cuthigh = 3.59156; }
  else if ( ntracks > 139 && ntracks <= 149) { cutlow = 2.12776; cuthigh = 3.56693; }
  else if ( ntracks > 149 && ntracks <= 159) { cutlow = 2.14364; cuthigh = 3.54514; }
  else if ( ntracks > 159 && ntracks <= 169) { cutlow = 2.15833; cuthigh = 3.52549; }
  else if ( ntracks > 169 && ntracks <= 179) { cutlow = 2.17209; cuthigh = 3.50778; }
  else if ( ntracks > 179 && ntracks <= 189) { cutlow = 2.18489; cuthigh = 3.49158; }
  else if ( ntracks > 189 && ntracks <= 199) { cutlow = 2.19689; cuthigh = 3.47695; }
  else if ( ntracks > 199 && ntracks <= 209) { cutlow = 2.20852; cuthigh = 3.46321; }
  else if ( ntracks > 209 && ntracks <= 219) { cutlow = 2.21944; cuthigh = 3.45063; }
  else if ( ntracks > 219 && ntracks <= 229) { cutlow = 2.22997; cuthigh = 3.43888; }
  else if ( ntracks > 229 && ntracks <= 239) { cutlow = 2.23989; cuthigh = 3.42809; }
  else if ( ntracks > 239 && ntracks <= 249) { cutlow = 2.24963; cuthigh = 3.41786; }
  else if ( ntracks > 249 && ntracks <= 259) { cutlow = 2.25889; cuthigh = 3.40818; }
  else if ( ntracks > 259 && ntracks <= 269) { cutlow = 2.26771; cuthigh = 3.39943; }
  else if ( ntracks > 269 && ntracks <= 279) { cutlow = 2.27636; cuthigh = 3.39082; }
  else if ( ntracks > 279 && ntracks <= 289) { cutlow = 2.28459; cuthigh = 3.38278; }
  else if ( ntracks > 289 && ntracks <= 299) { cutlow = 2.2926; cuthigh = 3.37523; }
  else if ( ntracks > 299 && ntracks <= 309) { cutlow = 2.3002; cuthigh = 3.36807; }
  else if ( ntracks > 309 && ntracks <= 319) { cutlow = 2.30781; cuthigh = 3.36111; }
  else if ( ntracks > 319 && ntracks <= 329) { cutlow = 2.31512; cuthigh = 3.35424; }
  else if ( ntracks > 329 && ntracks <= 339) { cutlow = 2.32269; cuthigh = 3.34728; }
  else if ( ntracks > 339 && ntracks <= 349) { cutlow = 2.33019; cuthigh = 3.34012; }
  else if ( ntracks > 349 && ntracks <= 359) { cutlow = 2.33811; cuthigh = 3.33229; }
  else if ( ntracks > 359 && ntracks <= 369) { cutlow = 2.34636; cuthigh = 3.32356; }
  else if ( ntracks > 369 && ntracks <= 379) { cutlow = 2.35461; cuthigh = 3.31482; }
  else if ( ntracks > 379 && ntracks <= 389) { cutlow = 2.36241; cuthigh = 3.30652; }
  else if ( ntracks > 389 && ntracks <= 399) { cutlow = 2.36958; cuthigh = 3.29883; }
  else if ( ntracks > 399 && ntracks <= 409) { cutlow = 2.37614; cuthigh = 3.29157; }
  else if ( ntracks > 409 && ntracks <= 419) { cutlow = 2.38238; cuthigh = 3.28478; }
  else if ( ntracks > 419 && ntracks <= 429) { cutlow = 2.38782; cuthigh = 3.27828; }
  else if ( ntracks > 429 && ntracks <= 439) { cutlow = 2.39303; cuthigh = 3.27203; }
  else if ( ntracks > 439 && ntracks <= 449) { cutlow = 2.39784; cuthigh = 3.26606; }
  else if ( ntracks > 449 && ntracks <= 459) { cutlow = 2.40211; cuthigh = 3.26025; }
  else if ( ntracks > 459 && ntracks <= 469) { cutlow = 2.40628; cuthigh = 3.25436; }
  else if ( ntracks > 469 && ntracks <= 479) { cutlow = 2.40995; cuthigh = 3.24829; }
  else if ( ntracks > 479 && ntracks <= 489) { cutlow = 2.41331; cuthigh = 3.24162; }
  else if ( ntracks > 489 && ntracks <= 499) { cutlow = 2.41623; cuthigh = 3.23425; }
  else if ( ntracks > 499 && ntracks <= 509) { cutlow = 2.41885; cuthigh = 3.22526; }
  else if ( ntracks > 509 && ntracks <= 519) { cutlow = 2.42007; cuthigh = 3.21454; }
  else if ( ntracks > 519 && ntracks <= 529) { cutlow = 2.41984; cuthigh = 3.20113; }
  else if ( ntracks > 529 && ntracks <= 539) { cutlow = 2.41701; cuthigh = 3.18527; }
  else if ( ntracks > 539 && ntracks <= 549) { cutlow = 2.41092; cuthigh = 3.16618; }
  else if ( ntracks > 549 && ntracks <= 559) { cutlow = 2.40031; cuthigh = 3.14449; }
  else if ( ntracks > 559 && ntracks <= 569) { cutlow = 2.38433; cuthigh = 3.12038; }
  else if ( ntracks > 569 && ntracks <= 579) { cutlow = 2.36174; cuthigh = 3.09414; }
  else if ( ntracks > 579 && ntracks <= 589) { cutlow = 2.33196; cuthigh = 3.06539; }
  else if ( ntracks > 589 && ntracks <= 599) { cutlow = 2.2939; cuthigh = 3.03398; }
  else if ( ntracks > 599 && ntracks <= 609) { cutlow = 2.24691; cuthigh = 2.99854; }
  else if ( ntracks > 609 && ntracks <= 619) { cutlow = 2.19197; cuthigh = 2.95674; }
  else if ( ntracks > 619 && ntracks <= 629) { cutlow = 2.13327; cuthigh = 2.9049; }
  else if ( ntracks > 629 && ntracks <= 639) { cutlow = 2.07798; cuthigh = 2.83959; }
  else if ( ntracks > 639 && ntracks <= 649) { cutlow = 2.03553; cuthigh = 2.76418; }
  else return false;

  double quantity = chargesum/double(ntracks);
  if ( quantity >= cutlow && quantity <= cuthigh ) return true;
  else return false;

}

