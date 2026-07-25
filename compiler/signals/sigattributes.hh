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
 * Since 2026-07-25 these ARE the type system : the shadow-comparison harness that
 * validated them against the old inference engine (corpus: 0 divergence on the five
 * exact attributes) was removed with the engine itself.
 */

/**
 * The five exact attributes of one root, solved once and queryable per signal.
 * Building block of the TypeSolver facade (sigtypesolver.hh); the concrete algebras
 * stay private to sigattributes.cpp, only the values cross this boundary.
 */
class SIGS_API ExactSolvers {
    struct Impl;
    Impl* fImpl;

   public:
    explicit ExactSolvers(Tree root);
    ~ExactSolvers();
    ExactSolvers(const ExactSolvers&)            = delete;
    ExactSolvers& operator=(const ExactSolvers&) = delete;

    int nature(Tree sig) const;
    int variability(Tree sig) const;
    int computability(Tree sig) const;
    int vectorability(Tree sig) const;
    int booleanity(Tree sig) const;
};
