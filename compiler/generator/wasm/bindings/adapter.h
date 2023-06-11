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
#include "faust/export.h"
#include "wasm_dynamic_dsp_aux.hh"


extern "C" LIBFAUST_API const char* getCLibFaustVersion();

struct FaustWasm {
    int cfactory;
    std::vector<int> data;
    std::string json;
    
    FaustWasm():cfactory(0)
    {}
};

class libFaustWasm
{
    public:
        libFaustWasm() {};
        virtual ~libFaustWasm() {};
    
        std::string version() { return ::getCLibFaustVersion(); }
    
        FaustWasm   createDSPFactory(const std::string name, const std::string dsp_content, const std::string args_aux, bool internal_memory);
        void        deleteAllDSPFactories() { ::deleteAllWasmDSPFactories(); }
        void        deleteDSPFactory(int cfactory);
    
        std::string expandDSP(const std::string name, const std::string dsp, const std::string args);
        bool        generateAuxFiles(const std::string name, const std::string dsp, const std::string args);
    
        void        cleanupAfterException() { ::cleanupAfterException(); }
        std::string getErrorAfterException() { return ::getErrorAfterException(); }
        
        std::string getInfos(const std::string what);
};


