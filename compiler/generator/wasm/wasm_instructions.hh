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
#include "typing_instructions.hh"

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

#define realStr ((gGlobal->gFloatSize == 1) ? "f32" : ((gGlobal->gFloatSize == 2) ? "f64" : ""))

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
    
        TypingVisitor fTypingVisitor;
    
        map <string, int> fFunctionSymbolTable;
        map <string, string> fMathLibTable;
        map <string, MemoryDesc> fFieldTable;   // Table : field_name, { offset, size, type }
        int fStructOffset;                      // Keep the offset in bytes of the structure
    
    
        bool isRealType(Typed::VarType type)
        {
            return (type == Typed::kFloat
                    || type == Typed::kFloatMacro
                    || type == Typed::kDouble);
        }
    
        bool isIntType(Typed::VarType type)
        {
            return (type == Typed::kInt);
        }

    public:

        WASMInstVisitor(std::ostream* out, int tab = 0)
            :TextInstVisitor(out, ".", tab)
        {
            // Float version
            fMathLibTable["abs"] = "i32.abs";
            fMathLibTable["absf"] = "f32.abs";
            fMathLibTable["fabsf"] = "f32.abs";
            fMathLibTable["acosf"] = "f32.acos";
            fMathLibTable["asinf"] = "f32.asin";
            fMathLibTable["atanf"] = "f32.atan";
            fMathLibTable["atan2f"] = "f32.atan2";
            fMathLibTable["ceilf"] = "f32.ceil";
            fMathLibTable["cosf"] = "f32.cos";
            fMathLibTable["expf"] = "f32.exp";
            fMathLibTable["floorf"] = "f32.floor";
            fMathLibTable["fmodf"] = "manual";      // Manually generated
            fMathLibTable["logf"] = "f32.log";
            fMathLibTable["log10f"] = "manual";     // Manually generated
            fMathLibTable["max"] = "f32.max";
            fMathLibTable["min"] = "f32.min";
            fMathLibTable["powf"] = "f32.pow";
            // fMathLibTable["remainderf"] "manual";      // Manually generated
            fMathLibTable["roundf"] = "f32.round";
            fMathLibTable["sinf"] = "f32.sin";
            fMathLibTable["sqrtf"] = "f32.sqrt";
            fMathLibTable["tanf"] = "f32.tan";
            
            // Double version
            fMathLibTable["abs"] = "i32.abs";
            fMathLibTable["absf"] = "f64.abs";
            fMathLibTable["fabsf"] = "f64.abs";
            fMathLibTable["acosf"] = "f64.acos";
            fMathLibTable["asinf"] = "f64.asin";
            fMathLibTable["atanf"] = "f64.atan";
            fMathLibTable["atan2f"] = "f64.atan2";
            fMathLibTable["ceilf"] = "f64.ceil";
            fMathLibTable["cosf"] = "f64.cos";
            fMathLibTable["expf"] = "f64.exp";
            fMathLibTable["floorf"] = "f64.floor";
            fMathLibTable["fmodf"] = "manual";      // Manually generated
            fMathLibTable["logf"] = "f64.log";
            fMathLibTable["log10f"] = "manual";     // Manually generated
            fMathLibTable["max"] = "f64.max";
            fMathLibTable["min"] = "f64.min";
            fMathLibTable["powf"] = "f64.pow";
            // fMathLibTable["remainderf"] "manual";      // Manually generated
            fMathLibTable["roundf"] = "f64.round";
            fMathLibTable["sinf"] = "f64.sin";
            fMathLibTable["sqrtf"] = "f64.sqrt";
            fMathLibTable["tanf"] = "f64.tan";
            
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
                    tab(fTab, *fOut); *fOut << "(import $" << inst->fName << " \"global.Math\" " "\"" << inst->fName << "\"" << " (param "<< realStr << "(result " << realStr << "))";
                }
            } else {
                // Prototype
                tab(fTab, *fOut); *fOut << "(func $" << generateFunName(inst->fName);
                generateFunDefArgs(inst);
                generateFunDefBody(inst);
                tab(fTab, *fOut); *fOut << ")";
            }
        }
    
        virtual void visit(LoadVarInst* inst)
        {
            /*
            *fOut << "(get_local $";
            inst->fAddress->accept(this);
            *fOut << ")";
            */
            
            fTypingVisitor.visit(inst);
        }
    
        virtual void visit(StoreVarInst* inst)
        {
            /*
            *fOut << "(set_local $";
            inst->fAddress->accept(this);
            *fOut << " ";
            inst->fValue->accept(this);
            *fOut << ")";
            */
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
            fTypingVisitor.visit(inst);
            *fOut << "(f32.const " << checkFloat(inst->fNum) << ")";
        }
        
        virtual void visit(DoubleNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << "(f64.const " << checkDouble(inst->fNum) << ")";
        }
    
        virtual void visit(IntNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << "(i32.const " << inst->fNum << ")";
        }
    
        // Numerical computation
        void visitAuxInt(BinopInst* inst)
        {
            *fOut << "(";
            *fOut << gBinOpTable[inst->fOpcode]->fNameWasmInt;
            *fOut << " ";
            inst->fInst1->accept(this);
            *fOut << " ";
            inst->fInst2->accept(this);
            *fOut << ")";
        }
    
        void visitAuxReal(BinopInst* inst, Typed::VarType type )
        {
            *fOut << "(";
            if (type == Typed::kFloat) {
                *fOut << gBinOpTable[inst->fOpcode]->fNameWasmFloat;
            } else if (type == Typed::kDouble) {
                *fOut << gBinOpTable[inst->fOpcode]->fNameWasmDouble;
            } else {
                assert(false);
            }
            *fOut << " ";
            inst->fInst1->accept(this);
            *fOut << " ";
            inst->fInst2->accept(this);
            *fOut << ")";
        }
    
        virtual void visit(BinopInst* inst)
        {
            if (isBoolOpcode(inst->fOpcode)) {
                *fOut << "(";
                *fOut << gBinOpTable[inst->fOpcode]->fNameWasmInt;
                *fOut << " ";
                inst->fInst1->accept(this);
                *fOut << " ";
                inst->fInst2->accept(this);
                *fOut << ")";
            } else {
                
                inst->fInst1->accept(&fTypingVisitor);
                Typed::VarType type1 = fTypingVisitor.fCurType;
                
                if (isRealType(type1)) {
                    visitAuxReal(inst, type1);
                } else {
                    inst->fInst2->accept(&fTypingVisitor);
                    Typed::VarType type2 = fTypingVisitor.fCurType;
                    if (isRealType(type2)) {
                        visitAuxReal(inst, type1);
                    } else if (isIntType(type1) || isIntType(type2)) {
                        visitAuxInt(inst);
                    } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                        visitAuxInt(inst);
                    } else {
                        // Should never happen...
                        assert(false);
                    }
                }
            }
            
            fTypingVisitor.visit(inst);
        }

        virtual void visit(CastNumInst* inst)
        {
            inst->fInst->accept(&fTypingVisitor);
            Typed::VarType type = fTypingVisitor.fCurType;
            
            if (inst->fType->getType() == Typed::kInt) {
                if (type == Typed::kInt) {
                    std::cout << "CastNumInst : cast to int, but arg already int !" << std::endl;
                } else {
                    *fOut << "(i32.trunc_s/" << realStr;
                    inst->fInst->accept(this);
                    *fOut << ")";
                }
            } else {
                if (isRealType(type)) {
                    std::cout << "CastNumInst : cast to real, but arg already real !" << std::endl;
                } else {
                    *fOut << "(" << realStr << ".convert_s/i32 ";
                    inst->fInst->accept(this);
                    *fOut << ")";
                }
            }
            
            fTypingVisitor.visit(inst);
        }
    
        // Conditional : select
        virtual void visit(Select2Inst* inst)
        {
            *fOut << "(select ";
            inst->fCond->accept(this);
            inst->fThen->accept(this);
            inst->fElse->accept(this);
            *fOut << ")";
            
            fTypingVisitor.visit(inst);
        }
        
        // Conditional : if
        virtual void visit(IfInst* inst)
        {
            *fOut << "(if ";
            inst->fCond->accept(this);
            inst->fThen->accept(this);
            inst->fElse->accept(this);
            *fOut << ")";
            
            fTypingVisitor.visit(inst);
        }
    
        virtual void visit(FunCallInst* inst)
        {}
    
        virtual void visit(ForLoopInst* inst)
        {
            // Don't generate empty loops...
            if (inst->fCode->size() == 0) return;
            
            /*
            DeclareVarInst* c99_declare_inst = dynamic_cast<DeclareVarInst*>(inst->fInit);
            StoreVarInst* c99_init_inst = NULL;
            
            if (c99_declare_inst) {
            
                // To generate C99 compatible loops...
                c99_init_inst = InstBuilder::genStoreStackVar(c99_declare_inst->getName(), c99_declare_inst->fValue);
                c99_declare_inst = InstBuilder::genDecStackVar(c99_declare_inst->getName(),
                                                               InstBuilder::genBasicTyped(Typed::kInt),
                                                               InstBuilder::genIntNumInst(0));
                // C99 loop variable declared outside the loop
                c99_declare_inst->accept(this);
            }
            
            *fOut << "(for ";
                if (c99_declare_inst) {
                    // C99 loop initialized here
                    c99_init_inst->accept(this);
                } else {
                    // Index already defined
                    inst->fInit->accept(this);
                }
                *fOut << "; ";
                inst->fEnd->accept(this);
                *fOut << "; ";
                inst->fIncrement->accept(this);
                *fOut << ") {";
                fTab++;
                tab(fTab, *fOut);
                inst->fCode->accept(this);
                fTab--;
                tab(fTab, *fOut);
                *fOut << "}";
                tab(fTab, *fOut);
            
            *fOut << ")";
            tab(fTab, *fOut);
            */
        }

};

#endif
