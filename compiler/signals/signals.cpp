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

#include <float.h>

#include "global.hh"
#include "signals.hh"
#include "xtended.hh"

Tree sigWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx)
{
	return sigRDTbl(sigWRTbl(gGlobal->nil, sigTable(gGlobal->nil, n, sigGen(init)), widx, wsig), ridx);
}

Tree sigReadOnlyTable(Tree n, Tree init, Tree ridx)
{
	return sigRDTbl(sigTable(gGlobal->nil, n, sigGen(init)), ridx);
}

////////////////////////////////////////////////////////////////////////
/**
 * Signals
 *
 */
///////////////////////////////////////////////////////////////////////

Tree  sigInt(int i) 								{ return tree(i); 					}
bool  isSigInt(Tree t, int* i) 						{ return isInt(t->node(), i); 		}

Tree  sigReal(double r) 							{ return tree(r); 					}
bool  isSigReal(Tree t, double* r) 					{ return isDouble(t->node(), r); 	}

Tree  sigInput(int i)								{ return tree(gGlobal->SIGINPUT, tree(i));	}
bool  isSigInput(Tree t, int* i) 					{ Tree x; return isTree(t, gGlobal->SIGINPUT, x) && isInt(x->node(),i); 	}

Tree  sigOutput(int i, Tree t0)						{ return tree(gGlobal->SIGOUTPUT, tree(i), t0); 	}
bool  isSigOutput(Tree t, int* i, Tree& t0)			{ Tree x; return isTree(t, gGlobal->SIGOUTPUT, x, t0) && isInt(x->node(),i); 	}

Tree  sigDelay0(Tree t0)							{ return sigFixDelay(t0, sigInt(0));}

Tree  sigDelay1(Tree t0)							{ return tree(gGlobal->SIGDELAY1, t0); 		}
bool  isSigDelay1(Tree t, Tree& t0)					{ return isTree(t, gGlobal->SIGDELAY1, t0); 	}

Tree  sigFixDelay(Tree t0, Tree t1)					{ return tree(gGlobal->SIGFIXDELAY, t0, sigIntCast(t1)); 		}
bool  isSigFixDelay(Tree t, Tree& t0, Tree& t1)		{ return isTree(t, gGlobal->SIGFIXDELAY, t0, t1); 	}

Tree  sigPrefix(Tree t0, Tree t1)					{ return tree(gGlobal->SIGPREFIX, t0, t1); 		}
bool  isSigPrefix(Tree t, Tree& t0, Tree& t1)		{ return isTree(t, gGlobal->SIGPREFIX, t0, t1); 	}

Tree  sigIota(Tree t0)								{ return tree(gGlobal->SIGIOTA, t0); 		}
bool  isSigIota(Tree t, Tree& t0)					{ return isTree(t, gGlobal->SIGIOTA, t0); 	}

// Read only and read write tables

Tree sigRDTbl (Tree t, Tree i)						{ return tree(gGlobal->SIGRDTBL, t, i); 	}
bool isSigRDTbl (Tree s, Tree& t, Tree& i)			{ return isTree(s, gGlobal->SIGRDTBL, t, i); 	}

Tree sigWRTbl (Tree id, Tree t, Tree i, Tree s)					{ return tree(gGlobal->SIGWRTBL, id, t, i, s); 	}
bool isSigWRTbl (Tree u, Tree& id, Tree& t, Tree& i, Tree& s)	{ return isTree(u, gGlobal->SIGWRTBL, id, t, i, s); 	}

Tree sigTable (Tree id, Tree n, Tree sig)				{ return tree(gGlobal->SIGTABLE, id, n, sig); 		}
bool isSigTable (Tree t, Tree& id, Tree& n, Tree& sig)	{ return isTree(t, gGlobal->SIGTABLE, id, n, sig); 	}

// Signal used to generate the initial content of a table

Tree sigGen (Tree s)							{ return tree(gGlobal->SIGGEN, s); 		}
bool isSigGen (Tree t, Tree& x)					{ return isTree(t, gGlobal->SIGGEN, x); 	}
bool isSigGen (Tree t)							{ return t->node() == Node(gGlobal->SIGGEN); 	}

// Documentator Tables : special version of tables only for documentation purposes

Tree   sigDocConstantTbl    (Tree n, Tree sig)                  { return tree(gGlobal->SIGDOCONSTANTTBL, n, sig);        }
bool isSigDocConstantTbl    (Tree t, Tree& n, Tree& sig)        { return isTree(t, gGlobal->SIGDOCONSTANTTBL, n, sig); 	}

Tree   sigDocWriteTbl   (Tree n, Tree sig, Tree widx, Tree wsig)                { return tree(gGlobal->SIGDOCWRITETBL, n, sig, widx, wsig); 		}
bool isSigDocWriteTbl   (Tree t, Tree& n, Tree& sig, Tree& widx, Tree& wsig)    { return isTree(t, gGlobal->SIGDOCWRITETBL, n, sig, widx, wsig); 	}

Tree   sigDocAccessTbl   (Tree tbl, Tree ridx)                  { return tree(gGlobal->SIGDOCACCESSTBL, tbl, ridx); 		}
bool isSigDocAccessTbl   (Tree t, Tree& tbl, Tree& ridx)        { return isTree(t, gGlobal->SIGDOCACCESSTBL, tbl, ridx); 	}

// Select on signal among severals

Tree sigSelect2 (Tree selector, Tree s1, Tree s2)							{ return tree(gGlobal->SIGSELECT2, sigIntCast(selector), s1, s2); }
bool isSigSelect2 (Tree t, Tree& selector, Tree& s1, Tree& s2)				{ return isTree(t, gGlobal->SIGSELECT2, selector, s1, s2); }

//  "select3" expresses with "select2"
Tree sigSelect3 (Tree selector, Tree s1, Tree s2, Tree s3)
{
    return sigSelect2(sigBinOp(kEQ, sigIntCast(selector), sigInt(0)),
           sigSelect2(sigBinOp(kEQ, sigIntCast(selector), sigInt(1)), s3, s2), s1);
}
bool isSigSelect3 (Tree t, Tree& selector, Tree& s1, Tree& s2, Tree& s3)	{ return isTree(t, gGlobal->SIGSELECT3, selector, s1, s2, s3); }

// Arithmetical operations

Tree sigBinOp(int op, Tree x, Tree y) 					{ return tree(gGlobal->SIGBINOP, tree(op), x, y); }
bool isSigBinOp(Tree s, int* op, Tree& x, Tree& y) 		{ Tree t; return isTree(s, gGlobal->SIGBINOP, t, x, y) && isInt(t->node(),op); }

// Foreign Functions

Tree sigFFun (Tree ff, Tree largs)						{ return tree(gGlobal->SIGFFUN, ff, largs); 			}
bool isSigFFun	(Tree s, Tree& ff, Tree& largs)			{ return isTree(s, gGlobal->SIGFFUN, ff, largs);		}

Tree sigFConst      (Tree type, Tree name, Tree file)             { return tree(gGlobal->SIGFCONST, type, name, file);         }
bool isSigFConst    (Tree s)                                      { Tree t,n,f; return isTree(s, gGlobal->SIGFCONST, t, n, f); }
bool isSigFConst    (Tree s, Tree& type, Tree& name, Tree& file)  { return isTree(s, gGlobal->SIGFCONST,type, name, file);     }

Tree sigFVar      (Tree type, Tree name, Tree file)               { return tree(gGlobal->SIGFVAR, type, name, file);           }
bool isSigFVar    (Tree s)                                        { Tree t,n,f; return isTree(s, gGlobal->SIGFVAR, t, n, f);   }
bool isSigFVar    (Tree s, Tree& type, Tree& name, Tree& file)    { return isTree(s, gGlobal->SIGFVAR, type, name, file);      }

// nouvelle version utilisant rec et ref

Tree sigProj (int i, Tree rgroup)				{ return tree(gGlobal->SIGPROJ, tree(i), rgroup); 	}
bool isProj (Tree t, int* i, Tree& rgroup)		{ Tree x; return isTree(t, gGlobal->SIGPROJ, x, rgroup) && isInt(x->node(), i); 	}

// Int and Float casting

Tree  sigIntCast(Tree t)						
{ 
	Node n = t->node();
	
	int i; 		if (isInt(n, &i)) 			return t; 
	double x;	if (isDouble(n, &x)) 		return tree(int(x));
				if (isSigIntCast(t))		return t;
	 
	return tree(gGlobal->SIGINTCAST, t);   
}

Tree  sigFloatCast(Tree t)						
{ 
	Node n = t->node();
	
	int i; 		if (isInt(n, &i)) 			return tree(double(i)); 
	double x;	if (isDouble(n, &x)) 		return t;
				if (isSigFloatCast(t))		return t;
                if (isSigInput(t, &i))      return t;
	 
	return tree(gGlobal->SIGFLOATCAST, t);   
}

//Tree  sigFloatCast(Tree t)						{ return isSigFloatCast(t)? t : tree(gGlobal->SIGFLOATCAST, t); }

bool  isSigIntCast(Tree t)						{ Tree x; return isTree(t, gGlobal->SIGINTCAST, x); 	}
bool  isSigIntCast(Tree t, Tree& x)				{ return isTree(t, gGlobal->SIGINTCAST, x); 			}

bool  isSigFloatCast(Tree t)					{ Tree x; return isTree(t, gGlobal->SIGFLOATCAST, x);}
bool  isSigFloatCast(Tree t, Tree& x)			{ return isTree(t, gGlobal->SIGFLOATCAST, x); 		}

/*****************************************************************************
							 User Interface Elements
*****************************************************************************/

Tree sigButton 	 (Tree lbl)					{ return tree(gGlobal->SIGBUTTON, lbl); 					}
bool isSigButton (Tree s)					{ Tree lbl; return isTree(s, gGlobal->SIGBUTTON, lbl);	}
bool isSigButton (Tree s, Tree& lbl)		{ return isTree(s, gGlobal->SIGBUTTON, lbl);				}

Tree sigCheckbox   (Tree lbl)				{ return tree(gGlobal->SIGCHECKBOX, lbl); 				}
bool isSigCheckbox (Tree s)					{ Tree lbl; return isTree(s, gGlobal->SIGCHECKBOX, lbl);	}
bool isSigCheckbox (Tree s, Tree& lbl)		{ return isTree(s, gGlobal->SIGCHECKBOX, lbl);           }

Tree sigWaveform (const tvec& wf)           { return tree(gGlobal->SIGWAVEFORM, wf);                 }
bool isSigWaveform(Tree s)                  { return isTree(s, gGlobal->SIGWAVEFORM);   }

Tree sigHSlider   (Tree lbl, Tree cur, Tree min, Tree max, Tree step)
											{ return tree(gGlobal->SIGHSLIDER, lbl, list4(cur,min,max,step));		}
bool isSigHSlider (Tree s)					{ Tree lbl, params; return isTree(s, gGlobal->SIGHSLIDER, lbl, params);	}

bool isSigHSlider (Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
	Tree params;
	if (isTree(s, gGlobal->SIGHSLIDER, lbl, params)) {
		cur = nth(params, 0);
		min = nth(params, 1);
		max = nth(params, 2);
		step= nth(params, 3);
		return true;
	} else {
		return false;
	}
}

Tree sigVSlider   (Tree lbl, Tree cur, Tree min, Tree max, Tree step)
											{ return tree(gGlobal->SIGVSLIDER, lbl, list4(cur,min,max,step));		}
bool isSigVSlider (Tree s)					{ Tree lbl, params; return isTree(s, gGlobal->SIGVSLIDER, lbl, params);	}

bool isSigVSlider (Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
	Tree params;
	if (isTree(s, gGlobal->SIGVSLIDER, lbl, params)) {
		cur = nth(params, 0);
		min = nth(params, 1);
		max = nth(params, 2);
		step= nth(params, 3);
		return true;
	} else {
		return false;
	}
}

Tree sigNumEntry   (Tree lbl, Tree cur, Tree min, Tree max, Tree step)
											{ return tree(gGlobal->SIGNUMENTRY, lbl, list4(cur,min,max,step));		}
bool isSigNumEntry (Tree s)					{ Tree lbl, params; return isTree(s, gGlobal->SIGNUMENTRY, lbl, params);	}

bool isSigNumEntry (Tree s, Tree& lbl, Tree& cur, Tree& min, Tree& max, Tree& step)
{
	Tree params;
	if (isTree(s, gGlobal->SIGNUMENTRY, lbl, params)) {
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

Tree sigHBargraph   (Tree lbl, Tree min, Tree max, Tree x)				{ return tree(gGlobal->SIGHBARGRAPH, lbl, min, max, x);		}
bool isSigHBargraph (Tree s)											{ Tree lbl, min, max, x; return isTree(s, gGlobal->SIGHBARGRAPH, lbl, min, max, x);	}
bool isSigHBargraph (Tree s, Tree& lbl, Tree& min, Tree& max, Tree& x)	{ return isTree(s, gGlobal->SIGHBARGRAPH, lbl, min, max, x);	}

Tree sigVBargraph   (Tree lbl, Tree min, Tree max, Tree x)				{ return tree(gGlobal->SIGVBARGRAPH, lbl, min, max, x);		}
bool isSigVBargraph (Tree s)											{ Tree lbl, min, max, x; return isTree(s, gGlobal->SIGVBARGRAPH, lbl, min, max, x);	}
bool isSigVBargraph (Tree s, Tree& lbl, Tree& min, Tree& max, Tree& x)	{ return isTree(s, gGlobal->SIGVBARGRAPH, lbl, min, max, x);	}

Tree  sigAttach(Tree t0, Tree t1)					{ return tree(gGlobal->SIGATTACH, t0, t1); 		}
bool  isSigAttach(Tree t, Tree& t0, Tree& t1)		{ return isTree(t, gGlobal->SIGATTACH, t0, t1); 	}

Tree  sigEnable(Tree t0, Tree t1)					{ return tree(gGlobal->SIGENABLE, t0, t1); 		}
bool  isSigEnable(Tree t, Tree& t0, Tree& t1)		{ return isTree(t, gGlobal->SIGENABLE, t0, t1); 	}

Tree  sigControl(Tree t0, Tree t1)					{ return tree(gGlobal->SIGCONTROL, t0, t1); 		}
bool  isSigControl(Tree t, Tree& t0, Tree& t1)		{ return isTree(t, gGlobal->SIGCONTROL, t0, t1); 	}

bool sameMagnitude(Tree a, Tree b)
{
    return sameMagnitude(a->node(), b->node());
}

Tree addNums(Tree a, Tree b)
{
	Tree r = tree(addNode(a->node(),b->node()));
	//cerr.flags(ios::showpoint); cerr << "addNums " << *a << "+" << *b << " -> " << *r << endl;
	return r;
}

Tree subNums(Tree a, Tree b)
{
	Tree r = tree(subNode(a->node(),b->node()));
	//cerr.flags(ios::showpoint); cerr << "subNums " << *a << "-" << *b << " -> " << *r << endl;
	return r;
}

Tree mulNums(Tree a, Tree b)
{
	Tree r = tree(mulNode(a->node(),b->node()));
	//cerr.flags(ios::showpoint); cerr << "mulNums " << *a << "*" << *b << " -> " << *r << endl;
	return r;
}

//Tree divNums(Tree a, Tree b)
//{
//	Tree r = tree(divNode(a->node(),b->node()));
//	//cerr.flags(ios::showpoint); cerr << "divNums " << *a << "/" << *b << " -> " << *r << endl;
//	return r;
//}

Tree divExtendedNums(Tree a, Tree b)
{
    //cerr.flags(ios::showpoint); cerr << "divExtendeNums " << *a << "/" << *b << " -> " << endl;
	Tree r = tree(divExtendedNode(a->node(),b->node()));
	//cerr.flags(ios::showpoint); cerr << "divExtendeNums " << *a << "/" << *b << " -> " << *r << endl;
	return r;
}

Tree minusNum(Tree a)
{
	Tree r = tree(minusNode(a->node()));
	//cerr.flags(ios::showpoint); cerr << "minusNum " << *a << " -> " << *r << endl;
	return r;
}

Tree inverseNum(Tree a)
{
	Tree r = tree(inverseNode(a->node()));
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
							 Sounfiles
*****************************************************************************/
/*
 A boxSounfile(label,c) has 1 input channel and c+3 output channels:
 0   sigSoundfileLength(label):  the number of frames of the soundfile (NK)
 1   sigSoundfileRate(label): the sampling rate encoded in the file (NK)
 2   sigSoundfileChannels(label): the number of channels of the file (NK)
 3.. sigSoundfileBuffer(label, c, ridx): the cth channel content (RK ou RS)
*/
Tree sigSoundfile(Tree label)							{ return tree(gGlobal->SIGSOUNDFILE, label); }
Tree sigSoundfileLength(Tree sf)						{ return tree(gGlobal->SIGSOUNDFILELENGTH, sf); }
Tree sigSoundfileRate(Tree sf)							{ return tree(gGlobal->SIGSOUNDFILERATE, sf); }
Tree sigSoundfileChannels(Tree sf)						{ return tree(gGlobal->SIGSOUNDFILECHANNELS, sf); }
Tree sigSoundfileBuffer(Tree sf, Tree chan, Tree ridx)	{ return tree(gGlobal->SIGSOUNDFILEBUFFER, sf, chan, ridx); }

bool isSigSoundfile(Tree s, Tree& label)				{ return isTree(s, gGlobal->SIGSOUNDFILE, label); }
bool isSigSoundfileLength(Tree s, Tree& sf)				{ return isTree(s, gGlobal->SIGSOUNDFILELENGTH, sf); }
bool isSigSoundfileRate(Tree s, Tree& sf)				{ return isTree(s, gGlobal->SIGSOUNDFILERATE, sf); }
bool isSigSoundfileChannels(Tree s, Tree& sf)			{ return isTree(s, gGlobal->SIGSOUNDFILECHANNELS, sf); }
bool isSigSoundfileBuffer(Tree s, Tree& sf, Tree& chan, Tree& ridx)
															{ return isTree(s, gGlobal->SIGSOUNDFILEBUFFER, sf, chan, ridx); }
/*****************************************************************************
							 matrix extension
*****************************************************************************/

// a tuple of signals is basically a list of signals.
// mode = 0 means normal, mode = 1 means blocked
Tree sigTuple (int mode, Tree ls)					{ return tree(gGlobal->SIGTUPLE, tree(mode), ls); }
bool isSigTuple (Tree s, int* mode, Tree& ls)		{ Tree m; return isTree(s, gGlobal->SIGTUPLE, m, ls) && isInt(m->node(), mode); }

// Access the components of a tuple.
// ts is tuple of signals, idx is a scalar signal between 0..n
Tree sigTupleAccess(Tree ts, Tree idx)				{ return tree(gGlobal->SIGTUPLEACCESS, ts, idx); }
bool isSigTupleAccess(Tree s, Tree& ts, Tree& idx)	{ return isTree(s, gGlobal->SIGTUPLEACCESS, ts, idx); }

// create a tuple of signals
Tree sigCartesianProd (Tree s1, Tree s2)
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

	return sigTuple(0, concat(l1,l2));
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

/*****************************************************************************
							 FTZ wrapping
    Add FTZ wrapping to a signal
*****************************************************************************/

// \(x).(select2(abs(x)<mmm, x, 0))

Tree sigFTZ (Tree s)
{
	return tree(gGlobal->gFtzPrim->symbol(), s);
}
