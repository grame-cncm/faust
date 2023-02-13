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

#ifndef _FAUST_EXCEPTION_
#define _FAUST_EXCEPTION_

#include <iostream>
#include <sstream>
#include <stdexcept>
#ifndef WIN32
#include <unistd.h>
#else
//#include <io.h>
#endif

#if !defined(EMCC) && !defined(WIN32) && !defined(ANDROID) && !defined(ALPINE)
#include <execinfo.h>
#endif

class faustexception : public std::runtime_error {
   public:
#ifdef EMCC
    static const char* gJSExceptionMsg;

    faustexception(const std::string& msg = "") : std::runtime_error(msg) { gJSExceptionMsg = strdup(msg.c_str()); }
    faustexception(char* msg) : std::runtime_error(msg) { gJSExceptionMsg = strdup(msg); }
    faustexception(const char* msg) : std::runtime_error(msg) { gJSExceptionMsg = strdup(msg); }
#else
    faustexception(const std::string& msg = "") : std::runtime_error(msg) {}
    faustexception(char* msg) : std::runtime_error(msg) {}
    faustexception(const char* msg) : std::runtime_error(msg) {}
#endif

    std::string Message() { return what(); }

    void PrintMessage() { std::cerr << what(); }
};

inline void stacktrace(std::stringstream& str, int val)
{
#if !defined(EMCC) && !defined(WIN32) && !defined(ANDROID) && !defined(ALPINE)
    void*  callstack[val];
    int    frames = backtrace(callstack, val);
    char** strs   = backtrace_symbols(callstack, frames);
    str << "====== stack trace start ======\n";
    for (int i = 0; i < frames; ++i) {
        str << strs[i] << "\n";
    }
    str << "====== stack trace stop ======\n";
    free(strs);
#endif
}

#define faustassert(cond) faustassertaux((cond), __FILE__, __LINE__)
void faustassertaux(bool cond, const std::string& file, int line);

#endif
