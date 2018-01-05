#include <iostream>
#include "BoulderCumulants.h"

using std::cout;
using std::endl;

void BoulderCumulants::SetQvectorOffsets(int run)
{
  if ( run < 0 ) return;
  if ( _verbosity > 1 ) cout << "Q-vector offsets: doing nothing..." << endl;
}
