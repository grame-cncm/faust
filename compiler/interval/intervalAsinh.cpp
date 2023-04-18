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
// Interval Asinh
// interval Asinh(const interval& x) const;
// void testAsinh() const;
static const interval domain(-HUGE_VAL, HUGE_VAL);

interval interval_algebra::Asinh(const interval& x) const
{
    double v = maxValAbs(x); // value at which the min slope is attained, here the bound of highest absolute value
    int sign = signMaxValAbs(x); // whether we compute the difference between f(v) and f(v+ε) or f(v-ε)

    int precision = exactPrecisionUnary(asinh, v, sign*pow(2, x.lsb()));

    return {asinh(x.lo()), asinh(x.hi()), precision};
}

void interval_algebra::testAsinh() const
{
    analyzeUnaryMethod(10, 1000, "asinh", interval(-10, 10, 0), asinh, &interval_algebra::Asinh);
    analyzeUnaryMethod(10, 1000, "asinh", interval(-10, 10, -5), asinh, &interval_algebra::Asinh);
    analyzeUnaryMethod(10, 1000, "asinh", interval(-10, 10, -10), asinh, &interval_algebra::Asinh);
    analyzeUnaryMethod(10, 1000, "asinh", interval(-10, 10, -15), asinh, &interval_algebra::Asinh);
    analyzeUnaryMethod(10, 1000, "asinh", interval(-10, 10, -20), asinh, &interval_algebra::Asinh);    
}
}  // namespace itv
