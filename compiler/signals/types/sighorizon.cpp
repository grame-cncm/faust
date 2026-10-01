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

#include <complex>
#include <limits>

#include "sighorizon.hh"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "affine_ops.hh"  // the numeric core: AffItv, AffineOps (interval library)
#include "ppsig.hh"
#include "signalAlgebra.hh"
#include "sigs-state.hh"
#include "sigtyperules.hh"

//----------------------------------------------------------------------------------------
// The tree-aware layer of THE interval domain (design decision, 2026-07-25: the affine
// domain is the interval domain; the ordinary one survives inside it as the rate-0
// subdomain and as the oracle of the nonlinear operations).
//
// Everything numeric lives in the interval library (affint.hh, affine_ops.hh). This file
// adds only what needs trees: the FixPointDomain glue, the probe (Tree-keyed), the
// signal-only constructors, and the analyses (horizon dating, reader).
//----------------------------------------------------------------------------------------

namespace {

using itv::AffItv;
using itv::interval;

class HorizonAlgebra : public itv::AffineOps<SignalAlgebra<AffItv>> {
    static constexpr double kBig = 1073741824.0;  // 2^30

    /// Probe results, keyed by proj(b, var). Mutable: engine feedback, not denotation.
    mutable std::unordered_map<Tree, std::pair<AffItv, bool>> fProbe;

    static double horizonFromEnv()
    {
        return 2147483648.0;  // default: 2^31 samples
    }

    // ---- IIR : worst-peak-gain (simple port of fir18) --------------------------------
    // Gain = 1/min|A(e^jw)| sampled (H-infinity norm of the frequency
    // response of an all-poles). This is a HEURISTIC : the safe bound for
    // an arbitrary bounded input is the L1 norm of the impulse response,
    // always >= H-inf, and the grid can miss a very narrow resonance ;
    // the certified bound (WCPG, Volkova-Hilaire-Lauter) is the
    // documented upgrade. Variable coefficients : max of the gain over
    // the 2^nz corners of the box (not rigorous, pragmatic).
    static double iirWorstPeakGain(const std::vector<double>& a, int numPoints = 10000)
    {
        const double pi      = std::acos(-1.0);
        double       min_mag = std::numeric_limits<double>::max();
        for (int i = 0; i < numPoints; ++i) {
            double               omega = pi * i / (numPoints - 1);
            std::complex<double> ejw   = std::polar(1.0, -omega);
            std::complex<double> A     = 1.0;
            std::complex<double> ejw_pow = 1.0;
            for (double ak : a) {
                ejw_pow *= ejw;
                A -= ak * ejw_pow;  // y = X + sum ak*y@k  =>  A(z) = 1 - sum ak z^-k
            }
            min_mag = std::min(min_mag, std::abs(A));
        }
        return 1.0 / min_mag;
    }

   public:
    AffItv Iir(Tree sig, const std::vector<AffItv>& c) const override
    {
        // coefficient boxes (C1..Cn), corners for the variable ones
        std::vector<interval> box;
        int                   nz = 0;
        for (size_t k = 3; k < c.size(); k++) {
            interval ci = itv::toItv(c[k], fT);
            if (!ci.isValid() || !ci.isBounded()) {
                return top(sig);  // unbounded coefficient : no finite gain claim
            }
            box.push_back(ci);
            if (ci.hi() > ci.lo()) {
                nz++;
            }
        }
        if (nz > 12) {
            return top(sig);  // corner explosion guard
        }
        double gain = 0.0;
        int    combos = 1 << nz;
        for (int mask = 0; mask < combos; mask++) {
            std::vector<double> a;
            int                 bit = 0;
            for (const interval& ci : box) {
                if (ci.hi() > ci.lo()) {
                    a.push_back((mask & (1 << bit)) ? ci.hi() : ci.lo());
                    bit++;
                } else {
                    a.push_back(ci.lo());
                }
            }
            gain = std::max(gain, iirWorstPeakGain(a));
        }
        interval ix = itv::toItv(c[1], fT);
        if (!ix.isValid()) {
            return itv::aempty();
        }
        if (!std::isfinite(gain) || gain > 1e12 || !ix.isBounded()) {
            return top(sig);  // unstable filter, or unbounded input
        }
        const double m = gain * std::max(std::fabs(ix.lo()), std::fabs(ix.hi()));
        return itv::fromItv(interval(-m, m));
    }

    /// defaultParams: parameters held at their DEFAULT values (nominal reading) instead
    /// of their full declared ranges (worst case). Buttons and checkboxes read released.
    explicit HorizonAlgebra(bool defaultParams = false)
        : itv::AffineOps<SignalAlgebra<AffItv>>(horizonFromEnv(), defaultParams)
    {
    }

    //--- the fractional part ---------------------------------------------------------
    // x - floor(x) is the fractional part of x : interval arithmetic, which reads the
    // two operands as independent, gives [-1000, 1000] for x in [-500, 500], where the
    // value lies in [0, 1]. Closed at 1 : in floating point, x - floor(x) rounds to 1
    // for a tiny negative x (-1e-10 - (-1)). This is the shape of every phase of the
    // libraries (ma.frac, ma.decimal) : a recursion through it is bounded at once.
    static bool isFractionalPart(Tree sig)
    {
        int  op;
        Tree x, y;
        return isSigBinOp(sig, &op, x, y) && op == kSub && y->arity() == 1 &&
               y->branch(0) == x && sigs::g.gFloorPrim != nullptr &&
               getUserData(y) == static_cast<void*>(sigs::g.gFloorPrim);
    }

    //--- the interpolation ------------------------------------------------------------
    // a*X + b*Y with b = 1 - a and a in [0, 1] is an interpolation between X and Y : it
    // lies in the hull of their intervals. Interval arithmetic reads a and 1 - a as
    // independent and loses it ([-2, 2] for a crossfade of two signals in [-1, 1]) ;
    // a smoother y = (1-p)*x + p*y' loses it at every step of its recursion, and the
    // widening of the fixpoint ends at +-1e9. Two recognitions : b is the node 1 - a
    // (the normal form keeps it : si.smooth with a variable pole, si.smoo), or a and b
    // are two numbers >= 0 whose sum is at most 1 (a constant pole, 0.001 and 0.999) ;
    // a sum below 1 adds 0 to the hull. Like the rest of the interval analysis, the
    // rule reasons on reals : a floating point rounding may exceed the hull by an ulp.
    static bool isOne(Tree t)
    {
        int    i;
        double r;
        return (isSigInt(t, &i) && i == 1) || (isSigReal(t, &r) && r == 1.0);
    }
    static bool isOneMinus(Tree b, Tree a)
    {
        int  op;
        Tree u, v;
        return isSigBinOp(b, &op, u, v) && op == kSub && isOne(u) && v == a;
    }
    // the (coefficient, operand) readings of a product : both orders
    static int productReadings(Tree t, Tree coef[2], Tree val[2])
    {
        int  op;
        Tree u, v;
        if (!isSigBinOp(t, &op, u, v) || op != kMul) {
            return 0;
        }
        coef[0] = u;
        val[0]  = v;
        coef[1] = v;
        val[1]  = u;
        return 2;
    }
    bool interpolationHull(Tree sig, FixPointEvaluator<AffItv>& ev, interval& out,
                           bool* openRecursion = nullptr) const
    {
        int  op;
        Tree p, q;
        if (!isSigBinOp(sig, &op, p, q) || op != kAdd) {
            return false;
        }
        Tree ca[2], xa[2], cb[2], yb[2];
        int  na = productReadings(p, ca, xa);
        int  nb = productReadings(q, cb, yb);
        auto inUnit = [&](Tree a) {
            interval ia = itv::toItv(ev.eval(a), fT);
            return ia.isValid() && !ia.isEmpty() && ia.lo() >= 0 && ia.hi() <= 1;
        };
        for (int i = 0; i < na; i++) {
            for (int j = 0; j < nb; j++) {
                Tree   a = ca[i], b = cb[j];
                bool   convex = false, subconvex = false;
                double va, vb;
                if ((isOneMinus(b, a) && inUnit(a)) || (isOneMinus(a, b) && inUnit(b))) {
                    convex = true;
                } else if (isSigReal(a, &va) && isSigReal(b, &vb) && va >= 0 && vb >= 0 &&
                           va + vb <= 1 + 1e-12) {
                    // 0.001 is computed as 1 - 0.999 in double : the sum may exceed 1 by an ulp
                    convex    = (std::fabs(va + vb - 1) <= 1e-12);
                    subconvex = !convex;
                }
                if (!convex && !subconvex) {
                    continue;
                }
                interval ix = itv::toItv(ev.eval(xa[i]), fT);
                interval iy = itv::toItv(ev.eval(yb[j]), fT);
                bool     ex = !ix.isValid() || ix.isEmpty(), ey = !iy.isValid() || iy.isEmpty();
                if (ex && ey) {
                    return false;
                }
                double lo = ex ? iy.lo() : (ey ? ix.lo() : std::min(ix.lo(), iy.lo()));
                double hi = ex ? iy.hi() : (ey ? ix.hi() : std::max(ix.hi(), iy.hi()));
                if (subconvex) {
                    lo = std::min(lo, 0.0);
                    hi = std::max(hi, 0.0);
                }
                if (!std::isfinite(lo) || !std::isfinite(hi)) {
                    return false;
                }
                out = interval(lo, hi);
                if (openRecursion) {
                    *openRecursion = !xa[i]->isRecFree() || !yb[j]->isRecFree();
                }
                return true;
            }
        }
        return false;
    }

   public:
    AffItv combine(Tree sig, const std::vector<AffItv>& c, FixPointEvaluator<AffItv>& ev) const override
    {
        AffItv r = itv::AffineOps<SignalAlgebra<AffItv>>::combine(sig, c, ev);
        if (r.isEmpty()) {
            // a recursion's first round : the generic sum is still empty, the hull is
            // already known from the other operand -- starting from it lets the fixpoint
            // settle at once instead of creeping up at the pole's rate into the widening
            interval h;
            return interpolationHull(sig, ev, h) ? itv::fromItv(h) : r;
        }
        if (isFractionalPart(sig)) {
            interval ri = itv::toItv(r, fT);
            double   lo = std::max(0.0, ri.lo());
            double   hi = std::min(1.0, ri.hi());
            return (lo <= hi) ? itv::fromItv(interval(lo, hi, ri.lsb())) : r;
        }
        interval h;
        bool     open = false;
        if (interpolationHull(sig, ev, h, &open)) {
            if (open) {
                // inside a recursion (a smoother's state) : the hull alone. Intersected
                // with the generic sum, the iterates would creep up at the pole's rate
                // (0.001 per round for a pole of 0.999) until the widening blows them up
                return itv::fromItv(h);
            }
            interval ri = itv::toItv(r, fT);
            double   lo = std::max(h.lo(), ri.lo());
            double   hi = std::min(h.hi(), ri.hi());
            return (lo <= hi) ? itv::fromItv(interval(lo, hi, ri.lsb())) : r;
        }
        return r;
    }

    //--- the lattice ------------------------------------------------------------------
    AffItv bottom(Tree) const override { return itv::aempty(); }
    AffItv top(Tree) const override { return itv::fromItv(interval(-HUGE_VAL, HUGE_VAL)); }
    bool   lessEqual(const AffItv& x, const AffItv& y) const override
    {
        return itv::aleq(x, y, fT);
    }
    bool converged(const AffItv& prev, const AffItv& cur) const override
    {
        return itv::aleq(cur, prev, fT);  // stationary OR descending stops
    }
    AffItv project(Tree, int i, const std::vector<AffItv>& row) const override
    {
        return row[i];  // the interval is a value attribute
    }

    int widenAfter() const override { return 8; }
    int maxNarrowingIterations() const override { return 3; }
    int maxIterations() const override { return 1000; }

    //--- probe: positivity seed first, then the symmetric fallback ---------------------
    std::vector<AffItv> probeSeeds(Tree) const override
    {
        return {itv::fromItv(interval(0, kBig, 0)),
                itv::fromItv(interval(-kBig, kBig, 0))};
    }
    void recordProbe(Tree var, const AffItv& probed, bool certified) const override
    {
        fProbe[var] = {probed, certified};
    }

    // Widening: a certified rate-0 probe threshold absorbs the move; otherwise the
    // numeric two-stage awiden (rate proposal, then escalation to the world's top).
    AffItv widen(Tree var, const AffItv& old, const AffItv& fresh) const override
    {
        if (old.isEmpty() || fresh.isEmpty()) return fresh;
        const bool wlo = fresh.lo(0) < old.lo(0) || fresh.lo(fT) < old.lo(fT);
        const bool whi = fresh.hi(0) > old.hi(0) || fresh.hi(fT) > old.hi(fT);
        if (!wlo && !whi) return fresh;

        auto it = fProbe.find(var);
        if (it != fProbe.end() && it->second.second && fresh.isConst() && old.isConst()) {
            const AffItv&  p = it->second.first;
            const interval f = itv::toItv(fresh, fT);
            if (!p.isEmpty() && p.isConst() && p.a0 <= f.lo() && f.hi() <= p.b0) {
                AffItv r = fresh;
                if (wlo) r.a0 = p.a0;
                if (whi) r.b0 = p.b0;
                r.lsb = std::min(fresh.lsb, p.lsb);
                return r;
            }
        }
        return itv::awiden(old, fresh, fT);
    }

    //--- signal-language-only constructors --------------------------------------------
    AffItv Table(const AffItv&, const AffItv& content) const override { return content; }
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
    o << " @48kHz (" << std::scientific << s << " samples)";
    return o.str();
}

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
                    std::cerr << "HORIZON " << tag << " : rate " << e.rate << "/sample";
                    if (e.wrapAt != INF) std::cerr << ", int32 wrap at " << fmtSamples(e.wrapAt);
                    if (e.absorb32At != INF) {
                        std::cerr << ", float absorption at " << fmtSamples(e.absorb32At)
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
    const RecPlan& plan = getRecPlan(L);

    // Worst case: parameters anywhere in their declared ranges.
    HorizonAlgebra worst(/*defaultParams*/ false);
    auto [wev, wt] = datePass(plan, worst, verbose, "pire-cas");

    // Nominal: parameters at their default values, buttons released.
    HorizonAlgebra nominal(/*defaultParams*/ true);
    auto [nev, nt] = datePass(plan, nominal, verbose, "defaults ");

    HorizonReport report;
    report.events                = std::move(wev);
    report.horizonSamples        = wt;
    report.horizonDefaultSamples = nt;
    report.defaultEventCount     = int(nev.size());

    if (verbose) {
        auto line = [](const char* tag, double t, std::size_t n) {
            std::cerr << "HORIZON T* " << tag << " : ";
            if (n == 0) {
                std::cerr << "no dated accumulator (exact semantics, no limit)";
            } else {
                std::cerr << fmtSamples(t) << " (" << n << " dated accumulator(s))";
            }
            std::cerr << std::endl;
        };
        line("(pire-cas)", wt, report.events.size());
        line("(defaults) ", nt, std::size_t(report.defaultEventCount));
    }
    return report;
}

//----------------------------------------------------------------------------------------
// HorizonReader: the horizon-bounded interval of any signal, for the shadow and roles
// reports. toItv caps integer chains at the int32 range past their wrap date.
//----------------------------------------------------------------------------------------

struct HorizonReader::Impl {
    const RecPlan&           plan;  ///< shared, memoized (getRecPlan)
    HorizonAlgebra           algebra;
    FixPointIterator<AffItv> it;

    explicit Impl(Tree L)
        : plan(getRecPlan(L)), algebra(/*defaultParams*/ false), it(plan, algebra)
    {
    }
};

HorizonReader::HorizonReader(Tree L) : fImpl(new Impl(L)) {}

HorizonReader::~HorizonReader()
{
    delete fImpl;
}

itv::interval HorizonReader::at(Tree sig) const
{
    return itv::toItv(fImpl->it.value(sig), fImpl->algebra.horizon());
}
