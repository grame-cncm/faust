/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2022 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifdef WIN32
#pragma warning(disable : 4996 4146 4244)
#endif

#include <string>

#include "faust/export.h"
#include "signals.hh"
#include "dsp_factory.hh"
#include "global.hh"
#include "labels.hh"
#include "normalform.hh"
#include "instructions.hh"
#include "ppbox.hh"
#include "xtended.hh"
#include "propagate.hh"
#include "sigtyperules.hh"

using namespace std;

// Implemented in libcode.cpp
LIBFAUST_API Tree DSPToBoxes(const string& name_app,
                             const string& dsp_content,
                             int argc, const char* argv[],
                             int* inputs, int* outputs,
                             string& error_msg);

// ===============
// Signal C++ API
// ===============

// Global context, to be used in C and C++ API

extern "C" LIBFAUST_API void createLibContext()
{
    gGlobal = nullptr;
    global::allocate();
}

extern "C" LIBFAUST_API void destroyLibContext()
{
    global::destroy();
}

// MUST match definition in libfaust-signal.h
#define low  std::numeric_limits<double>::lowest()
#define high std::numeric_limits<double>::max()

struct Interval {
    double fLo{low};  //< minimal value
    double fHi{high}; //< maximal value
    int    fLSB{-24}; //< lsb in bits
    
    Interval(double lo, double hi, int lsb):fLo(lo), fHi(hi), fLSB(lsb)
    {}
    Interval(int lsb):fLSB(lsb)
    {}
};

LIBFAUST_API Interval getSigInterval(Tree sig)
{
    interval it = getSigType(sig)->getInterval();
    return Interval(it.lo(), it.hi(), it.lsb());
}

LIBFAUST_API void setSigInterval(Tree sig, Interval& inter)
{
    Type ty = getSigType(sig);
    interval it1 = ty->getInterval();
    // If the inter argument has low/high range (the defaults), then it1 low/high values are kept,
    // otherwise use the given ones
    interval it2 ((inter.fLo != low) ? inter.fLo : it1.lo(),
                 (inter.fHi != high) ? inter.fHi : it1.hi(),
                 inter.fLSB);
    ty->setInterval(it2);
    setSigType(sig, ty);
}

LIBFAUST_API const char* xtendedName(Tree tree)
{
    void* userData = getUserData(tree);
    faustassert(userData != nullptr);
    return ((xtended*)userData)->name();
}

LIBFAUST_API unsigned int xtendedArity(Tree tree)
{
    void* userData = getUserData(tree);
    faustassert(userData != nullptr);
    return ((xtended*)userData)->arity();
}

LIBFAUST_API string createSourceFromSignals(const string& name_app, tvec signals,
                                         const string& lang,
                                         int argc, const char* argv[],
                                         string& error_msg)
{
    int         argc1 = 0;
    const char* argv1[64];
    argv1[argc1++] = "faust";
    argv1[argc1++] = "-lang";
    argv1[argc1++] = lang.c_str();
    argv1[argc1++] = "-o";
    argv1[argc1++] = "string";
    
    // Copy arguments
    for (int i = 0; i < argc; i++) {
        argv1[argc1++] = argv[i];
    }
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    dsp_factory_base* factory = createFactory(name_app, signals, argc1, argv1, error_msg);
    if (factory) {
        // Print the textual class
        stringstream str;
        factory->write(&str);
        delete factory;
        return str.str();
    } else {
        // the caller of this function should check that error_msg is blank.
        return "";
    }
}

// Foreign

LIBFAUST_API Tree sigFFun(Tree ff, tvec largs)
{
    return sigFFun(ff, listConvert(largs));
}

enum SType { kSInt, kSReal };

LIBFAUST_API Tree sigFConst(SType type, const string& name, const string& file)
{
    return sigFConst(tree(type), tree(name), tree(file));
}

LIBFAUST_API Tree sigFVar(SType type, const string& name, const string& file)
{
    return sigFVar(tree(type), tree(name), tree(file));
}

// User Interface

LIBFAUST_API Tree sigButton(const string& label)
{
    return sigButton(normalizePath(cons(tree(label), gGlobal->nil)));
}

LIBFAUST_API Tree sigCheckbox(const string& label)
{
    return sigCheckbox(normalizePath(cons(tree(label), gGlobal->nil)));
}

LIBFAUST_API Tree sigVSlider(const string& label, Tree cur, Tree min, Tree max, Tree step)
{
    return sigVSlider(normalizePath(cons(tree(label), gGlobal->nil)), cur, min, max, step);
}

LIBFAUST_API Tree sigHSlider(const string& label, Tree cur, Tree min, Tree max, Tree step)
{
    return sigHSlider(normalizePath(cons(tree(label), gGlobal->nil)), cur, min, max, step);
}

LIBFAUST_API Tree sigNumEntry(const string& label, Tree cur, Tree min, Tree max, Tree step)
{
    return sigNumEntry(normalizePath(cons(tree(label), gGlobal->nil)), cur, min, max, step);
}

LIBFAUST_API Tree sigVBargraph(const string& label, Tree min, Tree max, Tree x)
{
    return sigVBargraph(normalizePath(cons(tree(label), gGlobal->nil)), min, max, x);
}

LIBFAUST_API Tree sigHBargraph(const string& label, Tree min, Tree max, Tree x)
{
    return sigHBargraph(normalizePath(cons(tree(label), gGlobal->nil)), min, max, x);
}

LIBFAUST_API Tree sigSoundfile(const string& label)
{
    return sigSoundfile(normalizePath(cons(tree(label), gGlobal->nil)));
}

// Recursions

LIBFAUST_API Tree sigSelf()
{
    return sigDelay1(sigProj(0, ref(1)));
}

LIBFAUST_API Tree sigRecursion(Tree s)
{
    return sigDelay0(sigProj(0, rec(cons(s, gGlobal->nil))));
}

// Version for a N x M block
LIBFAUST_API Tree sigSelfN(int i)
{
    return sigDelay1(sigProj(i, ref(1)));
}

LIBFAUST_API tvec sigRecursionN(const tvec& ins)
{
    Tree out = rec(listConvert(ins));
    siglist outs(ins.size());
    // projection number
    int p = 0;
    for (const auto& exp : ins) {
        if (exp->aperture() > 0) {
            // it is a regular recursive expression branch
            outs[p] = sigDelay0(sigProj(p, out));
        } else {
            // this expression is a closed term,
            // it doesn't need to be inside this recursion group.
            outs[p] = exp;
        }
        p++;
    }
    return outs;
}

// =============
// Signal C API
// =============

#ifdef __cplusplus
extern "C" {
#endif
    
static Tree* list2array(tvec list)
{
    if (list.size() > 0) {
        Tree* res = (Tree*)malloc(sizeof(Tree) * (list.size() + 1));
        size_t i;
        for (i = 0; i < list.size(); i++) res[i] = list[i];
        res[i] = nullptr;
        return res;
    } else {
        return nullptr;
    }
}

LIBFAUST_API bool CisNil(Tree s)
{
    return isNil(s);
}

LIBFAUST_API const char* Ctree2str(Tree s)
{
    return tree2str(s);
}

LIBFAUST_API int Ctree2int(Tree s)
{
    return tree2int(s);
}

LIBFAUST_API void* CgetUserData(Tree s)
{
    return getUserData(s);
}

LIBFAUST_API Tree CsigInt(int n)
{
    return sigInt(n);
}

LIBFAUST_API Tree CsigReal(double n)
{
    return sigReal(n);
}

LIBFAUST_API Tree CsigInput(int idx)
{
    return sigInput(idx);
}

LIBFAUST_API Tree CsigDelay(Tree t0, Tree del)
{
    return sigDelay(t0, del);
}
    
LIBFAUST_API Tree CsigDelay1(Tree t0)
{
    return sigDelay1(t0);
}

LIBFAUST_API Tree CsigIntCast(Tree s)
{
    return sigIntCast(s);
}

LIBFAUST_API Tree CsigFloatCast(Tree s)
{
    return sigFloatCast(s);
}

LIBFAUST_API Tree CsigReadOnlyTable(Tree n, Tree init, Tree ridx)
{
    return sigReadOnlyTable(n, init, ridx);
}

LIBFAUST_API Tree CsigWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx)
{
    return sigWriteReadTable(n, init, widx, wsig, ridx);
}

LIBFAUST_API Tree CsigWaveform(Tree* wf_aux)
{
    tvec wf;
    int  i = 0;
    while (wf_aux[i]) {
        wf.push_back(wf_aux[i]);
        i++;
    }
    return sigWaveform(wf);
}

LIBFAUST_API Tree CsigSoundfile(const char* label)
{
    return sigSoundfile(label);
}

LIBFAUST_API Tree CsigSoundfileLength(Tree sf, Tree part)
{
    return sigSoundfileLength(sf, part);
}

LIBFAUST_API Tree CsigSoundfileRate(Tree sf, Tree part)
{
    return sigSoundfileRate(sf, part);
}

LIBFAUST_API Tree CsigSoundfileBuffer(Tree sf, Tree chan, Tree part, Tree ridx)
{
    return sigSoundfileBuffer(sf, chan, part, ridx);
}

LIBFAUST_API Tree CsigSelect2(Tree selector, Tree s1, Tree s2)
{
    return sigSelect2(selector, s1, s2);
}

LIBFAUST_API Tree CsigSelect3(Tree selector, Tree s1, Tree s2, Tree s3)
{
    return sigSelect3(selector, s1, s2, s3);
}

LIBFAUST_API Tree CsigFConst(SType type, const char* name, const char* file)
{
    return sigFConst(type, name, file);
}

LIBFAUST_API Tree CsigFVar(SType type, const char* name, const char* file)
{
    return sigFVar(type, name, file);
}

LIBFAUST_API Tree CsigBinOp(SOperator op, Tree x, Tree y)
{
    return sigBinOp(op, x, y);
}

LIBFAUST_API Tree CsigAdd(Tree x, Tree y)
{
    return sigAdd(x, y);
}
LIBFAUST_API Tree CsigSub(Tree x, Tree y)
{
    return sigSub(x, y);
}
LIBFAUST_API Tree CsigMul(Tree x, Tree y)
{
    return sigMul(x, y);
}
LIBFAUST_API Tree CsigDiv(Tree x, Tree y)
{
    return sigDiv(x, y);
}
LIBFAUST_API Tree CsigRem(Tree x, Tree y)
{
    return sigRem(x, y);
}

LIBFAUST_API Tree CsigLeftShift(Tree x, Tree y)
{
    return sigLeftShift(x, y);
}
LIBFAUST_API Tree CsigLRightShift(Tree x, Tree y)
{
    return sigLRightShift(x, y);
}
LIBFAUST_API Tree CsigARightShift(Tree x, Tree y)
{
    return sigARightShift(x, y);
}

LIBFAUST_API Tree CsigGT(Tree x, Tree y)
{
    return sigGT(x, y);
}
LIBFAUST_API Tree CsigLT(Tree x, Tree y)
{
    return sigLT(x, y);
}
LIBFAUST_API Tree CsigGE(Tree x, Tree y)
{
    return sigGE(x, y);
}
LIBFAUST_API Tree CsigLE(Tree x, Tree y)
{
    return sigLE(x, y);
}
LIBFAUST_API Tree CsigEQ(Tree x, Tree y)
{
    return sigEQ(x, y);
}
LIBFAUST_API Tree CsigNE(Tree x, Tree y)
{
    return sigNE(x, y);
}

LIBFAUST_API Tree CsigAND(Tree x, Tree y)
{
    return sigAND(x, y);
}
LIBFAUST_API Tree CsigOR(Tree x, Tree y)
{
    return sigOR(x, y);
}
LIBFAUST_API Tree CsigXOR(Tree x, Tree y)
{
    return sigXOR(x, y);
}

LIBFAUST_API Tree CsigAbs(Tree x)
{
    return sigAbs(x);
}
LIBFAUST_API Tree CsigAcos(Tree x)
{
    return sigAcos(x);
}
LIBFAUST_API Tree CsigTan(Tree x)
{
    return sigTan(x);
}
LIBFAUST_API Tree CsigSqrt(Tree x)
{
    return sigSqrt(x);
}
LIBFAUST_API Tree CsigSin(Tree x)
{
    return sigSin(x);
}
LIBFAUST_API Tree CsigRint(Tree x)
{
    return sigRint(x);
}
LIBFAUST_API Tree CsigRemainder(Tree x, Tree y)
{
    return sigRemainder(x, y);
}
LIBFAUST_API Tree CsigPow(Tree x, Tree y)
{
    return sigPow(x, y);
}
LIBFAUST_API Tree CsigMin(Tree x, Tree y)
{
    return sigMin(x, y);
}
LIBFAUST_API Tree CsigMax(Tree x, Tree y)
{
    return sigMax(x, y);
}
LIBFAUST_API Tree CsigLog(Tree x)
{
    return sigLog(x);
}
LIBFAUST_API Tree CsigLog10(Tree x)
{
    return sigLog10(x);
}
LIBFAUST_API Tree CsigFmod(Tree x, Tree y)
{
    return sigFmod(x, y);
}
LIBFAUST_API Tree CsigFloor(Tree x)
{
    return sigFloor(x);
}
LIBFAUST_API Tree CsigExp(Tree x)
{
    return sigExp(x);
}
LIBFAUST_API Tree CsigExp10(Tree x)
{
    return sigExp10(x);
}
LIBFAUST_API Tree CsigCos(Tree x)
{
    return sigCos(x);
}
LIBFAUST_API Tree CsigCeil(Tree x)
{
    return sigCeil(x);
}
LIBFAUST_API Tree CsigAtan(Tree x)
{
    return sigAtan(x);
}
LIBFAUST_API Tree CsigAtan2(Tree x, Tree y)
{
    return sigAtan2(x, y);
}
LIBFAUST_API Tree CsigAsin(Tree x)
{
    return sigAsin(x);
}

LIBFAUST_API Tree CsigSelf()
{
    return sigSelf();
}

LIBFAUST_API Tree CsigRecursion(Tree s1)
{
    return sigRecursion(s1);
}

LIBFAUST_API Tree CsigSelfN(int i)
{
    return sigSelfN(i);
}

LIBFAUST_API Signal* CsigRecursionN(Signal* ins_aux)
{
    tvec ins;
    int  i = 0;
    while (ins[i]) {
        ins.push_back(ins_aux[i]);
        i++;
    }
    tvec outs = sigRecursionN(ins);
    return list2array(outs);
}

LIBFAUST_API Tree CsigButton(const char* label)
{
    return sigButton(label);
}

LIBFAUST_API Tree CsigCheckbox(const char* label)
{
    return sigCheckbox(label);
}

LIBFAUST_API Tree CsigVSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return sigVSlider(label, init, min, max, step);
}

LIBFAUST_API Tree CsigHSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return sigHSlider(label, init, min, max, step);
}

LIBFAUST_API Tree CsigNumEntry(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return sigNumEntry(label, init, min, max, step);
}

LIBFAUST_API Tree CsigVBargraph(const char* label, Tree min, Tree max, Tree x)
{
    return sigVBargraph(label, min, max, x);
}

LIBFAUST_API Tree CsigHBargraph(const char* label, Tree min, Tree max, Tree x)
{
    return sigHBargraph(label, min, max, x);
}

LIBFAUST_API Tree CsigAttach(Tree x, Tree y)
{
    return sigAttach(y, y);
}

// Signal test API
LIBFAUST_API bool CisSigInt(Tree t, int* i)
{
    return isSigInt(t, i);
}
LIBFAUST_API bool CisSigReal(Tree t, double* r)
{
    return isSigReal(t, r);
}
LIBFAUST_API bool CisSigInput(Tree t, int* i)
{
    return isSigInput(t, i);
}
LIBFAUST_API bool CisSigOutput(Tree t, int* i, Tree* t0_aux)
{
    Tree t0;
    if (isSigOutput(t, i, t0)) {
        *t0_aux = t0;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigDelay1(Tree t, Tree* t0_aux)
{
    Tree t0;
    if (isSigDelay1(t, t0)) {
        *t0_aux = t0;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigDelay(Tree t, Tree* t0_aux, Tree* t1_aux)
{
    Tree t0, t1;
    if (isSigDelay(t, t0, t1)) {
        *t0_aux = t0;
        *t1_aux = t1;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigPrefix(Tree t, Tree* t0_aux, Tree* t1_aux)
{
    Tree t0, t1;
    if (isSigPrefix(t, t0, t1)) {
        *t0_aux = t0;
        *t1_aux = t1;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigRDTbl(Tree t, Tree* tbl_aux, Tree* ri_aux)
{
    Tree tbl, ri;
    if (isSigRDTbl(t, tbl, ri)) {
        *tbl_aux = tbl;
        *ri_aux = ri;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigWRTbl(Tree t, Tree* size_aux, Tree* gen_aux, Tree* wi_aux, Tree* ws_aux)
{
    Tree size, gen, wi, ws;
    if (isSigWRTbl(t, size, gen, wi, ws)) {
        *size_aux = size;
        *gen_aux = gen;
        *wi_aux = wi;
        *ws_aux = ws;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigGen(Tree t, Tree* x_aux)
{
    Tree x;
    if (isSigGen(t, x)) {
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigDocConstantTbl(Tree t, Tree* n_aux, Tree* sig_aux)
{
    Tree n, sig;
    if (isSigDocConstantTbl(t, n, sig)) {
        *n_aux   = n;
        *sig_aux = sig;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigDocWriteTbl(Tree t, Tree* n_aux, Tree* sig_aux, Tree* widx_aux, Tree* wsig_aux)
{
    Tree n, sig, widx, wsig;
    if (isSigDocWriteTbl(t, n, sig, widx, wsig)) {
        *n_aux    = n;
        *sig_aux  = sig;
        *widx_aux = widx;
        *wsig_aux = wsig;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigDocAccessTbl(Tree t, Tree* tbl_aux, Tree* ridx_aux)
{
    Tree tbl, ridx;
    if (isSigDocAccessTbl(t, tbl, ridx)) {
        *tbl_aux  = tbl;
        *ridx_aux = ridx;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigSelect2(Tree t, Tree* selector_aux, Tree* s1_aux, Tree* s2_aux)
{
    Tree selector, s1, s2;
    if (isSigSelect2(t, selector, s1, s2)) {
        *selector_aux = selector;
        *s1_aux       = s1;
        *s2_aux       = s2;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigAssertBounds(Tree t, Tree* s1_aux, Tree* s2_aux, Tree* s3_aux)
{
    Tree s1, s2, s3;
    if (isSigAssertBounds(t, s1, s2, s3)) {
        *s1_aux = s1;
        *s2_aux = s2;
        *s2_aux = s2;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigHighest(Tree t, Tree* s_aux)
{
    Tree s;
    if (isSigHighest(t, s)) {
        *s_aux = s;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigLowest(Tree t, Tree* s_aux)
{
    Tree s;
    if (isSigLowest(t, s)) {
        *s_aux = s;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigBinOp(Tree s, int* op, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isSigBinOp(s, op, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigFFun(Tree s, Tree* ff_aux, Tree* largs_aux)
{
    Tree ff, largs;
    if (isSigFFun(s, ff, largs)) {
        *ff_aux    = ff;
        *largs_aux = largs;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigFConst(Tree s, Tree* type_aux, Tree* name_aux, Tree* file_aux)
{
    Tree type, name, file;
    if (isSigFConst(s, type, name, file)) {
        *type_aux = type;
        *name_aux = name;
        *file_aux = file;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigFVar(Tree s, Tree* type_aux, Tree* name_aux, Tree* file_aux)
{
    Tree type, name, file;
    if (isSigFVar(s, type, name, file)) {
        *type_aux = type;
        *name_aux = name;
        *file_aux = file;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisProj(Tree s, int* i, Tree* rgroup_aux)
{
    Tree rgroup;
    if (isProj(s, i, rgroup)) {
        *rgroup_aux = rgroup;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisRec(Tree s, Tree* var_aux, Tree* body_aux)
{
    Tree var, body;
    if (isRec(s, var, body)) {
        *var_aux  = var;
        *body_aux = body;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigIntCast(Tree s, Tree* x_aux)
{
    Tree x;
    if (isSigIntCast(s, x)) {
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigFloatCast(Tree s, Tree* x_aux)
{
    Tree x;
    if (isSigFloatCast(s, x)) {
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigButton(Tree s, Tree* lbl_aux)
{
    Tree lbl;
    if (isSigButton(s, lbl)) {
        *lbl_aux = lbl;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigCheckbox(Tree s, Tree* lbl_aux)
{
    Tree lbl;
    if (isSigCheckbox(s, lbl)) {
        *lbl_aux = lbl;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigWaveform(Tree s)
{
    return isSigWaveform(s);
}

LIBFAUST_API bool CisSigHSlider(Tree s, Tree* lbl_aux, Tree* init_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, init, min, max, step;
    if (isSigHSlider(s, lbl, init, min, max, step)) {
        *lbl_aux  = lbl;
        *init_aux = init;
        *min_aux  = min;
        *max_aux  = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigVSlider(Tree s, Tree* lbl_aux, Tree* init_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, init, min, max, step;
    if (isSigVSlider(s, lbl, init, min, max, step)) {
        *lbl_aux  = lbl;
        *init_aux = init;
        *min_aux  = min;
        *max_aux  = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigNumEntry(Tree s, Tree* lbl_aux, Tree* init_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, init, min, max, step;
    if (isSigNumEntry(s, lbl, init, min, max, step)) {
        *lbl_aux  = lbl;
        *init_aux = init;
        *min_aux  = min;
        *max_aux  = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigHBargraph(Tree s, Tree* lbl_aux, Tree* min_aux, Tree* max_aux, Tree* x_aux)
{
    Tree lbl, min, max, x0;
    if (isSigHBargraph(s, lbl, min, max, x0)) {
        *lbl_aux = lbl;
        *min_aux = min;
        *max_aux = max;
        *x_aux   = x0;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigVBargraph(Tree s, Tree* lbl_aux, Tree* min_aux, Tree* max_aux, Tree* x_aux)
{
    Tree lbl, min, max, x0;
    if (isSigVBargraph(s, lbl, min, max, x0)) {
        *lbl_aux = lbl;
        *min_aux = min;
        *max_aux = max;
        *x_aux   = x0;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigAttach(Tree s, Tree* s0_aux, Tree* s1_aux)
{
    Tree s0, s1;
    if (isSigAttach(s, s0, s1)) {
        *s0_aux = s0;
        *s1_aux = s1;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigEnable(Tree s, Tree* s0_aux, Tree* s1_aux)
{
    Tree s0, s1;
    if (isSigEnable(s, s0, s1)) {
        *s0_aux = s0;
        *s1_aux = s1;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigControl(Tree s, Tree* s0_aux, Tree* s1_aux)
{
    Tree s0, s1;
    if (isSigControl(s, s0, s1)) {
        *s0_aux = s0;
        *s1_aux = s1;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigSoundfile(Tree s, Tree* label_aux)
{
    Tree label;
    if (isSigSoundfile(s, label)) {
        *label_aux = label;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigSoundfileLength(Tree s, Tree* sf_aux, Tree* part_aux)
{
    Tree sf, part;
    if (isSigSoundfileLength(s, sf, part)) {
        *sf_aux   = sf;
        *part_aux = part;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigSoundfileRate(Tree s, Tree* sf_aux, Tree* part_aux)
{
    Tree sf, part;
    if (isSigSoundfileRate(s, sf, part)) {
        *sf_aux   = sf;
        *part_aux = part;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigSoundfileBuffer(Tree s, Tree* sf_aux, Tree* chan_aux, Tree* part_aux, Tree* ridx_aux)
{
    Tree sf, chan, part, ridx;
    if (isSigSoundfileBuffer(s, sf, chan, part, ridx)) {
        *sf_aux   = sf;
        *chan_aux = chan;
        *part_aux = part;
        *ridx_aux = ridx;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API Tree CsimplifyToNormalForm(Tree s)
{
    return simplifyToNormalForm(s);
}

LIBFAUST_API Tree* CsimplifyToNormalForm2(Tree* siglist)
{
    tvec inputs;
    int  in = 0;
    while (siglist[in]) {
        inputs.push_back(siglist[in]);
        in++;
    }
    tvec outputs = simplifyToNormalForm2(inputs);
    return list2array(outputs);
}
    
LIBFAUST_API char* CcreateSourceFromSignals(const char* name_app, Signal* osigs,
                                        const char* lang,
                                        int argc, const char* argv[],
                                        char* error_msg)
{
    string error_msg_aux;
    tvec inputs;
    int  in = 0;
    while (osigs[in]) {
        inputs.push_back(osigs[in]);
        in++;
    }
    string source = createSourceFromSignals(name_app, inputs, lang, argc, argv, error_msg_aux);
    if (source.size() > 0) {
        return strdup(source.c_str());
    } else {
        strncpy(error_msg, error_msg_aux.c_str(), 4096);
        return nullptr;
    }
}
    
#ifdef __cplusplus
}
#endif

// ============
// Box C++ API
// ============

static void* boxesToSignalsAux2(void* arg)
{
    CallContext* context = static_cast<CallContext*>(arg);
    try {
        Tree outputs = boxPropagateSig(gGlobal->nil, context->fTree, makeSigInputList(context->fNumInputs));
        context->fTree = simplifyToNormalForm(outputs);
        return nullptr;
    } catch (faustexception& e) {
        context->fTree = nullptr;
        gGlobal->gErrorMessage = e.Message();
        return nullptr;
    }
}

// Can generate faustexception, used in createDSPFactoryFromBoxes and createInterpreterDSPFactoryFromBoxes
tvec boxesToSignalsAux(Tree box)
{
    // Cleanup all variables and reset gGlobal state
    DeclareVarInst::cleanup();
    gGlobal->reset();
    
    int numInputs, numOutputs;
    if (!getBoxType(box, &numInputs, &numOutputs)) {
        stringstream error;
        error << "ERROR during the evaluation of process : " << boxpp(box) << endl;
        throw faustexception(error.str());
    }
    
    // Threaded call
    CallContext context;
    context.fTree = box;
    context.fNumInputs = numInputs;
    callFun(boxesToSignalsAux2, &context);
    if (context.fTree) {
        return treeConvert(context.fTree);
    } else {
        throw faustexception(gGlobal->gErrorMessage);
    }
}

LIBFAUST_API tvec boxesToSignals(Tree box, string& error_msg)
{
    try {
        return boxesToSignalsAux(box);
    } catch (faustexception& e) {
        error_msg = e.Message();
        return {};
    }
}

LIBFAUST_API string createSourceFromBoxes(const string& name_app,
                                        Tree box,
                                        const string& lang,
                                        int argc, const char* argv[],
                                        string& error_msg)
{
    try {
        tvec signals = boxesToSignalsAux(box);
        return createSourceFromSignals(name_app, signals, lang, argc, argv, error_msg);
    } catch (faustexception& e) {
        return e.Message();
    }
}

LIBFAUST_API Tree boxDelay()
{
    return boxPrim2(sigDelay);
}

LIBFAUST_API Tree boxIntCast()
{
    return boxPrim1(sigIntCast);
}

LIBFAUST_API Tree boxFloatCast()
{
    return boxPrim1(sigFloatCast);
}

LIBFAUST_API Tree boxReadOnlyTable()
{
    return boxPrim3(sigReadOnlyTable);
}

LIBFAUST_API Tree boxWriteReadTable()
{
    return boxPrim5(sigWriteReadTable);
}

LIBFAUST_API Tree boxSoundfile(const string& label, Tree chan)
{
    return boxSoundfile(tree(label), chan);
}

LIBFAUST_API Tree boxSelect2()
{
    return boxPrim3(sigSelect2);
}

LIBFAUST_API Tree boxSelect3()
{
    return boxPrim4(sigSelect3);
}

LIBFAUST_API Tree boxFConst(SType type, const string& name, const string& file)
{
    return boxFConst(tree(type), tree(name), tree(file));
}

LIBFAUST_API Tree boxFVar(SType type, const string& name, const string& file)
{
    return boxFVar(tree(type), tree(name), tree(file));
}

LIBFAUST_API Tree boxBinOp(SOperator op)
{
    static sigFun fun[] = {sigAdd, sigSub, sigMul, sigDiv, sigRem, sigLeftShift, sigLRightShift, sigARightShift, sigGT,
                           sigLT,  sigGE,  sigLE,  sigEQ,  sigNE,  sigAND,       sigOR,          sigXOR};
    faustassert(op >= kAdd && op <= kXOR);
    return boxPrim2(fun[op]);
}

// Specific binary mathematical functions

LIBFAUST_API Tree boxAdd()
{
    return boxPrim2(sigAdd);
}
LIBFAUST_API Tree boxSub()
{
    return boxPrim2(sigSub);
}
LIBFAUST_API Tree boxMul()
{
    return boxPrim2(sigMul);
}
LIBFAUST_API Tree boxDiv()
{
    return boxPrim2(sigDiv);
}
LIBFAUST_API Tree boxRem()
{
    return boxPrim2(sigRem);
}

LIBFAUST_API Tree boxLeftShift()
{
    return boxPrim2(sigLeftShift);
}
LIBFAUST_API Tree boxLRightShift()
{
    return boxPrim2(sigLRightShift);
}
LIBFAUST_API Tree boxARightShift()
{
    return boxPrim2(sigARightShift);
}

LIBFAUST_API Tree boxGT()
{
    return boxPrim2(sigGT);
}
LIBFAUST_API Tree boxLT()
{
    return boxPrim2(sigLT);
}
LIBFAUST_API Tree boxGE()
{
    return boxPrim2(sigGE);
}
LIBFAUST_API Tree boxLE()
{
    return boxPrim2(sigLE);
}
LIBFAUST_API Tree boxEQ()
{
    return boxPrim2(sigEQ);
}
LIBFAUST_API Tree boxNE()
{
    return boxPrim2(sigNE);
}

LIBFAUST_API Tree boxAND()
{
    return boxPrim2(sigAND);
}
LIBFAUST_API Tree boxOR()
{
    return boxPrim2(sigOR);
}
LIBFAUST_API Tree boxXOR()
{
    return boxPrim2(sigXOR);
}

// Extended unary of binary mathematical functions

LIBFAUST_API Tree boxAbs()
{
    return gGlobal->gAbsPrim->box();
}
LIBFAUST_API Tree boxAcos()
{
    return gGlobal->gAcosPrim->box();
}
LIBFAUST_API Tree boxTan()
{
    return gGlobal->gTanPrim->box();
}
LIBFAUST_API Tree boxSqrt()
{
    return gGlobal->gSqrtPrim->box();
}
LIBFAUST_API Tree boxSin()
{
    return gGlobal->gSinPrim->box();
}
LIBFAUST_API Tree boxRint()
{
    return gGlobal->gRintPrim->box();
}
LIBFAUST_API Tree boxRound()
{
    return gGlobal->gRoundPrim->box();
}
LIBFAUST_API Tree boxRemainder()
{
    return gGlobal->gRemainderPrim->box();
}
LIBFAUST_API Tree boxPow()
{
    return gGlobal->gPowPrim->box();
}
LIBFAUST_API Tree boxMin()
{
    return gGlobal->gMinPrim->box();
}
LIBFAUST_API Tree boxMax()
{
    return gGlobal->gMaxPrim->box();
}
LIBFAUST_API Tree boxLog()
{
    return gGlobal->gLogPrim->box();
}
LIBFAUST_API Tree boxLog10()
{
    return gGlobal->gLog10Prim->box();
}
LIBFAUST_API Tree boxFmod()
{
    return gGlobal->gAbsPrim->box();
}
LIBFAUST_API Tree boxFloor()
{
    return gGlobal->gFloorPrim->box();
}
LIBFAUST_API Tree boxExp()
{
    return gGlobal->gExpPrim->box();
}
LIBFAUST_API Tree boxExp10()
{
    return gGlobal->gExp10Prim->box();
}
LIBFAUST_API Tree boxCos()
{
    return gGlobal->gAbsPrim->box();
}
LIBFAUST_API Tree boxCeil()
{
    return gGlobal->gCeilPrim->box();
}
LIBFAUST_API Tree boxAtan()
{
    return gGlobal->gAtanPrim->box();
}
LIBFAUST_API Tree boxAtan2()
{
    return gGlobal->gAtan2Prim->box();
}
LIBFAUST_API Tree boxAsin()
{
    return gGlobal->gAsinPrim->box();
}

// User Interface

LIBFAUST_API Tree boxButton(const string& label)
{
    return boxButton(tree(label));
}

LIBFAUST_API Tree boxCheckbox(const string& label)
{
    return boxButton(tree(label));
}

LIBFAUST_API Tree boxVSlider(const string& label, Tree init, Tree min, Tree max, Tree step)
{
    return boxVSlider(tree(label), init, min, max, step);
}

LIBFAUST_API Tree boxHSlider(const string& label, Tree init, Tree min, Tree max, Tree step)
{
    return boxHSlider(tree(label), init, min, max, step);
}

LIBFAUST_API Tree boxNumEntry(const string& label, Tree init, Tree min, Tree max, Tree step)
{
    return boxNumEntry(tree(label), init, min, max, step);
}

LIBFAUST_API Tree boxVBargraph(const string& label, Tree min, Tree max)
{
    return boxVBargraph(tree(label), min, max);
}

LIBFAUST_API Tree boxHBargraph(const string& label, Tree min, Tree max)
{
    return boxHBargraph(tree(label), min, max);
}

LIBFAUST_API Tree boxVGroup(const std::string& label, Tree group)
{
    return boxVGroup(tree(label), group);
}

LIBFAUST_API Tree boxHGroup(const std::string& label, Tree group)
{
    return boxHGroup(tree(label), group);
}

LIBFAUST_API Tree boxTGroup(const std::string& label, Tree group)
{
    return boxTGroup(tree(label), group);
}

LIBFAUST_API Tree boxAttach()
{
    return boxPrim2(sigAttach);
}

// Helpers

LIBFAUST_API Tree boxPar3(Tree x, Tree y, Tree z)
{
    return boxPar(x, boxPar(y, z));
}

LIBFAUST_API Tree boxPar4(Tree a, Tree b, Tree c, Tree d)
{
    return boxPar(a, boxPar3(b, c, d));
}

LIBFAUST_API Tree boxPar5(Tree a, Tree b, Tree c, Tree d, Tree e)
{
    return boxPar(a, boxPar4(b, c, d, e));
}

LIBFAUST_API Tree boxDelay(Tree s, Tree del)
{
    return boxSeq(boxPar(s, del), boxDelay());
}

LIBFAUST_API Tree boxIntCast(Tree s)
{
    return boxSeq(s, boxIntCast());
}

LIBFAUST_API Tree boxFloatCast(Tree s)
{
    return boxSeq(s, boxFloatCast());
}

LIBFAUST_API Tree boxReadOnlyTable(Tree n, Tree init, Tree ridx)
{
    return boxSeq(boxPar3(n, init, ridx), boxReadOnlyTable());
}

LIBFAUST_API Tree boxWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx)
{
    return boxSeq(boxPar5(n, init, widx, wsig, ridx), boxWriteReadTable());
}

LIBFAUST_API Tree boxSoundfile(const string& label, Tree chan, Tree part, Tree ridx)
{
    return boxSeq(boxPar(part, ridx), boxSoundfile(label, chan));
}

LIBFAUST_API Tree boxSelect2(Tree selector, Tree s1, Tree s2)
{
    return boxSeq(boxPar3(selector, s1, s2), boxSelect2());
}

LIBFAUST_API Tree boxSelect3(Tree selector, Tree s1, Tree s2, Tree s3)
{
    return boxSeq(boxPar4(selector, s1, s2, s3), boxSelect3());
}

LIBFAUST_API Tree boxBinOp(SOperator op, Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxBinOp(op));
}

LIBFAUST_API Tree boxAdd(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxAdd());
}

LIBFAUST_API Tree boxSub(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxSub());
}

LIBFAUST_API Tree boxMul(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxMul());
}

LIBFAUST_API Tree boxDiv(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxDiv());
}

LIBFAUST_API Tree boxRem(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxRem());
}

LIBFAUST_API Tree boxLeftShift(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLeftShift());
}

LIBFAUST_API Tree boxLRightShift(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLRightShift());
}

LIBFAUST_API Tree boxARightShift(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxARightShift());
}

LIBFAUST_API Tree boxGT(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxGT());
}

LIBFAUST_API Tree boxLT(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLT());
}

LIBFAUST_API Tree boxGE(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxGE());
}

LIBFAUST_API Tree boxLE(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLE());
}

LIBFAUST_API Tree boxEQ(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxEQ());
}

LIBFAUST_API Tree boxNE(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxNE());
}

LIBFAUST_API Tree boxAND(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxAND());
}

LIBFAUST_API Tree boxOR(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxOR());
}

LIBFAUST_API Tree boxXOR(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxXOR());
}

LIBFAUST_API Tree boxAbs(Tree x)
{
    return boxSeq(x, boxAbs());
}

LIBFAUST_API Tree boxAcos(Tree x)
{
    return boxSeq(x, boxAcos());
}

LIBFAUST_API Tree boxTan(Tree x)
{
    return boxSeq(x, boxTan());
}

LIBFAUST_API Tree boxSqrt(Tree x)
{
    return boxSeq(x, boxSqrt());
}

LIBFAUST_API Tree boxSin(Tree x)
{
    return boxSeq(x, boxSin());
}

LIBFAUST_API Tree boxRint(Tree x)
{
    return boxSeq(x, boxRint());
}

LIBFAUST_API Tree boxRound(Tree x)
{
    return boxSeq(x, boxRound());
}

LIBFAUST_API Tree boxLog(Tree x)
{
    return boxSeq(x, boxLog());
}

LIBFAUST_API Tree boxLog10(Tree x)
{
    return boxSeq(x, boxLog10());
}

LIBFAUST_API Tree boxFloor(Tree x)
{
    return boxSeq(x, boxFloor());
}

LIBFAUST_API Tree boxExp(Tree x)
{
    return boxSeq(x, boxExp());
}

LIBFAUST_API Tree boxExp10(Tree x)
{
    return boxSeq(x, boxExp10());
}

LIBFAUST_API Tree boxCos(Tree x)
{
    return boxSeq(x, boxCos());
}

LIBFAUST_API Tree boxCeil(Tree x)
{
    return boxSeq(x, boxCeil());
}

LIBFAUST_API Tree boxAtan(Tree x)
{
    return boxSeq(x, boxAtan());
}

LIBFAUST_API Tree boxAsin(Tree x)
{
    return boxSeq(x, boxAsin());
}

LIBFAUST_API Tree boxRemainder(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxRemainder());
}

LIBFAUST_API Tree boxPow(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxPow());
}

LIBFAUST_API Tree boxMin(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxMin());
}

LIBFAUST_API Tree boxMax(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxMax());
}

LIBFAUST_API Tree boxFmod(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxFmod());
}

LIBFAUST_API Tree boxAtan2(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxAtan2());
}

LIBFAUST_API Tree boxVBargraph(const string& label, Tree min, Tree max, Tree x)
{
    return boxSeq(x, boxVBargraph(label, min, max));
}

LIBFAUST_API Tree boxHBargraph(const string& label, Tree min, Tree max, Tree x)
{
    return boxSeq(x, boxHBargraph(label, min, max));
}

LIBFAUST_API Tree boxAttach(Tree s1, Tree s2)
{
    return boxSeq(boxPar(s1, s2), boxAttach());
}

// ==========
// Box C API
// ==========

#ifdef __cplusplus
extern "C" {
#endif

LIBFAUST_API Tree CDSPToBoxes(const char* name_app, const char* dsp_content, int argc, const char* argv[], int* inputs, int* outputs, char* error_msg)
{
    string error_msg_aux;
    Tree   box = DSPToBoxes(name_app, dsp_content, argc, argv, inputs, outputs, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return box;
}

LIBFAUST_API bool CgetBoxType(Tree box, int* inputs, int* outputs)
{
    return getBoxType(box, inputs, outputs);
}

LIBFAUST_API Tree* CboxesToSignals(Tree box, char* error_msg)
{
    string error_msg_aux;
    tvec   signals = boxesToSignals(box, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    if (signals.size() > 0) {
        Tree*  res = (Tree*)malloc(sizeof(Tree) * (signals.size() + 1));
        size_t i;
        for (i = 0; i < signals.size(); i++) res[i] = signals[i];
        res[i] = nullptr;
        return res;
    } else {
        return nullptr;
    }
}
    
LIBFAUST_API char* CcreateSourceFromBoxes(const char* name_app, Tree box,
                                        const char* lang,
                                        int argc, const char* argv[],
                                        char* error_msg)
{
    string error_msg_aux;
    string source = createSourceFromBoxes(name_app, box, lang, argc, argv, error_msg_aux);
    if (source.size() > 0) {
        return strdup(source.c_str());
    } else {
        strncpy(error_msg, error_msg_aux.c_str(), 4096);
        return nullptr;
    }
}

LIBFAUST_API Tree CboxInt(int n)
{
    return boxInt(n);
}

LIBFAUST_API Tree CboxReal(double n)
{
    return boxReal(n);
}

LIBFAUST_API Tree CboxWire()
{
    return boxWire();
}

LIBFAUST_API Tree CboxCut()
{
    return boxCut();
}

LIBFAUST_API Tree CboxSeq(Tree x, Tree y)
{
    return boxSeq(x, y);
}

LIBFAUST_API Tree CboxPar(Tree x, Tree y)
{
    return boxPar(x, y);
}

LIBFAUST_API Tree CboxSplit(Tree x, Tree y)
{
    return boxSplit(x, y);
}

LIBFAUST_API Tree CboxMerge(Tree x, Tree y)
{
    return boxMerge(x, y);
}

LIBFAUST_API Tree CboxRec(Tree x, Tree y)
{
    return boxRec(x, y);
}

LIBFAUST_API Tree CboxRoute(Tree n, Tree m, Tree r)
{
    return boxRoute(n, m, r);
}

LIBFAUST_API Tree CboxDelay()
{
    return boxDelay();
}

LIBFAUST_API Tree CboxIntCast()
{
    return boxIntCast();
}

LIBFAUST_API Tree CboxFloatCast()
{
    return boxFloatCast();
}

LIBFAUST_API Tree CboxReadOnlyTable()
{
    return boxReadOnlyTable();
}

LIBFAUST_API Tree CboxWriteReadTable()
{
    return boxWriteReadTable();
}

LIBFAUST_API Tree CboxWaveform(Tree* wf_aux)
{
    tvec wf;
    int  i = 0;
    while (wf_aux[i]) {
        wf.push_back(wf_aux[i]);
        i++;
    }
    return boxWaveform(wf);
}

LIBFAUST_API Tree CboxSoundfile(const char* label, Tree chan)
{
    return boxSoundfile(label, chan);
}

LIBFAUST_API Tree CboxSelect2()
{
    return boxSelect2();
}

LIBFAUST_API Tree CboxSelect3()
{
    return boxSelect3();
}

LIBFAUST_API Tree CboxFConst(SType type, const char* name, const char* file)
{
    return boxFConst(type, name, file);
}

LIBFAUST_API Tree CboxFVar(SType type, const char* name, const char* file)
{
    return boxFVar(type, name, file);
}

LIBFAUST_API Tree CboxBinOp(SOperator op)
{
    return boxBinOp(op);
}

// Specific binary mathematical functions

LIBFAUST_API Tree CboxAdd()
{
    return boxAdd();
}
LIBFAUST_API Tree CboxSub()
{
    return boxSub();
}
LIBFAUST_API Tree CboxMul()
{
    return boxMul();
}
LIBFAUST_API Tree CboxDiv()
{
    return boxDiv();
}
LIBFAUST_API Tree CboxRem()
{
    return boxRem();
}

LIBFAUST_API Tree CboxLeftShift()
{
    return boxLeftShift();
}
LIBFAUST_API Tree CboxLRightShift()
{
    return boxLRightShift();
}
LIBFAUST_API Tree CboxARightShift()
{
    return boxARightShift();
}

LIBFAUST_API Tree CboxGT()
{
    return boxGT();
}
LIBFAUST_API Tree CboxLT()
{
    return boxLT();
}
LIBFAUST_API Tree CboxGE()
{
    return boxGE();
}
LIBFAUST_API Tree CboxLE()
{
    return boxLE();
}
LIBFAUST_API Tree CboxEQ()
{
    return boxEQ();
}
LIBFAUST_API Tree CboxNE()
{
    return boxNE();
}

LIBFAUST_API Tree CboxAND()
{
    return boxAND();
}
LIBFAUST_API Tree CboxOR()
{
    return boxOR();
}
LIBFAUST_API Tree CboxXOR()
{
    return boxXOR();
}

// Extended unary of binary mathematical functions

LIBFAUST_API Tree CboxAbs()
{
    return boxAbs();
}
LIBFAUST_API Tree CboxAcos()
{
    return boxAcos();
}
LIBFAUST_API Tree CboxTan()
{
    return boxTan();
}
LIBFAUST_API Tree CboxSqrt()
{
    return boxSqrt();
}
LIBFAUST_API Tree CboxSin()
{
    return boxSin();
}
LIBFAUST_API Tree CboxRint()
{
    return boxRint();
}
LIBFAUST_API Tree CboxRound()
{
    return boxRound();
}
LIBFAUST_API Tree CboxRemainder()
{
    return boxRemainder();
}
LIBFAUST_API Tree CboxPow()
{
    return boxPow();
}
LIBFAUST_API Tree CboxMin()
{
    return boxMin();
}
LIBFAUST_API Tree CboxMax()
{
    return boxMax();
}
LIBFAUST_API Tree CboxLog()
{
    return boxLog();
}
LIBFAUST_API Tree CboxLog10()
{
    return boxLog10();
}
LIBFAUST_API Tree CboxFmod()
{
    return boxFmod();
}
LIBFAUST_API Tree CboxFloor()
{
    return boxFloor();
}
LIBFAUST_API Tree CboxExp()
{
    return boxExp();
}
LIBFAUST_API Tree CboxExp10()
{
    return boxExp10();
}
LIBFAUST_API Tree CboxCos()
{
    return boxCos();
}
LIBFAUST_API Tree CboxCeil()
{
    return boxCeil();
}
LIBFAUST_API Tree CboxAtan()
{
    return boxAtan();
}
LIBFAUST_API Tree CboxAtan2()
{
    return boxAtan2();
}
LIBFAUST_API Tree CboxAsin()
{
    return boxAsin();
}

// User Interface

LIBFAUST_API Tree CboxButton(const char* label)
{
    return boxButton(label);
}

LIBFAUST_API Tree CboxCheckbox(const char* label)
{
    return boxButton(label);
}

LIBFAUST_API Tree CboxVSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return boxVSlider(label, init, min, max, step);
}

LIBFAUST_API Tree CboxHSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return boxHSlider(label, init, min, max, step);
}

LIBFAUST_API Tree CboxNumEntry(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return boxNumEntry(label, init, min, max, step);
}

LIBFAUST_API Tree CboxVBargraph(const char* label, Tree min, Tree max)
{
    return boxVBargraph(label, min, max);
}

LIBFAUST_API Tree CboxHBargraph(const char* label, Tree min, Tree max)
{
    return boxHBargraph(label, min, max);
}
    
LIBFAUST_API Tree CboxVGroup(const char* label, Tree group)
{
    return boxVGroup(label, group);
}
    
LIBFAUST_API Tree CboxHGroup(const char* label, Tree group)
{
    return boxHGroup(label, group);
}
    
LIBFAUST_API Tree CboxTGroup(const char* label, Tree group)
{
    return boxTGroup(label, group);
}

LIBFAUST_API Tree CboxAttach()
{
    return boxAttach();
}

// Box test API

LIBFAUST_API bool CisBoxAbstr(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxAbstr(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxAccess(Tree t, Tree* exp_aux, Tree* id_aux)
{
    Tree exp, id;
    if (isBoxAccess(t, exp, id)) {
        *exp_aux = exp;
        *id_aux = id;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxAppl(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxAppl(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxButton(Tree t, Tree* lbl_aux)
{
    Tree lbl;
    if (isBoxButton(t, lbl)) {
        *lbl_aux = lbl;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxCase(Tree t, Tree* rules_aux)
{
    Tree rules;
    if (isBoxCase(t, rules)) {
        *rules_aux = rules;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxCheckbox(Tree t, Tree* lbl_aux)
{
    Tree lbl;
    if (isBoxCheckbox(t, lbl)) {
        *lbl_aux = lbl;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxComponent(Tree t, Tree* filename_aux)
{
    Tree filename;
    if (isBoxComponent(t, filename)) {
        *filename_aux = filename;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxCut(Tree t)
{
    return isBoxCut(t);
}

LIBFAUST_API bool CisBoxEnvironment(Tree t)
{
    return isBoxEnvironment(t);
}

LIBFAUST_API bool CisBoxError(Tree t)
{
    return isBoxError(t);
}

LIBFAUST_API bool CisBoxFConst(Tree t, Tree* type_aux, Tree* name_aux, Tree* file_aux)
{
    Tree type, name, file;
    if (isBoxFConst(t, type, name, file)) {
        *type_aux = type;
        *name_aux = name;
        *file_aux = file;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxFFun(Tree t, Tree* ff_aux)
{
    Tree ff;
    if (isBoxFFun(t, ff)) {
        *ff_aux = ff;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxFVar(Tree t, Tree* type_aux, Tree* name_aux, Tree* file_aux)
{
    Tree type, name, file;
    if (isBoxFVar(t, type, name, file)) {
        *type_aux = type;
        *name_aux = name;
        *file_aux = file;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxHBargraph(Tree t, Tree* lbl_aux, Tree* min_aux, Tree* max_aux)
{
    Tree lbl, min, max;
    if (isBoxHBargraph(t, lbl, min, max)) {
        *lbl_aux = lbl;
        *min_aux = min;
        *max_aux = max;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxHGroup(Tree t, Tree* lbl_aux, Tree* x_aux)
{
    Tree lbl, x;
    if (isBoxHGroup(t, lbl, x)) {
        *lbl_aux = lbl;
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxHSlider(Tree t, Tree* lbl_aux, Tree* cur_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, cur, min, max, step;
    if (isBoxHSlider(t, lbl, cur, min, max, step)) {
        *lbl_aux = lbl;
        *cur_aux = cur;
        *min_aux = min;
        *max_aux = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxIdent(Tree t, const char** str)
{
    return isBoxIdent(t, str);
}

LIBFAUST_API bool CisBoxInputs(Tree t, Tree* x_aux)
{
    Tree x;
    if (isBoxInputs(t, x)) {
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxInt(Tree t, int* i)
{
    return isBoxInt(t, i);
}

LIBFAUST_API bool CisBoxIPar(Tree t, Tree* x_aux, Tree* y_aux, Tree* z_aux)
{
    Tree x, y, z;
    if (isBoxIPar(t, x, y, z)) {
        *x_aux = x;
        *y_aux = y;
        *z_aux = z;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxIProd(Tree t, Tree* x_aux, Tree* y_aux, Tree* z_aux)
{
    Tree x, y, z;
    if (isBoxIProd(t, x, y, z)) {
        *x_aux = x;
        *y_aux = y;
        *z_aux = z;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxISeq(Tree t, Tree* x_aux, Tree* y_aux, Tree* z_aux)
{
    Tree x, y, z;
    if (isBoxISeq(t, x, y, z)) {
        *x_aux = x;
        *y_aux = y;
        *z_aux = z;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxISum(Tree t, Tree* x_aux, Tree* y_aux, Tree* z_aux)
{
    Tree x, y, z;
    if (isBoxISum(t, x, y, z)) {
        *x_aux = x;
        *y_aux = y;
        *z_aux = z;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxLibrary(Tree t, Tree* filename_aux)
{
    Tree filename;
    if (isBoxLibrary(t, filename)) {
        *filename_aux = filename;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxMerge(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxMerge(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxMetadata(Tree t, Tree* exp_aux, Tree* mdlist_aux)
{
    Tree exp, mdlist;
    if (isBoxMetadata(t, exp, mdlist)) {
        *exp_aux = exp;
        *mdlist_aux = mdlist;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxNumEntry(Tree t, Tree* lbl_aux, Tree* cur_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, cur, min, max, step;
    if (isBoxNumEntry(t, lbl, cur, min, max, step)) {
        *lbl_aux = lbl;
        *cur_aux = cur;
        *min_aux = min;
        *max_aux = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxOutputs(Tree t, Tree* x_aux)
{
    Tree x;
    if (isBoxOutputs(t, x)) {
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxPar(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxPar(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxPrim0(Tree t)
{
    return isBoxPrim0(t);
}

LIBFAUST_API bool CisBoxPrim1(Tree t)
{
    return isBoxPrim1(t);
}

LIBFAUST_API bool CisBoxPrim2(Tree t)
{
    return isBoxPrim2(t);
}

LIBFAUST_API bool CisBoxPrim3(Tree t)
{
    return isBoxPrim3(t);
}

LIBFAUST_API bool CisBoxPrim4(Tree t)
{
    return isBoxPrim4(t);
}

LIBFAUST_API bool CisBoxPrim5(Tree t)
{
    return isBoxPrim5(t);
}

LIBFAUST_API bool CisBoxReal(Tree t, double* r)
{
    return isBoxReal(t, r);
}

LIBFAUST_API bool CisBoxRec(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxRec(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxRoute(Tree t, Tree* n_aux, Tree* m_aux, Tree* r_aux)
{
    Tree n, m, r;
    if (isBoxRoute(t, n, m, r)) {
        *n_aux = n;
        *m_aux = m;
        *r_aux = r;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxSeq(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxSeq(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxSlot(Tree t, int* id)
{
    return isBoxSlot(t, id);
}

LIBFAUST_API bool CisBoxSoundfile(Tree t, Tree* label_aux, Tree* chan_aux)
{
    Tree label, chan;
    if (isBoxSoundfile(t, label, chan)) {
        *label_aux = label;
        *chan_aux = chan;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxSplit(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxSplit(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxSymbolic(Tree t, Tree* slot_aux, Tree* body_aux)
{
    Tree slot, body;
    if (isBoxSymbolic(t, slot, body)) {
        *slot_aux = slot;
        *body_aux = body;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxTGroup(Tree t, Tree* lbl_aux, Tree* x_aux)
{
    Tree lbl, x;
    if (isBoxTGroup(t, lbl, x)) {
        *lbl_aux = lbl;
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxVBargraph(Tree t, Tree* lbl_aux, Tree* min_aux, Tree* max_aux)
{
    Tree lbl, min, max;
    if (isBoxVBargraph(t, lbl, min, max)) {
        *lbl_aux = lbl;
        *min_aux = min;
        *max_aux = max;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxVGroup(Tree t, Tree* lbl_aux, Tree* x_aux)
{
    Tree lbl, x;
    if (isBoxVGroup(t, lbl, x)) {
        *lbl_aux = lbl;
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxVSlider(Tree t, Tree* lbl_aux, Tree* cur_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, cur, min, max, step;
    if (isBoxVSlider(t, lbl, cur, min, max, step)) {
        *lbl_aux = lbl;
        *cur_aux = cur;
        *min_aux = min;
        *max_aux = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxWaveform(Tree t)
{
    return isBoxWaveform(t);
}

LIBFAUST_API bool CisBoxWire(Tree t)
{
    return isBoxWire(t);
}

LIBFAUST_API bool CisBoxWithLocalDef(Tree t, Tree* body_aux, Tree* ldef_aux)
{
    Tree body, ldef;
    if (isBoxWithLocalDef(t, body, ldef)) {
        *body_aux = body;
        *ldef_aux = ldef;
        return true;
    } else {
        return false;
    }
}

// Helpers

LIBFAUST_API Tree CboxPar3(Tree x, Tree y, Tree z)
{
    return CboxPar(x, CboxPar(y, z));
}

LIBFAUST_API Tree CboxPar4(Tree a, Tree b, Tree c, Tree d)
{
    return CboxPar(a, CboxPar3(b, c, d));
}

LIBFAUST_API Tree CboxPar5(Tree a, Tree b, Tree c, Tree d, Tree e)
{
    return CboxPar(a, CboxPar4(b, c, d, e));
}

LIBFAUST_API Tree CboxDelayAux(Tree s, Tree del)
{
    return CboxSeq(CboxPar(s, del), CboxDelay());
}

LIBFAUST_API Tree CboxIntCastAux(Tree s)
{
    return CboxSeq(s, CboxIntCast());
}

LIBFAUST_API Tree CboxFloatCastAux(Tree s)
{
    return CboxSeq(s, CboxFloatCast());
}

LIBFAUST_API Tree CboxReadOnlyTableAux(Tree n, Tree init, Tree ridx)
{
    return CboxSeq(CboxPar3(n, init, ridx), CboxReadOnlyTable());
}

LIBFAUST_API Tree CboxWriteReadTableAux(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx)
{
    return CboxSeq(boxPar5(n, init, widx, wsig, ridx), CboxWriteReadTable());
}

LIBFAUST_API Tree CoxSoundfileAux(const char* label, Tree chan, Tree part, Tree ridx)
{
    return CboxSeq(CboxPar(part, ridx), CboxSoundfile(label, chan));
}

LIBFAUST_API Tree CboxSelect2Aux(Tree selector, Tree s1, Tree s2)
{
    return CboxSeq(CboxPar3(selector, s1, s2), CboxSelect2());
}

LIBFAUST_API Tree CboxSelect3Aux(Tree selector, Tree s1, Tree s2, Tree s3)
{
    return CboxSeq(CboxPar4(selector, s1, s2, s3), CboxSelect3());
}

LIBFAUST_API Tree CboxBinOpAux(SOperator op, Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxBinOp(op));
}

LIBFAUST_API Tree CboxAddAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxAdd());
}

LIBFAUST_API Tree CboxSubAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxSub());
}

LIBFAUST_API Tree CboxMulAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxMul());
}

LIBFAUST_API Tree CboxDivAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxDiv());
}

LIBFAUST_API Tree CboxRemAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxRem());
}

LIBFAUST_API Tree CboxLeftShiftAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxLeftShift());
}

LIBFAUST_API Tree CboxLRightShiftAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxLRightShift());
}

LIBFAUST_API Tree CboxARightShiftAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxARightShift());
}

LIBFAUST_API Tree CboxGTAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxGT());
}

LIBFAUST_API Tree CboxLTAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxLT());
}

LIBFAUST_API Tree CboxGEAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxGE());
}

LIBFAUST_API Tree CboxLEAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxLE());
}

LIBFAUST_API Tree CboxEQAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxEQ());
}

LIBFAUST_API Tree CboxNEAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxNE());
}

LIBFAUST_API Tree CboxANDAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxAND());
}

LIBFAUST_API Tree CboxORAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxOR());
}

LIBFAUST_API Tree CboxXORAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxXOR());
}

LIBFAUST_API Tree CboxAbsAux(Tree x)
{
    return CboxSeq(x, CboxAbs());
}

LIBFAUST_API Tree CboxAcosAux(Tree x)
{
    return CboxSeq(x, CboxAcos());
}

LIBFAUST_API Tree CboxTanAux(Tree x)
{
    return CboxSeq(x, CboxTan());
}

LIBFAUST_API Tree CboxSqrtAux(Tree x)
{
    return CboxSeq(x, CboxSqrt());
}

LIBFAUST_API Tree CboxSinAux(Tree x)
{
    return CboxSeq(x, CboxSin());
}

LIBFAUST_API Tree CboxRintAux(Tree x)
{
    return CboxSeq(x, CboxRint());
}
    
LIBFAUST_API Tree CboxRoundAux(Tree x)
{
    return CboxSeq(x, CboxRound());
}

LIBFAUST_API Tree CboxLogAux(Tree x)
{
    return CboxSeq(x, CboxLog());
}

LIBFAUST_API Tree CboxLog10Aux(Tree x)
{
    return CboxSeq(x, CboxLog10());
}

LIBFAUST_API Tree CboxFloorAux(Tree x)
{
    return CboxSeq(x, CboxFloor());
}

LIBFAUST_API Tree CboxExpAux(Tree x)
{
    return CboxSeq(x, CboxExp());
}

LIBFAUST_API Tree CboxExp10Aux(Tree x)
{
    return CboxSeq(x, CboxExp10());
}

LIBFAUST_API Tree CboxCosAux(Tree x)
{
    return CboxSeq(x, CboxCos());
}

LIBFAUST_API Tree CboxCeilAux(Tree x)
{
    return CboxSeq(x, CboxCeil());
}

LIBFAUST_API Tree CboxAtanAux(Tree x)
{
    return CboxSeq(x, CboxAtan());
}

LIBFAUST_API Tree CboxAsinAux(Tree x)
{
    return CboxSeq(x, CboxAsin());
}

LIBFAUST_API Tree CboxRemainderAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxRemainder());
}

LIBFAUST_API Tree CboxPowAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxPow());
}

LIBFAUST_API Tree CboxMinAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxMin());
}

LIBFAUST_API Tree CboxMaxAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxMax());
}

LIBFAUST_API Tree CboxFmodAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxFmod());
}

LIBFAUST_API Tree CboxAtan2Aux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxAtan2());
}

LIBFAUST_API Tree CboxVBargraphAux(const char* label, Tree min, Tree max, Tree x)
{
    return CboxSeq(x, CboxVBargraph(label, min, max));
}

LIBFAUST_API Tree CboxHBargraphAux(const char* label, Tree min, Tree max, Tree x)
{
    return CboxSeq(x, CboxHBargraph(label, min, max));
}

LIBFAUST_API Tree CboxAttachAux(Tree s1, Tree s2)
{
    return CboxSeq(CboxPar(s1, s2), CboxAttach());
}

LIBFAUST_API char* CprintBox(Tree box, bool shared, int max_size)
{
    string res = printBox(box, shared, max_size);
    return strdup(res.c_str());
}

LIBFAUST_API char* CprintSignal(Tree sig, bool shared, int max_size)
{
    string res = printSignal(sig, shared, max_size);
    return strdup(res.c_str());
}

#ifdef __cplusplus
}
#endif
