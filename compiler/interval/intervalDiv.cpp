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
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"
#include "directed_rounding.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval division

// Numeric kernel: enclose floating division with directly divided endpoints. Float/double
// bounds round outward; quad/fixed retain their previous evaluation.
// Empty operands yield empty; zero or an indeterminate infinite corner gives
// [-inf, +inf]. The LSB estimate remains separate from numeric bound inclusion.
interval interval_algebra::numericDiv(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }
    // an integer divisor beyond int32 has wrapped : any int32 value, zero included. A float
    // divisor whose only zero is a bound of known sign (+0 at the bottom, -0 at the top) is
    // divided by its corners : x / +0 and x / -0 are infinities of known signs.
    const bool signedZeroDivisor = detail::usesNativeBounds() && y.lsb() < 0 &&
                                   ((y.lo() == 0 && !std::signbit(y.lo()) && y.hi() >= 0) ||
                                    (y.hi() == 0 && std::signbit(y.hi()) && y.lo() <= 0));
    if (detail::int32Hull(y).hasZero() && !signedZeroDivisor) {
        return {-HUGE_VAL, HUGE_VAL, std::min({x.lsb(), y.lsb(), -24})};
    }

    if (detail::usesNativeBounds()) {
        const interval xFloat = detail::floatingOperand(x), yFloat = detail::floatingOperand(y);
        double lo = HUGE_VAL, hi = -HUGE_VAL;
        for (double numerator : {xFloat.lo(), xFloat.hi()}) {
            for (double denominator : {yFloat.lo(), yFloat.hi()}) {
                const double a = detail::directedBinary(detail::BinaryOp::Div, numerator,
                                                       denominator, detail::Direction::Down);
                const double b = detail::directedBinary(detail::BinaryOp::Div, numerator,
                                                       denominator, detail::Direction::Up);
                if (std::isnan(a) || std::isnan(b)) return {-HUGE_VAL, HUGE_VAL, -24};
                lo = minTotal(lo, a);
                hi = maxTotal(hi, b);
            }
        }
        return {lo, hi, std::min({x.lsb(), y.lsb(), -24})};
    }

    // Multiplication by a rounded reciprocal differs from a single division by
    // an ulp even for point operands. The four corners bound a zero-free quotient.
    auto quotient = [](double numerator, double denominator) {
        // Div is a floating operation even when the operands' LSB is nonnegative.
        // Evaluate single-precision endpoints as floats, including overflow.
        return programPrecision() == 1 ? double(float(numerator) / float(denominator))
                                       : numerator / denominator;
    };
    const double a = quotient(x.lo(), y.lo()), b = quotient(x.lo(), y.hi());
    const double c = quotient(x.hi(), y.lo()), d = quotient(x.hi(), y.hi());
    if (std::isnan(a) || std::isnan(b) || std::isnan(c) || std::isnan(d)) {
        return {-HUGE_VAL, HUGE_VAL, std::min({x.lsb(), y.lsb(), -24})};
    }
    // Keep the established precision estimate without using reciprocal bounds.
    const int precision = x.lsb() + Inv(y).lsb();
    return {std::min({a, b, c, d}), std::max({a, b, c, d}), precision};
}

double div(double x, double y)
{
    return x / y;
}
}  // namespace itv
