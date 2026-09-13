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
