#ifndef __TSignal__
#define __TSignal__

#include "TType.hh"
#include "TValue.hh"
#include "TStatement.hh"TBlockStatement* block, TAddress* address
#include "TAddress.hh"
#include <map>

#include <assert.h>

struct TBlockStatement;

extern int gVecSize;
extern TBlockStatement* gExternalBlock;
extern TBlockStatement* gDecBlock;

struct TSignal : public TTypable, public TRateable
{
    virtual ~TSignal () {}

	virtual void compileStatement(TBlockStatement* block, TAddress* address, TIndex* index) = 0;
    virtual TValue* compileSample(TIndex*) = 0;

};

struct TFloat : public TSignal
{
    float fValue;

    TFloat(float value):fValue(value) {}

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex*);

    virtual TType* getType() { return new TFloatType(); }
    virtual int getRate() { return 1; }

};

struct TInt : public TSignal
{
    int fValue;

    TInt(int value):fValue(value) {}

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex*);

    virtual TType* getType() { return new TIntType(); }
    virtual int getRate() { return 1; }
};

struct TInput : public TSignal
{
    int fIndex;
    int fRate;

    TInput(int index, int rate):fIndex(index), fRate(rate) {}

    virtual ~TInput() {}

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex* index);

    virtual TType* getType() { return new TFloatType(); }
    virtual int getRate() { return fRate; }
};

struct TPrimOp : public TSignal
{
	TSignal*	fExp1;
	TSignal*	fExp2;
    string fOp;

    TPrimOp(TSignal* x, TSignal* y, const string op) : fExp1(x), fExp2(y), fOp(op) {}

	virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex* Is);

    virtual TType* getType()  { return fExp1->getType(); }  // Here assume a PrimOp that keeps the same type
    virtual int getRate() { return fExp1->getRate(); }      // Here assume a PrimOp that keeps the same rate
};

struct TVectorize : public TSignal
{
    TSignal*	fExp;
    int fSize;

    TVectorize(TSignal* x, int size):fExp(x), fSize(size) { }

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex*);

    // T = type(E)
    // T[n] = type(vectorize(E))
    virtual TType* getType();

    // n * m = rate(E)
    // m = rate(vectorize(E))
    virtual int getRate() {
        //cerr << "TVectorize::getRate " << fExp->getRate() << " " << fSize << endl;
        return fExp->getRate() / fSize;
    }

};

struct TSerialize : public TSignal
{
	TSignal*	fExp;

    TSerialize(TSignal* x):fExp(x) { }

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex*);

    // T[n] = type(E)
    // T = type(serialize(E))
    virtual TType* getType()
    {
        TType* exp_type = fExp->getType();
        TVectorType* vector_type = dynamic_cast<TVectorType*>(exp_type);
        assert(vector_type);
        return vector_type->fType;
    }

    // m = rate(E)
    // n * m = rate(serialize(E))
    virtual int getRate()
    {
        TType* exp_type = fExp->getType();
        TVectorType* vector_type = dynamic_cast<TVectorType*>(exp_type);
        assert(vector_type);
        //cerr << "TSerialize::getRate " << fExp->getRate() << " " << vector_type->fSize << endl;
        return fExp->getRate() * vector_type->fSize;
    }
};

struct TConcat : public TSignal
{
	TSignal*	fExp1;
	TSignal*	fExp2;

    TConcat(TSignal* x, TSignal* y) : fExp1(x), fExp2(y) {}

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex*);

    virtual TType* getType();
    virtual int getRate()
    {
        return fExp1->getRate();
    }
};

struct TVectorAt : public TSignal
{
    TSignal*	fExp1;
	TSignal*	fExp2;

    TVectorAt(TSignal* x, TSignal* y) : fExp1(x), fExp2(y) {}

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex*);

    virtual TType* getType()
    {
        TType* type1 = fExp1->getType();
        TVectorType* vec1_type = dynamic_cast<TVectorType*>(type1);
        assert(vec1_type);
        return vec1_type->fType;
    }

    virtual int getRate()
    {
        return fExp1->getRate();
    }
};

struct TDelayLine : public TSignal
{
	TSignal* fExp;
    int fMaxDelay;

    TDelayLine(TSignal* x, int delay) : fExp(x), fMaxDelay(delay) { }

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex*);
#ifdef ALT_VECTOR
    virtual TVectorAddress* compile();
#else
    virtual TNamedAddress* compile();
#endif

    virtual TType* getType()
    {
        return fExp->getType();
    }

    virtual int getRate()
    {
        return fExp->getRate();
    }
};

struct TDelayAt : public TSignal
{
    TSignal*	fExp1;
	TSignal*	fExp2;

    TDelayAt(TSignal* x, TSignal* y) : fExp1(x), fExp2(y) {}

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex*);

    virtual TType* getType()
    {
        return fExp1->getType();
    }

    virtual int getRate()
    {
        return fExp1->getRate();
    }
};

struct TRecGroup : public TSignal
{
    string fRecGroup;
    vector<TSignal*> fCode;

    static map<string, int> gRecCompEnv;
#ifdef ALT_VECTOR
    static map<string, TVectorAddress*> gRecProjCompEnv;
#else
    static map<string, TNamedAddress*> gRecProjCompEnv;
#endif

    TRecGroup(const string& group):fRecGroup(group)
    {}

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex*);

    virtual TType* getType() { assert(false); }
    virtual int getRate() { assert(false); }

};

struct TRecProj : public TSignal
{
    TRecGroup* fRecGroup;
    int fProj;

    TRecProj(TRecGroup* group, int proj):fRecGroup(group), fProj(proj) {}

    virtual void  compileStatement(TBlockStatement* block, TAddress* address, TIndex* index);
    virtual TValue* compileSample(TIndex*);

    virtual TType* getType()
    {
        assert(fProj <= fRecGroup->fCode.size());
        return fRecGroup->fCode[fProj]->getType();
    }
    virtual int getRate()
    {
        assert(fProj <= fRecGroup->fCode.size());
        return fRecGroup->fCode[fProj]->getRate();
    }

};

#endif


