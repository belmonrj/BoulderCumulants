
const int number_of_tests = 7; // update as needed
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

  gROOT->ProcessLine(".L dothething_components.C");
  dothething_components(200,0,1,2,4);

  gROOT->ProcessLine(".L dothething_cumulants.C");
  dothething_cumulants(200,0,1,2,4);

}

