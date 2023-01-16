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
// Interval Tanh
// interval Tanh(const interval& x) const;
// void testTanh() const;

interval interval_algebra::Tanh(const interval& x) const
{
    if (x.isEmpty()) return {};
    return {tanh(x.lo()), tanh(x.hi())};
}

void interval_algebra::testTanh() const
{
    analyzeUnaryMethod(20, 2000, "tanh", interval(-10 * M_PI, 10 * M_PI), tanh, &interval_algebra::Tanh);
}
}  // namespace itv
