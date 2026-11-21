/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

// Smoke test of a libfaust build with the LLVM backend (see libfaust.yml).
//
//   libfaust-smoke run           compile a DSP with LLVM and run it
//   libfaust-smoke write <file>  same, then save it as machine code
//   libfaust-smoke read <file>   load the machine code and run it
//   libfaust-smoke wasm          compile a DSP to a wasm module, with its JSON
//
// 'write' and 'read' run in two processes, so that loading machine code is
// tested in a process where no DSP was compiled before: that path
// initializes the LLVM targets on its own.
//
// 'wasm' checks the wasm-dsp.h API that a host uses to give the module of
// its DSP to a web page or a phone (faustgen~ for instance), in a libfaust
// built without wasmtime: the functions can be there (the host links) and
// still give an empty module or JSON, which only running them shows.

#include <cmath>
#include <cstdio>
#include <string>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/wasm-dsp.h"

// y(n) = 1 + 0.5 * y(n-1)
static const char* kCode = "process = 1 : + ~ *(0.5);";

static bool check(llvm_dsp_factory* factory, const char* what)
{
    dsp* d = factory->createDSPInstance();
    if (!d) {
        std::fprintf(stderr, "%s: no DSP instance\n", what);
        return false;
    }
    d->init(44100);
    FAUSTFLOAT  out[4] = {0, 0, 0, 0};
    FAUSTFLOAT* outs[1] = {out};
    d->compute(4, nullptr, outs);
    delete d;

    const double expected[4] = {1.0, 1.5, 1.75, 1.875};
    for (int i = 0; i < 4; i++) {
        if (std::fabs(double(out[i]) - expected[i]) > 1e-6) {
            std::fprintf(stderr, "%s: sample %d is %g, expected %g\n", what, i, double(out[i]), expected[i]);
            return false;
        }
    }
    std::printf("%s: OK (%s)\n", what, getDSPMachineTarget().c_str());
    return true;
}

// Compiles kCode to wasm with internal or external memory (a mono DSP or the voices of a
// polyphonic one), checks the module and the JSON, then reads the module back
static bool check_wasm(bool internal_memory)
{
    const char* what = internal_memory ? "wasm (internal memory)" : "wasm (external memory)";
    std::string error;
    wasm_dsp_factory* factory = createWasmDSPFactoryFromString("smoke", kCode, 0, nullptr, error, internal_memory);
    if (!factory) {
        std::fprintf(stderr, "%s: %s\n", what, error.c_str());
        return false;
    }
    std::string module = writeWasmDSPFactoryToBitcode(factory);
    std::string json = factory->getJSON();
    deleteWasmDSPFactory(factory);

    // A wasm module starts with "\0asm"; the JSON names the DSP and its one output
    if (module.size() < 8 || module.compare(0, 4, std::string("\0asm", 4)) != 0) {
        std::fprintf(stderr, "%s: no wasm module (%zu bytes)\n", what, module.size());
        return false;
    }
    if (json.find("\"name\": \"smoke\"") == std::string::npos || json.find("\"outputs\": 1") == std::string::npos) {
        std::fprintf(stderr, "%s: JSON without the DSP's name or output: '%s'\n", what, json.c_str());
        return false;
    }

    // The module read back gives the same JSON
    wasm_dsp_factory* read = readWasmDSPFactoryFromBitcode(module, error);
    if (!read) {
        std::fprintf(stderr, "%s: module not read back: %s\n", what, error.c_str());
        return false;
    }
    bool same = (read->getJSON() == json);
    deleteWasmDSPFactory(read);
    if (!same) {
        std::fprintf(stderr, "%s: the module read back gives another JSON\n", what);
        return false;
    }
    std::printf("%s: OK (%zu bytes of module, %zu of JSON)\n", what, module.size(), json.size());
    return true;
}

int main(int argc, char* argv[])
{
    std::string mode = (argc > 1) ? argv[1] : "run";
    std::string path = (argc > 2) ? argv[2] : "";
    if (mode == "wasm") {
        bool internal = check_wasm(true);
        bool external = check_wasm(false);
        return (internal && external) ? 0 : 1;
    }
    if ((mode != "run" && path.empty()) || (mode != "run" && mode != "write" && mode != "read")) {
        std::fprintf(stderr, "usage: %s run | write <file> | read <file> | wasm\n", argv[0]);
        return 2;
    }

    std::string       error;
    llvm_dsp_factory* factory = nullptr;
    if (mode == "read") {
        factory = readDSPFactoryFromMachineFile(path, "", error);
    } else {
        factory = createDSPFactoryFromString("smoke", kCode, 0, nullptr, "", error, -1);
    }
    if (!factory) {
        std::fprintf(stderr, "%s: %s\n", mode.c_str(), error.c_str());
        return 1;
    }

    bool ok = check(factory, mode.c_str());
    if (ok && mode == "write" && !writeDSPFactoryToMachineFile(factory, path, "")) {
        std::fprintf(stderr, "write: cannot write %s\n", path.c_str());
        ok = false;
    }
    deleteDSPFactory(factory);
    return ok ? 0 : 1;
}
