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

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>

#ifdef WIN32
#pragma warning(disable : 4251 4275 4800)
#endif

#include "compatibility.hh"
#include "libfaust.h"
#include "wasm_dsp_aux.hh"

#include "faust/gui/JSONUIDecoder.h"

#ifdef EMCC
#include <emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;
#endif

using namespace std;

dsp_factory_table<SDsp_factory> wasm_dsp_factory::gWasmFactoryTable;

#ifdef EMCC

#ifndef FAUST_LIB
#include "faust/dsp/poly-wasm-dsp.h"
#endif

LIBFAUST_API wasm_dsp_factory::wasm_dsp_factory(int instance, const string& json)
{
    fFactory  = nullptr;
    fInstance = instance;
    fDecoder  = createJSONUIDecoder(json);
}

LIBFAUST_API wasm_dsp_factory::~wasm_dsp_factory()
{
    delete fFactory;
    delete fDecoder;
}

LIBFAUST_API wasm_dsp_factory* wasm_dsp_factory::createWasmDSPFactory(int           instance,
                                                                      const string& json)
{
    wasm_dsp_factory* factory = new wasm_dsp_factory(instance, json);
    wasm_dsp_factory::gWasmFactoryTable.setFactory(factory);
    return factory;
}

LIBFAUST_API string wasm_dsp_factory::extractJSON(const string& code)
{
    /* Deactivated for 'wasm' branch version
        connectMemory();
    */
    if (code != "") {
        WasmBinaryReader reader(code);
        reader.read();
        return reader.json;
    } else {
        return "";
    }
}

LIBFAUST_API wasm_dsp_factory* readWasmDSPFactoryFromMachine(const string& machine_code,
                                                             string&       error_msg)
{
    wasm_dsp_factory* factory =
        new wasm_dsp_factory(new text_dsp_factory_aux("MachineDSP", "", "", machine_code, ""));
    wasm_dsp_factory::gWasmFactoryTable.setFactory(factory);
    return factory;
}

LIBFAUST_API string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory)
{
    return factory->getBinaryCode();
}

LIBFAUST_API wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(const string& machine_code_path,
                                                                 string&       error_msg)
{
    ifstream infile;
    infile.open(machine_code_path, ifstream::in | ifstream::binary);

    if (infile.is_open()) {
        // get length of file:
        infile.seekg(0, infile.end);
        int length = infile.tellg();
        infile.seekg(0, infile.beg);

        // read code
        char* machine_code = new char[length];
        infile.read(machine_code, length);

        // create factory
        wasm_dsp_factory* factory = readWasmDSPFactoryFromMachine(
            string(machine_code, length), error_msg);  // Keep the binary string

        infile.close();
        delete[] machine_code;

        return factory;
    } else {
        error_msg = "ERROR : cannot open '" + machine_code_path + "' file\n";
        return nullptr;
    }
}

LIBFAUST_API void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory,
                                                   const string&     machine_code_path)
{
    ofstream outfile;
    outfile.open(machine_code_path, ofstream::out | ofstream::binary);
    if (outfile.is_open()) {
        outfile << factory->getBinaryCode();
        outfile.close();
    } else {
        cerr << "writeWasmDSPFactoryToMachineFile : cannot open '" << machine_code_path
             << "' file\n";
    }
}

LIBFAUST_API wasm_dsp::wasm_dsp(wasm_dsp_factory* factory) : fFactory(factory)
{
    // First instance builds the map
    if (fFactory->fMapUI.getParamsCount() == 0) {
        buildUserInterface(&fFactory->fMapUI);
    }
}

LIBFAUST_API wasm_dsp::~wasm_dsp()
{
    wasm_dsp_factory::gWasmFactoryTable.removeDSP(fFactory, this);
}

LIBFAUST_API int wasm_dsp::getNumInputs()
{
    return -1;
}

LIBFAUST_API int wasm_dsp::getNumOutputs()
{
    return -1;
}

LIBFAUST_API void wasm_dsp::buildUserInterface(UI* ui_interface)
{
    fFactory->getDecoder()->buildUserInterface(ui_interface, reinterpret_cast<char*>(fDSP));
}

LIBFAUST_API int wasm_dsp::getSampleRate()
{
    return -1;
}

LIBFAUST_API void wasm_dsp::init(int sample_rate)
{
}

LIBFAUST_API void wasm_dsp::instanceInit(int sample_rate)
{
}

LIBFAUST_API void wasm_dsp::instanceConstants(int sample_rate)
{
}

LIBFAUST_API void wasm_dsp::instanceResetUserInterface()
{
}

LIBFAUST_API void wasm_dsp::instanceClear()
{
}

LIBFAUST_API wasm_dsp* wasm_dsp::clone()
{
    return fFactory->createDSPInstance();
}

LIBFAUST_API void wasm_dsp::metadata(Meta* m)
{
    fFactory->getDecoder()->metadata(m);
}

LIBFAUST_API void wasm_dsp::computeJS(int count, uintptr_t inputs, uintptr_t outputs)
{
}

LIBFAUST_API void wasm_dsp::compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
{
}

LIBFAUST_API void wasm_dsp::setParamValue(const string& path, FAUSTFLOAT value)
{
    fFactory->fMapUI.setParamValue(path, value);
}

LIBFAUST_API FAUSTFLOAT wasm_dsp::getParamValue(const string& path)
{
    return fFactory->fMapUI.getParamValue(path);
}

EMSCRIPTEN_BINDINGS(CLASS_wasm_dsp_factory)
{
    class_<wasm_dsp_factory>("wasm_dsp_factory")
        .constructor()
        .function("createDSPInstance", &wasm_dsp_factory::createDSPInstance, allow_raw_pointers())
        .function("deleteDSPInstance", &wasm_dsp_factory::deleteDSPInstance, allow_raw_pointers())
        .class_function("readWasmDSPFactoryFromMachineFile2",
                        &wasm_dsp_factory::readWasmDSPFactoryFromMachineFile2, allow_raw_pointers())
        .class_function("readWasmDSPFactoryFromMachine2",
                        &wasm_dsp_factory::readWasmDSPFactoryFromMachine2, allow_raw_pointers())
        .class_function("createWasmDSPFactory", &wasm_dsp_factory::createWasmDSPFactory,
                        allow_raw_pointers())
        .class_function("deleteWasmDSPFactory", &wasm_dsp_factory::deleteWasmDSPFactory2,
                        allow_raw_pointers())
        .class_function("getErrorMessage", &wasm_dsp_factory::getErrorMessage)
        .class_function("extractJSON", &wasm_dsp_factory::extractJSON, allow_raw_pointers());
}

EMSCRIPTEN_BINDINGS(CLASS_wasm_dsp)
{
    class_<wasm_dsp>("wasm_dsp")
        .constructor()
        // DSP API
        .function("getNumInputs", &wasm_dsp::getNumInputs, allow_raw_pointers())
        .function("getNumOutputs", &wasm_dsp::getNumOutputs, allow_raw_pointers())
        .function("getSampleRate", &wasm_dsp::getSampleRate, allow_raw_pointers())
        .function("init", &wasm_dsp::init, allow_raw_pointers())
        .function("instanceInit", &wasm_dsp::instanceInit, allow_raw_pointers())
        .function("instanceConstants", &wasm_dsp::instanceConstants, allow_raw_pointers())
        .function("instanceResetUserInterface", &wasm_dsp::instanceResetUserInterface,
                  allow_raw_pointers())
        .function("instanceClear", &wasm_dsp::instanceClear, allow_raw_pointers())
        .function("clone", &wasm_dsp::clone, allow_raw_pointers())
        .function("compute", &wasm_dsp::computeJS, allow_raw_pointers())
        // Additional JSON based API
        .function("setParamValue", &wasm_dsp::setParamValue, allow_raw_pointers())
        .function("getParamValue", &wasm_dsp::getParamValue, allow_raw_pointers());
}

#else

LIBFAUST_API wasm_dsp_factory::wasm_dsp_factory(int instance, const string& json)
{
    fFactory  = nullptr;
    fInstance = instance;
    fDecoder  = createJSONUIDecoder(json);
}

LIBFAUST_API wasm_dsp_factory::~wasm_dsp_factory()
{
    delete fFactory;
    delete fDecoder;
}

LIBFAUST_API wasm_dsp_factory* wasm_dsp_factory::createWasmDSPFactory(int           instance,
                                                                      const string& json)
{
    return nullptr;
}

LIBFAUST_API string wasm_dsp_factory::extractJSON(const string& code)
{
    return "";
}

LIBFAUST_API wasm_dsp_factory* readWasmDSPFactoryFromMachine(const string& machine_code,
                                                             string&       error_msg)
{
    return nullptr;
}

LIBFAUST_API string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory)
{
    return "";
}

LIBFAUST_API wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(const string& machine_code_path,
                                                                 string&       error_msg)
{
    return nullptr;
}

LIBFAUST_API void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory,
                                                   const string&     machine_code_path)
{
}

LIBFAUST_API wasm_dsp::wasm_dsp(wasm_dsp_factory* factory) : fFactory(factory)
{
}

LIBFAUST_API wasm_dsp::~wasm_dsp()
{
    wasm_dsp_factory::gWasmFactoryTable.removeDSP(fFactory, this);
}

LIBFAUST_API int wasm_dsp::getNumInputs()
{
    return -1;
}

LIBFAUST_API int wasm_dsp::getNumOutputs()
{
    return -1;
}

LIBFAUST_API void wasm_dsp::buildUserInterface(UI* ui_interface)
{
}

LIBFAUST_API int wasm_dsp::getSampleRate()
{
    return -1;
}

LIBFAUST_API void wasm_dsp::init(int sample_rate)
{
}

LIBFAUST_API void wasm_dsp::instanceInit(int sample_rate)
{
}

LIBFAUST_API void wasm_dsp::instanceConstants(int sample_rate)
{
}

LIBFAUST_API void wasm_dsp::instanceResetUserInterface()
{
}

LIBFAUST_API void wasm_dsp::instanceClear()
{
}

LIBFAUST_API wasm_dsp* wasm_dsp::clone()
{
    return nullptr;
}

LIBFAUST_API void wasm_dsp::metadata(Meta* m)
{
}

LIBFAUST_API void wasm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
}

LIBFAUST_API void wasm_dsp::computeJS(int count, uintptr_t input, uintptr_t output)
{
}

LIBFAUST_API void wasm_dsp::setParamValue(const string& path, FAUSTFLOAT value)
{
}

LIBFAUST_API FAUSTFLOAT wasm_dsp::getParamValue(const string& path)
{
    return -1;
}

#endif

LIBFAUST_API wasm_dsp_factory::wasm_dsp_factory(dsp_factory_base* factory)
{
    fFactory = factory;
    fDecoder = nullptr;
}

LIBFAUST_API string wasm_dsp_factory::getName()
{
    return fFactory->getName();
}

LIBFAUST_API string wasm_dsp_factory::getSHAKey()
{
    return fFactory->getSHAKey();
}
LIBFAUST_API void wasm_dsp_factory::setSHAKey(const string& sha_key)
{
    fFactory->setSHAKey(sha_key);
}

LIBFAUST_API string wasm_dsp_factory::getDSPCode()
{
    return fFactory->getDSPCode();
}
LIBFAUST_API void wasm_dsp_factory::setDSPCode(const string& code)
{
    fFactory->setDSPCode(code);
}

LIBFAUST_API string wasm_dsp_factory::getCompileOptions()
{
    return fDecoder->getCompileOptions();
}

LIBFAUST_API vector<string> wasm_dsp_factory::getLibraryList()
{
    return fDecoder->getLibraryList();
}

LIBFAUST_API vector<string> wasm_dsp_factory::getIncludePathnames()
{
    return fDecoder->getIncludePathnames();
}

LIBFAUST_API vector<string> wasm_dsp_factory::getWarningMessages()
{
    return gWarningMessages;
}

LIBFAUST_API void wasm_dsp_factory::setMemoryManager(dsp_memory_manager* manager)
{
}

LIBFAUST_API dsp_memory_manager* wasm_dsp_factory::getMemoryManager()
{
    return nullptr;
}

LIBFAUST_API void wasm_dsp_factory::write(ostream* out, bool binary, bool small)
{
    fFactory->write(out, binary, small);
}

LIBFAUST_API void wasm_dsp_factory::writeHelper(ostream* out, bool binary, bool small)
{
    fFactory->writeHelper(out, binary, small);
}

LIBFAUST_API string wasm_dsp_factory::getBinaryCode()
{
    return fFactory->getBinaryCode();
}

LIBFAUST_API wasm_dsp* wasm_dsp_factory::createDSPInstance()
{
    wasm_dsp* dsp = new wasm_dsp(this);
    wasm_dsp_factory::gWasmFactoryTable.addDSP(this, dsp);
    return dsp;
}

LIBFAUST_API void wasm_dsp_factory::deleteDSPInstance(wasm_dsp* dsp)
{
    delete dsp;
}

// Static constructor

string wasm_dsp_factory::gErrorMessage = "";

LIBFAUST_API const string& wasm_dsp_factory::getErrorMessage()
{
    return wasm_dsp_factory::gErrorMessage;
}

LIBFAUST_API wasm_dsp_factory* wasm_dsp_factory::readWasmDSPFactoryFromMachineFile2(
    const string& machine_code_path)
{
    return readWasmDSPFactoryFromMachineFile(machine_code_path, wasm_dsp_factory::gErrorMessage);
}

LIBFAUST_API wasm_dsp_factory* wasm_dsp_factory::readWasmDSPFactoryFromMachine2(
    const string& machine_code)
{
    return readWasmDSPFactoryFromMachine(machine_code, wasm_dsp_factory::gErrorMessage);
}

LIBFAUST_API bool wasm_dsp_factory::deleteWasmDSPFactory2(wasm_dsp_factory* factory)
{
    return (factory) ? wasm_dsp_factory::gWasmFactoryTable.deleteDSPFactory(factory) : false;
}

// C++ API

LIBFAUST_API bool deleteWasmDSPFactory(wasm_dsp_factory* factory)
{
    return (factory) ? wasm_dsp_factory::gWasmFactoryTable.deleteDSPFactory(factory) : false;
}

LIBFAUST_API void deleteAllWasmDSPFactories()
{
    wasm_dsp_factory::gWasmFactoryTable.deleteAllDSPFactories();
}
