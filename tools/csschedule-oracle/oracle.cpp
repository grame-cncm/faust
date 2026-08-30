// Scheduler validation oracle, stage 1. Exhaustive oracle on small DAGs:
// exact minimum cycles under (R,U) with hard R, computed by subset DP;
// current schedulers (dfschedule, the csschedule lab) replayed against
// it. Liveness convention, shared with the schedulers under test: global
// usage counts, net balance per op, sampled after each op.
//
// Build: clang++ -std=c++17 -O2 -I compiler/DirectedGraph \
//        tools/csschedule-oracle/oracle.cpp -o oracle

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

#include "DirectedGraph.hh"
#include "DirectedGraphAlgorythm.hh"
#include "Schedule.hh"

using G = digraph<int>;

// ---- DAG description: edges consumer -> operand (the compiler's G
// orientation: G.destinations(c) = operands of c)
struct Dag {
    std::string                      name;
    int                              n = 0;
    std::vector<std::pair<int, int>> deps;  // (consumer, operand)
    G                                graph() const
    {
        G g;
        for (int i = 0; i < n; i++) {
            g.add(i);
        }
        for (auto& e : deps) {
            g.add(e.first, e.second, 0);
        }
        return g;
    }
};

// ---- global usage counts (consumers per node)
static std::vector<int> usages(const Dag& d)
{
    std::vector<int> u(d.n, 0);
    for (auto& e : d.deps) {
        u[e.second]++;
    }
    return u;
}

// ---- replay a full order under (R,U): ASAP cycles, per-op liveness.
// Returns {cycles, peak, feasible under R}.
struct Replay {
    int  cycles = 0, peak = 0;
    bool underR = true, valid = true;  // valid: permutation + topology (spec par.10)
};
static Replay replay(const Dag& d, const std::vector<int>& order, int R, int U)
{
    // invariants 1-2: permutation of V, producers before consumers
    {
        std::vector<int> seen(d.n, 0);
        for (int o : order) {
            if (o < 0 || o >= d.n || seen[o]++) {
                Replay r;
                r.valid = false;
                return r;
            }
        }
        if (int(order.size()) != d.n) {
            Replay r;
            r.valid = false;
            return r;
        }
        std::vector<int> at(d.n);
        for (int i = 0; i < d.n; i++) {
            at[order[i]] = i;
        }
        for (auto& e : d.deps) {
            if (at[e.second] > at[e.first]) {
                Replay r;
                r.valid = false;
                return r;
            }
        }
    }
    std::vector<int>              use = usages(d);
    std::vector<std::vector<int>> ops(d.n);  // operands per consumer
    for (auto& e : d.deps) {
        ops[e.first].push_back(e.second);
    }
    std::vector<int> cyc(d.n, -1), consumed(d.n, 0);
    Replay           r;
    int              cur = 0, slots = 0, live = 0;
    for (int o : order) {
        int lo = 0;
        for (int p : ops[o]) {
            lo = std::max(lo, cyc[p] + 1);
        }
        if (lo > cur) {
            cur   = lo;
            slots = 0;
        } else if (slots == U) {
            cur++;
            slots = 0;
        }
        cyc[o] = cur;
        slots++;
        if (use[o] > 0) {
            live++;
        }
        for (int p : ops[o]) {
            if (++consumed[p] == use[p]) {
                live--;
            }
        }
        r.peak = std::max(r.peak, live);
        if (live > R) {
            r.underR = false;
        }
    }
    r.cycles = cur + 1;
    return r;
}

// ---- exact oracle: min cycles subject to peak <= R at every op, over all
// batch schedules (a batch = <= U ops, all ready at cycle start). Intra-
// batch order optimized exactly (brute force over <= U! permutations).
// Returns -1 if infeasible under R.
static int oracle(const Dag& d, int R, int U)
{
    const int        n = d.n;
    std::vector<int> use = usages(d);
    std::vector<uint32_t> depm(n, 0), consm(n, 0);
    for (auto& e : d.deps) {
        depm[e.first] |= 1u << e.second;
        consm[e.second] |= 1u << e.first;
    }
    auto liveOf = [&](uint32_t mask) {
        int l = 0;
        for (int i = 0; i < n; i++) {
            if ((mask >> i & 1) && use[i] > 0 && (consm[i] & ~mask)) {
                l++;
            }
        }
        return l;
    };
    // exact intra-batch peak for batch q emitted from state mask
    auto batchPeak = [&](uint32_t mask, std::vector<int>& q) {
        std::sort(q.begin(), q.end());
        int best = 1 << 30;
        do {
            int live = liveOf(mask), mx = live;
            uint32_t got = mask;
            for (int o : q) {
                got |= 1u << o;
                if (use[o] > 0) {
                    live++;
                }
                for (int i = 0; i < n; i++) {
                    if ((depm[o] >> i & 1) && use[i] > 0 && !(consm[i] & ~got)) {
                        // o was the last consumer of i overall
                        bool lastNow = true;
                        for (int c = 0; c < n; c++) {
                            if ((consm[i] >> c & 1) && !(got >> c & 1)) {
                                lastNow = false;
                            }
                        }
                        if (lastNow) {
                            live--;
                        }
                    }
                }
                mx = std::max(mx, live);
            }
            best = std::min(best, mx);
        } while (std::next_permutation(q.begin(), q.end()));
        return best;
    };
    const uint32_t   FULL = (n == 32) ? 0xffffffffu : ((1u << n) - 1);
    std::vector<int> g(1u << n, 1 << 30);
    g[0] = 0;
    for (uint32_t mask = 0; mask < FULL; mask++) {
        if (g[mask] >= (1 << 30)) {
            continue;
        }
        // ready ops: deps satisfied, not yet emitted
        std::vector<int> ready;
        for (int i = 0; i < n; i++) {
            if (!(mask >> i & 1) && (depm[i] & ~mask) == 0) {
                ready.push_back(i);
            }
        }
        int rn = int(ready.size());
        // enumerate non-empty subsets of ready of size <= U
        for (uint32_t s = 1; s < (1u << rn); s++) {
            if (__builtin_popcount(s) > U) {
                continue;
            }
            std::vector<int> q;
            uint32_t         qm = 0;
            for (int b = 0; b < rn; b++) {
                if (s >> b & 1) {
                    q.push_back(ready[b]);
                    qm |= 1u << ready[b];
                }
            }
            if (batchPeak(mask, q) > R) {
                continue;
            }
            uint32_t nm = mask | qm;
            g[nm]       = std::min(g[nm], g[mask] + 1);
        }
    }
    return g[FULL] >= (1 << 30) ? -1 : g[FULL];
}

// ---- families (spec §12) ------------------------------------------------
static Dag chainD(int n)
{
    Dag d{"chain" + std::to_string(n), n, {}};
    for (int i = 1; i < n; i++) {
        d.deps.push_back({i, i - 1});
    }
    return d;
}
static Dag btree(int depth)  // complete binary expression tree
{
    int n = (1 << (depth + 1)) - 1;
    Dag d{"btree" + std::to_string(depth), n, {}};
    // node i consumes 2i+1 and 2i+2 (heap layout, leaves last) — invert so
    // operands have smaller indices: relabel via reverse
    for (int i = 0; i < n / 2; i++) {
        int c = n - 1 - i, a = n - 1 - (2 * i + 1), b = n - 1 - (2 * i + 2);
        d.deps.push_back({c, a});
        d.deps.push_back({c, b});
    }
    return d;
}
static Dag fan(int k)  // k independent leaves folded by a chain of adds
{
    Dag d{"fan" + std::to_string(k), 2 * k - 1, {}};
    // leaves 0..k-1 ; adds k..2k-2 : add_j consumes (prev, leaf)
    int prev = 0;
    for (int j = 0; j < k - 1; j++) {
        int a = k + j;
        d.deps.push_back({a, prev});
        d.deps.push_back({a, j + 1});
        prev = a;
    }
    return d;
}
static Dag sharedxy()  // F(a(x), b(x)) — the spec's witness
{
    Dag d{"sharedFab", 4, {}};
    d.deps = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};  // x=0 a=1 b=2 F=3
    return d;
}
static Dag diamond(int levels)  // nested shared diamonds
{
    // level: x ; a(x), b(x) ; join(a,b) ; feed next level
    Dag d{"diamond" + std::to_string(levels), 0, {}};
    int prev = -1, id = 0;
    for (int l = 0; l < levels; l++) {
        int x = id++, a = id++, b = id++, j = id++;
        if (prev >= 0) {
            d.deps.push_back({x, prev});
        }
        d.deps.push_back({a, x});
        d.deps.push_back({b, x});
        d.deps.push_back({j, a});
        d.deps.push_back({j, b});
        prev = j;
    }
    d.n = id;
    return d;
}
static Dag bank(int k, int len)  // k chains of len feeding a fold chain
{
    Dag d{"bank" + std::to_string(k) + "x" + std::to_string(len), 0, {}};
    int              id = 0;
    std::vector<int> out;
    for (int c = 0; c < k; c++) {
        int prev = id++;
        for (int s = 1; s < len; s++) {
            d.deps.push_back({id, prev});
            prev = id++;
        }
        out.push_back(prev);
    }
    int acc = out[0];
    for (int c = 1; c < k; c++) {
        d.deps.push_back({id, acc});
        d.deps.push_back({id, out[c]});
        acc = id++;
    }
    d.n = id;
    return d;
}
static Dag multiout()  // one value read by two otherwise-disjoint outputs
{
    Dag d{"multiout", 7, {}};
    // x=0 shared ; chain1: 1->2 uses x ; chain2: 3->4 uses x ; outs 5,6
    d.deps = {{1, 0}, {2, 1}, {5, 2}, {3, 0}, {4, 3}, {6, 4}};
    return d;
}
static Dag randomDag(int n, int seed)  // deterministic LCG, operands earlier
{
    Dag      d{"rand" + std::to_string(n) + "s" + std::to_string(seed), n, {}};
    uint32_t s = uint32_t(seed) * 2654435761u + 12345u;
    auto     rnd = [&]() { return (s = s * 1664525u + 1013904223u) >> 16; };
    for (int i = 1; i < n; i++) {
        int k = 1 + int(rnd() % 2);  // 1-2 operands
        for (int j = 0; j < k; j++) {
            d.deps.push_back({i, int(rnd() % uint32_t(i))});
        }
    }
    std::sort(d.deps.begin(), d.deps.end());
    d.deps.erase(std::unique(d.deps.begin(), d.deps.end()), d.deps.end());
    return d;
}

int main()
{
    const int        U = 4;
    std::vector<Dag> dags = {sharedxy(),  multiout(),   chainD(8),  fan(6),
                             fan(10),     btree(3),     diamond(2), diamond(3),
                             bank(4, 3),  bank(3, 4),   bank(5, 2), randomDag(12, 1),
                             randomDag(12, 2), randomDag(14, 3), randomDag(14, 4),
                             randomDag(16, 5), randomDag(16, 6)};
    printf("%-12s %3s %2s | %6s | %-12s | %-12s | %-12s | %-12s\n", "dag", "n", "R",
           "oracle", "df", "cs", "cs2 K=1", "cs2 K=4");
    int total = 0;
    int opt_[4] = {0, 0, 0, 0}, ok_[4] = {0, 0, 0, 0};
    for (auto& d : dags) {
        G g = d.graph();
        for (int R : {4, 6, 8}) {
            int opt = oracle(d, R, U);
            const schedule<int> dfs  = dfschedule(g);
            const schedule<int> css  = csschedule(g, (unsigned)R, (unsigned)U);
            const schedule<int> cs21 = csschedule2(g, (unsigned)R, (unsigned)U, 1);
            const schedule<int> cs24 = csschedule2(g, (unsigned)R, (unsigned)U, 4);
            Replay r[4] = {replay(d, dfs.elements(), R, U),
                           replay(d, css.elements(), R, U),
                           replay(d, cs21.elements(), R, U),
                           replay(d, cs24.elements(), R, U)};
            printf("%-12s %3d %2d | %6s |", d.name.c_str(), d.n, R,
                   opt < 0 ? "infeas" : std::to_string(opt).c_str());
            for (int k = 0; k < 4; k++) {
                if (!r[k].valid) {
                    printf(" INVALIDE    |");
                } else {
                    printf(" %3d,%2d %-4s |", r[k].cycles, r[k].peak,
                           r[k].underR ? "" : "OVER");
                }
            }
            printf("\n");
            if (opt >= 0) {
                total++;
                for (int k = 0; k < 4; k++) {
                    if (r[k].valid && r[k].underR) {
                        ok_[k]++;
                        if (r[k].cycles == opt) {
                            opt_[k]++;
                        }
                    }
                }
            }
        }
    }
    const char* names[4] = {"df", "cs", "cs2K1", "cs2K4"};
    printf("\nfaisables: %d\n", total);
    for (int k = 0; k < 4; k++) {
        printf("  %-6s : optimal %2d/%d, sous R %2d/%d\n", names[k], opt_[k], total,
               ok_[k], total);
    }
    return 0;
}
