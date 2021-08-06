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

#include <iomanip>

#include "binop.hh"
#include "struct_manager.hh"
#include "text_instructions.hh"
#include "typing_instructions.hh"

#define offStrNum ((gGlobal->gFloatSize == 1) ? 2 : ((gGlobal->gFloatSize == 2) ? 3 : 0))
#define audioPtrSize gGlobal->audioSampleSize()
#define wasmBlockSize int(pow(2, 16))

/*
 wast/wasm module ABI:

 - in internal memory mode, a memory segment is allocated, otherwise it is given by the external JS runtime
 - DSP fields start at offset 0, then followed by audio buffers
 - the JSON string is written at offset 0, to be copied and converted in a string
 by the runtime (JS or something else) before using the DSP itsef.

*/

inline int wasm_pow2limit(int x)
{
    int n = wasmBlockSize;  // Minimum = 64 kB
    while (n < x) {
        n = 2 * n;
    }
    return n;
}

// DSP size + (inputs + outputs) * (fsize() + max_buffer_size * audioSampleSize), json_len
inline int genMemSize(int struct_size, int channels, int json_len)
{
    return std::max<int>((wasm_pow2limit(std::max<int>(json_len, struct_size + channels * (audioPtrSize + (8192 * gGlobal->audioSampleSize())))) / wasmBlockSize), 1);
}

// Base class for textual 'wast' and binary 'wasm' visitors
struct WASInst {
    // Description of math functions
    struct MathFunDesc {
        enum Gen {
            kWAS,       // Implemented in wasm definition
            kExtMath,   // Implemented in JS Math context
            kIntWAS,    // Manually implemented in wast/wasm backends
            kExtWAS     // Manually implemented in JS
        };

        MathFunDesc() {}

        MathFunDesc(Gen mode, const string& name, WasmOp op, Typed::VarType type_in, Typed::VarType type_out, int args)
            : fMode(mode),
            fName(name),
            fWasmOp(op),
            fTypeIn(type_in),
            fTypeOut(type_out),
            fArgs(args)
        {}

        MathFunDesc(Gen mode, const string& name, Typed::VarType type_in, Typed::VarType type_out, int args)
            : fMode(mode),
            fName(name),
            fWasmOp(WasmOp::Dummy),
            fTypeIn(type_in),
            fTypeOut(type_out),
            fArgs(args)
        {}

        Gen            fMode;
        string         fName;
        WasmOp         fWasmOp;
        Typed::VarType fTypeIn;
        Typed::VarType fTypeOut;
        int            fArgs;
    };

    TypingVisitor            fTypingVisitor;
    map<string, bool>        fFunctionSymbolTable;  // Already generated functions
    map<string, MathFunDesc> fMathLibTable;         // Table : field_name, math description
    map<string, MemoryDesc>  fFieldTable;           // Table : field_name, { offset, size, type }

    // To generate tee_local the first time the variable access is compiled, then local.get will be used
    map<string, bool> fTeeMap;

    int  fStructOffset;  // Keep the offset in bytes of the structure
    int  fSubContainerType;
    bool fFastMemory;    // If true, assume $dsp is always 0 to simplify and speed-up dsp memory access code

    WASInst(bool fast_memory = false)
    {
        // Integer version
        fMathLibTable["abs"]   = MathFunDesc(MathFunDesc::Gen::kExtMath, "abs", Typed::kInt32, Typed::kInt32, 1);
        fMathLibTable["min_i"] = MathFunDesc(MathFunDesc::Gen::kIntWAS, "min_i", Typed::kInt32, Typed::kInt32, 2);
        fMathLibTable["max_i"] = MathFunDesc(MathFunDesc::Gen::kIntWAS, "max_i", Typed::kInt32, Typed::kInt32, 2);

        // Float version
        fMathLibTable["fabsf"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "abs", WasmOp::F32Abs, Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["acosf"]      = MathFunDesc(MathFunDesc::Gen::kExtMath, "acos", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["asinf"]      = MathFunDesc(MathFunDesc::Gen::kExtMath, "asin", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["atanf"]      = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["atan2f"]     = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan2", Typed::kFloat, Typed::kFloat, 2);
        fMathLibTable["ceilf"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "ceil", WasmOp::F32Ceil, Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["cosf"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "cos", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["expf"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "exp", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["exp10f"]     = MathFunDesc(MathFunDesc::Gen::kExtMath, "exp10", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["floorf"]     = MathFunDesc(MathFunDesc::Gen::kWAS, "floor", WasmOp::F32Floor, Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["fmodf"]      = MathFunDesc(MathFunDesc::Gen::kExtWAS, "fmod", Typed::kFloat, Typed::kFloat, 2);
        fMathLibTable["logf"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "log", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["log10f"]     = MathFunDesc(MathFunDesc::Gen::kExtMath, "log10", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["max_f"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "max", WasmOp::F32Max, Typed::kFloat, Typed::kFloat, 2);
        fMathLibTable["min_f"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "min", WasmOp::F32Min, Typed::kFloat, Typed::kFloat, 2);
        fMathLibTable["powf"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "pow", Typed::kFloat, Typed::kFloat, 2);
        fMathLibTable["remainderf"] = MathFunDesc(MathFunDesc::Gen::kExtWAS, "remainder", Typed::kFloat, Typed::kFloat, 2);
        fMathLibTable["rintf"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "nearest", WasmOp::F32NearestInt, Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["roundf"]     = MathFunDesc(MathFunDesc::Gen::kExtMath, "round", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["sinf"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "sin", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["sqrtf"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "sqrt", WasmOp::F32Sqrt, Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["tanf"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "tan", Typed::kFloat, Typed::kFloat, 1);
        
        // Additional hyperbolic math functions
        fMathLibTable["acoshf"]     =  MathFunDesc(MathFunDesc::Gen::kExtMath, "acosh", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["asinhf"]     =  MathFunDesc(MathFunDesc::Gen::kExtMath, "asinh", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["atanhf"]     =  MathFunDesc(MathFunDesc::Gen::kExtMath, "atanh", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["coshf"]      =  MathFunDesc(MathFunDesc::Gen::kExtMath, "cosh", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["sinhf"]      =  MathFunDesc(MathFunDesc::Gen::kExtMath, "sinh", Typed::kFloat, Typed::kFloat, 1);
        fMathLibTable["tanhf"]      =  MathFunDesc(MathFunDesc::Gen::kExtMath, "tanh", Typed::kFloat, Typed::kFloat, 1);
        
        fMathLibTable["isnanf"]     =  MathFunDesc(MathFunDesc::Gen::kExtMath, "isnan", Typed::kFloat, Typed::kInt32, 1);
        fMathLibTable["isinff"]     =  MathFunDesc(MathFunDesc::Gen::kExtWAS, "isinf", Typed::kFloat, Typed::kInt32, 1);
        fMathLibTable["copysignf"]  =  MathFunDesc(MathFunDesc::Gen::kExtWAS, "copysign", Typed::kFloat, Typed::kFloat, 2);
        
        // Double version
        fMathLibTable["fabs"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "abs", WasmOp::F64Abs, Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["acos"]      = MathFunDesc(MathFunDesc::Gen::kExtMath, "acos", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["asin"]      = MathFunDesc(MathFunDesc::Gen::kExtMath, "asin", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["atan"]      = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["atan2"]     = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan2", Typed::kDouble, Typed::kDouble, 2);
        fMathLibTable["ceil"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "ceil", WasmOp::F64Ceil, Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["cos"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "cos", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["exp"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "exp", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["exp10"]     = MathFunDesc(MathFunDesc::Gen::kExtMath, "exp10", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["floor"]     = MathFunDesc(MathFunDesc::Gen::kWAS, "floor", WasmOp::F64Floor, Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["fmod"]      = MathFunDesc(MathFunDesc::Gen::kExtWAS, "fmod", Typed::kDouble, Typed::kDouble, 2);
        fMathLibTable["log"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "log", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["log10"]     = MathFunDesc(MathFunDesc::Gen::kExtMath, "log10", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["max_"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "max", WasmOp::F64Max, Typed::kDouble, Typed::kDouble, 2);
        fMathLibTable["min_"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "min", WasmOp::F64Min, Typed::kDouble, Typed::kDouble, 2);
        fMathLibTable["pow"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "pow", Typed::kDouble, Typed::kDouble, 2);
        fMathLibTable["remainder"] = MathFunDesc(MathFunDesc::Gen::kExtWAS, "remainder", Typed::kDouble, Typed::kDouble, 2);
        fMathLibTable["rint"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "nearest", WasmOp::F64NearestInt, Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["round"]     = MathFunDesc(MathFunDesc::Gen::kExtMath, "round", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["sin"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "sin", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["sqrt"]      = MathFunDesc(MathFunDesc::Gen::kWAS, "sqrt", WasmOp::F64Sqrt, Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["tan"]       = MathFunDesc(MathFunDesc::Gen::kExtMath, "tan", Typed::kDouble, Typed::kDouble, 1);
        
        // Additional hyperbolic math functions
        fMathLibTable["acosh"]     =  MathFunDesc(MathFunDesc::Gen::kExtMath, "acosh", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["asinh"]     =  MathFunDesc(MathFunDesc::Gen::kExtMath, "asinh", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["atanh"]     =  MathFunDesc(MathFunDesc::Gen::kExtMath, "atanh", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["cosh"]      =  MathFunDesc(MathFunDesc::Gen::kExtMath, "cosh", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["sinh"]      =  MathFunDesc(MathFunDesc::Gen::kExtMath, "sinh", Typed::kDouble, Typed::kDouble, 1);
        fMathLibTable["tanh"]      =  MathFunDesc(MathFunDesc::Gen::kExtMath, "tanh", Typed::kDouble, Typed::kDouble, 1);
   
        fMathLibTable["isnan"]     =  MathFunDesc(MathFunDesc::Gen::kExtMath, "isnan", Typed::kDouble, Typed::kInt32, 1);
        fMathLibTable["isinf"]     =  MathFunDesc(MathFunDesc::Gen::kExtWAS, "isinf", Typed::kDouble, Typed::kInt32, 1);
        fMathLibTable["copysign"]  =  MathFunDesc(MathFunDesc::Gen::kExtWAS, "copysign", Typed::kDouble, Typed::kDouble, 2);
        
        fStructOffset     = 0;
        fSubContainerType = -1;
        fFastMemory       = fast_memory;
    }

    void setSubContainerType(int type) { fSubContainerType = type; }
    int  getSubContainerType() { return fSubContainerType; }

    // The DSP size in bytes
    int getStructSize() { return fStructOffset; }

    map<string, MemoryDesc>& getFieldTable() { return fFieldTable; }

    // Check if address is constant, so that to be used as an 'offset' in load/store
    int getConstantOffset(Address* address)
    {
        static char* wasm_opt      = getenv("FAUST_WASM");
        static bool  no_offset_opt = wasm_opt && (string(wasm_opt) == "no-offset");

        if (!fFastMemory || no_offset_opt) {
            return 0;
        }
        
        string name = address->getName();
        NamedAddress*   named   = dynamic_cast<NamedAddress*>(address);
        IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(address);
        
        if (fFieldTable.find(name) != fFieldTable.end()) {
            MemoryDesc tmp = fFieldTable[name];
            if (named) {
                return tmp.fOffset;
            } else if (indexed) {
                Int32NumInst* num;
                if ((num = dynamic_cast<Int32NumInst*>(indexed->fIndex))) {
                    return tmp.fOffset + (num->fNum << offStrNum);
                }
            }
        }
        
        return 0;
    }

    static DeclareFunInst* generateIntMin();
    static DeclareFunInst* generateIntMax();
};

#endif
