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
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Delay
// interval Delay(const interval& x);
// void testDelay();

interval interval_algebra::numericDelay(const interval& x, const interval& y) const
{
    const interval amount = IntCast(y);
    // A zero sample count has no initialization phase. Test numeric endpoints
    // independently of alerts: the public transfer retains both input flags.
    if (!amount.isEmpty() && amount.lo() == 0 && amount.hi() == 0) {
        return x;
    }
    if (x.isEmpty() || amount.isEmpty()) {
        return empty();
    }
    // A possibly positive count still reads initialized memory, even when its
    // minimum is zero. The initial value has the signal's nature and grid.
    interval z = reunion(x, interval(0, 0, x.lsb()));
    return {z.lo(), z.hi(), x.lsb()};
}

void interval_algebra::testDelay()
{
    check("test algebra Delay", Delay(interval(5), interval(0, 10)), interval(0, 5));
    check("test algebra Delay", Delay(interval(5), interval(0)), interval(5));
    check("test algebra Delay", Delay(interval(-1, 1), interval(0, 10)), interval(-1, 1));
}
}  // namespace itv
