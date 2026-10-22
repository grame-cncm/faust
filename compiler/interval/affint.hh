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

#include <initializer_list>

#include <algorithm>
#include <cmath>

#include "interval_def.hh"
#include "directed_rounding.hh"

/**
 * Affine-in-time intervals: x(t) ∈ [a0 + a1·t, b0 + b1·t] for t ∈ [0, T].
 *
 * An ordinary interval is the case a1 = b1 = 0 (a horizontal corridor); an accumulator
 * is a corridor whose ceiling climbs at its rate. The type is the smallest useful
 * fragment of the polyhedral domain (Cousot–Halbwachs 1978) — a trapezoid in the
 * (t, value) plane, four doubles, every operation O(1), fixpoints in closed form.
 *
 * The ordinary interval domain lives inside this one twice over: as the rate-0
 * subdomain (fromItv / toItv), and as the semantic oracle of the nonlinear operations,
 * which collapse their operands to the hull over [0, T] and delegate to
 * interval_algebra (see affine_ops.hh).
 *
 * Numeric emptiness follows the interval convention: NaN intercepts. A separate
 * invalidity flag survives empty results and participates in fixpoint ordering.
 */

namespace itv {

struct AffItv {
    // Numeric coefficients and nature are independent of execution validity.
    double a0 = NAN, a1 = 0;  ///< lo(t) = a0 + a1·t
    double b0 = NAN, b1 = 0;  ///< hi(t) = b0 + b1·t
    int    lsb = 0;           ///< precision, as in itv::interval
    bool   mayBeInvalid = false;  ///< a possible NaN or undefined operation
    bool   mayOverflow  = false;  ///< the int32 operation may wrap (interval::mayOverflow)
    // A bound that keeps moving past the horizon although its rate is 0 : the corridor of
    // a nonlinear operation whose operands move, reduced to its hull over [0, T].
    bool   loDrifts = false;  ///< the lower bound may go on decreasing past T
    bool   hiDrifts = false;  ///< the upper bound may go on increasing past T

    // Public API: monotonically add invalidity without changing the corridor.
    AffItv withInvalid(bool possible = true) const
    {
        AffItv result = *this;
        result.mayBeInvalid = mayBeInvalid || possible;
        return result;
    }
    // Public API: monotonically add a possible overflow. An int32 value that may wrap may
    // hold any int32 value once it has wrapped : both its bounds move past the horizon.
    AffItv withOverflow(bool possible = true) const
    {
        AffItv result = *this;
        result.mayOverflow = mayOverflow || possible;
        return result.wrapDrift();
    }
    // Public API: an int32 value that may wrap drifts on both sides.
    AffItv wrapDrift() const
    {
        AffItv result = *this;
        if (result.lsb >= 0 && result.mayOverflow) result.loDrifts = result.hiDrifts = true;
        return result;
    }

    bool   isEmpty() const { return std::isnan(a0) || std::isnan(b0); }
    bool   isConst() const { return a1 == 0 && b1 == 0; }
    // A corridor that does not move bounds its values for all time ; a moving one only up
    // to the horizon.
    bool   moving() const { return a1 != 0 || b1 != 0 || loDrifts || hiDrifts; }
    // Public API: enclose evaluation of the lower/upper affine line. In float/double
    // mode both product and sum round outward; t=0 avoids an inf*0 corner.
    double lo(double t) const
    {
        if (a1 == 0 || t == 0) return a0;
        if (!detail::usesNativeBounds()) return a0 + a1 * t;
        const double result = detail::directedBinary(detail::BinaryOp::Add, a0,
            detail::directedBinary(detail::BinaryOp::Mul, a1, t, detail::Direction::Down),
            detail::Direction::Down);
        // An indeterminate extended-real expression must not remove other
        // numeric states from a corridor used as an analysis bound.
        return std::isnan(result) ? -HUGE_VAL : result;
    }
    double hi(double t) const
    {
        if (b1 == 0 || t == 0) return b0;
        if (!detail::usesNativeBounds()) return b0 + b1 * t;
        const double result = detail::directedBinary(detail::BinaryOp::Add, b0,
            detail::directedBinary(detail::BinaryOp::Mul, b1, t, detail::Direction::Up),
            detail::Direction::Up);
        return std::isnan(result) ? HUGE_VAL : result;
    }
};

/// x, its bounds drifting as well where those of y drift (a join, a widening)
inline AffItv adrift(AffItv x, const AffItv& y)
{
    x.loDrifts = x.loDrifts || y.loDrifts;
    x.hiDrifts = x.hiDrifts || y.hiDrifts;
    return x;
}

/// x with its bounds exchanged for the drifts : the bound of -x or of z - x that x's
/// upper bound makes is a lower one
inline AffItv flipped(AffItv x)
{
    std::swap(x.loDrifts, x.hiDrifts);
    return x;
}

/// Bottom: no values yet. Neutral in every join.
inline AffItv aempty()
{
    return {};
}

/// Public API: lift an ordinary interval to a horizontal corridor, preserving
/// numeric emptiness, nature and possible invalid execution.
inline AffItv fromItv(const interval& x)
{
    // Empty numeric bounds can still carry invalid execution and its nature.
    return AffItv{x.lo(), 0, x.hi(), 0, x.lsb(), x.mayBeInvalid(), x.mayOverflow()}.wrapDrift();
}

/// Collapse to the ordinary interval hull over [0, T] — THE bridge from affine claims
/// to interval facts. An INTEGER chain's claim is only valid while its value fits
/// int32: past that date the real counter has wrapped and the form no longer bounds
/// it, so the collapse caps to the int32 range (constant forms included: an integer
/// interval beyond int32 describes no real int32 value). A float chain stays bounded
/// past absorption — the value freezes, the form keeps over-approximating it.
inline interval toItv(const AffItv& x, double T)
{
    if (x.isEmpty()) return empty(x.lsb).withInvalid(x.mayBeInvalid).withOverflow(x.mayOverflow);
    const double lo = std::min(x.lo(0), x.lo(T));
    const double hi = std::max(x.hi(0), x.hi(T));
    if (x.lsb >= 0 && (hi > 2147483647.0 || lo < -2147483648.0)) {
        return interval(-2147483648.0, 2147483647.0, x.lsb, x.mayBeInvalid)
            .withOverflow(x.mayOverflow);
    }
    return interval(lo, hi, x.lsb, x.mayBeInvalid).withOverflow(x.mayOverflow);
}

/// The values of x for all time : its hull over [0, T], each moving bound pushed to the
/// limit of its nature (the int32 range for an integer, infinity for a float). An integer
/// does not leave the int32 range without an operation that may wrap, flagged on its own.
inline interval forever(const AffItv& x, double T)
{
    const interval h = toItv(x, T);
    if (h.isEmpty() || !x.moving()) return h;
    const bool   integer = x.lsb >= 0;
    const double lo      = (x.a1 != 0 || x.loDrifts) ? (integer ? -2147483648.0 : -HUGE_VAL) : h.lo();
    const double hi      = (x.b1 != 0 || x.hiDrifts) ? (integer ? 2147483647.0 : HUGE_VAL) : h.hi();
    return interval(lo, hi, h.lsb(), h.mayBeInvalid()).withOverflow(h.mayOverflow());
}

/// Public API: prove x ⊑ y over [0,T], T>=0, by comparing exact affine lines at
/// both endpoints. In float/double mode an upward enclosure of each difference must
/// be nonpositive; comparing two separately rounded values could give a false proof.
/// An invalid execution in x also requires a corresponding alert in y.
inline bool aleq(const AffItv& x, const AffItv& y, double T)
{
    // An unchanged corridor with a new alert is a new abstract state.
    if (x.mayBeInvalid && !y.mayBeInvalid) return false;
    if (x.mayOverflow && !y.mayOverflow) return false;
    if ((x.loDrifts && !y.loDrifts) || (x.hiDrifts && !y.hiDrifts)) return false;
    if (x.isEmpty()) return true;
    if (y.isEmpty()) return false;
    if (detail::usesNativeBounds()) {
        auto leq = [](double a0, double a1, double b0, double b1, double t) {
            if (a0 == b0 && a1 == b1) return true;
            double difference = detail::directedBinary(detail::BinaryOp::Sub, a0, b0,
                                                       detail::Direction::Up);
            if (t != 0) {
                const double rate = detail::directedBinary(detail::BinaryOp::Sub, a1, b1,
                                                           detail::Direction::Up);
                difference = detail::directedBinary(detail::BinaryOp::Add, difference,
                    detail::directedBinary(detail::BinaryOp::Mul, rate, t, detail::Direction::Up),
                    detail::Direction::Up);
            }
            return difference <= 0;
        };
        return leq(y.a0, y.a1, x.a0, x.a1, 0) && leq(y.a0, y.a1, x.a0, x.a1, T) &&
               leq(x.b0, x.b1, y.b0, y.b1, 0) && leq(x.b0, x.b1, y.b0, y.b1, T);
    }
    return y.lo(0) <= x.lo(0) && y.lo(T) <= x.lo(T) && x.hi(0) <= y.hi(0) &&
           x.hi(T) <= y.hi(T);
}

/// x ⊑ y over [0, T] only : what happens past the horizon (the drifts, an overflow on the
/// values for all time) set aside. A probe seed claims a bound over [0, T] ; its image
/// keeps its own drifts.
inline bool aleqWithin(AffItv x, AffItv y, double T)
{
    x.loDrifts = x.hiDrifts = x.mayOverflow = false;
    y.loDrifts = y.hiDrifts = y.mayOverflow = false;
    return aleq(x, y, T);
}

/// Public API: write a lower chord (upper when upper=true) over [0,T], T>=0.
/// Directed subtraction and division enclose the slope in float/double mode. A zero
/// horizon or nonfinite endpoints use a constant hull in the requested direction.
inline void achord(double v0, double vT, double T, double& c0, double& c1, bool upper = false)
{
    if (!std::isfinite(v0) || !std::isfinite(vT) || v0 == vT || T <= 0 || !std::isfinite(T)) {
        c0 = upper ? std::max(v0, vT) : std::min(v0, vT);
        c1 = 0;
        return;
    }
    c0 = v0;
    if (detail::usesNativeBounds()) {
        const auto direction = upper ? detail::Direction::Up : detail::Direction::Down;
        c1 = detail::directedBinary(detail::BinaryOp::Div,
            detail::directedBinary(detail::BinaryOp::Sub, vT, v0, direction), T, direction);
    } else {
        c1 = (vT - v0) / T;
    }
}

/// Join (reunion) of two forms: endpoint hulls, chorded back to affine. Sound by
/// convexity — max of affine functions is convex, so its chord lies above it on
/// [0, T] (and min is concave, chord below). Exact when both are constant.
/// the upper bound of x may rise past the horizon, its lower bound fall
inline bool hiRises(const AffItv& x)
{
    return x.b1 > 0 || x.hiDrifts;
}
inline bool loFalls(const AffItv& x)
{
    return x.a1 < 0 || x.loDrifts;
}

/// r, a constant corridor rebuilt from the hulls over [0, T] of values that hold it between
/// them (a mix, a smoothing) : a bound drifts where one of them moves past the horizon
inline AffItv hullDrift(AffItv r, std::initializer_list<AffItv> xs)
{
    for (const AffItv& x : xs) {
        r.loDrifts = r.loDrifts || loFalls(x);
        r.hiDrifts = r.hiDrifts || hiRises(x);
    }
    return r;
}

/// r, rebuilt as the intersection of two sound bounds a and b of one value : a bound drifts
/// only where both move past the horizon
inline AffItv meetDrift(AffItv r, const AffItv& a, const AffItv& b)
{
    r.loDrifts = r.loDrifts || (loFalls(a) && loFalls(b));
    r.hiDrifts = r.hiDrifts || (hiRises(a) && hiRises(b));
    return r;
}

/// r, a chord through the bounds of a result at 0 and T, with a bound that does not rise
/// drifting where all, the result on the values of its operands for all time, goes beyond
/// it : the chord bounds [0, T] only (a bound that rises leaves every value past T anyway)
inline AffItv chordDrift(AffItv r, const interval& all, double T)
{
    if (r.isEmpty() || all.isEmpty()) return r;
    if (r.a1 >= 0 && all.lo() < std::min(r.lo(0), r.lo(T))) r.loDrifts = true;
    if (r.b1 <= 0 && all.hi() > std::max(r.hi(0), r.hi(T))) r.hiDrifts = true;
    return r;
}

inline AffItv ajoin(const AffItv& x, const AffItv& y, double T)
{
    const bool invalid  = x.mayBeInvalid || y.mayBeInvalid;
    const bool overflow = x.mayOverflow || y.mayOverflow;
    if (x.isEmpty()) return adrift(y.withInvalid(invalid).withOverflow(overflow), x);
    if (y.isEmpty()) return adrift(x.withInvalid(invalid).withOverflow(overflow), y);
    AffItv r;
    achord(std::min(x.lo(0), y.lo(0)), std::min(x.lo(T), y.lo(T)), T, r.a0, r.a1);
    achord(std::max(x.hi(0), y.hi(0)), std::max(x.hi(T), y.hi(T)), T, r.b0, r.b1, true);
    r.lsb = std::min(x.lsb, y.lsb);
    r.mayBeInvalid = invalid;
    r.mayOverflow  = overflow;
    return chordDrift(adrift(adrift(r, x), y), reunion(forever(x, T), forever(y, T)), T).wrapDrift();
}

/// The numeric core of widening, in two stages: the first widening of a moving bound
/// PROPOSES a rate — the increment observed over one iteration round — which a genuine
/// affine accumulator then makes stationary; a bound still moving despite a proposed
/// rate is super-linear and escalates to the top of its world (int32 saturation for
/// integer chains, ±inf with a float lsb stamp otherwise). This is what makes the
/// domain information-preserving where interval widening is destructive: growth gets a
/// coefficient to live in instead of being discarded into infinity.
/// (A domain may run a certification stage before this one — e.g. a probe threshold.)
inline AffItv awiden(const AffItv& old, const AffItv& fresh, double T)
{
    const bool invalid  = old.mayBeInvalid || fresh.mayBeInvalid;
    const bool overflow = old.mayOverflow || fresh.mayOverflow;
    if (old.isEmpty() || fresh.isEmpty())
        return adrift(fresh.withInvalid(invalid).withOverflow(overflow), old);
    const bool wlo = fresh.lo(0) < old.lo(0) || fresh.lo(T) < old.lo(T);
    const bool whi = fresh.hi(0) > old.hi(0) || fresh.hi(T) > old.hi(T);
    if (!wlo && !whi) return adrift(fresh.withInvalid(invalid).withOverflow(overflow), old);

    AffItv r = adrift(fresh, old);
    r.mayBeInvalid = invalid;
    r.mayOverflow  = overflow;
    if (whi) {
        if (old.b1 == fresh.b1 && old.b1 == 0 && std::isfinite(fresh.b0 - old.b0)) {
            r.b1 = fresh.b0 - old.b0;  // propose the observed per-round rate
        } else {
            r.b0 = (fresh.lsb >= 0) ? 2147483647.0 : HUGE_VAL;  // escalate
            r.b1 = 0;
            if (fresh.lsb < 0) r.lsb = std::min(fresh.lsb, -24);
        }
    }
    if (wlo) {
        if (old.a1 == fresh.a1 && old.a1 == 0 && std::isfinite(fresh.a0 - old.a0)) {
            r.a1 = fresh.a0 - old.a0;
        } else {
            r.a0 = (fresh.lsb >= 0) ? -2147483648.0 : -HUGE_VAL;
            r.a1 = 0;
            if (fresh.lsb < 0) r.lsb = std::min(fresh.lsb, -24);
        }
    }
    return r;
}

}  // namespace itv
