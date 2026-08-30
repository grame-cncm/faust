/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#ifndef __XTENDED_CODEGEN__
#define __XTENDED_CODEGEN__

#include <sstream>
#include <string>
#include <vector>

#include "exception.hh"
#include "floats.hh"
#include "instructions.hh"
#include "klass.hh"
#include "lateq.hh"
#include "ppsig.hh"
#include "xtended.hh"

class CodeContainer;

/*
 Code generation layer of the math primitives: the concrete primitives of the
 compiler (extended/*prim.hh) derive from this class, which extends the
 signal-level interface xtended (signals/xtended.hh) with the code generation
 methods of the FIR, old CPP and documentation backends.
 */

class xtendedCodegen : public xtended {
   public:
    using xtended::xtended;

    virtual std::string fname(int type) { return sname() + isuffix(); }

    // FIR backends
    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type rtype,
                                    ConstTypes types) = 0;
    // Old CPP backend
    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) = 0;

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args,
                                      const std::vector< ::Type>& types) = 0;

    ValueInst* generateFun(CodeContainer* container, const std::string& fun_name,
                           const Values& args, ::Type rtype, ConstTypes types);
};

// Casting operations
inline ValueInst* promote2real(int type, ValueInst* val)
{
    return (type == kReal) ? val : IB::genCastRealInst(val);
}
inline ValueInst* promote2int(int type, ValueInst* val)
{
    return (type == kInt) ? val : IB::genCastInt32Inst(val);
}

inline ValueInst* cast2real(int type, ValueInst* val)
{
    return (type == kReal) ? IB::genCastRealInst(val) : val;
}
inline ValueInst* cast2int(int type, ValueInst* val)
{
    return (type == kInt) ? IB::genCastInt32Inst(val) : val;
}

#endif
