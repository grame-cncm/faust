/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <string>
#include <vector>

#include "faust/export.h"

/*
    Global outside of the global context, compiled here
    to be defined in libfaust and libfaustmachine libraries.
*/
std::vector<std::string> gWarningMessages;
bool                     gAllWarning = false;

// External libfaust API

extern "C" LIBFAUST_API const char* getCLibFaustVersion()
{
#ifdef LLVM_BUILD
    static std::string version =
        std::string(FAUSTVERSION) + " (LLVM " + std::string(LLVM_VERSION) + ")";
    return version.c_str();
#else
    return FAUSTVERSION;
#endif
}

/*
 Regular C++ exceptions are deactivated when compiled with 'emcc' since adding
 them (using Emscripten runtime mechanism) practically doubles the size of the generated wasm
 library.

 A 'light' exception handling model is used:

 - C++ 'throw' is actually catched by the Emscripten runtime 'catch_throw' and the exception
 error message is kept in the global faustexception::gJSExceptionMsg variable
 - a regular JS exception is triggered and catched on JS side
 - the actual exception message is retrieved on JS side using 'getErrorAfterException'
 - and finally global context cleanup is done from JS side using 'cleanupAfterException'
 */

#ifdef EMCC
#include "exception.hh"

const char* faustexception::gJSExceptionMsg = nullptr;

// The message is null whenever the failure was not a faustexception : an abort,
// or -- far more often -- an error raised on the JS side after this call returned,
// such as WebAssembly.compile() refusing the module just generated. Reading it as a
// string was undefined behaviour that LOOKED deliberate : Emscripten's assertion
// build writes the null-pointer canary "emsc" at address 0, so std::string(nullptr)
// read back exactly the value the test compared against, and every such failure was
// reported as "ERROR : stack overflow". Saying nothing lets the JS side rethrow the
// exception it actually caught, which names the real cause -- a genuine stack
// exhaustion included, since the runtime's own message says so.
extern "C" LIBFAUST_API const char* getErrorAfterException()
{
    return (faustexception::gJSExceptionMsg) ? faustexception::gJSExceptionMsg : "";
}
#endif

#if defined(EMCC) && defined(FAUST_LIB)
#include "global.hh"

extern "C" LIBFAUST_API void cleanupAfterException()
{
    global::destroy();
}

#endif
