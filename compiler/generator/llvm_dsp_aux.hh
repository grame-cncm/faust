/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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
 
#ifndef LLVM_DSP_AUX_H
#define LLVM_DSP_AUX_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include <iostream>
#include <fstream>
#include <sstream>

#if defined(LLVM_33) || defined(LLVM_34)
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IRReader/IRReader.h>
#else
#include <llvm/Module.h>
#include <llvm/LLVMContext.h>
#include <llvm/Support/IRReader.h>
#endif

#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/PassManager.h>
#include <llvm/Analysis/Verifier.h>

#if defined(LLVM_33) || defined(LLVM_34)
#include <llvm/IR/DataLayout.h>
#elif LLVM_32
#include <llvm/DataLayout.h>
#else
#include <llvm/Target/TargetData.h>
#endif
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/PassNameParser.h>

#include <llvm/Linker.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

#ifdef LLVM_29
#include <llvm/Target/TargetSelect.h>
#endif
#if defined(LLVM_30) || defined(LLVM_31) || defined(LLVM_32) || defined(LLVM_33) || defined(LLVM_34)
#include <llvm/Support/TargetSelect.h>
#endif

#include <string>
#include "faust/gui/UI.h"
#include "faust/gui/CUI.h"
#include "faust/gui/meta.h"
#include "faust/audio/dsp.h"
#include "libfaust.h"
#include "export.hh"

#ifdef __cplusplus
extern "C"
{
#endif

using namespace std;
using namespace llvm;

class llvm_dsp_aux;

class llvm_dsp_factory {

    friend class llvm_dsp_aux;

    private:

        ExecutionEngine* fJIT;
        LLVMResult* fResult;
        
        int fOptLevel;
        string fTarget;
    
        newDspFun fNew;
        deleteDspFun fDelete;
        getNumInputsFun fGetNumInputs;
        getNumOutputsFun fGetNumOutputs;
        buildUserInterfaceFun fBuildUserInterface;
        initFun fInit;
        computeFun fCompute;
        metadataFun fMetadata;
        
        string fLibraryPath;
        
        bool fScheduler;
        
        void* LoadOptimize(const std::string& function);
        
        LLVMResult* CompileModule(int argc, const char *argv[], 
            const char* library_path, const char* draw_path,
            const char* input_name, const char* input, char* error_msg);
            
        void Init();
        
        static int gInstance;
                   
  public:
  
        llvm_dsp_factory(int argc, const char *argv[], 
                        const std::string& library_path, const std::string& draw_path, const std::string& name, 
                        const std::string& input, const std::string& target, 
                        std::string& error_msg, int opt_level = 3);
              
        llvm_dsp_factory(Module* module, LLVMContext* context, const std::string& target, int opt_level = 0);
      
        virtual ~llvm_dsp_factory();
      
        llvm_dsp_aux* createDSPInstance();
        
        // Bitcode
        std::string writeDSPFactoryToBitcode();
        
        void writeDSPFactoryToBitcodeFile(const std::string& bit_code_path);
        
        // IR
        std::string writeDSPFactoryToIR();
        
        void writeDSPFactoryToIRFile(const std::string& ir_code_path);
        
        bool initJIT(std::string& error_msg);
        
        void metadataDSPFactory(Meta* meta);
        
        void metadataDSPFactory(MetaGlue* glue);
     
};

class llvm_dsp_aux : public dsp {

    friend class llvm_dsp_factory;
   
    private:

        llvm_dsp_factory* fDSPFactory;
        llvm_dsp_imp* fDSP;
                 
    public:
        
        llvm_dsp_aux(llvm_dsp_factory* factory, llvm_dsp_imp* dsp);
        virtual ~llvm_dsp_aux();
     
        virtual int getNumInputs();
        virtual int getNumOutputs();
    
        virtual void init(int samplingFreq);
      
        virtual void buildUserInterface(UI* interface);
        void buildUserInterface(UIGlue* glue);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
     
};

// Public C++ interface

EXPORT llvm_dsp_factory* createDSPFactory(int argc, const char *argv[], 
                        const std::string& library_path, const std::string& draw_path,  const std::string& name, 
                        const std::string& input, const std::string& target, 
                        std::string& error_msg, int opt_level = 3);
                        
EXPORT void deleteDSPFactory(llvm_dsp_factory* factory);

// Bitcode <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcode(const std::string& bit_code, const std::string& target, int opt_level = 0);

EXPORT std::string writeDSPFactoryToBitcode(llvm_dsp_factory* factory);

// Bitcode <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, int opt_level = 0);

EXPORT void writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const std::string& bit_code_path);

// IR <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromIR(const std::string& ir_code, const std::string& target, int opt_level = 0);

EXPORT std::string writeDSPFactoryToIR(llvm_dsp_factory* factory);

// IR <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromIRFile(const std::string& ir_code_path, const std::string& target, int opt_level = 0);

EXPORT void writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const std::string& ir_code_path);

EXPORT void metadataDSPFactory(llvm_dsp_factory* factory, Meta* m);

class EXPORT llvm_dsp : public dsp {
                
    public:
     
        virtual int getNumInputs();
        virtual int getNumOutputs();
    
        virtual void init(int samplingFreq);
      
        virtual void buildUserInterface(UI* interface);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
     
};

EXPORT llvm_dsp* createDSPInstance(llvm_dsp_factory* factory);

EXPORT void deleteDSPInstance(llvm_dsp* dsp);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Public C interface

EXPORT llvm_dsp_factory* createCDSPFactory(int argc, const char *argv[], 
                        const char* library_path, const char* draw_path, const char* name, 
                        const char* input, const char* target, 
                        char* error_msg, int opt_level);

EXPORT void deleteCDSPFactory(llvm_dsp_factory* factory);

EXPORT llvm_dsp_factory* readCDSPFactoryFromBitcode(const char* bit_code, const char* target, int opt_level);

EXPORT const char* writeCDSPFactoryToBitcode(llvm_dsp_factory* factory);

EXPORT llvm_dsp_factory* readCDSPFactoryFromBitcodeFile(const char* bit_code_path, const char* target, int opt_level);

EXPORT void writeCDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const char* bit_code_path);

EXPORT llvm_dsp_factory* readCDSPFactoryFromIR(const char* ir_code, const char* target, int opt_level);

EXPORT const char* writeCDSPFactoryToIR(llvm_dsp_factory* factory);

EXPORT llvm_dsp_factory* readCDSPFactoryFromIRFile(const char* ir_code_path, const char* target, int opt_level);

EXPORT void writeCDSPFactoryToIRFile(llvm_dsp_factory* factory, const char* ir_code_path);

EXPORT void metadataCDSPFactory(llvm_dsp_factory* factory, MetaGlue* meta);

EXPORT int getNumInputsCDSPInstance(llvm_dsp* dsp);

EXPORT int getNumOutputsCDSPInstance(llvm_dsp* dsp);

EXPORT void initCDSPInstance(llvm_dsp* dsp, int samplingFreq);

EXPORT void buildUserInterfaceCDSPInstance(llvm_dsp* dsp, UIGlue* interface);

EXPORT void computeCDSPInstance(llvm_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output);

EXPORT llvm_dsp* createCDSPInstance(llvm_dsp_factory* factory);

EXPORT void deleteCDSPInstance(llvm_dsp* dsp);

#ifdef __cplusplus
}
#endif

#endif
