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
// Interval Atanh
// Calculates the inverse hyperbolic tangent of x; that is the value whose hyperbolic tangent is x.
// interval Atanh(const interval& x);

static const interval domain(std::nexttoward(-1, 0), std::nexttoward(1, 0),
                             0);  // interval ]-1,1[, precision 0

// Numeric kernel: numeric atanh image on its valid domain. In float/double,
// the native kernel encloses endpoints and extrema; quad/fixed retain
// their historical rule. LSB is an estimate; Validity is attached by the public transfer.
interval interval_algebra::numericAtanhBounds(const interval& x) const
{
    if (detail::usesNativeBounds()) return detail::doubleUnaryBounds(detail::UnaryOp::Atanh, x);
    interval i = intersection(domain, x);
    if (i.isEmpty()) {
        return empty();
    }

    double v         = minValAbs(x);
    double sign      = signMinValAbs(x);
    int    precision = exactPrecisionUnary(std::atanh, v, sign * std::pow(2, x.lsb()));

    if ((precision == INT_MIN) || taylor_lsb) {
        precision = std::floor(x.lsb() - (double)std::log2(1 - v * v));
    }

    return {atanh(i.lo()), atanh(i.hi()), precision};
}
}  // namespace itv
