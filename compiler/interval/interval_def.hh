/* Copyright 2020-2026 Yann Orlarey, Agathe Herrou, Stéphane Letz
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Lineage : this file started in 2020 as a copy of the FAUST compiler's
 * interval class (GRAME, GPL) and has been fully rewritten since -- the
 * lo/hi/lsb model, the NaN-empty convention and every operation are new.
 */

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
 * The precision of the program the intervals describe : 0 none (the default : the
 * library computes in double and rounds nothing, as it always did), 1 single (float),
 * 2 double, 3 quad, 4 fixed point. A user declares the precision of its program ; the
 * Faust compiler sets it from its float size (-single, -double...).
 */
inline int& programPrecision()
{
    static int precision = 0;
    return precision;
}

/**
 * A bound of a float-carried value, at the precision of the program. Round to nearest
 * is monotone : for a monotone operation, the bound computed in double then rounded
 * to float is the value the program computes at that bound. For +, -, *, / and sqrt
 * of floats, the double rounding is innocuous (53 >= 2*24 + 2) : rounding in double
 * then in float gives the float the program computes, even when the double result is
 * not exact. Not covered : the C++ compiler's FMA contraction and reassociation, the
 * libm (not correctly rounded) ; the decisions keep their own margin for those (the
 * guard of a table access near its edges). Round to nearest, not outward : a constant
 * stays a point. Left as they are : an integer bound beyond 2^24 (an integer value may
 * carry a float precision by default) and a nonzero bound below the smallest normal
 * float (its rounding to 0 would break the invariants of pow and log).
 */
inline double programBound(double b)
{
    if (programPrecision() != 1 || std::isnan(b) || std::isinf(b)) return b;
    if (std::fabs(b) >= 16777216.0 && b == std::floor(b)) return b;
    // below the smallest normal float, the rounding would reach 0 and break the
    // invariants of the operations (a positive bound stays positive : pow, log)
    if (b != 0 && std::fabs(b) < 0x1p-126) return b;
    return double(float(b));
}

/**
 * k ulps of the program's precision at the magnitude of [lo, hi] : the margin of a rule
 * that reasons on reals (the hull of a convex combination), whose float evaluation can
 * leave the hull by a few roundings. The elementary operations need none : their
 * bounds are computed at the precision of the program (programBound).
 */
inline double ulpMargin(double lo, double hi, int k)
{
    int    p   = programPrecision();
    double eps = (p == 1 || p == 4) ? 0x1p-23 : ((p == 3) ? 0x1p-112 : 0x1p-52);
    return k * eps * std::max(std::fabs(lo), std::fabs(hi));
}

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
            // a float-carried value : its bounds at the precision of the program
            if (fLSB < 0) {
                fLo = programBound(fLo);
                fHi = programBound(fHi);
            }
        }
    }

    explicit interval(double x) noexcept
    {
        if (x == 0) {
            fLo  = 0;
            fHi  = 0;
            fLSB = 0;
        } else {
            // a fractional constant is a float of the program
            if (x != std::floor(x)) x = programBound(x);
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
        return dst << "empty()";
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

/**
 * Return the interval containing every finite value representable by a double.
 *
 * This is the explicit equivalent of the historical default constructor. It
 * does not contain positive or negative infinity.
 */
inline interval fullFinite(int lsb = -24) noexcept
{
    return {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), lsb};
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
