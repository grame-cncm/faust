/************************** BEGIN interpreter-machine-dsp.h **************************/
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

#ifndef INTERPRETER_MACHINE_DSP_H
#define INTERPRETER_MACHINE_DSP_H

#ifdef _WIN32
#define DEPRECATED(fun) __declspec(deprecated) fun
#else
#define DEPRECATED(fun) fun __attribute__ ((deprecated));
#endif

#include <string>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"

/*!
 \addtogroup interpretercpp C++ interface for reading FBC code. Note that the API is not thread safe.
 @{
 */

/**
 * Get the library version.
 *
 * @return the library version as a static string.
 */
extern "C" const char* getCLibFaustVersion();

/**
 * DSP instance class with methods.
 */
class interpreter_dsp : public dsp {
    
    private:
    
        // interpreter_dsp objects are allocated using interpreter_dsp_factory::createDSPInstance();
        interpreter_dsp() {}
    
    public:
        
        int getNumInputs();
        
        int getNumOutputs();
        
        void buildUserInterface(UI* ui_interface);
        
        int getSampleRate();
        
        void init(int sample_rate);
        
        void instanceInit(int sample_rate);
    
        void instanceConstants(int sample_rate);
    
        void instanceResetUserInterface();
        
        void instanceClear();
        
        interpreter_dsp* clone();
        
        void metadata(Meta* m);
        
        void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
    
};

/**
* Interpreter DSP factory class.
*/

class interpreter_dsp_factory : public dsp_factory {

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
        
        /* Create a new DSP instance, to be deleted with C++ 'delete' */
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
 * @return a DSP factory if one is associated with the SHA key, otherwise a null pointer.
 */
interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const std::string& sha_key);

/**
 * Delete a Faust DSP factory, that is decrements it's reference counter, possibly really deleting the internal pointer.
 * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted.
 * Beware : all kept factories and DSP pointers (in local variables...) thus become invalid.
 * 
 * @param factory - the DSP factory
 *
 * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
 */                                 
bool deleteInterpreterDSPFactory(interpreter_dsp_factory* factory);

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
 * Delete all Faust DSP factories kept in the library cache. Beware : all kept factory and DSP pointers (in local variables...) thus become invalid.
 * 
 */                                 
void deleteAllInterpreterDSPFactories();

/**
 * Return Faust DSP factories of the library cache as a vector of their SHA keys.
 * 
 * @return the Faust DSP factories.
 */                                 
std::vector<std::string> getAllInterpreterDSPFactories();

/**
 * Create a Faust DSP factory from a bitcode string. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of the same DSP code (that is the same bitcode code string) will return
 * the same (reference counted) factory pointer. You will have to explicitly use deleteInterpreterDSPFactory to properly
 * decrement reference counter when the factory is no more needed.
 *
 * @param bitcode_code - the bitcode string
 * @param error_msg - the error string to be filled
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcode(const std::string& bitcode, std::string& error_msg);

/**
 * Write a Faust DSP factory into a bitcode string.
 *
 * @param factory - the DSP factory
 *
 * @return the bitcode as a string.
 */
std::string writeInterpreterDSPFactoryToBitcode(interpreter_dsp_factory* factory);

/**
 * Create a Faust DSP factory from a bitcode file. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of the same DSP code (that is the same Bitcode file) will return
 * the same (reference counted) factory pointer. You will have to explicitly use deleteInterpreterDSPFactory to properly
 * decrement reference counter when the factory is no more needed.
 *
 * @param bitcode_path - the bitcode file pathname
 * @param error_msg - the error string to be filled
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcodeFile(const std::string& bitcode_path, std::string& error_msg);

/**
 * Write a Faust DSP factory into a bitcode file.
 *
 * @param factory - the DSP factory
 * @param bitcode_path - the bitcode file pathname
 *
 */
void writeInterpreterDSPFactoryToBitcodeFile(interpreter_dsp_factory* factory, const std::string& bitcode_path);

/*!
 @}
 */

#endif
/**************************  END  interpreter-machine-dsp.h **************************/
