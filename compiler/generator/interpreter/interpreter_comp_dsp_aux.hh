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

#ifndef interpreter_comp_dsp_aux_h
#define interpreter_comp_dsp_aux_h

#include "interpreter_dsp_aux.hh"
#include "fbc_llvm_compiler.hh"
#include "fbc_compiler.hh"

// Interpreter factory using a LLVM compiler for 'compute' method

template <class T, int TRACE>
struct interpreter_comp_dsp_factory_aux : public interpreter_dsp_factory_aux<T,TRACE> {
    
     // Shared between all DSP instances
    typename FBCCompiler<T>::CompiledBlocksType* fCompiledBlocks;

    interpreter_comp_dsp_factory_aux(const std::string& name, const std::string& compile_options, const std::string& sha_key,
                                int version_num, int inputs, int outputs, int int_heap_size, int real_heap_size,
                                int sound_heap_size, int sr_offset, int count_offset, int iota_offset, int opt_level,
                                FIRMetaBlockInstruction* meta, FIRUserInterfaceBlockInstruction<T>* firinterface,
                                FBCBlockInstruction<T>* static_init, FBCBlockInstruction<T>* init,
                                FBCBlockInstruction<T>* resetui, FBCBlockInstruction<T>* clear,
                                FBCBlockInstruction<T>* compute_control, FBCBlockInstruction<T>* compute_dsp)
    : interpreter_dsp_factory_aux<T,TRACE>(name, compile_options, sha_key,
                                  version_num, inputs, outputs, int_heap_size, real_heap_size,
                                  sound_heap_size, sr_offset, count_offset,iota_offset, opt_level,
                                  meta, firinterface,
                                  static_init, init,
                                  resetui, clear,
                                  compute_control, compute_dsp)
    {
        fCompiledBlocks = new std::map<FBCBlockInstruction<T>*, FBCExecuteFun<T>*>();
    }

    virtual FBCExecutor<T>* createFBCExecutor()
    {
        return new FBCCompiler<T>(this, fCompiledBlocks);
    }

    virtual ~interpreter_comp_dsp_factory_aux()
    {
        for (auto& it : *fCompiledBlocks) {
            delete it.second;
        }
        delete fCompiledBlocks;
    }

};

// Interpreter instance using a LLVM compiler for 'compute' method

template <class T, int TRACE>
struct interpreter_comp_dsp_aux : public interpreter_dsp_aux<T,TRACE> {

    interpreter_comp_dsp_aux(interpreter_dsp_factory_aux<T, TRACE>* factory)
    {
        this->fFactory = factory;
        this->fInitialized = false;
        this->fCycle = 0;
        this->fTraceOutput = false;
        this->fFBCExecutor = factory->createFBCExecutor();
    }
    
};

#endif
