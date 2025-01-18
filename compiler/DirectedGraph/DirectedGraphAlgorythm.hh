/*******************************************************************************
********************************************************************************

    digraphop : a set of operations on directed graphs

    Created by Yann Orlarey on 31/01/2022.
    Copyright © 2023 Yann Orlarey. All rights reserved.

 *******************************************************************************
 ******************************************************************************/

#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

#include "DirectedGraph.hh"
#include "Schedule.hh"

//===========================================================
//===========================================================
// Partitions a graph into strongly connected components
// USAGE : Tarjan<N> t(mygraph); ...t.partition()...
//===========================================================
//===========================================================

template <typename N>
class Tarjan {
    // Additional information associated to each node
    // during the visit
    struct tarjanAux {
        bool fVisited = false;
        bool fStacked = false;
        int  fNum1    = 0;
        int  fNum2    = 0;
    };

    const digraph<N>       fGraph;
    int                    fGroup = 0;
    std::stack<N>          fStack;
    std::map<N, tarjanAux> fAux;
    std::set<std::set<N>>  fPartition;
    int                    fCycleCount = 0;

    // visit a specific node n of the graph
    void visit(const N& v)
    {
        // std::cout << "start (first) visit of " << v << '\n';
        auto& x = fAux[v];
        fStack.push(v);
        x.fStacked = true;
        x.fVisited = true;
        x.fNum1 = x.fNum2 = fGroup;
        ++fGroup;

        // std::cout << "visit all nodes connected to " << v << '\n';
        for (const auto& p : fGraph.destinations(v)) {
            // std::cout << "we have a connection " << v << "-" << p.second << "->" << p.first <<
            // '\n';
            const N& w = p.first;
            auto&    y = fAux[w];
            if (!y.fVisited) {
                visit(w);
                x.fNum2 = std::min(x.fNum2, y.fNum2);
            } else {
                if (y.fStacked) {
                    // std::cout << "the node " << w << " is already in the std::stack" <<
                    // '\n';
                    x.fNum2 = std::min(x.fNum2, y.fNum1);
                }
            }
        }

        if (x.fNum1 == x.fNum2) {
            // std::cout << "the node " << v << " is the root of a cycle" << '\n';

            std::set<N> cycle;
            bool        finished = false;
            do {
                const N& w = fStack.top();
                fStack.pop();
                fAux[w].fStacked = false;
                cycle.insert(w);
                finished = (w == v);
            } while (!finished);
            fPartition.insert(cycle);
            if ((cycle.size() > 1) || fGraph.areConnected(v, v)) {
                fCycleCount++;
            }
        }
        // std::cout << "end (first) visit of " << v << '\n';
    }

   public:
    explicit Tarjan(const digraph<N>& g) : fGraph(g)
    {
        for (const auto& n : fGraph.nodes()) {
            if (!fAux.contains(n)) {
                visit(n);
            }
        }
    }

    [[nodiscard]] const std::set<std::set<N>>& partition() const { return fPartition; }

    [[nodiscard]] int cycles() const { return fCycleCount; }
};

//===========================================================
//===========================================================
// cycles:graph->int : counts the number of cycles
// (strongly connected components) of a graph
//===========================================================
//===========================================================

template <typename N>
inline int cycles(const digraph<N>& g)
{
    Tarjan<N> T(g);
    return T.cycles();
}

//===========================================================
//===========================================================
// graph2dag : transfoms a graph into a dag of supernodes,
// ie strongly connected components. The connection value
// between two supernodes A and B is the smallest value of all
// the destinations between nodes of A and nodes of B.
//===========================================================
//===========================================================

template <typename N>
inline digraph<digraph<N>> graph2dag(const digraph<N>& g)
{
    Tarjan<N>               T(g);  // the partition of g
    std::map<N, digraph<N>> M;     // std::mapping between nodes and supernodes
    digraph<digraph<N>>     sg;    // the resulting supergraph

    // build the graph of supernodes

    // For each std::set s of the partition, create the corresponding graph sn
    // create also a std::mapping in order to retrieve the supernode a node
    /// belongs to.
    for (const auto& s : T.partition()) {
        digraph<N> sn;                        // the supernode graph
        for (const N& n : s) {                // for each node of a cycle
            M.insert(std::make_pair(n, sn));  // remember its supernode
            sn.add(n);                        // and add it to the super node
        }
        sg.add(sn);  // and add the super node to the super graph
    }

    // compute the destinations between the supernodes
    for (const auto& n1 : g.nodes()) {
        digraph<N> sn1(M[n1]);
        for (const auto& c : g.destinations(n1)) {
            const N&    n2  = c.first;
            const auto& W12 = c.second;
            digraph<N>  sn2(M[n2]);
            if (sn1 == sn2) {
                // the connection is inside the same supernode
                sn1.add(n1, n2, W12);
            } else {
                // the connection is between supernodes
                sg.add(sn1, sn2, W12);  // exploit the fact that add will keep the mini
            }
        }
    }

    return sg;
}

//===========================================================
//===========================================================
// graph2dag2 : transfoms a graph into a dag of supernodes,
// ie strongly connected components. The connection value
// between two supernodes A and B is the number of existing
// destinations between nodes of A and nodes of B.
//===========================================================
//===========================================================

template <typename N>
inline digraph<digraph<N>> graph2dag2(const digraph<N>& g)
{
    Tarjan<N>               T(g);  // the partition of g
    std::map<N, digraph<N>> M;     // std::mapping between nodes and supernodes
    digraph<digraph<N>>     sg;    // the resulting supergraph
    std::map<std::pair<digraph<N>, digraph<N>>, int>
        CC;  // count of destinations between supernodes

    // build the graph of supernodes

    // for each std::set s of the partition, create the corresponding graph sn
    // create also a std::mapping in order to retrieve the supernode a node
    /// belongs to.
    for (const auto& s : T.partition()) {
        digraph<N> sn;                        // the supernode graph
        for (const N& n : s) {                // for each node of a cycle
            M.insert(std::make_pair(n, sn));  // remember its supernode
            sn.add(n);                        // and add it to the super node
        }
        sg.add(sn);  // and add the super node to the super graph
    }

    // compute the number of destinations between the supernodes
    for (const auto& n1 : g.nodes()) {              // for each node n1
        digraph<N> sn1(M[n1]);                      // retrieve the supernode
        for (const auto& c : g.destinations(n1)) {  // for each destination of n
            digraph<N> sn2(M[c.first]);
            if (sn1 == sn2) {
                // the connection is inside the same supernode
                sn1.add(n1, c.first, c.second);
            } else {
                // We count the external destinations between two supernodes
                CC[std::make_pair(sn1, sn2)] += 1;
            }
        }
    }

    // we connect the super nodes using the count of external destinations
    for (const auto& entry : CC) {
        sg.add(entry.first.first, entry.first.second, entry.second);
    }

    return sg;
}

//===========================================================
//===========================================================
//
// parallelize : transfoms a DAG into a sequential std::vector
// of parallel vectors of nodes using a topological sort.
//
//===========================================================
//===========================================================

template <typename N>
inline std::vector<std::vector<N>> parallelize(const digraph<N>& g)
{
    //-----------------------------------------------------------
    // Find the level of a node n -> {m1,m2,...} such that
    //		level(n -> {})			= 0
    //		level(n -> {m1,m2,...})	= 1 + std::max(level(mi))
    //-----------------------------------------------------------
    using Levelfun = std::function<int(const N&, std::map<N, int>&)>;

    Levelfun level = [&g, &level](const N& n1, std::map<N, int>& levelcache) -> int {
        auto p = levelcache.find(n1);
        if (p != levelcache.end()) {
            return p->second;
        } else {
            int l = -1;
            for (const auto& e : g.destinations(n1)) {
                l = std::max(l, level(e.first, levelcache));
            }
            return levelcache[n1] = l + 1;
        }
    };

    std::map<N, int> levelcache;
    // compute the level of each node in the graph
    int l = -1;
    for (const N& n : g.nodes()) {
        l = std::max(l, level(n, levelcache));
    }
    // create a graph for each level and place
    // each node in the appropriate level
    std::vector<std::vector<N>> v;
    v.resize(l + 1);
    for (const N& n : g.nodes()) {
        v[levelcache[n]].push_back(n);
    }

    return v;
}

template <typename N>
inline std::vector<std::vector<N>> rparallelize(const digraph<N>& G)
{
    std::vector<std::vector<N>> P = parallelize(G);
    int                         i = 0;
    int                         j = int(P.size()) - 1;

    while (i < j) {
        swap(P[i], P[j]);
        ++i;
        --j;
    }

    return P;
}

//===========================================================
//===========================================================
// serialize : transfoms a DAG into a sequence of nodes
// using a topological sort.
//===========================================================
//===========================================================

template <typename N>
inline std::vector<N> serialize(const digraph<N>& G)
{
    //------------------------------------------------------------------------
    // visit : a local std::function (simulated using a lambda) to visit a graph
    // g : the graph
    // n : the node
    // V : std::set of already visited nodes
    // S : serialized std::vector of nodes
    //------------------------------------------------------------------------
    using Visitfun =
        std::function<void(const digraph<N>&, const N&, std::set<N>&, std::vector<N>&)>;
    Visitfun visit = [&visit](const digraph<N>& g, const N& n, std::set<N>& V, std::vector<N>& S) {
        if (!V.contains(n)) {
            V.insert(n);
            for (const auto& p : g.destinations(n)) {
                visit(g, p.first, V, S);
            }
            S.push_back(n);
        }
    };

    std::vector<N> S;
    std::set<N>    V;
    for (const N& n : G.nodes()) {
        visit(G, n, V, S);
    }
    return S;
}

//===========================================================
//===========================================================
// std::mapgraph(foo) : transfoms a graph  by applying foo:N->M
// to each node of graph. The destinations are preserved.
//===========================================================
//===========================================================

template <typename N, typename M>
inline digraph<M> mapnodes(const digraph<N>& g, std::function<M(const N&)> foo)
{
    digraph<M>     r;
    std::map<N, M> cache;
    // create a new graph with the transformed nodes
    for (const auto& n1 : g.nodes()) {
        M n2 = foo(n1);
        r.add(n2);
        cache.insert(std::make_pair(n1, n2));
    }

    // copy the destinations
    for (const auto& n : g.nodes()) {
        for (const auto& cnx : g.destinations(n)) {
            r.add(cache[n], cache[cnx.first], cnx.second);
        }
    }
    return r;
}

//===========================================================
//===========================================================
// reverse(g) : reverse all the destinations of a graph. The
// destinations keep their value.
// Property : reverse(reverse(g)) = g;
//===========================================================
//===========================================================

template <typename N>
inline digraph<N> reverse(const digraph<N>& g)
{
    digraph<N> r;
    // copy the destinations
    for (const auto& n : g.nodes()) {
        r.add(n);
        for (const auto& cnx : g.destinations(n)) {
            r.add(cnx.first, n, cnx.second);
        }
    }
    return r;
}

#if 0
//===========================================================
//===========================================================
// mapconnections(g, keep) -> g' : transfoms a graph by
// applying the std::function keep to each connection. If keep
// returns true the connection is maintained, otherwise it
// is removed.
//===========================================================
//===========================================================

template <typename N>
inline digraph<N> mapconnections(const digraph<N>&                                             G,
                                 std::function<bool(const N&, const N&, const std::set<int>&)> keep)
{
    digraph<N> R;
    for (const N& n : G.nodes()) {
        R.add(n);
        for (const auto& c : G.destinations(n)) {
            if (keep(n, c.first, c.second)) {
                R.add(n, c.first, c.second);
            }
        }
    }
    return R;
}
#endif

//===========================================================
//===========================================================
// splitgraph(G, left, L, R)
//===========================================================
//===========================================================

/**
 * @brief split a graph into two subgraphs L and R according to a predicate.
 *
 * @tparam N the type of nodes
 * @param G the input graph
 * @param left a node predicate, when true the node goes to L, otherwise to R
 * @param L resulting graph of left nodes
 * @param R resulting graph of right nodes
 */
template <typename N>
void splitgraph(const digraph<N>& G, std::function<bool(const N&)> left, digraph<N>& L,
                digraph<N>& R)
{
    for (auto n : G.nodes()) {
        if (left(n)) {
            L.add(n);
            for (const auto& c : G.destinations(n)) {
                if (left(c.first)) {
                    L.add(n, c.first, c.second);
                }
            }
        } else {
            R.add(n);
            for (const auto& c : G.destinations(n)) {
                if (!left(c.first)) {
                    R.add(n, c.first, c.second);
                }
            }
        }
    }
}

//===========================================================
//===========================================================
// subgraph(G, S)
//===========================================================
//===========================================================

/**
 * @brief extract a subgraph of G according to a std::set of nodes S.
 *
 * @tparam N the type of nodes
 * @param G the input graph
 * @param S the set of nodes to keep with their dependencies
 * @return the resulting subgraph
 */
template <typename N>
digraph<N> subgraph(const digraph<N>& G, const std::set<N>& S)
{
    digraph<N>  R;     // the (R)esulting graph
    std::set<N> W{S};  // nodes (W)aiting to be processed
    std::set<N> P;     // nodes already (P)rocessed
    while (!W.empty()) {
        std::set<N> M;  // (M)ore nodes to process at next iteration
        for (auto n : W) {
            R.add(n);     // add n to the resulting graph
            P.insert(n);  // mark n as processed
            for (const auto& a : G.destinations(n)) {
                R.add(n, a.first, a.second);  // add its adjacent nodes
                if (!P.contains(a.first)) {   // is it new ?
                    M.insert(a.first);        // we will have to process it
                }
            }
        }
        W = M;
    }
    return R;
}

//===========================================================
//===========================================================
// cut(g,d) -> g'
// cuts all the destinations of graph g of weight >= d
//===========================================================
//===========================================================

template <typename N>
inline digraph<N> cut(const digraph<N>& G, int dm)
{
    digraph<N> R;
    for (const auto& n1 : G.nodes()) {
        R.add(n1);
        for (const auto& c : G.destinations(n1)) {
            const auto& n2 = c.first;
            R.add(n2);
            // remove the connections with weight >= dm
            const auto&   wg = c.second;
            std::set<int> wr;
            for (int d : wg) {
                if (d < dm) {
                    wr.insert(d);
                }
            }
            if (!wr.empty()) {
                R.add(n1, n2, wr);
            }
        }
    }
    return R;
}

//===========================================================
//===========================================================
// chain(g) -> g'
// Keep only the chain destinations, that is destinations
// (n1 -d-> n2) such that dst(n1) == {n2} && src(n2) == {n1}
// If strict is true, only the node part of a chain are kept.
//===========================================================
//===========================================================

template <typename N>
inline digraph<N> chain(const digraph<N>& g, bool strict)
{
    const digraph<N> h = reverse(g);
    digraph<N>       r;
    for (const auto& n : g.nodes()) {
        if (!strict) {
            r.add(n);
        }
        if (g.destinations(n).size() == 1) {
            for (const auto& m : g.destinations(n)) {
                if (h.destinations(m.first).size() == 1) {
                    r.add(n, m.first, m.second);
                }
            }
        }
    }
    return r;
}

template <typename N>
inline std::vector<N> roots(const digraph<N>& G)
{
    std::map<N, int> R;
    for (const N& n : G.nodes()) {
        for (const auto& c : G.destinations(n)) {
            R[c.first]++;
        }
    }
    std::vector<N> V;
    for (const N& n : G.nodes()) {
        if (R[n] == 0) {
            V.push_back(n);
        }
    }
    return V;
}

template <typename N>
inline std::vector<N> leaves(const digraph<N>& G)
{
    std::vector<N> L;
    for (const N& n : G.nodes()) {
        if (G.destinations(n).size() == 0) {
            L.push_back(n);
        }
    }
    return L;
}

/**
 * @brief compute the critical path of a graph
 *
 * @param G
 * @return std::vector<N>
 */
template <typename N>
inline std::vector<N> criticalpath(const digraph<N>& G, const N& n)
{
    std::vector<N> P;
    for (const auto& c : G.destinations(n)) {
        std::vector<N> Q = criticalpath(G, c.first);
        if (Q.size() > P.size()) {
            P = Q;
        }
    }
    P.push_back(n);
    return P;
}

/**
 * @brief interleave two lists
 *
 * @param list1: (A,B,C,...)
 * @param list2: (U,W)
 * @return (A,U,B,W,C,...)
 */
template <typename N>
static std::list<N> interleave(std::list<N>& list1, std::list<N>& list2)
{
    std::list<N> result;

    // Iterators for both lists
    auto it1 = list1.begin();
    auto it2 = list2.begin();

    // Traverse both lists
    while (it1 != list1.end() && it2 != list2.end()) {
        result.push_back(*it1);
        result.push_back(*it2);
        ++it1;
        ++it2;
    }

    // Append remaining elements of list1
    while (it1 != list1.end()) {
        result.push_back(*it1);
        ++it1;
    }

    // Append remaining elements of list2
    while (it2 != list2.end()) {
        result.push_back(*it2);
        ++it2;
    }

    return result;
}

/**
 * @brief recursive scheduling of a node of a DAG
 *
 * @tparam N
 * @param G a DAG
 * @param n a node of G
 * @return std::list<N> scheduling with duplicates
 */
template <typename N>
inline std::list<N> recschedulenode(const digraph<N>& G, const N& n)
{
    std::list<N> P;
    for (const auto& c : G.destinations(n)) {
        std::list<N> Q = recschedulenode(G, c.first);
        P              = interleave(P, Q);
    }
    P.push_front(n);
    return P;
}

/**
 * @brief recursive scheduling of the roots of a DAG
 *
 * @tparam N
 * @param G a DAG
 * @return std::list<N> scheduling with duplicates
 */
template <typename N>
inline std::list<N> recschedule(const digraph<N>& G)
{
    std::list<N> P;
    for (const N& n : roots(G)) {
        std::list<N> Q = recschedulenode(G, n);
        P              = interleave(P, Q);
    }
    return P;
}


/*******************************************************************************
********************************************************************************

                                        VARIOUS PRINTING std::functionS

 *******************************************************************************
 ******************************************************************************/

//===========================================================
//===========================================================
// file << std::list : print a std::list on a stream
//===========================================================
//===========================================================

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const std::list<N>& L)
{
    std::string sep = "";

    file << "std::list{";
    for (const N& e : L) {
        file << sep << e;
        sep = ", ";
    }
    return file << "}";
}

//===========================================================
//===========================================================
// file << std::vector : print a std::vector on a stream
//===========================================================
//===========================================================

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const std::vector<N>& V)
{
    std::string sep = "";

    file << "std::vector{";
    for (const N& e : V) {
        file << sep << e;
        sep = ", ";
    }
    return file << "}";
}

//===========================================================
//===========================================================
// file << std::set : print a std::set on a stream
//===========================================================
//===========================================================

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const std::set<N>& S)
{
    std::string sep = "";

    file << "set{";
    for (const N& e : S) {
        file << sep << e;
        sep = ", ";
    }
    return file << "}";
}

//===========================================================
//===========================================================
// file << std::pair : print a std::pair on a stream
//===========================================================
//===========================================================

template <typename N, typename M>
inline std::ostream& operator<<(std::ostream& file, const std::pair<N, M>& V)
{
    return file << "std::pair{" << V.first << ", " << V.second << "}";
}

//===========================================================
//===========================================================
// dotfile(file, graph) print graph on a stream in .dot format
//===========================================================
//===========================================================

template <typename N>
inline std::ostream& dotfile(std::ostream& file, const digraph<N>& g, bool clusters = false)
{
    file << "digraph mygraph {" << '\n';
    for (const N& n : g.nodes()) {
        std::stringstream sn;
        sn << '"' << n << '"';
        bool hascnx = false;
        for (const auto& c : g.destinations(n)) {
            std::stringstream sm;
            sm << '"' << c.first << '"';
            hascnx = true;
            file << "\t" << sn.str() << "->" << sm.str() << " [label=\"" << c.second << "\"];"
                 << '\n';
        }
        if (!hascnx) {
            file << "\t" << sn.str() << ";" << '\n';
        }
    }

    if (clusters) {
        Tarjan<N> T(g);
        int       ccount = 0;  // cluster count
        for (const auto& s : T.partition()) {
            file << "\t"
                 << "subgraph cluster" << ccount << " { " << '\n';
            for (const N& n : s) {
                file << "\t\t" << '"' << n << '"' << ";" << '\n';
            }
            file << "\t"
                 << "}" << '\n';
            ccount++;
        }
    }

    return file << "}" << '\n';
}

//===========================================================
//===========================================================
// file << graph : print graph on a stream
//===========================================================
//===========================================================

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const digraph<N>& g)
{
    std::string sep = "";

    file << "Graph {";
    for (const N& n : g.nodes()) {
        bool hascnx = false;
        for (const auto& c : g.destinations(n)) {
            hascnx = true;
            file << sep << n << '-' << c.second << "->" << (c.first);
            sep = ", ";
        }
        if (!hascnx) {
            file << sep << n;
        }
        sep = ", ";
    }

    return file << "}";
}

//===========================================================
//===========================================================
//
// topology : high level description of a graph as a vector
// of intergers.
//
//===========================================================
//===========================================================

/**
 * @brief topology : high level description of a graph.
 * Returns a vector of int describing the graph g:
 * n: total number of nodes
 * a: total number of arrows
 * c: total number of cycles
 * 0: number of nodes of level 0 (with no dependencies)
 * 1: number of nodes of level 1 (with only dependecies at level 0)
 * ...
 *
 * @tparam N type of nodes
 * @param g graph we want to analyze
 * @return std::vector<int> [n, a, c, l0, l1, ...]
 */
template <typename N>
inline std::vector<int> topology(const digraph<N>& g)
{
    std::vector<int> v;
    int              n = 0;
    int              a = 0;
    for (const N& x : g.nodes()) {
        n++;
        a += g.destinations(x).size();  // count multi arrows for 1
    }
    v.push_back(n);  // number of nodes
    v.push_back(a);  // number of arrows
    int c = cycles(g);
    v.push_back(c);
    if (c > 0) {
        // we have cycles, compute a dag d first
        auto d = graph2dag(g);
        for (const auto& l : parallelize(d)) {
            v.push_back((int)l.size());
        }
    } else {
        for (const auto& l : parallelize(g)) {
            v.push_back((int)l.size());
        }
    }
    return v;
}
