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
 * is built by COMBINING sub-schedules, not by picking from a global front.
 *
 * View (the filling-a-grid formulation): scheduling is filling a U x cycles
 * grid under a register constraint R, minimizing empty slots. The recursion
 * follows the expression structure of the DAG made explicit by its LETS:
 * every node with several consumers (or none: a final root) is a let;
 * every other node belongs to the REGION of its unique consumer's let.
 *
 *   1. each region is scheduled by dfschedule -- a contiguous block with
 *      perfect operand locality (and, downstream, field-layout locality,
 *      since declarations follow emission order);
 *   2. the lets are folded in dependencies-first order, each region being
 *      merged into the accumulated schedule by an OPTIMAL pairwise
 *      interleaving: a dynamic program over the |A| x |B| grid that
 *      preserves both internal orders, respects cross-dependencies
 *      (a B node cannot precede its A operands), minimizes the summed
 *      over-pressure max(0, live - R), and among equal-cost paths prefers
 *      ALTERNATION (fill the issue slots with independent work).
 *
 * Locality is thus the default (df blocks), interleaving the exception,
 * decided where it pays. Degenerate cases: a combine that always
 * concatenates is df; one that always alternates level-by-level is bf.
 *
 * DAG only (use graph2dag upstream for cyclic graphs).
 * Complexity: O(V^2) overall (each pairwise DP is |acc| x |region|).
 *
 * @tparam N the type of nodes of G
 * @param G the DAG we want to schedule
 * @param R the register budget (live values)
 * @param U the issue width (only steers the alternation preference in v1)
 * @return schedule<N> a valid schedule of G
 */
template <typename N>
inline schedule<N> csschedule(const digraph<N>& G, unsigned int R, unsigned int U)
{
    (void)U;  // v1: alternation preference; a finer hole model may use U
    const schedule<N>&    topo  = dfschedule(G);
    const std::vector<N>& order = topo.elements();
    digraph<N>            Rg    = reverse(G);

    // lets: several consumers, or none (final roots)
    auto nconsumers = [&](const N& n) { return int(Rg.destinations(n).size()); };
    std::map<N, N> letOf;
    for (const N& n : order) {  // operands before consumers: memo is ready
        letOf.emplace(n, n);
    }
    // a single-consumer node belongs to its consumer's let -- computed
    // consumers-first (backward on the topological order)
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        if (nconsumers(*it) == 1) {
            const N& c   = Rg.destinations(*it).begin()->first;
            letOf.at(*it) = letOf.at(c);
        }
    }

    // per-let region, in topological order of the lets
    std::vector<N>                lets;
    std::map<N, std::vector<int>> unused;  // silence some compilers
    std::map<N, std::vector<N>>   region;
    for (const N& n : order) {
        const N& L = letOf.at(n);
        if (region.find(L) == region.end()) {
            lets.push_back(L);
        }
        region[L].push_back(n);  // topological inside the region
    }

    // fold: merge each region into the accumulated sequence by DP
    std::vector<N>   acc;
    std::map<N, int> posInAcc;
    for (const N& L : lets) {
        const std::vector<N>& B  = region[L];
        const int             nb = int(B.size());
        const int             na = int(acc.size());
        if (na == 0) {
            acc = B;
            for (int j = 0; j < nb; j++) {
                posInAcc[B[j]] = j;
            }
            continue;
        }
        // cross-dependencies: B[j] needs its operands in acc placed first
        std::vector<int> minI(nb, 0);
        std::map<N, int> posInB;
        for (int j = 0; j < nb; j++) {
            posInB[B[j]] = j;
        }
        for (int j = 0; j < nb; j++) {
            int need = (j > 0) ? minI[j - 1] : 0;
            for (const auto& d : G.destinations(B[j])) {
                auto pa = posInAcc.find(d.first);
                if (pa != posInAcc.end() && pa->second + 1 > need) {
                    need = pa->second + 1;
                }
            }
            minI[j] = need;
        }
        // liveness bookkeeping for the DP: a node is dead once ALL its
        // consumers are in the combined prefix ; consumers in future lets
        // keep it alive throughout this combine (hasExt)
        auto tag = [&](const std::vector<N>& S, std::map<N, int>& pos,
                       std::vector<std::vector<int>>& diesAt, std::vector<bool>& alive) {
            diesAt.assign(S.size(), {});
            alive.assign(S.size(), false);
            (void)pos;
        };
        (void)tag;
        // last consumer positions of every prefix node, split by side
        std::map<N, int>  lastA, lastB;
        std::map<N, bool> hasExt;
        auto scan = [&](const N& x) {
            int la = -1, lb = -1;
            bool ext = false;
            for (const auto& c : Rg.destinations(x)) {
                auto ia = posInAcc.find(c.first);
                auto ib = posInB.find(c.first);
                if (ia != posInAcc.end()) {
                    la = std::max(la, ia->second);
                } else if (ib != posInB.end()) {
                    lb = std::max(lb, ib->second);
                } else {
                    ext = true;
                }
            }
            lastA[x] = la;
            lastB[x] = lb;
            hasExt[x] = ext;
        };
        for (const N& x : acc) {
            scan(x);
        }
        for (const N& x : B) {
            scan(x);
        }
        // deaths triggered when crossing row i (adding acc[i]) or column j
        std::vector<std::vector<N>> deathA(na), deathB(nb);
        auto classify = [&](const N& x) {
            if (hasExt[x]) {
                return;  // stays live for this whole combine
            }
            int la = lastA[x], lb = lastB[x];
            auto ia = posInAcc.find(x);
            int  self = (ia != posInAcc.end()) ? ia->second : -1;
            if (self > la && posInB.find(x) == posInB.end()) {
                la = self;  // a value exists only once placed
            }
            auto ib2 = posInB.find(x);
            if (ib2 != posInB.end() && ib2->second > lb) {
                lb = ib2->second;
            }
            if (la >= 0 && lb < 0) {
                deathA[la].push_back(x);
            } else if (lb >= 0 && la < 0) {
                deathB[lb].push_back(x);
            } else if (la >= 0 && lb >= 0) {
                // dies when BOTH coordinates passed: attach to the A side,
                // guarded by the B coordinate at DP time
                deathA[la].push_back(x);
            }
        };
        for (const N& x : acc) {
            classify(x);
        }
        for (const N& x : B) {
            classify(x);
        }
        auto hasAnyConsumer = [&](const N& x) { return nconsumers(x) > 0 || hasExt[x]; };

        // the DP grid: cost = summed over-pressure, prefer alternation
        const int      W = nb + 1;
        std::vector<long>    cost((na + 1) * W, LONG_MAX);
        std::vector<int>     live((na + 1) * W, 0);
        std::vector<char>    from((na + 1) * W, 0);  // 1: from A, 2: from B
        auto idx = [&](int i, int j) { return i * W + j; };
        cost[idx(0, 0)] = 0;
        auto deltaLive = [&](const N& u, int i, int j) {
            // adding u to prefix (i, j) : +1 if it will be consumed later,
            // -1 for each of its prefix operands whose last consumer it is
            int d = hasAnyConsumer(u) ? 1 : 0;
            (void)i;
            (void)j;
            return d;
        };
        (void)deltaLive;
        for (int i = 0; i <= na; i++) {
            for (int j = 0; j <= nb; j++) {
                long c0 = cost[idx(i, j)];
                if (c0 == LONG_MAX) {
                    continue;
                }
                int l0 = live[idx(i, j)];
                // advance A
                if (i < na) {
                    const N& u = acc[i];
                    int      l = l0 + (hasAnyConsumer(u) ? 1 : 0);
                    for (const N& x : deathA[i]) {
                        if (lastB.count(x) == 0 || lastB[x] < 0 || lastB[x] <= j - 1) {
                            l--;
                        }
                    }
                    // deaths of B side waiting on this A coordinate
                    for (int jj = 0; jj < j; jj++) {
                        (void)jj;
                    }
                    long pen = std::max(0, l - int(R));
                    long c   = c0 + pen;
                    int  k   = idx(i + 1, j);
                    bool alt = (from[idx(i, j)] == 2);
                    if (c < cost[k] || (c == cost[k] && alt && from[k] != 1)) {
                        cost[k] = c;
                        live[k] = l;
                        from[k] = 1;
                    }
                }
                // advance B (cross-deps permitting)
                if (j < nb && minI[j] <= i) {
                    const N& u = B[j];
                    int      l = l0 + (hasAnyConsumer(u) ? 1 : 0);
                    for (const N& x : deathB[j]) {
                        if (lastA.count(x) == 0 || lastA[x] < 0 || lastA[x] <= i - 1) {
                            l--;
                        }
                    }
                    long pen = std::max(0, l - int(R));
                    long c   = c0 + pen;
                    int  k   = idx(i, j + 1);
                    bool alt = (from[idx(i, j)] == 1);
                    if (c < cost[k] || (c == cost[k] && alt && from[k] != 2)) {
                        cost[k] = c;
                        live[k] = l;
                        from[k] = 2;
                    }
                }
            }
        }
        // reconstruct
        std::vector<N> merged;
        merged.reserve(na + nb);
        int i = na, j = nb;
        while (i > 0 || j > 0) {
            if (from[idx(i, j)] == 1) {
                merged.push_back(acc[--i]);
            } else {
                merged.push_back(B[--j]);
            }
        }
        std::reverse(merged.begin(), merged.end());
        acc = merged;
        posInAcc.clear();
        for (int k = 0; k < int(acc.size()); k++) {
            posInAcc[acc[k]] = k;
        }
    }

    schedule<N> S;
    for (const N& n : acc) {
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
