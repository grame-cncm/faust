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

using namespace std;
#undef TRACE

/**
 * @brief Compute the Add-Normal form of a term t.
 * 
 * This function converts an additive expression into its Add-Normal form by
 * iteratively finding and factorizing the greatest common divisor of all terms.
 * The process continues until no more beneficial factorization is possible.
 * 
 * Algorithm:
 * 1. Convert the expression tree to an additive term (aterm)
 * 2. Find the greatest common divisor of all multiplicative terms
 * 3. If a non-trivial divisor exists, factorize it out
 * 4. Repeat until no more factorization is beneficial
 * 5. Convert back to normalized expression tree
 * 
 * Example: 2*x + 4*x*y -> 2*x*(1 + 2*y)
 * 
 * @param t The additive expression tree to normalize
 * @return The normalized expression tree in Add-Normal form
 */
Tree normalizeAddTerm(Tree t)
{
#ifdef TRACE
    cerr << "START normalizeAddTerm : " << ppsig(t) << endl;
#endif

    // Convert expression to additive term representation
    aterm A(t);
#ifdef TRACE
    cerr << "ATERM of " << A << endl;
#endif
    
    // Iteratively find and factorize greatest common divisors
    mterm D = A.greatestDivisor();
    while (D.isNotZero() && D.complexity() > 0) {
#ifdef TRACE
        cerr << "*** GREAT DIV : " << D << endl;
#endif
        // Factor out the common divisor
        A = A.factorize(D);
        // Look for further factorization opportunities
        D = A.greatestDivisor();
    }
    
    // Convert back to normalized expression tree
    Tree r = A.normalizedTree();
#ifdef TRACE
    cerr << "ATERM of " << A << " --> " << ppsig(r) << endl;
#endif
    return r;
}

/**
 * @brief Compute the normal form of a 1-sample delay term s'.
 * 
 * This is a convenience function that applies delay normalization rules
 * for the common case of a single-sample delay (s').
 * 
 * The normalization rules applied are:
 * - 0' -> 0 (delaying zero gives zero)
 * - (k*s)' -> k*s' (constant factors can be moved outside delay)
 * - (s/k)' -> s'/k (constant divisors can be moved outside delay)
 * 
 * @param s The signal term to be delayed by 1 sample
 * @return The normalized delay term
 */
Tree normalizeDelay1Term(Tree s)
{
    // Delegate to the general delay normalization with delay = 1
    return normalizeDelayTerm(s, tree(1));
}

/**
 * @brief Compute the normal form of a delay term (s@d).
 * 
 * This function applies algebraic rules to normalize delay operations,
 * creating more efficient representations while preserving semantics.
 * 
 * The normalization rules applied are:
 * - s@0 -> s (zero delay is identity)
 * - 0@d -> 0 (delaying zero gives zero)
 * - (k*s)@d -> k*(s@d) when k is constant
 * - (s/k)@d -> (s@d)/k when k is constant  
 * - (s@n)@m -> s@(n+m) when n is constant (delay composition)
 * 
 * Important: These rules cannot be applied to addition and subtraction
 * because the initial d samples would have incorrect values. For example,
 * (a+b)@d ≠ a@d + b@d in general due to initialization differences.
 * 
 * @param s The signal term to be delayed
 * @param d The delay amount (in samples)
 * @return The normalized delay term
 */
Tree normalizeDelayTerm(Tree s, Tree d)
{
    Tree x, y, r;
    int  i;

    // Rule: s@0 -> s (zero delay is identity)
    if (isZero(d)) {
        // Special case: projection signals need to keep their delay structure
        if (isProj(s, &i, r)) {
            return sigDelay(s, d);
        } else {
            return s;
        }

    // Rule: 0@d -> 0 (delaying zero gives zero)
    } else if (isZero(s)) {
        return s;

    // Rule: (k*s)@d -> k*(s@d) when k is constant
    } else if (isSigMul(s, x, y)) {
        // Check if x is constant (order < 2 means compile-time constant)
        if (getSigOrder(x) < 2) {
            return sigMul(x, normalizeDelayTerm(y, d));
        // Check if y is constant
        } else if (getSigOrder(y) < 2) {
            return sigMul(y, normalizeDelayTerm(x, d));
        } else {
            // Neither factor is constant, can't optimize
            return sigDelay(s, d);
        }

    // Rule: (s/k)@d -> (s@d)/k when k is constant
    } else if (isSigDiv(s, x, y)) {
        // Only apply if divisor is constant
        if (getSigOrder(y) < 2) {
            return sigDiv(normalizeDelayTerm(x, d), y);
        } else {
            // Divisor is not constant, can't optimize
            return sigDelay(s, d);
        }

    // Rule: (s@n)@m -> s@(n+m) when n is constant (delay composition)
    } else if (isSigDelay(s, x, y)) {
        // Only apply if inner delay is constant
        if (getSigOrder(y) < 2) {
            // Compose delays: (x@n)@m = x@(n+m)
            return normalizeDelayTerm(x, simplify(sigAdd(d, y)));
        } else {
            // Inner delay is not constant, can't optimize
            return sigDelay(s, d);
        }

    // No applicable rules, return basic delay
    } else {
        return sigDelay(s, d);
    }
}
