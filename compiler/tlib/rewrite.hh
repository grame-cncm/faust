/*
 * TLIB : tree library
 * Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#ifndef __REWRITE__
#define __REWRITE__

#include <optional>
#include <unordered_map>

#include "list.hh"
#include "symbol.hh"
#include "tlib-error.hh"
#include "tree.hh"

/**
 * Bottom-up rewriting of symbolic trees (see REWRITE-SPEC.md).
 *
 * treeRewrite(root, rule) applies 'rule' bottom-up to every node of the DAG,
 * with a memo local to the call :
 *  - sharing is preserved : a subtree seen several times is transformed once;
 *  - reconstruction is minimal : an unchanged node returns the same pointer;
 *  - no property is attached to the trees by the traversal;
 *  - the rule is never applied to SYMREC nodes : a recursive definition
 *    rec(var, body) is traversed through its body (RECDEF property), and
 *    every other occurrence of the same SYMREC pointer (recursive reference
 *    or shared occurrence) resolves through the memo.
 *
 * The rule is any callable of signature Tree(Tree), like tmap's tfun. It
 * receives a node whose branches are already transformed, and returns either
 * the same pointer ("no local change") or the replacement tree.
 *
 * treeRewrite() creates a fresh variable for every rec(var, body) : pure, the
 * old tree keeps its RECDEF untouched, but under the identity rule the
 * result is only alpha-equivalent to the input (areEquiv, not ==). A group
 * whose body comes back unchanged may keep its variable without redefining
 * it : treeRewriteMinimal, at the end of this file, does exactly that.
 *
 * Rule view, for a node f(t1,...,tn) which is not a SYMREC :
 *
 *   rule |- ti => ui for every i
 *   ------------------------------------------------------------ (rewrite)
 *   rule |- f(t1,...,tn) => rule⟦ f(u1,...,un) ⟧
 *
 * In other words, treeRewrite(root, rule) is the usual bottom-up
 * congruence closure followed by one local rewrite rule on the rebuilt
 * node. rule⟦x⟧ denotes the C++ call rule(x). The memo makes this a DAG
 * rewrite : the judgment t => u is computed once per Tree pointer and then
 * reused.
 *
 * For a recursive definition, treeRewrite is alpha-renaming :
 *
 *   body[var := var'] => body'
 *   ------------------------------- (rec-copy)
 *   rec(var, body) => rec(var', body')
 *
 * The memo is initialized before descending into body so that recursive
 * references to the definition have a target during the traversal.
 */

template <class Rule>
Tree treeRewriteMemo(Tree t, Rule& rule, std::unordered_map<Tree, Tree>& memo)
{
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }

    Tree var  = nullptr;
    Tree body = nullptr;
    if (isRec(t, var, body)) {
        // a symbolic reference whose variable was never defined by a
        // rec(var, body) reaches this point with a null body : caller error
        TLIB_ASSERT(body != nullptr);
        Tree newVar = tree(unique("W"));
        // resolves recursive references and shared occurrences of t during
        // the body traversal; ref(newVar) and rec(newVar, newBody) are the
        // same hash-consed pointer, so this memo entry is already final
        memo[t]      = ref(newVar);
        Tree newBody = treeRewriteMemo(body, rule, memo);
        return rec(newVar, newBody);
    }

    int  ar = t->arity();
    Tree r  = t;
    if (ar > 0) {
        bool changed = false;
        tvec br(ar);
        for (int i = 0; i < ar; i++) {
            br[i]   = treeRewriteMemo(t->branch(i), rule, memo);
            changed = changed || (br[i] != t->branch(i));
        }
        if (changed) {
            r = tree(t->node(), br);
        }
    }
    Tree result = rule(r);
    memo[t]     = result;
    return result;
}

template <class Rule>
Tree treeRewrite(Tree root, Rule&& rule)
{
    std::unordered_map<Tree, Tree> memo;
    return treeRewriteMemo(root, rule, memo);
}

/**
 * treeRewritePaired : same traversal and rec discipline as treeRewrite, but the rule
 * receives BOTH trees -- rule(original, rebuilt) -- so a transformation can consult
 * annotations carried by the original (types, intervals) while building from the
 * rebuilt branches. The memo is exposed for the same reason : it maps every processed
 * original to its result, which is how nested arguments (list-packed operands) are
 * paired with their transforms.
 */
template <class Pre, class Rule, class DefRule>
Tree treeRewritePairedMemo(Tree t, Pre& pre, Rule& rule, std::unordered_map<Tree, Tree>& memo,
                           DefRule& defRule)
{
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }

    Tree var  = nullptr;
    Tree body = nullptr;
    if (isRec(t, var, body)) {
        TLIB_ASSERT(body != nullptr);
        Tree newVar = tree(unique("W"));
        memo[t]      = ref(newVar);
        // A list-shaped body is rebuilt element by element so defRule can wrap each
        // definition at its slot. The wrap is positional : neither the wrapped
        // definitions nor the cons cells are memoized, so a subtree shared between
        // a definition root and an inner position keeps its unwrapped transform
        // everywhere else. The tail (the nil terminator, or a whole non-list body,
        // where the seam does not apply) goes through the ordinary rewrite.
        tvec defs;
        Tree l = body;
        while (isList(l)) {
            Tree d = hd(l);
            defs.push_back(defRule(d, treeRewritePairedMemo(d, pre, rule, memo, defRule)));
            l = tl(l);
        }
        Tree newBody = treeRewritePairedMemo(l, pre, rule, memo, defRule);
        for (auto i = defs.rbegin(); i != defs.rend(); ++i) {
            newBody = cons(*i, newBody);
        }
        return rec(newVar, newBody);
    }

    // the top-down guard : a fired cut decides the whole subtree on the ORIGINAL
    // node, children are never visited and the bottom-up rule is not applied (R1,
    // same discipline as the guarded treeRewrite)
    std::optional<Tree> cut = pre(t);
    if (cut.has_value()) {
        TLIB_ASSERT(*cut != nullptr);
        memo[t] = *cut;
        return *cut;
    }

    int  ar = t->arity();
    Tree r  = t;
    if (ar > 0) {
        bool changed = false;
        tvec br(ar);
        for (int i = 0; i < ar; i++) {
            br[i]   = treeRewritePairedMemo(t->branch(i), pre, rule, memo, defRule);
            changed = changed || (br[i] != t->branch(i));
        }
        if (changed) {
            r = tree(t->node(), br);
        }
    }
    Tree result = rule(t, r);
    memo[t]     = result;
    return result;
}

/**
 * The paired rewrite, full form : a top-down guard pre(orig) -> optional<Tree>
 * consulted on each original node before descending (a fired cut replaces the whole
 * subtree, R1), and a DEFINITION seam defRule(origDef, rebuiltDef) applied to every
 * element of a rec body -- each recursive definition, after its own rewriting,
 * before the group is tied. Every group still gets a fresh variable; the guard is
 * never consulted on SYMREC nodes.
 */
template <class Pre, class Rule, class DefRule>
Tree treeRewritePaired(Tree root, Pre&& pre, Rule&& rule, std::unordered_map<Tree, Tree>& memo,
                       DefRule&& defRule)
{
    return treeRewritePairedMemo(root, pre, rule, memo, defRule);
}

template <class Rule, class DefRule>
Tree treeRewritePaired(Tree root, Rule&& rule, std::unordered_map<Tree, Tree>& memo,
                       DefRule&& defRule)
{
    auto nopre = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    return treeRewritePairedMemo(root, nopre, rule, memo, defRule);
}

template <class Rule>
Tree treeRewritePaired(Tree root, Rule&& rule, std::unordered_map<Tree, Tree>& memo)
{
    auto nopre    = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto identity = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    return treeRewritePairedMemo(root, nopre, rule, memo, identity);
}

/**
 * Annotation-guarded variants (see REWRITE-SPEC.md, "Reecriture gardee par
 * annotation") : same bottom-up memoized traversal, plus a top-down guard
 * consulted on each ORIGINAL node before descending into its children.
 *
 * Motivation : some rules have a premise that is a judgment on the SOURCE
 * term (a type, an interval, any annotation computed by a prior analysis),
 * not a property of its structure :
 *
 *     G |- t : [k,k]
 *     --------------- (R1)
 *        t -> k
 *
 * Such a premise does not survive reconstruction : once children have been
 * rewritten, the rebuilt node is a fresh tree carrying no judgment, and R1
 * can never fire again -- the rewrite is lost, not delayed. R1 must
 * therefore be tried BEFORE the congruence descent (R2), on the original
 * node. This priority is part of the semantics, not an optimization.
 *
 * Rule view, for a node t = f(t1,...,tn) which is not a SYMREC :
 *
 *   pre⟦t⟧ = some(c)
 *   ----------------------- (guard-cut)
 *   pre,post |- t => c
 *
 *   pre⟦t⟧ = none
 *   pre,post |- ti => ui for every i
 *   --------------------------------------------------- (guard-congruence)
 *   pre,post |- t => post⟦ f(u1,...,un) ⟧
 *
 * Here pre⟦t⟧ and post⟦r⟧ denote the C++ calls pre(t) and post(r).
 * Therefore 'pre' decides whether the original subtree is opaque/replaced;
 * when it fires, children are not visited and 'post' is not applied to the
 * replacement. 'post' only handles nodes rebuilt by congruence.
 *
 * pre : Tree -> std::optional<Tree>, called top-down on each original node
 * (never on a SYMREC node, which the traversal handles itself) :
 *   - returns std::nullopt : no decision here, descend into children as usual;
 *   - returns r            : the whole subtree becomes r, children are never
 *                            visited. r == t expresses "keep this node
 *                            verbatim, don't enter it" (an opaque subtree).
 *
 * post : Tree -> Tree, the bottom-up rule, applied exactly once after
 * congruence descent. Its argument has already-rewritten children. Returning
 * that argument means "no local change".
 *
 * The single-rule treeRewrite(root, rule) is exactly equivalent to
 * treeRewrite(root, [](Tree) -> std::optional<Tree> { return std::nullopt; },
 *                   [](Tree r){ return rule(r); }).
 *
 * Caveat : after a guarded rewrite, the judgments consulted by 'pre' are
 * stale for the RESULT tree (new nodes carry no annotation). Recomputing
 * them -- including any fixpoint on recursive definitions -- is the
 * caller's pipeline's responsibility, as for any type-dependent pass.
 */

template <class Pre, class Post>
Tree treeRewriteMemo(Tree t, Pre& pre, Post& post, std::unordered_map<Tree, Tree>& memo)
{
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }

    Tree var  = nullptr;
    Tree body = nullptr;
    if (isRec(t, var, body)) {
        TLIB_ASSERT(body != nullptr);
        Tree newVar  = tree(unique("W"));
        memo[t]      = ref(newVar);
        Tree newBody = treeRewriteMemo(body, pre, post, memo);
        return rec(newVar, newBody);
    }

    Tree r;
    std::optional<Tree> cut = pre(t);
    if (cut.has_value()) {
        TLIB_ASSERT(*cut != nullptr);
        // guard fired : whole subtree decided here, children never visited
        memo[t] = *cut;
        return *cut;
    } else {
        int ar = t->arity();
        r      = t;
        if (ar > 0) {
            bool changed = false;
            tvec br(ar);
            for (int i = 0; i < ar; i++) {
                br[i]   = treeRewriteMemo(t->branch(i), pre, post, memo);
                changed = changed || (br[i] != t->branch(i));
            }
            if (changed) {
                r = tree(t->node(), br);
            }
        }
    }
    Tree result = post(r);
    memo[t]     = result;
    return result;
}

template <class Pre, class Post>
Tree treeRewrite(Tree root, Pre&& pre, Post&& post)
{
    std::unordered_map<Tree, Tree> memo;
    return treeRewriteMemo(root, pre, post, memo);
}


/**
 * treeRewriteMinimal : the bottom-up rewrite of treeRewrite, but a recursive
 * group keeps its variable when its body comes back unchanged. Under the
 * identity rule the result IS the input (==), not merely alpha-equivalent.
 *
 * Immutability forbids redefining a variable, so a group whose body changes
 * still needs a fresh one ; the only question is to know it BEFORE naming.
 * The groups reachable from the root, bodies included, are taken component by
 * component -- the strongly connected components of "the body of X mentions
 * Y", mutually recursive groups together -- in an order where a component
 * comes after every component it depends on. Within a component, the decision
 * is all or nothing : renaming one group changes every body that mentions it.
 *
 * For the current component C, each group of C gets a PROVISIONAL fresh name,
 * and one descent computes, for every subtree s of its bodies, a pair :
 *   I(s) : s with the groups of C renamed, the lower groups as they were ;
 *   R(s) : the rule applied bottom-up, the lower groups at their decided image.
 * If R and I agree on every body, the component keeps its names and the
 * provisional ones are never defined ; otherwise it takes them. I sees the
 * lower groups as they were, so a renamed lower group makes the bodies that
 * mention it differ, as it must.
 *
 * Both results live in a component-local memo P until the decision, and only
 * then reach the global memo G : a renamed component gives every s its R(s) ;
 * a kept one gives s -> s only where I(s) and R(s) agree. A projection shared
 * between a body and the outside would otherwise keep an image that mentions
 * a provisional name, whose group will never be defined.
 *
 * Once a whole body differs, the component is renamed and I is no longer
 * built (the decision is taken between complete bodies only : a change in a
 * child may still be undone by an ancestor).
 *
 * The input must be well formed : every reachable group is defined, and no
 * cycle is made of direct references alone (D(X) = Y, D(Y) = X). A renamed
 * component is checked the same way before any of its definitions is posed,
 * and so is the result. A violation goes through tlib::error.
 *
 * Preconditions on the rule, beyond those of treeRewrite : its result must
 * not depend on the names of the recursive variables (a rule that orders its
 * terms by serial number sees a provisional name as the newest node, and may
 * order differently), and its side effects must tolerate a subtree rewritten
 * again after a provisional result was discarded.
 */
#include <algorithm>
#include <functional>
#include <unordered_set>
#include <vector>

namespace tlibrwm {

// The groups and their components come from RecPlan (tree.hh) : every SYMREC
// node reachable from a root, bodies included, partitioned into the strongly
// connected components of "the body of X mentions Y" by DirectedGraph's Tarjan,
// dependencies first. RecPlan orders independent components by structural
// discovery rank, never by serial, so alpha-equivalent inputs get the same plan.

inline Tree groupBody(Tree n)
{
    Tree var = nullptr, body = nullptr;
    isRec(n, var, body);
    return body;
}

// the SYMREC nodes met from t without entering them, in depth-first order ; used
// on a candidate body, whose own groups are not defined yet
inline void scanGroups(Tree t, std::unordered_set<Tree>& seen, std::vector<Tree>& found)
{
    std::vector<Tree> stack{t};
    while (!stack.empty()) {
        Tree s = stack.back();
        stack.pop_back();
        if (!seen.insert(s).second) {
            continue;
        }
        Tree var = nullptr, body = nullptr;
        if (isRec(s, var, body)) {
            found.push_back(s);
            continue;
        }
        for (int i = s->arity() - 1; i >= 0; i--) {
            stack.push_back(s->branch(i));
        }
    }
}

// the two conditions on the groups of a plan : every group is defined, and no
// cycle is made of direct references alone (D(X) = Y, D(Y) = X)
inline void checkWellFormed(const RecPlan& plan)
{
    for (const std::vector<Tree>& comp : plan.components()) {
        for (Tree g : comp) {
            if (groupBody(g) == nullptr) {
                tlib::error("treeRewriteMinimal : a recursive group has no definition");
            }
        }
    }
    std::unordered_map<Tree, char> state;  // absent new, 1 on the current chain, 2 done
    for (const std::vector<Tree>& comp : plan.components()) {
        for (Tree v : comp) {
            std::vector<Tree> chain;
            Tree              cur = v;
            while (state[cur] == 0) {
                state[cur] = 1;
                chain.push_back(cur);
                Tree body = groupBody(cur);
                Tree var = nullptr, sub = nullptr;
                if (!isRec(body, var, sub)) {
                    break;
                }
                cur = body;
            }
            if (state[cur] == 1 && !chain.empty() && groupBody(chain.back()) == cur) {
                tlib::error("treeRewriteMinimal : a cycle of recursive groups made of references only");
            }
            for (Tree c : chain) {
                state[c] = 2;
            }
        }
    }
}

// The guard of a rewrite, consulted at most once per input node : its decision
// is kept, because the plan of the groups and the rewrite both need it.
template <class Pre>
struct Guard {
    Pre&                                              pre;
    std::unordered_map<Tree, std::optional<Tree>>     decided;

    const std::optional<Tree>& operator()(Tree s)
    {
        auto it = decided.find(s);
        if (it == decided.end()) {
            std::optional<Tree> c = pre(s);
            TLIB_ASSERT(!c.has_value() || *c != nullptr);
            it = decided.emplace(s, c).first;
        }
        return it->second;
    }
};

// the pair (I(s), R(s)) of one component ; I is nullptr once no longer built.
// The rule is paired, rule(orig, rebuilt) : orig is always an input node, never
// a renamed one, so its annotations stay readable while C takes fresh names.
template <class Pre, class Rule, class DefRule>
struct Component {
    Guard<Pre>&                                       guard;
    Rule&                                             rule;
    DefRule&                                          defRule;
    bool                                              listBodies;  // the definition seam of treeRewritePaired
    std::unordered_map<Tree, Tree>&                   G;
    std::unordered_map<Tree, Tree>                    nu;  // SYMREC node of C -> fresh variable
    std::unordered_map<Tree, std::pair<Tree, Tree>>   P;
    std::unordered_map<Tree, Tree>                    renamed;  // memo of rename
    bool                                              compare = true;

    // s with the groups of C renamed and nothing else : the I of a subtree that
    // the guard cut. No rule, no guard, and the references stop the descent.
    Tree rename(Tree s)
    {
        if (s->isRecFree() || G.count(s)) {
            return s;  // a decided subtree cannot mention C
        }
        auto itR = renamed.find(s);
        if (itR != renamed.end()) {
            return itR->second;
        }
        Tree res = s;
        Tree var = nullptr, body = nullptr;
        if (isRec(s, var, body)) {
            auto itN = nu.find(s);
            if (itN != nu.end()) {
                res = ref(itN->second);
            }
        } else {
            int  ar = s->arity();
            tvec br(ar);
            bool c = false;
            for (int k = 0; k < ar; k++) {
                br[k] = rename(s->branch(k));
                c     = c || br[k] != s->branch(k);
            }
            if (c) {
                res = tree(s->node(), br);
            }
        }
        renamed[s] = res;
        return res;
    }

    std::pair<Tree, Tree> visit(Tree s)
    {
        auto itP = P.find(s);
        if (itP != P.end()) {
            return itP->second;
        }
        Tree i = nullptr, r = nullptr;
        auto itG = G.find(s);
        Tree var = nullptr, body = nullptr;
        if (itG != G.end()) {
            // decided earlier : it cannot mention C, so renaming C leaves it as it is
            i = compare ? s : nullptr;
            r = itG->second;
        } else if (isRec(s, var, body)) {
            auto itN = nu.find(s);
            if (itN == nu.end()) {
                tlib::error("treeRewriteMinimal : a group met before its component is decided");
            }
            Tree n = ref(itN->second);  // the reference stops the descent : bodies are visited by the component
            i      = compare ? n : nullptr;
            r      = n;
        } else if (const std::optional<Tree>& cut = guard(s); cut.has_value()) {
            // what the guard cuts enters the result as it is, and I is the plain
            // renaming : a cut that mentions C forces the renaming of C, and keeps
            // the old names inside (LA-REECRITURE-MINIMALE, the guard)
            i = compare ? rename(s) : nullptr;
            r = *cut;
        } else {
            int  ar = s->arity();
            tvec bi(ar), br(ar);
            bool ci = false, cr = false;
            for (int k = 0; k < ar; k++) {
                auto pr = visit(s->branch(k));
                bi[k]   = pr.first;
                br[k]   = pr.second;
                ci      = ci || bi[k] != s->branch(k);
                cr      = cr || br[k] != s->branch(k);
            }
            if (compare) {
                for (int k = 0; k < ar; k++) {
                    TLIB_ASSERT(bi[k] != nullptr);
                }
                i = ci ? tree(s->node(), bi) : s;
            }
            r = rule(s, cr ? tree(s->node(), br) : s);
        }
        P[s] = {i, r};
        return {i, r};
    }

    // The pair of a group body. With the definition seam, a list-shaped body is
    // taken definition by definition : defRule applies to R only, at its slot, and
    // neither the cells nor the wrapped definitions enter P, as in treeRewritePaired.
    std::pair<Tree, Tree> visitBody(Tree body)
    {
        if (!listBodies) {
            return visit(body);
        }
        std::vector<std::pair<Tree, Tree>> defs;
        Tree                               l = body;
        while (isList(l)) {
            Tree d  = hd(l);
            auto pr = visit(d);
            defs.push_back({pr.first, defRule(d, pr.second)});
            l = tl(l);
        }
        auto tail = visit(l);
        Tree i = tail.first, r = tail.second;
        for (auto it = defs.rbegin(); it != defs.rend(); ++it) {
            if (compare) {
                i = cons(it->first, i);
            }
            r = cons(it->second, r);
        }
        return {i, r};
    }
};

// The groups a guarded traversal reaches from t (the root, or a group body when
// isBody) : the guard's cuts stop the scan, and with the definition seam a
// list-shaped body is entered at its definitions, its cells never shown to the
// guard -- the nodes the traversal itself shows it, no other.
template <class Pre>
void scanGuarded(Guard<Pre>& guard, bool listBodies, Tree t, bool isBody, std::vector<Tree>& found)
{
    std::unordered_set<Tree> visited;
    std::vector<Tree>        stack;
    if (isBody && listBodies) {
        Tree l = t;
        while (isList(l)) {
            stack.push_back(hd(l));
            l = tl(l);
        }
        stack.push_back(l);
        std::reverse(stack.begin(), stack.end());
    } else {
        stack.push_back(t);
    }
    while (!stack.empty()) {
        Tree s = stack.back();
        stack.pop_back();
        if (s->isRecFree() || !visited.insert(s).second) {
            continue;
        }
        Tree var = nullptr, body = nullptr;
        if (isRec(s, var, body)) {
            found.push_back(s);
            continue;
        }
        if (guard(s).has_value()) {
            continue;
        }
        for (int i = s->arity() - 1; i >= 0; i--) {
            stack.push_back(s->branch(i));
        }
    }
}

template <class Pre, class Rule, class DefRule>
Tree rewriteMinimalCore(Tree root, Pre& pre, Rule& rule, DefRule& defRule, bool listBodies, bool stopI)
{
    Guard<Pre>    guard{pre, {}};
    const RecPlan plan(root, [&](Tree t, bool isBody, std::vector<Tree>& found) {
        scanGuarded(guard, listBodies, t, isBody, found);
    });
    checkWellFormed(plan);
    std::unordered_map<Tree, Tree> G;  // the decided images, keyed by the input nodes

    for (const std::vector<Tree>& comp : plan.components()) {
        Component<Pre, Rule, DefRule> C{guard, rule, defRule, listBodies, G, {}, {}, {}, true};
        for (Tree g : comp) {
            C.nu[g] = tree(unique("W"));
        }
        std::vector<Tree> B;
        bool              differs = false;
        for (Tree g : comp) {
            auto pr = C.visitBody(groupBody(g));
            B.push_back(pr.second);
            if (C.compare && pr.first != pr.second) {
                differs = true;
                if (stopI) {
                    C.compare = false;
                }
            }
        }
        if (!differs) {
            // every body unchanged : the old groups stay, the provisional names are never defined
            for (Tree g : comp) {
                G[g] = g;
            }
            for (auto& e : C.P) {
                if (e.second.first != nullptr && e.second.first == e.second.second) {
                    G[e.first] = e.first;
                }
            }
        } else {
            // candidate bodies, checked before any definition is posed
            std::unordered_map<Tree, Tree> cand;  // new SYMREC node -> its body
            for (size_t j = 0; j < comp.size(); j++) {
                cand[ref(C.nu[comp[j]])] = B[j];
            }
            for (auto& e : cand) {
                Tree   cur   = e.second;
                size_t steps = 0;
                for (auto it = cand.find(cur); it != cand.end(); it = cand.find(cur)) {
                    cur = it->second;
                    if (++steps > cand.size()) {
                        tlib::error("treeRewriteMinimal : a rewritten body reduces to a cycle of references");
                    }
                }
                std::unordered_set<Tree> seen;
                std::vector<Tree>        found;
                scanGroups(e.second, seen, found);
                for (Tree n : found) {
                    if (cand.find(n) == cand.end() && groupBody(n) == nullptr) {
                        tlib::error("treeRewriteMinimal : a rewritten body mentions an undefined group");
                    }
                }
            }
            for (size_t j = 0; j < comp.size(); j++) {
                rec(C.nu[comp[j]], B[j]);
            }
            for (Tree g : comp) {
                G[g] = ref(C.nu[g]);
            }
            for (auto& e : C.P) {
                G[e.first] = e.second.second;
            }
        }
    }

    // the nodes outside every body, and the subtrees whose provisional result was discarded
    std::function<Tree(Tree)> finish = [&](Tree s) -> Tree {
        auto it = G.find(s);
        if (it != G.end()) {
            return it->second;
        }
        Tree var = nullptr, body = nullptr;
        if (isRec(s, var, body)) {
            tlib::error("treeRewriteMinimal : an undecided group outside the definitions");
        }
        Tree res = nullptr;
        if (const std::optional<Tree>& cut = guard(s); cut.has_value()) {
            res = *cut;
        } else {
            int  ar = s->arity();
            tvec br(ar);
            bool c = false;
            for (int k = 0; k < ar; k++) {
                br[k] = finish(s->branch(k));
                c     = c || br[k] != s->branch(k);
            }
            res = rule(s, c ? tree(s->node(), br) : s);
        }
        G[s] = res;
        return res;
    };
    Tree u = finish(root);
    checkWellFormed(RecPlan(u));  // also the groups the rule may have introduced
    return u;
}

template <class Rule>
Tree rewriteMinimal(Tree root, Rule& rule, bool stopI)
{
    auto nopre  = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto paired = [&rule](Tree, Tree rebuilt) { return rule(rebuilt); };
    auto nodef  = [](Tree, Tree rebuilt) { return rebuilt; };
    return rewriteMinimalCore(root, nopre, paired, nodef, false, stopI);
}

}  // namespace tlibrwm

template <class Rule>
Tree treeRewriteMinimal(Tree root, Rule&& rule)
{
    return tlibrwm::rewriteMinimal(root, rule, true);
}

/**
 * The guarded minimal rewrite, the counterpart of treeRewrite(root, pre, post) :
 * pre is consulted top-down on each input node that is not a SYMREC, at most
 * once per node. A cut enters the result as it is, never visited, never given
 * to post. The plan of the groups is built by a scan that stops at the same
 * cuts, so a group reachable only through a cut belongs to no component and is
 * left as it is. A cut is compared with the plain renaming of its subtree : a
 * cut that mentions a group of the current component forces the renaming of
 * that component, and keeps the old names inside -- what the guard cuts is
 * never touched, not even a name.
 */
template <class Pre, class Post>
Tree treeRewriteMinimal(Tree root, Pre&& pre, Post&& post)
{
    auto paired = [&post](Tree, Tree rebuilt) { return post(rebuilt); };
    auto nodef  = [](Tree, Tree rebuilt) { return rebuilt; };
    return tlibrwm::rewriteMinimalCore(root, pre, paired, nodef, false, true);
}

/**
 * treeRewriteMinimalPaired : treeRewritePaired, with the minimal naming of
 * treeRewriteMinimal. The rule receives rule(orig, rebuilt), orig being always
 * an input node ; defRule(origDef, rebuiltDef) wraps each definition of a
 * list-shaped group body at its slot, positionally, as in treeRewritePaired.
 * A wrapped definition that differs from its plain rewrite makes its body
 * differ, so its component is renamed. The optional guard pre follows the
 * guarded treeRewriteMinimal above ; it is never shown the cells of a body.
 *
 * The precondition on the rule becomes one on its second argument only : for a
 * renaming nu of the groups, rule(s, x.nu) = rule(s, x).nu, and the same for
 * defRule. Under this condition the result is alpha-equivalent to the one of
 * treeRewritePaired.
 */
template <class Pre, class Rule, class DefRule>
Tree treeRewriteMinimalPaired(Tree root, Pre&& pre, Rule&& rule, DefRule&& defRule)
{
    return tlibrwm::rewriteMinimalCore(root, pre, rule, defRule, true, true);
}

template <class Rule, class DefRule>
Tree treeRewriteMinimalPaired(Tree root, Rule&& rule, DefRule&& defRule)
{
    auto nopre = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    return tlibrwm::rewriteMinimalCore(root, nopre, rule, defRule, true, true);
}

template <class Rule>
Tree treeRewriteMinimalPaired(Tree root, Rule&& rule)
{
    auto nopre = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto nodef = [](Tree, Tree rebuilt) { return rebuilt; };
    return tlibrwm::rewriteMinimalCore(root, nopre, rule, nodef, true, true);
}

#endif
