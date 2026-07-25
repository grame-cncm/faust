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
 * The interval attribute computed by the generic fixpoint engine.
 *
 * Unlike the five exact attributes (sigattributes.hh), the interval is APPROXIMATE:
 * its lattice is unbounded, so the engine's widening / narrowing / probe machinery is
 * engaged. The transfer function is kept IDENTICAL to the current type system's (same
 * gAlgebra calls, same per-constructor rules), so that every measured difference is
 * attributable to the ITERATION STRATEGY -- per-SCC solving in topological order,
 * per-bound widening after a configurable number of rounds, bounded narrowing --
 * and not to diverging semantics.
 *
 * There is no exact oracle here: the shadow comparison CLASSIFIES instead of equating.
 * `tighter` is the goal; `wider` and `incomparable` demand investigation.
 */

/// Result of comparing the fixpoint interval against the type system's, per signal.
struct IntervalShadowStats {
    int equal      = 0;  ///< same bounds (or both unknown/empty)
    int tighter    = 0;  ///< strictly contained in the type system's (win)
    int fromTop    = 0;  ///< bounded where the type system had no information (win)
    int wider      = 0;  ///< strictly contains the type system's (loss: investigate)
    int toEmpty    = 0;  ///< empty where the type system had bounds (suspicious)
    int incomparable = 0;  ///< overlapping, neither contains the other (investigate)

    /// The disagreement is confined to the FLOOR: our low bound goes below the
    /// reference's while our ceiling does not exceed its. This is the signature of the
    /// signed-noise / plucked-string family, where the reference's [0,+inf) asserts a
    /// sign the signal does not have -- hand-verified on the idioms (LCG noise wraps
    /// and IS negative half the time; a string oscillates below zero; an int counter
    /// eventually wraps negative). Not a loss: there, the REFERENCE is the wrong one.
    int floorRefuted = 0;

    int total() const
    {
        return equal + tighter + fromTop + wider + toEmpty + incomparable + floorRefuted;
    }
};

/**
 * @brief Recompute the interval of every annotated signal of L by fixpoint and compare
 * it to the one inferSigType stored. L must have been through typeAnnotation() first.
 *
 * @param L the annotated list of output signals
 * @param verbose print a summary line, plus samples of the suspicious classes
 * @return the comparison statistics
 */
SIGS_API IntervalShadowStats shadowCheckInterval(Tree L, bool verbose);
