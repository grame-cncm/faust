/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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

#ifndef INTERPRETER_DSP_H
#define INTERPRETER_DSP_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <string>
#include <vector>
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"

/*!
 \addtogroup interpretercpp C++ interface for compiling Faust code. Note that the API is not thread safe.
 @{
 */

/**
 * DSP instance class with methods.
 */
class interpreter_dsp : public dsp {
    
    public:
        
        int getNumInputs();
        
        int getNumOutputs();
        
        void buildUserInterface(UI* ui_interface);
        
        int getSampleRate();
        
        void init(int samplingRate);
        
        void instanceInit(int samplingRate);
    
        void instanceConstants(int samplingRate);
    
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
    
        /* Return Factory name */
        std::string getName();
        
        /* Return Factory SHA key */
        std::string getSHAKey();
  
        /* Return Factory expanded DSP code */
        std::string getDSPCode();
    
        /* Creates a new dsp instance, to be deleted with C++ 'delete' before the DSP factory is itself deleted */
        interpreter_dsp* createDSPInstance();
  
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
interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const std::string& sha_key);

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
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
interpreter_dsp_factory* createInterpreterDSPFactoryFromFile(const std::string& filename,
                                                           int argc, const char* argv[], 
                                                           std::string& error_msg);

/**
 * Create a Faust DSP factory from a DSP source code as a string. Note that the library keeps an internal cache of all 
 * allocated factories so that the compilation of same DSP code (that is same source code and 
 * same set of 'normalized' compilations options) will return the same (reference counted) factory pointer. You will have to explicitly
 * use deleteDSPFactory to properly decrement reference counter when the factory is no more needed.
 * 
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
interpreter_dsp_factory* createInterpreterDSPFactoryFromString(const std::string& name_app,
                                                            const std::string& dsp_content,
                                                            int argc, const char* argv[],
                                                            std::string& error_msg);
/**
 * Delete a Faust DSP factory, that is decrements it's reference counter, possible really deleting the internal pointer. 
 * Possibly also delete DSP pointers associated with this factory, if they were not explicitly deleted with deleteDSPInstance.
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
 * @param factory - the DSP factory
 * 
 * @return the list as a vector of strings.
 */
std::vector<std::string> getInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory);

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
 * Create a Faust DSP factory from a base64 encoded machine code string. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of the same DSP code (that is the same machine code string) will return
 * the same (reference counted) factory pointer. You will have to explicitly use deleteInterpreterDSPFactory to properly
 * decrement reference counter when the factory is no more needed.
 *
 * @param machine_code - the machine code string
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
interpreter_dsp_factory* readInterpreterDSPFactoryFromMachine(const std::string& machine_code);

/**
 * Write a Faust DSP factory into a base64 encoded machine code string.
 *
 * @param factory - the DSP factory
 *
 * @return the machine code as a string.
 */
std::string writeInterpreterDSPFactoryToMachine(interpreter_dsp_factory* factory);

/**
 * Create a Faust DSP factory from a machine code file. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of the same DSP code (that is the same machine code file) will return
 * the same (reference counted) factory pointer. You will have to explicitly use deleteInterpreterDSPFactory to properly
 * decrement reference counter when the factory is no more needed.
 *
 * @param machine_code_path - the machine code file pathname
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
interpreter_dsp_factory* readInterpreterDSPFactoryFromMachineFile(const std::string& machine_code_path);

/**
 * Write a Faust DSP factory into a machine code file.
 *
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 *
 */
void writeInterpreterDSPFactoryToMachineFile(interpreter_dsp_factory* factory, const std::string& machine_code_path);

/*!
 @}
 */

#endif
