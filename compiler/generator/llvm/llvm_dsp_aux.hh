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

#ifndef LLVM_DSP_AUX_H
#define LLVM_DSP_AUX_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/gui/CInterface.h"
#include "faust/gui/JSONUIDecoder.h"
#include "faust/gui/meta.h"

#include "dsp_aux.hh"
#include "dsp_factory.hh"
#include "export.hh"
#include "smartpointer.h"
#include "timing.hh"

#include <llvm/ExecutionEngine/ObjectCache.h>

#define LLVM_MAX_OPT_LEVEL 5

#define STREAM_ERROR std::error_code
#define MEMORY_BUFFER llvm::MemoryBufferRef
#define MEMORY_BUFFER_GET(buffer) (buffer.getBuffer())
#define MEMORY_BUFFER_GET_REF(buffer) (buffer->get()->getMemBufferRef())
#define MEMORY_BUFFER_CREATE(stringref) (llvm::MemoryBufferRef(stringref, ""))
#define ModulePTR std::unique_ptr<Module>
#define MovePTR(ptr) std::move(ptr)
#define PASS_MANAGER legacy::PassManager
#define FUNCTION_PASS_MANAGER legacy::FunctionPassManager
#define sysfs_binary_flag sys::fs::F_None
#define OwningPtr std::unique_ptr
#define llvmcreatePrintModulePass(out) createPrintModulePass(out)
#define GET_CPU_NAME llvm::sys::getHostCPUName().str()

// namespace llvm
namespace llvm {
class LLVMContext;
class ExecutionEngine;
class Module;
}  // namespace llvm

class llvm_dsp_factory;

// Public C++ interface

class EXPORT llvm_dsp : public dsp {
   private:
    llvm_dsp_factory* fFactory;
    dsp_imp*          fDSP;

   public:
    llvm_dsp(llvm_dsp_factory* factory, dsp_imp* dsp);
    virtual ~llvm_dsp();

    void operator delete(void* ptr);

    virtual int getNumInputs();

    virtual int getNumOutputs();

    virtual void buildUserInterface(UI* ui_interface);

    virtual void buildUserInterface(UIGlue* glue);

    virtual int getSampleRate();

    virtual void init(int sample_rate);

    virtual void instanceInit(int sample_rate);

    virtual void instanceConstants(int sample_rate);

    virtual void instanceResetUserInterface();

    virtual void instanceClear();

    virtual void classInit(int sample_rate);

    virtual llvm_dsp* clone();

    virtual void metadata(Meta* m);

    virtual void metadata(MetaGlue* glue);

    virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
};

class FaustObjectCache : public llvm::ObjectCache {
   private:
    std::string fMachineCode;

   public:
    FaustObjectCache(const std::string& machine_code = "") : fMachineCode(machine_code) {}

    virtual ~FaustObjectCache() {}

    virtual void notifyObjectCompiled(const llvm::Module* M, llvm::MemoryBufferRef Obj)
    {
        fMachineCode = Obj.getBuffer().str();
    }

    virtual std::unique_ptr<llvm::MemoryBuffer> getObject(const llvm::Module* M)
    {
        return (fMachineCode == "") ? NULL : llvm::MemoryBuffer::getMemBuffer(llvm::StringRef(fMachineCode));
    }

    std::string getMachineCode() { return fMachineCode; }
};

typedef class faust_smartptr<llvm_dsp_factory> SDsp_factory;

class llvm_dsp_factory_aux : public dsp_factory_imp {
    friend class llvm_dsp;

   protected:
    llvm::ExecutionEngine*  fJIT;
    FaustObjectCache*       fObjectCache;
    llvm::Module*           fModule;
    llvm::LLVMContext*      fContext;
    JSONUITemplatedDecoder* fDecoder;

    int         fOptLevel;
    std::string fTarget;
    std::string fClassName;
    std::string fTypeName;

    allocateDspFun fAllocate;
    destroyDspFun  fDestroy;
    initFun        fInstanceConstants;
    clearFun       fInstanceClear;
    classInitFun   fClassInit;
    computeFun     fCompute;
    getJSONFun     fGetJSON;

    uint64_t loadOptimize(const std::string& function);

    void init(const std::string& dsp_name, const std::string& type_name);

    bool crossCompile(const std::string& target);

    static void LLVMFatalErrorHandler(const char* reason);

    void startLLVMLibrary();
    void stopLLVMLibrary();

    std::string writeDSPFactoryToMachineAux(const std::string& target);

   public:
    llvm_dsp_factory_aux(const std::string& sha_key, llvm::Module* module, llvm::LLVMContext* context,
                         const std::string& target, int opt_level = 0);

    llvm_dsp_factory_aux(const std::string& sha_key, const std::string& machine_code, const std::string& target);

    virtual ~llvm_dsp_factory_aux();

    std::string              getCompileOptions();
    std::vector<std::string> getLibraryList();
    std::vector<std::string> getIncludePathnames();

    virtual bool initJIT(std::string& error_msg);
    bool         initJITAux(std::string& error_msg);

    static llvm_dsp_factory* readDSPFactoryFromMachineAux(MEMORY_BUFFER buffer, const std::string& target,
                                                          std::string& error_msg);

    // Bitcode
    virtual std::string writeDSPFactoryToBitcode() { return ""; }

    virtual bool writeDSPFactoryToBitcodeFile(const std::string& bit_code_path) { return false; }

    // IR
    virtual std::string writeDSPFactoryToIR() { return ""; }

    virtual bool writeDSPFactoryToIRFile(const std::string& ir_code_path) { return false; }

    // Machine
    virtual std::string writeDSPFactoryToMachine(const std::string& target);

    virtual bool writeDSPFactoryToMachineFile(const std::string& machine_code_path, const std::string& target);

    // Object
    virtual bool writeDSPFactoryToObjectcodeFile(const std::string& object_code_path, const std::string& target)
    {
        return false;
    }

    std::string getTarget();
    void        setTarget(const std::string& target) { fTarget = target; }

    int  getOptlevel();
    void setOptlevel(int opt_level)
    {
        fOptLevel = ((opt_level == -1) || (opt_level > LLVM_MAX_OPT_LEVEL)) ? LLVM_MAX_OPT_LEVEL : opt_level;
    }

    void setClassName(const std::string& class_name) { fClassName = class_name; }

    llvm_dsp* createDSPInstance(dsp_factory* factory);

    void metadata(Meta* m);

    void metadata(MetaGlue* glue);

    static int gInstance;

    static dsp_factory_table<SDsp_factory> gLLVMFactoryTable;
};

// Public C++ interface

class EXPORT llvm_dsp_factory : public dsp_factory, public faust_smartable {
   private:
    llvm_dsp_factory_aux* fFactory;

    virtual ~llvm_dsp_factory() { delete fFactory; }

   public:
    llvm_dsp_factory(llvm_dsp_factory_aux* factory) : fFactory(factory) {}
    llvm_dsp_factory(dsp_factory_base* factory) : fFactory(static_cast<llvm_dsp_factory_aux*>(factory)) {}

    std::string getName() { return fFactory->getName(); }

    std::string getSHAKey() { return fFactory->getSHAKey(); }
    void        setSHAKey(std::string sha_key) { fFactory->setSHAKey(sha_key); }

    std::string getDSPCode() { return fFactory->getDSPCode(); }
    void        setDSPCode(std::string code) { fFactory->setDSPCode(code); }

    std::string getCompileOptions() { return fFactory->getCompileOptions(); }

    std::vector<std::string> getLibraryList() { return fFactory->getLibraryList(); }
    std::vector<std::string> getIncludePathnames() { return fFactory->getIncludePathnames(); }

    std::string getTarget() { return fFactory->getTarget(); }

    llvm_dsp* createDSPInstance();

    void                setMemoryManager(dsp_memory_manager* manager) { fFactory->setMemoryManager(manager); }
    dsp_memory_manager* getMemoryManager() { return fFactory->getMemoryManager(); }

    void setMemoryManager(ManagerGlue* manager)
    {
        // To check
        fFactory->setMemoryManager(static_cast<dsp_memory_manager*>(manager->managerInterface));
    }

    void write(std::ostream* out, bool binary, bool small = false) {}

    std::string writeDSPFactoryToBitcode() { return fFactory->writeDSPFactoryToBitcode(); }

    bool writeDSPFactoryToBitcodeFile(const std::string& bit_code_path)
    {
        return fFactory->writeDSPFactoryToBitcodeFile(bit_code_path);
    }

    std::string writeDSPFactoryToIR() { return fFactory->writeDSPFactoryToIR(); }

    bool writeDSPFactoryToIRFile(const std::string& ir_code_path)
    {
        return fFactory->writeDSPFactoryToIRFile(ir_code_path);
    }

    std::string writeDSPFactoryToMachine(const std::string& target)
    {
        return fFactory->writeDSPFactoryToMachine(target);
    }

    bool writeDSPFactoryToMachineFile(const std::string& machine_code_path, const std::string& target)
    {
        return fFactory->writeDSPFactoryToMachineFile(machine_code_path, target);
    }

    bool writeDSPFactoryToObjectcodeFile(const std::string& object_code_path, const std::string& target)
    {
        return fFactory->writeDSPFactoryToObjectcodeFile(object_code_path, target);
    }

    llvm_dsp_factory_aux* getFactory() { return fFactory; }
};

EXPORT llvm_dsp_factory* getDSPFactoryFromSHAKey(const std::string& sha_key);

EXPORT bool deleteDSPFactory(llvm_dsp_factory* factory);

EXPORT std::string getDSPMachineTarget();

EXPORT std::vector<std::string> getLibraryList(llvm_dsp_factory* factory);

EXPORT std::vector<std::string> getAllDSPFactories();

EXPORT void deleteAllDSPFactories();

// machine <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code, const std::string& target,
                                                   std::string& error_msg);

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path, const std::string& target,
                                                       std::string& error_msg);

EXPORT std::string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const std::string& target);

EXPORT bool writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const std::string& machine_code_path,
                                         const std::string& target);

#ifdef __cplusplus
extern "C" {
#endif

// Public C interface

EXPORT llvm_dsp_factory* getCDSPFactoryFromSHAKey(const char* sha_key);

EXPORT bool deleteCDSPFactory(llvm_dsp_factory* factory);

EXPORT char* getCName(llvm_dsp_factory* factory);

EXPORT char* getCSHAKey(llvm_dsp_factory* factory);

EXPORT char* getCTarget(llvm_dsp_factory* factory);

EXPORT char* getCDSPCode(llvm_dsp_factory* factory);

EXPORT char* getCDSPMachineTarget();

EXPORT const char** getCDSPFactoryLibraryList(llvm_dsp_factory* factory);

EXPORT const char** getCDSPFactoryIncludePathnames(llvm_dsp_factory* factory);

EXPORT char* getCDSPFactoryCompileOptions(llvm_dsp_factory* factory);

EXPORT void deleteAllCDSPFactories();

EXPORT const char** getAllCDSPFactories();

EXPORT bool startMTCDSPFactories();

EXPORT void stopMTCDSPFactories();

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code, const char* target, char* error_msg);

EXPORT char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const char* target);

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path, const char* target,
                                                        char* error_msg);

EXPORT bool writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path, const char* target);

EXPORT bool writeCDSPFactoryToObjectcodeFile(llvm_dsp_factory* factory, const char* object_code_path,
                                             const char* target);

EXPORT void metadataCDSPInstance(llvm_dsp* dsp, MetaGlue* meta);

EXPORT int getNumInputsCDSPInstance(llvm_dsp* dsp);

EXPORT int getNumOutputsCDSPInstance(llvm_dsp* dsp);

EXPORT void buildUserInterfaceCDSPInstance(llvm_dsp* dsp, UIGlue* ui_interface);

EXPORT int getSampleRateCDSPInstance(llvm_dsp* dsp);

EXPORT void initCDSPInstance(llvm_dsp* dsp, int sample_rate);

EXPORT void instanceInitCDSPInstance(llvm_dsp* dsp, int sample_rate);

EXPORT void instanceConstantsCDSPInstance(llvm_dsp* dsp, int sample_rate);

EXPORT void instanceResetUserInterfaceCDSPInstance(llvm_dsp* dsp);

EXPORT void instanceClearCDSPInstance(llvm_dsp* dsp);

EXPORT llvm_dsp* cloneCDSPInstance(llvm_dsp* dsp);

EXPORT void computeCDSPInstance(llvm_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output);

EXPORT void setCMemoryManager(llvm_dsp_factory* factory, ManagerGlue* manager);

EXPORT llvm_dsp* createCDSPInstance(llvm_dsp_factory* factory);

EXPORT void deleteCDSPInstance(llvm_dsp* dsp);

EXPORT void generateCSHA1(const char* data, char* key);

#ifdef __cplusplus
}
#endif

#endif
