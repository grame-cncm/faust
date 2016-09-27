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

/** \file node.hh
 * A Node is a tagged unions of int, double, symbol and void* used in the implementation of CTrees.
 * Nodes are completly described by the node.h file, there is no node.cpp file.
 *
 * <b>API:</b>
 *
 * 	Node(symbol("abcd")); 	: node with symbol content
 * 	Node(10);				: node with int content
 * 	Node(3.14159);			: node with double content
 *
 * 	n->type();				: kIntNode or kDoubleNode or kSymNode
 *
 * 	n->getInt();			: int content of n
 * 	n->getDouble();			: double content of n
 * 	n->getSym();			: symbol content of n
 *
 * 	if (isInt(n, &i))	... : int i = int content of n
 * 	if (isDouble(n, &f))	... : double f = double content of n
 * 	if (isSym(n, &s))	... : Sym s = Sym content of n
 *
 */

/******************************************************************************
*****************************************************************************/

#ifndef     __NODE__
#define     __NODE__

#include <iostream>
#include "symbol.hh"
#include "garbageable.hh"
#include <sys/types.h>
#include <stdint.h>

using namespace std;

/**
 * Tags used to define the type of a Node
 */
enum { kIntNode, kDoubleNode, kSymNode, kPointerNode };

/**
 * Class Node = (type x (int + double + Sym + void*))
 */
 
class Node : public virtual Garbageable
{
	int		fType;
	union {
		int 	i;
		double 	f;
		Sym 	s;
		void* 	p;
        int64_t v;
	} fData;

 public:
	// constructeurs (assume size of field f is the biggest)
    Node () { fData.v = 0; }
	Node (int x) 				: fType(kIntNode) 		{ fData.f = 0; fData.i = x; }
	Node (double x) 			: fType(kDoubleNode) 	{ fData.f = x; }
	Node (const char* name)		: fType(kSymNode) 		{ fData.f = 0; fData.s = symbol(name); }
	Node (const string& name)	: fType(kSymNode) 		{ fData.f = 0; fData.s = symbol(name); }
	Node (Sym x) 				: fType(kSymNode) 		{ fData.f = 0; fData.s = x; }
	Node (void* x) 				: fType(kPointerNode) 	{ fData.f = 0; fData.p = x; }

    Node (const Node& n)        : fType(n.fType)        { fData = n.fData; }

	// predicats
	bool operator == (const Node& n) const { return fType == n.fType && fData.v == n.fData.v; }
	bool operator != (const Node& n) const { return fType != n.fType || fData.v != n.fData.v; }

	// accessors
	int		type() 		const 	{ return fType; }

	int		getInt() 		const 	{ return fData.i; }
	double 	getDouble() 	const 	{ return fData.f; }
	Sym 	getSym() 		const 	{ return fData.s; }
	void* 	getPointer() 	const 	{ return fData.p; }

	// conversions and promotion for numbers
	operator int() 	 const 	    { return (fType == kIntNode) ? fData.i : (fType == kDoubleNode) ? int(fData.f) : 0 ; }
    operator double() const     { return (fType == kIntNode) ? double(fData.i) : (fType == kDoubleNode) ? fData.f : 0.0 ; }

	ostream& 	print (ostream& fout) const; 					///< print a node on a stream
};

//printing
inline ostream& operator << (ostream& s, const Node& n) { return n.print(s); }

//-------------------------------------------------------------------------
// Perdicates and pattern matching
//-------------------------------------------------------------------------

// integers
inline bool isInt (const Node& n)
{
	return (n.type() == kIntNode);
}

inline bool isInt (const Node& n, int* x)
{
	if (n.type() == kIntNode) {
		*x = n.getInt();
		return true;
	} else {
		return false;
	}
}

// floats
inline bool isDouble (const Node& n)
{
	return (n.type() == kDoubleNode);
}

inline bool isDouble (const Node& n, double* x)
{
	if (n.type() == kDoubleNode) {
		*x = n.getDouble();
		return true;
	} else {
		return false;
	}
}

inline bool isZero (const Node& n)
{
	return ((n.type() == kDoubleNode) && (n.getDouble() == 0.0))
		|| ((n.type() == kIntNode) && (n.getInt() == 0));
}

inline bool isGEZero (const Node& n)
{
	return ((n.type() == kDoubleNode) && (n.getDouble() >= 0.0))
		|| ((n.type() == kIntNode) && (n.getInt() >= 0));
}

inline bool isGTZero (const Node& n)
{
	return ((n.type() == kDoubleNode) && (n.getDouble() > 0.0))
		|| ((n.type() == kIntNode) && (n.getInt() > 0));
}

inline bool isOne (const Node& n)
{
	return ((n.type() == kDoubleNode) && (n.getDouble() == 1.0))
		|| ((n.type() == kIntNode) && (n.getInt() == 1));
}

inline bool isMinusOne (const Node& n)
{
	return ((n.type() == kDoubleNode) && (n.getDouble() == -1.0))
		|| ((n.type() == kIntNode) && (n.getInt() == -1));
}

bool sameMagnitude(const Node& a, const Node& b);

// numbers in general
inline bool isNum (const Node& n)
{
	return isInt(n)||isDouble(n);
}

// symbols
inline bool isSym (const Node& n)
{
	return (n.type() == kSymNode);
}

inline bool isSym (const Node& n, Sym* x)
{
	if (n.type() == kSymNode) {
		*x = n.getSym();
		return true;
	} else {
		return false;
	}
}

// void pointer
inline bool isPointer (const Node& n)
{
	return (n.type() == kPointerNode);
}

inline bool isPointer (const Node& n, void** x)
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

inline const Node addNode (const Node& x, const Node& y)
	{ return (isDouble(x)||isDouble(y)) ? Node(double(x)+double(y)) : Node(int(x)+int(y)); }

inline const Node subNode (const Node& x, const Node& y)
	{ return (isDouble(x)||isDouble(y)) ? Node(double(x)-double(y)) : Node(int(x)-int(y)); }

inline const Node mulNode (const Node& x, const Node& y)
	{ return (isDouble(x)||isDouble(y)) ? Node(double(x)*double(y)) : Node(int(x)*int(y)); }

inline const Node divExtendedNode (const Node& x, const Node& y)
	{ return (isDouble(x)||isDouble(y)) ? Node(double(x)/double(y))
			: (double(int(x)/int(y))==double(x)/double(y)) ? Node(int(x)/int(y))
			: Node(double(x)/double(y)); }

inline const Node remNode (const Node& x, const Node& y)
	{ return Node(int(x)%int(y)); }

// inverse functions

inline const Node minusNode (const Node& x)
	{ return subNode(0, x); }

inline const Node inverseNode (const Node& x)
    { return divExtendedNode(1.0f, x); }

// bit shifting operations

inline const Node lshNode (const Node& x, const Node& y)
	{ return Node(int(x)<<int(y)); }

inline const Node rshNode (const Node& x, const Node& y)
	{ return Node(int(x)>>int(y)); }

// boolean operations on bits

inline const Node andNode (const Node& x, const Node& y)
	{ return Node(int(x)&int(y)); }

inline const Node orNode (const Node& x, const Node& y)
	{ return Node(int(x)|int(y)); }

inline const Node xorNode (const Node& x, const Node& y)
	{ return Node(int(x)^int(y)); }

// compare operations

inline const Node gtNode (const Node& x, const Node& y)
	{ return (isDouble(x)||isDouble(y)) ? Node(double(x)>double(y)) : Node(int(x)>int(y)); }

inline const Node ltNode (const Node& x, const Node& y)
	{ return (isDouble(x)||isDouble(y)) ? Node(double(x)<double(y)) : Node(int(x)<int(y)); }

inline const Node geNode (const Node& x, const Node& y)
	{ return (isDouble(x)||isDouble(y)) ? Node(double(x)>=double(y)) : Node(int(x)>=int(y)); }

inline const Node leNode (const Node& x, const Node& y)
	{ return (isDouble(x)||isDouble(y)) ? Node(double(x)<=double(y)) : Node(int(x)<=int(y)); }
#if 1
inline const Node eqNode (const Node& x, const Node& y)
	{ return (isDouble(x)||isDouble(y)) ? Node(double(x)==double(y)) : Node(int(x)==int(y)); }

inline const Node neNode (const Node& x, const Node& y)
	{ return (isDouble(x)||isDouble(y)) ? Node(double(x)!=double(y)) : Node(int(x)!=int(y)); }
#endif

#endif
