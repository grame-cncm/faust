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
#include "libfaust.h"
#include "faust/gui/JSONUIDecoder.h"

// For tests
#include "faust/gui/PrintUI.h"
#include "faust/dsp/dsp-combiner.h"
#include "faust/gui/JSONUI.h"

#ifdef EMCC
#include <emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;
#endif

dsp_factory_table<SDsp_factory> gWasmFactoryTable;

#ifdef EMCC

EM_JS(int, createJSModuleFromString, (uint8_t* code_ptr, size_t code_size), {
    
    // Done once when creating the first factory
    FaustModule.faust = FaustModule.faust || {};
    FaustModule.faust.wasm_module = FaustModule.faust.wasm_module || [];
    FaustModule.faust.wasm_instance = FaustModule.faust.wasm_instance || [];
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
                
            // Emscripten generated global memory segment is used
            memory: FaustModule['wasmMemory'],
                
            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
        }
    };
    
    // Copy native 'binary' string in JavaScript Uint8Array
    var factory_code = new Uint8Array(code_size);
    for (var i = 0; i < code_size; i++) {
        // faster than 'getValue' which gets the type of access for each read...
        factory_code[i] = FaustModule.HEAP8[code_ptr + i];
    }
    
    // Compile wasm module
    FaustModule.faust.wasm_module.push(new WebAssembly.Module(factory_code));
    return FaustModule.faust.wasm_module.length - 1;

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
    // Deactivated for now
    /*
    createModuleFromString();
    std::cout << "fModule " << fModule << std::endl;
    
    fDecoder = new JSONUIDecoder(fJSON);
    std::cout << " fFactory->getJSON() " << fJSON << std::endl;
    */
    fModule = -1;
    fDecoder = nullptr;
}

#else

void wasm_dsp_factory::createModuleFromString()
{}

wasm_dsp_factory::wasm_dsp_factory(dsp_factory_base* factory) : fFactory(factory)
{
    fModule = 0;
}

#endif

wasm_dsp_factory::~wasm_dsp_factory()
{
    delete fFactory;
    delete fDecoder;
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
    
    var wasm_instance = new WebAssembly.Instance(FaustModule.faust.wasm_module[module], FaustModule.faust.importObject);
    FaustModule.faust.wasm_instance.push(wasm_instance);
    return FaustModule.faust.wasm_instance.length - 1;
});

wasm_dsp* wasm_dsp_factory::createDSPInstance()
{
    wasm_dsp* dsp = new wasm_dsp(this, createJSDSPInstance(fModule));
    gWasmFactoryTable.addDSP(this, dsp);
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

FAUSTFLOAT** wasm_dsp_factory::createAudioBuffers(int chan, int frames)
{
    FAUSTFLOAT** buffers = new FAUSTFLOAT*[chan];
    for (int i = 0; i < chan; i++) {
        buffers[i] = new FAUSTFLOAT[frames];
        memset(buffers[i], 0, frames * sizeof(FAUSTFLOAT));
    }
    return buffers;
}

void wasm_dsp_factory::copyAudioBuffer(FAUSTFLOAT** js_buffers, FAUSTFLOAT* js_buffer, int chan, int frames)
{
    memcpy(js_buffers[chan], js_buffer, frames * sizeof(FAUSTFLOAT));
}

void wasm_dsp_factory::deleteAudioBuffers(FAUSTFLOAT** buffers, int chan)
{
    for (int i = 0; i < chan; i++) {
        delete [] buffers[i];
    }
    delete [] buffers;
}

uintptr_t wasm_dsp_factory::createJSAudioBuffers(int chan, int frames)
{
    return reinterpret_cast<uintptr_t>(createAudioBuffers(chan, frames));
}

void wasm_dsp_factory::copyJSAudioBuffer(uintptr_t js_buffers, uintptr_t js_buffer, int chan, int frames)
{
    copyAudioBuffer(reinterpret_cast<FAUSTFLOAT**>(js_buffers), reinterpret_cast<FAUSTFLOAT*>(js_buffer), chan, frames);
}

void wasm_dsp_factory::deleteJSAudioBuffers(uintptr_t js_buffers, int chan)
{
    deleteAudioBuffers(reinterpret_cast<FAUSTFLOAT**>(js_buffers), chan);
}

// Static constructor

std::string wasm_dsp_factory::gErrorMessage = "";

const std::string&  wasm_dsp_factory::getErrorMessage() { return wasm_dsp_factory::gErrorMessage; }

wasm_dsp_factory* wasm_dsp_factory::readWasmDSPFactoryFromMachineFile2(const std::string& machine_code_path)
{
    return readWasmDSPFactoryFromMachineFile(machine_code_path);
}

wasm_dsp_factory* wasm_dsp_factory::readWasmDSPFactoryFromMachine2(const std::string& machine_code)
{
    return readWasmDSPFactoryFromMachine(machine_code);
}

// C++ API

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
    std::ifstream infile;
    infile.open(machine_code_path, std::ifstream::in | std::ifstream::binary);
    
    if (infile.is_open()) {
        // get length of file:
        infile.seekg(0, infile.end);
        int length = infile.tellg();
        infile.seekg(0, infile.beg);
        
        // read code
        char* machine_code = new char[length];
        infile.read(machine_code, length);
        
        // create factory
        wasm_dsp_factory* factory = readWasmDSPFactoryFromMachine(string(machine_code, length)); // Keep the binary string
        
        infile.close();
        delete[] machine_code;
        
        return factory;
    } else {
        std::cerr << "readWasmDSPFactoryFromMachineFile : cannot open '" << machine_code_path << "' file\n";
        return nullptr;
    }
}

EXPORT void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory, const std::string& machine_code_path)
{
    std::ofstream outfile;
    outfile.open(machine_code_path, std::ofstream::out | std::ofstream::binary);
    if (outfile.is_open()) {
        outfile << factory->getBinaryCode();
        outfile.close();
    } else {
        std::cerr << "writeWasmDSPFactoryToMachineFile : cannot open '" << machine_code_path << "' file\n";
    }
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

wasm_dsp::wasm_dsp(wasm_dsp_factory* factory, int index):fFactory(factory), fIndex(index)
{
    fDSP = EM_ASM_INT({
        return FaustModule._malloc($0);
    }, fFactory->getDecoder()->fDSPSize);
}

wasm_dsp::~wasm_dsp()
{
    EM_ASM({
        // Empty the JS structures so that the instance can be GCed
        FaustModule.faust.wasm_instance[$0] = null;
        // Free the DSP memory
        FaustModule._free($1);
    }, fIndex, fDSP);
}

int wasm_dsp::getNumInputs()
{
    return EM_ASM_INT({
        return FaustModule.faust.wasm_instance[$0].exports.getNumInputs($1);
    }, fIndex, fDSP);
}

int wasm_dsp::getNumOutputs()
{
    return EM_ASM_INT({
        return FaustModule.faust.wasm_instance[$0].exports.getNumOutputs($1);
    }, fIndex, fDSP);
}

void wasm_dsp::buildUserInterface(UI* ui_interface)
{
    fFactory->getDecoder()->buildUserInterface(ui_interface);
}

int wasm_dsp::getSampleRate()
{
    return EM_ASM_INT({
        return FaustModule.faust.wasm_instance[$0].exports.getSampleRate($1);
    }, fIndex, fDSP);
}

void wasm_dsp::init(int samplingRate)
{
    EM_ASM({
        FaustModule.faust.wasm_instance[$0].exports.init($1);
    }, fIndex, fDSP, samplingRate);
}

void wasm_dsp::instanceInit(int samplingRate)
{
    EM_ASM({
        FaustModule.faust.wasm_instance[$0].exports.instanceInit($1, $2);
    }, fIndex, fDSP, samplingRate);
}

void wasm_dsp::instanceConstants(int samplingRate)
{
    EM_ASM({
        FaustModule.faust.wasm_instance[$0].exports.instanceConstants($1, $2);
    }, fIndex, fDSP, samplingRate);
}

void wasm_dsp::instanceResetUserInterface()
{
    EM_ASM({
        FaustModule.faust.wasm_instance[$0].exports.instanceResetUserInterface($1);
    }, fIndex, fDSP);
}

void wasm_dsp::instanceClear()
{
    EM_ASM({
        FaustModule.faust.wasm_instance[$0].exports.instanceClear($1);
    }, fIndex, fDSP);
}

wasm_dsp* wasm_dsp::clone()
{
    return fFactory->createDSPInstance();
}

void wasm_dsp::metadata(Meta* m)
{
    fFactory->getDecoder()->metadata(m);
}

void wasm_dsp::computeJS(int count, uintptr_t input, uintptr_t output)
{
    //std::cout << "wasm_dsp::computeJS " << count << std::endl;
    
    EM_ASM({
        FaustModule.faust.wasm_instance[$0].exports.compute($1, $2, $3, $4);
    }, fIndex, fDSP, count, input, output);
}

void wasm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    //std::cout << "wasm_dsp::compute " << count << std::endl;
    
    EM_ASM({
        FaustModule.faust.wasm_instance[$0].exports.compute($1, $2, $3, $4);
    }, fIndex, fDSP, count, reinterpret_cast<uintptr_t>(input), reinterpret_cast<uintptr_t>(output));
}

void wasm_dsp::computeJSTest(int count)
{
    FAUSTFLOAT** inputs = wasm_dsp_factory::createAudioBuffers(getNumInputs(), count);
    FAUSTFLOAT** outputs = wasm_dsp_factory::createAudioBuffers(getNumOutputs(), count);
    
    std::cout << "computeJSTest " << count << " " << getNumInputs() << " " << getNumOutputs() << std::endl;
    std::cout << "computeJSTest inputs " << inputs << " outputs " << outputs << std::endl;
    
    for (int chan = 0; chan < getNumInputs(); chan++) {
        for (int frame = 0; frame < 10; frame++) {
            std::cout << "frame input = " << frame << " : " << (inputs[chan][frame]) << std::endl;
        }
    }
    
    //init(44100);
    //compute(count, inputs, outputs);
    
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
    
    for (int chan = 0; chan < getNumOutputs(); chan++) {
        for (int frame = 0; frame < 10; frame++) {
            std::cout << "frame output = " << frame << " : " << (outputs[chan][frame]) << std::endl;
        }
    }
    
    wasm_dsp_factory::deleteAudioBuffers(inputs, getNumInputs());
    wasm_dsp_factory::deleteAudioBuffers(outputs, getNumOutputs());
}

EMSCRIPTEN_BINDINGS(CLASS_wasm_dsp_factory) {
    class_<wasm_dsp_factory>("wasm_dsp_factory")
    .constructor()
    .function("createDSPInstance",
              &wasm_dsp_factory::createDSPInstance,
              allow_raw_pointers())
    .function("getJSON",
              &wasm_dsp_factory::getJSON,
              allow_raw_pointers())
    .class_function("readWasmDSPFactoryFromMachineFile2",
                    &wasm_dsp_factory::readWasmDSPFactoryFromMachineFile2,
                    allow_raw_pointers())
    .class_function("readWasmDSPFactoryFromMachine2",
                    &wasm_dsp_factory::readWasmDSPFactoryFromMachine2,
                    allow_raw_pointers())
    .class_function("createAudioBuffers",
                    &wasm_dsp_factory::createJSAudioBuffers,
                    allow_raw_pointers())
    .class_function("deleteAudioBuffers",
                    &wasm_dsp_factory::deleteJSAudioBuffers,
                    allow_raw_pointers())
    .class_function("copyAudioBuffer",
                    &wasm_dsp_factory::copyJSAudioBuffer,
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
    .function("compute",
              &wasm_dsp::computeJS,
              allow_raw_pointers())
    .function("computeJSTest",
              &wasm_dsp::computeJSTest,
              allow_raw_pointers());
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

void wasm_dsp::computeJS(int count, uintptr_t input, uintptr_t output)
{}

void wasm_dsp::computeJSTest(int count)
{}

#endif
