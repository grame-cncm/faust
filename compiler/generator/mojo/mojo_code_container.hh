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

/** @file compiler/generator/mojo/mojo_code_container.hh **/

#ifndef MOJO_CODE_CONTAINER_HH
#define MOJO_CODE_CONTAINER_HH

// faust
#include "code_container.hh"
#include "dsp_factory.hh"
#include "vec_code_container.hh"

// mojo
#include "mojo_instructions.hh"

inline namespace mojo {

using DspFactory = dsp_factory_base;
using TextDspFactory = text_dsp_factory_aux;

inline MojoInstVisitor* gScalarProducer;
inline MojoVecInstVisitor* gVectorProducer;

/**
    A `MojoCodeContainer` is an abstract code container for the mojo backend.
    @desc
    - Provides the common code generation structure for mojo DSP classes.
    - An instance is created with a DSP class name, input/output count and
      an `output` stream.
    - Allows to produce a DSP factory, the generated class and the internal
      declarations required by the backend.
    - Allows to create scalar mojo code containers from an existing container.
    - Allows to produce the fundamental `compute` method of the generated DSP.
    @rep
    - Maintains an `out` stream to write the generated mojo code to.
    @glob
    - Maintains a `code producer` visitor used to translate Faust IR
      instructions into mojo code.
    - Allows to create a mojo code container from the DSP name, input/output
      count and output stream.
**/
class MojoCodeContainer : public virtual CodeContainer {
protected:
    OStream* fOut;
    MojoCodeContainer() = default;

public:
    MojoCodeContainer(String const& name, int numInputs, int numOutputs, OStream* out);
    virtual ~MojoCodeContainer();

    // Public producers
    DspFactory* produceFactory()  override;
    void        produceClass()    override;
    void        produceInternal() override;

    // Factories
    CodeContainer*        createScalarContainer(String const& name, int subContKind) override;
    static CodeContainer* createContainer(String const& name, int numInputs, int numOutputs,
                                          OStream* out = new OString());

protected:
    // Writers
    void writeFaustHeader();
    void writeDRealDefinitions();
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

/**
    A `MojoScalarCodeContainer` is a `MojoCodeContainer` for scalar mojo code
    generation.
    @desc
    - Provides the scalar code generation path for mojo DSP classes.
    - An instance is created with a DSP class name, input/output count,
      an `output` stream and a scalar sub-container kind.
    - Allows to produce the scalar version of the generated Faust DSP class.
    - Allows to produce the scalar `compute` method of the generated DSP.
**/
class MojoScalarCodeContainer : public MojoCodeContainer {
public:
    MojoScalarCodeContainer(String const& name, int numInputs, int numOutputs,
                            OStream* out, int subContKind);
    virtual ~MojoScalarCodeContainer();
protected:
    void writeCompute(int n) override;
};

/**
    A `MojoVecCodeContainer` is both a `VectorCodeContainer` and a
    `MojoCodeContainer` for the mojo backend when the `-vec` option is enabled.
    @desc
    - Provides the vector code generation path for mojo DSP classes.
    - An instance is created with a DSP class name, input/output count and
      an `output` stream.
    - Allows to produce the vectorized version of the generated Faust DSP class.
    - Allows to produce the vector `compute` method of the generated DSP.
**/
class MojoVecCodeContainer : public VectorCodeContainer, public MojoCodeContainer {
public:
    MojoVecCodeContainer(const String& name, int numInputs, int numOutputs, OStream* out);
    virtual ~MojoVecCodeContainer();
protected:
    void writeCompute(int tab) override;
};

};      // namespace mojo
#endif  // MOJO_CODE_CONTAINER_HH
