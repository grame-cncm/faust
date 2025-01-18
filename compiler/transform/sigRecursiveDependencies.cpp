/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2024 INRIA, Institut national de recherche en sciences
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
 * @file sigRecursiveDependencies.cpp
 * @author Yann Orlarey (yann.orlarey@inria.fr)
 * @brief Compute and check the recursive dependencies of a signal
 * @version 0.1
 * @date 2024-03-15
 *
 * @copyright Copyright (c) 2024 INRIA
 *
 ***********************************************************************/

#include "sigRecursiveDependencies.hh"

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "global.hh"
#include "ppsig.hh"
#include "signals.hh"

// Uncomment to activate type inferrence tracing
#if 0
#define TRACE(x) x
#else
#define TRACE(x) \
    {            \
        ;        \
    }
#endif

/**
 * @brief Compute the set of dependencies of a signal
 *
 * @param underVisit, stack of projections under visit (prevent infinite loops)
 * @param sig
 * @return std::set<Tree> set of dependencies of sig
 */
static std::set<Tree> sigDependencies(std::vector<Tree>& underVisit, Tree sig)
{
    int  i;
    Tree rec, id, le;
    if (gGlobal->gDependencies.count(sig)) {
        // 1) the dependencies of sig have already been computed
        return gGlobal->gDependencies[sig];
    } else if (isProj(sig, &i, rec)) {
        // 2) sig is a projection, its dependencies are itself and the dependecies of its definition
        std::set<Tree> deps;
        if (std::find(underVisit.begin(), underVisit.end(), sig) == underVisit.end()) {
            // we mark the projection under visit and compute the dependencies of its definition
            underVisit.push_back(sig);
            faustassert(isRec(rec, id, le));
            deps = sigDependencies(underVisit, nth(le, i));
            underVisit.pop_back();
        }
        deps.insert(sig);  // insert the projection itself
        gGlobal->gDependencies[sig] = deps;
        return deps;

    } else {
        // 3) sig is not a projection but is any other expression,
        // its dependencies are the dependencies of its branches
        std::set<Tree> deps;
        for (Tree b : sig->branches()) {
            std::set<Tree> depsb = sigDependencies(underVisit, b);
            deps.insert(depsb.begin(), depsb.end());
        }
        gGlobal->gDependencies[sig] = deps;
        return deps;
    }
}

/**
 * @brief compute the set of recursive dependencies of a signal
 *
 * @param sig
 * @return std::set<Tree>
 */
std::set<Tree> signalDependencies(Tree sig)
{
    std::vector<Tree> underVisit;
    return sigDependencies(underVisit, sig);
}

/**
 * @brief true if a projection is recursive (i.e. it has a definition that depends on itself), false
 * otherwise
 *
 * @param proj, a signal of type projection
 * @return true if the projection is recursive
 * @return false otherwise
 */
bool isSignalRecursive(Tree proj)
{
    std::set<Tree> deps   = signalDependencies(getProjDefinition(proj));
    bool           answer = deps.find(proj) != deps.end();
#if 0
    if (answer) {
        std::cerr << "\nSignal " << *proj << " is recursive. Its dependencies are: (";
        for (Tree d : deps) {
            std::cerr << *d << " ";
        }
        std::cerr << ")\n" << std::endl;
    } else {
        std::cerr << "\nSignal " << *proj << " is NOT recursive. Its dependencies are: (";
        for (Tree d : deps) {
            std::cerr << *d << " ";
        }
        std::cerr << ")\n" << std::endl;
    }
#endif
    return answer;
}

/**
 * @brief isDependingOn(sig, proj) returns true if sig depends on proj, false otherwise
 *
 * @param sig
 * @param proj
 * @return true
 * @return false
 */
bool isDependingOn(Tree sig, Tree proj)
{
    std::set<Tree> deps   = signalDependencies(sig);
    bool           answer = deps.find(proj) != deps.end();
    return answer;
}

/**
 * @brief Returns the definition associated with a projection
 *
 * @param a signal of type projection
 * @return the definition associated with the projection
 */
Tree getProjDefinition(Tree proj)
{
    int  i;
    Tree w, id, le;
    faustassert(isProj(proj, &i, w));
    faustassert(isRec(w, id, le));
    return nth(le, i);
}

/**
 * @brief Get the Proj Final Definition object
 *
 * @param proj
 * @return Tree
 */
Tree getProjFinalDefinition(Tree proj)
{
    int  i;
    Tree w;
    Tree def = getProjDefinition(proj);
    while (isProj(def, &i, w)) {
        def = getProjDefinition(def);
    }
    return def;
}

/**
 * @brief Print the dependecies of a signal (for debugging)
 *
 * @param msg a string prefix to the message
 * @param sig the signal we want to print the depedencies of
 */
void printDependencies(const std::string& msg, Tree sig)
{
    std::set<Tree> deps = signalDependencies(sig);
    std::cerr << msg << " dependencies of " << ppsig(sig, 20) << " are: (";
    for (Tree d : deps) {
        std::cerr << *d << " ";
    }
    std::cerr << ")\n" << std::endl;
}
