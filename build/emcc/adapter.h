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

#include "libfaust.h"
#include "export.hh"
#include "wasm_dynamic_dsp_aux.hh"

using namespace std;

struct FactoryOut {
	int module = 0;
	std::string error;
};

struct ExpandOut {
	std::string dsp;
	std::string shakey;
	std::string error;
};

struct AuxOut {
	bool success;
	std::string error;
};

class libFaustWasm
{
	public:
				 libFaustWasm() {};
		virtual ~libFaustWasm() {};

		std::string		version()							{ return ::getCLibFaustVersion(); }
		FactoryOut		createDSPFactory 	(const std::string name, const std::string dsp, const std::string args, bool internal_memory);
		ExpandOut 		expandDSP 			(const std::string name, const std::string dsp, const std::string args);
		AuxOut 			generateAuxFiles	(const std::string name, const std::string dsp, const std::string args);

		void			deleteAllDSPFactories() 			{ ::deleteAllWasmCDSPFactories(); }

		std::string		getWasmModule 		(int module)	{ return getWasmCModule (static_cast<WasmModule*>((void*)module)); }
		int 			getWasmModuleSize	(int module)	{ return getWasmCModuleSize (static_cast<WasmModule*>((void*)module)); }
		std::string		getWasmHelpers		(int module)	{ return getWasmCHelpers (static_cast<WasmModule*>((void*)module)); }

		void			freeWasmModule		(int module) 	{ ::freeWasmCModule(static_cast<WasmModule*>((void*)module)); }
		void			freeMemory( void* ptr ) 			{ ::freeCMemory (ptr); }
		void			cleanupAfterException() 			{ ::cleanupAfterException(); }
		std::string		getErrorAfterException ()			{ return ::getErrorAfterException(); }
};

//-----------------------------------------------------------------
// list of changes regarding the previous C interface
//
//"createWasmCDSPFactoryFromString" -> libFaustWasm::createDSPFactory
//"expandCDSPFromString" 			-> libFaustWasm::expandDSP
//"deleteAllWasmCDSPFactories" 		-> libFaustWasm::deleteAllDSPFactories
//"getCLibFaustVersion" 			-> libFaustWasm::version
//"getWasmCModule" 					-> libFaustWasm::getWasmModule
//"getWasmCModuleSize" 				-> libFaustWasm::getWasmCModuleSize
//"getWasmCHelpers" 				-> libFaustWasm::getWasmCHelpers
//"freeWasmCModule" 				-> libFaustWasm::freeWasmModule
//"freeCMemory" 					-> libFaustWasm::freeMemory
//"cleanupAfterException" 			-> libFaustWasm::cleanupAfterException
//"getErrorAfterException" 			-> libFaustWasm::getErrorAfterException
//"generateCAuxFilesFromString" 	-> libFaustWasm::generateAuxFiles


