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
// Interval division

interval interval_algebra::Div(const interval& x, const interval& y) const
{
    interval D = Mul(x, Inv(y));
    return D;
}

double div(double x, double y)
{
    return x / y;
}

void interval_algebra::testDiv() const
{
    // lots of experiments because of the quadratic size of the input
    analyzeBinaryMethod(10, 5000000, "Div", interval(-100, 100, -15), interval(0.001, 1000, -15), div, &interval_algebra::Div);
    analyzeBinaryMethod(10, 5000000, "Div", interval(-100, 100, -15), interval(-1000, -0.001,-15), div, &interval_algebra::Div);
    
    analyzeBinaryMethod(10, 500000, "div", interval(0, 10, 0), interval(0, 10, 0), div, &interval_algebra::Div);
    analyzeBinaryMethod(10, 500000, "div", interval(0, 10, -5), interval(0, 10, 0), div, &interval_algebra::Div);
    analyzeBinaryMethod(10, 500000, "div", interval(0, 10, -10), interval(0, 10, 0), div, &interval_algebra::Div);
    analyzeBinaryMethod(10, 500000, "div", interval(0, 10, -15), interval(0, 10, 0), div, &interval_algebra::Div);
    analyzeBinaryMethod(10, 500000, "div", interval(0, 10, 0), interval(0, 10, -10), div, &interval_algebra::Div);
    analyzeBinaryMethod(10, 500000, "div", interval(0, 10, -5), interval(0, 10, -10), div, &interval_algebra::Div);
    analyzeBinaryMethod(10, 500000, "div", interval(0, 10, -10), interval(0, 10, -10), div, &interval_algebra::Div);
    analyzeBinaryMethod(10, 500000, "div", interval(0, 10, -15), interval(0, 10, -10), div, &interval_algebra::Div);

    //     check("test algebra Div", Div(interval(-2, 3), interval(1, 10)), interval(-2, 3));
    //     check("test algebra Div", Div(interval(-2, 3), interval(-1, 10)), interval(-HUGE_VAL, +HUGE_VAL));
    //     check("test algebra Div", Div(interval(-2, 3), interval(-0.1, -0.01)), interval(-300, 200));
    //     check("test algebra Div", Div(interval(0), interval(0)), interval(0));
    //     check("test algebra Div", Div(interval(0, 1), interval(0, 1)), interval(0, +HUGE_VAL));
}
}  // namespace itv
