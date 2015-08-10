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
#include "base64.h"

#if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36)
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Bitcode/ReaderWriter.h>
#if defined(LLVM_35) || defined(LLVM_36)
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
#elif !defined(LLVM_33) && !defined(LLVM_34) && !defined(LLVM_35) && !defined(LLVM_36)
#ifndef _WIN32
#include <llvm/Target/TargetData.h>
#endif
#endif

#if defined(LLVM_36)
#include <llvm/ExecutionEngine/MCJIT.h>
#else
#include <llvm/ExecutionEngine/JIT.h>
#endif

#include <llvm/PassManager.h>
#if defined(LLVM_35) || defined(LLVM_36)
#include <llvm/IR/Verifier.h>
#else
#include <llvm/Analysis/Verifier.h>
#endif
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
#if defined(LLVM_35) || defined(LLVM_36)
#include <llvm/IR/LegacyPassNameParser.h>
#include <llvm/Linker/Linker.h>
#else
#include <llvm/Support/PassNameParser.h>
#include <llvm/Linker.h>
#endif
#include <llvm/Support/Host.h>
#include <llvm/Support/ManagedStatic.h>
#if defined(LLVM_35) || defined(LLVM_36)
#include <llvm/IR/IRPrintingPasses.h>
#define llvmcreatePrintModulePass(out) createPrintModulePass(out)
#else
#include <llvm/Assembly/PrintModulePass.h>
#define llvmcreatePrintModulePass(out) createPrintModulePass(&out)
#endif
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/Support/Threading.h>

#if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36)) && !defined(_MSC_VER)
#include "llvm/ExecutionEngine/ObjectCache.h"
#endif

#if defined(LLVM_35) || defined(LLVM_36)
#define OwningPtr std::unique_ptr
#endif

#include <llvm/Support/TargetSelect.h>

#if defined(LLVM_35) || defined(LLVM_36)
#include <llvm/Support/FileSystem.h>
#define sysfs_binary_flag sys::fs::F_None
#elif defined(LLVM_34)
#define sysfs_binary_flag sys::fs::F_Binary
#else
#define sysfs_binary_flag raw_fd_ostream::F_Binary
#endif

#if defined(LLVM_36)
#define STREAM_ERROR std::error_code
#define MEMORY_BUFFER MemoryBufferRef
#define MEMORY_BUFFER_GET(buffer) (buffer.getBuffer())
#define MEMORY_BUFFER_GET_REF(buffer) (buffer->get()->getMemBufferRef())
#define MEMORY_BUFFER_CREATE(stringref) (MemoryBufferRef(stringref, ""))
#define GET_CPU_NAME llvm::sys::getHostCPUName().str()

static void splitTarget(const string& target, string& triple, string& cpu)
{
    size_t pos1 = target.find_first_of(':');
    triple = target.substr(0, pos1);
    if (pos1 != string::npos) {
        cpu = target.substr(pos1 + 1);
    }
}

#else
#define STREAM_ERROR string
#define MEMORY_BUFFER MemoryBuffer*
#define MEMORY_BUFFER_GET(buffer) (buffer->getBuffer())
#define MEMORY_BUFFER_GET_REF(buffer) (buffer->get())
#define MEMORY_BUFFER_CREATE(stringref) (MemoryBuffer::getMemBuffer(stringref))
#define GET_CPU_NAME llvm::sys::getHostCPUName()
#endif

#if defined(LLVM_34) || defined(LLVM_35)  || defined(LLVM_36)
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

void ObjectCache::anchor() {}

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

void* llvm_dsp_factory::LoadOptimize(const string& function)
{
    void* fun = (void*)fJIT->getFunctionAddress(function);
    if (fun) {
        return fun;
    } else {
        stringstream error;
        error << "LoadOptimize failed for '" << function << "'";
        throw faustexception(error.str());
    }
}

std::string llvm_dsp_factory::writeDSPFactoryToMachine()
{ 
    return base64_encode((const unsigned char*)fObjectCache->getMachineCode().c_str(), fObjectCache->getMachineCode().size());
}

void llvm_dsp_factory::writeDSPFactoryToMachineFile(const std::string& machine_code_path)
{
    STREAM_ERROR err;
    raw_fd_ostream out(machine_code_path.c_str(), err, sysfs_binary_flag);
    out << fObjectCache->getMachineCode(); 
    out.flush();
}

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

bool llvm_dsp_factory::initJIT(string& error_msg)
{
    startTiming("initJIT");
       
    // For host target support
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    
    // For ObjectCache to work...
    LLVMLinkInMCJIT();
    
    // Restoring from machine code
    EngineBuilder builder(unique_ptr<Module>(fResult->fModule));
    TargetMachine* tm = builder.selectTarget();
    fJIT = builder.create(tm);
    fJIT->setObjectCache(fObjectCache);
    fJIT->finalizeObject();
    
    // Run static constructors.
    fJIT->runStaticConstructorsDestructors(false);
    fJIT->DisableLazyCompilation(true);
    
    try {
        fNew = (newDspFun)LoadOptimize("new" + fClassName);
        fDelete = (deleteDspFun)LoadOptimize("delete" + fClassName);
        fGetNumInputs = (getNumInputsFun)LoadOptimize("getNumInputs" + fClassName);
        fGetNumOutputs = (getNumOutputsFun)LoadOptimize("getNumOutputs" + fClassName);
        fBuildUserInterface = (buildUserInterfaceFun)LoadOptimize("buildUserInterface" + fClassName);
        fInit = (initFun)LoadOptimize("init" + fClassName);
        fCompute = (computeFun)LoadOptimize("compute" + fClassName);
        fMetadata = (metadataFun)LoadOptimize("metadata" + fClassName);
        endTiming("initJIT");
        return true;
     } catch (faustexception& e) { // Module does not contain the Faust entry points, or external symbol was not found...
        endTiming("initJIT");
        error_msg = e.Message();
        return false;
    }
}

llvm_dsp_factory::~llvm_dsp_factory()
{
    delete fObjectCache;

    if (fJIT) {
        fJIT->runStaticConstructorsDestructors(true);
        // fResult->fModule is kept and deleted by fJIT
        delete fJIT;
    }
    
    if (fResult) {
        delete fResult->fContext;
        free(fResult);
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

EXPORT llvm_dsp_factory* getDSPFactoryFromSHAKey(const string& sha_key)
{
    TLock lock(gDSPFactoriesLock);
    
    FactoryTableIt it;
    return (getFactory(sha_key, it)) ? (*it).first : NULL;
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

EXPORT void deleteDSPFactory(llvm_dsp_factory* factory) 
{   
    TLock lock(gDSPFactoriesLock);
    
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
    TLock lock(gDSPFactoriesLock);
    
    return factory->getName();
}

EXPORT std::string getSHAKey(llvm_dsp_factory* factory)
{
    TLock lock(gDSPFactoriesLock);
    
    return factory->getSHAKey();
}

EXPORT std::string getTarget(llvm_dsp_factory* factory)
{
    TLock lock(gDSPFactoriesLock);
    
    return factory->getTarget();
}

EXPORT std::vector<std::string> getLibraryList(llvm_dsp_factory* factory)
{
    TLock lock(gDSPFactoriesLock);
    
    return factory->getLibraryList();
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
    
static llvm_dsp_factory* readDSPFactoryFromMachineAux(MEMORY_BUFFER buffer)
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
            llvm_dsp_factory* factory = checkDSPFactory(new llvm_dsp_factory(sha_key, MEMORY_BUFFER_GET(buffer).str()), error_msg);
            llvm_dsp_factory::gFactoryTable[factory] = list<llvm_dsp_aux*>();
            return factory;
        } catch (faustexception& e) {
            e.PrintMessage();
            return NULL;
        }
    }
}

// machine <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code)
{
    TLock lock(gDSPFactoriesLock);
    
    return readDSPFactoryFromMachineAux(MEMORY_BUFFER_CREATE(StringRef(base64_decode(machine_code))));
}

EXPORT std::string writeDSPFactoryToMachine(llvm_dsp_factory* factory)
{
    TLock lock(gDSPFactoriesLock);
    
    return factory->writeDSPFactoryToMachine();
}

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path)
{
    TLock lock(gDSPFactoriesLock);
    
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(machine_code_path);
    if (std::error_code ec = buffer.getError()) {
        printf("readDSPFactoryFromMachineFile failed : %s\n", ec.message().c_str());
        return NULL;
    } else {
        return readDSPFactoryFromMachineAux(MEMORY_BUFFER_GET_REF(buffer));
     }
}

EXPORT void writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const string& machine_code_path)
{
    TLock lock(gDSPFactoriesLock);
    
    if (factory) {
        factory->writeDSPFactoryToMachineFile(machine_code_path);
    }
}

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
    TLock lock(gDSPFactoriesLock);
    
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

EXPORT llvm_dsp* llvm_dsp::copy()
{
    return reinterpret_cast<llvm_dsp*>(reinterpret_cast<llvm_dsp_aux*>(this)->copy());
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
    sha_key_list2[i] = NULL;
    return sha_key_list2;
}

EXPORT bool startMTCDSPFactories() { return startMTDSPFactories(); }

EXPORT void stopMTCDSPFactories() { stopMTDSPFactories(); }

EXPORT void deleteCDSPFactory(llvm_dsp_factory* factory)
{
    if (factory) {
        deleteDSPFactory(factory);
    }
}

EXPORT const char* getCName(llvm_dsp_factory* factory)
{
    if (factory) {
        return strdup(factory->getName().c_str());
    } else {
        return NULL;
    }
}

EXPORT const char* getCSHAKey(llvm_dsp_factory* factory)
{
    if (factory) {
        return strdup(factory->getSHAKey().c_str()); 
    } else {
        return NULL;
    }
}

EXPORT const char* getCTarget(llvm_dsp_factory* factory)
{
    if (factory) {
        return strdup(factory->getTarget().c_str()); 
    } else {
        return NULL;
    }
}

EXPORT void deleteAllCDSPFactories()
{
    deleteAllDSPFactories();
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code)
{
    return readDSPFactoryFromMachine(machine_code);
}

EXPORT const char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory)
{
    if (factory) {
        return strdup(writeDSPFactoryToMachine(factory).c_str());
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
        delete reinterpret_cast<llvm_dsp_aux*>(dsp); 
    }
}

EXPORT void generateCSHA1(const char* data, char* key)
{
    string res = generateSHA1(data);
    strncpy(key, res.c_str(), 20);
}

#endif // LLVM_BUILD

