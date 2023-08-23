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

#ifndef _SIGNALS_
#define _SIGNALS_

#include <vector>

#include "faust/export.h"

#include "binop.hh"
#include "exception.hh"
#include "tlib.hh"
#include "global.hh"

#if defined(WIN32) && !defined(__GNUC__)
#pragma warning(disable : 4800)
#endif

////////////////////////////////////////////////////////////////////////
/**
 * Signals
 * Block-diagrams are converted into signal expressions via
 * symbolic propagation
 */
///////////////////////////////////////////////////////////////////////

typedef std::vector<Tree> siglist;

// Constant signals : for all t, x(t)=n
LIBFAUST_API Tree sigInt(int n);
Tree sigInt64(int64_t n);
LIBFAUST_API Tree sigReal(double n);

LIBFAUST_API bool isSigInt(Tree t, int* i);
bool isSigInt64(Tree t, int64_t* i);
LIBFAUST_API bool isSigReal(Tree t, double* r);

// Waveforms
LIBFAUST_API Tree sigWaveform(const tvec& wf);
LIBFAUST_API bool isSigWaveform(Tree s);

// Inputs and outputs
LIBFAUST_API Tree sigInput(int i);
Tree sigOutput(int i, Tree t);

LIBFAUST_API bool isSigInput(Tree t, int* i);
LIBFAUST_API bool isSigOutput(Tree t, int* i, Tree& t0);

// Delay
Tree sigDelay0(Tree t);
LIBFAUST_API Tree sigDelay1(Tree t);
LIBFAUST_API bool isSigDelay1(Tree t, Tree& t0);

LIBFAUST_API Tree sigDelay(Tree t0, Tree t1);
LIBFAUST_API bool isSigDelay(Tree t, Tree& t0, Tree& t1);

Tree sigPrefix(Tree t0, Tree t1);
LIBFAUST_API bool isSigPrefix(Tree t, Tree& t0, Tree& t1);

// Int, Bitcast and Double casting
LIBFAUST_API Tree sigIntCast(Tree t);
Tree sigBitCast(Tree t);
LIBFAUST_API Tree sigFloatCast(Tree t);

bool isSigIntCast(Tree t);
bool isSigBitCast(Tree t);
bool isSigFloatCast(Tree t);

LIBFAUST_API bool isSigIntCast(Tree t, Tree& x);
bool isSigBitCast(Tree t, Tree& x);
LIBFAUST_API bool isSigFloatCast(Tree t, Tree& x);

// Tables
Tree sigRDTbl(Tree tbl, Tree ri);
// for rwtable and rdtable (with wi and ws = gGlobal->nil)
Tree sigWRTbl(Tree size, Tree gen, Tree wi = gGlobal->nil, Tree ws = gGlobal->nil);
Tree sigGen(Tree content);

LIBFAUST_API bool isSigRDTbl(Tree s, Tree& tbl, Tree& ri);
// for rwtable
LIBFAUST_API bool isSigWRTbl(Tree u, Tree& size, Tree& gen, Tree& wi, Tree& ws);
// for rdtable
LIBFAUST_API bool isSigWRTbl(Tree u, Tree& size, Tree& gen);
LIBFAUST_API bool isSigGen(Tree t, Tree& content);
bool isSigGen(Tree t);

LIBFAUST_API Tree sigWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx);
LIBFAUST_API Tree sigReadOnlyTable(Tree n, Tree init, Tree ridx);

// Tables for documentator
// used to replace real tables for documentation purposes only
Tree sigDocConstantTbl(Tree n, Tree init);
Tree sigDocWriteTbl(Tree n, Tree init, Tree widx, Tree wsig);
Tree sigDocAccessTbl(Tree doctbl, Tree ridx);

LIBFAUST_API bool isSigDocConstantTbl(Tree s, Tree& n, Tree& init);
LIBFAUST_API bool isSigDocWriteTbl(Tree s, Tree& n, Tree& init, Tree& widx, Tree& wsig);
LIBFAUST_API bool isSigDocAccessTbl(Tree s, Tree& doctbl, Tree& ridx);

// Selectors
LIBFAUST_API Tree sigSelect2(Tree selector, Tree s1, Tree s2);
LIBFAUST_API Tree sigSelect3(Tree selector, Tree s1, Tree s2, Tree s3);

LIBFAUST_API bool isSigSelect2(Tree t, Tree& selector, Tree& s1, Tree& s2);

// Interval annotation
Tree sigAssertBounds(Tree s1, Tree s2, Tree s3);
Tree sigLowest(Tree s);
Tree sigHighest(Tree s);

LIBFAUST_API bool isSigAssertBounds(Tree t, Tree& s1, Tree& s2, Tree& s3);
LIBFAUST_API bool isSigLowest(Tree t, Tree& s);
LIBFAUST_API bool isSigHighest(Tree t, Tree& s);

// Arithmetical operations
LIBFAUST_API Tree sigBinOp(SOperator op, Tree x, Tree y);
LIBFAUST_API Tree sigBinOp(int op, Tree x, Tree y);
LIBFAUST_API bool isSigBinOp(Tree s, int* op, Tree& x, Tree& y);

// Foreign functions
Tree sigFFun(Tree ff, Tree largs);
LIBFAUST_API bool isSigFFun(Tree s, Tree& ff, Tree& largs);

// Foreign constants
LIBFAUST_API Tree sigFConst(Tree type, Tree name, Tree file);
bool isSigFConst(Tree s);
LIBFAUST_API bool isSigFConst(Tree s, Tree& type, Tree& name, Tree& file);

// Foreign variables
LIBFAUST_API Tree sigFVar(Tree type, Tree name, Tree file);
bool isSigFVar(Tree s);
LIBFAUST_API bool isSigFVar(Tree s, Tree& type, Tree& name, Tree& file);

// Emulation of all fonctions
typedef Tree (* sigFun)(Tree, Tree);

LIBFAUST_API Tree sigAdd(Tree x, Tree y);
LIBFAUST_API Tree sigSub(Tree x, Tree y);
LIBFAUST_API Tree sigMul(Tree x, Tree y);
LIBFAUST_API Tree sigDiv(Tree x, Tree y);
LIBFAUST_API Tree sigRem(Tree x, Tree y);

LIBFAUST_API Tree sigAND(Tree x, Tree y);
LIBFAUST_API Tree sigOR(Tree x, Tree y);
LIBFAUST_API Tree sigXOR(Tree x, Tree y);
LIBFAUST_API Tree sigLeftShift(Tree x, Tree y);
LIBFAUST_API Tree sigLRightShift(Tree x, Tree y);
LIBFAUST_API Tree sigARightShift(Tree x, Tree y);
LIBFAUST_API Tree sigGT(Tree x, Tree y);
LIBFAUST_API Tree sigLT(Tree x, Tree y);
LIBFAUST_API Tree sigGE(Tree x, Tree y);
LIBFAUST_API Tree sigLE(Tree x, Tree y);
LIBFAUST_API Tree sigEQ(Tree x, Tree y);
LIBFAUST_API Tree sigNE(Tree x, Tree y);

// Extended math functions
LIBFAUST_API Tree sigAbs(Tree x);
LIBFAUST_API Tree sigAcos(Tree x);
LIBFAUST_API Tree sigTan(Tree x);
LIBFAUST_API Tree sigSqrt(Tree x);
LIBFAUST_API Tree sigSin(Tree x);
LIBFAUST_API Tree sigRint(Tree x);
LIBFAUST_API Tree sigRemainder(Tree x, Tree y);
LIBFAUST_API Tree sigPow(Tree x, Tree y);
LIBFAUST_API Tree sigMin(Tree x, Tree y);
LIBFAUST_API Tree sigMax(Tree x, Tree y);
LIBFAUST_API Tree sigLog(Tree x);
LIBFAUST_API Tree sigLog10(Tree x);
LIBFAUST_API Tree sigFmod(Tree x, Tree y);
LIBFAUST_API Tree sigFloor(Tree x);
LIBFAUST_API Tree sigExp(Tree x);
LIBFAUST_API Tree sigExp10(Tree x);
LIBFAUST_API Tree sigCos(Tree x);
LIBFAUST_API Tree sigCeil(Tree x);
LIBFAUST_API Tree sigAtan(Tree x);
LIBFAUST_API Tree sigAtan2(Tree x, Tree y);
LIBFAUST_API Tree sigAsin(Tree x);

// Pattern matching for old fonctions
bool isSigAdd(Tree a, Tree& x, Tree& y);
bool isSigMul(Tree a, Tree& x, Tree& y);
bool isSigSub(Tree a, Tree& x, Tree& y);
bool isSigDiv(Tree a, Tree& x, Tree& y);

// Operations on tree representing numbers
bool sameMagnitude(Tree a, Tree b);

Tree addNums(Tree a, Tree b);
Tree subNums(Tree a, Tree b);
Tree mulNums(Tree a, Tree b);
Tree divExtendedNums(Tree a, Tree b);
Tree minusNum(Tree a);
Tree inverseNum(Tree a);

// Tests on constant signals
inline bool isNum(Tree a)
{
    faustassert(a);
    return isNum(a->node());
}
inline bool isZero(Tree a)
{
    faustassert(a);
    return isZero(a->node());
}
inline bool isGTZero(Tree a)
{
    faustassert(a);
    return isGTZero(a->node());
}
inline bool isGEZero(Tree a)
{
    faustassert(a);
    return isGEZero(a->node());
}
inline bool isOne(Tree a)
{
    faustassert(a);
    return isOne(a->node());
}
inline bool isMinusOne(Tree a)
{
    faustassert(a);
    return isMinusOne(a->node());
}

// Projection for recursive groups
Tree sigProj(int i, Tree rgroup);
LIBFAUST_API bool isProj(Tree t, int* i, Tree& rgroup);

inline bool isNum(const Tree& t, num& n)
{
    double f;
    int    i;

    if (isDouble(t->node(), &f)) {
        n = f;
        return true;
    }
    if (isInt(t->node(), &i)) {
        n = i;
        return true;
    }
    return false;
}

/*****************************************************************************
                             User Interface Elements
*****************************************************************************/

LIBFAUST_API Tree sigButton(Tree label);
bool isSigButton(Tree s);
LIBFAUST_API bool isSigButton(Tree s, Tree& label);

LIBFAUST_API Tree sigCheckbox(Tree label);
bool isSigCheckbox(Tree s);
LIBFAUST_API bool isSigCheckbox(Tree s, Tree& label);

LIBFAUST_API Tree sigVSlider(Tree label, Tree init, Tree min, Tree max, Tree step);
bool isSigVSlider(Tree s);
LIBFAUST_API bool isSigVSlider(Tree s, Tree& label, Tree& init, Tree& min, Tree& max, Tree& step);

LIBFAUST_API Tree sigHSlider(Tree label, Tree init, Tree min, Tree max, Tree step);
bool isSigHSlider(Tree s);
LIBFAUST_API bool isSigHSlider(Tree s, Tree& label, Tree& init, Tree& min, Tree& max, Tree& step);

LIBFAUST_API Tree sigNumEntry(Tree label, Tree init, Tree min, Tree max, Tree step);
bool isSigNumEntry(Tree s);
LIBFAUST_API bool isSigNumEntry(Tree s, Tree& label, Tree& init, Tree& min, Tree& max, Tree& step);

// Output elements
LIBFAUST_API Tree sigVBargraph(Tree label, Tree min, Tree max, Tree t0);
bool isSigVBargraph(Tree s);
LIBFAUST_API bool isSigVBargraph(Tree s, Tree& label, Tree& min, Tree& max, Tree& t0);

LIBFAUST_API Tree sigHBargraph(Tree label, Tree min, Tree max, Tree t0);
bool isSigHBargraph(Tree s);
LIBFAUST_API bool isSigHBargraph(Tree s, Tree& label, Tree& min, Tree& max, Tree& t0);

LIBFAUST_API Tree sigAttach(Tree x, Tree y);
LIBFAUST_API bool isSigAttach(Tree s, Tree& x, Tree& y);

Tree sigEnable(Tree x, Tree y);
LIBFAUST_API bool isSigEnable(Tree s, Tree& x, Tree& y);

Tree sigControl(Tree x, Tree y);
LIBFAUST_API bool isSigControl(Tree s, Tree& x, Tree& y);

/*****************************************************************************
                             Soundfiles (also UI elements)
*****************************************************************************/
/*
A boxSounfile(label,c) has 2 inputs and c+3 outputs:
    0   sigSoundfileLength(label, part):  the number of frames of the soundfile part (NK)
    1   sigSoundfileRate(label): the sampling rate encoded in the file (NK)
    2.. sigSoundfileBuffer(label, c, part, ridx): the cth channel content (RK or RS)
*/

LIBFAUST_API Tree sigSoundfile(Tree label);
LIBFAUST_API Tree sigSoundfileLength(Tree sf, Tree part);
LIBFAUST_API Tree sigSoundfileRate(Tree sf, Tree part);
LIBFAUST_API Tree sigSoundfileBuffer(Tree sf, Tree chan, Tree part, Tree ridx);

LIBFAUST_API bool isSigSoundfile(Tree s, Tree& label);
LIBFAUST_API bool isSigSoundfileLength(Tree s, Tree& sf, Tree& part);
LIBFAUST_API bool isSigSoundfileRate(Tree s, Tree& sf, Tree& part);
LIBFAUST_API bool isSigSoundfileBuffer(Tree s, Tree& sf, Tree& chan, Tree& part, Tree& ridx);

/*****************************************************************************
                             Matrix extension
*****************************************************************************/

// A tuple of signals is basically a list of signals.
// mode = 0 means normal, mode = 1 means blocked
Tree sigTuple(int mode, Tree ls);
LIBFAUST_API bool isSigTuple(Tree s, int* mode, Tree& ls);

// Access the components of a tuple.
// ts is tuple of signals, idx is a scalar signal between 0..n
Tree sigTupleAccess(Tree ts, Tree idx);
LIBFAUST_API bool isSigTupleAccess(Tree s, Tree& ts, Tree& idx);

// Create a tuple of signals
Tree sigCartesianProd(Tree s1, Tree s2);

/*****************************************************************************
                             Access to sub signals of a signal
*****************************************************************************/

int getSubSignals(Tree sig, tvec& vsigs, bool visitgen = true);

/**
 * Test if exp is very simple that is it
 * can't be considered a real component
 * @param exp the signal we want to test
 * @return true if it a very simple signal
 */
bool verySimple(Tree exp);

/**
 * Convert a list of signals (representing numbers) into a vector of ints
 * the result is true if the conversion was possible.
 */
bool sigList2vecInt(Tree ls, std::vector<int>& v);

/**
 * Convert an stl vector of signals into a tree list of signals
 */
Tree listConvert(const siglist& a);

/**
 * Convert a Tree in stl vector of signals
 */
siglist treeConvert(Tree t);

#endif
