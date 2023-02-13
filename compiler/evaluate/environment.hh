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

#ifndef ENVIRONMENT_HH
#define ENVIRONMENT_HH

#include "tlib.hh"

/**
 * Push a new layer and add a single definition.
 * @param id the symbol id to be defined
 * @param def the definition to be binded to the symbol id
 * @param lenv the environment where to push the layer and add the definition
 * @return the new environment
 */
Tree pushValueDef(Tree id, Tree def, Tree lenv);

/**
 * Search the environment (until first barrier) for
 * the definition of a symbol ID and return it. Used by the
 * pattern matcher.
 * @param id the symbol ID to search
 * @param def where to store the definition if any
 * @param lenv the environment
 * @return true if a definition was found
 */
bool searchIdDef(Tree id, Tree& def, Tree lenv);

/**
 * Push a new layer with multiple definitions creating the appropriate closures
 * @param ldefs list of pairs (symbol id x definition) to be binded to the symbol id
 * @param visited set of visited symbols (used for recursive definition detection)
 * @param lenv the environment where to push the layer and add all the definitions
 * @return the new environment
 */
Tree pushMultiClosureDefs(Tree ldefs, Tree visited, Tree lenv);

/**
 * Create a new environment by copying an existing one and replacing some definitions
 * @param xenv existing environment we will copy
 * @param ldefs list of pairs (symbol id x definition) that will replace old definitions
 * @param visited set of visited symbols (used for recursive definition detection)
 * @param lenv the current environment to evaluate the definitions
 * @return the new environment
 */
Tree copyEnvReplaceDefs(Tree anEnv, Tree ldefs, Tree visited, Tree curEnv);

/**
 * Test if the environment is a barrier (or nil) so
 * that searchIdDef will know where to stop when searching
 * an environment.
 * @param lenv the environment to test
 * @return true is barrier reached
 */
bool isEnvBarrier(Tree t);

/**
 * Push a new environment barrier on top of an existing environment so
 * that searchIdDef (used by the pattern matcher) will not look after
 * the barrier. This barrier will not any influence on regular environment
 * lookup.
 * @param lenv the old environment
 * @return the new environment
 */
Tree pushEnvBarrier(Tree lenv);

#endif  // ENVIRONMENT_HH
