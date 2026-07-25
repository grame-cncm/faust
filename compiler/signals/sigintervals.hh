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

#pragma once

#include "sigs-export.hh"
#include "tlib.hh"

/**
 * The two roles of the interval computation: CORRECTNESS -- the
 * program runs right: no div-by-zero, no NaN, no table overflow, no infinity, delay
 * lines allocated large enough -- and SOUND QUALITY -- the precision of the
 * computations: in fixed point, a signal's format takes its integer bits (msb) from
 * its RANGE, so a tighter interval converts directly into fractional bits, i.e. into
 * signal-to-noise ratio. This report measures THE interval domain (the affine one,
 * sighorizon.hh) on the concrete consumption sites of both roles.
 *
 * The shadow-comparison harness that validated the domain against the old type
 * system's intervals (classification: tighter / floorRefuted / wider...) was removed
 * with the old engine on 2026-07-25; see the journal for the final campaign numbers.
 */
struct IntervalRolesStats {
    // correctness: delay-line allocation (the hi bound of every delay amount)
    int delaySites     = 0;  ///< delay sites whose amount has provable finite bounds
    int delayUnbounded = 0;  ///< delay sites with no finite bound (compile error zone)
    // correctness: table accesses provably within [0, size)
    int tableAccesses = 0;
    int tableSafe     = 0;  ///< accesses proved in bounds (no clamp needed)
    int tableUnproven = 0;  ///< accesses that keep their guard
    // quality: integer bits of the fixed-point format (msb from the range)
    int       formatSites     = 0;  ///< signals with a finite range (a format exists)
    long long formatBitsTotal = 0;  ///< sum over sites of msb(range)
};

SIGS_API IntervalRolesStats intervalRolesReport(Tree L, bool verbose);
