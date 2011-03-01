#ifndef __TAddress__
#define __TAddress__

#include "TPrintable.hh"
#include "TType.hh"
#include "TIndex.hh"

#include <vector>

struct TAddress : public TPrintable {

    virtual ~TAddress() {}

    virtual TType* getType() = 0;

    virtual TIndex* rewriteIndex(TIndex* index) = 0;
    virtual TAddress* rewriteAddress(TIndex* index) = 0;

    virtual TAddress* getVector() = 0;
};

#ifdef ALT_VECTOR

struct TVectorAddress : public TAddress
{
    TType* fType;
    int fSize;
    string fName;

    TVectorAddress(const string& name, TType* type, int size):fName(name), fType(type), fSize(size){}

    virtual ~TVectorAddress() {}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);
    virtual TType* getType();

    virtual TIndex* rewriteIndex(TIndex* index);
    virtual TAddress* rewriteAddress(TIndex* index);

    virtual TAddress* getVector() { return this; }

};

#else

struct TVectorAddress : public TAddress
{
    TType* fType;
    string fName;

    TVectorAddress(const string& name, TType* type):fName(name), fType(type)
    {
        assert(dynamic_cast<TVectorType*>(type));
    }

    virtual ~TVectorAddress() {}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);
    virtual TType* getType();

    virtual TIndex* rewriteIndex(TIndex* index);
    virtual TAddress* rewriteAddress(TIndex* index);

    virtual TAddress* getVector() { return this; }

};

#endif

struct TCastAddress : public TAddress
{
    TAddress* fAddress;
    TType* fType;

    TCastAddress(TAddress* address, TType* type):fAddress(address), fType(type)
    {}

    virtual ~TCastAddress() {}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);
    virtual TType* getType();

    virtual TIndex* rewriteIndex(TIndex* index);
    virtual TAddress* rewriteAddress(TIndex* index);

    virtual TAddress* getVector() { return fAddress->getVector(); }

};

struct TIndexAddress : public TAddress
{
    TAddress* fAddress;
    TIndex* fIndex;

    TIndexAddress(TAddress* address, TIndex* index):fAddress(address), fIndex(index){}

    virtual ~TIndexAddress() {}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);
    virtual TType* getType();

    virtual TIndex* rewriteIndex(TIndex* index);
    virtual TAddress* rewriteAddress(TIndex* index);

    virtual TAddress* getVector() { return fAddress->getVector(); }

};


#endif


