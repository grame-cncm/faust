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

#include <string.h>
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include <map>

#include "faust/gui/CGlue.h"
#include "interpreter_bytecode.hh"
#include "exception.hh"

/*
 
 Trace mode: only check 'non-optimized' interpreter operations, since the code is not optimized in this case.
 
 1 : collect FP_SUBNORMAL only
 2 : collect FP_SUBNORMAL, FP_INFINITE and FP_NAN
 3 : collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW and DIV_BY_ZERO
 4 : collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, fails at first FP_INFINITE or FP_NAN
 5 : collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, continue after FP_INFINITE or FP_NAN
 
*/

#define INTEGER_OVERFLOW        -1
#define DIV_BY_ZERO             -2

template <class T, int TRACE>
struct interpreter_dsp_factory_aux;

// FIR bytecode interpreter
template <class T, int TRACE>
class FIRInterpreter  {
    
    protected:
    
        interpreter_dsp_factory_aux<T, TRACE>* fFactory;
    
        int* fIntHeap;
        T* fRealHeap;
    
        int fRealStackSize;
        int fIntStackSize;
    
        T** fInputs;
        T** fOutputs;
    
        std::map<int, long long> fRealStats;
    
        void printStats()
        {
            if (TRACE > 0) {
                std::cout << "-------------------------------"<< std::endl;
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
                std::cout << "-------------------------------"<< std::endl;
            }
        }
    
        inline void warning_overflow(InstructionIT it)
        {
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
    
        inline void check_div_zero(InstructionIT it, T val)
        {
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
    
        inline T check_real_aux(InstructionIT it, T val)
        {
            if (TRACE >= 2) {
                if (std::isnan(val)) {
                    fRealStats[FP_NAN]++;
                } else if (std::isinf(val)) {
                    fRealStats[FP_INFINITE]++;
                }
            }
            
            if (TRACE >= 1) {
                if (std::fpclassify(val) == FP_SUBNORMAL) {
                    fRealStats[FP_SUBNORMAL]++;
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
                        throw faustexception("");
                    }
                } else if (std::isinf(val)) {
                    std::cout << "-------- Interpreter 'Inf' trace start --------" << std::endl;
                    traceInstruction(it);
                    fTraceContext.write(&std::cout);
                    std::cout << "-------- Interpreter 'Inf' trace end --------\n\n";
                    // Fails at first error...
                    if (TRACE == 4) {
                        throw faustexception("");
                    }
                }
            }
            return val;
        }
    
        /*
          Keeps the latest TRACE_STACK_SIZE executed instructions, to be displayed when an error occurs.
        */
        struct InterpreterTrace {
            
            #define TRACE_STACK_SIZE 16
            
            std::vector<std::string> fExecTrace;
            int fWriteIndex;
            
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
                fWriteIndex = (fWriteIndex + 1) % TRACE_STACK_SIZE;
            }
            
            void write(std::ostream* out)
            {
                for (int i = fWriteIndex - 1; i >= 0; i--) {
                    *out << fExecTrace[i];
                }
                for (int i = fExecTrace.size() - 1; i >= fWriteIndex; i--) {
                    *out << fExecTrace[i];
                }
            }
            
        };

        InterpreterTrace fTraceContext;
    
        inline void traceInstruction(InstructionIT it)
        {
            if (TRACE >= 4) {
                std::stringstream message;
                (*it)->write(&message);
                fTraceContext.push(message.str());
            }
        }
    
        inline int assert_audio_buffer(InstructionIT it, int index)
        {
            if (TRACE >= 4 && ((index < 0) || (index >= fIntHeap[fFactory->fCountOffset]))) {
                std::cout << "-------- Interpreter crash trace start --------" << std::endl;
                std::cout << "assert_audio_buffer : count " << fIntHeap[fFactory->fCountOffset]  << " index " << index << std::endl;
                fTraceContext.write(&std::cout);
                std::cout << "-------- Interpreter crash trace end --------\n\n";
                throw faustexception("");
            } else {
                return index;
            }
        }
        
        inline int assert_int_heap(InstructionIT it, int index, int size = -1)
        {
            if (TRACE >= 4 && ((index < 0) || (index >= fFactory->fIntHeapSize) || (size > 0 && index >= size))) {
                std::cout << "-------- Interpreter crash trace start --------" << std::endl;
                std::cout << "assert_int_heap : fIntHeapSize " << fFactory->fIntHeapSize  << " index " << index << " size " << size << std::endl;
                fTraceContext.write(&std::cout);
                std::cout << "-------- Interpreter crash trace end --------\n\n";
                throw faustexception("");
            } else {
                return index;
            }
        }
        
        inline int assert_real_heap(InstructionIT it, int index, int size = -1)
        {
            if (TRACE >= 4 && ((index < 0) || (index >= fFactory->fRealHeapSize) || (size > 0 && index >= size))) {
                std::cout << "-------- Interpreter crash trace start --------" << std::endl;
                std::cout << "assert_real_heap : fRealHeapSize " << fFactory->fRealHeapSize  << " index " << index << " size " << size << std::endl;
                fTraceContext.write(&std::cout);
                std::cout << "-------- Interpreter crash trace end --------\n\n";
                throw faustexception("");
            } else {
                return index;
            }
        }
    
        inline T check_real(InstructionIT it, T val)
        {
            return (TRACE > 0) ? check_real_aux(it, val) : val;
        }
    
        #define push_int(val) (int_stack[int_stack_index++] = val)
        #define push_addr(addr) (address_stack[addr_stack_index++] = addr)
            
        #define pop_int() (int_stack[--int_stack_index])
        #define pop_addr() (address_stack[--addr_stack_index])
    
        #define push_real(it, val) (real_stack[real_stack_index++] = check_real(it, val))
        #define pop_real(it) check_real(it, real_stack[--real_stack_index])
    
        void ExecuteBuildUserInterface(FIRUserInterfaceBlockInstruction<T>* block, UITemplate* glue)
        {
            UIInstructionIT it;
            
            for (it = block->fInstructions.begin(); it != block->fInstructions.end(); it++) {
                
                //(*it)->write(&std::cout);
            
                switch ((*it)->fOpcode) {
                 
                        case FIRInstruction::kOpenVerticalBox:
                            glue->openVerticalBox((*it)->fLabel.c_str());
                            break;
                            
                        case FIRInstruction::kOpenHorizontalBox:
                            glue->openHorizontalBox((*it)->fLabel.c_str());
                            break;
                            
                        case FIRInstruction::kOpenTabBox:
                            glue->openTabBox((*it)->fLabel.c_str());
                            break;
                 
                        case FIRInstruction::kCloseBox:
                            glue->closeBox();
                            break;
                            
                        case FIRInstruction::kAddButton:
                            glue->addButton((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset]);
                            break;
                            
                        case FIRInstruction::kAddCheckButton:
                            glue->addCheckButton((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset]);
                            break;
                            
                        case FIRInstruction::kAddHorizontalSlider:
                            glue->addHorizontalSlider((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset],
                                                           (*it)->fInit, (*it)->fMin, (*it)->fMax, (*it)->fStep);
                            break;
                            
                        case FIRInstruction::kAddVerticalSlider:
                            glue->addVerticalSlider((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset],
                                                         (*it)->fInit, (*it)->fMin, (*it)->fMax, (*it)->fStep);
                            break;
                            
                        case FIRInstruction::kAddNumEntry:
                            glue->addNumEntry((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset], (*it)->fInit,
                                                   (*it)->fMin, (*it)->fMax, (*it)->fStep);
                            break;
                            
                        case FIRInstruction::kAddHorizontalBargraph:
                            glue->addHorizontalBargraph((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset], (*it)->fMin, (*it)->fMax);
                            break;
                            
                        case FIRInstruction::kAddVerticalBargraph:
                            glue->addVerticalBargraph((*it)->fLabel.c_str(), &fRealHeap[(*it)->fOffset], (*it)->fMin, (*it)->fMax);
                            break;
                            
                        case FIRInstruction::kDeclare:
                            // Special case for "0" zone
                            if ((*it)->fOffset == -1) {
                                glue->declare(static_cast<T*>(NULL), (*it)->fKey.c_str(), (*it)->fValue.c_str());
                            } else {
                                glue->declare(&fRealHeap[(*it)->fOffset], (*it)->fKey.c_str(), (*it)->fValue.c_str());
                            }
                            break;
                            
                        default:
                            break;
                }
            }
        }
    
        inline void ExecuteBlock(FIRBlockInstruction<T>* block)
        {
            static void* fDispatchTable[] = {
                
                // Numbers
                &&do_kRealValue, &&do_kInt32Value,
                
                // Memory
                &&do_kLoadReal, &&do_kLoadInt,
                &&do_kStoreReal, &&do_kStoreInt,
                &&do_kStoreRealValue, &&do_kStoreIntValue,
                &&do_kLoadIndexedReal, &&do_kLoadIndexedInt,
                &&do_kStoreIndexedReal, &&do_kStoreIndexedInt,
                &&do_kBlockStoreReal, &&do_kBlockStoreInt,
                &&do_kMoveReal, &&do_kMoveInt,
                &&do_kPairMoveReal, &&do_kPairMoveInt,
                &&do_kBlockPairMoveReal, &&do_kBlockPairMoveInt,
                &&do_kBlockShiftReal, &&do_kBlockShiftInt,
                &&do_kLoadInput, &&do_kStoreOutput,
                
                // Cast/bitcast
                &&do_kCastReal, &&do_kCastInt,
                &&do_kCastRealHeap, &&do_kCastIntHeap,
                &&do_kBitcastInt, &&do_kBitcastReal,
                
                // Standard math (stack OP stack)
                &&do_kAddReal, &&do_kAddInt, &&do_kSubReal, &&do_kSubInt,
                &&do_kMultReal, &&do_kMultInt, &&do_kDivReal, &&do_kDivInt,
                &&do_kRemReal, &&do_kRemInt, &&do_kLshInt, &&do_kRshInt, &&do_kGTInt,
                &&do_kLTInt, &&do_kGEInt, &&do_kLEInt, &&do_kEQInt, &&do_kNEInt,
                &&do_kGTReal, &&do_kLTReal, &&do_kGEReal,
                &&do_kLEReal, &&do_kEQReal, &&do_kNEReal,
                &&do_kANDInt, &&do_kORInt, &&do_kXORInt,
                
                // Standard math (heap OP heap)
                &&do_kAddRealHeap, &&do_kAddIntHeap, &&do_kSubRealHeap, &&do_kSubIntHeap,
                &&do_kMultRealHeap, &&do_kMultIntHeap, &&do_kDivRealHeap, &&do_kDivIntHeap,
                &&do_kRemRealHeap, &&do_kRemIntHeap, &&do_kLshIntHeap, &&do_kRshIntHeap, &&do_kGTIntHeap,
                &&do_kLTIntHeap, &&do_kGEIntHeap, &&do_kLEIntHeap, &&do_kEQIntHeap, &&do_kNEIntHeap,
                &&do_kGTRealHeap, &&do_kLTRealHeap, &&do_kGERealHeap,
                &&do_kLERealHeap, &&do_kEQRealHeap, &&do_kNERealHeap,
                &&do_kANDIntHeap, &&do_kORIntHeap, &&do_kXORIntHeap,
                
                // Standard math (heap OP stack)
                &&do_kAddRealStack, &&do_kAddIntStack, &&do_kSubRealStack, &&do_kSubIntStack,
                &&do_kMultRealStack, &&do_kMultIntStack, &&do_kDivRealStack, &&do_kDivIntStack,
                &&do_kRemRealStack, &&do_kRemIntStack, &&do_kLshIntStack, &&do_kRshIntStack, &&do_kGTIntStack,
                &&do_kLTIntStack, &&do_kGEIntStack, &&do_kLEIntStack, &&do_kEQIntStack, &&do_kNEIntStack,
                &&do_kGTRealStack, &&do_kLTRealStack, &&do_kGERealStack,
                &&do_kLERealStack, &&do_kEQRealStack, &&do_kNERealStack,
                &&do_kANDIntStack, &&do_kORIntStack, &&do_kXORIntStack,
                
                // Standard math (value OP stack)
                &&do_kAddRealStackValue, &&do_kAddIntStackValue, &&do_kSubRealStackValue, &&do_kSubIntStackValue,
                &&do_kMultRealStackValue, &&do_kMultIntStackValue, &&do_kDivRealStackValue, &&do_kDivIntStackValue,
                &&do_kRemRealStackValue, &&do_kRemIntStackValue, &&do_kLshIntStackValue, &&do_kRshIntStackValue, &&do_kGTIntStackValue,
                &&do_kLTIntStackValue, &&do_kGEIntStackValue, &&do_kLEIntStackValue, &&do_kEQIntStackValue, &&do_kNEIntStackValue,
                &&do_kGTRealStackValue, &&do_kLTRealStackValue, &&do_kGERealStackValue,
                &&do_kLERealStackValue, &&do_kEQRealStackValue, &&do_kNERealStackValue,
                &&do_kANDIntStackValue, &&do_kORIntStackValue, &&do_kXORIntStackValue,
    
                // Standard math (value OP heap)
                &&do_kAddRealValue, &&do_kAddIntValue, &&do_kSubRealValue, &&do_kSubIntValue,
                &&do_kMultRealValue, &&do_kMultIntValue, &&do_kDivRealValue, &&do_kDivIntValue,
                &&do_kRemRealValue, &&do_kRemIntValue, &&do_kLshIntValue, &&do_kRshIntValue, &&do_kGTIntValue,
                &&do_kLTIntValue, &&do_kGEIntValue, &&do_kLEIntValue, &&do_kEQIntValue, &&do_kNEIntValue,
                &&do_kGTRealValue, &&do_kLTRealValue, &&do_kGERealValue,
                &&do_kLERealValue, &&do_kEQRealValue, &&do_kNERealValue,
                &&do_kANDIntValue, &&do_kORIntValue, &&do_kXORIntValue,
                
                // Standard math (value OP heap) : non commutative operations
                &&do_kSubRealValueInvert, &&do_kSubIntValueInvert,
                &&do_kDivRealValueInvert, &&do_kDivIntValueInvert,
                &&do_kRemRealValueInvert, &&do_kRemIntValueInvert,
                &&do_kLshIntValueInvert, &&do_kRshIntValueInvert,
                &&do_kGTIntValueInvert, &&do_kLTIntValueInvert,
                &&do_kGEIntValueInvert, &&do_kLEIntValueInvert,
                &&do_kGTRealValueInvert, &&do_kLTRealValueInvert,
                &&do_kGERealValueInvert, &&do_kLERealValueInvert,
                
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
                
                // Extended unary math (heap OP heap)
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
                
                // Extended binary math
                &&do_kAtan2f,
                &&do_kFmodf,
                &&do_kPowf,
                &&do_kMax, &&do_kMaxf,
                &&do_kMin, &&do_kMinf,
                
                // Extended binary math (heap version)
                &&do_kAtan2fHeap,
                &&do_kFmodfHeap,
                &&do_kPowfHeap,
                &&do_kMaxHeap, &&do_kMaxfHeap,
                &&do_kMinHeap, &&do_kMinfHeap,
                
                // Extended binary math (stack version)
                &&do_kAtan2fStack,
                &&do_kFmodfStack,
                &&do_kPowfStack,
                &&do_kMaxStack, &&do_kMaxfStack,
                &&do_kMinStack, &&do_kMinfStack,
                
                // Extended binary math (Stack/Value version)
                &&do_kAtan2fStackValue,
                &&do_kFmodfStackValue,
                &&do_kPowfStackValue,
                &&do_kMaxStackValue, &&do_kMaxfStackValue,
                &&do_kMinStackValue, &&do_kMinfStackValue,
                
                // Extended binary math (Value version)
                &&do_kAtan2fValue,
                &&do_kFmodfValue,
                &&do_kPowfValue,
                &&do_kMaxValue, &&do_kMaxfValue,
                &&do_kMinValue, &&do_kMinfValue,
                
                // Extended binary math (Value version) : non commutative operations
                &&do_kAtan2fValueInvert,
                &&do_kFmodfValueInvert,
                &&do_kPowfValueInvert,
                
                // Control
                &&do_kLoop,
                &&do_kReturn,
                
                // Select/if
                &&do_kIf, &&do_kSelectReal, &&do_kSelectInt,
                &&do_kCondBranch
                
            };
            
            int real_stack_index = 0;
            int int_stack_index = 0;
            int addr_stack_index = 0;
            
            T real_stack[fRealStackSize];
            int int_stack[fIntStackSize];
            InstructionIT address_stack[64];
          
            #define dispatch_first() { goto *fDispatchTable[(*it)->fOpcode]; }
            #define dispatch_next() { traceInstruction(it); it++; goto *fDispatchTable[(*it)->fOpcode]; }
            
            #define dispatch_branch1() { it = (*it)->fBranch1->fInstructions.begin(); dispatch_first(); }
            #define dispatch_branch2() { it = (*it)->fBranch2->fInstructions.begin(); dispatch_first(); }
            
            #define push_branch1() { push_addr((*it)->fBranch1->fInstructions.begin()); }
            #define push_branch2() { push_addr((*it)->fBranch2->fInstructions.begin()); }
            
            #define dispatch_return() { it = pop_addr(); dispatch_first(); }
            #define save_return() { push_addr(it + 1); }
            #define empty_return() (addr_stack_index == 0)
            
            // Check block coherency
            InstructionIT it1 = block->fInstructions.end(); it1--;
            faustassert((*it1)->fOpcode == FIRInstruction::kReturn);
            
            try {
                
                InstructionIT it = block->fInstructions.begin();
                dispatch_first();
                
                while (true) {
                    
                    // Number operations
                    do_kRealValue:
                    {
                        push_real(it, (*it)->fRealValue);
                        dispatch_next();
                    }
                    
                    do_kInt32Value:
                    {
                        push_int((*it)->fIntValue);
                        dispatch_next();
                    }
                        
                    // Memory operations
                    do_kLoadReal:
                    {
                        if (TRACE) {
                            push_real(it, fRealHeap[assert_real_heap(it, (*it)->fOffset1)]);
                        } else {
                            push_real(it, fRealHeap[(*it)->fOffset1]);
                        }

                        dispatch_next();
                    }
                    
                    do_kLoadInt:
                    {
                        if (TRACE) {
                            push_int(fIntHeap[assert_int_heap(it, (*it)->fOffset1)]);
                        } else {
                            push_int(fIntHeap[(*it)->fOffset1]);
                        }
                        dispatch_next();
                    }
                    
                    do_kStoreReal:
                    {
                        if (TRACE) {
                            fRealHeap[assert_real_heap(it, (*it)->fOffset1)] = pop_real(it);
                        } else {
                            fRealHeap[(*it)->fOffset1] = pop_real(it);
                        }
                        dispatch_next();
                    }
                    
                    do_kStoreInt:
                    {
                        if (TRACE) {
                            fIntHeap[assert_int_heap(it, (*it)->fOffset1)] = pop_int();
                        } else {
                            fIntHeap[(*it)->fOffset1] = pop_int();
                        }
                        dispatch_next();
                    }
                    
                    // Directly store a value
                    do_kStoreRealValue:
                    {
                        if (TRACE) {
                            fRealHeap[assert_real_heap(it, (*it)->fOffset1)] = (*it)->fRealValue;
                        } else {
                            fRealHeap[(*it)->fOffset1] = (*it)->fRealValue;
                        }
                        dispatch_next();
                    }
                    
                    do_kStoreIntValue:
                    {
                        if (TRACE) {
                            fIntHeap[assert_int_heap(it, (*it)->fOffset1)] = (*it)->fIntValue;
                        } else {
                            fIntHeap[(*it)->fOffset1] = (*it)->fIntValue;
                        }
                        dispatch_next();
                    }
                    
                    do_kLoadIndexedReal:
                    {
                        if (TRACE) {
                            push_real(it, fRealHeap[(*it)->fOffset1 + assert_real_heap(it, pop_int(), (*it)->fOffset2)]);
                        } else {
                            push_real(it, fRealHeap[(*it)->fOffset1 + pop_int()]);
                        }
                        
                        dispatch_next();
                    }
                    
                    do_kLoadIndexedInt:
                    {
                        int offset = pop_int();
                        if (TRACE) {
                            push_int(fIntHeap[(*it)->fOffset1 + assert_int_heap(it, offset, (*it)->fOffset2)]);
                        } else {
                            push_int(fIntHeap[(*it)->fOffset1 + offset]);
                        }
                        dispatch_next();
                    }
                    
                    do_kStoreIndexedReal:
                    {
                        if (TRACE) {
                            fRealHeap[(*it)->fOffset1 + assert_real_heap(it, pop_int(), (*it)->fOffset2)] = pop_real(it);
                        } else {
                            fRealHeap[(*it)->fOffset1 + pop_int()] = pop_real(it);
                        }
                        dispatch_next();
                    }
                    
                    do_kStoreIndexedInt:
                    {
                        int offset = pop_int();
                        if (TRACE) {
                            fIntHeap[(*it)->fOffset1 + assert_int_heap(it, offset, (*it)->fOffset2)] = pop_int();
                        } else {
                            fIntHeap[(*it)->fOffset1 + offset] = pop_int();
                        }
                        dispatch_next();
                    }
                    
                    do_kBlockStoreReal:
                    {
                        FIRBlockStoreRealInstruction<T>* inst = dynamic_cast<FIRBlockStoreRealInstruction<T>*>(*it);
                        faustassert(inst);
                        for (int i = 0; i < inst->fOffset2; i++) {
                            fRealHeap[inst->fOffset1 + i] = inst->fNumTable[i];
                        }
                        dispatch_next();
                    }
                    
                    do_kBlockStoreInt:
                    {
                        FIRBlockStoreIntInstruction<T>* inst = dynamic_cast<FIRBlockStoreIntInstruction<T>*>(*it);
                        faustassert(inst);
                        for (int i = 0; i < inst->fOffset2; i++) {
                            fIntHeap[inst->fOffset1 + i] = inst->fNumTable[i];
                        }
                        dispatch_next();
                    }
                    
                    do_kMoveReal:
                    {
                        fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset2];
                        dispatch_next();
                    }
                    
                    do_kMoveInt:
                    {
                        fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset2];
                        dispatch_next();
                    }
                    
                    do_kPairMoveReal:
                    {
                        fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset1 - 1];
                        fRealHeap[(*it)->fOffset2] = fRealHeap[(*it)->fOffset2 - 1];
                        dispatch_next();
                    }
                    
                    do_kPairMoveInt:
                    {
                        fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset1 - 1];
                        fIntHeap[(*it)->fOffset2] = fIntHeap[(*it)->fOffset2 - 1];
                        dispatch_next();
                    }
       
                    do_kBlockPairMoveReal:
                    {
                        for (int i = (*it)->fOffset1; i < (*it)->fOffset2; i+=2) {
                            fRealHeap[i+1] = fRealHeap[i];
                        }
                        dispatch_next();
                    }
                    
                    do_kBlockPairMoveInt:
                    {
                        for (int i = (*it)->fOffset1; i < (*it)->fOffset2; i+=2) {
                            fIntHeap[i+1] = fIntHeap[i];
                        }
                        dispatch_next();
                    }
                    
                    do_kBlockShiftReal:
                    {
                        for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i-=1) {
                            fRealHeap[i] = fRealHeap[i-1];
                        }
                        dispatch_next();
                    }
                    
                    do_kBlockShiftInt:
                    {
                        for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i-=1) {
                            fIntHeap[i] = fIntHeap[i-1];
                        }
                        dispatch_next();
                    }
                    
                    // Input/output access
                    do_kLoadInput:
                    {
                        if (TRACE) {
                            push_real(it, fInputs[(*it)->fOffset1][assert_audio_buffer(it, pop_int())]);
                        } else {
                            push_real(it, fInputs[(*it)->fOffset1][pop_int()]);
                        }
                        dispatch_next();
                    }
                        
                    do_kStoreOutput:
                    {
                        if (TRACE) {
                            fOutputs[(*it)->fOffset1][assert_audio_buffer(it, pop_int())] = pop_real(it);
                        } else {
                            fOutputs[(*it)->fOffset1][pop_int()] = pop_real(it);
                        }
                        dispatch_next();
                    }
                    
                    // Cast operations
                    do_kCastReal:
                    {
                        push_real(it, T(pop_int()));
                        dispatch_next();
                    }
                    
                    do_kCastRealHeap:
                    {
                        push_real(it, T(fIntHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kCastInt:
                    {
                        push_int(int(pop_real(it)));
                        dispatch_next();
                    }
                    
                    do_kCastIntHeap:
                    {
                        push_int(int(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    // Bitcast operations
                    do_kBitcastInt:
                    {
                        T v1 = pop_real(it);
                        int v2 = *reinterpret_cast<int*>(&v1);
                        push_int(v2);
                        dispatch_next();
                    }
                    
                    do_kBitcastReal:
                    {
                        int v1 = pop_int();
                        T v2 = *reinterpret_cast<T*>(&v1);
                        push_real(it, v2);
                        dispatch_next();
                    }
                    
                    //-------------------------------------------------------
                    // Standard math operations : 'stack' OP 'stack' version
                    //-------------------------------------------------------
                    
                    do_kAddReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_real(it, v1 + v2);
                        dispatch_next();
                    }
                  
                    do_kAddInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        if (TRACE) {
                            int res;
                            if (__builtin_sadd_overflow(v1, v2, &res)) {
                                warning_overflow(it);
                            }
                            push_int(res);
                        } else {
                            push_int(v1 + v2);
                        }
                        dispatch_next();
                    }
                    
                    do_kSubReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_real(it, v1 - v2);
                        dispatch_next();
                    }
                    
                    do_kSubInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        if (TRACE) {
                            int res;
                            if (__builtin_ssub_overflow(v1, v2, &res)) {
                                warning_overflow(it);
                            }
                            push_int(res);
                        } else {
                            push_int(v1 - v2);
                        }
                        dispatch_next();
                    }
                    
                    do_kMultReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_real(it, v1 * v2);
                        dispatch_next();
                    }
                    
                    do_kMultInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        if (TRACE) {
                            int res;
                            if (__builtin_smul_overflow(v1, v2, &res)) {
                                warning_overflow(it);
                            }
                            push_int(res);
                        } else {
                            push_int(v1 * v2);
                        }
                        dispatch_next();
                    }
                    
                    do_kDivReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        if (TRACE) {
                            check_div_zero(it, v2);
                        }
                        push_real(it, v1 / v2);
                        dispatch_next();
                    }
                    
                    do_kDivInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        if (TRACE) {
                            check_div_zero(it, v2);
                        }
                        push_int(v1 / v2);
                        dispatch_next();
                    }
                        
                    do_kRemReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        if (TRACE) {
                            check_div_zero(it, v2);
                        }
                        push_real(it, std::remainder(v1, v2));
                        dispatch_next();
                    }
                    
                    do_kRemInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        if (TRACE) {
                            check_div_zero(it, v2);
                        }
                        push_int(v1 % v2);
                        dispatch_next();
                    }
                        
                    // Shift operation
                    do_kLshInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 << v2);
                        dispatch_next();
                    }
                    
                    do_kRshInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 >> v2);
                        dispatch_next();
                    }
                        
                    // Comparaison Int
                    do_kGTInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 > v2);
                        dispatch_next();
                    }
                    
                    do_kLTInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 < v2);
                        dispatch_next();
                    }
                    
                    do_kGEInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 >= v2);
                        dispatch_next();
                    }
                    
                    do_kLEInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 <= v2);
                        dispatch_next();
                    }
                    
                    do_kEQInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 == v2);
                        dispatch_next();
                    }
                    
                    do_kNEInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 != v2);
                        dispatch_next();
                    }
                        
                    // Comparaison Real
                    do_kGTReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_int(v1 > v2);
                        dispatch_next();
                    }
                    
                    do_kLTReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_int(v1 < v2);
                        dispatch_next();
                    }
                    
                    do_kGEReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_int(v1 >= v2);
                        dispatch_next();
                    }
                    
                    do_kLEReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_int(v1 <= v2);
                        dispatch_next();
                    }
                    
                    do_kEQReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_int(v1 == v2);
                        dispatch_next();
                    }
                    
                    do_kNEReal:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_int(v1 != v2);
                        dispatch_next();
                    }
                        
                    // Logical operations
                    do_kANDInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 & v2);
                        dispatch_next();
                    }
                    
                    do_kORInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 | v2);
                        dispatch_next();
                    }
                    
                    do_kXORInt:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 ^ v2);
                        dispatch_next();
                    }
                    
                    //-----------------------------------------------------
                    // Standard math operations : 'heap' OP 'heap' version
                    //-----------------------------------------------------
                    
                    do_kAddRealHeap:
                    {
                        push_real(it, fRealHeap[(*it)->fOffset1] + fRealHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kAddIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] + fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kSubRealHeap:
                    {
                        push_real(it, fRealHeap[(*it)->fOffset1] - fRealHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kSubIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] - fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kMultRealHeap:
                    {
                        push_real(it, fRealHeap[(*it)->fOffset1] * fRealHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kMultIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] * fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kDivRealHeap:
                    {
                        push_real(it, fRealHeap[(*it)->fOffset1] / fRealHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kDivIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] / fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kRemRealHeap:
                    {
                        push_real(it, std::remainder(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                        dispatch_next();
                    }
                    
                    do_kRemIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] % fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    // Shift operation
                    do_kLshIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] << fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kRshIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] >> fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    // Comparaison Int
                    do_kGTIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] > fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kLTIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] < fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kGEIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] >= fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kLEIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] <= fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kEQIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] == fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kNEIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] != fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    // Comparaison Real
                    do_kGTRealHeap:
                    {
                        push_int(fRealHeap[(*it)->fOffset1] > fRealHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kLTRealHeap:
                    {
                        push_int(fRealHeap[(*it)->fOffset1] < fRealHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kGERealHeap:
                    {
                        push_int(fRealHeap[(*it)->fOffset1] >= fRealHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kLERealHeap:
                    {
                        push_int(fRealHeap[(*it)->fOffset1] <= fRealHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kEQRealHeap:
                    {
                        push_int(fRealHeap[(*it)->fOffset1] == fRealHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kNERealHeap:
                    {
                        push_int(fRealHeap[(*it)->fOffset1] != fRealHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    // Logical operations
                    do_kANDIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] & fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kORIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] | fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    do_kXORIntHeap:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] ^ fIntHeap[(*it)->fOffset2]);
                        dispatch_next();
                    }
                    
                    //------------------------------------------------------
                    // Standard math operations : 'stack' OP 'heap' version
                    //------------------------------------------------------
                    
                    do_kAddRealStack:
                    {
                        T v1 = pop_real(it);
                        push_real(it, fRealHeap[(*it)->fOffset1] + v1);
                        dispatch_next();
                    }
                    
                    do_kAddIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] + v1);
                        dispatch_next();
                    }
                    
                    do_kSubRealStack:
                    {
                        T v1 = pop_real(it);
                        push_real(it, fRealHeap[(*it)->fOffset1] - v1);
                        dispatch_next();
                    }
                    
                    do_kSubIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] - v1);
                        dispatch_next();
                    }
                    
                    do_kMultRealStack:
                    {
                        T v1 = pop_real(it);
                        push_real(it, fRealHeap[(*it)->fOffset1] * v1);
                        dispatch_next();
                    }
                    
                    do_kMultIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] * v1);
                        dispatch_next();
                    }
                    
                    do_kDivRealStack:
                    {
                        T v1 = pop_real(it);
                        push_real(it, fRealHeap[(*it)->fOffset1] / v1);
                        dispatch_next();
                    }
                    
                    do_kDivIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] / v1);
                        dispatch_next();
                    }
                    
                    do_kRemRealStack:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::remainder(fRealHeap[(*it)->fOffset1], v1));
                        dispatch_next();
                    }
                    
                    do_kRemIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] % v1);
                        dispatch_next();
                    }
                    
                    // Shift operation
                    do_kLshIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] << v1);
                        dispatch_next();
                    }
                    
                    do_kRshIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] >> v1);
                        dispatch_next();
                    }
                    
                    // Comparaison Int
                    do_kGTIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] > v1);
                        dispatch_next();
                    }
                    
                    do_kLTIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] < v1);
                        dispatch_next();
                    }
                    
                    do_kGEIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] >= v1);
                        dispatch_next();
                    }
                    
                    do_kLEIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] <= v1);
                        dispatch_next();
                    }
                    
                    do_kEQIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] == v1);
                        dispatch_next();
                    }
                    
                    do_kNEIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] != v1);
                        dispatch_next();
                    }
                    
                    // Comparaison Real
                    do_kGTRealStack:
                    {
                        T v1 = pop_real(it);
                        push_int(fRealHeap[(*it)->fOffset1] > v1);
                        dispatch_next();
                    }
                    
                    do_kLTRealStack:
                    {
                        T v1 = pop_real(it);
                        push_int(fRealHeap[(*it)->fOffset1] < v1);
                        dispatch_next();
                    }
                    
                    do_kGERealStack:
                    {
                        T v1 = pop_real(it);
                        push_int(fRealHeap[(*it)->fOffset1] >= v1);
                        dispatch_next();
                    }
                    
                    do_kLERealStack:
                    {
                        T v1 = pop_real(it);
                        push_int(fRealHeap[(*it)->fOffset1] <= v1);
                        dispatch_next();
                    }
                    
                    do_kEQRealStack:
                    {
                        T v1 = pop_real(it);
                        push_int(fRealHeap[(*it)->fOffset1] == v1);
                        dispatch_next();
                    }
                    
                    do_kNERealStack:
                    {
                        T v1 = pop_real(it);
                        push_int(fRealHeap[(*it)->fOffset1] != v1);
                        dispatch_next();
                    }
                    
                    // Logical operations
                    do_kANDIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] & v1);
                        dispatch_next();
                    }
                    
                    do_kORIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] | v1);
                        dispatch_next();
                    }
                    
                    do_kXORIntStack:
                    {
                        int v1 = pop_int();
                        push_int(fIntHeap[(*it)->fOffset1] ^ v1);
                        dispatch_next();
                    }
                    
                    //-------------------------------------------------------
                    // Standard math operations : 'stack' OP 'value' version
                    //-------------------------------------------------------
                    
                    do_kAddRealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_real(it, (*it)->fRealValue + v1);
                        dispatch_next();
                    }
                    
                    do_kAddIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue + v1);
                        dispatch_next();
                    }
                    
                    do_kSubRealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_real(it, (*it)->fRealValue - v1);
                        dispatch_next();
                    }
                    
                    do_kSubIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue - v1);
                        dispatch_next();
                    }
                    
                    do_kMultRealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_real(it, (*it)->fRealValue * v1);
                        dispatch_next();
                    }
                    
                    do_kMultIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue * v1);
                        dispatch_next();
                    }
                    
                    do_kDivRealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_real(it, (*it)->fRealValue / v1);
                        dispatch_next();
                    }
                    
                    do_kDivIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue / v1);
                        dispatch_next();
                    }
                    
                    do_kRemRealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::remainder((*it)->fRealValue, v1));
                        dispatch_next();
                    }
                    
                    do_kRemIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue % v1);
                        dispatch_next();
                    }
                    
                    // Shift operation
                    do_kLshIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue << v1);
                        dispatch_next();
                    }
                    
                    do_kRshIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue >> v1);
                        dispatch_next();
                    }
                    
                    // Comparaison Int
                    do_kGTIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue > v1);
                        dispatch_next();
                    }
                    
                    do_kLTIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue < v1);
                        dispatch_next();
                    }
                    
                    do_kGEIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue >= v1);
                        dispatch_next();
                    }
                    
                    do_kLEIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue <= v1);
                        dispatch_next();
                    }
                    
                    do_kEQIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue == v1);
                        dispatch_next();
                    }
                    
                    do_kNEIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue != v1);
                        dispatch_next();
                    }
                    
                    // Comparaison Real
                    do_kGTRealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_int((*it)->fRealValue > v1);
                        dispatch_next();
                    }
                    
                    do_kLTRealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_int((*it)->fRealValue < v1);
                        dispatch_next();
                    }
                    
                    do_kGERealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_int((*it)->fRealValue >= v1);
                        dispatch_next();
                    }
                    
                    do_kLERealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_int((*it)->fRealValue <= v1);
                        dispatch_next();
                    }
                    
                    do_kEQRealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_int((*it)->fRealValue == v1);
                        dispatch_next();
                    }
                    
                    do_kNERealStackValue:
                    {
                        T v1 = pop_real(it);
                        push_int((*it)->fRealValue != v1);
                        dispatch_next();
                    }
                    
                    // Logical operations
                    do_kANDIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue & v1);
                        dispatch_next();
                    }
                    
                    do_kORIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue | v1);
                        dispatch_next();
                    }
                    
                    do_kXORIntStackValue:
                    {
                        int v1 = pop_int();
                        push_int((*it)->fIntValue ^ v1);
                        dispatch_next();
                    }
          
                    //------------------------------------------------------
                    // Standard math operations : 'value' OP 'heap' version
                    //------------------------------------------------------
                    
                    do_kAddRealValue:
                    {
                        push_real(it, (*it)->fRealValue + fRealHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kAddIntValue:
                    {
                        push_int((*it)->fIntValue + fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kSubRealValue:
                    {
                        push_real(it, (*it)->fRealValue - fRealHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kSubIntValue:
                    {
                        push_int((*it)->fIntValue - fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kMultRealValue:
                    {
                        push_real(it, (*it)->fRealValue * fRealHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kMultIntValue:
                    {
                        push_int((*it)->fIntValue * fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kDivRealValue:
                    {
                        push_real(it, (*it)->fRealValue / fRealHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kDivIntValue:
                    {
                        push_int((*it)->fIntValue / fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kRemRealValue:
                    {
                        push_real(it, std::remainder((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
        
                    do_kRemIntValue:
                    {
                        push_int((*it)->fIntValue % fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    // Shift operation
                    do_kLshIntValue:
                    {
                        push_int((*it)->fIntValue << fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kRshIntValue:
                    {
                        push_int((*it)->fIntValue >> fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    // Comparaison Int
                    do_kGTIntValue:
                    {
                        push_int((*it)->fIntValue > fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kLTIntValue:
                    {
                        push_int((*it)->fIntValue < fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kGEIntValue:
                    {
                        push_int((*it)->fIntValue >= fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kLEIntValue:
                    {
                        push_int((*it)->fIntValue <= fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kEQIntValue:
                    {
                        push_int((*it)->fIntValue == fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kNEIntValue:
                    {
                        push_int((*it)->fIntValue != fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    // Comparaison Real
                    do_kGTRealValue:
                    {
                        push_int((*it)->fRealValue > fRealHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kLTRealValue:
                    {
                        push_int((*it)->fRealValue < fRealHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kGERealValue:
                    {
                        push_int((*it)->fRealValue >= fRealHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kLERealValue:
                    {
                        push_int((*it)->fRealValue <= fRealHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kEQRealValue:
                    {
                        push_int((*it)->fRealValue == fRealHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kNERealValue:
                    {
                        push_int((*it)->fRealValue != fRealHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    // Logical operations
                    do_kANDIntValue:
                    {
                        push_int((*it)->fIntValue & fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kORIntValue:
                    {
                        push_int((*it)->fIntValue | fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    do_kXORIntValue:
                    {
                        push_int((*it)->fIntValue ^ fIntHeap[(*it)->fOffset1]);
                        dispatch_next();
                    }
                    
                    //----------------------------------------------------
                    // Standard math operations : Value inverted version
                    // (non commutative operations)
                    //----------------------------------------------------
                    
                    do_kSubRealValueInvert:
                    {
                        push_real(it, fRealHeap[(*it)->fOffset1] - (*it)->fRealValue);
                        dispatch_next();
                    }
                    
                    do_kSubIntValueInvert:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] - (*it)->fIntValue);
                        dispatch_next();
                    }
                    
                    do_kDivRealValueInvert:
                    {
                        push_real(it, fRealHeap[(*it)->fOffset1] / (*it)->fRealValue);
                        dispatch_next();
                    }
                    
                    do_kDivIntValueInvert:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] / (*it)->fIntValue);
                        dispatch_next();
                    }
                    
                    do_kRemRealValueInvert:
                    {
                        push_real(it, std::remainder(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                        dispatch_next();
                    }
                    
                    do_kRemIntValueInvert:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] % (*it)->fIntValue);
                        dispatch_next();
                    }
                    
                    // Shift operation
                    do_kLshIntValueInvert:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] << (*it)->fIntValue);
                        dispatch_next();
                    }
                    
                    do_kRshIntValueInvert:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] >> (*it)->fIntValue);
                        dispatch_next();
                    }
                    
                    // Comparaison Int
                    do_kGTIntValueInvert:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] > (*it)->fIntValue);
                        dispatch_next();
                    }
                    
                    do_kLTIntValueInvert:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] < (*it)->fIntValue);
                        dispatch_next();
                    }
                    
                    do_kGEIntValueInvert:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] >= (*it)->fIntValue);
                        dispatch_next();
                    }
                    
                    do_kLEIntValueInvert:
                    {
                        push_int(fIntHeap[(*it)->fOffset1] <= (*it)->fIntValue);
                        dispatch_next();
                    }
                    
                    // Comparaison Real
                    do_kGTRealValueInvert:
                    {
                        push_int(fRealHeap[(*it)->fOffset1] > (*it)->fRealValue);
                        dispatch_next();
                    }
                    
                    do_kLTRealValueInvert:
                    {
                        push_int(fRealHeap[(*it)->fOffset1] < (*it)->fRealValue);
                        dispatch_next();
                    }
                    
                    do_kGERealValueInvert:
                    {
                        push_int(fRealHeap[(*it)->fOffset1] >= (*it)->fRealValue);
                        dispatch_next();
                    }
                    
                    do_kLERealValueInvert:
                    {
                        push_int(fRealHeap[(*it)->fOffset1] <= (*it)->fRealValue);
                        dispatch_next();
                    }
           
                    //---------------------
                    // Extended unary math
                    //---------------------
                    
                    do_kAbs:
                    {
                        int v = pop_int();
                        push_int(std::abs(v));
                        dispatch_next();
                    }
                    
                    do_kAbsf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::fabs(v));
                        dispatch_next();
                    }
                    
                    do_kAcosf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::acos(v));
                        dispatch_next();
                    }
                    
                    do_kAsinf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::asin(v));
                        dispatch_next();
                    }
                    
                    do_kAtanf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::atan(v));
                        dispatch_next();
                    }
                    
                    do_kCeilf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::ceil(v));
                        dispatch_next();
                    }
                    
                    do_kCosf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::cos(v));
                        dispatch_next();
                    }
                    
                    do_kCoshf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::cosh(v));
                        dispatch_next();
                    }
                    
                    do_kExpf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::exp(v));
                        dispatch_next();
                    }

                    do_kFloorf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::floor(v));
                        dispatch_next();
                    }

                    do_kLogf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::log(v));
                        dispatch_next();
                    }
                    
                    do_kLog10f:
                    {
                        T v = pop_real(it);
                        push_real(it, std::log10(v));
                        dispatch_next();
                    }
                    
                    do_kRoundf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::round(v));
                        dispatch_next();
                    }
                    
                    do_kSinf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::sin(v));
                        dispatch_next();
                    }
                    
                    do_kSinhf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::sinh(v));
                        dispatch_next();
                    }
                    
                    do_kSqrtf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::sqrt(v));
                        dispatch_next();
                    }
                    
                    do_kTanf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::tan(v));
                        dispatch_next();
                    }
                    
                    do_kTanhf:
                    {
                        T v = pop_real(it);
                        push_real(it, std::tanh(v));
                        dispatch_next();
                    }
                    
                    //------------------------------------
                    // Extended unary math (heap version)
                    ///-----------------------------------
                    
                    do_kAbsHeap:
                    {
                        push_int(std::abs(fIntHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kAbsfHeap:
                    {
                        push_real(it, std::fabs(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kAcosfHeap:
                    {
                        push_real(it, std::acos(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kAsinfHeap:
                    {
                        push_real(it, std::asin(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kAtanfHeap:
                    {
                        push_real(it, std::atan(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kCeilfHeap:
                    {
                        push_real(it, std::ceil(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kCosfHeap:
                    {
                        push_real(it, std::cos(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kCoshfHeap:
                    {
                        push_real(it, std::cosh(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kExpfHeap:
                    {
                        push_real(it, std::exp(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kFloorfHeap:
                    {
                        push_real(it, std::floor(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kLogfHeap:
                    {
                        push_real(it, std::log(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kLog10fHeap:
                    {
                        push_real(it, std::log10(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kRoundfHeap:
                    {
                        push_real(it, std::round(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kSinfHeap:
                    {
                        push_real(it, std::sin(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kSinhfHeap:
                    {
                        push_real(it, std::sinh(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kSqrtfHeap:
                    {
                        push_real(it, std::sqrt(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kTanfHeap:
                    {
                        push_real(it, std::tan(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    do_kTanhfHeap:
                    {
                        push_real(it, std::tanh(fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
          
                    //----------------------
                    // Extended binary math
                    //----------------------
                    
                    do_kAtan2f:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_real(it, std::atan2(v1, v2));
                        dispatch_next();
                    }
               
                    do_kFmodf:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_real(it, std::fmod(v1, v2));
                        dispatch_next();
                    }
                    
                    do_kPowf:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_real(it, std::pow(v1, v2));
                        dispatch_next();
                    }
                    
                    do_kMax:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(std::max(v1, v2));
                        dispatch_next();
                    }
                    
                    do_kMaxf:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_real(it, std::max(v1, v2));
                        dispatch_next();
                    }
                    
                    do_kMin:
                    {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(std::min(v1, v2));
                        dispatch_next();
                    }
                    
                    do_kMinf:
                    {
                        T v1 = pop_real(it);
                        T v2 = pop_real(it);
                        push_real(it, std::min(v1, v2));
                        dispatch_next();
                    }
                    
                    //-------------------------------------
                    // Extended binary math (heap version)
                    //-------------------------------------
                    
                    do_kAtan2fHeap:
                    {
                        push_real(it, std::atan2(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                        dispatch_next();
                    }

                    do_kFmodfHeap:
                    {
                        push_real(it, std::fmod(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                        dispatch_next();
                    }

                    do_kPowfHeap:
                    {
                        push_real(it, std::pow(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                        dispatch_next();
                    }

                    do_kMaxHeap:
                    {
                        push_int(std::max(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
                        dispatch_next();
                    }

                    do_kMaxfHeap:
                    {
                        push_real(it, std::max(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                        dispatch_next();
                    }

                    do_kMinHeap:
                    {
                        push_int(std::min(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
                        dispatch_next();
                    }

                    do_kMinfHeap:
                    {
                        push_real(it, std::min(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                        dispatch_next();
                    }
                    
                    //--------------------------------------
                    // Extended binary math (stack version)
                    //--------------------------------------
                    
                    do_kAtan2fStack:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::atan2(fRealHeap[(*it)->fOffset1], v1));
                        dispatch_next();
                    }
                    
                    do_kFmodfStack:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::fmod(fRealHeap[(*it)->fOffset1], v1));
                        dispatch_next();
                    }
                    
                    do_kPowfStack:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::pow(fRealHeap[(*it)->fOffset1], v1));
                        dispatch_next();
                    }
                    
                    do_kMaxStack:
                    {
                        int v1 = pop_int();
                        push_int(std::max(fIntHeap[(*it)->fOffset1], v1));
                        dispatch_next();
                    }
                    
                    do_kMaxfStack:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::max(fRealHeap[(*it)->fOffset1], v1));
                        dispatch_next();
                    }
                    
                    do_kMinStack:
                    {
                        int v1 = pop_int();
                        push_int(std::min(fIntHeap[(*it)->fOffset1], v1));
                        dispatch_next();
                    }
                    
                    do_kMinfStack:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::min(fRealHeap[(*it)->fOffset1], v1));
                        dispatch_next();
                    }
                    
                    //--------------------------------------------
                    // Extended binary math (stack/value version)
                    //--------------------------------------------
                    
                    do_kAtan2fStackValue:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::atan2((*it)->fRealValue, v1));
                        dispatch_next();
                    }
                    
                    do_kFmodfStackValue:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::fmod((*it)->fRealValue, v1));
                        dispatch_next();
                    }
                    
                    do_kPowfStackValue:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::pow((*it)->fRealValue, v1));
                        dispatch_next();
                    }
                    
                    do_kMaxStackValue:
                    {
                        int v1 = pop_int();
                        push_int(std::max((*it)->fIntValue, v1));
                        dispatch_next();
                    }
                    
                    do_kMaxfStackValue:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::max((*it)->fRealValue, v1));
                        dispatch_next();
                    }
                    
                    do_kMinStackValue:
                    {
                        int v1 = pop_int();
                        push_int(std::min((*it)->fIntValue, v1));
                        dispatch_next();
                    }
                    
                    do_kMinfStackValue:
                    {
                        T v1 = pop_real(it);
                        push_real(it, std::min((*it)->fRealValue, v1));
                        dispatch_next();
                    }

                    //-------------------------------------
                    // Extended binary math (Value version)
                    //-------------------------------------

                    do_kAtan2fValue:
                    {
                        push_real(it, std::atan2((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }

                    do_kFmodfValue:
                    {
                        push_real(it, std::fmod((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }

                    do_kPowfValue:
                    {
                        push_real(it, std::pow((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }

                    do_kMaxValue:
                    {
                        push_int(std::max((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }

                    do_kMaxfValue:
                    {
                        push_real(it, std::max((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }

                    do_kMinValue:
                    {
                        push_int(std::min((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }

                    do_kMinfValue:
                    {
                        push_real(it, std::min((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                        dispatch_next();
                    }
                    
                    //-------------------------------------------------------------------
                    // Extended binary math (Value version) : non commutative operations
                    //-------------------------------------------------------------------

                    do_kAtan2fValueInvert:
                    {
                        push_real(it, std::atan2(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                        dispatch_next();
                    }

                    do_kFmodfValueInvert:
                    {
                        push_real(it, std::fmod(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                        dispatch_next();
                    }

                    do_kPowfValueInvert:
                    {
                        push_real(it, std::pow(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                        dispatch_next();
                    }

                    //---------
                    // Control
                    //---------
                    
                    do_kReturn:
                    {
                        // Empty addr stack = end of computation
                        if (empty_return()) {
                            break;
                        } else {
                            dispatch_return();
                        }
                    }
                    
                    do_kIf:
                    {
                        // Keep next instruction
                        save_return();
                        
                        if (pop_int()) {
                            // Execute new block
                            faustassert((*it)->fBranch1);
                            dispatch_branch1();
                            // No value (If)
                        } else {
                            // Execute new block
                            faustassert((*it)->fBranch2);
                            dispatch_branch2();
                            // No value (If)
                        }
                    }
                    
                    do_kSelectReal:
                    {
                        // Keep next instruction
                        save_return();
                        
                        if (pop_int()) {
                            // Execute new block
                            faustassert((*it)->fBranch1);
                            dispatch_branch1();
                            // Real value
                        } else {
                            // Execute new block
                            faustassert((*it)->fBranch2);
                            dispatch_branch2();
                            // Real value
                        }
                    }
                    
                    do_kSelectInt:
                    {
                        // Keep next instruction
                        save_return();
                        
                        if (pop_int()) {
                            // Execute new block
                            faustassert((*it)->fBranch1);
                            dispatch_branch1();
                            // Int value
                        } else {
                            // Execute new block
                            faustassert((*it)->fBranch2);
                            dispatch_branch2();
                            // Int value
                        }
                    }
                    
                    do_kCondBranch:
                    {
                        // If condition is true, just branch back on the block beginning
                        if (pop_int()) {
                            faustassert((*it)->fBranch1);
                            dispatch_branch1();
                        } else {
                            // Just continue after 'loop block'
                            dispatch_next();
                        }
                    }
                    
                    do_kLoop:
                    {
                        // Keep next instruction
                        save_return();
                        
                        // Push branch2 (loop content)
                        faustassert((*it)->fBranch2);
                        push_branch2();
                        
                        // And start branch1 loop variable declaration block
                        faustassert((*it)->fBranch1);
                        dispatch_branch1();
                    }
                }
                
                //printf("END real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index);
                
                // Check stack coherency
                faustassert(real_stack_index == 0 && int_stack_index == 0);
                
            } catch (faustexception& e) {
                std::cout << e.Message();
            }
        }
  
    
    public:
    
        FIRInterpreter(interpreter_dsp_factory_aux<T, TRACE>* factory)
        {
            /*
            std::cout << "FIRInterpreter :"
                    << " int_heap_size " << int_heap_size
                    << " real_heap_size " << real_heap_size
                    << " sr_offset " << sr_offset
                    << " count_offset " << count_offset << std::endl;
            */
            
            fFactory = factory;
            
            if (fFactory->getMemoryManager()) {
                fRealHeap = static_cast<T*>(fFactory->allocate(sizeof(T) * fFactory->fRealHeapSize));
                fIntHeap = static_cast<int*>(fFactory->allocate(sizeof(T) * fFactory->fIntHeapSize));
            } else {
                fRealHeap = new T[fFactory->fRealHeapSize];
                fIntHeap = new int[fFactory->fIntHeapSize];
            }
            
            // Initialise HEAP with 0
            memset(fRealHeap, 0, fFactory->fRealHeapSize * sizeof(T));
            memset(fIntHeap, 0, fFactory->fIntHeapSize * sizeof(int));
            
            // Stack
            fRealStackSize = 512;
            fIntStackSize = 512;
            
            fRealStats[INTEGER_OVERFLOW] = 0;
            fRealStats[DIV_BY_ZERO] = 0;
            fRealStats[FP_INFINITE] = 0;
            fRealStats[FP_NAN] = 0;
            fRealStats[FP_SUBNORMAL] = 0;
        }
    
        virtual ~FIRInterpreter()
        {
            if (fFactory->getMemoryManager()) {
                fFactory->destroy(fRealHeap);
                fFactory->destroy(fIntHeap);
            } else {
                delete [] fRealHeap;
                delete [] fIntHeap;
            }
            if (TRACE) {
                printStats();
            }
        }
    
        // Freeze values
        void freezeValues(std::map<int, int>& int_map, std::map<int, T>& real_map)
        {
            std::cout << "freezeValues Int " << std::endl;
            typename std::map<int, int>::iterator it1;
            for (it1 = int_map.begin(); it1 != int_map.end(); it1++) {
                std::cout << "offset " << (*it1).first << " value " << (*it1).second << std::endl;
                fIntHeap[(*it1).first] = (*it1).second;
            }
            
            std::cout << "freezeValues Real" << std::endl;
            typename std::map<int, T>::iterator it2;
            for (it2 = real_map.begin(); it2 != real_map.end(); it2++) {
                std::cout << "offset " << (*it2).first << " value " << (*it2).second << std::endl;
                fRealHeap[(*it2).first] = (*it2).second;
            }
        }
 
};

#endif
