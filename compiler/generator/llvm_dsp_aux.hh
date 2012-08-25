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

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
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

#ifdef LLVM_29
#include <llvm/Target/TargetSelect.h>
#endif
#if defined(LLVM_30) || defined(LLVM_31)
#include <llvm/Support/TargetSelect.h>
#endif

#include <string>
#include "../../architecture/faust//gui/UI.h"
#include "../../architecture/faust//gui/CUI.h"
#include "../../architecture/faust//audio/dsp.h"

using namespace std;
using namespace llvm;

struct llvm_dsp {};

typedef llvm_dsp* (* newDspFun) ();
typedef void (* deleteDspFun) (llvm_dsp* self);
typedef int (* getNumInputsFun) (llvm_dsp* self);
typedef int (* getNumOutputsFun) (llvm_dsp* self);
typedef void (* buildUserInterfaceFun) (llvm_dsp* self, UIGlue* ui);
typedef void (* initFun) (llvm_dsp* self, int freq);
typedef void (* classInitFun) (int freq);
typedef void (* instanceInitFun) (llvm_dsp* self, int freq);
typedef void (* computeFun) (llvm_dsp* self, int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);

class llvmdspaux : public dsp {

  private:

        ExecutionEngine* fJIT;
        Module* fModule;
        int fOptLevel;
        string fTarget;
    
        llvm_dsp* fDsp;
        newDspFun fNew;
        deleteDspFun fDelete;
        getNumInputsFun fGetNumInputs;
        getNumOutputsFun fGetNumOutputs;
        buildUserInterfaceFun fBuildUserInterface;
        initFun fInit;
        classInitFun fClassInit;
        instanceInitFun fInstanceInit;
        computeFun fCompute;
        
        static int fCount;
        
        void* LoadOptimize(const std::string& function);
        Module* LoadModule(const std::string filename);
        Module* CompileModule(int argc, char *argv[], const char* library_path, const char* input_name, const char* input, char* error_msg);
       
  public:
  
        llvmdspaux(int argc, char *argv[], const std::string& library_path, const std::string& name, const std::string& input, const std::string& target, char* error_msg, int opt_level = 3);
        llvmdspaux(int argc, char *argv[], const std::string& library_path, const std::string& name, const std::string& input, char* error_msg, int opt_level = 3);
        llvmdspaux(int argc, char *argv[], const std::string& library_path, const std::string& target, char* error_msg, int opt_level = 3);
        llvmdspaux(int argc, char *argv[], const std::string& library_path, char* error_msg, int opt_level = 3);
        
        virtual ~llvmdspaux();
        
        bool init();
    
        virtual int getNumInputs();
        virtual int getNumOutputs();
    
        void classInit(int samplingFreq);
        virtual void instanceInit(int samplingFreq);
        virtual void init(int samplingFreq);
      
        virtual void buildUserInterface(UI* interface);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
     
};

class llvmdsp : public dsp {

    private:
    
        llvmdspaux* fDSP;
        
    public:
  
        llvmdsp(int argc, char *argv[], const std::string& library_path, const std::string& name, const std::string& input, const std::string& target, char* error_msg, int opt_level = 3);
        llvmdsp(int argc, char *argv[], const std::string& library_path, const std::string& name, const std::string& input, char* error_msg, int opt_level = 3);
        llvmdsp(int argc, char *argv[], const std::string& library_path, const std::string& target, char* error_msg, int opt_level = 3);
        llvmdsp(int argc, char *argv[], const std::string& library_path, char* error_msg, int opt_level = 3);
        
        virtual ~llvmdsp();
        
        bool init();
     
        virtual int getNumInputs();
        virtual int getNumOutputs();
    
        void classInit(int samplingFreq);
        virtual void instanceInit(int samplingFreq);
        virtual void init(int samplingFreq);
      
        virtual void buildUserInterface(UI* interface);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
     
};
