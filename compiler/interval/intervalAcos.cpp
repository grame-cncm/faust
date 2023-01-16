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
// Interval Acos
// interval Acos(const interval& x) const;
// void testAcos() const;

static const interval AcosDomain(-1, 1);

interval interval_algebra::Acos(const interval& x) const
{
    interval i = intersection(AcosDomain, x);
    if (i.isEmpty()) return i;
    return {acos(i.hi()), acos(i.lo())};
}

void interval_algebra::testAcos() const
{
    analyzeUnaryMethod(10, 1000, "acos", interval(-1, 1), acos, &interval_algebra::Acos);
}
}  // namespace itv