#ifndef __TAddress__
#define __TAddress__

#include "TPrintable.hh"
#include "TType.hh"
#include "TIndex.hh"

#include <list>

struct TAddress : public TPrintable {

    virtual ~TAddress() {}

    virtual TType* getType() = 0;
    virtual TAddress* rewriteAddress(list<TAddress*>& address_list) = 0;
    virtual TAddress* linearizeAddress(list<TAddress*>& address_list) = 0;
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
    virtual TAddress* rewriteAddress(list<TAddress*>& address_list);
    virtual TAddress* linearizeAddress(list<TAddress*>& address_list);

};

#else

struct TNamedAddress : public TAddress
{
    TType* fType;
    string fName;

    TNamedAddress(const string& name, TType* type):fName(name), fType(type)
    {
        assert(dynamic_cast<TVectorType*>(type));
    }

    virtual ~TNamedAddress() {}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);
    virtual TType* getType();
    virtual TAddress* rewriteAddress(list<TAddress*>& address_list);
    virtual TAddress* linearizeAddress(list<TAddress*>& address_list);

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
    virtual TAddress* rewriteAddress(list<TAddress*>& address_list);
    virtual TAddress* linearizeAddress(list<TAddress*>& address_list);

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
    virtual TAddress* rewriteAddress(list<TAddress*>& address_list);
    virtual TAddress* linearizeAddress(list<TAddress*>& address_list);

};

#endif


