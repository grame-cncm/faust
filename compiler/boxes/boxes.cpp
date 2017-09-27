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

#include <stdio.h>
#include <string.h>
#include "boxes.hh"
#include "ppbox.hh"
#include "prim2.hh"
#include "xtended.hh"


/*****************************************************************************
							    	Identifiers
*****************************************************************************/
Sym BOXIDENT = symbol ("BoxIdent");

Tree boxIdent(const char* name)		{ return tree(BOXIDENT, tree(symbol(name)) ); }
bool isBoxIdent(Tree t)				{ return t->node() == Node(BOXIDENT); }
bool isBoxIdent(Tree t0, const char** str)
{
	Tree t1; Sym s;
	if ( isTree(t0, BOXIDENT, t1) && isSym(t1->node(), &s) ) {
		*str = name(s);
		return true;
	} else {
		return false;
	}
}


/*****************************************************************************
							    	Numbers
*****************************************************************************/

Tree boxInt(int n) 					{ return tree(n); 	}
Tree boxReal(double n) 				{ return tree(n); 	}

bool isBoxInt(Tree t)				{ return isInt(t->node());	}
bool isBoxReal(Tree t)				{ return isDouble(t->node()); }

bool isBoxInt(Tree t, int* i)		{ return isInt(t->node(), i);	}
bool isBoxReal(Tree t, double* r)	{ return isDouble(t->node(), r); }



/*****************************************************************************
							 Waveform
*****************************************************************************/

Sym BOXWAVEFORM = symbol ("BoxWaveform");

Tree boxWaveform (const tvec& br)
{
    return tree(BOXWAVEFORM, br);
}

bool isBoxWaveform (Tree s) 				{ return isTree(s, BOXWAVEFORM); }

/*****************************************************************************
							   	Wire and Cut
*****************************************************************************/

Sym BOXCUT = symbol ("BoxCut");
Tree boxCut()						{ return tree(BOXCUT); }
bool isBoxCut(Tree t)				{ return isTree(t, BOXCUT); }

Sym BOXWIRE = symbol ("BoxWire");
Tree boxWire()						{ return tree(BOXWIRE); }
bool isBoxWire(Tree t)				{ return isTree(t, BOXWIRE); }


/*****************************************************************************
						Symbolic Boxes with symbolic slots
*****************************************************************************/

Sym BOXSLOT = symbol ("BoxSlot");

Tree boxSlot(int id)				{ return tree(BOXSLOT,tree(id)); }
bool isBoxSlot(Tree t)				{ Tree w; return isTree(t, BOXSLOT,w); }
bool isBoxSlot(Tree t, int* id)		{ Tree w; return isTree(t, BOXSLOT,w) && isInt(w->node(),id); }


Sym BOXSYMBOLIC = symbol ("BoxSymbolic");

Tree boxSymbolic(Tree slot, Tree body)				{ return tree(BOXSYMBOLIC,slot, body); }
bool isBoxSymbolic(Tree t)							{ Tree slot, body; return isTree(t, BOXSYMBOLIC, slot, body); }
bool isBoxSymbolic(Tree t, Tree& slot, Tree& body)	{ return isTree(t, BOXSYMBOLIC, slot, body); }


/*****************************************************************************
							  Composition of Boxes
*****************************************************************************/

Sym BOXSEQ = symbol ("BoxSeq");
Tree boxSeq(Tree x, Tree y) 				{ return tree(BOXSEQ, x, y); 		}
bool isBoxSeq(Tree t, Tree& x, Tree& y) 	{ return isTree(t, BOXSEQ, x, y); 	}

Sym BOXPAR = symbol ("BoxPar");
Tree boxPar(Tree x, Tree y) 				{ return tree(BOXPAR, x, y); 		}
bool isBoxPar(Tree t, Tree& x, Tree& y)		{ return isTree(t, BOXPAR, x, y); 	}

Sym BOXREC = symbol ("BoxRec");
Tree boxRec(Tree x, Tree y) 				{ return tree(BOXREC, x, y); 		}
bool isBoxRec(Tree t, Tree& x, Tree& y)		{ return isTree(t, BOXREC, x, y); 	}

Sym BOXSPLIT = symbol ("BoxSplit");
Tree boxSplit(Tree x, Tree y) 				{ return tree(BOXSPLIT, x, y); 		}
bool isBoxSplit(Tree t, Tree& x, Tree& y)	{ return isTree(t, BOXSPLIT, x, y); }

Sym BOXMERGE = symbol ("BoxMerge");
Tree boxMerge(Tree x, Tree y) 				{ return tree(BOXMERGE, x, y); }
bool isBoxMerge(Tree t, Tree& x, Tree& y)	{ return isTree(t, BOXMERGE, x, y); }


/*****************************************************************************
						Algorithmic Composition of Boxes
*****************************************************************************/

Sym BOXIPAR = symbol ("BoxIPar");
Sym BOXISEQ = symbol ("BoxISeq");
Sym BOXISUM = symbol ("BoxISum");
Sym BOXIPROD = symbol ("BoxIProd");

Tree boxIPar(Tree x, Tree y, Tree z) 					{ return tree(BOXIPAR, x, y, z); 		}
Tree boxISeq(Tree x, Tree y, Tree z) 					{ return tree(BOXISEQ, x, y, z);		}
Tree boxISum(Tree x, Tree y, Tree z) 					{ return tree(BOXISUM, x, y, z);		}
Tree boxIProd(Tree x, Tree y, Tree z) 					{ return tree(BOXIPROD, x, y, z); 		}

bool isBoxIPar(Tree t, Tree& x, Tree& y, Tree& z)		{ return isTree(t, BOXIPAR,  x, y, z);   }
bool isBoxISeq(Tree t, Tree& x, Tree& y, Tree& z)		{ return isTree(t, BOXISEQ,  x, y, z);   }
bool isBoxISum(Tree t, Tree& x, Tree& y, Tree& z)		{ return isTree(t, BOXISUM,  x, y, z);   }
bool isBoxIProd(Tree t, Tree& x, Tree& y, Tree& z)		{ return isTree(t, BOXIPROD, x, y, z);   }


/*****************************************************************************
                        Static information on Boxes
*****************************************************************************/

Sym BOXINPUTS  = symbol ("BoxInputs");
Sym BOXOUTPUTS = symbol ("BoxOutputs");

Tree boxInputs(Tree x)                                  { return tree(BOXINPUTS, x); 		}
Tree boxOutputs(Tree x)                                 { return tree(BOXOUTPUTS, x); 		}

bool isBoxInputs(Tree t, Tree& x)                       { return isTree(t, BOXINPUTS, x);   }
bool isBoxOutputs(Tree t, Tree& x)                      { return isTree(t, BOXOUTPUTS, x);  }



/*****************************************************************************
							  Lambda-Calculus of Boxes
*****************************************************************************/
Sym BOXABSTR 	= symbol ("BoxAbstr");
Sym BOXAPPL 	= symbol ("BoxAppl");
Sym CLOSURE 	= symbol ("Closure");
Sym BOXERROR 	= symbol ("BoxError");
Sym BOXACCESS 	= symbol ("BoxAccess");

Tree boxAbstr	(Tree x, Tree y)			{ return tree(BOXABSTR, x, y); }
Tree boxAppl 	(Tree x, Tree y)			{ return tree(BOXAPPL, x, y); }

bool isBoxAbstr	(Tree t)					{ return t->node() == Node(BOXABSTR); }
bool isBoxAppl	(Tree t)					{ return t->node() == Node(BOXAPPL); }

bool isBoxAbstr	(Tree t, Tree& x, Tree& y)	{ return isTree(t, BOXABSTR, x, y); }
bool isBoxAppl	(Tree t, Tree& x, Tree& y)	{ return isTree(t, BOXAPPL, x, y); }

Tree buildBoxAbstr	(Tree largs, Tree body)
{
	if (isNil(largs)) {
		return body;
	} else {
		return buildBoxAbstr(tl(largs), boxAbstr(hd(largs), body));
	}
}

#if 0
Tree buildBoxAppl 	(Tree fun, Tree revarglist)
{
	if (isNil(revarglist)) {
		return fun;
	} else {
		return  boxAppl(buildBoxAppl(fun, tl(revarglist)), hd(revarglist));
	}
}
#else
Tree buildBoxAppl 	(Tree fun, Tree revarglist)
{
	if (isNil (revarglist)) exit(1); // a revoir !!!!!!
	return  boxAppl(fun, revarglist);
}
#endif

Tree closure (Tree abstr, Tree genv, Tree vis, Tree lenv)
{
	return 	tree(CLOSURE, abstr, genv, vis, lenv);
}

bool isClosure	(Tree t, Tree& abstr, Tree& genv, Tree& vis, Tree& lenv)
{
	return isTree(t, CLOSURE, abstr, genv, vis, lenv);
}

Tree boxError()
{
	return 	tree(BOXERROR);
}

bool isBoxError(Tree t)
{
	return isTree(t, BOXERROR);
}


Tree boxAccess (Tree exp, Tree id)				{ return tree(BOXACCESS, exp, id); }
bool isBoxAccess(Tree t, Tree& exp, Tree& id)	{ return isTree(t, BOXACCESS, exp, id); }


/*****************************************************************************
						Boxes with local definitions
*****************************************************************************/
Sym BOXWITHLOCALDEF 	= symbol ("BoxWithLocalDef");

Tree boxWithLocalDef (Tree body, Tree ldef)					{ return tree(BOXWITHLOCALDEF, body, ldef); }
bool isBoxWithLocalDef (Tree t, Tree& body, Tree& ldef)		{ return isTree(t, BOXWITHLOCALDEF, body, ldef); }


/*****************************************************************************
 Boxes with recursive definitions
 *****************************************************************************/
Tree LETRECBODY         = boxIdent("RECURSIVEBODY");

// def2names transforms a liste of definition (name.expression) into a list of name
static Tree def2names(Tree ldef)
{
    if (isNil(ldef)) {
        return nil;
    } else {
        Tree def = hd(ldef);
        return cons(hd(def), def2names(tl(ldef)));
    }
}

// def2exp transforms a list of definition (name.expression) into a list of expressions
static Tree def2exp(Tree ldef)
{
    if (isNil(ldef)) {
        return nil;
    } else {
        Tree def = hd(ldef);
        return cons(tl(def), def2exp(tl(ldef)));
    }
}

// makeBus(3) => "_,_,_"
static Tree makeBus(int n)
{
    return (n<=1) ? boxWire() : boxPar(boxWire(), makeBus(n-1));
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
static Tree makeBoxAbstr	(Tree largs, Tree body)
{
    if (isNil(largs)) {
        return body;
    } else {
        return boxAbstr(hd(largs), makeBoxAbstr(tl(largs),body));
    }
}

// makeSelector(5,2) => "!,!,_,!,!"
static Tree makeSelector(int n, int i)
{
    Tree op = (i==0) ? boxWire() : boxCut();
    return (n==1) ? op : boxPar(op, makeSelector(n-1, i-1));
}

// defines each symbol si of lnames as => "si = RECURSIVEBODY : select(n,i);"
static Tree makeRecProjectionsList(int n, int i, Tree lnames, Tree ldef)
{
    if (i==n) {
        return ldef;
    } else {
        Tree sel = boxSeq(LETRECBODY, makeSelector(n,i));
        return cons(cons(hd(lnames), sel), makeRecProjectionsList(n, i+1, tl(lnames), ldef));
    }
}

// buildRecursiveBodyDef(n,lnames,lexp) => "RECURSIVEBODY = \(lnames).(lexp) ~ bus(n);"
static Tree buildRecursiveBodyDef(int n, Tree lnames, Tree lexp)
{
    return cons(LETRECBODY, boxRec(makeBoxAbstr(lnames, makeParList(lexp)), makeBus(n)));
}

//----------------------------------------------------------------------------
// Transform a letrec expression into a with expression
//----------------------------------------------------------------------------
Tree boxWithRecDef (Tree body, Tree ldef) {
    //cout << "list of recursive definitions : " << *ldef << endl;
    Tree lnames = def2names(ldef);
    Tree   lexp = def2exp  (ldef);
    int       n = len(ldef);

    Tree   rdef = buildRecursiveBodyDef(n, lnames, lexp);
    Tree    lrp = makeRecProjectionsList(n, 0, lnames, nil);
    Tree      w = boxWithLocalDef(body, cons(rdef, lrp));
    //cerr << "boxWithRecDef(" << boxpp(body) << ',' << *ldef << ") -> " << boxpp(w) << endl;
    return w;
}


/*****************************************************************************
                        Boxes modif local definitions
*****************************************************************************/
Sym BOXMODIFLOCALDEF 	= symbol ("BoxModifLocalDef");


Tree boxModifLocalDef (Tree body, Tree ldef)                { return tree(BOXMODIFLOCALDEF, body, ldef); }
bool isBoxModifLocalDef (Tree t, Tree& body, Tree& ldef)	{ return isTree(t, BOXMODIFLOCALDEF, body, ldef); }


/*****************************************************************************
							 Modules
*****************************************************************************/

Sym BOXENVIRONMENT  = symbol ("BoxEnvironment");

Tree boxEnvironment ()                                      { return tree(BOXENVIRONMENT); }
bool isBoxEnvironment (Tree s)                              { return isTree(s, BOXENVIRONMENT); }

Sym BOXCOMPONENT    = symbol ("BoxComponent");

Tree boxComponent (Tree filename)                           { return tree(BOXCOMPONENT, filename); }
bool isBoxComponent (Tree s, Tree& filename)                { return isTree(s, BOXCOMPONENT, filename); }

Sym BOXLIBRARY      = symbol ("BoxLibrary");

Tree boxLibrary (Tree filename)                             { return tree(BOXLIBRARY, filename); }
bool isBoxLibrary (Tree s, Tree& filename)                  { return isTree(s, BOXLIBRARY, filename); }


Sym IMPORTFILE      = symbol ("ImportFile");

Tree importFile(Tree filename)								{ return tree(IMPORTFILE, filename); }
bool isImportFile(Tree s, Tree& filename)					{ return isTree(s, IMPORTFILE, filename); }


/*****************************************************************************
							External Primitive Boxes (n -> 1)
*****************************************************************************/

Sym BOXPRIM0 = symbol ("BoxPrim0");
Tree boxPrim0(prim0 foo)					{ return tree(BOXPRIM0, tree((void*)foo)); }
bool isBoxPrim0	(Tree s)					{ Tree t; return isTree(s, BOXPRIM0, t);	}
bool isBoxPrim0	(Tree s, prim0* p)			{ Tree t; return isTree(s, BOXPRIM0, t) && isPointer(t->node(),(void**)p);	}

Sym BOXPRIM1 = symbol ("BoxPrim1");
Tree boxPrim1(prim1 foo)					{ return tree(BOXPRIM1, tree((void*)foo)); }
bool isBoxPrim1	(Tree s)					{ Tree t; return isTree(s, BOXPRIM1, t);	}
bool isBoxPrim1	(Tree s, prim1* p)			{ Tree t; return isTree(s, BOXPRIM1, t) && isPointer(t->node(),(void**)p);	}

Sym BOXPRIM2 = symbol ("BoxPrim2");
Tree boxPrim2(prim2 foo)					{ return tree(BOXPRIM2, tree((void*)foo)); }
bool isBoxPrim2	(Tree s)					{ Tree t; return isTree(s, BOXPRIM2, t);	}
bool isBoxPrim2	(Tree s, prim2* p)			{ Tree t; return isTree(s, BOXPRIM2, t) && isPointer(t->node(),(void**)p);	}

Sym BOXPRIM3 = symbol ("BoxPrim3");
Tree boxPrim3(prim3 foo)					{ return tree(BOXPRIM3, tree((void*)foo)); }
bool isBoxPrim3	(Tree s)					{ Tree t; return isTree(s, BOXPRIM3, t);	}
bool isBoxPrim3	(Tree s, prim3* p)			{ Tree t; return isTree(s, BOXPRIM3, t) && isPointer(t->node(),(void**)p);	}

Sym BOXPRIM4 = symbol ("BoxPrim4");
Tree boxPrim4(prim4 foo)					{ return tree(BOXPRIM4, tree((void*)foo)); }
bool isBoxPrim4	(Tree s)					{ Tree t; return isTree(s, BOXPRIM4, t);	}
bool isBoxPrim4	(Tree s, prim4* p)			{ Tree t; return isTree(s, BOXPRIM4, t) && isPointer(t->node(),(void**)p);	}

Sym BOXPRIM5 = symbol ("BoxPrim5");
Tree boxPrim5(prim5 foo)					{ return tree(BOXPRIM5, tree((void*)foo)); }
bool isBoxPrim5	(Tree s)					{ Tree t; return isTree(s, BOXPRIM5, t);	}
bool isBoxPrim5	(Tree s, prim5* p)			{ Tree t; return isTree(s, BOXPRIM5, t) && isPointer(t->node(),(void**)p);	}

/*****************************************************************************
							 Foreign Functions
*****************************************************************************/

Sym BOXFFUN = symbol ("BoxFFun");
Tree boxFFun (Tree ff)						{ return tree(BOXFFUN, ff); 				}
bool isBoxFFun	(Tree s)					{ Tree ff; return isTree(s, BOXFFUN, ff);	}
bool isBoxFFun	(Tree s, Tree& ff)			{ return isTree(s, BOXFFUN, ff);			}


Sym BOXFCONST = symbol ("BoxFConst");
Tree boxFConst      (Tree type, Tree name, Tree file)               { return tree(BOXFCONST, type, name, file);             }
bool isBoxFConst    (Tree s)                                        { Tree t,n,f; return isTree(s, BOXFCONST, t, n, f); }
bool isBoxFConst    (Tree s, Tree& type, Tree& name, Tree& file)    { return isTree(s, BOXFCONST,type, name, file);     }


Sym BOXFVAR = symbol ("BoxFVar");
Tree boxFVar      (Tree type, Tree name, Tree file)                 { return tree(BOXFVAR, type, name, file);             }
bool isBoxFVar    (Tree s)                                          { Tree t,n,f; return isTree(s, BOXFVAR, t, n, f); }
bool isBoxFVar    (Tree s, Tree& type, Tree& name, Tree& file)      { return isTree(s, BOXFVAR,type, name, file);     }


/*****************************************************************************
							 User Interface Elements
*****************************************************************************/

Sym BOXBUTTON = symbol ("BoxButton");
Tree boxButton 	 (Tree lbl)					{ return tree(BOXBUTTON, lbl); 					}
bool isBoxButton (Tree s)					{ Tree lbl; return isTree(s, BOXBUTTON, lbl);	}
bool isBoxButton (Tree s, Tree& lbl)		{ return isTree(s, BOXBUTTON, lbl);				}


Sym BOXCHECKBOX = symbol ("BoxCheckbox");
Tree boxCheckbox   (Tree lbl)				{ return tree(BOXCHECKBOX, lbl); 					}
bool isBoxCheckbox (Tree s)					{ Tree lbl; return isTree(s, BOXCHECKBOX, lbl);	}
bool isBoxCheckbox (Tree s, Tree& lbl)		{ return isTree(s, BOXCHECKBOX, lbl);				}


Sym BOXHSLIDER = symbol ("BoxHSlider");
Tree boxHSlider   (Tree lbl, Tree cur, Tree min, Tree max, Tree step)
											{ return tree(BOXHSLIDER, lbl, list4(cur,min,max,step));		}
bool isBoxHSlider (Tree s)					{ Tree lbl, params; return isTree(s, BOXHSLIDER, lbl, params);	}

bool isBoxHSlider (Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
	Tree params;
	if (isTree(s, BOXHSLIDER, lbl, params)) {
		cur = nth(params, 0);
		min = nth(params, 1);
		max = nth(params, 2);
		step= nth(params, 3);
		return true;
	} else {
		return false;
	}
}


Sym BOXVSLIDER = symbol ("BoxVSlider");
Tree boxVSlider   (Tree lbl, Tree cur, Tree min, Tree max, Tree step)
											{ return tree(BOXVSLIDER, lbl, list4(cur,min,max,step));		}
bool isBoxVSlider (Tree s)					{ Tree lbl, params; return isTree(s, BOXVSLIDER, lbl, params);	}

bool isBoxVSlider (Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
	Tree params;
	if (isTree(s, BOXVSLIDER, lbl, params)) {
		cur = nth(params, 0);
		min = nth(params, 1);
		max = nth(params, 2);
		step= nth(params, 3);
		return true;
	} else {
		return false;
	}
}

Sym BOXNUMENTRY = symbol ("BoxNumEntry");
Tree boxNumEntry   (Tree lbl, Tree cur, Tree min, Tree max, Tree step)
											{ return tree(BOXNUMENTRY, lbl, list4(cur,min,max,step));		}
bool isBoxNumEntry (Tree s)					{ Tree lbl, params; return isTree(s, BOXNUMENTRY, lbl, params);	}

bool isBoxNumEntry (Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
	Tree params;
	if (isTree(s, BOXNUMENTRY, lbl, params)) {
		cur = nth(params, 0);
		min = nth(params, 1);
		max = nth(params, 2);
		step= nth(params, 3);
		return true;
	} else {
		return false;
	}
}


Sym BOXHGROUP = symbol ("BoxHGroup");
Tree boxHGroup   (Tree lbl, Tree x)				{ return tree(BOXHGROUP, lbl, x); 				}
bool isBoxHGroup (Tree s)						{ Tree lbl, x; return isTree(s, BOXHGROUP, lbl, x);	}
bool isBoxHGroup (Tree s, Tree& lbl, Tree& x)	{ return isTree(s, BOXHGROUP, lbl, x);				}


Sym BOXVGROUP = symbol ("BoxVGroup");
Tree boxVGroup   (Tree lbl, Tree x)				{ return tree(BOXVGROUP, lbl, x); 				}
bool isBoxVGroup (Tree s)						{ Tree lbl, x; return isTree(s, BOXVGROUP, lbl, x);	}
bool isBoxVGroup (Tree s, Tree& lbl, Tree& x)	{ return isTree(s, BOXVGROUP, lbl, x);				}


Sym BOXTGROUP = symbol ("BoxTGroup");
Tree boxTGroup   (Tree lbl, Tree x)				{ return tree(BOXTGROUP, lbl, x); 				}
bool isBoxTGroup (Tree s)						{ Tree lbl, x; return isTree(s, BOXTGROUP, lbl, x);	}
bool isBoxTGroup (Tree s, Tree& lbl, Tree& x)	{ return isTree(s, BOXTGROUP, lbl, x);				}


Sym BOXHBARGRAPH = symbol ("BoxHBargraph");
Tree boxHBargraph(Tree lbl, Tree min, Tree max)					{ return tree(BOXHBARGRAPH, lbl, min, max);		}
bool isBoxHBargraph (Tree s)									{ Tree lbl, min, max; return isTree(s, BOXHBARGRAPH, lbl, min, max);	}
bool isBoxHBargraph (Tree s, Tree& lbl, Tree& min, Tree& max)	{ return isTree(s, BOXHBARGRAPH, lbl, min, max); }


Sym BOXVBARGRAPH = symbol ("BoxVBargraph");
Tree boxVBargraph(Tree lbl, Tree min, Tree max)					{ return tree(BOXVBARGRAPH, lbl, min, max);		}
bool isBoxVBargraph (Tree s)									{ Tree lbl, min, max; return isTree(s, BOXVBARGRAPH, lbl, min, max);	}
bool isBoxVBargraph (Tree s, Tree& lbl, Tree& min, Tree& max)	{ return isTree(s, BOXVBARGRAPH, lbl, min, max); }


Sym BOXSOUNDFILE = symbol("boxSoundfile");

Tree boxSoundfile(Tree lbl, Tree chan)
{
    return tree(BOXSOUNDFILE, lbl, chan);
}

bool isBoxSoundfile(Tree s)
{
    Tree label;
    Tree chan;
    return isTree(s, BOXSOUNDFILE, label, chan);
}

bool isBoxSoundfile(Tree s, Tree &label, Tree &chan)
{
    return isTree(s, BOXSOUNDFILE, label, chan);
}

/*****************************************************************************
							 pattern lmatching case
*****************************************************************************/

Sym BOXCASE 		= symbol ("BoxCase");
Sym BOXPATMATCHER 	= symbol ("BoxPatMatcher");
Sym BOXPATVAR 		= symbol ("BoxPatVar");

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

        int		id;
        double	r;
        prim0	p0;
        prim1	p1;
        prim2	p2;
        prim3	p3;
        prim4	p4;
        prim5	p5;

        Tree	t1, t2, t3, ff, label, cur, min, max, step, type, name, file, arg,
                body, fun, args, ldef, slot,
                ident, rules;

        xtended* xt = (xtended*) getUserData(box);


        // primitive elements
             if (xt) 						return box;
        else if (isBoxIdent(box))           return boxPatternVar(box);
        else if (isBoxAppl(box, fun, args))	{
                if (isBoxIdent(fun))        return boxAppl( fun, lmap(preparePattern,args));
                else                        return boxAppl( preparePattern(fun), lmap(preparePattern,args));
            }
        else if (isBoxAbstr(box,arg,body))	return box;
        else if (isBoxInt(box))             return box;
        else if (isBoxReal(box, &r))		return box;
        else if (isBoxWaveform(box)) 		return box;
        else if (isBoxCut(box))				return box;
        else if (isBoxWire(box))			return box;
        else if (isBoxPrim0(box, &p0))		return box;
        else if (isBoxPrim1(box, &p1))		return box;
        else if (isBoxPrim2(box, &p2))		return box;
        else if (isBoxPrim3(box, &p3))		return box;
        else if (isBoxPrim4(box, &p4))		return box;
        else if (isBoxPrim5(box, &p5))		return box;

        else if (isBoxWithLocalDef(box, body, ldef))	return boxWithLocalDef(preparePattern(body), ldef);


        // foreign elements
        else if (isBoxFFun(box, ff))		return box;
        else if (isBoxFConst(box, type, name, file))
                                            return box;
        else if (isBoxFVar(box, type, name, file))
                                            return box;

        // block diagram binary operator
        else if (isBoxSeq(box, t1, t2))		return boxSeq( preparePattern(t1), preparePattern(t2) );
        else if (isBoxSplit(box, t1, t2))	return boxSplit( preparePattern(t1), preparePattern(t2) );
        else if (isBoxMerge(box, t1, t2)) 	return boxMerge( preparePattern(t1), preparePattern(t2) );
        else if (isBoxPar(box, t1, t2)) 	return boxPar( preparePattern(t1), preparePattern(t2) );
        else if (isBoxRec(box, t1, t2)) 	return boxRec( preparePattern(t1), preparePattern(t2) );

        // iterative block diagram construction
        else if (isBoxIPar(box, t1, t2, t3)) 	return boxIPar ( t1, t2, preparePattern(t3) );
        else if (isBoxISeq(box, t1, t2, t3)) 	return boxISeq ( t1, t2, preparePattern(t3) );
        else if (isBoxISum(box, t1, t2, t3)) 	return boxISum ( t1, t2, preparePattern(t3) );
        else if (isBoxIProd(box, t1, t2, t3)) 	return boxIProd( t1, t2, preparePattern(t3) );

        // static information
        else if (isBoxInputs(box, t1))          return boxInputs ( preparePattern(t1) );
        else if (isBoxOutputs(box, t1))         return boxOutputs( preparePattern(t1) );

        // user interface
        else if (isBoxButton(box, label))       return box;
        else if (isBoxCheckbox(box, label))     return box;

        else if (isBoxVSlider(box, label, cur, min, max, step)) 	return box;
        else if (isBoxHSlider(box, label, cur, min, max, step)) 	return box;

        else if (isBoxVGroup(box, label, t1))   return boxVGroup(label, preparePattern(t1));
        else if (isBoxHGroup(box, label, t1))   return boxHGroup(label, preparePattern(t1));
        else if (isBoxTGroup(box, label, t1))   return boxTGroup(label, preparePattern(t1));

        else if (isBoxHBargraph(box, label, min, max))              return box;
        else if (isBoxVBargraph(box, label, min, max))              return box;
        else if (isBoxNumEntry(box, label, cur, min, max, step))    return box;

        else if (isNil(box))                    return box;
        else if (isList(box))                   return lmap(preparePattern, box);
        else if (isBoxEnvironment(box))         return box;
        /* not expected
        else if (isClosure(box, abstr, genv, vis, lenv)) {
            fout << "closure[" << boxpp(abstr)
                << ", genv = " << envpp(genv)
                << ", lenv = " << envpp(lenv)
                << "]";
        }
        */
        else if (isBoxComponent(box, label))        return box;
        else if (isBoxAccess(box, t1, t2))          return box;

        /* not expected
        else if (isImportFile(box, label)) {
            fout << "import("
                << tree2str(label) << ')';
        }
        */


        else if (isBoxSlot(box, &id))               return box;
        else if (isBoxSymbolic(box, slot, body))    return box;

        // Pattern Matching Extensions
        else if (isBoxCase(box, rules))             return box;
        else if (isBoxPatternVar(box, ident))       return box;


        // None of the previous tests succeded, then it is not a valid box
        else {
            cerr << "Error in preparePattern() : " << *box << " is not a valid box" << endl;
            exit(1);
        }


   return box;
}

static Tree prepareRule(Tree rule)
{
    return cons (lmap(preparePattern,hd(rule)), tl(rule));
}

static Tree prepareRules(Tree rules) {
    return lmap(prepareRule, rules);
}

Tree boxCaseInternal 	 (Tree rules)       { return tree(BOXCASE, rules); 					}
Tree boxCase    (Tree rules)				{ return boxCaseInternal(prepareRules(rules));  }

bool isBoxCase (Tree s)						{ Tree rules; return isTree(s, BOXCASE, rules);	}
bool isBoxCase (Tree s, Tree& rules)		{ return isTree(s, BOXCASE, rules);				}


Tree boxPatternVar	(Tree id)				{ return tree(BOXPATVAR, id); 					}
bool isBoxPatternVar(Tree s, Tree& id)		{ return isTree(s, BOXPATVAR, id);				}


Tree boxPatternMatcher		(Automaton* a, int state, Tree env, Tree origRules, Tree revParamList)	
{ 
	return tree(BOXPATMATCHER, tree((void*)a), tree(state), env, origRules, revParamList); 
} 					

bool isBoxPatternMatcher	(Tree s)
{
	Tree ta, ts, env, orig, rpl;
	return isTree(s, BOXPATMATCHER, ta, ts, env, orig, rpl);
}

bool isBoxPatternMatcher	(Tree s, Automaton*& a, int& state, Tree& env, Tree& origRules, Tree& revParamList)
{
	Tree ta, ts;
	if (isTree(s, BOXPATMATCHER, ta, ts, env, origRules, revParamList)) {
		a = (Automaton*)tree2ptr(ta);
		state = tree2int(ts);
		return true;
	} else {
		return false;
	}
}
