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

#if defined(LLVM_33) || defined(LLVM_34)
#include <llvm/IR/Module.h>
#else
#include <llvm/Module.h>
#endif

#include <string.h>
#include <list>

typedef struct LLVMResult {
    llvm::Module*       fModule;
    llvm::LLVMContext*  fContext;
} LLVMResult;

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
 * @return 0 on success, otherwise a non-zero error code, with an error message in error_msg.
 */
 
int compile_faust(int argc, const char* argv[], const char* name, const char* input, char* error_msg);

/**
 * Compile a Faust program and produces an LLVM module.
 * 
 * @param argc - the number of parameter in argv array
 * @param argv - the array of parameters
 * @param name - the name of the Faust program
 * @param input - the Faust program as a C string
 * @param error_msg - the error string to be filled, has to be 256 characters long
 *
 * @return a LLVMResult with a LLVM module and LLVM context on success, 0 otherwise, with an error message in error_msg.
 */

LLVMResult* compile_faust_llvm(int argc,  const char* argv[], const char* name, const char* input, char* error_msg, bool generate);

std::string expand_dsp(int argc, const char* argv[], const char* name, const char* input, char* error_msg);

std::list<std::string>& get_import_dirs();

#endif

