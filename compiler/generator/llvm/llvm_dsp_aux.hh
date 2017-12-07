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

#if defined(LLVM_34) || defined(LLVM_35)  || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
    #define LLVM_MAX_OPT_LEVEL 5
#else
    #define LLVM_MAX_OPT_LEVEL 4
#endif

using namespace std;

namespace llvm
{
   class LLVMContext;
   class ExecutionEngine;
   class Module;
}

class llvm_dsp_factory;

class FaustObjectCache;

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

class llvm_dsp_factory_aux : public dsp_factory_imp {

    friend class llvm_dsp;
    
    private:
    
        llvm::ExecutionEngine* fJIT;

    #if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
        FaustObjectCache* fObjectCache;
    #endif
    
        llvm::Module* fModule;
        llvm::LLVMContext* fContext;
    
        int fOptLevel;
        string fTarget;
        string fClassName;
        string fTypeName;
    
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
    
        void* loadOptimize(const string& function);
    
        void init(const string& dsp_name, const string& type_name);
        
        bool crossCompile(const std::string& target);
      
    #if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
        static void LLVMFatalErrorHandler(const char* reason);
    #endif
    
        string writeDSPFactoryToMachineAux(const string& target);
        void startLLVMLibrary();
        void stopLLVMLibrary();
    
    public:
    
        llvm_dsp_factory_aux(const string& sha_key,
                             const std::vector<std::string>& pathname_list,
                             llvm::Module* module,
                             llvm::LLVMContext* context,
                             const string& target,
                             int opt_level = 0);
        
    #if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)) && !defined(_MSC_VER)
        llvm_dsp_factory_aux(const string& sha_key, const string& machine_code, const string& target);
    #endif
    
        virtual ~llvm_dsp_factory_aux();
    
        static llvm_dsp_factory_aux* JITFactory(llvm_dsp_factory_aux* factory, string& error_msg)
        {
            if (factory->initJIT(error_msg)) {
                return factory;
            } else {
                delete factory;
                return NULL;
            }
        }
    
        // Bitcode
        string writeDSPFactoryToBitcode();
        
        void writeDSPFactoryToBitcodeFile(const string& bit_code_path);
        
        // IR
        string writeDSPFactoryToIR();
        
        void writeDSPFactoryToIRFile(const string& ir_code_path);
        
        string writeDSPFactoryToMachine(const string& target);
        
        void writeDSPFactoryToMachineFile(const string& machine_code_path, const string& target);
        
        bool initJIT(std::string& error_msg);
    
        std::string getTarget();
        void setTarget(const std::string& target) { fTarget = target; }
    
        int getOptlevel();
        void setOptlevel(int opt_level) { fOptLevel = ((opt_level == -1) || (opt_level > LLVM_MAX_OPT_LEVEL)) ? LLVM_MAX_OPT_LEVEL : opt_level; }
    
        void setClassName(const string& class_name) { fClassName = class_name; }
    
        llvm_dsp* createDSPInstance(dsp_factory* factory);
    
        void write(std::ostream* out, bool binary, bool small = false);
    
        void metadata(Meta* m);
    
        void metadata(MetaGlue* glue);
   
        static int gInstance;
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
    
        void writeDSPFactoryToBitcodeFile(const string& bit_code_path) { fFactory->writeDSPFactoryToBitcodeFile(bit_code_path); }
    
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

EXPORT llvm_dsp_factory* createDSPFactoryFromFile(const std::string& filename, 
                                                  int argc, const char* argv[], 
                                                  const std::string& target, 
                                                  std::string& error_msg, int opt_level = -1);

EXPORT llvm_dsp_factory* createDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content,
                                                    int argc, const char* argv[], 
                                                    const std::string& target, 
                                                    std::string& error_msg, int opt_level = -1);

EXPORT bool deleteDSPFactory(llvm_dsp_factory* factory);

EXPORT std::string getDSPMachineTarget();

EXPORT std::vector<std::string> getDSPFactoryLibraryList(llvm_dsp_factory* factory);

EXPORT std::vector<std::string> getAllDSPFactories();

EXPORT void deleteAllDSPFactories();

EXPORT bool startMTDSPFactories();

EXPORT void stopMTDSPFactories();

// Bitcode <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcode(const std::string& bit_code, const std::string& target, int opt_level = 0);

EXPORT std::string writeDSPFactoryToBitcode(llvm_dsp_factory* factory);

// Bitcode <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, int opt_level = 0);

EXPORT void writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const std::string& bit_code_path);

// IR <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromIR(const std::string& ir_code, const std::string& target, int opt_level = 0);

EXPORT std::string writeDSPFactoryToIR(llvm_dsp_factory* factory);

// IR <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromIRFile(const std::string& ir_code_path, const std::string& target, int opt_level = 0);

EXPORT void writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const std::string& ir_code_path);

// machine <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code, const std::string& target);

EXPORT std::string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const std::string& target);

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path, const std::string& target);

EXPORT void writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const std::string& machine_code_path, const std::string& target);

#ifdef __cplusplus
extern "C" {
#endif

// Public C interface

EXPORT llvm_dsp_factory* getCDSPFactoryFromSHAKey(const char* sha_key);

EXPORT llvm_dsp_factory* createCDSPFactoryFromFile(const char* filename,
                                                   int argc, const char* argv[],
                                                   const char* target,
                                                   char* error_msg, int opt_level);

EXPORT llvm_dsp_factory* createCDSPFactoryFromString(const char* name_app, const char* dsp_content,
                                                    int argc, const char* argv[], 
                                                    const char* target, 
                                                    char* error_msg, int opt_level);
    
EXPORT bool deleteCDSPFactory(llvm_dsp_factory* factory);

EXPORT char* getCName(llvm_dsp_factory* factory);

EXPORT char* getCSHAKey(llvm_dsp_factory* factory);

EXPORT char* getCTarget(llvm_dsp_factory* factory);

EXPORT char* getCDSPCode(llvm_dsp_factory* factory);

EXPORT char* getCDSPMachineTarget();

EXPORT const char** getCDSPFactoryLibraryList(llvm_dsp_factory* factory);
    
EXPORT void deleteAllCDSPFactories();
    
EXPORT const char** getAllCDSPFactories();

EXPORT bool startMTCDSPFactories();

EXPORT void stopMTCDSPFactories();

EXPORT llvm_dsp_factory* readCDSPFactoryFromBitcode(const char* bit_code, const char* target, int opt_level);

EXPORT char* writeCDSPFactoryToBitcode(llvm_dsp_factory* factory);

EXPORT llvm_dsp_factory* readCDSPFactoryFromBitcodeFile(const char* bit_code_path, const char* target, int opt_level);

EXPORT void writeCDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const char* bit_code_path);

EXPORT llvm_dsp_factory* readCDSPFactoryFromIR(const char* ir_code, const char* target, int opt_level);

EXPORT char* writeCDSPFactoryToIR(llvm_dsp_factory* factory);

EXPORT llvm_dsp_factory* readCDSPFactoryFromIRFile(const char* ir_code_path, const char* target, int opt_level);

EXPORT void writeCDSPFactoryToIRFile(llvm_dsp_factory* factory, const char* ir_code_path);

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code, const char* target);

EXPORT char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const char* target);

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path, const char* target);

EXPORT void writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path, const char* target);
    
EXPORT void metadataCDSPInstance(llvm_dsp* dsp, MetaGlue* meta);

EXPORT int getNumInputsCDSPInstance(llvm_dsp* dsp);

EXPORT int getNumOutputsCDSPInstance(llvm_dsp* dsp);

EXPORT void buildUserInterfaceCDSPInstance(llvm_dsp* dsp, UIGlue* ui_interface);
    
EXPORT int getSampleRateCDSPInstance(llvm_dsp* dsp);

EXPORT void initCDSPInstance(llvm_dsp* dsp, int samplingRate);
    
EXPORT void instanceInitCDSPInstance(llvm_dsp* dsp, int samplingRate);

EXPORT void instanceConstantsCDSPInstance(llvm_dsp* dsp, int samplingRate);

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
