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
#include <assert.h>
#include <iostream>
#include <map>

#include "interpreter_bytecode.hh"

// Block optimizer : compact list of instructions in a more efficient single one

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

template <class T> struct FIRInstructionOptimizer;

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


/*
 opcode 12 kMoveReal int 0 real 0 offset1 120322 offset2 120321
 opcode 12 kMoveReal int 0 real 0 offset1 120321 offset2 120320
 opcode 12 kMoveReal int 0 real 0 offset1 120325 offset2 120324
 opcode 12 kMoveReal int 0 real 0 offset1 120324 offset2 120323
 opcode 12 kMoveReal int 0 real 0 offset1 120328 offset2 120327
 opcode 12 kMoveReal int 0 real 0 offset1 120327 offset2 120326
 
 ==>  opcode 13 kBlockPairMoveReal int 0 real 0 offset1 120321 offset2 120327
*/

template <class T>
struct FIRInstructionBlockMoveOptimizer : public FIRInstructionOptimizer<T> {
    
    FIRInstructionBlockMoveOptimizer()
    {
        //std::cout << "FIRInstructionBlockMoveOptimizer" << std::endl;
    }
    
    FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FIRBasicInstruction<T>* inst = *cur;
        InstructionIT next = cur;
        
        int begin_move = -1;
        int end_move = -1;
        int last_offset = -1;
        
        while (inst->fOpcode != FIRInstruction::kReturn && inst->fOpcode == FIRInstruction::kMoveReal) {
            if ((inst->fOffset1 == inst->fOffset2 + 1) && ((last_offset == -1) || (inst->fOffset1 == last_offset + 2))) {
                if (begin_move == -1) { begin_move = inst->fOffset2; }
                last_offset = end_move = inst->fOffset1;
                inst = *(++next);
            } else {
                break;
            }
        }
        
        if (begin_move != -1 && end_move != -1 && ((end_move - begin_move) > 4)) {
            //std::cout << "FIRInstructionBlockMoveOptimizer " << begin_move  << " " << end_move << std::endl;
            end = next;
            return new FIRBasicInstruction<T>(FIRInstruction::kBlockPairMoveReal, 0, 0, begin_move, end_move);
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
    
};

/*
 opcode 12 kMoveReal int 0 real 0 offset1 120322 offset2 120321
 opcode 12 kMoveReal int 0 real 0 offset1 120321 offset2 120320
 opcode 12 kMoveReal int 0 real 0 offset1 120325 offset2 120324
 opcode 12 kMoveReal int 0 real 0 offset1 120324 offset2 120323
 
 ==>
 
 opcode 14 kPairMoveReal int 0 real 0 offset1 120322 offset2 120321
 opcode 14 kPairMoveReal int 0 real 0 offset1 120325 offset2 120324
*/

template <class T>
struct FIRInstructionPairMoveOptimizer : public FIRInstructionOptimizer<T> {
    
    FIRInstructionPairMoveOptimizer()
    {
        //std::cout << "FIRInstructionPairMoveOptimizer" << std::endl;
    }
    
    FIRBasicInstruction<T>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FIRBasicInstruction<T>* inst1 = *cur;
        FIRBasicInstruction<T>* inst2 = *(cur + 1);
        
        if (inst1->fOpcode == FIRInstruction::kMoveReal
            && inst2->fOpcode == FIRInstruction::kMoveReal
            && (inst1->fOffset1 == (inst1->fOffset2 + 1))
            && (inst2->fOffset1 == (inst2->fOffset2 + 1))
            && (inst2->fOffset1 == inst1->fOffset2)) {
            end = cur + 2;
            //std::cout << "FIRInstructionPairMoveOptimizer" << inst1->fOffset1 << " " << inst2->fOffset1 << std::endl;
            return new FIRBasicInstruction<T>(FIRInstruction::kPairMoveReal, 0, 0, inst1->fOffset1, inst2->fOffset1);
        } else if (inst1->fOpcode == FIRInstruction::kMoveInt
                && inst2->fOpcode == FIRInstruction::kMoveInt
                && (inst1->fOffset1 == (inst1->fOffset2 + 1))
                && (inst2->fOffset1 == (inst2->fOffset2 + 1))
                && (inst2->fOffset1 == inst1->fOffset2)) {
                end = cur + 2;
                //std::cout << "FIRInstructionPairMoveOptimizer" << inst1->fOffset1 << " " << inst2->fOffset1 << std::endl;
                return new FIRBasicInstruction<T>(FIRInstruction::kPairMoveInt, 0, 0, inst1->fOffset1, inst2->fOffset1);
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
        
        // Block should have at least 2 instructions...
        if (cur_block->size() < 2) {
            return cur_block->copy();
        }
        
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
            } else if (inst->fOpcode == FIRInstruction::kIf
                       || inst->fOpcode == FIRInstruction::kSelectReal
                       || inst->fOpcode == FIRInstruction::kSelectInt) {
                new_block->push(new FIRBasicInstruction<T>(inst->fOpcode,
                                                           inst->fIntValue, inst->fRealValue,
                                                           inst->fOffset1, inst->fOffset2,
                                                           optimize_aux(inst->fBranch1, optimizer),
                                                           optimize_aux(inst->fBranch2, optimizer)));
                cur++;
            } else if (inst->fOpcode == FIRInstruction::kCondBranch) {
                // Special case for loops : branch to new_block
                new_block->push(new FIRBasicInstruction<T>(FIRInstruction::kCondBranch, 0, 0, 0, 0, new_block, 0));
                cur++;
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
    
    static FIRBlockInstruction<T>* optimizeBlock(FIRBlockInstruction<T>* block)
    {
        // 1) optimize indexed 'heap' load/store in normal load/store
        FIRInstructionLoadStoreOptimizer<T> opt1;
        block = FIRInstructionOptimizer<T>::optimize(block, opt1);
        
        // 2) then pptimize simple 'heap' load/store in move
        FIRInstructionMoveOptimizer<T> opt2;
        block = FIRInstructionOptimizer<T>::optimize(block, opt2);
        
        // 3) optimize 'cast' in heap cast
        FIRInstructionCastOptimizer<T> opt3;
        block = FIRInstructionOptimizer<T>::optimize(block, opt3);
        
        // 4) them optimize 'heap' and 'Value' math operations
        FIRInstructionMathOptimizer<T> opt4;
        block = FIRInstructionOptimizer<T>::optimize(block, opt4);
        
        return block;
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

/*

template <class T>
struct FIRInstructionSpecialier {
    
    typedef std::map<int, T>    RealMap;
    typedef std::map<int, int>  IntMap;
    
    static FIRBlockInstruction<T>* specializeBlock(FIRBlockInstruction<T>* cur_block, IntMap& int_map, RealMap& real_map)
    {
        FIRBlockInstruction<T>* new_block = new FIRBlockInstruction<T>();
        
        InstructionIT cur = cur_block->fInstructions.begin();
        
        FIRBasicInstruction<T>* res = 0;
        
        FIRBasicInstruction<T>* inst1 = *cur;
        FIRBasicInstruction<T>* inst2 = *(cur + 1);
        FIRBasicInstruction<T>* inst3 = *(cur + 2);
        
        int consumed;
        
        while ((res = specializeInstruction(inst1, inst2, inst3, int_map, real_map, consumed)) {
            inst1 = res;
            if (
        }
        
        
        if (res) {
            
        }
       
        
        
    }
    
    static FIRBasicInstruction<T>* specializeInstruction(FIRBasicInstruction<T>* inst1
                                                         FIRBasicInstruction<T>* inst2
                                                         FIRBasicInstruction<T>* inst3,
                                                         IntMap& int_map,
                                                         RealMap& real_map
                                                         int& consumed)
    {
        
        FIRBasicInstruction<T>* res = 0;
        
        if (inst1->fOpcode == FIRInstruction::kLoadReal) {
            
            if (real_map.find(inst1->fOffset1) != real_map.end()) {
                res = FIRBasicInstruction<T>(FIRInstruction::kRealValue, 0, real_map[inst1->fOffset1]);
                consumed = 1;
            }
            
        } else if (inst1->fOpcode == FIRInstruction::kLoadInt) {
            
            if (int_map.find(inst1->fOffset1) != int_map.end()) {
                res = FIRBasicInstruction<T>(FIRInstruction::kIntValue, int_map[inst1->fOffset1], 0);
                consumed = 1;
            }
            
        } else if (inst1->fOpcode == FIRInstruction::kRealValue
                   inst2->fOpcode == FIRInstruction::kStoreReal) {
            
            // Add a new entry in real_map
            real_map[inst2->fOffset1] = inst1->fRealValue;
            consumed = 2;
            
        } else if (inst1->fOpcode == FIRInstruction::kIntValue
                   inst2->fOpcode == FIRInstruction::kStoreInt) {
            
            // Add a new entry in int_map
            int_map[inst2->fOffset1] = inst1->fIntValue;
            consumed = 2;
            
        // kLoadIndexed
        } else if (inst1->fOpcode == FIRInstruction::kIntValue
                   inst2->fOpcode == FIRInstruction::kLoadIndexedReal) {
            
            if (int_map.find(inst2->fOffset1) != int_map.end()) {
                res = FIRBasicInstruction<T>(FIRInstruction::kLoadReal, 0, 0, int_map[inst2->fOffset1] + inst1->fIntValue);
                consumed = 2;
            }
            
        } else if (inst1->fOpcode == FIRInstruction::kIntValue
                   inst2->fOpcode == FIRInstruction::kLoadIndexedInt) {
            
            if (int_map.find(inst2->fOffset1) != int_map.end()) {
                res = FIRBasicInstruction<T>(FIRInstruction::kLoadInt, 0, 0, int_map[inst2->fOffset1] + inst1->fIntValue);
                consumed = 2;
            }
            
        // kStoreIndexed
        } else if (inst1->fOpcode == FIRInstruction::kIntValue
                   inst2->fOpcode == FIRInstruction::kStoreIndexedReal) {
            
            if (int_map.find(inst2->fOffset1) != int_map.end()) {
                res = FIRBasicInstruction<T>(FIRInstruction::kStoreReal, 0, 0, int_map[inst2->fOffset1] + inst1->fIntValue);
                consumed = 2;
            }
            
        } else if (inst1->fOpcode == FIRInstruction::kIntValue
                   inst2->fOpcode == FIRInstruction::kStoreIndexedInt) {
            
            if (int_map.find(inst2->fOffset1) != int_map.end()) {
                res = FIRBasicInstruction<T>(FIRInstruction::kStoreInt, 0, 0, int_map[inst2->fOffset1] + inst1->fIntValue);
                consumed = 2;
            }
           
        // TODO : Input/output
            
        } else if (inst1->fOpcode == FIRInstruction::kRealValue
                   && inst2->fOpcode == FIRInstruction::kRealValue
                   && (isMath(inst3->fOpcode) || isExtendedBinaryMath(inst3->fOpcode))) {
            
            res = specializeBinaryMath(inst1, inst2, inst3, int_map, real_map);
            consumed = 3;
            
        } else if (inst1->fOpcode == FIRInstruction::kIntValue
                   && inst2->fOpcode == FIRInstruction::kIntValue
                   && (isMath(inst3->fOpcode) || isExtendedBinaryMath(inst3->fOpcode))) {
            
            res = specializeBinaryMath(inst1, inst2, inst3, int_map, real_map);
            consumed = 3;
            
        } else if (inst1->fOpcode == FIRInstruction::kRealValue
                   && isExtendedUnaryMath(inst2->fOpcode)) {
            
            res = specializeUnaryMath(inst1, inst2, int_map, real_map);
            consumed = 2;
            
        } else if (inst1->fOpcode == FIRInstruction::kIntValue
                   && isExtendedUnaryMath(inst2->fOpcode)) {
            
            res = specializeUnaryMath(inst1, inst2, int_map, real_map);
            consumed = 2;
            
        } else if (inst1->fOpcode == FIRInstruction::kIntValue && inst2->fOpcode == FIRInstruction::kCastReal) {
            
            res = FIRBasicInstruction<T>(FIRInstruction::kRealValue, 0, T(inst1->fIntValue));
            consumed = 1;
            
        } else if (inst1->fOpcode == FIRInstruction::kRealValue && inst2->fOpcode == FIRInstruction::kCastInt) {
            
            res = FIRBasicInstruction<T>(FIRInstruction::kIntValue, int(inst1->fIntValue), 0);
            consumed = 1;
         
        // SelectReal/SelectInt
        } else if (inst1->fOpcode == FIRInstruction::kIntValue
                   && ((inst2->fOpcode == FIRInstruction::kSelectReal)
                       ||(inst2->fOpcode == FIRInstruction::kSelectInt))) {
            
            if (inst1->fIntValue) {
                specializeBlock((*it)->fBranch1, int_map, real_map);
                consumed = 1;
            } else {
                specializeBlock((*it)->fBranch2, int_map, real_map);
                consumed = 1;
            }
         
        }
        
        
        return res;
    }

};
*/

#endif
