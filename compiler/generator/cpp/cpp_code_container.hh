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

#ifndef _CPP_CODE_CONTAINER_H
#define _CPP_CODE_CONTAINER_H

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

class CPPCodeContainer : public virtual CodeContainer {
   protected:
    CPPInstVisitor* fCodeProducer;
    std::ostream*  fOut;
    std::string    fSuperKlassName;

    void produceMetadata(int tabs);
    void produceInit(int tabs);
    
    std::string genVirtual();
    std::string genFinal();
  
   public:
    CPPCodeContainer()
    {}
    CPPCodeContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs, std::ostream* out) : fSuperKlassName(super)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;
        fOut = out;

        // For mathematical functions
        if (gGlobal->gFastMath) {
            addIncludeFile((gGlobal->gFastMathLib == "def") ? "\"faust/dsp/fastmath.cpp\""
                                                            : ("\"" + gGlobal->gFastMathLib + "\""));
        } else {
            addIncludeFile("<cmath>");
            addIncludeFile("<algorithm>");
            // For int64_t type
            addIncludeFile("<cstdint>");
        }
    
        fCodeProducer = new CPPInstVisitor(out);
    }

    virtual ~CPPCodeContainer()
    {
        // fCodeProducer is a 'Garbageable'
    }

    virtual void produceClass();
    virtual void generateCompute(int tab) = 0;
    virtual void produceInternal();

    virtual dsp_factory_base* produceFactory();

    virtual void printHeader()
    {
        CodeContainer::printHeader(*fOut);

        tab(0, *fOut);
        *fOut << "#ifndef  __" << gGlobal->gClassName << "_H__";
        tab(0, *fOut);
        *fOut << "#define  __" << gGlobal->gClassName << "_H__" << std::endl << std::endl;
    }

    virtual void printFloatDef() { printfloatdef(*fOut); }

    virtual void printFooter()
    {
        tab(0, *fOut);
        *fOut << "#endif" << std::endl;
    }

    CodeContainer* createScalarContainer(const std::string& name, int sub_container_type);
    static CodeContainer* createScalarContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs, ostream* dst, int sub_container_type);
    
    static CodeContainer* createContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs,
                                          ostream* dst = new std::stringstream());
};

class CPPScalarCodeContainer : public CPPCodeContainer {
   protected:
   public:
    CPPScalarCodeContainer()
    {}
    CPPScalarCodeContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs, std::ostream* out,
                           int sub_container_type);
    virtual ~CPPScalarCodeContainer()
    {}

    void generateCompute(int tab);
};

// Special version for -os0 generation mode
class CPPScalarOneSampleCodeContainer1 : public CPPScalarCodeContainer {
   protected:
    virtual void produceClass();
   public:
    CPPScalarOneSampleCodeContainer1(const std::string& name, const std::string& super, int numInputs, int numOutputs, std::ostream* out,
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
            addIncludeFile("<cmath>");
            addIncludeFile("<algorithm>");
            // For int64_t type
            addIncludeFile("<cstdint>");
        }
        
        fCodeProducer = new CPPInstVisitor(out);
    }
    virtual ~CPPScalarOneSampleCodeContainer1()
    {}
    
    void generateCompute(int tab);
};

// Special version for -os1 generation mode with iZone and fZone
class CPPScalarOneSampleCodeContainer2 : public CPPScalarCodeContainer {
    protected:
        virtual void produceClass();
    public:
        CPPScalarOneSampleCodeContainer2()
        {}
        CPPScalarOneSampleCodeContainer2(const std::string& name, const std::string& super, int numInputs, int numOutputs, std::ostream* out,
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
                addIncludeFile("<cmath>");
                addIncludeFile("<algorithm>");
                // For int64_t type
                addIncludeFile("<cstdint>");
            }
        
            fCodeProducer = new CPPInstVisitor1(out);
        }
        virtual ~CPPScalarOneSampleCodeContainer2()
        {}
        
        void generateCompute(int tab);
};

/*
 Some of the DSP struct fields will be moved in the iZone/fZone (typically long delay lines).
 The others will stay in the DSP structure.
 */

// Special version for -os2 generation mode with iZone and fZone
class CPPScalarOneSampleCodeContainer3 : public CPPScalarOneSampleCodeContainer2 {
    protected:
        virtual void produceClass();
    public:
        CPPScalarOneSampleCodeContainer3(const std::string& name, const std::string& super, int numInputs, int numOutputs, std::ostream* out,
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
                addIncludeFile("<cmath>");
                addIncludeFile("<algorithm>");
                // For int64_t type
                addIncludeFile("<cstdint>");
            }
        
            // Setup in produceClass
            fCodeProducer = nullptr;
        }
        virtual ~CPPScalarOneSampleCodeContainer3()
        {}
 
};

// Special version for -os3 generation mode with iZone and fZone in DSP struct
class CPPScalarOneSampleCodeContainer4 : public CPPScalarOneSampleCodeContainer3 {

    protected:
        virtual void produceClass();
    public:
        CPPScalarOneSampleCodeContainer4(const std::string& name, const std::string& super,
                                         int numInputs, int numOutputs,
                                         std::ostream* out,
                                         int sub_container_type)
        :CPPScalarOneSampleCodeContainer3(name, super, numInputs, numOutputs, out, sub_container_type)
        {}
    
    virtual ~CPPScalarOneSampleCodeContainer4()
    {}
    
    void generateCompute(int tab);
    
};

class CPPVectorCodeContainer : public VectorCodeContainer, public CPPCodeContainer {
   protected:
   public:
    CPPVectorCodeContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs, std::ostream* out);
    virtual ~CPPVectorCodeContainer()
    {}

    void generateCompute(int tab);
};

class CPPOpenMPCodeContainer : public OpenMPCodeContainer, public CPPCodeContainer {
   protected:
   public:
    CPPOpenMPCodeContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs, std::ostream* out);
    virtual ~CPPOpenMPCodeContainer()
    {}

    void generateCompute(int tab);
};

class CPPWorkStealingCodeContainer : public WSSCodeContainer, public CPPCodeContainer {
   protected:
   public:
    CPPWorkStealingCodeContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs,
                                 std::ostream* out);
    virtual ~CPPWorkStealingCodeContainer()
    {}

    void produceClass();
    void generateCompute(int tab);
};

#endif
