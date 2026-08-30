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
#include "sigtype.hh"
#include "tlib.hh"

/**
 * The FACADE of the new type system: SimpleTypes assembled from the fixpoint domains.
 *
 * One solving session per root tree, memoized like getRecPlan. Two accesses: the
 * type of a signal, and the i-th type of a recursive group -- the second
 * being sugar for the first, since proj(i, X) is itself a signal whose evaluation
 * routes through each domain's project() hook (the promotions the old inferProjType
 * used to perform). The old system typed the GROUP node and therefore needed a
 * TupletType, derefRecCert, inferProjType, TREC/TRECMAX; the new one solves the group
 * and never types it, so none of that machinery exists here.
 *
 * STRICTNESS AT THE BOUNDARY: the signal domain contains no lists, no nil, no labels
 * -- those are structure. The signature system makes membership an O(1) test (two
 * field reads), and type() raises an error on any tree outside the signal domain,
 * including a bare rec node: a group is solved, not typed.
 */
class SIGS_API TypeSolver {
    struct Impl;
    Impl* fImpl;

   public:
    explicit TypeSolver(Tree root);
    ~TypeSolver();
    TypeSolver(const TypeSolver&)            = delete;
    TypeSolver& operator=(const TypeSolver&) = delete;

    /// The type of a signal (memoized). Errors on a tree outside the signal domain.
    Type type(Tree sig);

    /// Signal-domain membership, O(1) (the boundary test type() enforces) : true for
    /// numeric leaves, xtended applications, projections and Signal-signature
    /// constructors ; false for structure (lists, nil, labels, bare rec nodes).
    bool isSignal(Tree t) const;

    /// The i-th type of a recursive group: type(proj(i, X)). Errors if X is not a
    /// recursive node.
    Type recType(Tree X, int i);
};

/// Memoized access: one solving session per root per session (cleared by sigs::init).
SIGS_API TypeSolver& getTypeSolver(Tree root);
SIGS_API void        typeSolverReset();
