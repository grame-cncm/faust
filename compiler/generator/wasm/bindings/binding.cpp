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

#include <emscripten.h>
#include <emscripten/bind.h>

#include "adapter.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(CStruct)
{
    value_object<FaustWasm>("FaustWasm")
        .field("cfactory", &FaustWasm::cfactory)
        .field("data", &FaustWasm::data)
        .field("json", &FaustWasm::json);
}

EMSCRIPTEN_BINDINGS(FaustModule)
{
    emscripten::class_<libFaustWasm>("libFaustWasm")
        .constructor<>()
        .function("version", &libFaustWasm::version, allow_raw_pointers())

        .function("createDSPFactory", &libFaustWasm::createDSPFactory, allow_raw_pointers())
        .function("deleteDSPFactory", &libFaustWasm::deleteDSPFactory, allow_raw_pointers())
        .function("deleteAllDSPFactories", &libFaustWasm::deleteAllDSPFactories)

        .function("expandDSP", &libFaustWasm::expandDSP, allow_raw_pointers())
        .function("generateAuxFiles", &libFaustWasm::generateAuxFiles, allow_raw_pointers())

        .function("cleanupAfterException", &libFaustWasm::cleanupAfterException)
        .function("getErrorAfterException", &libFaustWasm::getErrorAfterException,
                  allow_raw_pointers())

        .function("getInfos", &libFaustWasm::getInfos, allow_raw_pointers());

    register_vector<int>("vector<int>");
}
