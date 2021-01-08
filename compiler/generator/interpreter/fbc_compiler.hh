/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef _FBC_COMPILER_H
#define _FBC_COMPILER_H

//#define MIR_BUILD 1

#include "fbc_interpreter.hh"
#ifdef MIR_BUILD
#include "fbc_mir_compiler.hh"
#elif LLVM_BUILD
#include "fbc_llvm_compiler.hh"
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

        // FBC blocks compilation
        //CompileBlock(factory->fComputeBlock);
        CompileBlock(factory->fComputeDSPBlock);
    }

    virtual ~FBCCompiler() {}

    void ExecuteBlock(FBCBlockInstruction<REAL>* block, bool compile)
    {
        if (compile && fCompiledBlocks->find(block) == fCompiledBlocks->end()) {
            CompileBlock(block);
        }

        // The 'DSP' compute block only is compiled..
        if (fCompiledBlocks->find(block) != fCompiledBlocks->end()) {
            ((*fCompiledBlocks)[block])->Execute(this->fIntHeap, this->fRealHeap, this->fInputs, this->fOutputs);
        } else {
            FBCInterpreter<REAL,0>::ExecuteBlock(block);
        }
    }

   protected:
    CompiledBlocksType* fCompiledBlocks;

    void CompileBlock(FBCBlockInstruction<REAL>* block)
    {
        if (fCompiledBlocks->find(block) == fCompiledBlocks->end()) {
        #ifdef MIR_BUILD
            // Run with interp/MIR compiler
            (*fCompiledBlocks)[block] = new FBCMIRCompiler<REAL>(block);
        #elif LLVM_BUILD
            // Run with interp/LLVM compiler
            (*fCompiledBlocks)[block] = new FBCLLVMCompiler<REAL>(block);
        #endif
        } else {
            // std::cout << "FBCCompiler: reuse compiled block" << std::endl;
        }
    }
};

#endif
