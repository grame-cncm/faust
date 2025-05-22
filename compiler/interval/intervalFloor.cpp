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
// Interval Floor
// interval Floor(const interval& x);
// void testFloor();

interval interval_algebra::Floor(const interval& x)
{
    if (x.isEmpty()) {
        return empty();
    }
    return {std::floor(x.lo()), std::floor(x.hi()),
            -1};  // even though the output of floor are mathematical integers,
                  // they are implemented as floats and thus should not be given precision 0,
                  // lest it be cast as an int
}

void interval_algebra::testFloor()
{
    analyzeUnaryMethod(10, 1000, "floor", interval(-10, 10, -24), floor, &interval_algebra::Floor);
}
}  // namespace itv
