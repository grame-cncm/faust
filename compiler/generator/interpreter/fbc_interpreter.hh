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

#ifndef _FBC_INTERPRETER_H
#define _FBC_INTERPRETER_H

#include <string.h>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "exception.hh"
#include "fbc_executor.hh"
#include "interpreter_bytecode.hh"

/*
 Interpreter using 'computed goto' technique: https://eli.thegreenplace.net/2012/07/12/computed-goto-for-efficient-dispatch-tables

 Trace mode: only check 'non-optimized' interpreter operations, since the code is not optimized in this case.

 1 : collect FP_SUBNORMAL only
 2 : collect FP_SUBNORMAL, FP_INFINITE and FP_NAN
 3 : collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW and DIV_BY_ZERO
 4 : collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, fails at first FP_INFINITE or FP_NAN
 5 : collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, continue after FP_INFINITE or FP_NAN

*/

#define INTEGER_OVERFLOW -1
#define DIV_BY_ZERO -2
#define DUMMY_REAL 0.12233344445555
#define DUMMY_INT 1223334444

//#define assertInterp(exp) faustassert(exp)
#define assertInterp(exp)

template <class T, int TRACE>
struct interpreter_dsp_factory_aux;

// FBC interpreter
template <class T, int TRACE>
class FBCInterpreter : public FBCExecutor<T> {
   protected:
    interpreter_dsp_factory_aux<T, TRACE>* fFactory;

    int*        fIntHeap;
    T*          fRealHeap;
    Soundfile** fSoundHeap;

    T** fInputs;
    T** fOutputs;

    std::map<int, long long> fRealStats;

    /*
     Keeps the latest TRACE_STACK_SIZE executed instructions, to be displayed when an error occurs.
     */
    struct InterpreterTrace {
#define TRACE_STACK_SIZE 16

        std::vector<std::string> fExecTrace;
        int                      fWriteIndex;
        std::stringstream        fMessage;

        InterpreterTrace()
        {
            for (int i = 0; i < TRACE_STACK_SIZE; i++) {
                fExecTrace.push_back("");
            }
            fWriteIndex = 0;
        }

        void push(const std::string& message)
        {
            fExecTrace[fWriteIndex] = message;
            fWriteIndex             = (fWriteIndex + 1) % TRACE_STACK_SIZE;
        }

        void write(std::ostream* out)
        {
            for (int i = fWriteIndex - 1; i >= 0; i--) {
                *out << fExecTrace[i];
            }
            for (int i = int(fExecTrace.size()) - 1; i >= fWriteIndex; i--) {
                *out << fExecTrace[i];
            }
        }

        void traceInstruction(InstructionIT it)
        {
            (*it)->write(&fMessage, false, false, false);  // Last param = false means no recursion in branches
            push(fMessage.str());
            fMessage.str("");
        }
    };

    InterpreterTrace fTraceContext;

    inline void traceInstruction(InstructionIT it)
    {
        if (TRACE >= 4) {
            fTraceContext.traceInstruction(it);
        }
    }

    void printStats()
    {
        if (TRACE > 0 && TRACE < 6) {
            std::cout << "-------------------------------" << std::endl;
            std::cout << "Interpreter statistics" << std::endl;
            if (TRACE >= 1) {
                std::cout << "FP_SUBNORMAL: " << fRealStats[FP_SUBNORMAL] << std::endl;
            }
            if (TRACE >= 2) {
                std::cout << "FP_INFINITE: " << fRealStats[FP_INFINITE] << std::endl;
                std::cout << "FP_NAN: " << fRealStats[FP_NAN] << std::endl;
            }
            if (TRACE >= 3) {
                std::cout << "INTEGER_OVERFLOW: " << fRealStats[INTEGER_OVERFLOW] << std::endl;
                std::cout << "DIV_BY_ZERO: " << fRealStats[DIV_BY_ZERO] << std::endl;
            }
            std::cout << "-------------------------------" << std::endl;
        }
    }

    inline void warningOverflow(InstructionIT it)
    {
        if (TRACE >= 6) return;

        if (TRACE >= 3) {
            fRealStats[INTEGER_OVERFLOW]++;
        }

        if (TRACE >= 5) {
            std::cout << "-------- Interpreter 'Overflow' warning trace start --------" << std::endl;
            traceInstruction(it);
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter 'Overflow' warning trace end --------\n\n";
        }
    }

    inline void checkDivZero(InstructionIT it, T val)
    {
        if (TRACE >= 6) return;

        if ((TRACE >= 3) && (val == T(0))) {
            fRealStats[DIV_BY_ZERO]++;
        }

        if ((TRACE >= 4) && (val == T(0))) {
            std::cout << "-------- Interpreter 'div by zero' trace start --------" << std::endl;
            traceInstruction(it);
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter 'div by zero' trace end ----------\n\n";
        }
    }

    inline T checkRealAux(InstructionIT it, T val)
    {
        if (TRACE >= 6) return val;

        if (TRACE >= 1) {
            if (std::fpclassify(val) == FP_SUBNORMAL) {
                fRealStats[FP_SUBNORMAL]++;
            }
        }

        if (TRACE >= 2) {
            if (std::isnan(val)) {
                fRealStats[FP_NAN]++;
            } else if (std::isinf(val)) {
                fRealStats[FP_INFINITE]++;
            }
        }

        if (TRACE >= 4) {
            if (std::isnan(val)) {
                std::cout << "-------- Interpreter 'Nan' trace start --------" << std::endl;
                traceInstruction(it);
                fTraceContext.write(&std::cout);
                std::cout << "-------- Interpreter 'Nan' trace end --------\n\n";
                // Fails at first error...
                if (TRACE == 4) {
                    throw faustexception("Interpreter exit\n");
                }
            } else if (std::isinf(val)) {
                std::cout << "-------- Interpreter 'Inf' trace start --------" << std::endl;
                traceInstruction(it);
                fTraceContext.write(&std::cout);
                std::cout << "-------- Interpreter 'Inf' trace end --------\n\n";
                // Fails at first error...
                if (TRACE == 4) {
                    throw faustexception("Interpreter exit\n");
                }
            }
        }
        return val;
    }

    inline int assertAudioBuffer(InstructionIT it, int index)
    {
        if (TRACE >= 6) return index;

        if (TRACE >= 4 && ((index < 0) || (index >= fIntHeap[fFactory->fCountOffset]))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            std::cout << "assertAudioBuffer : count " << fIntHeap[fFactory->fCountOffset];
            std::cout << " index " << index << std::endl;
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            if (TRACE == 4) {
                throw faustexception("Interpreter exit\n");
            }
        }
        return index;
    }

    inline int assertIntHeap(InstructionIT it, int index, int size = -1)
    {
        if (TRACE >= 4 &&
            ((index < 0) || (index >= fFactory->fIntHeapSize) || (size > 0 && (index >= ((*it)->fOffset1 + size))))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            if (size > 0) {
                std::cout << "assertIntHeap array: fIntHeapSize ";
                std::cout << fFactory->fIntHeapSize << " index " << (index - (*it)->fOffset1);
                std::cout << " size " << size;
                std::cout << " name " << (*it)->fName << std::endl;
            } else {
                std::cout << "assertIntHeap scalar: fIntHeapSize ";
                std::cout << fFactory->fIntHeapSize << " index " << index;
                std::cout << " name " << (*it)->fName << std::endl;
            }
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            if (TRACE == 4 || TRACE == 7) {
                throw faustexception("Interpreter exit\n");
            }
        }
        return index;
    }

    inline int assertRealHeap(InstructionIT it, int index, int size = -1)
    {
        if (TRACE >= 4 &&
            ((index < 0) || (index >= fFactory->fRealHeapSize) || (size > 0 && (index >= ((*it)->fOffset1 + size))))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            if (size > 0) {
                std::cout << "assertRealHeap array: fIntHeapSize ";
                std::cout << fFactory->fRealHeapSize << " index " << (index - (*it)->fOffset1);
                std::cout << " size " << size;
                std::cout << " name " << (*it)->fName << std::endl;
            } else {
                std::cout << "assertRealHeap scalar: fIntHeapSize ";
                std::cout << fFactory->fRealHeapSize << " index " << index;
                std::cout << " name " << (*it)->fName << std::endl;
            }
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            if (TRACE == 4 || TRACE == 7) {
                throw faustexception("Interpreter exit\n");
            }
        }
        return index;
    }

    inline int assertSoundHeap(InstructionIT it, int index, int size = -1)
    {
        if (TRACE >= 4 && ((index < 0) || (index >= fFactory->fSoundHeapSize) || (size > 0 && index >= size))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            std::cout << "assertSoundHeap : fSoundHeapSize "
                      << fFactory->fSoundHeapSize << " index " << index
                      << " size " << size << std::endl;
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            if (TRACE == 4 || TRACE == 7) {
                throw faustexception("Interpreter exit\n");
            }
        }
        return index;
    }

    inline int assertLoadIntHeap(InstructionIT it, int index, int size = -1)
    {
        if ((TRACE >= 4) &&
            ((index < 0)
             || (index >= fFactory->fIntHeapSize)
             || (size > 0 && (index >= ((*it)->fOffset1 + size)))
             || (fIntHeap[index] == DUMMY_INT))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            if (size > 0) {
                std::cout << "assertLoadIntHeap array: fIntHeapSize ";
                std::cout << fFactory->fIntHeapSize << " index " << (index - (*it)->fOffset1);
                std::cout << " size " << size;
                std::cout << " value " << fIntHeap[index];
                std::cout << " name " << (*it)->fName << std::endl;
            } else {
                std::cout << "assertLoadIntHeap scalar: fIntHeapSize ";
                std::cout << fFactory->fIntHeapSize << " index " << index;
                std::cout << " name " << (*it)->fName << std::endl;
            }
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            if (TRACE == 4 || TRACE == 7) {
                throw faustexception("Interpreter exit\n");
            }
        }
        return index;
    }

    inline int assertLoadRealHeap(InstructionIT it, int index, int size = -1)
    {
        if ((TRACE >= 4) &&
            ((index < 0)
             || (index >= fFactory->fRealHeapSize)
             || (size > 0 && (index >= ((*it)->fOffset1 + size)))
             || (fRealHeap[index] == T(DUMMY_REAL)))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            if (size > 0) {
                std::cout << "assertLoadRealHeap array: fIntHeapSize ";
                std::cout << fFactory->fRealHeapSize << " index " << (index - (*it)->fOffset1);
                std::cout << " size " << size;
                std::cout << " value " << fRealHeap[index];
                std::cout << " name " << (*it)->fName << std::endl;
            } else {
                std::cout << "assertLoadRealHeap scalar: fIntHeapSize ";
                std::cout << fFactory->fRealHeapSize << " index " << index;
                std::cout << " name " << (*it)->fName << std::endl;
            }
            fTraceContext.write(&std::cout);
            std::cout << "-------- Interpreter crash trace end --------\n\n";
            if (TRACE == 4 || TRACE == 7) {
                throw faustexception("Interpreter exit\n");
            }
        }
        return index;
    }
    
    inline void assertIndex(InstructionIT it, int index, int size = -1)
    {
        if ((TRACE >= 4) && ((index < 0) || (index >= size))) {
            std::cout << "-------- Interpreter crash trace start --------" << std::endl;
            std::cout << "index " << index << " size " << size << std::endl;
            traceInstruction(it);
            fTraceContext.write(&std::cout);
            throw faustexception("Interpreter exit\n");
        }
        if (TRACE == 4 || TRACE == 7) {
            throw faustexception("Interpreter exit\n");
        }
    }

    inline T checkReal(InstructionIT it, T val) { return (TRACE > 0) ? checkRealAux(it, val) : val; }

#define pushInt(val) (int_stack[int_stack_index++] = val)
#define popInt() (int_stack[--int_stack_index])

#define pushReal(it, val) (real_stack[real_stack_index++] = checkReal(it, val))
#define popReal(it) checkReal(it, real_stack[--real_stack_index])

#define pushSound(val) (sound_stack[sound_stack_index++] = val)
#define popSound() (sound_stack[--sound_stack_index])

#define pushAddr_(addr) (address_stack[addr_stack_index++] = addr)
#define popAddr_() (address_stack[--addr_stack_index])

    virtual void ExecuteBuildUserInterface(FIRUserInterfaceBlockInstruction<T>* block, UITemplate* glue)
    {
        for (auto& it : block->fInstructions) {
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

    virtual void ExecuteBlock(FBCBlockInstruction<T>* block, bool compile = false)
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
            &&do_kDivInt, &&do_kRemReal, &&do_kRemInt, &&do_kLshInt, &&do_kRshInt, &&do_kGTInt, &&do_kLTInt,
            &&do_kGEInt, &&do_kLEInt, &&do_kEQInt, &&do_kNEInt, &&do_kGTReal, &&do_kLTReal, &&do_kGEReal, &&do_kLEReal,
            &&do_kEQReal, &&do_kNEReal, &&do_kANDInt, &&do_kORInt, &&do_kXORInt,

            // Standard math (heap OP heap)
            &&do_kAddRealHeap, &&do_kAddIntHeap, &&do_kSubRealHeap, &&do_kSubIntHeap, &&do_kMultRealHeap,
            &&do_kMultIntHeap, &&do_kDivRealHeap, &&do_kDivIntHeap, &&do_kRemRealHeap, &&do_kRemIntHeap,
            &&do_kLshIntHeap, &&do_kRshIntHeap, &&do_kGTIntHeap, &&do_kLTIntHeap, &&do_kGEIntHeap, &&do_kLEIntHeap,
            &&do_kEQIntHeap, &&do_kNEIntHeap, &&do_kGTRealHeap, &&do_kLTRealHeap, &&do_kGERealHeap, &&do_kLERealHeap,
            &&do_kEQRealHeap, &&do_kNERealHeap, &&do_kANDIntHeap, &&do_kORIntHeap, &&do_kXORIntHeap,

            // Standard math (heap OP stack)
            &&do_kAddRealStack, &&do_kAddIntStack, &&do_kSubRealStack, &&do_kSubIntStack, &&do_kMultRealStack,
            &&do_kMultIntStack, &&do_kDivRealStack, &&do_kDivIntStack, &&do_kRemRealStack, &&do_kRemIntStack,
            &&do_kLshIntStack, &&do_kRshIntStack, &&do_kGTIntStack, &&do_kLTIntStack, &&do_kGEIntStack,
            &&do_kLEIntStack, &&do_kEQIntStack, &&do_kNEIntStack, &&do_kGTRealStack, &&do_kLTRealStack,
            &&do_kGERealStack, &&do_kLERealStack, &&do_kEQRealStack, &&do_kNERealStack, &&do_kANDIntStack,
            &&do_kORIntStack, &&do_kXORIntStack,

            // Standard math (value OP stack)
            &&do_kAddRealStackValue, &&do_kAddIntStackValue, &&do_kSubRealStackValue, &&do_kSubIntStackValue,
            &&do_kMultRealStackValue, &&do_kMultIntStackValue, &&do_kDivRealStackValue, &&do_kDivIntStackValue,
            &&do_kRemRealStackValue, &&do_kRemIntStackValue, &&do_kLshIntStackValue, &&do_kRshIntStackValue,
            &&do_kGTIntStackValue, &&do_kLTIntStackValue, &&do_kGEIntStackValue, &&do_kLEIntStackValue,
            &&do_kEQIntStackValue, &&do_kNEIntStackValue, &&do_kGTRealStackValue, &&do_kLTRealStackValue,
            &&do_kGERealStackValue, &&do_kLERealStackValue, &&do_kEQRealStackValue, &&do_kNERealStackValue,
            &&do_kANDIntStackValue, &&do_kORIntStackValue, &&do_kXORIntStackValue,

            // Standard math (value OP heap)
            &&do_kAddRealValue, &&do_kAddIntValue, &&do_kSubRealValue, &&do_kSubIntValue, &&do_kMultRealValue,
            &&do_kMultIntValue, &&do_kDivRealValue, &&do_kDivIntValue, &&do_kRemRealValue, &&do_kRemIntValue,
            &&do_kLshIntValue, &&do_kRshIntValue, &&do_kGTIntValue, &&do_kLTIntValue, &&do_kGEIntValue,
            &&do_kLEIntValue, &&do_kEQIntValue, &&do_kNEIntValue, &&do_kGTRealValue, &&do_kLTRealValue,
            &&do_kGERealValue, &&do_kLERealValue, &&do_kEQRealValue, &&do_kNERealValue, &&do_kANDIntValue,
            &&do_kORIntValue, &&do_kXORIntValue,

            // Standard math (value OP heap) : non commutative operations
            &&do_kSubRealValueInvert, &&do_kSubIntValueInvert, &&do_kDivRealValueInvert, &&do_kDivIntValueInvert,
            &&do_kRemRealValueInvert, &&do_kRemIntValueInvert, &&do_kLshIntValueInvert, &&do_kRshIntValueInvert,
            &&do_kGTIntValueInvert, &&do_kLTIntValueInvert, &&do_kGEIntValueInvert, &&do_kLEIntValueInvert,
            &&do_kGTRealValueInvert, &&do_kLTRealValueInvert, &&do_kGERealValueInvert, &&do_kLERealValueInvert,

            // Extended unary math
            &&do_kAbs, &&do_kAbsf, &&do_kAcosf, &&do_kAcoshf, &&do_kAsinf, &&do_kAsinhf, &&do_kAtanf, &&do_kAtanhf, &&do_kCeilf,
            &&do_kCosf, &&do_kCoshf,
            &&do_kExpf, &&do_kFloorf, &&do_kLogf, &&do_kLog10f, &&do_kRintf, &&do_kRoundf, &&do_kSinf, &&do_kSinhf, &&do_kSqrtf,
            &&do_kTanf, &&do_kTanhf,

            // Extended unary math (heap OP heap)
            &&do_kAbsHeap, &&do_kAbsfHeap, &&do_kAcosfHeap, &&do_kAcoshfHeap, &&do_kAsinfHeap, &&do_kAsinhfHeap, &&do_kAtanfHeap, &&do_kAtanhfHeap,
            &&do_kCeilfHeap,
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

        T             real_stack[512];
        int           int_stack[512];
        Soundfile*    sound_stack[512];
        InstructionIT address_stack[64];

#define dispatchFirstScal()                   \
    {                                         \
        goto *fDispatchTable[(*it)->fOpcode]; \
    }
#define dispatchNextScal()                    \
    {                                         \
        traceInstruction(it);                 \
        it++;                                 \
        goto *fDispatchTable[(*it)->fOpcode]; \
    }

#define dispatchBranch1Scal()                        \
    {                                                \
        it = (*it)->fBranch1->fInstructions.begin(); \
        dispatchFirstScal();                         \
    }
#define dispatchBranch2Scal()                        \
    {                                                \
        it = (*it)->fBranch2->fInstructions.begin(); \
        dispatchFirstScal();                         \
    }

#define pushBranch1Scal()                                  \
    {                                                      \
        pushAddr_((*it)->fBranch1->fInstructions.begin()); \
    }
#define pushBranch2Scal()                                  \
    {                                                      \
        pushAddr_((*it)->fBranch2->fInstructions.begin()); \
    }

#define dispatchReturnScal() \
    {                        \
        it = popAddr_();     \
        dispatchFirstScal(); \
    }
#define saveReturnScal()   \
    {                      \
        pushAddr_(it + 1); \
    }
#define emptyReturnScal() (addr_stack_index == 0)

        // Check block coherency
        block->check();

        InstructionIT it = block->fInstructions.begin();
        dispatchFirstScal();

    // Number operations
    do_kRealValue : {
        pushReal(it, (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kInt32Value : {
        pushInt((*it)->fIntValue);
        dispatchNextScal();
    }

    // Memory operations
    do_kLoadReal : {
        if (TRACE > 0) {
            pushReal(it, fRealHeap[assertLoadRealHeap(it, (*it)->fOffset1)]);
        } else {
            pushReal(it, fRealHeap[(*it)->fOffset1]);
        }
        dispatchNextScal();
    }

    do_kLoadInt : {
        if (TRACE > 0) {
            pushInt(fIntHeap[assertLoadIntHeap(it, (*it)->fOffset1)]);
        } else {
            pushInt(fIntHeap[(*it)->fOffset1]);
        }
        dispatchNextScal();
    }

    do_kLoadSound : {
        if (TRACE > 0) {
            pushSound(fSoundHeap[assertSoundHeap(it, (*it)->fOffset1)]);
        } else {
            pushSound(fSoundHeap[(*it)->fOffset1]);
        }
        dispatchNextScal();
    }

    do_kLoadSoundField : {
        /*
        if (TRACE > 0) {
            pushSound(fSoundHeap[assertSoundHeap(it, (*it)->fOffset1)]);
        } else {
            pushSound(fSoundHeap[(*it)->fOffset1]);
        }
        dispatchNextScal();
        */
    }

    do_kStoreReal : {
        if (TRACE > 0) {
            fRealHeap[assertRealHeap(it, (*it)->fOffset1)] = popReal(it);
        } else {
            fRealHeap[(*it)->fOffset1] = popReal(it);
        }
        dispatchNextScal();
    }

    do_kStoreInt : {
        if (TRACE > 0) {
            fIntHeap[assertIntHeap(it, (*it)->fOffset1)] = popInt();
        } else {
            fIntHeap[(*it)->fOffset1] = popInt();
        }
        dispatchNextScal();
    }

    do_kStoreSound : {
        /*
        if (TRACE > 0) {
            fSoundHeap[assertSoundHeap(it, (*it)->fOffset1)] = popSound();
        } else {
            fSoundHeap[(*it)->fOffset1] = popSound();
        }
        */
        dispatchNextScal();
    }

    // Directly store a value
    do_kStoreRealValue : {
        if (TRACE > 0) {
            fRealHeap[assertRealHeap(it, (*it)->fOffset1)] = (*it)->fRealValue;
        } else {
            fRealHeap[(*it)->fOffset1] = (*it)->fRealValue;
        }
        dispatchNextScal();
    }

    do_kStoreIntValue : {
        if (TRACE > 0) {
            fIntHeap[assertIntHeap(it, (*it)->fOffset1)] = (*it)->fIntValue;
        } else {
            fIntHeap[(*it)->fOffset1] = (*it)->fIntValue;
        }
        dispatchNextScal();
    }

    do_kLoadIndexedReal : {
        int offset = popInt();
        if (TRACE > 0) {
            // DEBUG
            // assertIndex(it, offset, (*it)->fOffset2);
            pushReal(it, fRealHeap[assertLoadRealHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)]);
        } else {
            pushReal(it, fRealHeap[(*it)->fOffset1 + offset]);
        }
        dispatchNextScal();
    }

    do_kLoadIndexedInt : {
        int offset = popInt();
        if (TRACE > 0) {
            // DEBUG
            // assertIndex(it, offset, (*it)->fOffset2);
            pushInt(fIntHeap[assertLoadIntHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)]);
        } else {
            pushInt(fIntHeap[(*it)->fOffset1 + offset]);
        }
        dispatchNextScal();
    }

    do_kStoreIndexedReal : {
        int offset = popInt();
        if (TRACE > 0) {
            // DEBUG
            // assertIndex(it, offset, (*it)->fOffset2);
            fRealHeap[assertRealHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)] = popReal(it);
        } else {
            fRealHeap[(*it)->fOffset1 + offset] = popReal(it);
        }
        dispatchNextScal();
    }

    do_kStoreIndexedInt : {
        int offset = popInt();
        if (TRACE > 0) {
            // DEBUG
            // assertIndex(it, offset, (*it)->fOffset2);
            fIntHeap[assertIntHeap(it, (*it)->fOffset1 + offset, (*it)->fOffset2)] = popInt();
        } else {
            fIntHeap[(*it)->fOffset1 + offset] = popInt();
        }
        dispatchNextScal();
    }

    do_kBlockStoreReal : {
        FIRBlockStoreRealInstruction<T>* inst = static_cast<FIRBlockStoreRealInstruction<T>*>(*it);
        assertInterp(inst);
        for (int i = 0; i < inst->fOffset2; i++) {
            fRealHeap[inst->fOffset1 + i] = inst->fNumTable[i];
        }
        dispatchNextScal();
    }

    do_kBlockStoreInt : {
        FIRBlockStoreIntInstruction<T>* inst = static_cast<FIRBlockStoreIntInstruction<T>*>(*it);
        assertInterp(inst);
        for (int i = 0; i < inst->fOffset2; i++) {
            fIntHeap[inst->fOffset1 + i] = inst->fNumTable[i];
        }
        dispatchNextScal();
    }

    do_kMoveReal : {
        fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset2];
        dispatchNextScal();
    }

    do_kMoveInt : {
        fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset2];
        dispatchNextScal();
    }

    do_kPairMoveReal : {
        fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset1 - 1];
        fRealHeap[(*it)->fOffset2] = fRealHeap[(*it)->fOffset2 - 1];
        dispatchNextScal();
    }

    do_kPairMoveInt : {
        fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset1 - 1];
        fIntHeap[(*it)->fOffset2] = fIntHeap[(*it)->fOffset2 - 1];
        dispatchNextScal();
    }

    do_kBlockPairMoveReal : {
        for (int i = (*it)->fOffset1; i < (*it)->fOffset2; i += 2) {
            fRealHeap[i + 1] = fRealHeap[i];
        }
        dispatchNextScal();
    }

    do_kBlockPairMoveInt : {
        for (int i = (*it)->fOffset1; i < (*it)->fOffset2; i += 2) {
            fIntHeap[i + 1] = fIntHeap[i];
        }
        dispatchNextScal();
    }

    do_kBlockShiftReal : {
        for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
            fRealHeap[i] = fRealHeap[i - 1];
        }
        dispatchNextScal();
    }

    do_kBlockShiftInt : {
        for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
            fIntHeap[i] = fIntHeap[i - 1];
        }
        dispatchNextScal();
    }

    // Input/output access
    do_kLoadInput : {
        if (TRACE > 0) {
            pushReal(it, fInputs[(*it)->fOffset1][assertAudioBuffer(it, popInt())]);
        } else {
            /*
            int index = popInt();
            pushReal(it, fInputs[(*it)->fOffset1][index]);
            std::cout << "do_kLoadInput " << index << std::endl;
            */
            pushReal(it, fInputs[(*it)->fOffset1][popInt()]);
        }
        dispatchNextScal();
    }

    do_kStoreOutput : {
        if (TRACE > 0) {
            fOutputs[(*it)->fOffset1][assertAudioBuffer(it, popInt())] = popReal(it);
        } else {
            /*
            int index = popInt();
            std::cout << "do_kStoreOutput " << index << std::endl;
            fOutputs[(*it)->fOffset1][index] = popReal(it);
            */
            fOutputs[(*it)->fOffset1][popInt()] = popReal(it);
        }
        dispatchNextScal();
    }

    // Cast operations
    do_kCastReal : {
        pushReal(it, T(popInt()));
        dispatchNextScal();
    }

    do_kCastRealHeap : {
        pushReal(it, T(fIntHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kCastInt : {
        pushInt(int(popReal(it)));
        dispatchNextScal();
    }

    do_kCastIntHeap : {
        pushInt(int(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    // Bitcast operations
    do_kBitcastInt : {
        T   v1 = popReal(it);
        int v2 = *reinterpret_cast<int*>(&v1);
        pushInt(v2);
        dispatchNextScal();
    }

    do_kBitcastReal : {
        int v1 = popInt();
        T   v2 = *reinterpret_cast<T*>(&v1);
        pushReal(it, v2);
        dispatchNextScal();
    }

        //-------------------------------------------------------
        // Standard math operations : 'stack' OP 'stack' version
        //-------------------------------------------------------

    do_kAddReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushReal(it, v1 + v2);
        dispatchNextScal();
    }

    do_kAddInt : {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            int res;
            if (__builtin_sadd_overflow(v1, v2, &res)) {
                warningOverflow(it);
            }
            pushInt(res);
        } else {
            pushInt(v1 + v2);
        }
        dispatchNextScal();
    }

    do_kSubReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushReal(it, v1 - v2);
        dispatchNextScal();
    }

    do_kSubInt : {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            int res;
            if (__builtin_ssub_overflow(v1, v2, &res)) {
                warningOverflow(it);
            }
            pushInt(res);
        } else {
            pushInt(v1 - v2);
        }
        dispatchNextScal();
    }

    do_kMultReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushReal(it, v1 * v2);
        dispatchNextScal();
    }

    do_kMultInt : {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            int res;
            if (__builtin_smul_overflow(v1, v2, &res)) {
                warningOverflow(it);
            }
            pushInt(res);
        } else {
            pushInt(v1 * v2);
        }
        dispatchNextScal();
    }

    do_kDivReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        if (TRACE > 0) {
            checkDivZero(it, v2);
        }
        pushReal(it, v1 / v2);
        dispatchNextScal();
    }

    do_kDivInt : {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            checkDivZero(it, v2);
        }
        pushInt(v1 / v2);
        dispatchNextScal();
    }

    do_kRemReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        if (TRACE > 0) {
            checkDivZero(it, v2);
        }
        pushReal(it, std::remainder(v1, v2));
        dispatchNextScal();
    }

    do_kRemInt : {
        int v1 = popInt();
        int v2 = popInt();
        if (TRACE > 0) {
            checkDivZero(it, v2);
        }
        pushInt(v1 % v2);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 << v2);
        dispatchNextScal();
    }

    do_kRshInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 >> v2);
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 > v2);
        dispatchNextScal();
    }

    do_kLTInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 < v2);
        dispatchNextScal();
    }

    do_kGEInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 >= v2);
        dispatchNextScal();
    }

    do_kLEInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 <= v2);
        dispatchNextScal();
    }

    do_kEQInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 == v2);
        dispatchNextScal();
    }

    do_kNEInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 != v2);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushInt(v1 > v2);
        dispatchNextScal();
    }

    do_kLTReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushInt(v1 < v2);
        dispatchNextScal();
    }

    do_kGEReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushInt(v1 >= v2);
        dispatchNextScal();
    }

    do_kLEReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushInt(v1 <= v2);
        dispatchNextScal();
    }

    do_kEQReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushInt(v1 == v2);
        dispatchNextScal();
    }

    do_kNEReal : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushInt(v1 != v2);
        dispatchNextScal();
    }

    // Logical operations
    do_kANDInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 & v2);
        dispatchNextScal();
    }

    do_kORInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 | v2);
        dispatchNextScal();
    }

    do_kXORInt : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(v1 ^ v2);
        dispatchNextScal();
    }

        //-----------------------------------------------------
        // Standard math operations : 'heap' OP 'heap' version
        //-----------------------------------------------------

    do_kAddRealHeap : {
        pushReal(it, fRealHeap[(*it)->fOffset1] + fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kAddIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] + fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kSubRealHeap : {
        pushReal(it, fRealHeap[(*it)->fOffset1] - fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kSubIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] - fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kMultRealHeap : {
        pushReal(it, fRealHeap[(*it)->fOffset1] * fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kMultIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] * fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kDivRealHeap : {
        pushReal(it, fRealHeap[(*it)->fOffset1] / fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kDivIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] / fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kRemRealHeap : {
        pushReal(it, std::remainder(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kRemIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] % fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] << fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kRshIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] >> fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] > fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kLTIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] < fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kGEIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] >= fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kLEIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] <= fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kEQIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] == fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kNEIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] != fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTRealHeap : {
        pushInt(fRealHeap[(*it)->fOffset1] > fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kLTRealHeap : {
        pushInt(fRealHeap[(*it)->fOffset1] < fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kGERealHeap : {
        pushInt(fRealHeap[(*it)->fOffset1] >= fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kLERealHeap : {
        pushInt(fRealHeap[(*it)->fOffset1] <= fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kEQRealHeap : {
        pushInt(fRealHeap[(*it)->fOffset1] == fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kNERealHeap : {
        pushInt(fRealHeap[(*it)->fOffset1] != fRealHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    // Logical operations
    do_kANDIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] & fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kORIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] | fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

    do_kXORIntHeap : {
        pushInt(fIntHeap[(*it)->fOffset1] ^ fIntHeap[(*it)->fOffset2]);
        dispatchNextScal();
    }

        //------------------------------------------------------
        // Standard math operations : 'stack' OP 'heap' version
        //------------------------------------------------------

    do_kAddRealStack : {
        T v1 = popReal(it);
        pushReal(it, fRealHeap[(*it)->fOffset1] + v1);
        dispatchNextScal();
    }

    do_kAddIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] + v1);
        dispatchNextScal();
    }

    do_kSubRealStack : {
        T v1 = popReal(it);
        pushReal(it, fRealHeap[(*it)->fOffset1] - v1);
        dispatchNextScal();
    }

    do_kSubIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] - v1);
        dispatchNextScal();
    }

    do_kMultRealStack : {
        T v1 = popReal(it);
        pushReal(it, fRealHeap[(*it)->fOffset1] * v1);
        dispatchNextScal();
    }

    do_kMultIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] * v1);
        dispatchNextScal();
    }

    do_kDivRealStack : {
        T v1 = popReal(it);
        pushReal(it, fRealHeap[(*it)->fOffset1] / v1);
        dispatchNextScal();
    }

    do_kDivIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] / v1);
        dispatchNextScal();
    }

    do_kRemRealStack : {
        T v1 = popReal(it);
        pushReal(it, std::remainder(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kRemIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] % v1);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] << v1);
        dispatchNextScal();
    }

    do_kRshIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] >> v1);
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] > v1);
        dispatchNextScal();
    }

    do_kLTIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] < v1);
        dispatchNextScal();
    }

    do_kGEIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] >= v1);
        dispatchNextScal();
    }

    do_kLEIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] <= v1);
        dispatchNextScal();
    }

    do_kEQIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] == v1);
        dispatchNextScal();
    }

    do_kNEIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] != v1);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTRealStack : {
        T v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] > v1);
        dispatchNextScal();
    }

    do_kLTRealStack : {
        T v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] < v1);
        dispatchNextScal();
    }

    do_kGERealStack : {
        T v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] >= v1);
        dispatchNextScal();
    }

    do_kLERealStack : {
        T v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] <= v1);
        dispatchNextScal();
    }

    do_kEQRealStack : {
        T v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] == v1);
        dispatchNextScal();
    }

    do_kNERealStack : {
        T v1 = popReal(it);
        pushInt(fRealHeap[(*it)->fOffset1] != v1);
        dispatchNextScal();
    }

    // Logical operations
    do_kANDIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] & v1);
        dispatchNextScal();
    }

    do_kORIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] | v1);
        dispatchNextScal();
    }

    do_kXORIntStack : {
        int v1 = popInt();
        pushInt(fIntHeap[(*it)->fOffset1] ^ v1);
        dispatchNextScal();
    }

        //-------------------------------------------------------
        // Standard math operations : 'stack' OP 'value' version
        //-------------------------------------------------------

    do_kAddRealStackValue : {
        T v1 = popReal(it);
        pushReal(it, (*it)->fRealValue + v1);
        dispatchNextScal();
    }

    do_kAddIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue + v1);
        dispatchNextScal();
    }

    do_kSubRealStackValue : {
        T v1 = popReal(it);
        pushReal(it, (*it)->fRealValue - v1);
        dispatchNextScal();
    }

    do_kSubIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue - v1);
        dispatchNextScal();
    }

    do_kMultRealStackValue : {
        T v1 = popReal(it);
        pushReal(it, (*it)->fRealValue * v1);
        dispatchNextScal();
    }

    do_kMultIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue * v1);
        dispatchNextScal();
    }

    do_kDivRealStackValue : {
        T v1 = popReal(it);
        pushReal(it, (*it)->fRealValue / v1);
        dispatchNextScal();
    }

    do_kDivIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue / v1);
        dispatchNextScal();
    }

    do_kRemRealStackValue : {
        T v1 = popReal(it);
        pushReal(it, std::remainder((*it)->fRealValue, v1));
        dispatchNextScal();
    }

    do_kRemIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue % v1);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue << v1);
        dispatchNextScal();
    }

    do_kRshIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue >> v1);
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue > v1);
        dispatchNextScal();
    }

    do_kLTIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue < v1);
        dispatchNextScal();
    }

    do_kGEIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue >= v1);
        dispatchNextScal();
    }

    do_kLEIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue <= v1);
        dispatchNextScal();
    }

    do_kEQIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue == v1);
        dispatchNextScal();
    }

    do_kNEIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue != v1);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTRealStackValue : {
        T v1 = popReal(it);
        pushInt((*it)->fRealValue > v1);
        dispatchNextScal();
    }

    do_kLTRealStackValue : {
        T v1 = popReal(it);
        pushInt((*it)->fRealValue < v1);
        dispatchNextScal();
    }

    do_kGERealStackValue : {
        T v1 = popReal(it);
        pushInt((*it)->fRealValue >= v1);
        dispatchNextScal();
    }

    do_kLERealStackValue : {
        T v1 = popReal(it);
        pushInt((*it)->fRealValue <= v1);
        dispatchNextScal();
    }

    do_kEQRealStackValue : {
        T v1 = popReal(it);
        pushInt((*it)->fRealValue == v1);
        dispatchNextScal();
    }

    do_kNERealStackValue : {
        T v1 = popReal(it);
        pushInt((*it)->fRealValue != v1);
        dispatchNextScal();
    }

    // Logical operations
    do_kANDIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue & v1);
        dispatchNextScal();
    }

    do_kORIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue | v1);
        dispatchNextScal();
    }

    do_kXORIntStackValue : {
        int v1 = popInt();
        pushInt((*it)->fIntValue ^ v1);
        dispatchNextScal();
    }

        //------------------------------------------------------
        // Standard math operations : 'value' OP 'heap' version
        //------------------------------------------------------

    do_kAddRealValue : {
        pushReal(it, (*it)->fRealValue + fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kAddIntValue : {
        pushInt((*it)->fIntValue + fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kSubRealValue : {
        pushReal(it, (*it)->fRealValue - fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kSubIntValue : {
        pushInt((*it)->fIntValue - fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kMultRealValue : {
        pushReal(it, (*it)->fRealValue * fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kMultIntValue : {
        pushInt((*it)->fIntValue * fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kDivRealValue : {
        pushReal(it, (*it)->fRealValue / fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kDivIntValue : {
        pushInt((*it)->fIntValue / fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kRemRealValue : {
        pushReal(it, std::remainder((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kRemIntValue : {
        pushInt((*it)->fIntValue % fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshIntValue : {
        pushInt((*it)->fIntValue << fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kRshIntValue : {
        pushInt((*it)->fIntValue >> fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTIntValue : {
        pushInt((*it)->fIntValue > fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kLTIntValue : {
        pushInt((*it)->fIntValue < fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kGEIntValue : {
        pushInt((*it)->fIntValue >= fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kLEIntValue : {
        pushInt((*it)->fIntValue <= fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kEQIntValue : {
        pushInt((*it)->fIntValue == fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kNEIntValue : {
        pushInt((*it)->fIntValue != fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTRealValue : {
        pushInt((*it)->fRealValue > fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kLTRealValue : {
        pushInt((*it)->fRealValue < fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kGERealValue : {
        pushInt((*it)->fRealValue >= fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kLERealValue : {
        pushInt((*it)->fRealValue <= fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kEQRealValue : {
        pushInt((*it)->fRealValue == fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kNERealValue : {
        pushInt((*it)->fRealValue != fRealHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    // Logical operations
    do_kANDIntValue : {
        pushInt((*it)->fIntValue & fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kORIntValue : {
        pushInt((*it)->fIntValue | fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

    do_kXORIntValue : {
        pushInt((*it)->fIntValue ^ fIntHeap[(*it)->fOffset1]);
        dispatchNextScal();
    }

        //----------------------------------------------------
        // Standard math operations : Value inverted version
        // (non commutative operations)
        //----------------------------------------------------

    do_kSubRealValueInvert : {
        pushReal(it, fRealHeap[(*it)->fOffset1] - (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kSubIntValueInvert : {
        pushInt(fIntHeap[(*it)->fOffset1] - (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kDivRealValueInvert : {
        pushReal(it, fRealHeap[(*it)->fOffset1] / (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kDivIntValueInvert : {
        pushInt(fIntHeap[(*it)->fOffset1] / (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kRemRealValueInvert : {
        pushReal(it, std::remainder(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
        dispatchNextScal();
    }

    do_kRemIntValueInvert : {
        pushInt(fIntHeap[(*it)->fOffset1] % (*it)->fIntValue);
        dispatchNextScal();
    }

    // Shift operation
    do_kLshIntValueInvert : {
        pushInt(fIntHeap[(*it)->fOffset1] << (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kRshIntValueInvert : {
        pushInt(fIntHeap[(*it)->fOffset1] >> (*it)->fIntValue);
        dispatchNextScal();
    }

    // Comparaison Int
    do_kGTIntValueInvert : {
        pushInt(fIntHeap[(*it)->fOffset1] > (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kLTIntValueInvert : {
        pushInt(fIntHeap[(*it)->fOffset1] < (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kGEIntValueInvert : {
        pushInt(fIntHeap[(*it)->fOffset1] >= (*it)->fIntValue);
        dispatchNextScal();
    }

    do_kLEIntValueInvert : {
        pushInt(fIntHeap[(*it)->fOffset1] <= (*it)->fIntValue);
        dispatchNextScal();
    }

    // Comparaison Real
    do_kGTRealValueInvert : {
        pushInt(fRealHeap[(*it)->fOffset1] > (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kLTRealValueInvert : {
        pushInt(fRealHeap[(*it)->fOffset1] < (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kGERealValueInvert : {
        pushInt(fRealHeap[(*it)->fOffset1] >= (*it)->fRealValue);
        dispatchNextScal();
    }

    do_kLERealValueInvert : {
        pushInt(fRealHeap[(*it)->fOffset1] <= (*it)->fRealValue);
        dispatchNextScal();
    }

        //---------------------
        // Extended unary math
        //---------------------

    do_kAbs : {
        int v = popInt();
        pushInt(std::abs(v));
        dispatchNextScal();
    }

    do_kAbsf : {
        T v = popReal(it);
        pushReal(it, std::fabs(v));
        dispatchNextScal();
    }

    do_kAcosf : {
        T v = popReal(it);
        pushReal(it, std::acos(v));
        dispatchNextScal();
    }
        
    do_kAcoshf : {
        T v = popReal(it);
        pushReal(it, std::acosh(v));
        dispatchNextScal();
    }

    do_kAsinf : {
        T v = popReal(it);
        pushReal(it, std::asin(v));
        dispatchNextScal();
    }
        
    do_kAsinhf : {
        T v = popReal(it);
        pushReal(it, std::asinh(v));
        dispatchNextScal();
    }

    do_kAtanf : {
        T v = popReal(it);
        pushReal(it, std::atan(v));
        dispatchNextScal();
    }
        
    do_kAtanhf : {
        T v = popReal(it);
        pushReal(it, std::atanh(v));
        dispatchNextScal();
    }

    do_kCeilf : {
        T v = popReal(it);
        pushReal(it, std::ceil(v));
        dispatchNextScal();
    }

    do_kCosf : {
        T v = popReal(it);
        pushReal(it, std::cos(v));
        dispatchNextScal();
    }

    do_kCoshf : {
        T v = popReal(it);
        pushReal(it, std::cosh(v));
        dispatchNextScal();
    }

    do_kExpf : {
        T v = popReal(it);
        pushReal(it, std::exp(v));
        dispatchNextScal();
    }

    do_kFloorf : {
        T v = popReal(it);
        pushReal(it, std::floor(v));
        dispatchNextScal();
    }

    do_kLogf : {
        T v = popReal(it);
        pushReal(it, std::log(v));
        dispatchNextScal();
    }

    do_kLog10f : {
        T v = popReal(it);
        pushReal(it, std::log10(v));
        dispatchNextScal();
    }
        
    do_kRintf : {
        T v = popReal(it);
        pushReal(it, std::rint(v));
        dispatchNextScal();
    }

    do_kRoundf : {
        T v = popReal(it);
        pushReal(it, std::round(v));
        dispatchNextScal();
    }

    do_kSinf : {
        T v = popReal(it);
        pushReal(it, std::sin(v));
        dispatchNextScal();
    }

    do_kSinhf : {
        T v = popReal(it);
        pushReal(it, std::sinh(v));
        dispatchNextScal();
    }

    do_kSqrtf : {
        T v = popReal(it);
        pushReal(it, std::sqrt(v));
        dispatchNextScal();
    }

    do_kTanf : {
        T v = popReal(it);
        pushReal(it, std::tan(v));
        dispatchNextScal();
    }

    do_kTanhf : {
        T v = popReal(it);
        pushReal(it, std::tanh(v));
        dispatchNextScal();
    }

        //------------------------------------
        // Extended unary math (heap version)
        ///-----------------------------------

    do_kAbsHeap : {
        pushInt(std::abs(fIntHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kAbsfHeap : {
        pushReal(it, std::fabs(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kAcosfHeap : {
        pushReal(it, std::acos(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }
        
    do_kAcoshfHeap : {
        pushReal(it, std::acosh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kAsinfHeap : {
        pushReal(it, std::asin(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }
        
    do_kAsinhfHeap : {
        pushReal(it, std::asinh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kAtanfHeap : {
        pushReal(it, std::atan(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }
        
    do_kAtanhfHeap : {
        pushReal(it, std::atanh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kCeilfHeap : {
        pushReal(it, std::ceil(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kCosfHeap : {
        pushReal(it, std::cos(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kCoshfHeap : {
        pushReal(it, std::cosh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kExpfHeap : {
        pushReal(it, std::exp(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kFloorfHeap : {
        pushReal(it, std::floor(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kLogfHeap : {
        pushReal(it, std::log(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kLog10fHeap : {
        pushReal(it, std::log10(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }
        
    do_kRintfHeap : {
        pushReal(it, std::rint(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }
   
    do_kRoundfHeap : {
        pushReal(it, std::round(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kSinfHeap : {
        pushReal(it, std::sin(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kSinhfHeap : {
        pushReal(it, std::sinh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kSqrtfHeap : {
        pushReal(it, std::sqrt(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kTanfHeap : {
        pushReal(it, std::tan(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kTanhfHeap : {
        pushReal(it, std::tanh(fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

        //----------------------
        // Extended binary math
        //----------------------

    do_kAtan2f : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushReal(it, std::atan2(v1, v2));
        dispatchNextScal();
    }

    do_kFmodf : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushReal(it, std::fmod(v1, v2));
        dispatchNextScal();
    }

    do_kPowf : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushReal(it, std::pow(v1, v2));
        dispatchNextScal();
    }

    do_kMax : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(std::max(v1, v2));
        dispatchNextScal();
    }

    do_kMaxf : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushReal(it, std::max(v1, v2));
        dispatchNextScal();
    }

    do_kMin : {
        int v1 = popInt();
        int v2 = popInt();
        pushInt(std::min(v1, v2));
        dispatchNextScal();
    }

    do_kMinf : {
        T v1 = popReal(it);
        T v2 = popReal(it);
        pushReal(it, std::min(v1, v2));
        dispatchNextScal();
    }

        //-------------------------------------
        // Extended binary math (heap version)
        //-------------------------------------

    do_kAtan2fHeap : {
        pushReal(it, std::atan2(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kFmodfHeap : {
        pushReal(it, std::fmod(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kPowfHeap : {
        pushReal(it, std::pow(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kMaxHeap : {
        pushInt(std::max(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kMaxfHeap : {
        pushReal(it, std::max(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kMinHeap : {
        pushInt(std::min(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

    do_kMinfHeap : {
        pushReal(it, std::min(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
        dispatchNextScal();
    }

        //--------------------------------------
        // Extended binary math (stack version)
        //--------------------------------------

    do_kAtan2fStack : {
        T v1 = popReal(it);
        pushReal(it, std::atan2(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kFmodfStack : {
        T v1 = popReal(it);
        pushReal(it, std::fmod(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kPowfStack : {
        T v1 = popReal(it);
        pushReal(it, std::pow(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kMaxStack : {
        int v1 = popInt();
        pushInt(std::max(fIntHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kMaxfStack : {
        T v1 = popReal(it);
        pushReal(it, std::max(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kMinStack : {
        int v1 = popInt();
        pushInt(std::min(fIntHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

    do_kMinfStack : {
        T v1 = popReal(it);
        pushReal(it, std::min(fRealHeap[(*it)->fOffset1], v1));
        dispatchNextScal();
    }

        //--------------------------------------------
        // Extended binary math (stack/value version)
        //--------------------------------------------

    do_kAtan2fStackValue : {
        T v1 = popReal(it);
        pushReal(it, std::atan2((*it)->fRealValue, v1));
        dispatchNextScal();
    }

    do_kFmodfStackValue : {
        T v1 = popReal(it);
        pushReal(it, std::fmod((*it)->fRealValue, v1));
        dispatchNextScal();
    }

    do_kPowfStackValue : {
        T v1 = popReal(it);
        pushReal(it, std::pow((*it)->fRealValue, v1));
        dispatchNextScal();
    }

    do_kMaxStackValue : {
        int v1 = popInt();
        pushInt(std::max((*it)->fIntValue, v1));
        dispatchNextScal();
    }

    do_kMaxfStackValue : {
        T v1 = popReal(it);
        pushReal(it, std::max((*it)->fRealValue, v1));
        dispatchNextScal();
    }

    do_kMinStackValue : {
        int v1 = popInt();
        pushInt(std::min((*it)->fIntValue, v1));
        dispatchNextScal();
    }

    do_kMinfStackValue : {
        T v1 = popReal(it);
        pushReal(it, std::min((*it)->fRealValue, v1));
        dispatchNextScal();
    }

        //-------------------------------------
        // Extended binary math (Value version)
        //-------------------------------------

    do_kAtan2fValue : {
        pushReal(it, std::atan2((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kFmodfValue : {
        pushReal(it, std::fmod((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kPowfValue : {
        pushReal(it, std::pow((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kMaxValue : {
        pushInt(std::max((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kMaxfValue : {
        pushReal(it, std::max((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kMinValue : {
        pushInt(std::min((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

    do_kMinfValue : {
        pushReal(it, std::min((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
        dispatchNextScal();
    }

        //-------------------------------------------------------------------
        // Extended binary math (Value version) : non commutative operations
        //-------------------------------------------------------------------

    do_kAtan2fValueInvert : {
        pushReal(it, std::atan2(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
        dispatchNextScal();
    }

    do_kFmodfValueInvert : {
        pushReal(it, std::fmod(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
        dispatchNextScal();
    }

    do_kPowfValueInvert : {
        pushReal(it, std::pow(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
        dispatchNextScal();
    }

        //---------
        // Control
        //---------

    do_kReturn : {
        // Empty addr stack = end of computation
        if (emptyReturnScal()) {
            goto end;
        } else {
            dispatchReturnScal();
        }
    }

    do_kIf : {
        // Keep next instruction
        saveReturnScal();

        if (popInt()) {
            // Execute new block
            assertInterp((*it)->fBranch1);
            dispatchBranch1Scal();
            // No value (If)
        } else {
            // Execute new block
            assertInterp((*it)->fBranch2);
            dispatchBranch2Scal();
            // No value (If)
        }
    }

    do_kSelectReal : {
        // Keep next instruction
        saveReturnScal();

        if (popInt()) {
            // Execute new block
            assertInterp((*it)->fBranch1);
            dispatchBranch1Scal();
            // Real value
        } else {
            // Execute new block
            assertInterp((*it)->fBranch2);
            dispatchBranch2Scal();
            // Real value
        }
    }

    do_kSelectInt : {
        // Keep next instruction
        saveReturnScal();

        if (popInt()) {
            // Execute new block
            assertInterp((*it)->fBranch1);
            dispatchBranch1Scal();
            // Int value
        } else {
            // Execute new block
            assertInterp((*it)->fBranch2);
            dispatchBranch2Scal();
            // Int value
        }
    }

    do_kCondBranch : {
        // If condition is true, just branch back on the block beginning
        if (popInt()) {
            assertInterp((*it)->fBranch1);
            dispatchBranch1Scal();
        } else {
            // Just continue after 'loop block' (do the final 'return')
            dispatchNextScal();
        }
    }

    do_kLoop : {
        // Keep next instruction
        saveReturnScal();

        // Push branch2 (loop content)
        assertInterp((*it)->fBranch2);
        pushBranch2Scal();

        // And start branch1 loop variable declaration block
        assertInterp((*it)->fBranch1);
        dispatchBranch1Scal();
    }

    end:
        // Check stack coherency
        assertInterp(real_stack_index == 0 && int_stack_index == 0 && sound_stack_index == 0);
    }

   public:
    FBCInterpreter(interpreter_dsp_factory_aux<T, TRACE>* factory)
    {
        /*
        std::cout << "FBCInterpreter :"
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

        // std::cout << "==== FBCInterpreter ==== " << std::endl;
        // std::cout << "fRealHeapSize = " << fFactory->fRealHeapSize << std::endl;
        // std::cout << "fIntHeapSize = " << fFactory->fIntHeapSize << std::endl;

        // Initialise HEAP with special values to detect incorrect Load access
        for (int i = 0; i < fFactory->fRealHeapSize; i++) {
            fRealHeap[i] = T(DUMMY_REAL);
        }
        for (int i = 0; i < fFactory->fIntHeapSize; i++) {
            fIntHeap[i] = DUMMY_INT;
        }

        fRealStats[INTEGER_OVERFLOW] = 0;
        fRealStats[DIV_BY_ZERO]      = 0;
        fRealStats[FP_INFINITE]      = 0;
        fRealStats[FP_NAN]           = 0;
        fRealStats[FP_SUBNORMAL]     = 0;
    }

    virtual ~FBCInterpreter()
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
        if (TRACE > 0) {
            printStats();
        }
    }

    void dumpMemory(FBCBlockInstruction<T>* block, const std::string& name, const std::string& filename)
    {
        std::ofstream out(filename);
        out << "DSP name: " << name << std::endl;

        out << "REAL memory: " << fFactory->fRealHeapSize << "\n";
        for (int i = 0; i < fFactory->fRealHeapSize; i++) {
            out << "mem: " << i << " " << fRealHeap[i] << std::endl;
        }

        out << "INT memory: " << fFactory->fIntHeapSize << "\n";
        for (int i = 0; i < fFactory->fIntHeapSize; i++) {
            out << "mem: " << i << " " << fIntHeap[i] << std::endl;
        }
    }

    void setIntValue(int offset, int value) { fIntHeap[offset] = value; }
    int  getIntValue(int offset) { return fIntHeap[offset]; }

    virtual void setInput(int input, T* buffer) { fInputs[input] = buffer; }
    virtual void setOutput(int output, T* buffer) { fOutputs[output] = buffer; }
};

#endif
