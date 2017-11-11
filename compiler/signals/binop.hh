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

enum WasmOp {
    
    I32EqZ = 0x45,
    I32Eq = 0x46,
    I32Ne = 0x47,
    I32LtS = 0x48,
    I32LtU = 0x49,
    I32GtS = 0x4a,
    I32GtU = 0x4b,
    I32LeS = 0x4c,
    I32LeU = 0x4d,
    I32GeS = 0x4e,
    I32GeU = 0x4f,
    I64EqZ = 0x50,
    I64Eq = 0x51,
    I64Ne = 0x52,
    I64LtS = 0x53,
    I64LtU = 0x54,
    I64GtS = 0x55,
    I64GtU = 0x56,
    I64LeS = 0x57,
    I64LeU = 0x58,
    I64GeS = 0x59,
    I64GeU = 0x5a,
    F32Eq = 0x5b,
    F32Ne = 0x5c,
    F32Lt = 0x5d,
    F32Gt = 0x5e,
    F32Le = 0x5f,
    F32Ge = 0x60,
    F64Eq = 0x61,
    F64Ne = 0x62,
    F64Lt = 0x63,
    F64Gt = 0x64,
    F64Le = 0x65,
    F64Ge = 0x66,
    
    I32Clz = 0x67,
    I32Ctz = 0x68,
    I32Popcnt = 0x69,
    I32Add = 0x6a,
    I32Sub = 0x6b,
    I32Mul = 0x6c,
    I32DivS = 0x6d,
    I32DivU = 0x6e,
    I32RemS = 0x6f,
    I32RemU = 0x70,
    I32And = 0x71,
    I32Or = 0x72,
    I32Xor = 0x73,
    I32Shl = 0x74,
    I32ShrS = 0x75,
    I32ShrU = 0x76,
    I32RotL = 0x77,
    I32RotR = 0x78,
    
    I64Clz = 0x79,
    I64Ctz = 0x7a,
    I64Popcnt = 0x7b,
    I64Add = 0x7c,
    I64Sub = 0x7d,
    I64Mul = 0x7e,
    I64DivS = 0x7f,
    I64DivU = 0x80,
    I64RemS = 0x81,
    I64RemU = 0x82,
    I64And = 0x83,
    I64Or = 0x84,
    I64Xor = 0x85,
    I64Shl = 0x86,
    I64ShrS = 0x87,
    I64ShrU = 0x88,
    I64RotL = 0x89,
    I64RotR = 0x8a,
    
    F32Abs = 0x8b,
    F32Neg = 0x8c,
    F32Ceil = 0x8d,
    F32Floor = 0x8e,
    F32Trunc = 0x8f,
    F32NearestInt = 0x90,
    F32Sqrt = 0x91,
    F32Add = 0x92,
    F32Sub = 0x93,
    F32Mul = 0x94,
    F32Div = 0x95,
    F32Min = 0x96,
    F32Max = 0x97,
    F32CopySign = 0x98,
    
    F64Abs = 0x99,
    F64Neg = 0x9a,
    F64Ceil = 0x9b,
    F64Floor = 0x9c,
    F64Trunc = 0x9d,
    F64NearestInt = 0x9e,
    F64Sqrt = 0x9f,
    F64Add = 0xa0,
    F64Sub = 0xa1,
    F64Mul = 0xa2,
    F64Div = 0xa3,
    F64Min = 0xa4,
    F64Max = 0xa5,
    F64CopySign = 0xa6,
    
    Dummy = 0x00
    
};

// Use in in static table so not Garbageable
struct BinOp {

    const char* fName;
    const char* fNameVec;
    const char* fNameScal;
    const char* fNameLLVMInt;
    const char* fNameLLVMFloat;
  
    unsigned int fLLVMIntInst;
    unsigned int fLLVMFloatInst;

    const char* fNameWastInt32;
    const char* fNameWastInt64;
    const char* fNameWastFloat;
    const char* fNameWastDouble;
    
    WasmOp fWasmInt32;
    WasmOp fWasmInt64;
    WasmOp fWasmFloat;
    WasmOp fWasmDouble;
 
    FIRInstruction::Opcode fInterpIntInst32;
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
            const char* name_wasm_int32,
            const char* name_wasm_int64,
            const char* name_wasm_float,
            const char* name_wasm_double,
            WasmOp wasm_int32,
            WasmOp wasm_int64,
            WasmOp wasm_float,
            WasmOp wasm_double,
            FIRInstruction::Opcode interp_int32,
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
            fNameWastInt32(name_wasm_int32), fNameWastInt64(name_wasm_int64),
            fNameWastFloat(name_wasm_float), fNameWastDouble(name_wasm_double),
            fWasmInt32(wasm_int32), fWasmInt64(wasm_int64),
            fWasmFloat(wasm_float), fWasmDouble(wasm_double),
            fInterpIntInst32(interp_int32), fInterpFloatInst(interp_float),
            fCompute(f), fLeftNeutral(ln), fRightNeutral(rn),
            fLeftAbsorbing(la), fRightAbsorbing(ra), fPriority(priority)
    {}

    Node compute(const Node& a, const Node& b) { return fCompute(a,b); }

    bool isRightNeutral(const Node& a)      { return fRightNeutral(a); }
    bool isLeftNeutral(const Node& a)       { return fLeftNeutral(a); }
    bool isLeftAbsorbing(const Node& a)     { return fLeftAbsorbing(a); }
    bool isRightAbsorbing(const Node& a)    { return fRightAbsorbing(a); }
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
