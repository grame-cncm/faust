/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#include "julia_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 Julia backend and module description:
 
 - 'delete' for SubContainers is not generated
*/

map<string, bool> JuliaInstVisitor::gFunctionSymbolTable;

dsp_factory_base* JuliaCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* JuliaCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new JuliaScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* JuliaCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    gGlobal->gDSPStruct = true;
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Julia\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Julia\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Julia\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Julia\n");
    } else if (gGlobal->gVectorSwitch) {
        //container = new JuliaVectorCodeContainer(name, numInputs, numOutputs, dst);
        throw faustexception("ERROR : Vector not supported for Julia\n");
    } else {
        container = new JuliaScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

void JuliaCodeContainer::produceInternal()
{
    int n = 0;
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);

    tab(n, *fOut);
    *fOut << "mutable struct " << fKlassName;
    tab(n + 1, *fOut);
    
    // Fields
    fCodeProducer->Tab(n + 1);
    generateDeclarations(fCodeProducer);
    *fOut << fKlassName << "() = begin";
    tab(n + 2, *fOut);
    *fOut << "dsp = new()";
    JuliaInitFieldsVisitor initializer(fOut, n + 2);
    generateDeclarations(&initializer);
    tab(n + 2, *fOut);
    *fOut << "dsp";
    tab(n + 1, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    tab(n, *fOut);
    produceInfoFunctions(n, fKlassName, "dsp", false, false, fCodeProducer);
    
    tab(n, *fOut);
    *fOut << "function instanceInit" << fKlassName << "(dsp::" << fKlassName << ", sample_rate::Int32)";
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    generateInit(fCodeProducer);
    generateResetUserInterface(fCodeProducer);
    generateClear(fCodeProducer);
    back(1, *fOut);
    *fOut << "end";
    
    // Fill
    tab(n, *fOut);
    string counter = "count";
    if (fSubContainerType == kInt) {
        tab(n, *fOut);
        *fOut << "function fill" << fKlassName << "(dsp::" << fKlassName << ", " << counter << "::Int32, table::Vector{Int32})";
    } else {
        tab(n, *fOut);
        *fOut << "function fill" << fKlassName << "(dsp::" << fKlassName << ", " << counter << "::Int32, table::Vector{" << ifloat() << "})";
    }
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    generateComputeBlock(fCodeProducer);
    SimpleForLoopInst* loop = fCurLoop->generateSimpleScalarLoop(counter);
    loop->accept(fCodeProducer);
    back(1, *fOut);
    *fOut << "end" << endl;
    
    // Memory methods
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "function new" << fKlassName << "()";
    tab(n + 1, *fOut);
    *fOut << "return " << fKlassName << "()";
    tab(n, *fOut);
    *fOut << "end";
}

void JuliaCodeContainer::produceClass()
{
    int n = 0;
    
    // Print header
    *fOut << "#=\n"
          << "Code generated with Faust version " << FAUSTVERSION << endl;
    *fOut << "Compilation options: ";
    stringstream stream;
    gGlobal->printCompilationOptions(stream);
    *fOut << stream.str();
    tab(n, *fOut);
    *fOut << "=#";
    tab(n, *fOut);
    
    // Dependencies and REAL alias
    tab(n, *fOut);
    *fOut << "using StaticArrays";
    tab(n, *fOut);
    *fOut << "const REAL = " << ifloat();
    tab(n, *fOut);
    
    // Missing mathematical functions
    *fOut << "pow(x, y) = x ^ y";
    tab(n, *fOut);
    *fOut << "rint(x) = round(x, Base.Rounding.RoundNearest)";
    tab(n, *fOut);
    *fOut << "remainder(x, y) = rem(x, y, Base.Rounding.RoundNearest)";
    
    // Generate gub containers
    generateSubContainers();

    // Functions
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);
   
    tab(n, *fOut);
    *fOut << "mutable struct " << fKlassName << " <: dsp";
    tab(n + 1, *fOut);

    // Fields
    fCodeProducer->Tab(n + 1);
    generateDeclarations(fCodeProducer);
    *fOut << fKlassName << "() = begin";
    tab(n + 2, *fOut);
    *fOut << "dsp = new()";
    JuliaInitFieldsVisitor initializer(fOut, n + 2);
    generateDeclarations(&initializer);
    tab(n + 2, *fOut);
    *fOut << "dsp";
    tab(n + 1, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    // Print metadata declaration
    produceMetadata(n + 1);

    // Get sample rate method
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGetSampleRate("getSampleRate", "dsp", false, false)->accept(fCodeProducer);

    tab(n, *fOut);
    produceInfoFunctions(n, "", "dsp", false, false, fCodeProducer);
    
    tab(n, *fOut);
    *fOut << "function classInit(sample_rate::Int32)";
    {
        tab(n + 1, *fOut);
        // Local visitor here to avoid DSP object incorrect type generation
        JuliaInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 1);
        generateStaticInit(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "end";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "function instanceResetUserInterface(dsp::" << fKlassName << ")";
    {
        tab(n + 1, *fOut);
        // Local visitor here to avoid DSP object incorrect type generation
        JuliaInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 1);
        generateResetUserInterface(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "end";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "function instanceClear(dsp::" << fKlassName << ")";
    {
        tab(n + 1, *fOut);
        // Local visitor here to avoid DSP object incorrect type generation
        JuliaInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 1);
        generateClear(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "end";

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "function instanceConstants(dsp::" << fKlassName << ", sample_rate::Int32)";
    {
        tab(n + 1, *fOut);
        // Local visitor here to avoid DSP object incorrect type generation
        JuliaInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 1);
        generateInit(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "end";
   
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "function instanceInit(dsp::" << fKlassName << ", sample_rate::Int32)";
    tab(n + 1, *fOut);
    *fOut << "instanceConstants(dsp, sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "instanceResetUserInterface(dsp)";
    tab(n + 1, *fOut);
    *fOut << "instanceClear(dsp)";
    tab(n, *fOut);
    *fOut << "end";

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "function init(dsp::" << fKlassName << ", sample_rate::Int32)";
    tab(n + 1, *fOut);
    *fOut << "classInit(sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "instanceInit(dsp, sample_rate)";
    tab(n, *fOut);
    *fOut << "end";
    
    // JSON generation
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "function getJSON(dsp::" << fKlassName << ")";
    {
        string json;
        if (gGlobal->gFloatSize == 1) {
            json = generateJSON<float>();
        } else {
            json = generateJSON<double>();
        }
        tab(n + 1, *fOut);
        *fOut << "return \"" << flattenJSON(json) << "\"" << endl;
        tab(n, *fOut);
    }
    back(1, *fOut);
    *fOut << "end";

    // User interface
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "function buildUserInterface(dsp::" << fKlassName << ", ui_interface::UI)";
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    // Compute
    generateCompute(n);
}

void JuliaCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n, *fOut);
    *fOut << "@inbounds function compute(dsp::" << fKlassName
          << ", " << fFullCount << "::Int32, inputs, outputs)";
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Generates one single scalar loop
    SimpleForLoopInst* loop = fCurLoop->generateSimpleScalarLoop(fFullCount);
    loop->accept(fCodeProducer);

    /*
    // TODO : atomic switch
    // Currently for soundfile management
    */
    generatePostComputeBlock(fCodeProducer);

    back(1, *fOut);
    *fOut << "end" << endl;
}

void JuliaCodeContainer::produceMetadata(int tabs)
{
}

// Scalar
JuliaScalarCodeContainer::JuliaScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                                                   int sub_container_type)
    : JuliaCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

// Vector
JuliaVectorCodeContainer::JuliaVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs), JuliaCodeContainer(name, numInputs, numOutputs, out)
{
}

void JuliaVectorCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateComputeFunctions(fCodeProducer);

    // Generates declaration
    tab(n + 1, *fOut);
    *fOut << "@inbounds function compute(dsp::" << fKlassName
          << ", " << fFullCount << "::Int32, inputs, outputs)";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Generates the DSP loop
    fDAGBlock->accept(fCodeProducer);

    back(1, *fOut);
    *fOut << "end";
}
