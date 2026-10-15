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
#include <utility>
#include <vector>

#include "exactWeights.hh"
#include "rewrite.hh"
#include "sigattributes.hh"
#include "sigtype.hh"

namespace {

bool isNumber(Tree t)
{
    double v;
    int    i;
    return isSigReal(t, &v) || isSigInt(t, &i);
}

bool isExactlyOne(Tree t)
{
    double v;
    int    i;
    return (isSigReal(t, &v) && v == 1.0) || (isSigInt(t, &i) && i == 1);
}

/// f is 1 + w (in either order), w a signal : gives the position of w in f
bool complementOf(Tree f, int& pos)
{
    tvec ts;
    if (!isSigSum(f, ts) || ts.size() != 2) return false;
    if (isExactlyOne(ts[0]) && !isNumber(ts[1])) return pos = 1, true;
    if (isExactlyOne(ts[1]) && !isNumber(ts[0])) return pos = 0, true;
    return false;
}

/**
 * The cone of the decisions : every signal that may reach the amount of a delay, the operand
 * of an integer conversion, the index of a table or of a soundfile, directly or through a
 * recursion. There, the wider interval of y + w * y (y read twice) could refuse a program
 * that (1 + w) * y lets through ; the products of the cone are left as they are.
 */
std::unordered_set<Tree> decisionCone(Tree L)
{
    std::unordered_set<Tree> seen, cone;
    std::vector<Tree>        work{L}, roots;
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) continue;
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body != nullptr) work.push_back(body);
            continue;
        }
        for (int i = 0; i < t->arity(); i++) work.push_back(t->branch(i));
        Tree x, d, tbl, sz, gen, sf, ch, part;
        if (isSigDelay(t, x, d) && !isNumber(d)) roots.push_back(d);
        if (isSigIntCast(t, x)) roots.push_back(x);
        if (isSigRDTbl(t, tbl, x)) roots.push_back(x);
        if (isSigWRTbl(t, sz, gen, x, d)) roots.push_back(x);
        if (isSigSoundfileBuffer(t, sf, ch, part, x)) {
            roots.push_back(part);
            roots.push_back(x);
        }
        if (isSigSoundfileLength(t, sf, part) || isSigSoundfileRate(t, sf, part)) roots.push_back(part);
    }
    while (!roots.empty()) {
        Tree t = roots.back();
        roots.pop_back();
        if (!cone.insert(t).second) continue;
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body != nullptr) roots.push_back(body);
            continue;
        }
        for (int i = 0; i < t->arity(); i++) roots.push_back(t->branch(i));
    }
    return cone;
}

}  // namespace

/// a real product with a factor 1 + w is held somewhere
static bool hasCandidate(Tree L, ExactSolvers& exact, const std::unordered_set<Tree>& cone)
{
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
        for (int i = 0; i < t->arity(); i++) work.push_back(t->branch(i));
        tvec fs;
        if (isSigProd(t, fs) && fs.size() >= 2 && exact.nature(t) == kReal && cone.count(t) == 0) {
            for (Tree f : fs) {
                int pos;
                if (complementOf(f, pos)) return true;
            }
        }
    }
    return false;
}

Tree exactWeights(Tree L)
{
    ExactSolvers                   exact(L);
    const std::unordered_set<Tree> cone = decisionCone(L);
    // a rewrite rebuilds the recursions with fresh variables : none when nothing changes
    if (!hasCandidate(L, exact, cone)) return L;
    std::unordered_map<Tree, Tree> memo;
    // the rewritten products : result -> (w * P, P)
    std::unordered_map<Tree, std::pair<Tree, Tree>> split;
    auto product = [&](Tree orig, Tree rebuilt) -> Tree {
        tvec of, rf;
        if (!isSigProd(orig, of) || !isSigProd(rebuilt, rf) || of.size() != rf.size() || of.size() < 2) {
            return rebuilt;
        }
        if (exact.nature(orig) != kReal || cone.count(orig) != 0) return rebuilt;
        for (size_t k = 0; k < of.size(); k++) {
            int pos, rpos;
            if (!complementOf(of[k], pos) || !complementOf(rf[k], rpos) || rpos != pos) continue;
            // P : the other factors, rebuilt
            tvec rest;
            for (size_t j = 0; j < rf.size(); j++) {
                if (j != k) rest.push_back(rf[j]);
            }
            Tree p  = (rest.size() == 1) ? rest[0] : sigProd(rest);
            Tree rw = rf[k]->branch(pos);
            Tree om, wp;
            if (isSigNeg(rw, om)) {
                Tree q = sigProd({om, p});
                wp     = sigNeg(q);
            } else {
                wp = sigProd({rw, p});
            }
            // the small term first : w * P + P
            Tree r   = sigSum({wp, p});
            split[r] = {wp, p};
            return r;
        }
        return rebuilt;
    };
    // a sum holding (1 + w) * P with other terms : the small terms are added first, then P,
    // (t1 + ... + w * P) + P, so that P does not absorb their low digits
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        Tree r = product(orig, rebuilt);
        if (r != rebuilt) return r;
        tvec ts;
        if (!isSigSum(rebuilt, ts) || ts.size() < 2) return rebuilt;
        for (size_t k = 0; k < ts.size(); k++) {
            auto it = split.find(ts[k]);
            if (it == split.end()) continue;
            tvec inner;
            for (size_t j = 0; j < ts.size(); j++) {
                if (j != k) inner.push_back(ts[j]);
            }
            inner.push_back(it->second.first);
            Tree small = sigSum(inner);
            return sigSum({small, it->second.second});
        }
        return rebuilt;
    };
    return treeRewritePaired(L, rule, memo);
}
