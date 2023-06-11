/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef WASM_DYNAMIC_DSP_AUX_H
#define WASM_DYNAMIC_DSP_AUX_H

#include <cstdlib>
#include <string>
#include <vector>

#include "wasm_dsp_aux.hh"

class LIBFAUST_API wasm_dynamic_dsp_factory : public wasm_dsp_factory {
   protected:
   public:
    wasm_dynamic_dsp_factory() {}
    wasm_dynamic_dsp_factory(dsp_factory_base* factory) : wasm_dsp_factory(factory) {}

    virtual ~wasm_dynamic_dsp_factory() {}

    static wasm_dsp_factory* createWasmDSPFactoryFromString2(const std::string& name_app,
                                                        const std::string& dsp_content,
                                                        const std::vector<std::string>& argv,
                                                        bool internal_memory);
    
    static std::string generateWasmFromString2(const std::string& name_app,
                                            const std::string& dsp_content,
                                            const std::vector<std::string>& argv,
                                            bool internal_memory);
};

LIBFAUST_API wasm_dsp_factory* createWasmDSPFactoryFromFile(const std::string& filename, int argc, const char* argv[], std::string& error_msg, bool internal_memory);

LIBFAUST_API wasm_dsp_factory* createWasmDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content, int argc, const char* argv[], std::string& error_msg,
                                                        bool internal_memory);

LIBFAUST_API wasm_dsp_factory* createWasmDSPFactoryFromSignals(const std::string& name_app, tvec signals,
                                                        int argc, const char* argv[], std::string& error_msg,
                                                        bool internal_memory);

LIBFAUST_API std::string generateWasmFromString(const std::string& name_app, const std::string& dsp_content,
                                          int argc, const char* argv[], std::string& error_msg,
                                          bool internal_memory);

#ifdef __cplusplus
extern "C" {
#endif

LIBFAUST_API wasm_dsp_factory* createWasmCDSPFactoryFromFile2(const char* filename, int argc, const char* argv[],
                                                        char* error_msg, bool internal_memory);

LIBFAUST_API wasm_dsp_factory* createWasmCDSPFactoryFromString2(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg, bool internal_memory);

LIBFAUST_API wasm_dsp_factory* createWasmCDSPFactoryFromSignals2(const char* name_app, tvec signals,
                                                           int argc, const char* argv[],
                                                           char* error_msg,
                                                           bool internal_memory);

LIBFAUST_API bool deleteWasmCDSPFactory(wasm_dsp_factory* factory);

LIBFAUST_API wasm_dsp_factory* readWasmCDSPFactoryFromMachine(const char* wasm_code, char* error_msg);

LIBFAUST_API char* writeWasmCDSPFactoryToMachine(wasm_dsp_factory* factory);

LIBFAUST_API wasm_dsp_factory* readWasmCDSPFactoryFromMachineFile(const char* wasm_code_path, char* error_msg);

LIBFAUST_API void writeWasmCDSPFactoryToMachineFile(wasm_dsp_factory* factory, const char* wasm_code_path);

/**
 * Get the error message after an exception occured.
 *
 * @return the error as a static string.
 */
LIBFAUST_API const char* getErrorAfterException();

/**
 *  Cleanup library global context after an exception occured.
 *
 */
LIBFAUST_API void cleanupAfterException();

#ifdef __cplusplus
}
#endif

#endif
