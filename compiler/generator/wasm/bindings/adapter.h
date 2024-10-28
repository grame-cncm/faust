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

#pragma once

#include <string>
#include <vector>

#include "faust/export.h"
#include "libfaust.h"
#include "wasm_dynamic_dsp_aux.hh"

extern "C" LIBFAUST_API const char* getCLibFaustVersion();

struct FaustWasm {
    int              cfactory;
    std::vector<int> data;
    std::string      json;

    FaustWasm() : cfactory(0) {}
};

class libFaustWasm {
   public:
    libFaustWasm(){};
    virtual ~libFaustWasm(){};

    std::string version() { return ::getCLibFaustVersion(); }

    FaustWasm createDSPFactory(const std::string name, const std::string dsp_content,
                               const std::string args_aux, bool internal_memory);
    void      deleteAllDSPFactories() { ::deleteAllWasmDSPFactories(); }
    void      deleteDSPFactory(int cfactory);

    std::string expandDSP(const std::string name, const std::string dsp, const std::string args);
    bool generateAuxFiles(const std::string name, const std::string dsp, const std::string args);

    void        cleanupAfterException() { ::cleanupAfterException(); }
    std::string getErrorAfterException() { return ::getErrorAfterException(); }

    std::string getInfos(const std::string what);
};
