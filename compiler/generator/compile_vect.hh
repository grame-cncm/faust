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

#ifndef _COMPILE_VEC_
#define _COMPILE_VEC_

#include "compile_scal.hh"
#include "loop.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a vector C++ class
 */
///////////////////////////////////////////////////////////////////////

class VectorCompiler : public ScalarCompiler
{

public:

    VectorCompiler(const string& name, const string& super, int numInputs, int numOutputs)
        : ScalarCompiler(name,super,numInputs,numOutputs)
        {}
    
    VectorCompiler(Klass* k) : ScalarCompiler(k)
    {}
    virtual void compileMultiSignal(Tree L);

protected:

    virtual string      CS(Tree sig);
    virtual string      generateCode(Tree sig);
    virtual void        generateCodeRecursions(Tree sig);
    virtual string      generateCodeNonRec(Tree sig);
    virtual string      generateLoopCode(Tree sig);

    virtual string      generateCacheCode(Tree sig, const string& exp);
    virtual void        generateDelayLine(const string& ctype, const string& vname, int mxd, const string& exp, const string& ccs);
    virtual string      generateVariableStore(Tree sig, const string& exp);
    virtual string      generateFixDelay(Tree sig, Tree exp, Tree delay);
    virtual string      generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
    virtual void        vectorLoop(const string& tname, const string& dlname, const string& cexp, const string& ccs);
    virtual void        dlineLoop( const string& tname, const string& dlname, int delay, const string& cexp, const string& ccs);
    virtual string      generateWaveform(Tree sig);

    bool    needSeparateLoop(Tree sig);
    
};

#endif
