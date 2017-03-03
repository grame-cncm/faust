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
								TREE 
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
Trees are made of a Node associated with a list of branches : (Node x [CTree]).
Up to 4 branches are allowed in this implementation. A hash table is used to 
maximize the sharing of trees during construction : trees at different 
addresses always have a different content. Reference counting is used for 
garbage collection, and smart pointers P<CTree> should be used for permanent
storage of trees.

 API:
 ----
 tree (n) 				: tree of node n with no branch				
 tree (n, t1) 			: tree of node n with a branch t
 tree (n, t1,...,tm)	: tree of node n with m branches t1,...,tm
 
 Pattern matching :
 
 if (isTree (t, n)) 		... : t has node n and no branches; 
 if (isTree (t, n, &t1)		... : t has node n and 1 branch, t1 is set accordingly; 
 if (isTree (t, n, &t1...&tm)...: t has node n and m branches, ti's are set accordingly; 
 
 Accessors :
		 
 t->node()			: the node of t		{ return fNode; }
 t->arity() 		: the number of branches of t return fArity; }
 t->branch(i) 		: the ith branch of t

 Attributs :
		 
 t->attribut() 		: return the attribut (also a tree) of t
 t->attribut(t')	: set the attribut of t to t' 
		 
 Warning :
 ---------
 Since reference counters are used for garbage collecting, one must be careful not to 
 create cycles in trees The only possible source of cycles is by setting the attribut
 of a tree t to a tree t' that contains t as a subtree.  
	
 Properties:
 -----------
	If p and q are two CTree pointers  : 
		p != q  <=>  *p != *q

 History :
 ---------
 	2002-02-08 : First version
	2002-10-14 : counts for height and recursiveness added
	
******************************************************************************
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "tree.hh"
#include <fstream>
#include <cstdlib>
#include "exception.hh"

#define ERROR(s,t) { throw faustexception(s); }

Tree CTree::gHashTable[kHashTableSize];
bool CTree::gDetails = false;
unsigned int CTree::gVisitTime = 0;

// Constructor : add the tree to the hash table
CTree::CTree (unsigned int hk, const Node& n, const tvec& br) 
	:	fNode(n), 
		fType(0),
		fHashKey(hk), 
	 	fAperture(calcTreeAperture(n,br)), 
        fVisitTime(0),
		fBranch(br) 
{ 
	// link dans la hash table
   	int j = hk % kHashTableSize;
	fNext = gHashTable[j];
	gHashTable[j] = this;
}

// Destructor : remove the tree form the hash table
CTree::~CTree () 
{
	int		i = fHashKey % kHashTableSize;
	Tree	t = gHashTable[i];
	
	//printf("Delete of "); this->print(); printf("\n");
	if (t == this) {
		gHashTable[i] = fNext;
	} else {
		Tree p = NULL;
		while (t != this) {
			p = t;
			t = t->fNext;
		}
        faustassert(p);
		p->fNext = fNext;
	}
}

// equivalence 
bool CTree::equiv (const Node& n, const tvec& br) const
{
	return (fNode == n) && (fBranch == br);
}

unsigned int CTree::calcTreeHash( const Node& n, const tvec& br )
{
	unsigned int 			hk = n.type() ^ n.getInt();
	tvec::const_iterator  b = br.begin();
	tvec::const_iterator  z = br.end();
	
	while (b != z) {
    	hk = (hk << 1) ^ (hk >> 20) ^ ((*b)->fHashKey);
		++b;
	}
	return hk;
}

Tree CTree::make(const Node& n, int ar, Tree* tbl)
{
	tvec	br(ar); 
	
	for (int i=0; i<ar; i++)  br[i] = tbl[i];
	
	unsigned int 	hk  = calcTreeHash(n, br);
	Tree	t = gHashTable[hk % kHashTableSize];
	
	while (t && !t->equiv(n, br)) {
		t = t->fNext;
	}
	return (t) ? t : new CTree(hk, n, br);
}

Tree CTree::make(const Node& n, const tvec& br)
{
	unsigned int 	hk  = calcTreeHash(n, br);
	Tree	t = gHashTable[hk % kHashTableSize];
	
	while (t && !t->equiv(n, br)) {
		t = t->fNext;
	}
	return (t) ? t : new CTree(hk, n, br);
}

ostream& CTree::print (ostream& fout) const
{
    if (gDetails) {
        // print the adresse of the tree
		fout << "<" << this << ">@"; 
    }
	fout << node();
	int a = arity();
	if (a > 0) {
		int i; char sep;
		for (sep = '[', i = 0; i < a; sep = ',', i++) {
			fout << sep; branch(i)->print(fout); 
		}
		fout << ']';
	} 
	
	return fout;
}

void CTree::control ()
{
	printf("\ngHashTable Content :\n\n");
	for (int i = 0; i < kHashTableSize; i++) {
		Tree t = gHashTable[i];
		if (t) {
			printf ("%4d = ", i);
			while (t) {
				/*t->print();*/
				printf(" => ");
				t = t->fNext;
			}
			printf("VOID\n");
		}
	}
	printf("\nEnd gHashTable\n");
}

void CTree::init ()
{
    memset(gHashTable, 0, sizeof(Tree) * kHashTableSize);
}

// if t has a node of type int, return it otherwise error
int tree2int (Tree t)
{
	double	x;
	int		i;

	if (isInt(t->node(), &i)) {
		// nothing to do
	} else if (isDouble(t->node(), &x)) {
		i = int(x);
	} else {
		ERROR("the node of the tree is not an int nor a float\n", t);
	}
	return i;
}	
    
// if t has a node of type float, return it otherwise error
double tree2float (Tree t)
{
    double   x;
    int     i;

    if (isInt(t->node(), &i)) {
        x = double(i);
    } else if (isDouble(t->node(), &x)) {
        //nothing to do
    } else {
        ERROR("the node of the tree is not a float nor an int\n", t);
    }
    return x;
}   
    
// if t has a node of type float, return it as a double otherwise error
double tree2double (Tree t)
{
    double   x;
    int     i;

    if (isInt(t->node(), &i)) {
        x = double(i);
    } else if (isDouble(t->node(), &x)) {
        //nothing to do
    } else {
        ERROR("the node of the tree is not a float nor an int\n", t);
    }
    return double(x);
}   
	
// if t has a node of type symbol, return its name otherwise error		
const char* tree2str (Tree t)
{
	Sym s;
	if (!isSym(t->node(), &s)) {
		ERROR("the node of the tree is not a symbol\n", t);
	}
	return name(s);
}	

string tree2quotedstr (Tree t)
{
    return "\"" + string(tree2str(t)) + "\"";
}

// if t has a node of type ptr, return it otherwise error			
void* tree2ptr (Tree t)
{
	void*	x;
	if (! isPointer(t->node(), &x)) {
		ERROR("the node of the tree is not a pointer\n", t);
	}
	return x;
}	
			
/*
bool isTree (const Tree& t, const Node& n) 
{ 
	return (t->node() == n) && (t->arity() == 0);
}
*/

// Si ca ne pose pas de probl�es, c'est plus pratique	
bool isTree (const Tree& t, const Node& n) 
{ 
	return (t->node() == n);
}

bool isTree (const Tree& t, const Node& n, Tree& a)
{
    if ((t->node() == n) && (t->arity() == 1)) {
        a=t->branch(0);
        return true;
    } else {
        return false;
    }
}

bool isTree (const Tree& t, const Node& n, Tree& a, Tree& b)
{ 
	if ((t->node() == n) && (t->arity() == 2)) { 
		a=t->branch(0); 
		b=t->branch(1); 
		return true; 
	} else {
		return false;
	}
}

bool isTree (const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c) 
{ 
	if ((t->node() == n) && (t->arity() == 3)) { 
		a=t->branch(0); 
		b=t->branch(1); 
		c=t->branch(2); 
		return true; 
	} else {
		return false;
	}
}

bool isTree (const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c, Tree& d)  
{ 
	if ((t->node() == n) && (t->arity() == 4)) { 
		a=t->branch(0); 
		b=t->branch(1); 
		c=t->branch(2); 
		d=t->branch(3); 
		return true; 
	} else {
		return false;
	}
}

bool isTree (const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c, Tree& d, Tree& e)  
{ 
	if ((t->node() == n) && (t->arity() == 5)) { 
		a=t->branch(0); 
		b=t->branch(1); 
		c=t->branch(2); 
		d=t->branch(3); 
		e=t->branch(4); 
		return true; 
	} else {
		return false;
	}
}

// July 2005, support for symbol user data

void* getUserData(Tree t)
{
	Sym s;
	if (isSym(t->node(), &s)) {
		return getUserData(s);
	} else {
		return 0;
	}
}

/**
 * export the properties of a CTree as two vectors, one for the keys
 * and one for the associated values
 */

void CTree::exportProperties(vector<Tree>& keys, vector<Tree>& values)
{
    for (plist::const_iterator p = fProperties.begin(); p != fProperties.end(); p++) {
        keys.push_back(p->first);
        values.push_back(p->second);
    }
}

