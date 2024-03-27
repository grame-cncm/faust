/*******************************************************************************
********************************************************************************

    digraph : directed graph

    Copyright © 2023 Yann Orlarey. All rights reserved.

 *******************************************************************************
 ******************************************************************************/

#pragma once

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <stack>

//===========================================================
// digraph : a directed graph, a set of nodes f type N and a
// set of connections between these nodes. Connections have an
// associated value, by defaut 0. This value is used in Faust
// to represent the time dependency between computations.
//===========================================================

template <typename N>
class digraph
{
    using TWeights      = std::set<int>;
    using TDestinations = std::map<N, TWeights>;

    static inline const TWeights gEmptyWeights;

    //--------------------------------------------------------------------------
    // Real/internal structure of a graph. A graph is a set of nodes
    // and a set of connections between theses nodes. These connections
    // have integer values attached.
    class internalgraph
    {
       private:
        std::set<N>                fNodes;        // {n1,n2,...}
        std::map<N, TDestinations> fConnections;  // {(ni -{d1,d2,...}-> nj),...}

       public:
#if 0
        internalgraph() { std::cout << "create internalgraph " << this << std::endl; }
        ~internalgraph() { std::cout << "delete internalgraph " << this << std::endl; }
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
        [[nodiscard]] const std::set<N>& nodes() const { return fNodes; }

        // returns the set of nodes of the graph
        [[nodiscard]] const std::map<N, TDestinations>& connections() const { return fConnections; }

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

    std::shared_ptr<internalgraph> fContent = std::make_shared<internalgraph>();

   public:
    //--------------------------------------------------------------------------
    // Methods used to build the graph
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
        for (auto& n : g.nodes()) {
            add(n);
            for (auto& c : g.destinations(n)) {
                add(n, c.first, c.second);
            }
        }
        return *this;
    }

    //--------------------------------------------------------------------------
    // Methods used to visit the graph
    //--------------------------------------------------------------------------

    // returns the set of nodes of the graph
    [[nodiscard]] const std::set<N>& nodes() const { return fContent->nodes(); }

    // returns the set of nodes of the graph
    [[nodiscard]] const std::map<N, TDestinations>& connections() const { return fContent->connections(); }

    // returns the destinations of node n in the graph
    [[nodiscard]] const TDestinations& destinations(const N& n) const { return fContent->destinations(n); }

    // returns the weights of the connections between two nodes
    [[nodiscard]] const TWeights& weights(const N& n1, const N& n2) const { return fContent->weights(n1, n2); }

    //--------------------------------------------------------------------------
    // Methods used to query the graph
    //--------------------------------------------------------------------------

    // true is there is any connection between nodes n1 and n2
    [[nodiscard]] bool areConnected(const N& n1, const N& n2) const { return fContent->areConnected(n1, n2); }

    // true is there is any connection between nodes n1 and n2.
    // The smallest weight is returned in d.
    bool areConnected(const N& n1, const N& n2, int& d) const { return fContent->areConnected(n1, n2, d); }

    //--------------------------------------------------------------------------
    // compare graphs for maps and other containers
    //--------------------------------------------------------------------------

    friend bool operator<(const digraph& p1, const digraph& p2)
    {
        return (p1.nodes() < p2.nodes()) || ((p1.nodes() == p2.nodes()) && (p1.connections() < p2.connections()));
    }

    friend bool operator==(const digraph& p1, const digraph& p2)
    {
        return p1.nodes() == p2.nodes() && p1.connections() == p2.connections();
    }
};
