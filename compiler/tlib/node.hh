/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

/** \file node.hh
 * A Node is a tagged unions of int, double, symbol and void* used in the implementation of CTrees.
 * Nodes are completly described by the node.h file, there is no node.cpp file.
 *
 * <b>API:</b>
 *
 * Node(symbol("abcd")); : node with symbol content
 * Node(10);             : node with int content
 * Node(3.14159);        : node with double content
 *
 * n->type();            : kIntNode or kDoubleNode or kSymNode
 *
 * n->getInt();          : int content of n
 * n->getDouble();       : double content of n
 * n->getSym();          : symbol content of n
 *
 * if (isInt(n, &i))     : int i = int content of n
 * if (isDouble(n, &f))  : double f = double content of n
 * if (isSym(n, &s))     : Sym s = Sym content of n
 *
 */

/******************************************************************************
*****************************************************************************/

#ifndef __NODE__
#define __NODE__

#include <cstdint>
#include <cstring>
#include <stdint.h>
#include <sys/types.h>
#include <cmath>
#include <iostream>

#include <cstdint>
#include <cstring>
#include <sstream>

#include "garbageable.hh"
#include "symbol.hh"
#include "tlib-error.hh"

/**
 * Tags used to define the type of a Node
 */
enum NodeType { kIntNode, kInt64Node, kDoubleNode, kSymNode, kPointerNode };

/**
 * Class Node = (type x (int + double + Sym + void*))
 */

/// The pointer-canonical registry (defined in tree.cpp) : a pointer payload
/// whose NAME was registered at creation (box primitives register through
/// primNname) hashes by that name -- value-derived, identical across builds.
/// Unregistered pointers fall back to the address (never canonical).
TLIB_API void               setPointerCanonicalHash(const void* p, std::size_t h);
TLIB_API const std::size_t* getPointerCanonicalHash(const void* p);
TLIB_API std::size_t        canonicalNameHash(const char* name);

class Node : public Garbageable {
    int fType;
    union {
        int     i;
        double  f;
        Sym     s;
        void*   p;
        int64_t v;
    } fData;

   public:

    /// The payload as an opaque 64-bit word, without reading an inactive union
    /// member : memcpy is the C++17 spelling of bit_cast, and folds to a single
    /// load at -O2. Used by the equality below ; canonicalHash uses the same
    /// idiom for its double case.
    std::uint64_t payload() const
    {
        std::uint64_t w;
        static_assert(sizeof(w) == sizeof(fData), "the payload union must be one 64-bit word");
        memcpy(&w, &fData, sizeof(w));
        return w;
    }

    /// Value-derived hash, identical across processes : symbols hash by NAME ;
    /// registered pointer payloads (box primitives) hash by their registered
    /// name ; unregistered pointers fall back to the address (non-canonical --
    /// they must never enter the canonical orderings, and their ancestors'
    /// canonHash is contaminated : the build-determinism phantom lived there).
    std::size_t canonicalHash() const
    {
        std::size_t h = std::size_t(fType) * 0x9e3779b97f4a7c15ULL;
        switch (fType) {
            case kIntNode: return h ^ std::size_t(fData.i);
            case kInt64Node: return h ^ std::size_t(fData.v);
            case kDoubleNode: {
                std::size_t b;
                static_assert(sizeof(b) == sizeof(fData.f), "size mismatch");
                memcpy(&b, &fData.f, sizeof(b));
                return h ^ b;
            }
            case kSymNode: return h ^ symbolHashKey(fData.s);
            default: {
                if (const std::size_t* r = getPointerCanonicalHash(fData.p)) {
                    return h ^ *r;
                }
                return h ^ std::size_t(reinterpret_cast<std::uintptr_t>(fData.p));
            }
        }
    }
    // constructors (assume size of field f is the biggest)

    ///< There is deliberately NO default constructor, for the same reason CTree has none
    ///< (see tree.hh) : a node IS its content, so a contentless node has no meaning. The
    ///< former default constructor zeroed fData but left fType INDETERMINATE, so comparing
    ///< or hashing a default-built Node was undefined behaviour. Giving it a well-defined
    ///< default instead would be worse in a different way : it would silently read as the
    ///< valid value Node(0). Build a Node from its content, always.
    Node() = delete;

    Node(int x) : fType(kIntNode)
    {
        fData.f = 0.0;
        fData.i = x;
    }

    Node(double x) : fType(kDoubleNode) { fData.f = x; }

    Node(int64_t x) : fType(kInt64Node) { fData.v = x; }

    Node(const char* name) : fType(kSymNode)
    {
        fData.f = 0.0;
        fData.s = symbol(name);
    }

    Node(const std::string& name) : fType(kSymNode)
    {
        fData.f = 0.0;
        fData.s = symbol(name);
    }

    Node(Sym x) : fType(kSymNode)
    {
        fData.f = 0.0;
        fData.s = x;
    }

    Node(void* x) : fType(kPointerNode)
    {
        fData.f = 0.0;
        fData.p = x;
    }

    // predicats

    ///< Equality compares the payload as RAW BITS (through the widest union member),
    ///< never by value. This is not an optimization, hash-consing DEPENDS on it :
    ///< IEEE equality is not reflexive -- a NaN is not equal to itself -- so a table
    ///< built on '==' would never find a NaN node it had just inserted and would
    ///< allocate new ones forever. Bitwise comparison makes node equality a genuine
    ///< equivalence relation. The price, in the other direction : +0.0 and -0.0 have
    ///< different bit patterns and are therefore different nodes. Both consequences
    ///< are pinned by tests in tour-examples.cpp.
    ///< Narrow constructors zero fData.f first so the unused bits are deterministic,
    ///< which is what makes the whole-word comparison exact for every payload type.
    bool operator==(const Node& n) const { return fType == n.fType && payload() == n.payload(); }
    bool operator!=(const Node& n) const { return fType != n.fType || payload() != n.payload(); }

    // accessors
    int type() const { return fType; }

    int     getInt() const { return fData.i; }
    int64_t getInt64() const { return fData.v; }
    double  getDouble() const { return fData.f; }
    Sym     getSym() const { return fData.s; }
    void*   getPointer() const { return fData.p; }

    // conversions and promotion for numbers
    operator int() const
    {
        return (fType == kIntNode) ? fData.i : (fType == kDoubleNode) ? int(fData.f) : 0;
    }
    operator double() const
    {
        return (fType == kIntNode) ? double(fData.i) : (fType == kDoubleNode) ? fData.f : 0.0;
    }

    std::ostream& print(std::ostream& fout) const;  ///< print a node on a stream
};

// printing
inline std::ostream& operator<<(std::ostream& s, const Node& n)
{
    return n.print(s);
}

//-------------------------------------------------------------------------
// Predicates and pattern matching
//-------------------------------------------------------------------------

// integers 32 bits
inline bool isInt(const Node& n)
{
    return (n.type() == kIntNode);
}

inline bool isInt(const Node& n, int* x)
{
    if (n.type() == kIntNode) {
        *x = n.getInt();
        return true;
    } else {
        return false;
    }
}

// integer 64 bits: incomplete implementation but enough to be used in FTZ = 2 mode
inline bool isInt64(const Node& n)
{
    return (n.type() == kInt64Node);
}

inline bool isInt64(const Node& n, int64_t* x)
{
    if (n.type() == kInt64Node) {
        *x = n.getInt64();
        return true;
    } else {
        return false;
    }
}

// floats
inline bool isDouble(const Node& n)
{
    return (n.type() == kDoubleNode);
}

inline bool isDouble(const Node& n, double* x)
{
    if (n.type() == kDoubleNode) {
        *x = n.getDouble();
        return true;
    } else {
        return false;
    }
}

inline bool isZero(const Node& n)
{
    return ((n.type() == kDoubleNode) && (n.getDouble() == 0.0)) ||
           ((n.type() == kIntNode) && (n.getInt() == 0));
}

inline bool isGEZero(const Node& n)
{
    return ((n.type() == kDoubleNode) && (n.getDouble() >= 0.0)) ||
           ((n.type() == kIntNode) && (n.getInt() >= 0));
}

inline bool isGTZero(const Node& n)
{
    return ((n.type() == kDoubleNode) && (n.getDouble() > 0.0)) ||
           ((n.type() == kIntNode) && (n.getInt() > 0));
}

inline bool isOne(const Node& n)
{
    return ((n.type() == kDoubleNode) && (n.getDouble() == 1.0)) ||
           ((n.type() == kIntNode) && (n.getInt() == 1));
}

inline bool isMinusOne(const Node& n)
{
    return ((n.type() == kDoubleNode) && (n.getDouble() == -1.0)) ||
           ((n.type() == kIntNode) && (n.getInt() == -1));
}

inline bool isNegative(const Node& n)
{
    return ((n.type() == kDoubleNode) && (n.getDouble() < 0.0)) ||
           ((n.type() == kIntNode) && (n.getInt() < 0));
}

bool sameMagnitude(const Node& a, const Node& b);

// numbers in general
inline bool isNum(const Node& n)
{
    return isInt(n) || isDouble(n);
}

// symbols
inline bool isSym(const Node& n)
{
    return (n.type() == kSymNode);
}

inline bool isSym(const Node& n, Sym* x)
{
    if (n.type() == kSymNode) {
        *x = n.getSym();
        return true;
    } else {
        return false;
    }
}

// void pointer
inline bool isPointer(const Node& n)
{
    return (n.type() == kPointerNode);
}

inline bool isPointer(const Node& n, void** x)
{
    if (n.type() == kPointerNode) {
        *x = n.getPointer();
        return true;
    } else {
        return false;
    }
}

//-------------------------------------------------------------------------
// Mathematical operations on nodes
//-------------------------------------------------------------------------

// arithmetic operations

inline const Node addNode(const Node& x, const Node& y)
{
    return (isDouble(x) || isDouble(y)) ? Node(double(x) + double(y)) : Node(int(x) + int(y));
}

inline const Node subNode(const Node& x, const Node& y)
{
    return (isDouble(x) || isDouble(y)) ? Node(double(x) - double(y)) : Node(int(x) - int(y));
}

inline const Node mulNode(const Node& x, const Node& y)
{
    return (isDouble(x) || isDouble(y)) ? Node(double(x) * double(y)) : Node(int(x) * int(y));
}

inline const Node divExtendedNode(const Node& x, const Node& y)
{
    if (isZero(y)) {
        std::stringstream error;
        error << "ERROR : division by 0 in " << x << " / " << y << std::endl;
        tlib::error(error.str());
    } else if (isDouble(x) || isDouble(y)) {
        return Node(double(x) / double(y));
    } else {
        int    xi     = int(x);
        int    yi     = int(y);
        int    intDiv = xi / yi;
        double dblDiv = double(xi) / double(yi);
        return (double(intDiv) == dblDiv) ? Node(intDiv) : Node(dblDiv);
    }
}

inline const Node remNode(const Node& x, const Node& y)
{
    if (isZero(y)) {
        std::stringstream error;
        error << "ERROR : % by 0 in " << x << " % " << y << std::endl;
        tlib::error(error.str());
    } else if (isInt(x) && isInt(y)) {
        return Node(int(x) % int(y));
    } else {
        return Node(std::fmod(double(x), double(y)));
    }
}

// inverse functions

inline const Node minusNode(const Node& x)
{
    return subNode(0, x);
}

inline const Node inverseNode(const Node& x)
{
    return divExtendedNode(1.0, x);
}

// bit shifting operations

inline const Node lshNode(const Node& x, const Node& y)
{
    return Node(int(x) << int(y));
}

inline const Node arshNode(const Node& x, const Node& y)
{
    return Node(int(x) >> int(y));
}

inline const Node lrshNode(const Node& x, const Node& y)
{
    return Node(int(x) >> int(y));
}

// boolean operations on bits

inline const Node andNode(const Node& x, const Node& y)
{
    return Node(int(x) & int(y));
}

inline const Node orNode(const Node& x, const Node& y)
{
    return Node(int(x) | int(y));
}

inline const Node xorNode(const Node& x, const Node& y)
{
    return Node(int(x) ^ int(y));
}

// compare operations

inline const Node gtNode(const Node& x, const Node& y)
{
    return (isDouble(x) || isDouble(y)) ? Node(double(x) > double(y)) : Node(int(x) > int(y));
}

inline const Node ltNode(const Node& x, const Node& y)
{
    return (isDouble(x) || isDouble(y)) ? Node(double(x) < double(y)) : Node(int(x) < int(y));
}

inline const Node geNode(const Node& x, const Node& y)
{
    return (isDouble(x) || isDouble(y)) ? Node(double(x) >= double(y)) : Node(int(x) >= int(y));
}

inline const Node leNode(const Node& x, const Node& y)
{
    return (isDouble(x) || isDouble(y)) ? Node(double(x) <= double(y)) : Node(int(x) <= int(y));
}
#if 1
inline const Node eqNode(const Node& x, const Node& y)
{
    return (isDouble(x) || isDouble(y)) ? Node(double(x) == double(y)) : Node(int(x) == int(y));
}

inline const Node neNode(const Node& x, const Node& y)
{
    return (isDouble(x) || isDouble(y)) ? Node(double(x) != double(y)) : Node(int(x) != int(y));
}
#endif

#endif
