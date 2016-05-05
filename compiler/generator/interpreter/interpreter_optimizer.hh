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

static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2Heap;
static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2Stack;
static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2StackValue;
static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2Value;
static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRMath2ValueInvert;

static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2Heap;
static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2Stack;
static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2StackValue;
static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2Value;
static std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> gFIRExtendedMath2ValueInvert;

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
            } else {
                FIRBasicInstruction<T>* optimized = optimizer.rewrite(cur, next);
                // Special case for loops
                if (inst->fOpcode == FIRInstruction::kCondBranch) { optimized->fBranch1 = new_block; }
                new_block->push(optimized);
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
    
    static void initTables()
    {
        // Initializations for FIRInstructionMathOptimizer pass
        
        //===============
        // Math
        //===============
        
        // Init heap opcode
        for (int i = FIRInstruction::kAddReal; i <= FIRInstruction::kXORInt; i++) {
            gFIRMath2Heap[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
        }
        
        // Init stack opcode
        for (int i = FIRInstruction::kAddReal; i <= FIRInstruction::kXORInt; i++) {
            gFIRMath2Stack[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAddRealStack - FIRInstruction::kAddReal));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealStack - FIRInstruction::kAddReal)] << std::endl;
        }
        
        // Init stack/value opcode
        for (int i = FIRInstruction::kAddReal; i <= FIRInstruction::kXORInt; i++) {
            gFIRMath2StackValue[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAddRealStackValue - FIRInstruction::kAddReal));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealStackValue - FIRInstruction::kAddReal)] << std::endl;
        }
        
        // Init Value opcode
        for (int i = FIRInstruction::kAddReal; i <= FIRInstruction::kXORInt; i++) {
            gFIRMath2Value[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAddRealValue - FIRInstruction::kAddReal));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealValue - FIRInstruction::kAddReal)] << std::endl;
        }
        
        // Init Value opcode (non commutative operation)
        for (int i = FIRInstruction::kAddReal; i <= FIRInstruction::kXORInt; i++) {
            gFIRMath2ValueInvert[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAddRealValue - FIRInstruction::kAddReal));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealValue - FIRInstruction::kAddReal)] << std::endl;
        }
        
        // Manually set inverted versions
        gFIRMath2ValueInvert[FIRInstruction::kSubReal] = FIRInstruction::kSubRealValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kSubInt] = FIRInstruction::kSubIntValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kDivReal] = FIRInstruction::kDivRealValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kDivInt] = FIRInstruction::kDivIntValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kRemReal] = FIRInstruction::kRemRealValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kRemInt] = FIRInstruction::kRemIntValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kLshInt] = FIRInstruction::kLshIntValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kRshInt] = FIRInstruction::kRshIntValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kGTInt] = FIRInstruction::kGTIntValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kLTInt] = FIRInstruction::kLTIntValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kGEInt] = FIRInstruction::kGEIntValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kLEInt] = FIRInstruction::kLEIntValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kGTReal] = FIRInstruction::kGTRealValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kLTReal] = FIRInstruction::kLTRealValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kGEReal] = FIRInstruction::kGERealValueInvert;
        gFIRMath2ValueInvert[FIRInstruction::kLEReal] = FIRInstruction::kLERealValueInvert;
        
        //===============
        // EXTENDED math
        //===============
        
        // Init unary extended math heap opcode
        for (int i = FIRInstruction::kAbs; i <= FIRInstruction::kTanhf; i++) {
            gFIRExtendedMath2Heap[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAbsHeap - FIRInstruction::kAbs));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
        }
        
        // Init binary extended math heap opcode
        for (int i = FIRInstruction::kAtan2f; i <= FIRInstruction::kMinf; i++) {
            gFIRExtendedMath2Heap[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAtan2fHeap - FIRInstruction::kAtan2f));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
        }
        
        
        // Init binary extended math stack opcode
        for (int i = FIRInstruction::kAtan2f; i <= FIRInstruction::kMinf; i++) {
            gFIRExtendedMath2Stack[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAtan2fStack - FIRInstruction::kAtan2f));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
        }
        
        // Init binary extended math stack/value opcode
        for (int i = FIRInstruction::kAtan2f; i <= FIRInstruction::kMinf; i++) {
            gFIRExtendedMath2StackValue[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAtan2fStackValue - FIRInstruction::kAtan2f));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
        }
        
        // Init unary math Value opcode
        for (int i = FIRInstruction::kAtan2f; i <= FIRInstruction::kMinf; i++) {
            gFIRExtendedMath2Value[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAtan2fValue - FIRInstruction::kAtan2f));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
        }
        
        // Init unary math Value opcode : non commutative operations
        for (int i = FIRInstruction::kAtan2f; i <= FIRInstruction::kPowf; i++) {
            gFIRExtendedMath2ValueInvert[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAtan2fValueInvert - FIRInstruction::kAtan2f));
            //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
        }
        
        // Test
        
        /*
         std::cout << "gFIRExtendedMath2Heap" << std::endl;
         for (int i = FIRInstruction::kAbs; i <= FIRInstruction::kTanhf; i++) {
         if (FIRInstruction::gFIRExtendedMath2Heap.find(FIRInstruction::Opcode(i)) !=  FIRInstruction::gFIRExtendedMath2Heap.end()) {
         std::cout   << gFIRInstructionTable[FIRInstruction::Opcode(i)] << " ==> "
         << gFIRInstructionTable[FIRInstruction::gFIRExtendedMath2Heap[FIRInstruction::Opcode(i)]] << std::endl;
         }
         }
         std::cout << "gFIRExtendedMath2Heap" << std::endl << std::endl;
         for (int i = FIRInstruction::kAbsHeap; i <= FIRInstruction::kMinf; i++) {
         if (FIRInstruction::gFIRExtendedMath2Heap.find(FIRInstruction::Opcode(i)) !=  FIRInstruction::gFIRExtendedMath2Heap.end()) {
         std::cout   << gFIRInstructionTable[FIRInstruction::Opcode(i)] << " ==> "
         << gFIRInstructionTable[FIRInstruction::gFIRExtendedMath2Heap[FIRInstruction::Opcode(i)]] << std::endl;
         }
         }
         
         std::cout << "gFIRExtendedMath2Stack" << std::endl << std::endl;
         for (int i = FIRInstruction::kAbsHeap; i <= FIRInstruction::kMinf; i++) {
         if (FIRInstruction::gFIRExtendedMath2Stack.find(FIRInstruction::Opcode(i)) !=  FIRInstruction::gFIRExtendedMath2Stack.end()) {
         std::cout   << gFIRInstructionTable[FIRInstruction::Opcode(i)] << " ==> "
         << gFIRInstructionTable[FIRInstruction::gFIRExtendedMath2Stack[FIRInstruction::Opcode(i)]] << std::endl;
         }
         }
         
         std::cout << "gFIRExtendedMath2StackValue" << std::endl << std::endl;
         for (int i = FIRInstruction::kAbsHeap; i <= FIRInstruction::kMinf; i++) {
         if (FIRInstruction::gFIRExtendedMath2StackValue.find(FIRInstruction::Opcode(i)) !=  FIRInstruction::gFIRExtendedMath2StackValue.end()) {
         std::cout   << gFIRInstructionTable[FIRInstruction::Opcode(i)] << " ==> "
         << gFIRInstructionTable[FIRInstruction::gFIRExtendedMath2StackValue[FIRInstruction::Opcode(i)]] << std::endl;
         }
         }
         
         std::cout << "gFIRExtendedMath2Value" << std::endl << std::endl;
         for (int i = FIRInstruction::kAbsHeap; i <= FIRInstruction::kMinf; i++) {
         if (FIRInstruction::gFIRExtendedMath2Value.find(FIRInstruction::Opcode(i)) !=  FIRInstruction::gFIRExtendedMath2Value.end()) {
         std::cout   << gFIRInstructionTable[FIRInstruction::Opcode(i)] << " ==> "
         << gFIRInstructionTable[FIRInstruction::gFIRExtendedMath2Value[FIRInstruction::Opcode(i)]] << std::endl;
         }
         }
         
         std::cout << "gFIRExtendedMath2ValueInvert" << std::endl << std::endl;
         for (int i = FIRInstruction::kAbsHeap; i <= FIRInstruction::kMinf; i++) {
         if (FIRInstruction::gFIRExtendedMath2ValueInvert.find(FIRInstruction::Opcode(i)) !=  FIRInstruction::gFIRExtendedMath2ValueInvert.end()) {
         std::cout   << gFIRInstructionTable[FIRInstruction::Opcode(i)] << " ==> "
         << gFIRInstructionTable[FIRInstruction::gFIRExtendedMath2ValueInvert[FIRInstruction::Opcode(i)]] << std::endl;
         }
         }
         */
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

// Rewrite heap Load/Store as Move or direct Value store
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
        
        // Optimize Heap Load/Store as Move
        if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kStoreReal) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kMoveReal, 0, 0, inst2->fOffset1, inst1->fOffset1);   // reverse order
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kStoreInt) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kMoveInt, 0, 0, inst2->fOffset1, inst1->fOffset1);    // reverse order
        // Optimize Value Load/Store as direct value Store
        } else if (inst1->fOpcode == FIRInstruction::kRealValue && inst2->fOpcode == FIRInstruction::kStoreReal) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kStoreRealValue, 0, inst1->fRealValue, inst2->fOffset1, 0);
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kStoreInt) {
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::kStoreIntValue, inst1->fIntValue, 0, inst2->fOffset1, 0);
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
    
};

// Rewrite math operations as 'heap', 'stack' or 'Value' versions
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
        
        //======
        // HEAP
        //======
        
            //======
            // MATH
            //======
        
        // kLoadReal OP kLoadReal ==> Heap version
        if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadReal op kLoadReal ==> Heap version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
            
        // kLoadInt OP kLoadInt ==> Heap version
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadRInt op kLoadInt ==> Heap version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
            
            //===============
            // EXTENDED MATH
            //===============
            
        // kLoadReal EXTENDED-OP kLoadReal ==> Heap version
        } else  if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kLoadReal op kLoadReal ==> Heap version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRExtendedMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
            
        // kLoadInt EXTENDED-OP kLoadInt ==> Heap version
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kLoadRInt op kLoadInt ==> Heap version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRExtendedMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
        
        //=======
        // VALUE
        //=======
            
            //======
            // MATH
            //======
            
        // kLoadReal OP kRealValue ==> Value version
        } else if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kRealValue && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadReal op kRealValue ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRMath2Value[inst3->fOpcode], 0, inst2->fRealValue, inst1->fOffset1, 0);
          
        // kRealValue OP kLoadReal ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FIRInstruction::kRealValue && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kRealValue op kLoadReal ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRMath2ValueInvert[inst3->fOpcode], 0, inst1->fRealValue, inst2->fOffset1, 0);
           
        // kLoadInt OP kIntValue ==> Value version
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kIntValue && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadInt op kIntValue ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRMath2Value[inst3->fOpcode], inst2->fIntValue, 0, inst1->fOffset1, 0);
            
        // kIntValue OP kLoadInt ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kIntValue op kLoadInt ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRMath2ValueInvert[inst3->fOpcode], inst1->fIntValue, 0, inst2->fOffset1, 0);
            
            //===============
            // EXTENDED MATH
            //===============
            
        // kLoadReal EXTENDED-OP kRealValue ==> Value version
        } else if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kRealValue && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kLoadReal op kRealValue ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRExtendedMath2Value[inst3->fOpcode], 0, inst2->fRealValue, inst1->fOffset1, 0);
            
        // kRealValue EXTENDED-OP kLoadReal ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FIRInstruction::kRealValue && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kRealValue op kLoadReal ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRExtendedMath2ValueInvert[inst3->fOpcode], 0, inst1->fRealValue, inst2->fOffset1, 0);
            
        // kLoadInt EXTENDED-OP kIntValue ==> Value version
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kIntValue && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kLoadInt op kIntValue ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRExtendedMath2Value[inst3->fOpcode], inst2->fIntValue, 0, inst1->fOffset1, 0);
            
        // kIntValue EXTENDED-OP kLoadInt ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kIntValue op kLoadInt ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(gFIRExtendedMath2ValueInvert[inst3->fOpcode], inst1->fIntValue, 0, inst2->fOffset1, 0);
        
        //=======
        // STACK
        //=======
            
            //======
            // MATH
            //======
            
        // kLoadReal/kLoadInt binary OP ==> Stack version
        } else if (((inst1->fOpcode == FIRInstruction::kLoadReal) || (inst1->fOpcode == FIRInstruction::kLoadInt)) && FIRInstruction::isMath(inst2->fOpcode)) {
            //std::cout << "kLoadReal/kLoadInt binary op ==> Stack version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(gFIRMath2Stack[inst2->fOpcode], 0, 0, inst1->fOffset1, 0);
        
        // kRealValue binary OP ==> Stack/Value version
        } else if ((inst1->fOpcode == FIRInstruction::kRealValue) && FIRInstruction::isMath(inst2->fOpcode)) {
            //std::cout << "kRealValue binary op ==> Stack/Value version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(gFIRMath2StackValue[inst2->fOpcode], 0, inst1->fRealValue);
          
        // kIntValue binary OP ==> Stack/Value version
        } else if (((inst1->fOpcode == FIRInstruction::kRealValue) || (inst1->fOpcode == FIRInstruction::kIntValue)) && FIRInstruction::isMath(inst2->fOpcode)) {
            //std::cout << "kRealValue binary op ==> Stack/Value version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(gFIRMath2StackValue[inst2->fOpcode], inst1->fIntValue, 0);
        
            //===============
            // EXTENDED MATH
            //===============
      
        // kLoadReal/kLoadInt binary EXTENDED-OP ==> Stack version
        } else if (((inst1->fOpcode == FIRInstruction::kLoadReal) || (inst1->fOpcode == FIRInstruction::kLoadInt)) && FIRInstruction::isExtendedBinaryMath(inst2->fOpcode)) {
            //std::cout << "kLoadReal/kLoadInt binary op ==> Stack version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(gFIRExtendedMath2Stack[inst2->fOpcode], 0, 0, inst1->fOffset1, 0);
            
        // kRealValue EXTENDED-OP ==> Stack/Value version
        } else if ((inst1->fOpcode == FIRInstruction::kRealValue) && FIRInstruction::isExtendedBinaryMath(inst2->fOpcode)) {
            //std::cout << "kRealValue binary op ==> Stack/Value version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(gFIRExtendedMath2StackValue[inst2->fOpcode], 0, inst1->fRealValue);
     
        // kIntValue binary EXTENDED-OP ==> Stack/Value version
        } else if ((inst1->fOpcode == FIRInstruction::kIntValue) && FIRInstruction::isExtendedBinaryMath(inst2->fOpcode)) {
            //std::cout << "kRealValue binary op ==> Stack/Value version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(gFIRExtendedMath2StackValue[inst2->fOpcode], inst1->fIntValue, 0);
            
        //=====================
        // UNARY EXTENDED MATH
        //=====================
            
        // kLoadReal unary  ==> Heap version
        } else if (inst1->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isExtendedUnaryMath(inst2->fOpcode)) {
            //std::cout << "kLoadReal unary ==> Heap version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(gFIRExtendedMath2Heap[inst2->fOpcode], 0, 0, inst1->fOffset1, 0);
            
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
    
};

#endif
