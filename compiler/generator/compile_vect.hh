/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef _COMPILE_VEC_
#define _COMPILE_VEC_

#include "compile_scal.hh"
#include "loop.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a vector C++ class
 */
///////////////////////////////////////////////////////////////////////

class VectorCompiler : public ScalarCompiler {
   public:
    VectorCompiler(const std::string& name, const std::string& super, int numInputs, int numOutputs)
        : ScalarCompiler(name, super, numInputs, numOutputs)
    {
    }

    VectorCompiler(Klass* k) : ScalarCompiler(k) {}
    virtual void compileMultiSignal(Tree L);

   protected:
    virtual std::string CS(Tree sig);
    virtual std::string generateCode(Tree sig);
    virtual void   generateCodeRecursions(Tree sig);
    virtual std::string generateCodeNonRec(Tree sig);
    virtual std::string generateLoopCode(Tree sig);

    virtual std::string generateCacheCode(Tree sig, const std::string& exp);
    virtual void   generateDelayLine(const std::string& ctype, const std::string& vname, int mxd, const std::string& exp,
                                     const std::string& ccs);
    virtual std::string generateVariableStore(Tree sig, const std::string& exp);
    virtual std::string generateDelayAccess(Tree sig, Tree exp, Tree delay);
    virtual std::string generateDelayVec(Tree sig, const std::string& exp, const std::string& ctype, const std::string& vname, int mxd);
    virtual void   generateVectorLoop(const std::string& tname, const std::string& dlname, const std::string& cexp, const std::string& ccs);
    virtual void   generateDlineLoop(const std::string& tname, const std::string& dlname, int delay, const std::string& cexp,
                                     const std::string& ccs);
    virtual std::string generateWaveform(Tree sig);

    bool needSeparateLoop(Tree sig);
};

#endif
