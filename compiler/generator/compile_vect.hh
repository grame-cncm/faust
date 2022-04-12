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

#include "compile_scal.hh"
#include "loop.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a vector C++ class
 */
///////////////////////////////////////////////////////////////////////

class VectorCompiler : public ScalarCompiler {
   public:
    VectorCompiler(const string& name, const string& super, int numInputs, int numOutputs)
        : ScalarCompiler(name, super, numInputs, numOutputs)
    {
    }

    VectorCompiler(Klass* k) : ScalarCompiler(k) {}
    void compileMultiSignal(Tree L) override;

   protected:
    string         CS(Tree sig) override;
    string         generateCode(Tree sig) override;
    virtual void   generateCodeRecursions(Tree sig);
    virtual string generateCodeNonRec(Tree sig);
    virtual string generateLoopCode(Tree sig);

    string       generateCacheCode(Tree sig, const string& exp) override;
    void         generateDelayLine(const string& ctype, const string& vname, int mxd, const string& exp, const string& ccs) override;
    string       generateVariableStore(Tree sig, const string& exp) override;
    string       generateFixDelay(Tree sig, Tree exp, Tree delay) override;
    string       generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd) override;
    virtual void generateVectorLoop(const string& tname, const string& dlname, const string& cexp, const string& ccs);
    virtual void generateDlineLoop(const string& tname, const string& dlname, int delay, const string& cexp, const string& ccs);
    string       generateWaveform(Tree sig) override;

    bool needSeparateLoop(Tree sig);
};
