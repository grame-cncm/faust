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

#include <llvm/Module.h>
#include <llvm/LLVMContext.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/PassManager.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/PassNameParser.h>
#include <llvm/Support/IRReader.h>
#include <llvm/Linker.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

#ifdef LLVM_29
#include <llvm/Target/TargetSelect.h>
#endif
#if defined(LLVM_30) || defined(LLVM_31)
#include <llvm/Support/TargetSelect.h>
#endif

#include <string>
#include "../../architecture/faust/gui/UI.h"
#include "../../architecture/faust/gui/CUI.h"
#include "../../architecture/faust/audio/dsp.h"

#include "export.hh"

using namespace std;
using namespace llvm;

struct llvm_dsp_imp {};

typedef llvm_dsp_imp* (* newDspFun) ();
typedef void (* deleteDspFun) (llvm_dsp_imp* self);
typedef int (* getNumInputsFun) (llvm_dsp_imp* self);
typedef int (* getNumOutputsFun) (llvm_dsp_imp* self);
typedef void (* buildUserInterfaceFun) (llvm_dsp_imp* self, UIGlue* ui);
typedef void (* initFun) (llvm_dsp_imp* self, int freq);
typedef void (* classInitFun) (int freq);
typedef void (* instanceInitFun) (llvm_dsp_imp* self, int freq);
typedef void (* computeFun) (llvm_dsp_imp* self, int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);

class llvm_dsp_aux;

class JSONUI : public UI {

    private:
       
        std::ostream* fOut;
        int fTab;
        bool fNewGroup;
        
        void openGroup(const char* group, const char* label);
        void addGenericButton(const char* button, const char* label, FAUSTFLOAT* zone);
        void addGenericSlider(const char* slider, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
        void addGenericBargraph(const char* bargraph, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
 
    public:
    
        JSONUI(std::ostream* out):fOut(out),fTab(0),fNewGroup(false)
        {
            *fOut << "{";
        }
        
        void finish()
        {
             *fOut << "}" << endl;
        }
  
        // -- widget's layouts

        virtual void openTabBox(const char* label);
        virtual void openHorizontalBox(const char* label);
        virtual void openVerticalBox(const char* label);
        virtual void closeBox();

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone);
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone);
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val);

}; 

class llvm_dsp_factory {

    friend class llvm_dsp_aux;

    private:

        ExecutionEngine* fJIT;
        Module* fModule;
        int fOptLevel;
        string fTarget;
    
        newDspFun fNew;
        deleteDspFun fDelete;
        getNumInputsFun fGetNumInputs;
        getNumOutputsFun fGetNumOutputs;
        buildUserInterfaceFun fBuildUserInterface;
        initFun fInit;
        classInitFun fClassInit;
        instanceInitFun fInstanceInit;
        computeFun fCompute;
        
        string fLibraryPath;
        
        bool fScheduler;
        
        void* LoadOptimize(const std::string& function);
        
        Module* CompileModule(int argc, const char *argv[], 
            const char* library_path, const char* draw_path,
            const char* input_name, const char* input, char* error_msg);
            
        void Init();
        
        std::string BuildJSON(llvm_dsp_imp* dsp);
                  
  public:
  
        llvm_dsp_factory(const std::string& module_path, int opt_level = 3);
  
        llvm_dsp_factory(int argc, const char *argv[], 
            const std::string& library_path, const std::string& draw_path, const std::string& name, 
            const std::string& input, const std::string& target, 
            char* error_msg, int opt_level = 3);
              
        llvm_dsp_factory(Module* module, const std::string& target, int opt_level = 0);
      
        virtual ~llvm_dsp_factory();
      
        llvm_dsp_aux* createDSPInstance();
        
        // Bitcode
        std::string writeDSPFactoryToBitcode();
        
        void writeDSPFactoryToBitcodeFile(const std::string& bit_code_path);
        
        // IR
        std::string writeDSPFactoryToIR();
        
        void writeDSPFactoryToIRFile(const std::string& ir_code_path);
        
        bool initJIT();
    
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
    
        void classInit(int samplingFreq);
        virtual void instanceInit(int samplingFreq);
        virtual void init(int samplingFreq);
      
        virtual void buildUserInterface(UI* interface);
        virtual std::string buildJSON();
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
     
};

// Public interface

#ifdef __cplusplus
extern "C"
{
#endif

EXPORT llvm_dsp_factory* createDSPFactory(int argc, const char *argv[], 
                        const std::string& library_path, const std::string& draw_path,  const std::string& name, 
                        const std::string& input, const std::string& target, 
                        char* error_msg, int opt_level = 3);
                        
EXPORT void deleteDSPFactory(llvm_dsp_factory* factory);

// Bitcode <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcode(const std::string& bit_code, const std::string& target, int opt_level = 0);

std::string EXPORT writeDSPFactoryToBitcode(llvm_dsp_factory* factory);

// Bitcode <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, int opt_level = 0);

EXPORT void writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const std::string& bit_code_path);

// IR <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromIR(const std::string& ir_code, const std::string& target, int opt_level = 0);

EXPORT std::string writeDSPFactoryToIR(llvm_dsp_factory* factory);

// IR <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromIRFile(const std::string& ir_code_path, const std::string& target, int opt_level = 0);

EXPORT void writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const std::string& ir_code_path);

class EXPORT llvm_dsp : public dsp {
                
    public:
     
        virtual int getNumInputs();
        virtual int getNumOutputs();
    
        void classInit(int samplingFreq);
        virtual void instanceInit(int samplingFreq);
        virtual void init(int samplingFreq);
      
        virtual void buildUserInterface(UI* interface);
        virtual std::string buildJSON();
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
     
};

EXPORT llvm_dsp* createDSPInstance(llvm_dsp_factory* factory);

EXPORT void deleteDSPInstance(llvm_dsp* dsp);

#ifdef __cplusplus
}
#endif

#endif