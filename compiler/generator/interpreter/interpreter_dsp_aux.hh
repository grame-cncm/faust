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
#include <libgen.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/UIGlue.h"
#include "faust/gui/meta.h"
#include "fir_interpreter.hh"
#include "interpreter_bytecode.hh"
//#include "smartpointer.h"

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__ ((visibility("default")))
#endif

static inline std::string unquote1(const std::string& str)
{
    return (str[0] == '"') ? str.substr(1, str.size() - 2) : str;
}

struct interpreter_dsp_factory_base {
    
    virtual ~interpreter_dsp_factory_base()
    {}
    
    virtual std::string getName() = 0;
    
    virtual std::string getSHAKey() = 0;
    
    virtual std::string getDSPCode() = 0;
    
    virtual void write(std::ostream* out) = 0;
    
    virtual dsp* createDSPInstance() = 0;
    
    virtual void metadata(Meta* meta) = 0;

};

template <class T>
class interpreter_dsp_aux;

template <class T>
struct interpreter_dsp_factory_aux : public interpreter_dsp_factory_base {
    
    std::string fExpandedDSP;
    std::string fShaKey;
    std::string fName;
    
    float fVersion;
    int fNumInputs;
    int fNumOutputs;
    
    int fIntHeapSize;
    int fRealHeapSize;
    int fSROffset;
    int fCountOffset;
    
    FIRMetaBlockInstruction* fMetaBlock;
    FIRUserInterfaceBlockInstruction<T>* fUserInterfaceBlock;
    FIRBlockInstruction<T>* fInitBlock;
    FIRBlockInstruction<T>* fComputeBlock;
    FIRBlockInstruction<T>* fComputeDSPBlock;
    
    interpreter_dsp_factory_aux(const std::string& name,
                                float version_num,
                                int inputs, int ouputs,
                                int int_heap_size, int real_heap_size,
                                int sr_offset, int count_offset,
                                FIRMetaBlockInstruction* meta,
                                FIRUserInterfaceBlockInstruction<T>* interface,
                                FIRBlockInstruction<T>* init,
                                FIRBlockInstruction<T>* compute_control,
                                FIRBlockInstruction<T>* compute_dsp)
    :fName(name),
    fVersion(version_num),
    fNumInputs(inputs),
    fNumOutputs(ouputs),
    fIntHeapSize(int_heap_size),
    fRealHeapSize(real_heap_size),
    fSROffset(sr_offset),
    fCountOffset(count_offset),
    fMetaBlock(meta),
    fUserInterfaceBlock(interface),
    fInitBlock(init),
    fComputeBlock(compute_control),
    fComputeDSPBlock(compute_dsp)
    {}
    
    virtual ~interpreter_dsp_factory_aux()
    {
        // No more DSP instances, so delete
        delete fUserInterfaceBlock;
        delete fInitBlock;
        delete fComputeBlock;
        delete fComputeDSPBlock;
    }
    
    std::string getName() { return fName; }
    
    std::string getSHAKey() { return fShaKey; }
    
    std::string getDSPCode() { return fExpandedDSP; }
    
    void write(std::ostream* out)
    {
        *out << "interpreter_dsp_factory " << ((sizeof(T) == 8) ? "double" : "float") << std::endl;
        *out << "version " << INTERP_FILE_VERSION << std::endl;
        
        *out << "name " << fName << std::endl;
        
        *out << "inputs " << fNumInputs << " outputs " << fNumOutputs << std::endl;
        *out << "int_heap_size " << fIntHeapSize << " real_heap_size " << fRealHeapSize
        << " sr_offset " << fSROffset << " count_offset " << fCountOffset << std::endl;
        
        *out << "meta_block" << std::endl;
        fMetaBlock->write(out);
        
        *out << "user_unterface_block" << std::endl;
        fUserInterfaceBlock->write(out);
        
        *out << "init_block" << std::endl;
        fInitBlock->write(out);
        
        *out << "control_block" << std::endl;
        fComputeBlock->write(out);
        
        *out << "dsp_block" << std::endl;
        fComputeDSPBlock->write(out);
    }
    
    // Factory reader
    
    static interpreter_dsp_factory_aux<T>* read(std::istream* in)
    {
        std::string dummy, value;
        
        // Read "version" line
        std::string version;
        float version_num;
        getline(*in, version);
        
        std::stringstream version_reader(version);
        version_reader >> dummy;   // Read "version" token
        version_reader >> value; version_num = strtof(value.c_str(), 0);
        
        if (INTERP_FILE_VERSION != version_num) {
            std::cerr << "Interpreter file format version '" << version_num << "' different from compiled one '" << INTERP_FILE_VERSION << "'" << std::endl;
            return 0;
        }
        
        // Read name
        std::string name, factory_name;
        getline(*in, name);
        
        std::stringstream name_reader(name);
        name_reader >> dummy;   // Read "name" token
        name_reader >> factory_name;
        
        // Read inputs/outputs
        std::string ins_outs;
        int inputs, outputs;
        getline(*in, ins_outs);
        
        std::stringstream in_out_reader(ins_outs);
        
        in_out_reader >> dummy; // Read "inputs" token
        in_out_reader >> value; inputs = strtol(value.c_str(), 0, 10);
        
        in_out_reader >> dummy; // Read "outputs" token
        in_out_reader >> value; outputs = strtol(value.c_str(), 0, 10);
        
        // Read int/real heap size and sr offset
        std::string heap_size;
        int int_heap_size, real_heap_size, sr_offset, count_offset;
        getline(*in, heap_size);
        
        std::stringstream heap_size_reader(heap_size);
        
        heap_size_reader >> dummy; // Read "int_heap_size" token
        heap_size_reader >> value; int_heap_size = strtol(value.c_str(), 0, 10);
        
        heap_size_reader >> dummy; // Read "real_heap_size" token
        heap_size_reader >> value; real_heap_size = strtol(value.c_str(), 0, 10);
        
        heap_size_reader >> dummy; // Read "sr_offet" token
        heap_size_reader >> value; sr_offset = strtol(value.c_str(), 0, 10);
        
        heap_size_reader >> dummy; // Read "count_offset" token
        heap_size_reader >> value; count_offset = strtol(value.c_str(), 0, 10);
        
        // Read meta block
        getline(*in, dummy);    // Read "mata_block" line
        FIRMetaBlockInstruction* meta_block = readMetaBlock(in);
        
        // Read user interface block
        getline(*in, dummy);    // Read "user_unterface_block" line
        FIRUserInterfaceBlockInstruction<T>* ui_block = readUIBlock(in);
        
        // Read init block
        getline(*in, dummy);    // Read "init_block" line
        FIRBlockInstruction<T>* init_block = readCodeBlock(in);
        
        // Read control block
        getline(*in, dummy);    // Read "control_block" line
        FIRBlockInstruction<T>* compute_control_block = readCodeBlock(in);
        
        // Read DSP block
        getline(*in, dummy);    // Read "dsp_block" line
        FIRBlockInstruction<T>* compute_dsp_block = readCodeBlock(in);
        
        return new interpreter_dsp_factory_aux(factory_name,
                                               version_num,
                                               inputs, outputs,
                                               int_heap_size,
                                               real_heap_size,
                                               sr_offset,
                                               count_offset,
                                               meta_block,
                                               ui_block,
                                               init_block,
                                               compute_control_block,
                                               compute_dsp_block);
    }
    
    static FIRMetaBlockInstruction* readMetaBlock(std::istream* in)
    {
        std::string dummy, value, line;
        int size;
        
        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);
        
        line_reader >> dummy; // Read "block_size" token
        line_reader >> value; size = strtol(value.c_str(), 0, 10);
        
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
        *inst >> key;    // Read "key" content
        
        *inst >> dummy;  // Read "value" token
        *inst >> val;    // Read "val" conent
        
        return new FIRMetaInstruction(unquote1(key), unquote1(val));
    }
    
    static FIRUserInterfaceBlockInstruction<T>* readUIBlock(std::istream* in)
    {
        std::string dummy, value, line;
        int size;
        
        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);
        
        line_reader >> dummy; // Read "block_size" token
        line_reader >> value; size = strtol(value.c_str(), 0, 10);
        
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
        FIRInstruction::Opcode opcode;
        int offset;
        float init, min, max, step;
        std::string dummy, value, label, key, val;
        
        *inst >> dummy;  // Read "opcode" token
        *inst >> value; opcode = FIRInstruction::Opcode(strtol(value.c_str(), 0, 10));
        *inst >> dummy;  // Read opcode string representation (that is not used)
        
        *inst >> dummy;  // Read "offset" token
        *inst >> value; offset = strtol(value.c_str(), 0, 10);
        
        *inst >> dummy;  // Read "label" token
        *inst >> label;  // Read "label" content
        
        *inst >> dummy;  // Read "key" token
        *inst >> key;    // Read "key" content
        
        *inst >> dummy;  // Read "val" token
        *inst >> val;    // Read "val" conent
        
        *inst >> dummy;  // Read "init" token
        *inst >> value; init = strtof(value.c_str(), 0);
        
        *inst >> dummy;  // Read "min" token
        *inst >> value; min = strtof(value.c_str(), 0);
        
        *inst >> dummy;  // Read "max" token
        *inst >> value; max = strtof(value.c_str(), 0);
        
        *inst >> dummy;  // Read "step" token
        *inst >> value; step = strtof(value.c_str(), 0);
        
        return new FIRUserInterfaceInstruction<T>(opcode, offset, unquote1(label), unquote1(key), unquote1(val), init, min, max, step);
    }
    
    static FIRBlockInstruction<T>* readCodeBlock(std::istream* in)
    {
        std::string dummy, value, line;
        int size;
        
        // Read "block_size" line
        getline(*in, line);
        std::stringstream line_reader(line);
        
        line_reader >> dummy; // Read "block_size" token
        line_reader >> value; size = strtol(value.c_str(), 0, 10);
        
        FIRBlockInstruction<T>* code_block = new FIRBlockInstruction<T>();
        
        for (int i = 0; i < size; i++) {
            getline(*in, line);
            std::stringstream inst_line_reader(line);
            FIRBasicInstruction<T>* inst = readCodeInstruction(&inst_line_reader, in);
            // Special case for loops
            if (inst->fOpcode == FIRInstruction::kCondBranch) {inst->fBranch1 = code_block; }
            code_block->push(inst);
        }
        
        return code_block;
    }
    
    static FIRBasicInstruction<T>* readCodeInstruction(std::istream* inst, std::istream* in)
    {
        FIRInstruction::Opcode opcode;
        int offset1, offset2, val_int;
        float val_real;
        std::string dummy, value;
        
        *inst >> dummy;  // Read "opcode" token
        *inst >> value; opcode = FIRInstruction::Opcode(strtol(value.c_str(), 0, 10));
        
        *inst >> dummy;  // Read opcode string representation (that is not used)
        
        *inst >> dummy;  // Read "int" token
        *inst >> value; val_int = strtol(value.c_str(), 0, 10);
        
        *inst >> dummy;  // Read "real" token
        *inst >> value; val_real = strtof(value.c_str(), 0);
        
        *inst >> dummy;  // Read "offset1" token
        *inst >> value; offset1 = strtol(value.c_str(), 0, 10);
        
        *inst >> dummy;  // Read "offset2" token
        *inst >> value; offset2 = strtol(value.c_str(), 0, 10);
        
        FIRBlockInstruction<T>* branch1 = 0;
        FIRBlockInstruction<T>* branch2 = 0;
        
        // Possibly read sub-blocks
        if (opcode == FIRInstruction::kIf) {
            branch1 = readCodeBlock(in);  // consume 'in'
            branch2 = readCodeBlock(in);  // consume 'in'
        } else if (opcode == FIRInstruction::kLoop) {
            branch1 = readCodeBlock(in);  // consume 'in'
        }
        
        return new FIRBasicInstruction<T>(opcode, val_int, val_real, offset1, offset2, branch1, branch2);
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
    
    dsp* createDSPInstance();
    
};

struct RealBuffers {
    
    float** fFloatInputs;
    float** fFloatOutputs;
    
    double** fDoubleInputs;
    double** fDoubleOutputs;
    
    RealBuffers(float** inputs, float** outputs)
        :fFloatInputs(inputs), fFloatOutputs(outputs)
    {}
    RealBuffers(double** inputs, double** outputs)
        :fDoubleInputs(inputs), fDoubleOutputs(outputs)
    {}

    void setInputs(float**& inputs) { inputs = fFloatInputs; }
    void setInputs(double**& inputs)  { inputs = fDoubleInputs; }
    
    void setOutputs(float**& outputs)  { outputs = fFloatOutputs; }
    void setOutputs(double**& outputs)  { outputs = fDoubleOutputs; }
};

struct interpreter_dsp_base : public dsp {
    
    virtual ~interpreter_dsp_base()
    {}
    
    // Not implemented...
    void buildUserInterface(UI* ui_interface) {}
    
    // Replaced by this one
    virtual void buildUserInterface(UIGeneric* glue) = 0;
    
    // Not implemented...
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
    virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs){}
    
    // Replaced by this one
    virtual void compute(int count, RealBuffers& buffers) = 0;
    
};

template <class T>
class interpreter_dsp_aux : public interpreter_dsp_base, public FIRInterpreter<T> {
	
    protected:
    
        interpreter_dsp_factory_aux<T>* fFactory;
   	
    public:
    
        interpreter_dsp_aux(interpreter_dsp_factory_aux<T>* factory)
        : FIRInterpreter<T>(factory->fIntHeapSize, factory->fRealHeapSize, factory->fSROffset, factory->fCountOffset)
        {
            fFactory = factory;
            
            this->fInputs = new T*[fFactory->fNumInputs];
            this->fOutputs = new T*[fFactory->fNumOutputs];
        }
    
        virtual ~interpreter_dsp_aux()
        {
            delete [] this->fInputs;
            delete [] this->fOutputs;
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
        
        static void classInit(int samplingRate)
        {}
        
        virtual void instanceInit(int samplingRate)
        {
            //std::cout << "instanceInit " << samplingRate << std::endl;
            // Store samplingRate in 'fSamplingFreq' variable at correct offset in fIntHeap
            this->fIntHeap[this->fSROffset] = samplingRate;
            
            // Execute init instructions
            this->ExecuteBlock(fFactory->fInitBlock);
        }
    
        virtual void init(int samplingRate)
        {
            classInit(samplingRate);
            this->instanceInit(samplingRate);
        }
    
        virtual void buildUserInterface(UIGeneric* glue)
        {
            //std::cout << "buildUserInterface" << std::endl;
            this->ExecuteBuildUserInterface(fFactory->fUserInterfaceBlock, glue);
        }
    
        virtual void compute(int count, RealBuffers& buffers)
        {
            //std::cout << "compute " << count << std::endl;
            
            T** inputs; buffers.setInputs(inputs);
            T** outputs; buffers.setOutputs(outputs);
            
            // Prepare in/out buffers
            for (int i = 0; i < this->fFactory->fNumInputs; i++) {
                this->fInputs[i] = inputs[i];
            }
            for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
                this->fOutputs[i] = outputs[i];
            }
            
            // Executes the 'control' block
            this->ExecuteBlock(this->fFactory->fComputeBlock);
            
            // Set count in 'count' variable at the correct offset in fIntHeap
            this->fIntHeap[this->fCountOffset] = count;
            
            // Executes the 'DSP' block
            this->ExecuteBlock(this->fFactory->fComputeDSPBlock);
            
             //std::cout << "sample " << outputs[0][0] << std::endl;
        }
};

/*
Computing using on a down-sampled version of signals
 
TODO:
 
- anti alias filter at input
 
- interpolation at output
 
*/

template <class T>
class interpreter_dsp_aux_down : public interpreter_dsp_aux<T> {
    
    private:
    
        int fDownSamplingFactor;

    public:
    
        interpreter_dsp_aux_down(interpreter_dsp_factory_aux<T>* factory, int down_sampling_factor)
            : interpreter_dsp_aux<T>(factory), fDownSamplingFactor(down_sampling_factor)
        {
            // Allocate and set downsampled inputs/outputs
            for (int i = 0; i < this->fFactory->fNumInputs; i++) {
                this->fInputs[i] = new T[2048];
            }
            for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
                this->fOutputs[i] = new T[2048];
            }
        }
        
        virtual ~interpreter_dsp_aux_down()
        {
            // Delete downsampled inputs/outputs
            for (int i = 0; i < this->fFactory->fNumInputs; i++) {
                delete [] this->fInputs[i];
            }
            for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
                delete [] this->fOutputs[i];
            }
        }
    
        static void classInit(int samplingRate)
        {}

        virtual void init(int samplingRate)
        {
            classInit(samplingRate / fDownSamplingFactor);
            this->instanceInit(samplingRate / fDownSamplingFactor);
        }
    
        virtual void compute(int count, RealBuffers& buffers)
        {
            T** inputs; buffers.setInputs(inputs);
            T** outputs; buffers.setOutputs(outputs);
            
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

struct EXPORT interpreter_dsp : public dsp {
    
    interpreter_dsp_base* fDSP;
    
    interpreter_dsp(interpreter_dsp_aux<float>* dsp):fDSP(dsp)
    {}
    interpreter_dsp(interpreter_dsp_aux<double>* dsp):fDSP(dsp)
    {}

    virtual ~interpreter_dsp()
    {
        delete fDSP;
    }

    int getNumInputs();
    int getNumOutputs();

    void init(int samplingRate);
    void instanceInit(int samplingRate);
  
    void buildUserInterface(UI* ui_interface);
    
    void compute(int count, float** input, float** output);
    void compute(int count, double** input, double** output);
    
};

template <class T>
dsp* interpreter_dsp_factory_aux<T>::createDSPInstance()
{
    return new interpreter_dsp(new interpreter_dsp_aux<T>(this));
    //return new interpreter_dsp(new interpreter_dsp_aux_down<T>(this, 2));
}

// Public C++ interface

struct EXPORT interpreter_dsp_factory : public dsp_factory {
    
    interpreter_dsp_factory_base* fFactory;
  
    interpreter_dsp_factory(const std::string& name,
                         float version_num,
                         int inputs, int ouputs,
                         int int_heap_size, int real_heap_size,
                         int sr_offset, int count_offset,
                         FIRMetaBlockInstruction* meta,
                         FIRUserInterfaceBlockInstruction<float>* interface,
                         FIRBlockInstruction<float>* init,
                         FIRBlockInstruction<float>* compute_control,
                         FIRBlockInstruction<float>* compute_dsp)
    {
        fFactory = new interpreter_dsp_factory_aux<float>(name, version_num,
                                                        inputs, ouputs,
                                                        int_heap_size, real_heap_size,
                                                        sr_offset, count_offset,
                                                        meta, interface,
                                                        init, compute_control, compute_dsp);
    }

    interpreter_dsp_factory(const std::string& name,
                            float version_num,
                            int inputs, int ouputs,
                            int int_heap_size, int real_heap_size,
                            int sr_offset, int count_offset,
                            FIRMetaBlockInstruction* meta,
                            FIRUserInterfaceBlockInstruction<double>* interface,
                            FIRBlockInstruction<double>* init,
                            FIRBlockInstruction<double>* compute_control,
                            FIRBlockInstruction<double>* compute_dsp)
    {
        fFactory = new interpreter_dsp_factory_aux<double>(name, version_num,
                                                        inputs, ouputs,
                                                        int_heap_size, real_heap_size,
                                                        sr_offset, count_offset,
                                                        meta, interface,
                                                        init, compute_control, compute_dsp);
    }
    
    interpreter_dsp_factory(interpreter_dsp_factory_aux<float>* factory):fFactory(factory)
    {}
    
    interpreter_dsp_factory(interpreter_dsp_factory_aux<double>* factory):fFactory(factory)
    {}
    
    virtual ~interpreter_dsp_factory()
    {
        delete fFactory;
    }

    std::string getName() { return fFactory->getName(); }
    
    std::string getSHAKey() { return fFactory->getSHAKey(); }
    
    std::string getDSPCode() { return fFactory->getDSPCode(); }
    
    dsp* createDSPInstance() { return fFactory->createDSPInstance(); }
    
    void metadata(Meta* meta) { fFactory->metadata(meta); }
    
    void write(std::ostream* out) { fFactory->write(out); }
    
};

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

EXPORT dsp* createInterpreterDSPInstance(interpreter_dsp_factory* factory);

EXPORT void deleteInterpreterDSPInstance(interpreter_dsp* dsp);

#endif

