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
// Interval Rsh
// interval Rsh(const interval& x, const interval& y) const;
// void testRsh() const;

static double rsh(double x, double y)
{
    return x*pow(2, -y);
}

interval interval_algebra::Rsh(const interval& x, const interval& y) const
{
    interval j{pow(2, -y.hi()), pow(2, -y.lo())};
    interval z = Mul(x, j);
    
    return {z.lo(), z.hi(), x.lsb() - (int)y.hi()}; // rshifts add some precision to the numbers, at most y.hi() bits
}

void interval_algebra::testRsh() const
{
    // check("test algebra Rsh", Rsh(interval(8, 16), interval(4)), interval(0.5, 1));
    analyzeBinaryMethod(10, 1000, "rshift", interval(0, 32, 0), interval(8, 8, 1), rsh, &interval_algebra::Rsh);
    analyzeBinaryMethod(10, 1000, "rshift", interval(0, 1024, 0), interval(-10, 10, 0), rsh, &interval_algebra::Rsh);
    analyzeBinaryMethod(10, 1000, "rshift", interval(0, 1024, 2), interval(-10, 10, 0), rsh, &interval_algebra::Rsh);
    analyzeBinaryMethod(10, 1000, "rshift", interval(0, 1024, 0), interval(-10, 10, 1), rsh, &interval_algebra::Rsh);
    analyzeBinaryMethod(10, 1000, "rshift", interval(0, 1024, 2), interval(-10, 10, 1), rsh, &interval_algebra::Rsh);
    // analyzeBinaryMethod(10, 1000, "rshift", interval(0, 32, 0), interval(-3, 0, 0), rsh, &interval_algebra::Rsh);
}
}  // namespace itv
