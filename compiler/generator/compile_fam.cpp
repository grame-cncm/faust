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

// The sum families (-fam, LES-FAMILLES-DE-LA-FORME-DE-CALCUL) : the ScalarCompiler methods
// that plan, schedule and emit the families found by families.hh. The declarations stay in
// compile_scal.hh.

#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>

#include "compile_scal.hh"
#include "computeSignals.hh"
#include "floats.hh"
#include "mixForm.hh"
#include "sumLayout.hh"
#include "global.hh"
#include "ppsig.hh"
#include "xtendedCodegen.hh"

namespace {

bool famTrace()
{
    static const bool trace = getenv("FAUST_FAM_TRACE") != nullptr;
    return trace;
}

std::string famPrint(Tree t, int n)
{
    std::ostringstream os;
    os << ppsig(t, n);
    return os.str();
}

}  // namespace

/// The loop of a family as it is written : the template's nodes spelled once, its slots
/// read in the family's tables and arrays, its states in arrays of P cells
struct ScalarCompiler::FamCtx {
    int                                              id = 0, P = 0, locals = 0;
    std::string                                      ty;  // the real type of the members
    const FamilyPlan*                                plan = nullptr;
    std::map<Tree, int, treeorder>                   slotIndex;  // template leaf -> coefficient slot
    std::vector<bool>                                uniform;    // the slot is the same tree in every member
    std::set<int>                                    usedSlots;
    std::map<Tree, int, treeorder>                   aslotIndex;  // template leaf -> audio slot
    std::vector<bool>                                auniform;
    std::set<int>                                    usedASlots;
    std::map<Tree, int, treeorder>                   uses;  // parents inside the template
    std::map<Tree, std::string, treeorder>           val;
    std::vector<std::string>                         body;
    std::map<Tree, int, treeorder>                   groupState;  // 1 computing, 2 done
    std::map<Tree, std::map<int, std::string>, treeorder> projVal;
    std::map<std::string, int>                       need;        // state -> deepest past sample read
    std::map<std::string, std::string>               stateValue;  // state -> its value of the sample
    std::map<Tree, int, treeorder>                   sid;
    bool                                             failed = false;
    std::string                                      reason;
    std::string                                      idx = "c";  // the member's index in the tables and arrays
    // the automaton : its state arrays, and per audio slot the offset of the projection read
    std::string                                      states;
    std::vector<int>                                 neighbour;
    // a family accumulated in an automaton's loop : the audio slot of the cell, its value
    int                                              cellSlot = -1;
    std::string                                      cellValue;

    std::string local() { return subst("fFam$0L$1", T(id), T(locals++)); }
    std::string stateKey(Tree node, int j)
    {
        auto it = sid.find(node);
        int  n  = (it == sid.end()) ? (sid[node] = int(sid.size())) : it->second;
        return subst("fFam$0S$1_$2", T(id), T(n), T(j));
    }
    void fail(const std::string& why)
    {
        if (!failed) {
            failed = true;
            reason = why;
        }
    }
};

void ScalarCompiler::planFamilies()
{
    fFamilies.clear();
    fFamHost.clear();
    fFamGroup.clear();
    fFamPrivate.clear();
    if (!gGlobal->gFamilies || gGlobal->gLoopSplit || fFamRoot == nullptr) {
        return;
    }
    std::map<int, int> idOf;  // the index of a family found -> its family
    int                index = -1;
    for (FamilyPlan& p : findFamilies(fFamRoot)) {
        index++;
        bool conditional = false;
        for (Tree t : p.priv) {
            conditional = conditional || !getConditionCode(t).empty();
        }
        for (Tree h : p.hosts) {
            conditional = conditional || !getConditionCode(h).empty();
        }
        if (Tree W, defs; p.group != nullptr && isRec(p.group, W, defs)) {
            for (Tree l = defs; isList(l); l = tl(l)) {
                conditional = conditional || !getConditionCode(hd(l)).empty();
            }
        }
        if (conditional) {
            if (famTrace()) {
                std::cerr << "fam refused : family of " << p.members.size() << " : conditional" << std::endl;
            }
            continue;
        }
        if (p.automaton >= 0) {
            auto it = idOf.find(p.automaton);
            if (it == idOf.end()) {
                continue;  // its automaton was refused
            }
            p.automaton = it->second;
        }
        Family f;
        f.plan = p;
        f.id   = int(fFamilies.size());
        idOf[index] = f.id;
        for (Tree h : p.hosts) {
            fFamHost[h] = f.id;
        }
        if (p.group != nullptr) {
            fFamGroup[p.group] = f.id;
        }
        if (p.automaton >= 0) {
            fFamilies[p.automaton].fused.push_back(f.id);
        }
        fFamPrivate.insert(p.priv.begin(), p.priv.end());
        fFamilies.push_back(f);
    }
}

/// the audio nodes a family reads from outside : its commons and audio slots ; for an
/// automaton or a family in its loop, not the projections of the automaton's group
static TreeSet famInputs(const FamilyPlan& p, Tree group = nullptr)
{
    TreeSet inputs(p.commons.begin(), p.commons.end());
    for (auto& v : p.aslots) {
        for (Tree t : v) {
            int  i;
            Tree h;
            if (group == nullptr || !(isProj(t, &i, h) && h == group)) {
                inputs.insert(t);
            }
        }
    }
    return inputs;
}

/// the projections of a group among the nodes, in serial order
template <typename Nodes>
static std::vector<Tree> famProjections(const Nodes& nodes, Tree group)
{
    std::vector<Tree> r;
    for (Tree t : nodes) {
        int  i;
        Tree h;
        if (isProj(t, &i, h) && h == group) {
            r.push_back(t);
        }
    }
    std::sort(r.begin(), r.end(), [](Tree a, Tree b) { return a->serial() < b->serial(); });
    return r;
}

void ScalarCompiler::famScheduleEdges(digraph<Tree>& G)
{
    // the loop of a family is emitted at its first host : every host depends on every
    // input of every member, unless the edge would close a cycle (an input reading a host
    // through a delay) ; checkFamilyOrder then dismantles the family
    auto reaches = [&G](Tree from, Tree to) -> bool {
        TreeSet           seen;
        std::vector<Tree> work{from};
        while (!work.empty()) {
            Tree n = work.back();
            work.pop_back();
            if (n == to) {
                return true;
            }
            if (!seen.insert(n).second) {
                continue;
            }
            for (const auto& c : G.destinations(n)) {
                work.push_back(c.first);
            }
        }
        return false;
    };
    for (Family& f : fFamilies) {
        if (f.plan.group != nullptr) {
            // the automaton is emitted at the first read of its current generation : every
            // projection of the group depends on every definition (none reads the group at
            // the current step, the plan checked it) and on the inputs of the families in
            // its loop
            Tree W, defs;
            isRec(f.plan.group, W, defs);
            TreeSet fusedInputs;
            for (int k : f.fused) {
                const TreeSet in = famInputs(fFamilies[k].plan, f.plan.group);
                fusedInputs.insert(in.begin(), in.end());
            }
            for (Tree p : famProjections(G.nodes(), f.plan.group)) {
                for (Tree l = defs; isList(l); l = tl(l)) {
                    if (hd(l) != p && G.nodes().count(hd(l))) {
                        G.add(p, hd(l), 0);
                    }
                }
                for (Tree i : fusedInputs) {
                    int k;
                    if (isSigInput(i, &k) || !G.nodes().count(i) || i == p || reaches(i, p)) {
                        continue;
                    }
                    G.add(p, i, 0);
                }
            }
            continue;
        }
        const TreeSet inputs = famInputs(f.plan);
        for (Tree h : f.plan.hosts) {
            if (!G.nodes().count(h)) {
                continue;
            }
            for (Tree i : inputs) {
                int k;
                if (isSigInput(i, &k) || !G.nodes().count(i) || i == h || reaches(i, h)) {
                    continue;
                }
                G.add(h, i, 0);
            }
        }
    }
}

void ScalarCompiler::dismantleFamily(Family& f)
{
    for (Tree t : f.plan.priv) {
        fFamPrivate.erase(t);
    }
    for (Tree h : f.plan.hosts) {
        fFamHost.erase(h);
    }
    if (f.plan.group != nullptr) {
        fFamGroup.erase(f.plan.group);
    }
    f.dismantled = true;
    for (int k : f.fused) {
        if (!fFamilies[k].dismantled) {
            dismantleFamily(fFamilies[k]);
        }
    }
}

void ScalarCompiler::checkFamilyOrder()
{
    // every input of a family is scheduled before the family : its first host, or for an
    // automaton the first projection of its group
    auto latestOf = [&](const TreeSet& inputs, int& latest, Tree& culprit) {
        for (Tree t : inputs) {
            int k;
            if (isSigInput(t, &k) || getCertifiedSigType(t)->variability() < kSamp) {
                continue;
            }
            if (auto it = fSchedPos.find(t); it != fSchedPos.end() && it->second > latest) {
                latest  = it->second;
                culprit = t;
            }
        }
    };
    for (Family& f : fFamilies) {
        if (f.dismantled) {
            continue;
        }
        int     first = INT_MAX, latest = -1;
        Tree    culprit = nullptr;
        TreeSet inputs;
        if (f.plan.group != nullptr) {
            for (auto& kv : fSchedPos) {
                int  i;
                Tree h;
                if (isProj(kv.first, &i, h) && h == f.plan.group) {
                    first = std::min(first, kv.second);
                }
            }
            inputs = famInputs(f.plan, f.plan.group);
            Tree W, defs;
            isRec(f.plan.group, W, defs);
            for (Tree l = defs; isList(l); l = tl(l)) {
                if (!fFamPrivate.count(hd(l))) {
                    inputs.insert(hd(l));  // a border : computed by the schedule, read by the automaton
                }
            }
            for (int k : f.fused) {
                const TreeSet in = famInputs(fFamilies[k].plan, f.plan.group);
                inputs.insert(in.begin(), in.end());
            }
        } else {
            for (Tree h : f.plan.hosts) {
                if (auto it = fSchedPos.find(h); it != fSchedPos.end()) {
                    first = std::min(first, it->second);
                }
            }
            inputs = famInputs(f.plan);
        }
        latestOf(inputs, latest, culprit);
        if (first == INT_MAX || latest > first) {
            if (famTrace()) {
                std::cerr << "fam dismantled : family of " << f.plan.members.size() << ", "
                          << (first == INT_MAX ? std::string("no host scheduled")
                                               : "an input (" + famPrint(culprit, 40) + ") is scheduled after its first host")
                          << std::endl;
            }
            dismantleFamily(f);
        }
    }
}

/// the row of the automaton's arrays holding the generation d samples ago : the rows rotate
/// through the index fFam<id>R instead of being copied at every sample
static std::string famRow(const std::string& S, const std::string& d)
{
    return subst("$0[$1R[$2]]", S, S.substr(0, S.size() - 1), d);
}

std::string ScalarCompiler::famHist(FamCtx& g, Tree x, int k)
{
    if (g.failed) {
        return "0";
    }
    if (k == 0) {
        return famExpr(g, x);
    }
    if (auto it = g.aslotIndex.find(x); it != g.aslotIndex.end() && it->second < int(g.neighbour.size()) &&
                                        g.neighbour[it->second] != INT_MIN) {
        // the automaton's neighbourhood : the projection at its offset from the cell, read in
        // the group's arrays at the past sample k
        return subst("$0[cell + $1]", famRow(g.states, T(k)), T(g.neighbour[it->second]));
    }
    Tree x2, y;
    int  d;
    if (isSigDelay(x, x2, y) && isSigInt(y, &d)) {
        return famHist(g, x2, k + d);
    }
    tvec V;
    if (isSigIIR(x, V)) {
        famExpr(g, x);  // the state is updated this iteration
        const std::string key = g.stateKey(x, 0);
        g.need[key]           = std::max(g.need[key], k);
        return subst("$0_$1[c]", key, T(k));
    }
    int  i;
    Tree grp, W, defs;
    if (isProj(x, &i, grp)) {
        if (!isRec(grp, W, defs)) {
            g.fail("projection of a non recursive group");
            return "0";
        }
        if (g.groupState[grp] == 0) {
            famExpr(g, x);
        }
        const std::string key = g.stateKey(grp, i);
        g.need[key]           = std::max(g.need[key], k);
        return subst("$0_$1[c]", key, T(k));
    }
    g.fail("history of a node that is not a state");
    return "0";
}

std::string ScalarCompiler::famExpr(FamCtx& g, Tree t)
{
    if (g.failed) {
        return "0";
    }
    if (auto it = g.val.find(t); it != g.val.end()) {
        return it->second;
    }
    // a node read twice in the template gets a local
    auto keep = [&](const std::string& e) {
        if (g.uses[t] > 1) {
            const std::string l = g.local();
            g.body.push_back(subst("$0 $1 = $2;", g.ty, l, e));
            return g.val[t] = l;
        }
        return g.val[t] = e;
    };
    if (auto it = g.slotIndex.find(t); it != g.slotIndex.end()) {
        if (g.uniform[it->second]) {
            return g.val[t] = CS(t);
        }
        if (it->second < int(g.plan->cellOffset.size()) && g.plan->cellOffset[it->second] != INT_MIN) {
            // an integer that is the index of the member's cell, up to a constant : exact
            return g.val[t] = subst("(cell + $0)", T(g.plan->cellOffset[it->second]));
        }
        g.usedSlots.insert(it->second);
        return g.val[t] = subst("fFam$0T$1[$2]", T(g.id), T(it->second), g.idx);
    }
    if (g.plan->commons.count(t)) {
        return g.val[t] = CS(t);  // what the family reads from outside is the tree's node
    }
    if (auto it = g.aslotIndex.find(t); it != g.aslotIndex.end()) {
        if (it->second == g.cellSlot) {
            return g.val[t] = g.cellValue;  // the cell the member reads, at the current step
        }
        if (it->second < int(g.neighbour.size()) && g.neighbour[it->second] != INT_MIN) {
            g.fail("the automaton's group read at the current step");
            return "0";
        }
        if (g.auniform[it->second]) {
            return g.val[t] = CS(t);
        }
        g.usedASlots.insert(it->second);
        return g.val[t] = subst("fFam$0In$1[$2]", T(g.id), T(it->second), g.idx);
    }
    tvec V;
    if (isSigIIR(t, V)) {
        // IIR[X, C1, ..., Cn] : y = X + C1.y' + ... + Cn.y@n
        std::ostringstream oss;
        oss << "(" << famExpr(g, V[0]);
        for (size_t k = 1; k < V.size(); k++) {
            auto sl = g.slotIndex.find(V[k]);
            if (sl != g.slotIndex.end() && g.uniform[sl->second] && isZero(V[k])) {
                continue;
            }
            const std::string key = g.stateKey(t, 0);
            g.need[key]           = std::max(g.need[key], int(k));
            const std::string c   = famExpr(g, V[k]);
            oss << " + " << c << " * " << subst("$0_$1[c]", key, T(int(k)));
        }
        oss << ")";
        const std::string l = g.local();
        g.body.push_back(subst("$0 $1 = $2;", g.ty, l, oss.str()));
        g.stateValue[g.stateKey(t, 0)] = l;
        return g.val[t] = l;
    }
    if (isSigFIR(t, V)) {
        // FIR[X, c0, c1, ...] : c0.X + c1.X' + ...
        std::ostringstream oss;
        std::string        sep;
        oss << "(";
        for (size_t k = 1; k < V.size(); k++) {
            auto       sl      = g.slotIndex.find(V[k]);
            const bool uniform = sl != g.slotIndex.end() && g.uniform[sl->second];
            if (uniform && isZero(V[k])) {
                continue;
            }
            const std::string h = famHist(g, V[0], int(k) - 1);
            if (uniform && isOne(V[k])) {
                oss << sep << h;
            } else {
                const std::string c = famExpr(g, V[k]);
                oss << sep << c << " * " << h;
            }
            sep = " + ";
        }
        if (sep.empty()) {
            oss << "0";
        }
        oss << ")";
        return keep(oss.str());
    }
    Tree x, y;
    int  d;
    if (isSigDelay(t, x, y)) {
        if (!isSigInt(y, &d)) {
            g.fail("variable delay inside a member");
            return "0";
        }
        return keep(famHist(g, x, d));
    }
    int  i;
    Tree grp, W, defs;
    if (isProj(t, &i, grp)) {
        if (!isRec(grp, W, defs)) {
            g.fail("projection of a non recursive group");
            return "0";
        }
        if (g.groupState[grp] == 1) {
            g.fail("instantaneous self reference");
            return "0";
        }
        if (g.groupState[grp] == 0) {
            // every definition of the group, in order, each in a local : the value of the
            // sample, then the state
            g.groupState[grp] = 1;
            int j             = 0;
            for (Tree l = defs; isList(l); l = tl(l), j++) {
                const std::string e  = famExpr(g, hd(l));
                const std::string lv = g.local();
                g.body.push_back(subst("$0 $1 = $2;", g.ty, lv, e));
                g.projVal[grp][j]                = lv;
                g.stateValue[g.stateKey(grp, j)] = lv;
            }
            g.groupState[grp] = 2;
        }
        auto it = g.projVal[grp].find(i);
        if (it == g.projVal[grp].end()) {
            g.fail("projection out of its group");
            return "0";
        }
        return g.val[t] = it->second;
    }
    int  op;
    Tree a, b;
    if (isSigBinOp(t, &op, a, b)) {
        const std::string ca = famExpr(g, a);
        const std::string cb = famExpr(g, b);
        return keep(subst("($0 $1 $2)", ca, gBinOpTable[op]->fName, cb));
    }
    if (isSigNeg(t, a)) {
        return keep(subst("(-$0)", famExpr(g, a)));
    }
    if (isSigSum(t, V)) {
        // the layout of emitSum (sumLayout.hh) : the chain of the node, a negated term
        // subtracted, the leading negated terms subtracted from the first positive one ; a
        // term is left out, or read as a negation, only on a coefficient that is the same in
        // every member
        auto uniformIs = [&](Tree u, bool (*test)(Tree)) {
            auto sl = g.slotIndex.find(u);
            return sl != g.slotIndex.end() && g.uniform[sl->second] && test(u);
        };
        std::vector<std::pair<bool, Tree>> st;
        for (Tree u : V) {
            Tree x2, a2, b2;
            tvec fc;
            if (uniformIs(u, [](Tree z) { return isZero(z); })) {
                continue;
            }
            if (isSigNeg(u, x2)) {
                st.push_back({false, x2});
            } else if (isSigMul(u, a2, b2) && uniformIs(a2, isMinusOne)) {
                st.push_back({false, b2});
            } else if (isSigMul(u, a2, b2) && uniformIs(b2, isMinusOne)) {
                st.push_back({false, a2});
            } else if (isSigFIR(u, fc) && fc.size() == 2 && uniformIs(fc[1], isMinusOne)) {
                st.push_back({false, fc[0]});
            } else {
                st.push_back({true, u});
            }
        }
        if (st.empty()) {
            return keep("0");
        }
        size_t first = 0;
        while (first < st.size() && !st[first].first) {
            first++;
        }
        std::string lead;
        for (size_t k = 0; k < first; k++) {
            const std::string x2 = famExpr(g, st[k].second);
            lead                 = lead.empty() ? x2 : subst("($0 + $1)", lead, x2);
        }
        if (first == st.size()) {
            return keep(subst("(-$0)", lead));
        }
        std::string acc = famExpr(g, st[first].second);
        if (!lead.empty()) {
            acc = subst("($0 - $1)", acc, lead);
        }
        for (size_t k = first + 1; k < st.size(); k++) {
            const std::string x2 = famExpr(g, st[k].second);
            acc                  = subst("($0 $1 $2)", acc, st[k].first ? "+" : "-", x2);
        }
        return keep(acc);
    }
    if (isSigProd(t, V)) {
        // the chain of emitProd : a factor that is 1, the same in every member, left out
        tvec kept;
        for (Tree u : V) {
            auto sl = g.slotIndex.find(u);
            if (!(sl != g.slotIndex.end() && g.uniform[sl->second] && isOneAtPrecision(u))) {
                kept.push_back(u);
            }
        }
        if (kept.empty()) {
            kept = V;
        }
        std::string acc;
        for (Tree u : kept) {
            const std::string x2 = famExpr(g, u);
            acc                  = acc.empty() ? x2 : subst("($0 * $1)", acc, x2);
        }
        return keep(acc);
    }
    Tree sel, s0, s1;
    if (isSigSelect2(t, sel, s0, s1)) {
        const std::string csel = famExpr(g, sel);
        const std::string c1   = famExpr(g, s1);
        const std::string c0   = famExpr(g, s0);
        return keep(subst("(($0) ? $1 : $2)", csel, c1, c0));
    }
    if (sigXtendedData(t) != nullptr) {
        // a math primitive : its own generator, on the members' expressions
        xtendedCodegen*          p = static_cast<xtendedCodegen*>((xtended*)sigXtendedData(t));
        std::vector<std::string> args;
        std::vector<::Type>      types;
        for (int k = 0; k < t->arity(); k++) {
            args.push_back(famExpr(g, t->branch(k)));
            types.push_back(getCertifiedSigType(t->branch(k)));
        }
        return keep(p->generateCode(fClass, args, types));
    }
    if (isSigFloatCast(t, x)) {
        return keep(subst("$0($1)", ifloat(), famExpr(g, x)));
    }
    MixForm form;
    if (isCfMix(t, sel, s0, s1, form)) {
        // the spellings of generateMix : a + c * (b - a), b + (1 - c) * (a - b), and from the
        // weight, c written 1 - w, b + w * (a - b)
        const std::string sa = famExpr(g, s0);
        const std::string sb = famExpr(g, s1);
        if (form == MixForm::kFromWeight) {
            Tree w;
            faustassert(mixComplementOf(sel, w));
            const std::string sw = famExpr(g, w);
            return keep(subst("($0 + $1 * ($2 - $0))", sb, sw, sa));
        }
        const std::string sc = famExpr(g, sel);
        if (form == MixForm::kFromB) {
            const std::string one = (gGlobal->gFloatSize == 1) ? "1.0f" : "1.0";
            return keep(subst("($0 + ($1 - $2) * ($3 - $0))", sb, one, sc, sa));
        }
        return keep(subst("($0 + $1 * ($2 - $0))", sa, sc, sb));
    }
    g.fail("unsupported node " + famPrint(t, 12));
    return "0";
}

void ScalarCompiler::famSetup(FamCtx& g, const Family& f)
{
    const FamilyPlan& plan = f.plan;
    const int         P    = int(plan.members.size());
    g.id                   = f.id;
    g.P                    = P;
    g.ty                   = ifloat();
    g.plan                 = &plan;
    g.uniform.assign(plan.leaves.size(), true);
    for (size_t k = 0; k < plan.leaves.size(); k++) {
        g.slotIndex.emplace(plan.leaves[k], int(k));
        for (int m = 0; m < P; m++) {
            g.uniform[k] = g.uniform[k] && plan.slots[m][k] == plan.leaves[k];
        }
    }
    g.auniform.assign(plan.aleaves.size(), true);
    for (size_t k = 0; k < plan.aleaves.size(); k++) {
        g.aslotIndex.emplace(plan.aleaves[k], int(k));
        for (int m = 0; m < P; m++) {
            g.auniform[k] = g.auniform[k] && plan.aslots[m][k] == plan.aleaves[k];
        }
    }
    // the parents inside the template, to name a shared subexpression once
    TreeSet           seen;
    std::vector<Tree> st{plan.tmpl};
    while (!st.empty()) {
        Tree t = st.back();
        st.pop_back();
        if (!seen.insert(t).second || g.slotIndex.count(t) || g.aslotIndex.count(t) || plan.commons.count(t)) {
            continue;
        }
        Tree id, body;
        if (isRec(t, id, body) && body) {
            st.push_back(body);
            continue;
        }
        for (int k = 0; k < t->arity(); k++) {
            g.uses[t->branch(k)]++;
            st.push_back(t->branch(k));
        }
    }
}

void ScalarCompiler::famTables(FamCtx& g)
{
    const FamilyPlan& plan = *g.plan;
    // the coefficients that differ between members : a table, filled once per block
    for (int k : g.usedSlots) {
        const std::string ct = (getCertifiedSigType(plan.leaves[k])->nature() == kInt) ? "int" : g.ty;
        fClass->addDeclCode(subst("$0 \tfFam$1T$2[$3];", ct, T(g.id), T(k), T(g.P)));
        for (int m = 0; m < g.P; m++) {
            const std::string cc = CS(plan.slots[m][k]);
            fClass->addZone3(subst("fFam$0T$1[$2] = $3;", T(g.id), T(k), T(m), cc));
        }
    }
    // the audio inputs that differ between members : an array filled every sample
    for (int k : g.usedASlots) {
        fClass->addExecCode(Statement("", subst("$0 \tfFam$1In$2[$3];", g.ty, T(g.id), T(k), T(g.P))));
        for (int m = 0; m < g.P; m++) {
            const std::string cc = CS(plan.aslots[m][k]);
            fClass->addExecCode(Statement("", subst("fFam$0In$1[$2] = $3;", T(g.id), T(k), T(m), cc)));
        }
    }
}

/// the balanced tree of the lanes acc[0] .. acc[W - 1]
static std::string famLaneTree(const std::string& acc, int W)
{
    std::vector<std::string> S;
    for (int j = 0; j < W; j++) {
        S.push_back(subst("$0[$1]", acc, T(j)));
    }
    while (S.size() > 1) {
        std::vector<std::string> R;
        for (size_t k = 0; k + 1 < S.size(); k += 2) {
            R.push_back(subst("($0 + $1)", S[k], S[k + 1]));
        }
        if (S.size() % 2) {
            R.push_back(S.back());
        }
        S = R;
    }
    return S[0];
}

/// the operations of a member : the nodes of the template, its leaves and the expressions
/// common to every member aside
static int famOps(const FamilyPlan& plan)
{
    TreeSet leaves(plan.leaves.begin(), plan.leaves.end());
    leaves.insert(plan.aleaves.begin(), plan.aleaves.end());
    TreeSet           seen;
    std::vector<Tree> st{plan.tmpl};
    int               ops = 0;
    while (!st.empty()) {
        Tree t = st.back();
        st.pop_back();
        if (!seen.insert(t).second || leaves.count(t) || plan.commons.count(t)) {
            continue;
        }
        Tree id, body;
        if (isRec(t, id, body) && body) {
            st.push_back(body);
            continue;
        }
        ops += (t->arity() > 0) ? 1 : 0;
        for (int k = 0; k < t->arity(); k++) {
            st.push_back(t->branch(k));
        }
    }
    return ops;
}

/// the sum of the n terms acc##Tm in W lanes : term k into lane k mod W, the terms beyond the
/// last whole group of W into lane 0, in order, the lanes added in a balanced tree (a
/// reassociation outside the cone of the decisions, spec LA-FORME-DE-CALCUL). The terms are
/// stored by a loop of their own : a loop that both computes the members and accumulates the
/// lanes carries the lanes from one iteration to the next, and a C++ compiler may then
/// vectorize across the iterations and add every term one at a time, in order
static std::vector<std::string> famLaneSum(const std::string& ty, const std::string& acc, int n, int W)
{
    const int                main = (n / W) * W;
    std::vector<std::string> code{subst("$0 \t$1L[$2] = {};", ty, acc, T(W)),
                                  subst("for (int c0 = 0; c0 < $0; c0 += $1) { for (int j = 0; j < $1; j++) { $2L[j] += $2Tm[c0 + j]; } }",
                                        T(main), T(W), acc)};
    if (main < n) {
        code.push_back(subst("for (int c = $0; c < $1; c++) { $2L[0] += $2Tm[c]; }", T(main), T(n), acc));
    }
    code.push_back(subst("$0 \t$1 = $2;", ty, acc, famLaneTree(acc + "L", W)));
    return code;
}

void ScalarCompiler::emitFamily(Family& f)
{
    if (f.emitted || f.dismantled) {
        return;
    }
    if (f.plan.automaton >= 0) {
        emitAutomaton(fFamilies[f.plan.automaton]);  // the family is accumulated in its loop
        return;
    }
    f.emitted              = true;
    const FamilyPlan& plan = f.plan;
    const int         P    = int(plan.members.size());
    FamCtx            g;
    famSetup(g, f);
    const std::string term = famExpr(g, plan.tmpl);
    for (const auto& kv : g.need) {
        if (!g.stateValue.count(kv.first)) {
            g.fail("a state read but never computed");
        }
    }
    // the plan checked what the loop can write (famCheck) : the private nodes have left the
    // schedule, and a refusal here would leave them uncompiled
    if (g.failed) {
        std::cerr << "ASSERT : the loop of a planned family cannot be written : " << g.reason << std::endl;
        faustassert(false);
    }
    // the states : arrays of P cells, cleared with the other states, shifted at the end of
    // each member's iteration
    std::ostringstream shifts;
    for (const auto& kv : g.need) {
        for (int k = 1; k <= kv.second; k++) {
            fClass->addDeclCode(subst("$0 \t$1_$2[$3];", g.ty, kv.first, T(k), T(P)));
            fClass->addClearCode(subst("for (int c = 0; c < $1; c++) { $0_$2[c] = 0; }", kv.first, T(P), T(k)));
        }
        for (int k = kv.second; k >= 2; k--) {
            shifts << subst(" $0_$1[c] = $0_$2[c];", kv.first, T(k), T(k - 1));
        }
        shifts << subst(" $0_1[c] = $1;", kv.first, g.stateValue[kv.first]);
    }
    famTables(g);
    std::string bodyCode;
    for (const std::string& l : g.body) {
        bodyCode += " " + l;
    }
    // one loop per host over its members. A member of many operations : its term stored, then
    // summed in lanes by a loop of its own (famLaneSum). A member of few operations : the lanes
    // accumulated in the loop, member c0 + j into lane j, where storing and reloading the term
    // would cost more than the member ; the outer loop is kept from clang's loop vectorizer,
    // which would vectorize across c0 and add the terms one at a time, so that the lanes are
    // vectorized whole
    const int  ops   = famOps(plan);
    const bool split = ops >= gGlobal->gFamilySplit;  // -fam-split
    for (size_t h = 0; h < plan.hosts.size(); h++) {
        int lo = -1, hi = -1;
        for (int m = 0; m < P; m++) {
            if (plan.memberHost[m] == int(h)) {
                lo = (lo < 0) ? m : lo;
                hi = m + 1;
            }
        }
        const int         n   = hi - lo;
        const int         W   = std::max(1, std::min(4, n));
        const std::string acc = subst("fFam$0H$1", T(g.id), T(int(h)));
        if (split) {
            fClass->addExecCode(Statement("", subst("$0 \t$1Tm[$2];", g.ty, acc, T(n))));
            fClass->addExecCode(Statement("", subst("for (int c = $0; c < $1; c++) {$2 $3Tm[c - $0] = $4;$5 }", T(lo),
                                                    T(hi), bodyCode, acc, term, shifts.str())));
            for (const std::string& s : famLaneSum(g.ty, acc, n, W)) {
                fClass->addExecCode(Statement("", s));
            }
        } else {
            const int main   = lo + (n / W) * W;
            auto      member = [&](const std::string& lane) {
                return subst("$0 $1L[$2] += $3;$4", bodyCode, acc, lane, term, shifts.str());
            };
            fClass->addExecCode(Statement("", subst("$0 \t$1L[$2] = {};", g.ty, acc, T(W))));
            fClass->addExecCode(Statement("", "#if defined(__clang__)"));
            fClass->addExecCode(Statement("", "#pragma clang loop vectorize(disable)"));
            fClass->addExecCode(Statement("", "#endif"));
            fClass->addExecCode(Statement(
                "", subst("for (int c0 = $0; c0 < $1; c0 += $2) { for (int j = 0; j < $2; j++) { int c = c0 + j;$3 } }",
                          T(lo), T(main), T(W), member("j"))));
            if (main < hi) {
                fClass->addExecCode(Statement("", subst("for (int c = $0; c < $1; c++) {$2 }", T(main), T(hi), member("0"))));
            }
            fClass->addExecCode(Statement("", subst("$0 \t$1 = $2;", g.ty, acc, famLaneTree(acc + "L", W))));
        }
        f.hostExpr.push_back(acc);
    }
    if (famTrace()) {
        std::cerr << "fam emitted : family " << g.id << ", " << P << " members, " << plan.hosts.size() << " host(s), "
                  << g.need.size() << " states, " << g.usedSlots.size() << " tables, " << g.usedASlots.size()
                  << " input arrays, " << g.body.size() << " statements per member, " << ops << " operations, "
                  << (split ? "split" : "one loop") << std::endl;
    }
}

bool ScalarCompiler::famAutoRead(Tree exp, const std::string& delayidx, std::string& out)
{
    int  j;
    Tree group;
    if (fFamGroup.empty() || !isProj(exp, &j, group)) {
        return false;
    }
    auto it = fFamGroup.find(group);
    if (it == fFamGroup.end()) {
        return false;
    }
    Family& f = fFamilies[it->second];
    if (delayidx == "0") {
        emitAutomaton(f);  // the current generation : computed by the automaton
    }
    // the group's arrays : row R[0] the current generation, row R[d] the generation d samples ago
    out = subst("$0[$1]", famRow(subst("fFam$0S", T(f.id)), delayidx), T(j));
    return true;
}

void ScalarCompiler::emitAutomaton(Family& f)
{
    if (f.emitted || f.dismantled) {
        return;
    }
    f.emitted              = true;
    const FamilyPlan& plan = f.plan;
    const int         P    = int(plan.members.size());
    const int         N    = plan.size;
    const int         D    = plan.depth;
    const std::string S    = subst("fFam$0S", T(f.id));
    // the arrays of the group : one row per generation, cleared with the other states ; the
    // index R names the row of each generation and rotates at the end of the sample, after
    // every read : the oldest row becomes the current one
    const std::string R = subst("fFam$0R", T(f.id));
    fClass->addDeclCode(subst("$0 \t$1[$2][$3];", ifloat(), S, T(D + 1), T(N)));
    fClass->addDeclCode(subst("int \t$0[$1];", R, T(D + 1)));
    fClass->addClearCode(subst("for (int d = 0; d < $0; d++) { $1[d] = d; for (int j = 0; j < $2; j++) { $3[d][j] = 0; } }",
                               T(D + 1), R, T(N), S));
    std::string rotate = subst("int r = $0[$1];", R, T(D));
    for (int d = D; d >= 1; d--) {
        rotate += subst(" $0[$1] = $0[$2];", R, T(d), T(d - 1));
    }
    fClass->addPostCode(Statement("", subst("{ $0 $1[0] = r; }", rotate, R)));

    // the cells : the template, read in the arrays at its neighbourhood
    FamCtx g;
    famSetup(g, f);
    g.states    = S;
    g.neighbour = plan.neighbour;
    const std::string term = famExpr(g, plan.tmpl);
    for (const auto& kv : g.need) {
        if (!g.stateValue.count(kv.first)) {
            g.fail("a state read but never computed");
        }
    }
    std::ostringstream shifts;
    for (const auto& kv : g.need) {
        for (int k = 1; k <= kv.second; k++) {
            fClass->addDeclCode(subst("$0 \t$1_$2[$3];", g.ty, kv.first, T(k), T(P)));
            fClass->addClearCode(subst("for (int c = 0; c < $1; c++) { $0_$2[c] = 0; }", kv.first, T(P), T(k)));
        }
        for (int k = kv.second; k >= 2; k--) {
            shifts << subst(" $0_$1[c] = $0_$2[c];", kv.first, T(k), T(k - 1));
        }
        shifts << subst(" $0_1[c] = $1;", kv.first, g.stateValue[kv.first]);
    }
    // the families accumulated in the loop : in the loop, the member reads the cell's value
    // still in a register ; outside, a member of a border reads the cell in the arrays
    struct Fused {
        Family*     f;
        FamCtx      in, out;
        std::string termIn, termOut, bodyIn, bodyOut;
        int         first = 0;  // the member of the loop's first cell
    };
    std::vector<Fused> fused;
    for (int k : f.fused) {
        Family& ff = fFamilies[k];
        if (ff.dismantled) {
            continue;
        }
        fused.push_back(Fused());
        Fused& u = fused.back();
        u.f      = &ff;
        famSetup(u.in, ff);
        famSetup(u.out, ff);
        u.in.idx  = u.out.idx = "m";
        u.in.cellSlot = u.out.cellSlot = ff.plan.cellSlot;
        u.in.cellValue  = "v";
        u.out.cellValue = subst("$0[cell]", famRow(S, "0"));
        u.termIn        = famExpr(u.in, ff.plan.tmpl);
        u.termOut       = famExpr(u.out, ff.plan.tmpl);
        for (const std::string& l : u.in.body) {
            u.bodyIn += " " + l;
        }
        for (const std::string& l : u.out.body) {
            u.bodyOut += " " + l;
        }
        while (ff.plan.cell[u.first] != plan.base) {
            u.first++;
        }
        g.failed = g.failed || u.in.failed || u.out.failed;
        g.reason += u.in.reason + u.out.reason;
    }
    if (g.failed) {
        std::cerr << "ASSERT : the loop of a planned automaton cannot be written : " << g.reason << std::endl;
        faustassert(false);
    }
    famTables(g);
    for (Fused& u : fused) {
        u.in.usedSlots.insert(u.out.usedSlots.begin(), u.out.usedSlots.end());
        u.in.usedASlots.insert(u.out.usedASlots.begin(), u.out.usedASlots.end());
        famTables(u.in);
    }
    // the borders : computed by the schedule, stored in the current generation
    Tree W, defs;
    isRec(plan.group, W, defs);
    int j = 0;
    for (Tree l = defs; isList(l); l = tl(l), j++) {
        if (j < plan.base || j >= plan.base + P) {
            const std::string code = CS(hd(l));
            fClass->addExecCode(Statement("", subst("$0[$1] = $2;", famRow(S, "0"), T(j), code)));
        }
    }
    std::string bodyCode;
    for (const std::string& l : g.body) {
        bodyCode += " " + l;
    }
    // the cell c : its value stored, then the terms of the members that read it
    std::string code = subst(" int cell = c + $0;$1 $2 v = $3; $4[cell] = v;$5", T(plan.base), bodyCode, g.ty, term,
                             famRow(S, "0"), shifts.str());
    for (Fused& u : fused) {
        fClass->addExecCode(Statement("", subst("$0 \tfFam$1H0Tm[$2];", g.ty, T(u.f->id), T(P))));
        code += subst(" { int m = c + $0;$1 fFam$2H0Tm[c] = $3; }", T(u.first), u.bodyIn, T(u.f->id), u.termIn);
    }
    fClass->addExecCode(Statement("", subst("for (int c = 0; c < $0; c++) {$1 }", T(P), code)));
    if (!fused.empty()) {
        // the lanes : a register of 256 bits, 8 floats or 4 doubles ; the lanes in a balanced
        // tree, then the members of the borders, in order
        const int W = std::max(1, std::min(gGlobal->gFloatSize == 1 ? 8 : 4, P));
        for (Fused& u : fused) {
            const std::string acc = subst("fFam$0H0", T(u.f->id));
            for (const std::string& s : famLaneSum(g.ty, acc, P, W)) {
                fClass->addExecCode(Statement("", s));
            }
            const int Pf = int(u.f->plan.members.size());
            for (int m = 0; m < Pf; m++) {
                const int cell = u.f->plan.cell[m];
                if (cell >= plan.base && cell < plan.base + P) {
                    continue;
                }
                fClass->addExecCode(Statement("", subst("{ int m = $0; int cell = $1;$2 $3 = ($3 + $4); }", T(m), T(cell),
                                                        u.bodyOut, acc, u.termOut)));
            }
            u.f->hostExpr.push_back(acc);
            u.f->emitted = true;
        }
    }
    if (famTrace()) {
        std::cerr << "fam emitted : automaton " << g.id << ", " << P << " cells of " << N << " definitions, depth " << D
                  << ", " << g.usedSlots.size() << " tables, " << g.usedASlots.size() << " input arrays, "
                  << fused.size() << " famil" << (fused.size() == 1 ? "y" : "ies") << " in its loop, " << g.body.size()
                  << " statements per cell" << std::endl;
    }
}

std::string ScalarCompiler::generateFamilySum(Tree sig)
{
    Family& f = fFamilies[fFamHost.at(sig)];
    emitFamily(f);
    size_t h = 0;
    while (f.plan.hosts[h] != sig) {
        h++;
    }
    tvec terms;
    isSigSum(sig, terms);
    TreeSet            in(f.plan.members.begin(), f.plan.members.end());
    std::string code = f.hostExpr[h];
    for (Tree t : terms) {
        if (!in.count(t)) {
            code = subst("($0 + $1)", code, CS(t));  // the terms outside the family, after the lanes, in order
        }
    }
    return generateCacheCode(sig, code);
}
