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
#include <string.h>
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
#include "rn_base64.h"

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    #include <system_error>
#else
    #include <llvm/Support/system_error.h>
#endif

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    #include <llvm/IR/Module.h>
    #include <llvm/IR/LLVMContext.h>
    #include <llvm/IRReader/IRReader.h>
    #include <llvm/IR/DataLayout.h>
    #include <llvm/Support/FormattedStream.h>
    #include <llvm/Support/SourceMgr.h>
    #include <llvm/Support/MemoryBuffer.h>
    #include <llvm/Bitcode/ReaderWriter.h>
    #include <llvm/ADT/Triple.h>
    #include <llvm/Support/TargetRegistry.h>
    #include <llvm-c/Core.h>
#else
    #include <llvm/Module.h>
    #include <llvm/LLVMContext.h>
    #include <llvm/Support/IRReader.h>
#endif

#if defined(LLVM_37)
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
 
/* The file llvm/Target/TargetData.h was renamed to llvm/DataLayout.h in LLVM
 * 3.2, which itself appears to have been moved to llvm/IR/DataLayout.h in LLVM
 * 3.3.
 */
#if defined(LLVM_32)
    #include <llvm/DataLayout.h>
#elif !defined(LLVM_33) && !defined(LLVM_34) && !defined(LLVM_35) && !defined(LLVM_36) && !defined(LLVM_37)
    #ifndef _WIN32
        #include <llvm/Target/TargetData.h>
    #endif
#endif

#if defined(LLVM_36) || defined(LLVM_37)
    #include <llvm/ExecutionEngine/MCJIT.h>
#else
    #include <llvm/ExecutionEngine/JIT.h>
#endif

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    #include <llvm/IR/Verifier.h>
#else
    #include <llvm/Analysis/Verifier.h>
#endif

#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    #include <llvm/IR/LegacyPassNameParser.h>
    #include <llvm/Linker/Linker.h>
#else
    #include <llvm/Support/PassNameParser.h>
    #include <llvm/Linker.h>
#endif

#include <llvm/Support/Host.h>
#include <llvm/Support/ManagedStatic.h>

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    #include <llvm/IR/IRPrintingPasses.h>
    #define llvmcreatePrintModulePass(out) createPrintModulePass(out)
#else
    #include <llvm/Assembly/PrintModulePass.h>
    #define llvmcreatePrintModulePass(out) createPrintModulePass(&out)
#endif

#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/Support/Threading.h>

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
    #include "llvm/ExecutionEngine/ObjectCache.h"
#endif

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    #define OwningPtr std::unique_ptr
#endif

#include <llvm/Support/TargetSelect.h>

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    #include <llvm/Support/FileSystem.h>
    #define sysfs_binary_flag sys::fs::F_None
#elif defined(LLVM_34)
    #define sysfs_binary_flag sys::fs::F_Binary
#else
    #define sysfs_binary_flag raw_fd_ostream::F_Binary
#endif

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    #define GET_CPU_NAME llvm::sys::getHostCPUName().str()
#else
    #define GET_CPU_NAME llvm::sys::getHostCPUName()
#endif

#if defined(LLVM_36) || defined(LLVM_37)
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

#if defined(LLVM_34) || defined(LLVM_35)  || defined(LLVM_36) || defined(LLVM_37)
    #define MAX_OPT_LEVEL 5
#else 
    #define MAX_OPT_LEVEL 4
#endif

using namespace llvm;

// Factories instances management
int llvm_dsp_factory::gInstance = 0;
FactoryTableType llvm_dsp_factory::gFactoryTable;

// Global API access lock
TLockAble* gDSPFactoriesLock = 0;

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

static llvm_dsp_factory* checkDSPFactory(llvm_dsp_factory* factory, string& error_msg)
{   
    if (factory->initJIT(error_msg)) {
        return factory;
    } else {
        delete factory;
        return NULL;
    }
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

// ObjectCache & MCCJIT is not taken into account when compiled with Visual Studio for the resulting compiler doesn't work 
#if (defined(LLVM_34) || defined(LLVM_35)) && !defined(_MSC_VER)
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

#if defined(LLVM_36) || defined(LLVM_37)

// Workaround for iOS compiled LLVM 3.6 missing symbol
#if __IPHONE_OS_VERSION_MIN_REQUIRED >= 50000
void ObjectCache::anchor() {}
#endif

class FaustObjectCache : public ObjectCache {
    
private:
    
    string fMachineCode;
    
public:
    
    FaustObjectCache(const string& machine_code = "") : fMachineCode(machine_code)
    {}
    
    virtual ~FaustObjectCache()
    {}
    
    virtual void notifyObjectCompiled(const Module *M, MemoryBufferRef Obj)
    {
        fMachineCode = Obj.getBuffer().str();
    }
    
    virtual std::unique_ptr<MemoryBuffer> getObject(const Module* M)
    {
        return (fMachineCode == "") ? NULL : MemoryBuffer::getMemBuffer(StringRef(fMachineCode));
    }
    
    string getMachineCode() { return fMachineCode; }
    
};
#endif

#if defined(LLVM_35) || defined(LLVM_36)
// LLVM 3.5 has parseBitcodeFile(). Must emulate ParseBitcodeFile. -ag
static Module* ParseBitcodeFile(MEMORY_BUFFER Buffer,
                                LLVMContext& Context,
                                string* ErrMsg)
{
    using namespace llvm;
    ErrorOr<Module*> ModuleOrErr = parseBitcodeFile(Buffer, Context);
    if (std::error_code EC = ModuleOrErr.getError()) {
        if (ErrMsg) *ErrMsg = EC.message();
        return NULL;
    } else {
        return ModuleOrErr.get();
    }

}
#endif

#if defined(LLVM_37)
static Module* ParseBitcodeFile(MEMORY_BUFFER Buffer,
                                LLVMContext& Context,
                                string* ErrMsg)
{
    using namespace llvm;
    ErrorOr<std::unique_ptr<Module>> ModuleOrErr = parseBitcodeFile(Buffer, Context);
    if (std::error_code EC = ModuleOrErr.getError()) {
        if (ErrMsg) *ErrMsg = EC.message();
        return NULL;
    } else {
        return ModuleOrErr.get().get();
    }
}
#endif

void* llvm_dsp_factory::loadOptimize(const string& function)
{
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
    void* fun = (void*)fJIT->getFunctionAddress(function);
    if (fun) {
        return fun;
    } else {
        stringstream error;
        error << "loadOptimize failed for '" << function << "'";
        throw faustexception(error.str());
    }
#else
    llvm::Function* fun_ptr = fResult->fModule->getFunction(function);
    if (fun_ptr) {
        return fJIT->getPointerToFunction(fun_ptr);
    } else {
        stringstream error;
        error << "loadOptimize failed for '" << function << "'";
        throw faustexception(error.str());
    }
#endif
}

LLVMResult* llvm_dsp_factory::compileModule(int argc, const char* argv[], const char* input_name, const char* input, char* error_msg)
{
    int argc1 = argc + 3;
    const char* argv1[32];

    argv1[0] = "faust";
    argv1[1] = "-lang";
    //argv1[2] = "cllvm";
    argv1[2] = "llvm";
    for (int i = 0; i < argc; i++) {
        argv1[i+3] = argv[i];
    }
    
    argv1[argc1] = 0;  // NULL terminated argv

    return compile_faust_llvm(argc1, argv1, input_name, input, error_msg);
}

// Bitcode
string llvm_dsp_factory::writeDSPFactoryToBitcode()
{
    string res;
    raw_string_ostream out(res);
    WriteBitcodeToFile(fResult->fModule, out);
    out.flush();
    return base64_encode(res);
}

void llvm_dsp_factory::writeDSPFactoryToBitcodeFile(const string& bit_code_path)
{
    STREAM_ERROR err;
    raw_fd_ostream out(bit_code_path.c_str(), err, sysfs_binary_flag);
    WriteBitcodeToFile(fResult->fModule, out);
}

// IR
string llvm_dsp_factory::writeDSPFactoryToIR()
{
    string res;
    raw_string_ostream out(res);
    PASS_MANAGER PM;
    PM.add(llvmcreatePrintModulePass(out));
    PM.run(*fResult->fModule);
    out.flush();
    return res;
}

void llvm_dsp_factory::writeDSPFactoryToIRFile(const string& ir_code_path)
{
    STREAM_ERROR err;
    raw_fd_ostream out(ir_code_path.c_str(), err, sysfs_binary_flag);
    PASS_MANAGER PM;
    PM.add(llvmcreatePrintModulePass(out));
    PM.run(*fResult->fModule);
    out.flush();
}

bool llvm_dsp_factory::crossCompile(const std::string& target)
{
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
    delete fObjectCache;
    fObjectCache = new FaustObjectCache();
    setTarget(target);
    string error;
    return initJIT(error);
#else
    return false;
#endif
}

std::string llvm_dsp_factory::writeDSPFactoryToMachineAux(const std::string& target)
{ 
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
    if (target == "" || target == getTarget()) {
        return fObjectCache->getMachineCode();
    } else {
        string old_target = getTarget();
        if (crossCompile(target)) {     // Recompilation is required
            string machine_code = fObjectCache->getMachineCode();
            crossCompile(old_target);   // Restore old target
            return machine_code;
        } else {
            return "";
        }
    }
#else
    return "";
#endif
}

std::string llvm_dsp_factory::writeDSPFactoryToMachine(const std::string& target)
{ 
    return base64_encode(writeDSPFactoryToMachineAux(target));
}

void llvm_dsp_factory::writeDSPFactoryToMachineFile(const std::string& machine_code_path, const std::string& target)
{
    STREAM_ERROR err;
    raw_fd_ostream out(machine_code_path.c_str(), err, sysfs_binary_flag);
    out << writeDSPFactoryToMachineAux(target); 
    out.flush();
}

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
llvm_dsp_factory::llvm_dsp_factory(const string& sha_key, const string& machine_code, const string& target)
{
    init("MachineDSP", "");
    fSHAKey = sha_key;
    fTarget = (target == "") ? fTarget = (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME) : target;
   
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
    init("BitcodeDSP", "");
    fOptLevel = ((opt_level == -1) || (opt_level > MAX_OPT_LEVEL)) ? MAX_OPT_LEVEL : opt_level;  // Normalize opt_level
    fSHAKey = sha_key;
    fTarget = (target == "") ? fTarget = (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME) : target;
    fResult = static_cast<LLVMResult*>(calloc(1, sizeof(LLVMResult)));
    fResult->fModule = module;
    fResult->fContext = context;
    
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
    fObjectCache = NULL;
#endif
}

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
void llvm_dsp_factory::LLVMFatalErrorHandler(const char* reason)
{
    throw faustexception(reason);
}
#endif

llvm_dsp_factory::llvm_dsp_factory(const string& sha_key, 
                                    int argc, const char* argv[], 
                                    const string& name_app,
                                    const string& dsp_content, 
                                    const string& expanded_dsp_content, 
                                    const string& target, 
                                    string& error_msg, int opt_level)
{

    
    if (llvm_dsp_factory::gInstance++ == 0) {
        
        // Install a LLVM error handler
    #if defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
        LLVMInstallFatalErrorHandler(llvm_dsp_factory::LLVMFatalErrorHandler);
    #endif
    #if (!defined(LLVM_35) && !defined(LLVM_36) && !defined(LLVM_37)) // In LLVM 3.5 this is gone.
        if (!llvm_start_multithreaded()) {
            printf("llvm_start_multithreaded error...\n");
        }
    #endif
    }
    init("SourceDSP", name_app);
    
    fOptLevel = ((opt_level == -1) || (opt_level > MAX_OPT_LEVEL)) ? MAX_OPT_LEVEL : opt_level;  // Normalize opt_level
    fExpandedDSP = expanded_dsp_content;
    fSHAKey = sha_key;
    fTarget = (target == "") ? fTarget = (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME) : target;  
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
    fObjectCache = NULL;
#endif
    
    char error_msg_aux[512];
    fClassName = getParam(argc, argv, "-cn", "mydsp");
    fIsDouble = isParam(argc, argv, "-double");
    fResult = compileModule(argc, argv, name_app.c_str(), dsp_content.c_str(), error_msg_aux);
    error_msg = error_msg_aux;
}

void llvm_dsp_factory::init(const string& type_name, const string& dsp_name)
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
    fDSPName = dsp_name;
    fTypeName = type_name;
    fExpandedDSP = "";
    fOptLevel = 0;
    fTarget = "";
}

llvm_dsp_aux* llvm_dsp_factory::createDSPInstance()
{
    assert(fResult->fModule);
    assert(fJIT);
    return new llvm_dsp_aux(this, fNew());
}

int llvm_dsp_factory::getOptlevel()
{
    // TODO LLVM_36
    /*
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
    */
    return -1;
}

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
/// AddOptimizationPasses - This routine adds optimization passes
/// based on selected optimization level, OptLevel. This routine
/// duplicates llvm-gcc behaviour.
///
/// OptLevel - Optimization Level
static void AddOptimizationPasses(PassManagerBase &MPM, FUNCTION_PASS_MANAGER &FPM,
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
    InitializeAllAsmPrinters();
    InitializeAllAsmParsers();
      
    // For host target support
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    
    // For ObjectCache to work...
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
    LLVMLinkInMCJIT();
#endif
    
    // Restoring from machine code
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
    if (fObjectCache) {
    
        // JIT
    #if defined(LLVM_36) || defined(LLVM_37)
        EngineBuilder builder(unique_ptr<Module>(fResult->fModule));
    #else
        EngineBuilder builder(fResult->fModule);
    #endif
        builder.setEngineKind(EngineKind::JIT);
    #if !defined(LLVM_36) && !defined(LLVM_37)
        builder.setUseMCJIT(true);
    #endif
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
       
    #if defined(LLVM_36) || defined(LLVM_37)
        EngineBuilder builder(unique_ptr<Module>(fResult->fModule));
    #else
        EngineBuilder builder(fResult->fModule);
    #endif
        builder.setOptLevel(CodeGenOpt::Aggressive);
        builder.setEngineKind(EngineKind::JIT);
        builder.setCodeModel(CodeModel::JITDefault);
        
        std::string buider_error;
        builder.setErrorStr(&buider_error);
        
        // MCJIT does not work correctly (incorrect float numbers ?) when used with dynamic libLLVM
    #if (defined(LLVM_34) || defined(LLVM_35)) && !defined(_MSC_VER)
        builder.setUseMCJIT(true);
    #elif !defined(LLVM_36) && !defined(LLVM_37)
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
        fResult->fModule->setTargetTriple(triple + target_suffix);
    #if defined(LLVM_34)
        builder.setMCPU((cpu == "") ? llvm::sys::getHostCPUName() : cpu);
    #else
        builder.setMCPU((cpu == "") ? llvm::sys::getHostCPUName() : StringRef(cpu));
    #endif
        
        TargetOptions targetOptions;
        //targetOptions.NoFramePointerElim = true;
        //targetOptions.LessPreciseFPMADOption = true;
        /*
        targetOptions.UnsafeFPMath = true;
        targetOptions.NoInfsFPMath = true;
        targetOptions.NoNaNsFPMath = true;
        */
        
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
            FUNCTION_PASS_MANAGER fpm(fResult->fModule);
            
        #if defined(LLVM_37) // Code taken from opt.cpp
            TargetLibraryInfoImpl TLII(Triple(fResult->fModule->getTargetTriple()));
            pm.add(new TargetLibraryInfoWrapperPass(TLII));
        #else
            // Add an appropriate TargetLibraryInfo pass for the module's triple.
            TargetLibraryInfo* tli = new TargetLibraryInfo(Triple(fResult->fModule->getTargetTriple()));
            pm.add(tli);
        #endif
            
        #if defined(LLVM_37) // Code taken from opt.cpp
            fResult->fModule->setDataLayout(*fJIT->getDataLayout());
        #elif defined(LLVM_35) || defined(LLVM_36)
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
        #if defined(LLVM_37) // Code taken from opt.cpp
            pm.add(createTargetTransformInfoWrapperPass(tm->getTargetIRAnalysis()));
        #else
            tm->addAnalysisPasses(pm);
        #endif
          
            if (fOptLevel > 0) {
                AddOptimizationPasses(pm, fpm, fOptLevel, 0);
            }
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM1") != string::npos)) {
                TargetRegistry::printRegisteredTargetsForVersion();
                fResult->fModule->dump();
            }
           
            fpm.doInitialization();
            for (Module::iterator F = fResult->fModule->begin(), E = fResult->fModule->end(); F != E; ++F) {
                fpm.run(*F);
            }
            fpm.doFinalization();
            
            pm.add(createVerifierPass());
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM4") != string::npos)) {
            #if defined(LLVM_37)
                // TODO
            #else
                tm->addPassesToEmitFile(pm, fouts(), TargetMachine::CGFT_AssemblyFile, true);
            #endif
            }
            
            // Now that we have all of the passes ready, run them.
            pm.run(*fResult->fModule);
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM2") != string::npos)) {
                fResult->fModule->dump();
            }
        }
        
    #if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
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
        fBuildUserInterface = (buildUserInterfaceFun)loadOptimize("buildUserInterface" + fClassName);
        fInit = (initFun)loadOptimize("init" + fClassName);
        fCompute = (computeFun)loadOptimize("compute" + fClassName);
        fMetadata = (metadataFun)loadOptimize("metadata" + fClassName);
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
    
    fResult->fModule->setTargetTriple(fTarget);
   
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
        PASS_MANAGER pm;
        FUNCTION_PASS_MANAGER fpm(fResult->fModule);
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
        fNew = (newDspFun)loadOptimize("new" + fClassName);
        fDelete = (deleteDspFun)loadOptimize("delete" + fClassName);
        fGetNumInputs = (getNumInputsFun)loadOptimize("getNumInputs" + fClassName);
        fGetNumOutputs = (getNumOutputsFun)loadOptimize("getNumOutputs" + fClassName);
        fBuildUserInterface = (buildUserInterfaceFun)loadOptimize("buildUserInterface" + fClassName);
        fInit = (initFun)loadOptimize("init" + fClassName);
        fCompute = (computeFun)loadOptimize("compute" + fClassName);
        fMetadata = (metadataFun)loadOptimize("metadata" + fClassName);
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
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
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
    #if  (!defined(LLVM_35)) && (!defined(LLVM_36)) && (!defined(LLVM_37)) // In LLVM 3.5 this is gone.
        llvm_stop_multithreaded();
    #endif
    #if defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
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

// Instance 

llvm_dsp_aux::llvm_dsp_aux(llvm_dsp_factory* factory, llvm_dsp_imp* dsp)
    :fDSPFactory(factory), fDSP(dsp)
{
    assert(fDSPFactory);
    assert(fDSP);
}
        
llvm_dsp_aux::~llvm_dsp_aux()
{   
    TLock lock(gDSPFactoriesLock);
 
    // Remove 'this' from its factory
    FactoryTableIt it = llvm_dsp_factory::gFactoryTable.find(fDSPFactory);
    assert(it != llvm_dsp_factory::gFactoryTable.end());
    (*it).second.remove(this);
    
    if (fDSP) {
        fDSPFactory->fDelete(fDSP);
    }
}

llvm_dsp_aux* llvm_dsp_aux::copy()
{
    return fDSPFactory->createDSPInstance();
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
    buildUIGlue(&glue, ui_interface, fDSPFactory->fIsDouble);
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

// Public C++ API

EXPORT std::string getLibFaustVersion() { return FAUSTVERSION; }

EXPORT Module* load_single_module(const string filename, LLVMContext* context)
{
    SMDiagnostic err;
#if defined(LLVM_36) || defined(LLVM_37)
    Module* module = parseIRFile(filename, err, *context).get();
#else
    Module* module = ParseIRFile(filename, err, *context);
#endif
    
    if (module) {
        return module;
    } else {
        err.print("ParseIRFile failed :", errs());
        return NULL;
    }
}

EXPORT bool link_modules(Module* dst, Module* src, char* error_msg)
{
    bool res = false;
    
#if defined(LLVM_36) || defined(LLVM_37)
    if (Linker::LinkModules(dst, src)) {
        snprintf(error_msg, 256, "cannot link module");
#else
    string err;
    if (Linker::LinkModules(dst, src, Linker::DestroySource, &err)) {
        snprintf(error_msg, 256, "cannot link module : %s", err.c_str());
#endif
    } else {
        res = true;
    }
        
    delete src;
    return res;
}

EXPORT bool startMTDSPFactories()
{
    try {
        if (!gDSPFactoriesLock) {
            gDSPFactoriesLock = new TLockAble();
        }
        return true;
    } catch (...) {
        return false;
    }
}

EXPORT void stopMTDSPFactories()
{
    delete gDSPFactoriesLock;
    gDSPFactoriesLock = 0;
}

EXPORT string path_to_content(const string& path)
{
    ifstream file(path.c_str(), ifstream::binary);
    
    file.seekg(0, file.end);
    int size = file.tellg();
    file.seekg(0, file.beg);
    
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
    TLock lock(gDSPFactoriesLock);
    
    const char** argv1 = (const char**)alloca((argc + 1) * sizeof(char*));
    int argc1 = 0;
 
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
        
    string expanded_dsp_content;
    string sha_key;
    
    if ((expanded_dsp_content = expandDSPFromString(name_app, dsp_content, argc1, argv1, sha_key, error_msg)) == "") {
        return NULL; 
    } else {

        FactoryTableIt it;
        llvm_dsp_factory* factory = 0;
        if (getFactory(sha_key, it)) {
            Sllvm_dsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else if ((factory = checkDSPFactory(new llvm_dsp_factory(sha_key, argc1, argv1, name_app, dsp_content, expanded_dsp_content, target, error_msg, opt_level), error_msg)) != 0) {
            llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
            return factory;
        } else {
            return NULL;
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
    } else if ((factory = checkDSPFactory(new llvm_dsp_factory(sha_key, argc, argv, name_app, dsp_content, target, error_msg, opt_level), error_msg)) != 0) {
        llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
        return factory;
    } else {
        return NULL;
    }*/
}

EXPORT llvm_dsp_factory* getDSPFactoryFromSHAKey(const string& sha_key)
{
    TLock lock(gDSPFactoriesLock);
    
    FactoryTableIt it;
    
    if (getFactory(sha_key, it)) {
        Sllvm_dsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        return NULL;
    }
}

EXPORT vector<string> getAllDSPFactories()
{
    TLock lock(gDSPFactoriesLock);
    
    FactoryTableIt it;
    vector<string> sha_key_list;
    
    for (it = llvm_dsp_factory::gFactoryTable.begin(); it != llvm_dsp_factory::gFactoryTable.end(); it++) {
        sha_key_list.push_back((*it).first->getSHAKey());
    }
    
    return sha_key_list;
}

EXPORT bool deleteDSPFactory(llvm_dsp_factory* factory) 
{   
    TLock lock(gDSPFactoriesLock);
    
    FactoryTableIt it;
    if ((it = llvm_dsp_factory::gFactoryTable.find(factory)) != llvm_dsp_factory::gFactoryTable.end()) {
        Sllvm_dsp_factory sfactory = (*it).first;
        list<llvm_dsp_aux*> dsp_list = (*it).second;
        if (sfactory->refs() == 2) { // Local stack pointer + the one in gFactoryTable...
            // Possibly delete remaining DSP
            list<llvm_dsp_aux*>::iterator it;
            for (it = dsp_list.begin(); it != dsp_list.end(); it++) { delete (*it); }
            // Last use, remove from the global table, pointer will be deleted
            llvm_dsp_factory::gFactoryTable.erase(factory);
            return true;
        } else {
            sfactory->removeReference();
        }
    }
    
    return false;
}

EXPORT std::string llvm_dsp_factory::getName()
{
    struct MyMeta : public Meta
    {
        string name;
        virtual void declare(const char* key, const char* value)
        {
            if (strcmp(key, "name") == 0) {
                name = value;
            }
        }
    };
    
    if (fDSPName == "") {
        MyMeta metadata;
        metadataDSPFactory(&metadata);
        return fTypeName + "_" + metadata.name;
    } else {
        return fTypeName + "_" + fDSPName;
    }
}

EXPORT std::string llvm_dsp_factory::getSHAKey() { return fSHAKey; }

EXPORT std::string llvm_dsp_factory::getDSPCode() { return fExpandedDSP; }

EXPORT std::string llvm_dsp_factory::getTarget() { return fTarget; }

EXPORT std::string getDSPMachineTarget()
{
    return (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME);
}

EXPORT std::vector<std::string> getDSPFactoryLibraryList(llvm_dsp_factory* factory)
{
    TLock lock(gDSPFactoriesLock);
    
    return factory->getDSPFactoryLibraryList();
}

EXPORT void deleteAllDSPFactories()
{
    TLock lock(gDSPFactoriesLock);
    
    FactoryTableIt it;
    for (it = llvm_dsp_factory::gFactoryTable.begin(); it != llvm_dsp_factory::gFactoryTable.end(); it++) {
        // Decrement counter up to one...
        while (((*it).first)->refs() > 1) { ((*it).first)->removeReference(); }
    }
    // Then clear the table thus finally deleting all ref = 1 smart pointers
    llvm_dsp_factory::gFactoryTable.clear();
}
    
// Bitcode <==> string
static llvm_dsp_factory* readDSPFactoryFromBitcodeAux(MEMORY_BUFFER buffer, const string& target, int opt_level)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
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
        if (module && ((factory = checkDSPFactory(new llvm_dsp_factory(sha_key, module, context, target, opt_level), error_msg)) != 0)) {
            llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
            return factory;
        } else {
            printf("readDSPFactoryFromBitcode failed : %s\n", error_msg.c_str());
            return NULL;
        }
    }
}

EXPORT llvm_dsp_factory* readDSPFactoryFromBitcode(const string& bit_code, const string& target, int opt_level)
{
    TLock lock(gDSPFactoriesLock);
    
    return readDSPFactoryFromBitcodeAux(MEMORY_BUFFER_CREATE(StringRef(base64_decode(bit_code))), target, opt_level);
}

EXPORT string writeDSPFactoryToBitcode(llvm_dsp_factory* factory)
{
    TLock lock(gDSPFactoriesLock);
    
    return (factory) ? factory->writeDSPFactoryToBitcode() : "";
}

// Bitcode <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const string& bit_code_path, const string& target, int opt_level)
{
    TLock lock(gDSPFactoriesLock);
  
#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(bit_code_path);
    if (std::error_code ec = buffer.getError()) {
        printf("readDSPFactoryFromBitcodeFile failed : %s\n", ec.message().c_str());
        return NULL;
    } else {
        return readDSPFactoryFromBitcodeAux(MEMORY_BUFFER_GET_REF(buffer), target, opt_level);
     }
#else
    OwningPtr<MemoryBuffer> buffer;
    if (llvm::error_code ec = MemoryBuffer::getFileOrSTDIN(bit_code_path.c_str(), buffer)) {
        printf("readDSPFactoryFromBitcodeFile failed : %s\n", ec.message().c_str());
        return NULL;
    } else {
        return readDSPFactoryFromBitcodeAux(buffer.get(), target, opt_level);
    }
#endif
}

EXPORT void writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const string& bit_code_path)
{
    TLock lock(gDSPFactoriesLock);
    
    if (factory) {
        factory->writeDSPFactoryToBitcodeFile(bit_code_path);
    }
}

// IR <==> string

static llvm_dsp_factory* readDSPFactoryFromIRAux(MEMORY_BUFFER buffer, const string& target, int opt_level)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
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
    #if defined(LLVM_36) || defined(LLVM_37)
        Module* module = parseIR(buffer, err, *context).get();  // ParseIR takes ownership of the given buffer, so don't delete it
    #else
        Module* module = ParseIR(buffer, err, *context);        // ParseIR takes ownership of the given buffer, so don't delete it
    #endif
        setlocale(LC_ALL, tmp_local);
        llvm_dsp_factory* factory = 0;
        string error_msg;
        if (module && ((factory = checkDSPFactory(new llvm_dsp_factory(sha_key, module, context, target, opt_level), error_msg)) != 0)) {
            llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
            return factory;
        } else {
            err.print("readDSPFactoryFromIRAux failed :", errs());
            return NULL;
        }
    }
}

EXPORT llvm_dsp_factory* readDSPFactoryFromIR(const string& ir_code, const string& target, int opt_level)
{
    TLock lock(gDSPFactoriesLock);
    
    return readDSPFactoryFromIRAux(MEMORY_BUFFER_CREATE(StringRef(ir_code)), target, opt_level);
}

EXPORT string writeDSPFactoryToIR(llvm_dsp_factory* factory)
{
    TLock lock(gDSPFactoriesLock);
    
    return (factory) ? factory->writeDSPFactoryToIR() : "";
}

// IR <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromIRFile(const string& ir_code_path, const string& target, int opt_level)
{
    TLock lock(gDSPFactoriesLock);
 
 #if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(ir_code_path);
    if (std::error_code ec = buffer.getError()) {
        printf("readDSPFactoryFromIRFile failed : %s\n", ec.message().c_str());
        return NULL;
    } else {
        return readDSPFactoryFromIRAux(MEMORY_BUFFER_GET_REF(buffer), target, opt_level);
    }
#else
    OwningPtr<MemoryBuffer> buffer;
    if (llvm::error_code ec = MemoryBuffer::getFileOrSTDIN(ir_code_path.c_str(), buffer)) {
        printf("readDSPFactoryFromIRFile failed : %s\n", ec.message().c_str());
        return NULL;
    } else {
        return readDSPFactoryFromIRAux(buffer.get(), target, opt_level);
    }
#endif
}

EXPORT void writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const string& ir_code_path)
{
    TLock lock(gDSPFactoriesLock);
    
    if (factory) {
        factory->writeDSPFactoryToIRFile(ir_code_path);
    }
}

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
    
static llvm_dsp_factory* readDSPFactoryFromMachineAux(MEMORY_BUFFER buffer, const std::string& target)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    FactoryTableIt it;
    
    if (getFactory(sha_key, it)) {
        Sllvm_dsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        string error_msg;
        try {
            llvm_dsp_factory* factory = checkDSPFactory(new llvm_dsp_factory(sha_key, MEMORY_BUFFER_GET(buffer).str(), target), error_msg);
            llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
            return factory;
        } catch (faustexception& e) {
            e.PrintMessage();
            return NULL;
        }
    }
}

// machine <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code, const std::string& target)
{
    TLock lock(gDSPFactoriesLock);
    
    return readDSPFactoryFromMachineAux(MEMORY_BUFFER_CREATE(StringRef(base64_decode(machine_code))), target);
}

EXPORT std::string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const std::string& target)
{
    TLock lock(gDSPFactoriesLock);
    
    return factory->writeDSPFactoryToMachine(target);
}

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path,const std::string& target)
{
    TLock lock(gDSPFactoriesLock);
    
#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(machine_code_path);
    if (std::error_code ec = buffer.getError()) {
        printf("readDSPFactoryFromMachineFile failed : %s\n", ec.message().c_str());
        return NULL;
    } else {
        return readDSPFactoryFromMachineAux(MEMORY_BUFFER_GET_REF(buffer), target);
     }
#else
    OwningPtr<MemoryBuffer> buffer;
    if (llvm::error_code ec = MemoryBuffer::getFileOrSTDIN(machine_code_path.c_str(), buffer)) {
        printf("readDSPFactoryFromMachineFile failed : %s\n", ec.message().c_str());
        return NULL;
    } else {
        return readDSPFactoryFromMachineAux(buffer.get(), target);
    }
#endif
}

EXPORT void writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const string& machine_code_path, const std::string& target)
{
    TLock lock(gDSPFactoriesLock);
    
    if (factory) {
        factory->writeDSPFactoryToMachineFile(machine_code_path, target);
    }
}

#else

EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code)
{
    printf("readDSPFactoryFromMachine not implemented\n");
    return NULL;
}

EXPORT std::string writeDSPFactoryToMachine(llvm_dsp_factory* factory)
{
    printf("writeDSPFactoryToMachine not implemented\n");
    return "";
}

EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path)
{
    printf("readDSPFactoryFromMachineFile not implemented\n");
    return NULL;
}

EXPORT void writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const string& machine_code_path)
{
    printf("writeDSPFactoryToMachineFile not implemented\n");
}

#endif

EXPORT void metadataDSPFactory(llvm_dsp_factory* factory, Meta* m)
{
    TLock lock(gDSPFactoriesLock);
    
    if (factory && m) {
        factory->metadataDSPFactory(m);
    }
}

// Instance

EXPORT llvm_dsp* createDSPInstance(llvm_dsp_factory* factory)
{  
    TLock lock(gDSPFactoriesLock);
    
    FactoryTableIt it;
    if ((it = llvm_dsp_factory::gFactoryTable.find(factory)) != llvm_dsp_factory::gFactoryTable.end()) {
        llvm_dsp_aux* instance = factory->createDSPInstance();
        (*it).second.push_back(instance);
        return reinterpret_cast<llvm_dsp*>(instance);
    } else {
        return NULL;
    }
}

EXPORT void deleteDSPInstance(llvm_dsp* dsp) 
{
    if (dsp) {
        delete (reinterpret_cast<llvm_dsp_aux*>(dsp));
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

EXPORT llvm_dsp* llvm_dsp::copy()
{
    return reinterpret_cast<llvm_dsp*>(reinterpret_cast<llvm_dsp_aux*>(this)->copy());
}

// Public C interface : lock management is done by called C++ API

EXPORT llvm_dsp_factory* getCDSPFactoryFromSHAKey(const char* sha_key)
{
    return getDSPFactoryFromSHAKey(sha_key);
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
        sha_key_list2[i] = strdup(sha_key_list1[i].c_str());
    }
    
    // Last element is NULL
    sha_key_list2[i] = NULL;
    return sha_key_list2;
}

EXPORT bool startMTCDSPFactories() { return startMTDSPFactories(); }

EXPORT void stopMTCDSPFactories() { stopMTDSPFactories(); }

EXPORT bool deleteCDSPFactory(llvm_dsp_factory* factory)
{
    return deleteDSPFactory(factory);
}

EXPORT char* getCName(llvm_dsp_factory* factory)
{
    if (factory) {
        string name = factory->getName();
        return strdup(name.c_str());
    } else {
        return NULL;
    }
}

EXPORT char* getCSHAKey(llvm_dsp_factory* factory)
{
    if (factory) {
        string shakey = factory->getSHAKey();
        return strdup(shakey.c_str());
    } else {
        return NULL;
    }
}

EXPORT char* getCDSPCode(llvm_dsp_factory* factory)
{
    if (factory) {
        string dspcode = factory->getDSPCode();
        return strdup(dspcode.c_str()); 
    } else {
        return NULL;
    }
}

EXPORT char* getCTarget(llvm_dsp_factory* factory)
{
    if (factory) {
        string target = factory->getTarget();
        return strdup(target.c_str());
    } else {
        return NULL;
    }
}

EXPORT char* getCDSPMachineTarget()
{
    string dspmachinetarget = getDSPMachineTarget();
    return strdup(dspmachinetarget.c_str());
}

EXPORT const char** getCDSPFactoryLibraryList(llvm_dsp_factory* factory)
{
    if (factory) {
        vector<string> library_list1 = factory->getDSPFactoryLibraryList();
        const char** library_list2 = (const char**)malloc(sizeof(char*) * (library_list1.size() + 1));
        
        size_t i;
        for (i = 0; i < library_list1.size(); i++) {
            library_list2[i] = strdup(library_list1[i].c_str());
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

EXPORT char* writeCDSPFactoryToBitcode(llvm_dsp_factory* factory)
{
    return (factory) ? strdup(writeDSPFactoryToBitcode(factory).c_str()) : NULL;
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

EXPORT char* writeCDSPFactoryToIR(llvm_dsp_factory* factory)
{
    return (factory) ? strdup(writeDSPFactoryToIR(factory).c_str()) : NULL;
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

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37)) && !defined(_MSC_VER)
EXPORT llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code, const char* target)
{
    return readDSPFactoryFromMachine(machine_code, target);
}

EXPORT char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const char* target)
{
    return (factory) ? strdup(writeDSPFactoryToMachine(factory, target).c_str()) : NULL;
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path, const char* target)
{
    return readDSPFactoryFromMachineFile(machine_code_path, target);
}

EXPORT void writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path, const char* target)
{
    if (factory) {
        writeDSPFactoryToMachineFile(factory, machine_code_path, target);
    }
}
#else
EXPORT llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code)
{
    return NULL;
}

EXPORT char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const std::string& target)
{
    return NULL;
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path)
{
    return NULL;
}

EXPORT void writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path, const std::string& target)
{}
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

EXPORT llvm_dsp* copyCDSPInstance(llvm_dsp* dsp)
{
    return (dsp) ? reinterpret_cast<llvm_dsp*>(reinterpret_cast<llvm_dsp_aux*>(dsp)->copy()) : 0;
}

EXPORT llvm_dsp* createCDSPInstance(llvm_dsp_factory* factory)
{
    return (factory) ? reinterpret_cast<llvm_dsp*>(factory->createDSPInstance()) : 0;
 }

EXPORT void deleteCDSPInstance(llvm_dsp* dsp)
{
    if (dsp) {
        delete (reinterpret_cast<llvm_dsp_aux*>(dsp)); 
    }
}

EXPORT void generateCSHA1(const char* data, char* sha_key)
{
    string res = generateSHA1(data);
    strncpy(sha_key, res.c_str(), 64);
}

#endif // LLVM_BUILD

