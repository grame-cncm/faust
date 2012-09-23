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
 
#ifndef __SHLYSIS__
#define __SHLYSIS__
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
	
******************************************************************************
*****************************************************************************/

#include    <string.h>
#include    <stdlib.h>
#include    <stdio.h>

#include 	"list.hh"

typedef bool (*barrier)(const Tree& t);

//------------------------------------------------------------------------------
// shprkey : Create a specific property key for the sharing count of subtrees of t

Tree shprkey(Tree t);

//------------------------------------------------------------------------------
// shcount : returns the sharing count of t within the tree T of key k

int shcount(Tree key, Tree t);

#if 0

//------------------------------------------------------------------------------
// shlysis : create a specific property key for the sharing count of subtrees of t

Tree shlysis(Tree t);
Tree shlysis(Tree t, barrier foo);

#endif
#endif
