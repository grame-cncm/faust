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
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>

#include "compatibility.hh"
#include "faust/gui/CGlue.h"
#include "libfaust.h"
#include "llvm_dsp_aux.hh"
#include "rn_base64.h"

#include <llvm-c/Core.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>

#if defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60)
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#else
#include <llvm/Bitcode/ReaderWriter.h>
#endif

#if defined(LLVM_35)
#include <llvm-c/Core.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetLibraryInfo.h>
#endif

using namespace llvm;
using namespace std;

#define LLVM_BACKEND_NAME "Faust LLVM backend"

#ifdef LLVM_MACHINE

void faustassert(bool)
{
}
extern "C" EXPORT const char* getCLibFaustVersion()
{
    return FAUSTVERSION;
}

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
    } else {
        stringstream error;
        error << "ERROR : loadOptimize failed for '" << function << "'" << endl;
        throw faustexception(error.str());
    }
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
#ifndef __APPLE__  // Crash on OSX, so deactivated in this case...
        LLVMResetFatalErrorHandler();
#endif
    }
}

llvm_dsp_factory_aux::llvm_dsp_factory_aux(const string& sha_key, const string& machine_code, const string& target)
    : dsp_factory_imp("MachineDSP", sha_key, "")
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
    fModule  = new Module(string(LLVM_BACKEND_NAME) + ", v" + string(FAUSTVERSION), *fContext);
#else
#warning "machine code is not supported..."
#endif
}

llvm_dsp_factory_aux::llvm_dsp_factory_aux(const string& sha_key, Module* module, LLVMContext* context, const string& target, int opt_level)
    : dsp_factory_imp("BitcodeDSP", sha_key, "")
{
    startLLVMLibrary();

    init("BitcodeDSP", "");
    fSHAKey = sha_key;
    fTarget = (target == "") ? fTarget = (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME) : target;
    setOptlevel(opt_level);

    fModule  = module;
    fContext = context;
    fDecoder = nullptr;
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
    delete fDecoder;
    stopLLVMLibrary();
}

void llvm_dsp_factory_aux::LLVMFatalErrorHandler(const char* reason)
{
    throw faustexception(string(reason) + "\n");
}

void llvm_dsp_factory_aux::init(const string& type_name, const string& dsp_name)
{
    fJIT                = 0;
    fNew                = 0;
    fDelete             = 0;
    fGetNumInputs       = 0;
    fGetNumOutputs      = 0;
    fBuildUserInterface = 0;
    fInit               = 0;
    fInstanceInit       = 0;
    fInstanceConstants  = 0;
    fInstanceResetUI    = 0;
    fInstanceClear      = 0;
    fCompute            = 0;
    fClassName          = "mydsp";
    fName               = dsp_name;
    fTypeName           = type_name;
    fExpandedDSP        = "";
    fOptLevel           = 0;
    fTarget             = "";
}

bool llvm_dsp_factory_aux::initJIT(string& error_msg)
{
    startTiming("initJIT");
 
    // Restoring from machine code
#if defined(LLVM_35)
    EngineBuilder builder(fModule);
#else
    EngineBuilder builder((unique_ptr<Module>(fModule)));
#endif
    TargetMachine* tm = builder.selectTarget();
    fJIT              = builder.create(tm);
#ifndef LLVM_35
    fJIT->setObjectCache(fObjectCache);
#endif
    fJIT->finalizeObject();

    return initJITAux(error_msg);
}

bool llvm_dsp_factory_aux::initJITAux(string& error_msg)
{
    // Run static constructors.
    fJIT->runStaticConstructorsDestructors(false);
    fJIT->DisableLazyCompilation(true);
    
    try {
        fNew                = (newDspFun)loadOptimize("new" + fClassName);
        fDelete             = (deleteDspFun)loadOptimize("delete" + fClassName);
        fGetNumInputs       = (getNumInputsFun)loadOptimize("getNumInputs" + fClassName);
        fGetNumOutputs      = (getNumOutputsFun)loadOptimize("getNumOutputs" + fClassName);
        fBuildUserInterface = (buildUserInterfaceFun)loadOptimize("buildUserInterface" + fClassName);
        fInit               = (initFun)loadOptimize("init" + fClassName);
        fInstanceInit       = (initFun)loadOptimize("instanceInit" + fClassName);
        fInstanceConstants  = (initFun)loadOptimize("instanceConstants" + fClassName);
        fInstanceResetUI    = (clearFun)loadOptimize("instanceResetUserInterface" + fClassName);
        fInstanceClear      = (clearFun)loadOptimize("instanceClear" + fClassName);
        fGetSampleRate      = (getSampleRateFun)loadOptimize("getSampleRate" + fClassName);
        fCompute            = (computeFun)loadOptimize("compute" + fClassName);
        fMetadata           = (metadataFun)loadOptimize("metadata" + fClassName);
        fGetJSON            = (getJSONFun)loadOptimize("getJSON" + fClassName);
        fSetDefaultSound    = (setDefaultSoundFun)loadOptimize("setDefaultSound" + fClassName);
        
        fDecoder = new JSONUIDecoder(fGetJSON());
        
        // Set the default sound
        fSetDefaultSound(dynamic_defaultsound);
        endTiming("initJIT");
        return true;
    } catch (faustexception& e) {  // Module does not contain the Faust entry points, or external symbol was not found...
        error_msg = e.Message();
        endTiming("initJIT");
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
        dsp_imp* dsp = static_cast<dsp_imp*>(tmp->getFactory()->allocate(fDecoder->fDSPSize));
        return (dsp) ? new (tmp->getFactory()->allocate(sizeof(llvm_dsp))) llvm_dsp(tmp, dsp) : nullptr;
    } else {
        // LLVM module memory code
        dsp_imp* dsp = fNew();
        return (dsp) ? new llvm_dsp(tmp, dsp) : nullptr;
    }
}

// Instance

llvm_dsp::llvm_dsp(llvm_dsp_factory* factory, dsp_imp* dsp) : fFactory(factory), fDSP(dsp)
{
}

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
    buildUIGlue(&glue, ui_interface, (fFactory->getFactory()->fDecoder->hasCompileOption("-double")));
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
    return static_cast<llvm_dsp_factory*>(llvm_dsp_factory_aux::gLLVMFactoryTable.getDSPFactoryFromSHAKey(sha_key));
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

string llvm_dsp_factory_aux::getTarget()
{
    return fTarget;
}

EXPORT string getDSPMachineTarget()
{
    return (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME);
}

EXPORT vector<string> getLibraryList(llvm_dsp_factory* factory)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return factory->getLibraryList();
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
    string                                            sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    dsp_factory_table<SDsp_factory>::factory_iterator it;

    if (llvm_dsp_factory_aux::gLLVMFactoryTable.getFactory(sha_key, it)) {
        SDsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        string                   error_msg;
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
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const string& machine_code_path, const string& target)
{
#ifndef LLVM_35
    TLock                            lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
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

EXPORT string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const string& target)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    return factory->writeDSPFactoryToMachine(target);
}

EXPORT void writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const string& machine_code_path,
                                         const string& target)
{
    TLock lock(llvm_dsp_factory_aux::gDSPFactoriesLock);
    if (factory) {
        factory->writeDSPFactoryToMachineFile(machine_code_path, target);
    }
}

// Instance
EXPORT llvm_dsp* llvm_dsp_factory::createDSPInstance()
{
    dsp* dsp = fFactory->createDSPInstance(this);
    llvm_dsp_factory_aux::gLLVMFactoryTable.addDSP(this, dsp);
    return static_cast<llvm_dsp*>(dsp);
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

#ifdef __cplusplus
extern "C" {
#endif
    
EXPORT llvm_dsp_factory* getCDSPFactoryFromSHAKey(const char* sha_key)
{
    return getDSPFactoryFromSHAKey(sha_key);
}

EXPORT const char** getAllCDSPFactories()
{
    vector<string> sha_key_list1 = getAllDSPFactories();
    const char**   sha_key_list2 = (const char**)malloc(sizeof(char*) * (sha_key_list1.size() + 1));
    
    size_t i;
    for (i = 0; i < sha_key_list1.size(); i++) {
        sha_key_list2[i] = strdup(sha_key_list1[i].c_str());
    }
    
    // Last element is NULL
    sha_key_list2[i] = nullptr;
    return sha_key_list2;
}

EXPORT bool startMTCDSPFactories()
{
    return startMTDSPFactories();
}

EXPORT void stopMTCDSPFactories()
{
    stopMTDSPFactories();
}

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
        vector<string> library_list1 = factory->getLibraryList();
        const char**   library_list2 = (const char**)malloc(sizeof(char*) * (library_list1.size() + 1));
        
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

EXPORT const char** getCDSPFactoryIncludePathnames(llvm_dsp_factory* factory)
{
    if (factory) {
        vector<string> include_list1 = factory->getIncludePathnames();
        const char**   include_list2 = (const char**)malloc(sizeof(char*) * (include_list1.size() + 1));
        
        size_t i;
        for (i = 0; i < include_list1.size(); i++) {
            include_list2[i] = strdup(include_list1[i].c_str());
        }
        
        // Last element is NULL
        include_list2[i] = nullptr;
        return include_list2;
    } else {
        return nullptr;
    }
}
    
EXPORT char* getCDSPFactoryCompileOptions(llvm_dsp_factory* factory)
{
    if (factory) {
        string const dspcode = factory->getCompileOptions();
        return strdup(dspcode.c_str());
    } else {
        return nullptr;
    }
}

EXPORT void deleteAllCDSPFactories()
{
    deleteAllDSPFactories();
}

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

EXPORT void metadataCDSPInstance(llvm_dsp* dsp, MetaGlue* glue)
{
    if (dsp) {
        dsp->metadata(glue);
    }
}

EXPORT int getNumInputsCDSPInstance(llvm_dsp* dsp)
{
    return (dsp) ? dsp->getNumInputs() : 0;
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
    if (factory) {
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
    
#ifdef __cplusplus
}
#endif
