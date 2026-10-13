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

// Numeric kernel: enclose multiplication; float/double floating corners round outward.
// Zero times an unbounded endpoint keeps the historical numeric-hull convention;
// the public transfer additionally marks possible NaN values.
interval interval_algebra::numericMul(const interval& xIn, const interval& yIn) const
{
    const auto [x, y] = detail::int32Operands(xIn, yIn);
    if (x.isEmpty() || y.isEmpty()) {
        return empty();
    }
    double a = specialmult(x.lo(), y.lo());
    double b = specialmult(x.lo(), y.hi());
    double c = specialmult(x.hi(), y.lo());
    double d = specialmult(x.hi(), y.hi());

    double lo = min4(a, b, c, d);
    double hi = max4(a, b, c, d);

    const bool integerOperands = detail::hasInt32Bounds(x) && detail::hasInt32Bounds(y);
    if (integerOperands) {
        // if the quotient of an INT limit by an interval limit is below a limit of the other
        // interval ie, if there is something big enough in the other interval to make the interval
        // limit go beyond an INT limit
        if (std::max(std::abs(x.lo()), std::abs(x.hi())) *
                std::max(std::abs(y.lo()), std::abs(y.hi())) >=
            (double)INT_MAX) {
            return {(double)INT_MIN, (double)INT_MAX, detail::sumLSB(x.lsb(), y.lsb())};
        }
        /* interval z{lo, hi, x.lsb()+y.lsb()};
        interval shift{pow(2, 31), pow(2, 31), 31};
        interval m{pow(2, 32), pow(2, 32), 32};

        return Sub(Mod(Add(z, shift), m), shift);*/

        /* if ((lo <= (double)INT_MIN - 1 && hi >= (double)INT_MIN) // discontinuity at the lower
        end or (lo <= (double)INT_MAX && hi >= (double)INT_MAX+1))
        {
            return {(double)INT_MIN, (double)INT_MAX, std::min(x.lsb(), y.lsb())};
        }

        int aint = (int)x.lo() * (int)y.lo();
        int bint = (int)x.lo() * (int)y.hi();
        int cint = (int)x.hi() * (int)y.lo();
        int dint = (int)x.hi() * (int)y.hi();

        return {min4(aint, bint, cint, dint), max4(aint, bint, cint, dint), x.lsb() + y.lsb()};*/
    }

    if (detail::usesNativeBounds() && !integerOperands) {
        const interval xFloat = detail::floatingOperand(x), yFloat = detail::floatingOperand(y);
        lo = HUGE_VAL;
        hi = -HUGE_VAL;
        for (double u : {xFloat.lo(), xFloat.hi()}) {
            for (double v : {yFloat.lo(), yFloat.hi()}) {
                // 0*inf describes a zero endpoint limit in the numeric hull.
                const double lower = (u == 0 || v == 0) ? 0 : detail::directedBinary(
                    detail::BinaryOp::Mul, u, v, detail::Direction::Down);
                const double upper = (u == 0 || v == 0) ? 0 : detail::directedBinary(
                    detail::BinaryOp::Mul, u, v, detail::Direction::Up);
                lo = std::min(lo, lower);
                hi = std::max(hi, upper);
            }
        }
    }
    return {
        lo, hi,
        integerOperands ? detail::sumLSB(x.lsb(), y.lsb())
                        : detail::floatingLSB(detail::sumLSB(x.lsb(), y.lsb()))};
}

void interval_algebra::testMul()
{
    /* check("test algebra Mul", Mul(interval(-1, 1), interval(0, 1)), interval(-1, 1));
    check("test algebra Mul", Mul(interval(-2, 3), interval(-50, 10)), interval(-150, 100));
    check("test algebra Mul", Mul(interval(-2, -1), interval(-2, -1)), interval(1, 4));
    check("test algebra Mul", Mul(interval(0), interval(-HUGE_VAL, HUGE_VAL)), interval(0));
    check("test algebra Mul", Mul(interval(-HUGE_VAL, HUGE_VAL), interval(0)), interval(0));*/

    // analyzeBinaryMethod(10, 2000, "mul", interval(0, 10, 0), interval(0, 10, 0), specialmult,
    // &interval_algebra::Mul);
    /* analyzeBinaryMethod(10, 20000, "mul", interval(0, 10, -5), interval(0, 10, 0), specialmult,
    &interval_algebra::Mul); analyzeBinaryMethod(10, 20000, "mul", interval(0, 10, -10), interval(0,
    10, 0), specialmult, &interval_algebra::Mul); analyzeBinaryMethod(10, 20000, "mul", interval(0,
    10, -15), interval(0, 10, 0), specialmult, &interval_algebra::Mul); analyzeBinaryMethod(10,
    20000, "mul", interval(0, 10, 0), interval(0, 10, -10), specialmult, &interval_algebra::Mul);
    analyzeBinaryMethod(10, 20000, "mul", interval(0, 10, -5), interval(0, 10, -10), specialmult,
                        &interval_algebra::Mul);
    analyzeBinaryMethod(10, 20000, "mul", interval(0, 10, -10), interval(0, 10, -10), specialmult,
                        &interval_algebra::Mul);
    analyzeBinaryMethod(10, 20000, "mul", interval(0, 10, -15), interval(0, 10, -10), specialmult,
                        &interval_algebra::Mul);

    analyzeBinaryMethod(10, 200000, "mul", interval(-pow(2, 31), pow(2, 31), 0), interval(-pow(2,
    31), pow(2, 31), 0), specialmultint, &interval_algebra::Mul); analyzeBinaryMethod(10, 200000,
    "mul", interval((double)INT_MAX/2, (double)INT_MAX, 0), interval((double)INT_MAX/2,
    (double)INT_MAX, 0), specialmultint, &interval_algebra::Mul); analyzeBinaryMethod(10, 200000,
    "mul", interval((double)INT_MIN, (double)INT_MIN/2, 0), interval((double)INT_MAX/2,
    (double)INT_MAX, 0), specialmultint, &interval_algebra::Mul); analyzeBinaryMethod(10, 2000000,
    "mul", interval((double)2*INT_MAX/3, (double)INT_MAX, 0), interval(0, 10, 0), specialmultint,
    &interval_algebra::Mul);*/
    check("Test integer Mult",
          Mul(interval(std::pow(2, 30), std::pow(2, 30) + 2, 2), interval(1, 2, 0)),
          interval((double)INT_MIN, std::pow(2, 30) + 2, 0));
    // analyzeBinaryMethod(10, 2000, "mul", interval((double)INT_MAX-1, (double)INT_MAX, 0),
    // interval((double)INT_MAX-1, (double)INT_MAX, 0), specialmultint, &interval_algebra::Mul);
}
}  // namespace itv
