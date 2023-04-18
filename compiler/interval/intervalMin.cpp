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
// Interval Min
// interval Min(const interval& x) const;
// void testMin() const;

interval interval_algebra::Min(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return {};

    return {std::min(x.lo(), y.lo()), std::min(x.hi(), y.hi()), std::min(x.lsb(), y.lsb())}; // resulting interval should be as precise as the most precise of the operands
}

void interval_algebra::testMin() const
{
    check("test algebra Min", Min(interval(0, 5), interval(-3, 10)), interval(-3, 5));
    check("test algebra Min", Min(interval(0, 5), interval(-3, -3)), interval(-3, -3));
}
}  // namespace itv
