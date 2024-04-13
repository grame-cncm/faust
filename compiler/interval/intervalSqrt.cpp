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
// Interval Sqrt
// interval Sqrt(const interval& x);
// void testSqrt();

static const interval SqrtDomain(0, HUGE_VAL, 0);

interval interval_algebra::Sqrt(const interval& x)
{
    interval i = intersection(SqrtDomain, x);

    if (i.isEmpty()) {
        return interval::empty();
    }
    /* if (i.lo() < 0) {
        return interval::empty();  // sqrt of negative numbers
    }*/

    // lowest slope at the highest bound of the interval
    int precision = exactPrecisionUnary(sqrt, i.hi(), -pow(2, i.lsb()));
    if (precision == INT_MIN or taylor_lsb) {
        if (i.hi() == 0) {
            precision = floor(i.lsb() / 2);
        } else {
            precision = floor(i.lsb() - log2(i.hi()) - 1);  // sqrt(x+u) - sqrt(x) = 1/2 u/sqrt(x)
        }
    }

    return {sqrt(i.lo()), sqrt(i.hi()), precision};
}

void interval_algebra::testSqrt()
{
    // analyzeUnaryMethod(10, 1000, "sqrt", interval(0, 10), sqrt, &interval_algebra::Sqrt);
    analyzeUnaryMethod(10, 1000, "sqrt", interval(0, 10, 0), sqrt, &interval_algebra::Sqrt);
    analyzeUnaryMethod(10, 1000, "sqrt", interval(0, 10, -5), sqrt, &interval_algebra::Sqrt);
    analyzeUnaryMethod(10, 1000, "sqrt", interval(0, 10, -10), sqrt, &interval_algebra::Sqrt);
    analyzeUnaryMethod(10, 1000, "sqrt", interval(0, 10, -15), sqrt, &interval_algebra::Sqrt);
    analyzeUnaryMethod(10, 1000, "sqrt", interval(0, 10, -20), sqrt, &interval_algebra::Sqrt);
}
}  // namespace itv
