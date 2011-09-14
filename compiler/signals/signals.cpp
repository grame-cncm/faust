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
	HISTORY
    22/01/05 : added int cast in select2 and select3 selection signal
*****************************************************************************/



#include "signals.hh"
#include "sigtype.hh"

#include <set>

////////////////////////////////////////////////////////////////////////
/**
 * Signals
 *
 */
///////////////////////////////////////////////////////////////////////

static Sym box_reference = symbol("box reference");
Tree box_symbol = tree(box_reference);

Tree  sigInt(int i, Tree box) 						{ return tree(i)->setProperty(box_symbol, box);	}
bool  isSigInt(Tree t, int* i) 						{ return isInt(t->node(), i); 		}

Tree  sigReal(double r, Tree box) 					{ return tree(r)->setProperty(box_symbol, box); }
bool  isSigReal(Tree t, double* r) 					{ return isDouble(t->node(), r); 	}

Sym SIGINPUT = symbol ("sigInput");
Tree  sigInput(int i, Tree box)                     { return tree(SIGINPUT, tree(i))->setProperty(box_symbol, box);	}
bool  isSigInput(Tree t, int* i) 					{ Tree x; return isTree(t, SIGINPUT, x) && isInt(x->node(),i); 	}

Sym SIGDELAY1 = symbol ("sigDelay1");
Tree  sigDelay0(Tree t0, Tree box)					{ return sigFixDelay(t0, sigInt(0, box), box);}

Tree  sigDelay1(Tree t0, Tree box)					{ return tree(SIGDELAY1, t0)->setProperty(box_symbol, box); 		}
bool  isSigDelay1(Tree t, Tree& t0)					{ return isTree(t, SIGDELAY1, t0); 	}

Sym SIGFIXDELAY = symbol ("sigFixDelay");
Tree  sigFixDelay(Tree t0, Tree t1, Tree box)		{ return tree(SIGFIXDELAY, t0, sigIntCast(t1, box))->setProperty(box_symbol, box); 		}
bool  isSigFixDelay(Tree t, Tree& t0, Tree& t1)		{ return isTree(t, SIGFIXDELAY, t0, t1); 	}

Sym SIGPREFIX = symbol ("sigPrefix");
Tree  sigPrefix(Tree t0, Tree t1, Tree box)			{ return tree(SIGPREFIX, t0, t1)->setProperty(box_symbol, box); 		}
bool  isSigPrefix(Tree t, Tree& t0, Tree& t1)		{ return isTree(t, SIGPREFIX, t0, t1); 	}

Sym SIGIOTA = symbol ("sigIota");
Tree  sigIota(Tree t0, Tree box)					{ return tree(SIGIOTA, t0)->setProperty(box_symbol, box); 		}
bool  isSigIota(Tree t, Tree& t0)					{ return isTree(t, SIGIOTA, t0); 	}


// Read only and read write tables

Sym SIGRDTBL = symbol ("SigRDTbl");
Tree sigRDTbl (Tree t, Tree i, Tree box)			{ return tree(SIGRDTBL, t, i)->setProperty(box_symbol, box); 	}
bool isSigRDTbl (Tree s, Tree& t, Tree& i)			{ return isTree(s, SIGRDTBL, t, i); 	}

Sym SIGWRTBL = symbol ("SigWRTbl");
Tree sigWRTbl (Tree id, Tree t, Tree i, Tree s, Tree box)		{ return tree(SIGWRTBL, id, t, i, s)->setProperty(box_symbol, box); 	}
bool isSigWRTbl (Tree u, Tree& id, Tree& t, Tree& i, Tree& s)	{ return isTree(u, SIGWRTBL, id, t, i, s); 	}

Sym SIGTABLE = symbol ("SigTable");
Tree sigTable (Tree id, Tree n, Tree sig, Tree box)		{ return tree(SIGTABLE, id, n, sig)->setProperty(box_symbol, box); 		}
bool isSigTable (Tree t, Tree& id, Tree& n, Tree& sig)	{ return isTree(t, SIGTABLE, id, n, sig); 	}

// Signal used to generate the initial content of a table

Sym SIGGEN = symbol ("SigGen");
Tree sigGen (Tree s, Tree box)					{ return tree(SIGGEN, s)->setProperty(box_symbol, box); 		}
bool isSigGen (Tree t, Tree& x)					{ return isTree(t, SIGGEN, x); 	}
bool isSigGen (Tree t)							{ return t->node()== Node(SIGGEN); 	}


// Documentator Tables : special version of tables only for documentation purposes

Sym SIGDOCONSTANTTBL = symbol ("SigDocConstantTbl");
Tree   sigDocConstantTbl    (Tree n, Tree sig, Tree box)        { return tree(SIGDOCONSTANTTBL, n, sig)->setProperty(box_symbol, box);        }
bool isSigDocConstantTbl    (Tree t, Tree& n, Tree& sig)        { return isTree(t, SIGDOCONSTANTTBL, n, sig); 	}

Sym SIGDOCWRITETBL = symbol ("SigDocWriteTbl");
Tree   sigDocWriteTbl   (Tree n, Tree sig, Tree widx, Tree wsig, Tree box)      { return tree(SIGDOCWRITETBL, n, sig, widx, wsig)->setProperty(box_symbol, box);	}
bool isSigDocWriteTbl   (Tree t, Tree& n, Tree& sig, Tree& widx, Tree& wsig)    { return isTree(t, SIGDOCWRITETBL, n, sig, widx, wsig); 	}

Sym SIGDOCACCESSTBL = symbol ("SigDocAccessTbl");
Tree   sigDocAccessTbl   (Tree tbl, Tree ridx, Tree box)        { return tree(SIGDOCACCESSTBL, tbl, ridx)->setProperty(box_symbol, box);	}
bool isSigDocAccessTbl   (Tree t, Tree& tbl, Tree& ridx)        { return isTree(t, SIGDOCACCESSTBL, tbl, ridx); 	}


// Select on signal among severals

Sym SIGSELECT2 = symbol ("SigSelect2");
Sym SIGSELECT3 = symbol ("SigSelect3");

Tree sigSelect2 (Tree selector, Tree s1, Tree s2, Tree box)			{ return tree(SIGSELECT2, sigIntCast(selector, box), s1, s2)->setProperty(box_symbol, box); }
bool isSigSelect2 (Tree t, Tree& selector, Tree& s1, Tree& s2)		{ return isTree(t, SIGSELECT2, selector, s1, s2); }

//Tree sigSelect3 (Tree selector, Tree s1, Tree s2, Tree s3, Tree box)    { return tree(SIGSELECT3, sigIntCast(selector, box), s1, s2, s3); }

bool isSigSelect3 (Tree t, Tree& selector, Tree& s1, Tree& s2, Tree& s3)	{ return isTree(t, SIGSELECT3, selector, s1, s2, s3); }

//  "select3" expresses with "select2"
Tree sigSelect3 (Tree selector, Tree s1, Tree s2, Tree s3, Tree box)
{
     return sigSelect2(sigBinOp(kEQ, sigIntCast(selector, box), sigInt(0, box), box),
            sigSelect2(sigBinOp(kEQ, sigIntCast(selector, box), sigInt(1, box), box), s3, s2, box), s1, box)->setProperty(box_symbol, box);
}

// multirate

Sym SIGVECTORIZE = symbol ("SigVectorize");
Tree sigVectorize (Tree s1, Tree s2, Tree box)  { return tree(SIGVECTORIZE, s1, s2)->setProperty(box_symbol, box); }
bool isSigVectorize (Tree a, Tree& s1, Tree& s2) { return isTree(a, SIGVECTORIZE, s1, s2); }

Sym SIGSERIALIZE = symbol ("SigSerialize");
Tree sigSerialize (Tree s1, Tree box)           { return tree(SIGSERIALIZE, s1)->setProperty(box_symbol, box); }
bool isSigSerialize (Tree a, Tree& s1)          { return isTree(a, SIGSERIALIZE, s1); }

Sym SIGCONCAT = symbol ("SigConcat");
Tree sigConcat (Tree s1, Tree s2, Tree box)     { return tree(SIGCONCAT, s1, s2)->setProperty(box_symbol, box); }
bool isSigConcat (Tree a, Tree& s1, Tree& s2)   { return isTree(a, SIGCONCAT, s1, s2); }

Sym SIGVECTORAT = symbol ("SigVectorAt");
Tree sigVectorAt (Tree s1, Tree s2, Tree box)   { return tree(SIGVECTORAT, s1, s2)->setProperty(box_symbol, box); }
bool isSigVectorAt(Tree a, Tree& s1, Tree& s2)  { return isTree(a, SIGVECTORAT, s1, s2); }

// Arithmetical operations

Sym SIGBINOP = symbol ("SigBinOp");

Tree sigBinOp(int op, Tree x, Tree y, Tree box)
{
    return tree(SIGBINOP, tree(op), x, y)->setProperty(box_symbol, box);
}
bool isSigBinOp(Tree s, int* op, Tree& x, Tree& y) 		{ Tree t; return isTree(s, SIGBINOP, t, x, y) && isInt(t->node(),op); }


// Foreign Functions

Sym SIGFFUN = symbol ("SigFFun");
Tree sigFFun (Tree ff, Tree largs, Tree box)			{ return tree(SIGFFUN, ff, largs)->setProperty(box_symbol, box); 			}
bool isSigFFun	(Tree s, Tree& ff, Tree& largs)			{ return isTree(s, SIGFFUN, ff, largs);		}


Sym SIGFCONST = symbol ("SigFConst");
Tree sigFConst      (Tree type, Tree name, Tree file, Tree box)   { return tree(SIGFCONST, type, name, file)->setProperty(box_symbol, box);         }
bool isSigFConst    (Tree s)                                      { Tree t,n,f; return isTree(s, SIGFCONST, t, n, f); }
bool isSigFConst    (Tree s, Tree& type, Tree& name, Tree& file)  { return isTree(s, SIGFCONST,type, name, file);     }


Sym SIGFVAR = symbol ("SigFVar");
Tree sigFVar      (Tree type, Tree name, Tree file, Tree box)     { return tree(SIGFVAR, type, name, file)->setProperty(box_symbol, box);           }
bool isSigFVar    (Tree s)                                        { Tree t,n,f; return isTree(s, SIGFVAR, t, n, f);   }
bool isSigFVar    (Tree s, Tree& type, Tree& name, Tree& file)    { return isTree(s, SIGFVAR, type, name, file);      }

// nouvelle version utilisant rec et ref

Sym SIGPROJ = symbol ("SigProj");
Tree sigProj (int i, Tree rgroup, Tree box)		{ return tree(SIGPROJ, tree(i), rgroup)->setProperty(box_symbol, box); 	}
bool isProj (Tree t, int* i, Tree& rgroup)		{ Tree x; return isTree(t, SIGPROJ, x, rgroup) && isInt(x->node(), i); 	}


// Int and Float casting

Sym SIGINTCAST = symbol ("sigIntCast");
Sym SIGFLOATCAST = symbol ("sigFloatCast");

Tree  sigIntCast(Tree t, Tree box)
{
	Node n = t->node();

	int i; 		if (isInt(n, &i)) 			return t;
	double x;	if (isDouble(n, &x)) 		return tree(int(x));
				if (isSigIntCast(t))		return t;

	return tree(SIGINTCAST, t)->setProperty(box_symbol, box);
}

Tree  sigFloatCast(Tree t, Tree box)
{
	Node n = t->node();

	int i; 		if (isInt(n, &i)) 			return tree(double(i));
	double x;	if (isDouble(n, &x)) 		return t;
				if (isSigFloatCast(t))		return t;
                if (isSigInput(t, &i))      return t;

	return tree(SIGFLOATCAST, t)->setProperty(box_symbol, box);
}

//Tree  sigFloatCast(Tree t)						{ return isSigFloatCast(t)? t : tree(SIGFLOATCAST, t); }

bool  isSigIntCast(Tree t)						{ Tree x; return isTree(t, SIGINTCAST, x); 	}
bool  isSigIntCast(Tree t, Tree& x)				{ return isTree(t, SIGINTCAST, x); 			}

bool  isSigFloatCast(Tree t)					{ Tree x; return isTree(t, SIGFLOATCAST, x);}
bool  isSigFloatCast(Tree t, Tree& x)			{ return isTree(t, SIGFLOATCAST, x); 		}




/*****************************************************************************
							 User Interface Elements
*****************************************************************************/

Sym SIGBUTTON = symbol ("SigButton");
Tree sigButton 	 (Tree lbl, Tree box)		{ return tree(SIGBUTTON, lbl)->setProperty(box_symbol, box);	}
bool isSigButton (Tree s)					{ Tree lbl; return isTree(s, SIGBUTTON, lbl);	}
bool isSigButton (Tree s, Tree& lbl)		{ return isTree(s, SIGBUTTON, lbl);				}


Sym SIGCHECKBOX = symbol ("SigCheckbox");
Tree sigCheckbox   (Tree lbl, Tree box)		{ return tree(SIGCHECKBOX, lbl)->setProperty(box_symbol, box);	}
bool isSigCheckbox (Tree s)					{ Tree lbl; return isTree(s, SIGCHECKBOX, lbl);	}
bool isSigCheckbox (Tree s, Tree& lbl)		{ return isTree(s, SIGCHECKBOX, lbl);				}


Sym SIGHSLIDER = symbol ("SigHSlider");
Tree sigHSlider   (Tree lbl, Tree cur, Tree min, Tree max, Tree step, Tree box)
											{ return tree(SIGHSLIDER, lbl, list4(cur,min,max,step))->setProperty(box_symbol, box);		}
bool isSigHSlider (Tree s)					{ Tree lbl, params; return isTree(s, SIGHSLIDER, lbl, params);	}

bool isSigHSlider (Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
	Tree params;
	if (isTree(s, SIGHSLIDER, lbl, params)) {
		cur = nth(params, 0);
		min = nth(params, 1);
		max = nth(params, 2);
		step= nth(params, 3);
		return true;
	} else {
		return false;
	}
}


Sym SIGVSLIDER = symbol ("SigVSlider");
Tree sigVSlider   (Tree lbl, Tree cur, Tree min, Tree max, Tree step, Tree box)
											{ return tree(SIGVSLIDER, lbl, list4(cur,min,max,step))->setProperty(box_symbol, box);		}
bool isSigVSlider (Tree s)					{ Tree lbl, params; return isTree(s, SIGVSLIDER, lbl, params);	}

bool isSigVSlider (Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
	Tree params;
	if (isTree(s, SIGVSLIDER, lbl, params)) {
		cur = nth(params, 0);
		min = nth(params, 1);
		max = nth(params, 2);
		step= nth(params, 3);
		return true;
	} else {
		return false;
	}
}


Sym SIGNUMENTRY = symbol ("SigNumEntry");
Tree sigNumEntry   (Tree lbl, Tree cur, Tree min, Tree max, Tree step, Tree box)
											{ return tree(SIGNUMENTRY, lbl, list4(cur,min,max,step))->setProperty(box_symbol, box);		}
bool isSigNumEntry (Tree s)					{ Tree lbl, params; return isTree(s, SIGNUMENTRY, lbl, params);	}

bool isSigNumEntry (Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
	Tree params;
	if (isTree(s, SIGNUMENTRY, lbl, params)) {
		cur = nth(params, 0);
		min = nth(params, 1);
		max = nth(params, 2);
		step= nth(params, 3);
		return true;
	} else {
		return false;
	}
}

// output elements



Sym SIGHBARGRAPH = symbol ("SigHBargraph");
Tree sigHBargraph   (Tree lbl, Tree min, Tree max, Tree x, Tree box)	{ return tree(SIGHBARGRAPH, lbl, min, max, x)->setProperty(box_symbol, box);		}
bool isSigHBargraph (Tree s)											{ Tree lbl, min, max, x; return isTree(s, SIGHBARGRAPH, lbl, min, max, x);	}
bool isSigHBargraph (Tree s, Tree& lbl, Tree& min, Tree& max, Tree& x)	{ return isTree(s, SIGHBARGRAPH, lbl, min, max, x);	}


Sym SIGVBARGRAPH = symbol ("SigVBargraph");
Tree sigVBargraph   (Tree lbl, Tree min, Tree max, Tree x, Tree box)	{ return tree(SIGVBARGRAPH, lbl, min, max, x)->setProperty(box_symbol, box);		}
bool isSigVBargraph (Tree s)											{ Tree lbl, min, max, x; return isTree(s, SIGVBARGRAPH, lbl, min, max, x);	}
bool isSigVBargraph (Tree s, Tree& lbl, Tree& min, Tree& max, Tree& x)	{ return isTree(s, SIGVBARGRAPH, lbl, min, max, x);	}


Sym SIGATTACH = symbol ("sigAttach");
Tree  sigAttach(Tree t0, Tree t1, Tree box)			{ return tree(SIGATTACH, t0, t1)->setProperty(box_symbol, box); 		}
bool  isSigAttach(Tree t, Tree& t0, Tree& t1)		{ return isTree(t, SIGATTACH, t0, t1); 	}



Tree addNums(Tree a, Tree b, Tree box)
{
	Tree r = tree(addNode(a->node(),b->node()))->setProperty(box_symbol, box);
	//cerr.flags(ios::showpoint); cerr << "addNums " << *a << "+" << *b << " -> " << *r << endl;
	return r;
}

Tree subNums(Tree a, Tree b, Tree box)
{
	Tree r = tree(subNode(a->node(),b->node()))->setProperty(box_symbol, box);
	//cerr.flags(ios::showpoint); cerr << "subNums " << *a << "-" << *b << " -> " << *r << endl;
	return r;
}

Tree mulNums(Tree a, Tree b, Tree box)
{
	Tree r = tree(mulNode(a->node(),b->node()))->setProperty(box_symbol, box);
	//cerr.flags(ios::showpoint); cerr << "mulNums " << *a << "*" << *b << " -> " << *r << endl;
	return r;
}

Tree divNums(Tree a, Tree b, Tree box)
{
	Tree r = tree(divNode(a->node(),b->node()))->setProperty(box_symbol, box);
	//cerr.flags(ios::showpoint); cerr << "divNums " << *a << "/" << *b << " -> " << *r << endl;
	return r;
}

Tree divExtendedNums(Tree a, Tree b, Tree box)
{
	Tree r = tree(divExtendedNode(a->node(),b->node()))->setProperty(box_symbol, box);
	//cerr.flags(ios::showpoint); cerr << "divExtendeNums " << *a << "/" << *b << " -> " << *r << endl;
	return r;
}

Tree minusNum(Tree a, Tree box)
{
	Tree r = tree(minusNode(a->node()))->setProperty(box_symbol, box);
	//cerr.flags(ios::showpoint); cerr << "minusNum " << *a << " -> " << *r << endl;
	return r;
}

Tree inverseNum(Tree a, Tree box)
{
	Tree r = tree(inverseNode(a->node()))->setProperty(box_symbol, box);
	//cerr.flags(ios::showpoint); cerr << "inverseNum " << *a << " -> " << *r << endl;
	return r;
}

bool isSigAdd(Tree a, Tree& x, Tree& y)
{
	int	op;
	return isSigBinOp(a, &op, x, y) && (op == kAdd);
}

bool isSigMul(Tree a, Tree& x, Tree& y)
{
	int	op;
	return isSigBinOp(a, &op, x, y) && (op == kMul);
}

bool isSigSub(Tree a, Tree& x, Tree& y)
{
	int	op;
	return isSigBinOp(a, &op, x, y) && (op == kSub);
}

bool isSigDiv(Tree a, Tree& x, Tree& y)
{
	int	op;
	return isSigBinOp(a, &op, x, y) && (op == kDiv);
}




/*****************************************************************************
							 matrix extension
*****************************************************************************/
Sym SIGTUPLE 		= symbol ("SigTuple");
Sym SIGTUPLEACCESS 	= symbol ("SigTupleAccess");

// a tuple of signals is basically a list of signals.
// mode = 0 means normal, mode = 1 means blocked
Tree sigTuple (int mode, Tree ls, Tree box)			{ return tree(SIGTUPLE, tree(mode), ls)->setProperty(box_symbol, box); }
bool isSigTuple (Tree s, int* mode, Tree& ls)		{ Tree m; return isTree(s, SIGTUPLE, m, ls) && isInt(m->node(), mode); }

// Access the components of a tuple.
// ts is tuple of signals, idx is a scalar signal between 0..n
Tree sigTupleAccess(Tree ts, Tree idx, Tree box)	{ return tree(SIGTUPLEACCESS, ts, idx)->setProperty(box_symbol, box); }
bool isSigTupleAccess(Tree s, Tree& ts, Tree& idx)	{ return isTree(s, SIGTUPLEACCESS, ts, idx); }

// create a tuple of signals
Tree sigCartesianProd (Tree s1, Tree s2, Tree box)
{
	Tree 	l1, l2;
	int		m1, m2;

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


	return sigTuple(0, concat(l1,l2), box);
}



/**
 * Test if exp is very simple that is it
 * can't be considered a real component
 * @param exp the signal we want to test
 * @return true if it a very simple signal
 */
bool verySimple(Tree exp)
{
	int		i;
	double	r;
	Tree 	type, name, file;

	return 	isSigInt(exp, &i)
			|| 	isSigReal(exp, &r)
			||	isSigInput(exp, &i)
			||	isSigFConst(exp, type, name, file);
}


/** helper class for testing a predicate on all subsignals or subtrees
 *
 *  parameters:
 *  Test: prediacate to test
 *  test_subsignals: if true, subsignals are traversed, otherwise all branches
 *
 * */
template <typename Test,
          bool test_subsignals>
struct SigChecker
{
    SigChecker(Test const & t = Test()):
        test(t)
    {}

    bool perform(Tree sig)
    {
        if (checked.find(sig) != checked.end())
            return true;

        checked.insert(sig);

        if (!sig->getType())
            return false;

        Tree rgroup;
        int i;

        if (isProj(sig, &i, rgroup))
            return perform(rgroup);

        if (test_subsignals) {
            vector<Tree> subsigs;
            getSubSignals(sig, subsigs);
            for (unsigned int i = 0; i != subsigs.size(); ++i) {
                if (!perform(subsigs[i]))
                    return false;
            }
        } else {
            for (int i = 0; i != sig->arity(); ++i) {
                if (!perform(sig->branch(i)))
                    return false;
            }
        }

        return true;
    }

    Test test;
    set<Tree> checked;
};

struct isTyped
{
    bool operator()(Tree sig) const {return sig->getType();} ;
};

bool sigIsTyped(Tree root)
{
    SigChecker<isTyped, true> checker;
    return checker.perform(root);
}

struct treeIsAnnotated
{
    treeIsAnnotated(Tree prop): property(prop) {}
    bool operator()(Tree sig) const {return sig->getProperty(property);};
    Tree property;
};

bool sigIsAnnotated(Tree root, Tree property)
{
    treeIsAnnotated check(property);
    SigChecker<treeIsAnnotated, true> checker(check);
    return checker.perform(root);
}

bool isAnnotated(Tree root, Tree property)
{
    treeIsAnnotated check(property);
    SigChecker<treeIsAnnotated, true> checker(check);
    return checker.perform(root);
}

bool sigValidInterval(Tree root)
{
    Type t = root->getType();
    if (t && t->getInterval().valid)
        return true;
    else
        return false;
}
