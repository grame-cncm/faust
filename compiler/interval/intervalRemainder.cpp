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
#include <algorithm>
#include <cmath>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Remainder
// interval Remainder(const interval& x, const interval& y);
// void testRemainder();

interval interval_algebra::Remainder(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }

    // IEEE remainder: x - n*y with n = rint(x/y), ties to even. The result lies in
    // [-|y|/2, +|y|/2] (both ends achievable at exact half-quotients), its magnitude
    // never exceeds |x|, and when |x| provably stays below HALF the smallest nonzero
    // divisor magnitude the quotient is 0 and remainder(x, y) = x exactly.
    const double m = std::max(std::fabs(y.lo()), std::fabs(y.hi()));
    if (m == 0) {
        return empty();  // y == [0, 0] : remainder(x, 0) is NaN, no value to describe
    }
    const double mmin = (y.lo() > 0) ? y.lo() : ((y.hi() < 0) ? -y.hi() : 0.0);
    const double xmax = std::max(std::fabs(x.lo()), std::fabs(x.hi()));
    if (mmin > 0 && xmax < mmin / 2) {
        return x;
    }
    const double b = std::min(xmax, m / 2);
    return {-b, b, std::min(x.lsb(), y.lsb())};
}

void interval_algebra::testRemainder()
{
    checkExact("remainder band", Remainder(interval(0, 100, 0), interval(2, 2, 0)),
               interval(-1, 1, 0));
    checkExact("remainder identity", Remainder(interval(3, 3, 0), interval(8, 8, 0)),
               interval(3, 3, 0));
    checkExact("remainder |x| clamp", Remainder(interval(-5, 5, 0), interval(4, 4, 0)),
               interval(-2, 2, 0));
    analyzeBinaryMethod(10, 10000, "remainder", interval(0, 100, -5), interval(1, 10, -5),
                        std::remainder, &interval_algebra::Remainder);
}
}  // namespace itv
