/*
 * TLIB : tree library
 * Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

// Generic DESCENDING (inherited) attribute over a tree, a DAG, or a
// SYMBOLIC recursive term.
//
// A synthesized attribute is a function of the subtree : hash-consing plus a
// memoized recursion computes it once per shared node -- the tlib serves that
// direction natively (and fixpoint.hh generalizes it to recursive terms). An
// INHERITED attribute is a function of the CONTEXT : on a shared DAG a node
// has several contexts, so the attribute only exists through three explicit
// ingredients this header provides once and for all :
//
//   contribution : (parent, branch index, parent attribute) -> child part
//   join         : aggregation of the parts reaching a node from all its
//                  incoming edges (sum for occurrence counts, min for
//                  depths, max for delays, lattice joins for clock
//                  environments...). The join MUST be associative and
//                  commutative : contributions arrive in an unspecified
//                  order and are folded as they come.
//   order        : joins complete before descent (see the invariant below).
//
// RECURSIVE TERMS. Recursive flow is interpreted in SYMBOLIC form only :
// the traversal follows the branches PLUS the doors -- a symbolic
// recursive node (SYMREC) holds its definition behind the RECDEF
// property, never behind a branch, and the descent crosses that property
// edge exactly once per door. (A de Bruijn term is traversed as its
// finite syntactic DAG : its references are indices and are NOT resolved.
// Convert with deBruijn2Sym first when the recursive flow matters.)
//
// Two structural facts make the recursive descent exact and finite :
//
//   THE THEOREM. The branch graph is acyclic by construction (hash-consing
//   builds parents from existing children, branches are never mutated), so
//   EVERY cycle of the extended graph crosses a door edge.
//
//   THE CONSTANCY OF DOORS. Write out(W) for the information a door W sends
//   into its definition. If out(W) were a function of W's context -- the
//   join of W's incoming edges -- the equation would be circular : through
//   the cycle, W's context contains contributions that depend on out(W).
//   Sharing does impose that out(W) not depend on WHICH use site asks (the
//   definition has ONE instance, common to every use site) ; it does NOT
//   impose independence from all the sites jointly. That joint dependency
//   is a legitimate circular system, solvable as a least fixpoint under
//   the usual completeness and monotonicity hypotheses -- regime C below,
//   with no finite solution at all for a join like +. Taking out(W)
//   CONSTANT with respect to the context -- independent of the context,
//   though it may perfectly well be computed from the node W itself
//   (doorSeed below) -- is therefore not a consequence of sharing but the
//   absorbing contract this one-pass analysis adopts.
//
//   The caller's context is not lost : it lands ON the door. A door node
//   accumulates, like any node, the join of ALL its incoming edges --
//   external uses and the self-references inside its own body alike. That
//   accumulator is the dividend of the absorption (it is where a maximum
//   delay over every use of a recursive signal lives) ; it completes only
//   at the end of the traversal and is never transmitted downward.
//
// Three regimes of attributes follow, in decreasing comfort :
//
//   A. EDGE-LOCAL : the contribution ignores the parent attribute (it
//      depends on the parent node and branch index alone). The attribute of
//      a node is then a join over its finitely many incoming EDGES, not
//      over the infinitely many paths : exact in one pass, cycles harmless.
//      Edge counting (contribution 1 per edge) is of this kind ; so is a
//      max-delay analysis whose contribution is read off the parent node's
//      own label rather than off the inherited attribute. Path counting
//      and depth chain through the parent attribute -- regime B ; on a
//      cyclic graph the path count is even infinite while the edge count
//      stays finite : two different quantities, not two spellings of one.
//   B. CHAINED WITH ABSORBING DOORS : the contribution reads the parent
//      attribute ; the door replaces it with doorSeed(W). Each definition
//      is analyzed once, independently of its use sites -- exact by the
//      constancy argument. Condition and clock propagation are of this
//      kind.
//   C. TRUE FIXPOINTS (the body would see the join of its entries, which
//      depends on the body) : Kleene iteration over a lattice with a
//      termination argument. OUT OF SCOPE here -- and for a join like +,
//      no finite least solution even exists (a node inside a recursion
//      occurs unboundedly often in the unfolding). See fixpoint.hh for the
//      synthesized counterpart.
//
// The ORDER invariant, restated honestly : a node's join is complete
// before its own descent, EXCEPT the door accumulators, which are only
// complete at the end of the traversal and are never read by the descent.
//
// The result is returned as an explicit map (treeorder : deterministic),
// deliberately NOT stored in tree properties : two computations with
// different seeds or joins must not collide.

#ifndef __DESCEND__
#define __DESCEND__

#include <functional>
#include <map>
#include <vector>

#include "tlib-error.hh"
#include "tree.hh"

template <typename A>
std::map<Tree, A, treeorder> descendAttribute(
    Tree root, const A& seed,
    std::function<A(Tree, int, const A&)> contrib,
    std::function<A(const A&, const A&)>  join,
    std::function<A(Tree)>                doorSeed = nullptr)
{
    // ---- phase 1 : discover the extended graph (branches + doors), count
    // the incoming BRANCH edges of every node. Door edges are not counted :
    // they carry a constant and fire unconditionally.
    std::map<Tree, int, treeorder>  pending;  // incoming branch edges
    std::vector<std::pair<Tree, Tree>> doors;    // (door, definition)
    {
        std::map<Tree, bool, treeorder> seen;
        std::vector<Tree>               work{root};
        seen[root] = true;
        pending[root];  // ensure the entry exists (in-degree 0 so far)
        while (!work.empty()) {
            Tree n = work.back();
            work.pop_back();
            Tree id, body;
            if (isRec(n, id, body) && body != nullptr) {
                doors.push_back({n, body});
                pending[body];
                if (!seen[body]) {
                    seen[body] = true;
                    work.push_back(body);
                }
            }
            for (int i = 0; i < n->arity(); i++) {
                Tree c = n->branch(i);
                pending[c] += 1;
                if (!seen[c]) {
                    seen[c] = true;
                    work.push_back(c);
                }
            }
        }
    }

    // ---- phase 2 : one global Kahn descent. The door edges fire first
    // (their information is constant) ; a node becomes ready when every
    // incoming branch edge has fired -- so its join is complete before its
    // descent, doors' accumulators excepted. By the theorem, the branch
    // edges alone are acyclic : the descent reaches every discovered node.
    std::map<Tree, A, treeorder> attr;
    auto inject = [&](Tree t, const A& a) {
        auto it = attr.find(t);
        if (it == attr.end()) {
            attr.emplace(t, a);
        } else {
            it->second = join(it->second, a);
        }
    };
    inject(root, seed);
    for (const auto& [w, body] : doors) {
        inject(body, doorSeed ? doorSeed(w) : seed);
    }
    std::vector<Tree> ready;
    for (const auto& [t, p] : pending) {
        if (p == 0) {
            ready.push_back(t);
        }
    }
    size_t processed = 0;
    while (!ready.empty()) {
        Tree n = ready.back();
        ready.pop_back();
        processed++;
        const A& an = attr.at(n);
        for (int i = 0; i < n->arity(); i++) {
            Tree c = n->branch(i);
            inject(c, contrib(n, i, an));
            if (--pending[c] == 0) {
                ready.push_back(c);
            }
        }
    }
    // runtime witness of the theorem : if a cycle avoided the doors, some
    // node would keep a positive count and this would fail
    TLIB_ASSERT(processed == pending.size());
    return attr;
}

#endif
