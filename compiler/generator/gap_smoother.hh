/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#ifndef _GAP_SMOOTHER_
#define _GAP_SMOOTHER_

#include "signals.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

/**
 * The smoother of a slow target : the member proj of a recursive group defined as
 * mix(c, proj', T), real, c and T slower than the sample, c in ]0, 1].
 *
 * Computed as y' + c * (T - y'), it stops where c * (T - y') rounds to nothing : in single
 * precision a delay of 48000 samples smoothed by si.smoo stays at 47997.875. The code
 * generators compute it as its gap to the target, e = T - y :
 *
 *     e = (1 - c) * (e' + (T - T')),   y = T - e
 *
 * The gap decays to zero, and y reaches T exactly. The gap and the previous target are two
 * states, both 0 at start, as y and T before the first sample.
 */
inline bool isGapSmoother(Tree proj, Tree def, Tree& c, Tree& target)
{
    Tree a, x, d;
    int  k;
    if (!isSigMix(def, c, a, target)) {
        return false;
    }
    if (!(isSigDelay1(a, x) || (isSigDelay(a, x, d) && isSigInt(d, &k) && k == 1)) || x != proj) {
        return false;
    }
    ::Type tp = getSigType(proj), tc = getSigType(c), tt = getSigType(target);
    if (!tp || !tc || !tt || tp->nature() != kReal || tc->variability() == kSamp ||
        tt->variability() == kSamp) {
        return false;
    }
    const auto ic = tc->getInterval();
    return ic.isValid() && ic.lo() > 0 && ic.hi() <= 1;
}

/**
 * IRM(x; p), the smoother y = mix(p, x, y'), p its pole : the weight of x, 1 - p, when the
 * normal form wrote the pole as the complement Sum(1, neg(w)) (the state of a TPT filter,
 * p = 1 - 2g) : w, read as it is, exact ; nullptr otherwise.
 */
inline Tree irmInputWeight(Tree p)
{
    Tree w;
    tvec ws;
    if (isSigSum(p, ws) && ws.size() == 2 && isOne(ws[0]) && isSigNeg(ws[1], w)) {
        return w;
    }
    return nullptr;
}

/**
 * IRM(x; p) computed as its gap to x (see above) : real, x and p slower than the sample,
 * p in [0, 1[ (the weight of x in ]0, 1]).
 */
inline bool isGapIRM(Tree sig, Tree x, Tree p)
{
    ::Type ts = getSigType(sig), tp = getSigType(p), tx = getSigType(x);
    if (!ts || !tp || !tx || ts->nature() != kReal || tp->variability() == kSamp || tx->variability() == kSamp) {
        return false;
    }
    const auto ip = tp->getInterval();
    return ip.isValid() && ip.lo() >= 0 && ip.hi() < 1;
}

#endif
