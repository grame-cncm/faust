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
#include "sigprint.hh"
#include "simplify.hh"
#include "num.hh"
 
// declarations 
Tree SIMPLIFIED = tree(symbol("sigSimplifiedProp"));
static Tree binequiv (Tree sig, int opnum, Tree a, Tree b);
static Tree simplification (Tree sig);


Tree simplify (Tree sig)
{
	return tmap(SIMPLIFIED, simplification, sig);
}


// Implementation

static Tree simplification (Tree sig)
{	
	int		opnum;
	Tree	t1, t2;
		
	if (isSigBinOp(sig, &opnum, t1, t2)) {
		BinOp* op = gBinOpTable[opnum];
		
		Node n1 = t1->node();
		Node n2 = t2->node();
		
		if (isNum(n1) && isNum(n2)) 		return tree(op->compute(n1,n2));
			
		else if (op->isLeftNeutral(n1)) 	return t2;
			
		else if (op->isRightNeutral(n2)) 	return t1;
			
		else 								return binequiv(sig, opnum, t1, t2);
		
	} else if (isSigDelay1(sig, t1)) {
		// delay1(0) = 0
		Node n1 = t1->node();
		return (isZero(n1)) ? t1 : sig;
		
		
	} else if (isSigFixDelay(sig, t1, t2)) {
		Node n2 = t2->node();
		return (isZero(n2)) ? t1 : sig;
		
		
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


/* Règles supplementaires de simplification
	a + (0-y) -> a-y
	(0-y) + b -> b-y
	a - (0-y) -> a+y
	a * (1/y) -> a/y
	(1/y) * b -> b/y
	a / (1/y) -> a*y
	
	a * 0	  -> 0
	0 * a	  -> 0
*/
/*
static void psig(Tree a)
{
	FILE* f = stdout;
	stdout = stderr;
	printSignal(a);
	stdout = f;
}
*/	

Tree binequiv (Tree sig, int opnum, Tree a, Tree b)
{
	int		op;
	Tree	x, y;
/*	
	fprintf(stderr, "binequiv(%d, ", opnum); 
	psig(a); 
	fprintf(stderr, ", ");
	psig(b);
	fprintf(stderr, ")\n\n");
*/	
	if        ( opnum==kAdd && isSigBinOp(b, &op, x, y) && (op == kSub) && isZero(x->node()) ) {
		return simplification(sigBinOp(kSub, a, y));
				
	} else if ( opnum==kAdd && isSigBinOp(a, &op, x, y) && op == kSub && isZero(x->node())) {
		return simplification(sigBinOp(kSub, b, y));
		
	} else if ( opnum==kSub && isSigBinOp(b, &op, x, y) && op == kSub && isZero(x->node())) {
		return simplification(sigBinOp(kAdd, a, y));
		
	} else if ( opnum==kMul && isZero(a->node()) ) {
		return a;
		
	} else if ( opnum==kMul && isZero(b->node()) ) {
		return b;
		
	} else if ( opnum==kMul && isSigBinOp(b, &op, x, y) && op == kDiv && isOne(x->node())) {
		return simplification(sigBinOp(kDiv, a, y));
		
	} else if ( opnum==kMul && isSigBinOp(a, &op, x, y) && op == kDiv && isOne(x->node())) {
		return simplification(sigBinOp(kDiv, b, y));
		
	} else if ( opnum==kDiv && isSigBinOp(b, &op, x, y) && op == kDiv && isOne(x->node())) {
		return simplification(sigBinOp(kMul, a, y));
		
	} else {
		return sig;
	}
}


 
