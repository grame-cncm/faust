/************************** BEGIN wasm-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef wasm_dsp_H
#define wasm_dsp_H

#include <string>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"

/*!
 \addtogroup wasmcpp C++ interface for compiling Faust code. Note that the API is not thread safe.
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
class wasm_dsp : public dsp {
    
    private:
    
        // wasm_dsp objects are allocated using wasm_dsp_factory::createDSPInstance();
        wasm_dsp() {}

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

        wasm_dsp* clone();

        void metadata(Meta* m);

        void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
    
};

/**
 * Wasm DSP factory class.
 */

class wasm_dsp_factory : public dsp_factory {
    
    public:
    
        virtual ~wasm_dsp_factory();

        /**
         *  Return factory name:
         *  either the name declared in DSP with [declare name "foo"] syntax
         *  or 'filename' (if createWasmDSPFactoryFromFile is used)
         *  or 'name_app' (if createWasmDSPFactoryFromString is used)
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
        wasm_dsp* createDSPInstance();

        /* Set a custom memory manager to be used when creating instances */
        void setMemoryManager(dsp_memory_manager* manager);

        /* Return the currently set custom memory manager */
        dsp_memory_manager* getMemoryManager();
};

/**
 * Get the Faust DSP factory associated with a given SHA key (created from the 'expanded' DSP source),
 * if already allocated in the factories cache and increment it's reference counter. You will have to explicitly
 * use deleteWasmDSPFactory to properly decrement reference counter when the factory is no more needed.
 *
 * @param sha_key - the SHA key for an already created factory, kept in the factory cache
 *
 * @return a valid DSP factory if one is associated with the SHA key, otherwise a null pointer.
 */
wasm_dsp_factory* getWasmDSPFactoryFromSHAKey(const std::string& sha_key);

/**
 * Create a Faust DSP factory from a DSP source code as a file. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of same DSP code (that is same source code and
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will
 * have to explicitly use deleteInterpreterDSPFactory to properly decrement reference counter when the factory is no
 * more needed.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 * @param internal_memory - whether to use an internallay allocated memory block for wasm module
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */
wasm_dsp_factory* createWasmDSPFactoryFromFile(const std::string& filename, int argc, const char* argv[],
                                               std::string& error_msg, bool internal_memory);

/**
 * Create a Faust DSP factory from a DSP source code as a string. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of same DSP code (that is same source code and
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will
 * have to explicitly use deleteDSPFactory to properly decrement reference counter when the factory is no more needed.
 *
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 * @param internal_memory - whether to use an internallay allocated memory block for wasm module
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */
wasm_dsp_factory* createWasmDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content, int argc,
                                                 const char* argv[], std::string& error_msg, bool internal_memory);
/**
 * Delete a Faust DSP factory, that is decrements it's reference counter, possibly really deleting the internal pointer.
 * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted.
 * Beware : all kept factories and DSP pointers (in local variables...) thus become invalid.
 *
 * @param factory - the DSP factory
 *
 * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
 */

/**
 * Delete a Faust DSP factory, that is decrements it's reference counter, possible really deleting the internal pointer.
 * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted.
 * Beware : all kept factories and DSP pointers (in local variables...) thus become invalid.
 *
 * @param factory - the DSP factory
 *
 * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
 */
bool deleteWasmDSPFactory(wasm_dsp_factory* factory);

/**
 * Delete all Faust DSP factories kept in the library cache. Beware : all kept factory and DSP pointers (in local
 * variables...) thus become invalid.
 *
 */
void deleteAllWasmDSPFactories();

/**
 * Return Faust DSP factories of the library cache as a vector of their SHA keys.
 *
 * @return the Faust DSP factories.
 */
std::vector<std::string> getAllWasmDSPFactories();

/**
 * Create a Faust DSP factory from a machine code string. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of the same DSP code (that is the same machine code string) will return
 * the same (reference counted) factory pointer. You will have to explicitly use deleteWasmDSPFactory to properly
 * decrement reference counter when the factory is no more needed.
 *
 * @param machine_code - the machine code string
 * @param error_msg - the error string to be filled
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
wasm_dsp_factory* readWasmDSPFactoryFromMachine(const std::string& machine_code, std::string& error_msg);

/**
 * Write a Faust DSP factory into a machine code string.
 *
 * @param factory - the DSP factory
 *
 * @return the machine code as a string.
 */
std::string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory);

/**
 * Create a Faust DSP factory from a machine code file. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of the same DSP code (that is the same machine code file) will return
 * the same (reference counted) factory pointer. You will have to explicitly use deleteWasmDSPFactory to properly
 * decrement reference counter when the factory is no more needed.
 *
 * @param machine_code_path - the machine code file pathname
 * @param error_msg - the error string to be filled
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(const std::string& machine_code_path, std::string& error_msg);

/**
 * Write a Faust DSP factory into a machine code file.
 *
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 *
 */
void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory, const std::string& machine_code_path);

/*!
 @}
 */

#ifdef EMCC
#include <emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(CLASS_wasm_dsp_factory)
{
    class_<wasm_dsp_factory>("wasm_dsp_factory")
    .constructor()
    .function("createDSPInstance", &wasm_dsp_factory::createDSPInstance, allow_raw_pointers())
    .function("deleteDSPInstance", &wasm_dsp_factory::deleteDSPInstance, allow_raw_pointers())
    .class_function("readWasmDSPFactoryFromMachineFile2", &wasm_dsp_factory::readWasmDSPFactoryFromMachineFile2,
                    allow_raw_pointers())
    .class_function("readWasmDSPFactoryFromMachine2", &wasm_dsp_factory::readWasmDSPFactoryFromMachine2,
                    allow_raw_pointers())
    .class_function("createWasmDSPFactory", &wasm_dsp_factory::createWasmDSPFactory, allow_raw_pointers())
    .class_function("deleteWasmDSPFactory", &wasm_dsp_factory::deleteWasmDSPFactory2, allow_raw_pointers())
    .class_function("getErrorMessage", &wasm_dsp_factory::getErrorMessage)
    .class_function("extractJSON", &wasm_dsp_factory::extractJSON, allow_raw_pointers());
}

EMSCRIPTEN_BINDINGS(CLASS_wasm_dsp)
{
    class_<wasm_dsp>("wasm_dsp")
    .constructor()
    .function("getNumInputs", &wasm_dsp::getNumInputs, allow_raw_pointers())
    .function("getNumOutputs", &wasm_dsp::getNumOutputs, allow_raw_pointers())
    .function("getSampleRate", &wasm_dsp::getSampleRate, allow_raw_pointers())
    .function("init", &wasm_dsp::init, allow_raw_pointers())
    .function("instanceInit", &wasm_dsp::instanceInit, allow_raw_pointers())
    .function("instanceConstants", &wasm_dsp::instanceConstants, allow_raw_pointers())
    .function("instanceResetUserInterface", &wasm_dsp::instanceResetUserInterface, allow_raw_pointers())
    .function("instanceClear", &wasm_dsp::instanceClear, allow_raw_pointers())
    .function("clone", &wasm_dsp::clone, allow_raw_pointers())
    .function("compute", &wasm_dsp::computeJS, allow_raw_pointers())
    .function("setParamValue", &wasm_dsp::setParamValue, allow_raw_pointers())
    .function("getParamValue", &wasm_dsp::getParamValue, allow_raw_pointers());
}

#endif

#endif
/**************************  END  wasm-dsp.h **************************/
