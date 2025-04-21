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
// Interval Cosh
// interval Cosh(const interval& x);
// void testCosh();

interval interval_algebra::Cosh(const interval& x)
{
    if (x.isEmpty()) {
        return empty();
    }

    double v = 0;  // absolute lowest slope is at zero

    if (x.hasZero()) {
        int precision = exactPrecisionUnary(cosh, v, pow(2, x.lsb()));
        if ((precision == INT_MIN) || taylor_lsb) {
            precision = floor(2 * x.lsb() - 1);  // cosh(u) - cosh(0) = u^2/2 + o(u^2)
        }
        return {1, std::max(cosh(x.lo()), cosh(x.hi())), precision};
    }

    int sign = 1;

    // if zero is not included, lowest slope is at the boundary of lowest absolute value
    if (x.lo() > 0) {  // if the interval is entirely in the positives,
        v = x.lo();
    } else if (x.hi() < 0) {  // if the interval is entirely in the negatives
        v    = x.hi();
        sign = -1;
    }

    int precision = exactPrecisionUnary(cosh, v, sign * pow(2, x.lsb()));
    if ((precision == INT_MIN) || taylor_lsb) {
        precision =
            floor(x.lsb() + log2(std::abs(sinh(v))));  // cosh(x+u) - cosh(x) = u sinh(x) + o(u)
    }

    return {std::min(cosh(x.lo()), cosh(x.hi())), std::max(cosh(x.lo()), cosh(x.hi())), precision};
}

void interval_algebra::testCosh()
{
    analyzeUnaryMethod(10, 1000, "cosh", interval(-10, 10, 0), cosh, &interval_algebra::Cosh);
    analyzeUnaryMethod(10, 1000, "cosh", interval(-10, 10, -5), cosh, &interval_algebra::Cosh);
    analyzeUnaryMethod(10, 1000, "cosh", interval(-10, 10, -10), cosh, &interval_algebra::Cosh);
    analyzeUnaryMethod(10, 1000, "cosh", interval(-10, 10, -15), cosh, &interval_algebra::Cosh);
}
}  // namespace itv
