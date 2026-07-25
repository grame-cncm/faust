/* Copyright 2026 Yann ORLAREY
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

    //--- injections -------------------------------------------------------------------
    AffItv Label(const std::string&) const override { return aempty(); }
    AffItv IntNum(int x) const override { return fromItv(fItv.IntNum(x)); }
    AffItv Int64Num(int64_t x) const override { return fromItv(fItv.Int64Num(x)); }
    AffItv FloatNum(double x) const override { return fromItv(fItv.FloatNum(x)); }
    AffItv FixPointUpdate(const AffItv& x, const AffItv& y) const override
    {
        return ajoin(x, y, fT);
    }

    AffItv Input(const AffItv&) const override { return fromItv(interval(-1, 1)); }
    AffItv Output(const AffItv&, const AffItv& x) const override { return x; }

    //--- user interface (rate 0 by nature) --------------------------------------------
    AffItv Button(const AffItv&) const override
    {
        if (fDefaults) return fromItv(interval(0, 0));  // released
        return fromItv(fItv.Button(interval(0, 0)));
    }
    AffItv Checkbox(const AffItv&) const override
    {
        if (fDefaults) return fromItv(interval(0, 0));
        return fromItv(fItv.Checkbox(interval(0, 0)));
    }
    AffItv VSlider(const AffItv&, const AffItv& c, const AffItv& l, const AffItv& h,
                   const AffItv& s) const override
    {
        if (fDefaults) return c;  // the default value, a singleton
        return fromItv(fItv.VSlider(interval(0, 0), toItv(c, fT), toItv(l, fT),
                                    toItv(h, fT), toItv(s, fT)));
    }
    AffItv HSlider(const AffItv&, const AffItv& c, const AffItv& l, const AffItv& h,
                   const AffItv& s) const override
    {
        if (fDefaults) return c;
        return fromItv(fItv.HSlider(interval(0, 0), toItv(c, fT), toItv(l, fT),
                                    toItv(h, fT), toItv(s, fT)));
    }
    AffItv NumEntry(const AffItv&, const AffItv& c, const AffItv& l, const AffItv& h,
                    const AffItv& s) const override
    {
        if (fDefaults) return c;
        return fromItv(fItv.NumEntry(interval(0, 0), toItv(c, fT), toItv(l, fT),
                                     toItv(h, fT), toItv(s, fT)));
    }
    // A bargraph reports the displayed signal; the range bounds do not participate.
    AffItv HBargraph(const AffItv&, const AffItv&, const AffItv&,
                     const AffItv& s) const override
    {
        return s;
    }
    AffItv VBargraph(const AffItv&, const AffItv&, const AffItv&,
                     const AffItv& s) const override
    {
        return s;
    }

    AffItv Attach(const AffItv& x, const AffItv&) const override { return x; }
    AffItv Enable(const AffItv& x, const AffItv&) const override { return x; }
    AffItv Control(const AffItv& x, const AffItv&) const override { return x; }

    //--- the affine-preserving (linear) regime ----------------------------------------
    AffItv Add(const AffItv& x, const AffItv& y) const override
    {
        if (x.isEmpty() || y.isEmpty()) return aempty();
        return {x.a0 + y.a0, x.a1 + y.a1, x.b0 + y.b0, x.b1 + y.b1,
                std::min(x.lsb, y.lsb)};
    }
    AffItv Sub(const AffItv& x, const AffItv& y) const override
    {
        if (x.isEmpty() || y.isEmpty()) return aempty();
        return {x.a0 - y.b0, x.a1 - y.b1, x.b0 - y.a0, x.b1 - y.a1,
                std::min(x.lsb, y.lsb)};
    }
    AffItv Neg(const AffItv& x) const override
    {
        if (x.isEmpty()) return aempty();
        return {-x.b0, -x.b1, -x.a0, -x.a1, x.lsb};
    }
    AffItv Mul(const AffItv& x, const AffItv& y) const override
    {
        return mulDivByConst(x, y, /*isDiv*/ false);
    }
    AffItv Div(const AffItv& x, const AffItv& y) const override
    {
        return mulDivByConst(x, y, /*isDiv*/ true);
    }

    //--- delays: the temporal rule on forms -------------------------------------------
    AffItv Mem(const AffItv& x) const override { return delayed(x, 1); }
    AffItv Delay(const AffItv& x, const AffItv& n) const override
    {
        const interval nn = toItv(n, fT);
        const double   nlo =
            (nn.isEmpty() || !std::isfinite(nn.lo())) ? 0 : std::max(0.0, nn.lo());
        return delayed(x, nlo);
    }
    AffItv Prefix(const AffItv& x, const AffItv& y) const override
    {
        return ajoin(x, y, fT);
    }
    AffItv AssertBounds(const AffItv& lo, const AffItv& hi,
                        const AffItv& x) const override
    {
        const interval l = toItv(lo, fT), h = toItv(hi, fT), xx = toItv(x, fT);
        if (l.isEmpty() || h.isEmpty()) return x;
        if (xx.isEmpty()) return fromItv(interval(l.lo(), h.hi()));
        return fromItv(
            interval(std::max(xx.lo(), l.lo()), std::min(xx.hi(), h.hi()), xx.lsb()));
    }

    //--- selection: value attribute, the selector is excluded -------------------------
    AffItv Select2(const AffItv&, const AffItv& x, const AffItv& y) const override
    {
        return ajoin(x, y, fT);
    }

    //--- casts ------------------------------------------------------------------------
    AffItv IntCast(const AffItv& x) const override
    {
        if (x.isEmpty()) return aempty();
        if (x.isConst()) return fromItv(fItv.IntCast(toItv(x, fT)));
        // truncation keeps affinity with one unit of slack, and marks the chain integer
        return {x.a0 - 1, x.a1, x.b0 + 1, x.b1, 0};
    }
    AffItv BitCast(const AffItv& x) const override { return x; }
    AffItv FloatCast(const AffItv& x) const override
    {
        if (x.isEmpty() || x.isConst()) return x;
        AffItv r = x;
        r.lsb    = std::min(x.lsb, -24);  // the value is now carried by a float
        return r;
    }

    //--- the nonlinear regime: collapse to the oracle ---------------------------------
    AffItv Mod(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Mod(a, b); });
    }
    AffItv Inv(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Inv(a); });
    }
    AffItv Abs(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Abs(a); });
    }
    AffItv Highest(const AffItv& x) const override
    {
        return fromItv(interval(toItv(x, fT).hi()));
    }
    AffItv Lowest(const AffItv& x) const override
    {
        return fromItv(interval(toItv(x, fT).lo()));
    }
    AffItv Gt(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Gt(a, b); });
    }
    AffItv Lt(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Lt(a, b); });
    }
    AffItv Ge(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Ge(a, b); });
    }
    AffItv Le(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Le(a, b); });
    }
    AffItv Eq(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Eq(a, b); });
    }
    AffItv Ne(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Ne(a, b); });
    }
    AffItv Not(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Not(a); });
    }
    AffItv And(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.And(a, b));
        });
    }
    AffItv Or(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.Or(a, b));
        });
    }
    AffItv Xor(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.Xor(a, b));
        });
    }
    AffItv Lsh(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.Lsh(a, b));
        });
    }
    AffItv ARsh(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.ARsh(a, b));
        });
    }
    AffItv LRsh(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.IntCast(fItv.LRsh(a, b));
        });
    }
    AffItv Acos(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Acos(a); });
    }
    AffItv Acosh(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Acosh(a); });
    }
    AffItv Asin(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Asin(a); });
    }
    AffItv Asinh(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Asinh(a); });
    }
    AffItv Atan(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Atan(a); });
    }
    AffItv Atan2(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y,
                  [this](const interval& a, const interval& b) { return fItv.Atan2(a, b); });
    }
    AffItv Atanh(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Atanh(a); });
    }
    AffItv Ceil(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Ceil(a); });
    }
    AffItv Cos(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Cos(a); });
    }
    AffItv Cosh(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Cosh(a); });
    }
    AffItv Exp(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Exp(a); });
    }
    AffItv Exp10(const AffItv& x) const override
    {
        // mirrors exp10prim: Pow(10, x)
        return c1(x, [this](const interval& a) { return fItv.Pow(interval(10, 10, 0), a); });
    }
    AffItv Floor(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Floor(a); });
    }
    AffItv Log(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Log(a); });
    }
    AffItv Log10(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Log10(a); });
    }
    AffItv Pow(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Pow(a, b); });
    }
    AffItv Remainder(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) {
            return fItv.Remainder(a, b);
        });
    }
    AffItv Rint(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Rint(a); });
    }
    AffItv Round(const AffItv& x) const override
    {
        // mirrors roundprim: delegated to Rint
        return c1(x, [this](const interval& a) { return fItv.Rint(a); });
    }
    AffItv Sin(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Sin(a); });
    }
    AffItv Sinh(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Sinh(a); });
    }
    AffItv Sqrt(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Sqrt(a); });
    }
    AffItv Tan(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Tan(a); });
    }
    AffItv Tanh(const AffItv& x) const override
    {
        return c1(x, [this](const interval& a) { return fItv.Tanh(a); });
    }
    AffItv Max(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Max(a, b); });
    }
    AffItv Min(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [this](const interval& a, const interval& b) { return fItv.Min(a, b); });
    }

    //--- tables -----------------------------------------------------------------------
    AffItv RDTbl(const AffItv& tbl, const AffItv&) const override { return tbl; }
    AffItv WRTbl(const AffItv&, const AffItv& g, const AffItv&,
                 const AffItv& ws) const override
    {
        return ajoin(g, ws, fT);
    }
    AffItv Gen(const AffItv& x) const override { return x; }
    AffItv Waveform(const std::vector<AffItv>& w) const override
    {
        AffItv r = aempty();
        for (const AffItv& x : w) {
            r = ajoin(r, x, fT);
        }
        return r;
    }

    //--- soundfiles -------------------------------------------------------------------
    AffItv SoundFile(const AffItv&) const override
    {
        return fromItv(interval(0, 2147483647.0));
    }
    AffItv SoundFileRate(const AffItv&, const AffItv&) const override
    {
        return fromItv(interval(0, 2147483647.0));
    }
    AffItv SoundFileLength(const AffItv&, const AffItv&) const override
    {
        return fromItv(interval(0, 2147483647.0));
    }
    AffItv SoundFileBuffer(const AffItv&, const AffItv&, const AffItv&,
                           const AffItv&) const override
    {
        return fromItv(interval(-1, 1));
    }

    //--- foreign entities: interval() is FULLFINITE -- a sound near-top ("unknown =
    // could be anything"), exactly what the current type system stores. NOT the empty
    // interval: empty is neutral in joins, which would let select2(c, fconst, k) claim
    // [k, k] -- unsound optimism.
    AffItv ForeignConst(int, const AffItv&, const AffItv&) const override
    {
        return fromItv(interval());
    }
    AffItv ForeignVar(int, const AffItv&, const AffItv&) const override
    {
        return fromItv(interval());
    }
    AffItv ForeignFunction(int, const std::vector<AffItv>&) const override
    {
        return fromItv(interval());
    }

   protected:
    template <typename F>
    AffItv c1(const AffItv& x, F f) const
    {
        if (x.isEmpty()) return aempty();
        return fromItv(f(toItv(x, fT)));
    }
    template <typename F>
    AffItv c2(const AffItv& x, const AffItv& y, F f) const
    {
        if (x.isEmpty() || y.isEmpty()) return aempty();
        return fromItv(f(toItv(x, fT), toItv(y, fT)));
    }

    /// Multiplication (or division) where at most one operand carries a rate: evaluate
    /// the oracle at both endpoints, chord back (min/max of affine functions, sound by
    /// convexity). Two rated operands would be quadratic in t: collapse.
    AffItv mulDivByConst(const AffItv& x, const AffItv& y, bool isDiv) const
    {
        if (x.isEmpty() || y.isEmpty()) return aempty();
        auto op = [&](const interval& a, const interval& b) {
            return isDiv ? fItv.Div(a, b) : fItv.Mul(a, b);
        };
        if (x.isConst() == y.isConst()) {  // both const, or both rated (quadratic)
            return fromItv(op(toItv(x, fT), toItv(y, fT)));
        }
        auto at = [&](double t) {
            return op(interval(x.lo(t), x.hi(t), x.lsb), interval(y.lo(t), y.hi(t), y.lsb));
        };
        const interval r0 = at(0), rT = at(fT);
        if (r0.isEmpty() || rT.isEmpty()) return aempty();
        AffItv r;
        achord(r0.lo(), rT.lo(), fT, r.a0, r.a1);
        achord(r0.hi(), rT.hi(), fT, r.b0, r.b1);
        r.lsb = std::min(r0.lsb(), rT.lsb());
        return r;
    }

    /// x delayed by at least nlo samples, then joined with the initial condition. A
    /// growing bound shifted back in time is smaller: intercept -= nlo * rate is the
    /// sound shift, and the shift is what makes accumulators stationary. A bound whose
    /// rate has the wrong sign collapses to its worst constant over the window.
    AffItv delayed(const AffItv& x, double nlo) const
    {
        if (x.isEmpty()) return fromItv(interval(0, 0));
        AffItv r = x;
        if (r.b1 >= 0) {
            r.b0 -= r.b1 * nlo;
        } else {
            r.b0 = std::max(x.hi(0), x.hi(fT));
            r.b1 = 0;
        }
        if (r.a1 <= 0) {
            r.a0 -= r.a1 * nlo;
        } else {
            r.a0 = std::min(x.lo(0), x.lo(fT));
            r.a1 = 0;
        }
        return ajoin(r, fromItv(interval(0, 0)), fT);
    }
};

/// The standalone numeric algebra: every FaustAlgebra operation over affine intervals,
/// testable in this repository, tlib-free.
using affine_algebra = AffineOps<FaustAlgebra<AffItv>>;

}  // namespace itv
