/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2017 GRAME, Centre National de Creation Musicale
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

#ifndef _RUST_CODE_CONTAINER_H
#define _RUST_CODE_CONTAINER_H

#include "code_container.hh"
#include "dsp_factory.hh"
#include "omp_code_container.hh"
#include "rust_instructions.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"

#ifdef WIN32
#pragma warning(disable : 4250)
#endif

class RustCodeContainer : public virtual CodeContainer {
   protected:
    RustInstVisitor fCodeProducer;
    std::ostream*   fOut;

    void produceMetadata(int tabs);

    virtual void printHeader() { CodeContainer::printHeader(*fOut); }

   public:
    RustCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out)
        : fCodeProducer(out, name), fOut(out)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;
    }
    virtual ~RustCodeContainer() {}

    virtual void              produceClass();
    virtual void              generateCompute(int tab) = 0;
    void                      produceInternal();
    virtual dsp_factory_base* produceFactory();
    virtual void produceInfoFunctions(int tabs, const std::string& classname, const std::string& obj, bool ismethod,
                                      FunTyped::FunAttribute funtype, TextInstVisitor* producer);
    virtual void produceParameterGetterSetter(int tabs, std::map<std::string, int> parameterLookup);

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);
    CodeContainer* createVectorContainer(const std::string& name, int sub_container_type);

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs,
                                          std::ostream* dst = new std::stringstream());
};

class RustScalarCodeContainer : public RustCodeContainer {
   protected:
   public:
    RustScalarCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out,
                            int sub_container_type);
    virtual ~RustScalarCodeContainer() {}

    void generateCompute(int tab);
};

class RustVectorCodeContainer : public VectorCodeContainer, public RustCodeContainer {
   protected:
   public:
    RustVectorCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~RustVectorCodeContainer() {}

    void generateCompute(int n);
    BlockInst* generateDAGLoopVariant0(const std::string& counter) override;
};

class RustOpenMPCodeContainer : public OpenMPCodeContainer, public RustCodeContainer {
   protected:
   public:
    RustOpenMPCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~RustOpenMPCodeContainer() {}

    void generateCompute(int tab);
};

class RustWorkStealingCodeContainer : public WSSCodeContainer, public RustCodeContainer {
   protected:
   public:
    RustWorkStealingCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~RustWorkStealingCodeContainer() {}

    void generateCompute(int tab);
};

#endif
