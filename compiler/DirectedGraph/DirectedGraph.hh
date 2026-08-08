/*
 * Copyright (c) 2023-2026, Yann Orlarey
 * SPDX-License-Identifier: Apache-2.0
 */

/*******************************************************************************
    DirectedGraph.hh

    A directed graph class
 ******************************************************************************/

#pragma once

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <stack>

/**
 * @brief A shared, mutable handle to a directed graph whose nodes have type N.
 *
 * Connections carry integer weights, defaulting to 0, which Faust uses to
 * represent time dependencies between computations.
 *
 * Copy construction and copy assignment intentionally share the underlying
 * graph instead of duplicating it. Mutating any copy therefore changes the
 * graph observed through every alias, while copying a handle remains cheap.
 *
 * Concurrent mutation through aliases requires external synchronization. A
 * digraph used as a key in an ordered container must not be mutated through
 * any alias while stored there because its ordering depends on its contents.
 */
// Deterministic-order customization point : every internal container of the
// graph -- and of the algorithms operating on it -- orders nodes with
// dgorder<N>. The default is std::less<N>. A client whose N is a POINTER
// type should specialize dgorder to a value- or serial-derived order :
// with the default, every iteration -- and therefore every schedule
// tie-break -- follows allocation addresses (ASLR), and compilation loses
// run-to-run determinism. (tlib specializes dgorder<Tree> to the serial
// order treeorder, in tree.hh.)
template <typename N>
struct dgorder : std::less<N> {};

template <typename N>
class digraph {
    using TWeights      = std::set<int>;
    using TDestinations = std::map<N, TWeights, dgorder<N>>;

    static inline const TWeights gEmptyWeights;

    //--------------------------------------------------------------------------
    // Real/internal structure of a graph. A graph is a set of nodes
    // and a set of connections between theses nodes. These connections
    // have integer values attached.
    class internalgraph {
       private:
        std::set<N, dgorder<N>>                fNodes;        // {n1,n2,...}
        std::map<N, TDestinations, dgorder<N>> fConnections;  // {(ni -{d1,d2,...}-> nj),...}

       public:
#if 0
        internalgraph() { std::cout << "create internalgraph " << this << '\n'; }
        ~internalgraph() { std::cout << "delete internalgraph " << this << '\n'; }
#endif
        //----------------------------------------------------------------------
        // Methods used to build the graph
        //----------------------------------------------------------------------

        // Add a node n to the graph
        void add(N n)
        {
            fNodes.insert(n);
            (void)fConnections[n];  // make sure we have an empty set of connections for n
        }

        // add two nodes with a set of connections of weights w
        void add(const N& n1, const N& n2, const TWeights& w)
        {
            add(n1);
            add(n2);
            fConnections[n1][n2].insert(w.begin(), w.end());
        }

        //----------------------------------------------------------------------
        // Methods used to query the graph
        //----------------------------------------------------------------------

        // returns the set of nodes of the graph
        [[nodiscard]] const std::set<N, dgorder<N>>& nodes() const { return fNodes; }

        // returns the set of nodes of the graph
        [[nodiscard]] const std::map<N, TDestinations, dgorder<N>>& connections() const
        {
            return fConnections;
        }

        // Returns the destinations of node n in the graph
        [[nodiscard]] const TDestinations& destinations(const N& n) const
        {
            assert(fNodes.find(n) != fNodes.end());
            return fConnections.at(n);
        }

        // Returns true is n1 and n2 are connected in the graph
        [[nodiscard]] bool areConnected(const N& n1, const N& n2) const
        {
            // check we test connexions between existing nodes
            assert(fNodes.find(n1) != fNodes.end());
            assert(fNodes.find(n2) != fNodes.end());
            auto cnx1 = fConnections.find(n1);
            if (cnx1 == fConnections.end()) {
                // n1 has no connection
                return false;
            } else {
                auto cnx2 = cnx1->second.find(n2);
                if (cnx2 == cnx1->second.end()) {
                    // n1 has connections, but not to n2
                    return false;
                } else {
                    // its seems we have connections between n1 and n2,
                    // but we need to check
                    const std::set<int>& w12 = cnx2->second;
                    return !w12.empty();
                }
            }
        }

        // Returns the destinations of node n in the graph
        [[nodiscard]] bool areConnected(const N& n1, const N& n2, int& d) const
        {
            // check we test connexions between existing nodes
            assert(fNodes.find(n1) != fNodes.end());
            assert(fNodes.find(n2) != fNodes.end());
            auto cnx1 = fConnections.find(n1);
            if (cnx1 == fConnections.end()) {
                // n1 has no connection
                return false;
            } else {
                auto cnx2 = cnx1->second.find(n2);
                if (cnx2 == cnx1->second.end()) {
                    // n1 has connections, but not to n2
                    return false;
                } else {
                    // its seems we have connections between n1 and n2,
                    // but we need to check
                    const std::set<int>& w12 = cnx2->second;
                    if (!w12.empty()) {
                        d = *w12.begin();
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }

        // Returns the weights of the connections between two nodes
        [[nodiscard]] const TWeights& weights(const N& n1, const N& n2) const
        {
            // check we test connexions between existing nodes
            assert(fNodes.find(n1) != fNodes.end());
            assert(fNodes.find(n2) != fNodes.end());
            auto cnx1 = fConnections.find(n1);
            if (cnx1 == fConnections.end()) {
                // n1 has no connection
                return gEmptyWeights;
            } else {
                auto cnx2 = cnx1->second.find(n2);
                if (cnx2 == cnx1->second.end()) {
                    // n1 has connections, but not to n2
                    return gEmptyWeights;
                } else {
                    // its seems we have connections between n1 and n2,
                    // but we need to check
                    const std::set<int>& w12 = cnx2->second;
                    return w12;
                }
            }
        }
    };

    // Shared ownership provides intentional reference semantics: all copied
    // digraph handles observe and mutate this same internal graph.
    std::shared_ptr<internalgraph> fContent = std::make_shared<internalgraph>();

   public:
    //--------------------------------------------------------------------------
    // Public API: graph construction and inspection
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    // Mutating operations; their effects are visible through every copied handle
    //--------------------------------------------------------------------------

    // Add the node n to the graph
    digraph& add(N n)
    {
        fContent->add(n);
        return *this;
    }

    // add two nodes with a set of connections of weights w
    digraph& add(const N& n1, const N& n2, const TWeights& w)
    {
        fContent->add(n1, n2, w);
        return *this;
    }

    // Add the nodes n1 and n2 and the connection (n1 -d-> n2) to the graph.
    digraph& add(const N& n1, const N& n2, int d = 0)
    {
        fContent->add(n1, n2, {d});
        return *this;
    }

    // add a whole graph g
    digraph& add(const digraph& g)
    {
        for (const auto& n : g.nodes()) {
            add(n);
        }

        for (const auto& n : g.nodes()) {
            for (const auto& c : g.destinations(n)) {
                add(n, c.first, c.second);
            }
        }
        return *this;
    }

    //--------------------------------------------------------------------------
    // Methods used to visit the graph
    //--------------------------------------------------------------------------

    // These four return a REFERENCE into the graph's content. Calling them on a temporary
    // would leave that reference dangling as soon as the temporary dies (the content is
    // shared by reference count, so it survives only if another digraph still holds it --
    // which cannot be known statically). The deleted rvalue overloads therefore reject
    // 'f(...).nodes()' at COMPILE TIME : bind the graph to a named variable first.

    // returns the set of nodes of the graph
    [[nodiscard]] const auto& nodes() const& { return fContent->nodes(); }
    const std::set<N>&               nodes() const&& = delete;

    // returns the set of nodes of the graph
    [[nodiscard]] const auto& connections() const& { return fContent->connections(); }
    const auto&               connections() const&& = delete;

    // returns the destinations of node n in the graph
    [[nodiscard]] const TDestinations& destinations(const N& n) const&
    {
        return fContent->destinations(n);
    }
    const TDestinations& destinations(const N& n) const&& = delete;

    // returns the weights of the connections between two nodes
    [[nodiscard]] const TWeights& weights(const N& n1, const N& n2) const&
    {
        return fContent->weights(n1, n2);
    }
    const TWeights& weights(const N& n1, const N& n2) const&& = delete;

    //--------------------------------------------------------------------------
    // Methods used to query the graph
    //--------------------------------------------------------------------------

    // true is there is any connection between nodes n1 and n2
    [[nodiscard]] bool areConnected(const N& n1, const N& n2) const
    {
        return fContent->areConnected(n1, n2);
    }

    // true is there is any connection between nodes n1 and n2.
    // The smallest weight is returned in d.
    bool areConnected(const N& n1, const N& n2, int& d) const
    {
        return fContent->areConnected(n1, n2, d);
    }

    //--------------------------------------------------------------------------
    // compare graphs for maps and other containers
    //--------------------------------------------------------------------------

    // Three-way lexicographic through dgorder<N> : std::set's own operator<
    // compares ELEMENTS with their operator< (address order for pointers),
    // never with the set's comparator -- spelling the trait out is the point.
    static int cmpNodes(const digraph& p1, const digraph& p2)
    {
        dgorder<N> lt;
        auto       a = p1.nodes().begin();
        auto       b = p2.nodes().begin();
        for (; a != p1.nodes().end() && b != p2.nodes().end(); ++a, ++b) {
            if (lt(*a, *b)) {
                return -1;
            }
            if (lt(*b, *a)) {
                return 1;
            }
        }
        if (a != p1.nodes().end()) {
            return 1;
        }
        if (b != p2.nodes().end()) {
            return -1;
        }
        return 0;
    }
    static int cmpConnections(const digraph& p1, const digraph& p2)
    {
        dgorder<N> lt;
        const auto& ca = p1.connections();
        const auto& cb = p2.connections();
        auto        a  = ca.begin();
        auto        b  = cb.begin();
        for (; a != ca.end() && b != cb.end(); ++a, ++b) {
            if (lt(a->first, b->first)) {
                return -1;
            }
            if (lt(b->first, a->first)) {
                return 1;
            }
            auto da = a->second.begin();
            auto db = b->second.begin();
            for (; da != a->second.end() && db != b->second.end(); ++da, ++db) {
                if (lt(da->first, db->first)) {
                    return -1;
                }
                if (lt(db->first, da->first)) {
                    return 1;
                }
                if (da->second != db->second) {
                    return (da->second < db->second) ? -1 : 1;  // weight sets : ints
                }
            }
            if (da != a->second.end()) {
                return 1;
            }
            if (db != b->second.end()) {
                return -1;
            }
        }
        if (a != ca.end()) {
            return 1;
        }
        if (b != cb.end()) {
            return -1;
        }
        return 0;
    }
    friend bool operator<(const digraph& p1, const digraph& p2)
    {
        int c = cmpNodes(p1, p2);
        return (c != 0) ? (c < 0) : (cmpConnections(p1, p2) < 0);
    }

    friend bool operator==(const digraph& p1, const digraph& p2)
    {
        return p1.nodes() == p2.nodes() && p1.connections() == p2.connections();
    }
};
