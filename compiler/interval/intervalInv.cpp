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
// Interval inverse

static double inv(double x)
{
    if (x == 0) {
        return HUGE_VAL;
    }
    return 1 / x;
}

// Numeric kernel: reciprocal bounds and their LSB estimate; empty stays empty.
// Zero gives both signed infinities in float/double (signed zero is not tracked). Float/double reciprocal endpoints
// round outward; LSB remains an estimate.
interval interval_algebra::numericInv(const interval& input) const
{
    const interval x = detail::floatingOperand(input);
    if (x.isEmpty()) {
        return empty();
    }
    if (x.isZero()) {
        // 1/+0 = +inf, 1/-0 = -inf : the zeros the interval holds give their infinities
        if (detail::usesNativeBounds()) {
            return {std::signbit(x.lo()) ? -HUGE_VAL : HUGE_VAL, std::signbit(x.hi()) ? -HUGE_VAL : HUGE_VAL, -24};
        }
        return {HUGE_VAL, HUGE_VAL, -24};
    }

    if (detail::usesNativeBounds()) {
        const int lsb = std::min(x.lsb(), -24);
        if (x.lo() < 0 && x.hi() > 0) return {-HUGE_VAL, HUGE_VAL, lsb};
        // an upper bound +0 holds +0 (1/+0 = +inf), a lower bound -0 holds -0 (1/-0 = -inf) ;
        // a zero bound of the other sign holds only that zero, whose infinity is a bound
        if (x.lo() < 0 && x.hi() == 0 && !std::signbit(x.hi())) return {-HUGE_VAL, HUGE_VAL, lsb};
        if (x.lo() == 0 && x.hi() > 0 && std::signbit(x.lo())) return {-HUGE_VAL, HUGE_VAL, lsb};
        return {x.hi() == 0 ? -HUGE_VAL : detail::directedBinary(
                    detail::BinaryOp::Div, 1, x.hi(), detail::Direction::Down),
                x.lo() == 0 ? HUGE_VAL : detail::directedBinary(
                    detail::BinaryOp::Div, 1, x.lo(), detail::Direction::Up), lsb};
    }

    int    sign = signMaxValAbs(x);
    double v = maxValAbs(x);  // precision is computed at the bound with the highest absolute value

    // if v is infinite, this means that images of interval elements will get closer and closer
    // but since we're writing the fixed-point numbers on at most 31 bits of MSB
    // we can take the max number to be an integer bound
    // and this one will give a finite precision, unlike a floating-point infinity
    if (std::isinf(v)) {
        v = (sign == -1) ? INT_MAX : INT_MIN;
    }

    int precision = exactPrecisionUnary(inv, v, sign * std::pow(2, x.lsb()));
    if ((precision == INT_MIN) || taylor_lsb) {
        precision =
            std::floor(x.lsb() - 2 * std::log2(std::abs(v)));  // 1/(x+u) - 1/x = -u/x^2 + o(u)
    }

    // precision = std::max(precision, -31);

    if ((x.hi() < 0) || (x.lo() >= 0)) {
        return {1.0 / x.hi(), 1.0 / x.lo(), precision};
    }
    if (x.hi() == 0 && x.lo() < 0) {
        return {-HUGE_VAL, 1.0 / x.lo(), precision};
        // normally, we don't divide by 0
        // so the bounds of the image interval are not infinity but 1/ulp
        // return {-pow(2, -x.lsb()), 1.0 / x.lo(), precision};
    }
    if (x.lo() == 0 && x.hi() > 0) {
        return {1 / x.hi(), HUGE_VAL, precision};
        // return {1 / x.hi(), pow(2, -x.lsb()), precision};
    }
    return {-HUGE_VAL, HUGE_VAL, precision};
    // return {-pow(2, -x.lsb()), pow(2, -x.lsb()), precision};
}
}  // namespace itv
