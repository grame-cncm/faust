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

#include <stdlib.h>
#include "list.hh"
#include "compatibility.hh"
#include "global.hh"
#include <map>
#include <cstdlib>

Tree cons (Tree a, Tree b) { return tree (gGlobal->CONS, a, b); }
Tree list0 () { return gGlobal->nil; }

bool isNil (Tree l) { return (l->node() == Node(gGlobal->NIL)) && (l->arity() == 0); }
bool isList (Tree l) { return (l->node() == Node(gGlobal->CONS)) && (l->arity() == 2); }

//------------------------------------------------------------------------------
// Printing of trees with special case for lists
//------------------------------------------------------------------------------

static bool printlist (Tree l, FILE* out)
{
	if (isList(l)) {
		
		char sep = '(';
		
		do {
			fputc(sep, out); sep = ',';
			print(hd(l));
			l = tl(l);
		} while (isList(l));
		
		if (! isNil(l)) {
			fprintf(out, " . ");
			print(l, out);
		}
		
		fputc(')', out);
		return true;
		
	} else if (isNil(l)) {
		
		fprintf(out, "nil");
		return true;
		
	} else {
		
		return false;
	}
}

void print (Tree t, FILE* out)
{
	int i; double f; Sym s; void* p;
	
	if (printlist(t, out))		return;
	
	Node n = t->node();
		 if (isInt(n, &i)) 		fprintf (out, "%d", i);
	else if (isDouble(n, &f)) 	fprintf (out, "%f", f);
	else if (isSym(n, &s)) 		fprintf (out, "%s", name(s));
	else if (isPointer(n, &p)) 	fprintf (out, "#%p", p);
	
	int k = t->arity();
	if (k > 0) {
		char sep = '[';
		for (int i=0; i<k; i++) {
			fputc(sep, out); sep = ',';
			print(t->branch(i), out);
		}
		fputc(']', out);
	} 
}

//------------------------------------------------------------------------------
// Elements of list
//------------------------------------------------------------------------------

Tree nth (Tree l, int i)
{
	while (isList(l)) {
		if (i == 0)  return hd(l);
		l = tl(l);
		i--;
	}
	return gGlobal->nil;
}

Tree replace(Tree l, int i, Tree e)
{
	return (i==0) ? cons(e,tl(l)) : cons( hd(l), replace(tl(l),i-1,e) );
}

int len (Tree l)
{
	int 	n = 0;
	while (isList(l)) { l = tl(l); n++; }
	return n;
}

//------------------------------------------------------------------------------
// Mapping and reversing
//------------------------------------------------------------------------------

Tree rconcat (Tree l, Tree q)
{
	while (isList(l)) { q = cons(hd(l),q); l = tl(l); }
	return q;
}

Tree concat (Tree l, Tree q)
{
	return rconcat(reverse(l), q);
}

Tree lrange (Tree l, int i, int j)
{
	Tree 	r = gGlobal->nil;
	int 	c = j;
	while (c>i) r = cons( nth(l,--c), r);
	return r;
}

//------------------------------------------------------------------------------
// Mapping and reversing
//------------------------------------------------------------------------------

static Tree rmap (tfun f, Tree l)
{
	Tree r = gGlobal->nil;
	while (isList(l)) { r = cons(f(hd(l)),r); l = tl(l); }
	return r;
}

Tree reverse (Tree l)
{
	Tree r = gGlobal->nil;
	while (isList(l)) { r = cons(hd(l),r); l = tl(l); }
	return r;
}

Tree lmap (tfun f, Tree l)
{
	return reverse(rmap(f,l));
}

Tree reverseall (Tree l)
{
	return isList(l) ? rmap(reverseall, l) : l;
}


//------------------------------------------------------------------------------
// Sets : implemented as ordered list
//------------------------------------------------------------------------------

bool isElement (Tree e, Tree l)
{
	while (isList(l)) {
		if (hd(l) == e) return true;
		if (hd(l) > e) return false;
		l = tl(l);
	}
	return false;
}

Tree addElement(Tree e, Tree l)
{
	if (isList(l)) {
		if (e < hd(l)) {
			return cons(e,l);
		} else if (e == hd(l)) {
			return l;
		} else {
			return cons(hd(l), addElement(e,tl(l)));
		}
	} else {
		return cons(e,gGlobal->nil);
	}
}

Tree remElement(Tree e, Tree l)
{
	if (isList(l)) {
		if (e < hd(l)) {
			return l;
		} else if (e == hd(l)) {
			return tl(l);
		} else {
			return cons(hd(l), remElement(e,tl(l)));
		}
	} else {
		return gGlobal->nil;
	}
}

Tree singleton (Tree e)
{
	return list1(e);
}

Tree list2set (Tree l)
{
	Tree s = gGlobal->nil;
	while (isList(l)) {
		s = addElement(hd(l),s);
		l = tl(l);
	}
	return s;
}

Tree setUnion (Tree A, Tree B)
{
	if (isNil(A)) 		return B;
	if (isNil(B)) 		return A;
	
	if (hd(A) == hd(B)) return cons(hd(A), setUnion(tl(A),tl(B)));
	if (hd(A) < hd(B)) 	return cons(hd(A), setUnion(tl(A),B));
	/* hd(A) > hd(B) */	return cons(hd(B), setUnion(A,tl(B)));
}

Tree setIntersection (Tree A, Tree B)
{
	if (isNil(A)) 		return A;
	if (isNil(B)) 		return B;
	if (hd(A) == hd(B)) return cons(hd(A), setIntersection(tl(A),tl(B)));
	if (hd(A) < hd(B)) 	return setIntersection(tl(A),B);
	/* (hd(A) > hd(B)*/	return setIntersection(A,tl(B));
}

Tree setDifference (Tree A, Tree B)
{
	if (isNil(A)) 		return A;
	if (isNil(B)) 		return A;
	if (hd(A) == hd(B)) return setDifference(tl(A),tl(B));
	if (hd(A) < hd(B)) 	return cons(hd(A), setDifference(tl(A),B));
	/* (hd(A) > hd(B)*/	return setDifference(A,tl(B));
}
	
//------------------------------------------------------------------------------
// Environments
//------------------------------------------------------------------------------

Tree pushEnv (Tree key, Tree val, Tree env)
{
	return cons (cons(key,val), env);
}

bool searchEnv (Tree key, Tree& v, Tree env)
{
	while (isList(env)) {
		if (hd(hd(env)) == key) {
			v = tl(hd(env));
			return true;
		}
		env = tl(env);
	}
	return false;
}

#if 0

//------------------------------------------------------------------------------
// Property list
//------------------------------------------------------------------------------

static bool findKey (Tree pl, Tree key, Tree& val)
{
	if (isNil(pl)) 				return false;
	if (left(hd(pl)) == key) 	{ val= right(hd(pl)); return true; }
	/*  left(hd(pl)) != key	*/	return findKey (tl(pl), key, val); 
}

static Tree updateKey (Tree pl, Tree key, Tree val)
{
	if (isNil(pl)) 				return cons ( cons(key,val), gGlobal->nil );
	if (left(hd(pl)) == key) 	return cons ( cons(key,val), tl(pl) );
	/*  left(hd(pl)) != key	*/	return cons ( hd(pl), updateKey( tl(pl), key, val ));
}

static Tree removeKey (Tree pl, Tree key)
{
	if (isNil(pl)) 				return gGlobal->nil;
	if (left(hd(pl)) == key) 	return tl(pl);
	/*  left(hd(pl)) != key	*/	return cons (hd(pl), removeKey(tl(pl), key));
}

#endif

#if 0
void setProperty (Tree t, Tree key, Tree val)
{
	CTree* pl = t->attribut();
	if (pl) t->attribut(updateKey(pl, key, val)); 
	else 	t->attribut(updateKey(gGlobal->nil, key, val));
}

void remProperty (Tree t, Tree key)
{
	CTree* pl = t->attribut();
	if (pl) t->attribut(removeKey(pl, key));
}

bool getProperty (Tree t, Tree key, Tree& val)
{
	CTree* pl = t->attribut();
	if (pl) return findKey(pl, key, val);
	else 	return false;
}

#else
// nouvelle implementation
void setProperty (Tree t, Tree key, Tree val)
{
	t->setProperty(key, val);
}

bool getProperty (Tree t, Tree key, Tree& val)
{
	CTree* pl = t->getProperty(key);
	if (pl) {
		val = pl;
		return true;
	} else {
		return false;
	}
}

void remProperty (Tree t, Tree key)
{
	exit(1); // fonction not implemented
}
#endif


//------------------------------------------------------------------------------
// Bottom Up Tree Mapping
//------------------------------------------------------------------------------

Tree tmap (Tree key, tfun f, Tree t)
{	
	//printf("start tmap\n");
	Tree p; 
	
	if (getProperty(t, key, p)) {
		
		return (isNil(p)) ? t : p;	// truc pour eviter les boucles
		
	} else {

        tvec br;
        int n = t->arity();
        for (int i = 0; i < n; i++) {
            br.push_back( tmap(key, f, t->branch(i)) );
        }

        Tree r1 = tree(t->node(), br);

		Tree r2 = f(r1);
		if (r2 == t) {
			setProperty(t, key, gGlobal->nil);
		} else {
			setProperty(t, key, r2);
		}
		return r2;
	}
}
		
//------------------------------------------------------------------------------
// substitute :remplace toutes les occurences de 'id' par 'val' dans 't'
//------------------------------------------------------------------------------

// genere une clef unique propre � cette substitution
static Tree substkey(Tree t, Tree id, Tree val) 
{
	char 	name[256];
	snprintf(name, 255, "SUBST<%p,%p,%p> : ", (void*)(CTree*)t, (void*)(CTree*)id, (void*)(CTree*)val);
	return tree(unique(name));
}	

// realise la substitution proprement dite tout en mettant a jour la propriete
// pour ne pas avoir a la calculer deux fois

static Tree subst (Tree t, Tree propkey, Tree id, Tree val)
{
	Tree p;
	
	if (t==id) {
		return val;
		
	} else if (t->arity() == 0) {
		return t;
	} else if (getProperty(t, propkey, p)) {
		return (isNil(p)) ?  t : p;
	} else {

        tvec br;
        int n = t->arity();
        for (int i = 0; i < n; i++) {
            br.push_back( subst(t->branch(i), propkey, id, val) );
        }

        Tree r = tree(t->node(), br);

		if (r == t) {
			setProperty(t, propkey, gGlobal->nil);
		} else {
			setProperty(t, propkey, r);
		}
		return r;
	}
		
}

// remplace toutes les occurences de 'id' par 'val' dans 't'
Tree substitute (Tree t, Tree id, Tree val)
{
	return subst (t, substkey(t,id,val), id, val);
}
	
	
	

	
