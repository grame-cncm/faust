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
 
/************************************************************************
 ************************************************************************
    Recursive Deepness
	How many lambdas are need to close a tree
    ---------------------------------------------------------------------
    Annotate all the subtrees of a tree with it's recursive deepness
	
	AnnotateRecness(t) : Annotate all the subtrees of t (a closed term)
	recness(t) : return the recursive deepness of t (a subtree of a 
	previously annotated tree
 ************************************************************************
 ************************************************************************/
 
 
 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "recness.hh"
#include "list.hh"
 
// Declaration of implementation

// recursive trees

Tree 	RECNESS 	= tree ("RECNESS");
	
//-----------------------------------------------------------------------------------------
// AnnotateRecness : Annotate all the subtrees of t (a closed term)
//-----------------------------------------------------------------------------------------

static int AR (Tree t, Tree env);
static int position(Tree var, Tree env);

void annotateRecness(Tree t)
{
	AR(t, nil);
}

int recness(Tree t)
{
	Tree prop = t->getProperty(RECNESS);
	assert(prop);
	return tree2int(prop);
}

//-----------------------------------------------------------------------------------------
// IMPLEMENTATION
//-----------------------------------------------------------------------------------------

int AR (Tree t, Tree env)
{
	Tree prop = t->getProperty(RECNESS);
	
	if (prop) {
		return tree2int(prop);
		
	} else {
		// make sure t is not in debruijn notation
		{ 
			int i; Tree body;
			assert(!isRef(t,i));
			assert(!isRec(t,body));
		}
		
		// compute and annotate t with its recness property
		int		r = 0;
		Tree 	var, body;
		
		if (isRec(t,var,body)) {
			r = AR(body, cons(var,env)) - 1;
			
		} else if (isRef(t,var)) {
			r = position(var,env);
			
		} else {
			// compute maximal recness of the subtrees
			for (int i = 0; i < t->arity(); i++) {
				r = max(r, AR(t->branch(i), env));
			}
		}
		t->setProperty(RECNESS,tree(r));
		return r;
	}
}

static int position(Tree var, Tree env)
{
	if (isNil(env)) {
		cerr << "RECNESS : internal error, empty env" << endl;
		exit(1);
	} else if (var == hd(env)) {
		return 1;
	} else {
		return 1 + position(var, tl(env));
	}
}
