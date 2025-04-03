/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2024 GRAME, Centre National de Creation Musicale
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
    stringstream tokenizer(args);
    string       token;

    // Use ' ' as delim for cutting string
    while (getline(tokenizer, token, ' ')) {
        strings.push_back(token);
    }
}

static const char** stringVector2argv(const vector<string>& v)
{
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

// Public API
FaustWasm libFaustWasm::createDSPFactory(const string name, const string dsp_content,
                                         const string args_aux, bool internal_memory)
{
    vector<string> argsv;
    string2StringsVector(args_aux, argsv);
    size_t n = argsv.size();

    // 'error_msg' is actually not used: the possible error is returned in
    // 'faustexception::gJSExceptionMsg'
    string            error_msg;
    const char**      args = stringVector2argv(argsv);
    wasm_dsp_factory* factory =
        ::createWasmDSPFactoryFromString(name, dsp_content, n, args, error_msg, internal_memory);
    delete[] args;

    FaustWasm out;
    if (factory) {
        // Keep C++ pointer as an int
        out.cfactory = int(factory);

        // 'Binary' string, so directly copy its raw content
        string code = factory->getBinaryCode();
        for (size_t i = 0; i < code.size(); i++) {
            out.data.push_back(code[i]);
        }

        // JSON file
        stringstream json;
        factory->writeHelper(&json, false, false);
        out.json = json.str();
    }
    return out;
}

void libFaustWasm::deleteDSPFactory(int cfactory)
{
    deleteWasmDSPFactory(static_cast<wasm_dsp_factory*>((void*)cfactory));
}

string libFaustWasm::expandDSP(const string name, const string dsp_content, const string args_aux)
{
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
