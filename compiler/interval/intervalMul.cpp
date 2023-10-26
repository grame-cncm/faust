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
#include "utils.hh"

namespace itv {
//==========================================================================================
//
// interval multiplication
//
//==========================================================================================

static double specialmult(double a, double b)
{
    // we want inf*0 to be 0
    return ((a == 0.0) || (b == 0.0)) ? 0.0 : a * b;
}

static double specialmultint(double a, double b)
{
    // we want inf*0 to be 0
    return ((a == 0.0) || (b == 0.0)) ? 0.0 : (int)a * (int)b;
}

interval interval_algebra::Mul(const interval& x, const interval& y)
{
    if (x.isEmpty() || y.isEmpty()) {
        return {};
    }

    if (x.lsb() >= 0 and y.lsb() >= 0) // operation between integers
    {
        // if the quotient of an INT limit by an interval limit is below a limit of the other interval
        // ie, if there is something big enough in the other interval to make the interval limit go beyond an INT limit
        if ((min4(std::abs(INT_MAX/y.lo()), 
                  std::abs(INT_MAX/y.hi()), 
                  std::abs(INT_MIN/y.lo()), 
                  std::abs(INT_MIN/y.hi())) 
                  <= std::max(std::abs(x.hi()), 
                              std::abs(x.lo()))) or 
            (min4(std::abs(INT_MAX/x.lo()), 
                  std::abs(INT_MAX/x.hi()), 
                  std::abs(INT_MIN/x.lo()), 
                  std::abs(INT_MIN/x.hi())) 
                  <= std::max(std::abs(y.hi()), 
                              std::abs(y.lo()))))
            return {(double) INT_MIN, (double) INT_MAX, x.lsb() + y.lsb()};

        int a = (int)x.lo() * (int)y.lo();
        int b = (int)x.lo() * (int)y.hi();
        int c = (int)x.hi() * (int)y.lo();
        int d = (int)x.hi() * (int)y.hi();

        return {min4(a, b, c, d), max4(a, b, c, d), x.lsb() + y.lsb()};
    }

    double a = specialmult(x.lo(), y.lo());
    double b = specialmult(x.lo(), y.hi());
    double c = specialmult(x.hi(), y.lo());
    double d = specialmult(x.hi(), y.hi());
    return {min4(a, b, c, d), max4(a, b, c, d),
            x.lsb() + y.lsb()};  // the worst case, we need all the precision digits from both the operands
}

void interval_algebra::testMul()
{
    /* check("test algebra Mul", Mul(interval(-1, 1), interval(0, 1)), interval(-1, 1));
    check("test algebra Mul", Mul(interval(-2, 3), interval(-50, 10)), interval(-150, 100));
    check("test algebra Mul", Mul(interval(-2, -1), interval(-2, -1)), interval(1, 4));
    check("test algebra Mul", Mul(interval(0), interval(-HUGE_VAL, HUGE_VAL)), interval(0));
    check("test algebra Mul", Mul(interval(-HUGE_VAL, HUGE_VAL), interval(0)), interval(0));*/

    // analyzeBinaryMethod(10, 2000, "mul", interval(0, 10, 0), interval(0, 10, 0), specialmult, &interval_algebra::Mul);
    analyzeBinaryMethod(10, 2000, "mul", interval(-pow(2, 31), pow(2, 31), 0), interval(-pow(2, 31), pow(2, 31), 0), specialmultint, &interval_algebra::Mul);
    /* analyzeBinaryMethod(10, 2000, "mul", interval(0, 10, -5), interval(0, 10, 0), specialmult, &interval_algebra::Mul);
    analyzeBinaryMethod(10, 2000, "mul", interval(0, 10, -10), interval(0, 10, 0), specialmult, &interval_algebra::Mul);
    analyzeBinaryMethod(10, 2000, "mul", interval(0, 10, -15), interval(0, 10, 0), specialmult, &interval_algebra::Mul);
    analyzeBinaryMethod(10, 2000, "mul", interval(0, 10, 0), interval(0, 10, -10), specialmult, &interval_algebra::Mul);
    analyzeBinaryMethod(10, 2000, "mul", interval(0, 10, -5), interval(0, 10, -10), specialmult,
                        &interval_algebra::Mul);
    analyzeBinaryMethod(10, 2000, "mul", interval(0, 10, -10), interval(0, 10, -10), specialmult,
                        &interval_algebra::Mul);
    analyzeBinaryMethod(10, 2000, "mul", interval(0, 10, -15), interval(0, 10, -10), specialmult,
                        &interval_algebra::Mul); */
}
}  // namespace itv
