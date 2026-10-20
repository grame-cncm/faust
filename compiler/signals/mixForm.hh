/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

#pragma once

#include "interval_algebra.hh"
#include "signals.hh"

/**
 * The form of mix(c, a, b) = (1 - c) a + c b that the code computes, shared by the code
 * generators and by the interval of the node, which bounds that same computation.
 *
 * The weight c is often written 1 - t by the normal form. Computing c, then 1 - c, rounds t
 * away when t is small (1 - 1e-8 is 1 in single precision) : the result, near b, loses its
 * digits. When c is 1 - t, the mix is computed b + t (a - b), from t itself, whenever the
 * interpolation from b is the one chosen (c may be near 1, itv::mixFromB) or when nothing
 * bounds c (a foreign function, say), the interval of the node being then unbounded anyway.
 */

/// c is 1 - t : the binary 1 - t, or the Sum(1, neg(t)) of the normal form
inline bool mixComplementOf(Tree c, Tree& t)
{
    auto isOneConst = [](Tree x) {
        double r;
        int    i;
        return (isSigReal(x, &r) && r == 1.0) || (isSigInt(x, &i) && i == 1);
    };
    int  op;
    Tree a, b;
    tvec subs;
    if (isSigBinOp(c, &op, a, b) && op == kSub && isOneConst(a)) {
        t = b;
        return true;
    }
    return isSigSum(c, subs) && subs.size() == 2 && isOneConst(subs[0]) && isSigNeg(subs[1], t);
}

/// mix(c, a, b) is computed b + t (a - b), c being 1 - t, ic the interval of c
inline bool mixFromWeight(Tree c, const itv::interval& ic, Tree& t)
{
    if (!mixComplementOf(c, t)) return false;
    return itv::mixFromB(ic) || ic.isEmpty() || !ic.isBounded();
}
