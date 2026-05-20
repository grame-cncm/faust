/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#ifndef MOJO_CODE_CONTAINER_HH
#define MOJO_CODE_CONTAINER_HH

// faust
#include "code_container.hh"
#include "vec_code_container.hh"
#include "dsp_factory.hh"

// mojo
#include "mojo_instructions.hh"

namespace mojo {

using DspFactory = dsp_factory_base;
using TextDspFactory = text_dsp_factory_aux;

class MojoCodeContainer : public virtual CodeContainer {
protected:
    std::ostream*                  fOut;
    static inline MojoInstVisitor* fCodeProducer;
    MojoCodeContainer() = default;

public:
    MojoCodeContainer(
        std::string const& name, int numInputs, int numOutputs, std::ostream* out
    );
    virtual ~MojoCodeContainer();

    // Public Producers
    DspFactory* produceFactory()  override;
    void        produceClass()    override;
    void        produceInternal() override;

    // Factories
    CodeContainer* createScalarContainer(
        std::string const& name, int subContKind
    ) override;
    static CodeContainer* createContainer(
        std::string const& name, int numInputs, int numOutputs,
        std::ostream* out = new std::stringstream()
    );

protected:
    void writeFaustHeader();
    // void writeGlobalFunctions(int n);
    void writeClassHeaderAndFields(int n);
    void writeGlobalVariablesInlined(int n);
    void writeDefaultConstructor(int n);
    void writeGlobalVariablesInitializations(int n);
    void writeGetSampleRate(int n);
    void writeGetInputs(int n);
    void writeGetOutputs(int n);
    void writeClassInit(int n);
    void writeInstanceConstants(int n);
    void writeInstanceResetUserInterface(int n);
    void writeInstanceClear(int n);
    void writeInstanceInit(int n);
    void writeInit(int n);
    void writeInitFunctions(int n);
    void writeGetJson(int n);
    void writeMetadataFunc(int n);
    void writeBuildUserInterface(int n);

    virtual void writeCompute(int n) = 0;
};

class MojoScalarCodeContainer : public MojoCodeContainer {
public:
    MojoScalarCodeContainer(
        std::string const& name, int numInputs, int numOutputs, std::ostream* out,
        int subContKind
    );
    virtual ~MojoScalarCodeContainer();
protected:
    void writeCompute(int n) override;
};

class MojoVectorCodeContainer : public VectorCodeContainer, public MojoCodeContainer {
public:
    MojoVectorCodeContainer(
        const std::string& name, int numInputs, int numOutputs, std::ostream* out
    );
    virtual ~MojoVectorCodeContainer();
protected:
    void writeCompute(int tab) override;
};

};      // namespace mojo
#endif  // MOJO_CODE_CONTAINER_HH
