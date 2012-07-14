/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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
 
#ifndef __PATTERNMATCHER__
#define __PATTERNMATCHER__

using namespace std;
#include <vector>
#include "tlib.hh"

struct Automaton;

/* Create a pattern matching automaton from the given list of rules. */

Automaton *make_pattern_matcher(Tree R);

/* Apply the pattern matcher to a single argument, starting from a given state
   s. Returns the resulting state, modifies the variable bindings E
   accordingly, and sets C to the resulting closure if a final state is
   reached. Result will be -1 to indicate a matching failure, and C will be
   set to nil if no final state has been reached yet. */

int apply_pattern_matcher(Automaton *A,	// automaton
                        int s,          // start state
                        Tree X,         // arg to be matched
                        Tree& C,        // output closure (if any)
                        vector<Tree>& E);	// modified output environments

#endif
