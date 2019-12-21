/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifdef WIN32
#pragma warning(disable : 4141 4146 4244 4267 4275 4800)
//# define strdup _strdup
#endif

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>

#include "Text.hh"
#include "compatibility.hh"
#include "faust/gui/CGlue.h"
#include "faust/gui/JSONUIDecoder.h"
#include "libfaust.h"
#include "llvm_dsp_aux.hh"
#include "rn_base64.h"
#include "lock_api.hh"

#include <llvm-c/Core.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>

using namespace llvm;
using namespace std;

// Used by LLVM backend (for now)
Soundfile* dynamic_defaultsound = new Soundfile(64);

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

// Debug tools
extern "C" EXPORT void printInt32(int val)
{
    cout << "printInt32 : " << val << endl;
}

extern "C" EXPORT void printFloat(float val)
{
    cout << "printFloat : " << val << endl;
}

extern "C" EXPORT void printDouble(double val)
{
    cout << "printDouble : " << val << endl;
}

extern "C" EXPORT void printPtr(void* val)
{
    cout << "printPtr : " << val << endl;
}

// Factories instances management
int llvm_dsp_factory_aux::gInstance = 0;

dsp_factory_table<SDsp_factory> llvm_dsp_factory_aux::gLLVMFactoryTable;

uint64_t llvm_dsp_factory_aux::loadOptimize(const string& function)
{
    uint64_t fun = fJIT->getFunctionAddress(function);
    if (fun) {
        return fun;
    } else {
        stringstream error;
        error << "ERROR : loadOptimize failed for '" << function << "'";
        throw faustexception(error.str());
    }
}

bool llvm_dsp_factory_aux::crossCompile(const string& target)
{
    delete fObjectCache;
    fObjectCache = new FaustObjectCache();
    setTarget(target);
    string error;
    return initJIT(error);
}

void llvm_dsp_factory_aux::startLLVMLibrary()
{
    if (llvm_dsp_factory_aux::gInstance++ == 0) {
        // Install an LLVM error handler
        LLVMInstallFatalErrorHandler(llvm_dsp_factory_aux::LLVMFatalErrorHandler);
    }
}

void llvm_dsp_factory_aux::stopLLVMLibrary()
{
    if (--llvm_dsp_factory_aux::gInstance == 0) {
        // Remove the LLVM error handler
#ifdef __APPLE__
    #warning Crash on OSX so deactivated in this case
#else
        LLVMResetFatalErrorHandler();
#endif
    }
}

llvm_dsp_factory_aux::llvm_dsp_factory_aux(const string& sha_key, const string& machine_code, const string& target)
    : dsp_factory_imp("MachineDSP", sha_key, "")
{
    startLLVMLibrary();

    init("MachineDSP", "");
    fSHAKey = sha_key;
    fTarget = (target == "") ? fTarget = (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME) : target;

    // Restoring the cache
    fObjectCache = new FaustObjectCache(machine_code);

    // Creates module and context
    fContext = new LLVMContext();
    fModule  = new Module(string(LLVM_BACKEND_NAME) + ", v" + string(FAUSTVERSION), *fContext);
    fDecoder = nullptr;
}

llvm_dsp_factory_aux::llvm_dsp_factory_aux(const string& sha_key, Module* module, LLVMContext* context,
                                           const string& target, int opt_level)
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
    fObjectCache = nullptr;
}

llvm_dsp_factory_aux::~llvm_dsp_factory_aux()
{
    delete fObjectCache;
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
    fJIT               = nullptr;
    fAllocate          = nullptr;
    fDestroy           = nullptr;
    fInstanceConstants = nullptr;
    fInstanceClear     = nullptr;
    fClassInit         = nullptr;
    fCompute           = nullptr;
    fClassName         = "mydsp";
    fName              = dsp_name;
    fTypeName          = type_name;
    fExpandedDSP       = "";
    fOptLevel          = 0;
    fTarget            = "";

    // To keep Debug functions in generated code
#if 0
    printInt32(1);
    printFloat(0.5f);
    printDouble(0.8);
    printPtr(this);
#endif
}

bool llvm_dsp_factory_aux::initJIT(string& error_msg)
{
    startTiming("initJIT");

    // For host target support
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    // For ObjectCache to work...
    LLVMLinkInMCJIT();

    // Restoring from machine code
    EngineBuilder builder((unique_ptr<Module>(fModule)));
    string buider_error;
    builder.setErrorStr(&buider_error);
    TargetMachine* tm = builder.selectTarget();
    fJIT              = builder.create(tm);
    if (!fJIT) {
        error_msg = buider_error;
        return false;
    }

    fJIT->setObjectCache(fObjectCache);
    fJIT->finalizeObject();
    return initJITAux(error_msg);
}

bool llvm_dsp_factory_aux::initJITAux(string& error_msg)
{
    // Run static constructors.
    fJIT->runStaticConstructorsDestructors(false);
    fJIT->DisableLazyCompilation(true);

    try {
        fAllocate          = (allocateDspFun)loadOptimize("allocate" + fClassName);
        fDestroy           = (destroyDspFun)loadOptimize("destroy" + fClassName);
        fInstanceConstants = (initFun)loadOptimize("instanceConstants" + fClassName);
        fInstanceClear     = (clearFun)loadOptimize("instanceClear" + fClassName);
        fClassInit         = (classInitFun)loadOptimize("classInit" + fClassName);
        fCompute           = (computeFun)loadOptimize("compute" + fClassName);
        fGetJSON           = (getJSONFun)loadOptimize("getJSON" + fClassName);
        
        fDecoder = createJSONUIDecoder(fGetJSON());
        endTiming("initJIT");
        return true;
    } catch (
        faustexception& e) {  // Module does not contain the Faust entry points, or external symbol was not found...
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
    fDecoder->metadata(m);
}

void llvm_dsp_factory_aux::metadata(MetaGlue* glue)
{
    fDecoder->metadata(glue);
}

llvm_dsp* llvm_dsp_factory_aux::createDSPInstance(dsp_factory* factory_aux)
{
    llvm_dsp_factory* factory = static_cast<llvm_dsp_factory*>(factory_aux);
    faustassert(factory);

    if (factory->getFactory()->getMemoryManager()) {
        dsp_imp* dsp = static_cast<dsp_imp*>(factory->getFactory()->allocate(fDecoder->getDSPSize()));
        return (dsp) ? new (factory->getFactory()->allocate(sizeof(llvm_dsp))) llvm_dsp(factory, dsp) : nullptr;
    } else {
        // LLVM module memory code
        dsp_imp* dsp = static_cast<dsp_imp*>(calloc(1, fDecoder->getDSPSize()));
        return (dsp) ? new llvm_dsp(factory, dsp) : nullptr;
    }
}

string llvm_dsp_factory_aux::getCompileOptions()
{
    return fDecoder->getCompileOptions();
}
vector<string> llvm_dsp_factory_aux::getLibraryList()
{
    return fDecoder->getLibraryList();
}
vector<string> llvm_dsp_factory_aux::getIncludePathnames()
{
    return fDecoder->getIncludePathnames();
}

// Instance

llvm_dsp::llvm_dsp(llvm_dsp_factory* factory, dsp_imp* dsp) : fFactory(factory), fDSP(dsp)
{
    // Used in -sch mode
    fFactory->getFactory()->fAllocate(fDSP);
}

llvm_dsp::~llvm_dsp()
{
    LOCK_API
    llvm_dsp_factory_aux::gLLVMFactoryTable.removeDSP(fFactory, this);

    // Used in -sch mode
    fFactory->getFactory()->fDestroy(fDSP);

    if (fFactory->getMemoryManager()) {
        fFactory->getMemoryManager()->destroy(fDSP);
    } else {
        // LLVM module memory code
        free(fDSP);
    }
}

void llvm_dsp::metadata(Meta* m)
{
    fFactory->getFactory()->metadata(m);
}

void llvm_dsp::metadata(MetaGlue* glue)
{
    fFactory->getFactory()->metadata(glue);
}

int llvm_dsp::getNumInputs()
{
    return fFactory->getFactory()->fDecoder->getNumInputs();
}

int llvm_dsp::getNumOutputs()
{
    return fFactory->getFactory()->fDecoder->getNumOutputs();
}

void llvm_dsp::init(int sample_rate)
{
    classInit(sample_rate);
    instanceInit(sample_rate);
}

void llvm_dsp::classInit(int sample_rate)
{
    fFactory->getFactory()->fClassInit(sample_rate);
}

void llvm_dsp::instanceInit(int sample_rate)
{
    instanceConstants(sample_rate);
    instanceResetUserInterface();
    instanceClear();
}

void llvm_dsp::instanceConstants(int sample_rate)
{
    fFactory->getFactory()->fInstanceConstants(fDSP, sample_rate);
}

void llvm_dsp::instanceResetUserInterface()
{
    fFactory->getFactory()->fDecoder->resetUserInterface(fDSP, dynamic_defaultsound);
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
    return fFactory->getFactory()->fDecoder->getSampleRate(fDSP);
}

void llvm_dsp::buildUserInterface(UI* ui_interface)
{
    fFactory->getFactory()->fDecoder->buildUserInterface(ui_interface, fDSP);
}

void llvm_dsp::buildUserInterface(UIGlue* glue)
{
    fFactory->getFactory()->fDecoder->buildUserInterface(glue, fDSP);
}

void llvm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    fFactory->getFactory()->fCompute(fDSP, count, input, output);
}

// Public C++ API

EXPORT llvm_dsp_factory* getDSPFactoryFromSHAKey(const string& sha_key)
{
    LOCK_API
    return static_cast<llvm_dsp_factory*>(llvm_dsp_factory_aux::gLLVMFactoryTable.getDSPFactoryFromSHAKey(sha_key));
}

EXPORT vector<string> getAllDSPFactories()
{
    LOCK_API
    return llvm_dsp_factory_aux::gLLVMFactoryTable.getAllDSPFactories();
}

EXPORT bool deleteDSPFactory(llvm_dsp_factory* factory)
{
    LOCK_API
    return (factory) ? llvm_dsp_factory_aux::gLLVMFactoryTable.deleteDSPFactory(factory) : false;
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
    LOCK_API
    return factory->getLibraryList();
}

EXPORT void deleteAllDSPFactories()
{
    LOCK_API
    llvm_dsp_factory_aux::gLLVMFactoryTable.deleteAllDSPFactories();
}

string llvm_dsp_factory_aux::writeDSPFactoryToMachineAux(const string& target)
{
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
}

string llvm_dsp_factory_aux::writeDSPFactoryToMachine(const string& target)
{
    return base64_encode(writeDSPFactoryToMachineAux(target));
}

bool llvm_dsp_factory_aux::writeDSPFactoryToMachineFile(const string& machine_code_path, const string& target)
{
    STREAM_ERROR   err;
    raw_fd_ostream out(machine_code_path.c_str(), err, sysfs_binary_flag);
    if (err) {
        cerr << "ERROR : writeDSPFactoryToMachineFile could not open file : " << err.message();
        return false;
    }
    out << writeDSPFactoryToMachineAux(target);
    out.flush();
    return true;
}

llvm_dsp_factory* llvm_dsp_factory_aux::readDSPFactoryFromMachineAux(MEMORY_BUFFER buffer, const string& target,
                                                                     string& error_msg)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    
    dsp_factory_table<SDsp_factory>::factory_iterator it;

    if (llvm_dsp_factory_aux::gLLVMFactoryTable.getFactory(sha_key, it)) {
        SDsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        vector<string>        dummy_list;
        llvm_dsp_factory_aux* factory_aux = new llvm_dsp_factory_aux(sha_key, MEMORY_BUFFER_GET(buffer).str(), target);
        if (factory_aux->initJIT(error_msg)) {
            llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
            llvm_dsp_factory_aux::gLLVMFactoryTable.setFactory(factory);
            factory->setSHAKey(sha_key);
            return factory;
        } else {
            error_msg = "ERROR : " + error_msg + "\n";
            delete factory_aux;
            return nullptr;
        }
    }
}

// machine <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const string& machine_code, const string& target, string& error_msg)
{
    LOCK_API
    return llvm_dsp_factory_aux::readDSPFactoryFromMachineAux(
        MEMORY_BUFFER_CREATE(StringRef(base64_decode(machine_code))), target, error_msg);
}

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const string& machine_code_path, const string& target,
                                                       string& error_msg)
{
    LOCK_API
    
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(machine_code_path);
    if (error_code ec = buffer.getError()) {
        error_msg = "ERROR : " + ec.message() + "\n";
        return nullptr;
    } else {
        try {
            return llvm_dsp_factory_aux::readDSPFactoryFromMachineAux(MEMORY_BUFFER_GET_REF(buffer), target, error_msg);
        } catch (faustexception& e) {
            error_msg = e.Message().data();
            return nullptr;
        }
    }
}

EXPORT string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const string& target)
{
    LOCK_API
    return factory->writeDSPFactoryToMachine(target);
}

EXPORT bool writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const string& machine_code_path,
                                         const string& target)
{
    LOCK_API
    return (factory) ? factory->writeDSPFactoryToMachineFile(machine_code_path, target) : false;
}

EXPORT bool writeDSPFactoryToObjectcodeFile(llvm_dsp_factory* factory, const string& object_code_path,
                                            const string& target)
{
    LOCK_API
    return (factory) ? factory->writeDSPFactoryToObjectcodeFile(object_code_path, target) : false;
}

// Instance
EXPORT llvm_dsp* llvm_dsp_factory::createDSPInstance()
{
    LOCK_API
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
        string options = factory->getCompileOptions();
        return strdup(options.c_str());
    } else {
        return nullptr;
    }
}

EXPORT void deleteAllCDSPFactories()
{
    deleteAllDSPFactories();
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code, const char* target, char* error_msg)
{
    string            error_msg_aux;
    llvm_dsp_factory* factory = readDSPFactoryFromMachine(machine_code, target, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

EXPORT char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const char* target)
{
    return (factory) ? strdup(writeDSPFactoryToMachine(factory, target).c_str()) : nullptr;
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path, const char* target,
                                                        char* error_msg)
{
    string            error_msg_aux;
    llvm_dsp_factory* factory = readDSPFactoryFromMachineFile(machine_code_path, target, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

EXPORT bool writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path, const char* target)
{
    return (factory) ? writeDSPFactoryToMachineFile(factory, machine_code_path, target) : false;
}

EXPORT bool writeCDSPFactoryToObjectcodeFile(llvm_dsp_factory* factory, const char* object_code_path,
                                             const char* target)
{
    return (factory) ? writeDSPFactoryToObjectcodeFile(factory, object_code_path, target) : false;
}

EXPORT void metadataCDSPInstance(llvm_dsp* dsp, MetaGlue* glue)
{
    if (dsp) {
        dsp->metadata(glue);
    }
}

EXPORT int getNumInputsCDSPInstance(llvm_dsp* dsp)
{
    return (dsp) ? dsp->getNumInputs() : -1;
}

EXPORT int getNumOutputsCDSPInstance(llvm_dsp* dsp)
{
    return (dsp) ? dsp->getNumOutputs() : -1;
}

EXPORT void initCDSPInstance(llvm_dsp* dsp, int sample_rate)
{
    if (dsp) {
        dsp->init(sample_rate);
    }
}

EXPORT void instanceInitCDSPInstance(llvm_dsp* dsp, int sample_rate)
{
    if (dsp) {
        dsp->instanceInit(sample_rate);
    }
}

EXPORT void instanceConstantsCDSPInstance(llvm_dsp* dsp, int sample_rate)
{
    if (dsp) {
        dsp->instanceConstants(sample_rate);
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
    delete dsp;
}

#ifdef __cplusplus
}
#endif
