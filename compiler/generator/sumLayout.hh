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
#include <cmath>
#include <cstdint>
#include <utility>
#include <vector>

#include "global.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "sumLanes.hh"

/**
 * The range of an Int32 value, for the decision to wrap an operation on it. Int32 add, sub
 * and mul wrap in two's complement (faust_wrap_*) where the exact result may leave Int32 :
 * signed overflow is undefined in C and C++. Elsewhere the plain operation is the same
 * value and leaves the C++ compiler its no-overflow reasoning. The bounds are int64 : a
 * sum, a difference or a product of two Int32 values is exact there, so the decision is
 * made in exact integer arithmetic.
 */
struct IntRange {
    int64_t lo = INT32_MIN;
    int64_t hi = INT32_MAX;
};

/**
 * The range of an Int32 operand : the interval of its type when it holds for all time (it
 * does not move, the immobile doctrine of the guards) and is certified ; the whole Int32
 * range otherwise, and under -nocert.
 */
inline IntRange intRange(const Type& ty)
{
    interval i = ty->getInterval();
    if (gGlobal->gNoCert || !i.isValid() || i.moves() || !(i.lo() >= double(INT32_MIN)) ||
        !(i.hi() <= double(INT32_MAX))) {
        return {};
    }
    return {int64_t(std::floor(i.lo())), int64_t(std::ceil(i.hi()))};
}

inline IntRange intRange(Tree t)
{
    return intRange(getCertifiedSigType(t));
}

/**
 * r = a op b (kAdd, kSub or kMul) : true when the exact result may leave Int32, the
 * operation then wraps and r is the whole Int32 range.
 */
inline bool intOpWraps(int opcode, const IntRange& a, const IntRange& b, IntRange& r)
{
    int64_t lo = 0, hi = 0;
    if (opcode == kAdd) {
        lo = a.lo + b.lo;
        hi = a.hi + b.hi;
    } else if (opcode == kSub) {
        lo = a.lo - b.hi;
        hi = a.hi - b.lo;
    } else {
        faustassert(opcode == kMul);
        const int64_t p[4] = {a.lo * b.lo, a.lo * b.hi, a.hi * b.lo, a.hi * b.hi};
        lo                 = *std::min_element(p, p + 4);
        hi                 = *std::max_element(p, p + 4);
    }
    const bool wraps = lo < INT32_MIN || hi > INT32_MAX;
    r                = wraps ? IntRange{} : IntRange{lo, hi};
    return wraps;
}

/**
 * Whether the Int32 shift x op k (kLsh, kARsh or kLRsh) takes its defined form : a count
 * that may leave [0, 31] is undefined in C and C++, and is taken modulo 32 (the constant
 * folding, wasm and the hardware) ; a left shift of a negative x, or past Int32, is
 * undefined in C and before C++20, and is done on the unsigned bits.
 */
inline bool shiftWraps(int opcode, const IntRange& x, const IntRange& k)
{
    if (k.lo < 0 || k.hi > 31) {
        return true;
    }
    // x.hi < 2^31 and k.hi <= 31 : the product fits in an int64
    return opcode == kLsh && (x.lo < 0 || x.hi * (int64_t(1) << k.hi) > INT32_MAX);
}

/**
 * Whether the Int32 operation sig = x op y takes its defined form : an add, a sub or a mul
 * that may overflow wraps (intOpWraps), a shift that may be undefined is masked
 * (shiftWraps) ; never for a real operation or another operation.
 */
inline bool binOpWraps(Tree sig, int opcode, Tree x, Tree y)
{
    if (getCertifiedSigType(sig)->nature() != kInt) {
        return false;
    }
    if (opcode == kAdd || opcode == kSub || opcode == kMul) {
        IntRange r;
        return intOpWraps(opcode, intRange(x), intRange(y), r);
    }
    if (opcode == kLsh || opcode == kARsh || opcode == kLRsh) {
        return shiftWraps(opcode, intRange(x), intRange(y));
    }
    return false;
}

/**
 * Whether abs of an Int32 of type ty takes its defined form : abs(INT32_MIN) is undefined in
 * C and C++, and is INT32_MIN again in the defined form (the interval of Abs says so).
 */
inline bool absWraps(const Type& ty)
{
    return ty->nature() == kInt && intRange(ty).lo <= INT32_MIN;
}

/**
 * Whether the Int32 negation sig = -x wraps (x may be INT32_MIN) ; never for a real one.
 */
inline bool negWraps(Tree sig, Tree x)
{
    if (getCertifiedSigType(sig)->nature() != kInt) {
        return false;
    }
    IntRange r;
    return intOpWraps(kSub, IntRange{0, 0}, intRange(x), r);
}

/**
 * The operand x of a negation, neg(x), -1*x or x*-1 : a signed read of x, never a value of its
 * own (spec LE-CONTEXTE-DES-OCCURRENCES) ; nullptr for any other signal.
 */
inline Tree negationOperand(Tree t)
{
    Tree a, b;
    if (isSigNeg(t, a)) {
        return a;
    }
    if (isSigMul(t, a, b)) {
        if (isMinusOne(a)) {
            return b;
        }
        if (isMinusOne(b)) {
            return a;
        }
    }
    return nullptr;
}

/**
 * The terms of Sum(t0, ..., tn) with their signs, in the order of the node, the zeros left
 * out : a negation (negationOperand) or the gain kernel FIR[x, -1] is x subtracted.
 */
inline std::vector<std::pair<bool, Tree>> signedTerms(const tvec& subs)
{
    std::vector<std::pair<bool, Tree>> st;
    for (Tree t : subs) {
        if (isZero(t)) {
            continue;
        }
        tvec fc;
        if (Tree x = negationOperand(t)) {
            st.push_back({false, x});
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
 * the sum is -(n0 + ... + nk-1). An Int32 operation of the chain wraps where its partial
 * result, in the order emitted, may leave Int32 (intOpWraps) ; the interval of the sum
 * alone does not tell, a partial sum can overflow when the whole sum does not.
 *
 * Ops provides term(Tree), negatedTerm(Tree) (the operand of a neg), add(V, V, wrap),
 * sub(V, V, wrap), neg(V, wrap), store(int variability, V) and zero(), the terms compiled
 * in the order of the node.
 */
template <class V, class Ops>
V emitSum(Tree sig, const tvec& subs, Ops& ops)
{
    const int                          vsum  = getCertifiedSigType(sig)->variability();
    const bool                         isInt = getCertifiedSigType(sig)->nature() == kInt;
    std::vector<std::pair<bool, Tree>> st    = signedTerms(subs);
    if (st.empty()) {
        return ops.zero();
    }
    auto rate = [](Tree t) { return getCertifiedSigType(t)->variability(); };
    struct Acc {
        V        value{};
        int      variability = 0;
        int      count       = 0;  ///< terms in the value : two or more, an operation
        IntRange range;            ///< of an Int32 value
    };
    // whether the Int32 operation acc.range op b wraps, acc.range becoming its result
    auto wraps = [&](Acc& acc, int opcode, const IntRange& b) {
        return isInt && intOpWraps(opcode, acc.range, b, acc.range);
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
        V              x  = negated ? ops.negatedTerm(t) : ops.term(t);
        const IntRange xr = isInt ? intRange(t) : IntRange{};
        if (acc.count == 0) {
            acc.value = x;
            acc.range = xr;
        } else if (positive) {
            const bool w = wraps(acc, kAdd, xr);
            acc.value    = ops.add(acc.value, x, w);
        } else {
            const bool w = wraps(acc, kSub, xr);
            acc.value    = ops.sub(acc.value, x, w);
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
        IntRange   r;
        const bool w = isInt && intOpWraps(kSub, IntRange{0, 0}, lead.range, r);
        return ops.neg(lead.value, w);
    }
    Acc acc;
    extend(acc, true, st[first].second, false);
    if (lead.count > 0) {
        if (lead.count >= 2 && lead.variability < acc.variability && lead.variability < vsum) {
            lead.value = ops.store(lead.variability, lead.value);
        }
        const bool w    = wraps(acc, kSub, lead.range);
        acc.value       = ops.sub(acc.value, lead.value, w);
        acc.variability = std::max(acc.variability, lead.variability);
        acc.count       = 2;
    }
    for (size_t k = first + 1; k < st.size(); k++) {
        extend(acc, st[k].first, st[k].second, !st[k].first);
    }
    return acc.value;
}

/**
 * A real factor whose literal in the precision of the generated code is exactly 1 : a
 * product of constants folded in double can land a few ulps away from 1 (the gains of a
 * normalized feedback matrix) and still be written 1.0f in single precision. The product by it is x itself, bit for bit, and is left out. Only the single
 * and double precisions, whose literals are the rounding of the double value.
 */
inline bool isOneAtPrecision(Tree f)
{
    double v;
    int    i;
    if (isSigInt(f, &i)) {
        return i == 1;
    }
    if (!isSigReal(f, &v)) {
        return false;
    }
    if (gGlobal->gFloatSize == 1) {
        return float(v) == 1.0f;
    }
    if (gGlobal->gFloatSize == 2) {
        return v == 1.0;
    }
    return false;
}

/**
 * The code of Prod(f0, ..., fn), shared by the code generators : the chain
 * ((f0 * f1) * ...) * fn of the node, the association its interval follows ; a computed
 * prefix slower than the next factor and than the product is stored at its rate (the
 * normal form puts the slow factors first). A factor that is 1 in the precision of the
 * code is left out (isOneAtPrecision). An Int32 product of the chain wraps where its
 * partial result may leave Int32, as in emitSum. Ops provides term(Tree), mul(V, V, wrap)
 * and store(int variability, V), the factors compiled in the order of the node.
 */
template <class V, class Ops>
V emitProd(Tree sig, const tvec& factors, Ops& ops)
{
    const int vprod = getCertifiedSigType(sig)->variability();
    V         acc{};
    int       variability = 0;
    int       count       = 0;  // factors in acc : two or more, an operation
    // the factors that are not 1 ; a real product keeps a real factor, so that the code
    // still computes in the real type (an int factor alone would make it an int expression)
    const int nprod = getCertifiedSigType(sig)->nature();
    tvec      kept;
    bool      typed = false;
    for (Tree f : factors) {
        if (!isOneAtPrecision(f)) {
            kept.push_back(f);
            typed = typed || getCertifiedSigType(f)->nature() == nprod;
        }
    }
    if (kept.empty() || !typed) {
        kept = factors;
    }
    const bool isInt = nprod == kInt;
    IntRange   range;
    for (Tree f : kept) {
        const int vf = getCertifiedSigType(f)->variability();
        if (count >= 2 && variability < vf && variability < vprod) {
            acc   = ops.store(variability, acc);
            count = 1;
        }
        V              x  = ops.term(f);
        const IntRange fr = isInt ? intRange(f) : IntRange{};
        if (count == 0) {
            acc   = x;
            range = fr;
        } else {
            const bool w = isInt && intOpWraps(kMul, range, fr, range);
            acc          = ops.mul(acc, x, w);
        }
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

/**
 * negativeCoefficient for a coefficient whose node may differ between the instances of the
 * code (a coefficient slot of a family, whose members may hold neg(2) and 3) : the sign is
 * read only on a coefficient fixed for every instance (Ops::fixed).
 */
template <class Ops>
bool filterNegative(Ops& ops, Tree coef, Tree& magnitude)
{
    if (ops.fixed(coef) && isSigNeg(coef, magnitude)) {
        return true;
    }
    if (ops.fixed(coef) && isMinusOne(coef)) {
        magnitude = nullptr;
        return true;
    }
    magnitude = coef;
    return false;
}

/**
 * The layout of the filters, shared by every emitter of a FIR or an IIR : the two code
 * generators, the lowering of -ls and the loop of a family. FIR[x, c1, c2, ...] adds
 * ck * x@(k-1) ; IIR[X, C1, ..., Cn] is y = X + C1 * y@1 + ... + Cn * y@n.
 * - In order : a FIR from its first tap to its last ; an IIR X, then its taps from y@1 to
 *   y@n. A left chain, a null coefficient left out, a coefficient 1 no product, a negative
 *   coefficient (negativeCoefficient) after the first term subtracted.
 * - The late term last (3f.5, markLateTaps : a real filter outside the cone of the memory
 *   decisions, lateTapsLast) : a FIR from its last tap to its first, the tap of delay 0,
 *   computed in the sample, last ; an IIR its feedback taps from y@n to y@1, then X, or,
 *   its FIR input fused (fusedFirInput, Ops::fusable), the delayed taps of the FIR, the
 *   feedback taps, then the tap of delay 0 of the FIR. The early terms read delay lines,
 *   ready from the start of the sample, and one operation waits for the late term ; y@1
 *   last keeps the recurrence at two operations. The chain of the early terms takes the
 *   sign of its first term (no negation), and the late term is written on the left of the
 *   last addition : of two products, a C++ compiler contracts the left one into the FMA.
 * - A real FIR whose first tap is negative and the second positive starts with the second
 *   (-a + b and b - a are the same value, bit for bit) ; a first tap of coefficient -1 is a
 *   negation, not a product by -1.
 * A coefficient is read as zero, one, -1 or a negation only when Ops::fixed says its node is
 * the same for every instance of the code. Every access is compiled before its coefficient,
 * the terms in the order of the chain.
 * Ops provides real (the nature of the filter), fixed(Tree), input() (X), self(int d)
 * (y@d), tap(int d) (x@d of a FIR), firTap(int d) (the source of the fused FIR at d),
 * fusable(Tree fir), coef(Tree c, bool negated) (c, negated : the magnitude of a subtracted
 * coefficient), mul(V, V), add(V, V), sub(V, V), neg(V), negAdd(V, V) (-(a + b)) and zero().
 */
template <class V, class Ops>
V emitFIR(Tree sig, const tvec& fir, Ops& ops)
{
    faustassert(fir.size() > 1);
    std::vector<size_t> taps;
    for (size_t i = 1; i < fir.size(); i++) {
        if (!(ops.fixed(fir[i]) && isZero(fir[i]))) {
            taps.push_back(i);
        }
    }
    if (ops.real && lateTapsLast(sig)) {
        std::reverse(taps.begin(), taps.end());
    }
    if (Tree m0, m1; ops.real && taps.size() >= 2 && filterNegative(ops, fir[taps[0]], m0) &&
                     !filterNegative(ops, fir[taps[1]], m1)) {
        std::swap(taps[0], taps[1]);
    }
    V    acc{};
    bool first = true;
    for (size_t i : taps) {
        V          access = ops.tap(int(i) - 1);
        Tree       m;
        const bool sub = !first && filterNegative(ops, fir[i], m);
        Tree       c   = sub ? m : fir[i];
        V          term;
        if (first && ops.real && ops.fixed(c) && isMinusOne(c)) {
            term = ops.neg(access);
        } else if (c != nullptr && !(ops.fixed(c) && isOne(c))) {
            term = ops.mul(ops.coef(c, sub), access);
        } else {
            term = access;
        }
        acc   = first ? term : (sub ? ops.sub(acc, term) : ops.add(acc, term));
        first = false;
    }
    return first ? ops.zero() : acc;
}

template <class V, class Ops>
V emitIIR(Tree sig, const tvec& iir, Ops& ops)
{
    faustassert(iir.size() > 1);
    // a tap : (subtracted, the product of its magnitude and its access)
    auto product = [&](Tree coef, const V& access) -> std::pair<bool, V> {
        Tree       m;
        const bool sub = filterNegative(ops, coef, m);
        if (m != nullptr && !(ops.fixed(m) && isOne(m))) {
            return {sub, ops.mul(ops.coef(m, sub), access)};
        }
        return {sub, access};
    };
    if (ops.real && lateTapsLast(sig)) {
        tvec       fir;
        const bool fused = fusedFirInput(sig) && isSigFIR(iir[0], fir) && !(ops.fixed(fir[1]) && isZero(fir[1])) &&
                           ops.fusable(iir[0]);
        std::vector<std::pair<bool, V>> early;
        std::pair<bool, V>              last;
        if (fused) {
            for (size_t i = fir.size() - 1; i >= 2; i--) {
                if (!(ops.fixed(fir[i]) && isZero(fir[i]))) {
                    V access = ops.firTap(int(i) - 1);
                    early.push_back(product(fir[i], access));
                }
            }
        } else {
            last = {false, ops.input()};
        }
        for (size_t i = iir.size() - 1; i >= 1; i--) {
            if (!(ops.fixed(iir[i]) && isZero(iir[i]))) {
                V access = ops.self(int(i));
                early.push_back(product(iir[i], access));
            }
        }
        if (fused) {
            V access = ops.firTap(0);
            last     = product(fir[1], access);
        }
        if (early.empty()) {
            return last.first ? ops.neg(last.second) : last.second;
        }
        const bool flip = early[0].first;
        V          fb   = early[0].second;
        for (size_t k = 1; k < early.size(); k++) {
            fb = (early[k].first != flip) ? ops.sub(fb, early[k].second) : ops.add(fb, early[k].second);
        }
        if (!flip && !last.first) {
            return ops.add(last.second, fb);  // the late term on the left
        }
        if (!flip) {
            return ops.sub(fb, last.second);
        }
        if (!last.first) {
            return ops.sub(last.second, fb);
        }
        return ops.negAdd(fb, last.second);
    }
    V acc = ops.input();
    for (size_t i = 1; i < iir.size(); i++) {
        if (ops.fixed(iir[i]) && isZero(iir[i])) {
            continue;
        }
        V    access = ops.self(int(i));
        auto t      = product(iir[i], access);
        acc         = t.first ? ops.sub(acc, t.second) : ops.add(acc, t.second);
    }
    return acc;
}
