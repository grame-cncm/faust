/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

/*****************************************************************************
    HISTORY
    22/01/05 : added int cast in select2 and select3 selection signal
*****************************************************************************/

/*
 * THE FACADE: sigXXX / isSigXXX are the exposed signal API, reimplemented over
 * the algebra. Every constructor delegates to the session's initial algebra
 * (sigs::algebra(), a TreeAlgebra) and every destructor to the pattern algebra
 * (sigpattern.hh) -- the depth-1 fragment of which is exactly this idiom. The
 * algebra is the single source of truth for tree shapes; the facade only adds
 * the API's own semantics: the folding casts (sigIntCast/sigFloatCast), the
 * zero-divisor diagnostic of sigRem, and the normalizing constructors of the
 * extended primitives (which fold through the primitive itself).
 */

#include <float.h>
#include <vector>

#include "sigs-state.hh"
#include "ppsig.hh"
#include "signals.hh"
#include "sigpattern.hh"
#include "sigtreealgebra.hh"
#include "xtended.hh"

using namespace std;

/// The session's initial algebra (rebuilt by initSignalSymbols()).
static const TreeAlgebra& A()
{
    return sigs::algebra();
}

SIGS_API Tree sigWriteReadTable(Tree size, Tree init, Tree widx, Tree wsig, Tree ridx)
{
    /*
     rwtable are parsed as boxPrim5, so do not have a special treatment in eval/propagate. So we do
     here:
     - the size argument is supposed to be known at compile time, it will be simplified in
     'simplify'
     - rwtable is using a fully filled sigWRTbl signal
     */
    return sigRDTbl(sigWRTbl(size, sigGen(init), widx, wsig), ridx);
}

SIGS_API Tree sigReadOnlyTable(Tree size, Tree init, Tree ridx)
{
    /*
     rtable are parsed as boxPrim3, so do not have a special treatment in eval/propagate. So we do
     here:
     - the size argument is supposed to be known at compile time, it will be simplified in
     'simplify'
     - rdtable is using a 'degenerated' sigWRTbl signal with NIL 'wi' and 'ws' parameters
     */
    return sigRDTbl(sigWRTbl(size, sigGen(init)), ridx);
}

////////////////////////////////////////////////////////////////////////
/**
 * Signals
 */
///////////////////////////////////////////////////////////////////////

SIGS_API Tree sigRem(Tree x, Tree y)
{
    // API semantics, not construction: a constant zero divisor is diagnosed here
    if (isZero(y)) {
        stringstream error;
        error << "ERROR : % by 0 in " << ppsig(x, MAX_ERROR_SIZE) << " % "
              << ppsig(y, MAX_ERROR_SIZE) << endl;
        tlib::error(error.str());
    }
    return sigBinOp(kRem, x, y);
}

SIGS_API Tree sigInt(int i)
{
    return A().IntNum(i);
}
SIGS_API bool isSigInt(Tree t, int* i)
{
    return isInt(t->node(), i);
}

Tree sigInt64(int64_t i)
{
    return A().Int64Num(i);
}
bool isSigInt64(Tree t, int64_t* i)
{
    return isInt64(t->node(), i);
}

SIGS_API Tree sigReal(double r)
{
    return A().FloatNum(r);
}
SIGS_API bool isSigReal(Tree t, double* r)
{
    return isDouble(t->node(), r);
}

SIGS_API Tree sigInput(int i)
{
    return A().Input(sigInt(i));
}

SIGS_API bool isSigInput(Tree t, int* i)
{
    Tree x = nullptr;
    return pat::Input(pat::var(x)).match(t) && isInt(x->node(), i);
}

Tree sigOutput(int i, Tree t0)
{
    return A().Output(sigInt(i), t0);
}
SIGS_API bool isSigOutput(Tree t, int* i, Tree& t0)
{
    Tree x = nullptr;
    return pat::Output(pat::var(x), pat::var(t0)).match(t) && isInt(x->node(), i);
}

Tree sigDelay0(Tree t0)
{
    return sigDelay(t0, sigInt(0));
}

SIGS_API Tree sigDelay1(Tree t0)
{
    return A().Mem(t0);
}
SIGS_API bool isSigDelay1(Tree t, Tree& t0)
{
    return pat::Mem(pat::var(t0)).match(t);
}

SIGS_API Tree sigDelay(Tree t0, Tree t1)
{
    return A().Delay(t0, t1);
}
SIGS_API bool isSigDelay(Tree t, Tree& t0, Tree& t1)
{
    return pat::Delay(pat::var(t0), pat::var(t1)).match(t);
}

Tree sigPrefix(Tree t0, Tree t1)
{
    return A().Prefix(t0, t1);
}
SIGS_API bool isSigPrefix(Tree t, Tree& t0, Tree& t1)
{
    return pat::Prefix(pat::var(t0), pat::var(t1)).match(t);
}

// Read only and read write tables

Tree sigRDTbl(Tree tbl, Tree ri)
{
    return A().RDTbl(tbl, ri);
}
SIGS_API bool isSigRDTbl(Tree s, Tree& tbl, Tree& ri)
{
    return pat::RDTbl(pat::var(tbl), pat::var(ri)).match(s);
}

Tree sigWRTbl(Tree size, Tree gen, Tree wi, Tree ws)
{
    return (wi == ::nil()) ? A().Table(size, gen) : A().WRTbl(size, gen, wi, ws);
}
SIGS_API bool isSigWRTbl(Tree u, Tree& size, Tree& gen, Tree& wi, Tree& ws)
{
    return pat::WRTbl(pat::var(size), pat::var(gen), pat::var(wi), pat::var(ws)).match(u);
}

SIGS_API bool isSigWRTbl(Tree u, Tree& size, Tree& gen)
{
    Tree wi = nullptr, ws = nullptr;
    return pat::WRTbl(pat::var(size), pat::var(gen), pat::var(wi), pat::var(ws)).match(u) &&
           (wi == ::nil());
}

// Signal used to generate the initial content of a table

Tree sigGen(Tree s)
{
    return A().Gen(s);
}
SIGS_API bool isSigGen(Tree t, Tree& x)
{
    return pat::Gen(pat::var(x)).match(t);
}
bool isSigGen(Tree t)
{
    return pat::headOnly(Node(sigs::g.SIGGEN)).match(t);
}

// Documentator Tables : special version of tables only for documentation purposes

Tree sigDocConstantTbl(Tree n, Tree sig)
{
    return A().DocConstantTbl(n, sig);
}
SIGS_API bool isSigDocConstantTbl(Tree t, Tree& n, Tree& sig)
{
    return pat::DocConstantTbl(pat::var(n), pat::var(sig)).match(t);
}

Tree sigDocWriteTbl(Tree n, Tree sig, Tree widx, Tree wsig)
{
    return A().DocWriteTbl(n, sig, widx, wsig);
}
SIGS_API bool isSigDocWriteTbl(Tree t, Tree& n, Tree& sig, Tree& widx, Tree& wsig)
{
    return pat::DocWriteTbl(pat::var(n), pat::var(sig), pat::var(widx), pat::var(wsig)).match(t);
}

Tree sigDocAccessTbl(Tree tbl, Tree ridx)
{
    return A().DocAccessTbl(tbl, ridx);
}
SIGS_API bool isSigDocAccessTbl(Tree t, Tree& tbl, Tree& ridx)
{
    return pat::DocAccessTbl(pat::var(tbl), pat::var(ridx)).match(t);
}

// Select on signal among severals

SIGS_API Tree sigSelect2(Tree selector, Tree s1, Tree s2)
{
    return A().Select2(selector, s1, s2);
}
SIGS_API bool isSigSelect2(Tree t, Tree& selector, Tree& s1, Tree& s2)
{
    return pat::Select2(pat::var(selector), pat::var(s1), pat::var(s2)).match(t);
}

// "select3" expressed with "select2"
SIGS_API Tree sigSelect3(Tree selector, Tree s1, Tree s2, Tree s3)
{
    return sigSelect2(sigBinOp(kEQ, selector, sigInt(0)),
                      sigSelect2(sigBinOp(kEQ, selector, sigInt(1)), s3, s2), s1);
}

Tree sigAssertBounds(Tree s1, Tree s2, Tree s3)
{
    return A().AssertBounds(s1, s2, s3);
}

SIGS_API bool isSigAssertBounds(Tree t, Tree& s1, Tree& s2, Tree& s3)
{
    return pat::AssertBounds(pat::var(s1), pat::var(s2), pat::var(s3)).match(t);
}

Tree sigHighest(Tree s)
{
    return A().Highest(s);
}

SIGS_API bool isSigHighest(Tree t, Tree& s)
{
    return pat::Highest(pat::var(s)).match(t);
}

Tree sigLowest(Tree s)
{
    return A().Lowest(s);
}

SIGS_API bool isSigLowest(Tree t, Tree& s)
{
    return pat::Lowest(pat::var(s)).match(t);
}

// Arithmetical operations

SIGS_API Tree sigBinOp(SOperator op, Tree x, Tree y)
{
    return sigBinOp(int(op), x, y);
}

SIGS_API Tree sigBinOp(int op, Tree x, Tree y)
{
    // the algebra is the authority on the shape, one named operation per opcode
    switch (op) {
        case kAdd:
            return A().Add(x, y);
        case kSub:
            return A().Sub(x, y);
        case kMul:
            return A().Mul(x, y);
        case kDiv:
            return A().Div(x, y);
        case kRem:
            return A().Mod(x, y);
        case kLsh:
            return A().Lsh(x, y);
        case kARsh:
            return A().ARsh(x, y);
        case kLRsh:
            return A().LRsh(x, y);
        case kGT:
            return A().Gt(x, y);
        case kLT:
            return A().Lt(x, y);
        case kGE:
            return A().Ge(x, y);
        case kLE:
            return A().Le(x, y);
        case kEQ:
            return A().Eq(x, y);
        case kNE:
            return A().Ne(x, y);
        case kAND:
            return A().And(x, y);
        case kOR:
            return A().Or(x, y);
        case kXOR:
            return A().Xor(x, y);
        default:
            tlib::error("ASSERT : sigBinOp -- unknown operator code\n");
            return nullptr;
    }
}

SIGS_API bool isSigBinOp(Tree s, int* op, Tree& x, Tree& y)
{
    Tree t = nullptr;
    return pat::BinOp(pat::var(t), pat::var(x), pat::var(y)).match(s) && isInt(t->node(), op);
}

// Foreign Functions

Tree sigFFun(Tree ff, Tree largs)
{
    // structural through the transformation driver too (see TransformAlgebra::ffApp)
    return tree(sigs::g.SIGFFUN, ff, largs);
}
SIGS_API bool isSigFFun(Tree s, Tree& ff, Tree& largs)
{
    return pat::FFun(pat::var(ff), pat::var(largs)).match(s);
}

SIGS_API Tree sigFConst(Tree type, Tree name, Tree file)
{
    return A().ForeignConst(tree2int(type), name, file);
}
bool isSigFConst(Tree s)
{
    return pat::FConst(pat::any(), pat::any(), pat::any()).match(s);
}
SIGS_API bool isSigFConst(Tree s, Tree& type, Tree& name, Tree& file)
{
    return pat::FConst(pat::var(type), pat::var(name), pat::var(file)).match(s);
}

SIGS_API Tree sigFVar(Tree type, Tree name, Tree file)
{
    return A().ForeignVar(tree2int(type), name, file);
}
bool isSigFVar(Tree s)
{
    return pat::FVar(pat::any(), pat::any(), pat::any()).match(s);
}
SIGS_API bool isSigFVar(Tree s, Tree& type, Tree& name, Tree& file)
{
    return pat::FVar(pat::var(type), pat::var(name), pat::var(file)).match(s);
}

// Projection is now a tlib primitive (proj/isProj, see tree.hh) : it is intrinsic to
// n-ary recursion and belongs with rec/ref. These keep the signal-facing names and the
// int* signature so the dozens of call sites are untouched ; they just forward to tlib.
// (The int& overload picked below is tlib's -- the int* one is this very function.)

Tree sigProj(int i, Tree rgroup)
{
    return proj(i, rgroup);
}
SIGS_API bool isProj(Tree t, int* i, Tree& rgroup)
{
    return isProj(t, *i, rgroup);
}

// Int, Bitcast and Float casting

SIGS_API Tree sigIntCast(Tree t)
{
    // API semantics: this constructor FOLDS numeric arguments (the initial
    // algebra's IntCast, by contrast, builds exactly what is asked)
    Node   n = t->node();
    int    i;
    double x;

    if (isInt(n, &i)) {
        return t;
    }
    if (isDouble(n, &x)) {
        return sigInt(int(x));
    }

    return A().IntCast(t);
}

Tree sigBitCast(Tree t)
{
    return A().BitCast(t);
}

SIGS_API Tree sigFloatCast(Tree t)
{
    // API semantics: folding constructor (see sigIntCast)
    Node   n = t->node();
    int    i;
    double x;

    if (isInt(n, &i)) {
        return sigReal(double(i));
    }
    if (isDouble(n, &x)) {
        return t;
    }

    return A().FloatCast(t);
}

bool isSigIntCast(Tree t)
{
    return pat::IntCast(pat::any()).match(t);
}
SIGS_API bool isSigIntCast(Tree t, Tree& x)
{
    return pat::IntCast(pat::var(x)).match(t);
}

bool isSigBitCast(Tree t)
{
    return pat::BitCast(pat::any()).match(t);
}
bool isSigBitCast(Tree t, Tree& x)
{
    return pat::BitCast(pat::var(x)).match(t);
}

bool isSigFloatCast(Tree t)
{
    return pat::FloatCast(pat::any()).match(t);
}
SIGS_API bool isSigFloatCast(Tree t, Tree& x)
{
    return pat::FloatCast(pat::var(x)).match(t);
}

// Emulation of all fonctions

SIGS_API Tree sigAdd(Tree x, Tree y)
{
    return sigBinOp(kAdd, x, y);
}
SIGS_API Tree sigSub(Tree x, Tree y)
{
    return sigBinOp(kSub, x, y);
}
SIGS_API Tree sigMul(Tree x, Tree y)
{
    return sigBinOp(kMul, x, y);
}
SIGS_API Tree sigDiv(Tree x, Tree y)
{
    return sigBinOp(kDiv, x, y);
}

SIGS_API Tree sigAND(Tree x, Tree y)
{
    return sigBinOp(kAND, x, y);
}
SIGS_API Tree sigOR(Tree x, Tree y)
{
    return sigBinOp(kOR, x, y);
}
SIGS_API Tree sigXOR(Tree x, Tree y)
{
    return sigBinOp(kXOR, x, y);
}

SIGS_API Tree sigLeftShift(Tree x, Tree y)
{
    return sigBinOp(kLsh, x, y);
}
SIGS_API Tree sigARightShift(Tree x, Tree y)
{
    return sigBinOp(kARsh, x, y);
}
SIGS_API Tree sigLRightShift(Tree x, Tree y)
{
    return sigBinOp(kLRsh, x, y);
}

SIGS_API Tree sigGT(Tree x, Tree y)
{
    return sigBinOp(kGT, x, y);
}
SIGS_API Tree sigLT(Tree x, Tree y)
{
    return sigBinOp(kLT, x, y);
}
SIGS_API Tree sigGE(Tree x, Tree y)
{
    return sigBinOp(kGE, x, y);
}
SIGS_API Tree sigLE(Tree x, Tree y)
{
    return sigBinOp(kLE, x, y);
}
SIGS_API Tree sigEQ(Tree x, Tree y)
{
    return sigBinOp(kEQ, x, y);
}
SIGS_API Tree sigNE(Tree x, Tree y)
{
    return sigBinOp(kNE, x, y);
}

/*****************************************************************************
                             User Interface Elements
*****************************************************************************/

SIGS_API Tree sigButton(Tree lbl)
{
    return A().Button(lbl);
}
bool isSigButton(Tree s)
{
    return pat::Button(pat::any()).match(s);
}
SIGS_API bool isSigButton(Tree s, Tree& lbl)
{
    return pat::Button(pat::var(lbl)).match(s);
}

SIGS_API Tree sigCheckbox(Tree lbl)
{
    return A().Checkbox(lbl);
}
bool isSigCheckbox(Tree s)
{
    return pat::Checkbox(pat::any()).match(s);
}
SIGS_API bool isSigCheckbox(Tree s, Tree& lbl)
{
    return pat::Checkbox(pat::var(lbl)).match(s);
}

SIGS_API Tree sigWaveform(const tvec& wf)
{
    return A().Waveform(std::vector<Tree>(wf.begin(), wf.end()));
}
SIGS_API bool isSigWaveform(Tree s)
{
    return pat::Waveform().match(s);
}

SIGS_API Tree sigHSlider(Tree lbl, Tree init, Tree min, Tree max, Tree step)
{
    return A().HSlider(lbl, init, min, max, step);
}
bool isSigHSlider(Tree s)
{
    return pat::HSlider(pat::any(), pat::any(), pat::any(), pat::any(), pat::any()).match(s);
}

SIGS_API bool isSigHSlider(Tree s, Tree& lbl, Tree& init, Tree& min, Tree& max, Tree& step)
{
    return pat::HSlider(pat::var(lbl), pat::var(init), pat::var(min), pat::var(max),
                        pat::var(step))
        .match(s);
}

SIGS_API Tree sigVSlider(Tree lbl, Tree init, Tree min, Tree max, Tree step)
{
    return A().VSlider(lbl, init, min, max, step);
}
bool isSigVSlider(Tree s)
{
    return pat::VSlider(pat::any(), pat::any(), pat::any(), pat::any(), pat::any()).match(s);
}

SIGS_API bool isSigVSlider(Tree s, Tree& lbl, Tree& init, Tree& min, Tree& max, Tree& step)
{
    return pat::VSlider(pat::var(lbl), pat::var(init), pat::var(min), pat::var(max),
                        pat::var(step))
        .match(s);
}

SIGS_API Tree sigNumEntry(Tree lbl, Tree init, Tree min, Tree max, Tree step)
{
    return A().NumEntry(lbl, init, min, max, step);
}
bool isSigNumEntry(Tree s)
{
    return pat::NumEntry(pat::any(), pat::any(), pat::any(), pat::any(), pat::any()).match(s);
}

SIGS_API bool isSigNumEntry(Tree s, Tree& lbl, Tree& init, Tree& min, Tree& max, Tree& step)
{
    return pat::NumEntry(pat::var(lbl), pat::var(init), pat::var(min), pat::var(max),
                         pat::var(step))
        .match(s);
}

// Output elements

SIGS_API Tree sigHBargraph(Tree lbl, Tree min, Tree max, Tree x)
{
    return A().HBargraph(lbl, min, max, x);
}
bool isSigHBargraph(Tree s)
{
    return pat::HBargraph(pat::any(), pat::any(), pat::any(), pat::any()).match(s);
}
SIGS_API bool isSigHBargraph(Tree s, Tree& lbl, Tree& min, Tree& max, Tree& x)
{
    return pat::HBargraph(pat::var(lbl), pat::var(min), pat::var(max), pat::var(x)).match(s);
}

SIGS_API Tree sigVBargraph(Tree lbl, Tree min, Tree max, Tree x)
{
    return A().VBargraph(lbl, min, max, x);
}
bool isSigVBargraph(Tree s)
{
    return pat::VBargraph(pat::any(), pat::any(), pat::any(), pat::any()).match(s);
}
SIGS_API bool isSigVBargraph(Tree s, Tree& lbl, Tree& min, Tree& max, Tree& x)
{
    return pat::VBargraph(pat::var(lbl), pat::var(min), pat::var(max), pat::var(x)).match(s);
}

bool isUIInputItem(Tree sig)
{
    Tree label, c, x, y, z;
    if (isSigButton(sig, label)) {
        return true;
    }
    if (isSigCheckbox(sig, label)) {
        return true;
    }
    if (isSigVSlider(sig, label, c, x, y, z)) {
        return true;
    }
    if (isSigHSlider(sig, label, c, x, y, z)) {
        return true;
    }
    if (isSigNumEntry(sig, label, c, x, y, z)) {
        return true;
    }
    if (isSigSoundfile(sig, label)) {
        return true;
    }
    return false;
}

bool isUIOutputItem(Tree sig)
{
    Tree label, x, y, z;
    if (isSigVBargraph(sig, label, x, y, z)) {
        return true;
    }
    if (isSigHBargraph(sig, label, x, y, z)) {
        return true;
    }
    return false;
}

Tree sigAttach(Tree t0, Tree t1)
{
    return A().Attach(t0, t1);
}
SIGS_API bool isSigAttach(Tree t, Tree& t0, Tree& t1)
{
    return pat::Attach(pat::var(t0), pat::var(t1)).match(t);
}

Tree sigEnable(Tree t0, Tree t1)
{
    return A().Enable(t0, t1);
}
SIGS_API bool isSigEnable(Tree t, Tree& t0, Tree& t1)
{
    return pat::Enable(pat::var(t0), pat::var(t1)).match(t);
}

Tree sigControl(Tree t0, Tree t1)
{
    return A().Control(t0, t1);
}
SIGS_API bool isSigControl(Tree t, Tree& t0, Tree& t1)
{
    return pat::Control(pat::var(t0), pat::var(t1)).match(t);
}

// Extended math functions : NORMALIZING constructors, folding through the
// primitive itself (computeSigOutput). This is API semantics -- the initial
// algebra's per-operation methods build the raw nodes instead.

static Tree sigExtended1(Tree sig, Tree x)
{
    tvec args;
    args.push_back(x);
    return ((xtended*)getUserData(sig))->computeSigOutput(args);
}

static Tree sigExtended2(Tree sig, Tree x, Tree y)
{
    tvec args;
    args.push_back(x);
    args.push_back(y);
    return ((xtended*)getUserData(sig))->computeSigOutput(args);
}

SIGS_API Tree sigAbs(Tree x)
{
    return sigExtended1(sigs::g.gAbsPrim->box(), x);
}

SIGS_API Tree sigAcos(Tree x)
{
    return sigExtended1(sigs::g.gAcosPrim->box(), x);
}

SIGS_API Tree sigTan(Tree x)
{
    return sigExtended1(sigs::g.gTanPrim->box(), x);
}

SIGS_API Tree sigSqrt(Tree x)
{
    return sigExtended1(sigs::g.gSqrtPrim->box(), x);
}

SIGS_API Tree sigSin(Tree x)
{
    return sigExtended1(sigs::g.gSinPrim->box(), x);
}

SIGS_API Tree sigRint(Tree x)
{
    return sigExtended1(sigs::g.gRintPrim->box(), x);
}

SIGS_API Tree sigRemainder(Tree x, Tree y)
{
    return sigExtended2(sigs::g.gRemainderPrim->box(), x, y);
}

SIGS_API Tree sigPow(Tree x, Tree y)
{
    return sigExtended2(sigs::g.gPowPrim->box(), x, y);
}

SIGS_API Tree sigMin(Tree x, Tree y)
{
    return sigExtended2(sigs::g.gMinPrim->box(), x, y);
}

SIGS_API Tree sigMax(Tree x, Tree y)
{
    return sigExtended2(sigs::g.gMaxPrim->box(), x, y);
}

SIGS_API Tree sigLog(Tree x)
{
    return sigExtended1(sigs::g.gLogPrim->box(), x);
}

SIGS_API Tree sigLog10(Tree x)
{
    return sigExtended1(sigs::g.gLog10Prim->box(), x);
}

SIGS_API Tree sigFmod(Tree x, Tree y)
{
    return sigExtended2(sigs::g.gFmodPrim->box(), x, y);
}

SIGS_API Tree sigFloor(Tree x)
{
    return sigExtended1(sigs::g.gFloorPrim->box(), x);
}

SIGS_API Tree sigExp(Tree x)
{
    return sigExtended1(sigs::g.gExpPrim->box(), x);
}

SIGS_API Tree sigExp10(Tree x)
{
    return sigExtended1(sigs::g.gExp10Prim->box(), x);
}

SIGS_API Tree sigCos(Tree x)
{
    return sigExtended1(sigs::g.gCosPrim->box(), x);
}

SIGS_API Tree sigCeil(Tree x)
{
    return sigExtended1(sigs::g.gCeilPrim->box(), x);
}

SIGS_API Tree sigAtan(Tree x)
{
    return sigExtended1(sigs::g.gAtanPrim->box(), x);
}

SIGS_API Tree sigAtan2(Tree x, Tree y)
{
    return sigExtended2(sigs::g.gAtan2Prim->box(), x, y);
}

SIGS_API Tree sigAsin(Tree x)
{
    return sigExtended1(sigs::g.gAsinPrim->box(), x);
}

bool sameMagnitude(Tree a, Tree b)
{
    return sameMagnitude(a->node(), b->node());
}

Tree addNums(Tree a, Tree b)
{
    Tree r = tree(addNode(a->node(), b->node()));
    // cerr.flags(ios::showpoint); cerr << "addNums " << *a << "+" << *b << " -> " << *r << endl;
    return r;
}

Tree subNums(Tree a, Tree b)
{
    Tree r = tree(subNode(a->node(), b->node()));
    // cerr.flags(ios::showpoint); cerr << "subNums " << *a << "-" << *b << " -> " << *r << endl;
    return r;
}

Tree mulNums(Tree a, Tree b)
{
    Tree r = tree(mulNode(a->node(), b->node()));
    // cerr.flags(ios::showpoint); cerr << "mulNums " << *a << "*" << *b << " -> " << *r << endl;
    return r;
}

// Tree divNums(Tree a, Tree b)
//{
//	Tree r = tree(divNode(a->node(),b->node()));
//	//cerr.flags(ios::showpoint); cerr << "divNums " << *a << "/" << *b << " -> " << *r << endl;
//	return r;
//}

Tree divExtendedNums(Tree a, Tree b)
{
    // cerr.flags(ios::showpoint); cerr << "divExtendeNums " << *a << "/" << *b << " -> " << endl;
    Tree r = tree(divExtendedNode(a->node(), b->node()));
    // cerr.flags(ios::showpoint); cerr << "divExtendeNums " << *a << "/" << *b << " -> " << *r <<
    // endl;
    return r;
}

Tree minusNum(Tree a)
{
    Tree r = tree(minusNode(a->node()));
    // cerr.flags(ios::showpoint); cerr << "minusNum " << *a << " -> " << *r << endl;
    return r;
}

Tree inverseNum(Tree a)
{
    Tree r = tree(inverseNode(a->node()));
    // cerr.flags(ios::showpoint); cerr << "inverseNum " << *a << " -> " << *r << endl;
    return r;
}

bool isSigAdd(Tree a, Tree& x, Tree& y)
{
    return pat::Add(pat::var(x), pat::var(y)).match(a);
}

bool isSigMul(Tree a, Tree& x, Tree& y)
{
    return pat::Mul(pat::var(x), pat::var(y)).match(a);
}

bool isSigSub(Tree a, Tree& x, Tree& y)
{
    return pat::Sub(pat::var(x), pat::var(y)).match(a);
}

bool isSigDiv(Tree a, Tree& x, Tree& y)
{
    return pat::Div(pat::var(x), pat::var(y)).match(a);
}

/*****************************************************************************
                             Soundfiles
*****************************************************************************/
/*
 A boxSoundfile(label,c) has 2 inputs and c+3 outputs:
 0   sigSoundfileLength(label, part):  the number of frames of the soundfile part (NK)
 1   sigSoundfileRate(label, part): the sampling rate encoded in the file (NK)
 2   sigSoundfileBuffer(label, c, part, ridx): the cth channel content (RK or RS)
*/
SIGS_API Tree sigSoundfile(Tree label)
{
    return A().SoundFile(label);
}
SIGS_API Tree sigSoundfileLength(Tree sf, Tree part)
{
    return A().SoundFileLength(sf, part);
}
SIGS_API Tree sigSoundfileRate(Tree sf, Tree part)
{
    return A().SoundFileRate(sf, part);
}
SIGS_API Tree sigSoundfileBuffer(Tree sf, Tree chan, Tree part, Tree ridx)
{
    return A().SoundFileBuffer(sf, chan, part, ridx);
}

SIGS_API bool isSigSoundfile(Tree s, Tree& label)
{
    return pat::SoundFile(pat::var(label)).match(s);
}
SIGS_API bool isSigSoundfileLength(Tree s, Tree& sf, Tree& part)
{
    return pat::SoundFileLength(pat::var(sf), pat::var(part)).match(s);
}
SIGS_API bool isSigSoundfileRate(Tree s, Tree& sf, Tree& part)
{
    return pat::SoundFileRate(pat::var(sf), pat::var(part)).match(s);
}
SIGS_API bool isSigSoundfileBuffer(Tree s, Tree& sf, Tree& chan, Tree& part, Tree& ridx)
{
    return pat::SoundFileBuffer(pat::var(sf), pat::var(chan), pat::var(part), pat::var(ridx))
        .match(s);
}

// for FPGA Retiming

SIGS_API Tree sigRegister(int n, Tree s)
{
    return A().Register(n, s);
}

SIGS_API bool isSigRegister(Tree s, int* n, Tree& x)
{
    Tree y = nullptr;
    return pat::Register(pat::var(y), pat::var(x)).match(s) && isInt(y->node(), n);
}


/**
 * Test if exp is very simple that is it
 * can't be considered a real component
 * @param exp the signal we want to test
 * @return true if it a very simple signal
 */
bool verySimple(Tree exp)
{
    int    i;
    double r;
    Tree   type, name, file;

    return isSigInt(exp, &i) || isSigReal(exp, &r) || isSigInput(exp, &i) ||
           isSigFConst(exp, type, name, file);
}

/*****************************************************************************
 *                          sigList2vectInt
 *****************************************************************************/
/**
 * Convert a list of signals (representing numbers) into a vector of ints
 * the result is true if the conversion was possible.
 */
bool sigList2vecInt(Tree ls, vector<int>& v)
{
    int    i;
    double x;

    while (!isNil(ls)) {
        Tree s = hd(ls);
        ls     = tl(ls);
        if (isSigInt(s, &i)) {
            v.push_back(i);
        } else if (isSigReal(s, &x)) {
            v.push_back(int(x));
        } else {
            return false;
        }
    }
    return true;
}

/**
 * Convert an stl vector of signals into a tree list of signals
 */
Tree listConvert(const siglist& a)
{
    int  n = (int)a.size();
    Tree t = ::nil();

    while (n--) {
        t = cons(a[n], t);
    }
    return t;
}

/*
 * Convert a Tree in stl vector of signals
 */
siglist treeConvert(Tree t)
{
    siglist res;
    while (!isNil(t)) {
        res.push_back(hd(t));
        t = tl(t);
    }
    return res;
}

/*****************************************************************************
                             FIR and IIR
*****************************************************************************/

// FIR

SIGS_API Tree sigFIR(const tvec& sigcoefs)
{
    // Construction invariant : a FIR with real taps (delays) is audio rate
    // by its local mask whatever its source -- FIR[1, 0, 1] is 1@1. The
    // one-coefficient form FIR[x, c0] is a plain product with no mask : it
    // is only truthful when x itself is audio rate, which the reveal rules
    // guarantee and this assert makes contractual.
    TLIB_ASSERT(sigcoefs.size() > 2 ||
                (sigcoefs.size() == 2 && sigs::isAudioRate(sigcoefs[0])));
    return tree(sigs::g.SIGFIR, sigcoefs);
}

SIGS_API bool isSigFIR(Tree s)
{
    return isTree(s, sigs::g.SIGFIR);
}

// temp(x) : a staging barrier -- semantically the identity, compiled by
// materializing x into a named temporary (see placeTemps.cpp for the
// placement policy). Two temp(x) of the same x are the same hash-consed
// node : one variable, several reads.
SIGS_API Tree sigTemp(Tree x)
{
    return tree(sigs::g.SIGTEMP, x);
}

SIGS_API bool isSigTemp(Tree s, Tree& x)
{
    return isTree(s, sigs::g.SIGTEMP, x);
}

SIGS_API bool isSigTemp(Tree s)
{
    return isTree(s, sigs::g.SIGTEMP);
}

SIGS_API bool isSigFIR(Tree s, Tree c0)
{
    return isTree(s, sigs::g.SIGFIR) && (s->branch(0) == c0);
}

SIGS_API bool isSigFIR(Tree s, tvec& sigcoefs)
{
    if (isTree(s, sigs::g.SIGFIR)) {
        sigcoefs = s->branches();
        return true;
    } else {
        return false;
    }
}

// IIR

SIGS_API Tree sigIIR(const tvec& sigcoefs)
{
    return tree(sigs::g.SIGIIR, sigcoefs);
}

SIGS_API bool isSigIIR(Tree s)
{
    return isTree(s, sigs::g.SIGIIR);
}

SIGS_API bool isSigIIR(Tree s, Tree c0)
{
    return isTree(s, sigs::g.SIGIIR) && (s->branch(0) == c0);
}

SIGS_API bool isSigIIR(Tree s, tvec& sigcoefs)
{
    if (isTree(s, sigs::g.SIGIIR)) {
        sigcoefs = s->branches();
        return true;
    } else {
        return false;
    }
}

// SUM

// spec LA-FORME-NOYAU v6 : the typed kernel core

SIGS_API Tree sigKForm(const tvec& coefs)
{
    // anchored by construction : first and last coefficients are not the
    // literal zero (syntactic anchor -- an init-time expression that
    // happens to be zero cannot be detected here)
    TLIB_ASSERT(!coefs.empty());
    TLIB_ASSERT(!isZero(coefs.front()) && !isZero(coefs.back()));
    return tree(sigs::g.SIGKFORM, coefs);
}

SIGS_API bool isSigKForm(Tree s)
{
    return isTree(s, sigs::g.SIGKFORM);
}

SIGS_API bool isSigKForm(Tree s, tvec& coefs)
{
    if (isTree(s, sigs::g.SIGKFORM)) {
        coefs = s->branches();
        return true;
    }
    return false;
}

SIGS_API Tree sigDense(Tree src, Tree kform)
{
    TLIB_ASSERT(isSigKForm(kform));
    return tree(sigs::g.SIGDENSE, src, kform);
}

SIGS_API bool isSigDense(Tree s)
{
    return isTree(s, sigs::g.SIGDENSE);
}

SIGS_API bool isSigDense(Tree s, Tree& src, Tree& kform)
{
    if (isTree(s, sigs::g.SIGDENSE)) {
        src   = s->branch(0);
        kform = s->branch(1);
        return true;
    }
    return false;
}

SIGS_API Tree sigLtvFIR(const tvec& sigcoefs)
{
    TLIB_ASSERT(sigcoefs.size() >= 2);
    return tree(sigs::g.SIGLTVFIR, sigcoefs);
}

SIGS_API bool isSigLtvFIR(Tree s)
{
    return isTree(s, sigs::g.SIGLTVFIR);
}

SIGS_API bool isSigLtvFIR(Tree s, tvec& sigcoefs)
{
    if (isTree(s, sigs::g.SIGLTVFIR)) {
        sigcoefs = s->branches();
        return true;
    }
    return false;
}

SIGS_API Tree sigSum(const tvec& sigsubs)
{
    return tree(sigs::g.SIGSUM, sigsubs);
}

SIGS_API bool isSigSum(Tree s)
{
    return isTree(s, sigs::g.SIGSUM);
}

SIGS_API bool isSigSum(Tree s, tvec& sigsubs)
{
    if (isTree(s, sigs::g.SIGSUM)) {
        sigsubs = s->branches();
        return true;
    } else {
        return false;
    }
}
