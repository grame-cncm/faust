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

#include <unordered_map>
#include <vector>
#include "rewrite.hh"
#include "sigattributes.hh"
#include "sigtype.hh"
#include "sumLanes.hh"

namespace {

const int kLanes = 4;  ///< the partial sums : the floats of a 128-bit vector

/// the parts added pairwise, level by level : ((p0 + p1) + (p2 + p3))
Tree balancedSum(tvec parts)
{
    while (parts.size() > 1) {
        tvec next;
        for (size_t k = 0; k + 1 < parts.size(); k += 2) {
            Tree s = sigSum({parts[k], parts[k + 1]});
            next.push_back(s);
        }
        if (parts.size() % 2) {
            next.push_back(parts.back());
        }
        parts = next;
    }
    return parts[0];
}

}  // namespace

Tree sumLanes(Tree L)
{
    const ExactSolvers             exact(L);
    std::unordered_map<Tree, Tree> memo;
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        tvec ot, rt;
        if (!isSigSum(orig, ot) || !isSigSum(rebuilt, rt) || ot.size() != rt.size() ||
            exact.nature(orig) != kReal) {
            return rebuilt;
        }
        // the slower terms first, then only sample-rate terms (the order of the normal form)
        size_t s = 0;
        while (s < ot.size() && exact.variability(ot[s]) < kSamp) {
            s++;
        }
        for (size_t k = s; k < ot.size(); k++) {
            if (exact.variability(ot[k]) < kSamp) {
                return rebuilt;
            }
        }
        if (ot.size() - s < size_t(2 * kLanes)) {
            return rebuilt;
        }
        tvec parts;
        for (size_t j = 0; j < size_t(kLanes); j++) {
            tvec lane;
            for (size_t k = s + j; k < rt.size(); k += kLanes) {
                lane.push_back(rt[k]);
            }
            Tree p = sigSum(lane);
            parts.push_back(p);
        }
        Tree fast = balancedSum(parts);
        if (s == 0) {
            return fast;
        }
        tvec outer(rt.begin(), rt.begin() + s);
        outer.push_back(fast);
        return sigSum(outer);
    };
    return treeRewritePaired(L, rule, memo);
}
