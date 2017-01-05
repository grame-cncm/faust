/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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

#ifndef _WAS_INST_H
#define _WAS_INST_H

using namespace std;

#include <iomanip>

#include "binop.hh"
#include "text_instructions.hh"
#include "typing_instructions.hh"

#define realStr ((gGlobal->gFloatSize == 1) ? "f32" : ((gGlobal->gFloatSize == 2) ? "f64" : ""))
#define offStr ((gGlobal->gFloatSize == 1) ? "2" : ((gGlobal->gFloatSize == 2) ? "3" : ""))
#define offStrNum ((gGlobal->gFloatSize == 1) ? 2 : ((gGlobal->gFloatSize == 2) ? 3 : 0))
#define audioMemSize pow(2, offStrNum)
#define wasmMemSize pow(2, 16)

inline int pow2limit(int x)
{
    int n = wasmMemSize; // Minimum = 64 kB
    while (n < x) { n = 2 * n; }
    return n;
}

// Base class for textual and binary wasm visitors
struct WASInst {
    
    struct MemoryDesc {
        
        MemoryDesc()
        {}
        
        MemoryDesc(int offset, int size, Typed::VarType type)
        :fOffset(offset), fSize(size), fType(type)
        {}
        
        int fOffset;
        int fSize;
        Typed::VarType fType;
    };
    
    struct MathFunDesc {
        
        enum Gen { kWAS, kExtMath, kExtWAS, kManual };
        
        MathFunDesc()
        {}
        
        MathFunDesc(Gen mode, const string& name, WasmOp op, Typed::VarType type, int args)
        :fMode(mode), fName(name), fWasmOp(op), fType(type), fArgs(args)
        {}
        
        MathFunDesc(Gen mode, const string& name, Typed::VarType type, int args)
        :fMode(mode), fName(name), fWasmOp(WasmOp::Dummy), fType(type), fArgs(args)
        {}
        
        Gen fMode;
        string fName;
        WasmOp fWasmOp;
        Typed::VarType fType;
        int fArgs;
    };

    TypingVisitor fTypingVisitor;
    map <string, int> fFunctionSymbolTable;
    map <string, MathFunDesc> fMathLibTable;
    map <string, MemoryDesc> fFieldTable;   // Table : field_name, { offset, size, type }
    int fStructOffset;                      // Keep the offset in bytes of the structure
    int fSubContainerType;
    bool fFastMemory;                       // Is true, assume $dsp is always 0 to simplify and speed up dsp memory access code
    
    
    WASInst()
    {
        // Integer version
        fMathLibTable["abs"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "abs", Typed::kInt, 1);
        fMathLibTable["min_i"] = MathFunDesc(MathFunDesc::Gen::kWAS, "min_i", Typed::kInt, 2);
        fMathLibTable["max_i"] = MathFunDesc(MathFunDesc::Gen::kWAS, "max_i", Typed::kInt, 2);
        
        // Float version
        fMathLibTable["fabsf"] = MathFunDesc(MathFunDesc::Gen::kWAS, "abs", WasmOp::F32Abs, Typed::kFloat, 1);
        fMathLibTable["acosf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "acos", Typed::kFloat, 1);
        fMathLibTable["asinf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "asin", Typed::kFloat, 1);
        fMathLibTable["atanf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan", Typed::kFloat, 1);
        fMathLibTable["atan2f"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan2", Typed::kFloat, 2);
        fMathLibTable["ceilf"] = MathFunDesc(MathFunDesc::Gen::kWAS, "ceil", WasmOp::F32Ceil, Typed::kFloat, 1);
        fMathLibTable["cosf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "cos", Typed::kFloat, 1);
        fMathLibTable["expf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "exp", Typed::kFloat, 1);
        fMathLibTable["floorf"] = MathFunDesc(MathFunDesc::Gen::kWAS, "floor", WasmOp::F32Floor, Typed::kFloat, 1);
        fMathLibTable["fmodf"] = MathFunDesc(MathFunDesc::Gen::kExtWAS, "fmod", Typed::kFloat, 2);
        fMathLibTable["logf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "log", Typed::kFloat, 1);
        fMathLibTable["log10f"] = MathFunDesc(MathFunDesc::Gen::kExtWAS, "log10", Typed::kFloat, 1);
        fMathLibTable["max_f"] = MathFunDesc(MathFunDesc::Gen::kWAS, "max", WasmOp::F32Max, Typed::kFloat, 2);
        fMathLibTable["min_f"] = MathFunDesc(MathFunDesc::Gen::kWAS, "min", WasmOp::F32Min, Typed::kFloat, 2);
        fMathLibTable["powf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "pow", Typed::kFloat, 2);
        // fMathLibTable["remainderf"] "manual";      // Manually generated
        fMathLibTable["roundf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "round", Typed::kFloat, 1);
        fMathLibTable["sinf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "sin", Typed::kFloat, 1);
        fMathLibTable["sqrtf"] = MathFunDesc(MathFunDesc::Gen::kWAS, "sqrt", WasmOp::F32Sqrt, Typed::kFloat, 1);
        fMathLibTable["tanf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "tan", Typed::kFloat, 1);
        
        // Double version
        fMathLibTable["fabs"] = MathFunDesc(MathFunDesc::Gen::kWAS, "abs", WasmOp::F64Abs, Typed::kDouble, 1);
        fMathLibTable["acos"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "acos", Typed::kDouble, 1);
        fMathLibTable["asin"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "asin", Typed::kDouble, 1);
        fMathLibTable["atan"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan", Typed::kDouble, 1);
        fMathLibTable["atan2"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan2", Typed::kDouble, 2);
        fMathLibTable["ceil"] = MathFunDesc(MathFunDesc::Gen::kWAS, "ceil", WasmOp::F64Ceil, Typed::kDouble, 1);
        fMathLibTable["cos"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "cos", Typed::kDouble, 1);
        fMathLibTable["exp"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "exp", Typed::kDouble, 1);
        fMathLibTable["floor"] = MathFunDesc(MathFunDesc::Gen::kWAS, "floor", WasmOp::F64Floor, Typed::kDouble, 1);
        fMathLibTable["fmod"] = MathFunDesc(MathFunDesc::Gen::kExtWAS, "fmod", Typed::kDouble, 2);
        fMathLibTable["log"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "log", Typed::kDouble, 1);
        fMathLibTable["log10"] = MathFunDesc(MathFunDesc::Gen::kExtWAS, "log10", Typed::kDouble, 1);
        fMathLibTable["max_"] = MathFunDesc(MathFunDesc::Gen::kWAS, "max", WasmOp::F64Max, Typed::kDouble, 2);
        fMathLibTable["min_"] = MathFunDesc(MathFunDesc::Gen::kWAS, "min", WasmOp::F64Min, Typed::kDouble, 2);
        fMathLibTable["pow"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "pow", Typed::kDouble, 2);
        // fMathLibTable["remainderf"] "manual";      // Manually generated
        fMathLibTable["round"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "round", Typed::kDouble, 1);
        fMathLibTable["sin"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "sin", Typed::kDouble, 1);
        fMathLibTable["sqrt"] = MathFunDesc(MathFunDesc::Gen::kWAS, "sqrt", WasmOp::F64Sqrt, Typed::kDouble, 1);
        fMathLibTable["tan"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "tan", Typed::kDouble, 1);
        
        fStructOffset = 0;
        fSubContainerType = -1;
        //fFastMemory = true;
        
        fFastMemory = false;
    }
    
    void setSubContainerType(int type) { fSubContainerType = type; }
    int getSubContainerType() { return fSubContainerType; }
    
    int getStructSize() { return fStructOffset; }
    
    map <string, MemoryDesc>& getFieldTable() { return fFieldTable; }
    
    int getFieldOffset(const string& name)
    {
        return (fFieldTable.find(name) != fFieldTable.end()) ? fFieldTable[name].fOffset : -1;
    }
    
    static DeclareFunInst* generateIntMin();
    static DeclareFunInst* generateIntMax();
    
    static DeclareFunInst* generateInit();
    static DeclareFunInst* generateInstanceInit();
    
    static DeclareFunInst* generateGetSampleRate();
    
};

#endif
