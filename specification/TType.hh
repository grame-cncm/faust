#ifndef __TType__
#define __TType__

#include "TPrintable.hh"
#include "Text.hh"

#include <assert.h>

string getFreshID(const string& prefix);

struct TType : public TPrintable
{
    virtual ~TType () {}

	virtual void generate(ostream* dst, int n) = 0;
    virtual void generateCPP(ostream* dst, int n) = 0;
    virtual void generateDef(ostream* dst, int n) = 0;

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
    virtual void generateCPP(ostream* dst, int n) { *dst << "int"; }
    virtual void generateDef(ostream* dst, int n) {}

    virtual int getSize() { return 0; }

    virtual bool equal(TType* type)
    {
        return dynamic_cast<TIntType*>(type);
    }

    virtual TType* deref()
    {
        cerr << "Error : dereferencing int type !!" << endl;
        assert(false);
    }
};

struct TFloatType : public TType
{
    virtual ~TFloatType() {}

	virtual void generate(ostream* dst, int n) { *dst << "float"; }
    virtual void generateCPP(ostream* dst, int n) { *dst << "float"; }
    virtual void generateDef(ostream* dst, int n) {}

    virtual int getSize() { return 0; }

    virtual bool equal(TType* type)
    {
        return dynamic_cast<TFloatType*>(type);
    }

    virtual TType* deref()
    {
        cerr << "Error : dereferencing float type !!" << endl;
        assert(false);
    }
};

struct TVectorType : public TType
{
    TType* fType;
    int fSize;
    string fDecName;
    bool fGenerated;

    TVectorType(TType* type, int size):fType(type), fSize(size)
    {
        fDecName = getFreshID("VecType");
        fGenerated = false;
    }

    virtual ~TVectorType() {}

	virtual void generate(ostream* dst, int n) { fType->generate(dst, n); *dst << "[" << fSize << "]";  }
    virtual void generateCPP(ostream* dst, int n)
    {
        *dst  << fDecName;
    }

    void generatePoly(ostream* dst, int n, const string& op)
    {
        tab(n+1, *dst); *dst << fDecName << " operator" << op << "(const " << fDecName << "& val)" << " {" << endl;
            tab(n+2, *dst); *dst << "for (int i = 0; i < " << fSize << "; i++) {" << endl;
                tab(n+3, *dst); *dst << "f[i] " << op << "= val.f[i];" << endl;
            tab(n+2, *dst); *dst << "}" << endl;
            tab(n+2, *dst); *dst << "return *this;" << endl;
        tab(n+1, *dst); *dst << "}" << endl;
    }

    void generatePolyScalar(ostream* dst, int n, const string& op)
    {
        tab(n+1, *dst); *dst << fDecName << " operator" << op << "(float val)" << " {" << endl;
            tab(n+2, *dst); *dst << "for (int i = 0; i < " << fSize << "; i++) {" << endl;
                tab(n+3, *dst); *dst << "f[i] " << op << "= val;" << endl;
            tab(n+2, *dst); *dst << "}" << endl;
            tab(n+2, *dst); *dst << "return *this;" << endl;
        tab(n+1, *dst); *dst << "}" << endl;
    }

    virtual void generateDef(ostream* dst, int n)
    {
        if (!fGenerated) {
            fType->generateDef(dst, n+1);
            tab(n, *dst);
            *dst << "struct " << fDecName;
            *dst << " {" << endl;
            tab(n+1, *dst);
            fType->generateCPP(dst, n+1);
            *dst << " f" << "[" << fSize << "];" << endl;

            generatePoly(dst, n, "+");
            generatePoly(dst, n, "-");
            generatePoly(dst, n, "*");
            generatePoly(dst, n, "/");

            generatePolyScalar(dst, n, "+");
            generatePolyScalar(dst, n, "-");
            generatePolyScalar(dst, n, "*");
            generatePolyScalar(dst, n, "/");

            tab(n, *dst); *dst << "};";
            fGenerated = true;
        }
    }

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


