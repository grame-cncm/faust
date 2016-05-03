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

#ifndef _FIR_INTERPRETER_OPTIMIZER_H
#define _FIR_INTERPRETER_OPTIMIZER_H

#include <string>
#include <math.h>
#include <assert.h>
#include <iostream>

#include "interpreter_bytecode.hh"

// Block optimizer : compact and reorganize instructions

template <class T>
struct FIRInstructionOptimizer {
    
    // Rewrite a sequence of instructions starting from 'cur' to 'end' in a new single instruction.
    // Update 'end' so that caller can move at the correct next location
    virtual FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        return 0;
    }
    
    // Return an optimized block by traversing it (including sub-blocks) with an 'optimizer'
    static FIRBlockInstruction<T>* optimize_aux(FIRBlockInstruction<T>* cur_block, FIRInstructionOptimizer<T>& optimizer)
    {
        assert(cur_block);
        
        FIRBlockInstruction<T>* new_block = new FIRBlockInstruction<T>();
        InstructionIT next, cur = cur_block->fInstructions.begin();
        
        do {
            FIRBasicInstruction<T>* inst = *cur;
            if (inst->fOpcode == FIRInstruction::kLoop) {
                new_block->push(new FIRBasicInstruction<T>(inst->fOpcode,
                                                           inst->fIntValue, inst->fRealValue,
                                                           inst->fOffset1, inst->fOffset2,
                                                           optimize_aux(inst->fBranch1, optimizer),
                                                           0));
                cur++;
            } else if (inst->fOpcode == FIRInstruction::kIf) {
                new_block->push(new FIRBasicInstruction<T>(inst->fOpcode,
                                                            inst->fIntValue, inst->fRealValue,
                                                            inst->fOffset1, inst->fOffset2,
                                                            optimize_aux(inst->fBranch1, optimizer),
                                                            optimize_aux(inst->fBranch2, optimizer)));
                cur++;
            } else if (inst->fOpcode == FIRInstruction::kCondBranch) {   // Special case for loops
                FIRBasicInstruction<T>* optimized = optimizer.rewrite(cur, next);
                optimized->fBranch1 = new_block;
                new_block->push(optimized);
                cur = next;
            } else {
                new_block->push(optimizer.rewrite(cur, next));
                cur = next;
            }
        } while (cur != cur_block->fInstructions.end());
        
        return new_block;
    }
    
    // Apply an optimizer on the block, return the optimized new block, then delete the original one
    static FIRBlockInstruction<T>* optimize(FIRBlockInstruction<T>* cur_block, FIRInstructionOptimizer<T>& optimizer)
    {
        FIRBlockInstruction<T>* new_block = optimize_aux(cur_block, optimizer);
        delete cur_block;
        return new_block;
    }
    
};

// Copy (= identity) optimizer (used to test...)
template <class T>
struct FIRInstructionCopyOptimizer : public FIRInstructionOptimizer<T>  {
    
    FIRInstructionCopyOptimizer()
    {
        //std::cout << "FIRInstructionCopyOptimizer" << std::endl;
    }
    
    virtual FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        end = cur + 1;
        return (*cur)->copy();
    }
};

// Cast optimizer
template <class T>
struct FIRInstructionCastOptimizer : public FIRInstructionOptimizer<T>  {
    
    
    FIRInstructionCastOptimizer()
    {
        //std::cout << "FIRInstructionCastOptimizer" << std::endl;
    }
    
    virtual FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FIRBasicInstruction<T>* inst1 = *cur;
        FIRBasicInstruction<T>* inst2 = *(cur + 1);
        
        if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kCastReal) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kCastRealHeap, 0, 0, inst1->fOffset1, 0);
        } else if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kCastInt) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kCastIntHeap, 0, 0, inst1->fOffset1, 0);
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
};

// Rewrite indexed Load/Store as simple Load/Store
template <class T>
struct FIRInstructionLoadStoreOptimizer : public FIRInstructionOptimizer<T> {
    
    
    FIRInstructionLoadStoreOptimizer()
    {
        //std::cout << "FIRInstructionLoadStoreOptimizer" << std::endl;
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
        //std::cout << "FIRInstructionMoveOptimizer" << std::endl;
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

// Rewrite math operations as 'heap', 'stack' or 'direct' versions
template <class T>
struct FIRInstructionMathOptimizer : public FIRInstructionOptimizer<T> {
    
    FIRInstructionMathOptimizer()
    {
        //std::cout << "FIRInstructionMathOptimizer" << std::endl;
    }
    
    FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FIRBasicInstruction<T>* inst1 = *cur;
        FIRBasicInstruction<T>* inst2 = *(cur + 1);
        FIRBasicInstruction<T>* inst3 = *(cur + 2);
        
        // kLoadReal op kLoadReal ==> Heap version
        if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadReal op kLoadReal ==> Heap version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
        // kLoadRInt op kLoadInt ==> Heap version
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadRInt op kLoadInt ==> Heap version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
        // kLoadReal op kRealValue ==> Direct version
        } else if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kRealValue && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadReal op kRealValue ==> Direct version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Direct[inst3->fOpcode], 0, inst2->fRealValue, inst1->fOffset1, 0);
        // kRealValue op kLoadReal ==> Direct version
        } else if (inst1->fOpcode == FIRInstruction::kRealValue && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kRealValue op kLoadReal ==> Direct version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2DirectInvert[inst3->fOpcode], 0, inst1->fRealValue, inst2->fOffset1, 0);
        // kLoadInt op kIntValue ==> Direct version
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kIntValue && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadInt op kIntValue ==> Direct version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Direct[inst3->fOpcode], inst2->fIntValue, 0, inst1->fOffset1, 0);
        // kIntValue op kLoadInt ==> Direct version
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kIntValue op kLoadInt ==> Direct version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2DirectInvert[inst3->fOpcode], inst1->fIntValue, 0, inst2->fOffset1, 0);
        // kLoadReal/kLoadInt binary op ==> Stack version
        } else if (((inst1->fOpcode == FIRInstruction::kLoadReal) || (inst1->fOpcode == FIRInstruction::kLoadInt)) && FIRInstruction::isMath(inst2->fOpcode)) {
            //std::cout << "kLoadReal/kLoadInt binary op ==> Stack version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Stack[inst2->fOpcode], 0, 0, inst1->fOffset1, 0);
        // kLoadReal unary  ==> Heap version
        } else if (inst1->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isExtendedUnaryMath(inst2->fOpcode)) {
            //std::cout << "kLoadReal unary ==> Heap version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRExtendedMath2Heap[inst2->fOpcode], 0, 0, inst1->fOffset1, 0);
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
    
};

#endif
