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

#include "export.hh"
#include "tlib-error.hh"
#include "tlib.hh"

using namespace std;

// The recursion symbols and property keys are owned by the library. The two
// symbols needed by calcTreeAperture (called on EVERY tree construction) are
// interned lazily and only ever create symbols, never trees -- interning a
// tree from inside calcTreeAperture would recurse into tree construction.
// The property-key TREES (recdefKey, debruijn2symKey) are created lazily too,
// but only from the rec/deBruijn2Sym entry points, never during construction.
// All are reset by tlib::init()/cleanup() (see tlib.cpp).
static Sym  gDebruijnSym     = nullptr;
static Sym  gDebruijnRefSym  = nullptr;
static Sym  gSymRecSym       = nullptr;
static Sym  gSubstituteSym   = nullptr;
static Sym  gSymLiftnSym     = nullptr;
static Tree gRecDefKey       = nullptr;
static Tree gDeBruijn2SymKey = nullptr;

static inline void ensureRecSymbols()
{
    if (gDebruijnSym == nullptr) {
        gDebruijnSym    = symbol("DEBRUIJN");
        gDebruijnRefSym = symbol("DEBRUIJNREF");
        gSymRecSym      = symbol("SYMREC");
        gSubstituteSym  = symbol("SUBSTITUTE");
        gSymLiftnSym    = symbol("LIFTN");
    }
}

static inline Tree recdefKey()
{
    if (gRecDefKey == nullptr) {
        gRecDefKey = tree(symbol("RECDEF"));
    }
    return gRecDefKey;
}

static inline Tree debruijn2symKey()
{
    if (gDeBruijn2SymKey == nullptr) {
        gDeBruijn2SymKey = tree(symbol("deBruijn2Sym"));
    }
    return gDeBruijn2SymKey;
}

// Internal hook used by tlib::init()/cleanup() (see tlib.cpp)
void tlibResetRecInternals()
{
    gDebruijnSym     = nullptr;
    gDebruijnRefSym  = nullptr;
    gSymRecSym       = nullptr;
    gSubstituteSym   = nullptr;
    gSymLiftnSym     = nullptr;
    gRecDefKey       = nullptr;
    gDeBruijn2SymKey = nullptr;
}

// Declaration of implementation
static Tree calcDeBruijn2Sym(Tree t);
static Tree substitute(Tree t, int n, Tree id);
static Tree calcsubstitute(Tree t, int level, Tree id);
Tree        liftn(Tree t, int threshold);
static Tree calcliftn(Tree t, int threshold);

// Tree	NOVAR = tree("NOVAR");

//-----------------------------------------------------------------------------------------
// rec, isRec : declare recursive trees
//-----------------------------------------------------------------------------------------

// de Bruijn declaration of a recursive tree
Tree rec(Tree body)
{
    ensureRecSymbols();
    return tree(gDebruijnSym, body);
}

bool isRec(Tree t, Tree& body)
{
    ensureRecSymbols();
    return isTree(t, gDebruijnSym, body);
}

Tree ref(int level)
{
    ensureRecSymbols();
    TLIB_ASSERT(level > 0);
    return tree(gDebruijnRefSym,
                tree(level));  // reference to enclosing recursive tree starting from 1
}

bool isRef(Tree t, int& level)
{
    Tree u;

    ensureRecSymbols();
    if (isTree(t, gDebruijnRefSym, u)) {
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
    ensureRecSymbols();
    Tree t = tree(gSymRecSym, var);
    t->setProperty(recdefKey(), body);
    return t;
}

bool TLIB_API isRec(Tree t, Tree& var, Tree& body)
{
    ensureRecSymbols();
    if (isTree(t, gSymRecSym, var)) {
        body = t->getProperty(recdefKey());
        return true;
    } else {
        return false;
    }
}

Tree ref(Tree id)
{
    ensureRecSymbols();
    return tree(gSymRecSym, id);  // reference to a symbolic id
}

bool isRef(Tree t, Tree& v)
{
    ensureRecSymbols();
    return isTree(t, gSymRecSym, v);
}

//-----------------------------------------------------------------------------------------
// The aperture of a tree is the deepest deBruijn reference it contains.
// Symbolic references count as zero which means that a tree with aperture
// 0 has no free deBruijn references.

int CTree::calcTreeAperture(const Node& n, const tvec& br)
{
    return calcTreeAperture(n, int(br.size()), br.empty() ? nullptr : br.data());
}

int CTree::calcTreeAperture(const Node& n, int ar, const Tree br[])
{
    int x;
    ensureRecSymbols();
    if (n == gDebruijnRefSym) {
        TLIB_ASSERT(br[0]);
        if (isInt(br[0]->node(), &x)) {
            return x;
        } else {
            return 0;
        }

    } else if (n == gDebruijnSym) {
        TLIB_ASSERT(br[0]);
        return br[0]->fAperture - 1;

    } else {
        // return max aperture of branches
        int rc = 0;
        for (int i = 0; i < ar; ++i) {
            if (br[i]->aperture() > rc) {
                rc = br[i]->aperture();
            }
        }
        return rc;
    }
}

Tree lift(Tree t)
{
    return liftn(t, 1);
}

// lift(t) : increase free references by 1

Tree liftn(Tree t, int threshold)
{
    ensureRecSymbols();
    Tree L  = tree(Node(gSymLiftnSym), tree(Node(threshold)));
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
        int  n1 = t->arity();
        tvec br(n1);
        for (int i = 0; i < n1; i++) {
            br[i] = liftn(t->branch(i), threshold);
        }
        return tree(t->node(), br);
    }
}

//-----------------------------------------------------------
// Transform a tree from deBruijn to symbolic representation
//-----------------------------------------------------------

Tree deBruijn2Sym(Tree t)
{
    TLIB_ASSERT(isClosed(t));
    Tree t2 = t->getProperty(debruijn2symKey());

    if (!t2) {
        t2 = calcDeBruijn2Sym(t);
        t->setProperty(debruijn2symKey(), t2);
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
        tlib::error("ASSERT : free de Bruijn reference found in deBruijn2Sym\n");
        return t;

    } else {
        int  a = t->arity();
        tvec br(a);
        for (int i1 = 0; i1 < a; i1++) {
            br[i1] = deBruijn2Sym(t->branch(i1));
        }
        return tree(t->node(), br);
    }
}

static Tree substitute(Tree t, int level, Tree id)
{
    ensureRecSymbols();
    Tree S  = tree(Node(gSubstituteSym), tree(Node(level)), id);
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
    if (isRef(t, l)) {
        return (l == level) ? id : t;
    }
    if (isRec(t, body)) {
        return rec(substitute(body, level + 1, id));
    }

    int  ar = t->arity();
    tvec br(ar);
    for (int i = 0; i < ar; i++) {
        br[i] = substitute(t->branch(i), level, id);
    }
    return tree(t->node(), br);
}
