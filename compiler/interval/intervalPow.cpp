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
#include <cassert>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Pow
// interval Pow(const interval& x, const interval& y) const;
// void testPow() const;

/**
 * @brief Interval elevated to an integer power
*/
static interval ipow(const interval& x, int y)
{
    assert(y >= 0);
    if (y == 0) {
        return singleton(1.0, 0);
    }

    // explicit expression because passing an anonymous function to exactPrecisionUnary is complicated
    int precision = x.lsb()*y; // if x contains 0: finest precision is attained in 0
    if (not x.hasZero())
    {
        double v = minValAbs(x);
        int sign = signMinValAbs(x);
        int p1 = y*(int)log2(abs(v));
        int p2 = 0;

        double epsilon = pow(2, x.lsb());
        double delta = abs(pow(1+ sign*epsilon/v, y) - 1);
        if (delta == 0) // in case of epsilon << x
            p2 = floor((double)log2(y) + x.lsb() - (double)log2(abs(v))); // (1 + eps/v)^y - 1 ≃ y*eps/v if eps/v very small
        else
            p2 = floor((double)log2(delta));

        precision = p1+p2;       
    }

    if ((y & 1) == 0) {
        // y is even
        double z0 = std::pow(x.lo(), y);
        double z1 = std::pow(x.hi(), y);
        return {x.hasZero() ? 0 : std::min(z0, z1), // 0 is in the output interval only if it is in the input interval
                std::max(z0, z1), 
                precision};
    }

    // y is odd
    return {std::pow(x.lo(), y), std::pow(x.hi(), y), precision};
}

/**
 * @brief Interval elevated to an interval power
*/
interval interval_algebra::fPow(const interval& x, const interval& y) const
{
    assert(x.lo() > 0);
    // x all positive
    return Exp(Mul(y, Log(x)));
}

interval interval_algebra::iPow(const interval& x, const interval& y) const
{
    int      y0 = std::max(0, saturatedIntCast(y.lo()));
    int      y1 = std::max(0, saturatedIntCast(y.hi()));
    interval z  = ipow(x, y0);
    if (y1 > y0) {
        // we have more than one integer exponent
        z = reunion(z, ipow(x, y0 + 1));
        z = reunion(z, ipow(x, y1 - 1));
        z = reunion(z, ipow(x, y1));
    }
    return z;
}

interval interval_algebra::Pow(const interval& x, const interval& y) const
{
    if (x.lo() > 0) {
        return fPow(x, y);
    }
    return iPow(x, y);
}

static double myfPow(double x, double y)
{
    return std::pow(x, y);
}

static double myiPow(double x, double y)
{
    return std::pow(x, int(y));
}

void interval_algebra::testPow() const
{
    /* analyzeBinaryMethod(10, 2000000, "iPow^2", interval(-100, 100), interval(2), myiPow, &interval_algebra::iPow);
    analyzeBinaryMethod(10, 2000000, "iPow^3", interval(-100, 100), interval(3), myiPow, &interval_algebra::iPow);
    analyzeBinaryMethod(10, 2000000, "iPow^2", interval(-1, 1), interval(2), myiPow, &interval_algebra::iPow);
    analyzeBinaryMethod(10, 2000000, "iPow^3", interval(-1, 1), interval(3), myiPow, &interval_algebra::iPow);*/

    analyzeBinaryMethod(10, 2000000, "iPow2", interval(-100, 100), interval(0, 200), myiPow, &interval_algebra::iPow);
    analyzeBinaryMethod(10, 2000000, "iPow2", interval(-1, 1), interval(1, 3), myiPow, &interval_algebra::iPow);
    analyzeBinaryMethod(10, 2000000, "iPow2", interval(-1, 1), interval(1, 10), myiPow, &interval_algebra::iPow);

    /* analyzeBinaryMethod(10, 2000000, "fPow2", interval(1, 1000), interval(-10, 10), myfPow, &interval_algebra::fPow);
    analyzeBinaryMethod(10, 2000000, "fPow2", interval(0.001, 1), interval(-10, 10), myfPow, &interval_algebra::fPow);
    analyzeBinaryMethod(10, 2000000, "fPow2", interval(0.001, 10), interval(-200, 200), myfPow, &interval_algebra::fPow);*/
}
}  // namespace itv
