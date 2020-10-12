/*
 Faust project
 Copyright (C) Grame 2020
 
 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
 
 Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
 research@grame.fr
 */

#include <vector>
#include <sstream>
#include "adapter.h"

using namespace std;

static void string2StringsVector(const string& args, vector<string>& strings)
{
    stringstream tokenizer(args);
    string token;
    
    // Use ' ' as delim for cutting string
    while (getline(tokenizer, token, ' ')) { strings.push_back(token); }
}

static const char** stringVector2argv(const vector<string>& v)
{
    const char** argv = nullptr;
    size_t n = v.size();
    if (n > 0) {
        argv = new const char*[n];
        for (size_t i = 0; i < n; i++) {
            argv[i] = v[i].c_str();
        }
    }
    return argv;
}

// Public API
int libFaustWasm::createDSPFactory(const string name, const string dsp_content, const string args_aux, bool internal_memory)
{
    vector<string> argsv;
    string2StringsVector(args_aux, argsv);
    size_t n = argsv.size();
   
    // 'errmsg' is actually not used: the possible error is returned in 'faustexception::gJSExceptionMsg'
    char errmsg[4096]; errmsg[0] = 0;
    int out;
    const char** args = stringVector2argv(argsv);
    out = int(::createWasmCDSPFactoryFromString(name.c_str(), dsp_content.c_str(), n, args, errmsg, internal_memory));
    delete [] args;
    return out;
}

ExpandOut libFaustWasm::expandDSP(const string name, const string dsp_content, const string args_aux)
{
    vector<string> argsv;
    string2StringsVector(args_aux, argsv);
    size_t n = argsv.size();
   
    ExpandOut out;
    const char** args = stringVector2argv(argsv);
    // 'errmsg' is actually not used: the possible error is returned in 'faustexception::gJSExceptionMsg'
    string sha_key, error_msg;
    out.dsp = ::expandDSPFromString(name, dsp_content, n, args, sha_key, error_msg);
    delete [] args;
    out.shakey = sha_key;
    return out;
}

bool libFaustWasm::generateAuxFiles(const string name, const string dsp_content, const string args_aux)
{
    vector<string> argsv;
    string2StringsVector(args_aux, argsv);
    size_t n = argsv.size();
    
    // 'errmsg' is actually not used: the possible error is returned in 'faustexception::gJSExceptionMsg'
    string error_msg;
    const char** args = stringVector2argv(argsv);
    bool out = ::generateAuxFilesFromString(name, dsp_content, n, args, error_msg);
    delete [] args;
    return out;
}

FaustWasm libFaustWasm::getWasmModule(int mptr)
{
    WasmModule* module = static_cast<WasmModule*>((void*)mptr);
    faustassert(module);
    
    FaustWasm out;
    const char* ptr = getWasmCModule(module);
    for (int i = 0; i < getWasmCModuleSize(module); i++) {
        out.data.push_back(*ptr++);
    }
    out.json = getWasmCHelpers(module);
    return out;
}

