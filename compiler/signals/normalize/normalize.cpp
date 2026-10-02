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

#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <list>
#include <map>

#include "aterm.hh"
#include "sigs-state.hh"
#include "tlib-error.hh"
#include "mterm.hh"
#include "normalize.hh"
#include "ppsig.hh"
#include "signals.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "tlib.hh"

using namespace std;
#undef TRACE

/**
 * The factorization guard (FAUST_OPT=FAUST_SIG_FACTOR_GUARD, under trial), in single
 * precision : factoring a divisor d computed at every sample out of A must not produce
 * a cofactor c0 + t1 + ... + tn computed once outside the sample loop in which a term
 * ti can be tiny next to the constant c0. That cofactor is rounded once : the part of the ti drowned in the
 * rounding of c0 becomes a bias, which a recurrence accumulates (x - h*x factored
 * into x*(1-h), h = 1/SR : an Euler step whose decay rate is off by 0.3 %). Kept as a
 * sum, each product is rounded at every sample, an error without bias. A cofactor
 * that varies at every sample is rounded at every sample anyway : factored.
 * "Tiny" : the lower bound of |ti| over its interval under 2^-10 |c0|.
 */
static bool factorAbsorbs(const aterm& A, const mterm& d)
{
    // the bias argument holds in the sample loop only : a factor d computed at every
    // sample (a recursive state above all) multiplies a cofactor rounded once. A sum
    // computed outside the loop is rounded once whatever its form, and there the
    // factored form is often the more precise (1 - r with r near 1 is exact in float :
    // q - q*r would round q*r first, then cancel)
    Tree dt = d.normalizedTree();
    if (dt->isRecFree()) {
        typeAnnotation(dt, sigs::g.gLocalCausalityCheck);
        if (getCertifiedSigType(dt)->variability() != kSamp) {
            return false;
        }
    }
    double            c0 = 0;
    std::vector<Tree> others;
    for (Tree t : A.cofactor(d).termTrees()) {
        double v;
        if (isSigReal(t, &v)) {
            c0 += v;
        } else if (int i; isSigInt(t, &i)) {
            c0 += i;
        } else {
            others.push_back(t);
        }
    }
    if (c0 == 0 || others.empty()) {
        return false;
    }
    for (Tree t : others) {
        if (!t->isRecFree()) {
            return false;  // a recursion : computed at every sample, no bias (and an open term does not type)
        }
    }
    bool tiny = false;
    for (Tree t : others) {
        typeAnnotation(t, sigs::g.gLocalCausalityCheck);
        Type ty = getCertifiedSigType(t);
        if (ty->variability() == kSamp) {
            return false;  // rounded at every sample : no bias
        }
        auto     I   = ty->getInterval();
        double   mag = (!I.isValid() || (I.lo() <= 0 && I.hi() >= 0)) ? 0.0 : std::min(std::abs(I.lo()), std::abs(I.hi()));
        if (mag < std::ldexp(std::abs(c0), -10)) {
            tiny = true;
        }
    }
    return tiny;
}

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
    // FAUST_SIG_NO_FACTOR : the monomials only, their greatest divisor not factored out
    mterm      D     = sigs::g.gSigNoFactor ? mterm() : A.greatestDivisor();
    const bool guard = sigs::g.gSigFactorGuard && sigs::g.gFloatSize == 1;
    while (D.isNotZero() && D.complexity() > 0) {
        if (guard && factorAbsorbs(A, D)) {
            break;  // the terms stay separate products
        }
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
    return normalizeDelayTerm(s, tree(1));
}

/**
 * Compute the normal form of a delay term (s@d).
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
Tree normalizeDelayTerm(Tree s, Tree d)
{
    Tree x, y, r;
    int  i;

    if (isZero(d)) {
        if (isProj(s, &i, r)) {
            return sigDelay(s, d);
        } else {
            return s;
        }

    } else if (isZero(s)) {
        return s;

    } else if (isSigNeg(s, x)) {
        // (-x)@d -> -(x@d) : the sign stays outside, as the factor -1 did
        return sigNeg(normalizeDelayTerm(x, d));

    } else if (isSigMul(s, x, y)) {
        if (sigs::sigOrder(x) < 2) {
            return /*simplify*/ (sigMul(x, normalizeDelayTerm(y, d)));
        } else if (sigs::sigOrder(y) < 2) {
            return /*simplify*/ (sigMul(y, normalizeDelayTerm(x, d)));
        } else {
            return sigDelay(s, d);
        }

    } else if (isSigDiv(s, x, y)) {
        if (sigs::sigOrder(y) < 2) {
            return /*simplify*/ (sigDiv(normalizeDelayTerm(x, d), y));
        } else {
            return sigDelay(s, d);
        }

    } else if (isSigDelay(s, x, y)) {
        if (sigs::sigOrder(y) < 2) {
            // (x@n)@m = x@(n+m) when n is constant
            // Local fold only : d and y are already simplified, and a full
            // simplify() here would be a transformation inside a transformation
            // (re-entrant driver on a freshly built tree -- the duplication bug
            // fixed structurally in tlib 89742b3 ; the neighbouring commented
            // /*simplify*/ calls show the same doctrine applied historically).
            return normalizeDelayTerm(x, simplifyExpression(sigAdd(d, y)));
        } else {
            return sigDelay(s, d);
        }

    } else {
        return sigDelay(s, d);
    }
}
