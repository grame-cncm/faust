#ifndef __TType__
#define __TType__

#include "TPrintable.hh"

struct TType : public TPrintable
{
    virtual ~TType () {}

	virtual void generate(ostream* dst, int n) = 0;

    virtual int getSize()  = 0;

    virtual bool equal(TType* type) = 0;

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
};

struct VectorType : public TType
{
    TType* fType;
    int fSize;

    VectorType(TType* type, int size):fType(type), fSize(size) {}

    virtual ~VectorType() {}

	virtual void generate(ostream* dst, int n) { fType->generate(dst, n); *dst << " [" << fSize << "]";  }

    virtual int getSize() { return fSize; }

    virtual bool equal(TType* type)
    {
        VectorType* vec_type = dynamic_cast<VectorType*>(type);
        return vec_type && fSize == vec_type->fSize && fType->equal(vec_type->fType);
    }

};

#endif


