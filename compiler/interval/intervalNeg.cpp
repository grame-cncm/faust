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

namespace itv {
//------------------------------------------------------------------------------------------
// negation, invert sign of an interval

interval interval_algebra::Neg(const interval& x) const
{
    if (x.isEmpty()) {
        return empty();
    }

    if (x.lsb() >= 0) {  // integer negation wraps: -INT_MIN is INT_MIN again
        const int xlo = (int)x.lo();
        const int xhi = (int)x.hi();

        double lo = -x.hi();
        double hi = -x.lo();

        // if there is a discontinuity by the lower end of integers
        if ((lo <= (double)INT_MIN - 1) && (hi >= (double)INT_MIN)) {
            return {(double)INT_MIN, (double)INT_MAX, x.lsb()};
        }

        // if there is a discontinuity by the higher end of integers
        if ((lo <= (double)INT_MAX) && (hi >= (double)INT_MAX + 1)) {
            return {(double)INT_MIN, (double)INT_MAX, x.lsb()};
        }

        // if there is potential wrapping but no discontinuity
        return {(double)(-xhi), (double)(-xlo), x.lsb()};
    }

    return {-x.hi(), -x.lo(), x.lsb()};
}

void interval_algebra::testNeg()
{
    check("test algebra Neg", Neg(interval(-1, 1)), interval(-1, 1));
    check("test algebra Neg", Neg(interval(-10, 1)), interval(-1, 10));
}
}  // namespace itv
