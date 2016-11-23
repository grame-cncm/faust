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

#include <iomanip>

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
#define offStr ((gGlobal->gFloatSize == 1) ? "2" : ((gGlobal->gFloatSize == 2) ? "3" : ""))

class WASMInstVisitor : public TextInstVisitor {
    
    public:
    
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
  
    private:
    
        TypingVisitor fTypingVisitor;
        map <string, int> fFunctionSymbolTable;
        map <string, string> fMathLibTable;
        map <string, MemoryDesc> fFieldTable;   // Table : field_name, { offset, size, type }
        int fStructOffset;                      // Keep the offset in bytes of the structure
        int fSubContainerType;
 
        string type2String(Typed::VarType type)
        {
            if (type == Typed::kInt
                || type == Typed::kFloat_ptr
                || type == Typed::kDouble_ptr) {
                return "i32";
            } else if (type == Typed::kFloat) {
                return "f32";
            } else if (type == Typed::kDouble) {
                return "f64";
            } else {
                assert(false);
                return "";
            }
        }
    
        virtual void EndLine()
        {
            if (fFinishLine) {
                tab(fTab, *fOut);
            }
        }
    
        string ensureFloat(string str)
        {
            bool dot = false;
            int e_pos = -1;
            for (unsigned int i = 0; i < str.size(); i++) {
                if (str[i] == '.') {
                    dot = true;
                    break;
                } else if (str[i] == 'e') {
                    e_pos = i;
                    break;
                }
            }
            
            if (e_pos >= 0) {
                return str.insert(e_pos, 1, '.');
            } else {
                return (dot) ? str : (str + ".");
            }
        }
        
        // Special version without termination
        template <class T>
        string checkReal(T val)
        {
            std::stringstream num;
            num << std::setprecision(std::numeric_limits<T>::max_digits10) << val;
            return ensureFloat(num.str());
        }
    
    public:

        WASMInstVisitor(std::ostream* out, int tab = 0)
            :TextInstVisitor(out, ".", tab)
        {
            fMathLibTable["abs"] = "abs";
  
            // Float version
            fMathLibTable["fabsf"] = "abs";
            fMathLibTable["acosf"] = "acos";
            fMathLibTable["asinf"] = "asin";
            fMathLibTable["atanf"] = "atan";
            fMathLibTable["atan2f"] = "atan2";
            fMathLibTable["ceilf"] = "ceil";
            fMathLibTable["cosf"] = "cos";
            fMathLibTable["expf"] = "exp";
            fMathLibTable["floorf"] = "floor";
            fMathLibTable["fmodf"] = "manual";      // Manually generated
            fMathLibTable["logf"] = "log";
            fMathLibTable["log10f"] = "manual";     // Manually generated
            fMathLibTable["max"] = "wasm";          // Part of WebAssembly
            fMathLibTable["min"] = "wasm";          // Part of WebAssembly
            fMathLibTable["powf"] = "pow";
            // fMathLibTable["remainderf"] "manual";      // Manually generated
            fMathLibTable["roundf"] = "round";
            fMathLibTable["sinf"] = "sin";
            fMathLibTable["sqrtf"] = "wasm";        // Part of WebAssembly
            fMathLibTable["tanf"] = "tan";
            
            // Double version
            fMathLibTable["fabs"] = "abs";
            fMathLibTable["acos"] = "acos";
            fMathLibTable["asin"] = "asin";
            fMathLibTable["atan"] = "atan";
            fMathLibTable["atan2"] = "atan2";
            fMathLibTable["ceil"] = "ceil";
            fMathLibTable["cos"] = "cos";
            fMathLibTable["exp"] = "exp";
            fMathLibTable["floor"] = "floor";
            fMathLibTable["fmod"] = "manual";       // Manually generated
            fMathLibTable["log"] = "log";
            fMathLibTable["log10"] = "manual";      // Manually generated
            fMathLibTable["max"] = "wasm";          // Part of WebAssembly
            fMathLibTable["min"] = "wasm";          // Part of WebAssembly
            fMathLibTable["pow"] = "pow";
            // fMathLibTable["remainderf"] "manual";      // Manually generated
            fMathLibTable["round"] = "round";
            fMathLibTable["sin"] = "sin";
            fMathLibTable["sqrt"] = "wasm";        // Part of WebAssembly
            fMathLibTable["tan"] = "tan";
            
            fStructOffset = 0;
            fSubContainerType = -1;
        }

        virtual ~WASMInstVisitor()
        {}
    
        void setSubContainerType(int type) { fSubContainerType = type; }
    
        int getStructSize() { return fStructOffset; }
    
        map <string, MemoryDesc>& getFieldTable() { return fFieldTable; }
    
        map <string, string>& getMathLibTable() { return fMathLibTable; }
    
        int getFieldOffset(const string& name)
        {
            return (fFieldTable.find(name) != fFieldTable.end()) ? fFieldTable[name].fOffset : -1;
        }
  
        virtual void visit(DeclareVarInst* inst)
        {
            //std::cout << "DeclareVarInst " << inst->fAddress->getName() << std::endl;
            
            bool is_struct = (inst->fAddress->getAccess() & Address::kStruct) || (inst->fAddress->getAccess() & Address::kStaticStruct);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
            
            if (array_typed && array_typed->fSize > 1) {
                if (is_struct) {
                    
                    //std::cout << "DeclareVarInst " << inst->fAddress->getName() << " " << array_typed->fType->getType() << std::endl;
                    
                    fFieldTable[inst->fAddress->getName()] = MemoryDesc(fStructOffset, array_typed->fSize, array_typed->fType->getType());
                    fStructOffset += (array_typed->fSize * fsize()); // Always use biggest size so that int/real access are correctly aligned
                } else {
                    // Should never happen...
                    assert(false);
                }
            } else {
                if (is_struct) {
                    
                    //std::cout << "DeclareVarInst STRUCT " << inst->fAddress->getName() << " " << inst->fType->getType() << std::endl;
                    
                    fFieldTable[inst->fAddress->getName()] = MemoryDesc(fStructOffset, 1, inst->fType->getType());
                    fStructOffset += fsize(); // Always use biggest size so that int/real access are correctly aligned
                } else {
                    
                    // Put in the table with a dummy offset
                    fFieldTable[inst->fAddress->getName()] = MemoryDesc(-1, -1, inst->fType->getType());
                    
                    *fOut << "(local $" << inst->fAddress->getName() << " " << type2String(inst->fType->getType()) << ")";
                    
                    assert(inst->fValue == nullptr);
                    
                    /*
                    if (inst->fValue) {
                        tab(fTab, *fOut);
                        *fOut << "(set_local $" << inst->fAddress->getName() << " ";
                        inst->fValue->accept(this);
                        *fOut << ")";
                        EndLine();
                    }
                    */
                    EndLine();
                }
            }
        }
    
        virtual void generateFunDefArgs(DeclareFunInst* inst)
        {
            // TODO
            /*
            list<NamedTyped*>::const_iterator it;
            int size = inst->fType->fArgsTypes.size(), i = 0;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                *fOut << generateType((*it));
                if (i < size - 1) *fOut << ", ";
            }
            */
        }
    
        virtual void generateFunDefBody(DeclareFunInst* inst)
        {
            // TODO
            /*
            if (inst->fCode->fCode.size() == 0) {
                *fOut << ")" << endl;  // Pure prototype
            } else {
                // Function body
                *fOut << ")";
                    fTab++;
                    tab(fTab, *fOut);
                    inst->fCode->accept(this);
                    fTab--;
                tab(fTab, *fOut);
            }
            */
        }

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
                if (fMathLibTable[inst->fName] != "manual" && fMathLibTable[inst->fName] != "wasm") {
                    tab(fTab, *fOut);
                    *fOut << "(import $" << inst->fName << " \"global.Math\" " "\"" << fMathLibTable[inst->fName]
                          << "\"" << " (param " << realStr << ") (result " << realStr << "))";
                }
            } else {
                // Prototype
                tab(fTab, *fOut); *fOut << "(func $" << generateFunName(inst->fName);
                generateFunDefArgs(inst);
                generateFunDefBody(inst);
                tab(fTab, *fOut); *fOut << ")";
            }
        }
    
        /*
        virtual void visit(LoadVarInst* inst)
        {
            fTypingVisitor.visit(inst);
            
            if (isIntOrPtrType(fTypingVisitor.fCurType)) {
                *fOut << "(i32.load ";
                TextInstVisitor::visit(inst);
                *fOut << ")";
            } else if (isRealType(fTypingVisitor.fCurType)) {
                *fOut << "(" << realStr;
                TextInstVisitor::visit(inst);
                *fOut << ")";
            } else {
                // HACK : completely adhoc code for input/output/count/samplingFreq...
                if ((startWith(inst->getName(), "inputs")
                     || startWith(inst->getName(), "outputs")
                     || startWith(inst->getName(), "count")
                     || startWith(inst->getName(), "samplingFreq"))) {
                    *fOut << "(i32.load ";
                    TextInstVisitor::visit(inst);
                    *fOut << ")";
                } else {
                    TextInstVisitor::visit(inst);
                }
            }
        }
        */
    
        virtual void visit(LoadVarInst* inst)
        {
            /*
              std::cout << "LoadVarInst " << inst->fAddress->getName() << std::endl;
              assert(fFieldTable.find(inst->fAddress->getName()) != fFieldTable.end());
              MemoryDesc tmp = fFieldTable[inst->fAddress->getName()];

              //std::cout << "LoadVarInst " << inst->fAddress->getName() << " " << tmp.fType << std::endl;
              */

            fTypingVisitor.visit(inst);

            //std::cout << "LoadVarInst " << inst->fAddress->getName() << " " << Typed::gTypeString[fTypingVisitor.fCurType] << std::endl;

            if (inst->fAddress->getAccess() & Address::kStruct
                || inst->fAddress->getAccess() & Address::kStaticStruct
                || dynamic_cast<IndexedAddress*>(inst->fAddress)) {

                if (isRealType(fTypingVisitor.fCurType) || isRealPtrType(fTypingVisitor.fCurType)) {
                    *fOut << "(" << realStr << ".load ";
                } else {
                    *fOut << "(i32.load ";
                }
                inst->fAddress->accept(this);
                *fOut << ")";
            } else {
                *fOut << "(get_local $" << inst->fAddress->getName() << ")";
            }
        }

        virtual void visit(StoreVarInst* inst)
        {
            /*
            assert(fFieldTable.find(inst->fAddress->getName()) != fFieldTable.end());
            MemoryDesc tmp = fFieldTable[inst->fAddress->getName()];
            -            if (isRealType(tmp.fType)) {
            -                *fOut << "(" << realStr << ".store ";
                  */

            inst->fValue->accept(&fTypingVisitor);

            if (inst->fAddress->getAccess() & Address::kStruct
                || inst->fAddress->getAccess() & Address::kStaticStruct
                || dynamic_cast<IndexedAddress*>(inst->fAddress)) {

                if (isRealType(fTypingVisitor.fCurType) || isRealPtrType(fTypingVisitor.fCurType)) {
                    *fOut << "(" << realStr << ".store ";
                } else {
                    *fOut << "(i32.store ";
                }
                inst->fAddress->accept(this);
                *fOut << " ";
                inst->fValue->accept(this);
                *fOut << ")";

            } else {
                *fOut << "(set_local $" << inst->fAddress->getName() << " ";
                inst->fValue->accept(this);
                *fOut << ")";
            }

            EndLine();
        }

        virtual void visit(NamedAddress* named)
        {
            if (named->getAccess() & Address::kStruct || named->getAccess() & Address::kStaticStruct) {
                MemoryDesc tmp = fFieldTable[named->getName()];
                *fOut << "(i32.add (get_local $dsp) (i32.const " << tmp.fOffset << "))";
            } else {
                *fOut << "(get_local $" << named->fName << ")";
            }
        }
    
        virtual void visit(IndexedAddress* indexed)
        {
            // HACK : completely adhoc code for inputs/outputs...
            if ((startWith(indexed->getName(), "inputs") || startWith(indexed->getName(), "outputs"))) {
                *fOut << "(i32.add (get_local $" << indexed->getName() << ") (i32.shl ";
                indexed->fIndex->accept(this);
                *fOut << " (i32.const 2)))";
                // HACK : completely adhoc code for input/output...
            } else if ((startWith(indexed->getName(), "input") || startWith(indexed->getName(), "output"))) {
                // Force "output" access to be coherent with fSubContainerType (integer or real)
                *fOut << "(i32.add (get_local $" << indexed->getName() << ") (i32.shl ";
                indexed->fIndex->accept(this);
                // Force "output" access to be coherent with fSubContainerType (integer or real)
                if (fSubContainerType == kInt) {
                    *fOut << " (i32.const 2)))";
                } else {
                    *fOut << " (i32.const " << offStr << ")))";
                }
            } else {
                // Fields in struct are accessed using 'dsp' and an offset
                MemoryDesc tmp = fFieldTable[indexed->getName()];
                *fOut << "(i32.add (i32.add (get_local $dsp) (i32.const " << tmp.fOffset << ")) (i32.shl ";
                indexed->fIndex->accept(this);
                *fOut << " (i32.const " << offStr << ")))";
            }
        }
  
        virtual void visit(LoadVarAddressInst* inst)
        {
           // Not implemented in WASM
            assert(false);
        }
                
        virtual void visit(FloatNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << "(f32.const " << checkReal<float>(inst->fNum) << ")";
        }
        
        virtual void visit(DoubleNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << "(f64.const " << checkReal<double>(inst->fNum) << ")";
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
                    //std::cout << "CastNumInst : cast to int, but arg already int !" << std::endl;
                    inst->fInst->accept(this);
                } else {
                    *fOut << "(i32.trunc_s/" << realStr << " ";
                    inst->fInst->accept(this);
                    *fOut << ")";
                }
            } else {
                if (isRealType(type)) {
                    //std::cout << "CastNumInst : cast to real, but arg already real !" << std::endl;
                    inst->fInst->accept(this);
                } else {
                    *fOut << "(" << realStr << ".convert_s/i32 ";
                    inst->fInst->accept(this);
                    *fOut << ")";
                }
            }
            
            fTypingVisitor.visit(inst);
        }
    
        // Generate standard funcall (not 'method' like funcall...)
        virtual void visit(FunCallInst* inst)
        {
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end() && fMathLibTable[inst->fName] == "wasm") {
                *fOut << "(" << realStr << "." << inst->fName << " ";
            } else {
                *fOut  << "(" << inst->fName << " ";
            }
            generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
            *fOut << ")";
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
    
        virtual void visit(ForLoopInst* inst)
        {
            // Don't generate empty loops...
            if (inst->fCode->size() == 0) return;
            
            // Local variables declaration including the loop counter have been moved outside of the loop
            static int loopCount = 0;
            
            *fOut << "(loop $for-in" << loopCount << " ";
            fTab++;
                tab(fTab, *fOut);
                *fOut << "(block $for-out" << loopCount << " ";
                    fTab++;
                    tab(fTab, *fOut);
                    // Loop counter test and possibly branch out
                    *fOut << "(if (i32.eqz ";
                    inst->fEnd->accept(this);
                    *fOut << ") (br $for-out" << loopCount << "))";
                    // Loop code
                    tab(fTab, *fOut);
                    inst->fCode->accept(this);
                    // Loop increment
                    inst->fIncrement->accept(this);
                    // Branch to loop label
                    *fOut << "(br $for-in" << loopCount++ << ")";
                    tab(fTab, *fOut);
                fTab--;
                tab(fTab, *fOut);
                *fOut << ")";
            fTab--;
            tab(fTab, *fOut);
            *fOut << ")";
            tab(fTab, *fOut);
        }
    
        // is this needed ?
        /*
        virtual void visit(BlockInst* inst)
        {
            *fOut << "(block";
                fTab++;
                tab(fTab, *fOut);
                TextInstVisitor::visit(inst);
                fTab--;
                tab(fTab, *fOut);
            *fOut << ")";
        }
        */

};

#endif
