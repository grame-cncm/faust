#ifndef DELAYLINE_HH_
#define DELAYLINE_HH_

#include <string>
#include "sigtype.hh"
#include "klass.hh"

void  vectorLoop (Klass* k, const string& tname, const string& dlname, const string& cexp);
void  dlineLoop (Klass* k, const string& tname, const string& dlname, int delay, const string& cexp);


#endif /*DELAYLINE_HH_*/
