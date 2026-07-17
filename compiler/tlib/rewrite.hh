/*
 * TLIB : tree library
 * Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#ifndef __REWRITE__
#define __REWRITE__

#include <optional>
#include <unordered_map>

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
 * result is only alpha-equivalent to the input (areEquiv, not ==).
 * treeRewriteInPlace() reuses the same variable : rec(var, newBody) updates
 * RECDEF on the shared SYMREC(var) node. Destructive on the old tree, but
 * pointer-stable : treeRewriteInPlace(t, identity) == t.
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
 * while treeRewriteInPlace keeps the recursive variable :
 *
 *   body => body'
 *   ------------------------------- (rec-in-place)
 *   rec(var, body) => rec(var, body')
 *
 * In both cases, the memo is initialized before descending into body so that
 * recursive references to the definition have a target during the traversal.
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

template <class Rule>
Tree treeRewriteInPlaceMemo(Tree t, Rule& rule, std::unordered_map<Tree, Tree>& memo)
{
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }

    Tree var  = nullptr;
    Tree body = nullptr;
    if (isRec(t, var, body)) {
        TLIB_ASSERT(body != nullptr);
        // self-mapping : recursive references and shared occurrences of t
        // resolve to t itself; rec(var, newBody) below returns this same
        // pointer, so the memo entry is already final
        memo[t]      = t;
        Tree newBody = treeRewriteInPlaceMemo(body, rule, memo);
        return rec(var, newBody);
    }

    int  ar = t->arity();
    Tree r  = t;
    if (ar > 0) {
        bool changed = false;
        tvec br(ar);
        for (int i = 0; i < ar; i++) {
            br[i]   = treeRewriteInPlaceMemo(t->branch(i), rule, memo);
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
Tree treeRewriteInPlace(Tree root, Rule&& rule)
{
    std::unordered_map<Tree, Tree> memo;
    return treeRewriteInPlaceMemo(root, rule, memo);
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

template <class Pre, class Post>
Tree treeRewriteInPlaceMemo(Tree t, Pre& pre, Post& post, std::unordered_map<Tree, Tree>& memo)
{
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }

    Tree var  = nullptr;
    Tree body = nullptr;
    if (isRec(t, var, body)) {
        TLIB_ASSERT(body != nullptr);
        memo[t]      = t;
        Tree newBody = treeRewriteInPlaceMemo(body, pre, post, memo);
        return rec(var, newBody);
    }

    Tree r;
    std::optional<Tree> cut = pre(t);
    if (cut.has_value()) {
        TLIB_ASSERT(*cut != nullptr);
        memo[t] = *cut;
        return *cut;
    } else {
        int ar = t->arity();
        r      = t;
        if (ar > 0) {
            bool changed = false;
            tvec br(ar);
            for (int i = 0; i < ar; i++) {
                br[i]   = treeRewriteInPlaceMemo(t->branch(i), pre, post, memo);
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
Tree treeRewriteInPlace(Tree root, Pre&& pre, Post&& post)
{
    std::unordered_map<Tree, Tree> memo;
    return treeRewriteInPlaceMemo(root, pre, post, memo);
}

#endif
