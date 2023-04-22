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
// Interval Atanh
// Calculates the inverse hyperbolic tangent of x; that is the value whose hyperbolic tangent is x.
// interval Atanh(const interval& x) const;
// void testAtanh() const;

static const interval domain(std::nexttoward(-1, 0), std::nexttoward(1, 0));  // interval ]-1,1[

interval interval_algebra::Atanh(const interval& x) const
{
    interval i = intersection(domain, x);
    if (i.isEmpty()) return i;
    return {atanh(i.lo()), atanh(i.hi())};
}

void interval_algebra::testAtanh() const
{
    analyzeUnaryMethod(10, 1000, "atanh", interval(-0.999, 0.999), atanh, &interval_algebra::Atanh);
}
}  // namespace itv
