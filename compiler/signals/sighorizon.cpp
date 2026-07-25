/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "sighorizon.hh"

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "interval.hh"  // gAlgebra and itv::interval
#include "ppsig.hh"
#include "signalAlgebra.hh"
#include "sigtyperules.hh"

//----------------------------------------------------------------------------------------
// Affine-in-time intervals: lo(t) = a0 + a1*t, hi(t) = b0 + b1*t, valid on [0, T].
//
// An ordinary interval is the case a1 = b1 = 0. Emptiness follows the interval library's
// convention (NaN intercepts). The rates are what the interval domain cannot express:
// they DATE an accumulator's failure modes (int32 wrap, float absorption) analytically,
// instead of collapsing them into an infinity or a wrap range.
//
// Soundness of the two structural tricks:
//  - the JOIN of two forms is the chord through the endpoint hulls at t = 0 and t = T:
//    max of affine functions is convex, so its chord lies above it on [0, T] (and min is
//    concave, chord below) -- an affine over-approximation, never an under one;
//  - a DELAY shifts the moving bound's intercept by -n.lo * rate (a delayed read sees an
//    older, hence smaller for a growing bound, value). This is what makes an accumulator
//    STATIONARY at its true rate: for x = x@1 + c the fixpoint equation on intercepts is
//    b0 - rate + c = b0, solved by rate = c, and the iteration converges by equality
//    instead of climbing forever.
//----------------------------------------------------------------------------------------

namespace {

using itv::interval;

struct AffItv {
    double a0 = NAN, a1 = 0;  // lo(t)
    double b0 = NAN, b1 = 0;  // hi(t)
    int    lsb = 0;

    bool isEmpty() const { return std::isnan(a0) || std::isnan(b0); }
    bool isConst() const { return a1 == 0 && b1 == 0; }
    double lo(double t) const { return a1 == 0 ? a0 : a0 + a1 * t; }
    double hi(double t) const { return b1 == 0 ? b0 : b0 + b1 * t; }
};

AffItv aEmpty()
{
    return {};
}

AffItv fromItv(const interval& x)
{
    if (x.isEmpty()) return aEmpty();
    return {x.lo(), 0, x.hi(), 0, x.lsb()};
}

/// Collapse to the ordinary interval hull over [0, T].
///
/// An INTEGER chain's affine claim is only valid while its value fits int32: past that
/// date the real counter has wrapped and the form no longer bounds it, so the collapse
/// caps to the int32 range -- THE bridge from affine claims to interval facts is where
/// the wrap reality must re-enter. (A float chain stays bounded past absorption: the
/// value freezes, the form keeps over-approximating it.)
interval toItv(const AffItv& x, double T)
{
    if (x.isEmpty()) return itv::empty();
    const double lo = std::min(x.lo(0), x.lo(T));
    const double hi = std::max(x.hi(0), x.hi(T));
    // The cap applies to CONSTANT forms too: an integer interval beyond int32 cannot
    // describe any real int32 value -- the machine one has already wrapped.
    if (x.lsb >= 0 && (hi > 2147483647.0 || lo < -2147483648.0)) {
        return {-2147483648.0, 2147483647.0, x.lsb};
    }
    return {lo, hi, x.lsb};
}

/// x ⊑ y over [0, T] : affine bounds compare at the endpoints.
bool aleq(const AffItv& x, const AffItv& y, double T)
{
    if (x.isEmpty()) return true;
    if (y.isEmpty()) return false;
    return y.lo(0) <= x.lo(0) && y.lo(T) <= x.lo(T) && x.hi(0) <= y.hi(0) &&
           x.hi(T) <= y.hi(T);
}

/// Affine chord through two endpoint values; degenerates to a constant when possible.
void chord(double v0, double vT, double T, double& c0, double& c1)
{
    if (!std::isfinite(v0) || !std::isfinite(vT) || v0 == vT) {
        c0 = (v0 == vT) ? v0 : (std::isfinite(v0) ? vT : v0);  // keep the infinite side
        if (!std::isfinite(v0)) c0 = v0;
        if (!std::isfinite(vT)) c0 = vT;
        c1 = 0;
        return;
    }
    c0 = v0;
    c1 = (vT - v0) / T;
}

/// Join (reunion) of two forms: endpoint hulls, chorded back to affine. Sound by
/// convexity; exact when both are constant. Empty is neutral.
AffItv aJoin(const AffItv& x, const AffItv& y, double T)
{
    if (x.isEmpty()) return y;
    if (y.isEmpty()) return x;
    AffItv r;
    chord(std::min(x.lo(0), y.lo(0)), std::min(x.lo(T), y.lo(T)), T, r.a0, r.a1);
    chord(std::max(x.hi(0), y.hi(0)), std::max(x.hi(T), y.hi(T)), T, r.b0, r.b1);
    r.lsb = std::min(x.lsb, y.lsb);
    return r;
}

class HorizonAlgebra : public SignalAlgebra<AffItv> {
    static constexpr double kBig = 1073741824.0;  // 2^30

    double fT;         ///< the horizon, in samples (FAUST_HORIZON_SAMPLES, default 2^31)
    bool   fDefaults;  ///< parameters at their default values (nominal reading)

    /// Probe results, keyed by proj(b, var). Mutable : engine feedback, not denotation.
    mutable std::unordered_map<Tree, std::pair<AffItv, bool>> fProbe;

   public:
    /// defaultParams: parameters held at their DEFAULT values (nominal reading) instead
    /// of their full declared ranges (worst case). Buttons and checkboxes read released.
    explicit HorizonAlgebra(bool defaultParams = false) : fDefaults(defaultParams)
    {
        const char* h = getenv("FAUST_HORIZON_SAMPLES");
        fT           = h ? std::atof(h) : 2147483648.0;  // default: 2^31 samples
    }

    double horizon() const { return fT; }

    //--- lattice ----------------------------------------------------------------------
    AffItv bottom(Tree) const override { return aEmpty(); }
    AffItv top(Tree) const override { return fromItv(interval(-HUGE_VAL, HUGE_VAL)); }
    bool   lessEqual(const AffItv& x, const AffItv& y) const override
    {
        return aleq(x, y, fT);
    }
    bool converged(const AffItv& prev, const AffItv& cur) const override
    {
        return aleq(cur, prev, fT);  // stationary OR descending stops (see sigintervals)
    }
    AffItv project(Tree, int i, const std::vector<AffItv>& row) const override
    {
        return row[i];
    }

    int widenAfter() const override { return 8; }
    int maxNarrowingIterations() const override { return 3; }
    int maxIterations() const override { return 1000; }

    //--- probe: identical policy to the interval domain, in the rate-0 world -----------
    std::vector<AffItv> probeSeeds(Tree) const override
    {
        if (getenv("FAUST_ITV_NOPROBE") != nullptr) return {};
        return {fromItv(interval(0, kBig, 0)), fromItv(interval(-kBig, kBig, 0))};
    }
    void recordProbe(Tree var, const AffItv& probed, bool certified) const override
    {
        fProbe[var] = {probed, certified};
    }

    // Widening in three stages: (1) a certified rate-0 probe threshold absorbs the move;
    // (2) first widening of a bound PROPOSES a rate -- the increment observed over one
    // round -- which a genuine affine accumulator then makes stationary; (3) a bound
    // still moving despite a proposed rate is super-linear: escalate to the top of its
    // world (int32 saturation or ±inf, as in the interval domain).
    AffItv widen(Tree var, const AffItv& old, const AffItv& fresh) const override
    {
        if (old.isEmpty() || fresh.isEmpty()) return fresh;
        const bool wlo = fresh.lo(0) < old.lo(0) || fresh.lo(fT) < old.lo(fT);
        const bool whi = fresh.hi(0) > old.hi(0) || fresh.hi(fT) > old.hi(fT);
        if (!wlo && !whi) return fresh;

        // (1) certified probe threshold, rate-0 world only
        auto it = fProbe.find(var);
        if (it != fProbe.end() && it->second.second && fresh.isConst() && old.isConst()) {
            const AffItv&  p = it->second.first;
            const interval f = toItv(fresh, fT);
            if (!p.isEmpty() && p.isConst() && p.a0 <= f.lo() && f.hi() <= p.b0) {
                AffItv r = fresh;
                if (wlo) r.a0 = p.a0;
                if (whi) r.b0 = p.b0;
                r.lsb = std::min(fresh.lsb, p.lsb);
                return r;
            }
        }

        AffItv r = fresh;
        if (whi) {
            if (old.b1 == fresh.b1 && old.b1 == 0 && std::isfinite(fresh.b0 - old.b0)) {
                r.b1 = fresh.b0 - old.b0;  // (2) propose the observed per-round rate
            } else {
                r.b0 = (fresh.lsb >= 0) ? double(INT_MAX) : HUGE_VAL;  // (3) escalate
                r.b1 = 0;
                if (fresh.lsb < 0) r.lsb = std::min(fresh.lsb, -24);
            }
        }
        if (wlo) {
            if (old.a1 == fresh.a1 && old.a1 == 0 && std::isfinite(fresh.a0 - old.a0)) {
                r.a1 = fresh.a0 - old.a0;
            } else {
                r.a0 = (fresh.lsb >= 0) ? double(INT_MIN) : -HUGE_VAL;
                r.a1 = 0;
                if (fresh.lsb < 0) r.lsb = std::min(fresh.lsb, -24);
            }
        }
        return r;
    }

    //--- injections -------------------------------------------------------------------
    AffItv Nil() const override { return aEmpty(); }
    AffItv Label(const std::string&) const override { return aEmpty(); }
    AffItv IntNum(int x) const override { return fromItv(gAlgebra.IntNum(x)); }
    AffItv Int64Num(int64_t x) const override { return fromItv(gAlgebra.Int64Num(x)); }
    AffItv FloatNum(double x) const override { return fromItv(gAlgebra.FloatNum(x)); }
    AffItv FixPointUpdate(const AffItv& x, const AffItv& y) const override
    {
        return aJoin(x, y, fT);
    }

    AffItv Input(const AffItv&) const override { return fromItv(interval(-1, 1)); }
    AffItv Output(const AffItv&, const AffItv& x) const override { return x; }

    //--- user interface (rate 0 by nature) --------------------------------------------
    AffItv Button(const AffItv&) const override
    {
        if (fDefaults) return fromItv(interval(0, 0));  // released
        return fromItv(gAlgebra.Button(interval(0, 0)));
    }
    AffItv Checkbox(const AffItv&) const override
    {
        if (fDefaults) return fromItv(interval(0, 0));
        return fromItv(gAlgebra.Checkbox(interval(0, 0)));
    }
    AffItv VSlider(const AffItv&, const AffItv& c, const AffItv& l, const AffItv& h,
                   const AffItv& s) const override
    {
        if (fDefaults) return c;  // the default value, a singleton
        return fromItv(
            gAlgebra.VSlider(interval(0, 0), toItv(c, fT), toItv(l, fT), toItv(h, fT),
                             toItv(s, fT)));
    }
    AffItv HSlider(const AffItv&, const AffItv& c, const AffItv& l, const AffItv& h,
                   const AffItv& s) const override
    {
        if (fDefaults) return c;
        return fromItv(
            gAlgebra.HSlider(interval(0, 0), toItv(c, fT), toItv(l, fT), toItv(h, fT),
                             toItv(s, fT)));
    }
    AffItv NumEntry(const AffItv&, const AffItv& c, const AffItv& l, const AffItv& h,
                    const AffItv& s) const override
    {
        if (fDefaults) return c;
        return fromItv(
            gAlgebra.NumEntry(interval(0, 0), toItv(c, fT), toItv(l, fT), toItv(h, fT),
                              toItv(s, fT)));
    }
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

    //--- the affine-preserving core ---------------------------------------------------
    AffItv Add(const AffItv& x, const AffItv& y) const override
    {
        if (x.isEmpty() || y.isEmpty()) return aEmpty();
        return {x.a0 + y.a0, x.a1 + y.a1, x.b0 + y.b0, x.b1 + y.b1,
                std::min(x.lsb, y.lsb)};
    }
    AffItv Sub(const AffItv& x, const AffItv& y) const override
    {
        if (x.isEmpty() || y.isEmpty()) return aEmpty();
        return {x.a0 - y.b0, x.a1 - y.b1, x.b0 - y.a0, x.b1 - y.a1,
                std::min(x.lsb, y.lsb)};
    }
    AffItv Neg(const AffItv& x) const override
    {
        if (x.isEmpty()) return aEmpty();
        return {-x.b0, -x.b1, -x.a0, -x.a1, x.lsb};
    }
    // Multiplication / division by a rate-0 operand stays affine: the bounds are
    // min/max of affine functions, chorded at the endpoints (convexity argument).
    // Anything else collapses.
    AffItv Mul(const AffItv& x, const AffItv& y) const override
    {
        return mulDivByConst(x, y, /*isDiv*/ false);
    }
    AffItv Div(const AffItv& x, const AffItv& y) const override
    {
        return mulDivByConst(x, y, /*isDiv*/ true);
    }

    //--- delays: the temporal rule on forms -------------------------------------------
    AffItv Mem(const AffItv& x) const override { return delayed(x, 1, 1); }
    AffItv Delay(const AffItv& x, const AffItv& n) const override
    {
        const interval nn = toItv(n, fT);
        const double   nlo = (nn.isEmpty() || !std::isfinite(nn.lo()))
                                 ? 0
                                 : std::max(0.0, nn.lo());
        return delayed(x, nlo, nn.isEmpty() ? 0 : std::max(0.0, nn.hi()));
    }
    AffItv Prefix(const AffItv& x, const AffItv& y) const override
    {
        return aJoin(x, y, fT);
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

    //--- selection --------------------------------------------------------------------
    AffItv Select2(const AffItv&, const AffItv& x, const AffItv& y) const override
    {
        return aJoin(x, y, fT);
    }

    //--- casts ------------------------------------------------------------------------
    AffItv IntCast(const AffItv& x) const override
    {
        if (x.isEmpty()) return aEmpty();
        if (x.isConst()) return fromItv(gAlgebra.IntCast(toItv(x, fT)));
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

    //--- everything nonlinear collapses to the horizon interval (mirrored transfer) ----
    AffItv Mod(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Mod(a, b); });
    }
    AffItv Inv(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Inv(a); });
    }
    AffItv Abs(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Abs(a); });
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
        return c2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Gt(a, b); });
    }
    AffItv Lt(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Lt(a, b); });
    }
    AffItv Ge(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Ge(a, b); });
    }
    AffItv Le(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Le(a, b); });
    }
    AffItv Eq(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Eq(a, b); });
    }
    AffItv Ne(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Ne(a, b); });
    }
    AffItv Not(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Not(a); });
    }
    AffItv And(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.And(a, b));
        });
    }
    AffItv Or(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.Or(a, b));
        });
    }
    AffItv Xor(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.Xor(a, b));
        });
    }
    AffItv Lsh(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.Lsh(a, b));
        });
    }
    AffItv ARsh(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.ARsh(a, b));
        });
    }
    AffItv LRsh(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.LRsh(a, b));
        });
    }
    AffItv Acos(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Acos(a); });
    }
    AffItv Acosh(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Acosh(a); });
    }
    AffItv Asin(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Asin(a); });
    }
    AffItv Asinh(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Asinh(a); });
    }
    AffItv Atan(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Atan(a); });
    }
    AffItv Atan2(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y,
                  [](const interval& a, const interval& b) { return gAlgebra.Atan2(a, b); });
    }
    AffItv Atanh(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Atanh(a); });
    }
    AffItv Ceil(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Ceil(a); });
    }
    AffItv Cos(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Cos(a); });
    }
    AffItv Cosh(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Cosh(a); });
    }
    AffItv Exp(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Exp(a); });
    }
    AffItv Exp10(const AffItv& x) const override
    {
        return c1(x,
                  [](const interval& a) { return gAlgebra.Pow(interval(10, 10, 0), a); });
    }
    AffItv Floor(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Floor(a); });
    }
    AffItv Log(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Log(a); });
    }
    AffItv Log10(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Log10(a); });
    }
    AffItv Pow(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Pow(a, b); });
    }
    AffItv Remainder(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.Remainder(a, b);
        });
    }
    AffItv Rint(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Rint(a); });
    }
    AffItv Round(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Rint(a); });
    }
    AffItv Sin(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Sin(a); });
    }
    AffItv Sinh(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Sinh(a); });
    }
    AffItv Sqrt(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Sqrt(a); });
    }
    AffItv Tan(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Tan(a); });
    }
    AffItv Tanh(const AffItv& x) const override
    {
        return c1(x, [](const interval& a) { return gAlgebra.Tanh(a); });
    }
    AffItv Max(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Max(a, b); });
    }
    AffItv Min(const AffItv& x, const AffItv& y) const override
    {
        return c2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Min(a, b); });
    }

    //--- tables -----------------------------------------------------------------------
    AffItv Table(const AffItv&, const AffItv& content) const override { return content; }
    AffItv WRTbl(const AffItv&, const AffItv& g, const AffItv&,
                 const AffItv& ws) const override
    {
        return aJoin(g, ws, fT);
    }
    AffItv RDTbl(const AffItv& tbl, const AffItv&) const override { return tbl; }
    AffItv Gen(const AffItv& x) const override { return x; }
    AffItv Waveform(const std::vector<AffItv>& w) const override
    {
        AffItv r = aEmpty();
        for (const AffItv& x : w) {
            r = aJoin(r, x, fT);
        }
        return r;
    }

    //--- soundfiles -------------------------------------------------------------------
    AffItv SoundFile(const AffItv&) const override
    {
        return fromItv(interval(0, double(INT32_MAX)));
    }
    AffItv SoundFileRate(const AffItv&, const AffItv&) const override
    {
        return fromItv(interval(0, double(INT32_MAX)));
    }
    AffItv SoundFileLength(const AffItv&, const AffItv&) const override
    {
        return fromItv(interval(0, double(INT32_MAX)));
    }
    AffItv SoundFileBuffer(const AffItv&, const AffItv&, const AffItv&,
                           const AffItv&) const override
    {
        return fromItv(interval(-1, 1));
    }

    //--- foreign entities -------------------------------------------------------------
    AffItv ForeignConst(int, const AffItv&, const AffItv&) const override
    {
        return aEmpty();
    }
    AffItv ForeignVar(int, const AffItv&, const AffItv&) const override
    {
        return aEmpty();
    }
    AffItv ForeignFunction(int, const std::vector<AffItv>&) const override
    {
        return aEmpty();
    }

    //--- signal-language-only ----------------------------------------------------------
    AffItv DocConstantTbl(const AffItv&, const AffItv& init) const override
    {
        return init;
    }
    AffItv DocWriteTbl(const AffItv&, const AffItv& init, const AffItv&,
                       const AffItv&) const override
    {
        return init;
    }
    AffItv DocAccessTbl(const AffItv& tbl, const AffItv&) const override { return tbl; }
    AffItv Register(int, const AffItv& s) const override { return s; }
    AffItv Tuple(int, const std::vector<AffItv>&) const override { return aEmpty(); }
    AffItv TupleAccess(const AffItv& ts, const AffItv&) const override { return ts; }

   private:

    template <typename F>
    AffItv c1(const AffItv& x, F f) const
    {
        if (x.isEmpty()) return aEmpty();
        return fromItv(f(toItv(x, fT)));
    }
    template <typename F>
    AffItv c2(const AffItv& x, const AffItv& y, F f) const
    {
        if (x.isEmpty() || y.isEmpty()) return aEmpty();
        return fromItv(f(toItv(x, fT), toItv(y, fT)));
    }

    /// Multiplication (or division) where at most one operand carries a rate: evaluate
    /// the mirrored gAlgebra transfer at both endpoints, chord back. Two rated operands
    /// would be quadratic in t: collapse.
    AffItv mulDivByConst(const AffItv& x, const AffItv& y, bool isDiv) const
    {
        if (x.isEmpty() || y.isEmpty()) return aEmpty();
        auto op = [&](const interval& a, const interval& b) {
            return isDiv ? gAlgebra.Div(a, b) : gAlgebra.Mul(a, b);
        };
        if (x.isConst() && y.isConst()) {
            return fromItv(op(toItv(x, fT), toItv(y, fT)));
        }
        if (!x.isConst() && !y.isConst()) {
            return fromItv(op(toItv(x, fT), toItv(y, fT)));  // quadratic: collapse
        }
        auto at = [&](double t) {
            return op(interval(x.lo(t), x.hi(t), x.lsb), interval(y.lo(t), y.hi(t), y.lsb));
        };
        const interval r0 = at(0), rT = at(fT);
        if (r0.isEmpty() || rT.isEmpty()) return aEmpty();
        AffItv r;
        chord(r0.lo(), rT.lo(), fT, r.a0, r.a1);
        chord(r0.hi(), rT.hi(), fT, r.b0, r.b1);
        r.lsb = std::min(r0.lsb(), rT.lsb());
        return r;
    }

    /// x delayed by n ∈ [nlo, nhi] samples, then joined with the initial condition.
    /// A growing bound shifted back in time is smaller: intercept -= n.lo * rate is the
    /// sound shift (max over the n range), and the shift is what makes accumulators
    /// stationary. A bound whose rate has the wrong sign for that argument collapses to
    /// its worst constant over the window instead.
    AffItv delayed(const AffItv& x, double nlo, double /*nhi*/) const
    {
        if (x.isEmpty()) return fromItv(interval(0, 0));
        AffItv r = x;
        if (r.b1 >= 0) {
            r.b0 -= r.b1 * nlo;
        } else {
            r.b0 = std::max(x.hi(0), x.hi(fT));  // worst constant ceiling
            r.b1 = 0;
        }
        if (r.a1 <= 0) {
            r.a0 -= r.a1 * nlo;
        } else {
            r.a0 = std::min(x.lo(0), x.lo(fT));  // worst constant floor
            r.a1 = 0;
        }
        return aJoin(r, fromItv(interval(0, 0)), fT);
    }

};

//----------------------------------------------------------------------------------------
// The report: date every rate-carrying accumulator.
//----------------------------------------------------------------------------------------

std::string fmtSamples(double s)
{
    std::ostringstream o;
    if (!std::isfinite(s)) {
        o << "jamais";
        return o.str();
    }
    const double sec = s / 48000.0;  // display convention: 48 kHz
    o.precision(3);
    if (sec < 60) {
        o << sec << " s";
    } else if (sec < 3600) {
        o << sec / 60 << " min";
    } else if (sec < 86400) {
        o << sec / 3600 << " h";
    } else {
        o << sec / 86400 << " j";
    }
    o << " @48kHz (" << std::scientific << s << " éch.)";
    return o.str();
}

}  // namespace

namespace {

/// One dated pass over the recursive variables with a given parameter policy.
std::pair<std::vector<HorizonEvent>, double> datePass(const RecPlan& plan,
                                                      HorizonAlgebra& algebra, bool verbose,
                                                      const char* tag)
{
    FixPointIterator<AffItv> it(plan, algebra);

    std::vector<HorizonEvent> events;
    double                    horizon = -1;
    const double              INF     = HUGE_VAL;

    for (const std::vector<Tree>& comp : plan.components()) {
        for (Tree var : comp) {
            const std::vector<AffItv>& row = it.variableValue(var);
            for (int b = 0; b < static_cast<int>(row.size()); ++b) {
                const AffItv& v = row[b];
                if (v.isEmpty() || (v.a1 == 0 && v.b1 == 0)) continue;
                if (!std::isfinite(v.a0) || !std::isfinite(v.b0)) continue;

                HorizonEvent e;
                {
                    std::ostringstream name;
                    name << ppsig(proj(b, var), 30);
                    e.signal = name.str();
                }
                e.rate = std::max(std::fabs(v.a1), std::fabs(v.b1));

                // int32 wrap: the growing bound reaches the int range's edge
                e.wrapAt = INF;
                if (v.lsb >= 0) {
                    if (v.b1 > 0) e.wrapAt = std::min(e.wrapAt, (2147483647.0 - v.b0) / v.b1);
                    if (v.a1 < 0) e.wrapAt = std::min(e.wrapAt, (-2147483648.0 - v.a0) / v.a1);
                }

                // float absorption: |value| reaches 2^p * increment, the add is absorbed
                e.absorb32At = INF;
                e.absorb53At = INF;
                if (v.lsb < 0) {
                    auto absorb = [&](double p) {
                        double t = INF;
                        if (v.b1 > 0) t = std::min(t, p - v.b0 / v.b1);
                        if (v.a1 < 0) t = std::min(t, p - v.a0 / v.a1);
                        return std::max(0.0, t);
                    };
                    e.absorb32At = absorb(16777216.0);          // 2^24
                    e.absorb53At = absorb(9007199254740992.0);  // 2^53
                }

                const double first = std::min(e.wrapAt, e.absorb32At);
                if (horizon < 0 || first < horizon) horizon = first;

                if (verbose) {
                    std::cerr << "HORIZON " << tag << " : rate " << e.rate << "/éch.";
                    if (e.wrapAt != INF) std::cerr << ", wrap int32 à " << fmtSamples(e.wrapAt);
                    if (e.absorb32At != INF) {
                        std::cerr << ", absorption float à " << fmtSamples(e.absorb32At)
                                  << " (double : " << fmtSamples(e.absorb53At) << ")";
                    }
                    std::cerr << " : " << e.signal << std::endl;
                }
                events.push_back(std::move(e));
            }
        }
    }
    return {std::move(events), horizon};
}

}  // namespace

HorizonReport horizonAnalysis(Tree L, bool verbose)
{
    RecPlan plan(L);

    // Worst case: parameters anywhere in their declared ranges.
    HorizonAlgebra worst(/*defaultParams*/ false);
    auto [wev, wt] = datePass(plan, worst, verbose, "pire-cas");

    // Nominal: parameters at their default values, buttons released.
    HorizonAlgebra nominal(/*defaultParams*/ true);
    auto [nev, nt] = datePass(plan, nominal, verbose, "défauts ");

    HorizonReport report;
    report.events                = std::move(wev);
    report.horizonSamples        = wt;
    report.horizonDefaultSamples = nt;
    report.defaultEventCount     = int(nev.size());

    if (verbose) {
        auto line = [](const char* tag, double t, std::size_t n) {
            std::cerr << "HORIZON T* " << tag << " : ";
            if (n == 0) {
                std::cerr << "aucun accumulateur daté (sémantique exacte sans limite)";
            } else {
                std::cerr << fmtSamples(t) << " (" << n << " accumulateur(s) daté(s))";
            }
            std::cerr << std::endl;
        };
        line("(pire-cas)", wt, report.events.size());
        line("(défauts) ", nt, std::size_t(report.defaultEventCount));
    }
    return report;
}


//----------------------------------------------------------------------------------------
// HorizonReader: the horizon-bounded interval of any signal, for the roles report.
//----------------------------------------------------------------------------------------

struct HorizonReader::Impl {
    RecPlan                  plan;
    HorizonAlgebra           algebra;
    FixPointIterator<AffItv> it;

    explicit Impl(Tree L) : plan(L), algebra(/*defaultParams*/ false), it(plan, algebra) {}
};

HorizonReader::HorizonReader(Tree L) : fImpl(new Impl(L)) {}

HorizonReader::~HorizonReader()
{
    delete fImpl;
}

itv::interval HorizonReader::at(Tree sig) const
{
    // toItv caps integer chains at the int32 range past their wrap date.
    return toItv(fImpl->it.value(sig), fImpl->algebra.horizon());
}
