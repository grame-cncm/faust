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

#include "orderSums.hh"

#include <cmath>
#include <limits>
#include <optional>
#include <unordered_map>
#include <vector>

#include "rewrite.hh"
#include "sigs-state.hh"
#include "sigtyperules.hh"

// The order of the terms of a Sum is its association (((t0 + t1) + ...) + tn) : the
// rounding error of the chain grows with the magnitude of its partial sums. Within a class
// of rate (constants, controls, audio, terms reading the state of a recursion : the prefix
// that the generator computes at its own rate is kept), the terms are taken greedily :
// first the pair whose sum has the smallest interval (two large terms that cancel), then
// each time the term that keeps the partial sum the smallest (same-sign terms by increasing
// magnitude). Ties keep the order of the normal form. A class holding an unbounded or
// invalid term is left as it is.

namespace {

struct Range {
    double lo, hi;
};

double magnitude(const Range& r)
{
    return std::max(std::abs(r.lo), std::abs(r.hi));
}

Range add(const Range& a, const Range& b)
{
    return {a.lo + b.lo, a.hi + b.hi};
}

// the rate class of a term : 0 constant, 1 control, 2 audio, 3 reads a recursive state
int rateClass(Tree t)
{
    if (sigs::sigOrder(t) >= 4) {
        return 3;
    }
    int v = getCertifiedSigType(t)->variability();
    return v == kKonst ? 0 : (v == kBlock ? 1 : 2);
}

// the greedy order of the terms idx (indices in rs), after a partial sum s (if any)
std::vector<int> greedy(const std::vector<Range>& rs, std::vector<int> idx, std::optional<Range> s)
{
    std::vector<int> out;
    if (!s && idx.size() >= 2) {
        // the first pair : the smallest sum
        size_t bi = 0, bj = 1;
        double best = std::numeric_limits<double>::infinity();
        for (size_t i = 0; i < idx.size(); i++) {
            for (size_t j = i + 1; j < idx.size(); j++) {
                double m = magnitude(add(rs[idx[i]], rs[idx[j]]));
                if (m < best) {
                    best = m;
                    bi   = i;
                    bj   = j;
                }
            }
        }
        out.push_back(idx[bi]);
        out.push_back(idx[bj]);
        s = add(rs[idx[bi]], rs[idx[bj]]);
        idx.erase(idx.begin() + long(bj));
        idx.erase(idx.begin() + long(bi));
    }
    while (!idx.empty()) {
        size_t bk   = 0;
        double best = std::numeric_limits<double>::infinity();
        for (size_t k = 0; k < idx.size(); k++) {
            double m = s ? magnitude(add(*s, rs[idx[k]])) : magnitude(rs[idx[k]]);
            if (m < best) {
                best = m;
                bk   = k;
            }
        }
        out.push_back(idx[bk]);
        s = s ? add(*s, rs[idx[bk]]) : rs[idx[bk]];
        idx.erase(idx.begin() + long(bk));
    }
    return out;
}

}  // namespace

Tree orderSumsByIntervals(Tree L)
{
    std::unordered_map<Tree, Tree> memo;
    auto pre     = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    auto rule    = [](Tree orig, Tree rebuilt) -> Tree {
        tvec ot, rt;
        if (!isSigSum(orig, ot) || !isSigSum(rebuilt, rt) || ot.size() < 3 || ot.size() != rt.size()) {
            return rebuilt;
        }
        std::vector<Range> rs(ot.size());
        std::vector<int>   cls(ot.size());
        for (size_t i = 0; i < ot.size(); i++) {
            interval itv = getCertifiedSigType(ot[i])->getInterval();
            rs[i]        = {itv.lo(), itv.hi()};
            if (itv.isEmpty() || !itv.isValid() || !std::isfinite(itv.lo()) || !std::isfinite(itv.hi())) {
                rs[i] = {-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()};
            }
            cls[i] = rateClass(ot[i]);
        }
        // the classes in the order of the normal form, each one reordered
        std::vector<int>     order;
        std::optional<Range> s;
        for (int c = 0; c <= 3; c++) {
            std::vector<int> idx;
            bool             bounded = true;
            for (size_t i = 0; i < ot.size(); i++) {
                if (cls[i] == c) {
                    idx.push_back(int(i));
                    bounded = bounded && std::isfinite(rs[i].lo) && std::isfinite(rs[i].hi);
                }
            }
            if (idx.empty()) {
                continue;
            }
            std::vector<int> part = bounded ? greedy(rs, idx, s) : idx;
            for (int i : part) {
                order.push_back(i);
                s = s ? add(*s, rs[i]) : rs[i];
            }
        }
        // a class not contiguous in the normal form keeps the normal form
        tvec out;
        for (int i : order) out.push_back(rt[i]);
        if (out == rt) {
            return rebuilt;
        }
        return sigSum(out);
    };
    return treeRewritePairedMemo(L, pre, rule, memo, defRule);
}
