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

#ifndef __NAMES__
#define __NAMES__

#include <string>

#include "tlib.hh"

/**
 * \file names.hh
 *
 * Interface for names management.
 *
 **/

/**
 * Indicates the identifier (if any) the expression was a definition of.
 * @param t the expression
 * @param id reference to the identifier
 * @return true if the expression t was a definition of id
 **/
LIBFAUST_API bool getDefNameProperty(Tree t, Tree& id);

void setDefNameProperty(Tree t, Tree id);
void setDefNameProperty(Tree t, const std::string& name);

/**
 * The number of definition names given so far. Taken before the value of a definition
 * is computed, it separates the names this value receives during the computation (from
 * definitions nested in it, like the right-hand side of an alias `foo = bar;`) from the
 * names it already had (from definitions evaluated independently of it).
 */
size_t defNameStamp();

/**
 * Give the definition name <id> to <t>, the value of a definition. <stamp> is the
 * defNameStamp() taken before <t> was computed.
 *
 * Hash-consing makes two definitions with the same value (`gain1 = 0.4; gain2 = 0.4;`)
 * share one tree, whose occurrences cannot be told apart. If <t> already had a different
 * name before <stamp>, it is the value of two independent definitions: its name is marked
 * shared, and stays so when <t> is renamed this way. A name given during the computation
 * of <t> (by a definition nested in the one named <id>) is simply replaced by <id>.
 *
 * <uncertain> tells that <id> itself may be wrong, as it comes from an ambiguous tree (the
 * closure of two definitions with the same right-hand side, a function that is the value
 * of two definitions). The name is then marked uncertain, until a definition that contains
 * this one renames <t>.
 */
void setDefNameProperty(Tree t, Tree id, size_t stamp, bool uncertain);
void setDefNameProperty(Tree t, const std::string& name, size_t stamp, bool uncertain);

/**
 * Give the definition name of <src> (if any) to <dst>, the value of <src>, as
 * setDefNameProperty(dst, id, stamp, uncertain) does, uncertain if the name of <src> is
 * ambiguous.
 */
void transferDefNameProperty(Tree src, Tree dst, size_t stamp);

/**
 * <dst>, the value of <src>, was computed before (it is found in a cache): if it has a
 * name different from the definition name of <src>, it is the value of two definitions
 * and its name is marked shared. Neither the name of <dst> nor when it was given is
 * changed, so that a definition that contains this evaluation still renames <dst>.
 */
void checkDefNameProperty(Tree src, Tree dst);

/**
 * True if the definition name of <t> is shared or uncertain: it would be wrong for some
 * of the occurrences of <t>. A name given later by the plain setDefNameProperty (a name
 * synthesized by the diagram generator) is not ambiguous.
 */
bool isDefNameAmbiguous(Tree t);

void setSigListNickName(Tree lsig, const std::string& nickname);

void setSigNickname(Tree t, const std::string& id);
bool getSigNickname(Tree t, Tree& id);

/**
 * Push a new layer and add a single definition.
 * @param id the symbol id to be defined
 * @param def the definition to be binded to the symbol id
 * @param lenv the environment where to push the layer and add the definition
 * @return the new environment
 */
Tree pushValueDef(Tree id, Tree def, Tree lenv);

#endif
