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
    fFamPrivate.clear();
    if (!gGlobal->gFamilies || gGlobal->gLoopSplit || fFamRoot == nullptr) {
        return;
    }
    for (FamilyPlan& p : findFamilies(fFamRoot)) {
        bool conditional = false;
        for (Tree t : p.priv) {
            conditional = conditional || !getConditionCode(t).empty();
        }
        for (Tree h : p.hosts) {
            conditional = conditional || !getConditionCode(h).empty();
        }
        if (conditional) {
            if (famTrace()) {
                std::cerr << "fam refused : family of " << p.members.size() << " : conditional" << std::endl;
            }
            continue;
        }
        Family f;
        f.plan = p;
        f.id   = int(fFamilies.size());
        for (Tree h : p.hosts) {
            fFamHost[h] = f.id;
        }
        fFamPrivate.insert(p.priv.begin(), p.priv.end());
        fFamilies.push_back(f);
    }
}

/// the audio nodes a family reads from outside : its commons and audio slots
static TreeSet famInputs(const FamilyPlan& p)
{
    TreeSet inputs(p.commons.begin(), p.commons.end());
    for (auto& v : p.aslots) {
        inputs.insert(v.begin(), v.end());
    }
    return inputs;
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
    f.dismantled = true;
}

void ScalarCompiler::checkFamilyOrder()
{
    for (Family& f : fFamilies) {
        int first = INT_MAX;
        for (Tree h : f.plan.hosts) {
            if (auto it = fSchedPos.find(h); it != fSchedPos.end()) {
                first = std::min(first, it->second);
            }
        }
        int  latest  = -1;
        Tree culprit = nullptr;
        for (Tree t : famInputs(f.plan)) {
            int k;
            if (isSigInput(t, &k) || getCertifiedSigType(t)->variability() < kSamp) {
                continue;
            }
            if (auto it = fSchedPos.find(t); it != fSchedPos.end() && it->second > latest) {
                latest  = it->second;
                culprit = t;
            }
        }
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

std::string ScalarCompiler::famHist(FamCtx& g, Tree x, int k)
{
    if (g.failed) {
        return "0";
    }
    if (k == 0) {
        return famExpr(g, x);
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
        g.usedSlots.insert(it->second);
        return g.val[t] = subst("fFam$0T$1[c]", T(g.id), T(it->second));
    }
    if (g.plan->commons.count(t)) {
        return g.val[t] = CS(t);  // what the family reads from outside is the tree's node
    }
    if (auto it = g.aslotIndex.find(t); it != g.aslotIndex.end()) {
        if (g.auniform[it->second]) {
            return g.val[t] = CS(t);
        }
        g.usedASlots.insert(it->second);
        return g.val[t] = subst("fFam$0In$1[c]", T(g.id), T(it->second));
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

void ScalarCompiler::emitFamily(Family& f)
{
    if (f.emitted || f.dismantled) {
        return;
    }
    f.emitted               = true;
    const FamilyPlan& plan  = f.plan;
    const int         P     = int(plan.members.size());
    FamCtx            g;
    g.id   = f.id;
    g.P    = P;
    g.ty   = ifloat();
    g.plan = &plan;
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
    {
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
    // the coefficients that differ between members : a table, filled once per block
    for (int k : g.usedSlots) {
        const std::string ct = (getCertifiedSigType(plan.leaves[k])->nature() == kInt) ? "int" : g.ty;
        fClass->addDeclCode(subst("$0 \tfFam$1T$2[$3];", ct, T(g.id), T(k), T(P)));
        for (int m = 0; m < P; m++) {
            const std::string cc = CS(plan.slots[m][k]);
            fClass->addZone3(subst("fFam$0T$1[$2] = $3;", T(g.id), T(k), T(m), cc));
        }
    }
    // the audio inputs that differ between members : an array filled every sample
    for (int k : g.usedASlots) {
        fClass->addExecCode(Statement("", subst("$0 \tfFam$1In$2[$3];", g.ty, T(g.id), T(k), T(P))));
        for (int m = 0; m < P; m++) {
            const std::string cc = CS(plan.aslots[m][k]);
            fClass->addExecCode(Statement("", subst("fFam$0In$1[$2] = $3;", T(g.id), T(k), T(m), cc)));
        }
    }
    std::string bodyCode;
    for (const std::string& l : g.body) {
        bodyCode += " " + l;
    }
    // one loop per host over its members, the sum in lanes : member c0 + j into lane j, the
    // loop unrolled by the number of lanes, the lanes added in a balanced tree (a
    // reassociation outside the cone of the decisions, spec LA-FORME-DE-CALCUL)
    for (size_t h = 0; h < plan.hosts.size(); h++) {
        int lo = -1, hi = -1;
        for (int m = 0; m < P; m++) {
            if (plan.memberHost[m] == int(h)) {
                lo = (lo < 0) ? m : lo;
                hi = m + 1;
            }
        }
        const int         n    = hi - lo;
        const int         W    = std::max(1, std::min(gGlobal->gFamilyLanes, n));
        const int         main = lo + (n / W) * W;
        const std::string acc  = subst("fFam$0H$1", T(g.id), T(int(h)));
        // the statements of member c, accumulated into a lane
        auto member = [&](int lane) {
            return subst("$0 $1L[$2] += $3;$4", bodyCode, acc, T(lane), term, shifts.str());
        };
        fClass->addExecCode(Statement("", subst("$0 \t$1L[$2] = {};", g.ty, acc, T(W))));
        std::string unrolled;
        for (int j = 0; j < W; j++) {
            unrolled += subst(" { int c = c0 + $0;$1 }", T(j), member(j));
        }
        fClass->addExecCode(
            Statement("", subst("for (int c0 = $0; c0 < $1; c0 += $2) {$3 }", T(lo), T(main), T(W), unrolled)));
        if (main < hi) {
            fClass->addExecCode(Statement("", subst("for (int c = $0; c < $1; c++) {$2 }", T(main), T(hi), member(0))));
        }
        std::vector<std::string> S;
        for (int j = 0; j < W; j++) {
            S.push_back(subst("$0L[$1]", acc, T(j)));
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
        fClass->addExecCode(Statement("", subst("$0 \t$1 = $2;", g.ty, acc, S[0])));
        f.hostExpr.push_back(acc);
    }
    if (famTrace()) {
        std::cerr << "fam emitted : family " << g.id << ", " << P << " members, " << plan.hosts.size() << " host(s), "
                  << g.need.size() << " states, " << g.usedSlots.size() << " tables, " << g.usedASlots.size()
                  << " input arrays, " << g.body.size() << " statements per member" << std::endl;
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
