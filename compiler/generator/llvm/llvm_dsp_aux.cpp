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
#include "llvm_dsp_aux.hh"
#include "faust/gui/CGlue.h"
#include "dsp_aux.hh"
#include "timing.hh"
#include "exception.hh"
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

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
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

#if defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
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

#if defined(LLVM_40) || defined(LLVM_50)
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
#elif !defined(LLVM_33) && !defined(LLVM_34) && !defined(LLVM_35) && !defined(LLVM_36) && !defined(LLVM_37) && !defined(LLVM_38) && !defined(LLVM_39) && !defined(LLVM_40) && !defined(LLVM_50)
    #ifndef _WIN32
    #include <llvm/Target/TargetData.h>
    #endif
#endif

#if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
    #include <llvm/ExecutionEngine/MCJIT.h>
    #include <llvm/ExecutionEngine/ObjectCache.h>
#else
    #include <llvm/ExecutionEngine/JIT.h>
#endif

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
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

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
    #include "llvm/ExecutionEngine/ObjectCache.h"
#endif

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
    #define sysfs_binary_flag sys::fs::F_None
#elif defined(LLVM_34)
    #define sysfs_binary_flag sys::fs::F_Binary
#else
    #define sysfs_binary_flag raw_fd_ostream::F_Binary
#endif

#if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
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

#if defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
    #define ModulePTR std::unique_ptr<Module>
    #define MovePTR(ptr) std::move(ptr)
#else
    #define ModulePTR Module*
    #define MovePTR(ptr) ptr
#endif

using namespace llvm;

// Factories instances management
int llvm_dsp_factory_aux::gInstance = 0;

typedef class faust_smartptr<llvm_dsp_factory> SDsp_factory;
static dsp_factory_table<SDsp_factory> gLLVMFactoryTable;

// Global API access lock
static TLockAble* gDSPFactoriesLock = 0;

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

static void DUMP(Module* module)
{
    string res;
    raw_string_ostream out_str(res);
    out_str << *module;
    std::cout << out_str.str();
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

#if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)

/*
static std::string getFeaturesStr()
{
    SubtargetFeatures Features;
    
    // If user asked for the 'native' CPU, we need to autodetect features.
    // This is necessary for x86 where the CPU might not support all the
    // features the autodetected CPU name lists in the target. For example,
    // not all Sandybridge processors support AVX.
    StringMap<bool> HostFeatures;
    if (sys::getHostCPUFeatures(HostFeatures)) {
        for (auto &F : HostFeatures) {
            Features.AddFeature(F.first(), F.second);
        }
    }
    
    return Features.getString();
}
*/

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
        
        virtual unique_ptr<MemoryBuffer> getObject(const Module* M)
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
    if (error_code EC = ModuleOrErr.getError()) {
        if (ErrMsg) *ErrMsg = EC.message();
        return nullptr;
    } else {
        return ModuleOrErr.get();
    }

}
#endif

#if defined(LLVM_40) || defined(LLVM_50)

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

void* llvm_dsp_factory_aux::loadOptimize(const string& function)
{
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
    void* fun = (void*)fJIT->getFunctionAddress(function);
    if (fun) {
        return fun;
    }
#else
    llvm::Function* fun_ptr = fModule->getFunction(function);
    if (fun_ptr) {
        return fJIT->getPointerToFunction(fun_ptr);
    }
#endif
    
    stringstream error;
    error << "loadOptimize failed for '" << function << "'";
    throw faustexception(error.str());
}

// Bitcode
string llvm_dsp_factory_aux::writeDSPFactoryToBitcode()
{
    string res;
    raw_string_ostream out(res);
    WriteBitcodeToFile(fModule, out);
    out.flush();
    return base64_encode(res);
}

void llvm_dsp_factory_aux::writeDSPFactoryToBitcodeFile(const string& bit_code_path)
{
    STREAM_ERROR err;
    raw_fd_ostream out(bit_code_path.c_str(), err, sysfs_binary_flag);
    WriteBitcodeToFile(fModule, out);
}

// IR
string llvm_dsp_factory_aux::writeDSPFactoryToIR()
{
    string res;
    raw_string_ostream out(res);
    PASS_MANAGER PM;
    PM.add(llvmcreatePrintModulePass(out));
    PM.run(*fModule);
    out.flush();
    return res;
}

void llvm_dsp_factory_aux::writeDSPFactoryToIRFile(const string& ir_code_path)
{
    STREAM_ERROR err;
    raw_fd_ostream out(ir_code_path.c_str(), err, sysfs_binary_flag);
    PASS_MANAGER PM;
    PM.add(llvmcreatePrintModulePass(out));
    PM.run(*fModule);
    out.flush();
}

bool llvm_dsp_factory_aux::crossCompile(const string& target)
{
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
    delete fObjectCache;
    fObjectCache = new FaustObjectCache();
    setTarget(target);
    string error;
    return initJIT(error);
#else
    return false;
#endif
}

string llvm_dsp_factory_aux::writeDSPFactoryToMachineAux(const string& target)
{ 
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
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

string llvm_dsp_factory_aux::writeDSPFactoryToMachine(const string& target)
{ 
    return base64_encode(writeDSPFactoryToMachineAux(target));
}

void llvm_dsp_factory_aux::writeDSPFactoryToMachineFile(const string& machine_code_path, const string& target)
{
    STREAM_ERROR err;
    raw_fd_ostream out(machine_code_path.c_str(), err, sysfs_binary_flag);
    out << writeDSPFactoryToMachineAux(target); 
    out.flush();
}

void llvm_dsp_factory_aux::startLLVMLibrary()
{
    if (llvm_dsp_factory_aux::gInstance++ == 0) {
        // Install a LLVM error handler
    #if defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
        LLVMInstallFatalErrorHandler(llvm_dsp_factory_aux::LLVMFatalErrorHandler);
    #endif
    #if (!defined(LLVM_35) && !defined(LLVM_36) && !defined(LLVM_37) && !defined(LLVM_38) && !defined(LLVM_39) && !defined(LLVM_40) && !defined(LLVM_50)) // In LLVM 3.5 this is gone.
        if (!llvm_start_multithreaded()) {
            std::cerr << "llvm_start_multithreaded error...\n";
        }
    #endif
    }
}

void llvm_dsp_factory_aux::stopLLVMLibrary()
{
    if (--llvm_dsp_factory_aux::gInstance == 0) {
    #if  (!defined(LLVM_35)) && (!defined(LLVM_36)) && (!defined(LLVM_37)) && (!defined(LLVM_38)) && (!defined(LLVM_39)) && (!defined(LLVM_40)) && (!defined(LLVM_50)) // In LLVM 3.5 this is gone.
        llvm_stop_multithreaded();
    #endif
    #if defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
        LLVMResetFatalErrorHandler();
    #endif
    }
}

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
llvm_dsp_factory_aux::llvm_dsp_factory_aux(const string& sha_key, const string& machine_code, const string& target)
    :dsp_factory_imp("MachineDSP", sha_key, "")
{
    startLLVMLibrary();
    
    init("MachineDSP", "");
    fSHAKey = sha_key;
    fTarget = (target == "") ? fTarget = (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME) : target;
   
    // Restoring the cache
    fObjectCache = new FaustObjectCache(machine_code);
    
    // Creates module and context
    fContext = new LLVMContext();
    fModule = new Module(string(LLVM_BACKEND_NAME) + ", v" + string(FAUSTVERSION), *fContext);
}
#endif

llvm_dsp_factory_aux::llvm_dsp_factory_aux(const string& sha_key,
                                           const std::vector<std::string>& pathname_list,
                                           Module* module,
                                           LLVMContext* context,
                                           const string& target,
                                           int opt_level)
    :dsp_factory_imp("BitcodeDSP", sha_key, "", pathname_list)
{
    startLLVMLibrary();
     
    init("BitcodeDSP", "");
    fSHAKey = sha_key;
    fTarget = (target == "") ? fTarget = (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME) : target;
    setOptlevel(opt_level);
    
    fModule = module;
    fContext = context;
    
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
    fObjectCache = nullptr;
#endif
}

llvm_dsp_factory_aux::~llvm_dsp_factory_aux()
{
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
    delete fObjectCache;
#endif
    if (fJIT) {
        fJIT->runStaticConstructorsDestructors(true);
        // fModule is kept and deleted by fJIT
        delete fJIT;
    }
    delete fContext;
    stopLLVMLibrary();
}

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
void llvm_dsp_factory_aux::LLVMFatalErrorHandler(const char* reason)
{
    throw faustexception(reason);
}
#endif

void llvm_dsp_factory_aux::init(const string& type_name, const string& dsp_name)
{
    fJIT = 0;
    fNew = 0;
    fDelete = 0;
    fGetNumInputs = 0;
    fGetNumOutputs = 0;
    fGetSize = 0;
    fBuildUserInterface = 0;
    fInit = 0;
    fInstanceInit = 0;
    fInstanceConstants = 0;
    fInstanceResetUI = 0;
    fInstanceClear = 0;
    fCompute = 0;
    fClassName = "mydsp";
    fName = dsp_name;
    fTypeName = type_name;
    fExpandedDSP = "";
    fOptLevel = 0;
    fTarget = "";
}

int llvm_dsp_factory_aux::getOptlevel()
{
    // TODO LLVM_36
    /*
    NamedMDNode* meta_data = fModule->getOrInsertNamedMetadata("OptLevel");
    if (meta_data->getNumOperands() > 0) {
        MDNode* node = meta_data->getOperand(0);
        return (node) ? atoi(static_cast<MDString*>(node->getOperand(0))->getString().data()) : -1;
    } else {
        char opt_level[32];
        sprintf(opt_level, "%d", fOptLevel);
        Value* values[] = { MDString::get(fModule->getContext(), opt_level) };
        meta_data->addOperand(MDNode::get(fModule->getContext(), values));
        return -1;
    }
    */
    return -1;
}

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
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
    #if defined(LLVM_40) || defined(LLVM_50)
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
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
    LLVMLinkInMCJIT();
#endif
    
    // Restoring from machine code
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
    if (fObjectCache) {
    
        // JIT
    #if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
        EngineBuilder builder((unique_ptr<Module>(fModule)));
    #else
        EngineBuilder builder(fModule);
    #endif
        builder.setEngineKind(EngineKind::JIT);
    #if !defined(LLVM_36) && !defined(LLVM_37) && !defined(LLVM_38) && !defined(LLVM_39) && !defined(LLVM_40) && !defined(LLVM_50)
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
    #if !defined(LLVM_38) && !defined(LLVM_39) && !defined(LLVM_40) && !defined(LLVM_50)
        initializeIPA(Registry);
    #endif
        initializeTransformUtils(Registry);
        initializeInstCombine(Registry);
        initializeInstrumentation(Registry);
        initializeTarget(Registry);
       
    #if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
        EngineBuilder builder((unique_ptr<Module>(fModule)));
    #else
        EngineBuilder builder(fModule);
    #endif
        builder.setOptLevel(CodeGenOpt::Aggressive);
        builder.setEngineKind(EngineKind::JIT);
        builder.setCodeModel(CodeModel::JITDefault);
        
        string buider_error;
        builder.setErrorStr(&buider_error);
        
        // MCJIT does not work correctly (incorrect float numbers ?) when used with dynamic libLLVM
    #if (defined(LLVM_34) || defined(LLVM_35)) && !defined(_MSC_VER)
        builder.setUseMCJIT(true);
    #elif !defined(LLVM_36) && !defined(LLVM_37) && !defined(LLVM_38) && !defined(LLVM_39) && !defined(LLVM_40) && !defined(LLVM_50)
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
        
        // -fastmath is activated at IR level, and needs to be setup at JIT level also
        
    #if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
    #if !defined(LLVM_50)
        targetOptions.LessPreciseFPMADOption = true;
    #endif
        targetOptions.AllowFPOpFusion = FPOpFusion::Fast;
        targetOptions.UnsafeFPMath = true;
        targetOptions.NoInfsFPMath = true;
        targetOptions.NoNaNsFPMath = true;
        targetOptions.GuaranteedTailCallOpt = true;
    #endif
    
    #if defined(LLVM_40) || defined(LLVM_50)
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
            
        #if defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) // Code taken from opt.cpp
            TargetLibraryInfoImpl TLII(Triple(fModule->getTargetTriple()));
            pm.add(new TargetLibraryInfoWrapperPass(TLII));
        #else
            // Add an appropriate TargetLibraryInfo pass for the module's triple.
            TargetLibraryInfo* tli = new TargetLibraryInfo(Triple(fModule->getTargetTriple()));
            pm.add(tli);
        #endif

        #if defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
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
        #if defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) // Code taken from opt.cpp
            pm.add(createTargetTransformInfoWrapperPass(tm->getTargetIRAnalysis()));
        #else
            tm->addAnalysisPasses(pm);
        #endif
          
            if (fOptLevel > 0) {
                AddOptimizationPasses(pm, fpm, fOptLevel, 0);
            }
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM1") != string::npos)) {
                TargetRegistry::printRegisteredTargetsForVersion();
                DUMP(fModule);
            }
           
            fpm.doInitialization();
            for (Module::iterator F = fModule->begin(), E = fModule->end(); F != E; ++F) {
                fpm.run(*F);
            }
            fpm.doFinalization();
            
            pm.add(createVerifierPass());
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM4") != string::npos)) {
            #if defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
                // TODO
            #else
                tm->addPassesToEmitFile(pm, fouts(), TargetMachine::CGFT_AssemblyFile, true);
            #endif
            }
            
            // Now that we have all of the passes ready, run them.
            pm.run(*fModule);
            
            if ((debug_var != "") && (debug_var.find("FAUST_LLVM2") != string::npos)) {
                DUMP(fModule);
            }
        }
        
    #if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
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

bool llvm_dsp_factory_aux::initJIT(string& error_msg)
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
            DUMP(fModule);
        }
        
        // Now that we have all of the passes ready, run them.
        pm.run(*fModule);
        
        if ((debug_var != "") && (debug_var.find("FAUST_LLVM2") != string::npos)) {
            DUMP(fModule);
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

void llvm_dsp_factory_aux::write(std::ostream* out, bool binary, bool small)
{
    string res;
    raw_string_ostream out_str(res);
    if (binary) {
        WriteBitcodeToFile(fModule, out_str);
    } else {
        out_str << *fModule;
    }
    *out << out_str.str();
}

void llvm_dsp_factory_aux::metadata(Meta* m)
{
    MetaGlue glue;
    buildMetaGlue(&glue, m);
    fMetadata(&glue);
}

void llvm_dsp_factory_aux::metadata(MetaGlue* glue)
{
    return fMetadata(glue);
}

/*
llvm_dsp* llvm_dsp_factory_aux::createDSPInstance(dsp_factory* factory)
{
    dsp_imp* dsp = fNew();
    return (dsp) ? new llvm_dsp(dynamic_cast<llvm_dsp_factory*>(factory), dsp) : nullptr;
}
*/

llvm_dsp* llvm_dsp_factory_aux::createDSPInstance(dsp_factory* factory)
{
    llvm_dsp_factory* tmp = static_cast<llvm_dsp_factory*>(factory);
    faustassert(tmp);
    
    if (tmp->getFactory()->getMemoryManager()) {
        dsp_imp* dsp = reinterpret_cast<dsp_imp*>(tmp->getFactory()->allocate(fGetSize()));
        return (dsp) ? new (tmp->getFactory()->allocate(sizeof(llvm_dsp))) llvm_dsp(tmp, dsp) : nullptr;
    } else {
        // LLVM module memory code
        dsp_imp* dsp = fNew();
        return (dsp) ? new llvm_dsp(tmp, dsp) : nullptr;
    }
}

// Instance

llvm_dsp::llvm_dsp(llvm_dsp_factory* factory, dsp_imp* dsp):fFactory(factory), fDSP(dsp)
{}

llvm_dsp::~llvm_dsp()
{
    gLLVMFactoryTable.removeDSP(fFactory, this);
    TLock lock(gDSPFactoriesLock);
    
    if (fFactory->getMemoryManager()) {
        fFactory->getMemoryManager()->destroy(fDSP);
    } else {
        // LLVM module memory code
        fFactory->getFactory()->fDelete(fDSP);
    }
}

void llvm_dsp::metadata(Meta* m)
{
    return fFactory->getFactory()->metadata(m);
}

void llvm_dsp::metadata(MetaGlue* glue)
{
    return fFactory->getFactory()->metadata(glue);
}

int llvm_dsp::getNumInputs()
{
    return fFactory->getFactory()->fGetNumInputs(fDSP);
}

int llvm_dsp::getNumOutputs()
{
    return fFactory->getFactory()->fGetNumOutputs(fDSP);
}

void llvm_dsp::init(int samplingRate)
{
    fFactory->getFactory()->fInit(fDSP, samplingRate);
}

void llvm_dsp::instanceInit(int samplingRate)
{
    fFactory->getFactory()->fInstanceInit(fDSP, samplingRate);
}

void llvm_dsp::instanceConstants(int samplingRate)
{
    fFactory->getFactory()->fInstanceConstants(fDSP, samplingRate);
}

void llvm_dsp::instanceResetUserInterface()
{
    fFactory->getFactory()->fInstanceResetUI(fDSP);
}

void llvm_dsp::instanceClear()
{
    fFactory->getFactory()->fInstanceClear(fDSP);
}

llvm_dsp* llvm_dsp::clone()
{
    return fFactory->createDSPInstance();
}

int llvm_dsp::getSampleRate()
{
    return fFactory->getFactory()->fGetSampleRate(fDSP);
}

void llvm_dsp::buildUserInterface(UI* ui_interface)
{
    UIGlue glue;
    buildUIGlue(&glue, ui_interface, (fFactory->getFactory()->fGetSampleSize() == sizeof(double)));
    fFactory->getFactory()->fBuildUserInterface(fDSP, &glue);
}

void llvm_dsp::buildUserInterface(UIGlue* glue)
{
    fFactory->getFactory()->fBuildUserInterface(fDSP, glue);
}

void llvm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    AVOIDDENORMALS;
    fFactory->getFactory()->fCompute(fDSP, count, input, output);
}

// Public C++ API

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
    TLock lock(gDSPFactoriesLock);
    
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
        
        if (gLLVMFactoryTable.getFactory(sha_key, it)) {
            SDsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else {
            llvm_dsp_factory_aux* factory_aux = static_cast<llvm_dsp_factory_aux*>(compileFaustFactory(argc1, argv1,
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
                gLLVMFactoryTable.setFactory(factory);
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

EXPORT llvm_dsp_factory* getDSPFactoryFromSHAKey(const string& sha_key)
{
    TLock lock(gDSPFactoriesLock);
    return reinterpret_cast<llvm_dsp_factory*>(gLLVMFactoryTable.getDSPFactoryFromSHAKey(sha_key));
}

EXPORT vector<string> getAllDSPFactories()
{
    TLock lock(gDSPFactoriesLock);
    return gLLVMFactoryTable.getAllDSPFactories();
}

EXPORT bool deleteDSPFactory(llvm_dsp_factory* factory)
{
    if (factory) {
        TLock lock(gDSPFactoriesLock);
        return gLLVMFactoryTable.deleteDSPFactory(factory);
    } else {
        return false;
    }
}

string llvm_dsp_factory_aux::getTarget() { return fTarget; }
    
EXPORT string getDSPMachineTarget()
{
    return (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME);
}

EXPORT vector<string> getDSPFactoryLibraryList(llvm_dsp_factory* factory)
{
    TLock lock(gDSPFactoriesLock);
    return factory->getDSPFactoryLibraryList();
}

EXPORT void deleteAllDSPFactories()
{
    TLock lock(gDSPFactoriesLock);
    gLLVMFactoryTable.deleteAllDSPFactories();
}
    
// Bitcode <==> string
static llvm_dsp_factory* readDSPFactoryFromBitcodeAux(MEMORY_BUFFER buffer, const string& target, int opt_level)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    dsp_factory_table<SDsp_factory>::factory_iterator it;
    
    if (gLLVMFactoryTable.getFactory(sha_key, it)) {
        SDsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        string error_msg;
        LLVMContext* context = new LLVMContext();
        Module* module = ParseBitcodeFile(buffer, *context, &error_msg);
        if (!module) return nullptr;
        
        std::vector<std::string> dummy_list;
        llvm_dsp_factory_aux* factory_aux = new llvm_dsp_factory_aux(sha_key, dummy_list, module, context, target, opt_level);
        
        if (factory_aux->initJIT(error_msg)) {
            llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
            gLLVMFactoryTable.setFactory(factory);
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
  
#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
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
    TLock lock(gDSPFactoriesLock);
    if (factory) {
        factory->writeDSPFactoryToBitcodeFile(bit_code_path);
    }
}

// IR <==> string

static llvm_dsp_factory* readDSPFactoryFromIRAux(MEMORY_BUFFER buffer, const string& target, int opt_level)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    dsp_factory_table<SDsp_factory>::factory_iterator it;
    
    if (gLLVMFactoryTable.getFactory(sha_key, it)) {
        SDsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        char* tmp_local = setlocale(LC_ALL, NULL);
        setlocale(LC_ALL, "C");
        LLVMContext* context = new LLVMContext();
        SMDiagnostic err;
    #if defined(LLVM_36) || defined(LLVM_37) ||defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
        Module* module = parseIR(buffer, err, *context).release();  // parseIR takes ownership of the given buffer, so don't delete it
    #else
        Module* module = ParseIR(buffer, err, *context);            // ParseIR takes ownership of the given buffer, so don't delete it
    #endif
        if (!module) return nullptr;
        
        setlocale(LC_ALL, tmp_local);
        string error_msg;
        std::vector<std::string> dummy_list;
        llvm_dsp_factory_aux* factory_aux = new llvm_dsp_factory_aux(sha_key, dummy_list, module, context, target, opt_level);
        
        if (factory_aux->initJIT(error_msg)) {
            llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
            gLLVMFactoryTable.setFactory(factory);
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
 
 #if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
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
    TLock lock(gDSPFactoriesLock);
    
    if (factory) {
        factory->writeDSPFactoryToIRFile(ir_code_path);
    }
}

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
    
static llvm_dsp_factory* readDSPFactoryFromMachineAux(MEMORY_BUFFER buffer, const string& target)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    dsp_factory_table<SDsp_factory>::factory_iterator it;
    
    if (gLLVMFactoryTable.getFactory(sha_key, it)) {
        SDsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        string error_msg;
        std::vector<std::string> dummy_list;
        llvm_dsp_factory_aux* factory_aux = new llvm_dsp_factory_aux(sha_key, MEMORY_BUFFER_GET(buffer).str(), target);
        
        if (factory_aux->initJIT(error_msg)) {
            llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
            gLLVMFactoryTable.setFactory(factory);
            factory->setSHAKey(sha_key);
            return factory;
        } else {
            std::cerr << "readDSPFactoryFromMachine failed : " << error_msg << std::endl;
            delete factory_aux;
            return nullptr;
        }
    }
}

// machine <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const string& machine_code, const string& target)
{
    TLock lock(gDSPFactoriesLock);
    return readDSPFactoryFromMachineAux(MEMORY_BUFFER_CREATE(StringRef(base64_decode(machine_code))), target);
}

EXPORT string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const string& target)
{
    TLock lock(gDSPFactoriesLock);
    return factory->writeDSPFactoryToMachine(target);
}

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const string& machine_code_path,const string& target)
{
    TLock lock(gDSPFactoriesLock);
    
#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(machine_code_path);
    if (error_code ec = buffer.getError()) {
        std::cerr << "readDSPFactoryFromMachineFile failed : " << ec.message() << std::endl;
        return nullptr;
    } else {
        return readDSPFactoryFromMachineAux(MEMORY_BUFFER_GET_REF(buffer), target);
     }
#else
    OwningPtr<MemoryBuffer> buffer;
    if (llvm::error_code ec = MemoryBuffer::getFileOrSTDIN(machine_code_path.c_str(), buffer)) {
        std::cerr << "readDSPFactoryFromMachineFile failed : " << ec.message() << std::endl;
        return nullptr;
    } else {
        return readDSPFactoryFromMachineAux(buffer.get(), target);
    }
#endif
}

EXPORT void writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const string& machine_code_path, const string& target)
{
    TLock lock(gDSPFactoriesLock);
    if (factory) {
        factory->writeDSPFactoryToMachineFile(machine_code_path, target);
    }
}

#else

EXPORT llvm_dsp_factory_aux* readDSPFactoryFromMachine(const string& machine_code)
{
    std::cerr << "readDSPFactoryFromMachine not implemented" << std::endl;
    return nullptr;
}

EXPORT string writeDSPFactoryToMachine(llvm_dsp_factory_aux* factory)
{
    std::cerr << "writeDSPFactoryToMachine not implemented" << std::endl;
    return "";
}

EXPORT llvm_dsp_factory_aux* readDSPFactoryFromMachineFile(const string& machine_code_path)
{
    std::cerr << "readDSPFactoryFromMachineFile not implemented" << std::endl;
    return nullptr;
}

EXPORT void writeDSPFactoryToMachineFile(llvm_dsp_factory_aux* factory, const string& machine_code_path)
{
    std::cerr << "writeDSPFactoryToMachineFile not implemented" << std::endl;
}

#endif
        
// Instance

EXPORT llvm_dsp* llvm_dsp_factory::createDSPInstance()
{
    dsp* dsp = fFactory->createDSPInstance(this);
    gLLVMFactoryTable.addDSP(this, dsp);
    return reinterpret_cast<llvm_dsp*>(dsp);
}

// Use the memory manager if needed
EXPORT void llvm_dsp::operator delete(void* ptr)
{
    dsp_memory_manager* manager = static_cast<llvm_dsp*>(ptr)->fFactory->getMemoryManager();
    if (manager) {
        manager->destroy(ptr);
    } else {
        ::operator delete(ptr);
    }
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

EXPORT const char** getAllCDSPFactories()
{
    vector<string> sha_key_list1 = getAllDSPFactories();
    const char** sha_key_list2 = (const char**)malloc(sizeof(char*) * (sha_key_list1.size() + 1));
    
    size_t i;
    for (i = 0; i < sha_key_list1.size(); i++) {
        sha_key_list2[i] = strdup(sha_key_list1[i].c_str());
    }
    
    // Last element is NULL
    sha_key_list2[i] = nullptr;
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
        return nullptr;
    }
}

EXPORT char* getCSHAKey(llvm_dsp_factory* factory)
{
    if (factory) {
        string shakey = factory->getSHAKey();
        return strdup(shakey.c_str());
    } else {
        return nullptr;
    }
}

EXPORT char* getCTarget(llvm_dsp_factory* factory)
{
    if (factory) {
        string target = factory->getTarget();
        return strdup(target.c_str());
    } else {
        return nullptr;
    }
}

EXPORT char* getCDSPCode(llvm_dsp_factory* factory)
{
    if (factory) {
        string dspcode = factory->getDSPCode();
        return strdup(dspcode.c_str()); 
    } else {
        return nullptr;
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
        library_list2[i] = nullptr;
        return library_list2;
    } else {
        return nullptr;
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
    return (factory) ? strdup(writeDSPFactoryToBitcode(factory).c_str()) : nullptr;
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
    return (factory) ? strdup(writeDSPFactoryToIR(factory).c_str()) : nullptr;
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

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
EXPORT llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code, const char* target)
{
    return readDSPFactoryFromMachine(machine_code, target);
}

EXPORT char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const char* target)
{
    return (factory) ? strdup(writeDSPFactoryToMachine(factory, target).c_str()) : nullptr;
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
    return nullptr;
}

EXPORT char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const string& target)
{
    return nullptr;
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path)
{
    return nullptr;
}

EXPORT void writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path, const string& target)
{}
#endif

EXPORT void metadataCDSPInstance(llvm_dsp* dsp, MetaGlue* glue)
{
    if (dsp) {
        dsp->metadata(glue);
    }
}

EXPORT int getNumInputsCDSPInstance(llvm_dsp* dsp)
{
    return (dsp) ? dsp->getNumInputs(): 0;
}

EXPORT int getNumOutputsCDSPInstance(llvm_dsp* dsp)
{
    return (dsp) ? dsp->getNumOutputs() : 0;
}

EXPORT void initCDSPInstance(llvm_dsp* dsp, int samplingRate)
{
    if (dsp) {
        dsp->init(samplingRate);
    }
}
    
EXPORT void instanceInitCDSPInstance(llvm_dsp* dsp, int samplingRate)
{
    if (dsp) {
        dsp->instanceInit(samplingRate);
    }
}

EXPORT void instanceConstantsCDSPInstance(llvm_dsp* dsp, int samplingRate)
{
    if (dsp) {
        dsp->instanceConstants(samplingRate);
    }
}
        
EXPORT void instanceResetUserInterfaceCDSPInstance(llvm_dsp* dsp)
{
    if (dsp) {
        dsp->instanceResetUserInterface();
    }
}
        
EXPORT void instanceClearCDSPInstance(llvm_dsp* dsp)
{
    if (dsp) {
        dsp->instanceClear();
    }
}
        
EXPORT int getSampleRateCDSPInstance(llvm_dsp* dsp)
{
    return (dsp) ? dsp->getSampleRate() : 0;
}

EXPORT void buildUserInterfaceCDSPInstance(llvm_dsp* dsp, UIGlue* glue)
{
    if (dsp) {
        dsp->buildUserInterface(glue);
    }
}

EXPORT void computeCDSPInstance(llvm_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    if (dsp) {
        dsp->compute(count, input, output);
    }
}

EXPORT llvm_dsp* cloneCDSPInstance(llvm_dsp* dsp)
{
    return (dsp) ? dsp->clone() : 0;
}

EXPORT void setCMemoryManager(llvm_dsp_factory* factory, ManagerGlue* manager)
{
    if (factory)  {
        factory->setMemoryManager(manager);
    }
}

EXPORT llvm_dsp* createCDSPInstance(llvm_dsp_factory* factory)
{
    return (factory) ? factory->createDSPInstance() : 0;
}

EXPORT void deleteCDSPInstance(llvm_dsp* dsp)
{
    if (dsp) {
        delete (dsp); 
    }
}

// Helper functions

ModulePTR loadSingleModule(const string filename, LLVMContext* context)
{
    SMDiagnostic err;
#if defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
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
    
#if defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
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

