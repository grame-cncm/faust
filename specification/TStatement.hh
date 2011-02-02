#ifndef __TStatement__
#define __TStatement__

#include "TPrintable.hh"
#include "TType.hh"
#include "TIndex.hh"
#include <vector>

struct TValue;

struct TStatement : public TPrintable
{
    virtual ~TStatement() {}

    virtual void generate(ostream* dst, int n) = 0;
};

struct TDeclareStatement : public TStatement
{
    string fName;
    TType* fType;

    TDeclareStatement(const string& name, TType* type):fName(name), fType(type) {}
    virtual ~TDeclareStatement() {}

    virtual void generate(ostream* dst, int n);
};

struct TStoreStatement : public TStatement
{
    TDeclareStatement* fAddress;
    TListIndex* fIndex;
    TValue* fValue;

    TStoreStatement(TDeclareStatement* address, TListIndex* Os, TValue* value):fAddress(address), fIndex(Os), fValue(value){}

    virtual void generate(ostream* dst, int n);
};

struct TBlockStatement : public TStatement
{
    vector<TStatement*> fCode;

    virtual void generate(ostream* dst, int n);
};

struct TLoopStatement : public TStatement
{
    int fSize;
    TIndex* fIndex;
    TBlockStatement* fCode;

    TLoopStatement(int size, TIndex* index, TBlockStatement* code):fSize(size), fIndex(index), fCode(code) {}

    virtual void generate(ostream* dst, int n);

};

struct TSubLoopStatement : public TLoopStatement
{
    TSubLoopStatement(int size, TIndex* index, TBlockStatement* code):TLoopStatement(size, index, code) {}

    virtual void generate(ostream* dst, int n);

};

struct TIfStatement : public TStatement
{
    TListIndex* fIndex;
    TBlockStatement* fCode;

    TIfStatement(TListIndex* index, TBlockStatement* code):fIndex(index), fCode(code) {}

    virtual void generate(ostream* dst, int n);

};


#endif


