/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _FBC_TEMPLATE_COMPILER_H
#define _FBC_TEMPLATE_COMPILER_H

#include <string>
#include <map>
#include <stdio.h>

#include "interpreter_bytecode.hh"
#include "fbc_executor.hh"

/*
 * FBC template compiler, where REAL will be either 'float' or 'double'
 * depending of the compiler choosen option: -single or -double
 */
template <class REAL>
class FBCTemplateCompiler : public FBCExecuteFun<REAL> {

   protected:
      
    // Compile the FBC code used in 'compute'
    void CompileBlock(FBCBlockInstruction<REAL>* block)
    {
        InstructionIT it  = block->fInstructions.begin();
        bool          end = false;
     
        while ((it != block->fInstructions.end()) && !end) {
            //(*it)->write(&std::cout);
         
            switch ((*it)->fOpcode) {
                    
                // Numbers
                case FBCInstruction::kRealValue:
                    it++;
                    break;
             
                case FBCInstruction::kInt32Value:
                    it++;
                    break;
              
                // Memory load/store
                case FBCInstruction::kLoadReal:
                    it++;
                    break;

                case FBCInstruction::kLoadInt:
                    it++;
                    break;
                    
                case FBCInstruction::kStoreReal:
                    it++;
                    break;

                case FBCInstruction::kStoreInt:
                    it++;
                    break;

                // Indexed memory load/store: constant values are added at generation time by CreateBinOp...
                case FBCInstruction::kLoadIndexedReal:
                    it++;
                    break;
             
                case FBCInstruction::kLoadIndexedInt:
                    it++;
                    break;
             
                case FBCInstruction::kLoadSoundFieldInt:
                    it++;
                    break;
                    
                case FBCInstruction::kLoadSoundFieldReal:
                    it++;
                    break;
            
                case FBCInstruction::kStoreIndexedReal:
                    it++;
                    break;
              
                case FBCInstruction::kStoreIndexedInt:
                    it++;
                    break;
           
                // Memory shift
                case FBCInstruction::kBlockShiftReal:
                    it++;
                    break;
              
                case FBCInstruction::kBlockShiftInt:
                    it++;
                    break;
              
                // Input/output
                case FBCInstruction::kLoadInput:
                    it++;
                    break;

                case FBCInstruction::kStoreOutput:
                    it++;
                    break;

                // Cast
                case FBCInstruction::kCastReal:
                    it++;
                    break;
          
                case FBCInstruction::kCastInt:
                    it++;
                    break;
         
                case FBCInstruction::kBitcastInt:
                    it++;
                    break;
          
                case FBCInstruction::kBitcastReal:
                    it++;
                    break;
         
                // Binary math
                case FBCInstruction::kAddReal:
                    it++;
                    break;

                case FBCInstruction::kAddInt:
                    it++;
                    break;

                case FBCInstruction::kSubReal:
                    it++;
                    break;

                case FBCInstruction::kSubInt:
                    it++;
                    break;

                case FBCInstruction::kMultReal:
                    it++;
                    break;

                case FBCInstruction::kMultInt:
                    it++;
                    break;

                case FBCInstruction::kDivReal:
                    it++;
                    break;

                case FBCInstruction::kDivInt:
                    it++;
                    break;

                case FBCInstruction::kRemReal:
                    it++;
                    break;

                case FBCInstruction::kRemInt:
                    it++;
                    break;

                case FBCInstruction::kLshInt:
                    it++;
                    break;

                case FBCInstruction::kARshInt:
                    it++;
                    break;

                case FBCInstruction::kGTInt:
                    it++;
                    break;

                case FBCInstruction::kLTInt:
                    it++;
                    break;

                case FBCInstruction::kGEInt:
                    it++;
                    break;

                case FBCInstruction::kLEInt:
                    it++;
                    break;

                case FBCInstruction::kEQInt:
                    it++;
                    break;

                case FBCInstruction::kNEInt:
                    it++;
                    break;

                case FBCInstruction::kGTReal:
                    it++;
                    break;

                case FBCInstruction::kLTReal:
                    it++;
                    break;

                case FBCInstruction::kGEReal:
                    it++;
                    break;

                case FBCInstruction::kLEReal:
                    it++;
                    break;

                case FBCInstruction::kEQReal:
                    it++;
                    break;

                case FBCInstruction::kNEReal:
                    it++;
                    break;

                case FBCInstruction::kANDInt:
                    it++;
                    break;

                case FBCInstruction::kORInt:
                    it++;
                    break;

                case FBCInstruction::kXORInt:
                    it++;
                    break;

                // Extended unary math
                case FBCInstruction::kAbs:
                    it++;
                    break;

                case FBCInstruction::kAbsf:
                    it++;
                    break;

                case FBCInstruction::kAcosf:
                    it++;
                    break;
                    
                case FBCInstruction::kAcoshf:
                    it++;
                    break;

                case FBCInstruction::kAsinf:
                    it++;
                    break;
                    
                case FBCInstruction::kAsinhf:
                    it++;
                    break;

                case FBCInstruction::kAtanf:
                    it++;
                    break;
                    
                case FBCInstruction::kAtanhf:
                    it++;
                    break;

                case FBCInstruction::kCeilf:
                    it++;
                    break;

                case FBCInstruction::kCosf:
                    it++;
                    break;

                case FBCInstruction::kCoshf:
                    it++;
                    break;

                case FBCInstruction::kExpf:
                    it++;
                    break;

                case FBCInstruction::kFloorf:
                    it++;
                    break;

                case FBCInstruction::kLogf:
                    it++;
                    break;

                case FBCInstruction::kLog10f:
                    it++;
                    break;
                    
                case FBCInstruction::kRintf:
                    it++;
                    break;

                case FBCInstruction::kRoundf:
                    it++;
                    break;

                case FBCInstruction::kSinf:
                    it++;
                    break;

                case FBCInstruction::kSinhf:
                    it++;
                    break;

                case FBCInstruction::kSqrtf:
                    it++;
                    break;

                case FBCInstruction::kTanf:
                    it++;
                    break;

                case FBCInstruction::kTanhf:
                    it++;
                    break;
                    
                case FBCInstruction::kIsnanf:
                    it++;
                    break;
                    
                case FBCInstruction::kIsinff:
                    it++;
                    break;
                    
                case FBCInstruction::kCopysignf:
                    it++;
                    break;

                // Extended binary math
                case FBCInstruction::kAtan2f:
                    it++;
                    break;

                case FBCInstruction::kFmodf:
                    it++;
                    break;

                case FBCInstruction::kPowf:
                    it++;
                    break;

                case FBCInstruction::kMax:
                    it++;
                    break;
    
                case FBCInstruction::kMaxf:
                    it++;
                    break;
 
                case FBCInstruction::kMin:
                    it++;
                    break;

                case FBCInstruction::kMinf:
                    it++;
                    break;
  
                // Control
                case FBCInstruction::kReturn:
                    end = true;
                    break;

                case FBCInstruction::kIf:
                    break;
                    
                case FBCInstruction::kSelectInt:
                    it++;
                    break;
                   
                case FBCInstruction::kSelectReal:
                    it++;
                    break;
            
                case FBCInstruction::kCondBranch:
                    it++;
                    break;
             
                case FBCInstruction::kLoop:
                    it++;
                    break;
             
                default:
                    (*it)->write(&std::cout);
                    faustassert(false);
                    break;
            }
        }
    }
    
   public:
    FBCTemplateCompiler(FBCBlockInstruction<REAL>* fbc_block, soundTable& sound_table)
    :FBCExecuteFun<REAL>(fbc_block, sound_table)
    {
        // Compile the 'compute' function once.
        CompileBlock(fbc_block);
    }

    virtual ~FBCTemplateCompiler()
    {}

    /*
     * The function to be executed each cycle.
     *
     * @param int_heap - the integer heap
     * @param real_heap - the REAL heap
     * @param inputs - the audio inputs
     * @param outputs - the audio outputs
     */
    void Execute(int* int_heap, REAL* real_heap, REAL** inputs, REAL** outputs)
    {}
    
};

#endif
