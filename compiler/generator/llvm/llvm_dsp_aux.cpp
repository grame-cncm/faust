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
#include "rn_base64.h"
#include "libfaust.h"

//#include <llvm/Target/TargetMachine.h>
//#include <llvm/Transforms/IPO.h>
//#include <llvm/Transforms/Scalar.h>
//#include <llvm/Support/TargetSelect.h>
//#include <llvm/Support/Host.h>
//#include <llvm/Support/ManagedStatic.h>
//#include <llvm/Transforms/IPO/PassManagerBuilder.h>
//#include <llvm/Support/Threading.h>

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    //#include <llvm/IR/Module.h>
    //#include <llvm/IR/LLVMContext.h>
    //#include <llvm/IRReader/IRReader.h>
    //#include <llvm/IR/DataLayout.h>
    //#include <llvm/Support/FormattedStream.h>
    //#include <llvm/Support/SourceMgr.h>
    //#include <llvm/Support/MemoryBuffer.h>
    //#include <llvm/ADT/Triple.h>
    //#include <llvm/Support/TargetRegistry.h>
    #include <llvm-c/Core.h>
    //#include <llvm/Support/Host.h>
    //#include <llvm/MC/SubtargetFeature.h>

#else
    #include <llvm/Module.h>
    #include <llvm/LLVMContext.h>
    #include <llvm/Support/IRReader.h>
#endif

#if defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    /*
    #include <llvm/Analysis/TargetLibraryInfo.h>
    #include <llvm/Analysis/TargetTransformInfo.h>
    #include <llvm/IR/PassManager.h>
    #include <llvm/IR/LegacyPassManager.h>
    #define PASS_MANAGER legacy::PassManager
    #define FUNCTION_PASS_MANAGER legacy::FunctionPassManager
    */
#else
    #include <llvm/Target/TargetLibraryInfo.h>
    #include <llvm/PassManager.h>
    #define PASS_MANAGER PassManager
    #define FUNCTION_PASS_MANAGER FunctionPassManager
#endif

#if defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)

    #include <llvm/Bitcode/BitcodeWriter.h>
    #include <llvm/Bitcode/BitcodeReader.h>
/*
    #include <llvm/Transforms/IPO/AlwaysInliner.h>
     */
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
    //#include <llvm/Target/TargetData.h>
    #endif
#endif

#if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    #include <llvm/ExecutionEngine/MCJIT.h>
    //#include <llvm/ExecutionEngine/ObjectCache.h>
#else
    #include <llvm/ExecutionEngine/JIT.h>
#endif

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
    /*
    #include <llvm/IR/LegacyPassNameParser.h>
    #include <llvm/Linker/Linker.h>
    #include <llvm/IR/IRPrintingPasses.h>
    #include <system_error>
    #include <llvm/IR/Verifier.h>
    #include <llvm/Support/FileSystem.h>
    */
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
    //#include <llvm/ExecutionEngine/ObjectCache.h>
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

// Factories instances management
int llvm_dsp_factory_aux::gInstance = 0;

dsp_factory_table<SDsp_factory> llvm_dsp_factory_aux::gLLVMFactoryTable;

// Global API access lock
TLockAble* llvm_dsp_factory_aux::gDSPFactoriesLock = 0;

void* llvm_dsp_factory_aux::loadOptimize(const string& function)
{
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
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

bool llvm_dsp_factory_aux::crossCompile(const string& target)
{
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
    delete fObjectCache;
    fObjectCache = new FaustObjectCache();
    setTarget(target);
    string error;
    return initJIT(error);
#else
    return false;
#endif
}

void llvm_dsp_factory_aux::startLLVMLibrary()
{
    if (llvm_dsp_factory_aux::gInstance++ == 0) {
        // Install a LLVM error handler
    #if defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
        LLVMInstallFatalErrorHandler(llvm_dsp_factory_aux::LLVMFatalErrorHandler);
    #endif
    #if (!defined(LLVM_35) && !defined(LLVM_36) && !defined(LLVM_37) && !defined(LLVM_38) && !defined(LLVM_39) && !defined(LLVM_40) && !defined(LLVM_50) && !defined(LLVM_60)) // In LLVM 3.5 this is gone.
        if (!llvm_start_multithreaded()) {
            std::cerr << "llvm_start_multithreaded error...\n";
        }
    #endif
    }
}

void llvm_dsp_factory_aux::stopLLVMLibrary()
{
    if (--llvm_dsp_factory_aux::gInstance == 0) {
    #if  (!defined(LLVM_35)) && (!defined(LLVM_36)) && (!defined(LLVM_37)) && (!defined(LLVM_38)) && (!defined(LLVM_39)) && (!defined(LLVM_40)) && (!defined(LLVM_50) && !defined(LLVM_60)) // In LLVM 3.5 this is gone.
        llvm_stop_multithreaded();
    #endif
    #if defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
        LLVMResetFatalErrorHandler();
    #endif
    }
}

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
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
    
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
    fObjectCache = nullptr;
#endif
}

llvm_dsp_factory_aux::~llvm_dsp_factory_aux()
{
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
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

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
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
    llvm_dsp_factory_aux::gLLVMFactoryTable.removeDSP(fFactory, this);
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    
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
        if (!llvm_dsp_factory_aux::gDSPFactoriesLock) {
            llvm_dsp_factory_aux::gDSPFactoriesLock = new TLockAble();
        }
        return true;
    } catch (...) {
        return false;
    }
}

EXPORT void stopMTDSPFactories()
{
    delete llvm_dsp_factory_aux::gDSPFactoriesLock;
    llvm_dsp_factory_aux::gDSPFactoriesLock = 0;
}

EXPORT llvm_dsp_factory* getDSPFactoryFromSHAKey(const string& sha_key)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return reinterpret_cast<llvm_dsp_factory*>(llvm_dsp_factory_aux::gLLVMFactoryTable.getDSPFactoryFromSHAKey(sha_key));
}

EXPORT vector<string> getAllDSPFactories()
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return llvm_dsp_factory_aux::gLLVMFactoryTable.getAllDSPFactories();
}

EXPORT bool deleteDSPFactory(llvm_dsp_factory* factory)
{
    if (factory) {
        TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
        return llvm_dsp_factory_aux::gLLVMFactoryTable.deleteDSPFactory(factory);
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
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return factory->getDSPFactoryLibraryList();
}

EXPORT void deleteAllDSPFactories()
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    llvm_dsp_factory_aux::gLLVMFactoryTable.deleteAllDSPFactories();
}

string llvm_dsp_factory_aux::writeDSPFactoryToMachineAux(const string& target)
{
#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
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

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
    
static llvm_dsp_factory* readDSPFactoryFromMachineAux(MEMORY_BUFFER buffer, const string& target)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    dsp_factory_table<SDsp_factory>::factory_iterator it;
    
    if (llvm_dsp_factory_aux::gLLVMFactoryTable.getFactory(sha_key, it)) {
        SDsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        string error_msg;
        std::vector<std::string> dummy_list;
        llvm_dsp_factory_aux* factory_aux = new llvm_dsp_factory_aux(sha_key, MEMORY_BUFFER_GET(buffer).str(), target);
        
        if (factory_aux->initJIT(error_msg)) {
            llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
            llvm_dsp_factory_aux::gLLVMFactoryTable.setFactory(factory);
            factory->setSHAKey(sha_key);
            return factory;
        } else {
            std::cerr << "readDSPFactoryFromMachine failed : " << error_msg << std::endl;
            delete factory_aux;
            return nullptr;
        }
    }
}

#endif

// machine <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const string& machine_code, const string& target)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return readDSPFactoryFromMachineAux(MEMORY_BUFFER_CREATE(StringRef(base64_decode(machine_code))), target);
}

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const string& machine_code_path,const string& target)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    
#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
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

// Instance

EXPORT llvm_dsp* llvm_dsp_factory::createDSPInstance()
{
    dsp* dsp = fFactory->createDSPInstance(this);
    llvm_dsp_factory_aux::gLLVMFactoryTable.addDSP(this, dsp);
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

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)) && !defined(_MSC_VER)
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
