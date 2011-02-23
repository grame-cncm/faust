#ifndef __TValue__
#define __TValue__

#include "TType.hh"
#include "TStatement.hh"
#include "TIndex.hh"

#include <assert.h>

struct TValue : public TPrintable
{
    virtual ~TValue() {}

	virtual TType* getType() = 0;

};

struct TNullValue : public TValue
{
    TNullValue() {}

	virtual TType* getType() { assert(false); }

    virtual void generate(ostream* dst, int n) { *dst << "NullValue"; }
    virtual void generateCPP(ostream* dst, int n) { *dst << "NullValue"; }
    virtual void generateCPPNoAlias(ostream* dst, int n) { *dst << "NullValue"; }

};

struct TFloatValue : public TValue
{
    float fValue;

    TFloatValue(float value):fValue(value) {}

	virtual TType* getType() { return new TFloatType(); }

    virtual void generate(ostream* dst, int n) { *dst << fValue; }
    virtual void generateCPP(ostream* dst, int n) { *dst << fValue; }
    virtual void generateCPPNoAlias(ostream* dst, int n) { *dst << fValue; }

};

struct TIntValue : public TValue
{
    int fValue;

    TIntValue(int value):fValue(value) {}

	virtual TType* getType() { return new TIntType(); }

    virtual void generate(ostream* dst, int n) { *dst << fValue; }
    virtual void generateCPP(ostream* dst, int n) { *dst << fValue; }
    virtual void generateCPPNoAlias(ostream* dst, int n) { *dst << fValue; }

};

struct TLoadValue : public TValue
{
    TAddress* fAddress;

    TLoadValue(TAddress* address):fAddress(address) {}

	virtual TType* getType() { return fAddress->getType(); }

    virtual void generate(ostream* dst, int n) { fAddress->generate(dst, n); }
    virtual void generateCPP(ostream* dst, int n) { fAddress->generateCPP(dst, n); }
    virtual void generateCPPNoAlias(ostream* dst, int n) { fAddress->generateCPPNoAlias(dst, n); }

};

struct TPrimOpValue : public TValue
{
 	TValue*	fVal1;
	TValue*	fVal2;
    string fOp;

    TPrimOpValue(TValue* x, TValue* y, const string& op):fVal1(x), fVal2(y), fOp(op) {}

	virtual TType* getType() { return fVal1->getType(); } // Here assume a PrimOp that keeps the same type

    virtual void generate(ostream* dst, int n) { fVal1->generate(dst, n); *dst << " " << fOp << " "; fVal2->generate(dst, n);}
    virtual void generateCPP(ostream* dst, int n) { fVal1->generateCPP(dst, n); *dst << " " << fOp << " "; fVal2->generateCPP(dst, n);}
    virtual void generateCPPNoAlias(ostream* dst, int n)
    {
        // TODO : generate additional nested loops to access complex typed addresses and values
        fVal1->generateCPPNoAlias(dst, n);
        *dst << " " << fOp << " ";
        fVal2->generateCPPNoAlias(dst, n);
    }

};

#endif


