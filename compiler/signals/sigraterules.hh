#ifndef SIGRATERULES_HH
#define SIGRATERULES_HH

#include <iostream>
#include "tlib.hh"

ostream&  printRateEnvironment(ostream& fout, Tree E);
Tree inferreMultiRates(Tree lsig, bool& success);
ostream&  printRateEnvironmentList(ostream& fout, Tree LE);

#endif // SIGRATERULES_HH
