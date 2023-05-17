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
// Interval Asin
// Calculates the principal value of the arc sine of x; that is the value whose sine is x.
// the return value is in the range [-pi/2, pi/2].
// interval Asin(const interval& x) const;
// void testAsin() const;

static const interval domain(-1, 1);

interval interval_algebra::Asin(const interval& x) const
{
    interval i = intersection(domain, x);
    if (i.isEmpty()) return i;
    return {asin(i.lo()), asin(i.hi())};
}

void interval_algebra::testAsin() const
{
    analyzeUnaryMethod(10, 1000, "asin", interval(-1, 1), asin, &interval_algebra::Asin);
}
}  // namespace itv
