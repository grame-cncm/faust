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
// modulo function on intervals
// (see https://stackoverflow.com/questions/31057473/calculating-the-modulo-of-two-intervals)

interval interval_algebra::Mod(const interval& x, double m)
{
    if (x.isEmpty() || (m == 0)) {
        return {};
    }

    if (x.hi() < 0) {
        return Neg(Mod({-x.hi(), -x.lo()}, m));
        // (3): split into negative and non-negative interval, compute and join
    }

    if (x.lo() < 0) {
        return reunion(Mod({x.lo(), nextafter(-0.0, -HUGE_VAL)}, m), Mod({0.0, x.hi()}, m));
        // (4): there is no k > 0 such that x.lo() < k*m <= x.hi()
    }

    if ((x.size() < fabs(m)) && (fmod(x.lo(), m) <= fmod(x.hi(), m))) {
        return {fmod(x.lo(), m), fmod(x.hi(), m)};
        // (5): we can't do better than that
    }
    // [0,m[
    return {0, nextafter(fabs(m), 0.0)};
}

interval interval_algebra::Mod(const interval& x, const interval& y)
{
    if (x.isEmpty() || y.isEmpty()) {
        return {};
    }
    if (x.hi() < 0) {
        return Neg(Mod({-x.hi(), -x.lo()}, {y.lo(), y.hi()}));
        // (3): split into negative and non-negative interval, compute, and join
    }
    if (x.lo() < 0) {
        return reunion(Mod({x.lo(), -1}, {y.lo(), y.hi()}), Mod({0, x.hi()}, {y.lo(), y.hi()}));
        // (4) use the simpler function from before
    }
    if (y.lo() == y.hi()) {
        return Mod({x.lo(), x.hi()}, y.lo());
        // (5) use only non-negative y.lo() and y.hi()
    }
    if (y.hi() <= 0) {
        return Mod({x.lo(), x.hi()}, {-y.hi(), -y.lo()});
        // (6) similar to (5), make modulus non-negative
    }
    if (y.lo() <= 0) {
        return Mod({x.lo(), x.hi()}, {1, std::max(-y.lo(), y.hi())});
        // (7) compare to (4) in mod1, check x.hi()-x.lo() < |modulus|
    }
    if (x.hi() - x.lo() >= y.hi()) {
        return {0, y.hi() - 1};
        // (8) similar to (7), split interval, compute, and join
    }
    if (x.hi() - x.lo() >= y.lo()) {
        return reunion({0, x.hi() - x.lo() - 1}, Mod({x.lo(), x.hi()}, {x.hi() - x.lo() + 1, y.hi()}));
        // (9) modulo has no effect
    }
    if (y.lo() > x.hi()) {
        return {x.lo(), x.hi()};
        // (10) there is some overlapping of {x.lo(),x.hi()} and {y.hi(),y.lo()}
    }
    if (y.hi() > x.hi()) {
        return {0, x.hi()};
        // (11)  either compute all possibilities and join, or be imprecise
    }
    return {0, y.hi() - 1};
}

void interval_algebra::testMod()
{
    check("test algebra Mod", Mod(interval(-100, 100), 1.0), interval(nextafter(-1.0, 0.0), nextafter(1.0, 0.0)));
    check("test algebra Mod", Mod(interval(0, 100), 2), interval(0, nextafter(2.0, 0)));
    check("test algebra Mod", Mod(interval(0, 100), -1.0), interval(0, nextafter(1.0, 0)));
    check("test algebra Mod", Mod(interval(5, 7), interval(8, 10)), interval(5, 7));
    check("test algebra Mod", Mod(interval(-7, 7), interval(8, 10)), interval(-7, 7));
    check("test algebra Mod", Mod(interval(0, 100), interval(7, 7)), interval(0, nextafter(7.0, 0.0)));
}
}  // namespace itv
