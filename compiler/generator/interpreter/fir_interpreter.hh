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

// Copy (= identity) optimizer (to test...)
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

// Rewrite some binary math operation as 'heap' or 'direct' versions
template <class T>
struct FIRInstructionMathOptimizer : public FIRInstructionOptimizer<T> {
    
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
    
    // Return an optimized block
    static FIRBlockInstruction* optimize_aux(FIRBlockInstruction<T>* cur_block, FIRInstructionOptimizer<T>& optimizer)
    {
        FIRBlockInstruction<T>* new_block = new FIRBlockInstruction<T>();
        InstructionIT next, cur = cur_block->fInstructions.begin();
        
        do {
            FIRBasicInstruction<T>* inst = *cur;
            if (inst->fOpcode == FIRInstruction::kLoop) {
                new_block->push(new FIRBasicInstruction<T>(FIRInstruction::kLoop,
                                                           inst->fIntValue, inst->fRealValue, inst->fOffset1, inst->fOffset2,
                                                           FIRBlockInstruction::optimize_aux(inst->fBranch1, optimizer), 0));
                cur++;
            } else if (inst->fOpcode == FIRInstruction::kSelectInt || inst->fOpcode == FIRInstruction::kSelectReal) {
                new_block->push(new FIRBasicInstruction<T>(inst->fOpcode,
                                                           inst->fIntValue, inst->fRealValue, inst->fOffset1, inst->fOffset2,
                                                           FIRBlockInstruction::optimize_aux(inst->fBranch1, optimizer),
                                                           FIRBlockInstruction::optimize_aux(inst->fBranch2, optimizer)));
                cur++;
            } else if (inst->fOpcode == FIRInstruction::kIf) {
                new_block->push(new FIRBasicInstruction<T>(FIRInstruction::kIf,
                                                           inst->fIntValue, inst->fRealValue, inst->fOffset1, inst->fOffset2,
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
    
        inline void ExecuteSlowBlock(FIRBlockInstruction<T>* block, int& res_int, T& res_real, int get_result)
        {
            InstructionIT it;
             
            int real_stack_index = 0;
            int int_stack_index = 0;
            
            //printf("ExecuteBlock size = %d fRealStackSize = %d fIntStackSize = %d\n", block->fInstructions.size(), fRealStackSize, fIntStackSize); 
        
            T real_stack[fRealStackSize];
            int int_stack[fIntStackSize];
             
            for (it = block->fInstructions.begin(); it != block->fInstructions.end(); it++) {
                
                //printf("fOpcode %d real_stack_index %d int_stack_index %d\n", (*it)->fOpcode, real_stack_index, int_stack_index);
             
                switch ((*it)->fOpcode) {
                        
                    // Number operations
                    case FIRInstruction::kRealValue:
                        push_real((*it)->fRealValue);
                        break;
                         
                    case FIRInstruction::kIntValue:
                        push_int((*it)->fIntValue);
                        break;
                    
                    // Memory operations
                    case FIRInstruction::kLoadReal:
                        push_real(fRealHeap[(*it)->fOffset1]);
                        break;
                        
                    case FIRInstruction::kLoadInt:
                        push_int(fIntHeap[(*it)->fOffset1]);
                        break;
                        
                    case FIRInstruction::kStoreReal:
                        fRealHeap[(*it)->fOffset1] = pop_real();
                        break;
                        
                    case FIRInstruction::kStoreInt:
                        fIntHeap[(*it)->fOffset1] = pop_int();
                        break;
                         
                    case FIRInstruction::kLoadIndexedReal:
                        push_real(fRealHeap[(*it)->fOffset1 + pop_int()]);
                        break;
                        
                    case FIRInstruction::kLoadIndexedInt: {
                        int val = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1 + val]);
                        break;
                    }
                         
                    case FIRInstruction::kStoreIndexedReal:
                        fRealHeap[(*it)->fOffset1 + pop_int()] = pop_real();
                        break;
                    
                    case FIRInstruction::kStoreIndexedInt: {
                        int offset = pop_int();
                        fIntHeap[(*it)->fOffset1 + offset] = pop_int();
                        break;
                    }
                        
                    case FIRInstruction::kMoveReal: {
                        fRealHeap[(*it)->fOffset2] = fRealHeap[(*it)->fOffset1];
                        break;
                    }
                        
                    case FIRInstruction::kMoveInt: {
                        fIntHeap[(*it)->fOffset2] = fIntHeap[(*it)->fOffset1];
                        break;
                    }
            
                    // Input/output access
                    case FIRInstruction::kLoadInput: 
                        push_real(fInputs[(*it)->fOffset1][pop_int()]);
                        break;
                        
                    case FIRInstruction::kStoreOutput: {
                        fOutputs[(*it)->fOffset1][pop_int()] = pop_real();
                        break;
                    }
                      
                    // Cast operations
                    case FIRInstruction::kCastReal: {
                        push_real(T(pop_int()));
                        break;
                    }
                        
                    case FIRInstruction::kCastInt:
                        push_int(int(pop_real()));
                        break;
                        
                    // Select/If operation
                    case FIRInstruction::kSelectInt: {
                        int cond = pop_int();
                        push_int(cond ? ExecuteBlockInt((*it)->fBranch1) : ExecuteBlockInt((*it)->fBranch2));
                        break;
                    }
                
                    case FIRInstruction::kSelectReal:
                        push_real(pop_int() ? ExecuteBlockInt((*it)->fBranch1) : ExecuteBlockInt((*it)->fBranch2));
                        break;
                        
                    case FIRInstruction::kIf: {
                        if (pop_int()) {
                            ExecuteBlockInt((*it)->fBranch1);
                        } else if ((*it)->fBranch2) { // Execute 'else' block if there is one
                            ExecuteBlockInt((*it)->fBranch2);
                        }
                        break;
                    }
                        
                    // Standard math operations
                    case FIRInstruction::kAddReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_real(v1 + v2);
                        break;
                    }
                        
                    case FIRInstruction::kAddInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 + v2);
                        break;
                    }
       
                    case FIRInstruction::kSubReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_real(v1 - v2);
                        break;
                    }
                        
                    case FIRInstruction::kSubInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 - v2);
                        break;
                    }
                        
                    case FIRInstruction::kMultReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_real(v1 * v2);
                        break;
                    }
                        
                    case FIRInstruction::kMultInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 * v2);
                        break;
                    }
                        
                    case FIRInstruction::kDivReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_real(v1 / v2);
                        break;
                    }
                        
                    case FIRInstruction::kDivInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 / v2);
                        break;
                    }
                    
                    //case FIRInstruction::kRemReal: {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    break;
                    //}
                        
                    case FIRInstruction::kRemInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 % v2);
                        break;
                    }
                        
                    // Shift operation
                    case FIRInstruction::kLshInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 << v2);
                        break;
                    }
       
                    case FIRInstruction::kRshInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 >> v2);
                        break;
                    }      
                                   
                    // Comparaison Int
                    case FIRInstruction::kGTInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 > v2);
                        break;
                    }         
                                     
                    case FIRInstruction::kLTInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 < v2);
                        break;
                    }      
                                        
                    case FIRInstruction::kGEInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 >= v2);
                        break;
                    }           
                                   
                    case FIRInstruction::kLEInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 <= v2);
                        break;
                    }           
                               
                    case FIRInstruction::kEQInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 == v2);
                        break;
                    }             
                                 
                    case FIRInstruction::kNEInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 != v2);
                        break;
                    }        
                                      
                    // Comparaison Real    
                    case FIRInstruction::kGTReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 > v2);
                        break;
                    }  
                        
                    case FIRInstruction::kLTReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 < v2);
                        break;
                    }  
                         
                    case FIRInstruction::kGEReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 >= v2);
                        break;
                    }  
                        
                    case FIRInstruction::kLEReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 <= v2);
                        break;
                    }  
                    
                    case FIRInstruction::kEQReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 == v2);
                        break;
                    }  
                        
                    case FIRInstruction::kNEReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 != v2);
                        break;
                    }  
                    
                    // Logical operations
                    case FIRInstruction::kANDInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 & v2);
                        break;
                    }     
                                                            
                    case FIRInstruction::kORInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 | v2);
                        break;
                    }     
                                                               
                    case FIRInstruction::kXORInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 ^ v2);
                        break;
                    }                        
                       
                    // Other Math operations
                    case FIRInstruction::kSin: {
                        T v = pop_real();
                        push_real(sinf(v));
                        break;
                    }
                        
                    case FIRInstruction::kCos: {
                        T v = pop_real();
                        push_real(cosf(v));
                        break;
                    }
                        
                    case FIRInstruction::kSqrt: {
                        T v = pop_real();
                        push_real(sqrtf(v));
                        break;
                    }
                        
                    case FIRInstruction::kLoop: {
                        ExecuteLoopBlock((*it)->fBranch1, (*it)->fOffset1, (*it)->fIntValue);
                        break;
                    }
                    
                    default:
                        break;
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
            
            //printf("real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index);
        }
    
        inline void ExecuteBlockFast(FIRBlockInstruction<T>* block, int& res_int, T& res_real, int get_result)
        {
            int real_stack_index = 0;
            int int_stack_index = 0;
            
            T real_stack[fRealStackSize];
            int int_stack[fIntStackSize];
            
            #define DISPATCH_FIRST() { goto *fDispatchTable[(*it)->fOpcode]; }
            #define DISPATCH() { it++; goto *fDispatchTable[(*it)->fOpcode]; }
            
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
                
                // Standard math (direct version) : non commutatives operations
                &&do_kSubRealDirectInvert, &&do_kSubIntDirectInvert,
                &&do_kDivRealDirectInvert, &&do_kDivIntDirectInvert,
                &&do_kRemRealDirectInvert, &&do_kRemIntDirectInvert,
                &&do_kLshIntDirectInvert, &&do_kRshIntDirectInvert,
                &&do_kGTIntDirectInvert, &&do_kLTIntDirectInvert,
                &&do_kGEIntDirectInvert, &&do_kLEIntDirectInvert,
                &&do_kGTRealDirectInvert, &&do_kLTRealDirectInvert,
                &&do_kGERealDirectInvert, &&do_kLERealDirectInvert,
                
                // Extended math
                &&do_kSqrt,
                &&do_kSin, &&do_kCos,
                
                // Control
                &&do_kLoop
            };
            
            //printf("Start\n");
            
            InstructionIT it = block->fInstructions.begin();
            DISPATCH_FIRST();
            
            while (1) {
                
                do_kHalt:
                {
                    //printf("do_kHalt\n");
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
                    int val = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1 + val]);
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
                    push_real(pop_int() ? ExecuteBlockInt((*it)->fBranch1) : ExecuteBlockInt((*it)->fBranch2));
                    DISPATCH();
                }
                
                do_kIf:
                {
                    if (pop_int()) {
                        ExecuteBlockInt((*it)->fBranch1);
                    } else if ((*it)->fBranch2) { // Execute 'else' block if there is one
                        ExecuteBlockInt((*it)->fBranch2);
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
                
                //------------------
                // Heap version
                //-----------------
                
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
                
                //-----------------
                // Direct version
                //-----------------
                
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
                
                //-----------------------------
                // Direct inverted version
                // (non commutative opetation)
                //-----------------------------
                
                
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
       
                // Math operations
                do_kSqrt:
                {
                    T v = pop_real();
                    push_real(sqrtf(v));
                    DISPATCH();
                }
                
                do_kSin:
                {
                    T v = pop_real();
                    push_real(sinf(v));
                    DISPATCH();
                }
                
                do_kCos:
                {
                    T v = pop_real();
                    push_real(cosf(v));
                    DISPATCH();
                }
                
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
            
            //printf("real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index);
        }
        
        void ExecuteLoopBlock(FIRBlockInstruction<T>* block, int loop_offset, int loop_count)
        {
            int res_int;
            T res_real;
            
            for (fIntHeap[loop_offset] = 0; fIntHeap[loop_offset] < loop_count; fIntHeap[loop_offset]++) {
                //ExecuteSlowBlock(block, res_int, res_real, 0);
                ExecuteBlockFast(block, res_int, res_real, 0);
            }
        }

        int ExecuteBlockInt(FIRBlockInstruction<T>* block)
        {
            int res_int;
            T res_real;
            //ExecuteSlowBlock(block, res_int, res_real, 1);
            ExecuteBlockFast(block, res_int, res_real, 1);
            return res_int;
        }
    
        T ExecuteBlockReal(FIRBlockInstruction<T>* block)
        {
            int res_int;
            T res_real;
            //ExecuteSlowBlock(block, res_int, res_real, 2);
            ExecuteBlockFast(block, res_int, res_real, 2);
            return res_real;
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
