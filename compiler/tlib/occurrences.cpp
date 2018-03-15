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
/**
 * @file occurrences.cpp
 * Count the number of occurences of each subtree of a root tree.
 */

// construction des representations graphiques

#include "occurrences.hh"
#include "compatibility.hh"

/**
 * Count the number of occurrences of each subtree of root
 */
Occurrences::Occurrences(Tree root)
{
	fKey = specificKey(root);
	countOccurrences(root);
	setCount(root,0); 	// root as no occurences in itself
}	

/**
 * Get the number of occurrences of t 
 */
int Occurrences::getCount(Tree t)
{
	Tree c;
	return (getProperty(t, fKey, c)) ? c->node().getInt() : 0;
}	

/**
 * Set the number of occurrences of t
 */
void Occurrences::setCount(Tree t, int c)
{
	setProperty(t, fKey, tree(c));
}	

/**
 * Creates a specific property key for occurrences count in root
 */
Tree Occurrences::specificKey(Tree root) 
{
	char keyname[256];
	snprintf(keyname, 256, "OCCURRENCES COUNT IN %p : ", (void*)(CTree*)root);

	return tree(unique(keyname));	
}	

/**
 * Increment the occurrences count of t and its subtrees
 */
void Occurrences::countOccurrences(Tree t)
{	
	setCount(t, getCount(t)+1);	// increment t occurrences count
	for (int i=0; i<t->arity(); i++) {
		countOccurrences(t->branch(i));
	}
}

