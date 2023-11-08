#pragma once

//===========================================================
//===========================================================
//                      printing.hh
//
// print operator<<() for pairs, vectors, sets and maps
//
//===========================================================
//===========================================================

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

//===========================================================
// Declarations of the operators
//===========================================================

template <typename N, typename M>
inline std::ostream& operator<<(std::ostream& file, const std::pair<N, M>& V);

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const std::vector<N>& V);

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const std::set<N>& S);

template <typename N, typename A>
inline std::ostream& operator<<(std::ostream& file, const std::map<N, A>& S);

//===========================================================
// Implementation of the operators
//===========================================================

// for pairs

template <typename N, typename M>
inline std::ostream& operator<<(std::ostream& file, const std::pair<N, M>& V)
{
    return file << "std::pair{" << V.first << ", " << V.second << "}";
}

// for vectors

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

// for sets

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const std::set<N>& S)
{
    std::string sep = "";

    file << "std::set{";
    for (const N& e : S) {
        file << sep << e;
        sep = ", ";
    }
    return file << "}";
}

// for maps

template <typename N, typename A>
inline std::ostream& operator<<(std::ostream& file, const std::map<N, A>& S)
{
    std::string sep = "";

    file << "std::map{";
    for (const auto& e : S) {
        file << sep << e;
        sep = ", ";
    }
    return file << "}";
}

// for lists

template <typename N, typename A>
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
