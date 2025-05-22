/* Copyright 2023 Yann ORLAREY
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

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Acos
// interval Acos(const interval& x);
// void testAcos();

interval interval_algebra::Abs(const interval& x)
{
    if (x.isEmpty()) {
        return empty();
    }

    // precision stays the same
    if (x.lo() >= 0) {
        return x;
    }

    // integer overflowing
    if ((x.lsb() >= 0) && (x.lo() <= (double)INT_MIN)) {
        double lo = (x.hi() >= 0) ? 0 : std::min(std::abs(x.hi()), (double)INT_MAX);
        return {lo, (double)INT_MAX, x.lsb()};
    }
    if (x.hi() <= 0) {
        return {-x.hi(), -x.lo(), x.lsb()};
    }

    return {0, std::max(std::abs(x.lo()), std::abs(x.hi())), x.lsb()};
}

void interval_algebra::testAbs()
{
    std::cout << "Testing abs on finite intervals" << std::endl;
    analyzeUnaryMethod(
        10, 10000, "abs", interval(-10, 10, 0), [](double x) { return std::abs(x); },
        &interval_algebra::Abs);
    analyzeUnaryMethod(
        10, 10000, "abs", interval(-10, 10, -15), [](double x) { return std::abs(x); },
        &interval_algebra::Abs);

    std::cout << "Testing abs on intervals with limit bounds" << std::endl;
    check("abs", Abs(interval(INT_MIN, INT_MIN, 0)), interval(INT_MAX, INT_MAX, 0));
    check("abs", Abs(interval(INT_MIN, -10, 0)), interval(10, INT_MAX, 0));
    check("abs", Abs(interval(INT_MIN, 10, 0)), interval(0, INT_MAX, 0));
    check("abs", Abs(interval(-10, INT_MAX, 0)), interval(0, INT_MAX, 0));

    check("abs", Abs(interval(INT_MIN, INT_MIN, 5)), interval(INT_MAX, INT_MAX, 5));
    check("abs", Abs(interval(INT_MIN, INT_MIN, -5)),
          interval(-(float)INT_MIN, -(float)INT_MIN, -5));
}
}  // namespace itv
