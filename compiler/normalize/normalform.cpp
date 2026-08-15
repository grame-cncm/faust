/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <stdio.h>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

#include "global.hh"
#include "ppbox.hh"
#include "ppsig.hh"
#include "sigNewConstantPropagation.hh"
#include "sigPromotion.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "timing.hh"
#include "tree.hh"
#include "rewrite.hh"

using namespace std;

//----------------------------------------------------------------------------------------
// Delayed-alias dissolution, caller side (spec GC-MEMBRES par.8).
//
// A member r of a recursive group whose definition is a pure literal delay
// x = y@n (n >= 1) stores nothing of its own : every reader can read y n
// taps deeper. The previous implementation lived INSIDE normalizeRecGroups
// behind three semantic callbacks (delayedBranch / shiftTerm / reshift) ;
// this one keeps the signal knowledge where it belongs :
//
//   1. detect the alias members and resolve alias-of-alias chains (folded
//      amounts ; a CYCLE of aliases is simply left unresolved -- if nothing
//      external reads it, gcRecGroups collects it wholesale : the old ad hoc
//      cycle guard became a theorem) ;
//   2. re-point every reference in ONE treeRewritePaired pass -- the rule
//      matches the ORIGINAL, where the group identity is unambiguous even
//      with nested groups, and folds the amounts locally (same doctrine as
//      the old reshift) so no nested delay is ever created ;
//   3. gcRecGroups : the now-unreferenced members disappear -- and whatever
//      they alone kept alive with them -- projections renumbered.
//----------------------------------------------------------------------------------------
static Tree dissolveDelayedAliases(Tree L)
{
    // ---- 1a. collect the raw aliases, keyed by their (hash-consed)
    // projection node : projNode -> (payload, literal amount)
    struct Alias {
        Tree payload;
        int  amount;
    };
    map<Tree, Alias, treeorder> raw;
    {
        set<Tree, treeorder>  seen;
        vector<Tree>          work{L};
        while (!work.empty()) {
            Tree n = work.back();
            work.pop_back();
            if (!seen.insert(n).second) {
                continue;
            }
            Tree id, body;
            if (isRec(n, id, body) && body != nullptr && isList(body)) {
                int i = 0;
                for (Tree l = body; isList(l); l = tl(l), i++) {
                    Tree def = hd(l);
                    Tree y, ny;
                    int  amt;
                    // n >= 1 only. The INSTANTANEOUS copies (x = s, or s@0,
                    // with s a projection) are covered by nobody -- eta
                    // requires a group-free definition, this rule a positive
                    // depth -- but the hole is theoretical : extending the
                    // match to amt == 0 (payload restricted to projections,
                    // bare payload emitted without a delay node) left the
                    // whole corpus byte-identical (199/199, 2026-08-15).
                    // The box-to-signal translation never produces such
                    // members ; if it ever does, extend here.
                    if (isSigDelay(def, y, ny) && isSigInt(ny, &amt) && amt >= 1) {
                        raw[proj(i, n)] = {y, amt};
                    }
                    work.push_back(def);
                }
                continue;
            }
            for (int i = 0; i < n->arity(); i++) {
                work.push_back(n->branch(i));
            }
        }
    }
    if (raw.empty()) {
        return L;
    }

    // ---- 1b. resolve chains (x = y@n where y is itself an alias) with
    // folded amounts ; a chain that loops is dropped whole
    map<Tree, Alias, treeorder> resolved;
    for (const auto& [p, a] : raw) {
        Tree                 pay = a.payload;
        int                  amt = a.amount;
        set<Tree, treeorder> visited{p};
        bool                 cyclic = false;
        while (true) {
            auto next = raw.find(pay);
            if (next == raw.end()) {
                break;
            }
            if (!visited.insert(pay).second) {
                cyclic = true;
                break;
            }
            amt += next->second.amount;
            pay = next->second.payload;
        }
        if (!cyclic) {
            resolved[p] = {pay, amt};
        }
    }

    // ---- 1c. the self-reach guard : an alias whose resolved payload
    // reaches its own projection THROUGH BRANCHES cannot be dissolved (the
    // re-pointing rule would recurse into itself before its memo entry
    // exists). Branches only, deliberately : the path through a RECDEF body
    // is already safe -- treeRewritePaired memoizes a recursive node BEFORE
    // descending its definitions, which breaks any loop through the group.
    // Walking RECDEF here would kill every intra-group alias (the payload
    // of x = s@n is typically a projection of the same group) for a danger
    // that does not exist.
    {
        vector<Tree> drop;
        for (const auto& [p, a] : resolved) {
            set<Tree, treeorder> seen;
            vector<Tree>         work{a.payload};
            bool                 reaches = false;
            while (!work.empty() && !reaches) {
                Tree n = work.back();
                work.pop_back();
                if (!seen.insert(n).second) {
                    continue;
                }
                if (n == p) {
                    reaches = true;
                    break;
                }
                for (int i = 0; i < n->arity(); i++) {
                    work.push_back(n->branch(i));
                }
            }
            if (reaches) {
                drop.push_back(p);
            }
        }
        for (Tree p : drop) {
            resolved.erase(p);
        }
    }
    if (resolved.empty()) {
        return L;
    }

    // ---- 2. one re-pointing pass. The rule matches ORIGINAL nodes ; the
    // payload is itself rewritten on demand through the shared memo (it may
    // read other aliases).
    unordered_map<Tree, Tree>        memo;
    function<Tree(Tree, Tree)> rule = [&](Tree orig, Tree rebuilt) -> Tree {
        int  i;
        Tree g;
        Tree op, oy;
        // a delay over an alias projection folds : (proj@n)@k -> payload@(n+k)
        if (isSigDelay(orig, op, oy)) {
            auto a = resolved.find(op);
            if (a != resolved.end()) {
                Tree pay = treeRewritePaired(a->second.payload, rule, memo);
                Tree k   = rebuilt->branch(1);  // the rewritten amount
                return sigDelay(pay,
                                simplifyExpression(sigAdd(sigInt(a->second.amount), k)));
            }
        }
        // a bare alias projection reads the payload at the alias depth
        if (isProj(orig, i, g)) {
            auto a = resolved.find(orig);
            if (a != resolved.end()) {
                Tree pay = treeRewritePaired(a->second.payload, rule, memo);
                return sigDelay(pay, sigInt(a->second.amount));
            }
        }
        return rebuilt;
    };
    Tree L2 = treeRewritePaired(L, rule, memo);

    // ---- 3. the dead members -- and their cascades -- disappear
    return gcRecGroups(L2);
}

// Implementation

//----------------------------------------------------------------------------------------
// The normalization fixpoint (-eta / -etai <n>).
//
// Interval-driven constant propagation changes the TOPOLOGY of recursions: a
// projection with a singleton interval becomes a constant, edges of the dependency
// graph disappear, groups shrink -- and two distinct recursive expressions can become
// alpha-EQUIVALENT. The symbolic representation cannot fuse them (distinct variables),
// but in de Bruijn form alpha-equivalence IS syntactic equality, so hash-consing
// fuses them for free. Fusion in turn makes pointers equal, the canonical maps of the
// polynomial normal form collect the newly identical terms, intervals tighten, new
// constants appear... hence the loop, iterated until the de Bruijn form is
// POINTER-stable. Termination: (distinct recursive groups, non-constant nodes)
// decreases on every productive iteration.
//----------------------------------------------------------------------------------------

/**
 * The AC hash of a (de Bruijn) tree: a memoized structural hash that is INSENSITIVE
 * to permutations inside commutative operations. At a commutative binop, the whole
 * same-operator spine is FLATTENED (a normalized sum is a binary comb, so a
 * permutation also changes the associativity) and the MULTISET of its leaves is
 * combined orderlessly. Two successive iterations of the normalization loop with
 * equal AC hashes differ only by alpha-renaming (the de Bruijn form has no names)
 * and commutative permutations: nothing that counts -- the loop can stop. A 64-bit
 * collision would stop one iteration early, with a correct (just possibly less
 * simplified) tree: a benign failure mode.
 */
static uint64_t acHash(Tree t, std::map<Tree, uint64_t, treeorder>& memo);

static void acFlatten(Tree t, int op, std::vector<uint64_t>& leaves,
                      std::map<Tree, uint64_t, treeorder>& memo)
{
    int  op2;
    Tree x, y;
    if (isSigBinOp(t, &op2, x, y) && op2 == op) {
        acFlatten(x, op, leaves, memo);
        acFlatten(y, op, leaves, memo);
    } else {
        leaves.push_back(acHash(t, memo));
    }
}

static uint64_t acHash(Tree t, std::map<Tree, uint64_t, treeorder>& memo)
{
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }

    uint64_t h;
    int      op;
    Tree     x, y;
    if (isSigBinOp(t, &op, x, y) && isCommutativeOpcode(op)) {
        // orderless combine of the flattened spine's leaves
        std::vector<uint64_t> leaves;
        acFlatten(x, op, leaves, memo);
        acFlatten(y, op, leaves, memo);
        uint64_t sum = 0;
        for (uint64_t l : leaves) {
            // mix each leaf so the sum resists simple collisions
            l ^= l >> 33;
            l *= 0xff51afd7ed558ccdULL;
            l ^= l >> 33;
            sum += l;
        }
        h = 0x9e3779b97f4a7c15ULL * (static_cast<uint64_t>(op) + 1) ^ sum;
    } else {
        h = t->node().canonicalHash();
        for (int i = 0; i < t->arity(); i++) {
            // hash_combine-style: the addition breaks the XOR-linearity that made
            // 'h = h*F ^ child' cancel on repeated identical elements (a stereo
            // program with equal outputs hashed to a CONSTANT, blinding the judge)
            h ^= acHash(t->branch(i), memo) + 0x9e3779b97f4a7c15ULL + (h << 12) + (h >> 4);
        }
    }
    memo[t] = h;
    return h;
}

/// Does t contain the node g? Traverses nested recursive definitions through their
/// bodies; cycle-safe by coinduction (a cycle not passing through g is g-free).
static bool containsNode(Tree t, Tree g, std::map<Tree, bool, treeorder>& memo)
{
    if (t == g) {
        return true;
    }
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }
    memo[t] = false;  // coinductive pre-mark: cycles resolve to "no" unless found
    bool found = false;
    Tree var, body;
    if (isRec(t, var, body)) {
        found = body != nullptr && containsNode(body, g, memo);
    } else {
        for (int i = 0; !found && i < t->arity(); i++) {
            found = containsNode(t->branch(i), g, memo);
        }
    }
    memo[t] = found;
    return found;
}

/**
 * The eta rule of the fixpoint, per definition: a projection of a definition that no
 * longer references its group (the tree became invariant under recursion) is replaced
 * by the definition itself -- the recursion, and its generated state, disappear.
 * Chains harvest themselves across loop iterations: replacing proj_k everywhere
 * (inside other definitions too) frees their referencers for the next round.
 */
static Tree degroupInvariants(Tree L)
{
    // one containment memo PER GROUP: a subtree can be g1-free yet contain g2
    std::map<Tree, std::map<Tree, bool, treeorder>, treeorder> memos;
    return treeRewrite(L, [&memos](Tree r) -> Tree {
        int  i;
        Tree g;
        if (isProj(r, i, g)) {
            Tree var, body;
            if (isRec(g, var, body) && body != nullptr) {
                Tree def = nth(body, i);
                if (def != nullptr && !isNil(def) && !containsNode(def, g, memos[g])) {
                    return def;
                }
            }
        }
        return r;
    });
}

/// Count the distinct recursive groups reachable from t (SYMREC nodes, definitions
/// traversed through their bodies).
static int countRecGroups(Tree t)
{
    std::set<Tree, treeorder>    seen;
    std::set<Tree, treeorder>    groups;
    std::vector<Tree> work{t};
    while (!work.empty()) {
        Tree s = work.back();
        work.pop_back();
        if (!seen.insert(s).second) {
            continue;
        }
        Tree var, body;
        if (isRec(s, var, body)) {
            groups.insert(s);
            if (body) {
                work.push_back(body);
            }
            continue;
        }
        for (int i = 0; i < s->arity(); i++) {
            work.push_back(s->branch(i));
        }
    }
    return static_cast<int>(groups.size());
}

static Tree normalizeFixpoint(Tree L)
{
    // (-etar : the input arrives already normalized -- the entry pass of
    // simplifyToNormalFormAux runs at the birth of the symbolic form, which
    // also protects the sym2deBruijn below from the exponential mutual
    // inlining of fragmented knots, jprev's old pathology. The in-loop
    // regroup below remains : each iteration's simplifications may
    // disentangle groups again.)
    const int groupsBefore = countRecGroups(L);
    Tree      prev         = nullptr;
    int       iter         = 0;

    const bool verbose  = getenv("FAUST_NORMALIZE_FIXPOINT_TRACE") != nullptr;
    Tree       prevPrev = nullptr;
    uint64_t   prevAch  = 0;
    bool       haveAch  = false;
    // Iteration budget (-etai, default 1): one pass isolates the eta harvest
    // (merge + propagation + simplify + eta) from the effects of iterated
    // re-normalization -- the two measure differently; the AC judge may stop
    // the loop before the budget is spent.
    const int maxIter = gGlobal->gEtaIterations;
    while (iter < maxIter) {
        Tree d = sym2deBruijn(L);
        if (d == prev) {
            if (verbose) {
                std::cerr << "NORMFIX exit at iter " << iter << " : pointer-stable" << std::endl;
            }
            break;  // the de Bruijn form is pointer-stable: fixpoint reached
        }
        {
            // the AC judge: stop when the iteration changed nothing that counts
            // (only alpha-renamings and commutative permutations)
            std::map<Tree, uint64_t, treeorder> achMemo;
            uint64_t                 ach = acHash(d, achMemo);
            if (haveAch && ach == prevAch) {
                if (verbose) {
                    std::cerr << "NORMFIX exit at iter " << iter << " : AC-equal" << std::endl;
                }
                break;
            }
            prevAch = ach;
            haveAch = true;
        }
        if (verbose) {
            static Tree prevL = nullptr;
            std::cerr << "NORMFIX iter " << iter << " : groups=" << countRecGroups(L)
                      << " dbj=" << static_cast<const void*>(d)
                      << (d == prevPrev ? "  CYCLE-2" : "")
                      << (prevL ? (alphaEquiv(L, prevL) ? "  ALPHA-EQ" : "  ALPHA-DIFF")
                                : "")
                      << std::endl;
            prevL = L;
            if (getenv("FAUST_NORMALIZE_FIXPOINT_DUMP") != nullptr && iter < 4) {
                std::string fn = std::string(getenv("FAUST_NORMALIZE_FIXPOINT_DUMP")) +
                                 "/normfix-iter" + std::to_string(iter) + ".txt";
                FILE* out = fopen(fn.c_str(), "w");
                if (out) {
                    std::ostringstream oss;
                    oss << ppsig(L, 100000000);
                    fputs(oss.str().c_str(), out);
                    fclose(out);
                }
            }
        }
        prevPrev = prev;
        prev     = d;
        // the merge: alpha-equivalent groups are now shared, back to symbolic --
        // with CONTENT-DERIVED variable names (deBruijn2Sym), so every name-derived
        // order is a pure function of the structure, stable across iterations
        L = deBruijn2Sym(d);
        typeAnnotation(L, gGlobal->gLocalCausalityCheck);
        L = newConstantPropagation(L);
        L = simplify(L);
        if (gGlobal->gEtaRegroup) {
            // -etar : complete the loop's two half-measures -- the merge (this
            // loop's deBruijn round trip) and the dissolution (the eta harvest
            // below) -- into the full re-partition of the letrecs along the
            // projection SCCs. The loop's own round trip canonicalizes at the
            // next iteration : no final trip here (canonical=false). The
            // simplifications of THIS iteration may have disentangled groups ;
            // the regroup of this iteration exposes new simplifications to the
            // next one -- the AC judge stops at their joint fixpoint.
            L = normalizeRecGroups(L, false);
        }
        // the eta rule: harvest the definitions the simplifications made invariant
        Tree Lh = degroupInvariants(L);
        if (Lh != L) {
            // a harvest substitutes definition trees for projections, creating
            // compositions (nested delays, foldable constants) the backends must
            // never see: re-normalize NOW, not at the next iteration -- with -eta
            // (a single pass) there is no next iteration
            L = Lh;
            typeAnnotation(L, gGlobal->gLocalCausalityCheck);
            L = newConstantPropagation(L);
            L = simplify(L);
        }
        typeAnnotation(L, gGlobal->gLocalCausalityCheck);
        L = signalPromote(L);
        iter++;
    }

    const int groupsAfter = countRecGroups(L);
    std::cerr << "NORMFIX : " << iter << " iteration(s), " << groupsBefore << " -> "
              << groupsAfter << " recursive group(s)" << std::endl;
    return L;
}
// Temporary debug (FAUST_DEBUG_RECCOUNT) : print the recursive-group count at a
// pipeline point, to localize where group sharing is lost vs master-dev.
void debugRecCount(const char* where, Tree L)
{
    if (getenv("FAUST_DEBUG_RECCOUNT") == nullptr) {
        return;
    }
    // collect the groups (same rules as countRecGroups)
    std::set<Tree, treeorder>    seen;
    std::vector<Tree> groups;
    std::vector<Tree> work{L};
    while (!work.empty()) {
        Tree s = work.back();
        work.pop_back();
        if (!seen.insert(s).second) {
            continue;
        }
        Tree var, body;
        if (isRec(s, var, body)) {
            groups.push_back(s);
            if (body) {
                work.push_back(body);
            }
            continue;
        }
        for (int i = 0; i < s->arity(); i++) {
            work.push_back(s->branch(i));
        }
    }
    // alpha-equivalence classes : duplicates are the lost sharing
    std::vector<std::vector<Tree>> classes;
    for (Tree g : groups) {
        bool placed = false;
        for (auto& c : classes) {
            if (alphaEquiv(g, c[0])) {
                c.push_back(g);
                placed = true;
                break;
            }
        }
        if (!placed) {
            classes.push_back({g});
        }
    }
    std::cerr << "RECCOUNT " << where << " : " << groups.size() << " groupes, "
              << classes.size() << " classes alpha";
    for (auto& c : classes) {
        if (c.size() > 1) {
            std::cerr << "  [dup x" << c.size() << " : " << *c[0]->branch(0) << "]";
        }
    }
    std::cerr << std::endl;
    // for each duplicate : immediate parents and mutual nesting
    for (auto& c : classes) {
        if (c.size() < 2) {
            continue;
        }
        for (Tree g : c) {
            // g est-il atteignable depuis le corps de l'autre ?
            for (Tree h : c) {
                if (h == g) {
                    continue;
                }
                std::map<Tree, bool, treeorder> memo;
                Tree                 hv, hb;
                isRec(h, hv, hb);
                if (hb && containsNode(hb, g, memo)) {
                    std::cerr << "    " << *g->branch(0) << " est DANS le corps de "
                              << *h->branch(0) << std::endl;
                }
            }
            // parents dans L
            std::set<Tree, treeorder>    seen2;
            std::vector<Tree> work2{L};
            int               shown = 0;
            while (!work2.empty() && shown < 4) {
                Tree s2 = work2.back();
                work2.pop_back();
                if (!seen2.insert(s2).second) {
                    continue;
                }
                for (int i2 = 0; i2 < s2->arity(); i2++) {
                    if (s2->branch(i2) == g) {
                        std::cerr << "    parent de " << *g->branch(0) << " : " << s2->node()
                                  << " (branche " << i2 << ")" << std::endl;
                        shown++;
                    }
                    work2.push_back(s2->branch(i2));
                }
                Tree v2, b2;
                if (isRec(s2, v2, b2) && b2) {
                    work2.push_back(b2);
                }
            }
        }
    }
}

static Tree simplifyToNormalFormAux(Tree LS)
{
    // Convert deBruijn recursion into symbolic recursion
    startTiming("deBruijn2Sym");
    Tree L1 = deBruijn2Sym(LS);
    endTiming("deBruijn2Sym");

    // Normalize the recursive structure AT THE BIRTH of the symbolic form,
    // unconditionally : the letrec packaging is a syntactic accident, the
    // projection SCCs are the real structure, and every downstream stage
    // (simplifications, typing, sharing, the eta loop, the backends) sees
    // minimal groups. canonical=true here : we just received content-derived
    // names and owe the same downstream ; the internal round trip runs on
    // the flattened structure (positional, cheap). Validated against the
    // 2026-07-27 reference milestone : impulse responses at rounding level
    // on the whole corpus, cost within noise.
    // The classifier tells normalizeRecGroups which branches shift time :
    // branch 0 of a delay whose amount is a literal >= 1, the delayed branch
    // of mem and prefix. Every other reference counts as instantaneous, so
    // the member order of each rebuilt group puts current-tick dependencies
    // first -- the order the backends that emit definitions in list order
    // rely on (a member read undelayed one position too early costs exactly
    // one sample : the freeverb comb regression of 2026-08-11).
    // The dissolution now precedes the normalization, on the caller's side
    // (spec GC-MEMBRES par.8) : detection, re-pointing and GC are signal
    // knowledge and live here ; normalizeRecGroups keeps only the ORDER
    // classifier below. The old shiftTerm/reshift callbacks are gone.
    startTiming("dissolveDelayedAliases");
    L1 = dissolveDelayedAliases(L1);
    endTiming("dissolveDelayedAliases");
    startTiming("normalizeRecGroups");
    L1 = normalizeRecGroups(L1, true, [](Tree t, int k) -> bool {
        Tree x, y;
        int  n;
        if (isSigDelay(t, x, y)) {
            return k == 0 && isSigInt(y, &n) && n >= 1;
        }
        if (isSigDelay1(t, x)) {
            return k == 0;
        }
        if (isSigPrefix(t, x, y)) {
            return k == 1;
        }
        return false;
    });
    endTiming("normalizeRecGroups");
/*
    // PROBE: cost of the symbolic -> deBruijn -> symbolic round-trip on the
    // recursive-group representation (scalarization abandoned: n-ary groups
    // are the right canonical form for dense mutual recursion, see
    // SCALARIZE-CARTOGRAPHY.md). The round-trip is the identity on the
    // already-canonical L0; it measures the benefit of the invariance
    // predicate on real programs.
    startTiming("sharing-roundtrip-1/2 sym2deBruijn");
    Tree LD = sym2deBruijn(L0);
    endTiming("sharing-roundtrip-1/2 sym2deBruijn");

    startTiming("sharing-roundtrip-2/2 deBruijn2Sym");
    Tree L1 = deBruijn2Sym(LD);
    endTiming("sharing-roundtrip-2/2 deBruijn2Sym");
*/
    // Annotate L1 with type information
    startTiming("L1 typeAnnotation");
    typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
    endTiming("L1 typeAnnotation");

    if (gGlobal->gRangeUI) {
        // Generate safe values for range UI items (sliders and nentry)
        startTiming("Safe values for range UI items");
        L1 = signalUIPromote(L1);
        endTiming("Safe values for range UI items");

        // Annotate L1 with type information
        startTiming("L1 typeAnnotation");
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
        endTiming("L1 typeAnnotation");
    }

    if (gGlobal->gFreezeUI) {
        // Freeze range UI items (sliders and nentry) to their init value
        startTiming("Freeze values for range UI items");
        L1 = signalUIFreezePromote(L1);
        endTiming("Freeze values for range UI items");

        // Annotate L1 with type information
        startTiming("L1 typeAnnotation");
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
        endTiming("L1 typeAnnotation");
    }

    if (gGlobal->gFTZMode > 0) {
        // Wrap real signals with FTZ
        startTiming("FTZ on recursive signals");
        L1 = signalFTZPromote(L1);
        endTiming("FTZ on recursive signals");

        // Annotate L1 with type information
        startTiming("L1 typeAnnotation");
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
        endTiming("L1 typeAnnotation");
    }

    // Needed before 'simplify' (see sigPromotion.hh)
    startTiming("Cast and Promotion");
    debugRecCount("NF:L1", L1);
    Tree L2 = signalPromote(L1);
    endTiming("Cast and Promotion");

    // Canonical names BEFORE the normal form (only under -co) : the CANONICAL
    // term orders hash the recursive variables by name, so the names must be
    // history-independent before normalization. Under the default serial order
    // this pass serves nothing and its fresh variables would shift the serials
    // (a reorder of the generated code) : it follows the option it serves.
    if (gGlobal->gCanonicalOrder) {
        startTiming("canonicalizeRecNames");
        L2 = canonicalizeRecNames(L2);
        endTiming("canonicalizeRecNames");

        startTiming("L2 typeAnnotation");
        typeAnnotation(L2, gGlobal->gLocalCausalityCheck);
        endTiming("L2 typeAnnotation");
    }

    // Simplify by executing every computable operation
    startTiming("L2 simplification");
    debugRecCount("NF:L2(promote)", L2);
    Tree L3 = simplify(L2);
    endTiming("L2 simplification");

    // Annotate L3 with type information
    startTiming("L3 typeAnnotation");
    typeAnnotation(L3, gGlobal->gLocalCausalityCheck);
    endTiming("L3 typeAnnotation");

    startTiming("Cast and Promotion");
    debugRecCount("NF:L3(simplify)", L3);
    Tree L4 = signalPromote(L3);
    endTiming("Cast and Promotion");

    startTiming("L4 typeAnnotation");
    typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
    endTiming("L4 typeAnnotation");

    // Must be done after simplification so that 'size' signal is properly simplified to a constant
    if (gGlobal->gCheckTable) {
        // Check and generate safe access to rdtable/rwtable
        startTiming("Safe access to rdtable/rwtable");
        L4 = signalTablePromote(L4);
        endTiming("Safe access to rdtable/rwtable");

        // Annotate L4 with type information
        startTiming("L4 typeAnnotation");
        typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
        endTiming("L4 typeAnnotation");
    }

    if (gGlobal->gCheckIntRange) {
        // Check and generate safe float to integer range conversion
        startTiming("Safe float to integer conversion");
        L4 = signalIntCastPromote(L4);
        endTiming("Safe float to integer conversion");

        // Annotate L4 with type information
        startTiming("L4 typeAnnotation");
        typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
        endTiming("L4 typeAnnotation");
    }

    if (gGlobal->gEtaHarvest) {
        startTiming("normalizeFixpoint");
        L4 = normalizeFixpoint(L4);
        endTiming("normalizeFixpoint");
    }

    // Canonical recursive-variable naming (only under -co) : names AND node serials
    // in plan order, so the downstream serial-ordered consumers (symbol sets, loop
    // scheduling) become independent of the transformation history -- the generated
    // code is the same for alpha-equivalent trees. Like the canonical term order it
    // serves, this is opt-in : the default serial regime keeps the historical,
    // construction-driven serials (and their measured performance).
    if (gGlobal->gCanonicalOrder) {
        startTiming("canonicalizeRecNames");
        L4 = canonicalizeRecNames(L4);
        endTiming("canonicalizeRecNames");
    }
    // Whoever rebuilt trees above (the renaming, or the -eta fixpoint) leaves them
    // without type annotations : re-annotate for the passes that follow. This is
    // tied to the REBUILDERS, not to -co -- the eta loop under serial order needs
    // it just as much (first caught by zitaRev -etai 10 : assert sigtyperules:224).
    if (gGlobal->gCanonicalOrder || gGlobal->gEtaHarvest) {
        startTiming("L4 typeAnnotation");
        typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
        endTiming("L4 typeAnnotation");
    }

    // Check signal tree
    startTiming("L4 signalChecker");
    SignalChecker checker(L4);
    endTiming("L4 signalChecker");
    debugRecCount("NF:L4(return)", L4);
    return L4;
}

// Public API
LIBFAUST_API Tree simplifyToNormalForm(Tree sig)
{
    if (isList(sig)) {
        startTiming("simplifyToNormalForm");
        Tree t2 = sig->getProperty(gGlobal->NORMALFORM);
        if (!t2) {
            t2 = simplifyToNormalFormAux(sig);
            sig->setProperty(gGlobal->NORMALFORM, t2);
        }
        endTiming("simplifyToNormalForm");
        return t2;
    } else {
        return simplifyToNormalForm(cons(sig, gGlobal->nil));
    }
}

LIBFAUST_API tvec simplifyToNormalForm2(tvec siglist)
{
    tvec res;
    for (const auto& it : siglist) {
        res.push_back(simplifyToNormalForm(it));
    }
    return res;
}

LIBFAUST_API string printSignal(Tree sig, bool shared, int max_size)
{
    // Clear print state
    gGlobal->clear();
    stringstream str;
    if (shared) {
        ppsigShared(sig, str, max_size);
    } else {
        str << ppsig(sig, max_size) << endl;
    }
    return str.str();
}

LIBFAUST_API string printBox(Tree box, bool shared, int max_size)
{
    // Clear print state
    gGlobal->clear();
    stringstream str;
    if (shared) {
        boxppShared(box, str);
    } else {
        str << mBox(box, max_size) << endl;
    }
    return str.str();
}
