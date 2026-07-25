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
        const char* h = getenv("FAUST_HORIZON_SAMPLES");
        return h ? std::atof(h) : 2147483648.0;  // default: 2^31 samples
    }

   public:
    /// defaultParams: parameters held at their DEFAULT values (nominal reading) instead
    /// of their full declared ranges (worst case). Buttons and checkboxes read released.
    explicit HorizonAlgebra(bool defaultParams = false)
        : itv::AffineOps<SignalAlgebra<AffItv>>(horizonFromEnv(), defaultParams)
    {
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
        if (getenv("FAUST_ITV_NOPROBE") != nullptr) return {};  // measurement A/B
        return {itv::fromItv(interval(0, kBig, 0)),
                itv::fromItv(interval(-kBig, kBig, 0))};
    }
    void recordProbe(Tree var, const AffItv& probed, bool certified) const override
    {
        fProbe[var] = {probed, certified};
        if (getenv("FAUST_ITV_TRACE") != nullptr && certified) {
            std::cerr << "PROBE CERTIFIED " << itv::toItv(probed, fT) << " : "
                      << ppsig(var, 30) << std::endl;
        }
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
    o << " @48kHz (" << std::scientific << s << " éch.)";
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
    const RecPlan& plan = getRecPlan(L);

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
