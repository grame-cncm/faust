/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2017-2021 GRAME, Centre National de Creation Musicale
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

#ifndef _INSTRUCTION_COMPILER1_H
#define _INSTRUCTION_COMPILER1_H

#include "instructions_compiler.hh"

// To be used with Rust and Julia backends

class InstructionsCompiler1 : public InstructionsCompiler {
   public:
    InstructionsCompiler1(CodeContainer* container);

   private:
    StatementInst* generateInitArray(const string& vname, Typed::VarType ctype, int delay);

    StatementInst* generateShiftArray(const string& vname, int delay);

    StatementInst* generateCopyArray(const string& vname_to, const string& vname_from, int size);
};

#endif
