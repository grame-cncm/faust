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
    // select2 cascades : a barrier on (or accounted through) a selection
    // tree measurably hurts (the vocal family, x2.3) -- the C compiler
    // treats the inline cascade as lazily-selected / loop-invariant
    // material, which a named stage disturbs. Selections are neither
    // staged nor counted.
    {
        Tree sel, then_, else_;
        if (isSigSelect2(t, sel, then_, else_)) {
            return false;
        }
    }
    // STRUCTURAL nodes : their consumers pattern-match them bare (a table
    // argument of RDTbl, a generator, a soundfile head, a waveform) and
    // the UI traversals must meet the widgets unwrapped. A barrier here
    // would hide them behind temp() and break the matchers.
    {
        Tree size, gen, wi, ws, sf, lbl, cur, mn, mx, st;
        if (isSigWRTbl(t, size, gen) || isSigWRTbl(t, size, gen, wi, ws) || isSigGen(t, x) ||
            isSigWaveform(t)) {
            return false;
        }
        if (isSigSoundfile(t, lbl) || isSigSoundfileLength(t, sf, x) ||
            isSigSoundfileRate(t, sf, x)) {
            return false;
        }
        if (isSigButton(t, lbl) || isSigCheckbox(t, lbl) ||
            isSigHSlider(t, lbl, cur, mn, mx, st) || isSigVSlider(t, lbl, cur, mn, mx, st) ||
            isSigNumEntry(t, lbl, cur, mn, mx, st) || isSigHBargraph(t, lbl, mn, mx, x) ||
            isSigVBargraph(t, lbl, mn, mx, x) || isSigAttach(t, x, cur) ||
            isSigEnable(t, x, cur) || isSigControl(t, x, cur)) {
            return false;
        }
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
            if (raw >= K) {
                // barrier even on SHARED nodes : the emitter's sharing is
                // CONTEXT-sensitive and may inline a DAG-shared node once
                // per context (GrainGenerator's grain sums, duplicated per
                // channel) -- the barrier materializes it once, globally
                stage.insert(t);
                c = 0;
            } else if (occ[t] > 1) {
                c = 0;  // the emitter will name it anyway
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
    // seed the analysis by a FULL traversal (same shape as
    // countOccurrences : rec bodies entered, projections' groups pushed
    // wherever they occur -- a projection buried in an expression must
    // still get its definitions analyzed)
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
            if (!isList(t) && !isNil(t)) {
                costOf(t);
            }
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
        }
    }

    if (getenv("FAUST_DEBUG_PLACETEMPS")) {
        std::cerr << "PLACETEMPS K=" << K << " nodes-costed=" << cost.size()
                  << " staged=" << stage.size() << std::endl;
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
