/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

#include "signals.hh"

/// Late state-join reassociation : inside every single-definition recursive
/// group, the sum terms that depend on the state (contain the group's own
/// projection) are joined LAST -- the recurrence chain shrinks to one add
/// plus the term's own depth. Off-path terms stay a flat comb : measured,
/// both clang (-ffast-math) and the out-of-order hardware handle flat
/// reductions as well as balanced trees, and WITHOUT fast-math the join
/// placement is worth x4 (see exp-reassoc micro-benchmarks).
Tree reassociate(Tree lsig);
