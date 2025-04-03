/************************** BEGIN signal-dsp.h *****************************
FAUST Architecture File
Copyright (C) 2024 GRAME, Centre National de Creation Musicale
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

#ifndef SIGNAL_DSP_H
#define SIGNAL_DSP_H

#include <string>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"

/*!
 \addtogroup signalcpp C++ interface for compiling Faust code with the Signal backend.
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

class LIBFAUST_API signal_dsp : public dsp {
    
    private:
    
        // signal_dsp objects are allocated using signal_dsp_factory::createDSPInstance();
        signal_dsp() {}
    
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
        signal_dsp* clone();
        
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
 * DSP factory class.
 */

class LIBFAUST_API signal_dsp_factory : public dsp_factory {

     public:
    
        virtual ~signal_dsp_factory();
        
        /**
         *  Return factory name:
         *  either the name declared in DSP with [declare name "foo"] syntax
         *  or 'filename' (if createDSPFactoryFromFile is used)
         *  or 'name_app' (if createDSPFactoryFromString is used)
        */
        std::string getName();
    
        /* Return factory LLVM target (like 'i386-apple-macosx10.6.0:opteron') */
        std::string getTarget();
        
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
         by 'deleteDSPFactory' if needed.
         */
        signal_dsp* createDSPInstance();
    
        /* Static tables initialization */
        void classInit(int sample_rate);
        
        /* Set a custom memory manager to be used when creating instances */
        void setMemoryManager(dsp_memory_manager* manager);
        
        /* Return the currently set custom memory manager */
        dsp_memory_manager* getMemoryManager();

};

/**
 * Create a Faust DSP factory from a DSP source code as a file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of the same DSP code (that is same source code and 
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will have to explicitly
 * use deleteDSPFactory to properly decrement the reference counter when the factory is no more needed.
 * 
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array 
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param error_msg - the error string to be filled
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */ 
LIBFAUST_API signal_dsp_factory* createSignalDSPFactoryFromFile(const std::string& filename,
                                                              int argc, const char* argv[],
                                                              std::string& error_msg);

/**
 * Create a Faust Signal DSP factory from a DSP source code as a string. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of the same DSP code (that is same source code and 
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will have to explicitly
 * use deleteDSPFactory to properly decrement reference counter when the factory is no more needed.
 * 
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param error_msg - the error string to be filled
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */ 
LIBFAUST_API signal_dsp_factory* createSignalDSPFactoryFromString(const std::string& name_app,
                                                                const std::string& dsp_content,
                                                                int argc, const char* argv[],
                                                                std::string& error_msg);

/**
 * Delete a Faust DSP factory, that is decrements it's reference counter, possibly really deleting the internal pointer. 
 * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted with C++ delete.
 * Beware: all kept factories and DSP pointers (in local variables...) thus become invalid.
 * 
 * @param factory - the DSP factory
 *
 * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
 */                                 
LIBFAUST_API bool deleteSignalDSPFactory(signal_dsp_factory* factory);

/*!
 @}
 */

#endif
/************************** END signal-dsp.h **************************/
