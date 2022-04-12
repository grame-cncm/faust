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
#include "cpp_instructions.hh"
#include "dsp_factory.hh"
#include "omp_code_container.hh"
#include "opencl_instructions.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"

#ifdef WIN32
#pragma warning(disable : 4250)
#endif

using namespace std;

class CPPCodeContainer : public virtual CodeContainer {
   protected:
    CPPInstVisitor fCodeProducer;
    std::ostream*  fOut;
    string         fSuperKlassName;

    void produceMetadata(int tabs);
    void produceInit(int tabs);

   public:
    CPPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
        : fCodeProducer(out), fOut(out), fSuperKlassName(super)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;

        // For mathematical functions
        if (gGlobal->gFastMath) {
            addIncludeFile((gGlobal->gFastMathLib == "def") ? "\"faust/dsp/fastmath.cpp\"" : ("\"" + gGlobal->gFastMathLib + "\""));
        } else {
            addIncludeFile("<cmath>");
            addIncludeFile("<algorithm>");
        }
    }

    ~CPPCodeContainer() override = default;

    void         produceClass() override;
    virtual void generateCompute(int tab) = 0;
    void         produceInternal() override;

    dsp_factory_base* produceFactory() override;

    void printHeader() override
    {
        CodeContainer::printHeader(*fOut);

        tab(0, *fOut);
        *fOut << "#ifndef  __" << gGlobal->gClassName << "_H__";
        tab(0, *fOut);
        *fOut << "#define  __" << gGlobal->gClassName << "_H__" << std::endl << std::endl;
    }

    void printFloatDef() override { printfloatdef(*fOut, (gGlobal->gFloatSize == 3)); }

    void printFooter() override
    {
        tab(0, *fOut);
        *fOut << "#endif" << std::endl;
    }

    CodeContainer* createScalarContainer(const string& name, int sub_container_type) override;

    static CodeContainer* createContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                          ostream* dst = new stringstream());
};

class CPPScalarCodeContainer : public CPPCodeContainer {
   protected:
   public:
    CPPScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out,
                           int sub_container_type);
    ~CPPScalarCodeContainer() override;

    void generateCompute(int tab) override;
};

class CPPVectorCodeContainer : public VectorCodeContainer, public CPPCodeContainer {
   protected:
   public:
    CPPVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
    ~CPPVectorCodeContainer() override;

    void generateCompute(int tab) override;
};

class CPPOpenMPCodeContainer : public OpenMPCodeContainer, public CPPCodeContainer {
   protected:
   public:
    CPPOpenMPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
    ~CPPOpenMPCodeContainer() override;

    void generateCompute(int tab) override;
};

class CPPWorkStealingCodeContainer : public WSSCodeContainer, public CPPCodeContainer {
   protected:
   public:
    CPPWorkStealingCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
    ~CPPWorkStealingCodeContainer() override;

    void produceClass() override;
    void generateCompute(int tab) override;
};
