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

#include <float.h>
#include <vector>

#include "sigs-state.hh"
#include "ppsig.hh"
#include "signals.hh"
#include "xtended.hh"

using namespace std;

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
    return tree(i);
}
SIGS_API bool isSigInt(Tree t, int* i)
{
    return isInt(t->node(), i);
}

Tree sigInt64(int64_t i)
{
    return tree(i);
}
bool isSigInt64(Tree t, int64_t* i)
{
    return isInt64(t->node(), i);
}

SIGS_API Tree sigReal(double r)
{
    return tree(r);
}
SIGS_API bool isSigReal(Tree t, double* r)
{
    return isDouble(t->node(), r);
}

SIGS_API Tree sigInput(int i)
{
    return tree(sigs::g.SIGINPUT, tree(i));
}

SIGS_API bool isSigInput(Tree t, int* i)
{
    Tree x;
    return isTree(t, sigs::g.SIGINPUT, x) && isInt(x->node(), i);
}

Tree sigOutput(int i, Tree t0)
{
    return tree(sigs::g.SIGOUTPUT, tree(i), t0);
}
SIGS_API bool isSigOutput(Tree t, int* i, Tree& t0)
{
    Tree x;
    return isTree(t, sigs::g.SIGOUTPUT, x, t0) && isInt(x->node(), i);
}

Tree sigDelay0(Tree t0)
{
    return sigDelay(t0, sigInt(0));
}

SIGS_API Tree sigDelay1(Tree t0)
{
    return tree(sigs::g.SIGDELAY1, t0);
}
SIGS_API bool isSigDelay1(Tree t, Tree& t0)
{
    return isTree(t, sigs::g.SIGDELAY1, t0);
}

SIGS_API Tree sigDelay(Tree t0, Tree t1)
{
    return tree(sigs::g.SIGDELAY, t0, t1);
}
SIGS_API bool isSigDelay(Tree t, Tree& t0, Tree& t1)
{
    return isTree(t, sigs::g.SIGDELAY, t0, t1);
}

Tree sigPrefix(Tree t0, Tree t1)
{
    return tree(sigs::g.SIGPREFIX, t0, t1);
}
SIGS_API bool isSigPrefix(Tree t, Tree& t0, Tree& t1)
{
    return isTree(t, sigs::g.SIGPREFIX, t0, t1);
}

// Read only and read write tables

Tree sigRDTbl(Tree tbl, Tree ri)
{
    return tree(sigs::g.SIGRDTBL, tbl, ri);
}
SIGS_API bool isSigRDTbl(Tree s, Tree& tbl, Tree& ri)
{
    return isTree(s, sigs::g.SIGRDTBL, tbl, ri);
}

Tree sigWRTbl(Tree size, Tree gen, Tree wi, Tree ws)
{
    return tree(sigs::g.SIGWRTBL, size, gen, wi, ws);
}
SIGS_API bool isSigWRTbl(Tree u, Tree& size, Tree& gen, Tree& wi, Tree& ws)
{
    return isTree(u, sigs::g.SIGWRTBL, size, gen, wi, ws);
}

SIGS_API bool isSigWRTbl(Tree u, Tree& size, Tree& gen)
{
    Tree wi, ws;
    return isTree(u, sigs::g.SIGWRTBL, size, gen, wi, ws) && (wi == ::nil());
}

// Signal used to generate the initial content of a table

Tree sigGen(Tree s)
{
    return tree(sigs::g.SIGGEN, s);
}
SIGS_API bool isSigGen(Tree t, Tree& x)
{
    return isTree(t, sigs::g.SIGGEN, x);
}
bool isSigGen(Tree t)
{
    return t->node() == Node(sigs::g.SIGGEN);
}

// Documentator Tables : special version of tables only for documentation purposes

Tree sigDocConstantTbl(Tree n, Tree sig)
{
    return tree(sigs::g.SIGDOCONSTANTTBL, n, sig);
}
SIGS_API bool isSigDocConstantTbl(Tree t, Tree& n, Tree& sig)
{
    return isTree(t, sigs::g.SIGDOCONSTANTTBL, n, sig);
}

Tree sigDocWriteTbl(Tree n, Tree sig, Tree widx, Tree wsig)
{
    return tree(sigs::g.SIGDOCWRITETBL, n, sig, widx, wsig);
}
SIGS_API bool isSigDocWriteTbl(Tree t, Tree& n, Tree& sig, Tree& widx, Tree& wsig)
{
    return isTree(t, sigs::g.SIGDOCWRITETBL, n, sig, widx, wsig);
}

Tree sigDocAccessTbl(Tree tbl, Tree ridx)
{
    return tree(sigs::g.SIGDOCACCESSTBL, tbl, ridx);
}
SIGS_API bool isSigDocAccessTbl(Tree t, Tree& tbl, Tree& ridx)
{
    return isTree(t, sigs::g.SIGDOCACCESSTBL, tbl, ridx);
}

// Select on signal among severals

SIGS_API Tree sigSelect2(Tree selector, Tree s1, Tree s2)
{
    return tree(sigs::g.SIGSELECT2, selector, s1, s2);
}
SIGS_API bool isSigSelect2(Tree t, Tree& selector, Tree& s1, Tree& s2)
{
    return isTree(t, sigs::g.SIGSELECT2, selector, s1, s2);
}

// "select3" expressed with "select2"
SIGS_API Tree sigSelect3(Tree selector, Tree s1, Tree s2, Tree s3)
{
    return sigSelect2(sigBinOp(kEQ, selector, sigInt(0)),
                      sigSelect2(sigBinOp(kEQ, selector, sigInt(1)), s3, s2), s1);
}

Tree sigAssertBounds(Tree s1, Tree s2, Tree s3)
{
    return tree(sigs::g.SIGASSERTBOUNDS, s1, s2, s3);
}

SIGS_API bool isSigAssertBounds(Tree t, Tree& s1, Tree& s2, Tree& s3)
{
    return isTree(t, sigs::g.SIGASSERTBOUNDS, s1, s2, s3);
}

Tree sigHighest(Tree s)
{
    return tree(sigs::g.SIGHIGHEST, s);
}

SIGS_API bool isSigHighest(Tree t, Tree& s)
{
    return isTree(t, sigs::g.SIGHIGHEST, s);
}

Tree sigLowest(Tree s)
{
    return tree(sigs::g.SIGLOWEST, s);
}

SIGS_API bool isSigLowest(Tree t, Tree& s)
{
    return isTree(t, sigs::g.SIGLOWEST, s);
}

// Arithmetical operations

SIGS_API Tree sigBinOp(SOperator op, Tree x, Tree y)
{
    return sigBinOp(int(op), x, y);
}

SIGS_API Tree sigBinOp(int op, Tree x, Tree y)
{
    return tree(sigs::g.SIGBINOP, tree(op), x, y);
}

SIGS_API bool isSigBinOp(Tree s, int* op, Tree& x, Tree& y)
{
    Tree t;
    return isTree(s, sigs::g.SIGBINOP, t, x, y) && isInt(t->node(), op);
}

// Foreign Functions

Tree sigFFun(Tree ff, Tree largs)
{
    return tree(sigs::g.SIGFFUN, ff, largs);
}
SIGS_API bool isSigFFun(Tree s, Tree& ff, Tree& largs)
{
    return isTree(s, sigs::g.SIGFFUN, ff, largs);
}

SIGS_API Tree sigFConst(Tree type, Tree name, Tree file)
{
    return tree(sigs::g.SIGFCONST, type, name, file);
}
bool isSigFConst(Tree s)
{
    Tree t, n, f;
    return isTree(s, sigs::g.SIGFCONST, t, n, f);
}
SIGS_API bool isSigFConst(Tree s, Tree& type, Tree& name, Tree& file)
{
    return isTree(s, sigs::g.SIGFCONST, type, name, file);
}

SIGS_API Tree sigFVar(Tree type, Tree name, Tree file)
{
    return tree(sigs::g.SIGFVAR, type, name, file);
}
bool isSigFVar(Tree s)
{
    Tree t, n, f;
    return isTree(s, sigs::g.SIGFVAR, t, n, f);
}
SIGS_API bool isSigFVar(Tree s, Tree& type, Tree& name, Tree& file)
{
    return isTree(s, sigs::g.SIGFVAR, type, name, file);
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
    Node   n = t->node();
    int    i;
    double x;

    if (isInt(n, &i)) {
        return t;
    }
    if (isDouble(n, &x)) {
        return tree(int(x));
    }

    return tree(sigs::g.SIGINTCAST, t);
}

Tree sigBitCast(Tree t)
{
    return tree(sigs::g.SIGBITCAST, t);
}

SIGS_API Tree sigFloatCast(Tree t)
{
    Node   n = t->node();
    int    i;
    double x;

    if (isInt(n, &i)) {
        return tree(double(i));
    }
    if (isDouble(n, &x)) {
        return t;
    }

    return tree(sigs::g.SIGFLOATCAST, t);
}

bool isSigIntCast(Tree t)
{
    Tree x;
    return isTree(t, sigs::g.SIGINTCAST, x);
}
SIGS_API bool isSigIntCast(Tree t, Tree& x)
{
    return isTree(t, sigs::g.SIGINTCAST, x);
}

bool isSigBitCast(Tree t)
{
    Tree x;
    return isTree(t, sigs::g.SIGBITCAST, x);
}
bool isSigBitCast(Tree t, Tree& x)
{
    return isTree(t, sigs::g.SIGBITCAST, x);
}

bool isSigFloatCast(Tree t)
{
    Tree x;
    return isTree(t, sigs::g.SIGFLOATCAST, x);
}
SIGS_API bool isSigFloatCast(Tree t, Tree& x)
{
    return isTree(t, sigs::g.SIGFLOATCAST, x);
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
    return tree(sigs::g.SIGBUTTON, lbl);
}
bool isSigButton(Tree s)
{
    Tree lbl;
    return isTree(s, sigs::g.SIGBUTTON, lbl);
}
SIGS_API bool isSigButton(Tree s, Tree& lbl)
{
    return isTree(s, sigs::g.SIGBUTTON, lbl);
}

SIGS_API Tree sigCheckbox(Tree lbl)
{
    return tree(sigs::g.SIGCHECKBOX, lbl);
}
bool isSigCheckbox(Tree s)
{
    Tree lbl;
    return isTree(s, sigs::g.SIGCHECKBOX, lbl);
}
SIGS_API bool isSigCheckbox(Tree s, Tree& lbl)
{
    return isTree(s, sigs::g.SIGCHECKBOX, lbl);
}

SIGS_API Tree sigWaveform(const tvec& wf)
{
    return tree(sigs::g.SIGWAVEFORM, wf);
}
SIGS_API bool isSigWaveform(Tree s)
{
    return isTree(s, sigs::g.SIGWAVEFORM);
}

SIGS_API Tree sigHSlider(Tree lbl, Tree init, Tree min, Tree max, Tree step)
{
    return tree(sigs::g.SIGHSLIDER, lbl, list4(init, min, max, step));
}
bool isSigHSlider(Tree s)
{
    Tree lbl, params;
    return isTree(s, sigs::g.SIGHSLIDER, lbl, params);
}

SIGS_API bool isSigHSlider(Tree s, Tree& lbl, Tree& init, Tree& min, Tree& max, Tree& step)
{
    Tree params;
    if (isTree(s, sigs::g.SIGHSLIDER, lbl, params)) {
        init = nth(params, 0);
        min  = nth(params, 1);
        max  = nth(params, 2);
        step = nth(params, 3);
        return true;
    } else {
        return false;
    }
}

SIGS_API Tree sigVSlider(Tree lbl, Tree init, Tree min, Tree max, Tree step)
{
    return tree(sigs::g.SIGVSLIDER, lbl, list4(init, min, max, step));
}
bool isSigVSlider(Tree s)
{
    Tree lbl, params;
    return isTree(s, sigs::g.SIGVSLIDER, lbl, params);
}

SIGS_API bool isSigVSlider(Tree s, Tree& lbl, Tree& init, Tree& min, Tree& max, Tree& step)
{
    Tree params;
    if (isTree(s, sigs::g.SIGVSLIDER, lbl, params)) {
        init = nth(params, 0);
        min  = nth(params, 1);
        max  = nth(params, 2);
        step = nth(params, 3);
        return true;
    } else {
        return false;
    }
}

SIGS_API Tree sigNumEntry(Tree lbl, Tree init, Tree min, Tree max, Tree step)
{
    return tree(sigs::g.SIGNUMENTRY, lbl, list4(init, min, max, step));
}
bool isSigNumEntry(Tree s)
{
    Tree lbl, params;
    return isTree(s, sigs::g.SIGNUMENTRY, lbl, params);
}

SIGS_API bool isSigNumEntry(Tree s, Tree& lbl, Tree& init, Tree& min, Tree& max, Tree& step)
{
    Tree params;
    if (isTree(s, sigs::g.SIGNUMENTRY, lbl, params)) {
        init = nth(params, 0);
        min  = nth(params, 1);
        max  = nth(params, 2);
        step = nth(params, 3);
        return true;
    } else {
        return false;
    }
}

// Output elements

SIGS_API Tree sigHBargraph(Tree lbl, Tree min, Tree max, Tree x)
{
    return tree(sigs::g.SIGHBARGRAPH, lbl, min, max, x);
}
bool isSigHBargraph(Tree s)
{
    Tree lbl, min, max, x;
    return isTree(s, sigs::g.SIGHBARGRAPH, lbl, min, max, x);
}
SIGS_API bool isSigHBargraph(Tree s, Tree& lbl, Tree& min, Tree& max, Tree& x)
{
    return isTree(s, sigs::g.SIGHBARGRAPH, lbl, min, max, x);
}

SIGS_API Tree sigVBargraph(Tree lbl, Tree min, Tree max, Tree x)
{
    return tree(sigs::g.SIGVBARGRAPH, lbl, min, max, x);
}
bool isSigVBargraph(Tree s)
{
    Tree lbl, min, max, x;
    return isTree(s, sigs::g.SIGVBARGRAPH, lbl, min, max, x);
}
SIGS_API bool isSigVBargraph(Tree s, Tree& lbl, Tree& min, Tree& max, Tree& x)
{
    return isTree(s, sigs::g.SIGVBARGRAPH, lbl, min, max, x);
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
    return tree(sigs::g.SIGATTACH, t0, t1);
}
SIGS_API bool isSigAttach(Tree t, Tree& t0, Tree& t1)
{
    return isTree(t, sigs::g.SIGATTACH, t0, t1);
}

Tree sigEnable(Tree t0, Tree t1)
{
    return tree(sigs::g.SIGENABLE, t0, t1);
}
SIGS_API bool isSigEnable(Tree t, Tree& t0, Tree& t1)
{
    return isTree(t, sigs::g.SIGENABLE, t0, t1);
}

Tree sigControl(Tree t0, Tree t1)
{
    return tree(sigs::g.SIGCONTROL, t0, t1);
}
SIGS_API bool isSigControl(Tree t, Tree& t0, Tree& t1)
{
    return isTree(t, sigs::g.SIGCONTROL, t0, t1);
}

// Extended math functions

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
    int op;
    return isSigBinOp(a, &op, x, y) && (op == kAdd);
}

bool isSigMul(Tree a, Tree& x, Tree& y)
{
    int op;
    return isSigBinOp(a, &op, x, y) && (op == kMul);
}

bool isSigSub(Tree a, Tree& x, Tree& y)
{
    int op;
    return isSigBinOp(a, &op, x, y) && (op == kSub);
}

bool isSigDiv(Tree a, Tree& x, Tree& y)
{
    int op;
    return isSigBinOp(a, &op, x, y) && (op == kDiv);
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
    return tree(sigs::g.SIGSOUNDFILE, label);
}
SIGS_API Tree sigSoundfileLength(Tree sf, Tree part)
{
    return tree(sigs::g.SIGSOUNDFILELENGTH, sf, part);
}
SIGS_API Tree sigSoundfileRate(Tree sf, Tree part)
{
    return tree(sigs::g.SIGSOUNDFILERATE, sf, part);
}
SIGS_API Tree sigSoundfileBuffer(Tree sf, Tree chan, Tree part, Tree ridx)
{
    return tree(sigs::g.SIGSOUNDFILEBUFFER, sf, chan, part, ridx);
}

SIGS_API bool isSigSoundfile(Tree s, Tree& label)
{
    return isTree(s, sigs::g.SIGSOUNDFILE, label);
}
SIGS_API bool isSigSoundfileLength(Tree s, Tree& sf, Tree& part)
{
    return isTree(s, sigs::g.SIGSOUNDFILELENGTH, sf, part);
}
SIGS_API bool isSigSoundfileRate(Tree s, Tree& sf, Tree& part)
{
    return isTree(s, sigs::g.SIGSOUNDFILERATE, sf, part);
}
SIGS_API bool isSigSoundfileBuffer(Tree s, Tree& sf, Tree& chan, Tree& part, Tree& ridx)
{
    return isTree(s, sigs::g.SIGSOUNDFILEBUFFER, sf, chan, part, ridx);
}

// for FPGA Retiming

SIGS_API Tree sigRegister(int n, Tree s)
{
    return tree(sigs::g.SIGREGISTER, tree(n), s);
}

SIGS_API bool isSigRegister(Tree s, int* n, Tree& x)
{
    Tree y;
    return isTree(s, sigs::g.SIGREGISTER, y, x) && isInt(y->node(), n);
}

/*****************************************************************************
                             Matrix extension
*****************************************************************************/

// A tuple of signals is basically a list of signals.
// mode = 0 means normal, mode = 1 means blocked
Tree sigTuple(int mode, Tree ls)
{
    return tree(sigs::g.SIGTUPLE, tree(mode), ls);
}
bool isSigTuple(Tree s, int* mode, Tree& ls)
{
    Tree m;
    return isTree(s, sigs::g.SIGTUPLE, m, ls) && isInt(m->node(), mode);
}

// Access the components of a tuple.
// ts is tuple of signals, idx is a scalar signal between 0..n
Tree sigTupleAccess(Tree ts, Tree idx)
{
    return tree(sigs::g.SIGTUPLEACCESS, ts, idx);
}
bool isSigTupleAccess(Tree s, Tree& ts, Tree& idx)
{
    return isTree(s, sigs::g.SIGTUPLEACCESS, ts, idx);
}

// Create a tuple of signals
Tree sigCartesianProd(Tree s1, Tree s2)
{
    Tree l1, l2;
    int  m1, m2;

    if (isSigTuple(s1, &m1, l1) && (m1 == 0)) {
        // nothing to do
    } else {
        l1 = list1(s1);
    }

    if (isSigTuple(s2, &m2, l2) && (m2 == 0)) {
        // nothing to do
    } else {
        l2 = list1(s2);
    }

    return sigTuple(0, concat(l1, l2));
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
