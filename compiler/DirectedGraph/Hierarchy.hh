/*
 * Copyright (c) 2026, Yann Orlarey
 * SPDX-License-Identifier: Apache-2.0
 */

//
//  Hierarchy.hh
//  DirectedGraph
//
//  A hierarchy over a delay graph : a laminar family of parts of the nodes,
//  each part identified by its content, such that every part can be executed
//  as a block (without interleaving with what lies outside it) and the parts
//  of one level can be ordered. The specification is HIERARCHY-SPEC.md at
//  the root of the repository ; this file follows it section by section.
//
//  A hierarchy is a value, like a digraph : construction operations return a
//  new hierarchy, equality and order take the graph, the family and the own
//  labels into account.
//

#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "DirectedGraph.hh"
#include "DirectedGraphAlgorythm.hh"

template <typename N, typename L = std::monostate>
class hierarchy {
   public:
    using Group = std::set<N, dgorder<N>>;  // a group is its content

    // Groups are ordered lexicographically through dgorder<N>, never through
    // std::set's own operator< (which compares elements with their operator<,
    // address order for pointers) -- the same care digraph takes for nodes.
    struct GroupLess {
        bool operator()(const Group& a, const Group& b) const
        {
            return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), dgorder<N>());
        }
    };

    // The vertices of a quotient : a child, to descend into ; an own
    // component, recursive or a single node, to treat as a whole.
    struct Child {
        Group group;
        bool  operator<(const Child& o) const { return GroupLess()(group, o.group); }
        bool  operator==(const Child& o) const { return group == o.group; }
    };
    struct Own {
        Group nodes;
        bool  operator<(const Own& o) const { return GroupLess()(nodes, o.nodes); }
        bool  operator==(const Own& o) const { return nodes == o.nodes; }
    };
    using Vertex = std::variant<Child, Own>;

   private:
    using Family = std::set<Group, GroupLess>;
    using Labels = std::map<Group, L, GroupLess>;

    digraph<N> fGraph;   // the graph, never modified
    Group      fNodes;   // V
    Family     fGroups;  // H, V included (the empty part on the empty graph)
    Labels     fLabels;  // the own labels, a partial map

    //--------------------------------------------------------------------------
    // set helpers, all through dgorder<N>
    //--------------------------------------------------------------------------

    static bool subset(const Group& a, const Group& b)
    {
        return std::includes(b.begin(), b.end(), a.begin(), a.end(), dgorder<N>());
    }
    static bool disjoint(const Group& a, const Group& b)
    {
        dgorder<N> lt;
        auto       i = a.begin();
        auto       j = b.begin();
        while (i != a.end() && j != b.end()) {
            if (lt(*i, *j)) {
                ++i;
            } else if (lt(*j, *i)) {
                ++j;
            } else {
                return false;
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------
    // the family's tree, derived from inclusion
    //--------------------------------------------------------------------------

    // the children of a within a family : the maximal groups strictly inside
    // a. By laminarity the children are pairwise disjoint, so a candidate
    // taken by decreasing size is a child iff it lies inside none of the
    // children already accepted : one sweep, no pairwise comparison.
    static std::vector<Group> childrenIn(const Family& fam, const Group& a)
    {
        std::vector<const Group*> inside;
        for (const Group& b : fam) {
            if (b.size() < a.size() && subset(b, a)) {
                inside.push_back(&b);
            }
        }
        std::stable_sort(inside.begin(), inside.end(),
                         [](const Group* x, const Group* y) { return x->size() > y->size(); });
        std::vector<Group> kids;
        for (const Group* b : inside) {
            bool covered = false;
            for (const Group& k : kids) {
                if (subset(*b, k)) {
                    covered = true;
                    break;
                }
            }
            if (!covered) {
                kids.push_back(*b);
            }
        }
        return kids;
    }

    // the smallest group of a family strictly containing a, if any
    static std::optional<Group> parentIn(const Family& fam, const Group& a)
    {
        std::optional<Group> best;
        for (const Group& b : fam) {
            if (b.size() > a.size() && subset(a, b) && (!best || b.size() < best->size())) {
                best = b;
            }
        }
        return best;
    }

    // the quotient of a within a family (HIERARCHY-SPEC.md, "Quotient d'un
    // groupe") : children and own components contracted, internal edges
    // dropped, the delays of merged edges united
    // Each vertex is stored once ; the nodes map to its index, so a group of
    // k nodes costs k entries, not k copies of itself. The own components are
    // computed on the subgraph induced by the own nodes at every call, on
    // purpose : a candidate family under test may cut a component of the
    // graph, and the quotient must see the cut.
    digraph<Vertex> quotientIn(const Family& fam, const Group& a) const
    {
        std::vector<Vertex>           vertices;
        std::map<N, size_t, dgorder<N>> indexOf;
        for (const Group& k : childrenIn(fam, a)) {
            for (const N& n : k) {
                indexOf.emplace(n, vertices.size());
            }
            vertices.push_back(Child{k});
        }
        // the own nodes and the subgraph they induce
        Group      own;
        digraph<N> sub;
        for (const N& n : a) {
            if (indexOf.count(n) == 0) {
                own.insert(n);
                sub.add(n);
            }
        }
        for (const N& u : own) {
            for (const auto& dst : fGraph.destinations(u)) {
                if (own.count(dst.first)) {
                    sub.add(u, dst.first, dst.second);
                }
            }
        }
        Tarjan<N> T(sub);
        for (const auto& comp : T.partition()) {
            Group g(comp.begin(), comp.end());
            for (const N& n : g) {
                indexOf.emplace(n, vertices.size());
            }
            vertices.push_back(Own{g});
        }
        digraph<Vertex> q;
        for (const Vertex& v : vertices) {
            q.add(v);
        }
        for (const N& u : a) {
            size_t iu = indexOf.at(u);
            for (const auto& dst : fGraph.destinations(u)) {
                auto it = indexOf.find(dst.first);
                if (it == indexOf.end()) {
                    continue;  // an edge leaving a : not part of the quotient
                }
                if (it->second != iu) {
                    q.add(vertices[iu], vertices[it->second], dst.second);  // add unites the delay sets
                }
            }
        }
        return q;
    }

    void requireGroup(const Group& a, const char* op) const
    {
        if (fGroups.count(a) == 0) {
            throw std::invalid_argument(std::string("hierarchy::") + op + " : not a group of the family");
        }
    }
    void requireNode(const N& n, const char* op) const
    {
        if (fNodes.count(n) == 0) {
            throw std::invalid_argument(std::string("hierarchy::") + op + " : not a node of the graph");
        }
    }

   public:
    //--------------------------------------------------------------------------
    // construction
    //--------------------------------------------------------------------------

    // H = { V }, V possibly empty. The graph is assumed well formed (its
    // instantaneous subgraph acyclic) ; check() verifies it.
    explicit hierarchy(const digraph<N>& g) : fGraph(g)
    {
        for (const N& n : g.nodes()) {
            fNodes.insert(n);
        }
        fGroups.insert(fNodes);
    }

    // The new hierarchy with s as a group, or nothing with the violated
    // invariant in why. The identity on an existing group, V included.
    std::optional<hierarchy> group(const Group& s, std::string* why = nullptr) const
    {
        auto refuse = [&](const char* msg) -> std::optional<hierarchy> {
            if (why) {
                *why = msg;
            }
            return std::nullopt;
        };
        if (fGroups.count(s)) {
            return *this;
        }
        if (s.empty()) {
            return refuse("H-NonEmpty : a group is not empty");
        }
        if (!subset(s, fNodes)) {
            return refuse("unknown node : a group is a part of the graph's nodes");
        }
        for (const Group& a : fGroups) {
            if (!subset(s, a) && !subset(a, s) && !disjoint(s, a)) {
                return refuse("H-Laminar : the part overlaps an existing group");
            }
        }
        Family fam = fGroups;
        fam.insert(s);
        std::optional<Group> p = parentIn(fam, s);  // exists : V contains s strictly
        if (!p) {
            return refuse("H-Laminar : no parent");  // cannot happen, s != V here
        }
        if (cycles(quotientIn(fam, *p)) > 0) {
            return refuse("H-Acyclic : the part closes a cycle among the children of its parent");
        }
        hierarchy h(*this);
        h.fGroups = std::move(fam);
        return h;
    }

    // H \ { a }, with a's own label ; a must be a group other than V
    hierarchy flatten(const Group& a) const
    {
        requireGroup(a, "flatten");
        if (a == fNodes) {
            throw std::invalid_argument("hierarchy::flatten : the root stays");
        }
        hierarchy h(*this);
        h.fGroups.erase(a);
        h.fLabels.erase(a);
        return h;
    }

    hierarchy label(const Group& a, const L& l) const
    {
        requireGroup(a, "label");
        hierarchy h(*this);
        h.fLabels.insert_or_assign(a, l);
        return h;
    }

    //--------------------------------------------------------------------------
    // derived notions, all from inclusion and edges
    //--------------------------------------------------------------------------

    const digraph<N>& graph() const { return fGraph; }
    const Group&      root() const { return fNodes; }
    size_t            size() const { return fGroups.size(); }
    bool              isGroup(const Group& a) const { return fGroups.count(a) > 0; }
    const std::set<Group, GroupLess>& groups() const { return fGroups; }

    std::optional<Group> parent(const Group& a) const
    {
        requireGroup(a, "parent");
        return parentIn(fGroups, a);
    }
    std::vector<Group> children(const Group& a) const
    {
        requireGroup(a, "children");
        return childrenIn(fGroups, a);
    }
    // from V down to the own group of n
    std::vector<Group> lineage(const N& n) const
    {
        requireNode(n, "lineage");
        std::vector<Group> l;
        for (const Group& a : fGroups) {
            if (a.count(n)) {
                l.push_back(a);
            }
        }
        std::sort(l.begin(), l.end(), [](const Group& a, const Group& b) { return a.size() > b.size(); });
        return l;
    }
    // the smallest group holding n ; it may have children
    const Group& ownGroup(const N& n) const
    {
        requireNode(n, "ownGroup");
        const Group* best = nullptr;
        for (const Group& a : fGroups) {
            if (a.count(n) && (!best || a.size() < best->size())) {
                best = &a;
            }
        }
        return *best;  // V holds every node
    }
    // the smallest group holding u and v
    const Group& lca(const N& u, const N& v) const
    {
        requireNode(u, "lca");
        requireNode(v, "lca");
        const Group* best = nullptr;
        for (const Group& a : fGroups) {
            if (a.count(u) && a.count(v) && (!best || a.size() < best->size())) {
                best = &a;
            }
        }
        return *best;
    }
    digraph<Vertex> quotient(const Group& a) const
    {
        requireGroup(a, "quotient");
        return quotientIn(fGroups, a);
    }
    // the edges with exactly one end in a
    std::vector<std::pair<N, N>> boundary(const Group& a) const
    {
        requireGroup(a, "boundary");
        std::vector<std::pair<N, N>> b;
        for (const N& u : fNodes) {
            for (const auto& dst : fGraph.destinations(u)) {
                if (a.count(u) != a.count(dst.first)) {
                    b.emplace_back(u, dst.first);
                }
            }
        }
        return b;
    }
    // the effective label : own, else inherited
    std::optional<L> label(const Group& a) const
    {
        requireGroup(a, "label");
        std::optional<Group> g = a;
        while (g) {
            auto it = fLabels.find(*g);
            if (it != fLabels.end()) {
                return it->second;
            }
            g = parentIn(fGroups, *g);
        }
        return std::nullopt;
    }
    // the own label, the one that takes part in equality
    std::optional<L> ownLabel(const Group& a) const
    {
        requireGroup(a, "ownLabel");
        auto it = fLabels.find(a);
        if (it == fLabels.end()) {
            return std::nullopt;
        }
        return it->second;
    }

    //--------------------------------------------------------------------------
    // verification, for the tests and the gates
    //--------------------------------------------------------------------------

    bool check(std::string* why = nullptr) const
    {
        auto fail = [&](const std::string& msg) {
            if (why) {
                *why = msg;
            }
            return false;
        };
        // well formed : the instantaneous subgraph is acyclic
        digraph<N> g0;
        for (const N& n : fNodes) {
            g0.add(n);
        }
        for (const N& u : fNodes) {
            for (const auto& dst : fGraph.destinations(u)) {
                if (dst.second.count(0)) {
                    if (dst.first == u) {
                        return fail("not well formed : an instantaneous self-loop");
                    }
                    g0.add(u, dst.first, 0);
                }
            }
        }
        if (cycles(g0) > 0) {
            return fail("not well formed : the instantaneous subgraph has a cycle");
        }
        if (fGroups.count(fNodes) == 0) {
            return fail("the root is missing");
        }
        for (const Group& a : fGroups) {
            if (a.empty() && !fNodes.empty()) {
                return fail("H-NonEmpty : an empty group on a non-empty graph");
            }
            if (!subset(a, fNodes)) {
                return fail("a group holds a node that is not in the graph");
            }
        }
        for (const Group& a : fGroups) {
            for (const Group& b : fGroups) {
                if (!subset(a, b) && !subset(b, a) && !disjoint(a, b)) {
                    return fail("H-Laminar : two groups overlap");
                }
            }
        }
        for (const Group& a : fGroups) {
            if (cycles(quotientIn(fGroups, a)) > 0) {
                return fail("H-Acyclic : a quotient has a cycle");
            }
        }
        for (const auto& kv : fLabels) {
            if (fGroups.count(kv.first) == 0) {
                return fail("a label on a part that is not a group");
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------
    // a value : the graph, the family and the own labels take part in
    // equality and order ; L must be comparable when these are instantiated
    //--------------------------------------------------------------------------

    friend bool operator==(const hierarchy& a, const hierarchy& b)
    {
        return a.fGraph == b.fGraph && a.fGroups == b.fGroups && a.fLabels == b.fLabels;
    }
    friend bool operator!=(const hierarchy& a, const hierarchy& b) { return !(a == b); }
    friend bool operator<(const hierarchy& a, const hierarchy& b)
    {
        if (a.fGraph < b.fGraph) {
            return true;
        }
        if (b.fGraph < a.fGraph) {
            return false;
        }
        if (std::lexicographical_compare(a.fGroups.begin(), a.fGroups.end(), b.fGroups.begin(), b.fGroups.end(),
                                         GroupLess())) {
            return true;
        }
        if (std::lexicographical_compare(b.fGroups.begin(), b.fGroups.end(), a.fGroups.begin(), a.fGroups.end(),
                                         GroupLess())) {
            return false;
        }
        // the labels : keys through GroupLess, never through std::set's own
        // operator< (element order, address order for pointers), values
        // through the order of L
        GroupLess lt;
        auto      i = a.fLabels.begin();
        auto      j = b.fLabels.begin();
        for (; i != a.fLabels.end() && j != b.fLabels.end(); ++i, ++j) {
            if (lt(i->first, j->first)) {
                return true;
            }
            if (lt(j->first, i->first)) {
                return false;
            }
            if (i->second < j->second) {
                return true;
            }
            if (j->second < i->second) {
                return false;
            }
        }
        return i == a.fLabels.end() && j != b.fLabels.end();
    }
};
