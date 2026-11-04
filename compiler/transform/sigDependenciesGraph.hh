/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2024-2026 GRAME, Centre National de Creation Musicale
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
#include "DirectedGraph.hh"
#include "DirectedGraphAlgorythm.hh"
#include "signalVisitor.hh"

/**
 * @brief Compute the immediate Graph of a list of signals
 *
 * @param L list of signals
 * @return digraph<Tree>
 */
digraph<Tree> immediateGraph(Tree L);

/**
 * @brief Compute the full Graph of a list of signals
 *
 * @param L list of signals
 * @return digraph<Tree>
 */
digraph<Tree> fullGraph(Tree L);

/**
 * @brief Compute in which order the list of signals L should be compiled
 *
 * @param L a list of signals
 * @return std::vector<Tree> The first element of the vector is the first signal to compile
 */
std::vector<Tree> compilationOrder(Tree L);
