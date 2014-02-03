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

#ifndef LLVM_DSP_C_H
#define LLVM_DSP_C_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/CUI.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Opaque types */
	
/*!
 \addtogroup llvmc C interface for compiling faust code
 @{
 */

struct llvm_dsp_factory;

struct llvm_dsp;

/**
 * Create a Faust DSP factory from a DSP source code. The source code is either given :
    - as a .dsp source filename (in which case the 'argc/argv' parameters have to be used)
    - as a string (in which case the 'name' and 'input' parameter have to be used).
 * 
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled, has to be 256 characters long
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
llvm_dsp_factory* createCDSPFactoryFromFile(const char* filename, int argc, const char *argv[], 
                                           const char* target, 
                                           char* error_msg, int opt_level);

/**
 * Create a Faust DSP factory from a DSP source code. The source code is either given :
    - as a .dsp source filename (in which case the 'argc/argv' parameters have to be used)
    - as a string (in which case the 'name' and 'input' parameter have to be used).
 * 
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled, has to be 256 characters long
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
llvm_dsp_factory* createCDSPFactoryFromString(const char* name_app, const char* dsp_content, int argc, const char *argv[], 
                                            const char* target, 
                                            char* error_msg, int opt_level);

/**
 * Destroy a Faust DSP factory.
 * 
 * @param factory - the DSP factory to be deleted.
*/                                 
void deleteCDSPFactory(llvm_dsp_factory* factory);
          
/**
 * Create a Faust DSP factory from a LLVM bitcode string.
 * 
 * @param bit_code - the LLVM bitcode string
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return the Faust DSP factory on success, otherwise a null pointer.
*/
llvm_dsp_factory* readCDSPFactoryFromBitcode(const char* bit_code, const char* target, int opt_level);

/**
 * Write a Faust DSP factory into a LLVM bitcode string.
 * 
 * @param factory - Faust DSP factory
 *
 * @return the LLVM bitcode as a string.
*/
const char* writeCDSPFactoryToBitcode(llvm_dsp_factory* factory);

/**
 * Create a Faust DSP factory from a LLVM bitcode file.
 * 
 * @param bit_code_path - the LLVM bitcode file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
*/
llvm_dsp_factory* readCDSPFactoryFromBitcodeFile(const char* bit_code_path, const char* target, int opt_level);

/**
 * Write a Faust DSP factory into a LLVM bitcode file.
 * 
 * @param factory - the Faust DSP factory
 * @param bit_code_path - the LLVM bitcode file pathname
 *
*/
void writeCDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const char* bit_code_path);

/**
 * Create a Faust DSP factory from a LLVM IR (textual) string.
 * 
 * @param ir_code - the LLVM IR (textual) string
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return the Faust DSP factory on success, otherwise a null pointer.
*/
llvm_dsp_factory* readCDSPFactoryFromIR(const char* ir_code, const char* target, int opt_level);

/**
 * Write a Faust DSP factory into a LLVM IR (textual) string.
 * 
 * @param factory - the Faust DSP factory
 *
 * @return the LLVM IR (textual) as a string.
*/
const char* writeCDSPFactoryToIR(llvm_dsp_factory* factory);

/**
 * Create a Faust DSP factory from a LLVM IR (textual) file.
 * 
 * @param ir_code_path - the LLVM IR (textual) file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
 *
 * @return the Faust DSP factory on success, otherwise a null pointer.
*/
llvm_dsp_factory* readCDSPFactoryFromIRFile(const char* ir_code_path, const char* target, int opt_level);

/**
 * Write a Faust DSP factory into a LLVM IR (textual) file.
 * 
 * @param factory - the Faust DSP factory
 * @param ir_code_path - the LLVM bitcode file pathname.
 *
*/
void writeCDSPFactoryToIRFile(llvm_dsp_factory* factory, const char* ir_code_path);

/**
 * Call global declarations with the given meta object.
 * 
 * @param factory - the Faust DSP factory
 * @param meta - the meta object to be used.
 *
*/
void metadataCDSPFactory(llvm_dsp_factory* factory, MetaGlue* meta);

/**
* Instance class
*/
int getNumInputsCDSPInstance(llvm_dsp* dsp);

int getNumOutputsCDSPInstance(llvm_dsp* dsp);

void initCDSPInstance(llvm_dsp* dsp, int samplingFreq);

void buildUserInterfaceCDSPInstance(llvm_dsp* dsp, UIGlue* interface);

void computeCDSPInstance(llvm_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output);

/**
 * Create a Faust DSP instance.
 * 
 * @param factory - the Faust DSP factory
 * 
 * @return the Faust DSP instance on success, otherwise a null pointer.
*/
llvm_dsp* createCDSPInstance(llvm_dsp_factory* factory);

/**
 * Destroy a Faust DSP instance.
 * 
 * @param dsp - the DSP instance to be deleted.
*/ 
void deleteCDSPInstance(llvm_dsp* dsp);

#ifdef __cplusplus
}
#endif

/*!
 @}
 */

#endif
