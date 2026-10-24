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
// Interval Max
// interval Max(const interval& x);

// Numeric kernel: enclose maximum after target operand conversions.
// Empty stays empty; widened integers recover their signed hull.
// The result is floating exactly when either operand is floating.
namespace {
// min and max return their first operand between two zeros : a zero bound of the result
// takes every zero that either operand may hold
interval zeroBoundsOf(interval r, const interval& x, const interval& y)
{
    if (r.isEmpty()) return r;
    auto holds = [](const interval& i, double z) { return leTotal(i.lo(), z) && leTotal(z, i.hi()); };
    double lo = r.lo(), hi = r.hi();
    if (lo == 0 && (holds(x, -0.0) || holds(y, -0.0))) lo = -0.0;
    if (hi == 0 && (holds(x, 0.0) || holds(y, 0.0))) hi = 0.0;
    return interval(lo, hi, r.lsb(), r.mayBeInvalid());
}
}  // namespace

interval interval_algebra::numericMax(const interval& xInput, const interval& yInput) const
{
    // Compare target values after integer widening and any implicit float cast.
    const auto [x, y] = detail::comparisonOperands(xInput, yInput);
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }

    return zeroBoundsOf(interval{maxTotal(x.lo(), y.lo()), maxTotal(x.hi(), y.hi()),
            std::min(x.lsb(), y.lsb())}, x, y);  // the resulting interval should be as precise as the most
                                          // precise of the operands
}
}  // namespace itv
