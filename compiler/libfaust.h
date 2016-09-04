/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2012-2013 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef __LIB_FAUST__
#define __LIB_FAUST__

#include <string>
#include <vector>
#include "export.hh"

#define LVVM_BACKEND_NAME "Faust LLVM backend"
#define COMPILATION_OPTIONS_KEY "compilation_options"
#define COMPILATION_OPTIONS "declare compilation_options    "

#define FAUSTVERSION "2.0.a47"

class dsp_factory_base;

/*
    Low level dynamic compilation interface. Better use the public API defined in llvm-dsp.h or llvm-c-dsp.h
*/

/**
 * Compile a Faust program.
 *
 * @param argc - the number of parameter in argv array
 * @param argv - the array of parameters
 * @param name - the name of the Faust program
 * @param input - the Faust program as a string
 * @param error_msg - the error string to be filled, has to be 256 characters long
 *
 * @return true on success, otherwise false with an error message in error_msg.
 */

EXPORT bool compile_faust(int argc, const char* argv[], const char* name, const char* input, std::string& error_msg, bool generate);

/**
 * Compile a Faust program and produces a factory.
 *
 * @param argc - the number of parameter in argv array
 * @param argv - the array of parameters
 * @param name - the name of the Faust program
 * @param input - the Faust program as a C string
 * @param error_msg - the error string to be filled, has to be 256 characters long
 *
 * @return a factory on success, 0 otherwise, with an error message in error_msg.
 */

EXPORT dsp_factory_base* compile_faust_factory(int argc, const char* argv[], const char* name, const char* input, std::string& error_msg);

EXPORT std::string expand_dsp(int argc, const char* argv[], const char* name, const char* input, std::string& sha_key, std::string& error_msg);

#endif
