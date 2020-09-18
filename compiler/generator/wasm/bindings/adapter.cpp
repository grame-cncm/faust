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
#include "adapter.h"

using namespace std;

static void string2StringsVector(const string& args, vector<string>& strings)
{
	string str = args;
	while (true) {
		size_t pos = str.find_first_of (' ', 0);
		if (pos == string::npos) break;
		if (pos > 1) strings.push_back(str.substr(0, pos));
		str = str.substr(pos+1, string::npos);
	}
	if (str.size()) strings.push_back(str);
}

static const char** stringVector2argv(const vector<string>& v)
{
	const char** argv = 0;
	size_t n = v.size();
	if (n) {
		argv = new const char*[n];
        for (size_t i = 0; i < v.size(); i++) {
			argv[i] = v[i].c_str();
        }
	}
	return argv;
}

FactoryOut libFaustWasm::createDSPFactory(const string name, const string dsp, const string args, bool internal_memory)
{
	vector<string> argsv;
	string2StringsVector (args, argsv);
	size_t n = argsv.size();
	cerr << "libFaustWasm::createDSPFactory " << name << " " << args;
	
	FactoryOut out;
    // 'errmsg' is actually not used: the possible error is returned in 'faustexception::gJSExceptionMsg'
	char errmsg[4096]; errmsg[0] = 0;
	if (n) {
		const char** args = stringVector2argv (argsv);
		out.module = int(::createWasmCDSPFactoryFromString (name.c_str(), dsp.c_str(), n, args, errmsg, internal_memory));
		delete [] args;
    } else {
		out.module = int(::createWasmCDSPFactoryFromString (name.c_str(), dsp.c_str(), 0, 0, errmsg, internal_memory));
    }
	
	return out;
}

ExpandOut libFaustWasm::expandDSP(const string name, const string dsp, const string args)
{
	vector<string> argsv;
	string2StringsVector (args, argsv);
	size_t n = argsv.size();
	cerr << "libFaustWasm::expandDSP " << name << " " ;
	
	ExpandOut out;
    // 'errmsg' is actually not used: the possible error is returned in 'faustexception::gJSExceptionMsg'
	char errmsg[4096]; errmsg[0] = 0;
	char sha[4096];
	if (n) {
		const char** args = stringVector2argv (argsv);
		out.dsp = ::expandCDSPFromString(name.c_str(), dsp.c_str(), n, args, sha, errmsg);
		delete [] args;
    } else {
		out.dsp = ::expandCDSPFromString(name.c_str(), dsp.c_str(), 0, 0, sha, errmsg);
    }
	out.shakey = sha;
	return out;
}

AuxOut libFaustWasm::generateAuxFiles(const string name, const string dsp, const string args)
{
	vector<string> argsv;
	string2StringsVector (args, argsv);
	size_t n = argsv.size();
	cerr << "libFaustWasm::generateAuxFiles " << name << " " ;

	AuxOut out;
    // 'errmsg' is actually not used: the possible error is returned in 'faustexception::gJSExceptionMsg'
	char errmsg[4096]; errmsg[0] = 0;
	if (n) {
		const char** args = stringVector2argv(argsv);
		out.success = ::generateCAuxFilesFromString(name.c_str(), dsp.c_str(), n, stringVector2argv (argsv), errmsg);
		delete [] args;
    } else {
		out.success = ::generateCAuxFilesFromString(name.c_str(), dsp.c_str(), 0, 0, errmsg);
    }
	return out;
}

FaustWasm libFaustWasm::getWasmModule(int mptr)
{
	FaustWasm out;
	WasmModule* module = static_cast<WasmModule*>((void*)mptr);
	if (module) {
		const char* ptr = getWasmCModule(module);
		int size = getWasmCModuleSize(module);
		for (int i = 0; i < size; i++) {
			out.data.push_back(*ptr++);
		}
	}
	return out;
}

