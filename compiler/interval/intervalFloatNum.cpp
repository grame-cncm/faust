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
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval IntNum

// Numeric kernel: inject a known literal as a point, rounded once to binary32 in float
// mode. Float/double retain floating nature even for integral-looking literals;
// quad/fixed keep legacy injection. Explicit literals need no analyzer-error widening.
// NaN literals retain an invalid-only numeric representation.
interval interval_algebra::numericFloatNum(double x) const
{
    const interval value = singleton(programBound(x));
    if (programPrecision() != 1 && programPrecision() != 2) return value;
    return {value.lo(), value.hi(), std::min(value.lsb(), -1)};
}
}  // namespace itv
