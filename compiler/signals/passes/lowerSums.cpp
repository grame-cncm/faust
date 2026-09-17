#include "lowerSums.hh"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <optional>
#include <tuple>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>

#include "sigs-state.hh"
#include "rewrite.hh"

//----------------------------------------------------------------------
// lowerSums v2 : signed butterfly extraction (the ±1 factorization)
//----------------------------------------------------------------------
//
// The flat sums of the reveal are rows of a {-1,0,+1} matrix over a pool
// of ATOMS (terms with their sign stripped : -1*x is atom x, sign -).
// The v1 co-occurrence pairing failed on FDN matrices because the sign
// distribution makes +d and -d distinct trees -- no literal pair left.
// The ±1-specific insight : a pair (a,b) is counted MODULO SIGN, and the
// extraction materializes the sum s=a+b AND the difference d=a-b
// together -- every row is then served whatever its sign pattern
// (+a+b -> s, +a-b -> d, -a+b -> -d, -a-b -> -s). Applied greedily and
// recursively, this rebuilds the Walsh-Hadamard butterfly from the
// flattened matrix : H4 goes from 12 additions to 8, fdnRev's target is
// 3056 -> ~823. The algorithm is its own detector : it extracts while
// the net gain (rows served minus adders spent) is positive, and
// degenerates into the canonical comb when no signed pair repeats.
//
// Ties follow the stages. On a Hadamard matrix every pair of inputs has
// the same net gain at the start, and breaking the tie by the canonical
// tree order pairs inputs across unrelated stages : the synthesized atoms
// then rarely meet in the same rows, and the extraction drifts away from
// n.log2(n) as n grows (x2.7 at n = 128). A pair splits the rows into the
// ones using a+b and the ones using a-b ; two pairs with the SAME split
// produce atoms that co-occur in every row, and pair again at the next
// stage. The tie is therefore broken first by the number of already
// extracted pairs whose split this pair repeats, then by the canonical
// order : the butterfly is recovered whatever the order of the atoms.

namespace {

// order-free hash of a set of row indices, accumulated one row at a time
inline uint64_t rowKey(size_t r)
{
    uint64_t z = uint64_t(r) + 0x9e3779b97f4a7c15ULL;
    z          = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z          = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return z ^ (z >> 31);
}

struct Atom {
    Tree t;
    int  sign;  // +1 / -1
};

using Row = std::vector<Atom>;

// deterministic unordered-pair key (both components in treeorder)
using TPair = std::pair<Tree, Tree>;

struct PairOrder {
    bool operator()(const TPair& a, const TPair& b) const
    {
        treeorder lt;
        if (lt(a.first, b.first)) {
            return true;
        }
        if (lt(b.first, a.first)) {
            return false;
        }
        return lt(a.second, b.second);
    }
};

// strip the sign of a term : -1*x (either operand order) is (x, -1)
Atom atomOf(Tree t)
{
    Tree a, b;
    if (isSigMul(t, a, b) && isMinusOne(a)) {
        return {b, -1};
    }
    if (isSigMul(t, a, b) && isMinusOne(b)) {
        return {a, -1};
    }
    return {t, +1};
}

// rebuild a signed row as binary adds/subs : canonically-sorted positives
// first (left comb), then canonically-sorted negatives as subtractions
Tree rebuildRow(const Row& row)
{
    treeorder         lt;
    std::vector<Tree> pos, neg;
    for (const Atom& a : row) {
        (a.sign > 0 ? pos : neg).push_back(a.t);
    }
    std::sort(pos.begin(), pos.end(), lt);
    std::sort(neg.begin(), neg.end(), lt);
    Tree   acc;
    size_t k = 0;
    if (!pos.empty()) {
        acc = pos[0];
        for (size_t i = 1; i < pos.size(); i++) {
            acc = sigAdd(acc, pos[i]);
        }
    } else {
        acc = sigMul(sigInt(-1), neg[0]);
        k   = 1;
    }
    for (; k < neg.size(); k++) {
        acc = sigSub(acc, neg[k]);
    }
    return acc;
}

}  // namespace

// synthesized butterfly atoms : placeholder -> (left, right, isAdd)
static std::map<Tree, std::tuple<Tree, Tree, bool>, treeorder> gSynth;

Tree lowerSums(Tree L, const std::set<Tree>* keep)
{
    gSynth.clear();
    // ---- collect the distinct Sum nodes and their signed rows
    std::vector<Tree> sums;
    std::vector<Row>  rows;
    {
        std::set<Tree>    seen;
        std::vector<Tree> work{L};
        while (!work.empty()) {
            Tree t = work.back();
            work.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree var, body;
            if (isRec(t, var, body)) {
                if (body) {
                    work.push_back(body);
                }
                continue;
            }
            if (tvec subs; isSigSum(t, subs) && !(keep && keep->count(t))) {
                Row row;
                for (Tree s : subs) {
                    row.push_back(atomOf(s));
                }
                sums.push_back(t);
                rows.push_back(std::move(row));
            }
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
        }
    }
    if (sums.empty()) {
        return L;
    }

    // ---- greedy signed extraction, all rows mutated simultaneously
    struct Count {
        int      cpos = 0;  // rows using the a+b combination
        int      cneg = 0;  // rows using the a-b combination
        uint64_t hpos = 0;  // hash of the set of rows using a+b
        uint64_t hneg = 0;  // hash of the set of rows using a-b
    };
    treeorder             lt;
    std::vector<uint64_t> splits;  // the a+b row sets of the extracted pairs
    for (int guard = 0; guard < 4096; guard++) {
        // count the signed pairs over every row
        std::map<TPair, Count, PairOrder> count;
        for (size_t r = 0; r < rows.size(); r++) {
            const Row&     row = rows[r];
            const uint64_t key = rowKey(r);
            for (size_t i = 0; i < row.size(); i++) {
                for (size_t j = i + 1; j < row.size(); j++) {
                    if (row[i].t == row[j].t) {
                        continue;
                    }
                    Tree a = row[i].t, b = row[j].t;
                    int  sa = row[i].sign, sb = row[j].sign;
                    if (lt(b, a)) {
                        std::swap(a, b);
                        std::swap(sa, sb);
                    }
                    Count& c = count[{a, b}];
                    if (sa * sb > 0) {
                        c.cpos++;
                        c.hpos += key;
                    } else {
                        c.cneg++;
                        c.hneg += key;
                    }
                }
            }
        }
        // the number of extracted pairs whose row split this pair repeats
        auto aligned = [&splits](const Count& c) {
            int n = 0;
            for (uint64_t h : splits) {
                n += (c.cpos > 0 && h == c.hpos) || (c.cneg > 0 && h == c.hneg);
            }
            return n;
        };
        // best net gain : rows served minus adders materialized ; ties go to
        // the most aligned pair, then to the first in canonical order
        int   best      = 0;
        int   bestAlign = 0;
        TPair bkey{nullptr, nullptr};
        for (const auto& [key, c] : count) {
            int net = c.cpos + c.cneg - (c.cpos > 0) - (c.cneg > 0);
            if (net <= 0 || net < best) {
                continue;
            }
            int al = aligned(c);
            if (net > best || al > bestAlign) {
                best      = net;
                bestAlign = al;
                bkey      = key;
            }
        }
        if (best <= 0) {
            break;
        }
        {
            const Count& c = count[bkey];
            if (c.cpos > 0) {
                splits.push_back(c.hpos);
            }
        }
        // materialize s = a+b and/or d = a-b, rewrite every row. The
        // synthetic atoms are PLACEHOLDER trees registered in gSynth :
        // their real form is rebuilt at rewrite time from the RESOLVED
        // operands (so inner lowered sums land inside them correctly).
        Tree a = bkey.first, b = bkey.second;
        Tree s = nullptr, d = nullptr;
        for (Row& row : rows) {
            int ia = -1, ib = -1;
            for (size_t i = 0; i < row.size(); i++) {
                if (row[i].t == a && ia < 0) {
                    ia = int(i);
                } else if (row[i].t == b && ib < 0) {
                    ib = int(i);
                }
            }
            if (ia < 0 || ib < 0) {
                continue;
            }
            int  sa = row[ia].sign, sb = row[ib].sign;
            Atom merged;
            if (sa * sb > 0) {
                if (!s) {
                    s          = sigAdd(a, b);
                    gSynth[s]  = {a, b, true};
                }
                merged = {s, sa};
            } else {
                if (!d) {
                    d          = sigSub(a, b);
                    gSynth[d]  = {a, b, false};
                }
                merged = {d, sa};
            }
            row[ia] = merged;
            row.erase(row.begin() + ib);
        }
    }

    // ---- rewrite : every Sum node becomes its factored binary form.
    // Paired traversal : the rule matches on the ORIGINAL Sum pointer and
    // resolves each atom through the traversal memo (an atom that is
    // itself a lowered inner Sum maps to its image ; a synthesized s/d
    // atom rebuilds from its resolved operands -- hash-consing shares the
    // result across rows, which is the whole point).
    std::map<size_t, size_t> dummy;
    std::map<Tree, size_t, treeorder> sumIndex;
    for (size_t k = 0; k < sums.size(); k++) {
        sumIndex[sums[k]] = k;
    }
    std::unordered_map<Tree, Tree> memo;

    std::function<Tree(Tree)> resolve = [&](Tree t) -> Tree {
        auto sy = gSynth.find(t);
        if (sy != gSynth.end()) {
            Tree l = resolve(std::get<0>(sy->second));
            Tree r = resolve(std::get<1>(sy->second));
            return std::get<2>(sy->second) ? sigAdd(l, r) : sigSub(l, r);
        }
        auto it = memo.find(t);
        return (it != memo.end()) ? it->second : t;
    };

    auto pre     = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    auto rule    = [&](Tree orig, Tree rebuilt) -> Tree {
        auto it = sumIndex.find(orig);
        if (it == sumIndex.end()) {
            return rebuilt;
        }
        Row resolved;
        for (const Atom& a : rows[it->second]) {
            resolved.push_back({resolve(a.t), a.sign});
        }
        return rebuildRow(resolved);
    };
    return treeRewritePairedMemo(L, pre, rule, memo, defRule);
}
