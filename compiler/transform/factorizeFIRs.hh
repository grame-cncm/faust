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

/// Intra-kernel FIR factorization (the first floor of "optimal FIR
/// sharing") : a kernel whose non-zero coefficients are all EQUAL loses
/// its gain -- FIR[x, c,c,0,c] becomes c * FIR[x, 1,1,0,1]. This both
/// removes redundant multiplications and NORMALIZES the all-ones kernels,
/// which unlocks their sliding-sum emission (see generateFIR : an
/// all-ones contiguous FIR is a moving sum, computable in O(1) whatever
/// its length). The content stays a FIR -- typed tightly by the
/// compositional expansion -- and the emission chooses the form.
Tree factorizeFIRs(Tree L);

/**
 * Consumer-side view of a kernel read. For any sigFIR node, rebuilds the
 * WORKING coefficient vector [x, c0..cn] with the source's literal delay
 * re-spelled as leading zeros : FIR[x@d, C] -> [x, 0 x d, C]. Returns
 * false for non-kernel nodes. Every consumer (occurrences, dependency
 * graph, supernodes, emission, oracle, probes) reads kernels through
 * this one lens, so a site's spelling and its accounting always agree.
 */
bool kernelWorkVec(Tree t, tvec& V);
