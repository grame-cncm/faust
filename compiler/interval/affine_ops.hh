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
#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

#include "FaustAlgebra.hh"
#include "affint.hh"
#include "interval_algebra.hh"
#include "validity.hh"

/**
 * The FaustAlgebra operations over affine-in-time intervals, as a MIXIN.
 *
 * AffineOps<Base> implements every FaustAlgebra<AffItv> operation on top of any Base
 * that declares them. Two instantiations serve two worlds with a single body of code:
 *
 *   - affine_algebra = AffineOps<FaustAlgebra<AffItv>> — the standalone numeric
 *     algebra, testable in this repository, tlib-free;
 *   - AffineOps<SignalAlgebra<AffItv>> — the compiler-side fixpoint domain, where the
 *     signals layer adds only what is tree-aware (probe, projection, widening policy).
 *
 * Three regimes:
 *   - LINEAR operations work on the coefficients and never touch interval_algebra:
 *     addition adds the lines, a delay slides the moving intercept by -n·rate (which
 *     is what makes accumulators stationary at their true rate), joins are endpoint
 *     chords;
 *   - NONLINEAR operations collapse their operands to the hull over [0, T] and
 *     delegate to interval_algebra, the semantic oracle — rates die there, and that is
 *     a feature: mod, clamps and sinusoids re-anchor the analysis (the hull of a
 *     sawtooth IS the horizontal band);
 *   - the MIXED case (multiplication or division by a rate-0 operand) evaluates the
 *     oracle at both endpoints and chords back, staying affine.
 *
 * In single precision, floating linear/mixed operations also collapse to the
 * ordinary oracle: rounded staircases need not fit chords through their endpoints.
 *
 * Rates are born at widening (awiden), live through the linear regime, die at the
 * nonlinear one.
 */

namespace itv {

template <typename Base>
class AffineOps : public Base {
   protected:
    // The mixin's whole state: the horizon (in samples), the parameter-reading policy,
    // and the semantic oracle for the nonlinear regime.
    double           fT;         ///< the horizon T, in samples
    bool             fDefaults;  ///< widgets at their default values (nominal reading)
    interval_algebra fItv;       ///< the ordinary interval algebra, stateless

   public:
    explicit AffineOps(double horizonSamples = 2147483648.0, bool defaultParams = false)
        : fT(horizonSamples), fDefaults(defaultParams)
    {
    }

    double horizon() const { return fT; }

   protected:
    // Numeric affine kernels; public transfers below attach sticky validity.
    //--- injections -------------------------------------------------------------------
    AffItv numericLabel(const std::string& arg0) const
    { return aempty(); }
    AffItv numericIntNum(int x) const
    { return fromItv(fItv.IntNum(x)); }
    AffItv numericInt64Num(int64_t x) const
    { return fromItv(fItv.Int64Num(x)); }
    AffItv numericFloatNum(double x) const
    { return fromItv(fItv.FloatNum(x)); }
    AffItv numericFixPointUpdate(const AffItv& x, const AffItv& y) const
    {
        return ajoin(x, y, fT);
    }

    // an audio input has no assumed range (see interval_algebra::numericInput)
    AffItv numericInput(const AffItv& arg0) const
    { return fromItv(interval(-HUGE_VAL, HUGE_VAL)); }
    AffItv numericOutput(const AffItv& arg0, const AffItv& x) const
    { return x; }

    //--- user interface (rate 0 by nature) --------------------------------------------
    AffItv numericButton(const AffItv& arg0) const
    {
        if (fDefaults) return fromItv(interval(0, 0));  // released
        return fromItv(fItv.Button(interval(0, 0)));
    }
    AffItv numericCheckbox(const AffItv& arg0) const
    {
        if (fDefaults) return fromItv(interval(0, 0));
        return fromItv(fItv.Checkbox(interval(0, 0)));
    }
    AffItv numericVSlider(const AffItv& arg0, const AffItv& c, const AffItv& l, const AffItv& h, const AffItv& s) const
    {
        if (fDefaults) return c;  // the default value, a singleton
        return fromItv(fItv.VSlider(interval(0, 0), toItv(c, fT), toItv(l, fT),
                                    toItv(h, fT), toItv(s, fT)));
    }
    AffItv numericHSlider(const AffItv& arg0, const AffItv& c, const AffItv& l, const AffItv& h, const AffItv& s) const
    {
        if (fDefaults) return c;
        return fromItv(fItv.HSlider(interval(0, 0), toItv(c, fT), toItv(l, fT),
                                    toItv(h, fT), toItv(s, fT)));
    }
    AffItv numericNumEntry(const AffItv& arg0, const AffItv& c, const AffItv& l, const AffItv& h, const AffItv& s) const
    {
        if (fDefaults) return c;
        return fromItv(fItv.NumEntry(interval(0, 0), toItv(c, fT), toItv(l, fT),
                                     toItv(h, fT), toItv(s, fT)));
    }
    // A bargraph reports the displayed signal; the range bounds do not participate.
    AffItv numericHBargraph(const AffItv& arg0, const AffItv& arg1, const AffItv& arg2, const AffItv& s) const
    {
        return s;
    }
    AffItv numericVBargraph(const AffItv& arg0, const AffItv& arg1, const AffItv& arg2, const AffItv& s) const
    {
        return s;
    }

    AffItv numericAttach(const AffItv& x, const AffItv& arg1) const
    { return x; }
    AffItv numericEnable(const AffItv& x, const AffItv& arg1) const
    { return x; }
    AffItv numericControl(const AffItv& x, const AffItv& arg1) const
    { return x; }

    //--- the affine-preserving (linear) regime ----------------------------------------
    // Numeric kernel: coefficient-wise enclosure of x+y over a nonnegative horizon.
    // Double coefficients round outward (they are not values of the program); float
    // operations use a constant hull through the ordinary oracle because rounding need not
    // preserve affinity, and so do two constant corridors, whose bounds are values.
    AffItv numericAdd(const AffItv& x, const AffItv& y) const
    {
        if (x.isEmpty() || y.isEmpty()) return aempty();
        auto add = [this](const interval& a, const interval& b) { return fItv.Add(a, b); };
        if (x.lsb < 0 && y.lsb < 0 && x.isConst() && y.isConst())
            return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Add(a, b); });
        // Binary32 rounding is a staircase, not an affine function of time.
        // Collapse float corridors over the horizon and use the outward oracle.
        // Mixed operations must also recover any wrapped integer hull before its
        // conversion to floating point, in double as well as single precision.
        if ((x.lsb < 0 || y.lsb < 0) &&
            (programPrecision() == 1 || integerMayWrap(x) || integerMayWrap(y)))
            return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Add(a, b); });
        if (programPrecision() == 2) {
            const AffItv result{detail::directedBinary(detail::BinaryOp::Add, x.a0, y.a0, detail::Direction::Down),
                    detail::directedBinary(detail::BinaryOp::Add, x.a1, y.a1, detail::Direction::Down),
                    detail::directedBinary(detail::BinaryOp::Add, x.b0, y.b0, detail::Direction::Up),
                    detail::directedBinary(detail::BinaryOp::Add, x.b1, y.b1, detail::Direction::Up),
                    std::min(x.lsb, y.lsb)};
            // Indeterminate coefficients must not erase numeric execution paths.
            if (result.isEmpty() || std::isnan(result.a1) || std::isnan(result.b1))
                return fromItv(interval(-HUGE_VAL, HUGE_VAL, std::min(x.lsb, y.lsb)));
            return integerOverflow(adrift(adrift(result, x), y), x, y, add);
        }
        return integerOverflow(adrift(adrift({x.a0 + y.a0, x.a1 + y.a1, x.b0 + y.b0, x.b1 + y.b1,
                                              std::min(x.lsb, y.lsb)},
                                             x),
                                      y),
                               x, y, add);
    }
    // Numeric kernel: coefficient-wise enclosure of x-y over a nonnegative horizon (see
    // numericAdd for the constant corridors).
    AffItv numericSub(const AffItv& x, const AffItv& y) const
    {
        if (x.isEmpty() || y.isEmpty()) return aempty();
        auto sub = [this](const interval& a, const interval& b) { return fItv.Sub(a, b); };
        if (x.lsb < 0 && y.lsb < 0 && x.isConst() && y.isConst())
            return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Sub(a, b); });
        if ((x.lsb < 0 || y.lsb < 0) &&
            (programPrecision() == 1 || integerMayWrap(x) || integerMayWrap(y)))
            return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Sub(a, b); });
        if (programPrecision() == 2) {
            const AffItv result{detail::directedBinary(detail::BinaryOp::Sub, x.a0, y.b0, detail::Direction::Down),
                    detail::directedBinary(detail::BinaryOp::Sub, x.a1, y.b1, detail::Direction::Down),
                    detail::directedBinary(detail::BinaryOp::Sub, x.b0, y.a0, detail::Direction::Up),
                    detail::directedBinary(detail::BinaryOp::Sub, x.b1, y.a1, detail::Direction::Up),
                    std::min(x.lsb, y.lsb)};
            if (result.isEmpty() || std::isnan(result.a1) || std::isnan(result.b1))
                return fromItv(interval(-HUGE_VAL, HUGE_VAL, std::min(x.lsb, y.lsb)));
            return integerOverflow(adrift(adrift(result, x), flipped(y)), x, y, sub);
        }
        return integerOverflow(adrift(adrift({x.a0 - y.b0, x.a1 - y.b1, x.b0 - y.a0, x.b1 - y.a1,
                                              std::min(x.lsb, y.lsb)},
                                             x),
                                      flipped(y)),
                               x, y, sub);
    }
    AffItv numericNeg(const AffItv& x) const
    {
        if (x.isEmpty()) return aempty();
        return integerOverflow(adrift({-x.b0, -x.b1, -x.a0, -x.a1, x.lsb}, flipped(x)), x, x,
                               [this](const interval& a, const interval&) { return fItv.Neg(a); });
    }
    AffItv numericMul(const AffItv& x, const AffItv& y) const
    {
        return mulDivByConst(x, y, /*isDiv*/ false);
    }
    AffItv numericDiv(const AffItv& x, const AffItv& y) const
    {
        return mulDivByConst(x, y, /*isDiv*/ true);
    }

    //--- delays: the temporal rule on forms -------------------------------------------
    AffItv numericMem(const AffItv& x) const
    { return delayed(x, 1); }
    AffItv numericDelay(const AffItv& x, const AffItv& n) const
    {
        const interval nn = fItv.IntCast(toItv(n, fT));
        // Exactly zero is the identity, even for empty or moving corridors.
        // A zero minimum alone is insufficient: a variable positive delay still
        // needs initialization. The public transfer attaches either input alert.
        if (!nn.isEmpty() && nn.lo() == 0 && nn.hi() == 0) return x;
        const double   nlo =
            (nn.isEmpty() || !std::isfinite(nn.lo())) ? 0 : std::max(0.0, nn.lo());
        return delayed(x, nlo);
    }
    // prefix(x, y) is x at t = 0, then y(t - 1) : x joined with the corridor of y shifted by
    // one sample (a moving line evaluated one sample earlier is not within its own corridor)
    AffItv numericPrefix(const AffItv& x, const AffItv& y) const
    {
        if (y.isEmpty()) return ajoin(x, y, fT);
        AffItv s = y;
        if (y.a1 != 0) {
            s.a0 = detail::usesNativeBounds()
                       ? detail::directedBinary(detail::BinaryOp::Sub, y.a0, y.a1, detail::Direction::Down)
                       : y.a0 - y.a1;
        }
        if (y.b1 != 0) {
            s.b0 = detail::usesNativeBounds()
                       ? detail::directedBinary(detail::BinaryOp::Sub, y.b0, y.b1, detail::Direction::Up)
                       : y.b0 - y.b1;
        }
        return ajoin(x, s, fT);
    }
    AffItv numericAssertBounds(const AffItv& lo, const AffItv& hi, const AffItv& x) const
    {
        if (toItv(lo, fT).isEmpty() || toItv(hi, fT).isEmpty()) return x;
        return collapse(lo.moving() || hi.moving() || x.moving(), [&](auto hull) {
            const interval l = hull(lo), h = hull(hi), xx = hull(x);
            if (xx.isEmpty()) return interval(l.lo(), h.hi());
            return interval(std::max(xx.lo(), l.lo()), std::min(xx.hi(), h.hi()), xx.lsb());
        });
    }

    //--- selection: numeric hull; the public transfer retains selector invalidity -------------------------
    AffItv numericSelect2(const AffItv& arg0, const AffItv& x, const AffItv& y) const
    {
        // a selector of one value over the horizon chooses its branch : the program
        // converts it to an integer
        const interval s = toItv(arg0, fT);
        if (!arg0.moving() && !s.isEmpty() && s.lo() == s.hi())
            return (std::trunc(s.lo()) == 0) ? x : y;
        return ajoin(x, y, fT);
    }

    //--- casts ------------------------------------------------------------------------
    // Numeric kernel: enclose integer truncation; constant corridors use the ordinary
    // rule. A later hull caps integer claims at int32 limits; this does not define an
    // invalid runtime cast. Truncation toward 0 is monotone, and moves a value by less
    // than one unit toward 0 : down for a positive value, up for a negative one. So each
    // line of a moving corridor is handled on its own : a constant line maps to its
    // truncation ; a moving line keeps its slope, with one unit of slack only on the side
    // the truncation can move it (none at the bottom of a corridor that stays negative,
    // none at the top of a corridor that stays nonnegative).
    AffItv numericIntCast(const AffItv& x) const
    {
        if (x.isEmpty()) return aempty();
        // the conversion of an int32 is the identity : its lines, beyond int32 once it has
        // wrapped, are read as the whole int32 range by toItv, never saturated
        if (x.lsb >= 0) return x;
        if (x.isConst() || detail::intCastInvalid(toItv(x, fT)))
            return collapse(x.moving(), [&](auto hull) { return fItv.IntCast(hull(x)); });
        const bool nonneg = std::min(x.lo(0), x.lo(fT)) >= 0;  // the bottom line stays >= 0
        const bool nonpos = std::max(x.hi(0), x.hi(fT)) <= 0;  // the top line stays <= 0
        double     a0     = x.a0;
        double     b0     = x.b0;
        if (x.a1 == 0) {
            a0 = double(saturatedIntCast(x.a0));
        } else if (!nonpos) {
            a0 = detail::usesNativeBounds()
                     ? detail::directedBinary(detail::BinaryOp::Sub, x.a0, 1, detail::Direction::Down)
                     : x.a0 - 1;
        }
        if (x.b1 == 0) {
            b0 = double(saturatedIntCast(x.b0));
        } else if (!nonneg) {
            b0 = detail::usesNativeBounds()
                     ? detail::directedBinary(detail::BinaryOp::Add, x.b0, 1, detail::Direction::Up)
                     : x.b0 + 1;
        }
        // the chain is integer from here
        return adrift({a0, x.a1, b0, x.b1, 0}, x);
    }
    AffItv numericBitCast(const AffItv& x) const
    { return c1(x, [this](const interval& a) { return fItv.BitCast(a); }); }
    AffItv numericFloatCast(const AffItv& x) const
    {
        // Constant corridors must acquire floating nature in double too. Integer
        // moving corridors first recover their wrapped hull; binary32 narrowing
        // also prevents floating slopes from remaining affine.
        if (programPrecision() == 1 || x.isConst() || x.lsb >= 0)
            return c1(x, [this](const interval& a) { return fItv.FloatCast(a); });
        if (x.isEmpty()) return aempty();
        AffItv r = x;
        r.lsb    = std::min(x.lsb, -24);  // the value is now carried by a float
        return r;
    }

    //--- the nonlinear regime: collapse to the oracle ---------------------------------
    AffItv numericMod(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Mod(a, b); });
    }
    AffItv numericFmod(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Fmod(a, b); });
    }
    AffItv numericInv(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Inv(a); });
    }
    AffItv numericAbs(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Abs(a); });
    }
    AffItv numericHighest(const AffItv& x) const
    {
        return collapse(x.moving(), [&](auto hull) { return interval(hull(x).hi()); });
    }
    AffItv numericLowest(const AffItv& x) const
    {
        return collapse(x.moving(), [&](auto hull) { return interval(hull(x).lo()); });
    }
    AffItv numericGt(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Gt(a, b); });
    }
    AffItv numericLt(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Lt(a, b); });
    }
    AffItv numericGe(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Ge(a, b); });
    }
    AffItv numericLe(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Le(a, b); });
    }
    AffItv numericEq(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Eq(a, b); });
    }
    AffItv numericNe(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Ne(a, b); });
    }
    AffItv numericNot(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Not(a); });
    }
    AffItv numericAnd(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.And(a, b));
        });
    }
    AffItv numericOr(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.Or(a, b));
        });
    }
    AffItv numericXor(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.Xor(a, b));
        });
    }
    AffItv numericLsh(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.Lsh(a, b));
        });
    }
    AffItv numericARsh(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.ARsh(a, b));
        });
    }
    AffItv numericLRsh(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.LRsh(a, b));
        });
    }
    AffItv numericAcos(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Acos(a); });
    }
    AffItv numericAcosh(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Acosh(a); });
    }
    AffItv numericAsin(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Asin(a); });
    }
    AffItv numericAsinh(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Asinh(a); });
    }
    AffItv numericAtan(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Atan(a); });
    }
    AffItv numericAtan2(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y,
                  [this](const interval& a, const interval& b) { return fItv.Atan2(a, b); });
    }
    AffItv numericAtanh(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Atanh(a); });
    }
    AffItv numericCeil(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Ceil(a); });
    }
    AffItv numericCos(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Cos(a); });
    }
    AffItv numericCosh(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Cosh(a); });
    }
    AffItv numericExp(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Exp(a); });
    }
    AffItv numericExp10(const AffItv& x) const
    {
        // the oracle computes a floating power of 10 (an integer power of 10 would wrap)
        return c1(x, [this](const interval& a) { return fItv.Exp10(a); });
    }
    AffItv numericFloor(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Floor(a); });
    }
    AffItv numericLog(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Log(a); });
    }
    AffItv numericLog10(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Log10(a); });
    }
    AffItv numericPow(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Pow(a, b); });
    }
    AffItv numericRemainder(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.Remainder(a, b);
        });
    }
    AffItv numericRint(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Rint(a); });
    }
    AffItv numericRound(const AffItv& x) const
    {
        // the generated code calls round (halves away from zero), not rint
        return c1(x, [this](const interval& a) { return fItv.Round(a); });
    }
    AffItv numericSin(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Sin(a); });
    }
    AffItv numericSinh(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Sinh(a); });
    }
    AffItv numericSqrt(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Sqrt(a); });
    }
    AffItv numericTan(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Tan(a); });
    }
    AffItv numericTanh(const AffItv& x) const
    {
        return c1(x, [this](const interval& a) { return fItv.Tanh(a); });
    }
    AffItv numericMax(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Max(a, b); });
    }
    AffItv numericMin(const AffItv& x, const AffItv& y) const
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Min(a, b); });
    }

    //--- tables -----------------------------------------------------------------------
    AffItv numericRDTbl(const AffItv& tbl, const AffItv& arg1) const
    { return tbl; }
    // a cell read at t was written at some t' <= t : the values written, over [0, T] and not
    // as corridors, drifting where they move past the horizon
    AffItv numericWRTbl(const AffItv& arg0, const AffItv& g, const AffItv& arg2, const AffItv& ws) const
    {
        if (g.isEmpty() || ws.isEmpty()) return ajoin(g, ws, fT);
        return hullDrift(fromItv(reunion(toItv(g, fT), toItv(ws, fT))), {g, ws});
    }
    AffItv numericGen(const AffItv& x) const
    { return x; }
    AffItv numericWaveform(const std::vector<AffItv>& w) const
    {
        AffItv r = aempty();
        for (const AffItv& x : w) {
            r = ajoin(r, x, fT);
        }
        return r;
    }

    //--- soundfiles -------------------------------------------------------------------
    // Metadata is int32 independently of the program's sample precision.
    AffItv numericSoundFile(const AffItv& arg0) const
    {
        return fromItv(interval(0, 2147483647.0, 0));
    }
    AffItv numericSoundFileRate(const AffItv& arg0, const AffItv& arg1) const
    {
        return fromItv(interval(0, 2147483647.0, 0));
    }
    AffItv numericSoundFileLength(const AffItv& arg0, const AffItv& arg1) const
    {
        return fromItv(interval(0, 2147483647.0, 0));
    }
    AffItv numericSoundFileBuffer(const AffItv& arg0, const AffItv& arg1, const AffItv& arg2, const AffItv& arg3) const
    {
        return fromItv(interval(-1, 1));
    }

    //--- foreign entities: retain an unknown typed hull, not numeric bottom.
    // Floating storage may contain NaN; a function without a domain contract
    // is uncertified even when it returns an integer.
    AffItv numericForeignConst(int arg0, const AffItv& arg1, const AffItv& arg2) const
    {
        return fromItv(fItv.ForeignConst(arg0, empty(), empty()));
    }
    AffItv numericForeignVar(int arg0, const AffItv& arg1, const AffItv& arg2) const
    {
        return fromItv(fItv.ForeignVar(arg0, empty(), empty()));
    }
    AffItv numericForeignFunction(int arg0, const std::vector<AffItv>& arg1) const
    {
        return fromItv(fItv.ForeignFunction(arg0, {}));
    }


   public:
    // Public API: validity-aware affine transfers. All incoming alerts survive
    // numeric early exits; linear operations also check their collapsed domains.

    // Public API: enclose Label over the horizon, retaining possible invalidity.
    AffItv Label(const std::string& arg0) const override
    {
        return numericLabel(arg0).withInvalid(false);
    }

    // Public API: enclose IntNum over the horizon, retaining possible invalidity.
    AffItv IntNum(int x) const override
    {
        return numericIntNum(x).withInvalid(false);
    }

    // Public API: enclose Int64Num over the horizon, retaining possible invalidity.
    AffItv Int64Num(int64_t x) const override
    {
        return numericInt64Num(x).withInvalid(false);
    }

    // Public API: enclose FloatNum over the horizon, retaining possible invalidity.
    AffItv FloatNum(double x) const override
    {
        return numericFloatNum(x).withInvalid(std::isnan(x));
    }

    // Public API: enclose FixPointUpdate over the horizon, retaining possible invalidity.
    AffItv FixPointUpdate(const AffItv& x, const AffItv& y) const override
    {
        return numericFixPointUpdate(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Input over the horizon, retaining possible invalidity.
    AffItv Input(const AffItv& arg0) const override
    {
        return numericInput(arg0).withInvalid(arg0.mayBeInvalid);
    }

    // Public API: enclose Output over the horizon, retaining possible invalidity.
    AffItv Output(const AffItv& arg0, const AffItv& x) const override
    {
        return numericOutput(arg0, x).withInvalid(arg0.mayBeInvalid || x.mayBeInvalid);
    }

    // Public API: enclose Button over the horizon, retaining possible invalidity.
    AffItv Button(const AffItv& arg0) const override
    {
        return numericButton(arg0).withInvalid(arg0.mayBeInvalid);
    }

    // Public API: enclose Checkbox over the horizon, retaining possible invalidity.
    AffItv Checkbox(const AffItv& arg0) const override
    {
        return numericCheckbox(arg0).withInvalid(arg0.mayBeInvalid);
    }

    // Public API: enclose VSlider over the horizon, retaining possible invalidity.
    AffItv VSlider(const AffItv& arg0, const AffItv& c, const AffItv& l, const AffItv& h, const AffItv& s) const override
    {
        return numericVSlider(arg0, c, l, h, s).withInvalid(arg0.mayBeInvalid || detail::widgetInvalid(toItv(c, fT), toItv(l, fT), toItv(h, fT), toItv(s, fT)));
    }

    // Public API: enclose HSlider over the horizon, retaining possible invalidity.
    AffItv HSlider(const AffItv& arg0, const AffItv& c, const AffItv& l, const AffItv& h, const AffItv& s) const override
    {
        return numericHSlider(arg0, c, l, h, s).withInvalid(arg0.mayBeInvalid || detail::widgetInvalid(toItv(c, fT), toItv(l, fT), toItv(h, fT), toItv(s, fT)));
    }

    // Public API: enclose NumEntry over the horizon, retaining possible invalidity.
    AffItv NumEntry(const AffItv& arg0, const AffItv& c, const AffItv& l, const AffItv& h, const AffItv& s) const override
    {
        return numericNumEntry(arg0, c, l, h, s).withInvalid(arg0.mayBeInvalid || detail::widgetInvalid(toItv(c, fT), toItv(l, fT), toItv(h, fT), toItv(s, fT)));
    }

    // Public API: enclose HBargraph over the horizon, retaining possible invalidity.
    AffItv HBargraph(const AffItv& arg0, const AffItv& arg1, const AffItv& arg2, const AffItv& s) const override
    {
        return numericHBargraph(arg0, arg1, arg2, s).withInvalid(arg0.mayBeInvalid || arg1.mayBeInvalid || arg2.mayBeInvalid || s.mayBeInvalid);
    }

    // Public API: enclose VBargraph over the horizon, retaining possible invalidity.
    AffItv VBargraph(const AffItv& arg0, const AffItv& arg1, const AffItv& arg2, const AffItv& s) const override
    {
        return numericVBargraph(arg0, arg1, arg2, s).withInvalid(arg0.mayBeInvalid || arg1.mayBeInvalid || arg2.mayBeInvalid || s.mayBeInvalid);
    }

    // Public API: enclose Attach over the horizon, retaining possible invalidity.
    AffItv Attach(const AffItv& x, const AffItv& arg1) const override
    {
        return numericAttach(x, arg1).withInvalid(x.mayBeInvalid || arg1.mayBeInvalid);
    }

    // Public API: enclose Enable over the horizon, retaining possible invalidity.
    AffItv Enable(const AffItv& x, const AffItv& arg1) const override
    {
        return numericEnable(x, arg1).withInvalid(x.mayBeInvalid || arg1.mayBeInvalid);
    }

    // Public API: enclose Control over the horizon, retaining possible invalidity.
    AffItv Control(const AffItv& x, const AffItv& arg1) const override
    {
        return numericControl(x, arg1).withInvalid(x.mayBeInvalid || arg1.mayBeInvalid);
    }

    // Public API: enclose Add over the horizon, retaining possible invalidity.
    AffItv Add(const AffItv& x, const AffItv& y) const override
    {
        return numericAdd(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Add, toItv(x, fT), toItv(y, fT)));
    }

    // Public API: enclose Sub over the horizon, retaining possible invalidity.
    AffItv Sub(const AffItv& x, const AffItv& y) const override
    {
        return numericSub(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Sub, toItv(x, fT), toItv(y, fT)));
    }

    // Public API: enclose Neg over the horizon, retaining possible invalidity.
    AffItv Neg(const AffItv& x) const override
    {
        return numericNeg(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Mul over the horizon, retaining possible invalidity.
    AffItv Mul(const AffItv& x, const AffItv& y) const override
    {
        return numericMul(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Mul, toItv(x, fT), toItv(y, fT)));
    }

    // Public API: enclose Div over the horizon, retaining possible invalidity.
    AffItv Div(const AffItv& x, const AffItv& y) const override
    {
        return numericDiv(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Div, toItv(x, fT), toItv(y, fT)));
    }

    // Public API: enclose Mem over the horizon, retaining possible invalidity.
    AffItv Mem(const AffItv& x) const override
    {
        return numericMem(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Delay after int32 conversion of the sample count.
    // Exactly zero preserves every coefficient; possibly positive counts include
    // initial zero. Retain invalidity of either operand and the delay domain.
    AffItv Delay(const AffItv& x, const AffItv& n) const override
    {
        return numericDelay(x, n).withInvalid(detail::delayInvalid(toItv(x, fT), toItv(n, fT)));
    }

    // Public API: enclose Prefix over the horizon, retaining possible invalidity.
    AffItv Prefix(const AffItv& x, const AffItv& y) const override
    {
        return numericPrefix(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose AssertBounds over the horizon, retaining possible invalidity.
    AffItv AssertBounds(const AffItv& lo, const AffItv& hi, const AffItv& x) const override
    {
        return numericAssertBounds(lo, hi, x).withInvalid(detail::assertionInvalid(toItv(lo, fT), toItv(hi, fT), toItv(x, fT)));
    }

    // Public API: enclose Select2 over the horizon, retaining possible invalidity.
    AffItv Select2(const AffItv& arg0, const AffItv& x, const AffItv& y) const override
    {
        return numericSelect2(arg0, x, y).withInvalid(arg0.mayBeInvalid || x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose IntCast over the horizon, retaining possible invalidity.
    AffItv IntCast(const AffItv& x) const override
    {
        return numericIntCast(x).withInvalid(detail::intCastInvalid(toItv(x, fT)));
    }

    // Public API: enclose BitCast over the horizon, retaining possible invalidity.
    AffItv BitCast(const AffItv& x) const override
    {
        return numericBitCast(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose FloatCast over the horizon, retaining possible invalidity.
    AffItv FloatCast(const AffItv& x) const override
    {
        return numericFloatCast(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Mod over the horizon, retaining possible invalidity.
    AffItv Mod(const AffItv& x, const AffItv& y) const override
    {
        return numericMod(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Fmod over the horizon, retaining possible invalidity.
    AffItv Fmod(const AffItv& x, const AffItv& y) const override
    {
        return numericFmod(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Inv over the horizon, retaining possible invalidity.
    AffItv Inv(const AffItv& x) const override
    {
        return numericInv(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Abs over the horizon, retaining possible invalidity.
    AffItv Abs(const AffItv& x) const override
    {
        return numericAbs(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Highest over the horizon, retaining possible invalidity.
    AffItv Highest(const AffItv& x) const override
    {
        return numericHighest(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Lowest over the horizon, retaining possible invalidity.
    AffItv Lowest(const AffItv& x) const override
    {
        return numericLowest(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Gt over the horizon, retaining possible invalidity.
    AffItv Gt(const AffItv& x, const AffItv& y) const override
    {
        return numericGt(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Lt over the horizon, retaining possible invalidity.
    AffItv Lt(const AffItv& x, const AffItv& y) const override
    {
        return numericLt(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Ge over the horizon, retaining possible invalidity.
    AffItv Ge(const AffItv& x, const AffItv& y) const override
    {
        return numericGe(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Le over the horizon, retaining possible invalidity.
    AffItv Le(const AffItv& x, const AffItv& y) const override
    {
        return numericLe(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Eq over the horizon, retaining possible invalidity.
    AffItv Eq(const AffItv& x, const AffItv& y) const override
    {
        return numericEq(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Ne over the horizon, retaining possible invalidity.
    AffItv Ne(const AffItv& x, const AffItv& y) const override
    {
        return numericNe(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Not over the horizon, retaining possible invalidity.
    AffItv Not(const AffItv& x) const override
    {
        return numericNot(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose And over the horizon, retaining possible invalidity.
    AffItv And(const AffItv& x, const AffItv& y) const override
    {
        return numericAnd(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Or over the horizon, retaining possible invalidity.
    AffItv Or(const AffItv& x, const AffItv& y) const override
    {
        return numericOr(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Xor over the horizon, retaining possible invalidity.
    AffItv Xor(const AffItv& x, const AffItv& y) const override
    {
        return numericXor(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Lsh over the horizon, retaining possible invalidity.
    AffItv Lsh(const AffItv& x, const AffItv& y) const override
    {
        return numericLsh(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose ARsh over the horizon, retaining possible invalidity.
    AffItv ARsh(const AffItv& x, const AffItv& y) const override
    {
        return numericARsh(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose LRsh over the horizon, retaining possible invalidity.
    AffItv LRsh(const AffItv& x, const AffItv& y) const override
    {
        return numericLRsh(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Acos over the horizon, retaining possible invalidity.
    AffItv Acos(const AffItv& x) const override
    {
        return numericAcos(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Acosh over the horizon, retaining possible invalidity.
    AffItv Acosh(const AffItv& x) const override
    {
        return numericAcosh(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Asin over the horizon, retaining possible invalidity.
    AffItv Asin(const AffItv& x) const override
    {
        return numericAsin(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Asinh over the horizon, retaining possible invalidity.
    AffItv Asinh(const AffItv& x) const override
    {
        return numericAsinh(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Atan over the horizon, retaining possible invalidity.
    AffItv Atan(const AffItv& x) const override
    {
        return numericAtan(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Atan2 over the horizon, retaining possible invalidity.
    AffItv Atan2(const AffItv& x, const AffItv& y) const override
    {
        return numericAtan2(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Atanh over the horizon, retaining possible invalidity.
    AffItv Atanh(const AffItv& x) const override
    {
        return numericAtanh(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Ceil over the horizon, retaining possible invalidity.
    AffItv Ceil(const AffItv& x) const override
    {
        return numericCeil(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Cos over the horizon, retaining possible invalidity.
    AffItv Cos(const AffItv& x) const override
    {
        return numericCos(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Cosh over the horizon, retaining possible invalidity.
    AffItv Cosh(const AffItv& x) const override
    {
        return numericCosh(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Exp over the horizon, retaining possible invalidity.
    AffItv Exp(const AffItv& x) const override
    {
        return numericExp(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Exp10 over the horizon, retaining possible invalidity.
    AffItv Exp10(const AffItv& x) const override
    {
        return numericExp10(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Floor over the horizon, retaining possible invalidity.
    AffItv Floor(const AffItv& x) const override
    {
        return numericFloor(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Log over the horizon, retaining possible invalidity.
    AffItv Log(const AffItv& x) const override
    {
        return numericLog(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Log10 over the horizon, retaining possible invalidity.
    AffItv Log10(const AffItv& x) const override
    {
        return numericLog10(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Pow over the horizon, retaining possible invalidity.
    AffItv Pow(const AffItv& x, const AffItv& y) const override
    {
        return numericPow(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Remainder over the horizon, retaining possible invalidity.
    AffItv Remainder(const AffItv& x, const AffItv& y) const override
    {
        return numericRemainder(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Rint over the horizon, retaining possible invalidity.
    AffItv Rint(const AffItv& x) const override
    {
        return numericRint(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: the compound operations collapse to the interval rule over the
    // horizon (nonlinear), retaining possible invalidity.
    AffItv Frac(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Frac(a); }).withInvalid(x.mayBeInvalid);
    }
    AffItv Cfrac(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Cfrac(a); }).withInvalid(x.mayBeInvalid);
    }
    AffItv Mix(const AffItv& c, const AffItv& a, const AffItv& b) const override
    {
        if (c.isEmpty() || a.isEmpty() || b.isEmpty()) {
            return aempty().withInvalid(c.mayBeInvalid || a.mayBeInvalid || b.mayBeInvalid);
        }
        return collapse(c.moving() || a.moving() || b.moving(),
                        [&](auto hull) { return fItv.Mix(hull(c), hull(a), hull(b)); })
            .withInvalid(c.mayBeInvalid || a.mayBeInvalid || b.mayBeInvalid);
    }
    AffItv Tpt(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Tpt(a); }).withInvalid(x.mayBeInvalid);
    }
    AffItv Phase(const AffItv& x, const AffItv& p) const override
    {
        if (x.isEmpty() || p.isEmpty()) return aempty().withInvalid(x.mayBeInvalid || p.mayBeInvalid);
        const interval r = fItv.Phase(toItv(x, fT), toItv(p, fT));
        return collapse(x.moving() || p.moving(),
                        [&](auto hull) { return fItv.Phase(hull(x), hull(p)); })
            .withInvalid(x.mayBeInvalid || p.mayBeInvalid || r.mayBeInvalid());
    }

    // The kernels : Sum, Prod and Fir as their definitions over the corridors (from left
    // to right), Iir by the gain rule of the intervals over the horizon
    AffItv Sum(const std::vector<AffItv>& terms) const override
    {
        if (terms.empty()) return this->IntNum(0);
        AffItv acc      = terms[0];
        bool   overflow = false;  // one of the partial sums may wrap
        for (size_t k = 1; k < terms.size(); k++) {
            acc      = this->Add(acc, terms[k]);
            overflow = overflow || acc.mayOverflow;
        }
        return acc.withOverflow(overflow);
    }
    AffItv Prod(const std::vector<AffItv>& factors) const override
    {
        if (factors.empty()) return this->IntNum(1);
        AffItv acc      = factors[0];
        bool   overflow = false;  // one of the partial products may wrap
        for (size_t k = 1; k < factors.size(); k++) {
            acc      = this->Mul(acc, factors[k]);
            overflow = overflow || acc.mayOverflow;
        }
        return acc.withOverflow(overflow);
    }
    AffItv Fir(const AffItv& x, const std::vector<AffItv>& coefs) const override
    {
        bool   first    = true;
        bool   overflow = false;  // one of the products or partial sums may wrap
        AffItv acc;
        for (size_t k = 0; k < coefs.size(); k++) {
            const AffItv& ck = coefs[k];
            // a null coefficient adds nothing, unless it moves past the horizon
            if (!ck.isEmpty() && !ck.moving() && ck.a0 == 0 && ck.b0 == 0 && !ck.mayBeInvalid) continue;
            AffItv term = (k == 0) ? this->Mul(ck, x) : this->Mul(ck, this->Delay(x, this->IntNum(int(k))));
            acc         = first ? term : this->Add(acc, term);
            overflow    = overflow || term.mayOverflow || acc.mayOverflow;
            first       = false;
        }
        return first ? this->IntNum(0) : acc.withOverflow(overflow);
    }
    AffItv Iir(const AffItv& x, const std::vector<AffItv>& coefs) const override
    {
        bool alert = x.mayBeInvalid;
        bool none  = x.isEmpty();
        for (const AffItv& ck : coefs) {
            alert = alert || ck.mayBeInvalid;
            none  = none || ck.isEmpty();
        }
        if (none) return aempty().withInvalid(alert);
        bool moving = x.moving();
        for (const AffItv& ck : coefs) moving = moving || ck.moving();
        return collapse(moving, [&](auto hull) {
            std::vector<interval> cs;
            for (const AffItv& ck : coefs) cs.push_back(hull(ck));
            return fItv.Iir(hull(x), cs);
        });
    }
    AffItv Bpf(const AffItv& x, const std::vector<AffItv>& t, const std::vector<AffItv>& r) const override
    {
        // the regions that x may reach, joined as corridors
        // a malformed node (|r| != |t| + 1) bounds nothing
        if (r.size() != t.size() + 1) return fromItv(interval(-HUGE_VAL, HUGE_VAL, -24, true));
        bool alert = x.mayBeInvalid;
        for (const AffItv& ti : t) alert = alert || ti.mayBeInvalid;
        for (const AffItv& ri : r) alert = alert || ri.mayBeInvalid;
        if (x.isEmpty()) return aempty().withInvalid(alert);
        // a moving x, or moving thresholds, may reach other regions past the horizon
        const interval ix = forever(x, fT);
        AffItv         acc;
        bool           any = false, invalid = false;
        for (size_t i = 0; i < r.size(); i++) {
            const double lo   = (i == 0) ? -HUGE_VAL : forever(t[i - 1], fT).lo();
            const double hi   = (i == t.size()) ? HUGE_VAL : forever(t[i], fT).hi();
            const bool   last = (i == t.size());
            if (!((ix.hi() >= lo && ix.lo() < hi) || (last && x.mayBeInvalid)) || r[i].isEmpty()) continue;
            acc     = any ? ajoin(acc, r[i], fT) : r[i];
            any     = true;
            invalid = invalid || r[i].mayBeInvalid;
        }
        for (const AffItv& ti : t) invalid = invalid || ti.mayBeInvalid;
        return any ? acc.withInvalid(invalid) : aempty().withInvalid(alert);
    }
    AffItv Irm(const AffItv& x, const AffItv& c) const override
    {
        if (x.isEmpty() || c.isEmpty()) return aempty().withInvalid(x.mayBeInvalid || c.mayBeInvalid);
        return collapse(x.moving() || c.moving(),
                        [&](auto hull) { return fItv.Irm(hull(x), hull(c)); })
            .withInvalid(x.mayBeInvalid || c.mayBeInvalid);
    }

    // Public API: enclose Round over the horizon, retaining possible invalidity.
    AffItv Round(const AffItv& x) const override
    {
        return numericRound(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Sin over the horizon, retaining possible invalidity.
    AffItv Sin(const AffItv& x) const override
    {
        return numericSin(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Sinh over the horizon, retaining possible invalidity.
    AffItv Sinh(const AffItv& x) const override
    {
        return numericSinh(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Sqrt over the horizon, retaining possible invalidity.
    AffItv Sqrt(const AffItv& x) const override
    {
        return numericSqrt(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Tan over the horizon, retaining possible invalidity.
    AffItv Tan(const AffItv& x) const override
    {
        return numericTan(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Tanh over the horizon, retaining possible invalidity.
    AffItv Tanh(const AffItv& x) const override
    {
        return numericTanh(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Max over the horizon, retaining possible invalidity.
    AffItv Max(const AffItv& x, const AffItv& y) const override
    {
        return numericMax(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose Min over the horizon, retaining possible invalidity.
    AffItv Min(const AffItv& x, const AffItv& y) const override
    {
        return numericMin(x, y).withInvalid(x.mayBeInvalid || y.mayBeInvalid);
    }

    // Public API: enclose RDTbl over the horizon, retaining possible invalidity.
    AffItv RDTbl(const AffItv& tbl, const AffItv& arg1) const override
    {
        return numericRDTbl(tbl, arg1).withInvalid(true);
    }

    // Public API: enclose WRTbl over the horizon, retaining possible invalidity.
    AffItv WRTbl(const AffItv& arg0, const AffItv& g, const AffItv& arg2, const AffItv& ws) const override
    {
        return numericWRTbl(arg0, g, arg2, ws).withInvalid(g.mayBeInvalid || ws.mayBeInvalid || detail::tableWriteInvalid(toItv(arg0, fT), toItv(arg2, fT)));
    }

    // Public API: enclose Gen over the horizon, retaining possible invalidity.
    AffItv Gen(const AffItv& x) const override
    {
        return numericGen(x).withInvalid(x.mayBeInvalid);
    }

    // Public API: enclose Waveform over the horizon, retaining possible invalidity.
    AffItv Waveform(const std::vector<AffItv>& w) const override
    {
        return numericWaveform(w).withInvalid(std::any_of(w.begin(), w.end(), [](const AffItv& x) { return x.mayBeInvalid; }));
    }

    // Public API: enclose SoundFile over the horizon, retaining possible invalidity.
    AffItv SoundFile(const AffItv& arg0) const override
    {
        return numericSoundFile(arg0).withInvalid(arg0.mayBeInvalid);
    }

    // Public API: enclose SoundFileRate over the horizon, retaining possible invalidity.
    AffItv SoundFileRate(const AffItv& arg0, const AffItv& arg1) const override
    {
        return numericSoundFileRate(arg0, arg1).withInvalid(true);
    }

    // Public API: enclose SoundFileLength over the horizon, retaining possible invalidity.
    AffItv SoundFileLength(const AffItv& arg0, const AffItv& arg1) const override
    {
        return numericSoundFileLength(arg0, arg1).withInvalid(true);
    }

    // Public API: enclose SoundFileBuffer over the horizon, retaining possible invalidity.
    AffItv SoundFileBuffer(const AffItv& arg0, const AffItv& arg1, const AffItv& arg2, const AffItv& arg3) const override
    {
        return numericSoundFileBuffer(arg0, arg1, arg2, arg3).withInvalid(true);
    }

    // Public API: enclose ForeignConst over the horizon, retaining possible invalidity.
    AffItv ForeignConst(int arg0, const AffItv& arg1, const AffItv& arg2) const override
    {
        return numericForeignConst(arg0, arg1, arg2).withInvalid(arg1.mayBeInvalid || arg2.mayBeInvalid);
    }

    // Public API: enclose ForeignVar over the horizon, retaining possible invalidity.
    AffItv ForeignVar(int arg0, const AffItv& arg1, const AffItv& arg2) const override
    {
        return numericForeignVar(arg0, arg1, arg2).withInvalid(arg1.mayBeInvalid || arg2.mayBeInvalid);
    }

    // Public API: enclose ForeignFunction over the horizon, retaining possible invalidity.
    AffItv ForeignFunction(int arg0, const std::vector<AffItv>& arg1) const override
    {
        return numericForeignFunction(arg0, arg1).withInvalid(std::any_of(arg1.begin(), arg1.end(), [](const AffItv& x) { return x.mayBeInvalid; }));
    }

   protected:
    // A floating operation must not consume the unwrapped coefficients of an
    // integer corridor which has crossed int32 somewhere in its horizon.
    bool integerMayWrap(const AffItv& x) const
    {
        return x.lsb >= 0 && (std::min(x.lo(0), x.lo(fT)) < -2147483648.0 ||
                             std::max(x.hi(0), x.hi(fT)) > 2147483647.0);
    }

    /// r, the result of a linear int32 operation op on x and y, flagged when the
    /// operation may wrap on the values of its operands for all time (a moving operand
    /// reaches the limit of the int32 range, a wrapped one holds any int32 value), and
    /// drifting where its operands do
    template <typename Op>
    AffItv integerOverflow(AffItv r, const AffItv& x, const AffItv& y, Op op) const
    {
        if (r.lsb < 0) return r;
        return r.withOverflow(op(forever(x, fT), forever(y, fT)).mayOverflow());
    }

    /// The corridor of a nonlinear operation, g applied to the hulls of its operands :
    /// g receives the function that gives the hull of an operand. Over the horizon, the
    /// hull over [0, T] ; when an operand moves, g is evaluated again on the values of the
    /// operands for all time : a bound of the result that differs drifts past the
    /// horizon, and an int32 operation that may wrap on those values may wrap.
    template <typename G>
    AffItv collapse(bool moving, G g) const
    {
        const interval r   = g([this](const AffItv& a) { return toItv(a, fT); });
        AffItv         out = fromItv(r);
        if (!moving) return out;
        const interval all = g([this](const AffItv& a) { return forever(a, fT); });
        if (all.isEmpty()) return out;
        out.loDrifts = r.isEmpty() || all.lo() < r.lo();
        out.hiDrifts = r.isEmpty() || all.hi() > r.hi();
        return out.withOverflow(all.mayOverflow());
    }

    template <typename F>
    AffItv c1(const AffItv& x, F f) const
    {
        if (x.isEmpty()) return aempty();
        return collapse(x.moving(), [&](auto hull) { return f(hull(x)); });
    }
    template <typename F>
    AffItv c2(const AffItv& x, const AffItv& y, F f) const
    {
        if (x.isEmpty() || y.isEmpty()) return aempty();
        return collapse(x.moving() || y.moving(), [&](auto hull) { return f(hull(x), hull(y)); });
    }

    /// Multiplication with at most one rated operand, or division by a constant
    /// corridor: evaluate the oracle at both endpoints and chord back. A rated
    /// denominator is nonlinear, even with a constant numerator, and may cross zero
    /// between the endpoints; collapse it over the full horizon instead.
    AffItv mulDivByConst(const AffItv& x, const AffItv& y, bool isDiv) const
    {
        if (x.isEmpty() || y.isEmpty()) return aempty();
        auto op = [&](const interval& a, const interval& b) {
            return isDiv ? fItv.Div(a, b) : fItv.Mul(a, b);
        };
        // Chording rounded endpoint values need not enclose staircase values.
        // Mixed/division paths also collapse integer corridors before floating
        // conversion: a wrap between endpoints cannot be represented by a chord.
        // A drifting operand has no line to evaluate at both endpoints.
        const bool drifts = x.loDrifts || x.hiDrifts || y.loDrifts || y.hiDrifts;
        // an int32 product that may wrap over [0, T] has no chord : its wrapped values are
        // not between the values at 0 and T
        const bool productWraps = !isDiv && x.lsb >= 0 && y.lsb >= 0 &&
                                  fItv.Mul(toItv(x, fT), toItv(y, fT)).mayOverflow();
        if ((programPrecision() == 1 && (isDiv || x.lsb < 0 || y.lsb < 0)) || productWraps ||
            ((isDiv || x.lsb < 0 || y.lsb < 0) && (integerMayWrap(x) || integerMayWrap(y))) ||
            (isDiv && !y.isConst()) || x.isConst() == y.isConst() || drifts) {
            return collapse(x.moving() || y.moving(), [&](auto hull) { return op(hull(x), hull(y)); });
        }
        auto at = [&](double t) {
            return op(interval(x.lo(t), x.hi(t), x.lsb), interval(y.lo(t), y.hi(t), y.lsb));
        };
        const interval r0 = at(0), rT = at(fT);
        if (r0.isEmpty() || rT.isEmpty()) return aempty();
        AffItv r;
        achord(r0.lo(), rT.lo(), fT, r.a0, r.a1);
        achord(r0.hi(), rT.hi(), fT, r.b0, r.b1, true);
        r.lsb         = std::min(r0.lsb(), rT.lsb());
        // an int32 product may wrap on the values of its operands for all time
        const interval all = op(forever(x, fT), forever(y, fT));
        r.mayOverflow      = r.lsb >= 0 && all.mayOverflow();
        // an operand that crosses zero, times a constant of either sign, grows again past T
        return chordDrift(r, all, fT).wrapDrift();
    }

    /// x delayed by at least nlo samples, with a positive delay still possible,
    /// then joined with the initial condition. An exactly zero count bypasses this
    /// helper; nlo == 0 here does not prove identity. A
    /// growing bound shifted back in time is smaller: intercept -= nlo * rate is the
    /// sound shift, and the shift is what makes accumulators stationary. A bound whose
    /// rate has the wrong sign collapses to its worst constant over the window.
    AffItv delayed(const AffItv& x, double nlo) const
    {
        // The initial condition is a zero of the signal's own nature : a float zero
        // (the default LSB in single precision) would turn an integer delay into a
        // float, and its later arithmetic would lose the int32 wrap.
        const interval zero(0, 0, x.lsb);
        if (x.isEmpty()) return fromItv(zero);
        AffItv r = x;
        if (r.b1 >= 0) {
            // Subtraction reverses the product's bound direction.
            r.b0 = detail::usesNativeBounds() ? detail::directedBinary(detail::BinaryOp::Sub, r.b0,
                detail::directedBinary(detail::BinaryOp::Mul, r.b1, nlo, detail::Direction::Down),
                detail::Direction::Up) : r.b0 - r.b1 * nlo;
        } else {
            r.b0 = std::max(x.hi(0), x.hi(fT));
            r.b1 = 0;
        }
        if (r.a1 <= 0) {
            r.a0 = detail::usesNativeBounds() ? detail::directedBinary(detail::BinaryOp::Sub, r.a0,
                detail::directedBinary(detail::BinaryOp::Mul, r.a1, nlo, detail::Direction::Up),
                detail::Direction::Down) : r.a0 - r.a1 * nlo;
        } else {
            r.a0 = std::min(x.lo(0), x.lo(fT));
            r.a1 = 0;
        }
        if (r.isEmpty())
            return fromItv(x.lsb >= 0 ? interval(-2147483648.0, 2147483647.0, x.lsb)
                                      : interval(-HUGE_VAL, HUGE_VAL, x.lsb));
        return ajoin(r, fromItv(zero), fT);
    }
};

/// The standalone numeric algebra: every FaustAlgebra operation over affine intervals,
/// testable in this repository, tlib-free.
using affine_algebra = AffineOps<FaustAlgebra<AffItv>>;

}  // namespace itv
