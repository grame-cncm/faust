#ifndef __TAddress__
#define __TAddress__

#include "TPrintable.hh"
#include "TType.hh"
#include "TIndex.hh"

#include <vector>

struct TAddress : public TPrintable {

    virtual ~TAddress() {}

    virtual TType* getType() = 0;
};

struct TVector : public TAddress
{
    TType* fType;
    string fName;

    TVector(const string& name, TType* type):fName(name), fType(type){}

    virtual ~TVector() {}

    virtual void generate(ostream* dst, int n)
    {
        // *dst << fName; fType->generate(dst, n);
        *dst << fName;
    }

    virtual TType* getType() { return fType; }
};

struct TIndexAddress : public TAddress
{
    TAddress* fAddress;
    TIndex* fIndex;

    TIndexAddress(TAddress* address, TIndex* index):fAddress(address), fIndex(index){}

    virtual ~TIndexAddress() {}

    virtual void generate(ostream* dst, int n)
    {

    }

    virtual TType* getType() { return fAddress->getType(); }
};

struct TCastAddress : public TAddress
{
    TAddress* fAddress;
    TType* fType;

    TCastAddress(TAddress* address, TType* type):fAddress(address), fType(type){}

    virtual ~TCastAddress() {}

    virtual void generate(ostream* dst, int n)
    {

    }

    virtual TType* getType() { return fAddress->getType(); }
};

struct TShiftAddress : public TAddress
{
    TAddress* fAddress;
    TIndex* fIndex;

    TShiftAddress(TAddress* address, TIndex* index):fAddress(address), fIndex(index){}

    virtual ~TShiftAddress() {}

    virtual void generate(ostream* dst, int n)
    {

    }

    virtual TType* getType() { return fAddress->getType(); }
};

#endif


