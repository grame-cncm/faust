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
// Interval Sqrt
// interval Sqrt(const interval& x);

static const interval SqrtDomain(0, HUGE_VAL, 0);

// Numeric kernel: square-root bounds over x intersected with [0, +inf], with an LSB
// estimate. An empty domain yields empty; a zero-only domain yields exact zero.
// Float/double bounds round outward independently of the host libm and rounding mode.
interval interval_algebra::numericSqrt(const interval& x) const
{
    if (detail::usesNativeBounds()) {
        // sqrt(-0) is -0 and sqrt(+0) is +0 : the zeros of the operand are those of the result
        const interval r = detail::doubleUnaryBounds(detail::UnaryOp::Sqrt, x);
        if (r.isEmpty()) return r;
        auto holds = [&](double z) { return leTotal(x.lo(), z) && leTotal(z, x.hi()); };
        const double lo = holds(-0.0) ? minTotal(r.lo(), -0.0) : r.lo();
        const double hi = holds(0.0) ? maxTotal(r.hi(), 0.0) : r.hi();
        return interval(lo, hi, r.lsb(), r.mayBeInvalid());
    }
    interval i = intersection(SqrtDomain, x);

    if (i.isEmpty()) {
        return empty();
    }
    // There is no preceding nonnegative sample at the exact zero point.
    if (i.isZero()) {
        return interval(0);
    }
    /* if (i.lo() < 0) {
        return {};  // sqrt of negative numbers
    }*/

    // lowest slope at the highest bound of the interval
    int precision = exactPrecisionUnary(sqrt, i.hi(), -std::pow(2, i.lsb()));
    if ((precision == INT_MIN) || taylor_lsb) {
        if (i.hi() == 0) {
            precision = std::floor(i.lsb() / 2);
        } else {
            precision = std::floor(i.lsb() - std::log2(i.hi()) -
                                   1.);  // sqrt(x+u) - sqrt(x) = 1/2 u/sqrt(x)
        }
    }

    return {std::sqrt(i.lo()), std::sqrt(i.hi()), precision};
}
}  // namespace itv
