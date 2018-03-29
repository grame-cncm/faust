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

#ifndef _INTERPRETER_INSTRUCTIONS_H
#define _INTERPRETER_INSTRUCTIONS_H

#include "instructions.hh"
#include "typing_instructions.hh"
#include "fir_interpreter.hh"
#include "struct_manager.hh"
#include "exception.hh"

using namespace std;

template <class T>
struct InterpreterInstVisitor : public DispatchVisitor {
    
    using DispatchVisitor::visit;

    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
    */
    static map <string, FIRInstruction::Opcode> gMathLibTable;
    
    int fRealHeapOffset;    // Offset in Real HEAP    
    int fIntHeapOffset;     // Offset in Integer HEAP
    bool fCommute;          // Whether to try commutative operation reverse order generation

    map <string, MemoryDesc> fFieldTable;   // Table : field_name, { offset, size, type }

    FIRUserInterfaceBlockInstruction<T>* fUserInterfaceBlock;
    FIRBlockInstruction<T>* fCurrentBlock;

    InterpreterInstVisitor()
    {
        fUserInterfaceBlock = new FIRUserInterfaceBlockInstruction<T>();
        fCurrentBlock = new FIRBlockInstruction<T>();
        fRealHeapOffset = 0;
        fIntHeapOffset = 0;
        fCommute = true;
        initMathTable();
    }

    virtual ~InterpreterInstVisitor()
    {}

    int getFieldOffset(const string& name)
    {
        return (fFieldTable.find(name) != fFieldTable.end()) ? fFieldTable[name].fOffset : -1;
    }

    void initMathTable()
    {
        // Integer version
        gMathLibTable["abs"] = FIRInstruction::kAbs;
        gMathLibTable["min_i"] = FIRInstruction::kMin;
        gMathLibTable["max_i"] = FIRInstruction::kMax;
        
        // Float version
        gMathLibTable["fabsf"] = FIRInstruction::kAbsf;
        gMathLibTable["acosf"] = FIRInstruction::kAcosf;
        gMathLibTable["asinf"] = FIRInstruction::kAsinf;
        gMathLibTable["atanf"] = FIRInstruction::kAtanf;
        gMathLibTable["atan2f"] = FIRInstruction::kAtan2f;
        gMathLibTable["ceilf"] = FIRInstruction::kCeilf;
        gMathLibTable["cosf"] = FIRInstruction::kCosf;
        gMathLibTable["coshf"] = FIRInstruction::kCoshf;
        gMathLibTable["expf"] = FIRInstruction::kExpf;
        gMathLibTable["floorf"] = FIRInstruction::kFloorf;
        gMathLibTable["fmodf"] = FIRInstruction::kFmodf;
        gMathLibTable["logf"] =  FIRInstruction::kLogf;
        gMathLibTable["log10f"] = FIRInstruction::kLog10f;
        gMathLibTable["min_f"] = FIRInstruction::kMinf;
        gMathLibTable["max_f"] = FIRInstruction::kMaxf;
        gMathLibTable["powf"] = FIRInstruction::kPowf;
        gMathLibTable["remainderf"] = FIRInstruction::kRemReal;
        gMathLibTable["roundf"] = FIRInstruction::kRoundf;
        gMathLibTable["sinf"] = FIRInstruction::kSinf;
        gMathLibTable["sinhf"] = FIRInstruction::kSinhf;
        gMathLibTable["sqrtf"] = FIRInstruction::kSqrtf;
        gMathLibTable["tanf"] = FIRInstruction::kTanf;
        gMathLibTable["tanhf"] = FIRInstruction::kTanhf;
        
        // Double version
        gMathLibTable["fabs"] = FIRInstruction::kAbsf;
        gMathLibTable["acos"] = FIRInstruction::kAcosf;
        gMathLibTable["asin"] = FIRInstruction::kAsinf;
        gMathLibTable["atan"] = FIRInstruction::kAtanf;
        gMathLibTable["atan2"] = FIRInstruction::kAtan2f;
        gMathLibTable["ceil"] = FIRInstruction::kCeilf;
        gMathLibTable["cos"] = FIRInstruction::kCosf;
        gMathLibTable["cosh"] = FIRInstruction::kCoshf;
        gMathLibTable["exp"] = FIRInstruction::kExpf;
        gMathLibTable["floor"] = FIRInstruction::kFloorf;
        gMathLibTable["fmod"] = FIRInstruction::kFmodf;
        gMathLibTable["log"] = FIRInstruction::kLogf;
        gMathLibTable["log10"] = FIRInstruction::kLog10f;
        gMathLibTable["min_"] = FIRInstruction::kMinf;
        gMathLibTable["max_"] = FIRInstruction::kMaxf;
        gMathLibTable["pow"] = FIRInstruction::kPowf;
        gMathLibTable["remainder"] = FIRInstruction::kRemReal;
        gMathLibTable["round"] = FIRInstruction::kRoundf;
        gMathLibTable["sin"] = FIRInstruction::kSinf;
        gMathLibTable["sinh"] = FIRInstruction::kSinhf;
        gMathLibTable["sqrt"] = FIRInstruction::kSqrtf;
        gMathLibTable["tan"] = FIRInstruction::kTanf;
        gMathLibTable["tanh"] = FIRInstruction::kTanhf;
        
        // Min/max directly handled in FunCallInst
    }

    virtual void visit(AddMetaDeclareInst* inst)
    {
        MemoryDesc tmp = fFieldTable[inst->fZone];
        if (inst->fZone == "0") {
            fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(FIRInstruction::kDeclare, -1, inst->fKey, inst->fValue));
        } else {
            fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(FIRInstruction::kDeclare, tmp.fOffset, inst->fKey, inst->fValue));
        }
    }

    virtual void visit(OpenboxInst* inst)
    {
        FIRInstruction::Opcode opcode = FIRInstruction::kNop;
        switch (inst->fOrient) {
            case 0:
                opcode = FIRInstruction::kOpenVerticalBox;
                break;
            case 1:
                opcode = FIRInstruction::kOpenHorizontalBox;
                break;
            case 2:
                opcode = FIRInstruction::kOpenTabBox;
                break;
            default:
                faustassert(false);
                break;
        }
        
        fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, inst->fName));
    }

    virtual void visit(CloseboxInst* inst)
    {
        fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(FIRInstruction::kCloseBox));
    }
    
    virtual void visit(AddButtonInst* inst)
    {
        FIRInstruction::Opcode opcode;
        if (inst->fType == AddButtonInst::kDefaultButton) {
            opcode = FIRInstruction::kAddButton;
        } else {
            opcode = FIRInstruction::kAddCheckButton;
        }
        
        MemoryDesc tmp = fFieldTable[inst->fZone];
        fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, tmp.fOffset, inst->fLabel));
    }

    virtual void visit(AddSliderInst* inst)
    {
        FIRInstruction::Opcode opcode = FIRInstruction::kNop;
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                opcode = FIRInstruction::kAddHorizontalSlider;
                break;
            case AddSliderInst::kVertical:
                opcode = FIRInstruction::kAddVerticalSlider;
                break;
            case AddSliderInst::kNumEntry:
                opcode = FIRInstruction::kAddNumEntry;
                break;
            default:
                faustassert(false);
                break;
        }
    
        MemoryDesc tmp = fFieldTable[inst->fZone];
        fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, tmp.fOffset, inst->fLabel, inst->fInit, inst->fMin, inst->fMax, inst->fStep));
    }

    virtual void visit(AddBargraphInst* inst)
    {
        FIRInstruction::Opcode opcode = FIRInstruction::kNop;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                opcode = FIRInstruction::kAddHorizontalBargraph;
                break;
            case AddBargraphInst::kVertical:
                opcode = FIRInstruction::kAddVerticalBargraph;
                break;
            default:
                faustassert(false);
                break;
        }
        
        MemoryDesc tmp = fFieldTable[inst->fZone];
        fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, tmp.fOffset, inst->fLabel, inst->fMin, inst->fMax));
    }
    
    virtual void visit(AddSoundfileInst* inst)
    {
        // TODO
        throw faustexception("ERROR : AddSoundfileInst not supported for Interpreter\n");
    }
    
    virtual void visit(LabelInst* inst) {}

    // Declarations
    virtual void visit(DeclareVarInst* inst) 
    {
        // HACK : completely adhoc code for input/output using kLoadInput and kStoreOutput instructions
        if ((startWith(inst->fAddress->getName(), "input") || startWith(inst->fAddress->getName(), "output"))) {
            return;
        }
        
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        
        if (array_typed && array_typed->fSize > 1) {
            if (array_typed->fType->getType() == Typed::kInt32) {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(fIntHeapOffset, array_typed->fSize, array_typed->fType->getType());
                fIntHeapOffset += array_typed->fSize;
            } else {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(fRealHeapOffset, array_typed->fSize, array_typed->fType->getType());
                fRealHeapOffset += array_typed->fSize;
            }
        } else {
            if (inst->fType->getType() == Typed::kInt32) {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(fIntHeapOffset, 1, inst->fType->getType());
                fIntHeapOffset++;
            } else {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(fRealHeapOffset, 1, inst->fType->getType());
                fRealHeapOffset++;
            }
        }
        
        // Simulate a 'Store'
        if (inst->fValue) {
            visitStore(inst->fAddress, inst->fValue, inst->fType);
        }
    }
    
    virtual void visit(DeclareFunInst* inst) {}

    // Memory
    virtual void visit(LoadVarInst* inst)
    {
        // Compile address
        inst->fAddress->accept(this);
        
        NamedAddress* named = dynamic_cast<NamedAddress*>(inst->fAddress);
        MemoryDesc tmp = fFieldTable[inst->fAddress->getName()];
        
        if (named) {
            fCurrentBlock->push(new FIRBasicInstruction<T>((tmp.fType == Typed::kInt32)
                                ? FIRInstruction::kLoadInt : FIRInstruction::kLoadReal, 0, 0, tmp.fOffset, 0));
        } else {
            // Indexed
            IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(inst->fAddress);
            string num;
            if (startWithRes(indexed->getName(), "input", num)) {
                fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kLoadInput, 0, 0, atoi(num.c_str()), 0));
            } else {
                fCurrentBlock->push(new FIRBasicInstruction<T>((tmp.fType == Typed::kInt32)
                                    ? FIRInstruction::kLoadIndexedInt : FIRInstruction::kLoadIndexedReal, 0, 0, tmp.fOffset, tmp.fSize));
            
            }
        }
    }

    virtual void visit(LoadVarAddressInst* inst) { faustassert(false); }

    virtual void visitStore(Address* address, ValueInst* value, Typed* type = NULL)
    {
        ArrayTyped* array_typed;
        
        // Waveform array store...
        if (type && (array_typed = dynamic_cast<ArrayTyped*>(type))) {
            
            MemoryDesc tmp = fFieldTable[address->getName()];
            
            Typed::VarType ctype = array_typed->fType->getType();
            if (ctype == Typed::kInt32) {
                
                Int32ArrayNumInst* int_array = dynamic_cast<Int32ArrayNumInst*>(value);
                fCurrentBlock->push(new FIRBlockStoreIntInstruction<T>(FIRInstruction::kBlockStoreInt, tmp.fOffset, int(int_array->fNumTable.size()), int_array->fNumTable));
            
            } else if (ctype == Typed::kFloat) {
                
                FloatArrayNumInst* float_array = dynamic_cast<FloatArrayNumInst*>(value);
                fCurrentBlock->push(new FIRBlockStoreRealInstruction<T>(FIRInstruction::kBlockStoreReal,
                                                                        tmp.fOffset, int(float_array->fNumTable.size()),
                                                                        reinterpret_cast<const std::vector<T>&>(float_array->fNumTable)));
                
            } else if (ctype == Typed::kDouble) {
                
                DoubleArrayNumInst* double_array = dynamic_cast<DoubleArrayNumInst*>(value);
                fCurrentBlock->push(new FIRBlockStoreRealInstruction<T>(FIRInstruction::kBlockStoreReal,
                                                                        tmp.fOffset, int(double_array->fNumTable.size()),
                                                                        reinterpret_cast<const std::vector<T>&>(double_array->fNumTable)));
                 
            } else {
                faustassert(false);
            }
        
        // Standard store
        } else {
            
            // Compile value
            value->accept(this);
            
            NamedAddress* named = dynamic_cast<NamedAddress*>(address);
            MemoryDesc tmp = fFieldTable[address->getName()];
            
            if (named) {
                fCurrentBlock->push(new FIRBasicInstruction<T>((tmp.fType == Typed::kInt32)
                                    ? FIRInstruction::kStoreInt : FIRInstruction::kStoreReal, 0, 0, tmp.fOffset, 0));
            } else {
                IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(address);
                // Compile address
                indexed->accept(this);
                // Indexed 
                string num;
                if (startWithRes(indexed->getName(), "output", num)) {
                    fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kStoreOutput, 0, 0, atoi(num.c_str()), 0));
                } else {
                    fCurrentBlock->push(new FIRBasicInstruction<T>((tmp.fType == Typed::kInt32)
                                        ? FIRInstruction::kStoreIndexedInt : FIRInstruction::kStoreIndexedReal, 0, 0, tmp.fOffset, tmp.fSize));
                }
            }
        }
    }

    virtual void visit(StoreVarInst* inst)
    {
        visitStore(inst->fAddress, inst->fValue);
    }

    virtual void visit(ShiftArrayVarInst* inst)
    {
        MemoryDesc tmp = fFieldTable[inst->fAddress->getName()];
        fCurrentBlock->push(new FIRBasicInstruction<T>((tmp.fType == Typed::kInt32)
                                                           ? FIRInstruction::kBlockShiftInt
                                                           : FIRInstruction::kBlockShiftReal, 0, 0, tmp.fOffset + inst->fDelay, tmp.fOffset));
    }

    // Primitives : numbers
    virtual void visit(FloatNumInst* inst) 
    {
        fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kRealValue, 0, inst->fNum));
    }

    // For Waveform : done in DeclareVarInst and visitStore
    virtual void visit(FloatArrayNumInst* inst) {}

    virtual void visit(Int32NumInst* inst)
    {
        fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kInt32Value, inst->fNum, 0));
    }

    // For Waveform : done in DeclareVarInst and visitStore
    virtual void visit(Int32ArrayNumInst* inst) {}
    
    virtual void visit(BoolNumInst* inst)
    {
        fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kInt32Value, inst->fNum, 0));
    }
    
    virtual void visit(DoubleNumInst* inst) 
    {
        // Double considered real...
        fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kRealValue, 0, inst->fNum));
    }

    // For Waveform : done in DeclareVarInst and visitStore
    virtual void visit(DoubleArrayNumInst* inst) {}

    // Numerical computation
    virtual void visit(BinopInst* inst) 
    {
        bool real_t1, real_t2;
        
        if (isCommutativeOpcode(inst->fOpcode) && fCommute) {
            // Tries to order branches to allow better math optimization later on
            if ((inst->fInst1->size() < inst->fInst2->size())) {
                inst->fInst2->accept(this);
                real_t2 = fCurrentBlock->isRealInst();
                inst->fInst1->accept(this);
                real_t1 = fCurrentBlock->isRealInst();
            } else {
                inst->fInst1->accept(this);
                real_t1 = fCurrentBlock->isRealInst();
                inst->fInst2->accept(this);
                real_t2 = fCurrentBlock->isRealInst();
            }
        } else {
            inst->fInst2->accept(this);
            real_t2 = fCurrentBlock->isRealInst();
            inst->fInst1->accept(this);
            real_t1 = fCurrentBlock->isRealInst();
        }
        
        if (real_t1 || real_t2) {
            fCurrentBlock->push(new FIRBasicInstruction<T>(gBinOpTable[inst->fOpcode]->fInterpFloatInst));
        } else if (!real_t1 || !real_t2) {
            fCurrentBlock->push(new FIRBasicInstruction<T>(gBinOpTable[inst->fOpcode]->fInterpIntInst32));
        } else {
            faustassert(false);
        }
    }

    // Cast
    virtual void visit(::CastInst* inst)
    {
        inst->fInst->accept(this);
        bool real_t1 = fCurrentBlock->isRealInst();
        
        if (inst->fType->getType() == Typed::kInt32) {
            if (!real_t1) {
                //std::cout << "CastInst : cast to int, but arg already int !" << std::endl;
            } else {
                fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kCastInt));
            }
        } else {
            if (real_t1) {
                //std::cout << "CastInst : cast to real, but arg already real !" << std::endl;
            } else {
                fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kCastReal));
            }
        }
    }

    virtual void visit(BitcastInst* inst)
    {
        inst->fInst->accept(this);
        switch (inst->fType->getType()) {
            case Typed::kInt32:
                fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kBitcastInt));
                break;
            case Typed::kInt64:
                faustassert(false);
                break;
            case Typed::kFloat:
            case Typed::kDouble:
                fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kBitcastReal));
                break;
            default:
                faustassert(false);
                break;
        }
    }

    // Function call
    virtual void visit(FunCallInst* inst)
    {
        // Compile args in reverse order
        list<ValueInst*>::reverse_iterator it;
        for (it = inst->fArgs.rbegin(); it != inst->fArgs.rend(); it++) {
            (*it)->accept(this);
        }
        
        if (gMathLibTable.find(inst->fName) == gMathLibTable.end()) {
            stringstream error;
            error << "ERROR : missing function : " << inst->fName << std::endl;
            throw faustexception(error.str());
        } else {
            fCurrentBlock->push(new FIRBasicInstruction<T>(gMathLibTable[inst->fName]));
        }
    }

    // Conditional : select
    virtual void visit(Select2Inst* inst)
    {
        // Compile condition
        inst->fCond->accept(this);
        
        // Keep current block
        FIRBlockInstruction<T>* previous = fCurrentBlock;
        
        // Compile 'then' in a new block
        FIRBlockInstruction<T>* then_block = new FIRBlockInstruction<T>();
        fCurrentBlock = then_block;
        inst->fThen->accept(this);
        bool real_t1 = fCurrentBlock->isRealInst(); // Type is the same on both branches, so takes the first one
        
        // Add kReturn in block
        then_block->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
        
        // Compile 'else' in a new block
        FIRBlockInstruction<T>* else_block = new FIRBlockInstruction<T>();
        fCurrentBlock = else_block;
        inst->fElse->accept(this);
        // Add kReturn in block
        else_block->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
        
        // Compile 'select'
        previous->push(new FIRBasicInstruction<T>((real_t1) ? FIRInstruction::kSelectReal : FIRInstruction::kSelectInt, 0, 0, 0, 0, then_block, else_block));
                                                       
        // Restore current block
        fCurrentBlock = previous;
    }

    // Conditional : if
    virtual void visit(IfInst* inst)
    {
        // Compile condition
        inst->fCond->accept(this);
        
        // Keep current block
        FIRBlockInstruction<T>* previous = fCurrentBlock;
        
        // Compile 'then' in a new block
        FIRBlockInstruction<T>* then_block = new FIRBlockInstruction<T>();
        fCurrentBlock = then_block;
        inst->fThen->accept(this);
        // Add kReturn in block
        then_block->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
        
        // Compile 'else' in a (possibly empty) new block
        FIRBlockInstruction<T>* else_block = new FIRBlockInstruction<T>();
        fCurrentBlock = else_block;
        inst->fElse->accept(this);
        // Add kReturn in block
        else_block->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
        
        // Compile 'if'
        previous->push(new FIRBasicInstruction<T>(FIRInstruction::kIf, 0, 0, 0, 0, then_block, else_block));
        
        // Restore current block
        fCurrentBlock = previous;
    }

    // Loop
    virtual void visit(ForLoopInst* inst)
    {
        // Keep current block
        FIRBlockInstruction<T>* previous = fCurrentBlock;
        
        // Compile 'loop variable init code' in a new block
        FIRBlockInstruction<T>* init_block = new FIRBlockInstruction<T>();
        fCurrentBlock = init_block;
        
        // Compile loop variable declaration
        inst->fInit->accept(this);
        
        // Add kReturn in block
        init_block->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
        
        // Compile 'loop code' in a new block
        FIRBlockInstruction<T>* loop_block = new FIRBlockInstruction<T>();
        fCurrentBlock = loop_block;
        
        // Compile loop code
        inst->fCode->accept(this);
        
        // Compile increment
        inst->fIncrement->accept(this);
        
        // Compile test
        inst->fEnd->accept(this);
        
        // Add branch that moves back on loop block itself
        fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kCondBranch, 0, 0, 0, 0, loop_block, 0));
        
        // Finally add 'return'
        fCurrentBlock->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
        
        // Add the loop block in previous
        previous->push(new FIRBasicInstruction<T>(FIRInstruction::kLoop, 0, 0, 0, 0, init_block, loop_block));
        
        // Restore current block
        fCurrentBlock = previous;
    }
 
};

#endif
