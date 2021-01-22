/*******************************************************************************
********************************************************************************

    digraphop : a set of operations on directed graphs

    Created by Yann Orlarey on 31/01/2017.
    Copyright © 2017 Grame. All rights reserved.

 *******************************************************************************
 ******************************************************************************/

#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <utility>
#include <vector>

#include "digraph.hh"
//#include "schedule.hh"

//===========================================================
//===========================================================
// Partitions a graph into strongly connected components
// USAGE : Tarjan<N,A> t(mygraph); ...t.partition()...
//===========================================================
//===========================================================

template <typename N, typename A = int>
class Tarjan
{
    // Additional information associated to each node
    // during the visit
    struct tarjanAux {
        bool fVisited = false;
        bool fStacked = false;
        int  fNum1    = 0;
        int  fNum2    = 0;
    };

    const digraph<N, A>&   fGraph;
    int                    fGroup;
    std::stack<N>          fStack;
    std::map<N, tarjanAux> fAux;
    std::set<std::set<N>>  fPartition;
    int                    fCycleCount;

    // visit a specific node n of the graph
    void visit(const N& v)
    {
        // std::cout << "start (first) visit of " << v << std::endl;
        auto& x = fAux[v];
        fStack.push(v);
        x.fStacked = true;
        x.fVisited = true;
        x.fNum1 = x.fNum2 = fGroup;
        ++fGroup;

        // std::cout << "visit all nodes connected to " << v << std::endl;
        for (const auto& p : fGraph.connections(v)) {
            // std::cout << "we have a connection " << v << "-" << p.second << "->" << p.first <<
            // std::endl;
            const N& w = p.first;
            auto&    y = fAux[w];
            if (!y.fVisited) {
                visit(w);
                x.fNum2 = std::min(x.fNum2, y.fNum2);
            } else {
                if (y.fStacked) {
                    // std::cout << "the node " << w << " is already in the std::stack" <<
                    // std::endl;
                    x.fNum2 = std::min(x.fNum2, y.fNum1);
                }
            }
        }

        if (x.fNum1 == x.fNum2) {
            // std::cout << "the node " << v << " is the root of a cycle" << std::endl;

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
            if ((cycle.size() > 1) || fGraph.areConnected(v, v)) { fCycleCount++; }
        }
        // std::cout << "end (first) visit of " << v << std::endl;
    }

   public:
    explicit Tarjan(const digraph<N, A>& g) : fGraph(g), fGroup(0), fCycleCount(0)
    {
        for (const auto& n : fGraph.nodes()) {
            if (fAux.find(n) == fAux.end()) { visit(n); }
        }
    }

    const std::set<std::set<N>>& partition() const { return fPartition; }

    int cycles() const { return fCycleCount; }
};

//===========================================================
//===========================================================
// cycles:graph->int : counts the number of cycles
// (strongly connected components) of a graph
//===========================================================
//===========================================================

template <typename N, typename A = int>
inline int cycles(const digraph<N, A>& g)
{
    Tarjan<N, A> T(g);
    return T.cycles();
}

//===========================================================
//===========================================================
// graph2dag : transfoms a graph into a dag of supernodes,
// ie strongly connected components. The connection value
// between two supernodes A and B is the smallest value of all
// the connections between nodes of A and nodes of B.
//===========================================================
//===========================================================

template <typename N, typename A = int>
inline digraph<digraph<N, A>, A> graph2dag(const digraph<N, A>& g)
{
    Tarjan<N, A>               T(g);  // the partition of g
    std::map<N, digraph<N, A>> M;     // std::mapping between nodes and supernodes
    digraph<digraph<N, A>, A>  sg;    // the resulting supergraph

    // build the graph of supernodes

    // For each std::set s of the partition, create the corresponding graph sn
    // create also a std::mapping in order to retrieve the supernode a node
    /// belongs to.
    for (const auto& s : T.partition()) {
        digraph<N, A> sn;                     // the supernode graph
        for (const N& n : s) {                // for each node of a cycle
            M.insert(std::make_pair(n, sn));  // remember its supernode
            sn.add(n);                        // and add it to the super node
        }
        sg.add(sn);  // and add the super node to the super graph
    }

    // compute the connections between the supernodes
    for (const auto& n1 : g.nodes()) {
        digraph<N, A> sn1(M[n1]);
        for (const auto& c : g.connections(n1)) {
            digraph<N, A> sn2(M[c.first]);
            if (sn1 == sn2) {
                // the connection is inside the same supernode
                sn1.add(n1, c.first, c.second);
            } else {
                // the connection is between supernodes
                sg.add(sn1, sn2, c.second);  // exploit the fact that add will keep the mini
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
// connections between nodes of A and nodes of B.
//===========================================================
//===========================================================

template <typename N, typename A = int>
inline digraph<digraph<N, A>, A> graph2dag2(const digraph<N, A>& g)
{
    Tarjan<N, A>               T(g);  // the partition of g
    std::map<N, digraph<N, A>> M;     // std::mapping between nodes and supernodes
    digraph<digraph<N, A>, A>  sg;    // the resulting supergraph
    std::map<std::pair<digraph<N, A>, digraph<N, A>>, int>
        CC;  // count of connections between supernodes

    // build the graph of supernodes

    // for each std::set s of the partition, create the corresponding graph sn
    // create also a std::mapping in order to retrieve the supernode a node
    /// belongs to.
    for (const auto& s : T.partition()) {
        digraph<N, A> sn;                     // the supernode graph
        for (const N& n : s) {                // for each node of a cycle
            M.insert(std::make_pair(n, sn));  // remember its supernode
            sn.add(n);                        // and add it to the super node
        }
        sg.add(sn);  // and add the super node to the super graph
    }

    // compute the number of connections between the supernodes
    for (const auto& n1 : g.nodes()) {             // for each node n1
        digraph<N, A> sn1(M[n1]);                  // retrieve the supernode
        for (const auto& c : g.connections(n1)) {  // for each destination of n
            digraph<N, A> sn2(M[c.first]);
            if (sn1 == sn2) {
                // the connection is inside the same supernode
                sn1.add(n1, c.first, c.second);
            } else {
                // We count the external connections between two supernodes
                CC[std::make_pair(sn1, sn2)] += 1;
            }
        }
    }

    // we connect the super nodes using the count of external connections
    for (const auto& entry : CC) { sg.add(entry.first.first, entry.first.second, entry.second); }

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

template <typename N, typename A = int>
inline std::vector<std::vector<N>> parallelize(const digraph<N, A>& g)
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
            for (const auto& e : g.connections(n1)) { l = std::max(l, level(e.first, levelcache)); }
            return levelcache[n1] = l + 1;
        }
    };

    std::map<N, int> levelcache;
    // compute the level of each node in the graph
    int l = -1;
    for (const N& n : g.nodes()) { l = std::max(l, level(n, levelcache)); }
    // create a graph for each level and place
    // each node in the appropriate level
    std::vector<std::vector<N>> v;
    v.resize(l + 1);
    for (const N& n : g.nodes()) { v[levelcache[n]].push_back(n); }

    return v;
}

template <typename N, typename A = int>
inline std::vector<std::vector<N>> rparallelize(const digraph<N, A>& G)
{
    std::vector<std::vector<N>> P = parallelize(G);
    int                         i = 0;
    int                         j = P.size() - 1;

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

template <typename N, typename A = int>
inline std::vector<N> serialize(const digraph<N, A>& G)
{
    //------------------------------------------------------------------------
    // visit : a local std::function (simulated using a lambda) to visit a graph
    // g : the graph
    // n : the node
    // V : std::set of already visited nodes
    // S : serialized std::vector of nodes
    //------------------------------------------------------------------------
    using Visitfun =
        std::function<void(const digraph<N, A>&, const N&, std::set<N>&, std::vector<N>&)>;
    Visitfun visit = [&visit](const digraph<N, A>& g, const N& n, std::set<N>& V,
                              std::vector<N>& S) {
        if (V.find(n) == V.end()) {
            V.insert(n);
            for (const auto& p : g.connections(n)) { visit(g, p.first, V, S); }
            S.push_back(n);
        }
    };

    std::vector<N> S;
    std::set<N>    V;
    for (const N& n : G.nodes()) { visit(G, n, V, S); }
    return S;
}

//===========================================================
//===========================================================
// std::mapgraph(foo) : transfoms a graph  by applying foo:N->M
// to each node of graph. The connections are preserved.
//===========================================================
//===========================================================

template <typename N, typename M, typename A = int>
inline digraph<M, A> mapnodes(const digraph<N, A>& g, std::function<M(const N&)> foo)
{
    digraph<M>     r;
    std::map<N, M> cache;
    // create a new graph with the transformed nodes
    for (const auto& n1 : g.nodes()) {
        M n2 = foo(n1);
        r.add(n2);
        cache.insert(std::make_pair(n1, n2));
    }

    // copy the connections
    for (const auto& n : g.nodes()) {
        for (const auto& cnx : g.connections(n)) { r.add(cache[n], cache[cnx.first], cnx.second); }
    }
    return r;
}

//===========================================================
//===========================================================
// reverse(g) : reverse all the connections of a graph. The
// connections keep their value.
// Property : reverse(reverse(g)) = g;
//===========================================================
//===========================================================

template <typename N, typename A = int>
inline digraph<N, A> reverse(const digraph<N, A>& g)
{
    digraph<N, A> r;
    // copy the connections
    for (const auto& n : g.nodes()) {
        r.add(n);
        for (const auto& cnx : g.connections(n)) { r.add(cnx.first, n, cnx.second); }
    }
    return r;
}

//===========================================================
//===========================================================
// mapconnections(g, keep) -> g' : transfoms a graph by
// applying the std::function keep to each connection. If keep
// returns true the connection is maintained, otherwise it
// is removed.
//===========================================================
//===========================================================

template <typename N, typename A = int>
inline digraph<N, A> mapconnections(const digraph<N, A>&                         G,
                                    std::function<bool(const N&, const N&, int)> keep)
{
    digraph<N, A> R;
    for (const N& n : G.nodes()) {
        R.add(n);
        for (const auto& c : G.connections(n)) {
            if (keep(n, c.first, c.second)) { R.add(n, c.first, c.second); }
        }
    }
    return R;
}

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
template <typename N, typename A = int>
void splitgraph(const digraph<N, A>& G, std::function<bool(const N&)> left, digraph<N, A>& L,
                digraph<N, A>& R)
{
    for (auto n : G.nodes()) {
        if (left(n)) {
            L.add(n);
            for (const auto& c : G.connections(n)) {
                if (left(c.first)) { L.add(n, c.first, c.second); }
            }
        } else {
            R.add(n);
            for (const auto& c : G.connections(n)) {
                if (!left(c.first)) { R.add(n, c.first, c.second); }
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
template <typename N, typename A = int>
digraph<N, A> subgraph(const digraph<N, A>& G, const std::set<N>& S)
{
    digraph<N, A> R;     // the (R)esulting graph
    std::set<N>   W{S};  // nodes (W)aiting to be processed
    std::set<N>   P;     // nodes already (P)rocessed
    while (!W.empty()) {
        std::set<N> M;  // (M)ore nodes to process at next iteration
        for (auto n : W) {
            R.add(n);     // add n to the resulting graph
            P.insert(n);  // mark n as processed
            for (const auto& a : G.connections(n)) {
                R.add(n, a.first, a.second);       // add its adjacent nodes
                if (P.find(a.first) == P.end()) {  // is it new ?
                    M.insert(a.first);             // we will have to process it
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
// cuts all the connections of graph g of weight >= d
//===========================================================
//===========================================================

template <typename N, typename A = int>
inline digraph<N, A> cut(const digraph<N, A>& G, int dm)
{
    return mapconnections<N>(G, [dm](const N&, const N&, int d) -> bool { return d < dm; });
}

//===========================================================
//===========================================================
// chain(g) -> g'
// Keep only the chain connections, that is connections
// (n1 -d-> n2) such that dst(n1) == {n2} && src(n2) == {n1}
// If strict is true, only the node part of a chain are kept.
//===========================================================
//===========================================================

template <typename N, typename A = int>
inline digraph<N, A> chain(const digraph<N, A>& g, bool strict)
{
    const digraph<N, A> h = reverse(g);
    digraph<N, A>       r;
    for (const auto& n : g.nodes()) {
        if (!strict) r.add(n);
        if (g.connections(n).size() == 1) {
            for (const auto& m : g.connections(n)) {
                if (h.connections(m.first).size() == 1) { r.add(n, m.first, m.second); }
            }
        }
    }
    return r;
}

template <typename N, typename A = int>
inline std::vector<N> roots(const digraph<N, A>& G)
{
    std::map<N, int> R;
    for (const N& n : G.nodes()) {
        for (const auto& c : G.connections(n)) { R[c.first]++; }
    }
    std::vector<N> V;
    for (const N& n : G.nodes()) {
        if (R[n] == 0) V.push_back(n);
    }
    return V;
}

template <typename N, typename A = int>
inline std::vector<N> leaves(const digraph<N, A>& G)
{
    std::vector<N> L;
    for (const N& n : G.nodes()) {
        if (G.connections(n).size() == 0) { L.push_back(n); }
    }
    return L;
}

/*******************************************************************************
********************************************************************************

                                        VARIOUS PRINTING std::functionS

 *******************************************************************************
 ******************************************************************************/

//===========================================================
//===========================================================
// file << graph : print graph on a stream
//===========================================================
//===========================================================

template <typename N, typename A>
inline std::ostream& operator<<(std::ostream& file, const digraph<N, A>& g)
{
    std::string sep = "";

    file << "Graph {";
    for (const N& n : g.nodes()) {
        bool hascnx = false;
        for (const auto& c : g.connections(n)) {
            hascnx = true;
            file << sep << n << '-' << (c.second) << "->" << (c.first);
            sep = ", ";
        }
        if (!hascnx) { file << sep << n; }
        sep = ", ";
    }

    return file << "}";
}

//===========================================================
//===========================================================
// dotfile(file, graph) print graph on a stream in .dot format
//===========================================================
//===========================================================

template <typename N, typename A>
inline std::ostream& dotfile(std::ostream& file, const digraph<N, A>& g, bool clusters = false)
{
    file << "digraph mygraph {" << std::endl;
    for (const N& n : g.nodes()) {
        std::stringstream sn;
        sn << '"' << n << '"';
        bool hascnx = false;
        for (const auto& c : g.connections(n)) {
            std::stringstream sm;
            sm << '"' << c.first << '"';
            hascnx = true;
            file << "\t" << sn.str() << "->" << sm.str() << " [label=\""
                 << arrow_traits<A>::label(c.second) << "\"];" << std::endl;
        }
        if (!hascnx) { file << "\t" << sn.str() << ";" << std::endl; }
    }

    if (clusters) {
        Tarjan<N, A> T(g);
        int          ccount = 0;  // cluster count
        for (const auto& s : T.partition()) {
            file << "\t"
                 << "subgraph cluster" << ccount++ << " { " << std::endl;
            for (const N& n : s) { file << "\t\t" << '"' << n << '"' << ";" << std::endl; }
            file << "\t"
                 << "}" << std::endl;
        }
    }

    return file << "}" << std::endl;
}
