#pragma once

//===========================================================
//===========================================================
//                      arrow.hh
//
// Arrows are connections between the nodes of a graph
//
//===========================================================
//===========================================================

#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <utility>

#include "stdprinting.hh"

//===========================================================
//                      arrow_traits
//
// Common operations on arrows
//
//===========================================================

template <typename A>
struct arrow_traits {
    static A           combine(const A& x, const A& y);
    static A           empty();
    static bool        isEmpty(const A& x);
    static int         mindist(const A& x);
    static std::string label(const A& x);
};

//===========================================================
//                      int arrows
//
// Arrows carrying only a time dependency between nodes
//
//===========================================================

template <>
struct arrow_traits<int> {
    static int         combine(int x, int y) { return (x < y) ? x : y; }
    static int         empty() { return INT32_MAX; }
    static bool        isEmpty(int d) { return d == INT32_MAX; }
    static int         mindist(int d) { return d; }
    static std::string label(int d) { return std::to_string(d); }
};

//===========================================================
//                      multidep arrow
//
// More sophisticated arrows with multiple communications
// channels. Each channel is associated with a time
// dependency. This association is represented by a map.
// A global minimal time dependency is also stored. It
// represents the minimal time dependecy associated with
// a communication channel.
//
//===========================================================

using multidep = std::pair<std::map<std::string, int>, int>;

inline multidep mdep(const std::string& s) { return {{{s, 0}}, 0}; }
inline multidep mdep(const std::string& s, int d) { return {{{s, d}}, d}; }

template <>
struct arrow_traits<multidep> {
    static std::string label(const multidep& M)
    {
        std::stringstream sn;
        std::string       sep = "";
        for (const auto& d : M.first) {
            sn << sep << d.first << ":" << d.second;
            sep = " ";
        }
        return sn.str();
    }
    static multidep combine(const multidep& X, const multidep& Y)
    {
        // std::cerr << "combine " << label(X) << " + " << label(Y) << std::endl;
        multidep M;
        auto     itx = X.first.begin();
        auto     ity = Y.first.begin();
        while ((itx != X.first.end()) && (ity != Y.first.end())) {
            if (itx->first < ity->first) {
                M.first[itx->first] = itx->second;
                itx++;
            } else if (ity->first < itx->first) {
                M.first[ity->first] = ity->second;
                ity++;
            } else {
                M.first[ity->first] = std::min(itx->second, ity->second);
                itx++;
                ity++;
            }
        }
        while (itx != X.first.end()) {
            M.first[itx->first] = itx->second;
            itx++;
        }
        while (ity != Y.first.end()) {
            M.first[ity->first] = ity->second;
            ity++;
        }
        M.second = std::min(X.second, Y.second);
        // std::cerr << "combine " << label(X) << " + " << label(Y) << " = " << label(M) <<
        // std::endl;
        return M;
    }

    static multidep empty() { return {{}, INT32_MAX}; }
    static bool     isEmpty(const multidep& M) { return M.first.size() == 0; }
    static int      mindist(const multidep& M) { return M.second; }
};
