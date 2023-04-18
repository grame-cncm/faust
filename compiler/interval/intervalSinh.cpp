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
// Interval Sinh
// interval Sinh(const interval& x) const;
// void testSinh() const;

interval interval_algebra::Sinh(const interval& x) const
{
    if (x.isEmpty()) return x;

    double v = 0; // absolute lowest slope is at zero
    int sign = 1;

    // if zero is not included, lowest slope is at the boundary of lowest absolute value
    if (not x.hasZero())
    {
        v = minValAbs(x);
        sign = signMinValAbs(x);
    }

    return {sinh(x.lo()), sinh(x.hi()), exactPrecisionUnary(sinh, v, sign*pow(2, x.lsb()))};
}

void interval_algebra::testSinh() const
{
    analyzeUnaryMethod(10, 1000, "sinh", interval(-10, 10, 0), sinh, &interval_algebra::Sinh);
    analyzeUnaryMethod(10, 1000, "sinh", interval(-10, 10, -5), sinh, &interval_algebra::Sinh);
    analyzeUnaryMethod(10, 1000, "sinh", interval(-10, 10, -10), sinh, &interval_algebra::Sinh);
    analyzeUnaryMethod(10, 1000, "sinh", interval(-10, 10, -15), sinh, &interval_algebra::Sinh);
    analyzeUnaryMethod(10, 1000, "sinh", interval(-10, 10, -20), sinh, &interval_algebra::Sinh);
}
}  // namespace itv
