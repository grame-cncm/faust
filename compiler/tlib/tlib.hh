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
							TLIB : tree library
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
Tlib is a simple tree library inspired by the ATerm library. It is made of
five elements : symbols, nodes, smartpointers, trees and lists :

     +------------------------+
     |  	  shlysis 		  |
     +------------------------+
     |  		rec	  	   	  |
     |------------------------|
     |  	    list       	  |
     |------------------------|
     |  	    tree 		  |
     |------------------------|
     | nodes   |			  |
     |---------| smartpointer |
     | symbol  |			  |
     +---------+--------------+

 API:
 ----
 	1) Symbols :
	------------
 	Sym q = symbol("abcd"); 	: returns a symbol q of name "abcd"
	const char* s = name(q); 	: returns the name of symbol q

	2) Nodes :
	----------
	Node(symbol("abcd")); 	: node with symbol content
	Node(10);				: node with int content
	Node(3.14159);			: node with float content

	n->type();				: kIntNode or kFloatNode or kSymNode

	n->getInt();			: int content of n
	n->getFloat();			: float content of n
	n->getSym();			: symbol content of n

	- Pattern matching :

	if (isInt(n, &i))	... : int i = int content of n
	if (isFloat(n, &f))	... : float f = float content of n
	if (isSym(n, &s))	... : Sym s = Sym content of n

 	3) Trees :
	----------
 	tree (n)			   : tree of node n with no branch
	tree (n, t1)		   : tree of node n with a branch t
	tree (n, t1,...,tm)    : tree of node n with m branches t1,...,tm

	- Pattern matching :

	if (isTree (t, n))  	   ... : t has node n and no branches;
	if (isTree (t, n, &t1)     ... : t has node n and 1 branch, t1 is set accordingly;
	if (isTree (t, n, &t1...&tm)...: t has node n and m branches, ti's are set accordingly;

	- Accessors :

	t->node()		   : the node of t
	t->arity()  	   : the number of branches of t
	t->branch(i)	   : the ith branch of t

	4) List :
	---------

	nil					= predefined empty list
	cons (x,l)			= create a new list of head x and tail l
	list(a,b,..)		= cons(a, list(b,...))

	hd(cons(x,l)) 		= x,
	tl (cons(x,l)) 		= l
	nth(l,i)			= ith element of l (or nil)
	len(l)				= number of elements of l

	isNil(nil) 			= true 		(false otherwise)
	isList(cons(x,l)) 	= true 		(false otherwise)

	lmap(f, cons(x,l))	= cons(f(x), lmap(f,l))
	reverse([a,b,..,z])	= [z,..,b,a]
	reverseall([a,b,..,z])	= [ra(z),..,ra(b),ra(a)] where ra is reverseall

	- Set :
	(Sets are implemented as ordered lists of elements without duplication)

	isElement(e,s)			= true if e is an element of set s, false otherwise
	addElement(e,s)			= s U {e}
	singleton(e)			= {e}
	list2set(l)				= convert a list into a set
	setUnion(s1,s2)			= s1 U s2
	setIntersection(s1,s2)	= s1 intersection s2
	setIntersection(s1,s2)	= s1 - s2

	- Environment :

	pushEnv (key, val, env) -> env' create a new environment
	searchEnv (key,&v,env) -> bool  search for key in env and set v accordingly

	- Property list :

	setProperty (t, key, val) -> t		add the association (key x val) to the pl of t
	getProperty (t, key, &val) -> bool	search the pp of t for the value associated to key
	remProperty (t, key) -> t			remove any association (key x ?) from the pl of t

	5) Recursive trees
	------------------

	rid()				= a unique ID (a tree) used to identify recursive trees
	rec(id, t)			= a tree containing recursive references 'ref(id)'
	ref(id)				= a reference to a surrounding 'rec(id,t)'
	isRec(t, id, t')	= true if t = rec(id,t')
	isRef(t, id)		= true if t = ref(id)

	areEquiv(t,t')		= alpha equivalence of trees
	shmax(t)			= maximize the sharing of recursive subtrees


	6) Sharing Analysis :
	---------------------

	shprkey(t) -> k		= unique sharing property key of t
	shcount(k,t') -> n	= returns the number of occurences of t' in t (where k = shprkey(t))
	shlysis(t)	-> k	= annotated the subtrees of t with prop (key sharing-count)
						  (0 if t' is not a subtree of t)


 History :
 ---------
 	2002-02-08 : First version
 	2002-02-20 : New description of the API
 	2002-04-07 : Added Sharing Analysis 'shlysis.h'

******************************************************************************
*****************************************************************************/

#ifndef     __TLIB__
#define     __TLIB__

#include "symbol.hh"
#include "node.hh"
#include "tree.hh"
#include "num.hh"
#include "list.hh"
#include "shlysis.hh"

#endif
