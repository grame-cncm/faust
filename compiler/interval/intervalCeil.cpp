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
// Interval Ceil
// interval Ceil(const interval& x) const;
// void testCeil() const;

interval interval_algebra::Ceil(const interval& x) const
{
    if (x.isEmpty()) return {};
    return {ceil(x.lo()), ceil(x.hi()), 0}; // ceil yields integers, thus with LSB 0
}

void interval_algebra::testCeil() const
{
    analyzeUnaryMethod(10, 1000, "ceil", interval(-10, 10), ceil, &interval_algebra::Ceil);
}
}  // namespace itv
