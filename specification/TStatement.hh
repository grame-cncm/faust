#ifndef __TStatement__
#define __TStatement__

#include "TPrintable.hh"
#include "TType.hh"
#include "TIndex.hh"
#include "TAddress.hh"
#include <vector>

struct TValue;

struct TStatement : public TPrintable
{
    virtual ~TStatement() {}

    virtual void generate(ostream* dst, int n) = 0;
    virtual void generateCPP(ostream* dst, int n) = 0;
    virtual void generateCPPNoAlias(ostream* dst, int n) = 0;
};

struct TDeclareStatement : public TStatement
{
#ifdef ALT_VECTOR
    TVectorAddress* fVector;

    TDeclareStatement(TVectorAddress* vector):fVector(vector) {}
#else
    TNamedAddress* fVector;

    TDeclareStatement(TNamedAddress* vector):fVector(vector) {}
#endif
    virtual ~TDeclareStatement() {}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);
};

struct TDeclareTypeStatement : public TStatement
{
    TType* fType;

    TDeclareTypeStatement(TType* type):fType(type) {}
    virtual ~TDeclareTypeStatement() {}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);
};

struct TStoreStatement : public TStatement
{
    TAddress* fAddress;
    TValue* fValue;

    TStoreStatement(TAddress* address, TValue* value):fAddress(address), fValue(value){}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);

    void generateSubLoops(ostream* dst, int n, const vector<int>& dimensions, int deep);
    TValue* generateSubValues(TValue* value, const vector<int>& dim);
    TAddress* generateSubAddressLoad(TAddress* address, const vector<int>& dim);
    TAddress* generateSubAddressStore(TAddress* address, const vector<int>& dim);

};

struct TBlockStatement : public TStatement
{
    vector<TStatement*> fCode;

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);
};

struct TLoopStatement : public TStatement
{
    int fSize;
    TIndex* fIndex;
    TBlockStatement* fCode;

    TLoopStatement(int size, TIndex* index, TBlockStatement* code):fSize(size), fIndex(index), fCode(code) {}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);

};

struct TSubLoopStatement : public TLoopStatement
{
    TSubLoopStatement(int size, TIndex* index, TBlockStatement* code):TLoopStatement(size, index, code) {}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);

};

struct TIfStatement : public TStatement
{
    TIndex* fIndex;
    TBlockStatement* fCode;

    TIfStatement(TIndex* index, TBlockStatement* code):fIndex(index), fCode(code) {}

    virtual void generate(ostream* dst, int n);
    virtual void generateCPP(ostream* dst, int n);
    virtual void generateCPPNoAlias(ostream* dst, int n);

};


#endif


