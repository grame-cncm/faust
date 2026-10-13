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
// Interval Round
// interval Round(const interval& x);
// void testRound();

// Numeric kernel: numeric round image; empty stays empty, and integer inputs
// first convert to the target float. Results keep floating nature in every precision,
// so subsequent operations cannot incorrectly enter the int32 wrapping branch.
interval interval_algebra::numericRound(const interval& input) const
{
    const interval x = detail::floatingOperand(input);
    if (x.isEmpty()) {
        return empty();
    }

    return {std::round(x.lo()), std::round(x.hi()),
            detail::floatingLSB(std::max(0, x.lsb()))};  // integral grid, with floating nature
}

void interval_algebra::testRound()
{
    check("test algebra Round", Round(interval(-3.1, 5.9)), interval(-3, 6));
}
}  // namespace itv
