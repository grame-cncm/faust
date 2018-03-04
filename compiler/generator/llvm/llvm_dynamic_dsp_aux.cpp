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

#include <stdio.h>
#include <string.h>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>

#include "compatibility.hh"
#include "llvm_dynamic_dsp_aux.hh"
#include "timing.hh"
#include "rn_base64.h"
#include "global.hh"
#include "Text.hh"
#include "libfaust.h"

#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/Support/Threading.h>

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    #include <llvm/IR/Module.h>
    #include <llvm/IR/LLVMContext.h>
    #include <llvm/IRReader/IRReader.h>
    #include <llvm/IR/DataLayout.h>
    #include <llvm/Support/FormattedStream.h>
    #include <llvm/Support/SourceMgr.h>
    #include <llvm/Support/MemoryBuffer.h>
    #include <llvm/ADT/Triple.h>
    #include <llvm/Support/TargetRegistry.h>
    #include <llvm-c/Core.h>
    #include <llvm/Support/Host.h>
    #include <llvm/MC/SubtargetFeature.h>
#else
    #include <llvm/Module.h>
    #include <llvm/LLVMContext.h>
    #include <llvm/Support/IRReader.h>
#endif

#if defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    #include <llvm/Analysis/TargetLibraryInfo.h>
    #include <llvm/Analysis/TargetTransformInfo.h>
    #include <llvm/IR/PassManager.h>
    #include <llvm/IR/LegacyPassManager.h>
    #define PASS_MANAGER legacy::PassManager
    #define FUNCTION_PASS_MANAGER legacy::FunctionPassManager
#else
    #include <llvm/Target/TargetLibraryInfo.h>
    #include <llvm/PassManager.h>
    #define PASS_MANAGER PassManager
    #define FUNCTION_PASS_MANAGER FunctionPassManager
#endif

#if defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    #include <llvm/Bitcode/BitcodeWriter.h>
    #include <llvm/Bitcode/BitcodeReader.h>
    #include <llvm/Transforms/IPO/AlwaysInliner.h>
#elif defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39)
    #include <llvm/Bitcode/ReaderWriter.h>
#endif

/* The file llvm/Target/TargetData.h was renamed to llvm/DataLayout.h in LLVM
 * 3.2, which itself appears to have been moved to llvm/IR/DataLayout.h in LLVM
 * 3.3.
 */
#if defined(LLVM_32)
    #include <llvm/DataLayout.h>
#elif !defined(LLVM_33) && !defined(LLVM_34) && !defined(LLVM_35) && !defined(LLVM_36) && !defined(LLVM_37) && !defined(LLVM_38) && !defined(LLVM_39) && !defined(LLVM_40) && !defined(LLVM_50) && !defined(LLVM_60)
    #ifndef _WIN32
    #include <llvm/Target/TargetData.h>
    #endif
#endif

#if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    #include <llvm/ExecutionEngine/MCJIT.h>
    #include <llvm/ExecutionEngine/ObjectCache.h>
#else
    #include <llvm/ExecutionEngine/JIT.h>
#endif

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    #include <llvm/IR/LegacyPassNameParser.h>
    #include <llvm/Linker/Linker.h>
    #include <llvm/IR/IRPrintingPasses.h>
    #include <system_error>
    #include <llvm/IR/Verifier.h>
    #include <llvm/Support/FileSystem.h>
    #define llvmcreatePrintModulePass(out) createPrintModulePass(out)
    #define OwningPtr std::unique_ptr
    #define GET_CPU_NAME llvm::sys::getHostCPUName().str()
#else
    #include <llvm/Support/PassNameParser.h>
    #include <llvm/Linker.h>
    #include <llvm/Assembly/PrintModulePass.h>
    #include <llvm/Support/system_error.h>
    #include <llvm/Analysis/Verifier.h>
    #define llvmcreatePrintModulePass(out) createPrintModulePass(&out)
    #define GET_CPU_NAME llvm::sys::getHostCPUName()
#endif

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
    #include "llvm/ExecutionEngine/ObjectCache.h"
#endif

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    #define sysfs_binary_flag sys::fs::F_None
#elif defined(LLVM_34)
    #define sysfs_binary_flag sys::fs::F_Binary
#else
    #define sysfs_binary_flag raw_fd_ostream::F_Binary
#endif

#if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    #define STREAM_ERROR std::error_code
    #define MEMORY_BUFFER MemoryBufferRef
    #define MEMORY_BUFFER_GET(buffer) (buffer.getBuffer())
    #define MEMORY_BUFFER_GET_REF(buffer) (buffer->get()->getMemBufferRef())
    #define MEMORY_BUFFER_CREATE(stringref) (MemoryBufferRef(stringref, ""))
#else
    #define STREAM_ERROR string
    #define MEMORY_BUFFER MemoryBuffer*
    #define MEMORY_BUFFER_GET(buffer) (buffer->getBuffer())
    #define MEMORY_BUFFER_GET_REF(buffer) (buffer->get())
    #define MEMORY_BUFFER_CREATE(stringref) (MemoryBuffer::getMemBuffer(stringref))
#endif

#if defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    #define ModulePTR std::unique_ptr<Module>
    #define MovePTR(ptr) std::move(ptr)
#else
    #define ModulePTR Module*
    #define MovePTR(ptr) ptr
#endif

using namespace llvm;
using namespace std;

static void splitTarget(const string& target, string& triple, string& cpu)
{
    size_t pos1 = target.find_first_of(':');
    triple = target.substr(0, pos1);
    if (pos1 != string::npos) {
        cpu = target.substr(pos1 + 1);
    }
}

static string getParam(int argc, const char* argv[], const string& param, const string& def)
{
    for (int i = 0; i < argc; i++) {
        if (string(argv[i]) == param) return argv[i+1];
    }
    return def;
}

static bool isParam(int argc, const char* argv[], const string& param)
{
    for (int i = 0; i < argc; i++) {
        if (string(argv[i]) == param) return true;
    }
    return false;
}

static void dumpModule(Module* module)
{
    string res;
    raw_string_ostream out_str(res);
    out_str << *module;
    std::cout << out_str.str();
}

#if defined(LLVM_35) || defined(LLVM_36)
// LLVM 3.5 has parseBitcodeFile(). Must emulate ParseBitcodeFile. -ag
static Module* ParseBitcodeFile(MEMORY_BUFFER Buffer,
                                LLVMContext& Context,
                                string* ErrMsg)
{
    using namespace llvm;
    ErrorOr<Module*> ModuleOrErr = parseBitcodeFile(Buffer, Context);
    if (error_code EC = ModuleOrErr.getError()) {
        if (ErrMsg) *ErrMsg = EC.message();
        return nullptr;
    } else {
        return ModuleOrErr.get();
    }

}
#endif

#if defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)

static Module* ParseBitcodeFile(MEMORY_BUFFER Buffer,
                                LLVMContext& Context,
                                string* ErrMsg)
{
    using namespace llvm;
    Expected<std::unique_ptr<Module>> ModuleOrErr = parseBitcodeFile(Buffer, Context);
    if (!ModuleOrErr) {
        if (ErrMsg) *ErrMsg = "Failed to read bitcode";
        return nullptr;
    } else {
        return ModuleOrErr.get().release();
    }
}

#elif defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39)

static Module* ParseBitcodeFile(MEMORY_BUFFER Buffer,
                                LLVMContext& Context,
                                string* ErrMsg)
{
    using namespace llvm;
    ErrorOr<unique_ptr<Module>> ModuleOrErr = parseBitcodeFile(Buffer, Context);
    if (error_code EC = ModuleOrErr.getError()) {
        if (ErrMsg) *ErrMsg = EC.message();
        return nullptr;
    } else {
        return ModuleOrErr.get().release();
    }
}

#endif

// Bitcode
string llvm_dynamic_dsp_factory_aux::writeDSPFactoryToBitcode()
{
    string res;
    raw_string_ostream out(res);
    WriteBitcodeToFile(fModule, out);
    out.flush();
    return base64_encode(res);
}

void llvm_dynamic_dsp_factory_aux::writeDSPFactoryToBitcodeFile(const string& bit_code_path)
{
    STREAM_ERROR err;
    raw_fd_ostream out(bit_code_path.c_str(), err, sysfs_binary_flag);
    WriteBitcodeToFile(fModule, out);
}

// IR
string llvm_dynamic_dsp_factory_aux::writeDSPFactoryToIR()
{
    string res;
    raw_string_ostream out(res);
    PASS_MANAGER PM;
    PM.add(llvmcreatePrintModulePass(out));
    PM.run(*fModule);
    out.flush();
    return res;
}

void llvm_dynamic_dsp_factory_aux::writeDSPFactoryToIRFile(const string& ir_code_path)
{
    STREAM_ERROR err;
    raw_fd_ostream out(ir_code_path.c_str(), err, sysfs_binary_flag);
    PASS_MANAGER PM;
    PM.add(llvmcreatePrintModulePass(out));
    PM.run(*fModule);
    out.flush();
}

llvm_dynamic_dsp_factory_aux::llvm_dynamic_dsp_factory_aux(const string& sha_key,
                                                           const std::vector<std::string>& pathname_list,
                                                           Module* module,
                                                           LLVMContext* context,
                                                           const string& target,
                                                           int opt_level)
    :llvm_dsp_factory_aux("BitcodeDSP", sha_key, "", pathname_list)
{
    startLLVMLibrary();
     
    init("BitcodeDSP", "");
    fSHAKey = sha_key;
    fTarget = (target == "") ? fTarget = (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME) : target;
    setOptlevel(opt_level);
    
    fModule = module;
    fContext = context;
    
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
    fObjectCache = nullptr;
#endif
}

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
/// AddOptimizationPasses - This routine adds optimization passes
/// based on selected optimization level, OptLevel. This routine
/// duplicates llvm-gcc behaviour.
///
/// OptLevel - Optimization Level
static void AddOptimizationPasses(PassManagerBase &MPM,
                                  FUNCTION_PASS_MANAGER &FPM,
                                  unsigned OptLevel,
                                  unsigned SizeLevel)
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
    #if defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
        Builder.Inliner = createAlwaysInlinerLegacyPass();
    #else
        Builder.Inliner = createAlwaysInlinerPass();
    #endif
    }
      
    Builder.DisableUnrollLoops = (OptLevel == 0);
#if defined(LLVM_33)   
    Builder.DisableSimplifyLibCalls = false;
#endif
    
    // Add auto-vectorization passes
    if (OptLevel > 3) {
        Builder.LoopVectorize = true;
        Builder.SLPVectorize = true;
    }
    
    Builder.populateFunctionPassManager(FPM);
    Builder.populateModulePassManager(MPM);
}

bool llvm_dsp_factory_aux::initJIT(string& error_msg)
{
    startTiming("initJIT");
    
    //std::cout << "getFeaturesStr : " << getFeaturesStr() << std::endl;
#ifdef LLVM_BUILD_UNIVERSAL
    // For multiple target support
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmPrinters();
    InitializeAllAsmParsers();
#endif
      
    // For host target support
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    
    // For ObjectCache to work...
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
    LLVMLinkInMCJIT();
#endif
    
    // Restoring from machine code
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
    if (fObjectCache) {
    
        // JIT
    #if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
        EngineBuilder builder((unique_ptr<Module>(fModule)));
    #else
        EngineBuilder builder(fModule);
    #endif
        builder.setEngineKind(EngineKind::JIT);
    #if !defined(LLVM_36) && !defined(LLVM_37) && !defined(LLVM_38) && !defined(LLVM_39) && !defined(LLVM_40) && !defined(LLVM_50) && !defined(LLVM_60)
        builder.setUseMCJIT(true);
    #endif
        TargetMachine* tm = builder.selectTarget();
        fJIT = builder.create(tm);
        fJIT->setObjectCache(fObjectCache);
        fJIT->finalizeObject();
          
    } else {
#endif
        // First check is Faust compilation succeeded... (valid LLVM module)
        if (!fModule) {
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
    #if !defined(LLVM_38) && !defined(LLVM_39) && !defined(LLVM_40) && !defined(LLVM_50) && !defined(LLVM_60)
        initializeIPA(Registry);
    #endif
        initializeTransformUtils(Registry);
        initializeInstCombine(Registry);
        initializeInstrumentation(Registry);
        initializeTarget(Registry);
       
    #if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
        EngineBuilder builder((unique_ptr<Module>(fModule)));
    #else
        EngineBuilder builder(fModule);
    #endif
        builder.setOptLevel(CodeGenOpt::Aggressive);
        builder.setEngineKind(EngineKind::JIT);
    #if !defined(LLVM_60)
        builder.setCodeModel(CodeModel::JITDefault);
    #endif
        
        string buider_error;
        builder.setErrorStr(&buider_error);
        
        // MCJIT does not work correctly (incorrect float numbers ?) when used with dynamic libLLVM
    #if (defined(LLVM_34) || defined(LLVM_35)) && !defined(_MSC_VER)
        builder.setUseMCJIT(true);
    #elif !defined(LLVM_36) && !defined(LLVM_37) && !defined(LLVM_38) && !defined(LLVM_39) && !defined(LLVM_40) && !defined(LLVM_50) && !defined(LLVM_60)
        builder.setUseMCJIT(false);
    #endif
    
    #ifdef _WIN32
        // Windows needs this special suffix to the target triple,
        // otherwise the backend would try to generate native COFF
        // code which the JIT can't use
        // (cf. http://lists.cs.uiuc.edu/pipermail/llvmdev/2013-December/068407.html).
        string target_suffix = "-elf";
    #else
        string target_suffix = "";
    #endif
    
        string triple, cpu;
        splitTarget(fTarget, triple, cpu);
        fModule->setTargetTriple(triple + target_suffix);
        
    #if defined(LLVM_33)
        builder.setMCPU((cpu == "") ? llvm::sys::getHostCPUName() : static_cast<std::basic_string<char>>(StringRef(cpu)));
    #elif defined(LLVM_34)
        builder.setMCPU((cpu == "") ? llvm::sys::getHostCPUName() : cpu);
    #else
        builder.setMCPU((cpu == "") ? llvm::sys::getHostCPUName() : StringRef(cpu));
        //std::cout << "llvm::sys::getHostCPUName()" << llvm::sys::getHostCPUName().data() << std::endl;
    #endif
        
        TargetOptions targetOptions;
        
        // -fastmath is activated at IR level, and has to be setup at JIT level also
        
    #if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    #if !defined(LLVM_50) && !defined(LLVM_60)
        targetOptions.LessPreciseFPMADOption = true;
    #endif
        targetOptions.AllowFPOpFusion = FPOpFusion::Fast;
        targetOptions.UnsafeFPMath = true;
        targetOptions.NoInfsFPMath = true;
        targetOptions.NoNaNsFPMath = true;
        targetOptions.GuaranteedTailCallOpt = true;
    #endif
    
    #if defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
        targetOptions.NoTrappingFPMath = true;
        targetOptions.FPDenormalMode = FPDenormal::IEEE;
    #endif
        
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
            error_msg = "Cannot create LLVM JIT : " + buider_error;
            return false;
        }
        
        int optlevel = getOptlevel();
        
        if ((optlevel == -1) || (fOptLevel > optlevel)) {
            PASS_MANAGER pm;
            FUNCTION_PASS_MANAGER fpm(fModule);
            
        #if defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60) // Code taken from opt.cpp
            TargetLibraryInfoImpl TLII(Triple(fModule->getTargetTriple()));
            pm.add(new TargetLibraryInfoWrapperPass(TLII));
        #else
            // Add an appropriate TargetLibraryInfo pass for the module's triple.
            TargetLibraryInfo* tli = new TargetLibraryInfo(Triple(fModule->getTargetTriple()));
            pm.add(tli);
        #endif

        #if defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
            fModule->setDataLayout(fJIT->getDataLayout());
        #elif defined(LLVM_37) // Code taken from opt.cpp
            fModule->setDataLayout(*fJIT->getDataLayout());
        #elif defined(LLVM_35) || defined(LLVM_36)
            // LLVM 3.5 doesn't need a separate pass for the data
            // layout, but it does require that we initialize the
            // data layout of the module. -ag
            fModule->setDataLayout(fJIT->getDataLayout());
        #else
            fModule->setDataLayout(fJIT->getDataLayout()->getStringRepresentation());
        #endif
          
            // Add internal analysis passes from the target machine (mandatory for vectorization to work)
        #if defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60) // Code taken from opt.cpp
            pm.add(createTargetTransformInfoWrapperPass(tm->getTargetIRAnalysis()));
        #else
            tm->addAnalysisPasses(pm);
        #endif
          
            if (fOptLevel > 0) {
                AddOptimizationPasses(pm, fpm, fOptLevel, 0);
            }
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM1") != string::npos)) {
            #if defined(LLVM_60)
              // TargetRegistry::printRegisteredTargetsForVersion(std::cout);
            #else
                TargetRegistry::printRegisteredTargetsForVersion();
            #endif
                dumpModule(fModule);
            }
           
            fpm.doInitialization();
            for (Module::iterator F = fModule->begin(), E = fModule->end(); F != E; ++F) {
                fpm.run(*F);
            }
            fpm.doFinalization();
            
            pm.add(createVerifierPass());
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM4") != string::npos)) {
            #if defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
                // TODO
            #else
                tm->addPassesToEmitFile(pm, fouts(), TargetMachine::CGFT_AssemblyFile, true);
            #endif
            }
            
            // Now that we have all of the passes ready, run them.
            pm.run(*fModule);
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM2") != string::npos)) {
                dumpModule(fModule);
            }
        }
        
    #if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
        fObjectCache = new FaustObjectCache();
        fJIT->setObjectCache(fObjectCache);
    }
    #endif
    
    // Run static constructors.
    fJIT->runStaticConstructorsDestructors(false);
    fJIT->DisableLazyCompilation(true);
    
    try {
        fNew = (newDspFun)loadOptimize("new" + fClassName);
        fDelete = (deleteDspFun)loadOptimize("delete" + fClassName);
        fGetNumInputs = (getNumInputsFun)loadOptimize("getNumInputs" + fClassName);
        fGetNumOutputs = (getNumOutputsFun)loadOptimize("getNumOutputs" + fClassName);
        fGetSize = (getSizeFun)loadOptimize("getSize" + fClassName);
        fBuildUserInterface = (buildUserInterfaceFun)loadOptimize("buildUserInterface" + fClassName);
        fInit = (initFun)loadOptimize("init" + fClassName);
        fInstanceInit = (initFun)loadOptimize("instanceInit" + fClassName);
        fInstanceConstants = (initFun)loadOptimize("instanceConstants" + fClassName);
        fInstanceResetUI = (clearFun)loadOptimize("instanceResetUserInterface" + fClassName);
        fInstanceClear = (clearFun)loadOptimize("instanceClear" + fClassName);
        fGetSampleRate = (getSampleRateFun)loadOptimize("getSampleRate" + fClassName);
        fCompute = (computeFun)loadOptimize("compute" + fClassName);
        fMetadata = (metadataFun)loadOptimize("metadata" + fClassName);
        fGetSampleSize = (getSampleSizeFun)loadOptimize("getSampleSize" + fClassName);
        endTiming("initJIT");
        return true;
     } catch (faustexception& e) { // Module does not contain the Faust entry points, or external symbol was not found...
        endTiming("initJIT");
        error_msg = e.Message();
        return false;
    }
}

#else

bool llvm_dynamic_dsp_factory_aux::initJIT(string& error_msg)
{
    startTiming("initJIT");
    
    // First check is Faust compilation succeeded... (valid LLVM module)
    if (!fModule) {
        return false;
    }
    
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    
    fModule->setTargetTriple(fTarget);
   
    EngineBuilder builder(fModule);
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
    fModule->setDataLayout(fJIT->getDataLayout()->getStringRepresentation());
#else
    fModule->setDataLayout(fJIT->getTargetData()->getStringRepresentation());
#endif

    int optlevel = getOptlevel();
    
    if ((optlevel == -1) || (fOptLevel > optlevel)) {
        // Set up the optimizer pipeline. Start with registering info about how the
        // target lays out data structures.
        PASS_MANAGER pm;
        FUNCTION_PASS_MANAGER fpm(fModule);
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
            dumpModule(fModule);
        }
        
        // Now that we have all of the passes ready, run them.
        pm.run(*fModule);
        
        if ((debug_var != "") && (debug_var.find("FAUST_LLVM2") != string::npos)) {
            dumpModule(fModule);
        }
    }
     
    try {
        fNew = (newDspFun)loadOptimize("new" + fClassName);
        fDelete = (deleteDspFun)loadOptimize("delete" + fClassName);
        fGetNumInputs = (getNumInputsFun)loadOptimize("getNumInputs" + fClassName);
        fGetNumOutputs = (getNumOutputsFun)loadOptimize("getNumOutputs" + fClassName);
        fGetSize = (getSizeFun)loadOptimize("getSize" + fClassName);
        fBuildUserInterface = (buildUserInterfaceFun)loadOptimize("buildUserInterface" + fClassName);
        fInit = (initFun)loadOptimize("init" + fClassName);
        fInstanceInit = (initFun)loadOptimize("instanceInit" + fClassName);
        fInstanceConstants = (initFun)loadOptimize("instanceConstants" + fClassName);
        fInstanceResetUI = (clearFun)loadOptimize("instanceResetUserInterface" + fClassName);
        fInstanceClear = (clearFun)loadOptimize("instanceClear" + fClassName);
        fGetSampleRate = (getSampleRateFun)loadOptimize("getSampleRate" + fClassName);
        fCompute = (computeFun)loadOptimize("compute" + fClassName);
        fMetadata = (metadataFun)loadOptimize("metadata" + fClassName);
        fGetSampleSize = (getSampleSizeFun)loadOptimize("getSampleSize" + fClassName);
        endTiming("initJIT");
        return true;
    } catch (...) { // Module does not contain the Faust entry points...
        endTiming("initJIT");
        return false;
    }
}

#endif

// Public C++ API

EXPORT llvm_dsp_factory* createDSPFactoryFromFile(const string& filename,
                                                int argc, const char* argv[], 
                                                const string& target, 
                                                string& error_msg, int opt_level)
{
	string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    
    if (pos != string::npos) {
        return createDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc, argv, target, error_msg, opt_level);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)";
        return nullptr;
    } 
}

EXPORT llvm_dsp_factory* createDSPFactoryFromString(const string& name_app, const string& dsp_content,
                                                    int argc, const char* argv[], 
                                                    const string& target, 
                                                    string& error_msg, int opt_level)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    
    string expanded_dsp_content, sha_key;
    
    if ((expanded_dsp_content = expandDSPFromString(name_app, dsp_content, argc, argv, sha_key, error_msg)) == "") {
        return nullptr; 
    } else {
        
        int argc1 = 0;
        const char* argv1[64];
        
        argv1[argc1++] = "faust";
        argv1[argc1++] = "-lang";
        //argv1[2] = "cllvm";
        argv1[argc1++] = "llvm";
        argv1[argc1++] = "-o";
        argv1[argc1++] = "string";
        
        // Filter arguments
        for (int i = 0; i < argc; i++) {
            if (!(strcmp(argv[i],"-tg") == 0 ||
                  strcmp(argv[i],"-sg") == 0 ||
                  strcmp(argv[i],"-ps") == 0 ||
                  strcmp(argv[i],"-svg") == 0 ||
                  strcmp(argv[i],"-mdoc") == 0 ||
                  strcmp(argv[i],"-mdlang") == 0 ||
                  strcmp(argv[i],"-stripdoc") == 0 ||
                  strcmp(argv[i],"-sd") == 0 ||
                  strcmp(argv[i],"-xml") == 0 ||
                  strcmp(argv[i],"-json") == 0))
            {
                argv1[argc1++] = argv[i];
            }
        }
        
        argv1[argc1] = 0;  // NULL terminated argv
        
        dsp_factory_table<SDsp_factory>::factory_iterator it;
        llvm_dsp_factory* factory = 0;
        
        if (llvm_dsp_factory_aux::gLLVMFactoryTable.getFactory(sha_key, it)) {
            SDsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else {
            llvm_dynamic_dsp_factory_aux* factory_aux = static_cast<llvm_dynamic_dsp_factory_aux*>(compileFaustFactory(argc1, argv1,
                                                                                                        name_app.c_str(),
                                                                                                        dsp_content.c_str(),
                                                                                                        error_msg,
                                                                                                        true));
            
            if (factory_aux && factory_aux->initJIT(error_msg)) {
                factory_aux->setTarget(target);
                factory_aux->setOptlevel(opt_level);
                factory_aux->setClassName(getParam(argc, argv, "-cn", "mydsp"));
                factory_aux->setName(name_app);
                factory = new llvm_dsp_factory(factory_aux);
                llvm_dsp_factory_aux::gLLVMFactoryTable.setFactory(factory);
                factory->setSHAKey(sha_key);
                factory->setDSPCode(expanded_dsp_content);
                return factory;
            } else {
                delete factory_aux;
                return NULL;
            }
        }
    }
}

// Bitcode <==> string
static llvm_dsp_factory* readDSPFactoryFromBitcodeAux(MEMORY_BUFFER buffer, const string& target, int opt_level)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    dsp_factory_table<SDsp_factory>::factory_iterator it;
    
    if (llvm_dsp_factory_aux::gLLVMFactoryTable.getFactory(sha_key, it)) {
        SDsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        string error_msg;
        LLVMContext* context = new LLVMContext();
        Module* module = ParseBitcodeFile(buffer, *context, &error_msg);
        if (!module) return nullptr;
        
        std::vector<std::string> dummy_list;
        llvm_dynamic_dsp_factory_aux* factory_aux = new llvm_dynamic_dsp_factory_aux(sha_key, dummy_list, module, context, target, opt_level);
        
        if (factory_aux->initJIT(error_msg)) {
            llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
            llvm_dsp_factory_aux::gLLVMFactoryTable.setFactory(factory);
            factory->setSHAKey(sha_key);
            return factory;
        } else {
            std::cerr << "readDSPFactoryFromBitcode failed : " << error_msg << std::endl;
            delete factory_aux;
            return nullptr;
        }
    }
}

EXPORT llvm_dsp_factory* readDSPFactoryFromBitcode(const string& bit_code, const string& target, int opt_level)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return readDSPFactoryFromBitcodeAux(MEMORY_BUFFER_CREATE(StringRef(base64_decode(bit_code))), target, opt_level);
}

EXPORT string writeDSPFactoryToBitcode(llvm_dsp_factory* factory)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return (factory) ? factory->writeDSPFactoryToBitcode() : "";
}

// Bitcode <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const string& bit_code_path, const string& target, int opt_level)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
  
#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(bit_code_path);
    if (error_code ec = buffer.getError()) {
        std::cerr << "readDSPFactoryFromBitcodeFile failed : " << ec.message() << std::endl;
        return nullptr;
    } else {
        return readDSPFactoryFromBitcodeAux(MEMORY_BUFFER_GET_REF(buffer), target, opt_level);
     }
#else
    OwningPtr<MemoryBuffer> buffer;
    if (llvm::error_code ec = MemoryBuffer::getFileOrSTDIN(bit_code_path.c_str(), buffer)) {
        std::cerr << "readDSPFactoryFromBitcodeFile failed : " << ec.message() << std::endl;
        return nullptr;
    } else {
        return readDSPFactoryFromBitcodeAux(buffer.get(), target, opt_level);
    }
#endif
}

EXPORT void writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const string& bit_code_path)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    if (factory) {
        factory->writeDSPFactoryToBitcodeFile(bit_code_path);
    }
}

// IR <==> string

static llvm_dsp_factory* readDSPFactoryFromIRAux(MEMORY_BUFFER buffer, const string& target, int opt_level)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    dsp_factory_table<SDsp_factory>::factory_iterator it;
    
    if (llvm_dsp_factory_aux::gLLVMFactoryTable.getFactory(sha_key, it)) {
        SDsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        char* tmp_local = setlocale(LC_ALL, NULL);
        setlocale(LC_ALL, "C");
        LLVMContext* context = new LLVMContext();
        SMDiagnostic err;
    #if defined(LLVM_36) || defined(LLVM_37) ||defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
        Module* module = parseIR(buffer, err, *context).release();  // parseIR takes ownership of the given buffer, so don't delete it
    #else
        Module* module = ParseIR(buffer, err, *context);            // ParseIR takes ownership of the given buffer, so don't delete it
    #endif
        if (!module) return nullptr;
        
        setlocale(LC_ALL, tmp_local);
        string error_msg;
        std::vector<std::string> dummy_list;
        llvm_dynamic_dsp_factory_aux* factory_aux = new llvm_dynamic_dsp_factory_aux(sha_key, dummy_list, module, context, target, opt_level);
        
        if (factory_aux->initJIT(error_msg)) {
            llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
            llvm_dsp_factory_aux::gLLVMFactoryTable.setFactory(factory);
            factory->setSHAKey(sha_key);
            return factory;
        } else {
            std::cerr << "readDSPFactoryFromBitcode failed : " << error_msg << std::endl;
            delete factory_aux;
            return nullptr;
        }
    }
}

EXPORT llvm_dsp_factory* readDSPFactoryFromIR(const string& ir_code, const string& target, int opt_level)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return readDSPFactoryFromIRAux(MEMORY_BUFFER_CREATE(StringRef(ir_code)), target, opt_level);
}

EXPORT string writeDSPFactoryToIR(llvm_dsp_factory* factory)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return (factory) ? factory->writeDSPFactoryToIR() : "";
}

// IR <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromIRFile(const string& ir_code_path, const string& target, int opt_level)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
 
 #if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(ir_code_path);
    if (error_code ec = buffer.getError()) {
        std::cerr << "readDSPFactoryFromIRFile failed : " << ec.message() << std::endl;
        return nullptr;
    } else {
        return readDSPFactoryFromIRAux(MEMORY_BUFFER_GET_REF(buffer), target, opt_level);
    }
#else
    OwningPtr<MemoryBuffer> buffer;
    if (llvm::error_code ec = MemoryBuffer::getFileOrSTDIN(ir_code_path.c_str(), buffer)) {
        std::cerr << "readDSPFactoryFromIRFile failed : " << ec.message() << std::endl;
        return nullptr;
    } else {
        return readDSPFactoryFromIRAux(buffer.get(), target, opt_level);
    }
#endif
}

EXPORT void writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const string& ir_code_path)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    
    if (factory) {
        factory->writeDSPFactoryToIRFile(ir_code_path);
    }
}

EXPORT string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const string& target)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return factory->writeDSPFactoryToMachine(target);
}

EXPORT void writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const string& machine_code_path, const string& target)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    if (factory) {
        factory->writeDSPFactoryToMachineFile(machine_code_path, target);
    }
}

// Helper functions

ModulePTR loadSingleModule(const string filename, LLVMContext* context)
{
    SMDiagnostic err;
#if defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    ModulePTR module = parseIRFile(filename, err, *context);
#elif defined(LLVM_36) || defined(LLVM_37)
    ModulePTR module = parseIRFile(filename, err, *context).release();
#else
    Module* module = ParseIRFile(filename, err, *context);
#endif
    
    if (module) {
        return module;
    } else {
        //err.print("ParseIRFile failed :", errs());
        return nullptr;
    }
}

ModulePTR loadModule(const string& module_name, llvm::LLVMContext* context)
{
    // Try as a complete path
    if (ModulePTR module = loadSingleModule(module_name, context)) {
        return module;
    } else {
        // Otherwise use import directories
        list<string>::iterator it;
        for (it = gGlobal->gImportDirList.begin(); it != gGlobal->gImportDirList.end(); it++) {
            string file_name = *it + '/' + module_name;
            if (ModulePTR module = loadSingleModule(file_name, context)) {
                return module;
            }
        }
        return nullptr;
    }
}

bool linkModules(Module* dst, ModulePTR src, char* error_msg)
{
    bool res = false;
    
#if defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    if (Linker::linkModules(*dst, MovePTR(src))) {
        snprintf(error_msg, 256, "cannot link module");
        
#elif defined(LLVM_36) || defined(LLVM_37)
    if (Linker::LinkModules(dst, MovePTR(src))) {
        snprintf(error_msg, 256, "cannot link module");
#else
    string err;
    if (Linker::LinkModules(dst, src, Linker::DestroySource, &err)) {
        snprintf(error_msg, 256, "cannot link module : %s", err.c_str());
#endif
    } else {
        res = true;
    }
#if defined(LLVM_34) || defined(LLVM_35)
    delete src;
#endif
    return res;
}
        
Module* linkAllModules(llvm::LLVMContext* context, Module* dst, char* error)
{
    list<string>::iterator it;
    
    for (it = gGlobal->gLibraryList.begin(); it != gGlobal->gLibraryList.end(); it++) {
        string module_name = *it;
        ModulePTR src = loadModule(module_name, context);
        if (!src) {
            sprintf(error, "cannot load module : %s", module_name.c_str());
            return nullptr;
        }
        if (!linkModules(dst, MovePTR(src), error)) {
            return nullptr;
        }
    }
    
    return dst;
}

// Public C interface : lock management is done by called C++ API

EXPORT llvm_dsp_factory* createCDSPFactoryFromFile(const char* filename,
                                                   int argc, const char* argv[],
                                                   const char* target,
                                                   char* error_msg, int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory = createDSPFactoryFromFile(filename, argc, argv, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

EXPORT llvm_dsp_factory* createCDSPFactoryFromString(const char* name_app, const char* dsp_content,
                                                     int argc, const char* argv[],
                                                     const char* target,
                                                     char* error_msg, int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory = createDSPFactoryFromString(name_app, dsp_content, argc, argv, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}
