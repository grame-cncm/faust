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

#ifndef _FBC_VEC_INTERPRETER_H
#define _FBC_VEC_INTERPRETER_H

#include <string.h>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "exception.hh"
#include "faust/gui/CGlue.h"
#include "fbc_executor.hh"
#include "interpreter_bytecode.hh"

//#define interp_assert(exp) faustassert(exp)
#define interp_assert(exp)

template <class REAL, int TRACE>
struct interpreter_dsp_factory_aux;

// FBC interpreter
template <class REAL, int VEC>
class FBCVecInterpreter : public FBCExecutor<REAL> {
   protected:
    interpreter_dsp_factory_aux<T, 0>* fFactory;

    int*        fIntHeap;
    REAL*       fRealHeap;
    Soundfile** fSoundHeap;

    REAL** fInputs;
    REAL** fOutputs;

#define POP_INT() (int_stack[--int_stack_index])

#define pushAddr(addr) (address_stack[addr_stack_index++] = addr)
#define popAddr() (address_stack[--addr_stack_index])

    virtual void ExecuteBuildUserInterface(FIRUserInterfaceBlockInstruction<T>* block, UIInterface* glue)
    {
        for (const auto& it : block->fInstructions) {
            // it->write(&std::cout);

            switch (it->fOpcode) {
                case FBCInstruction::kOpenVerticalBox:
                    glue->openVerticalBox(it->fLabel.c_str());
                    break;

                case FBCInstruction::kOpenHorizontalBox:
                    glue->openHorizontalBox(it->fLabel.c_str());
                    break;

                case FBCInstruction::kOpenTabBox:
                    glue->openTabBox(it->fLabel.c_str());
                    break;

                case FBCInstruction::kCloseBox:
                    glue->closeBox();
                    break;

                case FBCInstruction::kAddButton:
                    glue->addButton(it->fLabel.c_str(), &fRealHeap[it->fOffset]);
                    break;

                case FBCInstruction::kAddCheckButton:
                    glue->addCheckButton(it->fLabel.c_str(), &fRealHeap[it->fOffset]);
                    break;

                case FBCInstruction::kAddHorizontalSlider:
                    glue->addHorizontalSlider(it->fLabel.c_str(), &fRealHeap[it->fOffset], it->fInit, it->fMin,
                                              it->fMax, it->fStep);
                    break;

                case FBCInstruction::kAddVerticalSlider:
                    glue->addVerticalSlider(it->fLabel.c_str(), &fRealHeap[it->fOffset], it->fInit, it->fMin, it->fMax,
                                            it->fStep);
                    break;

                case FBCInstruction::kAddNumEntry:
                    glue->addNumEntry(it->fLabel.c_str(), &fRealHeap[it->fOffset], it->fInit, it->fMin, it->fMax,
                                      it->fStep);
                    break;

                case FBCInstruction::kAddSoundfile:
                    glue->addSoundfile(it->fLabel.c_str(), it->fKey.c_str(), &fSoundHeap[it->fOffset]);
                    break;

                case FBCInstruction::kAddHorizontalBargraph:
                    glue->addHorizontalBargraph(it->fLabel.c_str(), &fRealHeap[it->fOffset], it->fMin, it->fMax);
                    break;

                case FBCInstruction::kAddVerticalBargraph:
                    glue->addVerticalBargraph(it->fLabel.c_str(), &fRealHeap[it->fOffset], it->fMin, it->fMax);
                    break;

                case FBCInstruction::kDeclare:
                    // Special case for "0" zone
                    if (it->fOffset == -1) {
                        glue->declare(static_cast<T*>(nullptr), it->fKey.c_str(), it->fValue.c_str());
                    } else {
                        glue->declare(&fRealHeap[it->fOffset], it->fKey.c_str(), it->fValue.c_str());
                    }
                    break;

                default:
                    break;
            }
        }
    }

    // virtual void ExecuteVecLoop(FBCBasicInstruction<T>* block)
    virtual void ExecuteBlock(FBCBlockInstruction<REAL>* block)
    {
        static void* fDispatchTable[] = {

            // Numbers
            &&do_kRealValue, &&do_kInt32Value,

            // Memory
            &&do_kLoadReal, &&do_kLoadInt, &&do_kLoadSound, &&do_kLoadSoundField, &&do_kStoreReal, &&do_kStoreInt,
            &&do_kStoreSound, &&do_kStoreRealValue, &&do_kStoreIntValue, &&do_kLoadIndexedReal, &&do_kLoadIndexedInt,
            &&do_kStoreIndexedReal, &&do_kStoreIndexedInt, &&do_kBlockStoreReal, &&do_kBlockStoreInt, &&do_kMoveReal,
            &&do_kMoveInt, &&do_kPairMoveReal, &&do_kPairMoveInt, &&do_kBlockPairMoveReal, &&do_kBlockPairMoveInt,
            &&do_kBlockShiftReal, &&do_kBlockShiftInt, &&do_kLoadInput, &&do_kStoreOutput,

            // Cast/bitcast
            &&do_kCastReal, &&do_kCastInt, &&do_kCastRealHeap, &&do_kCastIntHeap, &&do_kBitcastInt, &&do_kBitcastReal,

            // Standard math (stack OP stack)
            &&do_kAddReal, &&do_kAddInt, &&do_kSubReal, &&do_kSubInt, &&do_kMultReal, &&do_kMultInt, &&do_kDivReal,
            &&do_kDivInt, &&do_kRemReal, &&do_kRemInt, &&do_kLshInt, &&do_kARshInt, &&do_kGTInt, &&do_kLTInt,
            &&do_kGEInt, &&do_kLEInt, &&do_kEQInt, &&do_kNEInt, &&do_kGTReal, &&do_kLTReal, &&do_kGEReal, &&do_kLEReal,
            &&do_kEQReal, &&do_kNEReal, &&do_kANDInt, &&do_kORInt, &&do_kXORInt,

            // Standard math (heap OP heap)
            &&do_kAddRealHeap, &&do_kAddIntHeap, &&do_kSubRealHeap, &&do_kSubIntHeap, &&do_kMultRealHeap,
            &&do_kMultIntHeap, &&do_kDivRealHeap, &&do_kDivIntHeap, &&do_kRemRealHeap, &&do_kRemIntHeap,
            &&do_kLshIntHeap, &&do_kARshIntHeap, &&do_kGTIntHeap, &&do_kLTIntHeap, &&do_kGEIntHeap, &&do_kLEIntHeap,
            &&do_kEQIntHeap, &&do_kNEIntHeap, &&do_kGTRealHeap, &&do_kLTRealHeap, &&do_kGERealHeap, &&do_kLERealHeap,
            &&do_kEQRealHeap, &&do_kNERealHeap, &&do_kANDIntHeap, &&do_kORIntHeap, &&do_kXORIntHeap,

            // Standard math (heap OP stack)
            &&do_kAddRealStack, &&do_kAddIntStack, &&do_kSubRealStack, &&do_kSubIntStack, &&do_kMultRealStack,
            &&do_kMultIntStack, &&do_kDivRealStack, &&do_kDivIntStack, &&do_kRemRealStack, &&do_kRemIntStack,
            &&do_kLshIntStack, &&do_kARshIntStack, &&do_kGTIntStack, &&do_kLTIntStack, &&do_kGEIntStack,
            &&do_kLEIntStack, &&do_kEQIntStack, &&do_kNEIntStack, &&do_kGTRealStack, &&do_kLTRealStack,
            &&do_kGERealStack, &&do_kLERealStack, &&do_kEQRealStack, &&do_kNERealStack, &&do_kANDIntStack,
            &&do_kORIntStack, &&do_kXORIntStack,

            // Standard math (value OP stack)
            &&do_kAddRealStackValue, &&do_kAddIntStackValue, &&do_kSubRealStackValue, &&do_kSubIntStackValue,
            &&do_kMultRealStackValue, &&do_kMultIntStackValue, &&do_kDivRealStackValue, &&do_kDivIntStackValue,
            &&do_kRemRealStackValue, &&do_kRemIntStackValue, &&do_kLshIntStackValue, &&do_kARshIntStackValue,
            &&do_kGTIntStackValue, &&do_kLTIntStackValue, &&do_kGEIntStackValue, &&do_kLEIntStackValue,
            &&do_kEQIntStackValue, &&do_kNEIntStackValue, &&do_kGTRealStackValue, &&do_kLTRealStackValue,
            &&do_kGERealStackValue, &&do_kLERealStackValue, &&do_kEQRealStackValue, &&do_kNERealStackValue,
            &&do_kANDIntStackValue, &&do_kORIntStackValue, &&do_kXORIntStackValue,

            // Standard math (value OP heap)
            &&do_kAddRealValue, &&do_kAddIntValue, &&do_kSubRealValue, &&do_kSubIntValue, &&do_kMultRealValue,
            &&do_kMultIntValue, &&do_kDivRealValue, &&do_kDivIntValue, &&do_kRemRealValue, &&do_kRemIntValue,
            &&do_kLshIntValue, &&do_kARshIntValue, &&do_kGTIntValue, &&do_kLTIntValue, &&do_kGEIntValue,
            &&do_kLEIntValue, &&do_kEQIntValue, &&do_kNEIntValue, &&do_kGTRealValue, &&do_kLTRealValue,
            &&do_kGERealValue, &&do_kLERealValue, &&do_kEQRealValue, &&do_kNERealValue, &&do_kANDIntValue,
            &&do_kORIntValue, &&do_kXORIntValue,

            // Standard math (value OP heap) : non commutative operations
            &&do_kSubRealValueInvert, &&do_kSubIntValueInvert, &&do_kDivRealValueInvert, &&do_kDivIntValueInvert,
            &&do_kRemRealValueInvert, &&do_kRemIntValueInvert, &&do_kLshIntValueInvert, &&do_kARshIntValueInvert,
            &&do_kGTIntValueInvert, &&do_kLTIntValueInvert, &&do_kGEIntValueInvert, &&do_kLEIntValueInvert,
            &&do_kGTRealValueInvert, &&do_kLTRealValueInvert, &&do_kGERealValueInvert, &&do_kLERealValueInvert,

            // Extended unary math
            &&do_kAbs, &&do_kAbsf, &&do_kAcosf, &&do_kAsinf, &&do_kAtanf, &&do_kCeilf, &&do_kCosf, &&do_kCoshf,
            &&do_kExpf, &&do_kFloorf, &&do_kLogf, &&do_kLog10f, &&do_kRintf, &&do_kRoundf, &&do_kSinf, &&do_kSinhf, &&do_kSqrtf,
            &&do_kTanf, &&do_kTanhf,

            // Extended unary math (heap OP heap)
            &&do_kAbsHeap, &&do_kAbsfHeap, &&do_kAcosfHeap, &&do_kAsinfHeap, &&do_kAtanfHeap, &&do_kCeilfHeap,
            &&do_kCosfHeap, &&do_kCoshfHeap, &&do_kExpfHeap, &&do_kFloorfHeap, &&do_kLogfHeap, &&do_kLog10fHeap,
            &&do_kRintfHeap, &&do_kRoundfHeap, &&do_kSinfHeap, &&do_kSinhfHeap, &&do_kSqrtfHeap, &&do_kTanfHeap, &&do_kTanhfHeap,

            // Extended binary math
            &&do_kAtan2f, &&do_kFmodf, &&do_kPowf, &&do_kMax, &&do_kMaxf, &&do_kMin, &&do_kMinf,

            // Extended binary math (heap version)
            &&do_kAtan2fHeap, &&do_kFmodfHeap, &&do_kPowfHeap, &&do_kMaxHeap, &&do_kMaxfHeap, &&do_kMinHeap,
            &&do_kMinfHeap,

            // Extended binary math (stack version)
            &&do_kAtan2fStack, &&do_kFmodfStack, &&do_kPowfStack, &&do_kMaxStack, &&do_kMaxfStack, &&do_kMinStack,
            &&do_kMinfStack,

            // Extended binary math (Stack/Value version)
            &&do_kAtan2fStackValue, &&do_kFmodfStackValue, &&do_kPowfStackValue, &&do_kMaxStackValue,
            &&do_kMaxfStackValue, &&do_kMinStackValue, &&do_kMinfStackValue,

            // Extended binary math (Value version)
            &&do_kAtan2fValue, &&do_kFmodfValue, &&do_kPowfValue, &&do_kMaxValue, &&do_kMaxfValue, &&do_kMinValue,
            &&do_kMinfValue,

            // Extended binary math (Value version) : non commutative operations
            &&do_kAtan2fValueInvert, &&do_kFmodfValueInvert, &&do_kPowfValueInvert,

            // Control
            &&do_kLoop, &&do_kReturn,

            // Select/if
            &&do_kIf, &&do_kSelectReal, &&do_kSelectInt, &&do_kCondBranch

        };

        int real_stack_index  = 0;
        int int_stack_index   = 0;
        int sound_stack_index = 0;
        int addr_stack_index  = 0;

        REAL          real_stack[512];
        int           int_stack[512];
        Soundfile*    sound_stack[512];
        InstructionIT address_stack[64];

#define dispatchFirstVec()                    \
    {                                         \
        goto* fDispatchTable[(*it)->fOpcode]; \
    }
#define dispatchNextVec()                     \
    {                                         \
        it++;                                 \
        goto* fDispatchTable[(*it)->fOpcode]; \
    }

#define dispatchBranch1Vec()                         \
    {                                                \
        it = (*it)->fBranch1->fInstructions.begin(); \
        dispatchFirstVec();                          \
    }
#define dispatchBranch2Vec()                         \
    {                                                \
        it = (*it)->fBranch2->fInstructions.begin(); \
        dispatchFirstVec();                          \
    }

#define pushBranch1Vec()                                  \
    {                                                     \
        pushAddr((*it)->fBranch1->fInstructions.begin()); \
    }
#define pushBranch2Vec()                                  \
    {                                                     \
        pushAddr((*it)->fBranch2->fInstructions.begin()); \
    }

#define dispatchReturnVec() \
    {                       \
        it = popAddr();     \
        dispatchFirstVec(); \
    }
#define saveReturnVec()   \
    {                     \
        pushAddr(it + 1); \
    }
#define emptyReturnVec() (addr_stack_index == 0)

#define pushSound(val) (sound_stack[sound_stack_index++] = val)
#define popSound() (sound_stack[--sound_stack_index])

        // #pragma clang loop vectorize(enable) interleave(enable)

#define VEC_LOOP(code)                  \
    {                                   \
        for (int j = 0; j < VEC; j++) { \
            code;                       \
        }                               \
    }

#define STACK_UP_INT() int_stack_index += VEC
#define STACK_DOWN_INT() int_stack_index -= VEC

#define STACK_UP_REAL() real_stack_index += VEC
#define STACK_DOWN_REAL() real_stack_index -= VEC

#define PUSH_VEC_INT(val) int_stack[int_stack_index + j] = (val)
#define PUSH_VEC_REAL(val) real_stack[real_stack_index + j] = (val)

#define POP_VEC_INT() int_stack[int_stack_index - (j + 1)]
#define POP_VEC_REAL() real_stack[real_stack_index - (j + 1)]

#define WRITE_HEAP_VEC_REAL(off, val) fRealHeap[(off) + j] = (val)
#define WRITE_HEAP_VEC_INT(off, val) fIntHeap[(off) + j] = (val)

#define READ_HEAP_VEC_REAL(off) fRealHeap[(off) + j]
#define READ_HEAP_VEC_INT(off) fIntHeap[(off) + j]

        // Check block coherency
        // block->check();

        // std::cout << "ExecuteBlock : " << block->fInstructions.size() << "\n";
        // block->write(&std::cout);

        int v1_int[VEC];
        int v2_int[VEC];
        REAL v1_real[VEC];
        REAL v2_real[VEC];

        try {
            InstructionIT it = block->fInstructions.begin();
            dispatchFirstVec();

        /*
        // Execute VecLoop
        InstructionIT it;

        // Push branch2 (loop content)
        interp_assert((*it)->fBranch2);
        pushBranch2Vec();

        // And start branch1 loop variable declaration block
        interp_assert((*it)->fBranch1);
        dispatchBranch1Vec();
        */

        // Number operations
        do_kRealValue : {
            VEC_LOOP(PUSH_VEC_REAL((*it)->fRealValue));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kInt32Value : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Memory operations
        do_kLoadReal : {
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kLoadInt : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLoadSound : {
            pushSound(fSoundHeap[(*it)->fOffset1]);
            dispatchNextVec();
        }

        do_kLoadSoundField : {
            /*
             if (TRACE) {
                push_sound(fSoundHeap[assert_sound_heap(it, (*it)->fOffset1)]);
             } else {
                push_sound(fSoundHeap[(*it)->fOffset1]);
             }
                dispatch_next();
             */
        }

        do_kStoreReal : {
            VEC_LOOP(WRITE_HEAP_VEC_REAL((*it)->fOffset1, POP_VEC_REAL()));
            STACK_DOWN_REAL();
            dispatchNextVec();
        }

        do_kStoreInt : {
            VEC_LOOP(WRITE_HEAP_VEC_INT((*it)->fOffset1, POP_VEC_INT()));
            STACK_DOWN_INT();
            dispatchNextVec();
        }

        do_kStoreSound : {
            // fSoundHeap[(*it)->fOffset1] = popSound();
            dispatchNextVec();
        }

        // Directly store a value
        do_kStoreRealValue : {
            VEC_LOOP(WRITE_HEAP_VEC_REAL((*it)->fOffset1, (*it)->fRealValue));
            dispatchNextVec();
        }

        do_kStoreIntValue : {
            VEC_LOOP(WRITE_HEAP_VEC_INT((*it)->fOffset1, (*it)->fIntValue));
            dispatchNextVec();
        }

        do_kLoadIndexedReal : {
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1 + POP_VEC_INT())));
            STACK_UP_REAL();
            STACK_DOWN_INT();
            dispatchNextVec();
        }

        do_kLoadIndexedInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1 + v1_int[j])));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kStoreIndexedReal : {
            VEC_LOOP(WRITE_HEAP_VEC_REAL((*it)->fOffset1 + POP_VEC_INT(), POP_VEC_REAL()));
            STACK_DOWN_REAL();
            STACK_DOWN_INT();
            dispatchNextVec();
        }

        do_kStoreIndexedInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(WRITE_HEAP_VEC_INT((*it)->fOffset1 + v1_int[j], POP_VEC_INT()));
            STACK_DOWN_INT();
            dispatchNextVec();
        }

        do_kBlockStoreReal : {
            FIRBlockStoreRealInstruction<T>* inst = static_cast<FIRBlockStoreRealInstruction<T>*>(*it);
            interp_assert(inst);
            for (int i = 0; i < inst->fOffset2; i++) {
                fRealHeap[inst->fOffset1 + i] = inst->fNumTable[i];
            }
            dispatchNextVec();
        }

        do_kBlockStoreInt : {
            FIRBlockStoreIntInstruction<T>* inst = static_cast<FIRBlockStoreIntInstruction<T>*>(*it);
            interp_assert(inst);
            for (int i = 0; i < inst->fOffset2; i++) {
                fIntHeap[inst->fOffset1 + i] = inst->fNumTable[i];
            }
            dispatchNextVec();
        }

        do_kMoveReal : {
            fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset2];
            dispatchNextVec();
        }

        do_kMoveInt : {
            fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset2];
            dispatchNextVec();
        }

        do_kPairMoveReal : {
            fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset1 - 1];
            fRealHeap[(*it)->fOffset2] = fRealHeap[(*it)->fOffset2 - 1];
            dispatchNextVec();
        }

        do_kPairMoveInt : {
            fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset1 - 1];
            fIntHeap[(*it)->fOffset2] = fIntHeap[(*it)->fOffset2 - 1];
            dispatchNextVec();
        }

        do_kBlockPairMoveReal : {
            for (int i = (*it)->fOffset1; i < (*it)->fOffset2; i += 2) {
                fRealHeap[i + 1] = fRealHeap[i];
            }
            dispatchNextVec();
        }

        do_kBlockPairMoveInt : {
            for (int i = (*it)->fOffset1; i < (*it)->fOffset2; i += 2) {
                fIntHeap[i + 1] = fIntHeap[i];
            }
            dispatchNextVec();
        }

        do_kBlockShiftReal : {
            for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                fRealHeap[i] = fRealHeap[i - 1];
            }
            dispatchNextVec();
        }

        do_kBlockShiftInt : {
            for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                fIntHeap[i] = fIntHeap[i - 1];
            }
            dispatchNextVec();
        }

        // Input/output access
        do_kLoadInput : {
            VEC_LOOP(PUSH_VEC_REAL(fInputs[(*it)->fOffset1][POP_VEC_INT()]));
            STACK_UP_REAL();
            STACK_DOWN_INT();
            dispatchNextVec();
        }

        do_kStoreOutput : {
            VEC_LOOP(fOutputs[(*it)->fOffset1][POP_VEC_INT()] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            STACK_DOWN_INT();
            dispatchNextVec();
        }

        // Cast operations
        do_kCastReal : {
            VEC_LOOP(PUSH_VEC_REAL(T(POP_VEC_INT())));
            STACK_UP_REAL();
            STACK_DOWN_INT();
            dispatchNextVec();
        }

        do_kCastRealHeap : {
            VEC_LOOP(PUSH_VEC_REAL(T(READ_HEAP_VEC_INT((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kCastInt : {
            VEC_LOOP(PUSH_VEC_INT(T(POP_VEC_REAL())));
            STACK_DOWN_REAL();
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kCastIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(T(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Bitcast operations
        do_kBitcastInt : {
            VEC_LOOP(T v1 = POP_VEC_REAL(); PUSH_VEC_INT(*reinterpret_cast<int*>(&v1)));
            STACK_DOWN_REAL();
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kBitcastReal : {
            VEC_LOOP(int v1 = POP_VEC_INT(); PUSH_VEC_REAL(*reinterpret_cast<T*>(&v1)));
            STACK_UP_REAL();
            STACK_DOWN_INT();
            dispatchNextVec();
        }

            //-------------------------------------------------------
            // Standard math operations : 'stack' OP 'stack' version
            //-------------------------------------------------------

        do_kAddReal : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(v1_real[j] + v2_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAddInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] + v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kSubReal : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(v1_real[j] - v2_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSubInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] - v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMultReal : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(v1_real[j] * v2_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMultInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] * v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kDivReal : {
            VEC_LOOP(v1_int[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(v1_int[j] / v2_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kDivInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] / v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kRemReal : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::remainder(v1_real[j], v2_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kRemInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] % v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Shift operation
        do_kLshInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] << v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kARshInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] >> v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Int
        do_kGTInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] > v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] < v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGEInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] >= v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLEInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] <= v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kEQInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] == v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kNEInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] != v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Real
        do_kGTReal : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(v1_real[j] > v2_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTReal : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(v1_real[j] < v2_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGEReal : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(v1_real[j] >= v2_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLEReal : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(v1_real[j] <= v2_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kEQReal : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(v1_real[j] == v2_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kNEReal : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(v1_real[j] != v2_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Logical operations
        do_kANDInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] & v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kORInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] | v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kXORInt : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(v1_int[j] ^ v2_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

            //-----------------------------------------------------
            // Standard math operations : 'heap' OP 'heap' version
            //-----------------------------------------------------

        do_kAddRealHeap : {
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1) + READ_HEAP_VEC_REAL((*it)->fOffset2)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAddIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) + READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kSubRealHeap : {
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1) - READ_HEAP_VEC_REAL((*it)->fOffset2)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSubIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) - READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMultRealHeap : {
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1) * READ_HEAP_VEC_REAL((*it)->fOffset2)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMultIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) * READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kDivRealHeap : {
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1) / READ_HEAP_VEC_REAL((*it)->fOffset2)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kDivIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) / READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kRemRealHeap : {
            VEC_LOOP(PUSH_VEC_REAL(
                std::remainder(READ_HEAP_VEC_REAL((*it)->fOffset1), READ_HEAP_VEC_REAL((*it)->fOffset2))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kRemIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) % READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Shift operation
        do_kLshIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) << READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kARshIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) >> READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Int
        do_kGTIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) > READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) < READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGEIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) >= READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLEIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) <= READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kEQIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) == READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kNEIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) != READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Real
        do_kGTRealHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) > READ_HEAP_VEC_REAL((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTRealHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) < READ_HEAP_VEC_REAL((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGERealHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) >= READ_HEAP_VEC_REAL((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLERealHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) <= READ_HEAP_VEC_REAL((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kEQRealHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) == READ_HEAP_VEC_REAL((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kNERealHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) != READ_HEAP_VEC_REAL((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Logical operations
        do_kANDIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) & READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kORIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) | READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kXORIntHeap : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) ^ READ_HEAP_VEC_INT((*it)->fOffset2)));
            STACK_UP_INT();
            dispatchNextVec();
        }

            //------------------------------------------------------
            // Standard math operations : 'stack' OP 'heap' version
            //------------------------------------------------------

        do_kAddRealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1) + v1_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAddIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) + v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kSubRealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1) - v1_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSubIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) - v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMultRealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1) * v1_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMultIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) * v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kDivRealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1) / v1_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kDivIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) / v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kRemRealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::remainder(READ_HEAP_VEC_REAL((*it)->fOffset1), v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kRemIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) % v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Shift operation
        do_kLshIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) << v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kARshIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) >> v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Int
        do_kGTIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) > v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) < v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGEIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) >= v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLEIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) <= v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kEQIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) == v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kNEIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) != v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Real
        do_kGTRealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) > v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTRealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) < v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGERealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) >= v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLERealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) <= v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kEQRealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) == v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kNERealStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) != v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Logical operations
        do_kANDIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) & v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kORIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) | v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kXORIntStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) ^ v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

            //-------------------------------------------------------
            // Standard math operations : 'stack' OP 'value' version
            //-------------------------------------------------------

        do_kAddRealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL((*it)->fRealValue + v1_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAddIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue + v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kSubRealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL((*it)->fRealValue - v1_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSubIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue - v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMultRealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL((*it)->fRealValue * v1_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMultIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue * v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kDivRealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL((*it)->fRealValue / v1_real[j]));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kDivIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue / v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kRemRealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::remainder((*it)->fRealValue, v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kRemIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue % v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Shift operation
        do_kLshIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue << v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kARshIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue >> v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Int
        do_kGTIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue > v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue < v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGEIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue >= v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLEIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue <= v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kEQIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue == v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kNEIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue != v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Real
        do_kGTRealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue > v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTRealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue < v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGERealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue >= v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLERealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue <= v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kEQRealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue == v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kNERealStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue != v1_real[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Logical operations
        do_kANDIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue & v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kORIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue | v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kXORIntStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue ^ v1_int[j]));
            STACK_UP_INT();
            dispatchNextVec();
        }

            //------------------------------------------------------
            // Standard math operations : 'value' OP 'heap' version
            //------------------------------------------------------

        do_kAddRealValue : {
            VEC_LOOP(PUSH_VEC_REAL((*it)->fRealValue + READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAddIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue + READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kSubRealValue : {
            VEC_LOOP(PUSH_VEC_REAL((*it)->fRealValue - READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSubIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue - READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMultRealValue : {
            VEC_LOOP(PUSH_VEC_REAL((*it)->fRealValue * READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMultIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue * READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kDivRealValue : {
            VEC_LOOP(PUSH_VEC_REAL((*it)->fRealValue / READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kDivIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue / READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kRemRealValue : {
            VEC_LOOP(PUSH_VEC_REAL(std::remainder((*it)->fRealValue, READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kRemIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue % READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Shift operation
        do_kLshIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue << READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kARshIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue >> READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Int
        do_kGTIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue > READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue < READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGEIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue >= READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLEIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue <= READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kEQIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue == READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kNEIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue != READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Real
        do_kGTRealValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue > READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTRealValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue < READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGERealValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue >= READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLERealValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue <= READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kEQRealValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue == READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kNERealValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fRealValue != READ_HEAP_VEC_REAL((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Logical operations
        do_kANDIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue & READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kORIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue | READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kXORIntValue : {
            VEC_LOOP(PUSH_VEC_INT((*it)->fIntValue ^ READ_HEAP_VEC_INT((*it)->fOffset1)));
            STACK_UP_INT();
            dispatchNextVec();
        }

            //----------------------------------------------------
            // Standard math operations : Value inverted version
            // (non commutative operations)
            //----------------------------------------------------

        do_kSubRealValueInvert : {
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1) - (*it)->fRealValue));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSubIntValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) - (*it)->fIntValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kDivRealValueInvert : {
            VEC_LOOP(PUSH_VEC_REAL(READ_HEAP_VEC_REAL((*it)->fOffset1) / (*it)->fRealValue));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kDivIntValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) / (*it)->fIntValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kRemRealValueInvert : {
            VEC_LOOP(PUSH_VEC_REAL(std::remainder(READ_HEAP_VEC_REAL((*it)->fOffset1), (*it)->fRealValue)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kRemIntValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) % (*it)->fIntValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Shift operation
        do_kLshIntValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) << (*it)->fIntValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kARshIntValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) >> (*it)->fIntValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Int
        do_kGTIntValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) > (*it)->fIntValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTIntValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) < (*it)->fIntValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGEIntValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) >= (*it)->fIntValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLEIntValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_INT((*it)->fOffset1) <= (*it)->fIntValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        // Comparaison Real
        do_kGTRealValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) > (*it)->fRealValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLTRealValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) < (*it)->fRealValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kGERealValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) >= (*it)->fRealValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kLERealValueInvert : {
            VEC_LOOP(PUSH_VEC_INT(READ_HEAP_VEC_REAL((*it)->fOffset1) <= (*it)->fRealValue));
            STACK_UP_INT();
            dispatchNextVec();
        }

            //---------------------
            // Extended unary math
            //---------------------

        do_kAbs : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(std::abs(v1_int[j])));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kAbsf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::fabs(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAcosf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::acos(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAsinf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::asin(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAtanf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::atan(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kCeilf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::ceil(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kCosf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::cos(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kCoshf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::cosh(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kExpf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::exp(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kFloorf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::floor(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kLogf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::log(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kLog10f : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::log10(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }
            
        do_kRintf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::rint(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kRoundf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::round(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSinf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::sin(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSinhf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::sinh(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSqrtf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::sqrt(v1_real[j])));
            dispatchNextVec();
        }

        do_kTanf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::tan(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kTanhf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::tanh(v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

            //------------------------------------
            // Extended unary math (heap version)
            ///-----------------------------------

        do_kAbsHeap : {
            VEC_LOOP(PUSH_VEC_INT(std::abs(READ_HEAP_VEC_INT((*it)->fOffset1))));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kAbsfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::fabs(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAcosfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::acos(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAsinfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::asin(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kAtanfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::atan(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kCeilfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::ceil(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kCosfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::cos(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kCoshfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::cosh(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kExpfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::exp(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kFloorfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::floor(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kLogfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::log(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kLog10fHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::log10(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }
            
        do_kRintfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::rint(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kRoundfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::round(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSinfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::sin(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSinhfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::sinh(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kSqrtfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::sqrt(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kTanfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::tan(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kTanhfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::tanh(READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

            //----------------------
            // Extended binary math
            //----------------------

        do_kAtan2f : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::atan2(v1_real[j], v2_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kFmodf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::fmod(v1_real[j], v2_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kPowf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::pow(v1_real[j], v2_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMax : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(std::max(v1_int[j], v2_int[j])));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMaxf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::max(v1_real[j], v2_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMin : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(v2_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(std::min(v1_int[j], v2_int[j])));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMinf : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(v2_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::min(v1_real[j], v2_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

            //-------------------------------------
            // Extended binary math (heap version)
            //-------------------------------------

        do_kAtan2fHeap : {
            VEC_LOOP(
                PUSH_VEC_REAL(std::atan2(READ_HEAP_VEC_REAL((*it)->fOffset1), READ_HEAP_VEC_REAL((*it)->fOffset2))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kFmodfHeap : {
            VEC_LOOP(
                PUSH_VEC_REAL(std::fmod(READ_HEAP_VEC_REAL((*it)->fOffset1), READ_HEAP_VEC_REAL((*it)->fOffset2))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kPowfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::pow(READ_HEAP_VEC_REAL((*it)->fOffset1), READ_HEAP_VEC_REAL((*it)->fOffset2))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMaxHeap : {
            VEC_LOOP(PUSH_VEC_INT(std::max(READ_HEAP_VEC_INT((*it)->fOffset1), READ_HEAP_VEC_INT((*it)->fOffset2))));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMaxfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::max(READ_HEAP_VEC_REAL((*it)->fOffset1), READ_HEAP_VEC_REAL((*it)->fOffset2))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMinHeap : {
            VEC_LOOP(PUSH_VEC_INT(std::min(READ_HEAP_VEC_INT((*it)->fOffset1), READ_HEAP_VEC_INT((*it)->fOffset2))));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMinfHeap : {
            VEC_LOOP(PUSH_VEC_REAL(std::min(READ_HEAP_VEC_REAL((*it)->fOffset1), READ_HEAP_VEC_REAL((*it)->fOffset2))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

            //--------------------------------------
            // Extended binary math (stack version)
            //--------------------------------------

        do_kAtan2fStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::atan2(READ_HEAP_VEC_REAL((*it)->fOffset1), v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kFmodfStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::fmod(READ_HEAP_VEC_REAL((*it)->fOffset1), v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kPowfStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::pow(READ_HEAP_VEC_REAL((*it)->fOffset1), v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMaxStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(std::max(READ_HEAP_VEC_INT((*it)->fOffset1), v1_int[j])));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMaxfStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::max(READ_HEAP_VEC_REAL((*it)->fOffset1), v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMinStack : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(std::min(READ_HEAP_VEC_INT((*it)->fOffset1), v1_int[j])));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMinfStack : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::min(READ_HEAP_VEC_REAL((*it)->fOffset1), v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

            //--------------------------------------------
            // Extended binary math (stack/value version)
            //--------------------------------------------

        do_kAtan2fStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::atan2((*it)->fRealValue, v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kFmodfStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::fmod((*it)->fRealValue, v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kPowfStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::pow((*it)->fRealValue, v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMaxStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(std::max((*it)->fIntValue, v1_int[j])));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMaxfStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::max((*it)->fRealValue, v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMinStackValue : {
            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            VEC_LOOP(PUSH_VEC_INT(std::min((*it)->fIntValue, v1_int[j])));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMinfStackValue : {
            VEC_LOOP(v1_real[j] = POP_VEC_REAL());
            STACK_DOWN_REAL();
            VEC_LOOP(PUSH_VEC_REAL(std::min((*it)->fRealValue, v1_real[j])));
            STACK_UP_REAL();
            dispatchNextVec();
        }

            //-------------------------------------
            // Extended binary math (Value version)
            //-------------------------------------

        do_kAtan2fValue : {
            VEC_LOOP(PUSH_VEC_REAL(std::atan2((*it)->fRealValue, READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kFmodfValue : {
            VEC_LOOP(PUSH_VEC_REAL(std::fmod((*it)->fRealValue, READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kPowfValue : {
            VEC_LOOP(PUSH_VEC_REAL(std::pow((*it)->fRealValue, READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMaxValue : {
            VEC_LOOP(PUSH_VEC_INT(std::max((*it)->fIntValue, READ_HEAP_VEC_INT((*it)->fOffset1))));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMaxfValue : {
            VEC_LOOP(PUSH_VEC_REAL(std::max((*it)->fRealValue, READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kMinValue : {
            VEC_LOOP(PUSH_VEC_INT(std::min((*it)->fIntValue, READ_HEAP_VEC_INT((*it)->fOffset1))));
            STACK_UP_INT();
            dispatchNextVec();
        }

        do_kMinfValue : {
            VEC_LOOP(PUSH_VEC_REAL(std::min((*it)->fRealValue, READ_HEAP_VEC_REAL((*it)->fOffset1))));
            STACK_UP_REAL();
            dispatchNextVec();
        }

            //-------------------------------------------------------------------
            // Extended binary math (Value version) : non commutative operations
            //-------------------------------------------------------------------

        do_kAtan2fValueInvert : {
            VEC_LOOP(PUSH_VEC_REAL(std::atan2(READ_HEAP_VEC_REAL((*it)->fOffset1), (*it)->fRealValue)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kFmodfValueInvert : {
            VEC_LOOP(PUSH_VEC_REAL(std::fmod(READ_HEAP_VEC_REAL((*it)->fOffset1), (*it)->fRealValue)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

        do_kPowfValueInvert : {
            VEC_LOOP(PUSH_VEC_REAL(std::pow(READ_HEAP_VEC_REAL((*it)->fOffset1), (*it)->fRealValue)));
            STACK_UP_REAL();
            dispatchNextVec();
        }

            //---------
            // Control
            //---------

        do_kReturn : {
            // Empty addr stack = end of computation
            if (emptyReturnVec()) {
                goto end;
            } else {
                dispatchReturnVec();
            }
        }

        do_kIf : {
            // Keep next instruction
            saveReturnVec();

            if (POP_INT()) {
                // Execute new block
                interp_assert((*it)->fBranch1);
                dispatchBranch1Vec();
                // No value (If)
            } else {
                // Execute new block
                interp_assert((*it)->fBranch2);
                dispatchBranch2Vec();
                // No value (If)
            }
        }

        do_kSelectReal : {
            // Keep next instruction
            saveReturnVec();

            // Compute condition vector

            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            // Execute new block
            VEC_LOOP(if (v1_int[j]) { dispatchBranch1Vec(); } else { dispatchBranch2Vec(); });
        }

        do_kSelectInt : {
            // Keep next instruction
            saveReturnVec();

            // Compute condition vector

            VEC_LOOP(v1_int[j] = POP_VEC_INT());
            STACK_DOWN_INT();
            // Execute new block
            VEC_LOOP(if (v1_int[j]) { dispatchBranch1Vec(); } else { dispatchBranch2Vec(); });
        }

        do_kCondBranch : {
            // If condition is true, just branch back on the block beginning
            if (POP_INT()) {
                interp_assert((*it)->fBranch1);
                dispatchBranch1Vec();
            } else {
                // Just continue after 'loop block' (do the final 'return')
                dispatchNextVec();
            }
        }

        do_kLoop : {
            // (*it)->fIntValue = vec_size

            // this->ExecuteVecLoop((*it));

            /*
            if ((*it)->fIntValue == 1) {
                this->ExecuteVecLoop<1, TRACE>((*it));
            } else if ((*it)->fIntValue == 4) {
                this->ExecuteVecLoop<4, TRACE>((*it));
            } else if ((*it)->fIntValue == 8) {
                this->ExecuteVecLoop<8, TRACE>((*it));
            } else if ((*it)->fIntValue == 16) {
                this->ExecuteVecLoop<16, TRACE>((*it));
            } else if ((*it)->fIntValue == 32) {
                this->ExecuteVecLoop<32, TRACE>((*it));
            } else if ((*it)->fIntValue == 64) {
                this->ExecuteVecLoop<64, TRACE>((*it));
            } else {
                this->ExecuteVecLoop<128, TRACE>((*it));
            }
            */

            // Keep next instruction
            saveReturnVec();

            // Push branch2 (loop content)
            interp_assert((*it)->fBranch2);
            pushBranch2Vec();

            // And start branch1 loop variable declaration block
            interp_assert((*it)->fBranch1);
            dispatchBranch1Vec();
        }

        end:
            // printf("END real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index);

            // Check stack coherency
            interp_assert(real_stack_index == 0 && int_stack_index == 0 && sound_stack_index == 0);

        } catch (faustexception& e) {
            std::cout << e.Message();
        }
    }

   public:
    FBCVecInterpreter(interpreter_dsp_factory_aux<REAL, 0>* factory)
    {
        /*
        std::cout << "FBCVecInterpreter :"
                << " int_heap_size " << int_heap_size
                << " real_heap_size " << real_heap_size
                << " sr_offset " << sr_offset
                << " count_offset " << count_offset << std::endl;
        */

        fFactory = factory;

        if (fFactory->getMemoryManager()) {
            fRealHeap  = static_cast<T*>(fFactory->allocate(sizeof(T) * fFactory->fRealHeapSize));
            fIntHeap   = static_cast<int*>(fFactory->allocate(sizeof(T) * fFactory->fIntHeapSize));
            fSoundHeap = static_cast<Soundfile**>(fFactory->allocate(sizeof(Soundfile*) * fFactory->fSoundHeapSize));
            fInputs    = static_cast<T**>(fFactory->allocate(sizeof(T*) * fFactory->fNumInputs));
            fOutputs   = static_cast<T**>(fFactory->allocate(sizeof(T*) * fFactory->fNumOutputs));
        } else {
            fRealHeap  = new T[fFactory->fRealHeapSize];
            fIntHeap   = new int[fFactory->fIntHeapSize];
            fSoundHeap = new Soundfile*[fFactory->fSoundHeapSize];
            fInputs    = new T*[fFactory->fNumInputs];
            fOutputs   = new T*[fFactory->fNumOutputs];
        }

        // std::cout << "==== FBCVecInterpreter ==== " << std::endl;
        // std::cout << "fRealHeapSize = " << fFactory->fRealHeapSize << std::endl;
        // std::cout << "fIntHeapSize = " << fFactory->fIntHeapSize << std::endl;

        // Initialise HEAP with 0
        memset(fRealHeap, 0, fFactory->fRealHeapSize * sizeof(REAL));
        memset(fIntHeap, 0, fFactory->fIntHeapSize * sizeof(int));
    }

    FBCVecInterpreter(interpreter_dsp_factory_aux<REAL, 1>* factory)
        : FBCVecInterpreter((interpreter_dsp_factory_aux<REAL, 0>*)factory)
    {
    }

    FBCVecInterpreter(interpreter_dsp_factory_aux<REAL, 2>* factory)
        : FBCVecInterpreter((interpreter_dsp_factory_aux<REAL, 0>*)factory)
    {
    }

    FBCVecInterpreter(interpreter_dsp_factory_aux<REAL, 3>* factory)
        : FBCVecInterpreter((interpreter_dsp_factory_aux<REAL, 0>*)factory)
    {
    }

    FBCVecInterpreter(interpreter_dsp_factory_aux<REAL, 4>* factory)
        : FBCVecInterpreter((interpreter_dsp_factory_aux<REAL, 0>*)factory)
    {
    }

    FBCVecInterpreter(interpreter_dsp_factory_aux<REAL, 5>* factory)
        : FBCVecInterpreter((interpreter_dsp_factory_aux<REAL, 0>*)factory)
    {
    }

    FBCVecInterpreter(interpreter_dsp_factory_aux<REAL, 6>* factory)
        : FBCVecInterpreter((interpreter_dsp_factory_aux<REAL, 0>*)factory)
    {
    }

    FBCVecInterpreter(interpreter_dsp_factory_aux<REAL, 7>* factory)
        : FBCVecInterpreter((interpreter_dsp_factory_aux<REAL, 0>*)factory)
    {
    }

    virtual ~FBCVecInterpreter()
    {
        if (fFactory->getMemoryManager()) {
            fFactory->destroy(fRealHeap);
            fFactory->destroy(fIntHeap);
            fFactory->destroy(fSoundHeap);
            fFactory->destroy(fInputs);
            fFactory->destroy(fOutputs);
        } else {
            delete[] fRealHeap;
            delete[] fIntHeap;
            delete[] fSoundHeap;
            delete[] fInputs;
            delete[] fOutputs;
        }
    }

    void setIntValue(int offset, int value) { fIntHeap[offset] = value; }
    int  getIntValue(int offset) { return fIntHeap[offset]; }

    virtual void setInput(int offset, REAL* buffer) { fInputs[offset] = buffer; }
    virtual void setOutput(int offset, REAL* buffer) { fOutputs[offset] = buffer; }
};

#endif
