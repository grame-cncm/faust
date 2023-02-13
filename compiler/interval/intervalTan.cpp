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
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Tan
// interval Tan(const interval& x) const;
// void testTan() const;

interval interval_algebra::Tan(const interval& x) const
{
    double TWOPI = 2 * M_PI;

    if (x.isEmpty()) return x;
    if (x.size() >= TWOPI) return {};  // we have undefined values

    // normalize input interval between 0..4PI
    double l = fmod(x.lo(), TWOPI);
    if (l < 0) l += TWOPI;
    interval i(l, l + x.size());

    if (i.has(M_PI_2) || i.has(3 * M_PI_2) || i.has(5 * M_PI_2) || i.has(7 * M_PI_2)) {
        return {};  //  we have undefined values
    }

    double a  = tan(i.lo());
    double b  = tan(i.hi());
    double lo = std::min(a, b);
    double hi = std::max(a, b);
    return {lo, hi};
}

void interval_algebra::testTan() const
{
    analyzeUnaryMethod(20, 2000, "tan", interval(-M_PI_2, M_PI_2), tan, &interval_algebra::Tan);
}
}  // namespace itv
