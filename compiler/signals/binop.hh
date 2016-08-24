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

#ifndef _BINOP_
#define _BINOP_

#include "node.hh"
#include "fir_opcode.hh"

typedef const Node	(*comp) (const Node& a, const Node& b);
typedef bool 		(*pred) (const Node& a);

bool falsePredicate(Node const & a);

// Use in in static table so not Garbageable
struct BinOp {

    const char* fName;
    const char* fNameVec;
    const char* fNameScal;
    const char* fNameLLVMInt;
    const char* fNameLLVMFloat;
  
    unsigned int fLLVMIntInst;
    unsigned int fLLVMFloatInst;

    const char* fNameWasmInt;
    const char* fNameWasmFloat;
    const char* fNameWasmDouble;

    FIRInstruction::Opcode fInterpIntInst;
    FIRInstruction::Opcode fInterpFloatInst;

    comp fCompute;
    pred fLeftNeutral;
    pred fRightNeutral;
    pred fLeftAbsorbing;
    pred fRightAbsorbing;
    int fPriority;
	
    BinOp(const char* name, const char* name_vec,
            const char* name_scal,
            const char* name_llvm_int,
            const char* name_llvm_float,
            unsigned int llvm_int,
            unsigned int llvm_float,
            const char* name_wasm_int,
            const char* name_wasm_float,
            const char* name_wasm_double,
            FIRInstruction::Opcode interp_int,
            FIRInstruction::Opcode interp_float,
            comp f,
            pred ln,
            pred rn,
            int priority,
            pred la = falsePredicate,
            pred ra = falsePredicate)
            :fName(name), fNameVec(name_vec), fNameScal(name_scal),
            fNameLLVMInt(name_llvm_int), fNameLLVMFloat(name_llvm_float),
            fLLVMIntInst(llvm_int), fLLVMFloatInst(llvm_float),
            fNameWasmInt(name_wasm_int), fNameWasmFloat(name_wasm_float), fNameWasmDouble(name_wasm_double),
            fInterpIntInst(interp_int), fInterpFloatInst(interp_float),
            fCompute(f), fLeftNeutral(ln), fRightNeutral(rn),
            fLeftAbsorbing(la), fRightAbsorbing(ra), fPriority(priority)
    {}

    Node compute(const Node& a, const Node& b) { return fCompute(a,b); 	}

    bool isRightNeutral(const Node& a)      { return fRightNeutral(a); 	    }
    bool isLeftNeutral(const Node& a)       { return fLeftNeutral(a); 	    }
    bool isLeftAbsorbing(const Node& a)     { return fLeftAbsorbing(a);     }
    bool isRightAbsorbing(const Node& a)    { return fRightAbsorbing(a);    }
};

extern BinOp* gBinOpTable[];
extern BinOp* gBinOpLateqTable[];

enum {
	kAdd, kSub, kMul, kDiv, kRem,
	kLsh, kRsh,
	kGT, kLT, kGE, kLE, kEQ, kNE,
	kAND, kOR, kXOR
};

bool isBoolOpcode(int o);
bool isLogicalOpcode(int o);
bool isCommutativeOpcode(int o);

#endif
