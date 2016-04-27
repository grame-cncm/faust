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

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "fir_opcode.hh"

#include <vector>
#include <string>
#include <math.h>
#include <assert.h>
#include <iostream>

// Interpreter

#define push_real(val) real_stack[real_stack_index++] = val
#define push_int(val) int_stack[int_stack_index++] = val

#define pop_real() (real_stack[--real_stack_index])
#define pop_int() int_stack[--int_stack_index]

typedef long double quad;

template <class T>
struct FIRBlockInstruction;

template <class T>
struct FIRBasicInstruction : public FIRInstruction {

    Opcode fOpcode;
    int fIntValue;
    T fRealValue;
    int fOffset;
    
    FIRBlockInstruction<T>* fbranch1;
    FIRBlockInstruction<T>* fbranch2;
    
    FIRBasicInstruction(Opcode opcode, 
                        int val_int, T val_real, 
                        int offset, 
                        FIRBlockInstruction<T>* branch1, 
                        FIRBlockInstruction<T>* branch2) 
                        : fOpcode(opcode), fIntValue(val_int), fRealValue(val_real), 
                        fOffset(offset), fbranch1(branch1), fbranch2(branch2) 
    {}
    
    FIRBasicInstruction(Opcode opcode, 
                        int val_int, T val_real) 
                        : fOpcode(opcode), fIntValue(val_int), fRealValue(val_real), 
                        fOffset(0), fbranch1(NULL), fbranch2(NULL) 
    {}
    
    FIRBasicInstruction(Opcode opcode, 
                        int val_int, T val_real, int offset) 
                        : fOpcode(opcode), fIntValue(val_int), fRealValue(val_real), 
                        fOffset(offset), fbranch1(NULL), fbranch2(NULL) 
    {}
    
    FIRBasicInstruction(Opcode opcode) 
                        : fOpcode(opcode), fIntValue(0), fRealValue(0), 
                        fOffset(0), fbranch1(NULL), fbranch2(NULL) 
    {}
    
     
    virtual ~FIRBasicInstruction()
    {
        delete fbranch1;
        delete fbranch2;
    }
    
    void dump()
    {
        std::cout << "opcode = " << fOpcode << " " << gFIRInstructionTable[fOpcode]
        << " int = " << fIntValue
        << " real = " << fRealValue
        << " offset = " << fOffset << std::endl;
        if (fbranch1) fbranch1->dump();
        if (fbranch2) fbranch2->dump();
    }
    
};

template <class T>
struct FIRUserInterfaceInstruction : public FIRInstruction {

    Opcode fOpcode;
    int fOffset;
    std::string fLabel;
    std::string fKey;
    std::string fValue;
    T fInit;
    T fMin;
    T fMax;
    T fStep;
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label, T init, T min, T max, T step)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fInit(init), fMin(min), fMax(max), fStep(step)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode)
        :fOpcode(opcode), fOffset(0), fLabel(""), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, const std::string& label)
        :fOpcode(opcode), fOffset(0), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
     
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& label, T min, T max)
        :fOpcode(opcode), fOffset(offset), fLabel(label), fKey(""), fValue(""), fInit(0), fMin(min), fMax(max), fStep(0)
    {}
    
    FIRUserInterfaceInstruction(Opcode opcode, int offset, const std::string& key, const std::string& value)
        :fOpcode(opcode), fOffset(offset), fLabel(""), fKey(key), fValue(value), fInit(0), fMin(0), fMax(0), fStep(0)
    {}
    
    virtual ~FIRUserInterfaceInstruction()
    {}
    
    void dump()
    {
        
    }
    
};

template <class T>
struct FIRUserInterfaceBlockInstruction : public FIRInstruction {

    std::vector<FIRUserInterfaceInstruction<T>*> fInstructions;
     
    virtual ~FIRUserInterfaceBlockInstruction()
    {
        typename std::vector<FIRUserInterfaceInstruction<T>* >::iterator it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            delete(*it);
        }
    }
     
    void push(FIRUserInterfaceInstruction<T>* inst) { fInstructions.push_back(inst); }
    
    void dump()
    {}
    
};

template <class T>
struct FIRBlockInstruction : public FIRInstruction {

    std::vector<FIRBasicInstruction<T>*> fInstructions;
     
    virtual ~FIRBlockInstruction()
    {
        typename std::vector<FIRBasicInstruction<T>* >::iterator it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            delete(*it);
        }
    }
     
    void push(FIRBasicInstruction<T>* inst) { fInstructions.push_back(inst); }
    
    void dump()
    {
        std::cout << "Block size = " << fInstructions.size() << std::endl;
        typename std::vector<FIRBasicInstruction<T>* >::iterator it;
        for (it = fInstructions.begin(); it != fInstructions.end(); it++) {
            (*it)->dump();
        }
    }
};

template <class T>
class FIRInterpreter  {

    protected:
    
        T* fRealHeap;
        int* fIntHeap;
    
        int fRealHeapSize;
        int fIntHeapSize;
        int fSROffset;
    
        int fRealStackSize;
        int fIntStackSize;
        
        FAUSTFLOAT** fInputs;
        FAUSTFLOAT** fOutputs;
        
        void ExecuteBuildUserInterface(FIRUserInterfaceBlockInstruction<T>* block, UI* interface)
        {
            typename std::vector<FIRUserInterfaceInstruction<T>* >::iterator it;
            
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
    
        inline void ExecuteBlock(FIRBlockInstruction<T>* block, int& res_int, T& res_real, int get_result)
        {
            typename std::vector<FIRBasicInstruction<T>* >::iterator it;
             
            int real_stack_index = 0;
            int int_stack_index = 0;
            
            //printf("ExecuteBlock size = %d fRealStackSize = %d fIntStackSize = %d\n", block->fInstructions.size(), fRealStackSize, fIntStackSize); 
        
            T real_stack[fRealStackSize];
            int int_stack[fIntStackSize];
             
            for (it = block->fInstructions.begin(); it != block->fInstructions.end(); it++) {
                
                //printf("fOpcode %d real_stack_index %d int_stack_index %d\n", (*it)->fOpcode, real_stack_index, int_stack_index);
             
                switch ((*it)->fOpcode) {
                        
                    // Number operations
                    case FIRInstruction::kRealValue:
                        push_real((*it)->fRealValue);
                        break;
                         
                    case FIRInstruction::kIntValue:
                        push_int((*it)->fIntValue);
                        break;
                    
                    // Memory operations
                    case FIRInstruction::kLoadReal:
                        push_real(fRealHeap[(*it)->fOffset]);
                        break;
                        
                    case FIRInstruction::kLoadInt:
                        push_int(fIntHeap[(*it)->fOffset]);
                        break;
                        
                    case FIRInstruction::kStoreReal:
                        fRealHeap[(*it)->fOffset] = pop_real();
                        break;
                        
                    case FIRInstruction::kStoreInt:
                        fIntHeap[(*it)->fOffset] = pop_int();
                        break;
                         
                    case FIRInstruction::kLoadIndexedReal:
                        push_real(fRealHeap[(*it)->fOffset + pop_int()]);
                        break;
                        
                    case FIRInstruction::kLoadIndexedInt: {
                        int val = pop_int();
                        push_int(fIntHeap[(*it)->fOffset + val]);
                        break;
                    }
                         
                    case FIRInstruction::kStoreIndexedReal:
                        fRealHeap[(*it)->fOffset + pop_int()] = pop_real();
                        break;
                        
                    case FIRInstruction::kStoreIndexedInt: {
                        int val = pop_int();
                        fIntHeap[(*it)->fOffset + pop_int()] = val;
                        break;
                    }
                        
                    // Input/output access
                    case FIRInstruction::kLoadInput: 
                        push_real(fInputs[(*it)->fOffset][pop_int()]);
                        break;
                        
                    case FIRInstruction::kStoreOutput: {
                        fOutputs[(*it)->fOffset][pop_int()] = pop_real();
                        break;
                    }
                      
                    // Cast operations
                    case FIRInstruction::kCastReal: {
                        push_real(T(pop_int()));
                        break;
                    }
                        
                    case FIRInstruction::kCastInt:
                        push_int(int(pop_real()));
                        break;
                        
                    // Select/If operation
                    case FIRInstruction::kSelectInt: {
                        int cond = pop_int();
                        push_int(cond ? ExecuteBlockInt((*it)->fbranch1) : ExecuteBlockInt((*it)->fbranch2));
                        break;
                    }
                
                    case FIRInstruction::kSelectReal:
                        push_real(pop_int() ? ExecuteBlockInt((*it)->fbranch1) : ExecuteBlockInt((*it)->fbranch2));
                        break;
                        
                    case FIRInstruction::kIf: {
                        if (pop_int()) {
                            ExecuteBlockInt((*it)->fbranch1);
                        } else if ((*it)->fbranch2) { // Execute 'else' block if there is one
                            ExecuteBlockInt((*it)->fbranch2);
                        }
                        break;
                    }
                        
                    // Standard math operations
                    case FIRInstruction::kAddReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_real(v1 + v2);
                        break;
                    }
                        
                    case FIRInstruction::kAddInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 + v2);
                        break;
                    }
       
                    case FIRInstruction::kSubReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_real(v1 - v2);
                        break;
                    }
                        
                    case FIRInstruction::kSubInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 - v2);
                        break;
                    }
                        
                    case FIRInstruction::kMultReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_real(v1 * v2);
                        break;
                    }
                        
                    case FIRInstruction::kMultInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 * v2);
                        break;
                    }
                        
                    case FIRInstruction::kDivReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_real(v1 / v2);
                        break;
                    }
                        
                    case FIRInstruction::kDivInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 / v2);
                        break;
                    }
                    
                    //case FIRInstruction::kRemReal: {
                    //    T v1 = pop_real();
                    //    T v2 = pop_real();
                    //    push_real(v1 % v2);
                    //    break;
                    //}
                        
                    case FIRInstruction::kRemInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 % v2);
                        break;
                    }
                        
                    // Shift operation
                    case FIRInstruction::kLshInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 << v2);
                        break;
                    }
       
                    case FIRInstruction::kRshInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 >> v2);
                        break;
                    }      
                                   
                    // Comparaison Int
                    case FIRInstruction::kGTInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 > v2);
                        break;
                    }         
                                     
                    case FIRInstruction::kLTInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 < v2);
                        break;
                    }      
                                        
                    case FIRInstruction::kGEInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 >= v2);
                        break;
                    }           
                                   
                    case FIRInstruction::kLEInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 <= v2);
                        break;
                    }           
                               
                    case FIRInstruction::kEQInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 == v2);
                        break;
                    }             
                                 
                    case FIRInstruction::kNEInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 != v2);
                        break;
                    }        
                                      
                    // Comparaison Real    
                    case FIRInstruction::kGTReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 > v2);
                        break;
                    }  
                        
                    case FIRInstruction::kLTReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 < v2);
                        break;
                    }  
                         
                    case FIRInstruction::kGEReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 >= v2);
                        break;
                    }  
                        
                    case FIRInstruction::kLEReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 <= v2);
                        break;
                    }  
                    
                    case FIRInstruction::kEQReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 == v2);
                        break;
                    }  
                        
                    case FIRInstruction::kNEReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_int(v1 != v2);
                        break;
                    }  
                    
                    // Logical operations
                    case FIRInstruction::kANDInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 & v2);
                        break;
                    }     
                                                            
                    case FIRInstruction::kORInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 | v2);
                        break;
                    }     
                                                               
                    case FIRInstruction::kXORInt: {
                        int v1 = pop_int();
                        int v2 = pop_int();
                        push_int(v1 ^ v2);
                        break;
                    }                        
                       
                    // Other Math operations
                    case FIRInstruction::kSin: {
                        T v = pop_real();
                        push_real(sinf(v));
                        break;
                    }
                        
                    case FIRInstruction::kCos: {
                        T v = pop_real();
                        push_real(cosf(v));
                        break;
                    }
                        
                    case FIRInstruction::kSqrt: {
                        T v = pop_real();
                        push_real(sqrtf(v));
                        break;
                    }
                        
                    case FIRInstruction::kLoop: {
                        ExecuteLoopBlock((*it)->fbranch1, (*it)->fOffset, (*it)->fIntValue);
                        break;
                    }
                    
                    default:
                        break;
                }
            }
            
            switch (get_result) {
                
                case 0:
                    break;
                    
                case 1:
                    res_int = pop_int();
                    break;
                    
                case 2:
                    res_real = pop_real();
                    break;
            
            }
            
            //printf("real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index);
        }
    
        inline void ExecuteBlockFast(FIRBlockInstruction<T>* block, int& res_int, T& res_real, int get_result)
        {
            int real_stack_index = 0;
            int int_stack_index = 0;
            
            T real_stack[fRealStackSize];
            int int_stack[fIntStackSize];
            
            #define DISPATCH_FIRST() { goto *fDispatchTable[(*it)->fOpcode]; }
            #define DISPATCH() { it++; goto *fDispatchTable[(*it)->fOpcode]; }
            
            static void* fDispatchTable[] = {
                &&do_kHalt,
                
                &&do_kRealValue, &&do_kIntValue,
                
                &&do_kLoadReal, &&do_kLoadInt,
                &&do_kStoreReal, &&do_kStoreInt,
                &&do_kLoadIndexedReal, &&do_kLoadIndexedInt,
                &&do_kStoreIndexedReal, &&do_kStoreIndexedInt,
                &&do_kLoadInput, &&do_kStoreOutput,
                
                &&do_kCastReal, &&do_kCastInt,
                
                &&do_kSelectInt, &&do_kSelectReal, &&do_kIf,
                
                &&do_kAddReal, &&do_kAddInt, &&do_kSubReal, &&do_kSubInt,
                &&do_kMultReal, &&do_kMultInt, &&do_kDivReal, &&do_kDivInt,
                &&do_kRemReal, &&do_kRemInt, &&do_kLshInt, &&do_kRshInt, &&do_kGTInt,
                &&do_kLTInt, &&do_kGEInt, &&do_kLEInt, &&do_kEQInt, &&do_kNEInt,
                &&do_kGTReal, &&do_kLTReal, &&do_kGEReal,
                &&do_kLEReal, &&do_kEQReal, &&do_kNEReal,
                &&do_kANDInt, &&do_kORInt, &&do_kXORInt,
                
                &&do_kSqrt,
                &&do_kSin, &&do_kCos,
                
                &&do_kLoop
            };
            
            //printf("Start\n");
            
            typename std::vector<FIRBasicInstruction<T>* >::iterator it = block->fInstructions.begin();
            DISPATCH_FIRST();
            
            while (1) {
                
                do_kHalt:
                {
                    //printf("do_kHalt\n");
                    break;
                }
                
                // Number operations
                do_kRealValue:
                {
                    push_real((*it)->fRealValue);
                    DISPATCH();
                }
                
                do_kIntValue:
                {
                    push_int((*it)->fIntValue);
                    DISPATCH();
                }
                    
                // Memory operations
                do_kLoadReal:
                {
                    push_real(fRealHeap[(*it)->fOffset]);
                    DISPATCH();
                }
                    
                do_kLoadInt:
                {
                    push_int(fIntHeap[(*it)->fOffset]);
                    DISPATCH();
                }
                    
                do_kStoreReal:
                {
                    fRealHeap[(*it)->fOffset] = pop_real();
                    DISPATCH();
                }
                    
                do_kStoreInt:
                {
                    fIntHeap[(*it)->fOffset] = pop_int();
                    DISPATCH();
                }
                    
                do_kLoadIndexedReal:
                {
                    push_real(fRealHeap[(*it)->fOffset + pop_int()]);
                    DISPATCH();
                }
                    
                do_kLoadIndexedInt:
                {
                    int val = pop_int();
                    push_int(fIntHeap[(*it)->fOffset + val]);
                    DISPATCH();
                }
                
                do_kStoreIndexedReal:
                {
                    fRealHeap[(*it)->fOffset + pop_int()] = pop_real();
                    DISPATCH();
                }
                    
                do_kStoreIndexedInt:
                {
                    int val = pop_int();
                    fIntHeap[(*it)->fOffset + pop_int()] = val;
                    DISPATCH();
                }
                
                // Input/output access
                do_kLoadInput:
                {
                    push_real(fInputs[(*it)->fOffset][pop_int()]);
                    DISPATCH();
                }
                    
                do_kStoreOutput:
                {
                    fOutputs[(*it)->fOffset][pop_int()] = pop_real();
                    DISPATCH();
                }
                
                // Cast operations
                do_kCastReal:
                {
                    push_real(T(pop_int()));
                    DISPATCH();
                }
                
                do_kCastInt:
                {
                    push_int(int(pop_real()));
                    DISPATCH();
                }
                    
                // Select/If operation
                do_kSelectInt:
                {
                    int cond = pop_int();
                    push_int(cond ? ExecuteBlockInt((*it)->fbranch1) : ExecuteBlockInt((*it)->fbranch2));
                    DISPATCH();
                }
                
                do_kSelectReal:
                {
                    push_real(pop_int() ? ExecuteBlockInt((*it)->fbranch1) : ExecuteBlockInt((*it)->fbranch2));
                    DISPATCH();
                }
                
                do_kIf:
                {
                    if (pop_int()) {
                        ExecuteBlockInt((*it)->fbranch1);
                    } else if ((*it)->fbranch2) { // Execute 'else' block if there is one
                        ExecuteBlockInt((*it)->fbranch2);
                    }
                    DISPATCH();
                }
                
                // Standard math operations
                do_kAddReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 + v2);
                    DISPATCH();
                }
                
                do_kAddInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 + v2);
                    DISPATCH();
                }
                
                do_kSubReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 - v2);
                    DISPATCH();
                }
                
                do_kSubInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 - v2);
                    DISPATCH();
                }
                
                do_kMultReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 * v2);
                    DISPATCH();
                }
                
                do_kMultInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 * v2);
                    DISPATCH();
                }
                
                do_kDivReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_real(v1 / v2);
                    DISPATCH();
                }
                
                do_kDivInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 / v2);
                    DISPATCH();
                }
                    
                do_kRemReal:
                {
                //    T v1 = pop_real();
                //    T v2 = pop_real();
                //    push_real(v1 % v2);
                //    DISPATCH();
                }
                
                do_kRemInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 % v2);
                    DISPATCH();
                }
                    
                // Shift operation
                do_kLshInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 << v2);
                    DISPATCH();
                }
                
                do_kRshInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 >> v2);
                    DISPATCH();
                }
                    
                // Comparaison Int
                do_kGTInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 > v2);
                    DISPATCH();
                }
                
                do_kLTInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 < v2);
                    DISPATCH();
                }
                
                do_kGEInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 >= v2);
                    DISPATCH();
                }
                
                do_kLEInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 <= v2);
                    DISPATCH();
                }
                
                do_kEQInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 == v2);
                    DISPATCH();
                }
                
                do_kNEInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 != v2);
                    DISPATCH();
                }
                    
                // Comparaison Real
                do_kGTReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 > v2);
                    DISPATCH();
                }
                
                do_kLTReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 < v2);
                    DISPATCH();
                }
                
                do_kGEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 >= v2);
                    DISPATCH();
                }
                
                do_kLEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 <= v2);
                    DISPATCH();
                }
                
                do_kEQReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 == v2);
                    DISPATCH();
                }
                
                do_kNEReal:
                {
                    T v1 = pop_real();
                    T v2 = pop_real();
                    push_int(v1 != v2);
                    DISPATCH();
                }
                    
                // Logical operations
                do_kANDInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 & v2);
                    DISPATCH();
                }
                
                do_kORInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 | v2);
                    DISPATCH();
                }
                
                do_kXORInt:
                {
                    int v1 = pop_int();
                    int v2 = pop_int();
                    push_int(v1 ^ v2);
                    DISPATCH();
                }
                
                do_kSqrt:
                {
                    T v = pop_real();
                    push_real(sqrtf(v));
                    DISPATCH();
                }
                
                // Other Math operations
                do_kSin:
                {
                    T v = pop_real();
                    push_real(sinf(v));
                    DISPATCH();
                }
                
                do_kCos:
                {
                    T v = pop_real();
                    push_real(cosf(v));
                    DISPATCH();
                }
                
                do_kLoop:
                {
                    ExecuteLoopBlock((*it)->fbranch1, (*it)->fOffset, (*it)->fIntValue);
                    DISPATCH();
                }
            }
            
            switch (get_result) {
                    
                case 0:
                    break;
                    
                case 1:
                    res_int = pop_int();
                    break;
                    
                case 2:
                    res_real = pop_real();
                    break;
                    
            }
            
            //printf("real_stack_index = %d, int_stack_index = %d\n", real_stack_index, int_stack_index);
        }
        
        void ExecuteLoopBlock(FIRBlockInstruction<T>* block, int loop_offset, int loop_count)
        {
            int res_int;
            T res_real;
            
            for (fIntHeap[loop_offset] = 0; fIntHeap[loop_offset] < loop_count; fIntHeap[loop_offset]++) {
                //ExecuteBlock(block, res_int, res_real, 0);
                ExecuteBlockFast(block, res_int, res_real, 0);
            }
        }

        int ExecuteBlockInt(FIRBlockInstruction<T>* block)
        {
            int res_int;
            T res_real;
            ExecuteBlock(block, res_int, res_real, 1);
            return res_int;
        }
    
        T ExecuteBlockReal(FIRBlockInstruction<T>* block)
        {
            int res_int;
            T res_real;
            ExecuteBlock(block, res_int, res_real, 2);
            return res_real;
        }
    
    public:
    
        FIRInterpreter(int real_heap_size, int int_heap_size, int sr_offset)
        {
            printf("FIRInterpreter : real_heap_size = %d int_heap_size = %d sr_offset = %d\n", real_heap_size, int_heap_size, sr_offset);
            
            // HEAP
            fRealHeapSize = real_heap_size;
            fIntHeapSize = int_heap_size;
            fSROffset = sr_offset;
            fRealHeap = new T[real_heap_size];
            fIntHeap = new int[int_heap_size];
            
            // Initialise HEAP with 0
            memset(fRealHeap, 0, real_heap_size * sizeof(T));
            memset(fIntHeap, 0, int_heap_size * sizeof(int));
            
            // Stack
            fRealStackSize = 4096 * 1;
            fIntStackSize = 4096 * 1;
        }
        
        virtual ~FIRInterpreter()
        {
            delete [] fRealHeap;
            delete [] fIntHeap;
        }
 
};

#endif
