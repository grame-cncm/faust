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

#include "code_container.hh"
#include "dsp_factory.hh"
#include "fir_to_fir.hh"
#include "vec_code_container.hh"
#include "wasm_instructions.hh"

using namespace std;

class WASMCodeContainer : public virtual CodeContainer {
   protected:
    std::ostream*          fOut;
    BufferWithRandomAccess fBinaryOut;
    std::stringstream      fHelper;
    int                    fInternalMemory;  // Whether memory is allocated inside wasm module or JS

    DeclareFunInst* generateInstanceInitFun(const string& name, const string& obj, bool ismethod, bool isvirtual) override;
    DeclareFunInst* generateClassInit(const string& name) override;
    DeclareFunInst* generateInstanceClear(const string& name, const string& obj, bool ismethod, bool isvirtual) override;
    DeclareFunInst* generateInstanceConstants(const string& name, const string& obj, bool ismethod, bool isvirtual) override;
    DeclareFunInst* generateInstanceResetUserInterface(const string& name, const string& obj, bool ismethod,
                                                       bool isvirtual) override;

    void generateComputeAux(BlockInst* compute_block);

   public:
    WASMCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                      bool internal_memory = true);
    ~WASMCodeContainer() override = default;

    void produceClass() override;
    virtual void generateCompute() = 0;

    void                      produceInternal() override;
    dsp_factory_base* produceFactory() override;

    CodeContainer* createScalarContainer(const string& name, int sub_container_type) override;
    CodeContainer* createScalarContainer(const string& name, int sub_container_type, bool internal_memory = true);

    static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs, std::ostream* dst,
                                          bool internal_memory);
};

class WASMScalarCodeContainer : public WASMCodeContainer {
   protected:
   public:
    WASMScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                            int sub_container_type, bool internal_memory);
    ~WASMScalarCodeContainer() override = default;

    void generateCompute() override;
};

class WASMVectorCodeContainer : public VectorCodeContainer, public WASMCodeContainer {
   protected:
   public:
    WASMVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, bool internal_memory);
    ~WASMVectorCodeContainer() override = default;

    void generateCompute() override;
};
