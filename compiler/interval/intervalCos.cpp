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
// Interval Cos
// interval Cos(const interval& x);
// void testCos();

static double cosPi(double x)
{
    return cos(x * M_PI);
}

interval interval_algebra::Cos(const interval& x)
{
    int precision = exactPrecisionUnary(cos, 0, pow(2, x.lsb()));
    if (precision == INT_MIN or taylor_lsb) precision = 2*x.lsb() - 1; // if x.lsb() is so small that the automatic computation doesn't work

    if (x.isEmpty()) {
        return {};
    }
    if (x.size() >= 2*M_PI) {
        return {-1, 1, precision};
    }

    // normalize input interval between 0..2 (corresponding to 0..2PI)
    double l = fmod(x.lo(), 2*M_PI);
    if (l < 0) {
        l += 2*M_PI;
    }
    interval i(l, l + x.size(), x.lsb());

    // compute the default boundaries
    double a  = cos(i.lo());
    double b  = cos(i.hi());
    double lo = std::min(a, b);
    double hi = std::max(a, b);

    // check if integers are included
    if (i.has(0) || i.has(2*M_PI)) {
        hi = 1;
    }
    if (i.has(1*M_PI) || i.has(3*M_PI)) {
        lo = -1;
    }

    double v = 0;  // value of the interval at which the finest precision is computed

    if (i.hi() < 1*M_PI or
        (i.lo() > 1*M_PI and i.hi() < 2*M_PI))  // if there are no integers in i, i.e i is included in ]0;1[ or ]1;2[
    {
        double delta_hi = ceil(x.hi()/M_PI) - x.hi()/M_PI;
        double delta_lo = x.lo()/M_PI - floor(x.lo()/M_PI);
        if (delta_hi < delta_lo) {  // if the lowest slope is attained for the higher bound
            v = x.hi();
        } else {  // ... for the lower bound
            v = x.lo();
        }
    }

    precision = exactPrecisionUnary(cos, v, pow(2, x.lsb()));
    if (precision == INT_MIN or taylor_lsb)
    {
        /* cos(x + u) - cos(x) = - u·sin(x) if x != 0
                                = - u^2/2 · cos(x) = -u^2/2 if x == 0*/

        if (v != 0) precision = x.lsb() + (int)floor(log2(abs(sin(v))));// (int)floor(log2(M_PI*abs(cos(M_PI*v)))) + x.lsb();
        else precision = 2*x.lsb() -1 ; //- (int)floor(2*log2(M_PI));
    }

    return {lo, hi, precision};
}

void interval_algebra::testCos()
{
    analyzeUnaryMethod(10, 40000, "cos", interval(0, 2*M_PI, -3), cos, &interval_algebra::Cos);
    analyzeUnaryMethod(10, 40000, "cos", interval(0, M_PI, -5), cos, &interval_algebra::Cos);
    analyzeUnaryMethod(10, 40000, "cos", interval(0, M_PI, -10), cos, &interval_algebra::Cos);
    analyzeUnaryMethod(10, 40000, "cos", interval(0, M_PI, -15), cos, &interval_algebra::Cos);
    analyzeUnaryMethod(10, 40000, "cos", interval(0, M_PI, -20), cos, &interval_algebra::Cos);
    analyzeUnaryMethod(10, 40000, "cos", interval(0, M_PI, -24), cos, &interval_algebra::Cos);
}
}  // namespace itv
