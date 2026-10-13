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
#include "reference_math.hh"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>

namespace itv::detail {
namespace {

using Bounds = NumericBounds;

// Precomputed outward binary64 constants, rather than nearest-rounded literals
// treated as exact mathematical values. The MPFR oracle checks these enclosures.
constexpr Bounds ln2{0x1.62e42fefa39efp-1, 0x1.62e42fefa39f0p-1};
constexpr Bounds ln10{0x1.26bb1bbb55515p+1, 0x1.26bb1bbb55516p+1};

Bounds point(double x) { return {x, x}; }
Bounds invalid() { return {NAN, NAN}; }
Bounds entire() { return {-HUGE_VAL, HUGE_VAL}; }
Bounds pi() { return {directedPi(Direction::Down), directedPi(Direction::Up)}; }
Bounds neg(Bounds x) { return {-x.hi, -x.lo}; }

double down(BinaryOp op, double x, double y) { return directedBinary(op, x, y, Direction::Down); }
double up(BinaryOp op, double x, double y) { return directedBinary(op, x, y, Direction::Up); }

// These small interval helpers have no LSB/type conversion or target-libm margin.
// Every intermediate rounding is included, including the remainder calculation.
Bounds add(Bounds x, Bounds y) { return {down(BinaryOp::Add, x.lo, y.lo), up(BinaryOp::Add, x.hi, y.hi)}; }
Bounds sub(Bounds x, Bounds y) { return add(x, neg(y)); }
// Sign monotonicity selects the extremal corners directly. Only two intervals
// straddling zero need all four products; scalar series terms usually need two.
Bounds mul(Bounds x, Bounds y)
{
    if (std::isnan(x.lo) || std::isnan(y.lo)) return invalid();
    const auto pair = [](double a, double b, double c, double d) -> Bounds {
        return {(a == 0 || b == 0) ? 0 : down(BinaryOp::Mul, a, b),
                (c == 0 || d == 0) ? 0 : up(BinaryOp::Mul, c, d)};
    };
    if (x.lo >= 0) {
        if (y.lo >= 0) return pair(x.lo, y.lo, x.hi, y.hi);
        if (y.hi <= 0) return pair(x.hi, y.lo, x.lo, y.hi);
        return pair(x.hi, y.lo, x.hi, y.hi);
    }
    if (x.hi <= 0) {
        if (y.lo >= 0) return pair(x.lo, y.hi, x.hi, y.lo);
        if (y.hi <= 0) return pair(x.hi, y.hi, x.lo, y.lo);
        return pair(x.lo, y.hi, x.lo, y.lo);
    }
    if (y.lo >= 0) return pair(x.lo, y.hi, x.hi, y.hi);
    if (y.hi <= 0) return pair(x.hi, y.lo, x.lo, y.lo);
    const Bounds a = pair(x.lo, y.hi, x.lo, y.lo);
    const Bounds b = pair(x.hi, y.lo, x.hi, y.hi);
    return {std::min(a.lo, b.lo), std::max(a.hi, b.hi)};
}

// Division by a positive corridor is monotone in each sign region. Computing
// quotients directly avoids both reciprocal rounding and extra series work.
Bounds div(Bounds x, Bounds y)
{
    if (std::isnan(x.lo) || std::isnan(y.lo)) return invalid();
    if (y.lo <= 0 && y.hi >= 0) return entire();
    if (y.hi < 0) return div(neg(x), neg(y));
    const double lower = down(BinaryOp::Div, x.lo, x.lo < 0 ? y.lo : y.hi);
    const double upper = up(BinaryOp::Div, x.hi, x.hi > 0 ? y.lo : y.hi);
    if (std::isnan(lower) || std::isnan(upper)) return entire();
    return {lower, upper};
}
Bounds scale(Bounds x, int exponent)
{
    return {directedScale(x.lo, exponent, Direction::Down),
            directedScale(x.hi, exponent, Direction::Up)};
}
Bounds root(Bounds x)
{
    return {directedUnary(UnaryOp::Sqrt, std::max(0.0, x.lo), Direction::Down),
            directedUnary(UnaryOp::Sqrt, std::max(0.0, x.hi), Direction::Up)};
}
double magnitude(Bounds x) { return std::max(std::abs(x.lo), std::abs(x.hi)); }
Bounds withTail(Bounds x, double tail) { return add(x, {-tail, tail}); }

// exp(x) = 2^k exp(r), with an enclosing ln(2) used to construct r. For |r|<=1,
// the tail after degree 32 is at most 3 times the absolute degree-33 term (e<3).
// Scaling compares exact dyadic exponents, so it also covers subnormal results.
Bounds exponential(double x)
{
    if (x == 0) return point(1);
    if (x == HUGE_VAL) return point(HUGE_VAL);
    if (x == -HUGE_VAL) return point(0);
    if (x >= 1024) return {std::numeric_limits<double>::max(), HUGE_VAL};
    if (x <= -1024) return {0, std::numeric_limits<double>::denorm_min()};
    const int k = int(std::floor(x / ln2.lo)); // bounded choice, not a proof of reduction
    const Bounds r = sub(point(x), mul(point(k), ln2));
    if (magnitude(r) > 1) return {0, HUGE_VAL};
    Bounds term = point(1), sum = term;
    for (int n = 1; n <= 32; ++n) {
        term = div(mul(term, r), point(n));
        sum = add(sum, term);
    }
    const double tail = up(BinaryOp::Mul, 3, magnitude(div(mul(term, r), point(33))));
    sum = withTail(sum, tail);
    sum.lo = std::max(0.0, sum.lo);
    return scale(sum, k);
}

// For m in [1,2), z=(m-1)/(m+1) lies in [0,1/3]. The atanh series gives
// log(m)=2*(z+z^3/3+...), and its positive tail is bounded by a geometric series.
// frexp is exact even for subnormals; no approximate host logarithm is used.
Bounds logarithm(double x)
{
    if (x < 0) return invalid();
    if (x == 0) return point(-HUGE_VAL);
    if (x == 1) return point(0);
    if (x == HUGE_VAL) return point(HUGE_VAL);
    int exponent;
    const double m = 2 * std::frexp(x, &exponent);
    --exponent;
    const Bounds z = div(sub(point(m), point(1)), add(point(m), point(1)));
    const Bounds zz = mul(z, z);
    Bounds term = z, sum = z;
    for (int n = 1; n < 32; ++n) {
        term = mul(term, zz);
        sum = add(sum, div(term, point(2 * n + 1)));
    }
    const Bounds tail = div(mul(point(2), mul(term, zz)),
                            mul(point(65), sub(point(1), zz)));
    Bounds value = mul(point(2), sum);
    value.hi = up(BinaryOp::Add, value.hi, tail.hi);
    value = add(value, mul(point(exponent), ln2));
    if (x > 1) value.lo = std::max(0.0, value.lo);
    else value.hi = std::min(0.0, value.hi);
    return value;
}

// Alternating atan series on |z|<=1/2. Its remainder is bounded by the first
// omitted term; the interval polynomial covers uncertainty in z itself.
Bounds atanSeries(Bounds z)
{
    const Bounds zz = neg(mul(z, z));
    Bounds term = z, sum = z;
    for (int n = 1; n < 32; ++n) {
        term = mul(term, zz);
        sum = add(sum, div(term, point(2 * n + 1)));
    }
    return withTail(sum, magnitude(div(mul(term, zz), point(65))));
}

Bounds arctangent(double x)
{
    if (x < 0) return neg(arctangent(-x));
    if (x == 0) return point(x);
    if (x == HUGE_VAL) return scale(pi(), -1);
    if (x > 1) {
        const Bounds reciprocal{down(BinaryOp::Div, 1, x), up(BinaryOp::Div, 1, x)};
        return sub(scale(pi(), -1),
                   {arctangent(reciprocal.lo).lo, arctangent(reciprocal.hi).hi});
    }
    Bounds value;
    if (x <= 0.5) value = atanSeries(point(x));
    else {
        const Bounds reduced = div(sub(point(x), point(1)), add(point(x), point(1)));
        value = add(scale(pi(), -2), atanSeries(reduced));
    }
    // Known signs survive tiny polynomial terms whose outward bounds underflow.
    return {std::max(0.0, value.lo), std::min(x, value.hi)};
}

Bounds atanBounds(Bounds x) { return {arctangent(x.lo).lo, arctangent(x.hi).hi}; }
Bounds logBounds(Bounds x) { return {logarithm(x.lo).lo, logarithm(x.hi).hi}; }

// A bounded quadrant integer makes reduction portable without a large table of
// pi digits. Huge inputs or uncertain reduction use the complete [-1,1] image.
// For |r|<=1 the alternating sin/cos tails are at most the first omitted terms.
Bounds trigonometric(double x, bool cosine)
{
    if (!std::isfinite(x)) return invalid();
    if (x == 0) return point(cosine ? 1 : x);
    if (std::abs(x) > 0x1p20) return {-1, 1};
    const int quadrant = int(std::round(x / 0x1.921fb54442d18p+0));
    const Bounds r = sub(point(x), mul(point(quadrant), scale(pi(), -1)));
    if (magnitude(r) > 1) return {-1, 1};
    const Bounds rr = neg(mul(r, r));
    Bounds st = r, ct = point(1), sine = st, cos = ct;
    for (int n = 1; n < 16; ++n) {
        st = div(mul(st, rr), point((2 * n) * (2 * n + 1)));
        ct = div(mul(ct, rr), point((2 * n) * (2 * n - 1)));
        sine = add(sine, st); cos = add(cos, ct);
    }
    sine = withTail(sine, magnitude(div(mul(st, rr), point(32 * 33))));
    cos = withTail(cos, magnitude(div(mul(ct, rr), point(32 * 31))));
    if (r.lo >= 0) sine.lo = std::max(0.0, sine.lo);
    if (r.hi <= 0) sine.hi = std::min(0.0, sine.hi);
    cos.lo = std::max(0.5, cos.lo); // cos(r)>=1-r^2/2>=1/2 on this reduction domain
    const int q = ((quadrant % 4) + 4) % 4;
    Bounds value;
    if (cosine) {
        value = q == 0 ? cos : q == 1 ? neg(sine) : q == 2 ? neg(cos) : sine;
    } else {
        value = q == 0 ? sine : q == 1 ? cos : q == 2 ? neg(sine) : neg(cos);
    }
    return {std::max(-1.0, value.lo), std::min(1.0, value.hi)};
}

// Inverse/hyperbolic functions reuse the same certified elementary bounds.
// Algebraic identities are chosen to avoid squaring large x or losing the
// domain of sqrt/log to cancellation. Mathematical signs/images tighten hulls.
Bounds arcsine(double x)
{
    if (std::abs(x) > 1) return invalid();
    if (x < 0) return neg(arcsine(-x));
    if (x == 0) return point(x);
    if (x == 1) return scale(pi(), -1);
    const Bounds denominator = root(mul(sub(point(1), point(x)), add(point(1), point(x))));
    const Bounds ratio{down(BinaryOp::Div, x, denominator.hi), up(BinaryOp::Div, x, denominator.lo)};
    Bounds value = atanBounds(ratio);
    value.lo = std::max(x, value.lo); // asin(x)>=x on [0,1]
    return value;
}

Bounds hyperbolicSine(double x)
{
    if (x < 0) return neg(hyperbolicSine(-x));
    if (x == 0 || x == HUGE_VAL) return point(x);
    Bounds value = scale(sub(exponential(x), exponential(-x)), -1);
    value.lo = std::max(x, value.lo); // sinh(x)>=x for x>=0
    return value;
}
Bounds hyperbolicCosine(double x)
{
    if (std::isinf(x)) return point(HUGE_VAL);
    const double a = std::abs(x);
    if (a == 0) return point(1);
    Bounds value = scale(add(exponential(a), exponential(-a)), -1);
    value.lo = std::max(1.0, value.lo);
    return value;
}
Bounds hyperbolicTangent(double x)
{
    if (x < 0) return neg(hyperbolicTangent(-x));
    if (x == 0) return point(x);
    if (x == HUGE_VAL) return point(1);
    if (x > 1024) return {std::nextafter(1.0, 0.0), 1};
    const Bounds e = exponential(-2 * x);
    Bounds value = div(sub(point(1), e), add(point(1), e));
    return {std::max(0.0, value.lo), std::min({x, 1.0, value.hi})};
}
Bounds inverseHyperbolicSine(double x)
{
    if (x < 0) return neg(inverseHyperbolicSine(-x));
    if (x == 0 || x == HUGE_VAL) return point(x);
    Bounds value;
    if (x > 1) {
        const Bounds inverse{down(BinaryOp::Div, 1, x), up(BinaryOp::Div, 1, x)};
        value = add(logarithm(x), logBounds(add(point(1), root(add(point(1), mul(inverse, inverse))))));
    } else {
        value = logBounds(add(point(x), root(add(point(1), mul(point(x), point(x))))));
    }
    return {std::max(0.0, value.lo), std::min(x, value.hi)};
}
Bounds inverseHyperbolicCosine(double x)
{
    if (x < 1) return invalid();
    if (x == 1) return point(0);
    if (x == HUGE_VAL) return point(x);
    const Bounds inverse{down(BinaryOp::Div, 1, x), up(BinaryOp::Div, 1, x)};
    Bounds value = add(logarithm(x), logBounds(add(point(1), root(sub(point(1), mul(inverse, inverse))))));
    value.lo = std::max(0.0, value.lo);
    return value;
}
Bounds inverseHyperbolicTangent(double x)
{
    if (std::abs(x) > 1) return invalid();
    if (x < 0) return neg(inverseHyperbolicTangent(-x));
    if (x == 0) return point(x);
    if (x == 1) return point(HUGE_VAL);
    Bounds value = scale(sub(logBounds(add(point(1), point(x))),
                             logBounds(sub(point(1), point(x)))), -1);
    value.lo = std::max(x, value.lo);
    return value;
}

Bounds angle(double y, double x)
{
    if (x == 0) {
        if (y == 0) return std::signbit(x) ? (std::signbit(y) ? neg(pi()) : pi()) : point(y);
        return y < 0 ? neg(scale(pi(), -1)) : scale(pi(), -1);
    }
    Bounds value;
    if (std::isinf(y) && std::isinf(x)) {
        value = scale(pi(), -2);
    } else if (std::isinf(y)) {
        return y < 0 ? neg(scale(pi(), -1)) : scale(pi(), -1);
    } else {
        value = atanBounds({down(BinaryOp::Div, std::abs(y), std::abs(x)),
                            up(BinaryOp::Div, std::abs(y), std::abs(x))});
    }
    if (x < 0) value = sub(pi(), value);
    return std::signbit(y) ? neg(value) : value;
}

Bounds integerPower(double x, double exponent)
{
    if (exponent == 0 || x == 1) return point(1);
    if (x == -1) return point(std::abs(exponent) >= 0x1p53 ||
                              (uint64_t(std::abs(exponent)) & 1) == 0 ? 1 : -1);
    if (std::abs(exponent) >= 0x1p53) return x < 0 ? entire() : Bounds{0, HUGE_VAL};
    uint64_t n = uint64_t(std::abs(exponent));
    const bool negative = x < 0 && (n & 1);
    Bounds result = point(1), base = point(std::abs(x));
    while (n) {
        if (n & 1) result = mul(result, base);
        n >>= 1;
        if (n) base = mul(base, base);
    }
    if (exponent < 0) result = {down(BinaryOp::Div, 1, result.hi), up(BinaryOp::Div, 1, result.lo)};
    return negative ? neg(result) : result;
}

Bounds power(double x, double y)
{
    if (y == 0 || x == 1) return point(1);
    if (std::isinf(y)) {
        if (std::abs(x) == 1) return point(1);
        return point((std::abs(x) > 1) == (y > 0) ? HUGE_VAL : 0);
    }
    if (std::isinf(x)) {
        if (x < 0 && y == std::floor(y)) return integerPower(x, y);
        return point(y > 0 ? HUGE_VAL : 0);
    }
    if (y == std::floor(y)) return integerPower(x, y);
    if (x < 0) return invalid();
    if (x == 0) return point(y > 0 ? 0 : HUGE_VAL);
    const Bounds exponent = mul(point(y), logarithm(x));
    return {exponential(exponent.lo).lo, exponential(exponent.hi).hi};
}

// Exact binary long division computes fmod and the quotient's parity without
// calling a libm or converting a huge rounded quotient to int. At most 2098
// shift/subtract steps are needed for finite binary64 inputs. The remainder is
// an exact multiple of denorm_min, so its final scaling is representable.
Bounds modulo(double x, double y, bool ieeeRemainder)
{
    if (y == 0 || std::isinf(x)) return invalid();
    if (std::isinf(y) || x == 0) return point(x);
    const double a = std::abs(x), b = std::abs(y);
    double result = a;
    bool odd = false;
    if (a >= b) {
        int ea, eb;
        uint64_t ma = uint64_t(std::scalbn(std::frexp(a, &ea), 53));
        const uint64_t mb = uint64_t(std::scalbn(std::frexp(b, &eb), 53));
        for (int n = ea - eb; n >= 0; --n) {
            odd = ma >= mb;
            if (odd) ma -= mb;
            if (n) ma <<= 1;
        }
        result = std::scalbn(double(ma), eb - 53);
    }
    if (ieeeRemainder) {
        // Dividing b by two could underflow. Normalized comparison of 2*r
        // with b avoids that, and ties use the exact quotient parity.
        int er, eb;
        const double mr = std::frexp(result, &er), mb = std::frexp(b, &eb);
        const bool above = result != 0 && (er + 1 > eb || (er + 1 == eb && mr > mb));
        const bool tie = result != 0 && er + 1 == eb && mr == mb;
        if (above || (tie && odd)) result -= b; // exact by Sterbenz, r in [b/2,b]
    }
    return point(std::signbit(x) ? -result : result);
}

}  // namespace

// Internal scalar reference: exact identities, outward interval series and
// analytic tails enclose the real function; target-libm errors remain separate.
NumericBounds referenceUnary(UnaryOp op, double x)
{
    if (std::isnan(x)) return invalid();
    switch (op) {
        case UnaryOp::Exp: return exponential(x);
        case UnaryOp::Log: return logarithm(x);
        case UnaryOp::Log10: return div(logarithm(x), ln10);
        case UnaryOp::Atan: return arctangent(x);
        case UnaryOp::Sin: return trigonometric(x, false);
        case UnaryOp::Cos: return trigonometric(x, true);
        case UnaryOp::Tan:
            if (!std::isfinite(x)) return invalid();
            return div(trigonometric(x, false), trigonometric(x, true));
        case UnaryOp::Asin: return arcsine(x);
        case UnaryOp::Acos:
            if (std::abs(x) > 1) return invalid();
            if (x == 1) return point(0);
            { Bounds value = sub(scale(pi(), -1), arcsine(x));
              value.lo = std::max(0.0, value.lo); return value; }
        case UnaryOp::Sinh: return hyperbolicSine(x);
        case UnaryOp::Cosh: return hyperbolicCosine(x);
        case UnaryOp::Tanh: return hyperbolicTangent(x);
        case UnaryOp::Asinh: return inverseHyperbolicSine(x);
        case UnaryOp::Acosh: return inverseHyperbolicCosine(x);
        case UnaryOp::Atanh: return inverseHyperbolicTangent(x);
        case UnaryOp::Sqrt: return x < 0 ? invalid() : root(point(x)); // normally handled by directedUnary
    }
    return entire();
}

// Internal binary reference: integer powers use bounded exponentiation;
// noninteger powers and angles reuse the scalar enclosures. Modulo is exact.
NumericBounds referenceBinary(BinaryOp op, double x, double y)
{
    if (std::isnan(x) || std::isnan(y)) return invalid();
    switch (op) {
        case BinaryOp::Pow: return power(x, y);
        case BinaryOp::Atan2: return angle(x, y);
        case BinaryOp::Fmod: return modulo(x, y, false);
        case BinaryOp::Remainder: return modulo(x, y, true);
        default: return entire(); // elementary operations belong to directedBinary
    }
}

}  // namespace itv::detail
