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

#include <utility>
#include <vector>

#include "sigs-export.hh"
#include "tlib.hh"

/**
 * Attributes of a signal computed by the generic fixpoint engine (tlib/fixpoint.hh),
 * as opposed to the ad-hoc fixpoint inside sigtyperules.cpp.
 *
 * The migration proceeds attribute by attribute, EXACT ones first (no approximation,
 * no widening, no probe), the interval last. Each new attribute is first run as a
 * SHADOW of the existing type inference and compared signal by signal: an exact
 * attribute must agree everywhere, so any divergence is a bug. That gives a
 * falsifiable checkpoint before reaching the interval, where a divergence will
 * legitimately mean "more precise" rather than "wrong".
 */

/**
 * @brief Recompute the five exact attributes of every annotated signal of L by fixpoint
 * and compare them to the ones inferSigType stored.
 *
 * The five are computed by five INDEPENDENT passes sharing one RecPlan, not by one pass
 * over a tuple: a tuple would couple their convergences, so a slow attribute would hold
 * back a fast one. They are genuinely independent -- no type rule crosses two attributes,
 * and none of the five depends on the interval.
 *
 * L must have been through typeAnnotation() first. Signals with no type, and nodes
 * carrying a non-simple type (a recursive group's tuplet), are skipped.
 *
 * @param L the annotated list of output signals
 * @param verbose print one line per divergence, and a summary per attribute
 * @return the total number of divergences (0 is the expected result)
 */
SIGS_API int shadowCheckNature(Tree L, bool verbose);
SIGS_API int shadowCheckExactAttributes(Tree L, bool verbose);

//----------------------------------------------------------------------------------------
// Shared by the shadow comparisons (exact attributes here, interval in sigintervals.cpp).
//----------------------------------------------------------------------------------------

class SimpleType;  // sigtype.hh

/// One comparable node: a signal and the SimpleType inferSigType stored on it.
using TypedNodes = std::vector<std::pair<Tree, SimpleType*>>;

/// Every annotated signal reachable from L that carries a SimpleType. Recursive groups
/// (tuplet type) and the syntax a walk also meets (opcode leaves, labels) are skipped.
SIGS_API TypedNodes collectTypedSignals(Tree L);

/**
 * @brief Time the NEW system's full equivalent of a typeAnnotation -- RecPlan, the five
 * exact-attribute passes, and the affine interval domain, each queried on every typed
 * signal -- and print it against the measured duration of the CURRENT system's pass.
 * Behind FAUST_TYPE_TIMING; currentMs is measured by the caller around the current
 * inference body.
 */
SIGS_API void typeTimingReport(Tree L, double currentMs);
