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
#include <climits>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"
#include "directed_rounding.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval substraction

// Numeric kernel: the values of the program's subtraction, its bounds rounded to nearest
// as the program rounds them (see numericAdd). The existing int32 wrapping and other
// precision paths remain.
interval interval_algebra::numericSub(const interval& xIn, const interval& yIn) const
{
    const auto [x, y] = detail::int32Operands(xIn, yIn);
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }

    if (detail::hasInt32Bounds(x) && detail::hasInt32Bounds(y)) {
        const int xlo = (int)x.lo();
        const int xhi = (int)x.hi();
        const int ylo = (int)y.lo();
        const int yhi = (int)y.hi();

        double lo = x.lo() - y.hi();
        double hi = x.hi() - y.lo();

        // the exact bounds, in double, beyond the int32 range : the operation may wrap
        const bool overflow = lo < (double)INT_MIN || hi > (double)INT_MAX;

        // if there is a discontinuity by the lower end of integers
        if ((lo <= (double)INT_MIN - 1) && (hi >= (double)INT_MIN)) {
            return interval((double)INT_MIN, (double)INT_MAX, std::min(x.lsb(), y.lsb()))
                .withOverflow();
        }

        // if there is a discontinuity by the higher end of integers
        if ((lo <= (double)INT_MAX) && (hi >= (double)INT_MAX + 1)) {
            return interval((double)INT_MIN, (double)INT_MAX, std::min(x.lsb(), y.lsb()))
                .withOverflow();
        }

        // no wrapping, or a certain one : the bounds shifted by 2^32 (-fwrapv)
        return interval((double)(xlo - yhi), (double)(xhi - ylo), std::min(x.lsb(), y.lsb()))
            .withOverflow(overflow);
    }

    if (detail::usesNativeBounds()) {
        const interval a = detail::floatingOperand(x), b = detail::floatingOperand(y);
        const double lo = detail::nearestSum(a.lo(), -b.hi(), detail::Direction::Down);
        const double hi = detail::nearestSum(a.hi(), -b.lo(), detail::Direction::Up);
        // An indeterminate infinite corner must not erase numeric interior values.
        if (std::isnan(lo) || std::isnan(hi)) return {-HUGE_VAL, HUGE_VAL, -24};
        return {lo, hi, detail::floatingLSB(std::min(x.lsb(), y.lsb()))};
    }
    return {x.lo() - y.hi(), x.hi() - y.lo(), std::min(x.lsb(), y.lsb())};
}
}  // namespace itv
