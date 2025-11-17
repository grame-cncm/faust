/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef __SIGDEGENERATERECURSIONELIMINATION__
#define __SIGDEGENERATERECURSIONELIMINATION__

#include <set>
#include "sigDependenciesGraph.hh"
#include "sigTransform.hh"

//-------------------------Degenerate Recursion Elimination-------------------------------
// Eliminates degenerate recursive projections by replacing them with their definitions.
// A degenerate recursion is a strongly connected component that:
// - Contains only one recursive projection
// - Has no connections (not connected to itself)
//----------------------------------------------------------------------

// Public API
Tree eliminateDegenerateRecursions(Tree sig, bool trace = false);
Tree inlineDegenerateRecursions(Tree siglist, bool trace);

#endif