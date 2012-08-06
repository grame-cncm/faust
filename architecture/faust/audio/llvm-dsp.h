/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"
#include "faust/gui/CUI.h"
#include "faust/libfaust.h"
#include "faust/audio/dsp.h"

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

// For scheduler mode : this function is retrieved in the LLVM module and used in scheduler.cpp
typedef void (* computeThreadExternalFun) (llvm_dsp* dsp, int cur_thread);
computeThreadExternalFun gComputeThreadExternal = 0;

class llvmdsp : public dsp {

  private:

        ExecutionEngine* fJIT;
        Module* fModule;
    
        llvm_dsp* fDsp;
        newDspFun fNew;
        deleteDspFun fDelete;
        getNumInputsFun fGetNumInputs;
        getNumOutputsFun fGetNumOutputs;
        buildUserInterfaceFun fBuildUserInterface;
        initFun fInit;
        static classInitFun fClassInit;
        instanceInitFun fInstanceInit;
        computeFun fCompute;
        
        static int fCount;
        
        void* LoadOptimize(const std::string& function)
        {
            Function* fun_ptr = fModule->getFunction(function);
            void* res;
            if (fun_ptr) {
                res = fJIT->getPointerToFunction(fun_ptr);
                return res;
            } else {
                return 0;
            }
        }
        
        Module* LoadModule(const std::string filename)
        {
            printf("Load module : %s \n", filename.c_str());
            LLVMContext &context = getGlobalContext();
            SMDiagnostic err;
            Module* res = ParseIRFile(filename, err, context);
            if (!res) {
            #if defined(LLVM_31) 
                err.print("LoadModule", errs());
            #endif
            #if defined(LLVM_30) 
                err.Print("LoadModule", errs());
            #endif
            }
            return res;
        }
        
        Module* CompileModule(int argc, char *argv[], const char* library_path, const char* input_name, const char* input, char* error_msg)
        {
            printf("Compile module...\n");
            
            int argc1 = argc + 3;
            const char* argv1[argc1];
            argv1[0] = "faust";
            argv1[1] = "-lang";
            argv1[2] = "llvm";
            for (int i = 0; i < argc; i++) {
                argv1[i+3] = argv[i];
            }
            
            return compile_faust_llvm(argc1, (char**)argv1, library_path, input_name, input, error_msg);
        }

  public:
  
        llvmdsp(int argc, char *argv[], const std::string& library_path, const std::string& input_name, const std::string& input, char* error_msg, int opt_level = 3)
        {
            fModule = CompileModule(argc, argv, library_path.c_str(), input_name.c_str(), input.c_str(), error_msg);
            Init(opt_level);
        }
  
        llvmdsp(int argc, char *argv[], const std::string& library_path, char* error_msg, int opt_level = 3)
        {
            if (strstr(argv[1], ".bc")) {
                fModule = LoadModule(argv[1]);
            } else {
                fModule = CompileModule(argc - 1, &argv[1], library_path.c_str(), NULL, NULL, error_msg);
            }
            
            Init(opt_level);
        }

        void Init(int opt_level)
        {
            if (!fModule) throw new std::bad_alloc;
            
            if (fCount++ == 0) {
                InitializeNativeTarget();
            }
        #if defined(LLVM_31)
            fModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
        #else
            fModule->setTargetTriple(llvm::sys::getHostTriple());
        #endif

            std::string err;
            EngineBuilder builder(fModule);
            
            builder.setOptLevel(CodeGenOpt::Aggressive);
            builder.setEngineKind(EngineKind::JIT);
            builder.setUseMCJIT(true);
            fJIT = builder.create();
            assert(fJIT);
            
            // Run static constructors.
            fJIT->runStaticConstructorsDestructors(false);
            
            fJIT->DisableLazyCompilation(true);
            fModule->setDataLayout(fJIT->getTargetData()->getStringRepresentation());
            //fModule->dump();
       
            // Set up the optimizer pipeline. Start with registering info about how the
            // target lays out data structures.
            PassManager pm;
            pm.add(new TargetData(*fJIT->getTargetData()));
            
            // Link with "scheduler" code
            Module* scheduler = LoadModule("scheduler.ll");
            if (scheduler) {
                //scheduler->dump();
                if (Linker::LinkModules(fModule, scheduler, Linker::DestroySource, &err)) {
                    printf("Cannot link scheduler module...\n");
                }
                delete scheduler;
            } else {
                printf("File scheduler.ll not found...\n");
            }
            
            // Taken from LuaAV
            switch (opt_level) {
            
                case 1:
                    pm.add(llvm::createPromoteMemoryToRegisterPass());
                    pm.add(llvm::createInstructionCombiningPass());
                    pm.add(llvm::createCFGSimplificationPass());
                    pm.add(llvm::createVerifierPass(llvm::PrintMessageAction));
                    break;
                    
                case 2:
                    pm.add(llvm::createCFGSimplificationPass());
                    pm.add(llvm::createJumpThreadingPass());
                    pm.add(llvm::createPromoteMemoryToRegisterPass());
                    pm.add(llvm::createInstructionCombiningPass());
                    pm.add(llvm::createCFGSimplificationPass());
                    pm.add(llvm::createScalarReplAggregatesPass());
                    pm.add(llvm::createLICMPass());
                    pm.add(llvm::createGVNPass());
                    pm.add(llvm::createSCCPPass());
                    pm.add(llvm::createAggressiveDCEPass());
                    pm.add(llvm::createCFGSimplificationPass());
                    pm.add(llvm::createVerifierPass(llvm::PrintMessageAction));
                    break;
                    
                case 3:
                    pm.add(llvm::createScalarReplAggregatesPass());
                    pm.add(llvm::createInstructionCombiningPass());
                    pm.add(llvm::createCFGSimplificationPass());        // Clean up disgusting code
                    pm.add(llvm::createPromoteMemoryToRegisterPass());  // Kill useless allocas
                    pm.add(llvm::createGlobalOptimizerPass());          // OptLevel out global vars
                    pm.add(llvm::createGlobalDCEPass());                // Remove unused fns and globs
                    pm.add(llvm::createIPConstantPropagationPass());    // IP Constant Propagation
                    pm.add(llvm::createDeadArgEliminationPass());       // Dead argument elimination
                    pm.add(llvm::createInstructionCombiningPass());     // Clean up after IPCP & DAE
                    pm.add(llvm::createCFGSimplificationPass());        // Clean up after IPCP & DAE
                    pm.add(llvm::createPruneEHPass());                  // Remove dead EH info
                    pm.add(llvm::createFunctionAttrsPass());            // Deduce function attrs
                    pm.add(llvm::createFunctionInliningPass());         // Inline small functions
                    pm.add(llvm::createArgumentPromotionPass());        // Scalarize uninlined fn args
                    pm.add(llvm::createSimplifyLibCallsPass());         // Library Call Optimizations
                    pm.add(llvm::createInstructionCombiningPass());     // Cleanup for scalarrepl.
                    pm.add(llvm::createJumpThreadingPass());            // Thread jumps.
                    pm.add(llvm::createCFGSimplificationPass());        // Merge & remove BBs
                    pm.add(llvm::createScalarReplAggregatesPass());     // Break up aggregate allocas
                    pm.add(llvm::createInstructionCombiningPass());     // Combine silly seq's
                    pm.add(llvm::createTailCallEliminationPass());      // Eliminate tail calls
                    pm.add(llvm::createCFGSimplificationPass());        // Merge & remove BBs
                    pm.add(llvm::createReassociatePass());              // Reassociate expressions
                    pm.add(llvm::createLoopRotatePass());               // Rotate Loop
                    pm.add(llvm::createLICMPass());                     // Hoist loop invariants
                    pm.add(llvm::createLoopUnswitchPass());
                    pm.add(llvm::createInstructionCombiningPass());
                    pm.add(llvm::createIndVarSimplifyPass());           // Canonicalize indvars
                    pm.add(llvm::createLoopDeletionPass());             // Delete dead loops
                    pm.add(llvm::createLoopUnrollPass());               // Unroll small loops
                    pm.add(llvm::createInstructionCombiningPass());     // Clean up after the unroller
                    pm.add(llvm::createGVNPass());                      // Remove redundancies
                    pm.add(llvm::createMemCpyOptPass());                // Remove memcpy / form memset
                    pm.add(llvm::createSCCPPass());                     // Constant prop with SCCP
                    pm.add(llvm::createInstructionCombiningPass());
                    pm.add(llvm::createDeadStoreEliminationPass());     // Delete dead stores
                    pm.add(llvm::createAggressiveDCEPass());            // Delete dead instructions
                    pm.add(llvm::createCFGSimplificationPass());        // Merge & remove BBs
                    pm.add(llvm::createStripDeadPrototypesPass());      // Get rid of dead prototypes
                    pm.add(llvm::createConstantMergePass());            // Merge dup global constants
                    pm.add(llvm::createVerifierPass(llvm::PrintMessageAction));
                    break;
            }
      
            pm.run(*fModule);
            //fModule->dump();

            fNew = (newDspFun)LoadOptimize("new_mydsp");
            fDelete = (deleteDspFun)LoadOptimize("delete_mydsp");
            fGetNumInputs = (getNumInputsFun)LoadOptimize("getNumInputs_mydsp");
            fGetNumOutputs = (getNumOutputsFun)LoadOptimize("getNumOutputs_mydsp");
            fBuildUserInterface = (buildUserInterfaceFun)LoadOptimize("buildUserInterface_mydsp");
            fInit = (initFun)LoadOptimize("init_mydsp");
            fClassInit = (classInitFun)LoadOptimize("classInit_mydsp");
            fInstanceInit = (instanceInitFun)LoadOptimize("instanceInit_mydsp");
            fCompute = (computeFun)LoadOptimize("compute_mydsp");
            gComputeThreadExternal = (computeThreadExternalFun)LoadOptimize("computeThreadExternal");
            fDsp = fNew();
        }

        virtual ~llvmdsp()
        {
            fJIT->runStaticConstructorsDestructors(true);
            fDelete(fDsp);
            // fModule is kept and deleted by fJIT
            delete fJIT;
        }
     
        virtual int getNumInputs()
        {
            return fGetNumInputs(fDsp);
        }
        virtual int getNumOutputs()
        {
            return fGetNumOutputs(fDsp);
        }

        static void classInit(int samplingFreq)
        {
            fClassInit(samplingFreq);
        }

        virtual void instanceInit(int samplingFreq)
        {
            fInstanceInit(fDsp, samplingFreq);
        }

        virtual void init(int samplingFreq)
        {
            fInit(fDsp, samplingFreq);
        }

        virtual void buildUserInterface(UI* interface)
        {
            UIGlue glue;
            glue.uiInterface = interface;
            glue.openTabBox = openTabBoxGlue;
            glue.openHorizontalBox = openHorizontalBoxGlue;
            glue.openVerticalBox = openVerticalBoxGlue;
            glue.closeBox = closeBoxGlue;
            glue.addButton = addButtonGlue;
            glue.addCheckButton = addCheckButtonGlue;
            glue.addVerticalSlider = addVerticalSliderGlue;
            glue.addHorizontalSlider = addHorizontalSliderGlue;
            glue.addNumEntry = addNumEntryGlue;
            glue.addHorizontalBargraph = addHorizontalBargraphGlue;
            glue.addVerticalBargraph = addVerticalBargraphGlue;
            glue.declare = declareGlue;
            fBuildUserInterface(fDsp, &glue);
        }

        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
        {
            AVOIDDENORMALS;
            fCompute(fDsp, count, input, output);
        }
};

int llvmdsp::fCount = 0;
