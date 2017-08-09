
const int number_of_tests = 10; // update as needed, but don't want to go beyond 10...
const int xhash = 0;
const int xdesc = 1;
TString hash_description[2][number_of_tests];

//void dothething(int, int, int, int, int);

void thing1()
{

  hash_description[0][0] = "10595";  hash_description[1][0] = "Janu";
  hash_description[0][1] = "11078";  hash_description[1][1] = "April";
  hash_description[0][2] = "11177";  hash_description[1][2] = "May";
  hash_description[0][3] = "11508";  hash_description[1][3] = "Jin 1";
  hash_description[0][4] = "11511";  hash_description[1][4] = "Jin 2";
  hash_description[0][5] = "11539";  hash_description[1][5] = "RemJ 1";
  hash_description[0][6] = "11540";  hash_description[1][6] = "RemJ 2";
  hash_description[0][7] = "11552";  hash_description[1][7] = "Base";
  hash_description[0][8] = "11596";  hash_description[1][8] = "DTC";
  hash_description[0][9] = "11601";  hash_description[1][9] = "New Stuff";

  gROOT->ProcessLine(".L dothething_diagnostics.C");
  dothething_diagnostics(200,0,1,2,4);
  dothething_diagnostics(200,3,4,5,6);
  dothething_diagnostics(200,4,7,8,9);

  gROOT->ProcessLine(".L dothething_components.C");
  dothething_components(200,0,1,2,4);
  dothething_components(200,3,4,5,6);
  dothething_components(200,4,7,8,9);

  gROOT->ProcessLine(".L dothething_cumulants.C");
  dothething_cumulants(200,0,1,2,4);
  dothething_cumulants(200,3,4,5,6);
  dothething_cumulants(200,4,7,8,9);

}

