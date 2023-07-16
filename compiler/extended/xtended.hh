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

#include <vector>
#include <sstream>

#include "garbageable.hh"
#include "instructions.hh"
#include "klass.hh"
#include "lateq.hh"
#include "ppsig.hh"
#include "sigtype.hh"
#include "tlib.hh"

class CodeContainer;

/*
 Base class for math primitives:
 - most of them have same args and result type, except 'pow' which can have different value and exponent types
 - max/min, abs/fabs have polymorphic kInt/kReal versions
 - some of them have optimized versions for specific arguments (like 'pow') or with gMathApprox (experimental)
 */

class xtended : public virtual Garbageable {
   private:
    Symbol* fSymbol;  ///< the symbol the xtended is attached to

   public:
    xtended(const char* name) : fSymbol(::symbol(name)) { setUserData(fSymbol, (void*)this); }
    virtual ~xtended() {}

    Sym         symbol() { return fSymbol; }
    const char* name() { return ::name(fSymbol); }

    // Create the box
    Tree box()
    {
        Tree b = tree(fSymbol);
        faustassert(getUserData(b) != nullptr);
        return b;
    }

    // virtual method to be implemented by subclasses
    virtual unsigned int arity() = 0;

    // FIR backends
    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type rtype, ConstTypes types) = 0;
    // Old CPP backend
    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types) = 0;

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, const std::vector< ::Type>& types) = 0;
    virtual int    infereSigOrder(const std::vector<int>& args)                                           = 0;
    virtual ::Type infereSigType(ConstTypes args)                                                        = 0;
    virtual Tree   computeSigOutput(const std::vector<Tree>& args)                                        = 0;
    virtual bool   needCache()                                                                           = 0;

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

    ValueInst* generateFun(CodeContainer* container, const std::string& fun_name, const Values& args, ::Type rtype,
                           ConstTypes types);
};

// True if two floating point numbers are close enough to be considered identical.
// It is used to recognize PI/n and 0 in some symbolic simplifications.
inline bool comparable(double x, double y)
{
    return fabs(x - y) < 0.00001;
}

// Casting operations
inline ValueInst* promote2real(int type, ValueInst* val)
{
    return (type == kReal) ? val : InstBuilder::genCastRealInst(val);
}
inline ValueInst* promote2int(int type, ValueInst* val)
{
    return (type == kInt) ? val : InstBuilder::genCastInt32Inst(val);
}

inline ValueInst* cast2real(int type, ValueInst* val)
{
    return (type == kReal) ? InstBuilder::genCastRealInst(val) : val;
}
inline ValueInst* cast2int(int type, ValueInst* val)
{
    return (type == kInt) ? InstBuilder::genCastInt32Inst(val) : val;
}

#endif
