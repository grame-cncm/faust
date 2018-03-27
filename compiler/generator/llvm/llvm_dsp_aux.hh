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
 
#ifndef LLVM_DSP_AUX_H
#define LLVM_DSP_AUX_H

#include <string>
#include <map>
#include <vector>
#include <utility>

#include "faust/gui/CInterface.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"

#include "export.hh"
#include "smartpointer.h"
#include "dsp_aux.hh"
#include "dsp_factory.hh"
#include "TMutex.h"

#if defined(LLVM_35) || defined(LLVM_38)
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include <llvm/ExecutionEngine/ObjectCache.h>

#define LLVM_MAX_OPT_LEVEL 5

#if defined(LLVM_35)
#define STREAM_ERROR string
#define MEMORY_BUFFER MemoryBuffer*
#define MEMORY_BUFFER_GET(buffer) (buffer->getBuffer())
#define MEMORY_BUFFER_GET_REF(buffer) (buffer->get())
#define MEMORY_BUFFER_CREATE(stringref) (MemoryBuffer::getMemBuffer(stringref))
#define ModulePTR Module*
#define MovePTR(ptr) ptr
#define PASS_MANAGER legacy::PassManager
#define FUNCTION_PASS_MANAGER FunctionPassManager
#else
#define STREAM_ERROR std::error_code
#define MEMORY_BUFFER MemoryBufferRef
#define MEMORY_BUFFER_GET(buffer) (buffer.getBuffer())
#define MEMORY_BUFFER_GET_REF(buffer) (buffer->get()->getMemBufferRef())
#define MEMORY_BUFFER_CREATE(stringref) (MemoryBufferRef(stringref, ""))
#define ModulePTR std::unique_ptr<Module>
#define MovePTR(ptr) std::move(ptr)
#define PASS_MANAGER legacy::PassManager
#define FUNCTION_PASS_MANAGER legacy::FunctionPassManager
#endif

#define sysfs_binary_flag sys::fs::F_None
#define OwningPtr std::unique_ptr
#define llvmcreatePrintModulePass(out) createPrintModulePass(out)
#define GET_CPU_NAME llvm::sys::getHostCPUName().str()

namespace llvm
{
   class LLVMContext;
   class ExecutionEngine;
   class Module;
}

class llvm_dsp_factory;

// Public C++ interface

class EXPORT llvm_dsp : public dsp {
    
    private:
        
        llvm_dsp_factory* fFactory;
        dsp_imp* fDSP;
    
    public:
        
        llvm_dsp(llvm_dsp_factory* factory, dsp_imp* dsp);
        virtual ~llvm_dsp();
    
        void operator delete(void* ptr);
    
        virtual int getNumInputs();
        
        virtual int getNumOutputs();
        
        virtual void buildUserInterface(UI* ui_interface);
        
        virtual void buildUserInterface(UIGlue* glue);
        
        virtual int getSampleRate();
        
        virtual void init(int samplingRate);
        
        virtual void instanceInit(int samplingRate);
        
        virtual void instanceConstants(int samplingRate);
        
        virtual void instanceResetUserInterface();
        
        virtual void instanceClear();
        
        virtual llvm_dsp* clone();
        
        virtual void metadata(Meta* m);
        
        virtual void metadata(MetaGlue* glue);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
    
};

#ifndef LLVM_35
class FaustObjectCache : public llvm::ObjectCache {
    
    private:
        
        std::string fMachineCode;
        
    public:
        
        FaustObjectCache(const std::string& machine_code = "") : fMachineCode(machine_code)
        {}
        
        virtual ~FaustObjectCache()
        {}
        
        virtual void notifyObjectCompiled(const llvm::Module *M, llvm::MemoryBufferRef Obj)
        {
            fMachineCode = Obj.getBuffer().str();
        }
        
        virtual std::unique_ptr<llvm::MemoryBuffer> getObject(const llvm::Module* M)
        {
            return (fMachineCode == "") ? NULL : llvm::MemoryBuffer::getMemBuffer(llvm::StringRef(fMachineCode));
        }
        
        std::string getMachineCode() { return fMachineCode; }
    
};
#endif

typedef class faust_smartptr<llvm_dsp_factory> SDsp_factory;

class llvm_dsp_factory_aux : public dsp_factory_imp {

    friend class llvm_dsp;
    
    protected:
    
        llvm::ExecutionEngine* fJIT;

    #ifndef LLVM_35
        FaustObjectCache* fObjectCache;
    #endif
        llvm::Module* fModule;
        llvm::LLVMContext* fContext;
    
        int fOptLevel;
        std::string fTarget;
        std::string fClassName;
        std::string fTypeName;
    
        newDspFun fNew;
        deleteDspFun fDelete;
        getNumInputsFun fGetNumInputs;
        getNumOutputsFun fGetNumOutputs;
        getSizeFun fGetSize;
        buildUserInterfaceFun fBuildUserInterface;
        initFun fInit;
        initFun fInstanceInit;
        initFun fInstanceConstants;
        clearFun fInstanceResetUI;
        clearFun fInstanceClear;
        getSampleRateFun fGetSampleRate;
        computeFun fCompute;
        metadataFun fMetadata;
        getSampleSizeFun fGetSampleSize;
    
        void* loadOptimize(const std::string& function);
    
        void init(const std::string& dsp_name, const std::string& type_name);
    
        bool crossCompile(const std::string& target);
    
        static void LLVMFatalErrorHandler(const char* reason);
    
        void startLLVMLibrary();
        void stopLLVMLibrary();
    
        std::string writeDSPFactoryToMachineAux(const std::string& target);
    
    public:
    
        llvm_dsp_factory_aux(const std::string& sha_key,
                             const std::vector<std::string>& pathname_list,
                             llvm::Module* module,
                             llvm::LLVMContext* context,
                             const std::string& target,
                             int opt_level = 0);
        
        llvm_dsp_factory_aux(const std::string& sha_key, const std::string& machine_code, const std::string& target);

        llvm_dsp_factory_aux(const std::string& name,
                            const std::string& sha_key,
                            const std::string& dsp,
                            const std::vector<std::string>& pathname_list)
        :dsp_factory_imp(name, sha_key, dsp, pathname_list)
        {}
    
        virtual ~llvm_dsp_factory_aux();
    
        virtual bool initJIT(std::string& error_msg);
    
        // Bitcode
        virtual std::string writeDSPFactoryToBitcode() { return ""; }
        
        virtual void writeDSPFactoryToBitcodeFile(const std::string& bit_code_path) {}
        
        // IR
        virtual std::string writeDSPFactoryToIR() { return ""; }
        
        virtual void writeDSPFactoryToIRFile(const std::string& ir_code_path) {}
    
        // Machine
        virtual std::string writeDSPFactoryToMachine(const std::string& target);
    
        virtual void writeDSPFactoryToMachineFile(const std::string& machine_code_path, const std::string& target);
    
        std::string getTarget();
        void setTarget(const std::string& target) { fTarget = target; }
    
        int getOptlevel();
        void setOptlevel(int opt_level) { fOptLevel = ((opt_level == -1) || (opt_level > LLVM_MAX_OPT_LEVEL)) ? LLVM_MAX_OPT_LEVEL : opt_level; }
    
        void setClassName(const std::string& class_name) { fClassName = class_name; }
    
        llvm_dsp* createDSPInstance(dsp_factory* factory);
    
        void metadata(Meta* m);
    
        void metadata(MetaGlue* glue);
   
        static int gInstance;
    
        static TLockAble* gDSPFactoriesLock;
    
        static dsp_factory_table<SDsp_factory> gLLVMFactoryTable;

};

// Public C++ interface

class EXPORT llvm_dsp_factory : public dsp_factory, public faust_smartable {
    
    private:
    
        llvm_dsp_factory_aux* fFactory;
     
        virtual ~llvm_dsp_factory()
        {
            delete fFactory;
        }
        
    public:
        
        llvm_dsp_factory(llvm_dsp_factory_aux* factory):fFactory(factory)
        {}
        llvm_dsp_factory(dsp_factory_base* factory):fFactory(static_cast<llvm_dsp_factory_aux*>(factory))
        {}
    
        std::string getName() { return fFactory->getName(); }
        
        std::string getSHAKey() { return fFactory->getSHAKey(); }
        void setSHAKey(std::string sha_key) { fFactory->setSHAKey(sha_key); }
        
        std::string getDSPCode() { return fFactory->getDSPCode(); }
        void setDSPCode(std::string code) { fFactory->setDSPCode(code); }
    
        std::string getTarget() { return fFactory->getTarget(); }
        
        llvm_dsp* createDSPInstance();
    
        void setMemoryManager(dsp_memory_manager* manager) { fFactory->setMemoryManager(manager); }
        dsp_memory_manager* getMemoryManager() { return fFactory->getMemoryManager(); }
    
        void setMemoryManager(ManagerGlue* manager)
        {
            // To check
            fFactory->setMemoryManager(static_cast<dsp_memory_manager*>(manager->managerInterface));
        }
    
        void write(std::ostream* out, bool binary, bool small = false) {}
        
        std::vector<std::string> getDSPFactoryLibraryList() { return fFactory->getDSPFactoryLibraryList(); }
    
        std::string writeDSPFactoryToBitcode() { return fFactory->writeDSPFactoryToBitcode(); }
    
        void writeDSPFactoryToBitcodeFile(const std::string& bit_code_path) { fFactory->writeDSPFactoryToBitcodeFile(bit_code_path); }
    
        std::string writeDSPFactoryToIR() { return fFactory->writeDSPFactoryToIR(); }
    
        void writeDSPFactoryToIRFile(const std::string& ir_code_path) { fFactory->writeDSPFactoryToIRFile(ir_code_path); }
    
        std::string writeDSPFactoryToMachine(const std::string& target) { return fFactory->writeDSPFactoryToMachine(target); }
    
        void writeDSPFactoryToMachineFile(const std::string& machine_code_path, const std::string& target)
        {
            fFactory->writeDSPFactoryToMachineFile(machine_code_path, target);
        }
    
        llvm_dsp_factory_aux* getFactory() { return fFactory; }

};

EXPORT llvm_dsp_factory* getDSPFactoryFromSHAKey(const std::string& sha_key);

EXPORT bool deleteDSPFactory(llvm_dsp_factory* factory);

EXPORT std::string getDSPMachineTarget();

EXPORT std::vector<std::string> getDSPFactoryLibraryList(llvm_dsp_factory* factory);

EXPORT std::vector<std::string> getAllDSPFactories();

EXPORT void deleteAllDSPFactories();

EXPORT bool startMTDSPFactories();

EXPORT void stopMTDSPFactories();

// machine <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code, const std::string& target);

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path, const std::string& target);

#endif
