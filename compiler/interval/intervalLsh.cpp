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
// Interval Lsh
// interval Lsh(const interval& x, const interval& y) const;
// void testLsh() const;

static double lsh(double x, double y)
{
    return x*pow(2, y);
}

interval interval_algebra::Lsh(const interval& x, const interval& y) const
{
    interval j{pow(2, y.lo()), pow(2, y.hi())};
    interval z = Mul(x, j);

    return {z.lo(), z.hi(), x.lsb() + (int)y.lo()}; // lshifts shave some precision off the numbers, at least y.lo() bits
}

void interval_algebra::testLsh() const
{
    /* check("test algebra Lsh", Lsh(interval(0, 1), interval(4)), interval(0, 16));
    check("test algebra Lsh", Lsh(interval(0.5, 1), interval(-1, 4)), interval(0.25, 16));
    check("test algebra Lsh", Lsh(interval(-10, 10), interval(-1, 4)), interval(-160, 160));*/
    analyzeBinaryMethod(10, 100000, "lshift", interval(0, 32, 0), interval(8, 8, 1), lsh, &interval_algebra::Lsh);
    analyzeBinaryMethod(10, 100000, "lshift", interval(0, 1024, 0), interval(-10, 10, 0), lsh, &interval_algebra::Lsh);
    analyzeBinaryMethod(10, 100000, "lshift", interval(0, 1024, 2), interval(-10, 10, 0), lsh, &interval_algebra::Lsh);
    analyzeBinaryMethod(10, 100000, "lshift", interval(0, 1024, 0), interval(-10, 10, 1), lsh, &interval_algebra::Lsh);
    analyzeBinaryMethod(10, 100000, "lshift", interval(0, 1024, 2), interval(-10, 10, 1), lsh, &interval_algebra::Lsh);
}
}  // namespace itv
