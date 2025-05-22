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
// interval Tanh(const interval& x);
// void testTanh();

interval interval_algebra::Tanh(const interval& x)
{
    if (x.isEmpty()) {
        return empty();
    }

    // value at which the lowest slope is attained: bound of the interval with the highest absolute
    // value
    double v    = maxValAbs(x);
    int    sign = signMaxValAbs(x);

    int precision = exactPrecisionUnary(std::tanh, v, sign * std::pow(2, x.lsb()));
    if ((precision == INT_MIN) || taylor_lsb) {
        precision = std::floor(x.lsb() - 2. * (double)std::log2(std::cosh(v)));
    }

    return {std::tanh(x.lo()), std::tanh(x.hi()), precision};
}

void interval_algebra::testTanh()
{
    // analyzeUnaryMethod(20, 2000, "tanh", interval(-10, 10), std::tanh, &interval_algebra::Tanh);
    analyzeUnaryMethod(20, 2000, "tanh", interval(-10, 10, 0), std::tanh, &interval_algebra::Tanh);
    analyzeUnaryMethod(20, 2000, "tanh", interval(-10, 10, -5), std::tanh, &interval_algebra::Tanh);
    analyzeUnaryMethod(20, 2000, "tanh", interval(-10, 10, -10), std::tanh,
                       &interval_algebra::Tanh);
    analyzeUnaryMethod(20, 2000, "tanh", interval(-10, 10, -15), std::tanh,
                       &interval_algebra::Tanh);
    analyzeUnaryMethod(20, 2000, "tanh", interval(-10, 10, -20), std::tanh,
                       &interval_algebra::Tanh);
}
}  // namespace itv
