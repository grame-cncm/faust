/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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

#ifndef _WASM_INSTRUCTIONS_H
#define _WASM_INSTRUCTIONS_H

using namespace std;

#include "text_instructions.hh"

/*
var asm2wasmImports = { // special asm2wasm imports
    "f64-rem": function(x, y) {
        return x % y;
    },
    "f64-to-int": function(x) {
        return x | 0;
    },
    "debugger": function() {
        debugger;
    },
};
*/

class WASMInstVisitor : public TextInstVisitor {

    private:
    
        struct MemoryDesc {
            
            MemoryDesc():
            fOffset(-1), fSize(-1), fType(Typed::kNoType)
            {}
            
            MemoryDesc(int offset, int size, Typed::VarType type):
            fOffset(offset), fSize(size), fType(type)
            {}
            
            int fOffset;
            int fSize;
            Typed::VarType fType;
        };
    
        map <string, int> fFunctionSymbolTable;
        map <string, string> fMathLibTable;
        map <string, MemoryDesc> fFieldTable;   // Table : field_name, { offset, size, type }
        int fStructOffset;                      // Keep the offset in bytes of the structure

    public:

        WASMInstVisitor(std::ostream* out, int tab = 0)
            :TextInstVisitor(out, ".", tab)
        {
            fMathLibTable["abs"] = "global.Math.abs";
            fMathLibTable["absf"] = "global.Math.abs";
            fMathLibTable["fabsf"] = "global.Math.abs";
            fMathLibTable["acosf"] = "global.Math.acos";
            fMathLibTable["asinf"] = "global.Math.asin";
            fMathLibTable["atanf"] = "global.Math.atan";
            fMathLibTable["atan2f"] = "global.Math.atan2";
            fMathLibTable["ceilf"] = "global.Math.ceil";
            fMathLibTable["cosf"] = "global.Math.cos";
            fMathLibTable["expf"] = "global.Math.exp";
            fMathLibTable["floorf"] = "global.Math.floor";
            fMathLibTable["fmodf"] = "manual";      // Manually generated
            fMathLibTable["logf"] = "global.Math.log";
            fMathLibTable["log10f"] = "manual";     // Manually generated
            fMathLibTable["max"] = "global.Math.max";
            fMathLibTable["min"] = "global.Math.min";
            fMathLibTable["powf"] = "global.Math.pow";
            fMathLibTable["roundf"] = "global.Math.round";
            fMathLibTable["sinf"] = "global.Math.sin";
            fMathLibTable["sqrtf"] = "global.Math.sqrt";
            fMathLibTable["tanf"] = "global.Math.tan";
            
            fStructOffset = 0;
        }

        virtual ~WASMInstVisitor()
        {}
    
        int getStructSize() { return fStructOffset; }
    
        int getFieldOffset(const string& name)
        {
            return (fFieldTable.find(name) != fFieldTable.end()) ? fFieldTable[name].fOffset : -1;
        }

        virtual void visit(DeclareVarInst* inst)
        {
            // HACK : completely adhoc code for input/output...
            if ((startWith(inst->fAddress->getName(), "input") || startWith(inst->fAddress->getName(), "output"))) {
                return;
            }
            
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
            
            if (array_typed && array_typed->fSize > 1) {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(fStructOffset, array_typed->fSize, array_typed->fType->getType());
                fStructOffset += array_typed->fSize;
            } else {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(fStructOffset, 1, inst->fType->getType());
                fStructOffset++;
            }
            
            // Simulate a 'Store'
            if (inst->fValue) {
                visitStore(inst->fAddress, inst->fValue, inst->fType);
            }
        }
    
        virtual void visitStore(Address* address, ValueInst* value, Typed* type = NULL)
        {
        }
    
        virtual void generateFunDefArgs(DeclareFunInst* inst)
        {}
    
        virtual void generateFunDefBody(DeclareFunInst* inst)
        {}
    
        virtual void visit(DeclareFunInst* inst)
        {
            // Already generated
            if (fFunctionSymbolTable.find(inst->fName) != fFunctionSymbolTable.end()) {
                return;
            } else {
                fFunctionSymbolTable[inst->fName] = 1;
            }
            
            // Math library functions are part of the 'global' module, 'fmodf' and 'log10f' will be manually generated
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                if (fMathLibTable[inst->fName] != "manual") {
                    tab(fTab, *fOut); *fOut << "(import $" << inst->fName << " \"global.Math\" " "\"" << inst->fName << "\"" << " (param f64) (result f64))";
                }
            } else {
                // Prototype
                tab(fTab, *fOut); *fOut << "(func $" << generateFunName(inst->fName);
                generateFunDefArgs(inst);
                generateFunDefBody(inst);
                tab(fTab, *fOut); *fOut << ")";
            }
        }
        
        virtual void visit(NamedAddress* named)
        {}
  
        virtual void visit(LoadVarAddressInst* inst)
        {
           // Not implemented in WASM
            assert(false);
        }
                
        virtual void visit(FloatNumInst* inst)
        {
            *fOut << "(f32.const " << checkFloat(inst->fNum) << ")";
        }
        
        virtual void visit(DoubleNumInst* inst)
        {
            *fOut << "(f64.const " << checkDouble(inst->fNum) << ")";
        }
    
        virtual void visit(IntNumInst* inst)
        {
            *fOut << "(i32.const " << inst->fNum << ")";
        }
    
        // Numerical computation
        virtual void visit(BinopInst* inst)
        {
        }

        virtual void visit(CastNumInst* inst)
        {
        }
    
        // Conditional : select
        virtual void visit(Select2Inst* inst)
        {
            
        }
        
        // Conditional : if
        virtual void visit(IfInst* inst)
        {

        }
    
        virtual void visit(FunCallInst* inst)
        {}
    
        virtual void visit(ForLoopInst* inst)
        {

        }

};

#endif
