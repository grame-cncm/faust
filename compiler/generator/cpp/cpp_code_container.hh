/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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
#include "opencl_instructions.hh"
#include "omp_code_container.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"
#include "dsp_factory.hh"

#ifdef WIN32
#pragma warning (disable: 4250)
#endif

using namespace std;

class CPPCodeContainer : public virtual CodeContainer {

    protected:

        CPPInstVisitor fCodeProducer;
        std::ostream* fOut;
        string fSuperKlassName;

        void produceMetadata(int tabs);
        void produceInit(int tabs);

    public:

        CPPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
            : fCodeProducer(out), fOut(out), fSuperKlassName(super)
        {
            initializeCodeContainer(numInputs, numOutputs);
            fKlassName = name;
            
            // For mathematical functions
            if (gGlobal->gFastMath) {
                addIncludeFile((gGlobal->gFastMathLib == "def") ? "\"faust/dsp/fastmath.cpp\"" : ("\"" + gGlobal->gFastMathLib + "\""));
            } else {
                addIncludeFile("<cmath>");
            }
        }
        
        virtual ~CPPCodeContainer()
        {}

        virtual void produceClass();
        virtual void generateCompute(int tab) = 0;
        virtual void produceInternal();
    
        virtual dsp_factory_base* produceFactory();
    
        virtual void printHeader()
        {
            CodeContainer::printHeader(*fOut);
            
            tab(0, *fOut); *fOut << "#ifndef  __" << gGlobal->gClassName << "_H__";
            tab(0, *fOut); *fOut << "#define  __" << gGlobal->gClassName << "_H__" << std::endl << std::endl;
        }
    
        virtual void printFloatDef() { printfloatdef(*fOut, (gGlobal->gFloatSize == 3)); }
        
        virtual void printFooter()
        {
            tab(0, *fOut); *fOut << "#endif"<< std::endl;
        }

        CodeContainer* createScalarContainer(const string& name, int sub_container_type);

        static CodeContainer* createContainer(const string& name, const string& super, int numInputs, int numOutputs, ostream* dst = new stringstream());

};

class CPPScalarCodeContainer : public CPPCodeContainer {

    protected:

    public:

        CPPScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out, int sub_container_type);
        virtual ~CPPScalarCodeContainer();

        void generateCompute(int tab);

};

class CPPVectorCodeContainer : public VectorCodeContainer, public CPPCodeContainer {

    protected:

    public:

        CPPVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPVectorCodeContainer();

        void generateCompute(int tab);

};

class CPPOpenMPCodeContainer : public OpenMPCodeContainer, public CPPCodeContainer {

    protected:

    public:

        CPPOpenMPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPOpenMPCodeContainer();

        void generateCompute(int tab);

};

class CPPWorkStealingCodeContainer : public WSSCodeContainer, public CPPCodeContainer {

    protected:

    public:

        CPPWorkStealingCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out);
        virtual ~CPPWorkStealingCodeContainer();

        void produceClass();
        void generateCompute(int tab);

};

#endif
