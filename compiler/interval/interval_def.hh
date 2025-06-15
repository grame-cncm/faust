/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#pragma once

#include <limits.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

// #include "global"

// ***************************************************************************
//
//     An Interval is a (possibly empty) set of numbers approximated by two
//     boundaries. Empty intervals have NAN as boundaries.
//
//****************************************************************************
namespace itv {

/**
 * Cast a double to an int, with saturation.
 */
inline int saturatedIntCast(double d)
{
    return int(std::min(2147483647.0, std::max(d, -2147483648.0)));
}

class interval {
   private:
    double fLo{std::numeric_limits<double>::lowest()};  ///< minimal value
    double fHi{std::numeric_limits<double>::max()};     ///< maximal value
    int    fLSB{-24};                                   ///< lsb in bits

   public:
    //-------------------------------------------------------------------------
    // constructors
    //-------------------------------------------------------------------------

    interval() = default;

    interval(double n, double m, int lsb = -24) noexcept
    {
        if (n == 0.0 && m == 0.0) {
            fLo  = 0.0;
            fHi  = 0.0;
            fLSB = 0;
            // std::cerr << "Warning: creating an interval with both bounds equal to zero."
            //           << std::endl;
            return;
        }
        if (lsb == INT_MIN) {
            fLSB = -24;
        } else {
            fLSB = lsb;
        }

        if (std::isnan(n) || std::isnan(m)) {
            fLo = NAN;
            fHi = NAN;
        } else {
            fLo = std::min(n, m);
            fHi = std::max(n, m);
        }
    }

    explicit interval(double x) noexcept
    {
        if (x == 0) {
            fLo  = 0;
            fHi  = 0;
            fLSB = 0;
        } else {
            // compute the preficion needed to represent x
            // in the form x = 2^p * y, where y is an integer
            int    p = 0;
            double y = x;
            double ipart;
            while (std::modf(y, &ipart) != 0.0) {
                y *= 2.0;
                p--;
            }
            fLo  = x;
            fHi  = x;
            fLSB = p;
        }
    }

    // interval(const interval& r) : fEmpty(r.empty()), fLo(r.lo()), fHi(r.hi())
    // {}

    //-------------------------------------------------------------------------
    // basic properties
    //-------------------------------------------------------------------------

    bool isEmpty() const { return std::isnan(fLo) || std::isnan(fHi); }
    bool isValid() const { return !isEmpty(); }  // for compatibility reasons
    bool isUnbounded() const { return std::isinf(fLo) || std::isinf(fHi); }
    bool isBounded() const { return !isUnbounded(); }
    bool has(double x) const { return (fLo <= x) && (fHi >= x); }
    bool is(double x) const { return (fLo == x) && (fHi == x); }
    bool hasZero() const { return has(0.0); }
    bool isZero() const { return is(0.0); }
    bool isconst() const { return (fLo == fHi) && !std::isnan(fLo); }

    bool ispowerof2() const
    {
        auto n = int(fHi);
        return isconst() && ((n & (-n)) == n);
    }

    bool isbitmask() const
    {
        int n = int(fHi) + 1;
        return isconst() && ((n & (-n)) == n);
    }

    double lo() const { return fLo; }
    double hi() const { return fHi; }
    double size() const { return fHi - fLo; }
    int    lsb() const { return fLSB; }

    // position of the most significant bit of the value, without taking the sign bit into account
    int msb() const
    {
        if ((fLo == 0) && (fHi == 0)) {
            return 0;
        }

        // amplitude of the interval
        // can be < 1.0, in which case the msb will be negative and indicate the number of implicit
        // leading zeroes
        double range = std::max(std::abs(fLo), std::abs(fHi));

        if (std::isinf(range)) {
            // if (fLSB == 0) // if we're dealing with integers: is that a good criterion?
            return 31;
            // return 20;  // max MSB of the VHDL design; TODO: change when integrating in the
            // compiler
        }

        int l = int(std::ceil(std::log2(range)));

        // The sign bit will be added later on
        return l;
    }

    std::string to_string() const
    {
        if (isEmpty()) {
            return "[]";
        } else {
            char buffer[64];
            snprintf(buffer, 63, "[%g, %g]", fLo, fHi);
            return std::string(buffer);
        }
    }
};

//-------------------------------------------------------------------------
// printing
//-------------------------------------------------------------------------

inline std::ostream& operator<<(std::ostream& dst, const interval& i)
{
    if (i.isEmpty()) {
        return dst << "interval()";
    } else {
        return dst << "interval(" << i.lo() << ',' << i.hi() << ',' << i.lsb() << ")";
    }
}

//-------------------------------------------------------------------------
// set operations
//-------------------------------------------------------------------------

inline interval empty() noexcept
{
    return {NAN, NAN, 0};
}

inline interval intersection(const interval& i, const interval& j)
{
    if (i.isEmpty()) {
        return i;
    } else if (j.isEmpty()) {
        return j;
    } else {
        double l = std::max(i.lo(), j.lo());
        double h = std::min(i.hi(), j.hi());
        int    p = std::min(i.lsb(),
                            j.lsb());  // precision of the intersection should be the finest of the two
        if (l > h) {
            return empty();
        } else {
            return {l, h, p};
        }
    }
}

inline interval reunion(const interval& i, const interval& j)
{
    if (i.isEmpty()) {
        return j;
    } else if (j.isEmpty()) {
        return i;
    } else {
        double l = std::min(i.lo(), j.lo());
        double h = std::max(i.hi(), j.hi());
        int    p =
            std::min(i.lsb(), j.lsb());  // precision of the reunion should be the finest of the two
        return {l, h, p};
    }
}

inline interval singleton(double x)
{
    if (x == 0) {
        return {0, 0, 0};
    }

    /* int precision = lsb;
    while (floor(x * pow(2, -precision - 1)) == x * pow(2, -precision - 1) && x != 0) {
        precision++;
    }
    */

    int m = std::floor(std::log2(std::abs(x)));

    int precision = m - 32;  // 32 = set width

    return {x, x, precision};
}

//-------------------------------------------------------------------------
// predicates
//-------------------------------------------------------------------------

// basic predicates
inline bool operator==(const interval& i, const interval& j)
{
    return (i.isEmpty() && j.isEmpty()) || ((i.lo() == j.lo()) && (i.hi() == j.hi()));
}

inline bool operator<=(const interval& i, const interval& j)
{
    return (i.lo() >= j.lo()) && (i.hi() <= j.hi());
}

// additional predicates
inline bool operator!=(const interval& i, const interval& j)
{
    return !(i == j);
}

inline bool operator<(const interval& i, const interval& j)
{
    return (i <= j) && (i != j);
}

inline bool operator>=(const interval& i, const interval& j)
{
    return j <= i;
}

inline bool operator>(const interval& i, const interval& j)
{
    return j < i;
}
}  // namespace itv
