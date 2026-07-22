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
 tree (n)            : tree of node n with no branch
 tree (n, t1)        : tree of node n with a branch t
 tree (n, t1,...,tm) : tree of node n with m branches t1,...,tm

 Pattern matching :

 if (isTree (t, n))           : t has node n and no branches;
 if (isTree (t, n, &t1)       : t has node n and 1 branch, t1 is set accordingly;
 if (isTree (t, n, &t1...&tm) : t has node n and m branches, ti's are set accordingly;

 Accessors :

 t->node()    : the node of t { return fNode; }
 t->arity()   : the number of branches of t { return fArity; }
 t->branch(i) : the ith branch of t

 Attributs :

 t->attribut()   : return the attribute (also a tree) of t
 t->attribut(t') : set the attribute of t to t'

 Warning :
 ---------
 Since reference counters are used for garbage collecting, one must be careful not to
 create cycles in trees. The only possible source of cycles is by setting the attribute
 of a tree t to a tree t' that contains t as a subtree.

 Properties:
 -----------
    If p and q are two CTree pointers :
        p != q <=> *p != *q

 History :
 ---------
    2002-02-08 : First version
    2002-10-14 : counts for height and recursiveness added

******************************************************************************
*****************************************************************************/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "tlib-error.hh"
#include "tree.hh"

using namespace std;

#ifdef WIN32
#pragma warning(disable : 4800)
#endif

#define ERROR(s, t)               \
    {                             \
        stringstream error;       \
        error << s << *t << endl; \
        tlib::error(error.str()); \
    }

Tree*        CTree::gHashTable       = nullptr;
size_t       CTree::gHashTableSize   = 0;
size_t       CTree::gHashTableCount  = 0;
double       CTree::gHashLoadFactor  = 0.7;
bool         CTree::gDetails        = false;
unsigned int CTree::gVisitTime      = 0;
size_t       CTree::gSerialCounter  = 0;

// Smallest prime >= n (trial division; only called on the rare rehash path)
static size_t nextPrimeAtLeast(size_t n)
{
    if (n <= 2) return 2;
    size_t candidate = (n % 2 == 0) ? n + 1 : n;
    for (;;) {
        bool   isPrime = true;
        size_t d       = 3;
        while (d * d <= candidate) {
            if (candidate % d == 0) {
                isPrime = false;
                break;
            }
            d += 2;
        }
        if (isPrime) return candidate;
        candidate += 2;
    }
}

// Lazily allocates the table on first use : unlike the previous fixed-size C array (whose static
// storage duration guaranteed a valid zero-initialized table before any code ran), a
// dynamically-allocated table needs an explicit first allocation. This makes CTree::make() safe
// to call even if something creates a Tree before CTree::init() has run (e.g. from another
// translation unit's static initializer, whose relative order versus init() is unspecified).
// Cheap after the first call (one non-null pointer check), so it's fine to call unconditionally
// on every make(), including lookups that turn out to be cache hits.
void CTree::ensureHashTableAllocated()
{
    if (gHashTable != nullptr) return;
    gHashTableSize = kInitialHashTableSize;
    gHashTable     = new Tree[gHashTableSize];
    memset(gHashTable, 0, sizeof(Tree) * gHashTableSize);
}

// Rehash into a larger table once the load factor (average chain length) would exceed 0.7.
// Existing CTree instances keep their address : only their fNext chaining is rewired, so every
// Tree pointer already held elsewhere in the compiler remains valid across the resize.
//
// Only called right before an insert (see CTree::make), not on every lookup : whether the table
// needs to grow can only change when an entry is actually added, so cache-hit calls to make() --
// the majority, in a compiler that constantly re-references already-built subexpressions -- have
// no reason to pay for this check at all.
//
// Triggers below load factor 1.0 : a growing file otherwise spends much of its compilation with
// the table between 0.5 and 1.0 full, i.e. real average chain length approaching 1 on every
// lookup (hit or miss), not just on insert -- the fixed 400009-bucket table this replaced kept
// load factor near 0 for all but the largest files, so this is a real cost the old table never
// had. 0.7 (the default) was chosen empirically on the Faust compiler examples corpus :
// lower wins more on time but costs real aggregate memory (table memory is cheap per bucket,
// but doubling how many buckets sit unused adds up across a large CTree population) ; 0.7
// keeps nearly all of the time win at roughly neutral memory. Exposed as setHashLoadFactor
// purely to let that trade-off be explored ; it never changes the trees created.
void CTree::growHashTableIfNeeded()
{
    if (double(gHashTableCount) < double(gHashTableSize) * gHashLoadFactor) return;

    size_t newSize  = nextPrimeAtLeast(gHashTableSize * 2);
    Tree*  newTable = new Tree[newSize];
    memset(newTable, 0, sizeof(Tree) * newSize);

    for (size_t i = 0; i < gHashTableSize; i++) {
        Tree t = gHashTable[i];
        while (t) {
            Tree   next = t->fNext;
            size_t j    = t->fHashKey % newSize;
            t->fNext    = newTable[j];
            newTable[j] = t;
            t           = next;
        }
    }

    delete[] gHashTable;
    gHashTable     = newTable;
    gHashTableSize = newSize;
}

// Constructor : add the tree to the hash table
CTree::CTree(size_t hk, const Node& n, const tvec& br)
    : CTree(hk, n, int(br.size()), br.empty() ? nullptr : br.data())
{
}

// Constructor : add the tree to the hash table
CTree::CTree(size_t hk, const Node& n, int ar, const Tree br[])
    : fNode(n),
      fType(0),
      fFastProperty(nullptr),
      fProperties(nullptr),
      fHashKey(hk),
      fSerial(++gSerialCounter),
      fAperture(calcTreeAperture(n, ar, br)),
      fContains(calcTreeContains(n, ar, br)),
      fVisitTime(0),
      fBranch()
{
    if (ar > 0) {
        fBranch.assign(br, br + ar);
    }

    // link in the hash table (CTree::make already called growHashTableIfNeeded)
    size_t j      = hk % gHashTableSize;
    fNext         = gHashTable[j];
    gHashTable[j] = this;
    gHashTableCount++;
}

// Destructor
CTree::~CTree()
{
    /*
     Remove the tree from the hash table is not needed
     since all pointers are either managed using the Garbageable model
     or with CDTree "successive pointers" allocation model.
     */
    delete fProperties;
}

// equivalence
bool CTree::equiv(const Node& n, const tvec& br) const
{
    return (fNode == n) && (fBranch == br);
}

bool CTree::equiv(const Node& n, int ar, const Tree br[]) const
{
    if (fNode != n || fBranch.size() != size_t(ar)) {
        return false;
    }
    for (int i = 0; i < ar; ++i) {
        if (fBranch[i] != br[i]) {
            return false;
        }
    }
    return true;
}

size_t CTree::calcTreeHash(const Node& n, const tvec& br)
{
    return calcTreeHash(n, int(br.size()), br.empty() ? nullptr : br.data());
}

size_t CTree::calcTreeHash(const Node& n, int ar, const Tree br[])
{
    size_t hk = std::hash<void*>()(n.getPointer());
    for (int i = 0; i < ar; ++i) {
        // Taken from by boost::hash_combine
        Tree ptr = br[i];
        hk       = hk ^ (ptr->fHashKey + 0x9e3779b9 + (hk << 6) + (hk >> 2));
    }
    return hk;
}

Tree CTree::make(const Node& n, int ar, const Tree tbl[])
{
    ensureHashTableAllocated();

    size_t hk       = calcTreeHash(n, ar, tbl);
    Tree   t        = gHashTable[hk % gHashTableSize];
    bool   collided = (t != nullptr);  // bucket already occupied, known for free from the lookup

    while (t && !t->equiv(n, ar, tbl)) {
        t = t->fNext;
    }

    if (t) {
        statsTreeReused();
        return t;
    } else {
        statsTreeCreated();
        // Only even consider growing when this insert lands on an already-occupied bucket ; most
        // inserts don't (see TLIB.md), so this skips the load-factor check entirely for them.
        if (collided) {
            growHashTableIfNeeded();
        }
        return new CTree(hk, n, ar, tbl);
    }
}

Tree CTree::make(const Node& n, const tvec& br)
{
    return CTree::make(n, int(br.size()), br.empty() ? nullptr : br.data());
}

ostream& CTree::print(ostream& fout) const
{
    if (gDetails) {
        // print the adresse of the tree
        fout << "<" << this << ">@";
    }
    fout << node();
    int a = arity();
    if (a > 0) {
        int  i;
        char sep;
        for (sep = '[', i = 0; i < a; sep = ',', i++) {
            fout << sep;
            branch(i)->print(fout);
        }
        fout << ']';
    }

    return fout;
}

void CTree::control()
{
    printf("\ngHashTable Content :\n\n");
    for (size_t i = 0; i < gHashTableSize; i++) {
        Tree t = gHashTable[i];
        if (t) {
            printf("%4zu = ", i);
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

void CTree::init()
{
    gSerialCounter  = 0;
    gVisitTime      = 0;
    gDetails        = false;
    gHashTableCount = 0;
    delete[] gHashTable;
    gHashTableSize = kInitialHashTableSize;
    gHashTable     = new Tree[gHashTableSize];
    memset(gHashTable, 0, sizeof(Tree) * gHashTableSize);
}

// if t has a node of type int, return it, or float, return casted to int, otherwise error
TLIB_API int tree2int(Tree t)
{
    double x;
    int    i;

    if (isInt(t->node(), &i)) {
        // nothing to do
    } else if (isDouble(t->node(), &x)) {
        i = int(x);
    } else {
        ERROR("ERROR : the parameter must be an integer constant numerical expression : ", t);
    }
    return i;
}

// if t has a node of type int, return casted to double, or double, return it, otherwise error
TLIB_API double tree2double(Tree t)
{
    double x;
    int    i;

    if (isInt(t->node(), &i)) {
        x = double(i);
    } else if (isDouble(t->node(), &x)) {
        // nothing to do
    } else {
        ERROR("ERROR : the parameter must be a real constant numerical expression : ", t);
    }
    return x;
}

// if t has a node of type symbol, return its name otherwise error
TLIB_API const char* tree2str(Tree t)
{
    Sym s;
    if (!isSym(t->node(), &s)) {
        ERROR("ERROR : the parameter must be a symbol known at compile time : ", t);
    }
    return name(s);
}

string tree2quotedstr(Tree t)
{
    return "\"" + string(tree2str(t)) + "\"";
}

// if t has a node of type ptr, return it otherwise error
void* tree2ptr(Tree t)
{
    void* x;
    if (!isPointer(t->node(), &x)) {
        ERROR("ERROR : the parameter must be a pointer known at compile time : ", t);
    }
    return x;
}

/*
bool isTree (const Tree& t, const Node& n)
{
    return (t->node() == n) && (t->arity() == 0);
}
*/

// If it's not a problem, it's more practical
bool isTree(const Tree& t, const Node& n)
{
    return (t->node() == n);
}

bool isTree(const Tree& t, const Node& n, Tree& a)
{
    if ((t->node() == n) && (t->arity() == 1)) {
        a = t->branch(0);
        return true;
    } else {
        return false;
    }
}

bool isTree(const Tree& t, const Node& n, Tree& a, Tree& b)
{
    if ((t->node() == n) && (t->arity() == 2)) {
        a = t->branch(0);
        b = t->branch(1);
        return true;
    } else {
        return false;
    }
}

bool isTree(const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c)
{
    if ((t->node() == n) && (t->arity() == 3)) {
        a = t->branch(0);
        b = t->branch(1);
        c = t->branch(2);
        return true;
    } else {
        return false;
    }
}

bool isTree(const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c, Tree& d)
{
    if ((t->node() == n) && (t->arity() == 4)) {
        a = t->branch(0);
        b = t->branch(1);
        c = t->branch(2);
        d = t->branch(3);
        return true;
    } else {
        return false;
    }
}

bool isTree(const Tree& t, const Node& n, Tree& a, Tree& b, Tree& c, Tree& d, Tree& e)
{
    if ((t->node() == n) && (t->arity() == 5)) {
        a = t->branch(0);
        b = t->branch(1);
        c = t->branch(2);
        d = t->branch(3);
        e = t->branch(4);
        return true;
    } else {
        return false;
    }
}

// Support for symbol user data
TLIB_API void* getUserData(Tree t)
{
    Sym s;
    if (isSym(t->node(), &s)) {
        return getUserData(s);
    } else {
        return nullptr;
    }
}

/**
 * export the properties of a CTree as two vectors, one for the keys
 * and one for the associated values
 */
void CTree::exportProperties(vector<Tree>& keys, vector<Tree>& values)
{
    if (!fProperties) {
        return;
    }
    for (const auto& it : *fProperties) {
        keys.push_back(it.first);
        values.push_back(it.second);
    }
}
