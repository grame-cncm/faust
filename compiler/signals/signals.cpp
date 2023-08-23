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

#include "global.hh"
#include "ppsig.hh"
#include "signals.hh"
#include "xtended.hh"

using namespace std;

LIBFAUST_API Tree sigWriteReadTable(Tree size, Tree init, Tree widx, Tree wsig, Tree ridx)
{
    /*
     rwtable are parsed as boxPrim5, so do not have a special treatment in eval/propagate. So we do here:
     - the size argument is supposed to be known at compile time, it will be simplified in 'simplify'
     - rwtable is using a fully filled sigWRTbl signal
     */
    return sigRDTbl(sigWRTbl(size, sigGen(init), widx, wsig), ridx);
}

LIBFAUST_API Tree sigReadOnlyTable(Tree size, Tree init, Tree ridx)
{
    /*
     rtable are parsed as boxPrim3, so do not have a special treatment in eval/propagate. So we do here:
     - the size argument is supposed to be known at compile time, it will be simplified in 'simplify'
     - rdtable is using a 'degenerated' sigWRTbl signal with NIL 'wi' and 'ws' parameters
     */
    return sigRDTbl(sigWRTbl(size, sigGen(init)), ridx);
}

////////////////////////////////////////////////////////////////////////
/**
 * Signals
 */
///////////////////////////////////////////////////////////////////////

LIBFAUST_API Tree sigRem(Tree x, Tree y)
{
    if (isZero(y)) {
        stringstream error;
        error << "ERROR : % by 0 in " << ppsig(x, MAX_ERROR_SIZE) << " % " << ppsig(y, MAX_ERROR_SIZE) << endl;
        throw faustexception(error.str());
    }
    return sigBinOp(kRem, x, y);
}

LIBFAUST_API Tree sigInt(int i)
{
    return tree(i);
}
LIBFAUST_API bool isSigInt(Tree t, int* i)
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

LIBFAUST_API Tree sigReal(double r)
{
    return tree(r);
}
LIBFAUST_API bool isSigReal(Tree t, double* r)
{
    return isDouble(t->node(), r);
}

LIBFAUST_API Tree sigInput(int i)
{
    return tree(gGlobal->SIGINPUT, tree(i));
}

LIBFAUST_API bool isSigInput(Tree t, int* i)
{
    Tree x;
    return isTree(t, gGlobal->SIGINPUT, x) && isInt(x->node(), i);
}

Tree sigOutput(int i, Tree t0)
{
    return tree(gGlobal->SIGOUTPUT, tree(i), t0);
}
LIBFAUST_API bool isSigOutput(Tree t, int* i, Tree& t0)
{
    Tree x;
    return isTree(t, gGlobal->SIGOUTPUT, x, t0) && isInt(x->node(), i);
}

Tree sigDelay0(Tree t0)
{
    return sigDelay(t0, sigInt(0));
}

LIBFAUST_API Tree sigDelay1(Tree t0)
{
    return tree(gGlobal->SIGDELAY1, t0);
}
LIBFAUST_API bool isSigDelay1(Tree t, Tree& t0)
{
    return isTree(t, gGlobal->SIGDELAY1, t0);
}

LIBFAUST_API Tree sigDelay(Tree t0, Tree t1)
{
    return tree(gGlobal->SIGDELAY, t0, t1);
}
LIBFAUST_API bool isSigDelay(Tree t, Tree& t0, Tree& t1)
{
    return isTree(t, gGlobal->SIGDELAY, t0, t1);
}

Tree sigPrefix(Tree t0, Tree t1)
{
    return tree(gGlobal->SIGPREFIX, t0, t1);
}
LIBFAUST_API bool isSigPrefix(Tree t, Tree& t0, Tree& t1)
{
    return isTree(t, gGlobal->SIGPREFIX, t0, t1);
}

// Read only and read write tables

Tree sigRDTbl(Tree tbl, Tree ri)
{
    return tree(gGlobal->SIGRDTBL, tbl, ri);
}
LIBFAUST_API bool isSigRDTbl(Tree s, Tree& tbl, Tree& ri)
{
    return isTree(s, gGlobal->SIGRDTBL, tbl, ri);
}

Tree sigWRTbl(Tree size, Tree gen, Tree wi, Tree ws)
{
    return tree(gGlobal->SIGWRTBL, size, gen, wi, ws);
}
LIBFAUST_API bool isSigWRTbl(Tree u, Tree& size, Tree& gen, Tree& wi, Tree& ws)
{
    return isTree(u, gGlobal->SIGWRTBL, size, gen, wi, ws);
}

LIBFAUST_API bool isSigWRTbl(Tree u, Tree& size, Tree& gen)
{
    Tree wi, ws;
    return isTree(u, gGlobal->SIGWRTBL, size, gen, wi, ws) && (wi == gGlobal->nil);
}

// Signal used to generate the initial content of a table

Tree sigGen(Tree s)
{
    return tree(gGlobal->SIGGEN, s);
}
LIBFAUST_API bool isSigGen(Tree t, Tree& x)
{
    return isTree(t, gGlobal->SIGGEN, x);
}
bool isSigGen(Tree t)
{
    return t->node() == Node(gGlobal->SIGGEN);
}

// Documentator Tables : special version of tables only for documentation purposes

Tree sigDocConstantTbl(Tree n, Tree sig)
{
    return tree(gGlobal->SIGDOCONSTANTTBL, n, sig);
}
LIBFAUST_API bool isSigDocConstantTbl(Tree t, Tree& n, Tree& sig)
{
    return isTree(t, gGlobal->SIGDOCONSTANTTBL, n, sig);
}

Tree sigDocWriteTbl(Tree n, Tree sig, Tree widx, Tree wsig)
{
    return tree(gGlobal->SIGDOCWRITETBL, n, sig, widx, wsig);
}
LIBFAUST_API bool isSigDocWriteTbl(Tree t, Tree& n, Tree& sig, Tree& widx, Tree& wsig)
{
    return isTree(t, gGlobal->SIGDOCWRITETBL, n, sig, widx, wsig);
}

Tree sigDocAccessTbl(Tree tbl, Tree ridx)
{
    return tree(gGlobal->SIGDOCACCESSTBL, tbl, ridx);
}
LIBFAUST_API bool isSigDocAccessTbl(Tree t, Tree& tbl, Tree& ridx)
{
    return isTree(t, gGlobal->SIGDOCACCESSTBL, tbl, ridx);
}

// Select on signal among severals

LIBFAUST_API Tree sigSelect2(Tree selector, Tree s1, Tree s2)
{
    return tree(gGlobal->SIGSELECT2, selector, s1, s2);
}
LIBFAUST_API bool isSigSelect2(Tree t, Tree& selector, Tree& s1, Tree& s2)
{
    return isTree(t, gGlobal->SIGSELECT2, selector, s1, s2);
}

// "select3" expressed with "select2"
LIBFAUST_API Tree sigSelect3(Tree selector, Tree s1, Tree s2, Tree s3)
{
    return sigSelect2(sigBinOp(kEQ, selector, sigInt(0)), sigSelect2(sigBinOp(kEQ, selector, sigInt(1)), s3, s2), s1);
}

Tree sigAssertBounds(Tree s1, Tree s2, Tree s3)
{
    return tree(gGlobal->SIGASSERTBOUNDS, s1, s2, s3);
}

LIBFAUST_API bool isSigAssertBounds(Tree t, Tree& s1, Tree& s2, Tree& s3)
{
    return isTree(t, gGlobal->SIGASSERTBOUNDS, s1, s2, s3);
}

Tree sigHighest(Tree s)
{
    return tree(gGlobal->SIGHIGHEST, s);
}

LIBFAUST_API bool isSigHighest(Tree t, Tree& s)
{
    return isTree(t, gGlobal->SIGHIGHEST, s);
}

Tree sigLowest(Tree s)
{
    return tree(gGlobal->SIGLOWEST, s);
}

LIBFAUST_API bool isSigLowest(Tree t, Tree& s)
{
    return isTree(t, gGlobal->SIGLOWEST, s);
}

// Arithmetical operations

LIBFAUST_API Tree sigBinOp(SOperator op, Tree x, Tree y)
{
    return sigBinOp(int(op), x, y);
}

LIBFAUST_API Tree sigBinOp(int op, Tree x, Tree y)
{
    return tree(gGlobal->SIGBINOP, tree(op), x, y);
}

LIBFAUST_API bool isSigBinOp(Tree s, int* op, Tree& x, Tree& y)
{
    Tree t;
    return isTree(s, gGlobal->SIGBINOP, t, x, y) && isInt(t->node(), op);
}

// Foreign Functions

Tree sigFFun(Tree ff, Tree largs)
{
    return tree(gGlobal->SIGFFUN, ff, largs);
}
LIBFAUST_API bool isSigFFun(Tree s, Tree& ff, Tree& largs)
{
    return isTree(s, gGlobal->SIGFFUN, ff, largs);
}

LIBFAUST_API Tree sigFConst(Tree type, Tree name, Tree file)
{
    return tree(gGlobal->SIGFCONST, type, name, file);
}
bool isSigFConst(Tree s)
{
    Tree t, n, f;
    return isTree(s, gGlobal->SIGFCONST, t, n, f);
}
LIBFAUST_API bool isSigFConst(Tree s, Tree& type, Tree& name, Tree& file)
{
    return isTree(s, gGlobal->SIGFCONST, type, name, file);
}

LIBFAUST_API Tree sigFVar(Tree type, Tree name, Tree file)
{
    return tree(gGlobal->SIGFVAR, type, name, file);
}
bool isSigFVar(Tree s)
{
    Tree t, n, f;
    return isTree(s, gGlobal->SIGFVAR, t, n, f);
}
LIBFAUST_API bool isSigFVar(Tree s, Tree& type, Tree& name, Tree& file)
{
    return isTree(s, gGlobal->SIGFVAR, type, name, file);
}

// New version using rec and ref

Tree sigProj(int i, Tree rgroup)
{
    return tree(gGlobal->SIGPROJ, tree(i), rgroup);
}
LIBFAUST_API bool isProj(Tree t, int* i, Tree& rgroup)
{
    Tree x;
    return isTree(t, gGlobal->SIGPROJ, x, rgroup) && isInt(x->node(), i);
}

// Int, Bitcast and Float casting

LIBFAUST_API Tree sigIntCast(Tree t)
{
    Node   n = t->node();
    int    i;
    double x;

    if (isInt(n, &i)) return t;
    if (isDouble(n, &x)) return tree(int(x));

    return tree(gGlobal->SIGINTCAST, t);
}

Tree sigBitCast(Tree t)
{
    return tree(gGlobal->SIGBITCAST, t);
}

LIBFAUST_API Tree sigFloatCast(Tree t)
{
    Node   n = t->node();
    int    i;
    double x;

    if (isInt(n, &i)) return tree(double(i));
    if (isDouble(n, &x)) return t;

    return tree(gGlobal->SIGFLOATCAST, t);
}

bool isSigIntCast(Tree t)
{
    Tree x;
    return isTree(t, gGlobal->SIGINTCAST, x);
}
LIBFAUST_API bool isSigIntCast(Tree t, Tree& x)
{
    return isTree(t, gGlobal->SIGINTCAST, x);
}

bool isSigBitCast(Tree t)
{
    Tree x;
    return isTree(t, gGlobal->SIGBITCAST, x);
}
bool isSigBitCast(Tree t, Tree& x)
{
    return isTree(t, gGlobal->SIGBITCAST, x);
}

bool isSigFloatCast(Tree t)
{
    Tree x;
    return isTree(t, gGlobal->SIGFLOATCAST, x);
}
LIBFAUST_API bool isSigFloatCast(Tree t, Tree& x)
{
    return isTree(t, gGlobal->SIGFLOATCAST, x);
}

// Emulation of all fonctions

LIBFAUST_API Tree sigAdd(Tree x, Tree y)
{
    return sigBinOp(kAdd, x, y);
}
LIBFAUST_API Tree sigSub(Tree x, Tree y)
{
    return sigBinOp(kSub, x, y);
}
LIBFAUST_API Tree sigMul(Tree x, Tree y)
{
    return sigBinOp(kMul, x, y);
}
LIBFAUST_API Tree sigDiv(Tree x, Tree y)
{
    return sigBinOp(kDiv, x, y);
}

LIBFAUST_API Tree sigAND(Tree x, Tree y)
{
    return sigBinOp(kAND, x, y);
}
LIBFAUST_API Tree sigOR(Tree x, Tree y)
{
    return sigBinOp(kOR, x, y);
}
LIBFAUST_API Tree sigXOR(Tree x, Tree y)
{
    return sigBinOp(kXOR, x, y);
}

LIBFAUST_API Tree sigLeftShift(Tree x, Tree y)
{
    return sigBinOp(kLsh, x, y);
}
LIBFAUST_API Tree sigARightShift(Tree x, Tree y)
{
    return sigBinOp(kARsh, x, y);
}
LIBFAUST_API Tree sigLRightShift(Tree x, Tree y)
{
    return sigBinOp(kLRsh, x, y);
}

LIBFAUST_API Tree sigGT(Tree x, Tree y)
{
    return sigBinOp(kGT, x, y);
}
LIBFAUST_API Tree sigLT(Tree x, Tree y)
{
    return sigBinOp(kLT, x, y);
}
LIBFAUST_API Tree sigGE(Tree x, Tree y)
{
    return sigBinOp(kGE, x, y);
}
LIBFAUST_API Tree sigLE(Tree x, Tree y)
{
    return sigBinOp(kLE, x, y);
}
LIBFAUST_API Tree sigEQ(Tree x, Tree y)
{
    return sigBinOp(kEQ, x, y);
}
LIBFAUST_API Tree sigNE(Tree x, Tree y)
{
    return sigBinOp(kNE, x, y);
}

/*****************************************************************************
                             User Interface Elements
*****************************************************************************/

LIBFAUST_API Tree sigButton(Tree lbl)
{
    return tree(gGlobal->SIGBUTTON, lbl);
}
bool isSigButton(Tree s)
{
    Tree lbl;
    return isTree(s, gGlobal->SIGBUTTON, lbl);
}
LIBFAUST_API bool isSigButton(Tree s, Tree& lbl)
{
    return isTree(s, gGlobal->SIGBUTTON, lbl);
}

LIBFAUST_API Tree sigCheckbox(Tree lbl)
{
    return tree(gGlobal->SIGCHECKBOX, lbl);
}
bool isSigCheckbox(Tree s)
{
    Tree lbl;
    return isTree(s, gGlobal->SIGCHECKBOX, lbl);
}
LIBFAUST_API bool isSigCheckbox(Tree s, Tree& lbl)
{
    return isTree(s, gGlobal->SIGCHECKBOX, lbl);
}

LIBFAUST_API Tree sigWaveform(const tvec& wf)
{
    return tree(gGlobal->SIGWAVEFORM, wf);
}
LIBFAUST_API bool isSigWaveform(Tree s)
{
    return isTree(s, gGlobal->SIGWAVEFORM);
}

LIBFAUST_API Tree sigHSlider(Tree lbl, Tree init, Tree min, Tree max, Tree step)
{
    return tree(gGlobal->SIGHSLIDER, lbl, list4(init, min, max, step));
}
bool isSigHSlider(Tree s)
{
    Tree lbl, params;
    return isTree(s, gGlobal->SIGHSLIDER, lbl, params);
}

LIBFAUST_API bool isSigHSlider(Tree s, Tree& lbl, Tree& init, Tree& min, Tree& max, Tree& step)
{
    Tree params;
    if (isTree(s, gGlobal->SIGHSLIDER, lbl, params)) {
        init = nth(params, 0);
        min  = nth(params, 1);
        max  = nth(params, 2);
        step = nth(params, 3);
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API Tree sigVSlider(Tree lbl, Tree init, Tree min, Tree max, Tree step)
{
    return tree(gGlobal->SIGVSLIDER, lbl, list4(init, min, max, step));
}
bool isSigVSlider(Tree s)
{
    Tree lbl, params;
    return isTree(s, gGlobal->SIGVSLIDER, lbl, params);
}

LIBFAUST_API bool isSigVSlider(Tree s, Tree& lbl, Tree& init, Tree& min, Tree& max, Tree& step)
{
    Tree params;
    if (isTree(s, gGlobal->SIGVSLIDER, lbl, params)) {
        init = nth(params, 0);
        min  = nth(params, 1);
        max  = nth(params, 2);
        step = nth(params, 3);
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API Tree sigNumEntry(Tree lbl, Tree init, Tree min, Tree max, Tree step)
{
    return tree(gGlobal->SIGNUMENTRY, lbl, list4(init, min, max, step));
}
bool isSigNumEntry(Tree s)
{
    Tree lbl, params;
    return isTree(s, gGlobal->SIGNUMENTRY, lbl, params);
}

LIBFAUST_API bool isSigNumEntry(Tree s, Tree& lbl, Tree& init, Tree& min, Tree& max, Tree& step)
{
    Tree params;
    if (isTree(s, gGlobal->SIGNUMENTRY, lbl, params)) {
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

LIBFAUST_API Tree sigHBargraph(Tree lbl, Tree min, Tree max, Tree x)
{
    return tree(gGlobal->SIGHBARGRAPH, lbl, min, max, x);
}
bool isSigHBargraph(Tree s)
{
    Tree lbl, min, max, x;
    return isTree(s, gGlobal->SIGHBARGRAPH, lbl, min, max, x);
}
LIBFAUST_API bool isSigHBargraph(Tree s, Tree& lbl, Tree& min, Tree& max, Tree& x)
{
    return isTree(s, gGlobal->SIGHBARGRAPH, lbl, min, max, x);
}

LIBFAUST_API Tree sigVBargraph(Tree lbl, Tree min, Tree max, Tree x)
{
    return tree(gGlobal->SIGVBARGRAPH, lbl, min, max, x);
}
bool isSigVBargraph(Tree s)
{
    Tree lbl, min, max, x;
    return isTree(s, gGlobal->SIGVBARGRAPH, lbl, min, max, x);
}
LIBFAUST_API bool isSigVBargraph(Tree s, Tree& lbl, Tree& min, Tree& max, Tree& x)
{
    return isTree(s, gGlobal->SIGVBARGRAPH, lbl, min, max, x);
}

Tree sigAttach(Tree t0, Tree t1)
{
    return tree(gGlobal->SIGATTACH, t0, t1);
}
LIBFAUST_API bool isSigAttach(Tree t, Tree& t0, Tree& t1)
{
    return isTree(t, gGlobal->SIGATTACH, t0, t1);
}

Tree sigEnable(Tree t0, Tree t1)
{
    return tree(gGlobal->SIGENABLE, t0, t1);
}
LIBFAUST_API bool isSigEnable(Tree t, Tree& t0, Tree& t1)
{
    return isTree(t, gGlobal->SIGENABLE, t0, t1);
}

Tree sigControl(Tree t0, Tree t1)
{
    return tree(gGlobal->SIGCONTROL, t0, t1);
}
LIBFAUST_API bool isSigControl(Tree t, Tree& t0, Tree& t1)
{
    return isTree(t, gGlobal->SIGCONTROL, t0, t1);
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

LIBFAUST_API Tree sigAbs(Tree x)
{
    return sigExtended1(gGlobal->gAbsPrim->box(), x);
}

LIBFAUST_API Tree sigAcos(Tree x)
{
    return sigExtended1(gGlobal->gAcosPrim->box(), x);
}

LIBFAUST_API Tree sigTan(Tree x)
{
    return sigExtended1(gGlobal->gTanPrim->box(), x);
}

LIBFAUST_API Tree sigSqrt(Tree x)
{
    return sigExtended1(gGlobal->gSqrtPrim->box(), x);
}

LIBFAUST_API Tree sigSin(Tree x)
{
    return sigExtended1(gGlobal->gSinPrim->box(), x);
}

LIBFAUST_API Tree sigRint(Tree x)
{
    return sigExtended1(gGlobal->gRintPrim->box(), x);
}

LIBFAUST_API Tree sigRemainder(Tree x, Tree y)
{
    return sigExtended2(gGlobal->gRemainderPrim->box(), x, y);
}

LIBFAUST_API Tree sigPow(Tree x, Tree y)
{
    return sigExtended2(gGlobal->gPowPrim->box(), x, y);
}

LIBFAUST_API Tree sigMin(Tree x, Tree y)
{
    return sigExtended2(gGlobal->gMinPrim->box(), x, y);
}

LIBFAUST_API Tree sigMax(Tree x, Tree y)
{
    return sigExtended2(gGlobal->gMaxPrim->box(), x, y);
}

LIBFAUST_API Tree sigLog(Tree x)
{
    return sigExtended1(gGlobal->gLogPrim->box(), x);
}

LIBFAUST_API Tree sigLog10(Tree x)
{
    return sigExtended1(gGlobal->gLog10Prim->box(), x);
}

LIBFAUST_API Tree sigFmod(Tree x, Tree y)
{
    return sigExtended2(gGlobal->gFmodPrim->box(), x, y);
}

LIBFAUST_API Tree sigFloor(Tree x)
{
    return sigExtended1(gGlobal->gFloorPrim->box(), x);
}

LIBFAUST_API Tree sigExp(Tree x)
{
    return sigExtended1(gGlobal->gExpPrim->box(), x);
}

LIBFAUST_API Tree sigExp10(Tree x)
{
    return sigExtended1(gGlobal->gExp10Prim->box(), x);
}

LIBFAUST_API Tree sigCos(Tree x)
{
    return sigExtended1(gGlobal->gCosPrim->box(), x);
}

LIBFAUST_API Tree sigCeil(Tree x)
{
    return sigExtended1(gGlobal->gCeilPrim->box(), x);
}

LIBFAUST_API Tree sigAtan(Tree x)
{
    return sigExtended1(gGlobal->gAtanPrim->box(), x);
}

LIBFAUST_API Tree sigAtan2(Tree x, Tree y)
{
    return sigExtended2(gGlobal->gAtan2Prim->box(), x, y);
}

LIBFAUST_API Tree sigAsin(Tree x)
{
    return sigExtended1(gGlobal->gAsinPrim->box(), x);
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
    // cerr.flags(ios::showpoint); cerr << "divExtendeNums " << *a << "/" << *b << " -> " << *r << endl;
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
 2   sigSoundfileBuffer(label, c, part, ridx): the cth channel content (RK ou RS)
*/
LIBFAUST_API Tree sigSoundfile(Tree label)
{
    return tree(gGlobal->SIGSOUNDFILE, label);
}
LIBFAUST_API Tree sigSoundfileLength(Tree sf, Tree part)
{
    return tree(gGlobal->SIGSOUNDFILELENGTH, sf, part);
}
LIBFAUST_API Tree sigSoundfileRate(Tree sf, Tree part)
{
    return tree(gGlobal->SIGSOUNDFILERATE, sf, part);
}
LIBFAUST_API Tree sigSoundfileBuffer(Tree sf, Tree chan, Tree part, Tree ridx)
{
    return tree(gGlobal->SIGSOUNDFILEBUFFER, sf, chan, part, ridx);
}

LIBFAUST_API bool isSigSoundfile(Tree s, Tree& label)
{
    return isTree(s, gGlobal->SIGSOUNDFILE, label);
}
LIBFAUST_API bool isSigSoundfileLength(Tree s, Tree& sf, Tree& part)
{
    return isTree(s, gGlobal->SIGSOUNDFILELENGTH, sf, part);
}
LIBFAUST_API bool isSigSoundfileRate(Tree s, Tree& sf, Tree& part)
{
    return isTree(s, gGlobal->SIGSOUNDFILERATE, sf, part);
}
LIBFAUST_API bool isSigSoundfileBuffer(Tree s, Tree& sf, Tree& chan, Tree& part, Tree& ridx)
{
    return isTree(s, gGlobal->SIGSOUNDFILEBUFFER, sf, chan, part, ridx);
}
/*****************************************************************************
                             Matrix extension
*****************************************************************************/

// A tuple of signals is basically a list of signals.
// mode = 0 means normal, mode = 1 means blocked
Tree sigTuple(int mode, Tree ls)
{
    return tree(gGlobal->SIGTUPLE, tree(mode), ls);
}
bool isSigTuple(Tree s, int* mode, Tree& ls)
{
    Tree m;
    return isTree(s, gGlobal->SIGTUPLE, m, ls) && isInt(m->node(), mode);
}

// Access the components of a tuple.
// ts is tuple of signals, idx is a scalar signal between 0..n
Tree sigTupleAccess(Tree ts, Tree idx)
{
    return tree(gGlobal->SIGTUPLEACCESS, ts, idx);
}
bool isSigTupleAccess(Tree s, Tree& ts, Tree& idx)
{
    return isTree(s, gGlobal->SIGTUPLEACCESS, ts, idx);
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

    return isSigInt(exp, &i) || isSigReal(exp, &r) || isSigInput(exp, &i) || isSigFConst(exp, type, name, file);
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
    Tree t = gGlobal->nil;

    while (n--) t = cons(a[n], t);
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
