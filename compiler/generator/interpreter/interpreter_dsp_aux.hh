/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef interpreter_dsp_aux_h
#define interpreter_dsp_aux_h

#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "dsp_aux.hh"
#include "dsp_factory.hh"
#include "export.hh"
#include "interpreter_bytecode.hh"
#include "interpreter_optimizer.hh"

#ifdef MACHINE
#include "fbc_cpp_compiler.hh"
#include "fbc_llvm_compiler.hh"
#endif

#include "fbc_interpreter.hh"
//#include "fbc_vec_interpreter.hh"

class interpreter_dsp_factory;

typedef class faust_smartptr<interpreter_dsp_factory> SDsp_factory;
extern dsp_factory_table<SDsp_factory>                gInterpreterFactoryTable;

template <class T, int TRACE>
class interpreter_dsp_aux;

template <class T, int TRACE>
struct interpreter_dsp_factory_aux : public dsp_factory_imp {
    int fVersion;
    int fNumInputs;
    int fNumOutputs;

    int fIntHeapSize;
    int fRealHeapSize;
    int fSoundHeapSize;
    int fSROffset;
    int fCountOffset;
    int fIOTAOffset;
    int fOptLevel;

    bool        fOptimized;
    std::string fCompileOptions;

    FIRMetaBlockInstruction*             fMetaBlock;
    FIRUserInterfaceBlockInstruction<T>* fUserInterfaceBlock;
    FBCBlockInstruction<T>*              fStaticInitBlock;
    FBCBlockInstruction<T>*              fInitBlock;
    FBCBlockInstruction<T>*              fResetUIBlock;
    FBCBlockInstruction<T>*              fClearBlock;
    FBCBlockInstruction<T>*              fComputeBlock;
    FBCBlockInstruction<T>*              fComputeDSPBlock;

#ifdef MACHINE
    // Shared between all DSP instances
    typename FBCCompiler<T>::CompiledBlocksType* fCompiledBlocks;
#endif

    interpreter_dsp_factory_aux(const std::string& name, const std::string& compile_options, const std::string& sha_key,
                                int version_num, int inputs, int outputs, int int_heap_size, int real_heap_size,
                                int sound_heap_size, int sr_offset, int count_offset, int iota_offset, int opt_level,
                                FIRMetaBlockInstruction* meta, FIRUserInterfaceBlockInstruction<T>* firinterface,
                                FBCBlockInstruction<T>* static_init, FBCBlockInstruction<T>* init,
                                FBCBlockInstruction<T>* resetui, FBCBlockInstruction<T>* clear,
                                FBCBlockInstruction<T>* compute_control, FBCBlockInstruction<T>* compute_dsp)
        : dsp_factory_imp(name, sha_key, ""),
          fVersion(version_num),
          fNumInputs(inputs),
          fNumOutputs(outputs),
          fIntHeapSize(int_heap_size),
          fRealHeapSize(real_heap_size),
          fSoundHeapSize(sound_heap_size),
          fSROffset(sr_offset),
          fCountOffset(count_offset),
          fIOTAOffset(iota_offset),
          fOptLevel(opt_level),
          fOptimized(false),
          fCompileOptions(compile_options),
          fMetaBlock(meta),
          fUserInterfaceBlock(firinterface),
          fStaticInitBlock(static_init),
          fInitBlock(init),
          fResetUIBlock(resetui),
          fClearBlock(clear),
          fComputeBlock(compute_control),
          fComputeDSPBlock(compute_dsp)
    {
#ifdef MACHINE
        fCompiledBlocks = new std::map<FBCBlockInstruction<T>*, FBCLLVMCompiler<T>*>();
        // fCompiledBlocks = new std::map<FBCBlockInstruction<T>*, FBCCPPCompiler<T>*>();
#endif
    }

    FBCExecutor<T>* createFBCExecutor()
    {
#ifdef MACHINE
        return new FBCCompiler<T>(this, fCompiledBlocks);
#else
        return new FBCInterpreter<T, TRACE>(this);
        // return new FBCVecInterpreter<T, 1>(this);
#endif
    }

    virtual ~interpreter_dsp_factory_aux()
    {
        // No more DSP instances, so delete
        delete fMetaBlock;
        delete fUserInterfaceBlock;
        delete fStaticInitBlock;
        delete fInitBlock;
        delete fResetUIBlock;
        delete fClearBlock;
        delete fComputeBlock;
        delete fComputeDSPBlock;
#ifdef MACHINE
        for (auto& it : *fCompiledBlocks) {
            delete it.second;
        }
        delete fCompiledBlocks;
#endif
    }

    void optimize()
    {
        if (!fOptimized) {
            fOptimized = true;
            // Bytecode optimization
            if (TRACE == 0) {
                fStaticInitBlock = FBCInstructionOptimizer<T>::optimizeBlock(fStaticInitBlock, 1, fOptLevel);
                fInitBlock       = FBCInstructionOptimizer<T>::optimizeBlock(fInitBlock, 1, fOptLevel);
                fResetUIBlock    = FBCInstructionOptimizer<T>::optimizeBlock(fResetUIBlock, 1, fOptLevel);
                fClearBlock      = FBCInstructionOptimizer<T>::optimizeBlock(fClearBlock, 1, fOptLevel);
                fComputeBlock    = FBCInstructionOptimizer<T>::optimizeBlock(fComputeBlock, 1, fOptLevel);
                fComputeDSPBlock = FBCInstructionOptimizer<T>::optimizeBlock(fComputeDSPBlock, 1, fOptLevel);
            }
        }
    }

    void write(std::ostream* out, bool binary = false, bool small = false)
    {
        *out << std::setprecision(std::numeric_limits<T>::max_digits10);

        if (small) {
            *out << "i " << ((sizeof(T) == sizeof(double)) ? "double" : "float") << std::endl;
            *out << "f " << INTERP_FILE_VERSION << std::endl;
            *out << "v " << FAUSTVERSION << std::endl;
            *out << "c " << fCompileOptions << std::endl;
            *out << "n " << fName << std::endl;
            *out << "s " << fSHAKey << std::endl;
            *out << "o " << fOptLevel << std::endl;
            *out << "i " << fNumInputs << " o " << fNumOutputs << std::endl;

            *out << "i " << fIntHeapSize << " r " << fRealHeapSize << " s " << fSoundHeapSize << " s " << fSROffset
                 << " c " << fCountOffset << " i " << fIOTAOffset << std::endl;

            *out << "m" << std::endl;
            fMetaBlock->write(out, small);

            *out << "u" << std::endl;
            fUserInterfaceBlock->write(out, small);

            *out << "s" << std::endl;
            fStaticInitBlock->write(out, small);

            *out << "i" << std::endl;
            fInitBlock->write(out, small);

            *out << "c" << std::endl;
            fResetUIBlock->write(out, small);

            *out << "c" << std::endl;
            fClearBlock->write(out, small);

            *out << "c" << std::endl;
            fComputeBlock->write(out, small);

            *out << "d" << std::endl;
            fComputeDSPBlock->write(out, small);
        } else {
            *out << "interpreter_dsp_factory " << ((sizeof(T) == sizeof(double)) ? "double" : "float") << std::endl;
            *out << "file_version " << INTERP_FILE_VERSION << std::endl;
            *out << "Faust version " << FAUSTVERSION << std::endl;
            *out << "compile_options " << fCompileOptions << std::endl;
            *out << "name " << fName << std::endl;
            *out << "sha_key " << fSHAKey << std::endl;
            *out << "opt_level " << fOptLevel << std::endl;

            *out << "inputs " << fNumInputs << " outputs " << fNumOutputs << std::endl;

            *out << "int_heap_size " << fIntHeapSize << " real_heap_size " << fRealHeapSize << " sound_heap_size "
                 << fSoundHeapSize << " sr_offset " << fSROffset << " count_offset " << fCountOffset << " iota_offset "
                 << fIOTAOffset << std::endl;

            *out << "meta_block" << std::endl;
            fMetaBlock->write(out, small);

            *out << "user_interface_block" << std::endl;
            fUserInterfaceBlock->write(out, small);

            *out << "static_init_block" << std::endl;
            fStaticInitBlock->write(out, small);

            *out << "constants_block" << std::endl;
            fInitBlock->write(out, small);

            *out << "reset_ui" << std::endl;
            fResetUIBlock->write(out, small);

            *out << "clear_block" << std::endl;
            fClearBlock->write(out, small);

            *out << "control_block" << std::endl;
            fComputeBlock->write(out, small);

            *out << "dsp_block" << std::endl;
            fComputeDSPBlock->write(out, small);
        }
    }

    // Factory reader
    static interpreter_dsp_factory_aux<T, TRACE>* read(std::istream* in)
    {
        std::string dummy;

        // Read "file" line
        std::string file_version;
        int         file_num;
        getline(*in, file_version);

        std::stringstream version_reader(file_version);
        version_reader >> dummy;  // Read "file_version" token
        version_reader >> file_num;

        if (INTERP_FILE_VERSION != file_num) {
            std::stringstream error;
            error << "ERROR : interpreter file format version '" << file_num << "' different from compiled one '"
                  << INTERP_FILE_VERSION << "'" << std::endl;
            throw faustexception(error.str());
        }

        // Read "version" line
        std::string version;
        getline(*in, version);

        // Read "compile_options" line
        std::string compile_options;
        getline(*in, compile_options);

        // Read name
        std::string name, factory_name;
        getline(*in, name);

        std::stringstream name_reader(name);
        name_reader >> dummy;  // Read "name" token
        name_reader >> factory_name;

        // Read sha_key
        std::string sha_key_line, sha_key;
        getline(*in, sha_key_line);

        std::stringstream sha_key_line_reader(sha_key_line);
        sha_key_line_reader >> dummy;  // Read "sha_key" token
        sha_key_line_reader >> sha_key;

        // Read opt_level
        std::string opt_level_line;
        int         opt_level;
        getline(*in, opt_level_line);

        std::stringstream opt_level_line_reader(opt_level_line);
        opt_level_line_reader >> dummy;  // Read "opt_level" token
        opt_level_line_reader >> opt_level;

        // Read inputs/outputs
        std::string ins_outs;
        int         inputs, outputs;
        getline(*in, ins_outs);

        std::stringstream in_out_reader(ins_outs);

        in_out_reader >> dummy;  // Read "inputs" token
        in_out_reader >> inputs;

        in_out_reader >> dummy;  // Read "outputs" token
        in_out_reader >> outputs;

        // Read int/real heap size and sr offset
        std::string heap_size;
        int         int_heap_size, real_heap_size, sound_heap_size, sr_offset, count_offset, iota_offset;
        getline(*in, heap_size);

        std::stringstream heap_size_reader(heap_size);

        heap_size_reader >> dummy;  // Read "int_heap_size" token
        heap_size_reader >> int_heap_size;

        heap_size_reader >> dummy;  // Read "real_heap_size" token
        heap_size_reader >> real_heap_size;

        heap_size_reader >> dummy;  // Read "sound_heap_size" token
        heap_size_reader >> sound_heap_size;

        heap_size_reader >> dummy;  // Read "sr_offet" token
        heap_size_reader >> sr_offset;

        heap_size_reader >> dummy;  // Read "count_offset" token
        heap_size_reader >> count_offset;

        heap_size_reader >> dummy;  // Read "iota_offset" token
        heap_size_reader >> iota_offset;

        // Read meta block
        getline(*in, dummy);  // Read "meta_block" line
        FIRMetaBlockInstruction* meta_block = readMetaBlock(in);

        // Read user interface block
        getline(*in, dummy);  // Read "user_interface_block" line
        FIRUserInterfaceBlockInstruction<T>* ui_block = readUIBlock(in);

        // Read static init block
        getline(*in, dummy);  // Read "static_init_block" line
        FBCBlockInstruction<T>* static_init_block = readCodeBlock(in);

        // Read constants block
        getline(*in, dummy);  // Read "constants_block" line
        FBCBlockInstruction<T>* init_block = readCodeBlock(in);

        // Read default ui block
        getline(*in, dummy);  // Read "clear_block" line
        FBCBlockInstruction<T>* resetui_block = readCodeBlock(in);

        // Read clear block
        getline(*in, dummy);  // Read "clear_block" line
        FBCBlockInstruction<T>* clear_block = readCodeBlock(in);

        // Read control block
        getline(*in, dummy);  // Read "control_block" line
        FBCBlockInstruction<T>* compute_control_block = readCodeBlock(in);

        // Read DSP block
        getline(*in, dummy);  // Read "dsp_block" line
        FBCBlockInstruction<T>* compute_dsp_block = readCodeBlock(in);

        return new interpreter_dsp_factory_aux(
            factory_name, compile_options, sha_key, file_num, inputs, outputs, int_heap_size, real_heap_size,
            sound_heap_size, sr_offset, count_offset, iota_offset, opt_level, meta_block, ui_block, static_init_block,
            init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);
    }

    static std::string parseStringToken(std::stringstream* inst)
    {
        std::string token;
        getline(*inst, token, '"');
        getline(*inst, token, '"');
        return token;
    }

    static FIRMetaBlockInstruction* readMetaBlock(std::istream* in)
    {
        std::string dummy, line;
        int         size;

        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);

        line_reader >> dummy;  // Read "block_size" token
        line_reader >> size;

        FIRMetaBlockInstruction* meta_block = new FIRMetaBlockInstruction();

        for (int i = 0; i < size; i++) {
            getline(*in, line);
            std::stringstream item_line_reader(line);
            meta_block->push(readMetaInstruction(&item_line_reader));
        }

        return meta_block;
    }

    static FIRMetaInstruction* readMetaInstruction(std::stringstream* inst)
    {
        std::string dummy, value, key, val;

        *inst >> dummy;  // Read "meta" token

        *inst >> dummy;  // Read "key" token
        // Read "key" content (as a string)
        key = parseStringToken(inst);

        *inst >> dummy;  // Read "value" token
        // Read "val" content (as a string)
        val = parseStringToken(inst);

        return new FIRMetaInstruction(unquote1(key), unquote1(val));
    }

    static FIRUserInterfaceBlockInstruction<T>* readUIBlock(std::istream* in)
    {
        std::string dummy, line;
        int         size;

        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);

        line_reader >> dummy;  // Read "block_size" token
        line_reader >> size;

        FIRUserInterfaceBlockInstruction<T>* ui_block = new FIRUserInterfaceBlockInstruction<T>();

        for (int i = 0; i < size; i++) {
            getline(*in, line);
            std::stringstream item_line_reader(line);
            ui_block->push(readUIInstruction(&item_line_reader));
        }

        return ui_block;
    }

    static FIRUserInterfaceInstruction<T>* readUIInstruction(std::stringstream* inst)
    {
        int         opcode, offset;
        T           init, min, max, step;
        std::string dummy, label, key, val;

        *inst >> dummy;  // Read "opcode" token
        *inst >> opcode;
        *inst >> dummy;  // Read opcode string representation (that is not used)

        *inst >> dummy;  // Read "offset" token
        *inst >> offset;

        *inst >> dummy;  // Read "label" token
        // Read "label" content (as a string)
        label = parseStringToken(inst);

        *inst >> dummy;  // Read "key" token
        *inst >> key;    // Read "key" content

        *inst >> dummy;  // Read "value" token
        // Read "Value" content (as a string)
        val = parseStringToken(inst);

        *inst >> dummy;  // Read "init" token
        *inst >> init;

        *inst >> dummy;  // Read "min" token
        *inst >> min;

        *inst >> dummy;  // Read "max" token
        *inst >> max;

        *inst >> dummy;  // Read "step" token
        *inst >> step;

        return new FIRUserInterfaceInstruction<T>(FBCInstruction::Opcode(opcode), offset, unquote1(label),
                                                  unquote1(key), unquote1(val), init, min, max, step);
    }

    static FBCBlockInstruction<T>* readCodeBlock(std::istream* in)
    {
        std::string dummy, line;
        int         size;

        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);

        line_reader >> dummy;  // Read "block_size" token
        line_reader >> size;

        FBCBlockInstruction<T>* code_block = new FBCBlockInstruction<T>();

        for (int i = 0; i < size; i++) {
            getline(*in, line);
            std::stringstream       inst_line_reader(line);
            FBCBasicInstruction<T>* inst = readCodeInstruction(&inst_line_reader, in);
            // Special case for loops
            if (inst->fOpcode == FBCInstruction::kCondBranch) {
                inst->fBranch1 = code_block;
            }
            code_block->push(inst);
        }

        return code_block;
    }

    static FBCBasicInstruction<T>* readCodeInstruction(std::istream* inst, std::istream* in)
    {
        int opcode, offset1, offset2;
        int val_int;
        T   val_real;

        std::string dummy, line;
        *inst >> dummy;  // Read "opcode" token
        *inst >> opcode;

        *inst >> dummy;  // Read opcode string representation (that is not used)

        if (opcode == FBCInstruction::kBlockStoreReal) {
            int            block_size;
            std::vector<T> block_values;

            *inst >> dummy;  // Read "offset1" token
            *inst >> offset1;

            *inst >> dummy;  // Read "offset2" token
            *inst >> offset2;

            *inst >> dummy;  // Read "size" token
            *inst >> block_size;

            // Read samples line
            getline(*in, line);
            std::stringstream sample_line_reader(line);

            // Read each sample
            for (int i = 0; i < block_size; i++) {
                sample_line_reader >> val_real;
                block_values.push_back(val_real);
            }

            return new FIRBlockStoreRealInstruction<T>(FBCInstruction::Opcode(opcode), offset1, offset2, block_values);

        } else if (opcode == FBCInstruction::kBlockStoreInt) {
            int              block_size;
            std::vector<int> block_values;

            *inst >> dummy;  // Read "offset1" token
            *inst >> offset1;

            *inst >> dummy;  // Read "offset2" token
            *inst >> offset2;

            *inst >> dummy;  // Read "size" token
            *inst >> block_size;

            // Read samples line
            getline(*in, line);
            std::stringstream sample_line_reader(line);

            // Read each sample
            for (int i = 0; i < block_size; i++) {
                sample_line_reader >> val_int;
                block_values.push_back(val_int);
            }

            return new FIRBlockStoreIntInstruction<T>(FBCInstruction::Opcode(opcode), offset1, offset2, block_values);

        } else {
            std::string name;
            *inst >> dummy;  // Read "int" token
            *inst >> val_int;

            *inst >> dummy;  // Read "real" token
            *inst >> val_real;

            *inst >> dummy;  // Read "offset1" token
            *inst >> offset1;

            *inst >> dummy;  // Read "offset2" token
            *inst >> offset2;

            *inst >> dummy;  // Read "name" token (if present)
            *inst >> name;

            FBCBlockInstruction<T>* branch1 = nullptr;
            FBCBlockInstruction<T>* branch2 = nullptr;

            // Possibly read sub-blocks
            if (FBCInstruction::isChoice(FBCInstruction::Opcode(opcode))) {
                branch1 = readCodeBlock(in);  // consume 'in'
                branch2 = readCodeBlock(in);  // consume 'in'
            } else if (opcode == FBCInstruction::kLoop) {
                branch1 = readCodeBlock(in);  // consume 'in'
                branch2 = readCodeBlock(in);  // consume 'in'
            }

            return new FBCBasicInstruction<T>(FBCInstruction::Opcode(opcode), name, val_int, val_real, offset1, offset2,
                                              branch1, branch2);
        }
    }

    void metadata(Meta* meta) { ExecuteMeta(fMetaBlock, meta); }

    void ExecuteMeta(FIRMetaBlockInstruction* block, Meta* meta)
    {
        for (auto& it : block->fInstructions) {
            meta->declare(it->fKey.c_str(), it->fValue.c_str());
        }
    }

    dsp* createDSPInstance(dsp_factory* factory);
};

struct interpreter_dsp_base : public dsp {
    virtual ~interpreter_dsp_base() {}

    // Not implemented...
    void buildUserInterface(UI* ui_interface) {}

    // Replaced by this one
    virtual void buildUserInterface(UITemplate* glue) = 0;

    virtual void instanceInit(int sample_rate) {}

    virtual void instanceConstants(int sample_rate) {}

    virtual void instanceResetUserInterface() {}

    virtual void instanceClear() {}

    // Not implemented...
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}

    virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
};

template <class T, int TRACE>
class interpreter_dsp_aux : public interpreter_dsp_base {
   protected:
    bool                                   fInitialized;
    bool                                   fTraceOutput;
    int                                    fCycle;
    interpreter_dsp_factory_aux<T, TRACE>* fFactory;
    FBCExecutor<T>*                        fFBCExecutor;

   public:
    interpreter_dsp_aux()
        : fInitialized(false), fTraceOutput(false), fCycle(0), fFactory(nullptr), fFBCExecutor(nullptr)
    {
    }

    interpreter_dsp_aux(interpreter_dsp_factory_aux<T, TRACE>* factory)
    {
        fFactory = factory;
#ifndef MACHINE
        // Done before createFBCExecutor that may compile blocks...
        fFactory->optimize();
#endif
        fFBCExecutor = factory->createFBCExecutor();
        fInitialized = false;
        fCycle       = 0;
        /*
        #ifdef MACHINE
                FBCCPPGenerator<T> cpp_generator(this->fFactory);
                cpp_generator.generateCode(std::cout);
        #endif
        */
        fTraceOutput = getenv("FAUST_INTERP_OUTPUT") != NULL;
    }

    virtual ~interpreter_dsp_aux()
    {
        delete fFBCExecutor;
        // delete fFBCVecExecutor;
    }

    // Freeze values
    void freezeValues(std::map<int, int>& int_map, std::map<int, T>& real_map)
    {
        std::cout << "freezeValues Int " << std::endl;
        for (auto& it1 : int_map) {
            std::cout << "offset " << it1.first << " value " << it1.second << std::endl;
            this->fIntHeap[it1.first] = it1.second;
        }

        std::cout << "freezeValues Real" << std::endl;
        for (auto& it2 : real_map) {
            std::cout << "offset " << it2.first << " value " << it2.second << std::endl;
            this->fRealHeap[it2.first] = it2.second;
        }
    }

    virtual void metadata(Meta* meta) { fFactory->metadata(meta); }

    virtual int getSampleRate() { return fFBCExecutor->getIntValue(fFactory->fSROffset); }

    // to be implemented by subclass
    virtual dsp* clone()
    {
        faustassert(false);
        return nullptr;
    }

    virtual int getNumInputs() { return fFactory->fNumInputs; }

    virtual int getNumOutputs() { return fFactory->fNumOutputs; }

    virtual int getInputRate(int channel) { return -1; }

    virtual int getOutputRate(int channel) { return -1; }

    virtual void classInit(int sample_rate)
    {
        if (TRACE > 0) {
            std::cout << "------------------------" << std::endl;
            std::cout << "classInit " << sample_rate << std::endl;
        }
        
        // Execute static init instructions
        fFBCExecutor->ExecuteBlock(fFactory->fStaticInitBlock);
    }

    virtual void instanceConstants(int sample_rate)
    {
        if (TRACE > 0) {
            std::cout << "------------------------" << std::endl;
            std::cout << "instanceConstants " << sample_rate << std::endl;
        }
        
        // Store sample_rate in 'fSampleRate' variable at correct offset in fIntHeap
        fFBCExecutor->setIntValue(fFactory->fSROffset, sample_rate);

        // Execute state init instructions
        fFBCExecutor->ExecuteBlock(fFactory->fInitBlock);
    }

    virtual void instanceResetUserInterface()
    {
        if (TRACE > 0) {
            std::cout << "------------------------" << std::endl;
            std::cout << "instanceResetUserInterface " << std::endl;
        }
        
        // Execute reset UI instructions
        fFBCExecutor->ExecuteBlock(fFactory->fResetUIBlock);
    }

    virtual void instanceClear()
    {
        if (TRACE > 0) {
            std::cout << "------------------------" << std::endl;
            std::cout << "instanceClear " << std::endl;
        }
        
        // Execute clear instructions
        fFBCExecutor->ExecuteBlock(fFactory->fClearBlock);
    }

    virtual void instanceInit(int sample_rate)
    {
        if (TRACE > 0) {
            std::cout << "------------------------" << std::endl;
            std::cout << "instanceInit " << sample_rate << std::endl;
        }
        
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }

    virtual void init(int sample_rate)
    {
        if (TRACE > 0) {
            std::cout << "------------------------" << std::endl;
            std::cout << "init " << sample_rate << std::endl;
        }
        
        fInitialized = true;
        classInit(sample_rate);
        instanceInit(sample_rate);
        /*
    #ifdef MACHINE
        FBCCPPGenerator<T> cpp_generator(this->fFactory);
        cpp_generator.generateCode(std::cout);
    #endif
        */
    }

    virtual void buildUserInterface(UITemplate* glue)
    {
        fFBCExecutor->ExecuteBuildUserInterface(fFactory->fUserInterfaceBlock, glue);
    }

    void ExecuteVecBlock(FBCBlockInstruction<T>* block, int vec_size)
    {
        /*
            Execute the VEC size specialized version of the interpreter
            vec_size == 1 correspond to the scalar interpreter
         */

        /*
        if (vec_size == 1) {
            fFBCExecutor->ExecuteBlock<T, 1, TRACE>(block);
        } else if (vec_size == 4) {
            fFBCExecutor->ExecuteBlock<T, 4, TRACE>(block);
        } else if (vec_size == 8) {
            fFBCExecutor->ExecuteBlock<T, 8, TRACE>(block);
        } else if (vec_size == 16) {
            fFBCExecutor->ExecuteBlock<T, 16, TRACE>(block);
        } else if (vec_size == 32) {
            fFBCExecutor->ExecuteBlock<T, 32, TRACE>(block);
        } else if (vec_size == 64) {
            fFBCExecutor->ExecuteBlock<T, 64, TRACE>(block);
        } else {
            fFBCExecutor->ExecuteBlock<T, 128, TRACE>(block);
        }
        */
    }

    virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
    {
        if (count == 0) return;  // Beware: compiled loop don't work with an index of 0

        if (TRACE > 0 && !fInitialized) {
            std::cout << "======== DSP is not initialized ! ========" << std::endl;
        } else {
            
            if (TRACE > 0) {
                std::cout << "------------------------" << std::endl;
                std::cout << "compute " << count << std::endl;
            }
            
            fCycle++;

            // std::cout << "compute " << count << std::endl;
            T** inputs  = reinterpret_cast<T**>(inputs_aux);
            T** outputs = reinterpret_cast<T**>(outputs_aux);

            // Prepare in/out buffers
            for (int i = 0; i < fFactory->fNumInputs; i++) {
                fFBCExecutor->setInput(i, inputs[i]);
            }
            for (int i = 0; i < fFactory->fNumOutputs; i++) {
                fFBCExecutor->setOutput(i, outputs[i]);
            }

            // Set count in 'count' variable at the correct offset in fIntHeap
            fFBCExecutor->setIntValue(fFactory->fCountOffset, count);
            
            try {
                
                // Executes the 'control' block
                fFBCExecutor->ExecuteBlock(fFactory->fComputeBlock);

                // Executes the 'DSP' block
                fFBCExecutor->ExecuteBlock(fFactory->fComputeDSPBlock);
                
            } catch (faustexception& e) {
                std::cout << e.Message();
                fFBCExecutor->dumpMemory(fFactory->fComputeDSPBlock, fFactory->getName(),
                                         "DumpMem-" + fFactory->getName() + std::to_string(fCycle) + ".txt");
                std::ofstream code_out("DumpCode-" + fFactory->getName() + ".txt");
                fFactory->write(&code_out, false);
                // If needed we exit
                if (e.Message() == "Interpreter exit\n") exit(1);
            }

            if ((TRACE == 7) && (fCycle < 4)) {
                fFBCExecutor->dumpMemory(fFactory->fComputeDSPBlock, fFactory->getName(),
                                         "DumpMem-" + fFactory->getName() + std::to_string(fCycle) + ".txt");
            }

            // fFBCVecExecutor->ExecuteBlock(fFactory->fComputeDSPBlock);

            if (fTraceOutput) {
                for (int chan = 0; chan < fFactory->fNumOutputs; chan++) {
                    for (int frame = 0; frame < count; frame++) {
                        std::cout << "Chan: " << chan << " sample: " << outputs_aux[chan][frame] << std::endl;
                    }
                }
            }
        }
    }
};

// Specialization using partial evaluation: making controllers constant and optimizing the code.

template <class T, int TRACE>
class interpreter_dsp_aux_pe : public interpreter_dsp_aux<T, TRACE> {
   protected:
    FBCBlockInstruction<T>* fStaticInitBlock;
    FBCBlockInstruction<T>* fInitBlock;
    FBCBlockInstruction<T>* fResetUIBlock;
    FBCBlockInstruction<T>* fClearBlock;
    FBCBlockInstruction<T>* fComputeBlock;
    FBCBlockInstruction<T>* fComputeDSPBlock;

    std::map<int, int> fIntMap;
    std::map<int, T>   fRealMap;

   public:
    interpreter_dsp_aux_pe(interpreter_dsp_factory_aux<T, TRACE>* factory)
    {
        std::cout << "interpreter_dsp_aux_pe\n";
        /*
         if (this->fFactory->getMemoryManager()) {
         this->fInputs  = static_cast<T**>(this->fFactory->allocate(sizeof(T*) * this->fFactory->fNumInputs));
         this->fOutputs = static_cast<T**>(this->fFactory->allocate(sizeof(T*) * this->fFactory->fNumOutputs));
         } else {
         this->fInputs  = new T*[this->fFactory->fNumInputs];
         this->fOutputs = new T*[this->fFactory->fNumOutputs];
         }
         */

        /*
         fFactory->fStaticInitBlock->write(&std::cout, false);
         fFactory->fInitBlock->write(&std::cout, false);
         fFactory->fResetUIBlock->write(&std::cout, false);
         fFactory->fClearBlock->write(&std::cout, false);
         fFactory->fComputeBlock->write(&std::cout, false);
         fFactory->fComputeDSPBlock->write(&std::cout, false);
         std::cout << "size " << fFactory->fComputeDSPBlock->size() << std::endl;
         */

        this->fFactory     = factory;
        this->fFBCExecutor = factory->createFBCExecutor();

        fStaticInitBlock = nullptr;
        fInitBlock       = nullptr;
        fResetUIBlock    = nullptr;
        fClearBlock      = nullptr;
        fComputeBlock    = nullptr;
        fComputeDSPBlock = nullptr;
    }

    virtual ~interpreter_dsp_aux_pe()
    {
        /*
         if (this->fFactory->getMemoryManager()) {
            this->fFactory->destroy(this->fInputs);
            this->fFactory->destroy(this->fOutputs);
         } else {
            delete[] this->fInputs;
            delete[] this->fOutputs;
         }
         */

        delete this->fStaticInitBlock;
        delete this->fInitBlock;
        delete this->fResetUIBlock;
        delete this->fClearBlock;
        delete this->fComputeBlock;
        delete this->fComputeDSPBlock;
    }

    virtual void instanceConstants(int sample_rate)
    {
        // Store sample_rate in specialization fIntMap
        fIntMap[this->fFactory->fSROffset] = sample_rate;

        // Store sample_rate in 'fSampleate' variable at correct offset in fIntHeap
        this->fFBCExecutor->setIntValue(this->fFactory->fSROffset, sample_rate);

        // Execute state init instructions
        this->fFBCExecutor->ExecuteBlock(this->fFactory->fInitBlock);
    }

    virtual void init(int sample_rate)
    {
        this->fInitialized = true;

        // Store sample_rate in specialization fIntMap
        fIntMap[this->fFactory->fSROffset] = sample_rate;

        // Store sample_rate in 'fSampleRate' variable at correct offset in fIntHeap
        this->fFBCExecutor->setIntValue(this->fFactory->fSROffset, sample_rate);

        this->classInit(sample_rate);
        this->instanceInit(sample_rate);

        // Propagate constant values stored in the code into the heap
        this->fStaticInitBlock =
            FBCInstructionOptimizer<T>::specialize2Heap(this->fFactory->fStaticInitBlock->copy(), fIntMap, fRealMap);
        this->fInitBlock =
            FBCInstructionOptimizer<T>::specialize2Heap(this->fFactory->fInitBlock->copy(), fIntMap, fRealMap);
        this->fResetUIBlock =
            FBCInstructionOptimizer<T>::specialize2Heap(this->fFactory->fResetUIBlock->copy(), fIntMap, fRealMap);
        this->fClearBlock =
            FBCInstructionOptimizer<T>::specialize2Heap(this->fFactory->fClearBlock->copy(), fIntMap, fRealMap);

        // Suppress IOTA from fIntMap since we don't want specialization to use it
        if (fIntMap.find(this->fFactory->fIOTAOffset) != fIntMap.end()) {
            fIntMap.erase(fIntMap.find(this->fFactory->fIOTAOffset));
        }

        // Freeze all controllers
        this->fFactory->fUserInterfaceBlock->freezeDefaultValues(fRealMap);

        // To test : unfreeze "freg, gate, gain" controllers
        std::map<std::string, int>& map = this->fFactory->fUserInterfaceBlock->getPathMap();
        for (auto& it : map) {
            if ((it.first.find("freq") != std::string::npos) || (it.first.find("gate") != std::string::npos) ||
                (it.first.find("gain") != std::string::npos)) {
                this->fFactory->fUserInterfaceBlock->unFreezeValue(fRealMap, it.first);
            }
        }
        // Keep button on
        // this->fFactory->fUserInterfaceBlock->unFreezeValue(fRealMap, FBCInstruction::kAddButton);

        // Specialization by partial evaluation
        this->fComputeBlock =
            FBCInstructionOptimizer<T>::specialize(this->fFactory->fComputeBlock->copy(), fIntMap, fRealMap);

#ifndef MACHINE
        // LLVM JIT only works on unoptimized FBC
        this->fComputeDSPBlock =
            FBCInstructionOptimizer<T>::optimizeBlock(this->fFactory->fComputeDSPBlock->copy(), 1, 4);
#else
        this->fComputeDSPBlock = this->fFactory->fComputeDSPBlock->copy();
#endif

        // To test C++ generation
        // this->fComputeDSPBlock = this->fFactory->fComputeDSPBlock->copy();

        this->fComputeDSPBlock = FBCInstructionOptimizer<T>::specialize(this->fComputeDSPBlock, fIntMap, fRealMap);

#ifndef MACHINE
        // // LLVM JIT only works on unoptimized FBC
        this->fComputeBlock    = FBCInstructionOptimizer<T>::optimizeBlock(this->fComputeBlock, 5, 6);
        this->fComputeDSPBlock = FBCInstructionOptimizer<T>::optimizeBlock(this->fComputeDSPBlock, 5, 6);
#endif

        /*
        this->fStaticInitBlock->write(&std::cout, false);
        this->fInitBlock->write(&std::cout, false);
        this->fResetUIBlock->write(&std::cout, false);
        this->fClearBlock->write(&std::cout, false);
        this->fComputeBlock->write(&std::cout, false);
        this->fComputeDSPBlock->write(&std::cout, false);
        */
        /*
        #ifdef MACHINE
            FBCCPPGenerator<T> cpp_generator(this->fFactory);
            cpp_generator.generateCode(std::cout, this->fComputeBlock, this->fComputeDSPBlock);
        #endif
        */
    }

    virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
    {
        if (count == 0) return;  // Beware: compiled loop don't work with an index of 0

        if (TRACE > 0 && !this->fInitialized) {
            std::cout << "======== DSP is not initialized ! ========" << std::endl;
        } else {
            // std::cout << "compute " << count << std::endl;
            T** inputs  = reinterpret_cast<T**>(inputs_aux);
            T** outputs = reinterpret_cast<T**>(outputs_aux);

            // Prepare in/out buffers
            for (int i = 0; i < this->fFactory->fNumInputs; i++) {
                this->fFBCExecutor->setInput(i, inputs[i]);
            }
            for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
                this->fFBCExecutor->setOutput(i, outputs[i]);
            }

            // Set count in 'count' variable at the correct offset in fIntHeap
            this->fFBCExecutor->setIntValue(this->fFactory->fCountOffset, count);

            // Executes the specialized 'control' block
            this->fFBCExecutor->ExecuteBlock(this->fComputeBlock);

            // Executes the specialized 'DSP' block
#ifndef MACHINE
            this->fFBCExecutor->ExecuteBlock(this->fComputeDSPBlock);
#else
            this->fFBCExecutor->ExecuteBlock(this->fComputeDSPBlock, true);
#endif
        }
    }
};

/*
Computing using on a down-sampled version of signals

TODO:

- anti alias filter at input
- interpolation at output

*/

template <class T, int TRACE>
class interpreter_dsp_aux_down : public interpreter_dsp_aux<T, TRACE> {
   private:
    int fDownSamplingFactor;

   public:
    interpreter_dsp_aux_down(interpreter_dsp_factory_aux<T, TRACE>* factory, int down_sampling_factor)
        : interpreter_dsp_aux<T, TRACE>(factory), fDownSamplingFactor(down_sampling_factor)
    {
        // TODO
        /*
        // Allocate and set downsampled inputs/outputs
        for (int i = 0; i < this->fFactory->fNumInputs; i++) {
            this->fInputs[i] = (this->fFactory->getMemoryManager())
                                   ? static_cast<T*>(this->fFactory->allocate(sizeof(T) * 2048))
                                   : new T[2048];
        }
        for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
            this->fOutputs[i] = (this->fFactory->getMemoryManager())
                                    ? static_cast<T*>(this->fFactory->allocate(sizeof(T) * 2048))
                                    : new T[2048];
        }
        */
    }

    virtual ~interpreter_dsp_aux_down()
    {
        // TODO
        /*
        // Delete downsampled inputs/outputs
        for (int i = 0; i < this->fFactory->fNumInputs; i++) {
            (this->fFactory->getMemoryManager()) ? this->fFactory->destroy(this->fInputs[i])
                                                 : delete[] this->fInputs[i];
        }
        for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
            (this->fFactory->getMemoryManager()) ? this->fFactory->destroy(this->fOutputs[i])
                                                 : delete[] this->fOutputs[i];
        }
        */
    }

    virtual void init(int sample_rate)
    {
        this->classInit(sample_rate / fDownSamplingFactor);
        this->instanceInit(sample_rate / fDownSamplingFactor);
    }

    virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
    {
        if (count == 0) return;  // Beware: compiled loop don't work with an index of 0

        T** inputs  = reinterpret_cast<T**>(inputs_aux);
        T** outputs = reinterpret_cast<T**>(outputs_aux);

        // Downsample inputs
        for (int i = 0; i < this->fFactory->fNumInputs; i++) {
            for (int j = 0; j < count / fDownSamplingFactor; j++) {
                this->fInputs[i][j] = inputs[i][j * fDownSamplingFactor];
            }
        }

        // Executes the 'control' block
        this->fFBCExecutor->ExecuteBlock(this->fFactory->fComputeBlock);

        // Set count in 'count' variable at the correct offset in fIntHeap
        this->fFBCExecutor->setIntValue(this->fFactory->fCountOffset, count / fDownSamplingFactor);

        // Executes the 'DSP' block
        this->fFBCExecutor->ExecuteBlock(this->fFactory->fComputeDSPBlock);

        // Upsample ouputs
        for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
            for (int j = 0; j < count / fDownSamplingFactor; j++) {
                T sample                                  = this->fOutputs[i][j];
                outputs[i][j * fDownSamplingFactor]       = sample;
                outputs[i][(j * fDownSamplingFactor) + 1] = sample;
            }
        }

        // std::cout << "sample " << outputs[0][0] << std::endl;
    }
};

// Public C++ interface

class EXPORT interpreter_dsp : public dsp {
   private:
    interpreter_dsp_factory* fFactory;
    interpreter_dsp_base*    fDSP;

   public:
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 0>* dsp) : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 0>* dsp)
        : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 1>* dsp) : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 1>* dsp)
        : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 2>* dsp) : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 2>* dsp)
        : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 3>* dsp) : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 3>* dsp)
        : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 4>* dsp) : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 4>* dsp)
        : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 5>* dsp) : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 5>* dsp)
        : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 6>* dsp) : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 6>* dsp)
        : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 7>* dsp) : fFactory(factory), fDSP(dsp)
    {
    }
    interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 7>* dsp)
        : fFactory(factory), fDSP(dsp)
    {
    }

    virtual ~interpreter_dsp();

    void operator delete(void* ptr);

    int getNumInputs();

    int getNumOutputs();

    void buildUserInterface(UI* ui_interface);

    int getSampleRate();

    void init(int sample_rate);

    void instanceInit(int sample_rate);

    void instanceConstants(int sample_rate);

    void instanceResetUserInterface();

    void instanceClear();

    interpreter_dsp* clone();

    void metadata(Meta* meta);

    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
};

class EXPORT interpreter_dsp_factory : public dsp_factory, public faust_smartable {
   protected:
    dsp_factory_base* fFactory;

    virtual ~interpreter_dsp_factory() { delete fFactory; }

   public:
    interpreter_dsp_factory(dsp_factory_base* factory) : fFactory(factory) {}

    std::string getName() { return fFactory->getName(); }

    std::string getSHAKey() { return fFactory->getSHAKey(); }
    void        setSHAKey(std::string sha_key) { fFactory->setSHAKey(sha_key); }

    std::string getDSPCode() { return fFactory->getDSPCode(); }
    void        setDSPCode(std::string code) { fFactory->setDSPCode(code); }

    std::string getCompileOptions() { return ""; }

    interpreter_dsp* createDSPInstance();

    // TODO
    std::vector<std::string> getLibraryList() { return std::vector<std::string>(); }
    std::vector<std::string> getIncludePathnames() { return std::vector<std::string>(); }

    void                setMemoryManager(dsp_memory_manager* manager) { fFactory->setMemoryManager(manager); }
    dsp_memory_manager* getMemoryManager() { return fFactory->getMemoryManager(); }

    dsp_factory_base* getFactory() { return fFactory; }

    void write(std::ostream* out, bool binary = false, bool small = false) { fFactory->write(out, binary, small); }
};

template <class T, int TRACE>
dsp* interpreter_dsp_factory_aux<T, TRACE>::createDSPInstance(dsp_factory* factory)
{
    interpreter_dsp_factory* tmp = static_cast<interpreter_dsp_factory*>(factory);
    faustassert(tmp);

    if (tmp->getMemoryManager()) {
        return new (tmp->getFactory()->allocate(sizeof(interpreter_dsp)))
            interpreter_dsp(tmp, new (tmp->getFactory()->allocate(sizeof(interpreter_dsp_aux<T, TRACE>)))
                                     interpreter_dsp_aux<T, TRACE>(this));
    } else {
        const char* trace = getenv("FAUST_INTERP_PE");
        int         mode  = (trace) ? std::atoi(trace) : 0;
        if (mode != 0) {
            // Testing partial evaluation
            return new interpreter_dsp(tmp, new interpreter_dsp_aux_pe<T, TRACE>(this));
        } else {
            return new interpreter_dsp(tmp, new interpreter_dsp_aux<T, TRACE>(this));
        }
    }
}

EXPORT interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const std::string& sha_key);

EXPORT bool deleteInterpreterDSPFactory(interpreter_dsp_factory* factory);

EXPORT std::vector<std::string> getInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory);

EXPORT std::vector<std::string> getAllInterpreterDSPFactories();

EXPORT interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcode(const std::string& bitcode,
                                                                     std::string&       error_msg);

EXPORT std::string writeInterpreterDSPFactoryToBitcode(interpreter_dsp_factory* factory);

EXPORT interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcodeFile(const std::string& bitcode_path,
                                                                         std::string&       error_msg);

EXPORT void writeInterpreterDSPFactoryToBitcodeFile(interpreter_dsp_factory* factory, const std::string& bitcode_path);

EXPORT void deleteAllInterpreterDSPFactories();

#endif
