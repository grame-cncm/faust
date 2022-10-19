/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2022 GRAME, Centre National de Creation Musicale
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

#include "template_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

map<string, bool> TemplateInstVisitor::gFunctionSymbolTable;

dsp_factory_base* TemplateCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

TemplateCodeContainer::TemplateCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out)
{
    // Mandatory
    initialize(numInputs, numOutputs);
    fKlassName = name;
    fOut = out;
    
    // Allocate one static visitor
    if (!gGlobal->gTemplateVisitor) {
        gGlobal->gTemplateVisitor = new TemplateInstVisitor(out, name);
    }
}

CodeContainer* TemplateCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new TemplateScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* TemplateCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    gGlobal->gDSPStruct = true;
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Template\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Template\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Template\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Template\n");
    } else if (gGlobal->gVectorSwitch) {
        container = new TemplateVectorCodeContainer(name, numInputs, numOutputs, dst);
    } else {
        container = new TemplateScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

// Used for subcontainers
void TemplateCodeContainer::produceInternal()
{}

void TemplateCodeContainer::produceClass()
{
    int n = 0;
    *fOut << "TemplateCodeContainer::produceClass\n";
    
    // Print header
    
    // Possibly missing mathematical functions
    
    // Possibly merge sub containers (with an empty 'produceInternal' method)
    // mergeSubContainers();

    // Functions
  
    // Fields
    
    // Print metadata declaration
    // produceMetadata(n);

    // getSampleRate
  
    // Info functions: getNumInputs/getNumOuputs
    
    // classInit
    
    // instanceResetUserInterface
    
    // instanceClear
  
    // instanceConstants

    // instanceInit
   
    // init
   
    // buildUserInterface
    
    // Compute
    generateCompute(n);
}

void TemplateCodeContainer::produceMetadata(int tabs)
{}

// Scalar
TemplateScalarCodeContainer::TemplateScalarCodeContainer(const string& name,
                                                    int numInputs, int numOutputs,
                                                    std::ostream* out,
                                                    int sub_container_type)
    : TemplateCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

void TemplateScalarCodeContainer::generateCompute(int n)
{
    *fOut << "TemplateScalarCodeContainer::generateCompute\n";
    
    // Generates declaration

    // Generates local variables declaration and setup

    // Generates one single scalar loop

    // Generates post compute
}

// Vector
TemplateVectorCodeContainer::TemplateVectorCodeContainer(const string& name,
                                                    int numInputs, int numOutputs,
                                                    std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs), TemplateCodeContainer(name, numInputs, numOutputs, out)
{}

void TemplateVectorCodeContainer::generateCompute(int n)
{
    *fOut << "TemplateVectorCodeContainer::generateCompute\n";
    
    // Possibly generate separated functions
    
    // Generates declaration
    
    // Generates local variables declaration and setup
    
    // Generates the DSP loop
}
