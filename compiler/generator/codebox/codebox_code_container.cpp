/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2023 GRAME, Centre National de Creation Musicale
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

#include "codebox_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

// Documentation
// https://rnbo.cycling74.com/objects/ref/gen~
// https://rnbo.cycling74.com/learn/how-to-include-rnbo-in-your-c-project
// https://cycling74.com/tutorials/gen~-for-beginners-part-6-thinking-inside-the-codebox
// https://rnbo.cycling74.com/codebox

using namespace std;

/*
 Codebox backend description:

 - variable identifiers cannot end by a number, so add a "_cb" suffix
 - all init code is done in 'dspsetup', called when audio start or in case of SR change
 - gOneSampleControl mode is used, 'control' function is generated as well as 'update' function
 which call 'control' only when needed (that is when as least one parameter changes)
 - 'compute' returns the list of audio outputs
 - some identifiers ending with a digit have to be used with "this." syntax in 'update' function (see CodeboxLabelsVisitor printArgs/printArgsCall)
 */

map<string, bool> CodeboxInstVisitor::gFunctionSymbolTable;

dsp_factory_base* CodeboxCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeboxCodeContainer::CodeboxCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out)
{
    // Mandatory
    initialize(numInputs, numOutputs);
    fKlassName = name;
    fOut = out;
    
    // Allocate one static visitor to be shared by main module and sub containers
    if (!gGlobal->gCodeboxVisitor) {
        gGlobal->gCodeboxVisitor = new CodeboxInstVisitor(out, name);
    }
}

CodeContainer* CodeboxCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new CodeboxScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* CodeboxCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    gGlobal->gDSPStruct = true;
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Codebox\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Codebox\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Codebox\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Codebox\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vecor not supported for Codebox\n");
    } else {
        container = new CodeboxScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

/*
 Given as an example of what a real backend would have to do: add or remove FIR visiting code etc.
*/
void CodeboxCodeContainer::produceClass()
{
    int n = 0;
    
    // Print header
    *fOut << "// Code generated with Faust version " << FAUSTVERSION << endl;
    *fOut << "// Compilation options: ";
    stringstream stream;
    gGlobal->printCompilationOptions(stream);
    *fOut << stream.str();
    tab(n, *fOut);
    
    // Additional functions'
    *fOut << "// Additional functions";
    tab(n, *fOut);
    // Emulates the missing rint : https://en.wikipedia.org/wiki/Rounding#Round_half_to_even
    *fOut << "function faust_rint(x) {\n";
    *fOut << "\t let i : Int = trunc(x);";
    *fOut << "\t let f  : number = x - i; \n";
    *fOut << "\t let odd : Int = abs(i % 2) >= 1; \n";
    *fOut << "\t let even : Int = odd == 0; \n";
    *fOut << "\t let a : number = (x > 0) * (((f > 0.5) * even) + ((f >= 0.5) * odd)); \n";
    *fOut << "\t let b : number = (x < 0) * (((f < -0.5) * even) + ((f <= -0.5) * odd)); \n";
    *fOut << "\t return i + (a - b); \n";
    *fOut<< "} \n";
    
    // Params
    *fOut << "// Params";
    tab(n, *fOut);
    
    CodeboxParamsVisitor shortnames1(fOut);
    // First pass to build shortnames
    generateUserInterface(&shortnames1);
    // Second pass to generate
    generateUserInterface(&shortnames1);
    
    // Possibly merge sub containers (with an empty 'produceInternal' method)
    mergeSubContainers();

    // Only generate globals functions
    *fOut << "// Globals";
    tab(n, *fOut);
    for (const auto& it : fGlobalDeclarationInstructions->fCode) {
        if (dynamic_cast<DeclareFunInst*>(it)) {
            it->accept(gGlobal->gCodeboxVisitor);
        }
    }
    
    // Fields
    *fOut << "// Fields";
    tab(n, *fOut);
    generateDeclarations(gGlobal->gCodeboxVisitor);
    // Generate global variables definition
    for (const auto& it : fGlobalDeclarationInstructions->fCode) {
        if (dynamic_cast<DeclareVarInst*>(it)) {
            it->accept(gGlobal->gCodeboxVisitor);
        }
    }
    // Control
    *fOut << "@state fUpdated : Int = 0;";
    tab(n, *fOut);
    
    // For control computation
    if (fIntControl->fCurIndex > 0) {
        *fOut << "@state iControl_cb = new FixedIntArray(" << fIntControl->fCurIndex << ");";
        tab(n, *fOut);
    }
    if (fRealControl->fCurIndex > 0) {
        *fOut << "@state fControl_cb = new " << gGlobal->gCodeboxVisitor->getTypeManager()->fTypeDirectTable[itfloatptr()] << "(" << fRealControl->fCurIndex << ");";
    }
    tab(n, *fOut);
  
    *fOut << "// Init";
    tab(n, *fOut);
    *fOut << "function dspsetup() {";
    tab(n + 1, *fOut);
    *fOut << "fUpdated = true;";
    tab(n + 1, *fOut);
    gGlobal->gCodeboxVisitor->Tab(n + 1);
    
    CodeboxInitArraysVisitor initializer(fOut, n + 1);
    generateDeclarations(&initializer);
    // Generate global variables initialisation
    for (const auto& it : fGlobalDeclarationInstructions->fCode) {
        if (dynamic_cast<DeclareVarInst*>(it)) {
            it->accept(&initializer);
        }
    }
    
    // classInit
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(gGlobal->gCodeboxVisitor);
    
    // instanceResetUserInterface
    generateResetUserInterface(gGlobal->gCodeboxVisitor);
    
    // instanceClear
    generateClear(gGlobal->gCodeboxVisitor);
  
    // instanceConstants
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    inlineSubcontainersFunCalls(fInitInstructions)->accept(gGlobal->gCodeboxVisitor);
 
    back(1, *fOut);
    *fOut << "}";
    tab(n, *fOut);
    
    // Control
    *fOut << "// Control";
    tab(n, *fOut);
    *fOut << "function control() {";
    tab(n + 1, *fOut);
    gGlobal->gCodeboxVisitor->Tab(n + 1);
    // Generates local variables declaration and setup
    generateComputeBlock(gGlobal->gCodeboxVisitor);
    back(1, *fOut);
    *fOut << "}";
    tab(n, *fOut);
    
    // Update parameters
    *fOut << "// Update parameters";
    tab(n, *fOut);
    *fOut << "function update(";
    CodeboxLabelsVisitor shortnames2(fOut);
    // First pass to build shortnames
    generateUserInterface(&shortnames2);
    // Second pass to build the list of shortnames for args
    generateUserInterface(&shortnames2);
    // Then generate the list of args
    shortnames2.printArgs();
    *fOut << ") {";
    tab(n+1, *fOut);
    CodeboxUpdateParamsVisitor params(fOut, n+1);
    // First pass to build shortnames
    generateUserInterface(&params);
    // Second pass to print the update lines
    generateUserInterface(&params);
    *fOut << "if (fUpdated) { fUpdated = false; control(); }";
    tab(n, *fOut);
    *fOut << "}";
    tab(n, *fOut);
    
    // Compute
    generateCompute(n);
    
    // Update parameters
    *fOut << "// Update parameters";
    tab(n, *fOut);
    *fOut << "update(";
    shortnames2.printArgsCall();
    *fOut << ");";
    tab(n, *fOut);
    
    // Compute one frame
    *fOut << "// Compute one frame";
    tab(n, *fOut);
    *fOut << "outputs = compute(";
    for (int in = 0; in < fNumInputs; in++) {
        *fOut << "in" << std::to_string(in+1);
        if (in < fNumInputs - 1) *fOut << ",";
    }
    *fOut << ");";
    tab(n, *fOut);
    *fOut << "// Write the outputs";
    tab(n, *fOut);
    for (int out = 0; out < fNumOutputs; out++) {
        // *fOut << "out" << std::to_string(out+1) << " = outputs[" << std::to_string(out) << "];";
        // Workaround for C++ generation bug when no audio inputs
        // See: https://beta.cycling74.com/t/still-confused-on-how-to-use-parameters-in-rnbo-codebox-patches/1763/4
        if (fNumInputs == 0) {
            *fOut << "out" << std::to_string(out+1) << " = outputs[" << std::to_string(out) << "] + in1;";
        } else {
            *fOut << "out" << std::to_string(out+1) << " = outputs[" << std::to_string(out) << "];";
        }
        tab(n, *fOut);
    }
}

// Scalar
CodeboxScalarCodeContainer::CodeboxScalarCodeContainer(const string& name,
                                                    int numInputs, int numOutputs,
                                                    std::ostream* out,
                                                    int sub_container_type)
    : CodeboxCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

// Given as an example of what a real backend would have to implement.
void CodeboxScalarCodeContainer::generateCompute(int n)
{
    *fOut << "// Compute one frame";
    tab(n, *fOut);

    *fOut << "function compute(";
    for (int in = 0; in < fNumInputs; in++) {
        *fOut << "i" << std::to_string(in);
        if (in < fNumInputs - 1) *fOut << ",";
    }
    *fOut << ") {";
    tab(n + 1, *fOut);
    for (int in = 0; in < fNumInputs; in++) {
        *fOut << "input" << std::to_string(in) << "_cb = i" << std::to_string(in) << ";";
        tab(n + 1, *fOut);
    }
  
    gGlobal->gCodeboxVisitor->Tab(n + 1);
    
    // Generates one sample block
    BlockInst* block = fCurLoop->generateOneSample();
    block->accept(gGlobal->gCodeboxVisitor);

    // Generates post compute
    generatePostComputeBlock(gGlobal->gCodeboxVisitor);
    
    *fOut << "return [";
    for (int out = 0; out < fNumOutputs; out++) {
        *fOut << "output" << std::to_string(out) << "_cb";
        if (out < fNumOutputs - 1) *fOut << ",";
    }
    *fOut << "];";
    tab(n, *fOut);
    *fOut << "}";
    tab(n, *fOut);
}

