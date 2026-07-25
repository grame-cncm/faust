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

#include "interval_def.hh"

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
 * Emptiness follows the interval convention: NaN intercepts.
 */

namespace itv {

struct AffItv {
    // The whole value is these five fields: two affine bounds and a precision.
    double a0 = NAN, a1 = 0;  ///< lo(t) = a0 + a1·t
    double b0 = NAN, b1 = 0;  ///< hi(t) = b0 + b1·t
    int    lsb = 0;           ///< precision, as in itv::interval

    bool   isEmpty() const { return std::isnan(a0) || std::isnan(b0); }
    bool   isConst() const { return a1 == 0 && b1 == 0; }
    double lo(double t) const { return a1 == 0 ? a0 : a0 + a1 * t; }
    double hi(double t) const { return b1 == 0 ? b0 : b0 + b1 * t; }
};

/// Bottom: no values yet. Neutral in every join.
inline AffItv aempty()
{
    return {};
}

/// Lift an ordinary interval: a horizontal corridor.
inline AffItv fromItv(const interval& x)
{
    if (x.isEmpty()) return aempty();
    return {x.lo(), 0, x.hi(), 0, x.lsb()};
}

/// Collapse to the ordinary interval hull over [0, T] — THE bridge from affine claims
/// to interval facts. An INTEGER chain's claim is only valid while its value fits
/// int32: past that date the real counter has wrapped and the form no longer bounds
/// it, so the collapse caps to the int32 range (constant forms included: an integer
/// interval beyond int32 describes no real int32 value). A float chain stays bounded
/// past absorption — the value freezes, the form keeps over-approximating it.
inline interval toItv(const AffItv& x, double T)
{
    if (x.isEmpty()) return empty();
    const double lo = std::min(x.lo(0), x.lo(T));
    const double hi = std::max(x.hi(0), x.hi(T));
    if (x.lsb >= 0 && (hi > 2147483647.0 || lo < -2147483648.0)) {
        return {-2147483648.0, 2147483647.0, x.lsb};
    }
    return {lo, hi, x.lsb};
}

/// x ⊑ y over [0, T]: affine bounds compare at the endpoints.
inline bool aleq(const AffItv& x, const AffItv& y, double T)
{
    if (x.isEmpty()) return true;
    if (y.isEmpty()) return false;
    return y.lo(0) <= x.lo(0) && y.lo(T) <= x.lo(T) && x.hi(0) <= y.hi(0) &&
           x.hi(T) <= y.hi(T);
}

/// Affine chord through two endpoint values; degenerates to a constant when possible.
inline void achord(double v0, double vT, double T, double& c0, double& c1)
{
    if (!std::isfinite(v0) || !std::isfinite(vT) || v0 == vT) {
        c0 = (v0 == vT) ? v0 : (std::isfinite(v0) ? vT : v0);
        if (!std::isfinite(v0)) c0 = v0;
        if (!std::isfinite(vT)) c0 = vT;
        c1 = 0;
        return;
    }
    c0 = v0;
    c1 = (vT - v0) / T;
}

/// Join (reunion) of two forms: endpoint hulls, chorded back to affine. Sound by
/// convexity — max of affine functions is convex, so its chord lies above it on
/// [0, T] (and min is concave, chord below). Exact when both are constant.
inline AffItv ajoin(const AffItv& x, const AffItv& y, double T)
{
    if (x.isEmpty()) return y;
    if (y.isEmpty()) return x;
    AffItv r;
    achord(std::min(x.lo(0), y.lo(0)), std::min(x.lo(T), y.lo(T)), T, r.a0, r.a1);
    achord(std::max(x.hi(0), y.hi(0)), std::max(x.hi(T), y.hi(T)), T, r.b0, r.b1);
    r.lsb = std::min(x.lsb, y.lsb);
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
    if (old.isEmpty() || fresh.isEmpty()) return fresh;
    const bool wlo = fresh.lo(0) < old.lo(0) || fresh.lo(T) < old.lo(T);
    const bool whi = fresh.hi(0) > old.hi(0) || fresh.hi(T) > old.hi(T);
    if (!wlo && !whi) return fresh;

    AffItv r = fresh;
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
