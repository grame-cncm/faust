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

#ifndef _FIR_INTERPRETER_OPTIMIZER_H
#define _FIR_INTERPRETER_OPTIMIZER_H

#include <cmath>
#include <iostream>
#include <map>
#include <string>

#include "exception.hh"
#include "interpreter_bytecode.hh"

#define INTER_MAX_OPT_LEVEL 6

// Tables for math optimization

static std::map<FBCInstruction::Opcode, FBCInstruction::Opcode> gFIRMath2Heap;
static std::map<FBCInstruction::Opcode, FBCInstruction::Opcode> gFIRMath2Stack;
static std::map<FBCInstruction::Opcode, FBCInstruction::Opcode> gFIRMath2StackValue;
static std::map<FBCInstruction::Opcode, FBCInstruction::Opcode> gFIRMath2Value;
static std::map<FBCInstruction::Opcode, FBCInstruction::Opcode> gFIRMath2ValueInvert;

static std::map<FBCInstruction::Opcode, FBCInstruction::Opcode> gFIRExtendedMath2Heap;
static std::map<FBCInstruction::Opcode, FBCInstruction::Opcode> gFIRExtendedMath2Stack;
static std::map<FBCInstruction::Opcode, FBCInstruction::Opcode> gFIRExtendedMath2StackValue;
static std::map<FBCInstruction::Opcode, FBCInstruction::Opcode> gFIRExtendedMath2Value;
static std::map<FBCInstruction::Opcode, FBCInstruction::Opcode> gFIRExtendedMath2ValueInvert;

//=======================
// Optimization
//=======================

template <class REAL>
struct FBCInstructionOptimizer;

// Copy (= identity) optimizer (used to test...)
template <class REAL>
struct FBCInstructionCopyOptimizer : public FBCInstructionOptimizer<REAL> {
    FBCInstructionCopyOptimizer() {}
    
    virtual FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        end = cur + 1;
        return (*cur)->copy();
    }
};

// Cast optimizer
template <class REAL>
struct FBCInstructionCastOptimizer : public FBCInstructionOptimizer<REAL> {
    FBCInstructionCastOptimizer() {}
    
    virtual FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FBCBasicInstruction<REAL>* &inst1 = *cur;
        FBCBasicInstruction<REAL>* &inst2 = *(cur + 1);
        
        if (inst1->fOpcode == FBCInstruction::kLoadInt && inst2->fOpcode == FBCInstruction::kCastReal) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kCastRealHeap, 0, 0, inst1->fOffset1, 0);
        } else if (inst1->fOpcode == FBCInstruction::kLoadReal && inst2->fOpcode == FBCInstruction::kCastInt) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kCastIntHeap, 0, 0, inst1->fOffset1, 0);
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
};

// Rewrite indexed Load/Store as simple Load/Store
template <class REAL>
struct FBCInstructionLoadStoreOptimizer : public FBCInstructionOptimizer<REAL> {
    FBCInstructionLoadStoreOptimizer() {}
    
    virtual ~FBCInstructionLoadStoreOptimizer() {}
    
    FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FBCBasicInstruction<REAL>* &inst1 = *cur;
        FBCBasicInstruction<REAL>* &inst2 = *(cur + 1);
        
        if (inst1->fOpcode == FBCInstruction::kInt32Value && inst2->fOpcode == FBCInstruction::kLoadIndexedReal) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kLoadReal, 0, 0, inst1->fIntValue + inst2->fOffset1, 0);
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value && inst2->fOpcode == FBCInstruction::kLoadIndexedInt) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kLoadInt, 0, 0, inst1->fIntValue + inst2->fOffset1, 0);
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value &&
                   inst2->fOpcode == FBCInstruction::kStoreIndexedReal) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kStoreReal, 0, 0, inst1->fIntValue + inst2->fOffset1, 0);
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value &&
                   inst2->fOpcode == FBCInstruction::kStoreIndexedInt) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kStoreInt, 0, 0, inst1->fIntValue + inst2->fOffset1, 0);
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
};

// Rewrite heap Load/Store as Move or direct Value store
template <class REAL>
struct FBCInstructionMoveOptimizer : public FBCInstructionOptimizer<REAL> {
    FBCInstructionMoveOptimizer() {}
    
    virtual ~FBCInstructionMoveOptimizer() {}
    
    FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FBCBasicInstruction<REAL>* &inst1 = *cur;
        FBCBasicInstruction<REAL>* &inst2 = *(cur + 1);
        
        // Optimize Heap Load/Store as Move
        if (inst1->fOpcode == FBCInstruction::kLoadReal && inst2->fOpcode == FBCInstruction::kStoreReal) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kMoveReal, 0, 0, inst2->fOffset1,
                                                 inst1->fOffset1);  // reverse order
        } else if (inst1->fOpcode == FBCInstruction::kLoadInt && inst2->fOpcode == FBCInstruction::kStoreInt) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kMoveInt, 0, 0, inst2->fOffset1,
                                                 inst1->fOffset1);  // reverse order
            // Optimize Value Load/Store as direct value Store
        } else if (inst1->fOpcode == FBCInstruction::kRealValue && inst2->fOpcode == FBCInstruction::kStoreReal) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kStoreRealValue, 0, inst1->fRealValue, inst2->fOffset1,
                                                 0);
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value && inst2->fOpcode == FBCInstruction::kStoreInt) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kStoreIntValue, inst1->fIntValue, 0, inst2->fOffset1, 0);
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

template <class REAL>
struct FBCInstructionBlockMoveOptimizer : public FBCInstructionOptimizer<REAL> {
    FBCInstructionBlockMoveOptimizer() {}
    
    virtual ~FBCInstructionBlockMoveOptimizer() {}
    
    FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FBCBasicInstruction<REAL>* inst = *cur;
        InstructionIT              next = cur;
        
        int begin_move  = -1;
        int end_move    = -1;
        int last_offset = -1;
        
        while (inst->fOpcode != FBCInstruction::kReturn && inst->fOpcode == FBCInstruction::kMoveReal) {
            if ((inst->fOffset1 == inst->fOffset2 + 1) &&
                ((last_offset == -1) || (inst->fOffset1 == last_offset + 2))) {
                if (begin_move == -1) {
                    begin_move = inst->fOffset2;
                }
                last_offset = end_move = inst->fOffset1;
                inst                   = *(++next);
            } else {
                break;
            }
        }
        
        if (begin_move != -1 && end_move != -1 && ((end_move - begin_move) > 4)) {
            // std::cout << "FBCInstructionBlockMoveOptimizer " << begin_move  << " " << end_move << std::endl;
            end = next;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kBlockPairMoveReal, 0, 0, begin_move, end_move);
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

template <class REAL>
struct FBCInstructionPairMoveOptimizer : public FBCInstructionOptimizer<REAL> {
    FBCInstructionPairMoveOptimizer() {}
    
    virtual ~FBCInstructionPairMoveOptimizer() {}
    
    FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FBCBasicInstruction<REAL>* &inst1 = *cur;
        FBCBasicInstruction<REAL>* &inst2 = *(cur + 1);
        
        if (inst1->fOpcode == FBCInstruction::kMoveReal && inst2->fOpcode == FBCInstruction::kMoveReal &&
            (inst1->fOffset1 == (inst1->fOffset2 + 1)) && (inst2->fOffset1 == (inst2->fOffset2 + 1)) &&
            (inst2->fOffset1 == inst1->fOffset2)) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kPairMoveReal, 0, 0, inst1->fOffset1, inst2->fOffset1);
        } else if (inst1->fOpcode == FBCInstruction::kMoveInt && inst2->fOpcode == FBCInstruction::kMoveInt &&
                   (inst1->fOffset1 == (inst1->fOffset2 + 1)) && (inst2->fOffset1 == (inst2->fOffset2 + 1)) &&
                   (inst2->fOffset1 == inst1->fOffset2)) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kPairMoveInt, 0, 0, inst1->fOffset1, inst2->fOffset1);
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
};

// Rewrite math operations as 'heap', 'stack' or 'Value' versions
template <class REAL>
struct FBCInstructionMathOptimizer : public FBCInstructionOptimizer<REAL> {
    virtual ~FBCInstructionMathOptimizer() {}
    
    FBCInstructionMathOptimizer()
    {
        if (gFIRMath2Heap.size() > 0) {
            // Already initialized
            return;
        }
        
        //===============
        // Math
        //===============
        
        // Init heap opcode
        for (int i = FBCInstruction::kAddReal; i <= FBCInstruction::kXORInt; i++) {
            gFIRMath2Heap[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAddRealHeap - FBCInstruction::kAddReal));
        }
        
        // Init stack opcode
        for (int i = FBCInstruction::kAddReal; i <= FBCInstruction::kXORInt; i++) {
            gFIRMath2Stack[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAddRealStack - FBCInstruction::kAddReal));
        }
        
        // Init stack/value opcode
        for (int i = FBCInstruction::kAddReal; i <= FBCInstruction::kXORInt; i++) {
            gFIRMath2StackValue[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAddRealStackValue - FBCInstruction::kAddReal));
        }
        
        // Init Value opcode
        for (int i = FBCInstruction::kAddReal; i <= FBCInstruction::kXORInt; i++) {
            gFIRMath2Value[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAddRealValue - FBCInstruction::kAddReal));
        }
        
        // Init Value opcode (non commutative operation)
        for (int i = FBCInstruction::kAddReal; i <= FBCInstruction::kXORInt; i++) {
            gFIRMath2ValueInvert[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAddRealValue - FBCInstruction::kAddReal));
        }
        
        // Manually set inverted versions
        gFIRMath2ValueInvert[FBCInstruction::kSubReal] = FBCInstruction::kSubRealValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kSubInt]  = FBCInstruction::kSubIntValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kDivReal] = FBCInstruction::kDivRealValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kDivInt]  = FBCInstruction::kDivIntValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kRemReal] = FBCInstruction::kRemRealValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kRemInt]  = FBCInstruction::kRemIntValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kLshInt]  = FBCInstruction::kLshIntValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kARshInt]  = FBCInstruction::kARshIntValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kGTInt]   = FBCInstruction::kGTIntValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kLTInt]   = FBCInstruction::kLTIntValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kGEInt]   = FBCInstruction::kGEIntValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kLEInt]   = FBCInstruction::kLEIntValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kGTReal]  = FBCInstruction::kGTRealValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kLTReal]  = FBCInstruction::kLTRealValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kGEReal]  = FBCInstruction::kGERealValueInvert;
        gFIRMath2ValueInvert[FBCInstruction::kLEReal]  = FBCInstruction::kLERealValueInvert;
        
        //===============
        // EXTENDED math
        //===============
        
        // Init unary extended math heap opcode
        for (int i = FBCInstruction::kAbs; i <= FBCInstruction::kTanhf; i++) {
            gFIRExtendedMath2Heap[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAbsHeap - FBCInstruction::kAbs));
        }
        
        // Init binary extended math heap opcode
        for (int i = FBCInstruction::kAtan2f; i <= FBCInstruction::kMinf; i++) {
            gFIRExtendedMath2Heap[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAtan2fHeap - FBCInstruction::kAtan2f));
        }
        
        // Init binary extended math stack opcode
        for (int i = FBCInstruction::kAtan2f; i <= FBCInstruction::kMinf; i++) {
            gFIRExtendedMath2Stack[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAtan2fStack - FBCInstruction::kAtan2f));
        }
        
        // Init binary extended math stack/value opcode
        for (int i = FBCInstruction::kAtan2f; i <= FBCInstruction::kMinf; i++) {
            gFIRExtendedMath2StackValue[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAtan2fStackValue - FBCInstruction::kAtan2f));
        }
        
        // Init binary math Value opcode
        for (int i = FBCInstruction::kAtan2f; i <= FBCInstruction::kMinf; i++) {
            gFIRExtendedMath2Value[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAtan2fValue - FBCInstruction::kAtan2f));
        }
        
        // Init binary math Value opcode : non commutative operations
        for (int i = FBCInstruction::kAtan2f; i <= FBCInstruction::kPowf; i++) {
            gFIRExtendedMath2ValueInvert[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kAtan2fValueInvert - FBCInstruction::kAtan2f));
        }
        
        //  Init binary math Value opcode : complete with commutative operations
        for (int i = FBCInstruction::kMax; i <= FBCInstruction::kMinf; i++) {
            gFIRExtendedMath2ValueInvert[FBCInstruction::Opcode(i)] =
                FBCInstruction::Opcode(i + (FBCInstruction::kMaxValue - FBCInstruction::kMax));
        }
    }
    
    FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FBCBasicInstruction<REAL>* &inst1 = *cur;
        FBCBasicInstruction<REAL>* &inst2 = *(cur + 1);
        FBCBasicInstruction<REAL>* &inst3 = *(cur + 2);
        
        faustassert(gFIRMath2Heap.size() > 0);
        faustassert(gFIRMath2Stack.size() > 0);
        faustassert(gFIRMath2StackValue.size() > 0);
        faustassert(gFIRMath2Value.size() > 0);
        faustassert(gFIRMath2ValueInvert.size() > 0);
        
        faustassert(gFIRExtendedMath2Heap.size() > 0);
        faustassert(gFIRExtendedMath2Stack.size() > 0);
        faustassert(gFIRExtendedMath2StackValue.size() > 0);
        faustassert(gFIRExtendedMath2Value.size() > 0);
        faustassert(gFIRExtendedMath2ValueInvert.size() > 0);
        
        //======
        // HEAP
        //======
        
        //======
        // MATH
        //======
        
        // kLoadReal OP kLoadReal ==> Heap version
        if (inst1->fOpcode == FBCInstruction::kLoadReal && inst2->fOpcode == FBCInstruction::kLoadReal &&
            FBCInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRMath2Heap.find(inst3->fOpcode) != gFIRMath2Heap.end());
            return new FBCBasicInstruction<REAL>(gFIRMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
            
            // kLoadInt OP kLoadInt ==> Heap version
        } else if (inst1->fOpcode == FBCInstruction::kLoadInt && inst2->fOpcode == FBCInstruction::kLoadInt &&
                   FBCInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRMath2Heap.find(inst3->fOpcode) != gFIRMath2Heap.end());
            return new FBCBasicInstruction<REAL>(gFIRMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1, inst1->fOffset1);
            
            //===============
            // EXTENDED MATH
            //===============
            
            // kLoadReal EXTENDED-OP kLoadReal ==> Heap version
        } else if (inst1->fOpcode == FBCInstruction::kLoadReal && inst2->fOpcode == FBCInstruction::kLoadReal &&
                   FBCInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRExtendedMath2Heap.find(inst3->fOpcode) != gFIRExtendedMath2Heap.end());
            return new FBCBasicInstruction<REAL>(gFIRExtendedMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1,
                                                 inst1->fOffset1);
            
            // kLoadInt EXTENDED-OP kLoadInt ==> Heap version
        } else if (inst1->fOpcode == FBCInstruction::kLoadInt && inst2->fOpcode == FBCInstruction::kLoadInt &&
                   FBCInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRExtendedMath2Heap.find(inst3->fOpcode) != gFIRExtendedMath2Heap.end());
            return new FBCBasicInstruction<REAL>(gFIRExtendedMath2Heap[inst3->fOpcode], 0, 0, inst2->fOffset1,
                                                 inst1->fOffset1);
            
            //=======
            // VALUE
            //=======
            
            //======
            // MATH
            //======
            
            // kLoadReal OP kRealValue ==> Value version
        } else if (inst1->fOpcode == FBCInstruction::kLoadReal && inst2->fOpcode == FBCInstruction::kRealValue &&
                   FBCInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRMath2Value.find(inst3->fOpcode) != gFIRMath2Value.end());
            return new FBCBasicInstruction<REAL>(gFIRMath2Value[inst3->fOpcode], 0, inst2->fRealValue, inst1->fOffset1, 0);
            
            // kRealValue OP kLoadReal ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FBCInstruction::kRealValue && inst2->fOpcode == FBCInstruction::kLoadReal &&
                   FBCInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRMath2ValueInvert.find(inst3->fOpcode) != gFIRMath2ValueInvert.end());
            return new FBCBasicInstruction<REAL>(gFIRMath2ValueInvert[inst3->fOpcode], 0, inst1->fRealValue,
                                                 inst2->fOffset1, 0);
            
            // kLoadInt OP kInt32Value ==> Value version
        } else if (inst1->fOpcode == FBCInstruction::kLoadInt && inst2->fOpcode == FBCInstruction::kInt32Value &&
                   FBCInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRMath2Value.find(inst3->fOpcode) != gFIRMath2Value.end());
            return new FBCBasicInstruction<REAL>(gFIRMath2Value[inst3->fOpcode], inst2->fIntValue, 0, inst1->fOffset1, 0);
            
            // kInt32Value OP kLoadInt ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value && inst2->fOpcode == FBCInstruction::kLoadInt &&
                   FBCInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRMath2ValueInvert.find(inst3->fOpcode) != gFIRMath2ValueInvert.end());
            return new FBCBasicInstruction<REAL>(gFIRMath2ValueInvert[inst3->fOpcode], inst1->fIntValue, 0,
                                                 inst2->fOffset1, 0);
            
            //===============
            // EXTENDED MATH
            //===============
            
            // kLoadReal EXTENDED-OP kRealValue ==> Value version
        } else if (inst1->fOpcode == FBCInstruction::kLoadReal && inst2->fOpcode == FBCInstruction::kRealValue &&
                   FBCInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRExtendedMath2Value.find(inst3->fOpcode) != gFIRExtendedMath2Value.end());
            return new FBCBasicInstruction<REAL>(gFIRExtendedMath2Value[inst3->fOpcode], 0, inst2->fRealValue,
                                                 inst1->fOffset1, 0);
            
            // kRealValue EXTENDED-OP kLoadReal ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FBCInstruction::kRealValue && inst2->fOpcode == FBCInstruction::kLoadReal &&
                   FBCInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRExtendedMath2ValueInvert.find(inst3->fOpcode) != gFIRExtendedMath2ValueInvert.end());
            return new FBCBasicInstruction<REAL>(gFIRExtendedMath2ValueInvert[inst3->fOpcode], 0, inst1->fRealValue,
                                                 inst2->fOffset1, 0);
            
            // kLoadInt EXTENDED-OP kInt32Value ==> Value version
        } else if (inst1->fOpcode == FBCInstruction::kLoadInt && inst2->fOpcode == FBCInstruction::kInt32Value &&
                   FBCInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRExtendedMath2Value.find(inst3->fOpcode) != gFIRExtendedMath2Value.end());
            return new FBCBasicInstruction<REAL>(gFIRExtendedMath2Value[inst3->fOpcode], inst2->fIntValue, 0,
                                                 inst1->fOffset1, 0);
            
            // kInt32Value EXTENDED-OP kLoadInt ==> Value version (special case for non-commutative operation)
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value && inst2->fOpcode == FBCInstruction::kLoadInt &&
                   FBCInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            end = cur + 3;
            faustassert(gFIRExtendedMath2ValueInvert.find(inst3->fOpcode) != gFIRExtendedMath2ValueInvert.end());
            return new FBCBasicInstruction<REAL>(gFIRExtendedMath2ValueInvert[inst3->fOpcode], inst1->fIntValue, 0,
                                                 inst2->fOffset1, 0);
            
            //=======
            // STACK
            //=======
            
            //======
            // MATH
            //======
            
            // kLoadReal/kLoadInt binary OP ==> Stack version
        } else if (((inst1->fOpcode == FBCInstruction::kLoadReal) || (inst1->fOpcode == FBCInstruction::kLoadInt)) &&
                   FBCInstruction::isMath(inst2->fOpcode)) {
            end = cur + 2;
            faustassert(gFIRMath2Stack.find(inst2->fOpcode) != gFIRMath2Stack.end());
            return new FBCBasicInstruction<REAL>(gFIRMath2Stack[inst2->fOpcode], 0, 0, inst1->fOffset1, 0);
            
            // kRealValue binary OP ==> Stack/Value version
        } else if ((inst1->fOpcode == FBCInstruction::kRealValue) && FBCInstruction::isMath(inst2->fOpcode)) {
            end = cur + 2;
            faustassert(gFIRMath2StackValue.find(inst2->fOpcode) != gFIRMath2StackValue.end());
            return new FBCBasicInstruction<REAL>(gFIRMath2StackValue[inst2->fOpcode], 0, inst1->fRealValue);
            
            // kInt32Value binary OP ==> Stack/Value version
        } else if (((inst1->fOpcode == FBCInstruction::kRealValue) ||
                    (inst1->fOpcode == FBCInstruction::kInt32Value)) &&
                   FBCInstruction::isMath(inst2->fOpcode)) {
            end = cur + 2;
            faustassert(gFIRMath2StackValue.find(inst2->fOpcode) != gFIRMath2StackValue.end());
            return new FBCBasicInstruction<REAL>(gFIRMath2StackValue[inst2->fOpcode], inst1->fIntValue, 0);
            
            //===============
            // EXTENDED MATH
            //===============
            
            // kLoadReal/kLoadInt binary EXTENDED-OP ==> Stack version
        } else if (((inst1->fOpcode == FBCInstruction::kLoadReal) || (inst1->fOpcode == FBCInstruction::kLoadInt)) &&
                   FBCInstruction::isExtendedBinaryMath(inst2->fOpcode)) {
            end = cur + 2;
            faustassert(gFIRExtendedMath2Stack.find(inst2->fOpcode) != gFIRExtendedMath2Stack.end());
            return new FBCBasicInstruction<REAL>(gFIRExtendedMath2Stack[inst2->fOpcode], 0, 0, inst1->fOffset1, 0);
            
            // kRealValue EXTENDED-OP ==> Stack/Value version
        } else if ((inst1->fOpcode == FBCInstruction::kRealValue) &&
                   FBCInstruction::isExtendedBinaryMath(inst2->fOpcode)) {
            end = cur + 2;
            faustassert(gFIRExtendedMath2StackValue.find(inst2->fOpcode) != gFIRExtendedMath2StackValue.end());
            return new FBCBasicInstruction<REAL>(gFIRExtendedMath2StackValue[inst2->fOpcode], 0, inst1->fRealValue);
            
            // kInt32Value binary EXTENDED-OP ==> Stack/Value version
        } else if ((inst1->fOpcode == FBCInstruction::kInt32Value) &&
                   FBCInstruction::isExtendedBinaryMath(inst2->fOpcode)) {
            end = cur + 2;
            faustassert(gFIRExtendedMath2StackValue.find(inst2->fOpcode) != gFIRExtendedMath2StackValue.end());
            return new FBCBasicInstruction<REAL>(gFIRExtendedMath2StackValue[inst2->fOpcode], inst1->fIntValue, 0);
            
            //=====================
            // UNARY EXTENDED MATH
            //=====================
            
            // kLoadReal unary  ==> Heap version
        } else if (inst1->fOpcode == FBCInstruction::kLoadReal && FBCInstruction::isExtendedUnaryMath(inst2->fOpcode)) {
            end = cur + 2;
            faustassert(gFIRExtendedMath2Heap.find(inst2->fOpcode) != gFIRExtendedMath2Heap.end());
            return new FBCBasicInstruction<REAL>(gFIRExtendedMath2Heap[inst2->fOpcode], 0, 0, inst1->fOffset1, 0);
            
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
};

//============================================
// Partial evaluation by constant propagation
//============================================

// Constant Values Optimizer : propagate Int and Real constant values
template <class REAL>
struct FBCInstructionConstantValueMap2Heap : public FBCInstructionOptimizer<REAL> {
    std::map<int, int>&  fIntMap;
    std::map<int, REAL>& fRealMap;
    
    FBCInstructionConstantValueMap2Heap(std::map<int, int>& int_map, std::map<int, REAL>& real_map)
    : fIntMap(int_map), fRealMap(real_map)
    {
    }
    
    virtual ~FBCInstructionConstantValueMap2Heap() {}
    
    virtual FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FBCBasicInstruction<REAL>* inst = *cur;
        
        if (inst->fOpcode == FBCInstruction::kLoadInt && fIntMap.find(inst->fOffset1) != fIntMap.end()) {
            end = cur + 1;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, fIntMap[inst->fOffset1], 0);
        } else if (inst->fOpcode == FBCInstruction::kLoadReal && fRealMap.find(inst->fOffset1) != fRealMap.end()) {
            end = cur + 1;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, fRealMap[inst->fOffset1]);
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
};

// Constant Values Optimizer : propagate Int and Real constant values
template <class REAL>
struct FBCInstructionConstantValueHeap2Map : public FBCInstructionOptimizer<REAL> {
    std::map<int, int>&  fIntMap;
    std::map<int, REAL>& fRealMap;
    
    FBCInstructionConstantValueHeap2Map(std::map<int, int>& int_map, std::map<int, REAL>& real_map)
    : fIntMap(int_map), fRealMap(real_map)
    {
    }
    
    virtual ~FBCInstructionConstantValueHeap2Map() {}
    
    virtual FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FBCBasicInstruction<REAL>* &inst1 = *cur;
        FBCBasicInstruction<REAL>* &inst2 = *(cur + 1);
        
        if (inst1->fOpcode == FBCInstruction::kRealValue && inst2->fOpcode == FBCInstruction::kStoreReal) {
            end = cur + 2;
            // Add a new entry in real_map
            fRealMap[inst2->fOffset1] = inst1->fRealValue;
            return nullptr;  // Will not be added in the block...
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value && inst2->fOpcode == FBCInstruction::kStoreInt) {
            end = cur + 2;
            // Add a new entry in int_map
            fIntMap[inst2->fOffset1] = inst1->fIntValue;
            return nullptr;  // Will not be added in the block...
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
};

// Cast specializer
template <class REAL>
struct FBCInstructionCastSpecializer : public FBCInstructionOptimizer<REAL> {
    FBCInstructionCastSpecializer() {}
    
    virtual ~FBCInstructionCastSpecializer() {}
    
    virtual FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FBCBasicInstruction<REAL>* &inst1 = *cur;
        FBCBasicInstruction<REAL>* &inst2 = *(cur + 1);
        
        if (inst1->fOpcode == FBCInstruction::kInt32Value && inst2->fOpcode == FBCInstruction::kCastReal) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, T(inst1->fIntValue));
        } else if (inst1->fOpcode == FBCInstruction::kRealValue && inst2->fOpcode == FBCInstruction::kCastInt) {
            end = cur + 2;
            return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, int(inst1->fRealValue), 0);
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
};

// Math specializer
template <class REAL>
struct FBCInstructionMathSpecializer : public FBCInstructionOptimizer<REAL> {
    FBCInstructionMathSpecializer() {}
    
    virtual ~FBCInstructionMathSpecializer() {}
    
    // Beware : inverted args...
    FBCBasicInstruction<REAL>* rewriteBinaryRealMath(FBCBasicInstruction<REAL>* inst1, FBCBasicInstruction<REAL>* inst2,
                                                     FBCBasicInstruction<REAL>* inst3)
    {
        switch (inst3->fOpcode) {
            case FBCInstruction::kAddReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, inst2->fRealValue + inst1->fRealValue);
                
            case FBCInstruction::kSubReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, inst2->fRealValue - inst1->fRealValue);
                
            case FBCInstruction::kMultReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, inst2->fRealValue * inst1->fRealValue);
                
            case FBCInstruction::kDivReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, inst2->fRealValue / inst1->fRealValue);
                
            case FBCInstruction::kRemReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0,
                                                  std::remainder(inst2->fRealValue, inst1->fRealValue));
                
            case FBCInstruction::kGTReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fRealValue > inst1->fRealValue,
                                                  0);
                
            case FBCInstruction::kLTReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fRealValue < inst1->fRealValue,
                                                  0);
                
            case FBCInstruction::kGEReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fRealValue >= inst1->fRealValue,
                                                  0);
                
            case FBCInstruction::kLEReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fRealValue <= inst1->fRealValue,
                                                  0);
                
            case FBCInstruction::kEQReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fRealValue == inst1->fRealValue,
                                                  0);
                
            case FBCInstruction::kNEReal:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fRealValue != inst1->fRealValue,
                                                  0);
                
            default:
                faustassert(false);
                return nullptr;
        }
    }
    
    // FBCInstruction::kRealValue
    // FBCInstruction::kLoadReal
    FBCBasicInstruction<REAL>* rewriteBinaryRealMath2(FBCBasicInstruction<REAL>* inst1, FBCBasicInstruction<REAL>* inst2,
                                                      FBCBasicInstruction<REAL>* inst3)
    {
        switch (inst3->fOpcode) {
            case FBCInstruction::kAddReal:
                return (inst1->fRealValue == REAL(0))
                    ? new FBCBasicInstruction<REAL>(FBCInstruction::kLoadReal, 0, 0, inst2->fOffset1, 0)
                    : nullptr;
                
            case FBCInstruction::kSubReal:
                return (inst1->fRealValue == REAL(0))
                    ? new FBCBasicInstruction<REAL>(FBCInstruction::kLoadReal, 0, 0, inst2->fOffset1, 0)
                    : nullptr;
                
            case FBCInstruction::kMultReal: {
                if (inst1->fRealValue == REAL(1)) {  // neutral
                    return new FBCBasicInstruction<REAL>(FBCInstruction::kLoadReal, 0, 0, inst2->fOffset1, 0);
                } else if (inst1->fRealValue == REAL(0)) {  // absorbant
                    return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, REAL(0));
                } else {
                    return nullptr;
                }
            }
                
            case FBCInstruction::kDivReal:
                return (inst1->fRealValue == REAL(1))
                ? new FBCBasicInstruction<REAL>(FBCInstruction::kLoadReal, 0, 0, inst2->fOffset1, 0)
                : nullptr;
                
            default:
                return nullptr;
        }
    }
    
    // FBCInstruction::kLoadReal
    // FBCInstruction::kRealValue : sub and div not rewritten
    FBCBasicInstruction<REAL>* rewriteBinaryRealMath3(FBCBasicInstruction<REAL>* inst1, FBCBasicInstruction<REAL>* inst2,
                                                      FBCBasicInstruction<REAL>* inst3)
    {
        switch (inst3->fOpcode) {
            case FBCInstruction::kAddReal:
                return (inst2->fRealValue == REAL(0))
                    ? new FBCBasicInstruction<REAL>(FBCInstruction::kLoadReal, 0, 0, inst1->fOffset1, 0)
                    : nullptr;
                
            case FBCInstruction::kMultReal:
                if (inst2->fRealValue == REAL(1)) {  // neutral
                    return new FBCBasicInstruction<REAL>(FBCInstruction::kLoadReal, 0, 0, inst1->fOffset1, 0);
                } else if (inst2->fRealValue == REAL(0)) {  // absorbant
                    return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, REAL(0));
                } else {
                    return nullptr;
                }
                
            default:
                return nullptr;
        }
    }
    
    FBCBasicInstruction<REAL>* rewriteBinaryIntMath(FBCBasicInstruction<REAL>* inst1, FBCBasicInstruction<REAL>* inst2,
                                                    FBCBasicInstruction<REAL>* inst3)
    {
        switch (inst3->fOpcode) {
            case FBCInstruction::kAddInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue + inst1->fIntValue, 0);
                
            case FBCInstruction::kSubInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue - inst1->fIntValue, 0);
                
            case FBCInstruction::kMultInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue * inst1->fIntValue, 0);
                
            case FBCInstruction::kDivInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue / inst1->fIntValue, 0);
                
            case FBCInstruction::kRemInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue % inst1->fIntValue, 0);
                
            case FBCInstruction::kLshInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue << inst1->fIntValue, 0);
                
            case FBCInstruction::kARshInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue >> inst1->fIntValue, 0);
                
            case FBCInstruction::kGTInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue > inst1->fIntValue, 0);
                
            case FBCInstruction::kLTInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue < inst1->fIntValue, 0);
                
            case FBCInstruction::kGEInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue >= inst1->fIntValue, 0);
                
            case FBCInstruction::kLEInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue <= inst1->fIntValue, 0);
                
            case FBCInstruction::kEQInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue == inst1->fIntValue, 0);
                
            case FBCInstruction::kNEInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue != inst1->fIntValue, 0);
                
            case FBCInstruction::kANDInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue & inst1->fIntValue, 0);
                
            case FBCInstruction::kORInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue | inst1->fIntValue, 0);
                
            case FBCInstruction::kXORInt:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, inst2->fIntValue ^ inst1->fIntValue, 0);
                
            default:
                faustassert(false);
                return nullptr;
        }
    }
    
    // FBCInstruction::kInt32Value
    // FBCInstruction::kLoadInt
    
    FBCBasicInstruction<REAL>* rewriteBinaryIntMath2(FBCBasicInstruction<REAL>* inst1, FBCBasicInstruction<REAL>* inst2,
                                                     FBCBasicInstruction<REAL>* inst3)
    {
        switch (inst3->fOpcode) {
            case FBCInstruction::kAddInt:
                return (inst1->fIntValue == 0)
                    ? new FBCBasicInstruction<REAL>(FBCInstruction::kLoadInt, 0, 0, inst2->fOffset1, 0)
                    : nullptr;
                
            case FBCInstruction::kSubInt:
                return (inst1->fIntValue == 0)
                    ? new FBCBasicInstruction<REAL>(FBCInstruction::kLoadInt, 0, 0, inst2->fOffset1, 0)
                    : nullptr;
                
            case FBCInstruction::kMultInt:
                if (inst1->fIntValue == 1) {  // neutral
                    new FBCBasicInstruction<REAL>(FBCInstruction::kLoadInt, 0, 0, inst2->fOffset1, 0);
                } else if (inst1->fIntValue == 0) {  // absorbant
                    new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, 0, 0);
                } else {
                    return nullptr;
                }
                
            case FBCInstruction::kDivInt:
                return (inst1->fIntValue == 1)
                ? new FBCBasicInstruction<REAL>(FBCInstruction::kLoadInt, 0, 0, inst2->fOffset1, 0)
                : nullptr;
                
            case FBCInstruction::kANDInt:
                if (inst1->fIntValue == 1) {  // neutral
                    new FBCBasicInstruction<REAL>(FBCInstruction::kLoadInt, 0, 0, inst2->fOffset1, 0);
                } else if (inst1->fIntValue == 0) {  // absorbant
                    new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, 0, 0);
                } else {
                    return nullptr;
                }
                
            case FBCInstruction::kORInt:
                if (inst1->fIntValue == 1) {  // absorbant
                    new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, 1, 0);
                } else if (inst1->fIntValue == 0) {  // neutral
                    new FBCBasicInstruction<REAL>(FBCInstruction::kLoadInt, 0, 0, inst2->fOffset1, 0);
                } else {
                    return nullptr;
                }
                
            default:
                return nullptr;
        }
    }
    
    // FBCInstruction::kLoadInt
    // FBCInstruction::kInt32Value : sub and div not rewritten
    FBCBasicInstruction<REAL>* rewriteBinaryIntMath3(FBCBasicInstruction<REAL>* inst1, FBCBasicInstruction<REAL>* inst2,
                                                     FBCBasicInstruction<REAL>* inst3)
    {
        switch (inst3->fOpcode) {
            case FBCInstruction::kAddInt:
                return (inst2->fIntValue == REAL(0))
                    ? new FBCBasicInstruction<REAL>(FBCInstruction::kLoadInt, 0, 0, inst1->fOffset1, 0)
                    : nullptr;
                
            case FBCInstruction::kMultInt:
                return (inst2->fIntValue == REAL(1))
                    ? new FBCBasicInstruction<REAL>(FBCInstruction::kLoadInt, 0, 0, inst1->fOffset1, 0)
                    : nullptr;
                
            default:
                return nullptr;
        }
    }
    
    FBCBasicInstruction<REAL>* rewriteExtendedBinaryRealMath(FBCBasicInstruction<REAL>* inst1, FBCBasicInstruction<REAL>* inst2,
                                                             FBCBasicInstruction<REAL>* inst3)
    {
        switch (inst3->fOpcode) {
            case FBCInstruction::kAtan2f:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0,
                                                     std::atan2(inst2->fRealValue, inst1->fRealValue));
                
            case FBCInstruction::kFmodf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0,
                                                     std::fmod(inst2->fRealValue, inst1->fRealValue));
                
            case FBCInstruction::kPowf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0,
                                                     std::pow(inst2->fRealValue, inst1->fRealValue));
                
            case FBCInstruction::kMaxf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0,
                                                     std::max(inst2->fRealValue, inst1->fRealValue));
                
            case FBCInstruction::kMinf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0,
                                                     std::min(inst2->fRealValue, inst1->fRealValue));
                
            default:
                faustassert(false);
                return nullptr;
        }
    }
    
    FBCBasicInstruction<REAL>* rewriteExtendedBinaryIntMath(FBCBasicInstruction<REAL>* inst1, FBCBasicInstruction<REAL>* inst2,
                                                            FBCBasicInstruction<REAL>* inst3)
    {
        switch (inst3->fOpcode) {
            case FBCInstruction::kMax:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value,
                                                     std::max(inst2->fIntValue, inst1->fIntValue), 0);
                
            case FBCInstruction::kMin:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value,
                                                     std::min(inst2->fIntValue, inst1->fIntValue), 0);
                
            default:
                faustassert(false);
                return nullptr;
        }
    }
    
    FBCBasicInstruction<REAL>* rewriteUnaryRealMath(FBCBasicInstruction<REAL>* inst1, FBCBasicInstruction<REAL>* inst2)
    {
        switch (inst2->fOpcode) {
            case FBCInstruction::kAbsf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::fabs(inst1->fRealValue));
                
            case FBCInstruction::kAcosf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::acos(inst1->fRealValue));
                
            case FBCInstruction::kAsinf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::asin(inst1->fRealValue));
                
            case FBCInstruction::kAtanf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::atan(inst1->fRealValue));
                
            case FBCInstruction::kCeilf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::ceil(inst1->fRealValue));
                
            case FBCInstruction::kCosf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::cos(inst1->fRealValue));
                
            case FBCInstruction::kCoshf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::cosh(inst1->fRealValue));
                
            case FBCInstruction::kExpf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::exp(inst1->fRealValue));
                
            case FBCInstruction::kFloorf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::floor(inst1->fRealValue));
                
            case FBCInstruction::kLogf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::log(inst1->fRealValue));
                
            case FBCInstruction::kLog10f:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::log10(inst1->fRealValue));
                
            case FBCInstruction::kRintf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::rint(inst1->fRealValue));
                
            case FBCInstruction::kRoundf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::round(inst1->fRealValue));
                
            case FBCInstruction::kSinf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::sin(inst1->fRealValue));
                
            case FBCInstruction::kSinhf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::sinh(inst1->fRealValue));
                
            case FBCInstruction::kSqrtf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::sqrt(inst1->fRealValue));
                
            case FBCInstruction::kTanf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::tan(inst1->fRealValue));
                
            case FBCInstruction::kTanhf:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kRealValue, 0, std::tanh(inst1->fRealValue));
                
            default:
                faustassert(false);
                return nullptr;
        }
    }
    
    FBCBasicInstruction<REAL>* rewriteUnaryIntMath(FBCBasicInstruction<REAL>* inst1, FBCBasicInstruction<REAL>* inst2)
    {
        switch (inst2->fOpcode) {
            case FBCInstruction::kAbs:
                return new FBCBasicInstruction<REAL>(FBCInstruction::kInt32Value, std::abs(inst1->fIntValue), 0);
                
            default:
                faustassert(false);
                return nullptr;
        }
    }
    
    virtual FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end)
    {
        FBCBasicInstruction<REAL>* &inst1 = *cur;
        FBCBasicInstruction<REAL>* &inst2 = *(cur + 1);
        FBCBasicInstruction<REAL>* &inst3 = *(cur + 2);
        
        FBCBasicInstruction<REAL>* res;
        
        // Real
        if (inst1->fOpcode == FBCInstruction::kRealValue && inst2->fOpcode == FBCInstruction::kRealValue &&
            FBCInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            return rewriteBinaryRealMath(inst1, inst2, inst3);
            
        } else if (inst1->fOpcode == FBCInstruction::kRealValue && inst2->fOpcode == FBCInstruction::kLoadReal &&
                   FBCInstruction::isMath(inst3->fOpcode)) {
            // Uses neutral and absorbent elements (0 for + et - and 1 for * et /)
            res = rewriteBinaryRealMath2(inst1, inst2, inst3);
            if (res) {
                end = cur + 3;
                return res;
            } else {
                end = cur + 1;
                return (*cur)->copy();
            }
            
        } else if (inst1->fOpcode == FBCInstruction::kLoadReal && inst2->fOpcode == FBCInstruction::kRealValue &&
                   FBCInstruction::isMath(inst3->fOpcode)) {
            // Uses neutral and absorbent elements (0 for + - and 1 for * /)
            res = rewriteBinaryRealMath3(inst1, inst2, inst3);
            if (res) {
                end = cur + 3;
                return res;
            } else {
                end = cur + 1;
                return (*cur)->copy();
            }
            
            // Int
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value && inst2->fOpcode == FBCInstruction::kInt32Value &&
                   FBCInstruction::isMath(inst3->fOpcode)) {
            end = cur + 3;
            return rewriteBinaryIntMath(inst1, inst2, inst3);
            
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value && inst2->fOpcode == FBCInstruction::kLoadInt &&
                   FBCInstruction::isMath(inst3->fOpcode)) {
            // Uses neutral and absorbent elements (0 for + - and 1 for * /)
            res = rewriteBinaryIntMath2(inst1, inst2, inst3);
            if (res) {
                end = cur + 3;
                return res;
            } else {
                end = cur + 1;
                return (*cur)->copy();
            }
            
        } else if (inst1->fOpcode == FBCInstruction::kLoadInt && inst2->fOpcode == FBCInstruction::kInt32Value &&
                   FBCInstruction::isMath(inst3->fOpcode)) {
            // Uses neutral and absorbent elements (0 for + - and 1 for * /)
            res = rewriteBinaryIntMath3(inst1, inst2, inst3);
            if (res) {
                end = cur + 3;
                return res;
            } else {
                end = cur + 1;
                return (*cur)->copy();
            }
            
        } else if (inst1->fOpcode == FBCInstruction::kRealValue && inst2->fOpcode == FBCInstruction::kRealValue &&
                   FBCInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            end = cur + 3;
            return rewriteExtendedBinaryRealMath(inst1, inst2, inst3);
            
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value && inst2->fOpcode == FBCInstruction::kInt32Value &&
                   FBCInstruction::isExtendedBinaryMath(inst3->fOpcode)) {
            end = cur + 3;
            return rewriteExtendedBinaryIntMath(inst1, inst2, inst3);
            
        } else if (inst1->fOpcode == FBCInstruction::kRealValue &&
                   FBCInstruction::isExtendedUnaryMath(inst2->fOpcode)) {
            end = cur + 2;
            return rewriteUnaryRealMath(inst1, inst2);
            
        } else if (inst1->fOpcode == FBCInstruction::kInt32Value &&
                   FBCInstruction::isExtendedUnaryMath(inst2->fOpcode)) {
            end = cur + 2;
            return rewriteUnaryIntMath(inst1, inst2);
            
        } else {
            end = cur + 1;
            return (*cur)->copy();
        }
    }
};

template <class REAL>
struct FBCInstructionOptimizer {
    virtual ~FBCInstructionOptimizer() {}
    
    static void displayMaps(std::map<int, int>& int_map, std::map<int, REAL>& real_map)
    {
        std::cout << "displayMaps : int_map" << std::endl;
        for (const auto& it1 : int_map) {
            std::cout << "int_map offset " << it1.first << " value " << it1.second << std::endl;
        }
        
        std::cout << "displayMaps : real_map" << std::endl;
        for (const auto& it2 : real_map) {
            std::cout << "real_map offset " << it2.first << " value " << it2.second << std::endl;
        }
    }
    
    // Rewrite a sequence of instructions starting from 'cur' to 'end' in a new single instruction.
    // Update 'end' so that caller can move at the correct next location
    virtual FBCBasicInstruction<REAL>* rewrite(InstructionIT cur, InstructionIT& end) { return nullptr; }
    
    // Return an optimized block by traversing it (including sub-blocks) with an 'optimizer'
    static FBCBlockInstruction<REAL>* optimize_aux(FBCBlockInstruction<REAL>*     cur_block,
                                                   FBCInstructionOptimizer<REAL>& optimizer)
    {
        faustassert(cur_block);
        
        // Block should have at least 2 instructions...
        if (cur_block->size() < 2) {
            return cur_block->copy();
        }
        
        FBCBlockInstruction<REAL>* new_block = new FBCBlockInstruction<REAL>();
        InstructionIT              next, cur = cur_block->fInstructions.begin();
        
        do {
            FBCBasicInstruction<REAL>* &inst1 = *cur;
            FBCBasicInstruction<REAL>* &inst2 = *(cur + 1);
            
            // Specialization
            if (inst1->fOpcode == FBCInstruction::kInt32Value && FBCInstruction::isChoice(inst2->fOpcode)) {
                if (inst1->fIntValue == 1) {
                    new_block->merge(optimize_aux(inst2->fBranch1, optimizer));
                } else if (inst1->fIntValue == 0) {
                    new_block->merge(optimize_aux(inst2->fBranch2, optimizer));
                } else {
                    faustassert(false);
                }
                cur += 2;
            } else if (inst1->fOpcode == FBCInstruction::kLoop) {
                new_block->push(new FBCBasicInstruction<REAL>(
                    inst1->fOpcode, inst1->fName, inst1->fIntValue, inst1->fRealValue, inst1->fOffset1, inst1->fOffset2,
                    inst1->fBranch1->copy(),  // No optimization for loop variable declaration
                    optimize_aux(inst1->fBranch2, optimizer)));
                cur++;
            } else if (FBCInstruction::isChoice(inst1->fOpcode)) {
                new_block->push(new FBCBasicInstruction<REAL>(
                    inst1->fOpcode, inst1->fName, inst1->fIntValue, inst1->fRealValue, inst1->fOffset1, inst1->fOffset2,
                    optimize_aux(inst1->fBranch1, optimizer), optimize_aux(inst1->fBranch2, optimizer)));
                cur++;
            } else if (inst1->fOpcode == FBCInstruction::kCondBranch) {
                // Special case for loops : branch to new_block
                new_block->push(new FBCBasicInstruction<REAL>(FBCInstruction::kCondBranch, "", 0, 0, 0, 0, new_block, 0));
                cur++;
            } else {
                new_block->push(optimizer.rewrite(cur, next));
                cur = next;
            }
            
        } while (cur != cur_block->fInstructions.end());
        
        return new_block;
    }
    
    // Apply an optimizer on the block, return the optimized new block, then delete the original one
    static FBCBlockInstruction<REAL>* optimize(FBCBlockInstruction<REAL>* cur_block, FBCInstructionOptimizer<REAL>& optimizer)
    {
        FBCBlockInstruction<REAL>* new_block = optimize_aux(cur_block, optimizer);
        delete cur_block;
        return new_block;
    }
    
    // Specialize a block with an optimizer
    static FBCBlockInstruction<REAL>* specialize(FBCBlockInstruction<REAL>* cur_block, FBCInstructionOptimizer<REAL>& optimizer)
    {
        int cur_block_size = cur_block->size();
        int new_block_size = cur_block->size();
        
        do {
            cur_block_size = new_block_size;
            cur_block      = optimize(cur_block, optimizer);
            new_block_size = cur_block->size();
        } while (new_block_size < cur_block_size);
        
        return cur_block;
    }
    
    static FBCBlockInstruction<REAL>* specialize2Heap(FBCBlockInstruction<REAL>* cur_block, std::map<int, int>& int_map,
                                                      std::map<int, REAL>& real_map)
    {
        FBCInstructionConstantValueHeap2Map<REAL> heap_2_map(int_map, real_map);
        
        // Propagate constant values stored in the code into the heap
        return optimize(cur_block, heap_2_map);
    }
    
    // Specialize a block
    static FBCBlockInstruction<REAL>* specialize(FBCBlockInstruction<REAL>* cur_block, std::map<int, int>& int_map,
                                                 std::map<int, REAL>& real_map)
    {
        FBCInstructionConstantValueMap2Heap<REAL> map_2_heap(int_map, real_map);
        FBCInstructionCastSpecializer<REAL>       cast_specializer;
        FBCInstructionMathSpecializer<REAL>       math_specializer;
        FBCInstructionConstantValueHeap2Map<REAL> heap_2_map(int_map, real_map);
        
        // Global specialization
        int cur_block_size = cur_block->size();
        int new_block_size = cur_block->size();
        // displayMaps(int_map, real_map);
        
        do {
            cur_block_size = new_block_size;
            
            // Propagate constant values from the heap into the code
            cur_block = optimize(cur_block, map_2_heap);
            
            // Cast specialization
            cur_block = specialize(cur_block, cast_specializer);
            
            // Math specialization
            cur_block = specialize(cur_block, math_specializer);
            
            // Propagate constant values stored in the code into the heap
            cur_block = optimize(cur_block, heap_2_map);
            
            new_block_size = cur_block->size();
            
        } while (new_block_size < cur_block_size);
        
        // displayMaps(int_map, real_map);
        return cur_block;
    }
    
    static FBCBlockInstruction<REAL>* optimizeBlock(FBCBlockInstruction<REAL>* block, int min_level, int max_level)
    {
        if (min_level <= 1 && 1 <= max_level) {
            // 1) optimize indexed 'heap' load/store in normal load/store
            FBCInstructionLoadStoreOptimizer<REAL> opt1;
            block = FBCInstructionOptimizer<REAL>::optimize(block, opt1);
        }
        
        if (min_level <= 2 && 2 <= max_level) {
            // 2) optimize simple 'heap' load/store in move
            FBCInstructionMoveOptimizer<REAL> opt2;
            block = FBCInstructionOptimizer<REAL>::optimize(block, opt2);
        }
        
        if (min_level <= 3 && 3 <= max_level) {
            // 3) optimize moves in block move
            FBCInstructionBlockMoveOptimizer<REAL> opt3;
            block = FBCInstructionOptimizer<REAL>::optimize(block, opt3);
        }
        
        if (min_level <= 4 && 4 <= max_level) {
            // 4) optimize 2 moves in pair move
            FBCInstructionPairMoveOptimizer<REAL> opt4;
            block = FBCInstructionOptimizer<REAL>::optimize(block, opt4);
        }
        
        if (min_level <= 5 && 5 <= max_level) {
            // 5) optimize 'cast' in heap cast
            FBCInstructionCastOptimizer<REAL> opt5;
            block = FBCInstructionOptimizer<REAL>::optimize(block, opt5);
        }
        
        if (min_level <= 6 && 6 <= max_level) {
            // 6) optimize 'heap' and 'value' math operations
            FBCInstructionMathOptimizer<REAL> opt6;
            block = FBCInstructionOptimizer<REAL>::optimize(block, opt6);
        }
        
        return block;
    }
};

#endif
