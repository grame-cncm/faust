/************************** BEGIN llvm-dsp.h **************************/
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

#ifndef LLVM_DSP_H
#define LLVM_DSP_H

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
 \addtogroup llvmcpp C++ interface for compiling Faust code. Note that the API is not thread safe : use 'startMTDSPFactories/stopMTDSPFactories' to use it in a multi-thread context.
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
class llvm_dsp : public dsp {
    
    private:
    
        // llvm_dsp objects are allocated using llvm_dsp_factory::createDSPInstance();
        llvm_dsp() {}
    
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
        
        llvm_dsp* clone();
        
        void metadata(Meta* m);
        
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
    
};

/**
 * DSP factory class.
 */

class llvm_dsp_factory : public dsp_factory {

     public:
    
        virtual ~llvm_dsp_factory();
        
        /**
         *  Return factory name:
         *  either the name declared in DSP with [declare name "foo"] syntax
         *  or 'filename' (if createDSPFactoryFromFile is used)
         *  or 'name_app' (if createDSPFactoryFromString is used)
        */
        std::string getName();
    
        /* Return factory LLVM target (like 'i386-apple-macosx10.6.0:opteron')*/
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
        
        /* Create a new DSP instance, to be deleted with C++ 'delete' */
        llvm_dsp* createDSPInstance();
        
        /* Set a custom memory manager to be used when creating instances */
        void setMemoryManager(dsp_memory_manager* manager);
        
        /* Return the currently set custom memory manager */
        dsp_memory_manager* getMemoryManager();

};

/**
 * Get the target (triple + CPU) of the machine.
 *
 * @return the target as a string.
 */
std::string getDSPMachineTarget();

/**
 * Get the Faust DSP factory associated with a given SHA key (created from the 'expanded' DSP source), 
 * if already allocated in the factories cache and increment it's reference counter. You will have to explicitly
 * use deleteDSPFactory to properly decrement reference counter when the factory is no more needed.
 *
 * @param sha_key - the SHA key for an already created factory, kept in the factory cache
 *
 * @return a DSP factory if one is associated with the SHA key, otherwise a null pointer.
 */
llvm_dsp_factory* getDSPFactoryFromSHAKey(const std::string& sha_key);

/**
 * Create a Faust DSP factory from a DSP source code as a file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of the same DSP code (that is same source code and 
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will have to explicitly
 * use deleteDSPFactory to properly decrement the reference counter when the factory is no more needed.
 * 
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array 
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
 * since the maximum value may change with new LLVM versions)
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */ 
llvm_dsp_factory* createDSPFactoryFromFile(const std::string& filename, 
                                           int argc, const char* argv[], 
                                           const std::string& target, 
                                           std::string& error_msg,
                                           int opt_level = -1);

/**
 * Create a Faust DSP factory from a DSP source code as a string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of the same DSP code (that is same source code and 
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will have to explicitly
 * use deleteDSPFactory to properly decrement reference counter when the factory is no more needed.
 * 
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
 * since the maximum value may change with new LLVM versions)
 *
 * @return a DSP factory on success, otherwise a null pointer.
 */ 
llvm_dsp_factory* createDSPFactoryFromString(const std::string& name_app,
                                             const std::string& dsp_content,
                                             int argc, const char* argv[], 
                                             const std::string& target, 
                                             std::string& error_msg,
                                             int opt_level = -1);

/**
 * Delete a Faust DSP factory, that is decrements it's reference counter, possibly really deleting the internal pointer. 
 * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted with C++ delete.
 * Beware : all kept factories and DSP pointers (in local variables...) thus become invalid.
 * 
 * @param factory - the DSP factory
 *
 * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
 */                                 
bool deleteDSPFactory(llvm_dsp_factory* factory);

/**
 * Get the Faust DSP factory list of library dependancies.
 *
 * @deprecated : use factory getDSPFactoryLibraryList method.
 *
 * @param factory - the DSP factory
 * 
 * @return the list as a vector of strings.
 */
DEPRECATED(std::vector<std::string> getDSPFactoryLibraryList(llvm_dsp_factory* factory));

/**
 * Delete all Faust DSP factories kept in the library cache. Beware : all kept factory and DSP pointers (in local variables...) thus become invalid.
 * 
 */                                 
void deleteAllDSPFactories();

/**
 * Return Faust DSP factories of the library cache as a vector of their SHA keys.
 * 
 * @return the Faust DSP factories.
 */                                 
std::vector<std::string> getAllDSPFactories();

/**
 * Start multi-thread access mode (since by default the library is not 'multi-thread' safe).
 * 
 * @return true if 'multi-thread' safe access is started.
 */ 
extern "C" bool startMTDSPFactories();

/**
 * Stop multi-thread access mode.
 * 
 */ 
extern "C" void stopMTDSPFactories();

/**
 * Create a Faust DSP factory from a base64 encoded LLVM bitcode string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of the same DSP code (that is the same LLVM bitcode string) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param bit_code - the LLVM bitcode string
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling createDSPFactory can possibly be used.
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromBitcode(const std::string& bit_code, const std::string& target, std::string& error_msg, int opt_level = -1);

/**
 * Write a Faust DSP factory into a base64 encoded LLVM bitcode string.
 * 
 * @param factory - the DSP factory
 *
 * @return the LLVM bitcode as a string.
 */
std::string writeDSPFactoryToBitcode(llvm_dsp_factory* factory);

/**
 * Create a Faust DSP factory from a LLVM bitcode file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of the same DSP code (that is the same LLVM bitcode file) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param bit_code_path - the LLVM bitcode file pathname
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling 
 * createDSPFactory can possibly be used.
 * 
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, std::string& error_msg, int opt_level = -1);

/**
 * Write a Faust DSP factory into a LLVM bitcode file.
 * 
 * @param factory - the DSP factory
 * @param bit_code_path - the LLVM bitcode file pathname.
 *
 * @return true on success, false on failure.
 */
bool writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const std::string& bit_code_path);

/**
 * Create a Faust DSP factory from a LLVM IR (textual) string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of the same DSP code (that is the same LLVM IR string) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param ir_code - the LLVM IR (textual) string
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling 
 * createDSPFactory can possibly be used.
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromIR(const std::string& ir_code, const std::string& target, std::string& error_msg, int opt_level = -1);

/**
 * Write a Faust DSP factory into a LLVM IR (textual) string.
 * 
 * @param factory - the DSP factory
 *
 * @return the LLVM IR (textual) as a string.
 */
std::string writeDSPFactoryToIR(llvm_dsp_factory* factory);

/**
 * Create a Faust DSP factory from a LLVM IR (textual) file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of the same DSP code (that is the same LLVM IR file) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param ir_code_path - the LLVM IR (textual) file pathname
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions), a higher value 
 * than the one used when calling createDSPFactory can possibly be used.
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromIRFile(const std::string& ir_code_path, const std::string& target, std::string& error_msg, int opt_level = -1);

/**
 * Write a Faust DSP factory into a LLVM IR (textual) file.
 * 
 * @param factory - the DSP factory
 * @param ir_code_path - the LLVM bitcode file pathname.
 *
 * @return true on success, false on failure.
 */
bool writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const std::string& ir_code_path);

/**
 * Create a Faust DSP factory from a base64 encoded machine code string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of the same DSP code (that is the same machine code string) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param machine_code - the machine code string
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 * @param error_msg - the error string to be filled
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code, const std::string& target, std::string& error_msg);

/**
 * Write a Faust DSP factory into a base64 encoded machine code string.
 * 
 * @param factory - the DSP factory
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 *
 * @return the machine code as a string.
 */
std::string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const std::string& target);

/**
 * Create a Faust DSP factory from a machine code file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of the same DSP code (that is the same machine code file) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param machine_code_path - the machine code file pathname
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 * @param error_msg - the error string to be filled
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path, const std::string& target, std::string& error_msg);

/**
 * Write a Faust DSP factory into a machine code file.
 * 
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 *
 * @return true on success, false on failure.
 */
bool writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const std::string& machine_code_path, const std::string& target);

/**
 * Write a Faust DSP factory into an object code file.
 *
 * @param factory - the DSP factory
 * @param target - the LLVM machine target: like 'i386-apple-macosx10.6.0:opteron',
 *                 using an empty string takes the current machine settings,
 *                 and i386-apple-macosx10.6.0:generic kind of syntax for a generic processor
 *
 * @return true on success, false on failure.
 */
bool writeDSPFactoryToObjectcodeFile(llvm_dsp_factory* factory, const std::string& object_code_path, const std::string& target);

/**
 * Call global declarations with the given meta object.
 * 
 * @deprecated : use DSP instance metadata method.
 * @param factory - the DSP factory
 * @param meta - the meta object to be used.
 *
 */
DEPRECATED(void metadataDSPFactory(llvm_dsp_factory* factory, Meta* meta));

/**
 * Create a Faust DSP instance.
 * 
 * @deprecated : use factory createDSPInstance method.
 * @param factory - the DSP factory
 * 
 * @return the DSP instance on success, otherwise a null pointer.
 */
DEPRECATED(llvm_dsp* createDSPInstance(llvm_dsp_factory* factory));

/**
 * Delete a Faust DSP instance. You can also simply use C++ 'delete'. 
 * 
 * @deprecated : simply use C++ delete.
 * @param dsp - the DSP instance to be deleted.
 */ 
DEPRECATED(void deleteDSPInstance(llvm_dsp* dsp));

/*!
 @}
 */

#endif
/**************************  END  llvm-dsp.h **************************/
