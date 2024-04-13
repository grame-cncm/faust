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
// Interval Lt
// interval Lt(const interval& x, const interval& y);
// void testLt();

static double myLt(double x, double y)
{
    return (x < y);
}

interval interval_algebra::Lt(const interval& x, const interval& y)
{
    return Gt(y, x);
}

void interval_algebra::testLt()
{
    /* check("test algebra Lt", Lt(interval(5), interval(6, 10)), interval(1));
    check("test algebra Lt", Lt(interval(2, 5), interval(0, 2)), interval(0));
    check("test algebra Lt", Lt(interval(-1, 1), interval(0, 10)), interval(0, 1)); */

    analyzeBinaryMethod(10, 200, "Lt", interval(-1, 1, 0), interval(-1, 1, 0), myLt, &interval_algebra::Lt);
    analyzeBinaryMethod(10, 200, "Lt", interval(-10, 10, 0), interval(-10, 10, 0), myLt, &interval_algebra::Lt);
    analyzeBinaryMethod(10, 2000, "Lt", interval(-10, 10), interval(-10, 10), myLt, &interval_algebra::Lt);    
}
}  // namespace itv
