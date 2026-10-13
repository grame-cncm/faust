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
#include "cxx_compat.hh"
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>

// #include "global"

// ***************************************************************************
//
//     An Interval is a (possibly empty) set of numbers approximated by two
//     boundaries. NaN boundaries encode an empty numeric part; a separate flag
//     records possible invalid execution, including a NaN or undefined conversion.
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
 * Public API: legacy target-libm compensation, enabled by default. The two-ULP
 * widening is a configurable assumption, not a universal error guarantee.
 * Float/double reference bounds use the native kernel independently of this setting;
 * quad/fixed retain the host libm. Disable only under an established target contract.
 */
inline bool& libmCompensation()
{
    static bool compensation = true;
    return compensation;
}

/**
 * Public API: round an explicitly known literal/conversion to program precision.
 * Float selects nearest-even independently of the host rounding mode, including
 * gradual underflow. Handle overflow before narrowing a finite double.
 * Double is unchanged. Computed/domain bounds must use programDirectedBound instead:
 * singleton shape alone does not identify a literal or prove exact arithmetic.
 */
inline double programBound(double b)
{
    if (programPrecision() != 1 || std::isnan(b) || std::isinf(b)) return b;
    // Nearest-even overflows only at the midpoint above max-finite. Avoid an
    // out-of-range C++ narrowing cast even below that midpoint.
    if (b > std::numeric_limits<float>::max())
        return b >= 0x1.ffffffp127 ? HUGE_VAL : double(std::numeric_limits<float>::max());
    if (b < -std::numeric_limits<float>::max())
        return b <= -0x1.ffffffp127 ? -HUGE_VAL : -double(std::numeric_limits<float>::max());
    const float rounded = float(b);
    if (double(rounded) == b) return b;
    // Any IEEE host rounding gives an adjacent float. Its neighbour brackets b;
    // the sum and midpoint of two adjacent binary32 values are exact in binary64.
    // Integer parity selects the even significand at a midpoint, without fenv changes.
    const float lower = double(rounded) < b ? rounded : std::nextafter(rounded, -INFINITY);
    const float upper = double(rounded) > b ? rounded : std::nextafter(rounded, INFINITY);
    const double midpoint = (double(lower) + double(upper)) * 0.5;
    if (b < midpoint) return double(lower);
    if (b > midpoint) return double(upper);
    return double((compat::bit_cast<uint32_t>(lower) & 1u) == 0 ? lower : upper);
}

/**
 * Public API: enclose an exact binary64 bound in program precision, downward for
 * a lower endpoint and upward for an upper endpoint. Float narrowing is corrected
 * by comparison and nextafter; exact floats stay unchanged. Overflow brackets the
 * finite real value between max-finite and infinity, and underflow between zero
 * and the least subnormal. Integer-looking floating bounds receive the same rule.
 * Double/quad/fixed are unchanged; IEEE conversion and gradual underflow are assumed.
 */
inline double programDirectedBound(double b, bool upper)
{
    if (programPrecision() != 1 || !std::isfinite(b)) return b;
    const double largest = std::numeric_limits<float>::max();
    if (b > largest) return upper ? HUGE_VAL : largest;
    if (b < -largest) return upper ? -largest : -HUGE_VAL;
    const float rounded = float(b);
    if ((upper && double(rounded) < b) || (!upper && double(rounded) > b))
        return double(std::nextafter(rounded, upper ? INFINITY : -INFINITY));
    return double(rounded);
}

/**
 * k ulps of the program's precision at the magnitude of [lo, hi] : the margin of a rule
 * that reasons on reals (the hull of a convex combination), whose float evaluation can
 * leave the hull by a few roundings. Elementary float/double operations use
 * directed bounds instead of this heuristic margin.
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
    bool   fMayBeInvalid{false};                         ///< independent of numeric bounds

   public:
    //-------------------------------------------------------------------------
    // constructors
    //-------------------------------------------------------------------------

    interval() = default;

    // Public API: construct a numeric enclosure and optional invalidity. NaN
    // endpoints describe an invalid-only value; use empty() for numeric bottom.
    interval(double n, double m, int lsb = -24, bool mayBeInvalid = false) noexcept
    {
        fMayBeInvalid = mayBeInvalid || std::isnan(n) || std::isnan(m);
        if (n == 0.0 && m == 0.0) {
            fLo  = 0.0;
            fHi  = 0.0;
            // Zero carries the requested nature and grid in every precision.
            // Otherwise a computed floating zero can turn a later operation into
            // int32 wrapping, or a delay can discard an integer signal's grid.
            fLSB = lsb == INT_MIN ? -24 : lsb;
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
            // A computed/domain point is not a literal: independently enclose
            // both endpoints, even when analyzer rounding collapsed them.
            if (fLSB < 0) {
                fLo = programDirectedBound(fLo, false);
                fHi = programDirectedBound(fHi, true);
            }
        }
    }

    explicit interval(double x) noexcept
    {
        // Exceptional points have no finite grid exponent. Avoid precision
        // inference on NaN/inf; a NaN point has no numeric value and is invalid.
        if (!std::isfinite(x)) {
            fLo = x;
            fHi = x;
            fMayBeInvalid = std::isnan(x);
            return;
        }
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
    // Public API: isEmpty() tests only numeric bottom; isValid() additionally
    // requires proven validity. Invalid-only and partially invalid values differ.
    bool isValid() const { return !isEmpty() && !fMayBeInvalid; }
    // Public API: true means an invalid execution is possible, not certain.
    bool mayBeInvalid() const { return fMayBeInvalid; }
    // Public API: monotonically add an alert without changing bounds or nature.
    // Passing false cannot erase an alert produced earlier in the computation.
    interval withInvalid(bool possible = true) const noexcept
    {
        interval result = *this;
        result.fMayBeInvalid = fMayBeInvalid || possible;
        return result;
    }
    // Public API: numeric bottom with no alert. NaN endpoints are storage
    // sentinels here, not injected NaN values; retain the requested nature.
    static interval numericEmpty(int lsb = 0) noexcept
    {
        interval result;
        result.fLo = result.fHi = NAN;
        result.fLSB = lsb;
        return result;
    }
    bool isUnbounded() const { return std::isinf(fLo) || std::isinf(fHi); }
    bool isBounded() const { return !isUnbounded(); }
    bool has(double x) const { return (fLo <= x) && (fHi >= x); }
    // An alerted numeric point also represents possible invalid execution, so
    // singleton predicates must not let a consumer fold away that possibility.
    bool is(double x) const { return !fMayBeInvalid && (fLo == x) && (fHi == x); }
    bool hasZero() const { return has(0.0); }
    bool isZero() const { return is(0.0); }
    bool isconst() const { return (fLo == fHi) && !std::isnan(fLo) && !fMayBeInvalid; }

    bool ispowerof2() const
    {
        if (!isconst() || fHi < 1 || fHi > INT_MAX) return false;
        auto n = int(fHi);
        return isconst() && ((n & (-n)) == n);
    }

    bool isbitmask() const
    {
        if (!isconst() || fHi < 0 || fHi >= INT_MAX) return false;
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
        // Numeric bottom has no grid magnitude. Avoid a NaN-to-int metadata
        // conversion; callers must inspect validity before using an empty format.
        if (isEmpty()) return 0;
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
            return fMayBeInvalid ? "[] + invalid" : "[]";
        } else {
            char buffer[64];
            snprintf(buffer, 63, "[%g, %g]", fLo, fHi);
            return std::string(buffer) + (fMayBeInvalid ? " + invalid" : "");
        }
    }
};

//-------------------------------------------------------------------------
// printing
//-------------------------------------------------------------------------

inline std::ostream& operator<<(std::ostream& dst, const interval& i)
{
    if (i.isEmpty()) {
        return dst << (i.mayBeInvalid() ? "empty() + invalid" : "empty()");
    } else {
        return dst << "interval(" << i.lo() << ',' << i.hi() << ',' << i.lsb() << ")"
                   << (i.mayBeInvalid() ? " + invalid" : "");
    }
}

//-------------------------------------------------------------------------
// set operations
//-------------------------------------------------------------------------

// Public API: numeric bottom, distinct from an invalid-only execution.
inline interval empty(int lsb = 0) noexcept
{
    return interval::numericEmpty(lsb);
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
    // Numeric refinement must not silently clear an existing validity alert.
    const bool invalid = i.mayBeInvalid() || j.mayBeInvalid();
    if (i.isEmpty()) {
        return i.withInvalid(invalid);
    } else if (j.isEmpty()) {
        return j.withInvalid(invalid);
    } else {
        double l = std::max(i.lo(), j.lo());
        double h = std::min(i.hi(), j.hi());
        int    p = std::min(i.lsb(),
                            j.lsb());  // precision of the intersection should be the finest of the two
        if (l > h) {
            return empty().withInvalid(invalid);
        } else {
            return {l, h, p, invalid};
        }
    }
}

inline interval reunion(const interval& i, const interval& j)
{
    const bool invalid = i.mayBeInvalid() || j.mayBeInvalid();
    if (i.isEmpty()) {
        return j.withInvalid(invalid);
    } else if (j.isEmpty()) {
        return i.withInvalid(invalid);
    } else {
        double l = std::min(i.lo(), j.lo());
        double h = std::max(i.hi(), j.hi());
        int    p =
            std::min(i.lsb(), j.lsb());  // precision of the reunion should be the finest of the two
        return {l, h, p, invalid};
    }
}

inline interval singleton(double x)
{
    if (!std::isfinite(x)) return {x, x, -24};
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
    return i.mayBeInvalid() == j.mayBeInvalid() &&
           ((i.isEmpty() && j.isEmpty()) || ((i.lo() == j.lo()) && (i.hi() == j.hi())));
}

// Public API: numeric and validity inclusion, independent of LSB. An alert can
// only be included in another alert; numeric bottom without an alert is bottom.
inline bool operator<=(const interval& i, const interval& j)
{
    if (i.mayBeInvalid() && !j.mayBeInvalid()) return false;
    if (i.isEmpty()) {
        return true;
    }
    if (j.isEmpty()) {
        return false;
    }
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
 * stays >= 0), a bound of exactly 0 excepted. A float/double singleton is not
 * automatically a folded constant, so it receives the target margin too.
 * Quad/fixed retain the historical singleton exemption. This margin is heuristic.
 */
inline double ulpStep(double b, double dir)
{
    if (std::isnan(b) || std::isinf(b)) return b;
    int p = programPrecision();
    if (p == 1 || p == 4) return double(std::nextafter(float(b), float(dir)));
    return std::nextafter(b, dir);
}

inline interval libmBounds(const interval& r, double fmin, double fmax)
{
    // A singleton alone is not evidence that Faust folded an operation. Float/double
    // references are certified independently; the legacy two-ULP target margin
    // still applies to singleton results unless they are explicitly integer.
    if (!libmCompensation() || r.isEmpty() || r.lsb() >= 0 ||
        (programPrecision() != 1 && programPrecision() != 2 && r.isconst())) return r;
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
    return interval(lo, hi, r.lsb(), r.mayBeInvalid());
}

}  // namespace itv
