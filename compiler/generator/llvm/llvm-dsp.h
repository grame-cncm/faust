/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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
 
 ************************************************************************
 ************************************************************************/

#ifndef LLVM_DSP_H
#define LLVM_DSP_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
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
 * @return the library version as a string.
 */
std::string getLibFaustVersion();

/**
* DSP factory class.
*/

class llvm_dsp_factory {

     public: 
        
        /* Return Factory name */
        std::string getName();
        
        /* Return Factory LLVM target */
        std::string getTarget();
        
        /* Return Factory SHA key */
        std::string getSHAKey();
  
        /* Return Factory expanded DSP code */
        std::string getDSPCode();

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
 * @return a valid DSP factory if one is associated with the SHA key, otherwise a null pointer.
 */
llvm_dsp_factory* getDSPFactoryFromSHAKey(const std::string& sha_key);

/**
 * Create a Faust DSP factory from a DSP source code as a file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is same source code and 
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will have to explicitly
 * use deleteDSPFactory to properly decrement the reference counter when the factory is no more needed.
 * 
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array 
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
 * since the maximum value may change with new LLVM versions)
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
llvm_dsp_factory* createDSPFactoryFromFile(const std::string& filename, 
                                           int argc, const char* argv[], 
                                           const std::string& target, 
                                           std::string& error_msg, int opt_level = -1);

/**
 * Create a Faust DSP factory from a DSP source code as a string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is same source code and 
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will have to explicitly
 * use deleteDSPFactory to properly decrement reference counter when the factory is no more needed.
 * 
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
 * since the maximum value may change with new LLVM versions)
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
llvm_dsp_factory* createDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content, 
                                             int argc, const char* argv[], 
                                             const std::string& target, 
                                             std::string& error_msg, int opt_level = -1);

/**
 * Delete a Faust DSP factory, that is decrements it's reference counter, possible really deleting the internal pointer. 
 * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted with deleteDSPInstance.
 * Beware : all kept factories and DSP pointers (in local variables...) thus become invalid.
 * 
 * @param factory - the DSP factory
 *
 * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
 */                                 
bool deleteDSPFactory(llvm_dsp_factory* factory);

/**
 * Get the list of library dependancies of the Faust DSP factory.
 *
 * @param factory - the DSP factory
 * 
 * @return the list as a vector of strings.
 */
std::vector<std::string> getDSPFactoryLibraryList(llvm_dsp_factory* factory);

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
bool startMTDSPFactories();

/**
 * Stop multi-thread access mode.
 * 
 */ 
void stopMTDSPFactories();

/**
 * Create a Faust DSP factory from a base64 encoded LLVM bitcode string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is the same LLVM bitcode string) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param bit_code - the LLVM bitcode string
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling createDSPFactory can possibly be used.
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromBitcode(const std::string& bit_code, const std::string& target, int opt_level = -1);

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
 * allocated factories so that the compilation of same DSP code (that is the same LLVM bitcode file) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param bit_code_path - the LLVM bitcode file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling 
 * createDSPFactory can possibly be used.
 * 
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, int opt_level = -1);

/**
 * Write a Faust DSP factory into a LLVM bitcode file.
 * 
 * @param factory - the DSP factory
 * @param bit_code_path - the LLVM bitcode file pathname.
 *
 */
void writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const std::string& bit_code_path);

/**
 * Create a Faust DSP factory from a LLVM IR (textual) string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is the same LLVM IR string) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param ir_code - the LLVM IR (textual) string
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling 
 * createDSPFactory can possibly be used.
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromIR(const std::string& ir_code, const std::string& target, int opt_level = -1);

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
 * allocated factories so that the compilation of same DSP code (that is the same LLVM IR file) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param ir_code_path - the LLVM IR (textual) file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value' 
 * since the maximum value may change with new LLVM versions), a higher value 
 * than the one used when calling createDSPFactory can possibly be used.
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromIRFile(const std::string& ir_code_path, const std::string& target, int opt_level = -1);

/**
 * Write a Faust DSP factory into a LLVM IR (textual) file.
 * 
 * @param factory - the DSP factory
 * @param ir_code_path - the LLVM bitcode file pathname.
 *
 */
void writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const std::string& ir_code_path);

/**
 * Create a Faust DSP factory from a base64 encoded machine code string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is the same machine code string) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param machine_code - the machine code string
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code, const std::string& target);

/**
 * Write a Faust DSP factory into a base64 encoded machine code string.
 * 
 * @param factory - the DSP factory
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 *
 * @return the machine code as a string.
 */
std::string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const std::string& target);

/**
 * Create a Faust DSP factory from a machine code file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is the same machine code file) will return 
 * the same (reference counted) factory pointer. You will have to explicitly use deleteDSPFactory to properly 
 * decrement reference counter when the factory is no more needed.
 * 
 * @param machine_code_path - the machine code file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path, const std::string& target);

/**
 * Write a Faust DSP factory into a machine code file.
 * 
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings).
 *
 */
void writeDSPFactoryToMachineFile(llvm_dsp_factory* factory, const std::string& machine_code_path, const std::string& target);

/**
 * Call global declarations with the given meta object.
 * 
 * @param factory - the DSP factory
 * @param meta - the meta object to be used.
 *
 */
void metadataDSPFactory(llvm_dsp_factory* factory, Meta* meta);

/**
 * From a DSP source file, creates a 'self-contained' DSP source string where all needed librairies have been included.
 * All compilations options are 'normalized' and included as a comment in the expanded string.
 
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param sha_key - the SHA key to be filled
 * @param error_msg - the error string to be filled
 *
 * @return the expanded DSP as a string (possibly empty).
 */ 
std::string expandDSPFromFile(const std::string& filename, 
                              int argc, const char* argv[],
                              std::string& sha_key,
                              std::string& error_msg);

/**
 * From a DSP source string, creates a 'self-contained' DSP source string where all needed librairies have been included.
 * All compilations options are 'normalized' and included as a comment in the expanded string.
 
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param sha_key - the SHA key to be filled
 * @param error_msg - the error string to be filled
 *
 * @return the expanded DSP as a string (possibly empty).
 */ 
std::string expandDSPFromString(const std::string& name_app, 
                                const std::string& dsp_content, 
                                int argc, const char* argv[], 
                                std::string& sha_key,
                                std::string& error_msg);

/**
 * From a DSP source file, generates auxiliary files : SVG, XML, ps... depending of the 'argv' parameters.
 
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return true if compilation succedeed, false and an error_msg in case of failure.
 */ 
bool generateAuxFilesFromFile(const std::string& filename, int argc, const char* argv[], std::string& error_msg);

/**
 * From a DSP source file, generates auxiliary files : SVG, XML, ps... depending of the 'argv' parameters.
 
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return true if compilation succedeed, false and an error_msg in case of failure.
 */ 
bool generateAuxFilesFromString(const std::string& name_app, const std::string& dsp_content, int argc, const char* argv[], std::string& error_msg);

/**
 * Instance class with related methods.
 */
class llvm_dsp : public dsp {
    
    public:
        
        void metadata(Meta* m);
        
        int getNumInputs();
        int getNumOutputs();
        
        void init(int samplingFreq);
        
        void buildUserInterface(UI* ui_interface);
        
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
        
        llvm_dsp* copy();
};

/**
 * Create a Faust DSP instance.
 * 
 * @param factory - the DSP factory
 * 
 * @return the DSP instance on success, otherwise a null pointer.
 */
llvm_dsp* createDSPInstance(llvm_dsp_factory* factory);

/**
 * Delete a Faust DSP instance. You can also simply use C++ 'delete'. 
 * 
 * @param dsp - the DSP instance to be deleted.
 */ 
void deleteDSPInstance(llvm_dsp* dsp);

/**
 * Compute a SHA1 key from a string
 * 
 * @param data - the string to be converted in SHA1 key
 *
 * @return the computed SHA1 key.
 */ 
std::string generateSHA1(const std::string& data);

/*!
 @}
 */

#endif
