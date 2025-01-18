/*******************************************************************************
********************************************************************************

    schedule : a schedule is an ordered set of nodes of some directed graph.
    It capture the idea of computing the graph in a certain order that preserves
    the dependecies.

    Created by Yann Orlarey on 17/03/2020.
    Copyright © 2023 Yann Orlarey. All rights reserved.

 *******************************************************************************
 ******************************************************************************/

#pragma once
#include <algorithm>  // for std::find
#include <cassert>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "DirectedGraph.hh"
#include "DirectedGraphAlgorythm.hh"

/**
 * @brief a schedule gives the computation order of the nodes of a DAG.
 * A valid schedule is such if n->m in G, then order(n) > order(m), i.e. n
 * must be computed after m because it depends on it.
 *
 * @tparam N
 */
template <typename N>
class schedule {
   private:
    std::vector<N>   fElements;  // ordered set of elements
    std::map<N, int> fOrder;  // order of each element (starting at 1, 0 indicates not in schedule)

   public:
    // number of elements in the schedule
    [[nodiscard]] size_t size() const { return fElements.size(); }

    // the vector of elements (for iterations)
    [[nodiscard]] const std::vector<N>& elements() const { return fElements; }

    // the order of an element in the schedule (starting from 1)
    [[nodiscard]] int order(const N& n) const
    {
        auto it = fOrder.find(n);
        return (it == fOrder.end()) ? 0 : it->second;
    }

    // append a new element to a schedule
    schedule& append(const N& n)
    {
        if (fOrder[n] > 0) {
            std::cerr << "WARNING, already scheduled" << '\n';
        } else {
            fElements.push_back(n);
            fOrder[n] = int(fElements.size());
        }
        return *this;
    }

    // append all the elements of a schedule
    schedule& append(const schedule<N>& S)
    {
        for (const N& n : S.elements()) {
            append(n);
        }
        return *this;
    }

    // A schedule in reverse order
    schedule reverse() const
    {
        schedule<N> S;
        for (auto it = fElements.rbegin(); it != fElements.rend(); ++it) {
            S.append(*it);
        }
        return S;
    }
};

/**
 * @brief print a schedule
 *
 * @tparam N
 * @param file
 * @param S the schedule
 * @return std::ostream& the output stream
 */
template <typename N>
inline std::ostream& operator<<(std::ostream& file, const schedule<N>& S)
{
    std::string sep = "";

    file << "Schedule {";
    for (const N& n : S.elements()) {
        file << sep << S.order(n) << ":" << n;
        sep = ", ";
    }
    return file << "}";
}

/**
 * @brief Deep-first scheduling of a DAG G
 *
 * @tparam N the type of nodes of G
 * @param G the graph we want to schedule
 * @return schedule<N> the deep first schedule of G
 */
template <typename N>
inline schedule<N> dfschedule(const digraph<N>& G)
{
    schedule<N> S;
    std::set<N> V;  // set of visited nodes

    // recursive deep first visit (pseudo local function using a lambda)
    std::function<void(const N&)> dfvisit = [&](const N& n) {
        if (V.find(n) == V.end()) {
            V.insert(n);
            for (const auto& p : G.destinations(n)) {
                dfvisit(p.first);
            }
            S.append(n);
        }
    };

    for (const auto& n : roots(G)) {
        dfvisit(n);
    }

    return S;
}

/**
 * @brief Breadth-first scheduling of G
 *
 * @tparam N the type of the nodes of G
 * @param G the graph we want to schedule
 * @return schedule<N> the breadth first schedule of G
 */

template <typename N>
inline schedule<N> bfschedule(const digraph<N>& G)
{
    std::vector<std::vector<N>> P = parallelize(G);
    schedule<N>                 S;

    for (uint64_t i = 0; i < P.size(); i++) {
        for (const N& n : P[i]) {
            S.append(n);
        }
    }
    return S;
}

/**
 * @brief special schedule for a DAG
 *
 * @tparam N
 * @param G
 * @return schedule<N>
 */
template <typename N>
inline schedule<N> spschedule(const digraph<N>& G)
{
    std::set<N> V;  // already scheduled nodes
    schedule<N> S;  // the final schedule

    std::list<N> L = recschedule(G);  // schedule list with duplicated
    for (auto it = L.rbegin(); it != L.rend(); ++it) {
        if (!V.contains(*it)) {
            S.append(*it);
            V.insert(*it);
        }
    }
    return S;
}

/**
 * @brief The 'cost' of a scheduling. The scheduling time distance
 * between the nodes and its dependencies. This should be an indication
 * of how hot the cache is kept by this scheduling. The less the cost
 * is the better it is.
 *
 * @tparam N
 * @param G
 * @param S
 * @return int
 */
template <typename N>
inline unsigned int schedulingcost(const digraph<N>& G, const schedule<N>& S)
{
    unsigned int cost = 0;
    for (const N& n : G.nodes()) {
        unsigned int t1 = S.order(n);
        for (const auto& c : G.destinations(n)) {
            unsigned int t0 = S.order(c.first);
            // assert(t1 > t0);
            cost += (t1 - t0) * (t1 - t0);  // We may have loops
        }
    }
    return cost;
}

/**
 * @brief Deep-first scheduling of a directed graph G with cycles
 *
 * @tparam N the type of nodes of G
 * @param G the graph we want to schedule
 * @return schedule<N> the deep first schedule of G
 */
template <typename N>
inline schedule<N> dfcyclesschedule(const digraph<N>& G)
{
    digraph<digraph<N>>  H  = graph2dag(G);
    schedule<digraph<N>> SH = dfschedule(H);
    schedule<N>          S;
    for (const digraph<N>& n : SH.elements()) {
        S.append(dfschedule(cut(n, 1)));
    }
    return S;
}

/**
 * @brief Breadth-first scheduling of a directed graph G with cycles
 *
 * @tparam N the type of nodes of G
 * @param G the graph we want to schedule
 * @return schedule<N> the deep first schedule of G
 */
template <typename N>
inline schedule<N> bfcyclesschedule(const digraph<N>& G)
{
    digraph<digraph<N>>  H  = graph2dag(G);
    schedule<digraph<N>> SH = bfschedule(H);
    schedule<N>          S;
    for (const digraph<N>& n : SH.elements()) {
        S.append(dfschedule(cut(n, 1)));
    }
    return S;
}

/**
 * @brief reverse breadth first schedule for a DAG
 *
 * @tparam N
 * @param G
 * @return schedule<N>
 */
template <typename N>
inline schedule<N> rbschedule(const digraph<N>& G)
{
    std::vector<std::vector<N>> P = parallelize(reverse(G));
    schedule<N>                 S;

    for (uint64_t i = 0; i < P.size(); i++) {
        for (const N& n : P[i]) {
            S.append(n);
        }
    }
    return S.reverse();
}
