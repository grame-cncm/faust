/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2017 GRAME, Centre National de Creation Musicale
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

#ifndef _RUST_CODE_CONTAINER_H
#define _RUST_CODE_CONTAINER_H

#include "code_container.hh"
#include "dsp_factory.hh"
#include "omp_code_container.hh"
#include "rust_instructions.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"

using namespace std;

#ifdef WIN32
#pragma warning(disable : 4250)
#endif

class RustCodeContainer : public virtual CodeContainer {
   protected:
    RustInstVisitor fCodeProducer;
    std::ostream*   fOut;

    void produceMetadata(int tabs);

   public:
    RustCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
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

    CodeContainer* createScalarContainer(const string& name, int sub_container_type);

    static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs,
                                          ostream* dst = new stringstream());
};

class RustScalarCodeContainer : public RustCodeContainer {
   protected:
   public:
    RustScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                            int sub_container_type);
    virtual ~RustScalarCodeContainer();

    void generateCompute(int tab);
};

class RustVectorCodeContainer : public VectorCodeContainer, public RustCodeContainer {
   protected:
   public:
    RustVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~RustVectorCodeContainer();

    void generateCompute(int n);
};

class RustOpenMPCodeContainer : public OpenMPCodeContainer, public RustCodeContainer {
   protected:
   public:
    RustOpenMPCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~RustOpenMPCodeContainer();

    void generateCompute(int tab);
};

class RustWorkStealingCodeContainer : public WSSCodeContainer, public RustCodeContainer {
   protected:
   public:
    RustWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~RustWorkStealingCodeContainer();

    void generateCompute(int tab);
};

#endif
