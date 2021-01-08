/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <ostream>

#include "was_instructions.hh"

#define realStr ((gGlobal->gFloatSize == 1) ? "f32" : ((gGlobal->gFloatSize == 2) ? "f64" : ""))
#define offStr ((gGlobal->gFloatSize == 1) ? "2" : ((gGlobal->gFloatSize == 2) ? "3" : ""))

class WASTInstVisitor : public TextInstVisitor, public WASInst {
   private:
    string type2String(Typed::VarType type)
    {
        if (isIntOrPtrType(type) || isBoolType(type)) {
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
        bool dot   = false;
        int  e_pos = -1;
        for (size_t i = 0; i < str.size(); i++) {
            if (str[i] == '.') {
                dot = true;
                break;
            } else if (str[i] == 'e') {
                e_pos = int(i);
                break;
            }
        }

        if (e_pos >= 0) {
            return str.insert(e_pos, 1, '.');
        } else {
            return (dot) ? str : (str + ".");
        }
    }

    virtual void EndLine(char end_line = ';')
    {
        if (fFinishLine) {
            tab(fTab, *fOut);
        }
    }

    // Special version without termination
    template <class T>
    string checkReal(T val)
    {
        if (std::isinf(val)) {
            return "inf";
        } else {
            std::stringstream num;
            num << setprecision(numeric_limits<T>::max_digits10) << val;
            return ensureFloat(num.str());
        }
    }

   public:
    using TextInstVisitor::visit;

    WASTInstVisitor(std::ostream* out, bool fast_memory, int tab = 0)
        : TextInstVisitor(out, ".", tab), WASInst(fast_memory)
    {
    }

    virtual ~WASTInstVisitor() {}

    virtual void visit(DeclareVarInst* inst)
    {
        Address::AccessType access      = inst->fAddress->getAccess();
        bool                is_struct   = (access & Address::kStruct) || (access & Address::kStaticStruct);
        ArrayTyped*         array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        string              name        = inst->fAddress->getName();

        // fSampleRate may appear several time (in subcontainers and in main DSP)
        if (name != "fSampleRate") {
            faustassert(fFieldTable.find(name) == fFieldTable.end());
        }

        if (array_typed && array_typed->fSize > 1) {
            if (is_struct) {
                fFieldTable[name] = MemoryDesc(-1, fStructOffset, array_typed->fSize, array_typed->fType->getType());
                // Always use biggest size so that int/real access are correctly aligned
                fStructOffset += (array_typed->fSize * gGlobal->audioSampleSize());
            } else {
                *fOut << "(local $" << name << " " << type2String(inst->fType->getType()) << ")";
                EndLine();
            }
        } else {
            if (is_struct) {
                fFieldTable[name] = MemoryDesc(-1, fStructOffset, 1, inst->fType->getType());
                // Always use biggest size so that int/real access are correctly aligned
                fStructOffset += gGlobal->audioSampleSize();
            } else {
                *fOut << "(local $" << name << " " << type2String(inst->fType->getType()) << ")";
                // Local variable declaration has been previously separated as 'pure declaration' first,
                // followed by 'store' later on (done in MoveVariablesInFront3)
                faustassert(inst->fValue == nullptr);
                EndLine();
            }
        }
    }

    virtual void visitAux(RetInst* inst, bool gen_empty)
    {
        if (inst->fResult) {
            *fOut << "(return ";
            inst->fResult->accept(this);
            *fOut << ")";
        } else if (gen_empty) {
            *fOut << "(return)";
        }
    }

    virtual void generateFunDefArgs(DeclareFunInst* inst)
    {
        list<NamedTyped*>::const_iterator it;
        size_t                            size = inst->fType->fArgsTypes.size(), i = 0;
        for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
            *fOut << "(param $" << (*it)->fName << " " << type2String((*it)->getType()) << ")";
            if (i < size - 1) *fOut << " ";
        }
        if (inst->fType->getType() != Typed::kVoid) {
            *fOut << " (result " << type2String(inst->getResType()) << ")";
        }
    }

    virtual void generateFunDefBody(DeclareFunInst* inst)
    {
        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        fTab--;
    }

    virtual void generateFunCallArgs(list<ValueInst*>::const_iterator beg, list<ValueInst*>::const_iterator end,
                                     int size)
    {
        list<ValueInst*>::const_iterator it = beg;
        int                              i  = 0;
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
            fFunctionSymbolTable[inst->fName] = true;
        }

        // Math library functions are part of the 'global' module, 'fmod', 'log10' and 'remainder' will be manually
        // generated
        if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
            MathFunDesc desc = fMathLibTable[inst->fName];
            if (desc.fMode == MathFunDesc::Gen::kExtMath || desc.fMode == MathFunDesc::Gen::kExtWAS) {
                tab(fTab, *fOut);
                // Possibly map fastmath functions, emcc compiled functions are prefixed with '_'
                *fOut << "(import $" << inst->fName << " \"env\" \""
                      << "_" << gGlobal->getMathFunction(inst->fName) << "\" (param ";
                for (int i = 0; i < desc.fArgs; i++) {
                    *fOut << type2String(desc.fTypeIn);
                    if (i < desc.fArgs - 1) *fOut << " ";
                }
                *fOut << ") (result " << type2String(desc.fTypeOut) << "))";
                return;
            }
        }

        // Complete function
        if (inst->fCode->fCode.size() != 0) {
            tab(fTab, *fOut);
            *fOut << "(func $" << generateFunName(inst->fName) << " ";
            generateFunDefArgs(inst);
            generateFunDefBody(inst);
            tab(fTab, *fOut);
            *fOut << ")";
        }
    }

    virtual void visit(LoadVarInst* inst)
    {
        fTypingVisitor.visit(inst);
        Typed::VarType        type = fTypingVisitor.fCurType;
        Address::AccessType access = inst->fAddress->getAccess();
        string                name = inst->fAddress->getName();
        IndexedAddress*    indexed =  dynamic_cast<IndexedAddress*>(inst->fAddress);

        if (access & Address::kStruct || access & Address::kStaticStruct || indexed) {
            
            int offset;
            if ((offset = getConstantOffset(inst->fAddress)) > 0) {
                if (isRealType(type)) {
                    *fOut << "(" << realStr << ".load offset=";
                } else if (isInt64Type(type)) {
                    *fOut << "(i64.load offset=";
                } else if (isInt32Type(type) || isPtrType(type)) {
                    *fOut << "(i32.load offset=";
                } else {
                    faustassert(false);
                }
                *fOut << offset << " (i32.const 0))";
            } else {
                if (isRealType(type)) {
                    *fOut << "(" << realStr << ".load ";
                } else if (isInt64Type(type)) {
                    *fOut << "(i64.load ";
                } else if (isInt32Type(type) || isPtrType(type)) {
                    *fOut << "(i32.load ";
                } else {
                    faustassert(false);
                }
                inst->fAddress->accept(this);
                *fOut << ")";
            }
        
        } else {
            *fOut << "(local.get $" << name << ")";
        }
    }

    virtual void visit(TeeVarInst* inst)
    {
        // 'tee_local' is generated the first time the variable is used
        // All future access simply use a local.get
        string name = inst->fAddress->getName();

        if (fTeeMap.find(name) == fTeeMap.end()) {
            *fOut << "(tee_local $" << name << " ";
            inst->fValue->accept(this);
            *fOut << ")";
            fTeeMap[name] = true;
        } else {
            *fOut << "(local.get $" << name << ")";
        }
    }

    virtual void visit(StoreVarInst* inst)
    {
        inst->fValue->accept(&fTypingVisitor);
        Typed::VarType      type   = fTypingVisitor.fCurType;
        Address::AccessType access = inst->fAddress->getAccess();
  
        if (access & Address::kStruct || access & Address::kStaticStruct ||
            dynamic_cast<IndexedAddress*>(inst->fAddress)) {
            int offset;
            if ((offset = getConstantOffset(inst->fAddress)) > 0) {
                if (isRealType(type) || isRealPtrType(type)) {
                    *fOut << "(" << realStr << ".store offset=";
                } else if (isInt64Type(type)) {
                    *fOut << "(i64.store offset=";
                } else if (isInt32Type(type) || isPtrType(type) || isBoolType(type)) {
                    *fOut << "(i32.store offset=";
                } else {
                    faustassert(false);
                }
                *fOut << offset << " (i32.const 0) ";
                inst->fValue->accept(this);
                *fOut << ")";
            } else {
                if (isRealType(type) || isRealPtrType(type)) {
                    *fOut << "(" << realStr << ".store ";
                } else if (isInt64Type(type)) {
                    *fOut << "(i64.store ";
                } else if (isInt32Type(type) || isPtrType(type) || isBoolType(type)) {
                    *fOut << "(i32.store ";
                } else {
                    faustassert(false);
                }
                inst->fAddress->accept(this);
                *fOut << " ";
                inst->fValue->accept(this);
                *fOut << ")";
            }
        } else {
            *fOut << "(local.set $" << inst->fAddress->getName() << " ";
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
                *fOut << "(i32.add (local.get $dsp) (i32.const " << tmp.fOffset << "))";
            }
        } else {
            *fOut << "(local.get $" << named->getName() << ")";
        }
    }

    virtual void visit(IndexedAddress* indexed)
    {
        // TO CHECK : size of memory ptr ?

        // HACK : completely adhoc code for inputs/outputs...
        if ((startWith(indexed->getName(), "inputs") || startWith(indexed->getName(), "outputs"))) {
            // Since indexed->fIndex is always a known constant value, offset can be directly generated
            Int32NumInst* num = dynamic_cast<Int32NumInst*>(indexed->fIndex);
            faustassert(num);
            *fOut << "(i32.add (local.get $" << indexed->getName() << ") (i32.const " << (num->fNum << 2) << "))";
            // HACK : completely adhoc code for input/output...
        } else if ((startWith(indexed->getName(), "input") || startWith(indexed->getName(), "output"))) {
            // If 'i' loop variable moves in bytes, save index code generation of input/output
            if (gGlobal->gLoopVarInBytes) {
                *fOut << "(i32.add (local.get $" << indexed->getName() << ") ";
                indexed->fIndex->accept(this);
                *fOut << ")";
            } else {
                *fOut << "(i32.add (local.get $" << indexed->getName() << ") (i32.shl ";
                indexed->fIndex->accept(this);
                // Force "output" access to be coherent with fSubContainerType (integer or real)
                if (fSubContainerType == kInt) {
                    *fOut << " (i32.const 2)))";
                } else {
                    *fOut << " (i32.const " << offStr << ")))";
                }
            }
        } else {
            /*
             Fields in DSP struct are accessed using 'dsp' and an offset
             IndexedAddress is also used for soundfiles (pointer + field index)
            */
            if (fFieldTable.find(indexed->getName()) != fFieldTable.end()) {
                MemoryDesc    tmp = fFieldTable[indexed->getName()];
                Int32NumInst* num;
                if ((num = dynamic_cast<Int32NumInst*>(indexed->fIndex))) {
                    // Index can be computed at compile time
                    if (fFastMemory) {
                        *fOut << "(i32.const " << (tmp.fOffset + (num->fNum << offStrNum)) << ")";
                    } else {
                        *fOut << "(i32.add (local.get $dsp) (i32.const " << (tmp.fOffset + (num->fNum << offStrNum))
                              << "))";
                    }
                } else {
                    // Otherwise generate index computation code
                    if (fFastMemory) {
                        // Micro optimization if the field is actually the first one in the structure
                        if (tmp.fOffset == 0) {
                            *fOut << "(i32.shl ";
                            indexed->fIndex->accept(this);
                            *fOut << " (i32.const " << offStr << "))";
                        } else {
                            *fOut << "(i32.add (i32.const " << tmp.fOffset << ") (i32.shl ";
                            indexed->fIndex->accept(this);
                            *fOut << " (i32.const " << offStr << ")))";
                        }
                    } else {
                        // Micro optimization if the field is actually the first one in the structure
                        if (tmp.fOffset == 0) {
                            *fOut << "(i32.add (local.get $dsp) (i32.shl ";
                            indexed->fIndex->accept(this);
                            *fOut << " (i32.const " << offStr << ")))";
                        } else {
                            *fOut << "(i32.add (local.get $dsp) (i32.add (i32.const " << tmp.fOffset << ") (i32.shl ";
                            indexed->fIndex->accept(this);
                            *fOut << " (i32.const " << offStr << "))))";
                        }
                    }
                }
            } else {
                // Local variable
                Int32NumInst* num;
                if ((num = dynamic_cast<Int32NumInst*>(indexed->fIndex))) {
                    // Hack for 'soundfile'
                    DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
                    *fOut << "(i32.add (local.get " << indexed->getName();
                    if (struct_type) {
                        *fOut << ") (i32.const " << struct_type->fType->getOffset(num->fNum);
                    } else {
                        *fOut << ") (i32.const " << (num->fNum << offStrNum);
                    }
                    *fOut << "))";
                } else {
                    *fOut << "(i32.add (local.get " << indexed->getName() << ") (i32.shl ";
                    indexed->fIndex->accept(this);
                    *fOut << " (i32.const " << offStr << ")))";
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

    virtual void visit(BoolNumInst* inst) { faustassert(false); }

    virtual void visit(Int32NumInst* inst)
    {
        fTypingVisitor.visit(inst);
        *fOut << "(i32.const " << inst->fNum << ")";
    }

    virtual void visit(Int64NumInst* inst)
    {
        fTypingVisitor.visit(inst);
        *fOut << "(i64.const " << inst->fNum << ")";
    }

    // Numerical computation
    void visitAuxInt(BinopInst* inst, Typed::VarType type)
    {
        *fOut << "(";
        if (isInt32Type(type) || isBoolType(type)) {
            *fOut << gBinOpTable[inst->fOpcode]->fNameWastInt32;
        } else if (isInt64Type(type)) {
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
        if (isFloatType(type)) {
            *fOut << gBinOpTable[inst->fOpcode]->fNameWastFloat;
        } else if (isDoubleType(type)) {
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
            } else if (isBoolType(type1) && isBoolType(type2)) {
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
     
        switch (inst->fType->getType()) {
            case Typed::kInt32:
                if (isInt32Type(type)) {
                    // std::cout << "CastInst : cast to int, but arg already int !" << std::endl;
                    inst->fInst->accept(this);
                } else if (isInt64Type(type)) {
                    *fOut << "(i32.wrap_i64 ";
                    inst->fInst->accept(this);
                    *fOut << ")";
                } else {
                    *fOut << "(i32.trunc_" << realStr << "_s ";
                    inst->fInst->accept(this);
                    *fOut << ")";
                }
                break;
            
             case Typed::kInt64:
                faustassert(false);
                break;
                
            case Typed::kFloat:
            case Typed::kDouble:
                if (isRealType(type)) {
                    // std::cout << "CastInst : cast to real, but arg already real !" << std::endl;
                    inst->fInst->accept(this);
                } else if (isInt64Type(type)) {
                    *fOut << "(" << realStr << ".convert_i64_s ";
                    inst->fInst->accept(this);
                    *fOut << ")";
                } else if (isInt32Type(type) || isBoolType(type)) {
                    *fOut << "(" << realStr << ".convert_i32_s ";
                    inst->fInst->accept(this);
                    *fOut << ")";
                } else {
                    faustassert(false);
                }
                break;
                
            default:
                faustassert(false);
                break;
        }

        fTypingVisitor.visit(inst);
    }

    virtual void visit(BitcastInst* inst)
    {
        switch (inst->fType->getType()) {
            case Typed::kInt32:
                *fOut << "(i32.reinterpret_" << realStr << " ";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            case Typed::kInt64:
                *fOut << "(i64.reinterpret_" << realStr << " ";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            case Typed::kFloat:
                *fOut << "(" << realStr << ".reinterpret_i32 ";
                inst->fInst->accept(this);
                *fOut << ")";
                break;
            case Typed::kDouble:
                *fOut << "(" << realStr << ".reinterpret_i64 ";
                inst->fInst->accept(this);
                *fOut << ")";
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
        ValueInst*                 arg1 = *(args.begin());
        arg1->accept(&fTypingVisitor);
        if (isIntType(fTypingVisitor.fCurType)) {
            // Using manually generated min/max
            *fOut << "(call $" << fun << " ";
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
                if (checkMinMax(desc.fName)) {
                    generateMinMax(inst->fArgs, desc.fName);
                } else {
                    *fOut << "(" << realStr << "." << desc.fName << " ";
                }
            } else {
                *fOut << "(call $" << inst->fName << " ";
            }
        } else {
            *fOut << "(call $" << inst->fName << " ";
        }
        generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), (int)inst->fArgs.size());
        *fOut << ")";
    }
    
    /*
    // Select that computes both branches
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
        if (isInt64Type(fTypingVisitor.fCurType)) {
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
    */

    // Select that only computes one branch
    virtual void visit(Select2Inst* inst)
    {
        *fOut << "(if ";
        // Result type
        inst->fThen->accept(&fTypingVisitor);
        *fOut << "(result " << type2String(fTypingVisitor.fCurType) << ") ";
        
        // Compile 'cond'
        inst->fCond->accept(&fTypingVisitor);
        // Possibly convert i64 to i32
        if (isInt64Type(fTypingVisitor.fCurType)) {
            // Compare to 0
            *fOut << "(i64.ne ";
            inst->fCond->accept(this);
            *fOut << "(i64.const 0))";
        } else {
            inst->fCond->accept(this);
        }
        // Compile 'then'
        *fOut << " ";
        inst->fThen->accept(this);
        // Compile 'else'
        *fOut << " ";
        inst->fElse->accept(this);
        *fOut << ")";
        
        fTypingVisitor.visit(inst);
    }
 
    // Conditional : if
    virtual void visit(IfInst* inst)
    {
        *fOut << "(if ";
        inst->fCond->accept(&fTypingVisitor);
        // Possibly convert i64 to i32
        if (isInt64Type(fTypingVisitor.fCurType)) {
            // Compare to 0
            *fOut << "(i64.ne ";
            inst->fCond->accept(this);
            *fOut << "(i64.const 0))";
        } else {
            inst->fCond->accept(this);
        }
        fTab++;
        tab(fTab, *fOut);
        *fOut << "(block ";
        inst->fThen->accept(this);
        *fOut << ")";
        if (inst->fElse->fCode.size() > 0) {
            tab(fTab, *fOut);
            *fOut << "(block ";
            inst->fElse->accept(this);
            *fOut << ")";
        }
        fTab--;
        tab(fTab, *fOut);
        *fOut << ")";
        tab(fTab, *fOut);

        fTypingVisitor.visit(inst);
    }

    // Loop : beware: compiled loop don't work with an index of 0
    virtual void visit(ForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) return;

        // Local variables declaration including the loop counter have been moved outside of the loop
        string name = inst->getName();

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
        back(1, *fOut);
        *fOut << ")";
        fTab--;
        tab(fTab, *fOut);
        *fOut << ")";
        tab(fTab, *fOut);
    }

};

#endif
