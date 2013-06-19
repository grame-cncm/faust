/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#if defined(LLVM_33)
#include <llvm/IR/Module.h>
#else
#include <llvm/Module.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct LLVMResult {
    llvm::Module*       fModule;
    llvm::LLVMContext*  fContext;
} LLVMResult;

/**
 * Compile a Faust program.
 * 
 * @param argc - the number of parameter in argv array
 * @param argv - the array of parameters
 * @param library_path - Faust library path : if null, the default localization mechanism will be used
 * @param draw_path - the place where to put output files like SVG, ps, dot...
 * @param name - the name of the Faust program
 * @param input - the Faust program as a string
 * @param error_msg - the error string to be filled, has to be 256 characters long
 *
 * @return 0 on success, otherwise a non-zero error code, with an error message in error_msg.
 */
 
int compile_faust(int argc, const char* argv[], const char* library_path, const char* draw_path, const char* name, const char* input, char* error_msg);

/**
 * Compile a Faust program and produces an LLVM module.
 * 
 * @param argc - the number of parameter in argv array
 * @param argv - the array of parameters
 * @param library_path - Faust library path : if null, the default localization mechanism will be used
 * @param draw_path - the place where to put ouput files like SVG, ps, dot...
 * @param name - the name of the Faust program
 * @param input - the Faust program as a C string
 * @param error_msg - the error string to be filled, has to be 256 characters long
 *
 * @return a LLVMResult with a LLVM module and LLVM context on success, O otherwise, with an error message in error_msg.
 */

LLVMResult* compile_faust_llvm(int argc,  const char* argv[], const char* library_path, const char* draw_path, const char* name, const char* input, char* error_msg);

#ifdef __cplusplus
}
#endif

#endif

