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

interval interval_algebra::ARsh(const interval& x, const interval& k) const
{
    if (x.isEmpty() || k.isEmpty()) {
        return empty();
    }

    interval j{pow(2, -k.hi()), std::pow(2, -k.lo())};
    interval z = Mul(x, j);

    return {
        z.lo(), z.hi(),
        x.lsb() - (int)k.hi()};  // rshifts add some precision to the numbers, at most y.hi() bits
}

interval interval_algebra::LRsh(const interval& x, const interval& k) const
{
    if (x.isEmpty() || k.isEmpty()) {
        return empty();
    }
    if (x.lo() >= 0) {
        return ARsh(x, k);
    }
    // Negative operands are reinterpreted as uint32 before shifting. A shift by 0
    // passes them through UNCHANGED (still negative once stored back in int32), so
    // when k can be 0 the whole integer range is reachable. For k >= 1 the result is
    // nonnegative and bounded by 2^(32-k) - 1.
    if (k.lo() < 1) {
        return {(double)INT_MIN, (double)INT_MAX, 0};
    }
    double hi = std::min((double)INT_MAX, std::pow(2.0, 32.0 - k.lo()) - 1);
    return {0, hi, 0};
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
