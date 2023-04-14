/************************** BEGIN llvm-dsp-c.h *****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef LLVM_DSP_C_H
#define LLVM_DSP_C_H

#include <stdbool.h>

#include "faust/gui/CInterface.h"
#include "faust/dsp/libfaust-signal-c.h"

/*!
 \addtogroup llvmc C interface for compiling Faust code with the LLVM backend.
 Note that the API is not thread safe : use 'startMTDSPFactories/stopMTDSPFactories' to use it in a multi-thread context.
 @{
 */

#ifdef __cplusplus
extern "C"
{
#endif
    
    /* Opaque types */
    
#ifdef _MSC_VER
    typedef void llvm_dsp_factory;
    typedef void llvm_dsp;
#else
    typedef struct {} llvm_dsp_factory;
    typedef struct {} llvm_dsp;
#endif
    
    /**
     * Get the library version.
     * 
     * @return the library version as a static string.
     */
    LIBFAUST_API const char* getCLibFaustVersion();
      
    /**
     * Get the target (triple + CPU) of the machine.
     * 
     * @return the target as a string (to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API char* getCDSPMachineTarget();
  
    /**
     * Get the Faust DSP factory associated with a given SHA key (created from the 'expanded' DSP source), 
     * if already allocated in the factories cache and increment it's reference counter. You will have to explicitly
     * use deleteCDSPFactory to properly decrement the reference counter when the factory is no more needed.
     *
     * @param sha_key - the SHA key for an already created factory, kept in the factory cache
     *
     * @return a valid DSP factory if one is associated with the SHA key, otherwise a null pointer.
     */
    LIBFAUST_API llvm_dsp_factory* getCDSPFactoryFromSHAKey(const char* sha_key);
    
    /**
     * Create a Faust DSP factory from a DSP source code as a file. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is same source code and 
     * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will 
     * have to explicitly use deleteCDSPFactory to properly decrement reference counter when the factory is no more needed.
     *
     * @param filename - the DSP filename
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings, 
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
     * since the maximum value may change with new LLVM versions)
     *
     * @return a valid DSP factory on success, otherwise a null pointer.
     */ 
    LIBFAUST_API llvm_dsp_factory* createCDSPFactoryFromFile(const char* filename,
                                                             int argc, const char* argv[],
                                                             const char* target,
                                                             char* error_msg,
                                                             int opt_level);

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
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
     * since the maximum value may change with new LLVM versions)
     *
     * @return a valid DSP factory on success, otherwise a null pointer.
     */ 
    LIBFAUST_API llvm_dsp_factory* createCDSPFactoryFromString(const char* name_app,
                                                               const char* dsp_content,
                                                               int argc, const char* argv[],
                                                               const char* target,
                                                               char* error_msg,
                                                               int opt_level);

    /**
     * Create a Faust DSP factory from a null terminated array of output signals.
     * It has to be used with the signal API defined in libfaust-signal-c.h.
     *
     * @param name_app - the name of the Faust program
     * @param signals - the null terminated array of output signals
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
     * since the maximum value may change with new LLVM versions)
     *
     * @return a DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API llvm_dsp_factory* createCDSPFactoryFromSignals(const char* name_app,
                                                                Signal* signals,
                                                                int argc, const char* argv[],
                                                                const char* target,
                                                                char* error_msg,
                                                                int opt_level);

    /**
     * Create a Faust DSP factory from a box expression.
     * It has to be used with the box API defined in libfaust-box-c.h.
     *
     * @param name_app - the name of the Faust program
     * @param box - the box expression
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
     * since the maximum value may change with new LLVM versions)
     *
     * @return a DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API llvm_dsp_factory* createCDSPFactoryFromBoxes(const char* name_app,
                                                            Box box,
                                                            int argc, const char* argv[],
                                                            const char* target,
                                                            char* error_msg,
                                                            int opt_level);

    /**
     * Delete a Faust DSP factory, that is decrements it's reference counter, possibly really deleting the internal pointer. 
     * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted with deleteCDSPInstance.
     * Beware: all kept factories and DSP pointers (in local variables...) thus become invalid. 
     * 
     * @param factory - the DSP factory to be deleted.
     *
     * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
     */                                 
    LIBFAUST_API bool deleteCDSPFactory(llvm_dsp_factory* factory);
    
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
    LIBFAUST_API char* getCName(llvm_dsp_factory* factory);

    /**
     * Get the SHA Key of the Faust DSP factory.
     *
     * @param factory - the DSP factory.
     * 
     * @return the SHA key as a string (to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API char* getCSHAKey(llvm_dsp_factory* factory);
    
    /**
     * Get the expanded DSP code of the Faust DSP factory.
     *
     * @param factory - the DSP factory.
     * 
     * @return the expanded DSP code string (to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API char* getCDSPCode(llvm_dsp_factory* factory);
    
    /**
     * Get the compile options of the Faust DSP factory.
     *
     * @param factory - the DSP factory.
     *
     * @return the LLVM compile options as a string (to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API char* getCDSPFactoryCompileOptions(llvm_dsp_factory* factory);
    
    /**
     * Get the LLVM target of the Faust DSP factory.
     *
     * @param factory - the DSP factory.
     * 
     * @return the LLVM target as a string (to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API char* getCTarget(llvm_dsp_factory* factory);
  
    /**
     * Get the Faust DSP factory list of library dependancies as a null-terminated array.
     *
     * @param factory - the DSP factory.
     * 
     * @return the library dependancies (the array and it's content has to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API const char** getCDSPFactoryLibraryList(llvm_dsp_factory* factory);
    
    /**
     * Get the list of all used includes as a null-terminated array.
     *
     * @param factory - the DSP factory.
     *
     * @return the includes list (the array and it's content has to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API const char** getCDSPFactoryIncludePathnames(llvm_dsp_factory* factory);
    
    /**
     * Get warning messages list for a given compilation as a null-terminated array.
     *
     * @param factory - the DSP factory.
     *
     * @return the warning messages list (the array and it's content has to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API const char** getCWarningMessages(llvm_dsp_factory* factory);

    /**
     * Delete all Faust DSP factories kept in the library cache. Beware: all kept factory pointers (in local variables...) thus become invalid.
     */                                 
    LIBFAUST_API void deleteAllCDSPFactories();
    
    /**
     * Return Faust DSP factories of the library cache as a null-terminated array of their SHA keys.
     * 
     * @return the Faust DSP factories (the array and it's content has to be deleted by the caller using freeCMemory).
     */    
    LIBFAUST_API const char** getAllCDSPFactories();
    
    
    /* Static tables initialization */
    LIBFAUST_API void classCInit(llvm_dsp_factory* factory, int sample_rate);
    
    /**
     * Start multi-thread access mode (since by default the library is not 'multi-thread' safe).
     * 
     * @return true if 'multi-thread' safe access is started.
     */ 
    LIBFAUST_API bool startMTDSPFactories();

    /**
     * Stop multi-thread access mode.
     */ 
    LIBFAUST_API void stopMTDSPFactories();
  
    /**
     * Create a Faust DSP factory from a base64 encoded LLVM bitcode string. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same LLVM bitcode string) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param bit_code - the LLVM bitcode string
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
     * since the maximum value may change with new LLVM versions), a higher value 
     * than the one used when calling createDSPFactory can possibly be used.
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API llvm_dsp_factory* readCDSPFactoryFromBitcode(const char* bit_code, const char* target, char* error_msg, int opt_level);
    
    /**
     * Write a Faust DSP factory into a base64 encoded LLVM bitcode string.
     * 
     * @param factory - Faust DSP factory
     *
     * @return the LLVM bitcode as a string (to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API char* writeCDSPFactoryToBitcode(llvm_dsp_factory* factory);
    
    /**
     * Create a Faust DSP factory from a LLVM bitcode file. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same LLVM bitcode file) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param bit_code_path - the LLVM bitcode file pathname
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
     * since the maximum value may change with new LLVM versions). A higher value than the one used when 
     * calling createDSPFactory can possibly be used.
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API llvm_dsp_factory* readCDSPFactoryFromBitcodeFile(const char* bit_code_path, const char* target, char* error_msg, int opt_level);
    
    /**
     * Write a Faust DSP factory into a LLVM bitcode file.
     * 
     * @param factory - the Faust DSP factory
     * @param bit_code_path - the LLVM bitcode file pathname
     *
     * @return true on success, false on failure.
     */
    LIBFAUST_API bool writeCDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const char* bit_code_path);
    
    /**
     * Create a Faust DSP factory from a LLVM IR (textual) string. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same LLVM IR string) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param ir_code - the LLVM IR (textual) string
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value').
     * A higher value than the one used when calling createDSPFactory can possibly be used
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API llvm_dsp_factory* readCDSPFactoryFromIR(const char* ir_code, const char* target, char* error_msg, int opt_level);
    
    /**
     * Write a Faust DSP factory into a LLVM IR (textual) string.
     * 
     * @param factory - the DSP factory
     *
     * @return the LLVM IR (textual) as a string (to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API char* writeCDSPFactoryToIR(llvm_dsp_factory* factory);
    
    /**
     * Create a Faust DSP factory from a LLVM IR (textual) file. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same LLVM IR file) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param ir_code_path - the LLVM IR (textual) file pathname
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
     * since the maximum value may change with new LLVM versions). A higher value than the one used when calling 
     * createDSPFactory can possibly be used.
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API llvm_dsp_factory* readCDSPFactoryFromIRFile(const char* ir_code_path, const char* target, char* error_msg, int opt_level);
    
    /**
     * Write a Faust DSP factory into a LLVM IR (textual) file.
     * 
     * @param factory - the Faust DSP factory
     * @param ir_code_path - the LLVM bitcode file pathname.
     *
     * @return true on success, false on failure.
     */
    LIBFAUST_API bool writeCDSPFactoryToIRFile(llvm_dsp_factory* factory, const char* ir_code_path);
    
    /**
     * Create a Faust DSP factory from a base64 encoded machine code string. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same machine code string) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param machine_code - the machine code string
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code, char* error_msg, const char* target);

    /**
     * Write a Faust DSP factory into a base64 encoded machine code string.
     * 
     * @param factory - the Faust DSP factory
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     *
     * @return the machine code as a string (to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const char* target);

    /**
     * Create a Faust DSP factory from a machine code file. Note that the library keeps an internal cache of all 
     * allocated factories so that the compilation of the same DSP code (that is the same machine code file) will return 
     * the same (reference counted) factory pointer. You will have to explicitly use deleteCDSPFactory to properly 
     * decrement reference counter when the factory is no more needed.
     * 
     * @param machine_code_path - the machine code file pathname
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path, const char* target, char* error_msg);

    /**
     * Write a Faust DSP factory into a machine code file.
     * 
     * @param factory - the Faust DSP factory
     * @param machine_code_path - the machine code file pathname
     * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
     *                 using an empty string takes the current machine settings,
     *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
     *
     * @return true on success, false on failure.
     */
    LIBFAUST_API bool writeCDSPFactoryToMachineFile(llvm_dsp_factory* factory, const char* machine_code_path, const char* target);
    
    /**
     * Instance functions.
     */
    
    LIBFAUST_API int getNumInputsCDSPInstance(llvm_dsp* dsp);
    
    LIBFAUST_API int getNumOutputsCDSPInstance(llvm_dsp* dsp);
    
    LIBFAUST_API void buildUserInterfaceCDSPInstance(llvm_dsp* dsp, UIGlue* interface);
    
    LIBFAUST_API int getSampleRateCDSPInstance(llvm_dsp* dsp);
    
    LIBFAUST_API void initCDSPInstance(llvm_dsp* dsp, int sample_rate);
    
    LIBFAUST_API void instanceInitCDSPInstance(llvm_dsp* dsp, int sample_rate);
    
    LIBFAUST_API void instanceConstantsCDSPInstance(llvm_dsp* dsp, int sample_rate);
    
    LIBFAUST_API void instanceResetUserInterfaceCDSPInstance(llvm_dsp* dsp);
    
    LIBFAUST_API void instanceClearCDSPInstance(llvm_dsp* dsp);
    
    LIBFAUST_API llvm_dsp* cloneCDSPInstance(llvm_dsp* dsp);
    
    LIBFAUST_API void metadataCDSPInstance(llvm_dsp* dsp, MetaGlue* meta);
    
    LIBFAUST_API void computeCDSPInstance(llvm_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
    
    /* Set custom memory manager to be used when creating instances */
    LIBFAUST_API void setCMemoryManager(llvm_dsp_factory* factory, MemoryManagerGlue* manager);
    
    /**
     * Create a Faust DSP instance.
     * 
     * @param factory - the Faust DSP factory
     * 
     * @return the DSP instance on success, otherwise a null pointer.
     */
    LIBFAUST_API llvm_dsp* createCDSPInstance(llvm_dsp_factory* factory);
    
    /**
     * Delete a Faust DSP instance.
     * 
     * @param dsp - the DSP instance to be deleted.
     */ 
    LIBFAUST_API void deleteCDSPInstance(llvm_dsp* dsp);
    
    /**
     * Register a custom foreign function that will be exported by the host binary running the DSP code.
     *
     * @param function_name - the function name to be available
     */
    LIBFAUST_API void registerCForeignFunction(const char* function_name);
    
#ifdef __cplusplus
}
#endif

/*!
 @}
 */
 
#endif
/************************** END llvm-dsp-c.h **************************/
