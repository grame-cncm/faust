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
								LIST 
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
This file contains several extensions to the tree library : 
	- lists : based on a operations like cons, hd , tl, ... 
	- environments : list of associations (key value)
	- property list : used to annotate trees


 API:
 ---- 

	List :
	-----
	
	nil					= predefined empty list
	cons (x,l)			= create a nex list of head x and tail l
	hd(cons(x,l)) 		= x, 
	tl (cons(x,l)) 		= l
	nth(l,i)			= ith element of l (or nil)
	replace(l,i,e)		= a copy of l where the ith element is e
	len(l)				= number of elements of l
	isNil(nil) 			= true 		(false otherwise)
	isList(cons(x,l)) 	= true 		(false otherwise)
	list(a,b,..)		= cons(a, list(b,...))
	
	lmap(f, cons(x,l))	= cons(f(x), lmap(f,l))
	reverse([a,b,..,z])	= [z,..,b,a]
	reverseall([a,b,..,z])	= [ra(z),..,ra(b),ra(a)] where ra is reverseall
	
	Set :
	-----
	(Sets are implemented as ordered lists of elements without duplication)
	
	isElement(e,s)			= true if e is an element of set s, false otherwise
	addElement(e,s)			= s U {e}
	remElement(e,s)			= s - {e}
	singleton(e)			= {e}
	list2set(l)				= convert a list into a set 
	setUnion(s1,s2)			= s1 U s2
	setIntersection(s1,s2)	= s1 intersection s2
	setDifference(s1,s2)	= s1 - s2
	
	Environment : 
	-------------
	
	An 'environment' is a stack of pairs (key x value) used to keep track of lexical bindings
	
	pushEnv (key, val, env) -> env' create a new environment
	searchEnv (key,&v,env) -> bool  search for key in env and set v accordingly
	
	search(k1,&v, push(k2,x,env)) 	= true and v is set to x if k1==k2
									= search(k1,&v,env) if k1 != k2
	Property list :
	---------------
	
	Every tree can be annotated with an 'attribut' field. This attribute field 
	can be used to manage a property list (pl). A property list is a list of pairs
	key x value, with three basic operations :
	
	setProperty (t, key, val) -> t		add the association (key x val) to the pl of t
	getProperty (t, key, &val) -> bool	search the pp of t for the value associated to key
	remProperty (t, key) -> t			remove any association (key x ?) from the pl of t
	
 Warning :
 ---------
 Since reference counters are used for garbage collecting, one must be careful not to 
 create cycles in trees. The only possible source of cycles is by setting the attribut
 of a tree t to a tree t' that contains t as a subtree.  
	
 History :
 ---------
 	2002-02-08 : First version
 	2002-02-20 : New description of the API, non recursive lmap and reverse
 	2002-03-29 : Added function remElement(e,set), corrected comment error
	
******************************************************************************
*****************************************************************************/

#ifndef     __LIST__
#define     __LIST__

#include "symbol.hh"
#include "tree.hh"
#include <stdio.h>

// Basic List Operations implemented on trees

typedef Tree (*tfun)(Tree);

void print (Tree t, FILE* out=stdout);

// to create new lists
Tree 	cons (Tree a, Tree b);
Tree 	list0 ();
inline Tree 	list1 (Tree a) 							{ return cons (a, list0()); }
inline Tree 	list2 (Tree a, Tree b) 					{ return cons (a, list1(b)); }
inline Tree 	list3 (Tree a, Tree b, Tree c) 			{ return cons (a, list2(b, c)); }
inline Tree 	list4 (Tree a, Tree b, Tree c, Tree d) 	{ return cons (a, list3(b, c, d)); }

// to access the head and the tail of a list
inline Tree 	hd (Tree l)				{ return l->branch(0); }
inline Tree 	tl (Tree l)				{ return l->branch(1); }

// predicates
bool 	isNil (Tree l);
bool 	isList (Tree l);

// predicates
Tree			nth(Tree l, int i);
Tree			replace(Tree l, int i, Tree e);
int				len(Tree l);

// reversing
Tree reverse (Tree l);
Tree reverseall (Tree l);

// operations
Tree rconcat(Tree l1, Tree l2);
Tree concat(Tree l1, Tree l2);
Tree lrange(Tree l, int i, int j); // de i a j exclu

// mapping
Tree lmap 	(tfun f, Tree l);

// Sets
bool isElement (Tree e, Tree l);
Tree addElement (Tree e, Tree l1);
Tree remElement (Tree e, Tree l1);
Tree singleton (Tree l);
Tree list2set (Tree l);
Tree setUnion (Tree l1, Tree l2);
Tree setIntersection (Tree l1, Tree l2);
Tree setDifference (Tree l1, Tree l2);

// Pairs

//inline Tree pair (Tree t1, Tree t2) { return cons(t1,t2);  }
inline Tree left (Tree t) 			{ return t->branch(0); }
inline Tree right (Tree t) 			{ return t->branch(1); }

// Environment : stack of pairs key value)
//Tree 	pushEnv (Tree key, Tree val, Tree env=gGlobal->nil);
Tree 	pushEnv (Tree key, Tree val, Tree env);
bool 	searchEnv (Tree key, Tree& v, Tree env);

// Operations on the property list of a tree t
void 	setProperty (Tree t, Tree key, Tree val);
bool 	getProperty (Tree t, Tree key, Tree& val);
void 	remProperty (Tree t, Tree key);

// Mapping sur les arbres
Tree tmap (Tree k, tfun f, Tree t);

// remplacement
Tree substitute (Tree t, Tree id, Tree val);

#endif
