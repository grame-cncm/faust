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
        
        MathFunDesc(Gen mode, const string& name, Typed::VarType type, int args)
        :fMode(mode), fName(name), fType(type), fArgs(args)
        {}
        
        Gen fMode;
        string fName;
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
        fMathLibTable["fabsf"] = MathFunDesc(MathFunDesc::Gen::kWAS, "abs", itfloat(), 1);
        fMathLibTable["acosf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "acos", itfloat(), 1);
        fMathLibTable["asinf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "asin", itfloat(), 1);
        fMathLibTable["atanf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan", itfloat(), 1);
        fMathLibTable["atan2f"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan2", itfloat(), 2);
        fMathLibTable["ceilf"] = MathFunDesc(MathFunDesc::Gen::kWAS, "ceil", itfloat(), 1);
        fMathLibTable["cosf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "cos", itfloat(), 1);
        fMathLibTable["expf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "exp", itfloat(), 1);
        fMathLibTable["floorf"] = MathFunDesc(MathFunDesc::Gen::kWAS, "floor", itfloat(), 1);
        fMathLibTable["fmodf"] = MathFunDesc(MathFunDesc::Gen::kExtWAS, "fmod", itfloat(), 2);
        fMathLibTable["logf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "log", itfloat(), 1);
        fMathLibTable["log10f"] = MathFunDesc(MathFunDesc::Gen::kExtWAS, "log10", itfloat(), 1);
        fMathLibTable["max_f"] = MathFunDesc(MathFunDesc::Gen::kWAS, "max", itfloat(), 2);
        fMathLibTable["min_f"] = MathFunDesc(MathFunDesc::Gen::kWAS, "min", itfloat(), 2);
        fMathLibTable["powf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "pow", itfloat(), 2);
        // fMathLibTable["remainderf"] "manual";      // Manually generated
        fMathLibTable["roundf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "round", itfloat(), 1);
        fMathLibTable["sinf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "sin", itfloat(), 1);
        fMathLibTable["sqrtf"] = MathFunDesc(MathFunDesc::Gen::kWAS, "sqrt", itfloat(), 1);
        fMathLibTable["tanf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "tan", itfloat(), 1);
        
        // Double version
        fMathLibTable["fabs"] = MathFunDesc(MathFunDesc::Gen::kWAS, "abs", itfloat(), 1);
        fMathLibTable["acos"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "acos", itfloat(), 1);
        fMathLibTable["asin"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "asin", itfloat(), 1);
        fMathLibTable["atan"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan", itfloat(), 1);
        fMathLibTable["atan2"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan2", itfloat(), 2);
        fMathLibTable["ceil"] = MathFunDesc(MathFunDesc::Gen::kWAS, "ceil", itfloat(), 1);
        fMathLibTable["cos"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "cos", itfloat(), 1);
        fMathLibTable["exp"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "exp", itfloat(), 1);
        fMathLibTable["floor"] = MathFunDesc(MathFunDesc::Gen::kWAS, "floor", itfloat(), 1);
        fMathLibTable["fmod"] = MathFunDesc(MathFunDesc::Gen::kExtWAS, "fmod", itfloat(), 2);
        fMathLibTable["log"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "log", itfloat(), 1);
        fMathLibTable["log10"] = MathFunDesc(MathFunDesc::Gen::kExtWAS, "log10", itfloat(), 1);
        fMathLibTable["max_"] = MathFunDesc(MathFunDesc::Gen::kWAS, "max", itfloat(), 2);
        fMathLibTable["min_"] = MathFunDesc(MathFunDesc::Gen::kWAS, "min", itfloat(), 2);
        fMathLibTable["pow"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "pow", itfloat(), 2);
        // fMathLibTable["remainderf"] "manual";      // Manually generated
        fMathLibTable["round"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "round", itfloat(), 1);
        fMathLibTable["sin"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "sin", itfloat(), 1);
        fMathLibTable["sqrt"] = MathFunDesc(MathFunDesc::Gen::kWAS, "sqrt", itfloat(), 1);
        fMathLibTable["tan"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "tan", itfloat(), 1);
        fStructOffset = 0;
        fSubContainerType = -1;
        fFastMemory = true;
    }
    
    void setSubContainerType(int type) { fSubContainerType = type; }
    int getSubContainerType() { return fSubContainerType; }
    
    int getStructSize() { return fStructOffset; }
    
    map <string, MemoryDesc>& getFieldTable() { return fFieldTable; }
    
    int getFieldOffset(const string& name)
    {
        return (fFieldTable.find(name) != fFieldTable.end()) ? fFieldTable[name].fOffset : -1;
    }
    
};

#endif
