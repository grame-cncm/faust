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
// Interval Exp
// interval Exp(const interval& x) const;
// void testExp() const;

interval interval_algebra::Exp(const interval& x) const
{
    if (x.isEmpty()) {
        return x;
    }

    // lowest slope is attained at the lowest boundary
    // int precision = exactPrecisionUnary(exp, x.lo(), pow(2, x.lsb()));
    double delta = exp(pow(2, x.lsb())) - 1;
    int p1 = floor(x.lo()*log2(M_E)); // log2(exp(x.lo()))
    int p2 = 0;
    if (delta == 0) // avoid absorption of 2^l into x
        p2 = x.lsb(); // exp(x) - 1 ≃ x if x very small, so delta2 ≃ pow(2, x.lsb())
    else
        p2 = floor((double)log2(delta));
    int precision = p1 + p2;

    return {exp(x.lo()), exp(x.hi()), precision};
}

void interval_algebra::testExp() const
{
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, 0), exp, &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -3), exp, &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -6), exp, &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -9), exp, &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -12), exp, &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -15), exp, &interval_algebra::Exp);
    analyzeUnaryMethod(10, 100000, "exp", interval(-100, 10, -18), exp, &interval_algebra::Exp);
}
}  // namespace itv
