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
 
 
 
#include <stdio.h>
#include <assert.h>
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "sigorderrules.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "num.hh"
#include "xtended.hh"
#include <map>

#include "normalize.hh"
 
#undef TRACE

// declarations 
Tree SIMPLIFIED = tree(symbol("sigSimplifiedProp"));
static Tree binequiv (Tree sig, int opnum, Tree a, Tree b);
static Tree simplification (Tree sig);

static Tree traced_simplification(Tree sig)
{
	assert(sig);
#ifdef TRACE
	cerr << ++TABBER << "Start simplification of : " << *sig << endl;
	/*
	fprintf(stderr, "\nStart simplification of : "); 
	printSignal(sig, stderr); 
	fprintf(stderr, "\n");	
	*/
#endif
	Tree r = simplification(sig);
#ifdef TRACE
	cerr << --TABBER << "Simplification of : " << *sig << " Returns : " << *r << endl;
	/*
	fprintf(stderr, "Simplification of : "); 
	printSignal(sig, stderr); 
	fprintf(stderr, " -> ");
	printSignal(r, stderr);	
	fprintf(stderr, "\n");	
	*/
#endif
	return r;
}

Tree simplify (Tree sig)
{
	return tmap(SIMPLIFIED, traced_simplification, sig);
}


// Implementation

static Tree simplification (Tree sig)
{	
	assert(sig);
	int		opnum;
	Tree	t1, t2;

	xtended* xt = (xtended*) getUserData(sig);
	// primitive elements
	if (xt) 								
	{
		//return 3;
		vector<Tree> args;
		for (int i=0; i<sig->arity(); i++) { args.push_back( sig->branch(i) ); }
		return xt->computeSigOutput(args);
		
	} else if (isSigBinOp(sig, &opnum, t1, t2)) {
	
		BinOp* op = gBinOpTable[opnum];
		
		Node n1 = t1->node();
		Node n2 = t2->node();
		
		if (isNum(n1) && isNum(n2)) 		return tree(op->compute(n1,n2));
			
		else if (op->isLeftNeutral(n1)) 	return t2;
			
		else if (op->isRightNeutral(n2)) 	return t1;
			
		else 								return normalizeAddTerm(sig);	
		
	} else if (isSigDelay1(sig, t1)) {
		// delay1(0) = 0
		//Node n1 = t1->node();
		
		//return (isZero(t1)) ? t1 : sig;
		return normalizeDelay1Term (t1);
		
		
	} else if (isSigFixDelay(sig, t1, t2)) {
		
		//return (isZero(t2)) ? t1 : sig;
		return normalizeFixedDelayTerm (t1, t2);
		
		
	} else if (isSigIntCast(sig, t1)) {
		
		Node n1 = t1->node();
		if (isNum(n1)) {
			return tree(int(n1));
		} else {
			return sig;
		}
		
	} else if (isSigFloatCast(sig, t1)) {
		
		Node n1 = t1->node();
		if (isNum(n1)) {
			return tree(float(n1));
		} else {
			return sig;
		}
		
	} else {
		
		return sig;
	}
}
