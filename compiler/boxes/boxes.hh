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

#include "faust/export.h"

#include "tlib.hh"

namespace PM {
struct Automaton;
}

/*****************************************************************************
******************************************************************************

                                The Box Language

******************************************************************************
*****************************************************************************/

/*****************************************************************************
                                    Identifiers
*****************************************************************************/

Tree              boxIdent(const char* name);
LIBFAUST_API bool isBoxIdent(Tree t);
LIBFAUST_API bool isBoxIdent(Tree t, const char** name);

/*****************************************************************************
                                    Numbers
*****************************************************************************/

LIBFAUST_API Tree boxInt(int n);
LIBFAUST_API Tree boxReal(double n);

LIBFAUST_API bool isBoxInt(Tree t);
LIBFAUST_API bool isBoxReal(Tree t);

LIBFAUST_API bool isBoxInt(Tree t, int* i);
LIBFAUST_API bool isBoxReal(Tree t, double* r);

/*****************************************************************************
                                    Waveform
    waveform {1,2,3,...}
    an object with 2 outputs: the size of the waveform and the actual waveform.
    A Waveform is int if all its values are int. It is float otherwise.
*****************************************************************************/

LIBFAUST_API Tree boxWaveform(const tvec& br);
LIBFAUST_API bool isBoxWaveform(Tree t);

/*****************************************************************************
                                    Route
    route (n, m,...(si,di),...)
    a n-inputs, m-outputs routing object
*****************************************************************************/

LIBFAUST_API Tree boxRoute(Tree n, Tree m, Tree r);
LIBFAUST_API bool isBoxRoute(Tree s, Tree& n, Tree& m, Tree& r);

/*****************************************************************************
                                Wire and Cut
*****************************************************************************/

LIBFAUST_API Tree boxWire();
LIBFAUST_API Tree boxCut();

LIBFAUST_API bool isBoxWire(Tree t);
LIBFAUST_API bool isBoxCut(Tree t);

/*****************************************************************************
                        Symbolic Boxes with symbolic slots
*****************************************************************************/

Tree boxSlot(int id);
Tree boxSymbolic(Tree slot, Tree body);

LIBFAUST_API bool isBoxSlot(Tree t);
LIBFAUST_API bool isBoxSymbolic(Tree t);

LIBFAUST_API bool isBoxSlot(Tree t, int* id);
LIBFAUST_API bool isBoxSymbolic(Tree t, Tree& slot, Tree& body);

/*****************************************************************************
                              Composition of Boxes
*****************************************************************************/

LIBFAUST_API Tree boxSeq(Tree x, Tree y);
LIBFAUST_API Tree boxPar(Tree x, Tree y);
LIBFAUST_API Tree boxRec(Tree x, Tree y);
LIBFAUST_API Tree boxSplit(Tree x, Tree y);
LIBFAUST_API Tree boxMerge(Tree x, Tree y);

LIBFAUST_API bool isBoxSeq(Tree t, Tree& x, Tree& y);
LIBFAUST_API bool isBoxPar(Tree t, Tree& x, Tree& y);
LIBFAUST_API bool isBoxRec(Tree t, Tree& x, Tree& y);
LIBFAUST_API bool isBoxSplit(Tree t, Tree& x, Tree& y);
LIBFAUST_API bool isBoxMerge(Tree t, Tree& x, Tree& y);

/*****************************************************************************
                        Algorithmic Composition of Boxes
*****************************************************************************/

Tree boxIPar(Tree x, Tree y, Tree z);
Tree boxISeq(Tree x, Tree y, Tree z);
Tree boxISum(Tree x, Tree y, Tree z);
Tree boxIProd(Tree x, Tree y, Tree z);

LIBFAUST_API bool isBoxIPar(Tree t, Tree& x, Tree& y, Tree& z);
LIBFAUST_API bool isBoxISeq(Tree t, Tree& x, Tree& y, Tree& z);
LIBFAUST_API bool isBoxISum(Tree t, Tree& x, Tree& y, Tree& z);
LIBFAUST_API bool isBoxIProd(Tree t, Tree& x, Tree& y, Tree& z);

/*****************************************************************************
                        Static information on Boxes
*****************************************************************************/

Tree boxInputs(Tree x);
Tree boxOutputs(Tree x);

LIBFAUST_API bool isBoxInputs(Tree t, Tree& x);
LIBFAUST_API bool isBoxOutputs(Tree t, Tree& x);

/*****************************************************************************
                              Lambda-Calculus of Boxes
*****************************************************************************/

Tree buildBoxAbstr(Tree x, Tree y);
Tree buildBoxModulation(Tree x, Tree y);
Tree buildBoxAppl(Tree x, Tree y);

Tree boxAbstr(Tree x, Tree y);
Tree boxModulation(Tree x, Tree y);
Tree boxAppl(Tree x, Tree y);

LIBFAUST_API bool isBoxAbstr(Tree t);
LIBFAUST_API bool isBoxModulation(Tree t);
LIBFAUST_API bool isBoxAppl(Tree t);

LIBFAUST_API bool isBoxAbstr(Tree t, Tree& x, Tree& y);
LIBFAUST_API bool isBoxModulation(Tree t, Tree& x, Tree& y);
LIBFAUST_API bool isBoxAppl(Tree t, Tree& x, Tree& y);

Tree closure(Tree abstr, Tree genv, Tree vis, Tree lenv);

bool isClosure(Tree t, Tree& abstr, Tree& genv, Tree& vis, Tree& lenv);

// for foo(x,y).faa expressions
Tree              boxAccess(Tree exp, Tree id);
LIBFAUST_API bool isBoxAccess(Tree t, Tree& exp, Tree& id);

/*****************************************************************************
                        Boxes with local definitions
*****************************************************************************/

Tree              boxWithLocalDef(Tree body, Tree ldef);
LIBFAUST_API bool isBoxWithLocalDef(Tree t, Tree& body, Tree& ldef);
Tree              boxWithRecDef(Tree body, Tree ldef, Tree ldef2);

/*****************************************************************************
                        Modification of local definitions
*****************************************************************************/

Tree              boxModifLocalDef(Tree body, Tree ldef);
LIBFAUST_API bool isBoxModifLocalDef(Tree t, Tree& body, Tree& ldef);

/*****************************************************************************
                             Error Box
*****************************************************************************/

Tree              boxError();
LIBFAUST_API bool isBoxError(Tree t);

/*****************************************************************************
                             Primitive Boxes (n -> 1)
*****************************************************************************/

typedef Tree (*prim0)();
typedef Tree (*prim1)(Tree x);
typedef Tree (*prim2)(Tree x, Tree y);
typedef Tree (*prim3)(Tree x, Tree y, Tree z);
typedef Tree (*prim4)(Tree w, Tree x, Tree y, Tree z);
typedef Tree (*prim5)(Tree v, Tree w, Tree x, Tree y, Tree z);

LIBFAUST_API Tree boxPrim0(prim0 foo);
LIBFAUST_API Tree boxPrim1(prim1 foo);
LIBFAUST_API Tree boxPrim2(prim2 foo);
LIBFAUST_API Tree boxPrim3(prim3 foo);
LIBFAUST_API Tree boxPrim4(prim4 foo);
LIBFAUST_API Tree boxPrim5(prim5 foo);

LIBFAUST_API bool isBoxPrim0(Tree s);
LIBFAUST_API bool isBoxPrim1(Tree s);
LIBFAUST_API bool isBoxPrim2(Tree s);
LIBFAUST_API bool isBoxPrim3(Tree s);
LIBFAUST_API bool isBoxPrim4(Tree s);
LIBFAUST_API bool isBoxPrim5(Tree s);

LIBFAUST_API bool isBoxPrim0(Tree s, prim0* p);
LIBFAUST_API bool isBoxPrim1(Tree s, prim1* p);
LIBFAUST_API bool isBoxPrim2(Tree s, prim2* p);
LIBFAUST_API bool isBoxPrim3(Tree s, prim3* p);
LIBFAUST_API bool isBoxPrim4(Tree s, prim4* p);
LIBFAUST_API bool isBoxPrim5(Tree s, prim5* p);

/*****************************************************************************
                             Foreign Functions
*****************************************************************************/

LIBFAUST_API Tree boxFFun(Tree ff);
LIBFAUST_API bool isBoxFFun(Tree s);
LIBFAUST_API bool isBoxFFun(Tree s, Tree& ff);

LIBFAUST_API Tree boxFConst(Tree type, Tree name, Tree file);
LIBFAUST_API bool isBoxFConst(Tree s);
LIBFAUST_API bool isBoxFConst(Tree s, Tree& type, Tree& name, Tree& file);

LIBFAUST_API Tree boxFVar(Tree type, Tree name, Tree file);
LIBFAUST_API bool isBoxFVar(Tree s);
LIBFAUST_API bool isBoxFVar(Tree s, Tree& type, Tree& name, Tree& file);

/*****************************************************************************
                             Modules
*****************************************************************************/

Tree              boxEnvironment();
LIBFAUST_API bool isBoxEnvironment(Tree s);

Tree              boxComponent(Tree filename);
LIBFAUST_API bool isBoxComponent(Tree s, Tree& filename);

Tree              boxLibrary(Tree filename);
LIBFAUST_API bool isBoxLibrary(Tree s, Tree& filename);

Tree importFile(Tree filename);
bool isImportFile(Tree s, Tree& filename);

/*****************************************************************************
                             User Interface Elements
*****************************************************************************/

// GUI inputs
LIBFAUST_API Tree boxButton(Tree label);
LIBFAUST_API bool isBoxButton(Tree s);
LIBFAUST_API bool isBoxButton(Tree s, Tree& label);

LIBFAUST_API Tree boxCheckbox(Tree label);
LIBFAUST_API bool isBoxCheckbox(Tree s);
LIBFAUST_API bool isBoxCheckbox(Tree s, Tree& label);

LIBFAUST_API Tree boxVSlider(Tree label, Tree cur, Tree min, Tree max, Tree step);
LIBFAUST_API bool isBoxVSlider(Tree s);
LIBFAUST_API bool isBoxVSlider(Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

LIBFAUST_API Tree boxHSlider(Tree label, Tree cur, Tree min, Tree max, Tree step);
LIBFAUST_API bool isBoxHSlider(Tree s);
LIBFAUST_API bool isBoxHSlider(Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

LIBFAUST_API Tree boxNumEntry(Tree label, Tree cur, Tree min, Tree max, Tree step);
LIBFAUST_API bool isBoxNumEntry(Tree s);
LIBFAUST_API bool isBoxNumEntry(Tree s, Tree& label, Tree& cur, Tree& min, Tree& max, Tree& step);

// GUI outputs
LIBFAUST_API Tree boxVBargraph(Tree label, Tree min, Tree max);
LIBFAUST_API bool isBoxVBargraph(Tree s);
LIBFAUST_API bool isBoxVBargraph(Tree s, Tree& label, Tree& min, Tree& max);

LIBFAUST_API Tree boxHBargraph(Tree label, Tree min, Tree max);
LIBFAUST_API bool isBoxHBargraph(Tree s);
LIBFAUST_API bool isBoxHBargraph(Tree s, Tree& label, Tree& min, Tree& max);

// Groups
LIBFAUST_API Tree boxVGroup(Tree label, Tree x);
LIBFAUST_API bool isBoxVGroup(Tree s);
LIBFAUST_API bool isBoxVGroup(Tree s, Tree& label, Tree& x);

LIBFAUST_API Tree boxHGroup(Tree label, Tree x);
LIBFAUST_API bool isBoxHGroup(Tree s);
LIBFAUST_API bool isBoxHGroup(Tree s, Tree& label, Tree& x);

LIBFAUST_API Tree boxTGroup(Tree label, Tree x);
LIBFAUST_API bool isBoxTGroup(Tree s);
LIBFAUST_API bool isBoxTGroup(Tree s, Tree& label, Tree& x);

LIBFAUST_API Tree boxSoundfile(Tree label, Tree chan);
LIBFAUST_API bool isBoxSoundfile(Tree s);
LIBFAUST_API bool isBoxSoundfile(Tree s, Tree& label, Tree& chan);

/*****************************************************************************
                             Case (pattern matching)
*****************************************************************************/
Tree              boxCase(Tree rules);
LIBFAUST_API bool isBoxCase(Tree s);
LIBFAUST_API bool isBoxCase(Tree s, Tree& rules);

Tree boxPatternMatcher(PM::Automaton* a, int state, Tree env, Tree origRules, Tree revParamList);
bool isBoxPatternMatcher(Tree s);
bool isBoxPatternMatcher(Tree s, PM::Automaton*& a, int& state, Tree& env, Tree& origRules, Tree& revParamList);

// wrap an id into a pattern variable
Tree boxPatternVar(Tree id);
bool isBoxPatternVar(Tree s, Tree& id);

/*****************************************************************************
                             Metadata (pattern matching)
*****************************************************************************/
Tree              boxMetadata(Tree exp, Tree mdlist);
LIBFAUST_API bool isBoxMetadata(Tree s, Tree& exp, Tree& mdlist);

/*****************************************************************************
******************************************************************************

                                Box Algorithms

******************************************************************************
*****************************************************************************/

// Return the number of inputs and outputs
LIBFAUST_API bool getBoxType(Tree box, int* inum, int* onum);

/**
 * Produces "1 input" or "n inputs" according to n
 * \param n the number of inputs
 * \return the corresponding string
 */
inline std::string inputs(int n)
{
    return std::to_string(n) + ((n == 1) ? " input" : " inputs");
}

/**
 * Produces "1 output" or "n outputs" according to n
 * \param n the number of outputs
 * \return the corresponding string
 */
inline std::string outputs(int n)
{
    return std::to_string(n) + ((n == 1) ? " output" : " outputs");
}

#endif
