/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2025 GRAME, Centre National de Creation Musicale
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

#ifndef WASM_DSP_AUX_H
#define WASM_DSP_AUX_H

#include <cstdlib>
#include <string>
#include <vector>

#include "faust/export.h"
#include "dsp_aux.hh"
#include "dsp_factory.hh"
#include "faust/dsp/wasm-dsp-imp.h"
#include "wasm_binary.hh"

#ifdef WASMTIME
#ifndef EMCC
// Wasmtime C API
#include <wasm.h>
#include <wasmtime.h>
#endif
#endif

/**
 * Concrete DSP instance backed by a Wasmtime instance (C‑API flavour).
 */

#ifdef WASMTIME

class LIBFAUST_API wasm_dsp_factory;

class LIBFAUST_API wasm_dsp : public wasm_dsp_imp {
   private:
    // One store per DSP instance (required for thread‑safety)
    wasmtime_store_t*   fStore;
    wasmtime_instance_t fInstance{};
    wasmtime_func_t     fComputeFunc{};

    /// Helper – call exported int(int) with dsp index = 0
    int callIntExport(const char* name);

   public:
    wasm_dsp(wasm_dsp_factory* factory, wasmtime_store_t* store,
             const wasmtime_instance_t& instance, char* memory_base);
    ~wasm_dsp();

    int getNumInputs() override;
    int getNumOutputs() override;
    int getSampleRate() override;

    void init(int sample_rate) override;
    void instanceInit(int sample_rate) override;
    void instanceConstants(int sample_rate) override;
    void instanceResetUserInterface() override;
    void instanceClear() override;

    wasm_dsp* clone() override;

    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override;
    void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override
    {
        compute(count, inputs, outputs);
    }
};

/**
 * Factory able to compile a .wasm file produced by the FAUST compiler and
 * instantiate DSP objects running in the Wasmtime runtime (C‑API flavour).
 */

typedef class faust_smartptr<wasm_dsp_factory> SDsp_factory;

class LIBFAUST_API wasm_dsp_factory : public wasm_dsp_factory_imp, public faust_smartable {
   private:
    dsp_factory_base* fFactory;

    // Long‑lived objects shared by all DSP instances
    wasm_engine_t*     fEngine    = nullptr;
    wasmtime_linker_t* fLinker    = nullptr;
    wasm_byte_vec_t    fWasmBytes = WASM_EMPTY_VEC;
    wasmtime_module_t* fModule    = nullptr;

   protected:
    wasm_dsp_factory(const std::string& binary_code);

   public:
    wasm_dsp_factory() : wasm_dsp_factory_imp() {}
    wasm_dsp_factory(dsp_factory_base* factory);
    virtual ~wasm_dsp_factory();

    std::string getName() override { return fDecoder->getName(); }

    std::string getSHAKey() override;
    void        setSHAKey(const std::string& sha_key);

    std::string getDSPCode() override;
    void        setDSPCode(const std::string& code);

    std::string getBinaryCode() { return fFactory->getBinaryCode(); }

    std::string              getCompileOptions() override;
    std::vector<std::string> getLibraryList() override;
    std::vector<std::string> getIncludePathnames() override;

    wasm_dsp* createDSPInstance() override;

    /** Register the math functions that the FAUST‑generated WASM expects. */
    static void registerMathFuns(wasmtime_linker_t* linker, wasmtime_store_t* store);

    static dsp_factory_table<SDsp_factory> gWasmFactoryTable;

    static std::string gErrorMessage;
};

#else

// The C++ side version of compiled wasm code

class wasm_dsp_factory;
struct JSONUIDecoderBase;

class LIBFAUST_API wasm_dsp : public dsp {
   private:
    wasm_dsp_factory* fFactory;

   public:
    wasm_dsp() : fFactory(nullptr) {}
    wasm_dsp(wasm_dsp_factory* factory) : fFactory(factory) {}
    virtual ~wasm_dsp() {}

    virtual int getNumInputs() { return -1; }

    virtual int getNumOutputs() { return -1; }

    virtual void buildUserInterface(UI* ui_interface) {}

    virtual int getSampleRate() { return -1; }

    virtual void init(int sample_rate) {}

    virtual void instanceInit(int sample_rate) {}

    virtual void instanceConstants(int sample_rate) {}

    virtual void instanceResetUserInterface() {}

    virtual void instanceClear() {}

    virtual wasm_dsp* clone() { return nullptr; }

    virtual void metadata(Meta* m) {}

    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
    
};

typedef class faust_smartptr<wasm_dsp_factory> SDsp_factory;

class LIBFAUST_API wasm_dsp_factory : public dsp_factory, public faust_smartable {
    friend class wasm_dsp;

   protected:
    dsp_factory_base*  fFactory;
    JSONUIDecoderBase* fDecoder;

   public:
    wasm_dsp_factory() : fFactory(nullptr), fDecoder(nullptr) {}
    wasm_dsp_factory(dsp_factory_base* factory);
    wasm_dsp_factory(int instance, const std::string& json);

    virtual ~wasm_dsp_factory() {}

    std::string getName();

    std::string getSHAKey();
    void        setSHAKey(const std::string& sha_key);

    std::string getDSPCode();
    void        setDSPCode(const std::string& code);

    std::string              getCompileOptions();
    std::vector<std::string> getLibraryList();
    std::vector<std::string> getIncludePathnames();

    std::vector<std::string> getWarningMessages();

    JSONUIDecoderBase* getDecoder() { return fDecoder; }

    wasm_dsp* createDSPInstance();
    void      deleteDSPInstance(wasm_dsp* dsp);

    void                setMemoryManager(dsp_memory_manager* manager);
    dsp_memory_manager* getMemoryManager();

    void write(std::ostream* out, bool binary, bool smallflag = false);
    void writeHelper(std::ostream* out, bool binary, bool smallflag = false);

    std::string getBinaryCode();

    static wasm_dsp_factory* readWasmDSPFactoryFromMachineFile2(
        const std::string& machine_code_path);

    static wasm_dsp_factory* readWasmDSPFactoryFromMachine2(const std::string& machine_code);

    static wasm_dsp_factory* createWasmDSPFactory(int instance, const std::string& json);

    static bool deleteWasmDSPFactory2(wasm_dsp_factory* factory);

    static std::string extractJSON(const std::string& code);

    static std::string gErrorMessage;

    static const std::string& getErrorMessage();

    static dsp_factory_table<SDsp_factory> gWasmFactoryTable;
};

#endif

LIBFAUST_API bool deleteWasmDSPFactory(wasm_dsp_factory* factory);

LIBFAUST_API void deleteAllWasmDSPFactories();

LIBFAUST_API wasm_dsp_factory* readWasmDSPFactoryFromMachine(const std::string& machine_code,
                                                             std::string&       error_msg);

LIBFAUST_API std::string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory);

LIBFAUST_API wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(
    const std::string& machine_code_path, std::string& error_msg);

LIBFAUST_API bool writeWasmDSPFactoryToMachineFile(wasm_dsp_factory*  factory,
                                                   const std::string& machine_code_path);

#endif
