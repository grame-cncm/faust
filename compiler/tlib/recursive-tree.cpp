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
#include <stdlib.h>
#include <limits.h>

#include "tlib.hh"
#include "exception.hh"
#include "global.hh"

// Declaration of implementation
static Tree calcDeBruijn2Sym (Tree t);
static Tree substitute(Tree t, int n, Tree id);
static Tree calcsubstitute(Tree t, int level, Tree id);
static Tree liftn(Tree t, int threshold);
static Tree calcliftn(Tree t, int threshold);

//Tree	NOVAR		= tree("NOVAR");

//-----------------------------------------------------------------------------------------
// rec, isRec : declare recursive trees
//-----------------------------------------------------------------------------------------

// de Bruijn declaration of a recursive tree
Tree rec(Tree body)
{
	return tree(gGlobal->DEBRUIJN, body);
}

bool isRec(Tree t, Tree& body)
{
	return isTree(t, gGlobal->DEBRUIJN, body);
}

Tree ref(int level)
{
	faustassert(level > 0);
	return tree(gGlobal->DEBRUIJNREF, tree(level));	// reference to enclosing recursive tree starting from 1
}

bool isRef(Tree t, int& level)
{
	Tree	u;

	if (isTree(t, gGlobal->DEBRUIJNREF, u)) {
		return isInt(u->node(), &level);
	} else {
		return false;
	}
}

//-----------------------------------------------------------------------------------------
// Recursive tree in symbolic notation (using a recursive definition property)
//-----------------------------------------------------------------------------------------

// declaration of a recursive tree using a symbolic variable
Tree rec(Tree var, Tree body)
{
    Tree t = tree(gGlobal->SYMREC, var);
    t->setProperty(gGlobal->RECDEF, body);
    return t;
}

bool isRec(Tree t, Tree& var, Tree& body)
{
    if (isTree(t, gGlobal->SYMREC, var)) {
        body = t->getProperty(gGlobal->RECDEF);
        return true;
    } else {
        return false;
    }
}

Tree ref(Tree id)
{
	return tree(gGlobal->SYMREC, id);			// reference to a symbolic id
}

bool isRef(Tree t, Tree& v)
{
	return isTree(t, gGlobal->SYMREC, v);
}

//-----------------------------------------------------------------------------------------
// L'aperture d'un arbre est la plus profonde reference de Bruijn qu'il contienne.
// Les references symboliques compte pour zero ce qui veut dire qu'un arbre d'aperture
// 0 ne compte aucun reference de bruijn libres.

int CTree::calcTreeAperture( const Node& n, const tvec& br )
{
 	int x;
	if (n == gGlobal->DEBRUIJNREF) {
    
        faustassert(br[0]);
		if (isInt(br[0]->node(), &x)) {
			return x;
		} else {
			return 0;
		}

	} else if (n == gGlobal->DEBRUIJN) {
 
        faustassert(br[0]);
		return br[0]->fAperture - 1;

	} else {
		// return max aperture of branches
		int rc = 0;
		tvec::const_iterator	b = br.begin();
		tvec::const_iterator	z = br.end();
		while (b != z) {
			if ((*b)->aperture() > rc) rc = (*b)->aperture();
			++b;
		}
		return rc;
	}
}

Tree lift(Tree t) { return liftn(t, 1); }

void printSignal(Tree sig, FILE* out, int prec=0);

// lift (t) : increase free references by 1

#if 0
static Tree _liftn(Tree t, int threshold);

static Tree liftn(Tree t, int threshold)
{
	fprintf(stderr, "call of liftn("); printSignal(t, stderr); fprintf(stderr, ", %d)\n", threshold);
	Tree r = _liftn(t, threshold);
	fprintf(stderr, "return of liftn("); printSignal(t, stderr); fprintf(stderr, ", %d) -> ", threshold);
	printSignal(r, stderr); fprintf(stderr, "\n");
	return r;
}
#endif

static Tree liftn(Tree t, int threshold)
{
	Tree L 	= tree( Node(gGlobal->SYMLIFTN), tree(Node(threshold)) );
	Tree t2 = t->getProperty(L);

	if (!t2) {
		t2 = calcliftn(t, threshold);
		t->setProperty(L, t2);
	}
	return t2;
	
}

static Tree calcliftn(Tree t, int threshold)
{
	int		n;
	Tree	u;

	if (isClosed(t)) {

		return t;

	} else if (isRef(t,n)) {

		if (n < threshold) {
			// it is a bounded reference
			return t;
		} else {
			// it is a free reference
			return ref(n+1);
		}

	} else if (isRec(t,u)) {

		return rec(liftn(u, threshold+1));

	} else {
		int n = t->arity();
		//Tree	br[4];
		tvec	br(n);
		for (int i = 0; i < n; i++) {
			br[i] = liftn(t->branch(i), threshold);
		}
		//return CTree::make(t->node(), n, br);
		return CTree::make(t->node(), br);
	}

}

//-----------------------------------------------------------
// Transform a tree from deBruijn to symbolic representation
//-----------------------------------------------------------

Tree deBruijn2Sym (Tree t)
{
	faustassert(isClosed(t));
	Tree t2 = t->getProperty(gGlobal->DEBRUIJN2SYM);

	if (!t2) {
		t2 = calcDeBruijn2Sym(t);
		t->setProperty(gGlobal->DEBRUIJN2SYM, t2);
	}
	return t2;
}

static Tree calcDeBruijn2Sym(Tree t)
{
	Tree 	body, var;
	int		i;

	if (isRec(t,body)) {

		var = tree(unique("W"));
		return rec(var, deBruijn2Sym(substitute(body,1,ref(var))));

	} else if (isRef(t,var)) {

		return t;

	} else if (isRef(t,i)) {

        throw faustexception("ERROR : one Bruijn reference found !\n");
        return t;

	} else {

		//Tree	br[4];
		int 	a = t->arity();
		tvec	br(a);

		for (int i = 0; i < a; i++) {
			br[i] = deBruijn2Sym(t->branch(i));
		}
		//return CTree::make(t->node(), a, br);
		return CTree::make(t->node(), br);
	}
}

static Tree substitute(Tree t, int level, Tree id)
{
	Tree S 	= tree( Node(gGlobal->SUBSTITUTE), tree(Node(level)), id );
	Tree t2 = t->getProperty(S);

	if (!t2) {
		t2 = calcsubstitute(t, level, id);
		t->setProperty(S, t2);
	}
	return t2;
	
}

static Tree calcsubstitute(Tree t, int level, Tree id)
{
	int 	l;
	Tree	body;

	if (t->aperture()<level) {
//		fprintf(stderr, "aperture %d < level %d !!\n", t->aperture(), level);
		return t;
	}
	if (isRef(t,l)) 		 return (l == level) ? id : t;
	if (isRec(t,body)) 		 return rec(substitute(body, level+1, id));

	int 	ar = t->arity();
	//Tree	br[4];
	tvec	br(ar);
	for (int i = 0; i < ar; i++) {
		br[i] = substitute(t->branch(i), level, id);
	}
	//return CTree::make(t->node(), ar, br);
	return CTree::make(t->node(), br);
}


//--------------------------------------------------------------------------
// UpdateAperture (t) : recursively mark open and closed terms.
// closed term : fAperture == 0,  open term fAperture == -1

struct Env {
	Tree fTree; Env* fNext;
	Env(Tree t, Env* nxt) : fTree(t), fNext(nxt) {}
};

static void markOpen(Tree t);
static int recomputeAperture(Tree t, Env* p);
static int orderof (Tree t, Env* p);

void updateAperture(Tree t)
{
	markOpen(t);
	recomputeAperture(t, NULL);
}

//----------------------implementation--------------------------------

static void markOpen(Tree t)
{
	if (t->aperture() == INT_MAX) return;
	t->setAperture(INT_MAX);
	int ar = t->arity();
	for (int i = 0; i < ar; i++) {
		markOpen(t->branch(i));
	}
}

static int recomputeAperture(Tree t, Env* env)
{
	Tree 	var, body;

	if (t->aperture() == 0) return 0;

	if (isRef(t, var)) {

		return orderof(var, env);

	} else if (isRec(t, var, body)) {

		Env e(var,env);
		int a = recomputeAperture(body, &e) - 1;
		if (a<=0) { /*print(t, stderr);*/ t->setAperture(0); }
		return a;

	} else {
		// return max aperture of branches
		int ma = 0;
		int ar = t->arity();
		for (int i = 0; i<ar; i++) {
			int a = recomputeAperture(t->branch(i), env);
			if (ma < a) ma = a;
		}
		if (ma <= 0)  { /*print(t, stderr);*/ t->setAperture(0); }
		return ma;
	}
}

static int orderof (Tree t, Env* p)
{
	if (p == NULL) return 0;
	if (t == p->fTree) return 1;

	int pos = 1;
	while (p != NULL) {
		if (t == p->fTree) return pos;
		p = p->fNext;
		pos++;
	}
	return 0;
}
