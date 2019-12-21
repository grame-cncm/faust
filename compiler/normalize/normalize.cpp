/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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
#include <list>
#include <map>

#include "aterm.hh"
#include "exception.hh"
#include "mterm.hh"
#include "normalize.hh"
#include "ppsig.hh"
#include "signals.hh"
#include "sigorderrules.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "tlib.hh"

#if 0
static void countAddTerm(map<Tree,Tree>& M, Tree t, bool invflag);
static void incTermCount(map<Tree,int>& M, Tree t, bool invflag);
static Tree buildPowTerm(Tree f, int q);
static Tree simplifyingReorganizingMul(Tree t1, Tree t2);
static Tree reorganizingMul(Tree k, Tree t);
static void factorizeAddTerm(map<Tree,Tree>& M);
#endif

#undef TRACE

/**
 * Compute the Add-Normal form of a term t.
 * \param t the term to be normalized
 * \return the normalized term
 */
Tree normalizeAddTerm(Tree t)
{
#ifdef TRACE
    cerr << "START normalizeAddTerm : " << ppsig(t) << endl;
#endif

    aterm A(t);
#ifdef TRACE
    cerr << "ATERM of " << A << endl;
#endif
    mterm D = A.greatestDivisor();
    while (D.isNotZero() && D.complexity() > 0) {
#ifdef TRACE
        cerr << "*** GREAT DIV : " << D << endl;
#endif
        A = A.factorize(D);
        D = A.greatestDivisor();
    }
    Tree r = A.normalizedTree();
#ifdef TRACE
    cerr << "ATERM of " << A << " --> " << ppsig(r) << endl;
#endif
    return r;
}

/**
 * Compute the normal form of a 1-sample delay term s'.
 * The normalisation rules are :
 *     	0' -> 0 /// INACTIVATE dec07 bug recursion
 *     	(k*s)' -> k*s'
 *		(s/k)' -> s'/k
 * \param s the term to be delayed by 1 sample
 * \return the normalized term
 */
Tree normalizeDelay1Term(Tree s)
{
    return normalizeFixedDelayTerm(s, tree(1));
}

/**
 * Compute the normal form of a fixed delay term (s@d).
 * The normalisation rules are :
 *		s@0 -> s
 *     	0@d -> 0
 *     	(k*s)@d -> k*(s@d)
 *		(s/k)@d -> (s@d)/k
 * 		(s@n)@m -> s@(n+m) and n is constant
 * Note that the same rules can't be applied to
 * + and - because the value of the first d samples
 * would be wrong.
 * \param s the term to be delayed
 * \param d the value of the delay
 * \return the normalized term
 */

Tree normalizeFixedDelayTerm(Tree s, Tree d)
{
    Tree x, y, r;
    int  i;

    if (isZero(d)) {
        if (isProj(s, &i, r)) {
            return sigFixDelay(s, d);
        } else {
            return s;
        }

    } else if (isZero(s)) {
        return s;

    } else if (isSigMul(s, x, y)) {
        if (getSigOrder(x) < 2) {
            return /*simplify*/ (sigMul(x, normalizeFixedDelayTerm(y, d)));
        } else if (getSigOrder(y) < 2) {
            return /*simplify*/ (sigMul(y, normalizeFixedDelayTerm(x, d)));
        } else {
            return sigFixDelay(s, d);
        }

    } else if (isSigDiv(s, x, y)) {
        if (getSigOrder(y) < 2) {
            return /*simplify*/ (sigDiv(normalizeFixedDelayTerm(x, d), y));
        } else {
            return sigFixDelay(s, d);
        }

    } else if (isSigFixDelay(s, x, y)) {
        if (getSigOrder(y) < 2) {
            // (x@n)@m = x@(n+m) when n is constant
            return normalizeFixedDelayTerm(x, simplify(sigAdd(d, y)));
        } else {
            return sigFixDelay(s, d);
        }

    } else {
        return sigFixDelay(s, d);
    }
}
