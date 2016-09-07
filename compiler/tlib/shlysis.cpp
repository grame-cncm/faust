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
 
 
 
/*****************************************************************************
******************************************************************************
								Tree Sharing Analysis
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
The sharing analysis of tree t is the annotation of all its subtrees t' 
with their number of occurences in t. As this annotation of t' depends of
a context (the tree t for which t' is a subtree) a specific property key
unique to each sharing analysis must be generated.

 API:
 ---- 
	
	shprkey(t) -> k		= unique sharing property key of t
	shcount(k,t') -> n	= returns the number of occurences of t' in t (where k = shprkey(t))
	shlysis(t)	-> k	= annotated the subtrees of t with prop (key sharing-count)
						  (0 if t' is not a subtree of t)

 History :
 ---------
 	2002-04-08 : First version
    2006-03-25 : Modifications for new symbolic rec trees
	
******************************************************************************
*****************************************************************************/

 /**
 * @file shlysis.cpp
 * The sharing analysis of tree t is the annotation of all its subtrees t' 
 * with their number of occurences in t. As this annotation of t' depends of
 * a context (the tree t for which t' is a subtree) a specific property key
 * unique to each sharing analysis must be generated.
 */

#include    <string.h>
#include    <stdlib.h>
#include    <stdio.h>

#include 	"shlysis.hh"
#include "compatibility.hh"

/**
 * Create a specific property key for the sharing count of subtrees of t
 */

Tree shprkey(Tree t) 
{
	char 	name[256];
	snprintf(name, 256, "SHARED IN %p : ", (void*)(CTree*)t);
	return tree(unique(name));
}	


/**
 * Return the value of sharing count or 0
 */

int shcount(Tree key, Tree t)
{
	Tree c;
	if (getProperty(t, key, c)) {
		return c->node().getInt();
	} else {
		return 0;
	}
}	



//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of t
//------------------------------------------------------------------------------

static void annotate(Tree k, Tree t, barrier foo);

static bool nobarrier (const Tree& t) { return false; }

/**
 * Do a sharing analysis : annotates all the subtrees of t 
 * with there occurences
 */
Tree shlysis(Tree t, barrier foo)
{
	Tree k = shprkey(t);
	annotate(k, t, foo);
	return k;
}


/**
 * Do a sharing analysis : annotates all the subtrees of t 
 * with there occurences
 */
Tree shlysis(Tree t)
{
	Tree k = shprkey(t);
	annotate(k, t, nobarrier);
	return k;
}


/**
 * Recursively increment the occurences count
 * of t and its subtrees
 */
static void annotate(Tree k, Tree t, barrier foo)
{
	cerr << "Annotate " << *t << endl;
	int c = shcount(k,t);
	if (c==0) {
		// First visit
		Tree var, body;
		if (isRec(t, var, body)) {
			// special case for recursive trees
			setProperty(t, k, tree(1));
			annotate(k, body, foo);
			return;
		} else {
			int n = t->arity();
			if (n>0 && ! foo(t)) {
				for (int i=0; i<n; i++) annotate(k, t->branch(i), foo);
			}
		}
	} else {
		//printf(" annotate %p with %d\n", (CTree*)t, c+1);
	}
	setProperty(t, k, tree(c+1));
}
