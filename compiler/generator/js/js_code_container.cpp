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

#include "js_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "exception.hh"
#include "global.hh"

using namespace std;

map <string, bool> JAVAScriptInstVisitor::gFunctionSymbolTable;
map <string, string> JAVAScriptInstVisitor::gMathLibTable;

dsp_factory_base* JAVAScriptCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    ((dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : ""), "");
}

CodeContainer* JAVAScriptCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new JAVAScriptScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* JAVAScriptCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    CodeContainer* container;
    
    if (gGlobal->gMemoryManager) {
        throw faustexception("ERROR : -mem not suported for JavaScript\n");
    }
    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : quad format not supported for JavaScript\n");
    }
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for JavaScript\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for JavaScript\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for JavaScript\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler mode not supported for JavaScript\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector mode not supported for JavaScript\n");
    } else {
        container = new JAVAScriptScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

// Scalar
JAVAScriptScalarCodeContainer::JAVAScriptScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :JAVAScriptCodeContainer(name, numInputs, numOutputs, out)
{
     fSubContainerType = sub_container_type;
}

JAVAScriptScalarCodeContainer::~JAVAScriptScalarCodeContainer()
{}

void JAVAScriptCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "function " << fKlassName << "() {";

        tab(n+1, *fOut);
        tab(n+1, *fOut);
    
        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);
        
        tab(n+1, *fOut);
        // fKlassName used in method naming for subclasses
        produceInfoFunctions(n+1, fKlassName, "dsp", true, false, &fCodeProducer);
    
        // TODO
        //generateInstanceInitFun("instanceInit" + fKlassName, true, false)->accept(&fCodeProducer);

        // Inits
        tab(n+1, *fOut); *fOut << "this.instanceInit" << fKlassName << " = function(samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
            generateResetUserInterface(&fCodeProducer);
            generateClear(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
   
        // Fill
        string counter = "count";
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "this.fill" << fKlassName << " = function" << subst("($0, output) {", counter);
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateComputeBlock(&fCodeProducer);
            ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
            loop->accept(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

    tab(n, *fOut); *fOut << "}" << endl;
    
    // Memory methods (as globals)
    tab(n, *fOut); *fOut << "new" << fKlassName << " = function() { "
                        << "return new "<< fKlassName << "()"
                        << "; }";

    tab(n, *fOut); *fOut << "delete" << fKlassName << "= function(dsp) {}";
    
    tab(n, *fOut);
}

void JAVAScriptCodeContainer::produceClass()
{
    int n = 0;

    // Libraries
    printLibrary(*fOut);
    
    // Sub containers
    generateSubContainers();

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "function " << fKlassName << "() {";

        tab(n+1, *fOut);

        // Fields
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

        // Print metadata declaration
        tab(n+1, *fOut); *fOut   << "this.metadata = function(m) { ";

        for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
            if (i->first != tree("author")) {
                tab(n+2, *fOut); *fOut << "m.declare(\"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
            } else {
                for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                    if (j == i->second.begin()) {
                        tab(n+2, *fOut); *fOut << "m.declare(\"" << *(i->first) << "\", " << **j << ");" ;
                    } else {
                        tab(n+2, *fOut); *fOut << "m.declare(\"" << "contributor" << "\", " << **j << ");";
                    }
                }
            }
        }

        tab(n+1, *fOut); *fOut << "}" << endl;
  
        tab(n+1, *fOut);
        // No class name for main class
        produceInfoFunctions(n+1, "", "dsp", true, true, &fCodeProducer);

        // Inits
    
        // TODO
        /*
        generateStaticInitFun("classInit", false)->accept(&fCodeProducer);
        generateInstanceInitFun("instanceInit", true, true)->accept(&fCodeProducer);
        */

        tab(n+1, *fOut); *fOut << "this.classInit = function(samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateStaticInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "this.instanceConstants = function(samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
            *fOut << "this.instanceClear();";
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "instanceResetUserInterface = function() {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateResetUserInterface(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "this.instanceClear = function() {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateClear(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
       
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "this.init = function(samplingFreq) {";
            tab(n+2, *fOut); *fOut << "this.classInit(samplingFreq);";
            tab(n+2, *fOut); *fOut << "this.instanceInit(samplingFreq);";
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "this.instanceInit = function(samplingFreq) {";
            tab(n+2, *fOut); *fOut << "this.instanceConstants(samplingFreq);";
            tab(n+2, *fOut); *fOut << "this.instanceResetUserInterface();";
            tab(n+2, *fOut); *fOut << "this.instanceClear();";
        tab(n+1, *fOut); *fOut << "}";

        // User interface
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "this.buildUserInterface = function(ui_interface) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateUserInterface(&fCodeProducer);
            printlines(n+2, fUICode, *fOut);
        tab(n+1, *fOut); *fOut << "}";

        // Compute
        generateCompute(n);

        // Possibly generate separated functions
        fCodeProducer.Tab(n+1);
        tab(n+1, *fOut);
        generateComputeFunctions(&fCodeProducer);

    tab(n, *fOut); *fOut << "}\n" << endl;
}

void JAVAScriptScalarCodeContainer::generateCompute(int n)
{
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("this.compute = function($0, inputs, outputs) {", fFullCount);
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

        // Generates one single scalar loop
        ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
        loop->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}
