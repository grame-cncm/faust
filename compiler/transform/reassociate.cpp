#include "reassociate.hh"

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "global.hh"

//----------------------------------------------------------------------
// Late state-join reassociation
//----------------------------------------------------------------------
//
// The normal form's association of sums is an accident of the canonical
// order ; in a recurrence-bound loop the association IS the performance :
// every add that separates the state read from the state write is a cycle
// of recMII no scheduler can remove. The micro-benchmarks (exp-reassoc)
// established the reduced scope :
//
//   - off-path balancing is USELESS (clang and the out-of-order hardware
//     do it : comb/tree ratio 1.00 in both flag regimes) ;
//   - the JOIN PLACEMENT is worth x4 without -ffast-math, and clang's
//     rescue under fast-math gives up on complex chains (korg35) ;
//
// STATUS after the full investigation (2026-08-09) : correct (0
// duplications corpus-wide by the state-count detector, 0 recMII
// regressions, 10 model-level improvements) but runtime-MARGINAL on the
// corpus (freeverb -6%, pluckedString -8% fast, others +/-3%) : real
// programs' long sums feed through DELAYS (memory reads, off the
// zero-delay cycle), so the x4 micro-bench scenario (long zero-delay
// add-chain into state) is rare. The FDN knots' sums live in multi-def
// groups, which V1 deliberately does not reassociate. Kept experimental :
// the correct tool for a rare disease, and the doctrine carrier (content
// vs shape, late join) for the emission work to come.
//
// so the pass does exactly one thing : inside every single-definition
// recursive group, flatten each addition spine (stopping at shared nodes
// -- never trade a certain sharing), split the terms into off-path (do
// not contain the group's own projection) and on-path (do), and rebuild
// with the on-path terms LAST. Term order inside each class is preserved
// (deterministic, minimal rounding churn). Multi-definition groups (true
// knots) are left untouched.

// does f contain the projection self, other projections being opaque
// leaves ? (exact on the normalized term : a foreign component cannot
// come back -- see revealIIR)
static bool containsSelf(Tree f, Tree self)
{
    std::unordered_set<Tree> seen;
    std::vector<Tree>        st{f};
    while (!st.empty()) {
        Tree t = st.back();
        st.pop_back();
        if (t == self) {
            return true;
        }
        if (!seen.insert(t).second) {
            continue;
        }
        int  i;
        Tree g;
        if (isProj(t, &i, g)) {
            continue;
        }
        for (int k = 0; k < t->arity(); k++) {
            st.push_back(t->branch(k));
        }
    }
    return false;
}

// occurrence count (parent edges), rec bodies entered -- same shape as
// placeTemps : a shared addition node is an ATOM of the enclosing spine
static void countOccurrences(Tree root, std::unordered_map<Tree, int>& occ)
{
    std::unordered_set<Tree> visited;
    std::vector<Tree>        work{root};
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        Tree var, body;
        if (isRec(t, var, body)) {
            if (visited.insert(t).second && body != nullptr) {
                work.push_back(body);
            }
            continue;
        }
        for (int k = 0; k < t->arity(); k++) {
            Tree b = t->branch(k);
            occ[b]++;
            if (visited.insert(b).second) {
                work.push_back(b);
            }
        }
    }
}

Tree reassociate(Tree lsig)
{
    std::unordered_map<Tree, int> occ;
    countOccurrences(lsig, occ);

    std::unordered_map<Tree, Tree> memo;

    // flatten the addition spine of t (single-use add nodes only) into terms
    std::function<void(Tree, std::vector<Tree>&, bool)> flatten = [&](Tree t,
                                                                      std::vector<Tree>& terms,
                                                                      bool               isRoot) {
        Tree x, y;
        if (isSigAdd(t, x, y) && (isRoot || occ[t] <= 1)) {
            flatten(x, terms, false);
            flatten(y, terms, false);
        } else {
            terms.push_back(t);
        }
    };

    std::function<Tree(Tree, Tree)> build = [&](Tree t, Tree selfProj) -> Tree {
        if (auto it = memo.find(t); it != memo.end()) {
            return it->second;
        }

        int  i;
        Tree grp, var, body;
        if (isProj(t, &i, grp) && isRec(grp, var, body) && body != nullptr && !isNil(body)) {
            // EVERY group is rebuilt -- a knot left "untouched" in a renamed
            // world keeps stale references to the OLD singletons and both
            // versions end up emitted (korg35 : +4 duplicated states). The
            // knots get no reassociation (selfProj null : pure reference
            // remapping through the memo) ; only single-definition groups
            // get the late join.
            int               n = len(body);
            Tree              var2 = tree(unique("A"));
            Tree              g2   = ref(var2);
            std::vector<Tree> oldp(n);
            for (int j = 0; j < n; j++) {
                oldp[j]       = proj(j, grp);
                memo[oldp[j]] = proj(j, g2);
            }
            tvec defs;
            for (int j = 0; j < n; j++) {
                defs.push_back(build(nth(body, j), (n == 1) ? oldp[j] : nullptr));
            }
            Tree body2 = gGlobal->nil;
            for (auto it2 = defs.rbegin(); it2 != defs.rend(); ++it2) {
                body2 = cons(*it2, body2);
            }
            rec(var2, body2);
            return memo.at(t);
        }

        Tree x, y;
        if (selfProj != nullptr && isSigAdd(t, x, y) && occ[t] <= 1) {
            // an addition spine inside a recursive definition : late join.
            // Never a shared root (duplication), and only when the join is
            // ACTUALLY misplaced -- an on-path term appearing before an
            // off-path one in the flattened order ; otherwise the original
            // tree (and its sharing, and its rounding) is kept untouched.
            std::vector<Tree> terms;
            flatten(t, terms, true);
            std::vector<Tree> off, on;
            bool              misplaced = false;
            for (Tree tm : terms) {
                if (containsSelf(tm, selfProj)) {
                    on.push_back(tm);
                } else {
                    if (!on.empty()) {
                        misplaced = true;  // off-path term AFTER an on-path one
                    }
                    off.push_back(tm);
                }
            }
            if (misplaced && !on.empty() && !off.empty()) {
                Tree acc = nullptr;
                for (Tree tm : off) {
                    Tree b = build(tm, selfProj);
                    acc    = acc ? sigAdd(acc, b) : b;
                }
                for (Tree tm : on) {
                    Tree b = build(tm, selfProj);
                    acc    = acc ? sigAdd(acc, b) : b;
                }
                memo[t] = acc;
                return acc;
            }
            // single-class sum : fall through to the generic rebuild
        }

        int  ar = t->arity();
        Tree r  = t;
        if (ar > 0 && !isRec(t, var, body)) {
            bool  changed = false;
            tvec br(ar);
            for (int k = 0; k < ar; k++) {
                br[k]   = build(t->branch(k), selfProj);
                changed = changed || (br[k] != t->branch(k));
            }
            if (changed) {
                r = tree(t->node(), br);
            }
        }
        memo[t] = r;
        return r;
    };

    return build(lsig, nullptr);
}
