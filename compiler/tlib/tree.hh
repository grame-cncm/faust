/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2024 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

/*****************************************************************************
******************************************************************************/

/** \file tree.hh
 * A tree library with hashconsing and maximal sharing capabilities.
 *
 * <b>API:</b>
 *
 * \li tree (n)            : tree of node n with no branch
 * \li tree (n, t1)        : tree of node n with a branch t
 * \li tree (n, t1,...,tm) : tree of node n with m branches t1,...,tm
 *
 * <b>Useful conversions :</b>
 *
 * \li int         tree2int (t)    : if t has a node of type int, return it otherwise error
 * \li float       tree2double (t) : if t has a node of type double, return it otherwise error
 * \li const char  tree2str (t)    : if t has a node of type symbol, return its name otherwise error
 * \li void        tree2ptr (t)    : if t has a node of type ptr, return it otherwise error
 *
 * <b>Pattern matching :</b>
 *
 * \li if (isTree (t, n))           : t has node n and no branches;
 * \li if (isTree (t, n, &t1)       : t has node n and 1 branch, t1 is set accordingly;
 * \li if (isTree (t, n, &t1...&tm) : t has node n and m branches, ti's are set accordingly;
 *
 * <b>Accessors :</b>
 *
 * \li t->node()     : the node of t { return fNode; }
 * \li t->height()   : lambda height such that H(x)=0, H(\x.e)=1+H(e), H(e*f)=max(H(e),H(f))
 * \li t->arity()    : the number of branches of t { return fArity; }
 * \li t->branch(i)  : the ith branch of t
 *
 * <b>Attributs :</b>
 *
 * \li t->attribut()   : return the attribute (also a tree) of t
 * \li t->attribut(t') : set the attribute of t to t'
 *
 * <b>Properties:</b>
 *
 * If p and q are two CTree pointers :
 *     p != q <=> *p != *q
 *
 **/

/*****************************************************************************
******************************************************************************/

#ifndef __TREE__
#define __TREE__

#include <map>
#include <vector>

#include "exception.hh"
#include "garbageable.hh"
#include "node.hh"
#include "symbol.hh"

//---------------------------------API---------------------------------------

class CTree;
typedef CTree* Tree;

typedef std::vector<Tree> tvec;

namespace std {

// The std::less <CTree*>comparison function is redefined to provide an unique and stable ordering
// for all CTree instances and so maintain determinism.
template <>
struct less<CTree*> {
    bool operator()(const CTree* lhs, const CTree* rhs) const;
};

} 

/**
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
 * alpha-equivalent recursive CTrees are necessarily identical (and therefore shared).
 *
 **/

class LIBFAUST_API CTree : public virtual Garbageable {
   protected:
    static const int kHashTableSize = 400009;     ///< size of the hash table (prime number)
    static size_t    gSerialCounter;              ///< the serial number counter
    static Tree      gHashTable[kHashTableSize];  ///< hash table used for "hash consing"

   public:
    static bool gDetails;  ///< CTree::print() print with more details when true
    ///< Should be incremented for each new visit to keep track of visited tree
    static unsigned int gVisitTime;

    typedef std::map<Tree, Tree> plist;

   protected:
    // fields
    Tree         fNext;        ///< next tree in the same hashtable entry
    Node         fNode;        ///< the node content of the tree
    void*        fType;        ///< the type of a tree
    plist        fProperties;  ///< the properties list attached to the tree
    size_t       fHashKey;     ///< the hashtable key
    size_t       fSerial;      ///< the increasing serial number
    int          fAperture;    ///< how "open" is a tree (synthesized field)
    unsigned int fVisitTime;   ///< keep track of visits
    tvec         fBranch;      ///< the subtrees

    CTree() : fNext(nullptr), fType(nullptr), fHashKey(0), fSerial(0), fAperture(0), fVisitTime(0)
    {
    }
    ///< construction is private, uses tree::make instead
    CTree(size_t hk, const Node& n, const tvec& br);

    ///< used to check if an equivalent tree already exists
    bool equiv(const Node& n, const tvec& br) const;

    static size_t calcTreeHash(
        const Node& n,
        const tvec& br);  ///< compute the hash key of a tree according to its node and branches
    static int calcTreeAperture(const Node& n, const tvec& br);  ///< compute how open is a tree

   public:
    virtual ~CTree();

    static Tree make(const Node& n, int ar,
                     Tree br[]);  ///< return a new tree or an existing equivalent one
    static Tree make(const Node& n,
                     const tvec& br);  ///< return a new tree or an existing equivalent one

    // Accessors
    const Node& node() const { return fNode; }  ///< return the content of the tree
    int         arity() const
    {
        return (int)fBranch.size();
    }  ///< return the number of branches (subtrees) of a tree
    Tree branch(int i) const { return fBranch[i]; }   ///< return the ith branch (subtree) of a tree
    const tvec& branches() const { return fBranch; }  ///< return all branches (subtrees) of a tree
    size_t      hashkey() const { return fHashKey; }  ///< return the hashkey of the tree
    size_t      serial() const { return fSerial; }    ///< return the serial of the tree
    int         aperture() const
    {
        return fAperture;
    }  ///< return how "open" is a tree in terms of free variables
    void setAperture(int a) { fAperture = a; }  ///< modify the aperture of a tree

    // Print a tree and the hash table (for debugging purposes)
    std::ostream& print(
        std::ostream& fout) const;  ///< print recursively the content of a tree on a stream
    static void control();          ///< print the hash table content (for debug purpose)

    static void init();

    // type information
    void  setType(void* t) { fType = t; }
    void* getType() { return fType; }

    // Keep track of visited trees (WARNING : non reentrant)
    static void startNewVisit() { ++gVisitTime; }
    bool        isAlreadyVisited() { return fVisitTime == gVisitTime; }
    void        setVisited() { fVisitTime = gVisitTime; }

    // Property list of a tree
    void setProperty(Tree key, Tree value) { fProperties[key] = value; }
    void clearProperty(Tree key) { fProperties.erase(key); }
    void clearProperties() { fProperties = plist(); }

    void exportProperties(std::vector<Tree>& keys, std::vector<Tree>& values);

    Tree getProperty(Tree key)
    {
        plist::iterator i = fProperties.find(key);
        return (i == fProperties.end()) ? nullptr : i->second;
    }
};

// The comparison function relies on lhs->serial() which provides an unique and stable ordering
// for all CTree instances and so maintain determinism.
namespace std {
inline bool less<CTree*>::operator()(const CTree* lhs, const CTree* rhs) const
{
    return lhs->serial() < rhs->serial();
}
};

//---------------------------------API---------------------------------------
// To build trees

inline Tree tree(const Node& n)
{
    return CTree::make(n, 0, nullptr);
}

inline Tree tree(const Node& n, const Tree& a)
{
    return CTree::make(n, {a});
}

inline Tree tree(const Node& n, const Tree& a, const Tree& b)
{
    return CTree::make(n, {a, b});
}

inline Tree tree(const Node& n, const Tree& a, const Tree& b, const Tree& c)
{
    return CTree::make(n, {a, b, c});
}

inline Tree tree(const Node& n, const Tree& a, const Tree& b, const Tree& c, const Tree& d)
{
    return CTree::make(n, {a, b, c, d});
}

inline Tree tree(const Node& n, const Tree& a, const Tree& b, const Tree& c, const Tree& d,
                 const Tree& e)
{
    return CTree::make(n, {a, b, c, d, e});
}

inline Tree tree(const Node& n, const tvec& br)
{
    return CTree::make(n, br);
}

// Useful conversions
LIBFAUST_API int    tree2int(Tree t);  ///< if t has a node of type int, return it otherwise error
LIBFAUST_API double tree2double(
    Tree t);  ///< if t has a node of type double, return it otherwise error
LIBFAUST_API const char* tree2str(
    Tree t);  ///< if t has a node of type symbol, return its name otherwise error
std::string        tree2quotedstr(Tree t);
void*              tree2ptr(Tree t);  ///< if t has a node of type ptr, return it otherwise error
LIBFAUST_API void* getUserData(
    Tree t);  ///< if t has a node of type symbol, return the associated user data

// Pattern matching
bool isTree(const Tree& t, const Node& n);
bool isTree(const Tree& t, const Node& n, Tree& a);
bool isTree(const Tree& t, const Node& n, Tree& a, Tree& b);
bool isTree(const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c);
bool isTree(const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c, Tree& d);
bool isTree(const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c, Tree& d, Tree& e);

// Printing
inline std::ostream& operator<<(std::ostream& s, const CTree& t)
{
    return t.print(s);
}

//-----------------------------------------------------------------------------
// Recursive trees
//-----------------------------------------------------------------------------

// Creation of recursive trees

Tree rec(Tree body);           ///< create a de Bruijn recursive tree
Tree rec(Tree id, Tree body);  ///< create a symbolic recursive tree

bool              isRec(Tree t, Tree& body);            ///< is t a de Bruijn recursive tree
LIBFAUST_API bool isRec(Tree t, Tree& id, Tree& body);  ///< is t a symbolic recursive tree

// Creation of recursive references

Tree ref(int level);  ///< create a de Bruijn recursive reference
Tree ref(Tree id);    ///< create a symbolic recursive reference

bool isRef(Tree t, int& level);  ///< is t a de Bruijn recursive reference
bool isRef(Tree t, Tree& id);    ///< is t a symbolic recursive reference

// Open vs Closed regarding de Bruijn references

inline bool isOpen(Tree t)
{
    return t->aperture() > 0;
}  ///< t contains free de Bruijn references

inline bool isClosed(Tree t)
{
    return t->aperture() <= 0;
}  ///< t does not contain free de Bruijn ref

// Lift by 1 the free de Bruijn references

Tree lift(Tree t);  ////< add 1 to the free de bruijn references of t

Tree deBruijn2Sym(Tree t);  ////< transform a tree from deBruijn to symbolic representation

//---------------------------------------------------------------------------

class Tabber {
    int fIndent;
    int fPostInc;

   public:
    Tabber(int n = 0) : fIndent(n), fPostInc(0) {}
    Tabber& operator++()
    {
        fPostInc++;
        return *this;
    }
    Tabber& operator--()
    {
        faustassert(fIndent > 0);
        fIndent--;
        return *this;
    }

    std::ostream& print(std::ostream& fout)
    {
        for (int i = 0; i < fIndent; i++) {
            fout << '\t';
        }
        fIndent += fPostInc;
        fPostInc = 0;
        return fout;
    }
};

// Printing
inline std::ostream& operator<<(std::ostream& s, Tabber& t)
{
    return t.print(s);
}

#endif
