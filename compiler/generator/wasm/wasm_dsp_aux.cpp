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
#include <fstream>
#include <iostream>
#include <sstream>

#include "wasm_dsp_aux.hh"
#include "Text.hh"
#include "compatibility.hh"
#include "dsp_aux.hh"
#include "libfaust.h"
#include "faust/gui/JSONUIDecoder.h"

#include "faust/gui/PrintUI.h"

#ifdef EMCC
#include <emscripten.h>
#include <emscripten/bind.h>
#endif

typedef class faust_smartptr<wasm_dsp_factory> SDsp_factory;

dsp_factory_table<SDsp_factory> gWasmFactoryTable;

#ifdef EMCC

int wasm_dsp_factory::createModuleFromString(const std::string& code)
{
    // 'Binary' string, so directly copy its raw content
    char* code_ptr = (char*)malloc(code.size());
    memcpy(code_ptr, code.c_str(), code.size());
    
    // Synchronously compile wasm module
    int module = EM_ASM_INT({
        FaustModule.faust = FaustModule.faust || {};
        FaustModule.faust.wasm_module = FaustModule.faust.wasm_module || [];
        
        // Copy native 'binary' string in JavaScript Uint8Array
        var factory_code = new Uint8Array($1);
        for (var i = 0; i < $1; i++) {
            // faster than 'getValue' which gets the type of access for each read...
            factory_code[i] = FaustModule.HEAP8[$0 + i];
        }
        
        // Compile wasm module
        FaustModule.faust.wasm_module.push(new WebAssembly.Module(factory_code));
        return FaustModule.faust.wasm_module.length - 1;
        
        // WebAssembly.compile(factory_code)
        // .then(module => { faust.wasm_module = module; console.log(faust.wasm_module); })
        // .catch(function(error) { console.log(error); });
        
    }, code_ptr, code.size());
    
    free(code_ptr);
    return module;
}

wasm_dsp_factory::wasm_dsp_factory(dsp_factory_base* factory) : fFactory(factory)
{
    std::cout << "wasm_dsp_factory::wasm_dsp_factory" << std::endl;
    fModule = createModuleFromString(factory->getBinaryCode());
    std::cout << "fModule " << fModule << std::endl;
    
    wasm_dsp* dsp1 = createDSPInstance();
    std::cout << "getNumInputs " << dsp1->getNumInputs() << std::endl;
    
    wasm_dsp* dsp2 = createDSPInstance();
    std::cout << "getNumOutputs " << dsp2->getNumOutputs() << std::endl;
    
    PrintUI ui;
    dsp1->buildUserInterface(&ui);
}

#else

int wasm_dsp_factory::createModuleFromString(const std::string& code)
{
    return -1;
}

wasm_dsp_factory::wasm_dsp_factory(dsp_factory_base* factory) : fFactory(factory)
{
    fModule = 0;
}

#endif

wasm_dsp_factory::~wasm_dsp_factory()
{
    delete fFactory;
}

std::string wasm_dsp_factory::getName()
{
    return fFactory->getName();
}

std::string wasm_dsp_factory::getSHAKey()
{
    return fFactory->getSHAKey();
}
void wasm_dsp_factory::setSHAKey(std::string sha_key)
{
    fFactory->setSHAKey(sha_key);
}

std::string wasm_dsp_factory::getDSPCode()
{
    return fFactory->getDSPCode();
}
void wasm_dsp_factory::setDSPCode(std::string code)
{
    fFactory->setDSPCode(code);
}

#ifdef EMCC

EM_JS(int, createJSDSPInstance, (int module), {
    
    FaustModule.faust = FaustModule.faust || {};
    FaustModule.faust.wasm_instance = FaustModule.faust.wasm_instance || [];
    
    console.log("createJSDSPInstance " + FaustModule['wasmMemory']);
    
    FaustModule.faust.importObject = FaustModule.faust.importObject ||
    {
        env: {
            memoryBase: 0,
            tableBase: 0,
                
            // Integer version
            _abs: Math.abs,
                
            // Float version
            _acosf: Math.acos,
            _asinf: Math.asin,
            _atanf: Math.atan,
            _atan2f: Math.atan2,
            _ceilf: Math.ceil,
            _cosf: Math.cos,
            _expf: Math.exp,
            _floorf: Math.floor,
            _fmodf: function(x, y) { return x % y; },
            _logf: Math.log,
            _log10f: Math.log10,
            _max_f: Math.max,
            _min_f: Math.min,
            _remainderf: function(x, y) { return x - Math.round(x/y) * y; },
            _powf: Math.pow,
            _roundf: Math.fround,
            _sinf: Math.sin,
            _sqrtf: Math.sqrt,
            _tanf: Math.tan,
                
            // Double version
            _acos: Math.acos,
            _asin: Math.asin,
            _atan: Math.atan,
            _atan2: Math.atan2,
            _ceil: Math.ceil,
            _cos: Math.cos,
            _exp: Math.exp,
            _floor: Math.floor,
            _fmod: function(x, y) { return x % y; },
            _log: Math.log,
            _log10: Math.log10,
            _max_: Math.max,
            _min_: Math.min,
            _remainder:function(x, y) { return x - Math.round(x/y) * y; },
            _pow: Math.pow,
            _round: Math.fround,
            _sin: Math.sin,
            _sqrt: Math.sqrt,
            _tan: Math.tan,
            
            memory: FaustModule['wasmMemory'],
                
            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
        }
    };
    
    console.log(FaustModule.faust.wasm_module);
    var wasm_instance = new WebAssembly.Instance(FaustModule.faust.wasm_module[module], FaustModule.faust.importObject);
    console.log(wasm_instance);
    FaustModule.faust.wasm_instance.push(wasm_instance);
    
    console.log("createJSDSPInstance wasm_instance.exports " + wasm_instance.exports);
    
    //console.log("createJSDSPInstance wasm_instance.exports " + wasm_instance.exports);
    //console.log("createJSDSPInstance wasm_instance.exports.memory " + wasm_instance.exports.memory);
    
    return FaustModule.faust.wasm_instance.length - 1;
});

wasm_dsp* wasm_dsp_factory::createDSPInstance()
{
    return new wasm_dsp(fFactory, createJSDSPInstance(fModule));
}

#else

wasm_dsp* wasm_dsp_factory::createDSPInstance()
{
     return nullptr;
}

#endif

void wasm_dsp_factory::setMemoryManager(dsp_memory_manager* manager)
{
}
dsp_memory_manager* wasm_dsp_factory::getMemoryManager()
{
    return nullptr;
}

void wasm_dsp_factory::write(std::ostream* out, bool binary, bool small)
{
    fFactory->write(out, binary, small);
}
void wasm_dsp_factory::writeAux(std::ostream* out, bool binary, bool small)
{
    fFactory->writeAux(out, binary, small);
}

std::string wasm_dsp_factory::getBinaryCode()
{
    return fFactory->getBinaryCode();
}

// Static constructor

std::string wasm_dsp_factory::gErrorMessage = "";

const std::string&  wasm_dsp_factory::getErrorMessage() { return wasm_dsp_factory::gErrorMessage; }

wasm_dsp_factory* wasm_dsp_factory::createWasmDSPFactoryFromString2(const string& name_app,
                                                                   const string& dsp_content,
                                                                   const vector<string>& argv,
                                                                   bool internal_memory)
{
    int argc1 = 0;
    const char* argv1[64];
    for (int i = 0; i < argv.size(); i++) {
        argv1[argc1++] = argv[i].c_str();
    }
    argv1[argc1] = 0;  // NULL terminated argv
    
    wasm_dsp_factory* factory = createWasmDSPFactoryFromString(name_app, dsp_content, argc1, argv1, wasm_dsp_factory::gErrorMessage, internal_memory);
    return factory;
}

// C++ API

EXPORT wasm_dsp_factory* createWasmDSPFactoryFromFile(const string& filename, int argc, const char* argv[],
                                                      string& error_msg, bool internal_memory)
{
    string base = basename((char*)filename.c_str());
    size_t pos  = filename.find(".dsp");

    if (pos != string::npos) {
        return createWasmDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc, argv, error_msg,
                                              internal_memory);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)\n";
        return nullptr;
    }
}

EXPORT wasm_dsp_factory* createWasmDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc,
                                                        const char* argv[], string& error_msg, bool internal_memory)
{
    
     std::cout << "createWasmDSPFactoryFromString" << std::endl;
    
    /*
    string expanded_dsp_content, sha_key;
    
    if ((expanded_dsp_content = expandDSPFromString(name_app, dsp_content, argc, argv, sha_key, error_msg)) == "") {
        return nullptr;
    } else {
        int         argc1 = 0;
        const char* argv1[32];

        argv1[argc1++] = "faust";
        argv1[argc1++] = "-lang";
        // argv1[argc1++] = (internal_memory) ? "wasm-i" : "wasm-e";
        argv1[argc1++] = (internal_memory) ? "wasm-ib" : "wasm-eb";
        argv1[argc1++] = "-o";
        argv1[argc1++] = "binary";

        for (int i = 0; i < argc; i++) {
            argv1[argc1++] = argv[i];
        }
        argv1[argc1] = 0;  // NULL terminated argv
        
        dsp_factory_table<SDsp_factory>::factory_iterator it;
        
        wasm_dsp_factory* factory = 0;
        
        if (gWasmFactoryTable.getFactory(sha_key, it)) {
            SDsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else {
            dsp_factory_base* dsp_factory_aux =
                compileFaustFactory(argc1, argv1, name_app.c_str(), dsp_content.c_str(), error_msg, true);
            if (dsp_factory_aux) {
                dsp_factory_aux->setName(name_app);
                wasm_dsp_factory* factory = new wasm_dsp_factory(dsp_factory_aux);
                gWasmFactoryTable.setFactory(factory);
                factory->setSHAKey(sha_key);
                factory->setDSPCode(expanded_dsp_content);
                return factory;
            } else {
                return nullptr;
            }
        }
    }
    */
    
    string expanded_dsp_content = "";
    string sha_key              = "";
    
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
    argv1[argc1] = 0;  // NULL terminated argv
 
    dsp_factory_base* dsp_factory_aux =
        compileFaustFactory(argc1, argv1, name_app.c_str(), dsp_content.c_str(), error_msg, true);
    
    if (dsp_factory_aux) {
        dsp_factory_aux->setName(name_app);
        wasm_dsp_factory* factory = new wasm_dsp_factory(dsp_factory_aux);
        gWasmFactoryTable.setFactory(factory);
        factory->setSHAKey(sha_key);
        factory->setDSPCode(expanded_dsp_content);
        return factory;
    } else {
        return nullptr;
    }
}

EXPORT bool deleteWasmDSPFactory(wasm_dsp_factory* factory)
{
    return (factory) ? gWasmFactoryTable.deleteDSPFactory(factory) : false;
}

#ifdef EMCC

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachine(const std::string& machine_code)
{
    vector<string> dummy;
    wasm_dsp_factory* factory = new wasm_dsp_factory(new text_dsp_factory_aux("MachineDSP", "", "", dummy, dummy, machine_code, ""));
    gWasmFactoryTable.setFactory(factory);
    factory->setSHAKey("");
    factory->setDSPCode("");
    return factory;
}

EXPORT std::string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory)
{
    return factory->getBinaryCode();
}

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(const std::string& machine_code_path)
{
    // TODO
    return nullptr;
}

EXPORT void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory, const std::string& machine_code_path)
{
    // TODO
}

#else

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachine(const std::string& machine_code)
{
    return nullptr;
}

EXPORT std::string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory)
{
    return "";
}

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(const std::string& machine_code_path)
{
    return nullptr;
}

EXPORT void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory, const std::string& machine_code_path)
{}

#endif

// Instance API

#ifdef EMCC

wasm_dsp::wasm_dsp(dsp_factory_base* factory, int dsp):fFactory(factory), fDSP(dsp)
{
    // Get JSON in the wasm module
    char* json = (char*)EM_ASM_INT({
        FaustModule.faust = FaustModule.faust || {};
        var jsString = "";
        var i = 0;
        var HEAP8 = new Uint8Array(FaustModule.faust.wasm_instance[$0].exports.memory.buffer);
        while (HEAP8[i] !== 0) { jsString += String.fromCharCode(HEAP8[i++]); }
        var lengthBytes = lengthBytesUTF8(jsString)+1;
        var stringOnWasmHeap = FaustModule._malloc(lengthBytes);
        stringToUTF8(jsString, stringOnWasmHeap, lengthBytes+1);
        return stringOnWasmHeap;
    }, fDSP);
    
    fDecoder = new JSONUIDecoder(json);
    
    // String allocated on JS side must be deallocated
    free(json);
}

wasm_dsp::~wasm_dsp()
{
    // Empty the JS structures so that the instance can be GCed
    EM_ASM({
        FaustModule.faust = FaustModule.faust || {};
        FaustModule.faust.wasm_instance[$0] = null;
    }, fDSP);
    
    delete fDecoder;
}

int wasm_dsp::getNumInputs()
{
    return EM_ASM_INT({
        FaustModule.faust = FaustModule.faust || {};
        var dsp = FaustModule.faust.wasm_instance[$0].exports.memory.buffer;
        return FaustModule.faust.wasm_instance[$0].exports.getNumInputs(dsp);
    }, fDSP);
}

int wasm_dsp::getNumOutputs()
{
    return EM_ASM_INT({
        FaustModule.faust = FaustModule.faust || {};
        var dsp = FaustModule.faust.wasm_instance[$0].exports.memory.buffer;
        return FaustModule.faust.wasm_instance[$0].exports.getNumOutputs(dsp);
    }, fDSP);
}

void wasm_dsp::buildUserInterface(UI* ui_interface)
{
    fDecoder->buildUserInterface(ui_interface);
}

int wasm_dsp::getSampleRate()
{
    return EM_ASM_INT({
        FaustModule.faust = FaustModule.faust || {};
        var dsp = FaustModule.faust.wasm_instance[$0].exports.memory.buffer;
        return FaustModule.faust.wasm_instance[$0].exports.getSampleRate(dsp);
    }, fDSP);
}

void wasm_dsp::init(int samplingRate)
{
    EM_ASM({
        FaustModule.faust = FaustModule.faust || {};
        var dsp = FaustModule.faust.wasm_instance[$0].exports.memory.buffer;
        FaustModule.faust.wasm_instance[$0].exports.init(dsp);
    }, fDSP, samplingRate);
}

void wasm_dsp::instanceInit(int samplingRate)
{
    EM_ASM({
        FaustModule.faust = FaustModule.faust || {};
        var dsp = FaustModule.faust.wasm_instance[$0].exports.memory.buffer;
        FaustModule.faust.wasm_instance[$0].exports.instanceInit(dsp, $1);
    }, fDSP, samplingRate);
}

void wasm_dsp::instanceConstants(int samplingRate)
{
    EM_ASM({
        FaustModule.faust = FaustModule.faust || {};
        var dsp = FaustModule.faust.wasm_instance[$0].exports.memory.buffer;
        FaustModule.faust.wasm_instance[$0].exports.instanceConstants(dsp, $1);
    }, fDSP);
}

void wasm_dsp::instanceResetUserInterface()
{
    EM_ASM({
        FaustModule.faust = FaustModule.faust || {};
        var dsp = FaustModule.faust.wasm_instance[$0].exports.memory.buffer;
        FaustModule.faust.wasm_instance[$0].exports.instanceResetUserInterface(dsp);
    }, fDSP);
}

void wasm_dsp::instanceClear()
{
    EM_ASM({
        FaustModule.faust = FaustModule.faust || {};
        var dsp = FaustModule.faust.wasm_instance[$0].exports.memory.buffer;
        FaustModule.faust.wasm_instance[$0].exports.instanceClear(dsp);
    }, fDSP);
}

wasm_dsp* wasm_dsp::clone()
{
    return nullptr;
}

void wasm_dsp::metadata(Meta* m)
{
     fDecoder->metadata(m);
}

//void wasm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
void wasm_dsp::computeJS(int count, uintptr_t input, uintptr_t output)
{
    std::cout << "computeJS " << input << " " << output << std::endl;
    EM_ASM({
        FaustModule.faust = FaustModule.faust || {};
        console.log("count " + $1);
        console.log("input " + $2);
        console.log("output " + $3);
        var dsp = FaustModule.faust.wasm_instance[$0].exports.memory.buffer;
        console.log("dsp " + dsp);
        console.log("FaustModule.faust.wasm_instance[$0].exports.compute " + FaustModule.faust.wasm_instance[$0].exports.compute);
        FaustModule.faust.wasm_instance[$0].exports.compute(dsp, $1, $2, $3);
    }, fDSP, count, input, output);
}

void wasm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    std::cout << "compute " << count << " " << input << " " << output << std::endl;
    computeJS(count, reinterpret_cast<uintptr_t>(input), reinterpret_cast<uintptr_t>(output));
}

void wasm_dsp::computeJSTest(int count)
{
    FAUSTFLOAT** inputs = new FAUSTFLOAT*[getNumInputs()];
    FAUSTFLOAT** outputs = new FAUSTFLOAT*[getNumOutputs()];
    
    std::cout << "computeJSTest " << count << " " << getNumInputs() << " " << getNumOutputs() << std::endl;
    
    for (int i = 0; i < getNumInputs(); i++) {
        inputs[i] = new FAUSTFLOAT[count];
    }
    for (int i = 0; i < getNumOutputs(); i++) {
        outputs[i] = new FAUSTFLOAT[count];
    }
    
    std::cout << "computeJSTest inputs " << inputs << " outputs " << outputs << std::endl;
    
    compute(count, inputs, outputs);
}

#else

wasm_dsp::~wasm_dsp()
{}

int wasm_dsp::getNumInputs()
{
    return -1;
}

int wasm_dsp::getNumOutputs()
{
    return -1;
}

void wasm_dsp::buildUserInterface(UI* ui_interface)
{
    // TODO : use JSONUIDecoder
}

int wasm_dsp::getSampleRate()
{
    return -1;
}

void wasm_dsp::init(int samplingRate)
{}

void wasm_dsp::instanceInit(int samplingRate)
{}

void wasm_dsp::instanceConstants(int samplingRate)
{}

void wasm_dsp::instanceResetUserInterface()
{}

void wasm_dsp::instanceClear()
{}

wasm_dsp* wasm_dsp::clone()
{
    return nullptr;
}

void wasm_dsp::metadata(Meta* m)
{
    // TODO : JSONUIDecoder
}

void wasm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{}

#endif

// C API

#ifdef EMCC
    
using namespace emscripten;

vector<string> makeStringVector()
{
    vector<string> v;
    return v;
}
    
EMSCRIPTEN_BINDINGS(CLASS_wasm_dsp_factory) {
    emscripten::function("makeStringVector", &makeStringVector);
    register_vector<string>("vector<string>");
    class_<wasm_dsp_factory>("wasm_dsp_factory")
    .constructor()
    .function("createDSPInstance",
              &wasm_dsp_factory::createDSPInstance,
              allow_raw_pointers())
    .class_function("createWasmDSPFactoryFromString2",
                    &wasm_dsp_factory::createWasmDSPFactoryFromString2,
                    allow_raw_pointers())
    .class_function("getErrorMessage",
                    &wasm_dsp_factory::getErrorMessage);
}
    
EMSCRIPTEN_BINDINGS(CLASS_wasm_dsp) {
    class_<wasm_dsp>("wasm_dsp")
    .constructor()
    .function("getNumInputs",
              &wasm_dsp::getNumInputs,
              allow_raw_pointers())
    .function("getNumOutputs",
              &wasm_dsp::getNumOutputs,
              allow_raw_pointers())
    .function("getSampleRate",
              &wasm_dsp::getSampleRate,
              allow_raw_pointers())
    .function("init",
              &wasm_dsp::init,
              allow_raw_pointers())
    .function("instanceInit",
              &wasm_dsp::instanceInit,
              allow_raw_pointers())
    .function("instanceConstants",
              &wasm_dsp::instanceConstants,
              allow_raw_pointers())
    .function("instanceResetUserInterface",
              &wasm_dsp::instanceResetUserInterface,
              allow_raw_pointers())
    .function("instanceClear",
             &wasm_dsp::instanceClear,
             allow_raw_pointers())
    .function("clone",
             &wasm_dsp::clone,
             allow_raw_pointers())
    .function("computeJS",
             &wasm_dsp::computeJS,
             allow_raw_pointers())
    .function("computeJSTest",
              &wasm_dsp::computeJSTest,
              allow_raw_pointers());
}

#endif

#ifdef __cplusplus
extern "C" {
#endif
    
EXPORT wasm_dsp_factory* createWasmCDSPFactoryFromFile2(const char* filename, int argc, const char* argv[],
                                                        char* error_msg, bool internal_memory)
{
    string error_msg_aux;
    wasm_dsp_factory* factory = createWasmDSPFactoryFromFile(filename, argc, argv, error_msg_aux, internal_memory);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

EXPORT wasm_dsp_factory* createWasmCDSPFactoryFromString2(const char* name_app, const char* dsp_content, int argc,
                                                          const char* argv[], char* error_msg, bool internal_memory)
{
    string error_msg_aux;
    wasm_dsp_factory* factory = createWasmDSPFactoryFromString(name_app, dsp_content, argc, argv, error_msg_aux, internal_memory);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

EXPORT bool deleteWasmCDSPFactory(wasm_dsp_factory* factory)
{}

EXPORT wasm_dsp_factory* readWasmCDSPFactoryFromMachine(const char* machine_code)
{}

EXPORT char* writeWasmCDSPFactoryToMachine(wasm_dsp_factory* factory)
{}

EXPORT wasm_dsp_factory* readWasmCDSPFactoryFromMachineFile(const char* machine_code_path)
{}

EXPORT void writeWasmCDSPFactoryToMachineFile(wasm_dsp_factory* factory, const char* machine_code_path)
{}

static WasmModule* createWasmCDSPFactoryAux(wasm_dsp_factory* factory, const string& error_msg_aux, char* error_msg)
{
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    if (factory) {
        WasmModule* res = static_cast<WasmModule*>(calloc(1, sizeof(WasmModule)));

        // 'Binary' string, so directly copy its raw content
        string code    = factory->getBinaryCode();
        res->fCodeSize = code.size();
        res->fCode     = (char*)malloc(res->fCodeSize);
        memcpy(res->fCode, code.c_str(), res->fCodeSize);

        stringstream dst2;
        factory->writeAux(&dst2, false, false);
        res->fHelpers = strdup(flatten(dst2.str()).c_str());

        return res;
        // And keep factory...
    } else {
        return nullptr;
    }
}

EXPORT WasmModule* createWasmCDSPFactoryFromFile(const char* filename, int argc, const char* argv[], char* error_msg,
                                                 bool internal_memory)
{
    string            error_msg_aux;
    wasm_dsp_factory* factory = createWasmDSPFactoryFromFile(filename, argc, argv, error_msg_aux, internal_memory);
    return createWasmCDSPFactoryAux(factory, error_msg_aux, error_msg);
}

EXPORT WasmModule* createWasmCDSPFactoryFromString(const char* name_app, const char* dsp_content, int argc,
                                                   const char* argv[], char* error_msg, bool internal_memory)
{
    string            error_msg_aux;
    wasm_dsp_factory* factory =
        createWasmDSPFactoryFromString(name_app, dsp_content, argc, argv, error_msg_aux, internal_memory);
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

#ifdef __cplusplus
}
#endif
