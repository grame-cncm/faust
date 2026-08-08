#include "placeTemps.hh"

#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "global.hh"
#include "rewrite.hh"

//----------------------------------------------------------------------
// Structural staging : sigTemp barriers placed at normalization
//----------------------------------------------------------------------
//
// The emitter inlines every single-use expression, whatever its size. In
// one-sample recursive loops this folds whole chains into one
// mega-expression : the C compiler then tends to emit the recurrence chain
// as a contiguous block instead of interleaving independent work inside
// its latency shadow (measured x1.2-1.46 on the oberheim/korg35 family
// after the letrec dissolution removed the projection boundaries that
// used to stage them accidentally). And a mega-expression is opaque to
// the intra-loop scheduling model : named stages are its instructions.
//
// The policy, decided HERE and reified as sigTemp nodes (inspectable,
// transformable, backend-independent) rather than buried in the emitter :
//
//   a node gains a barrier iff it is single-use, is an operation, and its
//   INLINE COST reaches K -- where the inline cost counts the operations
//   that would end up nested in the emitted expression :
//
//     cost(leaf)                          = 0
//     cost(shared node)                   = 0   (the emitter names it)
//     cost(barrier'd node)                = 0   (just materialized)
//     cost(op)  = 1 + sum cost(children)        (otherwise)
//
//   K=1 places a barrier on every operation : the SSA form, where the
//   emitter's job degenerates to printing one instruction per node and
//   the scheduling model governs the whole order.
//
// The analysis runs on the ORIGINAL side of the generic paired rewrite
// (occurrence counts need the original DAG), the barriers are placed on
// the rebuilt side. Placement must run AFTER the normal form is final :
// temp is a barrier the rewrite rules do not see through.

// occurrence count of every node reachable from the root list (a shared
// subtree is counted once per PARENT EDGE, which is what the emitter's own
// sharing analysis will see)
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

// is t an operation worth staging at all ? (leaves, references and
// structural nodes are not : they cost nothing to inline)
static bool isStageable(Tree t)
{
    int     i;
    int64_t i64;
    double  r;
    Tree    x, y, var, body;
    if (t->arity() == 0) {
        return false;  // numbers, inputs, UI leaves, symbols
    }
    if (isSigInt(t, &i) || isSigInt64(t, &i64) || isSigReal(t, &r)) {
        return false;
    }
    if (isRec(t, var, body) || isProj(t, &i, x) || isList(t) || isNil(t)) {
        return false;
    }
    if (isSigTemp(t, x) || isSigOutput(t, &i, x)) {
        return false;
    }
    return true;
}

Tree placeTemps(Tree lsig, int K)
{
    std::unordered_map<Tree, int> occ;
    countOccurrences(lsig, occ);

    // inline cost + barrier decision, bottom-up on the original DAG
    std::unordered_map<Tree, int>  cost;   // contribution to the PARENT
    std::unordered_set<Tree>       stage;  // nodes that get a barrier
    std::function<int(Tree)> costOf = [&](Tree t) -> int {
        if (auto it = cost.find(t); it != cost.end()) {
            return it->second;
        }
        int c = 0;
        if (isStageable(t)) {
            Tree var, body;
            int  raw = 1;
            for (int k = 0; k < t->arity(); k++) {
                raw += costOf(t->branch(k));
            }
            if (occ[t] > 1) {
                c = 0;  // the emitter will name it anyway
            } else if (raw >= K) {
                stage.insert(t);  // barrier : materialized, costs nothing above
                c = 0;
            } else {
                c = raw;
            }
        } else {
            // leaves and references contribute nothing ; still visit the
            // children of structural nodes (proj's group is NOT an
            // expression : skip it)
            int  i;
            Tree g, var, body;
            if (isProj(t, &i, g) || isRec(t, var, body)) {
                c = 0;
            } else {
                for (int k = 0; k < t->arity(); k++) {
                    costOf(t->branch(k));
                }
                c = 0;
            }
        }
        cost[t] = c;
        return c;
    };
    // seed the analysis from every expression reachable outside rec bodies,
    // and from every definition (walk mirrors countOccurrences)
    {
        std::unordered_set<Tree> visited;
        std::vector<Tree>        work{lsig};
        while (!work.empty()) {
            Tree t = work.back();
            work.pop_back();
            if (!visited.insert(t).second) {
                continue;
            }
            Tree var, body;
            if (isRec(t, var, body)) {
                if (body != nullptr) {
                    work.push_back(body);
                }
                continue;
            }
            if (isList(t) || isNil(t)) {
                for (int k = 0; k < t->arity(); k++) {
                    work.push_back(t->branch(k));
                }
                continue;
            }
            costOf(t);
            int  i;
            Tree g;
            if (isProj(t, &i, g)) {
                work.push_back(g);
            }
        }
    }

    // placement : the generic paired rewrite -- decisions were taken on the
    // ORIGINAL side, barriers go on the rebuilt side
    std::unordered_map<Tree, Tree> memo;
    auto pre     = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    auto rule    = [&](Tree orig, Tree rebuilt) -> Tree {
        return stage.count(orig) ? sigTemp(rebuilt) : rebuilt;
    };
    return treeRewritePairedMemo(lsig, pre, rule, memo, defRule);
}
