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

/**
 * Implement C FIR base container.
 */

class CCodeContainer : public virtual CodeContainer {
   protected:
    CInstVisitor* fCodeProducer;
    std::ostream* fOut;

    virtual void produceClass();
    void produceMetadata(int tabs);
    virtual void produceInternal();
    
    virtual void generateComputeAux(int tab) = 0;
    
    void generateCompute(int n)
    {
        // Possibly generate separated functions
        tab(n, *fOut);
        fCodeProducer->Tab(n);
        generateComputeFunctions(fCodeProducer);
        
        char* archs = getenv("FAUST_ARCHS");
        if (archs) {
            tab(n, *fOut);
            for (const auto& it : tokenizeString(archs, ' ')) {
                *fOut << "__attribute__ ((target (\"arch=" << it << "\")))";
                generateComputeAux(n);
                tab(n, *fOut);
            }
            // Default version
            *fOut << "__attribute__ ((target (\"default\")))";
            generateComputeAux(n);
            tab(n, *fOut);
        } else {
            generateComputeAux(n);
        }
    }
    
    void generateAllocateFun(int n)
    {
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n, *fOut);
            *fOut << "void allocate" << fKlassName << "(" << fKlassName << "* dsp) {";
            tab(n + 1, *fOut);
            generateAllocate(fCodeProducer);
            back(1, *fOut);
            *fOut << "}";
        }
    }
    
    void generateDestroyFun(int n)
    {
        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n, *fOut);
            *fOut << "void destroy" << fKlassName << "(" << fKlassName << "* dsp) {";
            tab(n + 1, *fOut);
            generateDestroy(fCodeProducer);
            back(1, *fOut);
            *fOut << "}";
            tab(n, *fOut);
        }
    }
    
    void generateHeader1(int n)
    {
        tab(n, *fOut);
        *fOut << "#ifdef __cplusplus" << std::endl;
        *fOut << "extern \"C\" {" << std::endl;
        *fOut << "#endif" << std::endl;
        tab(n, *fOut);
        
        *fOut << "#if defined(_WIN32)" << std::endl;
        *fOut << "#define RESTRICT __restrict" << std::endl;
        *fOut << "#else" << std::endl;
        *fOut << "#define RESTRICT __restrict__" << std::endl;
        *fOut << "#endif" << std::endl;
        tab(n, *fOut);
    }
    
    void generateHeader2(int n)
    {
        tab(n, *fOut);
        *fOut << "#ifndef FAUSTCLASS " << std::endl;
        *fOut << "#define FAUSTCLASS " << fKlassName << std::endl;
        *fOut << "#endif" << std::endl;
        tab(n, *fOut);
        
        *fOut << "#ifdef __APPLE__ " << std::endl;
        *fOut << "#define exp10f __exp10f" << std::endl;
        *fOut << "#define exp10 __exp10" << std::endl;
        *fOut << "#endif" << std::endl;
        
        if (gGlobal->gLightMode) {
            tab(n, *fOut);
            *fOut << "#define max(a,b) ((a < b) ? b : a)\n";
            *fOut << "#define min(a,b) ((a < b) ? a : b)\n";
            tab(n, *fOut);
        }
    }
    
    void printMathHeader()
    {
        // For mathematical functions
        if (gGlobal->gFastMathLib != "") {
            includeFastMath();
        } else {
            addIncludeFile("<math.h>");
        }
        
        // For malloc/free
        addIncludeFile("<stdlib.h>");
        // For int64_t type
        addIncludeFile("<stdint.h>");
    }

   public:
    CCodeContainer()
    {}
    CCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;
        fOut = out;

        printMathHeader();
        
        fCodeProducer = new CInstVisitor(out, name);
    }

    virtual ~CCodeContainer()
    {
        // fCodeProducer is a 'Garbageable'
    }
    
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
    static CodeContainer* createScalarContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* dst, int sub_container_type);

    static CodeContainer* createContainer(const std::string& name, int numInputs, int numOutputs,
                                          std::ostream* dst = new std::stringstream());
};

/**
 * Implement C FIR scalar container.
 */

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

    void generateComputeAux(int tab);
};

/**
 * Implement C FIR scalar container (special version for -os0 generation mode)
 */

class CScalarOneSampleCodeContainer1 : public CScalarCodeContainer {
   protected:
    virtual void produceClass();
   public:
    CScalarOneSampleCodeContainer1(const std::string& name,
                                  int numInputs,
                                  int numOutputs,
                                  std::ostream* out,
                                  int sub_container_type)
    {
        initialize(numInputs, numOutputs);
        fKlassName = name;
        fOut = out;
        
        printMathHeader();
        
        fSubContainerType = sub_container_type;
        fCodeProducer = new CInstVisitor(out, name);
    }

    virtual ~CScalarOneSampleCodeContainer1()
    {}
    
    void generateComputeAux(int tab);
};

/**
 * Implement C FIR scalar container (special version for -os1 generation mode with iZone and fZone).
 */

class CScalarOneSampleCodeContainer2 : public CScalarCodeContainer {
    protected:
        virtual void produceClass();
    public:
        CScalarOneSampleCodeContainer2()
        {}
        CScalarOneSampleCodeContainer2(const std::string& name,
                                      int numInputs,
                                      int numOutputs,
                                      std::ostream* out,
                                      int sub_container_type)
        {
            initialize(numInputs, numOutputs);
            fKlassName = name;
            fOut = out;
            
            printMathHeader();
            
            fSubContainerType = sub_container_type;
            fCodeProducer = new CInstVisitor1(out, name);
        }
    
        virtual ~CScalarOneSampleCodeContainer2()
        {}
    
        void generateComputeAux(int tab);
};

/**
 Implement C FIR scalar container (special version for -os2 generation mode with iZone and fZone). Some of the DSP struct fields will be moved in the iZone/fZone (typically long delay lines). The others will stay in the DSP structure.
 */

class CScalarOneSampleCodeContainer3 : public CScalarOneSampleCodeContainer2 {
    protected:
        virtual void produceClass();
    public:
        CScalarOneSampleCodeContainer3(const std::string& name,
                                       int numInputs,
                                       int numOutputs,
                                       std::ostream* out,
                                       int sub_container_type)
        {
            initialize(numInputs, numOutputs);
            fKlassName = name;
            fOut = out;
            
            printMathHeader();
            
            fSubContainerType = sub_container_type;
            // Setup in produceClass
            fCodeProducer = nullptr;
        }
        
        virtual ~CScalarOneSampleCodeContainer3()
        {}
    
};

/**
 Implement C FIR scalar container (special version for -os3 generation mode with iZone and fZone in DSP struct).
 */

class CScalarOneSampleCodeContainer4 : public CScalarOneSampleCodeContainer3 {
    protected:
        virtual void produceClass();
    public:
        CScalarOneSampleCodeContainer4(const std::string& name,
                                       int numInputs,
                                       int numOutputs,
                                       std::ostream* out,
                                       int sub_container_type)
        :CScalarOneSampleCodeContainer3(name, numInputs, numOutputs, out, sub_container_type)
        {}
        
        virtual ~CScalarOneSampleCodeContainer4()
        {}
        
        void generateComputeAux(int tab);
    
};

/**
 Implement C FIR vector container.
 */

class CVectorCodeContainer : public VectorCodeContainer, public CCodeContainer {
   protected:
   public:
    CVectorCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~CVectorCodeContainer()
    {}

    void generateComputeAux(int n);
};

/**
 Implement C FIR OpenMP container.
 */

class COpenMPCodeContainer : public OpenMPCodeContainer, public CCodeContainer {
   protected:
   public:
    COpenMPCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~COpenMPCodeContainer()
    {}

    void generateComputeAux(int tab);
};

/**
 Implement C FIR Work Stealing container.
 */

class CWorkStealingCodeContainer : public WSSCodeContainer, public CCodeContainer {
   protected:
   public:
    CWorkStealingCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out);
    virtual ~CWorkStealingCodeContainer()
    {}

    void generateComputeAux(int tab);
};

#endif
