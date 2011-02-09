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

};

struct TFloatValue : public TValue
{
    float fValue;

    TFloatValue(float value):fValue(value) {}

	virtual TType* getType() { return new TFloatType(); }

    virtual void generate(ostream* dst, int n) { *dst << fValue; }

};

struct TIntValue : public TValue
{
    int fValue;

    TIntValue(int value):fValue(value) {}

	virtual TType* getType() { return new TIntType(); }

    virtual void generate(ostream* dst, int n) { *dst << fValue; }

};

struct TVarValue : public TValue
{
    string fName;

    TVarValue(const string& name):fName(name) {}

    virtual ~TVarValue() {}

	virtual TType* getType() = 0;

    virtual void generate(ostream* dst, int n) { *dst << fName; }

};

struct TLoadValue : public TValue
{
    TAddress* fAddress;

    TLoadValue(TAddress* address):fAddress(address) {}

	virtual TType* getType() { return fAddress->getType(); }

    virtual void generate(ostream* dst, int n) { fAddress->generate(dst, n); }

};

struct TVectorValue : public TValue
{
    TValue* fValue;
    int fSize;

    TVectorValue(TValue* val, int size):fValue(val), fSize(size) {}

    virtual ~TVectorValue() {}

	virtual TType* getType() { return new TVectorType(fValue->getType(), fSize); }

    virtual void generate(ostream* dst, int n) { fValue->generate(dst, n); tab(n, *dst);; *dst << "[" << fSize << "]";}

};

struct TPrimOpValue : public TValue
{
 	TValue*	fVal1;
	TValue*	fVal2;
    string fOp;

    TPrimOpValue(TValue* x, TValue* y, const string& op):fVal1(x), fVal2(y), fOp(op) {}

	virtual TType* getType() { return fVal1->getType(); } // Here assume a PrimOp that keeps the same type

    virtual void generate(ostream* dst, int n) { fVal1->generate(dst, n); *dst << " " << fOp << " "; fVal2->generate(dst, n);}

};

#endif


