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
#include <cmath>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Lsh
// interval Lsh(const interval& x, const interval& y) const;
// void testLsh() const;

interval interval_algebra::Lsh(const interval& x, const interval& y) const
{
    interval j{pow(2, y.lo()), pow(2, y.hi())};
    return Mul(x, j);
}

void interval_algebra::testLsh() const
{
    check("test algebra Lsh", Lsh(interval(0, 1), interval(4)), interval(0, 16));
    check("test algebra Lsh", Lsh(interval(0.5, 1), interval(-1, 4)), interval(0.25, 16));
    check("test algebra Lsh", Lsh(interval(-10, 10), interval(-1, 4)), interval(-160, 160));
}
}  // namespace itv
