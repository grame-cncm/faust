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

#ifndef _C_CODE_CONTAINER_H
#define _C_CODE_CONTAINER_H

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
    CInstVisitor* fCodeProducer;
    std::ostream* fOut;

    virtual void produceClass();
    void produceMetadata(int tabs);
    virtual void produceInternal();

   public:
    CCodeContainer()
    {}
    CCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;
        fOut = out;

        // For mathematical functions
        if (gGlobal->gFastMath) {
            addIncludeFile((gGlobal->gFastMathLib == "def") ? "\"faust/dsp/fastmath.cpp\""
                                                            : ("\"" + gGlobal->gFastMathLib + "\""));
        } else {
            addIncludeFile("<math.h>");
        }

        // For malloc/free
        addIncludeFile("<stdlib.h>");
        
        fCodeProducer = new CInstVisitor(out, name);
    }

    virtual ~CCodeContainer()
    {
        // fCodeProducer is a 'Garbageable'
    }
  
    virtual void generateCompute(int tab) = 0;
    
    virtual dsp_factory_base* produceFactory();

    virtual void printHeader()
    {
        CodeContainer::printHeader(*fOut);

        tab(0, *fOut);
        *fOut << "#ifndef  __" << gGlobal->gClassName << "_H__";
        tab(0, *fOut);
        *fOut << "#define  __" << gGlobal->gClassName << "_H__" << std::endl << std::endl;
    }

    virtual void printFloatDef() { printfloatdef(*fOut, (gGlobal->gFloatSize == 3)); }

    virtual void printFooter()
    {
        tab(0, *fOut);
        *fOut << "#endif" << std::endl;
    }

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs,
                                          std::ostream* dst = new std::stringstream());
};

class CScalarCodeContainer : public CCodeContainer {
   protected:
 
   public:
    CScalarCodeContainer()
    {}
    CScalarCodeContainer(const std::string& name,
                         int numInputs,
                         int numOutputs,
                         std::ostream* out,
                         int sub_container_type);
    virtual ~CScalarCodeContainer()
    {}

    void generateCompute(int tab);
};

class CScalarOneSampleCodeContainer : public CScalarCodeContainer {
   protected:
    virtual void produceClass();
    virtual void produceInternal();
   public:
    CScalarOneSampleCodeContainer(const std::string& name,
                                  int numInputs,
                                  int numOutputs,
                                  std::ostream* out,
                                  int sub_container_type)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;
        fOut = out;
        
        // For mathematical functions
        if (gGlobal->gFastMath) {
            addIncludeFile((gGlobal->gFastMathLib == "def") ? "\"faust/dsp/fastmath.cpp\""
                           : ("\"" + gGlobal->gFastMathLib + "\""));
        } else {
            addIncludeFile("<math.h>");
        }
        
        // For malloc/free
        addIncludeFile("<stdlib.h>");
        
        fSubContainerType = sub_container_type;
        
        //fCodeProducer = new CInstVisitor(out, name);
        fCodeProducer = new CInstVisitor1(out, name);
    }

    virtual ~CScalarOneSampleCodeContainer()
    {}
    
    void generateCompute(int tab);
};

class CVectorCodeContainer : public VectorCodeContainer, public CCodeContainer {
   protected:
   public:
    CVectorCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~CVectorCodeContainer()
    {}

    void generateCompute(int n);
};

class COpenMPCodeContainer : public OpenMPCodeContainer, public CCodeContainer {
   protected:
   public:
    COpenMPCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~COpenMPCodeContainer()
    {}

    void generateCompute(int tab);
};

class CWorkStealingCodeContainer : public WSSCodeContainer, public CCodeContainer {
   protected:
   public:
    CWorkStealingCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~CWorkStealingCodeContainer()
    {}

    void generateCompute(int tab);
};

#endif
