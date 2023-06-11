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

#ifdef WIN32
#pragma warning(disable : 4251 4275 4800)
#endif

#include "wasm_dynamic_dsp_aux.hh"
#include "Text.hh"
#include "compatibility.hh"

using namespace std;

#ifdef WIN32
#define strdup _strdup
#endif

#ifdef EMCC
#include <emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;
#endif

wasm_dsp_factory* wasm_dynamic_dsp_factory::createWasmDSPFactoryFromString2(const string& name_app,
                                                                        const string& dsp_content,
                                                                        const vector<string>& argv,
                                                                        bool internal_memory)
{
    int         argc1 = 0;
    const char* argv1[64];
    for (size_t i = 0; i < argv.size(); i++) {
        argv1[argc1++] = argv[i].c_str();
    }
    argv1[argc1] = nullptr;  // NULL terminated argv

    return createWasmDSPFactoryFromString(name_app, dsp_content, argc1, argv1,
                                                               wasm_dsp_factory::gErrorMessage, internal_memory);
}

string wasm_dynamic_dsp_factory::generateWasmFromString2(const string& name_app,
                                                     const string& dsp_content,
                                                     const vector<string>& argv,
                                                     bool internal_memory)
{
    int         argc1 = 0;
    const char* argv1[64];
    for (size_t i = 0; i < argv.size(); i++) {
        argv1[argc1++] = argv[i].c_str();
    }
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    return generateWasmFromString(name_app, dsp_content, argc1, argv1, wasm_dsp_factory::gErrorMessage, internal_memory);
}

// C++ API

LIBFAUST_API wasm_dsp_factory* createWasmDSPFactoryFromFile(const string& filename, int argc, const char* argv[],
                                                      string& error_msg, bool internal_memory)
{
    string base = basename((char*)filename.c_str());
    size_t pos  = filename.find(".dsp");

    if (pos != string::npos) {
        return createWasmDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc, argv, error_msg,
                                              internal_memory);
    } else {
        error_msg = "ERROR : file extension is not the one expected (.dsp expected)\n";
        return nullptr;
    }
}

LIBFAUST_API wasm_dsp_factory* createWasmDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc,
                                                            const char* argv[], string& error_msg, bool internal_memory)
{
    string expanded_dsp_content, sha_key;

    if ((expanded_dsp_content = sha1FromDSP(name_app, dsp_content, argc, argv, sha_key)) == "") {
        return nullptr;
    } else {
        
        dsp_factory_table<SDsp_factory>::factory_iterator it;
        if (wasm_dsp_factory::gWasmFactoryTable.getFactory(sha_key, it)) {
            SDsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else {
            
            int         argc1 = 0;
            const char* argv1[64];
            argv1[argc1++] = "faust";
            argv1[argc1++] = "-lang";
            argv1[argc1++] = (internal_memory) ? "wasm-i" : "wasm-e";
            argv1[argc1++] = "-o";
            argv1[argc1++] = "binary";
            // Copy argument
            for (int i = 0; i < argc; i++) {
                argv1[argc1++] = argv[i];
            }
            argv1[argc1] = nullptr;  // NULL terminated argv

            dsp_factory_base* dsp_factory_aux = createFactory(name_app, dsp_content, argc1, argv1, error_msg, true);
            if (dsp_factory_aux) {
                dsp_factory_aux->setName(name_app);
                wasm_dsp_factory* factory = new wasm_dsp_factory(dsp_factory_aux);
                wasm_dsp_factory::gWasmFactoryTable.setFactory(factory);
                factory->setSHAKey(sha_key);
                factory->setDSPCode(expanded_dsp_content);
                return factory;
            } else {
                return nullptr;
            }
        }
    }
}

LIBFAUST_API wasm_dsp_factory* createWasmDSPFactoryFromSignals(const string& name_app, tvec signals,
                                                            int argc, const char* argv[], string& error_msg,
                                                            bool internal_memory)
{
    int         argc1 = 0;
    const char* argv1[64];
    argv1[argc1++] = "faust";
    argv1[argc1++] = "-lang";
    // argv1[argc1++] = (internal_memory) ? "wasm-i" : "wasm-e";
    argv1[argc1++] = (internal_memory) ? "wasm-ib" : "wasm-eb";
    argv1[argc1++] = "-o";
    argv1[argc1++] = "binary";
    // Copy argument
    for (int i = 0; i < argc; i++) {
        argv1[argc1++] = argv[i];
    }
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    dsp_factory_base* dsp_factory_aux = createFactory(name_app, signals, argc1, argv1, error_msg);
    if (dsp_factory_aux) {
        dsp_factory_aux->setName(name_app);
        wasm_dsp_factory* factory = new wasm_dsp_factory(dsp_factory_aux);
        wasm_dsp_factory::gWasmFactoryTable.setFactory(factory);
        return factory;
    } else {
        return nullptr;
    }
}

LIBFAUST_API string generateWasmFromString(const string& name_app, const string& dsp_content, int argc,
                                         const char* argv[], string& error_msg, bool internal_memory)
{
    int         argc1 = 0;
    const char* argv1[64];
    argv1[argc1++] = "faust";
    argv1[argc1++] = "-lang";
    // argv1[argc1++] = (internal_memory) ? "wasm-i" : "wasm-e";
    argv1[argc1++] = (internal_memory) ? "wasm-ib" : "wasm-eb";
    argv1[argc1++] = "-o";
    argv1[argc1++] = "binary";
    for (int i = 0; i < argc; i++) {
        argv1[argc1++] = argv[i];
    }
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    dsp_factory_base* dsp_factory_aux = createFactory(name_app, dsp_content, argc1, argv1, error_msg, true);
    return (dsp_factory_aux) ? dsp_factory_aux->getBinaryCode() : "";
}

#ifdef __cplusplus
extern "C" {
#endif

LIBFAUST_API void deleteAllWasmCDSPFactories()
{
    deleteAllWasmDSPFactories();
}

LIBFAUST_API wasm_dsp_factory* createWasmCDSPFactoryFromFile2(const char* filename, int argc, const char* argv[],
                                                        char* error_msg, bool internal_memory)
{
    string error_msg_aux;
    wasm_dsp_factory* factory = createWasmDSPFactoryFromFile(filename, argc, argv, error_msg_aux, internal_memory);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

LIBFAUST_API wasm_dsp_factory* createWasmCDSPFactoryFromString2(const char* name_app, const char* dsp_content, int argc,
                                                          const char* argv[], char* error_msg, bool internal_memory)
{
    string error_msg_aux;
    wasm_dsp_factory* factory =
        createWasmDSPFactoryFromString(name_app, dsp_content, argc, argv, error_msg_aux, internal_memory);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}
    
LIBFAUST_API wasm_dsp_factory* createWasmCDSPFactoryFromSignals2(const char* name_app, tvec signals,
                                                           int argc, const char* argv[], char* error_msg,
                                                           bool internal_memory)
{
    string error_msg_aux;
    wasm_dsp_factory* factory =
        createWasmDSPFactoryFromSignals(name_app, signals, argc, argv, error_msg_aux, internal_memory);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

#ifdef __cplusplus
}
#endif

#ifdef EMCC

vector<string> makeStringVector()
{
    return vector<string>();
}

EMSCRIPTEN_BINDINGS(CLASS_wasm_dynamic_dsp_factory)
{
    emscripten::function("makeStringVector", &makeStringVector);
    register_vector<string>("vector<string>");
    class_<wasm_dynamic_dsp_factory>("wasm_dynamic_dsp_factory")
        .constructor()
        .class_function("createWasmDSPFactoryFromString2", &wasm_dynamic_dsp_factory::createWasmDSPFactoryFromString2,
                        allow_raw_pointers())
        .class_function("generateWasmFromString2", &wasm_dynamic_dsp_factory::createWasmDSPFactoryFromString2,
                    allow_raw_pointers());
}

#endif
