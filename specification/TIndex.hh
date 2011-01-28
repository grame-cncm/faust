#ifndef __TIndex__
#define __TIndex__

#include <vector>
#include "TPrintable.hh"
#include "Text.hh"

struct TIndex : public TPrintable
{
    virtual ~TIndex() {}

    virtual void generate(ostream* dst, int n) = 0;
};

struct TVarIndex : public TIndex
{
    string fName;

    TVarIndex(const string& name):fName(name) {}

    virtual ~TVarIndex() {}

    virtual void generate(ostream* dst, int n) { *dst << "(" << fName << ")"; }
};

struct TIntIndex : public TIndex
{
    int fIndex;

    TIntIndex(int index):fIndex(index) {}

    virtual ~TIntIndex() {}

    virtual void generate(ostream* dst, int n) { *dst << "(" << fIndex << ")"; }
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
};

struct TListIndex
{
    vector<TIndex*> fIndexList;

    TListIndex() {}

    virtual ~TListIndex() {}

    virtual void generate(ostream* dst, int n)
    {
        vector<TIndex*>::const_iterator it;
        *dst << "(";
        for (it = fIndexList.begin(); it != fIndexList.end(); it++) {
            (*it)->generate(dst, n+1);
        }
        *dst << ")";
    }

    TListIndex* copy()
    {
        TListIndex* copy = new TListIndex();
        vector<TIndex*>::const_iterator it;
        for (it = fIndexList.begin(); it != fIndexList.end(); it++) {
            copy->fIndexList.push_back(*it);
        }
        return copy;
    }

    TIndex* getStreamIndex()
    {
        return (fIndexList.size() > 0) ? fIndexList[fIndexList.size() - 1] : 0;
    }

    void setStreamIndex(TIndex* index)
    {
       fIndexList[fIndexList.size() - 1] = index;
    }

};

#endif


