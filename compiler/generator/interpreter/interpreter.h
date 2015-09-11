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

struct Instruction : public virtual Garbageable {

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
struct BlockInstruction;

template <class T>
struct BasicInstruction : public Instruction {

    int fOffset;
    Opcode fOpcode;
    int fIntValue;
    T fRealValue;
    
    BlockInstruction<T>* fbranch1;
    BlockInstruction<T>* fbranch2;
    
    BasicInstruction(Opcode opcode, int offset = 0) : fOpcode(opcode), fOffset(offset) {}
     
};

template <class T>
struct BlockInstruction : public Instruction {

     std::vector<BasicInstruction<T>*> fInstructions;
     
     virtual ~BlockInstruction()
     {
     
     }
};

template <class T>
struct FIRInterpreter : public virtual Garbageable {

    T* fRealHeap;
    int* fIntHeap;
     
    /*
        - Offset in arrays in HEAP can be precomputed when visiting FIR
    */
   
    void ExecuteBlock(BlockInstruction<T>* block, int& res_int, T& res_real, bool is_int_res)
    {
        typename std::vector<BasicInstruction<T>*>::iterator it;
         
        T val1_real;
        T val2_real;
        
        int val1_int;
        int val2_int;
        
        for (it = block->fInstructions.begin(); it != block->fInstructions.end(); it++) {
        
            switch ((*it)->fOpcode) {
            
                // Number operations
                case Instruction::kRealValue1:
                    val1_real = (*it)->fRealValue;
                    break;
                    
                case Instruction::kRealValue2:
                    val2_real = (*it)->fRealValue;
                    break;
                    
                case Instruction::kIntValue1:
                    val1_int = (*it)->fIntValue;
                    break;
                    
                 case Instruction::kIntValue2:
                    val2_int = (*it)->fIntValue;
                    break;
                
                // Memory operations
                case Instruction::kLoadReal1:
                    val1_real = fRealHeap[(*it)->fOffset];
                    break;
                    
                case Instruction::kLoadReal2:
                    val2_real = fRealHeap[(*it)->fOffset];
                    break;
                    
                case Instruction::kLoadInt1:
                    val1_int = fIntHeap[(*it)->fOffset];
                    break;
                    
                case Instruction::kLoadInt2:
                    val2_int = fIntHeap[(*it)->fOffset];
                    break;
                    
                case Instruction::kStoreReal1:
                    fRealHeap[(*it)->fOffset] = val1_real;
                    break;
                    
                case Instruction::kStoreReal2:
                    fRealHeap[(*it)->fOffset] = val2_real;
                    break;
                    
                case Instruction::kStoreInt1:
                    fIntHeap[(*it)->fOffset] = val1_int;
                    break;
                    
                case Instruction::kStoreInt2:
                    fIntHeap[(*it)->fOffset] = val2_int;
                    break;
                  
                // Cast operations
                case Instruction::kCastReal1:
                    val1_real = T(val1_int);
                    break;
                    
                 case Instruction::kCastReal2:
                    val2_real = T(val1_int);
                    break;
                    
                case Instruction::kCastInt1:
                    val1_int = int(val1_real);
                    break;
                    
                case Instruction::kCastInt2:
                    val2_int = int(val1_real);
                    break;
                    
                // Select operation
                case Instruction::kIfInt1:
                    val1_int = (val1_int ? ExecuteBlockInt((*it)->fbranch1) : ExecuteBlockInt((*it)->fbranch2));
                    break;
                    
                case Instruction::kIfInt2:
                    val2_int  = (val1_int ? ExecuteBlockInt((*it)->fbranch1) : ExecuteBlockInt((*it)->fbranch2));
                    break;
                case Instruction::kIfReal1:
                    val1_real  = (val1_int ? ExecuteBlockReal((*it)->fbranch1) : ExecuteBlockReal((*it)->fbranch2));
                    break;
                    
                case Instruction::kIfReal2:
                    val2_real  = (val1_int ? ExecuteBlockReal((*it)->fbranch1) : ExecuteBlockReal((*it)->fbranch2));
                    break;
                    
                // Standard math operations
                case Instruction::kAddReal1:
                    val1_real = val1_real + val2_real;
                    break;
                    
                case Instruction::kAddReal2:
                    val2_real = val1_real + val2_real;
                    break;
                    
                case Instruction::kAddInt1:
                    val1_int = val1_int  + val2_int;
                    break;
                    
                case Instruction::kAddInt2:
                    val2_int = val1_int  + val2_int;
                    break;
                    
                case Instruction::kSubReal1:
                    val1_real = val1_real - val2_real;
                    break;
                    
                case Instruction::kSubReal2:
                    val2_real = val1_real - val2_real;
                    break;
                    
                case Instruction::kSubInt1:
                    val1_int = val1_int - val2_int;
                    break;
                    
                case Instruction::kSubInt2:
                    val2_int = val1_int - val2_int;
                    break;
                    
                case Instruction::kMultReal1:
                    val1_real = val1_real * val2_real;
                    break;
                    
                case Instruction::kMultReal2:
                    val2_real = val1_real * val2_real;
                    break;
                    
                case Instruction::kMultInt1:
                    val1_int = val1_int * val2_int;
                    break;
                    
                 case Instruction::kMultInt2:
                    val2_int = val1_int * val2_int;
                    break;
                    
                case Instruction::kDivReal1:
                    val1_real = val1_real / val2_real;
                    break;
                    
                case Instruction::kDivReal2:
                    val2_real = val1_real / val2_real;
                    break;
                    
                case Instruction::kDivInt1:
                    val1_int = val1_int / val2_int;
                    break;
                    
                 case Instruction::kDivInt2:
                    val2_int = val1_int / val2_int;
                    break;
                    
                case Instruction::kRemInt1:
                    val1_int = val1_int % val2_int;
                    break;
                    
                case Instruction::kRemInt2:
                    val2_int = val1_int % val2_int;
                    break;
                
                // Shift operation
                case Instruction::kLshInt1:
                    val1_int = val1_int << val2_int;
                    break;
                    
                case Instruction::kLshInt2:
                    val2_int = val1_int << val2_int;
                    break;
                    
                case Instruction::kRshInt1:
                    val1_int = val1_int >> val2_int;
                    break;
                    
                case Instruction::kRshInt2:
                    val2_int = val1_int >> val2_int;
                    break;
                 
                // Comparaison Int
                case Instruction::kGTInt1:
                    val1_int = val1_int > val2_int;
                    break;
                    
                case Instruction::kGTInt2:
                    val2_int = val1_int > val2_int;
                    break;
                    
                case Instruction::kLTInt1:
                    val1_int = val1_int < val2_int;
                    break;
                    
                case Instruction::kLTInt2:
                    val2_int = val1_int < val2_int;
                    break;
                    
                case Instruction::kGEInt1:
                    val1_int = val1_int >= val2_int;
                    break;
                    
                case Instruction::kGEInt2:
                    val2_int = val1_int >= val2_int;
                    break;
                    
                case Instruction::kLEInt1:
                    val1_int = val1_int <= val2_int;
                    break;
                    
                 case Instruction::kLEInt2:
                    val2_int = val1_int <= val2_int;
                    break;
                
                case Instruction::kEQInt1:
                    val1_int = val1_int == val2_int;
                    break;
                    
                case Instruction::kEQInt2:
                    val2_int = val1_int == val2_int;
                    break;
                    
                case Instruction::kNEInt1:
                    val1_int = val1_int != val2_int;
                    break;
                    
                 case Instruction::kNEInt2:
                    val2_int = val1_int != val2_int;
                    break;
                    
                // Comparaison Real    
                case Instruction::kGTReal1:
                    val1_int = val1_real > val2_real;
                    break;
                    
                case Instruction::kGTReal2:
                    val2_int = val1_real > val2_real;
                    break;
                    
                case Instruction::kLTReal1:
                    val1_int = val1_real < val2_real;
                    break;
                    
                case Instruction::kLTReal2:
                    val2_int = val1_real < val2_real;
                    break;
                    
                case Instruction::kGEReal1:
                    val1_int = val1_real >= val2_real;
                    break;
                    
                case Instruction::kGEReal2:
                    val2_int = val1_real >= val2_real;
                    break;
                    
                case Instruction::kLEReal1:
                    val1_int = val1_real <= val2_real;
                    break;
                    
                 case Instruction::kLEReal2:
                    val2_int = val1_real <= val2_real;
                    break;
                
                case Instruction::kEQReal1:
                    val1_int = val1_real == val2_real;
                    break;
                    
                case Instruction::kEQReal2:
                    val2_int = val1_real == val2_real;
                    break;
                    
                case Instruction::kNEReal1:
                    val1_int = val1_real != val2_real;
                    break;
                    
                case Instruction::kNEReal2:
                    val2_int = val1_real != val2_real;
                    break;
                
                // Logical operations
                case Instruction::kANDInt1:
                    val1_int = val1_int & val2_int;
                    break;
                    
                case Instruction::kANDInt2:
                    val2_int = val1_int & val2_int;
                    break;
                 
                case Instruction::kORInt1:
                    val1_int = val1_int | val2_int;
                    break;
                    
                case Instruction::kORInt2:
                    val2_int = val1_int | val2_int;
                    break;
                    
                case Instruction::kXORInt1:
                    val1_int = val1_int ^  val2_int;
                    break;
                    
                case Instruction::kXORInt2:
                    val2_int = val1_int ^  val2_int;
                    break;
                   
                // Other Math operations
                case Instruction::kSin1:
                    val1_real = sinf(val1_real);
                    break;
                    
                case Instruction::kSin2:
                    val2_real = sinf(val1_real);
                    break;
                    
                case Instruction::kCos1:
                    val1_real = cosf(val1_real);
                    break;
                
                case Instruction::kCos2:
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
    
    int ExecuteBlockInt(BlockInstruction<T>* block)
    {
        int res_int;
        T res_real;
        ExecuteBlock(block, res_int, res_real, true);
        return res_int;
    }
    
    T ExecuteBlockReal(BlockInstruction<T>* block)
    {
        int res_int;
        T res_real;
        ExecuteBlock(block, res_int, res_real, false);
        return res_real;
    }
    
    Interpreter(int real_heap_size, int int_heap_size)
    {
        fRealHeap = new T[real_heap_size];
        fIntHeap = new int[int_heap_size];
    }
    
    virtual ~Interpreter()
    {
        // Nothing (since garbageable)
    }
 
};

