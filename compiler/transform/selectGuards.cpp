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

#include <set>
#include <utility>
#include <vector>

#include "selectGuards.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

namespace {

/// the reading of a signal : under a guard, or at each sample (free) ; unset before its first
/// reader is seen
enum class Mark { kUnset, kGuarded, kFree };

struct Reading {
    Mark        mark = Mark::kUnset;
    SelectGuard guard;
};

/// an operation computing a value from the values of its operands, read when it is read
bool readsWhenRead(Tree t)
{
    Tree a, b, c;
    int  op;
    return isSigBinOp(t, &op, a, b) || isSigIntCast(t, a) || isSigFloatCast(t, a) || isSigBitCast(t) ||
           isSigSelect2(t, a, b, c) || sigXtendedData(t) != nullptr || isSigSum(t) || isSigProd(t) ||
           isSigNeg(t, a) || isSigMix(t, a, b, c) || isSigFrac(t, a) || isSigCfrac(t, a);
}

/// a selector computed once per block
bool isSlow(Tree s)
{
    return getCertifiedSigType(s)->variability() <= kBlock;
}

/// the reading r merged with a reader ; true when r changes
bool merge(Reading& r, const Reading& by)
{
    if (r.mark == Mark::kFree) {
        return false;
    }
    if (by.mark == Mark::kFree) {
        r.mark = Mark::kFree;
        return true;
    }
    if (r.mark == Mark::kUnset) {
        r = by;
        return true;
    }
    if (r.guard.selector == by.guard.selector && r.guard.second == by.guard.second) {
        return false;
    }
    r.mark = Mark::kFree;
    return true;
}

}  // namespace

std::unordered_map<Tree, SelectGuard> selectGuards(Tree L)
{
    std::unordered_map<Tree, Reading>     readings;
    std::vector<std::pair<Tree, Reading>> work;
    const Reading                         free{Mark::kFree, {}};
    for (Tree l = L; isList(l); l = tl(l)) {
        work.push_back({hd(l), free});
    }
    // each signal changes at most twice (unset, guarded, free) : its operands are visited
    // at most twice
    while (!work.empty()) {
        auto [t, by] = work.back();
        work.pop_back();
        Reading& r = readings[t];
        if (!merge(r, by)) {
            continue;
        }
        const Reading rt = r;
        if (isSigGen(t)) {
            continue;
        }
        Tree s, x, y;
        if (isSigSelect2(t, s, x, y) && isSlow(s)) {
            work.push_back({s, rt});
            work.push_back({x, Reading{Mark::kGuarded, {s, false}}});
            work.push_back({y, Reading{Mark::kGuarded, {s, true}}});
            continue;
        }
        const Reading operands = readsWhenRead(t) ? rt : free;
        tvec          subs;
        getSubSignals(t, subs);
        for (Tree u : subs) {
            work.push_back({u, operands});
        }
    }
    std::unordered_map<Tree, SelectGuard> guards;
    for (const auto& [t, r] : readings) {
        if (r.mark == Mark::kGuarded) {
            guards[t] = r.guard;
        }
    }
    return guards;
}

bool isCostlyMathFunction(const std::string& name)
{
    static const std::set<std::string> costly = {
        "exp",   "exp2",  "exp10", "expm1", "log",   "log2",  "log10", "log1p", "pow",
        "sin",   "cos",   "tan",   "asin",  "acos",  "atan",  "atan2", "sinh",  "cosh",
        "tanh",  "asinh", "acosh", "atanh", "sqrt",  "cbrt",  "hypot", "fmod",  "remainder",
        "erf",   "erfc",  "lgamma", "tgamma"};
    std::string f = (name.rfind("std::", 0) == 0) ? name.substr(5) : name;
    if (costly.count(f)) {
        return true;
    }
    return f.size() > 1 && (f.back() == 'f' || f.back() == 'l') && costly.count(f.substr(0, f.size() - 1));
}
