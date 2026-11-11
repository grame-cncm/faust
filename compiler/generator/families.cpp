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

#include "families.hh"

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <unordered_set>

#include "binop.hh"
#include "computeSignals.hh"
#include "decisionCone.hh"
#include "mixForm.hh"
#include "ppsig.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

namespace {

/// the fewest cells of an automaton : below, the loop over the cells and the rotation of its
/// rows cost more than the scalar code (measured on 1dDampedWaveEquation : the automaton loses
/// up to 30 cells and wins from 46, on x86 and on arm)
const int kAutomatonMinCells = 40;

bool famTrace()
{
    static const bool trace = getenv("FAUST_FAM_TRACE") != nullptr;
    return trace;
}

/// slow : computed per block or once, not per sample, by the certified variability. An
/// untyped node is structure : a cell of a group's definitions, or the datum of a node (the
/// index of a projection, the form of a cfMix)
bool famSlow(Tree t)
{
    AudioType* ty = (AudioType*)t->getType();
    return ty != nullptr && ty->variability() < kSamp;
}

/// the operands of a sum or the factors of a product : their order does not count
bool unordered(Tree t, tvec& ops)
{
    return isSigSum(t, ops) || isSigProd(t, ops);
}

/// The abstract shape of a node : an interned key, computed bottom-up, the same operators
/// and arities with the children replaced by their shapes, and three kinds of holes where
/// the members may differ -- a slow subtree (SLOW), an audio input or a rare closed subtree
/// (AUDIO), and a reference to an enclosing group (REF, by its binding depth). The integer
/// literals stay structural (a projection index, a delay) and a recursive group is the shape
/// of its body. A key is an int, never a tree : no serial is consumed by the analysis.
using Shape = int;

struct FamShapes {
    std::map<std::string, Shape>    intern;
    std::vector<int>                sizes;
    std::vector<std::string>        ops;
    std::vector<std::vector<Shape>> kids;
    Shape                           SLOW, AUDIO;
    std::map<Tree, Shape, treeorder> memo;  // closed subtrees
    std::vector<Tree>               stack;  // the enclosing groups (their identifiers), innermost last
    // open subtrees, per stack of enclosing groups : an open subtree's shape depends on the
    // levels of the groups it names, and on nothing else ; memoized so that a body whose
    // subtrees are shared is walked once per node, not once per path
    std::map<std::vector<Tree>, std::map<Tree, Shape, treeorder>> openMemo;
    TreeSet                         holes;  // the rare closed subtrees, audio slots of their parents
    std::map<Tree, TreeSet, treeorder> refs;

    FamShapes()
    {
        SLOW  = make("SLOW", 1, "SLOW", {});
        AUDIO = make("AUDIO", 1, "AUDIO", {});
    }
    void clearMemo()
    {
        memo.clear();
        openMemo.clear();
    }
    Shape make(const std::string& key, int size, const std::string& op, const std::vector<Shape>& br)
    {
        if (auto it = intern.find(key); it != intern.end()) {
            return it->second;
        }
        sizes.push_back(size);
        ops.push_back(op);
        kids.push_back(br);
        return intern[key] = Shape(sizes.size()) - 1;
    }
    int         size(Shape s) const { return sizes[s]; }
    std::string print(Shape s, int budget = 100) const
    {
        std::string r = ops[s];
        if (kids[s].empty() || budget <= 0) {
            return kids[s].empty() ? r : r + "(...)";
        }
        r += "(";
        std::string sep;
        for (Shape b : kids[s]) {
            r += sep + print(b, budget / int(kids[s].size()) - 1);
            sep = ",";
            if (int(r.size()) > budget) {
                return r + "...";
            }
        }
        return r + ")";
    }
    /// the groups a subtree names (its projections, bodies not entered)
    const TreeSet& groupsOf(Tree t)
    {
        if (auto it = refs.find(t); it != refs.end()) {
            return it->second;
        }
        TreeSet r;
        Tree    id, body;
        if (isRec(t, id, body)) {
            r.insert(id);
        } else {
            for (int k = 0; k < t->arity(); k++) {
                const TreeSet& c = groupsOf(t->branch(k));
                r.insert(c.begin(), c.end());
            }
        }
        return refs[t] = r;
    }
    bool openHere(Tree t)
    {
        for (Tree id : stack) {
            if (groupsOf(t).count(id)) {
                return true;
            }
        }
        return false;
    }
    Shape shapeOf(Tree t)
    {
        // std::map keeps its references valid across insertions : m survives compute
        std::map<Tree, Shape, treeorder>& m = openHere(t) ? openMemo[stack] : memo;
        if (auto it = m.find(t); it != m.end()) {
            return it->second;
        }
        Shape r = compute(t);
        m[t]    = r;
        return r;
    }
    Shape compute(Tree t)
    {
        int  i;
        Tree id, body, x, y;
        if (isSigInt(t, &i) && t->getType() == nullptr) {
            return make("I" + std::to_string(i), 1, std::to_string(i), {});
        }
        if (t->getType() == nullptr && t->arity() == 0 && isNum(t)) {
            std::ostringstream d;
            d << t->node();
            return make("D" + d.str(), 1, d.str(), {});  // a datum of its parent
        }
        if (isRec(t, id, body)) {
            int level = 0;
            for (auto it = stack.rbegin(); it != stack.rend(); ++it, level++) {
                if (*it == id) {
                    return make("REF" + std::to_string(level), 1, "REF" + std::to_string(level), {});
                }
            }
            if (!body) {
                return make("REF-1", 1, "REF-1", {});
            }
            stack.push_back(id);
            Shape b = shapeOf(body);
            stack.pop_back();
            return make("REC(" + std::to_string(b) + ")", 1 + size(b), "REC", {b});
        }
        if (famSlow(t)) {
            return SLOW;
        }
        if (Tree g; isProj(t, &i, g)) {
            // the index of a projection is structural (a raw integer, no signal)
            Shape sg = shapeOf(g);
            return make("PROJ" + std::to_string(i) + "(" + std::to_string(sg) + ")", 1 + size(sg),
                        "proj" + std::to_string(i), {sg});
        }
        if (isSigInput(t, &i)) {
            return AUDIO;
        }
        if (isSigDelay(t, x, y) && isZero(y)) {
            return holes.count(x) ? AUDIO : shapeOf(x);  // a delay of zero is its signal
        }
        if (isSigDelay(t, x, y) && isSigInt(y, &i) && i != 0) {
            // the amount of a delay is structural ; an integer elsewhere is a coefficient
            Shape sx = holes.count(x) ? AUDIO : shapeOf(x);
            return make("DELAY" + std::to_string(i) + "(" + std::to_string(sx) + ")", 1 + size(sx),
                        "@" + std::to_string(i), {sx});
        }
        std::vector<Shape> br;
        for (int k = 0; k < t->arity(); k++) {
            Tree c = t->branch(k);
            br.push_back(holes.count(c) ? AUDIO : shapeOf(c));  // a hole is opaque to its parent only
        }
        if (tvec ops2; unordered(t, ops2)) {
            std::sort(br.begin(), br.end());
        }
        std::ostringstream key, opss;
        opss << t->node();
        const std::string op = opss.str();
        key << op << "#" << t->arity();
        int sz = 1;
        for (Shape b : br) {
            key << "," << b;
            sz += size(b);
        }
        return make(key.str(), sz, op, br);
    }
};

/// every audio node reachable from the root, with its shape ; the classes are the shapes
/// shared by several nodes
struct FamClasses {
    std::map<Shape, std::vector<Tree>> members;  // shape -> nodes, in serial order
    std::map<Tree, Shape, treeorder>   shapeOfNode;
    std::map<TreeSet, std::map<Tree, bool, treeorder>> insideMemo;

    /// The occurrence rule, from the leaves up. A node whose shape has fewer than 4
    /// occurrences and whose children are all settled -- a leaf, a hole, or a node of 4
    /// occurrences or more whose own subtree is settled -- is a hole : its parents see an
    /// audio input, their shapes coarsen, and the count is redone until no hole is added.
    /// A region rare only because of a rare subtree (an excitation, a source) becomes an
    /// input of the members it feeds. Monotone, hence finite.
    void collectWithHoles(Tree root, FamShapes& S)
    {
        for (int round = 0; round < 256; round++) {
            members.clear();
            shapeOfNode.clear();
            S.clearMemo();
            collect(root, S);
            std::map<Tree, bool, treeorder> settled;
            insideMemo.clear();
            TreeSet fresh;
            for (auto& kv : shapeOfNode) {
                int k;
                if (members[kv.second].size() < 4 && !isSigInput(kv.first, &k) && !S.holes.count(kv.first)) {
                    TreeSet active;
                    if (childrenSettled(kv.first, S, settled, active)) {
                        fresh.insert(kv.first);
                    }
                }
            }
            if (famTrace()) {
                int big = 0;
                for (auto& kv : members) {
                    big += kv.second.size() >= 4;
                }
                std::cerr << "fam shapes round " << round << " : " << shapeOfNode.size() << " audio nodes, "
                          << members.size() << " shapes, " << big << " classes of 4 or more, " << fresh.size()
                          << " holes added" << std::endl;
            }
            if (fresh.empty()) {
                break;
            }
            S.holes.insert(fresh.begin(), fresh.end());
        }
    }
    bool rare(Tree t)
    {
        auto it = shapeOfNode.find(t);
        return it != shapeOfNode.end() && members[it->second].size() < 4;
    }
    bool isSettled(Tree c, FamShapes& S, std::map<Tree, bool, treeorder>& memo, TreeSet& active)
    {
        int  i;
        Tree id, body;
        if (isSigInt(c, &i) || famSlow(c) || isSigInput(c, &i) || S.holes.count(c)) {
            return true;
        }
        if (isRec(c, id, body)) {
            if (!body || active.count(id)) {
                return true;  // a self-reference is a leaf
            }
            active.insert(id);
            bool r = childrenSettled(body, S, memo, active);
            active.erase(id);
            return r;
        }
        bool inside = false;  // naming an active group : part of it, transparent
        for (Tree g : active) {
            inside = inside || S.groupsOf(c).count(g);
        }
        if (inside) {
            std::map<Tree, bool, treeorder>& m = insideMemo[active];
            if (auto it = m.find(c); it != m.end()) {
                return it->second;
            }
            bool r                = childrenSettled(c, S, memo, active);
            insideMemo[active][c] = r;
            return r;
        }
        if (auto it = memo.find(c); it != memo.end()) {
            return it->second;
        }
        bool r  = !rare(c) && childrenSettled(c, S, memo, active);
        memo[c] = r;
        return r;
    }
    bool childrenSettled(Tree n, FamShapes& S, std::map<Tree, bool, treeorder>& memo, TreeSet& active)
    {
        Tree id, body;
        if (isRec(n, id, body)) {
            return isSettled(n, S, memo, active);
        }
        for (int b = 0; b < n->arity(); b++) {
            if (!isSettled(n->branch(b), S, memo, active)) {
                return false;
            }
        }
        return true;
    }
    void collect(Tree root, FamShapes& S)
    {
        TreeSet           seen;
        std::vector<Tree> st{root};
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree id, body;
            if (isRec(t, id, body) && body) {
                st.push_back(body);
                continue;
            }
            if (t->getType() != nullptr && !famSlow(t)) {
                Shape sh       = S.shapeOf(t);
                shapeOfNode[t] = sh;
                members[sh].push_back(t);
            }
            for (int k = 0; k < t->arity(); k++) {
                st.push_back(t->branch(k));
            }
        }
        for (auto& kv : members) {
            std::sort(kv.second.begin(), kv.second.end(), [](Tree a, Tree b) { return a->serial() < b->serial(); });
        }
    }
};

/// The alignment of a member on the template : a slow subtree on both sides is a
/// coefficient slot (even the same node : the slots of every member then line up), an
/// audio input or a hole on both sides an audio slot, an audio node that is the same on
/// both sides a common input, and the rest -- operators, own recursions -- private to the
/// member. The operands of a sum and the factors of a product are paired in a structural
/// order (shape, lowest projection read, serial), not positionally.
struct FamIso {
    std::map<Tree, Tree, treeorder>                        bind;
    std::map<Tree, Tree, treeorder>                        leafBind;
    std::map<std::pair<Tree, Tree>, bool>                  memo;
    std::vector<Tree>                                      slotA, slotB, aslotA, aslotB;
    TreeSet                                                commonA, privA, privB;
    const TreeSet*                                         holes  = nullptr;
    FamShapes*                                             shapes = nullptr;
    Tree                                                   topA = nullptr, topB = nullptr;
    bool                                                   collided = false;
    std::map<Tree, int, treeorder>                         projMemo;

    bool iso(Tree a, Tree b)
    {
        auto key = std::make_pair(a, b);
        if (auto it = memo.find(key); it != memo.end()) {
            return it->second;
        }
        memo[key] = true;
        bool r    = walk(a, b);
        memo[key] = r;
        return r;
    }
    /// a leaf the template shares between two positions must be shared the same way by
    /// the member, or its two columns would read one table
    bool bindLeaf(Tree a, Tree b)
    {
        auto it = leafBind.find(a);
        if (it != leafBind.end()) {
            collided = collided || it->second != b;
            return it->second == b;
        }
        leafBind[a] = b;
        return true;
    }
    bool walk(Tree a, Tree b)
    {
        const bool sa = famSlow(a), sb = famSlow(b);
        if (sa && sb) {
            if (!bindLeaf(a, b)) {
                return false;
            }
            slotA.push_back(a);
            slotB.push_back(b);
            return true;
        }
        int        ka, kb;
        const bool ha = isSigInput(a, &ka) || (holes && a != topA && holes->count(a));
        const bool hb = isSigInput(b, &kb) || (holes && b != topB && holes->count(b));
        if (ha && hb) {
            if (!bindLeaf(a, b)) {
                return false;
            }
            aslotA.push_back(a);
            aslotB.push_back(b);
            return true;
        }
        if (a == b) {
            if (a->getType() != nullptr) {
                commonA.insert(a);
            }
            return true;
        }
        if (sa != sb) {
            return false;
        }
        Tree ia, ba, ib, bb;
        if (int pa, pb; isProj(a, &pa, ia) && isProj(b, &pb, ib)) {
            if (pa != pb) {
                return false;
            }
            privA.insert(a);
            privB.insert(b);
            return iso(ia, ib);
        }
        if (isRec(a, ia, ba) && isRec(b, ib, bb)) {
            if (auto it = bind.find(ia); it != bind.end()) {
                return it->second == ib;
            }
            bind[ia] = ib;
            privA.insert(a);
            privB.insert(b);
            return iso(ba, bb);
        }
        if (!(a->node() == b->node()) || a->arity() != b->arity()) {
            return false;
        }
        privA.insert(a);
        privB.insert(b);
        if (tvec oa0, ob0; unordered(a, oa0) && unordered(b, ob0)) {
            const std::vector<Tree> oa = ordered(oa0), ob = ordered(ob0);
            for (size_t k = 0; k < oa.size(); k++) {
                if (!iso(oa[k], ob[k])) {
                    return false;
                }
            }
            return true;
        }
        for (int k = 0; k < a->arity(); k++) {
            if (!iso(a->branch(k), b->branch(k))) {
                return false;
            }
        }
        return true;
    }
    int lowestProj(Tree t)
    {
        if (auto it = projMemo.find(t); it != projMemo.end()) {
            return it->second;
        }
        int  r = INT_MAX, i;
        Tree g, id, body;
        if (isProj(t, &i, g)) {
            r = i;
        } else if (!isRec(t, id, body)) {
            for (int k = 0; k < t->arity(); k++) {
                r = std::min(r, lowestProj(t->branch(k)));
            }
        }
        return projMemo[t] = r;
    }
    std::vector<Tree> ordered(const tvec& ops)
    {
        std::vector<std::tuple<int, int, int, Tree>> keyed;
        for (Tree o : ops) {
            keyed.push_back({shapes->holes.count(o) ? shapes->AUDIO : shapes->shapeOf(o), lowestProj(o), int(o->serial()), o});
        }
        std::sort(keyed.begin(), keyed.end(), [](const auto& x, const auto& y) {
            return std::tie(std::get<0>(x), std::get<1>(x), std::get<2>(x)) < std::tie(std::get<0>(y), std::get<1>(y), std::get<2>(y));
        });
        std::vector<Tree> r;
        for (auto& k : keyed) {
            r.push_back(std::get<3>(k));
        }
        return r;
    }
};

/// a state the loop can read at a past sample : a recursive filter, a projection of a
/// group, a constant delay of one
bool famIsState(Tree x)
{
    Tree x2, y, W, defs;
    int  d, i;
    tvec V;
    if (isSigDelay(x, x2, y)) {
        return isSigInt(y, &d) && famIsState(x2);
    }
    return isSigIIR(x, V) || (isProj(x, &i, x2) && isRec(x2, W, defs));
}

bool famReal(Tree t)
{
    AudioType* ty = (AudioType*)t->getType();
    return ty != nullptr && ty->nature() == kReal;
}

bool famCheckNode(Tree t, const TreeSet& slots, const TreeSet& commons, TreeSet& seen);

Tree famCulprit = nullptr;  // the innermost node famCheck refused, for the trace

/// what the loop can generate, decided when the family is planned : a family is planned
/// only if its template is generable, since its private nodes then leave the schedule
bool famCheck(Tree t, const TreeSet& slots, const TreeSet& commons, TreeSet& seen)
{
    const bool ok = famCheckNode(t, slots, commons, seen);
    if (!ok && famCulprit == nullptr) {
        famCulprit = t;
    }
    return ok;
}

bool famCheckNode(Tree t, const TreeSet& slots, const TreeSet& commons, TreeSet& seen)
{
    if (slots.count(t) || commons.count(t) || !seen.insert(t).second) {
        return true;
    }
    tvec V;
    if (isSigIIR(t, V)) {
        // IIR[X, C1, ..., Cn] : y = X + C1.y' + ... + Cn.y@n
        for (Tree v : V) {
            if (!famCheck(v, slots, commons, seen)) {
                return false;
            }
        }
        return famReal(t);
    }
    if (isSigFIR(t, V)) {
        // FIR[X, c0, c1, ...] : c0.X + c1.X' + ... ; a history of a state only
        if (V.size() > 2 && !famIsState(V[0])) {
            return false;
        }
        for (Tree v : V) {
            if (!famCheck(v, slots, commons, seen)) {
                return false;
            }
        }
        return famReal(t);
    }
    Tree x, y, grp, W, defs;
    int  d, i;
    if (isSigDelay(t, x, y)) {
        return isSigInt(y, &d) && (d == 0 || famIsState(x)) && famCheck(x, slots, commons, seen);
    }
    if (isProj(t, &i, grp)) {
        if (!isRec(grp, W, defs)) {
            return false;
        }
        if (seen.count(grp)) {
            return true;
        }
        seen.insert(grp);
        for (Tree l = defs; isList(l); l = tl(l)) {
            if (!famReal(hd(l)) || !famCheck(hd(l), slots, commons, seen)) {
                return false;
            }
        }
        return true;
    }
    int  op;
    Tree a, b;
    if (isSigBinOp(t, &op, a, b)) {
        // the real arithmetic, spelled as the operator itself, and the comparison of two reals
        // or of two integers (exact : its 0 or 1 is held exactly by a real local)
        auto       isInt   = [](Tree u) {
            AudioType* ty = (AudioType*)u->getType();
            return ty != nullptr && ty->nature() == kInt;
        };
        const bool arith   = famReal(t) && (op == kAdd || op == kSub || op == kMul || op == kDiv);
        const bool compare = (op == kGT || op == kLT || op == kGE || op == kLE || op == kEQ || op == kNE) &&
                             ((famReal(a) && famReal(b)) || (isInt(a) && isInt(b)));
        return (arith || compare) && famCheck(a, slots, commons, seen) && famCheck(b, slots, commons, seen);
    }
    if (isSigNeg(t, a)) {
        return famReal(t) && famCheck(a, slots, commons, seen);
    }
    if (unordered(t, V)) {
        if (!famReal(t)) {
            return false;
        }
        for (Tree u : V) {
            if (!famCheck(u, slots, commons, seen)) {
                return false;
            }
        }
        return true;
    }
    Tree sel, s0, s1;
    if (isSigSelect2(t, sel, s0, s1)) {
        return famCheck(sel, slots, commons, seen) && famCheck(s0, slots, commons, seen) &&
               famCheck(s1, slots, commons, seen);
    }
    if (sigXtendedData(t) != nullptr) {
        if (!famReal(t)) {
            return false;  // a math primitive : real results only
        }
        for (int k = 0; k < t->arity(); k++) {
            if (!famCheck(t->branch(k), slots, commons, seen)) {
                return false;
            }
        }
        return true;
    }
    if (isSigFloatCast(t, x)) {
        return famCheck(x, slots, commons, seen);
    }
    MixForm form;
    if (isCfMix(t, sel, s0, s1, form)) {
        // the form is a datum of the node, part of the shape : the same for every member ;
        // from the weight, c is read as 1 - t, so c must be a node of the member
        Tree w;
        if (form == MixForm::kFromWeight) {
            if (slots.count(sel) || commons.count(sel) || !mixComplementOf(sel, w)) {
                return false;
            }
            sel = w;
        }
        return famReal(t) && famCheck(sel, slots, commons, seen) && famCheck(s0, slots, commons, seen) &&
               famCheck(s1, slots, commons, seen);
    }
    return false;  // cfIrm, cfPhase, cfFrac, Bpf, tables, ... : no family at step 1
}

/// the work of a member : its private nodes, an n-ary node counting for its n - 1 operations
int famWork(const TreeSet& priv, int members)
{
    int w = 0;
    for (Tree t : priv) {
        tvec ops;
        if (unordered(t, ops) || isSigFIR(t, ops) || isSigIIR(t, ops)) {
            w += std::max(1, int(ops.size()) - 1);
        } else if (sigXtendedData(t) != nullptr) {
            w += 4;
        } else {
            w += 1;
        }
    }
    return w / std::max(1, members);
}

/// the states of a member : its private recursive groups and filters
int famStates(const TreeSet& priv, int members)
{
    int n = 0;
    for (Tree t : priv) {
        Tree id, body;
        tvec V;
        n += (isRec(t, id, body) || isSigIIR(t, V) || (isSigFIR(t, V) && V.size() > 2)) ? 1 : 0;
    }
    return n / std::max(1, members);
}

/// whether t reads the group g at the current step : a projection of g read otherwise than
/// through a constant delay of 1 or more, or than as the source of a FIR whose tap of delay 0
/// is zero ; a projection of another group reads what its group reads
bool readsNow(Tree t, Tree g, TreeSet& seen)
{
    if (!seen.insert(t).second) {
        return false;
    }
    int  i, d;
    Tree h, x, y, id, body;
    tvec V;
    if (isProj(t, &i, h)) {
        return h == g || readsNow(h, g, seen);
    }
    if (isRec(t, id, body)) {
        return body != nullptr && readsNow(body, g, seen);
    }
    if (isSigDelay(t, x, y) && isSigInt(y, &d) && d >= 1 && isProj(x, &i, h) && h == g) {
        return false;
    }
    if (isSigFIR(t, V) && isProj(V[0], &i, h) && h == g && isZero(V[1])) {
        for (size_t k = 2; k < V.size(); k++) {
            if (readsNow(V[k], g, seen)) {
                return true;
            }
        }
        return false;
    }
    for (int k = 0; k < t->arity(); k++) {
        if (readsNow(t->branch(k), g, seen)) {
            return true;
        }
    }
    return false;
}

class Planner {
    std::map<Tree, TreeSet, treeorder>               fParents;  // node -> the nodes that read it
    std::unordered_set<Tree>                         fCone;     // the cone of the memory decisions
    std::map<Tree, std::pair<Tree, int>, treeorder>  fDefCell;  // a cell of a group's definitions -> (group, index)

   public:
    explicit Planner(Tree L) : fCone(decisionCone(L, /*discontinuities*/ false))
    {
        TreeSet           seen;
        std::vector<Tree> st{L};
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree id, body;
            if (isRec(t, id, body) && body) {
                fParents[body].insert(t);
                int j = 0;
                for (Tree l = body; isList(l); l = tl(l), j++) {
                    fDefCell.emplace(l, std::make_pair(t, j));
                }
                st.push_back(body);
                continue;
            }
            for (int k = 0; k < t->arity(); k++) {
                fParents[t->branch(k)].insert(t);
                st.push_back(t->branch(k));
            }
        }
    }

    /// every private node is read by private nodes or hosts only ; otherwise why says which.
    /// In an automaton (group), a private node without state of its own may be read outside :
    /// its reader computes it again from the automaton's arrays
    bool privateOnly(const TreeSet& priv, const TreeSet& hosts, std::string& why, Tree group = nullptr) const
    {
        std::map<Tree, bool, treeorder> memo;
        for (Tree n : priv) {
            auto it = fParents.find(n);
            if (it == fParents.end()) {
                continue;
            }
            for (Tree p : it->second) {
                if (!hosts.count(p) && !priv.count(p)) {
                    if (group != nullptr && stateless(n, group, priv, memo)) {
                        continue;
                    }
                    std::ostringstream os;
                    os << "a node of a member is read elsewhere (" << n->node() << "/" << n->arity() << " read by "
                       << (isList(p) ? "a list cell " : "") << p->node() << "/" << p->arity() << ")";
                    if (getenv("FAUST_FAM_MEMBERS")) {
                        int  pi, d;
                        Tree g, x, y;
                        if (isProj(n, &pi, g)) {
                            os << " proj" << pi << " of the group #" << g->serial();
                        }
                        if (isSigDelay(p, x, y)) {
                            os << ", delay " << (isSigInt(y, &d) ? std::to_string(d) : "variable") << ", reader #"
                               << p->serial() << " read by " << fParents.at(p).size() << " node(s)";
                            for (Tree q : fParents.at(p)) {
                                os << " " << q->node() << (priv.count(q) ? "(private)" : "");
                            }
                        }
                    }
                    why = os.str();
                    return false;
                }
            }
        }
        return true;
    }

    /// a private node with no state of its own : no group, no filter, no delay line but the
    /// automaton's (a constant delay of a projection of the group, a FIR on one) ; the nodes
    /// it reads outside the member are computed by the schedule
    static bool stateless(Tree t, Tree group, const TreeSet& priv, std::map<Tree, bool, treeorder>& memo)
    {
        if (!priv.count(t)) {
            return true;
        }
        if (auto it = memo.find(t); it != memo.end()) {
            return it->second;
        }
        bool r = true;
        int  i, d;
        Tree h, x, y, id, body;
        tvec V;
        if (isProj(t, &i, h)) {
            r = (h == group);
        } else if (isRec(t, id, body) || isSigIIR(t, V)) {
            r = false;
        } else if (isSigDelay(t, x, y)) {
            r = isSigInt(y, &d) && ((isProj(x, &i, h) && h == group) || d == 0) && stateless(x, group, priv, memo);
        } else if (isSigFIR(t, V)) {
            r = (V.size() == 2 || (isProj(V[0], &i, h) && h == group));
            for (size_t k = 0; r && k < V.size(); k++) {
                r = stateless(V[k], group, priv, memo);
            }
        } else {
            for (int k = 0; r && k < t->arity(); k++) {
                r = stateless(t->branch(k), group, priv, memo);
            }
        }
        return memo[t] = r;
    }

    /// The members aligned on a template : the first member, unless a leaf it shares between
    /// two positions is not shared by the others ; another template is tried only after such
    /// a collision, never after a shape mismatch. Fills the template, the slots, the commons
    /// and the private nodes of plan.
    bool align(const std::vector<Tree>& nodes, FamilyPlan& plan, std::string& why, FamShapes& S) const
    {
        std::vector<FamIso> isos(nodes.size());
        size_t              tj    = 0;
        bool                found = false;
        for (bool retry = true; tj < nodes.size() && retry && !found; tj += found ? 0 : 1) {
            Tree t0    = nodes[tj];
            bool first = true, ok = true;
            retry      = false;
            for (size_t m = 0; m < nodes.size() && ok; m++) {
                if (m == tj) {
                    continue;
                }
                isos[m]        = FamIso();
                isos[m].holes  = &S.holes;
                isos[m].shapes = &S;
                isos[m].topA   = t0;
                isos[m].topB   = nodes[m];
                if (!isos[m].iso(t0, nodes[m])) {
                    why   = isos[m].collided ? "a leaf the template shares is not shared by a member"
                                             : "a member is not isomorphic to the template";
                    ok    = false;
                    retry = isos[m].collided;
                } else if (first) {
                    plan.leaves  = isos[m].slotA;
                    plan.aleaves = isos[m].aslotA;
                    plan.commons = isos[m].commonA;
                    plan.priv    = isos[m].privA;
                    first        = false;
                } else if (isos[m].slotA != plan.leaves || isos[m].aslotA != plan.aleaves ||
                           isos[m].commonA != plan.commons) {
                    why = "the members do not line up on the same slots and commons";
                    ok  = false;
                }
            }
            if (ok) {
                found = true;
                continue;
            }
            plan.leaves.clear();
            plan.aleaves.clear();
            plan.commons.clear();
            plan.priv.clear();
        }
        if (!found) {
            return false;
        }
        plan.tmpl = nodes[tj];
        for (size_t m = 0; m < nodes.size(); m++) {
            if (m != tj) {
                plan.priv.insert(isos[m].privB.begin(), isos[m].privB.end());
            }
        }
        if (plan.leaves.empty() && plan.aleaves.empty()) {
            why = "the members differ by nothing";
            return false;
        }
        plan.members = nodes;
        for (size_t m = 0; m < nodes.size(); m++) {
            plan.slots.push_back(m == tj ? plan.leaves : isos[m].slotB);
            plan.aslots.push_back(m == tj ? plan.aleaves : isos[m].aslotB);
        }
        return true;
    }

    /// what the loop can write, the cone of the decisions, and the private nodes read only
    /// inside the family
    bool checkPlan(FamilyPlan& plan, const TreeSet& hostSet, std::string& why, Tree group) const
    {
        for (Tree t : plan.priv) {
            if (fCone.count(t)) {
                why = "a node of a member reaches a memory decision";
                return false;
            }
        }
        if (!privateOnly(plan.priv, hostSet, why, group)) {
            return false;
        }
        TreeSet slotSet(plan.leaves.begin(), plan.leaves.end()), seen, com = plan.commons;
        com.insert(plan.aleaves.begin(), plan.aleaves.end());
        famCulprit = nullptr;
        if (!famCheck(plan.tmpl, slotSet, com, seen)) {
            std::ostringstream os;
            os << "the template holds a node the family loop cannot generate (" << famCulprit->node() << "/"
               << famCulprit->arity() << (famReal(famCulprit) ? "" : ", not real") << ")";
            why = os.str();
            return false;
        }
        return true;
    }

    /// A shape class as a family : the members aligned on a template, their hosts the sums
    /// they feed, the members grouped by host ; or, when the members are definitions of one
    /// recursive group, an automaton
    bool planClass(const std::vector<Tree>& cls, FamilyPlan& plan, std::string& why, FamShapes& S, Tree root) const
    {
        // a delay of zero has the shape of its signal : the member is the delay, the node a
        // sum reads, and the signal under it a node of the member
        std::vector<Tree> nodes0;
        {
            TreeSet under;
            for (Tree t : cls) {
                Tree x, y;
                if (isSigDelay(t, x, y) && isZero(y)) {
                    under.insert(x);
                }
            }
            for (Tree t : cls) {
                if (!under.count(t)) {
                    nodes0.push_back(t);
                }
            }
        }
        if (nodes0.size() < 4) {
            why = "fewer than 4 members";
            return false;
        }
        if (Tree group = automatonGroup(nodes0); group != nullptr) {
            return planAutomaton(nodes0, group, plan, why, S, root);
        }
        std::map<Tree, int, treeorder> hostIndex;
        std::vector<Tree>              hosts;
        std::vector<int>               memberHost;
        for (Tree m : nodes0) {
            if (fCone.count(m)) {
                why = "a member reaches a memory decision";
                return false;
            }
            auto it = fParents.find(m);
            if (it == fParents.end()) {
                why = "a member read by nothing";
                return false;
            }
            // the member's own delayed reads (inside its recursion) are not readers ; a read
            // of that delay from outside is a private node read elsewhere, refused below
            std::vector<Tree> readers;
            for (Tree r : it->second) {
                Tree x, y;
                int  d;
                if (isSigDelay(r, x, y) && x == m && isSigInt(y, &d) && d >= 1) {
                    continue;
                }
                readers.push_back(r);
            }
            if (readers.size() != 1) {
                why = "a member read by several nodes";
                return false;
            }
            Tree h = readers[0];
            if (!isSigSum(h) || fCone.count(h)) {
                std::ostringstream os;
                os << "a member read by something else than a sum outside the decisions ("
                   << (fCone.count(h) ? "in the cone : " : "") << (isList(h) ? "a list cell " : "") << h->node() << "/"
                   << h->arity() << ")";
                why = os.str();
                return false;
            }
            auto hi = hostIndex.find(h);
            if (hi == hostIndex.end()) {
                hi = hostIndex.emplace(h, int(hosts.size())).first;
                hosts.push_back(h);
            }
            memberHost.push_back(hi->second);
        }
        // members grouped by host, hosts in the order met
        std::vector<int> order(nodes0.size());
        for (size_t i = 0; i < order.size(); i++) {
            order[i] = int(i);
        }
        std::stable_sort(order.begin(), order.end(), [&](int a, int b) { return memberHost[a] < memberHost[b]; });
        std::vector<Tree> nodes;
        std::vector<int>  mh;
        for (int i : order) {
            nodes.push_back(nodes0[i]);
            mh.push_back(memberHost[i]);
        }
        if (!famReal(nodes[0])) {
            why = "not real";
            return false;
        }
        plan = FamilyPlan();
        if (!align(nodes, plan, why, S)) {
            return false;
        }
        TreeSet hostSet(hosts.begin(), hosts.end());
        if (!checkPlan(plan, hostSet, why, nullptr)) {
            return false;
        }
        // a member fed, through an audio slot, by another member of the class : the loop
        // reads its input arrays before its first iteration
        {
            TreeSet           memberSet(nodes.begin(), nodes.end()), seen;
            std::vector<Tree> st;
            for (auto& v : plan.aslots) {
                st.insert(st.end(), v.begin(), v.end());
            }
            while (!st.empty()) {
                Tree t = st.back();
                st.pop_back();
                if (!seen.insert(t).second) {
                    continue;
                }
                if (memberSet.count(t)) {
                    why = "a member is fed by another member of the class";
                    return false;
                }
                Tree id, body;
                if (isRec(t, id, body)) {
                    if (body) {
                        st.push_back(body);
                    }
                    continue;
                }
                for (int k = 0; k < t->arity(); k++) {
                    st.push_back(t->branch(k));
                }
            }
        }
        plan.hosts      = hosts;
        plan.memberHost = mh;
        return true;
    }

    /// the group whose definitions the members all are, each read by its cell of the list of
    /// definitions only ; nullptr otherwise
    Tree automatonGroup(const std::vector<Tree>& nodes) const
    {
        Tree group = nullptr;
        for (Tree m : nodes) {
            auto it = fParents.find(m);
            if (it == fParents.end() || it->second.size() != 1) {
                return nullptr;
            }
            Tree l  = *it->second.begin();
            auto dc = fDefCell.find(l);
            if (dc == fDefCell.end() || hd(l) != m || (group != nullptr && dc->second.first != group)) {
                return nullptr;
            }
            group = dc->second.first;
        }
        return group;
    }

    /// The automaton : the members are contiguous definitions of the group, its cells ; each
    /// audio slot reads, in every cell, the projection at the same offset from the cell, or no
    /// projection of the group ; no definition reads the group at the current step
    bool planAutomaton(const std::vector<Tree>& nodes0, Tree group, FamilyPlan& plan, std::string& why, FamShapes& S,
                       Tree root) const
    {
        Tree W, defs;
        isRec(group, W, defs);
        std::vector<std::pair<int, Tree>> cells;
        TreeSet                           listCells;
        for (Tree m : nodes0) {
            Tree l = *fParents.at(m).begin();
            cells.push_back({fDefCell.at(l).second, m});
            listCells.insert(l);
        }
        std::sort(cells.begin(), cells.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
        const int N = len(defs), P = int(cells.size());
        if (P < kAutomatonMinCells) {
            why = "an automaton of fewer than " + std::to_string(kAutomatonMinCells) + " cells";
            return false;
        }
        for (int c = 1; c < P; c++) {
            if (cells[c].first != cells[0].first + c) {
                why = "an automaton whose cells are not contiguous definitions";
                return false;
            }
        }
        if (2 * P < N) {
            why = "an automaton whose cells are fewer than half of the group's definitions";
            return false;
        }
        std::vector<Tree> nodes;
        for (auto& c : cells) {
            nodes.push_back(c.second);
        }
        for (Tree l = defs; isList(l); l = tl(l)) {
            if (!famReal(hd(l))) {
                why = "a definition of the automaton's group is not real";  // its arrays are real
                return false;
            }
        }
        for (Tree m : nodes) {
            if (fCone.count(m)) {
                why = "a member reaches a memory decision";
                return false;
            }
        }
        plan = FamilyPlan();
        if (!align(nodes, plan, why, S)) {
            return false;
        }
        const int base = cells[0].first;
        // the neighbourhood : per audio slot, the projection at a constant offset from the cell
        for (size_t k = 0; k < plan.aleaves.size(); k++) {
            int  off = INT_MIN, i;
            bool any = false, all = true;
            for (int c = 0; c < P; c++) {
                Tree h;
                if (isProj(plan.aslots[c][k], &i, h) && h == group) {
                    any = true;
                    if (c == 0) {
                        off = i - base;
                    } else if (i - (base + c) != off) {
                        why = "an automaton whose neighbourhood is not at a constant offset";
                        return false;
                    }
                } else {
                    all = false;
                }
            }
            if (any && !all) {
                why = "an audio slot of the automaton reads the group in some cells only";
                return false;
            }
            plan.neighbour.push_back(any ? off : INT_MIN);
        }
        // the generations : every definition reads the group in the past only, and so do the
        // audio slots computed before the loop and the commons
        {
            TreeSet seen;
            for (Tree l = defs; isList(l); l = tl(l)) {
                if (readsNow(hd(l), group, seen)) {
                    why = "a definition of the automaton's group reads the group at the current step";
                    return false;
                }
            }
            for (size_t k = 0; k < plan.aleaves.size(); k++) {
                for (int c = 0; c < P && plan.neighbour[k] == INT_MIN; c++) {
                    if (readsNow(plan.aslots[c][k], group, seen)) {
                        why = "an input of the automaton reads the group at the current step";
                        return false;
                    }
                }
            }
        }
        // the readers of the group, everywhere : a delay of a projection is a constant
        {
            TreeSet           seen;
            std::vector<Tree> st{root};
            while (!st.empty()) {
                Tree t = st.back();
                st.pop_back();
                if (!seen.insert(t).second) {
                    continue;
                }
                Tree x, y, h, id, body;
                int  i, d;
                if (isSigDelay(t, x, y) && isProj(x, &i, h) && h == group) {
                    if (!isSigInt(y, &d)) {
                        why = "a projection of the automaton's group read at a variable delay";
                        return false;
                    }
                    plan.depth = std::max(plan.depth, d);
                }
                tvec V;
                if (isSigFIR(t, V) && isProj(V[0], &i, h) && h == group) {
                    plan.depth = std::max(plan.depth, int(V.size()) - 2);
                }
                if (isRec(t, id, body)) {
                    if (body) {
                        st.push_back(body);
                    }
                    continue;
                }
                for (int k = 0; k < t->arity(); k++) {
                    st.push_back(t->branch(k));
                }
            }
        }
        if (!checkPlan(plan, listCells, why, group)) {
            return false;
        }
        plan.group = group;
        plan.base  = base;
        plan.size  = N;
        plan.memberHost.assign(P, 0);
        return true;
    }
};

}  // namespace

std::vector<FamilyPlan> findFamilies(Tree L)
{
    const bool trace = famTrace();
    FamShapes  S;
    FamClasses C;
    C.collectWithHoles(L, S);
    std::vector<std::pair<Shape, std::vector<Tree>>> classes;
    for (auto& kv : C.members) {
        if (kv.second.size() >= 4) {
            classes.push_back(kv);
        }
    }
    std::sort(classes.begin(), classes.end(), [&S](const auto& a, const auto& b) {
        if (a.second.size() != b.second.size()) {
            return a.second.size() > b.second.size();
        }
        int sa = S.size(a.first), sb = S.size(b.first);
        return sa != sb ? sa > sb : a.second[0]->serial() < b.second[0]->serial();
    });
    Planner planner(L);
    struct Cand {
        FamilyPlan plan;
        int        coverage;
    };
    std::vector<Cand>       cands;
    std::vector<FamilyPlan> stateless;  // the families without a state of their own
    for (auto& kv : classes) {
        FamilyPlan  plan;
        std::string why;
        if (!planner.planClass(kv.second, plan, why, S, L)) {
            if (trace) {
                std::cerr << "fam refused : class of " << kv.second.size() << " (" << S.size(kv.first)
                          << " nodes) : " << why << std::endl;
                if (getenv("FAUST_FAM_MEMBERS")) {
                    for (Tree m : kv.second) {
                        std::cerr << "      member #" << m->serial() << " " << m->node() << " " << ppsig(m, 40) << std::endl;
                    }
                }
            }
            continue;
        }
        // every member must carry a state : a family without one is per-sample arithmetic,
        // which the C++ compiler already packs as straight-line code, unless it reads the
        // cells of an automaton (below) ; an automaton's state is its group
        const int P = int(plan.members.size());
        if (plan.group == nullptr && famStates(plan.priv, P) < 1) {
            stateless.push_back(plan);
            continue;
        }
        int coverage = famWork(plan.priv, 1);
        for (Tree h : plan.hosts) {
            tvec ops;
            isSigSum(h, ops);
            coverage += std::max(1, int(ops.size()) - 1);
        }
        cands.push_back({plan, coverage});
    }
    // the most work first ; a candidate whose members are inside an accepted family is
    // compiled by its loop, one whose members are the hosts of a wider candidate, or hold
    // an accepted family, steps aside
    std::sort(cands.begin(), cands.end(), [](const Cand& a, const Cand& b) {
        if (a.coverage != b.coverage) {
            return a.coverage > b.coverage;
        }
        return a.plan.members.size() != b.plan.members.size() ? a.plan.members.size() > b.plan.members.size()
                                                              : a.plan.members[0]->serial() < b.plan.members[0]->serial();
    });
    std::vector<FamilyPlan> out;
    TreeSet                 covered;  // the private nodes and hosts of the accepted families
    for (size_t i = 0; i < cands.size(); i++) {
        FamilyPlan& plan   = cands[i].plan;
        bool        inside = false;
        for (Tree m : plan.members) {
            inside = inside || covered.count(m);
        }
        for (Tree h : plan.hosts) {
            inside = inside || covered.count(h);
        }
        bool aside = false;
        for (size_t j = i + 1; j < cands.size() && !aside; j++) {
            if (cands[j].plan.members.size() <= plan.members.size()) {
                continue;
            }
            TreeSet hostsOfJ(cands[j].plan.hosts.begin(), cands[j].plan.hosts.end());
            bool    hosts = true;
            for (Tree m : plan.members) {
                hosts = hosts && hostsOfJ.count(m);
            }
            aside = hosts;
        }
        bool swallows = false;
        for (Tree t : plan.priv) {
            swallows = swallows || covered.count(t);
        }
        if (inside || aside || swallows) {
            if (trace) {
                std::cerr << "fam : a family of " << plan.members.size() << " steps aside ("
                          << (inside ? "inside an accepted one" : aside ? "its members are the hosts of a wider one"
                                                                         : "it holds an accepted one")
                          << ")" << std::endl;
            }
            continue;
        }
        covered.insert(plan.priv.begin(), plan.priv.end());
        covered.insert(plan.hosts.begin(), plan.hosts.end());
        if (trace) {
            std::cerr << "fam planned : " << plan.members.size() << " members, "
                      << (plan.group ? "an automaton over " + std::to_string(plan.size) + " definitions, depth " +
                                           std::to_string(plan.depth)
                                     : std::to_string(plan.hosts.size()) + " host(s)")
                      << ", " << plan.leaves.size() << " slots, " << plan.aleaves.size() << " audio slots, "
                      << plan.commons.size() << " commons, " << plan.priv.size() << " private nodes, "
                      << cands[i].coverage << " operations" << std::endl;
        }
        out.push_back(plan);
    }
    // a family without state whose members each read, at the current step, a cell of an
    // accepted automaton : accumulated in the automaton's loop
    const size_t automata = out.size();
    for (FamilyPlan& plan : stateless) {
        const int P     = int(plan.members.size());
        bool      fused = false;
        for (size_t a = 0; a < automata && !fused; a++) {
            const Tree group = out[a].group;
            if (group == nullptr) {
                continue;
            }
            for (size_t s = 0; s < plan.aleaves.size() && !fused; s++) {
                std::vector<int> cell;
                std::set<int>    distinct;
                for (int m = 0; m < P; m++) {
                    int  i;
                    Tree h;
                    if (isProj(plan.aslots[m][s], &i, h) && h == group && distinct.insert(i).second) {
                        cell.push_back(i);
                    }
                }
                if (int(cell.size()) != P) {
                    continue;
                }
                // what the members read besides the cell is computed before the automaton
                bool    ok = true;
                TreeSet seen;
                for (Tree t : plan.commons) {
                    ok = ok && !readsNow(t, group, seen);
                }
                for (size_t k = 0; k < plan.aleaves.size(); k++) {
                    for (int m = 0; k != s && m < P; m++) {
                        ok = ok && !readsNow(plan.aslots[m][k], group, seen);
                    }
                }
                for (Tree t : plan.priv) {
                    ok = ok && !covered.count(t);
                }
                for (Tree h : plan.hosts) {
                    ok = ok && !covered.count(h);
                }
                // one host, and a member for every cell of the loop : the members ordered by
                // their cells, the loop's cells contiguous among them
                std::set<int> cells(cell.begin(), cell.end());
                for (int k = out[a].base; ok && k < out[a].base + int(out[a].members.size()); k++) {
                    ok = cells.count(k) > 0;
                }
                if (!ok || plan.hosts.size() != 1) {
                    continue;
                }
                {
                    std::vector<int> order(P);
                    for (int m = 0; m < P; m++) {
                        order[m] = m;
                    }
                    std::sort(order.begin(), order.end(), [&](int x, int y) { return cell[x] < cell[y]; });
                    FamilyPlan sorted = plan;
                    for (int m = 0; m < P; m++) {
                        sorted.members[m] = plan.members[order[m]];
                        sorted.slots[m]   = plan.slots[order[m]];
                        sorted.aslots[m]  = plan.aslots[order[m]];
                    }
                    std::vector<int> sortedCell(P);
                    for (int m = 0; m < P; m++) {
                        sortedCell[m] = cell[order[m]];
                    }
                    plan = sorted;
                    cell = sortedCell;
                }
                plan.automaton = int(a);
                plan.cellSlot  = int(s);
                plan.cell      = cell;
                for (size_t k = 0; k < plan.leaves.size(); k++) {
                    int off = INT_MIN, v;
                    for (int m = 0; m < P; m++) {
                        if (!isSigInt(plan.slots[m][k], &v) || (m > 0 && v - cell[m] != off)) {
                            off = INT_MIN;
                            break;
                        }
                        off = v - cell[m];
                    }
                    plan.cellOffset.push_back(off);
                }
                fused = true;
            }
        }
        if (!fused) {
            if (trace) {
                std::cerr << "fam refused : family of " << P << " : no state per member" << std::endl;
            }
            continue;
        }
        covered.insert(plan.priv.begin(), plan.priv.end());
        covered.insert(plan.hosts.begin(), plan.hosts.end());
        if (trace) {
            std::cerr << "fam planned : " << P << " members, " << plan.hosts.size()
                      << " host(s), in the loop of the automaton " << plan.automaton << ", " << plan.leaves.size()
                      << " slots, " << plan.aleaves.size() << " audio slots, " << plan.commons.size() << " commons"
                      << std::endl;
        }
        out.push_back(plan);
    }
    return out;
}

TreeSet familyFrozenSet(Tree L, const std::vector<FamilyPlan>& families)
{
    TreeSet frozen;
    for (const FamilyPlan& f : families) {
        frozen.insert(f.hosts.begin(), f.hosts.end());
        if (f.group != nullptr) {
            // an automaton's cells are in its group's body : the whole group is frozen
            frozen.insert(f.members.begin(), f.members.end());
        }
    }
    // what a family reads from outside is frozen with it : the loop reads the node of the
    // tree, and a node the rewrites had rebuilt would be computed twice
    auto leaf = [&](Tree t) {
        if (t->getType() != nullptr && !isNum(t)) {
            frozen.insert(t);
        }
    };
    for (const FamilyPlan& f : families) {
        for (auto& v : f.slots) {
            for (Tree t : v) {
                leaf(t);
            }
        }
        for (auto& v : f.aslots) {
            for (Tree t : v) {
                leaf(t);
            }
        }
        for (Tree t : f.commons) {
            leaf(t);
        }
    }
    // A frozen node inside the body of a recursive group freezes the whole group : a rewrite
    // gives every group it rebuilds a fresh variable, and a frozen subtree kept as it is
    // would still name the old one. The group is frozen by its projections, and a projection
    // inside another group freezes that group too, to the fixpoint.
    std::map<Tree, Tree, treeorder> enclosing;  // node -> the innermost group whose body holds it
    {
        TreeSet                         seen;
        std::function<void(Tree, Tree)> walk = [&](Tree t, Tree g) {
            if (!seen.insert(t).second) {
                return;
            }
            if (g) {
                enclosing.emplace(t, g);
            }
            Tree id, body;
            if (isRec(t, id, body)) {
                if (body) {
                    walk(body, t);
                }
                return;
            }
            for (int k = 0; k < t->arity(); k++) {
                walk(t->branch(k), g);
            }
        };
        walk(L, nullptr);
    }
    TreeSet groups;
    for (bool more = true; more;) {
        more = false;
        for (Tree t : frozen) {
            auto it = enclosing.find(t);
            if (it != enclosing.end() && groups.insert(it->second).second) {
                more = true;
            }
        }
        TreeSet           seen;
        std::vector<Tree> st{L};
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            int  i;
            Tree g, id, body;
            if (isProj(t, &i, g) && groups.count(g)) {
                if (frozen.insert(t).second) {
                    more = true;
                }
                continue;
            }
            if (isRec(t, id, body)) {
                if (body) {
                    st.push_back(body);
                }
                continue;
            }
            for (int k = 0; k < t->arity(); k++) {
                st.push_back(t->branch(k));
            }
        }
    }
    // a node inside a frozen group is frozen with it : it needs no leaf of its own
    for (auto it = frozen.begin(); it != frozen.end();) {
        int  i;
        Tree g;
        auto e = enclosing.find(*it);
        it     = (e != enclosing.end() && groups.count(e->second) && !(isProj(*it, &i, g) && groups.count(g)))
                     ? frozen.erase(it)
                     : std::next(it);
    }
    return frozen;
}

namespace {

using Rebuild = std::function<Tree(Tree)>;

/// L with the nodes of sub replaced, outside the bodies of the groups : the nodes above a
/// replaced one are rebuilt with the type of the node they rebuild ; sub may rebuild the
/// operands of its replacement
Tree substituteOutsideGroups(Tree L, const std::function<Tree(Tree, const Rebuild&)>& sub,
                             std::unordered_map<Tree, Tree>& image)
{
    Rebuild rebuild = [&](Tree t) -> Tree {
        if (auto it = image.find(t); it != image.end()) {
            return it->second;
        }
        Tree r = sub(t, rebuild);
        Tree id, body;
        if (r == nullptr) {
            r = t;
            if (!isRec(t, id, body) && t->arity() > 0) {
                tvec br;
                bool changed = false;
                for (int k = 0; k < t->arity(); k++) {
                    br.push_back(rebuild(t->branch(k)));
                    changed = changed || br.back() != t->branch(k);
                }
                if (changed) {
                    r = tree(t->node(), br);
                    if (r->getType() == nullptr && t->getType() != nullptr) {
                        setSigType(r, getSigType(t));
                    }
                }
            }
        }
        image[t] = r;
        return r;
    };
    return rebuild(L);
}

}  // namespace

Tree freezeFamilies(Tree L, const TreeSet& frozen, std::unordered_map<Tree, Tree>& back,
                    std::unordered_map<Tree, Tree>& image)
{
    int  n   = 0;
    auto sub = [&](Tree t, const Rebuild&) -> Tree {
        if (!frozen.count(t)) {
            return nullptr;
        }
        // an opaque leaf, typed like the node : an input no program has
        Tree leaf = sigInput(1000000 + n++);
        setSigType(leaf, getSigType(t));
        back[leaf] = t;
        return leaf;
    };
    return substituteOutsideGroups(L, sub, image);
}

Tree thawFamilies(Tree L, const std::unordered_map<Tree, Tree>& back, std::unordered_map<Tree, Tree>& image)
{
    auto sub = [&](Tree t, const Rebuild&) -> Tree {
        auto it = back.find(t);
        return it == back.end() ? nullptr : it->second;
    };
    return substituteOutsideGroups(L, sub, image);
}

namespace {

/// the terms of a sum written flat : an operand that is a sum, or a product by exactly 1.0,
/// read by nothing else, gives its own terms, recursively, and is absorbed ; the order is
/// the order met
void flatTerms(Tree t, const std::map<Tree, int, treeorder>& reads, tvec& terms, TreeSet& absorbed)
{
    auto single = [&](Tree x) {
        auto it = reads.find(x);
        return it != reads.end() && it->second == 1;
    };
    tvec ops;
    isSigSum(t, ops);
    for (Tree o : ops) {
        tvec   fs;
        double v;
        Tree   x = o;
        while (single(x) && isSigProd(x, fs) && fs.size() == 2) {
            Tree y = (isSigReal(fs[0], &v) && v == 1.0) ? fs[1] : (isSigReal(fs[1], &v) && v == 1.0) ? fs[0] : nullptr;
            if (y == nullptr) {
                break;
            }
            absorbed.insert(x);
            x = y;
        }
        if (single(x) && isSigSum(x)) {
            absorbed.insert(x);
            flatTerms(x, reads, terms, absorbed);
        } else {
            terms.push_back(x);
        }
    }
}

}  // namespace

Tree flattenFamilyHosts(Tree L, std::vector<FamilyPlan>& families, std::unordered_map<Tree, Tree>& image)
{
    // the number of reads of every node (a node read twice by one parent counts twice), and
    // the sums outside the groups whose flat form differs : the candidates
    std::map<Tree, int, treeorder> reads;
    TreeSet                        outside;
    {
        TreeSet           seen;
        std::vector<Tree> st{L};
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree id, body;
            if (isRec(t, id, body)) {
                if (body) {
                    reads[body]++;
                    st.push_back(body);
                }
                continue;
            }
            for (int k = 0; k < t->arity(); k++) {
                reads[t->branch(k)]++;
                st.push_back(t->branch(k));
            }
        }
        std::vector<Tree> st2{L};
        while (!st2.empty()) {
            Tree t = st2.back();
            st2.pop_back();
            Tree id, body;
            if (!outside.insert(t).second || isRec(t, id, body)) {
                continue;
            }
            for (int k = 0; k < t->arity(); k++) {
                st2.push_back(t->branch(k));
            }
        }
    }
    std::map<Tree, tvec, treeorder> flat;
    TreeSet                         absorbed;  // the sub-sums and unit products of the candidates
    for (Tree t : outside) {
        tvec    terms;
        TreeSet abs;
        if (isSigSum(t) && t->getType() != nullptr) {
            flatTerms(t, reads, terms, abs);
            if (!abs.empty()) {
                flat[t] = terms;
                absorbed.insert(abs.begin(), abs.end());
            }
        }
    }
    // the candidates kept are the sums whose flat form hosts a family, to the fixpoint : a
    // sum written flat that hosts none would only change its rounding
    TreeSet keep;
    for (auto& kv : flat) {
        if (!absorbed.count(kv.first)) {
            keep.insert(kv.first);
        }
    }
    while (!keep.empty()) {
        std::unordered_map<Tree, Tree> img;
        auto                           sub = [&](Tree t, const Rebuild& rebuild) -> Tree {
            if (!keep.count(t)) {
                return nullptr;
            }
            tvec ops;
            for (Tree o : flat.at(t)) {
                Tree r = rebuild(o);
                ops.push_back(r);
            }
            Tree s = sigSum(ops);
            if (s->getType() == nullptr) {
                setSigType(s, getSigType(t));
            }
            return s;
        };
        Tree                    Lk   = substituteOutsideGroups(L, sub, img);
        std::vector<FamilyPlan> fams = findFamilies(Lk);
        TreeSet                 hosts;
        for (const FamilyPlan& f : fams) {
            hosts.insert(f.hosts.begin(), f.hosts.end());
        }
        TreeSet next;
        for (Tree t : keep) {
            if (auto it = img.find(t); it != img.end() && hosts.count(it->second)) {
                next.insert(t);
            }
        }
        if (next == keep) {
            if (famTrace()) {
                std::cerr << "fam : " << keep.size() << " host(s) written flat" << std::endl;
            }
            families = fams;
            image    = img;
            return Lk;
        }
        keep = next;
    }
    families = findFamilies(L);
    return L;
}
