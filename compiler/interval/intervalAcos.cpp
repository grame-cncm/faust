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

static const interval AcosDomain(-1, 1, 0);  // this interval needs 0 digits of precision

interval interval_algebra::Acos(const interval& x)
{
    interval i = intersection(AcosDomain, x);  // TODO: warn about interval violations
    if (i.isEmpty()) {
        return interval::empty();
    }

    double v = 0;  // value at which the min slope is attained, zero if it is present
    int sign = 1;  // whether we compute the difference between f(x) and f(x+ε) or f(x-ε), chosing the point that lies
                   // in the interval
    if (not i.has(0))  // if zero is not present, it's the bound closer to zero
    {
        v    = minValAbs(i);
        sign = signMinValAbs(i);
    }

    int precision = exactPrecisionUnary(acos, v, sign * pow(2, i.lsb()));

    if (precision == INT_MIN or taylor_lsb) {
        precision = floor(i.lsb() - (double)log2(1 - v * v) / 2);
    }

    return {acos(i.hi()), acos(i.lo()), precision};
}

void interval_algebra::testAcos()
{
    analyzeUnaryMethod(10, 1000, "acos", interval(-1, 1, -1), acos, &interval_algebra::Acos);
    analyzeUnaryMethod(10, 1000, "acos", interval(-1, 1, -5), acos, &interval_algebra::Acos);
    analyzeUnaryMethod(10, 1000, "acos", interval(-1, 1, -10), acos, &interval_algebra::Acos);
    analyzeUnaryMethod(10, 1000, "acos", interval(-1, 1, -15), acos, &interval_algebra::Acos);
    analyzeUnaryMethod(10, 1000, "acos", interval(-1, 1, -20), acos, &interval_algebra::Acos);

    // very fine input precision
    /* analyzeUnaryMethod(10, 1000, "acos", interval(-1, 1, -100), acos, &interval_algebra::Acos);
    analyzeUnaryMethod(10, 1000, "acos", interval(-1, -0.85, -100), acos, &interval_algebra::Acos);
    analyzeUnaryMethod(10, 1000, "acos", interval(0.85, 1, -100), acos, &interval_algebra::Acos);

    // out of bounds input interval
    analyzeUnaryMethod(10, 1000, "acos", interval(-2, 2, -20), acos, &interval_algebra::Acos);*/
}
}  // namespace itv