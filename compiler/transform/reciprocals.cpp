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
#include <unordered_set>
#include <vector>

#include "decisionCone.hh"
#include "reciprocals.hh"
#include "rewrite.hh"
#include "sigtype.hh"
#include "typedAttributes.hh"

namespace {

/// the certified interval of d lies within [2^-100, 2^100] or its opposite : 1 / d is
/// finite and normal in every real type of the code
bool boundedAwayFromZero(Tree d)
{
    const itv::interval i = getCertifiedSigType(d)->getInterval();
    if (i.isEmpty()) {
        return false;
    }
    return (i.lo() >= 0x1p-100 && i.hi() <= 0x1p100) || (i.hi() <= -0x1p-100 && i.lo() >= -0x1p100);
}

bool isNumber(Tree t)
{
    double v;
    int    i;
    return isSigReal(t, &v) || isSigInt(t, &i);
}

}  // namespace

Tree reciprocals(Tree L, std::unordered_map<Tree, Tree>* image)
{
    const TypedAttributes exact;
    // the cone of the decisions, with the discontinuities : a value that reaches a delay
    // amount, an index, an integer conversion or a comparison keeps its rounding
    const std::unordered_set<Tree> cone = decisionCone(L, /*discontinuities*/ true);

    // a real division x / d outside the cone, d real, not a number, bounded away from 0
    auto candidate = [&](Tree t, Tree& d) -> bool {
        Tree x;
        return isSigDiv(t, x, d) && exact.nature(t) == kReal && exact.nature(d) == kReal &&
               !isNumber(d) && cone.count(t) == 0 && boundedAwayFromZero(d);
    };

    // the number of candidate divisions by each divisor
    std::unordered_map<Tree, int> divisions;
    {
        std::unordered_set<Tree> seen;
        std::vector<Tree>        work{L};
        while (!work.empty()) {
            Tree t = work.back();
            work.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree var, body;
            if (isRec(t, var, body)) {
                if (body != nullptr) {
                    work.push_back(body);
                }
                continue;
            }
            for (int i = 0; i < t->arity(); i++) {
                work.push_back(t->branch(i));
            }
            Tree d;
            if (candidate(t, d)) {
                divisions[d]++;
            }
        }
    }

    // the reciprocal is computed less often than the division : d slower than it, or d
    // shared by several divisions
    auto worthIt = [&](Tree t, Tree d) -> bool {
        return divisions[d] >= 2 || exact.variability(d) < exact.variability(t);
    };
    bool any = false;
    for (const auto& [d, n] : divisions) {
        any = any || n >= 2;
    }
    if (!any) {
        // a slower divisor ?
        std::unordered_set<Tree> seen;
        std::vector<Tree>        work{L};
        while (!work.empty() && !any) {
            Tree t = work.back();
            work.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree var, body;
            if (isRec(t, var, body)) {
                if (body != nullptr) {
                    work.push_back(body);
                }
                continue;
            }
            for (int i = 0; i < t->arity(); i++) {
                work.push_back(t->branch(i));
            }
            Tree d;
            any = candidate(t, d) && worthIt(t, d);
        }
    }
    // a rewrite rebuilds the recursions with fresh variables : none when nothing changes
    if (!any) {
        if (image != nullptr) {
            image->clear();
        }
        return L;
    }

    std::unordered_map<Tree, Tree> memo;
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        Tree d, x2, d2;
        if (!candidate(orig, d) || !worthIt(orig, d) || !isSigDiv(rebuilt, x2, d2)) {
            return rebuilt;
        }
        Tree inv = sigDiv(sigReal(1.0), d2);
        return sigProd({x2, inv});
    };
    Tree r = treeRewritePaired(L, rule, memo);
    completeTypes(r, memo);
    if (image != nullptr) {
        *image = memo;
    }
    return r;
}
