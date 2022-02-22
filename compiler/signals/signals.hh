/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _SIGNALS_
#define _SIGNALS_

#include <vector>

#include "binop.hh"
#include "exception.hh"
#include "tlib.hh"
#include "export.hh"

using namespace std;

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
EXPORT Tree sigInt(int n);
EXPORT Tree sigReal(double n);

bool isSigInt(Tree t, int* i);
bool isSigReal(Tree t, double* r);

// Waveforms
EXPORT  Tree sigWaveform(const tvec& wf);
bool isSigWaveform(Tree s);

// Inputs and outputs
EXPORT Tree sigInput(int i);
Tree sigOutput(int i, Tree t);

bool isSigInput(Tree t, int* i);
bool isSigOutput(Tree t, int* i, Tree& t0);

// Delay
Tree sigDelay0(Tree t);
Tree sigDelay1(Tree t);
bool isSigDelay1(Tree t, Tree& t0);

EXPORT Tree sigDelay(Tree t0, Tree t1);
bool isSigDelay(Tree t, Tree& t0, Tree& t1);

Tree sigPrefix(Tree t0, Tree t1);
bool isSigPrefix(Tree t, Tree& t0, Tree& t1);

// Int and Double casting
EXPORT Tree sigIntCast(Tree t);
EXPORT Tree sigFloatCast(Tree t);

bool isSigIntCast(Tree t);
bool isSigFloatCast(Tree t);

bool isSigIntCast(Tree t, Tree& x);
bool isSigFloatCast(Tree t, Tree& x);

// Tables
Tree sigRDTbl(Tree t, Tree i);
Tree sigWRTbl(Tree id, Tree t, Tree i, Tree s);
Tree sigTable(Tree id, Tree n, Tree sig);
Tree sigGen(Tree content);

bool isSigRDTbl(Tree s, Tree& t, Tree& i);
bool isSigWRTbl(Tree u, Tree& id, Tree& t, Tree& i, Tree& s);
bool isSigTable(Tree t, Tree& id, Tree& n, Tree& sig);
bool isSigGen(Tree t, Tree& content);
bool isSigGen(Tree t);

EXPORT Tree sigWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx);
EXPORT Tree sigReadOnlyTable(Tree n, Tree init, Tree ridx);

// Tables for documentator
// used to replace real tables for documentation purposes only
Tree sigDocConstantTbl(Tree n, Tree init);
Tree sigDocWriteTbl(Tree n, Tree init, Tree widx, Tree wsig);
Tree sigDocAccessTbl(Tree doctbl, Tree ridx);

bool isSigDocConstantTbl(Tree s, Tree& n, Tree& init);
bool isSigDocWriteTbl(Tree s, Tree& n, Tree& init, Tree& widx, Tree& wsig);
bool isSigDocAccessTbl(Tree s, Tree& doctbl, Tree& ridx);

// Selectors
EXPORT Tree sigSelect2(Tree selector, Tree s1, Tree s2);
EXPORT Tree sigSelect3(Tree selector, Tree s1, Tree s2, Tree s3);

bool isSigSelect2(Tree t, Tree& selector, Tree& s1, Tree& s2);

// Interval annotation
Tree sigAssertBounds(Tree s1, Tree s2, Tree s3);
Tree sigLowest(Tree s);
Tree sigHighest(Tree s);

bool isSigAssertBounds(Tree t, Tree& s1, Tree& s2, Tree& s3);
bool isSigLowest(Tree t, Tree& s);
bool isSigHighest(Tree t, Tree& s);

// Arithmetical operations
EXPORT Tree sigBinOp(int op, Tree x, Tree y);
bool isSigBinOp(Tree s, int* op, Tree& x, Tree& y);

// Foreign functions
Tree sigFFun(Tree ff, Tree largs);
bool isSigFFun(Tree s, Tree& ff, Tree& largs);

// Foreign constants
EXPORT Tree sigFConst(Tree type, Tree name, Tree file);
bool isSigFConst(Tree s);
bool isSigFConst(Tree s, Tree& type, Tree& name, Tree& file);

// Foreign variables
EXPORT Tree sigFVar(Tree type, Tree name, Tree file);
bool isSigFVar(Tree s);
bool isSigFVar(Tree s, Tree& type, Tree& name, Tree& file);

// Emulation of all fonctions
typedef Tree (* sigFun)(Tree, Tree);

EXPORT Tree sigAdd(Tree x, Tree y);
EXPORT Tree sigSub(Tree x, Tree y);
EXPORT Tree sigMul(Tree x, Tree y);
EXPORT Tree sigDiv(Tree x, Tree y);
Tree sigRem(Tree x, Tree y);

EXPORT Tree sigAND(Tree x, Tree y);
EXPORT Tree sigOR(Tree x, Tree y);
EXPORT Tree sigXOR(Tree x, Tree y);
EXPORT Tree sigLeftShift(Tree x, Tree y);
EXPORT Tree sigLRightShift(Tree x, Tree y);
EXPORT Tree sigARightShift(Tree x, Tree y);
EXPORT Tree sigGT(Tree x, Tree y);
EXPORT Tree sigLT(Tree x, Tree y);
EXPORT Tree sigGE(Tree x, Tree y);
EXPORT Tree sigLE(Tree x, Tree y);
EXPORT Tree sigEQ(Tree x, Tree y);
EXPORT Tree sigNE(Tree x, Tree y);

// Extended math functions
EXPORT Tree sigAbs(Tree x);
EXPORT Tree sigAcos(Tree x);
EXPORT Tree sigTan(Tree x);
EXPORT Tree sigSqrt(Tree x);
EXPORT Tree sigSin(Tree x);
EXPORT Tree sigRint(Tree x);
EXPORT Tree sigRemainder(Tree x, Tree y);
EXPORT Tree sigPow(Tree x, Tree y);
EXPORT Tree sigMin(Tree x, Tree y);
EXPORT Tree sigMax(Tree x, Tree y);
EXPORT Tree sigLog(Tree x);
EXPORT Tree sigLog10(Tree x);
EXPORT Tree sigFmod(Tree x, Tree y);
EXPORT Tree sigFloor(Tree x);
EXPORT Tree sigExp(Tree x);
EXPORT Tree sigExp10(Tree x);
EXPORT Tree sigCos(Tree x);
EXPORT Tree sigCeil(Tree x);
EXPORT Tree sigAtan(Tree x);
EXPORT Tree sigAtan2(Tree x, Tree y);
EXPORT Tree sigAsin(Tree x);

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
bool isProj(Tree t, int* i, Tree& rgroup);

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

EXPORT Tree sigButton(Tree label);
bool isSigButton(Tree s);
bool isSigButton(Tree s, Tree& label);

EXPORT Tree sigCheckbox(Tree label);
bool isSigCheckbox(Tree s);
bool isSigCheckbox(Tree s, Tree& label);

EXPORT Tree sigVSlider(Tree label, Tree init, Tree min, Tree max, Tree step);
bool isSigVSlider(Tree s);
bool isSigVSlider(Tree s, Tree& label, Tree& init, Tree& min, Tree& max, Tree& step);

EXPORT Tree sigHSlider(Tree label, Tree init, Tree min, Tree max, Tree step);
bool isSigHSlider(Tree s);
bool isSigHSlider(Tree s, Tree& label, Tree& init, Tree& min, Tree& max, Tree& step);

EXPORT Tree sigNumEntry(Tree label, Tree init, Tree min, Tree max, Tree step);
bool isSigNumEntry(Tree s);
bool isSigNumEntry(Tree s, Tree& label, Tree& init, Tree& min, Tree& max, Tree& step);

// Output elements
EXPORT Tree sigVBargraph(Tree label, Tree min, Tree max, Tree t0);
bool isSigVBargraph(Tree s);
bool isSigVBargraph(Tree s, Tree& label, Tree& min, Tree& max, Tree& t0);

EXPORT Tree sigHBargraph(Tree label, Tree min, Tree max, Tree t0);
bool isSigHBargraph(Tree s);
bool isSigHBargraph(Tree s, Tree& label, Tree& min, Tree& max, Tree& t0);

EXPORT Tree sigAttach(Tree x, Tree y);
bool isSigAttach(Tree s);
bool isSigAttach(Tree s, Tree& x, Tree& y);

Tree sigEnable(Tree x, Tree y);
bool isSigEnable(Tree s);
bool isSigEnable(Tree s, Tree& x, Tree& y);

Tree sigControl(Tree x, Tree y);
bool isSigControl(Tree s);
bool isSigControl(Tree s, Tree& x, Tree& y);

/*****************************************************************************
                             Sounfiles (also UI elements)
*****************************************************************************/
/*
A boxSounfile(label,c) has 2 inputs and c+3 outputs:
    0   sigSoundfileLength(label, part):  the number of frames of the soundfile part (NK)
    1   sigSoundfileRate(label): the sampling rate encoded in the file (NK)
    2.. sigSoundfileBuffer(label, c, part, ridx): the cth channel content (RK or RS)
*/

EXPORT Tree sigSoundfile(Tree label);
EXPORT Tree sigSoundfileLength(Tree sf, Tree part);
EXPORT Tree sigSoundfileRate(Tree sf, Tree part);
EXPORT Tree sigSoundfileBuffer(Tree sf, Tree chan, Tree part, Tree ridx);

bool isSigSoundfile(Tree s, Tree& label);
bool isSigSoundfileLength(Tree s, Tree& sf, Tree& part);
bool isSigSoundfileRate(Tree s, Tree& sf, Tree& part);
bool isSigSoundfileBuffer(Tree s, Tree& sf, Tree& chan, Tree& part, Tree& ridx);

/*****************************************************************************
                             matrix extension
*****************************************************************************/

// A tuple of signals is basically a list of signals.
// mode = 0 means normal, mode = 1 means blocked
Tree sigTuple(int mode, Tree ls);
bool isSigTuple(Tree s, int* mode, Tree& ls);

// Access the components of a tuple.
// ts is tuple of signals, idx is a scalar signal between 0..n
Tree sigTupleAccess(Tree ts, Tree idx);
bool isSigTupleAccess(Tree s, Tree& ts, Tree& idx);

// Create a tuple of signals
Tree sigCartesianProd(Tree s1, Tree s2);

/*****************************************************************************
                             FTZ wrapping
    Add FTZ wrapping to a signal
*****************************************************************************/

Tree sigFTZ(Tree s);

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

bool sigList2vecInt(Tree ls, vector<int>& v);

/**
 * Convert an stl vector of signals into a tree list of signals
 */
Tree listConvert(const siglist& a);

#endif
