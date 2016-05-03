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
            int real_stack_index = 0;
            int int_stack_index = 0;
            int addr_stack_index = 0;
            
            T real_stack[fRealStackSize];
            int int_stack[fIntStackSize];
            InstructionIT address_stack[32];
            
            int max_real_stack = 0;
            int max_int_stack = 0;
            
            //printf("ExecuteBlock\n");
            
            /*
            #define dispatch_first() { (*it)->write(&std::cout); goto *fDispatchTable[(*it)->fOpcode]; }
            #define dispatch() { (*it)->write(&std::cout); printf("int_stack_index = %d real_stack_index = %d\n", int_stack_index, real_stack_index);  \
                                max_real_stack = std::max(max_real_stack, real_stack_index); max_int_stack = std::max(max_int_stack, int_stack_index); \
                                assert(real_stack_index >= 0 && int_stack_index >= 0); \
                                it++; goto *fDispatchTable[(*it)->fOpcode]; }
            */
            
            #define dispatch_first() { goto *fDispatchTable[(*it)->fOpcode]; }
            #define dispatch() { it++; goto *fDispatchTable[(*it)->fOpcode]; }
            
            
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
    
                // Standard math (direct version)
                &&do_kAddRealDirect, &&do_kAddIntDirect, &&do_kSubRealDirect, &&do_kSubIntDirect,
                &&do_kMultRealDirect, &&do_kMultIntDirect, &&do_kDivRealDirect, &&do_kDivIntDirect,
                &&do_kRemRealDirect, &&do_kRemIntDirect, &&do_kLshIntDirect, &&do_kRshIntDirect, &&do_kGTIntDirect,
                &&do_kLTIntDirect, &&do_kGEIntDirect, &&do_kLEIntDirect, &&do_kEQIntDirect, &&do_kNEIntDirect,
                &&do_kGTRealDirect, &&do_kLTRealDirect, &&do_kGERealDirect,
                &&do_kLERealDirect, &&do_kEQRealDirect, &&do_kNERealDirect,
                &&do_kANDIntDirect, &&do_kORIntDirect, &&do_kXORIntDirect,
                
                // Standard math (direct version) : non commutative operations
                &&do_kSubRealDirectInvert, &&do_kSubIntDirectInvert,
                &&do_kDivRealDirectInvert, &&do_kDivIntDirectInvert,
                &&do_kRemRealDirectInvert, &&do_kRemIntDirectInvert,
                &&do_kLshIntDirectInvert, &&do_kRshIntDirectInvert,
                &&do_kGTIntDirectInvert, &&do_kLTIntDirectInvert,
                &&do_kGEIntDirectInvert, &&do_kLEIntDirectInvert,
                &&do_kGTRealDirectInvert, &&do_kLTRealDirectInvert,
                &&do_kGERealDirectInvert, &&do_kLERealDirectInvert,
                
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
                
                // Extended binary math (direct version)
                &&do_kAtan2fDirect,
                &&do_kFmodfDirect,
                &&do_kPowfDirect,
                &&do_kMaxDirect, &&do_kMaxfDirect,
                &&do_kMinDirect, &&do_kMinfDirect,
                
                // Extended binary math (direct version) : non commutative operations
                &&do_kAtan2fDirectInvert,
                &&do_kFmodfDirectInvert,
                &&do_kPowfDirectInvert,
                
                // Control
                &&do_kLoop,
                &&do_kReturn,
                
                // Select/if
                &&do_kIf,
                &&do_kCondBranch
                
            };
            
            InstructionIT it = block->fInstructions.begin();
            dispatch_first();
            
            while (true) {
                
                // Number operations
                do_kRealValue:
                {
                    push_real((*it)->fRealValue);
                    dispatch();
                }
                
                do_kIntValue:
                {
                    push_int((*it)->fIntValue);
                    dispatch();
                }
                    
                // Memory operations
                do_kLoadReal:
                {
                    push_real(fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                    
                do_kLoadInt:
                {
                    push_int(fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                    
                do_kStoreReal:
                {
                    fRealHeap[(*it)->fOffset1] = pop_real();
                    dispatch();
                }
                    
                do_kStoreInt:
                {
                    fIntHeap[(*it)->fOffset1] = pop_int();
                    dispatch();
                }
                    
                do_kLoadIndexedReal:
                {
                    push_real(fRealHeap[(*it)->fOffset1 + pop_int()]);
                    dispatch();
                }
                    
                do_kLoadIndexedInt:
                {
                    int offset = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1 + offset]);
                    dispatch();
                }
                
                do_kStoreIndexedReal:
                {
                    fRealHeap[(*it)->fOffset1 + pop_int()] = pop_real();
                    dispatch();
                }
                
                do_kStoreIndexedInt:
                {
                    int offset = pop_int();
                    fIntHeap[(*it)->fOffset1 + offset] = pop_int();
                    dispatch();
                }
                
                do_kMoveReal:
                {
                    fRealHeap[(*it)->fOffset1] = fRealHeap[(*it)->fOffset2];
                    dispatch();
                }
                
                do_kMoveInt:
                {
                    fIntHeap[(*it)->fOffset1] = fIntHeap[(*it)->fOffset2];
                    dispatch();
                }
                
                // Input/output access
                do_kLoadInput:
                {
                    push_real(fInputs[(*it)->fOffset1][pop_int()]);
                    dispatch();
                }
                    
                do_kStoreOutput:
                {
                    fOutputs[(*it)->fOffset1][pop_int()] = pop_real();
                    dispatch();
                }
                
                // Cast operations
                do_kCastReal:
                {
                    push_real(T(pop_int()));
                    dispatch();
                }
                
                do_kCastRealHeap:
                {
                    push_real(T(fIntHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kCastInt:
                {
                    push_int(int(pop_real()));
                    dispatch();
                }
                
                do_kCastIntHeap:
                {
                    push_int(int(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                //------------------------------------------
                // Standard math operations : stack version
                //------------------------------------------
                
                do_kAddReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 + v2);
                    dispatch();
                }
              
                do_kAddInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 + v2);
                    dispatch();
                }
                
                do_kSubReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 - v2);
                    dispatch();
                }
                
                do_kSubInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 - v2);
                    dispatch();
                }
                
                do_kMultReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 * v2);
                    dispatch();
                }
                
                do_kMultInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 * v2);
                    dispatch();
                }
                
                do_kDivReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 / v2);
                    dispatch();
                }
                
                do_kDivInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 / v2);
                    dispatch();
                }
                    
                do_kRemReal:
                {
                //    T v1 = pop_real();
                //    T v2 = pop_real();
                //    push_real(v1 % v2);
                //    dispatch();
                }
                
                do_kRemInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 % v2);
                    dispatch();
                }
                    
                // Shift operation
                do_kLshInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 << v2);
                    dispatch();
                }
                
                do_kRshInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 >> v2);
                    dispatch();
                }
                    
                // Comparaison Int
                do_kGTInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 > v2);
                    dispatch();
                }
                
                do_kLTInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 < v2);
                    dispatch();
                }
                
                do_kGEInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 >= v2);
                    dispatch();
                }
                
                do_kLEInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 <= v2);
                    dispatch();
                }
                
                do_kEQInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 == v2);
                    dispatch();
                }
                
                do_kNEInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 != v2);
                    dispatch();
                }
                    
                // Comparaison Real
                do_kGTReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 > v2);
                    dispatch();
                }
                
                do_kLTReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 < v2);
                    dispatch();
                }
                
                do_kGEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 >= v2);
                    dispatch();
                }
                
                do_kLEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 <= v2);
                    dispatch();
                }
                
                do_kEQReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 == v2);
                    dispatch();
                }
                
                do_kNEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 != v2);
                    dispatch();
                }
                    
                // Logical operations
                do_kANDInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 & v2);
                    dispatch();
                }
                
                do_kORInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 | v2);
                    dispatch();
                }
                
                do_kXORInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 ^ v2);
                    dispatch();
                }
                
                //-----------------------------------------
                // Standard math operations : heap version
                //-----------------------------------------
                
                do_kAddRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] + fRealHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kAddIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] + fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kSubRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] - fRealHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kSubIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] - fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kMultRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] * fRealHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kMultIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] * fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kDivRealHeap:
                {
                    push_real(fRealHeap[(*it)->fOffset1] / fRealHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kDivIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] / fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kRemRealHeap:
                {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    dispatch();
                }
                
                do_kRemIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] % fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                // Shift operation
                do_kLshIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] << fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kRshIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] >> fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                // Comparaison Int
                do_kGTIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] > fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kLTIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] < fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kGEIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] >= fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kLEIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] <= fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kEQIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] == fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kNEIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] != fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                // Comparaison Real
                do_kGTRealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] > fRealHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kLTRealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] < fRealHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kGERealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] >= fRealHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kLERealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] <= fRealHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kEQRealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] == fRealHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kNERealHeap:
                {
                    push_int(fRealHeap[(*it)->fOffset1] != fRealHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                // Logical operations
                do_kANDIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] & fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kORIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] | fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                do_kXORIntHeap:
                {
                    push_int(fIntHeap[(*it)->fOffset1] ^ fIntHeap[(*it)->fOffset2]);
                    dispatch();
                }
                
                //-----------------------------------------
                // Standard math operations : stack version
                //-----------------------------------------
                
                do_kAddRealStack:
                {
                    T v1 = pop_real();
                    push_real(fRealHeap[(*it)->fOffset1] + v1);
                    dispatch();
                }
                
                do_kAddIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] + v1);
                    dispatch();
                }
                
                do_kSubRealStack:
                {
                    T v1 = pop_real();
                    push_real(fRealHeap[(*it)->fOffset1] - v1);
                    dispatch();
                }
                
                do_kSubIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] - v1);
                    dispatch();
                }
                
                do_kMultRealStack:
                {
                    T v1 = pop_real();
                    push_real(fRealHeap[(*it)->fOffset1] * v1);
                    dispatch();
                }
                
                do_kMultIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] * v1);
                    dispatch();
                }
                
                do_kDivRealStack:
                {
                    T v1 = pop_real();
                    push_real(fRealHeap[(*it)->fOffset1] / v1);
                    dispatch();
                }
                
                do_kDivIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] / v1);
                    dispatch();
                }
                
                do_kRemRealStack:
                {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    dispatch();
                }
                
                do_kRemIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] % v1);
                    dispatch();
                }
                
                // Shift operation
                do_kLshIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] << v1);
                    dispatch();
                }
                
                do_kRshIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] >> v1);
                    dispatch();
                }
                
                // Comparaison Int
                do_kGTIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] > v1);
                    dispatch();
                }
                
                do_kLTIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] < v1);
                    dispatch();
                }
                
                do_kGEIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] >= v1);
                    dispatch();
                }
                
                do_kLEIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] <= v1);
                    dispatch();
                }
                
                do_kEQIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] == v1);
                    dispatch();
                }
                
                do_kNEIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] != v1);
                    dispatch();
                }
                
                // Comparaison Real
                do_kGTRealStack:
                {
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] > v1);
                    dispatch();
                }
                
                do_kLTRealStack:
                {
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] < v1);
                    dispatch();
                }
                
                do_kGERealStack:
                {
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] >= v1);
                    dispatch();
                }
                
                do_kLERealStack:
                {
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] <= v1);
                    dispatch();
                }
                
                do_kEQRealStack:
                {
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] == v1);
                    dispatch();
                }
                
                do_kNERealStack:
                {
                    T v1 = pop_real();
                    push_int(fRealHeap[(*it)->fOffset1] != v1);
                    dispatch();
                }
                
                // Logical operations
                do_kANDIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] & v1);
                    dispatch();
                }
                
                do_kORIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] | v1);
                    dispatch();
                }
                
                do_kXORIntStack:
                {
                    int v1 = pop_int();
                    push_int(fIntHeap[(*it)->fOffset1] ^ v1);
                    dispatch();
                }
                
                //-------------------------------------------
                // Standard math operations : direct version
                //-------------------------------------------
                
                do_kAddRealDirect:
                {
                    push_real((*it)->fRealValue + fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kAddIntDirect:
                {
                    push_int((*it)->fIntValue + fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kSubRealDirect:
                {
                    push_real((*it)->fRealValue - fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kSubIntDirect:
                {
                    push_int((*it)->fIntValue - fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kMultRealDirect:
                {
                    push_real((*it)->fRealValue * fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kMultIntDirect:
                {
                    push_int((*it)->fIntValue * fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kDivRealDirect:
                {
                    push_real((*it)->fRealValue / fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kDivIntDirect:
                {
                    push_int((*it)->fIntValue / fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kRemRealDirect:
                {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    dispatch();
                }
                
                do_kRemIntDirect:
                {
                    push_int((*it)->fIntValue % fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                // Shift operation
                do_kLshIntDirect:
                {
                    push_int((*it)->fIntValue << fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kRshIntDirect:
                {
                    push_int((*it)->fIntValue >> fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                // Comparaison Int
                do_kGTIntDirect:
                {
                    push_int((*it)->fIntValue > fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kLTIntDirect:
                {
                    push_int((*it)->fIntValue < fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kGEIntDirect:
                {
                    push_int((*it)->fIntValue >= fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kLEIntDirect:
                {
                    push_int((*it)->fIntValue <= fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kEQIntDirect:
                {
                    push_int((*it)->fIntValue == fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kNEIntDirect:
                {
                    push_int((*it)->fIntValue != fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                // Comparaison Real
                do_kGTRealDirect:
                {
                    push_int((*it)->fRealValue > fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kLTRealDirect:
                {
                    push_int((*it)->fRealValue < fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kGERealDirect:
                {
                    push_int((*it)->fRealValue >= fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kLERealDirect:
                {
                    push_int((*it)->fRealValue <= fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kEQRealDirect:
                {
                    push_int((*it)->fRealValue == fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kNERealDirect:
                {
                    push_int((*it)->fRealValue != fRealHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                // Logical operations
                do_kANDIntDirect:
                {
                    push_int((*it)->fIntValue & fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kORIntDirect:
                {
                    push_int((*it)->fIntValue | fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                do_kXORIntDirect:
                {
                    push_int((*it)->fIntValue ^ fIntHeap[(*it)->fOffset1]);
                    dispatch();
                }
                
                //----------------------------------------------------
                // Standard math operations : direct inverted version
                // (non commutative operations)
                //----------------------------------------------------
                
                do_kSubRealDirectInvert:
                {
                    push_real(fRealHeap[(*it)->fOffset1] - (*it)->fRealValue);
                    dispatch();
                }
                
                do_kSubIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] - (*it)->fIntValue);
                    dispatch();
                }
                
                do_kDivRealDirectInvert:
                {
                    push_real(fRealHeap[(*it)->fOffset1] / (*it)->fRealValue);
                    dispatch();
                }
                
                do_kDivIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] / (*it)->fIntValue);
                    dispatch();
                }
                
                do_kRemRealDirectInvert:
                {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    dispatch();
                }
                
                do_kRemIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] % (*it)->fIntValue);
                    dispatch();
                }
                
                // Shift operation
                do_kLshIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] << (*it)->fIntValue);
                    dispatch();
                }
                
                do_kRshIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] >> (*it)->fIntValue);
                    dispatch();
                }
                
                // Comparaison Int
                do_kGTIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] > (*it)->fIntValue);
                    dispatch();
                }
                
                do_kLTIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] < (*it)->fIntValue);
                    dispatch();
                }
                
                do_kGEIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] >= (*it)->fIntValue);
                    dispatch();
                }
                
                do_kLEIntDirectInvert:
                {
                    push_int(fIntHeap[(*it)->fOffset1] <= (*it)->fIntValue);
                    dispatch();
                }
                
                // Comparaison Real
                do_kGTRealDirectInvert:
                {
                    push_int(fRealHeap[(*it)->fOffset1] > (*it)->fRealValue);
                    dispatch();
                }
                
                do_kLTRealDirectInvert:
                {
                    push_int(fRealHeap[(*it)->fOffset1] < (*it)->fRealValue);
                    dispatch();
                }
                
                do_kGERealDirectInvert:
                {
                    push_int(fRealHeap[(*it)->fOffset1] >= (*it)->fRealValue);
                    dispatch();
                }
                
                do_kLERealDirectInvert:
                {
                    push_int(fRealHeap[(*it)->fOffset1] <= (*it)->fRealValue);
                    dispatch();
                }
       
                //---------------------
                // Extended unary math
                //---------------------
                
                do_kAbs:
                {
                    int v = pop_int();
                    push_int(abs(v));
                    dispatch();
                }
                
                do_kAbsf:
                {
                    T v = pop_real();
                    push_real(fabsf(v));
                    dispatch();
                }
                
                do_kAcosf:
                {
                    T v = pop_real();
                    push_real(acosf(v));
                    dispatch();
                }
                
                do_kAsinf:
                {
                    T v = pop_real();
                    push_real(asinf(v));
                    dispatch();
                }
                
                do_kAtanf:
                {
                    T v = pop_real();
                    push_real(atanf(v));
                    dispatch();
                }
                
                do_kCeilf:
                {
                    T v = pop_real();
                    push_real(ceilf(v));
                    dispatch();
                }
                
                do_kCosf:
                {
                    T v = pop_real();
                    push_real(cosf(v));
                    dispatch();
                }
                
                do_kCoshf:
                {
                    T v = pop_real();
                    push_real(coshf(v));
                    dispatch();
                }
                
                do_kExpf:
                {
                    T v = pop_real();
                    push_real(expf(v));
                    dispatch();
                }

                do_kFloorf:
                {
                    T v = pop_real();
                    push_real(floorf(v));
                    dispatch();
                }

                do_kLogf:
                {
                    T v = pop_real();
                    push_real(logf(v));
                    dispatch();
                }
                
                do_kLog10f:
                {
                    T v = pop_real();
                    push_real(log10f(v));
                    dispatch();
                }
                
                do_kRoundf:
                {
                    T v = pop_real();
                    push_real(roundf(v));
                    dispatch();
                }
                
                do_kSinf:
                {
                    T v = pop_real();
                    push_real(sinf(v));
                    dispatch();
                }
                
                do_kSinhf:
                {
                    T v = pop_real();
                    push_real(sinhf(v));
                    dispatch();
                }
                
                do_kSqrtf:
                {
                    T v = pop_real();
                    push_real(sqrtf(v));
                    dispatch();
                }
                
                do_kTanf:
                {
                    T v = pop_real();
                    push_real(tanf(v));
                    dispatch();
                }
                
                do_kTanhf:
                {
                    T v = pop_real();
                    push_real(tanhf(v));
                    dispatch();
                }
                
                //---------------------
                // Extended binary math
                //---------------------
                
                do_kAtan2f:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(atan2f(v1, v2));
                    dispatch();
                }
           
                do_kFmodf:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(fmodf(v1, v2));
                    dispatch();
                }
                
                do_kPowf:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(powf(v1, v2));
                    dispatch();
                }
                
                do_kMax:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(std::max(v1, v2));
                    dispatch();
                }
                
                do_kMaxf:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(std::max(v1, v2));
                    dispatch();
                }
                
                do_kMin:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(std::min(v1, v2));
                    dispatch();
                }
                
                do_kMinf:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(std::min(v1, v2));
                    dispatch();
                }
                
                //------------------------------------
                // Extended unary math (head version)
                ///------------------------------------
                
                do_kAbsHeap:
                {
                    push_int(abs(fIntHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kAbsfHeap:
                {
                    push_real(fabsf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kAcosfHeap:
                {
                    push_real(acosf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kAsinfHeap:
                {
                    push_real(asinf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kAtanfHeap:
                {
                    push_real(atanf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kCeilfHeap:
                {
                    push_real(ceilf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kCosfHeap:
                {
                    push_real(cosf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kCoshfHeap:
                {
                    push_real(coshf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kExpfHeap:
                {
                    push_real(expf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kFloorfHeap:
                {
                    push_real(floorf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kLogfHeap:
                {
                    push_real(logf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kLog10fHeap:
                {
                    push_real(log10f(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kRoundfHeap:
                {
                    push_real(roundf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kSinfHeap:
                {
                    push_real(sinf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kSinhfHeap:
                {
                    push_real(sinhf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kSqrtfHeap:
                {
                    push_real(sqrtf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kTanfHeap:
                {
                    push_real(tanf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                do_kTanhfHeap:
                {
                    push_real(tanhf(fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }
                
                //-------------------------------------
                // Extended binary math (heap version)
                //-------------------------------------
                
                do_kAtan2fHeap:
                {
                    push_real(atan2f(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatch();
                }

                do_kFmodfHeap:
                {
                    push_real(fmodf(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatch();
                }

                do_kPowfHeap:
                {
                    push_real(powf(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatch();
                }

                do_kMaxHeap:
                {
                    push_int(std::max(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
                    dispatch();
                }

                do_kMaxfHeap:
                {
                    push_real(std::max(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatch();
                }

                do_kMinHeap:
                {
                    push_int(std::min(fIntHeap[(*it)->fOffset1], fIntHeap[(*it)->fOffset2]));
                    dispatch();
                }

                do_kMinfHeap:
                {
                    push_real(std::min(fRealHeap[(*it)->fOffset1], fRealHeap[(*it)->fOffset2]));
                    dispatch();
                }

                //-------------------------------------
                // Extended binary math (direct version)
                //-------------------------------------

                do_kAtan2fDirect:
                {
                    push_real(atan2f((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }

                do_kFmodfDirect:
                {
                    push_real(fmodf((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }

                do_kPowfDirect:
                {
                    push_real(powf((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }

                do_kMaxDirect:
                {
                    push_int(std::max((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
                    dispatch();
                }

                do_kMaxfDirect:
                {
                    push_real(std::max((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }

                do_kMinDirect:
                {
                    push_int(std::min((*it)->fIntValue, fIntHeap[(*it)->fOffset1]));
                    dispatch();
                }

                do_kMinfDirect:
                {
                    push_real(std::min((*it)->fRealValue, fRealHeap[(*it)->fOffset1]));
                    dispatch();
                }

                //-------------------------------------------------------------------
                // Extended binary math (direct version) : non commutative operations
                //-------------------------------------------------------------------

                do_kAtan2fDirectInvert:
                {
                    push_real(atan2f(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    dispatch();
                }

                do_kFmodfDirectInvert:
                {
                    push_real(fmodf(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    dispatch();
                }

                do_kPowfDirectInvert:
                {
                    push_real(powf(fRealHeap[(*it)->fOffset1], (*it)->fRealValue));
                    dispatch();
                }

                //---------
                // Control
                //---------
                
                do_kReturn:
                {
                    // Empty addr stack = end of computation
                    if (addr_stack_index == 0) {
                        break;
                    } else {
                        it = pop_addr();
                        dispatch_first();
                    }
                }
                
                do_kIf:
                {
                    // Keep next instruction
                    push_addr(it + 1);
                    
                    if (pop_int()) {
                        // Execute new block
                        it = (*it)->fBranch1->fInstructions.begin();
                        // Int value (SelectInt), Real value (SelectFloat), or no value (If)
                    } else {
                        // Execute new block
                        it = (*it)->fBranch2->fInstructions.begin();
                        // Int value (SelectInt), Real value (SelectFloat), or no value (If)
                    }
                    
                    dispatch_first();
                }
                
                do_kCondBranch:
                {
                    if (pop_int()) {
                        // Branch back on 'loop' block
                        it = (*it)->fBranch1->fInstructions.begin();
                        dispatch_first();
                    } else {
                        // Just continue after 'loop block'
                        dispatch();
                    }
                }
                
                do_kLoop:
                {
                    // Keep next instruction
                    push_addr(it + 1);
                    
                    // And start look block
                    it = (*it)->fBranch1->fInstructions.begin();
                    dispatch_first();
                }
            }
        
            //printf("END real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index);
            assert(real_stack_index == 0 && int_stack_index == 0);
        }
        
    public:
    
        FIRInterpreter(int int_heap_size, int real_heap_size, int sr_offset, int count_offset)
        {
            printf("FIRInterpreter : int_heap_size = %d real_heap_size = %d sr_offset = %d\n", int_heap_size, real_heap_size, sr_offset);
            
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
