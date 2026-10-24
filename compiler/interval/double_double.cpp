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
#include <cfloat>

// The error-free transformations and the directed bounds assume that each double operation
// rounds once, to a double : an extended evaluation (x87, FLT_EVAL_METHOD 1 or 2) keeps
// intermediates wider and rounds them twice.
#if !defined(FLT_EVAL_METHOD) || FLT_EVAL_METHOD != 0
#error "the interval library needs FLT_EVAL_METHOD == 0 (SSE2 on x86 : -msse2 -mfpmath=sse)"
#endif

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

DoubleDouble scaled(DoubleDouble x, int e)
{
    return {std::ldexp(x.hi, e), std::ldexp(x.lo, e)};
}

bool finite(DoubleDouble x)
{
    return std::isfinite(x.hi) && std::isfinite(x.lo);
}

// the result of an operation whose plain form on hi is plain : an exact zero takes the sign
// of the plain operation (-0 + -0, -1 * 0) ; a non-finite operand gives the plain result
DoubleDouble zeroSigned(DoubleDouble r, double plain)
{
    if (r.hi == 0) return {plain == 0 ? plain : 0.0, 0.0};
    return r;
}

// an intermediate that overflows although the value may not : the operation again on
// operands scaled down by 2^e (exact), its result scaled back ; a value that does not fit is
// an infinity
template <typename Op>
DoubleDouble rescaled(Op op, DoubleDouble x, DoubleDouble y, int ex, int ey, int back, double plain)
{
    const DoubleDouble r  = op(scaled(x, -ex), scaled(y, -ey));
    const double       hi = std::ldexp(r.hi, back);
    if (!std::isfinite(hi)) return {std::isnan(hi) ? plain : hi, 0.0};
    return {hi, std::ldexp(r.lo, back)};
}

DoubleDouble addCore(DoubleDouble x, DoubleDouble y)
{
    const DoubleDouble s = twoSum(x.hi, y.hi);
    const DoubleDouble t = twoSum(x.lo, y.lo);
    DoubleDouble       r = fastTwoSum(s.hi, s.lo + t.hi);
    return fastTwoSum(r.hi, r.lo + t.lo);
}

DoubleDouble mulCore(DoubleDouble x, DoubleDouble y)
{
    const double p = x.hi * y.hi;
    double       e = std::fma(x.hi, y.hi, -p);  // the exact error of the product
    e              = std::fma(x.hi, y.lo, e);
    e              = std::fma(x.lo, y.hi, e);
    return fastTwoSum(p, e);
}

DoubleDouble divCore(DoubleDouble x, DoubleDouble y)
{
    const double q1 = x.hi / y.hi;
    // the remainder x - q1 * y, its leading part exact through a fused multiply-add
    double r = std::fma(-q1, y.hi, x.hi);
    r        = r + x.lo;
    r        = std::fma(-q1, y.lo, r);
    const double q2 = r / y.hi;
    return fastTwoSum(q1, q2);
}

// below 2^-969 (2^53 times the smallest normal), the error terms of a product or a quotient
// are subnormal and no longer exact : the plain operation, correctly rounded, is closer
constexpr double kTiny = 0x1p-969;

}  // namespace

DoubleDouble ddAdd(DoubleDouble x, DoubleDouble y)
{
    const double plain = x.hi + y.hi;
    if (!finite(x) || !finite(y)) return {plain, 0.0};
    const DoubleDouble r = addCore(x, y);
    if (!finite(r)) return rescaled(addCore, x, y, 2, 2, 2, plain);
    return zeroSigned(r, plain);
}

DoubleDouble ddSub(DoubleDouble x, DoubleDouble y)
{
    return ddAdd(x, {-y.hi, -y.lo});
}

DoubleDouble ddMul(DoubleDouble x, DoubleDouble y)
{
    const double plain = x.hi * y.hi;
    if (!finite(x) || !finite(y)) return {plain, 0.0};
    const DoubleDouble r = mulCore(x, y);
    if (!finite(r)) return rescaled(mulCore, x, y, 4, 0, 4, plain);
    if (std::abs(r.hi) < kTiny) return {plain, 0.0};
    return zeroSigned(r, plain);
}

DoubleDouble ddDiv(DoubleDouble x, DoubleDouble y)
{
    const double plain = x.hi / y.hi;
    if (!finite(x) || !finite(y) || y.hi == 0) return {plain, 0.0};
    const DoubleDouble r = divCore(x, y);
    if (!finite(r)) return rescaled(divCore, x, y, 4, 0, 4, plain);
    if (std::abs(r.hi) < kTiny) return {plain, 0.0};
    return zeroSigned(r, plain);
}

float ddToFloat(DoubleDouble x)
{
    const float f = static_cast<float>(x.hi);
    if (x.lo == 0 || !std::isfinite(x.hi)) return f;
    // hi rounds alone, unless it lies halfway between two floats : lo then says on which side
    // the value lies (the conversion broke the tie to even)
    if (std::isinf(f)) {
        // the tie between the largest float and the next power of two (0x1.ffffffp+127)
        const double mid = std::copysign(0x1.ffffffp+127, x.hi);
        return (x.hi == mid && (x.lo < 0) == (x.hi > 0)) ? std::copysign(FLT_MAX, x.hi) : f;
    }
    const double gap   = static_cast<double>(f) - x.hi;  // exact
    const float  other = std::nextafter(f, gap > 0 ? -HUGE_VALF : HUGE_VALF);
    if (gap != 0 && static_cast<double>(other) - x.hi == -gap) {
        return ((x.lo > 0) == (other > f)) ? other : f;
    }
    return f;
}

}  // namespace itv
