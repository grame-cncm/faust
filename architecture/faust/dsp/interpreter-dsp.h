/************************** BEGIN interpreter-dsp.h **********************
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

#ifndef INTERPRETER_DSP_H
#define INTERPRETER_DSP_H

#ifdef _WIN32
#define DEPRECATED(fun) __declspec(deprecated) fun
#else
#define DEPRECATED(fun) fun __attribute__ ((deprecated));
#endif

#include <string>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/dsp/libfaust-signal.h"
#include "faust/dsp/libfaust-box.h"
#include "faust/gui/meta.h"

/*!
 \addtogroup interpretercpp C++ interface for compiling Faust code with the Interpreter backend.
 Note that the API is not thread safe: use 'startMTDSPFactories/stopMTDSPFactories' to use it in a multi-thread context.
 @{
 */

/**
 * Get the library version.
 *
 * @return the library version as a static string.
 */
extern "C" LIBFAUST_API const char* getCLibFaustVersion();

/**
 * DSP instance class with methods.
 */
class LIBFAUST_API interpreter_dsp : public dsp {
    
    private:
    
        // interpreter_dsp objects are allocated using interpreter_dsp_factory::createDSPInstance();
        interpreter_dsp() {}
    
    public:
        
        /* Return instance number of audio inputs */
        int getNumInputs();
        
        /* Return instance number of audio outputs */
        int getNumOutputs();
        
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        void buildUserInterface(UI* ui_interface);
        
        /* Return the sample rate currently used by the instance */
        int getSampleRate();
        
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        void init(int sample_rate);
        
        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        void instanceInit(int sample_rate);
        
        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        void instanceConstants(int sample_rate);
        
        /* Init default control parameters values */
        void instanceResetUserInterface();
        
        /* Init instance state (like delay lines...) but keep the control parameter values */
        void instanceClear();
        
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        interpreter_dsp* clone();
        
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        void metadata(Meta* m);
        
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
    
};

/**
* Interpreter DSP factory class.
*/
class LIBFAUST_API interpreter_dsp_factory : public dsp_factory {

     public:
    
        virtual ~interpreter_dsp_factory();
    
        /**
         *  Return factory name:
         *  either the name declared in DSP with [declare name "foo"] syntax
         *  or 'filename' (if createInterpreterDSPFactoryFromFile is used)
         *  or 'name_app' (if createInterpreterDSPFactoryFromString is used)
         */
        std::string getName();
        
        /* Return factory SHA key */
        std::string getSHAKey();
  
        /* Return factory expanded DSP code */
        std::string getDSPCode();
    
        /* Return factory compile options */
        std::string getCompileOptions();
    
        /* Get the Faust DSP factory list of library dependancies */
        std::vector<std::string> getLibraryList();
        
        /* Get the list of all used includes */
        std::vector<std::string> getIncludePathnames();
        
        /* Get warning messages list for a given compilation */
        std::vector<std::string> getWarningMessages();

        /* Create a new DSP instance, to be deleted with C++ 'delete'.
         Note that the factory keeps track of all DSP allocated with 'createDSPInstance',
         so a DSP can be manually deleted using the C++ 'delete', or will be finally garbaged
         by 'deleteInterpreterDSPFactory' if needed.
         */
        interpreter_dsp* createDSPInstance();
    
        /* Set a custom memory manager to be used when creating instances */
        void setMemoryManager(dsp_memory_manager* manager);
        
        /* Return the currently set custom memory manager */
        dsp_memory_manager* getMemoryManager();

};

/**
 * Get the Faust DSP factory associated with a given SHA key (created from the 'expanded' DSP source),
 * if already allocated in the factories cache and increment it's reference counter. You will have to explicitly
 * use deleteInterpreterDSPFactory to properly decrement reference counter when the factory is no more needed.
 *
 * @param sha_key - the SHA key for an already created factory, kept in the factory cache
 *
 * @return a valid DSP factory if one is associated with the SHA key, otherwise a null pointer.
 */
LIBFAUST_API interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const std::string& sha_key);

/**
 * Create a Faust DSP factory from a DSP source code as a file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is same source code and 
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will have to explicitly
 * use deleteInterpreterDSPFactory to properly decrement reference counter when the factory is no more needed.
 * 
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array 
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */
LIBFAUST_API interpreter_dsp_factory* createInterpreterDSPFactoryFromFile(const std::string& filename,
                                                                          int argc, const char* argv[],
                                                                          std::string& error_msg);

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
 * @param error_msg - the error string to be filled
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */ 
LIBFAUST_API interpreter_dsp_factory* createInterpreterDSPFactoryFromString(const std::string& name_app,
                                                                            const std::string& dsp_content,
                                                                            int argc, const char* argv[],
                                                                            std::string& error_msg);

/**
 * Create a Faust DSP factory from a vector of output signals.
 * It has to be used with the signal API defined in libfaust-signal.h.
 *
 * @param name_app - the name of the Faust program
 * @param signals - the vector of output signals (that will internally be converted in normal form, see simplifyToNormalForm in libfaust-signal.h)
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */
LIBFAUST_API interpreter_dsp_factory* createInterpreterDSPFactoryFromSignals(const std::string& name_app,
                                                                             tvec signals,
                                                                             int argc, const char* argv[],
                                                                             std::string& error_msg);

/**
 * Create a Faust DSP factory from a box expression.
 * It has to be used with the box API defined in libfaust-box.h.
 *
 * @param name_app - the name of the Faust program
 * @param box - the box expression
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */
LIBFAUST_API interpreter_dsp_factory* createInterpreterDSPFactoryFromBoxes(const std::string& name_app,
                                                                           Box box,
                                                                           int argc, const char* argv[],
                                                                           std::string& error_msg);

/**
 * Delete a Faust DSP factory, that is decrements it's reference counter, possibly really deleting the internal pointer.
 * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted.
 * Beware: all kept factories and DSP pointers (in local variables...) thus become invalid.
 * 
 * @param factory - the DSP factory
 *
 * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
 */                                 
LIBFAUST_API bool deleteInterpreterDSPFactory(interpreter_dsp_factory* factory);

/**
 * Get the list of library dependancies of the Faust DSP factory.
 *
 * @deprecated : use factory getInterpreterDSPFactoryLibraryList method.
 *
 * @param factory - the DSP factory
 * 
 * @return the list as a vector of strings.
 */
DEPRECATED(std::vector<std::string> getInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory));

/**
 * Delete all Faust DSP factories kept in the library cache. Beware: all kept factory and DSP pointers (in local variables...) thus become invalid.
 */                                 
LIBFAUST_API void deleteAllInterpreterDSPFactories();

/**
 * Return Faust DSP factories of the library cache as a vector of their SHA keys.
 * 
 * @return the Faust DSP factories.
 */                                 
LIBFAUST_API std::vector<std::string> getAllInterpreterDSPFactories();

/**
 * Start multi-thread access mode (since by default the library is not 'multi-thread' safe).
 *
 * @return true if 'multi-thread' safe access is started.
 */
extern "C" LIBFAUST_API bool startMTDSPFactories();

/**
 * Stop multi-thread access mode.
 */
extern "C" LIBFAUST_API void stopMTDSPFactories();

/**
 * Create a Faust DSP factory from a bitcode string. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of the same DSP code (that is the same bitcode code string) will return
 * the same (reference counted) factory pointer. You will have to explicitly use deleteInterpreterDSPFactory to properly
 * decrement reference counter when the factory is no more needed.
 *
 * @param bit_code - the bitcode string
 * @param error_msg - the error string to be filled
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
LIBFAUST_API interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcode(const std::string& bit_code, std::string& error_msg);

/**
 * Write a Faust DSP factory into a bitcode string.
 *
 * @param factory - the DSP factory
 *
 * @return the bitcode as a string.
 */
LIBFAUST_API std::string writeInterpreterDSPFactoryToBitcode(interpreter_dsp_factory* factory);

/**
 * Create a Faust DSP factory from a bitcode file. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of the same DSP code (that is the same Bitcode file) will return
 * the same (reference counted) factory pointer. You will have to explicitly use deleteInterpreterDSPFactory to properly
 * decrement reference counter when the factory is no more needed.
 *
 * @param bit_code_path - the bitcode file pathname
 * @param error_msg - the error string to be filled
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
LIBFAUST_API interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcodeFile(const std::string& bit_code_path, std::string& error_msg);

/**
 * Write a Faust DSP factory into a bitcode file.
 *
 * @param factory - the DSP factory
 * @param bit_code_path - the bitcode file pathname
 *
 * @return true if success, false otherwise.
 */
LIBFAUST_API bool writeInterpreterDSPFactoryToBitcodeFile(interpreter_dsp_factory* factory, const std::string& bit_code_path);

/*!
 @}
 */

#endif
/************************** END interpreter-dsp.h **************************/
