/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#include "exception.hh"
#include "tlib.hh"
#include "binop.hh"

using namespace std;

////////////////////////////////////////////////////////////////////////
/**
 * Signals
 * Block-diagrams are converted into signal expressions via
 * symbolic propagation
 */
///////////////////////////////////////////////////////////////////////

// Constant signals : for all t, x(t)=n
Tree sigInt(int n);
Tree sigReal(double n);

bool  isSigInt(Tree t, int* i);
bool  isSigReal(Tree t, double* r);

// waveforms
Tree sigWaveform (const tvec& wf);
bool isSigWaveform(Tree s);

// Inputs and outputs
Tree sigInput(int i);
Tree sigOutput(int i, Tree t);

bool  isSigInput(Tree t, int* i);
bool  isSigOutput(Tree t, int* i, Tree& t0);

// delay
Tree  sigDelay0(Tree t);
Tree  sigDelay1(Tree t);
bool  isSigDelay1(Tree t, Tree& t0);

Tree  sigFixDelay(Tree t0, Tree t1);
bool  isSigFixDelay(Tree t, Tree& t0, Tree& t1);

Tree  sigPrefix(Tree t0, Tree t1);
bool  isSigPrefix(Tree t, Tree& t0, Tree& t1);

Tree  sigIota(Tree t0);
bool  isSigIota(Tree t, Tree& t0);

// Int and Double casting
Tree  sigIntCast(Tree t);
Tree  sigFloatCast(Tree t);

bool  isSigIntCast(Tree t);
bool  isSigFloatCast(Tree t);

bool  isSigIntCast(Tree t, Tree& x);
bool  isSigFloatCast(Tree t, Tree& x);

// tables
Tree sigRDTbl (Tree t, Tree i);
Tree sigWRTbl (Tree id, Tree t, Tree i, Tree s);
Tree sigTable (Tree id, Tree n, Tree sig);
Tree sigGen   (Tree content);

bool isSigRDTbl (Tree s, Tree& t, Tree& i);
bool isSigWRTbl (Tree u, Tree& id, Tree& t, Tree& i, Tree& s);
bool isSigTable (Tree t, Tree& id, Tree& n, Tree& sig);
bool isSigGen   (Tree t, Tree& content);
bool isSigGen   (Tree t);

Tree sigWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx);
Tree sigReadOnlyTable(Tree n, Tree init, Tree ridx);

// Tables for documentator
// used to replace real tables for documentation purposes only

Tree sigDocConstantTbl(Tree n, Tree init);
Tree sigDocWriteTbl(Tree n, Tree init, Tree widx, Tree wsig);
Tree sigDocAccessTbl(Tree doctbl, Tree ridx);

bool isSigDocConstantTbl(Tree s, Tree& n, Tree& init);
bool isSigDocWriteTbl(Tree s, Tree& n, Tree& init, Tree& widx, Tree& wsig);
bool isSigDocAccessTbl(Tree s, Tree& doctbl, Tree& ridx);

// selectors

Tree sigSelect2 (Tree selector, Tree s1, Tree s2);
Tree sigSelect3 (Tree selector, Tree s1, Tree s2, Tree s3);

bool isSigSelect2 (Tree t, Tree& selector, Tree& s1, Tree& s2);
bool isSigSelect3 (Tree t, Tree& selector, Tree& s1, Tree& s2, Tree& s3);

// arithmetical operations 

Tree sigBinOp	(int op, Tree x, Tree y);
bool isSigBinOp	(Tree s, int* op, Tree& x, Tree& y);

// Foreign Functions

Tree sigFFun (Tree ff, Tree largs);
bool isSigFFun	(Tree s, Tree& ff, Tree& largs);

// Foreign Constants

Tree sigFConst      (Tree type, Tree name, Tree file);
bool isSigFConst    (Tree s);
bool isSigFConst    (Tree s, Tree& type, Tree& name, Tree& file);

// Foreign Variables

Tree sigFVar      (Tree type, Tree name, Tree file);
bool isSigFVar    (Tree s);
bool isSigFVar    (Tree s, Tree& type, Tree& name, Tree& file);

// emulation of all fonctions
inline Tree sigAdd(Tree x, Tree y)	{ return sigBinOp(kAdd, x, y); }
inline Tree sigSub(Tree x, Tree y)	{ return sigBinOp(kSub, x, y); }
inline Tree sigMul(Tree x, Tree y)	{ return sigBinOp(kMul, x, y); }
inline Tree sigDiv(Tree x, Tree y)	{ return sigBinOp(kDiv, x, y); }
inline Tree sigRem(Tree x, Tree y)	{ return sigBinOp(kRem, x, y); }

inline Tree sigAND(Tree x, Tree y)	{ return sigBinOp(kAND, x, y); }
inline Tree sigOR(Tree x, Tree y)	{ return sigBinOp(kOR, x, y); }
inline Tree sigXOR(Tree x, Tree y)	{ return sigBinOp(kXOR, x, y); }

inline Tree sigLeftShift(Tree x, Tree y)	{ return sigBinOp(kLsh, x, y); }
inline Tree sigRightShift(Tree x, Tree y)	{ return sigBinOp(kRsh, x, y); }

inline Tree sigGT(Tree x, Tree y)	{ return sigBinOp(kGT, x, y); }
inline Tree sigLT(Tree x, Tree y)	{ return sigBinOp(kLT, x, y); }
inline Tree sigGE(Tree x, Tree y)	{ return sigBinOp(kGE, x, y); }
inline Tree sigLE(Tree x, Tree y)	{ return sigBinOp(kLE, x, y); }
inline Tree sigEQ(Tree x, Tree y)	{ return sigBinOp(kEQ, x, y); }
inline Tree sigNE(Tree x, Tree y)	{ return sigBinOp(kNE, x, y); }

// pattern matching for old fonctions
bool isSigAdd	(Tree a, Tree&x, Tree&y);
bool isSigMul	(Tree a, Tree&x, Tree&y);
bool isSigSub	(Tree a, Tree&x, Tree&y);
bool isSigDiv	(Tree a, Tree&x, Tree&y);

// operations on tree representing numbers
bool sameMagnitude(Tree a, Tree b);

Tree addNums 	(Tree a, Tree b);
Tree subNums 	(Tree a, Tree b);
Tree mulNums 	(Tree a, Tree b);
Tree divExtendedNums 	(Tree a, Tree b);
Tree minusNum	(Tree a);
Tree inverseNum	(Tree a);

// tests on constant signals
inline bool isNum		(Tree a)	{ faustassert(a); return isNum(a->node()); }
inline bool isZero		(Tree a)	{ faustassert(a); return isZero(a->node()); }
inline bool isGTZero	(Tree a)	{ faustassert(a); return isGTZero(a->node()); }
inline bool isGEZero	(Tree a)	{ faustassert(a); return isGEZero(a->node()); }
inline bool isOne		(Tree a)	{ faustassert(a); return isOne(a->node()); }
inline bool isMinusOne	(Tree a)	{ faustassert(a); return isMinusOne(a->node()); }

//projection for recursive groups
Tree sigProj (int i, Tree rgroup);
bool isProj (Tree t, int* i, Tree& rgroup);

inline bool isNum(const Tree& t, num& n)
{
	double 		f;
	int 		i;

	if (isDouble(t->node(), &f)) { n = f; return true;  }
	if (isInt(t->node(), &i)) { n = i; return true;  }
	return false;
}

/*****************************************************************************
							 User Interface Elements
*****************************************************************************/

Tree sigButton 	 (Tree label);
bool isSigButton (Tree s);
bool isSigButton (Tree s, Tree& label);

Tree sigCheckbox   (Tree label);
bool isSigCheckbox (Tree s);
bool isSigCheckbox (Tree s, Tree& label);

Tree sigVSlider   (Tree label, Tree cur, Tree min, Tree max, Tree step);
bool isSigVSlider (Tree s);
bool isSigVSlider (Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

Tree sigHSlider   (Tree label, Tree cur, Tree min, Tree max, Tree step);
bool isSigHSlider (Tree s);
bool isSigHSlider (Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

Tree sigNumEntry   (Tree label, Tree cur, Tree min, Tree max, Tree step);
bool isSigNumEntry (Tree s);
bool isSigNumEntry (Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

// output elements
Tree sigVBargraph   (Tree label, Tree min, Tree max, Tree t0);
bool isSigVBargraph (Tree s);
bool isSigVBargraph (Tree s, Tree& label, Tree& min, Tree& max, Tree& t0);

Tree sigHBargraph   (Tree label, Tree min, Tree max, Tree t0);
bool isSigHBargraph (Tree s);
bool isSigHBargraph (Tree s, Tree& label, Tree& min, Tree& max, Tree& t0);

Tree sigAttach   (Tree x, Tree y);
bool isSigAttach (Tree s);
bool isSigAttach (Tree s, Tree& x, Tree& y);

Tree sigEnable   (Tree x, Tree y);
bool isSigEnable (Tree s);
bool isSigEnable (Tree s, Tree& x, Tree& y);

Tree sigControl   (Tree x, Tree y);
bool isSigControl (Tree s);
bool isSigControl (Tree s, Tree& x, Tree& y);

/*****************************************************************************
							 Sounfiles (also UI elements)
*****************************************************************************/
/*
A boxSounfile(label,c) has 1 input channel and c+2 output channels:
    0   sigSoundfileLength(label):  the number of frames of the soundfile (NK)
    1   sigSoundfileRate(label): the sampling rate encoded in the file (NK)
    2.. sigSoundfileChannel(label, c, ridx): the cth channel content (RK ou RS)
*/

Tree sigSoundfile(Tree label);
Tree sigSoundfileLength(Tree sf);
Tree sigSoundfileRate(Tree sf);
Tree sigSoundfileChannel(Tree sf, Tree chan, Tree ridx);

bool isSigSoundfile(Tree s, Tree& label);
bool isSigSoundfileLength(Tree s, Tree& sf);
bool isSigSoundfileRate(Tree s, Tree& sf);
bool isSigSoundfileChannel(Tree s, Tree& sf, Tree& chan, Tree& ridx);

/*****************************************************************************
							 matrix extension
*****************************************************************************/

// a tuple of signals is basically a list of signals.
// mode = 0 means normal, mode = 1 means blocked
Tree sigTuple (int mode, Tree ls);
bool isSigTuple (Tree s, int* mode, Tree& ls);

// Access the components of a tuple.
// ts is tuple of signals, idx is a scalar signal between 0..n
Tree sigTupleAccess(Tree ts, Tree idx);
bool isSigTupleAccess(Tree s, Tree& ts, Tree& idx);

// create a tuple of signals
Tree sigCartesianProd (Tree s1, Tree s2);

/*****************************************************************************
							 FTZ wrapping
    Add FTZ wrapping to a signal
*****************************************************************************/

Tree sigFTZ (Tree s);

/*****************************************************************************
							 access to sub signals of a signal
*****************************************************************************/

int	getSubSignals (Tree sig, vector<Tree>& vsigs, bool visitgen=true);

/**
 * Test if exp is very simple that is it
 * can't be considered a real component
 * @param exp the signal we want to test
 * @return true if it a very simple signal
 */
bool verySimple(Tree exp);

#endif
