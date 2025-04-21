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
// Interval Log10
// interval Log10(const interval& x);
// void testLog10();

interval interval_algebra::Log10(const interval& x)
{
    if (x.isEmpty()) {
        return empty();
    }

    // lowest slope is at the highest bound of the interval
    int precision = exactPrecisionUnary(
        log10, x.hi(),
        -pow(2, x.lsb()));  // -pow because we take the FP number right before the higher bound
    if ((precision == INT_MIN) || taylor_lsb) {
        precision = floor(x.lsb() - (double)log2(std::abs(x.hi())) - log2(log(10)));
    }

    interval i = intersection(interval(0, HUGE_VAL), x);
    return {log10(i.lo()), log10(i.hi()), precision};
}

void interval_algebra::testLog10()
{
    analyzeUnaryMethod(10, 1000, "log10", interval(0, 10, 0), log10, &interval_algebra::Log10);
    analyzeUnaryMethod(10, 1000, "log10", interval(0, 10, -5), log10, &interval_algebra::Log10);
    analyzeUnaryMethod(10, 1000, "log10", interval(0, 10, -10), log10, &interval_algebra::Log10);
    analyzeUnaryMethod(10, 1000, "log10", interval(0, 10, -15), log10, &interval_algebra::Log10);
    analyzeUnaryMethod(10, 1000, "log10", interval(0, 10, -20), log10, &interval_algebra::Log10);

    // check("test algebra Log", Log10(interval(1, 10)), interval(log10(1), log10(10)));
    // check("test algebra Log", Log10(interval(0, 10)), interval(log10(0), log10(10)));
    // check("test algebra Log", Log10(interval(-10, 10)), interval(log10(0), log10(10)));
}
}  // namespace itv
