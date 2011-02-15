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
    int fSize;

    TVector(const string& name, TType* type, int size):fName(name), fType(type), fSize(size){}

    virtual ~TVector() {}

    virtual void generate(ostream* dst, int n)
    {
        fType->generate(dst, n);
        *dst << "[" << fSize << "]";
        *dst << " " << fName;
    }

    virtual void generateCPP(ostream* dst, int n)
    {
        //fType->generateCPP(dst, n);
        *dst << fName;
    }

    virtual TType* getType() { return fType; }
};

struct TCastAddress : public TAddress
{
    TAddress* fAddress;
    TType* fType;

    TCastAddress(TAddress* address, TType* type):fAddress(address), fType(type)
    {}

    virtual ~TCastAddress() {}

    virtual void generate(ostream* dst, int n)
    {
        fAddress->generate(dst, n);
        *dst << "{"; fAddress->getType()->generate(dst, n); *dst << "->"; fType->generate(dst, n); *dst << "}";
    }

    virtual void generateCPP(ostream* dst, int n)
    {
        *dst << "(*(";
        fType->generateCPP(dst, n);
        *dst << "*)&(";
        fAddress->generateCPP(dst, n);
        *dst << "))";
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
        fAddress->generate(dst, n);
        *dst << "("; fIndex->generate(dst, n); *dst << ")";
    }

    virtual void generateCPP(ostream* dst, int n)
    {
        fAddress->generateCPP(dst, n);
        if (dynamic_cast<TIndexAddress*>(fAddress) || dynamic_cast<TCastAddress*>(fAddress)) {
            *dst << ".f[";
        } else {
            *dst << "[";
        }
        fIndex->generateCPP(dst, n);
        *dst << "]";
    }

    virtual TType* getType()
    {
        return fAddress->getType();
    }
};


#endif


