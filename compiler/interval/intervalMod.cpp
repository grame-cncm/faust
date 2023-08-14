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
#include <iostream>
#include <random>
#include <utility>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {

// union of two floating point intervals
inline interval operator+(const interval& a, const interval& b)
{
    if (a.isEmpty()) {
        return b;
    }
    if (b.isEmpty()) {
        return a;
    }
    return interval{std::min(a.lo(), b.lo()), std::max(a.hi(), b.hi()), std::min(a.lsb(), b.lsb())};
}

// negation of an interval
interval neg(interval x)
{
    return interval{-x.hi(), -x.lo(), x.lsb()};
}

// join of two intervals
interval join(interval x, interval y)
{
    if (x.isEmpty()) {
        return y;
    }
    if (y.isEmpty()) {
        return x;
    }
    return interval{std::min(x.lo(), y.lo()), std::max(x.hi(), y.hi()), std::min(x.lsb(), y.lsb())};
}

// split an interval into two intervals, negative and positive (or empty)
std::pair<interval, interval> split(interval x)
{
    if (x.lo() >= 0) {
        return {empty(), x};
    }
    if (x.hi() < 0) {
        return {x, empty()};
    }
    return {interval{x.lo(), nexttoward(0.0, -1.0), x.lsb()}, interval{0.0, x.hi(), x.lsb()}};
}

// split an interval into two intervals, negative and positive (or empty)
std::pair<interval, interval> splitnz(interval x)
{
    if (x.lo() >= 0) {
        return {empty(), x};
    }
    if (x.hi() < 0) {
        return {x, empty()};
    }
    return {interval{x.lo(), nexttoward(0.0, -1.0)}, interval{nexttoward(0.0, 1.0), x.hi()}};
}

//------------------------------------------------------------------------------------------
// modulo function on intervals based on https://github.com/orlarey/interval-mod
//------------------------------------------------------------------------------------------

/**
 * @brief resulting interval of fmod(x,y) for interval x and y
 *
 * @param x the interval we compute the modulo of
 * @param y the divisor
 * @return interval the resulting interval
 */

interval positiveFMod(const interval& x, const interval& y)
{
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }
    int n = int(x.lo() / y.hi());
    int precision = std::min(x.lsb(), y.lsb());

    if (n == 0) {
        // prop: x.lo() < y.hi()
        if (y.hi() > x.hi()) {
            if (y.lo() > x.hi()) {
                // prop: x < y => fmod(x,y) = x
                return x;
            }
            // prop: y.lo() <= x.hi() < y.hi()
            return interval{0.0, x.hi(), precision};
        }
        // prop: x.lo() < y.hi() <= x.hi()
        return interval{0.0, nexttoward(y.hi(), 0), precision};
    }

    // prop: n > 0 && y.hi() <= x.lo()
    double hi = x.hi() / (n + 1);
    if (y.hi() <= hi) {
        return interval{0.0, nexttoward(y.hi(), 0), precision};
    }
    // prop: y.hi() > hi
    if (y.lo() <= hi) {
        return interval{0.0, nexttoward(hi, 0), precision};
    }
    // prop : y.lo() > hi
    // we compute the intersections of y with the segment
    // (hi,hi)->(zhi,0) and (lo,lo)->(zlo,0)
    double lo  = x.lo() / (n + 1);
    double zhi = x.hi() / n;
    double zlo = x.lo() / n;

    double v1 = hi - (y.lo() - hi) / (zhi - hi) * hi;
    double v0 = lo - (y.hi() - lo) / (zlo - lo) * lo;

    return interval{v0, v1, precision};
}

// fmod of two signed intervals
interval interval_algebra::Mod(const interval& x, const interval& y)
{
    auto [xn, xp] = split(x);    // slipts x into a negative and a positive interval
    auto [yn, yp] = splitnz(y);  // slipts y into a negative and a positive interval (zero excluded)

    // compute the 4 possible fmod of the 4 possible combinations of xn, xp, yn, yp
    auto xnyn = neg(positiveFMod(neg(xn), neg(yn)));
    auto xnyp = neg(positiveFMod(neg(xn), yp));
    auto xpyn = positiveFMod(xp, neg(yn));
    auto xpyp = positiveFMod(xp, yp);

    // Make sure these 4 values are in the resulting interval
    auto bb = singleton(fmod(x.hi(), y.hi())) + singleton(fmod(x.lo(), y.hi())) + singleton(fmod(x.hi(), y.lo())) +
              singleton(fmod(x.lo(), y.lo()));

    // combine all the intervals
    return bb + xnyn + xnyp + xpyn + xpyp;
}

void interval_algebra::testMod()
{
    // check("test algebra Mod", Mod(interval(-100, 100), 1.0), interval(nextafter(-1.0, 0.0), nextafter(1.0, 0.0)));
    // check("test algebra Mod", Mod(interval(0, 100), 2), interval(0, nextafter(2.0, 0)));
    // check("test algebra Mod", Mod(interval(0, 100), -1.0), interval(0, nextafter(1.0, 0)));
    /* check("test algebra Mod", Mod(interval(5, 7), interval(4, 4.5)), interval(0.5, 3));
    check("test algebra Mod", Mod(interval(5, 7), interval(8, 10)), interval(5, 7));
    check("test algebra Mod", Mod(interval(-7, 7), interval(8, 10)), interval(-7, 7));
    check("test algebra Mod", Mod(interval(0, 100), interval(7, 7)), interval(0, nextafter(7.0, 0.0))); */

    analyzeBinaryMethod(10, 10000, "mod", interval(0, 10, -5), interval(0, 10, -5), fmod, &interval_algebra::Mod);
    analyzeBinaryMethod(10, 10000, "mod", interval(0, 10, 1), interval(0, 10, 0), fmod, &interval_algebra::Mod);
    analyzeBinaryMethod(10, 10000, "mod", interval(0, 10, 0), interval(0, 10, 0), fmod, &interval_algebra::Mod);
    analyzeBinaryMethod(10, 10000, "mod", interval(0, 10, 0), interval(0, 10, -5), fmod, &interval_algebra::Mod);
}

}  // namespace itv
