/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
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
#include "faust/audio/dsp.h"
#include "faust/gui/meta.h"

/*!
 \addtogroup llvmcpp C++ interface for compiling Faust code. Note that the API is not thread safe and must be used with 
 appropiate protections (like mutexes) in a multi-thread context.
 @{
 */

/* Opaque type */

class llvm_dsp_factory {};

/**
 * Get the Faust DSP factory associated with a given SHA key (created from the 'expanded' DSP source), 
 * if already allocated in the factories cache.
 *
 * @param sha_key - the SHA key for an already created factory, kept in the factory cache
 *
 * @return a valid DSP factory if one is associated with the SHA key, otherwise a null pointer.
 */
llvm_dsp_factory* getDSPFactoryFromSHAKey(const std::string& sha_key);

/**
 * Create a Faust DSP factory from a DSP source code as a file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is same source code and 
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer.
 * 
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
llvm_dsp_factory* createDSPFactoryFromFile(const std::string& filename, 
                                           int argc, const char* argv[], 
                                           const std::string& target, 
                                           std::string& error_msg, int opt_level = 3);

/**
 * Create a Faust DSP factory from a DSP source code as a string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is same source code and 
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer.
 * 
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
llvm_dsp_factory* createDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content, 
                                             int argc, const char* argv[], 
                                             const std::string& target, 
                                             std::string& error_msg, int opt_level = 3);

/**
 * Destroy a Faust DSP factory, that is decrements it's reference counter, possible really deleting the pointer.  
 * 
 * @param factory - the DSP factory to be deleted.
 */                                 
void deleteDSPFactory(llvm_dsp_factory* factory);

/**
 * Get the name of the DSP factory : will be the name declared in the DSP source file or string, or if not available,
 * the DSP 'filename' given in createDSPFactoryFromFile or the DSP 'name_app' given in createDSPFactoryFromString.
 *
 * @param factory - the DSP factory.
 * 
 * @return the name as a string.
 */
std::string getName(llvm_dsp_factory* factory);

/**
 * Get the SHA Key of the DSP factory.
 *
 * @param factory - the DSP factory.
 * 
 * @return the SHA key as a string.
 */
std::string getSHAKey(llvm_dsp_factory* factory);

/**
 * Get the list of library dependancies of the DSP factory.
 *
 * @param factory - the DSP factory.
 * 
 * @return the list as a vector of strings.
 */
std::vector<std::string> getLibraryList(llvm_dsp_factory* factory);

/**
 * Destroy all Faust DSP factories kept in the library cache. Beware : all kept factory pointers (in local variables of so...) thus become invalid.
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
 * Create a Faust DSP factory from a LLVM bitcode string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is the same LLVM bitcode string) will return 
 * the same (reference counted) factory pointer.
 * 
 * @param bit_code - the LLVM bitcode string
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3). A higher value than the one used when calling createDSPFactory can possibly be used
 *
 * @return the Faust DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromBitcode(const std::string& bit_code, const std::string& target, int opt_level = 0);

/**
 * Write a Faust DSP factory into a LLVM bitcode string.
 * 
 * @param factory - Faust DSP factory
 *
 * @return the LLVM bitcode as a string.
 */
std::string writeDSPFactoryToBitcode(llvm_dsp_factory* factory);

/**
 * Create a Faust DSP factory from a LLVM bitcode file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is the same LLVM bitcode file) will return 
 * the same (reference counted) factory pointer.
 * 
 * @param bit_code_path - the LLVM bitcode file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3). A higher value than the one used when calling createDSPFactory can possibly be used
 */
llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, int opt_level = 0);

/**
 * Write a Faust DSP factory into a LLVM bitcode file.
 * 
 * @param factory - the Faust DSP factory
 * @param bit_code_path - the LLVM bitcode file pathname
 *
 */
void writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const std::string& bit_code_path);

/**
 * Create a Faust DSP factory from a LLVM IR (textual) string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is the same LLVM IR string) will return 
 * the same (reference counted) factory pointer.
 * 
 * @param ir_code - the LLVM IR (textual) string
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3). A higher value than the one used when calling createDSPFactory can possibly be used
 *
 * @return the Faust DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromIR(const std::string& ir_code, const std::string& target, int opt_level = 0);

/**
 * Write a Faust DSP factory into a LLVM IR (textual) string.
 * 
 * @param factory - the Faust DSP factory
 *
 * @return the LLVM IR (textual) as a string.
 */
std::string writeDSPFactoryToIR(llvm_dsp_factory* factory);

/**
 * Create a Faust DSP factory from a LLVM IR (textual) file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is the same LLVM IR file) will return 
 * the same (reference counted) factory pointer.
 * 
 * @param ir_code_path - the LLVM IR (textual) file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3). A higher value than the one used when calling createDSPFactory can possibly be used
 *
 * @return the Faust DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromIRFile(const std::string& ir_code_path, const std::string& target, int opt_level = 0);

/**
 * Write a Faust DSP factory into a LLVM IR (textual) file.
 * 
 * @param factory - the Faust DSP factory
 * @param ir_code_path - the LLVM bitcode file pathname.
 *
 */
void writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const std::string& ir_code_path);

/**
 * Call global declarations with the given meta object.
 * 
 * @param factory - the Faust DSP factory
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
 * From a DSP source file, generates auxillary files : SVG, XML, ps... depending of the 'argv' parameters.
 
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return true if compilation succedeed, false and an error_msg in case of failure.
 */ 
bool generateAuxFilesFromFile(const std::string& filename, int argc, const char* argv[], std::string& error_msg);

/**
 * From a DSP source file, generates auxillary files : SVG, XML, ps... depending of the 'argv' parameters.
 
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
    
    virtual int getNumInputs();
    virtual int getNumOutputs();
    
    virtual void init(int samplingFreq);
    
    virtual void buildUserInterface(UI* inter);
    
    virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
};

/**
 * Create a Faust DSP instance.
 * 
 * @param factory - the Faust DSP factory
 * 
 * @return the Faust DSP instance on success, otherwise a null pointer.
 */
llvm_dsp* createDSPInstance(llvm_dsp_factory* factory);

/**
 * Destroy a Faust DSP instance.
 * 
 * @param dsp - the DSP instance to be deleted.
 */ 
void deleteDSPInstance(llvm_dsp* dsp);

/**
 * Compute a SHA1 hey from a string
 * 
 * @param data - the string to be converted in SHA1 key
 *
 * @return the computed SHA1 key.
 */ 
std::string generateSha1(const std::string& data);

/*!
 @}
 */

#endif
