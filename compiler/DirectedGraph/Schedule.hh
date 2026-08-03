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
/**
 * @brief Quality vector of a schedule on the (R, U) abstract machine:
 * cycles and holes from a greedy packing under unit latency, register
 * over-pressure, and the count of ADJACENT ISOMORPHIC INDEPENDENT pairs
 * (the superword-vectorization opportunities: same shape, no dependency).
 * The shape of a node is given by the optional functor (nullptr: every
 * node has its own shape, isoadj is then always 0).
 */
struct schedquality {
    int  cycles = 0;
    int  holes  = 0;
    int  peak   = 0;
    long over   = 0;
    int  isoadj = 0;
};

template <typename N>
inline schedquality squality(const digraph<N>& G, const std::vector<N>& S, unsigned int R,
                             unsigned int U, std::function<long(const N&)> shape = nullptr)
{
    schedquality q;
    digraph<N>   Rg = reverse(G);
    std::map<N, int> cyc, pending;
    for (const N& n : S) {
        pending[n] = int(Rg.destinations(n).size());
    }
    int cur = 0, slots = 0, live = 0;
    for (size_t i = 0; i < S.size(); i++) {
        const N& n  = S[i];
        int      lo = 0;
        for (const auto& d : G.destinations(n)) {
            auto it = cyc.find(d.first);
            if (it != cyc.end()) {
                lo = std::max(lo, it->second + 1);
            }
        }
        if (lo > cur) {
            q.holes += (lo - cur) * int(U) - slots;
            cur   = lo;
            slots = 0;
        } else if (slots == int(U)) {
            cur++;
            slots = 0;
        }
        cyc[n] = cur;
        slots++;
        if (pending[n] > 0) {
            live++;
        }
        for (const auto& d : G.destinations(n)) {
            if (--pending[d.first] == 0) {
                live--;
            }
        }
        q.peak = std::max(q.peak, live);
        q.over += std::max(0, live - int(R));
        if (i > 0 && shape != nullptr && shape(S[i - 1]) == shape(n)) {
            bool dep = false;
            for (const auto& d : G.destinations(n)) {
                if (d.first == S[i - 1]) {
                    dep = true;
                }
            }
            if (!dep) {
                q.isoadj++;
            }
        }
    }
    q.cycles = cur + 1;
    q.holes += int(U) - slots;
    return q;
}

/**
 * @brief Optimal-ish pairwise interleaving of two DISJOINT sequences over
 * G under R -- the COMBINE at the heart of compositional scheduling.
 *
 * Liveness is founded on GLOBAL USAGE COUNTS (the in-degree of each value
 * in the whole graph: its number of distinct consumers): a placed value is
 * live while its consumed-count within the merged prefix is below its
 * global usage -- values with consumers outside A and B therefore remain
 * live through the whole merge, and deaths are EXACT (a value dies when
 * its last GLOBAL consumer is placed). This makes the operator
 * independent of any folding-order invariant: constraints are BILATERAL
 * (a node of either side waits for its operands on the other side), so
 * combine(A, B) and combine(B, A) face symmetric problems -- the partial
 * commutativity of the trace monoid, restored.
 *
 * Both internal orders are preserved; the DP minimizes
 *   BIG * over-pressure + stalls + iso-misses
 * (stall: node right after one of its operands; iso-miss: an adjacency
 * that could have been isomorphic-independent, when a shape functor is
 * given). Ties prefer staying on the same sequence: locality by default,
 * interleaving where it pays.
 */
template <typename N>
inline std::vector<N> dpcombine(const digraph<N>& G, const digraph<N>& Rg, std::vector<N> A,
                                std::vector<N> B, unsigned int R,
                                std::function<long(const N&)> shape = nullptr)
{
    const int na = int(A.size()), nb = int(B.size());
    if (na == 0) {
        return B;
    }
    if (nb == 0) {
        return A;
    }
    if (long(na + 1) * long(nb + 1) > 4000000L) {
        std::vector<N> cat = A;
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
    // global usage counts, and the positions of each value's consumers
    // inside A and inside B (for exact prefix-consumption counting)
    std::map<N, int>              usage;
    std::map<N, std::vector<int>> consA, consB;
    auto note = [&](const N& x) {
        if (usage.count(x)) {
            return;
        }
        usage[x] = int(Rg.destinations(x).size());
        for (const auto& c : Rg.destinations(x)) {
            auto ia = pA.find(c.first);
            auto ib = pB.find(c.first);
            if (ia != pA.end()) {
                consA[x].push_back(ia->second);
            } else if (ib != pB.end()) {
                consB[x].push_back(ib->second);
            }
        }
        std::sort(consA[x].begin(), consA[x].end());
        std::sort(consB[x].begin(), consB[x].end());
    };
    for (const N& x : A) {
        note(x);
    }
    for (const N& x : B) {
        note(x);
    }
    auto countLE = [](const std::vector<int>& v, int lim) {
        return int(std::upper_bound(v.begin(), v.end(), lim) - v.begin());
    };
    // consumed count of x in the prefix (i first of A, j first of B)
    auto consumed = [&](const N& x, int i, int j) {
        return countLE(consA[x], i - 1) + countLE(consB[x], j - 1);
    };
    // BILATERAL cross-constraints: a node waits for its operands living on
    // the other side
    std::vector<int> minI(nb, 0), minJ(na, 0);
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
    for (int i = 0; i < na; i++) {
        int need = (i > 0) ? minJ[i - 1] : 0;
        for (const auto& d : G.destinations(A[i])) {
            auto it = pB.find(d.first);
            if (it != pB.end() && it->second + 1 > need) {
                need = it->second + 1;
            }
        }
        minJ[i] = need;
    }
    auto dependsOn = [&](const N& u, const N& v) {
        for (const auto& d : G.destinations(u)) {
            if (d.first == v) {
                return true;
            }
        }
        return false;
    };
    const long PBIG = 1000000L, STALL = 3, ISOMISS = 2;
    const int  W    = nb + 1;
    const long INF  = LONG_MAX / 4;
    std::vector<long> cost(size_t(na + 1) * W * 2, INF);
    std::vector<int>  live(size_t(na + 1) * W * 2, 0);
    std::vector<char> par(size_t(na + 1) * W * 2, 0);
    auto id = [&](int i, int j, int s) { return (size_t(i) * W + j) * 2 + s; };
    cost[id(0, 0, 0)] = 0;
    for (int i = 0; i <= na; i++) {
        for (int j = 0; j <= nb; j++) {
            for (int s = 0; s < 2; s++) {
                long c0 = cost[id(i, j, s)];
                if (c0 >= INF) {
                    continue;
                }
                int      l0   = live[id(i, j, s)];
                const N* prev = nullptr;
                if (i + j > 0) {
                    prev = (s == 0) ? (i > 0 ? &A[i - 1] : nullptr)
                                    : (j > 0 ? &B[j - 1] : nullptr);
                }
                auto relax = [&](int ni, int nj, int ns, const N& u) {
                    // exact liveness from the usage counters: placing u
                    // makes it live iff consumers remain beyond the new
                    // prefix; each operand whose LAST global consumer is u
                    // (within this prefix) dies
                    int l = l0 + ((usage[u] - consumed(u, ni, nj) > 0) ? 1 : 0);
                    for (const auto& d : G.destinations(u)) {
                        const N& x = d.first;
                        if (x == u || (!pA.count(x) && !pB.count(x))) {
                            continue;
                        }
                        if (consumed(x, ni, nj) == usage[x]) {
                            // u completed x's global consumption iff x was
                            // still live just before
                            if (usage[x] - consumed(x, i, j) > 0) {
                                l--;
                            }
                        }
                    }
                    long pen = PBIG * std::max(0, l - int(R));
                    if (prev != nullptr) {
                        if (dependsOn(u, *prev)) {
                            pen += STALL;
                        } else if (shape != nullptr && shape(u) != shape(*prev)) {
                            pen += ISOMISS;
                        }
                    }
                    long   c    = c0 + pen;
                    size_t k    = id(ni, nj, ns);
                    bool   same = (ns == s);
                    if (c < cost[k] || (c == cost[k] && same && par[k] == 0)) {
                        cost[k] = c;
                        live[k] = l;
                        par[k]  = char(s + 1);
                    }
                };
                if (i < na && minJ[i] <= j) {
                    relax(i + 1, j, 0, A[i]);
                }
                if (j < nb && minI[j] <= i) {
                    relax(i, j + 1, 1, B[j]);
                }
            }
        }
    }
    int sEnd = (cost[id(na, nb, 0)] <= cost[id(na, nb, 1)]) ? 0 : 1;
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
}

template <typename N>
inline schedule<N> csschedule(const digraph<N>& G, unsigned int R, unsigned int U,
                              std::function<long(const N&)> shape = nullptr)
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

    // ---- the pairwise merge: the library operator (usage-count exact)
    auto dpmerge = [&](std::vector<N> A, std::vector<N> B) {
        return dpcombine(G, Rg, std::move(A), std::move(B), R, shape);
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
 * @brief Shape-ALIGNED scheduling of a DAG G -- Yann's alignment step.
 *
 * View the shapes as colors : a schedule is well aligned when equal colors
 * are grouped in monochromatic RANKS instead of dispersed. A rank being an
 * antichain by construction, the mutual independence of a bank's instances
 * is structural -- ranks of one shape are exactly the banks the superword
 * vectorizer wants, in runs whose LENGTH is the packing currency.
 *
 * Algorithm (v1) :
 *   1. mobility intervals [ASAP, ALAP] for every node (topological levels
 *      at the earliest / latest) ;
 *   2. shape classes by DECREASING frequency ; each class groups its
 *      instances on the fewest possible ranks given the intervals -- the
 *      polynomial interval-stabbing greedy (sort by ALAP, place a rank at
 *      each uncovered instance). Frequent colors are served first,
 *      singletons fill the gaps ;
 *   3. robust emission : target ranks are PRIORITIES in a Kahn descent
 *      (among ready nodes, smallest (targetRank, shape, anchor) wins) --
 *      validity by construction, monochromatic runs emerge.
 *
 * Breadth-first is the color-blind special case (pure ASAP) : it aligns
 * banks only when the program happens to put them at equal depths ; this
 * step does it on purpose. Cyclic graphs tolerated like dfschedule
 * (back edges ignored by the level computation, deadlock-broken in Kahn).
 */
template <typename N>
inline schedule<N> alignschedule(const digraph<N>& G, std::function<long(const N&)> shape)
{
    const schedule<N>     topo  = dfschedule(G);
    const std::vector<N>& order = topo.elements();  // operands first
    const int             V     = int(order.size());
    digraph<N>            Rg    = reverse(G);
    std::map<N, int>      pos;
    for (int i = 0; i < V; i++) {
        pos[order[i]] = i;
    }

    // ---- mobility intervals (back edges ignored : an operand placed
    // AFTER its consumer in the anchor is a cycle edge)
    std::vector<int> asap(V, 0), alap(V, 0);
    int              maxRank = 0;
    for (int i = 0; i < V; i++) {
        int lo = 0;
        for (const auto& d : G.destinations(order[i])) {
            auto it = pos.find(d.first);
            if (it != pos.end() && it->second < i) {
                lo = std::max(lo, asap[it->second] + 1);
            }
        }
        asap[i] = lo;
        maxRank = std::max(maxRank, lo);
    }
    for (int i = V - 1; i >= 0; i--) {
        int hi = maxRank;
        for (const auto& c : Rg.destinations(order[i])) {
            auto it = pos.find(c.first);
            if (it != pos.end() && it->second > i) {
                hi = std::min(hi, alap[it->second] - 1);
            }
        }
        alap[i] = std::max(hi, asap[i]);
    }

    // ---- shape classes by decreasing frequency
    std::map<long, std::vector<int>> classes;
    std::vector<long>                shapeOf(V);
    for (int i = 0; i < V; i++) {
        shapeOf[i] = shape ? shape(order[i]) : long(i);
        classes[shapeOf[i]].push_back(i);
    }
    std::vector<std::pair<int, long>> byFreq;
    for (const auto& [sh, v] : classes) {
        byFreq.push_back({int(v.size()), sh});
    }
    std::sort(byFreq.begin(), byFreq.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });

    // ---- per class : group on the fewest ranks (interval stabbing)
    // per-class grouping, EARLIEST placement : instances are grouped while
    // their intervals keep a common rank, and the group takes the earliest
    // rank its members allow (the v1 latest-placement variant hoarded --
    // values were kept alive to meet late color ranks, downstream stalled :
    // vocoder fill 49 %)
    std::vector<int> target(V, 0);
    for (const auto& [cnt, sh] : byFreq) {
        std::vector<int> inst = classes[sh];
        std::sort(inst.begin(), inst.end(),
                  [&](int a, int b) { return asap[a] < asap[b]; });
        size_t g0 = 0;
        while (g0 < inst.size()) {
            int lo = asap[inst[g0]], hi = alap[inst[g0]];
            size_t g1 = g0 + 1;
            while (g1 < inst.size() && asap[inst[g1]] <= hi) {
                lo = std::max(lo, asap[inst[g1]]);
                hi = std::min(hi, alap[inst[g1]]);
                g1++;
            }
            for (size_t k = g0; k < g1; k++) {
                target[inst[k]] = lo;  // earliest common rank
            }
            g0 = g1;
        }
    }

    // ---- Kahn with (target, shape, anchor) priority
    std::vector<int> pending(V, 0);
    for (int i = 0; i < V; i++) {
        for (const auto& d : G.destinations(order[i])) {
            auto it = pos.find(d.first);
            if (it != pos.end() && it->second < i) {
                pending[i]++;
            }
        }
    }
    auto        cmp = [&](int a, int b) {
        if (target[a] != target[b]) {
            return target[a] > target[b];  // min-heap on target rank
        }
        if (shapeOf[a] != shapeOf[b]) {
            return shapeOf[a] > shapeOf[b];
        }
        return a > b;  // anchor position
    };
    std::vector<int> heap;
    for (int i = 0; i < V; i++) {
        if (pending[i] == 0) {
            heap.push_back(i);
        }
    }
    std::make_heap(heap.begin(), heap.end(), cmp);
    schedule<N> S;
    while (int(S.size()) < V) {
        if (heap.empty()) {  // cyclic remainder : deadlock-break in anchor order
            for (int i = 0; i < V; i++) {
                if (S.order(order[i]) == 0) {
                    S.append(order[i]);
                    break;
                }
            }
            continue;
        }
        std::pop_heap(heap.begin(), heap.end(), cmp);
        int n = heap.back();
        heap.pop_back();
        if (S.order(order[n]) > 0) {
            continue;
        }
        S.append(order[n]);
        for (const auto& c : Rg.destinations(order[n])) {
            auto it = pos.find(c.first);
            if (it != pos.end() && it->second > n && --pending[it->second] == 0) {
                heap.push_back(it->second);
                std::push_heap(heap.begin(), heap.end(), cmp);
            }
        }
    }
    return S;
}

/**
 * @brief Bank-compositional scheduling -- alignment THEN composition,
 * the two steps that were competing strategies composed as intended :
 * all composition happens under constraint (R, U), simply on a DAG
 * previously ALIGNED by shapes.
 *
 * Stage A (alignment as ANALYSIS, not order) : mobility intervals and
 * earliest-common-rank grouping as in alignschedule, but the output is
 * target ranks, not a schedule.
 *
 * Stage B (legalization + condensation) : final ranks are recomputed in
 * topological order as max(target, 1 + rank of dependencies), so every
 * edge STRICTLY increases the rank. Members that drift lose their bank
 * but validity is structural. Nodes are then grouped by (rank, shape) :
 * each bank is an antichain (one rank = no internal edges) and the
 * quotient DAG is acyclic (edges strictly decrease rank), by
 * construction -- no verification pass needed. A bank is the native
 * superword unit : isomorphic independent instructions emitted as one
 * contiguous run.
 *
 * Stage C (composition under constraint) : csschedule on the bank DAG
 * -- dominator association, batched round-robin, DP merges -- decides
 * WHERE banks go, never whether they exist. On singleton-shape regions
 * (deep recurrences) banks have size 1 and the stage degenerates into
 * plain csschedule ; on repeated-shape regions the colors can no longer
 * be dispersed. The align-vs-cs selection becomes local and automatic.
 *
 * Note : R now counts pressure in BANKS, not values -- a deliberate
 * coarsening for this first version.
 */
template <typename N>
inline schedule<N> bankschedule(const digraph<N>& G, unsigned int R, unsigned int U,
                                std::function<long(const N&)> shape,
                                unsigned int bankcap = 0)
{
    const schedule<N>     topo  = dfschedule(G);
    const std::vector<N>& order = topo.elements();  // operands first
    const int             V     = int(order.size());
    digraph<N>            Rg    = reverse(G);
    std::map<N, int>      pos;
    for (int i = 0; i < V; i++) {
        pos[order[i]] = i;
    }

    // ---- stage A : mobility + earliest-common-rank targets (alignschedule)
    std::vector<int> asap(V, 0), alap(V, 0);
    int              maxRank = 0;
    for (int i = 0; i < V; i++) {
        int lo = 0;
        for (const auto& d : G.destinations(order[i])) {
            auto it = pos.find(d.first);
            if (it != pos.end() && it->second < i) {
                lo = std::max(lo, asap[it->second] + 1);
            }
        }
        asap[i] = lo;
        maxRank = std::max(maxRank, lo);
    }
    for (int i = V - 1; i >= 0; i--) {
        int hi = maxRank;
        for (const auto& c : Rg.destinations(order[i])) {
            auto it = pos.find(c.first);
            if (it != pos.end() && it->second > i) {
                hi = std::min(hi, alap[it->second] - 1);
            }
        }
        alap[i] = std::max(hi, asap[i]);
    }
    std::map<long, std::vector<int>> classes;
    std::vector<long>                shapeOf(V);
    for (int i = 0; i < V; i++) {
        shapeOf[i] = shape ? shape(order[i]) : long(i);
        classes[shapeOf[i]].push_back(i);
    }
    std::vector<std::pair<int, long>> byFreq;
    for (const auto& [sh, v] : classes) {
        byFreq.push_back({int(v.size()), sh});
    }
    std::sort(byFreq.begin(), byFreq.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });
    std::vector<int> target(V, 0);
    for (const auto& [cnt, sh] : byFreq) {
        std::vector<int> inst = classes[sh];
        std::sort(inst.begin(), inst.end(),
                  [&](int a, int b) { return asap[a] < asap[b]; });
        size_t g0 = 0;
        while (g0 < inst.size()) {
            int    lo = asap[inst[g0]], hi = alap[inst[g0]];
            size_t g1 = g0 + 1;
            while (g1 < inst.size() && asap[inst[g1]] <= hi) {
                lo = std::max(lo, asap[inst[g1]]);
                hi = std::min(hi, alap[inst[g1]]);
                g1++;
            }
            for (size_t k = g0; k < g1; k++) {
                target[inst[k]] = lo;
            }
            g0 = g1;
        }
    }

    // ---- stage B : legalization (edges strictly increase the rank)
    std::vector<int> rank(V, 0);
    for (int i = 0; i < V; i++) {
        int lo = target[i];
        for (const auto& d : G.destinations(order[i])) {
            auto it = pos.find(d.first);
            if (it != pos.end() && it->second < i) {
                lo = std::max(lo, rank[it->second] + 1);
            }
        }
        rank[i] = lo;
    }
    // banks by (rank, shape) ; members kept in anchor order. A bank is
    // CAPPED at max(R, U) members : a contiguous run keeps all its values
    // live, so an uncapped bank would override the R constraint stage C is
    // in charge of (on wide chain families the R-tiling must emerge from
    // the composition, not be crushed by a giant bank) ; U floors the cap
    // so runs stay superword-packable when R is small.
    const size_t cap = (bankcap > 0) ? bankcap : std::max<size_t>(1, std::max(R, U));
    std::map<std::pair<int, long>, int> bankOf;
    std::vector<std::vector<int>>       members;
    std::vector<int>                    bankIx(V);
    for (int i = 0; i < V; i++) {
        auto key = std::make_pair(rank[i], shapeOf[i]);
        auto it  = bankOf.find(key);
        if (it == bankOf.end() || members[it->second].size() >= cap) {
            if (it != bankOf.end()) {
                bankOf.erase(it);
            }
            it = bankOf.insert({key, int(members.size())}).first;
            members.push_back({});
        }
        bankIx[i] = it->second;
        members[it->second].push_back(i);
    }
    digraph<int> B;
    for (int b = 0; b < int(members.size()); b++) {
        B.add(b);
    }
    for (int i = 0; i < V; i++) {
        for (const auto& d : G.destinations(order[i])) {
            auto it = pos.find(d.first);
            if (it != pos.end() && it->second < i && bankIx[i] != bankIx[it->second]) {
                B.add(bankIx[i], bankIx[it->second], 0);
            }
        }
    }

    // ---- stage C : composition under constraint on the bank DAG.
    // Stage C counts pressure in BANKS while R counts values : with banks
    // of up to `cap` values each, the value budget R converts to a bank
    // budget R/cap (uniform-size approximation) -- this is what lets the
    // R-tiling of wide chain families emerge from the composition.
    unsigned int Rb = std::max<unsigned int>(1, R / unsigned(cap));
    auto bankShape = std::function<long(const int&)>(
        [&](const int& b) { return shapeOf[members[b][0]]; });
    schedule<int> BS = csschedule(B, Rb, U, bankShape);

    schedule<N> S;
    for (const int& b : BS.elements()) {
        for (int i : members[b]) {
            S.append(order[i]);
        }
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
