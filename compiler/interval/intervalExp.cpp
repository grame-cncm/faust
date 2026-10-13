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
// Interval Exp
// interval Exp(const interval& x);
// void testExp();

// Numeric kernel: numeric exp image on its valid domain. In float/double,
// the native kernel encloses endpoints and extrema; quad/fixed retain
// their historical rule. LSB is an estimate; Validity is attached by the public transfer.
interval interval_algebra::numericExpBounds(const interval& x) const
{
    if (detail::usesNativeBounds()) return detail::doubleUnaryBounds(detail::UnaryOp::Exp, x);
    if (x.isEmpty()) {
        return empty();
    }

    // lowest slope is attained at the lowest boundary
    // int precision = exactPrecisionUnary(exp, x.lo(), pow(2, x.lsb()));
    double delta = std::exp(std::pow(2, x.lsb())) - 1;
    int    p1    = std::floor(x.lo() * std::log2(M_E));  // log2(exp(x.lo()))
    int    p2    = 0;
    if (delta == 0) {  // avoid absorption of 2^l into v
        p2 = x.lsb();  // exp(v) - 1 ≃ v if v very small, so delta2 ≃ pow(2, x.lsb())
    } else {
        p2 = std::floor((double)std::log2(delta));
    }
    int precision = p1 + p2;

    return {exp(x.lo()), exp(x.hi()), precision};
}

interval interval_algebra::numericExp10(const interval& x) const
{
    // Base-10 exponentiation is floating even for an integer exponent; otherwise
    // 10^10 would take the int32 wrapping path instead of the libm image.
    return Pow(FloatNum(10), FloatCast(x));
}

void interval_algebra::testExp()
{
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, 0), std::exp, &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -3), std::exp, &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -6), std::exp, &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -9), std::exp, &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -12), std::exp,
                       &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -15), std::exp,
                       &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -18), std::exp,
                       &interval_algebra::Exp);
}
}  // namespace itv
