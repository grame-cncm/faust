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

#ifndef __XTENDED__
#define __XTENDED__

#include <cmath>
#include <string>
#include <vector>

#include "garbageable.hh"
#include "sigtype.hh"
#include "tlib.hh"

/*
 Base class for math primitives, signal-level interface: identity (symbol,
 box), arity, type and order inference, symbolic computation. The code
 generation layer of these primitives lives in the compiler, in the derived
 class xtendedCodegen (extended/xtendedCodegen.hh).
 - most of them have same args and result type, except 'pow' which can have different value and
 exponent types
 - max/min, abs/fabs have polymorphic kInt/kReal versions
 - some of them have optimized versions for specific arguments (like 'pow') or with gMathApprox
 (experimental)
 */

class xtended : public virtual Garbageable {
   private:
    Sym fSymbol;  ///< the symbol the xtended is attached to

   public:
    xtended(const char* name) : fSymbol(::symbol(name)) { setUserData(fSymbol, (void*)this); }
    virtual ~xtended() {}

    Sym         symbol() { return fSymbol; }
    const char* name() { return ::name(fSymbol); }
    std::string sname() { return std::string(::name(fSymbol)); }

    // Create the box
    Tree box()
    {
        Tree b = tree(fSymbol);
        TLIB_ASSERT(getUserData(b) != nullptr);
        return b;
    }

    // virtual method to be implemented by subclasses
    virtual unsigned int arity() = 0;

    virtual int    inferSigOrder(const std::vector<int>& args)     = 0;
    virtual ::Type inferSigType(ConstTypes args)                   = 0;
    virtual Tree   computeSigOutput(const std::vector<Tree>& args) = 0;
    virtual bool   needCache()                                     = 0;

    virtual double compute(const std::vector<Node>& args) { return -1.; };

    // Compute the derivative of a primitive with respect to its arguments.
    virtual Tree diff(const std::vector<Tree>& args)
    {
        // TODO: implement `diff` for all `xtended` implementations.
        return nullptr;
    }

    virtual bool isSpecialInfix()
    {
        return false;
    }  ///< generally false, but true for binary op # such that #(x) == _#x
};

// True if two floating point numbers are close enough to be considered identical.
// It is used to recognize PI/n and 0 in some symbolic simplifications.
inline bool comparable(double x, double y)
{
    return fabs(x - y) < 0.00001;
}

#endif
