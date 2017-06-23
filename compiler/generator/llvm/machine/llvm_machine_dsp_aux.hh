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
 
#ifndef LLVM_DSP_AUX_H
#define LLVM_DSP_AUX_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <string>
#include <map>
#include <vector>
#include <utility>
#include "faust/gui/CInterface.h"
#include "faust/dsp/dsp.h"
#include "export.hh"
#include "smartpointer.h"
#include "TMutex.h"

using namespace std;

class llvm_dsp_aux;

struct Meta;

class llvm_dsp_factory;

typedef class SMARTP<llvm_dsp_factory> Sllvm_dsp_factory;

struct FactoryTableType : public map< Sllvm_dsp_factory, list<llvm_dsp_aux*> > 
{
    FactoryTableType() 
    {}
    virtual ~FactoryTableType() 
    {}
};

#define FactoryTableIt FactoryTableType::iterator

class FaustObjectCache;

class llvm_dsp_factory : public smartable {

    friend class llvm_dsp_aux;

    private:
    
        ExecutionEngine* fJIT;
        FaustObjectCache* fObjectCache;
        LLVMResult* fResult;
     
        int fOptLevel;
        string fExpandedDSP;
        string fTarget;
        string fClassName;
        string fSHAKey;
        string fExtName;
        bool fIsDouble;
    
        newDspFun fNew;
        deleteDspFun fDelete;
        getNumInputsFun fGetNumInputs;
        getNumOutputsFun fGetNumOutputs;
        buildUserInterfaceFun fBuildUserInterface;
        initFun fInit;
        computeFun fCompute;
        metadataFun fMetadata;
        
        int getOptlevel();
        void* loadOptimize(const string& function);
         
        static int gInstance;
                   
  public:
  
        llvm_dsp_factory(const string& sha_key, const string& machine_code, const string& target);
      
        virtual ~llvm_dsp_factory();
      
        llvm_dsp_aux* createDSPInstance();
        
        bool initJIT(std::string& error_msg);
        
        void metadataDSPFactory(Meta* meta);
        
        void metadataDSPFactory(MetaGlue* glue);
    
        string getName();
        
        string getSHAKey();
    
        string getDSPCode();
    
        string getTarget();
    
        vector<std::string> getLibraryList() { return fResult->fPathnameList; }
    
        static FactoryTableType gFactoryTable;
       
};

class llvm_dsp_aux : public dsp {

    friend class llvm_dsp_factory;
   
    private:

        llvm_dsp_factory* fDSPFactory;
        llvm_dsp_imp* fDSP;
                 
    public:
        
        llvm_dsp_aux(llvm_dsp_factory* factory, llvm_dsp_imp* dsp);
        virtual ~llvm_dsp_aux();
    
        void metadata(Meta* m);
        void metadata(MetaGlue* m);
     
        virtual int getNumInputs();
        virtual int getNumOutputs();
    
        virtual void init(int samplingFreq);
      
        virtual void buildUserInterface(UI* ui_interface);
        virtual void buildUserInterface(UIGlue* glue);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
        
        virtual llvm_dsp_aux* copy();
    
        llvm_dsp_factory* getFactory() { return fDSPFactory; }
       
};

// Public C++ interface using LLVM

EXPORT llvm_dsp_factory* getDSPFactoryFromSHAKey(const std::string& sha_key);

EXPORT llvm_dsp_factory* createDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content,
                                                    int argc, const char* argv[],
                                                    const std::string& target,
                                                    std::string& error_msg, int opt_level = -1);


EXPORT bool deleteDSPFactory(llvm_dsp_factory* factory);

EXPORT std::string getDSPMachineTarget();

EXPORT std::vector<std::string> getLibraryList(llvm_dsp_factory* factory);

EXPORT std::vector<std::string> getAllDSPFactories();

EXPORT void deleteAllDSPFactories();

EXPORT bool startMTDSPFactories();

EXPORT void stopMTDSPFactories();

// machine <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code, const std::string& target);

// machine <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path, const std::string& target);

class EXPORT llvm_dsp : public dsp {
                
    public:
    
        void metadata(Meta* m);
     
        virtual int getNumInputs();
        virtual int getNumOutputs();
    
        virtual void init(int samplingFreq);
      
        virtual void buildUserInterface(UI* ui_interface);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
        
        virtual llvm_dsp* copy();
     
};

EXPORT void deleteDSPInstance(llvm_dsp* dsp);

#ifdef __cplusplus
extern "C" {
#endif

// Public C interface using LLVM

EXPORT llvm_dsp_factory* getCDSPFactoryFromSHAKey(const char* sha_key);
    
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

EXPORT const char** getCLibraryList(llvm_dsp_factory* factory);
    
EXPORT void deleteAllCDSPFactories();
    
EXPORT const char** getAllCDSPFactories();

EXPORT bool startMTCDSPFactories();

EXPORT void stopMTCDSPFactories();

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code, const char* target);

EXPORT llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path, const char* target);
    
EXPORT char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const char* target);

EXPORT void writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path, const char* target);

EXPORT void metadataCDSPFactory(llvm_dsp_factory* factory, MetaGlue* meta);
    
EXPORT void metadataCDSPInstance(llvm_dsp* dsp, MetaGlue* meta);

EXPORT int getNumInputsCDSPInstance(llvm_dsp* dsp);

EXPORT int getNumOutputsCDSPInstance(llvm_dsp* dsp);

EXPORT void initCDSPInstance(llvm_dsp* dsp, int samplingFreq);

EXPORT void buildUserInterfaceCDSPInstance(llvm_dsp* dsp, UIGlue* ui_interface);

EXPORT void computeCDSPInstance(llvm_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output);

EXPORT llvm_dsp* copyCDSPInstance(llvm_dsp* dsp);

EXPORT llvm_dsp* createCDSPInstance(llvm_dsp_factory* factory);

EXPORT void deleteCDSPInstance(llvm_dsp* dsp);

EXPORT void generateCSHA1(const char* data, char* key);

EXPORT void freeCMemory(void* ptr);

#ifdef __cplusplus
}
#endif

#endif
