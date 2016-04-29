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

#ifndef _FIR_INTERPRETER_H
#define _FIR_INTERPRETER_H

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "fir_opcode.hh"

#include <vector>
#include <string>
#include <math.h>
#include <assert.h>
#include <iostream>

// Interpreter

#define push_real(val) real_stack[real_stack_index++] = val
#define push_int(val) int_stack[int_stack_index++] = val

#define pop_real() (real_stack[--real_stack_index])
#define pop_int() int_stack[--int_stack_index]

typedef long double quad;

template <class T>
struct FIRBlockInstruction;

template <class T>
struct FIRBasicInstruction : public FIRInstruction {

    Opcode fOpcode;
    int fIntValue;
    T fRealValue;
    int fOffset1;
    int fOffset2;
    
    FIRBlockInstruction<T>* fBranch1;
    FIRBlockInstruction<T>* fBranch2;
    
    FIRBasicInstruction(Opcode opcode, 
                        int val_int, T val_real, 
                        int off1, int off2,
                        FIRBlockInstruction<T>* branch1, 
                        FIRBlockInstruction<T>* branch2) 
                        :fOpcode(opcode), fIntValue(val_int), fRealValue(val_real),
                        fOffset1(off1), fOffset2(off2),
                        fBranch1(branch1), fBranch2(branch2)
    {}
    
    FIRBasicInstruction(Opcode opcode, 
                        int val_int, T val_real) 
                        :fOpcode(opcode), fIntValue(val_int), fRealValue(val_real),
                        fOffset1(0), fOffset2(0),
                        fBranch1(0), fBranch2(0)
    {}
    
    FIRBasicInstruction(Opcode opcode, 
                        int val_int, T val_real, int off1, int off2)
                        :fOpcode(opcode), fIntValue(val_int), fRealValue(val_real),
                        fOffset1(off1), fOffset2(off2),
                        fBranch1(0), fBranch2(0)
    {}
    
    FIRBasicInstruction(Opcode opcode) 
                        :fOpcode(opcode), fIntValue(0), fRealValue(0),
                        fOffset1(0), fOffset2(0),
                        fBranch1(0), fBranch2(0)
    {}
    
     
    virtual ~FIRBasicInstruction()
    {
        delete fBranch1;
        delete fBranch2;
    }
    
    int size()
    {
        int branches = std::max(((fBranch1) ? fBranch1->size() : 0), ((fBranch2) ? fBranch2->size() : 0));
        return (branches > 0) ? branches : 1;
    }
    
    void dump()
    {
        std::cout << "opcode = " << fOpcode << " " << gFIRInstructionTable[fOpcode]
        << " int = " << fIntValue
        << " real = " << fRealValue
        << " offset1 = " << fOffset1
        << " offset2 = " << fOffset2
        << std::endl;
        if (fBranch1) fBranch1->dump();
        if (fBranch2) fBranch2->dump();
    }
    
    FIRBasicInstruction<T>* copy()
    {
        return new FIRBasicInstruction<T>(fOpcode, fIntValue, fRealValue, fOffset1, fOffset2, ((fBranch1) ? fBranch1->copy() : 0), ((fBranch2) ? fBranch2->copy() : 0));
    }
    
};

template <class T>
struct FIRUserInterfaceInstruction : public FIRInstruction {

    Opcode fOpcode;
    int fOffset;
    std::string fLabel;
    std::string fKey;
    std::string fValue;
    T fInit;
    T fMin;
    T fMax;
    T fStep;
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label, T init, T min, T max, T step)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fInit(init), fMin(min), fMax(max), fStep(step)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode)
        :fOpcode(opcode), fOffset(0), fLabel(""), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, const std::string& label)
        :fOpcode(opcode), fOffset(0), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
     
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label, T min, T max)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(min), fMax(max), fStep(0)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& key, const std::string& value)
        :fOpcode(opcode), fOffset(offset), fLabel(""), fKey(key), fValue(value), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
    
    virtual ~FIRUserInterfaceInstruction()
    {}
    
    void dump()
    {
        
    }
    
};

#define InstructionIT typename std::vector<FIRBasicInstruction<T>* >::iterator
#define UIInstructionIT typename std::vector<FIRUserInterfaceInstruction<T>* >::iterator

template <class T>
struct FIRUserInterfaceBlockInstruction : public FIRInstruction {

    std::vector<FIRUserInterfaceInstruction<T>*> fInstructions;
     
    virtual ~FIRUserInterfaceBlockInstruction()
    {
        UIInstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            delete(*it);
        }
    }
     
    void push(FIRUserInterfaceInstruction<T>* inst) { fInstructions.push_back(inst); }
    
    void dump()
    {}
    
};

// Block optimizer : compact and reorganize instructions
template <class T>
struct FIRInstructionOptimizer {
    
    virtual FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        return 0;
    }
};

// Copy (= identity) optimizer (used to test...)
template <class T>
struct FIRInstructionCopyOptimizer : public FIRInstructionOptimizer<T>  {
    
    virtual FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        end = cur + 1;
        return (*cur)->copy();
    }
};

// Rewrite indexed Load/Store as simple Load/Store
template <class T>
struct FIRInstructionLoadStoreOptimizer : public FIRInstructionOptimizer<T> {
    
    
    FIRInstructionLoadStoreOptimizer()
    {
        std::cout << "FIRInstructionLoadStoreOptimizer" << std::endl;
    }
    
    FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FIRBasicInstruction<T>* inst1 = *cur;
        FIRBasicInstruction<T>* inst2 = *(cur + 1);
        
        if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kLoadIndexedReal) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kLoadReal, 0, 0, inst1->fIntValue + inst2->fOffset1, 0);
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kLoadIndexedInt) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kLoadInt, 0, 0, inst1->fIntValue + inst2->fOffset1, 0);
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kStoreIndexedReal) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kStoreReal, 0, 0, inst1->fIntValue + inst2->fOffset1, 0);
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kStoreIndexedInt) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kStoreInt, 0, 0, inst1->fIntValue + inst2->fOffset1, 0);
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
    
};

// Rewrite heap Load/Store as Move
template <class T>
struct FIRInstructionMoveOptimizer : public FIRInstructionOptimizer<T> {
    
    FIRInstructionMoveOptimizer()
    {
        std::cout << "FIRInstructionMoveOptimizer" << std::endl;
    }
    
    FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FIRBasicInstruction<T>* inst1 = *cur;
        FIRBasicInstruction<T>* inst2 = *(cur + 1);
        
        if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kStoreReal) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kMoveReal, 0, 0, inst2->fOffset1, inst1->fOffset1);   // reverse order
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kStoreInt) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kMoveInt, 0, 0, inst2->fOffset1, inst1->fOffset1);    // reverse order
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
    
};

// Rewrite math operations as 'heap' or 'direct' versions
template <class T>
struct FIRInstructionMathOptimizer : public FIRInstructionOptimizer<T> {
    
    FIRInstructionMathOptimizer()
    {
        std::cout << "FIRInstructionMathOptimizer" << std::endl;
    }
    
    FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FIRBasicInstruction<T>* inst1 = *cur;
        FIRBasicInstruction<T>* inst2 = *(cur + 1);
        FIRBasicInstruction<T>* inst3 = *(cur + 2);
        
        if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
        } else if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kRealValue && FIRInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Direct[inst3->fOpcode], 0, inst2->fRealValue, inst1->fOffset1, 0);
        } else if (inst1->fOpcode == FIRInstruction::kRealValue && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2DirectInvert[inst3->fOpcode], 0, inst1->fRealValue, inst2->fOffset1, 0);
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kIntValue && FIRInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Direct[inst3->fOpcode], inst2->fIntValue, 0, inst1->fOffset1, 0);
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2DirectInvert[inst3->fOpcode], inst1->fIntValue, 0, inst2->fOffset1, 0);
        //} else if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isMath(inst3->fOpcode)) {
           
        } else {
            
            end = cur + 1;
            return (*cur)->copy();
        }
    }
    
};


template <class T>
struct FIRBlockInstruction : public FIRInstruction {

    std::vector<FIRBasicInstruction<T>*> fInstructions;
    
    virtual ~FIRBlockInstruction()
    {
        InstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            delete (*it);
        }
    }
     
    void push(FIRBasicInstruction<T>* inst) { fInstructions.push_back(inst); }
    
    void dump()
    {
        std::cout << "Block size = " << fInstructions.size() << std::endl;
        InstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            (*it)->dump();
        }
    }
    
    FIRBlockInstruction<T>* copy()
    {
        FIRBlockInstruction<T>* block = new FIRBlockInstruction<T>();
        InstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            block->push((*it)->copy());
        }
        return block;
    }
    
    // Return an optimized block by traversing it (including sub-blocks) with an 'optimizer'
    static FIRBlockInstruction* optimize_aux(FIRBlockInstruction<T>* cur_block, FIRInstructionOptimizer<T>& optimizer)
    {
        FIRBlockInstruction<T>* new_block = new FIRBlockInstruction<T>();
        InstructionIT next, cur = cur_block->fInstructions.begin();
        
        do {
            FIRBasicInstruction<T>* inst = *cur;
            if (inst->fOpcode == FIRInstruction::kLoop) {
                new_block->push(new FIRBasicInstruction<T>(FIRInstruction::kLoop,
                                                           inst->fIntValue, inst->fRealValue,
                                                           inst->fOffset1, inst->fOffset2,
                                                           FIRBlockInstruction::optimize_aux(inst->fBranch1, optimizer), 0));
                cur++;
            } else if (inst->fOpcode == FIRInstruction::kSelectInt || inst->fOpcode == FIRInstruction::kSelectReal) {
                new_block->push(new FIRBasicInstruction<T>(inst->fOpcode,
                                                           inst->fIntValue, inst->fRealValue,
                                                           inst->fOffset1, inst->fOffset2,
                                                           FIRBlockInstruction::optimize_aux(inst->fBranch1, optimizer),
                                                           FIRBlockInstruction::optimize_aux(inst->fBranch2, optimizer)));
                cur++;
            } else if (inst->fOpcode == FIRInstruction::kIf) {
                new_block->push(new FIRBasicInstruction<T>(FIRInstruction::kIf,
                                                           inst->fIntValue, inst->fRealValue,
                                                           inst->fOffset1, inst->fOffset2,
                                                           FIRBlockInstruction::optimize_aux(inst->fBranch1, optimizer),
                                                           (inst->fBranch2) ? FIRBlockInstruction::optimize_aux(inst->fBranch2, optimizer) : 0));
                cur++;
            } else {
                new_block->push(optimizer.rewrite(cur, next));
                cur = next;
            }
        } while (cur != cur_block->fInstructions.end());
    
        return new_block;
    }
    
    // Return an optimized block (copy), delete the original one
    static FIRBlockInstruction* optimize(FIRBlockInstruction<T>* cur_block, FIRInstructionOptimizer<T>& optimizer)
    {
        FIRBlockInstruction* new_block = FIRBlockInstruction::optimize_aux(cur_block, optimizer);
        delete cur_block;
        return new_block;
    }
    
    int size()
    {
        int size = 0;
        InstructionIT it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            size += (*it)->size();
        }
        return size;
    }
};


// FIR bytecode interpreter
template <class T>
class FIRInterpreter  {

    protected:
    
        T* fRealHeap;
        int* fIntHeap;
    
        int fRealHeapSize;
        int fIntHeapSize;
        int fSROffset;
    
        int fRealStackSize;
        int fIntStackSize;
        
        FAUSTFLOAT** fInputs;
        FAUSTFLOAT** fOutputs;
        
        void ExecuteBuildUserInterface(FIRUserInterfaceBlockInstruction<T>* block, UI* interface)
        {
            UIInstructionIT it;
            
            for (it = block->fInstructions.begin(); it != block->fInstructions.end(); it++) {
            
                switch ((*it)->fOpcode) {
                 
                        case FIRInstruction::kOpenVerticalBox:
                            interface->openVerticalBox((*it)->fLabel.c_str()); 
                            break;
                            
                        case FIRInstruction::kOpenHorizontalBox:
                            interface->openHorizontalBox((*it)->fLabel.c_str()); 
                            break;
                            
                        case FIRInstruction::kOpenTabBox:
                            interface->openTabBox((*it)->fLabel.c_str()); 
                            break;
                 
                        case FIRInstruction::kCloseBox:
                            interface->closeBox(); 
                            break;
                            
                        case FIRInstruction::kAddButton:
                            interface->addButton((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset]);
                            break;
                            
                        case FIRInstruction::kAddCheckButton:
                            interface->addCheckButton((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset]);
                            break;
                            
                        case FIRInstruction::kAddHorizontalSlider:
                            interface->addHorizontalSlider((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset], (*it)->fInit, (*it)->fMin, (*it)->fMax, (*it)->fStep);
                            break;
                            
                        case FIRInstruction::kAddVerticalSlider:
                            interface->addVerticalSlider((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset], (*it)->fInit, (*it)->fMin, (*it)->fMax, (*it)->fStep);
                            break;
                            
                        case FIRInstruction::kAddNumEntry:
                            interface->addNumEntry((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset], (*it)->fInit, (*it)->fMin, (*it)->fMax, (*it)->fStep);
                            break;
                            
                        case FIRInstruction::kAddHorizontalBargraph:
                            interface->addHorizontalBargraph((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset], (*it)->fMin, (*it)->fMax);
                            break;
                            
                        case FIRInstruction::kAddVerticalBargraph:
                            interface->addVerticalBargraph((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset], (*it)->fMin, (*it)->fMax);
                            break;
                            
                        case FIRInstruction::kDeclare:
                            // Special case for "0" zone
                            if ((*it)->fOffset == -1) {
                                interface->declare(NULL, (*it)->fKey.c_str(), (*it)->fValue.c_str());
                            } else {
                                interface->declare(&fRealHeap[(*it)->fOffset], (*it)->fKey.c_str(), (*it)->fValue.c_str());
                            }
                            break;
                            
                        default:
                            break;
                }
            }
        }
    
        inline void ExecuteBlockFast(FIRBlockInstruction<T>* block, int& res_int, T& res_real, int get_result)
        {
            int real_stack_index = 0;
            int int_stack_index = 0;
            
            T real_stack[fRealStackSize];
            int int_stack[fIntStackSize];
            
            #define DISPATCH_FIRST() { goto *fDispatchTable[(*it)->fOpcode]; }
            #define DISPATCH() { it++; goto *fDispatchTable[(*it)->fOpcode]; }
            
            /*
            #define DISPATCH_FIRST() { printf("real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index); (*it)->dump(); goto *fDispatchTable[(*it)->fOpcode]; }
            #define DISPATCH() { assert(real_stack_index >=0);   assert(int_stack_index >=0); printf("real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index); it++; (*it)->dump();  goto *fDispatchTable[(*it)->fOpcode]; }
            */
            
            static void* fDispatchTable[] = {
                
                // End operation
                &&do_kHalt,
                
                // Numbers
                &&do_kRealValue, &&do_kIntValue,
                
                // Memory
                &&do_kLoadReal, &&do_kLoadInt,
                &&do_kStoreReal, &&do_kStoreInt,
                &&do_kLoadIndexedReal, &&do_kLoadIndexedInt,
                &&do_kStoreIndexedReal, &&do_kStoreIndexedInt,
                &&do_kMoveReal, &&do_kMoveInt,
                &&do_kLoadInput, &&do_kStoreOutput,
                
                // Cast
                &&do_kCastReal, &&do_kCastInt,
                
                // Select/if
                &&do_kSelectInt, &&do_kSelectReal, &&do_kIf,
                
                // Standard math
                &&do_kAddReal, &&do_kAddInt, &&do_kSubReal, &&do_kSubInt,
                &&do_kMultReal, &&do_kMultInt, &&do_kDivReal, &&do_kDivInt,
                &&do_kRemReal, &&do_kRemInt, &&do_kLshInt, &&do_kRshInt, &&do_kGTInt,
                &&do_kLTInt, &&do_kGEInt, &&do_kLEInt, &&do_kEQInt, &&do_kNEInt,
                &&do_kGTReal, &&do_kLTReal, &&do_kGEReal,
                &&do_kLEReal, &&do_kEQReal, &&do_kNEReal,
                &&do_kANDInt, &&do_kORInt, &&do_kXORInt,
                
                // Standard math (heap version)
                &&do_kAddRealHeap, &&do_kAddIntHeap, &&do_kSubRealHeap, &&do_kSubIntHeap,
                &&do_kMultRealHeap, &&do_kMultIntHeap, &&do_kDivRealHeap, &&do_kDivIntHeap,
                &&do_kRemRealHeap, &&do_kRemIntHeap, &&do_kLshIntHeap, &&do_kRshIntHeap, &&do_kGTIntHeap,
                &&do_kLTIntHeap, &&do_kGEIntHeap, &&do_kLEIntHeap, &&do_kEQIntHeap, &&do_kNEIntHeap,
                &&do_kGTRealHeap, &&do_kLTRealHeap, &&do_kGERealHeap,
                &&do_kLERealHeap, &&do_kEQRealHeap, &&do_kNERealHeap,
                &&do_kANDIntHeap, &&do_kORIntHeap, &&do_kXORIntHeap,
                
                // Standard math (direct version)
                &&do_kAddRealDirect, &&do_kAddIntDirect, &&do_kSubRealDirect, &&do_kSubIntDirect,
                &&do_kMultRealDirect, &&do_kMultIntDirect, &&do_kDivRealDirect, &&do_kDivIntDirect,
                &&do_kRemRealDirect, &&do_kRemIntDirect, &&do_kLshIntDirect, &&do_kRshIntDirect, &&do_kGTIntDirect,
                &&do_kLTIntDirect, &&do_kGEIntDirect, &&do_kLEIntDirect, &&do_kEQIntDirect, &&do_kNEIntDirect,
                &&do_kGTRealDirect, &&do_kLTRealDirect, &&do_kGERealDirect,
                &&do_kLERealDirect, &&do_kEQRealDirect, &&do_kNERealDirect,
                &&do_kANDIntDirect, &&do_kORIntDirect, &&do_kXORIntDirect,
                
                // Standard math (direct version) : non commutative operations
                &&do_kSubRealDirectInvert, &&do_kSubIntDirectInvert,
                &&do_kDivRealDirectInvert, &&do_kDivIntDirectInvert,
                &&do_kRemRealDirectInvert, &&do_kRemIntDirectInvert,
                &&do_kLshIntDirectInvert, &&do_kRshIntDirectInvert,
                &&do_kGTIntDirectInvert, &&do_kLTIntDirectInvert,
                &&do_kGEIntDirectInvert, &&do_kLEIntDirectInvert,
                &&do_kGTRealDirectInvert, &&do_kLTRealDirectInvert,
                &&do_kGERealDirectInvert, &&do_kLERealDirectInvert,
                
                // Extended unary math
                &&do_kAbs, &&do_kAbsf,
                &&do_kAcosf, &&do_kAsinf,
                &&do_kAtanf,
                &&do_kCeilf,
                &&do_kCosf, &&do_kCoshf,
                &&do_kExpf,
                &&do_kFloorf,
                &&do_kLogf, &&do_kLog10f,
                &&do_kRoundf,
                &&do_kSinf, &&do_kSinhf,
                &&do_kSqrtf,
                &&do_kTanf, &&do_kTanhf,

                // Extended binary math
                &&do_kAtan2f,
                &&do_kFmodf,
                &&do_kPowf,
                &&do_kMax, &&do_kMaxf,
                &&do_kMin, &&do_kMinf,
                
                // Extended unary math (heap version)
                &&do_kAbsHeap, &&do_kAbsfHeap,
                &&do_kAcosfHeap, &&do_kAsinfHeap,
                &&do_kAtanfHeap,
                &&do_kCeilfHeap,
                &&do_kCosfHeap, &&do_kCoshfHeap,
                &&do_kExpfHeap,
                &&do_kFloorfHeap,
                &&do_kLogfHeap, &&do_kLog10fHeap,
                &&do_kRoundfHeap,
                &&do_kSinfHeap, &&do_kSinhfHeap,
                &&do_kSqrtfHeap,
                &&do_kTanfHeap, &&do_kTanhfHeap,
                
                // Extended binary math (heap version)
                &&do_kAtan2fHeap,
                &&do_kFmodfHeap,
                &&do_kPowfHeap,
                &&do_kMaxHeap, &&do_kMaxfHeap,
                &&do_kMinHeap, &&do_kMinfHeap,
                
                // Extended binary math (direct version)
                &&do_kAtan2fDirect,
                &&do_kFmodfDirect,
                &&do_kPowfDirect,
                &&do_kMaxDirect, &&do_kMaxfDirect,
                &&do_kMinDirect, &&do_kMinfDirect,
                
                // Extended binary math (direct version) : non commutative operations
                &&do_kAtan2fDirectInvert,
                &&do_kFmodfDirectInvert,
                &&do_kPowfDirectInvert,
                
                // Control
                &&do_kLoop
            };
            
            InstructionIT it = block->fInstructions.begin();
            DISPATCH_FIRST();
            
            while (1) {
                
                //-----
                // End
                //-----
                do_kHalt:
                {
                    break;
                }
                
                // Number operations
                do_kRealValue:
                {
                    push_real((*it)->fRealValue);
                    DISPATCH();
                }
                
                do_kIntValue:
                {
                    push_int((*it)->fIntValue);
                    DISPATCH();
                }
                    
                // Memory operations
                do_kLoadReal:
                {
                    push_real(fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                    
                do_kLoadInt:
                {
                    push_int(fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                    
                do_kStoreReal:
                {
                    fRealHeap[(*it)->fOffset1] = pop_real();
                    DISPATCH();
                }
                    
                do_kStoreInt:
                {
                    fIntHeap[(*it)->fOffset1] = pop_int();
                    DISPATCH();
                }
                    
                do_kLoadIndexedReal:
                {
                    push_real(fRealHeap[(*it)->fOffset1 + pop_int()]);
                    DISPATCH();
                }
                    
                do_kLoadIndexedInt:
                {
                    int offset = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1 + offset]);
                    DISPATCH();
                }
                
                do_kStoreIndexedReal:
                {
                    fRealHeap[(*it)->fOffset1 + pop_int()] = pop_real();
                    DISPATCH();
                }
                
                do_kStoreIndexedInt:
                {
                    int offset = pop_int();
                    fIntHeap[(*it)->fOffset1 + offset] = pop_int();
                    DISPATCH();
                }
                
                do_kMoveReal:
                {
                    fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset2];
                    DISPATCH();
                }
                
                do_kMoveInt:
                {
                    fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset2];
                    DISPATCH();
                }
                
                // Input/output access
                do_kLoadInput:
                {
                    push_real(fInputs[(*it)->fOffset1][pop_int()]);
                    DISPATCH();
                }
                    
                do_kStoreOutput:
                {
                    fOutputs[(*it)->fOffset1][pop_int()] = pop_real();
                    DISPATCH();
                }
                
                // Cast operations
                do_kCastReal:
                {
                    push_real(T(pop_int()));
                    DISPATCH();
                }
                
                do_kCastInt:
                {
                    push_int(int(pop_real()));
                    DISPATCH();
                }
                    
                // Select/If operation
                do_kSelectInt:
                {
                    int cond = pop_int();
                    push_int(cond ? ExecuteBlockInt((*it)->fBranch1) : ExecuteBlockInt((*it)->fBranch2));
                    DISPATCH();
                }
                
                do_kSelectReal:
                {
                    push_real(pop_int() ? ExecuteBlockReal((*it)->fBranch1) : ExecuteBlockReal((*it)->fBranch2));
                    DISPATCH();
                }
                
                do_kIf:
                {
                    if (pop_int()) {
                        ExecuteBlockVoid((*it)->fBranch1);
                    } else if ((*it)->fBranch2) { // Execute 'else' block if there is one
                        ExecuteBlockVoid((*it)->fBranch2);
                    }
                    DISPATCH();
                }
                
                //------------------------------------------
                // Standard math operations : stack version
                //------------------------------------------
                
                do_kAddReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 + v2);
                    DISPATCH();
                }
              
                do_kAddInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 + v2);
                    DISPATCH();
                }
                
                do_kSubReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 - v2);
                    DISPATCH();
                }
                
                do_kSubInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 - v2);
                    DISPATCH();
                }
                
                do_kMultReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 * v2);
                    DISPATCH();
                }
                
                do_kMultInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 * v2);
                    DISPATCH();
                }
                
                do_kDivReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 / v2);
                    DISPATCH();
                }
                
                do_kDivInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 / v2);
                    DISPATCH();
                }
                    
                do_kRemReal:
                {
                //    T v1 = pop_real();
                //    T v2 = pop_real();
                //    push_real(v1 % v2);
                //    DISPATCH();
                }
                
                do_kRemInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 % v2);
                    DISPATCH();
                }
                    
                // Shift operation
                do_kLshInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 << v2);
                    DISPATCH();
                }
                
                do_kRshInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 >> v2);
                    DISPATCH();
                }
                    
                // Comparaison Int
                do_kGTInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 > v2);
                    DISPATCH();
                }
                
                do_kLTInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 < v2);
                    DISPATCH();
                }
                
                do_kGEInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 >= v2);
                    DISPATCH();
                }
                
                do_kLEInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 <= v2);
                    DISPATCH();
                }
                
                do_kEQInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 == v2);
                    DISPATCH();
                }
                
                do_kNEInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 != v2);
                    DISPATCH();
                }
                    
                // Comparaison Real
                do_kGTReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 > v2);
                    DISPATCH();
                }
                
                do_kLTReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 < v2);
                    DISPATCH();
                }
                
                do_kGEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 >= v2);
                    DISPATCH();
                }
                
                do_kLEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 <= v2);
                    DISPATCH();
                }
                
                do_kEQReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 == v2);
                    DISPATCH();
                }
                
                do_kNEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 != v2);
                    DISPATCH();
                }
                    
                // Logical operations
                do_kANDInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 & v2);
                    DISPATCH();
                }
                
                do_kORInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 | v2);
                    DISPATCH();
                }
                
                do_kXORInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 ^ v2);
                    DISPATCH();
                }
                
                //-----------------------------------------
                // Standard math operations : heap version
                //-----------------------------------------
                
                do_kAddRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] + fRealHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kAddIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] + fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kSubRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] - fRealHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kSubIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] - fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kMultRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] * fRealHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kMultIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] * fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kDivRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] / fRealHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kDivIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] / fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kRemRealHeap:
                {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    DISPATCH();
                }
                
                do_kRemIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] % fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                // Shift operation
                do_kLshIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] << fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kRshIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] >> fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                // Comparaison Int
                do_kGTIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] > fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kLTIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] < fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kGEIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] >= fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kLEIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] <= fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kEQIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] == fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kNEIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] != fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                // Comparaison Real
                do_kGTRealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] > fRealHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kLTRealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] < fRealHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kGERealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] >= fRealHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kLERealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] <= fRealHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kEQRealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] == fRealHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kNERealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] != fRealHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                // Logical operations
                do_kANDIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] & fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kORIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] | fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                do_kXORIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] ^ fIntHeap[(*it)->fOffset2]);
                    DISPATCH();
                }
                
                //-------------------------------------------
                // Standard math operations : direct version
                //-------------------------------------------
                
                do_kAddRealDirect:
                {
                    push_real((*it)->fRealValue + fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kAddIntDirect:
                {
                    push_int((*it)->fIntValue + fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kSubRealDirect:
                {
                    push_real((*it)->fRealValue - fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kSubIntDirect:
                {
                    push_int((*it)->fIntValue - fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kMultRealDirect:
                {
                    push_real((*it)->fRealValue * fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kMultIntDirect:
                {
                    push_int((*it)->fIntValue * fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kDivRealDirect:
                {
                    push_real((*it)->fRealValue / fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kDivIntDirect:
                {
                    push_int((*it)->fIntValue / fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kRemRealDirect:
                {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    DISPATCH();
                }
                
                do_kRemIntDirect:
                {
                    push_int((*it)->fIntValue % fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                // Shift operation
                do_kLshIntDirect:
                {
                    push_int((*it)->fIntValue << fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kRshIntDirect:
                {
                    push_int((*it)->fIntValue >> fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                // Comparaison Int
                do_kGTIntDirect:
                {
                    push_int((*it)->fIntValue > fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kLTIntDirect:
                {
                    push_int((*it)->fIntValue < fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kGEIntDirect:
                {
                    push_int((*it)->fIntValue >= fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kLEIntDirect:
                {
                    push_int((*it)->fIntValue <= fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kEQIntDirect:
                {
                    push_int((*it)->fIntValue == fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kNEIntDirect:
                {
                    push_int((*it)->fIntValue != fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                // Comparaison Real
                do_kGTRealDirect:
                {
                    push_int((*it)->fRealValue > fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kLTRealDirect:
                {
                    push_int((*it)->fRealValue < fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kGERealDirect:
                {
                    push_int((*it)->fRealValue >= fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kLERealDirect:
                {
                    push_int((*it)->fRealValue <= fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kEQRealDirect:
                {
                    push_int((*it)->fRealValue == fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kNERealDirect:
                {
                    push_int((*it)->fRealValue != fRealHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                // Logical operations
                do_kANDIntDirect:
                {
                    push_int((*it)->fIntValue & fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kORIntDirect:
                {
                    push_int((*it)->fIntValue | fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                do_kXORIntDirect:
                {
                    push_int((*it)->fIntValue ^ fIntHeap[(*it)->fOffset1]);
                    DISPATCH();
                }
                
                //----------------------------------------------------
                // Standard math operations : direct inverted version
                // (non commutative operations)
                //----------------------------------------------------
                
                do_kSubRealDirectInvert:
                {
                    push_real(fRealHeap[(*it)->fOffset1] - (*it)->fRealValue);
                    DISPATCH();
                }
                
                do_kSubIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] - (*it)->fIntValue);
                    DISPATCH();
                }
                
                do_kDivRealDirectInvert:
                {
                    push_real(fRealHeap[(*it)->fOffset1] / (*it)->fRealValue);
                    DISPATCH();
                }
                
                do_kDivIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] / (*it)->fIntValue);
                    DISPATCH();
                }
                
                do_kRemRealDirectInvert:
                {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    DISPATCH();
                }
                
                do_kRemIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] % (*it)->fIntValue);
                    DISPATCH();
                }
                
                // Shift operation
                do_kLshIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] << (*it)->fIntValue);
                    DISPATCH();
                }
                
                do_kRshIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] >> (*it)->fIntValue);
                    DISPATCH();
                }
                
                // Comparaison Int
                do_kGTIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] > (*it)->fIntValue);
                    DISPATCH();
                }
                
                do_kLTIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] < (*it)->fIntValue);
                    DISPATCH();
                }
                
                do_kGEIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] >= (*it)->fIntValue);
                    DISPATCH();
                }
                
                do_kLEIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] <= (*it)->fIntValue);
                    DISPATCH();
                }
                
                // Comparaison Real
                do_kGTRealDirectInvert:
                {
                    push_int(fRealHeap[(*it)->fOffset1] > (*it)->fRealValue);
                    DISPATCH();
                }
                
                do_kLTRealDirectInvert:
                {
                    push_int(fRealHeap[(*it)->fOffset1] < (*it)->fRealValue);
                    DISPATCH();
                }
                
                do_kGERealDirectInvert:
                {
                    push_int(fRealHeap[(*it)->fOffset1] >= (*it)->fRealValue);
                    DISPATCH();
                }
                
                do_kLERealDirectInvert:
                {
                    push_int(fRealHeap[(*it)->fOffset1] <= (*it)->fRealValue);
                    DISPATCH();
                }
       
                //---------------------
                // Extended unary math
                //---------------------
                
                do_kAbs:
                {
                    int v = pop_int();
                    push_int(abs(v));
                    DISPATCH();
                }
                
                do_kAbsf:
                {
                    T v = pop_real();
                    push_real(fabsf(v));
                    DISPATCH();
                }
                
                do_kAcosf:
                {
                    T v = pop_real();
                    push_real(acosf(v));
                    DISPATCH();
                }
                
                do_kAsinf:
                {
                    T v = pop_real();
                    push_real(asinf(v));
                    DISPATCH();
                }
                
                do_kAtanf:
                {
                    T v = pop_real();
                    push_real(atanf(v));
                    DISPATCH();
                }
                
                do_kCeilf:
                {
                    T v = pop_real();
                    push_real(ceilf(v));
                    DISPATCH();
                }
                
                do_kCosf:
                {
                    T v = pop_real();
                    push_real(cosf(v));
                    DISPATCH();
                }
                
                do_kCoshf:
                {
                    T v = pop_real();
                    push_real(coshf(v));
                    DISPATCH();
                }
                
                do_kExpf:
                {
                    T v = pop_real();
                    push_real(expf(v));
                    DISPATCH();
                }

                do_kFloorf:
                {
                    T v = pop_real();
                    push_real(floorf(v));
                    DISPATCH();
                }

                do_kLogf:
                {
                    T v = pop_real();
                    push_real(logf(v));
                    DISPATCH();
                }
                
                do_kLog10f:
                {
                    T v = pop_real();
                    push_real(log10f(v));
                    DISPATCH();
                }
                
                do_kRoundf:
                {
                    T v = pop_real();
                    push_real(roundf(v));
                    DISPATCH();
                }
                
                do_kSinf:
                {
                    T v = pop_real();
                    push_real(sinf(v));
                    DISPATCH();
                }
                
                do_kSinhf:
                {
                    T v = pop_real();
                    push_real(sinhf(v));
                    DISPATCH();
                }
                
                do_kSqrtf:
                {
                    T v = pop_real();
                    push_real(sqrtf(v));
                    DISPATCH();
                }
                
                do_kTanf:
                {
                    T v = pop_real();
                    push_real(tanf(v));
                    DISPATCH();
                }
                
                do_kTanhf:
                {
                    T v = pop_real();
                    push_real(tanhf(v));
                    DISPATCH();
                }
                
                //---------------------
                // Extended binary math
                //---------------------
                
                do_kAtan2f:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(atan2f(v1, v2));
                    DISPATCH();
                }
           
                do_kFmodf:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(fmodf(v1, v2));
                    DISPATCH();
                }
                
                do_kPowf:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(powf(v1, v2));
                    DISPATCH();
                }
                
                do_kMax:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(std::max(v1, v2));
                    DISPATCH();
                }
                
                do_kMaxf:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(std::max(v1, v2));
                    DISPATCH();
                }
                
                do_kMin:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(std::min(v1, v2));
                    DISPATCH();
                }
                
                do_kMinf:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(std::min(v1, v2));
                    DISPATCH();
                }
                
                //------------------------------------
                // Extended unary math (head version)
                ///------------------------------------
                
                do_kAbsHeap:
                {
                    push_int(abs(fIntHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kAbsfHeap:
                {
                    push_real(fabsf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kAcosfHeap:
                {
                    push_real(acosf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kAsinfHeap:
                {
                    push_real(asinf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kAtanfHeap:
                {
                    push_real(atanf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kCeilfHeap:
                {
                    push_real(ceilf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kCosfHeap:
                {
                    push_real(cosf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kCoshfHeap:
                {
                    push_real(coshf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kExpfHeap:
                {
                    push_real(expf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kFloorfHeap:
                {
                    push_real(floorf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kLogfHeap:
                {
                    push_real(logf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kLog10fHeap:
                {
                    push_real(log10f(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kRoundfHeap:
                {
                    push_real(roundf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kSinfHeap:
                {
                    push_real(sinf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kSinhfHeap:
                {
                    push_real(sinhf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kSqrtfHeap:
                {
                    push_real(sqrtf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kTanfHeap:
                {
                    push_real(tanf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                do_kTanhfHeap:
                {
                    push_real(tanhf(fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }
                
                //-------------------------------------
                // Extended binary math (heap version)
                //-------------------------------------
                
                do_kAtan2fHeap:
                {
                    push_real(atan2f(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    DISPATCH();
                }

                do_kFmodfHeap:
                {
                    push_real(fmodf(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    DISPATCH();
                }

                do_kPowfHeap:
                {
                    push_real(powf(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    DISPATCH();
                }

                do_kMaxHeap:
                {
                    push_int(std::max(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
                    DISPATCH();
                }

                do_kMaxfHeap:
                {
                    push_real(std::max(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    DISPATCH();
                }

                do_kMinHeap:
                {
                    push_int(std::min(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
                    DISPATCH();
                }

                do_kMinfHeap:
                {
                    push_real(std::min(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    DISPATCH();
                }

                //-------------------------------------
                // Extended binary math (direct version)
                //-------------------------------------

                do_kAtan2fDirect:
                {
                    push_real(atan2f((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }

                do_kFmodfDirect:
                {
                    push_real(fmodf((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }

                do_kPowfDirect:
                {
                    push_real(powf((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }

                do_kMaxDirect:
                {
                    push_int(std::max((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
                    DISPATCH();
                }

                do_kMaxfDirect:
                {
                    push_real(std::max((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }

                do_kMinDirect:
                {
                    push_int(std::min((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
                    DISPATCH();
                }

                do_kMinfDirect:
                {
                    push_real(std::min((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    DISPATCH();
                }

                //-------------------------------------------------------------------
                // Extended binary math (direct version) : non commutative operations
                //-------------------------------------------------------------------

                do_kAtan2fDirectInvert:
                {
                    push_real(atan2f(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    DISPATCH();
                }

                do_kFmodfDirectInvert:
                {
                    push_real(fmodf(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    DISPATCH();
                }

                do_kPowfDirectInvert:
                {
                    push_real(powf(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    DISPATCH();
                }

                //---------
                // Control
                //---------
                
                do_kLoop:
                {
                    ExecuteLoopBlock((*it)->fBranch1, (*it)->fOffset1, (*it)->fIntValue);
                    DISPATCH();
                }
            }
            
            switch (get_result) {
                    
                case 0:
                    break;
                    
                case 1:
                    res_int = pop_int();
                    break;
                    
                case 2:
                    res_real = pop_real();
                    break;
                    
            }
            
            //printf("END real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index);
            assert(real_stack_index == 0 && int_stack_index == 0);
        }
    
        void ExecuteLoopBlock(FIRBlockInstruction<T>* block, int count)
        {
            // 2 first compiled instructions are not needed
            FIRBasicInstruction<T>* loop = block->fInstructions[2];
            ExecuteLoopBlock(loop->fBranch1, loop->fOffset1, count);
        }
    
        inline void ExecuteLoopBlock(FIRBlockInstruction<T>* block, int loop_offset, int loop_count)
        {
            for (fIntHeap[loop_offset] = 0; fIntHeap[loop_offset] < loop_count; fIntHeap[loop_offset]++) {
                ExecuteBlockVoid(block);
            }
        }

        inline int ExecuteBlockInt(FIRBlockInstruction<T>* block)
        {
            int res_int;
            T dummy_res_real;
            ExecuteBlockFast(block, res_int, dummy_res_real, 1);
            return res_int;
        }
    
        inline T ExecuteBlockReal(FIRBlockInstruction<T>* block)
        {
            int dummy_res_int;
            T res_real;
            ExecuteBlockFast(block, dummy_res_int, res_real, 2);
            return res_real;
        }
    
        inline void ExecuteBlockVoid(FIRBlockInstruction<T>* block)
        {
            int dummy_res_int;
            T dummy_res_real;
            ExecuteBlockFast(block, dummy_res_int, dummy_res_real, 0);
        }
    
    public:
    
        FIRInterpreter(int real_heap_size, int int_heap_size, int sr_offset)
        {
            printf("FIRInterpreter : real_heap_size = %d int_heap_size = %d sr_offset = %d\n", real_heap_size, int_heap_size, sr_offset);
            
            // HEAP
            fRealHeapSize = real_heap_size;
            fIntHeapSize = int_heap_size;
            fSROffset = sr_offset;
            fRealHeap = new T[real_heap_size];
            fIntHeap = new int[int_heap_size];
            
            // Initialise HEAP with 0
            memset(fRealHeap, 0, real_heap_size * sizeof(T));
            memset(fIntHeap, 0, int_heap_size * sizeof(int));
            
            // Stack
            fRealStackSize = 4096 * 1;
            fIntStackSize = 4096 * 1;
        }
        
        virtual ~FIRInterpreter()
        {
            delete [] fRealHeap;
            delete [] fIntHeap;
        }
 
};

#endif
