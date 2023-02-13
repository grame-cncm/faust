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
// Interval Log
// interval Log(const interval& x) const;
// void testLog() const;

interval interval_algebra::Log(const interval& x) const
{
    if (x.isEmpty()) return {};

    interval i = intersection(interval(0, HUGE_VAL), x);
    return {log(i.lo()), log(i.hi())};
}

void interval_algebra::testLog() const
{
    analyzeUnaryMethod(10, 1000, "log", interval(0, 10), log, &interval_algebra::Log);

    // check("test algebra Log", Log(interval(1, 10)), interval(log(1), log(10)));
    // check("test algebra Log", Log(interval(0, 10)), interval(log(0), log(10)));
    // check("test algebra Log", Log(interval(-10, 10)), interval(log(0), log(10)));
}
}  // namespace itv
