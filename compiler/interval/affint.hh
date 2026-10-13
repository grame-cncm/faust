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

    // Public API: monotonically add invalidity without changing the corridor.
    AffItv withInvalid(bool possible = true) const
    {
        AffItv result = *this;
        result.mayBeInvalid = mayBeInvalid || possible;
        return result;
    }

    bool   isEmpty() const { return std::isnan(a0) || std::isnan(b0); }
    bool   isConst() const { return a1 == 0 && b1 == 0; }
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
    return {x.lo(), 0, x.hi(), 0, x.lsb(), x.mayBeInvalid()};
}

/// Collapse to the ordinary interval hull over [0, T] — THE bridge from affine claims
/// to interval facts. An INTEGER chain's claim is only valid while its value fits
/// int32: past that date the real counter has wrapped and the form no longer bounds
/// it, so the collapse caps to the int32 range (constant forms included: an integer
/// interval beyond int32 describes no real int32 value). A float chain stays bounded
/// past absorption — the value freezes, the form keeps over-approximating it.
inline interval toItv(const AffItv& x, double T)
{
    if (x.isEmpty()) return empty(x.lsb).withInvalid(x.mayBeInvalid);
    const double lo = std::min(x.lo(0), x.lo(T));
    const double hi = std::max(x.hi(0), x.hi(T));
    if (x.lsb >= 0 && (hi > 2147483647.0 || lo < -2147483648.0)) {
        return {-2147483648.0, 2147483647.0, x.lsb, x.mayBeInvalid};
    }
    return {lo, hi, x.lsb, x.mayBeInvalid};
}

/// Public API: prove x ⊑ y over [0,T], T>=0, by comparing exact affine lines at
/// both endpoints. In float/double mode an upward enclosure of each difference must
/// be nonpositive; comparing two separately rounded values could give a false proof.
/// An invalid execution in x also requires a corresponding alert in y.
inline bool aleq(const AffItv& x, const AffItv& y, double T)
{
    // An unchanged corridor with a new alert is a new abstract state.
    if (x.mayBeInvalid && !y.mayBeInvalid) return false;
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
inline AffItv ajoin(const AffItv& x, const AffItv& y, double T)
{
    const bool invalid = x.mayBeInvalid || y.mayBeInvalid;
    if (x.isEmpty()) return y.withInvalid(invalid);
    if (y.isEmpty()) return x.withInvalid(invalid);
    AffItv r;
    achord(std::min(x.lo(0), y.lo(0)), std::min(x.lo(T), y.lo(T)), T, r.a0, r.a1);
    achord(std::max(x.hi(0), y.hi(0)), std::max(x.hi(T), y.hi(T)), T, r.b0, r.b1, true);
    r.lsb = std::min(x.lsb, y.lsb);
    r.mayBeInvalid = invalid;
    return r;
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
    const bool invalid = old.mayBeInvalid || fresh.mayBeInvalid;
    if (old.isEmpty() || fresh.isEmpty()) return fresh.withInvalid(invalid);
    const bool wlo = fresh.lo(0) < old.lo(0) || fresh.lo(T) < old.lo(T);
    const bool whi = fresh.hi(0) > old.hi(0) || fresh.hi(T) > old.hi(T);
    if (!wlo && !whi) return fresh.withInvalid(invalid);

    AffItv r = fresh;
    r.mayBeInvalid = invalid;
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
