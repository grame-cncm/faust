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
 * @brief Implementation of the additive term (`aterm`) class.
 *
 * This file provides the logic for the `aterm` class, which represents
 * a sum of `mterm`s. It is the main driver of Faust's symbolic simplification,
 * handling the deconstruction of expressions, grouping of like terms,
 * factorization, and reconstruction of a final, normalized expression tree.
 */

#include "aterm.hh"
#include "ppsig.hh"
#include "sigtype.hh"

using namespace std;

typedef map<Tree, mterm> SM;

aterm::aterm()
{
}

/**
 * @brief Create a aterm from a tree expression
 */
aterm::aterm(Tree t)
{
#ifdef TRACE
    cerr << "aterm::aterm (" << ppsig(t) << ")" << endl;
#endif
    *this += t;
#ifdef TRACE
    cerr << "aterm::aterm (" << ppsig(t) << ") : -> " << *this << endl;
#endif
}

/**
 * @brief Add two terms trying to simplify the result
 */
Tree simplifyingAdd(Tree t1, Tree t2)
{
    faustassert(t1);
    faustassert(t2);

    if (isNum(t1) && isNum(t2)) {
        return addNums(t1, t2);

    } else if (isZero(t1)) {
        return t2;

    } else if (isZero(t2)) {
        return t1;

    } else if (t1->serial() <= t2->serial()) {
        return sigAdd(t1, t2);

    } else {
        return sigAdd(t2, t1);
    }
}

/**
 * @brief Return the corresponding normalized expression tree
 */

/*====================================================

 addTermsWithSign:

 (s1 v1 s2 v2) -> (s3 v3)

 (s1  0 s2 v2) -> (s2 v2)
 (s1 v1 s2  0) -> (s1 v1)
 (+  v1 +  v2) -> (+ (v1+v2))
 (+  v1 -  v2) -> (+ (v1-v2))
 (-  v1 +  v2) -> (+ (v2-v1))
 (-  v1 -  v2) -> (- (v1+v2))

 */
/**
 * @brief Helper to combine two terms with their signs, producing a new signed term. (New
 * Documentation)
 *
 * Implements the logic for (s1*v1) + (s2*v2), where s1/s2 are signs (+1 or -1).
 * The result is (s3*v3). This helps in reconstructing a canonical expression tree.
 * @param p1 Sign of the first value (true for '+').
 * @param v1 First value tree.
 * @param p2 Sign of the second value.
 * @param v2 Second value tree.
 * @param[out] p3 Sign of the result.
 * @param[out] v3 Result value tree.
 */
static void addTermsWithSign(bool p1, Tree v1, bool p2, Tree v2, bool& p3, Tree& v3)
{
    if (isZero(v1)) {
        p3 = p2;
        v3 = v2;
        return;
    }
    if (isZero(v2)) {
        p3 = p1;
        v3 = v1;
        return;
    }
    if (p1 && p2) {
        p3 = true;
        v3 = sigAdd(v1, v2);
        return;
    }
    if (p1) {
        p3 = true;
        v3 = sigSub(v1, v2);
        return;
    }
    if (p2) {
        p3 = true;
        v3 = sigSub(v2, v1);
        return;
    } else {
        p3 = false;
        v3 = sigAdd(v1, v2);
        return;
    }
}

/**
 * @brief Reconstructs a single, simplified, and canonical Faust expression tree from the aterm.
 *
 * This is the final step of normalization. It rebuilds an expression tree from the
 * simplified internal map of mterms. The process involves:
 * 1. Separating mterms into positive (P) and negative (N) groups, based on their coefficient.
 * 2. Sorting these groups by signal order to create a canonical structure (e.g., signals first).
 * 3. Recombining the sorted terms into a final expression tree, typically in a `(P - N)` form.
 *
 * @return The normalized expression tree.
 */
Tree aterm::normalizedTree() const
{
    // store positive and negative terms by order and sign
    // positive terms are stored in P[]
    // negative terms are inverted (made positive) and stored in N[]
    // terms sorted by order: to better enable the sharing of expensive expressions (like signal
    // over control.etc)
    Tree P[4], N[4];

    // prepare
    for (int order = 0; order < 4; order++) {
        P[order] = N[order] = tree(0);
    }

    // sum by order and sign
    for (const auto& p : fSig2MTerms) {
        const mterm& m = p.second;
        if (m.isNegative()) {
            Tree t     = m.normalizedTree(false, true);  // not in signatureMode
            int  order = getSigOrder(t);
            N[order]   = simplifyingAdd(N[order], t);
        } else {
            Tree t     = m.normalizedTree();
            int  order = getSigOrder(t);
            P[order]   = simplifyingAdd(P[order], t);
        }
    }

    Tree SUM   = subNums(P[0], N[0]);
    bool signe = true;
    Tree R;
    bool s;

    for (int order = 3; order > 0; order--) {
        addTermsWithSign(false, N[order], signe, SUM, s, R);
        signe = s;
        SUM   = R;

        addTermsWithSign(true, P[order], signe, SUM, s, R);
        signe = s;
        SUM   = R;
    }

    if (!signe) {
        SUM = sigBinOp(kMul, sigInt(-1), SUM);
    }

#ifdef TRACE
    cerr << __LINE__ << ":" << __FUNCTION__ << "(" << *this << ") ---> " << ppsig(SUM) << endl;
#endif
    return SUM;
}

/**
 * @brief Print an aterm in a human readable format
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
 * @brief Add in place an additive expression tree. Go down recursively looking
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
 * @brief Substract in place an additive expression tree. Go down to recursively looking
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
 * @brief Add in place an mterm
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
 * @brief Substract in place an mterm
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

/**
 * @brief Finds the greatest common divisor (GCD) among the mterms.
 *
 * This method iterates through all pairs of mterms in the aterm, computes
 * their GCD, and returns the one with the highest "complexity". This "best"
 * GCD is a candidate for factorization to simplify the overall expression.
 * @return The mterm representing the most significant GCD found.
 */
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
 * @brief Reorganize the aterm by factorizing d
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
