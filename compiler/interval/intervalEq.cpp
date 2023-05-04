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
// Interval Eq
// interval Eq(const interval& x, const interval& y);
// void testEq();

static double myEq(double x, double y)
{
    return (x == y);
}

interval interval_algebra::Eq(const interval& x, const interval& y)
{
    // boolean value => precision 0
    if (x.isEmpty() || y.isEmpty()) return interval{};
    if (x.lo() == x.hi() && x.lo() == y.lo() && x.lo() == y.hi()) return singleton(1,0);
    if (x.hi() < y.lo() || x.lo() > y.hi()) return singleton(0,0);
    return interval{0, 1, 0};
}

void interval_algebra::testEq()
{
    /* check("test algebra Eq", Eq(interval(5), interval(5)), interval(1));
    check("test algebra Eq", Eq(interval(2, 5), interval(0, 1)), interval(0));
    check("test algebra Eq", Eq(interval(-1, 1), interval(0, 10)), interval(0, 1));*/

    analyzeBinaryMethod(10, 200, "Eq", interval(-1, 1, 0), interval(-1, 1, 0), myEq, &interval_algebra::Eq);
    analyzeBinaryMethod(10, 200, "Eq", interval(-10, 10, 0), interval(-10, 10, 0), myEq, &interval_algebra::Eq);
    analyzeBinaryMethod(10, 20000, "Eq", interval(-1, 1, -2), interval(-1, 1, -2), myEq, &interval_algebra::Eq);
}
}  // namespace itv
