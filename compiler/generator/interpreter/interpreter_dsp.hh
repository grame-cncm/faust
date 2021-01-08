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

#ifndef interpreter_dsp_h
#define interpreter_dsp_h

#include "interpreter_comp_dsp_aux.hh"
#ifndef MACHINE
#include "interpreter_optimizer.hh"
#endif

// Factory reader
template <class REAL, int TRACE>
interpreter_dsp_factory_aux<REAL, TRACE>* interpreter_dsp_factory_aux<REAL, TRACE>::read(std::istream* in)
{
    std::string dummy;
    
    // Read "file" line
    std::string file_version;
    int         file_num;
    getline(*in, file_version);
    
    std::stringstream file_version_reader(file_version);
    file_version_reader >> dummy;  // Read "file_version" token
    checkToken(dummy, "file_version");
    file_version_reader >> file_num;
    
    if (INTERP_FILE_VERSION != file_num) {
        std::stringstream error;
        error << "ERROR : interpreter file format version '" << file_num << "' different from compiled one '"
        << INTERP_FILE_VERSION << "'" << std::endl;
        throw faustexception(error.str());
    }
    
    // Read "version" line
    std::string version;
    getline(*in, version);
    
    std::stringstream version_reader(version);
    version_reader >> dummy;  // Read "Faust" token
    checkToken(dummy, "Faust");
    version_reader >> dummy;  // Read "version" token
    checkToken(dummy, "version");
    
    // Read "compile_options" line
    std::string compile_options;
    getline(*in, compile_options);
    
    std::stringstream compile_options_reader(compile_options);
    compile_options_reader >> dummy;  // Read "compile_options" token
    checkToken(dummy, "compile_options");
    
    // Read name
    std::string name, factory_name;
    getline(*in, name);
    
    std::stringstream name_reader(name);
    name_reader >> dummy;  // Read "name" token
    checkToken(dummy, "name");
    name_reader >> factory_name;
    
    // Read sha_key
    std::string sha_key_line, sha_key;
    getline(*in, sha_key_line);
    
    std::stringstream sha_key_line_reader(sha_key_line);
    sha_key_line_reader >> dummy;  // Read "sha_key" token
    checkToken(dummy, "sha_key");
    sha_key_line_reader >> sha_key;
    
    // Read opt_level
    std::string opt_level_line;
    int         opt_level;
    getline(*in, opt_level_line);
    
    std::stringstream opt_level_line_reader(opt_level_line);
    opt_level_line_reader >> dummy;  // Read "opt_level" token
    checkToken(dummy, "opt_level");
    opt_level_line_reader >> opt_level;
    
    // Read inputs/outputs
    std::string ins_outs;
    int         inputs, outputs;
    getline(*in, ins_outs);
    
    std::stringstream in_out_reader(ins_outs);
    
    in_out_reader >> dummy;  // Read "inputs" token
    checkToken(dummy, "inputs");
    in_out_reader >> inputs;
    
    in_out_reader >> dummy;  // Read "outputs" token
    checkToken(dummy, "outputs");
    in_out_reader >> outputs;
    
    // Read int/real heap size and sr offset
    std::string heap_size;
    int         int_heap_size, real_heap_size, sound_heap_size, sr_offset, count_offset, iota_offset;
    getline(*in, heap_size);
    
    std::stringstream heap_size_reader(heap_size);
    
    heap_size_reader >> dummy;  // Read "int_heap_size" token
    checkToken(dummy, "int_heap_size");
    heap_size_reader >> int_heap_size;
    
    heap_size_reader >> dummy;  // Read "real_heap_size" token
    checkToken(dummy, "real_heap_size");
    heap_size_reader >> real_heap_size;
    
    heap_size_reader >> dummy;  // Read "sound_heap_size" token
    checkToken(dummy, "sound_heap_size");
    heap_size_reader >> sound_heap_size;
    
    heap_size_reader >> dummy;  // Read "sr_offet" token
    checkToken(dummy, "sr_offset");
    heap_size_reader >> sr_offset;
    
    heap_size_reader >> dummy;  // Read "count_offset" token
    checkToken(dummy, "count_offset");
    heap_size_reader >> count_offset;
    
    heap_size_reader >> dummy;  // Read "iota_offset" token
    checkToken(dummy, "iota_offset");
    heap_size_reader >> iota_offset;
    
    // Read meta block
    getline(*in, dummy);  // Read "meta_block" line
    FIRMetaBlockInstruction* meta_block = readMetaBlock(in);
    
    // Read user interface block
    getline(*in, dummy);  // Read "user_interface_block" line
    FIRUserInterfaceBlockInstruction<REAL>* ui_block = readUIBlock(in);
    
    // Read static init block
    getline(*in, dummy);  // Read "static_init_block" line
    FBCBlockInstruction<REAL>* static_init_block = readCodeBlock(in);
    
    // Read constants block
    getline(*in, dummy);  // Read "constants_block" line
    FBCBlockInstruction<REAL>* init_block = readCodeBlock(in);
    
    // Read default ui block
    getline(*in, dummy);  // Read "clear_block" line
    FBCBlockInstruction<REAL>* resetui_block = readCodeBlock(in);
    
    // Read clear block
    getline(*in, dummy);  // Read "clear_block" line
    FBCBlockInstruction<REAL>* clear_block = readCodeBlock(in);
    
    // Read control block
    getline(*in, dummy);  // Read "control_block" line
    FBCBlockInstruction<REAL>* compute_control_block = readCodeBlock(in);
    
    // Read DSP block
    getline(*in, dummy);  // Read "dsp_block" line
    FBCBlockInstruction<REAL>* compute_dsp_block = readCodeBlock(in);
#ifdef MACHINE
    return new interpreter_comp_dsp_factory_aux<REAL,TRACE>(factory_name, compile_options, sha_key, file_num, inputs, outputs, int_heap_size, real_heap_size,
                                                         sound_heap_size, sr_offset, count_offset, iota_offset, opt_level, meta_block, ui_block, static_init_block,
                                                         init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);
#else
    return new interpreter_dsp_factory_aux<REAL,TRACE>(factory_name, compile_options, sha_key, file_num, inputs, outputs, int_heap_size, real_heap_size,
                                                    sound_heap_size, sr_offset, count_offset, iota_offset, opt_level, meta_block, ui_block, static_init_block,
                                                    init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);
#endif
}

template <class REAL, int TRACE>
void interpreter_dsp_factory_aux<REAL, TRACE>::optimize()
{
    if (!fOptimized) {
        fOptimized = true;
        // Bytecode optimization
        if (TRACE == 0) {
    #ifndef MACHINE
            fStaticInitBlock = FBCInstructionOptimizer<REAL>::optimizeBlock(fStaticInitBlock, 1, fOptLevel);
            fInitBlock       = FBCInstructionOptimizer<REAL>::optimizeBlock(fInitBlock, 1, fOptLevel);
            fResetUIBlock    = FBCInstructionOptimizer<REAL>::optimizeBlock(fResetUIBlock, 1, fOptLevel);
            fClearBlock      = FBCInstructionOptimizer<REAL>::optimizeBlock(fClearBlock, 1, fOptLevel);
            fComputeBlock    = FBCInstructionOptimizer<REAL>::optimizeBlock(fComputeBlock, 1, fOptLevel);
            fComputeDSPBlock = FBCInstructionOptimizer<REAL>::optimizeBlock(fComputeDSPBlock, 1, fOptLevel);
    #endif
        }
    }
}

template <class REAL, int TRACE>
dsp* interpreter_dsp_factory_aux<REAL, TRACE>::createDSPInstance(dsp_factory* factory)
{
    interpreter_dsp_factory* tmp = static_cast<interpreter_dsp_factory*>(factory);
    faustassert(tmp);
    
    if (tmp->getMemoryManager()) {
        return new (tmp->getFactory()->allocate(sizeof(interpreter_dsp)))
        interpreter_dsp(tmp, new (tmp->getFactory()->allocate(sizeof(interpreter_dsp_aux<REAL, TRACE>)))
                        interpreter_dsp_aux<REAL, TRACE>(this));
    } else {
    #ifdef MACHINE
        return new interpreter_dsp(tmp, new interpreter_comp_dsp_aux<REAL, TRACE>(this));
    #else
        return new interpreter_dsp(tmp, new interpreter_dsp_aux<REAL, TRACE>(this));
    #endif
    }
}


#endif
