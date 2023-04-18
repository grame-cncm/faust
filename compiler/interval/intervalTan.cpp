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
#include <cmath>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Tan
// interval Tan(const interval& x) const;
// void testTan() const;

static double tanPi(double x)
{
    return tan(x * M_PI);
}

interval interval_algebra::Tan(const interval& x) const
{
    if (x.isEmpty()) {
        return x;
    }
    if (x.size() >= 1) { // spans asymptots and contains an integer
        return {-HUGE_VAL, HUGE_VAL, 
                exactPrecisionUnary(tanPi, ceil(x.lo()), pow(2, x.lsb())) // computes the precision at the first integer contained in the interval
                };
    }

    // normalize input interval between -0.5..0.5 (corresponding to -PI/2..PI/2)
    double   l = fmod(x.lo(), 1);  // fractional part of x.lo()
    interval i(l, l + x.size(), x.lsb());

    double v = 0;  // value at which the lowest slope is computed: 0 if present
    int sign = 1;

    if (i.lo() > 0) {
         v = i.lo();
    } else if (i.hi() < 0) {
         v = i.hi();
    }
    int precision = exactPrecisionUnary(tanPi, v, sign * pow(2, x.lsb()));

    if (i.has(0.5) or i.has(-0.5))  // asymptots at PI/2
        return {-HUGE_VAL, HUGE_VAL, precision};

    double a  = tanPi(i.lo());
    double b  = tanPi(i.hi());
    double lo = std::min(a, b);
    double hi = std::max(a, b);

    return {lo, hi, precision};
}

void interval_algebra::testTan() const
{
    analyzeUnaryMethod(20, 20000, "tan", interval(-0.5, 0.5, -2), tanPi, &interval_algebra::Tan);
    analyzeUnaryMethod(20, 20000, "tan", interval(-0.5, 0.5, -5), tanPi, &interval_algebra::Tan);
    analyzeUnaryMethod(20, 20000, "tan", interval(-0.5, 0.5, -10), tanPi, &interval_algebra::Tan);
    analyzeUnaryMethod(20, 20000, "tan", interval(-0.5, 0.5, -15), tanPi, &interval_algebra::Tan);
}
}  // namespace itv
