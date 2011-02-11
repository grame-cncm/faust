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


struct TCastType : public TType
{
    TType* fOld;
    TType* fNew;

    // TODO
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

    TCastType(TType* type1, TType* type2):fOld(type1), fNew(type2)
    {
        bool res = checkCast(type1, type2);
        //printf("checkCast %d\n", res);
    }

	virtual void generate(ostream* dst, int n) { *dst << "{"; fOld->generate(dst, n); *dst << "->"; fNew->generate(dst, n); *dst << "}"; }

    virtual int getSize() { return fNew->getSize(); }

    virtual bool equal(TType* type)
    {
        return fNew->equal(type);
    }

    virtual TType* deref()
    {
        return fNew->deref();
    }
};


#endif


