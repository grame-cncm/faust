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
#include <limits>
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
 * The precision of the program the intervals describe : 1 single (float), 2 double (the
 * default), 3 quad, 4 fixed point. A user declares the precision of its program ; the
 * Faust compiler sets it from its float size (-single, -double...).
 */
inline int& programPrecision()
{
    static int precision = 2;
    return precision;
}

/**
 * The compensation of the libm (true by default) : the functions of the libm (sin, exp,
 * log, pow...) are not guaranteed correctly rounded, and the program calls the libm of
 * its target, not the one that computes the intervals. Their bounds widen by 2 ulps of
 * the program's precision (libmBounds). A user may turn it off when both libms are
 * correctly rounded (CORE-MATH for instance) : the libm of the target, and the libm of
 * the machine that computes the intervals.
 */
inline bool& libmCompensation()
{
    static bool compensation = true;
    return compensation;
}

/**
 * A bound rounded to float : to nearest (dir 0), down (dir < 0) or up (dir > 0). Beyond
 * the largest float, a lower bound stays the largest float and an upper bound reaches
 * infinity (the value of the program overflows).
 */
inline double floatBound(double b, int dir)
{
    if (std::isnan(b) || std::isinf(b)) {
        return b;
    }
    const double fmax = std::numeric_limits<float>::max();
    if (b > fmax) {
        return (dir < 0) ? fmax : HUGE_VAL;
    }
    if (b < -fmax) {
        return (dir > 0) ? -fmax : -HUGE_VAL;
    }
    float f = float(b);
    if (dir < 0 && double(f) > b) {
        f = std::nextafter(f, -HUGE_VALF);
    }
    if (dir > 0 && double(f) < b) {
        f = std::nextafter(f, HUGE_VALF);
    }
    return double(f);
}

/**
 * A bound of a float-carried value, at the precision of the program : rounded to
 * nearest (dir 0, a constant of the program), down (dir < 0, a lower bound) or up
 * (dir > 0, an upper bound). Only the single precision rounds : the bounds are doubles
 * already, computed with directed rounding (addDown, mulUp...). Left as they are : an
 * integer bound beyond 2^24 (an integer value may carry a float precision by default)
 * and a nonzero bound below the smallest normal float (its rounding to 0 would break
 * the invariants of pow and log).
 */
inline double programBound(double b, int dir)
{
    if (programPrecision() != 1 || std::isnan(b) || std::isinf(b)) return b;
    if (std::fabs(b) >= 16777216.0 && b == std::floor(b)) return b;
    // below the smallest normal float, the rounding would reach 0 and break the
    // invariants of the operations (a positive bound stays positive : pow, log)
    if (b != 0 && std::fabs(b) < 0x1p-126) return b;
    return floatBound(b, dir);
}

//-------------------------------------------------------------------------
// Directed rounding. An interval must contain every value the compiled program can
// produce. Rounded to nearest, a bound is only the value of ONE way of computing it :
// each operation rounded apart, in the written order. The C++ compiler may compute
// otherwise -- clang fuses a*b + c into an FMA by default, which keeps a*b exact --
// and a bound rounded to nearest may then exclude the value of the program
// (x = a*b + c proven >= 0.5 where the FMA gives 0.49999997). A lower bound rounded
// down and an upper bound rounded up contain both : RD(RD(ab) + c) <= RN(RN(ab) + c)
// and RD(RD(ab) + c) <= RD(ab + c) <= RN(ab + c), RD and RN being monotone.
//
// The exact result of +, -, *, / and sqrt rounded down or up, in double, from the
// result rounded to nearest and its exact error (error-free transformations : TwoSum
// for the sum, the FMA for the others). An exact result is left as it is : an
// interval widens only where the value of the program is uncertain. Near the
// underflow, where the error is no longer exact, the result steps one double outward.
// An overflow saturates on the side of the bound (a lower bound of +inf is the
// largest double). 0 times an infinite bound is 0, as in specialmult.
//-------------------------------------------------------------------------

namespace directed {
constexpr double kTiny = 0x1p-969;  // 2^(-1022 + 53) : the errors are exact above

inline double stepDown(double r)
{
    return std::nextafter(r, -HUGE_VAL);
}
inline double stepUp(double r)
{
    return std::nextafter(r, HUGE_VAL);
}
// r : the result rounded to nearest, e : its exact error (the exact result is r + e)
inline double down(double r, double e)
{
    return (e < 0) ? stepDown(r) : r;
}
inline double up(double r, double e)
{
    return (e > 0) ? stepUp(r) : r;
}
// an infinite result of finite operands is an overflow
inline double overflow(double r, bool finiteOperands, int dir)
{
    if (!finiteOperands) {
        return r;
    }
    if (dir < 0 && r > 0) {
        return std::numeric_limits<double>::max();
    }
    if (dir > 0 && r < 0) {
        return -std::numeric_limits<double>::max();
    }
    return r;
}
inline double add(double a, double b, int dir)
{
    double s = a + b;
    if (std::isnan(s)) {
        return s;
    }
    if (std::isinf(s)) {
        return overflow(s, std::isfinite(a) && std::isfinite(b), dir);
    }
    double bb = s - a;
    double e  = (a - (s - bb)) + (b - bb);  // TwoSum, exact
    return (dir < 0) ? down(s, e) : up(s, e);
}
inline double mul(double a, double b, int dir)
{
    if (a == 0 || b == 0) {
        return 0;
    }
    double p = a * b;
    if (std::isnan(p)) {
        return p;
    }
    if (std::isinf(p)) {
        return overflow(p, std::isfinite(a) && std::isfinite(b), dir);
    }
    if (std::fabs(p) < kTiny) {
        return (dir < 0) ? stepDown(p) : stepUp(p);
    }
    double e = std::fma(a, b, -p);  // exact
    return (dir < 0) ? down(p, e) : up(p, e);
}
inline double div(double a, double b, int dir)
{
    double q = a / b;
    if (std::isnan(q) || a == 0 || std::isinf(b)) {
        return q;  // a 0 or a division by inf : exact
    }
    if (std::isinf(q)) {
        return overflow(q, std::isfinite(a) && b != 0, dir);
    }
    if (std::fabs(q) < kTiny || std::fabs(a) < kTiny) {
        return (dir < 0) ? stepDown(q) : stepUp(q);
    }
    double r = std::fma(-q, b, a);  // a - q*b, exact : the exact quotient is q + r/b
    double e = (b > 0) ? r : -r;    // the sign of the error
    return (dir < 0) ? down(q, e) : up(q, e);
}
inline double sqrt(double a, int dir)
{
    double s = std::sqrt(a);
    if (std::isnan(s) || std::isinf(s) || s == 0) {
        return s;
    }
    if (a < kTiny) {
        return (dir < 0) ? stepDown(s) : stepUp(s);
    }
    double r = std::fma(-s, s, a);  // a - s*s, exact : the sign of the error
    return (dir < 0) ? down(s, r) : up(s, r);
}
}  // namespace directed

inline double addDown(double a, double b)
{
    return directed::add(a, b, -1);
}
inline double addUp(double a, double b)
{
    return directed::add(a, b, 1);
}
inline double subDown(double a, double b)
{
    return directed::add(a, -b, -1);
}
inline double subUp(double a, double b)
{
    return directed::add(a, -b, 1);
}
inline double mulDown(double a, double b)
{
    return directed::mul(a, b, -1);
}
inline double mulUp(double a, double b)
{
    return directed::mul(a, b, 1);
}
inline double divDown(double a, double b)
{
    return directed::div(a, b, -1);
}
inline double divUp(double a, double b)
{
    return directed::div(a, b, 1);
}
inline double sqrtDown(double a)
{
    return directed::sqrt(a, -1);
}
inline double sqrtUp(double a)
{
    return directed::sqrt(a, 1);
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
            // a float-carried value : its bounds at the precision of the program,
            // outward ; a point is a constant of the program (or an exact result) and
            // stays a point, the float its literal gives
            if (fLSB < 0) {
                if (fLo == fHi) {
                    fLo = fHi = programBound(fLo, 0);
                } else {
                    fLo = programBound(fLo, -1);
                    fHi = programBound(fHi, 1);
                }
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
            if (x != std::floor(x)) {
                x = programBound(x, 0);
            }
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

/**
 * The bounds of a libm function, compensated : 2 ulps of the program's precision
 * outward, within the image [fmin, fmax] of the function (sin stays in [-1, 1], exp
 * stays >= 0), a bound of exactly 0 excepted. A point is left as it is : a function of
 * a constant is folded by the compiler and never calls the libm of the target.
 */
inline double ulpStep(double b, double dir)
{
    if (std::isnan(b) || std::isinf(b)) return b;
    int p = programPrecision();
    if (p == 1 || p == 4) return double(std::nextafter(float(b), float(dir)));
    return std::nextafter(b, dir);
}

/**
 * The bounds of a value stored in a FAUSTFLOAT zone (a slider, a bargraph read back) :
 * the zone is a float by default whatever the precision of the program, and the float
 * of a declared bound may pass it (in -double, the float of 1.30550981 is below the
 * minimum 1.30550981). Rounded outward to float : sound whether FAUSTFLOAT is a float
 * or a double. An integer value (lsb >= 0) is left as it is.
 */
inline interval zoneBounds(const interval& r)
{
    if (r.isEmpty() || r.lsb() >= 0) {
        return r;
    }
    return interval(floatBound(r.lo(), -1), floatBound(r.hi(), 1), r.lsb());
}

inline interval libmBounds(const interval& r, double fmin, double fmax)
{
    // an integer result (lsb >= 0) is computed in integers, never by the libm
    if (!libmCompensation() || r.isEmpty() || r.isconst() || r.lsb() >= 0) return r;
    // a bound of exactly 0 stays : the C standard (annex F) makes the libm exact there
    // (sin(+-0) = +-0, tan(0) = 0, log(1) = 0, pow(0, y) = 0...), and a bound of 0 comes
    // from such an exact point
    double lo = r.lo(), hi = r.hi();
    for (int k = 0; k < 2; k++) {
        if (lo != 0) lo = ulpStep(lo, -HUGE_VAL);
        if (hi != 0) hi = ulpStep(hi, HUGE_VAL);
    }
    if (r.lo() >= fmin) lo = std::max(lo, fmin);
    if (r.hi() <= fmax) hi = std::min(hi, fmax);
    return interval(lo, hi, r.lsb());
}

}  // namespace itv
