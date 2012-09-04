/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2012 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/

#ifndef LLVM_DSP_AUX_H
#define LLVM_DSP_AUX_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

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
 
    public:
    
        JSONUI()
        {}

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
        
        Module* LoadModule(const std::string filename);
        
        Module* CompileModule(int argc, char *argv[], 
            const char* library_path, const char* draw_path,
            const char* input_name, const char* input, char* error_msg);
            
        void Init();
        
        std::string BuildJSON(llvm_dsp_imp* dsp);
                  
  public:
  
        llvm_dsp_factory(const std::string& module_path, int opt_level = 3);
  
        llvm_dsp_factory(int argc, char *argv[], 
            const std::string& library_path, const std::string& draw_path, const std::string& name, 
            const std::string& input, const std::string& target, 
            char* error_msg, int opt_level = 3);
              
        llvm_dsp_factory(Module* module, const std::string& target, int opt_level = 0);
      
        virtual ~llvm_dsp_factory();
      
        llvm_dsp_aux* createDSPInstance();
        
        
        std::string writeDSPFactoryToBitcode();
        std::string writeDSPFactoryToIR();
        
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

llvm_dsp_factory* createDSPFactory(int argc, char *argv[], 
                        const std::string& library_path, const std::string& draw_path,  const std::string& name, 
                        const std::string& input, const std::string& target, 
                        char* error_msg, int opt_level = 3);
                                    
llvm_dsp_factory* createDSPFactory(const std::string& module_path, int opt_level = 3);
                        
void deleteDSPFactory(llvm_dsp_factory* factory);

llvm_dsp_factory* readDSPFactoryFromBitcode(const std::string& bit_code, const std::string& target, int opt_level = 0);

std::string writeDSPFactoryToBitcode(llvm_dsp_factory* factory);

llvm_dsp_factory* readDSPFactoryFromIR(const std::string& ir_code, const std::string& target, int opt_level = 0);

std::string writeDSPFactoryToIR(llvm_dsp_factory* factory);

class llvm_dsp : public dsp {
                
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

llvm_dsp* createDSPInstance(llvm_dsp_factory* factory);

void deleteDSPInstance(llvm_dsp* dsp);

#endif