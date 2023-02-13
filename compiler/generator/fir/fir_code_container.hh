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

#ifndef _FIR_CODE_CONTAINER_H
#define _FIR_CODE_CONTAINER_H

#ifdef WIN32
#pragma warning(disable : 4250)
#endif

#include "code_container.hh"
#include "fir_instructions.hh"
#include "omp_code_container.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"

class FIRCodeContainer : public virtual CodeContainer {
   private:
    void dumpGlobalsAndInit(FIRInstVisitor& firvisitor, std::ostream* dst);
    void dumpUserInterface(FIRInstVisitor& firvisitor, std::ostream* dst);
    void dumpSubContainers(FIRInstVisitor& firvisitor, std::ostream* dst);

    virtual void dumpThread(FIRInstVisitor& firvisitor, std::ostream* dst){};
    virtual void dumpComputeBlock(FIRInstVisitor& firvisitor, std::ostream* dst);
    virtual void dumpCompute(FIRInstVisitor& firvisitor, std::ostream* dst) = 0;
    virtual void dumpPostCompute(FIRInstVisitor& firvisitor, std::ostream* dst);
    virtual void dumpMemory(std::ostream* dst);
    virtual void dumpFlatten(std::ostream* dst);

    std::ostream* fOut;

   protected:
    FIRCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* dst, bool top_level)
    {
        fTopLevel  = top_level;
        fKlassName = name;
        fOut       = dst;
        initialize(numInputs, numOutputs);
    }

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);
    void           produceInternal();
    void           produceClass();

    virtual dsp_factory_base* produceFactory();

    bool fTopLevel;

   public:
    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* dst,
                                          bool top_level = false);
};

class FIRScalarCodeContainer : public FIRCodeContainer {
   private:
    virtual void dumpCompute(FIRInstVisitor& firvisitor, std::ostream* dst);

   public:
    FIRScalarCodeContainer(const std::string& name, int numInputs, int numOutputs, int sub_container_type, std::ostream* dst, bool top_level)
        : FIRCodeContainer(name, numInputs, numOutputs, dst, top_level)
    {
        fSubContainerType = sub_container_type;
    }
};

class FIRVectorCodeContainer : public VectorCodeContainer, public FIRCodeContainer {
   private:
    virtual void dumpCompute(FIRInstVisitor& firvisitor, std::ostream* dst);

   public:
    FIRVectorCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* dst, bool top_level)
        : VectorCodeContainer(numInputs, numOutputs), FIRCodeContainer(name, numInputs, numOutputs, dst, top_level)
    {
    }
};

class FIROpenMPCodeContainer : public OpenMPCodeContainer, public FIRCodeContainer {
   private:
    virtual void dumpCompute(FIRInstVisitor& firvisitor, std::ostream* dst);

   public:
    FIROpenMPCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* dst, bool top_level)
        : OpenMPCodeContainer(numInputs, numOutputs), FIRCodeContainer(name, numInputs, numOutputs, dst, top_level)
    {
    }
};

class FIRWorkStealingCodeContainer : public WSSCodeContainer, public FIRCodeContainer {
   private:
    virtual void dumpCompute(FIRInstVisitor& firvisitor, std::ostream* dst);
    virtual void dumpThread(FIRInstVisitor& firvisitor, std::ostream* dst);
    virtual void dumpMemory(std::ostream* dst);

   public:
    FIRWorkStealingCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* dst, bool top_level)
        : WSSCodeContainer(numInputs, numOutputs, "this"), FIRCodeContainer(name, numInputs, numOutputs, dst, top_level)
    {
    }
};

#endif
