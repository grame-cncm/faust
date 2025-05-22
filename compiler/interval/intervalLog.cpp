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
// Interval Log
// interval Log(const interval& x);
// void testLog();

static const interval domain{0, HUGE_VAL, 0};

interval interval_algebra::Log(const interval& x)
{
    interval i = intersection(x, domain);

    if (i.isEmpty()) {
        return empty();
    }

    // lowest slope is at the highest bound of the interval
    int precision = exactPrecisionUnary(
        std::log, i.hi(),
        -std::pow(2, i.lsb()));  // -pow because we take the FP number right before the higher bound
    if ((precision == INT_MIN) || taylor_lsb) {
        /* double delta     = -std::log(1 - std::pow(2, i.lsb()) / i.hi());
        precision = std::floor((double)std::log2(delta));*/
        precision = std::floor(i.lsb() - (double)std::log2(std::abs(i.hi())));
    }

    return {log(i.lo()), log(i.hi()), precision};
}

void interval_algebra::testLog()
{
    /* analyzeUnaryMethod(10, 10000, "log", interval(0, 10, -6), log, &interval_algebra::Log);
    analyzeUnaryMethod(10, 10000, "log", interval(0, 10, -12), log, &interval_algebra::Log);
    analyzeUnaryMethod(10, 10000, "log", interval(0, 10, -20), log, &interval_algebra::Log);
    analyzeUnaryMethod(10, 10000, "log", interval(0, 10, -24), log, &interval_algebra::Log);*/

    analyzeUnaryMethod(10, 10000, "log", interval(-10, 10, -24), log, &interval_algebra::Log);

    // check("test algebra Log", Log(interval(1, 10)), interval(log(1), log(10)));
    // check("test algebra Log", Log(interval(0, 10)), interval(log(0), log(10)));
    // check("test algebra Log", Log(interval(-10, 10)), interval(log(0), log(10)));
}
}  // namespace itv
