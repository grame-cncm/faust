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
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "computeSignals.hh"
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

/// two gammas c0 / c1 of affine factors the program cannot tell apart, lo <= hi : computed
/// from coefficients rounded along different paths (1/3 rounded to a float), they differ by
/// an ulp or two ; in single precision, within 2^-21 (4 ulps of a float), in double within
/// 2^-46
bool sameGamma(double hi, double lo)
{
    return hi - lo <= std::ldexp(1.0, (gGlobal->gFloatSize == 1) ? -21 : -46) * hi;
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
/// held one (a power 2 without it is base * base). An affine factor c0 + c1 * t is t + gamma,
/// gamma = c0 / c1 (c1 joins the number of the monomial) : its base is set once the gammas
/// of the sum are clustered, the original t when gamma is 0, else a new tree (fresh)
struct Factor {
    Tree   base;
    int    power;
    Tree   square;
    Tree   atom  = nullptr;  ///< an affine factor : t
    double gamma = 0;
    double scale = 1;        ///< an affine factor : c1, joining the number once normalized
    Tree   src   = nullptr;  ///< an affine factor : its node, nullptr for the weight of a mix
    bool   fresh = false;
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

    // while the terms of a sum are parsed : the nodes below the terms that other signals
    // read too (kept whole), and the reads of each node by the terms of the sum
    mutable std::unordered_set<Tree>      fOpaque;
    mutable std::unordered_map<Tree, int> fCounts;

    bool parse(Tree t, Mono& m, bool inner) const;
    bool affine(Tree t, double& c0, double& c1, Tree& atom) const;
    bool scaled(Tree t, double& c, Tree& atom) const;
    void normalize(std::vector<Mono>& terms, std::unordered_map<Tree, Tree>& memo) const;
    void add(Mono& m, Tree base, int power, Tree square) const;
    Tree build(const Mono& m, std::unordered_map<Tree, Tree>& memo) const;
    void factor(std::vector<Mono> terms, std::vector<std::pair<int, Tree>>& out,
                std::unordered_map<Tree, Tree>& memo, bool& changed) const;
};

// t is c * atom : a number times a real signal at the sample rate, or the signal itself
bool Factorer::scaled(Tree t, double& c, Tree& atom) const
{
    Tree x, a, b;
    tvec fs;
    double k;
    c = 1;
    while (isSigNeg(t, x)) {
        c = -c;
        t = x;
    }
    if (isSigProd(t, fs) && fs.size() == 2) {
        a = fs[0], b = fs[1];
    } else if (!isSigMul(t, a, b)) {
        a = b = nullptr;
    }
    if (a != nullptr) {
        if (numVal(a, k)) {
            c *= k, t = b;
        } else if (numVal(b, k)) {
            c *= k, t = a;
        } else {
            a = nullptr;
        }
    } else if (isSigFIR(t, fs) && fs.size() == 2 && numVal(fs[1], k)) {
        c *= k, t = fs[0];
    }
    if (numVal(t, k) || fExact.nature(t) != kReal || fExact.variability(t) != kSamp) {
        return false;
    }
    atom = t;
    return c != 0;
}

// t is c0 + c1 * atom, two terms, c0 a number
bool Factorer::affine(Tree t, double& c0, double& c1, Tree& atom) const
{
    tvec subs;
    if (!isSigSum(t, subs) || subs.size() != 2) {
        return false;
    }
    for (int i = 0; i < 2; i++) {
        if (numVal(subs[i], c0) && scaled(subs[1 - i], c1, atom)) {
            return true;
        }
    }
    return false;
}

// the affine factors of a sum, t + gamma : the gammas of one t that the program cannot tell
// apart (sameGamma, one sign) count as one, the most frequent. A class that holds two
// origins at least (two nodes, or the weight of a mix) is normalized, c1 joining the number
// of the term ; a class of one node keeps it as it is : already common to the terms that
// hold it, written c1 * (t + gamma) it would spread c1 over them (moogHalfLadder). Then a
// factor held twice by a monomial is one factor of power 2
void Factorer::normalize(std::vector<Mono>& terms, std::unordered_map<Tree, Tree>& memo) const
{
    std::vector<Tree>                                   atoms;
    std::unordered_map<Tree, std::map<double, int>>     gammas;
    for (auto& m : terms) {
        for (auto& f : m.factors) {
            if (f.atom == nullptr) continue;
            if (gammas.find(f.atom) == gammas.end()) atoms.push_back(f.atom);
            gammas[f.atom][f.gamma]++;
        }
    }
    for (Tree t : atoms) {
        std::map<double, double> rep;
        auto&                    gs = gammas[t];
        for (auto it = gs.begin(); it != gs.end();) {
            std::vector<std::pair<double, int>> cluster;
            const double                        g0 = it->first;
            do {
                cluster.push_back(*it);
                ++it;
            } while (it != gs.end() && g0 != 0 && it->first != 0 && (it->first > 0) == (g0 > 0) &&
                     sameGamma(std::max(std::fabs(it->first), std::fabs(g0)),
                               std::min(std::fabs(it->first), std::fabs(g0))));
            double best = cluster[0].first;
            int    n    = cluster[0].second;
            for (auto& [g, k] : cluster) {
                if (k > n) best = g, n = k;
            }
            for (auto& [g, k] : cluster) rep[g] = best;
        }
        // the origins of each class : distinct nodes, every weight of a mix counted apart
        std::map<double, std::unordered_set<Tree>> nodes;
        std::map<double, int>                      weights;
        for (auto& m : terms) {
            for (auto& f : m.factors) {
                if (f.atom != t) continue;
                if (f.src != nullptr) {
                    nodes[rep[f.gamma]].insert(f.src);
                } else {
                    weights[rep[f.gamma]]++;
                }
            }
        }
        for (auto& m : terms) {
            for (auto& f : m.factors) {
                if (f.atom != t) continue;
                const double g = rep[f.gamma];
                if (f.src != nullptr && nodes[g].size() + weights[g] < 2) {
                    f.base = f.src;  // kept as it is
                    f.atom = nullptr;
                    continue;
                }
                for (int k = 0; k < f.power; k++) m.coef *= f.scale;
                f.gamma = g;
                if (f.gamma == 0) {
                    f.base = t;
                } else {
                    Tree g  = sigReal(f.gamma);
                    Tree x  = memo.at(t);
                    f.base  = sigSum({g, x});
                    f.fresh = true;
                }
            }
        }
    }
    for (auto& m : terms) {
        std::vector<Factor> merged;
        for (auto& f : m.factors) {
            auto it = std::find_if(merged.begin(), merged.end(), [&](const Factor& g) { return g.base == f.base; });
            if (it == merged.end()) {
                merged.push_back(f);
            } else {
                it->power += f.power;
                it->square = nullptr;
            }
        }
        m.factors = merged;
    }
}

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
// real factors, pow(x, 2), an affine factor c0 + c1 * t, or another real signal, a factor
// of its own. A product that holds an integer factor is no monomial : its integer
// operations stay as certified. A node below the term that signals outside the terms of
// the sum read too (fOpaque) is one factor : it is computed once for all its readers, and
// dividing it would compute its factors again.
bool Factorer::parse(Tree t, Mono& m, bool inner) const
{
    Tree   x, a, b;
    tvec   fs;
    double c;
    if (inner) {
        fCounts[t]++;
    }
    if (inner && fOpaque.count(t) != 0 && !numVal(t, c)) {
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
    double c0, c1;
    Tree   atom;
    if (inner && affine(t, c0, c1, atom)) {
        Factor f{nullptr, 1, nullptr};
        f.atom  = atom;
        f.gamma = c0 / c1;
        f.scale = c1;
        f.src   = t;
        m.factors.push_back(f);
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
            Tree b = f.fresh ? f.base : memo.at(f.base);
            for (int k = 0; k < f.power; k++) {
                fs.push_back(b);
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
    std::unordered_map<Tree, bool>                freshOf;  ///< a base that is a new tree
    for (const auto& m : terms) {
        for (const auto& f : m.factors) {
            if (fExact.variability(f.atom != nullptr ? f.atom : f.base) != kSamp) {
                continue;
            }
            freshOf[f.base] = f.fresh;
            auto it         = stat.find(f.base);
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
    Tree base = freshOf[best] ? best : memo.at(best);
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
    fOpaque.clear();
    auto degree = [](const Mono& m) {
        int d = 0;
        for (const auto& f : m.factors) d += f.power;
        return d;
    };
    auto holdsAffine = [](const Mono& m, Tree t) {
        for (const auto& f : m.factors) {
            if (f.atom == t) return true;
        }
        return false;
    };
    // the terms parsed until the nodes read outside the terms of the sum are known : a node
    // that the terms read as often as the whole program does is theirs alone
    for (int round = 0;; round++) {
    terms.clear();
    products = 0;
    fCounts.clear();
    for (size_t i = 0; i < subs.size(); i++) {
        // a mix (1 - c) * a + c * b, c affine in t, a and b products that hold an affine
        // factor in t (the terms of a Lagrange interpolation, two of them joined in a mix) :
        // its two terms, 1 - c and c affine factors of theirs
        Tree   c, a, b, t;
        double w0 = 0, w1 = 0;
        if (!shared(subs[i]) && isMixNode(subs[i], c, a, b) && fExact.nature(subs[i]) == kReal &&
            (affine(c, w0, w1, t) || scaled(c, w1, t))) {
            Mono ma, mb;
            if (parse(a, ma, true) && parse(b, mb, true) && holdsAffine(ma, t) && holdsAffine(mb, t)) {
                Factor fa{nullptr, 1, nullptr};
                fa.atom  = t;
                fa.gamma = (w0 - 1) / w1;  // 1 - c = -w1 * (t + (w0 - 1) / w1)
                fa.scale = -w1;
                ma.factors.push_back(fa);
                Factor fb{nullptr, 1, nullptr};
                fb.atom  = t;
                fb.gamma = w0 / w1;  // c = w1 * (t + w0 / w1)
                fb.scale = w1;
                mb.factors.push_back(fb);
                for (Mono* m : {&ma, &mb}) {
                    m->orig = nullptr;
                    m->pos  = int(i);
                    products += (degree(*m) >= 2) ? 1 : 0;
                    terms.push_back(*m);
                }
                continue;
            }
        }
        Mono m;
        if (shared(subs[i]) || !parse(subs[i], m, false)) {
            m = Mono();
        }
        m.orig = subs[i];
        m.pos  = int(i);
        products += (degree(m) >= 2) ? 1 : 0;
        terms.push_back(m);
    }
    // (an affine factor is never kept whole : t + gamma is a tree of its own, shared by
    // every sum that reads it, and c1 joins the number of the term)
    std::vector<Tree> outside;
    for (const auto& [t, n] : fCounts) {
        double v, c0, c1;
        Tree   x;
        if (fOpaque.count(t) == 0 && !numVal(t, v) && fReads[t] > n && !affine(t, c0, c1, x)) {
            outside.push_back(t);
        }
    }
    if (outside.empty()) break;
    if (round == 16) return rebuilt;
    fOpaque.insert(outside.begin(), outside.end());
    }
    if (products < 2) {
        return rebuilt;
    }
    normalize(terms, memo);
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
