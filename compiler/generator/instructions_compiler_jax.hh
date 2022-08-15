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

#ifndef _INSTRUCTION_COMPILER_JAX_H
#define _INSTRUCTION_COMPILER_JAX_H

#include "instructions_compiler.hh"

// To be used with JAX backend

class InstructionsCompilerJAX : public InstructionsCompiler {
   public:
    InstructionsCompilerJAX(CodeContainer* container): InstructionsCompiler(container)
    {}

    ValueInst* generateDelay(Tree sig, Tree exp, Tree delay) override;
    ValueInst* generateRecProj(Tree sig, Tree r, int i) override;
    ValueInst* generateRec(Tree sig, Tree var, Tree le, int index) override;
    ValueInst* generateDelayLine(ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd,
                                                   Address::AccessType& var_access, ValueInst* ccs) override;

	StatementInst* generateShiftArray(const string& vname, int delay) override;
    StatementInst* generateCopyArray(const string& vname, int index_from, int index_to);

	StoreVarInst* genStoreArrayStructVar(const string& vname, int index, ValueInst* exp);

    void ensureIotaCode();

	ValueInst* generateSoundfile(Tree sig, Tree path);
};

#endif
