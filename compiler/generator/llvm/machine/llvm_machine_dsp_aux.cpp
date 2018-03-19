/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#ifndef _WIN32
#include <libgen.h>
#endif

#include "llvm_machine_dsp_aux.hh"
#include "faust/gui/CGlue.h"
#include "exception.hh"
#include "rn_base64.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <system_error>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/IR/LegacyPassNameParser.h>
#include <llvm/Support/Host.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/Support/Threading.h>
#include "llvm/ExecutionEngine/ObjectCache.h"
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/FileSystem.h>

#define OwningPtr std::unique_ptr
#define sysfs_binary_flag sys::fs::F_None

#define STREAM_ERROR std::error_code
#define MEMORY_BUFFER MemoryBufferRef
#define MEMORY_BUFFER_GET(buffer) (buffer.getBuffer())
#define MEMORY_BUFFER_GET_REF(buffer) (buffer->get()->getMemBufferRef())
#define MEMORY_BUFFER_CREATE(stringref) (MemoryBufferRef(stringref, ""))
#define GET_CPU_NAME llvm::sys::getHostCPUName().str()
#define LLVM_MAX_OPT_LEVEL 5

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

void* llvm_dsp_factory::loadOptimize(const string& function)
{
    void* fun = (void*)fJIT->getFunctionAddress(function);
    if (fun) {
        return fun;
    } else {
        stringstream error;
        error << "ERROR : loadOptimize failed for '" << function << "'";
        throw faustexception(error.str());
    }
}

llvm_dsp_factory::llvm_dsp_factory(const string& sha_key, const string& machine_code, const string& target)
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
    fExtName = "MachineDSP";
    fTarget = (target == "") ? fTarget = (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME) : target;
    fSHAKey = sha_key;
    
    fObjectCache = new FaustObjectCache(machine_code);
    
    // Creates module and context
    fResult = static_cast<LLVMResult*>(calloc(1, sizeof(LLVMResult)));
    fResult->fContext = new LLVMContext();
    fResult->fModule = new Module(LVVM_BACKEND_NAME, *fResult->fContext);
}

llvm_dsp_aux* llvm_dsp_factory::createDSPInstance()
{
    faustassert(fResult->fModule);
    faustassert(fJIT);
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
    // For host target support
    InitializeNativeTarget();
     
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
        fNew = (newDspFun)loadOptimize("new" + fClassName);
        fDelete = (deleteDspFun)loadOptimize("delete" + fClassName);
        fGetNumInputs = (getNumInputsFun)loadOptimize("getNumInputs" + fClassName);
        fGetNumOutputs = (getNumOutputsFun)loadOptimize("getNumOutputs" + fClassName);
        fBuildUserInterface = (buildUserInterfaceFun)loadOptimize("buildUserInterface" + fClassName);
        fInit = (initFun)loadOptimize("init" + fClassName);
        fCompute = (computeFun)loadOptimize("compute" + fClassName);
        fMetadata = (metadataFun)loadOptimize("metadata" + fClassName);
        return true;
    } catch (faustexception& e) { // Module does not contain the Faust entry points, or external symbol was not found...
        error_msg = e.Message();
        return false;
    }
}

llvm_dsp_factory::~llvm_dsp_factory()
{
    if (fJIT) {
        fJIT->runStaticConstructorsDestructors(true);
        // fResult->fModule is kept and deleted by fJIT
        delete fJIT;
    }
    
    if (fResult) {
        delete fResult->fContext;
        free(fResult);
    }
    
    delete fObjectCache;
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
    faustassert(fDSPFactory);
    faustassert(fDSP);
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

EXPORT llvm_dsp_factory* createDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content,
                                                    int argc, const char* argv[],
                                                    const std::string& target,
                                                    std::string& error_msg, int opt_level) 
{ 
    return NULL; 
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
        
        virtual void declare(const char* key, const char* value){
            if (strcmp(key, "name") == 0) {
                name = value;
            }
        }
        
    };
    
    MyMeta metadata;
    metadataDSPFactory(&metadata);
    return (fExtName != "") ? fExtName : metadata.name;
}

EXPORT std::string llvm_dsp_factory::getSHAKey() { return fSHAKey; }

EXPORT std::string llvm_dsp_factory::getDSPCode() { return fExpandedDSP; }

EXPORT std::string llvm_dsp_factory::getTarget() { return fTarget; }

EXPORT std::string getDSPMachineTarget()
{
    return (llvm::sys::getDefaultTargetTriple() + ":" + GET_CPU_NAME);
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

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path, const std::string& target)
{
    TLock lock(gDSPFactoriesLock);
    
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(machine_code_path);
    if (std::error_code ec = buffer.getError()) {
        printf("readDSPFactoryFromMachineFile failed : %s\n", ec.message().c_str());
        return NULL;
    } else {
        return readDSPFactoryFromMachineAux(MEMORY_BUFFER_GET_REF(buffer), target);
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
        faustassert(it != llvm_dsp_factory::gFactoryTable.end());
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

EXPORT llvm_dsp_factory* createCDSPFactoryFromString(const char* name_app, const char* dsp_content,
                                                     int argc, const char* argv[],
                                                     const char* target,
                                                     char* error_msg, int opt_level)
{
    return NULL;
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
    return (factory) ? strdup(factory->getName().c_str()) : NULL;
}

EXPORT char* getCSHAKey(llvm_dsp_factory* factory)
{
    return (factory) ? strdup(factory->getSHAKey().c_str()) : NULL;
}

EXPORT char* getCDSPCode(llvm_dsp_factory* factory)
{
    return (factory) ? strdup(factory->getDSPCode().c_str()) : NULL;
}

EXPORT char* getCTarget(llvm_dsp_factory* factory)
{
    return (factory) ? strdup(factory->getTarget().c_str()) : NULL;
}

EXPORT char* getCDSPMachineTarget()
{
    return strdup(getDSPMachineTarget().c_str());
}

EXPORT void deleteAllCDSPFactories()
{
    deleteAllDSPFactories();
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code, const char* target)
{
    return readDSPFactoryFromMachine(machine_code, target);
}

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path, const char* target)
{
    return readDSPFactoryFromMachineFile(machine_code_path, target);
}

EXPORT char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const char* target)
{
     return NULL;
}

EXPORT void writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path, const char* target)
{}

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

EXPORT string generateSHA1(const string& dsp_content)
{
    // compute SHA1 key
    unsigned char obuf[20];
    SHA1((const unsigned char*)dsp_content.c_str(), dsp_content.size(), obuf);
    
    // convert SHA1 key into hexadecimal string
    string sha1key;
    for (int i = 0; i < 20; i++) {
        const char* H = "0123456789ABCDEF";
        char c1 = H[(obuf[i] >> 4)];
        char c2 = H[(obuf[i] & 15)];
        sha1key += c1;
        sha1key += c2;
    }
    
    return sha1key;
}

EXPORT void generateCSHA1(const char* data, char* sha_key)
{
    string res = generateSHA1(data);
    strncpy(sha_key, res.c_str(), 64);
}

EXPORT void freeCMemory(void* ptr)
{
    free(ptr);
}
