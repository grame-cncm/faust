#pragma once

#include <set>
#include <tuple>
#include <vector>

//---------------------------------------------------------------------------------------
// code from : https://stackoverflow.com/questions/20834838/using-tuple-in-unordered-map
// function has to live in the std namespace
// so that it is picked up by argument-dependent name lookup (ADL).
namespace std {
namespace yann {
// Code from boost
// Reciprocal of the golden ratio helps spread entropy
//     and handles duplicates.
// See Mike Seymour in magic-numbers-in-boosthash-combine:
//     https://stackoverflow.com/questions/4948780

template <class T>
inline void hash_combine(std::size_t& seed, T const& v)
{
    seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// Recursive template code derived from Matthieu M.
template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
struct HashValueImpl {
    static void apply(size_t& seed, Tuple const& tuple)
    {
        HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
        hash_combine(seed, get<Index>(tuple));
    }
};

template <class Tuple>
struct HashValueImpl<Tuple, 0> {
    static void apply(size_t& seed, Tuple const& tuple) { hash_combine(seed, get<0>(tuple)); }
};
}  // namespace yann

template <typename... TT>
struct hash<std::tuple<TT...>> {
    size_t operator()(std::tuple<TT...> const& tt) const
    {
        size_t seed = 0;
        yann::HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
        return seed;
    }
};

template <typename T>
struct hash<std::set<T>> {
    size_t operator()(const std::set<T>& S) const
    {
        size_t seed = 0;
        for (const T& v : S) {
            seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

template <typename T>
struct hash<std::vector<T>> {
    size_t operator()(const std::vector<T>& S) const
    {
        size_t seed = 0;
        for (const T& v : S) {
            seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

}  // namespace std