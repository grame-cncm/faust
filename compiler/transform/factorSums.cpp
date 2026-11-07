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
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "decisionCone.hh"
#include "exception.hh"
#include "factorSums.hh"
#include "global.hh"
#include "rewrite.hh"
#include "sigtype.hh"
#include "typedAttributes.hh"
#include "xtended.hh"

namespace {

bool numVal(Tree t, double& v)
{
    int i;
    if (isSigReal(t, &v)) {
        return true;
    }
    if (isSigInt(t, &i)) {
        v = i;
        return true;
    }
    return false;
}

/// t is pow(x, 2)
bool isSquare(Tree t, Tree& x)
{
    double e;
    if (sigXtendedData(t) != static_cast<void*>(gGlobal->gPowPrim) || t->arity() != 2 ||
        !numVal(t->branch(1), e) || e != 2.0) {
        return false;
    }
    x = t->branch(0);
    return true;
}

/// a factor of a monomial : its base, its power, and the tree pow(base, 2) when the term
/// held one (a power 2 without it is base * base)
struct Factor {
    Tree base;
    int  power;
    Tree square;
};

/// a term of a sum : a number times factors, the original term while it is not divided,
/// and its position in the sum
struct Mono {
    double              coef = 1;
    std::vector<Factor> factors;
    Tree                orig = nullptr;
    int                 pos  = 0;
};

class Factorer {
   public:
    explicit Factorer(Tree L) : fCone(decisionCone(L, /*discontinuities*/ false))
    {
        // the reads of every signal, one per branch that holds it
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
                    fReads[body]++;
                    work.push_back(body);
                }
                continue;
            }
            for (int i = 0; i < t->arity(); i++) {
                fReads[t->branch(i)]++;
                work.push_back(t->branch(i));
            }
        }
    }

    Tree rule(Tree orig, Tree rebuilt, std::unordered_map<Tree, Tree>& memo);

   private:
    TypedAttributes               fExact;
    std::unordered_set<Tree>      fCone;   ///< the cone of the memory decisions : no sum there
    std::unordered_map<Tree, int> fReads;  ///< the reads of every signal

    bool shared(Tree t) const
    {
        auto it = fReads.find(t);
        return it != fReads.end() && it->second > 1;
    }

    bool parse(Tree t, Mono& m, bool inner) const;
    void add(Mono& m, Tree base, int power, Tree square) const;
    Tree build(const Mono& m, std::unordered_map<Tree, Tree>& memo) const;
    void factor(std::vector<Mono> terms, std::vector<std::pair<int, Tree>>& out,
                std::unordered_map<Tree, Tree>& memo, bool& changed) const;
};

void Factorer::add(Mono& m, Tree base, int power, Tree square) const
{
    for (auto& f : m.factors) {
        if (f.base == base) {
            f.power += power;
            f.square = nullptr;
            return;
        }
    }
    m.factors.push_back({base, power, square});
}

// a monomial : neg(x), a number, a product (n-ary, binary, or the gain kernel FIR[x, k]) of
// real factors, pow(x, 2), or another real signal, a factor of its own. A product that
// holds an integer factor is no monomial : its integer operations stay as certified. A
// product or a square read elsewhere (inner, below the term) is one factor : it is
// computed once for all its readers, and dividing it would compute its factors again.
bool Factorer::parse(Tree t, Mono& m, bool inner) const
{
    Tree   x, a, b;
    tvec   fs;
    double c;
    if (inner && shared(t) && !numVal(t, c)) {
        if (fExact.nature(t) != kReal) return false;
        add(m, t, 1, nullptr);
        return true;
    }
    if (isSigNeg(t, x)) {
        m.coef = -m.coef;
        return parse(x, m, true);
    }
    if (numVal(t, c)) {
        m.coef *= c;
        return true;
    }
    if (fExact.nature(t) != kReal) {
        return false;
    }
    if (isSigProd(t, fs)) {
        for (Tree f : fs) {
            if (!parse(f, m, true)) return false;
        }
        return true;
    }
    if (isSigMul(t, a, b)) {
        return parse(a, m, true) && parse(b, m, true);
    }
    if (isSigFIR(t, fs) && fs.size() == 2 && numVal(fs[1], c)) {
        m.coef *= c;
        return parse(fs[0], m, true);
    }
    if (isSquare(t, x) && fExact.nature(x) == kReal) {
        add(m, x, 2, t);
        return true;
    }
    add(m, t, 1, nullptr);
    return true;
}

Tree Factorer::build(const Mono& m, std::unordered_map<Tree, Tree>& memo) const
{
    if (m.orig != nullptr) {
        return memo.at(m.orig);
    }
    tvec         fs;
    const double mag = std::fabs(m.coef);
    if (mag != 1.0 || m.factors.empty()) {
        fs.push_back(sigReal(mag));
    }
    for (const auto& f : m.factors) {
        if (f.power == 2 && f.square != nullptr) {
            fs.push_back(memo.at(f.square));
        } else {
            for (int k = 0; k < f.power; k++) {
                fs.push_back(memo.at(f.base));
            }
        }
    }
    Tree core = (fs.size() == 1) ? fs[0] : sigProd(fs);
    return (m.coef < 0) ? sigNeg(core) : core;
}

// the greedy factoring of a list of monomials : the trees of the terms, with the position
// of their first term in the sum
void Factorer::factor(std::vector<Mono> terms, std::vector<std::pair<int, Tree>>& out,
                      std::unordered_map<Tree, Tree>& memo, bool& changed) const
{
    // the factors at the sample rate, in the order they are met : the terms that hold
    // them, and the terms that are the factor alone (they save no product)
    std::vector<Tree>                            order;
    std::unordered_map<Tree, std::pair<int, int>> stat;
    for (const auto& m : terms) {
        for (const auto& f : m.factors) {
            if (fExact.variability(f.base) != kSamp) {
                continue;
            }
            auto it = stat.find(f.base);
            if (it == stat.end()) {
                order.push_back(f.base);
                it = stat.emplace(f.base, std::make_pair(0, 0)).first;
            }
            it->second.first++;
            if (m.factors.size() == 1 && f.power == 1 && std::fabs(m.coef) == 1.0) {
                it->second.second++;
            }
        }
    }
    Tree best  = nullptr;
    int  saved = 0;
    for (Tree f : order) {
        const int s = stat[f].first - stat[f].second - 1;
        if (s > saved) {
            best  = f;
            saved = s;
        }
    }
    if (best == nullptr) {
        for (const auto& m : terms) {
            out.push_back({m.pos, build(m, memo)});
        }
        return;
    }
    changed = true;
    std::vector<Mono> inner, rest;
    int               pos = INT32_MAX;
    for (auto& m : terms) {
        auto it = std::find_if(m.factors.begin(), m.factors.end(),
                               [&](const Factor& f) { return f.base == best; });
        if (it == m.factors.end()) {
            rest.push_back(m);
            continue;
        }
        pos = std::min(pos, m.pos);
        if (--it->power == 0) {
            m.factors.erase(it);
        } else {
            it->square = nullptr;
        }
        m.orig = nullptr;
        inner.push_back(m);
    }
    // an inner sum whose terms are all negated is read negated : no negation in it
    bool negated = true;
    for (const auto& m : inner) {
        negated = negated && m.coef < 0;
    }
    if (negated) {
        for (auto& m : inner) {
            m.coef = -m.coef;
        }
    }
    std::vector<std::pair<int, Tree>> in;
    factor(inner, in, memo, changed);
    std::stable_sort(in.begin(), in.end(),
                     [](const std::pair<int, Tree>& x, const std::pair<int, Tree>& y) { return x.first < y.first; });
    tvec ts;
    for (auto& [p, t] : in) {
        ts.push_back(t);
    }
    Tree sum  = (ts.size() == 1) ? ts[0] : sigSum(ts);
    Tree base = memo.at(best);
    Tree prod = sigProd({base, sum});
    out.push_back({pos, negated ? sigNeg(prod) : prod});
    factor(rest, out, memo, changed);
}

Tree Factorer::rule(Tree orig, Tree rebuilt, std::unordered_map<Tree, Tree>& memo)
{
    tvec subs;
    if (!isSigSum(orig, subs) || fExact.nature(orig) != kReal || fExact.variability(orig) != kSamp ||
        fCone.count(orig) != 0) {
        return rebuilt;
    }
    // the monomials ; a term that is none, or that another signal reads too (computed
    // once for all its readers), stays as it is
    std::vector<Mono> terms;
    int               products = 0;
    for (size_t i = 0; i < subs.size(); i++) {
        Mono m;
        if (shared(subs[i]) || !parse(subs[i], m, false)) {
            m = Mono();
        }
        m.orig = subs[i];
        m.pos  = int(i);
        int degree = 0;
        for (const auto& f : m.factors) {
            degree += f.power;
        }
        products += (degree >= 2) ? 1 : 0;
        terms.push_back(m);
    }
    if (products < 2) {
        return rebuilt;
    }
    bool                              changed = false;
    std::vector<std::pair<int, Tree>> out;
    factor(terms, out, memo, changed);
    if (!changed) {
        return rebuilt;
    }
    std::stable_sort(out.begin(), out.end(),
                     [](const std::pair<int, Tree>& x, const std::pair<int, Tree>& y) { return x.first < y.first; });
    tvec ts;
    for (auto& [p, t] : out) {
        ts.push_back(t);
    }
    return (ts.size() == 1) ? ts[0] : sigSum(ts);
}

}  // namespace

Tree factorSums(Tree L, std::unordered_map<Tree, Tree>* image)
{
    Factorer                       f(L);
    std::unordered_map<Tree, Tree> memo;
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree { return f.rule(orig, rebuilt, memo); };
    Tree L1   = treeRewritePaired(L, rule, memo);
    completeTypes(L1, memo);
    if (image != nullptr) {
        *image = memo;
    }
    return L1;
}
