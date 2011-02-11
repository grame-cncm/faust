#ifndef __TType__
#define __TType__

#include "TPrintable.hh"

#include <assert.h>

struct TType : public TPrintable
{
    virtual ~TType () {}

	virtual void generate(ostream* dst, int n) = 0;

    virtual int getSize()  = 0;

    virtual bool equal(TType* type) = 0;

    virtual TType* deref() = 0;

};

struct TTypable
{
  	virtual TType* getType() = 0;
};

struct TRateable
{
  	virtual int getRate() = 0;
};

struct TIntType : public TType
{
    virtual ~TIntType() {}

	virtual void generate(ostream* dst, int n) { *dst << "int"; }

    virtual int getSize() { return 0; }

    virtual bool equal(TType* type)
    {
        return dynamic_cast<TIntType*>(type);
    }

    virtual TType* deref()
    {
        cerr << "Error : derefencing int type !!" << endl;
        assert(false);
    }
};

struct TFloatType : public TType
{
    virtual ~TFloatType() {}

	virtual void generate(ostream* dst, int n) { *dst << "float"; }

    virtual int getSize() { return 0; }

    virtual bool equal(TType* type)
    {
        return dynamic_cast<TFloatType*>(type);
    }

    virtual TType* deref()
    {
        cerr << "Error : derefencing float type !!" << endl;
        assert(false);
    }
};

struct TVectorType : public TType
{
    TType* fType;
    int fSize;

    TVectorType(TType* type, int size):fType(type), fSize(size) {}

    virtual ~TVectorType() {}

	virtual void generate(ostream* dst, int n) { fType->generate(dst, n); *dst << "[" << fSize << "]";  }

    virtual int getSize() { return fSize; }

    virtual bool equal(TType* type)
    {
        TVectorType* vec_type = dynamic_cast<TVectorType*>(type);
        return vec_type && fSize == vec_type->fSize && fType->equal(vec_type->fType);
    }

    virtual TType* deref()
    {
        return fType;
    }
};

#endif


