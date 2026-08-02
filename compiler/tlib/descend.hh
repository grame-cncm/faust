/*
 * TLIB : tree library
 * Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

// Generic DESCENDING (inherited) attribute over a tree or DAG.
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
//                  parents (sum for occurrence counts, min for depths,
//                  lattice joins for clock environments, or/and for
//                  conditions...)
//   order        : parents before children (topological descent from the
//                  root), a node's join being COMPLETE before its own
//                  descent -- the invariant every hand-written pass
//                  (occurrences, clkEnv, conditions) reimplements.
//
// Cycles (symbolic recursive trees) : back edges -- an edge whose target is
// on the current exploration stack -- are excluded from the readiness
// counts, so the descent terminates. Their contributions are applied by
// BOUNDED ROUNDS (recRounds) : each extra round replays the descent with
// the previous round's attributes feeding the back edges (a truncated
// Kleene iteration ; recRounds = 0 simply cuts them).
//
// The result is returned as an explicit map (treeorder : deterministic),
// deliberately NOT stored in tree properties : two computations with
// different seeds or joins must not collide.

#ifndef __DESCEND__
#define __DESCEND__

#include <functional>
#include <map>
#include <utility>
#include <vector>

#include "tree.hh"

template <typename A>
std::map<Tree, A, treeorder> descendAttribute(
    Tree root, const A& seed,
    std::function<A(Tree, int, const A&)>    contrib,
    std::function<A(const A&, const A&)>     join,
    int                                      recRounds = 0)
{
    // ---- phase 1 : iterative exploration, classify back edges
    std::map<Tree, int, treeorder> state;  // 0 unseen, 1 on stack, 2 done
    std::vector<Tree>              order;  // parents-before-children capable order
    std::map<Tree, int, treeorder> fwdParents;
    struct Edge {
        Tree parent;
        int  branch;
    };
    std::map<Tree, std::vector<Edge>, treeorder> backIn;  // back edges, per target
    {
        std::vector<std::pair<Tree, int>> stack;
        stack.push_back({root, 0});
        state[root]      = 1;
        fwdParents[root] = 0;
        while (!stack.empty()) {
            Tree n = stack.back().first;
            int& i = stack.back().second;
            if (i == n->arity()) {
                state[n] = 2;
                order.push_back(n);  // post-order : reversed = parents first
                stack.pop_back();
                continue;
            }
            Tree c = n->branch(i);
            int  b = i;
            i++;
            int st = state.count(c) ? state[c] : 0;
            if (st == 1) {
                backIn[c].push_back({n, b});  // back edge : cycle
            } else {
                fwdParents[c] += 1;
                if (st == 0) {
                    state[c] = 1;
                    stack.push_back({c, 0});
                }
            }
        }
    }

    // ---- phase 2 (+ rounds) : Kahn descent, joins complete before descent
    std::map<Tree, A, treeorder> attr;
    for (int round = 0; round <= recRounds; round++) {
        std::map<Tree, A, treeorder>   next;
        std::map<Tree, int, treeorder> pending = fwdParents;
        auto inject = [&](Tree t, const A& a) {
            auto it = next.find(t);
            if (it == next.end()) {
                next.emplace(t, a);
            } else {
                it->second = join(it->second, a);
            }
        };
        inject(root, seed);
        // back-edge contributions come from the PREVIOUS round
        if (round > 0) {
            for (const auto& [t, edges] : backIn) {
                for (const Edge& e : edges) {
                    auto pa = attr.find(e.parent);
                    if (pa != attr.end()) {
                        inject(t, contrib(e.parent, e.branch, pa->second));
                    }
                }
            }
        }
        std::vector<Tree> ready;
        ready.push_back(root);
        while (!ready.empty()) {
            Tree n = ready.back();
            ready.pop_back();
            const A& an = next.at(n);
            for (int b = 0; b < n->arity(); b++) {
                Tree c = n->branch(b);
                bool isBack = false;
                auto bi     = backIn.find(c);
                if (bi != backIn.end()) {
                    for (const Edge& e : bi->second) {
                        if (e.parent == n && e.branch == b) {
                            isBack = true;
                            break;
                        }
                    }
                }
                if (isBack) {
                    continue;
                }
                inject(c, contrib(n, b, an));
                if (--pending[c] == 0) {
                    ready.push_back(c);
                }
            }
        }
        attr = std::move(next);
    }
    return attr;
}

#endif
