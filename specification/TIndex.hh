#ifndef __TIndex__
#define __TIndex__

#include <vector>
#include "TPrintable.hh"
#include "Text.hh"

struct TIndex : public TPrintable
{
    virtual ~TIndex() {}

    virtual void generate(ostream* dst, int n) = 0;
    virtual void generateCPP(ostream* dst, int n) = 0;
    virtual void generateCPPNoAlias(ostream* dst, int n) = 0;
};

struct TVarIndex : public TIndex
{
    string fName;

    TVarIndex(const string& name):fName(name) {}

    virtual ~TVarIndex() {}

    virtual void generate(ostream* dst, int n)
    {
        *dst << fName;
    }

    virtual void generateCPP(ostream* dst, int n)
    {
        *dst << fName;
    }

    virtual void generateCPPNoAlias(ostream* dst, int n)
    {
        *dst << fName;
    }
};

struct TIntIndex : public TIndex
{
    int fIndex;

    TIntIndex(int index):fIndex(index) {}

    virtual ~TIntIndex() {}

    virtual void generate(ostream* dst, int n)
    {
        *dst << fIndex;
    }

    virtual void generateCPP(ostream* dst, int n)
    {
        *dst << fIndex;
    }

    virtual void generateCPPNoAlias(ostream* dst, int n)
    {
        *dst << fIndex;
    }
};

struct TBinOpIndex : public TIndex
{
    TIndex*	fExp1;
	TIndex*	fExp2;
    string fOp;

    TBinOpIndex(TIndex* x, TIndex* y, const string& op) : fExp1(x), fExp2(y), fOp(op) {}

    virtual ~TBinOpIndex() {}

    virtual void generate(ostream* dst, int n)
    {
        *dst << "(";
        fExp1->generate(dst, n);
        *dst << fOp;
        fExp2->generate(dst, n);
        *dst << ")";
    }

    virtual void generateCPP(ostream* dst, int n)
    {
        *dst << "(";
        fExp1->generateCPP(dst, n);
        *dst << fOp;
        fExp2->generateCPP(dst, n);
        *dst << ")";
    }

    virtual void generateCPPNoAlias(ostream* dst, int n)
    {
        *dst << "(";
        fExp1->generateCPPNoAlias(dst, n);
        *dst << fOp;
        fExp2->generateCPPNoAlias(dst, n);
        *dst << ")";
    }
};

#endif


