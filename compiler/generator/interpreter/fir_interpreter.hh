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
        std::cout << "opcode = " << gFIRInstructionTable[fOpcode]
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
                        //printf("kRealValue %f\n", (*it)->fRealValue);
                        push_real((*it)->fRealValue);
                        break;
                         
                    case FIRInstruction::kIntValue:
                        //printf("kIntValue %d\n", (*it)->fIntValue);
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
                        
                    // Select operation
                    case FIRInstruction::kIfInt: {
                        int cond = pop_int();
                        push_int(cond ? ExecuteBlockInt((*it)->fbranch1) : ExecuteBlockInt((*it)->fbranch2));
                        break;
                    }
                
                    case FIRInstruction::kIfReal:
                        push_real(pop_int() ? ExecuteBlockInt((*it)->fbranch1) : ExecuteBlockInt((*it)->fbranch2));
                        break;
                        
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
                        //printf("kAddInt %d %d\n", v1, v2);
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
                        //printf("kSubInt %d %d\n", v1, v2);
                        push_int(v1 - v2);
                        break;
                    }
                        
                    case FIRInstruction::kMultReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_real(v1 * v2);
                        //printf("kMultReal %f %f %f\n", v1, v2, v1 * v2);
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
                        push_int(v1 / v2);;
                        break;
                    }
                    
                    /*
                    case FIRInstruction::kRemReal: {
                        T v1 = pop_real();
                        T v2 = pop_real();
                        push_real(v1 % v2);
                        break;
                    }
                    */
                        
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
                        //printf("kANDInt %d %d\n", v1, v2);
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
                        printf("kSin1 %f\n", v);
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
    
        void ExecuteLoopBlock(FIRBlockInstruction<T>* block, int loop_offset, int loop_count)
        {
            int res_int;
            T res_real;
            
            for (fIntHeap[loop_offset] = 0; fIntHeap[loop_offset] < loop_count; fIntHeap[loop_offset]++) {
                ExecuteBlock(block, res_int, res_real, 0);
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
