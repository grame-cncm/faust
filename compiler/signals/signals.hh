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

#include "tlib.hh"
#include "binop.hh"
#include <assert.h>
#include <vector>

using namespace std;

extern Tree box_symbol;

#define unknown_box NULL

////////////////////////////////////////////////////////////////////////
/**
 * Signals
 * Block-diagrams are converted into signal expressions via
 * symbolic propagation
 */
///////////////////////////////////////////////////////////////////////

// Constant signals : for all t, x(t)=n
Tree sigInt(int n, Tree box);
Tree sigReal(double n, Tree box);

bool  isSigInt(Tree t, int* i);
bool  isSigReal(Tree t, double* r);


// Inputs and outputs
Tree sigInput(int i, Tree box);

bool  isSigInput(Tree t, int* i);

// delay
Tree  sigDelay0(Tree t, Tree box);
Tree  sigDelay1(Tree t, Tree box);
bool  isSigDelay1(Tree t, Tree& t0);

Tree  sigFixDelay(Tree t0, Tree t1, Tree box = unknown_box);
bool  isSigFixDelay(Tree t, Tree& t0, Tree& t1);

Tree  sigPrefix(Tree t0, Tree t1, Tree box);
bool  isSigPrefix(Tree t, Tree& t0, Tree& t1);

Tree  sigIota(Tree t0, Tree box);
bool  isSigIota(Tree t, Tree& t0);

// Int and Double casting
Tree  sigIntCast(Tree t, Tree box);
Tree  sigFloatCast(Tree t, Tree box);

bool  isSigIntCast(Tree t);
bool  isSigFloatCast(Tree t);

bool  isSigIntCast(Tree t, Tree& x);
bool  isSigFloatCast(Tree t, Tree& x);


// tables
Tree sigRDTbl (Tree t, Tree i, Tree box);
Tree sigWRTbl (Tree id, Tree t, Tree i, Tree s, Tree box);
Tree sigTable (Tree id, Tree n, Tree sig, Tree box);
Tree sigGen   (Tree content, Tree box);

bool isSigRDTbl (Tree s, Tree& t, Tree& i);
bool isSigWRTbl (Tree u, Tree& id, Tree& t, Tree& i, Tree& s);
bool isSigTable (Tree t, Tree& id, Tree& n, Tree& sig);
bool isSigGen   (Tree t, Tree& content);
bool isSigGen   (Tree t);

inline Tree sigWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx, Tree box)
{
	return sigRDTbl(sigWRTbl(nil, sigTable(nil, n, sigGen(init, box), box), widx, wsig, box), ridx, box);
}

inline Tree sigReadOnlyTable(Tree n, Tree init, Tree ridx, Tree box)
{
	return sigRDTbl(sigTable(nil, n, sigGen(init, box), box), ridx, box);
}


// Tables for documentator
// used to replace real tables for documentation purposes only

Tree sigDocConstantTbl(Tree n, Tree init, Tree box);
Tree sigDocWriteTbl(Tree n, Tree init, Tree widx, Tree wsig, Tree box);
Tree sigDocAccessTbl(Tree doctbl, Tree ridx, Tree box);

bool isSigDocConstantTbl(Tree s, Tree& n, Tree& init);
bool isSigDocWriteTbl(Tree s, Tree& n, Tree& init, Tree& widx, Tree& wsig);
bool isSigDocAccessTbl(Tree s, Tree& doctbl, Tree& ridx);

// selectors

Tree sigSelect2 (Tree selector, Tree s1, Tree s2, Tree box);
Tree sigSelect3 (Tree selector, Tree s1, Tree s2, Tree s3, Tree box);

bool isSigSelect2 (Tree t, Tree& selector, Tree& s1, Tree& s2);
bool isSigSelect3 (Tree t, Tree& selector, Tree& s1, Tree& s2, Tree& s3);

// multirate
Tree sigVectorize (Tree s1, Tree s2, Tree box);
bool isSigVectorize (Tree a, Tree& s1, Tree& s2);

Tree sigSerialize (Tree s, Tree box);
bool isSigSerialize (Tree a, Tree& s);

Tree sigConcat (Tree s1, Tree s2, Tree box);
bool isSigConcat (Tree a, Tree& s1, Tree& s2);

Tree sigVectorAt (Tree s1, Tree s2, Tree box);
bool isSigVectorAt (Tree a, Tree& s1, Tree& s2);

// arithmetical operations

Tree sigBinOp	(int op, Tree x, Tree y, Tree box);
bool isSigBinOp	(Tree s, int* op, Tree& x, Tree& y);

// Foreign Functions

Tree sigFFun (Tree ff, Tree largs, Tree box);
bool isSigFFun	(Tree s, Tree& ff, Tree& largs);

// Foreign Constants

Tree sigFConst      (Tree type, Tree name, Tree file, Tree box);
bool isSigFConst    (Tree s);
bool isSigFConst    (Tree s, Tree& type, Tree& name, Tree& file);

// Foreign Variables

Tree sigFVar      (Tree type, Tree name, Tree file, Tree box);
bool isSigFVar    (Tree s);
bool isSigFVar    (Tree s, Tree& type, Tree& name, Tree& file);

// emulation des anciennes fonctions
inline Tree sigAdd(Tree x, Tree y, Tree box = unknown_box)	{ return sigBinOp(kAdd, x, y, box); }
inline Tree sigSub(Tree x, Tree y, Tree box = unknown_box)	{ return sigBinOp(kSub, x, y, box); }
inline Tree sigMul(Tree x, Tree y, Tree box = unknown_box)	{ return sigBinOp(kMul, x, y, box); }
inline Tree sigDiv(Tree x, Tree y, Tree box = unknown_box)	{ return sigBinOp(kDiv, x, y, box); }
inline Tree sigRem(Tree x, Tree y, Tree box = unknown_box)	{ return sigBinOp(kRem, x, y, box); }

inline Tree sigAND(Tree x, Tree y, Tree box)	{ return sigBinOp(kAND, x, y, box); }
inline Tree sigOR(Tree x, Tree y, Tree box)	{ return sigBinOp(kOR, x, y, box); }
inline Tree sigXOR(Tree x, Tree y, Tree box)	{ return sigBinOp(kXOR, x, y, box); }

inline Tree sigLeftShift(Tree x, Tree y, Tree box)	{ return sigBinOp(kLsh, x, y, box); }
inline Tree sigRightShift(Tree x, Tree y, Tree box)	{ return sigBinOp(kRsh, x, y, box); }

inline Tree sigGT(Tree x, Tree y, Tree box)	{ return sigBinOp(kGT, x, y, box); }
inline Tree sigLT(Tree x, Tree y, Tree box)	{ return sigBinOp(kLT, x, y, box); }
inline Tree sigGE(Tree x, Tree y, Tree box)	{ return sigBinOp(kGE, x, y, box); }
inline Tree sigLE(Tree x, Tree y, Tree box)	{ return sigBinOp(kLE, x, y, box); }
inline Tree sigEQ(Tree x, Tree y, Tree box)	{ return sigBinOp(kEQ, x, y, box); }
inline Tree sigNE(Tree x, Tree y, Tree box)	{ return sigBinOp(kNE, x, y, box); }

// pattern matching pour les anciennes fonctions
bool isSigAdd	(Tree a, Tree&x, Tree&y);
bool isSigMul	(Tree a, Tree&x, Tree&y);
bool isSigSub	(Tree a, Tree&x, Tree&y);
bool isSigDiv	(Tree a, Tree&x, Tree&y);

// operations pratiques sur des arbres dont on sait qu'ils sont des nombres
Tree addNums 	(Tree a, Tree b, Tree box = unknown_box);
Tree subNums 	(Tree a, Tree b, Tree box = unknown_box);
Tree mulNums 	(Tree a, Tree b, Tree box = unknown_box);
Tree divNums 	(Tree a, Tree b, Tree box = unknown_box);
Tree divExtendedNums 	(Tree a, Tree b, Tree box = unknown_box);
Tree minusNum	(Tree a, Tree box = unknown_box);
Tree inverseNum	(Tree a, Tree box = unknown_box);

// tests sur les signaux constants
inline bool isNum		(Tree a)	{ assert(a); return isNum(a->node()); }
inline bool isZero		(Tree a)	{ assert(a); return isZero(a->node()); }
inline bool isGTZero	(Tree a)	{ assert(a); return isGTZero(a->node()); }
inline bool isGEZero	(Tree a)	{ assert(a); return isGEZero(a->node()); }
inline bool isOne		(Tree a)	{ assert(a); return isOne(a->node()); }
inline bool isMinusOne	(Tree a)	{ assert(a); return isMinusOne(a->node()); }

//projection for recursive groups
Tree sigProj (int i, Tree rgroup, Tree box);
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

Tree sigButton 	 (Tree label, Tree box);
bool isSigButton (Tree s);
bool isSigButton (Tree s, Tree& label);

Tree sigCheckbox   (Tree label, Tree box);
bool isSigCheckbox (Tree s);
bool isSigCheckbox (Tree s, Tree& label);

Tree sigVSlider   (Tree label, Tree cur, Tree min, Tree max, Tree step, Tree box);
bool isSigVSlider (Tree s);
bool isSigVSlider (Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

Tree sigHSlider   (Tree label, Tree cur, Tree min, Tree max, Tree step, Tree box);
bool isSigHSlider (Tree s);
bool isSigHSlider (Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

Tree sigNumEntry   (Tree label, Tree cur, Tree min, Tree max, Tree step, Tree box);
bool isSigNumEntry (Tree s);
bool isSigNumEntry (Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

// output elements
Tree sigVBargraph   (Tree label, Tree min, Tree max, Tree t0, Tree box);
bool isSigVBargraph (Tree s);
bool isSigVBargraph (Tree s, Tree& label, Tree& min, Tree& max, Tree& t0);

Tree sigHBargraph   (Tree label, Tree min, Tree max, Tree t0, Tree box);
bool isSigHBargraph (Tree s);
bool isSigHBargraph (Tree s, Tree& label, Tree& min, Tree& max, Tree& t0);

Tree sigAttach   (Tree x, Tree y, Tree box);
bool isSigAttach (Tree s);
bool isSigAttach (Tree s, Tree& x, Tree& y);


/*****************************************************************************
							 matrix extension
*****************************************************************************/

// a tuple of signals is basically a list of signals.
// mode = 0 means normal, mode = 1 means blocked
Tree sigTuple (int mode, Tree ls, Tree box);
bool isSigTuple (Tree s, int* mode, Tree& ls);

// Access the components of a tuple.
// ts is tuple of signals, idx is a scalar signal between 0..n
Tree sigTupleAccess(Tree ts, Tree idx, Tree box);
bool isSigTupleAccess(Tree s, Tree& ts, Tree& idx);

// create a tuple of signals
Tree sigCartesianProd (Tree s1, Tree s2, Tree box);



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

// steph
extern Sym SIGINTCAST;
extern Sym SIGFLOATCAST;


/*****************************************************************************
                             signal checks
*****************************************************************************/

/** test if signal and all subsignals are typed */
bool sigIsTyped(Tree root);
/** test if signal and all subsignals are annotated with a property */
bool sigIsAnnotated(Tree root, Tree property);
/** test if tree and all subtrees are annotated with a property */
bool isAnnotated(Tree root, Tree property);
/** test if signal has a valid interval */
bool sigValidInterval(Tree root);

#endif
