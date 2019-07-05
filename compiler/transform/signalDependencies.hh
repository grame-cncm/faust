/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef _SignalDependencies_
#define _SignalDependencies_

#include <cstdlib>
#include <iostream>
#include <map>

#include "digraph.hh"
#include "digraphop.hh"
#include "property.hh"
#include "signalVisitor.hh"
#include "sigtyperules.hh"
#include "tree.hh"

using namespace std;

digraph<Tree> dependencyGraph(Tree sig);

class Dictionnary {
    map<Tree, Tree> fDefinitions;

   public:
    void add(Tree sig);
    Tree operator[](Tree id);
};
ostream& dotfile2(ostream& file, Dictionnary& dict, const digraph<Tree>& g);

/**
 * A bijective function that returns a unique ID, that starts with prefix, associated to sig
 * uniqueID(prefix,sig) -> ID
 */
Tree uniqueID(const char* prefix, Tree sig);

#endif