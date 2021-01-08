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
#include "fbc_compiler.hh"

// Interpreter factory using a LLVM or MIR compiler for the 'compute' method

template <class REAL, int TRACE>
struct interpreter_comp_dsp_factory_aux : public interpreter_dsp_factory_aux<REAL,TRACE> {
    
    // Shared between all DSP instances
    typename FBCCompiler<REAL>::CompiledBlocksType* fCompiledBlocks;

    interpreter_comp_dsp_factory_aux(const std::string& name, const std::string& compile_options, const std::string& sha_key,
                                int version_num, int inputs, int outputs, int int_heap_size, int real_heap_size,
                                int sound_heap_size, int sr_offset, int count_offset, int iota_offset, int opt_level,
                                FIRMetaBlockInstruction* meta, FIRUserInterfaceBlockInstruction<REAL>* firinterface,
                                FBCBlockInstruction<REAL>* static_init, FBCBlockInstruction<REAL>* init,
                                FBCBlockInstruction<REAL>* resetui, FBCBlockInstruction<REAL>* clear,
                                FBCBlockInstruction<REAL>* compute_control, FBCBlockInstruction<REAL>* compute_dsp)
    : interpreter_dsp_factory_aux<REAL,TRACE>(name, compile_options, sha_key,
                                  version_num, inputs, outputs, int_heap_size, real_heap_size,
                                  sound_heap_size, sr_offset, count_offset,iota_offset, opt_level,
                                  meta, firinterface,
                                  static_init, init,
                                  resetui, clear,
                                  compute_control, compute_dsp)
    {
        fCompiledBlocks = new std::map<FBCBlockInstruction<REAL>*, FBCExecuteFun<REAL>*>();
    }

    virtual FBCExecutor<REAL>* createFBCExecutor()
    {
        return new FBCCompiler<REAL>(this, fCompiledBlocks);
    }

    virtual ~interpreter_comp_dsp_factory_aux()
    {
        for (auto& it : *fCompiledBlocks) {
            delete it.second;
        }
        delete fCompiledBlocks;
    }

};

// Interpreter instance using a LLVM or MIR compiler for the 'compute' method

template <class REAL, int TRACE>
struct interpreter_comp_dsp_aux : public interpreter_dsp_aux<REAL,TRACE> {

    interpreter_comp_dsp_aux(interpreter_dsp_factory_aux<REAL, TRACE>* factory)
    {
        this->fFactory = factory;
        this->fInitialized = false;
        this->fCycle = 0;
        this->fTraceOutput = false;
        this->fFBCExecutor = factory->createFBCExecutor();
    }
    
};

#endif
