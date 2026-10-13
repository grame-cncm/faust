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
// Interval Log10
// interval Log10(const interval& x);
// void testLog10();

// Numeric kernel: uncompensated base-10-log bounds over x intersected with [0, +inf].
// An empty domain yields empty; a zero-only domain yields the -inf point with
// default floating LSB, since a finite precision cannot be inferred there.
// Numeric kernel: numeric log10 image on its valid domain. In float/double,
// the native kernel encloses endpoints and extrema; quad/fixed retain
// their historical rule. LSB is an estimate; Validity is attached by the public transfer.
interval interval_algebra::numericLog10Bounds(const interval& x) const
{
    if (detail::usesNativeBounds()) return detail::doubleUnaryBounds(detail::UnaryOp::Log10, x);
    const interval i = intersection(interval(0, HUGE_VAL, 0), x);
    if (i.isEmpty()) {
        return empty();
    }
    // Check the domain before evaluating a precision at its singular endpoint.
    if (i.isZero()) {
        return {-HUGE_VAL, -HUGE_VAL, -24};
    }

    // lowest slope is at the highest bound of the interval
    int precision = exactPrecisionUnary(
        std::log10, i.hi(),
        -std::pow(2, i.lsb()));  // -pow because we take the FP number right before the higher bound
    if ((precision == INT_MIN) || taylor_lsb) {
        precision = floor(i.lsb() - (double)std::log2(std::abs(i.hi())) - std::log2(std::log(10)));
    }

    return {log10(i.lo()), log10(i.hi()), precision};
}

void interval_algebra::testLog10()
{
    analyzeUnaryMethod(10, 1000, "log10", interval(0, 10, 0), std::log10, &interval_algebra::Log10);
    analyzeUnaryMethod(10, 1000, "log10", interval(0, 10, -5), std::log10,
                       &interval_algebra::Log10);
    analyzeUnaryMethod(10, 1000, "log10", interval(0, 10, -10), std::log10,
                       &interval_algebra::Log10);
    analyzeUnaryMethod(10, 1000, "log10", interval(0, 10, -15), std::log10,
                       &interval_algebra::Log10);
    analyzeUnaryMethod(10, 1000, "log10", interval(0, 10, -20), std::log10,
                       &interval_algebra::Log10);

    // check("test algebra Log", Log10(interval(1, 10)), interval(std::log10(1), std::log10(10)));
    // check("test algebra Log", Log10(interval(0, 10)), interval(std::log10(0), std::log10(10)));
    // check("test algebra Log", Log10(interval(-10, 10)), interval(std::log10(0), std::log10(10)));
}
}  // namespace itv
