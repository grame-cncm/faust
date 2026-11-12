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

/**
 * Consumer-side view of a kernel read. For any sigFIR node, rebuilds the
 * WORKING coefficient vector [x, c0..cn] with the source's literal delay
 * re-spelled as leading zeros : FIR[x@d, C] -> [x, 0 x d, C]. Returns
 * false for non-kernel nodes. Every consumer (occurrences, dependency
 * graph, supernodes, emission, oracle, probes) reads kernels through
 * this one lens, so a site's spelling and its accounting always agree.
 */
bool kernelWorkVec(Tree t, tvec& V);
