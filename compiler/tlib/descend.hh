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
//   THE TWO VALUES OF A DOOR. A recursive node W carries two flows that
//   must not be mixed :
//
//     doorOut(W) = doorSeed(W)   what the door sends into its definition
//     a(W)                       what accumulates ON W -- external uses
//                                and the self-references of its own body
//
//   Keeping them separate IS the mechanism. If doorOut(W) were a(W) --
//   the join of W's incoming edges -- the equation would be circular :
//   through the cycle, a(W) contains contributions that depend on
//   doorOut(W). Sharing does impose that doorOut(W) not depend on WHICH
//   use site asks (the definition has ONE instance, common to every use
//   site) ; it does NOT impose independence from all the sites jointly.
//   That joint dependency is a legitimate circular system, solvable as a
//   least fixpoint under the usual completeness and monotonicity
//   hypotheses -- regime C below, with no finite solution at all for a
//   join like +. Sending doorSeed(W) -- computable from the node W
//   itself, never from its context -- is therefore not a consequence of
//   sharing but the absorbing contract this one-pass analysis adopts :
//   the door does not delay a circular value, it immediately transmits
//   another one, defined precisely not to be circular.
//
//   a(W) is not lost : it is the dividend of the absorption (a maximum
//   delay over every use of a recursive signal lives exactly there). The
//   definition can be entered long before a(W) is complete, since it
//   receives doorSeed(W) and not a(W) ; evaluating it then produces
//   further contributions TOWARD W, collected and never fed back.
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
//      two-values argument. Condition and clock propagation are of this
//      kind.
//   C. TRUE FIXPOINTS (the body would see the join of its entries, which
//      depends on the body) : Kleene iteration over a lattice with a
//      termination argument. OUT OF SCOPE here -- and for a join like +,
//      no finite least solution even exists (a node inside a recursion
//      occurs unboundedly often in the unfolding). See fixpoint.hh for the
//      synthesized counterpart.
//
// The ORDER invariant, in two parts rather than one rule with an
// exception :
//
//   - branch edges follow the Kahn order : a node's join is complete
//     before its branches are processed ;
//   - door edges fire OUTSIDE that order, before the descent -- and may,
//     precisely because their value is doorSeed(W) and reads no
//     accumulator.
//
// So a door enters its definition while a(W) is still incomplete, without
// ever exposing an incomplete value to it. What is never fed back through
// a door is a(W) itself.
//
// The whole system in one equation, doors only in the seed set :
//
//   a(n) = join( S(n) u { contrib(p, i, a(p)) | p --i--> n by a branch } )
//   S(n) = { seed | n = root } u { doorSeed(W) | def(W) = n }
//
// Door edges appear ONLY in S(n) : unlike a branch edge, a door does not
// transmit its source's attribute. That single asymmetry is why every
// door can fire before the descent, and why no recursive equation is
// left to solve in regimes A and B.
//
// The result is returned as an explicit map (treeorder : deterministic),
// deliberately NOT stored in tree properties : two computations with
// different seeds or joins must not collide.

#ifndef __DESCEND__
#define __DESCEND__

#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <utility>
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
    // they carry doorSeed(W) and fire unconditionally.
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
    // (they carry doorSeed(W) and read no accumulator) ; a node becomes
    // ready when every incoming branch edge has fired -- so its join is
    // complete before its branches are processed, and a(W) is never fed
    // back through a door. By the theorem, the branch edges alone are
    // acyclic : the descent reaches every discovered node.
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

// ---------------------------------------------------------------------------
// THE UNIFIED ENGINE -- regime C brought in scope (spec DESCEND-REGIME-C).
//
// The general model : a finite directed graph -- the branch edges, plus any
// extra edges the instance declares (the "doors", which are ordinary edges
// here ; they merely happen to close cycles). Attributes live on nodes ; at
// every node an equation
//
//   a(n) = combine(n, [ values of the incoming edges ] ++ [ seed if root ])
//
// where a branch edge (p --i--> n) carries contrib(p, i, a(p)) and a door
// edge (p --> n) carries doorContrib(p, a(p)). combine receives the LIST of
// incoming values -- not their join -- which is what admits equations that
// COUNT their inputs (saturating sums) as well as plain joins.
//
// Two conditions buy three theorems. If every equation is MONOTONE in each
// argument and the attribute domain has FINITE HEIGHT on reachable chains,
// then the least fixpoint exists (Knaster-Tarski), the fair chaotic
// iteration below reaches it in at most height x |edges| re-evaluations,
// and the result is CANONICAL -- independent of the visiting order. Proof
// of canonicity in three lines : starting from bottom every intermediate
// state stays <= lfp by monotonicity ; the final state (empty worklist)
// satisfies every equation, hence is a fixpoint ; a fixpoint reached from
// below is the least one.
//
// The engine is RECOMPUTE-AND-COMPARE : when a node is scheduled, its
// attribute is recomputed from the current values of its parents and
// propagated only if it changed. Blind accumulation would double-count a
// non-idempotent equation ; recomputation never does. (For idempotent
// joins, accumulation is a legitimate optimization -- not taken here : one
// engine, one semantics, the optimization can come with a measured need.)
//
// The default strategy processes nodes in REVERSE POSTORDER of the extended
// graph : on an acyclic instance the first sweep reaches the fixpoint and
// nothing is ever re-scheduled -- the one-pass regimes are the emergent
// behavior of the default, not a separate mode. The strategy set is CLOSED
// (all members are fair) : fairness is a correctness condition and stays
// inside the engine. Its first use is the cross-strategy canonicity test.
//
// Determinism of the equation inputs : the incoming list of a node is
// ordered by (treeorder of the parent, branch index, door flag), and the
// root seed comes first -- so any combine, commutative or not, sees a
// reproducible list.
// ---------------------------------------------------------------------------

enum class DescendStrategy { kReversePostorder, kFifo, kLifo };

template <typename A>
std::map<Tree, A, treeorder> descendFixpoint(
    Tree root, const A& bottom, const A& seed,
    std::function<A(Tree, int, const A&)>          contrib,
    std::function<A(Tree, const std::vector<A>&)>  combine,
    std::function<void(Tree, std::vector<Tree>&)>  doorTargets = nullptr,
    std::function<A(Tree, const A&)>               doorContrib = nullptr,
    DescendStrategy strategy = DescendStrategy::kReversePostorder)
{
    // default doors : the RECDEF edge of a symbolic recursive node
    if (!doorTargets) {
        doorTargets = [](Tree n, std::vector<Tree>& out) {
            Tree id, body;
            if (isRec(n, id, body) && body != nullptr) {
                out.push_back(body);
            }
        };
    }
    if (!doorContrib) {
        doorContrib = [](Tree, const A& a) { return a; };
    }

    // ---- phase 1 : discover the extended graph. Per node : the incoming
    // edges (parent, branch index ; index -1 = door) and the successors.
    struct Edge {
        Tree parent;
        int  index;  // branch index, or -1 for a door edge
    };
    std::map<Tree, std::vector<Edge>, treeorder> incoming;
    std::map<Tree, std::vector<Tree>, treeorder> successors;
    {
        std::map<Tree, bool, treeorder> seen;
        std::vector<Tree>               work{root};
        seen[root]     = true;
        incoming[root];  // the root exists even without incoming edges
        std::vector<Tree> targets;
        while (!work.empty()) {
            Tree n = work.back();
            work.pop_back();
            auto visit = [&](Tree c) {
                successors[n].push_back(c);
                if (!seen[c]) {
                    seen[c] = true;
                    work.push_back(c);
                }
            };
            for (int i = 0; i < n->arity(); i++) {
                Tree c = n->branch(i);
                incoming[c].push_back({n, i});
                visit(c);
            }
            targets.clear();
            doorTargets(n, targets);
            for (Tree c : targets) {
                incoming[c].push_back({n, -1});
                visit(c);
            }
        }
        // determinism : a node's incoming list is ordered independently of
        // the discovery order
        treeorder lt;
        for (auto& [t, edges] : incoming) {
            std::sort(edges.begin(), edges.end(), [&lt](const Edge& a, const Edge& b) {
                if (a.parent != b.parent) {
                    return lt(a.parent, b.parent);
                }
                return a.index < b.index;
            });
        }
    }

    // ---- phase 2 : the fair chaotic iteration, recompute-and-compare.
    std::map<Tree, A, treeorder> attr;
    for (const auto& [t, e] : incoming) {
        attr.emplace(t, bottom);
    }
    auto recompute = [&](Tree n) -> A {
        std::vector<A> in;
        if (n == root) {
            in.push_back(seed);  // the root's virtual edge, always first
        }
        for (const Edge& e : incoming.at(n)) {
            const A& pa = attr.at(e.parent);
            in.push_back(e.index >= 0 ? contrib(e.parent, e.index, pa)
                                      : doorContrib(e.parent, pa));
        }
        return combine(n, in);
    };

    // rank : reverse postorder of the extended graph (iterative DFS,
    // finishing order reversed). On an acyclic instance, processing by
    // ascending rank makes the first sweep exact.
    std::map<Tree, int, treeorder> rank;
    {
        std::map<Tree, int, treeorder> state;  // 0 new, 1 expanded
        std::vector<Tree>              stack{root};
        std::vector<Tree>              post;
        while (!stack.empty()) {
            Tree n = stack.back();
            if (state[n] == 0) {
                state[n] = 1;
                auto it  = successors.find(n);
                if (it != successors.end()) {
                    for (auto r = it->second.rbegin(); r != it->second.rend(); ++r) {
                        if (state[*r] == 0) {
                            stack.push_back(*r);
                        }
                    }
                }
            } else {
                stack.pop_back();
                if (rank.find(n) == rank.end()) {
                    post.push_back(n);
                    rank[n] = 0;  // placeholder
                }
            }
        }
        int r = 0;
        for (auto it = post.rbegin(); it != post.rend(); ++it) {
            rank[*it] = r++;
        }
    }

    // the worklist : a strategy-ordered set of scheduled nodes. All three
    // strategies are fair (every scheduled node is eventually processed).
    std::vector<Tree>               fifo, lifo;
    std::set<std::pair<int, Tree>>  prio;
    std::map<Tree, bool, treeorder> queued;
    auto push = [&](Tree t) {
        if (queued[t]) {
            return;
        }
        queued[t] = true;
        switch (strategy) {
            case DescendStrategy::kReversePostorder:
                prio.insert({rank.at(t), t});
                break;
            case DescendStrategy::kFifo:
                fifo.push_back(t);
                break;
            case DescendStrategy::kLifo:
                lifo.push_back(t);
                break;
        }
    };
    auto pop = [&]() -> Tree {
        Tree t;
        switch (strategy) {
            case DescendStrategy::kReversePostorder:
                t = prio.begin()->second;
                prio.erase(prio.begin());
                break;
            case DescendStrategy::kFifo:
                t = fifo.front();
                fifo.erase(fifo.begin());
                break;
            case DescendStrategy::kLifo:
                t = lifo.back();
                lifo.pop_back();
                break;
        }
        queued[t] = false;
        return t;
    };
    auto empty = [&]() {
        return prio.empty() && fifo.empty() && lifo.empty();
    };

    for (const auto& [t, e] : incoming) {
        push(t);
    }
    while (!empty()) {
        Tree n = pop();
        A    v = recompute(n);
        if (!(v == attr.at(n))) {
            attr.at(n) = v;
            auto it    = successors.find(n);
            if (it != successors.end()) {
                for (Tree s : it->second) {
                    push(s);
                }
            }
        }
    }
    return attr;
}

#endif
