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

#ifndef _COMPILE_SCHED_
#define _COMPILE_SCHED_

#include "compile_vect.hh"
#include "loop.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a vector C++ class
 */
///////////////////////////////////////////////////////////////////////

class SchedulerCompiler : public VectorCompiler {
   public:
    SchedulerCompiler(const std::string& name, const std::string& super, int numInputs, int numOutputs)
        : VectorCompiler(name, super, numInputs, numOutputs)
    {
    }

    SchedulerCompiler(Klass* k) : VectorCompiler(k) {}
    virtual void compileMultiSignal(Tree L);

   protected:
    virtual void vectorLoop(const std::string& tname, const std::string& dlname, const std::string& cexp, const std::string& ccs);
    virtual void dlineLoop(const std::string& tname, const std::string& dlname, int delay, const std::string& cexp, const std::string& ccs);
};

#endif
