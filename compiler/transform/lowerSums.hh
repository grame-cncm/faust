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

#include <set>

#include "signals.hh"

/// Co-occurrence lowering of the n-ary Sum nodes into binary adds.
///
/// A flat Sum is canonical CONTENT but destroys structural sharing : two
/// sums with many common terms are distinct nodes sharing nothing, where
/// the binary form shared their common partial sums as real nodes (an FDN
/// matrix loses its butterfly : fdnRev emits 3.7x more additions). The
/// association is FORM, and it is inherently global -- the right binary
/// shape of one sum depends on every other sum of the program.
///
/// The heuristic ({x:2, y:2, z:1} -> (x+y)+z) : count the unordered pairs
/// of terms across ALL sums, let every sum greedily merge its globally
/// most frequent pair while one occurs at least twice, then fold the rest
/// as a canonically-sorted left comb. Two sums that share terms make the
/// same choices in the same order, build the same subtrees, and
/// hash-consing shares them without any explicit coordination.
///
/// A Sum node in `keep` is left N-ARY (neither mutated nor lowered) :
/// the matrix-row regime (spec LA-FORME-MATRICE) consumes whole rows at
/// emission, so the lowering must not shred them.
Tree lowerSums(Tree L, const std::set<Tree>* keep = nullptr);
