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
// Interval Rint
// interval Rint(const interval& x);
// void testRint();

interval interval_algebra::Rint(const interval& x)
{
    return {rint(x.lo()), rint(x.hi()), 0}; // round to nearest integral value => integer => precision 0
}

void interval_algebra::testRint()
{
    check("test algebra Rint", Rint(interval(-3.1, 5.9)), interval(-3, 6));
}
}  // namespace itv
