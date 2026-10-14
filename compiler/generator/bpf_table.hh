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
#include <vector>

#include "global.hh"
#include "signals.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

/**
 * The table of cells of a break-point function Bpf(x; t1, ..., tn; r0, ..., rn) : the
 * region of x found in constant time instead of by the chain of comparisons, whose
 * branches depend on the data. A uniform grid of step h, at most half the smallest gap
 * between two thresholds, covers [t1, tn[ ; each cell gives the region of its left edge.
 * The code computes
 *
 *     xc = x < t1 ? t1 : (x < tn ? x : t1)            (finite : a NaN x gives t1)
 *     k  = min(int((xc - t1) * (1/h)), K - 1)          (k >= 0 since xc >= t1)
 *     r  = cell[k], corrected by the thresholds : r += xc >= hi[r] twice, r -= xc < lo[r]
 *     r  = x < t1 ? 0 : (x < tn ? r : n)               (a NaN x : the last region)
 *     y  = a[r] + b[r] * (xc - c[r])
 *
 * A region may compute with x or with one other variable u (the normal form writes the
 * regions of x = u + m in u) : useU[r] says which, uc = u inside [t1, tn[, 0 outside.
 * The rounding of k moves it by one cell at most, which the corrections absorb (a cell
 * holds at most one threshold). The arrays are padded so that no index leaves them,
 * whatever the floating-point arithmetic. Each region is a + b * (x - c), the same
 * computation, bit for bit, as the expression of the normal form it comes from (a
 * constant, b * x, a + b * (x - c), a + b * (c - x) as a + (-b) * (x - c)) ; the outer
 * regions are constants, computed at xc = t1 so that an infinite x never meets 0 * inf.
 * The table is used for x at the sample rate and four thresholds or more ; otherwise, or
 * for a region of another form, the chain stays.
 */
struct BpfTable {
    std::vector<double> lo, hi;     ///< the range of each region, padded
    std::vector<double> a, b, c;    ///< the region r : a[r] + b[r] * (x - c[r])
    std::vector<int>    cell;       ///< the region at the left edge of each cell
    std::vector<int>    useU;       ///< the region computes with u instead of x
    Tree                u = nullptr;  ///< the other variable of the regions, or nullptr
    double              t1 = 0, tn = 0, invh = 0;
    int                 n  = 0;     ///< the number of thresholds
    int                 K  = 0;     ///< the number of cells
};

namespace bpftable {

inline bool numVal(Tree t, double& v)
{
    int i;
    if (isSigReal(t, &v)) return true;
    if (isSigInt(t, &i)) {
        v = i;
        return true;
    }
    return false;
}

/// a variable : a tree that is not a number
inline bool variable(Tree t)
{
    double v;
    return !numVal(t, v);
}

/// d is x - c, x a variable (c = -m for x + m, m + x ; c = m for x - m) : gives x and c ;
/// or c - x : gives x and c, and flips the sign of the slope ; or x itself, c = 0
inline bool differenceOf(Tree d, Tree& x, double& c, bool& flip)
{
    tvec ts;
    Tree u, v, w;
    int  op;
    double m;
    flip = false;
    if (isSigSum(d, ts) && ts.size() == 2) {
        u = ts[0], v = ts[1];
        if (numVal(u, m) && isSigNeg(v, w) && variable(w)) return x = w, c = m, flip = true, true;
        if (numVal(v, m) && isSigNeg(u, w) && variable(w)) return x = w, c = m, flip = true, true;
        if (variable(u) && numVal(v, m)) return x = u, c = -m, true;
        if (variable(v) && numVal(u, m)) return x = v, c = -m, true;
        return false;
    }
    if (isSigBinOp(d, &op, u, v) && (op == kAdd || op == kSub)) {
        if (op == kAdd && variable(u) && numVal(v, m)) return x = u, c = -m, true;
        if (op == kAdd && variable(v) && numVal(u, m)) return x = v, c = -m, true;
        if (op == kSub && variable(u) && numVal(v, m)) return x = u, c = m, true;
        if (op == kSub && variable(v) && numVal(u, m)) return x = v, c = m, flip = true, true;
        return false;
    }
    if (variable(d) && !isSigSum(d) && !isSigProd(d) && !isSigNeg(d, w)) {
        x = d, c = 0;
        return true;
    }
    return false;
}

/// p is b * (x - c) in one of its writings : gives x, b and c
inline bool slopeOf(Tree p, Tree& x, double& b, double& c)
{
    tvec fs;
    Tree u, v;
    int  op;
    if (isSigProd(p, fs) && fs.size() == 2) {
        u = fs[0], v = fs[1];
    } else if (!(isSigBinOp(p, &op, u, v) && op == kMul)) {
        return false;
    }
    double k;
    bool   flip;
    if (numVal(u, k) && differenceOf(v, x, c, flip)) return b = flip ? -k : k, true;
    if (numVal(v, k) && differenceOf(u, x, c, flip)) return b = flip ? -k : k, true;
    return false;
}

/// r is a + b * (x - c) in one of the writings of the normal form, x a variable : gives
/// x (nullptr for a constant), a, b and c
inline bool affineOf(Tree r, Tree& x, double& a, double& b, double& c)
{
    tvec ts;
    Tree u, v;
    int  op;
    x = nullptr;
    if (numVal(r, a)) return b = 0, c = 0, true;
    // a plain variable : 1 * (x - 0), exact
    auto plain = [](Tree t) {
        Tree w, p, q;
        int  o;
        return variable(t) && !isSigSum(t) && !isSigProd(t) && !isSigNeg(t, w) && !isSigBinOp(t, &o, p, q);
    };
    if (isSigSum(r, ts) && ts.size() == 2) {
        u = ts[0], v = ts[1];
    } else if (!(isSigBinOp(r, &op, u, v) && op == kAdd)) {
        a = 0;
        if (plain(r)) return x = r, b = 1, c = 0, true;
        return slopeOf(r, x, b, c);
    }
    if (numVal(u, a) && plain(v)) return x = v, b = 1, c = 0, true;
    if (numVal(v, a) && plain(u)) return x = u, b = 1, c = 0, true;
    if (numVal(u, a) && slopeOf(v, x, b, c)) return true;
    if (numVal(v, a) && slopeOf(u, x, b, c)) return true;
    return false;
}

}  // namespace bpftable

/// the table of cells of sig, when it applies (see above)
inline bool bpfTableOf(Tree sig, BpfTable& tb)
{
    Tree x;
    tvec t, r;
    if (!isSigBpf(sig, x, t, r) || t.size() < 4 || r.size() != t.size() + 1) return false;
    if (gGlobal->gFloatSize != 1 && gGlobal->gFloatSize != 2) return false;
    ::Type ts = getCertifiedSigType(sig), tx = getCertifiedSigType(x);
    if (ts->nature() != kReal || tx->nature() != kReal || tx->variability() != kSamp) return false;
    const int n = int(t.size());
    std::vector<double> th(n);
    for (int i = 0; i < n; i++) {
        if (!bpftable::numVal(t[i], th[i])) return false;
        if (i > 0 && !(th[i] > th[i - 1])) return false;
    }
    tb.a.assign(n + 3, 0), tb.b.assign(n + 3, 0), tb.c.assign(n + 3, 0);
    tb.useU.assign(n + 3, 0);
    tb.u = nullptr;
    for (int i = 0; i <= n; i++) {
        Tree v;
        if (!bpftable::affineOf(r[i], v, tb.a[i], tb.b[i], tb.c[i])) return false;
        if (v == nullptr || v == x) continue;
        if (tb.u != nullptr && v != tb.u) return false;  // a third variable
        ::Type tv = getCertifiedSigType(v);
        if (tv->nature() != kReal) return false;
        tb.u       = v;
        tb.useU[i] = 1;
    }
    // the outer regions are constants (computed at xc = t1)
    if (tb.b[0] != 0 || tb.b[n] != 0) return false;
    double gap = HUGE_VAL;
    for (int i = 1; i < n; i++) gap = std::min(gap, th[i] - th[i - 1]);
    const double span = th[n - 1] - th[0];
    const double h    = gap / 2;
    const double K    = std::ceil(span / h);
    if (!(K >= 1 && K <= 4096)) return false;
    tb.n = n, tb.K = int(K), tb.t1 = th[0], tb.tn = th[n - 1], tb.invh = K / span;
    // lo[r] and hi[r] : the range [t(r), t(r+1)[ of region r, padded with the largest finite
    // value of the program (an x below tn never reaches it)
    const double big = (gGlobal->gFloatSize == 1) ? double(3.40282347e+38f) : 1.7976931348623157e+308;
    tb.lo.assign(n + 3, -big), tb.hi.assign(n + 3, big);
    for (int i = 1; i <= n; i++) tb.lo[i] = th[i - 1];
    for (int i = 0; i < n; i++) tb.hi[i] = th[i];
    tb.cell.resize(tb.K);
    for (int k = 0; k < tb.K; k++) {
        const double left = th[0] + k * (span / K);
        int          reg  = 0;
        while (reg < n && th[reg] <= left) reg++;
        tb.cell[k] = std::max(1, std::min(reg, n - 1));
    }
    return true;
}
