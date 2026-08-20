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

#ifndef _ASSEMBLYSCRIPT_CODE_CONTAINER_H
#define _ASSEMBLYSCRIPT_CODE_CONTAINER_H

#include "assemblyscript_instructions.hh"
#include "code_container.hh"
#include "dsp_factory.hh"
#include "vec_code_container.hh"

#ifdef _WIN32
#pragma warning(disable : 4250)
#endif

// AssemblyScript backend container.
//
// Particularities versus most backends:
// - currently scalar-only in practice (vector/scheduler/openmp are rejected in createContainer)
// - emits an experimental class-shaped ABI for generated DSP code
// - relies on explicit init methods (classInit/init/instanceInit) instead of constructor emission
class AssemblyScriptCodeContainer : public virtual CodeContainer {
   protected:
    std::ostream* fOut;

    virtual void produceClass();

    void produceMetadata(int tabs);

    virtual void produceInternal();

   public:
    AssemblyScriptCodeContainer() {}
    AssemblyScriptCodeContainer(const std::string& name, int numInputs, int numOutputs,
                                std::ostream* out);

    virtual ~AssemblyScriptCodeContainer()
    {
        // fCodeProducer is a 'Garbageable', so nothing to delete
    }

    virtual void generateCompute(int tab) = 0;

    virtual dsp_factory_base* produceFactory();

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs,
                                          std::ostream* dst = new std::stringstream());
};

// Used in -scalar (= default) mode
class AssemblyScriptScalarCodeContainer : public AssemblyScriptCodeContainer {
   protected:
   public:
    AssemblyScriptScalarCodeContainer() {}
    AssemblyScriptScalarCodeContainer(const std::string& name, int numInputs, int numOutputs,
                                      std::ostream* out, int sub_container_type);
    virtual ~AssemblyScriptScalarCodeContainer() {}

    void generateCompute(int n);
};

#endif
