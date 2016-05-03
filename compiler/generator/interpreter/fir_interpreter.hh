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

#include <string>
#include <math.h>
#include <assert.h>
#include <iostream>

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "interpreter_bytecode.hh"

// Interpreter

#define push_real(val) (real_stack[real_stack_index++] = val)
#define push_int(val) (int_stack[int_stack_index++] = val)
#define push_addr(addr) (address_stack[addr_stack_index++] = addr)

#define pop_real() (real_stack[--real_stack_index])
#define pop_int() (int_stack[--int_stack_index])
#define pop_addr() (address_stack[--addr_stack_index])

// FIR bytecode interpreter
template <class T>
class FIRInterpreter  {

    protected:
    
        T* fRealHeap;
        int* fIntHeap;
    
        int fRealHeapSize;
        int fIntHeapSize;
        int fSROffset;
        int fCountOffset;
    
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
    
        inline void ExecuteBlock(FIRBlockInstruction<T>* block)
        {
            //printf("ExecuteBlock\n");
            
            /*
            #define dispatch_first() { (*it)->write(&std::cout); goto *fDispatchTable[(*it)->fOpcode]; }
            #define dispatch() { (*it)->write(&std::cout); printf("int_stack_index = %d real_stack_index = %d\n", int_stack_index, real_stack_index);  \
                                max_real_stack = std::max(max_real_stack, real_stack_index); max_int_stack = std::max(max_int_stack, int_stack_index); \
                                assert(real_stack_index >= 0 && int_stack_index >= 0); \
                                it++; goto *fDispatchTable[(*it)->fOpcode]; }
            */
            
            #define dispatch_first() { goto *fDispatchTable[(*it)->fOpcode]; }
            #define dispatch_next() { it++; goto *fDispatchTable[(*it)->fOpcode]; }
            
            #define dispatch_branch1() { it = (*it)->fBranch1->fInstructions.begin(); dispatch_first(); }
            #define dispatch_branch2() { it = (*it)->fBranch2->fInstructions.begin(); dispatch_first(); }
            
            #define dispatch_return() { it = pop_addr(); dispatch_first(); }
            #define save_return() { push_addr(it + 1); }
            #define empty_return() (addr_stack_index == 0)
            
            
            /*
            #define dispatch_first() { printf("int_stack_index = %d real_stack_index = %d\n",int_stack_index, real_stack_index); (*it)->dump(); goto *fDispatchTable[(*it)->fOpcode]; }
            #define dispatch() { assert(real_stack_index >=0); assert(int_stack_index >=0); printf("real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index); it++; (*it)->write();  goto *fDispatchTable[(*it)->fOpcode]; }
            */
            
            static void* fDispatchTable[] = {
                
                // Numbers
                &&do_kRealValue, &&do_kIntValue,
                
                // Memory
                &&do_kLoadReal, &&do_kLoadInt,
                &&do_kStoreReal, &&do_kStoreInt,
                &&do_kStoreRealValue, &&do_kStoreIntValue,
                &&do_kLoadIndexedReal, &&do_kLoadIndexedInt,
                &&do_kStoreIndexedReal, &&do_kStoreIndexedInt,
                &&do_kMoveReal, &&do_kMoveInt,
                &&do_kLoadInput, &&do_kStoreOutput,
                
                // Cast
                &&do_kCastReal, &&do_kCastInt,
                &&do_kCastRealHeap, &&do_kCastIntHeap,
                
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
                
                // Standard math (stack version)
                &&do_kAddRealStack, &&do_kAddIntStack, &&do_kSubRealStack, &&do_kSubIntStack,
                &&do_kMultRealStack, &&do_kMultIntStack, &&do_kDivRealStack, &&do_kDivIntStack,
                &&do_kRemRealStack, &&do_kRemIntStack, &&do_kLshIntStack, &&do_kRshIntStack, &&do_kGTIntStack,
                &&do_kLTIntStack, &&do_kGEIntStack, &&do_kLEIntStack, &&do_kEQIntStack, &&do_kNEIntStack,
                &&do_kGTRealStack, &&do_kLTRealStack, &&do_kGERealStack,
                &&do_kLERealStack, &&do_kEQRealStack, &&do_kNERealStack,
                &&do_kANDIntStack, &&do_kORIntStack, &&do_kXORIntStack,
                
                // Standard math (stack/value version)
                &&do_kAddRealStackValue, &&do_kAddIntStackValue, &&do_kSubRealStackValue, &&do_kSubIntStackValue,
                &&do_kMultRealStackValue, &&do_kMultIntStackValue, &&do_kDivRealStackValue, &&do_kDivIntStackValue,
                &&do_kRemRealStackValue, &&do_kRemIntStackValue, &&do_kLshIntStackValue, &&do_kRshIntStackValue, &&do_kGTIntStackValue,
                &&do_kLTIntStackValue, &&do_kGEIntStackValue, &&do_kLEIntStackValue, &&do_kEQIntStackValue, &&do_kNEIntStackValue,
                &&do_kGTRealStackValue, &&do_kLTRealStackValue, &&do_kGERealStackValue,
                &&do_kLERealStackValue, &&do_kEQRealStackValue, &&do_kNERealStackValue,
                &&do_kANDIntStackValue, &&do_kORIntStackValue, &&do_kXORIntStackValue,
    
                // Standard math (Value version)
                &&do_kAddRealValue, &&do_kAddIntValue, &&do_kSubRealValue, &&do_kSubIntValue,
                &&do_kMultRealValue, &&do_kMultIntValue, &&do_kDivRealValue, &&do_kDivIntValue,
                &&do_kRemRealValue, &&do_kRemIntValue, &&do_kLshIntValue, &&do_kRshIntValue, &&do_kGTIntValue,
                &&do_kLTIntValue, &&do_kGEIntValue, &&do_kLEIntValue, &&do_kEQIntValue, &&do_kNEIntValue,
                &&do_kGTRealValue, &&do_kLTRealValue, &&do_kGERealValue,
                &&do_kLERealValue, &&do_kEQRealValue, &&do_kNERealValue,
                &&do_kANDIntValue, &&do_kORIntValue, &&do_kXORIntValue,
                
                // Standard math (Value version) : non commutative operations
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
                &&do_kIf,
                &&do_kCondBranch
                
            };
            
            int real_stack_index = 0;
            int int_stack_index = 0;
            int addr_stack_index = 0;
            
            T real_stack[fRealStackSize];
            int int_stack[fIntStackSize];
            InstructionIT address_stack[32];
            
            int max_real_stack = 0;
            int max_int_stack = 0;
            
            InstructionIT it = block->fInstructions.begin();
            dispatch_first();
            
            while (true) {
                
                // Number operations
                do_kRealValue:
                {
                    push_real((*it)->fRealValue);
                    dispatch_next();
                }
                
                do_kIntValue:
                {
                    push_int((*it)->fIntValue);
                    dispatch_next();
                }
                    
                // Memory operations
                do_kLoadReal:
                {
                    push_real(fRealHeap[(*it)->fOffset1]);
                    dispatch_next();
                }
                    
                do_kLoadInt:
                {
                    push_int(fIntHeap[(*it)->fOffset1]);
                    dispatch_next();
                }
                    
                do_kStoreReal:
                {
                    fRealHeap[(*it)->fOffset1] = pop_real();
                    dispatch_next();
                }
                    
                do_kStoreInt:
                {
                    fIntHeap[(*it)->fOffset1] = pop_int();
                    dispatch_next();
                }
                
                // Directly store a value
                do_kStoreRealValue:
                {
                    fRealHeap[(*it)->fOffset1] = (*it)->fRealValue;
                    dispatch_next();
                }
                
                do_kStoreIntValue:
                {
                    fIntHeap[(*it)->fOffset1] = (*it)->fIntValue;
                    dispatch_next();
                }
                
                do_kLoadIndexedReal:
                {
                    push_real(fRealHeap[(*it)->fOffset1 + pop_int()]);
                    dispatch_next();
                }
                    
                do_kLoadIndexedInt:
                {
                    int offset = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1 + offset]);
                    dispatch_next();
                }
                
                do_kStoreIndexedReal:
                {
                    fRealHeap[(*it)->fOffset1 + pop_int()] = pop_real();
                    dispatch_next();
                }
                
                do_kStoreIndexedInt:
                {
                    int offset = pop_int();
                    fIntHeap[(*it)->fOffset1 + offset] = pop_int();
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
                
                // Input/output access
                do_kLoadInput:
                {
                    push_real(fInputs[(*it)->fOffset1][pop_int()]);
                    dispatch_next();
                }
                    
                do_kStoreOutput:
                {
                    fOutputs[(*it)->fOffset1][pop_int()] = pop_real();
                    dispatch_next();
                }
                
                // Cast operations
                do_kCastReal:
                {
                    push_real(T(pop_int()));
                    dispatch_next();
                }
                
                do_kCastRealHeap:
                {
                    push_real(T(fIntHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kCastInt:
                {
                    push_int(int(pop_real()));
                    dispatch_next();
                }
                
                do_kCastIntHeap:
                {
                    push_int(int(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                //-------------------------------------------------------
                // Standard math operations : 'stack' OP 'stack' version
                //-------------------------------------------------------
                
                do_kAddReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 + v2);
                    dispatch_next();
                }
              
                do_kAddInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 + v2);
                    dispatch_next();
                }
                
                do_kSubReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 - v2);
                    dispatch_next();
                }
                
                do_kSubInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 - v2);
                    dispatch_next();
                }
                
                do_kMultReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 * v2);
                    dispatch_next();
                }
                
                do_kMultInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 * v2);
                    dispatch_next();
                }
                
                do_kDivReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 / v2);
                    dispatch_next();
                }
                
                do_kDivInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 / v2);
                    dispatch_next();
                }
                    
                do_kRemReal:
                {
                //    T v1 = pop_real();
                //    T v2 = pop_real();
                //    push_real(v1 % v2);
                //    dispatch_next();
                }
                
                do_kRemInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
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
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 > v2);
                    dispatch_next();
                }
                
                do_kLTReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 < v2);
                    dispatch_next();
                }
                
                do_kGEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 >= v2);
                    dispatch_next();
                }
                
                do_kLEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 <= v2);
                    dispatch_next();
                }
                
                do_kEQReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 == v2);
                    dispatch_next();
                }
                
                do_kNEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
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
                    push_real(fRealHeap[(*it)->fOffset1] + fRealHeap[(*it)->fOffset2]);
                    dispatch_next();
                }
                
                do_kAddIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] + fIntHeap[(*it)->fOffset2]);
                    dispatch_next();
                }
                
                do_kSubRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] - fRealHeap[(*it)->fOffset2]);
                    dispatch_next();
                }
                
                do_kSubIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] - fIntHeap[(*it)->fOffset2]);
                    dispatch_next();
                }
                
                do_kMultRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] * fRealHeap[(*it)->fOffset2]);
                    dispatch_next();
                }
                
                do_kMultIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] * fIntHeap[(*it)->fOffset2]);
                    dispatch_next();
                }
                
                do_kDivRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] / fRealHeap[(*it)->fOffset2]);
                    dispatch_next();
                }
                
                do_kDivIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] / fIntHeap[(*it)->fOffset2]);
                    dispatch_next();
                }
                
                do_kRemRealHeap:
                {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    dispatch_next();
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
                    T v1 = pop_real();
                    push_real(fRealHeap[(*it)->fOffset1] + v1);
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
                    T v1 = pop_real();
                    push_real(fRealHeap[(*it)->fOffset1] - v1);
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
                    T v1 = pop_real();
                    push_real(fRealHeap[(*it)->fOffset1] * v1);
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
                    T v1 = pop_real();
                    push_real(fRealHeap[(*it)->fOffset1] / v1);
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
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    dispatch_next();
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
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] > v1);
                    dispatch_next();
                }
                
                do_kLTRealStack:
                {
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] < v1);
                    dispatch_next();
                }
                
                do_kGERealStack:
                {
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] >= v1);
                    dispatch_next();
                }
                
                do_kLERealStack:
                {
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] <= v1);
                    dispatch_next();
                }
                
                do_kEQRealStack:
                {
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] == v1);
                    dispatch_next();
                }
                
                do_kNERealStack:
                {
                    T v1 = pop_real();
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
                
                //-----------------------------------------------------
                // Standard math operations : 'stack' OP 'value' version
                //-----------------------------------------------------
                
                do_kAddRealStackValue:
                {
                    T v1 = pop_real();
                    push_real((*it)->fRealValue + v1);
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
                    T v1 = pop_real();
                    push_real((*it)->fRealValue - v1);
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
                    T v1 = pop_real();
                    push_real((*it)->fRealValue * v1);
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
                    T v1 = pop_real();
                    push_real((*it)->fRealValue / v1);
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
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    dispatch_next();
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
                    T v1 = pop_real();
                    push_int((*it)->fRealValue > v1);
                    dispatch_next();
                }
                
                do_kLTRealStackValue:
                {
                    T v1 = pop_real();
                    push_int((*it)->fRealValue < v1);
                    dispatch_next();
                }
                
                do_kGERealStackValue:
                {
                    T v1 = pop_real();
                    push_int((*it)->fRealValue >= v1);
                    dispatch_next();
                }
                
                do_kLERealStackValue:
                {
                    T v1 = pop_real();
                    push_int((*it)->fRealValue <= v1);
                    dispatch_next();
                }
                
                do_kEQRealStackValue:
                {
                    T v1 = pop_real();
                    push_int((*it)->fRealValue == v1);
                    dispatch_next();
                }
                
                do_kNERealStackValue:
                {
                    T v1 = pop_real();
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
      
                //-------------------------------------------------------
                // Standard math operations : 'value' OP 'heap' version
                //-------------------------------------------------------
                
                do_kAddRealValue:
                {
                    push_real((*it)->fRealValue + fRealHeap[(*it)->fOffset1]);
                    dispatch_next();
                }
                
                do_kAddIntValue:
                {
                    push_int((*it)->fIntValue + fIntHeap[(*it)->fOffset1]);
                    dispatch_next();
                }
                
                do_kSubRealValue:
                {
                    push_real((*it)->fRealValue - fRealHeap[(*it)->fOffset1]);
                    dispatch_next();
                }
                
                do_kSubIntValue:
                {
                    push_int((*it)->fIntValue - fIntHeap[(*it)->fOffset1]);
                    dispatch_next();
                }
                
                do_kMultRealValue:
                {
                    push_real((*it)->fRealValue * fRealHeap[(*it)->fOffset1]);
                    dispatch_next();
                }
                
                do_kMultIntValue:
                {
                    push_int((*it)->fIntValue * fIntHeap[(*it)->fOffset1]);
                    dispatch_next();
                }
                
                do_kDivRealValue:
                {
                    push_real((*it)->fRealValue / fRealHeap[(*it)->fOffset1]);
                    dispatch_next();
                }
                
                do_kDivIntValue:
                {
                    push_int((*it)->fIntValue / fIntHeap[(*it)->fOffset1]);
                    dispatch_next();
                }
                
                do_kRemRealValue:
                {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    dispatch_next();
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
                    push_real(fRealHeap[(*it)->fOffset1] - (*it)->fRealValue);
                    dispatch_next();
                }
                
                do_kSubIntValueInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] - (*it)->fIntValue);
                    dispatch_next();
                }
                
                do_kDivRealValueInvert:
                {
                    push_real(fRealHeap[(*it)->fOffset1] / (*it)->fRealValue);
                    dispatch_next();
                }
                
                do_kDivIntValueInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] / (*it)->fIntValue);
                    dispatch_next();
                }
                
                do_kRemRealValueInvert:
                {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    dispatch_next();
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
                    push_int(abs(v));
                    dispatch_next();
                }
                
                do_kAbsf:
                {
                    T v = pop_real();
                    push_real(fabsf(v));
                    dispatch_next();
                }
                
                do_kAcosf:
                {
                    T v = pop_real();
                    push_real(acosf(v));
                    dispatch_next();
                }
                
                do_kAsinf:
                {
                    T v = pop_real();
                    push_real(asinf(v));
                    dispatch_next();
                }
                
                do_kAtanf:
                {
                    T v = pop_real();
                    push_real(atanf(v));
                    dispatch_next();
                }
                
                do_kCeilf:
                {
                    T v = pop_real();
                    push_real(ceilf(v));
                    dispatch_next();
                }
                
                do_kCosf:
                {
                    T v = pop_real();
                    push_real(cosf(v));
                    dispatch_next();
                }
                
                do_kCoshf:
                {
                    T v = pop_real();
                    push_real(coshf(v));
                    dispatch_next();
                }
                
                do_kExpf:
                {
                    T v = pop_real();
                    push_real(expf(v));
                    dispatch_next();
                }

                do_kFloorf:
                {
                    T v = pop_real();
                    push_real(floorf(v));
                    dispatch_next();
                }

                do_kLogf:
                {
                    T v = pop_real();
                    push_real(logf(v));
                    dispatch_next();
                }
                
                do_kLog10f:
                {
                    T v = pop_real();
                    push_real(log10f(v));
                    dispatch_next();
                }
                
                do_kRoundf:
                {
                    T v = pop_real();
                    push_real(roundf(v));
                    dispatch_next();
                }
                
                do_kSinf:
                {
                    T v = pop_real();
                    push_real(sinf(v));
                    dispatch_next();
                }
                
                do_kSinhf:
                {
                    T v = pop_real();
                    push_real(sinhf(v));
                    dispatch_next();
                }
                
                do_kSqrtf:
                {
                    T v = pop_real();
                    push_real(sqrtf(v));
                    dispatch_next();
                }
                
                do_kTanf:
                {
                    T v = pop_real();
                    push_real(tanf(v));
                    dispatch_next();
                }
                
                do_kTanhf:
                {
                    T v = pop_real();
                    push_real(tanhf(v));
                    dispatch_next();
                }
                
                //---------------------
                // Extended binary math
                //---------------------
                
                do_kAtan2f:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(atan2f(v1, v2));
                    dispatch_next();
                }
           
                do_kFmodf:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(fmodf(v1, v2));
                    dispatch_next();
                }
                
                do_kPowf:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(powf(v1, v2));
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
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(std::max(v1, v2));
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
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(std::min(v1, v2));
                    dispatch_next();
                }
                
                //------------------------------------
                // Extended unary math (head version)
                ///------------------------------------
                
                do_kAbsHeap:
                {
                    push_int(abs(fIntHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kAbsfHeap:
                {
                    push_real(fabsf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kAcosfHeap:
                {
                    push_real(acosf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kAsinfHeap:
                {
                    push_real(asinf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kAtanfHeap:
                {
                    push_real(atanf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kCeilfHeap:
                {
                    push_real(ceilf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kCosfHeap:
                {
                    push_real(cosf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kCoshfHeap:
                {
                    push_real(coshf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kExpfHeap:
                {
                    push_real(expf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kFloorfHeap:
                {
                    push_real(floorf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kLogfHeap:
                {
                    push_real(logf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kLog10fHeap:
                {
                    push_real(log10f(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kRoundfHeap:
                {
                    push_real(roundf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kSinfHeap:
                {
                    push_real(sinf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kSinhfHeap:
                {
                    push_real(sinhf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kSqrtfHeap:
                {
                    push_real(sqrtf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kTanfHeap:
                {
                    push_real(tanf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                do_kTanhfHeap:
                {
                    push_real(tanhf(fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }
                
                //-------------------------------------
                // Extended binary math (heap version)
                //-------------------------------------
                
                do_kAtan2fHeap:
                {
                    push_real(atan2f(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatch_next();
                }

                do_kFmodfHeap:
                {
                    push_real(fmodf(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatch_next();
                }

                do_kPowfHeap:
                {
                    push_real(powf(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatch_next();
                }

                do_kMaxHeap:
                {
                    push_int(std::max(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
                    dispatch_next();
                }

                do_kMaxfHeap:
                {
                    push_real(std::max(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatch_next();
                }

                do_kMinHeap:
                {
                    push_int(std::min(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
                    dispatch_next();
                }

                do_kMinfHeap:
                {
                    push_real(std::min(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatch_next();
                }

                //-------------------------------------
                // Extended binary math (Value version)
                //-------------------------------------

                do_kAtan2fValue:
                {
                    push_real(atan2f((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }

                do_kFmodfValue:
                {
                    push_real(fmodf((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }

                do_kPowfValue:
                {
                    push_real(powf((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }

                do_kMaxValue:
                {
                    push_int(std::max((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
                    dispatch_next();
                }

                do_kMaxfValue:
                {
                    push_real(std::max((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }

                do_kMinValue:
                {
                    push_int(std::min((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
                    dispatch_next();
                }

                do_kMinfValue:
                {
                    push_real(std::min((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatch_next();
                }

                //-------------------------------------------------------------------
                // Extended binary math (Value version) : non commutative operations
                //-------------------------------------------------------------------

                do_kAtan2fValueInvert:
                {
                    push_real(atan2f(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    dispatch_next();
                }

                do_kFmodfValueInvert:
                {
                    push_real(fmodf(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    dispatch_next();
                }

                do_kPowfValueInvert:
                {
                    push_real(powf(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
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
                        assert((*it)->fBranch1);
                        dispatch_branch1();
                        // Int value (SelectInt), Real value (SelectFloat), or no value (If)
                    } else {
                        // Execute new block
                        assert((*it)->fBranch2);
                        dispatch_branch2();
                        // Int value (SelectInt), Real value (SelectFloat), or no value (If)
                    }
                 }
                
                do_kCondBranch:
                {
                    // If condition is true, just branch back on the block begining
                    if (pop_int()) {
                        assert((*it)->fBranch1);
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
                    
                    // And start look block (finished by a kCondBranch instruction that points to same block)
                    assert((*it)->fBranch1);
                    dispatch_branch1();
                }
            }
        
            //printf("END real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index);
            
            // Check stack coherency
            assert(real_stack_index == 0 && int_stack_index == 0);
        }
    
    public:
    
        FIRInterpreter(int int_heap_size, int real_heap_size, int sr_offset, int count_offset)
        {
            std::cout << "FIRInterpreter :"
                    << " int_heap_size " << int_heap_size
                    << " real_heap_size "  << real_heap_size
                    << " sr_offset "  << sr_offset
                    << " count_offset "  << count_offset << std::endl;
            
            
            // HEAP
            fRealHeapSize = real_heap_size;
            fIntHeapSize = int_heap_size;
            fSROffset = sr_offset;
            fCountOffset = count_offset;
            fRealHeap = new T[real_heap_size];
            fIntHeap = new int[int_heap_size];
            
            // Initialise HEAP with 0
            memset(fRealHeap, 0, real_heap_size * sizeof(T));
            memset(fIntHeap, 0, int_heap_size * sizeof(int));
            
            // Stack
            fRealStackSize = 256;
            fIntStackSize = 256;
        }
        
        virtual ~FIRInterpreter()
        {
            delete [] fRealHeap;
            delete [] fIntHeap;
        }
 
};

#endif
