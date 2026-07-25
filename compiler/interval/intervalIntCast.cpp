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
// Interval IntCast
// interval IntCast(const interval& x);
// void testIntCast();

// restrict to integer range

interval interval_algebra::IntCast(const interval& x) const
{
    if (x.isEmpty()) {
        return empty();
    }
    // An out-of-range float-to-int cast is not portable: x86 (cvttsd2si) yields
    // INT_MIN for every out-of-range value while ARM (fcvtzs) saturates. The compiler
    // emits a plain cast and guarantees neither, so as soon as the input can leave
    // the int32 range the sound bound is the UNION of both behaviors: the full range.
    if (x.lo() < (double)INT_MIN || x.hi() > (double)INT_MAX) {
        return {(double)INT_MIN, (double)INT_MAX, 0};
    }
    return {double(saturatedIntCast(x.lo())), double(saturatedIntCast(x.hi())),
            0};  // integer intervals have 0 bits of precision
}

void interval_algebra::testIntCast()
{
    check("test algebra IntCast", IntCast(interval{-3.8, 4.9}), interval{-3.0, 4.0, 0});
    check("test algebra IntCast", IntCast(interval{-HUGE_VAL, HUGE_VAL}),
          interval{-2147483648.0, 2147483647.0, 0});
}
}  // namespace itv
