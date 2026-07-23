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

#include <cstddef>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "export.hh"
#include "garbageable.hh"
#include "node.hh"
#include "symbol.hh"
#include "tlib-error.hh"

// Stats hooks are no-ops unless FIR_BUILD is enabled.
#ifdef FIR_BUILD
void statsTreeCreated();
void statsTreeReused();
void statsPropertySet();
void statsPropertyGet();
#else
inline void statsTreeCreated()
{
}
inline void statsTreeReused()
{
}
inline void statsPropertySet()
{
}
inline void statsPropertyGet()
{
}
#endif

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

}  // namespace std

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

class TLIB_API CTree : public Garbageable {
   protected:
    static const std::size_t kInitialHashTableSize = 1009;  ///< initial size of the hash table (prime);
                                                             ///< grows as needed, see growHashTableIfNeeded
    static std::size_t   gSerialCounter;   ///< the serial number counter
    static double        gHashLoadFactor; ///< load factor triggering table growth
    static std::size_t   gHashTableSize;   ///< current size of the hash table (grows as needed)
    static std::size_t   gHashTableCount;  ///< number of trees currently stored in the table
    static Tree*         gHashTable;       ///< hash table used for "hash consing" (grows by rehashing)

    ///< cheap check, called on every make() : lazily allocates the table on first use (needed
    ///< even for a lookup, not just an insert -- see the comment on the definition)
    static void ensureHashTableAllocated();
    ///< called only right before inserting a new tree ; rehash into a larger table once the load
    ///< factor is too high. Not called on a lookup that finds an existing tree, so the many
    ///< cache-hit calls to make() don't pay for a load-factor check that can't change outcome.
    static void growHashTableIfNeeded();

   public:
    static bool gDetails;  ///< CTree::print() print with more details when true
    ///< Should be incremented for each new visit to keep track of visited tree
    static unsigned int gVisitTime;

    // Property list type. Measured on the examples/*.dsp corpus, ~72% of CTree never get a
    // single property, so the map is allocated lazily (nullptr = none) instead of being an
    // always-present inline member. A plain linear-scan buffer was tried first, but at least one
    // real file has a single node carrying tens of thousands of properties (apparently from a
    // memoization keyed by a fresh Tree per call, e.g. substitute()/liftn()) : with a flat buffer
    // that node's O(n) lookup made the whole compile quadratic. std::map keeps every node bounded
    // at O(log n) regardless of how many properties it accumulates. See TLIB.md for the numbers.
    typedef std::map<Tree, Tree> plist;

   protected:
    // fields
    Tree         fNext;         ///< next tree in the same hashtable entry
    Node         fNode;         ///< the node content of the tree
    void*        fType;         ///< the type of a tree
    Tree         fFastProperty; ///< generic single-slot fast path for one caller-chosen "hot"
                                 ///< property, bypassing fProperties entirely (see setFastProperty)
    plist*       fProperties;   ///< lazily allocated; nullptr means no property set
    std::size_t  fHashKey;      ///< the hashtable key
    std::size_t  fSerial;       ///< the increasing serial number
    // fAperture and fContains share one 32-bit word : a deBruijn depth never comes close to
    // 24 bits, which buys 8 synthesized flag bits for free (sizeof(CTree) stays 112).
    // fAperture stays SIGNED : calcTreeAperture returns br[0]->fAperture - 1 on a rec node,
    // which can be negative.
    int          fAperture : 24;  ///< how "open" is a tree (synthesized field)
    unsigned int fContains : 8;   ///< kinds of constructs occurring here or below (synthesized)
    unsigned int fVisitTime;      ///< keep track of visits
    tvec         fBranch;         ///< the subtrees

    ///< construction is private, uses tree::make instead.
    ///< There is deliberately NO default constructor : every CTree must go through a
    ///< constructor that computes fContains. A zero-initialized fContains would read as
    ///< "contains nothing", i.e. the optimistic value, and a fold would then wrongly skip
    ///< fixpoint iteration on a recursive subtree.
    CTree(std::size_t hk, const Node& n, const tvec& br);
    CTree(std::size_t hk, const Node& n, int ar, const Tree br[]);

    ///< used to check if an equivalent tree already exists
    bool equiv(const Node& n, const tvec& br) const;
    bool equiv(const Node& n, int ar, const Tree br[]) const;

    static std::size_t calcTreeHash(
        const Node& n,
        const tvec& br);  ///< compute the hash key of a tree according to its node and branches
    static std::size_t calcTreeHash(const Node& n, int ar, const Tree br[]);
    static int calcTreeAperture(const Node& n, const tvec& br);  ///< compute how open is a tree
    static int calcTreeAperture(const Node& n, int ar, const Tree br[]);
    ///< compute the kinds occurring in a tree. Defined in recursive-tree.cpp, next to
    ///< calcTreeAperture, because that is where the recursive node symbols live.
    static unsigned int calcTreeContains(const Node& n, const tvec& br);
    static unsigned int calcTreeContains(const Node& n, int ar, const Tree br[]);

   public:
    virtual ~CTree();

    // Synthesized set of construct kinds occurring in a tree (itself included).
    //
    // CONVENTION : each bit means "this kind occurs here or below", and bits combine by
    // UNION over the branches :
    //
    //     kinds(t) = {kind(t)} U (U_i kinds(branch_i))
    //
    // so a single word-wide |= folds every present and future bit at once, a leaf is
    // naturally 0 (contains nothing), and adding a bit costs no change to the combining
    // loop -- only a new rule in calcTreeContains. Do NOT mix in a bit with the opposite
    // ("free of X") polarity : the uniform rule is worth more than per-bit optimality.
    // Accessors may of course read either way (see isRecFree below).
    //
    // These 8 bits are tlib-level : a bit's rule must be decidable from the node alone,
    // inside recursive-tree.cpp. A consumer-level notion (a Faust table, a clock node...)
    // would need a registered hook, which does not exist today.
    enum : unsigned int {
        kContainsRec = 1u << 0,  ///< a recursive node (SYMREC, DEBRUIJN or DEBRUIJNREF) occurs
    };

    static Tree make(const Node& n, int ar,
                     const Tree br[]);  ///< return a new tree or an existing equivalent one
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
    std::size_t hashkey() const { return fHashKey; }  ///< return the hashkey of the tree
    std::size_t serial() const { return fSerial; }    ///< return the serial of the tree
    int         aperture() const
    {
        return fAperture;
    }  ///< return how "open" is a tree in terms of free variables
    void setAperture(int a) { fAperture = a; }  ///< modify the aperture of a tree

    unsigned int contains() const { return fContains; }  ///< the raw set of kinds

    ///< true iff a recursive node occurs in this tree
    bool containsRec() const { return (fContains & kContainsRec) != 0; }

    ///< true iff NO recursive node occurs in this tree, in either notation (symbolic or
    ///< deBruijn). Such a tree is its own sym2deBruijn image, and -- the reason this is
    ///< worth a synthesized bit -- a bottom-up fold over it reaches its final value in one
    ///< pass : it can never change during a fixpoint iteration.
    bool isRecFree() const { return (fContains & kContainsRec) == 0; }

    // Print a tree and the hash table (for debugging purposes)
    std::ostream& print(
        std::ostream& fout) const;  ///< print recursively the content of a tree on a stream
    static void control();          ///< print the hash table content (for debug purpose)

    ///< Test/debug : recompute the synthesized kind bits of EVERY live tree by an
    ///< independent traversal and compare them with the value stored at construction.
    ///< Returns the number of mismatches (0 when the synthesized attribute is sound).
    static std::size_t checkContainsInvariant();

    static void init();

    ///< Set the load factor that triggers hash table growth (default 0.7).
    ///< A pure performance knob : it never changes the trees created.
    static void setHashLoadFactor(double f) { gHashLoadFactor = f; }

    // type information
    void  setType(void* t) { fType = t; }
    void* getType() { return fType; }

    // Generic fast-path slot for one caller-chosen property : one dedicated field instead of a
    // map entry, for a property so widely used that the map overhead isn't worth paying. Only one
    // caller should claim this (currently compiler/propagate/propagate.cpp's PropagateProperty,
    // ~20% of all property traffic measured on examples/*.dsp) : it is not namespaced by key like
    // setProperty/getProperty, so two unrelated callers using it on the same trees would collide.
    void setFastProperty(Tree value) { fFastProperty = value; }
    Tree getFastProperty() { return fFastProperty; }

    // Keep track of visited trees (WARNING : non reentrant)
    static void startNewVisit() { ++gVisitTime; }
    bool        isAlreadyVisited() { return fVisitTime == gVisitTime; }
    void        setVisited() { fVisitTime = gVisitTime; }

    // Property list of a tree
    void setProperty(Tree key, Tree value)
    {
        statsPropertySet();
        if (!fProperties) {
            fProperties = new plist();
        }
        (*fProperties)[key] = value;
    }
    void clearProperty(Tree key)
    {
        if (fProperties) {
            fProperties->erase(key);
        }
    }
    void clearProperties()
    {
        delete fProperties;
        fProperties = nullptr;
    }

    void exportProperties(std::vector<Tree>& keys, std::vector<Tree>& values);

    Tree getProperty(Tree key)
    {
        statsPropertyGet();
        if (!fProperties) {
            return nullptr;
        }
        plist::iterator i = fProperties->find(key);
        return (i == fProperties->end()) ? nullptr : i->second;
    }
};

// The comparison function relies on lhs->serial() which provides an unique and stable ordering
// for all CTree instances and so maintain determinism.
namespace std {
inline bool less<CTree*>::operator()(const CTree* lhs, const CTree* rhs) const
{
    return lhs->serial() < rhs->serial();
}
};  // namespace std

//---------------------------------API---------------------------------------
// To build trees

inline Tree tree(const Node& n)
{
    return CTree::make(n, 0, nullptr);
}

inline Tree tree(const Node& n, const Tree& a)
{
    Tree br[] = {a};
    return CTree::make(n, 1, br);
}

inline Tree tree(const Node& n, const Tree& a, const Tree& b)
{
    Tree br[] = {a, b};
    return CTree::make(n, 2, br);
}

inline Tree tree(const Node& n, const Tree& a, const Tree& b, const Tree& c)
{
    Tree br[] = {a, b, c};
    return CTree::make(n, 3, br);
}

inline Tree tree(const Node& n, const Tree& a, const Tree& b, const Tree& c, const Tree& d)
{
    Tree br[] = {a, b, c, d};
    return CTree::make(n, 4, br);
}

inline Tree tree(const Node& n, const Tree& a, const Tree& b, const Tree& c, const Tree& d,
                 const Tree& e)
{
    Tree br[] = {a, b, c, d, e};
    return CTree::make(n, 5, br);
}

inline Tree tree(const Node& n, const tvec& br)
{
    return CTree::make(n, br);
}

// Useful conversions
TLIB_API int    tree2int(Tree t);  ///< if t has a node of type int, return it otherwise error
TLIB_API double tree2double(
    Tree t);  ///< if t has a node of type double, return it otherwise error
TLIB_API const char* tree2str(
    Tree t);  ///< if t has a node of type symbol, return its name otherwise error
std::string        tree2quotedstr(Tree t);
void*              tree2ptr(Tree t);  ///< if t has a node of type ptr, return it otherwise error
TLIB_API void* getUserData(
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
TLIB_API bool isRec(Tree t, Tree& id, Tree& body);  ///< is t a symbolic recursive tree

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
Tree deBruijn2SymCached(Tree t);  ////< deBruijn2Sym with a persistent tree-property cache
Tree sym2deBruijn(Tree t);  ////< transform a tree from symbolic to deBruijn representation
bool isSym2deBruijnInvariant(Tree t);  ////< true iff sym2deBruijn(t) == t. Now a corollary
                                       ////< of the synthesized kContainsRec bit : see
                                       ////< CTree::isRecFree(), which is what to call in
                                       ////< new code -- this name only records the theorem
bool areEquiv(Tree a, Tree b);  ////< alpha-equivalence of recursive trees

// The recursion structure of a symbolic term : every symbolic recursive node reachable
// from a root, partitioned into strongly connected components (the mutual-recursion
// groups) via DirectedGraph's Tarjan. It is V-independent -- it depends on the tree
// alone -- so it is computed ONCE and shared, read-only, by every attribute computation
// over that term (sym2deBruijn today, the generic fixpoint iterator to come : see
// FIXPOINT-SPEC). Only the partition is exposed for now ; the reverse-topological order
// it will also carry lands with the iterator that first consumes it.
class TLIB_API RecPlan {
   public:
    explicit RecPlan(Tree root);

    ///< component id of a symbolic recursive node, or -1 if it is not one of the
    ///< recursive nodes reachable from root. Two nodes share a component iff their ids
    ///< are equal ; the numbering itself carries no meaning.
    int sccOf(Tree recNode) const;

   private:
    std::unordered_map<Tree, int> fSccOf;
};
std::ostream& printDeBruijn(std::ostream& out, Tree t);
std::ostream& printSymbolic(std::ostream& out, Tree t);
std::string   toDeBruijnString(Tree t);
std::string   toSymbolicString(Tree t);

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
        TLIB_ASSERT(fIndent > 0);
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
