/************************** BEGIN poly-wasm-dsp.h **************************/
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

#ifndef __poly_wasm_dsp__
#define __poly_wasm_dsp__

#ifdef EMCC
wasm_dsp_factory* createWasmDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content, int argc,
                                                 const char* argv[], std::string& error_msg, bool internal_memory)
{
    return nullptr;
}
std::string pathToContent(const string& str) { return ""; }
#else
#include "faust/dsp/wasm-dsp.h"
#endif

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
 * @param internal_memory - whether to use an internallay allocated memory block for wasm module
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
 * @param internal_memory - whether to use an internallay allocated memory block for wasm module
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
    wasm_dsp_factory* process_factory = readWasmDSPFactoryFromMachineFile(process_path, error_msg);
    wasm_dsp_factory* effect_factory = readWasmDSPFactoryFromMachineFile(effect_path, error_msg);
    if (process_factory) {
        return new dsp_poly_factory(process_factory, effect_factory);
    } else {
        wasm_dsp_factory* process_factory = readWasmDSPFactoryFromMachineFile(machine_code_path, error_msg);
        return (process_factory) ? new dsp_poly_factory(process_factory, NULL) : NULL;
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
        writeWasmDSPFactoryToMachineFile(static_cast<wasm_dsp_factory*>(factory->fEffectFactory), effect_path);
    } else {
        process_path = machine_code_path;
    }
    writeWasmDSPFactoryToMachineFile(static_cast<wasm_dsp_factory*>(factory->fProcessFactory), process_path);
}

#ifdef EMCC
#include <emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(CLASS_MapUI) {
    
    class_<MapUI>("MapUI")
    .constructor();
}

EMSCRIPTEN_BINDINGS(CLASS_dsp_poly_factory) {
    class_<dsp_poly_factory>("dsp_poly_factory")
    .constructor<dsp_poly_factory*, dsp_poly_factory*>();
}

EMSCRIPTEN_BINDINGS(CLASS_wasm_dsp_poly_factory) {
    class_<wasm_dsp_poly_factory>("wasm_dsp_poly_factory")
    .constructor<wasm_dsp_factory*, wasm_dsp_factory*>()
    .function("createPolyDSPInstance", &wasm_dsp_poly_factory::createPolyDSPInstance, allow_raw_pointers())
    .function("deletePolyDSPInstance", &wasm_dsp_poly_factory::deletePolyDSPInstance, allow_raw_pointers())
    .class_function("createWasmPolyDSPFactoryFromString2",&wasm_dsp_poly_factory::createWasmPolyDSPFactoryFromString2, allow_raw_pointers())
    .class_function("deleteWasmPolyDSPFactory", &wasm_dsp_poly_factory::deleteWasmPolyDSPFactory, allow_raw_pointers());
}

EMSCRIPTEN_BINDINGS(CLASS_dsp_poly)
{
    class_<dsp_poly>("dsp_poly")
    .constructor<dsp*>()
    // DSP API
    .function("getNumInputs", &dsp_poly::getNumInputs, allow_raw_pointers())
    .function("getNumOutputs", &dsp_poly::getNumOutputs, allow_raw_pointers())
    .function("getSampleRate", &dsp_poly::getSampleRate, allow_raw_pointers())
    .function("init", &dsp_poly::init, allow_raw_pointers())
    .function("instanceInit", &dsp_poly::instanceInit, allow_raw_pointers())
    .function("instanceConstants", &dsp_poly::instanceConstants, allow_raw_pointers())
    .function("instanceResetUserInterface", &dsp_poly::instanceResetUserInterface, allow_raw_pointers())
    .function("instanceClear", &dsp_poly::instanceClear, allow_raw_pointers())
    .function("clone", &dsp_poly::clone, allow_raw_pointers())
    .function("compute", &dsp_poly::computeJS, allow_raw_pointers())
    // Additional JSON based API
    .function("getJSON", &dsp_poly::getJSON, allow_raw_pointers())
    .function("setParamValue", &dsp_poly::setParamValue, allow_raw_pointers())
    .function("getParamValue", &dsp_poly::getParamValue, allow_raw_pointers())
    // MIDI API
    .function("keyOn", &dsp_poly::keyOn, allow_raw_pointers())
    .function("keyOff", &dsp_poly::keyOff, allow_raw_pointers())
    .function("keyPress", &dsp_poly::keyPress, allow_raw_pointers())
    .function("chanPress", &dsp_poly::chanPress, allow_raw_pointers())
    .function("ctrlChange", &dsp_poly::ctrlChange, allow_raw_pointers())
    .function("ctrlChange14bits", &dsp_poly::ctrlChange14bits, allow_raw_pointers())
    .function("pitchWheel", &dsp_poly::pitchWheel, allow_raw_pointers())
    .function("progChange", &dsp_poly::progChange, allow_raw_pointers());
}

#endif

#endif // __poly_wasm_dsp__
/**************************  END  poly-wasm-dsp.h **************************/
