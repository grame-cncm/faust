/************************** BEGIN poly-llvm-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
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

#ifndef __poly_llvm_dsp__
#define __poly_llvm_dsp__

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/misc.h"

/**
 *  LLVM backend based Polyphonic DSP factory class.
 */

struct llvm_dsp_poly_factory : public dsp_poly_factory {
    
    llvm_dsp_poly_factory(const std::string& name_app,
                          const std::string& dsp_content,
                          int argc, const char* argv[],
                          const std::string& target,
                          std::string& error_msg,
                          int opt_level = -1)
    {
        fProcessFactory = createDSPFactoryFromString(name_app, dsp_content, argc, argv, target, error_msg);
        if (fProcessFactory) {
            fEffectFactory = createDSPFactoryFromString(name_app, getEffectCode(dsp_content), argc, argv, target, error_msg);
            if (!fEffectFactory) {
                std::cerr << "llvm_dsp_poly_factory : fEffectFactory " << error_msg;
                // The error message is not really needed...
                error_msg = "";
            }
        } else {
            std::cerr << "llvm_dsp_poly_factory : fProcessFactory " << error_msg;
            throw std::bad_alloc();
        }
    }
    
    virtual ~llvm_dsp_poly_factory()
    {
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(fProcessFactory));
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(fEffectFactory));
    }

};

/**
 * Create a Faust Polyphonic DSP factory from a DSP source code as a file.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions)
 *
 * @return a Polyphonic DSP factory on success, otherwise a null pointer.
 */
static llvm_dsp_poly_factory* createPolyDSPFactoryFromString(const std::string& name_app,
                                                             const std::string& dsp_content,
                                                             int argc, const char* argv[],
                                                             const std::string& target,
                                                             std::string& error_msg,
                                                             int opt_level = -1)
{
    try {
        return new llvm_dsp_poly_factory(name_app, dsp_content, argc, argv, target, error_msg, opt_level);
    } catch (...) {
        return NULL;
    }
}

/**
 * Create a Faust Polyphonic DSP factory from a DSP source code as a string.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param target - the LLVM machine target (using empty string will take current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions)
 *
 * @return a Polyphonic DSP factory on success, otherwise a null pointer.
 */
static llvm_dsp_poly_factory* createPolyDSPFactoryFromFile(const std::string& filename,
                                                           int argc, const char* argv[],
                                                           const std::string& target,
                                                           std::string& error_msg,
                                                           int opt_level = -1)
{
    return createPolyDSPFactoryFromString("FaustDSP", pathToContent(filename), argc, argv, target, error_msg, opt_level);
}

/**
 * Create a Faust Polyphonic DSP factory from a LLVM bitcode file.
 *
 * @param bit_code_path - the LLVM bitcode file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling
 * createDSPFactory can possibly be used.
 *
 * @return the Polyphonic DSP factory on success, otherwise a null pointer.
 */
static dsp_poly_factory* readPolyDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, std::string& error_msg, int opt_level = -1)
{
    std::string process_path = bit_code_path + "_bitcode_process.bc";
    std::string effect_path = bit_code_path + "_bicode_effect.bc";
    llvm_dsp_factory* process_factory = readDSPFactoryFromBitcodeFile(process_path, target, error_msg, opt_level);
    llvm_dsp_factory* effect_factory = readDSPFactoryFromBitcodeFile(effect_path, target, error_msg, opt_level);
    if (process_factory) {
        return new dsp_poly_factory(process_factory, effect_factory);
    } else {
        llvm_dsp_factory* process_factory = readDSPFactoryFromBitcodeFile(bit_code_path, target, error_msg, opt_level);
        return (process_factory) ? new dsp_poly_factory(process_factory, NULL) : NULL;
    }
}

/**
 * Write a Faust Polyphonic DSP factory into a LLVM bitcode file.
 *
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings).
 *
 */
static void writePolyDSPFactoryToBitcodeFile(dsp_poly_factory* factory, const std::string& bit_code_path)
{
    std::string process_path = bit_code_path + "_bitcode_process.bc";
    if (factory->fEffectFactory) {
        std::string effect_path = bit_code_path + "_bicode_effect.bc";
        writeDSPFactoryToBitcodeFile(static_cast<llvm_dsp_factory*>(factory->fEffectFactory), effect_path);
    }
    writeDSPFactoryToBitcodeFile(static_cast<llvm_dsp_factory*>(factory->fProcessFactory), process_path);
}

/**
 * Create a Faust Polyphonic DSP factory from a LLVM IR (textual) file.
 *
 * @param bit_code_path - the LLVM bitcode file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling
 * createPolyDSPFactory can possibly be used.
 *
 * @return the Polyphonic DSP factory on success, otherwise a null pointer.
 */
static dsp_poly_factory* readPolyDSPFactoryFromIRFile(const std::string& ir_code_path, const std::string& target, std::string& error_msg, int opt_level = -1)
{
    std::string process_path = ir_code_path + "_ir_process.ll";
    std::string effect_path = ir_code_path + "_ir_effect.ll";
    llvm_dsp_factory* process_factory = readDSPFactoryFromIRFile(process_path, target, error_msg, opt_level);
    llvm_dsp_factory* effect_factory = readDSPFactoryFromIRFile(effect_path, target, error_msg, opt_level);
    if (process_factory) {
        return new dsp_poly_factory(process_factory, effect_factory);
    } else {
        llvm_dsp_factory* process_factory = readDSPFactoryFromIRFile(ir_code_path, target, error_msg, opt_level);
        return (process_factory) ? new dsp_poly_factory(process_factory, NULL) : NULL;
    }
}

/**
 * Write a Faust Polyphonic DSP factory into a LLVM IR (textual) file.
 *
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings).
 *
 */
static void writePolyDSPFactoryToIRFile(dsp_poly_factory* factory, const std::string& ir_code_path)
{
    std::string process_path = ir_code_path + "_ir_process.ll";
    if (factory->fEffectFactory) {
        std::string effect_path = ir_code_path + "_ir_effect.ll";
        writeDSPFactoryToIRFile(static_cast<llvm_dsp_factory*>(factory->fEffectFactory), effect_path);
    }
    writeDSPFactoryToIRFile(static_cast<llvm_dsp_factory*>(factory->fProcessFactory), process_path);
}

/**
 * Create a Faust Polyphonic DSP factory from a machine code file.
 *
 * @param bit_code_path - the LLVM bitcode file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings)
 * @param error_msg - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value'
 * since the maximum value may change with new LLVM versions). A higher value than the one used when calling
 * createPolyDSPFactory can possibly be used.
 *
 * @return the Polyphonic DSP factory on success, otherwise a null pointer.
 */
static dsp_poly_factory* readPolyDSPFactoryFromMachineFile(const std::string& machine_code_path, const std::string& target, std::string& error_msg)
{
    std::string process_path = machine_code_path + "_machine_process.o";
    std::string effect_path = machine_code_path + "_machine_effect.o";
    llvm_dsp_factory* process_factory = readDSPFactoryFromMachineFile(process_path, target, error_msg);
    llvm_dsp_factory* effect_factory = readDSPFactoryFromMachineFile(effect_path, target, error_msg);
    if (process_factory) {
        return new dsp_poly_factory(process_factory, effect_factory);
    } else {
        llvm_dsp_factory* process_factory = readDSPFactoryFromMachineFile(machine_code_path, target, error_msg);
        return (process_factory) ? new dsp_poly_factory(process_factory, NULL) : NULL;
    }
}

/**
 * Write a Faust Polyphonic DSP factory into a machine code file.
 *
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 * @param target - the LLVM machine target (using empty string will takes current machine settings).
 *
 */
static void writePolyDSPFactoryToMachineFile(dsp_poly_factory* factory, const std::string& machine_code_path, const std::string& target)
{
    std::string process_path = machine_code_path + "_machine_process.o";
    if (factory->fEffectFactory) {
        std::string effect_path = machine_code_path + "_machine_effect.o";
        writeDSPFactoryToMachineFile(static_cast<llvm_dsp_factory*>(factory->fEffectFactory), effect_path, target);
    }
    writeDSPFactoryToMachineFile(static_cast<llvm_dsp_factory*>(factory->fProcessFactory), process_path, target);
}

#endif // __poly_llvm_dsp_tools__
/**************************  END  poly-llvm-dsp.h **************************/
