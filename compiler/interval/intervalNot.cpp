/* Copyright 2020-2026 Yann Orlarey, Agathe Herrou, Stéphane Letz
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
// Interval Not
// interval Not(const interval& x);
// void testNot();

// Numeric kernel: enclose int32 bitwise complement after integer conversion.
// ~x = -1-x reverses signed order, so endpoints suffice even for full int32;
// enumerating that range would not terminate. The low bit is always significant.
interval interval_algebra::numericNot(const interval& input) const
{
    const interval x = IntCast(input);
    if (x.isEmpty()) return empty();
    return {-1.0 - x.hi(), -1.0 - x.lo(), 0};
}

static double myNot(double x)
{
    int a = saturatedIntCast(x);
    int b = ~a;
    return double(b);
}

void interval_algebra::testNot()
{
    analyzeUnaryMethod(10, 1000, "not", interval(-10, -1), myNot, &interval_algebra::Not);
    analyzeUnaryMethod(10, 1000, "not", interval(10, 12), myNot, &interval_algebra::Not);
    analyzeUnaryMethod(10, 1000, "not", interval(-10, 12), myNot, &interval_algebra::Not);

    analyzeUnaryMethod(10, 1000, "not", interval(-10, -1, 5), myNot, &interval_algebra::Not);
    analyzeUnaryMethod(10, 1000, "not", interval(10, 12, 10), myNot, &interval_algebra::Not);
    analyzeUnaryMethod(10, 1000, "not", interval(-10, 12, 5), myNot, &interval_algebra::Not);
}
}  // namespace itv
