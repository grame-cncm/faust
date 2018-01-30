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

#ifndef interpreter_dsp_aux_h
#define interpreter_dsp_aux_h

#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/CGlue.h"
#include "faust/gui/meta.h"

#include "fir_interpreter.hh"
#include "interpreter_bytecode.hh"
#include "interpreter_optimizer.hh"
#include "dsp_aux.hh"
#include "dsp_factory.hh"

class interpreter_dsp_factory;

template <class T, int TRACE>
class interpreter_dsp_aux;

template <class T, int TRACE>
struct interpreter_dsp_factory_aux : public dsp_factory_imp {

    int fVersion;
    int fNumInputs;
    int fNumOutputs;

    int fIntHeapSize;
    int fRealHeapSize;
    int fSROffset;
    int fCountOffset;
    int fIOTAOffset;
    int fOptLevel;

    bool fOptimized;

    FIRMetaBlockInstruction* fMetaBlock;
    FIRUserInterfaceBlockInstruction<T>* fUserInterfaceBlock;
    FIRBlockInstruction<T>* fStaticInitBlock;
    FIRBlockInstruction<T>* fInitBlock;
    FIRBlockInstruction<T>* fResetUIBlock;
    FIRBlockInstruction<T>* fClearBlock;
    FIRBlockInstruction<T>* fComputeBlock;
    FIRBlockInstruction<T>* fComputeDSPBlock;

    interpreter_dsp_factory_aux(const std::string& name,
                                const std::string& sha_key,
                                const std::vector<std::string>& pathname_list,
                                int version_num,
                                int inputs, int outputs,
                                int int_heap_size, int real_heap_size,
                                int sr_offset,
                                int count_offset,
                                int iota_offset,
                                int opt_level,
                                FIRMetaBlockInstruction* meta,
                                FIRUserInterfaceBlockInstruction<T>* firinterface,
                                FIRBlockInstruction<T>* static_init,
                                FIRBlockInstruction<T>* init,
                                FIRBlockInstruction<T>* resetui,
                                FIRBlockInstruction<T>* clear,
                                FIRBlockInstruction<T>* compute_control,
                                FIRBlockInstruction<T>* compute_dsp)
    :dsp_factory_imp(name, sha_key, "", pathname_list),
    fVersion(version_num),
    fNumInputs(inputs),
    fNumOutputs(outputs),
    fIntHeapSize(int_heap_size),
    fRealHeapSize(real_heap_size),
    fSROffset(sr_offset),
    fCountOffset(count_offset),
    fIOTAOffset(iota_offset),
    fOptLevel(opt_level),
    fOptimized(false),
    fMetaBlock(meta),
    fUserInterfaceBlock(firinterface),
    fStaticInitBlock(static_init),
    fInitBlock(init),
    fResetUIBlock(resetui),
    fClearBlock(clear),
    fComputeBlock(compute_control),
    fComputeDSPBlock(compute_dsp)
    {}

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
    }

    void optimize()
    {
        if (!fOptimized) {
            fOptimized = true;
            // Bytecode optimization
            if (TRACE == 0) {
                fStaticInitBlock = FIRInstructionOptimizer<T>::optimizeBlock(fStaticInitBlock, 1, fOptLevel);
                fInitBlock = FIRInstructionOptimizer<T>::optimizeBlock(fInitBlock, 1, fOptLevel);
                fResetUIBlock = FIRInstructionOptimizer<T>::optimizeBlock(fResetUIBlock, 1, fOptLevel);
                fClearBlock = FIRInstructionOptimizer<T>::optimizeBlock(fClearBlock, 1, fOptLevel);
                fComputeBlock = FIRInstructionOptimizer<T>::optimizeBlock(fComputeBlock, 1, fOptLevel);
                fComputeDSPBlock = FIRInstructionOptimizer<T>::optimizeBlock(fComputeDSPBlock, 1, fOptLevel);
            }
        }
    }

    void write(std::ostream* out, bool binary = false, bool small = false)
    {
        *out << std::setprecision(std::numeric_limits<T>::max_digits10);

        if (small) {
            *out << "i " << ((sizeof(T) == 8) ? "double" : "float") << std::endl;
            *out << "v " << FAUSTVERSION << std::endl;
            *out << "f " << INTERP_FILE_VERSION << std::endl;
            *out << "n " << fName << std::endl;
            *out << "s " << fSHAKey << std::endl;
            *out << "o " << fOptLevel << std::endl;

            *out << "i " << fNumInputs << " o " << fNumOutputs << std::endl;
            *out << "i " << fIntHeapSize << " r " << fRealHeapSize
            << " s " << fSROffset
            << " c " << fCountOffset
            << " i " << fIOTAOffset << std::endl;

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
            *out << "interpreter_dsp_factory " << ((sizeof(T) == 8) ? "double" : "float") << std::endl;
            *out << "version " << FAUSTVERSION << std::endl;
            *out << "file " << INTERP_FILE_VERSION << std::endl;
            *out << "name " << fName << std::endl;
            *out << "sha_key " << fSHAKey << std::endl;
            *out << "opt_level " << fOptLevel << std::endl;

            *out << "inputs " << fNumInputs << " outputs " << fNumOutputs << std::endl;
            *out << "int_heap_size " << fIntHeapSize << " real_heap_size " << fRealHeapSize
            << " sr_offset " << fSROffset
            << " count_offset " << fCountOffset
            << " iota_offset " << fIOTAOffset << std::endl;

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

        // Read "version" line
        std::string version;
        getline(*in, version);

        // Read "file" line
        std::string file;
        int file_num;
        getline(*in, file);

        std::stringstream version_reader(file);
        version_reader >> dummy;   // Read "version" token
        version_reader >> file_num;

        if (INTERP_FILE_VERSION != file_num) {
            std::cerr << "Interpreter file format version '" << file_num
            << "' different from compiled one '" << INTERP_FILE_VERSION << "'" << std::endl;
            return 0;
        }

        // Read name
        std::string name, factory_name;
        getline(*in, name);

        std::stringstream name_reader(name);
        name_reader >> dummy;   // Read "name" token
        name_reader >> factory_name;

        // Read sha_key
        std::string sha_key_line, sha_key;
        getline(*in, sha_key_line);

        std::stringstream sha_key_line_reader(sha_key_line);
        sha_key_line_reader >> dummy;   // Read "sha_key" token
        sha_key_line_reader >> sha_key;

        // Read opt_level
        std::string opt_level_line;
        int opt_level;
        getline(*in, opt_level_line);

        std::stringstream opt_level_line_reader(opt_level_line);
        opt_level_line_reader >> dummy;   // Read "opt_level" token
        opt_level_line_reader >> opt_level;

        // Read inputs/outputs
        std::string ins_outs;
        int inputs, outputs;
        getline(*in, ins_outs);

        std::stringstream in_out_reader(ins_outs);

        in_out_reader >> dummy; // Read "inputs" token
        in_out_reader >> inputs;

        in_out_reader >> dummy; // Read "outputs" token
        in_out_reader >> outputs;

        // Read int/real heap size and sr offset
        std::string heap_size;
        int int_heap_size, real_heap_size, sr_offset, count_offset, iota_offset;
        getline(*in, heap_size);

        std::stringstream heap_size_reader(heap_size);

        heap_size_reader >> dummy; // Read "int_heap_size" token
        heap_size_reader >> int_heap_size;

        heap_size_reader >> dummy; // Read "real_heap_size" token
        heap_size_reader >> real_heap_size;

        heap_size_reader >> dummy; // Read "sr_offet" token
        heap_size_reader >> sr_offset;

        heap_size_reader >> dummy; // Read "count_offset" token
        heap_size_reader >> count_offset;

        heap_size_reader >> dummy; // Read "iota_offset" token
        heap_size_reader >> iota_offset;

        // Read meta block
        getline(*in, dummy);    // Read "meta_block" line
        FIRMetaBlockInstruction* meta_block = readMetaBlock(in);

        // Read user interface block
        getline(*in, dummy);    // Read "user_interface_block" line
        FIRUserInterfaceBlockInstruction<T>* ui_block = readUIBlock(in);

        // Read static init block
        getline(*in, dummy);    // Read "static_init_block" line
        FIRBlockInstruction<T>* static_init_block = readCodeBlock(in);

        // Read constants block
        getline(*in, dummy);    // Read "constants_block" line
        FIRBlockInstruction<T>* init_block = readCodeBlock(in);

        // Read default ui block
        getline(*in, dummy);    // Read "clear_block" line
        FIRBlockInstruction<T>* resetui_block = readCodeBlock(in);

        // Read clear block
        getline(*in, dummy);    // Read "clear_block" line
        FIRBlockInstruction<T>* clear_block = readCodeBlock(in);

        // Read control block
        getline(*in, dummy);    // Read "control_block" line
        FIRBlockInstruction<T>* compute_control_block = readCodeBlock(in);

        // Read DSP block
        getline(*in, dummy);    // Read "dsp_block" line
        FIRBlockInstruction<T>* compute_dsp_block = readCodeBlock(in);

        std::vector<std::string> dummy_list;
        return new interpreter_dsp_factory_aux(factory_name,
                                               sha_key,
                                               dummy_list,
                                               file_num,
                                               inputs, outputs,
                                               int_heap_size,
                                               real_heap_size,
                                               sr_offset,
                                               count_offset,
                                               iota_offset,
                                               opt_level,
                                               meta_block,
                                               ui_block,
                                               static_init_block,
                                               init_block,
                                               resetui_block,
                                               clear_block,
                                               compute_control_block,
                                               compute_dsp_block);
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
        int size;

        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);

        line_reader >> dummy; // Read "block_size" token
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
        int size;

        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);

        line_reader >> dummy; // Read "block_size" token
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
        int opcode, offset;
        T init, min, max, step;
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

        return new FIRUserInterfaceInstruction<T>(FIRInstruction::Opcode(opcode), offset,
                                                  unquote1(label), unquote1(key),
                                                  unquote1(val),
                                                  init, min, max, step);
    }

    static FIRBlockInstruction<T>* readCodeBlock(std::istream* in)
    {
        std::string dummy, line;
        int size;

        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);

        line_reader >> dummy; // Read "block_size" token
        line_reader >> size;

        FIRBlockInstruction<T>* code_block = new FIRBlockInstruction<T>();

        for (int i = 0; i < size; i++) {
            getline(*in, line);
            std::stringstream inst_line_reader(line);
            FIRBasicInstruction<T>* inst = readCodeInstruction(&inst_line_reader, in);
            // Special case for loops
            if (inst->fOpcode == FIRInstruction::kCondBranch) { inst->fBranch1 = code_block; }
            code_block->push(inst);
        }

        return code_block;
    }

    static FIRBasicInstruction<T>* readCodeInstruction(std::istream* inst, std::istream* in)
    {
        int opcode, offset1, offset2;
        int val_int;
        T val_real;

        std::string dummy, line;
        *inst >> dummy;  // Read "opcode" token
        *inst >> opcode;

        *inst >> dummy;  // Read opcode string representation (that is not used)

        if (opcode == FIRInstruction::kBlockStoreReal) {

            int block_size;
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

            return new FIRBlockStoreRealInstruction<T>(FIRInstruction::Opcode(opcode), offset1, offset2, block_values);

        } else if (opcode == FIRInstruction::kBlockStoreInt) {

            int block_size;
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

            return new FIRBlockStoreIntInstruction<T>(FIRInstruction::Opcode(opcode), offset1, offset2, block_values);

        } else {

            *inst >> dummy;  // Read "int" token
            *inst >> val_int;

            *inst >> dummy;  // Read "real" token
            *inst >> val_real;

            *inst >> dummy;  // Read "offset1" token
            *inst >> offset1;

            *inst >> dummy;  // Read "offset2" token
            *inst >> offset2;

            FIRBlockInstruction<T>* branch1 = 0;
            FIRBlockInstruction<T>* branch2 = 0;

            // Possibly read sub-blocks
            if (FIRInstruction::isChoice(FIRInstruction::Opcode(opcode))) {
                branch1 = readCodeBlock(in);  // consume 'in'
                branch2 = readCodeBlock(in);  // consume 'in'
            } else if (opcode == FIRInstruction::kLoop) {
                branch1 = readCodeBlock(in);  // consume 'in'
                branch2 = readCodeBlock(in);  // consume 'in'
            }

            return new FIRBasicInstruction<T>(FIRInstruction::Opcode(opcode), val_int, val_real, offset1, offset2, branch1, branch2);
        }
    }

    void metadata(Meta* meta)
    {
        ExecuteMeta(fMetaBlock, meta);
    }

    void ExecuteMeta(FIRMetaBlockInstruction* block, Meta* meta)
    {
        MetaInstructionIT it;
        for (it = block->fInstructions.begin(); it != block->fInstructions.end(); it++) {
            meta->declare((*it)->fKey.c_str(), (*it)->fValue.c_str());
        }
    }

    dsp* createDSPInstance(dsp_factory* factory);

};

struct interpreter_dsp_base : public dsp {

    virtual ~interpreter_dsp_base()
    {}

    // Not implemented...
    void buildUserInterface(UI* ui_interface) {}

    // Replaced by this one
    virtual void buildUserInterface(UITemplate* glue) = 0;

    virtual void instanceInit(int samplingRate) {}

    virtual void instanceConstants(int samplingRate) {}

    virtual void instanceResetUserInterface() {}

    virtual void instanceClear() {}

    // Not implemented...
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}

    virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}

};

template <class T, int TRACE>
class interpreter_dsp_aux : public interpreter_dsp_base, public FIRInterpreter<T, TRACE> {

    protected:

        /*
        FIRBlockInstruction<T>* fStaticInitBlock;
        FIRBlockInstruction<T>* fInitBlock;
        FIRBlockInstruction<T>* fResetUIBlock;
        FIRBlockInstruction<T>* fClearBlock;
        FIRBlockInstruction<T>* fComputeBlock;
        FIRBlockInstruction<T>* fComputeDSPBlock;
        */

        std::map<int, int> fIntMap;
        std::map<int, T> fRealMap;
        bool fInitialized;
 
    public:

        interpreter_dsp_aux(interpreter_dsp_factory_aux<T, TRACE>* factory)
        : FIRInterpreter<T, TRACE>(factory)
        {
            if (this->fFactory->getMemoryManager()) {
                this->fInputs = static_cast<T**>(this->fFactory->allocate(sizeof(T*) * this->fFactory->fNumInputs));
                this->fOutputs = static_cast<T**>(this->fFactory->allocate(sizeof(T*) * this->fFactory->fNumOutputs));
            } else {
                this->fInputs = new T*[this->fFactory->fNumInputs];
                this->fOutputs = new T*[this->fFactory->fNumOutputs];
            }

            // Comment to allow specialization...
            this->fFactory->optimize();

            /*
            fFactory->fStaticInitBlock->write(&std::cout, false);
            fFactory->fInitBlock->write(&std::cout, false);
            fFactory->fResetUIBlock->write(&std::cout, false);
            fFactory->fClearBlock->write(&std::cout, false);
            fFactory->fComputeBlock->write(&std::cout, false);
            fFactory->fComputeDSPBlock->write(&std::cout, false);
            std::cout << "size " << fFactory->fComputeDSPBlock->size() << std::endl;
            */

            /*
            this->fStaticInitBlock = 0;
            this->fInitBlock = 0;
            this->fResetUIBlock = 0;
            this->fClearBlock = 0;
            this->fComputeBlock = 0;
            this->fComputeDSPBlock = 0;
            */
            this->fInitialized = false;
        }

        virtual ~interpreter_dsp_aux()
        {
            if (this->fFactory->getMemoryManager()) {
                this->fFactory->destroy(this->fInputs);
                this->fFactory->destroy(this->fOutputs);
            } else {
                delete [] this->fInputs;
                delete [] this->fOutputs;
            }

            /*
            delete this->fStaticInitBlock;
            delete this->fInitBlock;
            delete this->fResetUIBlock;
            delete this->fClearBlock;
            delete this->fComputeBlock;
            delete this->fComputeDSPBlock;
            */
        }

        virtual void metadata(Meta* meta)
        {
            this->fFactory->metadata(meta);
        }

        virtual int getSampleRate()
        {
            return this->fIntMap[this->fFactory->fSROffset];
        }

        // to be implemented by subclass
        virtual dsp* clone()
        {
            faustassert(false);
            return nullptr;
        }

        virtual int getNumInputs()
        {
            return this->fFactory->fNumInputs;
        }

        virtual int getNumOutputs()
        {
            return this->fFactory->fNumOutputs;
        }

        virtual int getInputRate(int channel)
        {
            return -1;
        }

        virtual int getOutputRate(int channel)
        {
            return -1;
        }

        virtual void classInit(int samplingRate)
        {
            // Execute static init instructions
            this->ExecuteBlock(this->fFactory->fStaticInitBlock);
        }

        virtual void instanceConstants(int samplingRate)
        {
            // Store samplingRate in specialization fIntMap
            this->fIntMap[this->fFactory->fSROffset] = samplingRate;

            // Store samplingRate in 'fSamplingFreq' variable at correct offset in fIntHeap
            this->fIntHeap[this->fFactory->fSROffset] = samplingRate;

            // Execute state init instructions
            this->ExecuteBlock(this->fFactory->fInitBlock);
        }

        virtual void instanceResetUserInterface()
        {
            // Execute reset UI instructions
            this->ExecuteBlock(this->fFactory->fResetUIBlock);
        }

        virtual void instanceClear()
        {
            // Execute clear instructions
            this->ExecuteBlock(this->fFactory->fClearBlock);
        }

        virtual void instanceInit(int samplingRate)
        {
            this->instanceConstants(samplingRate);
            this->instanceResetUserInterface();
            this->instanceClear();
        }

        virtual void init(int samplingRate)
        {
            this->fInitialized = true;
            this->classInit(samplingRate);
            this->instanceInit(samplingRate);
        }

        /*
        virtual void init(int samplingRate)
        {
            // Store samplingRate in specialization fIntMap
            this->fIntMap[this->fSROffset] = samplingRate;

            // Store samplingRate in 'fSamplingFreq' variable at correct offset in fIntHeap
            this->fIntHeap[this->fSROffset] = samplingRate;

            this->classInit(samplingRate);
            this->instanceInit(samplingRate);

            this->fStaticInitBlock = FIRInstructionOptimizer<T>::specialize2Heap(fFactory->fStaticInitBlock->copy(), fIntMap, fRealMap);
            this->fInitBlock = FIRInstructionOptimizer<T>::specialize2Heap(fFactory->fInitBlock->copy(), fIntMap, fRealMap);
            this->fResetUIBlock = FIRInstructionOptimizer<T>::specialize2Heap(fFactory->fResetUIBlock->copy(), fIntMap, fRealMap);
            this->fClearBlock = FIRInstructionOptimizer<T>::specialize2Heap(fFactory->fClearBlock->copy(), fIntMap, fRealMap);

            // Suppress IOTA from fRealMap since we don't want specialization to use it
            if (this->fIntMap.find(fFactory->fIOTAOffset) != this->fIntMap.end()) {
                this->fIntMap.erase(this->fIntMap.find(fFactory->fIOTAOffset));
            }

            // Keep control ON
            fFactory->fUserInterfaceBlock->unFreezeDefaultValues(fRealMap, FIRInstruction::kAddButton);
            //fFactory->fUserInterfaceBlock->unFreezeDefaultValues(fRealMap);

            // Specialization
            //this->fComputeBlock = FIRInstructionOptimizer<T>::optimizeBlock(fFactory->fComputeBlock->copy(), 4);

            this->fComputeBlock = FIRInstructionOptimizer<T>::specialize(fFactory->fComputeBlock->copy(), fIntMap, fRealMap);
            this->fComputeDSPBlock = FIRInstructionOptimizer<T>::optimizeBlock(fFactory->fComputeDSPBlock->copy(), 1, 4);
            this->fComputeDSPBlock = FIRInstructionOptimizer<T>::specialize(this->fComputeDSPBlock, fIntMap, fRealMap);

            // Optimization
            this->fComputeBlock = FIRInstructionOptimizer<T>::optimizeBlock(this->fComputeBlock, 5, 6);
            this->fComputeDSPBlock = FIRInstructionOptimizer<T>::optimizeBlock(this->fComputeDSPBlock, 5, 6);

            std::cout << "INIT" << std::endl;

            this->fStaticInitBlock->write(&std::cout, false);
            this->fInitBlock->write(&std::cout, false);
            this->fResetUIBlock->write(&std::cout, false);
            this->fClearBlock->write(&std::cout, false);
            this->fComputeBlock->write(&std::cout, false);
            this->fComputeDSPBlock->write(&std::cout, false);
        }
        */

        virtual void buildUserInterface(UITemplate* glue)
        {
            //std::cout << "buildUserInterface" << std::endl;
            this->ExecuteBuildUserInterface(this->fFactory->fUserInterfaceBlock, glue);
        }

        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
        {
            if (TRACE > 0 && !fInitialized) {
                std::cout << "-------- DSP is not initialized ! --------" << std::endl;
            } else {
                //std::cout << "compute " << count << std::endl;
                T** inputs = reinterpret_cast<T**>(input);
                T** outputs = reinterpret_cast<T**>(output);

                // Prepare in/out buffers
                for (int i = 0; i < this->fFactory->fNumInputs; i++) {
                    this->fInputs[i] = inputs[i];
                }
                for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
                    this->fOutputs[i] = outputs[i];
                }

                // Set count in 'count' variable at the correct offset in fIntHeap
                this->fIntHeap[this->fFactory->fCountOffset] = count;

                // Executes the 'control' block
                this->ExecuteBlock(this->fFactory->fComputeBlock);

                // Executes the 'DSP' block
                this->ExecuteBlock(this->fFactory->fComputeDSPBlock);
            }
        }

        /*
        // Version with specialization
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
        {
        #ifdef INTERPRETER_TRACE
            if (!fInitialized) {
                std::cout << "-------- DSP is not initialized ! --------" << std::endl;
            } else
        #endif
            {
                //std::cout << "compute " << count << std::endl;

                T** inputs = reinterpret_cast<T**>(input);
                T** outputs = reinterpret_cast<T**>(output);

                // Prepare in/out buffers
                for (int i = 0; i < this->fFactory->fNumInputs; i++) {
                    this->fInputs[i] = inputs[i];
                }
                for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
                    this->fOutputs[i] = outputs[i];
                }

                // Set count in 'count' variable at the correct offset in fIntHeap
                this->fIntHeap[this->fCountOffset] = count;

                // Executes the 'control' block
                this->ExecuteBlock(this->fComputeBlock);

                // Executes the 'DSP' block
                this->ExecuteBlock(this->fComputeDSPBlock);
            }
        }
        */

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
            // Allocate and set downsampled inputs/outputs
            for (int i = 0; i < this->fFactory->fNumInputs; i++) {
                this->fInputs[i] = (this->fFactory->getMemoryManager()) ? static_cast<T*>(this->fFactory->allocate(sizeof(T) * 2048)) :  new T[2048];
            }
            for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
                this->fOutputs[i] = (this->fFactory->getMemoryManager()) ? static_cast<T*>(this->fFactory->allocate(sizeof(T) * 2048)) :  new T[2048];
            }
        }

        virtual ~interpreter_dsp_aux_down()
        {
            // Delete downsampled inputs/outputs
            for (int i = 0; i < this->fFactory->fNumInputs; i++) {
                (this->fFactory->getMemoryManager()) ? this->fFactory->destroy(this->fInputs[i]) : delete [] this->fInputs[i];
            }
            for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
                (this->fFactory->getMemoryManager()) ? this->fFactory->destroy(this->fOutputs[i]) : delete [] this->fOutputs[i];
            }
        }

        virtual void init(int samplingRate)
        {
            this->classInit(samplingRate / fDownSamplingFactor);
            this->instanceInit(samplingRate / fDownSamplingFactor);
        }

        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
        {
            T** inputs = reinterpret_cast<T**>(input);
            T** outputs = reinterpret_cast<T**>(output);

            // Downsample inputs
            for (int i = 0; i < this->fFactory->fNumInputs; i++) {
                for (int j = 0; j < count / fDownSamplingFactor; j++) {
                    this->fInputs[i][j] = inputs[i][j * fDownSamplingFactor];
                }
            }

            // Executes the 'control' block
            this->ExecuteBlock(this->fFactory->fComputeBlock);

            // Set count in 'count' variable at the correct offset in fIntHeap
            this->fIntHeap[this->fCountOffset] = count / fDownSamplingFactor;

            // Executes the 'DSP' block
            this->ExecuteBlock(this->fFactory->fComputeDSPBlock);

            // Upsample ouputs
            for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
                for (int j = 0; j < count / fDownSamplingFactor; j++) {
                    T sample = this->fOutputs[i][j];
                    outputs[i][j * fDownSamplingFactor] = sample;
                    outputs[i][(j * fDownSamplingFactor) + 1] = sample;
                }
            }

            //std::cout << "sample " << outputs[0][0] << std::endl;
        }

};

// Public C++ interface

class EXPORT interpreter_dsp : public dsp {

    private:

        interpreter_dsp_factory* fFactory;
        interpreter_dsp_base* fDSP;

    public:
    
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 0>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 0>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 1>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 1>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 2>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 2>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 3>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 3>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 4>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 4>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<float, 5>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}
        interpreter_dsp(interpreter_dsp_factory* factory, interpreter_dsp_aux<double, 5>* dsp)
            :fFactory(factory), fDSP(dsp)
        {}

        virtual ~interpreter_dsp();

        void operator delete(void* ptr);

        int getNumInputs();

        int getNumOutputs();

        void buildUserInterface(UI* ui_interface);

        int getSampleRate();

        void init(int samplingRate);

        void instanceInit(int samplingRate);

        void instanceConstants(int samplingRate);

        void instanceResetUserInterface();

        void instanceClear();

        interpreter_dsp* clone();

        void metadata(Meta* meta);

        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);

};

class EXPORT interpreter_dsp_factory : public dsp_factory, public faust_smartable {

    protected:

        dsp_factory_base* fFactory;

        virtual ~interpreter_dsp_factory()
        {
            delete fFactory;
        }

    public:

        interpreter_dsp_factory(dsp_factory_base* factory):fFactory(factory)
        {}

        std::string getName() { return fFactory->getName(); }

        std::string getSHAKey() { return fFactory->getSHAKey(); }
        void setSHAKey(std::string sha_key) { fFactory->setSHAKey(sha_key); }

        std::string getDSPCode() { return fFactory->getDSPCode(); }
        void setDSPCode(std::string code) { fFactory->setDSPCode(code); }

        interpreter_dsp* createDSPInstance();

        void setMemoryManager(dsp_memory_manager* manager) { fFactory->setMemoryManager(manager); }
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
            interpreter_dsp(tmp,
                new (tmp->getFactory()->allocate(sizeof(interpreter_dsp_aux<T, TRACE>)))
                    interpreter_dsp_aux<T, TRACE>(this));
    } else {
        return new interpreter_dsp(tmp, new interpreter_dsp_aux<T, TRACE>(this));
    }
}

EXPORT interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const std::string& sha_key);

EXPORT interpreter_dsp_factory* createInterpreterDSPFactoryFromFile(const std::string& filename,
                                                                  int argc, const char* argv[],
                                                                  std::string& error_msg);

EXPORT interpreter_dsp_factory* createInterpreterDSPFactoryFromString(const std::string& name_app,
                                                                    const std::string& dsp_content,
                                                                    int argc, const char* argv[],
                                                                    std::string& error_msg);

EXPORT bool deleteInterpreterDSPFactory(interpreter_dsp_factory* factory);

EXPORT std::vector<std::string> getInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory);

EXPORT std::vector<std::string> getAllInterpreterDSPFactories();

EXPORT interpreter_dsp_factory* readInterpreterDSPFactoryFromMachine(const std::string& machine_code);

EXPORT std::string writeInterpreterDSPFactoryToMachine(interpreter_dsp_factory* factory);

EXPORT interpreter_dsp_factory* readInterpreterDSPFactoryFromMachineFile(const std::string& machine_code_path);

EXPORT void writeInterpreterDSPFactoryToMachineFile(interpreter_dsp_factory* factory, const std::string& machine_code_path);

EXPORT void deleteAllInterpreterDSPFactories();

#endif
