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

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <string>
#include <map>
#include <vector>
#include <utility>
#include "faust/gui/CUI.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "export.hh"
#include "libfaust.h"
#include "smartpointer.h"
#include "dsp_aux.hh"
#include "TMutex.h"

using namespace std;

class FaustObjectCache;

class EXPORT llvm_dsp : public dsp {
    
public:
    
    int getNumInputs();
    int getNumOutputs();
    
    void metadata(Meta* m);
    
    void init(int samplingRate);
    void instanceInit(int samplingRate);
    
    int getSampleRate();
    
    void buildUserInterface(UI* ui_interface);
    
    void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
    
    llvm_dsp* clone();
    
};

class EXPORT llvm_dsp_factory : public dsp_factory, public smartable {

    friend class llvm_dsp_aux;
    
    private:
    
        ExecutionEngine* fJIT;

    #if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38)) && !defined(_MSC_VER)
        FaustObjectCache* fObjectCache;
    #endif
        LLVMResult* fResult;
     
        int fOptLevel;
        string fExpandedDSP;
        string fTarget;
        string fClassName;
        string fSHAKey;
        string fTypeName; 
        string fDSPName;
        bool fIsDouble;
    
        newDspFun fNew;
        deleteDspFun fDelete;
        getNumInputsFun fGetNumInputs;
        getNumOutputsFun fGetNumOutputs;
        buildUserInterfaceFun fBuildUserInterface;
        initFun fInit;
        initFun fInstanceInit;
        getSampleRateFun fGetSampleRate;
        computeFun fCompute;
        metadataFun fMetadata;
        
        int getOptlevel();
        
        void* loadOptimize(const string& function);
        
        LLVMResult* compileModule(int argc, 
                                const char* argv[], 
                                const char* input_name, 
                                const char* input, 
                                string& error_msg);
        void init(const string& dsp_name, const string& type_name);
        
        bool crossCompile(const std::string& target);
      
    #if defined(LLVM_33) || defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38)
        static void LLVMFatalErrorHandler(const char* reason);
    #endif
    
        string writeDSPFactoryToMachineAux(const string& target);
    

  
    protected:
    
        virtual ~llvm_dsp_factory();
                   
    public:
  
        llvm_dsp_factory(const string& sha_key, int argc, const char* argv[], 
                        const string& name, 
                        const string& dsp_content, const string& expendand_dsp_content,
                        const string& target, 
                        string& error_msg, int opt_level = -1);
              
        llvm_dsp_factory(const string& sha_key, Module* module, LLVMContext* context, const string& target, int opt_level = 0);
        
    #if (defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38)) && !defined(_MSC_VER)
        llvm_dsp_factory(const string& sha_key, const string& machine_code, const string& target);
    #endif
      
        static llvm_dsp_factory* checkDSPFactory(llvm_dsp_factory* factory, string& error_msg)
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
    
        EXPORT string getTarget();
        void setTarget(const string target) { fTarget = target; }
    
        vector<std::string> getDSPFactoryLibraryList() { return fResult->fPathnameList; }
    
        EXPORT string getName();
    
        EXPORT string getSHAKey();
    
        void setSHAKey(std::string sha_key) { fSHAKey = sha_key; }
    
        EXPORT string getDSPCode();
    
        EXPORT llvm_dsp* createDSPInstance();
   
        static int gInstance;
};

class llvm_dsp_aux : public dsp {

    friend class llvm_dsp_factory;
   
    private:

        llvm_dsp_factory* fFactory;
        llvm_dsp_imp* fDSP;
                 
    public:
        
        llvm_dsp_aux(llvm_dsp_factory* factory, llvm_dsp_imp* dsp);
        virtual ~llvm_dsp_aux();
    
        void metadata(Meta* m);
        void metadata(MetaGlue* glue);
    
        virtual int getNumInputs();
        virtual int getNumOutputs();
    
        virtual void init(int samplingRate);
        virtual void instanceInit(int samplingRate);
    
        virtual int getSampleRate();
      
        virtual void buildUserInterface(UI* ui_interface);
        virtual void buildUserInterface(UIGlue* glue);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
        
        virtual llvm_dsp_aux* clone();
    
        llvm_dsp_factory* getFactory() { return fFactory; }
    
};

// Public C++ interface

EXPORT std::string getLibFaustVersion();

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

EXPORT char* getCLibFaustVersion();

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

EXPORT void initCDSPInstance(llvm_dsp* dsp, int samplingRate);
    
EXPORT void instanceInitCDSPInstance(llvm_dsp* dsp, int samplingRate);

EXPORT void buildUserInterfaceCDSPInstance(llvm_dsp* dsp, UIGlue* ui_interface);

EXPORT void computeCDSPInstance(llvm_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output);

EXPORT llvm_dsp* cloneCDSPInstance(llvm_dsp* dsp);

EXPORT llvm_dsp* createCDSPInstance(llvm_dsp_factory* factory);

EXPORT void deleteCDSPInstance(llvm_dsp* dsp);

EXPORT void generateCSHA1(const char* data, char* key);

EXPORT void freeCDSP(const char* ptr);

#ifdef __cplusplus
}
#endif

#endif
