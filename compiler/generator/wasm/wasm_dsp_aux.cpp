/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "compatibility.hh"
#include "wasm_dsp_aux.hh"
#include "dsp_factory.hh"
#include "Text.hh"

typedef class faust_smartptr<wasm_dsp_factory> SDsp_factory;

dsp_factory_table<SDsp_factory> gWasmFactoryTable;

wasm_dsp_factory::~wasm_dsp_factory()
{
    delete fFactory;
}

std::string wasm_dsp_factory::getName() { return fFactory->getName(); }

std::string wasm_dsp_factory::getSHAKey() { return fFactory->getSHAKey(); }
void wasm_dsp_factory::setSHAKey(std::string sha_key) { fFactory->setSHAKey(sha_key); }

std::string wasm_dsp_factory::getDSPCode() { return fFactory->getDSPCode(); }
void wasm_dsp_factory::setDSPCode(std::string code) { fFactory->setDSPCode(code); }

wasm_dsp* wasm_dsp_factory::createDSPInstance() { return nullptr; }

void wasm_dsp_factory::setMemoryManager(dsp_memory_manager* manager) {}
dsp_memory_manager* wasm_dsp_factory::getMemoryManager() { return nullptr; }

void wasm_dsp_factory::write(std::ostream* out, bool binary, bool small) { fFactory->write(out, binary, small); }
void wasm_dsp_factory::writeAux(std::ostream* out, bool binary, bool small) { fFactory->writeAux(out, binary, small); }

std::string wasm_dsp_factory::getBinaryCode() { return fFactory->getBinaryCode(); }

// C++ API

EXPORT wasm_dsp_factory* createWasmDSPFactoryFromFile(const string& filename,
                                                      int argc, const char* argv[],
                                                      string& error_msg,
                                                      bool internal_memory)
{
    string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    
    if (pos != string::npos) {
        return createWasmDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc, argv, error_msg, internal_memory);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)";
        return NULL;
    }
}

EXPORT wasm_dsp_factory* createWasmDSPFactoryFromString(const string& name_app,
                                                        const string& dsp_content,
                                                        int argc, const char* argv[],
                                                        string& error_msg,
                                                        bool internal_memory)
{
    string expanded_dsp_content = "";
    string sha_key = "";
   
    int argc1 = 0;
    const char* argv1[64];

    argv1[argc1++] = "faust";
    argv1[argc1++] = "-lang";
    //argv1[argc1++] = (internal_memory) ? "wasm-i" : "wasm-e";
    argv1[argc1++] = (internal_memory) ? "wasm-ib" : "wasm-eb";
    argv1[argc1++] = "-o";
    argv1[argc1++] = "binary";

    for (int i = 0; i < argc; i++) {
        argv1[argc1++] = argv[i];
    }
    argv1[argc1] = 0;  // NULL terminated argv

    dsp_factory_base* dsp_factory_aux = compileFaustFactory(argc1, argv1,
                                                            name_app.c_str(),
                                                            dsp_content.c_str(),
                                                            error_msg,
                                                            true);
    if (dsp_factory_aux) {
        dsp_factory_aux->setName(name_app);
        wasm_dsp_factory* factory = new wasm_dsp_factory(dsp_factory_aux);
        gWasmFactoryTable.setFactory(factory);
        factory->setSHAKey(sha_key);
        factory->setDSPCode(expanded_dsp_content);
        return factory;
    } else {
        return NULL;
    }
}

EXPORT bool deleteWasmDSPFactory(wasm_dsp_factory* factory)
{
    return (factory) ? gWasmFactoryTable.deleteDSPFactory(factory): false;
}

// C API

static WasmModule* createWasmCDSPFactoryAux(wasm_dsp_factory* factory, const string& error_msg_aux, char* error_msg)
{
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    if (factory) {
        WasmModule* res = static_cast<WasmModule*>(calloc(1, sizeof(WasmModule)));
        
        // 'Binary' string, so directly copy its raw content
        string code = factory->getBinaryCode();
        res->fCodeSize = code.size();
        res->fCode = (char*)malloc(res->fCodeSize);
        memcpy(res->fCode, code.c_str(), res->fCodeSize);
        
        stringstream dst2;
        factory->writeAux(&dst2, false, false);
        res->fHelpers = strdup(flatten(dst2.str()).c_str());
        
        return res;
        // And keep factory...
    } else {
        return NULL;
    }
}

EXPORT WasmModule* createWasmCDSPFactoryFromFile(const char* filename, int argc, const char* argv[], char* error_msg, bool internal_memory)
{
    string error_msg_aux;
    wasm_dsp_factory* factory = createWasmDSPFactoryFromFile(filename, argc, argv, error_msg_aux, internal_memory);
    return createWasmCDSPFactoryAux(factory, error_msg_aux, error_msg);
}

EXPORT WasmModule* createWasmCDSPFactoryFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg, bool internal_memory)
{
    string error_msg_aux;
    wasm_dsp_factory* factory = createWasmDSPFactoryFromString(name_app, dsp_content, argc, argv, error_msg_aux, internal_memory);
    return createWasmCDSPFactoryAux(factory, error_msg_aux, error_msg);
}

EXPORT const char* getWasmCModule(WasmModule* module)
{
    return module->fCode;
}

EXPORT int getWasmCModuleSize(WasmModule* module)
{
    return module->fCodeSize;
}

EXPORT const char* getWasmCHelpers(WasmModule* module)
{
    return module->fHelpers;
}

EXPORT void freeWasmCModule(WasmModule* module)
{
    free((void*)module->fCode);
    free((void*)module->fHelpers);
    free(module);
}

