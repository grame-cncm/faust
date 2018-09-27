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

#ifndef __poly_wasm_dsp_tools__
#define __poly_wasm_dsp_tools__

#include "faust/dsp/wasm-dsp.h"
#include "faust/dsp/poly-dsp.h"

/**
 *  wasm backend based Polyphonic DSP factory class.
 */

struct wasm_dsp_poly_factory : public dsp_poly_factory {
    
    wasm_dsp_poly_factory(const std::string& name_app,
                        const std::string& dsp_content,
                        const std::vector<std::string>& argv,
                        std::string& error_msg)
    {
        fProcessFactory = createWasmDSPFactoryFromString(name_app, dsp_content, argv, error_msg);
        if (fProcessFactory) {
            fEffectFactory = createWasmDSPFactoryFromString(name_app, getEffectCode(dsp_content), argv, error_msg);
            if (!fEffectFactory) {
                std::cerr << "wasm_dsp_poly_factory : fEffectFactory " << error_msg << std::endl;
                // The error message is not really needed...
                error_msg = "";
            }
        } else {
            std::cerr << "wasm_dsp_poly_factory : fProcessFactory " << error_msg << std::endl;
            throw std::bad_alloc();
        }
    }
    
    virtual ~wasm_dsp_poly_factory()
    {
        deleteWasmDSPFactory(static_cast<wasm_dsp_factory*>(fProcessFactory));
        if (fEffectFactory) { deleteWasmDSPFactory(static_cast<wasm_dsp_factory*>(fEffectFactory)); }
    }
    
    /**
     * Create a Faust Polyphonic DSP factory from a DSP source code as a file.
     *
     * @param filename - the DSP filename
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters (Warning : aux files generation options will be filtered (-svg, ...) --> use generateAuxFiles)
     * @param error_msg - the error string to be filled
     * since the maximum value may change with new LLVM versions)
     *
     * @return a Polyphonic DSP factory on success, otherwise a null pointer.
     */
    static dsp_poly_factory* createWasmPolyDSPFactoryFromString(const std::string& name_app,
                                                                const std::string& dsp_content,
                                                                const std::vector<std::string>& argv,
                                                                std::string& error_msg)
    {
        try {
            return new wasm_dsp_poly_factory(name_app, dsp_content, argv, error_msg);
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
     * since the maximum value may change with new LLVM versions)
     *
     * @return a Polyphonic DSP factory on success, otherwise a null pointer.
     */
    static dsp_poly_factory* createWasmPolyDSPFactoryFromFile(const std::string& filename,
                                                              const std::vector<std::string>& argv,
                                                              std::string& error_msg)
    {
        return createWasmPolyDSPFactoryFromString("FaustDSP", pathToContent(filename), argv, error_msg);
    }
    
};


#ifdef EMCC
#include <emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;

vector<string> makeStringVector()
{
    vector<string> v;
    return v;
}

EMSCRIPTEN_BINDINGS(CLASS_wasm_dynamic_dsp_factory) {
    emscripten::function("makeStringVector", &makeStringVector);
    register_vector<string>("vector<string>");
    class_<wasm_dynamic_dsp_factory>("wasm_dsp_poly_factory")
    .constructor()
    .class_function("createWasmPolyDSPFactoryFromString",
                    &wasm_dsp_poly_factory::createWasmPolyDSPFactoryFromString,
                    allow_raw_pointers());
}

#endif

#endif // __poly_wasm_dsp__
