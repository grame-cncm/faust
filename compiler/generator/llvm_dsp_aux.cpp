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

#include "llvm_dsp_aux.hh"
#include "../../architecture/faust/libfaust.h"

// For scheduler mode : this function is retrieved in the LLVM module and used in scheduler.cpp
typedef void (* computeThreadExternalFun) (llvm_dsp* dsp, int cur_thread);
computeThreadExternalFun gComputeThreadExternal = 0;

static int gLLVMInit = 0;
        
void* llvm_dsp_factory::LoadOptimize(const std::string& function)
{
    llvm::Function* fun_ptr = fModule->getFunction(function);
    void* res;
    if (fun_ptr) {
        res = fJIT->getPointerToFunction(fun_ptr);
        return res;
    } else {
        return 0;
    }
}

Module* llvm_dsp_factory::LoadModule(const std::string filename)
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

Module* llvm_dsp_factory::CompileModule(int argc, char *argv[], const char* library_path, const char* input_name, const char* input, char* error_msg)
{
    printf("Compile module...\n");
    
    int argc1 = argc + 3;
    const char* argv1[argc1];
    argv1[0] = "faust";
    argv1[1] = "-lang";
    argv1[2] = "llvm";
    for (int i = 0; i < argc; i++) {
        argv1[i+3] = argv[i];
        if (strcmp(argv[i], "-sch") == 0) {
            fScheduler = true;
        }
    }
    
    return compile_faust_llvm(argc1, (char**)argv1, library_path, input_name, input, error_msg);
}

llvm_dsp_factory::llvm_dsp_factory(int argc, char *argv[], const std::string& library_path, const std::string& name, const std::string& input, const std::string& target, char* error_msg, int opt_level)
{
    fOptLevel = opt_level;
    fTarget = target;
    Init();
    fModule = CompileModule(argc, argv, library_path.c_str(), name.c_str(), input.c_str(), error_msg);
}

llvm_dsp_factory::llvm_dsp_factory(int argc, char *argv[], const std::string& library_path, const std::string& name, const std::string& input, char* error_msg, int opt_level)
{
    llvm_dsp_factory(argc, argv, library_path, name, input, "", error_msg, opt_level);
}

llvm_dsp_factory::llvm_dsp_factory(int argc, char *argv[], const std::string& library_path, const std::string& target, char* error_msg, int opt_level)
{
    fOptLevel = opt_level;
    fTarget = target;
    Init();
    fModule = CompileModule(argc, argv, library_path.c_str(), NULL, NULL, error_msg);
}
 
llvm_dsp_factory::llvm_dsp_factory(int argc, char *argv[], const std::string& library_path, char* error_msg, int opt_level)
{
    llvm_dsp_factory(argc, argv, library_path, "", error_msg, opt_level);
}

llvm_dsp_factory::llvm_dsp_factory(const std::string& module_path, int opt_level)
{
    fOptLevel = opt_level;
    fTarget = "";
    Init();
    fModule = LoadModule(module_path);
}

void llvm_dsp_factory::Init()
{
    fJIT = 0;
    fNew = 0;
    fDelete = 0;
    fGetNumInputs = 0;
    fGetNumOutputs = 0;
    fBuildUserInterface = 0;
    fInit = 0;
    fClassInit = 0;
    fInstanceInit = 0;
    fCompute = 0;
    fScheduler = false;
}

llvm_dsp_aux* llvm_dsp_factory::createDSPInstance()
{
    assert(fModule);
    
    if (!fJIT) {
    
        if (gLLVMInit++ == 0) {
            InitializeNativeTarget();
        }
        if (fTarget != "") {
             fModule->setTargetTriple(fTarget);
        } else {
        #if defined(LLVM_31)
            fModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
        #else
            fModule->setTargetTriple(llvm::sys::getHostTriple());
        #endif
        }

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
        if (fScheduler) {
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
        }
        
        // Taken from LuaAV
        switch (fOptLevel) {
        
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
    }
    
    // Create instance 
    return new llvm_dsp_aux(this, fNew());
}

llvm_dsp_factory::~llvm_dsp_factory()
{
    if (fJIT) {
        fJIT->runStaticConstructorsDestructors(true);
        // fModule is kept and deleted by fJIT
        delete fJIT;
    }
}
        
// Instance 

llvm_dsp_aux::llvm_dsp_aux(llvm_dsp_factory* factory, llvm_dsp_imp* dsp)
    :fFactory(factory), fDSP(dsp)
{
    assert(fFactory);
    assert(fDSP);
}
        
llvm_dsp_aux::~llvm_dsp_aux()
{   
    if (fDSP) {
        fFactory->fDelete(fDSP);
    }
}

int llvm_dsp_aux::getNumInputs()
{
    return fFactory->fGetNumInputs(fDSP);
}
int llvm_dsp_aux::getNumOutputs()
{
    return fFactory->fGetNumOutputs(fDSP);
}

void llvm_dsp_aux::classInit(int samplingFreq)
{
    fFactory->fClassInit(samplingFreq);
}

void llvm_dsp_aux::instanceInit(int samplingFreq)
{
    fFactory->fInstanceInit(fDSP, samplingFreq);
}

void llvm_dsp_aux::init(int samplingFreq)
{
    fFactory->fInit(fDSP, samplingFreq);
}

void llvm_dsp_aux::buildUserInterface(UI* interface)
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
    fFactory->fBuildUserInterface(fDSP, &glue);
}

void llvm_dsp_aux::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    AVOIDDENORMALS;
    fFactory->fCompute(fDSP, count, input, output);
}

static llvm_dsp_factory* CheckDSPFactory(llvm_dsp_factory* factory)
{
    if (factory->getModule()) {
        return factory;
    } else {
        delete factory;
        return 0;
    }
}

// Public API

llvm_dsp_factory* createDSPFactory(int argc, char *argv[], 
    const std::string& library_path, const std::string& name, 
    const std::string& input, const std::string& target, 
    char* error_msg, int opt_level)
{
    return CheckDSPFactory(new llvm_dsp_factory(argc, argv, library_path, name, input, target, error_msg, opt_level));
}
    
llvm_dsp_factory* createDSPFactory(int argc, char *argv[], 
    const std::string& library_path, const std::string& name, 
    const std::string& input, char* error_msg, 
    int opt_level)
{
    return CheckDSPFactory(new llvm_dsp_factory(argc, argv, library_path, name, input, error_msg, opt_level));
 }
    
llvm_dsp_factory* createDSPFactory(int argc, char *argv[], 
    const std::string& library_path, const std::string& target, 
    char* error_msg, int opt_level)
{
    return CheckDSPFactory(new llvm_dsp_factory(argc, argv, library_path, target, error_msg, opt_level));
 }
    
llvm_dsp_factory* createDSPFactory(int argc, char *argv[], 
    const std::string& library_path, char* error_msg, 
    int opt_level)
{
    return CheckDSPFactory(new llvm_dsp_factory(argc, argv, library_path, error_msg, opt_level));
}

llvm_dsp_factory* createDSPFactory(const std::string& module_path, int opt_level)
{
    return CheckDSPFactory(new llvm_dsp_factory(module_path, opt_level));
}

llvm_dsp* createDSPInstance(llvm_dsp_factory* factory)
{
    return reinterpret_cast<llvm_dsp*>(factory->createDSPInstance());
}

void deleteDSPFactory(llvm_dsp_factory* factory) { delete factory; }

void deleteDSPInstance(llvm_dsp* dsp) 
{
    delete reinterpret_cast<llvm_dsp_aux*>(dsp); 
}

int llvm_dsp::getNumInputs()
{
    return reinterpret_cast<llvm_dsp_aux*>(this)->getNumInputs();
}

int llvm_dsp::getNumOutputs()
{
    return reinterpret_cast<llvm_dsp_aux*>(this)->getNumOutputs();
}

void llvm_dsp::classInit(int samplingFreq)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->classInit(samplingFreq);
}

void llvm_dsp::instanceInit(int samplingFreq)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->instanceInit(samplingFreq);
}

void llvm_dsp::init(int samplingFreq)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->init(samplingFreq);
}

void llvm_dsp::buildUserInterface(UI* interface)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->buildUserInterface(interface);
}

void llvm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
     reinterpret_cast<llvm_dsp_aux*>(this)->compute(count, input, output);
}
