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

#include "bitwiseOperations.hh"
#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"
#include "directed_rounding.hh"

namespace itv {
//------------------------------------------------------------------------------------------

// BRUTE FORCE
// Numeric kernel: enclose int32 bitwise operations after integer conversion.
// Normalize widened integers before bit analysis; empty stays empty.
// Floating inputs are truncated and nonempty results remain integer.
interval interval_algebra::numericOr(const interval& xInput, const interval& yInput) const
{
    // Bitwise results are int32 even for floating inputs; IntCast also recovers
    // the full signed hull of widened integer operands before bit analysis.
    const interval x = xInput.lsb() >= 0 ? detail::int32Hull(xInput) : IntCast(xInput);
    const interval y = yInput.lsb() >= 0 ? detail::int32Hull(yInput) : IntCast(yInput);
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }
    int x0 = saturatedIntCast(x.lo());
    int x1 = saturatedIntCast(x.hi());
    int y0 = saturatedIntCast(y.lo());
    int y1 = saturatedIntCast(y.hi());

    SInterval z = bitwiseSignedOr({x0, x1}, {y0, y1});

    int precision = std::min(x.lsb(), y.lsb());  // all input bits are significant

    /* int precision = std::max(x.lsb(), y.lsb());  // output precision cannot be finer than that of
    the input intervals

    // however, if one of the intervals is reduced to one element, the mask can make it so
    int precisionx = 0;

    if (x0 == x1) {
        int v = x0;           // only element of interval x
        while ((v & 1) == 1)  // while we encounter ones at the lower end of v
        {
            v = v / 2;
            precisionx++;
        }
    }

    int precisiony = 0;

    if (y0 == y1) {
        int v = y0;           // only element of interval y
        while ((v & 1) == 1)  // while we encounter ones at the lower end of v
        {
            v = v / 2;
            precisiony++;
        }
    }*/
    return {double(z.lo), double(z.hi),
            // std::max(precision, std::max(precisionx, precisiony))
            precision};
}
}  // namespace itv
