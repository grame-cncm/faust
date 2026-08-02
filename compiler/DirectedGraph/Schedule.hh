/*
 * Copyright (c) 2020-2026, Yann Orlarey
 * SPDX-License-Identifier: Apache-2.0
 */

/*******************************************************************************
    Schedule.hh

    A schedule is an ordered set of nodes of some directed graph.
    It capture the idea of computing the graph in a certain order that preserves
    the dependencies.

 ******************************************************************************/

#pragma once
#include <algorithm>
#include <climits>  // for std::find
#include <cassert>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "DirectedGraph.hh"
#include "DirectedGraphAlgorythm.hh"

/**
 * @brief a schedule gives the computation order of the nodes of a DAG.
 * A valid schedule is such if n->m in G, then order(n) > order(m), i.e. n
 * must be computed after m because it depends on it.
 *
 * @tparam N
 */
template <typename N>
class schedule {
   private:
    std::vector<N>   fElements;  // ordered set of elements
    std::map<N, int> fOrder;  // order of each element (starting at 1, 0 indicates not in schedule)

   public:
    // number of elements in the schedule
    [[nodiscard]] size_t size() const { return fElements.size(); }

    // the vector of elements (for iterations). Returns a REFERENCE into this schedule :
    // the deleted rvalue overload rejects 'f(...).elements()' at compile time.
    [[nodiscard]] const std::vector<N>& elements() const& { return fElements; }
    const std::vector<N>&               elements() const&& = delete;

    // the order of an element in the schedule (starting from 1)
    [[nodiscard]] int order(const N& n) const
    {
        auto it = fOrder.find(n);
        return (it == fOrder.end()) ? 0 : it->second;
    }

    // append a new element to a schedule
    schedule& append(const N& n)
    {
        if (fOrder[n] > 0) {
            std::cerr << "WARNING, already scheduled" << '\n';
        } else {
            fElements.push_back(n);
            fOrder[n] = int(fElements.size());
        }
        return *this;
    }

    // append all the elements of a schedule
    schedule& append(const schedule<N>& S)
    {
        for (const N& n : S.elements()) {
            append(n);
        }
        return *this;
    }

    // A schedule in reverse order
    schedule reverse() const
    {
        schedule<N> S;
        for (auto it = fElements.rbegin(); it != fElements.rend(); ++it) {
            S.append(*it);
        }
        return S;
    }
};

/**
 * @brief print a schedule
 *
 * @tparam N
 * @param file
 * @param S the schedule
 * @return std::ostream& the output stream
 */
template <typename N>
inline std::ostream& operator<<(std::ostream& file, const schedule<N>& S)
{
    std::string sep = "";

    file << "Schedule {";
    for (const N& n : S.elements()) {
        file << sep << S.order(n) << ":" << n;
        sep = ", ";
    }
    return file << "}";
}

/**
 * @brief Deep-first scheduling of a DAG G
 *
 * @tparam N the type of nodes of G
 * @param G the graph we want to schedule
 * @return schedule<N> the deep first schedule of G
 */
template <typename N>
inline schedule<N> dfschedule(const digraph<N>& G)
{
    schedule<N> S;
    std::set<N> V;  // set of visited nodes

    // Iterative deep-first visit: an explicit two-phase stack -- an unexpanded
    // entry pushes its destinations (reversed, so they are explored in order), an
    // expanded entry is appended to the schedule. Exactly the recursive visit's
    // order, but the C++ stack depth stays constant: scheduling a pathologically
    // deep graph must not be the thing that overflows.
    for (const auto& r : roots(G)) {
        std::vector<std::pair<N, bool>> work;  // (node, expanded)
        work.push_back({r, false});
        while (!work.empty()) {
            if (work.back().second) {
                S.append(work.back().first);
                work.pop_back();
                continue;
            }
            N n = work.back().first;
            if (V.find(n) != V.end()) {
                work.pop_back();
                continue;
            }
            V.insert(n);
            work.back().second = true;
            const auto& dests = G.destinations(n);
            for (auto it = dests.rbegin(); it != dests.rend(); ++it) {
                work.push_back({it->first, false});
            }
        }
    }

    return S;
}

/**
 * @brief Breadth-first scheduling of G
 *
 * @tparam N the type of the nodes of G
 * @param G the graph we want to schedule
 * @return schedule<N> the breadth first schedule of G
 */

template <typename N>
inline schedule<N> bfschedule(const digraph<N>& G)
{
    std::vector<std::vector<N>> P = parallelize(G);
    schedule<N>                 S;

    for (uint64_t i = 0; i < P.size(); i++) {
        for (const N& n : P[i]) {
            S.append(n);
        }
    }
    return S;
}

/**
 * @brief special schedule for a DAG
 *
 * @tparam N
 * @param G
 * @return schedule<N>
 */
template <typename N>
inline schedule<N> spschedule(const digraph<N>& G)
{
    std::set<N> V;  // already scheduled nodes
    schedule<N> S;  // the final schedule

    std::list<N> L = recschedule(G);  // schedule list with duplicated
    for (auto it = L.rbegin(); it != L.rend(); ++it) {
        if (V.find(*it) == V.end()) {
            S.append(*it);
            V.insert(*it);
        }
    }
    return S;
}

/**
 * @brief The 'cost' of a scheduling. The scheduling time distance
 * between the nodes and its dependencies. This should be an indication
 * of how hot the cache is kept by this scheduling. The less the cost
 * is the better it is.
 *
 * @tparam N
 * @param G
 * @param S
 * @return int
 */
template <typename N>
inline unsigned int schedulingcost(const digraph<N>& G, const schedule<N>& S)
{
    unsigned int cost = 0;
    for (const N& n : G.nodes()) {
        unsigned int t1 = S.order(n);
        for (const auto& c : G.destinations(n)) {
            unsigned int t0 = S.order(c.first);
            // assert(t1 > t0);
            cost += (t1 - t0) * (t1 - t0);  // We may have loops
        }
    }
    return cost;
}

/**
 * @brief Deep-first scheduling of a directed graph G with cycles
 *
 * @tparam N the type of nodes of G
 * @param G the graph we want to schedule
 * @return schedule<N> the deep first schedule of G
 */
template <typename N>
inline schedule<N> dfcyclesschedule(const digraph<N>& G)
{
    digraph<digraph<N>>  H  = graph2dag(G);
    schedule<digraph<N>> SH = dfschedule(H);
    schedule<N>          S;
    for (const digraph<N>& n : SH.elements()) {
        S.append(dfschedule(cut(n, 1)));
    }
    return S;
}

/**
 * @brief Breadth-first scheduling of a directed graph G with cycles
 *
 * @tparam N the type of nodes of G
 * @param G the graph we want to schedule
 * @return schedule<N> the deep first schedule of G
 */
template <typename N>
inline schedule<N> bfcyclesschedule(const digraph<N>& G)
{
    digraph<digraph<N>>  H  = graph2dag(G);
    schedule<digraph<N>> SH = bfschedule(H);
    schedule<N>          S;
    for (const digraph<N>& n : SH.elements()) {
        S.append(dfschedule(cut(n, 1)));
    }
    return S;
}

/**
 * @brief Model-constrained scheduling of a DAG G on an abstract machine
 * with R registers and U issue units.
 *
 * A list scheduler working in cycles of width U with unit latency: a node
 * issued in a cycle becomes usable as an operand in the NEXT cycle only.
 * A node is READY when all its destinations (its operands, since n->m
 * means "n depends on m") were issued in a previous cycle. A scheduled
 * node is LIVE while at least one of its consumers (its sources) is still
 * unscheduled -- the live count models register pressure.
 *
 * Two selection regimes, switching on the live count:
 *   live <  R : pick the ready node of greatest critical HEIGHT (the
 *               longest chain of dependents above it) -- widen the front,
 *               feed the units;
 *   live >= R : pick the ready node RELEASING the most registers (operands
 *               whose last pending consumer it is) -- narrow the front,
 *               free the bank.
 *
 * Ties anchor on the dfschedule order of G, so the result is stable
 * relative to graph iteration. Cyclic graphs are tolerated by a
 * deadlock-breaking fallback (issue the first unscheduled node in anchor
 * order, as dfschedule tolerates cycles); the full contract holds on DAGs.
 *
 * Complexity: O(V * cycles) candidate scans -- fine up to ~1e5 nodes.
 *
 * @tparam N the type of nodes of G
 * @param G the graph we want to schedule
 * @param R the register budget (live values) of the abstract machine
 * @param U the issue width (nodes per cycle) of the abstract machine
 * @return schedule<N> a valid schedule of G shaped by (R, U)
 */
template <typename N>
inline schedule<N> mcschedule(const digraph<N>& G, unsigned int R, unsigned int U)
{
    if (U < 1) {
        U = 1;
    }
    const schedule<N>&    anchor = dfschedule(G);
    const std::vector<N>& order  = anchor.elements();
    digraph<N>            Rg     = reverse(G);

    // critical height : 1 + max over consumers, computed consumers-first
    // (backward on the anchor, whose operands precede their consumers)
    std::map<N, int> height;
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        int h = 1;
        for (const auto& c : Rg.destinations(*it)) {
            auto hc = height.find(c.first);
            if (hc != height.end() && hc->second >= h) {
                h = hc->second + 1;
            }
        }
        height[*it] = h;
    }

    std::map<N, int> pending;  // remaining unscheduled consumers
    for (const N& n : order) {
        pending[n] = int(Rg.destinations(n).size());
    }

    schedule<N>  S;
    std::set<N>  done;  // issued in a COMPLETED cycle (usable as operand)
    unsigned int live = 0;

    auto ready = [&](const N& n) {
        if (S.order(n) > 0) {
            return false;
        }
        for (const auto& d : G.destinations(n)) {
            if (done.find(d.first) == done.end() && !(d.first == n)) {
                return false;
            }
        }
        return true;
    };

    auto issue = [&](const N& n) {
        S.append(n);
        if (pending[n] > 0) {
            live++;
        }
        for (const auto& d : G.destinations(n)) {
            if (!(d.first == n) && --pending[d.first] == 0) {
                if (live > 0) {
                    live--;
                }
            }
        }
    };

    while (S.size() < order.size()) {
        std::vector<N> cycle;
        for (unsigned int u = 0; u < U; u++) {
            const N* best  = nullptr;
            int      bestK = -1;
            for (const N& n : order) {
                if (!ready(n)) {
                    continue;
                }
                int k;
                if (live < R) {
                    k = height[n];
                } else {
                    k = 0;  // registers released by issuing n
                    for (const auto& d : G.destinations(n)) {
                        if (!(d.first == n) && pending[d.first] == 1) {
                            k++;
                        }
                    }
                }
                if (k > bestK) {
                    bestK = k;
                    best  = &n;
                }
            }
            if (best == nullptr) {
                break;
            }
            issue(*best);
            cycle.push_back(*best);
        }
        if (cycle.empty()) {
            // cyclic remainder : break the deadlock in anchor order
            for (const N& n : order) {
                if (S.order(n) == 0) {
                    issue(n);
                    cycle.push_back(n);
                    break;
                }
            }
        }
        for (const N& n : cycle) {
            done.insert(n);
        }
    }
    return S;
}

/**
 * @brief Compositional scheduling of a DAG G under (R, U) -- the schedule
 * is built by COMBINING sub-schedules along the DOMINATOR TREE, not by
 * picking from a global front.
 *
 * View (the filling-a-grid formulation): scheduling is filling a U x cycles
 * grid under a register constraint R, minimizing empty slots. The recursion
 * follows the structure of the expression: the block of a node n is the
 * fold of the blocks of its dominator-tree children (every node whose
 * value converges to n: its exclusive operands, and every shared operand
 * whose consumers all funnel through n), merged pairwise by an optimal
 * interleaving, with n appended last. The dominator tree makes the
 * cross-dependency story exact: a shared value is always a SIBLING block,
 * placed before its readers by the topological fold order.
 *
 * The pairwise merge is a dynamic program over the |A| x |B| grid that
 * preserves both internal orders, respects cross-dependencies, and
 * minimizes  BIG * over-pressure + stalls  where a stall is a node placed
 * immediately after one of its operands (the guaranteed empty slot of the
 * unit-latency machine). Ties prefer STAYING on the same sequence:
 * locality (blocks, and downstream the field layout that follows emission
 * order) is the default, interleaving the exception that pays -- either
 * by relieving pressure or by filling stalls.
 *
 * Degenerate cases: always-concatenate is df, always-alternate is bf.
 * DAG only (use graph2dag upstream for cyclic graphs). A pairwise merge
 * beyond ~4M DP cells falls back to concatenation (guarded, logged by
 * cost only).
 *
 * @tparam N the type of nodes of G
 * @param G the DAG we want to schedule
 * @param R the register budget (live values)
 * @param U the issue width (v1: the stall term models its effect)
 * @return schedule<N> a valid schedule of G
 */
template <typename N>
inline schedule<N> csschedule(const digraph<N>& G, unsigned int R, unsigned int U)
{
    (void)U;
    const schedule<N>     topo  = dfschedule(G);
    const std::vector<N>& order = topo.elements();  // operands first
    const int             V     = int(order.size());
    digraph<N>            Rg    = reverse(G);

    std::map<N, int> pos;
    for (int i = 0; i < V; i++) {
        pos[order[i]] = i;
    }
    auto consumers = [&](const N& n) -> const auto& { return Rg.destinations(n); };

    // ---- immediate dominators, flow entry -> consumers -> ... -> node.
    // Classic intersection algorithm; preds in the flow are the consumers,
    // the virtual ENTRY (index V) precedes every node without consumers.
    // Processing order: consumers first = reverse of `order`.
    std::vector<int> idom(V + 1, -1);
    idom[V] = V;
    auto intersect = [&](int a, int b) {
        // walk up; ENTRY has the SMALLEST consumers-first rank, i.e. the
        // LARGEST operand-first position -> compare by operand-first pos,
        // where entry(V) ranks above everything
        auto rank = [&](int x) { return (x == V) ? V : x; };
        while (a != b) {
            while (rank(a) < rank(b)) {
                a = idom[a];
            }
            while (rank(b) < rank(a)) {
                b = idom[b];
            }
        }
        return a;
    };
    for (int i = V - 1; i >= 0; i--) {
        const N& n   = order[i];
        int      nid = -1;
        if (consumers(n).empty()) {
            nid = V;
        } else {
            for (const auto& c : consumers(n)) {
                int cp = pos[c.first];
                if (idom[cp] == -1) {
                    continue;  // (cannot happen on a DAG)
                }
                nid = (nid == -1) ? cp : intersect(nid, cp);
            }
        }
        idom[i] = nid;
    }

    // ---- dominator-tree children, kept in operand-first order
    std::vector<std::vector<int>> children(V + 1);
    for (int i = 0; i < V; i++) {
        children[idom[i]].push_back(i);
    }

    // ---- the pairwise merge (DP with side-memory for the stall term)
    auto dpmerge = [&](std::vector<N> A, std::vector<N> B) -> std::vector<N> {
        const int na = int(A.size()), nb = int(B.size());
        if (na == 0) {
            return B;
        }
        if (nb == 0) {
            return A;
        }
        std::vector<N> cat;  // the guarded fallback: concatenation
        if (long(na + 1) * long(nb + 1) > 4000000L) {
            cat = A;
            cat.insert(cat.end(), B.begin(), B.end());
            return cat;
        }
        std::map<N, int> pA, pB;
        for (int i = 0; i < na; i++) {
            pA[A[i]] = i;
        }
        for (int j = 0; j < nb; j++) {
            pB[B[j]] = j;
        }
        // cross-deps: B[j] cannot precede its operands living in A
        std::vector<int> minI(nb, 0);
        for (int j = 0; j < nb; j++) {
            int need = (j > 0) ? minI[j - 1] : 0;
            for (const auto& d : G.destinations(B[j])) {
                auto it = pA.find(d.first);
                if (it != pA.end() && it->second + 1 > need) {
                    need = it->second + 1;
                }
            }
            minI[j] = need;
        }
        // liveness: last consumer coordinate on each side; a consumer
        // outside A and B keeps the value live for this whole merge
        std::map<N, int>  lastA, lastB;
        std::map<N, bool> ext;
        auto scan = [&](const N& x) {
            int la = -1, lb = -1;
            bool e = false;
            for (const auto& c : consumers(x)) {
                auto ia = pA.find(c.first);
                auto ib = pB.find(c.first);
                if (ia != pA.end()) {
                    la = std::max(la, ia->second);
                } else if (ib != pB.end()) {
                    lb = std::max(lb, ib->second);
                } else {
                    e = true;
                }
            }
            lastA[x] = la;
            lastB[x] = lb;
            ext[x]   = e;
        };
        for (const N& x : A) {
            scan(x);
        }
        for (const N& x : B) {
            scan(x);
        }
        std::vector<std::vector<int>> dieA(na), dieB(nb);  // indexes into A/B universe
        std::vector<N>                univ;
        univ.reserve(na + nb);
        univ.insert(univ.end(), A.begin(), A.end());
        univ.insert(univ.end(), B.begin(), B.end());
        for (const N& x : univ) {
            if (ext[x]) {
                continue;
            }
            int la = lastA[x], lb = lastB[x];
            if (la < 0 && lb < 0) {
                continue;  // never consumed here: never live in this merge
            }
            if (lb < 0) {
                dieA[la].push_back(pB.count(x) ? na + pB[x] : pA[x]);
            } else if (la < 0) {
                dieB[lb].push_back(pB.count(x) ? na + pB[x] : pA[x]);
            } else {
                dieA[la].push_back(pB.count(x) ? na + pB[x] : pA[x]);  // guarded by j at DP time
            }
        }
        auto liveAfter = [&](const N& u) {
            if (ext[u]) {
                return true;
            }
            return lastA[u] >= 0 || lastB[u] >= 0;
        };
        auto dependsOn = [&](const N& u, const N& v) {
            for (const auto& d : G.destinations(u)) {
                if (d.first == v) {
                    return true;
                }
            }
            return false;
        };
        const long      PBIG = 1000000L;
        const int       W    = nb + 1;
        const long      INF  = LONG_MAX / 4;
        std::vector<long> cost(size_t(na + 1) * W * 2, INF);
        std::vector<int>  live(size_t(na + 1) * W * 2, 0);
        std::vector<char> par(size_t(na + 1) * W * 2, 0);  // 1 from A, 2 from B
        auto id = [&](int i, int j, int s) { return (size_t(i) * W + j) * 2 + s; };
        cost[id(0, 0, 0)] = 0;
        for (int i = 0; i <= na; i++) {
            for (int j = 0; j <= nb; j++) {
                for (int s = 0; s < 2; s++) {
                    long c0 = cost[id(i, j, s)];
                    if (c0 >= INF) {
                        continue;
                    }
                    int l0 = live[id(i, j, s)];
                    const N* prev = nullptr;
                    if (i + j > 0) {
                        prev = (s == 0) ? (i > 0 ? &A[i - 1] : nullptr)
                                        : (j > 0 ? &B[j - 1] : nullptr);
                    }
                    auto relax = [&](int ni, int nj, int ns, const N& u,
                                     const std::vector<int>& dies, int dieGuardJ) {
                        int l = l0 + (liveAfter(u) ? 1 : 0);
                        for (int x : dies) {
                            int lbx = lastB[(x < na) ? A[x] : B[x - na]];
                            if (lbx < 0 || lbx <= dieGuardJ) {
                                l--;
                            }
                        }
                        long stall = (prev != nullptr && dependsOn(u, *prev)) ? 1 : 0;
                        long c     = c0 + PBIG * std::max(0, l - int(R)) + stall;
                        size_t k   = id(ni, nj, ns);
                        bool same  = (ns == s);  // prefer staying on a side
                        if (c < cost[k] || (c == cost[k] && same && par[k] == 0)) {
                            cost[k] = c;
                            live[k] = l;
                            par[k]  = char(s + 1);
                        }
                    };
                    if (i < na) {
                        relax(i + 1, j, 0, A[i], dieA.empty() ? std::vector<int>{} : dieA[i],
                              j - 1);
                    }
                    if (j < nb && minI[j] <= i) {
                        relax(i, j + 1, 1, B[j], dieB.empty() ? std::vector<int>{} : dieB[j],
                              j);
                    }
                }
            }
        }
        // best final state
        int  sEnd = (cost[id(na, nb, 0)] <= cost[id(na, nb, 1)]) ? 0 : 1;
        std::vector<N> merged;
        merged.reserve(na + nb);
        int i = na, j = nb, sc = sEnd;
        while (i > 0 || j > 0) {
            char p = par[id(i, j, sc)];
            if (sc == 0) {
                merged.push_back(A[--i]);
            } else {
                merged.push_back(B[--j]);
            }
            sc = (p == 1) ? 0 : (p == 2) ? 1 : sc;
        }
        std::reverse(merged.begin(), merged.end());
        return merged;
    };

    // ---- bottom-up along the dominator tree: operands-first order means
    // every dominated child block is complete before its dominator
    std::vector<std::vector<N>> block(V + 1);
    // fold the children of a dominator node. Children that no sibling
    // depends on and that depend on no sibling are INDEPENDENT: they are
    // interleaved by a REGULAR round-robin in batches of width <= R --
    // the memory-regular sweep (breadth-first's stride, the prefetcher's
    // friend, and the -ls engine's packet tiling rediscovered). Dependent
    // children (shared values and their readers) go through the DP merge
    // in topological order.
    auto foldChildren = [&](int d) {
        // membership of each node in a child block
        std::map<N, int> owner;
        for (int c : children[d]) {
            for (const N& x : block[c]) {
                owner[x] = c;
            }
        }
        std::set<int> dependent;
        for (int c : children[d]) {
            for (const N& x : block[c]) {
                for (const auto& dd : G.destinations(x)) {
                    auto o = owner.find(dd.first);
                    if (o != owner.end() && o->second != c) {
                        dependent.insert(c);          // reads a sibling
                        dependent.insert(o->second);  // is read by a sibling
                    }
                }
            }
        }
        std::vector<N> acc;
        std::vector<int> indep;
        for (int c : children[d]) {
            if (dependent.count(c)) {
                acc = dpmerge(std::move(acc), std::move(block[c]));
            } else {
                indep.push_back(c);
            }
        }
        // batches of independent siblings, regular round-robin inside
        size_t batchW = (R > 1) ? size_t(R) : 1;
        for (size_t b0 = 0; b0 < indep.size(); b0 += batchW) {
            size_t b1 = std::min(indep.size(), b0 + batchW);
            std::vector<N> rr;
            for (size_t k = 0;; k++) {
                bool any = false;
                for (size_t c = b0; c < b1; c++) {
                    const std::vector<N>& blk = block[indep[c]];
                    if (k < blk.size()) {
                        rr.push_back(blk[k]);
                        any = true;
                    }
                }
                if (!any) {
                    break;
                }
            }
            acc = dpmerge(std::move(acc), std::move(rr));
        }
        return acc;
    };
    for (int i = 0; i < V; i++) {
        std::vector<N> b = foldChildren(i);
        b.push_back(order[i]);
        block[i] = std::move(b);
    }
    std::vector<N> final_ = foldChildren(V);

    schedule<N> S;
    for (const N& n : final_) {
        S.append(n);
    }
    return S;
}

/**
 * @brief reverse breadth first schedule for a DAG
 *
 * @tparam N
 * @param G
 * @return schedule<N>
 */
template <typename N>
inline schedule<N> rbschedule(const digraph<N>& G)
{
    std::vector<std::vector<N>> P = parallelize(reverse(G));
    schedule<N>                 S;

    for (uint64_t i = 0; i < P.size(); i++) {
        for (const N& n : P[i]) {
            S.append(n);
        }
    }
    return S.reverse();
}
