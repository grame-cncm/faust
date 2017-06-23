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
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"

/*!
 \addtogroup llvmcpp C++ interface for loading (cross) compiled Faust code. Note that the API is not thread safe :
 use 'startMTDSPFactories/stopMTDSPFactories' to use it in a multi-thread context.
 @{
 */

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
 * Get the target (triple + CPU) of the DSP machine.
 *
 * @return the target as a string.
 */
std::string getDSPMachineTarget();

extern "C" char* getCDSPMachineTarget();

/**
 * Get the Faust DSP factory associated with a given SHA key (created from the 'expanded' DSP source), 
 * if already allocated in the factories cache.
 *
 * @param sha_key - the SHA key for an already created factory, kept in the factory cache
 *
 * @return a valid DSP factory if one is associated with the SHA key, otherwise a null pointer.
 */
llvm_dsp_factory* getDSPFactoryFromSHAKey(const std::string& sha_key);

extern "C" llvm_dsp_factory* getCDSPFactoryFromSHAKey(const char* sha_key);

/**
 * Create a Faust DSP factory from a DSP source code as a string. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of same DSP code (that is same source code and
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer.
 *
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux file generation options will be filtrated (-svg, ...) --> use generateAuxFiles)
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value')
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* createDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content,
                                             int argc, const char* argv[],
                                             const std::string& target,
                                             std::string& error_msg, int opt_level = 3);

extern "C" llvm_dsp_factory* createCDSPFactoryFromString(const char* name_app, const char* dsp_content,
                                                         int argc, const char* argv[],
                                                         const char* target,
                                                         char* error_msg, int opt_level);


/**
 * Destroy a Faust DSP factory, that is decrements it's reference counter, possible really deleting the pointer.  
 * 
 * @param factory - the DSP factory to be deleted.
 */                                 
void deleteDSPFactory(llvm_dsp_factory* factory);

/**
 * Get the name of the Faust DSP factory : will be the name declared in the DSP source file or string, or if not available,
 * the DSP 'filename' given in createDSPFactoryFromFile or the DSP 'name_app' given in createDSPFactoryFromString.
 *
 * @param factory - the DSP factory
 *
 * @return the name as a string.
 */
extern "C" char* getCName(llvm_dsp_factory* factory);

/**
 * Get the LLVM target of the Faust DSP factory.
 *
 * @param factory - the DSP factory
 *
 * @return the LLVM target as a string.
 */
extern "C" char* getCTarget(llvm_dsp_factory* factory);

/**
 * Get the SHA Key of the Faust DSP factory.
 *
 * @param factory - the DSP factory
 *
 * @return the SHA key as a string.
 */
extern "C" char* getCSHAKey(llvm_dsp_factory* factory);

/**
 * Get the expanded DSP code of the Faust DSP factory.
 *
 * @param factory - the DSP factory
 *
 * @return the expanded DSP code as a string.
 */
extern "C" char* getCDSPCode(llvm_dsp_factory* factory);

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
 * Start multi-thread access mode (since by default the library is not 'multi-thread' safe).
 * 
 * @return true is 'multi-thread' safe access is started.
 */ 
bool startMTDSPFactories();

/**
 * Stop multi-thread access mode.
 * 
 */ 
void stopMTDSPFactories();

/**
 * Create a Faust DSP factory from a machine code string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is the same machine code string) will return 
 * the same (reference counted) factory pointer.
 * 
 * @param machine_code - the machine code string
 *
 * @return the Faust DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromMachine(const std::string& machine_code);

extern "C" llvm_dsp_factory* readCDSPFactoryFromMachine(const char* machine_code);

/**
 * Create a Faust DSP factory from a machine code file. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is the same machine code file) will return 
 * the same (reference counted) factory pointer.
 * 
 * @param machine_code_path - the machine code file pathname
 *
 * @return the Faust DSP factory on success, otherwise a null pointer.
 */
llvm_dsp_factory* readDSPFactoryFromMachineFile(const std::string& machine_code_path);

extern "C" llvm_dsp_factory* readCDSPFactoryFromMachineFile(const char* machine_code_path);

extern "C" char* writeCDSPFactoryToMachine(llvm_dsp_factory* factory, const char* target);

/**
 * Call global declarations with the given meta object.
 * 
 * @param factory - the Faust DSP factory
 * @param meta - the meta object to be used.
 *
 */
void metadataDSPFactory(llvm_dsp_factory* factory, Meta* meta);

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
        
        virtual llvm_dsp* copy();
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
 * Compute a SHA1 key from a string
 * 
 * @param data - the string to be converted in SHA1 key
 *
 * @return the computed SHA1 key.
 */ 
std::string generateSHA1(const std::string& data);

/**
 * The free function to be used on memory returned by getCDSPMachineTarget, getCName, getCSHAKey, getCDSPCode, getCLibraryList,
 * getAllCDSPFactories, writeCDSPFactoryToBitcode, writeCDSPFactoryToIR, writeCDSPFactoryToMachine,
 * expandCDSPFromString and expandCDSPFromFile.
 * This is MANDATORY on Windows when otherwise all nasty runtime version related crashes can occur.
 *
 * @param ptr - the pointer to be deleted.
 */
extern "C" void freeCMemory(void* ptr);

/*!
 @}
 */

#endif
