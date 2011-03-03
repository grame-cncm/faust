#ifndef __TPrintable__
#define __TPrintable__

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

using namespace std;


struct TPrintable
{
    virtual ~TPrintable () {}

    virtual void generate(ostream* dst, int n) = 0;
    virtual void generateCPP(ostream* dst, int n) = 0;
    virtual void generateCPPNoAlias(ostream* dst, int n) = 0;
};


//#define ALT_VECTOR 1

#endif


