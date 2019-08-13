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

#include "c_instructions.hh"
#include "code_container.hh"
#include "dsp_factory.hh"
#include "omp_code_container.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"

#ifdef WIN32
#pragma warning(disable : 4250)
#endif

class CCodeContainer : public virtual CodeContainer {
   protected:
    CInstVisitor  fCodeProducer;
    std::ostream* fOut;

    void produceMetadata(int tabs);

   public:
    CCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out)
        : fCodeProducer(out, name), fOut(out)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;

        // For mathematical functions
        if (gGlobal->gFastMath) {
            addIncludeFile((gGlobal->gFastMathLib == "def") ? "\"faust/dsp/fastmath.cpp\""
                                                            : ("\"" + gGlobal->gFastMathLib + "\""));
        } else {
            addIncludeFile("<math.h>");
        }

        // For malloc/free
        addIncludeFile("<cstdlib>");
    }

    ~CCodeContainer() override = default;

    void              produceClass() override;
    virtual void      generateCompute(int tab) = 0;
    void              produceInternal() override;
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

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type) override;

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs,
                                          std::ostream* dst = new std::stringstream());
};

class CScalarCodeContainer : public CCodeContainer {
   protected:
   public:
    CScalarCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out,
                         int sub_container_type);
    ~CScalarCodeContainer() override;

    void generateCompute(int tab) override;
};

class CVectorCodeContainer : public VectorCodeContainer, public CCodeContainer {
   protected:
   public:
    CVectorCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    ~CVectorCodeContainer() override;

    void generateCompute(int n) override;
};

class COpenMPCodeContainer : public OpenMPCodeContainer, public CCodeContainer {
   protected:
   public:
    COpenMPCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    ~COpenMPCodeContainer() override;

    void generateCompute(int tab) override;
};

class CWorkStealingCodeContainer : public WSSCodeContainer, public CCodeContainer {
   protected:
   public:
    CWorkStealingCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    ~CWorkStealingCodeContainer() override;

    void generateCompute(int tab) override;
};
