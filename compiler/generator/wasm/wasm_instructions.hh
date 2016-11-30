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
#define offStrNum ((gGlobal->gFloatSize == 1) ? 2 : ((gGlobal->gFloatSize == 2) ? 3 : 0))
#define audioMemSize pow(2, offStrNum)
#define wasmMemSize pow(2, 16)

class WASMInstVisitor : public TextInstVisitor {
    
    public:
    
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
        
            enum Gen { kWasm, kExtMath, kExtAsm, kManual };
            
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
  
    private:
    
        TypingVisitor fTypingVisitor;
        map <string, int> fFunctionSymbolTable;
        map <string, MathFunDesc> fMathLibTable;
        map <string, MemoryDesc> fFieldTable;   // Table : field_name, { offset, size, type }
        int fStructOffset;                      // Keep the offset in bytes of the structure
        int fSubContainerType;
        bool fFastMemory;                       // Is true, assume $dsp is always 0 to simplify and speed up dsp memory access code
 
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
            // Integer version
            fMathLibTable["abs"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "abs", Typed::kInt, 1);
            fMathLibTable["min_i"] = MathFunDesc(MathFunDesc::Gen::kWasm, "min_i", Typed::kInt, 2);
            fMathLibTable["max_i"] = MathFunDesc(MathFunDesc::Gen::kWasm, "max_i", Typed::kInt, 2);
  
            // Float version
            fMathLibTable["fabsf"] = MathFunDesc(MathFunDesc::Gen::kWasm, "abs", itfloat(), 1);
            fMathLibTable["acosf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "acos", itfloat(), 1);
            fMathLibTable["asinf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "asin", itfloat(), 1);
            fMathLibTable["atanf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan", itfloat(), 1);
            fMathLibTable["atan2f"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan2", itfloat(), 2);
            fMathLibTable["ceilf"] = MathFunDesc(MathFunDesc::Gen::kWasm, "ceil", itfloat(), 1);
            fMathLibTable["cosf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "cos", itfloat(), 1);
            fMathLibTable["expf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "exp", itfloat(), 1);
            fMathLibTable["floorf"] = MathFunDesc(MathFunDesc::Gen::kWasm, "floor", itfloat(), 1);
            fMathLibTable["fmodf"] = MathFunDesc(MathFunDesc::Gen::kExtAsm, "fmod", itfloat(), 2);
            fMathLibTable["logf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "log", itfloat(), 1);
            fMathLibTable["log10f"] = MathFunDesc(MathFunDesc::Gen::kExtAsm, "log10", itfloat(), 1);
            fMathLibTable["max_f"] = MathFunDesc(MathFunDesc::Gen::kWasm, "max", itfloat(), 2);
            fMathLibTable["min_f"] = MathFunDesc(MathFunDesc::Gen::kWasm, "min", itfloat(), 2);
            fMathLibTable["powf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "pow", itfloat(), 2);
            // fMathLibTable["remainderf"] "manual";      // Manually generated
            fMathLibTable["roundf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "round", itfloat(), 1);
            fMathLibTable["sinf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "sin", itfloat(), 1);
            fMathLibTable["sqrtf"] = MathFunDesc(MathFunDesc::Gen::kWasm, "sqrt", itfloat(), 1);
            fMathLibTable["tanf"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "tan", itfloat(), 1);
            
            // Double version
            fMathLibTable["fabs"] = MathFunDesc(MathFunDesc::Gen::kWasm, "abs", itfloat(), 1);
            fMathLibTable["acos"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "acos", itfloat(), 1);
            fMathLibTable["asin"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "asin", itfloat(), 1);
            fMathLibTable["atan"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan", itfloat(), 1);
            fMathLibTable["atan2"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "atan2", itfloat(), 2);
            fMathLibTable["ceil"] = MathFunDesc(MathFunDesc::Gen::kWasm, "ceil", itfloat(), 1);
            fMathLibTable["cos"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "cos", itfloat(), 1);
            fMathLibTable["exp"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "exp", itfloat(), 1);
            fMathLibTable["floor"] = MathFunDesc(MathFunDesc::Gen::kWasm, "floor", itfloat(), 1);
            fMathLibTable["fmod"] = MathFunDesc(MathFunDesc::Gen::kExtAsm, "fmod", itfloat(), 2);
            fMathLibTable["log"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "log", itfloat(), 1);
            fMathLibTable["log10"] = MathFunDesc(MathFunDesc::Gen::kExtAsm, "log10", itfloat(), 1);
            fMathLibTable["max_"] = MathFunDesc(MathFunDesc::Gen::kWasm, "max", itfloat(), 2);
            fMathLibTable["min_"] = MathFunDesc(MathFunDesc::Gen::kWasm, "min", itfloat(), 2);
            fMathLibTable["pow"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "pow", itfloat(), 2);
            // fMathLibTable["remainderf"] "manual";      // Manually generated
            fMathLibTable["round"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "round", itfloat(), 1);
            fMathLibTable["sin"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "sin", itfloat(), 1);
            fMathLibTable["sqrt"] = MathFunDesc(MathFunDesc::Gen::kWasm, "sqrt", itfloat(), 1);
            fMathLibTable["tan"] = MathFunDesc(MathFunDesc::Gen::kExtMath, "tan", itfloat(), 1);
            fStructOffset = 0;
            fSubContainerType = -1;
            fFastMemory = true;
        }

        virtual ~WASMInstVisitor()
        {}
    
        void setSubContainerType(int type) { fSubContainerType = type; }
    
        int getStructSize() { return fStructOffset; }
    
        map <string, MemoryDesc>& getFieldTable() { return fFieldTable; }
    
        //map <string, string>& getMathLibTable() { return fMathLibTable; }
    
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
                    
                    // Put in the table with a dummy offset (seems not necessary anymore...)
                    //fFieldTable[inst->fAddress->getName()] = MemoryDesc(-1, -1, inst->fType->getType());
                    
                    *fOut << "(local $" << inst->fAddress->getName() << " " << type2String(inst->fType->getType()) << ")";
                    
                    // Local variable declaration has been previsouly separated as 'pure declaration' first, followed by 'store' later on (done in MoveVariablesInFront3)
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
    
        virtual void visit(RetInst* inst)
        {
            if (inst->fResult) {
                *fOut << "(return ";
                inst->fResult->accept(this);
                *fOut << ")";
            }
            //EndLine();
        }
    
        virtual void generateFunDefArgs(DeclareFunInst* inst)
        {
            list<NamedTyped*>::const_iterator it;
            int size = inst->fType->fArgsTypes.size(), i = 0;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                *fOut << "(param $" << (*it)->fName << " " << type2String((*it)->getType()) << ")";
                if (i < size - 1) *fOut << " ";
            }
            *fOut << " (result " << type2String(inst->fType->getType()) << ")";
        }
    
        virtual void generateFunDefBody(DeclareFunInst* inst)
        {
            if (inst->fCode->fCode.size() == 0) {
                // Pure prototype
            } else {
                // Function body
                fTab++;
                tab(fTab, *fOut);
                inst->fCode->accept(this);
                fTab--;
                tab(fTab, *fOut);
            }
        }
    
        virtual void generateFunCallArgs(list<ValueInst*>::const_iterator beg, list<ValueInst*>::const_iterator end, int size)
        {
            list<ValueInst*>::const_iterator it = beg;
            int i = 0;
            for (it = beg; it != end; it++, i++) {
                // Compile argument
                (*it)->accept(this);
                if (i < size - 1) *fOut << " ";
            }
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
                MathFunDesc desc = fMathLibTable[inst->fName];
                
                if (desc.fMode == MathFunDesc::Gen::kExtMath || desc.fMode == MathFunDesc::Gen::kExtAsm) {
                    tab(fTab, *fOut);
                    if (desc.fMode == MathFunDesc::Gen::kExtMath) {
                        *fOut << "(import $" << inst->fName << " \"global.Math\" " "\"" << desc.fName << "\" (param ";
                    } else if (desc.fMode == MathFunDesc::Gen::kExtAsm) {
                        *fOut << "(import $" << inst->fName << " \"asm2wasm\" " "\"" << desc.fName << "\" (param ";
                    } else {
                        assert(false);
                    }
                    for (int i = 0; i < desc.fArgs; i++) {
                        *fOut << (isIntType(desc.fType) ? "i32" : realStr);
                        if (i < desc.fArgs - 1) *fOut << " ";
                    }
                    *fOut << ") (result " << (isIntType(desc.fType) ? "i32" : realStr) << "))";
                }
                
                /*
                if (fMathLibTable[inst->fName] != "manual" && fMathLibTable[inst->fName] != "wasm") {
                    tab(fTab, *fOut);
                    // Two arguments functions
                    if (fMathLibTable[inst->fName] == "fmod" || fMathLibTable[inst->fName] == "pow") {
                        *fOut << "(import $" << inst->fName << " \"global.Math\" " "\"" << fMathLibTable[inst->fName]
                              << "\"" << " (param " << realStr << " " << realStr << ") (result " << realStr << "))";
                    } else {
                        // One argument
                        *fOut << "(import $" << inst->fName << " \"global.Math\" " "\"" << fMathLibTable[inst->fName]
                              << "\"" << " (param " << realStr << ") (result " << realStr << "))";
                    }
                }
                */
                
            } else {
                // Prototype
                tab(fTab, *fOut); *fOut << "(func $" << generateFunName(inst->fName) << " ";
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
                if (fFastMemory) {
                    *fOut << "(i32.const " << tmp.fOffset << ")";
                } else {
                    *fOut << "(i32.add (get_local $dsp) (i32.const " << tmp.fOffset << "))";
                }
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
                /*
                *fOut << "(i32.add (i32.add (get_local $dsp) (i32.const " << tmp.fOffset << ")) (i32.shl ";
                indexed->fIndex->accept(this);
                *fOut << " (i32.const " << offStr << ")))";
                 
                */
                
                IntNumInst* num;
                if ((num = dynamic_cast<IntNumInst*>(indexed->fIndex))) {
                    // Index can be computed at compile time
                    if (fFastMemory) {
                        *fOut << "(i32.const " << (tmp.fOffset + (num->fNum << offStrNum)) << ")";
                    } else {
                        *fOut << "(i32.add (get_local $dsp) (i32.const " << (tmp.fOffset + (num->fNum << offStrNum)) << "))";
                    }
                } else {
                    // Otherwise generate index computation code
                    if (fFastMemory) {
                        *fOut << "(i32.add (i32.const " << tmp.fOffset << ") (i32.shl ";
                        indexed->fIndex->accept(this);
                        *fOut << " (i32.const " << offStr << ")))";
                    } else {
                        *fOut << "(i32.add (get_local $dsp) (i32.add (i32.const " << tmp.fOffset << ") (i32.shl ";
                        indexed->fIndex->accept(this);
                        *fOut << " (i32.const " << offStr << "))))";
                    }
                }
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

        // Special case for min/max
        void generateMinMax(const list<ValueInst*>& args, const string& fun)
        {
            list<ValueInst*>::iterator it;
            ValueInst* arg1 = *(args.begin());
            arg1->accept(&fTypingVisitor);
            if (isIntType(fTypingVisitor.fCurType)) {
                // Using manually generated min/max
                *fOut  << "(call $" << fun << " ";
            } else {
                *fOut << "(" << realStr << "." << fun << " ";
            }
        }

        // Generate standard funcall (not 'method' like funcall...)
        virtual void visit(FunCallInst* inst)
        {
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                MathFunDesc desc = fMathLibTable[inst->fName];
                if (desc.fMode == MathFunDesc::Gen::kWasm) {
                    // Special case for min/max
                    if (startWith(desc.fName, "min") || startWith(desc.fName, "max")) {
                        generateMinMax(inst->fArgs, desc.fName);
                    } else {
                        *fOut << "(" << realStr << "." << desc.fName << " ";
                    }
                } else {
                    *fOut  << "(call $" << inst->fName << " ";
                }
                
                /*
                if (inst->fName == "min") {
                    // TODO
                    ///assert(false);
                } else if (inst->fName == "max") {
                    // TODO
                    //assert(false);
                } else {
                    *fOut << "(" << realStr << "." << inst->fName << " ";
                }
                */
                
            } else {
                *fOut  << "(call $" << inst->fName << " ";
            }
            generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
            *fOut << ")";
        }
    
        // Conditional : select
        virtual void visit(Select2Inst* inst)
        {
            *fOut << "(select ";
            inst->fThen->accept(this);
            inst->fElse->accept(this);
            // Condition is last item
            inst->fCond->accept(this);
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
            string name = inst->getLoopName();
            
            *fOut << "(loop $for-in-" << name << " ";
            fTab++;
                tab(fTab, *fOut);
                *fOut << "(block $for-out-" << name << " ";
                    fTab++;
            
                    // Loop counter test and possibly branch out
                    tab(fTab, *fOut);
                    *fOut << "(if (i32.eqz ";
                    inst->fEnd->accept(this);
                    *fOut << ") (br $for-out-" << name << "))";
                    
                    // Loop code
                    tab(fTab, *fOut);
                    inst->fCode->accept(this);
                    // Loop increment
                    inst->fIncrement->accept(this);
            
                    /*
                    // Loop counter test and possibly branch out
                    *fOut << "(if ";
                    inst->fEnd->accept(this);
                    *fOut << " (br $for-in-" << name << ") (br $for-out-" << name << "))";
                    */
            
                    // Branch to loop label
                    *fOut << "(br $for-in-" << name << ")";
            
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
