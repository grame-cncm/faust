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
// Interval Le
// interval Le(const interval& x, const interval& y);
// void testLe();

static double myLe(double x, double y)
{
    return (x <= y);
}

interval interval_algebra::Le(const interval& x, const interval& y)
{
    return Ge(y, x);
}

void interval_algebra::testLe()
{
    /* check("test algebra Le", Le(interval(5), interval(5)), interval(1));
    check("test algebra Le", Le(interval(2, 5), interval(0, 1)), interval(0));
    check("test algebra Le", Le(interval(-1, 1), interval(0, 10)), interval(0, 1));*/

    analyzeBinaryMethod(10, 200, "Le", interval(-1, 1, 0), interval(-1, 1, 0), myLe, &interval_algebra::Le);
    analyzeBinaryMethod(10, 200, "Le", interval(-10, 10, 0), interval(-10, 10, 0), myLe, &interval_algebra::Le);
    analyzeBinaryMethod(10, 2000, "Le", interval(-10, 10), interval(-10, 10), myLe, &interval_algebra::Le);
}
}  // namespace itv
