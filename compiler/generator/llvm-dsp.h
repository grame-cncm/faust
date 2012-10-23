/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2012 GRAME, Centre National de Creation Musicale
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
#include "faust/audio/dsp.h"
#include "faust/gui/meta.h"

struct llvm_dsp_factory {};

/**
 * Create a Faust DSP factory from a DSP source code.
 * 
 * @param argc - the number of parameter in argv array
 * @param argv - the array of parameters
 * @param library_path - Faust library path : if null, the default localization mechanism will be used
 * @param draw_path - the place where to put output files like SVG, ps, dot...
 * @param name - the name of the Faust program
 * @param input - the Faust program as a string
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param error_msg - the error string to be filled, has to be 256 characters long
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
llvm_dsp_factory* createDSPFactory(int argc, const char *argv[], 
                        const std::string& library_path, const std::string& draw_path, const std::string& name, 
                        const std::string& input, const std::string& target, 
                        char* error_msg, int opt_level = 3);
/**
 * Destroy a Faust DSP factory.
 * 
 * @param factory - the DSP factory to be deleted.
*/                                 
void deleteDSPFactory(llvm_dsp_factory* factory);
          
/**
 * Create a Faust DSP factory from a LLVM bitcode string.
 * 
 * @param bit_code - the LLVM bicode string
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
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
 * Create a Faust DSP factory from a LLVM bitcode file.
 * 
 * @param bit_code_path - the LLVM bicode file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
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
 * Create a Faust DSP factory from a LLVM IR (textual) string.
 * 
 * @param ir_code - the LLVM IR (textual) string
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
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
 * Create a Faust DSP factory from a LLVM IR (textual) string.
 * 
 * @param ir_code_path - the LLVM IR (textual) file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
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
* Instance class
*/
class llvm_dsp : public dsp {
               
    public:
      
        virtual int getNumInputs();
        virtual int getNumOutputs();

        void classInit(int samplingFreq);
        virtual void instanceInit(int samplingFreq);
        virtual void init(int samplingFreq);

        virtual void buildUserInterface(UI* interface);
 
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

#endif
