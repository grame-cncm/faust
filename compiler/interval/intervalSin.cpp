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
// Interval Sin
// interval Sin(const interval& x);
// void testSin();

static double sinPi(double x)
{
    return sin(x * M_PI);
}

interval interval_algebra::Sin(const interval& x)
{
    int precision = exactPrecisionUnary(sin, 0.5, pow(2, x.lsb()));
    if (precision == INT_MIN or taylor_lsb) precision = 2*x.lsb() - 1; // if x.lsb() is so small that the automatic computation doesn't work

    if (x.size() >= 2*M_PI) {
        return {-1, 1, precision};
    }

    // normalize input interval between 0..2
    double l = fmod(x.lo(), 2*M_PI);
    if (l < 0) {
        l += 2*M_PI;
    }
    interval i(l, l + x.size(), x.lsb());

    // compute the default boundaries
    double a  = sin(i.lo());
    double b  = sin(i.hi());
    double lo = std::min(a, b);
    double hi = std::max(a, b);

    // check if integers are included
    if (i.has(0.5*M_PI) || i.has(2.5*M_PI)) {
        hi = 1;
    }
    if (i.has(1.5*M_PI) || i.has(3.5*M_PI)) {
        lo = -1;
    }

    double v = 0.5*M_PI;  // value of the interval at which the finest precision is computed
                     // defaults at 0.5, interchangeable with any other half-integer

    // precision if we don't hit the half integers
    if (i.hi() < 0.5*M_PI) {
        v = x.hi();
    } else if ((i.lo() > 0.5*M_PI and i.hi() < 1.5*M_PI) or (i.lo() > 1.5*M_PI and i.hi() < 2.5*M_PI)) {
        double delta_hi = ceil(i.hi()/M_PI + 0.5) - i.hi()/M_PI; 
        double delta_lo = i.lo()/M_PI - floor(i.lo()/M_PI - 0.5);
        if (delta_lo > delta_hi) {  // if i.hi is closer to its higher half-integer than i.lo() to its lower half-integer
            v = x.hi();
        } else {
            v = x.lo();
        }
    }

    precision = exactPrecisionUnary(sin, v, pow(2, x.lsb()));
    if (precision == INT_MIN or taylor_lsb)
    {
        if (v != 0.5*M_PI) precision = x.lsb() + (int)floor(log2(abs(cos(v))));// (int)floor(log2(M_PI*cos(M_PI*v))) + x.lsb();
        else precision = 2*x.lsb() -1; // - (int)floor(2*log2(M_PI));
    }

    return {lo, hi, precision};
}

void interval_algebra::testSin()
{
    // analyzeUnaryMethod(5, 20000, "sin", interval(-1, 1, -3), sin, &interval_algebra::Sin);
    analyzeUnaryMethod(10, 40000, "sin", interval(0, 2*M_PI, -3), sin, &interval_algebra::Sin);
    analyzeUnaryMethod(10, 40000, "sin", interval(0, 2*M_PI, -5), sin, &interval_algebra::Sin);
    analyzeUnaryMethod(10, 40000, "sin", interval(0, 2*M_PI, -10), sin, &interval_algebra::Sin);
    analyzeUnaryMethod(10, 40000, "sin", interval(0, 2*M_PI, -15), sin, &interval_algebra::Sin);
    analyzeUnaryMethod(10, 40000, "sin", interval(0, 2*M_PI, -20), sin, &interval_algebra::Sin);
    analyzeUnaryMethod(10, 40000, "sin", interval(0, 2*M_PI, -24), sin, &interval_algebra::Sin);
}
}  // namespace itv
