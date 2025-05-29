/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2025 GRAME, Centre National de Creation Musicale
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

#ifdef WASMTIME

using namespace std;
#define CTX(st) wasmtime_store_context(st)

// ---------------------------------------------------------------------
// Functype helpers
// ---------------------------------------------------------------------

// helper – build 1-param/1-result functype safely
static wasm_functype_t* fn_1_1(wasm_valkind_t p, wasm_valkind_t r)
{
    // allocate the pointer array on the heap (linker will free it later)
    auto** params  = new wasm_valtype_t*[1];
    auto** results = new wasm_valtype_t*[1];
    params[0]      = wasm_valtype_new(p);
    results[0]     = wasm_valtype_new(r);

    wasm_valtype_vec_t pvec;
    wasm_valtype_vec_t rvec;
    wasm_valtype_vec_new(&pvec, 1, params);   // takes ownership of `params`
    wasm_valtype_vec_new(&rvec, 1, results);  // takes ownership of `results`

    return wasm_functype_new(&pvec, &rvec);  // takes ownership of valtypes & arrays
}

// helper – 2-param/1-result
static wasm_functype_t* fn_2_1(wasm_valkind_t p0, wasm_valkind_t p1, wasm_valkind_t r0)
{
    auto** params  = new wasm_valtype_t*[2];
    auto** results = new wasm_valtype_t*[1];
    params[0]      = wasm_valtype_new(p0);
    params[1]      = wasm_valtype_new(p1);
    results[0]     = wasm_valtype_new(r0);

    wasm_valtype_vec_t pvec;
    wasm_valtype_vec_t rvec;
    wasm_valtype_vec_new(&pvec, 2, params);
    wasm_valtype_vec_new(&rvec, 1, results);

    return wasm_functype_new(&pvec, &rvec);
}

// ---------------------------------------------------------------------
// Host math callbacks
// ---------------------------------------------------------------------

#define UNARY_CB(NAME, FN, VKIND)                                                                \
    static wasm_trap_t* NAME##_cb(void*, wasmtime_caller_t*, const wasmtime_val_t* args, size_t, \
                                  wasmtime_val_t* res, size_t)                                   \
    {                                                                                            \
        res[0].kind = VKIND;                                                                     \
        if (VKIND == WASM_F32)                                                                   \
            res[0].of.f32 = FN(args[0].of.f32);                                                  \
        else                                                                                     \
            res[0].of.f64 = FN(args[0].of.f64);                                                  \
        return nullptr;                                                                          \
    }

#define BINARY_CB(NAME, FN, VKIND)                                                               \
    static wasm_trap_t* NAME##_cb(void*, wasmtime_caller_t*, const wasmtime_val_t* args, size_t, \
                                  wasmtime_val_t* res, size_t)                                   \
    {                                                                                            \
        res[0].kind = VKIND;                                                                     \
        if (VKIND == WASM_F32)                                                                   \
            res[0].of.f32 = FN(args[0].of.f32, args[1].of.f32);                                  \
        else                                                                                     \
            res[0].of.f64 = FN(args[0].of.f64, args[1].of.f64);                                  \
        return nullptr;                                                                          \
    }

UNARY_CB(_sinf, std::sinf, WASM_F32)
UNARY_CB(_cosf, std::cosf, WASM_F32)
UNARY_CB(_tanf, std::tanf, WASM_F32)
UNARY_CB(_asinf, std::asinf, WASM_F32)
UNARY_CB(_acosf, std::acosf, WASM_F32)
UNARY_CB(_atanf, std::atanf, WASM_F32)
UNARY_CB(_expf, std::expf, WASM_F32)
UNARY_CB(_logf, std::logf, WASM_F32)
UNARY_CB(_log10f, std::log10f, WASM_F32)
UNARY_CB(_roundf, std::roundf, WASM_F32)
UNARY_CB(_sinhf, std::sinhf, WASM_F32)
UNARY_CB(_coshf, std::coshf, WASM_F32)
UNARY_CB(_tanhf, std::tanhf, WASM_F32)
UNARY_CB(_asinhf, std::asinhf, WASM_F32)
UNARY_CB(_acoshf, std::acoshf, WASM_F32)
UNARY_CB(_atanhf, std::atanhf, WASM_F32)

UNARY_CB(_sin, std::sin, WASM_F64)
UNARY_CB(_cos, std::cos, WASM_F64)
UNARY_CB(_tan, std::tan, WASM_F64)
UNARY_CB(_asin, std::asin, WASM_F64)
UNARY_CB(_acos, std::acos, WASM_F64)
UNARY_CB(_atan, std::atan, WASM_F64)
UNARY_CB(_exp, std::exp, WASM_F64)
UNARY_CB(_log, std::log, WASM_F64)
UNARY_CB(_log10, std::log10, WASM_F64)
UNARY_CB(_round, std::round, WASM_F64)
UNARY_CB(_sinh, std::sinh, WASM_F64)
UNARY_CB(_cosh, std::cosh, WASM_F64)
UNARY_CB(_tanh, std::tanh, WASM_F64)
UNARY_CB(_asinh, std::asinh, WASM_F64)
UNARY_CB(_acosh, std::acosh, WASM_F64)
UNARY_CB(_atanh, std::atanh, WASM_F64)

BINARY_CB(_atan2f, std::atan2f, WASM_F32)
BINARY_CB(_fmodf, std::fmodf, WASM_F32)
BINARY_CB(_powf, std::powf, WASM_F32)
BINARY_CB(_remainderf, std::remainderf, WASM_F32)

BINARY_CB(_atan2, std::atan2, WASM_F64)
BINARY_CB(_fmod, std::fmod, WASM_F64)
BINARY_CB(_pow, std::pow, WASM_F64)
BINARY_CB(_remainder, std::remainder, WASM_F64)

// abs(int)
static wasm_trap_t* _abs_cb(void*, wasmtime_caller_t*, const wasmtime_val_t* args, size_t,
                            wasmtime_val_t* res, size_t)
{
    res[0].kind   = WASM_I32;
    res[0].of.i32 = std::abs(args[0].of.i32);
    return nullptr;
}

// ---------------------------------------------------------------------
// Factory
// ---------------------------------------------------------------------

wasm_dsp_factory::wasm_dsp_factory(const string& binary_code) : wasm_dsp_factory_imp()
{
    fEngine = wasm_engine_new();
    fLinker = wasmtime_linker_new(fEngine);

    // Register math funcs
    wasmtime_store_t* store = wasmtime_store_new(fEngine, nullptr, nullptr);
    registerMathFuns(fLinker, store);

    // Compile module
    wasm_byte_vec_new_uninitialized(&fWasmBytes, binary_code.size());
    memcpy(fWasmBytes.data, binary_code.data(), binary_code.size());

    wasmtime_module_new(fEngine, reinterpret_cast<const uint8_t*>(fWasmBytes.data), fWasmBytes.size,
                        &fModule);

    wasm_trap_t*        trap = nullptr;
    wasmtime_instance_t inst;
    wasmtime_linker_instantiate(fLinker, CTX(store), fModule, &inst, &trap);

    wasmtime_extern_t memExt;
    wasmtime_instance_export_get(CTX(store), &inst, "memory", strlen("memory"), &memExt);

    char* memory     = reinterpret_cast<char*>(wasmtime_memory_data(CTX(store), &memExt.of.memory));
    std::string json = std::string(memory);
    fDecoder         = createJSONUIDecoder(json);

    wasmtime_store_delete(store);
}

//--------------------------------------------------------------------
// Helper: register one host callback
//--------------------------------------------------------------------
static void define_func(wasmtime_linker_t* linker, wasmtime_store_t*, const char* name,
                        wasm_functype_t* ft, wasmtime_func_callback_t cb)
{
    wasmtime_linker_define_func(linker, "env", 3,    // module name
                                name, strlen(name),  // export name
                                ft,                  // type
                                cb,                  // callback
                                nullptr,             // env  (not needed)
                                nullptr              // finalizer (not needed)
    );
}

void wasm_dsp_factory::registerMathFuns(wasmtime_linker_t* linker, wasmtime_store_t* s)
{
    define_func(linker, s, "_abs", fn_1_1(WASM_I32, WASM_I32), _abs_cb);

#define REG_UN(name, kind) define_func(linker, s, #name, fn_1_1(kind, kind), name##_cb)
#define REG_BIN(name, kind) define_func(linker, s, #name, fn_2_1(kind, kind, kind), name##_cb)

    // Float
    REG_UN(_sinf, WASM_F32);
    REG_UN(_cosf, WASM_F32);
    REG_UN(_tanf, WASM_F32);
    REG_UN(_asinf, WASM_F32);
    REG_UN(_acosf, WASM_F32);
    REG_UN(_atanf, WASM_F32);
    REG_UN(_expf, WASM_F32);
    REG_UN(_logf, WASM_F32);
    REG_UN(_log10f, WASM_F32);
    REG_UN(_roundf, WASM_F32);
    REG_UN(_sinhf, WASM_F32);
    REG_UN(_coshf, WASM_F32);
    REG_UN(_tanhf, WASM_F32);
    REG_UN(_asinhf, WASM_F32);
    REG_UN(_acoshf, WASM_F32);
    REG_UN(_atanhf, WASM_F32);

    REG_BIN(_atan2f, WASM_F32);
    REG_BIN(_fmodf, WASM_F32);
    REG_BIN(_powf, WASM_F32);
    REG_BIN(_remainderf, WASM_F32);

    // Double
    REG_UN(_sin, WASM_F64);
    REG_UN(_cos, WASM_F64);
    REG_UN(_tan, WASM_F64);
    REG_UN(_asin, WASM_F64);
    REG_UN(_acos, WASM_F64);
    REG_UN(_atan, WASM_F64);
    REG_UN(_exp, WASM_F64);
    REG_UN(_log, WASM_F64);
    REG_UN(_log10, WASM_F64);
    REG_UN(_round, WASM_F64);
    REG_UN(_sinh, WASM_F64);
    REG_UN(_cosh, WASM_F64);
    REG_UN(_tanh, WASM_F64);
    REG_UN(_asinh, WASM_F64);
    REG_UN(_acosh, WASM_F64);
    REG_UN(_atanh, WASM_F64);

    REG_BIN(_atan2, WASM_F64);
    REG_BIN(_fmod, WASM_F64);
    REG_BIN(_pow, WASM_F64);
    REG_BIN(_remainder, WASM_F64);

#undef REG_UN
#undef REG_BIN
}

wasm_dsp_factory::wasm_dsp_factory(dsp_factory_base* factory)
    : wasm_dsp_factory(factory->getBinaryCode())
{
    fFactory = factory;
}

wasm_dsp_factory::~wasm_dsp_factory()
{
    if (fModule) {
        wasmtime_module_delete(fModule);
    }
    if (fLinker) {
        wasmtime_linker_delete(fLinker);
    }
    if (fEngine) {
        wasm_engine_delete(fEngine);
    }
    wasm_byte_vec_delete(&fWasmBytes);
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

wasm_dsp* wasm_dsp_factory::createDSPInstance()
{
    wasmtime_store_t* store = wasmtime_store_new(fEngine, nullptr, nullptr);

    wasm_trap_t*        trap = nullptr;
    wasmtime_instance_t inst;
    wasmtime_linker_instantiate(fLinker, CTX(store), fModule, &inst, &trap);

    wasmtime_extern_t memExt;
    wasmtime_instance_export_get(CTX(store), &inst, "memory", strlen("memory"), &memExt);

    char* memory = reinterpret_cast<char*>(wasmtime_memory_data(CTX(store), &memExt.of.memory));
    return new wasm_dsp(this, store, inst, memory);
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

LIBFAUST_API bool writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory,
                                                   const string&     machine_code_path)
{
    ofstream outfile;
    outfile.open(machine_code_path, ofstream::out | ofstream::binary);
    if (outfile.is_open()) {
        outfile << factory->getBinaryCode();
        ;
        outfile.close();
        return true;
    } else {
        cerr << "writeWasmDSPFactoryToMachineFile : cannot open '" << machine_code_path
             << "' file\n";
        return false;
    }
}

// ---------------------------------------------------------------------
// DSP instance
// ---------------------------------------------------------------------

wasm_dsp::wasm_dsp(wasm_dsp_factory* factory, wasmtime_store_t* store,
                   const wasmtime_instance_t& instance, char* memory)
    : wasm_dsp_imp(factory, memory), fStore(store), fInstance(instance)
{
    initDecoder();

    wasmtime_extern_t ext;
    wasmtime_instance_export_get(CTX(fStore), &fInstance, "compute", strlen("compute"), &ext);
    fComputeFunc = ext.of.func;
}

wasm_dsp::~wasm_dsp()
{
    wasmtime_store_delete(fStore);
}

int wasm_dsp::callIntExport(const char* name)
{
    wasmtime_extern_t ext;
    wasmtime_instance_export_get(CTX(fStore), &fInstance, name, strlen(name), &ext);

    wasmtime_val_t arg{.kind = WASM_I32, .of = {.i32 = 0}};
    wasmtime_val_t out;
    wasm_trap_t*   trap = nullptr;
    wasmtime_func_call(CTX(fStore), &ext.of.func, &arg, 1, &out, 1, &trap);
    return out.of.i32;
}

int wasm_dsp::getNumInputs()
{
    return callIntExport("getNumInputs");
}
int wasm_dsp::getNumOutputs()
{
    return callIntExport("getNumOutputs");
}
int wasm_dsp::getSampleRate()
{
    return callIntExport("getSampleRate");
}

void wasm_dsp::instanceResetUserInterface()
{
    wasmtime_extern_t ext;
    wasmtime_instance_export_get(CTX(fStore), &fInstance, "instanceResetUserInterface",
                                 strlen("instanceResetUserInterface"), &ext);
    wasmtime_val_t arg{.kind = WASM_I32, .of = {.i32 = 0}};
    wasm_trap_t*   trap = nullptr;
    wasmtime_func_call(CTX(fStore), &ext.of.func, &arg, 1, nullptr, 0, &trap);
}

void wasm_dsp::instanceClear()
{
    wasmtime_extern_t ext;
    wasmtime_instance_export_get(CTX(fStore), &fInstance, "instanceClear",
                                                        strlen("instanceClear"), &ext);
    wasmtime_val_t arg{.kind = WASM_I32, .of = {.i32 = 0}};
    wasm_trap_t*   trap = nullptr;
    wasmtime_func_call(CTX(fStore), &ext.of.func, &arg, 1, nullptr, 0, &trap);
}

static void call_i32_i32(wasmtime_store_t* st, const wasmtime_instance_t* inst, const char* fn,
                         int v, wasm_trap_t** trap)
{
    wasmtime_extern_t ext;
    wasmtime_instance_export_get(CTX(st), inst, fn, strlen(fn), &ext);
    wasmtime_val_t a[2];
    a[0].kind   = WASM_I32;
    a[0].of.i32 = 0;
    a[1].kind   = WASM_I32;
    a[1].of.i32 = v;
    wasmtime_func_call(CTX(st), &ext.of.func, a, 2, nullptr, 0, trap);
}

void wasm_dsp::init(int sr)
{
    wasm_trap_t* t = nullptr;
    call_i32_i32(fStore, &fInstance, "init", sr, &t);
}
void wasm_dsp::instanceInit(int sr)
{
    wasm_trap_t* t = nullptr;
    call_i32_i32(fStore, &fInstance, "instanceInit", sr, &t);
}
void wasm_dsp::instanceConstants(int sr)
{
    wasm_trap_t* t = nullptr;
    call_i32_i32(fStore, &fInstance, "instanceConstants", sr, &t);
}

wasm_dsp* wasm_dsp::clone()
{
    return reinterpret_cast<wasm_dsp*>(fFactory->createDSPInstance());
}

void wasm_dsp::compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
{
    for (int c = 0; c < fFactory->fDecoder->getNumInputs(); ++c) {
        memcpy(fInputs[c], inputs[c], sizeof(FAUSTFLOAT) * count);
    }

    wasmtime_val_t a[4];
    a[0].kind   = WASM_I32;
    a[0].of.i32 = 0;
    a[1].kind   = WASM_I32;
    a[1].of.i32 = count;
    a[2].kind   = WASM_I32;
    a[2].of.i32 = fWasmInputs;
    a[3].kind   = WASM_I32;
    a[3].of.i32 = fWasmOutputs;

    wasm_trap_t* trap = nullptr;
    wasmtime_func_call(CTX(fStore), &fComputeFunc, a, 4, nullptr, 0, &trap);

    for (int c = 0; c < fFactory->fDecoder->getNumOutputs(); ++c) {
        memcpy(outputs[c], fOutputs[c], sizeof(FAUSTFLOAT) * count);
    }
}

#else

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

#endif

// Static constructor

string wasm_dsp_factory::gErrorMessage = "";

// C++ API

LIBFAUST_API bool deleteWasmDSPFactory(wasm_dsp_factory* factory)
{
    return (factory) ? wasm_dsp_factory::gWasmFactoryTable.deleteDSPFactory(factory) : false;
}

LIBFAUST_API void deleteAllWasmDSPFactories()
{
    wasm_dsp_factory::gWasmFactoryTable.deleteAllDSPFactories();
}
