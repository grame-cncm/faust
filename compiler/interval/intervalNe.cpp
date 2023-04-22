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
// Interval Ne
// interval Ne(const interval& x, const interval& y) const;
// void testNe() const;

interval interval_algebra::Ne(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return {};
    }
    if ((x.hi() < y.lo()) || x.lo() > y.hi()) {
        return interval{1.0};
    }
    if ((x.hi() == y.lo()) || x.lo() == y.hi()) {
        return interval{0.0};
    }
    return {0, 1};
}

void interval_algebra::testNe() const
{
    check("test algebra Ne", Ne(interval(0, 5), interval(-3, 10)), interval(0, 1));
    check("test algebra Ne", Ne(interval(0, 5), interval(8, 10)), interval(1));
    check("test algebra Ne", Ne(interval(0, 0), interval(0, 0)), interval(0));
}
}  // namespace itv
