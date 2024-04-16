/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2017-2021 GRAME, Centre National de Creation Musicale
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

#ifndef _INSTRUCTION_COMPILER1_H
#define _INSTRUCTION_COMPILER1_H

#include "instructions_compiler.hh"

// To be used with Rust and Julia backends

class InstructionsCompiler1 : public InstructionsCompiler {
   public:
    InstructionsCompiler1(CodeContainer* container): InstructionsCompiler(container)
    {}

   private:
    StatementInst* generateInitArray(const std::string& vname, BasicTyped* ctype, int delay) override;
    StatementInst* generateShiftArray(const std::string& vname, int delay) override;
    StatementInst* generateCopyArray(const std::string& vname_to, const std::string& vname_from, int size) override;
};

#endif
