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
#include "directed_rounding.hh"

#include <algorithm>
#include <cmath>
#include <limits>
#include "cxx_compat.hh"
#include <cfenv>
#include <cstdint>

#include "reference_math.hh"

namespace itv::detail {
namespace {

static_assert(std::numeric_limits<double>::is_iec559 &&
              std::numeric_limits<double>::digits == 53 &&
              std::numeric_limits<double>::max_exponent == 1024,
              "Directed double bounds require IEEE binary64 storage.");

// Locate extrema with enclosing pi and directed elementary arithmetic. If large
// phases cannot distinguish neighbouring integers, include the critical point.
bool containsPiLattice(double lo, double hi, double offset, unsigned period)
{
    if (!std::isfinite(lo) || !std::isfinite(hi)) return true;
    const double piLo = directedPi(Direction::Down), piHi = directedPi(Direction::Up);
    double lower = directedBinary(BinaryOp::Div, lo, lo < 0 ? piLo : piHi, Direction::Down);
    double upper = directedBinary(BinaryOp::Div, hi, hi < 0 ? piHi : piLo, Direction::Up);
    lower = directedBinary(BinaryOp::Sub, lower, offset, Direction::Down);
    upper = directedBinary(BinaryOp::Sub, upper, offset, Direction::Up);
    lower = directedBinary(BinaryOp::Div, lower, period, Direction::Down);
    upper = directedBinary(BinaryOp::Div, upper, period, Direction::Up);
    if (std::abs(lower) >= 0x1p52 || std::abs(upper) >= 0x1p52) return true;
    return std::ceil(lower) <= std::floor(upper);
}

// Two 64-bit limbs hold the exact product of binary64's 53-bit significands.
// This avoids a hardware FMA requirement and a residual that can underflow to 0.
struct Wide {
    uint64_t hi = 0, lo = 0;
    int bits() const { return hi ? 128 - compat::countl_zero(hi) : 64 - compat::countl_zero(lo); }
};

Wide product(uint64_t a, uint64_t b)
{
    const uint64_t mask = UINT64_C(0xffffffff);
    const uint64_t low = (a & mask) * (b & mask);
    const uint64_t middle = (a >> 32) * (b & mask) + (low >> 32);
    const uint64_t other = (a & mask) * (b >> 32) + (middle & mask);
    return {(a >> 32) * (b >> 32) + (middle >> 32) + (other >> 32),
            (other << 32) | (low & mask)};
}

Wide shifted(Wide x, int n)
{
    if (n == 0) return x;
    if (n >= 64) return {x.lo << (n - 64), 0};
    return {(x.hi << n) | (x.lo >> (64 - n)), x.lo << n};
}

// A finite double is an exact signed integer significand times a power of two.
// Exponents remain unrestricted here, so products cannot underflow or overflow.
struct Dyadic { Wide significand; int exponent; bool negative; };

Dyadic dyadic(double x)
{
    const uint64_t bits = compat::bit_cast<uint64_t>(x);
    const int exponent = int((bits >> 52) & 0x7ff);
    const uint64_t fraction = bits & UINT64_C(0xfffffffffffff);
    return {{0, fraction | (exponent ? UINT64_C(0x10000000000000) : 0)},
            exponent ? exponent - 1075 : -1074, bool(bits >> 63)};
}

Dyadic multiplied(double x, double y)
{
    const Dyadic a = dyadic(x), b = dyadic(y);
    return {product(a.significand.lo, b.significand.lo), a.exponent + b.exponent,
            a.negative != b.negative};
}

int compareMagnitude(Dyadic a, Dyadic b)
{
    const int na = a.significand.bits(), nb = b.significand.bits();
    if (!na || !nb) return (na > 0) - (nb > 0);
    const int ea = a.exponent + na, eb = b.exponent + nb;
    if (ea != eb) return ea > eb ? 1 : -1;
    // Equal leading exponents need at most 105 bits of alignment, all within
    // the two limbs. No lossy floating subtraction is used for this comparison.
    a.significand = shifted(a.significand, std::max(0, nb - na));
    b.significand = shifted(b.significand, std::max(0, na - nb));
    if (a.significand.hi != b.significand.hi)
        return a.significand.hi > b.significand.hi ? 1 : -1;
    return (a.significand.lo > b.significand.lo) - (a.significand.lo < b.significand.lo);
}

int compare(Dyadic a, Dyadic b)
{
    if (!a.significand.bits()) a.negative = false;
    if (!b.significand.bits()) b.negative = false;
    if (a.negative != b.negative) return a.negative ? -1 : 1;
    const int magnitude = compareMagnitude(a, b);
    return a.negative ? -magnitude : magnitude;
}

// Compare an exact finite dyadic with a rounded double, including overflow.
int compare(Dyadic exact, double rounded)
{
    if (std::isinf(rounded)) return rounded > 0 ? -1 : 1;
    return compare(exact, dyadic(rounded));
}

double adjusted(double rounded, int exactMinusRounded, Direction direction)
{
    if ((direction == Direction::Down && exactMinusRounded < 0) ||
        (direction == Direction::Up && exactMinusRounded > 0))
        return std::nextafter(rounded, direction == Direction::Down ? -HUGE_VAL : HUGE_VAL);
    return rounded;
}

// A neighbour in the requested direction is safe in every IEEE rounding mode.
// It is used only when an exact residual is unavailable (notably non-nearest sums).
double widened(double rounded, Direction direction)
{
    return std::nextafter(rounded, direction == Direction::Down ? -HUGE_VAL : HUGE_VAL);
}

bool nearestMode()
{
#ifdef __EMSCRIPTEN__
    return true; // WebAssembly scalar arithmetic has a fixed nearest-even mode.
#else
    return std::fegetround() == FE_TONEAREST;
#endif
}

// Reference series produce both directions together. Reuse their enclosure
// rather than evaluating the same polynomial again for each bound of a point.
NumericBounds scalarBounds(UnaryOp op, double x)
{
    if (op == UnaryOp::Sqrt)
        return {directedUnary(op, x, Direction::Down), directedUnary(op, x, Direction::Up)};
    return referenceUnary(op, x);
}

interval positivePower(double lo, double hi, double elo, double ehi, int lsb)
{
    double lower = HUGE_VAL, upper = -HUGE_VAL;
    for (double base : {lo, hi}) {
        for (double exponent : {elo, ehi}) {
            const NumericBounds value = referenceBinary(BinaryOp::Pow, base, exponent);
            const double a = value.lo, b = value.hi;
            // Indeterminate extended-real corners must not discard finite values
            // attained inside the rectangle (e.g. 1^inf or inf^0).
            if (std::isnan(a) || std::isnan(b)) return {0, HUGE_VAL, lsb};
            lower = std::min(lower, a);
            upper = std::max(upper, b);
        }
    }
    return {lower, upper, lsb};
}

}  // namespace

// Internal kernel: exact residual/comparison chooses whether the rounded result
// needs its neighbouring double. Invalid operations give NaN; fenv is unchanged.
double directedBinary(BinaryOp op, double x, double y, Direction direction)
{
    if (op != BinaryOp::Add && op != BinaryOp::Sub && op != BinaryOp::Mul && op != BinaryOp::Div) {
        const NumericBounds bounds = referenceBinary(op, x, y);
        return direction == Direction::Down ? bounds.lo : bounds.hi;
    }
    if (op == BinaryOp::Sub) y = -y;
    if (op == BinaryOp::Add || op == BinaryOp::Sub) {
        const double r = x + y;
        if (!std::isfinite(x) || !std::isfinite(y) || std::isnan(r)) return r;
        if (!std::isfinite(r) || !nearestMode()) return widened(r, direction);
        // TwoSum recovers the exact addition residual, including subnormals.
        const double z = r - x;
        const double error = (x - (r - z)) + (y - z);
        if (!std::isfinite(error)) return widened(r, direction);
        return adjusted(r, (error > 0) - (error < 0), direction);
    }
    if (op == BinaryOp::Mul) {
        const double r = x * y;
        if (!std::isfinite(x) || !std::isfinite(y) || std::isnan(r)) return r;
        return adjusted(r, compare(multiplied(x, y), r), direction);
    }
    const double r = x / y;
    if (!std::isfinite(x) || !std::isfinite(y) || y == 0 || std::isnan(r)) return r;
    // sign(x/y - r) = sign(x - r*y) * sign(y). Infinite rounded quotients
    // still bracket a finite exact quotient with max-finite on the inner side.
    if (std::isinf(r)) return widened(r, direction);
    const int residual = compare(dyadic(x), multiplied(r, y));
    return adjusted(r, y < 0 ? -residual : residual, direction);
}

// Internal kernel: TwoSum gives the exact sum r + error, r = x + y rounded to nearest in
// binary64. In double, r is the program's sum. In float, rounding r to binary32 rounds
// the exact sum the same way, unless r lies exactly at the midpoint of two floats : the
// sign of the residual then decides (ties to even when there is none, as the cast does).
double nearestSum(double x, double y, Direction fallback)
{
    const double r = x + y;
    if (!std::isfinite(x) || !std::isfinite(y) || std::isnan(r)) return r;
    if (!nearestMode()) return directedBinary(BinaryOp::Add, x, y, fallback);
    if (programPrecision() != 1 || !std::isfinite(r)) return programPrecision() == 1 ? double(float(r)) : r;
    const double z     = r - x;
    const double error = (x - (r - z)) + (y - z);
    const float  f     = static_cast<float>(r);
    if (error == 0 || double(f) == r || !std::isfinite(f)) return f;
    const float  below = double(f) < r ? f : std::nextafter(f, -HUGE_VALF);
    const float  above = std::nextafter(below, HUGE_VALF);
    const double mid   = (double(below) + double(above)) / 2;
    if (r != mid) return f;
    return error > 0 ? above : below;
}

// Internal kernel: sqrt is correctly rounded; an exact significand comparison
// with r*r determines the outward neighbour without trusting an underflowed FMA.
double directedUnary(UnaryOp op, double x, Direction direction)
{
    if (op != UnaryOp::Sqrt) {
        const NumericBounds bounds = referenceUnary(op, x);
        return direction == Direction::Down ? bounds.lo : bounds.hi;
    }
    const double r = std::sqrt(x);
    if (!std::isfinite(x) || std::isnan(r)) return r;
    return adjusted(r, compare(dyadic(x), multiplied(r, r)), direction);
}

// Internal kernel: scaling changes only the exact dyadic exponent. Comparing
// with scalbn's rounded result covers gradual underflow and finite overflow.
double directedScale(double x, int exponent, Direction direction)
{
    const double r = std::scalbn(x, exponent);
    if (!std::isfinite(x) || x == 0) return r;
    Dyadic exact = dyadic(x);
    exact.exponent += exponent;
    return adjusted(r, compare(exact, r), direction);
}

// Precomputed neighbouring binary64 values straddle mathematical pi. These
// hexadecimal constants are also verified by the optional MPFR oracle.
double directedPi(Direction direction)
{
    return direction == Direction::Down ? 0x1.921fb54442d18p+1 : 0x1.921fb54442d19p+1;
}

// Numeric image on the valid real domain; endpoint evaluation is supplemented by
// all interior extrema/poles. LSB remains an estimate, not part of this proof.
interval doubleUnaryBounds(UnaryOp op, const interval& input)
{
    const interval x = floatingOperand(input);
    if (x.isEmpty()) return empty();
    double lo = x.lo(), hi = x.hi();
    const int lsb = std::min(x.lsb(), -24);
    switch (op) {
        case UnaryOp::Sqrt: case UnaryOp::Log: case UnaryOp::Log10:
            if (hi < 0) return empty();
            lo = std::max(lo, 0.0);
            break;
        case UnaryOp::Acosh:
            if (hi < 1) return empty();
            lo = std::max(lo, 1.0);
            break;
        case UnaryOp::Acos: case UnaryOp::Asin: case UnaryOp::Atanh:
            if (hi < -1 || lo > 1) return empty();
            lo = std::max(lo, -1.0);
            hi = std::min(hi, 1.0);
            break;
        default: break;
    }
    if (op == UnaryOp::Sin || op == UnaryOp::Cos || op == UnaryOp::Tan) {
        // Infinities are invalid trigonometric arguments. An unbounded interval
        // still contains finite arguments, whose image must remain represented.
        if (lo == hi && std::isinf(lo)) return empty();
        if (op == UnaryOp::Tan && containsPiLattice(lo, hi, 0.5, 1))
            return {-HUGE_VAL, HUGE_VAL, lsb};
        if (!std::isfinite(lo) || !std::isfinite(hi)) return {-1, 1, lsb};
        const NumericBounds a = scalarBounds(op, lo), b = lo == hi ? a : scalarBounds(op, hi);
        double lower = std::min(a.lo, b.lo), upper = std::max(a.hi, b.hi);
        if (op == UnaryOp::Sin) {
            if (containsPiLattice(lo, hi, 0.5, 2)) upper = 1;
            if (containsPiLattice(lo, hi, -0.5, 2)) lower = -1;
        } else if (op == UnaryOp::Cos) {
            if (containsPiLattice(lo, hi, 0, 2)) upper = 1;
            if (containsPiLattice(lo, hi, 1, 2)) lower = -1;
        }
        return {lower, upper, lsb};
    }
    if (op == UnaryOp::Cosh) {
        const NumericBounds a = scalarBounds(op, lo), b = lo == hi ? a : scalarBounds(op, hi);
        return {x.hasZero() ? 1 : std::min(a.lo, b.lo), std::max(a.hi, b.hi), lsb};
    }
    if (op == UnaryOp::Acos) std::swap(lo, hi); // decreasing on [-1, 1]
    const NumericBounds a = scalarBounds(op, lo), b = lo == hi ? a : scalarBounds(op, hi);
    return {a.lo, b.hi, lsb};
}

// Numeric atan2 image. Rectangular extrema are corners except at the negative
// x-axis cut or the origin; include both signs of pi whenever that cut is possible.
interval doubleAtan2Bounds(const interval& yInput, const interval& xInput)
{
    const interval y = floatingOperand(yInput), x = floatingOperand(xInput);
    if (x.isEmpty() || y.isEmpty()) return empty();
    const int lsb = std::min({x.lsb(), y.lsb(), -24});
    if (x.lo() <= 0 && y.hasZero()) {
        const double pi = directedPi(Direction::Up);
        return {-pi, pi, lsb};
    }
    double lower = HUGE_VAL, upper = -HUGE_VAL;
    for (double a : {y.lo(), y.hi()}) {
        for (double b : {x.lo(), x.hi()}) {
            const NumericBounds value = referenceBinary(BinaryOp::Atan2, a, b);
            lower = std::min(lower, value.lo);
            upper = std::max(upper, value.hi);
        }
    }
    return {lower, upper, lsb};
}

// Numeric pow image. Positive bases use monotonicity in each coordinate (the
// direction changes at base 1/exponent 0, but their value 1 is covered by corners).
// Negative bases contribute only integer exponents, separated by parity.
interval doublePowBounds(const interval& xInput, const interval& yInput)
{
    const interval x = floatingOperand(xInput), y = floatingOperand(yInput);
    if (x.isEmpty() || y.isEmpty()) return empty();
    const int lsb = std::min({x.lsb(), y.lsb(), -24});
    // The interval representation merges signed zero. Negative powers of -0
    // can be -inf for odd integral exponents; keep both signs in either precision.
    if (x.hasZero() && y.lo() < 0)
        return {-HUGE_VAL, HUGE_VAL, lsb};
    interval result = empty();
    if (x.hi() >= 0) result = positivePower(std::max(0.0, x.lo()), x.hi(), y.lo(), y.hi(), lsb);
    // IEEE pow also defines some noninteger powers of -inf, although the
    // corresponding finite negative bases have no real image. Keep those numeric
    // exceptional results instead of dropping the infinite endpoint entirely.
    if (x.lo() == -HUGE_VAL) {
        if (y.hi() > 0) result = reunion(result, interval(-HUGE_VAL, HUGE_VAL, lsb));
        if (y.lo() < 0) result = reunion(result, interval(0, 0, lsb));
        if (y.hasZero()) result = reunion(result, interval(1, 1, lsb));
    }
    if (x.lo() < 0) {
        double first = std::ceil(y.lo()), last = std::floor(y.hi());
        if (first <= last) {
            // Beyond 2^53, binary64 cannot distinguish neighbouring integer
            // parities. An unrestricted hull is preferable to dropping a sign.
            if (!std::isfinite(first) || !std::isfinite(last) ||
                std::abs(first) >= 0x1p53 || std::abs(last) >= 0x1p53)
                return {-HUGE_VAL, HUGE_VAL, lsb};
            for (int parity : {0, 1}) {
                const double a = first + (int(uint64_t(std::abs(first)) & 1) == parity ? 0 : 1);
                const double b = last - (int(uint64_t(std::abs(last)) & 1) == parity ? 0 : 1);
                if (a > b) continue;
                const interval magnitude = positivePower(std::max(0.0, -x.hi()), -x.lo(), a, b, lsb);
                result = reunion(result, parity == 0 ? magnitude
                                                    : interval(-magnitude.hi(), -magnitude.lo(), lsb));
            }
        }
    }
    return result;
}

// Numeric fmod image. The sign follows x and |fmod| <= min(|x|, |y|); this
// deliberately avoids a rounded quotient and an unsafe conversion to int.
interval doubleFmodBounds(const interval& xInput, const interval& yInput)
{
    const interval x = floatingOperand(xInput), y = floatingOperand(yInput);
    if (x.isEmpty() || y.isEmpty() || y.isZero()) return empty();
    const int lsb = std::min({x.lsb(), y.lsb(), -24});
    if (x.isconst() && y.isconst()) {
        const NumericBounds value = referenceBinary(BinaryOp::Fmod, x.lo(), y.lo());
        return {value.lo, value.hi, lsb};
    }
    // fmod is exact, and its result, a value of the program, is strictly below |y| : at
    // most the program's float that precedes the largest |y| (frac(z) = fmod(z, 1) for a
    // nonnegative z is then [0, 1[, as frac's own bound)
    const double ymax  = std::max(std::abs(y.lo()), std::abs(y.hi()));
    double       below = ymax;
    if (std::isfinite(ymax)) {
        if (programPrecision() == 1) {
            const float yf = float(ymax);
            if (double(yf) == ymax) below = double(std::nextafter(yf, 0.0f));
        } else {
            below = std::nextafter(ymax, 0.0);
        }
    }
    const double magnitude = std::min(std::max(std::abs(x.lo()), std::abs(x.hi())), below);
    return {x.lo() >= 0 ? 0 : -magnitude, x.hi() <= 0 ? 0 : magnitude, lsb};
}

}  // namespace itv::detail
