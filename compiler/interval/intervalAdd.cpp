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
// Interval addition

static double add(double x, double y)
{
    return x + y;
}

static double addint(double x, double y)
{
    return (int)x + (int)y;
}

// Numeric kernel: the values of the program's addition. Float/double floating bounds are
// the program's own sums of the operands' bounds, rounded to nearest (nearestSum) : the
// rounding is nondecreasing, so no program sum lies beyond them. A product the program may
// fuse into the sum keeps an outward bound (Mul), above both its exact and its rounded
// value. The existing int32 wrapping and other precision paths remain.
interval interval_algebra::numericAdd(const interval& xIn, const interval& yIn) const
{
    const auto [x, y] = detail::int32Operands(xIn, yIn);
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }

    if (detail::hasInt32Bounds(x) && detail::hasInt32Bounds(y)) {
        // if we're dealing with integers the interval has to wrap around 0
        const int xlo = (int)x.lo();
        const int xhi = (int)x.hi();
        const int ylo = (int)y.lo();
        const int yhi = (int)y.hi();

        // detect wrapping
        /* if (std::abs((double)xhi + (double)yhi) >= (double)INT_MAX
            || std::abs((double)xhi + (double)yhi) <= (double)INT_MIN
            || std::abs((double)xlo + (double)ylo) >= (double)INT_MAX
            || std::abs((double)xlo + (double)ylo) <= (double)INT_MIN)
            return {(double) INT_MIN, (double) INT_MAX, std::min(x.lsb(), y.lsb())};*/

        double lo = x.lo() + y.lo();
        double hi = x.hi() + y.hi();

        // if there is a discontinuity by the lower end of integers
        if ((lo <= (double)INT_MIN - 1) && (hi >= (double)INT_MIN)) {
            return {(double)INT_MIN, (double)INT_MAX, std::min(x.lsb(), y.lsb())};
        }

        // if there is a discontinuity by the higher end of integers
        if ((lo <= (double)INT_MAX) && (hi >= (double)INT_MAX + 1)) {
            return {(double)INT_MIN, (double)INT_MAX, std::min(x.lsb(), y.lsb())};
        }

        // if there is potential wrapping but no discontinuity
        return {(double)(xlo + ylo), (double)(xhi + yhi), std::min(x.lsb(), y.lsb())};
    }

    if (detail::usesNativeBounds()) {
        const interval a = detail::floatingOperand(x), b = detail::floatingOperand(y);
        const double lo = detail::nearestSum(a.lo(), b.lo(), detail::Direction::Down);
        const double hi = detail::nearestSum(a.hi(), b.hi(), detail::Direction::Up);
        // An indeterminate infinite corner must not erase numeric interior values.
        if (std::isnan(lo) || std::isnan(hi)) return {-HUGE_VAL, HUGE_VAL, -24};
        return {lo, hi, detail::floatingLSB(std::min(x.lsb(), y.lsb()))};
    }
    return {x.lo() + y.lo(), x.hi() + y.hi(),
            std::min(x.lsb(), y.lsb())};  // the result of an addition needs to be only as precise
                                          // as the most precise of the operands
}

void interval_algebra::testAdd()
{
    std::cout << "Testing add on regular intervals" << std::endl;
    check("test algebra Add", Add(interval(0, 100), interval(10, 500)), interval(10, 600));

    std::cout << "Testing add on positive intervals" << std::endl;
    analyzeBinaryMethod(5, 2000, "add", interval(0, 10, 0), interval(0, 10, 0), add,
                        &interval_algebra::Add);
    analyzeBinaryMethod(5, 2000, "add", interval(0, 10, -10), interval(0, 10, 0), add,
                        &interval_algebra::Add);
    analyzeBinaryMethod(5, 2000, "add", interval(0, 10, 0), interval(0, 10, -10), add,
                        &interval_algebra::Add);
    analyzeBinaryMethod(5, 2000, "add", interval(0, 10, -10), interval(0, 10, -10), add,
                        &interval_algebra::Add);

    std::cout << "Testing add on negative intervals" << std::endl;
    analyzeBinaryMethod(5, 2000, "add", interval(-10, 10, -5), interval(-10, 0, -5), add,
                        &interval_algebra::Add);
    analyzeBinaryMethod(5, 2000, "add", interval(-10, 0, -5), interval(-10, 0, -5), add,
                        &interval_algebra::Add);

    std::cout << "Testing add with wrapping" << std::endl;

    analyzeBinaryMethod(10, 2000, "add", interval(0, pow(2, 31), 0), interval(0, pow(2, 31), 0),
                        addint, &interval_algebra::Add);
    analyzeBinaryMethod(10, 2000, "add", interval((double)INT_MAX / 2, (double)INT_MAX, 0),
                        interval((double)INT_MAX / 2, (double)INT_MAX, 0), addint,
                        &interval_algebra::Add);
    analyzeBinaryMethod(10, 2000, "add", interval((double)INT_MIN, (double)INT_MIN / 2, 0),
                        interval((double)INT_MAX / 2, (double)INT_MAX, 0), addint,
                        &interval_algebra::Add);
    analyzeBinaryMethod(10, 2000, "add", interval((double)INT_MIN, (double)INT_MIN / 2, 0),
                        interval((double)INT_MIN, (double)INT_MIN / 2, 0), addint,
                        &interval_algebra::Add);
}
}  // namespace itv
