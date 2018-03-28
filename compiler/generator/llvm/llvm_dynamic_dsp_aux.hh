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
 
#ifndef LLVM_DYNAMIC_DSP_AUX_H
#define LLVM_DYNAMIC_DSP_AUX_H

#include "llvm_dsp_aux.hh"

class llvm_dynamic_dsp_factory_aux : public llvm_dsp_factory_aux {
    
 
    public:
    
        llvm_dynamic_dsp_factory_aux(const std::string& sha_key,
                                     const std::vector<std::string>& pathname_list,
                                     llvm::Module* module,
                                     llvm::LLVMContext* context,
                                     const std::string& target,
                                     int opt_level = 0);
    
        llvm_dynamic_dsp_factory_aux(const std::string& sha_key,
                                     const std::string& machine_code,
                                     const std::string& target)
        :llvm_dsp_factory_aux(sha_key, machine_code, target)
        {}
    
        virtual bool initJIT(std::string& error_msg);
    
        void write(std::ostream* out, bool binary, bool small = false);
    
        // Bitcode
        std::string writeDSPFactoryToBitcode();
        
        void writeDSPFactoryToBitcodeFile(const std::string& bit_code_path);
        
        // IR
        virtual std::string writeDSPFactoryToIR();
        
        virtual void writeDSPFactoryToIRFile(const std::string& ir_code_path);
    
};

EXPORT llvm_dsp_factory* createDSPFactoryFromFile(const std::string& filename,
                                                  int argc, const char* argv[],
                                                  const std::string& target,
                                                  std::string& error_msg, int opt_level = -1);

EXPORT llvm_dsp_factory* createDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content,
                                                    int argc, const char* argv[],
                                                    const std::string& target,
                                                    std::string& error_msg, int opt_level = -1);

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

EXPORT std::string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const std::string& target);

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
