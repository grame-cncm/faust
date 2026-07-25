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

#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "interval.hh"   // itv::interval
#include "ppsig.hh"
#include "sighorizon.hh"  // HorizonReader: THE interval domain (affine), collapsed
#include "signals.hh"
#include "sigtyperules.hh"  // getSigType: restrict format sites to annotated signals

//----------------------------------------------------------------------------------------
// The roles report of THE interval domain (affine, sighorizon.cpp), measured on its
// real consumption sites: delay-line allocation, table-access proofs, fixed-point
// formats. Absolute statistics: since 2026-07-25 this domain IS the type system's,
// there is no other producer left to compare against.
//----------------------------------------------------------------------------------------

namespace {

using itv::interval;

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
            if (boundedItv(hz.at(n))) {
                st.delaySites++;
            } else {
                st.delayUnbounded++;
                if (verbose) {
                    std::cerr << "ROLES delay : amount unbounded : " << ppsig(n, 30)
                              << std::endl;
                }
            }
        }

        // --- correctness: table accesses provably inside [0, size) --------------------
        auto checkAccess = [&](Tree table, Tree index) {
            int  sz;
            Tree s1, s2, s3, s4;
            if (!isSigWRTbl(table, s1, s2, s3, s4)) return;
            if (!isSigInt(s1, &sz)) return;  // dynamic sizes: skip
            const interval m = hz.at(index);
            st.tableAccesses++;
            if (boundedItv(m) && m.lo() >= 0 && m.hi() < double(sz)) {
                st.tableSafe++;
            } else {
                st.tableUnproven++;
                if (verbose) {
                    std::cerr << "ROLES table : unproven " << m << " for size " << sz
                              << " : " << ppsig(index, 30) << std::endl;
                }
            }
        };
        if (isSigRDTbl(t, tbl, ri)) checkAccess(tbl, ri);
        if (isSigWRTbl(t, size, gen, wi, ws) && wi != ::nil()) checkAccess(t, wi);

        // --- quality: integer bits of the fixed-point format --------------------------
        // Only annotated signals: a walk also meets structure (list spines, labels).
        if (getSigType(t)) {
            const interval m = hz.at(t);
            if (boundedItv(m)) {
                st.formatSites++;
                st.formatBitsTotal += msbOf(m);
            }
        }

        for (int i = 0; i < t->arity(); i++) {
            work.push_back(t->branch(i));
        }
    }

    if (verbose) {
        std::cerr << "ROLES delay : bornés=" << st.delaySites
                  << " non-bornés=" << st.delayUnbounded << std::endl;
        std::cerr << "ROLES table : accès=" << st.tableAccesses
                  << " prouvés=" << st.tableSafe << " gardés=" << st.tableUnproven
                  << std::endl;
        std::cerr << "ROLES format : sites-bornés=" << st.formatSites
                  << " bits-entiers-totaux=" << st.formatBitsTotal << std::endl;
    }
    return st;
}
