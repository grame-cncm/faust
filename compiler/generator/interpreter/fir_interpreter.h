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

#include "faust/audio/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "garbageable.hh"

#include <vector>

// Interpreter

typedef long double quad;

struct FIRInstruction : public virtual Garbageable {

    enum Opcode { 
        // Numbers
        kRealValue1, kRealValue2, kIntValue1, kIntValue2,
        // Memory
        kLoadReal1, kLoadReal2, kLoadInt1, kLoadInt2, 
        kStoreReal1, kStoreReal2, kStoreInt1, kStoreInt2,
        // Cast
        kCastReal1, kCastReal2, kCastInt1, kCastInt2, 
        // Select/if
        kIfInt1, kIfInt2, kIfReal1, kIfReal2,
        // Standar math
        kAddReal1, kAddReal2, kAddInt1, kAddInt2, kSubReal1, kSubReal2, kSubInt1, kSubInt2, 
        kMultReal1, kMultReal2,  kMultInt1, kMultInt2, kDivReal1, kDivReal2, kDivInt1, kDivInt2,
        kRemInt1, kRemInt2, kLshInt1, kLshInt2, kRshInt1, kRshInt2, kGTInt1, kGTInt2,
        kLTInt1, kLTInt2, kGEInt1, kGEInt2, kLEInt1, kLEInt2, kEQInt1, kEQInt2, kNEInt1, kNEInt2, 
        kGTReal1, kGTReal2, kLTReal1, kLTReal2, kGEReal1, kGEReal2, 
        kLEReal1, kLEReal2, kEQReal1, kEQReal2, kNEReal1, kNEReal2,
        kANDInt1, kANDInt2, kORInt1, kORInt2, kXORInt1, kXORInt2, 
        // Trigonometric
        kSin1, kSin2, kCos1, kCos2 
    };
     
};

template <class T>
struct FIRBlockInstruction;

template <class T>
struct FIRBasicInstruction : public FIRInstruction {

    int fOffset;
    Opcode fOpcode;
    int fIntValue;
    T fRealValue;
    
    FIRBlockInstruction<T>* fbranch1;
    FIRBlockInstruction<T>* fbranch2;
    
    FIRBasicInstruction(Opcode opcode, 
        int val_int, T val_real, 
        int offset, 
        FIRBlockInstruction<T>* branch1, 
        FIRBlockInstruction<T>* branch2) 
        : fOpcode(opcode), fIntValue(val_int), fRealValue(val_real), fOffset(offset), fbranch1(branch1), fbranch2(branch2) 
    {}
     
};

template <class T>
struct FIRBlockInstruction : public FIRInstruction {

     std::vector<FIRBasicInstruction<T>*> fInstructions;
     
     virtual ~FIRBlockInstruction()
     {
     
     }
};

template <class T>
class FIRInterpreter : public virtual Garbageable {

    protected :
    
        T* fRealHeap;
        int* fIntHeap;
        
        int fRealHeapSize;
        int fIntHeapSize;
         
        /*
            - Offset in arrays in HEAP can be precomputed when visiting FIR
        */
       
        void ExecuteBlock(FIRBlockInstruction<T>* block, int& res_int, T& res_real, bool is_int_res)
        {
            typename std::vector<FIRBasicInstruction<T>*>::iterator it;
             
            T val1_real;
            T val2_real;
            
            int val1_int;
            int val2_int;
            
            for (it = block->fInstructions.begin(); it != block->fInstructions.end(); it++) {
            
                switch ((*it)->fOpcode) {
                
                    // Number operations
                    case FIRInstruction::kRealValue1:
                        val1_real = (*it)->fRealValue;
                        break;
                        
                    case FIRInstruction::kRealValue2:
                        val2_real = (*it)->fRealValue;
                        break;
                        
                    case FIRInstruction::kIntValue1:
                        val1_int = (*it)->fIntValue;
                        break;
                        
                     case FIRInstruction::kIntValue2:
                        val2_int = (*it)->fIntValue;
                        break;
                    
                    // Memory operations
                    case FIRInstruction::kLoadReal1:
                        val1_real = fRealHeap[(*it)->fOffset];
                        break;
                        
                    case FIRInstruction::kLoadReal2:
                        val2_real = fRealHeap[(*it)->fOffset];
                        break;
                        
                    case FIRInstruction::kLoadInt1:
                        val1_int = fIntHeap[(*it)->fOffset];
                        break;
                        
                    case FIRInstruction::kLoadInt2:
                        val2_int = fIntHeap[(*it)->fOffset];
                        break;
                        
                    case FIRInstruction::kStoreReal1:
                        fRealHeap[(*it)->fOffset] = val1_real;
                        break;
                        
                    case FIRInstruction::kStoreReal2:
                        fRealHeap[(*it)->fOffset] = val2_real;
                        break;
                        
                    case FIRInstruction::kStoreInt1:
                        fIntHeap[(*it)->fOffset] = val1_int;
                        break;
                        
                    case FIRInstruction::kStoreInt2:
                        fIntHeap[(*it)->fOffset] = val2_int;
                        break;
                      
                    // Cast operations
                    case FIRInstruction::kCastReal1:
                        val1_real = T(val1_int);
                        break;
                        
                     case FIRInstruction::kCastReal2:
                        val2_real = T(val1_int);
                        break;
                        
                    case FIRInstruction::kCastInt1:
                        val1_int = int(val1_real);
                        break;
                        
                    case FIRInstruction::kCastInt2:
                        val2_int = int(val1_real);
                        break;
                        
                    // Select operation
                    case FIRInstruction::kIfInt1:
                        val1_int = (val1_int ? ExecuteBlockInt((*it)->fbranch1) : ExecuteBlockInt((*it)->fbranch2));
                        break;
                        
                    case FIRInstruction::kIfInt2:
                        val2_int  = (val1_int ? ExecuteBlockInt((*it)->fbranch1) : ExecuteBlockInt((*it)->fbranch2));
                        break;
                    case FIRInstruction::kIfReal1:
                        val1_real  = (val1_int ? ExecuteBlockReal((*it)->fbranch1) : ExecuteBlockReal((*it)->fbranch2));
                        break;
                        
                    case FIRInstruction::kIfReal2:
                        val2_real  = (val1_int ? ExecuteBlockReal((*it)->fbranch1) : ExecuteBlockReal((*it)->fbranch2));
                        break;
                        
                    // Standard math operations
                    case FIRInstruction::kAddReal1:
                        val1_real = val1_real + val2_real;
                        break;
                        
                    case FIRInstruction::kAddReal2:
                        val2_real = val1_real + val2_real;
                        break;
                        
                    case FIRInstruction::kAddInt1:
                        val1_int = val1_int  + val2_int;
                        break;
                        
                    case FIRInstruction::kAddInt2:
                        val2_int = val1_int  + val2_int;
                        break;
                        
                    case FIRInstruction::kSubReal1:
                        val1_real = val1_real - val2_real;
                        break;
                        
                    case FIRInstruction::kSubReal2:
                        val2_real = val1_real - val2_real;
                        break;
                        
                    case FIRInstruction::kSubInt1:
                        val1_int = val1_int - val2_int;
                        break;
                        
                    case FIRInstruction::kSubInt2:
                        val2_int = val1_int - val2_int;
                        break;
                        
                    case FIRInstruction::kMultReal1:
                        val1_real = val1_real * val2_real;
                        break;
                        
                    case FIRInstruction::kMultReal2:
                        val2_real = val1_real * val2_real;
                        break;
                        
                    case FIRInstruction::kMultInt1:
                        val1_int = val1_int * val2_int;
                        break;
                        
                     case FIRInstruction::kMultInt2:
                        val2_int = val1_int * val2_int;
                        break;
                        
                    case FIRInstruction::kDivReal1:
                        val1_real = val1_real / val2_real;
                        break;
                        
                    case FIRInstruction::kDivReal2:
                        val2_real = val1_real / val2_real;
                        break;
                        
                    case FIRInstruction::kDivInt1:
                        val1_int = val1_int / val2_int;
                        break;
                        
                     case FIRInstruction::kDivInt2:
                        val2_int = val1_int / val2_int;
                        break;
                        
                    case FIRInstruction::kRemInt1:
                        val1_int = val1_int % val2_int;
                        break;
                        
                    case FIRInstruction::kRemInt2:
                        val2_int = val1_int % val2_int;
                        break;
                    
                    // Shift operation
                    case FIRInstruction::kLshInt1:
                        val1_int = val1_int << val2_int;
                        break;
                        
                    case FIRInstruction::kLshInt2:
                        val2_int = val1_int << val2_int;
                        break;
                        
                    case FIRInstruction::kRshInt1:
                        val1_int = val1_int >> val2_int;
                        break;
                        
                    case FIRInstruction::kRshInt2:
                        val2_int = val1_int >> val2_int;
                        break;
                     
                    // Comparaison Int
                    case FIRInstruction::kGTInt1:
                        val1_int = val1_int > val2_int;
                        break;
                        
                    case FIRInstruction::kGTInt2:
                        val2_int = val1_int > val2_int;
                        break;
                        
                    case FIRInstruction::kLTInt1:
                        val1_int = val1_int < val2_int;
                        break;
                        
                    case FIRInstruction::kLTInt2:
                        val2_int = val1_int < val2_int;
                        break;
                        
                    case FIRInstruction::kGEInt1:
                        val1_int = val1_int >= val2_int;
                        break;
                        
                    case FIRInstruction::kGEInt2:
                        val2_int = val1_int >= val2_int;
                        break;
                        
                    case FIRInstruction::kLEInt1:
                        val1_int = val1_int <= val2_int;
                        break;
                        
                     case FIRInstruction::kLEInt2:
                        val2_int = val1_int <= val2_int;
                        break;
                    
                    case FIRInstruction::kEQInt1:
                        val1_int = val1_int == val2_int;
                        break;
                        
                    case FIRInstruction::kEQInt2:
                        val2_int = val1_int == val2_int;
                        break;
                        
                    case FIRInstruction::kNEInt1:
                        val1_int = val1_int != val2_int;
                        break;
                        
                     case FIRInstruction::kNEInt2:
                        val2_int = val1_int != val2_int;
                        break;
                        
                    // Comparaison Real    
                    case FIRInstruction::kGTReal1:
                        val1_int = val1_real > val2_real;
                        break;
                        
                    case FIRInstruction::kGTReal2:
                        val2_int = val1_real > val2_real;
                        break;
                        
                    case FIRInstruction::kLTReal1:
                        val1_int = val1_real < val2_real;
                        break;
                        
                    case FIRInstruction::kLTReal2:
                        val2_int = val1_real < val2_real;
                        break;
                        
                    case FIRInstruction::kGEReal1:
                        val1_int = val1_real >= val2_real;
                        break;
                        
                    case FIRInstruction::kGEReal2:
                        val2_int = val1_real >= val2_real;
                        break;
                        
                    case FIRInstruction::kLEReal1:
                        val1_int = val1_real <= val2_real;
                        break;
                        
                     case FIRInstruction::kLEReal2:
                        val2_int = val1_real <= val2_real;
                        break;
                    
                    case FIRInstruction::kEQReal1:
                        val1_int = val1_real == val2_real;
                        break;
                        
                    case FIRInstruction::kEQReal2:
                        val2_int = val1_real == val2_real;
                        break;
                        
                    case FIRInstruction::kNEReal1:
                        val1_int = val1_real != val2_real;
                        break;
                        
                    case FIRInstruction::kNEReal2:
                        val2_int = val1_real != val2_real;
                        break;
                    
                    // Logical operations
                    case FIRInstruction::kANDInt1:
                        val1_int = val1_int & val2_int;
                        break;
                        
                    case FIRInstruction::kANDInt2:
                        val2_int = val1_int & val2_int;
                        break;
                     
                    case FIRInstruction::kORInt1:
                        val1_int = val1_int | val2_int;
                        break;
                        
                    case FIRInstruction::kORInt2:
                        val2_int = val1_int | val2_int;
                        break;
                        
                    case FIRInstruction::kXORInt1:
                        val1_int = val1_int ^  val2_int;
                        break;
                        
                    case FIRInstruction::kXORInt2:
                        val2_int = val1_int ^  val2_int;
                        break;
                       
                    // Other Math operations
                    case FIRInstruction::kSin1:
                        val1_real = sinf(val1_real);
                        break;
                        
                    case FIRInstruction::kSin2:
                        val2_real = sinf(val1_real);
                        break;
                        
                    case FIRInstruction::kCos1:
                        val1_real = cosf(val1_real);
                        break;
                    
                    case FIRInstruction::kCos2:
                        val2_real = cosf(val1_real);
                        break;
            
                }
            }
            
            if (is_int_res) {
                res_int = val1_int;
            } else {
                res_real = val1_real;
            }
        }
        
        int ExecuteBlockInt(FIRBlockInstruction<T>* block)
        {
            int res_int;
            T res_real;
            ExecuteBlock(block, res_int, res_real, true);
            return res_int;
        }
        
        T ExecuteBlockReal(FIRBlockInstruction<T>* block)
        {
            int res_int;
            T res_real;
            ExecuteBlock(block, res_int, res_real, false);
            return res_real;
        }
    
    public:
        
        FIRInterpreter(int real_heap_size, int int_heap_size)
        {
            fRealHeapSize = real_heap_size;
            fIntHeapSize = int_heap_size;
            fRealHeap = new T[real_heap_size];
            fIntHeap = new int[int_heap_size];
        }
        
        virtual ~FIRInterpreter()
        {
            // Nothing (since garbageable)
        }
 
};

