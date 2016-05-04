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


/*
// Select optimizer : when branchees are simple (Values or Load)
template <class T>
struct FIRInstructionSelectOptimizer : public FIRInstructionOptimizer<T>  {
    
    
    FIRInstructionSelectOptimizer()
    {
        //std::cout << "FIRInstructionSelectOptimizer" << std::endl;
    }
    
    FIRBasicInstruction<T>* rewriteSimpleSelect(FIRBasicInstruction<T>* inst1, FIRBasicInstruction<T>* inst2)
    {
        FIRBasicInstruction<T>* res;
        
        if (inst1->fOpcode == FIRInstruction::kIntValue) {
            if (inst2->fOpcode == FIRInstruction::kIntValue) {
                res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectTwoInt, inst1->fIntValue, T(inst2->fIntValue)); // Cast int ==> T here
            } else if (inst2->fOpcode == FIRInstruction::kLoadInt) {
                res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectTwoInt, inst1->fIntValue, 0, inst2->fOffset1, 0);
            } else {
                assert(false); // Should never happen
            }
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt) {
            if (inst2->fOpcode == FIRInstruction::kIntValue) {
                res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectTwoInt, inst2->fIntValue, 0, inst1->fOffset1, 0);
            } else if (inst2->fOpcode == FIRInstruction::kLoadInt) {
                res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectTwoInt, 0, 0, inst1->fOffset1, inst2->fOffset1);
            } else {
                assert(false); // Should never happen
            }
        } else if (inst1->fOpcode == FIRInstruction::kRealValue) {
            if (inst2->fOpcode == FIRInstruction::kRealValue) {
                res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectTwoInt, int(inst1->fRealValue), inst2->fRealValue); // Cast T ==> int here
            } else if (inst2->fOpcode == FIRInstruction::kLoadReal) {
                res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectTwoInt, 0, inst1->fRealValue, inst2->fOffset1, 0);
            } else {
                assert(false); // Should never happen
            }
        } else if (inst1->fOpcode == FIRInstruction::kLoadReal) {
            if (inst2->fOpcode == FIRInstruction::kRealValue) {
                res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectTwoInt, 0, inst2->fRealValue, inst1->fOffset1, 0); // Cast T ==> int here
            } else if (inst2->fOpcode == FIRInstruction::kLoadReal) {
                res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectTwoInt, 0, 0, inst1->fOffset1, inst2->fOffset1);
            } else {
                assert(false); // Should never happen
            }
        } else {
            assert(false); // Should never happen
        }
        
        return res;
    }
    
    FIRBasicInstruction<T>* rewriteSimpleBranchSelect(FIRBasicInstruction<T>* inst, FIRBlockInstruction<T>* branch)
    {
        if (inst->fOpcode == FIRInstruction::kIntValue) {
            res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectIntValue, inst->fIntValue, 0, 0, 0, branch, 0); // Cast int ==> T here
        } else if (inst->fOpcode == FIRInstruction::kLoadInt) {
             res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectLoadInt, 0, 0, inst->fOffset1, 0, branch, 0);
        } else if (inst->fOpcode == FIRInstruction::kRealInt) {
             res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectRealValue, 0, inst->fRealValue, 0, 0, branch, 0);
        } else if (inst->fOpcode == FIRInstruction::kLoadReal) {
            res = new FIRBasicInstruction<T>(FIRInstruction::kSimpleSelectLoadReal, 0, 0, inst->fOffset1, 0, branch, 0);
        } else {
            assert(false); // Should never happen
        }
        
        return res;
    }
    
    virtual FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FIRBasicInstruction<T>* inst1 = *cur;
        
        if (inst1->fOpcode == FIRInstruction::kIf) {
            FIRBlockInstruction<T>* branch1 = (*cur)->fBranch1;
            FIRBlockInstruction<T>* branch2 = (*cur)->fBranch2;
            if (branch1->size() == 1) {
                if (branch2->size() == 1)) {
                    return new rewriteSimpleSelect(*branch1->begin(), *branch2->begin());
                } else {
                    return new rewriteSimpleBranch1Select(*branch1->begin(), branch2);
                }
            } else if ((branch2->size() == 1) {
                return new rewriteSimpleBranch2Select(branch1, *branch2->begin());
            }
        }
                       
        // Default
        end = cur + 1;
        return (*cur)->copy();
    }
};
 */

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
        
        //===========
        // HEAP
        //===========
        
            //===========
            // MATH
            //===========
        
        // kLoadReal OP kLoadReal ==> Heap version
        if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadReal op kLoadReal ==> Heap version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
            
        // kLoadInt OP kLoadInt ==> Heap version
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadRInt op kLoadInt ==> Heap version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
            
            //==============
            // EXTENDED MATH
            //==============
            
        // kLoadReal EXTENDED-OP kLoadReal ==> Heap version
        } else  if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kLoadReal op kLoadReal ==> Heap version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRExtendedMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
            
        // kLoadInt EXTENDED-OP kLoadInt ==> Heap version
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kLoadRInt op kLoadInt ==> Heap version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRExtendedMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
        
        //===========
        // VALUE
        //===========
            
            //===========
            // MATH
            //===========
            
        // kLoadReal OP kRealValue ==> Value version
        } else if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kRealValue && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadReal op kRealValue ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Value[inst3->fOpcode], 0, inst2->fRealValue, inst1->fOffset1, 0);
          
        // kRealValue OP kLoadReal ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FIRInstruction::kRealValue && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kRealValue op kLoadReal ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2ValueInvert[inst3->fOpcode], 0, inst1->fRealValue, inst2->fOffset1, 0);
           
        // kLoadInt OP kIntValue ==> Value version
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kIntValue && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kLoadInt op kIntValue ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Value[inst3->fOpcode], inst2->fIntValue, 0, inst1->fOffset1, 0);
            
        // kIntValue OP kLoadInt ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isMath(inst3->fOpcode)) {
            //std::cout << "kIntValue op kLoadInt ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2ValueInvert[inst3->fOpcode], inst1->fIntValue, 0, inst2->fOffset1, 0);
            
            //==============
            // EXTENDED MATH
            //==============
      
            
        // kLoadReal EXTENDED-OP kRealValue ==> Value version
        } else if (inst1->fOpcode == FIRInstruction::kLoadReal && inst2->fOpcode == FIRInstruction::kRealValue && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kLoadReal op kRealValue ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRExtendedMath2Value[inst3->fOpcode], 0, inst2->fRealValue, inst1->fOffset1, 0);
            
        // kRealValue EXTENDED-OP kLoadReal ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FIRInstruction::kRealValue && inst2->fOpcode == FIRInstruction::kLoadReal && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kRealValue op kLoadReal ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRExtendedMath2ValueInvert[inst3->fOpcode], 0, inst1->fRealValue, inst2->fOffset1, 0);
            
        // kLoadInt EXTENDED-OP kIntValue ==> Value version
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt && inst2->fOpcode == FIRInstruction::kIntValue && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kLoadInt op kIntValue ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRExtendedMath2Value[inst3->fOpcode], inst2->fIntValue, 0, inst1->fOffset1, 0);
            
        // kIntValue EXTENDED-OP kLoadInt ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kLoadInt && FIRInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            //std::cout << "kIntValue op kLoadInt ==> Value version" << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 3;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRExtendedMath2ValueInvert[inst3->fOpcode], inst1->fIntValue, 0, inst2->fOffset1, 0);
        
        //===========
        // STACK
        //===========
            
            //===========
            // MATH
            //===========
            
        // kLoadReal/kLoadInt binary OP ==> Stack version
        } else if (((inst1->fOpcode == FIRInstruction::kLoadReal) || (inst1->fOpcode == FIRInstruction::kLoadInt)) && FIRInstruction::isMath(inst2->fOpcode)) {
            //std::cout << "kLoadReal/kLoadInt binary op ==> Stack version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2Stack[inst2->fOpcode], 0, 0, inst1->fOffset1, 0);
        
        // kRealValue binary OP ==> Stack/Value version
        } else if ((inst1->fOpcode == FIRInstruction::kRealValue) && FIRInstruction::isMath(inst2->fOpcode)) {
            //std::cout << "kRealValue binary op ==> Stack/Value version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2StackValue[inst2->fOpcode], 0, inst1->fRealValue);
          
        // kIntValue binary OP ==> Stack/Value version
        } else if (((inst1->fOpcode == FIRInstruction::kRealValue) || (inst1->fOpcode == FIRInstruction::kIntValue)) && FIRInstruction::isMath(inst2->fOpcode)) {
            //std::cout << "kRealValue binary op ==> Stack/Value version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRMath2StackValue[inst2->fOpcode], inst1->fIntValue, 0);
        
            //==============
            // EXTENDED MATH
            //==============
      
        // kLoadReal/kLoadInt binary EXTENDED-OP ==> Stack version
        } else if (((inst1->fOpcode == FIRInstruction::kLoadReal) || (inst1->fOpcode == FIRInstruction::kLoadInt)) && FIRInstruction::isExtendedBinaryMath(inst2->fOpcode)) {
            //std::cout << "kLoadReal/kLoadInt binary op ==> Stack version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRExtendedMath2Stack[inst2->fOpcode], 0, 0, inst1->fOffset1, 0);
            
        // kRealValue EXTENDED-OP ==> Stack/Value version
        } else if ((inst1->fOpcode == FIRInstruction::kRealValue) && FIRInstruction::isExtendedBinaryMath(inst2->fOpcode)) {
            //std::cout << "kRealValue binary op ==> Stack/Value version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRExtendedMath2StackValue[inst2->fOpcode], 0, inst1->fRealValue);
     
        // kIntValue binary EXTENDED-OP ==> Stack/Value version
        } else if ((inst1->fOpcode == FIRInstruction::kIntValue) && FIRInstruction::isExtendedBinaryMath(inst2->fOpcode)) {
            //std::cout << "kRealValue binary op ==> Stack/Value version " << gFIRInstructionTable[inst2->fOpcode] << endl;
            end = cur + 2;
            return new FIRBasicInstruction<T>(FIRInstruction::gFIRExtendedMath2StackValue[inst2->fOpcode], inst1->fIntValue, 0);
            
        //====================
        // UNARY EXTENDED MATH
        //=====================
            
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
