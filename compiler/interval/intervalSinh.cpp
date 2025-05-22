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
// interval Sinh(const interval& x);
// void testSinh();

interval interval_algebra::Sinh(const interval& x)
{
    if (x.isEmpty()) {
        return empty();
    }

    double v    = 0;  // absolute lowest slope is at zero
    int    sign = 1;

    // if zero is not included, lowest slope is at the boundary of lowest absolute value
    if (!x.hasZero()) {
        v    = minValAbs(x);
        sign = signMinValAbs(x);
    }

    int precision = exactPrecisionUnary(sinh, v, sign * std::pow(2, x.lsb()));
    if ((precision == INT_MIN) || taylor_lsb) {
        precision = std::floor(x.lsb() + std::log2(std::cosh(v)));
    }

    return {std::sinh(x.lo()), std::sinh(x.hi()), precision};
}

void interval_algebra::testSinh()
{
    analyzeUnaryMethod(10, 1000, "sinh", interval(-10, 10, 0), std::sinh, &interval_algebra::Sinh);
    analyzeUnaryMethod(10, 1000, "sinh", interval(-10, 10, -5), std::sinh, &interval_algebra::Sinh);
    analyzeUnaryMethod(10, 1000, "sinh", interval(-10, 10, -10), std::sinh,
                       &interval_algebra::Sinh);
    analyzeUnaryMethod(10, 1000, "sinh", interval(-10, 10, -15), std::sinh,
                       &interval_algebra::Sinh);
    analyzeUnaryMethod(10, 1000, "sinh", interval(-10, 10, -20), std::sinh,
                       &interval_algebra::Sinh);
}
}  // namespace itv
