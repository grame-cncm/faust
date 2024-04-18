#pragma once

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <utility>

namespace itv {
//==============================================================================
// Definitions of signed and unsigned intervals for bitwise operations
//==============================================================================

// Intervals are represented as pairs of numbers.
template <typename T>
struct BitwiseInterval {
    T lo;
    T hi;
};

// We need signed and unisgned intervals
using SInterval = BitwiseInterval<int>;
using UInterval = BitwiseInterval<unsigned int>;

// Empty intervals represented by (.lo > .hi)
constexpr UInterval UEMPTY{UINT_MAX, 0};
constexpr SInterval SEMPTY{INT_MAX, INT_MIN};

//==============================================================================
// Predicates
//==============================================================================

// Empty intervals are intervals such that: lo > hi
template <typename T>
bool isEmpty(const BitwiseInterval<T>& i)
{
    return i.lo > i.hi;
}

// Equality of intervals.
template <typename T>
bool operator==(const BitwiseInterval<T>& a, const BitwiseInterval<T>& b)
{
    if (isEmpty(a)) {
        return isEmpty(b);
    }
    return (a.lo == b.lo) && (a.hi == b.hi);
}

// Equality of intervals.
template <typename T>
bool operator!=(const BitwiseInterval<T>& a, const BitwiseInterval<T>& b)
{
    if (isEmpty(a)) {
        return !isEmpty(b);
    }
    return (a.lo != b.lo) || (a.hi != b.hi);
}

//==============================================================================
// Printing
//==============================================================================

inline std::ostream& operator<<(std::ostream& os, const UInterval& x)
{
    if (isEmpty(x)) {
        return os << "U[]";
    }
    return os << "U[" << x.lo << ".." << x.hi << "]";
}

inline std::ostream& operator<<(std::ostream& os, const SInterval& x)
{
    if (isEmpty(x)) {
        return os << "S[]";
    }
    return os << "S[" << x.lo << ".." << x.hi << "]";
}

//==============================================================================
// Operations
//==============================================================================

// Union of intervals
template <typename T>
BitwiseInterval<T> operator+(const BitwiseInterval<T>& a, const BitwiseInterval<T>& b)
{
    if (isEmpty(a)) {
        return b;
    }
    if (isEmpty(b)) {
        return a;
    }
    return {std::min(a.lo, b.lo), std::max(a.hi, b.hi)};
}

std::pair<UInterval, UInterval> signSplit(const SInterval& x);
SInterval                       signMerge(const UInterval& np, const UInterval& pp);

UInterval bitwiseUnsignedNot(const UInterval& a);
SInterval bitwiseSignedNot(const SInterval& a);

UInterval bitwiseUnsignedOr(const UInterval& a, const UInterval& b);
SInterval bitwiseSignedOr(const SInterval& a, const SInterval& b);

UInterval bitwiseUnsignedAnd(const UInterval& a, const UInterval& b);
SInterval bitwiseSignedAnd(const SInterval& a, const SInterval& b);

UInterval bitwiseUnsignedXOr(const UInterval& a, const UInterval& b);
SInterval bitwiseSignedXOr(const SInterval& a, const SInterval& b);
}  // namespace itv
