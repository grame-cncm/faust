/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

#ifndef _FBC_YDSP_COMPILER_H
#define _FBC_YDSP_COMPILER_H

#include "fbc_executor.hh"
#include "interpreter_bytecode.hh"

/*
 FBC -> YDSP compiler: the 'compute' DSP block of a factory, translated to the typed IR of YDSP (the DSP
 language of the YUP library) and compiled to x86-64 or AArch64 machine code by YDSP's asmjit code generator.

 This is a measurement prototype (phase 0 of ANALYSE_YDSP_JIT.md at the root of the repository). The YDSP headers
 need C++20 while libfaust is C++17, so the compiler is not in libfaust: it is defined in a separate C++20 unit,
 tests/interp-tests/interp-ydsp/fbc_ydsp_compiler.cpp, that the program linking a libfaust built with
 INTERP_COMP and INTERP_YDSP_BUILD must link too. Only this declaration is seen by libfaust.

 Returns nullptr when the block is not compiled; the interpreter then keeps running it.
 count_offset is the int heap offset where the interpreter stores the 'count' of compute().
*/
template <class REAL>
FBCExecuteFun<REAL>* createFBCYdspCompiler(FBCBlockInstruction<REAL>* block, soundTable& sound_table,
                                           int count_offset);

#endif
