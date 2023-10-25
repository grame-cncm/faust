/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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
 - add the ! character to the name of functions that modify their arguments
  (see https://docs.julialang.org/en/v1/manual/style-guide/#bang-convention)
 - in order to simplify global array typing, subcontainers are actually merged in the main DSP structure:
    - so 'mergeSubContainers' is used
    - global variables are added in the DSP structure
    - the JuliaInitFieldsVisitor class does initialisation for waveforms
    - the fGlobalDeclarationInstructions contains global functions and variables. It is "manually" used
    to generate global functions and move global variables declaration at DSP structure level.
*/

map<string, bool> JuliaInstVisitor::gFunctionSymbolTable;

dsp_factory_base* JuliaCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

JuliaCodeContainer::JuliaCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out)
{
    // Mandatory
    initialize(numInputs, numOutputs);
    fKlassName = name;
    fOut = out;
    
    // Allocate one static visitor
    if (!gGlobal->gJuliaVisitor) {
        gGlobal->gJuliaVisitor = new JuliaInstVisitor(out, name);
    }
}

CodeContainer* JuliaCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new JuliaScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* JuliaCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
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
    
    // Merge sub containers
    mergeSubContainers();

    // Functions
    tab(n, *fOut);
    gGlobal->gJuliaVisitor->Tab(n);
    
    // Only generate globals functions
    for (const auto& it : fGlobalDeclarationInstructions->fCode) {
        if (dynamic_cast<DeclareFunInst*>(it)) {
            it->accept(gGlobal->gJuliaVisitor);
        }
    }
   
    tab(n, *fOut);
    *fOut << "mutable struct " << fKlassName << "{T} <: dsp";
    tab(n + 1, *fOut);

    // Fields
    gGlobal->gJuliaVisitor->Tab(n + 1);
    generateDeclarations(gGlobal->gJuliaVisitor);
    // Generate global variables definition
    for (const auto& it : fGlobalDeclarationInstructions->fCode) {
        if (dynamic_cast<DeclareVarInst*>(it)) {
            it->accept(gGlobal->gJuliaVisitor);
        }
    }
    *fOut << fKlassName << "{T}() where {T} = begin";
    tab(n + 2, *fOut);
    *fOut << "dsp = new{T}()";
    JuliaInitFieldsVisitor initializer(fOut, n + 2);
    generateDeclarations(&initializer);
    // Generate global variables initialisation
    for (const auto& it : fGlobalDeclarationInstructions->fCode) {
        if (dynamic_cast<DeclareVarInst*>(it)) {
            it->accept(&initializer);
        }
    }
    tab(n + 2, *fOut);
    *fOut << "dsp";
    tab(n + 1, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    // Print metadata declaration
    produceMetadata(n);

    // getSampleRate
    tab(n, *fOut);
    gGlobal->gJuliaVisitor->Tab(n);
    generateGetSampleRate("getSampleRate", "dsp", false, false)->accept(gGlobal->gJuliaVisitor);

    // Info functions: getNumInputs/getNumOuputs
    tab(n, *fOut);
    produceInfoFunctions(n, "", "dsp", false, FunTyped::kDefault, gGlobal->gJuliaVisitor);
    
    tab(n, *fOut);
    *fOut << "function classInit!(dsp::" << fKlassName << "{T}, sample_rate::Int32) where {T}";
    {
        tab(n + 1, *fOut);
        gGlobal->gJuliaVisitor->Tab(n + 1);
        inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(gGlobal->gJuliaVisitor);
    }
    back(1, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "function instanceResetUserInterface!(dsp::" << fKlassName << "{T}) where {T}";
    {
        tab(n + 1, *fOut);
        generateResetUserInterface(gGlobal->gJuliaVisitor);
    }
    back(1, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "function instanceClear!(dsp::" << fKlassName << "{T}) where {T}";
    {
        tab(n + 1, *fOut);
        generateClear(gGlobal->gJuliaVisitor);
    }
    back(1, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "function instanceConstants!(dsp::" << fKlassName << "{T}, sample_rate::Int32) where {T}";
    {
        tab(n + 1, *fOut);
        inlineSubcontainersFunCalls(fInitInstructions)->accept(gGlobal->gJuliaVisitor);
    }
    back(1, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "function instanceInit!(dsp::" << fKlassName << "{T}, sample_rate::Int32) where {T}";
    tab(n + 1, *fOut);
    *fOut << "instanceConstants!(dsp, sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "instanceResetUserInterface!(dsp)";
    tab(n + 1, *fOut);
    *fOut << "instanceClear!(dsp)";
    tab(n, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "function init!(dsp::" << fKlassName << "{T}, sample_rate::Int32) where {T}";
    tab(n + 1, *fOut);
    *fOut << "classInit!(dsp, sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "instanceInit!(dsp, sample_rate)";
    tab(n, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    // JSON generation
    tab(n, *fOut);
    *fOut << "function getJSON(dsp::" << fKlassName << "{T}) where {T}";
    {
        string json = generateJSONAux();
        tab(n + 1, *fOut);
        *fOut << "return \"" << flattenJSON(json) << "\"" << endl;
        tab(n, *fOut);
    }
    back(1, *fOut);
    *fOut << "end";
    tab(n, *fOut);

    // User interface
    tab(n, *fOut);
    *fOut << "function buildUserInterface!(dsp::" << fKlassName << "{T}, ui_interface::UI) where {T}";
    tab(n + 1, *fOut);
    gGlobal->gJuliaVisitor->Tab(n + 1);
    generateUserInterface(gGlobal->gJuliaVisitor);
    back(1, *fOut);
    *fOut << "end";
    tab(n, *fOut);
    
    // Compute
    generateCompute(n);
}

void JuliaCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "function metadata!(dsp::" << fKlassName << "{T}, m::FMeta) where {T}";
    
        // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            tab(tabs + 1, *fOut);
            *fOut << "declare!(m, \"" << *(i.first) << "\", " << **(i.second.begin()) << ");";
        } else {
                // But the "author" meta data is accumulated, the upper level becomes the main author and sub-levels become
                // "contributor"
            for (set<Tree>::iterator j = i.second.begin(); j != i.second.end(); j++) {
                if (j == i.second.begin()) {
                    tab(tabs + 1, *fOut);
                    *fOut << "declare!(m, \"" << *(i.first) << "\", " << **j << ");";
                } else {
                    tab(tabs + 1, *fOut);
                    *fOut << "declare!(m, \""
                    << "contributor"
                    << "\", " << **j << ");";
                }
            }
        }
    }
    
    tab(tabs, *fOut);
    *fOut << "end" << endl;
}

// Scalar
JuliaScalarCodeContainer::JuliaScalarCodeContainer(const string& name,
                                                int numInputs, int numOutputs,
                                                std::ostream* out,
                                                int sub_container_type)
    : JuliaCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

void JuliaScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n, *fOut);
    *fOut << "@inbounds function compute!(dsp::" << fKlassName
    << "{T}, " << fFullCount << subst("::Int32, inputs::Matrix{$0}, outputs::Matrix{$0}) where {T}", xfloat());
    tab(n + 1, *fOut);
    gGlobal->gJuliaVisitor->Tab(n + 1);
    
    // Generates local variables declaration and setup
    generateComputeBlock(gGlobal->gJuliaVisitor);
    
    // Generates one single scalar loop
    SimpleForLoopInst* loop = fCurLoop->generateSimpleScalarLoop(fFullCount);
    loop->accept(gGlobal->gJuliaVisitor);
    
    /*
     // TODO : atomic switch
     // Currently for soundfile management
     */
    generatePostComputeBlock(gGlobal->gJuliaVisitor);
    
    back(1, *fOut);
    *fOut << "end" << endl;
}

// Vector
JuliaVectorCodeContainer::JuliaVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs), JuliaCodeContainer(name, numInputs, numOutputs, out)
{
}

void JuliaVectorCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    gGlobal->gJuliaVisitor->Tab(n + 1);
    tab(n + 1, *fOut);
    generateComputeFunctions(gGlobal->gJuliaVisitor);

    // Generates declaration
    tab(n + 1, *fOut);
    *fOut << "@inbounds function compute!(dsp::" << fKlassName
          << "{T}, " << fFullCount << subst("::Int32, inputs::Matrix{$0}, outputs::Matrix{$0}) where {T}", xfloat());
    tab(n + 2, *fOut);
    gGlobal->gJuliaVisitor->Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(gGlobal->gJuliaVisitor);

    // Generates the DSP loop
    fDAGBlock->accept(gGlobal->gJuliaVisitor);

    back(1, *fOut);
    *fOut << "end";
}
