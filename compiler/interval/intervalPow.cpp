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
 */
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <limits>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"
#include "directed_rounding.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Pow
// interval Pow(const interval& x, const interval& y);
// void testPow();

static const interval domainx = {0, HUGE_VAL, 0};

static interval fullIntegerRange()
{
    return {static_cast<double>(INT32_MIN), static_cast<double>(INT32_MAX), 0};
}

static bool integerPowerMayWrap(const interval& x, int exponent)
{
    if (exponent <= 0) {
        return false;
    }
    if ((x.lo() < INT32_MIN) || (x.hi() > INT32_MAX)) {
        return true;
    }

    double magnitude = std::max(std::abs(x.lo()), std::abs(x.hi()));
    if (magnitude <= 1.0) {
        return false;
    }

    // Conservatively consider 2^31 a possible wrap. The exceptional value
    // INT32_MIN for an odd power of a negative singleton is deliberately not
    // special-cased here: returning the full range remains sound.
    if (programPrecision() == 2) {
        // Round the magnitude upward before comparing with the wrap threshold;
        // an approximate logarithm must not turn a possible wrap into a proof.
        return detail::directedBinary(detail::BinaryOp::Pow, magnitude, exponent,
                                      detail::Direction::Up) >= 2147483648.0;
    }
    return static_cast<double>(exponent) * std::log2(magnitude) >= 31.0;
}

static int multiplyLSB(int lsb, int exponent)
{
    int64_t value = static_cast<int64_t>(lsb) * static_cast<int64_t>(exponent);
    return static_cast<int>(std::clamp<int64_t>(value, std::numeric_limits<int>::min() + 1LL,
                                                std::numeric_limits<int>::max()));
}

/**
 * @brief Interval elevated to an integer power
 */
static interval ipow(const interval& x, int k)
{
    assert(k >= 0);
    if (k == 0) {
        return interval{1, 1, 0};
    }

    // explicit expression because passing an anonymous function to exactPrecisionUnary is
    // complicated
    int precision = multiplyLSB(x.lsb(), k);  // if x contains 0: finest precision is attained in 0
    if (!x.hasZero()) {
        double v    = minValAbs(x);
        int    sign = signMinValAbs(x);
        double logMagnitude = static_cast<double>(k) * std::log2(std::abs(v));
        double logDelta     = 0;

        double u     = pow(2, x.lsb());  // ulp
        double delta = std::abs(std::pow(1 + sign * u / v, k) - 1);
        if (delta == 0) {  // in case of u << x
            logDelta = std::log2(k) + x.lsb() - std::log2(std::abs(v));
            // (1 + u/v)^k - 1 ≃ k*u/v if u/v is very small
        } else {
            logDelta = std::log2(delta);
        }

        // Round only once. Truncating log2(|v|) before combining the terms can
        // make the result one or more bits too coarse when |v| < 1.
        const double estimate = std::floor(logMagnitude + logDelta);
        // A huge exponent or a subnormal base can put this metadata estimate
        // outside int. Preserve a conservative grid fallback without an UB cast.
        if (std::isfinite(estimate) && estimate > INT_MIN && estimate <= INT_MAX)
            precision = static_cast<int>(estimate);
    }

    if ((k & 1) == 0) {
        // k is even
        if (programPrecision() == 2) {
            return {x.hasZero() ? 0 : std::min(
                        detail::directedBinary(detail::BinaryOp::Pow, x.lo(), k, detail::Direction::Down),
                        detail::directedBinary(detail::BinaryOp::Pow, x.hi(), k, detail::Direction::Down)),
                    std::max(detail::directedBinary(detail::BinaryOp::Pow, x.lo(), k, detail::Direction::Up),
                             detail::directedBinary(detail::BinaryOp::Pow, x.hi(), k, detail::Direction::Up)), precision};
        }
        double z0 = std::pow(x.lo(), k);
        double z1 = std::pow(x.hi(), k);
        return {
            x.hasZero()
                ? 0
                : std::min(z0,
                           z1),  // 0 is in the output interval only if it is in the input interval
            std::max(z0, z1), precision};
    }

    // k is odd
    if (programPrecision() == 2) {
        return {detail::directedBinary(detail::BinaryOp::Pow, x.lo(), k, detail::Direction::Down),
                detail::directedBinary(detail::BinaryOp::Pow, x.hi(), k, detail::Direction::Up), precision};
    }
    return {std::pow(x.lo(), k), std::pow(x.hi(), k), precision};
}

/**
 * @brief Interval elevated to an interval power
 */
interval interval_algebra::numericfPow(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }

    assert(x.lo() > 0);
    // x all positive
    return Exp(Mul(y, Log(x)));
}

interval interval_algebra::numericiPow(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }

    int      y0 = std::max(0, saturatedIntCast(y.lo()));
    int      y1 = std::max(0, saturatedIntCast(y.hi()));

    // Faust integers are 32-bit values and their intended arithmetic wraps
    // modulo 2^32. Once a wrap is possible, the current interval domain cannot
    // represent the resulting disjoint set precisely, so use a sound envelope.
    if ((x.lsb() >= 0) && (y.lsb() >= 0) && integerPowerMayWrap(x, y1)) {
        return fullIntegerRange();
    }

    interval z  = ipow(x, y0);
    if (y1 > y0) {
        // we have more than one integer exponent
        z = reunion(z, ipow(x, y0 + 1));
        z = reunion(z, ipow(x, y1 - 1));
        z = reunion(z, ipow(x, y1));

        // Every fixed-point input is n*2^l. For l < 0, all powers lie on
        // the finest grid 2^(l*y1). For l >= 0, they share the coarsest
        // factor 2^(l*y0). Both bounds also cover differences between
        // results obtained with distinct exponents.
        int gridExponent = (x.lsb() < 0) ? y1 : y0;
        int commonGridLSB = multiplyLSB(x.lsb(), gridExponent);
        z = interval(z.lo(), z.hi(), std::min(z.lsb(), commonGridLSB));
    }
    return z;
}

// Numeric kernel: numeric power image. Float/double floating powers round outward; negative
// bases use integer exponents by parity. The existing nonnegative integer-power
// path retains wrapping and LSB estimates. Validity is attached by the public transfer.
interval interval_algebra::numericPowBounds(const interval& xIn, const interval& yIn) const
{
    const auto [x, y] = detail::int32Operands(xIn, yIn);
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }

    if (detail::hasInt32Bounds(x) && detail::hasInt32Bounds(y)) {
        return iPow(x, y);
    }

    // Float pow is a single target-libm operation, not rounded exp(y*log(x)).
    // Use the certified scalar reference and narrow its bounds outward once.
    if (programPrecision() == 1) return detail::doublePowBounds(x, y);

    if (programPrecision() == 2) {
        // Preserve the established grid estimate for bounded integer exponents;
        // their endpoint powers are now themselves evaluated with outward arithmetic.
        if (y.lsb() >= 0 && y.lo() >= 0 && y.hi() <= INT32_MAX &&
            std::isfinite(x.lo()) && std::isfinite(x.hi())) {
            const interval result = iPow(x, y);
            return {result.lo(), result.hi(), detail::floatingLSB(result.lsb())};
        }
        return detail::doublePowBounds(x, y);
    }

    interval z  = empty();
    // The nonzero domain separators must survive rounding to the program's
    // precision: a double subnormal rounds to zero in single precision and would
    // admit zero into fPow, whose logarithmic decomposition requires x > 0.
    const double smallest = programPrecision() == 1
                                ? double(std::numeric_limits<float>::denorm_min())
                                : std::numeric_limits<double>::denorm_min();
    interval     xp       = intersection(x, interval{smallest, HUGE_VAL, 0});
    interval     xn       = intersection(x, interval{-HUGE_VAL, -smallest, 0});

    if (y.hasZero()) {
        // x^0 = 1
        z = reunion(z, interval(1, 1, 0));
    }
    if (x.hasZero()) {
        // 0^y = 0
        z = reunion(z, interval(0, 0, 0));
    }
    if (!xp.isEmpty()) {
        z = reunion(z, fPow(xp, y));
    }
    if (!xn.isEmpty()) {
        z = reunion(z, iPow(xn, y));
    }
    return z;
}

static double myfPow(double x, double y)
{
    return std::pow(x, y);
}

static double myiPow(double x, double y)
{
    return std::pow(x, int(y));
}

static double myiPow32(double x, double y)
{
    uint32_t base     = static_cast<uint32_t>(static_cast<int32_t>(x));
    uint32_t exponent = static_cast<uint32_t>(std::max(0, static_cast<int>(y)));
    uint32_t result   = 1;

    while (exponent != 0) {
        if ((exponent & 1u) != 0) {
            result *= base;
        }
        exponent >>= 1u;
        if (exponent != 0) {
            base *= base;
        }
    }

    int64_t signedResult = (result <= static_cast<uint32_t>(INT32_MAX))
                               ? static_cast<int64_t>(result)
                               : static_cast<int64_t>(result) - (int64_t{1} << 32);
    return static_cast<double>(signedResult);
}

void interval_algebra::testPow()
{
    /* analyzeBinaryMethod(10, 2000000, "iPow^2", interval(-100, 100), interval(2), myiPow,
    &interval_algebra::iPow); analyzeBinaryMethod(10, 2000000, "iPow^3", interval(-100, 100),
    interval(3), myiPow, &interval_algebra::iPow); analyzeBinaryMethod(10, 2000000, "iPow^2",
    interval(-1, 1), interval(2), myiPow, &interval_algebra::iPow); analyzeBinaryMethod(10, 2000000,
    "iPow^3", interval(-1, 1), interval(3), myiPow, &interval_algebra::iPow);*/

    analyzeBinaryMethod(5, 2000000, "iPow2", interval(-100, 100, 0), interval(0, 200, 0), myiPow32,
                        &interval_algebra::iPow);
    analyzeBinaryMethod(5, 2000000, "iPow2", interval(-100, 100, -5), interval(0, 200, 0), myiPow,
                        &interval_algebra::iPow);
    analyzeBinaryMethod(5, 2000000, "iPow2", interval(-100, 100, 0), interval(0, 200, -5), myiPow,
                        &interval_algebra::iPow);

    analyzeBinaryMethod(5, 2000000, "iPow2", interval(-1, 1, 0), interval(1, 3, 0), myiPow32,
                        &interval_algebra::iPow);
    analyzeBinaryMethod(5, 2000000, "iPow2", interval(-1, 1, -5), interval(1, 3, 0), myiPow,
                        &interval_algebra::iPow);
    analyzeBinaryMethod(5, 2000000, "iPow2", interval(-1, 1, 0), interval(1, 3, -5), myiPow,
                        &interval_algebra::iPow);

    analyzeBinaryMethod(5, 2000000, "iPow2", interval(-1, 1), interval(1, 10), myiPow,
                        &interval_algebra::iPow);
    analyzeBinaryMethod(5, 2000000, "iPow2", interval(-1, 1), interval(1, 10), myiPow,
                        &interval_algebra::iPow);
    analyzeBinaryMethod(5, 2000000, "iPow2", interval(-1, 1), interval(1, 10), myiPow,
                        &interval_algebra::iPow);

    /* analyzeBinaryMethod(10, 2000000, "fPow2", interval(1, 1000), interval(-10, 10), myfPow,
    &interval_algebra::fPow); analyzeBinaryMethod(10, 2000000, "fPow2", interval(0.001, 1),
    interval(-10, 10), myfPow, &interval_algebra::fPow); analyzeBinaryMethod(10, 2000000, "fPow2",
    interval(0.001, 10), interval(-200, 200), myfPow, &interval_algebra::fPow);*/
}
}  // namespace itv
