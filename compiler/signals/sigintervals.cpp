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

#include "sigintervals.hh"

#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "interval.hh"       // itv::interval
#include "ppsig.hh"
#include "sigattributes.hh"  // collectTypedSignals
#include "sighorizon.hh"     // HorizonReader: THE interval domain (affine), collapsed
#include "sigtype.hh"
#include "sigtyperules.hh"

//----------------------------------------------------------------------------------------
// Shadow comparison and roles report of THE interval domain.
//
// Since the design decision of 2026-07-25 there is a single interval domain, the
// affine-in-time one (interval library: affint.hh / affine_ops.hh; tree layer:
// sighorizon.cpp). This file only READS it, through HorizonReader -- the affine forms
// collapsed to ordinary intervals over [0, T] -- and compares it to what the current
// type system stored:
//   - shadowCheckInterval classifies per signal (equal / tighter / floorRefuted /
//     wider / incomparable / empty) -- there is no exact oracle for an approximate
//     attribute, so classification replaces equality;
//   - intervalRolesReport measures the two roles (Yann): CORRECTNESS on its real
//     consumption sites (delay-line allocation, table accesses provably in bounds) and
//     SOUND QUALITY (the integer bits of a fixed-point format, msb from the range).
//----------------------------------------------------------------------------------------

namespace {

using itv::interval;

/// x ⊑ y with the empty (NaN) conventions made explicit.
bool leq(const interval& x, const interval& y)
{
    if (x.isEmpty()) return true;
    if (y.isEmpty()) return false;
    return (y.lo() <= x.lo()) && (x.hi() <= y.hi());
}

/// Under FAUST_ITV_EXPLAIN, dump the operand intervals (ours vs the reference's) of a
/// diverging binop: divergences on comparisons are usually CASCADES from an operand
/// classified elsewhere, and this shows which operand and by how much.
void explainBinOp(const HorizonReader& hz, Tree sig)
{
    if (getenv("FAUST_ITV_EXPLAIN") == nullptr) return;
    int  op;
    Tree x, y;
    if (!isSigBinOp(sig, &op, x, y)) return;
    for (Tree operand : {x, y}) {
        AudioType*  ty = getSigType(operand);
        SimpleType* st = ty ? isSimpleType(ty) : nullptr;
        std::cerr << "    operand " << hz.at(operand) << " vs ref "
                  << (st ? st->getInterval() : itv::interval()) << " : " << ppsig(operand, 25)
                  << std::endl;
    }
}

}  // namespace

IntervalShadowStats shadowCheckInterval(Tree L, bool verbose)
{
    HorizonReader hz(L);

    IntervalShadowStats stats;
    const TypedNodes    nodes = collectTypedSignals(L);

    int shownWider = 0, shownIncomp = 0, shownEmpty = 0;
    for (const auto& n : nodes) {
        const interval mine = hz.at(n.first);
        const interval ref  = n.second->getInterval();

        const bool mEmpty = mine.isEmpty();
        const bool rEmpty = ref.isEmpty();

        if (mEmpty && rEmpty) {
            stats.equal++;
        } else if (mEmpty) {
            stats.toEmpty++;
            if (verbose && shownEmpty++ < 5) {
                std::cerr << "ITV EMPTY   : ref " << ref << " : " << ppsig(n.first, 40)
                          << std::endl;
            }
        } else if (rEmpty) {
            stats.fromTop++;  // bounded where the current system had no information
        } else if (mine.lo() == ref.lo() && mine.hi() == ref.hi()) {
            stats.equal++;
        } else if (leq(mine, ref)) {
            stats.tighter++;
        } else if (mine.lo() < ref.lo() && mine.hi() <= ref.hi()) {
            // floor-only disagreement: the reference asserts a floor we refute
            stats.floorRefuted++;
        } else if (leq(ref, mine)) {
            stats.wider++;
            if (verbose && shownWider++ < 5) {
                std::cerr << "ITV WIDER   : " << mine << " vs ref " << ref << " : "
                          << ppsig(n.first, 40) << std::endl;
                explainBinOp(hz, n.first);
            }
        } else {
            stats.incomparable++;
            if (verbose && shownIncomp++ < 5) {
                std::cerr << "ITV INCOMP  : " << mine << " vs ref " << ref << " : "
                          << ppsig(n.first, 40) << std::endl;
                explainBinOp(hz, n.first);
            }
        }
    }

    if (verbose) {
        std::cerr << "ITV SHADOW : " << stats.total() << " signals, eq=" << stats.equal
                  << " tighter=" << stats.tighter << " fromTop=" << stats.fromTop
                  << " floorRefuted=" << stats.floorRefuted << " wider=" << stats.wider
                  << " toEmpty=" << stats.toEmpty << " incomp=" << stats.incomparable
                  << std::endl;
    }
    return stats;
}

//----------------------------------------------------------------------------------------
// The two roles, measured on their consumption sites.
//----------------------------------------------------------------------------------------

namespace {

/// Integer bits needed to represent the range (the msb of a fixed-point format),
/// capped at 64: beyond that a fixed-point format is fiction anyway, and the cap keeps
/// one pathological bound from dominating a corpus-wide sum.
int msbOf(const interval& x)
{
    const double m = std::max(std::fabs(x.lo()), std::fabs(x.hi()));
    if (m < 1) return 0;
    return std::min(64, int(std::ceil(std::log2(m + 1))));
}

bool boundedItv(const interval& x)
{
    return !x.isEmpty() && std::isfinite(x.lo()) && std::isfinite(x.hi());
}

}  // namespace

IntervalRolesStats intervalRolesReport(Tree L, bool verbose)
{
    HorizonReader hz(L);

    IntervalRolesStats       st;
    std::unordered_set<Tree> visited;
    std::vector<Tree>        work{L};

    auto refItv = [](Tree t) -> interval {
        AudioType*  ty = getSigType(t);
        SimpleType* s  = ty ? isSimpleType(ty) : nullptr;
        return s ? s->getInterval() : itv::interval();
    };

    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!visited.insert(t).second) continue;

        Tree var, body;
        if (isRec(t, var, body)) {
            if (body) work.push_back(body);
            continue;
        }

        Tree x, n, tbl, ri, size, gen, wi, ws;

        // --- correctness: delay-line allocation, driven by the amount's hi ------------
        if (isSigDelay(t, x, n)) {
            const interval r  = refItv(n);
            const interval m  = hz.at(n);
            const bool     rb = boundedItv(r), mb = boundedItv(m);
            if (rb || mb) st.delaySites++;
            if (mb && !rb) {
                st.delayOnlyUs++;
            } else if (rb && !mb) {
                st.delayOnlyRef++;
                if (verbose) {
                    std::cerr << "ROLES delay : réf bornée " << r << ", nous non : "
                              << ppsig(n, 30) << std::endl;
                }
            } else if (rb && mb) {
                if (m.hi() < r.hi()) {
                    st.delayTighter++;
                } else if (m.hi() == r.hi()) {
                    st.delayEqual++;
                } else {
                    st.delayWider++;
                    if (verbose) {
                        std::cerr << "ROLES delay : nous " << m.hi() << " vs réf " << r.hi()
                                  << " : " << ppsig(n, 30) << std::endl;
                    }
                }
            }
        }

        // --- correctness: table accesses provably inside [0, size) --------------------
        auto checkAccess = [&](Tree table, Tree index) {
            int  sz;
            Tree s1, s2, s3, s4;
            if (!isSigWRTbl(table, s1, s2, s3, s4)) return;
            if (!isSigInt(s1, &sz)) return;  // dynamic sizes: skip
            const interval r  = refItv(index);
            const interval m  = hz.at(index);
            const auto     ok = [&](const interval& i) {
                return boundedItv(i) && i.lo() >= 0 && i.hi() < double(sz);
            };
            st.tableAccesses++;
            if (ok(m)) st.tableSafeHorizon++;  // single domain: same reading
            const bool ro = ok(r), mo = ok(m);
            if (ro && mo) {
                st.tableSafeBoth++;
            } else if (mo) {
                st.tableSafeUsOnly++;
            } else if (ro) {
                st.tableSafeRefOnly++;
                if (verbose) {
                    std::cerr << "ROLES table : réf prouve " << r << ", nous " << m << " : "
                              << ppsig(index, 30) << std::endl;
                }
            } else {
                st.tableSafeNone++;
            }
        };
        if (isSigRDTbl(t, tbl, ri)) checkAccess(tbl, ri);
        if (isSigWRTbl(t, size, gen, wi, ws) && wi != ::nil()) checkAccess(t, wi);

        // --- quality: integer bits of the fixed-point format --------------------------
        // Only signals the current system typed with a SimpleType: the same comparison
        // set as the shadow, free of walk artifacts (opcode leaves, list spines).
        {
            AudioType*  ty = getSigType(t);
            SimpleType* sy = ty ? isSimpleType(ty) : nullptr;
            if (sy != nullptr) {
                const interval r  = sy->getInterval();
                const interval m  = hz.at(t);
                const bool     rb = boundedItv(r), mb = boundedItv(m);
                if (rb && mb) {
                    st.formatSites++;
                    st.formatBitsSaved += msbOf(r) - msbOf(m);
                    st.formatSitesHorizon++;
                    st.formatBitsSavedHorizon += msbOf(r) - msbOf(m);
                } else if (mb) {
                    st.formatOnlyUs++;
                    st.formatOnlyHorizon++;
                } else if (rb) {
                    st.formatOnlyRef++;
                    if (verbose && st.formatOnlyRef <= 3) {
                        std::cerr << "ROLES format : réf bornée " << r << ", nous " << m
                                  << " : " << ppsig(t, 30) << std::endl;
                    }
                }
            }
        }

        for (int i = 0; i < t->arity(); i++) {
            work.push_back(t->branch(i));
        }
    }

    if (verbose) {
        std::cerr << "ROLES delay : sites=" << st.delaySites << " serrés=" << st.delayTighter
                  << " égaux=" << st.delayEqual << " larges=" << st.delayWider
                  << " bornés-par-nous-seuls=" << st.delayOnlyUs
                  << " par-réf-seule=" << st.delayOnlyRef << std::endl;
        std::cerr << "ROLES table : accès=" << st.tableAccesses
                  << " prouvés-les-deux=" << st.tableSafeBoth
                  << " nous-seuls=" << st.tableSafeUsOnly
                  << " réf-seule=" << st.tableSafeRefOnly << " aucun=" << st.tableSafeNone
                  << std::endl;
        std::cerr << "ROLES format : sites=" << st.formatSites
                  << " bits-gagnés=" << st.formatBitsSaved
                  << " bornés-par-nous-seuls=" << st.formatOnlyUs
                  << " par-réf-seule=" << st.formatOnlyRef << std::endl;
    }
    return st;
}
