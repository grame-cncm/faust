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

/**
 * @file normalize.hh
 * @brief Signal normalization functions for the Faust compiler
 * 
 * This module provides functions to normalize signal expressions into
 * canonical forms. Normalization is a crucial optimization step that
 * simplifies expressions by applying algebraic identities and factorization.
 * 
 * The normalization process includes:
 * - Converting additive terms to Add-Normal form using factorization
 * - Normalizing delay operations with specific algebraic rules
 * - Optimizing multiplicative and divisive operations within delays
 * 
 * @author GRAME
 * @version 2.75+
 */

#ifndef __NORMALIZE__
#define __NORMALIZE__

#include "tree.hh"

/**
 * @brief Compute the Add-Normal form of a term.
 * 
 * This function converts an additive expression tree into its Add-Normal form
 * by factorizing common multiplicative terms. The process uses the aterm class
 * to find the greatest common divisor and factorize accordingly.
 * 
 * The normalization helps reduce redundant computations and creates more
 * efficient signal processing graphs.
 * 
 * @param t The term to be normalized (must be an additive expression)
 * @return The normalized term in Add-Normal form
 * 
 * @see aterm::greatestDivisor()
 * @see aterm::factorize()
 */
Tree normalizeAddTerm(Tree t);

/**
 * @brief Compute the normal form of a 1-sample delay term.
 * 
 * This is a convenience function that normalizes a signal delayed by exactly
 * one sample (s'). It applies the same normalization rules as normalizeDelayTerm
 * with a delay of 1.
 * 
 * Applied normalization rules:
 * - 0' -> 0 (zero delayed is still zero)
 * - (k*s)' -> k*s' (constant factors can be moved outside)
 * - (s/k)' -> s'/k (constant divisors can be moved outside)
 * 
 * @param s The signal term to be delayed by 1 sample
 * @return The normalized delay term
 * 
 * @see normalizeDelayTerm()
 */
Tree normalizeDelay1Term(Tree s);

/**
 * @brief Compute the normal form of a delay term (s@d).
 * 
 * This function normalizes delay operations by applying algebraic rules
 * that preserve the semantic meaning while creating more efficient forms.
 * 
 * Applied normalization rules:
 * - s@0 -> s (zero delay is identity)
 * - 0@d -> 0 (delaying zero gives zero)
 * - (k*s)@d -> k*(s@d) (constants can be factored out)
 * - (s/k)@d -> (s@d)/k (constant divisors can be factored out)
 * - (s@n)@m -> s@(n+m) when n is constant (delay composition)
 * 
 * Note: These rules cannot be applied to addition and subtraction because
 * the initial d samples would have incorrect values.
 * 
 * @param s The signal term to be delayed
 * @param d The delay amount (in samples)
 * @return The normalized delay term
 * 
 * @see getSigOrder() for determining if terms are constant
 * @see sigDelay() for creating delay signals
 */
Tree normalizeDelayTerm(Tree s, Tree d);

#endif
