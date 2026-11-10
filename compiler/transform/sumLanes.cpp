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

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "rewrite.hh"
#include "decisionCone.hh"
#include "exception.hh"
#include "typedAttributes.hh"
#include "sigtype.hh"
#include "sumLanes.hh"

namespace {

const int kLanes = 4;  ///< the partial sums : the floats of a 128-bit vector

/// whether a term is subtracted by the sum that reads it (emitSum) : a negation or a
/// negative number
bool isSubtracted(Tree t)
{
    double v;
    int    i;
    Tree   x;
    return isSigNeg(t, x) || (isSigReal(t, &v) && v < 0) || (isSigInt(t, &i) && i < 0);
}

/// the opposite of a term : a number negated, neg(x) is x, x is neg(x), the same value
/// negated bit for bit
Tree opposite(Tree t)
{
    double v;
    int    i;
    Tree   x;
    if (isSigReal(t, &v)) {
        return sigReal(-v);
    }
    if (isSigInt(t, &i)) {
        return sigInt(-i);
    }
    if (isSigNeg(t, x)) {
        return x;
    }
    return sigNeg(t);
}

/// a part of the balanced tree, with its sign : the value is sign * sum
struct Part {
    int  sign;
    Tree sum;
};

/// the sum of a lane : a lane whose terms are all subtracted is the opposite of the sum of
/// their opposites, so that no negation is computed (emitSum subtracts a negated term ; a
/// sum of negated terms only would be computed as a negation)
Part lanePart(const tvec& lane)
{
    bool all = !lane.empty();
    for (Tree t : lane) {
        all = all && isSubtracted(t);
    }
    if (!all) {
        return {1, sigSum(lane)};
    }
    tvec op;
    for (Tree t : lane) {
        op.push_back(opposite(t));
    }
    return {-1, sigSum(op)};
}

/// the parts added pairwise, level by level : ((p0 + p1) + (p2 + p3)), a negative part
/// subtracted : a - b, the same value bit for bit as a + (-b) or -(b - a)
Part balancedSum(std::vector<Part> parts)
{
    while (parts.size() > 1) {
        std::vector<Part> next;
        for (size_t k = 0; k + 1 < parts.size(); k += 2) {
            const Part& a = parts[k];
            const Part& b = parts[k + 1];
            if (a.sign > 0 && b.sign > 0) {
                next.push_back({1, sigSum({a.sum, b.sum})});
            } else if (a.sign > 0) {
                next.push_back({1, sigSum({a.sum, sigNeg(b.sum)})});
            } else if (b.sign > 0) {
                next.push_back({1, sigSum({b.sum, sigNeg(a.sum)})});
            } else {
                next.push_back({-1, sigSum({a.sum, b.sum})});
            }
        }
        if (parts.size() % 2) {
            next.push_back(parts.back());
        }
        parts = next;
    }
    return parts[0];
}

/// the sample-rate terms rt[s..] in 4 partial sums added as a balanced tree, after the
/// slower terms rt[0..s) : interleaved, Sum(t0, t4, ...), Sum(t1, t5, ...), ..., or
/// contiguous, Sum(t0, ..., t(k-1)), Sum(tk, ...), ...
Tree laneSum(const tvec& rt, size_t s, LaneOrder order)
{
    std::vector<Part> parts;
    const size_t      n = rt.size() - s;
    for (size_t j = 0; j < size_t(kLanes); j++) {
        tvec lane;
        if (order == LaneOrder::kInterleaved) {
            for (size_t k = s + j; k < rt.size(); k += kLanes) {
                lane.push_back(rt[k]);
            }
        } else {
            // lane j : the terms n * j / 4 to n * (j + 1) / 4, at least 2 of them
            for (size_t k = s + n * j / kLanes; k < s + n * (j + 1) / kLanes; k++) {
                lane.push_back(rt[k]);
            }
        }
        parts.push_back(lanePart(lane));
    }
    Part fast = balancedSum(parts);
    Tree f    = (fast.sign > 0) ? fast.sum : sigNeg(fast.sum);
    if (s == 0) {
        return f;
    }
    tvec outer(rt.begin(), rt.begin() + s);
    outer.push_back(f);
    return sigSum(outer);
}

/// the depth in additions of n sample-rate terms in 4 partial sums : each lane a chain,
/// then two levels
int laneDepth(size_t n)
{
    return int((n + kLanes - 1) / kLanes) - 1 + 2;
}

/// the number of reads of every signal, one per branch that holds it ; nodes receives the
/// signals in the order of a depth-first walk
std::unordered_map<Tree, int> readCounts(Tree L, std::vector<Tree>& nodes)
{
    std::unordered_map<Tree, int> reads;
    std::unordered_set<Tree>      seen;
    std::vector<Tree>             work{L};
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) {
            continue;
        }
        nodes.push_back(t);
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body != nullptr) {
                reads[body]++;
                work.push_back(body);
            }
            continue;
        }
        for (int i = 0; i < t->arity(); i++) {
            reads[t->branch(i)]++;
            work.push_back(t->branch(i));
        }
    }
    return reads;
}

/// the gathering of the sums (step 3f.1) : which nested sums a sum takes in, decided on the
/// program before the rewrite
struct Gathering {
    const TypedAttributes&               exact;
    const std::unordered_set<Tree>&      cone;
    const std::unordered_map<Tree, int>& reads;
    std::unordered_set<Tree>             absorbed;  ///< spliced into the sum that reads them
    std::unordered_set<Tree>             roots;     ///< a sum that takes in nested sums
    std::unordered_map<Tree, size_t>     count;     ///< the sample-rate terms, gathered
    std::unordered_map<Tree, int>        depth;     ///< the depth in additions, as it is

    Gathering(const TypedAttributes& e, const std::unordered_set<Tree>& c,
              const std::unordered_map<Tree, int>& r)
        : exact(e), cone(c), reads(r)
    {
    }

    int readsOf(Tree t) const
    {
        auto it = reads.find(t);
        return (it == reads.end()) ? 0 : it->second;
    }

    /// a real sum outside the cone : its association may change
    bool open(Tree t) const
    {
        return isSigSum(t) && exact.nature(t) == kReal && cone.count(t) == 0;
    }

    /// the nested sum of a term u of an open sum, or nullptr : u, or u = neg(x), is a real
    /// sum at the sample rate, outside the cone, that the sum alone reads
    Tree nested(Tree u, bool& negated) const
    {
        Tree x;
        negated = isSigNeg(u, x) && readsOf(u) == 1;
        Tree t  = negated ? x : u;
        if (open(t) && exact.variability(t) == kSamp && readsOf(t) == 1) {
            return t;
        }
        negated = false;
        return nullptr;
    }

    /// the sample-rate terms of the sum S, its nested sums gathered
    size_t gatheredCount(Tree S)
    {
        auto it = count.find(S);
        if (it != count.end()) {
            return it->second;
        }
        tvec ts;
        isSigSum(S, ts);
        size_t n = 0;
        for (Tree u : ts) {
            bool neg;
            if (Tree t = nested(u, neg)) {
                n += gatheredCount(t);
            } else if (exact.variability(u) == kSamp) {
                n++;
            }
        }
        count[S] = n;
        return n;
    }

    /// the depth in additions of the sum S as the code computes it without the gathering :
    /// the chain of its sample-rate terms, a nested sum computed before it is added, or 4
    /// partial sums when it has at least 8 sample-rate terms, its slower terms first ; the
    /// slower terms are computed at their rate, a sum read elsewhere once, both ready
    int depthAsIs(Tree S)
    {
        auto it = depth.find(S);
        if (it != depth.end()) {
            return it->second;
        }
        tvec ts;
        isSigSum(S, ts);
        int    acc = -1, deepest = 0;
        size_t n = 0, s = 0;
        bool   slowFirst = true;
        for (Tree u : ts) {
            if (exact.variability(u) < kSamp) {
                slowFirst = slowFirst && n == 0;
                s++;
                continue;
            }
            n++;
            bool neg;
            Tree t = nested(u, neg);
            int  d = (t != nullptr) ? depthAsIs(t) : 0;
            deepest = std::max(deepest, d);
            acc     = (acc < 0) ? d : std::max(acc, d) + 1;
        }
        int r = std::max(acc, 0);
        if (slowFirst && n >= size_t(2 * kLanes)) {
            r = std::max(laneDepth(n), deepest + 3);
        }
        depth[S] = r;
        return r;
    }

    /// the sum R, read as a whole : it takes in its nested sums when the gathered sum has
    /// at least 8 sample-rate terms and its partial sums are less deep than the sum as it
    /// is ; otherwise each nested sum decides for itself (a staircase of nested sums,
    /// computed one after the other, is gathered ; a balanced tree of nested sums, or a
    /// short chain beside a nested sum, is not)
    void decide(Tree R)
    {
        tvec ts;
        isSigSum(R, ts);
        bool hasNested = false;
        for (Tree u : ts) {
            bool neg;
            hasNested = hasNested || nested(u, neg) != nullptr;
        }
        const size_t n = hasNested ? gatheredCount(R) : 0;
        if (hasNested && n >= size_t(2 * kLanes) && laneDepth(n) < depthAsIs(R)) {
            roots.insert(R);
            absorb(R);
            return;
        }
        for (Tree u : ts) {
            bool neg;
            if (Tree t = nested(u, neg)) {
                decide(t);
            }
        }
    }

    void absorb(Tree S)
    {
        tvec ts;
        isSigSum(S, ts);
        for (Tree u : ts) {
            bool neg;
            if (Tree t = nested(u, neg)) {
                absorbed.insert(t);
                absorb(t);
            }
        }
    }
};

}  // namespace

Tree sumLanes(Tree L, LaneOrder order, std::unordered_map<Tree, Tree>* image)
{
    const TypedAttributes                exact;
    const std::unordered_set<Tree>       cone  = decisionCone(L, /*discontinuities*/ false);
    std::vector<Tree>                    nodes;
    const std::unordered_map<Tree, int>  reads = readCounts(L, nodes);
    Gathering                            G(exact, cone, reads);
    {
        // the open sums that no open sum takes in are read as a whole
        std::unordered_set<Tree> inner;
        std::vector<Tree>        sums;
        for (Tree t : nodes) {
            if (G.open(t)) {
                sums.push_back(t);
                tvec ts;
                isSigSum(t, ts);
                for (Tree u : ts) {
                    bool neg;
                    if (Tree x = G.nested(u, neg)) {
                        inner.insert(x);
                    }
                }
            }
        }
        for (Tree t : sums) {
            if (inner.count(t) == 0) {
                G.decide(t);
            }
        }
    }
    // a gathered sum -> its terms with their rates
    std::unordered_map<Tree, std::vector<std::pair<Tree, int>>> gathered;
    std::unordered_map<Tree, Tree>                              memo;
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        tvec ot, rt;
        if (!isSigSum(orig, ot) || !isSigSum(rebuilt, rt) || ot.size() != rt.size() ||
            exact.nature(orig) != kReal || cone.count(orig) != 0) {
            return rebuilt;
        }
        if (G.absorbed.count(orig) || G.roots.count(orig)) {
            // the terms, each nested sum replaced by its terms, at its place
            std::vector<std::pair<Tree, int>> terms;
            for (size_t k = 0; k < ot.size(); k++) {
                Tree x, rx;
                bool neg = isSigNeg(ot[k], x) && G.absorbed.count(x);
                if (neg || G.absorbed.count(ot[k])) {
                    Tree r = rt[k];
                    if (neg) {
                        faustassert(isSigNeg(rt[k], rx));
                        r = rx;
                    }
                    auto it = gathered.find(r);
                    faustassert(it != gathered.end());
                    for (const auto& [t, v] : it->second) {
                        terms.push_back({neg ? opposite(t) : t, v});
                    }
                } else {
                    terms.push_back({rt[k], exact.variability(ot[k])});
                }
            }
            if (G.absorbed.count(orig)) {
                tvec ts;
                for (const auto& tv : terms) {
                    ts.push_back(tv.first);
                }
                Tree g = sigSum(ts);
                gathered[g] = terms;
                return g;
            }
            // the root : the numbers added into one, first, then the slower terms by rate
            // (the order of the normal form), then the sample-rate terms in partial sums
            double sum = 0;
            int    nums = 0;
            std::vector<std::pair<Tree, int>> rest;
            for (const auto& tv : terms) {
                double v;
                if (isSigReal(tv.first, &v)) {
                    sum += v;
                    nums++;
                } else {
                    rest.push_back(tv);
                }
            }
            std::stable_sort(rest.begin(), rest.end(),
                             [](const auto& a, const auto& b) { return a.second < b.second; });
            tvec ts;
            if (nums > 0 && sum != 0) {
                ts.push_back(sigReal(sum));
            }
            size_t s = ts.size();
            for (const auto& tv : rest) {
                ts.push_back(tv.first);
                if (tv.second < kSamp) {
                    s++;
                }
            }
            faustassert(ts.size() - s >= size_t(2 * kLanes));
            return laneSum(ts, s, order);
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
        return laneSum(rt, s, order);
    };
    Tree r = treeRewritePaired(L, rule, memo);
    completeTypes(r, memo);
    if (image != nullptr) {
        *image = memo;
    }
    return r;
}
