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
 * @file aterm.cpp
 * @brief Implementation of additive term representation for signal normalization
 * 
 * This file implements the aterm class, which represents additive expressions
 * as collections of multiplicative terms. The class provides efficient operations
 * for algebraic simplification, factorization, and normalization of signal
 * expressions in the Faust compiler.
 * 
 * Key features:
 * - Automatic grouping of terms with identical signatures
 * - Greatest common divisor computation for factorization
 * - Efficient addition and subtraction operations
 * - Conversion to/from Faust expression trees
 * 
 * @see aterm.hh for class interface documentation
 * @see mterm.cpp for multiplicative term implementation
 */

#include "aterm.hh"
#include "ppsig.hh"
#include "sigtype.hh"

using namespace std;

/// Type alias for the signature-to-mterm mapping
typedef map<Tree, mterm> SM;

/*****************************************************************************
 * ATERM CLASS IMPLEMENTATION
 *****************************************************************************/

/**
 * @brief Default constructor - creates an empty additive term.
 * 
 * Initializes an aterm representing mathematical zero (empty sum).
 */
aterm::aterm()
{
    // Empty map represents zero
}

/**
 * @brief Construct an additive term from a tree expression.
 * 
 * Parses the given tree expression and decomposes it into its constituent
 * multiplicative terms. Handles addition, subtraction, and nested expressions.
 * 
 * @param t The tree expression to convert to additive normal form
 */
aterm::aterm(Tree t)
{
#ifdef TRACE
    cerr << "aterm::aterm (" << ppsig(t) << ")" << endl;
#endif
    // Use the += operator to decompose and add the expression
    *this += t;
#ifdef TRACE
    cerr << "aterm::aterm (" << ppsig(t) << ") : -> " << *this << endl;
#endif
}

/*****************************************************************************
 * GLOBAL UTILITY FUNCTIONS
 *****************************************************************************/

/**
 * @brief Add two expression trees with algebraic simplification.
 * 
 * This function provides an optimized way to add two expression trees
 * by first checking for simple cases (numeric addition, zero operands)
 * before falling back to the full additive term representation.
 * 
 * Optimization cases:
 * - Numeric constants: direct arithmetic evaluation
 * - Zero operands: identity elimination
 * - General case: additive term normalization
 * 
 * @param t1 First expression tree
 * @param t2 Second expression tree
 * @return Simplified sum of the two expressions
 */
Tree simplifyingAdd(Tree t1, Tree t2)
{
    faustassert(t1);
    faustassert(t2);

    // Fast path: add numeric constants directly
    if (isNum(t1) && isNum(t2)) {
        return addNums(t1, t2);
    } 
    // Identity: 0 + x = x
    else if (isZero(t1)) {
        return t2;

    } 
    // Identity: x + 0 = x
    else if (isZero(t2)) {
        return t1;
    } 
    // Canonical ordering: ensure consistent term ordering for normalization
    else if (t1->serial() <= t2->serial()) {
        return sigAdd(t1, t2);
    } else {
        return sigAdd(t2, t1);
    }
}

/*****************************************************************************
 * SIGNED TERM ARITHMETIC
 *****************************************************************************/

/**
 * @brief Add two terms with explicit sign handling.
 * 
 * This function implements signed addition of two terms, handling all
 * combinations of positive and negative signs. It optimizes for zero
 * operands and implements the algebraic rules for signed arithmetic.
 * 
 * Rules implemented:
 * - (s1  0 s2 v2) -> (s2 v2)  [zero elimination]
 * - (s1 v1 s2  0) -> (s1 v1)  [zero elimination]  
 * - (+  v1 +  v2) -> (+ (v1+v2))  [positive addition]
 * - (+  v1 -  v2) -> (+ (v1-v2))  [mixed signs]
 * - (-  v1 +  v2) -> (+ (v2-v1))  [mixed signs]
 * - (-  v1 -  v2) -> (- (v1+v2))  [negative addition]
 * 
 * @param p1 Sign of first term (true=positive, false=negative)
 * @param v1 Value of first term
 * @param p2 Sign of second term (true=positive, false=negative)
 * @param v2 Value of second term
 * @param p3 [out] Resulting sign
 * @param v3 [out] Resulting value
 */
static void addTermsWithSign(bool p1, Tree v1, bool p2, Tree v2, bool& p3, Tree& v3)
{
    // Rule: (s1  0 s2 v2) -> (s2 v2) - first operand is zero
    if (isZero(v1)) {
        p3 = p2;
        v3 = v2;
        return;
    }
    
    // Rule: (s1 v1 s2  0) -> (s1 v1) - second operand is zero
    if (isZero(v2)) {
        p3 = p1;
        v3 = v1;
        return;
    }
    
    // Rule: (+  v1 +  v2) -> (+ (v1+v2)) - both positive
    if (p1 && p2) {
        p3 = true;
        v3 = sigAdd(v1, v2);
        return;
    }
    
    // Rule: (+  v1 -  v2) -> (+ (v1-v2)) - first positive, second negative
    if (p1) {
        p3 = true;
        v3 = sigSub(v1, v2);
        return;
    }
    
    // Rule: (-  v1 +  v2) -> (+ (v2-v1)) - first negative, second positive
    if (p2) {
        p3 = true;
        v3 = sigSub(v2, v1);
        return;
    } 
    // Rule: (-  v1 -  v2) -> (- (v1+v2)) - both negative
    else {
        p3 = false;
        v3 = sigAdd(v1, v2);
        return;
    }
}

/**
 * @brief Convert the additive term back to a normalized expression tree.
 * 
 * This function reconstructs a Faust expression tree from the internal
 * additive term representation. The reconstruction process:
 * 
 * 1. Groups terms by signal order (0-3) and sign (positive/negative)
 * 2. Combines terms within each order group
 * 3. Reconstructs the final expression with proper sign handling
 * 
 * The ordering strategy enables better sharing of expensive expressions
 * (control signals vs. audio signals) in the resulting tree.
 * 
 * Signal orders:
 * - Order 0: Constants (integers, floats)
 * - Order 1: Simple expressions (inputs, constant operations)  
 * - Order 2: Moderate complexity (simple arithmetic)
 * - Order 3: High complexity (delays, recursive signals)
 * 
 * @return The normalized Faust expression tree
 */
Tree aterm::normalizedTree() const
{
    // Store positive and negative terms by signal order and sign
    // Positive terms are stored in P[order]
    // Negative terms are inverted (made positive) and stored in N[order]
    // Terms are sorted by order to enable better sharing of expensive expressions
    Tree P[4], N[4];

    // Initialize all order buckets to zero
    for (int order = 0; order < 4; order++) {
        P[order] = N[order] = tree(0);
    }

    // Classify and sum terms by order and sign
    for (const auto& p : fSig2MTerms) {
        const mterm& m = p.second;
        if (m.isNegative()) {
            // Convert negative term to positive and store in N[]
            Tree t     = m.normalizedTree(false, true);  // not in signatureMode, negate=true
            int  order = getSigOrder(t);
            N[order]   = simplifyingAdd(N[order], t);
        } else {
            // Store positive term directly in P[]
            Tree t     = m.normalizedTree();
            int  order = getSigOrder(t);
            P[order]   = simplifyingAdd(P[order], t);
        }
    }

    // Start with constant terms (order 0): SUM = P[0] - N[0]
    Tree SUM   = subNums(P[0], N[0]);
    bool signe = true;  // Track overall sign
    Tree R;
    bool s;

    // Process higher-order terms (3 down to 1) to build final expression
    // Process in reverse order to put most complex terms first
    for (int order = 3; order > 0; order--) {
        // Add negative terms for this order: SUM = SUM - N[order]
        addTermsWithSign(false, N[order], signe, SUM, s, R);
        signe = s;
        SUM   = R;

        // Add positive terms for this order: SUM = SUM + P[order]
        addTermsWithSign(true, P[order], signe, SUM, s, R);
        signe = s;
        SUM   = R;
    }

    // If final result is negative, multiply by -1
    if (!signe) {
        SUM = sigBinOp(kMul, sigInt(-1), SUM);
    }

#ifdef TRACE
    cerr << __LINE__ << ":" << __FUNCTION__ << "(" << *this << ") ---> " << ppsig(SUM) << endl;
#endif
    return SUM;
}

/**
 * @brief Print an additive term in human-readable format.
 * 
 * Outputs the additive term as a mathematical expression showing
 * all constituent multiplicative terms.
 * 
 * @param dst Output stream to write to
 * @return Reference to the output stream
 */
ostream& aterm::print(ostream& dst) const
{
    if (fSig2MTerms.empty()) {
        dst << "AZERO";
    } else {
        const char* sep = "";
        for (const auto& p : fSig2MTerms) {
            dst << sep << p.second;
            sep = " + ";
        }
    }

    return dst;
}

/**
 * Add in place an additive expression tree. Go down recursively looking
 * for additions and substractions
 */
const aterm& aterm::operator+=(Tree t)
{
    int  op;
    Tree x, y;

    faustassert(t);

    if (isSigBinOp(t, &op, x, y) && (op == kAdd)) {
        *this += x;
        *this += y;

    } else if (isSigBinOp(t, &op, x, y) && (op == kSub)) {
        *this += x;
        *this -= y;

    } else {
        mterm m(t);
        *this += m;
    }
    return *this;
}

/**
 * Substract in place an additive expression tree. Go down to recursively looking
 * for additions and substractions
 */
const aterm& aterm::operator-=(Tree t)
{
    int  op;
    Tree x, y;

    faustassert(t);

    if (isSigBinOp(t, &op, x, y) && (op == kAdd)) {
        *this -= x;
        *this -= y;

    } else if (isSigBinOp(t, &op, x, y) && (op == kSub)) {
        *this -= x;
        *this += y;

    } else {
        mterm m(t);
        *this -= m;
    }
    return *this;
}

/**
 * Add in place an mterm
 */
const aterm& aterm::operator+=(const mterm& m)
{
#ifdef TRACE
    cerr << *this << " aterm::+= " << m << endl;
#endif
    Tree signature = m.signatureTree();
#ifdef TRACE
    cerr << "signature " << *signature << endl;
#endif
    SM::const_iterator p = fSig2MTerms.find(signature);
    if (p == fSig2MTerms.end()) {
        // its a new mterm
        fSig2MTerms.insert(make_pair(signature, m));
    } else {
        // we already have a mterm of same signature, we add them together
        fSig2MTerms[signature] += m;
    }
    return *this;
}

/**
 * Substract in place an mterm
 */
const aterm& aterm::operator-=(const mterm& m)
{
    // cerr << *this << " aterm::-= " << m << endl;
    Tree sig = m.signatureTree();
    // cerr << "signature " << *sig << endl;
    SM::const_iterator p = fSig2MTerms.find(sig);
    if (p == fSig2MTerms.end()) {
        // its a new mterm
        fSig2MTerms.insert(make_pair(sig, m * mterm(-1)));
    } else {
        fSig2MTerms[sig] -= m;
    }
    return *this;
}

mterm aterm::greatestDivisor() const
{
    int   maxComplexity = 0;
    mterm maxGCD(1);
    // cerr << "greatestDivisor of " << *this << endl;

    for (auto p1 = fSig2MTerms.begin(); p1 != fSig2MTerms.end(); p1++) {
        for (auto p2 = std::next(p1); p2 != fSig2MTerms.end(); p2++) {
            mterm g = gcd(p1->second, p2->second);
            // cerr << "TRYING " << g << " of complexity " << g.complexity() << " (max complexity so
            // far " << maxComplexity << ")" << endl;
            int complexity = g.complexity();
            if (complexity > maxComplexity) {
                maxComplexity = complexity;
                maxGCD        = g;
            }
        }
    }
    // cerr << "greatestDivisor of " << *this << " --> " << maxGCD << endl;
    return maxGCD;
}

/**
 * Reorganize the aterm by factorizing d
 */
aterm aterm::factorize(const mterm& d)
{
    // cerr << "factorize : " << *this << " with " << d << endl;
    aterm A;
    aterm Q;

    // separate the multiple of m from the others
    for (const auto& p1 : fSig2MTerms) {
        mterm t = p1.second;
        if (t.hasDivisor(d)) {
            mterm q = t / d;
            // cerr << "q = " << q << endl;
            Q += q;
            // cerr << "step Q = " << Q << endl;
        } else {
            A += t;
            // cerr << "step A = " << A << endl;
        }
    }

    // combines the two parts
    // cerr << "d.normalizedTree() " << ppsig(d.normalizedTree()) << endl;
    // cerr << "Q.normalizedTree() " << ppsig(Q.normalizedTree()) << endl;
    // Tree tt = sigMul(d.normalizedTree(), Q.normalizedTree());
    // cerr << "tt " << *tt << endl;

    // Tree ttt = sigAdd(
    A += sigMul(d.normalizedTree(), Q.normalizedTree());
    // cerr << "Final A = " << A << endl;
    // cerr << "Final Tree " << *(A.normalizedTree()) << endl;
    return A;
}
