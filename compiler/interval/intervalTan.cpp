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
// interval Tan(const interval& x);
// void testTan();

static double tanPi(double x)
{
    return std::tan(x * M_PI);
}

interval interval_algebra::Tan(const interval& x)
{
    if (x.isEmpty()) {
        return empty();
    }

    if (x.size() >= M_PI) {  // spans asymptotes and contains an integer multiple of pi
        // std::cout << "Spanning more than one period" << std::endl;
        int precision = exactPrecisionUnary(std::tan, 0, std::pow(2, x.lsb()));
        if ((precision == INT_MIN) || taylor_lsb) {
            precision = x.lsb();
        }
        return {-HUGE_VAL, HUGE_VAL, precision};
    }

    // normalize input interval between -PI/2..PI/2
    double   l = std::fmod(x.lo(), M_PI);  // fractional part of x.lo()
    interval i(l, l + x.size(), x.lsb());

    double v    = 0;  // value at which the lowest slope is computed: 0 if present
    int    sign = 1;

    if (i.lo() > 0) {
        v = i.lo();
    } else if (i.hi() < 0) {
        v    = i.hi();
        sign = -1;
    }

    int precision = exactPrecisionUnary(std::tan, v, sign * std::pow(2, x.lsb()));
    if ((precision == INT_MIN) || taylor_lsb) {
        precision = std::floor(x.lsb() - 2. * (double)std::log2(std::cos(v)));
    }

    if (i.has(-M_PI_2) || i.has(M_PI_2)) {  // asymptotes at PI/2
        return {-HUGE_VAL, HUGE_VAL, precision};
    }

    double a  = std::tan(i.lo());
    double b  = std::tan(i.hi());
    double lo = std::min(a, b);
    double hi = std::max(a, b);

    return {lo, hi, precision};
}

void interval_algebra::testTan()
{
    // analyzeUnaryMethod(20, 20000, "tan", interval(-5, 5, -2), std::tan, &interval_algebra::Tan);
    analyzeUnaryMethod(20, 20000, "tan", interval(-5, 5, -5), std::tan, &interval_algebra::Tan);
    // analyzeUnaryMethod(20, 20000, "tan", interval(-5, 5, -10), std::tan, &interval_algebra::Tan);
    // analyzeUnaryMethod(20, 20000, "tan", interval(-5, 5, -15), std::tan, &interval_algebra::Tan);
}
}  // namespace itv
