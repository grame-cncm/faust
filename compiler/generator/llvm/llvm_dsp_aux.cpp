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

#include "compatibility.hh"

#if LLVM_BUILD

#include <stdio.h>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#ifndef _WIN32
#include <libgen.h>
#endif

#include "llvm_dsp_aux.hh"
#include "faust/gui/UIGlue.h"
#include "libfaust.h"
#include "dsp_aux.hh"
#include "timing.hh"
#include "exception.hh"

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36)
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Bitcode/ReaderWriter.h>
#ifdef LLVM_35
#include <system_error>
#else
#include <llvm/Support/system_error.h>
#endif
#include <llvm/ADT/Triple.h>
#include <llvm/Target/TargetLibraryInfo.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm-c/Core.h>
#else
#include <llvm/Module.h>
#include <llvm/LLVMContext.h>
#include <llvm/Support/IRReader.h>
#endif

/* The file llvm/Target/TargetData.h was renamed to llvm/DataLayout.h in LLVM
 * 3.2, which itself appears to have been moved to llvm/IR/DataLayout.h in LLVM
 * 3.3.
 */
#if defined(LLVM_32)
#include <llvm/DataLayout.h>
#elif !defined(LLVM_33) && !defined(LLVM_34) && !defined(LLVM_35)
#ifndef _WIN32
#include <llvm/Target/TargetData.h>
#endif
#endif

#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/PassManager.h>
#ifdef LLVM_35
#include <llvm/IR/Verifier.h>
#else
#include <llvm/Analysis/Verifier.h>
#endif
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
#ifdef LLVM_35
#include <llvm/IR/LegacyPassNameParser.h>
#include <llvm/Linker/Linker.h>
#else
#include <llvm/Support/PassNameParser.h>
#include <llvm/Linker.h>
#endif
#include <llvm/Support/Host.h>
#include <llvm/Support/ManagedStatic.h>
#ifdef LLVM_35
#include <llvm/IR/IRPrintingPasses.h>
#define llvmcreatePrintModulePass(out) createPrintModulePass(out)
#else
#include <llvm/Assembly/PrintModulePass.h>
#define llvmcreatePrintModulePass(out) createPrintModulePass(&out)
#endif
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/Support/Threading.h>

#if defined(LLVM_34) || defined(LLVM_35)
#include "llvm/ExecutionEngine/ObjectCache.h"
#endif

#if defined(LLVM_35)
#define OwningPtr std::unique_ptr
#endif

#if defined(LLVM_31) || defined(LLVM_32) || defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35)
#include <llvm/Support/TargetSelect.h>
#endif

#if defined(LLVM_35)
#include <llvm/Support/FileSystem.h>
#define sysfs_binary_flag sys::fs::F_None
#elif defined(LLVM_34)
#define sysfs_binary_flag sys::fs::F_Binary
#else
#define sysfs_binary_flag raw_fd_ostream::F_Binary
#endif

#define MAX_OPT_LEVEL 4

using namespace llvm;

int llvm_dsp_factory::gInstance = 0;
FactoryTableType llvm_dsp_factory::gFactoryTable;

static string getParam(int argc, const char* argv[], const string& param, const string& def)
{
    for (int i = 0; i < argc; i++) {
        if (string(argv[i]) == param) return argv[i+1];
    }
    return def;
}

#if defined(LLVM_34) || defined(LLVM_35)

class FaustObjectCache : public ObjectCache {

    private:
    
        string fMachineCode;
        
    public:
    
        FaustObjectCache(const string& machine_code = "") : fMachineCode(machine_code)
        {}
        
        virtual ~FaustObjectCache() 
        {}
        
        void notifyObjectCompiled(const Module *M, const MemoryBuffer *Obj) 
        {
            fMachineCode = Obj->getBuffer().str();
        }
        
        MemoryBuffer* getObject(const Module* M)
        {
            return (fMachineCode == "") ? NULL : MemoryBuffer::getMemBuffer(StringRef(fMachineCode));
        }
        
        string getMachineCode() { return fMachineCode; }
        
};

#endif

void* llvm_dsp_factory::LoadOptimize(const string& function)
{
#if defined(LLVM_34) || defined(LLVM_35)
    return (void*)fJIT->getFunctionAddress(function);
#else
    llvm::Function* fun_ptr = fResult->fModule->getFunction(function);
    if (fun_ptr) {
        return fJIT->getPointerToFunction(fun_ptr);
    } else {
        stringstream error;
        error << "LoadOptimize : getPointerToFunction failed for " << function;
        throw faustexception(error.str());
    }
#endif
}

EXPORT Module* load_single_module(const string filename, LLVMContext* context)
{
    SMDiagnostic err;
    Module* module = ParseIRFile(filename, err, *context);
    
    if (module) {
        return module;
    } else {
    #if defined(LLVM_31) || defined(LLVM_32) || defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35)
        err.print("ParseIRFile failed :", errs());
    #else
        err.Print("ParseIRFile failed :", errs());
    #endif
        return 0;
    }
}

EXPORT bool link_modules(Module* dst, Module* src, char* error_msg)
{
    string err;
    
    if (Linker::LinkModules(dst, src, Linker::DestroySource, &err)) {
        delete src;
        snprintf(error_msg, 256, "cannot link module : %s", err.c_str());
        return false;
    } else {
        delete src;
        return true;
    }
}

LLVMResult* llvm_dsp_factory::CompileModule(int argc, const char* argv[], const char* input_name, const char* input, char* error_msg)
{
    int argc1 = argc + 4;
 	const char* argv1[32];
    
    argv1[0] = "faust";
	argv1[1] = "-lang";
    argv1[2] = "llvm";
    argv1[3] = "-flist";
    for (int i = 0; i < argc; i++) {
        argv1[i+4] = argv[i];
    }
    
    return compile_faust_llvm(argc1, argv1, input_name, input, error_msg);
}

// Bitcode
string llvm_dsp_factory::writeDSPFactoryToBitcode()
{
    string res;
    raw_string_ostream out(res);
    WriteBitcodeToFile(fResult->fModule, out);
    out.flush();
    return res;
}

void llvm_dsp_factory::writeDSPFactoryToBitcodeFile(const string& bit_code_path)
{
    string err;
    raw_fd_ostream out(bit_code_path.c_str(), err, sysfs_binary_flag);
    WriteBitcodeToFile(fResult->fModule, out);
}

// IR
string llvm_dsp_factory::writeDSPFactoryToIR()
{
    string res;
    raw_string_ostream out(res);
    PassManager PM;
    PM.add(llvmcreatePrintModulePass(out));
    PM.run(*fResult->fModule);
    out.flush();
    return res;
}

void llvm_dsp_factory::writeDSPFactoryToIRFile(const string& ir_code_path)
{
    string err;
    raw_fd_ostream out(ir_code_path.c_str(), err, sysfs_binary_flag);
    PassManager PM;
    PM.add(llvmcreatePrintModulePass(out));
    PM.run(*fResult->fModule);
    out.flush();
}

std::string llvm_dsp_factory::writeDSPFactoryToMachine()
{ 
#if defined(LLVM_34) || defined(LLVM_35)
    return fObjectCache->getMachineCode(); 
#else
    return "";
#endif
}

void llvm_dsp_factory::writeDSPFactoryToMachineFile(const std::string& machine_code_path)
{
#if defined(LLVM_34) || defined(LLVM_35)
    string err;
    raw_fd_ostream out(machine_code_path.c_str(), err, sysfs_binary_flag);
    out << fObjectCache->getMachineCode(); 
    out.flush();
#endif
}

#if defined(LLVM_34) || defined(LLVM_35)
llvm_dsp_factory::llvm_dsp_factory(const string& sha_key, const string& machine_code)
{
    Init();
    fSHAKey = sha_key;
   
    // Restoring the cache
    fObjectCache = new FaustObjectCache(machine_code);
    
    // Creates module and context
    fResult = static_cast<LLVMResult*>(calloc(1, sizeof(LLVMResult)));
    fResult->fContext = new LLVMContext();
    fResult->fModule = new Module(LVVM_BACKEND_NAME, *fResult->fContext);
}
#endif

llvm_dsp_factory::llvm_dsp_factory(const string& sha_key, Module* module, LLVMContext* context, const string& target, int opt_level)
{
    Init();
    fSHAKey = sha_key;
    fOptLevel = opt_level;
    fTarget = target;
 
    fResult = static_cast<LLVMResult*>(calloc(1, sizeof(LLVMResult)));
    fResult->fModule = module;
    fResult->fContext = context;
    
#if defined(LLVM_34) || defined(LLVM_35)
    fObjectCache = NULL;
#endif
}

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35)
void llvm_dsp_factory::LLVMFatalErrorHandler(const char* reason)
{
    throw faustexception(reason);
}
#endif

llvm_dsp_factory::llvm_dsp_factory(const string& sha_key, int argc, const char* argv[], 
                                    const string& name_app,
                                    const string& dsp_content, 
                                    const string& target, 
                                    string& error_msg, int opt_level)
{
    Init();
    
    if (llvm_dsp_factory::gInstance++ == 0) {
        
        // Install a LLVM error handler
    #if defined(LLVM_34) || defined(LLVM_35)
        LLVMInstallFatalErrorHandler(llvm_dsp_factory::LLVMFatalErrorHandler);
    #endif
    #ifndef LLVM_35 // In LLVM 3.5 this is gone.
        if (!llvm_start_multithreaded()) {
            printf("llvm_start_multithreaded error...\n");
        }
    #endif
    }
    
    if (opt_level >=0 && opt_level <= MAX_OPT_LEVEL) {
        // Keep given name
        fExtName = name_app;
        
        fSHAKey = sha_key;
        fOptLevel = opt_level;
        fTarget = target;
        
    #if defined(LLVM_34) || defined(LLVM_35)
        fObjectCache = NULL;
    #endif
        
        char error_msg_aux[512];
        fClassName = getParam(argc, argv, "-cn", "mydsp");
        fResult = CompileModule(argc, argv, name_app.c_str(), dsp_content.c_str(), error_msg_aux);
        error_msg = error_msg_aux;
    } else {
        fResult = NULL;
        error_msg = "Incorrect LLVM optimisation level";
    }
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
    fCompute = 0;
    fClassName = "mydsp";
    fExtName = "ModuleDSP";
}

llvm_dsp_aux* llvm_dsp_factory::createDSPInstance()
{
    assert(fResult->fModule);
    assert(fJIT);
    return new llvm_dsp_aux(this, fNew());
}

int llvm_dsp_factory::getOptlevel()
{
    NamedMDNode* meta_data = fResult->fModule->getOrInsertNamedMetadata("OptLevel");
    if (meta_data->getNumOperands() > 0) {
        MDNode* node = meta_data->getOperand(0);
        return (node) ? atoi(static_cast<MDString*>(node->getOperand(0))->getString().data()) : -1;
    } else {
        char opt_level[32];
        sprintf(opt_level, "%d", fOptLevel);
        Value* values[] = { MDString::get(fResult->fModule->getContext(), opt_level) };
        meta_data->addOperand(MDNode::get(fResult->fModule->getContext(), values));
        return -1;
    }
}

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35)
/// AddOptimizationPasses - This routine adds optimization passes
/// based on selected optimization level, OptLevel. This routine
/// duplicates llvm-gcc behaviour.
///
/// OptLevel - Optimization Level
static void AddOptimizationPasses(PassManagerBase &MPM,FunctionPassManager &FPM,
                                    unsigned OptLevel, unsigned SizeLevel) 
{
    FPM.add(createVerifierPass());                  // Verify that input is correct

    PassManagerBuilder Builder;
    Builder.OptLevel = OptLevel;
    Builder.SizeLevel = SizeLevel;

    if (OptLevel > 1) {
        unsigned Threshold = 225;
        if (SizeLevel == 1) {           // -Os
            Threshold = 75;
        } else if (SizeLevel == 2) {    // -Oz
            Threshold = 25;
        }
        if (OptLevel > 2) {
            Threshold = 275;
        }
        Builder.Inliner = createFunctionInliningPass(Threshold);
    } else {
        Builder.Inliner = createAlwaysInlinerPass();
    }
      
    Builder.DisableUnrollLoops = (OptLevel == 0);
#if defined(LLVM_33)   
    Builder.DisableSimplifyLibCalls = false;
#endif
      
    if (OptLevel > 3) {
        Builder.LoopVectorize = true;
        Builder.SLPVectorize = true;
    }
    if (OptLevel > 4) {
        Builder.BBVectorize = true;
    }
     
    Builder.populateFunctionPassManager(FPM);
    Builder.populateModulePassManager(MPM);
}

bool llvm_dsp_factory::initJIT(string& error_msg)
{
    startTiming("initJIT");
    
    // For multiple target support
    InitializeAllTargets();
    InitializeAllTargetMCs();
      
    // For host target support
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    
    // For ObjectCache to work...
#if defined(LLVM_34) || defined(LLVM_35)
    LLVMLinkInMCJIT();
#endif
    
    // Restoring from machine code
#if defined(LLVM_34) || defined(LLVM_35)
    if (fObjectCache) {
    
        // JIT
        EngineBuilder builder(fResult->fModule);
        builder.setEngineKind(EngineKind::JIT);
        builder.setUseMCJIT(true);
        TargetMachine* tm = builder.selectTarget();
        fJIT = builder.create(tm);
        fJIT->setObjectCache(fObjectCache);
        fJIT->finalizeObject();
          
    } else {
#endif
        // First check is Faust compilation succeeded... (valid LLVM module)
        if (!fResult || !fResult->fModule) {
            return false;
        }
    
        // Initialize passes
        PassRegistry &Registry = *PassRegistry::getPassRegistry();
        
        initializeCodeGen(Registry);
        initializeCore(Registry);
        initializeScalarOpts(Registry);
        initializeObjCARCOpts(Registry);
        initializeVectorization(Registry);
        initializeIPO(Registry);
        initializeAnalysis(Registry);
        initializeIPA(Registry);
        initializeTransformUtils(Registry);
        initializeInstCombine(Registry);
        initializeInstrumentation(Registry);
        initializeTarget(Registry);

    #ifdef _WIN32
        // Windows needs this special suffix to the target triple,
        // otherwise the backend would try to generate native COFF
        // code which the JIT can't use
        // (cf. http://lists.cs.uiuc.edu/pipermail/llvmdev/2013-December/068407.html).
        string target_suffix = "-elf";
    #else
        string target_suffix = "";
    #endif
        if (fTarget != "") {
            fResult->fModule->setTargetTriple(fTarget+target_suffix);
        } else {
            fResult->fModule->setTargetTriple(llvm::sys::getDefaultTargetTriple()+target_suffix);
        }
     
        EngineBuilder builder(fResult->fModule);
        builder.setOptLevel(CodeGenOpt::Aggressive);
        builder.setEngineKind(EngineKind::JIT);
        
        // MCJIT does not work correctly (incorrect float numbers ?) when used with dynamic libLLVM
    #if defined(LLVM_34) || defined(LLVM_35)
        builder.setUseMCJIT(true);
    #else
        builder.setUseMCJIT(false);
    #endif
    
        builder.setCodeModel(CodeModel::JITDefault);
        builder.setMCPU(llvm::sys::getHostCPUName());
        
        TargetOptions targetOptions;
        targetOptions.NoFramePointerElim = true;
        targetOptions.LessPreciseFPMADOption = true;
        targetOptions.UnsafeFPMath = true;
        targetOptions.NoInfsFPMath = true;
        targetOptions.NoNaNsFPMath = true;
        targetOptions.GuaranteedTailCallOpt = true;
         
        string debug_var = (getenv("FAUST_DEBUG")) ? string(getenv("FAUST_DEBUG")) : "";
        
        if ((debug_var != "") && (debug_var.find("FAUST_LLVM3") != string::npos)) {
           targetOptions.PrintMachineCode = true;
        }
        
        builder.setTargetOptions(targetOptions);
        TargetMachine* tm = builder.selectTarget();
        
        fJIT = builder.create(tm);
        if (!fJIT) {
            endTiming("initJIT");
            return false;
        }
        
        int optlevel = getOptlevel();
        
        if ((optlevel == -1) || (fOptLevel > optlevel)) {
            PassManager pm;
            FunctionPassManager fpm(fResult->fModule);
          
            // Add an appropriate TargetLibraryInfo pass for the module's triple.
            TargetLibraryInfo* tli = new TargetLibraryInfo(Triple(fResult->fModule->getTargetTriple()));
            pm.add(tli);
            
        #ifdef LLVM_35
            // LLVM 3.5 doesn't need a separate pass for the data
            // layout, but it does require that we initialize the
            // data layout of the module. -ag
            fResult->fModule->setDataLayout(fJIT->getDataLayout());
        #else
            const string &ModuleDataLayout = fResult->fModule->getDataLayout();
            DataLayout* td = new DataLayout(ModuleDataLayout);
            pm.add(td);
        #endif
          
            // Add internal analysis passes from the target machine (mandatory for vectorization to work)
            tm->addAnalysisPasses(pm);
            
            if (fOptLevel > 0) {
                AddOptimizationPasses(pm, fpm, fOptLevel, 0);
            }
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM1") != string::npos)) {
                fResult->fModule->dump();
            }
           
            fpm.doInitialization();
            for (Module::iterator F = fResult->fModule->begin(), E = fResult->fModule->end(); F != E; ++F) {
                fpm.run(*F);
            }
            fpm.doFinalization();
            
            pm.add(createVerifierPass());
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM4") != string::npos)) {
                tm->addPassesToEmitFile(pm, fouts(), TargetMachine::CGFT_AssemblyFile, true);
            }
            
            // Now that we have all of the passes ready, run them.
            pm.run(*fResult->fModule);
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM2") != string::npos)) {
                fResult->fModule->dump();
            }
        }
        
    #if defined(LLVM_34) || defined(LLVM_35)
        fObjectCache = new FaustObjectCache();
        fJIT->setObjectCache(fObjectCache);
    }
    #endif
    
    // Run static constructors.
    fJIT->runStaticConstructorsDestructors(false);
    fJIT->DisableLazyCompilation(true);
    
    try {
        fNew = (newDspFun)LoadOptimize("new_" + fClassName);
        fDelete = (deleteDspFun)LoadOptimize("delete_" + fClassName);
        fGetNumInputs = (getNumInputsFun)LoadOptimize("getNumInputs_" + fClassName);
        fGetNumOutputs = (getNumOutputsFun)LoadOptimize("getNumOutputs_" + fClassName);
        fBuildUserInterface = (buildUserInterfaceFun)LoadOptimize("buildUserInterface_" + fClassName);
        fInit = (initFun)LoadOptimize("init_" + fClassName);
        fCompute = (computeFun)LoadOptimize("compute_" + fClassName);
        fMetadata = (metadataFun)LoadOptimize("metadata_" + fClassName);
        endTiming("initJIT");
        return true;
     } catch (faustexception& e) { // Module does not contain the Faust entry points, or external symbol was not found...
        endTiming("initJIT");
        error_msg = e.Message();
        return false;
    }
}

#else

bool llvm_dsp_factory::initJIT(string& error_msg)
{
    startTiming("initJIT");
    
    // First check is Faust compilation succeeded... (valid LLVM module)
    if (!fResult || !fResult->fModule) {
        return false;
    }
    
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    
    if (fTarget != "") {
         fResult->fModule->setTargetTriple(fTarget);
    } else {
    #if defined(LLVM_31) || defined(LLVM_32) 
        fResult->fModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
    #else
        fResult->fModule->setTargetTriple(llvm::sys::getHostTriple());
    #endif
    }

    EngineBuilder builder(fResult->fModule);
    builder.setOptLevel(CodeGenOpt::Aggressive);
    builder.setEngineKind(EngineKind::JIT);
    builder.setUseMCJIT(false);
    builder.setMCPU(llvm::sys::getHostCPUName());
       
    TargetMachine* tm = builder.selectTarget();
    fJIT = builder.create(tm);
    
    if (!fJIT) {
        endTiming("initJIT");
        return false;
    }
    
    // Run static constructors.
    fJIT->runStaticConstructorsDestructors(false);
    fJIT->DisableLazyCompilation(true);
    
#if defined(LLVM_32) 
    fResult->fModule->setDataLayout(fJIT->getDataLayout()->getStringRepresentation());
#else
    fResult->fModule->setDataLayout(fJIT->getTargetData()->getStringRepresentation());
#endif

    int optlevel = getOptlevel();
    
    if ((optlevel == -1) || (fOptLevel > optlevel)) {
        // Set up the optimizer pipeline. Start with registering info about how the
        // target lays out data structures.
        PassManager pm;
        FunctionPassManager fpm(fResult->fModule);
    #if defined(LLVM_32)    
        // TODO
    #else
        pm.add(new TargetData(*fJIT->getTargetData()));
        fpm.add(new TargetData(*fJIT->getTargetData()));
    #endif

        // Taken from LLVM Opt.cpp
        PassManagerBuilder Builder;
        Builder.OptLevel = fOptLevel;

        if (fOptLevel > 1) {
            unsigned threshold = 225;
            if (fOptLevel > 2) {
                threshold = 275;
            }
            Builder.Inliner = createFunctionInliningPass(threshold);
        } else {
            Builder.Inliner = createAlwaysInlinerPass();
        }
        
        // We use '4' to activate the auto-vectorizer
        if (fOptLevel > 3) {
        
        #if defined(LLVM_32) 
            Builder.LoopVectorize = true;
            //Builder.Vectorize = true;
        #elif defined(LLVM_31)
            Builder.Vectorize = true;
        #endif
        }
          
        Builder.DisableUnrollLoops = (fOptLevel == 0);
        Builder.populateFunctionPassManager(fpm);
        Builder.populateModulePassManager(pm);
        
        string debug_var = (getenv("FAUST_DEBUG")) ? string(getenv("FAUST_DEBUG")) : "";
        
        if ((debug_var != "") && (debug_var.find("FAUST_LLVM1") != string::npos)) {
            fResult->fModule->dump();
        }
        
        // Now that we have all of the passes ready, run them.
        pm.run(*fResult->fModule);
        
        if ((debug_var != "") && (debug_var.find("FAUST_LLVM2") != string::npos)) {
            fResult->fModule->dump();
        }
    }
     
    try {
        fNew = (newDspFun)LoadOptimize("new_" + fClassName);
        fDelete = (deleteDspFun)LoadOptimize("delete_" + fClassName);
        fGetNumInputs = (getNumInputsFun)LoadOptimize("getNumInputs_" + fClassName);
        fGetNumOutputs = (getNumOutputsFun)LoadOptimize("getNumOutputs_" + fClassName);
        fBuildUserInterface = (buildUserInterfaceFun)LoadOptimize("buildUserInterface_" + fClassName);
        fInit = (initFun)LoadOptimize("init_" + fClassName);
        fCompute = (computeFun)LoadOptimize("compute_" + fClassName);
        fMetadata = (metadataFun)LoadOptimize("metadata_" + fClassName);
        endTiming("initJIT");
        return true;
    } catch (...) { // Module does not contain the Faust entry points...
        endTiming("initJIT");
        return false;
    }
}

#endif

llvm_dsp_factory::~llvm_dsp_factory()
{
#if defined(LLVM_34) || defined(LLVM_35)
    delete fObjectCache;
#endif
    if (fJIT) {
        fJIT->runStaticConstructorsDestructors(true);
        // fResult->fModule is kept and deleted by fJIT
        delete fJIT;
    }
    
    if (fResult) {
        delete fResult->fContext;
        free(fResult);
    }
    
    if (--llvm_dsp_factory::gInstance == 0) {
    #ifndef LLVM_35 // In LLVM 3.5 this is gone.
        llvm_stop_multithreaded();
    #endif
    #if defined(LLVM_34) || defined(LLVM_35)
        LLVMResetFatalErrorHandler();
    #endif
    }
}

void llvm_dsp_factory::metadataDSPFactory(Meta* meta)
{
    MetaGlue glue;
    buildMetaGlue(&glue, meta);
    fMetadata(&glue);
}

void llvm_dsp_factory::metadataDSPFactory(MetaGlue* glue)
{
    fMetadata(glue);
}

string llvm_dsp_factory::getName()
{
    struct MyMeta : public Meta
    {
        string name;
        
        virtual void declare(const char* key, const char* value){
            if (strcmp(key, "name") == 0) {
                name = value;
            }
        }
    };
    
    MyMeta metadata;
    metadataDSPFactory (&metadata);
    return (fExtName != "") ? fExtName : metadata.name;
}
  
// Instance 

llvm_dsp_aux::llvm_dsp_aux(llvm_dsp_factory* factory, llvm_dsp_imp* dsp)
    :fDSPFactory(factory), fDSP(dsp)
{
    assert(fDSPFactory);
    assert(fDSP);
}
        
llvm_dsp_aux::~llvm_dsp_aux()
{   
    if (fDSP) {
        fDSPFactory->fDelete(fDSP);
    }
}

void llvm_dsp_aux::metadata(Meta* m)
{
    MetaGlue glue;
    buildMetaGlue(&glue, m);
    return fDSPFactory->fMetadata(&glue);
}

void llvm_dsp_aux::metadata(MetaGlue* m)
{
    return fDSPFactory->fMetadata(m);
}

int llvm_dsp_aux::getNumInputs()
{
    return fDSPFactory->fGetNumInputs(fDSP);
}
int llvm_dsp_aux::getNumOutputs()
{
    return fDSPFactory->fGetNumOutputs(fDSP);
}

void llvm_dsp_aux::init(int samplingFreq)
{
    fDSPFactory->fInit(fDSP, samplingFreq);
}

void llvm_dsp_aux::buildUserInterface(UI* ui_interface)
{
    UIGlue glue;
    buildUIGlue(&glue, ui_interface);
    fDSPFactory->fBuildUserInterface(fDSP, &glue);
}

void llvm_dsp_aux::buildUserInterface(UIGlue* glue)
{
    fDSPFactory->fBuildUserInterface(fDSP, glue);
}

void llvm_dsp_aux::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    AVOIDDENORMALS;
    fDSPFactory->fCompute(fDSP, count, input, output);
}

static llvm_dsp_factory* CheckDSPFactory(llvm_dsp_factory* factory, string& error_msg)
{   
    if (factory->initJIT(error_msg)) {
        return factory;
    } else {
        delete factory;
        return 0;
    }
}

EXPORT string path_to_content(const string& path)
{
    ifstream file(path.c_str(), ifstream::binary);
    
    file.seekg (0, file.end);
    int size = file.tellg();
    file.seekg (0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

static bool getFactory(const string& sha_key, FactoryTableIt& res)
{
    FactoryTableIt it;
    
    for (it = llvm_dsp_factory::gFactoryTable.begin(); it != llvm_dsp_factory::gFactoryTable.end(); it++) {
        if ((*it).first->getSHAKey() == sha_key) {
            res = it;
            return true;
        }
    }
    
    return false;
}

// Public C++ API

EXPORT llvm_dsp_factory* createDSPFactory(int argc, const char* argv[], 
                                        const string& name, 
                                        const string& input, const string& target, 
                                        string& error_msg, int opt_level)
{
    return CheckDSPFactory(new llvm_dsp_factory("", argc, argv, name, input, target, error_msg, opt_level), error_msg);
}

EXPORT llvm_dsp_factory* createDSPFactoryFromFile(const string& filename, 
                                                int argc, const char* argv[], 
                                                const string& target, 
                                                string& error_msg, int opt_level)
{
	string base = basename((char*)filename.c_str());

    size_t pos = filename.find(".dsp");
    
    if (pos != string::npos) {
        return createDSPFactoryFromString(base.substr(0, pos), path_to_content(filename), argc, argv, target, error_msg, opt_level);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)\n";
        return NULL;
    } 
}

EXPORT llvm_dsp_factory* createDSPFactoryFromString(const string& name_app, const string& dsp_content, 
                                                    int argc, const char* argv[], 
                                                    const string& target, 
                                                    string& error_msg, int opt_level)
{

//    ----- Filtrate Options for file generation ----------      //
    int numberArg = argc;
 
    for (int i=0; i<argc; i++) {
        if (strcmp(argv[i],"-svg") == 0 || 
           strcmp(argv[i],"-ps") == 0 || 
           strcmp(argv[i],"-tg") == 0 || 
           strcmp(argv[i],"-sg") == 0 || 
           strcmp(argv[i],"-mdoc") == 0 || 
           strcmp(argv[i],"-mdlang") == 0 || 
           strcmp(argv[i],"-stripdoc") == 0 || 
           strcmp(argv[i],"-xml") == 0)
            numberArg--;
    }

// New is needed, otherwise it doesn't compile on windows ! 
    const char** arguments = new const char*[numberArg];
    
    int i = 0;
    for (int j=0; j<numberArg; j++) {
        while (strcmp(argv[i],"-svg") == 0 || 
                strcmp(argv[i],"-ps") == 0 || 
                strcmp(argv[i],"-tg") == 0 || 
                strcmp(argv[i],"-sg") == 0 || 
                strcmp(argv[i],"-mdoc") == 0 || 
                strcmp(argv[i],"-mdlang") == 0 || 
                strcmp(argv[i],"-stripdoc") == 0 || 
                strcmp(argv[i],"-xml") == 0)
            i++;
        
        arguments[j] = argv[i];

        i++;
    }
    
//    --------- Reuse of compile DSP ------------------------    //
    string expanded_dsp;
    string sha_key;
    
    if ((expanded_dsp = expandDSPFromString(name_app, dsp_content, numberArg, arguments, sha_key, error_msg)) == "") {
		delete [] arguments;
        return 0; 
    } else {

        FactoryTableIt it;
        llvm_dsp_factory* factory = 0;
        if (getFactory(sha_key, it)) {
            Sllvm_dsp_factory sfactory = (*it).first;
            sfactory->addReference();
            
            delete [] arguments;
            return sfactory;
        } else if ((factory = CheckDSPFactory(new llvm_dsp_factory(sha_key, numberArg, arguments, name_app, dsp_content, target, error_msg, opt_level), error_msg)) != 0) {
            llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
            delete [] arguments;
            return factory;
        } else {
			delete [] arguments;
            return 0;
        }
    }
    
    /*
    string sha_key = generateSHA1(reorganize_compilation_options(argc, argv) + dsp_content);
    FactoryTableIt it;
    llvm_dsp_factory* factory = 0;
    
    if (getFactory(sha_key, it)) {
        Sllvm_dsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else if ((factory = CheckDSPFactory(new llvm_dsp_factory(sha_key, argc, argv, name_app, dsp_content, target, error_msg, opt_level), error_msg)) != 0) {
        llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
        return factory;
    } else {
        return 0;
    }*/
}

EXPORT llvm_dsp_factory* createDSPFactoryFromSHAKey(const string& sha_key)
{
    FactoryTableIt it;
    return (getFactory(sha_key, it)) ? (*it).first : NULL;
}

EXPORT vector<string> getAllDSPFactories()
{
    FactoryTableIt it;
    vector<string> sha_key_list;
    
    for (it = llvm_dsp_factory::gFactoryTable.begin(); it != llvm_dsp_factory::gFactoryTable.end(); it++) {
        sha_key_list.push_back((*it).first->getSHAKey());
    }
    
    return sha_key_list;
}

EXPORT void deleteDSPFactory(llvm_dsp_factory* factory) 
{   
    FactoryTableIt it;
    if ((it = llvm_dsp_factory::gFactoryTable.find(factory)) != llvm_dsp_factory::gFactoryTable.end()) {
        Sllvm_dsp_factory sfactory = (*it).first;
        if (sfactory->refs() == 2) { // Local stack pointer + the one in gFactoryTable...
            // Last use, remove from the global table, pointer will be deleted
            llvm_dsp_factory::gFactoryTable.erase(factory);
        } else {
            sfactory->removeReference();
        }
    }
}

EXPORT std::string getName(llvm_dsp_factory* factory)
{
    return factory->getName();
}

EXPORT std::string getSHAKey(llvm_dsp_factory* factory)
{
    return factory->getSHAKey();
}

EXPORT std::vector<std::string> getLibraryList(llvm_dsp_factory* factory)
{
    return factory->getLibraryList();
}

EXPORT void deleteAllDSPFactories()
{
    FactoryTableIt it;
    for (it = llvm_dsp_factory::gFactoryTable.begin(); it != llvm_dsp_factory::gFactoryTable.end(); it++) {
        // Decrement counter up to one...
        while (((*it).first)->refs() > 1) { ((*it).first)->removeReference(); }
    }
    // Then clear the table thus finally deleting all ref = 1 smart pointers
    llvm_dsp_factory::gFactoryTable.clear();
}
    
// Bitcode <==> string

#ifdef LLVM_35
// LLVM 3.5 has parseBitcodeFile(). Must emulate ParseBitcodeFile. -ag
static llvm::Module *ParseBitcodeFile(llvm::MemoryBuffer *Buffer,
				      llvm::LLVMContext& Context,
				      std::string *ErrMsg)
{
  using namespace llvm;
  ErrorOr<Module *> ModuleOrErr = parseBitcodeFile(Buffer, Context);
  if (std::error_code EC = ModuleOrErr.getError()) {
    if (ErrMsg) *ErrMsg = EC.message();
    return 0;
  } else
  return ModuleOrErr.get();
}
#endif

static llvm_dsp_factory* readDSPFactoryFromBitcodeAux(MemoryBuffer* buffer, const string& target, int opt_level)
{
    string sha_key = generateSHA1(buffer->getBuffer().str());
    FactoryTableIt it;
    
    if (getFactory(sha_key, it)) {
        Sllvm_dsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        string error_msg;
        LLVMContext* context = new LLVMContext();
        Module* module = ParseBitcodeFile(buffer, *context, &error_msg);
        llvm_dsp_factory* factory = 0;
        if (module && ((factory = CheckDSPFactory(new llvm_dsp_factory(sha_key, module, context, target, opt_level), error_msg)) != 0)) {
            llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
            return factory;
        } else {
            printf("readDSPFactoryFromBitcode failed : %s\n", error_msg.c_str());
            return 0;
        }
    }
}

EXPORT llvm_dsp_factory* readDSPFactoryFromBitcode(const string& bit_code, const string& target, int opt_level)
{
    return readDSPFactoryFromBitcodeAux(MemoryBuffer::getMemBuffer(StringRef(bit_code)), target, opt_level);
}

EXPORT string writeDSPFactoryToBitcode(llvm_dsp_factory* factory)
{
    return (factory) ? factory->writeDSPFactoryToBitcode() : "";
}

// Bitcode <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const string& bit_code_path, const string& target, int opt_level)
{
#ifdef LLVM_35
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(bit_code_path);
    if (std::error_code ec = buffer.getError()) {
        printf("readDSPFactoryFromBitcodeFile failed : %s\n", ec.message().c_str());
        return 0;
    } else {
        return readDSPFactoryFromBitcodeAux(buffer->get(), target, opt_level);
    }
#else

    OwningPtr<MemoryBuffer> buffer;
    if (llvm::error_code ec = MemoryBuffer::getFileOrSTDIN(bit_code_path.c_str(), buffer)) {
        printf("readDSPFactoryFromBitcodeFile failed : %s\n", ec.message().c_str());
        return 0;
    } else {
        return readDSPFactoryFromBitcodeAux(buffer.get(), target, opt_level);
    }
    
#endif
}

EXPORT void writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const string& bit_code_path)
{
    if (factory) {
        factory->writeDSPFactoryToBitcodeFile(bit_code_path);
    }
}

// IR <==> string

static llvm_dsp_factory* readDSPFactoryFromIRAux(MemoryBuffer* buffer, const string& target, int opt_level)
{
    string sha_key = generateSHA1(buffer->getBuffer().str());
    FactoryTableIt it;
    
    if (getFactory(sha_key, it)) {
        Sllvm_dsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        char* tmp_local = setlocale(LC_ALL, NULL);
        setlocale(LC_ALL, "C");
        LLVMContext* context = new LLVMContext();
        SMDiagnostic err;
        Module* module = ParseIR(buffer, err, *context); // ParseIR takes ownership of the given buffer, so don't delete it
        setlocale(LC_ALL, tmp_local);
        llvm_dsp_factory* factory = 0;
        string error_msg;
        if (module && ((factory = CheckDSPFactory(new llvm_dsp_factory(sha_key, module, context, target, opt_level), error_msg)) != 0)) {
            llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
            return factory;
        } else {
        #if defined(LLVM_31) || defined(LLVM_32) || defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35)
            err.print("readDSPFactoryFromIRAux failed :", errs());
        #else
            err.Print("readDSPFactoryFromIRAux failed :", errs());
        #endif
            return 0;
        }
    }
}

EXPORT llvm_dsp_factory* readDSPFactoryFromIR(const string& ir_code, const string& target, int opt_level)
{
    return readDSPFactoryFromIRAux(MemoryBuffer::getMemBuffer(StringRef(ir_code)), target, opt_level);
}

EXPORT string writeDSPFactoryToIR(llvm_dsp_factory* factory)
{
    return (factory) ? factory->writeDSPFactoryToIR() : "";
}

// IR <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromIRFile(const string& ir_code_path, const string& target, int opt_level)
{
#ifdef LLVM_35
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(ir_code_path);
    if (std::error_code ec = buffer.getError()) {
        printf("readDSPFactoryFromIRFile failed : %s\n", ec.message().c_str());
        return 0;
    } else {
        return readDSPFactoryFromIRAux(buffer->get(), target, opt_level);
    }
#else
    OwningPtr<MemoryBuffer> buffer;
    if (llvm::error_code ec = MemoryBuffer::getFileOrSTDIN(ir_code_path.c_str(), buffer)) {
        printf("readDSPFactoryFromIRFile failed : %s\n", ec.message().c_str());
        return 0;
    } else {
        return readDSPFactoryFromIRAux(buffer.get(), target, opt_level);
    }
#endif
}

EXPORT void writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const string& ir_code_path)
{
    if (factory) {
        factory->writeDSPFactoryToIRFile(ir_code_path);
    }
}

#if defined(LLVM_34) || defined(LLVM_35)
    
static llvm_dsp_factory* readDSPFactoryFromMachineAux(MemoryBuffer* buffer)
{
    string sha_key = generateSHA1(buffer->getBuffer().str());
    FactoryTableIt it;
    
    if (getFactory(sha_key, it)) {
        Sllvm_dsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        string error_msg;
        llvm_dsp_factory* factory = CheckDSPFactory(new llvm_dsp_factory(sha_key, buffer->getBuffer().str()), error_msg);
        llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
        return factory;
    }
}

// machine <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code)
{
    return readDSPFactoryFromMachineAux(MemoryBuffer::getMemBuffer(StringRef(machine_code)));
}

EXPORT std::string writeDSPFactoryToMachine(llvm_dsp_factory* factory)
{
    return factory->writeDSPFactoryToMachine();
}

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path)
{
#ifdef LLVM_35
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(machine_code_path);
    if (std::error_code ec = buffer.getError()) {
        printf("readDSPFactoryFromMachineFile failed : %s\n", ec.message().c_str());
        return 0;
    } else {
        return readDSPFactoryFromMachineAux(buffer->get());
    }
#else
    OwningPtr<MemoryBuffer> buffer;
    if (llvm::error_code ec = MemoryBuffer::getFileOrSTDIN(machine_code_path.c_str(), buffer)) {
        printf("readDSPFactoryFromMachineFile failed : %s\n", ec.message().c_str());
        return 0;
    } else {
        return readDSPFactoryFromMachineAux(buffer.get());
    }
#endif
}

EXPORT void writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const string& machine_code_path)
{
    if (factory) {
        factory->writeDSPFactoryToMachineFile(machine_code_path);
    }
}

#endif

EXPORT void metadataDSPFactory(llvm_dsp_factory* factory, Meta* m)
{
    if (factory && m) {
        factory->metadataDSPFactory(m);
    }
}

// Instance

EXPORT llvm_dsp* createDSPInstance(llvm_dsp_factory* factory)
{  
    FactoryTableIt it;
    if ((it = llvm_dsp_factory::gFactoryTable.find(factory)) != llvm_dsp_factory::gFactoryTable.end()) {
        llvm_dsp_aux* instance = factory->createDSPInstance();
        (*it).second.push_back(instance);
        return reinterpret_cast<llvm_dsp*>(instance);
    } else {
        return 0;
    }
}

EXPORT void deleteDSPInstance(llvm_dsp* dsp) 
{
    if (dsp) {
        FactoryTableIt it;
        llvm_dsp_aux* dsp_aux = reinterpret_cast<llvm_dsp_aux*>(dsp);
        llvm_dsp_factory* factory = dsp_aux->getFactory();
        
        it = llvm_dsp_factory::gFactoryTable.find(factory);
        assert(it != llvm_dsp_factory::gFactoryTable.end());
        (*it).second.remove(dsp_aux);
         
        delete dsp_aux; 
    }
}

EXPORT void llvm_dsp::metadata(Meta* m)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->metadata(m);
}

EXPORT int llvm_dsp::getNumInputs()
{
    return reinterpret_cast<llvm_dsp_aux*>(this)->getNumInputs();
}

int EXPORT llvm_dsp::getNumOutputs()
{
    return reinterpret_cast<llvm_dsp_aux*>(this)->getNumOutputs();
}

EXPORT void llvm_dsp::init(int samplingFreq)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->init(samplingFreq);
}

EXPORT void llvm_dsp::buildUserInterface(UI* ui_interface)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->buildUserInterface(ui_interface);
}

EXPORT void llvm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->compute(count, input, output);
}

// Public C interface

EXPORT llvm_dsp_factory* createCDSPFactoryFromSHAKey(const char* sha_key)
{
    return createDSPFactoryFromSHAKey(sha_key);
}

EXPORT llvm_dsp_factory* createCDSPFactory(int argc, const char* argv[], 
                                           const char* name, const char* input, 
                                           const char* target, char* error_msg, int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory = CheckDSPFactory(new llvm_dsp_factory("", argc, argv, name, input, target, error_msg_aux, opt_level), error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 256);
    return factory;
}

EXPORT llvm_dsp_factory* createCDSPFactoryFromFile(const char* filename, 
                                                   int argc, const char* argv[], 
                                                   const char* target, 
                                                   char* error_msg, int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory = createDSPFactoryFromFile(filename, argc, argv, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 256);
    return factory;                                
}

EXPORT llvm_dsp_factory* createCDSPFactoryFromString(const char* name_app, const char* dsp_content, 
                                                     int argc, const char* argv[], 
                                                     const char* target, 
                                                     char* error_msg, int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory = createDSPFactoryFromString(name_app, dsp_content, argc, argv, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 256);
    return factory;
}

EXPORT const char** getAllCDSPFactories()
{
    vector<string> sha_key_list1 = getAllDSPFactories();
    const char** sha_key_list2 = (const char**)malloc(sizeof(char*) * (sha_key_list1.size() + 1));
    
    size_t i;
    for (i = 0; i < sha_key_list1.size(); i++) {
        string sha_key1 = sha_key_list1[i];
        char* sha_key2 = (char*)malloc(sizeof(char) * (sha_key1.length() + 1));
        strcpy(sha_key2, sha_key1.c_str());
        sha_key_list2[i] = sha_key2;
    }
    
    // Last element is NULL
    sha_key_list2[i] = NULL;
    return sha_key_list2;
}

EXPORT void deleteCDSPFactory(llvm_dsp_factory* factory)
{
    if (factory) {
        deleteDSPFactory(factory);
    }
}

EXPORT char* getCName(llvm_dsp_factory* factory)
{
    if (factory) {
        string res = factory->getName();
        char* name = (char*)malloc(sizeof(char) * (res.length() + 1));
        strcpy(name, res.c_str());
        return name;
    } else {
        return NULL;
    }
}

EXPORT char* getCSHAKey(llvm_dsp_factory* factory)
{
    if (factory) {
        string res = factory->getSHAKey();
        char* key = (char*)malloc(sizeof(char) * (res.length() + 1));
        strcpy(key, res.c_str());
        return key;
    } else {
        return NULL;
    }
}

EXPORT const char** getCLibraryList(llvm_dsp_factory* factory)
{
    if (factory) {
        vector<string> library_list1 = factory->getLibraryList();
        const char** library_list2 = (const char**)malloc(sizeof(char*) * (library_list1.size() + 1));
        
        size_t i;
        for (i = 0; i < library_list1.size(); i++) {
            string library1 = library_list1[i];
            char* library2 = (char*)malloc(sizeof(char) * (library1.length() + 1));
            strcpy(library2, library1.c_str());
            library_list2[i] = library2;
        }
        
        // Last element is NULL
        library_list2[i] = NULL;
        return library_list2;
    } else {
        return NULL;
    }
}

EXPORT void deleteAllCDSPFactories()
{
    deleteAllDSPFactories();
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromBitcode(const char* bit_code, const char* target, int opt_level)
{
    return readDSPFactoryFromBitcode(bit_code, target, opt_level);
}

EXPORT const char* writeCDSPFactoryToBitcode(llvm_dsp_factory* factory)
{
    if (factory) {
        string str = writeDSPFactoryToBitcode(factory);
        char* cstr = (char*)malloc(str.length() + 1);
        strcpy(cstr, str.c_str());
        return cstr;
    } else {
        return NULL;
    }
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromBitcodeFile(const char* bit_code_path, const char* target, int opt_level)
{
    return readDSPFactoryFromBitcodeFile(bit_code_path, target, opt_level);
}

EXPORT void writeCDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const char* bit_code_path)
{
    if (factory) {
        writeDSPFactoryToBitcodeFile(factory, bit_code_path);
    }
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromIR(const char* ir_code, const char* target, int opt_level)
{
    return readDSPFactoryFromIR(ir_code, target, opt_level);
}

EXPORT const char* writeCDSPFactoryToIR(llvm_dsp_factory* factory)
{
    if (factory) {
        string str = writeDSPFactoryToIR(factory);
        char* cstr = (char*)malloc(str.length() + 1);
        strcpy(cstr, str.c_str());
        return cstr;
    } else {
        return NULL;
    }
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromIRFile(const char* ir_code_path, const char* target, int opt_level)
{
    return readDSPFactoryFromIRFile(ir_code_path, target, opt_level);
}

EXPORT void writeCDSPFactoryToIRFile(llvm_dsp_factory* factory, const char* ir_code_path)
{
    if (factory) {
        writeDSPFactoryToIRFile(factory, ir_code_path);
    }
}

#if defined(LLVM_34) || defined(LLVM_35)

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code)
{
    return readDSPFactoryFromMachine(machine_code);
}

EXPORT const char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory)
{
    if (factory) {
        string str = writeDSPFactoryToMachine(factory);
        char* cstr = (char*)malloc(str.length() + 1);
        strcpy(cstr, str.c_str());
        return cstr;
    } else {
        return NULL;
    }
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path)
{
    return readDSPFactoryFromMachineFile(machine_code_path);
}

EXPORT void writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path)
{
    if (factory) {
        writeDSPFactoryToMachineFile(factory, machine_code_path);
    }
}
#endif

EXPORT void metadataCDSPFactory(llvm_dsp_factory* factory, MetaGlue* glue)
{
    if (factory) {
        factory->metadataDSPFactory(glue);
    }
}

EXPORT void metadataCDSPInstance(llvm_dsp* dsp, MetaGlue* glue)
{
    if (dsp) {
        reinterpret_cast<llvm_dsp_aux*>(dsp)->metadata(glue);
    }
}

EXPORT int getNumInputsCDSPInstance(llvm_dsp* dsp)
{
    return (dsp) ? reinterpret_cast<llvm_dsp_aux*>(dsp)->getNumInputs(): 0;
}

EXPORT int getNumOutputsCDSPInstance(llvm_dsp* dsp)
{
    return (dsp) ? reinterpret_cast<llvm_dsp_aux*>(dsp)->getNumOutputs() : 0;
}

EXPORT void initCDSPInstance(llvm_dsp* dsp, int samplingFreq)
{
    if (dsp) {
        reinterpret_cast<llvm_dsp_aux*>(dsp)->init(samplingFreq);
    }
}

EXPORT void buildUserInterfaceCDSPInstance(llvm_dsp* dsp, UIGlue* glue)
{
    if (dsp) {
        reinterpret_cast<llvm_dsp_aux*>(dsp)->buildUserInterface(glue);
    }
}

EXPORT void computeCDSPInstance(llvm_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    if (dsp) {
        reinterpret_cast<llvm_dsp_aux*>(dsp)->compute(count, input, output);
    }
}

EXPORT llvm_dsp* createCDSPInstance(llvm_dsp_factory* factory)
{
    return (factory) ? reinterpret_cast<llvm_dsp*>(factory->createDSPInstance()) : 0;
 }

EXPORT void deleteCDSPInstance(llvm_dsp* dsp)
{
    if (dsp) {
        delete reinterpret_cast<llvm_dsp_aux*>(dsp); 
    }
}

EXPORT void generateCSHA1(const char* data, char* key)
{
    string res = generateSHA1(data);
    strncpy(key, res.c_str(), 20);
}

#endif // LLVM_BUILD

