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
#include <cstdint>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "exception.hh"
#include "global.hh"
#include "rewrite.hh"
#include "shareSums.hh"
#include "sigattributes.hh"
#include "sigtype.hh"

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

/// an atom of the rows : a signal, or a signal read d samples late (a tap)
struct AtomKey {
    Tree base;
    int  delay;
    bool operator==(const AtomKey& o) const { return base == o.base && delay == o.delay; }
};

struct AtomKeyHash {
    size_t operator()(const AtomKey& k) const
    {
        return std::hash<Tree>()(k.base) * 31 + std::hash<int>()(k.delay);
    }
};

/// a sum of atoms with coefficients +1 or -1, ordered by atom index
using Signed = std::map<int, int>;

/// a dense row : the node and its terms (atom, coefficient), in the order of the node
struct Row {
    Tree                                node;
    std::vector<std::pair<int, double>> terms;
};

/// what an atom index stands for : an original atom, a product c * S, or a pair u + rel * v
struct AtomDef {
    enum Kind { kOrig, kProduct, kPair } kind;
    AtomKey orig{nullptr, 0};
    double  coef = 0;   ///< kProduct : the coefficient
    int     sum  = -1;  ///< kProduct : the index of S in fSums
    int     u = -1, v = -1, rel = 0;  ///< kPair
};

class Planner {
   public:
    std::vector<AtomDef>                           fAtoms;
    std::unordered_map<AtomKey, int, AtomKeyHash>  fIndex;
    std::vector<Row>                               fRows;
    std::vector<Signed>                            fSums;      ///< the top sum of row r is fSums[r]
    std::map<std::pair<double, Signed>, int>       fProducts;  ///< (coefficient, S) -> atom
    std::vector<bool>                              fRewrite;   ///< row r is rewritten
    std::unordered_map<Tree, int>                  fRowOf;     ///< node -> row
    std::unordered_map<int, Tree>                  fBuilt;     ///< atom -> its tree

    explicit Planner(Tree L) : fExact(L) {}

    void collect(Tree L);
    void plan();
    Tree rewrite(Tree L);

   private:
    ExactSolvers fExact;

    bool isReal(Tree t) const { return fExact.nature(t) == kReal; }
    int  atom(Tree base, int delay);
    bool parseTerm(Tree t, double sign, std::vector<std::pair<int, double>>& terms);
    bool rowOf(Tree t, Row& row);
    Tree buildAtom(int a, std::unordered_map<Tree, Tree>& memo);
    Tree buildSigned(const Signed& s, std::unordered_map<Tree, Tree>& memo);
};

int Planner::atom(Tree base, int delay)
{
    // x@d with a constant d is the tap d of x, the same atom as the tap of a FIR on x
    Tree x, d;
    int  k;
    if (isSigDelay(base, x, d) && isSigInt(d, &k) && k >= 0) {
        base = x;
        delay += k;
    }
    AtomKey key{base, delay};
    auto    it = fIndex.find(key);
    if (it != fIndex.end()) {
        return it->second;
    }
    AtomDef def;
    def.kind = AtomDef::kOrig;
    def.orig = key;
    fAtoms.push_back(def);
    int a = int(fAtoms.size()) - 1;
    fIndex[key] = a;
    return a;
}

// a term of a Sum : neg(x), c * x (a product, a binary multiplication or the gain kernel
// FIR[x, c]), or x itself
bool Planner::parseTerm(Tree t, double sign, std::vector<std::pair<int, double>>& terms)
{
    Tree   x, a, b;
    tvec   fs;
    double c;
    if (isSigNeg(t, x)) {
        return parseTerm(x, -sign, terms);
    }
    if (isSigProd(t, fs) && fs.size() == 2) {
        a = fs[0], b = fs[1];
    } else if (isSigMul(t, a, b)) {
    } else if (isSigFIR(t, fs) && fs.size() == 2 && numVal(fs[1], c)) {
        a = fs[1], b = fs[0];
    } else {
        a = b = nullptr;
    }
    if (a != nullptr) {
        double     ca, cb;
        const bool na = numVal(a, ca);
        const bool nb = numVal(b, cb);
        if (na != nb) {
            Tree         y = na ? b : a;
            const double k = na ? ca : cb;
            if (!isReal(y)) return false;
            terms.push_back({atom(y, 0), sign * k});
            return true;
        }
    }
    if (!isReal(t)) return false;
    terms.push_back({atom(t, 0), sign});
    return true;
}

// a real Sum, or a real FIR with numeric coefficients, of three terms or more
bool Planner::rowOf(Tree t, Row& row)
{
    tvec subs;
    row.node = t;
    row.terms.clear();
    if (isSigSum(t, subs)) {
        if (!isReal(t)) return false;
        for (Tree s : subs) {
            if (!parseTerm(s, 1, row.terms)) return false;
        }
    } else if (isSigFIR(t, subs) && subs.size() > 2) {
        if (!isReal(t) || !isReal(subs[0])) return false;
        std::vector<double> cs;
        for (size_t i = 1; i < subs.size(); i++) {
            double c;
            if (!numVal(subs[i], c)) return false;
            cs.push_back(c);
        }
        for (size_t i = 0; i < cs.size(); i++) {
            if (cs[i] != 0) {
                row.terms.push_back({atom(subs[0], int(i)), cs[i]});
            }
        }
    } else {
        return false;
    }
    // an atom held twice : its coefficients are added
    std::map<int, double> merged;
    std::vector<int>      order;
    for (auto& [a, c] : row.terms) {
        if (merged.find(a) == merged.end()) order.push_back(a);
        merged[a] += c;
    }
    row.terms.clear();
    for (int a : order) {
        if (merged[a] != 0) row.terms.push_back({a, merged[a]});
    }
    return row.terms.size() >= 3;
}

void Planner::collect(Tree L)
{
    // a depth-first walk in the order of the branches, rec bodies included : the atoms
    // are numbered in the order they are met, never by address
    std::unordered_set<Tree> seen;
    std::vector<Tree>        work{L};
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) continue;
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body != nullptr) work.push_back(body);
            continue;
        }
        for (int i = t->arity() - 1; i >= 0; i--) {
            work.push_back(t->branch(i));
        }
        Row row;
        if (rowOf(t, row)) {
            fRowOf[t] = int(fRows.size());
            fRows.push_back(row);
        }
    }
}

void Planner::plan()
{
    const size_t R = fRows.size();
    fRewrite.assign(R, false);
    if (R == 0) return;

    // 1. the magnitudes of the coefficients, in clusters of the magnitudes the program
    //    cannot tell apart : in single precision, equal once rounded to a float (no value
    //    of the program moves) ; in double, within a relative 2^-46, about 64 ulps -- the
    //    error of the coefficients computed at compilation, cos(pi/4) and sin(pi/4) of an
    //    FFT -- a coefficient moving by 1.4e-14 at most ; the representative is 1 when the
    //    cluster holds it, else its most frequent value
    std::map<double, int> mags;
    for (auto& row : fRows) {
        for (auto& [a, c] : row.terms) mags[std::fabs(c)]++;
    }
    // (a magnitude beyond FLT_MAX is an infinity in single precision : the test is an
    // equality, inf - inf being no number, and a cluster always takes its first magnitude)
    const bool   single = (gGlobal->gFloatSize == 1);
    const double tol    = std::ldexp(1.0, -46);
    auto         same   = [single, tol](double m, double start) {
        return single ? double(float(m)) == double(float(start)) : m - start <= tol * start;
    };
    std::map<double, double> rep;
    for (auto it = mags.begin(); it != mags.end();) {
        const double                        start = it->first;
        std::vector<std::pair<double, int>> cluster;
        do {
            cluster.push_back(*it);
            ++it;
        } while (it != mags.end() && same(it->first, start));
        double best = cluster[0].first;
        int    n    = cluster[0].second;
        for (auto& [v, k] : cluster) {
            if (v == 1.0) {
                best = 1.0;
                n    = INT32_MAX;
            } else if (k > n) {
                best = v;
                n    = k;
            }
        }
        for (auto& [v, k] : cluster) rep[v] = best;
    }

    // 2. each row : the terms of magnitude 1 in its top sum, the others factored by
    //    magnitude into products c * S, S normalized with its first atom positive
    std::vector<int> groupsOf(R, 0);
    fSums.assign(R, Signed());
    for (size_t r = 0; r < R; r++) {
        std::map<double, Signed> groups;
        for (auto& [a, c] : fRows[r].terms) {
            const double m = rep[std::fabs(c)];
            const int    s = (c > 0) ? 1 : -1;
            if (m == 1.0) {
                fSums[r][a] += s;
            } else {
                groups[m][a] += s;
            }
        }
        for (auto& [m, S] : groups) {
            if (S.size() >= 2) groupsOf[r]++;
            const int flip = S.begin()->second;
            Signed    norm;
            for (auto& [a, s] : S) norm[a] = s * flip;
            auto key = std::make_pair(m, norm);
            auto it  = fProducts.find(key);
            int  p;
            if (it == fProducts.end()) {
                fSums.push_back(norm);
                AtomDef def;
                def.kind = AtomDef::kProduct;
                def.coef = m;
                def.sum  = int(fSums.size()) - 1;
                fAtoms.push_back(def);
                p              = int(fAtoms.size()) - 1;
                fProducts[key] = p;
            } else {
                p = it->second;
            }
            fSums[r][p] += flip;
        }
    }

    // 3. the signed pair the most sums hold becomes an atom, until no pair is held twice ;
    //    ties go to the smallest (u, v, rel), so that the result does not depend on hashing
    size_t work = 0;
    for (auto& s : fSums) work += s.size() * s.size();
    const size_t kBudget = 50000000;
    while (work > 0) {
        // past the budget, stop before a counting pass whose result would be dropped (a
        // dense FIR of 32768 taps alone counts 5e8 pairs)
        if (work > kBudget) break;
        // a pair held twice is made of atoms held by two sums at least : the pairs of the
        // other atoms are counted once and never chosen, they are not counted. The work,
        // which the budget reads, stays that of the whole sums.
        std::unordered_map<int, int> holders;
        for (auto& s : fSums) {
            if (s.size() < 2) continue;
            for (auto& [a, sign] : s) holders[a]++;
        }
        std::unordered_map<uint64_t, int> count;
        size_t                            pass = 0;
        std::vector<std::pair<int, int>>  shared;
        for (auto& s : fSums) {
            if (s.size() < 2) continue;
            pass += s.size() * s.size();
            shared.clear();
            for (auto& [a, sign] : s) {
                if (holders[a] > 1) shared.emplace_back(a, sign);
            }
            for (size_t i = 0; i < shared.size(); ++i) {
                for (size_t j = i + 1; j < shared.size(); ++j) {
                    const uint64_t key = (uint64_t(shared[i].first) << 33) |
                                         (uint64_t(shared[j].first) << 1) |
                                         uint64_t(shared[i].second * shared[j].second > 0);
                    count[key]++;
                }
            }
        }
        uint64_t bestKey = 0;
        int      bestN   = 1;
        for (auto& [key, n] : count) {
            if (n > bestN || (n == bestN && n > 1 && key < bestKey)) {
                bestKey = key;
                bestN   = n;
            }
        }
        if (bestN < 2 || work > kBudget) break;
        work += pass;
        const int u   = int(bestKey >> 33);
        const int v   = int((bestKey >> 1) & 0xFFFFFFFF);
        const int rel = (bestKey & 1) ? 1 : -1;
        AtomDef   def;
        def.kind = AtomDef::kPair;
        def.u    = u;
        def.v    = v;
        def.rel  = rel;
        fAtoms.push_back(def);
        const int t = int(fAtoms.size()) - 1;
        for (auto& s : fSums) {
            auto iu = s.find(u);
            auto iv = s.find(v);
            if (iu != s.end() && iv != s.end() && iu->second * iv->second == rel) {
                const int su = iu->second;
                s.erase(iu);
                s.erase(v);
                s[t] = su;
            }
        }
    }

    // 4. a row is rewritten when it gains : a factored group, a pair, a product held by
    //    another row or whose sum holds a pair
    std::map<int, int> productUses;
    for (size_t r = 0; r < R; r++) {
        for (auto& [a, s] : fSums[r]) {
            if (fAtoms[a].kind == AtomDef::kProduct) productUses[a]++;
        }
    }
    auto holdsPair = [&](const Signed& s) {
        for (auto& [a, x] : s) {
            if (fAtoms[a].kind == AtomDef::kPair) return true;
        }
        return false;
    };
    for (size_t r = 0; r < R; r++) {
        bool gain = groupsOf[r] > 0 || holdsPair(fSums[r]);
        for (auto& [a, s] : fSums[r]) {
            if (fAtoms[a].kind == AtomDef::kProduct &&
                (productUses[a] > 1 || holdsPair(fSums[fAtoms[a].sum]))) {
                gain = true;
            }
        }
        fRewrite[r] = gain;
    }
}

Tree Planner::buildAtom(int a, std::unordered_map<Tree, Tree>& memo)
{
    auto it = fBuilt.find(a);
    if (it != fBuilt.end()) return it->second;
    const AtomDef& def = fAtoms[a];
    Tree           t;
    if (def.kind == AtomDef::kOrig) {
        auto m = memo.find(def.orig.base);
        faustassert(m != memo.end());
        t = m->second;
        // a member of a recursion is read at the current tick as x@0, the form the code
        // generators expect there ; another signal read without delay is itself
        int  i;
        Tree g;
        if (def.orig.delay > 0 || isProj(def.orig.base, &i, g)) {
            Tree d = sigInt(def.orig.delay);
            t      = sigDelay(t, d);
        }
    } else if (def.kind == AtomDef::kProduct) {
        Tree c = sigReal(def.coef);
        Tree s = buildSigned(fSums[def.sum], memo);
        t      = sigProd({c, s});
    } else {
        Tree u = buildAtom(def.u, memo);
        Tree v = buildAtom(def.v, memo);
        if (def.rel < 0) v = sigNeg(v);
        t = sigSum({u, v});
    }
    fBuilt[a] = t;
    return t;
}

Tree Planner::buildSigned(const Signed& s, std::unordered_map<Tree, Tree>& memo)
{
    tvec terms;
    for (auto& [a, sg] : s) {
        Tree x = buildAtom(a, memo);
        if (sg < 0) x = sigNeg(x);
        terms.push_back(x);
    }
    faustassert(!terms.empty());
    return (terms.size() == 1) ? terms[0] : sigSum(terms);
}

Tree Planner::rewrite(Tree L)
{
    std::unordered_map<Tree, Tree> memo;
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        auto it = fRowOf.find(orig);
        if (it == fRowOf.end() || !fRewrite[it->second]) return rebuilt;
        return buildSigned(fSums[it->second], memo);
    };
    return treeRewritePaired(L, rule, memo);
}

}  // namespace

Tree shareSums(Tree L)
{
    Planner p(L);
    p.collect(L);
    p.plan();
    bool any = false;
    for (bool b : p.fRewrite) any = any || b;
    return any ? p.rewrite(L) : L;
}
