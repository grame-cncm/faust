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
// Interval inverse

static double inv(double x)
{
    if (x==0)
        return HUGE_VAL;
    return 1/x;
}

interval interval_algebra::Inv(const interval& x) const
{
    if (x.isEmpty()) {
        return {};
    }

    int sign = signMaxValAbs(x);
    double v = maxValAbs(x); // precision is computed at the bound with the highest absolute value

    int precision = exactPrecisionUnary(inv, v, sign*pow(2, x.lsb()));

    if ((x.hi() < 0) || (x.lo() >= 0)) {
        return {1.0 / x.hi(), 1.0 / x.lo(), precision};
    }
    if (x.hi() == 0 && x.lo() < 0) {
        return {-HUGE_VAL, 1.0 / x.lo(), precision};
    }
    if (x.lo() == 0 && x.hi() > 0) {
        return {1/x.hi(), HUGE_VAL, precision};
    }
    return {-HUGE_VAL, HUGE_VAL, precision};
}

void interval_algebra::testInv() const
{
    /* check("test algebra Inv", Inv(interval(-16, -4)), interval(-1. / 4., -1. / 16.));
    check("test algebra Inv", Inv(interval(4, 16)), interval(1.0 / 16, 0.25));
    check("test algebra Inv", Inv(interval(0, 10)), interval(0.1, +HUGE_VAL));
    check("test algebra Inv", Inv(interval(-10, 0)), interval(-HUGE_VAL, -0.1));
    check("test algebra Inv", Inv(interval(-20, +20)), interval(-HUGE_VAL, +HUGE_VAL));
    check("test algebra Inv", Inv(interval(0, 0)), interval(+HUGE_VAL, +HUGE_VAL));*/

    analyzeUnaryMethod(10, 2000, "inv", interval(-16, -4, -5), inv, &interval_algebra::Inv);
    analyzeUnaryMethod(10, 2000, "inv", interval(4, 16, -5), inv, &interval_algebra::Inv);
    analyzeUnaryMethod(10, 2000, "inv", interval(0, 10, -5), inv, &interval_algebra::Inv);
    analyzeUnaryMethod(10, 2000, "inv", interval(-10, 0, -5), inv, &interval_algebra::Inv);
    analyzeUnaryMethod(10, 2000, "inv", interval(-20, 20, -5), inv, &interval_algebra::Inv);
    analyzeUnaryMethod(10, 2000, "inv", interval(0, 0, -5), inv, &interval_algebra::Inv);
    // analyzeUnaryMethod(10, 2000, "inv", interval(-10, 0, -5), inv, &interval_algebra::Inv);
}
}  // namespace itv
