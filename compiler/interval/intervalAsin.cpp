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
// Interval Asin
// Calculates the principal value of the arc sine of x; that is the value whose sine is x.
// the return value is in the range [-pi/2, pi/2].
// interval Asin(const interval& x);
// void testAsin();

static const interval domain(-1, 1, 0);  // this interval needs 0 digits of precision

interval interval_algebra::Asin(const interval& x)
{
    interval i = intersection(domain, x);
    if (i.isEmpty()) {
        return empty();
    }

    double v    = 0;  // value at which the min slope is attained, zero if it is present
    int    sign = 1;  // whether we compute the difference between f(v) and f(v+ε) or f(v-ε)
    if (!i.has(0)) {  // if zero is not present, it's the bound closer to zero
        v    = minValAbs(i);
        sign = signMinValAbs(i);
    }
    int precision = exactPrecisionUnary(std::asin, v, sign * std::pow(2, i.lsb()));

    if ((precision == INT_MIN) || taylor_lsb) {
        precision = std::floor(x.lsb() - (double)std::log2(1 - v * v) / 2);
    }

    return {std::asin(i.lo()), std::asin(i.hi()), precision};
}

void interval_algebra::testAsin()
{
    analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1, 0), std::asin, &interval_algebra::Asin);
    analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1, -5), std::asin, &interval_algebra::Asin);
    analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1, -10), std::asin, &interval_algebra::Asin);
    analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1, -15), std::asin, &interval_algebra::Asin);
    analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1, -20), std::asin, &interval_algebra::Asin);

    /* analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1, 30), std::asin,
    &interval_algebra::Asin); analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1, -35), std::asin,
    &interval_algebra::Asin); analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1, -40), std::asin,
    &interval_algebra::Asin); analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1, -45), std::asin,
    &interval_algebra::Asin); analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1, -50), std::asin,
    &interval_algebra::Asin);*/
}
}  // namespace itv
