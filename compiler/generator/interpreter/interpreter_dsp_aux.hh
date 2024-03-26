/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef interpreter_dsp_aux_h
#define interpreter_dsp_aux_h

#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "faust/export.h"

#include "dsp_aux.hh"
#include "dsp_factory.hh"
#include "interpreter_bytecode.hh"
#include "fbc_interpreter.hh"

static inline void checkToken(const std::string& token, const std::string& expected)
{
    if (token != expected) throw faustexception("ERROR : unrecognized file format [" + token + "] [" + expected + "]\n");
}

static inline std::string replace_first(std::string s, const std::string& toReplace, const std::string& replaceWith)
{
    std::size_t pos = s.find(toReplace);
    if (pos == std::string::npos) {
        return s;
    } else {
        s.replace(pos, toReplace.length(), replaceWith);
        return s;
    }
}

class interpreter_dsp_factory;

typedef class faust_smartptr<interpreter_dsp_factory> SDsp_factory;
extern dsp_factory_table<SDsp_factory> gInterpreterFactoryTable;

template <class REAL, int TRACE>
class interpreter_dsp_aux;

template <class REAL, int TRACE>
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

    bool        fOptimized;
    std::string fCompileOptions;

    FIRMetaBlockInstruction*                fMetaBlock;
    FIRUserInterfaceBlockInstruction<REAL>* fUserInterfaceBlock;
    FBCBlockInstruction<REAL>*              fStaticInitBlock;
    FBCBlockInstruction<REAL>*              fInitBlock;
    FBCBlockInstruction<REAL>*              fResetUIBlock;
    FBCBlockInstruction<REAL>*              fClearBlock;
    FBCBlockInstruction<REAL>*              fComputeBlock;
    FBCBlockInstruction<REAL>*              fComputeDSPBlock;

    interpreter_dsp_factory_aux(const std::string& name, const std::string& compile_options, const std::string& sha_key,
                                int version_num, int inputs, int outputs, int int_heap_size, int real_heap_size,
                                int sr_offset, int count_offset, int iota_offset, int opt_level,
                                FIRMetaBlockInstruction* meta, FIRUserInterfaceBlockInstruction<REAL>* firinterface,
                                FBCBlockInstruction<REAL>* static_init, FBCBlockInstruction<REAL>* init,
                                FBCBlockInstruction<REAL>* resetui, FBCBlockInstruction<REAL>* clear,
                                FBCBlockInstruction<REAL>* compute_control, FBCBlockInstruction<REAL>* compute_dsp)
        : dsp_factory_imp(name, sha_key, ""),
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
    {
    // Hack to display the LLVM or MIR used compiler
#if INTERP_MIR_BUILD
    fCompileOptions = replace_first(compile_options, "interp", "interp-mir");
#elif INTERP_LLVM_BUILD
    fCompileOptions = replace_first(compile_options, "interp", "interp-llvm");
#else
    fCompileOptions = compile_options;
#endif
    }

    virtual FBCExecutor<REAL>* createFBCExecutor()
    {
       return new FBCInterpreter<REAL, TRACE>(this);
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
    }

    void optimize(); // moved in interpreted_dsp.hh
 
    void write(std::ostream* out, bool binary = false, bool small = false)
    {
        *out << std::setprecision(std::numeric_limits<REAL>::digits10+1);
        if (small) {
            *out << "i " << ((sizeof(REAL) == sizeof(double)) ? "double" : "float") << std::endl;
            *out << "f " << INTERP_FILE_VERSION << std::endl;
            *out << "v " << FAUSTVERSION << std::endl;
            *out << "c " << fCompileOptions << std::endl;
            *out << "n " << fName << std::endl;
            *out << "s " << fSHAKey << std::endl;
            *out << "o " << fOptLevel << std::endl;
            *out << "i " << fNumInputs << " o " << fNumOutputs << std::endl;

            *out << "i " << fIntHeapSize << " r " << fRealHeapSize << " s " << fSROffset
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
            *out << "interpreter_dsp_factory " << ((sizeof(REAL) == sizeof(double)) ? "double" : "float") << std::endl;
            *out << "file_version " << INTERP_FILE_VERSION << std::endl;
            *out << "Faust version " << FAUSTVERSION << std::endl;
            *out << "compile_options " << fCompileOptions << std::endl;
            *out << "name " << fName << std::endl;
            *out << "sha_key " << fSHAKey << std::endl;
            *out << "opt_level " << fOptLevel << std::endl;

            *out << "inputs " << fNumInputs << " outputs " << fNumOutputs << std::endl;

            *out << "int_heap_size " << fIntHeapSize << " real_heap_size " << fRealHeapSize << " sr_offset "
                 << fSROffset << " count_offset " << fCountOffset << " iota_offset "
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
    
    std::string getCompileOptions() { return fCompileOptions; };

    // Factory reader
    static interpreter_dsp_factory_aux<REAL, TRACE>* read(std::istream* in);

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

    static FIRUserInterfaceBlockInstruction<REAL>* readUIBlock(std::istream* in)
    {
        std::string dummy, line;
        int         size;

        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);

        line_reader >> dummy;  // Read "block_size" token
        line_reader >> size;

        FIRUserInterfaceBlockInstruction<REAL>* ui_block = new FIRUserInterfaceBlockInstruction<REAL>();

        for (int i = 0; i < size; i++) {
            getline(*in, line);
            std::stringstream item_line_reader(line);
            ui_block->push(readUIInstruction(&item_line_reader));
        }

        return ui_block;
    }

    static FIRUserInterfaceInstruction<REAL>* readUIInstruction(std::stringstream* inst)
    {
        int         opcode, offset;
        REAL        init, min, max, step;
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

        return new FIRUserInterfaceInstruction<REAL>(FBCInstruction::Opcode(opcode), offset, unquote1(label),
                                                  unquote1(key), unquote1(val), init, min, max, step);
    }

    static FBCBlockInstruction<REAL>* readCodeBlock(std::istream* in)
    {
        std::string dummy, line;
        int         size;

        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);

        line_reader >> dummy;  // Read "block_size" token
        line_reader >> size;

        FBCBlockInstruction<REAL>* code_block = new FBCBlockInstruction<REAL>();

        for (int i = 0; i < size; i++) {
            getline(*in, line);
            std::stringstream       inst_line_reader(line);
            FBCBasicInstruction<REAL>* inst = readCodeInstruction(&inst_line_reader, in);
            // Special case for loops
            if (inst->fOpcode == FBCInstruction::kCondBranch) {
                inst->fBranch1 = code_block;
            }
            code_block->push(inst);
        }

        return code_block;
    }

    static FBCBasicInstruction<REAL>* readCodeInstruction(std::istream* inst, std::istream* in)
    {
        int opcode, offset1, offset2;
        int  val_int;
        REAL val_real;

        std::string dummy, line;
        *inst >> dummy;  // Read "opcode" token
        *inst >> opcode;

        *inst >> dummy;  // Read opcode string representation (that is not used)

        if (opcode == FBCInstruction::kBlockStoreReal) {
            int            block_size;
            std::vector<REAL> block_values;

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

            return new FIRBlockStoreRealInstruction<REAL>(FBCInstruction::Opcode(opcode), offset1, offset2, block_values);

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

            return new FIRBlockStoreIntInstruction<REAL>(FBCInstruction::Opcode(opcode), offset1, offset2, block_values);

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

            FBCBlockInstruction<REAL>* branch1 = nullptr;
            FBCBlockInstruction<REAL>* branch2 = nullptr;

            // Possibly read sub-blocks
            if (FBCInstruction::isChoice(FBCInstruction::Opcode(opcode))) {
                branch1 = readCodeBlock(in);  // consume 'in'
                branch2 = readCodeBlock(in);  // consume 'in'
            } else if (opcode == FBCInstruction::kLoop) {
                branch1 = readCodeBlock(in);  // consume 'in'
                branch2 = readCodeBlock(in);  // consume 'in'
            }

            return new FBCBasicInstruction<REAL>(FBCInstruction::Opcode(opcode), name, val_int, val_real, offset1, offset2,
                                              branch1, branch2);
        }
    }

    void metadata(Meta* meta)
    {
        for (const auto& it : fMetaBlock->fInstructions) {
            meta->declare(it->fKey.c_str(), it->fValue.c_str());
        }
    }
    
    void metadata(MetaGlue* meta)
    {
        for (const auto& it : fMetaBlock->fInstructions) {
            meta->declare(meta->metaInterface, it->fKey.c_str(), it->fValue.c_str());
        }
    }

    dsp* createDSPInstance(dsp_factory* factory);
};

struct interpreter_dsp_base : public dsp {
    
    virtual ~interpreter_dsp_base() {}

    // Not implemented...
    void buildUserInterface(UI* ui_interface) {}

    // Replaced by this one
    virtual void buildUserInterface(UIInterface* glue) = 0;

    virtual void instanceInit(int sample_rate) {}

    virtual void instanceConstants(int sample_rate) {}

    virtual void instanceResetUserInterface() {}

    virtual void instanceClear() {}
    
    virtual void metadata(Meta* meta) {}
    
    virtual void metadata(MetaGlue* meta) {}

    // Not implemented...
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}

    virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
};

template <class REAL, int TRACE>
class interpreter_dsp_aux : public interpreter_dsp_base {
   protected:
    bool                                   fInitialized;
    bool                                   fTraceOutput;
    int                                    fCycle;
    interpreter_dsp_factory_aux<REAL, TRACE>* fFactory;
    FBCExecutor<REAL>*                     fFBCExecutor;

   public:
    interpreter_dsp_aux()
        : fInitialized(false), fTraceOutput(false), fCycle(0), fFactory(nullptr), fFBCExecutor(nullptr)
    {
    }

    interpreter_dsp_aux(interpreter_dsp_factory_aux<REAL, TRACE>* factory)
    {
        fFactory = factory;
        fInitialized = false;
        fCycle = 0;
        fTraceOutput = getenv("FAUST_INTERP_OUTPUT") != NULL;
        // Done before createFBCExecutor that may compile blocks...
        fFactory->optimize();
        fFBCExecutor = factory->createFBCExecutor();
    }

    virtual ~interpreter_dsp_aux()
    {
        delete fFBCExecutor;
    }

    // Freeze values
    void freezeValues(std::map<int, int>& int_map, std::map<int, REAL>& real_map)
    {
        std::cout << "freezeValues Int " << std::endl;
        for (const auto& it1 : int_map) {
            std::cout << "offset " << it1.first << " value " << it1.second << std::endl;
            this->fIntHeap[it1.first] = it1.second;
        }

        std::cout << "freezeValues Real" << std::endl;
        for (const auto& it2 : real_map) {
            std::cout << "offset " << it2.first << " value " << it2.second << std::endl;
            this->fRealHeap[it2.first] = it2.second;
        }
    }

    virtual void metadata(Meta* meta) { fFactory->metadata(meta); }
    
    virtual void metadata(MetaGlue* meta) { fFactory->metadata(meta); }

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
        
        try {
            // Execute static init instructions
            fFBCExecutor->executeBlock(fFactory->fStaticInitBlock);
        } catch (faustexception& e) {
            std::cerr << e.Message();
            exit(1);
        }
    }

    virtual void instanceConstants(int sample_rate)
    {
        if (TRACE > 0) {
            std::cout << "------------------------" << std::endl;
            std::cout << "instanceConstants " << sample_rate << std::endl;
        }
        
        // Store sample_rate in 'fSampleRate' variable at correct offset in fIntHeap
        fFBCExecutor->setIntValue(fFactory->fSROffset, sample_rate);

        try {
            // Execute state init instructions
            fFBCExecutor->executeBlock(fFactory->fInitBlock);
        } catch (faustexception& e) {
            std::cerr << e.Message();
            exit(1);
        }
    }

    virtual void instanceResetUserInterface()
    {
        if (TRACE > 0) {
            std::cout << "------------------------" << std::endl;
            std::cout << "instanceResetUserInterface " << std::endl;
        }
        
        try {
            // Execute reset UI instructions
            fFBCExecutor->executeBlock(fFactory->fResetUIBlock);
        } catch (faustexception& e) {
            std::cerr << e.Message();
            exit(1);
        }
    }

    virtual void instanceClear()
    {
        if (TRACE > 0) {
            std::cout << "------------------------" << std::endl;
            std::cout << "instanceClear " << std::endl;
        }
        
        try {
            // Execute clear instructions
            fFBCExecutor->executeBlock(fFactory->fClearBlock);
        } catch (faustexception& e) {
            std::cerr << e.Message();
            exit(1);
        }
    }

    virtual void instanceInit(int sample_rate)
    {
        if (TRACE > 0) {
            std::cout << "------------------------" << std::endl;
            std::cout << "instanceInit " << sample_rate << std::endl;
        }
        
        // classInit has to be called for each instance since the tables are actually not shared between instances
        classInit(sample_rate);
        
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
    
        // Possibly compile (when using LLVM or MIR)
        //fFBCExecutor->compileBlock(fFactory->fComputeBlock);
        fFBCExecutor->compileBlock(fFactory->fComputeDSPBlock);
        
        // classInit is not called here since the tables are actually not shared between instances
        instanceInit(sample_rate);
    }
    
    virtual void buildUserInterface(UIInterface* glue)
    {
        try {
            fFBCExecutor->executeBuildUserInterface(fFactory->fUserInterfaceBlock, glue);
        } catch (faustexception& e) {
            std::cerr << e.Message();
            exit(1);
        }
    }

    void ExecuteVecBlock(FBCBlockInstruction<REAL>* block, int vec_size)
    {
        /*
            Execute the VEC size specialized version of the interpreter
            vec_size == 1 correspond to the scalar interpreter
        */

        /*
        if (vec_size == 1) {
            fFBCExecutor->executeBlock<REAL, 1, TRACE>(block);
        } else if (vec_size == 4) {
            fFBCExecutor->executeBlock<REAL, 4, TRACE>(block);
        } else if (vec_size == 8) {
            fFBCExecutor->executeBlock<REAL, 8, TRACE>(block);
        } else if (vec_size == 16) {
            fFBCExecutor->executeBlock<REAL, 16, TRACE>(block);
        } else if (vec_size == 32) {
            fFBCExecutor->executeBlock<REAL, 32, TRACE>(block);
        } else if (vec_size == 64) {
            fFBCExecutor->executeBlock<REAL, 64, TRACE>(block);
        } else {
            fFBCExecutor->executeBlock<REAL, 128, TRACE>(block);
        }
        */
    }

    virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
    {
        if (count == 0) return;  // Beware: compiled loop does not work with an index of 0

        if (TRACE > 0 && !fInitialized) {
            std::cout << "======== DSP is not initialized ! ========" << std::endl;
        } else {
            
            if (TRACE > 0) {
                // A single display
                static bool display = true;
                if (display) {
                    std::cout << "------------------------" << std::endl;
                    std::cout << "compute " << count << std::endl;
                    display = false;
                }
            }
            
            REAL** inputs  = reinterpret_cast<REAL**>(inputs_aux);
            REAL** outputs = reinterpret_cast<REAL**>(outputs_aux);

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
                // Needed when used in DSPProxy
                fFBCExecutor->updateInputControls();
                
                // Executes the 'control' block
                fFBCExecutor->executeBlock(fFactory->fComputeBlock);

                // Executes the 'DSP' block
                fFBCExecutor->executeBlock(fFactory->fComputeDSPBlock);
                
                // Needed when used in DSPProxy
                fFBCExecutor->updateOutputControls();
                
            } catch (faustexception& e) {
                std::cerr << e.Message();
                std::vector<FBCBlockInstruction<REAL>*> blocks = {
                    fFactory->fStaticInitBlock,
                    fFactory->fInitBlock,
                    fFactory->fResetUIBlock,
                    fFactory->fClearBlock,
                    fFactory->fComputeBlock,
                    fFactory->fComputeDSPBlock
                };
                fFBCExecutor->dumpMemory(blocks,
                                         fFactory->getName(),
                                         "DumpMem-" + fFactory->getName() + std::to_string(fCycle) + ".txt");
                std::ofstream code_out("DumpCode-" + fFactory->getName() + ".txt");
                fFactory->write(&code_out, false);
                // If needed we exit
                if (e.Message() == "Interpreter exit\n") throw std::exception();
            }

            if ((TRACE == 7) && (fCycle < 4)) {
                std::vector<FBCBlockInstruction<REAL>*> blocks = {
                    fFactory->fStaticInitBlock,
                    fFactory->fInitBlock,
                    fFactory->fResetUIBlock,
                    fFactory->fClearBlock,
                    fFactory->fComputeBlock,
                    fFactory->fComputeDSPBlock
                };
                fFBCExecutor->dumpMemory(blocks,
                                         fFactory->getName(),
                                         "DumpMem-" + fFactory->getName() + std::to_string(fCycle) + ".txt");
            }

            if (fTraceOutput) {
                std::cout << std::setprecision(std::numeric_limits<REAL>::digits10+1);
                for (int chan = 0; chan < fFactory->fNumOutputs; chan++) {
                    for (int frame = 0; frame < count; frame++) {
                        std::cout << "Index : " << ((fCycle * count) + frame)
                                  << " chan: " << chan << " sample: " << outputs[chan][frame]
                                  << std::endl;
                    }
                }
            }
            fCycle++;
        }
    }
};

// Public C++ interface

class LIBFAUST_API interpreter_dsp : public dsp {
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
    
    void buildUserInterface(UIGlue* glue);
    
    int getSampleRate();

    void init(int sample_rate);

    void instanceInit(int sample_rate);

    void instanceConstants(int sample_rate);

    void instanceResetUserInterface();

    void instanceClear();

    interpreter_dsp* clone();

    void metadata(Meta* meta);
    
    void metadata(MetaGlue* meta);

    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
};

class LIBFAUST_API interpreter_dsp_factory : public dsp_factory, public faust_smartable {
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

    std::string getCompileOptions() { return fFactory->getCompileOptions(); }
    
    std::vector<std::string> getWarningMessages() { return fFactory->getWarningMessages(); }

    interpreter_dsp* createDSPInstance();

    // TODO
    std::vector<std::string> getLibraryList() { return std::vector<std::string>(); }
    std::vector<std::string> getIncludePathnames() { return std::vector<std::string>(); }

    void                setMemoryManager(dsp_memory_manager* manager) { fFactory->setMemoryManager(manager); }
    dsp_memory_manager* getMemoryManager() { return fFactory->getMemoryManager(); }

    dsp_factory_base* getFactory() { return fFactory; }

    void write(std::ostream* out, bool binary = false, bool small = false) { fFactory->write(out, binary, small); }
};

LIBFAUST_API interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const std::string& sha_key);

LIBFAUST_API bool deleteInterpreterDSPFactory(interpreter_dsp_factory* factory);

LIBFAUST_API std::vector<std::string> getInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory);

LIBFAUST_API std::vector<std::string> getAllInterpreterDSPFactories();

LIBFAUST_API interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcode(const std::string& bitcode,
                                                                        std::string& error_msg);

LIBFAUST_API std::string writeInterpreterDSPFactoryToBitcode(interpreter_dsp_factory* factory);

LIBFAUST_API interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcodeFile(const std::string& bitcode_path,
                                                                            std::string& error_msg);

LIBFAUST_API bool writeInterpreterDSPFactoryToBitcodeFile(interpreter_dsp_factory* factory, const std::string& bitcode_path);

LIBFAUST_API void deleteAllInterpreterDSPFactories();

#ifdef __cplusplus
extern "C" {
#endif

// Public C interface

LIBFAUST_API interpreter_dsp_factory* getCInterpreterDSPFactoryFromSHAKey(const char* sha_key);

LIBFAUST_API bool deleteCInterpreterDSPFactory(interpreter_dsp_factory* factory);

LIBFAUST_API const char** getCInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory);

LIBFAUST_API const char** getAllCInterpreterDSPFactories();

LIBFAUST_API interpreter_dsp_factory* readCInterpreterDSPFactoryFromBitcode(const char* bitcode, char* error_msg);

LIBFAUST_API char* writeCInterpreterDSPFactoryToBitcode(interpreter_dsp_factory* factory);

LIBFAUST_API interpreter_dsp_factory* readCInterpreterDSPFactoryFromBitcodeFile(const char* bitcode_path, char* error_msg);

LIBFAUST_API bool writeCInterpreterDSPFactoryToBitcodeFile(interpreter_dsp_factory* factory, const char* bitcode_path);

LIBFAUST_API void deleteAllCInterpreterDSPFactories();

#ifdef __cplusplus
}
#endif

#endif
