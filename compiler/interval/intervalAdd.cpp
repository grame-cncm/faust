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
// Interval addition

static double add(double x, double y)
{
    return x + y;
}

static double addint(double x, double y)
{
    return (int)x + (int)y;
}

interval interval_algebra::Add(const interval& x, const interval& y)
{
    if (x.isEmpty() || y.isEmpty()) {
        return {};
    }

    if (x.lsb() >= 0 and y.lsb() >= 0) { // if both intervals are integers
        // if we're dealing with integers the interval has to wrap around 0
        const int xlo = (int)x.lo();
        const int xhi = (int)x.hi();
        const int ylo = (int)y.lo();
        const int yhi = (int)y.hi();

        // detect wrapping
        if (std::abs((double)xhi + (double)yhi) >= (double) INT_MAX 
            or std::abs((double)xhi + (double)yhi) <= (double) INT_MIN 
            or std::abs((double)xlo + (double)ylo) >= (double) INT_MAX
            or std::abs((double)xlo + (double)ylo) <= (double) INT_MIN)
            return {(double) INT_MIN, (double) INT_MAX, std::min(x.lsb(), y.lsb())};

        return {(double)(xlo + ylo), (double)(xhi + yhi), std::min(x.lsb(), y.lsb())};
    }

    return {x.lo() + y.lo(), x.hi() + y.hi(),
            std::min(x.lsb(),
                     y.lsb())};  // the result of an addition needs to be only as precise as the most precise of the operands
}

void interval_algebra::testAdd()
{
    // check("test algebra Add", Add(interval(0, 100), interval(10, 500)), interval(10, 600));
    // analyzeBinaryMethod(10, 2000, "add", interval(0, 10, 0), interval(0, 10, 0), add, &interval_algebra::Add);
    analyzeBinaryMethod(10, 2000, "add", interval(0, pow(2, 31), 0), interval(0, pow(2, 31), 0), addint, &interval_algebra::Add);
    /* analyzeBinaryMethod(10, 2000, "add", interval(0, 10, -5), interval(0, 10, 0), add, &interval_algebra::Add);
    analyzeBinaryMethod(10, 2000, "add", interval(0, 10, -10), interval(0, 10, 0), add, &interval_algebra::Add);
    analyzeBinaryMethod(10, 2000, "add", interval(0, 10, -15), interval(0, 10, 0), add, &interval_algebra::Add);
    analyzeBinaryMethod(10, 2000, "add", interval(0, 10, 0), interval(0, 10, -10), add, &interval_algebra::Add);
    analyzeBinaryMethod(10, 2000, "add", interval(0, 10, -5), interval(0, 10, -10), add, &interval_algebra::Add);
    analyzeBinaryMethod(10, 2000, "add", interval(0, 10, -10), interval(0, 10, -10), add, &interval_algebra::Add);
    analyzeBinaryMethod(10, 2000, "add", interval(0, 10, -15), interval(0, 10, -10), add, &interval_algebra::Add);*/
}
}  // namespace itv
