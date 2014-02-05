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

#include "asmjs_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "exception.hh"
#include "global.hh"

using namespace std;

CodeContainer* ASMJAVAScriptCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new ASMJAVAScriptScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* ASMJAVAScriptCodeContainer::createContainer(const string& name, const string& super, int numInputs, int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for ASMJavaScript\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for ASMJavaScript\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("OpenMP : OpenMP not supported for ASMJavaScript\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("Scheduler mode not supported for ASMJavaScript\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("Vector mode not supported for ASMJavaScript\n");
    } else {
        //container = new ASMJAVAScriptScalarCodeContainer(name, super, numInputs, numOutputs, dst, kInt);
        throw faustexception("Scalar mode not (yet) supported for ASMJavaScript\n");
    }

    return container;
}

// Scalar
ASMJAVAScriptScalarCodeContainer::ASMJAVAScriptScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :ASMJAVAScriptCodeContainer(name, super, numInputs, numOutputs, out)
{
     fSubContainerType = sub_container_type;
}

ASMJAVAScriptScalarCodeContainer::~ASMJAVAScriptScalarCodeContainer()
{}

void ASMJAVAScriptCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "function " << fKlassName << "() {";

        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);
        
        tab(n+1, *fOut);
        tab(n+1, *fOut);
        produceInfoFunctions(n+1, fKlassName, false);

        // Inits
        tab(n+1, *fOut); *fOut << "this.instanceInit" << fKlassName << " = function(samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
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
    tab(n, *fOut); *fOut << "new" << fKlassName << " = function() {"
                        << "return new "<< fKlassName << "()"
                        << "; }";

    tab(n, *fOut);
}

void ASMJAVAScriptCodeContainer::produceClass()
{
    int n = 0;

    generateSR();

    // Libraries
    printLibrary(*fOut);
    
    // Sub containers
    generateSubContainers();

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    //tab(n, *fOut); *fOut << "public class " << fKlassName << " extends " << fSuperKlassName << " {";
    tab(n, *fOut); *fOut << "function " << fKlassName << "() {";

        tab(n+1, *fOut);

        // Fields
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

        // Print metadata declaration
        tab(n+1, *fOut); *fOut   << "this.metadata = function(m) {";

        for (map<Tree, set<Tree> >::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
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
        produceInfoFunctions(n+1, fKlassName, true);

        // Inits
        tab(n+1, *fOut); *fOut << "this.classInit = function(samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateStaticInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "this.instanceInit = function(samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "this.init = function(samplingFreq) {";
            tab(n+2, *fOut); *fOut << "this.classInit(samplingFreq);";
            tab(n+2, *fOut); *fOut << "this.instanceInit(samplingFreq);";
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

// Functions are coded with a "class" prefix, so to stay separated in "gGlobalTable"
void ASMJAVAScriptCodeContainer::produceInfoFunctions(int tabs, const string& classname, bool isvirtual)
{
    // Input/Output method
    fCodeProducer.Tab(tabs);
    generateGetInputs(subst("$0::getNumInputs", classname), true, isvirtual)->accept(&fCodeProducer);
    generateGetOutputs(subst("$0::getNumOutputs", classname), true, isvirtual)->accept(&fCodeProducer);

    // Input Rates
    fCodeProducer.Tab(tabs);
    generateGetInputRate(subst("$0::getInputRate", classname), true, isvirtual)->accept(&fCodeProducer);

    // Output Rates
    fCodeProducer.Tab(tabs);
    generateGetOutputRate(subst("$0::getOutputRate", classname), true, isvirtual)->accept(&fCodeProducer);
}

void ASMJAVAScriptScalarCodeContainer::generateCompute(int n)
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
