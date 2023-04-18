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
// Interval Ge
// interval Ge(const interval& x, const interval& y) const;
// void testGe() const;

interval interval_algebra::Ge(const interval& x, const interval& y) const
{
    // boolean value => precision 0
    if (x.isEmpty() || y.isEmpty()) return interval{};
    if (x.lo() >= y.hi()) return singleton(1,1);
    if (x.hi() < y.lo()) return singleton(0,1);
    return interval{0, 1,1};
}

void interval_algebra::testGe() const
{
    check("test algebra Ge", Ge(interval(5), interval(5)), interval(1));
    check("test algebra Ge", Ge(interval(2, 5), interval(0, 1)), interval(1));
    check("test algebra Ge", Ge(interval(-1, 1), interval(0, 10)), interval(0, 1));
}
}  // namespace itv
