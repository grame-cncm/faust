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
 * Kernel materialization candidacy, as the RETIMING LAW applied per
 * site. A shifted kernel FIR[x@d, C] has two spellings :
 *
 *   FIR[x@d, C]              the reader inlines the shifted taps on the
 *                            source's line (one line, no store, no new
 *                            entity) -- the CANONICAL spelling ;
 *   delay(FIR[x, C], d)      the kernel value is computed once, stored
 *                            in its own line, and read delayed -- legal
 *                            for CONSTANT C only (time invariance).
 *
 * The right spelling pays on shared computation (k shifted readers :
 * one evaluation instead of k) and on large shifts (one deep access
 * instead of N+1, and x's line stays in the short window class). This
 * pass rewrites, per site, the constant-class shifted kernels that are
 * NOT self reads (a site living inside the very group its source
 * projects from stays inline : materializing it would carry state
 * across the loop -- the plate's stencils, x1.51 measured). Both
 * results are ordinary signal trees ; downstream consumers need no
 * special knowledge.
 */
Tree kernelCandidacy(Tree L);

/**
 * A kernel whose taps are all 0, +1 or -1 has no coefficient : it is a sum
 * of delayed reads of its source, spelled as a kernel only because every
 * constant delay goes through the FIR form on its way to the folding rules.
 * As a kernel it is closed to the dispatch of the sums : a bank of such
 * kernels on ONE source is a {-1,0,+1} matrix over the atoms x@d (eight
 * delayed copies of an input through a Hadamard matrix : 56 additions, one
 * row at a time, where the butterfly needs 24), and its larger members are
 * emitted as a loop over a table of +-1 coefficients, one multiplication
 * per tap. This pass gives them back to the sums : FIR[x, c..] becomes
 * Sum[+-x@i], spliced into its reader when the reader is a sum and the only
 * one. The all-ones contiguous kernels of four taps and more stay kernels
 * (moving sums, O(1)). To be run BEFORE kernelCandidacy : what is not a
 * kernel is not retimed (a bank whose members share their shift would each
 * get a delay line for nothing). Without lowerSums the sums stay n-ary and
 * only the multiplications by +-1 go ; with it the bank is dispatched.
 */
Tree dissolveUnitKernels(Tree L);

