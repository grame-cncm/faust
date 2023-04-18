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
// Interval substraction

static double sub(double a, double b)
{
    return a - b;
}

interval interval_algebra::Sub(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return {};

    return {x.lo() - y.hi(), x.hi() - y.lo(), std::min(x.lsb(), y.lsb())};
}

void interval_algebra::testSub() const
{
    // check("test algebra Sub", Sub(interval(0, 100), interval(10, 500)), interval(-500, 90));
    analyzeBinaryMethod(10, 2000, "sub", interval(0, 10, 0), interval(0, 10, 0), sub, &interval_algebra::Sub);
    analyzeBinaryMethod(10, 2000, "sub", interval(0, 10, -5), interval(0, 10, 0), sub, &interval_algebra::Sub);
    analyzeBinaryMethod(10, 2000, "sub", interval(0, 10, -10), interval(0, 10, 0), sub, &interval_algebra::Sub);
    analyzeBinaryMethod(10, 2000, "sub", interval(0, 10, -15), interval(0, 10, 0), sub, &interval_algebra::Sub);
    analyzeBinaryMethod(10, 2000, "sub", interval(0, 10, 0), interval(0, 10, -10), sub, &interval_algebra::Sub);
    analyzeBinaryMethod(10, 2000, "sub", interval(0, 10, -5), interval(0, 10, -10), sub, &interval_algebra::Sub);
    analyzeBinaryMethod(10, 2000, "sub", interval(0, 10, -10), interval(0, 10, -10), sub, &interval_algebra::Sub);
    analyzeBinaryMethod(10, 2000, "sub", interval(0, 10, -15), interval(0, 10, -10), sub, &interval_algebra::Sub);
}
}  // namespace itv
