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

#include <map>
#include <set>
#include <unordered_map>
#include <vector>

#include "global.hh"
#include "sharing.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "xtended.hh"

/**
 * phase(x, p) = (x % p) / p divides by p ; it may multiply by 1/p instead, computed once at
 * p's rate, when p is an integer slower than the sample whose magnitude is at most 2^24 in
 * float (2^53 in double) : |x % p| <= |p| - 1 and 1/p are then exact or within half an ulp,
 * and the rounded product (|p| - 1) * fl(1/p) < 1 + u rounds to at most 1, so the value stays
 * in [-1, 1], the interval of the node.
 */
inline bool phaseByReciprocal(Tree p)
{
    Type t = getCertifiedSigType(p);
    if (t->nature() != kInt || t->variability() == kSamp) {
        return false;
    }
    if (gGlobal->gFloatSize != 1 && gGlobal->gFloatSize != 2) {
        return false;
    }
    const double   m = (gGlobal->gFloatSize == 1) ? 16777216.0 : 9007199254740992.0;
    const interval i = t->getInterval();
    return i.isValid() && ((i.lo() >= 1 && i.hi() <= m) || (i.hi() <= -1 && i.lo() >= -m));
}

/**
 * The subterms of the compound operations' definitions that the program already holds,
 * by operand : floor(x), rint(x), x + 1 and x % p. A code generator writing a definition
 * reads such a node (shared with its other uses, stored at its rate, already analysed)
 * and writes the subterm itself only when the program does not hold it. Built by a walk
 * over the annotated signals. The definition reads such a node once more : its sharing
 * count says so, and it is computed once, in a variable, whatever the compilation order.
 */
class DefinitionIndex {
    std::unordered_map<Tree, Tree> fFloor, fRint, fPlusOne;
    std::map<std::pair<Tree, Tree>, Tree> fRem;  ///< x % p (or fmod(x, p)) by (x, p)
    std::vector<Tree>              fCompounds;  ///< the compound nodes, in walk order

    void record(Tree t)
    {
        Tree  u, c, a, b;
        if (isSigFrac(t, u) || isSigCfrac(t, u) || isSigTpt(t, u) || isSigMix(t, c, a, b) ||
            isSigPhase(t, a, b)) {
            fCompounds.push_back(t);
            return;
        }
        void* ud = getUserData(t);
        if (ud != nullptr && t->arity() == 2 && ud == static_cast<void*>(gGlobal->gFmodPrim)) {
            fRem.emplace(std::make_pair(t->branch(0), t->branch(1)), t);
            return;
        }
        if (ud != nullptr && t->arity() == 1) {
            if (ud == static_cast<void*>(gGlobal->gFloorPrim)) {
                fFloor.emplace(t->branch(0), t);
            } else if (ud == static_cast<void*>(gGlobal->gRintPrim)) {
                fRint.emplace(t->branch(0), t);
            }
            return;
        }
        int  op;
        Tree x, y;
        tvec subs;
        if (isSigSum(t, subs) && subs.size() == 2) {
            // x + 1 as the normal form writes it : Sum(x, 1) or Sum(1, x)
            if (isOne(subs[1])) {
                fPlusOne.emplace(subs[0], t);
            } else if (isOne(subs[0]) && !isSigNeg(subs[1], y)) {
                fPlusOne.emplace(subs[1], t);
            }
            return;
        }
        if (isSigBinOp(t, &op, x, y)) {
            if (op == kRem) {
                fRem.emplace(std::make_pair(x, y), t);
            } else if (op == kAdd && isOne(y)) {
                fPlusOne.emplace(x, t);
            } else if (op == kAdd && isOne(x)) {
                fPlusOne.emplace(y, t);
            }
        }
    }

    static Tree find(const std::unordered_map<Tree, Tree>& m, Tree x)
    {
        auto it = m.find(x);
        return it == m.end() ? nullptr : it->second;
    }

   public:
    void build(Tree L)
    {
        fFloor.clear();
        fRint.clear();
        fPlusOne.clear();
        fRem.clear();
        fCompounds.clear();
        std::set<Tree, treeorder> seen;
        std::vector<Tree>         work{L};
        while (!work.empty()) {
            Tree t = work.back();
            work.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            record(t);
            Tree var, body;
            if (isRec(t, var, body)) {
                if (body != nullptr) {
                    work.push_back(body);
                }
                continue;
            }
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
        }
    }

    /// the subterm of t's definition that the program holds, or nullptr
    Tree held(Tree t) const
    {
        Tree x, a, b;
        if (isSigFrac(t, x)) return floorOf(x);
        if (isSigCfrac(t, x)) return rintOf(x);
        if (isSigTpt(t, x)) return plusOneOf(x);
        if (isSigPhase(t, a, b)) return remOf(a, b);
        return nullptr;
    }

    /// count the definition's read of every held subterm in the sharing analysis of key
    void countReads(Tree key) const
    {
        for (Tree t : fCompounds) {
            if (Tree h = held(t)) {
                setProperty(h, key, tree(getSharingCount(h, key) + 1));
            }
        }
    }

    Tree floorOf(Tree x) const { return find(fFloor, x); }
    Tree rintOf(Tree x) const { return find(fRint, x); }
    Tree plusOneOf(Tree x) const { return find(fPlusOne, x); }
    Tree remOf(Tree x, Tree p) const
    {
        auto it = fRem.find(std::make_pair(x, p));
        return it == fRem.end() ? nullptr : it->second;
    }
};
