/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
 ************************************************************************
 ************************************************************************/

#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include "signals.hh"
#include "sigtyperules.hh"

/**
 * The terms of Sum(t0, ..., tn) with their signs, in the order of the node, the zeros left
 * out : neg(x), a product by -1 or the gain kernel FIR[x, -1] is x subtracted.
 */
inline std::vector<std::pair<bool, Tree>> signedTerms(const tvec& subs)
{
    std::vector<std::pair<bool, Tree>> st;
    for (Tree t : subs) {
        if (isZero(t)) {
            continue;
        }
        Tree a, b;
        tvec fc;
        if (isSigNeg(t, a)) {
            st.push_back({false, a});
        } else if (isSigMul(t, a, b) && isMinusOne(a)) {
            st.push_back({false, b});
        } else if (isSigMul(t, a, b) && isMinusOne(b)) {
            st.push_back({false, a});
        } else if (isSigFIR(t, fc) && fc.size() == 2 && isMinusOne(fc[1])) {
            st.push_back({false, fc[0]});
        } else {
            st.push_back({true, t});
        }
    }
    return st;
}

/**
 * The code of Sum(t0, ..., tn), shared by the code generators : the chain
 * ((t0 + t1) + ...) + tn of the node, the association its interval follows, a negated
 * term subtracted. A computed prefix of the chain slower than the next term and than the
 * sum is stored at its rate (the normal form puts the slow terms first). Leading negated
 * terms n0, ..., nk-1 before the first positive term p are written p - (n0 + ... + nk-1) :
 * the same value, bit for bit, as (-n0 - ... - nk-1) + p, since a rounding to nearest
 * commutes with the negation and an addition with its operands. Without a positive term,
 * the sum is -(n0 + ... + nk-1).
 *
 * Ops provides term(Tree), negatedTerm(Tree) (the operand of a neg), add(V, V), sub(V, V),
 * neg(V), store(int variability, V) and zero(), the terms compiled in the order of the node.
 */
template <class V, class Ops>
V emitSum(Tree sig, const tvec& subs, Ops& ops)
{
    const int                          vsum = getCertifiedSigType(sig)->variability();
    std::vector<std::pair<bool, Tree>> st   = signedTerms(subs);
    if (st.empty()) {
        return ops.zero();
    }
    auto rate = [](Tree t) { return getCertifiedSigType(t)->variability(); };
    struct Acc {
        V   value{};
        int variability = 0;
        int count       = 0;  ///< terms in the value : two or more, an operation
    };
    // acc +/- t, the computed prefix stored first when slower than t and than the sum
    // (the operand of a neg is not read by the sum as a node of its own : the occurrences
    // saw it under the neg, the generator reads it at its rate, negatedTerm)
    auto extend = [&](Acc& acc, bool positive, Tree t, bool negated) {
        const int vt = rate(t);
        if (acc.count >= 2 && acc.variability < vt && acc.variability < vsum) {
            acc.value = ops.store(acc.variability, acc.value);
            acc.count = 1;
        }
        V x = negated ? ops.negatedTerm(t) : ops.term(t);
        if (acc.count == 0) {
            acc.value = x;
        } else {
            acc.value = positive ? ops.add(acc.value, x) : ops.sub(acc.value, x);
        }
        acc.variability = std::max(acc.variability, vt);
        acc.count++;
    };
    size_t first = 0;  // the first positive term
    while (first < st.size() && !st[first].first) {
        first++;
    }
    Acc lead;  // the sum of the leading negated terms
    for (size_t k = 0; k < first; k++) {
        extend(lead, true, st[k].second, true);
    }
    if (first == st.size()) {
        return ops.neg(lead.value);
    }
    Acc acc;
    extend(acc, true, st[first].second, false);
    if (lead.count > 0) {
        if (lead.count >= 2 && lead.variability < acc.variability && lead.variability < vsum) {
            lead.value = ops.store(lead.variability, lead.value);
        }
        acc.value       = ops.sub(acc.value, lead.value);
        acc.variability = std::max(acc.variability, lead.variability);
        acc.count       = 2;
    }
    for (size_t k = first + 1; k < st.size(); k++) {
        extend(acc, st[k].first, st[k].second, !st[k].first);
    }
    return acc.value;
}

/**
 * The code of Prod(f0, ..., fn), shared by the code generators : the chain
 * ((f0 * f1) * ...) * fn of the node, the association its interval follows ; a computed
 * prefix slower than the next factor and than the product is stored at its rate (the
 * normal form puts the slow factors first). Ops provides term(Tree), mul(V, V) and
 * store(int variability, V), the factors compiled in the order of the node.
 */
template <class V, class Ops>
V emitProd(Tree sig, const tvec& factors, Ops& ops)
{
    const int vprod = getCertifiedSigType(sig)->variability();
    V         acc{};
    int       variability = 0;
    int       count       = 0;  // factors in acc : two or more, an operation
    for (Tree f : factors) {
        const int vf = getCertifiedSigType(f)->variability();
        if (count >= 2 && variability < vf && variability < vprod) {
            acc   = ops.store(variability, acc);
            count = 1;
        }
        V x         = ops.term(f);
        acc         = (count == 0) ? x : ops.mul(acc, x);
        variability = std::max(variability, vf);
        count++;
    }
    return acc;
}

/**
 * The sign of a coefficient of a FIR : neg(c) is c subtracted, the same value bit for bit
 * (a negation is exact) ; -1 is the tap subtracted, magnitude then nullptr (no product).
 * magnitude is c, or the coefficient itself. Another negative number stays a literal (no
 * operation, and a fresh number would have no annotation).
 */
inline bool negativeCoefficient(Tree coef, Tree& magnitude)
{
    if (isSigNeg(coef, magnitude)) {
        return true;
    }
    if (isMinusOne(coef)) {
        magnitude = nullptr;
        return true;
    }
    magnitude = coef;
    return false;
}
