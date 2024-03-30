/*
 Faust project
 Copyright (C) Grame 2020
 
 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
 
 Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
 research@grame.fr
 */

#include <emscripten.h>
#include <emscripten/bind.h>

#include "adapter.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(CStruct) {
    
    value_object<FaustWasm>("FaustWasm")
        .field("cfactory", &FaustWasm::cfactory)
        .field("data", &FaustWasm::data)
        .field("json", &FaustWasm::json);
}

EMSCRIPTEN_BINDINGS(FaustModule) {
    
  emscripten::class_<libFaustWasm>("libFaustWasm")
    .constructor<>()
    .function("version",                &libFaustWasm::version, allow_raw_pointers())
    
    .function("createDSPFactory",       &libFaustWasm::createDSPFactory, allow_raw_pointers())
    .function("deleteDSPFactory",       &libFaustWasm::deleteDSPFactory, allow_raw_pointers())
    .function("deleteAllDSPFactories",  &libFaustWasm::deleteAllDSPFactories)
    
    .function("expandDSP",              &libFaustWasm::expandDSP, allow_raw_pointers())
    .function("generateAuxFiles",       &libFaustWasm::generateAuxFiles, allow_raw_pointers())
    
    .function("cleanupAfterException",  &libFaustWasm::cleanupAfterException)
    .function("getErrorAfterException", &libFaustWasm::getErrorAfterException, allow_raw_pointers())

    .function("getInfos",               &libFaustWasm::getInfos, allow_raw_pointers());

     register_vector<int>("vector<int>");
}

