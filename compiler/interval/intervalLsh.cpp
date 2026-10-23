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
#include <cmath>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Lsh
// interval Lsh(const interval& x, const interval& y);

// Numeric kernel: enclose wrapping int32 left shift for counts in [0,31].
// Convert operands to integers first. Invalid counts have no portable execution
// contract and conservatively return full int32; this does not define such shifts.
interval interval_algebra::numericLsh(const interval& input, const interval& counts) const
{
    const interval x = IntCast(input), k = IntCast(counts);
    if (x.isEmpty() || k.isEmpty()) return empty();
    if (k.lo() < 0 || k.hi() > 31) return {double(INT_MIN), double(INT_MAX), 0};
    interval result = empty();
    for (int shift = int(k.lo()); shift <= int(k.hi()); ++shift) {
        if (x.isconst()) {
            const uint32_t bits = uint32_t(int32_t(x.lo())) << shift;
            result = reunion(result, IntNum(compat::bit_cast<int32_t>(bits)));
        } else {
            // Scaling int32 by powers up to 2^31 is exact in binary64. Once a
            // wrap is possible a single contiguous interval uses the full hull.
            const double lo = std::ldexp(x.lo(), shift), hi = std::ldexp(x.hi(), shift);
            if (lo < INT_MIN || hi > INT_MAX) return {double(INT_MIN), double(INT_MAX), 0};
            result = reunion(result, interval(lo, hi, 0));
        }
    }
    return result;
}
}  // namespace itv
