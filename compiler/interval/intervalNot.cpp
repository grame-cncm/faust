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
// Interval Not
// interval Not(const interval& x) const;
// void testNot() const;

interval interval_algebra::Not(const interval& x) const
{
    if (x.isEmpty()) return x;
    int x0 = saturatedIntCast(x.lo());
    int x1 = saturatedIntCast(x.hi());

    int z0 = INT32_MAX;
    int z1 = INT32_MIN;

    for (int i = x0; i <= x1; i++) {
        int z = ~i;
        if (z < z0) z0 = z;
        if (z > z1) z1 = z;
    }

    // the interval is made up of integer so no need to have a precision finer than 0
    // but take the precision of the original interval if it is even coarser
    int precision = std::max(0, x.lsb()); 

    return {double(z0), double(z1), precision};
}

static double myNot(double x)
{
    int a = saturatedIntCast(x);
    int b = ~a;
    return double(b);
}

void interval_algebra::testNot() const
{
    analyzeUnaryMethod(10, 1000, "not", interval(-10, -1), myNot, &interval_algebra::Not);
    analyzeUnaryMethod(10, 1000, "not", interval(10, 12), myNot, &interval_algebra::Not);
    analyzeUnaryMethod(10, 1000, "not", interval(-10, 12), myNot, &interval_algebra::Not);

    analyzeUnaryMethod(10, 1000, "not", interval(-10, -1, 5), myNot, &interval_algebra::Not);
    analyzeUnaryMethod(10, 1000, "not", interval(10, 12, 10), myNot, &interval_algebra::Not);
    analyzeUnaryMethod(10, 1000, "not", interval(-10, 12, 5), myNot, &interval_algebra::Not);
}
}  // namespace itv
