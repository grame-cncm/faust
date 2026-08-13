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
    std::map<N, int, dgorder<N>> fOrder;  // order of each element (starting at 1, 0 indicates not in schedule)

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
    std::set<N, dgorder<N>> V;  // set of visited nodes

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
    std::set<N, dgorder<N>> V;  // already scheduled nodes
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
    std::map<N, int, dgorder<N>> height;
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

    std::map<N, int, dgorder<N>> pending;  // remaining unscheduled consumers
    for (const N& n : order) {
        pending[n] = int(Rg.destinations(n).size());
    }

    schedule<N>  S;
    std::set<N, dgorder<N>>  done;  // issued in a COMPLETED cycle (usable as operand)
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
    // monochromatic RUNS : maximal sequences of same-shape nodes with no
    // direct dependency between consecutive elements (approximation of
    // superword packability : the vectorizer packs by groups of 4, so the
    // currency is the run-length DISTRIBUTION, not the sum of adjacencies
    // -- 600 adjacencies in runs of 2-3 are worthless, 500 in runs of 8
    // are gold)
    int packs4 = 0;  // complete groups of 4 : sum of len/4 over runs
    int r4n    = 0;  // nodes living in runs of length >= 4
    int maxrun = 1;  // longest run
    // critical-path DILATION : mean scheduled distance between consecutive
    // nodes of one longest dependency chain. Serial-bound programs lose
    // when the next chain step drifts beyond the out-of-order window
    // (whole layers inserted between two dependent steps expose the full
    // chain latency) ; bank-bound programs do not care
    int cpdil = 0;  // mean gap along the chain (schedule positions)
    int cpmax = 0;  // largest gap along the chain
    int cplen = 0;  // chain length (nodes)
    // two-resource machine (compute units U, memory ports M) : a schedule
    // cannot beat the per-resource floor II = max(nAlu/U, nMem/M) -- the
    // modulo-scheduling ResMII, one bound per typed resource. Optimizing a
    // resource below the BINDING bound is wasted work.
    int nmem   = 0;  // nodes classified memory
    int aluMII = 0;  // ceil(nAlu / U)
    int memMII = 0;  // ceil(nMem / M), 0 when no mem functor given
};

template <typename N>
inline schedquality squality(const digraph<N>& G, const std::vector<N>& S, unsigned int R,
                             unsigned int U, std::function<long(const N&)> shape = nullptr,
                             std::function<bool(const N&)> mem = nullptr, unsigned int M = 0)
{
    schedquality q;
    digraph<N>   Rg = reverse(G);
    std::map<N, int, dgorder<N>> cyc, pending;
    for (const N& n : S) {
        pending[n] = int(Rg.destinations(n).size());
    }
    int  cur = 0, slots = 0, live = 0;
    int  slotsM   = 0;  // memory ops issued in the current cycle
    bool twoRes   = (mem != nullptr) && (M > 0);
    int  run      = 0;
    auto closeRun = [&]() {
        if (run > 0) {
            q.packs4 += run / 4;
            q.maxrun = std::max(q.maxrun, run);
            if (run >= 4) {
                q.r4n += run;
            }
        }
    };
    for (size_t i = 0; i < S.size(); i++) {
        const N& n  = S[i];
        int      lo = 0;
        for (const auto& d : G.destinations(n)) {
            auto it = cyc.find(d.first);
            if (it != cyc.end()) {
                lo = std::max(lo, it->second + 1);
            }
        }
        bool isM = twoRes && mem(n);
        if (isM) {
            q.nmem++;
        }
        if (lo > cur) {
            q.holes += (lo - cur) * int(U) - slots;
            cur    = lo;
            slots  = 0;
            slotsM = 0;
        } else if ((!twoRes || !isM) && slots == int(U)) {
            cur++;
            slots  = 0;
            slotsM = 0;
        } else if (twoRes && isM && slotsM == int(M)) {
            cur++;
            slots  = 0;
            slotsM = 0;
        }
        cyc[n] = cur;
        if (isM) {
            slotsM++;
        } else {
            slots++;
        }
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
        bool extend = false;
        if (i > 0 && shape != nullptr && shape(S[i - 1]) == shape(n)) {
            bool dep = false;
            for (const auto& d : G.destinations(n)) {
                if (d.first == S[i - 1]) {
                    dep = true;
                }
            }
            if (!dep) {
                q.isoadj++;
                extend = true;
            }
        }
        if (extend) {
            run++;
        } else {
            closeRun();
            run = 1;
        }
    }
    closeRun();
    q.cycles = cur + 1;
    q.holes += int(U) - slots;
    {
        int nalu = int(S.size()) - q.nmem;
        q.aluMII = (U > 0) ? (nalu + int(U) - 1) / int(U) : 0;
        q.memMII = (M > 0) ? (q.nmem + int(M) - 1) / int(M) : 0;
    }
    // one longest chain, walked back through maximal-depth operands
    {
        std::map<N, int, dgorder<N>> pos, depth;
        for (size_t i = 0; i < S.size(); i++) {
            pos[S[i]] = int(i);
        }
        N    best  = S.empty() ? N() : S[0];
        int  bestd = -1;
        for (const N& n : S) {
            int d = 0;
            for (const auto& e : G.destinations(n)) {
                auto it = depth.find(e.first);
                if (it != depth.end()) {
                    d = std::max(d, it->second + 1);
                }
            }
            depth[n] = d;
            if (d > bestd) {
                bestd = d;
                best  = n;
            }
        }
        if (bestd > 0) {
            N    cur2 = best;
            long sum = 0;
            int  cnt = 0;
            while (depth[cur2] > 0) {
                N nxt = cur2;
                for (const auto& e : G.destinations(cur2)) {
                    auto it = depth.find(e.first);
                    if (it != depth.end() && it->second == depth[cur2] - 1) {
                        nxt = e.first;
                        break;
                    }
                }
                int gap = std::abs(pos[cur2] - pos[nxt]);
                sum += gap;
                q.cpmax = std::max(q.cpmax, gap);
                cnt++;
                cur2 = nxt;
            }
            q.cplen = cnt + 1;
            q.cpdil = int(sum / std::max(cnt, 1));
        }
    }
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
    std::map<N, int, dgorder<N>> pA, pB;
    for (int i = 0; i < na; i++) {
        pA[A[i]] = i;
    }
    for (int j = 0; j < nb; j++) {
        pB[B[j]] = j;
    }
    // global usage counts, and the positions of each value's consumers
    // inside A and inside B (for exact prefix-consumption counting)
    std::map<N, int, dgorder<N>>              usage;
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
 * @brief CSSCHEDULE v2 -- compositional scheduler of the spec in
 * faust-migration/CSSCHEDULE.md. Dominator-tree blocks, K-wide frontiers
 * of open traces, cycle-wide DP combination under (R,U), ASAP closure as
 * the only R certificate.
 *
 * Diversity (spec par.6 and par.9), third cut: the prefix-grid DP keeps
 * a PARETO BEAM of up to K (cycles, peak) entries per state -- the
 * spec's "K best paths", subsuming the two cost orders of the second
 * cut in a single run -- the plain concatenation joins as a structural
 * alternative, and every dominator node folds its children in two
 * orders (operand-first, then largest-frontier-first) when they differ.
 * Frontiers keep the K best distinct traces. Still deviating from the
 * full spec: no interface-signature diversity;
 * the R filter inside folds is a PRUNE (open inputs are not placed yet,
 * mid-fold peaks under-estimate) and CloseReplay alone certifies
 * peak <= R. A pair over the cell budget degrades to concatenation.
 */
// work accounting of one csschedule2 run : how many trace pairs were
// combined, how many degraded to concatenation (budget or pair cap), and
// how many grid cells were actually charged against the budget
struct cs2stats {
    long pairs    = 0;
    long degraded = 0;
    long cells    = 0;
};

template <typename N>
inline schedule<N> csschedule2(const digraph<N>& G, unsigned int R, unsigned int U,
                               unsigned int K = 4, bool* feasibleOut = nullptr,
                               long cellBudget = 8000000, cs2stats* statsOut = nullptr,
                               bool bfSpine = false)
{
    // The SPINE is the base topological order everything inherits from :
    // fold orders derive from it, the identity seed IS it, and above all
    // budget-degraded pairs concatenate segments shaped like it. df spine
    // (default) leans deep and local ; bf spine leans wide and parallel --
    // the DP refines either under (R,U) where the budget allows.
    const schedule<N>     topo  = bfSpine ? bfschedule(G) : dfschedule(G);
    const std::vector<N>& order = topo.elements();  // operands first
    const int             V     = int(order.size());
    digraph<N>            Rg    = reverse(G);

    std::map<N, int> pos;
    for (int i = 0; i < V; i++) {
        pos[order[i]] = i;
    }
    std::vector<std::vector<int>> ops(V), cons(V);
    std::vector<int>              usage(V, 0);
    for (int i = 0; i < V; i++) {
        for (const auto& d : G.destinations(order[i])) {
            ops[i].push_back(pos[d.first]);
        }
        for (const auto& c : Rg.destinations(order[i])) {
            cons[i].push_back(pos[c.first]);
        }
        usage[i] = int(cons[i].size());
    }

    // ---- immediate dominators (same construction as csschedule)
    std::vector<int> idom(V + 1, -1);
    idom[V] = V;
    auto intersect = [&](int a, int b) {
        while (a != b) {
            while (a < b) {
                a = idom[a];
            }
            while (b < a) {
                b = idom[b];
            }
        }
        return a;
    };
    for (int i = V - 1; i >= 0; i--) {
        int nid = -1;
        if (cons[i].empty()) {
            nid = V;
        } else {
            for (int c : cons[i]) {
                if (idom[c] != -1) {
                    nid = (nid == -1) ? c : intersect(nid, c);
                }
            }
            if (nid == -1) {
                nid = V;
            }
        }
        idom[i] = nid;
    }
    std::vector<std::vector<int>> children(V + 1);
    for (int i = 0; i < V; i++) {
        children[idom[i]].push_back(i);  // operand-first order
    }

    using Trace = std::vector<int>;
    struct Cand {
        Trace trace;
        int   cyc = 0, peak = 0;
    };

    // provisional (open) score of a trace: ASAP under U on its internal
    // deps, liveness with global usage counts (open inputs ignored)
    auto scoreTrace = [&](Cand& c) {
        std::vector<int>  cy(V, -1), consumed(V, 0);
        std::vector<char> inT(V, 0);
        for (int o : c.trace) {
            inT[o] = 1;
        }
        int cur = 0, slots = 0, live = 0, mx = 0;
        for (int o : c.trace) {
            int lo = 0;
            for (int d : ops[o]) {
                if (inT[d]) {
                    if (cy[d] < 0) {  // in-trace dep not yet emitted:
                        c.cyc  = 1 << 27;  // topology violated, bury it
                        c.peak = 1 << 27;
                        return;
                    }
                    lo = std::max(lo, cy[d] + 1);
                }
            }
            if (lo > cur) {
                cur   = lo;
                slots = 0;
            } else if (slots == int(U)) {
                cur++;
                slots = 0;
            }
            cy[o] = cur;
            slots++;
            if (usage[o] > 0) {
                live++;
            }
            for (int d : ops[o]) {
                if (inT[d] && ++consumed[d] == usage[d] && usage[d] > 0) {
                    live--;
                }
            }
            mx = std::max(mx, live);
        }
        c.cyc  = c.trace.empty() ? 0 : cur + 1;
        c.peak = mx;
    };

    const long PAIRCAP    = 4000000;   // per-pair memory guard
    long       cellsLeft  = cellBudget;  // global work budget (spec par.11)
    cs2stats   stats;                    // work accounting for this run

    // ---- the cycle-wide DP on the prefix grid, with a PARETO BEAM of up
    // to K (cycles, peak) entries per state -- the spec's "K best paths"
    // (par.6). All insertions into a state happen before it is processed
    // (transitions strictly increase (i,j)), so each beam is finalized
    // exactly once and entry indices stay stable for the backtracks.
    auto dpBeam = [&](const Trace& A, const Trace& B, bool filterR,
                      std::vector<Cand>& outv) -> bool {
        const int        m = int(A.size()), n = int(B.size());
        std::vector<int> inA(V, -1), inB(V, -1);
        for (int i = 0; i < m; i++) {
            inA[A[i]] = i;
        }
        for (int j = 0; j < n; j++) {
            inB[B[j]] = j;
        }
        auto placed = [&](int d, int i, int j) {
            if (inA[d] >= 0) {
                return inA[d] < i;
            }
            if (inB[d] >= 0) {
                return inB[d] < j;
            }
            return true;  // open input: owned above, no obligation here
        };
        auto deathsAt = [&](int o, int i, int j) {
            int dth = 0;
            for (int d : ops[o]) {
                int consumedNow = 0;
                for (int c : cons[d]) {
                    if ((inA[c] >= 0 && inA[c] < i) || (inB[c] >= 0 && inB[c] < j) ||
                        c == o) {
                        consumedNow++;
                    }
                }
                if (consumedNow == usage[d]) {
                    dth++;
                }
            }
            return dth;
        };
        auto orderBatch = [&](std::vector<int>& batch, int i, int j) {
            std::sort(batch.begin(), batch.end(), [&](int a, int b) {
                int da = (usage[a] ? 1 : 0) - deathsAt(a, i, j);
                int db = (usage[b] ? 1 : 0) - deathsAt(b, i, j);
                return da != db ? da < db : a < b;
            });
        };
        auto evalBatch = [&](int i, int j, int x, int y, int liveIn, int& net) {
            std::vector<int> batch;
            for (int k = 0; k < x; k++) {
                batch.push_back(A[i + k]);
            }
            for (int k = 0; k < y; k++) {
                batch.push_back(B[j + k]);
            }
            for (int o : batch) {
                for (int d : ops[o]) {
                    if ((inA[d] >= 0 || inB[d] >= 0) && !placed(d, i, j)) {
                        return -1;
                    }
                }
            }
            orderBatch(batch, i, j);
            int              live = liveIn, mx = liveIn;
            std::vector<int> placedBatch;
            for (int o : batch) {
                if (usage[o] > 0) {
                    live++;
                }
                for (int d : ops[o]) {
                    int consumed = 0;
                    for (int c : cons[d]) {
                        bool inPref =
                            (inA[c] >= 0 && inA[c] < i) || (inB[c] >= 0 && inB[c] < j);
                        bool inBat = false;
                        for (int pb : placedBatch) {
                            if (pb == c) {
                                inBat = true;
                            }
                        }
                        if (inPref || inBat || c == o) {
                            consumed++;
                        }
                    }
                    if (usage[d] > 0 && consumed == usage[d]) {
                        live--;
                    }
                }
                placedBatch.push_back(o);
                mx = std::max(mx, live);
            }
            net = live - liveIn;
            return mx;
        };
        struct Ent {
            int   cyc, pk, par, pei;
            short act;
        };
        const int      W  = n + 1;
        const int      NS = (m + 1) * W;
        const unsigned BW = std::max(1u, K);  // beam width
        std::vector<std::vector<Ent>> beam(NS), pend(NS);
        std::vector<int>              lv(NS, -1);
        pend[0].push_back({0, 0, -1, -1, short(-1)});
        lv[0] = 0;
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                int s = i * W + j;
                if (!pend[s].empty()) {
                    std::sort(pend[s].begin(), pend[s].end(), [](const Ent& a, const Ent& b) {
                        return a.cyc != b.cyc ? a.cyc < b.cyc : a.pk < b.pk;
                    });
                    int minPk = 1 << 30;
                    for (Ent& e : pend[s]) {
                        if (e.pk < minPk && beam[s].size() < BW) {
                            beam[s].push_back(e);  // Pareto front, capped
                            minPk = e.pk;
                        }
                    }
                    pend[s].clear();
                    pend[s].shrink_to_fit();
                }
                if (beam[s].empty()) {
                    continue;
                }
                for (int x = 0; x <= std::min<int>(U, m - i); x++) {
                    for (int y = (x == 0) ? 1 : 0; x + y <= int(U) && y <= n - j; y++) {
                        int net = 0;
                        int mx  = evalBatch(i, j, x, y, lv[s], net);
                        if (mx < 0) {
                            break;  // batch prefix not ready: larger y neither
                        }
                        if (filterR && mx > int(R)) {
                            continue;
                        }
                        int t = (i + x) * W + (j + y);
                        if (lv[t] < 0) {
                            lv[t] = lv[s] + net;  // set-determined
                        }
                        for (size_t ei = 0; ei < beam[s].size(); ei++) {
                            const Ent& e = beam[s][ei];
                            pend[t].push_back({e.cyc + 1, std::max(e.pk, mx), s, int(ei),
                                               short(x * (U + 1) + y)});
                        }
                    }
                }
            }
        }
        int fs = m * W + n;
        if (beam[fs].empty()) {
            return false;
        }
        for (const Ent& fe : beam[fs]) {
            std::vector<std::pair<int, int>> steps;
            const Ent*                       e = &fe;
            while (e->par >= 0) {
                steps.push_back({e->act / (U + 1), e->act % (U + 1)});
                e = &beam[e->par][e->pei];
            }
            std::reverse(steps.begin(), steps.end());
            Cand c;
            int  i = 0, j = 0;
            for (auto& st : steps) {
                std::vector<int> batch;
                for (int k = 0; k < st.first; k++) {
                    batch.push_back(A[i + k]);
                }
                for (int k = 0; k < st.second; k++) {
                    batch.push_back(B[j + k]);
                }
                orderBatch(batch, i, j);
                for (int o : batch) {
                    c.trace.push_back(o);
                }
                i += st.first;
                j += st.second;
            }
            c.cyc  = fe.cyc;
            c.peak = fe.pk;
            outv.push_back(std::move(c));
        }
        return true;
    };

    // concatenation A-then-B is a candidate only when valid : no op of A
    // may depend on an op of B (possible under the alternate fold order,
    // where a block precedes a shared value it reads)
    auto concatCand = [&](const Trace& A, const Trace& B, std::vector<Cand>& out) {
        std::vector<char> inB(V, 0);
        for (int o : B) {
            inB[o] = 1;
        }
        for (int o : A) {
            for (int d : ops[o]) {
                if (inB[d]) {
                    return;  // invalid concatenation, skip
                }
            }
        }
        Cand c;
        c.trace = A;
        c.trace.insert(c.trace.end(), B.begin(), B.end());
        scoreTrace(c);
        out.push_back(std::move(c));
    };

    // ---- combine two disjoint traces: up to three diverse candidates
    auto combine = [&](const Trace& A, const Trace& B) -> std::vector<Cand> {
        if (A.empty() || B.empty()) {
            Cand c;
            c.trace = A.empty() ? B : A;
            scoreTrace(c);
            return {c};
        }
        const long cost = long(A.size() + 1) * long(B.size() + 1);
        stats.pairs++;
        if (cost > PAIRCAP || cost > cellsLeft) {
            stats.degraded++;
            std::vector<Cand> deg;  // budget exhausted: degrade to concat
            concatCand(A, B, deg);
            if (deg.empty()) {
                concatCand(B, A, deg);  // acyclicity: one direction is valid
            }
            return deg;
        }
        cellsLeft -= cost;
        stats.cells += cost;
        std::vector<Cand> out;
        if (!dpBeam(A, B, true, out)) {
            if (cost <= cellsLeft) {
                cellsLeft -= cost;
                stats.cells += cost;
                dpBeam(A, B, false, out);  // no R-feasible path: unfiltered
            }
        }
        concatCand(A, B, out);
        return out;
    };

    // rank by (cycles, peak), drop duplicate traces, keep K
    auto dedupTrim = [&](std::vector<Cand>& v) {
        std::sort(v.begin(), v.end(), [](const Cand& a, const Cand& b) {
            return a.cyc != b.cyc ? a.cyc < b.cyc : a.peak < b.peak;
        });
        std::set<size_t>  seen;
        std::vector<Cand> out;
        for (auto& c : v) {
            size_t h = 1469598103934665603ull;
            for (int o : c.trace) {
                h = (h ^ size_t(o)) * 1099511628211ull;
            }
            if (seen.insert(h).second) {
                out.push_back(std::move(c));
            }
            if (out.size() >= K) {
                break;
            }
        }
        v = std::move(out);
    };

    // ---- frontier fold (spec par.7), two child orders when they differ
    std::vector<std::vector<Cand>> frontier(V + 1);
    auto foldOrder = [&](const std::vector<int>& kids) {
        std::vector<Cand> F{Cand{}};
        for (int ch : kids) {
            std::vector<Cand> nf;
            for (const Cand& f : F) {
                for (const Cand& t : frontier[ch]) {
                    for (Cand& c : combine(f.trace, t.trace)) {
                        nf.push_back(std::move(c));
                    }
                }
            }
            dedupTrim(nf);
            F = std::move(nf);
        }
        return F;
    };
    auto foldNode = [&](int d) {
        const std::vector<int>& kids = children[d];
        std::vector<Cand>       F    = foldOrder(kids);
        auto                    childSize = [&](int a) {
            return frontier[a].empty() ? size_t(0) : frontier[a][0].trace.size();
        };
        size_t total = 0;
        for (int ch : kids) {
            total += childSize(ch);
        }
        // alternate fold orders only while the fold stays affordable :
        // beyond the threshold the primary order alone is explored
        if (kids.size() > 2 && total <= 1200 && cellsLeft > 0) {
            std::vector<std::vector<int>> alts;
            {
                std::vector<int> byBig = kids;  // largest child frontier first
                std::stable_sort(byBig.begin(), byBig.end(),
                                 [&](int a, int b) { return childSize(a) > childSize(b); });
                alts.push_back(std::move(byBig));
                std::vector<int> bySmall = kids;  // smallest first
                std::stable_sort(bySmall.begin(), bySmall.end(),
                                 [&](int a, int b) { return childSize(a) < childSize(b); });
                alts.push_back(std::move(bySmall));
                std::vector<int> rev = kids;  // reversed operand order
                std::reverse(rev.begin(), rev.end());
                alts.push_back(std::move(rev));
            }
            for (auto& alt : alts) {
                if (alt != kids) {
                    std::vector<Cand> F2 = foldOrder(alt);
                    for (Cand& c : F2) {
                        F.push_back(std::move(c));
                    }
                }
            }
            dedupTrim(F);
        }
        return F;
    };
    for (int i = 0; i < V; i++) {  // operand-first: children before idom
        std::vector<Cand> F = foldNode(i);
        for (Cand& f : F) {
            f.trace.push_back(i);  // "f suivie de d"
            scoreTrace(f);
        }
        dedupTrim(F);
        frontier[i] = std::move(F);
    }
    std::vector<Cand> C = foldNode(V);

    // ---- ensemble seeding: the existing family's traces join the
    // candidates before closure, so csschedule2 never returns worse than
    // the best of the portfolio on any instance
    {
        Cand cdf;  // the spine = the identity over `order`
        for (int i = 0; i < V; i++) {
            cdf.trace.push_back(i);
        }
        scoreTrace(cdf);
        C.push_back(std::move(cdf));
        const schedule<N> lab = csschedule(G, R, U);
        Cand              clab;
        for (const N& n2 : lab.elements()) {
            clab.trace.push_back(pos[n2]);
        }
        scoreTrace(clab);
        C.push_back(std::move(clab));
    }

    // ---- closure: ASAP cycles under U, global liveness, hard R (par.6-7)
    auto closeReplay = [&](const Trace& T, int& cycOut, int& pkOut) {
        std::vector<int> cy(V, -1), consumed(V, 0);
        int              cur = 0, slots = 0, live = 0, mx = 0;
        for (int o : T) {
            int lo = 0;
            for (int d : ops[o]) {
                lo = std::max(lo, cy[d] + 1);
            }
            if (lo > cur) {
                cur   = lo;
                slots = 0;
            } else if (slots == int(U)) {
                cur++;
                slots = 0;
            }
            cy[o] = cur;
            slots++;
            if (usage[o] > 0) {
                live++;
            }
            for (int d : ops[o]) {
                if (++consumed[d] == usage[d] && usage[d] > 0) {
                    live--;
                }
            }
            mx = std::max(mx, live);
        }
        cycOut = cur + 1;
        pkOut  = mx;
        return mx <= int(R);
    };
    int  bestIdx = -1, bestCyc = 1 << 28, bestPk = 1 << 28;
    bool feasible = false;
    for (size_t k = 0; k < C.size(); k++) {
        int  cy2 = 0, pk2 = 0;
        bool ok = closeReplay(C[k].trace, cy2, pk2);
        if (ok && (!feasible || cy2 < bestCyc || (cy2 == bestCyc && pk2 < bestPk))) {
            feasible = true;
            bestIdx  = int(k);
            bestCyc  = cy2;
            bestPk   = pk2;
        }
        if (!feasible && bestIdx == -1) {
            bestIdx = int(k);  // provisional: best-ranked even if over R
        }
    }
    if (feasibleOut) {
        *feasibleOut = feasible;
    }
    if (statsOut) {
        *statsOut = stats;
    }
    schedule<N> S;
    if (bestIdx >= 0) {
        for (int o : C[bestIdx].trace) {
            S.append(order[o]);
        }
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
                                unsigned int bankcap = 0, int stagec = 0,
                                bool stats = false)
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
    if (stagec == 2) {
        // layers mode : natural levels untouched (the frequency grouping
        // pulls instances OFF their level and dephases their operand
        // lanes -- bf keeps levels intact, we keep bf's phase and only
        // sort colors inside each level)
        for (int i = 0; i < V; i++) {
            target[i] = asap[i];
        }
    } else
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
    if (stats) {
        // NATURAL bank widths : (rank, shape) group sizes before capping --
        // the antichain width per class, the statistic the auto-cap needs
        std::map<std::pair<int, long>, int> nat;
        for (int i = 0; i < V; i++) {
            nat[{rank[i], shapeOf[i]}]++;
        }
        std::map<int, int> hist;
        for (const auto& [k, c] : nat) {
            hist[c]++;
        }
        std::cerr << "SS_BANKSTATS widths:";
        int shown = 0;
        for (auto it = hist.rbegin(); it != hist.rend() && shown < 8; ++it, ++shown) {
            std::cerr << " " << it->first << "x" << it->second;
        }
        std::cerr << std::endl;
    }
    const size_t cap = (stagec == 2) ? size_t(V)
                       : (bankcap > 0) ? bankcap
                                       : std::max<size_t>(1, std::max(R, U));
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
    // stagec selects the composition of the bank dag : 0 = csschedule
    // (default) ; 1 = dfschedule -- pure VERTICAL column chaining, the
    // phase-coherence experiment (consecutive layers of one family stay
    // inside the SLP scheduling window)
    schedule<int> BS;
    if (stagec == 2) {
        // layers : banks in (rank, class frequency) order -- level-major
        // emission, colors grouped inside each level
        std::vector<int> bk(members.size());
        for (size_t b = 0; b < members.size(); b++) {
            bk[b] = int(b);
        }
        std::map<long, int> freq;
        for (int i = 0; i < V; i++) {
            freq[shapeOf[i]]++;
        }
        std::sort(bk.begin(), bk.end(), [&](int a, int b) {
            int ra = rank[members[a][0]], rb2 = rank[members[b][0]];
            if (ra != rb2) {
                return ra < rb2;
            }
            long sa = shapeOf[members[a][0]], sb = shapeOf[members[b][0]];
            if (freq[sa] != freq[sb]) {
                return freq[sa] > freq[sb];
            }
            return sa < sb;
        });
        for (int b : bk) {
            BS.append(b);
        }
    } else {
        BS = (stagec == 1) ? dfschedule(B) : csschedule(B, Rb, U, bankShape);
    }

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
