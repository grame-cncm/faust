/* Copyright 2026 Yann Orlarey, Stéphane Letz
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
#include "double_double.hh"

#include <cmath>

namespace itv {

namespace {

// s + e = a + b exactly, s the rounded sum (Knuth's two-sum)
DoubleDouble twoSum(double a, double b)
{
    const double s  = a + b;
    const double bb = s - a;
    const double e  = (a - (s - bb)) + (b - bb);
    return {s, e};
}

// s + e = a + b exactly, |a| >= |b| (Dekker's fast two-sum) : the renormalization
DoubleDouble fastTwoSum(double a, double b)
{
    const double s = a + b;
    const double e = b - (s - a);
    return {s, e};
}

// the value itself when an infinity or a NaN appears : no error term
DoubleDouble checked(DoubleDouble r, double plain)
{
    if (!std::isfinite(r.hi) || !std::isfinite(r.lo)) return {plain, 0.0};
    return r;
}

}  // namespace

DoubleDouble ddAdd(DoubleDouble x, DoubleDouble y)
{
    const DoubleDouble s = twoSum(x.hi, y.hi);
    const DoubleDouble t = twoSum(x.lo, y.lo);
    DoubleDouble       r = fastTwoSum(s.hi, s.lo + t.hi);
    r                    = fastTwoSum(r.hi, r.lo + t.lo);
    return checked(r, x.hi + y.hi);
}

DoubleDouble ddSub(DoubleDouble x, DoubleDouble y)
{
    return ddAdd(x, {-y.hi, -y.lo});
}

DoubleDouble ddMul(DoubleDouble x, DoubleDouble y)
{
    const double p = x.hi * y.hi;
    double       e = std::fma(x.hi, y.hi, -p);  // the exact error of the product
    e              = std::fma(x.hi, y.lo, e);
    e              = std::fma(x.lo, y.hi, e);
    return checked(fastTwoSum(p, e), x.hi * y.hi);
}

DoubleDouble ddDiv(DoubleDouble x, DoubleDouble y)
{
    const double q1 = x.hi / y.hi;
    // the remainder x - q1 * y, its leading part exact through a fused multiply-add
    double r = std::fma(-q1, y.hi, x.hi);
    r        = r + x.lo;
    r        = std::fma(-q1, y.lo, r);
    const double q2 = r / y.hi;
    return checked(fastTwoSum(q1, q2), x.hi / y.hi);
}

}  // namespace itv
