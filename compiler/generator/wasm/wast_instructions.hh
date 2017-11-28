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

#ifndef _WAST_INSTRUCTIONS_H
#define _WAST_INSTRUCTIONS_H

#include "was_instructions.hh"

using namespace std;

#define realStr ((gGlobal->gFloatSize == 1) ? "f32" : ((gGlobal->gFloatSize == 2) ? "f64" : ""))
#define offStr ((gGlobal->gFloatSize == 1) ? "2" : ((gGlobal->gFloatSize == 2) ? "3" : ""))

class WASTInstVisitor : public TextInstVisitor, public WASInst {
    
     private:
    
        string type2String(Typed::VarType type)
        {
            if (isIntOrPtrType(type)) {
                return "i32";
            } else if (type == Typed::kFloat) {
                return "f32";
            } else if (type == Typed::kDouble) {
                return "f64";
            } else {
                faustassert(false);
                return "";
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
    
        virtual void EndLine()
        {
            if (fFinishLine) {
                tab(fTab, *fOut);
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
		using TextInstVisitor::visit;

        WASTInstVisitor(std::ostream* out, bool fast_memory, int tab = 0)
            :TextInstVisitor(out, ".", tab), WASInst(fast_memory)
        {}

        virtual ~WASTInstVisitor()
        {}
    
        virtual void visit(DeclareVarInst* inst)
        {
            bool is_struct = (inst->fAddress->getAccess() & Address::kStruct) || (inst->fAddress->getAccess() & Address::kStaticStruct);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
            
            if (array_typed && array_typed->fSize > 1) {
                if (is_struct) {
                    fFieldTable[inst->fAddress->getName()] = MemoryDesc(fStructOffset, array_typed->fSize, array_typed->fType->getType());
                    fStructOffset += (array_typed->fSize * audioSampleSize()); // Always use biggest size so that int/real access are correctly aligned
                } else {
                    // Should never happen...
                    faustassert(false);
                }
            } else {
                if (is_struct) {
                    fFieldTable[inst->fAddress->getName()] = MemoryDesc(fStructOffset, 1, inst->fType->getType());
                    fStructOffset += audioSampleSize(); // Always use biggest size so that int/real access are correctly aligned
                } else {
                    *fOut << "(local $" << inst->fAddress->getName() << " " << type2String(inst->fType->getType()) << ")";
                    // Local variable declaration has been previsouly separated as 'pure declaration' first, followed by 'store' later on (done in MoveVariablesInFront3)
                    faustassert(inst->fValue == nullptr);
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
        }
    
        virtual void generateFunDefArgs(DeclareFunInst* inst)
        {
            list<NamedTyped*>::const_iterator it;
            size_t size = inst->fType->fArgsTypes.size(), i = 0;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                *fOut << "(param $" << (*it)->fName << " " << type2String((*it)->getType()) << ")";
                if (i < size - 1) *fOut << " ";
            }
            if (inst->fType->getType() != Typed::kVoid) {
                *fOut << " (result " << type2String(inst->fType->getType()) << ")";
            }
        }
    
        virtual void generateFunDefBody(DeclareFunInst* inst)
        {
            fTab++;
            tab(fTab, *fOut);
            inst->fCode->accept(this);
            fTab--;
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
            if (inst->fName != "min_i" && inst->fName != "max_i") {  // adhoc code for now otherwise min_i/max_i are not always correctly generated...
                if (fFunctionSymbolTable.find(inst->fName) != fFunctionSymbolTable.end()) {
                    return;
                } else {
                    fFunctionSymbolTable[inst->fName] = 1;
                }
            }
            
            // Math library functions are part of the 'global' module, 'fmod', 'log10' and 'remainder' will be manually generated
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                MathFunDesc desc = fMathLibTable[inst->fName];
                if (desc.fMode == MathFunDesc::Gen::kExtMath || desc.fMode == MathFunDesc::Gen::kExtWAS) {
                    tab(fTab, *fOut);
                    if (desc.fMode == MathFunDesc::Gen::kExtMath || desc.fMode == MathFunDesc::Gen::kExtWAS) {
                        // Possibly map fastmath functions, emcc compiled functions are prefixed with '_'
                        *fOut << "(import $" << inst->fName << " \"env\" \"" << "_" << gGlobal->getMathFunction(inst->fName) << "\" (param ";
                    } else {
                        faustassert(false);
                    }
                    
                    for (int i = 0; i < desc.fArgs; i++) {
                        *fOut << (isIntType(desc.fType) ? "i32" : realStr);
                        if (i < desc.fArgs - 1) *fOut << " ";
                    }
                    *fOut << ") (result " << (isIntType(desc.fType) ? "i32" : realStr) << "))";
                    return;
                }
            }
                
            // Complete function
            if (inst->fCode->fCode.size() != 0) {
                tab(fTab, *fOut); *fOut << "(func $" << generateFunName(inst->fName) << " ";
                generateFunDefArgs(inst);
                generateFunDefBody(inst);
                tab(fTab, *fOut); *fOut << ")";
            }
        }
    
        virtual void visit(LoadVarInst* inst)
        {
            fTypingVisitor.visit(inst);
            Typed::VarType type = fTypingVisitor.fCurType;
            
            if (inst->fAddress->getAccess() & Address::kStruct
                || inst->fAddress->getAccess() & Address::kStaticStruct
                || dynamic_cast<IndexedAddress*>(inst->fAddress)) {
                
                int offset;
                if ((offset = getConstantOffset(inst->fAddress)) > 0) {
                    if (isRealType(type) || isRealPtrType(type)) {
                        *fOut << "(" << realStr << ".load offset=";
                    } else {
                        *fOut << "(i32.load offset=";
                    }
                    *fOut << offset << " (i32.const 0))";
                } else {
                    if (isRealType(fTypingVisitor.fCurType) || isRealPtrType(fTypingVisitor.fCurType)) {
                        *fOut << "(" << realStr << ".load ";
                    } else {
                        *fOut << "(i32.load ";
                    }
                    inst->fAddress->accept(this);
                    *fOut << ")";
                }
                
            } else {
                *fOut << "(get_local $" << inst->fAddress->getName() << ")";
            }
        }
    
        virtual void visit(TeeVarInst* inst)
        {
            // 'tee_local' is generated the first time the variable is used
            // All future access simply use a get_local
            if (fTeeMap.find(inst->fAddress->getName()) == fTeeMap.end()) {
                *fOut << "(tee_local $" << inst->fAddress->getName() << " ";
                inst->fValue->accept(this);
                *fOut << ")";
                fTeeMap[inst->fAddress->getName()] = true;
            } else {
                *fOut << "(get_local $" << inst->fAddress->getName() << ")";
            }
        }

        virtual void visit(StoreVarInst* inst)
        {
            inst->fValue->accept(&fTypingVisitor);
            Typed::VarType type = fTypingVisitor.fCurType;

            if (inst->fAddress->getAccess() & Address::kStruct
                || inst->fAddress->getAccess() & Address::kStaticStruct
                || dynamic_cast<IndexedAddress*>(inst->fAddress)) {
       
                int offset;
                if ((offset = getConstantOffset(inst->fAddress)) > 0) {
                    if (isRealType(type) || isRealPtrType(type)) {
                        *fOut << "(" << realStr << ".store offset=";
                    } else {
                        *fOut << "(i32.store offset=";
                    }
                    *fOut << offset << " (i32.const 0) ";
                    inst->fValue->accept(this);
                    *fOut << ")";
                } else {
                    if (isRealType(type) || isRealPtrType(type)) {
                        *fOut << "(" << realStr << ".store ";
                    } else {
                        *fOut << "(i32.store ";
                    }
                    inst->fAddress->accept(this);
                    *fOut << " ";
                    inst->fValue->accept(this);
                    *fOut << ")";
                }
                
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
                faustassert(fFieldTable.find(named->getName()) != fFieldTable.end());
                MemoryDesc tmp = fFieldTable[named->getName()];
                if (fFastMemory) {
                    *fOut << "(i32.const " << tmp.fOffset << ")";
                } else {
                    *fOut << "(i32.add (get_local $dsp) (i32.const " << tmp.fOffset << "))";
                }
            } else {
                *fOut << "(get_local $" << named->getName() << ")";
            }
        }
    
        virtual void visit(IndexedAddress* indexed)
        {
            // TO CHECK : size of memory ptr ?
            
            // HACK : completely adhoc code for inputs/outputs...
            if ((startWith(indexed->getName(), "inputs") || startWith(indexed->getName(), "outputs"))) {
                // Since indexed->fIndex is always a known constant value, offset can be directly generated
                Int32NumInst* num = dynamic_cast<Int32NumInst*>(indexed->fIndex); faustassert(num);
                *fOut << "(i32.add (get_local $" << indexed->getName() << ") (i32.const " << (num->fNum << 2) << "))";
            // HACK : completely adhoc code for input/output...
            } else if ((startWith(indexed->getName(), "input") || startWith(indexed->getName(), "output"))) {
                // If 'i' loop variable moves in bytes, save index code generation of input/output
                if (gGlobal->gLoopVarInBytes) {
                    *fOut << "(i32.add (get_local $" << indexed->getName() << ") ";
                    indexed->fIndex->accept(this);
                    *fOut << ")";
                } else {
                    *fOut << "(i32.add (get_local $" << indexed->getName() << ") (i32.shl ";
                    indexed->fIndex->accept(this);
                    // Force "output" access to be coherent with fSubContainerType (integer or real)
                    if (fSubContainerType == kInt) {
                        *fOut << " (i32.const 2)))";
                    } else {
                        *fOut << " (i32.const " << offStr << ")))";
                    }
                }
            } else {
                // Fields in struct are accessed using 'dsp' and an offset
                faustassert(fFieldTable.find(indexed->getName()) != fFieldTable.end());
                MemoryDesc tmp = fFieldTable[indexed->getName()];
                Int32NumInst* num;
                if ((num = dynamic_cast<Int32NumInst*>(indexed->fIndex))) {
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
            faustassert(false);
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
    
        virtual void visit(Int32NumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << "(i32.const " << inst->fNum << ")";
        }
    
        virtual void visit(Int64NumInst* inst)
        {
            fTypingVisitor.visit(inst);
            *fOut << "(i64.const 0x" << hex << inst->fNum << ")";
        }
    
        // Numerical computation
        void visitAuxInt(BinopInst* inst, Typed::VarType type)
        {
            *fOut << "(";
            if (type == Typed::kInt32 || type == Typed::kBool) {
                *fOut << gBinOpTable[inst->fOpcode]->fNameWastInt32;
            } else if (type == Typed::kInt64) {
                *fOut << gBinOpTable[inst->fOpcode]->fNameWastInt64;
            } else {
                faustassert(false);
            }
            *fOut << " ";
            inst->fInst1->accept(this);
            *fOut << " ";
            inst->fInst2->accept(this);
            *fOut << ")";
        }
    
        void visitAuxReal(BinopInst* inst, Typed::VarType type)
        {
            *fOut << "(";
            if (type == Typed::kFloat) {
                *fOut << gBinOpTable[inst->fOpcode]->fNameWastFloat;
            } else if (type == Typed::kDouble) {
                *fOut << gBinOpTable[inst->fOpcode]->fNameWastDouble;
            } else {
                faustassert(false);
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
                // type1 is kInt
                inst->fInst2->accept(&fTypingVisitor);
                Typed::VarType type2 = fTypingVisitor.fCurType;
                if (isRealType(type2)) {
                    visitAuxReal(inst, type2);
                } else if (isIntType(type1) || isIntType(type2)) {
                    visitAuxInt(inst, type2);
                } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                    visitAuxInt(inst, type1);
                } else {
                    // Should never happen...
                    faustassert(false);
                }
            }
            
            fTypingVisitor.visit(inst);
        }

        virtual void visit(::CastInst* inst)
        {
            inst->fInst->accept(&fTypingVisitor);
            Typed::VarType type = fTypingVisitor.fCurType;
            
            if (inst->fType->getType() == Typed::kInt32) {
                if (type == Typed::kInt32) {
                    //std::cout << "CastInst : cast to int, but arg already int !" << std::endl;
                    inst->fInst->accept(this);
                } else {
                    *fOut << "(i32.trunc_s/" << realStr << " ";
                    inst->fInst->accept(this);
                    *fOut << ")";
                }
            } else {
                if (isRealType(type)) {
                    //std::cout << "CastInst : cast to real, but arg already real !" << std::endl;
                    inst->fInst->accept(this);
                } else {
                    *fOut << "(" << realStr << ".convert_s/i32 ";
                    inst->fInst->accept(this);
                    *fOut << ")";
                }
            }
            
            fTypingVisitor.visit(inst);
        }
    
        virtual void visit(BitcastInst* inst)
        {
            switch (inst->fType->getType()) {
                case Typed::kInt32:
                    *fOut << "(i32.reinterpret/" << realStr << " "; inst->fInst->accept(this); *fOut << ")";
                    break;
                case Typed::kInt64:
                    *fOut << "(i64.reinterpret/" << realStr << " "; inst->fInst->accept(this); *fOut << ")";
                    break;
                case Typed::kFloat:
                    *fOut << "(" << realStr << ".reinterpret/i32 "; inst->fInst->accept(this); *fOut << ")";
                    break;
                case Typed::kDouble:
                    *fOut << "(" << realStr << ".reinterpret/i64 "; inst->fInst->accept(this); *fOut << ")";
                    break;
                default:
                    faustassert(false);
                    break;
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
                if (desc.fMode == MathFunDesc::Gen::kWAS) {
                    // Special case for min/max
                    if (startWith(desc.fName, "min") || startWith(desc.fName, "max")) {
                        generateMinMax(inst->fArgs, desc.fName);
                    } else {
                        *fOut << "(" << realStr << "." << desc.fName << " ";
                    }
                } else {
                    *fOut  << "(call $" << inst->fName << " ";
                }
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
            *fOut << " ";
            inst->fElse->accept(this);
            *fOut << " ";
            // Condition is last item
            inst->fCond->accept(&fTypingVisitor);
            // Possibly convert i64 to i32
            if (isIntType64(fTypingVisitor.fCurType)) {
                // Compare to 0
                *fOut << "(i64.ne ";
                inst->fCond->accept(this);
                *fOut << "(i64.const 0))";
            } else {
                inst->fCond->accept(this);
            }
            *fOut << ")";
            
            fTypingVisitor.visit(inst);
        }
    
        // Conditional : if
        virtual void visit(IfInst* inst)
        {
            *fOut << "(if ";
            inst->fCond->accept(&fTypingVisitor);
            // Possibly convert i64 to i32
            if (isIntType64(fTypingVisitor.fCurType)) {
                // Compare to 0
                *fOut << "(i64.ne ";
                inst->fCond->accept(this);
                *fOut << "(i64.const 0))";
            } else {
                inst->fCond->accept(this);
            }
            *fOut << " ";
            inst->fThen->accept(this);
            *fOut << " ";
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
            
            // Init loop counter
            inst->fInit->accept(this);
            
            *fOut << "(loop $for-in-" << name << " ";
            fTab++;
                tab(fTab, *fOut);
                *fOut << "(block $for-out-" << name << " ";
            
                    // Loop code
                    fTab++;
                    tab(fTab, *fOut);
                    inst->fCode->accept(this);
            
                    // Loop counter increment
                    inst->fIncrement->accept(this);
            
                    // Loop counter test and possibly branch out
                    *fOut << "(if ";
                    inst->fEnd->accept(this);
                    *fOut << " (br $for-in-" << name << ") (br $for-out-" << name << "))";
                    tab(fTab, *fOut);
            
                fTab--;
                tab(fTab, *fOut);
                *fOut << ")";
            fTab--;
            tab(fTab, *fOut);
            *fOut << ")";
            tab(fTab, *fOut);
        }
    
};

#endif
