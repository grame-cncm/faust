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
******************************************************************************

                                The Box Language

******************************************************************************
*****************************************************************************/

/**\file boxes.cpp
 * \author Yann Orlarey
 * \version 1.0
 * \date 2003
 * \brief Implementation of block diagram expressions.
 *  Boxes are created using five main connection operations : sequential (:),
 *  parallel (,), split (<:), merge (:>), and recursive (~).
 */

#include "boxes.hh"
#include <stdio.h>
#include <string.h>
#include "exception.hh"
#include "global.hh"
#include "prim2.hh"
#include "xtended.hh"

using namespace std;

/*****************************************************************************
                                    Identifiers
*****************************************************************************/

Tree boxIdent(const char* name)
{
    return tree(gGlobal->BOXIDENT, tree(symbol(name)));
}
LIBFAUST_API bool isBoxIdent(Tree t)
{
    return t->node() == Node(gGlobal->BOXIDENT);
}
LIBFAUST_API bool isBoxIdent(Tree t0, const char** str)
{
    Tree t1;
    Sym  s;
    if (isTree(t0, gGlobal->BOXIDENT, t1) && isSym(t1->node(), &s)) {
        *str = name(s);
        return true;
    } else {
        return false;
    }
}

/*****************************************************************************
                                    Numbers
*****************************************************************************/

LIBFAUST_API Tree boxInt(int n)
{
    return tree(n);
}
LIBFAUST_API Tree boxReal(double n)
{
    return tree(n);
}

LIBFAUST_API bool isBoxInt(Tree t)
{
    return isInt(t->node());
}
LIBFAUST_API bool isBoxReal(Tree t)
{
    return isDouble(t->node());
}

LIBFAUST_API bool isBoxInt(Tree t, int* i)
{
    return isInt(t->node(), i);
}
LIBFAUST_API bool isBoxReal(Tree t, double* r)
{
    return isDouble(t->node(), r);
}

/*****************************************************************************
                             Waveform
*****************************************************************************/

LIBFAUST_API Tree boxWaveform(const tvec& br)
{
    return tree(gGlobal->BOXWAVEFORM, br);
}

LIBFAUST_API bool isBoxWaveform(Tree s)
{
    return isTree(s, gGlobal->BOXWAVEFORM);
}

/*****************************************************************************
                             Route
*****************************************************************************/

LIBFAUST_API Tree boxRoute(Tree n, Tree m, Tree r)
{
    return tree(gGlobal->BOXROUTE, n, m, r);
}

LIBFAUST_API bool isBoxRoute(Tree s, Tree& n, Tree& m, Tree& r)
{
    return isTree(s, gGlobal->BOXROUTE, n, m, r);
}

/*****************************************************************************
                                Wire and Cut
*****************************************************************************/

LIBFAUST_API Tree boxCut()
{
    return tree(gGlobal->BOXCUT);
}
LIBFAUST_API bool isBoxCut(Tree t)
{
    return isTree(t, gGlobal->BOXCUT);
}

LIBFAUST_API Tree boxWire()
{
    return tree(gGlobal->BOXWIRE);
}
LIBFAUST_API bool isBoxWire(Tree t)
{
    return isTree(t, gGlobal->BOXWIRE);
}

/*****************************************************************************
                        Symbolic Boxes with symbolic slots
*****************************************************************************/

Tree boxSlot(int id)
{
    return tree(gGlobal->BOXSLOT, tree(id));
}
LIBFAUST_API bool isBoxSlot(Tree t)
{
    Tree w;
    return isTree(t, gGlobal->BOXSLOT, w);
}
LIBFAUST_API bool isBoxSlot(Tree t, int* id)
{
    Tree w;
    return isTree(t, gGlobal->BOXSLOT, w) && isInt(w->node(), id);
}

Tree boxSymbolic(Tree slot, Tree body)
{
    return tree(gGlobal->BOXSYMBOLIC, slot, body);
}
LIBFAUST_API bool isBoxSymbolic(Tree t)
{
    Tree slot, body;
    return isTree(t, gGlobal->BOXSYMBOLIC, slot, body);
}
LIBFAUST_API bool isBoxSymbolic(Tree t, Tree& slot, Tree& body)
{
    return isTree(t, gGlobal->BOXSYMBOLIC, slot, body);
}

/*****************************************************************************
                              Composition of Boxes
*****************************************************************************/

LIBFAUST_API Tree boxSeq(Tree x, Tree y)
{
    return tree(gGlobal->BOXSEQ, x, y);
}
LIBFAUST_API bool isBoxSeq(Tree t, Tree& x, Tree& y)
{
    return isTree(t, gGlobal->BOXSEQ, x, y);
}

LIBFAUST_API Tree boxPar(Tree x, Tree y)
{
    return tree(gGlobal->BOXPAR, x, y);
}
LIBFAUST_API bool isBoxPar(Tree t, Tree& x, Tree& y)
{
    return isTree(t, gGlobal->BOXPAR, x, y);
}

LIBFAUST_API Tree boxRec(Tree x, Tree y)
{
    return tree(gGlobal->BOXREC, x, y);
}
LIBFAUST_API bool isBoxRec(Tree t, Tree& x, Tree& y)
{
    return isTree(t, gGlobal->BOXREC, x, y);
}

LIBFAUST_API Tree boxSplit(Tree x, Tree y)
{
    return tree(gGlobal->BOXSPLIT, x, y);
}
LIBFAUST_API bool isBoxSplit(Tree t, Tree& x, Tree& y)
{
    return isTree(t, gGlobal->BOXSPLIT, x, y);
}

LIBFAUST_API Tree boxMerge(Tree x, Tree y)
{
    return tree(gGlobal->BOXMERGE, x, y);
}
LIBFAUST_API bool isBoxMerge(Tree t, Tree& x, Tree& y)
{
    return isTree(t, gGlobal->BOXMERGE, x, y);
}

/*****************************************************************************
                        Algorithmic Composition of Boxes
*****************************************************************************/

Tree boxIPar(Tree x, Tree y, Tree z)
{
    return tree(gGlobal->BOXIPAR, x, y, z);
}
Tree boxISeq(Tree x, Tree y, Tree z)
{
    return tree(gGlobal->BOXISEQ, x, y, z);
}
Tree boxISum(Tree x, Tree y, Tree z)
{
    return tree(gGlobal->BOXISUM, x, y, z);
}
Tree boxIProd(Tree x, Tree y, Tree z)
{
    return tree(gGlobal->BOXIPROD, x, y, z);
}

LIBFAUST_API bool isBoxIPar(Tree t, Tree& x, Tree& y, Tree& z)
{
    return isTree(t, gGlobal->BOXIPAR, x, y, z);
}
LIBFAUST_API bool isBoxISeq(Tree t, Tree& x, Tree& y, Tree& z)
{
    return isTree(t, gGlobal->BOXISEQ, x, y, z);
}
LIBFAUST_API bool isBoxISum(Tree t, Tree& x, Tree& y, Tree& z)
{
    return isTree(t, gGlobal->BOXISUM, x, y, z);
}
LIBFAUST_API bool isBoxIProd(Tree t, Tree& x, Tree& y, Tree& z)
{
    return isTree(t, gGlobal->BOXIPROD, x, y, z);
}

/*****************************************************************************
                        Static information on Boxes
*****************************************************************************/

Tree boxInputs(Tree x)
{
    return tree(gGlobal->BOXINPUTS, x);
}
Tree boxOutputs(Tree x)
{
    return tree(gGlobal->BOXOUTPUTS, x);
}

LIBFAUST_API bool isBoxInputs(Tree t, Tree& x)
{
    return isTree(t, gGlobal->BOXINPUTS, x);
}
LIBFAUST_API bool isBoxOutputs(Tree t, Tree& x)
{
    return isTree(t, gGlobal->BOXOUTPUTS, x);
}

/*****************************************************************************
                              Lambda-Calculus of Boxes
*****************************************************************************/

Tree boxAbstr(Tree x, Tree y)
{
    return tree(gGlobal->BOXABSTR, x, y);
}
Tree boxAppl(Tree x, Tree y)
{
    return tree(gGlobal->BOXAPPL, x, y);
}

LIBFAUST_API bool isBoxAbstr(Tree t)
{
    return t->node() == Node(gGlobal->BOXABSTR);
}
LIBFAUST_API bool isBoxAppl(Tree t)
{
    return t->node() == Node(gGlobal->BOXAPPL);
}

LIBFAUST_API bool isBoxAbstr(Tree t, Tree& x, Tree& y)
{
    return isTree(t, gGlobal->BOXABSTR, x, y);
}
LIBFAUST_API bool isBoxAppl(Tree t, Tree& x, Tree& y)
{
    return isTree(t, gGlobal->BOXAPPL, x, y);
}

Tree buildBoxAbstr(Tree largs, Tree body)
{
    if (isNil(largs)) {
        return body;
    } else {
        return buildBoxAbstr(tl(largs), boxAbstr(hd(largs), body));
    }
}

#if 0
Tree buildBoxAppl(Tree fun, Tree revarglist)
{
	if (isNil(revarglist)) {
		return fun;
	} else {
		return boxAppl(buildBoxAppl(fun, tl(revarglist)), hd(revarglist));
	}
}
#else

Tree buildBoxAppl(Tree fun, Tree revarglist)
{
    if (isNil(revarglist)) {
        cerr << "ASSERT : buildBoxAppl called with null revarglist\n";
        faustassert(false);
    }
    return boxAppl(fun, revarglist);
}
#endif

Tree closure(Tree abstr, Tree genv, Tree vis, Tree lenv)
{
    return tree(gGlobal->CLOSURE, abstr, genv, vis, lenv);
}

bool isClosure(Tree t, Tree& abstr, Tree& genv, Tree& vis, Tree& lenv)
{
    return isTree(t, gGlobal->CLOSURE, abstr, genv, vis, lenv);
}

Tree boxError()
{
    return tree(gGlobal->BOXERROR);
}

LIBFAUST_API bool isBoxError(Tree t)
{
    return isTree(t, gGlobal->BOXERROR);
}

Tree boxAccess(Tree exp, Tree id)
{
    return tree(gGlobal->BOXACCESS, exp, id);
}
LIBFAUST_API bool isBoxAccess(Tree t, Tree& exp, Tree& id)
{
    return isTree(t, gGlobal->BOXACCESS, exp, id);
}

/*****************************************************************************
                        Boxes with local definitions
*****************************************************************************/

Tree boxWithLocalDef(Tree body, Tree ldef)
{
    return tree(gGlobal->BOXWITHLOCALDEF, body, ldef);
}
LIBFAUST_API bool isBoxWithLocalDef(Tree t, Tree& body, Tree& ldef)
{
    return isTree(t, gGlobal->BOXWITHLOCALDEF, body, ldef);
}

/*****************************************************************************
                        Boxes with recursive definitions
 *****************************************************************************/

// def2names transforms a liste of definition (name.expression) into a list of name
static Tree def2names(Tree ldef)
{
    if (isNil(ldef)) {
        return gGlobal->nil;
    } else {
        Tree def = hd(ldef);
        return cons(hd(def), def2names(tl(ldef)));
    }
}

// def2exp transforms a list of definition (name.expression) into a list of expressions
static Tree def2exp(Tree ldef)
{
    if (isNil(ldef)) {
        return gGlobal->nil;
    } else {
        Tree def = hd(ldef);
        return cons(tl(def), def2exp(tl(ldef)));
    }
}

// makeBus(3) => "_,_,_"
static Tree makeBus(int n)
{
    return (n <= 1) ? boxWire() : boxPar(boxWire(), makeBus(n - 1));
}

// makeParList((a,b,d)) => "a,b,c"
static Tree makeParList(Tree lexp)
{
    Tree l2 = tl(lexp);
    if (isNil(l2)) {
        return hd(lexp);
    } else {
        return boxPar(hd(lexp), makeParList(l2));
    }
}

// makeBoxAbstr(largs,body) => \(lnames).(body)
static Tree makeBoxAbstr(Tree largs, Tree body)
{
    if (isNil(largs)) {
        return body;
    } else {
        return boxAbstr(hd(largs), makeBoxAbstr(tl(largs), body));
    }
}

// makeSelector(5,2) => "!,!,_,!,!"
static Tree makeSelector(int n, int i)
{
    Tree op = (i == 0) ? boxWire() : boxCut();
    return (n == 1) ? op : boxPar(op, makeSelector(n - 1, i - 1));
}

// defines each symbol si of lnames as => "si = RECURSIVEBODY : select(n,i);"
static Tree makeRecProjectionsList(int n, int i, Tree lnames, Tree ldef)
{
    if (i == n) {
        return ldef;
    } else {
        Tree sel = boxSeq(gGlobal->LETRECBODY, makeSelector(n, i));
        return cons(cons(hd(lnames), sel), makeRecProjectionsList(n, i + 1, tl(lnames), ldef));
    }
}

// buildRecursiveBodyDef(n,lnames,lexp) => "RECURSIVEBODY = \(lnames).(lexp) ~ bus(n);"
static Tree buildRecursiveBodyDef(int n, Tree lnames, Tree lexp, Tree ldef2)
{
    if (ldef2 == gGlobal->nil) {
        return cons(gGlobal->LETRECBODY, boxRec(makeBoxAbstr(lnames, makeParList(lexp)), makeBus(n)));
    } else {
        return cons(gGlobal->LETRECBODY,
                    boxRec(makeBoxAbstr(lnames, boxWithLocalDef(makeParList(lexp), ldef2)), makeBus(n)));
    }
}

//----------------------------------------------------------------------------
// Transform a letrec expression into a with expression. The 'where' part
// is optional. It allows for common local definitions. It is translated into
// a with{} inside the body of the abstraction. Only signals x and y are
// visible outside the letrec. The foo definition after the where is not visible
// outside.
//
// process = x * y letrec {
//  'x = foo(x,y);
//  'y = foo(y,x);
//  where
//    foo(u, v) = u - v;
//  };
//----------------------------------------------------------------------------
Tree boxWithRecDef(Tree body, Tree ldef, Tree ldef2)
{
    // cout << "list of recursive definitions : " << *ldef << endl;
    Tree lnames = def2names(ldef);
    Tree lexp   = def2exp(ldef);
    int  n      = len(ldef);

    Tree rdef = buildRecursiveBodyDef(n, lnames, lexp, ldef2);
    Tree lrp  = makeRecProjectionsList(n, 0, lnames, gGlobal->nil);
    Tree w    = boxWithLocalDef(body, cons(rdef, lrp));
    // cerr << "boxWithRecDef(" << boxpp(body) << ',' << *ldef << ") -> " << boxpp(w) << endl;
    return w;
}

/*****************************************************************************
                        Boxes modif local definitions
*****************************************************************************/

Tree boxModifLocalDef(Tree body, Tree ldef)
{
    return tree(gGlobal->BOXMODIFLOCALDEF, body, ldef);
}
bool isBoxModifLocalDef(Tree t, Tree& body, Tree& ldef)
{
    return isTree(t, gGlobal->BOXMODIFLOCALDEF, body, ldef);
}

/*****************************************************************************
                             Modules
*****************************************************************************/

Tree boxEnvironment()
{
    return tree(gGlobal->BOXENVIRONMENT);
}
LIBFAUST_API bool isBoxEnvironment(Tree s)
{
    return isTree(s, gGlobal->BOXENVIRONMENT);
}

Tree boxComponent(Tree filename)
{
    return tree(gGlobal->BOXCOMPONENT, filename);
}
LIBFAUST_API bool isBoxComponent(Tree s, Tree& filename)
{
    return isTree(s, gGlobal->BOXCOMPONENT, filename);
}

Tree boxLibrary(Tree filename)
{
    return tree(gGlobal->BOXLIBRARY, filename);
}
LIBFAUST_API bool isBoxLibrary(Tree s, Tree& filename)
{
    return isTree(s, gGlobal->BOXLIBRARY, filename);
}

Tree importFile(Tree filename)
{
    return tree(gGlobal->IMPORTFILE, filename);
}
bool isImportFile(Tree s, Tree& filename)
{
    return isTree(s, gGlobal->IMPORTFILE, filename);
}

/*****************************************************************************
                            External Primitive Boxes (n -> 1)
*****************************************************************************/

LIBFAUST_API Tree boxPrim0(prim0 foo)
{
    return tree(gGlobal->BOXPRIM0, tree((void*)foo));
}
LIBFAUST_API bool isBoxPrim0(Tree s)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM0, t);
}
LIBFAUST_API bool isBoxPrim0(Tree s, prim0* p)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM0, t) && isPointer(t->node(), (void**)p);
}

LIBFAUST_API Tree boxPrim1(prim1 foo)
{
    return tree(gGlobal->BOXPRIM1, tree((void*)foo));
}
LIBFAUST_API bool isBoxPrim1(Tree s)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM1, t);
}
LIBFAUST_API bool isBoxPrim1(Tree s, prim1* p)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM1, t) && isPointer(t->node(), (void**)p);
}

LIBFAUST_API Tree boxPrim2(prim2 foo)
{
    return tree(gGlobal->BOXPRIM2, tree((void*)foo));
}
LIBFAUST_API bool isBoxPrim2(Tree s)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM2, t);
}
LIBFAUST_API bool isBoxPrim2(Tree s, prim2* p)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM2, t) && isPointer(t->node(), (void**)p);
}

LIBFAUST_API Tree boxPrim3(prim3 foo)
{
    return tree(gGlobal->BOXPRIM3, tree((void*)foo));
}
LIBFAUST_API bool isBoxPrim3(Tree s)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM3, t);
}
LIBFAUST_API bool isBoxPrim3(Tree s, prim3* p)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM3, t) && isPointer(t->node(), (void**)p);
}

LIBFAUST_API Tree boxPrim4(prim4 foo)
{
    return tree(gGlobal->BOXPRIM4, tree((void*)foo));
}
LIBFAUST_API bool isBoxPrim4(Tree s)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM4, t);
}
LIBFAUST_API bool isBoxPrim4(Tree s, prim4* p)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM4, t) && isPointer(t->node(), (void**)p);
}

LIBFAUST_API Tree boxPrim5(prim5 foo)
{
    return tree(gGlobal->BOXPRIM5, tree((void*)foo));
}
LIBFAUST_API bool isBoxPrim5(Tree s)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM5, t);
}
LIBFAUST_API bool isBoxPrim5(Tree s, prim5* p)
{
    Tree t;
    return isTree(s, gGlobal->BOXPRIM5, t) && isPointer(t->node(), (void**)p);
}

/*****************************************************************************
                             Foreign Functions
*****************************************************************************/

LIBFAUST_API Tree boxFFun(Tree ff)
{
    return tree(gGlobal->BOXFFUN, ff);
}
LIBFAUST_API bool isBoxFFun(Tree s)
{
    Tree ff;
    return isTree(s, gGlobal->BOXFFUN, ff);
}
LIBFAUST_API bool isBoxFFun(Tree s, Tree& ff)
{
    return isTree(s, gGlobal->BOXFFUN, ff);
}

LIBFAUST_API Tree boxFConst(Tree type, Tree name, Tree file)
{
    return tree(gGlobal->BOXFCONST, type, name, file);
}
LIBFAUST_API bool isBoxFConst(Tree s)
{
    Tree t, n, f;
    return isTree(s, gGlobal->BOXFCONST, t, n, f);
}
LIBFAUST_API bool isBoxFConst(Tree s, Tree& type, Tree& name, Tree& file)
{
    return isTree(s, gGlobal->BOXFCONST, type, name, file);
}

LIBFAUST_API Tree boxFVar(Tree type, Tree name, Tree file)
{
    return tree(gGlobal->BOXFVAR, type, name, file);
}
LIBFAUST_API bool isBoxFVar(Tree s)
{
    Tree t, n, f;
    return isTree(s, gGlobal->BOXFVAR, t, n, f);
}
LIBFAUST_API bool isBoxFVar(Tree s, Tree& type, Tree& name, Tree& file)
{
    return isTree(s, gGlobal->BOXFVAR, type, name, file);
}

/*****************************************************************************
                             User Interface Elements
*****************************************************************************/

LIBFAUST_API Tree boxButton(Tree lbl)
{
    return tree(gGlobal->BOXBUTTON, lbl);
}
LIBFAUST_API bool isBoxButton(Tree s)
{
    Tree lbl;
    return isTree(s, gGlobal->BOXBUTTON, lbl);
}
LIBFAUST_API bool isBoxButton(Tree s, Tree& lbl)
{
    return isTree(s, gGlobal->BOXBUTTON, lbl);
}

LIBFAUST_API Tree boxCheckbox(Tree lbl)
{
    return tree(gGlobal->BOXCHECKBOX, lbl);
}
LIBFAUST_API bool isBoxCheckbox(Tree s)
{
    Tree lbl;
    return isTree(s, gGlobal->BOXCHECKBOX, lbl);
}
LIBFAUST_API bool isBoxCheckbox(Tree s, Tree& lbl)
{
    return isTree(s, gGlobal->BOXCHECKBOX, lbl);
}

LIBFAUST_API Tree boxHSlider(Tree lbl, Tree cur, Tree min, Tree max, Tree step)
{
    return tree(gGlobal->BOXHSLIDER, lbl, list4(cur, min, max, step));
}
LIBFAUST_API bool isBoxHSlider(Tree s)
{
    Tree lbl, params;
    return isTree(s, gGlobal->BOXHSLIDER, lbl, params);
}

LIBFAUST_API bool isBoxHSlider(Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
    Tree params;
    if (isTree(s, gGlobal->BOXHSLIDER, lbl, params)) {
        cur  = nth(params, 0);
        min  = nth(params, 1);
        max  = nth(params, 2);
        step = nth(params, 3);
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API Tree boxVSlider(Tree lbl, Tree cur, Tree min, Tree max, Tree step)
{
    return tree(gGlobal->BOXVSLIDER, lbl, list4(cur, min, max, step));
}
LIBFAUST_API bool isBoxVSlider(Tree s)
{
    Tree lbl, params;
    return isTree(s, gGlobal->BOXVSLIDER, lbl, params);
}

LIBFAUST_API bool isBoxVSlider(Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
    Tree params;
    if (isTree(s, gGlobal->BOXVSLIDER, lbl, params)) {
        cur  = nth(params, 0);
        min  = nth(params, 1);
        max  = nth(params, 2);
        step = nth(params, 3);
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API Tree boxNumEntry(Tree lbl, Tree cur, Tree min, Tree max, Tree step)
{
    return tree(gGlobal->BOXNUMENTRY, lbl, list4(cur, min, max, step));
}
LIBFAUST_API bool isBoxNumEntry(Tree s)
{
    Tree lbl, params;
    return isTree(s, gGlobal->BOXNUMENTRY, lbl, params);
}

LIBFAUST_API bool isBoxNumEntry(Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
    Tree params;
    if (isTree(s, gGlobal->BOXNUMENTRY, lbl, params)) {
        cur  = nth(params, 0);
        min  = nth(params, 1);
        max  = nth(params, 2);
        step = nth(params, 3);
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API Tree boxHGroup(Tree lbl, Tree x)
{
    return tree(gGlobal->BOXHGROUP, lbl, x);
}
LIBFAUST_API bool isBoxHGroup(Tree s)
{
    Tree lbl, x;
    return isTree(s, gGlobal->BOXHGROUP, lbl, x);
}
LIBFAUST_API bool isBoxHGroup(Tree s, Tree& lbl, Tree& x)
{
    return isTree(s, gGlobal->BOXHGROUP, lbl, x);
}

LIBFAUST_API Tree boxVGroup(Tree lbl, Tree x)
{
    return tree(gGlobal->BOXVGROUP, lbl, x);
}
LIBFAUST_API bool isBoxVGroup(Tree s)
{
    Tree lbl, x;
    return isTree(s, gGlobal->BOXVGROUP, lbl, x);
}
LIBFAUST_API bool isBoxVGroup(Tree s, Tree& lbl, Tree& x)
{
    return isTree(s, gGlobal->BOXVGROUP, lbl, x);
}

LIBFAUST_API Tree boxTGroup(Tree lbl, Tree x)
{
    return tree(gGlobal->BOXTGROUP, lbl, x);
}
LIBFAUST_API bool isBoxTGroup(Tree s)
{
    Tree lbl, x;
    return isTree(s, gGlobal->BOXTGROUP, lbl, x);
}
LIBFAUST_API bool isBoxTGroup(Tree s, Tree& lbl, Tree& x)
{
    return isTree(s, gGlobal->BOXTGROUP, lbl, x);
}

LIBFAUST_API Tree boxHBargraph(Tree lbl, Tree min, Tree max)
{
    return tree(gGlobal->BOXHBARGRAPH, lbl, min, max);
}
LIBFAUST_API bool isBoxHBargraph(Tree s)
{
    Tree lbl, min, max;
    return isTree(s, gGlobal->BOXHBARGRAPH, lbl, min, max);
}
LIBFAUST_API bool isBoxHBargraph(Tree s, Tree& lbl, Tree& min, Tree& max)
{
    return isTree(s, gGlobal->BOXHBARGRAPH, lbl, min, max);
}

LIBFAUST_API Tree boxVBargraph(Tree lbl, Tree min, Tree max)
{
    return tree(gGlobal->BOXVBARGRAPH, lbl, min, max);
}
LIBFAUST_API bool isBoxVBargraph(Tree s)
{
    Tree lbl, min, max;
    return isTree(s, gGlobal->BOXVBARGRAPH, lbl, min, max);
}
LIBFAUST_API bool isBoxVBargraph(Tree s, Tree& lbl, Tree& min, Tree& max)
{
    return isTree(s, gGlobal->BOXVBARGRAPH, lbl, min, max);
}

LIBFAUST_API Tree boxSoundfile(Tree lbl, Tree chan)
{
    return tree(gGlobal->BOXSOUNDFILE, lbl, chan);
}

LIBFAUST_API bool isBoxSoundfile(Tree s)
{
    Tree label;
    Tree chan;
    return isTree(s, gGlobal->BOXSOUNDFILE, label, chan);
}

LIBFAUST_API bool isBoxSoundfile(Tree s, Tree& label, Tree& chan)
{
    return isTree(s, gGlobal->BOXSOUNDFILE, label, chan);
}

/*****************************************************************************
                             Metadata (pattern matching)
*****************************************************************************/
Tree boxMetadata(Tree exp, Tree mdlist)
{
    return tree(gGlobal->BOXMETADATA, exp, mdlist);
}

LIBFAUST_API bool isBoxMetadata(Tree s, Tree& exp, Tree& mdlist)
{
    return isTree(s, gGlobal->BOXMETADATA, exp, mdlist);
}

/*****************************************************************************
                             Pattern matching case
*****************************************************************************/

/**
 * Prepare a "pattern" by replacing variables x by special
 * pattern variables ?x.
 *
 * P[x]     -> ?x
 * P[x(e)]  -> x(P[e])
 * P[e(f)]  -> P[e](P[f])
 * P[e:f]   -> P[e]:P[f]
 * etc.
 */
static Tree preparePattern(Tree box)
{
    //    cerr << "preparePattern(" << boxpp(box) << ")" << endl;

    int    id;
    double r;
    prim0  p0;
    prim1  p1;
    prim2  p2;
    prim3  p3;
    prim4  p4;
    prim5  p5;

    Tree t1, t2, t3, ff, label, cur, min, max, step, type, name, file, arg, body, fun, args, ldef, slot, ident, rules;

    xtended* xt = (xtended*)getUserData(box);

    // Primitive elements
    if (xt)
        return box;
    else if (isBoxIdent(box))
        return boxPatternVar(box);
    else if (isBoxAppl(box, fun, args)) {
        if (isBoxIdent(fun))
            return boxAppl(fun, lmap(preparePattern, args));
        else
            return boxAppl(preparePattern(fun), lmap(preparePattern, args));
    } else if (isBoxAbstr(box, arg, body))
        return box;
    else if (isBoxInt(box))
        return box;
    else if (isBoxReal(box, &r))
        return box;
    else if (isBoxWaveform(box))
        return box;
    else if (isBoxCut(box))
        return box;
    else if (isBoxWire(box))
        return box;
    else if (isBoxPrim0(box, &p0))
        return box;
    else if (isBoxPrim1(box, &p1))
        return box;
    else if (isBoxPrim2(box, &p2))
        return box;
    else if (isBoxPrim3(box, &p3))
        return box;
    else if (isBoxPrim4(box, &p4))
        return box;
    else if (isBoxPrim5(box, &p5))
        return box;

    else if (isBoxWithLocalDef(box, body, ldef))
        return boxWithLocalDef(preparePattern(body), ldef);

    // Foreign elements
    else if (isBoxFFun(box, ff))
        return box;
    else if (isBoxFConst(box, type, name, file))
        return box;
    else if (isBoxFVar(box, type, name, file))
        return box;

    // Block diagram binary operator
    else if (isBoxSeq(box, t1, t2))
        return boxSeq(preparePattern(t1), preparePattern(t2));
    else if (isBoxSplit(box, t1, t2))
        return boxSplit(preparePattern(t1), preparePattern(t2));
    else if (isBoxMerge(box, t1, t2))
        return boxMerge(preparePattern(t1), preparePattern(t2));
    else if (isBoxPar(box, t1, t2))
        return boxPar(preparePattern(t1), preparePattern(t2));
    else if (isBoxRec(box, t1, t2))
        return boxRec(preparePattern(t1), preparePattern(t2));

    // Iterative block diagram construction
    else if (isBoxIPar(box, t1, t2, t3))
        return boxIPar(t1, t2, preparePattern(t3));
    else if (isBoxISeq(box, t1, t2, t3))
        return boxISeq(t1, t2, preparePattern(t3));
    else if (isBoxISum(box, t1, t2, t3))
        return boxISum(t1, t2, preparePattern(t3));
    else if (isBoxIProd(box, t1, t2, t3))
        return boxIProd(t1, t2, preparePattern(t3));

    // Static information
    else if (isBoxInputs(box, t1))
        return boxInputs(preparePattern(t1));
    else if (isBoxOutputs(box, t1))
        return boxOutputs(preparePattern(t1));

    // User interface
    else if (isBoxButton(box, label))
        return box;
    else if (isBoxCheckbox(box, label))
        return box;

    else if (isBoxVSlider(box, label, cur, min, max, step))
        return box;
    else if (isBoxHSlider(box, label, cur, min, max, step))
        return box;

    else if (isBoxVGroup(box, label, t1))
        return boxVGroup(label, preparePattern(t1));
    else if (isBoxHGroup(box, label, t1))
        return boxHGroup(label, preparePattern(t1));
    else if (isBoxTGroup(box, label, t1))
        return boxTGroup(label, preparePattern(t1));

    else if (isBoxHBargraph(box, label, min, max))
        return box;
    else if (isBoxVBargraph(box, label, min, max))
        return box;
    else if (isBoxNumEntry(box, label, cur, min, max, step))
        return box;

    else if (isNil(box))
        return box;
    else if (isList(box))
        return lmap(preparePattern, box);
    else if (isBoxEnvironment(box))
        return box;
    /* not expected
    else if (isClosure(box, abstr, genv, vis, lenv)) {
        fout << "closure[" << boxpp(abstr)
            << ", genv = " << envpp(genv)
            << ", lenv = " << envpp(lenv)
            << "]";
    }
    */
    else if (isBoxComponent(box, label))
        return box;
    else if (isBoxAccess(box, t1, t2))
        return box;

    /* not expected
    else if (isImportFile(box, label)) {
        fout << "import("
            << tree2str(label) << ')';
    }
    */

    else if (isBoxSlot(box, &id))
        return box;
    else if (isBoxSymbolic(box, slot, body))
        return box;

    // Pattern Matching Extensions
    else if (isBoxCase(box, rules))
        return box;
    else if (isBoxPatternVar(box, ident))
        return box;

    // None of the previous tests succeded, then it is not a valid box
    else {
        stringstream error;
        error << "ERROR : preparePattern() : " << *box << " is not a valid box" << endl;
        throw faustexception(error.str());
    }

    return box;
}

static Tree prepareRule(Tree rule)
{
    return cons(lmap(preparePattern, hd(rule)), tl(rule));
}

static Tree prepareRules(Tree rules)
{
    return lmap(prepareRule, rules);
}

Tree boxCaseInternal(Tree rules)
{
    return tree(gGlobal->BOXCASE, rules);
}
Tree boxCase(Tree rules)
{
    return boxCaseInternal(prepareRules(rules));
}

LIBFAUST_API bool isBoxCase(Tree s)
{
    Tree rules;
    return isTree(s, gGlobal->BOXCASE, rules);
}
LIBFAUST_API bool isBoxCase(Tree s, Tree& rules)
{
    return isTree(s, gGlobal->BOXCASE, rules);
}

Tree boxPatternVar(Tree id)
{
    return tree(gGlobal->BOXPATVAR, id);
}
bool isBoxPatternVar(Tree s, Tree& id)
{
    return isTree(s, gGlobal->BOXPATVAR, id);
}

Tree boxPatternMatcher(PM::Automaton* a, int state, Tree env, Tree origRules, Tree revParamList)
{
    return tree(gGlobal->BOXPATMATCHER, tree((void*)a), tree(state), env, origRules, revParamList);
}

bool isBoxPatternMatcher(Tree s)
{
    Tree ta, ts, env, orig, rpl;
    return isTree(s, gGlobal->BOXPATMATCHER, ta, ts, env, orig, rpl);
}

bool isBoxPatternMatcher(Tree s, PM::Automaton*& a, int& state, Tree& env, Tree& origRules, Tree& revParamList)
{
    Tree ta, ts;
    if (isTree(s, gGlobal->BOXPATMATCHER, ta, ts, env, origRules, revParamList)) {
        a     = (PM::Automaton*)tree2ptr(ta);
        state = tree2int(ts);
        return true;
    } else {
        return false;
    }
}
