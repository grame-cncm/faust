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
#include <map>
#include <list>

#include "tlib.hh"
#include "signals.hh"
#include "sigprint.hh"
#include "ppsig.hh"
#include "simplify.hh"
#include "normalize.hh"
#include "sigorderrules.hh"
#include "mterm.hh"
#include "aterm.hh"
#include "exception.hh"

#if 0
static void countAddTerm (map<Tree,Tree>& M, Tree t, bool invflag);
static void incTermCount (map<Tree,int>& M, Tree t, bool invflag);
static Tree buildPowTerm (Tree f, int q);
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
 * 		(s@n)@m -> s@(n+m)
 * Note that the same rules can't be applied to
 * + et - becaue the value of the first d samples
 * would be wrong. We could also add delays such that
 * \param s the term to be delayed
 * \param d the value of the delay
 * \return the normalized term
 */

Tree normalizeFixedDelayTerm(Tree s, Tree d)
{
	Tree x, y, r;
	int i;

	if (isZero(d) && ! isProj(s, &i, r)) {

        return s;

	} else if (isZero(s)) {

        return s;

	} else if (isSigMul(s, x, y)) {

		if (getSigOrder(x) < 2) {
            return /*simplify*/(sigMul(x,normalizeFixedDelayTerm(y,d)));
		} else if (getSigOrder(y) < 2) {
            return /*simplify*/(sigMul(y,normalizeFixedDelayTerm(x,d)));
		} else {
			return sigFixDelay(s,d);
		}

	} else if (isSigDiv(s, x, y)) {

		if (getSigOrder(y) < 2) {
            return /*simplify*/(sigDiv(normalizeFixedDelayTerm(x,d),y));
		} else {
			return sigFixDelay(s,d);
		}

	} else if (isSigFixDelay(s, x, y)) {
		// (x@n)@m = x@(n+m)
//		return sigFixDelay(x,tree(tree2int(d)+tree2int(y)));
		return normalizeFixedDelayTerm(x,simplify(sigAdd(d,y))); 

	} else {

		return sigFixDelay(s,d);
	}
}

