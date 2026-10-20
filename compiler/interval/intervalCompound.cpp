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
#include <cmath>

#include "directed_rounding.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {

//------------------------------------------------------------------------------------------
// The compound operations Frac, Cfrac, Mix, Tpt and Phase : each one is its definition, written once as
// an operation so that its repeated operand appears once. Evaluated as two independent
// values, x - floor(x) loses that the result lies in [0, 1] (the dependency problem).
//
// The bounds describe the program, which computes x once and then the operation : the
// subtraction of floor(x) or rint(x) is exact (Sterbenz : the rounded value is within a
// factor 2 of x, or 0), so the result lies in [0, 1[ (frac of x >= 0), [0, 1] (any x) or
// [-1/2, 1/2] (cfrac). One error is left : a compiler may contract the product computing x
// with the subtraction (fma(a, b, -floor(a * b))), reading x exactly on one side and
// rounded on the other ; the result may then leave its range by half an ulp of x. The
// bounds keep that margin.
//------------------------------------------------------------------------------------------

namespace {

/// the unit roundoff of the program (float for the precisions without one)
double unitRoundoff()
{
    return programPrecision() == 2 ? std::ldexp(1.0, -53) : std::ldexp(1.0, -24);
}

/// the largest program value below 1
double belowOne()
{
    if (programPrecision() == 1) return double(std::nextafter(1.0f, 0.0f));
    if (programPrecision() == 2) return std::nextafter(1.0, 0.0);
    return 1;
}

/// the smallest power of two M >= mag such that a mix of operands in [-M, M] stays in
/// [-M, M] (see numericMix), or 0 when the program has no such envelope : not a binary
/// floating-point format, or mag beyond its range (an ulp of M far above the subnormal
/// roundings, and M * (1 + 2u) finite)
double mixEnvelope(double mag)
{
    const int precision = programPrecision();
    if (precision != 1 && precision != 2) return 0;
    if (!(mag > 0) || !std::isfinite(mag)) return 0;
    int          e;
    const double f = std::frexp(mag, &e);
    const double M = (f == 0.5) ? mag : std::ldexp(1.0, e);
    const double lo = (precision == 1) ? std::ldexp(1.0, -126 + 24) : std::ldexp(1.0, -1022 + 53);
    const double hi = (precision == 1) ? std::ldexp(1.0, 126) : std::ldexp(1.0, 1022);
    return (M >= lo && M <= hi) ? M : 0;
}

/// half an ulp of the largest magnitude of x, plus the loss of a flush to zero
double contractionMargin(const interval& x)
{
    const double mag = std::max(std::abs(x.lo()), std::abs(x.hi()));
    return unitRoundoff() * mag * (1 + std::ldexp(1.0, -20)) + std::ldexp(1.0, -125);
}

/// x - round(x) for a rounding round (floor or rint) of range [lo, hi] when x spans
/// several cells ; [x.lo - r, x.hi - r] when x lies in the cell of the integer r
interval remainder(const interval& input, double (*round)(double), double lo, double hi)
{
    const interval x = detail::floatingOperand(input);
    if (x.isEmpty()) return empty();
    if (input.lsb() >= 0) return interval(0, 0, -1);  // an integer is its own rounding
    if (!std::isfinite(x.lo()) || !std::isfinite(x.hi())) return interval(lo, hi, -1);
    const double rl = round(x.lo()), rh = round(x.hi());
    double       a = lo, b = hi;
    if (rl == rh) {
        a = std::max(lo, detail::directedBinary(detail::BinaryOp::Sub, x.lo(), rl, detail::Direction::Down));
        b = std::min(hi, detail::directedBinary(detail::BinaryOp::Sub, x.hi(), rl, detail::Direction::Up));
    }
    const double d = contractionMargin(x);
    return interval(a - d, b + d, std::min(x.lsb(), -1));
}

double floorOf(double v)
{
    return std::floor(v);
}

double rintOf(double v)
{
    return std::rint(v);
}

}  // namespace

// The definitions, operation by operation
// mix(c, a, b) is computed as an interpolation from one of its operands (mixFromB) : the
// definition follows the operations of the program
interval interval_algebra::mixDefinition(const interval& c, const interval& a, const interval& b) const
{
    if (mixFromB(detail::floatingOperand(c))) {
        const interval w = Sub(FloatNum(1.0), c);
        const interval d = Sub(a, b);
        const interval p = Mul(w, d);
        return Add(b, p);
    }
    const interval d = Sub(b, a);
    const interval p = Mul(c, d);
    return Add(a, p);
}

interval interval_algebra::tptDefinition(const interval& x) const
{
    const interval d = Add(x, FloatNum(1.0));
    return Div(x, d);
}

interval interval_algebra::phaseDefinition(const interval& x, const interval& p) const
{
    const interval r = Mod(x, p);
    return Div(r, p);
}

// Numeric kernel : x % p has the sign of x and a magnitude below |p|, for the SAME p, so
// (x % p) / p lies in [-1, 1], of the sign of x times the sign of p. The division may round
// a ratio below 1 up to 1 (a divisor beyond 2^24 in float) : the bounds are closed. The
// definition, its operands read as independent, is sound as well : the two are intersected.
// A divisor that may be 0 leaves the definition alone.
interval interval_algebra::numericPhase(const interval& x, const interval& p) const
{
    if (x.isEmpty() || p.isEmpty()) return empty();
    const interval def = phaseDefinition(x, p);
    if (def.isEmpty() || !(p.lo() > 0 || p.hi() < 0)) return def;
    double lo = -1, hi = 1;
    if (x.lo() >= 0) {
        (p.lo() > 0 ? lo : hi) = 0;
    } else if (x.hi() <= 0) {
        (p.lo() > 0 ? hi : lo) = 0;
    }
    return interval(std::max(lo, def.lo()), std::min(hi, def.hi()), def.lsb());
}

// Numeric kernel : x - floor(x) lies in [0, 1[ for x >= 0, [0, 1] otherwise
interval interval_algebra::numericFrac(const interval& x) const
{
    const bool nonnegative = !x.isEmpty() && x.lo() >= 0;
    return remainder(x, floorOf, 0, nonnegative ? belowOne() : 1.0);
}

// Numeric kernel : x - rint(x) lies in [-1/2, 1/2]
interval interval_algebra::numericCfrac(const interval& x) const
{
    return remainder(x, rintOf, -0.5, 0.5);
}

// Numeric kernel : (1 - c) a + c b with c in [0, 1] lies between a and b. For a fixed c
// the mix is linear in c, so its extremes are reached at the two ends of c : computed in
// double (a 2^-50 relative slack covers their own rounding), then widened by the rounding
// of the program at any c in between : an interpolation from a (or b, see mixFromB), with
// w the largest weight of the difference, c (or 1 - c, exact), and W the largest |b - a|.
// The difference and the product cost (2u + u^2) w W, the sum u times the result : about
// one rounding of the result when w is small (a slow smoother).
//
// Two envelopes then bound the result whatever the rounding, each rounding to nearest
// being monotone and odd. A mix of nonnegative operands stays nonnegative (and
// symmetrically) : the interpolation adds to its base a difference at least minus the
// base, times a weight in [0, 1]. A mix of operands in [-M, M], M a power of two, stays in
// [-M, M] : a + c (b - a) is at most a + fl(M - a), since c fl(b - a) <= fl(M - a) ; and
// fl(M - a) exceeds M - a by at most half an ulp of a value below 2M, u M, so that the sum
// is at most the midpoint M (1 + u) between M and the next float, rounded to the even M
// (the same with the product fused, and from b with the weight 1 - c in [0, 1]). This
// envelope bounds a recursive smoother y = mix(c, x, y') whose stability margin 1 - c is
// a few rounding errors, smaller than its rounding : the fixpoint of the margins diverges,
// the envelope [-M, M] maps into itself. Outside of its premise (c beyond [0, 1], an
// unbounded operand), the mix is its definition.
interval interval_algebra::numericMix(const interval& c, const interval& a, const interval& b) const
{
    const interval fc = detail::floatingOperand(c);
    return numericMixWeight(c, a, b, fc.isEmpty() ? 0 : (mixFromB(fc) ? 1 - fc.lo() : fc.hi()));
}

// any form : the largest weight the difference may have in an interpolation, and the
// weighted sum
interval interval_algebra::numericMixAnyForm(const interval& c, const interval& a, const interval& b) const
{
    const interval fc = detail::floatingOperand(c);
    return numericMixWeight(c, a, b, fc.isEmpty() ? 0 : std::max(1 - fc.lo(), fc.hi()), true);
}

// w : the largest weight of the difference in the computation bounded. weightedSum : the
// computation may also be the weighted sum fl(fl(w' a) + fl(c' b)) of a slow smoother, its
// pole c' = fl(1 - w') computed from the weight w' it holds, or its weight w' = fl(1 - c')
// computed from the pole : w' + c' differs from 1 by at most u, which moves the result by
// u |a| or u |b| ; the two products and the sum round once each, about u (1 + w' + 1) times
// the largest operand. In all, (4u + 4u^2) times it bounds the distance to the exact mix
// (1 - c') a + c' b. The two envelopes hold as well : the products of nonnegative operands
// are nonnegative, and with |a|, |b| <= M a power of two, w' M + c' M = (w' + c') M stays
// below M (1 + u), the midpoint rounded to M.
interval interval_algebra::numericMixWeight(const interval& c, const interval& a, const interval& b, double weight,
                                            bool weightedSum) const
{
    if (c.isEmpty() || a.isEmpty() || b.isEmpty()) return empty();
    const interval fc = detail::floatingOperand(c), fa = detail::floatingOperand(a),
                   fb = detail::floatingOperand(b);
    if (fc.lo() < 0 || fc.hi() > 1 || !fa.isBounded() || !fb.isBounded()) {
        return mixDefinition(c, a, b);
    }
    double lo = HUGE_VAL, hi = -HUGE_VAL;
    for (double e : {fc.lo(), fc.hi()}) {
        const double w = 1 - e;
        lo             = std::min(lo, w * fa.lo() + e * fb.lo());
        hi             = std::max(hi, w * fa.hi() + e * fb.hi());
    }
    const double mag = std::max({std::abs(fa.lo()), std::abs(fa.hi()), std::abs(fb.lo()), std::abs(fb.hi())});
    const double u   = unitRoundoff();
    const double w   = weight;
    const double W   = std::max(fa.hi(), fb.hi()) - std::min(fa.lo(), fb.lo());
    const double rnd = std::max((2 * u + u * u) * w * W + u * mag, weightedSum ? (4 * u + 4 * u * u) * mag : 0.0);
    const double eps = rnd * (1 + std::ldexp(1.0, -20)) + std::ldexp(1.0, -50) * mag + std::ldexp(1.0, -122);
    double       rlo = lo - eps, rhi = hi + eps;
    if (fa.lo() >= 0 && fb.lo() >= 0) rlo = std::max(rlo, 0.0);
    if (fa.hi() <= 0 && fb.hi() <= 0) rhi = std::min(rhi, 0.0);
    if (const double M = mixEnvelope(mag); M > 0) {
        rlo = std::max(rlo, -M);
        rhi = std::min(rhi, M);
    }
    return interval(rlo, rhi, std::min({fc.lsb(), fa.lsb(), fb.lsb()}));
}

// Irm(x, c) = y, y(n) = mix(c, x(n), y(n - 1)), y(-1) = 0. An interval Y that holds 0 and
// that the mix maps into itself, Mix(c, x, Y) within Y, holds every y(n) : y(-1) is in Y,
// and y(n) is a mix of x(n) and of y(n - 1), in Y. Two such intervals are tried, and their
// intersection, an invariant as well (the mix of intervals is monotone), is the result :
//  - the hull of x and 0, widened on each side that may move by a margin doubled from one
//    rounding of the result until the mix maps it into itself, then narrowed by
//    bisection : the exact mix of values of Y moves a bound inwards by (1 - c) times its
//    distance to x, which pays for the rounding once the margin reaches about one
//    rounding divided by 1 - c ;
//  - the power-of-two envelope of x and 0 (see numericMix), which needs no margin, for a
//    pole that may reach 1.
// The rounding is the one of any form of the computation, an interpolation from x or from
// the state, or the weighted sum (1 - c) x + c y' of a slow smoother : a code generator may
// choose one or the other (the weight of x is sometimes exact, the pole computed from it is
// not). The result is then the image of the invariant by one more
// mix : the samples are mixes of x and of a state in the invariant, the state 0 before the
// first sample aside. A pole beyond [0, 1] (a recursion that may diverge) or an unbounded
// x : anything, NaN included.
interval interval_algebra::Irm(const interval& x, const interval& c) const
{
    if (x.isEmpty() || c.isEmpty()) return empty().withInvalid(x.mayBeInvalid() || c.mayBeInvalid());
    const bool     invalid  = x.mayBeInvalid() || c.mayBeInvalid();
    const int      lsb      = std::min({x.lsb(), c.lsb(), -1});
    const interval anything = interval(-HUGE_VAL, HUGE_VAL, lsb, true);
    const interval fc = detail::floatingOperand(c), fx = detail::floatingOperand(x);
    if (fc.lo() < 0 || fc.hi() > 1 || !fx.isBounded()) return anything;

    const double lo0 = std::min(fx.lo(), 0.0), hi0 = std::max(fx.hi(), 0.0);
    auto         invariant = [&](const interval& Y) {
        const interval m = numericMixAnyForm(fc, fx, Y);
        return !m.isEmpty() && m.lo() >= Y.lo() && m.hi() <= Y.hi();
    };
    interval best = anything;
    // the hull with a margin : a bound at 0 that x does not cross stays there (the sign of
    // the mix), the other ones move
    const double mag  = std::max(std::abs(lo0), std::abs(hi0));
    const bool   keepLo = fx.lo() >= 0, keepHi = fx.hi() <= 0;
    double       m      = unitRoundoff() * mag + std::ldexp(1.0, -122);
    auto widened = [&](double margin) {
        return interval(keepLo ? lo0 : lo0 - margin, keepHi ? hi0 : hi0 + margin, lsb);
    };
    for (int k = 0; k < 64 && m <= mag; k++, m *= 2) {
        if (invariant(widened(m))) {
            // the smallest margin, within an eighth, between m / 2 (refused, or the first
            // try) and m (accepted)
            double refused = (k == 0) ? 0 : m / 2, accepted = m;
            for (int j = 0; j < 3; j++) {
                const double mid = (refused + accepted) / 2;
                (invariant(widened(mid)) ? accepted : refused) = mid;
            }
            best = widened(accepted);
            break;
        }
    }
    // the power-of-two envelope, on the sides that may move ; met with the hull when both
    // are invariants
    if (const double M = mixEnvelope(mag); M > 0) {
        const interval E(keepLo ? 0.0 : -M, keepHi ? 0.0 : M, lsb);
        if (invariant(E)) {
            best = std::isfinite(best.hi()) ? interval(std::max(best.lo(), E.lo()), std::min(best.hi(), E.hi()), lsb) : E;
        }
    }
    if (!std::isfinite(best.lo()) || !std::isfinite(best.hi())) return anything;
    // the samples themselves are mixes of x and of a state in the invariant : one more step
    // (a smoother of a positive x is positive, the state 0 before the first sample aside)
    const interval step = numericMixAnyForm(fc, fx, best);
    return interval(std::max(best.lo(), step.lo()), std::min(best.hi(), step.hi()), lsb).withInvalid(invalid);
}

// Numeric kernel : x / (x + 1) is increasing on ]-1, +inf[, so for a finite x in that
// domain its image is [lo / (lo + 1), hi / (hi + 1)]. The ends are computed in double
// (a 2^-50 relative slack covers their own rounding), then widened by the 2 rounding
// errors of the program (the sum, the division) relative to each end ; the result is
// also intersected with the bounds of the definition, both being sound. Outside of
// that domain (x reaching -1, or unbounded), Tpt is its definition.
interval interval_algebra::numericTpt(const interval& x) const
{
    if (x.isEmpty()) return empty();
    const interval def = tptDefinition(x);
    const interval fx  = detail::floatingOperand(x);
    if (!(fx.lo() > -1) || !std::isfinite(fx.hi()) || def.isEmpty()) return def;
    const double rel = 2 * unitRoundoff() + std::ldexp(1.0, -50);
    const double lo  = fx.lo() / (fx.lo() + 1);
    const double hi  = fx.hi() / (fx.hi() + 1);
    const double rlo = lo - std::abs(lo) * rel - std::ldexp(1.0, -122);
    const double rhi = hi + std::abs(hi) * rel + std::ldexp(1.0, -122);
    return interval(std::max(rlo, def.lo()), std::min(rhi, def.hi()), def.lsb());
}

// Public API : an x that may be infinite gives a possible NaN (inf - inf)
interval interval_algebra::Frac(const interval& x) const
{
    const bool infinite = !x.isEmpty() && (!std::isfinite(x.lo()) || !std::isfinite(x.hi()));
    return numericFrac(x).withInvalid(x.mayBeInvalid() || infinite);
}

interval interval_algebra::Cfrac(const interval& x) const
{
    const bool infinite = !x.isEmpty() && (!std::isfinite(x.lo()) || !std::isfinite(x.hi()));
    return numericCfrac(x).withInvalid(x.mayBeInvalid() || infinite);
}

interval interval_algebra::Mix(const interval& c, const interval& a, const interval& b) const
{
    return numericMix(c, a, b).withInvalid(c.mayBeInvalid() || a.mayBeInvalid() || b.mayBeInvalid());
}

// The interpolation from b with the weight t of the difference, as numericMix bounds the one
// from b when c = 1 - t >= 1/2 : the hull of the exact mix, whose weight c is 1 - t computed
// here in double and enclosed outwards, and the rounding of b + t (a - b) (a difference
// weighted by at most t). Outside of [0, 1], the definition.
interval interval_algebra::MixOfComplement(const interval& t, const interval& a, const interval& b) const
{
    const bool invalid = t.mayBeInvalid() || a.mayBeInvalid() || b.mayBeInvalid();
    if (t.isEmpty() || a.isEmpty() || b.isEmpty()) return empty().withInvalid(invalid);
    const interval ft = detail::floatingOperand(t);
    if (!(ft.lo() >= 0) || !(ft.hi() <= 1)) {
        return Add(b, Mul(t, Sub(a, b))).withInvalid(invalid);
    }
    const double   clo = std::max(0.0, std::nextafter(1 - ft.hi(), -HUGE_VAL));
    const double   chi = std::min(1.0, std::nextafter(1 - ft.lo(), HUGE_VAL));
    const interval c(clo, chi, ft.lsb());
    return numericMixWeight(c, a, b, ft.hi()).withInvalid(invalid);
}

// Public API : inside its domain Tpt is valid when x is ; outside, the definition says
interval interval_algebra::Tpt(const interval& x) const
{
    if (x.isEmpty()) return empty().withInvalid(x.mayBeInvalid());
    const interval fx = detail::floatingOperand(x);
    if (!(fx.lo() > -1) || !std::isfinite(fx.hi())) return tptDefinition(x);
    return numericTpt(x).withInvalid(x.mayBeInvalid());
}

// Public API : the validity of the definition (a divisor that may be 0, an invalid operand)
interval interval_algebra::Phase(const interval& x, const interval& p) const
{
    if (x.isEmpty() || p.isEmpty()) return empty().withInvalid(x.mayBeInvalid() || p.mayBeInvalid());
    return numericPhase(x, p).withInvalid(phaseDefinition(x, p).mayBeInvalid());
}

}  // namespace itv
