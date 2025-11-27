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

#include <sstream>
#include <vector>

#include "Text.hh"
#include "adapter.h"
#include "global.hh"

using namespace std;

static void string2StringsVector(const string& args, vector<string>& strings)
{
    // Split a space-delimited argument string into a vector of tokens.
    stringstream tokenizer(args);
    string       token;

    // Use ' ' as delim for cutting string
    while (getline(tokenizer, token, ' ')) {
        strings.push_back(token);
    }
}

static const char** stringVector2argv(const vector<string>& v)
{
    // Build a transient argv-style array (no trailing nullptr).
    const char** argv = nullptr;
    size_t       n    = v.size();
    if (n > 0) {
        argv = new const char*[n];
        for (size_t i = 0; i < n; i++) {
            argv[i] = v[i].c_str();
        }
    }
    return argv;
}

// Convert a native wasm_dsp_factory into the embind-friendly FaustWasm struct.
static FaustWasm makeFaustWasm(wasm_dsp_factory* factory)
{
    // Convert a native factory into the embind-friendly struct (pointer + code + JSON).
    FaustWasm out;
    if (!factory) {
        return out;
    }

    // Keep C++ pointer as an int
    out.cfactory = int(factory);

    // 'Binary' string, so directly copy its raw content
    string code = factory->getBinaryCode();
    out.data.assign(code.begin(), code.end());

    // JSON file
    stringstream json;
    factory->writeHelper(&json, false, false);
    out.json = json.str();
    return out;
}

// Common wrapper to parse CLI args and invoke a factory builder lambda.
template <typename Builder>
static FaustWasm buildFactory(const string& args_aux, Builder&& builder)
{
    // Parse args, run the provided builder, then serialize into FaustWasm.
    vector<string> argsv;
    string2StringsVector(args_aux, argsv);
    size_t n = argsv.size();

    const char** argv = stringVector2argv(argsv);
    wasm_dsp_factory* factory = builder(n, argv);
    delete[] argv;

    return makeFaustWasm(factory);
}

// Public API

// Build a wasm DSP factory from DSP source code.
FaustWasm libFaustWasm::createDSPFactory(const string name, const string dsp_content,
                                         const string args_aux, bool internal_memory)
{
    return buildFactory(args_aux, [&](size_t n, const char** argv) {
        // 'error_msg' is actually not used: the possible error is returned in
        // 'faustexception::gJSExceptionMsg'
        string error_msg;
        return ::createWasmDSPFactoryFromString(name, dsp_content, n, argv, error_msg,
                                                internal_memory);
    });
}

// Build a wasm DSP factory directly from a vector of signals.
FaustWasm libFaustWasm::createDSPFactoryFromSignals(const string name, tvec signals,
                                                    const string args_aux, bool internal_memory)
{
    return buildFactory(args_aux, [&](size_t n, const char** argv) {
        // 'error_msg' is actually not used: the possible error is returned in
        // 'faustexception::gJSExceptionMsg'
        string error_msg;
        return ::createWasmDSPFactoryFromSignals(name, signals, n, argv, error_msg,
                                                 internal_memory);
    });
}

// Build a wasm DSP factory from a box expression.
FaustWasm libFaustWasm::createDSPFactoryFromBoxes(const string name, Tree box,
                                                  const string args_aux, bool internal_memory)
{
    return buildFactory(args_aux, [&](size_t n, const char** argv) {
        // 'error_msg' is actually not used: the possible error is returned in
        // 'faustexception::gJSExceptionMsg'
        string error_msg;
        return ::createWasmDSPFactoryFromBoxes(name, box, n, argv, error_msg, internal_memory);
    });
}

void libFaustWasm::deleteDSPFactory(int cfactory)
{
    // Delete a single factory created via wasm helpers.
    deleteWasmDSPFactory(static_cast<wasm_dsp_factory*>((void*)cfactory));
}

string libFaustWasm::expandDSP(const string name, const string dsp_content, const string args_aux)
{
    // Expand a DSP string (inline imports) using the core libfaust API.
    vector<string> argsv;
    string2StringsVector(args_aux, argsv);
    size_t n = argsv.size();

    // 'error_msg' is actually not used: the possible error is returned in
    // 'faustexception::gJSExceptionMsg'
    string       sha_key, error_msg;
    const char** args     = stringVector2argv(argsv);
    string       expanded = ::expandDSPFromString(name, dsp_content, n, args, sha_key, error_msg);
    delete[] args;
    return expanded;
}

bool libFaustWasm::generateAuxFiles(const string name, const string dsp_content,
                                    const string args_aux)
{
    // Run auxiliary file generation (SVG/JSON/other backends) from a DSP string.
    vector<string> argsv;
    string2StringsVector(args_aux, argsv);
    // 'error_msg' is actually not used: the possible error is returned in
    // 'faustexception::gJSExceptionMsg'
    string       error_msg;
    const char** args = stringVector2argv(argsv);
    size_t       n    = argsv.size();
    bool         res  = ::generateAuxFilesFromString(name, dsp_content, n, args, error_msg);
    delete[] args;
    return res;
}

string libFaustWasm::getInfos(const std::string what)
{
    // Return string info about libfaust environment (version, dirs, help...).
    if (what == "version") {
        return global::printVersion();
    }
    if (what == "help") {
        return global::printHelp();
    }
    if (what == "libdir") {
        return gGlobal->printLibDir();
    }
    if (what == "includedir") {
        return gGlobal->printIncludeDir();
    }
    if (what == "archdir") {
        return gGlobal->printArchDir();
    }
    if (what == "dspdir") {
        return gGlobal->printDspDir();
    }
    if (what == "pathslist") {
        return gGlobal->printPaths();
    }
    return "incorrect argument passed to getInfos";
}
