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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "exception.hh"
#include "global.hh"
#include "tlib.hh"
#include "faust/export.h"

using namespace std;

// Declaration of implementation
static Tree calcDeBruijn2Sym(Tree t);
static Tree substitute(Tree t, int n, Tree id);
static Tree calcsubstitute(Tree t, int level, Tree id);
Tree liftn(Tree t, int threshold);
static Tree calcliftn(Tree t, int threshold);

// Tree	NOVAR = tree("NOVAR");

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
    return tree(gGlobal->DEBRUIJNREF, tree(level));  // reference to enclosing recursive tree starting from 1
}

bool isRef(Tree t, int& level)
{
    Tree u;

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

bool LIBFAUST_API isRec(Tree t, Tree& var, Tree& body)
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
    return tree(gGlobal->SYMREC, id);  // reference to a symbolic id
}

bool isRef(Tree t, Tree& v)
{
    return isTree(t, gGlobal->SYMREC, v);
}

//-----------------------------------------------------------------------------------------
// The aperture of a tree is the deepest deBruijn reference it contains.
// Symbolic references count as zero which means that a tree with aperture
// 0 has no free deBruijn references.

int CTree::calcTreeAperture(const Node& n, const tvec& br)
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
        int                  rc = 0;
        tvec::const_iterator b  = br.begin();
        tvec::const_iterator z  = br.end();
        while (b != z) {
            if ((*b)->aperture() > rc) rc = (*b)->aperture();
            ++b;
        }
        return rc;
    }
}

Tree lift(Tree t)
{
    return liftn(t, 1);
}

void printSignal(Tree sig, FILE* out, int prec = 0);

// lift(t) : increase free references by 1

#if 0
static Tree _liftn(Tree t, int threshold);

Tree liftn(Tree t, int threshold)
{
	fprintf(stderr, "call of liftn("); printSignal(t, stderr); fprintf(stderr, ", %d)\n", threshold);
	Tree r = _liftn(t, threshold);
	fprintf(stderr, "return of liftn("); printSignal(t, stderr); fprintf(stderr, ", %d) -> ", threshold);
	printSignal(r, stderr); fprintf(stderr, "\n");
	return r;
}
#endif

Tree liftn(Tree t, int threshold)
{
    Tree L  = tree(Node(gGlobal->SYMLIFTN), tree(Node(threshold)));
    Tree t2 = t->getProperty(L);

    if (!t2) {
        t2 = calcliftn(t, threshold);
        t->setProperty(L, t2);
    }
    return t2;
}

static Tree calcliftn(Tree t, int threshold)
{
    int  n;
    Tree u;

    if (isClosed(t)) {
        return t;

    } else if (isRef(t, n)) {
        if (n < threshold) {
            // it is a bounded reference
            return t;
        } else {
            // it is a free reference
            return ref(n + 1);
        }

    } else if (isRec(t, u)) {
        return rec(liftn(u, threshold + 1));

    } else {
        int n1 = t->arity();
        tvec br(n1);
        for (int i = 0; i < n1; i++) {
            br[i] = liftn(t->branch(i), threshold);
        }
        return CTree::make(t->node(), br);
    }
}

//-----------------------------------------------------------
// Transform a tree from deBruijn to symbolic representation
//-----------------------------------------------------------

Tree deBruijn2Sym(Tree t)
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
    Tree body, var;
    int  i;

    if (isRec(t, body)) {
        var = tree(unique("W"));
        return rec(var, deBruijn2Sym(substitute(body, 1, ref(var))));

    } else if (isRef(t, var)) {
        return t;

    } else if (isRef(t, i)) {
        cerr << "ASSERT : one Bruijn reference found\n";
        faustassert(false);
        return t;

    } else {
        int  a = t->arity();
        tvec br(a);
        for (int i1 = 0; i1 < a; i1++) {
            br[i1] = deBruijn2Sym(t->branch(i1));
        }
        return CTree::make(t->node(), br);
    }
}

static Tree substitute(Tree t, int level, Tree id)
{
    Tree S  = tree(Node(gGlobal->SUBSTITUTE), tree(Node(level)), id);
    Tree t2 = t->getProperty(S);

    if (!t2) {
        t2 = calcsubstitute(t, level, id);
        t->setProperty(S, t2);
    }
    return t2;
}

static Tree calcsubstitute(Tree t, int level, Tree id)
{
    int  l;
    Tree body;

    if (t->aperture() < level) {
        // fprintf(stderr, "aperture %d < level %d !!\n", t->aperture(), level);
        return t;
    }
    if (isRef(t, l)) return (l == level) ? id : t;
    if (isRec(t, body)) return rec(substitute(body, level + 1, id));

    int ar = t->arity();
    tvec br(ar);
    for (int i = 0; i < ar; i++) {
        br[i] = substitute(t->branch(i), level, id);
    }
    return CTree::make(t->node(), br);
}
