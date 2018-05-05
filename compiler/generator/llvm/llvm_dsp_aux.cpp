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

#include <llvm/Support/TargetSelect.h>
#include <llvm-c/Core.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/FileSystem.h>

#if defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Bitcode/BitcodeReader.h>
#else
#include <llvm/Bitcode/ReaderWriter.h>
#endif

#if defined(LLVM_35)
#include <llvm-c/Core.h>
#include <llvm/Target/TargetLibraryInfo.h>
#include <llvm/PassManager.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#endif

using namespace llvm;
using namespace std;

#ifdef LLVM_MACHINE

void faustassert(bool) {}
extern "C" EXPORT const char* getCLibFaustVersion() { return FAUSTVERSION; }

#endif

// Factories instances management
int llvm_dsp_factory_aux::gInstance = 0;

dsp_factory_table<SDsp_factory> llvm_dsp_factory_aux::gLLVMFactoryTable;

// Global API access lock
TLockAble* llvm_dsp_factory_aux::gDSPFactoriesLock = 0;

void* llvm_dsp_factory_aux::loadOptimize(const string& function)
{
    void* fun = (void*)fJIT->getFunctionAddress(function);
    if (fun) {
        return fun;
    }
    
    stringstream error;
    error << "ERROR : loadOptimize failed for '" << function << "'";
    throw faustexception(error.str());
}

bool llvm_dsp_factory_aux::crossCompile(const string& target)
{
#ifndef LLVM_35
    delete fObjectCache;
    fObjectCache = new FaustObjectCache();
#endif
    setTarget(target);
    string error;
    return initJIT(error);
}

void llvm_dsp_factory_aux::startLLVMLibrary()
{
    if (llvm_dsp_factory_aux::gInstance++ == 0) {
        // Install a LLVM error handler
        LLVMInstallFatalErrorHandler(llvm_dsp_factory_aux::LLVMFatalErrorHandler);
    }
}

void llvm_dsp_factory_aux::stopLLVMLibrary()
{
    if (--llvm_dsp_factory_aux::gInstance == 0) {
    #ifndef LLVM_BUILD_UNIVERSAL // Crash in 32 bits on OSX, so deactivated in this case...
        LLVMResetFatalErrorHandler();
    #endif
    }
}

llvm_dsp_factory_aux::llvm_dsp_factory_aux(const string& sha_key, const string& machine_code, const string& target)
:dsp_factory_imp("MachineDSP", sha_key, "")
{
#ifndef LLVM_35
    startLLVMLibrary();
    
    init("MachineDSP", "");
    fSHAKey = sha_key;
    fTarget = (target == "") ? fTarget = (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME) : target;
    
    // Restoring the cache
    fObjectCache = new FaustObjectCache(machine_code);
    
    // Creates module and context
    fContext = new LLVMContext();
    fModule = new Module(string(LLVM_BACKEND_NAME) + ", v" + string(FAUSTVERSION), *fContext);
#else
    #warning "machine code is not supported..."
#endif
}

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
#ifndef LLVM_35
    fObjectCache = nullptr;
#endif
}

llvm_dsp_factory_aux::~llvm_dsp_factory_aux()
{
#ifndef LLVM_35
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

void llvm_dsp_factory_aux::LLVMFatalErrorHandler(const char* reason)
{
    throw faustexception(string(reason) + "\n");
}

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

bool llvm_dsp_factory_aux::initJIT(string& error_msg)
{
    // For host target support
    InitializeNativeTarget();
    
    // Restoring from machine code
#if defined(LLVM_35)
    EngineBuilder builder(fModule);
#else
    EngineBuilder builder((unique_ptr<Module>(fModule)));
#endif
    TargetMachine* tm = builder.selectTarget();
    fJIT = builder.create(tm);
#ifndef LLVM_35
    fJIT->setObjectCache(fObjectCache);
#endif
    fJIT->finalizeObject();
    
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
        fGetSampleSize = (getSampleSizeFun)loadOptimize("getSampleSize" + fClassName);        return true;
    } catch (faustexception& e) { // Module does not contain the Faust entry points, or external symbol was not found...
        error_msg = e.Message();
        return false;
    }
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
#ifndef LLVM_35
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
    #warning "machine code is not supported..."
    return "";
#endif
}

string llvm_dsp_factory_aux::writeDSPFactoryToMachine(const string& target)
{
    return base64_encode(writeDSPFactoryToMachineAux(target));
}

void llvm_dsp_factory_aux::writeDSPFactoryToMachineFile(const string& machine_code_path, const string& target)
{
#ifndef LLVM_35
    STREAM_ERROR err;
    raw_fd_ostream out(machine_code_path.c_str(), err, sysfs_binary_flag);
    out << writeDSPFactoryToMachineAux(target);
    out.flush();
#else
    #warning "machine code is not supported..."
#endif
}

#ifndef LLVM_35
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
#ifndef LLVM_35
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return readDSPFactoryFromMachineAux(MEMORY_BUFFER_CREATE(StringRef(base64_decode(machine_code))), target);
#else
    #warning "machine code is not supported..."
    return nullptr;
#endif
}

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const string& machine_code_path,const string& target)
{
#ifndef LLVM_35
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(machine_code_path);
    if (error_code ec = buffer.getError()) {
        std::cerr << "readDSPFactoryFromMachineFile failed : " << ec.message() << std::endl;
        return nullptr;
    } else {
        return readDSPFactoryFromMachineAux(MEMORY_BUFFER_GET_REF(buffer), target);
    }
#else
    #warning "machine code is not supported..."
    return nullptr;
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
