/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#pragma once

#include "instructions_compiler.hh"

class DAGInstructionsCompiler : public InstructionsCompiler {
   public:
    DAGInstructionsCompiler(CodeContainer* container);

    void compileMultiSignal(Tree sig) override;

   private:
    // reimplemented code generation methods
    ValueInst* CS(Tree sig) override;
    ValueInst* generateCode(Tree sig) override;
    virtual void       generateCodeRecursions(Tree sig);
    virtual ValueInst* generateCodeNonRec(Tree sig);
    virtual ValueInst* generateLoopCode(Tree sig);

    ValueInst* generateWaveform(Tree sig) override;

    void generateVectorLoop(Typed::VarType ctype, const string& vecname, ValueInst* exp,
                            Address::AccessType& var_access);
    void generateDlineLoop(Typed::VarType ctype, const string& vecname, int delay, ValueInst* exp,
                           Address::AccessType& var_access);

    ValueInst* generateVariableStore(Tree sig, ValueInst* inst) override;
    ValueInst* generateCacheCode(Tree sig, ValueInst* inst) override;
    ValueInst* generateInput(Tree sig, int idx) override;

    ValueInst* generateFixDelay(Tree sig, Tree arg, Tree size) override;
    ValueInst* generateDelayVec(Tree sig, ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd) override;
    ValueInst* generateDelayLine(ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd,
                                         Address::AccessType& var_access) override;

    StatementInst* generateCopyBackArray(const string& vname_to, const string& vname_from, int size);

    // private helper functions
    bool needSeparateLoop(Tree sig);
};
