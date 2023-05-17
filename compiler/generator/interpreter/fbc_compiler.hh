/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef _FBC_COMPILER_H
#define _FBC_COMPILER_H

#include "fbc_interpreter.hh"

#ifdef INTERP_MIR_BUILD
#include "fbc_mir_compiler.hh"
#elif INTERP_LLVM_BUILD
#include "fbc_llvm_compiler.hh"
#elif INTERP_TEMPLATE_BUILD
#include "fbc_template_compiler.hh"
#endif

// FBC compiler
template <class REAL>
class FBCCompiler : public FBCInterpreter<REAL,0> {
   public:
    typedef typename std::map<FBCBlockInstruction<REAL>*, FBCExecuteFun<REAL>*>           CompiledBlocksType;
    typedef typename std::map<FBCBlockInstruction<REAL>*, FBCExecuteFun<REAL>*>::iterator CompiledBlocksTypeIT;

    FBCCompiler(interpreter_dsp_factory_aux<REAL,0>* factory, CompiledBlocksType* map) : FBCInterpreter<REAL,0>(factory)
    {
        fCompiledBlocks = map;
    }

    virtual ~FBCCompiler() {}

    void executeBlock(FBCBlockInstruction<REAL>* block)
    {
        // The 'DSP' compute block only is compiled..
        if (fCompiledBlocks->find(block) != fCompiledBlocks->end()) {
            ((*fCompiledBlocks)[block])->execute(this->fIntHeap, this->fRealHeap, this->fInputs, this->fOutputs);
        } else {
            FBCInterpreter<REAL,0>::executeBlock(block);
        }
    }

   private:
    CompiledBlocksType* fCompiledBlocks;

    void compileBlock(FBCBlockInstruction<REAL>* block)
    {
        if (fCompiledBlocks->find(block) == fCompiledBlocks->end()) {
        #ifdef INTERP_COMP_BUILD
            #ifdef INTERP_MIR_BUILD
                // Run with interp/MIR compiler
                (*fCompiledBlocks)[block] = new FBCMIRCompiler<REAL>(block, this->fSoundTable);
            #elif INTERP_LLVM_BUILD
                // Run with interp/LLVM compiler
                (*fCompiledBlocks)[block] = new FBCLLVMCompiler<REAL>(block, this->fSoundTable);
            #elif INTERP_TEMPLATE_BUILD
                // Run with template compiler
                (*fCompiledBlocks)[block] = new FBCTemplateCompiler<REAL>(block, this->fSoundTable);
            #endif
        #else
            #ifdef WIN32
                #pragma message("warning pure Interpreter mode");
            #else
                #warning pure Interpreter mode
            #endif
        #endif
        } else {
            // std::cout << "FBCCompiler: reuse compiled block" << std::endl;
        }
    }
};

#endif
