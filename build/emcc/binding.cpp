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
	
	value_object<FactoryOut>("FactoryOut")
		.field("module",   &FactoryOut::module)
		.field("error",    &FactoryOut::error);

	value_object<ExpandOut>("ExpandOut")
		.field("dsp",    &ExpandOut::dsp)
		.field("shakey", &ExpandOut::shakey)
		.field("error",  &ExpandOut::error);

	
	value_object<AuxOut>("AuxOut")
		.field("success",  	&AuxOut::success)
		.field("error",  	&AuxOut::error);
}

/*
 * C functions binding.
 * These functions can be used on javascript side.
 */
EMSCRIPTEN_BINDINGS(FaustModule) {

	// this is the old C interface
//	emscripten::function("createWasmCDSPFactoryFromString", &createWasmCDSPFactoryFromString, allow_raw_pointers());
//	emscripten::function("expandCDSPFromString", 			&expandCDSPFromString, allow_raw_pointers());
//	emscripten::function("deleteAllWasmCDSPFactories", 		&deleteAllWasmCDSPFactories);
//	emscripten::function("getCLibFaustVersion", 			&getCLibFaustVersion, allow_raw_pointers());
//	emscripten::function("getWasmCModule", 					&getWasmCModule, allow_raw_pointers());
//	emscripten::function("getWasmCModuleSize", 				&getWasmCModuleSize, allow_raw_pointers());
//	emscripten::function("getWasmCHelpers", 				&getWasmCHelpers, allow_raw_pointers());
//	emscripten::function("freeWasmCModule", 				&freeWasmCModule, allow_raw_pointers());
//	emscripten::function("freeCMemory", 					&freeCMemory, allow_raw_pointers());
//	emscripten::function("cleanupAfterException", 			&cleanupAfterException);
//	emscripten::function("getErrorAfterException", 			&getErrorAfterException, allow_raw_pointers());
//	emscripten::function("generateCAuxFilesFromString", 	&generateCAuxFilesFromString, allow_raw_pointers());

	emscripten::class_<libFaustWasm>("libFaustWasm")
			.constructor<>()
			.function("version", 				&libFaustWasm::version, allow_raw_pointers())

			.function("createDSPFactory", 		&libFaustWasm::createDSPFactory, allow_raw_pointers())
			.function("expandDSP", 				&libFaustWasm::expandDSP, allow_raw_pointers())
			.function("generateAuxFiles", 		&libFaustWasm::generateAuxFiles, allow_raw_pointers())
			.function("deleteAllDSPFactories", 	&libFaustWasm::deleteAllDSPFactories)
			
			.function("getWasmModule", 			&libFaustWasm::getWasmModule, allow_raw_pointers())
			.function("getWasmModuleSize", 		&libFaustWasm::getWasmModuleSize, allow_raw_pointers())
			.function("getWasmHelpers", 		&libFaustWasm::getWasmHelpers, allow_raw_pointers())

			.function("freeWasmModule", 		&libFaustWasm::freeWasmModule, allow_raw_pointers())
			.function("freeMemory", 			&libFaustWasm::freeMemory, allow_raw_pointers())
			.function("cleanupAfterException", 	&libFaustWasm::cleanupAfterException)
			.function("getErrorAfterException", &libFaustWasm::getErrorAfterException, allow_raw_pointers());
}

