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
#include "directed_rounding.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval FloatCast
// interval FloatCast(const interval& x);
// void testFloatCast();

// Numeric kernel: enclose conversion to the program's floating type. In float mode,
// convert the source endpoints once; IEEE narrowing is monotone. This is a known
// conversion, not a bound calculation with an unknown analyzer rounding residual.
// Normalize widened integer sources before conversion, retaining a negative
// floating LSB in every precision. NaN keeps the historical empty convention.
interval interval_algebra::numericFloatCast(const interval& input) const
{
    const interval x = detail::int32Hull(input);
    // LSB with -1 value to force the float typing
    return {programBound(x.lo()), programBound(x.hi()), std::min(x.lsb(), -1)};
}

void interval_algebra::testFloatCast()
{
    std::cout << "OK: FloatCast no tests needed" << std::endl;
}
}  // namespace itv
