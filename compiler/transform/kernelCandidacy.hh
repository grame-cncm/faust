/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#pragma once

#include "tlib.hh"

/**
 * Kernel materialization candidacy. For every shifted kernel read
 * delay(DENSE(x, KFORM(C)), d) the emission has two spellings :
 *
 *  - TRAVERSAL : the reader inlines the shifted taps on the source's
 *    existing ring -- no entity for the kernel's own value ;
 *  - MATERIALIZATION : the kernel value is computed once, stored in a
 *    line, and the reader loads it at d.
 *
 * The decision is structural : a SELF read (the reader lives inside the
 * very recursive group the kernel's source projects from -- the plate's
 * stencil kernels re-read by their own grid recursion) traverses,
 * because materializing it turns the value into a loop-carried state
 * pair. Every other shifted read materializes : cross-group readers
 * (statespace : one state's kernel consumed by the other equations) and
 * non-recursive sources (the FFT windows, shared across shifted
 * readers) pay one computation and a line instead of one computation
 * per reader.
 *
 * The verdict is deposited as the KERNELINLINE property on the delay
 * node itself, BEFORE the occurrences, dependency-graph, supernode and
 * emission consumers run -- one decision, read by everyone (a site's
 * spelling and its accounting must never disagree). A node read from
 * both inside and outside its group keeps the traversal (the state
 * pair is the greater danger, measured x1.51 on the plate).
 */
void kernelCandidacy(Tree L);

/// true when the shifted read t = delay(DENSE(..), d) was judged a
/// traversal site by kernelCandidacy
bool isKernelInline(Tree t);
