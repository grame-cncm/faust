/*******************************************************************************
********************************************************************************

    schedule : a schedule is an ordered set of nodes of some directed graph.
    It capture the idea of computing the graph in a certain order that preserves
    the dependecies.

    Created by Yann Orlarey on 17/03/2020.
    Copyright © 2017-2021 Grame. All rights reserved.

 *******************************************************************************
 ******************************************************************************/

#pragma once
#include <cassert>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "digraph.hh"
#include "digraphop.hh"

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
    std::map<N, int> fOrder;     // order of each element (starting at 1, 0 indicates not in schedule)

   public:
    // number of elements in the schedule
    int size() const { return fElements.size(); }

    // the vector of elements (for iterations)
    const std::vector<N>& elements() const { return fElements; }

    // the order of an element in the schedule (starting from 1)
    int order(const N& n) const
    {
        auto it = fOrder.find(n);
        return (it == fOrder.end()) ? 0 : it->second;
    }

    // append a new element to a schedule
    schedule& append(const N& n)
    {
        if (fOrder[n] > 0) {
            std::cerr << "WARNING, already scheduled" << std::endl;
        } else {
            fElements.push_back(n);
            fOrder[n] = fElements.size();
        }
        return *this;
    }

    // append all the elements of a schedule
    schedule& append(const schedule<N>& S)
    {
        for (const N& n : S.elements()) append(n);
        return *this;
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
 * @tparam A the type of arrows of G
 * @param G the graph we want to schedule
 * @return schedule<N> the deep first schedule of G
 */
template <typename N, typename A>
inline schedule<N> dfschedule(const digraph<N, A>& G)
{
    schedule<N> S;
    std::set<N> V;  // set of visited nodes

    // recursive deep first visit (pseudo local function using a lambda)
    std::function<void(const N&)> dfvisit = [&](const N& n) {
        if (V.find(n) == V.end()) {
            V.insert(n);
            for (const auto& p : G.connections(n)) {
                dfvisit(p.first);
            }
            S.append(n);
        }
    };

    for (const auto& n : roots(G)) dfvisit(n);

    return S;
}

/**
 * @brief Breadth-first scheduling of G
 *
 * @tparam N the type of the nodes of G
 * @tparam A the type of arrows of G
 * @param G the graph we want to schedule
 * @return schedule<N> the breadth first schedule of G
 */

template <typename N, typename A>
inline schedule<N> bfschedule(const digraph<N, A>& G)
{
    std::vector<std::vector<N>> P = parallelize(G);
    schedule<N>                 S;

    for (uint64_t i = 0; i < P.size(); i++) {
        for (const N& n : P[i]) S.append(n);
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
 * @tparam A the type of arrows of G
 * @param G
 * @param S
 * @return int
 */
template <typename N, typename A>
inline int schedulingcost(const digraph<N, A>& G, const schedule<N>& S)
{
    int cost = 0;
    for (const N& n : G.nodes()) {
        int t1 = S.order(n);
        for (const auto& c : G.connections(n)) {
            int t0 = S.order(c.first);
            // assert(t1 > t0);
            cost += std::abs(t1 - t0);  // We may have loops
        }
    }
    return cost;
}

/**
 * @brief Deep-first scheduling of a directed graph G with cycles
 *
 * @tparam N the type of nodes of G
 * @tparam A the type of arrows of G
 * @param G the graph we want to schedule
 * @return schedule<N> the deep first schedule of G
 */
template <typename N, typename A>
inline schedule<N> dfcyclesschedule(const digraph<N, A>& G)
{
    digraph<digraph<N, A>, A> H  = graph2dag(G);
    schedule<digraph<N, A>>   SH = dfschedule(H);
    schedule<N>               S;
    for (const digraph<N, A>& n : SH.elements()) {
        S.append(dfschedule(cut(n, 1)));
    }
    return S;
}

/**
 * @brief Breadth-first scheduling of a directed graph G with cycles
 *
 * @tparam N the type of nodes of G
 * @tparam A the type of arrows of G
 * @param G the graph we want to schedule
 * @return schedule<N> the deep first schedule of G
 */
template <typename N, typename A>
inline schedule<N> bfcyclesschedule(const digraph<N, A>& G)
{
    digraph<digraph<N, A>, A> H  = graph2dag(G);
    schedule<digraph<N, A>>   SH = bfschedule(H);
    schedule<N>               S;
    for (const digraph<N, A>& n : SH.elements()) {
        S.append(dfschedule(cut(n, 1)));
    }
    return S;
}
