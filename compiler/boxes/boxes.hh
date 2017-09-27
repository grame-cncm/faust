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

#ifndef _BOXES_
#define _BOXES_

/*****************************************************************************
******************************************************************************
							FAUST BOX ALGEBRA
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
box ::= i | f | p0 | p1 | p3
	  | _ | ! | a:b | a<:b | a,b | a:>b | a~b

 History :
 ---------
 	2002-06-06 : First version

******************************************************************************
*****************************************************************************/

#include "tlib.hh"
#include "signals.hh"

struct Automaton;

/*****************************************************************************
******************************************************************************

							    The Box Language

******************************************************************************
*****************************************************************************/


/*****************************************************************************
							    	Identifiers
*****************************************************************************/

Tree boxIdent(const char* name);
bool isBoxIdent(Tree t);
bool isBoxIdent(Tree t, const char** name);

/*****************************************************************************
							    	Numbers
*****************************************************************************/

Tree boxInt(int n);
Tree boxReal(double n);

bool  isBoxInt(Tree t);
bool  isBoxReal(Tree t);

bool  isBoxInt(Tree t, int* i);
bool  isBoxReal(Tree t, double* r);

/*****************************************************************************
							    	Waveform
	waveform {1,2,3,...}
	an object with 2 outputs : the size of the waveform, the actual waveform.
	A Waveform is in is all its values are int. It is float otherwise.
*****************************************************************************/

Tree boxWaveform(const tvec& br);
bool  isBoxWaveform(Tree t);

/*****************************************************************************
							   	Wire and Cut
*****************************************************************************/

Tree boxWire();
Tree boxCut();

bool isBoxWire(Tree t);
bool isBoxCut(Tree t);

/*****************************************************************************
						Symbolic Boxes with symbolic slots
*****************************************************************************/

Tree boxSlot(int id);
Tree boxSymbolic(Tree slot, Tree body);

bool isBoxSlot(Tree t);
bool isBoxSymbolic(Tree t);

bool isBoxSlot(Tree t, int* id);
bool isBoxSymbolic(Tree t, Tree& slot, Tree& body);

/*****************************************************************************
							  Composition of Boxes
*****************************************************************************/

Tree boxSeq   (Tree x, Tree y);
Tree boxPar   (Tree x, Tree y);
Tree boxRec	  (Tree x, Tree y);
Tree boxSplit (Tree x, Tree y);
Tree boxMerge (Tree x, Tree y);

bool isBoxSeq	(Tree t, Tree& x, Tree& y);
bool isBoxPar	(Tree t, Tree& x, Tree& y);
bool isBoxRec	(Tree t, Tree& x, Tree& y);
bool isBoxSplit	(Tree t, Tree& x, Tree& y);
bool isBoxMerge	(Tree t, Tree& x, Tree& y);

/*****************************************************************************
						Algorithmic Composition of Boxes
*****************************************************************************/

Tree boxIPar(Tree x, Tree y, Tree z);
Tree boxISeq(Tree x, Tree y, Tree z);
Tree boxISum(Tree x, Tree y, Tree z);
Tree boxIProd(Tree x, Tree y, Tree z);

bool isBoxIPar(Tree t, Tree& x, Tree& y, Tree& z);
bool isBoxISeq(Tree t, Tree& x, Tree& y, Tree& z);
bool isBoxISum(Tree t, Tree& x, Tree& y, Tree& z);
bool isBoxIProd(Tree t, Tree& x, Tree& y, Tree& z);

/*****************************************************************************
                        Static information on Boxes
*****************************************************************************/

Tree boxInputs  (Tree x);
Tree boxOutputs (Tree x);

bool isBoxInputs  (Tree t, Tree& x);
bool isBoxOutputs (Tree t, Tree& x);


/*****************************************************************************
							  Lambda-Calculus of Boxes
*****************************************************************************/

Tree buildBoxAbstr	(Tree x, Tree y);
Tree buildBoxAppl 	(Tree x, Tree y);

Tree boxAbstr	(Tree x, Tree y);
Tree boxAppl 	(Tree x, Tree y);

bool isBoxAbstr	(Tree t);
bool isBoxAppl	(Tree t);

bool isBoxAbstr	(Tree t, Tree& x, Tree& y);
bool isBoxAppl	(Tree t, Tree& x, Tree& y);

Tree closure (Tree abstr, Tree genv, Tree vis, Tree lenv);

bool isClosure	(Tree t, Tree& abstr, Tree& genv, Tree& vis, Tree& lenv);

// for foo(x,y).faa expressions
Tree boxAccess (Tree exp, Tree id);
bool isBoxAccess(Tree t, Tree& exp, Tree& id);

/*****************************************************************************
                        Boxes with local definitions
*****************************************************************************/

Tree boxWithLocalDef (Tree body, Tree ldef);
bool isBoxWithLocalDef (Tree t, Tree& body, Tree& ldef);
Tree boxWithRecDef (Tree body, Tree ldef);

/*****************************************************************************
                        Modification of local definitions
*****************************************************************************/

Tree boxModifLocalDef (Tree body, Tree ldef);
bool isBoxModifLocalDef (Tree t, Tree& body, Tree& ldef);

/*****************************************************************************
							 Error Boxe
*****************************************************************************/

Tree boxError();
bool isBoxError(Tree t);

/*****************************************************************************
							 Primitive Boxes (n -> 1)
*****************************************************************************/

typedef Tree (*prim0)();
typedef Tree (*prim1)(Tree x);
typedef Tree (*prim2)(Tree x, Tree y);
typedef Tree (*prim3)(Tree x, Tree y, Tree z);
typedef Tree (*prim4)(Tree w, Tree x, Tree y, Tree z);
typedef Tree (*prim5)(Tree v, Tree w, Tree x, Tree y, Tree z);

Tree boxPrim0 (prim0 foo);
Tree boxPrim1 (prim1 foo);
Tree boxPrim2 (prim2 foo);
Tree boxPrim3 (prim3 foo);
Tree boxPrim4 (prim4 foo);
Tree boxPrim5 (prim5 foo);

bool isBoxPrim0	(Tree s);
bool isBoxPrim1	(Tree s);
bool isBoxPrim2	(Tree s);
bool isBoxPrim3	(Tree s);
bool isBoxPrim4	(Tree s);
bool isBoxPrim5	(Tree s);

bool isBoxPrim0	(Tree s, prim0* p);
bool isBoxPrim1	(Tree s, prim1* p);
bool isBoxPrim2	(Tree s, prim2* p);
bool isBoxPrim3	(Tree s, prim3* p);
bool isBoxPrim4	(Tree s, prim4* p);
bool isBoxPrim5	(Tree s, prim5* p);

/*****************************************************************************
							 Foreign Functions
*****************************************************************************/

Tree boxFFun (Tree ff);
bool isBoxFFun	(Tree s);
bool isBoxFFun	(Tree s, Tree& ff);

Tree boxFConst      (Tree type, Tree name, Tree file);
bool isBoxFConst    (Tree s);
bool isBoxFConst    (Tree s, Tree& type, Tree& name, Tree& file);

Tree boxFVar      (Tree type, Tree name, Tree file);
bool isBoxFVar    (Tree s);
bool isBoxFVar    (Tree s, Tree& type, Tree& name, Tree& file);

/*****************************************************************************
							 Modules
*****************************************************************************/

Tree boxEnvironment();
bool isBoxEnvironment (Tree s);

Tree boxComponent (Tree filename);
bool isBoxComponent (Tree s, Tree& filename);

Tree boxLibrary (Tree filename);
bool isBoxLibrary (Tree s, Tree& filename);

Tree importFile(Tree filename);
bool isImportFile(Tree s, Tree& filename);

/*****************************************************************************
							 User Interface Elements
*****************************************************************************/

Tree boxButton 	 (Tree label);
bool isBoxButton (Tree s);
bool isBoxButton (Tree s, Tree& label);

Tree boxCheckbox   (Tree label);
bool isBoxCheckbox (Tree s);
bool isBoxCheckbox (Tree s, Tree& label);

Tree boxVSlider   (Tree label, Tree cur, Tree min, Tree max, Tree step);
bool isBoxVSlider (Tree s);
bool isBoxVSlider (Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

Tree boxHSlider   (Tree label, Tree cur, Tree min, Tree max, Tree step);
bool isBoxHSlider (Tree s);
bool isBoxHSlider (Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

Tree boxNumEntry   (Tree label, Tree cur, Tree min, Tree max, Tree step);
bool isBoxNumEntry (Tree s);
bool isBoxNumEntry (Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

Tree boxVGroup   (Tree label, Tree x);
bool isBoxVGroup (Tree s);
bool isBoxVGroup (Tree s, Tree& label, Tree& x);

Tree boxHGroup   (Tree label, Tree x);
bool isBoxHGroup (Tree s);
bool isBoxHGroup (Tree s, Tree& label, Tree& x);

Tree boxTGroup   (Tree label, Tree x);
bool isBoxTGroup (Tree s);
bool isBoxTGroup (Tree s, Tree& label, Tree& x);

// GUI outputs
Tree boxVBargraph   (Tree label, Tree min, Tree max);
bool isBoxVBargraph (Tree s);
bool isBoxVBargraph (Tree s, Tree& label, Tree& min, Tree& max);

Tree boxHBargraph   (Tree label, Tree min, Tree max);
bool isBoxHBargraph (Tree s);
bool isBoxHBargraph (Tree s, Tree& label, Tree& min, Tree& max);

Tree boxSoundfile(Tree label, Tree chan);
bool isBoxSoundfile(Tree s);
bool isBoxSoundfile(Tree s, Tree &label, Tree &chan);

/*****************************************************************************
							 case (pattern matching)
*****************************************************************************/
Tree boxCase		(Tree rules);
bool isBoxCase		(Tree s);
bool isBoxCase		(Tree s, Tree& rules);

Tree boxPatternMatcher		(Automaton* a, int state, Tree env, Tree origRules, Tree revParamList);
bool isBoxPatternMatcher	(Tree s);
bool isBoxPatternMatcher	(Tree s, Automaton*& a, int& state, Tree& env, Tree& origRules, Tree& revParamList);

// wrap an id into a pattern variable
Tree boxPatternVar	(Tree id);
bool isBoxPatternVar(Tree s, Tree& id);

/*****************************************************************************
******************************************************************************

							    Box Algorithms

******************************************************************************
*****************************************************************************/

// return the number of input
bool getBoxType (Tree box, int* inum, int* onum);

#endif
