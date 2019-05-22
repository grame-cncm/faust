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

#ifdef WIN32
#pragma warning(disable : 4251 4275 4800)
#endif

#include "compatibility.hh"
#include "faust/gui/JSONUIDecoder.h"
#include "libfaust.h"
#include "wasm_dsp_aux.hh"

// For tests
#include "faust/dsp/dsp-combiner.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/PrintUI.h"

#ifdef EMCC
#include <emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;
#endif

dsp_factory_table<SDsp_factory> wasm_dsp_factory::gWasmFactoryTable;

#ifdef EMCC

using namespace std;

EM_JS(int, createJSModuleFromString, (uint8_t* code_ptr, size_t code_size),
{
    // Done once when creating the first factory
    faust_module.faust               = faust_module.faust || {};
    faust_module.faust.wasm_module   = faust_module.faust.wasm_module || [];
    faust_module.faust.wasm_instance = faust_module.faust.wasm_instance || [];
    faust_module.faust.importObject  = faust_module.faust.importObject ||
    { env :
        {
            memoryBase : 0,
            tableBase : 0,

            // Integer version
            _abs : Math.abs,

            // Float version
            _acosf : Math.acos,
            _asinf : Math.asin,
            _atanf : Math.atan,
            _atan2f : Math.atan2,
            _ceilf : Math.ceil,
            _cosf : Math.cos,
            _expf : Math.exp,
            _floorf : Math.floor,
            _fmodf : function(x, y)
            { return x % y; },
            _logf: Math.log,
            _log10f: Math.log10,
            _max_f: Math.max,
            _min_f: Math.min,
            _powf: Math.pow,
            _remainderf: function(x, y)
            { return x - Math.round(x / y) * y; },
            _roundf: Math.fround,
            _sinf: Math.sin,
            _sqrtf: Math.sqrt,
            _tanf: Math.tan,
            _acoshf: Math.acosh,
            _asinhf: Math.asinh,
            _atanhf: Math.atanh,
            _coshf: Math.cosh,
            _sinhf: Math.sinh,
            _tanhf: Math.tanh,
        
            // Double version
            _acos: Math.acos,
            _asin: Math.asin,
            _atan: Math.atan,
            _atan2: Math.atan2,
            _ceil: Math.ceil,
            _cos: Math.cos,
            _exp: Math.exp,
            _floor: Math.floor,
            _fmod: function(x, y)
            { return x % y; },
            _log: Math.log,
            _log10: Math.log10,
            _max_: Math.max,
            _min_: Math.min,
            _pow: Math.pow,
            _remainder:function(x, y)
            { return x - Math.round(x / y) * y; },
            _round: Math.fround,
            _sin: Math.sin,
            _sqrt: Math.sqrt,
            _tan: Math.tan,
            _acosh: Math.acosh,
            _asinh: Math.asinh,
            _atanh: Math.atanh,
            _cosh: Math.cosh,
            _sinh: Math.sinh,
            _tanh: Math.tanh,
        
            // Emscripten generated global memory segment is used
            //memory: FaustModule['wasmMemory'],
            memory: wasmMemory,
            
            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
        }
    };

    // Copy native 'binary' string in JavaScript Uint8Array
    var factory_code = new Uint8Array(code_size);
    for (var i = 0; i < code_size; i++) {
        // faster than 'getValue' which gets the type of access for each read...
        factory_code[i] = faust_module.HEAP8[code_ptr + i];
    }

    // Compile wasm module
    faust_module.faust.wasm_module.push(new WebAssembly.Module(factory_code));
    
    /*
    var finished = false;
    WebAssembly.compile(factory_code)
    .then(module => { console.log("COMPILED"); console.log(module); finished = true; faust_module.faust.wasm_module.push(module); })
    .catch(function(error) { console.log(error); });
    */
 
    return faust_module.faust.wasm_module.length - 1;
});

void wasm_dsp_factory::createModuleFromString()
{
    WasmBinaryReader reader(fFactory->getBinaryCode());

    // Extract JSON
    reader.read();
    fJSON = reader.json;

    // 'reader.data_segment_pos' is the new end of the module
    fModule = createJSModuleFromString(reader.input, reader.data_segment_pos);
}

wasm_dsp_factory::wasm_dsp_factory(dsp_factory_base* factory) : fFactory(factory)
{
    createModuleFromString();
    fDecoder = createJSONUIDecoder(fJSON);
}

#else

void wasm_dsp_factory::createModuleFromString()
{
}

wasm_dsp_factory::wasm_dsp_factory(dsp_factory_base* factory)
{
    fFactory = factory;
    fModule = 0;
    fDecoder = nullptr;
}

#endif

wasm_dsp_factory::wasm_dsp_factory(int module, const std::string& json)
{
    fFactory = nullptr;
    fModule = module;
    fJSON = json;
    fDecoder = createJSONUIDecoder(fJSON);
}

wasm_dsp_factory::~wasm_dsp_factory()
{
    delete fFactory;
    delete fDecoder;
}

string wasm_dsp_factory::extractJSON(const string& code)
{
    WasmBinaryReader reader(code);
    reader.read();
    return reader.json;
}

string wasm_dsp_factory::getName()
{
    return fFactory->getName();
}

string wasm_dsp_factory::getSHAKey()
{
    return fFactory->getSHAKey();
}
void wasm_dsp_factory::setSHAKey(string sha_key)
{
    fFactory->setSHAKey(sha_key);
}

string wasm_dsp_factory::getDSPCode()
{
    return fFactory->getDSPCode();
}
void wasm_dsp_factory::setDSPCode(string code)
{
    fFactory->setDSPCode(code);
}

string wasm_dsp_factory::getCompileOptions()
{
    return fDecoder->getCompileOptions();
}
vector<string> wasm_dsp_factory::getLibraryList()
{
    return fDecoder->getLibraryList();
}
vector<string> wasm_dsp_factory::getIncludePathnames()
{
    return fDecoder->getIncludePathnames();
}

#ifdef EMCC

EM_JS(int, createJSDSPInstance, (int module), {
    
    faust_module.faust.importObject  = faust_module.faust.importObject ||
    { env :
        {
            memoryBase : 0,
            tableBase : 0,
            
            // Integer version
            _abs : Math.abs,
            
            // Float version
            _acosf : Math.acos,
            _asinf : Math.asin,
            _atanf : Math.atan,
            _atan2f : Math.atan2,
            _ceilf : Math.ceil,
            _cosf : Math.cos,
            _expf : Math.exp,
            _floorf : Math.floor,
            _fmodf : function(x, y)
            { return x % y; },
            _logf: Math.log,
            _log10f: Math.log10,
            _max_f: Math.max,
            _min_f: Math.min,
            _powf: Math.pow,
            _remainderf: function(x, y)
            { return x - Math.round(x / y) * y; },
            _roundf: Math.fround,
            _sinf: Math.sin,
            _sqrtf: Math.sqrt,
            _tanf: Math.tan,
            _acoshf: Math.acosh,
            _asinhf: Math.asinh,
            _atanhf: Math.atanh,
            _coshf: Math.cosh,
            _sinhf: Math.sinh,
            _tanhf: Math.tanh,
                
            // Double version
            _acos: Math.acos,
            _asin: Math.asin,
            _atan: Math.atan,
            _atan2: Math.atan2,
            _ceil: Math.ceil,
            _cos: Math.cos,
            _exp: Math.exp,
            _floor: Math.floor,
            _fmod: function(x, y)
            { return x % y; },
            _log: Math.log,
            _log10: Math.log10,
            _max_: Math.max,
            _min_: Math.min,
            _pow: Math.pow,
            _remainder:function(x, y)
            { return x - Math.round(x / y) * y; },
            _round: Math.fround,
            _sin: Math.sin,
            _sqrt: Math.sqrt,
            _tan: Math.tan,
            _acosh: Math.acosh,
            _asinh: Math.asinh,
            _atanh: Math.atanh,
            _cosh: Math.cosh,
            _sinh: Math.sinh,
            _tanh: Math.tanh,
                
            // Emscripten generated global memory segment is used
            //memory: FaustModule['wasmMemory'],
            memory: wasmMemory,
                
            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
        }
    };

    var wasm_instance = new WebAssembly.Instance(faust_module.faust.wasm_module[module], faust_module.faust.importObject);
    faust_module.faust.wasm_instance.push(wasm_instance);
    return faust_module.faust.wasm_instance.length - 1;
});

wasm_dsp* wasm_dsp_factory::createDSPInstance()
{
    wasm_dsp* dsp = new wasm_dsp(this, createJSDSPInstance(fModule));
    wasm_dsp_factory::gWasmFactoryTable.addDSP(this, dsp);
    return dsp;
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

void wasm_dsp_factory::write(ostream* out, bool binary, bool small)
{
    fFactory->write(out, binary, small);
}
void wasm_dsp_factory::writeAux(ostream* out, bool binary, bool small)
{
    fFactory->writeAux(out, binary, small);
}

string wasm_dsp_factory::getBinaryCode()
{
    return fFactory->getBinaryCode();
}

FAUSTFLOAT** wasm_dsp_factory::createAudioBuffers(int chan, int frames)
{
    FAUSTFLOAT** buffers = new FAUSTFLOAT*[chan];
    for (int i = 0; i < chan; i++) {
        buffers[i] = new FAUSTFLOAT[frames];
        memset(buffers[i], 0, frames * sizeof(FAUSTFLOAT));
    }
    return buffers;
}

void wasm_dsp_factory::copyFromAudioBuffer(FAUSTFLOAT** out, FAUSTFLOAT* in, int chan, int frames)
{
    memcpy(out[chan], in, frames * sizeof(FAUSTFLOAT));
}

void wasm_dsp_factory::copyToAudioBuffer(FAUSTFLOAT** in, FAUSTFLOAT* out, int chan, int frames)
{
    memcpy(out, in[chan], frames * sizeof(FAUSTFLOAT));
}

void wasm_dsp_factory::deleteAudioBuffers(FAUSTFLOAT** buffers, int chan)
{
    for (int i = 0; i < chan; i++) {
        delete[] buffers[i];
    }
    delete[] buffers;
}

void wasm_dsp_factory::printAudioBuffers(FAUSTFLOAT** buffers, int chan_aux, int count)
{
    for (int chan = 0; chan < chan_aux; chan++) {
        for (int frame = 0; frame < count; frame++) {
            std::cout << "frame input = " << frame << " : " << (buffers[chan][frame]) << std::endl;
        }
    }
}

uintptr_t wasm_dsp_factory::createJSAudioBuffers(int chan, int frames)
{
    return reinterpret_cast<uintptr_t>(createAudioBuffers(chan, frames));
}

void wasm_dsp_factory::copyJSFromAudioBuffer(uintptr_t out, uintptr_t in, int chan, int frames)
{
    copyFromAudioBuffer(reinterpret_cast<FAUSTFLOAT**>(out), reinterpret_cast<FAUSTFLOAT*>(in), chan, frames);
}

void wasm_dsp_factory::copyJSToAudioBuffer(uintptr_t in, uintptr_t out, int chan, int frames)
{
    copyToAudioBuffer(reinterpret_cast<FAUSTFLOAT**>(in), reinterpret_cast<FAUSTFLOAT*>(out), chan, frames);
}

void wasm_dsp_factory::deleteJSAudioBuffers(uintptr_t js_buffers, int chan)
{
    deleteAudioBuffers(reinterpret_cast<FAUSTFLOAT**>(js_buffers), chan);
}

void wasm_dsp_factory::printJSAudioBuffers(uintptr_t js_buffers, int chan, int frames)
{
    printAudioBuffers(reinterpret_cast<FAUSTFLOAT**>(js_buffers), chan, frames);
}

// Static constructor

string wasm_dsp_factory::gErrorMessage = "";

const string& wasm_dsp_factory::getErrorMessage()
{
    return wasm_dsp_factory::gErrorMessage;
}

wasm_dsp_factory* wasm_dsp_factory::readWasmDSPFactoryFromMachineFile2(const string& machine_code_path)
{
    return readWasmDSPFactoryFromMachineFile(machine_code_path, wasm_dsp_factory::gErrorMessage);
}

wasm_dsp_factory* wasm_dsp_factory::readWasmDSPFactoryFromMachine2(const string& machine_code)
{
    return readWasmDSPFactoryFromMachine(machine_code, wasm_dsp_factory::gErrorMessage);
}

wasm_dsp_factory* wasm_dsp_factory::connectWasmDSPFactory(int module, const std::string& json)
{
    wasm_dsp_factory* factory = new wasm_dsp_factory(module, json);
    wasm_dsp_factory::gWasmFactoryTable.setFactory(factory);
    return factory;
}

// C++ API

EXPORT bool deleteWasmDSPFactory(wasm_dsp_factory* factory)
{
    return (factory) ? wasm_dsp_factory::gWasmFactoryTable.deleteDSPFactory(factory) : false;
}

EXPORT void deleteAllWasmDSPFactories()
{
    wasm_dsp_factory::gWasmFactoryTable.deleteAllDSPFactories();
}

#ifdef EMCC

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachine(const string& machine_code, string& error_msg)
{
    wasm_dsp_factory* factory = new wasm_dsp_factory(new text_dsp_factory_aux("MachineDSP", "", "", machine_code, ""));
    wasm_dsp_factory::gWasmFactoryTable.setFactory(factory);
    return factory;
}

EXPORT string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory)
{
    return factory->getBinaryCode();
}

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(const string& machine_code_path, string& error_msg)
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
        wasm_dsp_factory* factory =
            readWasmDSPFactoryFromMachine(string(machine_code, length), error_msg);  // Keep the binary string

        infile.close();
        delete[] machine_code;

        return factory;
    } else {
        error_msg = "ERROR : cannot open '" + machine_code_path + "' file\n";
        return nullptr;
    }
}

EXPORT void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory, const string& machine_code_path)
{
    ofstream outfile;
    outfile.open(machine_code_path, ofstream::out | ofstream::binary);
    if (outfile.is_open()) {
        outfile << factory->getBinaryCode();
        outfile.close();
    } else {
        cerr << "writeWasmDSPFactoryToMachineFile : cannot open '" << machine_code_path << "' file\n";
    }
}

#else

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachine(const string& machine_code, string& error_msg)
{
    return nullptr;
}

EXPORT string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory)
{
    return "";
}

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(const string& machine_code_path, string& error_msg)
{
    return nullptr;
}

EXPORT void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory, const string& machine_code_path)
{
}

#endif

// Instance API

#ifdef EMCC

wasm_dsp::wasm_dsp(wasm_dsp_factory* factory, int index) : fFactory(factory), fIndex(index)
{
    fDSP = EM_ASM_INT({ return faust_module._malloc($0); }, fFactory->getDecoder()->getDSPSize());
    buildUserInterface(&fMapUI);
}

wasm_dsp::~wasm_dsp()
{
    EM_ASM(
        {
            // Empty the JS structures so that the instance can be GCed
            faust_module.faust.wasm_instance[$0] = null;
            // Free the DSP memory
            faust_module._free($1);
        },
        fIndex, fDSP);
}

int wasm_dsp::getNumInputs()
{
    return EM_ASM_INT({ return faust_module.faust.wasm_instance[$0].exports.getNumInputs($1); }, fIndex, fDSP);
}

int wasm_dsp::getNumOutputs()
{
    return EM_ASM_INT({ return faust_module.faust.wasm_instance[$0].exports.getNumOutputs($1); }, fIndex, fDSP);
}

void wasm_dsp::buildUserInterface(UI* ui_interface)
{
    fFactory->getDecoder()->buildUserInterface(ui_interface, reinterpret_cast<char*>(fDSP));
}

int wasm_dsp::getSampleRate()
{
    return EM_ASM_INT({ return faust_module.faust.wasm_instance[$0].exports.getSampleRate($1); }, fIndex, fDSP);
}

void wasm_dsp::init(int sample_rate)
{
    EM_ASM({ faust_module.faust.wasm_instance[$0].exports.init($1, $2); }, fIndex, fDSP, sample_rate);
}

void wasm_dsp::instanceInit(int sample_rate)
{
    EM_ASM({ faust_module.faust.wasm_instance[$0].exports.instanceInit($1, $2); }, fIndex, fDSP, sample_rate);
}

void wasm_dsp::instanceConstants(int sample_rate)
{
    EM_ASM({ faust_module.faust.wasm_instance[$0].exports.instanceConstants($1, $2); }, fIndex, fDSP, sample_rate);
}

void wasm_dsp::instanceResetUserInterface()
{
    EM_ASM({ faust_module.faust.wasm_instance[$0].exports.instanceResetUserInterface($1); }, fIndex, fDSP);
}

void wasm_dsp::instanceClear()
{
    EM_ASM({ faust_module.faust.wasm_instance[$0].exports.instanceClear($1); }, fIndex, fDSP);
}

wasm_dsp* wasm_dsp::clone()
{
    return fFactory->createDSPInstance();
}

void wasm_dsp::metadata(Meta* m)
{
    fFactory->getDecoder()->metadata(m);
}

void wasm_dsp::computeJS(int count, uintptr_t inputs, uintptr_t outputs)
{
    std::cout << "computeJS " << count << " " << inputs << " " << outputs << std::endl;
    
    /*
    EM_ASM({ faust_module.faust.wasm_instance[$0].exports.compute($1, $2, $3, $4); }, fIndex, fDSP, count, inputs,
           outputs);
    */
}

void wasm_dsp::compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
{
    EM_ASM({ faust_module.faust.wasm_instance[$0].exports.compute($1, $2, $3, $4); }, fIndex, fDSP, count,
           reinterpret_cast<uintptr_t>(inputs), reinterpret_cast<uintptr_t>(outputs));
}

void wasm_dsp::computeJSTest(int count)
{
    FAUSTFLOAT** inputs  = wasm_dsp_factory::createAudioBuffers(getNumInputs(), count);
    FAUSTFLOAT** outputs = wasm_dsp_factory::createAudioBuffers(getNumOutputs(), count);

    std::cout << "computeJSTest " << count << " " << getNumInputs() << " " << getNumOutputs() << std::endl;
    std::cout << "computeJSTest inputs " << inputs << " outputs " << outputs << std::endl;
    std::cout << "computeJSTest getNumInputs() " << getNumInputs() << " getNumOutputs() " << getNumOutputs() << std::endl;

    for (int chan = 0; chan < getNumInputs(); chan++) {
        for (int frame = 0; frame < count; frame++) {
            std::cout << "frame input = " << frame << " : " << (inputs[chan][frame]) << std::endl;
        }
    }

    compute(count, inputs, outputs);

    /*
    wasm_dsp* dsp1 = clone();
    wasm_dsp* dsp2 = clone();
    wasm_dsp* dsp3 = clone();

    dsp* seq = new dsp_sequencer(dsp1, new dsp_sequencer(dsp2, dsp3, 4096), 4096);
    seq->init(44100);

    PrintUI ui;
    seq->buildUserInterface(&ui);

    JSONUI jsonui;
    seq->buildUserInterface(&jsonui);
    std::cout << "JSON " << jsonui.JSON(true);

    seq->compute(count, inputs, outputs);
    */

    for (int chan = 0; chan < getNumOutputs(); chan++) {
        for (int frame = 0; frame < count; frame++) {
            std::cout << "frame output = " << frame << " : " << (outputs[chan][frame]) << std::endl;
        }
    }

    wasm_dsp_factory::deleteAudioBuffers(inputs, getNumInputs());
    wasm_dsp_factory::deleteAudioBuffers(outputs, getNumOutputs());
}

void wasm_dsp::setParamValue(const std::string& path, FAUSTFLOAT value)
{
    fMapUI.setParamValue(path, value);
}

FAUSTFLOAT wasm_dsp::getParamValue(const std::string& path)
{
    return fMapUI.getParamValue(path);
}

EMSCRIPTEN_BINDINGS(CLASS_wasm_dsp_factory)
{
    class_<wasm_dsp_factory>("wasm_dsp_factory")
        .constructor()
        .function("createDSPInstance", &wasm_dsp_factory::createDSPInstance, allow_raw_pointers())
        .class_function("readWasmDSPFactoryFromMachineFile2", &wasm_dsp_factory::readWasmDSPFactoryFromMachineFile2,
                        allow_raw_pointers())
        .class_function("readWasmDSPFactoryFromMachine2", &wasm_dsp_factory::readWasmDSPFactoryFromMachine2,
                        allow_raw_pointers())
        .class_function("connectWasmDSPFactory", &wasm_dsp_factory::connectWasmDSPFactory, allow_raw_pointers())
        .class_function("createAudioBuffers", &wasm_dsp_factory::createJSAudioBuffers, allow_raw_pointers())
        .class_function("deleteAudioBuffers", &wasm_dsp_factory::deleteJSAudioBuffers, allow_raw_pointers())
        .class_function("copyFromAudioBuffer", &wasm_dsp_factory::copyJSFromAudioBuffer, allow_raw_pointers())
        .class_function("copyToAudioBuffer", &wasm_dsp_factory::copyJSToAudioBuffer, allow_raw_pointers())
        .class_function("printAudioBuffers", &wasm_dsp_factory::printJSAudioBuffers, allow_raw_pointers())
        .class_function("getErrorMessage", &wasm_dsp_factory::getErrorMessage)
        .class_function("extractJSON", &wasm_dsp_factory::extractJSON, allow_raw_pointers());
}

EMSCRIPTEN_BINDINGS(CLASS_wasm_dsp)
{
    class_<wasm_dsp>("wasm_dsp")
        .constructor()
        .function("getNumInputs", &wasm_dsp::getNumInputs, allow_raw_pointers())
        .function("getNumOutputs", &wasm_dsp::getNumOutputs, allow_raw_pointers())
        .function("getSampleRate", &wasm_dsp::getSampleRate, allow_raw_pointers())
        .function("init", &wasm_dsp::init, allow_raw_pointers())
        .function("instanceInit", &wasm_dsp::instanceInit, allow_raw_pointers())
        .function("instanceConstants", &wasm_dsp::instanceConstants, allow_raw_pointers())
        .function("instanceResetUserInterface", &wasm_dsp::instanceResetUserInterface, allow_raw_pointers())
        .function("instanceClear", &wasm_dsp::instanceClear, allow_raw_pointers())
        .function("clone", &wasm_dsp::clone, allow_raw_pointers())
        .function("compute", &wasm_dsp::computeJS, allow_raw_pointers())
        .function("computeJSTest", &wasm_dsp::computeJSTest, allow_raw_pointers())
        .function("setParamValue", &wasm_dsp::setParamValue, allow_raw_pointers())
        .function("getParamValue", &wasm_dsp::getParamValue, allow_raw_pointers());
}

#else

wasm_dsp::~wasm_dsp()
{
}

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
}

int wasm_dsp::getSampleRate()
{
    return -1;
}

void wasm_dsp::init(int sample_rate)
{
}

void wasm_dsp::instanceInit(int sample_rate)
{
}

void wasm_dsp::instanceConstants(int sample_rate)
{
}

void wasm_dsp::instanceResetUserInterface()
{
}

void wasm_dsp::instanceClear()
{
}

wasm_dsp* wasm_dsp::clone()
{
    return nullptr;
}

void wasm_dsp::metadata(Meta* m)
{
}

void wasm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
}

void wasm_dsp::computeJS(int count, uintptr_t input, uintptr_t output)
{
}

void wasm_dsp::computeJSTest(int count)
{
}

void wasm_dsp::setParamValue(const std::string& path, FAUSTFLOAT value)
{
}

FAUSTFLOAT wasm_dsp::getParamValue(const std::string& path)
{
    return -1;
}

#endif
