/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "superNodes.hh"

#include <algorithm>
#include <functional>

#include "exception.hh"
#include "sharing.hh"
#include "signals.hh"
#include "sigtyperules.hh"

/*****************************************************************************
 shared helpers
 *****************************************************************************/

bool SuperNodeGraph::isNum(Tree t)
{
    int     i;
    int64_t i64;
    double  r;
    return isSigInt(t, &i) || isSigInt64(t, &i64) || isSigReal(t, &r);
}

bool SuperNodeGraph::isSlow(Tree t)
{
    return getCertifiedSigType(t)->variability() < kSamp;
}

bool SuperNodeGraph::isCallPrim(const std::string& name)
{
    static const std::set<std::string> calls = {
        "sin",  "cos",   "tan", "asin", "acos",  "atan",  "atan2", "exp",
        "exp2", "exp10", "log", "log2", "log10", "pow",   "fmod",  "remainder",
        "sinh", "cosh",  "tanh", "asinh", "acosh", "atanh"};
    return calls.count(name) > 0;
}

Tree SuperNodeGraph::defOf(Tree m)
{
    int  i;
    Tree w, id, le;
    if (isProj(m, &i, w)) {
        faustassert(isRec(w, id, le));
        return nth(le, i);
    }
    return m;
}

void SuperNodeGraph::delayBounds(Tree y, int& dmin, int& dmax, bool& dvar)
{
    int d;
    if (isSigInt(y, &d)) {
        dmin = dmax = d;
        dvar        = false;
    } else {
        interval I = getCertifiedSigType(y)->getInterval();
        dmin       = (int)I.lo();
        dmax       = (int)I.hi();
        dvar       = true;
    }
}

int SuperNodeGraph::maxDelayOf(Tree t) const
{
    Occurrences* o = fOcc->retrieve(t);
    return o ? o->getMaxDelay() : 0;
}

/*****************************************************************************
 materialization criterion
 *****************************************************************************/

bool SuperNodeGraph::materializedCriterion(Tree t) const
{
    int  i;
    Tree w;
    if (isNum(t) || isSlow(t) || isSigInput(t, &i)) {
        // a delayed constant/slow/input needs a history buffer (a copy loop
        // whose zero-initialized prefix IS the initial-delay semantics)
        return maxDelayOf(t) > 0;
    }
    return isProj(t, &i, w) || maxDelayOf(t) > 0 || getSharingCount(t, fKey) > 1;
}

/*****************************************************************************
 reference collection
 *****************************************************************************/

void SuperNodeGraph::collectRefs(Tree t, std::set<int>& refs, std::set<int>& refs0,
                                 std::set<Tree>& seen, bool root) const
{
    int  i;
    Tree x, y, tb, size, gen, ri;
    if (seen.count(t)) {
        return;
    }
    seen.insert(t);
    // materialization first: nums/slow/inputs CAN be materialized (when
    // delayed), and their d0 readers need the ordering edge. The walk's ROOT
    // is the signal whose refs we are collecting -- it must not match
    // itself, its children are the references.
    auto it = fMatIdx.find(t);
    if (!root && it != fMatIdx.end()) {
        refs.insert(it->second);
        refs0.insert(it->second);
        return;
    }
    if (isNum(t) || isSigInput(t, &i)) {
        return;
    }
    if (isSigAttach(t, x, y) && !isSlow(y)) {
        // attach takes the type of its left arm but its right arm is a
        // sample-rate side effect: it must escape the slow pruning below
        collectRefs(x, refs, refs0, seen, false);
        collectRefs(y, refs, refs0, seen, false);
        return;
    }
    if (isSlow(t)) {
        return;
    }
    if (isSigDelay(t, x, y)) {
        int  dmin, dmax;
        bool dvar;
        delayBounds(y, dmin, dmax, dvar);
        auto ix = fMatIdx.find(x);
        if (ix != fMatIdx.end()) {
            // a read whose certified minimal delay reaches the chunk size
            // only touches previous chunks: it does not constrain grouping
            if (fFreeDelay == 0 || dmin < fFreeDelay) {
                refs.insert(ix->second);
            }
            if (dmin == 0) {
                refs0.insert(ix->second);
            }
        } else {
            collectRefs(x, refs, refs0, seen, false);
        }
        collectRefs(y, refs, refs0, seen, false);
        return;
    }
    if (isSigRDTbl(t, tb, ri) && isSigWRTbl(tb, size, gen)) {
        // read-only table: the content is init-time, only the index matters
        collectRefs(ri, refs, refs0, seen, false);
        return;
    }
    tvec subs;
    getSubSignals(t, subs, false);
    for (Tree s : subs) {
        collectRefs(s, refs, refs0, seen, false);
    }
}

/*****************************************************************************
 Tarjan strongly connected components over fRefs
 *****************************************************************************/

struct SuperNodeGraph::TarjanState {
    std::vector<int>  index, low;
    std::vector<bool> onstack;
    std::vector<int>  stack;
    int               counter = 0;
};

void SuperNodeGraph::tarjanVisit(int v, TarjanState& st, std::vector<std::vector<int>>& comps)
{
    st.index[v] = st.low[v] = st.counter++;
    st.stack.push_back(v);
    st.onstack[v] = true;
    for (int w : fRefs[v]) {
        if (st.index[w] < 0) {
            tarjanVisit(w, st, comps);
            st.low[v] = std::min(st.low[v], st.low[w]);
        } else if (st.onstack[w]) {
            st.low[v] = std::min(st.low[v], st.index[w]);
        }
    }
    if (st.low[v] == st.index[v]) {
        std::vector<int> comp;
        int              w;
        do {
            w = st.stack.back();
            st.stack.pop_back();
            st.onstack[w] = false;
            comp.push_back(w);
        } while (w != v);
        comps.push_back(comp);
    }
}

/*****************************************************************************
 build
 *****************************************************************************/

void SuperNodeGraph::build(Tree L, const std::vector<Tree>& sched, int freeDelayThreshold)
{
    fFreeDelay = freeDelayThreshold;

    // 1. materialized signals, in schedule order (deterministic indices)
    for (Tree t : sched) {
        if (fMatIdx.find(t) == fMatIdx.end() && materializedCriterion(t)) {
            fMatIdx[t] = (int)fMat.size();
            fMat.push_back(t);
        }
    }
    int n = (int)fMat.size();

    // 2. reference graph
    fRefs.resize(n);
    fRefs0.resize(n);
    for (int i = 0; i < n; i++) {
        std::set<Tree> seen;
        Tree           d = defOf(fMat[i]);
        if (d != fMat[i] && fMatIdx.count(d)) {
            // projection defined by another materialized signal: pure ref
            fRefs[i].insert(fMatIdx[d]);
            fRefs0[i].insert(fMatIdx[d]);
        } else {
            collectRefs(d, fRefs[i], fRefs0[i], seen, /*root*/ true);
        }
    }

    // 3. blocks: Tarjan pops components in dependencies-first order
    std::vector<std::vector<int>> comps;
    {
        TarjanState st;
        st.index.assign(n, -1);
        st.low.assign(n, 0);
        st.onstack.assign(n, false);
        for (int v = 0; v < n; v++) {
            if (st.index[v] < 0) {
                tarjanVisit(v, st, comps);
            }
        }
    }

    // 4. order members of each block by instantaneous dependencies
    // (acyclic by causality)
    fScc.assign(n, -1);
    fBlocks.clear();
    for (auto& comp : comps) {
        int b = (int)fBlocks.size();
        std::sort(comp.begin(), comp.end());  // schedule order as base
        for (int m : comp) {
            fScc[m] = b;
        }
        fBlocks.push_back(orderByInstantDeps(comp));
    }
}

/**
 * Topological order of a member set along its internal instantaneous
 * dependencies (fRefs0 restricted to the set) -- acyclic by causality.
 */
std::vector<int> SuperNodeGraph::orderByInstantDeps(const std::vector<int>& members) const
{
    std::set<int>            inSet(members.begin(), members.end());
    std::vector<int>         ordered;
    std::map<int, int>       state;  // 0 unvisited, 1 visiting, 2 done
    std::function<void(int)> dfs = [&](int m) {
        if (state[m]) {
            return;
        }
        state[m] = 1;
        for (int p : fRefs0[m]) {
            if (inSet.count(p) && p != m) {
                dfs(p);
            }
        }
        state[m] = 2;
        ordered.push_back(m);
    };
    for (int m : members) {
        dfs(m);
    }
    return ordered;
}

/*****************************************************************************
 the moves
 *****************************************************************************/

std::set<int> SuperNodeGraph::blockDeps(int b) const
{
    std::set<int> deps;
    for (int m : fBlocks[b]) {
        for (int r : fRefs[m]) {
            if (fScc[r] != b) {
                deps.insert(fScc[r]);
            }
        }
    }
    return deps;
}

std::set<int> SuperNodeGraph::blockConsumers(int b) const
{
    std::set<int> cons;
    for (int b2 = 0; b2 < (int)fBlocks.size(); b2++) {
        if (b2 == b) {
            continue;
        }
        for (int m : fBlocks[b2]) {
            for (int r : fRefs[m]) {
                if (fScc[r] == b) {
                    cons.insert(b2);
                }
            }
        }
    }
    return cons;
}

/**
 * Contract(a, b) keeps the quotient acyclic iff there is no path between a
 * and b through a third block, in either direction. Check: DFS in the
 * quotient dependency graph ignoring direct a<->b edges.
 */
bool SuperNodeGraph::canContract(int a, int b) const
{
    auto reachesThroughOthers = [&](int from, int to) -> bool {
        std::set<int>    seen = {from};
        std::vector<int> todo;
        for (int d : blockDeps(from)) {
            if (d != to) {  // ignore the direct edge
                todo.push_back(d);
            }
        }
        while (!todo.empty()) {
            int x = todo.back();
            todo.pop_back();
            if (x == to) {
                return true;
            }
            if (!seen.insert(x).second) {
                continue;
            }
            for (int d : blockDeps(x)) {
                todo.push_back(d);
            }
        }
        return false;
    };
    return !reachesThroughOthers(a, b) && !reachesThroughOthers(b, a);
}

void SuperNodeGraph::contract(int a, int b)
{
    faustassert(a != b);
    std::vector<int> merged = fBlocks[a];
    merged.insert(merged.end(), fBlocks[b].begin(), fBlocks[b].end());
    std::sort(merged.begin(), merged.end());
    for (int m : merged) {
        fScc[m] = a;
    }
    fBlocks[a] = orderByInstantDeps(merged);
    fBlocks.erase(fBlocks.begin() + b);
    // block ids above b shift down
    for (int& s : fScc) {
        if (s > b) {
            s--;
        }
    }
}

/**
 * Renumber blocks in dependencies-first order (Kahn on the quotient) --
 * emission relies on it. Called once after a fusion campaign.
 */
void SuperNodeGraph::retopo()
{
    int              nb = (int)fBlocks.size();
    std::vector<int> indeg(nb, 0);
    std::vector<std::set<int>> cons(nb);
    for (int b = 0; b < nb; b++) {
        for (int d : blockDeps(b)) {
            cons[d].insert(b);
        }
        indeg[b] = (int)blockDeps(b).size();
    }
    std::vector<int> order;
    std::vector<int> todo;
    for (int b = 0; b < nb; b++) {
        if (indeg[b] == 0) {
            todo.push_back(b);
        }
    }
    while (!todo.empty()) {
        int b = todo.back();
        todo.pop_back();
        order.push_back(b);
        for (int c : cons[b]) {
            if (--indeg[c] == 0) {
                todo.push_back(c);
            }
        }
    }
    faustassert((int)order.size() == nb);  // acyclic by invariant
    std::vector<std::vector<int>> nb2(nb);
    std::vector<int>              newId(nb);
    for (int k = 0; k < nb; k++) {
        newId[order[k]] = k;
        nb2[k]          = fBlocks[order[k]];
    }
    fBlocks = std::move(nb2);
    for (int& s : fScc) {
        s = newId[s];
    }
}

/**
 * Count of sample-rate operation nodes in a member's body, stopping at the
 * same boundaries as the reference walk (other materialized signals, nums,
 * slow subtrees, inputs). Pure analysis, no side effects.
 */
int SuperNodeGraph::opsOfMember(int m) const
{
    auto it = fOpsEstimate.find(m);
    if (it != fOpsEstimate.end()) {
        return it->second;
    }
    int            count = 0;
    std::set<Tree> seen;
    // the root exemption is POSITIONAL (like collectRefs), not by identity:
    // a member's self-read re-encounters the member's tree deeper in the
    // walk, and must stop there like any materialized reference
    std::function<void(Tree, bool)> walk = [&](Tree t, bool root) {
        int  i;
        Tree x, y, tb, size, gen, ri;
        if (seen.count(t)) {
            return;
        }
        seen.insert(t);
        if (!root && fMatIdx.count(t)) {
            return;
        }
        if (isNum(t) || isSigInput(t, &i)) {
            return;
        }
        Tree ax, ay;
        if (isSigAttach(t, ax, ay) && !isSlow(ay)) {
            count++;
            walk(ax, false);
            walk(ay, false);
            return;
        }
        if (isSlow(t)) {
            return;
        }
        if (isSigDelay(t, x, y)) {
            walk(x, false);
            walk(y, false);
            return;
        }
        count++;
        if (isSigRDTbl(t, tb, ri) && isSigWRTbl(tb, size, gen)) {
            walk(ri, false);
            return;
        }
        tvec subs;
        getSubSignals(t, subs, false);
        for (Tree s : subs) {
            walk(s, false);
        }
    };
    Tree d = defOf(fMat[m]);
    if (!(d != fMat[m] && fMatIdx.count(d))) {
        walk(d, true);
    }
    fOpsEstimate[m] = count;
    return count;
}

int SuperNodeGraph::opsEstimate(int b) const
{
    int total = 0;
    for (int m : fBlocks[b]) {
        total += opsOfMember(m);
    }
    return total;
}

std::vector<int> SuperNodeGraph::orderedUnion(int a, int b) const
{
    std::vector<int> merged = fBlocks[a];
    merged.insert(merged.end(), fBlocks[b].begin(), fBlocks[b].end());
    std::sort(merged.begin(), merged.end());
    return orderByInstantDeps(merged);
}

std::set<int> SuperNodeGraph::blockIns(int b) const
{
    std::set<int> ins;
    for (int m : fBlocks[b]) {
        for (int r : fRefs[m]) {
            if (fScc[r] != b) {
                ins.insert(r);
            }
        }
    }
    return ins;
}

void SuperNodeGraph::print(std::ostream& out) const
{
    out << "SuperNodeGraph: " << fMat.size() << " materialized signals, " << fBlocks.size()
        << " blocks\n";
    for (int b = 0; b < (int)fBlocks.size(); b++) {
        const auto& mb  = fBlocks[b];
        auto        ins = blockIns(b);
        out << "  block " << b << ": " << mb.size() << " member(s) [";
        for (size_t k = 0; k < mb.size(); k++) {
            out << (k ? " " : "") << mb[k];
        }
        out << "] ins {";
        bool first = true;
        for (int i : ins) {
            out << (first ? "" : " ") << i;
            first = false;
        }
        out << "} maxd ";
        int mx = 0;
        for (int m : mb) {
            mx = std::max(mx, maxDelayOf(fMat[m]));
        }
        out << mx << "\n";
    }
}
