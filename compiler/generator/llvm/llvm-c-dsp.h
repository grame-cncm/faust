/************************************************************************
 ************************************************************************
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 ************************************************************************
 ************************************************************************/

#ifndef LLVM_DSP_C_H
#define LLVM_DSP_C_H

#include <stdbool.h>

#include "faust/gui/CInterface.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
    /* Opaque types */
	
    /*!
     \addtogroup llvm C interface for compiling Faust code. Note that the API is not thread safe : use 'startMTCDSPFactories/stopMTCDSPFactories' to use it in a multi-thread context.
    @{
     */
    
    typedef struct {} llvm_dsp_factory;
    
    typedef struct {} llvm_dsp;
    
    /**
     * Get the library version.
     * 
     * @return the library version as a static string.
     */
    const char* getCLibFaustVersion();
      
    /**
     * Get the target (triple + CPU) of the machine.
     * 
     * @return the target as a string (to be deleted by the caller using freeCMemory).
     */
     char* getCDSPMachineTarget();
  
    /**
     * Get the Faust DSP factory associated with a given SHA key (created from the 'expanded' DSP source), 
     * if already allocated in the factories cache and increment it's reference counter. You will have to explicitly
     * use deleteCDSPFactory to properly decrement the reference counter when the factory is no more needed.
     *
     * @param sha_key - the SHA key for an already created factory, kept in the factory cache
     *
     * @return a valid DSP factory if one is associated with the SHA key, otherwise a null pointer.
     */
    llvm_dsp_factory* getCDSPFactoryFromSHAKey(const char* sha_key);
    
    /**
     * Create a Faust DSP factory from a DSP source code as a file. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is same source code and 
     * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will 
     * have to explicitly use deleteCDSPFactory to properly decrement reference counter when the factory is no more needed.
     *
     * @param filename - the DSP filename
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
     * @param target - the LLVM machine target (using empty string will take current machine settings)
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
     * since the maximum value may change with new LLVM versions)
     *
     * @return a valid DSP factory on success, otherwise a null pointer.
     */ 
    llvm_dsp_factory* createCDSPFactoryFromFile(const char* filename, int argc, const char* argv[], 
                                                const char* target, 
                                                char* error_msg, int opt_level);
    
    /**
     * Create a Faust DSP factory from a DSP source code as a string. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is same source code and 
     * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will 
     * have to explicitly use deleteCDSPFactory to properly decrement reference counter when the factory is no more needed.
     * 
     * @param name_app - the name of the Faust program
     * @param dsp_content - the Faust program as a string
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
     * @param target - the LLVM machine target (using empty string will take current machine settings)
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
     * since the maximum value may change with new LLVM versions)
     *
     * @return a valid DSP factory on success, otherwise a null pointer.
     */ 
    llvm_dsp_factory* createCDSPFactoryFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], 
                                                  const char* target, 
                                                  char* error_msg, int opt_level);
    
    /**
     * Delete a Faust DSP factory, that is decrements it's reference counter, possibly really deleting the internal pointer. 
     * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted with deleteCDSPInstance.
     * Beware : all kept factories and DSP pointers (in local variables...) thus become invalid. 
     * 
     * @param factory - the DSP factory to be deleted.
     *
     * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
     */                                 
    bool deleteCDSPFactory(llvm_dsp_factory* factory);
    
    /**
     *  Returns factory name :
     *  either the name declared in DSP with [declare name "foo"] syntax
     *  or 'filename' (if createDSPFactoryFromFile is used)
     *  or 'name_app' (if createDSPFactoryFromString is used)
     *
     * @param factory - the DSP factory.
     * 
     * @return the name as a string (to be deleted by the caller using freeCMemory).
     */
    char* getCName(llvm_dsp_factory* factory);

    /**
     * Get the SHA Key of the Faust DSP factory.
     *
     * @param factory - the DSP factory.
     * 
     * @return the SHA key as a string (to be deleted by the caller using freeCMemory).
     */
    char* getCSHAKey(llvm_dsp_factory* factory);
    
    /**
     * Get the expanded DSP code of the Faust DSP factory.
     *
     * @param factory - the DSP factory.
     * 
     * @return the expanded DSP code string (to be deleted by the caller using freeCMemory).
     */
    char* getCDSPCode(llvm_dsp_factory* factory);
    
    /**
     * Get the LLVM target of the Faust DSP factory.
     *
     * @param factory - the DSP factory.
     * 
     * @return the LLVM target as a string (to be deleted by the caller using freeCMemory).
     */
    char* getCTarget(llvm_dsp_factory* factory);
  
    /**
     * Get the list of library dependancies of the Faust DSP factory as a null-terminated array.
     *
     * @param factory - the DSP factory.
     * 
     * @return the library dependancies (the array and it's contain has to be deleted by the caller using freeCMemory).
     */
    const char** getCDSPFactoryLibraryList(llvm_dsp_factory* factory);
    
    /**
     * Delete all Faust DSP factories kept in the library cache. Beware : all kept factory pointers (in local variables...) thus become invalid.
     * 
     */                                 
    void deleteAllCDSPFactories();
    
    /**
     * Return Faust DSP factories of the library cache as a null-terminated array of their SHA keys.
     * 
     * @return the Faust DSP factories (the array and it's content has to be deleted by the caller using freeCMemory).
     */    
    const char** getAllCDSPFactories();
    
    /**
     * Start multi-thread access mode (since by default the library is not 'multi-thread' safe).
     * 
     * @return true if 'multi-thread' safe access is started.
     */ 
    bool startMTCDSPFactories();

    /**
     * Stop multi-thread access mode.
     * 
     */ 
    void stopMTCDSPFactories();
  
    /**
     * Create a Faust DSP factory from a base64 encoded LLVM bitcode string. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same LLVM bitcode string) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param bit_code - the LLVM bitcode string
     * @param target - the LLVM machine target (using empty string will take current machine settings)
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
     * since the maximum value may change with new LLVM versions), a higher value 
     * than the one used when calling createDSPFactory can possibly be used.
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    llvm_dsp_factory* readCDSPFactoryFromBitcode(const char* bit_code, const char* target, int opt_level);
    
    /**
     * Write a Faust DSP factory into a base64 encoded LLVM bitcode string.
     * 
     * @param factory - Faust DSP factory
     *
     * @return the LLVM bitcode as a string (to be deleted by the caller using freeCMemory).
     */
    char* writeCDSPFactoryToBitcode(llvm_dsp_factory* factory);
    
    /**
     * Create a Faust DSP factory from a LLVM bitcode file. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same LLVM bitcode file) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param bit_code_path - the LLVM bitcode file pathname
     * @param target - the LLVM machine target (using empty string will takes current machine settings)
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
     * since the maximum value may change with new LLVM versions). A higher value than the one used when 
     * calling createDSPFactory can possibly be used.
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    llvm_dsp_factory* readCDSPFactoryFromBitcodeFile(const char* bit_code_path, const char* target, int opt_level);
    
    /**
     * Write a Faust DSP factory into a LLVM bitcode file.
     * 
     * @param factory - the Faust DSP factory
     * @param bit_code_path - the LLVM bitcode file pathname
     *
     */
    void writeCDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const char* bit_code_path);
    
    /**
     * Create a Faust DSP factory from a LLVM IR (textual) string. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same LLVM IR string) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param ir_code - the LLVM IR (textual) string
     * @param target - the LLVM machine target (using empty string will takes current machine settings)
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'). 
     * A higher value than the one used when calling createDSPFactory can possibly be used
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    llvm_dsp_factory* readCDSPFactoryFromIR(const char* ir_code, const char* target, int opt_level);
    
    /**
     * Write a Faust DSP factory into a LLVM IR (textual) string.
     * 
     * @param factory - the DSP factory
     *
     * @return the LLVM IR (textual) as a string (to be deleted by the caller using freeCMemory).
     */
    char* writeCDSPFactoryToIR(llvm_dsp_factory* factory);
    
    /**
     * Create a Faust DSP factory from a LLVM IR (textual) file. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same LLVM IR file) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param ir_code_path - the LLVM IR (textual) file pathname
     * @param target - the LLVM machine target (using empty string will takes current machine settings)
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
     * since the maximum value may change with new LLVM versions). A higher value than the one used when calling 
     * createDSPFactory can possibly be used.
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    llvm_dsp_factory* readCDSPFactoryFromIRFile(const char* ir_code_path, const char* target, int opt_level);
    
    /**
     * Write a Faust DSP factory into a LLVM IR (textual) file.
     * 
     * @param factory - the Faust DSP factory
     * @param ir_code_path - the LLVM bitcode file pathname.
     *
     */
    void writeCDSPFactoryToIRFile(llvm_dsp_factory* factory, const char* ir_code_path);
    
    /**
     * Create a Faust DSP factory from a base64 encoded machine code string. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same machine code string) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param machine_code - the machine code string
     * @param target - the LLVM machine target (using empty string will takes current machine settings)
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code, const char* target);

    /**
     * Write a Faust DSP factory into a base64 encoded machine code string.
     * 
     * @param factory - the Faust DSP factory
     * @param target - the LLVM machine target (using empty string will takes current machine settings)
     *
     * @return the machine code as a string (to be deleted by the caller using freeCMemory).
     */
    char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const char* target);

    /**
     * Create a Faust DSP factory from a machine code file. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same machine code file) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param machine_code_path - the machine code file pathname
     * @param target - the LLVM machine target (using empty string will takes current machine settings)
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path, const char* target);

    /**
     * Write a Faust DSP factory into a machine code file.
     * 
     * @param factory - the Faust DSP factory
     * @param machine_code_path - the machine code file pathname
     * @param target - the LLVM machine target (using empty string will takes current machine settings).
     *
     */
    void writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path, const char* target);
    
    /**
     * Instance functions.
     */
    
    int getNumInputsCDSPInstance(llvm_dsp* dsp);
    
    int getNumOutputsCDSPInstance(llvm_dsp* dsp);
    
    void buildUserInterfaceCDSPInstance(llvm_dsp* dsp, UIGlue* interface);
    
    int getSampleRateCDSPInstance(llvm_dsp* dsp);
    
    void initCDSPInstance(llvm_dsp* dsp, int samplingRate);
    
    void instanceInitCDSPInstance(llvm_dsp* dsp, int samplingRate);
    
    void instanceConstantsCDSPInstance(llvm_dsp* dsp, int samplingRate);
    
    void instanceResetUserInterfaceCDSPInstance(llvm_dsp* dsp);
    
    void instanceClearCDSPInstance(llvm_dsp* dsp);
    
    llvm_dsp* cloneCDSPInstance(llvm_dsp* dsp);
    
    void metadataCDSPInstance(llvm_dsp* dsp, MetaGlue* meta);
    
    void computeCDSPInstance(llvm_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
    
    /* Set custom memory manager to be used when creating instances */
    void setCMemoryManager(llvm_dsp_factory* factory, ManagerGlue* manager);
    
    /**
     * Create a Faust DSP instance.
     * 
     * @param factory - the Faust DSP factory
     * 
     * @return the DSP instance on success, otherwise a null pointer.
     */
    llvm_dsp* createCDSPInstance(llvm_dsp_factory* factory);
    
    /**
     * Delete a Faust DSP instance.
     * 
     * @param dsp - the DSP instance to be deleted.
     */ 
    void deleteCDSPInstance(llvm_dsp* dsp);
    
#ifdef __cplusplus
}
#endif

/*!
 @}
 */
 
#endif
