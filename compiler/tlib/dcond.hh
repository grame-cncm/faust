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

#ifndef DCOND_HH
#define DCOND_HH

#include "list.hh"

/*
 * Dcond are conditions in disjunctive normal form implemented
 * as set of set of Tree
 */

// WARNING : Memoization probably needed here !!!!

Tree dnfCond(Tree c);                  // create a dcond from a simple expression

Tree dnfAnd(Tree c1, Tree c2);         // And operation between two conditions in DNF

Tree dnfOr(Tree c1, Tree c2);          // Or operation between two conditions in DNF

bool dnfLess(Tree c1, Tree c2);        // True if (c1 v c2) == c2 i.e. c1 ==> c2

Tree cnfCond(Tree c);
Tree cnfAnd(Tree c1, Tree c2);
Tree cnfOr(Tree c1, Tree c2);
bool cnfLess(Tree c1, Tree c2);

#endif // DCOND_HH
