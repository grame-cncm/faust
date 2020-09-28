/*
 Faust project
 Copyright (C) Grame 2020
 
 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
 
 Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
 research@grame.fr
 */

#pragma once

#include <string>
#include <vector>

#include "libfaust.h"
#include "export.hh"
#include "wasm_dynamic_dsp_aux.hh"

using namespace std;

struct ExpandOut {
    std::string dsp;
    std::string shakey;
};

struct FaustWasm {
    std::vector<int> data;
    std::string json;
};

class libFaustWasm
{
    public:
        libFaustWasm() {};
        virtual ~libFaustWasm() {};
    
        std::string version() { return ::getCLibFaustVersion(); }
        int  		createDSPFactory(const std::string name, const std::string dsp, const std::string args, bool internal_memory);
        ExpandOut   expandDSP(const std::string name, const std::string dsp, const std::string args);
        bool      	generateAuxFiles(const std::string name, const std::string dsp, const std::string args);
    
        void        deleteAllDSPFactories() { ::deleteAllWasmCDSPFactories(); }
    
        FaustWasm   getWasmModule(int module);
        void        freeWasmModule(int module) { ::freeWasmCModule(static_cast<WasmModule*>((void*)module)); }
    
        void        cleanupAfterException() { ::cleanupAfterException(); }
        std::string getErrorAfterException() { return ::getErrorAfterException(); }
};


