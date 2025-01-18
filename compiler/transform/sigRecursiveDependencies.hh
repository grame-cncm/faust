/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2024 INRIA: Institut national de recherche en sciences
                              et technologies du numérique
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

/************************************************************************
 * @file sigRecursiveDependencies.hh
 * @author Yann Orlarey (yann.orlarey@inria.fr)
 * @brief Compute and check the recursive dependencies of a signal
 * @version 0.1
 * @date 2024-03-15
 *
 * @copyright Copyright (c) 2024 INRIA
 *
 ***********************************************************************/

#pragma once

#include <set>
#include "signals.hh"

/**
 * @brief compute the set of dependencies of a signal
 *
 * @param sig
 * @return std::set<Tree>
 */
std::set<Tree> signalDependencies(Tree sig);

/**
 * @brief true if signal is a recursive projection that depends on itself, false otherwise
 *
 * @param proj
 * @return true
 * @return false
 */
bool isSignalRecursive(Tree proj);

/**
 * @brief true if sig depends on dep, false otherwise
 *
 * @param sig
 * @param dep
 * @return true
 * @return false
 */
bool isDependingOn(Tree sig, Tree dep);

/**
 * @brief get the definition of a projection
 *
 * @param proj
 * @return its definition
 */
Tree getProjDefinition(Tree proj);

/**
 * @brief iterate to reach the final definition of a projection
 *
 * @param proj
 * @return its final definition
 */
Tree getProjFinalDefinition(Tree proj);

/**
 * @brief print the dependencies of a signal
 *
 * @param msg
 * @param sig
 */
void printDependencies(const std::string& msg, Tree sig);
