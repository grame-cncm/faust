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

struct TVectorType : public TType
{
    TType* fType;
    int fSize;

    TVectorType(TType* type, int size):fType(type), fSize(size) {}

    virtual ~TVectorType() {}

	virtual void generate(ostream* dst, int n) { fType->generate(dst, n); *dst << " [" << fSize << "]";  }

    virtual int getSize() { return fSize; }

    virtual bool equal(TType* type)
    {
        TVectorType* vec_type = dynamic_cast<TVectorType*>(type);
        return vec_type && fSize == vec_type->fSize && fType->equal(vec_type->fType);
    }

};

/*
struct TCastType : public TType
{
    TType* fCasted;

    bool checkCast(TType* type1, TType* type2)
    {
        TVectorType* vec_type1;
        TVectorType* vec_type2;

        if (type1->equal(type2)) {
            return true;
        } else if (dynamic_cast<TIntType*>(type1)) {
            return dynamic_cast<TFloatType*>(type2);
        } else if (dynamic_cast<TFloatType*>(type1)) {
            return dynamic_cast<TIntType*>(type2);
        } if ((vec_type1 = dynamic_cast<TVectorType*>(type1))
                && (vec_type2 = dynamic_cast<TVectorType*>(type2))) {
            return (vec_type2->fSize <= vec_type1->fSize) && ((vec_type1->fSize % vec_type2->fSize) == 0);
        } else {
            return false;
        }
    }

    TCastType(TType* type1, TType* type2)
    {
        assert(checkCast(type1, type2));

        // Cast is possible

        TVectorType* vec_type1 = dynamic_cast<TVectorType*>(type1);
        TVectorType* vec_type2 = dynamic_cast<TVectorType*>(type2);
        if (vec_type1 && vec_type2) {
            TVectorType* tmp = new TVectorType(vec_type1->fType, vec_type2->fSize);
            fCasted = new TVectorType(tmp, vec_type1->fSize / vec_type2->fSize);
        } else {
            // Simple cast
            fCasted = type2;
        }
    }

	virtual void generate(ostream* dst, int n) { fCasted->generate(dst, n); }

    virtual int getSize() { return fCasted->getSize(); }

    virtual bool equal(TType* type)
    {
        return fCasted->equal(type);
    }
};
*/

#endif


