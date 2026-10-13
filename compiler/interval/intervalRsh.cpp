/* Copyright 2020-2026 Yann Orlarey, Agathe Herrou, Stéphane Letz
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
#include <climits>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval arithmetic and logical right shifts
// interval ARsh(const interval& x, const interval& y);
// interval LRsh(const interval& x, const interval& y);
// void testRsh();

static double rsh(double x, double k)
{
    return x * std::pow(2, -k);
}

// Numeric kernel: enclose arithmetic int32 right shift for counts in [0,31].
// Arithmetic shifts round negative quotients downward; real scaling alone can
// miss the actual integer result. Invalid counts conservatively return full int32.
interval interval_algebra::numericARsh(const interval& input, const interval& counts) const
{
    const interval x = IntCast(input), k = IntCast(counts);
    if (x.isEmpty() || k.isEmpty()) return empty();
    if (k.lo() < 0 || k.hi() > 31) return {double(INT_MIN), double(INT_MAX), 0};
    interval result = empty();
    for (int shift = int(k.lo()); shift <= int(k.hi()); ++shift)
        result = reunion(result, interval(std::floor(std::ldexp(x.lo(), -shift)),
                                          std::floor(std::ldexp(x.hi(), -shift)), 0));
    return result;
}

// Numeric kernel: enclose logical int32 right shift for counts in [0,31].
// A positive shift sees the uint32 bit pattern; shift zero retains the original
// signed value. Split at zero to handle the unsigned ordering discontinuity.
interval interval_algebra::numericLRsh(const interval& input, const interval& counts) const
{
    const interval x = IntCast(input), k = IntCast(counts);
    if (x.isEmpty() || k.isEmpty()) return empty();
    if (k.lo() < 0 || k.hi() > 31) return {double(INT_MIN), double(INT_MAX), 0};
    interval result = empty();
    for (int shift = int(k.lo()); shift <= int(k.hi()); ++shift) {
        if (shift == 0) { result = reunion(result, x); continue; }
        if (x.lo() < 0) {
            const uint32_t lo = uint32_t(int32_t(x.lo())) >> shift;
            const uint32_t hi = uint32_t(int32_t(std::min(x.hi(), -1.0))) >> shift;
            result = reunion(result, interval(double(lo), double(hi), 0));
        }
        if (x.hi() >= 0) {
            const uint32_t lo = uint32_t(std::max(x.lo(), 0.0)) >> shift;
            const uint32_t hi = uint32_t(x.hi()) >> shift;
            result = reunion(result, interval(double(lo), double(hi), 0));
        }
    }
    return result;
}

void interval_algebra::testRsh()
{
    // check("test algebra Rsh", ARsh(interval(8, 16), interval(4)), interval(0.5, 1));
    analyzeBinaryMethod(10, 1000, "rshift", interval(0, 32, 0), interval(8, 8, 1), rsh,
                        &interval_algebra::ARsh);
    analyzeBinaryMethod(10, 1000, "rshift", interval(0, 1024, 0), interval(-10, 10, 0), rsh,
                        &interval_algebra::ARsh);
    analyzeBinaryMethod(10, 1000, "rshift", interval(0, 1024, 2), interval(-10, 10, 0), rsh,
                        &interval_algebra::ARsh);
    analyzeBinaryMethod(10, 1000, "rshift", interval(0, 1024, 0), interval(-10, 10, 1), rsh,
                        &interval_algebra::ARsh);
    analyzeBinaryMethod(10, 1000, "rshift", interval(0, 1024, 2), interval(-10, 10, 1), rsh,
                        &interval_algebra::ARsh);
    // analyzeBinaryMethod(10, 1000, "rshift", interval(0, 32, 0), interval(-3, 0, 0), rsh,
    // &interval_algebra::ARsh);
}
}  // namespace itv
