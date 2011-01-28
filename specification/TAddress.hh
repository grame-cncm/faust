#ifndef __TAddress__
#define __TAddress__

#include "TPrintable.hh"
#include "TType.hh"

#include <vector>

struct TAddress : public TPrintable
{
    TType* fType;
    string fName;

    TAddress(const string& name, TType* type):fName(name), fType(type){}

    virtual ~TAddress() {}

    virtual void generate(ostream* dst, int n)
    {
       // *dst << fName; fType->generate(dst, n);
        *dst << fName;
    }

    TAddress* getIndexedAddress(const vector<int>& access);

    TAddress* getAddress(int access);
};


#endif


