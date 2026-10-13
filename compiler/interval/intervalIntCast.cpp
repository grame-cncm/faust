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
#include "directed_rounding.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval IntCast
// interval IntCast(const interval& x);
// void testIntCast();

// restrict to integer range

interval interval_algebra::numericIntCast(const interval& x) const
{
    if (x.isEmpty()) {
        return empty();
    }
    // Already-integer operands have wrapping semantics, not an undefined cast.
    if (x.lsb() >= 0) return detail::int32Hull(x);
    // Truncation must fit int32. Fractional endpoints just beyond INT_MIN/MAX
    // can still truncate to a valid integer; infinities and boundary integers cannot.
    if (x.lo() >= 2147483648.0 || x.hi() <= -2147483649.0) return empty();
    // Clamp only the analyzer's endpoints to compute the image of VALID inputs.
    // The public transfer marks excluded inputs invalid; runtime code is not clamped.
    return {double(saturatedIntCast(x.lo())), double(saturatedIntCast(x.hi())),
            0};  // integer intervals have 0 bits of precision
}

void interval_algebra::testIntCast()
{
    check("test algebra IntCast", IntCast(interval{-3.8, 4.9}), interval{-3.0, 4.0, 0});
    check("test algebra IntCast", IntCast(interval{-HUGE_VAL, HUGE_VAL}),
          interval(-2147483648.0, 2147483647.0, 0, true));
}
}  // namespace itv
