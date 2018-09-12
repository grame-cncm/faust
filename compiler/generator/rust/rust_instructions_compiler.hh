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

 #ifndef _RUST_INSTRUCTION_COMPILER_H
 #define _RUST_INSTRUCTION_COMPILER_H

 #include "instructions_compiler.hh"

 class RustInstructionsCompiler : public InstructionsCompiler {
 public:
    RustInstructionsCompiler(CodeContainer* container);

private:
    StatementInst* generateInitArray(const string& vname, Typed::VarType ctype, int delay);

    StatementInst* generateShiftArray(const string& vname, int delay);

    StatementInst* generateCopyArray(const string& vname_to, const string& vname_from, int size);

 };


 #endif
