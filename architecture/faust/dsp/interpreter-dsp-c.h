/************************** BEGIN interpreter-dsp-c.h **********************
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
************************************************************************/

#ifndef INTERPRETER_DSP_C_H
#define INTERPRETER_DSP_C_H

#include <stdbool.h>

#include "faust/gui/CInterface.h"
#include "faust/dsp/libfaust-signal-c.h"
#include "faust/dsp/libfaust-box-c.h"

/*!
 \addtogroup interpreter C interface for compiling Faust code with the Interpreter backend.
 Note that the API is not thread safe: use 'startMTDSPFactories/stopMTDSPFactories' to use it in a multi-thread context.
 @{
 */

#ifdef __cplusplus
extern "C"
{
#endif
    
    /* Opaque types */
    
#ifdef _MSC_VER
    typedef void interpreter_dsp_factory;
    typedef void interpreter_dsp;
#else
    typedef struct {} interpreter_dsp_factory;
    typedef struct {} interpreter_dsp;
#endif
    
    /**
     * Get the library version.
     *
     * @return the library version as a static string.
     */
    LIBFAUST_API const char* getCLibFaustVersion();

    /**
     * Get the Faust DSP factory associated with a given SHA key (created from the 'expanded' DSP source),
     * if already allocated in the factories cache and increment it's reference counter. You will have to explicitly
     * use deleteInterpreterDSPFactory to properly decrement reference counter when the factory is no more needed.
     *
     * @param sha_key - the SHA key for an already created factory, kept in the factory cache
     *
     * @return a valid DSP factory if one is associated with the SHA key, otherwise a null pointer.
     */
    LIBFAUST_API interpreter_dsp_factory* getCInterpreterDSPFactoryFromSHAKey(const char* sha_key);

    /**
     * Create a Faust DSP factory from a DSP source code as a file. Note that the library keeps an internal cache of all
     * allocated factories so that the compilation of same DSP code (that is same source code and
     * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will have to explicitly
     * use deleteInterpreterDSPFactory to properly decrement reference counter when the factory is no more needed.
     *
     * @param filename - the DSP filename
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     *
     * @return a DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API interpreter_dsp_factory* createCInterpreterDSPFactoryFromFile(const char* filename,
                                                                            int argc, const char* argv[],
                                                                            char* error_msg);

    /**
     * Create a Faust DSP factory from a DSP source code as a string. Note that the library keeps an internal cache of all
     * allocated factories so that the compilation of same DSP code (that is same source code and
     * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will have to explicitly
     * use deleteInterpreterDSPFactory to properly decrement reference counter when the factory is no more needed.
     *
     * @param name_app - the name of the Faust program
     * @param dsp_content - the Faust program as a string
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     *
     * @return a DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API interpreter_dsp_factory* createCInterpreterDSPFactoryFromString(const char* name_app,
                                                                             const char* dsp_content,
                                                                             int argc, const char* argv[],
                                                                             char* error_msg);

    /**
     * Create a Faust DSP factory from a vector of output signals.
     * It has to be used with the signal API defined in libfaust-signal-c.h.
     *
     * @param name_app - the name of the Faust program
     * @param signals - the vector of output signals (that will internally be converted in normal form, see CsimplifyToNormalForm in libfaust-signal-c.h)
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     *
     * @return a DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API interpreter_dsp_factory* createCInterpreterDSPFactoryFromSignals(const char* name_app,
                                                                                Signal* signals,
                                                                                int argc, const char* argv[],
                                                                                char* error_msg);

    /**
     * Create a Faust DSP factory from a box expression.
     * It has to be used with the box API defined in libfaust-box-c.h.
     *
     * @param name_app - the name of the Faust program
     * @param box - the box expression
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     *
     * @return a DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API interpreter_dsp_factory* createCInterpreterDSPFactoryFromBoxes(const char* name_app,
                                                                            Box box,
                                                                            int argc, const char* argv[],
                                                                            char* error_msg);

    /**
     * Delete a Faust DSP factory, that is decrements it's reference counter, possibly really deleting the internal pointer.
     * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted.
     * Beware: all kept factories and DSP pointers (in local variables...) thus become invalid.
     *
     * @param factory - the DSP factory
     *
     * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
     */
    LIBFAUST_API bool deleteCInterpreterDSPFactory(interpreter_dsp_factory* factory);

    /**
     * Get the list of library dependancies of the Faust DSP factory.
     *
     * @deprecated : use factory getInterpreterDSPFactoryLibraryList method.
     *
     * @param factory - the DSP factory
     *
     * @return the library dependancies (the array and it's content has to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API const char** getCInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory);

    /**
     * Delete all Faust DSP factories kept in the library cache. Beware: all kept factory and DSP pointers (in local variables...) thus become invalid.
     */
    LIBFAUST_API void deleteAllCInterpreterDSPFactories();

    /**
     * Return Faust DSP factories of the library cache as a vector of their SHA keys.
     *
     * @return the Faust DSP factories (the array and it's content has to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API const char** getAllCInterpreterDSPFactories();

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
     * Create a Faust DSP factory from a bitcode string. Note that the library keeps an internal cache of all
     * allocated factories so that the compilation of the same DSP code (that is the same bitcode code string) will return
     * the same (reference counted) factory pointer. You will have to explicitly use deleteInterpreterDSPFactory to properly
     * decrement reference counter when the factory is no more needed.
     *
     * @param bitcode - the bitcode string
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API interpreter_dsp_factory* readCInterpreterDSPFactoryFromBitcode(const char* bitcode, char* error_msg);

    /**
     * Write a Faust DSP factory into a bitcode string.
     *
     * @param factory - the DSP factory
     *
     * @return the bitcode as a string (to be deleted by the caller using freeCMemory).
     */
    LIBFAUST_API char* writeCInterpreterDSPFactoryToBitcode(interpreter_dsp_factory* factory);

    /**
     * Create a Faust DSP factory from a bitcode file. Note that the library keeps an internal cache of all
     * allocated factories so that the compilation of the same DSP code (that is the same Bitcode file) will return
     * the same (reference counted) factory pointer. You will have to explicitly use deleteInterpreterDSPFactory to properly
     * decrement reference counter when the factory is no more needed.
     *
     * @param bit_code_path - the bitcode file pathname
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     *
     * @return the DSP factory on success, otherwise a null pointer.
     */
    LIBFAUST_API interpreter_dsp_factory* readCInterpreterDSPFactoryFromBitcodeFile(const char* bit_code_path, char* error_msg);

    /**
     * Write a Faust DSP factory into a bitcode file.
     *
     * @param factory - the DSP factory
     * @param bit_code_path - the bitcode file pathname
     *
     * @return true if success, false otherwise.
     */
    LIBFAUST_API bool writeCInterpreterDSPFactoryToBitcodeFile(interpreter_dsp_factory* factory, const char* bit_code_path);
    
    /**
     * Instance functions.
     */
    
    LIBFAUST_API int getNumInputsCInterpreterDSPInstance(interpreter_dsp* dsp);
    
    LIBFAUST_API int getNumOutputsCInterpreterDSPInstance(interpreter_dsp* dsp);
    
    LIBFAUST_API void buildUserInterfaceCInterpreterDSPInstance(interpreter_dsp* dsp, UIGlue* interface);
    
    LIBFAUST_API int getSampleRateCInterpreterDSPInstance(interpreter_dsp* dsp);
    
    LIBFAUST_API void initCInterpreterDSPInstance(interpreter_dsp* dsp, int sample_rate);
    
    LIBFAUST_API void instanceInitCInterpreterDSPInstance(interpreter_dsp* dsp, int sample_rate);
    
    LIBFAUST_API void instanceConstantsCInterpreterDSPInstance(interpreter_dsp* dsp, int sample_rate);
    
    LIBFAUST_API void instanceResetUserInterfaceCInterpreterDSPInstance(interpreter_dsp* dsp);
    
    LIBFAUST_API void instanceClearCInterpreterDSPInstance(interpreter_dsp* dsp);
    
    LIBFAUST_API interpreter_dsp* cloneCInterpreterDSPInstance(interpreter_dsp* dsp);
    
    LIBFAUST_API void metadataCInterpreterDSPInstance(interpreter_dsp* dsp, MetaGlue* meta);
    
    LIBFAUST_API void computeCInterpreterDSPInstance(interpreter_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
    
    /**
     * Create a Faust DSP instance.
     *
     * @param factory - the Faust DSP factory
     *
     * @return the DSP instance on success, otherwise a null pointer.
     */
    LIBFAUST_API interpreter_dsp* createCInterpreterDSPInstance(interpreter_dsp_factory* factory);
    
    /**
     * Delete a Faust DSP instance.
     *
     * @param dsp - the DSP instance to be deleted.
     */
    LIBFAUST_API void deleteCInterpreterDSPInstance(interpreter_dsp* dsp);
    

#ifdef __cplusplus
}
#endif

/*!
 @}
 */

#endif
/************************** END interpreter-dsp-c.h **************************/
