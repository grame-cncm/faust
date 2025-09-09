/************************** BEGIN poly-wasm-dsp.h **************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __poly_wasm_dsp__
#define __poly_wasm_dsp__

#include "faust/dsp/wasm-dsp.h"
#include "faust/dsp/poly-dsp.h"

/**
 *  wasm backend based Polyphonic DSP factory class.
 */
struct wasm_dsp_poly_factory : public dsp_poly_factory {
    
    wasm_dsp_poly_factory(const std::string& name_app,
                          const std::string& dsp_content,
                          int argc, const char* argv[],
                          std::string& error_msg,
                          bool internal_memory)
    {
        fProcessFactory = createWasmDSPFactoryFromString(name_app, dsp_content, argc, argv, error_msg, internal_memory);
        if (fProcessFactory) {
            fEffectFactory = createWasmDSPFactoryFromString(name_app, getEffectCode(dsp_content), argc, argv, error_msg, internal_memory);
            if (!fEffectFactory) {
                std::cerr << "wasm_dsp_poly_factory : fEffectFactory " << error_msg;
                // The error message is not really needed...
                error_msg = "";
            }
        } else {
            std::cerr << "wasm_dsp_poly_factory : fProcessFactory " << error_msg;
            throw std::bad_alloc();
        }
    }
    
    wasm_dsp_poly_factory(wasm_dsp_factory* process_factory = NULL,
                          wasm_dsp_factory* effect_factory = NULL)
        : dsp_poly_factory(process_factory, effect_factory)
    {}
    
    virtual ~wasm_dsp_poly_factory()
    {
        deleteWasmDSPFactory(static_cast<wasm_dsp_factory*>(fProcessFactory));
        deleteWasmDSPFactory(static_cast<wasm_dsp_factory*>(fEffectFactory));
    }
    
    dsp_poly* createPolyDSPInstance(int nvoices, bool control, bool group)
    {
        return dsp_poly_factory::createPolyDSPInstance(nvoices, control, group);
    }
    
    void deletePolyDSPInstance(dsp_poly* dsp)
    {
        delete dsp;
    }
    
    static wasm_dsp_poly_factory* createWasmPolyDSPFactoryFromString2(const std::string&              name_app,
                                                                      const std::string&              dsp_content,
                                                                      const std::vector<std::string>& argv,
                                                                      bool                            internal_memory);
    
    static void deleteWasmPolyDSPFactory(wasm_dsp_poly_factory* factory) { delete factory; }
    
};

/**
 * Create a Faust Polyphonic DSP factory from a DSP source code as a file.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
 * @param error_msg - the error string to be filled
 * @param internal_memory - whether to use an internally allocated memory block for wasm module
 *
 * @return a Polyphonic DSP factory on success, otherwise a null pointer.
 */
static wasm_dsp_poly_factory* createWasmPolyDSPFactoryFromString(const std::string& name_app,
                                                                 const std::string& dsp_content,
                                                                 int argc, const char* argv[],
                                                                 std::string& error_msg,
                                                                 bool internal_memory)
{
    try {
        return new wasm_dsp_poly_factory(name_app, dsp_content, argc, argv, error_msg, internal_memory);
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
 * @param error_msg - the error string to be filled
 * @param internal_memory - whether to use an internally allocated memory block for wasm module
 *
 * @return a Polyphonic DSP factory on success, otherwise a null pointer.
 */
static wasm_dsp_poly_factory* createWasmPolyDSPFactoryFromFile(const std::string& filename,
                                                               int argc, const char* argv[],
                                                               std::string& error_msg,
                                                               bool internal_memory)
{
    return createWasmPolyDSPFactoryFromString("FaustDSP", pathToContent(filename), argc, argv, error_msg, internal_memory);
}


wasm_dsp_poly_factory* wasm_dsp_poly_factory::createWasmPolyDSPFactoryFromString2(const std::string&              name_app,
                                                                                  const std::string&              dsp_content,
                                                                                  const std::vector<std::string>& argv,
                                                                                  bool                            internal_memory)
{
    int         argc1 = 0;
    const char* argv1[64];
    for (size_t i = 0; i < argv.size(); i++) {
        argv1[argc1++] = argv[i].c_str();
    }
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    wasm_dsp_poly_factory* factory = createWasmPolyDSPFactoryFromString(name_app, dsp_content, argc1, argv1,
                                                                        wasm_dsp_factory::gErrorMessage, internal_memory);
    return factory;
}

/**
 * Create a Faust Polyphonic DSP factory from a wasm file.
 *
 * @param machine_code_path - the wasm file pathname
 * @param error_msg - the error string to be filled
*
 * @return the Polyphonic DSP factory on success, otherwise a null pointer.
 */
static dsp_poly_factory* readWasmPolyDSPFactoryFromMachineFile(const std::string& machine_code_path, std::string& error_msg)
{
    std::string process_path = machine_code_path + "_machine_process";
    std::string effect_path = machine_code_path + "_machine_effect";
    wasm_dsp_factory* process_factory = readWasmDSPFactoryFromBitcodeFile(process_path, error_msg);
    wasm_dsp_factory* effect_factory = readWasmDSPFactoryFromBitcodeFile(effect_path, error_msg);
    if (process_factory) {
        return new wasm_dsp_poly_factory(process_factory, effect_factory);
    } else {
        process_factory = readWasmDSPFactoryFromBitcodeFile(machine_code_path, error_msg);
        return (process_factory) ? new wasm_dsp_poly_factory(process_factory, NULL) : NULL;
    }
}

/**
 * Write a Faust Polyphonic DSP factory into a wasm file.
 *
 * @param factory - the DSP factory
 * @param machine_code_path - the machine code file pathname
 *
 */
static void writeWasmPolyDSPFactoryToMachineFile(dsp_poly_factory* factory, const std::string& machine_code_path)
{
    std::string process_path, effect_path;
    if (factory->fEffectFactory) {
        process_path = machine_code_path + "_machine_process";
        effect_path = machine_code_path + "_machine_effect";
        writeWasmDSPFactoryToBitcodeFile(static_cast<wasm_dsp_factory*>(factory->fEffectFactory), effect_path);
    } else {
        process_path = machine_code_path;
    }
    writeWasmDSPFactoryToBitcodeFile(static_cast<wasm_dsp_factory*>(factory->fProcessFactory), process_path);
}

#endif // __poly_wasm_dsp__
/************************** END poly-wasm-dsp.h **************************/
