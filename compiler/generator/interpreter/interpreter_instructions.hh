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

#ifndef _INTERPRETER_INSTRUCTIONS_H
#define _INTERPRETER_INSTRUCTIONS_H

#include <cstdlib>

#include "exception.hh"
#include "fbc_interpreter.hh"
#include "instructions.hh"
#include "struct_manager.hh"
#include "typing_instructions.hh"

template <class T>
struct InterpreterInstVisitor : public DispatchVisitor {
    using DispatchVisitor::visit;

    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
    */
    static std::map<std::string, FBCInstruction::Opcode> gMathLibTable;

    int  fRealHeapOffset;   // Offset in Real HEAP
    int  fIntHeapOffset;    // Offset in Integer HEAP
    int  fSoundHeapOffset;  // Offset in Sound HEAP
    bool fCommute;          // Whether to try commutative operation reverse order generation

    std::map<std::string, MemoryDesc> fFieldTable;  // Table : field_name, { offset, size, type }

    FIRUserInterfaceBlockInstruction<T>* fUserInterfaceBlock;
    FBCBlockInstruction<T>*              fCurrentBlock;

    InterpreterInstVisitor()
    {
        fUserInterfaceBlock = new FIRUserInterfaceBlockInstruction<T>();
        fCurrentBlock       = new FBCBlockInstruction<T>();
        fRealHeapOffset     = 0;
        fIntHeapOffset      = 0;
        fSoundHeapOffset    = 0;
        fCommute            = true;
        initMathTable();
    }

    virtual ~InterpreterInstVisitor() {}

    int getFieldOffset(const std::string& name)
    {
        return (fFieldTable.find(name) != fFieldTable.end()) ? fFieldTable[name].fOffset : -1;
    }

    void initMathTable()
    {
        // Integer version
        gMathLibTable["abs"]   = FBCInstruction::kAbs;
        gMathLibTable["min_i"] = FBCInstruction::kMin;
        gMathLibTable["max_i"] = FBCInstruction::kMax;

        // Float version
        gMathLibTable["fabsf"]      = FBCInstruction::kAbsf;
        gMathLibTable["acosf"]      = FBCInstruction::kAcosf;
        gMathLibTable["asinf"]      = FBCInstruction::kAsinf;
        gMathLibTable["atanf"]      = FBCInstruction::kAtanf;
        gMathLibTable["atan2f"]     = FBCInstruction::kAtan2f;
        gMathLibTable["ceilf"]      = FBCInstruction::kCeilf;
        gMathLibTable["cosf"]       = FBCInstruction::kCosf;
        gMathLibTable["expf"]       = FBCInstruction::kExpf;
        gMathLibTable["floorf"]     = FBCInstruction::kFloorf;
        gMathLibTable["fmodf"]      = FBCInstruction::kFmodf;
        gMathLibTable["logf"]       = FBCInstruction::kLogf;
        gMathLibTable["log10f"]     = FBCInstruction::kLog10f;
        gMathLibTable["min_f"]      = FBCInstruction::kMinf;
        gMathLibTable["max_f"]      = FBCInstruction::kMaxf;
        gMathLibTable["powf"]       = FBCInstruction::kPowf;
        gMathLibTable["remainderf"] = FBCInstruction::kRemReal;
        gMathLibTable["roundf"]     = FBCInstruction::kRoundf;
        gMathLibTable["sinf"]       = FBCInstruction::kSinf;
        gMathLibTable["sqrtf"]      = FBCInstruction::kSqrtf;
        gMathLibTable["tanf"]       = FBCInstruction::kTanf;
        
        // Hyperbolic
        gMathLibTable["acoshf"]     = FBCInstruction::kAcoshf;
        gMathLibTable["asinhf"]     = FBCInstruction::kAsinhf;
        gMathLibTable["atanhf"]     = FBCInstruction::kAtanhf;
        gMathLibTable["coshf"]      = FBCInstruction::kCoshf;
        gMathLibTable["sinhf"]      = FBCInstruction::kSinhf;
        gMathLibTable["tanhf"]      = FBCInstruction::kTanhf;

        // Double version
        gMathLibTable["fabs"]      = FBCInstruction::kAbsf;
        gMathLibTable["acos"]      = FBCInstruction::kAcosf;
        gMathLibTable["asin"]      = FBCInstruction::kAsinf;
        gMathLibTable["atan"]      = FBCInstruction::kAtanf;
        gMathLibTable["atan2"]     = FBCInstruction::kAtan2f;
        gMathLibTable["ceil"]      = FBCInstruction::kCeilf;
        gMathLibTable["cos"]       = FBCInstruction::kCosf;
        gMathLibTable["exp"]       = FBCInstruction::kExpf;
        gMathLibTable["floor"]     = FBCInstruction::kFloorf;
        gMathLibTable["fmod"]      = FBCInstruction::kFmodf;
        gMathLibTable["log"]       = FBCInstruction::kLogf;
        gMathLibTable["log10"]     = FBCInstruction::kLog10f;
        gMathLibTable["min_"]      = FBCInstruction::kMinf;
        gMathLibTable["max_"]      = FBCInstruction::kMaxf;
        gMathLibTable["pow"]       = FBCInstruction::kPowf;
        gMathLibTable["remainder"] = FBCInstruction::kRemReal;
        gMathLibTable["round"]     = FBCInstruction::kRoundf;
        gMathLibTable["sin"]       = FBCInstruction::kSinf;
        gMathLibTable["sqrt"]      = FBCInstruction::kSqrtf;
        gMathLibTable["tan"]       = FBCInstruction::kTanf;
        
        // Hyperbolic
        gMathLibTable["acosh"]     = FBCInstruction::kAcoshf;
        gMathLibTable["asinh"]     = FBCInstruction::kAsinhf;
        gMathLibTable["atanh"]     = FBCInstruction::kAtanhf;
        gMathLibTable["cosh"]      = FBCInstruction::kCoshf;
        gMathLibTable["sinh"]      = FBCInstruction::kSinhf;
        gMathLibTable["tanh"]      = FBCInstruction::kTanhf;

        // Min/max directly handled in FunCallInst
    }

    virtual void visit(AddMetaDeclareInst* inst)
    {
        MemoryDesc tmp = fFieldTable[inst->fZone];
        if (inst->fZone == "0") {
            fUserInterfaceBlock->push(
                new FIRUserInterfaceInstruction<T>(FBCInstruction::kDeclare, -1, inst->fKey, inst->fValue));
        } else {
            fUserInterfaceBlock->push(
                new FIRUserInterfaceInstruction<T>(FBCInstruction::kDeclare, tmp.fOffset, inst->fKey, inst->fValue));
        }
    }

    virtual void visit(OpenboxInst* inst)
    {
        FBCInstruction::Opcode opcode = FBCInstruction::kNop;
        switch (inst->fOrient) {
            case 0:
                opcode = FBCInstruction::kOpenVerticalBox;
                break;
            case 1:
                opcode = FBCInstruction::kOpenHorizontalBox;
                break;
            case 2:
                opcode = FBCInstruction::kOpenTabBox;
                break;
            default:
                faustassert(false);
                break;
        }

        fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, inst->fName));
    }

    virtual void visit(CloseboxInst* inst)
    {
        fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(FBCInstruction::kCloseBox));
    }

    virtual void visit(AddButtonInst* inst)
    {
        FBCInstruction::Opcode opcode;
        if (inst->fType == AddButtonInst::kDefaultButton) {
            opcode = FBCInstruction::kAddButton;
        } else {
            opcode = FBCInstruction::kAddCheckButton;
        }

        MemoryDesc tmp = fFieldTable[inst->fZone];
        fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, tmp.fOffset, inst->fLabel));
    }

    virtual void visit(AddSliderInst* inst)
    {
        FBCInstruction::Opcode opcode = FBCInstruction::kNop;
        switch (inst->fType) {
            case AddSliderInst::kHorizontal:
                opcode = FBCInstruction::kAddHorizontalSlider;
                break;
            case AddSliderInst::kVertical:
                opcode = FBCInstruction::kAddVerticalSlider;
                break;
            case AddSliderInst::kNumEntry:
                opcode = FBCInstruction::kAddNumEntry;
                break;
            default:
                faustassert(false);
                break;
        }

        MemoryDesc tmp = fFieldTable[inst->fZone];
        fUserInterfaceBlock->push(new FIRUserInterfaceInstruction<T>(opcode, tmp.fOffset, inst->fLabel, inst->fInit,
                                                                     inst->fMin, inst->fMax, inst->fStep));
    }

    virtual void visit(AddBargraphInst* inst)
    {
        FBCInstruction::Opcode opcode = FBCInstruction::kNop;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                opcode = FBCInstruction::kAddHorizontalBargraph;
                break;
            case AddBargraphInst::kVertical:
                opcode = FBCInstruction::kAddVerticalBargraph;
                break;
            default:
                faustassert(false);
                break;
        }

        MemoryDesc tmp = fFieldTable[inst->fZone];
        fUserInterfaceBlock->push(
            new FIRUserInterfaceInstruction<T>(opcode, tmp.fOffset, inst->fLabel, inst->fMin, inst->fMax));
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        // Not supported for now
        throw faustexception("ERROR : AddSoundfileInst not supported for interp\n");

        MemoryDesc tmp = fFieldTable[inst->fSFZone];
        fUserInterfaceBlock->push(
            new FIRUserInterfaceInstruction<T>(FBCInstruction::kAddSoundfile, tmp.fOffset, inst->fLabel, inst->fURL));
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
        faustassert(fFieldTable.find(inst->fAddress->getName()) == fFieldTable.end());

        if (array_typed && array_typed->fSize > 1) {
            if (array_typed->fType->getType() == Typed::kInt32) {
                fFieldTable[inst->fAddress->getName()] =
                    MemoryDesc(-1, fIntHeapOffset, array_typed->fSize, array_typed->fType->getType());
                fIntHeapOffset += array_typed->fSize;
            } else {
                fFieldTable[inst->fAddress->getName()] =
                    MemoryDesc(-1, fRealHeapOffset, array_typed->fSize, array_typed->fType->getType());
                fRealHeapOffset += array_typed->fSize;
            }
        } else {
            if (inst->fType->getType() == Typed::kInt32) {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(-1, fIntHeapOffset, 1, inst->fType->getType());
                fIntHeapOffset++;
            } else if (inst->fType->getType() == Typed::kSound_ptr) {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(-1, fSoundHeapOffset, 1, inst->fType->getType());
                fSoundHeapOffset++;
            } else {
                fFieldTable[inst->fAddress->getName()] = MemoryDesc(-1, fRealHeapOffset, 1, inst->fType->getType());
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
        if (!startWith(inst->fAddress->getName(), "input")) {
            faustassert(fFieldTable.find(inst->fAddress->getName()) != fFieldTable.end());
        }

        NamedAddress* named = dynamic_cast<NamedAddress*>(inst->fAddress);
        if (named) {
            MemoryDesc tmp = fFieldTable[named->getName()];
            faustassert(tmp.fOffset >= 0);

            switch (tmp.fType) {
                case Typed::kInt32:
                    fCurrentBlock->push(
                        new FBCBasicInstruction<T>(FBCInstruction::kLoadInt, named->getName(), 0, 0, tmp.fOffset, 0));
                    break;
                case Typed::kSound_ptr:
                    fCurrentBlock->push(
                        new FBCBasicInstruction<T>(FBCInstruction::kLoadSound, named->getName(), 0, 0, tmp.fOffset, 0));
                    break;
                default:
                    fCurrentBlock->push(
                        new FBCBasicInstruction<T>(FBCInstruction::kLoadReal, named->getName(), 0, 0, tmp.fOffset, 0));
                    break;
            }

        } else {
            // Indexed
            IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(inst->fAddress);

            std::string num;
            // Special treatment for inputs
            if (startWithRes(indexed->getName(), "input", num)) {
                fCurrentBlock->push(
                    new FBCBasicInstruction<T>(FBCInstruction::kLoadInput, 0, 0, std::atoi(num.c_str()), 0));
            } else {
                DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
                if (struct_type) {
                    Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->fIndex);
                    fCurrentBlock->push(
                        new FBCBasicInstruction<T>(FBCInstruction::kLoadSoundField, 0, 0, field_index->fNum, 0));
                } else {
                    MemoryDesc tmp = fFieldTable[indexed->getName()];
                    faustassert(tmp.fOffset >= 0);
                    fCurrentBlock->push(new FBCBasicInstruction<T>((tmp.fType == Typed::kInt32)
                                                                       ? FBCInstruction::kLoadIndexedInt
                                                                       : FBCInstruction::kLoadIndexedReal,
                                                                   indexed->getName(), 0, 0, tmp.fOffset, tmp.fSize));
                }
            }
        }
    }

    virtual void visit(LoadVarAddressInst* inst) { faustassert(false); }

    virtual void visitStore(Address* address, ValueInst* value, Typed* type = nullptr)
    {
        if (!startWith(address->getName(), "output")) {
            faustassert(fFieldTable.find(address->getName()) != fFieldTable.end());
        }
        // Waveform array store...
        ArrayTyped* array_typed;
        if (type && (array_typed = dynamic_cast<ArrayTyped*>(type))) {
            MemoryDesc tmp = fFieldTable[address->getName()];
            faustassert(tmp.fOffset >= 0);

            switch (array_typed->fType->getType()) {
                case Typed::kInt32: {
                    Int32ArrayNumInst* int_array = dynamic_cast<Int32ArrayNumInst*>(value);
                    faustassert(int_array);
                    fCurrentBlock->push(new FIRBlockStoreIntInstruction<T>(FBCInstruction::kBlockStoreInt, tmp.fOffset,
                                                                           int(int_array->fNumTable.size()),
                                                                           int_array->fNumTable));
                    break;
                }
                case Typed::kFloat: {
                    FloatArrayNumInst* float_array = dynamic_cast<FloatArrayNumInst*>(value);
                    faustassert(float_array);
                    fCurrentBlock->push(new FIRBlockStoreRealInstruction<T>(
                        FBCInstruction::kBlockStoreReal, tmp.fOffset, int(float_array->fNumTable.size()),
                        reinterpret_cast<const std::vector<T>&>(float_array->fNumTable)));
                    break;
                }
                case Typed::kDouble: {
                    DoubleArrayNumInst* double_array = dynamic_cast<DoubleArrayNumInst*>(value);
                    faustassert(double_array);
                    fCurrentBlock->push(new FIRBlockStoreRealInstruction<T>(
                        FBCInstruction::kBlockStoreReal, tmp.fOffset, int(double_array->fNumTable.size()),
                        reinterpret_cast<const std::vector<T>&>(double_array->fNumTable)));
                    break;
                }
                default:
                    faustassert(false);
                    break;
            }

            // Standard store
        } else {
            // Compile value
            value->accept(this);
            NamedAddress* named = dynamic_cast<NamedAddress*>(address);

            if (named) {
                MemoryDesc tmp = fFieldTable[named->getName()];
                faustassert(tmp.fOffset >= 0);

                switch (tmp.fType) {
                    case Typed::kInt32:
                        fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kStoreInt, named->getName(), 0,
                                                                       0, tmp.fOffset, 0));
                        break;
                    case Typed::kSound_ptr:
                        fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kStoreSound, named->getName(), 0,
                                                                       0, tmp.fOffset, 0));
                        break;
                    default:
                        fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kStoreReal, named->getName(), 0,
                                                                       0, tmp.fOffset, 0));
                        break;
                }

            } else {
                IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(address);
                // Compile address
                indexed->accept(this);
                // Indexed
                std::string num;
                // Special treatment for outputs
                if (startWithRes(indexed->getName(), "output", num)) {
                    fCurrentBlock->push(
                        new FBCBasicInstruction<T>(FBCInstruction::kStoreOutput, 0, 0, std::atoi(num.c_str()), 0));
                } else {
                    MemoryDesc tmp = fFieldTable[indexed->getName()];
                    faustassert(tmp.fOffset >= 0);
                    fCurrentBlock->push(new FBCBasicInstruction<T>((tmp.fType == Typed::kInt32)
                                                                       ? FBCInstruction::kStoreIndexedInt
                                                                       : FBCInstruction::kStoreIndexedReal,
                                                                   indexed->getName(), 0, 0, tmp.fOffset, tmp.fSize));
                }
            }
        }
    }

    virtual void visit(StoreVarInst* inst) { visitStore(inst->fAddress, inst->fValue); }

    virtual void visit(ShiftArrayVarInst* inst)
    {
        MemoryDesc tmp = fFieldTable[inst->fAddress->getName()];
        fCurrentBlock->push(new FBCBasicInstruction<T>(
            (tmp.fType == Typed::kInt32) ? FBCInstruction::kBlockShiftInt : FBCInstruction::kBlockShiftReal, 0, 0,
            tmp.fOffset + inst->fDelay, tmp.fOffset));
    }

    // Primitives : numbers
    virtual void visit(FloatNumInst* inst)
    {
        fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kRealValue, 0, inst->fNum));
    }

    // For Waveform : done in DeclareVarInst and visitStore
    virtual void visit(FloatArrayNumInst* inst) {}

    virtual void visit(Int32NumInst* inst)
    {
        fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kInt32Value, inst->fNum, 0));
    }

    // For Waveform : done in DeclareVarInst and visitStore
    virtual void visit(Int32ArrayNumInst* inst) {}

    virtual void visit(BoolNumInst* inst)
    {
        fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kInt32Value, inst->fNum, 0));
    }

    virtual void visit(DoubleNumInst* inst)
    {
        // Double considered real...
        fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kRealValue, 0, inst->fNum));
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
            fCurrentBlock->push(new FBCBasicInstruction<T>(gBinOpTable[inst->fOpcode]->fInterpFloatInst));
        } else if (!real_t1 || !real_t2) {
            fCurrentBlock->push(new FBCBasicInstruction<T>(gBinOpTable[inst->fOpcode]->fInterpIntInst32));
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
                // std::cout << "CastInst : cast to int, but arg already int !" << std::endl;
            } else {
                fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kCastInt));
            }
        } else {
            if (real_t1) {
                // std::cout << "CastInst : cast to real, but arg already real !" << std::endl;
            } else {
                fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kCastReal));
            }
        }
    }

    virtual void visit(BitcastInst* inst)
    {
        inst->fInst->accept(this);
        switch (inst->fType->getType()) {
            case Typed::kInt32:
                fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kBitcastInt));
                break;
            case Typed::kInt64:
                faustassert(false);
                break;
            case Typed::kFloat:
            case Typed::kDouble:
                fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kBitcastReal));
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
            std::stringstream error;
            error << "ERROR : missing function : " << inst->fName << std::endl;
            throw faustexception(error.str());
        } else {
            fCurrentBlock->push(new FBCBasicInstruction<T>(gMathLibTable[inst->fName]));
        }
    }

    // Conditional : select
    virtual void visit(Select2Inst* inst)
    {
        // Compile condition
        inst->fCond->accept(this);

        // Keep current block
        FBCBlockInstruction<T>* previous = fCurrentBlock;

        // Compile 'then' in a new block
        FBCBlockInstruction<T>* then_block = new FBCBlockInstruction<T>();
        fCurrentBlock                      = then_block;
        inst->fThen->accept(this);
        bool real_t1 = fCurrentBlock->isRealInst();  // Type is the same on both branches, so takes the first one
        // Add kReturn in block
        then_block->push(new FBCBasicInstruction<T>(FBCInstruction::kReturn));

        // Compile 'else' in a new block
        FBCBlockInstruction<T>* else_block = new FBCBlockInstruction<T>();
        fCurrentBlock                      = else_block;
        inst->fElse->accept(this);
        // Add kReturn in block
        else_block->push(new FBCBasicInstruction<T>(FBCInstruction::kReturn));

        // Compile 'select'
        previous->push(new FBCBasicInstruction<T>((real_t1) ? FBCInstruction::kSelectReal : FBCInstruction::kSelectInt,
                                                  "", 0, 0, 0, 0, then_block, else_block));

        // Restore current block
        fCurrentBlock = previous;
    }

    // Conditional : if
    virtual void visit(IfInst* inst)
    {
        // Compile condition
        inst->fCond->accept(this);

        // Keep current block
        FBCBlockInstruction<T>* previous = fCurrentBlock;

        // Compile 'then' in a new block
        FBCBlockInstruction<T>* then_block = new FBCBlockInstruction<T>();
        fCurrentBlock                      = then_block;
        inst->fThen->accept(this);
        // Add kReturn in block
        then_block->push(new FBCBasicInstruction<T>(FBCInstruction::kReturn));

        // Compile 'else' in a (possibly empty) new block
        FBCBlockInstruction<T>* else_block = new FBCBlockInstruction<T>();
        fCurrentBlock                      = else_block;
        inst->fElse->accept(this);
        // Add kReturn in block
        else_block->push(new FBCBasicInstruction<T>(FBCInstruction::kReturn));

        // Compile 'if'
        previous->push(new FBCBasicInstruction<T>(FBCInstruction::kIf, "", 0, 0, 0, 0, then_block, else_block));

        // Restore current block
        fCurrentBlock = previous;
    }

    // Loop : beware: compiled loop don't work with an index of 0
    virtual void visit(ForLoopInst* inst)
    {
        // Keep current block
        FBCBlockInstruction<T>* previous = fCurrentBlock;

        // Compile 'loop variable init code' in a new block
        FBCBlockInstruction<T>* init_block = new FBCBlockInstruction<T>();
        fCurrentBlock                      = init_block;

        // Compile loop variable declaration
        inst->fInit->accept(this);

        // Add kReturn in block
        init_block->push(new FBCBasicInstruction<T>(FBCInstruction::kReturn));

        // Compile 'loop code' in a new block
        FBCBlockInstruction<T>* loop_body_block = new FBCBlockInstruction<T>();
        fCurrentBlock                           = loop_body_block;

        // Compile loop code
        inst->fCode->accept(this);

        // Compile increment
        inst->fIncrement->accept(this);

        // Compile test
        inst->fEnd->accept(this);

        // Add branch that moves back on loop block itself
        fCurrentBlock->push(
            new FBCBasicInstruction<T>(FBCInstruction::kCondBranch, "", 0, 0, 0, 0, loop_body_block, 0));

        // Finally add 'return'
        fCurrentBlock->push(new FBCBasicInstruction<T>(FBCInstruction::kReturn));

        // Add the loop block in previous
        previous->push(new FBCBasicInstruction<T>(FBCInstruction::kLoop, "",
                                                  ((inst->fIsRecursive) ? 1 : gGlobal->gVecSize), 0, 0, 0, init_block,
                                                  loop_body_block));

        // Restore current block
        fCurrentBlock = previous;
    }
};

#endif
