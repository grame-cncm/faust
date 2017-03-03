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
******************************************************************************/

/** \file tree.hh
 * A tree library with hashconsing and maximal sharing capabilities.
 *
 * A tree library with hashconsing and maximal sharing capabilities.
 *
 * <b>API:</b>
 *
 * \li tree (n) 				: tree of node n with no branch
 * \li tree (n, t1) 			: tree of node n with a branch t
 * \li tree (n, t1,...,tm)		: tree of node n with m branches t1,...,tm
 *
 * <b>Useful conversions :</b>
 *
 * \li int 			tree2int (t)	: if t has a node of type int, return it otherwise error
 * \li float 		tree2float (t)	: if t has a node of type float, return it otherwise error
 * \li const char* 	tree2str (t)	: if t has a node of type symbol, return its name otherwise error
 * \li void* 		tree2ptr (t)	: if t has a node of type ptr, return it otherwise error
 *
 * <b>Pattern matching :</b>
 *
 * \li if (isTree (t, n)) 		... 	: t has node n and no branches;
 * \li if (isTree (t, n, &t1)		... : t has node n and 1 branch, t1 is set accordingly;
 * \li if (isTree (t, n, &t1...&tm)...	: t has node n and m branches, ti's are set accordingly;
 *
 * <b>Accessors :</b>
 *
 * \li t->node()		: the node of t		{ return fNode; }
 * \li t->height() 		: lambda height such that H(x)=0, H(\x.e)=1+H(e), H(e*f)=max(H(e),H(f))
 * \li t->arity() 		: the number of branches of t { return fArity; }
 * \li t->branch(i) 	: the ith branch of t
 *
 * <b>Attributs :</b>
 *
 * \li t->attribut() 	: return the attribut (also a tree) of t
 * \li t->attribut(t')	: set the attribut of t to t'
 *
 *
 * <b>Properties:</b>
 *
 * If p and q are two CTree pointers  :
 * 		p != q  <=>  *p != *q
 *
 **/

/*****************************************************************************
******************************************************************************/

#ifndef __TREE__
#define __TREE__

#include <vector>
#include <map>

#include "symbol.hh"
#include "node.hh"
#include "garbageable.hh"
#include "exception.hh"

//---------------------------------API---------------------------------------

class 	CTree ;
typedef CTree* Tree;

typedef map<Tree, Tree>	plist;
typedef vector<Tree>	tvec;

/**
 * A CTree = (Node x [CTree]) is a Node associated with a list of subtrees called branches.
 * A CTree = (Node x [CTree]) is the association of a content Node and a list of subtrees
 * called branches. In order to maximize the sharing of trees, hashconsing techniques are used.
 * Ctrees at different addresses always have a different content. A first consequence of this
 * approach is that a fast equality test on pointers can be used as an equality test on CTrees.
 * A second consequence is that a CTree can NEVER be modified. But a property list is associated
 * to each CTree that can be used to attach arbitrary information to it. Due to the maximal
 * sharing property it is therefore easy to do memoization using these property lists.
 *
 * Means are also provided to do maximal sharing on recursive trees. The idea is to start from
 * a deBruijn representation and progressively build a classical representation such that
 * alpha-equivalent recursive CTrees are necesseraly identical (and therefore shared).
 *
 * WARNING : in the current implementation CTrees are allocated but never deleted
 **/

class CTree : public virtual Garbageable
{
 private:
	static const int 	kHashTableSize = 2000000; //510511;	///< size of the hash table used for "hash consing"
	static Tree			gHashTable[kHashTableSize];	///< hash table used for "hash consing"

 public:
	static bool			gDetails;					///< Ctree::print() print with more details when true
    static unsigned int gVisitTime;                 ///< Should be incremented for each new visit to keep track of visited tree.

 private:
	// fields
    Tree            fNext;				///< next tree in the same hashtable entry
    Node            fNode;				///< the node content of the tree
    void*           fType;				///< the type of a tree
    plist           fProperties;		///< the properties list attached to the tree
    unsigned int	fHashKey;			///< the hashtable key
    int             fAperture;			///< how "open" is a tree (synthezised field)
    unsigned int	fVisitTime;			///< keep track of visits
    tvec            fBranch;			///< the subtrees

	CTree (unsigned int hk, const Node& n, const tvec& br); 						///< construction is private, uses tree::make instead

	bool 		equiv 				(const Node& n, const tvec& br) const;	///< used to check if an equivalent tree already exists
	static unsigned int	calcTreeHash 		(const Node& n, const tvec& br);		///< compute the hash key of a tree according to its node and branches
	static int	calcTreeAperture 	(const Node& n, const tvec& br);		///< compute how open is a tree

 public:
	virtual ~CTree ();

	static Tree make (const Node& n, int ar, Tree br[]);		///< return a new tree or an existing equivalent one
	static Tree make(const Node& n, const tvec& br);			///< return a new tree or an existing equivalent one

 	// Accessors
 	const Node& node() const		{ return fNode; 		}	///< return the content of the tree
 	int 		arity() const		{ return (int)fBranch.size();}	///< return the number of branches (subtrees) of a tree
    Tree 		branch(int i) const	{ return fBranch[i];	}	///< return the ith branch (subtree) of a tree
    const tvec& branches() const	{ return fBranch;	}       ///< return all branches (subtrees) of a tree
    unsigned int 		hashkey() const		{ return fHashKey; 		}	///< return the hashkey of the tree
 	int 		aperture() const	{ return fAperture; 	}	///< return how "open" is a tree in terms of free variables
 	void 		setAperture(int a) 	{ fAperture=a; 			}	///< modify the aperture of a tree


	// Print a tree and the hash table (for debugging purposes)
	ostream& 	print (ostream& fout) const; 					///< print recursively the content of a tree on a stream
	static void control ();										///< print the hash table content (for debug purpose)
    
    static void init ();
  
	// type information
	void		setType(void* t) 	{ fType = t; }
	void*		getType() 			{ return fType; }
	
    // Keep track of visited trees (WARNING : non reentrant)
    static void     startNewVisit()                 { ++gVisitTime; }
    bool            isAlreadyVisited()              { return fVisitTime==gVisitTime; }
    void            setVisited()                    { /*faustassert(fVisitTime!=gVisitTime);*/ fVisitTime=gVisitTime; }


	// Property list of a tree
	void		setProperty(Tree key, Tree value) { fProperties[key] = value; }
	void		clearProperty(Tree key) { fProperties.erase(key); }
	void		clearProperties()		{ fProperties = plist(); }

	void		exportProperties(vector<Tree>& keys, vector<Tree>& values);

	Tree		getProperty(Tree key) {
		plist::iterator i = fProperties.find(key);
		if (i==fProperties.end()) {
			return 0;
		} else {
			return i->second;
		}
	}
};

//---------------------------------API---------------------------------------

// to build trees
inline Tree tree (const Node& n) { Tree br[1]; return CTree::make(n, 0, br); }
inline Tree tree (const Node& n, const Tree& a) { Tree br[]= {a}; return CTree::make(n, 1, br); }
inline Tree tree (const Node& n, const Tree& a, const Tree& b) { Tree br[]= {a,b}; return CTree::make(n, 2, br); }
inline Tree tree (const Node& n, const Tree& a, const Tree& b, const Tree& c) { Tree br[]= {a,b,c}; return CTree::make(n, 3, br); }
inline Tree tree (const Node& n, const Tree& a, const Tree& b, const Tree& c, const Tree& d) { Tree br[]= {a,b,c,d}; return CTree::make(n, 4, br); }

inline Tree tree (const Node& n, const Tree& a, const Tree& b, const Tree& c, const Tree& d, const Tree& e) { Tree br[]= {a,b,c,d,e}; return CTree::make(n, 5, br); }
inline Tree tree (const Node& n, const tvec& br) { return CTree::make(n, br); }

// useful conversions
int 		tree2int (Tree t);		///< if t has a node of type int, return it otherwise error
double      tree2float (Tree t);    ///< if t has a node of type float, return it otherwise error
double      tree2double (Tree t);    ///< if t has a node of type float, return it otherwise error
const char* tree2str (Tree t);		///< if t has a node of type symbol, return its name otherwise error
string      tree2quotedstr (Tree t);
void*       tree2ptr (Tree t);		///< if t has a node of type ptr, return it otherwise error
void*       getUserData(Tree t);	///< if t has a node of type symbol, return the associated user data

// pattern matching
bool isTree (const Tree& t, const Node& n);
bool isTree (const Tree& t, const Node& n, Tree& a);
bool isTree (const Tree& t, const Node& n, Tree& a, Tree& b);
bool isTree (const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c);
bool isTree (const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c, Tree& d);
bool isTree (const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c, Tree& d, Tree& e);

//printing
inline ostream& operator << (ostream& s, const CTree& t) { return t.print(s); }


//-----------------------------------------------------------------------------
// recursive trees
//-----------------------------------------------------------------------------

// creation a recursive trees

Tree rec(Tree body);						///< create a de Bruijn recursive tree
Tree rec(Tree id, Tree body);				///< create a symbolic recursive tree

bool isRec(Tree t, Tree& body);				///< is t a de Bruijn recursive tree
bool isRec(Tree t, Tree& id, Tree& body);	///< is t a symbolic recursive tree

// creation of recursive references

Tree ref(int level);						///< create a de Bruijn recursive reference
Tree ref(Tree id);							///< create a symbolic recursive reference

bool isRef(Tree t, int& level);				///< is t a de Bruijn recursive reference
bool isRef(Tree t, Tree& id);				///< is t a symbolic recursive reference


// Open vs Closed regarding de Bruijn references

inline bool isOpen(Tree t)	 { return t->aperture() > 0; }	///< t contains free de Bruijn references
inline bool isClosed(Tree t) { return t->aperture() <= 0;}	///< t dont contain free de Bruijn ref

// lift by 1 the free de Bruijn references

Tree lift(Tree t); 							////< add 1 to the free de bruijn references of t

Tree deBruijn2Sym (Tree t);					////< transform a tree from deBruijn to symbolic notation
void updateAperture (Tree t);				////< update aperture field of a tree in symbolic notation

//---------------------------------------------------------------------------

class Tabber
{
	int fIndent;
    int fPostInc;
  public:
    Tabber(int n=0) : fIndent(n), fPostInc(0)	{}
    Tabber& operator++() 			{ fPostInc++; return *this;}
	Tabber& operator--() 			{ faustassert(fIndent > 0); fIndent--; return *this; }

	ostream& print (ostream& fout)
                        { for (int i=0; i<fIndent; i++) fout << '\t';  fIndent+=fPostInc; fPostInc=0; return fout; }
};

//printing
inline ostream& operator << (ostream& s, Tabber& t) { return t.print(s); }

#endif
